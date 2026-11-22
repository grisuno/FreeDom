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

typedef enum chl_status { CHL_OK = 0, CHL_EINVAL = -1 } chl_status;

typedef struct chl_rect { double x, y, w, h; } chl_rect;

typedef enum chl_part {
    CHL_PART_NONE = 0,
    CHL_PART_TAB,
    CHL_PART_TAB_CLOSE,
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
    CHL_PART_CONTENT
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
    chl_rect new_tab;
    chl_rect win_min, win_max, win_close; /* zero-sized under SSD */
    chl_rect back, fwd, reload, url, identity, menu;
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
