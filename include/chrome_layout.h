#ifndef FREEDOM_CHROME_LAYOUT_H
#define FREEDOM_CHROME_LAYOUT_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * chrome_layout (chl_) -- the browser chrome's geometry and the connection
 * identity badge. Pure: no I/O, no Cairo, no window state. The single source of
 * truth shared by the GUI painter and every pointer hit-test, so what is drawn and
 * what is clicked cannot drift. Contract: spec/chrome_layout.md.
 */

#include <stddef.h>

#define CHL_TABBAR_H        38.0  /* row 1: tabs (+ window buttons under CSD) */
#define CHL_TOOLBAR_H       42.0  /* row 2: navigation buttons, URL pill, menu */
#define CHL_PAD             8.0   /* outer horizontal padding of both rows */
#define CHL_TAB_TOP_GAP     5.0   /* space above a tab inside row 1 */
#define CHL_TAB_MIN_W       76.0
#define CHL_TAB_MAX_W       240.0
#define CHL_TAB_GAP         2.0   /* space between two tabs */
#define CHL_TAB_CLOSE       20.0  /* square close button inside a tab */
#define CHL_TAB_CLOSE_MIN_W 110.0 /* narrower inactive tabs hide their close button */
#define CHL_NEWTAB_W        30.0
#define CHL_WIN_BTN_W       46.0
#define CHL_DRAG_MIN        48.0  /* CSD: drag area always kept free in row 1 */
#define CHL_BTN             32.0  /* round toolbar button diameter */
#define CHL_BTN_GAP         2.0
#define CHL_URL_H           32.0
#define CHL_ID_W            30.0  /* identity badge slot at the pill's left */
#define CHL_STAR_W          30.0  /* bookmark star slot at the pill's right */
#define CHL_STAR_MIN_URL    160.0 /* narrower pills keep their width for the URL text */
#define CHL_MORE_W          26.0  /* hidden-tabs indicator at each end of an overflowing strip */
#define CHL_DRAG_THRESHOLD  6.0   /* px a pressed tab must travel before it is dragged */

typedef enum chl_status { CHL_OK = 0, CHL_EINVAL = -1 } chl_status;

typedef struct chl_rect { double x, y, w, h; } chl_rect;

typedef enum chl_part {
    CHL_PART_NONE = 0,
    CHL_PART_TAB,
    CHL_PART_TAB_CLOSE,
    CHL_PART_TABS_LEFT,  /* indicator: tabs hidden before the strip */
    CHL_PART_TABS_RIGHT, /* indicator: tabs hidden after the strip */
    CHL_PART_NEW_TAB,
    CHL_PART_DRAG,
    CHL_PART_WIN_MIN,
    CHL_PART_WIN_MAX,
    CHL_PART_WIN_CLOSE,
    CHL_PART_BACK,
    CHL_PART_FWD,
    CHL_PART_RELOAD,
    CHL_PART_IDENTITY,
    CHL_PART_URL,
    CHL_PART_MENU,
    CHL_PART_CONTENT,
    CHL_PART_STAR        /* bookmark star inside the pill (zero-sized when it does not fit) */
} chl_part;

typedef struct chl_layout {
    double   width;
    int      csd;
    int      tab_count;
    int      active;
    double   tabbar_top, toolbar_top, content_top;
    double   tab_x0;       /* x of the first tab */
    double   tab_w;        /* width of every tab */
    int      tabs_visible; /* tabs that fit before the new-tab button */
    int      tab_first;    /* first visible tab: the strip scrolls to keep `active` visible */
    int      hidden_left;  /* tabs before tab_first */
    int      hidden_right; /* tabs after the last visible one */
    chl_rect more_left, more_right; /* indicators; zero-sized when every tab fits */
    chl_rect new_tab;
    chl_rect win_min, win_max, win_close; /* zero-sized under SSD */
    chl_rect back, fwd, reload, url, identity, menu;
    chl_rect star;         /* bookmark toggle at the pill's right; zero-sized if too narrow */
} chl_layout;

/* Computes the layout. tab_count >= 1 and 0 <= active < tab_count, else CHL_EINVAL
 * (out untouched). A non-finite or < 1 width is treated as 1. */
