/* site_panel -- site identity panel content + geometry. spec/site_panel.md */
#include "site_panel.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

/* Largest size the layout honours; anything above is clamped so every sum stays finite. */
#define SP_SIZE_MAX 1.0e7

static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; }

static int has_prefix_ci(const char *s, const char *prefix) {
    for (; *prefix != '\0'; ++s, ++prefix)
        if (*s == '\0' || lower((unsigned char)*s) != lower((unsigned char)*prefix)) return 0;
    return 1;
}

/* Copies at most `max` bytes of s[0..n) into dst as printable ASCII ('?' for anything
 * else), appending "..." when cut. dst holds max + 4 bytes. */
static void sanitize(char *dst, size_t max, const char *s, size_t n) {
    size_t k = (n > max) ? max : n;
    for (size_t i = 0; i < k; ++i) {
        unsigned char c = (unsigned char)s[i];
        dst[i] = (c >= 0x20 && c < 0x7f) ? (char)c : '?';
    }
    if (n > max) { memcpy(dst + k, "...", 3); k += 3; }
    dst[k] = '\0';
}

/* Host of a network URL (after "scheme://", userinfo and port removed); 0 when none. */
static size_t url_host(const char *url, const char **out) {
    const char *sep = strstr(url, "://");
    if (sep == NULL) return 0;
    const char *rest = sep + 3;
    size_t end = strcspn(rest, "/?#");
    const char *h = rest;
    for (size_t i = 0; i < end; ++i)
        if (rest[i] == '@') h = rest + i + 1;
    size_t n = end - (size_t)(h - rest);
    if (n > 0 && h[0] == '[') {
        const char *rb = memchr(h, ']', n);
        n = (rb != NULL) ? (size_t)(rb - h) + 1 : n;
    } else {
        const char *colon = memchr(h, ':', n);
        if (colon != NULL) n = (size_t)(colon - h);
    }
    *out = h;
    return n;
}

static int is_network(chl_identity id) {
    switch (id) {
        case CHL_ID_PQ: case CHL_ID_CLASSICAL: case CHL_ID_WEAK: case CHL_ID_OVERLAY:
        case CHL_ID_UNVERIFIED: case CHL_ID_INSECURE: case CHL_ID_UNKNOWN:
            return 1;
        default:
            return 0;
    }
}

static sp_tone tone_of(chl_identity id) {
    switch (id) {
        case CHL_ID_PQ:         return SP_TONE_GOOD;
        case CHL_ID_UNVERIFIED:
        case CHL_ID_INSECURE:   return SP_TONE_BAD;
        case CHL_ID_CLASSICAL:
        case CHL_ID_WEAK:
        case CHL_ID_UNKNOWN:    return SP_TONE_WARN;
        default:                return SP_TONE_NEUTRAL;
    }
}

static sp_row *add_row(sp_panel *p, const char *label, sp_tone tone) {
    if (p->row_count >= SP_MAX_ROWS) return NULL;
    sp_row *r = &p->rows[p->row_count++];
    r->label = label;
    r->value[0] = '\0';
    r->tone = tone;
    return r;
}

static void row_text(sp_panel *p, const char *label, sp_tone tone, const char *text) {
    sp_row *r = add_row(p, label, tone);
    if (r != NULL) sanitize(r->value, SP_VALUE_MAX - 4, text, strlen(text));
}

/* "<tls> / <group>" with each part sanitized and bounded. */
static void connection_value(char *dst, const char *tls, const char *group) {
    char a[24], b[32];
    sanitize(a, sizeof a - 4, tls != NULL ? tls : "TLS", strlen(tls != NULL ? tls : "TLS"));
    sanitize(b, sizeof b - 4, group != NULL ? group : "unknown group",
             strlen(group != NULL ? group : "unknown group"));
    int r = snprintf(dst, SP_VALUE_MAX, "%s / %s", a, b);
    if (r < 0) dst[0] = '\0';
}

static int names_mlkem(const char *g) {
    if (g == NULL) return 0;
    for (; *g != '\0'; ++g)
        if (has_prefix_ci(g, "mlkem")) return 1;
    return 0;
}

