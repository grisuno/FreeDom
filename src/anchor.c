/* anchor.c — the indicated part of a document and where it sits (spec/anchor.md). */
#include "anchor.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

static int hex_val(int c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

size_t anc_percent_decode(const char *in, char *out, size_t cap) {
    if (out == NULL || cap == 0) return (size_t)-1;
    out[0] = '\0';
    if (in == NULL) return (size_t)-1;
    size_t n = 0;
    for (size_t i = 0; in[i] != '\0'; ++i) {
        unsigned char b = (unsigned char)in[i];
        if (b == '%') {
            int hi = hex_val((unsigned char)in[i + 1]);
            int lo = (hi >= 0) ? hex_val((unsigned char)in[i + 2]) : -1;
            if (hi >= 0 && lo >= 0) { b = (unsigned char)(hi * 16 + lo); i += 2; }
        }
        if (n + 1 >= cap) { out[0] = '\0'; return (size_t)-1; }
        out[n++] = (char)b;
    }
    out[n] = '\0';
    return n;
}

/* The first connected <a> in tree order whose name attribute is exactly name. */
static dom_node_id first_named_a(const dom_index *idx, const char *name) {
    size_t total = dom_get_by_tag(idx, "a", NULL, 0);
    if (total == 0) return DOM_NODE_NONE;
    dom_node_id *ids = (dom_node_id *)calloc(total, sizeof *ids);
    if (ids == NULL) return DOM_NODE_NONE;
    size_t n = dom_get_by_tag(idx, "a", ids, total);
    if (n > total) n = total;
    dom_node_id best = DOM_NODE_NONE;
    for (size_t i = 0; i < n; ++i) {
        if (!dom_is_connected(idx, ids[i])) continue;
        const char *v = dom_get_attribute(idx, ids[i], "name", NULL);
        if (v == NULL || strcmp(v, name) != 0) continue;
        if (best == DOM_NODE_NONE || dom_precedes(idx, ids[i], best)) best = ids[i];
    }
    free(ids);
    return best;
}

/* HTML 7.4.6.4 "find a potential indicated element". */
static dom_node_id potential_indicated(const dom_index *idx, const char *s) {
    dom_node_id t = dom_get_connected_by_id(idx, s);
    return (t != DOM_NODE_NONE) ? t : first_named_a(idx, s);
}

static int is_top(const char *s) {
    return (s[0] | 0x20) == 't' && (s[1] | 0x20) == 'o' && (s[2] | 0x20) == 'p' && s[3] == '\0';
}

anc_kind anc_resolve(const dom_index *idx, const char *fragment, dom_node_id *out) {
    if (idx == NULL || fragment == NULL || out == NULL) return ANC_NONE;
    size_t len = strlen(fragment);
    if (len >= ANC_MAX_FRAGMENT) return ANC_NONE;
    if (len == 0) return ANC_TOP;
    dom_node_id t = potential_indicated(idx, fragment);
    if (t != DOM_NODE_NONE) { *out = t; return ANC_ELEMENT; }
    char dec[ANC_MAX_FRAGMENT];
    size_t dl = anc_percent_decode(fragment, dec, sizeof dec);
    if (dl == (size_t)-1 || dl != strlen(dec)) return ANC_NONE;   /* embedded NUL */
    if (dl != 0 && strcmp(dec, fragment) != 0) {
        t = potential_indicated(idx, dec);
        if (t != DOM_NODE_NONE) { *out = t; return ANC_ELEMENT; }
    }
    return is_top(dec) ? ANC_TOP : ANC_NONE;
}

/* Next element after cur in preorder; *left set once the walk climbs out of root. */
static dom_node_id next_preorder(const dom_index *idx, dom_node_id cur, dom_node_id root,
                                 int *left) {
    dom_node_id c = dom_first_child(idx, cur);
    if (c != DOM_NODE_NONE) return c;
    for (dom_node_id x = cur; x != DOM_NODE_NONE; x = dom_parent(idx, x)) {
        if (x == root) *left = 1;
        dom_node_id s = dom_next_sibling(idx, x);
        if (s != DOM_NODE_NONE) return s;
    }
    return DOM_NODE_NONE;
}

size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap,
                   size_t *nsub) {
    if (nsub == NULL) return 0;
    *nsub = 0;
    if (idx == NULL || out == NULL || cap == 0 || !dom_is_connected(idx, target)) return 0;
    if (cap > ANC_MAX_HANDLES) cap = ANC_MAX_HANDLES;
    size_t n = 0;
    int left = 0;
    for (dom_node_id cur = target; cur != DOM_NODE_NONE && n < cap;) {
        out[n++] = cur;
        cur = next_preorder(idx, cur, target, &left);
        if (left && *nsub == 0) *nsub = n;
    }
    if (*nsub == 0) *nsub = n;
    return n;
}

int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub,
                   double *top) {
    if (g == NULL || h == NULL || top == NULL) return -1;
    if (nsub > n) nsub = n;
    int found = 0;
    double best = 0.0;
    for (size_t i = 0; i < nsub; ++i) {
        const jg_rect *r = jg_find(g, h[i]);
        if (r == NULL) continue;
        if (!found || (double)r->y < best) best = (double)r->y;
        found = 1;
    }
    for (size_t i = nsub; i < n && !found; ++i) {
        const jg_rect *r = jg_find(g, h[i]);
        if (r != NULL) { best = (double)r->y; found = 1; }
    }
    if (!found) return -1;
    *top = best;
    return 0;
}

double anc_scroll_for(double top, double max_scroll) {
    if (!isfinite(top) || !isfinite(max_scroll) || max_scroll < 0.0) return 0.0;
    if (top < 0.0) return 0.0;
    return (top > max_scroll) ? max_scroll : top;
}