chl_status chl_compute(double width, int csd, int tab_count, int active, chl_layout *out);

/* Tab i's rectangle / its close button. 1 if it exists (visible), else 0. */
int chl_tab_rect(const chl_layout *l, int i, chl_rect *r);
int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r);

/* 1 if (x, y) lies inside r (half-open on the right and bottom). */
int chl_rect_has(chl_rect r, double x, double y);

/* The chrome part under (x, y); *tab gets the tab index for TAB/TAB_CLOSE, else -1.
 * tab may be NULL. */
chl_part chl_hit(const chl_layout *l, double x, double y, int *tab);

/* Absolute index of the visible tab slot under x (clamped to the visible tabs): where a
 * dragged tab dropped at x lands. -1 if l is NULL or no tab is visible. */
int chl_tab_drop_index(const chl_layout *l, double x);

/* Where element i ends up after the element at `from` moves to `to` (the others shift to
 * close the gap and open the slot). The single remapping for every index the GUI keeps. */
int chl_move_index(int i, int from, int to);

/* Ctrl+<digit>: 1..8 select that tab, 9 the last one (Firefox). -1 when there is none. */
int chl_tab_for_digit(int digit, int tab_count);

/* A tab label for a page without <title> (Firefox): a file's name for file: URLs and
 * local paths, otherwise the URL without its "scheme://". Writes "" for NULL/empty.
 * Truncates on a UTF-8 boundary; out is always NUL-terminated when cap > 0. */
void chl_tab_fallback_title(const char *url, char *out, size_t cap);

/* --- find bar (spec/find_text.md), docked at the bottom of the window --- */

#define CHL_FIND_H        40.0  /* bar height */
#define CHL_FIND_FIELD_W  320.0 /* preferred field width */
#define CHL_FIND_FIELD_H  28.0
#define CHL_FIND_BTN      28.0  /* prev / next / close square buttons */
#define CHL_FIND_COUNT_W  170.0 /* "999 of 1000 matches" */

typedef enum chl_find_part {
    CHL_FIND_NONE = 0,  /* outside the bar */
    CHL_FIND_BAR,       /* inside the bar, on no control */
    CHL_FIND_FIELD,
    CHL_FIND_PREV,
    CHL_FIND_NEXT,
    CHL_FIND_CLOSE
} chl_find_part;

typedef struct chl_findbar {
    chl_rect bar, field, prev, next, count, close;
} chl_findbar;

/* The bar for a window of (width, height). Non-finite or < 1 sizes are treated as 1;
 * controls never overlap one another and never leave the bar. out == NULL: CHL_EINVAL. */
chl_status chl_findbar_compute(double width, double height, chl_findbar *out);

/* The find-bar part under (x, y). */
chl_find_part chl_findbar_hit(const chl_findbar *f, double x, double y);

/* --- connection identity badge --- */

typedef enum chl_identity {
    CHL_ID_UNKNOWN = 0, /* no claim: transport not known (fail-closed default) */
    CHL_ID_INTERNAL,    /* about: pages, start page */
    CHL_ID_LOCAL,       /* file: */
    CHL_ID_PQ,          /* https, TLS 1.3 + hybrid post-quantum key exchange */
    CHL_ID_CLASSICAL,   /* https, TLS 1.3 classical key exchange */
    CHL_ID_WEAK,        /* https under the per-host allowlist override */
    CHL_ID_OVERLAY,     /* Tor .onion / I2P .i2p */
    CHL_ID_UNVERIFIED,  /* operator --insecure: certificate not verified */
    CHL_ID_INSECURE     /* plaintext http outside an overlay */
} chl_identity;

/* Matches secure_fetch's downgrade levels (SF_DOWNGRADE_*). */
enum { CHL_DG_NONE = 0, CHL_DG_CLASSICAL_KE = 1, CHL_DG_ALLOWLISTED = 2 };

chl_identity chl_identity_of(const char *url, int transport_known, int downgrade,
                             int operator_insecure);

/* Short English label for the badge (static, never NULL). */
const char *chl_identity_label(chl_identity id);

#endif /* FREEDOM_CHROME_LAYOUT_H */
