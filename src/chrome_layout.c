/* chrome_layout -- browser chrome geometry + identity badge. spec/chrome_layout.md */
#include "chrome_layout.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

/* Inset of a tab's close button from the tab's right edge. */
#define CHL_TAB_CLOSE_INSET 6.0
/* Space between the reload button / the menu button and the URL pill. */
#define CHL_URL_GAP 8.0
/* Inset of the identity badge inside the pill. */
#define CHL_ID_INSET 2.0
/* Largest width the layout honours; anything above is clamped so every sum stays finite. */
#define CHL_WIDTH_MAX 1.0e7

static chl_rect rect(double x, double y, double w, double h) {
    chl_rect r;
    r.x = x;
    r.y = y;
    r.w = (w > 0.0) ? w : 0.0;
    r.h = (h > 0.0) ? h : 0.0;
    return r;
}

int chl_rect_has(chl_rect r, double x, double y) {
    return r.w > 0.0 && r.h > 0.0 && x >= r.x && x < r.x + r.w && y >= r.y && y < r.y + r.h;
}

chl_status chl_compute(double width, int csd, int tab_count, int active, chl_layout *out) {
    if (out == NULL || tab_count < 1 || active < 0 || active >= tab_count) return CHL_EINVAL;
    if (!isfinite(width) || width < 1.0) width = 1.0;
    if (width > CHL_WIDTH_MAX) width = CHL_WIDTH_MAX;

    chl_layout l;
    memset(&l, 0, sizeof l);
    l.width = width;
    l.csd = csd != 0;
    l.tab_count = tab_count;
    l.active = active;
    l.tabbar_top = 0.0;
    l.toolbar_top = CHL_TABBAR_H;
    l.content_top = CHL_TABBAR_H + CHL_TOOLBAR_H;

    /* Row 1: window buttons at the right (CSD), then a guaranteed drag area. */
    double right_limit;
    if (l.csd) {
        l.win_close = rect(width - CHL_WIN_BTN_W, 0.0, CHL_WIN_BTN_W, CHL_TABBAR_H);
        l.win_max   = rect(width - 2.0 * CHL_WIN_BTN_W, 0.0, CHL_WIN_BTN_W, CHL_TABBAR_H);
        l.win_min   = rect(width - 3.0 * CHL_WIN_BTN_W, 0.0, CHL_WIN_BTN_W, CHL_TABBAR_H);
        right_limit = l.win_min.x - CHL_DRAG_MIN;
    } else {
        right_limit = width - CHL_PAD;
    }

    /* Tabs share the room; when they do not all fit, an indicator at each end of the strip
     * takes its slot (stable positions whichever side hides tabs). */
    int overflow = 0, fit = 0;
    double tw = CHL_TAB_MIN_W, slot = tw + CHL_TAB_GAP;
    for (int pass = 0; pass < 2; ++pass) {
        double more = overflow ? CHL_MORE_W : 0.0;
        l.tab_x0 = CHL_PAD + more;
        double tabs_room = right_limit - CHL_NEWTAB_W - l.tab_x0 - more; /* tabs + their gaps */
        tw = tabs_room / (double)tab_count - CHL_TAB_GAP;
        if (!(tw <= CHL_TAB_MAX_W)) tw = CHL_TAB_MAX_W;
        if (tw < CHL_TAB_MIN_W) tw = CHL_TAB_MIN_W;
        slot = tw + CHL_TAB_GAP;
        fit = 0;
        if (tabs_room + CHL_TAB_GAP >= slot) {
            double f = floor((tabs_room + CHL_TAB_GAP) / slot);
            fit = (f >= (double)tab_count) ? tab_count : (int)f;
        }
        if (fit >= tab_count || overflow) break;
        overflow = 1;
    }
    l.tab_w = tw;
    l.tabs_visible = fit;
    /* Scroll the strip so the active tab is always among the visible ones. */
    l.tab_first = (fit > 0 && active >= fit) ? active - fit + 1 : 0;
    l.hidden_left = l.tab_first;
    l.hidden_right = tab_count - l.tab_first - fit;

    double tab_y = CHL_TAB_TOP_GAP;
    double tab_h = CHL_TABBAR_H - CHL_TAB_TOP_GAP;
    double strip_end = l.tab_x0 + (double)fit * slot;
    if (overflow) {
        l.more_left  = rect(CHL_PAD, tab_y, CHL_MORE_W - CHL_TAB_GAP, tab_h);
        l.more_right = rect(strip_end, tab_y, CHL_MORE_W - CHL_TAB_GAP, tab_h);
        strip_end += CHL_MORE_W;
    }
    l.new_tab = rect(strip_end, tab_y + (tab_h - CHL_NEWTAB_W) / 2.0, CHL_NEWTAB_W, CHL_NEWTAB_W);

    /* Row 2: round buttons, the URL pill with its identity badge, the menu. */
    double by = l.toolbar_top + (CHL_TOOLBAR_H - CHL_BTN) / 2.0;
    l.back   = rect(CHL_PAD, by, CHL_BTN, CHL_BTN);
    l.fwd    = rect(l.back.x + CHL_BTN + CHL_BTN_GAP, by, CHL_BTN, CHL_BTN);
    l.reload = rect(l.fwd.x + CHL_BTN + CHL_BTN_GAP, by, CHL_BTN, CHL_BTN);
    double mx = width - CHL_PAD - CHL_BTN;
    if (mx < l.reload.x + CHL_BTN) mx = l.reload.x + CHL_BTN;
    l.menu = rect(mx, by, CHL_BTN, CHL_BTN);
    double ux = l.reload.x + CHL_BTN + CHL_URL_GAP;
    double uy = l.toolbar_top + (CHL_TOOLBAR_H - CHL_URL_H) / 2.0;
    l.url = rect(ux, uy, l.menu.x - CHL_URL_GAP - ux, CHL_URL_H);
    double iw = l.url.w - 2.0 * CHL_ID_INSET;
    if (iw > CHL_ID_W) iw = CHL_ID_W;
    l.identity = rect(l.url.x + CHL_ID_INSET, uy + CHL_ID_INSET, iw, CHL_URL_H - 2.0 * CHL_ID_INSET);

    *out = l;
    return CHL_OK;
}