sp_status sp_build(const sp_facts *f, sp_panel *out) {
    if (f == NULL || out == NULL) return SP_EINVAL;
    sp_panel p;
    memset(&p, 0, sizeof p);
    chl_identity id = f->identity;
    p.headline = chl_identity_label(id);
    p.tone = tone_of(id);
    int net = is_network(id);

    const char *host = NULL;
    size_t hn = (f->url != NULL && net) ? url_host(f->url, &host) : 0;
    if (hn > 0)                     sanitize(p.title, SP_HOST_MAX, host, hn);
    else if (id == CHL_ID_LOCAL)    strcpy(p.title, "Local file");
    else if (net)                   strcpy(p.title, "Unknown site");
    else                            strcpy(p.title, "Freedom");

    int tls = (id == CHL_ID_PQ || id == CHL_ID_CLASSICAL || id == CHL_ID_WEAK
               || id == CHL_ID_UNVERIFIED
               || (id == CHL_ID_OVERLAY && f->url != NULL && has_prefix_ci(f->url, "https://")));

    /* 1. Connection */
    if (!net) {
        row_text(&p, "Connection", SP_TONE_NEUTRAL, "No network");
    } else if (id == CHL_ID_INSECURE) {
        row_text(&p, "Connection", SP_TONE_BAD, "Not encrypted");
    } else if (id == CHL_ID_UNKNOWN) {
        row_text(&p, "Connection", SP_TONE_WARN, "Unknown: not delivered by a checked fetch");
    } else if (id == CHL_ID_OVERLAY && !tls) {
        row_text(&p, "Connection", SP_TONE_NEUTRAL, "Encrypted by the I2P overlay");
    } else {
        sp_row *r = add_row(&p, "Connection", tone_of(id));
        if (r != NULL) connection_value(r->value, f->tls_version, f->group);
    }
    /* 2. Key exchange: the hybrid claim needs BOTH the PQ identity and an ML-KEM group. */
    if (tls) {
        if (id == CHL_ID_PQ && names_mlkem(f->group))
            row_text(&p, "Key exchange", SP_TONE_GOOD, "Hybrid post-quantum (ML-KEM + classical)");
        else if (id == CHL_ID_CLASSICAL || id == CHL_ID_WEAK || id == CHL_ID_PQ)
            row_text(&p, "Key exchange", SP_TONE_WARN, "Classical: not quantum-resistant");
    }
    /* 3. Certificate */
    if (tls) {
        if (id == CHL_ID_UNVERIFIED)
            row_text(&p, "Certificate", SP_TONE_BAD, "NOT verified (--insecure)");
        else if (id == CHL_ID_WEAK)
            row_text(&p, "Certificate", SP_TONE_WARN, "Verified; weak crypto allowed by allow.conf");
        else
            row_text(&p, "Certificate", SP_TONE_GOOD, "Verified");
    }
    /* 4..7: route and permissions of a network site. */
    if (net) {
        row_text(&p, "Route", SP_TONE_NEUTRAL,
                 f->route == SP_ROUTE_TOR ? "Tor (SOCKS5h, remote DNS)"
               : f->route == SP_ROUTE_I2P ? "I2P" : "Direct");
        row_text(&p, "Third parties", SP_TONE_NEUTRAL,
                 f->trusted ? "Allowed (site trusted)" : "Blocked");
        row_text(&p, "JavaScript", SP_TONE_NEUTRAL, f->js_site ? "On for this site" : "Off");
        row_text(&p, "Cookies", SP_TONE_NEUTRAL,
                 f->trusted ? "Session only, in memory" : "None");
        if (hn > 0 && f->listable) {
            if (!f->allowlisted) p.actions[p.action_count++] = SP_ACT_ALLOW;
            if (!f->js_site)     p.actions[p.action_count++] = SP_ACT_JS;
        }
    }
    *out = p;
    return SP_OK;
}

const char *sp_action_label(sp_action a) {
    switch (a) {
        case SP_ACT_ALLOW: return "Trust this site (allow.conf)";
        case SP_ACT_JS:    return "Enable JavaScript (js.conf)";
        case SP_ACT_NONE:
        default:           return "";
    }
}

static double clampd(double v, double lo, double hi) {
    if (!isfinite(v) || v < lo) return lo;
    return (v > hi) ? hi : v;
}

static chl_rect rect(double x, double y, double w, double h) {
    chl_rect r = { x, y, (w > 0.0) ? w : 0.0, (h > 0.0) ? h : 0.0 };
    return r;
}

sp_status sp_layout(const sp_panel *p, chl_rect anchor, double win_w, double win_h, sp_geom *g) {
    if (p == NULL || g == NULL) return SP_EINVAL;
    win_w = clampd(win_w, 1.0, SP_SIZE_MAX);
    win_h = clampd(win_h, 1.0, SP_SIZE_MAX);
    double ax = clampd(anchor.x, 0.0, win_w);
    double ay = clampd(anchor.y, 0.0, win_h) + clampd(anchor.h, 0.0, win_h);
    int nact = (p->action_count < 0) ? 0
             : (p->action_count > SP_MAX_ACTIONS) ? SP_MAX_ACTIONS : p->action_count;
    int nrow = (p->row_count < 0) ? 0 : (p->row_count > SP_MAX_ROWS) ? SP_MAX_ROWS : p->row_count;

    double w = SP_WIDTH;
    if (w > win_w - 2.0 * SP_MARGIN) w = win_w - 2.0 * SP_MARGIN;
    if (w < 0.0) w = 0.0;
    double h = SP_HEADER_H + (double)nrow * SP_ROW_H + SP_PAD
             + (double)nact * (SP_ACTION_H + SP_ACTION_GAP) + (nact > 0 ? SP_PAD - SP_ACTION_GAP : 0.0);
    double x = ax;
    if (x + w > win_w - SP_MARGIN) x = win_w - SP_MARGIN - w;
    if (x < SP_MARGIN) x = (win_w > 2.0 * SP_MARGIN) ? SP_MARGIN : 0.0;
    double y = ay + SP_GAP;
    if (y + h > win_h - SP_MARGIN) h = win_h - SP_MARGIN - y; /* a short window cuts it */
    if (h < 0.0) h = 0.0;

    sp_geom out;
    memset(&out, 0, sizeof out);
    out.panel = rect(x, y, w, h);
    double by = y + SP_HEADER_H + (double)nrow * SP_ROW_H + SP_PAD;
    for (int i = 0; i < nact; ++i) {
        chl_rect a = rect(x + SP_PAD, by, w - 2.0 * SP_PAD, SP_ACTION_H);
        if (a.y + a.h > y + h || a.w <= 0.0) break; /* only buttons that fit exist */
        out.action[out.action_count++] = a;
        by += SP_ACTION_H + SP_ACTION_GAP;
    }
    *g = out;
    return SP_OK;
}

int sp_hit(const sp_geom *g, double x, double y) {
    if (g == NULL || !chl_rect_has(g->panel, x, y)) return SP_HIT_OUTSIDE;
    for (int i = 0; i < g->action_count && i < SP_MAX_ACTIONS; ++i)
        if (chl_rect_has(g->action[i], x, y)) return SP_HIT_ACTION0 + i;
    return SP_HIT_PANEL;
}
