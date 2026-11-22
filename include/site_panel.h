#ifndef FREEDOM_SITE_PANEL_H
#define FREEDOM_SITE_PANEL_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * site_panel (sp_) -- the site identity panel opened from the connection badge: how the
 * page on screen arrived (TLS, key exchange, certificate, route) and what the site may do
 * (third parties, JavaScript, cookies), with the user's two sovereignty actions. Pure: no
 * I/O, no Cairo, no window state. Contract: spec/site_panel.md.
 */

#include "chrome_layout.h"

#define SP_HOST_MAX   48   /* title characters kept before "..." */
#define SP_VALUE_MAX  64   /* bytes of a row value, NUL included */
#define SP_MAX_ROWS   8
#define SP_MAX_ACTIONS 2

#define SP_WIDTH      460.0
#define SP_MARGIN     8.0
#define SP_PAD        16.0
#define SP_HEADER_H   64.0   /* title + headline */
#define SP_ROW_H      24.0
#define SP_ACTION_H   32.0
#define SP_ACTION_GAP 8.0
#define SP_GAP        6.0    /* between the anchor and the panel */

typedef enum sp_status { SP_OK = 0, SP_EINVAL = -1 } sp_status;

typedef enum sp_tone { SP_TONE_NEUTRAL = 0, SP_TONE_GOOD, SP_TONE_WARN, SP_TONE_BAD } sp_tone;

typedef enum sp_route { SP_ROUTE_DIRECT = 0, SP_ROUTE_TOR, SP_ROUTE_I2P } sp_route;

typedef enum sp_action { SP_ACT_NONE = 0, SP_ACT_ALLOW, SP_ACT_JS } sp_action;

typedef struct sp_facts {
    const char  *url;          /* hostile; may be NULL */
    chl_identity identity;
    const char  *tls_version;  /* may be NULL */
    const char  *group;        /* negotiated KE group; may be NULL */
    sp_route     route;
    int          allowlisted;  /* host in allow.conf */
    int          js_site;      /* JavaScript on for this host */
    int          trusted;      /* allow AND js: full capabilities */
    int          listable;     /* the host is one hostedit accepts into a .conf list */
} sp_facts;

typedef struct sp_row {
    const char *label;               /* static */
    char        value[SP_VALUE_MAX]; /* sanitized, printable ASCII */
    sp_tone     tone;
} sp_row;

typedef struct sp_panel {
    char        title[SP_HOST_MAX + 4];
    const char *headline;            /* static, never NULL */
    sp_tone     tone;
    sp_row      rows[SP_MAX_ROWS];
    int         row_count;
    sp_action   actions[SP_MAX_ACTIONS];
    int         action_count;
} sp_panel;

typedef struct sp_geom {
    chl_rect panel;
    chl_rect action[SP_MAX_ACTIONS];
    int      action_count;
} sp_geom;

enum { SP_HIT_OUTSIDE = -2, SP_HIT_PANEL = -1, SP_HIT_ACTION0 = 0 };

/* Builds the panel content from the facts. NULL f/out: SP_EINVAL (out untouched). */
sp_status sp_build(const sp_facts *f, sp_panel *out);

/* Label of an action button (static, never NULL). */
const char *sp_action_label(sp_action a);

/* Places the panel under `anchor`, kept inside a win_w x win_h window. */
sp_status sp_layout(const sp_panel *p, chl_rect anchor, double win_w, double win_h, sp_geom *g);

/* SP_HIT_OUTSIDE, SP_HIT_PANEL, or SP_HIT_ACTION0 + i for action i. */
int sp_hit(const sp_geom *g, double x, double y);

#endif /* FREEDOM_SITE_PANEL_H */