int chl_tab_rect(const chl_layout *l, int i, chl_rect *r) {
    if (l == NULL || i < l->tab_first || i >= l->tab_first + l->tabs_visible || i >= l->tab_count)
        return 0;
    if (r != NULL) {
        double x = l->tab_x0 + (double)(i - l->tab_first) * (l->tab_w + CHL_TAB_GAP);
        *r = rect(x, CHL_TAB_TOP_GAP, l->tab_w, CHL_TABBAR_H - CHL_TAB_TOP_GAP);
    }
    return 1;
}

int chl_tab_close_rect(const chl_layout *l, int i, chl_rect *r) {
    chl_rect t;
    if (l == NULL || l->tab_count < 2 || !chl_tab_rect(l, i, &t)) return 0;
    if (l->tab_w < CHL_TAB_CLOSE_MIN_W && i != l->active) return 0;
    if (r != NULL)
        *r = rect(t.x + t.w - CHL_TAB_CLOSE_INSET - CHL_TAB_CLOSE,
                  t.y + (t.h - CHL_TAB_CLOSE) / 2.0, CHL_TAB_CLOSE, CHL_TAB_CLOSE);
    return 1;
}

chl_part chl_hit(const chl_layout *l, double x, double y, int *tab) {
    if (tab != NULL) *tab = -1;
    if (l == NULL || !isfinite(x) || !isfinite(y) || y < 0.0) return CHL_PART_NONE;
    if (y >= l->content_top) return CHL_PART_CONTENT;
    if (y < l->toolbar_top) {
        if (l->csd) {
            if (chl_rect_has(l->win_close, x, y)) return CHL_PART_WIN_CLOSE;
            if (chl_rect_has(l->win_max, x, y))   return CHL_PART_WIN_MAX;
            if (chl_rect_has(l->win_min, x, y))   return CHL_PART_WIN_MIN;
        }
        if (l->hidden_left > 0 && chl_rect_has(l->more_left, x, y))   return CHL_PART_TABS_LEFT;
        if (l->hidden_right > 0 && chl_rect_has(l->more_right, x, y)) return CHL_PART_TABS_RIGHT;
        if (chl_rect_has(l->more_left, x, y) || chl_rect_has(l->more_right, x, y))
            return CHL_PART_NONE;  /* an inert indicator is not a drag handle either */
        for (int i = l->tab_first; i < l->tab_first + l->tabs_visible; ++i) {
            chl_rect t, c;
            if (!chl_tab_rect(l, i, &t) || !chl_rect_has(t, x, y)) continue;
            if (tab != NULL) *tab = i;
            if (chl_tab_close_rect(l, i, &c) && chl_rect_has(c, x, y)) return CHL_PART_TAB_CLOSE;
            return CHL_PART_TAB;
        }
        if (chl_rect_has(l->new_tab, x, y)) return CHL_PART_NEW_TAB;
        return l->csd ? CHL_PART_DRAG : CHL_PART_NONE;
    }
    if (chl_rect_has(l->back, x, y))     return CHL_PART_BACK;
    if (chl_rect_has(l->fwd, x, y))      return CHL_PART_FWD;
    if (chl_rect_has(l->reload, x, y))   return CHL_PART_RELOAD;
    if (chl_rect_has(l->identity, x, y)) return CHL_PART_IDENTITY;
    if (chl_rect_has(l->url, x, y))      return CHL_PART_URL;
    if (chl_rect_has(l->menu, x, y))     return CHL_PART_MENU;
    return CHL_PART_NONE;
}

