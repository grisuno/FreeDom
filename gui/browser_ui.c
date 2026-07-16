/*
 * browser_ui — Wayland + Cairo + xkbcommon GUI for Freedom.
 *
 * Provides a minimal browser window with Back/Forward buttons, URL bar, and
 * scrollable text content. The heavy lifting (navigation state, secure_fetch,
 * tab sandbox) lives in src/browser.c, src/secure_fetch.c and src/tab.c; this
 * file only wires input/output and paints the frame.
 *
 * Visual test only: run on a Wayland session.
 */

#define _GNU_SOURCE

#include "browser.h"
#include "box_style.h"
#include "box_tree.h"
#include "compositor.h"
#include "css.h"
#include "css_color.h"
#include "data_url.h"
#include "download.h"
#include "frame_clock.h"
#include "freebug.h"
#include "hostblock.h"
#include "hostedit.h"
#include "image_decode.h"
#include "interp.h"
#include "js_policy.h"
#include "link_nav.h"
#include "net_realm.h"
#include "pdf_export.h"
#include "prefetch.h"
#include "prefs.h"
#include "profile.h"
#include "render_doc.h"
#include "render_policy.h"
#include "request_policy.h"
#include "text_shape.h"
#include "textfield.h"
#include "webcaps.h"
#include "ui.h"
#include "url.h"
#include "zoom.h"

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <poll.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/eventfd.h>
#include <sys/timerfd.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>

#include <wayland-client.h>
#include <wayland-cursor.h>
#include <cairo/cairo.h>
#include <cairo/cairo-pdf.h>
#include <fontconfig/fontconfig.h>
#include <xkbcommon/xkbcommon.h>

#include "xdg-shell-client-protocol.h"
#include "xdg-decoration-client-protocol.h"

#include "browser_ui_internal.h"

#define UI_TOOLBAR_H   36.0
#define UI_TITLEBAR_H  30.0
#define UI_TABBAR_H    30.0   /* height of the tab strip (between titlebar and toolbar) */
#define UI_TAB_MIN_W   80.0   /* minimum drawn width of a tab before it shrinks further */
#define UI_TAB_MAX_W   200.0  /* preferred width of a tab when there is room */
#define UI_TAB_NEW_W   30.0   /* width of the trailing "new tab" (+) button */
#define UI_TAB_CLOSE_W 18.0   /* width of a tab's close (x) hot zone at its right edge */
#define UI_BTN_W       48.0
#define UI_WIN_BTN_W   30.0
#define UI_MARGIN      6.0
#define UI_BTN_LEFT    0x110  /* BTN_LEFT */
#define UI_LIST_INDENT 24.0   /* left indent (px) per list nesting level (ul/ol) */

/* Vertical scrollbar in the content area's right gutter. The gutter width is
 * always reserved (subtracted from the content width) so the scroll affordance and
 * the click hit-test share one geometry and never overlap the text. */
#define UI_SCROLLBAR_W   12.0  /* reserved gutter width on the content's right edge */
#define UI_SCROLLBAR_MIN 28.0  /* minimum thumb height so it stays grabbable */
#define UI_SCROLLBAR_PAD 2.0   /* inset of the thumb inside the track */

/* Border band (px) that starts an interactive window resize when dragged, used
 * only with client-side decorations (the compositor handles edges under SSD). */
#define UI_RESIZE_MARGIN 6.0

/* Options menu (gear) panel geometry and the pointer cursor size, gathered with
 * the other chrome constants so no value is hardcoded at a call site. The panel is
 * wide enough to edit a User-Agent string. */
#define UI_MENU_W       340.0
#define UI_MENU_ITEM_H  28.0
#define UI_MENU_PAD     6.0
#define UI_CHECK_SZ     16.0
#define UI_MENU_LABEL_H 22.0   /* height of the "User-Agent" section label row */
#define UI_MENU_INPUT_H 26.0   /* height of the editable User-Agent box */
#define UI_HAMBURGER_W  18.0   /* width of the drawn menu-button icon */
#define UI_HAMBURGER_GAP 5.0   /* vertical gap between the three icon bars */
#define UI_CURSOR_SIZE  24     /* themed cursor size in px (XCURSOR_SIZE default) */
#define UI_TOAST_PAD    8.0    /* padding inside the toast banner */
#define OMNI_MAX_SUGG   6      /* max omnibox autocomplete rows shown */
#define UI_OMNI_ROW_H   24.0   /* height of one omnibox suggestion row */
#define UI_TWO_PI       6.28318530717958647692 /* radians of a full circle (busy clock) */

/* Form control geometry: inner padding of a text box, the preferred text-box width
 * (clamped to the content width), and the horizontal padding of a button. */
#define UI_INPUT_PAD     6.0
#define UI_INPUT_WIDTH   360.0
#define UI_BUTTON_HPAD   14.0
#define UI_FORM_FIELDS_MAX 64  /* matches FM_MAX_FIELDS; cap gathered controls */

/* Link/author text-decoration geometry, expressed relative to the run's font so it
 * scales with heading-sized text. Underline offset is below the baseline; the
 * line-through sits over the x-height and the overline above the ascent. */
#define UI_UNDERLINE_OFFSET 0.12
#define UI_UNDERLINE_THICK  1.0
#define UI_STRIKE_OFFSET    0.32   /* above the baseline (≈ through the x-height) */
#define UI_OVERLINE_OFFSET  0.78   /* above the baseline (≈ at the ascent) */

/* Largest text slice measured/drawn at once (one word, or one clipped label).
 * Words longer than this are still placed, just measured up to the cap. */
#define UI_SLICE_MAX 512

/* Monotonic millisecond clock for toast timing (caller of the pure browser API). */
static uint64_t now_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u;
}

/* Which host list a UI_MENU_HOSTADD item edits (carried in the item's theme_val). */
enum { HOSTLIST_BLOCK = 0, HOSTLIST_ALLOW = 1, HOSTLIST_JS = 2 };

/* The options-menu items. A capability item toggles a bool in rdp_caps by field
 * offset (labels and the flag live in one place, no magic indices); a theme item
 * selects a palette; the force item ignores author colours. */
typedef enum ui_menu_action {
    UI_MENU_CAP = 0,  /* toggles w->caps.<offset>; needs a re-render from cache */
    UI_MENU_THEME,    /* selects w->theme_mode (theme_val); needs only a repaint */
    UI_MENU_FORCE,    /* toggles w->force_theme; needs only a repaint */
    UI_MENU_TOR,      /* toggles Tor routing (tor_enabled + torify clearnet) */
    UI_MENU_I2P,      /* toggles I2P routing for .i2p */
    UI_MENU_JS,       /* cycles the JS policy (off -> allowlist -> on) */
    UI_MENU_READER,   /* toggles distraction-free (reader) mode; re-renders from cache */
    UI_MENU_PDF,      /* action (not a toggle): export the page to a vector PDF */
    UI_MENU_PNG,      /* action (not a toggle): export the page to a raster PNG */
    UI_MENU_FREEBUG,  /* toggles the Freebug developer console (second window) */
    UI_MENU_HOSTADD,  /* action: add the current host to a .conf list (theme_val selects which) */
    UI_MENU_BOOKMARK, /* action: toggle a bookmark for the current page (Ctrl+B) */
    UI_MENU_BOOKMARKS,/* action: open the internal about:bookmarks page */
    UI_MENU_REMHIST   /* toggles persistent history (off also forgets it) */
} ui_menu_action;

typedef struct ui_menu_item {
    const char    *label;
    ui_menu_action action;
    size_t         cap_offset; /* offset of a bool field within rdp_caps (UI_MENU_CAP) */
    int            theme_val;  /* the ui_theme_mode this item selects (UI_MENU_THEME) */
} ui_menu_item;

static const ui_menu_item UI_MENU_ITEMS[] = {
    { "Dark mode",            UI_MENU_THEME, 0,                          UI_THEME_DARK },
    { "Reading mode (sepia)", UI_MENU_THEME, 0,                          UI_THEME_SEPIA },
    { "Force theme colors",   UI_MENU_FORCE, 0,                          0 },
    { "Load images",          UI_MENU_CAP,   offsetof(rdp_caps, images), 0 },
    { "Author styles (CSS)",  UI_MENU_CAP,   offsetof(rdp_caps, css),    0 },
    { "Distraction-free (Ctrl+D)", UI_MENU_READER, 0,                    0 },
    { "Bookmark page (Ctrl+B)", UI_MENU_BOOKMARK, 0,                     0 },
    { "Bookmarks & history",  UI_MENU_BOOKMARKS, 0,                      0 },
    { "Remember history",     UI_MENU_REMHIST, 0,                        0 },
    { "Tor routing (.onion)", UI_MENU_TOR,   0,                          0 },
    { "I2P routing (.i2p)",   UI_MENU_I2P,   0,                          0 },
    { "JavaScript",           UI_MENU_JS,    0,                          0 },
    { "Freebug console (F12)", UI_MENU_FREEBUG, 0,                       0 },
    { "Block this site (Ctrl+Shift+B)", UI_MENU_HOSTADD, 0,             HOSTLIST_BLOCK },
    { "Allow this site (Ctrl+Shift+A)", UI_MENU_HOSTADD, 0,             HOSTLIST_ALLOW },
    { "Allow JS here (Ctrl+Shift+J)",   UI_MENU_HOSTADD, 0,             HOSTLIST_JS },
    { "Save as PDF (Ctrl+P)", UI_MENU_PDF,   0,                          0 },
    { "Save as PNG (Ctrl+Shift+P)", UI_MENU_PNG, 0,                      0 },
};
#define UI_MENU_COUNT (sizeof UI_MENU_ITEMS / sizeof UI_MENU_ITEMS[0])

/* Toolbar control under the pointer, for the hover highlight (the same affordance
 * links already get). */
typedef enum ui_hot {
    UI_HOT_NONE = 0, UI_HOT_BACK, UI_HOT_FWD, UI_HOT_RELOAD, UI_HOT_GO, UI_HOT_MENU
} ui_hot;

/* Live editable state for one form text control, aliasing a block of the current
 * rd_doc (not owned; valid until the doc is replaced). The field carries the value
 * the user is editing; submission reads it back. */
typedef struct ui_input_state {
    const rd_block *blk;   /* the RD_INPUT block (aliases w->doc) */
    tf_field        field; /* live editable value */
} ui_input_state;

/* Hard cap on the response body of an image subresource (a PNG/JPEG; the decoder
 * bounds the decoded pixels further). Keeps a hostile server from streaming forever. */
#define UI_IMAGE_MAX_BODY ((size_t)(8u * 1024u * 1024u))

/* A decoded image for one RD_IMAGE block of the current doc. surface owns the
 * pixels (ARGB32) and is NULL when the image was blocked, not fetched, or could
 * not be decoded (the placeholder is drawn instead). nat_w/nat_h are the natural
 * pixel dimensions. The block aliases w->doc (not owned). */
/* href is an OWNED copy of the image's URL, not a pointer into w->doc (fixed
 * 2026-07-16): a worker result applied outside a fresh navigation (a click, or a
 * JS timer firing via OP_TICK -- see apply_click_result) rebuilds w->doc WHOLESALE
 * from scratch without re-running load_images, so any rd_block* recorded here
 * would immediately dangle and, worse, silently stop matching ANY block in the
 * new doc (find_image compared pointer identity) -- every already-decoded image
 * would revert to its placeholder on the very next repaint even though nothing
 * about the image actually changed. Matching by URL content instead is stable
 * across a doc rebuild with no re-fetch needed (the decoded surface is reused
 * as-is): a JS timer firing seconds into a page like an ad-heavy anime-streaming
 * site is exactly the case this fixes. */
typedef struct ui_image {
    char            *href;
    cairo_surface_t *surface;
    int              nat_w, nat_h;
} ui_image;

/* A decoded CSS background-image for one box of the current doc (2026-07-16).
 * Same shape as ui_image and the same reasoning applies: url is an OWNED copy
 * (not a pv_box_def* into w->doc), so it survives a doc rebuild that does not
 * re-run load_bg_images. surface NULL means blocked/unset/failed (paint as if
 * there were no background-image at all, no placeholder: it is decoration, not
 * content with alt text, matching real-browser behaviour for a failed
 * background). */
typedef struct ui_bg_image {
    char             *url;
    cairo_surface_t  *surface;
    int               nat_w, nat_h;
} ui_bg_image;

/* Maximum concurrent tabs. Bounded so the per-tab snapshot array is a fixed,
 * auditable size (no unbounded growth from a hostile page opening tabs; this
 * browser never opens a tab on a page's behalf anyway). */
#define UI_MAX_TABS 16

/* One tab's complete per-page state: everything that must persist when the tab is
 * not the foreground one. The browser_window keeps the ACTIVE tab's copy in its own
 * fields (so the 200+ render/event call sites stay unchanged); tab_save/tab_restore
 * move this set in and out of the slot array on a switch. All owned pointers are
 * transferred by value (no deep copy, no free): exactly one of {live window field,
 * inactive slot} owns each allocation at any time. */
typedef struct tab_ctx {
    browser_state   bs;          /* history, URL bar, page text/title, exceptions */
    rd_doc         *doc;         /* structured render, or NULL (text mode) */
    rdp_caps        caps;        /* per-tab render capabilities (images/CSS/JS) */
    double          scroll, content_total_h;
    ui_input_state *inputs; size_t input_count; int focused_input;
    ui_image       *images; size_t image_count;
    ui_bg_image    *bg_images; size_t bg_image_count;
    char           *cur_html; size_t cur_html_len; char *cur_top;
    int             loading;
    const char     *hover_href; /* aliases doc; moves with it */
    int             hover_cursor; /* css_cursor resolved at the pointer, moves with hover_href */
} tab_ctx;

#include "hls.h"

typedef struct browser_window {
    struct wl_display    *display;
    struct wl_registry   *registry;
    struct wl_compositor *compositor;
    struct wl_shm        *shm;
    struct xdg_wm_base   *wm_base;
    struct wl_seat       *seat;
    struct wl_pointer    *pointer;
    struct wl_keyboard   *keyboard;

    struct wl_surface    *surface;
    struct xdg_surface   *xdg_surface;
    struct xdg_toplevel  *xdg_toplevel;

    int width, height;
    int configured;
    int running;
    int redraw_pending;

    struct wl_buffer *buffer;
    void             *shm_data;
    size_t            shm_size;
    cairo_surface_t  *cairo_surface;

    struct zxdg_decoration_manager_v1  *deco_mgr;
    struct zxdg_toplevel_decoration_v1 *deco;
    int use_csd;

    double ptr_x, ptr_y;

    browser_state bs;
    int url_bar_focused;
    /* Omnibox autocomplete: allow.conf treated as a favorites list. `favorites` holds
     * the concatenated allow.conf bodies (loaded at startup, refreshed on edit);
     * omni_sugg/omni_sugg_n are the live matches for what is typed; omni_sel is the
     * highlighted row (-1 = none). The matching is the pure he_suggest. */
    char  *favorites;
    char   omni_sugg[OMNI_MAX_SUGG][HE_MAX_HOST + 1];
    int    omni_sugg_n;
    int    omni_sel;

    /* Persisted profile (Hito 10): preferences + bookmarks + history, sealed to
     * the config dir via profile (AEAD, per-device key). profile_rw is 1 only
     * when the profile opened AND authenticated; otherwise saves are disabled so
     * a foreign/corrupt prefs.bin is never clobbered (session stays memory-only). */
    prefs_state prefs;
    profile_ctx profile;
    int         profile_rw;

    ui_theme  theme;
    int       theme_mode;  /* ui_theme_mode selected in the options menu */
    int       zoom_pct;    /* page zoom percentage (window-level; see zoom.h) */
    int       force_theme; /* ignore author fg/bg colors, use the theme (reading) */
    int       reader;      /* distraction-free mode: drop boilerplate + author CSS, wide margins */
    int       loading;   /* a network request is in flight (busy clock shown) */
    ui_hot    hot;       /* toolbar button under the pointer, or UI_HOT_NONE */
    rd_doc   *doc;      /* structured render of the current page; NULL => text mode */
    rdp_caps  caps;     /* per-page render capabilities (images off by default) */
    hb_set   *hosts;    /* /etc/hosts-format blocklist + allowlist; consulted pre-fetch */
    hb_set   *js_hosts; /* js.conf allowlist (HB_LIST_ALLOW): hosts permitted to run JS */
    hb_set   *impersonate_hosts; /* impersonate.conf: triple-opt-in TLS-blend hosts */
    jsp_mode  js_mode;  /* global JS policy (Secure by Default: JSP_ALLOWLIST) */
    nr_config net_cfg;  /* Tor/I2P routing (Privacy by Default: opt-in, off by default) */
    char      tor_addr[64];  /* Tor SOCKS5h proxy "host:port" (default 127.0.0.1:9050) */
    char      i2p_addr[64];  /* I2P HTTP proxy "host:port" (default 127.0.0.1:4444) */
    double    scroll;   /* content scroll offset in pixels */
    double    content_total_h;  /* full height of the laid-out content, cached each paint */
    int       maximized;        /* toplevel currently maximized (from xdg states) */
    int       dragging_scroll;  /* the scrollbar thumb is being dragged */
    double    scroll_grab_dy;   /* pointer offset within the thumb at drag start */
    int       pending_g;        /* a 'g' was pressed; a second one scrolls to the top (vim gg) */

    /* Real async JS timers (2026-07-11): the worker reports its smallest pending
     * timer delay (tab_page.next_timer_ms); the trusted parent schedules an
     * OP_TICK from it via the event-loop poll timeout. js_ticks_left caps the
     * ticks per page load (anti battery-drain; the shared per-page JS budget
     * bounds the work itself). js_tick_due_ms 0 = no tick pending. */
    uint64_t    js_tick_due_ms;   /* absolute now_ms() deadline, 0 = none */
    int         js_tick_elapsed;  /* virtual ms to advance when the tick fires */
    int         js_ticks_left;    /* remaining ticks for this page load */

    int         menu_open;     /* the options (gear) panel is showing */
    const char *hover_href;    /* link target under the pointer (aliases doc), or NULL */
    int         hover_cursor;  /* author cursor (css_cursor) resolved at the pointer, or
                                 * CSS_CUR_UNSET; drives the hand-vs-arrow decision alongside
                                 * hover_href/hot */

    /* Live form text controls of the current page (rebuilt with the doc). */
    ui_input_state *inputs;
    size_t          input_count;
    int             focused_input; /* index into inputs, or -1 */

    /* Decoded images of the current page (rebuilt with the doc; one per RD_IMAGE). */
    ui_image       *images;
    size_t          image_count;

    /* Decoded CSS background-images of the current page (2026-07-16; rebuilt with
     * the doc, one per box with a resolved bg_image_url). */
    ui_bg_image    *bg_images;
    size_t          bg_image_count;

    /* Configurable network User-Agent (session only; empty => SF_DEFAULT_USER_AGENT,
     * which IS the anti_fp normalized identity, matching navigator.userAgent). A custom
     * value overrides only the wire header; the JS identity stays normalised. Edited in
     * the options menu with the shared textfield primitive. */
    tf_field    ua_field;
    int         ua_field_focused;

    /* Cached source of the current page, so a capability toggle re-renders without
     * a network round-trip. cur_top is the https origin (image policy) or NULL. */
    char  *cur_html;
    size_t cur_html_len;
    char  *cur_top;

    uint32_t            pointer_serial; /* last pointer-enter serial, for set_cursor */
    struct wl_cursor_theme *cursor_theme;
    struct wl_cursor       *cursor_default;
    struct wl_cursor       *cursor_hand;
    struct wl_surface      *cursor_surface;

    /* xkbcommon state for keyboard input. */
    struct xkb_context *xkb_ctx;
    struct xkb_keymap  *xkb_keymap;
    struct xkb_state   *xkb_state;

    /* Key auto-repeat. Wayland delivers one key event per physical press; a held key
     * (e.g. Backspace to clear the URL bar) repeats only if the client re-fires it on
     * a timer. repeat_key is the evdev code currently held (0 => none); rate/delay come
     * from the compositor (keyboard_repeat_info) with sane fallbacks. */
    int      repeat_timer_fd;  /* timerfd in the poll set; -1 if unavailable */
    uint32_t repeat_key;       /* evdev keycode being repeated, or 0 */
    int32_t  repeat_rate;      /* repeats per second (0 disables repeat) */
    int32_t  repeat_delay;     /* ms held before the first repeat */

    /* Clipboard (wl_data_device): paste into the focused text field, copy the address.
     * A selection offer's mime types are scanned as it is introduced (incoming_*); on
     * the selection event the chosen text mime is committed for a later paste. */
    struct wl_data_device_manager *data_device_manager;
    struct wl_data_device         *data_device;
    struct wl_data_offer          *selection_offer;  /* current clipboard offer, or NULL */
    struct wl_data_offer          *incoming_offer;   /* offer being introduced (mime scan) */
    int      selection_offer_has_text;
    int      incoming_offer_has_text;
    char     sel_mime[64];      /* committed selection's preferred text mime */
    char     incoming_mime[64]; /* preferred text mime while scanning the incoming offer */
    struct wl_data_source *copy_source; /* our active copy offer, or NULL */
    char    *copy_text;                 /* text exposed for copy (owned) */
    uint32_t last_serial;               /* latest input-event serial, for set_selection */

    /* Asynchronous network fetch. The blocking sf_get/sf_post runs on a detached
     * worker thread so the event loop stays responsive; the thread posts a completed
     * fetch_job pointer down fetch_pipe, which the loop polls and renders on the main
     * thread (Cairo/Wayland are single-threaded). net_gen is bumped on every new
     * navigation and every tab context change, so a result whose gen no longer matches
     * is discarded -- the active tab is then guaranteed unchanged since the launch. */
    int      fetch_pipe[2];  /* [0] read end (polled), [1] write end (threads) */
    uint64_t net_gen;        /* current navigation generation */
    int js_nav_depth;        /* consecutive JS-driven navigations (location.href=); capped */

    /* Streaming progressive render: the fetch thread copies accumulated body here
     * as data downloads, then signals the main loop via stream_evfd (eventfd). The
     * main handler reads under stream_lock, copies to cur_html, and re-renders, so
     * the page appears BEFORE the full response arrives. The final deliver_fetch_result
     * supersedes this with the complete body. */
    pthread_mutex_t stream_lock;
    char           *stream_body;
    size_t          stream_body_len;
    int             stream_evfd;
    uint64_t        stream_launch_gen; /* net_gen at launch; progress_cb checks this */
    uint64_t        last_stream_render;/* timestamp of last streaming render (rate limit) */

    /* Tabs. The active tab's state lives in the fields above; the other tabs are
     * parked in tab_slots. tab_count >= 1 always; active_tab is in [0, tab_count). */
    tab_ctx tab_slots[UI_MAX_TABS];
    int     tab_count;
    int     active_tab;

    /* HTTP Basic Authentication, scoped to the origin (scheme + host + port) from
     * which the credentials were extracted (https://user:pass@host/). Only injected
     * into requests whose origin matches auth_host, so credentials never leak cross-
     * origin across tabs or redirects. auth_user/auth_pass are owned; NULL = no auth. */
    char *auth_host;
    char *auth_user;
    char *auth_pass;

    /* Freebug developer console (F12 / hamburger). The active page's worker is kept
     * ALIVE after rendering (tab_worker) so the console REPL can tab_eval against the
     * live page context; console holds the captured console.* output + uncaught script
     * errors of the active page; freebug is the second Wayland toplevel (NULL until
     * first opened). kbd_focus/ptr_focus track which surface holds input focus, so the
     * shared seat listeners route keys/pointer to the right window. */
    struct tab        *tab_worker; /* forward-declared; tab.h is included further down */
    fb_buffer          console;
    struct freebug_window *freebug;
    struct wl_surface *kbd_focus;
    struct wl_surface *ptr_focus;

    /* Video playback (Fase 1+): the media decoder child process, its pipe fds,
     * and the current decoded frame for the active video element.
     *
     * Feeder thread: downloads TS segments and writes them to the decoder pipe
     * so the main (Wayland) thread never blocks on HTTP. The thread is spawned by
     * video_play() and joined by video_stop(); it reads video_pl/video_base_url
     * (set once before spawn, freed after join) and checks video_active (set to 0
     * by the main thread before join) at the top of each segment loop. The eventfd
     * signals the event loop to drain decoder frames + redraw. */
    pid_t        decoder_pid;      /* 0 = not running */
    int          decoder_out_fd;   /* read decoded frames from decoder */
    int          decoder_cmd_fd;   /* write commands to decoder (thread writes, main never) */
    uint8_t     *video_frame;      /* current decoded ARGB frame (owned) */
    int          video_w, video_h; /* frame dimensions */
    int          video_active;     /* nonzero when playing; set to 0 to stop the feeder thread */
    int          video_pending;    /* nonzero when a frame may be on the pipe */
    hls_playlist *video_pl;        /* parsed segment list (owned; freed in video_stop after join) */
    char         *video_base_url;  /* m3u8 base URL for segment resolution (owned) */
    int           video_eof;       /* feeder thread has sent MD_FLUSH */
    pthread_t     video_thread;    /* feeder thread handle */
    int           video_evfd;      /* eventfd: feeder thread → main thread wake */

    /* Mouse event dispatch (Phase 1.2). Caches the DOM node under the pointer for
     * mouseover/mouseout detection between motion events. DOM_NODE_NONE = no hover. */
    dom_node_id mouse_hover_node;

    /* Animation frame clock (Phase R1). page_load_mono_ms is the monotonic timestamp
     * when the current page finished rendering. Animation state is derived from
     * elapsed wall-clock time relative to this. fc is the pure frame_clock that
     * signals whether the repaint loop should run when animations are active. */
    uint64_t page_load_mono_ms;
    fc_clock fc;
} browser_window;

/* Freebug second-window forward declarations (defined further down, but referenced
 * by render_current_ex, the menu and the input listeners above their definition). */
typedef struct freebug_window freebug_window;
static void freebug_toggle(browser_window *w);
static void freebug_redraw(browser_window *w);
static void freebug_destroy(browser_window *w);
static int  freebug_is_open(const browser_window *w);
static int  freebug_owns_surface(const browser_window *w, const struct wl_surface *sf);
static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                               const char *utf8, int n, int ctrl, int shift);
static void freebug_pointer_button(browser_window *w, uint32_t serial,
                                   uint32_t button, uint32_t state);
static void freebug_pointer_motion(browser_window *w);
static void freebug_pointer_axis(browser_window *w, wl_fixed_t value);

static void redraw(browser_window *w);
static void profile_sync(browser_window *w);  /* persists preference changes (Hito 10) */

/* Rebuilds the live theme for the current mode and scales the font-driven metrics
 * by the page zoom. Layout and text flow read these straight from the theme, so a
 * zoom change is just "rebuild + repaint" -- no new pure layout path. The page
 * gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF export keeps its own forced light theme and never calls this. */
/* Comfortable reading-column width (px) used by distraction-free mode: the text is
 * centered in a column no wider than this, so long lines do not sprawl edge to edge. */
#define UI_READER_COLUMN_W 720.0

static void apply_theme(browser_window *w) {
    w->theme = ui_theme_for(w->theme_mode);
    double s = zm_scale(w->zoom_pct);
    w->theme.body_font     = zm_apply(w->theme.body_font, w->zoom_pct);
    w->theme.paragraph_gap = w->theme.paragraph_gap * s;
    w->theme.image_box_pad = w->theme.image_box_pad * s;
    /* Distraction-free centering lives in content_margin_x (HORIZONTAL only); it must
     * NOT widen w->theme.content_margin, which is also the VERTICAL page margin
     * (content_geometry height + paint origin) -- inflating it there pushed the
     * content off-screen on wide windows. */
}

/* Applies a new zoom level: rebuild the theme and repaint. The page is laid out
 * fresh from w->theme on every paint, so no re-fetch and no worker round-trip are
 * needed -- the text simply reflows at the new size. */
static void apply_zoom(browser_window *w) {
    apply_theme(w);
    char msg[48];
    snprintf(msg, sizeof msg, "Zoom %d%%", w->zoom_pct);
    browser_set_status(&w->bs, msg, now_ms());
    profile_sync(w);  /* the zoom level persists across sessions */
    redraw(w);
}

/* --- shm buffer (same pattern as ui_render.c) --- */

static void buffer_release(void *data, struct wl_buffer *wl_buffer) {
    (void)wl_buffer;
    (void)data;
}
static const struct wl_buffer_listener buffer_listener = { buffer_release };

static void destroy_buffer(browser_window *w) {
    if (w->cairo_surface) { cairo_surface_destroy(w->cairo_surface); w->cairo_surface = NULL; }
    if (w->buffer) { wl_buffer_destroy(w->buffer); w->buffer = NULL; }
    if (w->shm_data) { munmap(w->shm_data, w->shm_size); w->shm_data = NULL; w->shm_size = 0; }
}

static int ensure_buffer(browser_window *w) {
    int stride = w->width * 4;
    size_t size = (size_t)stride * (size_t)w->height;
    if (w->buffer && w->shm_size == size && w->cairo_surface) return 0;

    destroy_buffer(w);

    int fd = memfd_create("freedom-shm", MFD_CLOEXEC);
    if (fd < 0) return -1;
    if (ftruncate(fd, (off_t)size) < 0) { close(fd); return -1; }

    void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) { close(fd); return -1; }

    struct wl_shm_pool *pool = wl_shm_create_pool(w->shm, fd, (int32_t)size);
    w->buffer = wl_shm_pool_create_buffer(pool, 0, w->width, w->height, stride, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);
    if (w->buffer == NULL) { munmap(data, size); return -1; }
    wl_buffer_add_listener(w->buffer, &buffer_listener, w);

    w->shm_data = data;
    w->shm_size = size;
    w->cairo_surface = cairo_image_surface_create_for_data(
        (unsigned char *)data, CAIRO_FORMAT_ARGB32, w->width, w->height, stride);
    return (cairo_surface_status(w->cairo_surface) == CAIRO_STATUS_SUCCESS) ? 0 : -1;
}

/* --- page loading --- */

static char *read_file(const char *path, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return NULL; }
    rewind(f);
    char *buf = (char *)malloc((size_t)sz + 1);
    if (buf == NULL) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    buf[n] = '\0';
    if (out_len != NULL) *out_len = n;
    return buf;
}

/* Reads up to cap bytes of a local file; fails closed (NULL) if the file is larger
 * than cap or unreadable. Used for local images, so a giant local file cannot be
 * read whole into memory (anti-DoS, like the network image cap). */
static uint8_t *read_file_bounded(const char *path, size_t cap, size_t *out_len) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz < 0 || (size_t)sz > cap) { fclose(f); return NULL; }
    rewind(f);
    uint8_t *buf = (uint8_t *)malloc((size_t)sz > 0 ? (size_t)sz : 1);
    if (buf == NULL) { fclose(f); return NULL; }
    size_t n = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if (out_len != NULL) *out_len = n;
    return buf;
}

/* Builds a "file:///<canonical absolute path>" origin from a local path (or passes
 * through a file:// URL's path). realpath canonicalizes; on failure (file gone, too
 * long) returns 0 and the caller proceeds with no origin (local images then simply
 * do not resolve). This origin makes a local page "act like https": relative
 * references and images resolve against it, confined to its own directory. */
static int build_file_origin(const char *path_or_url, char *out, size_t outsz) {
    const char *path = url_is_file(path_or_url) ? url_file_path(path_or_url) : path_or_url;
    char abs[PATH_MAX];
    if (path == NULL || realpath(path, abs) == NULL) return 0;
    int n = snprintf(out, outsz, "file://%s", abs);
    return n > 0 && (size_t)n < outsz;
}

/* Loads one /etc/hosts-format .conf file (if present and readable) into the given
 * list. A missing file is not an error: the filter fails open, never over-blocking. */
static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list) {
    char path[1024];
    int n = snprintf(path, sizeof path, "%s/%s", dir, name);
    if (n <= 0 || (size_t)n >= sizeof path) return;
    size_t len = 0;
    char *txt = read_file(path, &len);
    if (txt == NULL) return;
    hb_load(s, txt, list);   /* HB_ERR_OOM only drops extra entries; not fatal here */
    free(txt);
}

/* Builds the host filter from the user's .conf lists. Privacy by Default: block.conf
 * (a /etc/hosts-format blocklist) blocks trackers/ads and their subdomains; allow.conf
 * re-enables specific (sub)domains and wins over the blocklist. Directories are tried
 * in order -- $FREEDOM_HOSTS_DIR, then ~/.config/freedom, then ./config (repo-local) --
 * and each that exists is loaded cumulatively. Returns NULL only on OOM (hb_check
 * then treats every host as allowed). */
static hb_set *build_host_filter(void) {
    hb_set *s = hb_new();
    if (s == NULL) return NULL;

    const char *env = getenv("FREEDOM_HOSTS_DIR");
    if (env != NULL && env[0] != '\0') {
        load_host_file(s, env, "block.conf", HB_LIST_BLOCK);
        load_host_file(s, env, "allow.conf", HB_LIST_ALLOW);
    }

    const char *home = getenv("HOME");
    if (home != NULL && home[0] != '\0') {
        char dir[1024];
        int n = snprintf(dir, sizeof dir, "%s/.config/freedom", home);
        if (n > 0 && (size_t)n < sizeof dir) {
            load_host_file(s, dir, "block.conf", HB_LIST_BLOCK);
            load_host_file(s, dir, "allow.conf", HB_LIST_ALLOW);
        }
    }

    load_host_file(s, "config", "block.conf", HB_LIST_BLOCK);
    load_host_file(s, "config", "allow.conf", HB_LIST_ALLOW);
    return s;
}

/* Builds the per-host JS allowlist from js.conf (same /etc/hosts format and search
 * order as the host filter). Loaded as HB_LIST_ALLOW so hb_is_allowlisted reports
 * membership (subdomains covered). Returns NULL on OOM (then no host is allowlisted,
 * so under JSP_ALLOWLIST no page runs JS -- fail closed). */
static hb_set *build_conf_allowlist(const char *fname) {
    hb_set *s = hb_new();
    if (s == NULL) return NULL;

    const char *env = getenv("FREEDOM_HOSTS_DIR");
    if (env != NULL && env[0] != '\0') load_host_file(s, env, fname, HB_LIST_ALLOW);

    const char *home = getenv("HOME");
    if (home != NULL && home[0] != '\0') {
        char dir[1024];
        int n = snprintf(dir, sizeof dir, "%s/.config/freedom", home);
        if (n > 0 && (size_t)n < sizeof dir) load_host_file(s, dir, fname, HB_LIST_ALLOW);
    }

    load_host_file(s, "config", fname, HB_LIST_ALLOW);
    return s;
}

static hb_set *build_js_filter(void)          { return build_conf_allowlist("js.conf"); }
/* impersonate.conf: the THIRD opt-in signal. A host here (and in allow.conf and js.conf)
 * gets the Chrome/Firefox-consistent TLS ClientHello blend (spec/tls_impersonate.md). */
static hb_set *build_impersonate_filter(void) { return build_conf_allowlist("impersonate.conf"); }

/* The writable Freedom config dir: $FREEDOM_HOSTS_DIR if set, else ~/.config/freedom
 * (created if absent). Returns 0 on success. Mirrors the read search path so an edit
 * lands where build_host_filter/build_js_filter will read it back. */
static int freedom_write_dir(char *out, size_t cap) {
    const char *env = getenv("FREEDOM_HOSTS_DIR");
    if (env != NULL && env[0] != '\0') {
        int n = snprintf(out, cap, "%s", env);
        return (n > 0 && (size_t)n < cap) ? 0 : -1;
    }
    const char *home = getenv("HOME");
    if (home == NULL || home[0] == '\0') return -1;
    char cfg[PATH_MAX];
    int n = snprintf(cfg, sizeof cfg, "%s/.config", home);
    if (n <= 0 || (size_t)n >= sizeof cfg) return -1;
    mkdir(cfg, 0700);                            /* ignore EEXIST */
    n = snprintf(out, cap, "%s/.config/freedom", home);
    if (n <= 0 || (size_t)n >= cap) return -1;
    mkdir(out, 0700);
    return 0;
}

static void render_current(browser_window *w);  /* defined below; used by list editing */
static void load_favorites(browser_window *w);  /* defined below; refreshed after allow edit */

/* Appends the current page's host to one of the user's .conf lists (block/allow/js),
 * then reloads the in-memory filter so it applies. The host is hostile data with
 * provenance: the pure hostedit validates it fail-closed and builds the line; a
 * duplicate is skipped. Feedback goes through the status toast. */
static void add_current_host_to_list(browser_window *w, int sel) {
    const char *filename = (sel == HOSTLIST_BLOCK) ? "block.conf"
                         : (sel == HOSTLIST_ALLOW) ? "allow.conf" : "js.conf";
    w->menu_open = 0;
    char host[HE_MAX_HOST + 1];
    if (rp_host_of(browser_current_url(&w->bs), host, sizeof host) != 0) {
        browser_set_status(&w->bs, "Cannot edit lists: this page has no host.", now_ms());
        return;
    }
    char line[HE_MAX_HOST + 2];
    if (he_make_line(host, line, sizeof line) != HE_OK) {
        browser_set_status(&w->bs, "Cannot edit lists: invalid host.", now_ms());
        return;
    }
    char dir[PATH_MAX], path[PATH_MAX];
    if (freedom_write_dir(dir, sizeof dir) != 0) {
        browser_set_status(&w->bs, "Cannot edit lists: no writable config dir.", now_ms());
        return;
    }
    int pn = snprintf(path, sizeof path, "%s/%s", dir, filename);
    if (pn <= 0 || (size_t)pn >= sizeof path) {
        browser_set_status(&w->bs, "Cannot edit lists: path too long.", now_ms());
        return;
    }
    char msg[HE_MAX_HOST + 80];
    /* Skip a duplicate: read the file (bounded) and check for the host already listed. */
    size_t cur_len = 0;
    uint8_t *cur = read_file_bounded(path, 1u << 20, &cur_len);
    if (cur != NULL) {
        char *txt = (cur_len <= (1u << 20)) ? (char *)malloc(cur_len + 1) : NULL;
        int dup = 0;
        if (txt != NULL) {
            memcpy(txt, cur, cur_len);
            txt[cur_len] = '\0';
            dup = he_text_has_host(txt, host);
            free(txt);
        }
        free(cur);
        if (dup) {
            snprintf(msg, sizeof msg, "%s is already in %s.", host, filename);
            browser_set_status(&w->bs, msg, now_ms());
            return;
        }
    }
    int fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (fd < 0 || write(fd, line, strlen(line)) != (ssize_t)strlen(line)) {
        if (fd >= 0) close(fd);
        browser_set_status(&w->bs, "Cannot edit lists: write failed.", now_ms());
        return;
    }
    close(fd);
    /* Reload the affected in-memory filter so it applies immediately on the next fetch. */
    if (sel == HOSTLIST_JS) {
        hb_free(w->js_hosts);
        w->js_hosts = build_js_filter();
    } else {
        hb_free(w->hosts);
        w->hosts = build_host_filter();
        if (sel == HOSTLIST_ALLOW) load_favorites(w);  /* refresh omnibox favorites */
    }
    snprintf(msg, sizeof msg, "Added %s to %s. Reload to apply.", host, filename);
    browser_set_status(&w->bs, msg, now_ms());
    render_current(w);
}

/* Concatenates the allow.conf bodies along the same search path build_host_filter
 * uses into one string: the omnibox "favorites". Frees any previous value. Best-effort
 * (a missing/oversized file is skipped); on OOM favorites stays NULL (no suggestions). */
static void load_favorites(browser_window *w) {
    free(w->favorites);
    w->favorites = NULL;
    char *acc = (char *)malloc(1);
    if (acc == NULL) return;
    acc[0] = '\0';
    size_t len = 0;

    const char *dirs[3];
    int nd = 0;
    char home_dir[PATH_MAX];
    const char *env = getenv("FREEDOM_HOSTS_DIR");
    if (env != NULL && env[0] != '\0') dirs[nd++] = env;
    const char *home = getenv("HOME");
    if (home != NULL && home[0] != '\0') {
        int n = snprintf(home_dir, sizeof home_dir, "%s/.config/freedom", home);
        if (n > 0 && (size_t)n < sizeof home_dir) dirs[nd++] = home_dir;
    }
    dirs[nd++] = "config";

    for (int i = 0; i < nd; ++i) {
        char path[PATH_MAX];
        int n = snprintf(path, sizeof path, "%s/allow.conf", dirs[i]);
        if (n <= 0 || (size_t)n >= sizeof path) continue;
        size_t flen = 0;
        char *txt = read_file(path, &flen);
        if (txt == NULL) continue;
        if (len + flen + 2 > len && len + flen + 2 <= (1u << 20)) {
            char *na = (char *)realloc(acc, len + flen + 2);
            if (na != NULL) {
                acc = na;
                memcpy(acc + len, txt, flen);
                len += flen;
                acc[len++] = '\n';
                acc[len] = '\0';
            }
        }
        free(txt);
    }
    w->favorites = acc;
}

/* Recomputes the omnibox autocomplete suggestions for the current URL-bar text. Shown
 * only while the URL bar is focused and something is typed; otherwise cleared. Pure
 * matching: the user's own bookmarks/history first (prefs_suggest), then the
 * allow.conf favorites (he_suggest), deduplicated; no I/O. */
static void omni_refresh(browser_window *w) {
    if (!w->url_bar_focused || w->bs.url_bar_len == 0) {
        w->omni_sugg_n = 0;
        w->omni_sel = -1;
        return;
    }
    int n = prefs_suggest(&w->prefs, w->bs.url_bar, (char *)w->omni_sugg,
                          sizeof w->omni_sugg[0], OMNI_MAX_SUGG);
    if (n < OMNI_MAX_SUGG && w->favorites != NULL) {
        char more[OMNI_MAX_SUGG][HE_MAX_HOST + 1];
        int m = he_suggest(w->favorites, w->bs.url_bar, more, OMNI_MAX_SUGG);
        for (int i = 0; i < m && n < OMNI_MAX_SUGG; ++i) {
            int dup = 0;
            for (int j = 0; j < n; ++j)
                if (strcmp(w->omni_sugg[j], more[i]) == 0) { dup = 1; break; }
            if (!dup) {
                memcpy(w->omni_sugg[n], more[i], sizeof more[i]);
                n++;
            }
        }
    }
    w->omni_sugg_n = n;
    if (n == 0) w->omni_sel = -1;
    else if (w->omni_sel >= n) w->omni_sel = n - 1;
}

/* --- persisted profile (Hito 10) --- */

/* Mirrors the session's persistable choices into w->prefs and seals them to disk.
 * Called after any preference change; with a read-only profile (absent config dir,
 * foreign/corrupt prefs.bin) it is memory-only, so the session still works. */
static void profile_sync(browser_window *w) {
    w->prefs.theme_mode  = w->theme_mode;
    w->prefs.force_theme = w->force_theme;
    w->prefs.images      = w->caps.images ? 1 : 0;
    w->prefs.css         = w->caps.css ? 1 : 0;
    w->prefs.reader      = w->reader;
    w->prefs.js_mode     = (int)w->js_mode;
    w->prefs.tor         = w->net_cfg.tor_enabled;
    w->prefs.i2p         = w->net_cfg.i2p_enabled;
    w->prefs.torify      = w->net_cfg.torify_clearnet;
    w->prefs.zoom_pct    = w->zoom_pct;
    if (w->profile_rw) profile_save(&w->profile, &w->prefs);
}

/* Records a committed navigation in the persistent history (dedup + cap live in
 * prefs). Opt-out via the "Remember history" toggle; internal pages are never
 * recorded. Only URLs that already passed the pre-fetch gates reach this. */
static void remember_visit(browser_window *w, const char *url) {
    if (!w->prefs.remember_history || url == NULL) return;
    if (strncmp(url, "about:", 6) == 0) return;
    if (prefs_history_add(&w->prefs, url) == PREFS_OK && w->profile_rw)
        profile_save(&w->profile, &w->prefs);
}

/* Ctrl+B / menu: toggles a bookmark for the current page (title from the page). */
static void bookmark_toggle_current(browser_window *w) {
    const char *url = browser_current_url(&w->bs);
    if (url == NULL || url[0] == '\0' || strncmp(url, "about:", 6) == 0) {
        browser_set_status(&w->bs, "Nothing to bookmark here.", now_ms());
        redraw(w);
        return;
    }
    int added = 0;
    prefs_status ps = prefs_bookmark_toggle(&w->prefs, url, w->bs.page_title, &added);
    if (ps == PREFS_ERR_FULL) {
        browser_set_status(&w->bs, "Bookmark list is full.", now_ms());
    } else if (ps != PREFS_OK) {
        browser_set_status(&w->bs, "Cannot bookmark this URL.", now_ms());
    } else {
        if (w->profile_rw) profile_save(&w->profile, &w->prefs);
        browser_set_status(&w->bs, added ? "Bookmarked. See Bookmarks & history in the menu."
                                         : "Bookmark removed.", now_ms());
    }
    redraw(w);
}

/* Copies a proxy "host:port" into dst: if the env value is unset/empty the default is
 * used; the literal "1" also means "use the default" (a convenient on-switch). Returns
 * 1 if the env var was set non-empty (the proxy should be enabled), else 0. */
static int proxy_addr_from_env(const char *envname, const char *deflt,
                               char *dst, size_t dstsz) {
    const char *v = getenv(envname);
    int enabled = (v != NULL && v[0] != '\0');
    const char *addr = (!enabled || strcmp(v, "1") == 0) ? deflt : v;
    snprintf(dst, dstsz, "%s", addr);
    return enabled;
}

/* Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in,
 * everything off unless explicitly enabled). FREEDOM_TOR_PROXY / FREEDOM_I2P_PROXY set
 * and enable each proxy ("1" => the default port); FREEDOM_TORIFY_CLEARNET=1 routes
 * ordinary clearnet through Tor too. The addresses are always seeded with the defaults
 * so the menu toggles work even when the env vars are absent. */
static void init_net_config(browser_window *w) {
    memset(&w->net_cfg, 0, sizeof w->net_cfg);
    w->net_cfg.tor_enabled = proxy_addr_from_env("FREEDOM_TOR_PROXY", "127.0.0.1:9050",
                                                 w->tor_addr, sizeof w->tor_addr);
    w->net_cfg.i2p_enabled = proxy_addr_from_env("FREEDOM_I2P_PROXY", "127.0.0.1:4444",
                                                 w->i2p_addr, sizeof w->i2p_addr);
    const char *t = getenv("FREEDOM_TORIFY_CLEARNET");
    w->net_cfg.torify_clearnet = (t != NULL && strcmp(t, "1") == 0 && w->net_cfg.tor_enabled);
}

static int is_https_url(const char *s) {
    return strncmp(s, "https://", 8) == 0;
}

static int is_http_url(const char *s) {
    return strncmp(s, "http://", 7) == 0;
}

/* A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is
 * fetched over the network (through the overlay proxy), not read as a local file. */
static int is_overlay_http_url(const char *s) {
    return is_http_url(s) && nr_realm_allows_http(nr_classify_url(s));
}

/* Extract hostname from https://host[:port][/path]. Returns 0 on parse failure. */
static int host_from_url(const char *url, char *out, size_t outsz) {
    if (!is_https_url(url)) return 0;
    const char *p = url + 8; /* skip https:// */
    /* Optional userinfo (not expected). */
    const char *at = strchr(p, '@');
    if (at != NULL) p = at + 1;
    const char *slash = strchr(p, '/');
    const char *end = slash != NULL ? slash : p + strlen(p);
    const char *colon = memchr(p, ':', (size_t)(end - p));
    const char *host_end = colon != NULL ? colon : end;
    size_t len = (size_t)(host_end - p);
    if (len == 0 || len >= outsz) return 0;
    memcpy(out, p, len);
    out[len] = '\0';
    return 1;
}

#include "form.h"
#include "secure_fetch.h"
#include "tab.h"
#include "tls_impersonate.h"
#include "media_decoder.h"

/* Video playback functions (defined below; forward declarations for render path). */
static void video_stop(browser_window *w);
static int  video_play(browser_window *w, const char *m3u8_url);
static void *video_feeder_thread(void *arg);

/* An editable control gets a live text field; submit/button/hidden do not.
 * Checkboxes, radios, and selects are interactive (click toggles/opens) but
 * are not text-editable -- they are tracked via rebuild_inputs so clicks
 * dispatch to them, but they have no tf_field. */
static int input_is_interactive(int input_type) {
    return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD
        || input_type == PV_IN_TEXTAREA || input_type == PV_IN_CHECKBOX
        || input_type == PV_IN_RADIO || input_type == PV_IN_SELECT;
}

static int input_is_editable(int input_type) {
    return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD
        || input_type == PV_IN_TEXTAREA;
}

/* Releases the live form-control states (the array; fields are inline). */
static void free_inputs(browser_window *w) {
    free(w->inputs);
    w->inputs = NULL;
    w->input_count = 0;
    w->focused_input = -1;
}

/* Releases the decoded image surfaces of the current page and the array. */
static void free_images(browser_window *w) {
    for (size_t i = 0; i < w->image_count; ++i) {
        if (w->images[i].surface != NULL) cairo_surface_destroy(w->images[i].surface);
        free(w->images[i].href);
    }
    free(w->images);
    w->images = NULL;
    w->image_count = 0;
}

/* The decoded image for href (a doc block's URL), or NULL when it has none
 * (blocked / failed / never fetched). Matches by URL content, not block
 * identity: a worker result applied outside a fresh navigation (click, JS
 * timer) rebuilds w->doc from scratch, so the block pointer a slot was loaded
 * against no longer exists -- see the ui_image comment. */
static const ui_image *find_image(const browser_window *w, const char *href) {
    if (href == NULL) return NULL;
    for (size_t i = 0; i < w->image_count; ++i) {
        if (w->images[i].href != NULL && strcmp(w->images[i].href, href) == 0)
            return &w->images[i];
    }
    return NULL;
}

/* Releases the decoded background-image surfaces of the current page and the
 * array (2026-07-16, mirrors free_images). */
static void free_bg_images(browser_window *w) {
    for (size_t i = 0; i < w->bg_image_count; ++i) {
        if (w->bg_images[i].surface != NULL) cairo_surface_destroy(w->bg_images[i].surface);
        free(w->bg_images[i].url);
    }
    free(w->bg_images);
    w->bg_images = NULL;
    w->bg_image_count = 0;
}

/* The decoded background-image for url (a box's bg_image_url), or NULL when it
 * has none (unset / blocked / failed -- the caller paints as if there were no
 * background-image). Matches by URL content, not box identity; see find_image. */
static const ui_bg_image *find_bg_image(const browser_window *w, const char *url) {
    if (url == NULL || url[0] == '\0') return NULL;
    for (size_t i = 0; i < w->bg_image_count; ++i) {
        if (w->bg_images[i].url != NULL && strcmp(w->bg_images[i].url, url) == 0)
            return &w->bg_images[i];
    }
    return NULL;
}

/* On-screen size of a decoded image: fit to the content width, never upscaled past
 * the natural size. Returns 1 and sets dw/dh when a decoded surface exists for the
 * block; 0 otherwise (the caller draws the placeholder). The single source of truth
 * shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image_display_size(const browser_window *w, const rd_block *blk,
                              double box_w, double *dw, double *dh) {
    const ui_image *im = find_image(w, blk->href);
    if (im == NULL || im->surface == NULL || im->nat_w <= 0 || im->nat_h <= 0) return 0;
    if (box_w < 1.0) box_w = 1.0;
    double scale = ((double)im->nat_w > box_w) ? box_w / (double)im->nat_w : 1.0;
    *dw = (double)im->nat_w * scale;
    *dh = (double)im->nat_h * scale;
    return 1;
}

/* Builds the live editable state for the current doc: one entry per editable
 * control, seeded with its declared value. Aliases the doc blocks (not owned). */
static void rebuild_inputs(browser_window *w) {
    free_inputs(w);
    if (w->doc == NULL) return;
    size_t n = rd_count(w->doc);
    size_t editable = 0;
    for (size_t i = 0; i < n; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind == RD_INPUT && input_is_interactive(b->input_type)) editable++;
    }
    if (editable == 0) return;
    w->inputs = (ui_input_state *)calloc(editable, sizeof *w->inputs);
    if (w->inputs == NULL) return; /* fail closed: no editable fields, page still shows */
    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind != RD_INPUT || !input_is_interactive(b->input_type)) continue;
        ui_input_state *st = &w->inputs[k++];
        st->blk = b;
        tf_init(&st->field);
        if (b->value != NULL) tf_set(&st->field, b->value);
    }
    w->input_count = k;
}

/* The live state for a given doc block, or NULL when it has none. */
static ui_input_state *find_input_state(browser_window *w, const rd_block *blk) {
    for (size_t i = 0; i < w->input_count; ++i)
        if (w->inputs[i].blk == blk) return &w->inputs[i];
    return NULL;
}

/* Releases the structured render of the previous page (text mode resumes). The
 * hovered link and the live form controls alias the doc, so they are cleared too. */
static void clear_doc(browser_window *w) {
    free_inputs(w);
    free_images(w);
    free_bg_images(w);
    if (w->doc != NULL) { rd_free(w->doc); w->doc = NULL; }
    w->hover_href = NULL;
    w->hover_cursor = CSS_CUR_UNSET;
}

/* Replaces the cached page source. Takes ownership of html; copies top. */
static void set_cache(browser_window *w, char *html, size_t len, const char *top) {
    free(w->cur_html);
    free(w->cur_top);
    w->cur_html = html;
    w->cur_html_len = len;
    w->cur_top = (top != NULL) ? strdup(top) : NULL;
}

/* Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit. Copies row
 * by row because Cairo may use a wider stride than the tightly packed worker buffer.
 * Returns NULL on failure. */
static cairo_surface_t *surface_from_pixels(const tab_image *img) {
    if (img->data == NULL || img->width == 0 || img->height == 0) return NULL;
    cairo_surface_t *s = cairo_image_surface_create(
        CAIRO_FORMAT_ARGB32, (int)img->width, (int)img->height);
    if (cairo_surface_status(s) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(s);
        return NULL;
    }
    cairo_surface_flush(s);
    unsigned char *dst = cairo_image_surface_get_data(s);
    int dstride = cairo_image_surface_get_stride(s);
    size_t rowbytes = (size_t)img->width * 4u;
    if (dstride < 0 || (size_t)dstride < rowbytes) { cairo_surface_destroy(s); return NULL; }
    for (uint32_t y = 0; y < img->height; ++y) {
        memcpy(dst + (size_t)y * (size_t)dstride,
               img->data + (size_t)y * (size_t)img->stride, rowbytes);
    }
    cairo_surface_mark_dirty(s);
    return s;
}

/* Applies the realm route for url to cfg (proxy type + address). Returns the route;
 * NR_ROUTE_BLOCKED means the caller must NOT fetch (fail closed). */
static nr_route apply_route(const browser_window *w, const char *url, sf_config *cfg) {
    nr_route r = nr_route_for(url, w->net_cfg);
    if (r == NR_ROUTE_TOR) {
        cfg->proxy_type = SF_PROXY_SOCKS5H;
        cfg->proxy_address = w->tor_addr;
    } else if (r == NR_ROUTE_I2P) {
        cfg->proxy_type = SF_PROXY_HTTP;
        cfg->proxy_address = w->i2p_addr;
    }
    /* An overlay realm routed through its proxy may use plain http (the overlay
     * authenticates + encrypts by address). Only i2p opts in today; onion stays https. */
    if (r == NR_ROUTE_TOR || r == NR_ROUTE_I2P)
        cfg->allow_overlay_http = nr_realm_allows_http(nr_classify_url(url));
    return r;
}

/* Injects HTTP Basic Auth credentials from the window into cfg, but ONLY when the
 * request's host matches the host from which the credentials were originally
 * extracted (auth_host). This prevents credential leakage across origins when a
 * page fetches a cross-origin subresource or a redirect crosses hosts. */
static void apply_auth(const browser_window *w, const char *url, sf_config *cfg) {
    if (w->auth_host == NULL || w->auth_user == NULL || url == NULL) return;
    char host[256];
    if (rp_host_of(url, host, sizeof host) != 0) return;
    if (strcmp(host, w->auth_host) != 0) return;
    cfg->username = w->auth_user;
    cfg->password = w->auth_pass;
}

/* Downgrade reasons reported by fetch_follow_navigable via *downgraded. */
enum { DOWNGRADE_NONE = 0, DOWNGRADE_CLASSICAL_KE = 1, DOWNGRADE_ALLOWLISTED = 2 };

/* Fetches url (following redirects) under cfg's policy, applying two navigability
 * fallbacks in order of decreasing security:
 *   1) If the only obstacle is a non-PQ key exchange (SF_ERR_KEM_NOT_PQ), retry with
 *      the classical-KE fallback (TLS 1.3 + full cert validation kept). Applies to
 *      every host; *downgraded = DOWNGRADE_CLASSICAL_KE on success.
 *   2) If the host is on the user's allowlist (allowlisted != 0) and still fails,
 *      retry with the allowlist override: TLS 1.2, classical KE, weak-but-valid cert.
 *      The chain is still authenticated, so this reaches the real site over older
 *      crypto, not an impostor. *downgraded = DOWNGRADE_ALLOWLISTED on success. This
 *      is the user's sovereign escape hatch -- secure by default, not a dictatorship.
 * A non-allowlisted host that fails Freedom's standard stays fatal (fail closed).
 * cfg->policy is restored before returning. */
static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                                        sf_response *out, int *downgraded,
                                        int allowlisted) {
    *downgraded = DOWNGRADE_NONE;
    sf_status s = sf_get_follow(url, cfg, out, SF_DEFAULT_MAX_REDIRECTS);
    if (s == SF_OK) return s;

    if (s == SF_ERR_KEM_NOT_PQ) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        cfg->policy = SF_POLICY_ALLOW_CLASSICAL_KE;
        s = sf_get_follow(url, cfg, out, SF_DEFAULT_MAX_REDIRECTS);
        cfg->policy = saved;
        if (s == SF_OK) { *downgraded = DOWNGRADE_CLASSICAL_KE; return s; }
    }

    if (allowlisted) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        int saved_insecure = cfg->insecure;
        cfg->policy = SF_POLICY_ALLOWLISTED_INSECURE;
        cfg->insecure = 1;
        s = sf_get_follow(url, cfg, out, SF_DEFAULT_MAX_REDIRECTS);
        cfg->policy = saved;
        cfg->insecure = saved_insecure;
        if (s == SF_OK) { *downgraded = DOWNGRADE_ALLOWLISTED; return s; }
    }
    return s;
}

/* Like fetch_follow_navigable, but for a POST (sf_post does not follow redirects:
 * the caller inspects out->http_code/out->location). The SAME two navigability
 * fallbacks apply in the SAME order, so a POST is never sent under weaker rules than
 * a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                                      const void *body, size_t body_len,
                                      const char *content_type, sf_response *out,
                                      int *downgraded, int allowlisted) {
    *downgraded = DOWNGRADE_NONE;
    sf_status s = sf_post(url, cfg, body, body_len, content_type, out);
    if (s == SF_OK) return s;

    if (s == SF_ERR_KEM_NOT_PQ) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        cfg->policy = SF_POLICY_ALLOW_CLASSICAL_KE;
        s = sf_post(url, cfg, body, body_len, content_type, out);
        cfg->policy = saved;
        if (s == SF_OK) { *downgraded = DOWNGRADE_CLASSICAL_KE; return s; }
    }

    if (allowlisted) {
        sf_response_free(out);
        sf_policy saved = cfg->policy;
        int saved_insecure = cfg->insecure;
        cfg->policy = SF_POLICY_ALLOWLISTED_INSECURE;
        cfg->insecure = 1;
        s = sf_post(url, cfg, body, body_len, content_type, out);
        cfg->policy = saved;
        cfg->insecure = saved_insecure;
        if (s == SF_OK) { *downgraded = DOWNGRADE_ALLOWLISTED; return s; }
    }
    return s;
}

/* Host of the current page is on allow.conf (sovereign list). Used to gate page-JS
 * network access (XHR/fetch): allowed only for allow.conf AND js.conf hosts. */
static int page_host_allowlisted(const browser_window *w) {
    if (w == NULL || w->cur_top == NULL) return 0;
    char host[256];
    if (rp_host_of(w->cur_top, host, sizeof host) != 0) return 0;
    return hb_is_allowlisted(w->hosts, host);
}

/* tab_fetch_fn: the trusted parent's policy-checked subresource fetch for page XHR/fetch.
 * The worker has no network; it proxied the request here. We re-apply the SAME gates a
 * click/load gets -- https-only resolution (cross-host allowed), the host blocklist
 * (tracker filter), realm routing (fail-closed), TLS-PQ with the navigability fallbacks --
 * so a trusted page can talk to the network without ever bypassing policy. */
static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
                                 const char *body, size_t body_len,
                                 int *out_status, char **out_body, size_t *out_body_len,
                                 char **out_ctype) {
    browser_window *w = (browser_window *)vctx;
    *out_status = 0; *out_body = NULL; *out_body_len = 0; *out_ctype = NULL;
    if (w == NULL || url == NULL || w->cur_top == NULL) return -1;

    ln_result ln;
    if (ln_resolve(w->cur_top, url, &ln) != LN_OK
        || ln.action != LN_NAVIGATE || ln.kind != LN_TARGET_HTTPS) return -1;
    const char *abs = ln.target;

    char host[256];
    if (rp_host_of(abs, host, sizeof host) != 0) return -1;
    if (hb_check(w->hosts, host) == HB_BLOCK) return -1;   /* tracker/host blocklist */

    sf_config cfg = sf_config_default();
    apply_auth(w, abs, &cfg);
    if (apply_route(w, abs, &cfg) == NR_ROUTE_BLOCKED) return -1;  /* realm fail-closed */
    int allowlisted = hb_is_allowlisted(w->hosts, host), dg = 0;
    /* Subrequests to a triple-opt-in host share the page's TLS-blend identity. */
    cfg.impersonate = ti_should_impersonate(allowlisted,
        hb_is_allowlisted(w->js_hosts, host), hb_is_allowlisted(w->impersonate_hosts, host));
    sf_response resp; memset(&resp, 0, sizeof resp);
    int is_post = (method != NULL && (strcmp(method, "POST") == 0 || strcmp(method, "post") == 0));
    sf_status s = is_post
        ? fetch_post_navigable(abs, &cfg, body, body_len,
                               "application/x-www-form-urlencoded", &resp, &dg, allowlisted)
        : fetch_follow_navigable(abs, &cfg, &resp, &dg, allowlisted);
    if (s != SF_OK) { sf_response_free(&resp); return -1; }

    char *rb = (char *)malloc(resp.body_len + 1);
    if (rb == NULL) { sf_response_free(&resp); return -1; }
    if (resp.body_len != 0) memcpy(rb, resp.body, resp.body_len);
    rb[resp.body_len] = '\0';
    *out_status = (int)resp.http_code;
    *out_body = rb; *out_body_len = resp.body_len;
    *out_ctype = (resp.content_type != NULL) ? strdup(resp.content_type) : NULL;
    sf_response_free(&resp);
    return 0;
}

/* pf_fetch_fn for page images (Hito 29): resolves the raw src against the page
 * origin and fetches it under the SAME gates as the serial image loop always
 * applied (auth, realm routing fail-closed, body cap, per-host allowlist
 * override). Runs on prefetch-pool threads too: it only READS window state,
 * which is stable while the image pass runs on the GUI thread. */
static int gui_image_fetch(void *vctx, const char *method, const char *url,
                           const char *body, size_t body_len,
                           int *out_status, char **out_body, size_t *out_len,
                           char **out_ctype) {
    browser_window *w = (browser_window *)vctx;
    (void)method; (void)body; (void)body_len;
    *out_status = 0; *out_body = NULL; *out_len = 0; *out_ctype = NULL;
    if (w == NULL || url == NULL || w->cur_top == NULL) return -1;

    char abs[URL_MAX_LEN];
    if (url_resolve_https(w->cur_top, url, abs, sizeof abs) != URL_OK) return -1;

    sf_config cfg = sf_config_default();
    cfg.user_agent = tf_text(&w->ua_field);
    cfg.max_body_bytes = UI_IMAGE_MAX_BODY;
    apply_auth(w, abs, &cfg);

    /* Route the image like the page: a .onion/.i2p image with its proxy off is
     * skipped, never leaked over clearnet (fail closed). */
    if (apply_route(w, abs, &cfg) == NR_ROUTE_BLOCKED) return -1;

    int dg = 0; /* page-level toast already warns; per-image is moot */
    char ihost[256];
    int img_allow = host_from_url(abs, ihost, sizeof ihost)
                    && hb_is_allowlisted(w->hosts, ihost);
    /* EXTENSION: also check if the PAGE's host is on the allowlist. This means
     * CDN-hosted images on an allowlisted page get the same sovereign TLS fallback
     * as the page itself: without it, many websites with images on cdn.example.com
     * (which the user never explicitly allowlisted) display all images as placeholders
     * because strict TLS is the only policy tier available. The page's host already
     * passed the user's trust check, so relax the image host too. */
    if (!img_allow) {
        char phost[256];
        if (rp_host_of(w->cur_top, phost, sizeof phost) == 0
            && hb_is_allowlisted(w->hosts, phost))
            img_allow = 1;
    }
    /* An image from a triple-opt-in host uses the same TLS-blend as its page. */
    cfg.impersonate = ti_should_impersonate(img_allow,
        hb_is_allowlisted(w->js_hosts, ihost), hb_is_allowlisted(w->impersonate_hosts, ihost));
    sf_response resp;
    memset(&resp, 0, sizeof resp);
    if (fetch_follow_navigable(abs, &cfg, &resp, &dg, img_allow) != SF_OK) {
        sf_response_free(&resp);
        return -1;
    }
    char *rb = (char *)malloc(resp.body_len + 1);
    if (rb == NULL) { sf_response_free(&resp); return -1; }
    if (resp.body_len != 0) memcpy(rb, resp.body, resp.body_len);
    rb[resp.body_len] = '\0';
    *out_status = (int)resp.http_code;
    *out_body = rb;
    *out_len = resp.body_len;
    sf_response_free(&resp);
    return 0;
}

/* Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post).
 * Both MUST pass through the SAME host filter, per-host exception, allowlist override
 * and Tor/I2P realm route before any socket opens -- otherwise a POST could reach the
 * network under laxer rules than a GET, or leak a .onion lookup over clearnet. */
typedef struct fetch_prep {
    int  allowlisted;  /* host is explicitly on allow.conf (sovereign override eligible) */
    char err[768];     /* when prepare_fetch returns 0: the ready-to-show block reason */
} fetch_prep;

/* Builds cfg for url and applies the pre-fetch gates. Returns nonzero when the fetch
 * may proceed (cfg and pr->allowlisted are then set); returns 0 when the request is
 * blocked, with pr->err holding the user-facing reason (host filter or realm fail-
 * closed). Pure orchestration over already-tested validators (hostblock, net_realm). */
static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                         fetch_prep *pr) {
    memset(pr, 0, sizeof *pr);
    *cfg = sf_config_default();
    cfg->user_agent = tf_text(&w->ua_field); /* "" => SF_DEFAULT_USER_AGENT */

    char host[256];
    int have_host = host_from_url(url, host, sizeof host);

    /* Privacy by Default: consult the host filter before opening any socket. The
     * allowlist wins, so a re-enabled subdomain of a blocked domain still loads. */
    if (have_host && hb_check(w->hosts, host) == HB_BLOCK) {
        snprintf(pr->err, sizeof pr->err,
            "Blocked '%s' by the host filter.\n\n"
            "This domain (or a parent of it) is on your blocklist (block.conf).\n"
            "To see a specific subdomain, add it to allow.conf -- the allowlist\n"
            "wins over the blocklist and covers its subdomains -- then reload.\n\n"
            "Lists are read from $FREEDOM_HOSTS_DIR, ~/.config/freedom, or ./config\n"
            "in /etc/hosts format (one domain per line, or '0.0.0.0 domain').",
            host);
        return 0;
    }

    if (have_host && browser_is_exception(&w->bs, host)) {
        cfg->policy = SF_POLICY_PERMISSIVE;
        cfg->insecure = 1;
    }

    /* The user's sovereign override: a host explicitly on allow.conf may be navigated
     * below Freedom's standard (TLS 1.2, classical KE, weak cert) if strict fails. */
    pr->allowlisted = have_host && hb_is_allowlisted(w->hosts, host);

    /* Triple opt-in TLS-ClientHello blend: allow.conf AND js.conf AND impersonate.conf.
     * Drops the X25519MLKEM768 tell and matches the browser cipher order we advertise
     * (spec/tls_impersonate.md). Only shapes the handshake; authenticity is untouched. */
    cfg->impersonate = ti_should_impersonate(
        pr->allowlisted,
        have_host && hb_is_allowlisted(w->js_hosts, host),
        have_host && hb_is_allowlisted(w->impersonate_hosts, host));

    /* Socket-level anonymity routing (Tor/I2P). A .onion/.i2p host with its proxy
     * disabled is BLOCKED, never leaked over clearnet (fail closed). */
    /* HTTP Basic Auth: inject credentials scoped to the request's origin host. */
    apply_auth(w, url, cfg);

    nr_route route = apply_route(w, url, cfg);
    if (route == NR_ROUTE_BLOCKED) {
        nr_realm realm = nr_classify_url(url);
        snprintf(pr->err, sizeof pr->err,
            "Blocked '%s': it is a %s address but %s routing is not enabled.\n\n"
            "Freedom never leaks a %s lookup over the clearnet (fail closed). Enable\n"
            "%s in the menu (or set %s) and make sure a local %s proxy is running,\n"
            "then reload.",
            url, nr_realm_name(realm),
            (realm == NR_I2P) ? "I2P" : "Tor",
            nr_realm_name(realm),
            (realm == NR_I2P) ? "I2P routing" : "Tor routing",
            (realm == NR_I2P) ? "FREEDOM_I2P_PROXY" : "FREEDOM_TOR_PROXY",
            (realm == NR_I2P) ? "I2P (e.g. i2pd)" : "Tor");
        return 0;
    }
    return 1;
}

/* A network request handed to the fetch thread. It owns deep copies of every input
 * string (the window's buffers may change while the fetch runs), and is filled with
 * the result before being posted back to the main thread, which owns it from then on.
 * The thread ONLY accesses the browser_window's stream_* fields (under stream_lock)
 * and the fetch_pipe/stream_evfd for I/O -- never any other field. */
typedef struct fetch_job {
    browser_window *window;  /* for streaming progress; the thread is disciplined */
    int       write_fd;     /* fetch_pipe[1]: where the thread posts itself when done */
    uint64_t  gen;          /* navigation generation; stale results are discarded */
    int       is_post;

    /* Input (owned). cfg is rebuilt from these on the thread. */
    char         *url;
    char         *user_agent;    /* may be NULL => sf default */
    char         *proxy_address; /* may be NULL */
    sf_proxy_type proxy_type;
    int           allow_overlay_http;
    sf_policy     policy;
    int           allowlisted;
    int           impersonate;   /* TLS-ClientHello blend for triple-opt-in hosts */
    char         *username;      /* HTTP Basic Auth username (may be NULL) */
    char         *password;      /* HTTP Basic Auth password (may be NULL) */
    void         *body;          /* POST body (owned), or NULL */
    size_t        body_len;
    char         *content_type;  /* POST content type (owned), or NULL */

    /* Output (filled by the thread). */
    sf_status status;
    int       downgraded;        /* DOWNGRADE_* */
    char     *html;              /* response body (owned), or NULL */
    size_t    html_len;
    long      http_code;
    char     *location;          /* POST redirect target (owned), or NULL */
    char     *resp_ctype;        /* response Content-Type (owned), or NULL */
    char     *resp_disp;         /* response Content-Disposition (owned, hostile), or NULL */
} fetch_job;

static void fetch_job_free(fetch_job *j) {
    if (j == NULL) return;
    free(j->url);
    free(j->user_agent);
    free(j->proxy_address);
    free(j->username);
    free(j->password);
    free(j->body);
    free(j->content_type);
    free(j->html);
    free(j->location);
    free(j->resp_ctype);
    free(j->resp_disp);
    free(j);
}

/* Called by the fetch thread (~1/sec) with the downloaded body so far. Copies
 * the data to the window's thread-safe streaming buffer and signals the main
 * loop via eventfd, which triggers a progressive re-render. Runs under the
 * curl transfer thread, not the main thread: only touches stream_* fields. */
static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata) {
    browser_window *w = (browser_window *)userdata;
    if (w == NULL || w->stream_evfd < 0) return;
    /* Discard if the main thread has launched a new navigation since this fetch
     * started (net_gen was bumped). Reading net_gen from the fetch thread is safe:
     * the main thread only writes it before launching, and x86_64 reads are atomic. */
    if (w->net_gen != w->stream_launch_gen) return;
    pthread_mutex_lock(&w->stream_lock);
    free(w->stream_body);
    w->stream_body = (char *)malloc(body_len + 1);
    if (w->stream_body != NULL) {
        memcpy(w->stream_body, body, body_len);
        w->stream_body[body_len] = '\0';
    }
    w->stream_body_len = body_len;
    pthread_mutex_unlock(&w->stream_lock);
    uint64_t one = 1;
    ssize_t wr = write(w->stream_evfd, &one, sizeof one);
    (void)wr; /* signal best-effort */
}

/* Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer
 * back to the event loop. Pure with respect to the window: it reads/writes only the
 * job and writes one pointer to the pipe. */
static void *fetch_thread(void *arg) {
    fetch_job *j = (fetch_job *)arg;
    browser_window *w = j->window;

    sf_config cfg = sf_config_default();
    cfg.user_agent = j->user_agent; /* NULL => sf default */
    cfg.proxy_type = j->proxy_type;
    cfg.proxy_address = j->proxy_address;
    cfg.allow_overlay_http = j->allow_overlay_http;
    cfg.policy = j->policy;
    cfg.impersonate = j->impersonate;
    cfg.username = j->username;
    cfg.password = j->password;
    /* Enable streaming progress so the page renders before the full download
     * finishes. Only for GET (not POST); the callback copies data under the
     * window's stream_lock and signals the main loop via eventfd. */
    if (!j->is_post && w != NULL) {
        cfg.progress_cb = stream_progress_cb;
        cfg.progress_ctx = w;
    }

    sf_response resp;
    memset(&resp, 0, sizeof resp);
    sf_status s = j->is_post
        ? fetch_post_navigable(j->url, &cfg, j->body, j->body_len, j->content_type,
                               &resp, &j->downgraded, j->allowlisted)
        : fetch_follow_navigable(j->url, &cfg, &resp, &j->downgraded, j->allowlisted);

    j->status = s;
    if (s == SF_OK) {
        j->html = (char *)resp.body; resp.body = NULL; /* move ownership to the job */
        j->html_len = resp.body_len;
        j->http_code = resp.http_code;
        j->location = (resp.location != NULL) ? strdup(resp.location) : NULL;
        /* Move the headers that drive the render-vs-download decision (no extra copy). */
        j->resp_ctype = resp.content_type; resp.content_type = NULL;
        j->resp_disp  = resp.content_disposition; resp.content_disposition = NULL;
    }
    sf_response_free(&resp);

    ssize_t wr = write(j->write_fd, &j, sizeof j);
    if (wr != (ssize_t)sizeof j) fetch_job_free(j); /* pipe gone (shutdown): no reader */
    return NULL;
}

/* Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch).
 * The caller has bumped w->net_gen for this navigation; the job snapshots it. Returns
 * nonzero on success. On failure nothing is launched and the caller shows an error. */
static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
                        int allowlisted, int is_post, const void *body, size_t body_len,
                        const char *content_type) {
    if (w->fetch_pipe[1] < 0) return 0;
    fetch_job *j = (fetch_job *)calloc(1, sizeof *j);
    if (j == NULL) return 0;

    j->window = w;
    j->write_fd = w->fetch_pipe[1];
    j->gen = w->net_gen;
    /* Snapshot the launch generation so the progress callback discards its data
     * if the main thread starts a new navigation before this fetch finishes. */
    w->stream_launch_gen = w->net_gen;
    j->is_post = is_post;
    j->proxy_type = cfg->proxy_type;
    j->allow_overlay_http = cfg->allow_overlay_http;
    j->policy = cfg->policy;
    j->allowlisted = allowlisted;
    j->impersonate = cfg->impersonate;
    j->url = strdup(url);
    j->user_agent = (cfg->user_agent != NULL) ? strdup(cfg->user_agent) : NULL;
    j->proxy_address = (cfg->proxy_address != NULL) ? strdup(cfg->proxy_address) : NULL;
    j->username = (cfg->username != NULL) ? strdup(cfg->username) : NULL;
    j->password = (cfg->password != NULL) ? strdup(cfg->password) : NULL;
    if (is_post) {
        j->content_type = (content_type != NULL) ? strdup(content_type) : NULL;
        if (body_len > 0) {
            j->body = malloc(body_len);
            if (j->body != NULL) { memcpy(j->body, body, body_len); j->body_len = body_len; }
        }
    }
    /* Bail if any required copy failed (an OOM mid-setup must not fetch a truncated body). */
    if (j->url == NULL ||
        (cfg->user_agent != NULL && j->user_agent == NULL) ||
        (cfg->proxy_address != NULL && j->proxy_address == NULL) ||
        (is_post && content_type != NULL && j->content_type == NULL) ||
        (is_post && body_len > 0 && j->body == NULL)) {
        fetch_job_free(j);
        return 0;
    }

    pthread_t th;
    if (pthread_create(&th, NULL, fetch_thread, j) != 0) {
        fetch_job_free(j);
        return 0;
    }
    pthread_detach(th);
    return 1;
}

/* Fetches and decodes every allowed image of the current doc into w->images (one
 * entry per RD_IMAGE block). Each fetch re-applies the full TLS/PQ/chain policy
 * through secure_fetch (Zero Trust); decoding happens inside the still-open confined
 * worker t, so the parent never decodes hostile image bytes. A blocked, policy-
 * rejected, failed or undecodable (non-PNG/JPEG) image keeps surface == NULL and the
 * placeholder is drawn. Synchronous: image loads block this render (acceptable for v1;
 * async fetch is future work). */
/* Fetches and decodes ONE already-ALLOWed image URL (data:/file:/https -- exactly
 * the gates rd_build already applied to href) into a cairo surface. Shared by the
 * <img> loader (load_images) and the CSS background-image loader (load_bg_images,
 * 2026-07-16): from a trust standpoint the two are the identical operation --
 * bytes are hostile either way and are decoded inside the confined worker, never
 * in this process. pool/pooled may be a no-op pool (pooled=0) to always fetch
 * directly -- background-images are not prefetch-pooled in v1, the pool stays
 * scoped to <img> which is the overwhelmingly common case. On any failure
 * *out_surface is left NULL and the returned reason says where it failed (a
 * background-image caller can ignore the reason and just skip painting: a
 * blocked/failed decorative background has no natural placeholder, matching
 * real-browser behaviour, unlike an <img> which shows why via its alt text). */
static img_fail_reason fetch_decode_image(browser_window *w, tab *t, tab_fetch_fn img_fetch,
                                          void *fetch_ctx, const char *href,
                                          pf_pool *pool, int pooled,
                                          cairo_surface_t **out_surface,
                                          int *out_w, int *out_h) {
    *out_surface = NULL;
    *out_w = 0;
    *out_h = 0;
    tab_image img;
    tab_status ds;

    if (du_is_data_url(href)) {
        ds = tab_decode_image_data_url(t, href, &img);
        if (ds != TAB_OK || img.data == NULL) { tab_image_free(&img); return IMG_FAIL_DECODE; }
        *out_surface = surface_from_pixels(&img);
        img_fail_reason r = IMG_FAIL_OK;
        if (*out_surface != NULL) { *out_w = (int)img.width; *out_h = (int)img.height; }
        else r = IMG_FAIL_SURFACE;
        tab_image_free(&img);
        return r;
    }

    uint8_t *bytes = NULL;
    size_t bytes_len = 0;
    if (url_is_file(w->cur_top)) {
        const char *p = url_file_path(href);
        if (p == NULL) return IMG_FAIL_LOCAL_READ;
        bytes = read_file_bounded(p, UI_IMAGE_MAX_BODY, &bytes_len);
        if (bytes == NULL) return IMG_FAIL_LOCAL_READ;
    } else {
        int rc = -1, st = 0;
        char *bd = NULL, *ct = NULL;
        size_t bl = 0;
        if (!(pooled && pool != NULL && pf_pool_take(pool, href, &rc, &st, &bd, &bl, &ct)))
            rc = img_fetch(fetch_ctx, "GET", href, NULL, 0, &st, &bd, &bl, &ct);
        free(ct);
        if (rc != 0 || bd == NULL) { free(bd); return IMG_FAIL_FETCH; }
        bytes = (uint8_t *)bd;
        bytes_len = bl;
    }

    ds = tab_decode_image(t, bytes, bytes_len, &img);
    free(bytes);
    if (ds != TAB_OK || img.data == NULL) { tab_image_free(&img); return IMG_FAIL_DECODE; }
    *out_surface = surface_from_pixels(&img);
    img_fail_reason r = IMG_FAIL_OK;
    if (*out_surface != NULL) { *out_w = (int)img.width; *out_h = (int)img.height; }
    else r = IMG_FAIL_SURFACE;
    tab_image_free(&img);
    return r;
}

static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx) {
    if (w->doc == NULL) return;
    size_t n = rd_count(w->doc);
    size_t nimg = 0;
    for (size_t i = 0; i < n; ++i)
        if (rd_at(w->doc, i)->kind == RD_IMAGE) nimg++;
    if (nimg == 0) return;

    w->images = (ui_image *)calloc(nimg, sizeof *w->images);
    if (w->images == NULL) return; /* fail closed: no images, page still shows */

    /* Hito 29: fetch the page's network images IN PARALLEL through the same
     * per-image gates (gui_image_fetch); decoding stays serial in the confined
     * worker (one pipe). The pooled URL list is exactly what the serial loop
     * would fetch -- rd_build already applied the per-image policy -- so the
     * pool changes WHEN bytes move, never WHAT is fetched. */
    const char *purls[PF_MAX_REFS];
    size_t np = 0;
    if (w->cur_top != NULL && !url_is_file(w->cur_top)) {
        for (size_t i = 0; i < n && np < PF_MAX_REFS; ++i) {
            const rd_block *b = rd_at(w->doc, i);
            /* A data: URI's bytes are already in the document -- nothing to
             * prefetch, and it is not a real network request the pool fetcher
             * could perform. */
            if (b->kind == RD_IMAGE && b->img_decision == RDP_IMG_ALLOW
                && b->href != NULL && !du_is_data_url(b->href))
                purls[np++] = b->href;
        }
    }
    pf_pool imgpool;
    int pooled = np > 1
                 && pf_pool_start(&imgpool, purls, np, img_fetch, fetch_ctx) == 0;

    size_t k = 0;
    for (size_t i = 0; i < n; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind != RD_IMAGE) continue;
        ui_image *slot = &w->images[k++];
        slot->href = (b->href != NULL) ? strdup(b->href) : NULL;

        /* render_doc already applied the policy: only an ALLOW image with a src is
         * loaded. cur_top is the origin (https remote, or file:// local) that a
         * fetched image is resolved/routed against -- a data: URL needs no origin
         * at all (render_doc's decision for it is origin-independent too), so it
         * is exempt from this guard. */
        if (b->img_decision != RDP_IMG_ALLOW || b->href == NULL) continue;
        if (w->cur_top == NULL && !du_is_data_url(b->href)) continue;

        img_fail_reason reason = fetch_decode_image(w, t, img_fetch, fetch_ctx, b->href,
                                                     &imgpool, pooled,
                                                     &slot->surface, &slot->nat_w, &slot->nat_h);
        if (reason != IMG_FAIL_OK) {
            rd_block *rw = (rd_block *)b;
            rw->img_fail = reason;
        }
    }
    w->image_count = k;
    if (pooled) pf_pool_finish(&imgpool);
}

/* Fetches and decodes every box's resolved CSS background-image into w->bg_images
 * (2026-07-16, mirrors load_images -- see fetch_decode_image). rd_build already
 * resolved+gated bg_image_url: a box here either has an ALLOW'd absolute/data URL
 * or an empty string (unset, blocked, or off by caps.images), so there is no
 * decision to re-check, unlike load_images which still reads b->img_decision (a
 * box def carries no decision field, only the already-cleared-or-not URL). Not
 * prefetch-pooled in v1 (see fetch_decode_image); a page with many distinct
 * background-images fetches them serially, same as it would without a pool. */
static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx) {
    if (w->doc == NULL) return;
    size_t nb = rd_box_count(w->doc);
    size_t nwith = 0;
    for (size_t i = 0; i < nb; ++i)
        if (rd_box_at(w->doc, i)->bg_image_url[0] != '\0') nwith++;
    if (nwith == 0) return;

    w->bg_images = (ui_bg_image *)calloc(nwith, sizeof *w->bg_images);
    if (w->bg_images == NULL) return; /* fail closed: no backgrounds, page still shows */

    size_t k = 0;
    for (size_t i = 0; i < nb; ++i) {
        const pv_box_def *bx = rd_box_at(w->doc, i);
        if (bx->bg_image_url[0] == '\0') continue;
        if (w->cur_top == NULL && !du_is_data_url(bx->bg_image_url)) continue;
        ui_bg_image *slot = &w->bg_images[k++];
        slot->url = strdup(bx->bg_image_url);
        fetch_decode_image(w, t, img_fetch, fetch_ctx, bx->bg_image_url,
                           NULL, 0, &slot->surface, &slot->nat_w, &slot->nat_h);
    }
    w->bg_image_count = k;
}

static void do_load(browser_window *w, const char *url); /* JS navigation re-enters it */

/* Cap on consecutive JS-driven navigations (location.href=) without a settling page,
 * so a hostile redirect loop cannot pin the browser. Reset when a page settles. */
#define JS_NAV_MAX 10

/* Renders the cached page source into the page/doc using the current capabilities.
 * No network: a capability toggle (images/CSS) re-renders from cache. Does nothing
 * when there is no cached source (start/error pages stay in plain-text mode).
 *
 * allow_js_nav: on a FRESH load (not a toggle re-render) the page's JS may request a
 * navigation (location.href=/assign/replace); the worker reports it and the trusted
 * parent (tab) already gated it (ln_resolve). We then drive it through the normal
 * load path so it re-applies ALL network policy. A toggle re-render passes 0 so a
 * settled page is not re-navigated every time the user flips a switch. */
/* Resolves the JS policy for the current page's host (Secure by Default: off unless
 * the global mode is ON or the host is on the js.conf allowlist). Pure read of the
 * window state; reused by render_current_ex and the Freebug REPL's lazy worker. */
static int page_js_host_allowlisted(const browser_window *w) {
    char js_host[256];
    if (w->cur_top != NULL && host_from_url(w->cur_top, js_host, sizeof js_host))
        return hb_is_allowlisted(w->js_hosts, js_host);
    return 0;
}
static int compute_page_js(const browser_window *w) {
    return jsp_enabled(w->js_mode, page_js_host_allowlisted(w));
}

/* Trusted-host doctrine (Hito 28): a host the user declared trustworthy twice --
 * JS enabled for it AND explicitly on allow.conf -- gets the full modern
 * experience (author CSS + images on, and page-JS network access) without
 * per-session toggles. Reader mode is applied afterwards by callers and wins. */
static int page_trusted(const browser_window *w) {
    return jsp_trusted(compute_page_js(w), page_host_allowlisted(w));
}

/* Seeds document.cookie for the next load from the ephemeral network jar (trusted host
 * only); reset to none otherwise so a persistent worker never leaks stale cookies. */
static void seed_session_cookies(tab *t, int trusted, const char *url) {
    if (trusted && url != NULL && url[0] != '\0') {
        char ckhdr[4096];
        if (sf_cookie_header_for(url, ckhdr, sizeof ckhdr) > 0) {
            tab_set_cookies(t, ckhdr);
            return;
        }
    }
    tab_set_cookies(t, NULL);
}

/* Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network jar
 * one pair at a time, so JS-set session cookies reach the next request. */
static void foldback_session_cookies(const char *url, const char *jar) {
    if (url == NULL || jar == NULL) return;
    for (const char *p = jar; *p != '\0'; ) {
        while (*p == ' ' || *p == ';') ++p;
        const char *end = p;
        while (*end != '\0' && *end != ';') ++end;
        size_t plen = (size_t)(end - p);
        if (plen > 0 && plen < 700) {
            char pair[768];
            memcpy(pair, p, plen); pair[plen] = '\0';
            sf_cookie_put(url, pair);
        }
        p = end;
    }
}

/* Drops the kept-alive REPL worker and clears the (active-tab) console transcript.
 * Used when the active page changes WITHOUT a re-render (tab switch / new / close):
 * a later eval lazily rebinds the worker to the now-active page. */
static void drop_repl_worker(browser_window *w) {
    if (w->tab_worker != NULL) { tab_close(w->tab_worker); w->tab_worker = NULL; }
    fb_buffer_reset(&w->console);
    if (w->freebug != NULL) freebug_redraw(w);
}

/* Cap on OP_TICKs per page load (anti battery-drain; the shared per-page JS
 * budget already bounds the total script time). ~240 ticks at the 16 ms floor is
 * a few seconds of animation, plenty for progressive-render patterns. */
#define JS_TICKS_PER_LOAD 240

/* Schedules the next JS timer tick from the worker's reported smallest pending
 * delay (tab_page.next_timer_ms; < 0 = nothing pending). The event loop fires it
 * through the poll timeout; a 16 ms floor keeps a 0 ms chain from busy-spinning. */
static void schedule_js_tick(browser_window *w, int next_ms) {
    if (next_ms < 0 || w->js_ticks_left <= 0) {
        w->js_tick_due_ms = 0;
        return;
    }
    int delay = (next_ms < 16) ? 16 : next_ms;
    w->js_tick_elapsed = next_ms;
    w->js_tick_due_ms = now_ms() + (uint64_t)delay;
}

static void render_current_ex(browser_window *w, int allow_js_nav) {
    clear_doc(w);
    if (w->cur_html == NULL) return;
    w->js_tick_due_ms = 0;   /* a new render cancels any pending JS tick */

    /* A fresh render replaces the page: drop the previous tab's still-alive worker
     * (kept for the Freebug REPL) so a new one binds to the new page. */
    if (w->tab_worker != NULL) { tab_close(w->tab_worker); w->tab_worker = NULL; }

    /* caps.js drives the worker's <noscript> handling and inline-script execution. */
    w->caps.js = compute_page_js(w);

    tab *t = NULL;
    if (tab_open(&t) != TAB_OK) {
        browser_set_page(&w->bs, NULL, "Failed to spawn sandboxed tab.", 1);
        return;
    }

    /* Page-JS network (XHR/fetch) is granted only for a host in allow.conf AND js.conf
     * (the sovereignty boundary): the fetcher re-applies the full network policy.
     * External stylesheets (Hito 27) follow the author-styles opt-in -- or the
     * trusted-host doctrine (Hito 28) -- (GET-only at the parent gate); reader mode
     * ignores author styling, so it fetches none. */
    wc_caps wc = wc_derive((wc_input){
        .js_mode       = w->js_mode,
        .host_in_js    = page_js_host_allowlisted(w),
        .host_in_allow = page_host_allowlisted(w),
        .reader        = w->reader,
        .user_css      = w->caps.css,
        .user_images   = w->caps.images,
    });
    int trusted   = wc.net;   /* privacy caps (net/cookies) == the double-consent */
    int css_grant = wc.css;   /* external-stylesheet prefetch + author CSS apply */
    int js_grant  = wc.net;   /* external-script prefetch (was caps.js && trusted) */
    tab_set_net_allowed(t, wc.net);
    tab_set_css_allowed(t, wc.css);
    seed_session_cookies(t, wc.cookies, w->cur_top);

    /* Hito 29 (lookahead prefetch): scan the raw HTML for the external
     * stylesheets/scripts the worker will request over TAG_SUBREQ and download
     * them in parallel through the SAME policy-gated fetcher while the worker
     * parses. Protocol and policy are unchanged: a pool hit only changes WHEN
     * the bytes were fetched; a miss falls back to the serial path. Each kind
     * is queued only under the grant that would let the worker request it. */
    pf_list scanned;
    scanned.count = 0;
    pf_pool subpool;
    pf_gated_fetch gated = { gui_subresource_fetch, w, NULL };
    if ((css_grant || js_grant)
        && pf_scan(w->cur_html, w->cur_html_len, &scanned) == 0) {
        const char *urls[PF_MAX_REFS];
        size_t nurl = 0;
        for (size_t i = 0; i < scanned.count; ++i) {
            int want = (scanned.refs[i].kind == PF_STYLESHEET) ? css_grant : js_grant;
            if (want) urls[nurl++] = scanned.refs[i].url;
        }
        if (nurl > 0
            && pf_pool_start(&subpool, urls, nurl, gui_subresource_fetch, w) == 0)
            gated.pool = &subpool;
    }
    tab_set_fetcher(t, pf_pooled_fetch, &gated);

    tab_page page;
    memset(&page, 0, sizeof page);
    /* Distraction-free mode drops boilerplate in the worker (reader flag); the dark
     * theme makes the author's @media(prefers-color-scheme:dark) rules apply (auto
     * dark mode). Reader forces a clean view, so it never reports a dark preference. */
    int prefers_dark = (!w->reader && w->theme_mode == UI_THEME_DARK);
    tab_status load_ts = tab_load_full(t, w->cur_html, w->cur_html_len, w->cur_top,
                                       w->caps.js, w->reader, prefers_dark, &page);

    /* The prefetch window ends with the load: rebind the direct fetcher (the
     * kept-alive REPL worker must never point at this stack frame) and drop the
     * pool -- unconsumed results are freed, in-flight fetches are joined. */
    tab_set_fetcher(t, gui_subresource_fetch, w);
    if (gated.pool != NULL) pf_pool_finish(&subpool);
    pf_list_free(&scanned);

    if (load_ts != TAB_OK) {
        browser_set_page(&w->bs, NULL, "Failed to render page in sandbox.", 1);
        tab_close(t);
        return;
    }

    /* Fold JS-set session cookies back into the ephemeral network jar before any
     * JS-driven navigation, so a consent/redirect hop carries them (trusted host only). */
    if (trusted && page.set_cookies != NULL)
        foldback_session_cookies(w->cur_top, page.set_cookies);

    /* JS-requested navigation (location.href=/assign/replace). page.nav_url is already
     * resolved AND policy-gated by the trusted parent; we never render the transient
     * page, we navigate (re-applying ALL network policy via do_load). Capped so a
     * redirect loop cannot pin the browser; a settled page resets the chain. */
    if (allow_js_nav && page.nav_url != NULL && page.nav_url[0] != '\0') {
        if (w->js_nav_depth < JS_NAV_MAX) {
            char target[LN_MAX_TARGET];
            snprintf(target, sizeof target, "%s", page.nav_url);
            w->js_nav_depth++;
            tab_page_free(&page);
            tab_close(t);
            if (browser_navigate(&w->bs, target) == BROWSER_OK) do_load(w, target);
            return;
        }
        browser_set_status(&w->bs, "Stopped a JavaScript redirect loop.", now_ms());
    } else {
        w->js_nav_depth = 0; /* a page that did not auto-navigate ends the chain */
    }

    browser_set_page(&w->bs, page.title, page.text, 0);

    /* Trusted-host doctrine (Hito 28) + presentation-trust (2026-07-11): a host
     * explicitly on allow.conf gets author PRESENTATION (CSS + images) without
     * session toggles -- presentation is lower risk than script/network, which stay
     * double-gated (allow.conf AND js.conf) via `trusted`. Distraction-free mode
     * still ignores author styling and images (a clean reading view) and wins over
     * both; neither disturbs the user's persistent toggles: gate a local copy, not
     * w->caps. */
    rdp_caps eff = wc_render_caps(wc);

    /* The top-level URL is the https origin (per-image policy) or NULL for a local
     * file, which fails image loads closed. On failure doc stays NULL and the
     * plain-text painter still shows the extracted text. */
    rd_doc *doc = NULL;
    if (rd_build(page.view, eff, w->cur_top, &doc) == RD_OK) {
        w->doc = doc;
    }
    w->page_load_mono_ms = now_ms();  /* Phase R1: animation frame clock baseline */
    rebuild_inputs(w); /* seed live editable state for this page's controls */
    load_images(w, t, gui_image_fetch, w); /* fetch + decode allowed images in the still-open worker */
    load_bg_images(w, t, gui_image_fetch, w); /* fetch + decode allowed CSS background-images */

    /* Video playback is user-initiated (click), not auto-played. The auto-play
     * via video_play() would block the Wayland event loop with a synchronous
     * sf_get() to the .m3u8 URL, freezing the GUI. The placeholder (play
     * button + URL label) is painted by paint_video_row; clicking it triggers
     * the video frame pipeline through the normal pointer dispatch. */
    video_stop(w);
    (void)w->doc; /* keep - video detection via block scan is deferred to click */


    /* Move the page's captured console transcript into the window for Freebug, then
     * keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this
     * live page. The next render (or a tab switch) closes it. */
    fb_buffer_free(&w->console);
    w->console = page.console;
    fb_buffer_init(&page.console); /* ownership moved; tab_page_free frees an empty buffer */

    /* Real async timers: a fresh load resets the per-page tick budget and schedules
     * the first OP_TICK from the worker's reported smallest pending delay. */
    w->js_ticks_left = JS_TICKS_PER_LOAD;
    schedule_js_tick(w, page.next_timer_ms);

    tab_page_free(&page);
    w->tab_worker = t;
    if (w->freebug != NULL) freebug_redraw(w); /* refresh the console pane if open */
}

/* Re-render from cache without honoring JS navigation (capability/theme toggles). */
static void render_current(browser_window *w) {
    render_current_ex(w, 0);
}

/* Marks a request in flight and paints a frame so the spinner appears at once. The
 * fetch now runs on a worker thread, so the event loop keeps animating the spinner
 * and stays responsive until deliver_fetch_result lands the page. */
static void show_busy(browser_window *w) {
    w->loading = 1;
    redraw(w);
    if (w->display != NULL) wl_display_flush(w->display);
}

/* Replaces the page with the standard "Failed to load" diagnostic for status ss on
 * url. allowlisted tailors the hint (already retried vs. how to override). Shared by
 * the GET and POST async-result handlers so the message stays in one place. */
static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                             int allowlisted) {
    char host[256];
    const char *reason = "";
    switch (ss) {
        case SF_ERR_TLS_VERSION:  reason = "TLS version below 1.3"; break;
        case SF_ERR_KEM_NOT_PQ:   reason = "key exchange is not PQ-hybrid"; break;
        case SF_ERR_WEAK_ALGO:    reason = "weak certificate/key algorithm"; break;
        case SF_ERR_CERT_INVALID: reason = "TLS handshake/cert validation failed (site may not support TLS 1.3)"; break;
        case SF_ERR_CERT_NOT_PQ:  reason = "strict PQ signature missing"; break;
        case SF_ERR_NETWORK:      reason = "network error"; break;
        case SF_ERR_TOO_MANY_REDIRECTS: reason = "too many redirects"; break;
        default:                  reason = "fetch error"; break;
    }
    char bypass[768];
    bypass[0] = '\0';
    if (allowlisted) {
        if (host_from_url(url, host, sizeof host))
            snprintf(bypass, sizeof bypass,
                "\n\n'%s' is on your allowlist, so Freedom already retried it accepting\n"
                "TLS 1.2 and weak-but-valid crypto. This failure is real: the certificate\n"
                "is untrusted/expired, the network failed, or TLS is below 1.2.", host);
    } else if (ss == SF_ERR_TLS_VERSION || ss == SF_ERR_WEAK_ALGO
               || ss == SF_ERR_CERT_INVALID || ss == SF_ERR_CERT_NOT_PQ
               || ss == SF_ERR_KEM_NOT_PQ) {
        if (host_from_url(url, host, sizeof host))
            snprintf(bypass, sizeof bypass,
                "\n\nThis site is below Freedom's security standard. To navigate it\n"
                "anyway, add '%s' to allow.conf -- your sovereign per-host override:\n"
                "TLS 1.2, a classical key exchange, and weak-but-valid certificates\n"
                "are then accepted for this host (with a warning). The chain is still\n"
                "authenticated, so you reach the real site, not an impostor.\n"
                "Ctrl+Shift+E relaxes only a weak certificate for this session.", host);
    }
    char msg[1536];
    snprintf(msg, sizeof msg,
             "Failed to load '%s'.\nStatus %d: %s.\n\n"
             "Freedom rejects TLS < 1.3, a site (leaf) certificate with RSA\n"
             "< 3072, any SHA-1 signature in the chain, and certificates that\n"
             "fail strict validation. A host that cannot do a post-quantum key\n"
             "exchange is loaded over classical TLS 1.3 with a warning, not\n"
             "blocked.\n%s",
             url, (int)ss, reason, bypass);
    clear_doc(w);
    set_cache(w, NULL, 0, NULL);
    browser_set_page(&w->bs, NULL, msg, 1);
}

/* Starts a navigation. Network loads are ASYNCHRONOUS: prepare_fetch (pure, fast)
 * runs here, then fetch_launch hands the blocking transfer to a worker thread and we
 * return immediately -- the event loop stays responsive and the previous page stays
 * on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local files are synchronous (no network). Every call bumps net_gen so an older
 * in-flight fetch is discarded when it completes. */
static void do_load(browser_window *w, const char *url) {
    if (url == NULL) return;
    w->net_gen++;        /* new navigation: supersede any in-flight fetch */
    w->menu_open = 0;

    if (strcmp(url, "about:blank") == 0) {
        clear_doc(w);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
        w->loading = 0;
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, "Freedom", "", 0);
        return;
    }

    /* Internal bookmarks + recent-history page (Hito 10). Generated pure and
     * escaped (prefs_bookmarks_page), then rendered by the normal confined
     * pipeline like any other page -- never interpreted on the trusted side. */
    if (strcmp(url, "about:bookmarks") == 0) {
        clear_doc(w);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
        w->loading = 0;
        char *html = NULL;
        size_t hlen = 0;
        if (prefs_bookmarks_page(&w->prefs, &html, &hlen) != PREFS_OK) {
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL, "Could not build the bookmarks page.", 1);
            return;
        }
        set_cache(w, html, hlen, NULL);
        browser_set_url_bar(&w->bs, "about:bookmarks");
        render_current(w);
        return;
    }

    /* A search-engine page whose results are built only by client-side JavaScript we
     * cannot fully run (DuckDuckGo's SPA) is transparently redirected to its no-JS
     * server-rendered endpoint, which Freedom renders directly. Pure decision in
     * url_search_rewrite. The redirect is transparent: the URL bar / history keep the
     * address the user requested, so Reload and Back re-apply the same rewrite. */
    char search_rw[URL_MAX_LEN + 1];
    if (url_search_rewrite(url, search_rw, sizeof search_rw) == URL_OK) {
        url = search_rw;
    }

    if (is_https_url(url) || is_overlay_http_url(url)) {
        /* Extract HTTP Basic Auth credentials from the URL (https://user:pass@host/)
         * before the pre-fetch gates: strip them from the URL and store in the window
         * so they are available for subresource fetches (images, XHR) too. The cleaned
         * URL (without userinfo) is what flows through the rest of the pipeline.
         * The auth is scoped to the origin host so it never leaks cross-tab. */
        char clean_url[SF_MAX_URL];
        char *url_user = NULL, *url_pass = NULL;
        url_status us = url_extract_userinfo(url, clean_url, sizeof clean_url,
                                             &url_user, &url_pass);
        const char *fetch_url = (us == URL_OK) ? clean_url : url;
        char auth_host_buf[256];
        int have_fetch_host = rp_host_of(fetch_url, auth_host_buf, sizeof auth_host_buf) == 0;
        if (url_user != NULL) {
            free(w->auth_user); w->auth_user = url_user;
            free(w->auth_pass); w->auth_pass = url_pass;
            if (have_fetch_host) {
                free(w->auth_host);
                w->auth_host = strdup(auth_host_buf);
            }
        } else if (have_fetch_host && w->auth_host != NULL
                   && strcmp(auth_host_buf, w->auth_host) != 0) {
            /* Navigation to a DIFFERENT host without userinfo: clear the previous
             * auth so credentials do not persist cross-host. */
            free(w->auth_host); w->auth_host = NULL;
            free(w->auth_user); w->auth_user = NULL;
            free(w->auth_pass); w->auth_pass = NULL;
        }

        /* Pre-fetch gates (host filter, exception, allowlist, Tor/I2P route) are
         * shared with the POST path so the two can never diverge (Zero Trust). */
        sf_config cfg;
        fetch_prep pr;
        if (!prepare_fetch(w, fetch_url, &cfg, &pr)) {
            clear_doc(w);
            w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
            w->loading = 0;
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL, pr.err, 1);
            return;
        }
        if (!fetch_launch(w, fetch_url, &cfg, pr.allowlisted, 0, NULL, 0, NULL)) {
            clear_doc(w);
            w->scroll = 0.0; w->loading = 0;
            set_cache(w, NULL, 0, NULL);
            browser_set_page(&w->bs, NULL,
                "Could not start the request (out of resources).", 1);
            return;
        }
        remember_visit(w, fetch_url); /* passed the gates: persist the visit */
        show_busy(w); /* spinner on; the old page stays visible until the result lands */
        return;
    }

    /* Local file: synchronous (no network, instant). The page is given a file://
     * origin so its relative references and local images resolve (confined to the
     * document's directory) -- a local page "acts like https" for resolution. */
    clear_doc(w);
    w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
    w->loading = 0;
    const char *path = url_is_file(url) ? url_file_path(url) : url;
    size_t html_len = 0;
    char *html = read_file(path, &html_len);
    if (html == NULL) {
        char msg[256];
        snprintf(msg, sizeof msg, "Cannot read file '%.160s': %s.", path, strerror(errno));
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, msg, 1);
        return;
    }
    char origin[PATH_MAX + 16];
    const char *top = build_file_origin(url, origin, sizeof origin) ? origin : NULL;
    set_cache(w, html, html_len, top);
    remember_visit(w, url);  /* local pages count as visits too */
    render_current_ex(w, 1); /* a fresh load may honor a JS-requested navigation */
}

/* --- tabs --- */

/* Parks the active tab's live state into its slot (a shallow move: the slot and the
 * live fields briefly alias the same allocations; the live fields are overwritten
 * by tab_restore before anything is freed). */
static void tab_save(browser_window *w) {
    tab_ctx *c = &w->tab_slots[w->active_tab];
    c->bs = w->bs;
    c->doc = w->doc;
    c->caps = w->caps;
    c->scroll = w->scroll;
    c->content_total_h = w->content_total_h;
    c->inputs = w->inputs; c->input_count = w->input_count; c->focused_input = w->focused_input;
    c->images = w->images; c->image_count = w->image_count;
    c->bg_images = w->bg_images; c->bg_image_count = w->bg_image_count;
    c->cur_html = w->cur_html; c->cur_html_len = w->cur_html_len; c->cur_top = w->cur_top;
    c->loading = w->loading;
    c->hover_href = w->hover_href;
    c->hover_cursor = w->hover_cursor;
}

/* Loads the active tab's slot into the live fields (the inverse move). */
static void tab_restore(browser_window *w) {
    tab_ctx *c = &w->tab_slots[w->active_tab];
    w->bs = c->bs;
    w->doc = c->doc;
    w->caps = c->caps;
    w->scroll = c->scroll;
    w->content_total_h = c->content_total_h;
    w->inputs = c->inputs; w->input_count = c->input_count; w->focused_input = c->focused_input;
    w->images = c->images; w->image_count = c->image_count;
    w->bg_images = c->bg_images; w->bg_image_count = c->bg_image_count;
    w->cur_html = c->cur_html; w->cur_html_len = c->cur_html_len; w->cur_top = c->cur_top;
    w->loading = c->loading;
    w->hover_href = c->hover_href;
    w->hover_cursor = c->hover_cursor;
}

/* Frees the LIVE page's owned state (used when closing the foreground tab). */
static void free_live_page(browser_window *w) {
    clear_doc(w);                 /* inputs, images, doc, hover_href */
    free(w->cur_html); w->cur_html = NULL;
    free(w->cur_top);  w->cur_top = NULL;
    browser_free(&w->bs);
    memset(&w->bs, 0, sizeof w->bs);
}

/* Frees a parked (inactive) tab's owned state. */
static void tab_ctx_release(tab_ctx *c) {
    if (c->images != NULL) {
        for (size_t i = 0; i < c->image_count; ++i) {
            if (c->images[i].surface != NULL) cairo_surface_destroy(c->images[i].surface);
            free(c->images[i].href);
        }
        free(c->images);
    }
    if (c->bg_images != NULL) {
        for (size_t i = 0; i < c->bg_image_count; ++i) {
            if (c->bg_images[i].surface != NULL) cairo_surface_destroy(c->bg_images[i].surface);
            free(c->bg_images[i].url);
        }
        free(c->bg_images);
    }
    free(c->inputs);
    if (c->doc != NULL) rd_free(c->doc);
    free(c->cur_html);
    free(c->cur_top);
    browser_free(&c->bs);
    memset(c, 0, sizeof *c);
}

/* Brings tab idx to the foreground (no network: the cached doc is restored). */
static void tab_switch(browser_window *w, int idx) {
    if (idx < 0 || idx >= w->tab_count || idx == w->active_tab) return;
    /* Single-load model: leaving a tab abandons its in-flight fetch (the discarded
     * result is dropped by the generation check). Concurrent per-tab loading is future
     * work. Clear the spinner now so the parked tab does not show it on return. */
    w->net_gen++;
    w->loading = 0;
    drop_repl_worker(w); /* active page changes without a render; rebind on next eval */
    tab_save(w);
    w->active_tab = idx;
    tab_restore(w);
    w->menu_open = 0;
    w->url_bar_focused = 0;
    const char *u = browser_current_url(&w->bs);
    browser_set_url_bar(&w->bs, (u != NULL) ? u : "");
    redraw(w);
}

/* Opens a new tab after the active one and loads url (the start page when NULL). */
static void tab_new(browser_window *w, const char *url) {
    if (w->tab_count >= UI_MAX_TABS) {
        browser_set_status(&w->bs, "Tab limit reached.", now_ms());
        redraw(w);
        return;
    }
    w->loading = 0; /* clear the current tab's spinner before parking it (its fetch,
                     * if any, is abandoned: do_load below bumps the generation) */
    tab_save(w);
    int idx = w->active_tab + 1;
    for (int i = w->tab_count; i > idx; --i) w->tab_slots[i] = w->tab_slots[i - 1];
    memset(&w->tab_slots[idx], 0, sizeof w->tab_slots[idx]); /* drop the stale duplicate */
    w->tab_count++;
    w->active_tab = idx;

    /* Blank live page, then load. */
    drop_repl_worker(w); /* the previous tab's worker/console must not bleed into the new one */
    w->doc = NULL; w->hover_href = NULL; w->hover_cursor = CSS_CUR_UNSET;
    w->inputs = NULL; w->input_count = 0; w->focused_input = -1;
    w->images = NULL; w->image_count = 0;
    w->bg_images = NULL; w->bg_image_count = 0;
    w->cur_html = NULL; w->cur_html_len = 0; w->cur_top = NULL;
    w->scroll = 0.0; w->content_total_h = 0.0; w->loading = 0;
    w->caps = rdp_caps_safe();
    memset(&w->bs, 0, sizeof w->bs);
    if (browser_init(&w->bs) != BROWSER_OK) { browser_set_page(&w->bs, "Freedom", "", 0); }
    w->url_bar_focused = 1;
    do_load(w, (url != NULL) ? url : "docs/index.html");
    browser_url_bar_clear(&w->bs);
    redraw(w);
}

/* Closes tab idx. Never closes the last tab (always keeps one). */
static void uitab_close(browser_window *w, int idx) {
    if (w->tab_count <= 1 || idx < 0 || idx >= w->tab_count) return;

    if (idx == w->active_tab) {
        /* The active tab may have a fetch in flight; abandon it so its result is not
         * later painted onto whichever tab becomes active. Closing a BACKGROUND tab
         * leaves the active tab's load untouched (its generation still matches). */
        w->net_gen++;
        drop_repl_worker(w); /* the active page is going away; rebind on next eval */
        free_live_page(w);
    } else {
        tab_ctx_release(&w->tab_slots[idx]);
    }
    for (int i = idx; i < w->tab_count - 1; ++i) w->tab_slots[i] = w->tab_slots[i + 1];
    memset(&w->tab_slots[w->tab_count - 1], 0, sizeof w->tab_slots[0]);
    w->tab_count--;

    if (idx == w->active_tab) {
        if (w->active_tab >= w->tab_count) w->active_tab = w->tab_count - 1;
        tab_restore(w);
        const char *u = browser_current_url(&w->bs);
        browser_set_url_bar(&w->bs, (u != NULL) ? u : "");
        w->menu_open = 0; w->url_bar_focused = 0;
    } else if (idx < w->active_tab) {
        w->active_tab--;
    }
    redraw(w);
}

/* Width of one tab: the strip (minus the trailing + button) split evenly, clamped to
 * a readable maximum and a grabbable floor (many tabs shrink, they never vanish). */
static double tab_width(const browser_window *w) {
    double avail = (double)w->width - UI_TAB_NEW_W;
    if (avail < 1.0) avail = 1.0;
    double tw = avail / (double)w->tab_count;
    if (tw > UI_TAB_MAX_W) tw = UI_TAB_MAX_W;
    if (tw < 36.0) tw = 36.0;
    return tw;
}

/* X of the "new tab" (+) button: right after the last tab, clamped to the reserved
 * slot at the right edge. */
static double newtab_x(const browser_window *w) {
    double after = (double)w->tab_count * tab_width(w);
    double maxx = (double)w->width - UI_TAB_NEW_W;
    return (after < maxx) ? after : maxx;
}

/* Title shown on a tab: the page title, else the URL, else a placeholder. */
static const char *tab_title(const browser_window *w, int i) {
    const browser_state *bs = (i == w->active_tab) ? &w->bs : &w->tab_slots[i].bs;
    if (bs->page_title != NULL && bs->page_title[0] != '\0') return bs->page_title;
    if (bs->url_bar[0] != '\0') return bs->url_bar;
    return "New tab";
}

/* --- painting --- */

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x, double *menu_x);

/* Top of the tab strip: directly under the client-side titlebar (or at the surface
 * top under server-side decorations). */
static double tabbar_top(const browser_window *w) {
    return w->use_csd ? UI_TITLEBAR_H : 0.0;
}

/* Top of the toolbar: under the tab strip, which is always reserved. The whole
 * content area derives from this, so adding the strip reflows everything below it. */
static double toolbar_top(const browser_window *w) {
    return tabbar_top(w) + UI_TABBAR_H;
}

/* The content area rectangle below the toolbar, in surface coordinates. The
 * single source of truth for both painting and click hit-testing so they cannot
 * drift apart. */
static void content_geometry(const browser_window *w, double *top, double *height) {
    double t = toolbar_top(w) + UI_TOOLBAR_H;
    double h = (double)w->height - t - 2.0 * w->theme.content_margin;
    if (h < 1.0) h = 1.0;
    *top = t;
    *height = h;
}

/* Width available to page content: the window width minus the left/right margins
 * and the always-reserved scrollbar gutter. The single source of truth shared by
 * the painter and the click/link hit-tests so the laid-out lines and the hit
 * geometry cannot drift. */
/* Horizontal page margin (left edge to content, and symmetric right gutter). Equals
 * the base content_margin, except in distraction-free mode it widens to center the
 * content in a fixed reading column (UI_READER_COLUMN_W). This is HORIZONTAL only --
 * the vertical margin stays w->theme.content_margin (see content_geometry), so reader
 * centering never shrinks the vertical viewport. */
static double content_margin_x(const browser_window *w) {
    double m = w->theme.content_margin;
    if (w->reader) {
        double avail = (double)w->width - UI_SCROLLBAR_W;
        double margin = (avail - UI_READER_COLUMN_W) / 2.0;
        if (margin > m) m = margin;
    }
    return m;
}

static double content_width(const browser_window *w) {
    double cw = (double)w->width - 2.0 * content_margin_x(w) - UI_SCROLLBAR_W;
    if (cw < 1.0) cw = 1.0;
    return cw;
}

/* Geometry of the vertical scrollbar in surface coordinates, plus the current
 * thumb position. Returns 0 (and leaves outputs untouched) when the content fits
 * and no scrollbar is needed. content_total_h is the height cached by the last
 * paint; the track spans the content area down to the bottom edge. */
static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
                             double *track_h, double *thumb_y, double *thumb_h) {
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    double total = w->content_total_h;
    if (content_h <= 0.0 || total <= content_h) return 0;

    double trh = (double)w->height - content_top;
    if (trh < 1.0) trh = 1.0;
    double thh = trh * (content_h / total);
    if (thh < UI_SCROLLBAR_MIN) thh = UI_SCROLLBAR_MIN;
    if (thh > trh) thh = trh;

    double max_scroll = total - content_h;
    double frac = (max_scroll > 0.0) ? (w->scroll / max_scroll) : 0.0;
    if (frac < 0.0) frac = 0.0;
    if (frac > 1.0) frac = 1.0;

    *track_x = (double)w->width - UI_SCROLLBAR_W;
    *track_y = content_top;
    *track_h = trh;
    *thumb_h = thh;
    *thumb_y = content_top + frac * (trh - thh);
    return 1;
}

/* Maps the current pointer Y (less the grab offset) to a scroll offset while the
 * thumb is being dragged, then repaints. No-op when there is no scrollbar. */
static void scrollbar_drag_to(browser_window *w) {
    double tx, ty, trh, thy, thh;
    if (!scrollbar_metrics(w, &tx, &ty, &trh, &thy, &thh)) return;
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    double max_scroll = w->content_total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double travel = trh - thh;
    double frac = (travel > 0.0) ? ((w->ptr_y - w->scroll_grab_dy) - ty) / travel : 0.0;
    if (frac < 0.0) frac = 0.0;
    if (frac > 1.0) frac = 1.0;
    w->scroll = frac * max_scroll;
    redraw(w);
}

/* Paints the scrollbar track and thumb. The thumb highlights while hovered or
 * dragged, the same affordance the toolbar buttons and links get. */
static void draw_scrollbar(cairo_t *cr, const browser_window *w) {
    double tx, ty, trh, thy, thh;
    if (!scrollbar_metrics(w, &tx, &ty, &trh, &thy, &thh)) return;
    const ui_theme *th = &w->theme;

    set_rgb(cr, th->scrollbar_track);
    cairo_rectangle(cr, tx, ty, UI_SCROLLBAR_W, trh);
    cairo_fill(cr);

    int hot = w->dragging_scroll
           || (w->ptr_x >= tx && w->ptr_x <= tx + UI_SCROLLBAR_W
               && w->ptr_y >= thy && w->ptr_y <= thy + thh);
    set_rgb(cr, hot ? th->scrollbar_thumb_hot : th->scrollbar_thumb);
    cairo_rectangle(cr, tx + UI_SCROLLBAR_PAD, thy + UI_SCROLLBAR_PAD,
                    UI_SCROLLBAR_W - 2.0 * UI_SCROLLBAR_PAD, thh - 2.0 * UI_SCROLLBAR_PAD);
    cairo_fill(cr);
}

/* Interactive-resize edge for a pointer near the window border (CSD only). Returns
 * an xdg_toplevel resize edge, or 0 (NONE) away from the edges. The top edge is
 * excluded: it belongs to the titlebar (move / window buttons). */
static uint32_t resize_edge_at(const browser_window *w, double x, double y) {
    double m = UI_RESIZE_MARGIN;
    int left   = x < m;
    int right  = x > (double)w->width - m;
    int bottom = y > (double)w->height - m;
    /* The side edges live in the page margins; keep them out of the titlebar and
     * toolbar rows so the chrome buttons stay clickable. */
    if (y < toolbar_top(w) + UI_TOOLBAR_H) { left = 0; right = 0; }
    if (bottom && left)  return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT;
    if (bottom && right) return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT;
    if (bottom) return XDG_TOPLEVEL_RESIZE_EDGE_BOTTOM;
    if (left)   return XDG_TOPLEVEL_RESIZE_EDGE_LEFT;
    if (right)  return XDG_TOPLEVEL_RESIZE_EDGE_RIGHT;
    return XDG_TOPLEVEL_RESIZE_EDGE_NONE;
}

static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *close_x) {
    *close_x = w->width - UI_WIN_BTN_W;
    *max_x   = w->width - 2 * UI_WIN_BTN_W;
    *min_x   = w->width - 3 * UI_WIN_BTN_W;
}

/* The reload button sits as the third left chrome button (after back/forward), at a
 * fixed x; callers that need it derive it here so the layout stays single-sourced. */
#define UI_RELOAD_X (UI_BTN_W * 2.0)

static void toolbar_rects(const browser_window *w,
                          double *back_x, double *fwd_x,
                          double *url_x, double *url_w,
                          double *go_x, double *menu_x) {
    *back_x = 0.0;
    *fwd_x  = UI_BTN_W;
    *menu_x = (double)w->width - UI_BTN_W;
    *go_x   = *menu_x - UI_BTN_W;
    *url_x  = UI_BTN_W * 3.0 + UI_MARGIN;   /* after back, forward, reload */
    *url_w  = *go_x - *url_x - UI_MARGIN;
    if (*url_w < 20.0) *url_w = 20.0;
}

/* Which toolbar button (if any) is at (px, py). Shared by the hover highlight and
 * the cursor shape so they cannot drift from the click hit-test. */
static ui_hot toolbar_button_at(const browser_window *w, double px, double py) {
    if (w->menu_open) return UI_HOT_NONE;
    double ttop = toolbar_top(w);
    if (py < ttop || py >= ttop + UI_TOOLBAR_H) return UI_HOT_NONE;
    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    if (px >= menu_x) return UI_HOT_MENU;
    if (px >= go_x && px < menu_x) return UI_HOT_GO;
    if (px >= UI_RELOAD_X && px < UI_RELOAD_X + UI_BTN_W) return UI_HOT_RELOAD;
    if (px >= fwd_x && px < fwd_x + UI_BTN_W) return UI_HOT_FWD;
    if (px >= back_x && px < back_x + UI_BTN_W) return UI_HOT_BACK;
    return UI_HOT_NONE;
}

/* A hovered button is "actionable" (gets the hand cursor) when clicking it would
 * do something: Go/menu always, Back/Forward only when there is history. */
static int hot_actionable(const browser_window *w, ui_hot hot) {
    switch (hot) {
        case UI_HOT_GO: case UI_HOT_MENU: case UI_HOT_RELOAD: return 1;
        case UI_HOT_BACK: return browser_can_back(&w->bs);
        case UI_HOT_FWD:  return browser_can_forward(&w->bs);
        default: return 0;
    }
}

/* The options-menu panel rectangle (below the gear button), and its per-item row
 * height. The single source of truth for drawing and hit-testing the panel. */
static void menu_panel_rect(const browser_window *w, double *x, double *y,
                            double *width, double *height, double *item_h) {
    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    *width  = UI_MENU_W;
    *x      = menu_x + UI_BTN_W - UI_MENU_W; /* right-aligned under the gear */
    if (*x < 0.0) *x = 0.0;
    *y      = toolbar_top(w) + UI_TOOLBAR_H;
    *item_h = UI_MENU_ITEM_H;
    /* Checkbox rows, then the User-Agent section (label + editable box). */
    *height = 2.0 * UI_MENU_PAD + (double)UI_MENU_COUNT * UI_MENU_ITEM_H
            + UI_MENU_LABEL_H + UI_MENU_INPUT_H + UI_MENU_PAD;
}

/* The editable User-Agent box rectangle inside the options panel. The single
 * source of truth for drawing and hit-testing the field. */
static void ua_box_rect(const browser_window *w, double *x, double *y,
                        double *width, double *height) {
    double mx, my, mw, mh, ih;
    menu_panel_rect(w, &mx, &my, &mw, &mh, &ih);
    *x      = mx + UI_MENU_PAD;
    *width  = mw - 2.0 * UI_MENU_PAD;
    *y      = my + UI_MENU_PAD + (double)UI_MENU_COUNT * UI_MENU_ITEM_H + UI_MENU_LABEL_H;
    *height = UI_MENU_INPUT_H;
}

static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered) {
    if (s == NULL) return;
    cairo_text_extents_t te;
    cairo_text_extents(cr, s, &te);
    double dx = centered ? x - te.width / 2.0 : x;
    cairo_move_to(cr, dx, y);
    cairo_show_text(cr, s);
}

/* ===================== structured content layout + paint ==================== */
/*
 * The content area paints an rd_doc (the same structured document the headless
 * mode prints): headings, paragraphs and inline links flow word-by-word into
 * lines, the image-tracking warning is a banner, and each image is a bordered
 * placeholder showing its render_policy decision. Layout runs once per frame into
 * transient arrays so vertical scrolling can be a smooth pixel offset over the
 * real total height. This is visual-only (no headless test) but compiles under
 * the same hardened flags.
 */

typedef struct rc_frag {
    double      x, width, font_size;
    int         bold, italic, underline, strike, overline;
    ui_rgb      color;
    const char *text;     /* slice into a rd_block text (not owned) */
    size_t      len;
    const char *href;     /* link target (aliases the rd_block href, not owned); NULL if not a link */
    dom_node_id node_id;  /* element that produced this fragment (DOM_NODE_NONE if none) */
    int         block_id; /* owning box-def index (-1 if none), for hover-cursor lookup */
    /* Author text-presentation extensions (Hito 23b-6), applied by the painter and
     * consistently by the layout measure. Defaults (no author style): family 0
     * (sans), transform 0 (none), letter_spacing 0, valign_dy 0, shadow_color -1
     * (no shadow), opacity -1 (opaque). */
    int         family;       /* css_font_family */
    int         transform;    /* css_text_transform */
    double      letter_spacing;/* px between clusters */
    double      valign_dy;    /* baseline shift px (sub/super) */
    int         shadow_dx, shadow_dy, shadow_color;
    int         opacity;      /* 0..100, or -1 */
    /* Author text-decoration sub-properties (Hito 23b-...): color overrides the
     * current fg for the line stroke (-1 = use fragment color), style is the
     * css_text_decoration_style (0 unset -> solid), thickness is px (-1 unset -> 1.0).
     * Applied by the painter, no effect on the layout measure. */
    int         deco_color;   /* 0xRRGGBB, or -1 (use fragment color) */
    int         deco_style;   /* css_text_decoration_style */
    int         deco_thick;   /* px, or -1 (use default 1.0) */
    /* 2026-07-10 text-extension batch. font_variant applies small-caps to the
     * fragment (uppercase + scaled font when set; baked at flow time so the
     * layout/paint stay consistent). */
    int         font_variant; /* css_font_variant (small-caps etc.) */
} rc_frag;

typedef enum rc_rowkind { RC_TEXT = 0, RC_IMAGE, RC_INPUT, RC_VIDEO } rc_rowkind;

typedef struct rc_row {
    rc_rowkind      kind;
    double          top, height, ascent;
    size_t          first, count;  /* RC_TEXT: frag range */
    int             banner;        /* RC_TEXT: draw the notice background */
    int             bg_rgb;        /* author background-color packed 0xRRGGBB, or -1 */
    double          bg_w;          /* background width; 0 = full content width */
    double          x_off;         /* extra horizontal offset (flex/grid column), 0 normally */
    int             align;         /* author text-align (css_align), 0 = left/unset */
    const rd_block *blk;           /* RC_IMAGE: source image block */
    int             hidden;        /* visibility:hidden on this row's box (or an ancestor):
                                     * space is still reserved, painting is skipped */
} rc_row;

/* One painted block box (Hito 23b-8 Step C): a border-box rectangle in layout space
 * with its author decoration, painted behind the rows it encloses. Built from a
 * maximal run of rd_blocks sharing one block_id. block_id is stamped at open_box
 * time so position_doc can map an in-flow rc_box back to its pv_box_def (and the
 * resolved out-of-flow rect to the right ancestor). */
typedef struct rc_box {
    double x, top, w, h;   /* border-box rect (layout space) */
    int    block_id;       /* pv_box_def index, -1 if none */
    int    bord_tw, bord_rw, bord_bw, bord_lw;
    int    bord_ts, bord_rs, bord_bs, bord_ls;
    int    bord_tc, bord_rc, bord_bc, bord_lc;
    int    radius;
    int    bsh_dx, bsh_dy, bsh_blur, bsh_spread, bsh_color, bsh_inset;
    int    outline_w, outline_style, outline_color;
    int    outline_offset;  /* px outset from the border edge; CSS_LEN_UNSET = 0 */
    int    bg_rgb;
    int    hidden;   /* visibility:hidden on this box (or an ancestor): geometry (h/w)
                       * is still resolved, decoration painting is skipped */
    /* 2026-07-10 author vertical dimensions: a fixed height/width sets the box's
     * size when the content is smaller (height) or wider (min-width); a max-height
     * caps the painted height. 0 = unset. Applied at open_box time; aspect_ratio
     * (num/den x1000) sizes a box that has one dimension only. */
    int    box_h, box_min_h, box_max_h, box_min_w;
    int    aspect_num, aspect_den;
    /* linear-gradient background (2026-07-11): stop count (0 = none), CSS degrees,
     * packed stops. Wins over bg_rgb when set. */
    int    grad_n, grad_angle;
    int    grad_c[4];
    /* background-image size/repeat (2026-07-16). css_bg_size/css_bg_repeat, 0
     * unset (natural size / CSS default "repeat"). The decoded surface itself is
     * looked up separately by the painter (ui_bg_image, keyed by pv_box_def
     * pointer) -- not carried here, unlike the color/gradient fields above,
     * because it is an owned decoded resource, not a small resolved value. */
    int    bg_size, bg_repeat;
} rc_box;

typedef struct rc_layout {
    rc_frag *frags; size_t nfrag, capfrag;
    rc_row  *rows;  size_t nrow,  caprow;
    rc_box  *boxes; size_t nbox,  capbox;
    double   total_h;
    /* Stage 2: out-of-flow positioned boxes, in stacking order (z_index ASC,
     * doc_order ASC). Allocated as a fixed-size array bounded by BT_MAX_POSITIONED;
     * npositioned is the number of valid entries (out-of-flow blocks painted on
     * top of the in-flow content). z_index < 0 entries are skipped by the painter
     * in v1 (would need a two-pass painter to paint behind in-flow). */
    bt_positioned positioned[BT_MAX_POSITIONED];
    size_t        npositioned;
    /* 2026-07-10 tab expansion in <pre> needs a buffer that lives as long as
     * the layout: the rc_frag.text slice is just an offset into one of these
     * owned buffers (heap-allocated, freed by rc_free). Without this, a
     * tab-expanded slice from a local stack buffer would dangle by the time
     * the painter runs. Bounded by a total cap to keep the layout bounded. */
    char  **text_bufs;       /* array of owned heap buffers */
    size_t  n_text_bufs;     /* count of valid entries */
    size_t  cap_text_bufs;   /* allocated slots */
} rc_layout;

/* Box engine (Hito 23b-8 Step D): one entry of the open-box stack. A box's content
 * rect (inner_left/inner_w) is the coordinate context its children (text or nested
 * boxes) are placed in; bl/br/pb/bb are its borders/bottom-padding reserved geometry;
 * box_idx points at the rc_box rect being measured. */
typedef struct rc_open_box {
    int    block_id;
    size_t box_idx;
    double bl, br, pb, bb;
    double inner_left, inner_w;
} rc_open_box;

/* Max box-nesting depth the painter composes (anti-DoS; deeper boxes are clamped to
 * the innermost open box, so a pathological tree never overflows the stack). */
#define RC_BOX_STACK_MAX 16

typedef struct rc_state {
    double cur_top, pending_gap, pen_x, line_asc, line_desc;
    double prev_bottom;  /* bottom margin (px) of the last block, for CSS margin collapsing */
    double indent_px;    /* left indent of the current line (list nesting), applied as row x_off */
    int    line_open, banner;
    int    bg_rgb;       /* current block's author background-color, or -1 */
    double bg_w;         /* background width for the current rows; 0 = full content width */
    int    align;        /* current block's author text-align (css_align), 0 = left/unset */
    int    line_scale;   /* current block's author line-height percent, 0 = use theme spacing */
    double pending_indent;/* author text-indent (px) to apply to the next opened line, 0 normally */
    int    nowrap;       /* current block's white-space suppresses line wrapping */
    int    break_words;  /* current block's word-break/overflow-wrap allows a mid-word split */
    int    text_overflow;/* current block's text-overflow (css_text_overflow) */
    /* 2026-07-10 text-extensions. white_space is the full css_white_space (flow_text
     * uses it to know when to expand tabs in <pre>); tab_size is the author override
     * (0 -> 8). The rest are read from rc_ext in flow_text and not cached here. */
    int    white_space;  /* css_white_space of the current block */
    int    tab_size;     /* author tab-size of the current block (0 -> 8) */
    size_t line_first;
    /* Box engine (Hito 23b-8 Step D) visibility: hidden_from is 0 (not hidden) or the
     * box_stack depth (1-based) at which a visibility:hidden box was opened -- every
     * row/box created while hidden_from != 0 is marked hidden (space reserved, paint
     * skipped). Cleared when that box closes (box_depth drops back below it). */
    int    hidden_from;
    /* Box engine (Hito 23b-8 Step D): the STACK of currently-open block boxes, from
     * outermost (index 0) to innermost. A run is laid out inside the innermost box's
     * content rect; a child box nests inside its parent's, so a box is no longer split
     * when a child interrupts it. box_depth 0 = no open box (default flat flow). */
    rc_open_box box_stack[RC_BOX_STACK_MAX];
    int         box_depth;
} rc_state;

static void rc_free(rc_layout *L) {
    free(L->frags);
    free(L->rows);
    free(L->boxes);
    /* Free every owned text buffer (2026-07-10: tab-expanded <pre> slices). */
    for (size_t i = 0; i < L->n_text_bufs; ++i) free(L->text_bufs[i]);
    free(L->text_bufs);
}

static rc_box *rc_add_box(rc_layout *L) {
    if (L->nbox == L->capbox) {
        size_t nc = L->capbox ? L->capbox * 2 : 8;
        rc_box *g = (rc_box *)realloc(L->boxes, nc * sizeof *g);
        if (g == NULL) return NULL;
        L->boxes = g; L->capbox = nc;
    }
    rc_box *b = &L->boxes[L->nbox++];
    b->block_id = -1;  /* stamped by open_box; -1 = no associated pv_box_def */
    return b;
}

static rc_frag *rc_add_frag(rc_layout *L) {
    if (L->nfrag == L->capfrag) {
        size_t nc = L->capfrag ? L->capfrag * 2 : 64;
        rc_frag *g = (rc_frag *)realloc(L->frags, nc * sizeof *g);
        if (g == NULL) return NULL;
        L->frags = g; L->capfrag = nc;
    }
    return &L->frags[L->nfrag++];
}

static rc_row *rc_add_row(rc_layout *L) {
    if (L->nrow == L->caprow) {
        size_t nc = L->caprow ? L->caprow * 2 : 32;
        rc_row *g = (rc_row *)realloc(L->rows, nc * sizeof *g);
        if (g == NULL) return NULL;
        L->rows = g; L->caprow = nc;
    }
    return &L->rows[L->nrow++];
}

/* Maps an author font-family bucket (css_font_family) to a Cairo toy-font family.
 * The engine matches no exact families, only the generic groups. */
static const char *family_face(int family) {
    switch (family) {
        case CSS_FF_SERIF:   return "serif";
        case CSS_FF_MONO:    return "monospace";
        case CSS_FF_CURSIVE: return "cursive";
        case CSS_FF_FANTASY: return "fantasy";
        default:             return "sans-serif";  /* CSS_FF_SANS / unset */
    }
}

/* The font last selected by content_font. measure_slice/draw_slice shape with this
 * descriptor via HarfBuzz (text_shape); the painter always selects the font before
 * measuring/drawing a slice, so this single-threaded shadow is always current. The
 * toy face is still selected so the fallback path and direct cairo_show_text users
 * (chrome labels) keep working. */
static tsh_font g_cur_font;
static double    g_cur_px;

static void content_font(cairo_t *cr, double size, int bold, int italic, int family) {
    cairo_select_font_face(cr, family_face(family),
                           italic ? CAIRO_FONT_SLANT_ITALIC : CAIRO_FONT_SLANT_NORMAL,
                           bold ? CAIRO_FONT_WEIGHT_BOLD : CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, size);
    g_cur_font.family = family;
    g_cur_font.bold = bold;
    g_cur_font.italic = italic;
    g_cur_px = size;
}

/* Sets the source color, applying an author opacity (0..100) as an alpha when set
 * (-1 = fully opaque). Used for author text and its shadow. */
static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity) {
    if (opacity >= 0 && opacity < 100)
        cairo_set_source_rgba(cr, c.r, c.g, c.b, (double)opacity / 100.0);
    else
        cairo_set_source_rgb(cr, c.r, c.g, c.b);
}

/* Bytes in the UTF-8 cluster starting at s[0] (1 for a stray/continuation byte),
 * clamped to n. */
static size_t utf8_clen(const char *s, size_t n) {
    unsigned char c = (unsigned char)s[0];
    size_t l = (c < 0x80) ? 1 : ((c >> 5) == 0x6) ? 2 :
               ((c >> 4) == 0xe) ? 3 : ((c >> 3) == 0x1e) ? 4 : 1;
    return (l > n) ? n : l;
}

/* Copies one cluster s[0,cl) into out (>= 4 bytes), applying text-transform. ASCII
 * case mapping only (a multi-byte cluster passes through). first marks the word's
 * first cluster (for capitalize). Returns cl. */
static size_t xform_cluster(const char *s, size_t cl, int transform, int first, char *out) {
    memcpy(out, s, cl);
    if (cl == 1) {
        char c = out[0];
        if (transform == CSS_TT_UPPERCASE && c >= 'a' && c <= 'z') out[0] = (char)(c - 32);
        else if (transform == CSS_TT_LOWERCASE && c >= 'A' && c <= 'Z') out[0] = (char)(c + 32);
        else if (transform == CSS_TT_CAPITALIZE && first && c >= 'a' && c <= 'z')
            out[0] = (char)(c - 32);
    }
    return cl;
}

/* Advance (px) of a text slice in the current content font. Shapes with HarfBuzz
 * (text_shape) when the backend is available, otherwise falls back to the Cairo
 * toy API (byte-identical to the pre-Hito-25 renderer). */
static double measure_slice(cairo_t *cr, const char *s, size_t n) {
    double adv = tsh_measure(&g_cur_font, g_cur_px, s, n);
    if (adv >= 0.0) return adv;
    char buf[UI_SLICE_MAX];
    if (n >= sizeof buf) n = sizeof buf - 1;
    memcpy(buf, s, n);
    buf[n] = '\0';
    cairo_text_extents_t te;
    cairo_text_extents(cr, buf, &te);
    return te.x_advance;
}

/* Draws a text slice at (x, baseline) in the current content font/source. Shapes
 * with HarfBuzz when available; otherwise the Cairo toy API. Mirrors measure_slice
 * so layout and paint stay consistent for the same slice. */
static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n) {
    if (tsh_draw(cr, &g_cur_font, g_cur_px, x, baseline, s, n) == TSH_OK) return;
    char buf[UI_SLICE_MAX];
    if (n >= sizeof buf) n = sizeof buf - 1;
    memcpy(buf, s, n);
    buf[n] = '\0';
    cairo_move_to(cr, x, baseline);
    cairo_show_text(cr, buf);
}

/* True if a fragment needs the per-cluster path (text-transform other than
 * none/unset, or a non-zero letter-spacing). Otherwise the fast whole-slice path is
 * byte-identical to the pre-Hito-23b-6 renderer. */
static int frag_styled(const rc_frag *f) {
    return f->transform > CSS_TT_NONE || f->letter_spacing != 0.0;
}

/* Advance (px) of a fragment's text under its text-transform + letter-spacing. The
 * current Cairo font must already be selected. Mirrors styled_draw exactly so layout
 * and paint stay consistent. */
static double styled_advance(cairo_t *cr, const rc_frag *f) {
    if (!frag_styled(f)) return measure_slice(cr, f->text, f->len);
    double adv = 0.0;
    int first = 1;
    char cl[8];
    for (size_t i = 0; i < f->len; first = 0) {
        size_t clen = utf8_clen(f->text + i, f->len - i);
        size_t ol = xform_cluster(f->text + i, clen, f->transform, first, cl);
        adv += measure_slice(cr, cl, ol) + f->letter_spacing;
        i += clen;
    }
    return adv;
}

/* Draws a fragment's text starting at (x, baseline) under its text-transform +
 * letter-spacing. The current Cairo font/source must already be set. */
static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f) {
    if (!frag_styled(f)) {
        draw_slice(cr, x, baseline, f->text, f->len);
        return;
    }
    double px = x;
    int first = 1;
    char cl[8];
    for (size_t i = 0; i < f->len; first = 0) {
        size_t clen = utf8_clen(f->text + i, f->len - i);
        size_t ol = xform_cluster(f->text + i, clen, f->transform, first, cl);
        draw_slice(cr, px, baseline, cl, ol);
        px += measure_slice(cr, cl, ol) + f->letter_spacing;
        i += clen;
    }
}

static void block_style(const ui_theme *th, const rd_block *b,
                        double *size, int *bold, int *italic, int *underline, ui_rgb *color) {
    *bold = 0; *italic = 0; *underline = 0; *size = th->body_font; *color = th->text;
    if (b->kind == RD_HEADING) {
        int lv = (b->heading_level >= 1 && b->heading_level <= UI_HEADING_LEVELS)
                 ? b->heading_level : 1;
        *size = th->body_font * th->heading_scale[lv];
        *bold = 1; *color = th->heading;
    } else if (b->kind == RD_LINK) {
        *color = th->link; *underline = 1;
    } else if (b->kind == RD_NOTICE) {
        *color = th->notice_text;
    }
    /* Inline emphasis (b/strong/i/em) layers on top of the block's base style: a
     * heading stays bold, a bold link stays a link. */
    if (b->bold) *bold = 1;
    if (b->italic) *italic = 1;
}

/* Vertical margins (px) of a block from the user-agent box model (box_style),
 * resolved against the block's own font size (em -> px). The user-agent notice has
 * no HTML tag, so it keeps the theme's paragraph gap as a separator and does not
 * regress. The single place that turns "what tag is this" into block spacing. */
static void block_margins(const ui_theme *th, const rd_block *b,
                          double *top_px, double *bottom_px) {
    const char *tag = rd_block_tag(b);
    if (tag == NULL) { *top_px = th->paragraph_gap; *bottom_px = th->paragraph_gap; return; }
    bx_box box = bx_default_for_tag(tag);
    double size; int bold, italic, underline; ui_rgb color;
    block_style(th, b, &size, &bold, &italic, &underline, &color);
    /* An author margin-top/bottom (px, only with caps.css) overrides the UA margin;
     * PV_LEN_UNSET keeps the UA value. */
    *top_px = (b->box_mt != PV_LEN_UNSET) ? (double)b->box_mt : box.margin.top * size;
    *bottom_px = (b->box_mb != PV_LEN_UNSET) ? (double)b->box_mb : box.margin.bottom * size;
}

static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th) {
    if (!s->line_open) return;
    /* Author line-height (percent of the natural line box) replaces the theme's
     * default spacing when set; render_doc gated it behind caps.css (0 when off). */
    double spacing = (s->line_scale > 0) ? (double)s->line_scale / 100.0 : th->line_spacing;
    double h = (s->line_asc + s->line_desc) * spacing;
    rc_row *r = rc_add_row(L);
    if (r != NULL) {
        r->kind = RC_TEXT; r->top = s->cur_top; r->height = h; r->ascent = s->line_asc;
        r->first = s->line_first; r->count = L->nfrag - s->line_first;
        r->banner = s->banner; r->bg_rgb = s->bg_rgb; r->bg_w = s->bg_w;
        r->x_off = s->indent_px;
        r->align = s->align; r->blk = NULL;
        r->hidden = (s->hidden_from != 0);
    }
    s->cur_top += h;
    s->line_open = 0; s->pen_x = 0; s->line_asc = 0; s->line_desc = 0;
    s->line_first = L->nfrag;
}

static void open_line(rc_layout *L, rc_state *s) {
    if (s->line_open) return;
    if (L->nrow > 0) s->cur_top += s->pending_gap;  /* no leading gap at the very top */
    s->pending_gap = 0;
    s->line_open = 1;
    /* Author text-indent (px) offsets the first line a block opens; cleared so wrapped
     * lines start at 0. Default pending_indent 0 -> identical to before. */
    s->pen_x = s->pending_indent;
    s->pending_indent = 0;
    s->line_first = L->nfrag;
}

/* Author text-presentation extensions for a block, derived from its rd_block (already
 * gated by caps.css upstream) and handed to flow_text. */
typedef struct rc_ext {
    int    family;        /* css_font_family */
    int    transform;     /* css_text_transform */
    double letter_spacing;/* px between clusters */
    double word_spacing;  /* px added to each inter-word gap */
    double valign_dy;     /* baseline shift px (sub/super) */
    int    shadow_dx, shadow_dy, shadow_color;
    int    opacity;       /* 0..100, or -1 */
    /* Author text-decoration sub-properties (per-fragment). Same semantics as on
     * rc_frag. */
    int    deco_color, deco_style, deco_thick;
    /* 2026-07-10 text-extension batch. tab_size 0 -> 8 (CSS default) at the
     * pre block; font_variant is applied via uppercase transform (v1 small-caps
     * approximation: see flow_text); list_style_pos CSS_LP_INSIDE means the
     * list marker is part of the line (no extra first-line indent). */
    int    tab_size;       /* 0 unset */
    int    direction;      /* css_direction (carried; layout is still LTR) */
    int    font_variant;   /* css_font_variant */
    int    list_style_pos; /* css_list_pos */
} rc_ext;

/* Emits one fragment at the current pen position, advancing it. Shared by the
 * whole-word path and the word-break split path in flow_text. */
static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                           const char *text, size_t len, double width, double size,
                           int bold, int italic, int underline, int strike, int overline,
                           ui_rgb color, const char *href, dom_node_id node_id,
                           int block_id, const rc_ext *x) {
    rc_frag *f = rc_add_frag(L);
    if (f != NULL) {
        f->x = s->pen_x; f->width = width; f->font_size = size;
        f->bold = bold; f->italic = italic; f->underline = underline;
        f->strike = strike; f->overline = overline; f->color = color;
        f->text = text; f->len = len; f->href = href; f->node_id = node_id;
        f->block_id = block_id;
        f->family = x->family; f->transform = x->transform;
        f->letter_spacing = x->letter_spacing; f->valign_dy = x->valign_dy;
        f->shadow_dx = x->shadow_dx; f->shadow_dy = x->shadow_dy;
        f->shadow_color = x->shadow_color; f->opacity = x->opacity;
        f->deco_color = x->deco_color; f->deco_style = x->deco_style;
        f->deco_thick = x->deco_thick;
        f->font_variant = x->font_variant;
    }
    s->pen_x += width;
    if (fe->ascent  > s->line_asc)  s->line_asc  = fe->ascent;
    if (fe->descent > s->line_desc) s->line_desc = fe->descent;
}

/* U+2026 HORIZONTAL ELLIPSIS, UTF-8. Static storage: safe for a zero-copy rc_frag.text
 * (like every other frag, which aliases the source rd_block text). */
static const char FLOW_ELLIPSIS[] = "\xE2\x80\xA6";

/* Places the words of text into the current inline line, wrapping at content_w.
 * href tags every fragment produced (NULL for non-link runs) so a later hit-test
 * can recover the click target without re-walking the document. node_id tags the
 * originating element for JS click dispatch (Stage 4 dispatcher); block_id tags the
 * owning box (for the hover-cursor lookup), -1 if none.
 *
 * word-break/overflow-wrap (s->break_words): a single word wider than the WHOLE
 * line (not just the remaining space -- a normal wrap already handles that) is
 * split at UTF-8 cluster boundaries into pieces that each fit, instead of
 * overflowing the box edge unbroken.
 *
 * text-overflow: ellipsis (s->text_overflow, only meaningful with s->nowrap: this
 * engine does not paint overflow:hidden clipping yet, so nowrap is the only signal
 * that the line is meant to stay on one row): once a word would push the line past
 * content_w, the line is truncated at the cluster boundary that fits, an ellipsis
 * is appended, and the rest of this call's text is dropped (single-line
 * truncation; text from a LATER sibling run on the same visual line, if any, is a
 * known v1 gap -- see spec/css.md). */
static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
                      const char *text, double size, int bold, int italic, int underline,
                      int strike, int overline,
                      ui_rgb color, double content_w, const char *href,
                      dom_node_id node_id, int block_id, const rc_ext *x) {
    /* 2026-07-10: author font-variant: small-caps is approximated by rendering the
     * text in uppercase (v1: a real implementation would draw lowercase at 0.7x in
     * the small-caps font variant, but no Cairo toy backend exposes a small-caps
     * face). The fragment's text_transform becomes uppercase, and the stored
     * transform on the rc_frag is updated so layout measure + paint agree. */
    int xform = x->transform;
    if (x->font_variant == CSS_FV_SMALL_CAPS && xform == CSS_TT_UNSET)
        xform = CSS_TT_UPPERCASE;

    /* 2026-07-10: author tab-size inside a <pre>-like block. Tabs become that many
     * spaces (the CSS default of 8 is used when the property is unset, so a
     * `<pre>` with no tab-size still aligns the way browsers do). The expansion
     * happens into a heap-allocated buffer owned by the layout (rc_layout.text_bufs),
     * so the rc_frag.text slice into it stays valid past this function. */
    const char *src = text;
    size_t src_len = strlen(text);
    if (s->white_space == CSS_WS_PRE || s->white_space == CSS_WS_PRE_WRAP ||
        s->white_space == CSS_WS_PRE_LINE) {
        int tab_n = (x->tab_size > 0) ? x->tab_size : 8;
        if (tab_n > 32) tab_n = 32;            /* anti-DoS: cap a hostile tab-size */

        /* Heap-allocate the expanded text: the slice (f->text) must stay
         * valid past this function, and the rc_frag.text pointer is "not
         * owned" (it points into one of the layout's owned buffers).
         * Bounded to src_len * (tab_n <= 32) + 1 -- an over-long pre line
         * falls back to the raw text (tabs become font glyphs). */
        size_t need = src_len * tab_n + 1;
        if (need < src_len + 1) need = src_len + 1;  /* overflow guard */
        char *expanded = (char *)malloc(need);
        if (expanded == NULL) return;
        size_t o = 0;
        for (size_t j = 0; j < src_len; ++j) {
            if (text[j] == '\t') {
                for (int k = 0; k < tab_n && o + 1 < need; ++k)
                    expanded[o++] = ' ';
            } else {
                expanded[o++] = text[j];
            }
        }
        expanded[o] = '\0';
        if (L->n_text_bufs == L->cap_text_bufs) {
            size_t nc = L->cap_text_bufs ? L->cap_text_bufs * 2 : 8;
            char **g = (char **)realloc(L->text_bufs, nc * sizeof *g);
            if (g == NULL) { free(expanded); return; }
            L->text_bufs = g;
            L->cap_text_bufs = nc;
        }
        L->text_bufs[L->n_text_bufs++] = expanded;
        src = expanded;
        src_len = o;
    }

    content_font(cr, size, bold, italic, x->family);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double space_w = measure_slice(cr, " ", 1) + x->word_spacing;
    if (space_w < 0.0) space_w = 0.0;

    size_t i = 0, n = src_len;
    while (i < n) {
        while (i < n && text[i] == ' ') ++i;
        size_t ws = i;
        while (i < n && text[i] != ' ') ++i;
        size_t wl = i - ws;
        if (wl == 0) break;

        open_line(L, s);
        /* A leading inter-word gap only between words already on this line (not at a
         * line start), so an author text-indent does not gain a phantom space. */
        int line_has_frag = (L->nfrag > s->line_first);
        double adv = line_has_frag ? space_w : 0.0;

        rc_frag probe = (rc_frag){ 0 };
        probe.text = src + ws; probe.len = wl;
        probe.transform = xform; probe.letter_spacing = x->letter_spacing;
        double ww = styled_advance(cr, &probe);

        if (line_has_frag && !s->nowrap && s->pen_x + adv + ww > content_w) {
            flush_line(L, s, th);
            open_line(L, s);
            adv = 0.0;
            line_has_frag = 0;
        }

        if (s->nowrap && s->text_overflow == CSS_TO_ELLIPSIS &&
            s->pen_x + adv + ww > content_w) {
            double ell_w = measure_slice(cr, FLOW_ELLIPSIS, sizeof FLOW_ELLIPSIS - 1);
            double budget = content_w - s->pen_x - adv - ell_w;
            s->pen_x += adv;
            size_t take = 0;
            double acc = 0.0;
            size_t p = ws;
            while (budget > 0.0 && p < ws + wl) {
                size_t clen = utf8_clen(src + p, (ws + wl) - p);
                rc_frag cprobe = (rc_frag){ 0 };
                cprobe.text = src + p; cprobe.len = clen;
                cprobe.transform = xform; cprobe.letter_spacing = x->letter_spacing;
                double cw = styled_advance(cr, &cprobe);
                if (acc + cw > budget) break;
                acc += cw; p += clen; take += clen;
            }
            if (take > 0)
                flow_emit_frag(L, s, &fe, src + ws, take, acc, size, bold, italic,
                               underline, strike, overline, color, href, node_id,
                               block_id, x);
            flow_emit_frag(L, s, &fe, FLOW_ELLIPSIS, sizeof FLOW_ELLIPSIS - 1, ell_w,
                           size, bold, italic, underline, strike, overline, color,
                           href, node_id, block_id, x);
            return;
        }

        if (s->break_words && !line_has_frag && ww > content_w && content_w > 0.0) {
            s->pen_x += adv;
            size_t p = ws;
            while (p < ws + wl) {
                size_t chunk_start = p;
                double chunk_w = 0.0;
                while (p < ws + wl) {
                    size_t clen = utf8_clen(src + p, (ws + wl) - p);
                    rc_frag cprobe = (rc_frag){ 0 };
                    cprobe.text = src + p; cprobe.len = clen;
                    cprobe.transform = xform; cprobe.letter_spacing = x->letter_spacing;
                    double cw = styled_advance(cr, &cprobe);
                    if (chunk_w + cw > content_w && p > chunk_start) break;
                    chunk_w += cw; p += clen;
                }
                flow_emit_frag(L, s, &fe, src + chunk_start, p - chunk_start, chunk_w,
                               size, bold, italic, underline, strike, overline, color,
                               href, node_id, block_id, x);
                if (p < ws + wl) { flush_line(L, s, th); open_line(L, s); }
            }
            continue;
        }

        s->pen_x += adv;
        flow_emit_frag(L, s, &fe, src + ws, wl, ww, size, bold, italic, underline,
                       strike, overline, color, href, node_id, block_id, x);
    }
}

/* Flows one text/link/notice block into L at content_w using state s. The caller
 * sets s->bg_rgb (the block's author background, or -1) beforehand; the foreground
 * color and link/heading styling are derived here. */
static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                            rc_state *s, const ui_theme *th, const rd_block *b,
                            double content_w) {
    double size; int bold, italic, underline; ui_rgb color;
    block_style(th, b, &size, &bold, &italic, &underline, &color);
    if (!w->force_theme && b->fg_rgb >= 0) color = rgb_from_packed(b->fg_rgb);
    /* Author font-size scales the block's base size (composes with a heading's own
     * scale); render_doc already gated this behind caps.css (0 when off). */
    if (b->font_scale > 0) size = size * (double)b->font_scale / 100.0;
    /* Author text-align travels on the rows this block flushes (paint centers/right-
     * aligns each line); render_doc gated it behind caps.css (0 when off). */
    s->align = b->text_align;
    s->line_scale = b->line_scale;
    /* Author text-decoration overrides the base underline (e.g. `a {text-decoration:
     * none}` drops the link underline) and adds line-through/overline. -1 means the
     * author set none (render_doc gated it off, or no rule), so the base style stands. */
    int strike = 0, overline = 0;
    if (b->text_decoration != -1) {
        underline = (b->text_decoration & CSS_DECO_UNDERLINE) ? 1 : 0;
        strike    = (b->text_decoration & CSS_DECO_LINE_THROUGH) ? 1 : 0;
        overline  = (b->text_decoration & CSS_DECO_OVERLINE) ? 1 : 0;
    }
    const char *href = (b->kind == RD_LINK) ? b->href : NULL;

    /* Author text-presentation extensions (gated by caps.css upstream; no-effect
     * defaults otherwise). vertical-align sub/super shrinks the run and shifts its
     * baseline; text-indent applies to the first line this block opens; white-space
     * nowrap/pre suppresses wrapping. */
    rc_ext x = (rc_ext){ 0 };
    x.family = b->font_family;
    x.transform = b->text_transform;
    x.letter_spacing = (b->letter_spacing != PV_LEN_UNSET) ? (double)b->letter_spacing : 0.0;
    x.word_spacing = (b->word_spacing != PV_LEN_UNSET) ? (double)b->word_spacing : 0.0;
    x.shadow_dx = b->shadow_dx; x.shadow_dy = b->shadow_dy; x.shadow_color = b->shadow_color;
    x.opacity = b->opacity;
    /* Author text-decoration sub-properties: -1/0/UNSET already set by the
     * (rc_ext){ 0 } init, just lift from the block. */
    x.deco_color = b->text_decoration_color;
    x.deco_style = b->text_decoration_style;
    x.deco_thick = b->text_decoration_thickness;
    /* 2026-07-10 text-extension batch. */
    x.tab_size = b->tab_size;
    x.direction = b->direction;
    x.font_variant = b->font_variant;
    x.list_style_pos = b->list_style_pos;
    if (b->valign == CSS_VA_SUB)        { x.valign_dy =  size * 0.18; size *= 0.83; }
    else if (b->valign == CSS_VA_SUPER) { x.valign_dy = -size * 0.34; size *= 0.83; }

    s->nowrap = (b->white_space == CSS_WS_NOWRAP || b->white_space == CSS_WS_PRE);
    s->break_words = (b->word_break == CSS_WB_BREAK);
    s->text_overflow = b->text_overflow;
    s->white_space = b->white_space;  /* 2026-07-10: page_view fills the pre UA default (CSS_WS_PRE) upstream */
    s->tab_size = b->tab_size;        /* 0 -> 8 at expand time */
    if (!s->line_open && b->text_indent != PV_LEN_UNSET)
        s->pending_indent = (double)b->text_indent;

    if (b->kind == RD_NOTICE) {
        s->banner = 1;
        flow_text(cr, L, s, th, b->text, size, bold, italic, underline, strike, overline,
                  color, content_w, href, b->node_id, b->block_id, &x);
        flush_line(L, s, th);
        s->banner = 0;
    } else {
        flow_text(cr, L, s, th, b->text, size, bold, italic, underline, strike, overline,
                  color, content_w, href, b->node_id, b->block_id, &x);
    }
    s->nowrap = 0;
    s->break_words = 0;
    s->text_overflow = 0;
}

/* Lays a contiguous range [start,end) of blocks that share one author flex/grid
 * container into equal columns, then appends the positioned rows to L and advances
 * s->cur_top. Each block is one item (basic: items are not grouped). Column geometry
 * and row packing come from box_tree/flex_layout (already tested); this only flows
 * the text and translates the rows. Visual-only structure, applied by default
 * (decoupled from caps.css, which gates only author colors). A run that falls
 * outside the engine's range degrades to plain vertical flow. */
/* Stage 3: true iff any block in [start, end) declares a flex per-item property
 * (grow/shrink/basis/order/align-self). Without one -- and without a container-level
 * flex-wrap/align-items (checked by the caller) -- the equal-columns path stays in
 * effect (byte-identical default). */
static int container_has_flex_items(const rd_doc *doc, size_t start, size_t end) {
    for (size_t k = start; k < end; ++k) {
        const rd_block *bk = rd_at(doc, k);
        if (bk->flex_grow >= 0 || bk->flex_shrink >= 0 ||
            bk->flex_basis != CSS_LEN_UNSET || bk->flex_order != CSS_LEN_UNSET ||
            (bk->flex_align_self != CSS_AK_UNSET && bk->flex_align_self != CSS_AK_AUTO))
            return 1;
    }
    return 0;
}

/* Maps a css_align_kw (align-items/align-self) to the box_tree cross-axis
 * alignment it drives. BASELINE/AUTO/UNSET/space-* (align-content only, never
 * seen here) all fall back to START; STRETCH is v1-approximated as START too
 * (see spec/box_engine.md) -- box_tree.c's BT_ALIGN_STRETCH already does that. */
static int css_align_to_bt(int align_kw) {
    switch (align_kw) {
        case CSS_AK_CENTER:  return BT_ALIGN_CENTER;
        case CSS_AK_END:     return BT_ALIGN_END;
        case CSS_AK_STRETCH: return BT_ALIGN_STRETCH;
        default:              return BT_ALIGN_START;
    }
}

static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                             rc_state *s, const ui_theme *th, double content_w,
                             const rd_doc *doc, size_t start, size_t end) {
    size_t nruns = end - start;
    const rd_block *head = rd_at(doc, start);
    int is_grid = (head->cont_display == BX_DISPLAY_GRID);

    /* Group consecutive runs into ITEMS by cont_item: inline fragments of one
     * direct child of the container share an ordinal and flow together in one
     * cell ("the <a>free</a> web" is ONE item, not three columns). A run without
     * an ordinal (-1: synthesized runs, old wire) is its own item — collected
     * table cells carry one ordinal per cell, so cells never merge. */
    size_t gstart[BT_MAX_CHILDREN + 1];
    size_t g = 0;
    int grp_overflow = 0;
    {
        int prev_item = -1;
        int have_prev = 0;
        for (size_t k = start; k < end; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (!have_prev || bk->cont_item < 0 || bk->cont_item != prev_item) {
                if (g >= BT_MAX_CHILDREN) { grp_overflow = 1; break; }
                gstart[g++] = k;
            }
            prev_item = bk->cont_item;
            have_prev = 1;
        }
        gstart[g] = end;
    }
    size_t ncols = is_grid ? (size_t)head->cont_cols : g;
    if (ncols < 1) ncols = 1;

    if (nruns == 0 || grp_overflow || ncols > BT_MAX_CHILDREN) {
        /* Too many items for the grid engine: degrade to plain flow, but honor each
         * run's block_break so a table that overflows the engine still lays out one
         * ROW per line (page_view marks the first cell of every <tr>) instead of one
         * continuous blob. This is the Hacker News case (>128 cells). */
        for (size_t k = start; k < end; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (bk->block_break) flush_line(L, s, th);
            s->bg_rgb = (!w->force_theme) ? bk->bg_rgb : -1;
            flow_text_block(cr, w, L, s, th, bk, content_w);
        }
        return;
    }

    /* Stage 3: flex-direction column stacks the items vertically at full width
     * (the row engine below would squeeze them into n side-by-side columns —
     * exactly wrong for vertical navs). The container gap becomes vertical space
     * between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visual order: last item at top, first at bottom. */
    if (!is_grid && (head->flex_direction == CSS_FD_COLUMN ||
                     head->flex_direction == CSS_FD_COLUMN_REVERSE)) {
        size_t row_start[BT_MAX_CHILDREN], row_count[BT_MAX_CHILDREN];
        double item_h[BT_MAX_CHILDREN], cum_off[BT_MAX_CHILDREN];
        double base = s->cur_top + ((L->nrow > 0) ? s->pending_gap : 0.0);
        s->pending_gap = 0;
        double cur = base;
        for (size_t j = 0; j < g; ++j) {
            flush_line(L, s, th);
            if (j > 0 && head->cont_gap > 0)
                cur += (double)head->cont_gap;
            s->cur_top = cur;
            cum_off[j] = cur;
            size_t sr = L->nrow;
            for (size_t k = gstart[j]; k < gstart[j + 1]; ++k) {
                const rd_block *bk = rd_at(doc, k);
                if (k > gstart[j] && bk->block_break) flush_line(L, s, th);
                s->bg_rgb = (!w->force_theme) ? bk->bg_rgb : -1;
                flow_text_block(cr, w, L, s, th, bk, content_w);
            }
            flush_line(L, s, th);
            row_start[j] = sr;
            row_count[j] = L->nrow - sr;
            item_h[j] = s->cur_top - cur;
            cur = s->cur_top;
        }
        if (head->flex_direction == CSS_FD_COLUMN_REVERSE) {
            double total_h = s->cur_top - base;
            double rev = base + total_h;
            for (size_t j = 0; j < g; ++j) {
                rev -= item_h[j];
                double delta = rev - cum_off[j];
                for (size_t r = row_start[j]; r < row_start[j] + row_count[j]; ++r)
                    L->rows[r].top += delta;
                rev -= (double)((head->cont_gap > 0) ? head->cont_gap : 0);
            }
            s->cur_top = base + total_h;
        }
        return;
    }

    flush_line(L, s, th);
    double base_top = s->cur_top + ((L->nrow > 0) ? s->pending_gap : 0.0);
    s->pending_gap = 0;

    /* Stage 3: per-item flex. pos_of[j] is the layout slot of document item j —
     * the identity map unless `order` reorders the main axis (stable insertion
     * sort: equal order keeps document order, matching CSS). An item's flex
     * values are read from its first run (fragments share them). */
    int use_flex = !is_grid &&
        (container_has_flex_items(doc, start, end) ||
         head->cont_wrap == CSS_FW_WRAP || head->cont_wrap == CSS_FW_WRAP_REVERSE ||
         head->cont_align_items != CSS_AK_UNSET);
    size_t pos_of[BT_MAX_CHILDREN];
    for (size_t j = 0; j < g; ++j) pos_of[j] = j;
    if (use_flex) {
        size_t slot[BT_MAX_CHILDREN];   /* slot[j] = document item at layout slot j */
        for (size_t j = 0; j < g; ++j) slot[j] = j;
        for (size_t j = 1; j < g; ++j) {
            size_t it = slot[j];
            const rd_block *bi = rd_at(doc, gstart[it]);
            int oi = (bi->flex_order != CSS_LEN_UNSET) ? bi->flex_order : 0;
            size_t m = j;
            while (m > 0) {
                const rd_block *bj = rd_at(doc, gstart[slot[m - 1]]);
                int oj = (bj->flex_order != CSS_LEN_UNSET) ? bj->flex_order : 0;
                if (oj <= oi) break;
                slot[m] = slot[m - 1];
                --m;
            }
            slot[m] = it;
        }
        for (size_t j = 0; j < g; ++j) pos_of[slot[j]] = j;
        /* flex-direction: row-reverse reverses the visual order of flex items.
         * After the order sort, the slot array has the visual order (slot[0] =
         * leftmost item). Reversing pos_of maps each document item to its reversed
         * layout slot (item 0 → rightmost, last item → leftmost). */
        if (head->flex_direction == CSS_FD_ROW_REVERSE) {
            for (size_t j = 0; j < g; ++j)
                pos_of[j] = g - 1 - pos_of[j];
        }
    }

    bt_node kids[BT_MAX_CHILDREN];
    bt_node root;
    memset(&root, 0, sizeof root);
    memset(kids, 0, sizeof kids[0] * g);
    root.gap = (double)head->cont_gap;
    root.justify = (fx_justify)head->cont_justify;
    root.children = kids;
    root.child_count = g;
    /* row-gap (author `row-gap`, distinct from `gap`/column-gap): applies to both
     * the flex-wrap cross axis and grid row spacing below. Unset (-1) leaves
     * has_row_gap at its zero-init 0, so `gap` keeps serving both axes exactly as
     * before this property existed. */
    if (head->cont_row_gap >= 0) {
        root.has_row_gap = 1;
        root.row_gap = (double)head->cont_row_gap;
    }
    if (use_flex) {
        /* An item without an explicit basis takes an equal share of the line
         * (basis auto == content size needs text measured before layout; the
         * equal share is the flat model's stand-in and matches the default path).
         * With wrap, this share is still content_w/g (not per-line): an accurate
         * per-line auto-basis needs measuring content before layout, so wrapping
         * items that want real auto-sizing should set an explicit basis/width --
         * the common case in practice (cards, nav items with a fixed min width). */
        root.display = BX_DISPLAY_FLEX;
        root.wrap = (head->cont_wrap == CSS_FW_WRAP || head->cont_wrap == CSS_FW_WRAP_REVERSE) ? 1 : 0;
        root.wrap_reverse = (head->cont_wrap == CSS_FW_WRAP_REVERSE) ? 1 : 0;
        double share = (content_w - (double)head->cont_gap * (double)(g - 1)) / (double)g;
        if (share < 1.0) share = 1.0;
        for (size_t j = 0; j < g; ++j) {
            const rd_block *bk = rd_at(doc, gstart[j]);
            bt_node *kid = &kids[pos_of[j]];
            kid->display = BX_DISPLAY_BLOCK;
            kid->grow = (bk->flex_grow >= 0) ? (double)bk->flex_grow / 100.0 : 0.0;
            kid->shrink = (bk->flex_shrink >= 0) ? (double)bk->flex_shrink / 100.0 : 1.0;
            kid->basis = (bk->flex_basis >= 0) ? (double)bk->flex_basis : share;
            int akw = (bk->flex_align_self != CSS_AK_UNSET && bk->flex_align_self != CSS_AK_AUTO)
                      ? bk->flex_align_self : head->cont_align_items;
            kid->align = css_align_to_bt(akw);
            kid->min_main = 1.0;
        }
    } else {
        root.display = BX_DISPLAY_GRID;   /* flex row == grid with g columns, one row */
        root.grid_cols = ncols;
        /* Sized tracks + column spans (2026-07-11): only a real author grid carries
         * them (the flex-degrade row keeps equal columns and 1-cell items). */
        if (is_grid) {
            root.grid_track = head->cont_col_w;
            root.grid_ntrack = PV_GRID_TRACKS;
        }
        for (size_t j = 0; j < g; ++j) {
            kids[j].display = BX_DISPLAY_BLOCK;
            if (is_grid) {
                const rd_block *bk = rd_at(doc, gstart[j]);
                kids[pos_of[j]].grid_span = bk->grid_span;
            }
        }
    }

    /* First pass: column widths (heights still 0). */
    if (bt_layout(&root, content_w) != BT_OK) {
        for (size_t k = start; k < end; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (bk->block_break) flush_line(L, s, th);
            s->bg_rgb = (!w->force_theme) ? bk->bg_rgb : -1;
            flow_text_block(cr, w, L, s, th, bk, content_w);
        }
        return;
    }

    /* Flow each item into L at its column width; record its row range and height.
     * A multi-run item flows its fragments inline, breaking a line only where a
     * run inside the item starts a new block. */
    size_t row_start[BT_MAX_CHILDREN], row_count[BT_MAX_CHILDREN];
    for (size_t j = 0; j < g; ++j) {
        rc_state si;
        memset(&si, 0, sizeof si);
        bt_node *kid = &kids[pos_of[j]];
        double cw = (kid->w < 1.0) ? 1.0 : kid->w;
        /* The item's author background paints its own column rect (zebra rows in
         * data tables via tr:nth-child(even), header bands...). */
        si.bg_w = cw;
        size_t sr = L->nrow;
        for (size_t k = gstart[j]; k < gstart[j + 1]; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (k > gstart[j] && bk->block_break) flush_line(L, &si, th);
            si.bg_rgb = (!w->force_theme) ? bk->bg_rgb : -1;
            flow_text_block(cr, w, L, &si, th, bk, cw);
        }
        flush_line(L, &si, th);
        row_start[j] = sr;
        row_count[j] = L->nrow - sr;
        kid->content_h = si.cur_top;
    }

    /* Second pass: final row packing + y now that the heights are known. */
    if (bt_layout(&root, content_w) != BT_OK) return;

    /* Translate each item's rows into its column rectangle. */
    for (size_t j = 0; j < g; ++j) {
        const bt_node *kid = &kids[pos_of[j]];
        for (size_t r = row_start[j]; r < row_start[j] + row_count[j]; ++r) {
            L->rows[r].top += base_top + kid->y;
            L->rows[r].x_off = kid->x;
        }
    }
    s->cur_top = base_top + root.h;
}

/* A border/outline width in px, or 0 when unset/non-positive. */
static double box_edge_px(int wpx) {
    return (wpx != PV_LEN_UNSET && wpx > 0) ? (double)wpx : 0.0;
}

/* True iff a border/outline style paints a line (solid..outset); none/hidden/unset
 * paint nothing. The fancier 3D styles collapse to solid at paint time. */
static int box_line_visible(int style) {
    return style >= CSS_BST_SOLID && style <= CSS_BST_OUTSET;
}

/* Closes the open block box: flushes the current line, reserves the box's bottom
 * padding+border, and finalizes the recorded border-box height. No-op if none open. */
static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th) {
    if (s->box_depth <= 0) return;
    flush_line(L, s, th);
    rc_open_box *ob = &s->box_stack[s->box_depth - 1];
    s->cur_top += ob->pb + ob->bb;   /* bottom padding + border close the border box */
    if (ob->box_idx < L->nbox) {
        rc_box *bx = &L->boxes[ob->box_idx];
        double h = s->cur_top - bx->top;
        /* 2026-07-10: author box_h / box_min_h / box_max_h clamp the painted
         * height. box_h wins when set (the box is the declared size); min_h is
         * a floor, max_h a cap. The v1 model is intentionally simple: the box
         * is the larger of content vs min_h, smaller of result vs max_h, and
         * the fixed box_h when set overrides both. */
        if (bx->box_h > 0) h = (double)bx->box_h;
        if (bx->box_min_h > 0 && h < (double)bx->box_min_h) h = (double)bx->box_min_h;
        if (bx->box_max_h > 0 && h > (double)bx->box_max_h) h = (double)bx->box_max_h;
        bx->h = h;
        if (h > 0.0 && s->cur_top - bx->top < h) s->cur_top = bx->top + h;
    }
    s->box_depth--;
    if (s->hidden_from > s->box_depth) s->hidden_from = 0;
}

/* Closes every open box (innermost first). Used at document end and when a flex/grid
 * container interrupts the box flow (a box broken by a container is not composed). */
static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th) {
    while (s->box_depth > 0) close_top_box(L, s, th);
}

/* Content rect (left, width) the current run/box is laid out in: the innermost open
 * box's, or the page content box when no box is open (default flat flow). */
static void rc_box_context(const rc_state *s, double content_w,
                           double *ctx_left, double *ctx_w) {
    if (s->box_depth > 0) {
        const rc_open_box *ob = &s->box_stack[s->box_depth - 1];
        *ctx_left = ob->inner_left;
        *ctx_w = ob->inner_w;
    } else {
        *ctx_left = 0.0;
        *ctx_w = content_w;
    }
}

/* Opens a block box (block_id, decoration from def) INSIDE the content rect
 * [ctx_left, ctx_left+ctx_w): flushes the line, applies the gap before the box,
 * records the border-box rect, reserves the top border+padding, and pushes the box's
 * own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At top level (ctx_left 0, ctx_w content_w) this reproduces the Step B/C single-
 * box geometry exactly, so single boxes and the default path stay byte-identical. */
static void open_box(rc_layout *L, rc_state *s, const ui_theme *th,
                     int block_id, const pv_box_def *def,
                     double ctx_left, double ctx_w) {
    flush_line(L, s, th);
    if (L->nrow > 0) {
        double gap = (s->prev_bottom > th->paragraph_gap) ? s->prev_bottom : th->paragraph_gap;
        s->cur_top += gap;
    }
    s->prev_bottom = 0;

    double bl = box_edge_px(def->bord_lw), br = box_edge_px(def->bord_rw);
    double bt = box_edge_px(def->bord_tw), bb = box_edge_px(def->bord_bw);
    double pl = (def->pad_l > 0) ? (double)def->pad_l : 0.0;
    double pr = (def->pad_r > 0) ? (double)def->pad_r : 0.0;
    double pt = (def->pad_t > 0) ? (double)def->pad_t : 0.0;
    double pb = (def->pad_b > 0) ? (double)def->pad_b : 0.0;

    double avail_w = ctx_w;
    if (avail_w < 1.0) avail_w = 1.0;
    /* box-sizing: border-box (2026-07-11): the declared width includes the
     * horizontal padding + border, so the CONTENT cap shrinks by those edges. */
    double wcap = bx_content_cap(bx_width_cap(def->box_w, def->box_w_pct, avail_w),
                                 def->box_sizing == CSS_BOXS_BORDER, pl, pr, bl, br);
    bx_hplace hp = bx_place((double)def->box_l, (double)def->box_r,
                            wcap, def->box_center, avail_w);
    double box_left = ctx_left + hp.x_off - pl;
    double box_width = hp.content_w + pl + pr;

    /* visibility:hidden on this box or an inherited hidden ancestor: geometry
     * (x/top/w, and h once close_top_box finalizes it) is still resolved so layout
     * space is reserved; only decoration/content painting is skipped. */
    int inherited_hidden = (s->hidden_from != 0);
    int this_hidden = (def->visibility == CSS_VIS_HIDDEN || def->visibility == CSS_VIS_COLLAPSE);

    rc_box *bx = rc_add_box(L);
    size_t idx = (bx != NULL) ? (L->nbox - 1) : (size_t)-1;
    if (bx != NULL) {
        bx->x = box_left; bx->top = s->cur_top; bx->w = box_width; bx->h = 0.0;
        bx->block_id = block_id;
        bx->bord_tw = def->bord_tw; bx->bord_rw = def->bord_rw;
        bx->bord_bw = def->bord_bw; bx->bord_lw = def->bord_lw;
        bx->bord_ts = def->bord_ts; bx->bord_rs = def->bord_rs;
        bx->bord_bs = def->bord_bs; bx->bord_ls = def->bord_ls;
        bx->bord_tc = def->bord_tc; bx->bord_rc = def->bord_rc;
        bx->bord_bc = def->bord_bc; bx->bord_lc = def->bord_lc;
        bx->radius = def->border_radius;
        bx->bsh_dx = def->bsh_dx; bx->bsh_dy = def->bsh_dy; bx->bsh_blur = def->bsh_blur;
        bx->bsh_spread = def->bsh_spread; bx->bsh_color = def->bsh_color;
        bx->bsh_inset = def->bsh_inset;
        bx->outline_w = def->outline_w; bx->outline_style = def->outline_style;
        bx->outline_color = def->outline_color;
        bx->outline_offset = (def->outline_offset != PV_LEN_UNSET) ? def->outline_offset : 0;
        bx->bg_rgb = def->bg_rgb;
        bx->grad_n = def->grad_n; bx->grad_angle = def->grad_angle;
        bx->grad_c[0] = def->grad_c0; bx->grad_c[1] = def->grad_c1;
        bx->grad_c[2] = def->grad_c2; bx->grad_c[3] = def->grad_c3;
        bx->bg_size = def->bg_size; bx->bg_repeat = def->bg_repeat;
        bx->hidden = inherited_hidden || this_hidden;
        /* 2026-07-10 author vertical dimensions + aspect-ratio. box_min_w enlarges
         * box_width when the layout was smaller; box_h sets a fixed height (the
         * content still flows; the painted box keeps the larger of content vs
         * box_h). aspect-ratio is honoured below alongside the box. */
        bx->box_h = def->box_h; bx->box_min_h = def->box_min_h;
        bx->box_max_h = def->box_max_h; bx->box_min_w = def->box_min_w;
        bx->aspect_num = def->aspect_num; bx->aspect_den = def->aspect_den;
        if (def->box_min_w > 0 && box_width < (double)def->box_min_w) {
            box_width = (double)def->box_min_w;
            bx->w = box_width;
        }
        if (bx->aspect_num > 0 && bx->aspect_den > 0) {
            /* aspect-ratio (num/den x1000) sizes the height from width or vice
             * versa. With a fixed width, the height is width * den / num. */
            if (box_width > 0.0) {
                double h = box_width * (double)bx->aspect_den / (double)bx->aspect_num;
                if (bx->box_h == 0 && h > bx->h) bx->h = h;
            }
        }

        /* Stage 2: position:relative (and sticky, fail-closed to relative) offsets
         * the box's own rect by its insets. Siblings are unaffected — the box's
         * own rows (and child boxes) move with it. Inset UNSET/AUTO → 0 offset
         * on that axis (the box anchors at its in-flow position). */
        if (def->position == BT_POS_RELATIVE || def->position == BT_POS_STICKY) {
            if (def->inset_left != PV_LEN_UNSET && def->inset_left != (int)PV_LEN_UNSET + 1)
                bx->x += (double)def->inset_left;
            if (def->inset_top  != PV_LEN_UNSET && def->inset_top  != (int)PV_LEN_UNSET + 1)
                bx->top += (double)def->inset_top;
        }
    }
    s->cur_top += bt + pt;       /* inner content starts below the top border + padding */
    if (s->box_depth < RC_BOX_STACK_MAX) {
        rc_open_box *ob = &s->box_stack[s->box_depth++];
        ob->block_id = block_id;
        ob->box_idx = idx;
        ob->bl = bl; ob->br = br; ob->pb = pb; ob->bb = bb;
        ob->inner_left = ctx_left + hp.x_off + bl;
        ob->inner_w = hp.content_w - bl - br;
        if (ob->inner_w < 1.0) ob->inner_w = 1.0;
        if (!inherited_hidden && this_hidden) s->hidden_from = s->box_depth;
    }
}

/* Reconciles the open-box stack so it equals block b's box path (root..b->block_id),
 * derived from the box-def parent_id chain. Closes any open box not on the path
 * (innermost first), then opens any path box not yet open (outermost first), nesting
 * each inside its parent's content rect. Bounded by RC_BOX_STACK_MAX. */
static void reconcile_boxes(rc_layout *L, rc_state *s, const ui_theme *th,
                            const rd_doc *doc, double content_w, int block_id) {
    int path[RC_BOX_STACK_MAX];
    int n = 0;
    for (int id = block_id; id >= 0 && n < RC_BOX_STACK_MAX; ) {
        path[n++] = id;
        const pv_box_def *d = rd_box_at(doc, (size_t)id);
        id = (d != NULL) ? d->parent_id : -1;
    }
    /* path is innermost..outermost; reverse to root..innermost. */
    for (int a = 0, b = n - 1; a < b; ++a, --b) { int t = path[a]; path[a] = path[b]; path[b] = t; }

    /* Keep the common prefix; close the divergent tail of the open stack. */
    int common = 0;
    while (common < s->box_depth && common < n &&
           s->box_stack[common].block_id == path[common]) ++common;
    while (s->box_depth > common) close_top_box(L, s, th);

    /* Open the remaining path boxes, each inside the current innermost box's rect. */
    for (int k = common; k < n; ++k) {
        const pv_box_def *d = rd_box_at(doc, (size_t)path[k]);
        if (d == NULL) break;
        double ctx_left, ctx_w;
        rc_box_context(s, content_w, &ctx_left, &ctx_w);
        open_box(L, s, th, path[k], d, ctx_left, ctx_w);
    }
}

/* Stage 2: positioned blocks (absolute/fixed) that were skipped from the in-flow
 * pass are recorded here for position_doc to lay out afterwards. The cap mirrors
 * PV's per-page container cap; a hostile page cannot exceed it. */
#define RC_MAX_OUT_OF_FLOW 256

/* Box path root..block_id via the box-def parent_id chain (root first), written into
 * out (bounded by RC_BOX_STACK_MAX). Returns the path length; block_id < 0 gives 0. */
static int box_path_of(const rd_doc *doc, int block_id, int *out) {
    int tmp[RC_BOX_STACK_MAX];
    int n = 0;
    for (int id = block_id; id >= 0 && n < RC_BOX_STACK_MAX; ) {
        tmp[n++] = id;
        const pv_box_def *d = rd_box_at(doc, (size_t)id);
        id = (d != NULL) ? d->parent_id : -1;
    }
    for (int a = 0; a < n; ++a) out[a] = tmp[n - 1 - a];  /* reverse to root..id */
    return n;
}

/* The innermost box that is an ancestor (or self) of EVERY block in [start, end), via
 * the longest common prefix of their box paths — the box a float band nests inside, so
 * a wrapping position:relative/background panel is opened in flow and paints its
 * background behind the columns. -1 when the blocks share no box (top-level band). */
static int band_common_box(const rd_doc *doc, size_t start, size_t end) {
    int common[RC_BOX_STACK_MAX];
    int ncommon = box_path_of(doc, rd_at(doc, start)->block_id, common);
    for (size_t k = start + 1; k < end && ncommon > 0; ++k) {
        int path[RC_BOX_STACK_MAX];
        int n = box_path_of(doc, rd_at(doc, k)->block_id, path);
        int m = 0;
        while (m < ncommon && m < n && common[m] == path[m]) ++m;
        ncommon = m;
    }
    return (ncommon > 0) ? common[ncommon - 1] : -1;
}

/* Lays a float band [start, end) — a maximal run of blocks each with float_id >= 0 —
 * side by side inside the current box context (spec/float.md). Blocks are grouped by
 * float_id into items (document order); each item's width is its author box_w (px or
 * % via bx_width_cap, Hito 32), and width-less items split the leftover evenly;
 * left/right sides pack via fx_float_pack_wrap: an item that no longer fits opens a
 * NEW band row (spec/float.md §7b), so consecutive full-width floats stack. Each
 * item's blocks flow into its column (a fresh sub-state, like the flex per-item
 * pass); the band height is the sum over rows of each row's tallest column.
 * Structure, applied by default. */
static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
                              rc_state *s, const ui_theme *th, double content_w,
                              const rd_doc *doc, size_t start, size_t end) {
    flush_line(L, s, th);
    double ctx_left, ctx_w;
    rc_box_context(s, content_w, &ctx_left, &ctx_w);
    if (ctx_w < 1.0) ctx_w = 1.0;

    /* Group consecutive blocks by float_id into items (one floated element = one item). */
    size_t gstart[BT_MAX_CHILDREN + 1];
    size_t g = 0;
    int grp_overflow = 0;
    {
        int prev_fid = -1, have = 0;
        for (size_t k = start; k < end; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (!have || bk->float_id != prev_fid) {
                if (g >= BT_MAX_CHILDREN) { grp_overflow = 1; break; }
                gstart[g++] = k;
            }
            prev_fid = bk->float_id; have = 1;
        }
        gstart[g] = end;
    }
    if (g == 0 || grp_overflow) {  /* too many items: degrade to plain vertical flow */
        for (size_t k = start; k < end; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (bk->block_break) flush_line(L, s, th);
            s->bg_rgb = (!w->force_theme) ? bk->bg_rgb : -1;
            flow_text_block(cr, w, L, s, th, bk, ctx_w);
        }
        return;
    }

    double base_top = s->cur_top + ((L->nrow > 0) ? s->pending_gap : 0.0);
    s->pending_gap = 0;

    /* Item widths + sides: explicit author width (px or % of the band context,
     * Hito 32) wins; width-less items split the leftover evenly. */
    double width[BT_MAX_CHILDREN];
    int    side[BT_MAX_CHILDREN];
    double outx[BT_MAX_CHILDREN];
    size_t outrow[BT_MAX_CHILDREN];
    double explicit_sum = 0.0;
    size_t nfree = 0;
    for (size_t j = 0; j < g; ++j) {
        const rd_block *bk = rd_at(doc, gstart[j]);
        side[j] = (bk->float_side == CSS_FLOAT_RIGHT) ? 1 : 0;
        double capw = bx_width_cap(bk->box_w, bk->box_w_pct, ctx_w);
        width[j] = (capw > 0.0) ? capw : -1.0;
        if (width[j] > 0.0) explicit_sum += width[j]; else ++nfree;
    }
    double leftover = ctx_w - explicit_sum;
    double share = (nfree > 0) ? (leftover / (double)nfree) : 0.0;
    if (share < 1.0) share = 1.0;
    for (size_t j = 0; j < g; ++j) if (width[j] < 0.0) width[j] = share;

    /* Greedy row wrap (Hito 32): an item that no longer fits opens a new band
     * row -- consecutive full-width floats (.grid_24) stack instead of cramming. */
    if (fx_float_pack_wrap(width, side, g, ctx_w, 0.0, outx, outrow) != FX_OK) {
        for (size_t k = start; k < end; ++k)
            flow_text_block(cr, w, L, s, th, rd_at(doc, k), ctx_w);
        return;
    }

    /* Flow each item into its column, then translate its rows to the column rect.
     * Band rows stack: a row's top is the summed height of the rows above it and
     * its height is its tallest column (items arrive in document order, so row
     * indices are non-decreasing). */
    double row_top = 0.0;
    double row_h = 0.0;
    size_t cur_row = 0;
    for (size_t j = 0; j < g; ++j) {
        if (outrow[j] != cur_row) {
            row_top += row_h;
            row_h = 0.0;
            cur_row = outrow[j];
        }
        rc_state si;
        memset(&si, 0, sizeof si);
        double cw = (width[j] < 1.0) ? 1.0 : width[j];
        si.bg_w = cw;
        size_t sr = L->nrow;
        for (size_t k = gstart[j]; k < gstart[j + 1]; ++k) {
            const rd_block *bk = rd_at(doc, k);
            if (k > gstart[j] && bk->block_break) flush_line(L, &si, th);
            si.bg_rgb = (!w->force_theme) ? bk->bg_rgb : -1;
            flow_text_block(cr, w, L, &si, th, bk, cw);
        }
        flush_line(L, &si, th);
        if (si.cur_top > row_h) row_h = si.cur_top;
        for (size_t r = sr; r < L->nrow; ++r) {
            L->rows[r].top += base_top + row_top;
            L->rows[r].x_off = ctx_left + outx[j];
        }
    }
    s->cur_top = base_top + row_top + row_h;
}

static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                       rc_layout *L) {
    const rd_doc *doc = w->doc;
    const ui_theme *th = &w->theme;
    memset(L, 0, sizeof *L);
    rc_state s;
    memset(&s, 0, sizeof s);
    s.bg_rgb = -1;  /* 0 is opaque black; no background until a block sets one */
    /* s.box_depth starts 0 (memset): no open box -> default flat flow. */

    for (size_t i = 0; i < rd_count(doc); ++i) {
        const rd_block *b = rd_at(doc, i);
        /* Hidden controls are never painted (their value still submits). */
        if (b->kind == RD_INPUT && b->input_type == PV_IN_HIDDEN) continue;

        /* A maximal run of blocks sharing one author flex/grid container (carried
         * by default; layout is structure, not gated by caps.css) is laid out in
         * columns and then skipped. */
        if (b->cont_id >= 0 &&
            (b->cont_display == BX_DISPLAY_FLEX || b->cont_display == BX_DISPLAY_GRID)) {
            close_all_boxes(L, &s, th);  /* a container ends any open block box (v1) */
            size_t j = i + 1;
            while (j < rd_count(doc) && rd_at(doc, j)->cont_id == b->cont_id) ++j;
            double mt, mb;
            block_margins(th, b, &mt, &mb);
            s.pending_gap = (s.prev_bottom > mt) ? s.prev_bottom : mt;
            layout_container(cr, w, L, &s, th, content_w, doc, i, j);
            s.prev_bottom = mb;
            i = j - 1;  /* the loop's ++i moves past the container */
            continue;
        }

        /* Stage 2: out-of-flow blocks (position:absolute / fixed) are skipped from
         * the in-flow layout — they take no space, don't open a box, and don't
         * collapse margins. position_doc resolves their final rect after this pass.
         * The parent wrapper is NOT closed: an absolute/fixed child must not
         * fragment its in-flow ancestor (the spec says "skip the in-flow placement
         * entirely; prev_bottom/pending_gap not touched" — closing boxes here was a
         * regression that split the wrapper into N zero-height pieces, making the
         * LAST piece the containing block and pushing the absolutes to the page
         * bottom). The next in-flow block reconciles the box stack normally. */
        if (b->block_id >= 0) {
            const pv_box_def *bd = rd_box_at(doc, (size_t)b->block_id);
            if (bd != NULL && (bd->position == BT_POS_ABSOLUTE || bd->position == BT_POS_FIXED)) {
                continue;
            }
        }

        /* Float band (spec/float.md): a maximal run of blocks each with float_id >= 0
         * lays side by side. Unlike a flex/grid container it does NOT close the open
         * boxes — it reconciles to the band's COMMON box so a wrapping
         * position:relative/background panel stays open and paints behind the columns.
         * A block whose own `clear` is set ends the band (the cleared block flows below).
         * Structure, applied by default (never gated by caps.css). */
        if (b->float_id >= 0) {
            size_t j = i + 1;
            while (j < rd_count(doc)) {
                const rd_block *bj = rd_at(doc, j);
                if (bj->float_id < 0 || bj->float_clear != 0) break;
                ++j;
            }
            reconcile_boxes(L, &s, th, doc, content_w, band_common_box(doc, i, j));
            double mt, mb;
            block_margins(th, b, &mt, &mb);
            s.pending_gap = (s.prev_bottom > mt) ? s.prev_bottom : mt;
            layout_float_band(cr, w, L, &s, th, content_w, doc, i, j);
            s.prev_bottom = mb;
            i = j - 1;  /* the loop's ++i moves past the band */
            continue;
        }

        /* Box engine (Hito 23b-8 Step D): reconcile the open-box stack with this
         * block's box path (root..block_id) from the box-def parent chain, so a child
         * box nests inside its parent instead of splitting it. block_id < 0 (images,
         * inputs, blocks outside any box) closes all open boxes. */
        reconcile_boxes(L, &s, th, doc, content_w, b->block_id);

        int standalone = (b->kind == RD_IMAGE || b->kind == RD_NOTICE
                       || b->kind == RD_HEADING || b->kind == RD_INPUT
                       || b->kind == RD_VIDEO);
        if (standalone || b->block_break) {
            flush_line(L, &s, th);
            /* Space before this block = its top margin collapsed with the previous
             * block's bottom margin (CSS adjacent-margin collapsing, basic). */
            double mt, mb;
            block_margins(th, b, &mt, &mb);
            s.pending_gap = (s.prev_bottom > mt) ? s.prev_bottom : mt;
            s.prev_bottom = mb;
        }

        if (b->kind == RD_INPUT) {
            content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            double h = fe.height + 2.0 * UI_INPUT_PAD;
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_INPUT; r->top = top; r->height = h; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->bg_rgb = -1; r->x_off = 0.0;
                r->align = 0; r->blk = b; r->hidden = (s.hidden_from != 0);
            }
            s.cur_top = top + h;
            continue;
        }

        if (b->kind == RD_IMAGE) {
            content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            /* A decoded image sizes the row to its on-screen height; otherwise the
             * row is a single-line placeholder box. Same box width used to paint. */
            double dw, dh;
            double box_w = content_w - 2.0 * th->image_box_pad;
            double h = image_display_size(w, b, box_w, &dw, &dh)
                       ? dh + 2.0 * th->image_box_pad
                       : fe.height + 2.0 * th->image_box_pad;
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_IMAGE; r->top = top; r->height = h; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->bg_rgb = -1; r->x_off = 0.0;
                r->align = 0; r->blk = b; r->hidden = (s.hidden_from != 0);
            }
            s.cur_top = top + h;
            continue;
        }

        if (b->kind == RD_VIDEO) {
            content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            /* Placeholder row: use declared dimensions or a default box. Later
             * (Fase 1+) this row will contain the decoded video frame. */
            double vh = (b->video_h > 0) ? (double)b->video_h
                       : fe.height * 6.0;  /* ~matched to video aspect ratio default */
            double top = s.cur_top + (L->nrow > 0 ? s.pending_gap : 0.0);
            s.pending_gap = 0;
            rc_row *r = rc_add_row(L);
            if (r != NULL) {
                r->kind = RC_VIDEO; r->top = top; r->height = vh; r->ascent = fe.ascent;
                r->first = 0; r->count = 0; r->banner = 0; r->bg_rgb = -1; r->x_off = 0.0;
                r->align = 0; r->blk = b; r->hidden = (s.hidden_from != 0);
            }
            s.cur_top = top + vh;
            continue;
        }

        /* Author background travels on the row (unless the theme is forced); the
         * foreground tints the fragments inside flow_text_block. */
        s.bg_rgb = (!w->force_theme) ? b->bg_rgb : -1;
        /* List items indent the whole block by their nesting depth; the marker text
         * was prepended by page_view. Non-list blocks have indent 0. The author box
         * model (left/right insets, a width cap and margin:0 auto centering, only
         * with caps.css; all zero otherwise -> identical to before) then places the
         * content within the remaining width via the pure bx_place. */
        double base_l = (double)b->indent * UI_LIST_INDENT;
        double inner_w;
        if (s.box_depth > 0) {
            /* Inside a box: the box already placed its content rect (consuming its own
             * hbox/padding/border), so the run just flows there plus its list indent.
             * Re-applying the run's bx_place would double-count the box's insets. */
            double ctx_left, ctx_w;
            rc_box_context(&s, content_w, &ctx_left, &ctx_w);
            s.indent_px = ctx_left + base_l;
            inner_w = ctx_w - base_l;
        } else {
            /* Top level: apply the block's own author box model (insets, width cap,
             * margin:0 auto centering) via the pure bx_place. Byte-identical to before
             * when there is no author box (all zero). */
            double avail_w = content_w - base_l;
            if (avail_w < 1.0) avail_w = 1.0;
            bx_hplace hp = bx_place((double)b->box_l, (double)b->box_r,
                                    bx_width_cap(b->box_w, b->box_w_pct, avail_w),
                                    b->box_center, avail_w);
            s.indent_px = base_l + hp.x_off;
            inner_w = hp.content_w;
        }
        if (inner_w < 1.0) inner_w = 1.0;
        flow_text_block(cr, w, L, &s, th, b, inner_w);
    }
    close_all_boxes(L, &s, th);
    flush_line(L, &s, th);
    L->total_h = s.cur_top;
}

/* Stage 2: resolves out-of-flow positioning for every absolute/fixed block in the
 * document and stores the stacking-ordered result in L->positioned. Runs after
 * layout_doc (which has already placed in-flow blocks). The geometry arrays are
 * built from the rc_box rects (in-flow boxes) plus a content-measurement pass for
 * out-of-flow blocks; pv_box_defs that are not present in either get zero geometry
 * (the solver treats them as zero-size at the containing block's origin). */
static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                        rc_layout *L) {
    const rd_doc *doc = w->doc;
    size_t nbox = rd_box_count(doc);
    if (nbox == 0) { L->npositioned = 0; return; }
    if (nbox > BT_MAX_POSITIONED) {
        /* Fail closed: a hostile page with too many boxes skips the positioning
         * pass for this frame rather than overflowing. */
        L->npositioned = 0;
        return;
    }

    /* Build the geometry arrays indexed by block_id (= pv_box_def index). */
    double gx[BT_MAX_POSITIONED] = {0};
    double gy[BT_MAX_POSITIONED] = {0};
    double gw[BT_MAX_POSITIONED] = {0};
    double gh[BT_MAX_POSITIONED] = {0};
    char   in_flow[BT_MAX_POSITIONED] = {0};

    /* In-flow boxes: their rc_box rect is the layout-space border-box. */
    for (size_t i = 0; i < L->nbox; ++i) {
        int bid = L->boxes[i].block_id;
        if (bid < 0 || (size_t)bid >= nbox) continue;
        gx[bid] = L->boxes[i].x;
        gy[bid] = L->boxes[i].top;
        gw[bid] = L->boxes[i].w;
        gh[bid] = L->boxes[i].h;
        in_flow[bid] = 1;
    }

    /* Out-of-flow blocks: measure content so the solver has a final w/h. The
     * box-def's own box_w (an author width cap) is the first preference; the
     * content width is the fallback. Height is the measured text height for
     * text blocks, the image-display size for image blocks, the input height
     * for inputs, and a reasonable default otherwise. */
    const ui_theme *th = &w->theme;
    content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double default_h = fe.height;
    for (size_t i = 0; i < rd_count(doc); ++i) {
        const rd_block *b = rd_at(doc, i);
        if (b->block_id < 0) continue;
        size_t bid = (size_t)b->block_id;
        if (bid >= nbox) continue;
        if (in_flow[bid]) continue;  /* already set from rc_box */

        const pv_box_def *bd = rd_box_at(doc, bid);
        if (bd == NULL) continue;

        /* Width: author width cap (px or %), else the box's own bx_place against
         * content_w. */
        double bw = bx_width_cap(bd->box_w, bd->box_w_pct, content_w);
        if (bw <= 0.0) {
            bx_hplace hp = bx_place((double)bd->box_l, (double)bd->box_r, 0, 0, content_w);
            bw = hp.content_w;
        }
        if (bw < 1.0) bw = content_w;
        if (bw < 1.0) bw = 1.0;
        gw[bid] = bw;

        /* Height: measured for text, default for the rest. */
        if (b->kind == RD_IMAGE) {
            double dw, dh, box_w = content_w - 2.0 * th->image_box_pad;
            if (image_display_size(w, b, box_w, &dw, &dh)) {
                gh[bid] = dh + 2.0 * th->image_box_pad;
            } else {
                gh[bid] = default_h + 2.0 * th->image_box_pad;
            }
        } else if (b->kind == RD_INPUT) {
            gh[bid] = default_h + 2.0 * UI_INPUT_PAD;
        } else {
            /* Text block: the same single-line height used by the in-flow rows.
             * Multi-line absolute/fixed is approximated as one line in v1; the
             * painter wraps inside the resolved width. */
            gh[bid] = default_h;
        }
    }

    bt_status st = bt_resolve_positioning(
        doc->boxes, nbox, gx, gy, gw, gh, content_w, content_w,
        L->positioned, BT_MAX_POSITIONED, &L->npositioned);
    (void)st;  /* BT_OK / BT_ERR_NULL_ARG / BT_ERR_RANGE all logged via dom_debug */

    /* A position:relative box is already painted IN FLOW (open_box applied its inset
     * offset and its rc_box paints its decoration behind its rows). bt_resolve_
     * positioning also emits it (relative keeps in-flow geometry + inset), which would
     * make the painter repaint the box on TOP of its rows — covering everything past
     * the first block with the box background. So drop the in-flow (relative) boxes
     * here; the positioned repaint pass is left with only the true out-of-flow boxes
     * (absolute/fixed, which layout_doc skipped so they have no rc_box). */
    size_t keep = 0;
    for (size_t i = 0; i < L->npositioned; ++i) {
        size_t bid = L->positioned[i].box_index;
        if (bid < BT_MAX_POSITIONED && in_flow[bid]) continue;
        L->positioned[keep++] = L->positioned[i];
    }
    L->npositioned = keep;
}

/* Width of a painted text-input box: the preferred width clamped to the content. */
static double input_box_width(double content_w) {
    return (content_w < UI_INPUT_WIDTH) ? content_w : UI_INPUT_WIDTH;
}

static double select_box_width(double content_w) {
    return input_box_width(content_w);
}

/* Width of a painted button: its label plus horizontal padding, clamped. */
static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
                               double content_w) {
    content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
    const char *label = (b->text != NULL && b->text[0] != '\0') ? b->text
                        : rd_input_label(b->input_type);
    double bw = measure_slice(cr, label, strlen(label)) + 2.0 * UI_BUTTON_HPAD;
    return (bw > content_w) ? content_w : bw;
}

/* Paints one form control row: a filled button, or a bordered editable text box
 * with its value (masked for passwords), placeholder, and caret when focused. */
static void draw_input_row(cairo_t *cr, browser_window *w, const rd_block *b,
                           double left, double content_w, double ry,
                           double ascent, double height) {
    const ui_theme *th = &w->theme;
    int focused = (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count
                   && w->inputs[w->focused_input].blk == b);

    if (b->input_type == PV_IN_SUBMIT || b->input_type == PV_IN_BUTTON) {
        const char *label = (b->text != NULL && b->text[0] != '\0') ? b->text
                            : rd_input_label(b->input_type);
        double bw = button_box_width(cr, th, b, content_w);
        set_rgb(cr, th->button_bg);
        cairo_rectangle(cr, left, ry, bw, height);
        cairo_fill(cr);
        cairo_save(cr);
        cairo_rectangle(cr, left, ry, bw, height);
        cairo_clip(cr);
        set_rgb(cr, th->button_text);
        content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
        draw_slice(cr, left + UI_BUTTON_HPAD, ry + ascent + UI_INPUT_PAD, label, strlen(label));
        cairo_restore(cr);
        return;
    }

    if (b->input_type == PV_IN_CHECKBOX || b->input_type == PV_IN_RADIO) {
        /* Checkbox: square box; Radio: circle. Both 14×14 px, UX clickable. */
        double bx = left, by = ry + (height - 14.0) * 0.5;
        int is_checked = (b->checked >= 1) ? 1 : 0;
        double lw = 1.5;
        set_rgb(cr, focused ? th->link : th->input_border);
        cairo_set_line_width(cr, lw);
        if (b->input_type == PV_IN_RADIO) {
            double r = 6.5;
            cairo_arc(cr, bx + 7.0, by + 7.0, r, 0, 2 * M_PI);
            cairo_stroke(cr);
            if (is_checked) {
                set_rgb(cr, focused ? th->link : th->button_bg);
                cairo_arc(cr, bx + 7.0, by + 7.0, 4.0, 0, 2 * M_PI);
                cairo_fill(cr);
            }
        } else {
            cairo_rectangle(cr, bx + 1.0, by + 1.0, 12.0, 12.0);
            cairo_stroke(cr);
            if (is_checked) {
                set_rgb(cr, th->link);
                cairo_move_to(cr, bx + 3.0, by + 7.0);
                cairo_line_to(cr, bx + 6.5, by + 10.5);
                cairo_line_to(cr, bx + 11.0, by + 3.0);
                cairo_set_line_width(cr, 2.0);
                cairo_stroke(cr);
            }
        }
        /* Label after the widget */
        if (b->text != NULL && b->text[0] != '\0') {
            set_rgb(cr, th->input_text);
            content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
            draw_slice(cr, bx + 18.0, ry + ascent + UI_INPUT_PAD, b->text, strlen(b->text));
        }
        return;
    }

    if (b->input_type == PV_IN_SELECT) {
        double bw = select_box_width(content_w);
        set_rgb(cr, focused ? th->input_bg_focused : th->input_bg);
        cairo_rectangle(cr, left, ry, bw, height);
        cairo_fill(cr);
        set_rgb(cr, focused ? th->link : th->input_border);
        cairo_set_line_width(cr, 1.0);
        cairo_rectangle(cr, left, ry, bw, height);
        cairo_stroke(cr);
        /* Look up the display label for the current value from options. */
        char selbuf[128];
        const char *shown = selbuf;
        selbuf[0] = '\0';
        if (b->select_opts != NULL) {
            const char *opts = b->select_opts;
            const char *needle = (b->value != NULL) ? b->value : "";
            while (*opts) {
                const char *sep = strstr(opts, "||");
                if (sep == NULL) break;
                size_t vlen = (size_t)(sep - opts);
                const char *lbl_start = sep + 2;
                size_t ll = strcspn(lbl_start, "|");
                if (vlen == strlen(needle) && memcmp(opts, needle, vlen) == 0) {
                    size_t cp = (ll < sizeof selbuf - 1) ? ll : sizeof selbuf - 1;
                    memcpy(selbuf, lbl_start, cp);
                    selbuf[cp] = '\0';
                    break;
                }
                opts = lbl_start + ll;
                if (*opts == '|') opts++; /* skip second | */
                if (*opts == '|') opts++;
                if (*opts == '\0') break;
            }
        }
        if (selbuf[0] == '\0' && b->value != NULL && b->value[0] != '\0')
            shown = b->value;
        if (shown[0] == '\0' && b->text != NULL && b->text[0] != '\0') {
            set_rgb(cr, th->input_placeholder);
            shown = b->text;
        } else {
            set_rgb(cr, th->input_text);
        }
        content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
        cairo_save(cr);
        cairo_rectangle(cr, left + 2.0, ry + 1.0, bw - 24.0, height - 2.0);
        cairo_clip(cr);
        draw_slice(cr, left + UI_INPUT_PAD, ry + ascent + UI_INPUT_PAD, shown, strlen(shown));
        cairo_restore(cr);
        /* Downward triangle */
        set_rgb(cr, th->input_border);
        double ax = left + bw - 16.0;
        double ay = ry + height * 0.5;
        cairo_move_to(cr, ax, ay - 3.0);
        cairo_line_to(cr, ax + 8.0, ay - 3.0);
        cairo_line_to(cr, ax + 4.0, ay + 4.0);
        cairo_close_path(cr);
        cairo_fill(cr);
        return;
    }

    if (b->input_type == PV_IN_PROGRESS || b->input_type == PV_IN_METER) {
        double bar_w = input_box_width(content_w);
        if (bar_w < 20.0) bar_w = 20.0;
        double bar_h = height - 4.0;
        if (bar_h < 4.0) bar_h = 4.0;
        double bar_x = left;
        double bar_y = ry + (height - bar_h) * 0.5;

        /* Parse value and max (the same fields used by the text-input fallthrough) */
        double val_d = 0.0, max_d = 1.0;
        if (b->value != NULL) val_d = atof(b->value);
        if (b->input_type == PV_IN_PROGRESS) {
            if (b->text != NULL && b->text[0] != '\0') max_d = atof(b->text);
        } else {
            /* meter: text holds "min,max,low,high,optimum" */
            double min_d = 0.0, low_d = 0.0, high_d = 0.0, opt_d = 0.0;
            if (b->text != NULL && b->text[0] != '\0') {
                int nf = sscanf(b->text, "%lf,%lf,%lf,%lf,%lf",
                                &min_d, &max_d, &low_d, &high_d, &opt_d);
                (void)nf;
            }
            if (max_d <= min_d) max_d = min_d + 1.0;
            if (val_d < min_d) val_d = min_d;
            if (val_d > max_d) val_d = max_d;
            double span = max_d - min_d;
            double ratio = (span > 0.0) ? (val_d - min_d) / span : 0.0;

            /* Background track */
            set_rgb(cr, th->input_bg);
            cairo_rectangle(cr, bar_x, bar_y, bar_w, bar_h);
            cairo_fill(cr);

            /* Determine color band: green (good), yellow (warn), red (danger)
             * using low/high as the "good" range and optimum for coloring. */
            ui_rgb fill_col = { 0.4, 0.8, 0.3 }; /* green default */
            int has_low = (low_d > min_d && low_d <= max_d);
            int has_high = (high_d >= min_d && high_d < max_d);
            double good_low = has_low ? low_d : min_d;
            double good_high = has_high ? high_d : max_d;

            if (val_d < good_low) {
                /* Below the low threshold: yellow if optimum is high, red otherwise */
                fill_col = (opt_d >= good_high) ? (ui_rgb){0.9, 0.7, 0.1} : (ui_rgb){0.9, 0.3, 0.2};
            } else if (val_d > good_high) {
                /* Above the high threshold: yellow if optimum is low, red otherwise */
                fill_col = (opt_d <= good_low) ? (ui_rgb){0.9, 0.7, 0.1} : (ui_rgb){0.9, 0.3, 0.2};
            }

            double fill_w = ratio * bar_w;
            if (fill_w > 0.0) {
                cairo_set_source_rgb(cr, fill_col.r, fill_col.g, fill_col.b);
                cairo_rectangle(cr, bar_x, bar_y, fill_w, bar_h);
                cairo_fill(cr);
            }

            /* Thin border */
            set_rgb(cr, th->input_border);
            cairo_set_line_width(cr, 1.0);
            cairo_rectangle(cr, bar_x, bar_y, bar_w, bar_h);
            cairo_stroke(cr);

            /* Label: value/max */
            char label[64];
            cairo_save(cr);
            content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
            cairo_font_extents_t fe;
            cairo_font_extents(cr, &fe);
            int nw = snprintf(label, sizeof label, "%.*g/%.*g",
                              (val_d == (int)val_d) ? 0 : 2, val_d,
                              (max_d == (int)max_d) ? 0 : 2, max_d);
            (void)nw;
            set_rgb(cr, th->input_text);
            double lx = bar_x + 4.0;
            double ly = bar_y + (bar_h - fe.height) * 0.5 + fe.ascent;
            draw_slice(cr, lx, ly, label, strlen(label));
            cairo_restore(cr);
            return;
        }

        if (max_d <= 0.0) max_d = 1.0;
        if (val_d < 0.0) val_d = 0.0;
        if (val_d > max_d) val_d = max_d;
        double ratio = val_d / max_d;

        /* Background track (unfilled portion) */
        set_rgb(cr, th->input_bg);
        cairo_rectangle(cr, bar_x, bar_y, bar_w, bar_h);
        cairo_fill(cr);

        /* Filled portion */
        if (ratio > 0.0) {
            double fill_w = ratio * bar_w;
            if (fill_w < 1.0 && ratio > 0.0) fill_w = 1.0;
            set_rgb(cr, th->link);
            cairo_rectangle(cr, bar_x, bar_y, fill_w, bar_h);
            cairo_fill(cr);
        }

        /* Thin border */
        set_rgb(cr, th->input_border);
        cairo_set_line_width(cr, 1.0);
        cairo_rectangle(cr, bar_x, bar_y, bar_w, bar_h);
        cairo_stroke(cr);

        /* Label: value / max */
        char label[64];
        cairo_save(cr);
        content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
        cairo_font_extents_t fe;
        cairo_font_extents(cr, &fe);
        int nw = snprintf(label, sizeof label, "%.*g / %.*g",
                          (val_d == (int)val_d) ? 0 : 2, val_d,
                          (max_d == (int)max_d) ? 0 : 2, max_d);
        (void)nw;
        set_rgb(cr, th->input_text);
        double lx = bar_x + 4.0;
        double ly = bar_y + (bar_h - fe.height) * 0.5 + fe.ascent;
        draw_slice(cr, lx, ly, label, strlen(label));
        cairo_restore(cr);
        return;
    }

    if (b->input_type == PV_IN_LEGEND) {
        const char *legend = (b->text != NULL && b->text[0] != '\0') ? b->text
                           : (b->value != NULL ? b->value : "");
        if (legend[0] == '\0') return;
        cairo_save(cr);
        content_font(cr, th->body_font, 1, 0, CSS_FF_UNSET); /* bold */
        cairo_font_extents_t fe;
        cairo_font_extents(cr, &fe);
        double lx = left + 4.0;
        double ly = ry + ascent - 1.0;
        /* White background behind the legend text so it covers the border line */
        double tw = measure_slice(cr, legend, strlen(legend));
        set_rgb(cr, th->content_bg);
        cairo_rectangle(cr, lx - 2.0, ly - fe.ascent, tw + 4.0, fe.height);
        cairo_fill(cr);
        set_rgb(cr, th->text);
        draw_slice(cr, lx, ly, legend, strlen(legend));
        cairo_restore(cr);
        return;
    }

    double bw = input_box_width(content_w);
    set_rgb(cr, focused ? th->input_bg_focused : th->input_bg);
    cairo_rectangle(cr, left, ry, bw, height);
    cairo_fill(cr);
    set_rgb(cr, focused ? th->link : th->input_border);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, left, ry, bw, height);
    cairo_stroke(cr);

    ui_input_state *st = find_input_state(w, b);
    const char *val = (st != NULL) ? tf_text(&st->field) : (b->value != NULL ? b->value : "");

    content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
    cairo_save(cr);
    cairo_rectangle(cr, left + 2.0, ry + 1.0, bw - 4.0, height - 2.0);
    cairo_clip(cr);
    double tx = left + UI_INPUT_PAD;
    double ty = ry + ascent + UI_INPUT_PAD;

    /* A password is shown as a run of '*' (one per value byte). */
    char maskbuf[TF_CAP];
    const char *shown = val;
    if (b->input_type == PV_IN_PASSWORD) {
        size_t vl = strlen(val);
        if (vl >= sizeof maskbuf) vl = sizeof maskbuf - 1;
        memset(maskbuf, '*', vl);
        maskbuf[vl] = '\0';
        shown = maskbuf;
    }

    if (shown[0] == '\0' && b->text != NULL && b->text[0] != '\0') {
        set_rgb(cr, th->input_placeholder);
        draw_slice(cr, tx, ty, b->text, strlen(b->text));
    } else {
        set_rgb(cr, th->input_text);
        draw_slice(cr, tx, ty, shown, strlen(shown));
    }

    if (focused && st != NULL) {
        size_t cur = tf_cursor(&st->field);
        size_t slen = strlen(shown);
        if (cur > slen) cur = slen;
        double cx = tx + measure_slice(cr, shown, cur);
        cairo_font_extents_t fe;
        cairo_font_extents(cr, &fe);
        /* caret-color (2026-07-10): the author tint, already caps.css-gated by
         * rd_build (-1 = auto/off -> theme caret). */
        if (b->caret_color >= 0 && !w->force_theme)
            set_rgb(cr, rgb_from_packed(b->caret_color));
        else
            set_rgb(cr, th->caret);
        cairo_rectangle(cr, cx, ty - fe.ascent, 1.5, fe.height);
        cairo_fill(cr);
    }
    cairo_restore(cr);
}

/* Paints one RD_IMAGE row inside the content rectangle: the decoded image blitted
 * and scaled to fit the content width (the bytes were fetched and decoded in the
 * confined worker), or, when no image is available (blocked / policy-rejected /
 * decode failed), a bordered placeholder box labelled with the render_policy
 * decision plus the alt text. The on-screen size comes from image_display_size, the
 * same source of truth the layout used to size this row, so paint and layout agree. */
static void paint_image_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                            double left, double ry, double content_w, double row_h) {
    const ui_theme *th = &w->theme;
    const double pad = th->image_box_pad;
    double box_w = content_w - 2.0 * pad;

    double dw, dh;
    if (image_display_size(w, blk, box_w, &dw, &dh)) {
        const ui_image *im = find_image(w, blk->href);
        int of = blk->object_fit;
        if (of == 0) of = CSS_OFI_FILL; /* unset = fill */
        cairo_save(cr);
        cairo_translate(cr, left + pad, ry + pad);
        cairo_rectangle(cr, 0.0, 0.0, dw, dh);
        cairo_clip(cr);
        switch (of) {
            case CSS_OFI_FILL:
                /* Stretch to fill box, ignoring aspect ratio. */
                cairo_scale(cr, dw / (double)im->nat_w, dh / (double)im->nat_h);
                break;
            case CSS_OFI_CONTAIN:
                /* Fit within box, aspect preserved, centred. */
                { double sx = dw / (double)im->nat_w, sy = dh / (double)im->nat_h;
                  double s = (sx < sy) ? sx : sy;
                  cairo_translate(cr, (dw - im->nat_w * s) * 0.5, (dh - im->nat_h * s) * 0.5);
                  cairo_scale(cr, s, s); }
                break;
            case CSS_OFI_COVER:
                /* Fill box, aspect preserved, cropped. */
                { double sx = dw / (double)im->nat_w, sy = dh / (double)im->nat_h;
                  double s = (sx > sy) ? sx : sy;
                  cairo_translate(cr, (dw - im->nat_w * s) * 0.5, (dh - im->nat_h * s) * 0.5);
                  cairo_scale(cr, s, s); }
                break;
            case CSS_OFI_NONE:
                /* No scaling, centred in box. */
                cairo_translate(cr, (dw - (double)im->nat_w) * 0.5,
                                (dh - (double)im->nat_h) * 0.5);
                break;
            case CSS_OFI_SCALE_DOWN:
                /* Like none or contain, whichever gives a SMALLER image. */
                { double sx = dw / (double)im->nat_w, sy = dh / (double)im->nat_h;
                  double s = (sx < sy) ? sx : sy;
                  if (s > 1.0) { s = 1.0;
                      cairo_translate(cr, (dw - (double)im->nat_w) * 0.5,
                                      (dh - (double)im->nat_h) * 0.5);
                  } else {
                      cairo_translate(cr, (dw - im->nat_w * s) * 0.5,
                                      (dh - im->nat_h * s) * 0.5);
                  }
                  cairo_scale(cr, s, s); }
                break;
        }
        cairo_set_source_surface(cr, im->surface, 0.0, 0.0);
        int nearest = (blk->image_rendering == CSS_IR_PIXELATED ||
                       blk->image_rendering == CSS_IR_CRISP_EDGES);
        cairo_pattern_set_filter(cairo_get_source(cr),
                                 nearest ? CAIRO_FILTER_NEAREST : CAIRO_FILTER_GOOD);
        cairo_paint(cr);
        cairo_restore(cr);
        return;
    }

    /* When an ALLOWed image failed post-decision, show the diagnostic label
     * (e.g. "image (TLS/network error)"); otherwise show the policy label
     * ("image (allowed)", "image blocked: ..."). */
    int blocked = (blk->img_decision != RDP_IMG_ALLOW);
    const char *fail = (!blocked && blk->img_fail != IMG_FAIL_OK)
                     ? rd_image_fail_label(blk->img_fail) : NULL;
    set_rgb(cr, blocked ? th->image_blocked : th->image_box);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, left, ry, content_w, row_h);
    cairo_stroke(cr);

    content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
    cairo_save(cr);
    cairo_rectangle(cr, left + pad, ry, content_w - 2.0 * pad, row_h);
    cairo_clip(cr);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_move_to(cr, left + pad, ry + fe.ascent + pad);
    char label[1024];
    const char *alt = (blk->text != NULL) ? blk->text : "";
    if (fail != NULL) {
        snprintf(label, sizeof label, "%s%s%s",
                 fail, alt[0] ? " : " : "", alt);
    } else {
        snprintf(label, sizeof label, "%s%s%s",
                 rd_image_label(blk->img_decision), alt[0] ? " : " : "", alt);
    }
    cairo_show_text(cr, label);
    cairo_restore(cr);
}

/* Paints one RD_VIDEO row inside the content rectangle: a placeholder rectangle
 * with the video URL label. When the video frame pipeline (Fase 1+) is active,
 * the decoded frame will be blitted here instead. */
/* Frees the video decoder process and its cached frame. Safe to call
 * when no decoder is running (decoder_pid == 0). NULL-safe on w. */
/* EINTR-safe pipe write (local version of the tab.c helper). */
static int v_write(int fd, const void *buf, size_t n) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t done = 0;
    while (done < n) {
        ssize_t w = write(fd, p + done, n - done);
        if (w < 0) { if (errno == EINTR) continue; return -1; }
        done += (size_t)w;
    }
    return 0;
}

/* EINTR-safe pipe read (local version of the tab.c helper). */
static int v_read(int fd, void *buf, size_t n) {
    uint8_t *p = (uint8_t *)buf;
    size_t got = 0;
    while (got < n) {
        ssize_t r = read(fd, p + got, n - got);
        if (r < 0) { if (errno == EINTR) continue; return -1; }
        if (r == 0) return -1;
        got += (size_t)r;
    }
    return 0;
}

static void video_stop(browser_window *w) {
    if (w == NULL) return;

    /* Tell the feeder thread to exit, then wait for it. */
    w->video_active = 0;
    if (w->video_thread != 0) {
        /* Wake the eventfd so the thread doesn't deadlock waiting for a pipe
         * that the main thread already polled. The thread checks video_active
         * before writing and will see 0 and exit. */
        uint64_t one = 1;
        ssize_t wr = write(w->video_evfd, &one, sizeof one);
        (void)wr;
        pthread_join(w->video_thread, NULL);
        w->video_thread = 0;
    }

    if (w->decoder_pid > 0) {
        uint8_t q = MD_QUIT;
        (void)v_write(w->decoder_cmd_fd, &q, 1);
        int st;
        waitpid(w->decoder_pid, &st, WNOHANG);
        close(w->decoder_cmd_fd);
        close(w->decoder_out_fd);
    }
    if (w->video_evfd >= 0) {
        close(w->video_evfd);
        w->video_evfd = -1;
    }
    free(w->video_frame);
    hls_playlist_free(w->video_pl);
    free(w->video_base_url);
    w->decoder_pid = 0;
    w->decoder_cmd_fd = -1;
    w->decoder_out_fd = -1;
    w->video_frame = NULL;
    w->video_w = 0;
    w->video_h = 0;
    w->video_active = 0;
    w->video_pending = 0;
    w->video_pl = NULL;
    w->video_base_url = NULL;
    w->video_eof = 0;
}

/* Reads one decoded ARGB frame from the decoder process pipe and caches
 * it in w->video_frame. Returns 1 if a frame was read, 0 if none available
 * (EAGAIN / EOF), -1 on error. */
static int video_read_frame(browser_window *w) {
    if (w == NULL || w->decoder_out_fd < 0) return -1;
    uint8_t tag;
    ssize_t r = read(w->decoder_out_fd, &tag, 1);
    if (r <= 0) {
        if (r < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) return 0;
        return -1;
    }
    if (tag == MD_EOS) {
        w->video_active = 0;
        return 0;
    }
    if (tag == MD_STREAM_INFO) {
        int32_t codec, w32, h32, ha32;
        if (v_read(w->decoder_out_fd, &codec, sizeof codec) != 0
         || v_read(w->decoder_out_fd, &w32, sizeof w32) != 0
         || v_read(w->decoder_out_fd, &h32, sizeof h32) != 0
         || v_read(w->decoder_out_fd, &ha32, sizeof ha32) != 0)
            return -1;
        (void)codec; (void)ha32;
        w->video_w = (int)w32;
        w->video_h = (int)h32;
        return video_read_frame(w);
    }
    if (tag == MD_FRAME) {
        int64_t pts_s;
        int32_t w32, h32;
        size_t dlen;
        if (v_read(w->decoder_out_fd, &pts_s, sizeof pts_s) != 0
         || v_read(w->decoder_out_fd, &w32, sizeof w32) != 0
         || v_read(w->decoder_out_fd, &h32, sizeof h32) != 0
         || v_read(w->decoder_out_fd, &dlen, sizeof dlen) != 0)
            return -1;
        (void)pts_s;
        if (dlen > 0) {
            uint8_t *frame = (uint8_t *)realloc(w->video_frame, dlen);
            if (frame == NULL) return -1;
            w->video_frame = frame;
            if (v_read(w->decoder_out_fd, w->video_frame, dlen) != 0)
                return -1;
            w->video_w = (int)w32;
            w->video_h = (int)h32;
        }
        return 1;
    }
    if (tag == MD_AUDIO_FRAME) {
        /* Audio frame: read and discard (audio output is future work). The
         * format is PCM S16LE interleaved; we just drain the pipe here. */
        int64_t pts_s;
        int32_t rate, ch;
        size_t dlen;
        if (v_read(w->decoder_out_fd, &pts_s, sizeof pts_s) != 0
         || v_read(w->decoder_out_fd, &rate, sizeof rate) != 0
         || v_read(w->decoder_out_fd, &ch, sizeof ch) != 0
         || v_read(w->decoder_out_fd, &dlen, sizeof dlen) != 0)
            return -1;
        (void)pts_s; (void)rate; (void)ch;
        if (dlen > 0) {
            uint8_t *drop = (uint8_t *)malloc(dlen);
            if (drop != NULL) {
                v_read(w->decoder_out_fd, drop, dlen);
                free(drop);
            }
        }
        return video_read_frame(w); /* read next frame */
    }
    if (tag == MD_ERROR) {
        size_t elen;
        if (v_read(w->decoder_out_fd, &elen, sizeof elen) != 0) return -1;
        if (elen > 0) {
            char *emsg = (char *)malloc(elen + 1);
            if (emsg) {
                v_read(w->decoder_out_fd, emsg, elen);
                emsg[elen] = '\0';
                fprintf(stderr, "[video] decoder error: %s\n", emsg);
                free(emsg);
            }
        }
        return video_read_frame(w);
    }
    return 0;
}

/* Builds a properly-gated sf_config for a video-related fetch (m3u8 playlist or TS
 * segment). Applies the SAME gates as gui_subresource_fetch: host-based impersonation,
 * realm routing (fail-closed), auth scoped to origin, and the allowlist override for
 * navigability fallbacks. The hostblock tracker filter is NOT applied (the user opted
 * in by clicking the placeholder). Returns 1 on success, 0 on realm route blocked. */
static int video_build_fetch_config(browser_window *w, const char *url, sf_config *cfg,
                                     int *allowlisted) {
    *cfg = sf_config_default();
    *allowlisted = 0;
    if (w == NULL || url == NULL) return 1;

    char host[256];
    int have_host = (rp_host_of(url, host, sizeof host) == 0);

    *allowlisted = have_host && hb_is_allowlisted(w->hosts, host);
    apply_auth(w, url, cfg);
    if (apply_route(w, url, cfg) == NR_ROUTE_BLOCKED) return 0;

    cfg->impersonate = ti_should_impersonate(*allowlisted,
        have_host && hb_is_allowlisted(w->js_hosts, host),
        have_host && hb_is_allowlisted(w->impersonate_hosts, host));
    return 1;
}

/* Fetches a single resource (m3u8 or TS segment) under the full policy gates:
 * impersonation, routing, auth, navigability fallbacks. Returns 0 on success;
 * *resp is populated and must be freed with sf_response_free. */
static sf_status video_fetch(const char *url, browser_window *w,
                              sf_response *resp) {
    memset(resp, 0, sizeof *resp);
    sf_config cfg;
    int allowlisted = 0;
    if (!video_build_fetch_config(w, url, &cfg, &allowlisted))
        return SF_ERR_NETWORK;
    int dg = 0;
    return fetch_follow_navigable(url, &cfg, resp, &dg, allowlisted);
}

/* Starts video playback from an m3u8 playlist URL. Fetches the playlist,
 * parses it, handles multi-variant master playlists, spawns the decoder
 * process AND a feeder thread that downloads TS segments and writes them
 * to the decoder pipe. The main (Wayland) thread never blocks on HTTP for
 * video: the event loop drains decoder frames and paints.
 * Returns 0 on success, -1 on failure. */
static int video_play(browser_window *w, const char *m3u8_url) {
    if (w == NULL || m3u8_url == NULL) return -1;
    video_stop(w);

    sf_response resp;
    if (video_fetch(m3u8_url, w, &resp) != SF_OK
        || resp.http_code != 200 || resp.body == NULL || resp.body_len == 0) {
        sf_response_free(&resp);
        return -1;
    }

    hls_playlist *pl = NULL;
    if (hls_parse((const char *)resp.body, resp.body_len, &pl) != HLS_OK) {
        sf_response_free(&resp);
        hls_playlist_free(pl);
        return -1;
    }
    sf_response_free(&resp);

    if (pl->is_variant && pl->nvariants > 0) {
        size_t vi = hls_select_variant(pl, 1920, 1080);
        if (vi == (size_t)-1) { hls_playlist_free(pl); return -1; }
        char var_url[4096];
        size_t vn = hls_resolve_url(m3u8_url, pl->variants[vi].url,
                                     var_url, sizeof var_url);
        hls_playlist_free(pl);
        pl = NULL;
        if (vn == 0) return -1;
        if (video_fetch(var_url, w, &resp) != SF_OK
            || resp.http_code != 200 || resp.body == NULL || resp.body_len == 0) {
            sf_response_free(&resp);
            return -1;
        }
        if (hls_parse((const char *)resp.body, resp.body_len, &pl) != HLS_OK) {
            sf_response_free(&resp);
            hls_playlist_free(pl);
            return -1;
        }
        sf_response_free(&resp);
        w->video_base_url = strdup(var_url);
    } else {
        w->video_base_url = strdup(m3u8_url);
    }

    if (pl == NULL || pl->count == 0) {
        hls_playlist_free(pl);
        free(w->video_base_url);
        w->video_base_url = NULL;
        return -1;
    }

    int out_fd = -1, cmd_fd = -1;
    pid_t pid = 0;
    if (media_decoder_spawn(&pid, &out_fd, &cmd_fd) != 0) {
        hls_playlist_free(pl);
        free(w->video_base_url);
        w->video_base_url = NULL;
        return -1;
    }
    w->decoder_pid = pid;
    w->decoder_out_fd = out_fd;
    w->decoder_cmd_fd = cmd_fd;
    w->video_active = 1;
    w->video_pending = 1;
    w->video_pl = pl;
    w->video_eof = 0;

    int flags = fcntl(out_fd, F_GETFD, 0);
    if (flags >= 0) fcntl(out_fd, F_SETFL, flags | O_NONBLOCK);

    w->video_evfd = eventfd(0, EFD_NONBLOCK);
    if (w->video_evfd < 0) {
        video_stop(w);
        return -1;
    }

    if (pthread_create(&w->video_thread, NULL, video_feeder_thread, w) != 0) {
        video_stop(w);
        return -1;
    }
    return 0;
}

/* Feeder thread: downloads every TS segment and writes them to the decoder
 * pipe. Runs detached from the Wayland event loop — the main thread never
 * blocks on HTTP for video. Signals video_evfd after each segment so the
 * event loop drains frames and redraws. Checks video_active at the top of
 * each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthread_join) causes an orderly exit. */
static void *video_feeder_thread(void *arg) {
    browser_window *w = (browser_window *)arg;
    if (w == NULL || w->video_pl == NULL || w->video_base_url == NULL) {
        if (w != NULL) w->video_eof = 1;
        return NULL;
    }
    signal(SIGPIPE, SIG_IGN);
    size_t total = w->video_pl->count;

    for (size_t i = 0; i < total; i++) {
        if (!w->video_active) break;

        char abs_url[4096];
        size_t n = hls_resolve_url(w->video_base_url,
                                    w->video_pl->segments[i].url,
                                    abs_url, sizeof abs_url);
        if (n == 0) continue;

        sf_response resp;
        memset(&resp, 0, sizeof resp);
        if (video_fetch(abs_url, w, &resp) != SF_OK
            || resp.body == NULL || resp.body_len == 0) {
            sf_response_free(&resp);
            continue;
        }

        uint8_t cmd = MD_DECODE;
        size_t slen = resp.body_len;
        v_write(w->decoder_cmd_fd, &cmd, 1);
        v_write(w->decoder_cmd_fd, &slen, sizeof slen);
        v_write(w->decoder_cmd_fd, resp.body, resp.body_len);
        sf_response_free(&resp);

        /* Wake the event loop so it drains frames and paints. */
        uint64_t one = 1;
        ssize_t wr = write(w->video_evfd, &one, sizeof one);
        (void)wr;
    }

    if (w->video_active) {
        uint8_t f = MD_FLUSH;
        v_write(w->decoder_cmd_fd, &f, 1);
        w->video_eof = 1;
        uint64_t one = 1;
        ssize_t wr = write(w->video_evfd, &one, sizeof one);
        (void)wr;
    }
    return NULL;
}

static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                            double left, double ry, double content_w, double row_h) {
    const ui_theme *th = &w->theme;
    double pad = 4.0;

    /* If a decoded frame is available, blit it. */
    if (w->video_active && w->video_frame != NULL && w->video_w > 0) {
        cairo_surface_t *surf = cairo_image_surface_create_for_data(
            w->video_frame, CAIRO_FORMAT_ARGB32,
            w->video_w, w->video_h,
            w->video_w * 4);
        if (cairo_surface_status(surf) == CAIRO_STATUS_SUCCESS) {
            double scale_x = content_w / (double)w->video_w;
            double scale_y = row_h / (double)w->video_h;
            double scale = (scale_x < scale_y) ? scale_x : scale_y;
            double dw = (double)w->video_w * scale;
            double dh = (double)w->video_h * scale;
            double dx = left + (content_w - dw) / 2.0;
            double dy = ry + (row_h - dh) / 2.0;
            cairo_save(cr);
            cairo_rectangle(cr, left, ry, content_w, row_h);
            cairo_clip(cr);
            cairo_translate(cr, dx, dy);
            cairo_scale(cr, scale, scale);
            cairo_set_source_surface(cr, surf, 0.0, 0.0);
            cairo_paint(cr);
            cairo_restore(cr);
            cairo_surface_destroy(surf);
            return;
        }
        cairo_surface_destroy(surf);
    }

    /* Placeholder background */
    set_rgb(cr, th->image_box);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, left, ry, content_w, row_h);
    cairo_fill_preserve(cr);
    set_rgb(cr, th->input_border);
    cairo_stroke(cr);

    /* Play button icon (triangle) */
    double cx = left + content_w / 2.0;
    double cy = ry + row_h / 2.0;
    double size = (row_h < content_w ? row_h : content_w) * 0.3;
    if (size > 48.0) size = 48.0;
    if (size < 12.0) size = 12.0;
    set_rgb(cr, th->chrome_text);
    cairo_move_to(cr, cx - size * 0.4, cy - size * 0.5);
    cairo_line_to(cr, cx - size * 0.4, cy + size * 0.5);
    cairo_line_to(cr, cx + size * 0.5, cy);
    cairo_close_path(cr);
    cairo_fill(cr);

    /* Label: video URL or alt text */
    content_font(cr, th->body_font, 0, 0, CSS_FF_UNSET);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    const char *label = (blk->text != NULL && blk->text[0] != '\0')
                        ? blk->text
                        : (blk->href != NULL ? blk->href : "video");
    cairo_move_to(cr, left + pad, ry + row_h - pad);
    set_rgb(cr, th->chrome_text_dim);
    cairo_show_text(cr, label);
}

/* Horizontal shift a row's text gets from author text-align (center/right): the
 * slack between the available width and the line's right edge. 0 for left/justify/
 * unset, and for non-text rows. Shared by the painter and the link hit-test so the
 * click target matches exactly what is drawn. */
static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w) {
    if ((r->align != CSS_ALIGN_CENTER && r->align != CSS_ALIGN_RIGHT)
        || r->count == 0 || r->first + r->count > L->nfrag) return 0.0;
    const rc_frag *last = &L->frags[r->first + r->count - 1];
    double line_w = last->x + last->width;
    double slack = (content_w - r->x_off) - line_w;
    if (slack <= 0.0) return 0.0;
    return (r->align == CSS_ALIGN_CENTER) ? slack / 2.0 : slack;
}

/* For text-align: justify, returns the extra width to add per inter-word space
 * (the slack evenly split across all SPACE characters in the row), or 0.0 when
 * the row should not be justified (no slack, no spaces, single fragment, not a
 * justify row). The caller must multiply this by the number of SPACE characters
 * that precede the current fragment to get the fragment's shift. */
static double row_justify_gap(const rc_layout *L, const rc_row *r, double content_w) {
    if (r->align != CSS_ALIGN_JUSTIFY || r->count < 2) return 0.0;
    if (r->first + r->count > L->nfrag) return 0.0;
    const rc_frag *last = &L->frags[r->first + r->count - 1];
    double line_w = last->x + last->width;
    double slack = (content_w - r->x_off) - line_w;
    if (slack <= 0.0) return 0.0;
    size_t nsp = 0;
    for (size_t k = r->first; k < r->first + r->count; ++k) {
        const rc_frag *ff = &L->frags[k];
        for (size_t i = 0; i < ff->len; ++i)
            if (ff->text[i] == ' ') ++nsp;
    }
    return (nsp == 0) ? 0.0 : slack / (double)nsp;
}

/* Appends a rectangle path with radius r (px) to cr. r <= 0 falls back to a plain
 * rectangle; r is clamped so opposite corners never overlap (min(w,h)/2). One radius
 * for all four corners: per-corner / elliptical radii collapse to the first value
 * upstream (see spec/css.md). */
static void box_path(cairo_t *cr, double x, double y, double w, double h, double r) {
    if (r <= 0.0 || w <= 0.0 || h <= 0.0) {
        cairo_rectangle(cr, x, y, w, h);
        return;
    }
    double half = (w < h ? w : h) / 2.0;
    if (r > half) r = half;
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + w - r, y + r,     r, -M_PI / 2.0, 0.0);
    cairo_arc(cr, x + w - r, y + h - r, r, 0.0,          M_PI / 2.0);
    cairo_arc(cr, x + r,     y + h - r, r, M_PI / 2.0,   M_PI);
    cairo_arc(cr, x + r,     y + r,     r, M_PI,         3.0 * M_PI / 2.0);
    cairo_close_path(cr);
}

/* Paints one block box's decoration (Hito 23b-8 Step C): box-shadow, background fill,
 * the four borders and the outline, behind the rows it encloses. (ox, oy) is the
 * absolute offset for the box's layout-space rect. Solid lines in v1 (dashed/dotted
 * collapse to solid). border-radius rounds the shadow, background, outline and --
 * when the four borders are uniform -- the border ring; mixed per-side borders keep
 * square corners. Content is not clipped to the rounded rect (v1). The box
 * decoration was gated behind caps.css upstream (render_doc). */
static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
                                 const ui_bg_image *bgimg) {
    if (bx->hidden) return;  /* visibility:hidden: geometry stood, decoration does not paint */
    double x = ox + bx->x, y = oy + bx->top, w = bx->w, h = bx->h;
    if (w <= 0.0 || h <= 0.0) return;
    double bt = box_edge_px(bx->bord_tw), br = box_edge_px(bx->bord_rw);
    double bb = box_edge_px(bx->bord_bw), bl = box_edge_px(bx->bord_lw);
    double rad = (bx->radius > 0 && bx->radius != CSS_LEN_UNSET) ? (double)bx->radius : 0.0;

    /* Box shadow: skip for sentinel values (CC_COLOR_TRANSPARENT, -1 unset).
     * CC_COLOR_CURRENT uses a default dark gray since we lack the element's color here. */
    if (bx->bsh_color >= 0) {
        double sp = (double)bx->bsh_spread, blur = (double)bx->bsh_blur;
        if (bx->bsh_inset == 1) {
            /* Inset: offset translates; the shadow stays within the border box. */
            double sx = x + (double)bx->bsh_dx, sy = y + (double)bx->bsh_dy;
            double sw = w, sh = h;
            if (sw > 0.0 && sh > 0.0) {
                ui_rgb sc = rgb_from_packed(bx->bsh_color);
                int steps = (blur > 0.0) ? 4 : 1;
                cairo_save(cr);
                box_path(cr, x, y, w, h, rad);          /* clip to inside the box */
                cairo_clip(cr);
                for (int k = steps; k >= 1; --k) {
                    double g = blur * (double)k / (double)steps;
                    cairo_set_source_rgba(cr, sc.r, sc.g, sc.b, 0.30 / (double)steps);
                    box_path(cr, sx - g, sy - g, sw + 2.0 * g, sh + 2.0 * g, rad + g);
                    cairo_fill(cr);
                }
                cairo_restore(cr);
            }
        } else {
            /* Outset (the default): the shadow expands outside the border box. */
            double sx = x + (double)bx->bsh_dx - sp, sy = y + (double)bx->bsh_dy - sp;
            double sw = w + 2.0 * sp, sh = h + 2.0 * sp;
            if (sw > 0.0 && sh > 0.0) {
                ui_rgb sc = rgb_from_packed(bx->bsh_color);
                int steps = (blur > 0.0) ? 4 : 1;
                cairo_save(cr);
                cairo_rectangle(cr, sx - blur, sy - blur, sw + 2.0 * blur, sh + 2.0 * blur);
                box_path(cr, x, y, w, h, rad);              /* punch out the border box */
                cairo_set_fill_rule(cr, CAIRO_FILL_RULE_EVEN_ODD);
                cairo_clip(cr);
                for (int k = steps; k >= 1; --k) {
                    double g = blur * (double)k / (double)steps;
                    cairo_set_source_rgba(cr, sc.r, sc.g, sc.b, 0.30 / (double)steps);
                    box_path(cr, sx - g, sy - g, sw + 2.0 * g, sh + 2.0 * g, rad + g);
                    cairo_fill(cr);
                }
                cairo_restore(cr);
            }
        }
    }

    /* Background fill inside the border box (covers the padding area). A linear
     * gradient wins over the solid color: the gradient line runs through the box
     * center along the CSS angle (0 = to top, 90 = to right), long enough that the
     * first/last stops land on the box corners; stops paint evenly spaced. */
    if (bx->grad_n >= 2) {
        double a = (double)bx->grad_angle * M_PI / 180.0;
        double dx = sin(a), dy = -cos(a);
        double half = (fabs(dx) * w + fabs(dy) * h) / 2.0;
        double cx = x + w / 2.0, cy = y + h / 2.0;
        cairo_pattern_t *pat = cairo_pattern_create_linear(
            cx - dx * half, cy - dy * half, cx + dx * half, cy + dy * half);
        int nst = bx->grad_n <= 4 ? bx->grad_n : 4;
        for (int k = 0; k < nst; ++k) {
            ui_rgb sc = rgb_from_packed(bx->grad_c[k] >= 0 ? bx->grad_c[k] : 0);
            cairo_pattern_add_color_stop_rgb(pat, (double)k / (double)(nst - 1),
                                             sc.r, sc.g, sc.b);
        }
        cairo_set_source(cr, pat);
        box_path(cr, x, y, w, h, rad);
        cairo_fill(cr);
        cairo_pattern_destroy(pat);
    } else if (bx->bg_rgb >= 0) {
        set_rgb(cr, rgb_from_packed(bx->bg_rgb));
        box_path(cr, x, y, w, h, rad);
        cairo_fill(cr);
    }

    /* CSS background-image (2026-07-16): paints OVER bg_rgb/gradient, UNDER the
     * border (CSS background layering: color, then image, then border box edge)
     * -- an image with transparency lets the color underneath show through.
     * background-size chooses the scale: cover/contain both preserve aspect
     * ratio (cover fills the box, possibly cropping; contain fits inside,
     * possibly letterboxing); unset/auto uses the natural pixel size.
     * background-position is not resolved in v1 (see spec/css.md) so tiling/
     * placement always starts at the top-left corner, which matches the CSS
     * initial value 0% 0% -- the common case, not a compromise. repeat-x/
     * repeat-y clip to a one-tile-tall/-wide strip so Cairo's single
     * EXTEND_REPEAT (which tiles both axes) only shows through on the axis
     * that should repeat; space/round fall back to plain repeat (their exact
     * tile-count/spacing math is a v2 refinement, see spec/css.md). */
    if (bgimg != NULL && bgimg->surface != NULL && bgimg->nat_w > 0 && bgimg->nat_h > 0
        && w > 0.0 && h > 0.0) {
        double sx = 1.0, sy = 1.0;
        if (bx->bg_size == CSS_BGS_COVER) {
            double s = (w / (double)bgimg->nat_w > h / (double)bgimg->nat_h)
                     ? w / (double)bgimg->nat_w : h / (double)bgimg->nat_h;
            sx = sy = s;
        } else if (bx->bg_size == CSS_BGS_CONTAIN) {
            double s = (w / (double)bgimg->nat_w < h / (double)bgimg->nat_h)
                     ? w / (double)bgimg->nat_w : h / (double)bgimg->nat_h;
            sx = sy = s;
        }
        double iw = (double)bgimg->nat_w * sx, ih = (double)bgimg->nat_h * sy;
        cairo_save(cr);
        box_path(cr, x, y, w, h, rad);
        cairo_clip(cr);
        if (bx->bg_repeat == CSS_BGR_REPEAT_X && ih > 0.0) {
            cairo_rectangle(cr, x, y, w, ih);
            cairo_clip(cr);
        } else if (bx->bg_repeat == CSS_BGR_REPEAT_Y && iw > 0.0) {
            cairo_rectangle(cr, x, y, iw, h);
            cairo_clip(cr);
        }
        cairo_translate(cr, x, y);
        cairo_scale(cr, sx, sy);
        cairo_pattern_t *ipat = cairo_pattern_create_for_surface(bgimg->surface);
        cairo_pattern_set_extend(ipat, bx->bg_repeat == CSS_BGR_NO_REPEAT
                                       ? CAIRO_EXTEND_NONE : CAIRO_EXTEND_REPEAT);
        cairo_pattern_set_filter(ipat, CAIRO_FILTER_GOOD);
        cairo_set_source(cr, ipat);
        cairo_paint(cr);
        cairo_pattern_destroy(ipat);
        cairo_restore(cr);
    }

    /* The four borders. With a radius and UNIFORM sides (same width, colour and a
     * visible style on all four) the ring is one rounded stroke centred on the
     * half-width inset; otherwise each side is a filled rect of its width along its
     * edge (square corners). An unset/currentColor color falls back to a dark grey
     * (CSS would use currentColor, but we lack the element's color here). */
    const double bw[4] = { bt, br, bb, bl };
    const int    bs[4] = { bx->bord_ts, bx->bord_rs, bx->bord_bs, bx->bord_ls };
    const int    bc[4] = { bx->bord_tc, bx->bord_rc, bx->bord_bc, bx->bord_lc };
    int uniform = rad > 0.0 && bt > 0.0 && bt == br && bt == bb && bt == bl &&
                  box_line_visible(bs[0]) && bs[0] == bs[1] && bs[0] == bs[2] &&
                  bs[0] == bs[3] && bc[0] == bc[1] && bc[0] == bc[2] && bc[0] == bc[3];
    if (uniform) {
        set_rgb(cr, rgb_from_packed(bc[0] >= 0 ? bc[0] : 0x333333));
        cairo_set_line_width(cr, bt);
        double inner_rad = rad - bt / 2.0;
        box_path(cr, x + bt / 2.0, y + bt / 2.0, w - bt, h - bt,
                 inner_rad > 0.0 ? inner_rad : 0.0);
        cairo_stroke(cr);
    } else {
        for (int k = 0; k < 4; ++k) {
            if (bw[k] <= 0.0 || !box_line_visible(bs[k])) continue;
            set_rgb(cr, rgb_from_packed(bc[k] >= 0 ? bc[k] : 0x333333));
            if      (k == 0) cairo_rectangle(cr, x, y, w, bt);            /* top */
            else if (k == 1) cairo_rectangle(cr, x + w - br, y, br, h);   /* right */
            else if (k == 2) cairo_rectangle(cr, x, y + h - bb, w, bb);   /* bottom */
            else             cairo_rectangle(cr, x, y, bl, h);            /* left */
            cairo_fill(cr);
        }
    }

    /* Outline: stroked just outside the border box, offset by outline_offset
     * (positive pushes the outline further out, negative pulls it inside). */
    double ow = box_edge_px(bx->outline_w);
    if (ow > 0.0 && box_line_visible(bx->outline_style)) {
        set_rgb(cr, rgb_from_packed(bx->outline_color >= 0 ? bx->outline_color : 0x333333));
        cairo_set_line_width(cr, ow);
        double oo = (double)bx->outline_offset;
        box_path(cr, x - ow / 2.0 - oo, y - ow / 2.0 - oo,
                 w + ow + 2.0 * oo, h + ow + 2.0 * oo,
                 rad > 0.0 ? rad + ow / 2.0 + oo : 0.0);
        cairo_stroke(cr);
    }
}

/* Paints the structured document into the content rectangle, honouring scroll. */
/* Paints one laid-out row at vertical position ry. Shared by the on-screen painter
 * and the PDF exporter so both render identically (same fonts, colours, emphasis,
 * links and backgrounds). band_w is the full-bleed width for notice banners (the
 * window width on screen, the page width in the PDF). show_hover draws the link
 * hover highlight (on screen only; suppressed when exporting). */
static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
                              const rc_row *r, double left, double ry,
                              double content_w, double band_w, int show_hover) {
    const ui_theme *th = &w->theme;

    if (r->hidden) return;  /* visibility:hidden: space stood, nothing paints */

    if (r->kind == RC_IMAGE && r->blk != NULL) {
        paint_image_row(cr, w, r->blk, left, ry, content_w, r->height);
        return;
    }
    if (r->kind == RC_VIDEO && r->blk != NULL) {
        paint_video_row(cr, w, r->blk, left, ry, content_w, r->height);
        return;
    }
    if (r->kind == RC_INPUT && r->blk != NULL) {
        draw_input_row(cr, w, r->blk, left, content_w, ry, r->ascent, r->height);
        return;
    }

    if (r->banner) {
        set_rgb(cr, th->notice_bg);
        cairo_rectangle(cr, 0.0, ry, band_w, r->height);
        cairo_fill(cr);
    } else if (r->bg_rgb >= 0) {
        /* Author background-color behind the block's text (content box).
         * Stage 2: r->x_off carries the column offset (flex/grid) OR the
         * positioned box's resolved x. Either way the background sits on
         * top of the same rect the text is drawn in. A container item's
         * background is clipped to its own column (bg_w). */
        double bw = (r->bg_w > 0.0) ? r->bg_w : content_w;
        set_rgb(cr, rgb_from_packed(r->bg_rgb));
        cairo_rectangle(cr, left + r->x_off, ry, bw, r->height);
        cairo_fill(cr);
    }
    double baseline = ry + r->ascent;
    /* row origin (column offset for flex/grid) plus any author text-align shift. */
    double rx = left + r->x_off + row_align_offset(L, r, content_w);
    /* text-align: justify: distribute slack evenly between SPACE characters */
    double jgap = row_justify_gap(L, r, content_w);
    double jdx = 0.0; /* accumulates per-fragment justify shift */
    for (size_t k = r->first; k < r->first + r->count && k < L->nfrag; ++k) {
        const rc_frag *f = &L->frags[k];
        double fx = rx + f->x + jdx;
        /* Highlight the link under the pointer (all fragments of that link share
         * its href pointer into the doc). */
        if (show_hover && f->href != NULL && f->href == w->hover_href) {
            set_rgb(cr, th->link_hover_bg);
            cairo_rectangle(cr, fx, ry, f->width, r->height);
            cairo_fill(cr);
        }
        content_font(cr, f->font_size, f->bold, f->italic, f->family);
        /* vertical-align sub/super shifts this fragment's baseline (and the
         * decorations below); default valign_dy 0 keeps it on the line. */
        double fbaseline = baseline + f->valign_dy;
        /* Accumulate justify offset: count spaces in this fragment */
        if (jgap > 0.0)
            for (size_t i = 0; i < f->len; ++i)
                if (f->text[i] == ' ') jdx += jgap;
        /* Author text-shadow: one offset copy behind the glyphs, in the shadow color
         * (honoring opacity). shadow_color -1 (the default) means no shadow.
         * CC_COLOR_CURRENT (-2) resolves to the fragment's text color. */
        if (f->shadow_color >= 0 || f->shadow_color == CC_COLOR_CURRENT) {
            ui_rgb sc = (f->shadow_color >= 0) ? rgb_from_packed(f->shadow_color) : f->color;
            set_rgb_alpha(cr, sc, f->opacity);
            styled_draw(cr, fx + f->shadow_dx, fbaseline + f->shadow_dy, f);
        }
        set_rgb_alpha(cr, f->color, f->opacity);
        styled_draw(cr, fx, fbaseline, f);
        if (f->underline || f->strike || f->overline) {
            /* Author text-decoration sub-properties override the line stroke:
             * - color -1/CC_COLOR_CURRENT means use the fragment's text color
             * - thickness -1 means use the default 1.0px
             * - style 0 (unset) means solid; CSS_TDS_DASHED/DOTTED use cairo dashes
             *   (CSS_TDS_WAVY/CSS_TDS_DOUBLE fall back to solid in v1). */
            ui_rgb deco_rgb = (f->deco_color >= 0) ? rgb_from_packed(f->deco_color)
                            : (f->deco_color == CC_COLOR_CURRENT) ? f->color
                            : f->color;
            double deco_thick = (f->deco_thick >= 0) ? (double)f->deco_thick : UI_UNDERLINE_THICK;
            set_rgb(cr, deco_rgb);
            cairo_set_line_width(cr, deco_thick);
            cairo_set_line_cap(cr, CAIRO_LINE_CAP_BUTT);
            if (f->deco_style == CSS_TDS_DASHED) {
                double on = 4.0 * deco_thick, off = 2.0 * deco_thick;
                cairo_set_dash(cr, (double[]){ on, off }, 2, 0.0);
            } else if (f->deco_style == CSS_TDS_DOTTED) {
                cairo_set_dash(cr, (double[]){ 0.0, deco_thick * 2.0 }, 2, 0.0);
            } else {
                cairo_set_dash(cr, NULL, 0, 0.0);
            }
            double x0 = fx, x1 = x0 + f->width;
            if (f->underline) {
                double uy = fbaseline + f->font_size * UI_UNDERLINE_OFFSET;
                cairo_move_to(cr, x0, uy); cairo_line_to(cr, x1, uy); cairo_stroke(cr);
            }
            if (f->strike) {
                double sy = fbaseline - f->font_size * UI_STRIKE_OFFSET;
                cairo_move_to(cr, x0, sy); cairo_line_to(cr, x1, sy); cairo_stroke(cr);
            }
            if (f->overline) {
                double oy = fbaseline - f->font_size * UI_OVERLINE_OFFSET;
                cairo_move_to(cr, x0, oy); cairo_line_to(cr, x1, oy); cairo_stroke(cr);
            }
            cairo_set_dash(cr, NULL, 0, 0.0);  /* restore solid for next line */
        }
    }
}

/* Max overflow:hidden nesting depth (anti-DoS). */
#define OV_MAX_DEPTH 16

/* Returns nonzero if a box clips content on either axis. */
static int ov_box_clips(const pv_box_def *d) {
    if (d == NULL) return 0;
    return (d->overflow_x != CSS_OF_VISIBLE && d->overflow_x != CSS_OF_UNSET)
        || (d->overflow_y != CSS_OF_VISIBLE && d->overflow_y != CSS_OF_UNSET);
}

/* Walks the ancestor chain of block_id and collects overflow:hidden box IDs
 * into out[] (outermost first). Returns count, limited to OV_MAX_DEPTH. */
static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap) {
    int tmp[OV_MAX_DEPTH], n = 0;
    for (int id = block_id; id >= 0 && n < cap; ) {
        const pv_box_def *d = rd_box_at(doc, (size_t)id);
        if (d == NULL) break;
        if (ov_box_clips(d)) tmp[n++] = id;
        id = d->parent_id;
    }
    /* tmp is innermost..outermost; reverse to outermost..innermost */
    for (int i = 0; i < n; ++i) out[i] = tmp[n - 1 - i];
    return n;
}

/* Looks up an rc_box by block_id. */
static const rc_box *ov_find_box(const rc_layout *L, int bid) {
    for (size_t i = 0; i < L->nbox; ++i)
        if (L->boxes[i].block_id == bid) return &L->boxes[i];
    return NULL;
}

/* Computes the padding-box content rect (in page coords: y, x, w, h) for a box.
 * Used as the clip region for overflow:hidden children. */
static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            double origin, double left, double *oy, double *ox,
                            double *ow, double *oh) {
    double bl = box_edge_px(d->bord_lw), br = box_edge_px(d->bord_rw);
    double bt = box_edge_px(d->bord_tw), bb = box_edge_px(d->bord_bw);
    double pl = (d->pad_l > 0) ? d->pad_l : 0.0;
    double pr = (d->pad_r > 0) ? d->pad_r : 0.0;
    double pt = (d->pad_t > 0) ? d->pad_t : 0.0;
    double pb = (d->pad_b > 0) ? d->pad_b : 0.0;
    *oy = origin + bx->top + bt + pt;
    *ox = left   + bx->x   + bl + pl;
    double cw = bx->w - bl - br - pl - pr;
    double ch = bx->h - bt - bb - pt - pb;
    *ow = (cw >= 1.0) ? cw : 1.0;
    *oh = (ch >= 1.0) ? ch : 1.0;
}

/* A row's owning box index (pv_box_def), for overflow-clip ancestor lookups and
 * (M1.1 increment 4) stacking-context grouping. rc_row.blk is populated ONLY for
 * RC_IMAGE rows (see its declaration); a text row's owning box instead rides its
 * first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alone silently resolved every text row to "no owning box" (-1),
 * which meant overflow:hidden ancestor clipping never engaged for a plain text
 * row (only for images). -1 when neither is available. */
static int row_owner_block_id(const rc_layout *L, const rc_row *r) {
    if (r->blk != NULL) return (int)r->blk->block_id;
    if (r->count > 0 && r->first < L->nfrag) return L->frags[r->first].block_id;
    return -1;
}

/* Reconciles the cairo overflow clip stack: pops clips that are no longer
 * ancestors of block_id (common-prefix rule), pushes clips for new overflow:
 * hidden ancestors that aren't on the stack yet, outermost first. clip_stack
 * stores block_id of each active overflow:hidden box. */
static void ov_reconcile(cairo_t *cr, int *clip_stack, int *clip_depth,
                         const rd_doc *doc, int block_id,
                         const rc_layout *L, double origin, double left) {
    int new_chain[OV_MAX_DEPTH];
    int new_depth = ov_collect_chain(doc, block_id, new_chain, OV_MAX_DEPTH);

    /* Find common prefix (the outer boxes that are still ancestors of the new
     * block_id and match the current stack). */
    int common = 0;
    while (common < *clip_depth && common < new_depth &&
           clip_stack[common] == new_chain[common])
        ++common;

    /* Pop clips that are no longer on the common prefix (innermost first). */
    while (*clip_depth > common) {
        cairo_restore(cr);
        (*clip_depth)--;
    }

    /* Push new clips (outermost first). Each entry in new_chain beyond the
     * common prefix needs a cairo_save + rectangle clip. */
    for (int k = common; k < new_depth; ++k) {
        const rc_box *bx = ov_find_box(L, new_chain[k]);
        if (bx == NULL) continue;  /* no rc_box (positioned?); clip not possible */
        const pv_box_def *d = rd_box_at(doc, (size_t)new_chain[k]);
        if (d == NULL) continue;
        double cy, cx, cw, ch;
        ov_content_rect(bx, d, origin, left, &cy, &cx, &cw, &ch);
        cairo_save(cr);
        cairo_rectangle(cr, cx, cy, cw, ch);
        cairo_clip(cr);
        clip_stack[*clip_depth] = new_chain[k];
        (*clip_depth)++;
    }
}

/* Does this box need its own offscreen compositing group? Single source of truth:
 * the compositor's cx_forms_stacking_context (spec/compositor.md), fed straight
 * from the box's resolved style -- the same predicate box_tree.c already uses to
 * decide Stage-2 paint ORDER now also decides the painter's compositing MECHANISM.
 * NULL-safe (cx_forms_stacking_context(NULL) is 0). */
static int box_forms_stacking_context(const pv_box_def *def) {
    if (def == NULL) return 0;
    cx_style st = {
        .position = def->position,
        .z_index = (def->z_index == PV_LEN_UNSET) ? 0 : def->z_index,
        .z_auto = (def->z_index == PV_LEN_UNSET) ? 1 : 0,
        .opacity = def->opacity,
        .mix_blend = def->mix_blend,
        .isolation = def->isolation,
        .is_float = 0, .is_inline = 0,
        .has_transform = def->transform_tx != PV_LEN_UNSET ||
                         def->transform_ty != PV_LEN_UNSET ||
                         def->transform_sx != PV_LEN_UNSET ||
                         def->transform_sy != PV_LEN_UNSET ||
                         def->transform_rotate != PV_LEN_UNSET,
    };
    if (def->anim_duration_ms > 0) return 1;  /* Phase R1: animation needs stacking context */
    if (def->filter_blur > 0 || def->filter_grayscale > 0) return 1;  /* R3: filter needs SC */
    return cx_forms_stacking_context(&st);
}

/* transform (M1.2 translate; M1.2b adds scale/rotate): builds the box's full 2D
 * affine transform -- translate, then rotate, then scale, pivoted at the box's
 * own center (CSS's initial transform-origin, 50% 50%, the only pivot this
 * engine supports) -- as a Cairo matrix. Identity when the box has no
 * transform, so callers can apply it unconditionally with no visual change for
 * the untransformed common case. box_x/box_y are the box's DEVICE-space
 * top-left (e.g. ox+bx->x, oy+bx->top -- what paint_box_decoration receives).
 * Forward application (cairo_transform around a box's paint calls) lives at
 * the three call sites below; hit-testing (the inverse) is out of scope for
 * this increment, see include/page_view.h pv_box_def. */
static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
                                 double box_w, double box_h, cairo_matrix_t *m) {
    cairo_matrix_init_identity(m);
    if (def == NULL) return;
    double tx = (def->transform_tx != PV_LEN_UNSET) ? (double)def->transform_tx : 0.0;
    double ty = (def->transform_ty != PV_LEN_UNSET) ? (double)def->transform_ty : 0.0;
    double sx = (def->transform_sx != PV_LEN_UNSET) ? (double)def->transform_sx / 100.0 : 1.0;
    double sy = (def->transform_sy != PV_LEN_UNSET) ? (double)def->transform_sy / 100.0 : 1.0;
    double rot = (def->transform_rotate != PV_LEN_UNSET)
               ? (double)def->transform_rotate * (M_PI / 180.0) : 0.0;
    if (tx == 0.0 && ty == 0.0 && sx == 1.0 && sy == 1.0 && rot == 0.0) return;
    double cx = box_x + box_w / 2.0, cy = box_y + box_h / 2.0;
    cairo_matrix_translate(m, tx, ty);
    cairo_matrix_translate(m, cx, cy);
    cairo_matrix_rotate(m, rot);
    cairo_matrix_scale(m, sx, sy);
    cairo_matrix_translate(m, -cx, -cy);
}

/* Maps CSS mix-blend-mode to the Cairo compositing operator used when a box's
 * offscreen group is blended back over its backdrop. Cairo's separable and
 * non-separable blend operators are a 1:1 match for the CSS values (both trace to
 * the same Porter-Duff/W3C Compositing spec); NORMAL/unset is the ordinary OVER
 * operator every other paint call in this file already uses implicitly. */
static cairo_operator_t bui_blend_operator(int mix_blend) {
    switch (mix_blend) {
        case CSS_MB_MULTIPLY:    return CAIRO_OPERATOR_MULTIPLY;
        case CSS_MB_SCREEN:      return CAIRO_OPERATOR_SCREEN;
        case CSS_MB_OVERLAY:     return CAIRO_OPERATOR_OVERLAY;
        case CSS_MB_DARKEN:      return CAIRO_OPERATOR_DARKEN;
        case CSS_MB_LIGHTEN:     return CAIRO_OPERATOR_LIGHTEN;
        case CSS_MB_COLOR_DODGE: return CAIRO_OPERATOR_COLOR_DODGE;
        case CSS_MB_COLOR_BURN:  return CAIRO_OPERATOR_COLOR_BURN;
        case CSS_MB_DIFFERENCE:  return CAIRO_OPERATOR_DIFFERENCE;
        case CSS_MB_EXCLUSION:   return CAIRO_OPERATOR_EXCLUSION;
        case CSS_MB_HUE:         return CAIRO_OPERATOR_HSL_HUE;
        case CSS_MB_SATURATION:  return CAIRO_OPERATOR_HSL_SATURATION;
        case CSS_MB_COLOR:       return CAIRO_OPERATOR_HSL_COLOR;
        case CSS_MB_LUMINOSITY:  return CAIRO_OPERATOR_HSL_LUMINOSITY;
        default:                  return CAIRO_OPERATOR_OVER;
    }
}

/* Composites the currently-pushed group back onto cr using def's opacity/mix-blend
 * (the group must already be open via cairo_push_group). Restores CAIRO_OPERATOR_OVER
 * afterwards so callers never leak a non-default operator into later paint calls.
 * elapsed_ms: time since page load in ms; used for animation-blended opacity. */
static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms) {
    cairo_pop_group_to_source(cr);
    int eff_opacity = (def ? def->opacity : -1);
    if (def && def->anim_duration_ms > 0) {
        ip_ease_fn ease = { .kind = IP_EASE_LINEAR };
        ip_keyframe kf[] = { {0.0, 0.0}, {100.0, 100.0} };
        ip_anim a;
        ip_anim_init(&a, IP_VAL_SCALAR, &ease, kf, 2,
                     (double)def->anim_duration_ms, 0.0,
                     1, IP_DIR_NORMAL, IP_FILL_FORWARDS);
        ip_anim_tick(&a, (double)elapsed_ms);
        int anim = (int)ip_anim_current(&a);
        if (anim >= 0 && anim <= 100) eff_opacity = anim;
    }
    double alpha = (eff_opacity >= 0 && eff_opacity < 100)
                 ? (double)eff_opacity / 100.0 : 1.0;
    cairo_set_operator(cr, bui_blend_operator(def ? def->mix_blend : CSS_MB_UNSET));
    cairo_paint_with_alpha(cr, alpha);
    cairo_set_operator(cr, CAIRO_OPERATOR_OVER);
}

/* Paints one IN-FLOW box's decoration ONLY (M1.1 increment 4), compositing it
 * through an offscreen group when it forms a stacking context. Used where
 * grouping the box's own rows too (paint_box_and_direct_rows below) isn't worth
 * the added bookkeeping -- currently just the PDF path, whose pagination already
 * anchors box decoration to a page-specific box_oy per box, and which already
 * documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this way still shows the SAME artifact this file's opacity/blend work
 * was written to avoid elsewhere: its background/border fades or blends
 * correctly, but a row's own cascaded background-color (paint_content_row's
 * r->bg_rgb fill, a separate draw call) does not, and paints solid on top. */
static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                                         const rc_box *bx, double ox, double oy) {
    const pv_box_def *def = (bx->block_id >= 0) ? rd_box_at(w->doc, bx->block_id) : NULL;
    const ui_bg_image *bgimg = (def != NULL) ? find_bg_image(w, def->bg_image_url) : NULL;
    if (!box_forms_stacking_context(def)) {
        paint_box_decoration(cr, bx, ox, oy, bgimg);
        return;
    }
    cairo_matrix_t m;
    box_transform_matrix(def, ox + bx->x, oy + bx->top, bx->w, bx->h, &m);
    cairo_push_group(cr);
    cairo_save(cr);
    cairo_transform(cr, &m);
    paint_box_decoration(cr, bx, ox, oy, bgimg);
    cairo_restore(cr);
    bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms);
}

/* Paints one IN-FLOW box's decoration AND every row that belongs directly to it
 * (blk->block_id match), together, when the box forms a stacking context -- so a
 * translucent/blended box's background and its text row(s) fade or blend as ONE
 * coherent unit. Grouping decoration alone is not enough: a row's own background
 * fill (paint_content_row's r->bg_rgb branch) cascades the SAME author
 * background-color as the box, but paints in the caller's separate row pass --
 * left ungrouped, it shows as a solid, un-faded rectangle sitting on top of an
 * otherwise-correctly-translucent box, which looks more broken than doing
 * nothing. Consumed rows are marked in row_done (indexed like L->rows) so the
 * caller's row loop skips them. Glyph color still uses the pre-existing
 * pv_run.opacity/set_rgb_alpha path (untouched, already correct); this only adds
 * the row BACKGROUND and the box's own decoration to the group. Ungrouped boxes
 * are unchanged: paint_box_decoration only, rows stay in the normal row loop.
 * Does not recurse into nested child boxes/their rows -- a full nested layer tree
 * is out of scope, see spec/compositor.md. */
static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
                                      const rc_box *bx, double left, double origin,
                                      double content_w, double page_w,
                                      double content_top, double content_h,
                                      int show_hover, char *row_done) {
    const pv_box_def *def = (bx->block_id >= 0) ? rd_box_at(w->doc, bx->block_id) : NULL;
    const ui_bg_image *bgimg = (def != NULL) ? find_bg_image(w, def->bg_image_url) : NULL;
    if (!box_forms_stacking_context(def)) {
        paint_box_decoration(cr, bx, left, origin, bgimg);
        return;
    }
    cairo_matrix_t m;
    box_transform_matrix(def, left + bx->x, origin + bx->top, bx->w, bx->h, &m);
    /* Cull heuristic only (not a clip): a row's visible vertical range shifts
     * by the translate component when deciding whether to skip an off-screen
     * row. Rotate/scale are ignored here -- worst case a row near the cull
     * boundary is painted (or skipped) a few pixels off from ideal, which the
     * viewport's own clip (established by the caller) still bounds visually. */
    double cull_ty = (def->transform_ty != PV_LEN_UNSET) ? (double)def->transform_ty : 0.0;
    cairo_push_group(cr);
    cairo_save(cr);
    cairo_transform(cr, &m);
    paint_box_decoration(cr, bx, left, origin, bgimg);
    cairo_restore(cr);
    int ov_stack[OV_MAX_DEPTH] = {0};
    int ov_depth = 0;
    for (size_t j = 0; j < L->nrow; ++j) {
        const rc_row *r = &L->rows[j];
        if (row_owner_block_id(L, r) != bx->block_id) continue;
        /* Overflow-clip ancestor resolution stays at the UNTRANSFORMED position
         * (untransformed layout geometry); only the painted content moves. */
        ov_reconcile(cr, ov_stack, &ov_depth, w->doc, bx->block_id, L, origin, left);
        double ry = origin + r->top;
        if (!(ry + cull_ty + r->height < content_top || ry + cull_ty > content_top + content_h)) {
            cairo_save(cr);
            cairo_transform(cr, &m);
            paint_content_row(cr, w, L, r, left, ry, content_w, page_w, show_hover);
            cairo_restore(cr);
        }
        if (row_done != NULL) row_done[j] = 1;
    }
    while (ov_depth > 0) { cairo_restore(cr); ov_depth--; }
    bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms);
}

/* Paints one Stage-2 out-of-flow positioned box: its decoration, then (if it holds
 * a paragraph/heading/link block) one synthetic text row at its content origin. v1
 * only paints the FIRST rd_block whose block_id matches; a positioned box with
 * multiple runs would be a follow-up. Honours overflow:hidden ancestor clipping via
 * ov_reconcile against the caller's clip stack. Shared by the negative-z (paints
 * BEHIND in-flow content) and non-negative-z (paints ABOVE) passes in
 * paint_structured/write_doc_png — CSS 2.1 Appendix E puts negative z-index
 * stacking contexts in a paint-order layer that precedes in-flow content, so the
 * two passes bracket the in-flow painting rather than running back-to-back (see
 * spec/compositor.md and cx_box_layer). No-ops on missing geometry/box-def
 * (fail-open on hostile/malformed input, matching the rest of the painter).
 *
 * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context
 * (box_forms_stacking_context: opacity<1, mix-blend != normal, isolation:isolate,
 * transform != none, or the position+z-index triggers cx_forms_stacking_context
 * already needed for paint ORDER) is composited as ONE unit -- its decoration and
 * content blended together first, then the whole result faded/blended -- not each
 * piece faded independently (naive per-draw alpha double-blends wherever e.g.
 * background and content overlap). cairo_push_group redirects the box's paint
 * calls to a fresh offscreen surface (bounded by the current clip, so this is
 * exactly the "layer" spec/compositor.md describes); bui_pop_group_composite
 * blends that surface back with the box's opacity and mix-blend-mode.
 * box_transform_matrix (M1.2 translate; M1.2b scale/rotate) shifts where
 * decoration/content PAINT -- the box's stored rect used for hit-testing is
 * untouched, see include/page_view.h. */
static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
                                 const bt_positioned *pb, double left, double origin,
                                 double content_top, double content_h, double page_w,
                                 int *clip_stack, int *clip_depth, const rc_layout *L) {
    if (pb->w < 1.0 || pb->h < 1.0) return;
    const pv_box_def *def = rd_box_at(w->doc, pb->box_index);
    if (def == NULL) return;
    /* Constrain the positioned box to its overflow:hidden ancestors. */
    ov_reconcile(cr, clip_stack, clip_depth, w->doc, (int)pb->box_index, L, origin, left);

    int needs_group = box_forms_stacking_context(def);
    cairo_matrix_t m;
    box_transform_matrix(def, left + pb->x, origin + pb->y, pb->w, pb->h, &m);
    /* Cull heuristic only (not a clip), same simplification as
     * paint_box_and_direct_rows: rotate/scale are ignored when deciding
     * whether the synthetic text row below is off-screen. */
    double cull_ty = (def->transform_ty != PV_LEN_UNSET) ? (double)def->transform_ty : 0.0;
    if (needs_group) cairo_push_group(cr);

    /* Build a transient rc_box for the existing paint helper. */
    rc_box bx = {
        .x = pb->x, .top = pb->y, .w = pb->w, .h = pb->h, .block_id = -1,
        .bord_tw = def->bord_tw, .bord_rw = def->bord_rw,
        .bord_bw = def->bord_bw, .bord_lw = def->bord_lw,
        .bord_ts = def->bord_ts, .bord_rs = def->bord_rs,
        .bord_bs = def->bord_bs, .bord_ls = def->bord_ls,
        .bord_tc = def->bord_tc, .bord_rc = def->bord_rc,
        .bord_bc = def->bord_bc, .bord_lc = def->bord_lc,
        .radius = def->border_radius,
        .bsh_dx = def->bsh_dx, .bsh_dy = def->bsh_dy,
        .bsh_blur = def->bsh_blur, .bsh_spread = def->bsh_spread,
        .bsh_color = def->bsh_color, .bsh_inset = def->bsh_inset,
        .outline_w = def->outline_w, .outline_style = def->outline_style,
        .outline_color = def->outline_color,
        .bg_rgb = def->bg_rgb,
        .grad_n = def->grad_n, .grad_angle = def->grad_angle,
        .grad_c = { def->grad_c0, def->grad_c1, def->grad_c2, def->grad_c3 },
        .bg_size = def->bg_size, .bg_repeat = def->bg_repeat,
    };
    if (needs_group) { cairo_save(cr); cairo_transform(cr, &m); }
    paint_box_decoration(cr, &bx, left, origin, find_bg_image(w, def->bg_image_url));
    if (needs_group) cairo_restore(cr);
    for (size_t bi = 0; bi < rd_count(w->doc); ++bi) {
        const rd_block *b = rd_at(w->doc, bi);
        if ((int)b->block_id != (int)pb->box_index) continue;
        if (b->kind != RD_PARAGRAPH && b->kind != RD_HEADING &&
            b->kind != RD_LINK) break;
        rc_frag fg = {
            .x = 0, .width = 0, .font_size = th->body_font,
            .bold = b->bold, .italic = b->italic,
            .underline = 0, .strike = 0, .overline = 0,
            .color = th->text,
            .text = b->text, .len = strlen(b->text),
            .href = b->href, .node_id = b->node_id,
            .family = CSS_FF_UNSET, .transform = 0,
            .letter_spacing = 0, .valign_dy = 0,
            .shadow_dx = 0, .shadow_dy = 0, .shadow_color = -1,
            .opacity = -1,
        };
        content_font(cr, th->body_font, b->bold, b->italic, CSS_FF_UNSET);
        cairo_font_extents_t fe;
        cairo_font_extents(cr, &fe);
        cairo_text_extents_t te;
        cairo_text_extents(cr, b->text, &te);
        fg.width = te.x_advance;
        rc_row row = {
            .kind = RC_TEXT, .top = pb->y, .height = fe.height,
            .ascent = fe.ascent, .first = 0, .count = 1,
            .banner = 0, .bg_rgb = (!w->force_theme) ? b->bg_rgb : -1,
            .x_off = pb->x, .align = 0, .blk = b,
        };
        rc_layout mini = { .frags = &fg, .nfrag = 1, .capfrag = 1,
                           .rows = &row, .nrow = 1, .caprow = 1,
                           .boxes = NULL, .nbox = 0, .capbox = 0,
                           .total_h = pb->h, .npositioned = 0 };
        double ry = origin + pb->y;
        if (ry + cull_ty + fe.height < content_top || ry + cull_ty > content_top + content_h)
            break;
        if (needs_group) { cairo_save(cr); cairo_transform(cr, &m); }
        paint_content_row(cr, w, &mini, &row, left, ry, pb->w, page_w, 0);
        if (needs_group) cairo_restore(cr);
        break;
    }

    if (needs_group) bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms);
}

static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                             double content_h) {
    const ui_theme *th = &w->theme;
    double left = content_margin_x(w);
    double content_w = content_width(w);

    rc_layout L;
    layout_doc(cr, w, content_w, &L);
    position_doc(cr, w, content_w, &L);
    w->content_total_h = L.total_h;  /* cached for the scrollbar */

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    if (w->scroll < 0.0) w->scroll = 0.0;
    if (w->scroll > max_scroll) w->scroll = max_scroll;
    double origin = content_top + th->content_margin - w->scroll;

    /* R4: sticky positioning adjust — clamp sticky boxes to viewport top
     * (inset_top) when scrolled past their natural in-flow position. */
    for (size_t i = 0; i < L.npositioned; ++i) {
        int bid = (int)L.positioned[i].box_index;
        if (bid < 0) continue;
        const pv_box_def *bd = rd_box_at(w->doc, bid);
        if (bd == NULL || bd->position != CSS_POS_STICKY) continue;
        double inset = (bd->inset_top != PV_LEN_UNSET && bd->inset_top != CSS_LEN_AUTO)
                     ? (double)bd->inset_top : 0.0;
        double natural_y = origin + L.positioned[i].y;
        double sticky_y = content_top + inset;
        if (natural_y < sticky_y) L.positioned[i].y = sticky_y - origin;
    }

    /* Stage 2, negative z-index PAINTS FIRST: CSS 2.1 App E layer 1 (NEG_Z)
     * precedes the in-flow BLOCK/FLOAT/INLINE layers, so an overlapping in-flow
     * box or text run must cover a negative-z positioned box, not the other way
     * around. cx_sort (M1.1, box_tree.c) already groups L.positioned by layer, so
     * every z<0 entry is a contiguous prefix of the array. */
    {
        int neg_ov_stack[OV_MAX_DEPTH] = {0};
        int neg_ov_depth = 0;
        for (size_t i = 0; i < L.npositioned && L.positioned[i].z_index < 0; ++i) {
            paint_positioned_one(cr, w, th, &L.positioned[i], left, origin,
                                 content_top, content_h, (double)w->width,
                                 neg_ov_stack, &neg_ov_depth, &L);
        }
        while (neg_ov_depth > 0) { cairo_restore(cr); neg_ov_depth--; }
    }

    /* Overflow clip state: stores block_id of each active overflow:hidden box
     * whose content rect is applied as a cairo clip. clip_depth = number of
     * active saves. Box decorations (borders/bg/shadow) are NOT clipped —
     * CSS paints those outside the padding box; children are clipped inside. */
    int ov_stack[OV_MAX_DEPTH] = {0};
    int ov_depth = 0;

    /* row_done marks rows already painted as part of a grouped box (M1.1
     * increment 4, paint_box_and_direct_rows) so the row loop below doesn't
     * paint them a second time. NULL (calloc(0) or OOM) degrades to "nothing
     * grouped skips" -- every row falls through to the normal ungrouped path,
     * same as before this feature existed. */
    char *row_done = (L.nrow > 0) ? (char *)calloc(L.nrow, 1) : NULL;
    for (size_t i = 0; i < L.nbox; ++i) {
        const rc_box *bx = &L.boxes[i];
        double by = origin + bx->top;
        if (by + bx->h < content_top || by > content_top + content_h) continue;
        paint_box_and_direct_rows(cr, w, &L, bx, left, origin, content_w,
                                  (double)w->width, content_top, content_h,
                                  1, row_done);
    }
    for (size_t i = 0; i < L.nrow; ++i) {
        if (row_done != NULL && row_done[i]) continue;
        const rc_row *r = &L.rows[i];
        /* Each row is clipped to the innermost overflow:hidden ancestor's
         * padding-box (the content rect where children paint). */
        int row_bid = row_owner_block_id(&L, r);
        ov_reconcile(cr, ov_stack, &ov_depth, w->doc, row_bid, &L, origin, left);
        double ry = origin + r->top;
        if (ry + r->height < content_top || ry > content_top + content_h) continue;
        paint_content_row(cr, w, &L, r, left, ry, content_w, (double)w->width, 1);
    }
    free(row_done);
    /* Pop all overflow clips before painting positioned boxes. */
    while (ov_depth > 0) { cairo_restore(cr); ov_depth--; }

    /* Stage 2, non-negative z-index PAINTS ABOVE in-flow content (App E layers
     * ZERO_Z/POS_Z), honouring overflow:hidden ancestor clipping (ov_reconcile) —
     * a positioned box inside e.g. a <div style="overflow:hidden"> is clipped to
     * that ancestor's padding-box. */
    {
        int pos_ov_stack[OV_MAX_DEPTH] = {0};
        int pos_ov_depth = 0;
        for (size_t i = 0; i < L.npositioned; ++i) {
            const bt_positioned *pb = &L.positioned[i];
            if (pb->z_index < 0) continue;  /* already painted behind, above */
            paint_positioned_one(cr, w, th, pb, left, origin,
                                 content_top, content_h, (double)w->width,
                                 pos_ov_stack, &pos_ov_depth, &L);
        }
        while (pos_ov_depth > 0) { cairo_restore(cr); pos_ov_depth--; }
    }
    rc_free(&L);
}

/* PDF page geometry: US Letter at 72 dpi (Cairo's PDF user-space unit is 1 point =
 * 1/72 inch), with a uniform margin. */
#define PDF_PAGE_W  612.0
#define PDF_PAGE_H  792.0
#define PDF_MARGIN  48.0

/* Saves the current page as a vector PDF (selectable text, infinite zoom): Cairo
 * re-draws the SAME render_doc display list onto a cairo_pdf_surface_t instead of
 * the screen. Pure helpers (pdf_export) choose a safe output path from the hostile
 * page title and paginate the rows; this orchestrator only does the Cairo I/O. The
 * page is laid out in a clean light theme so the print is dark-on-white. */
/* Writes the window's current laid-out document to a vector PDF at `path`,
 * paginated to US Letter. Returns the page count (0 when the document lays out to
 * nothing), or -1 on a Cairo error. The page is laid out and coloured in a forced
 * light theme so the print is dark-on-white; the live theme is restored before
 * return. No window/Wayland state is touched -- only w->doc and w->theme are read,
 * through the same layout_doc / paint_content_row the screen uses -- so the GUI
 * "Save as PDF" and the headless --download-pdf path render identically. */
static long write_doc_pdf(browser_window *w, const char *path) {
    cairo_surface_t *surf = cairo_pdf_surface_create(path, PDF_PAGE_W, PDF_PAGE_H);
    if (cairo_surface_status(surf) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(surf);
        return -1;
    }
    cairo_t *cr = cairo_create(surf);

    ui_theme saved = w->theme;
    w->theme = ui_theme_for(UI_THEME_LIGHT);
    const ui_theme *th = &w->theme;

    double content_w = PDF_PAGE_W - 2.0 * PDF_MARGIN;
    double page_content_h = PDF_PAGE_H - 2.0 * PDF_MARGIN;

    rc_layout L;
    layout_doc(cr, w, content_w, &L);
    position_doc(cr, w, content_w, &L);

    size_t pages = 0;
    double *tops = NULL, *heights = NULL, *yof = NULL;
    int *pageof = NULL;
    if (L.nrow > 0) {
        tops    = (double *)calloc(L.nrow, sizeof *tops);
        heights = (double *)calloc(L.nrow, sizeof *heights);
        yof     = (double *)calloc(L.nrow, sizeof *yof);
        pageof  = (int *)calloc(L.nrow, sizeof *pageof);
    }
    if (L.nrow > 0 && tops != NULL && heights != NULL && yof != NULL && pageof != NULL) {
        for (size_t i = 0; i < L.nrow; ++i) {
            tops[i] = L.rows[i].top;
            heights[i] = L.rows[i].height;
        }
        pages = pe_paginate(tops, heights, L.nrow, page_content_h, pageof, yof);
        for (size_t p = 0; p < pages; ++p) {
            cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); /* white page */
            cairo_paint(cr);
            /* Box decoration first (behind the rows): a box is placed on the page of
             * its first enclosed row, offset to keep its rect aligned with that row. */
            for (size_t bi = 0; bi < L.nbox; ++bi) {
                const rc_box *bx = &L.boxes[bi];
                size_t k = L.nrow;
                for (size_t i = 0; i < L.nrow; ++i) {
                    if (L.rows[i].top >= bx->top && L.rows[i].top < bx->top + bx->h) { k = i; break; }
                }
                if (k == L.nrow || (size_t)pageof[k] != p) continue;
                /* paint_box_decoration adds bx->top to oy, so oy maps the box's layout
                 * top to the same page line as its first enclosed row. */
                double box_oy = PDF_MARGIN + yof[k] - L.rows[k].top;
                paint_box_decoration_grouped(cr, w, bx, PDF_MARGIN, box_oy);
            }
            /* Note: overflow:hidden clipping is NOT applied to the PDF export in v1
             * because PDF pagination uses per-page Y offsets (yof[i]) and per-box
             * first-row anchors (box_oy above), which would need per-box clip-rect
             * recalculation at each page boundary. The on-screen (paint_structured)
             * and PNG (write_doc_png) paths DO honour overflow:hidden. */
            for (size_t i = 0; i < L.nrow; ++i) {
                if ((size_t)pageof[i] != p) continue;
                paint_content_row(cr, w, &L, &L.rows[i], PDF_MARGIN,
                                  PDF_MARGIN + yof[i], content_w, PDF_PAGE_W, 0);
            }
            /* Stage 2: out-of-flow positioned boxes (v1: painted on every page; a
             * positioned box that should only appear on one specific page is a
             * follow-up). z_index < 0 is skipped -- PDF v1 doesn't reproduce the
             * on-screen/PNG "paints behind in-flow" ordering across page
             * boundaries (an omission, not a wrong-order bug). Reuses
             * paint_positioned_one (same helper as the on-screen/PNG paths), so
             * overflow:hidden ancestor clipping and stacking-context group
             * compositing (opacity/mix-blend) are no longer PDF-only gaps -- a
             * fresh page starts with a fresh clip stack, so per-page
             * reconciliation is safe (no cross-page clip leakage). */
            int pdf_pos_ov_stack[OV_MAX_DEPTH] = {0};
            int pdf_pos_ov_depth = 0;
            for (size_t pi = 0; pi < L.npositioned; ++pi) {
                const bt_positioned *pb = &L.positioned[pi];
                if (pb->z_index < 0) continue;
                paint_positioned_one(cr, w, th, pb, PDF_MARGIN, PDF_MARGIN,
                                     -1e9, 2e9, PDF_PAGE_W,
                                     pdf_pos_ov_stack, &pdf_pos_ov_depth, &L);
            }
            while (pdf_pos_ov_depth > 0) { cairo_restore(cr); pdf_pos_ov_depth--; }
            cairo_show_page(cr);
        }
    }

    free(tops); free(heights); free(yof); free(pageof);
    rc_free(&L);
    w->theme = saved;
    cairo_destroy(cr);
    cairo_surface_destroy(surf);
    return (long)pages;
}

static void export_pdf(browser_window *w) {
    if (w->doc == NULL || rd_count(w->doc) == 0) {
        browser_set_status(&w->bs, "Nothing to export to PDF.", now_ms());
        redraw(w);
        return;
    }

    /* Output directory: $XDG_DOWNLOAD_DIR, else $HOME, else the current directory. */
    const char *dir = getenv("XDG_DOWNLOAD_DIR");
    if (dir == NULL || dir[0] == '\0') dir = getenv("HOME");
    if (dir == NULL || dir[0] == '\0') dir = ".";

    /* The page title is hostile remote content; pe_build_path sanitises it into a
     * safe basename (no traversal/separators/hidden) -- fail-closed by design. */
    const char *title = (w->bs.page_title != NULL && w->bs.page_title[0] != '\0')
                        ? w->bs.page_title : PE_FALLBACK_NAME;
    char path[PE_NAME_MAX + 4096u];
    if (pe_build_path(dir, title, path, sizeof path) != PE_OK) {
        browser_set_status(&w->bs, "Could not build a safe PDF path.", now_ms());
        redraw(w);
        return;
    }

    long pages = write_doc_pdf(w, path);

    char msg[PE_NAME_MAX + 4096u + 64u];
    if (pages < 0) {
        snprintf(msg, sizeof msg, "Could not create the PDF file.");
    } else if (pages > 0) {
        snprintf(msg, sizeof msg, "Saved PDF (%ld page%s): %s",
                 pages, pages == 1 ? "" : "s", path);
    } else {
        snprintf(msg, sizeof msg, "Nothing to export to PDF.");
    }
    browser_set_status(&w->bs, msg, now_ms());
    redraw(w);
}

/* PNG raster geometry: a single continuous bitmap (not paginated) of the whole
 * page, sized to the laid-out content. The width fixes the wrap column; the height
 * follows the content but is capped so a hostile page cannot force an unbounded
 * allocation (a taller page is clipped at PNG_MAX_H). */
#define PNG_PAGE_W   1000.0
#define PNG_MARGIN   24.0
#define PNG_MAX_H    30000   /* px; 1000 * 30000 * 4B ~= 120 MiB worst case */

/* Writes the window's current laid-out document to a single full-height PNG at
 * `path` (the same layout/paint path as the screen and the PDF export, in a forced
 * light theme so it is dark-on-white). Returns the image height in px (0 when the
 * document lays out to nothing), or -1 on a Cairo error. No Wayland state is
 * touched -- only w->doc and w->theme are read. */
static long write_doc_png(browser_window *w, const char *path) {
    ui_theme saved = w->theme;
    w->theme = ui_theme_for(UI_THEME_LIGHT);
    const ui_theme *th = &w->theme;
    double content_w = PNG_PAGE_W - 2.0 * PNG_MARGIN;

    /* layout_doc needs a live Cairo context to measure text (font extents), but the
     * image height is unknown until after layout. Measure on a scratch 1x1 surface
     * (image-surface font metrics are size-independent), then paint on a surface
     * sized to the result. */
    cairo_surface_t *meas = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cairo_t *mcr = cairo_create(meas);
    rc_layout L;
    layout_doc(mcr, w, content_w, &L);
    position_doc(mcr, w, content_w, &L);
    double content_h = L.total_h;
    cairo_destroy(mcr);
    cairo_surface_destroy(meas);

    if (L.nrow == 0 || content_h <= 0.0) { rc_free(&L); w->theme = saved; return 0; }

    long img_h = (long)(content_h + 2.0 * PNG_MARGIN + 0.5);
    if (img_h > PNG_MAX_H) img_h = PNG_MAX_H;

    cairo_surface_t *surf =
        cairo_image_surface_create(CAIRO_FORMAT_ARGB32, (int)PNG_PAGE_W, (int)img_h);
    if (cairo_surface_status(surf) != CAIRO_STATUS_SUCCESS) {
        cairo_surface_destroy(surf); rc_free(&L); w->theme = saved; return -1;
    }
    cairo_t *cr = cairo_create(surf);
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);   /* white page */
    cairo_paint(cr);

    /* PNG export never scrolls/culls, so pass a viewport wide enough that
     * paint_positioned_one's culling check never trips. */
    const double no_cull_top = -1e9, no_cull_h = 2e9;

    /* Stage 2, negative z-index PAINTS FIRST -- see paint_structured for the App E
     * rationale; cx_sort groups L.positioned by layer, so z<0 is a prefix. */
    {
        int neg_ov_stack[OV_MAX_DEPTH] = {0};
        int neg_ov_depth = 0;
        for (size_t i = 0; i < L.npositioned && L.positioned[i].z_index < 0; ++i) {
            paint_positioned_one(cr, w, th, &L.positioned[i], PNG_MARGIN, PNG_MARGIN,
                                 no_cull_top, no_cull_h, PNG_PAGE_W,
                                 neg_ov_stack, &neg_ov_depth, &L);
        }
        while (neg_ov_depth > 0) { cairo_restore(cr); neg_ov_depth--; }
    }

    /* Box decoration first (behind the rows), then the rows, at a constant origin
     * (no pagination): both use PNG_MARGIN + their layout-space top. row_done (see
     * paint_structured) marks rows already painted as part of a grouped box. */
    char *row_done = (L.nrow > 0) ? (char *)calloc(L.nrow, 1) : NULL;
    for (size_t bi = 0; bi < L.nbox; ++bi)
        paint_box_and_direct_rows(cr, w, &L, &L.boxes[bi], PNG_MARGIN, PNG_MARGIN,
                                  content_w, PNG_PAGE_W, no_cull_top, no_cull_h,
                                  0, row_done);
    {
        int ov_stack[OV_MAX_DEPTH] = {0};
        int ov_depth = 0;
        for (size_t i = 0; i < L.nrow; ++i) {
            if (row_done != NULL && row_done[i]) continue;
            const rc_row *r = &L.rows[i];
            int row_bid = row_owner_block_id(&L, r);
            ov_reconcile(cr, ov_stack, &ov_depth, w->doc, row_bid, &L,
                         PNG_MARGIN, PNG_MARGIN);
            paint_content_row(cr, w, &L, r, PNG_MARGIN,
                              PNG_MARGIN + r->top, content_w, PNG_PAGE_W, 0);
        }
        while (ov_depth > 0) { cairo_restore(cr); ov_depth--; }
        free(row_done);
    }
    /* Stage 2, non-negative z-index PAINTS ABOVE in-flow content (same as
     * paint_structured). Honours overflow:hidden ancestors via ov_reconcile. */
    {
        int pos_ov_stack[OV_MAX_DEPTH] = {0};
        int pos_ov_depth = 0;
        for (size_t pi = 0; pi < L.npositioned; ++pi) {
            const bt_positioned *pb = &L.positioned[pi];
            if (pb->z_index < 0) continue;  /* already painted behind, above */
            paint_positioned_one(cr, w, th, pb, PNG_MARGIN, PNG_MARGIN,
                                 no_cull_top, no_cull_h, PNG_PAGE_W,
                                 pos_ov_stack, &pos_ov_depth, &L);
        }
        while (pos_ov_depth > 0) { cairo_restore(cr); pos_ov_depth--; }
    }

    cairo_destroy(cr);
    cairo_status_t st = cairo_surface_write_to_png(surf, path);
    cairo_surface_destroy(surf);
    rc_free(&L);
    w->theme = saved;
    return (st == CAIRO_STATUS_SUCCESS) ? img_h : -1;
}

static void export_png(browser_window *w) {
    if (w->doc == NULL || rd_count(w->doc) == 0) {
        browser_set_status(&w->bs, "Nothing to export to PNG.", now_ms());
        redraw(w);
        return;
    }

    const char *dir = getenv("XDG_DOWNLOAD_DIR");
    if (dir == NULL || dir[0] == '\0') dir = getenv("HOME");
    if (dir == NULL || dir[0] == '\0') dir = ".";

    /* The page title is hostile remote content; pe_build_path_ext sanitises it into
     * a safe basename (no traversal/separators/hidden) -- fail-closed by design. */
    const char *title = (w->bs.page_title != NULL && w->bs.page_title[0] != '\0')
                        ? w->bs.page_title : PE_FALLBACK_NAME;
    char path[PE_NAME_MAX + 4096u];
    if (pe_build_path_ext(dir, title, PE_EXT_PNG, path, sizeof path) != PE_OK) {
        browser_set_status(&w->bs, "Could not build a safe PNG path.", now_ms());
        redraw(w);
        return;
    }

    long h = write_doc_png(w, path);
    char msg[PE_NAME_MAX + 4096u + 64u];
    if (h < 0)        snprintf(msg, sizeof msg, "Could not create the PNG file.");
    else if (h > 0)   snprintf(msg, sizeof msg, "Saved PNG (%ld px): %s", h, path);
    else              snprintf(msg, sizeof msg, "Nothing to export to PNG.");
    browser_set_status(&w->bs, msg, now_ms());
    redraw(w);
}

/* Headless PDF export (no Wayland; see include/ui.h). Renders an already-built
 * render document to a vector PDF at out_path, reusing the exact on-screen
 * layout/paint path so what the file shows is what the window would paint. The
 * caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path verbatim (a trusted local path, not derived from the hostile title). */
ui_status ui_render_pdf(const rd_doc *doc, const char *out_path, long *out_pages) {
    if (out_pages != NULL) *out_pages = 0;
    if (doc == NULL || out_path == NULL || rd_count(doc) == 0) return UI_ERR_NULL_ARG;

    /* A zeroed window is enough for layout/paint: no images (placeholders drawn),
     * no inputs, no hover, light theme. write_doc_pdf touches no Wayland state. */
    browser_window w;
    memset(&w, 0, sizeof w);
    w.theme = ui_theme_for(UI_THEME_LIGHT);
    w.doc = (rd_doc *)doc;   /* read-only here; write_doc_pdf never mutates the doc */
    w.focused_input = -1;

    long pages = write_doc_pdf(&w, out_path);
    if (pages < 0) return UI_ERR_INTERNAL;
    if (out_pages != NULL) *out_pages = pages;
    return UI_OK;
}

/* Headless PNG export (no Wayland; see include/ui.h). One full-height bitmap of the
 * whole page, the cheapest artifact for visual review (no PDF rasterise step). Same
 * zeroed-window setup as ui_render_pdf. */
ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h) {
    if (out_h != NULL) *out_h = 0;
    if (doc == NULL || out_path == NULL || rd_count(doc) == 0) return UI_ERR_NULL_ARG;

    browser_window w;
    memset(&w, 0, sizeof w);
    w.theme = ui_theme_for(UI_THEME_LIGHT);
    w.doc = (rd_doc *)doc;   /* read-only here; write_doc_png never mutates the doc */
    w.focused_input = -1;

    long h = write_doc_png(&w, out_path);
    if (h < 0) return UI_ERR_INTERNAL;
    if (out_h != NULL) *out_h = h;
    return UI_OK;
}

/* Headless PNG/PDF export WITH image decoding (see include/ui.h). Unlike the plain
 * ui_render_png/pdf (which always draw placeholders), these decode the page's allowed
 * images through the still-open confined worker `t` -- the hostile image bytes never
 * touch this process -- exactly as the on-screen window does. Remote image bytes come
 * from `img_fetch` (the caller's policy-applying fetcher, e.g. headless_fetch); local
 * file:// images are read from disk (confined to the document directory by render_doc).
 * top_url is the page origin (https or file://); a NULL origin loads no images. Any
 * image that fails falls back to its placeholder, byte-identical to the window path.
 * The zeroed window mirrors ui_render_png; cur_top drives the local-vs-remote branch in
 * load_images and is released before returning. */
static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
                                   tab_fetch_fn img_fetch, void *fetch_ctx,
                                   const char *out_path, int as_pdf, long *out_metric) {
    if (out_metric != NULL) *out_metric = 0;
    if (doc == NULL || out_path == NULL || rd_count(doc) == 0) return UI_ERR_NULL_ARG;

    browser_window w;
    memset(&w, 0, sizeof w);
    w.theme = ui_theme_for(UI_THEME_LIGHT);
    w.doc = (rd_doc *)doc;
    w.focused_input = -1;
    w.cur_top = (top_url != NULL) ? strdup(top_url) : NULL;

    /* Decode allowed images into w.images (fetch/read + worker decode); a failure per
     * image just leaves surface == NULL and its placeholder is drawn. Background-images
     * (2026-07-16) follow the same path so --download-png/--download-pdf --images can
     * actually verify them headless, not just <img>. */
    if (t != NULL && img_fetch != NULL) {
        load_images(&w, t, img_fetch, fetch_ctx);
        load_bg_images(&w, t, img_fetch, fetch_ctx);
    }

    long metric = as_pdf ? write_doc_pdf(&w, out_path) : write_doc_png(&w, out_path);
    free_images(&w);
    free_bg_images(&w);
    free(w.cur_top);
    if (metric < 0) return UI_ERR_INTERNAL;
    if (out_metric != NULL) *out_metric = metric;
    return UI_OK;
}

ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                               tab_fetch_fn img_fetch, void *fetch_ctx,
                               const char *out_path, long *out_h) {
    return render_doc_images(doc, t, top_url, img_fetch, fetch_ctx, out_path, 0, out_h);
}

ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                               tab_fetch_fn img_fetch, void *fetch_ctx,
                               const char *out_path, long *out_pages) {
    return render_doc_images(doc, t, top_url, img_fetch, fetch_ctx, out_path, 1, out_pages);
}

/* Headless layout dump: runs the same layout_doc + position_doc pass as the
 * on-screen/PNG renderer and prints the resolved box geometry (in-flow boxes and
 * out-of-flow positioned boxes) to stdout as agent-readable text. This is the
 * layout-side counterpart to --dump-dom (which prints the pre-layout render
 * tree): it makes the EFFECT of the layout engine verifiable without a display or
 * a rasterised image (CI, an AI agent) — the Stacking/positioning bugs that a PNG
 * would reveal are inspectable as plain numbers. See `--dump-layout` in
 * spec/freedom.md. Pure I/O on already-resolved, already-fuzzed data; no socket,
 * no file, no mutation of the doc. */
ui_status ui_dump_layout(const rd_doc *doc) {
    if (doc == NULL || rd_count(doc) == 0) return UI_ERR_NULL_ARG;

    browser_window w;
    memset(&w, 0, sizeof w);
    w.theme = ui_theme_for(UI_THEME_LIGHT);
    w.doc = (rd_doc *)doc;   /* read-only; layout_doc/position_doc never mutate it */
    w.focused_input = -1;

    double content_w = PNG_PAGE_W - 2.0 * PNG_MARGIN;
    cairo_surface_t *meas = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cairo_t *cr = cairo_create(meas);
    rc_layout L;
    layout_doc(cr, &w, content_w, &L);
    position_doc(cr, &w, content_w, &L);
    cairo_destroy(cr);
    cairo_surface_destroy(meas);

    printf("=== Freedom layout ===\n");
    printf("content_w=%.0f total_h=%.1f nbox=%zu nrow=%zu npositioned=%zu\n",
           content_w, L.total_h, L.nbox, L.nrow, L.npositioned);
    /* Rows are the resolved line geometry — x_off/bg_w expose the flex/grid column
     * a line landed in (Stage 3), which no other dump shows. Text stays out (it is
     * --dump-dom's job); geometry only, one line per row, agent-parseable. */
    for (size_t i = 0; i < L.nrow; ++i) {
        const rc_row *r = &L.rows[i];
        printf("  row[%zu] top=%.1f h=%.1f x_off=%.1f", i, r->top, r->height, r->x_off);
        if (r->bg_w > 0.0) printf(" w=%.1f", r->bg_w);
        if (r->kind == RC_IMAGE) printf(" image");
        printf("\n");
    }
    for (size_t i = 0; i < L.nbox; ++i) {
        const rc_box *b = &L.boxes[i];
        printf("  box[%zu] bid=%d x=%.1f top=%.1f w=%.1f h=%.1f\n",
               i, b->block_id, b->x, b->top, b->w, b->h);
    }
    for (size_t i = 0; i < L.npositioned; ++i) {
        const bt_positioned *p = &L.positioned[i];
        printf("  pos[%zu] box=%zu z=%d x=%.1f y=%.1f w=%.1f h=%.1f\n",
               i, p->box_index, p->z_index, p->x, p->y, p->w, p->h);
    }
    rc_free(&L);
    return UI_OK;
}

/* Returns the link target under the surface point (px, py), or NULL when the
 * point is outside the content area or not over a link fragment. The layout and
 * scroll clamping mirror paint_structured exactly, so the hit matches what is on
 * screen. The returned pointer aliases the current rd_doc (it is not owned) and
 * stays valid until the document is replaced; the caller must resolve it before
 * triggering a load that frees the document. */
static int box_pointer_events_none(const rd_doc *doc, int block_id);

static const char *link_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return NULL;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return NULL;

    const ui_theme *th = &w->theme;
    double left = content_margin_x(w);
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + th->content_margin - scroll;

    const char *hit = NULL;
    for (size_t i = 0; i < L.nrow && hit == NULL; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_TEXT) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        double ax = row_align_offset(&L, r, content_w);
        double jgap = row_justify_gap(&L, r, content_w);
        double jdx = 0.0;
        for (size_t k = r->first; k < r->first + r->count && k < L.nfrag; ++k) {
            const rc_frag *f = &L.frags[k];
            double fx = left + r->x_off + ax + f->x + jdx;
            if (f->href != NULL && !box_pointer_events_none(w->doc, f->block_id)
                && px >= fx && px <= fx + f->width) { hit = f->href; break; }
            for (size_t j = 0; j < f->len; ++j)
                if (f->text[j] == ' ') jdx += jgap;
        }
    }

    rc_free(&L);
    cairo_destroy(cr);
    return hit;
}

/* Returns the video source URL when the point (px, py) falls on an RC_VIDEO row,
 * or NULL. The caller should call video_play with the returned URL. The returned
 * string aliases the currently rendered document (w->doc), valid until the doc
 * is rebuilt or freed. */
static const char *video_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return NULL;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return NULL;

    const ui_theme *th = &w->theme;
    double left = content_margin_x(w);
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + th->content_margin - scroll;

    (void)left;
    (void)px;
    (void)content_w;
    const char *hit = NULL;
    for (size_t i = 0; i < L.nrow && hit == NULL; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_VIDEO || r->blk == NULL) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        hit = r->blk->href;
    }

    rc_free(&L);
    cairo_destroy(cr);
    return hit;
}

/* First non-unset author `cursor` on block_id's box or an ancestor (nearest wins,
 * like the rest of the box-decoration fields), or CSS_CUR_UNSET if none set the
 * property or block_id < 0. Bounded by the box-def parent chain (RC_BOX_STACK_MAX,
 * same cap as every other box-path walk here). */
static int resolve_box_cursor(const rd_doc *doc, int block_id) {
    for (int id = block_id, n = 0; id >= 0 && n < RC_BOX_STACK_MAX; ++n) {
        const pv_box_def *d = rd_box_at(doc, (size_t)id);
        if (d == NULL) break;
        if (d->cursor != CSS_CUR_UNSET) return d->cursor;
        id = d->parent_id;
    }
    return CSS_CUR_UNSET;
}

/* True when author `pointer-events: none` removes block_id's content from
 * hit-testing (2026-07-10): the nearest box in the parent chain that sets the
 * property wins, exactly like resolve_box_cursor. The box tree only exists with
 * caps.css, so the default render hit-tests everything (byte-identical). */
static int box_pointer_events_none(const rd_doc *doc, int block_id) {
    for (int id = block_id, n = 0; id >= 0 && n < RC_BOX_STACK_MAX; ++n) {
        const pv_box_def *d = rd_box_at(doc, (size_t)id);
        if (d == NULL) break;
        if (d->pointer_events != CSS_PE_UNSET) return d->pointer_events == CSS_PE_NONE;
        id = d->parent_id;
    }
    return 0;
}

/* Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET
 * when outside content / no box sets one. Unlike link_at_point this tests EVERY
 * fragment (not just linked ones): cursor:pointer commonly styles a non-link
 * clickable element (a JS-driven button/div). A separate layout+hit-test walk from
 * link_at_point/node_at_point (matching this file's existing per-purpose hit-test
 * style); update_hover calls all it needs once per pointer-motion event. */
static int cursor_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return CSS_CUR_UNSET;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return CSS_CUR_UNSET;

    const ui_theme *th = &w->theme;
    double left = content_margin_x(w);
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + th->content_margin - scroll;

    int cur = CSS_CUR_UNSET;
    for (size_t i = 0; i < L.nrow && cur == CSS_CUR_UNSET; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_TEXT) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        double ax = row_align_offset(&L, r, content_w);
        double jgap = row_justify_gap(&L, r, content_w);
        double jdx = 0.0;
        for (size_t k = r->first; k < r->first + r->count && k < L.nfrag; ++k) {
            const rc_frag *f = &L.frags[k];
            double fx = left + r->x_off + ax + f->x + jdx;
            if (!box_pointer_events_none(w->doc, f->block_id)
                && px >= fx && px <= fx + f->width) {
                cur = resolve_box_cursor(w->doc, f->block_id);
                break;
            }
            for (size_t j = 0; j < f->len; ++j)
                if (f->text[j] == ' ') jdx += jgap;
        }
    }

    rc_free(&L);
    cairo_destroy(cr);
    return cur;
}

/* Returns the DOM node id of the element under (px, py), or DOM_NODE_NONE if the
 * point is over blank space / outside content. Mirrors layout and scroll clamping
 * exactly so the hit matches the painted frame. */
static dom_node_id node_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return DOM_NODE_NONE;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return DOM_NODE_NONE;

    double left = content_margin_x(w);
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + w->theme.content_margin - scroll;

    dom_node_id hit = DOM_NODE_NONE;
    for (size_t i = 0; i < L.nrow && hit == DOM_NODE_NONE; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_TEXT) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        double ax = row_align_offset(&L, r, content_w);
        double jgap = row_justify_gap(&L, r, content_w);
        double jdx = 0.0;
        for (size_t k = r->first; k < r->first + r->count && k < L.nfrag; ++k) {
            const rc_frag *f = &L.frags[k];
            double fx = left + r->x_off + ax + f->x + jdx;
            if (f->node_id != DOM_NODE_NONE && !box_pointer_events_none(w->doc, f->block_id)
                && px >= fx && px <= fx + f->width) { hit = f->node_id; break; }
            for (size_t j = 0; j < f->len; ++j)
                if (f->text[j] == ' ') jdx += jgap;
        }
    }

    rc_free(&L);
    cairo_destroy(cr);
    return hit;
}

/* Resolves a clicked link's raw href against the current page location through
 * the pure navigation policy and, only when it yields a navigable target, records
 * the navigation and performs the load. A same-document fragment or a blocked
 * reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content cannot drive an unsafe load. */
static void follow_link(browser_window *w, const char *href) {
    ln_result res;
    if (ln_resolve(browser_current_url(&w->bs), href, &res) != LN_OK) return;
    if (res.action == LN_BLOCKED) {
        /* Tell the user why an unsafe link did nothing (the toast auto-hides). */
        browser_set_status(&w->bs, ln_block_reason_text(res.reason), now_ms());
        return;
    }
    /* A same-document fragment stays on the page (res.fragment carries the anchor
     * id for a future scroll); only a real target navigates. */
    if (res.action != LN_NAVIGATE) return;
    if (browser_navigate(&w->bs, res.target) != BROWSER_OK) return;
    do_load(w, res.target);
}

/* Applies a click result returned by the worker: rebuild the rendered document and
 * refresh inputs/console, but keep the current page in history (a click is not a
 * navigation). Images are not re-fetched: a click handler may add text, but v1 does
 * not introduce new remote images. */
static void apply_click_result(browser_window *w, tab_page *page) {
    if (w->doc != NULL) { rd_free(w->doc); w->doc = NULL; }
    w->hover_href = NULL; /* aliased the doc we just freed; recomputed on next hover */
    w->hover_cursor = CSS_CUR_UNSET;
    rdp_caps eff = w->caps;
    if (w->reader) { eff.css = false; eff.images = false; }
    rd_doc *doc = NULL;
    if (rd_build(page->view, eff, w->cur_top, &doc) == RD_OK) {
        w->doc = doc;
    }
    rebuild_inputs(w);
    fb_buffer_free(&w->console);
    w->console = page->console;
    fb_buffer_init(&page->console);
    browser_set_page(&w->bs, page->title, page->text, 0);
    /* Handlers may have (re)armed timers: schedule the next tick from the report. */
    schedule_js_tick(w, page->next_timer_ms);
}

/* Dispatches a click to the live worker for the node under the cursor. If the node
 * is a link and the handler does not prevent the default, the link is followed.
 * The link target aliases w->doc, which apply_click_result frees when it rebuilds
 * the view; own a copy up front so following the link afterward never reads freed
 * memory (the href pointer, not its contents, was all the old code preserved). */
static void dispatch_click(browser_window *w, double px, double py) {
    /* Check video click (play button / placeholder) before dispatching to the
     * worker, since video blocks have no text fragments for node_at_point. */
    const char *video_url = video_at_point(w, px, py);
    if (video_url != NULL) {
        video_play(w, video_url);
        return;
    }

    if (w->tab_worker == NULL) return;
    dom_node_id nid = node_at_point(w, px, py);
    if (nid == DOM_NODE_NONE) return;

    const char *href_alias = link_at_point(w, px, py);
    char *href = (href_alias != NULL) ? strdup(href_alias) : NULL;

    tab_page page;
    memset(&page, 0, sizeof page);
    if (tab_click(w->tab_worker, nid, &page) != TAB_OK) {
        browser_set_status(&w->bs, "Click handler failed.", now_ms());
        free(href);
        return;
    }

    apply_click_result(w, &page);
    tab_page_free(&page);
    if (href != NULL) follow_link(w, href);
    free(href);
}

/* Returns the painted form control under (px, py), or NULL. Mirrors the layout and
 * scroll clamping of paint_structured so the hit matches what is on screen. The
 * returned block aliases the current rd_doc (not owned). */
static const rd_block *input_at_point(browser_window *w, double px, double py) {
    if (w->doc == NULL || w->cairo_surface == NULL) return NULL;

    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);
    if (py < content_top || py > content_top + content_h) return NULL;

    const ui_theme *th = &w->theme;
    double left = content_margin_x(w);
    double content_w = content_width(w);

    cairo_t *cr = cairo_create(w->cairo_surface);
    rc_layout L;
    layout_doc(cr, w, content_w, &L);

    double max_scroll = L.total_h - content_h;
    if (max_scroll < 0.0) max_scroll = 0.0;
    double scroll = w->scroll;
    if (scroll < 0.0) scroll = 0.0;
    if (scroll > max_scroll) scroll = max_scroll;
    double origin = content_top + th->content_margin - scroll;

    const rd_block *hit = NULL;
    for (size_t i = 0; i < L.nrow && hit == NULL; ++i) {
        const rc_row *r = &L.rows[i];
        if (r->kind != RC_INPUT || r->blk == NULL) continue;
        double ry = origin + r->top;
        if (py < ry || py > ry + r->height) continue;
        const rd_block *b = r->blk;
        double bw = (b->input_type == PV_IN_SUBMIT || b->input_type == PV_IN_BUTTON)
                    ? button_box_width(cr, th, b, content_w)
                    : input_box_width(content_w);
        if (px >= left && px <= left + bw) hit = b;
    }

    rc_free(&L);
    cairo_destroy(cr);
    return hit;
}

/* Submits a POST plan ASYNCHRONOUSLY (same model as do_load): the pre-fetch gates run
 * here, then the blocking POST goes to a worker thread and the result is rendered by
 * deliver_fetch_result. Goes through the SAME gates as a GET (host filter, exception,
 * allowlist, Tor/I2P realm route) and the SAME navigability fallbacks: a POST to a
 * .onion is routed through Tor instead of failing SF_ERR_NETWORK, and never reaches
 * the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_window *w, const fm_plan *plan) {
    w->net_gen++;        /* new navigation: supersede any in-flight fetch */
    w->menu_open = 0;

    sf_config cfg;
    fetch_prep pr;
    if (!prepare_fetch(w, plan->url, &cfg, &pr)) {
        clear_doc(w);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1; w->loading = 0;
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, pr.err, 1);
        return;
    }

    if (!fetch_launch(w, plan->url, &cfg, pr.allowlisted, 1,
                      plan->body, plan->body_len, plan->content_type)) {
        clear_doc(w);
        w->scroll = 0.0; w->loading = 0;
        set_cache(w, NULL, 0, NULL);
        browser_set_page(&w->bs, NULL, "Could not start the POST (out of resources).", 1);
        return;
    }
    show_busy(w); /* spinner on; the form page stays visible until the response lands */
}

/* Renders a completed fetch on the main thread. A result whose generation no longer
 * matches w->net_gen is silently dropped: the user navigated again or switched tabs,
 * so the active tab is no longer this job's target (fail safe -- never paint a stale
 * or wrong-tab page). On success the page is rendered in place; a POST redirect is
 * followed as a fresh async GET (re-applying the full policy, Zero Trust). */
/* Builds ~/Downloads/freedom into out and creates both levels (best effort; an
 * existing directory is fine). Returns 1 on success. Falls back to $HOME or "."
 * for the base, matching export_pdf's directory choice. */
static int ensure_download_dir(char *out, size_t outsz) {
    const char *home = getenv("HOME");
    if (home == NULL || home[0] == '\0') home = ".";
    char base[PATH_MAX];
    if ((size_t)snprintf(base, sizeof base, "%s/Downloads", home) >= sizeof base) return 0;
    if ((size_t)snprintf(out, outsz, "%s/freedom", base) >= outsz) return 0;
    mkdir(base, 0700);   /* ignore EEXIST */
    mkdir(out, 0700);
    struct stat st;
    return (stat(out, &st) == 0 && S_ISDIR(st.st_mode));
}

/* Writes len bytes to path with 0600 perms via a temp file + atomic rename (the
 * disk_store convention): a crash mid-write never leaves a half file at path, and
 * a download is never world-readable. Returns 1 on success. */
static int write_file_atomic(const char *path, const void *bytes, size_t len) {
    char tmp[PATH_MAX];
    if ((size_t)snprintf(tmp, sizeof tmp, "%s.part", path) >= sizeof tmp) return 0;
    int fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0600);
    if (fd < 0) return 0;
    const uint8_t *p = (const uint8_t *)bytes;
    size_t off = 0;
    int ok = 1;
    while (off < len) {
        ssize_t wr = write(fd, p + off, len - off);
        if (wr < 0) { if (errno == EINTR) continue; ok = 0; break; }
        off += (size_t)wr;
    }
    if (close(fd) != 0) ok = 0;
    if (ok && rename(tmp, path) == 0) return 1;
    unlink(tmp);
    return 0;
}

/* Saves a fetched resource to ~/Downloads/freedom instead of rendering it. The
 * filename is derived fail-closed from the hostile Content-Disposition / URL
 * (download module); the body is size-capped. The current page stays on screen. */
static void save_download(browser_window *w, const char *url, const char *bytes,
                          size_t len, const char *ctype, const char *disp) {
    if (dl_check_size(len) != DL_OK) {
        browser_set_status(&w->bs, "Download refused: exceeds the size cap.", now_ms());
        redraw(w);
        return;
    }
    char dir[PATH_MAX];
    if (!ensure_download_dir(dir, sizeof dir)) {
        browser_set_status(&w->bs, "Could not create the downloads directory.", now_ms());
        redraw(w);
        return;
    }
    char name[DL_NAME_MAX + 8];
    char path[PATH_MAX];
    if (dl_pick_name(url, disp, ctype, name, sizeof name) != DL_OK ||
        dl_build_path(dir, name, path, sizeof path) != DL_OK) {
        browser_set_status(&w->bs, "Could not build a safe download path.", now_ms());
        redraw(w);
        return;
    }
    char msg[PATH_MAX + 64];
    if (write_file_atomic(path, bytes != NULL ? bytes : "", len)) {
        snprintf(msg, sizeof msg, "Downloaded (%zu bytes): %s", len, path);
    } else {
        snprintf(msg, sizeof msg, "Could not write the download: %s", path);
    }
    browser_set_status(&w->bs, msg, now_ms());
    redraw(w);
}

/* Ctrl+S: save the current page's cached source to ~/Downloads/freedom. No network
 * round-trip -- the bytes already in the page cache are written. */
static void save_current_page(browser_window *w) {
    if (w->cur_html == NULL) {
        browser_set_status(&w->bs, "Nothing to save.", now_ms());
        redraw(w);
        return;
    }
    const char *url = (w->cur_top != NULL) ? w->cur_top : browser_current_url(&w->bs);
    save_download(w, url, w->cur_html, w->cur_html_len, "text/html", NULL);
}

static void deliver_fetch_result(browser_window *w, fetch_job *j) {
    if (j->gen != w->net_gen) return; /* superseded/abandoned navigation */
    w->loading = 0;

    if (j->status != SF_OK) {
        show_fetch_error(w, j->url, j->status, j->allowlisted);
        w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;
        redraw(w);
        return;
    }

    if (j->is_post && sf_is_redirect_code(j->http_code) && j->location != NULL) {
        char next[SF_MAX_URL];
        if (sf_resolve_redirect(j->url, j->location, next, sizeof next) == SF_OK) {
            if (browser_navigate(&w->bs, next) == BROWSER_OK) do_load(w, next);
            redraw(w);
            return;
        }
    }

    /* A non-renderable response (PDF, archive, ...) or an explicit attachment is
     * saved to disk rather than parsed as HTML. The current page stays on screen. */
    if (dl_should_download(j->resp_ctype, j->resp_disp)) {
        save_download(w, j->url, j->html, j->html_len, j->resp_ctype, j->resp_disp);
        return;
    }

    clear_doc(w);
    w->scroll = 0.0; w->ua_field_focused = 0; w->focused_input = -1;

    char *html = j->html;
    size_t len = j->html_len;
    j->html = NULL; /* ownership moves into the page cache */
    if (html == NULL) { html = strdup(""); len = 0; }

    /* Image policy resolves srcs against this origin (the requested URL, as before). */
    set_cache(w, html, len, j->url);
    if (j->is_post) browser_set_url_bar(&w->bs, j->url); /* reflect action URL; no history push */
    render_current_ex(w, 1); /* a fresh load may honor a JS-requested navigation */

    if (j->downgraded == DOWNGRADE_ALLOWLISTED) {
        browser_set_status(&w->bs,
            "Warning: allowlisted host loaded below Freedom's standard "
            "(possibly TLS 1.2 / weak crypto).", now_ms());
    } else if (j->downgraded == DOWNGRADE_CLASSICAL_KE) {
        browser_set_status(&w->bs,
            "Warning: connection is not post-quantum (classical TLS 1.3).", now_ms());
    }
    redraw(w);
}

/* Drains every completed fetch the worker threads have posted (the read end is
 * non-blocking; pointer-sized writes are atomic). Called when the loop sees the
 * fetch pipe readable. */
static void drain_fetch_results(browser_window *w) {
    fetch_job *j;
    while (read(w->fetch_pipe[0], &j, sizeof j) == (ssize_t)sizeof j) {
        deliver_fetch_result(w, j);
        fetch_job_free(j);
    }
}

/* Submits the form that owns rep (any control of the form supplies the action and
 * method). Gathers the named controls' current values, builds the plan with the
 * pure form module (fail closed to https), and dispatches GET (navigate) or POST.
 * The caller is responsible for the follow-up redraw. */
static void submit_form(browser_window *w, const rd_block *rep) {
    if (w->doc == NULL || rep == NULL) return;
    if (rep->form_id < 0) {
        browser_set_status(&w->bs, "This control is not part of a form.", now_ms());
        return;
    }

    fm_field fields[UI_FORM_FIELDS_MAX];
    size_t nf = 0;
    for (size_t i = 0; i < rd_count(w->doc) && nf < UI_FORM_FIELDS_MAX; ++i) {
        const rd_block *b = rd_at(w->doc, i);
        if (b->kind != RD_INPUT || b->form_id != rep->form_id) continue;
        if (b->name == NULL || b->name[0] == '\0') continue;
        const char *value;
        if (input_is_editable(b->input_type)) {
            ui_input_state *st = find_input_state(w, b);
            value = (st != NULL) ? tf_text(&st->field) : (b->value != NULL ? b->value : "");
        } else if (b->input_type == PV_IN_HIDDEN) {
            value = (b->value != NULL) ? b->value : "";
        } else {
            continue; /* submit/button controls are not value fields (v1) */
        }
        fields[nf].name = b->name;
        fields[nf].value = value;
        nf++;
    }

    /* Dispatch submit event to JS before proceeding. If the handler calls
     * preventDefault(), abort the native form submission. */
    if (w->js_mode != JSP_OFF && w->tab_worker != NULL && rep->node_id != DOM_NODE_NONE) {
        int prevented = 0;
        if (tab_submit(w->tab_worker, rep->node_id, &prevented) == TAB_OK && prevented) {
            return;
        }
    }

    const char *base = browser_current_url(&w->bs);
    if (base == NULL) base = ""; /* "" => fm_build blocks (no https base, fail closed) */
    fm_plan plan;
    if (fm_build(base, rep->href, (fm_method)rep->form_method, fields, nf, &plan) != FM_OK) {
        browser_set_status(&w->bs, "Could not build the form submission.", now_ms());
        return;
    }
    if (plan.kind == FM_BLOCKED) {
        const char *why = "Form blocked: insecure target (https required).";
        if (plan.reason == FM_BLOCK_OVERFLOW) why = "Form blocked: data too large.";
        else if (plan.reason == FM_BLOCK_INVALID) why = "Form blocked: invalid fields.";
        browser_set_status(&w->bs, why, now_ms());
        return;
    }
    if (plan.kind == FM_NAVIGATE) {
        if (browser_navigate(&w->bs, plan.url) == BROWSER_OK) do_load(w, plan.url);
        return;
    }
    if (plan.kind == FM_POST_REQUEST) {
        do_submit_post(w, &plan);
    }
}

/* Draws the three-bar "hamburger" icon for the options-menu button, centred in a
 * UI_BTN_W-wide button starting at bx within the toolbar. */
/* Toggles distraction-free (reader) mode and re-renders from cache (no network):
 * the worker drops boilerplate, author styling/images are gated off, and the content
 * is centered in a reading column. Shared by the menu item and the Ctrl+D shortcut. */
static void toggle_reader(browser_window *w) {
    w->reader = !w->reader;
    apply_theme(w); /* recompute the reading-column margin for the new state */
    browser_set_status(&w->bs, w->reader
        ? "Distraction-free mode ON (boilerplate and author styles hidden)."
        : "Distraction-free mode OFF.", now_ms());
    profile_sync(w);
    render_current(w);
}

/* True when options-menu item i is currently enabled (drives its checkmark). */
static int menu_item_checked(const browser_window *w, size_t i) {
    const ui_menu_item *it = &UI_MENU_ITEMS[i];
    if (it->action == UI_MENU_THEME) return w->theme_mode == it->theme_val;
    if (it->action == UI_MENU_FORCE) return w->force_theme;
    if (it->action == UI_MENU_TOR)   return w->net_cfg.tor_enabled;
    if (it->action == UI_MENU_I2P)   return w->net_cfg.i2p_enabled;
    if (it->action == UI_MENU_JS)    return w->js_mode != JSP_OFF;
    if (it->action == UI_MENU_READER) return w->reader;
    if (it->action == UI_MENU_FREEBUG) return freebug_is_open(w);
    if (it->action == UI_MENU_PDF)   return 0; /* an action, never "checked" */
    if (it->action == UI_MENU_PNG)   return 0; /* an action, never "checked" */
    if (it->action == UI_MENU_HOSTADD) return 0; /* an action, never "checked" */
    if (it->action == UI_MENU_BOOKMARK)
        return prefs_bookmark_index(&w->prefs, browser_current_url(&w->bs)) >= 0;
    if (it->action == UI_MENU_BOOKMARKS) return 0; /* an action, never "checked" */
    if (it->action == UI_MENU_REMHIST) return w->prefs.remember_history;
    return *(const bool *)((const char *)&w->caps + it->cap_offset);
}

/* Toggles options-menu item i and applies its effect. Theme and force-colors only
 * affect presentation (a repaint, which re-runs layout, suffices); a capability
 * change re-renders from cache. */
static void menu_item_toggle(browser_window *w, size_t i) {
    const ui_menu_item *it = &UI_MENU_ITEMS[i];
    if (it->action == UI_MENU_THEME) {
        /* Clicking the active palette returns to light; otherwise select it. */
        w->theme_mode = (w->theme_mode == it->theme_val) ? UI_THEME_LIGHT : it->theme_val;
        apply_theme(w);
        profile_sync(w);
        /* With author styles on (session toggle or trusted-host doctrine), the
         * color scheme drives the page's own @media(prefers-color-scheme) CSS, so
         * re-render from cache (no network) to pick up its dark/light rules.
         * Otherwise a repaint suffices. */
        if ((w->caps.css || page_trusted(w)) && w->cur_html != NULL) render_current(w);
        return;
    }
    if (it->action == UI_MENU_FORCE) {
        w->force_theme = !w->force_theme;
        profile_sync(w);
        return;  /* layout re-applies author colors (or not) on the next paint */
    }
    if (it->action == UI_MENU_TOR) {
        /* One switch: enable Tor and route clearnet through it too (so the whole
         * session is anonymized and .onion becomes reachable). Takes effect on the
         * next navigation; warn the user, who must have a Tor proxy running. */
        w->net_cfg.tor_enabled = !w->net_cfg.tor_enabled;
        w->net_cfg.torify_clearnet = w->net_cfg.tor_enabled;
        browser_set_status(&w->bs, w->net_cfg.tor_enabled
            ? "Tor routing ON (needs a Tor proxy on the configured port). Reload to apply."
            : "Tor routing OFF.", now_ms());
        profile_sync(w);
        return;
    }
    if (it->action == UI_MENU_I2P) {
        w->net_cfg.i2p_enabled = !w->net_cfg.i2p_enabled;
        browser_set_status(&w->bs, w->net_cfg.i2p_enabled
            ? "I2P routing ON for .i2p (needs an I2P HTTP proxy). Reload to apply."
            : "I2P routing OFF.", now_ms());
        profile_sync(w);
        return;
    }
    if (it->action == UI_MENU_JS) {
        /* Cycle the global policy: off -> allowlist -> on -> off. ALLOWLIST runs JS
         * only for hosts in js.conf; ON runs it everywhere (least safe). Re-render so
         * <noscript> handling reflects the new policy for the current page. */
        w->js_mode = (w->js_mode == JSP_OFF)       ? JSP_ALLOWLIST
                   : (w->js_mode == JSP_ALLOWLIST) ? JSP_ON
                                                   : JSP_OFF;
        char msg[96];
        snprintf(msg, sizeof msg, "JavaScript policy: %s.", jsp_mode_str(w->js_mode));
        browser_set_status(&w->bs, msg, now_ms());
        profile_sync(w);
        render_current(w);
        return;
    }
    if (it->action == UI_MENU_READER) {
        toggle_reader(w);
        return;
    }
    if (it->action == UI_MENU_PDF) {
        w->menu_open = 0; /* dismiss the menu, then export */
        export_pdf(w);
        return;
    }
    if (it->action == UI_MENU_PNG) {
        w->menu_open = 0; /* dismiss the menu, then export */
        export_png(w);
        return;
    }
    if (it->action == UI_MENU_FREEBUG) {
        w->menu_open = 0; /* dismiss the menu, then open/close the console window */
        freebug_toggle(w);
        return;
    }
    if (it->action == UI_MENU_HOSTADD) {
        add_current_host_to_list(w, it->theme_val);  /* theme_val = HOSTLIST_* */
        return;
    }
    if (it->action == UI_MENU_BOOKMARK) {
        w->menu_open = 0;
        bookmark_toggle_current(w);
        return;
    }
    if (it->action == UI_MENU_BOOKMARKS) {
        w->menu_open = 0;
        do_load(w, "about:bookmarks");
        return;
    }
    if (it->action == UI_MENU_REMHIST) {
        /* Zero Knowledge bias: opting out also forgets what was retained. */
        w->prefs.remember_history = !w->prefs.remember_history;
        if (!w->prefs.remember_history) {
            for (size_t h = 0; h < w->prefs.history_len; ++h) free(w->prefs.history[h]);
            free(w->prefs.history);
            w->prefs.history = NULL;
            w->prefs.history_len = 0;
        }
        browser_set_status(&w->bs, w->prefs.remember_history
            ? "History will be remembered (encrypted at rest)."
            : "History OFF and forgotten.", now_ms());
        if (w->profile_rw) profile_save(&w->profile, &w->prefs);
        return;
    }
    bool *flag = (bool *)((char *)&w->caps + it->cap_offset);
    *flag = !*flag;
    profile_sync(w);
    render_current(w);
}

/* A small spinner meaning "busy". Now that the fetch runs off the event-loop thread,
 * the loop ticks ~12 fps while loading and rotates a leading arc so the user sees real
 * progress. phase in [0,1) is the rotation, derived from the wall clock. */
static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
                       double phase) {
    double a0 = phase * UI_TWO_PI;
    set_rgb(cr, color);
    cairo_set_line_width(cr, 2.0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    /* A 270-degree arc that sweeps around, leaving a moving gap (a classic spinner). */
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, r, a0, a0 + UI_TWO_PI * 0.75);
    cairo_stroke(cr);
}

static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop) {
    set_rgb(cr, color);
    cairo_set_line_width(cr, 2.0);
    double cx = bx + (UI_BTN_W - UI_HAMBURGER_W) / 2.0;
    double cy = ttop + (UI_TOOLBAR_H - 2.0 * UI_HAMBURGER_GAP) / 2.0;
    for (int i = 0; i < 3; ++i) {
        double y = cy + (double)i * UI_HAMBURGER_GAP;
        cairo_move_to(cr, cx, y);
        cairo_line_to(cr, cx + UI_HAMBURGER_W, y);
        cairo_stroke(cr);
    }
}

/* The reload button glyph: a ~300-degree circular arrow centred in a UI_BTN_W button
 * starting at bx. Drawn with Cairo (not a font glyph) so it never depends on the
 * chrome face having a reload codepoint. */
static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop) {
    set_rgb(cr, color);
    cairo_set_line_width(cr, 2.0);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    double cx = bx + UI_BTN_W / 2.0;
    double cy = ttop + UI_TOOLBAR_H / 2.0;
    double r = 6.0;
    double a0 = -UI_TWO_PI * 0.08;          /* start just right of top */
    double a1 = a0 + UI_TWO_PI * 0.82;      /* leave a gap for the arrowhead */
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, r, a0, a1);
    cairo_stroke(cr);
    /* Arrowhead at the arc's start (top), pointing clockwise. */
    double hx = cx + r * cos(a0), hy = cy + r * sin(a0);
    cairo_move_to(cr, hx, hy);
    cairo_line_to(cr, hx - 4.0, hy - 1.0);
    cairo_move_to(cr, hx, hy);
    cairo_line_to(cr, hx + 1.0, hy - 4.5);
    cairo_stroke(cr);
}

/* Draws the options-menu panel (checkbox per capability) when open. */
static void draw_menu(cairo_t *cr, browser_window *w) {
    if (!w->menu_open) return;
    const ui_theme *th = &w->theme;
    double mx, my, mw, mh, ih;
    menu_panel_rect(w, &mx, &my, &mw, &mh, &ih);

    set_rgb(cr, th->menu_bg);
    cairo_rectangle(cr, mx, my, mw, mh);
    cairo_fill(cr);
    set_rgb(cr, th->menu_border);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, mx, my, mw, mh);
    cairo_stroke(cr);

    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);

    for (size_t i = 0; i < UI_MENU_COUNT; ++i) {
        double row_y = my + UI_MENU_PAD + (double)i * ih;
        double box_y = row_y + (ih - UI_CHECK_SZ) / 2.0;
        double box_x = mx + UI_MENU_PAD;

        set_rgb(cr, th->check_border);
        cairo_set_line_width(cr, 1.5);
        cairo_rectangle(cr, box_x, box_y, UI_CHECK_SZ, UI_CHECK_SZ);
        cairo_stroke(cr);

        if (menu_item_checked(w, i)) {
            set_rgb(cr, th->check_mark);
            cairo_set_line_width(cr, 2.0);
            cairo_move_to(cr, box_x + UI_CHECK_SZ * 0.2, box_y + UI_CHECK_SZ * 0.55);
            cairo_line_to(cr, box_x + UI_CHECK_SZ * 0.42, box_y + UI_CHECK_SZ * 0.78);
            cairo_line_to(cr, box_x + UI_CHECK_SZ * 0.8, box_y + UI_CHECK_SZ * 0.25);
            cairo_stroke(cr);
        }

        set_rgb(cr, th->menu_text);
        double tx = box_x + UI_CHECK_SZ + UI_MENU_PAD;
        double ty = row_y + (ih + fe.ascent - fe.descent) / 2.0;
        cairo_move_to(cr, tx, ty);
        /* The JS row shows its tri-state mode inline (off/allowlist/on). */
        if (UI_MENU_ITEMS[i].action == UI_MENU_JS) {
            char jl[64];
            snprintf(jl, sizeof jl, "JavaScript: %s", jsp_mode_str(w->js_mode));
            cairo_show_text(cr, jl);
        } else {
            cairo_show_text(cr, UI_MENU_ITEMS[i].label);
        }
    }

    /* User-Agent section: a label and an editable box. The box uses a monospace
     * face for stable caret math (same convention as the URL bar). */
    double label_y = my + UI_MENU_PAD + (double)UI_MENU_COUNT * ih;
    set_rgb(cr, th->menu_text);
    cairo_move_to(cr, mx + UI_MENU_PAD, label_y + (UI_MENU_LABEL_H + fe.ascent - fe.descent) / 2.0);
    cairo_show_text(cr, "User-Agent (network):");

    double bx, by, bw, bh;
    ua_box_rect(w, &bx, &by, &bw, &bh);
    set_rgb(cr, w->ua_field_focused ? th->url_bg_focused : th->url_bg);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_fill(cr);
    set_rgb(cr, w->ua_field_focused ? th->link : th->url_border);
    cairo_set_line_width(cr, 1.0);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_stroke(cr);

    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t mfe;
    cairo_font_extents(cr, &mfe);

    cairo_save(cr);
    cairo_rectangle(cr, bx + 2.0, by + 1.0, bw - 4.0, bh - 2.0);
    cairo_clip(cr);

    const char *ua = tf_text(&w->ua_field);
    double tx = bx + UI_MARGIN;
    double ty = by + (bh + mfe.ascent - mfe.descent) / 2.0;
    if (ua[0] == '\0' && !w->ua_field_focused) {
        /* Empty field => the normalized anti-fingerprint identity (a shared Firefox
         * string) is sent. The placeholder names that intent rather than the long UA
         * literal; "Freedom" is deliberately never sent on the wire. */
        set_rgb(cr, th->chrome_text_dim);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, "anti-fingerprint default (shared Firefox identity)");
    } else {
        set_rgb(cr, th->menu_text);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, ua);
    }
    if (w->ua_field_focused) {
        double cx = tx;
        for (size_t i = 0; i < tf_cursor(&w->ua_field); ++i) {
            char tmp[2] = { ua[i], '\0' };
            cairo_text_extents_t te;
            cairo_text_extents(cr, tmp, &te);
            cx += te.x_advance;
        }
        set_rgb(cr, th->caret);
        cairo_rectangle(cr, cx, ty - mfe.ascent, 1.5, mfe.height);
        cairo_fill(cr);
    }
    cairo_restore(cr);
}

/* Persistent bottom strip showing the target of the link under the pointer, so
 * the user always knows where a click will go. Returns the strip height (0 when
 * nothing is hovered) so the toast can stack above it. */
static double draw_hover_url(cairo_t *cr, browser_window *w) {
    if (w->hover_href == NULL) return 0.0;
    const ui_theme *th = &w->theme;

    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_text_extents_t te;
    cairo_text_extents(cr, w->hover_href, &te);

    double bh = fe.height + 2.0 * UI_TOAST_PAD;
    double bw = te.width + 2.0 * UI_TOAST_PAD;
    if (bw > (double)w->width) bw = (double)w->width; /* never wider than the window */
    double by = (double)w->height - bh;

    set_rgb(cr, th->toast_bg);
    cairo_rectangle(cr, 0.0, by, bw, bh);
    cairo_fill(cr);

    cairo_save(cr);
    cairo_rectangle(cr, 0.0, by, bw - UI_TOAST_PAD, bh); /* clip a long URL */
    cairo_clip(cr);
    set_rgb(cr, th->toast_text);
    cairo_move_to(cr, UI_TOAST_PAD, by + UI_TOAST_PAD + fe.ascent);
    cairo_show_text(cr, w->hover_href);
    cairo_restore(cr);
    return bh;
}

/* Draws the transient status toast (a banner near the bottom of the window),
 * raised by bottom_offset so it stacks above the hover-URL strip when both show. */
static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset) {
    const char *msg = browser_status_text(&w->bs, now_ms());
    if (msg == NULL) return;
    const ui_theme *th = &w->theme;

    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    cairo_text_extents_t te;
    cairo_text_extents(cr, msg, &te);

    double bh = fe.height + 2.0 * UI_TOAST_PAD;
    double bw = te.width + 2.0 * UI_TOAST_PAD;
    double bx = UI_MARGIN;
    double by = (double)w->height - bh - UI_MARGIN - bottom_offset;

    set_rgb(cr, th->toast_bg);
    cairo_rectangle(cr, bx, by, bw, bh);
    cairo_fill(cr);
    set_rgb(cr, th->toast_text);
    cairo_move_to(cr, bx + UI_TOAST_PAD, by + UI_TOAST_PAD + fe.ascent);
    cairo_show_text(cr, msg);
}

/* Paints the tab strip: one cell per tab (the active one connected to the content
 * background, the rest dimmed), each with its clipped title and a close 'x', then a
 * trailing '+' to open a new tab. The geometry mirrors the pointer hit-test
 * (tab_width/newtab_x) so a click lands on exactly what is drawn. Uses the chrome
 * (monospace) font already selected by paint(). */
static void draw_tabstrip(cairo_t *cr, browser_window *w) {
    const ui_theme *th = &w->theme;
    double top = tabbar_top(w);
    double h = UI_TABBAR_H;

    set_rgb(cr, th->titlebar_bg);
    cairo_rectangle(cr, 0, top, w->width, h);
    cairo_fill(cr);

    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double baseline = top + (h + fe.ascent - fe.descent) / 2.0;
    double tw = tab_width(w);

    for (int i = 0; i < w->tab_count; ++i) {
        double x = (double)i * tw;
        int active = (i == w->active_tab);
        int hot = (w->ptr_y >= top && w->ptr_y < top + h
                   && w->ptr_x >= x && w->ptr_x < x + tw);

        set_rgb(cr, active ? th->content_bg : (hot ? th->btn_hover_bg : th->toolbar_bg));
        cairo_rectangle(cr, x, top, tw - 1.0, h);
        cairo_fill(cr);

        cairo_save(cr);
        cairo_rectangle(cr, x + 6.0, top, tw - 6.0 - UI_TAB_CLOSE_W, h);
        cairo_clip(cr);
        set_rgb(cr, active ? th->chrome_text : th->chrome_text_dim);
        cairo_move_to(cr, x + 6.0, baseline);
        cairo_show_text(cr, tab_title(w, i));
        cairo_restore(cr);

        if (w->tab_count > 1) {
            double cxr = x + tw - UI_TAB_CLOSE_W;
            int cl_hot = (w->ptr_y >= top && w->ptr_y < top + h
                          && w->ptr_x >= cxr && w->ptr_x < x + tw);
            set_rgb(cr, cl_hot ? th->close_button
                                : (active ? th->chrome_text : th->chrome_text_dim));
            draw_text(cr, "x", cxr + UI_TAB_CLOSE_W / 2.0, baseline, 1);
        }
    }

    double nx = newtab_x(w);
    int nhot = (w->ptr_y >= top && w->ptr_y < top + h
                && w->ptr_x >= nx && w->ptr_x < nx + UI_TAB_NEW_W);
    set_rgb(cr, nhot ? th->btn_hover_bg : th->titlebar_bg);
    cairo_rectangle(cr, nx, top, UI_TAB_NEW_W, h);
    cairo_fill(cr);
    set_rgb(cr, th->chrome_text);
    draw_text(cr, "+", nx + UI_TAB_NEW_W / 2.0, baseline, 1);
}

/* Omnibox autocomplete dropdown: a panel of favorite-host suggestions below the URL
 * bar, drawn as an overlay (on top of content) while the URL bar is focused and a
 * query matches. The highlighted row (omni_sel) is shaded. */
static void draw_omnibox(cairo_t *cr, browser_window *w) {
    omni_refresh(w);
    if (w->omni_sugg_n <= 0) return;
    const ui_theme *th = &w->theme;
    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    double top = toolbar_top(w) + UI_TOOLBAR_H;
    double h = UI_OMNI_ROW_H * (double)w->omni_sugg_n;

    set_rgb(cr, th->url_bg);
    cairo_rectangle(cr, url_x, top, url_w, h);
    cairo_fill(cr);
    set_rgb(cr, th->url_border);
    cairo_rectangle(cr, url_x, top, url_w, h);
    cairo_stroke(cr);

    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, UI_FONT_SIZE);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    for (int i = 0; i < w->omni_sugg_n; ++i) {
        double ry = top + UI_OMNI_ROW_H * (double)i;
        if (i == w->omni_sel) {
            set_rgb(cr, th->btn_hover_bg);
            cairo_rectangle(cr, url_x, ry, url_w, UI_OMNI_ROW_H);
            cairo_fill(cr);
        }
        set_rgb(cr, th->chrome_text);
        cairo_move_to(cr, url_x + UI_MARGIN,
                      ry + (UI_OMNI_ROW_H + fe.ascent - fe.descent) / 2.0);
        cairo_show_text(cr, w->omni_sugg[i]);
    }
}

static void paint(browser_window *w) {
    cairo_t *cr = cairo_create(w->cairo_surface);
    const ui_theme *th = &w->theme;
    double ttop = toolbar_top(w);

    /* Background. */
    set_rgb(cr, th->window_bg);
    cairo_paint(cr);

    /* The chrome (titlebar, toolbar, URL bar) uses a monospace face for stable
     * caret math; page content is painted separately with a proportional face. */
    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, th->body_font);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);

    /* Client-side titlebar (when the compositor offers no SSD). */
    if (w->use_csd) {
        double bl = (UI_TITLEBAR_H + fe.ascent - fe.descent) / 2.0;
        set_rgb(cr, th->titlebar_bg);
        cairo_rectangle(cr, 0, 0, w->width, UI_TITLEBAR_H);
        cairo_fill(cr);

        set_rgb(cr, th->chrome_text);
        cairo_move_to(cr, UI_MARGIN, bl);
        cairo_show_text(cr, w->loading ? "Loading..."
                          : (w->bs.page_title != NULL) ? w->bs.page_title : "Freedom");

        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        set_rgb(cr, th->chrome_text);
        draw_text(cr, "_", min_x + UI_WIN_BTN_W / 2.0, bl, 1);
        draw_text(cr, "[]", max_x + UI_WIN_BTN_W / 2.0, bl, 1);
        set_rgb(cr, th->close_button);
        draw_text(cr, "X", close_x + UI_WIN_BTN_W / 2.0, bl, 1);
    }

    /* Tab strip, between the titlebar and the toolbar. */
    draw_tabstrip(cr, w);

    /* Toolbar. */
    set_rgb(cr, th->toolbar_bg);
    cairo_rectangle(cr, 0, ttop, w->width, UI_TOOLBAR_H);
    cairo_fill(cr);

    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);
    double bl = ttop + (UI_TOOLBAR_H + fe.ascent - fe.descent) / 2.0;

    /* Hover highlight behind the toolbar button under the pointer (the same
     * affordance links get). */
    if (w->hot != UI_HOT_NONE) {
        double hx = back_x;
        switch (w->hot) {
            case UI_HOT_BACK:   hx = back_x;      break;
            case UI_HOT_FWD:    hx = fwd_x;       break;
            case UI_HOT_RELOAD: hx = UI_RELOAD_X; break;
            case UI_HOT_GO:     hx = go_x;        break;
            case UI_HOT_MENU:   hx = menu_x;      break;
            default: break;
        }
        set_rgb(cr, th->btn_hover_bg);
        cairo_rectangle(cr, hx, ttop, UI_BTN_W, UI_TOOLBAR_H);
        cairo_fill(cr);
    }

    /* Buttons. */
    int can_back = browser_can_back(&w->bs);
    int can_fwd  = browser_can_forward(&w->bs);

    set_rgb(cr, can_back ? th->chrome_text : th->chrome_text_dim);
    draw_text(cr, "<", back_x + UI_BTN_W / 2.0, bl, 1);

    set_rgb(cr, can_fwd ? th->chrome_text : th->chrome_text_dim);
    draw_text(cr, ">", fwd_x + UI_BTN_W / 2.0, bl, 1);

    /* Reload button (also F5 / Ctrl+R). */
    draw_reload(cr, th->chrome_text, UI_RELOAD_X, ttop);

    set_rgb(cr, th->chrome_text);
    draw_text(cr, "Go", go_x + UI_BTN_W / 2.0, bl, 1);

    /* Options-menu (gear) button: a three-bar icon. */
    draw_hamburger(cr, th->chrome_text, menu_x, ttop);

    /* URL bar. */
    set_rgb(cr, w->url_bar_focused ? th->url_bg_focused : th->url_bg);
    cairo_rectangle(cr, url_x, ttop + UI_MARGIN, url_w, UI_TOOLBAR_H - 2 * UI_MARGIN);
    cairo_fill(cr);

    set_rgb(cr, th->url_border);
    cairo_rectangle(cr, url_x, ttop + UI_MARGIN, url_w, UI_TOOLBAR_H - 2 * UI_MARGIN);
    cairo_stroke(cr);

    /* URL text + cursor. */
    const char *url = w->bs.url_bar;
    if (url != NULL) {
        char buf[BROWSER_URL_MAX];
        snprintf(buf, sizeof buf, "%s", url);
        cairo_text_extents_t te;
        cairo_text_extents(cr, buf, &te);
        double tx = url_x + UI_MARGIN;
        double ty = bl;

        /* Clip to URL bar interior. */
        cairo_save(cr);
        cairo_rectangle(cr, url_x + 2, ttop + UI_MARGIN + 2, url_w - 4, UI_TOOLBAR_H - 2 * UI_MARGIN - 4);
        cairo_clip(cr);

        /* Selection highlight behind the text (omnibar). Wrapped in save/restore so the
         * source colour for the text below is unchanged when there is no selection. */
        if (w->url_bar_focused) {
            size_t ss = 0, sl = 0;
            if (browser_url_bar_selection(&w->bs, &ss, &sl)) {
                char m[2] = {0};
                double sx = tx;
                for (size_t i = 0; i < ss && i < w->bs.url_bar_len; ++i) {
                    m[0] = url[i]; cairo_text_extents(cr, m, &te); sx += te.x_advance;
                }
                double ex = sx;
                for (size_t i = ss; i < ss + sl && i < w->bs.url_bar_len; ++i) {
                    m[0] = url[i]; cairo_text_extents(cr, m, &te); ex += te.x_advance;
                }
                cairo_save(cr);
                set_rgb(cr, th->btn_hover_bg);
                cairo_rectangle(cr, sx, ty - fe.ascent, ex - sx, fe.height);
                cairo_fill(cr);
                cairo_restore(cr);
            }
        }

        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, buf);

        if (w->url_bar_focused) {
            /* Cursor position. */
            char left[2] = {0};
            double cx = tx;
            for (size_t i = 0; i < w->bs.url_bar_cursor && i < w->bs.url_bar_len; ++i) {
                left[0] = url[i];
                cairo_text_extents(cr, left, &te);
                cx += te.x_advance;
            }
            set_rgb(cr, th->caret);
            cairo_rectangle(cr, cx, ty - fe.ascent, 1.5, fe.height);
            cairo_fill(cr);
        }
        cairo_restore(cr);
    }

    /* Animated spinner at the right of the URL bar while a request is in flight. The
     * rotation comes from the wall clock; the loop wakes ~12 fps while loading. */
    if (w->loading) {
        double r = (UI_TOOLBAR_H - 2.0 * UI_MARGIN) * 0.30;
        double ccx = url_x + url_w - r - UI_MARGIN;
        double ccy = ttop + UI_TOOLBAR_H / 2.0;
        double phase = (double)(now_ms() % 1000u) / 1000.0;
        draw_clock(cr, th->link, ccx, ccy, r, phase);
    }

    /* Content area. */
    double content_top, content_h;
    content_geometry(w, &content_top, &content_h);

    set_rgb(cr, th->content_bg);
    cairo_rectangle(cr, 0, content_top, w->width, (double)w->height - content_top);
    cairo_fill(cr);

    /* Clip every page paint to the content viewport. Rows that straddle the top
     * edge (partly scrolled above content_top) would otherwise bleed up over the
     * toolbar/tab strip; the clip is the single guard that keeps content under the
     * chrome no matter the scroll offset. Released before the chrome overlays
     * (scrollbar, menu, toast) so those still paint over the full surface. */
    cairo_save(cr);
    cairo_rectangle(cr, 0, content_top, w->width, (double)w->height - content_top);
    cairo_clip(cr);

    w->content_total_h = 0.0;  /* each branch sets the real height; 0 => no scrollbar */
    if (w->doc != NULL) {
        paint_structured(cr, w, content_top, content_h);
    } else {
        /* Plain-text fallback for the start page and error pages: monospace,
         * word-wrapped, scrolled by the same pixel offset (converted to lines). */
        const char *text = w->bs.page_text ? w->bs.page_text : "";
        size_t text_len = strlen(text);

        cairo_text_extents_t te;
        cairo_text_extents(cr, "M", &te);
        double cell_w = (te.x_advance > 0) ? te.x_advance : 8.0;
        double cell_h = (fe.height > 0) ? fe.height : th->body_font;

        size_t max_cols = (size_t)(content_width(w) / cell_w);
        if (max_cols == 0) max_cols = 1;
        size_t viewport_lines = (size_t)(content_h / cell_h);
        if (viewport_lines == 0) viewport_lines = 1;

        ui_layout lay;
        if (ui_wrap_text(text, text_len, max_cols, &lay) == UI_OK) {
            w->content_total_h = (double)lay.count * cell_h;  /* cached for the scrollbar */
            size_t first = (size_t)(w->scroll / cell_h);
            first = ui_clamp_scroll(first, lay.count, viewport_lines);
            w->scroll = (double)first * cell_h;

            /* A line is at most max_cols columns; in UTF-8 each column is up to 4
             * bytes, so size for that and copy whole lines (ui_wrap_text already
             * breaks on character boundaries, so no byte cap can split a glyph). */
            size_t linecap = max_cols * 4 + 1;
            char *linebuf = (char *)malloc(linecap);
            if (linebuf != NULL) {
                set_rgb(cr, th->text);
                double y = content_top + th->content_margin + fe.ascent;
                for (size_t row = 0; row < viewport_lines; ++row) {
                    size_t idx = first + row;
                    if (idx >= lay.count) break;
                    size_t n = lay.lines[idx].len;
                    if (n > linecap - 1) n = linecap - 1;
                    memcpy(linebuf, text + lay.lines[idx].offset, n);
                    linebuf[n] = '\0';
                    cairo_move_to(cr, content_margin_x(w), y);
                    cairo_show_text(cr, linebuf);
                    y += cell_h;
                }
                free(linebuf);
            }
            ui_layout_free(&lay);
        }
    }

    cairo_restore(cr);  /* end content-viewport clip */

    /* Scrollbar over the content's right gutter, then overlays on top. */
    draw_scrollbar(cr, w);
    draw_menu(cr, w);
    draw_omnibox(cr, w);
    double hover_h = draw_hover_url(cr, w);
    draw_toast(cr, w, hover_h);

    cairo_surface_flush(w->cairo_surface);
    cairo_destroy(cr);
}

static void redraw(browser_window *w) {
    if (!w->configured) return;
    if (ensure_buffer(w) != 0) return;
    paint(w);
    wl_surface_attach(w->surface, w->buffer, 0, 0);
    wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height);
    wl_surface_commit(w->surface);
}

/* --- xdg-shell --- */

static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial) {
    (void)data;
    xdg_wm_base_pong(b, serial);
}
static const struct xdg_wm_base_listener wm_base_listener = { wm_base_ping };

static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial) {
    browser_window *w = (browser_window *)data;
    xdg_surface_ack_configure(s, serial);
    w->configured = 1;
    redraw(w);
}
static const struct xdg_surface_listener xdg_surface_listener = { xdg_surface_configure };

static void toplevel_configure(void *data, struct xdg_toplevel *t,
                               int32_t width, int32_t height, struct wl_array *states) {
    (void)t;
    browser_window *w = (browser_window *)data;
    if (width > 0 && height > 0) {
        w->width = width;
        w->height = height;
        /* Reader mode centers the content in a width-derived margin, so recompute it
         * when the window resizes (a no-op for the other modes). */
        if (w->reader) apply_theme(w);
    }
    /* Track the maximized state so the titlebar button toggles correctly. */
    w->maximized = 0;
    if (states != NULL) {
        const uint32_t *st;
        wl_array_for_each(st, states) {
            if (*st == XDG_TOPLEVEL_STATE_MAXIMIZED) w->maximized = 1;
        }
    }
}
static void toplevel_close(void *data, struct xdg_toplevel *t) {
    (void)t;
    ((browser_window *)data)->running = 0;
}
static const struct xdg_toplevel_listener toplevel_listener = {
    .configure = toplevel_configure,
    .close = toplevel_close,
};

static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode) {
    (void)d;
    browser_window *w = (browser_window *)data;
    w->use_csd = (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE);
    redraw(w);
}
static const struct zxdg_toplevel_decoration_v1_listener deco_listener = { deco_configure };

/* --- input --- */

/* Applies the hand (over a link) or default arrow cursor for the current pointer
 * enter serial. A no-op when no themed cursor is available (the compositor keeps
 * its own default). */
static void set_cursor(browser_window *w, int hand) {
    if (w->pointer == NULL || w->cursor_surface == NULL) return;
    struct wl_cursor *c = hand ? w->cursor_hand : w->cursor_default;
    if (c == NULL || c->image_count == 0) return;
    struct wl_cursor_image *img = c->images[0];
    struct wl_buffer *buf = wl_cursor_image_get_buffer(img);
    if (buf == NULL) return;
    wl_pointer_set_cursor(w->pointer, w->pointer_serial, w->cursor_surface,
                          (int32_t)img->hotspot_x, (int32_t)img->hotspot_y);
    wl_surface_attach(w->cursor_surface, buf, 0, 0);
    wl_surface_damage(w->cursor_surface, 0, 0, (int32_t)img->width, (int32_t)img->height);
    wl_surface_commit(w->cursor_surface);
}

/* Recomputes which link (if any) is under the pointer; on a change, updates the
 * cursor shape and repaints so the hover highlight follows. The author `cursor`
 * (css_cursor) at the point is folded into the hand-vs-arrow decision: a
 * cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without an href. v1 only distinguishes pointer from everything else (the
 * rest of the keyword set resolves for completeness/debug_dom but still paints as
 * the default arrow -- see spec/css.md); overriding a LINK's hand cursor away
 * (e.g. `a{cursor:default}`) is a known v1 gap. */
static void update_hover(browser_window *w) {
    const char *h = (w->doc != NULL && !w->menu_open)
                    ? link_at_point(w, w->ptr_x, w->ptr_y) : NULL;
    int cur = (w->doc != NULL && !w->menu_open)
              ? cursor_at_point(w, w->ptr_x, w->ptr_y) : CSS_CUR_UNSET;
    ui_hot hot = toolbar_button_at(w, w->ptr_x, w->ptr_y);
    if (h == w->hover_href && cur == w->hover_cursor && hot == w->hot) return;

    int hand_was = (w->hover_href != NULL) || hot_actionable(w, w->hot) ||
                   w->hover_cursor == CSS_CUR_POINTER;
    int hand_now = (h != NULL) || hot_actionable(w, hot) || cur == CSS_CUR_POINTER;
    w->hover_href = h;
    w->hover_cursor = cur;
    w->hot = hot;
    if (hand_was != hand_now) set_cursor(w, hand_now);
    redraw(w);
}

/* ===================== Freebug (developer console, second window) ===================== */
/* A second Wayland xdg_toplevel: a log pane (the active page's captured console.* +
 * uncaught script errors, held in browser_window.console) over a JS REPL editor that
 * tab_eval's against the live page worker (browser_window.tab_worker, kept alive after
 * render). Opened with F12 or the hamburger menu. It shares display/compositor/shm/
 * wm_base/seat with the main window; the shared seat listeners route input here while
 * this surface holds focus (kbd_focus/ptr_focus). */

#define FBW_W          760
#define FBW_H          560
#define FBW_HEADER     26.0
#define FBW_PAD         8.0
#define FBW_LINE       16.0
#define FBW_GUTTER     16.0
#define FBW_MIN_SPLIT   0.20
#define FBW_MAX_SPLIT   0.88
#define FBW_COPY_BTN_W 56.0
#define FBW_COPY_BTN_H 16.0

struct freebug_window {
    browser_window      *owner;
    struct wl_surface   *surface;
    struct xdg_surface  *xdg_surface;
    struct xdg_toplevel *xdg_toplevel;
    struct zxdg_toplevel_decoration_v1 *deco;
    int    width, height;
    int    configured;
    int    visible;
    struct wl_buffer *buffer;
    void  *shm_data;
    size_t shm_size;
    cairo_surface_t *cairo_surface;
    double split;          /* log-pane fraction of the body height */
    double scroll;         /* log scroll offset (px) */
    int    dragging_split; /* the divider is being dragged */
    int    hover_copy;     /* mouse is over the copy button */
    int    copy_status;    /* 0=idle, 1=no-clipboard(red), 2=OK(green) */
    uint64_t copy_ts;      /* last copy timestamp (ms), for "Copied!" feedback */
    tf_field editor;       /* the JS REPL input (newlines allowed) */
};

/* y of the divider between the log pane and the editor. */
static double fbw_split_y(const freebug_window *fb) {
    double body = (double)fb->height - FBW_HEADER;
    if (body < 0) body = 0;
    double s = fb->split;
    if (s < FBW_MIN_SPLIT) s = FBW_MIN_SPLIT;
    if (s > FBW_MAX_SPLIT) s = FBW_MAX_SPLIT;
    return FBW_HEADER + body * s;
}

static int freebug_ensure_buffer(freebug_window *fb) {
    int stride = fb->width * 4;
    size_t size = (size_t)stride * (size_t)fb->height;
    if (fb->buffer && fb->shm_size == size && fb->cairo_surface) return 0;
    if (fb->cairo_surface) { cairo_surface_destroy(fb->cairo_surface); fb->cairo_surface = NULL; }
    if (fb->buffer) { wl_buffer_destroy(fb->buffer); fb->buffer = NULL; }
    if (fb->shm_data) { munmap(fb->shm_data, fb->shm_size); fb->shm_data = NULL; fb->shm_size = 0; }

    int fd = memfd_create("freedom-freebug", MFD_CLOEXEC);
    if (fd < 0) return -1;
    if (ftruncate(fd, (off_t)size) < 0) { close(fd); return -1; }
    void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) { close(fd); return -1; }
    struct wl_shm_pool *pool = wl_shm_create_pool(fb->owner->shm, fd, (int32_t)size);
    fb->buffer = wl_shm_pool_create_buffer(pool, 0, fb->width, fb->height, stride, WL_SHM_FORMAT_ARGB8888);
    wl_shm_pool_destroy(pool);
    close(fd);
    if (fb->buffer == NULL) { munmap(data, size); return -1; }
    wl_buffer_add_listener(fb->buffer, &buffer_listener, fb); /* release is a no-op */
    fb->shm_data = data;
    fb->shm_size = size;
    fb->cairo_surface = cairo_image_surface_create_for_data(
        (unsigned char *)data, CAIRO_FORMAT_ARGB32, fb->width, fb->height, stride);
    return (cairo_surface_status(fb->cairo_surface) == CAIRO_STATUS_SUCCESS) ? 0 : -1;
}

/* Color for a console level (dark devtools palette). */
static void fbw_level_rgb(int level, double *r, double *g, double *b) {
    switch (level) {
        case FB_ERROR: *r = 0.95; *g = 0.36; *b = 0.36; break;
        case FB_WARN:  *r = 0.93; *g = 0.78; *b = 0.36; break;
        case FB_INFO:  *r = 0.46; *g = 0.80; *b = 0.95; break;
        case FB_DEBUG: *r = 0.60; *g = 0.60; *b = 0.66; break;
        default:       *r = 0.86; *g = 0.88; *b = 0.91; break; /* log */
    }
}

/* Counts the visual lines a console buffer occupies (entries split on '\n'). */
static size_t fbw_console_lines(const fb_buffer *log) {
    size_t lines = 0;
    for (size_t i = 0; i < fb_buffer_count(log); ++i) {
        const fb_entry *e = fb_buffer_at(log, i);
        lines += 1;
        for (size_t k = 0; k < e->len; ++k) if (e->text[k] == '\n') lines++;
    }
    return lines;
}

/* Forward declaration (defined in the clipboard section below). */
static void freebug_copy_console(browser_window *w);

static void freebug_paint(freebug_window *fb) {
    browser_window *w = fb->owner;
    cairo_t *cr = cairo_create(fb->cairo_surface);
    cairo_set_source_rgb(cr, 0.11, 0.12, 0.14);
    cairo_paint(cr);
    cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 13.0);

    /* header */
    cairo_set_source_rgb(cr, 0.18, 0.19, 0.22);
    cairo_rectangle(cr, 0, 0, fb->width, FBW_HEADER);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0.80, 0.82, 0.86);
    cairo_move_to(cr, FBW_PAD, FBW_HEADER - 8.0);
    cairo_show_text(cr, "Freebug  -  F12 close  -  Ctrl+Enter run  - Ctrl+L clear  - Ctrl+C copy");

    /* copy button (right side of header) */
    double cbx = fb->width - FBW_PAD - FBW_COPY_BTN_W;
    double cby = (FBW_HEADER - FBW_COPY_BTN_H) / 2.0;
    uint64_t now = now_ms();
    int copied = (fb->copy_ts > 0 && now - fb->copy_ts < 2000);
    if (copied) {
        if (fb->copy_status == 1)
            cairo_set_source_rgb(cr, 0.50, 0.15, 0.15); /* red: no clipboard */
        else
            cairo_set_source_rgb(cr, 0.20, 0.50, 0.25); /* green: success */
    } else if (fb->hover_copy) {
        cairo_set_source_rgb(cr, 0.30, 0.45, 0.65);
    } else {
        cairo_set_source_rgb(cr, 0.25, 0.27, 0.30);
    }
    cairo_rectangle(cr, cbx, cby, FBW_COPY_BTN_W, FBW_COPY_BTN_H);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0.75, 0.78, 0.82);
    cairo_set_font_size(cr, 10.0);
    cairo_move_to(cr, cbx + 4.0, cby + 12.0);
    cairo_show_text(cr, copied ? "OK" : "[C]");
    /* clipboard icon: a small rectangle with a handle on top */
    double icx = cbx + FBW_COPY_BTN_W - 18.0;
    double icy = cby + 2.0;
    cairo_set_line_width(cr, 1.2);
    cairo_rectangle(cr, icx, icy + 4.0, 10.0, 11.0);
    cairo_stroke(cr);
    cairo_move_to(cr, icx + 2.0, icy + 4.0);
    cairo_line_to(cr, icx + 2.0, icy + 1.0);
    cairo_line_to(cr, icx + 8.0, icy + 1.0);
    cairo_line_to(cr, icx + 8.0, icy + 4.0);
    cairo_stroke(cr);
    cairo_set_font_size(cr, 13.0);

    double split_y = fbw_split_y(fb);
    double logh = split_y - FBW_HEADER;

    /* clamp the scroll against the content height */
    double total = (double)fbw_console_lines(&w->console) * FBW_LINE;
    double view = logh - 2 * FBW_PAD;
    double maxs = (total > view) ? (total - view) : 0.0;
    if (fb->scroll > maxs) fb->scroll = maxs;
    if (fb->scroll < 0) fb->scroll = 0;

    /* log pane (clipped) */
    cairo_save(cr);
    cairo_rectangle(cr, 0, FBW_HEADER, fb->width, logh);
    cairo_clip(cr);
    double y = FBW_HEADER + FBW_PAD + FBW_LINE - fb->scroll;
    for (size_t i = 0; i < fb_buffer_count(&w->console); ++i) {
        const fb_entry *e = fb_buffer_at(&w->console, i);
        double r, g, b; fbw_level_rgb(e->level, &r, &g, &b);
        cairo_set_source_rgb(cr, r, g, b);
        const char *p = e->text;
        size_t rem = e->len;
        int first = 1;
        for (;;) {
            const char *nl = (rem > 0) ? (const char *)memchr(p, '\n', rem) : NULL;
            size_t linelen = nl ? (size_t)(nl - p) : rem;
            if (y > FBW_HEADER && y < split_y + FBW_LINE) {
                double textx = FBW_PAD + FBW_GUTTER;
                if (first) {
                    const char *mk = (e->level == FB_ERROR) ? "x"
                                   : (e->level == FB_WARN)  ? "!" : ">";
                    cairo_move_to(cr, FBW_PAD, y);
                    cairo_show_text(cr, mk);
                    /* Source location of an error (file:line:col) in a muted tone,
                     * then the message in the level colour -- like a devtools link. */
                    if (e->file != NULL && e->file[0] != '\0') {
                        char locbuf[160];
                        if (e->col > 0)
                            snprintf(locbuf, sizeof locbuf, "%s:%d:%d  ", e->file, e->line, e->col);
                        else if (e->line > 0)
                            snprintf(locbuf, sizeof locbuf, "%s:%d  ", e->file, e->line);
                        else
                            snprintf(locbuf, sizeof locbuf, "%s  ", e->file);
                        cairo_set_source_rgb(cr, 0.55, 0.58, 0.64);
                        cairo_move_to(cr, textx, y);
                        cairo_show_text(cr, locbuf);
                        cairo_text_extents_t lext;
                        cairo_text_extents(cr, locbuf, &lext);
                        textx += lext.x_advance;
                        cairo_set_source_rgb(cr, r, g, b);
                    }
                }
                char buf[1024];
                size_t cpy = (linelen < sizeof buf - 1) ? linelen : sizeof buf - 1;
                memcpy(buf, p, cpy);
                buf[cpy] = '\0';
                cairo_move_to(cr, textx, y);
                cairo_show_text(cr, buf);
            }
            y += FBW_LINE;
            first = 0;
            if (nl == NULL) break;
            rem -= (linelen + 1);
            p = nl + 1;
        }
    }
    if (w->console.overflow) {
        static const char notice[] = "[console output was truncated]";
        cairo_set_source_rgb(cr, 0.55, 0.58, 0.64);
        cairo_move_to(cr, FBW_PAD, y);
        cairo_show_text(cr, notice);
    }
    cairo_restore(cr);

    /* divider */
    cairo_set_source_rgb(cr, 0.30, 0.32, 0.36);
    cairo_rectangle(cr, 0, split_y, fb->width, 3.0);
    cairo_fill(cr);

    /* editor pane */
    double ey0 = split_y + 3.0;
    cairo_set_source_rgb(cr, 0.07, 0.08, 0.09);
    cairo_rectangle(cr, 0, ey0, fb->width, fb->height - ey0);
    cairo_fill(cr);
    cairo_save(cr);
    cairo_rectangle(cr, 0, ey0, fb->width, fb->height - ey0);
    cairo_clip(cr);

    const char *etext = tf_text(&fb->editor);
    size_t elen = tf_len(&fb->editor);
    size_t ecur = tf_cursor(&fb->editor);
    if (elen == 0) {
        cairo_set_source_rgb(cr, 0.45, 0.47, 0.50);
        cairo_move_to(cr, FBW_PAD + FBW_GUTTER, ey0 + FBW_PAD + FBW_LINE);
        cairo_show_text(cr, "type JS here, Ctrl+Enter to run");
        /* still draw the prompt + caret at the start */
        cairo_set_source_rgb(cr, 0.55, 0.85, 0.55);
        cairo_move_to(cr, FBW_PAD, ey0 + FBW_PAD + FBW_LINE);
        cairo_show_text(cr, ">");
        cairo_set_source_rgb(cr, 0.95, 0.95, 0.45);
        cairo_rectangle(cr, FBW_PAD + FBW_GUTTER, ey0 + FBW_PAD + 4.0, 1.5, FBW_LINE);
        cairo_fill(cr);
    } else {
        cairo_set_source_rgb(cr, 0.86, 0.88, 0.91);
        double yy = ey0 + FBW_PAD + FBW_LINE;
        double caret_x = -1, caret_y = -1;
        size_t line_start = 0;
        for (size_t k = 0; k <= elen; ++k) {
            if (k == elen || etext[k] == '\n') {
                size_t ll = k - line_start;
                char buf[1024];
                size_t cpy = (ll < sizeof buf - 1) ? ll : sizeof buf - 1;
                memcpy(buf, etext + line_start, cpy);
                buf[cpy] = '\0';
                if (line_start == 0) {
                    cairo_set_source_rgb(cr, 0.55, 0.85, 0.55);
                    cairo_move_to(cr, FBW_PAD, yy);
                    cairo_show_text(cr, ">");
                    cairo_set_source_rgb(cr, 0.86, 0.88, 0.91);
                }
                cairo_move_to(cr, FBW_PAD + FBW_GUTTER, yy);
                cairo_show_text(cr, buf);
                if (caret_x < 0 && ecur >= line_start && ecur <= k) {
                    char cbuf[1024];
                    size_t cc = ecur - line_start;
                    if (cc > sizeof cbuf - 1) cc = sizeof cbuf - 1;
                    memcpy(cbuf, etext + line_start, cc);
                    cbuf[cc] = '\0';
                    cairo_text_extents_t te;
                    cairo_text_extents(cr, cbuf, &te);
                    caret_x = FBW_PAD + FBW_GUTTER + te.x_advance;
                    caret_y = yy;
                }
                yy += FBW_LINE;
                line_start = k + 1;
                if (k == elen) break;
            }
        }
        if (caret_x >= 0) {
            cairo_set_source_rgb(cr, 0.95, 0.95, 0.45);
            cairo_rectangle(cr, caret_x, caret_y - FBW_LINE + 4.0, 1.5, FBW_LINE);
            cairo_fill(cr);
        }
    }
    cairo_restore(cr);

    cairo_surface_flush(fb->cairo_surface);
    cairo_destroy(cr);
}

static void freebug_redraw_fb(freebug_window *fb) {
    if (fb == NULL || !fb->visible || !fb->configured) return;
    if (freebug_ensure_buffer(fb) != 0) return;
    freebug_paint(fb);
    wl_surface_attach(fb->surface, fb->buffer, 0, 0);
    wl_surface_damage_buffer(fb->surface, 0, 0, fb->width, fb->height);
    wl_surface_commit(fb->surface);
}

static void freebug_redraw(browser_window *w) {
    if (w->freebug != NULL) freebug_redraw_fb(w->freebug);
}

static void freebug_hide(browser_window *w) {
    freebug_window *fb = w->freebug;
    if (fb == NULL || !fb->visible) return;
    if (w->kbd_focus == fb->surface) w->kbd_focus = NULL;
    if (w->ptr_focus == fb->surface) w->ptr_focus = NULL;
    if (fb->cairo_surface) { cairo_surface_destroy(fb->cairo_surface); fb->cairo_surface = NULL; }
    if (fb->buffer) { wl_buffer_destroy(fb->buffer); fb->buffer = NULL; }
    if (fb->shm_data) { munmap(fb->shm_data, fb->shm_size); fb->shm_data = NULL; fb->shm_size = 0; }
    if (fb->deco) { zxdg_toplevel_decoration_v1_destroy(fb->deco); fb->deco = NULL; }
    if (fb->xdg_toplevel) { xdg_toplevel_destroy(fb->xdg_toplevel); fb->xdg_toplevel = NULL; }
    if (fb->xdg_surface) { xdg_surface_destroy(fb->xdg_surface); fb->xdg_surface = NULL; }
    if (fb->surface) { wl_surface_destroy(fb->surface); fb->surface = NULL; }
    fb->visible = 0;
    fb->configured = 0;
}

static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial) {
    freebug_window *fb = (freebug_window *)data;
    xdg_surface_ack_configure(s, serial);
    fb->configured = 1;
    freebug_redraw_fb(fb);
}
static const struct xdg_surface_listener fbw_xdg_surface_listener = { fbw_xdg_surface_configure };

static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                                   int32_t width, int32_t height, struct wl_array *states) {
    (void)t; (void)states;
    freebug_window *fb = (freebug_window *)data;
    if (width > 0) fb->width = width;
    if (height > 0) fb->height = height;
    if (fb->width < 240) fb->width = 240;
    if (fb->height < 160) fb->height = 160;
}
static void fbw_toplevel_close(void *data, struct xdg_toplevel *t) {
    (void)t;
    freebug_window *fb = (freebug_window *)data;
    freebug_hide(fb->owner); /* the window's close button hides it, never quits the app */
}
static const struct xdg_toplevel_listener fbw_toplevel_listener = {
    .configure = fbw_toplevel_configure,
    .close = fbw_toplevel_close,
};

static void freebug_show(browser_window *w) {
    if (w->compositor == NULL || w->wm_base == NULL || w->shm == NULL) return;
    if (w->freebug == NULL) {
        w->freebug = (freebug_window *)calloc(1, sizeof *w->freebug);
        if (w->freebug == NULL) return;
        w->freebug->owner = w;
        w->freebug->width = FBW_W;
        w->freebug->height = FBW_H;
        w->freebug->split = 0.68;
        tf_init(&w->freebug->editor);
    }
    freebug_window *fb = w->freebug;
    if (fb->visible) return;
    fb->surface = wl_compositor_create_surface(w->compositor);
    if (fb->surface == NULL) return;
    fb->xdg_surface = xdg_wm_base_get_xdg_surface(w->wm_base, fb->surface);
    xdg_surface_add_listener(fb->xdg_surface, &fbw_xdg_surface_listener, fb);
    fb->xdg_toplevel = xdg_surface_get_toplevel(fb->xdg_surface);
    xdg_toplevel_add_listener(fb->xdg_toplevel, &fbw_toplevel_listener, fb);
    xdg_toplevel_set_title(fb->xdg_toplevel, "Freebug - Freedom DevTools");
    xdg_toplevel_set_app_id(fb->xdg_toplevel, "org.freedom.freebug");
    if (w->deco_mgr != NULL) {
        fb->deco = zxdg_decoration_manager_v1_get_toplevel_decoration(w->deco_mgr, fb->xdg_toplevel);
        zxdg_toplevel_decoration_v1_set_mode(fb->deco, ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE);
    }
    fb->configured = 0;
    fb->visible = 1;
    wl_surface_commit(fb->surface); /* trigger the initial configure -> first paint */
}

static void freebug_toggle(browser_window *w) {
    if (w->freebug != NULL && w->freebug->visible) freebug_hide(w);
    else freebug_show(w);
}

static void freebug_destroy(browser_window *w) {
    if (w->freebug == NULL) return;
    freebug_hide(w);
    free(w->freebug);
    w->freebug = NULL;
}

static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf) {
    return w->freebug != NULL && w->freebug->visible && w->freebug->surface == sf;
}

static int freebug_is_open(const browser_window *w) {
    return w->freebug != NULL && w->freebug->visible;
}

/* Returns the live page worker for the REPL, lazily (re)opening one bound to the
 * active page's cache if none is kept alive (e.g. just after a tab switch). NULL if
 * there is no page to bind to. */
static tab *freebug_repl_worker(browser_window *w) {
    if (w->tab_worker != NULL) return w->tab_worker;
    if (w->cur_html == NULL) return NULL;
    tab *t = NULL;
    if (tab_open(&t) != TAB_OK) return NULL;
    /* Same unified per-host caps as the visible render (webcaps): the REPL worker
     * evaluates against THIS page, so its network / author-CSS / cookie grants match
     * what the user already sees (present-trust included). */
    wc_caps wc = wc_derive((wc_input){
        .js_mode       = w->js_mode,
        .host_in_js    = page_js_host_allowlisted(w),
        .host_in_allow = page_host_allowlisted(w),
        .reader        = w->reader,
        .user_css      = w->caps.css,
        .user_images   = w->caps.images,
    });
    tab_set_fetcher(t, gui_subresource_fetch, w);
    tab_set_net_allowed(t, wc.net);
    tab_set_css_allowed(t, wc.css);
    seed_session_cookies(t, wc.cookies, w->cur_top); /* REPL worker sees the same cookies */
    int prefers_dark = (!w->reader && w->theme_mode == UI_THEME_DARK);
    tab_page page;
    memset(&page, 0, sizeof page);
    if (tab_load_full(t, w->cur_html, w->cur_html_len, w->cur_top,
                      compute_page_js(w), w->reader, prefers_dark, &page) != TAB_OK) {
        tab_close(t);
        return NULL;
    }
    fb_buffer_free(&w->console);
    w->console = page.console;
    fb_buffer_init(&page.console);
    tab_page_free(&page);
    w->tab_worker = t;
    return t;
}

static void freebug_eval(browser_window *w) {
    freebug_window *fb = w->freebug;
    if (fb == NULL) return;
    const char *code = tf_text(&fb->editor);
    size_t clen = tf_len(&fb->editor);
    if (clen == 0) return;

    char line[1100];
    int n = snprintf(line, sizeof line, "> %.1000s", code);
    if (n > 0) fb_buffer_push(&w->console, FB_LOG, line, strlen(line));

    tab *t = freebug_repl_worker(w);
    if (t == NULL) {
        fb_buffer_push(&w->console, FB_ERROR,
                       "Freebug: no live page to evaluate (reload the page first).", 56);
    } else {
        tab_eval_result r;
        if (tab_eval(t, code, clen, &r) != TAB_OK) {
            if (w->tab_worker == t) { tab_close(w->tab_worker); w->tab_worker = NULL; }
            fb_buffer_push(&w->console, FB_ERROR,
                           "Freebug: evaluation failed (the page worker is gone).", 52);
        } else {
            for (size_t i = 0; i < fb_buffer_count(&r.console); ++i) {
                const fb_entry *e = fb_buffer_at(&r.console, i);
                fb_buffer_push_loc(&w->console, e->level, e->text, e->len,
                                   e->file, e->line, e->col);
            }
            char out[1100];
            int m = snprintf(out, sizeof out, "%s %.1000s",
                             r.is_exception ? "x" : "=", r.value ? r.value : "undefined");
            if (m > 0) fb_buffer_push(&w->console, r.is_exception ? FB_ERROR : FB_INFO,
                                      out, strlen(out));
            tab_eval_result_free(&r);
        }
    }
    tf_clear(&fb->editor);
    fb->scroll = 1e9; /* jump to the bottom; paint clamps it */
    freebug_redraw_fb(fb);
}

static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                               const char *utf8, int n, int ctrl, int shift) {
    freebug_window *fb = w->freebug;
    if (fb == NULL) return;
    (void)shift;
    if (sym == XKB_KEY_F12 || sym == XKB_KEY_Escape) { freebug_hide(w); redraw(w); return; }
    if (ctrl && (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter)) { freebug_eval(w); return; }
    if (ctrl && (sym == XKB_KEY_c || sym == XKB_KEY_C)) {
        freebug_copy_console(w); freebug_redraw_fb(fb); return;
    }
    if (ctrl && (sym == XKB_KEY_l || sym == XKB_KEY_L)) {
        tf_clear(&fb->editor); freebug_redraw_fb(fb); return;
    }
    if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
        tf_insert(&fb->editor, '\n'); freebug_redraw_fb(fb); return;
    }
    if (sym == XKB_KEY_BackSpace) { tf_backspace(&fb->editor); freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Delete)    { tf_delete(&fb->editor);    freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Left)      { tf_move(&fb->editor, -1);  freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Right)     { tf_move(&fb->editor, 1);   freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Home)      { tf_home(&fb->editor);      freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_End)       { tf_end(&fb->editor);       freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Up)        { fb->scroll -= FBW_LINE * 3; if (fb->scroll < 0) fb->scroll = 0; freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Down)      { fb->scroll += FBW_LINE * 3; freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Page_Up)   { fb->scroll -= 200; if (fb->scroll < 0) fb->scroll = 0; freebug_redraw_fb(fb); return; }
    if (sym == XKB_KEY_Page_Down) { fb->scroll += 200; freebug_redraw_fb(fb); return; }
    if (!ctrl && n > 0) {
        for (int i = 0; i < n; ++i) {
            char c = utf8[i];
            if (c == '\t' || (unsigned char)c >= 0x20) tf_insert(&fb->editor, c);
        }
        freebug_redraw_fb(fb);
    }
}

static void freebug_pointer_button(browser_window *w, uint32_t serial,
                                    uint32_t button, uint32_t state) {
    freebug_window *fb = w->freebug;
    if (fb == NULL) return;
    if (button != UI_BTN_LEFT) return;
    if (state == WL_POINTER_BUTTON_STATE_RELEASED) { fb->dragging_split = 0; return; }
    w->last_serial = serial;
    double sy = fbw_split_y(fb);
    if (w->ptr_y >= sy - 4.0 && w->ptr_y <= sy + 7.0) { fb->dragging_split = 1; return; }
    /* copy button hit-test */
    double cbx = fb->width - FBW_PAD - FBW_COPY_BTN_W;
    double cby = (FBW_HEADER - FBW_COPY_BTN_H) / 2.0;
    if (w->ptr_x >= cbx && w->ptr_x < cbx + FBW_COPY_BTN_W &&
        w->ptr_y >= cby && w->ptr_y < cby + FBW_COPY_BTN_H) {
        freebug_copy_console(w);
        return;
    }
}

static void freebug_pointer_motion(browser_window *w) {
    freebug_window *fb = w->freebug;
    if (fb == NULL) return;
    /* Track hover over the copy button for the visual highlight. */
    double cbx = fb->width - FBW_PAD - FBW_COPY_BTN_W;
    double cby = (FBW_HEADER - FBW_COPY_BTN_H) / 2.0;
    int over = (w->ptr_x >= cbx && w->ptr_x < cbx + FBW_COPY_BTN_W &&
                w->ptr_y >= cby && w->ptr_y < cby + FBW_COPY_BTN_H);
    if (over != fb->hover_copy) {
        fb->hover_copy = over;
        freebug_redraw_fb(fb);
    }
    if (!fb->dragging_split) return;
    double body = (double)fb->height - FBW_HEADER;
    if (body < 1.0) body = 1.0;
    double s = (w->ptr_y - FBW_HEADER) / body;
    if (s < FBW_MIN_SPLIT) s = FBW_MIN_SPLIT;
    if (s > FBW_MAX_SPLIT) s = FBW_MAX_SPLIT;
    fb->split = s;
    freebug_redraw_fb(fb);
}

static void freebug_pointer_axis(browser_window *w, wl_fixed_t value) {
    freebug_window *fb = w->freebug;
    if (fb == NULL) return;
    double v = wl_fixed_to_double(value);
    fb->scroll += (v > 0.0) ? (FBW_LINE * 3) : -(FBW_LINE * 3);
    if (fb->scroll < 0) fb->scroll = 0;
    freebug_redraw_fb(fb);
}

/* ===================== end Freebug ===================== */

/* Forward declarations for pointer event handlers below. dispatch_mouse_event is
 * defined further down (after dispatch_js_event) but called from ptr_enter/leave
 * /motion too. */
static void dispatch_mouse_event(browser_window *w, dom_node_id node_id,
                                 const char *event_type,
                                 int client_x, int client_y, int button);

static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_surface *sf, wl_fixed_t x, wl_fixed_t y) {
    (void)p;
    browser_window *w = (browser_window *)d;
    w->pointer_serial = s;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
    w->ptr_focus = sf; /* route later pointer events to the focused window */
    set_cursor(w, 0);
    if (freebug_owns_surface(w, sf)) return;
    update_hover(w);
    /* Dispatch mouseenter on the element under the pointer. */
    dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y);
    if (nid != DOM_NODE_NONE) {
        w->mouse_hover_node = nid;
        dispatch_mouse_event(w, nid, "mouseenter", (int)w->ptr_x, (int)w->ptr_y, 0);
    }
}
static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf) {
    (void)p; (void)s;
    browser_window *w = (browser_window *)d;
    if (w->ptr_focus == sf) w->ptr_focus = NULL;
    /* Dispatch mouseleave on the last hovered node before clearing. */
    if (w->mouse_hover_node != DOM_NODE_NONE) {
        dispatch_mouse_event(w, w->mouse_hover_node, "mouseleave",
                             (int)w->ptr_x, (int)w->ptr_y, 0);
        w->mouse_hover_node = DOM_NODE_NONE;
    }
    if (w->hover_href != NULL || w->hot != UI_HOT_NONE) {
        w->hover_href = NULL;
        w->hover_cursor = CSS_CUR_UNSET;
        w->hot = UI_HOT_NONE;
        redraw(w);
    }
}
static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y) {
    (void)p; (void)t;
    browser_window *w = (browser_window *)d;
    w->ptr_x = wl_fixed_to_double(x);
    w->ptr_y = wl_fixed_to_double(y);
    if (freebug_owns_surface(w, w->ptr_focus)) { freebug_pointer_motion(w); return; }
    if (w->dragging_scroll) { scrollbar_drag_to(w); return; }
    update_hover(w);
    /* Track hovered-node changes for JS mouseover/mouseout events. */
    if (w->js_mode != JSP_OFF && w->tab_worker != NULL) {
        dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y);
        if (nid != w->mouse_hover_node) {
            if (w->mouse_hover_node != DOM_NODE_NONE) {
                dispatch_mouse_event(w, w->mouse_hover_node, "mouseout",
                                     (int)w->ptr_x, (int)w->ptr_y, 0);
            }
            if (nid != DOM_NODE_NONE) {
                dispatch_mouse_event(w, nid, "mouseover",
                                     (int)w->ptr_x, (int)w->ptr_y, 0);
            }
            w->mouse_hover_node = nid;
        }
    }
}

static void load_current(browser_window *w) {
    const char *url = browser_current_url(&w->bs);
    if (url != NULL) {
        browser_set_url_bar(&w->bs, url);
        do_load(w, url);
    }
}

/* Commits the URL bar like a real omnibox: an existing local file is opened as
 * before; otherwise url_omnibox (pure) decides between navigating to a site and
 * running a DuckDuckGo HTML search, building the absolute https URL either way. So
 * "example.com" becomes https://example.com and "best linux distro" becomes a
 * search, instead of the old "cannot read file" dead end. */
static void go_omnibox(browser_window *w) {
    const char *raw = w->bs.url_bar;
    if (raw == NULL || raw[0] == '\0') return;

    /* Internal pages navigate directly (url_omnibox would fail-closed a foreign
     * scheme into a web search, which is right for javascript:/file: but not for
     * the browser's own about: pages). */
    if (strcmp(raw, "about:bookmarks") == 0 || strcmp(raw, "about:blank") == 0) {
        do_load(w, raw);
        return;
    }

    /* A typed file:// URL navigates to its path (do_load rebuilds the file:// origin),
     * so the URL bar / history / link base stay a plain path that link_nav resolves. */
    if (url_is_file(raw)) {
        const char *p = url_file_path(raw);
        if (p != NULL && access(p, R_OK) == 0) {
            if (browser_navigate(&w->bs, p) == BROWSER_OK) load_current(w);
            return;
        }
    }

    /* A readable local path keeps the file-browsing capability (the start page is a
     * relative path), and must win over the host heuristic ("docs/index.html"). */
    if (!is_https_url(raw) && !is_overlay_http_url(raw) && access(raw, R_OK) == 0) {
        if (browser_navigate(&w->bs, raw) == BROWSER_OK) load_current(w);
        return;
    }

    char target[URL_MAX_LEN];
    url_omni_kind kind;
    if (url_omnibox(raw, &kind, target, sizeof target) == URL_OK &&
        browser_navigate(&w->bs, target) == BROWSER_OK) {
        do_load(w, target);
        return;
    }
    /* Fail closed to the legacy path (e.g. about:blank or an OOM in the bounded build). */
    browser_commit_url_bar(&w->bs);
    load_current(w);
}

static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                              const char *event_type, const char *key,
                              int key_code, const char *value);

static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
                       uint32_t button, uint32_t state) {
    (void)p; (void)t;
    browser_window *w = (browser_window *)d;
    w->last_serial = serial; /* pointer.button serial is valid for set_selection */
    if (freebug_owns_surface(w, w->ptr_focus)) {
        freebug_pointer_button(w, serial, button, state);
        return;
    }
    if (button != UI_BTN_LEFT) return;
    if (state == WL_POINTER_BUTTON_STATE_RELEASED) {
        if (w->dragging_scroll) { w->dragging_scroll = 0; redraw(w); }
        /* Dispatch mouseup on the element under the pointer. */
        if (w->js_mode != JSP_OFF && w->tab_worker != NULL && !freebug_owns_surface(w, w->ptr_focus)) {
            dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y);
            if (nid != DOM_NODE_NONE)
                dispatch_mouse_event(w, nid, "mouseup", (int)w->ptr_x, (int)w->ptr_y, 0);
        }
        return;
    }
    /* state == WL_POINTER_BUTTON_STATE_PRESSED below. */
    /* Dispatch mousedown before any chrome logic so JS handlers see the press even
     * when the UI consumes the release (e.g. toolbar click). Only content-area
     * presses get dispatched (chrome has no DOM element). */
    if (w->js_mode != JSP_OFF && w->tab_worker != NULL && !freebug_owns_surface(w, w->ptr_focus)) {
        double tbtop = tabbar_top(w);
        double top_of_toolbar = toolbar_top(w);
        double bottom_of_chrome = top_of_toolbar + UI_TOOLBAR_H;
        if (w->ptr_y >= tbtop + UI_TABBAR_H && w->ptr_y >= bottom_of_chrome) {
            dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y);
            if (nid != DOM_NODE_NONE)
                dispatch_mouse_event(w, nid, "mousedown", (int)w->ptr_x, (int)w->ptr_y, 0);
        }
    }

    double ttop = toolbar_top(w);

    /* Tab strip (between titlebar and toolbar): the "+" opens a tab, the close 'x' at
     * a tab's right edge closes it, and a click on the body switches to it. */
    double tbtop = tabbar_top(w);
    if (w->ptr_y >= tbtop && w->ptr_y < tbtop + UI_TABBAR_H) {
        double nx = newtab_x(w);
        if (w->ptr_x >= nx && w->ptr_x < nx + UI_TAB_NEW_W) { tab_new(w, NULL); return; }
        double tw = tab_width(w);
        int i = (int)(w->ptr_x / tw);
        if (i >= 0 && i < w->tab_count) {
            double cxr = (double)i * tw + tw - UI_TAB_CLOSE_W;
            if (w->tab_count > 1 && w->ptr_x >= cxr && w->ptr_x < (double)i * tw + tw)
                uitab_close(w, i);
            else
                tab_switch(w, i);
        }
        return; /* clicks anywhere on the strip stay on the strip */
    }

    /* While the options menu is open it captures the click: a hit on a row toggles
     * that capability and re-renders from cache (no network); any click elsewhere
     * dismisses the menu. */
    if (w->menu_open) {
        double mx, my, mw, mh, ih;
        menu_panel_rect(w, &mx, &my, &mw, &mh, &ih);
        int inside = (w->ptr_x >= mx && w->ptr_x < mx + mw
                   && w->ptr_y >= my && w->ptr_y < my + mh);
        if (inside) {
            double bx, by, bw, bh;
            ua_box_rect(w, &bx, &by, &bw, &bh);
            if (w->ptr_x >= bx && w->ptr_x < bx + bw && w->ptr_y >= by && w->ptr_y < by + bh) {
                w->ua_field_focused = 1; /* edit the User-Agent */
                w->url_bar_focused = 0;
            } else {
                w->ua_field_focused = 0;
                if (w->ptr_y >= my + UI_MENU_PAD) {
                    size_t row = (size_t)((w->ptr_y - (my + UI_MENU_PAD)) / ih);
                    if (row < UI_MENU_COUNT) menu_item_toggle(w, row);
                }
            }
        } else {
            w->menu_open = 0;
            w->ua_field_focused = 0;
        }
        redraw(w);
        return;
    }

    /* Dragging a window border starts an interactive resize (CSD only; the
     * compositor owns the edges under server-side decorations). Checked before the
     * scrollbar so the extreme edge always resizes; the rest of the gutter drags. */
    if (w->use_csd && !w->maximized) {
        uint32_t edge = resize_edge_at(w, w->ptr_x, w->ptr_y);
        if (edge != XDG_TOPLEVEL_RESIZE_EDGE_NONE) {
            if (w->seat != NULL)
                xdg_toplevel_resize(w->xdg_toplevel, w->seat, serial, edge);
            return;
        }
    }

    /* The scrollbar captures the press: grabbing the thumb starts a drag; clicking
     * the track jumps the thumb under the cursor and then drags. */
    {
        double tx, ty, trh, thy, thh;
        if (scrollbar_metrics(w, &tx, &ty, &trh, &thy, &thh)
            && w->ptr_x >= tx && w->ptr_x <= tx + UI_SCROLLBAR_W
            && w->ptr_y >= ty && w->ptr_y <= ty + trh) {
            w->scroll_grab_dy = (w->ptr_y >= thy && w->ptr_y <= thy + thh)
                                ? (w->ptr_y - thy)   /* grabbed the thumb */
                                : (thh / 2.0);       /* clicked the track: center on cursor */
            w->dragging_scroll = 1;
            scrollbar_drag_to(w);
            return;
        }
    }

    /* Client-side decoration controls: close / maximize-toggle / minimize, and a
     * drag on the empty titlebar moves the window. */
    if (w->use_csd && w->ptr_y < UI_TITLEBAR_H) {
        double min_x, max_x, close_x;
        window_button_rects(w, &min_x, &max_x, &close_x);
        if (w->ptr_x >= close_x) {
            w->running = 0;
        } else if (w->ptr_x >= max_x) {
            if (w->maximized) xdg_toplevel_unset_maximized(w->xdg_toplevel);
            else              xdg_toplevel_set_maximized(w->xdg_toplevel);
        } else if (w->ptr_x >= min_x) {
            xdg_toplevel_set_minimized(w->xdg_toplevel);
        } else if (w->seat != NULL) {
            xdg_toplevel_move(w->xdg_toplevel, w->seat, serial);
        }
        return;
    }

    double back_x, fwd_x, url_x, url_w, go_x, menu_x;
    toolbar_rects(w, &back_x, &fwd_x, &url_x, &url_w, &go_x, &menu_x);

    if (w->ptr_y >= ttop && w->ptr_y < ttop + UI_TOOLBAR_H) {
        if (w->ptr_x >= menu_x) {
            w->menu_open = 1;
        } else if (w->ptr_x >= go_x && w->ptr_x < menu_x) {
            go_omnibox(w);
        } else if (w->ptr_x >= UI_RELOAD_X && w->ptr_x < UI_RELOAD_X + UI_BTN_W) {
            load_current(w);  /* reload: re-fetch, full TLS/PQ policy re-applied (also F5/Ctrl+R) */
        } else if (w->ptr_x >= url_x && w->ptr_x < url_x + url_w) {
            w->url_bar_focused = 1;
            w->focused_input = -1; /* the URL bar takes the keyboard */
            /* Place cursor roughly by pixel offset. */
            double cx = w->ptr_x - url_x - UI_MARGIN;
            w->bs.url_bar_cursor = 0;
            cairo_t *cr = cairo_create(w->cairo_surface);
            cairo_select_font_face(cr, "monospace", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
            cairo_set_font_size(cr, UI_FONT_SIZE);
            cairo_text_extents_t te;
            double acc = 0.0;
            for (size_t i = 0; i < w->bs.url_bar_len; ++i) {
                char tmp[2] = { w->bs.url_bar[i], '\0' };
                cairo_text_extents(cr, tmp, &te);
                acc += te.x_advance;
                if (acc >= cx) { w->bs.url_bar_cursor = i; break; }
                w->bs.url_bar_cursor = i + 1;
            }
            w->bs.url_bar_anchor = w->bs.url_bar_cursor;  /* a click collapses any selection */
            cairo_destroy(cr);
        } else if (w->ptr_x >= fwd_x && w->ptr_x < fwd_x + UI_BTN_W) {
            if (browser_forward(&w->bs) == BROWSER_OK) load_current(w);
        } else if (w->ptr_x >= back_x && w->ptr_x < back_x + UI_BTN_W) {
            if (browser_back(&w->bs) == BROWSER_OK) load_current(w);
        } else {
            w->url_bar_focused = 0;
        }
    } else {
        /* Omnibox autocomplete dropdown: a click on a favorite row commits it (the
         * dropdown overlays the content top, so this is checked before content). */
        if (w->url_bar_focused && w->omni_sugg_n > 0) {
            double dtop = ttop + UI_TOOLBAR_H;
            if (w->ptr_x >= url_x && w->ptr_x < url_x + url_w &&
                w->ptr_y >= dtop && w->ptr_y < dtop + UI_OMNI_ROW_H * (double)w->omni_sugg_n) {
                int row = (int)((w->ptr_y - dtop) / UI_OMNI_ROW_H);
                if (row >= 0 && row < w->omni_sugg_n) {
                    browser_set_url_bar(&w->bs, w->omni_sugg[row]);
                    w->omni_sugg_n = 0;
                    w->omni_sel = -1;
                    go_omnibox(w);
                    w->url_bar_focused = 0;
                    redraw(w);
                    return;
                }
            }
        }
        /* Content area. A click first hit-tests the form controls: an editable box
         * takes focus, a submit button submits its form. Otherwise a hyperlink is
         * followed (the security decision lives in the pure ln_resolve).
         * Before clearing focus, dispatch blur on the old focused input so JS sees
         * the loss of focus. */
        dom_node_id old_nid = DOM_NODE_NONE;
        if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
            const rd_block *b = w->inputs[w->focused_input].blk;
            if (b != NULL) old_nid = b->node_id;
        }
        w->url_bar_focused = 0;
        w->focused_input = -1;
        const rd_block *ctl = input_at_point(w, w->ptr_x, w->ptr_y);
        if (ctl != NULL) {
            if (ctl->input_type == PV_IN_SUBMIT) {
                /* Dispatch blur before submit. */
                if (old_nid != DOM_NODE_NONE)
                    dispatch_js_event(w, old_nid, "blur", NULL, 0, NULL);
                submit_form(w, ctl);
            } else if (input_is_editable(ctl->input_type)) {
                for (size_t i = 0; i < w->input_count; ++i) {
                    if (w->inputs[i].blk == ctl) {
                        /* Dispatch blur on old, focus on new. */
                        if (old_nid != ctl->node_id && old_nid != DOM_NODE_NONE)
                            dispatch_js_event(w, old_nid, "blur", NULL, 0, NULL);
                        w->focused_input = (int)i;
                        dispatch_js_event(w, ctl->node_id, "focus", NULL, 0, NULL);
                        break;
                    }
                }
            }
            /* PV_IN_BUTTON (reset/generic) is inert in v1. */
        } else {
            /* Clicking non-input: dispatch blur on old if any. */
            if (old_nid != DOM_NODE_NONE)
                dispatch_js_event(w, old_nid, "blur", NULL, 0, NULL);
            dispatch_click(w, w->ptr_x, w->ptr_y);
        }
    }
    redraw(w);
}

/* One body line of scroll, in pixels (the common step unit). */
static double scroll_line_px(const browser_window *w) {
    return w->theme.body_font * w->theme.line_spacing;
}

static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32_t axis, wl_fixed_t value) {
    (void)p; (void)time;
    if (axis != WL_POINTER_AXIS_VERTICAL_SCROLL) return;
    browser_window *w = (browser_window *)data;
    if (freebug_owns_surface(w, w->ptr_focus)) { freebug_pointer_axis(w, value); return; }
    if (w->ptr_y < UI_TOOLBAR_H) return;

    double v = wl_fixed_to_double(value);
    double step = w->theme.scroll_step_lines * scroll_line_px(w);
    w->scroll += (v > 0.0) ? step : -step;
    if (w->scroll < 0.0) w->scroll = 0.0; /* the upper bound is clamped during paint */
    redraw(w);

    /* Dispatch wheel + scroll events to the element under the pointer. */
    if (w->js_mode != JSP_OFF && w->tab_worker != NULL) {
        dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y);
        if (nid != DOM_NODE_NONE) {
            dispatch_mouse_event(w, nid, "wheel", (int)w->ptr_x, (int)w->ptr_y, -1);
            dispatch_js_event(w, nid, "scroll", NULL, 0, NULL);
        }
    }
}

static void ptr_frame(void *d, struct wl_pointer *p) {
    (void)d; (void)p;
}

static const struct wl_pointer_listener pointer_listener = {
    .enter = ptr_enter,
    .leave = ptr_leave,
    .motion = ptr_motion,
    .button = ptr_button,
    .axis = ptr_axis,
    .frame = ptr_frame,
};

/* --- clipboard (wl_data_device) --- */

/* True for a mime type that carries plain UTF-8/Latin text we can paste. */
static int mime_is_text(const char *mime) {
    if (mime == NULL) return 0;
    return strncmp(mime, "text/plain", 10) == 0 ||
           strcmp(mime, "UTF8_STRING") == 0 ||
           strcmp(mime, "TEXT") == 0 ||
           strcmp(mime, "STRING") == 0;
}

/* A mime type advertised by the incoming offer. Remember the best text mime so paste
 * requests exactly what the source provides (preferring an explicit UTF-8 variant). */
static void data_offer_mime(void *data, struct wl_data_offer *offer, const char *mime) {
    browser_window *w = (browser_window *)data;
    if (offer != w->incoming_offer || !mime_is_text(mime)) return;
    w->incoming_offer_has_text = 1;
    int prefer = (strstr(mime, "utf-8") != NULL || strstr(mime, "UTF-8") != NULL);
    if (w->incoming_mime[0] == '\0' || prefer)
        snprintf(w->incoming_mime, sizeof w->incoming_mime, "%s", mime);
}
static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) {
    (void)d; (void)o; (void)a;
}
static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a) {
    (void)d; (void)o; (void)a;
}
static const struct wl_data_offer_listener data_offer_listener = {
    .offer = data_offer_mime,
    .source_actions = data_offer_source_actions,
    .action = data_offer_action,
};

/* A new offer is being introduced: start scanning its mime types. */
static void data_device_data_offer(void *data, struct wl_data_device *dev,
                                   struct wl_data_offer *offer) {
    (void)dev;
    browser_window *w = (browser_window *)data;
    w->incoming_offer = offer;
    w->incoming_offer_has_text = 0;
    w->incoming_mime[0] = '\0';
    wl_data_offer_add_listener(offer, &data_offer_listener, w);
}

/* The clipboard selection changed. Commit the new offer (or NULL when the clipboard
 * was cleared), destroying any previous one we held. */
static void data_device_selection(void *data, struct wl_data_device *dev,
                                  struct wl_data_offer *offer) {
    (void)dev;
    browser_window *w = (browser_window *)data;
    if (w->selection_offer != NULL && w->selection_offer != offer)
        wl_data_offer_destroy(w->selection_offer);
    if (offer == NULL) {
        w->selection_offer = NULL;
        w->selection_offer_has_text = 0;
        w->sel_mime[0] = '\0';
        return;
    }
    w->selection_offer = offer;
    w->selection_offer_has_text = (offer == w->incoming_offer) ? w->incoming_offer_has_text : 0;
    snprintf(w->sel_mime, sizeof w->sel_mime, "%s",
             (offer == w->incoming_offer && w->incoming_mime[0]) ? w->incoming_mime : "text/plain");
}

/* Drag-and-drop events: not supported (the data device is clipboard-only). */
static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
                              struct wl_surface *s, wl_fixed_t x, wl_fixed_t y,
                              struct wl_data_offer *o) {
    (void)d; (void)dev; (void)serial; (void)s; (void)x; (void)y; (void)o;
}
static void data_device_leave(void *d, struct wl_data_device *dev) { (void)d; (void)dev; }
static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                               wl_fixed_t x, wl_fixed_t y) {
    (void)d; (void)dev; (void)t; (void)x; (void)y;
}
static void data_device_drop(void *d, struct wl_data_device *dev) { (void)d; (void)dev; }
static const struct wl_data_device_listener data_device_listener = {
    .data_offer = data_device_data_offer,
    .enter = data_device_enter,
    .leave = data_device_leave,
    .motion = data_device_motion,
    .drop = data_device_drop,
    .selection = data_device_selection,
};

/* Another client now owns our copied text: drop our source. */
static void data_source_cancelled(void *data, struct wl_data_source *src) {
    browser_window *w = (browser_window *)data;
    if (src == w->copy_source) w->copy_source = NULL;
    wl_data_source_destroy(src);
}
/* A paster asked for our copied text: write it to the pipe and close. */
static void data_source_send(void *data, struct wl_data_source *src,
                             const char *mime, int32_t fd) {
    (void)src; (void)mime;
    browser_window *w = (browser_window *)data;
    const char *t = (w->copy_text != NULL) ? w->copy_text : "";
    size_t len = strlen(t), off = 0;
    while (off < len) {
        ssize_t n = write(fd, t + off, len - off);
        if (n <= 0) break;       /* SIGPIPE is ignored process-wide; a closed reader ends it */
        off += (size_t)n;
    }
    close(fd);
}
static void data_source_target(void *d, struct wl_data_source *s, const char *m) {
    (void)d; (void)s; (void)m;
}
static const struct wl_data_source_listener data_source_listener = {
    .target = data_source_target,
    .send = data_source_send,
    .cancelled = data_source_cancelled,
};

/* Formats the entire Freebug console buffer and places it on the Wayland clipboard,
 * so the user can paste the developer console output elsewhere. The format matches
 * print_console in freedom.c. Called from the Copy button in the Freebug header. */
static void freebug_copy_console(browser_window *w) {
    freebug_window *fb = w->freebug;
    if (fb != NULL) fb->copy_ts = now_ms();
    if (fb != NULL) fb->copy_status = 0;
    if (w->data_device == NULL || w->data_device_manager == NULL) {
        if (fb != NULL) fb->copy_status = 1; /* red: no clipboard */
        return;
    }
    if (fb != NULL) fb->copy_status = 2; /* green: OK */
    size_t n = fb_buffer_count(&w->console);
    size_t est = 128;
    for (size_t i = 0; i < n; ++i) {
        const fb_entry *e = fb_buffer_at(&w->console, i);
        est += e->len + 96;
    }
    if (est > 4u * 1024u * 1024u) est = 4u * 1024u * 1024u;
    char *buf = (char *)malloc(est);
    if (buf == NULL) return;
    size_t pos = 0;
    int rem = (int)est;
    int m = snprintf(buf + pos, (size_t)rem > 0 ? (size_t)rem : 0,
                     "=== Freebug console (%zu) ===\n", n);
    if (m > 0 && m < rem) { pos += (size_t)m; rem -= m; }
    for (size_t i = 0; i < n && rem > 0; ++i) {
        const fb_entry *e = fb_buffer_at(&w->console, i);
        if (e->file != NULL && e->file[0] != '\0')
            m = snprintf(buf + pos, (size_t)rem > 0 ? (size_t)rem : 0,
                         "[%s] %s:%d:%d  %s\n", fb_level_name(e->level),
                         e->file, e->line, e->col, e->text);
        else
            m = snprintf(buf + pos, (size_t)rem > 0 ? (size_t)rem : 0,
                         "[%s] %s\n", fb_level_name(e->level), e->text);
        if (m > 0 && m < rem) { pos += (size_t)m; rem -= m; }
    }
    if (w->console.overflow && rem > 0) {
        m = snprintf(buf + pos, (size_t)rem > 0 ? (size_t)rem : 0,
                     "[notice] console output was truncated (buffer full)\n");
        if (m > 0 && m < rem) pos += (size_t)m;
    }
    free(w->copy_text);
    w->copy_text = buf;
    if (w->copy_source != NULL) wl_data_source_destroy(w->copy_source);
    w->copy_source = wl_data_device_manager_create_data_source(w->data_device_manager);
    if (w->copy_source == NULL) return;
    wl_data_source_add_listener(w->copy_source, &data_source_listener, w);
    wl_data_source_offer(w->copy_source, "text/plain;charset=utf-8");
    wl_data_source_offer(w->copy_source, "text/plain");
    wl_data_device_set_selection(w->data_device, w->copy_source, w->last_serial);
    /* Roundtrip to ensure the compositor has processed the selection request before
     * we return to the event loop (without this, the clipboard offer stays queued
     * and a paste that follows immediately might miss it). */
    wl_display_roundtrip(w->display);
}

/* Inserts pasted bytes into whichever text target currently has focus (page input,
 * User-Agent box, or the URL bar). Control bytes -- including embedded CR/LF/TAB that
 * a multi-line clipboard would carry -- are dropped so a paste cannot inject a newline
 * into a single-line field; UTF-8 continuation bytes (>= 0x80) pass through. */
static void insert_pasted_text(browser_window *w, const char *text, size_t len) {
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = (unsigned char)text[i];
        if (c < 0x20 || c == 0x7f) continue;
        if (w->ua_field_focused) {
            tf_insert(&w->ua_field, (char)c);
        } else if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
            tf_insert(&w->inputs[w->focused_input].field, (char)c);
        } else if (w->url_bar_focused) {
            browser_url_bar_insert(&w->bs, (char)c);
        } else {
            return; /* nothing focused: paste goes nowhere */
        }
    }
}

/* Ctrl+V: pull the clipboard's text and insert it at the focused field's cursor.
 * Synchronous (like the v1 image fetch): a pipe is handed to the source, the display
 * is flushed so the source -- possibly ourselves -- writes, then we drain to EOF. The
 * read is capped so a hostile clipboard cannot exhaust memory. */
static void clipboard_paste(browser_window *w) {
    if (w->selection_offer == NULL || !w->selection_offer_has_text) return;
    /* Only paste when a text field is focused, else the bytes have nowhere to go. */
    if (!w->ua_field_focused && w->url_bar_focused == 0 &&
        !(w->focused_input >= 0 && (size_t)w->focused_input < w->input_count))
        return;

    int fds[2];
    if (pipe(fds) != 0) return;
    const char *mime = (w->sel_mime[0] != '\0') ? w->sel_mime : "text/plain";
    wl_data_offer_receive(w->selection_offer, mime, fds[1]);
    /* Roundtrip so the source dispatches the receive request (our own data_source_send
     * runs here for a self-paste), then close our write end to bound the read by EOF. */
    wl_display_roundtrip(w->display);
    close(fds[1]);

    char *buf = NULL;
    size_t cap = 0, total = 0;
    const size_t LIMIT = 1u << 20; /* 1 MiB hard cap */
    for (;;) {
        /* Bound the wait: a misbehaving source must not freeze the UI. Local clipboard
         * transfers complete in well under this; a stall just truncates the paste. */
        struct pollfd rp = { .fd = fds[0], .events = POLLIN, .revents = 0 };
        int pr = poll(&rp, 1, 500);
        if (pr <= 0) break; /* timeout or error: stop reading */
        if (total == cap) {
            size_t ncap = (cap == 0) ? 4096 : cap * 2;
            if (ncap > LIMIT) ncap = LIMIT;
            if (ncap == cap) break; /* hit the cap */
            char *nb = (char *)realloc(buf, ncap);
            if (nb == NULL) break;
            buf = nb; cap = ncap;
        }
        ssize_t n = read(fds[0], buf + total, cap - total);
        if (n <= 0) break;
        total += (size_t)n;
    }
    close(fds[0]);
    if (buf != NULL) insert_pasted_text(w, buf, total);
    free(buf);
}

/* Ctrl+C: copy the focused field's text (or, with nothing focused, the page address)
 * to the clipboard by owning a wl_data_source that serves it on demand. */
static void clipboard_copy(browser_window *w) {
    if (w->data_device == NULL || w->data_device_manager == NULL) return;

    const char *text = NULL;
    char selbuf[BROWSER_URL_MAX];
    if (w->ua_field_focused) {
        text = tf_text(&w->ua_field);
    } else if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
        text = tf_text(&w->inputs[w->focused_input].field);
    } else if (w->url_bar_focused) {
        /* Copy just the selection if there is one, else the whole URL bar. */
        size_t s = 0, l = 0;
        if (browser_url_bar_selection(&w->bs, &s, &l) && l < sizeof selbuf) {
            memcpy(selbuf, w->bs.url_bar + s, l);
            selbuf[l] = '\0';
            text = selbuf;
        } else {
            text = w->bs.url_bar;
        }
    } else {
        text = browser_current_url(&w->bs); /* copy the current page's address */
    }
    if (text == NULL || text[0] == '\0') return;

    char *dup = strdup(text);
    if (dup == NULL) return;
    free(w->copy_text);
    w->copy_text = dup;
    if (w->copy_source != NULL) wl_data_source_destroy(w->copy_source);
    w->copy_source = wl_data_device_manager_create_data_source(w->data_device_manager);
    if (w->copy_source == NULL) return;
    wl_data_source_add_listener(w->copy_source, &data_source_listener, w);
    wl_data_source_offer(w->copy_source, "text/plain;charset=utf-8");
    wl_data_source_offer(w->copy_source, "text/plain");
    wl_data_device_set_selection(w->data_device, w->copy_source, w->last_serial);
}

/* Cut the omnibar selection: copy it to the clipboard, then remove it. v1 cut is the
 * URL bar only (page inputs / the UA box have no selection model yet). */
static void clipboard_cut(browser_window *w) {
    if (!w->url_bar_focused) return;
    if (!browser_url_bar_selection(&w->bs, NULL, NULL)) return;
    clipboard_copy(w);                       /* copies just the selection */
    browser_url_bar_delete_selection(&w->bs);
}

/* --- keyboard with xkbcommon --- */

static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint32_t format, int32_t fd, uint32_t size) {
    (void)kbd;
    browser_window *w = (browser_window *)data;
    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) { close(fd); return; }

    char *map_str = (char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (map_str == MAP_FAILED) return;

    if (w->xkb_keymap) xkb_keymap_unref(w->xkb_keymap);
    if (w->xkb_state)  xkb_state_unref(w->xkb_state);

    w->xkb_keymap = xkb_keymap_new_from_string(w->xkb_ctx, map_str,
                                               XKB_KEYMAP_FORMAT_TEXT_V1,
                                               XKB_KEYMAP_COMPILE_NO_FLAGS);
    munmap(map_str, size);
    if (w->xkb_keymap == NULL) return;
    w->xkb_state = xkb_state_new(w->xkb_keymap);
}

static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                           struct wl_surface *sf, struct wl_array *keys) {
    (void)kbd; (void)keys;
    browser_window *w = (browser_window *)d;
    w->last_serial = s; /* keyboard.enter serial is valid for set_selection */
    w->kbd_focus = sf;
}
static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf) {
    (void)kbd; (void)s;
    browser_window *w = (browser_window *)d;
    if (w->kbd_focus == sf) w->kbd_focus = NULL;
}

/* Maps an xkb keysym to a JS event.key string. Returns NULL for printable chars
 * (the utf8 bytes should be used as the key). */
static const char *key_sym_to_js_key(xkb_keysym_t sym) {
    switch (sym) {
    case XKB_KEY_Return: case XKB_KEY_KP_Enter: return "Enter";
    case XKB_KEY_BackSpace: return "Backspace";
    case XKB_KEY_Delete: case XKB_KEY_KP_Delete: return "Delete";
    case XKB_KEY_Escape: return "Escape";
    case XKB_KEY_Tab: case XKB_KEY_KP_Tab: return "Tab";
    case XKB_KEY_Left: return "ArrowLeft";
    case XKB_KEY_Right: return "ArrowRight";
    case XKB_KEY_Up: return "ArrowUp";
    case XKB_KEY_Down: return "ArrowDown";
    case XKB_KEY_Home: return "Home";
    case XKB_KEY_End: return "End";
    case XKB_KEY_Page_Up: return "PageUp";
    case XKB_KEY_Page_Down: return "PageDown";
    case XKB_KEY_Shift_L: case XKB_KEY_Shift_R: return "Shift";
    case XKB_KEY_Control_L: case XKB_KEY_Control_R: return "Control";
    case XKB_KEY_Alt_L: case XKB_KEY_Alt_R: return "Alt";
    case XKB_KEY_Meta_L: case XKB_KEY_Meta_R: return "Meta";
    case XKB_KEY_Caps_Lock: return "CapsLock";
    default: return NULL;
    }
}

/* Maps an xkb keysym to a JS keyCode number. For printable ASCII, returns the
 * ASCII value; for special keys, returns the standard JS keyCode. */
static int key_sym_to_keycode(xkb_keysym_t sym) {
    if (sym >= 0x20 && sym <= 0x7E) return (int)sym;
    switch (sym) {
    case XKB_KEY_Return: case XKB_KEY_KP_Enter: return 13;
    case XKB_KEY_BackSpace: return 8;
    case XKB_KEY_Delete: case XKB_KEY_KP_Delete: return 46;
    case XKB_KEY_Escape: return 27;
    case XKB_KEY_Tab: case XKB_KEY_KP_Tab: return 9;
    case XKB_KEY_Left: return 37;
    case XKB_KEY_Right: return 39;
    case XKB_KEY_Up: return 38;
    case XKB_KEY_Down: return 40;
    case XKB_KEY_Home: return 36;
    case XKB_KEY_End: return 35;
    case XKB_KEY_Page_Up: return 33;
    case XKB_KEY_Page_Down: return 34;
    default: return 0;
    }
}

/* Dispatches a JS DOM event to the worker for the given node_id. The worker
 * returns a re-derived view which is applied via apply_click_result. Since that
 * replaces w->doc and rebuilds w->inputs, focus is cleared before the call and
 * restored afterward if the input still exists. The text value is saved before
 * dispatch and restored after, so live typed content is not lost. */
static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                              const char *event_type, const char *key,
                              int key_code, const char *value) {
    if (w->js_mode == JSP_OFF || w->tab_worker == NULL) return;
    if (node_id == DOM_NODE_NONE || event_type == NULL) return;

    /* Clear focus before apply_click_result (which rebuilds w->inputs). */
    int old_focus = w->focused_input;
    w->focused_input = -1;

    tab_page page;
    memset(&page, 0, sizeof page);
    if (tab_dispatch_event(w->tab_worker, node_id, event_type,
                           key, key_code, value, &page) != TAB_OK) {
        tab_page_free(&page);
        return;
    }
    apply_click_result(w, &page);
    tab_page_free(&page);

    /* Restore focus and value: the fresh inputs have default values from the HTML
     * value attribute; re-set from the saved copy so live typing survives. */
    if (value != NULL && old_focus >= 0) {
        for (size_t i = 0; i < w->input_count; ++i) {
            if (w->inputs[i].blk != NULL && w->inputs[i].blk->node_id == node_id
                && input_is_editable(w->inputs[i].blk->input_type)) {
                tf_set(&w->inputs[i].field, value);
                w->focused_input = (int)i;
                break;
            }
        }
    }
}

/* Dispatches a mouse DOM event to the live JS worker. Like dispatch_js_event but
 * for mouse events (mouseover/mouseout/mousemove/etc.) via tab_dispatch_mouse.
 * The refreshed view is applied with apply_click_result (same as click). */
static void dispatch_mouse_event(browser_window *w, dom_node_id node_id,
                                 const char *event_type,
                                 int client_x, int client_y, int button) {
    if (w->js_mode == JSP_OFF || w->tab_worker == NULL) return;
    if (node_id == DOM_NODE_NONE || event_type == NULL) return;

    tab_page page;
    memset(&page, 0, sizeof page);
    if (tab_dispatch_mouse(w->tab_worker, node_id, event_type,
                           client_x, client_y, button, &page) != TAB_OK) {
        tab_page_free(&page);
        return;
    }
    apply_click_result(w, &page);
    tab_page_free(&page);
}

/* Performs the effect of a single key press. Factored out of keyboard_key so a held
 * key can be re-fired from the repeat timer with the exact same semantics (the caller
 * recomputes sym/utf8/modifiers from the live xkb_state each time). */
static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
                             int n, int ctrl, int shift) {
    /* F12 opens / closes the Freebug developer console (second window). Works from the
     * main window regardless of which field is focused; closing it from inside is handled
     * in freebug_handle_key. */
    if (sym == XKB_KEY_F12) { freebug_toggle(w); return; }

    /* Ctrl+L focuses and clears the URL bar. */
    if (ctrl && !shift && (sym == XKB_KEY_l || sym == XKB_KEY_L)) {
        w->url_bar_focused = 1;
        browser_url_bar_clear(&w->bs);
        redraw(w);
        return;
    }

    /* Ctrl+V pastes the clipboard into the focused field; Ctrl+C copies the focused
     * field's text (or the page address when nothing is focused). */
    if (ctrl && !shift && (sym == XKB_KEY_v || sym == XKB_KEY_V)) {
        clipboard_paste(w);
        redraw(w);
        return;
    }
    if (ctrl && !shift && (sym == XKB_KEY_c || sym == XKB_KEY_C)) {
        clipboard_copy(w);
        return;
    }
    /* Ctrl+X cuts the omnibar selection (copy + delete). */
    if (ctrl && !shift && (sym == XKB_KEY_x || sym == XKB_KEY_X)) {
        clipboard_cut(w);
        redraw(w);
        return;
    }
    /* Ctrl+A selects all of the URL bar when it is focused. */
    if (ctrl && !shift && (sym == XKB_KEY_a || sym == XKB_KEY_A) && w->url_bar_focused) {
        browser_url_bar_select_all(&w->bs);
        redraw(w);
        return;
    }

    /* Ctrl+Shift+E: add current host to exception list and reload insecurely. */
    if (ctrl && shift && sym == XKB_KEY_E) {
        const char *url = browser_current_url(&w->bs);
        char host[256];
        if (url != NULL && host_from_url(url, host, sizeof host)) {
            browser_add_exception(&w->bs, host);
            load_current(w);
        }
        return;
    }

    /* Ctrl+I toggles loading remote images for this session (Privacy by Default:
     * off), the same capability the options menu exposes. Re-renders from the
     * cached source (no network) so the tracking warning and the per-image
     * placeholders update to the new posture. */
    if (ctrl && !shift && (sym == XKB_KEY_i || sym == XKB_KEY_I)) {
        w->caps.images = !w->caps.images;
        profile_sync(w);
        render_current(w);
        redraw(w);
        return;
    }

    /* Ctrl+B toggles a bookmark for the current page (title from the page). The
     * bookmarks live encrypted in the profile; browse them via the menu's
     * "Bookmarks & history" (about:bookmarks). */
    if (ctrl && !shift && (sym == XKB_KEY_b || sym == XKB_KEY_B)) {
        bookmark_toggle_current(w);
        return;
    }

    /* Ctrl+D toggles distraction-free (reader) mode: drop nav/header/footer/aside
     * boilerplate and author styling, center the content in a reading column. */
    if (ctrl && !shift && (sym == XKB_KEY_d || sym == XKB_KEY_D)) {
        toggle_reader(w);
        redraw(w);
        return;
    }

    /* Ctrl+P saves the current page as a vector PDF (selectable text) to the
     * downloads directory. The output filename is derived safely from the page
     * title (pdf_export, fail-closed). */
    if (ctrl && !shift && (sym == XKB_KEY_p || sym == XKB_KEY_P)) {
        export_pdf(w);
        return;
    }

    /* Ctrl+Shift+P saves the current page as a single full-height PNG bitmap (the
     * cheapest artifact for visual review; same safe-title path as Save as PDF). */
    if (ctrl && shift && (sym == XKB_KEY_p || sym == XKB_KEY_P)) {
        export_png(w);
        return;
    }

    /* Ctrl+S saves the current page's cached source to ~/Downloads/freedom (no
     * network); the filename is derived fail-closed from the URL (download module). */
    if (ctrl && !shift && (sym == XKB_KEY_s || sym == XKB_KEY_S)) {
        save_current_page(w);
        return;
    }

    /* Ctrl+R / F5 reloads the current page (re-fetch, full TLS/PQ policy re-applied). */
    if ((ctrl && !shift && (sym == XKB_KEY_r || sym == XKB_KEY_R)) || sym == XKB_KEY_F5) {
        load_current(w);
        return;
    }

    /* Ctrl+Shift+B / A / J add the current host to block.conf / allow.conf / js.conf
     * (hostedit validates fail-closed) and reload the matching filter immediately. */
    if (ctrl && shift && (sym == XKB_KEY_b || sym == XKB_KEY_B)) {
        add_current_host_to_list(w, HOSTLIST_BLOCK);
        return;
    }
    if (ctrl && shift && (sym == XKB_KEY_a || sym == XKB_KEY_A)) {
        add_current_host_to_list(w, HOSTLIST_ALLOW);
        return;
    }
    if (ctrl && shift && (sym == XKB_KEY_j || sym == XKB_KEY_J)) {
        add_current_host_to_list(w, HOSTLIST_JS);
        return;
    }

    /* Zoom: Ctrl + / Ctrl = / Ctrl KP+ zoom in, Ctrl - / Ctrl _ / Ctrl KP- zoom out,
     * Ctrl 0 resets to 100%. The level snaps to the zoom ladder (zoom module). */
    if (ctrl && (sym == XKB_KEY_plus || sym == XKB_KEY_equal || sym == XKB_KEY_KP_Add)) {
        w->zoom_pct = zm_zoom_in(w->zoom_pct);
        apply_zoom(w);
        return;
    }
    if (ctrl && (sym == XKB_KEY_minus || sym == XKB_KEY_underscore || sym == XKB_KEY_KP_Subtract)) {
        w->zoom_pct = zm_zoom_out(w->zoom_pct);
        apply_zoom(w);
        return;
    }
    if (ctrl && (sym == XKB_KEY_0 || sym == XKB_KEY_KP_0)) {
        w->zoom_pct = zm_reset();
        apply_zoom(w);
        return;
    }

    /* Tab shortcuts. Ctrl+T opens a tab, Ctrl+W closes the current one (never the
     * last), Ctrl+Tab / Ctrl+Shift+Tab cycle forward / backward. */
    if (ctrl && !shift && (sym == XKB_KEY_t || sym == XKB_KEY_T)) {
        tab_new(w, NULL);
        return;
    }
    if (ctrl && !shift && (sym == XKB_KEY_w || sym == XKB_KEY_W)) {
        uitab_close(w, w->active_tab);
        return;
    }
    if (ctrl && (sym == XKB_KEY_Tab || sym == XKB_KEY_ISO_Left_Tab)) {
        if (w->tab_count > 1) {
            int next = shift ? (w->active_tab + w->tab_count - 1) % w->tab_count
                             : (w->active_tab + 1) % w->tab_count;
            tab_switch(w, next);
        }
        return;
    }

    /* Editing the configurable User-Agent in the options menu takes priority over
     * the URL bar and page scroll. Enter applies it (used on the next load). */
    if (w->ua_field_focused) {
        if (sym == XKB_KEY_Escape) {
            w->ua_field_focused = 0;
        } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
            w->ua_field_focused = 0;
            browser_set_status(&w->bs, "User-Agent set; reload to apply.", now_ms());
        } else if (sym == XKB_KEY_BackSpace) {
            tf_backspace(&w->ua_field);
        } else if (sym == XKB_KEY_Delete || sym == XKB_KEY_KP_Delete) {
            tf_delete(&w->ua_field);
        } else if (sym == XKB_KEY_Left) {
            tf_move(&w->ua_field, -1);
        } else if (sym == XKB_KEY_Right) {
            tf_move(&w->ua_field, 1);
        } else if (sym == XKB_KEY_Home) {
            tf_home(&w->ua_field);
        } else if (sym == XKB_KEY_End) {
            tf_end(&w->ua_field);
        } else if (n > 0) {
            for (int i = 0; i < n; ++i) tf_insert(&w->ua_field, utf8[i]);
        }
        redraw(w);
        return;
    }

    /* A focused page text control (e.g. a search box) captures the keyboard before
     * scroll: typing edits its live value, Enter submits the owning form (the load
     * re-applies the full TLS/PQ policy, Zero Trust), Escape releases focus. Same
     * edit mechanics as the URL bar and the User-Agent box, over the shared
     * textfield primitive. submit_form may reload and rebuild w->inputs, so the
     * block is captured and focus dropped before calling it. */
    if (w->focused_input >= 0 && (size_t)w->focused_input < w->input_count) {
        tf_field *field = &w->inputs[w->focused_input].field;
        dom_node_id nid = w->inputs[w->focused_input].blk != NULL
                            ? w->inputs[w->focused_input].blk->node_id : DOM_NODE_NONE;
        const char *old_val = tf_text(field);
        const char *js_key = key_sym_to_js_key(sym);
        int kc = key_sym_to_keycode(sym);

        if (sym == XKB_KEY_Escape) {
            /* Dispatch blur before clearing focus. */
            dispatch_js_event(w, nid, "blur", NULL, 0, NULL);
            w->focused_input = -1;
        } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
            /* Dispatch change event with current value before submit. */
            dispatch_js_event(w, nid, "change", js_key, kc, old_val);
            const rd_block *blk = w->inputs[w->focused_input].blk;
            w->focused_input = -1;
            submit_form(w, blk);
        } else if (sym == XKB_KEY_BackSpace) {
            tf_backspace(field);
            const char *new_val = tf_text(field);
            dispatch_js_event(w, nid, "input", js_key, kc, new_val);
        } else if (sym == XKB_KEY_Delete || sym == XKB_KEY_KP_Delete) {
            tf_delete(field);
            const char *new_val = tf_text(field);
            dispatch_js_event(w, nid, "input", js_key, kc, new_val);
        } else if (sym == XKB_KEY_Left || sym == XKB_KEY_Right
                   || sym == XKB_KEY_Up || sym == XKB_KEY_Down
                   || sym == XKB_KEY_Home || sym == XKB_KEY_End
                   || sym == XKB_KEY_Page_Up || sym == XKB_KEY_Page_Down) {
            tf_move(field, (sym == XKB_KEY_Right || sym == XKB_KEY_Down) ? 1 : -1);
            /* Cursor-only event: just keydown */
            dispatch_js_event(w, nid, "keydown", js_key, kc, old_val);
        } else if (n > 0 && (unsigned char)utf8[0] >= 0x20) {
            for (int i = 0; i < n; ++i) tf_insert(field, utf8[i]);
            const char *new_val = tf_text(field);
            dispatch_js_event(w, nid, "input", js_key, kc, new_val);
        }
        redraw(w);
        return;
    }

    if (!w->url_bar_focused) {
        /* Page scroll plus vim-style keys: j/k by line, space/b by page, gg to the
         * top, G to the bottom. pending_g remembers a lone 'g' for the gg sequence. */
        double line = scroll_line_px(w);
        double page = w->theme.page_step_lines * line;
        int was_g = w->pending_g;
        w->pending_g = 0;
        int scrolled = 1;
        if (sym == XKB_KEY_Up || sym == XKB_KEY_k) { w->scroll -= line; }
        else if (sym == XKB_KEY_Down || sym == XKB_KEY_j) { w->scroll += line; }
        else if (sym == XKB_KEY_Page_Up || sym == XKB_KEY_b) { w->scroll -= page; }
        else if (sym == XKB_KEY_Page_Down || sym == XKB_KEY_space) { w->scroll += page; }
        else if (sym == XKB_KEY_Home) { w->scroll = 0.0; }
        else if (sym == XKB_KEY_End || sym == XKB_KEY_G) { w->scroll = w->content_total_h; }
        else if (sym == XKB_KEY_g) { if (was_g) w->scroll = 0.0; else w->pending_g = 1; scrolled = 0; }
        else { scrolled = 0; }
        if (w->scroll < 0.0) w->scroll = 0.0;
        redraw(w);
        /* Dispatch scroll event if the page actually scrolled. */
        if (scrolled && w->js_mode != JSP_OFF && w->tab_worker != NULL) {
            dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y);
            if (nid != DOM_NODE_NONE)
                dispatch_js_event(w, nid, "scroll", NULL, 0, NULL);
        }
        return;
    }

    if (sym == XKB_KEY_Escape) {
        w->url_bar_focused = 0;
        w->omni_sugg_n = 0; w->omni_sel = -1;
    } else if (sym == XKB_KEY_Return || sym == XKB_KEY_KP_Enter) {
        /* Commit a highlighted favorite suggestion, else what is typed. */
        if (w->omni_sel >= 0 && w->omni_sel < w->omni_sugg_n)
            browser_set_url_bar(&w->bs, w->omni_sugg[w->omni_sel]);
        go_omnibox(w);
        w->url_bar_focused = 0;
        w->omni_sugg_n = 0; w->omni_sel = -1;
    } else if (sym == XKB_KEY_Tab || sym == XKB_KEY_ISO_Left_Tab) {
        /* Tab completes the URL bar to the top (or highlighted) favorite. */
        omni_refresh(w);
        if (w->omni_sugg_n > 0) {
            int idx = (w->omni_sel >= 0) ? w->omni_sel : 0;
            browser_set_url_bar(&w->bs, w->omni_sugg[idx]);
            w->omni_sel = -1;
        }
    } else if (sym == XKB_KEY_Down) {
        omni_refresh(w);
        if (w->omni_sugg_n > 0)
            w->omni_sel = (w->omni_sel + 1 < w->omni_sugg_n) ? w->omni_sel + 1 : 0;
    } else if (sym == XKB_KEY_Up) {
        w->omni_sel = (w->omni_sel > 0) ? w->omni_sel - 1 : -1;
    } else if (sym == XKB_KEY_BackSpace) {
        browser_url_bar_backspace(&w->bs);
        w->omni_sel = -1;
    } else if (sym == XKB_KEY_Delete || sym == XKB_KEY_KP_Delete) {
        browser_url_bar_delete(&w->bs);
        w->omni_sel = -1;
    } else if (sym == XKB_KEY_Left) {
        if (shift) browser_url_bar_extend_cursor(&w->bs, -1);
        else       browser_url_bar_move_cursor(&w->bs, -1);
    } else if (sym == XKB_KEY_Right) {
        if (shift) browser_url_bar_extend_cursor(&w->bs, 1);
        else       browser_url_bar_move_cursor(&w->bs, 1);
    } else if (sym == XKB_KEY_Home) {
        browser_url_bar_set_cursor(&w->bs, 0, shift);            /* shift extends */
    } else if (sym == XKB_KEY_End) {
        browser_url_bar_set_cursor(&w->bs, w->bs.url_bar_len, shift);
    } else if (n > 0) {
        for (int i = 0; i < n; ++i) {
            browser_url_bar_insert(&w->bs, utf8[i]);
        }
        w->omni_sel = -1;
    }
    redraw(w);
}

/* Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion
 * and scrolling. A Ctrl chord (tab spawn, reload, image toggle...) or Enter must NOT
 * repeat -- holding them would loop a navigation or spawn tabs. A printable character
 * (n > 0) repeats so a held letter types, mirroring every text widget. */
static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl) {
    if (ctrl) return 0;
    switch (sym) {
        case XKB_KEY_BackSpace:
        case XKB_KEY_Delete: case XKB_KEY_KP_Delete:
        case XKB_KEY_Left:   case XKB_KEY_Right:
        case XKB_KEY_Up:     case XKB_KEY_Down:
        case XKB_KEY_Page_Up: case XKB_KEY_Page_Down:
            return 1;
        default:
            return n > 0;
    }
}

/* Arms the repeat timer for key: first fire after repeat_delay ms, then every
 * 1/repeat_rate s. A held key thus repeats until released (key_repeat_stop). */
static void key_repeat_arm(browser_window *w, uint32_t key) {
    if (w->repeat_timer_fd < 0 || w->repeat_rate <= 0) return;
    w->repeat_key = key;
    long interval_ns = 1000000000L / w->repeat_rate;
    struct itimerspec its;
    its.it_value.tv_sec  = w->repeat_delay / 1000;
    its.it_value.tv_nsec = (long)(w->repeat_delay % 1000) * 1000000L;
    its.it_interval.tv_sec  = interval_ns / 1000000000L;
    its.it_interval.tv_nsec = interval_ns % 1000000000L;
    timerfd_settime(w->repeat_timer_fd, 0, &its, NULL);
}

/* Disarms repeat (key released, or a non-repeatable key was pressed). */
static void key_repeat_stop(browser_window *w) {
    w->repeat_key = 0;
    if (w->repeat_timer_fd < 0) return;
    struct itimerspec off;
    memset(&off, 0, sizeof off);
    timerfd_settime(w->repeat_timer_fd, 0, &off, NULL);
}

/* Re-fires the currently held key. Called from the event loop when the timer expires.
 * Modifiers/keysym are recomputed from the live xkb_state, so a chord released
 * mid-repeat degrades correctly. */
static void key_repeat_fire(browser_window *w) {
    if (w->repeat_key == 0 || w->xkb_state == NULL) return;
    uint32_t kc = w->repeat_key + 8;
    xkb_keysym_t sym = xkb_state_key_get_one_sym(w->xkb_state, kc);
    char utf8[16];
    int n = xkb_state_key_get_utf8(w->xkb_state, kc, utf8, sizeof utf8);
    int ctrl = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_CTRL,
                                            XKB_STATE_MODS_EFFECTIVE);
    int shift = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_SHIFT,
                                             XKB_STATE_MODS_EFFECTIVE);
    if (!key_is_repeatable(sym, n, ctrl)) { key_repeat_stop(w); return; }
    handle_key_press(w, sym, utf8, n, ctrl, shift);
}

static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                         uint32_t time, uint32_t key, uint32_t state) {
    (void)kbd; (void)time; (void)serial;
    browser_window *w = (browser_window *)data;
    /* last_serial for set_selection is set by keyboard_enter / ptr_button —
     * keyboard.key serials are NOT valid for wl_data_device.set_selection. */
    if (w->xkb_state == NULL) return;

    /* Releasing the held key (or any other key while it repeats) stops the repeat. */
    if (state != WL_KEYBOARD_KEY_STATE_PRESSED) {
        if (key == w->repeat_key) key_repeat_stop(w);
        return;
    }

    xkb_keysym_t sym = xkb_state_key_get_one_sym(w->xkb_state, key + 8);
    char utf8[16];
    int n = xkb_state_key_get_utf8(w->xkb_state, key + 8, utf8, sizeof utf8);
    int ctrl = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_CTRL,
                                            XKB_STATE_MODS_EFFECTIVE);
    int shift = xkb_state_mod_name_is_active(w->xkb_state, XKB_MOD_NAME_SHIFT,
                                             XKB_STATE_MODS_EFFECTIVE);

    /* Route to the Freebug console when it holds keyboard focus (it has its own,
     * simpler editor key handling and does not use the main window's auto-repeat). */
    if (freebug_owns_surface(w, w->kbd_focus)) {
        key_repeat_stop(w);
        freebug_handle_key(w, sym, utf8, n, ctrl, shift);
        return;
    }

    handle_key_press(w, sym, utf8, n, ctrl, shift);

    /* Start (or restart, for a new key) auto-repeat for the keys that warrant it. */
    if (key_is_repeatable(sym, n, ctrl) &&
        w->xkb_keymap != NULL && xkb_keymap_key_repeats(w->xkb_keymap, key + 8))
        key_repeat_arm(w, key);
    else
        key_repeat_stop(w);
}

static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                               uint32_t mods_depressed, uint32_t mods_latched,
                               uint32_t mods_locked, uint32_t group) {
    (void)kbd; (void)s;
    browser_window *w = (browser_window *)data;
    if (w->xkb_state) {
        xkb_state_update_mask(w->xkb_state, mods_depressed, mods_latched, mods_locked, 0, 0, group);
    }
}
static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay) {
    (void)kbd;
    browser_window *w = (browser_window *)d;
    /* rate is repeats/second (0 => repeat disabled); delay is ms before the first. */
    w->repeat_rate = rate;
    w->repeat_delay = delay;
}

static const struct wl_keyboard_listener keyboard_listener = {
    .keymap = keyboard_keymap,
    .enter = keyboard_enter,
    .leave = keyboard_leave,
    .key = keyboard_key,
    .modifiers = keyboard_modifiers,
    .repeat_info = keyboard_repeat_info,
};

/* --- seat --- */

static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps) {
    browser_window *w = (browser_window *)data;
    if ((caps & WL_SEAT_CAPABILITY_POINTER) && w->pointer == NULL) {
        w->pointer = wl_seat_get_pointer(seat);
        wl_pointer_add_listener(w->pointer, &pointer_listener, w);
    }
    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && w->keyboard == NULL) {
        w->keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(w->keyboard, &keyboard_listener, w);
    }
}
static void seat_name(void *d, struct wl_seat *s, const char *name) {
    (void)d; (void)s; (void)name;
}
static const struct wl_seat_listener seat_listener = { seat_caps, seat_name };

/* --- registry --- */

static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                            const char *iface, uint32_t version) {
    (void)version;
    browser_window *w = (browser_window *)data;
    if (strcmp(iface, wl_compositor_interface.name) == 0) {
        w->compositor = wl_registry_bind(reg, name, &wl_compositor_interface, 4);
    } else if (strcmp(iface, wl_shm_interface.name) == 0) {
        w->shm = wl_registry_bind(reg, name, &wl_shm_interface, 1);
    } else if (strcmp(iface, xdg_wm_base_interface.name) == 0) {
        w->wm_base = wl_registry_bind(reg, name, &xdg_wm_base_interface, 1);
        xdg_wm_base_add_listener(w->wm_base, &wm_base_listener, w);
    } else if (strcmp(iface, wl_seat_interface.name) == 0) {
        w->seat = wl_registry_bind(reg, name, &wl_seat_interface, 1);
        wl_seat_add_listener(w->seat, &seat_listener, w);
    } else if (strcmp(iface, wl_data_device_manager_interface.name) == 0) {
        w->data_device_manager = wl_registry_bind(reg, name, &wl_data_device_manager_interface, 1);
    } else if (strcmp(iface, zxdg_decoration_manager_v1_interface.name) == 0) {
        w->deco_mgr = wl_registry_bind(reg, name, &zxdg_decoration_manager_v1_interface, 1);
    }
}
static void registry_remove(void *d, struct wl_registry *r, uint32_t name) {
    (void)d; (void)r; (void)name;
}
static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = registry_remove,
};

/* --- public API --- */

ui_status ui_run_browser(const char *start_url) {
    browser_window w;
    memset(&w, 0, sizeof w);
    w.decoder_cmd_fd = -1;
    w.decoder_out_fd = -1;
    w.width = 900;
    w.height = 700;
    w.running = 1;
    w.use_csd = 1;
    w.caps = rdp_caps_safe();   /* Privacy by Default: images/CSS/JS off */

    /* Persisted profile (Hito 10): open the encrypted profile in the writable
     * config dir and apply the remembered choices before the first paint/load.
     * Fail closed: an unreadable/foreign prefs.bin leaves the safe defaults AND
     * disables saving (never clobber); no config dir means memory-only. */
    prefs_init(&w.prefs);
    w.profile_rw = 0;
    {
        char profile_dir[PATH_MAX];
        if (freedom_write_dir(profile_dir, sizeof profile_dir) == 0 &&
            profile_open(&w.profile, profile_dir) == PROFILE_OK &&
            profile_load(&w.profile, &w.prefs) == PROFILE_OK) {
            w.profile_rw = 1;
        }
    }
    w.theme_mode  = w.prefs.theme_mode;
    w.force_theme = w.prefs.force_theme;
    w.reader      = w.prefs.reader;
    w.caps.images = w.prefs.images != 0;
    w.caps.css    = w.prefs.css != 0;
    w.zoom_pct    = zm_clamp(w.prefs.zoom_pct); /* Ctrl +/-/0 steps the ladder */
    apply_theme(&w);
    w.scroll = 0.0;
    w.focused_input = -1;       /* no form control focused */
    w.tab_count = 1;            /* the foreground tab lives in the window's own fields */
    w.active_tab = 0;
    tf_init(&w.ua_field);       /* empty => SF_DEFAULT_USER_AGENT */
    fc_init(&w.fc);             /* animation frame scheduler (Phase R1) */

    /* Key auto-repeat: a monotonic timerfd polled alongside the Wayland fd. Defaults
     * apply until the compositor sends keyboard_repeat_info. A failed create (-1) just
     * disables repeat -- one event per press, as before. */
    w.repeat_timer_fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    w.repeat_key = 0;
    w.repeat_rate = 25;         /* repeats/second */
    w.repeat_delay = 600;       /* ms before the first repeat */

    /* A clipboard paster that closes the pipe early would otherwise SIGPIPE us out of
     * data_source_send; ignore it process-wide (curl is also happier this way). A
     * fetch worker writing to a closed result pipe at shutdown benefits too. */
    signal(SIGPIPE, SIG_IGN);

    /* Async fetch: thread-safe global transport init on the main thread (before any
     * worker), and the non-blocking result pipe the loop polls. If the pipe cannot be
     * created, fetch_launch fails closed and loads report an error rather than block. */
    sf_global_init();
    w.fetch_pipe[0] = w.fetch_pipe[1] = -1;
    if (pipe(w.fetch_pipe) == 0) {
        fcntl(w.fetch_pipe[0], F_SETFL, O_NONBLOCK); /* drain without blocking the loop */
        fcntl(w.fetch_pipe[0], F_SETFD, FD_CLOEXEC);
        fcntl(w.fetch_pipe[1], F_SETFD, FD_CLOEXEC);
    }
    /* Streaming progressive render: eventfd the fetch thread signals when new
     * body data arrives; the main loop picks it up and re-renders the page. */
    pthread_mutex_init(&w.stream_lock, NULL);
    w.stream_body = NULL;
    w.stream_body_len = 0;
    w.stream_evfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    w.stream_launch_gen = 0;
    w.last_stream_render = 0;
    w.video_evfd = -1;
    w.video_thread = 0;

    if (browser_init(&w.bs) != BROWSER_OK) return UI_ERR_OOM;

    if (start_url != NULL) {
        /* Strip userinfo (user:password@) before storing in history so
         * credentials never leak into the URL bar or the history list. */
        char clean_url[SF_MAX_URL];
        if (url_extract_userinfo(start_url, clean_url, sizeof clean_url,
                                 NULL, NULL) == URL_OK)
            browser_navigate(&w.bs, clean_url);
        else
            browser_navigate(&w.bs, start_url);
    }

    w.xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (w.xkb_ctx == NULL) { browser_free(&w.bs); return UI_ERR_OOM; }

    w.display = wl_display_connect(NULL);
    if (w.display == NULL) { browser_free(&w.bs); xkb_context_unref(w.xkb_ctx); return UI_ERR_DISPLAY; }

    /* Raise the Wayland output buffer from the default (4096 on this version)
     * so a large page with frequent redraws (spinner, JS ticks, video frames)
     * never hits "Data too big for buffer". A 4 KiB buffer overflows when
     * accumulated messages exceed that, since manual flushes don't always drain
     * before the next redraw queues more. 1 MiB is generous for any page. */
    wl_display_set_max_buffer_size(w.display, 1024u * 1024u);

    w.registry = wl_display_get_registry(w.display);
    wl_registry_add_listener(w.registry, &registry_listener, &w);
    wl_display_roundtrip(w.display);

    if (w.compositor == NULL || w.shm == NULL || w.wm_base == NULL) {
        wl_display_disconnect(w.display);
        browser_free(&w.bs);
        xkb_context_unref(w.xkb_ctx);
        return UI_ERR_INTERNAL;
    }

    /* Clipboard wiring (optional: a compositor without wl_data_device_manager simply
     * has no copy/paste). The seat and the manager are both bound by the roundtrip. */
    if (w.data_device_manager != NULL && w.seat != NULL) {
        w.data_device = wl_data_device_manager_get_data_device(w.data_device_manager, w.seat);
        wl_data_device_add_listener(w.data_device, &data_device_listener, &w);
    }

    w.surface = wl_compositor_create_surface(w.compositor);
    w.xdg_surface = xdg_wm_base_get_xdg_surface(w.wm_base, w.surface);
    xdg_surface_add_listener(w.xdg_surface, &xdg_surface_listener, &w);
    w.xdg_toplevel = xdg_surface_get_toplevel(w.xdg_surface);
    xdg_toplevel_add_listener(w.xdg_toplevel, &toplevel_listener, &w);
    xdg_toplevel_set_title(w.xdg_toplevel, "Freedom");
    xdg_toplevel_set_app_id(w.xdg_toplevel, "org.freedom.browser");

    w.use_csd = 1;
    if (w.deco_mgr != NULL) {
        w.deco = zxdg_decoration_manager_v1_get_toplevel_decoration(w.deco_mgr, w.xdg_toplevel);
        zxdg_toplevel_decoration_v1_add_listener(w.deco, &deco_listener, &w);
        zxdg_toplevel_decoration_v1_set_mode(w.deco,
            ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE);
    }

    /* Themed cursors: a hand over links, the default arrow elsewhere. Best-effort
     * from the system theme (no absolute paths); if unavailable the compositor's
     * own default cursor is used. */
    w.cursor_theme = wl_cursor_theme_load(NULL, UI_CURSOR_SIZE, w.shm);
    if (w.cursor_theme != NULL) {
        w.cursor_default = wl_cursor_theme_get_cursor(w.cursor_theme, "left_ptr");
        w.cursor_hand = wl_cursor_theme_get_cursor(w.cursor_theme, "pointer");
        if (w.cursor_hand == NULL) w.cursor_hand = wl_cursor_theme_get_cursor(w.cursor_theme, "hand2");
        if (w.cursor_hand == NULL) w.cursor_hand = wl_cursor_theme_get_cursor(w.cursor_theme, "hand1");
    }
    w.cursor_surface = wl_compositor_create_surface(w.compositor);

    wl_surface_commit(w.surface);

    /* Host filter (blocklist + allowlist) ready before the first fetch. Placed after
     * the fallible Wayland setup so its error returns above never leak it. */
    w.hosts = build_host_filter();
    w.js_hosts = build_js_filter();        /* per-host JS allowlist (js.conf) */
    w.impersonate_hosts = build_impersonate_filter(); /* per-host TLS blend (impersonate.conf) */
    w.omni_sel = -1;
    load_favorites(&w);                    /* omnibox autocomplete from allow.conf */
    /* JS policy: an explicit FREEDOM_JS env wins for this session; otherwise the
     * persisted choice applies (prefs_parse already clamped it to a valid mode). */
    const char *js_env = getenv("FREEDOM_JS");
    w.js_mode = (js_env != NULL && js_env[0] != '\0') ? jsp_mode_from_str(js_env)
                                                      : (jsp_mode)w.prefs.js_mode;
    init_net_config(&w);  /* Tor/I2P routing config from the environment (opt-in) */
    /* Remembered routing choices apply where the environment did not opt in
     * (the env stays a per-session override; both are explicit user opt-ins). */
    if (w.prefs.tor && !w.net_cfg.tor_enabled) w.net_cfg.tor_enabled = 1;
    if (w.prefs.i2p && !w.net_cfg.i2p_enabled) w.net_cfg.i2p_enabled = 1;
    if (w.prefs.torify && w.net_cfg.tor_enabled) w.net_cfg.torify_clearnet = 1;

    /* Optionally start in distraction-free (reader) mode: set FREEDOM_READER to any
     * value (like a startup affordance for the Ctrl+D toggle). Set before the first
     * load so the worker drops boilerplate and the paint centers the reading column. */
    if (getenv("FREEDOM_READER") != NULL) w.reader = 1;

    /* Optionally start with images enabled: set FREEDOM_IMAGES to any value (a
     * startup affordance for the Ctrl+I toggle, for agent-verifiable sessions --
     * images remain opt-in by default, Privacy by Default). */
    if (getenv("FREEDOM_IMAGES") != NULL) w.caps.images = true;

    /* Initial page. Provide instructions because the strict TLS policy means
       many public sites will be rejected. */
    if (start_url != NULL) {
        do_load(&w, start_url);
    } else {
        do_load(&w, "docs/index.html");
    }

    /* Make the URL bar ready for typing. */
    w.url_bar_focused = 1;
    browser_url_bar_clear(&w.bs);

    /* Optionally open the Freebug console on launch (like a browser's
     * auto-open-devtools): set FREEDOM_FREEBUG to any value. F12 / the hamburger
     * toggle it at any time. */
    if (getenv("FREEDOM_FREEBUG") != NULL) freebug_show(&w);

    /* Event loop using the prepare_read/read_events pattern so a poll timeout can
     * fire the toast's auto-hide without racing the Wayland queue. The timeout is
     * the remaining lifetime of an active toast, or infinite when there is none. */
    while (w.running) {
        while (wl_display_prepare_read(w.display) != 0) {
            wl_display_dispatch_pending(w.display);
        }
        wl_display_flush(w.display);

        uint64_t t = now_ms();
        int timeout = -1;
        if (browser_status_text(&w.bs, t) != NULL) {
            uint64_t exp = w.bs.status_expiry_ms;
            timeout = (exp > t) ? (int)(exp - t) : 0;
        }
        /* While a fetch is in flight, wake ~12 fps to animate the spinner. */
        if (w.loading && (timeout < 0 || timeout > 80)) timeout = 80;
        /* A pending JS timer tick bounds the wait too (real async timers). */
        if (w.js_tick_due_ms != 0) {
            int tk = (w.js_tick_due_ms > t) ? (int)(w.js_tick_due_ms - t) : 0;
            if (timeout < 0 || tk < timeout) timeout = tk;
        }
        /* While video is playing, wake at ~30 fps to check for new frames. */
        if (w.video_active && w.decoder_out_fd >= 0
            && (timeout < 0 || timeout > 33)) timeout = 33;

        /* Poll the Wayland fd, the key-repeat timer, the async-fetch result pipe,
         * and the video decoder + feeder-thread eventfds together. */
        struct pollfd pfds[6];
        int nfds = 0;
        pfds[nfds].fd = wl_display_get_fd(w.display); pfds[nfds].events = POLLIN; pfds[nfds].revents = 0; nfds++;
        int timer_idx = -1, fetch_idx = -1, stream_idx = -1,
            video_idx = -1, video_ev_idx = -1;
        if (w.repeat_timer_fd >= 0) {
            pfds[nfds].fd = w.repeat_timer_fd; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            timer_idx = nfds++;
        }
        if (w.fetch_pipe[0] >= 0) {
            pfds[nfds].fd = w.fetch_pipe[0]; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            fetch_idx = nfds++;
        }
        if (w.stream_evfd >= 0) {
            pfds[nfds].fd = w.stream_evfd; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            stream_idx = nfds++;
        }
        if (w.decoder_out_fd >= 0 && w.video_active) {
            pfds[nfds].fd = w.decoder_out_fd; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            video_idx = nfds++;
        }
        if (w.video_evfd >= 0 && w.video_active) {
            pfds[nfds].fd = w.video_evfd; pfds[nfds].events = POLLIN; pfds[nfds].revents = 0;
            video_ev_idx = nfds++;
        }
        int pr = poll(pfds, (nfds_t)nfds, timeout);

        if (pr > 0 && (pfds[0].revents & POLLIN)) {
            if (wl_display_read_events(w.display) == -1) break;
            if (wl_display_dispatch_pending(w.display) == -1) break;
        } else {
            wl_display_cancel_read(w.display);
            if (pr < 0) { if (errno != EINTR) break; }       /* a real poll error */
            else if (pr == 0) redraw(&w);                    /* toast/spinner tick: repaint */
            else if (pfds[0].revents & (POLLHUP | POLLERR)) break; /* the display is gone */
        }

        /* A held key fired: re-apply it (read drains the expiration count so the timer
         * re-arms cleanly). Only acts while a repeat key is set. */
        if (pr > 0 && timer_idx >= 0 && (pfds[timer_idx].revents & POLLIN)) {
            uint64_t expirations;
            if (read(w.repeat_timer_fd, &expirations, sizeof expirations) > 0)
                key_repeat_fire(&w);
        }

        /* One or more fetches completed: render them on this (main) thread. */
        if (pr > 0 && fetch_idx >= 0 && (pfds[fetch_idx].revents & POLLIN))
            drain_fetch_results(&w);

        /* A JS timer came due: advance the worker's virtual clock (OP_TICK), apply
         * the refreshed view and schedule the next tick from its report. Bounded
         * per load by js_ticks_left; skipped while a page load is in flight. */
        if (w.js_tick_due_ms != 0 && now_ms() >= w.js_tick_due_ms &&
            !w.loading && w.tab_worker != NULL) {
            w.js_tick_due_ms = 0;
            if (w.js_ticks_left > 0) {
                w.js_ticks_left--;
                tab_page tp;
                memset(&tp, 0, sizeof tp);
                if (tab_tick(w.tab_worker, w.js_tick_elapsed, &tp) == TAB_OK) {
                    apply_click_result(&w, &tp);
                    tab_page_free(&tp);
                    redraw(&w);
                }
            }
        }

        /* Streaming fetch: new body data arrived. Drain the eventfd counter,
         * copy the accumulated page to cur_html, and re-render progressively.
         * Guarded: only when configured, loading, and rate-limited to ~4 fps
         * (250ms min interval) to avoid overwhelming the tab worker + fork. */
        if (pr > 0 && stream_idx >= 0 && (pfds[stream_idx].revents & POLLIN)) {
            uint64_t cnt = 0;
            ssize_t rd = read(w.stream_evfd, &cnt, sizeof cnt); /* drain counter */
            (void)rd;
            uint64_t now = now_ms();
            if (w.configured && w.loading &&
                now - w.last_stream_render >= 250) {
                pthread_mutex_lock(&w.stream_lock);
                if (w.stream_body != NULL && w.stream_body_len > 0) {
                    free(w.cur_html);
                    w.cur_html = w.stream_body;
                    w.cur_html_len = w.stream_body_len;
                    w.stream_body = NULL;
                    w.stream_body_len = 0;
                }
                pthread_mutex_unlock(&w.stream_lock);
                if (w.cur_html != NULL && w.cur_html_len > 0) {
                    render_current(&w);
                    w.last_stream_render = now;
                }
            }
        }

        /* A decoded video frame arrived from the media decoder process, or the
         * feeder thread signalled that it sent one or more new TS segments.
         * Drain the eventfd counter, read all available frames, and repaint. */
        if (pr > 0 && video_ev_idx >= 0 && (pfds[video_ev_idx].revents & POLLIN)) {
            uint64_t cnt = 0;
            ssize_t rd = read(w.video_evfd, &cnt, sizeof cnt);
            (void)rd;
        }
        if (pr > 0 && video_idx >= 0 && (pfds[video_idx].revents & POLLIN)) {
            while (video_read_frame(&w) > 0) {}
        }
        /* After both fd events are handled (either can fire independently),
         * redraw if we have a frame. Also drain any frames that arrived via the
         * eventfd without a simultaneous pipe event. */
        if (w.video_active && w.decoder_out_fd >= 0) {
            while (video_read_frame(&w) > 0) {}
        }
        if (w.video_frame != NULL)
            redraw(&w);
    }

    video_stop(&w);    /* stop the video decoder if running */
    profile_sync(&w);  /* final state (zoom/toggles) sealed before teardown */

    destroy_buffer(&w);
    freebug_destroy(&w);                       /* tear down the console window if open */
    if (w.tab_worker) tab_close(w.tab_worker); /* the kept-alive REPL worker */
    fb_buffer_free(&w.console);                /* captured console transcript */
    if (w.copy_source) wl_data_source_destroy(w.copy_source);
    free(w.copy_text);
    if (w.selection_offer) wl_data_offer_destroy(w.selection_offer);
    if (w.data_device) wl_data_device_destroy(w.data_device);
    if (w.data_device_manager) wl_data_device_manager_destroy(w.data_device_manager);
    if (w.deco) zxdg_toplevel_decoration_v1_destroy(w.deco);
    if (w.deco_mgr) zxdg_decoration_manager_v1_destroy(w.deco_mgr);
    if (w.xdg_toplevel) xdg_toplevel_destroy(w.xdg_toplevel);
    if (w.xdg_surface) xdg_surface_destroy(w.xdg_surface);
    if (w.surface) wl_surface_destroy(w.surface);
    if (w.keyboard) wl_keyboard_destroy(w.keyboard);
    if (w.pointer) wl_pointer_destroy(w.pointer);
    if (w.seat) wl_seat_destroy(w.seat);
    if (w.cursor_surface) wl_surface_destroy(w.cursor_surface);
    if (w.cursor_theme) wl_cursor_theme_destroy(w.cursor_theme);
    if (w.wm_base) xdg_wm_base_destroy(w.wm_base);
    if (w.shm) wl_shm_destroy(w.shm);
    if (w.compositor) wl_compositor_destroy(w.compositor);
    if (w.registry) wl_registry_destroy(w.registry);
    wl_display_disconnect(w.display);

    if (w.repeat_timer_fd >= 0) close(w.repeat_timer_fd);
    /* Close the result pipe. Any still-running detached fetch worker that posts after
     * this gets a write error (SIGPIPE ignored) and frees its own job; the process is
     * exiting, so the OS reclaims the rest. */
    if (w.fetch_pipe[0] >= 0) close(w.fetch_pipe[0]);
    if (w.fetch_pipe[1] >= 0) close(w.fetch_pipe[1]);
    if (w.stream_evfd >= 0) close(w.stream_evfd);
    pthread_mutex_lock(&w.stream_lock);
    free(w.stream_body);
    w.stream_body = NULL;
    pthread_mutex_unlock(&w.stream_lock);
    pthread_mutex_destroy(&w.stream_lock);
    if (w.xkb_keymap) xkb_keymap_unref(w.xkb_keymap);
    if (w.xkb_state) xkb_state_unref(w.xkb_state);
    xkb_context_unref(w.xkb_ctx);

    /* Release background tabs (parked in slots); the foreground tab is freed via the
     * live fields just below. */
    for (int i = 0; i < w.tab_count; ++i) {
        if (i != w.active_tab) tab_ctx_release(&w.tab_slots[i]);
    }

    clear_doc(&w);
    hb_free(w.hosts);
    hb_free(w.js_hosts);
    hb_free(w.impersonate_hosts);
    free(w.favorites);
    free(w.cur_html);
    free(w.cur_top);
    free(w.auth_user);
    free(w.auth_pass);
    browser_free(&w.bs);
    prefs_free(&w.prefs);
    profile_close(&w.profile);

    /* Release the process-wide font caches so a leak checker sees a clean exit.
     * tsh_shutdown drops the HarfBuzz shaper's cached FT/cairo faces first, then
     * cairo's static font cache (which holds FcPattern references), then let
     * fontconfig free its global config. All other cairo objects have already
     * been destroyed above, so this ordering is safe. */
    tsh_shutdown();
    cairo_debug_reset_static_data();
    FcFini();
    return UI_OK;
}