int chl_tab_drop_index(const chl_layout *l, double x) {
    if (l == NULL || l->tabs_visible < 1) return -1;
    int lo = l->tab_first, hi = l->tab_first + l->tabs_visible - 1;
    if (hi >= l->tab_count) hi = l->tab_count - 1;
    if (!isfinite(x) || x < l->tab_x0) return lo;
    double k = floor((x - l->tab_x0) / (l->tab_w + CHL_TAB_GAP));
    if (!(k < (double)(hi - lo))) return hi;
    return lo + (int)k;
}

int chl_move_index(int i, int from, int to) {
    if (i == from) return to;
    if (from < to && i > from && i <= to) return i - 1;
    if (to < from && i >= to && i < from) return i + 1;
    return i;
}

int chl_tab_for_digit(int digit, int tab_count) {
    if (tab_count < 1 || digit < 1 || digit > 9) return -1;
    if (digit == 9) return tab_count - 1;
    return (digit <= tab_count) ? digit - 1 : -1;
}

/* --- identity badge --- */

static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; }

/* 1 if s starts with prefix, ASCII case-insensitively. */
static int has_prefix_ci(const char *s, const char *prefix) {
    for (; *prefix != '\0'; ++s, ++prefix)
        if (*s == '\0' || lower((unsigned char)*s) != lower((unsigned char)*prefix)) return 0;
    return 1;
}

/* 1 if the n-byte host ends in the label suffix (".onion"), case-insensitively. */
static int host_ends_with(const char *h, size_t n, const char *suffix) {
    size_t k = strlen(suffix);
    if (n <= k) return 0;
    for (size_t i = 0; i < k; ++i)
        if (lower((unsigned char)h[n - k + i]) != (unsigned char)suffix[i]) return 0;
    return 1;
}

/* Host of an authority-bearing URL after "scheme://": userinfo, port and one trailing
 * dot removed. Returns its length (0 when empty) and points *out at it. */
static size_t url_host(const char *rest, const char **out) {
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
    if (n > 0 && h[n - 1] == '.') --n;
    *out = h;
    return n;
}

chl_identity chl_identity_of(const char *url, int transport_known, int downgrade,
                             int operator_insecure) {
    if (url == NULL || url[0] == '\0' || has_prefix_ci(url, "about:")) return CHL_ID_INTERNAL;
    if (has_prefix_ci(url, "file:")) return CHL_ID_LOCAL;
    int https = has_prefix_ci(url, "https://");
    int http = !https && has_prefix_ci(url, "http://");
    if (!https && !http) return CHL_ID_UNKNOWN;

    const char *host = NULL;
    size_t hn = url_host(url + (https ? 8 : 7), &host);
    if (hn == 0) return CHL_ID_UNKNOWN;
    int overlay = host_ends_with(host, hn, ".onion") || host_ends_with(host, hn, ".i2p");

    if (operator_insecure) return CHL_ID_UNVERIFIED;
    if (http) return host_ends_with(host, hn, ".i2p") ? CHL_ID_OVERLAY : CHL_ID_INSECURE;
    if (!transport_known) return CHL_ID_UNKNOWN;
    switch (downgrade) {
        case CHL_DG_ALLOWLISTED:  return CHL_ID_WEAK;
        case CHL_DG_CLASSICAL_KE: return CHL_ID_CLASSICAL;
        case CHL_DG_NONE:         return overlay ? CHL_ID_OVERLAY : CHL_ID_PQ;
        default:                  return CHL_ID_UNKNOWN;
    }
}

const char *chl_identity_label(chl_identity id) {
    switch (id) {
        case CHL_ID_INTERNAL:   return "Freedom page";
        case CHL_ID_LOCAL:      return "Local file (no network)";
        case CHL_ID_PQ:         return "Post-quantum secure: TLS 1.3 + hybrid ML-KEM key exchange";
        case CHL_ID_CLASSICAL:  return "Secure, but not post-quantum (classical TLS 1.3)";
        case CHL_ID_WEAK:       return "Weak crypto allowed by your allowlist (certificate verified)";
        case CHL_ID_OVERLAY:    return "Routed through the Tor/I2P overlay";
        case CHL_ID_UNVERIFIED: return "Certificate NOT verified (--insecure)";
        case CHL_ID_INSECURE:   return "Not secure: plaintext connection";
        case CHL_ID_UNKNOWN:
        default:                return "Connection security unknown";
    }
}

/* Find bar: the field at the left, prev/next right after it, the match count, and the
 * close button at the right edge. A narrow window shrinks the count, then the field. */
chl_status chl_findbar_compute(double width, double height, chl_findbar *out) {
    if (out == NULL) return CHL_EINVAL;
    if (!isfinite(width) || width < 1.0) width = 1.0;
    if (width > CHL_WIDTH_MAX) width = CHL_WIDTH_MAX;
    if (!isfinite(height) || height < 1.0) height = 1.0;
    if (height > CHL_WIDTH_MAX) height = CHL_WIDTH_MAX;
    chl_findbar f;
    memset(&f, 0, sizeof f);
    double top = height - CHL_FIND_H;
    f.bar = rect(0.0, top, width, CHL_FIND_H);
    double fy = top + (CHL_FIND_H - CHL_FIND_FIELD_H) / 2.0;
    double by = top + (CHL_FIND_H - CHL_FIND_BTN) / 2.0;
    double room = width - 2.0 * CHL_PAD;            /* everything sits inside the padding */
    double fixed = 3.0 * CHL_FIND_BTN + 3.0 * CHL_BTN_GAP + CHL_URL_GAP;
    double count_w = CHL_FIND_COUNT_W;
    double field_w = CHL_FIND_FIELD_W;
    double over = fixed + field_w + count_w - room;
    if (over > 0.0) { double c = (over < count_w) ? over : count_w; count_w -= c; over -= c; }
    if (over > 0.0) { double c = (over < field_w) ? over : field_w; field_w -= c; over -= c; }
    if (over > 0.0) {                               /* not even the buttons fit: show none */
        *out = f;
        return CHL_OK;
    }
    double x = CHL_PAD;
    f.field = rect(x, fy, field_w, CHL_FIND_FIELD_H);
    x += field_w + CHL_BTN_GAP;
    f.prev = rect(x, by, CHL_FIND_BTN, CHL_FIND_BTN);
    x += CHL_FIND_BTN + CHL_BTN_GAP;
    f.next = rect(x, by, CHL_FIND_BTN, CHL_FIND_BTN);
    x += CHL_FIND_BTN + CHL_URL_GAP;
    f.count = rect(x, fy, count_w, CHL_FIND_FIELD_H);
    f.close = rect(width - CHL_PAD - CHL_FIND_BTN, by, CHL_FIND_BTN, CHL_FIND_BTN);
    *out = f;
    return CHL_OK;
}

chl_find_part chl_findbar_hit(const chl_findbar *f, double x, double y) {
    if (f == NULL || !chl_rect_has(f->bar, x, y)) return CHL_FIND_NONE;
    if (chl_rect_has(f->field, x, y)) return CHL_FIND_FIELD;
    if (chl_rect_has(f->prev, x, y))  return CHL_FIND_PREV;
    if (chl_rect_has(f->next, x, y))  return CHL_FIND_NEXT;
    if (chl_rect_has(f->close, x, y)) return CHL_FIND_CLOSE;
    return CHL_FIND_BAR;
}

