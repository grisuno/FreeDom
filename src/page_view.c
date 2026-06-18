/*
 * page_view — implementation (Lexbor backend, via the hp_document_root seam).
 *
 * Walks the inert, sanitised tree iteratively (child/sibling/parent, never
 * recursively, so attacker-controlled nesting cannot overflow the stack) and
 * emits an ordered display list of inline runs. The tree is read-only here; the
 * view owns copies of all text/href bytes, so it outlives the hp_document.
 */

#define _POSIX_C_SOURCE 200809L

#include "page_view.h"
#include "css_color.h"
#include "html_parse.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <lexbor/dom/dom.h>
#include <lexbor/html/html.h>
#include <lexbor/tag/const.h>

/* Upper bound for a parsed <img> declared dimension. A declared size only feeds
 * the tracking-pixel heuristic and the layout hint, so absurd values are clamped
 * rather than trusted; this also keeps parse_dim free of integer overflow. */
#define PV_MAX_DIM 1000000

/* --- UTF-8 sanitisation (cairo rejects invalid UTF-8; legacy-encoded pages
 * carry bytes that are invalid UTF-8). Mirrors browser.c's sanitiser; kept local
 * so page_view stays self-contained. Output is never longer than the input. --- */

static size_t utf8_seq_len(unsigned char c) {
    if (c < 0x80) return 1;
    if (c >= 0xC2 && c <= 0xDF) return 2;
    if (c >= 0xE0 && c <= 0xEF) return 3;
    if (c >= 0xF0 && c <= 0xF4) return 4;
    return 0;
}

static char *utf8_sanitized_dup(const char *s) {
    size_t n = strlen(s);
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    size_t i = 0, o = 0;
    while (i < n) {
        unsigned char c = (unsigned char)s[i];
        size_t L = utf8_seq_len(c);
        int ok = (L >= 1 && i + L <= n);
        for (size_t k = 1; ok && k < L; ++k) {
            if (((unsigned char)s[i + k] & 0xC0) != 0x80) ok = 0;
        }
        if (ok && L == 3 && c == 0xE0 && (unsigned char)s[i + 1] < 0xA0) ok = 0;
        if (ok && L == 3 && c == 0xED && (unsigned char)s[i + 1] > 0x9F) ok = 0;
        if (ok && L == 4 && c == 0xF0 && (unsigned char)s[i + 1] < 0x90) ok = 0;
        if (ok && L == 4 && c == 0xF4 && (unsigned char)s[i + 1] > 0x8F) ok = 0;
        if (ok) {
            for (size_t k = 0; k < L; ++k) d[o++] = s[i + k];
            i += L;
        } else {
            d[o++] = '?';
            i += 1;
        }
    }
    d[o] = '\0';
    return d;
}

static char *dup_n(const char *s, size_t n) {
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    if (n != 0 && s != NULL) memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

/* --- public: model --- */

pv_view *pv_new(void) {
    return (pv_view *)calloc(1, sizeof(pv_view));
}

pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    const char *text, const char *href) {
    if (v == NULL || text == NULL) return PV_ERR_NULL_ARG;

    if (v->count == v->cap) {
        size_t ncap = v->cap ? v->cap * 2 : 32;
        pv_run *grown = (pv_run *)realloc(v->runs, ncap * sizeof *grown);
        if (grown == NULL) return PV_ERR_OOM;
        v->runs = grown;
        v->cap = ncap;
    }

    char *t = utf8_sanitized_dup(text);
    if (t == NULL) return PV_ERR_OOM;
    char *h = NULL;
    if (href != NULL) {
        h = dup_n(href, strlen(href));
        if (h == NULL) { free(t); return PV_ERR_OOM; }
    }

    pv_run *r = &v->runs[v->count++];
    r->kind = kind;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->href = h;
    r->src = NULL;
    r->img_w = -1;
    r->img_h = -1;
    r->fg_rgb = -1;
    r->input_type = 0;
    r->name = NULL;
    r->value = NULL;
    r->form_id = -1;
    r->form_method = PV_METHOD_GET;
    return PV_OK;
}

pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src, int w, int h) {
    if (v == NULL || src == NULL) return PV_ERR_NULL_ARG;

    if (v->count == v->cap) {
        size_t ncap = v->cap ? v->cap * 2 : 32;
        pv_run *grown = (pv_run *)realloc(v->runs, ncap * sizeof *grown);
        if (grown == NULL) return PV_ERR_OOM;
        v->runs = grown;
        v->cap = ncap;
    }

    char *t = utf8_sanitized_dup(alt != NULL ? alt : "");
    if (t == NULL) return PV_ERR_OOM;
    char *s = utf8_sanitized_dup(src);
    if (s == NULL) { free(t); return PV_ERR_OOM; }

    pv_run *r = &v->runs[v->count++];
    r->kind = PV_IMAGE;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->href = NULL;
    r->src = s;
    r->img_w = w;
    r->img_h = h;
    r->fg_rgb = -1;
    r->input_type = 0;
    r->name = NULL;
    r->value = NULL;
    r->form_id = -1;
    r->form_method = PV_METHOD_GET;
    return PV_OK;
}

pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_input_type input_type, const char *text,
                          const char *name, const char *value,
                          const char *action, int form_id, int method) {
    if (v == NULL) return PV_ERR_NULL_ARG;

    if (v->count == v->cap) {
        size_t ncap = v->cap ? v->cap * 2 : 32;
        pv_run *grown = (pv_run *)realloc(v->runs, ncap * sizeof *grown);
        if (grown == NULL) return PV_ERR_OOM;
        v->runs = grown;
        v->cap = ncap;
    }

    /* text is display (placeholder/label) -> UTF-8 sanitised; name/value/action are
     * submitted/resolved bytes -> copied verbatim. */
    char *t = utf8_sanitized_dup(text != NULL ? text : "");
    if (t == NULL) return PV_ERR_OOM;
    char *nm = (name != NULL) ? dup_n(name, strlen(name)) : NULL;
    if (name != NULL && nm == NULL) { free(t); return PV_ERR_OOM; }
    char *vl = (value != NULL) ? dup_n(value, strlen(value)) : NULL;
    if (value != NULL && vl == NULL) { free(t); free(nm); return PV_ERR_OOM; }
    char *ac = (action != NULL) ? dup_n(action, strlen(action)) : NULL;
    if (action != NULL && ac == NULL) { free(t); free(nm); free(vl); return PV_ERR_OOM; }

    pv_run *r = &v->runs[v->count++];
    r->kind = PV_INPUT;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->href = ac;
    r->src = NULL;
    r->img_w = -1;
    r->img_h = -1;
    r->fg_rgb = -1;
    r->input_type = (int)input_type;
    r->name = nm;
    r->value = vl;
    r->form_id = form_id;
    r->form_method = method;
    return PV_OK;
}

void pv_set_color(pv_view *v, int fg_rgb) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].fg_rgb = fg_rgb;
}

void pv_free(pv_view *v) {
    if (v == NULL) return;
    for (size_t i = 0; i < v->count; ++i) {
        free(v->runs[i].text);
        free(v->runs[i].href);
        free(v->runs[i].src);
        free(v->runs[i].name);
        free(v->runs[i].value);
    }
    free(v->runs);
    free(v);
}

size_t pv_count(const pv_view *v) {
    return (v != NULL) ? v->count : 0;
}

const pv_run *pv_at(const pv_view *v, size_t i) {
    if (v == NULL || i >= v->count) return NULL;
    return &v->runs[i];
}

/* --- builder helpers --- */

/* Iterative pre-order successor of node within the subtree rooted at root. */
static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root) {
    if (node->first_child != NULL) return node->first_child;
    while (node != root && node->next == NULL) {
        if (node->parent == NULL) return NULL;
        node = node->parent;
    }
    if (node == root) return NULL;
    return node->next;
}

static int is_block_tag(lxb_tag_id_t t) {
    switch (t) {
        case LXB_TAG_BODY: case LXB_TAG_DIV: case LXB_TAG_P:
        case LXB_TAG_H1: case LXB_TAG_H2: case LXB_TAG_H3:
        case LXB_TAG_H4: case LXB_TAG_H5: case LXB_TAG_H6:
        case LXB_TAG_UL: case LXB_TAG_OL: case LXB_TAG_LI:
        case LXB_TAG_SECTION: case LXB_TAG_ARTICLE: case LXB_TAG_HEADER:
        case LXB_TAG_FOOTER: case LXB_TAG_NAV: case LXB_TAG_MAIN:
        case LXB_TAG_ASIDE: case LXB_TAG_BLOCKQUOTE: case LXB_TAG_PRE:
        case LXB_TAG_TABLE: case LXB_TAG_TR: case LXB_TAG_FIGURE:
        case LXB_TAG_FORM: case LXB_TAG_FIELDSET: case LXB_TAG_DL:
        case LXB_TAG_DT: case LXB_TAG_DD:
            return 1;
        default:
            return 0;
    }
}

static int heading_level(lxb_tag_id_t t) {
    switch (t) {
        case LXB_TAG_H1: return 1;
        case LXB_TAG_H2: return 2;
        case LXB_TAG_H3: return 3;
        case LXB_TAG_H4: return 4;
        case LXB_TAG_H5: return 5;
        case LXB_TAG_H6: return 6;
        default:         return 0;
    }
}

static int is_skipped_tag(lxb_tag_id_t t) {
    /* TEXTAREA/SELECT/BUTTON content is a control's value/label, emitted as a
     * PV_INPUT, not as page text; suppress their inner text from the normal walk. */
    return t == LXB_TAG_SCRIPT || t == LXB_TAG_STYLE || t == LXB_TAG_HEAD
        || t == LXB_TAG_TITLE  || t == LXB_TAG_NOSCRIPT
        || t == LXB_TAG_TEXTAREA || t == LXB_TAG_SELECT || t == LXB_TAG_BUTTON;
}

static lxb_tag_id_t node_tag(const lxb_dom_node_t *n) {
    return lxb_dom_element_tag_id(lxb_dom_interface_element((lxb_dom_node_t *)n));
}

/* Nonzero if any ancestor up to base is a non-rendered container. */
static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT && is_skipped_tag(node_tag(p))) return 1;
        if (p == base) break;
    }
    return 0;
}

/* Largest color token value extracted from markup. A longer value is not a valid
 * color and is ignored (fail closed). */
#define PV_COLOR_TOKEN_MAX 64u

static int ascii_eq_color(const char *p) {
    return (p[0] | 0x20) == 'c' && (p[1] | 0x20) == 'o' && (p[2] | 0x20) == 'l'
        && (p[3] | 0x20) == 'o' && (p[4] | 0x20) == 'r';
}

/* Extracts the value of the CSS `color` declaration from an inline style string
 * and parses it. Matches the property name exactly (length 5) so "background-color"
 * is never mistaken for "color"; the last `color` declaration wins (the cascade).
 * Returns the packed 0xRRGGBB color, or -1 when absent or unparseable. */
static int color_from_style(const char *style, size_t len) {
    int result = -1;
    size_t i = 0;
    while (i < len) {
        size_t ds = i;
        while (i < len && style[i] != ';') ++i;
        size_t de = i;
        if (i < len) ++i; /* skip ';' */

        size_t colon = ds;
        while (colon < de && style[colon] != ':') ++colon;
        if (colon >= de) continue;

        size_t ps = ds, pe = colon;
        while (ps < pe && (style[ps] == ' ' || style[ps] == '\t')) ++ps;
        while (pe > ps && (style[pe - 1] == ' ' || style[pe - 1] == '\t')) --pe;
        if (pe - ps != 5 || !ascii_eq_color(style + ps)) continue;

        size_t vs = colon + 1, ve = de;
        while (vs < ve && (style[vs] == ' ' || style[vs] == '\t')) ++vs;
        while (ve > vs && (style[ve - 1] == ' ' || style[ve - 1] == '\t')) --ve;
        size_t vlen = ve - vs;
        if (vlen == 0 || vlen >= PV_COLOR_TOKEN_MAX) continue;

        char buf[PV_COLOR_TOKEN_MAX];
        memcpy(buf, style + vs, vlen);
        buf[vlen] = '\0';
        cc_rgb rgb;
        if (cc_parse(buf, &rgb) == CC_OK) result = cc_pack(rgb);
    }
    return result;
}

/* Author foreground color declared directly on el (inline style "color:", or the
 * legacy <font color> attribute), or -1 if none/unparseable. */
static int element_color(lxb_dom_element_t *el, lxb_tag_id_t tag) {
    size_t sl = 0;
    const lxb_char_t *style =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"style", 5, &sl);
    if (style != NULL && sl > 0) {
        int c = color_from_style((const char *)style, sl);
        if (c >= 0) return c;
    }
    if (tag == LXB_TAG_FONT) {
        size_t cl = 0;
        const lxb_char_t *col =
            lxb_dom_element_get_attribute(el, (const lxb_char_t *)"color", 5, &cl);
        if (col != NULL && cl > 0 && cl < PV_COLOR_TOKEN_MAX) {
            char buf[PV_COLOR_TOKEN_MAX];
            memcpy(buf, col, cl);
            buf[cl] = '\0';
            cc_rgb rgb;
            if (cc_parse(buf, &rgb) == CC_OK) return cc_pack(rgb);
        }
    }
    return -1;
}

/* Resolves the inline context of a text node: nearest <a href>, nearest heading
 * level, nearest block-level ancestor (defaults to base), and the inherited author
 * color (nearest ancestor that sets one, packed 0xRRGGBB, or -1). */
static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                            const char **href, size_t *href_len,
                            const lxb_dom_node_t **block, int *heading, int *fg) {
    *href = NULL; *href_len = 0; *block = base; *heading = 0; *fg = -1;
    int got_link = 0, got_block = 0, got_heading = 0, got_color = 0;

    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)p);
            lxb_tag_id_t t = lxb_dom_element_tag_id(el);
            if (!got_link && t == LXB_TAG_A) {
                size_t hl = 0;
                const lxb_char_t *h =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"href", 4, &hl);
                if (h != NULL && hl > 0) { *href = (const char *)h; *href_len = hl; got_link = 1; }
            }
            if (!got_heading) { int lv = heading_level(t); if (lv) { *heading = lv; got_heading = 1; } }
            if (!got_block && is_block_tag(t)) { *block = p; got_block = 1; }
            if (!got_color) { int c = element_color(el, t); if (c >= 0) { *fg = c; got_color = 1; } }
        }
        if (p == base) break;
    }
}

/* Collapses ASCII whitespace runs to a single space into a fresh buffer. */
static char *collapse_ws(const char *s, size_t n) {
    char *out = (char *)malloc(n + 1);
    if (out == NULL) return NULL;
    size_t o = 0;
    int prev_ws = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)s[i];
        int ws = (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f');
        if (ws) {
            if (!prev_ws) out[o++] = ' ';
            prev_ws = 1;
        } else {
            out[o++] = (char)c;
            prev_ws = 0;
        }
    }
    out[o] = '\0';
    return out;
}

/* Parses the leading non-negative integer of an HTML length attribute value
 * (e.g. "640", "640px", "50%"). Returns the value clamped to a sane bound, or -1
 * if the value is absent, empty, or does not start with a digit. */
static int parse_dim(const lxb_char_t *s, size_t len) {
    if (s == NULL || len == 0) return -1;
    size_t i = 0;
    while (i < len && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i >= len || s[i] < '0' || s[i] > '9') return -1;
    long v = 0;
    for (; i < len && s[i] >= '0' && s[i] <= '9'; ++i) {
        v = v * 10 + (s[i] - '0');
        if (v > PV_MAX_DIM) { v = PV_MAX_DIM; break; }
    }
    return (int)v;
}

static lxb_dom_node_t *find_body(lxb_dom_node_t *root) {
    for (lxb_dom_node_t *n = root; n != NULL; n = node_next(n, root)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT && node_tag(n) == LXB_TAG_BODY) return n;
    }
    return NULL;
}

/* --- form controls --- */

/* One <form> seen in document order: its grouping id is its index. action is an
 * owned NUL-terminated copy of the raw action attribute (or NULL); method is GET
 * unless method="post". */
typedef struct form_rec {
    const lxb_dom_node_t *node;
    char                 *action;
    int                   method;
} form_rec;

typedef struct form_table {
    form_rec *recs;
    size_t    count, cap;
} form_table;

static void forms_free(form_table *ft) {
    for (size_t i = 0; i < ft->count; ++i) free(ft->recs[i].action);
    free(ft->recs);
    ft->recs = NULL; ft->count = ft->cap = 0;
}

/* Case-insensitive ASCII equality of a NUL-terminated string against a literal. */
static int ascii_ieq(const char *s, const char *lit) {
    if (s == NULL) return 0;
    for (;; ++s, ++lit) {
        int a = (unsigned char)*s, b = (unsigned char)*lit;
        if (a >= 'A' && a <= 'Z') a += 'a' - 'A';
        if (a != b) return 0;
        if (a == '\0') return 1;
    }
}

/* Owned NUL-terminated copy of an attribute value, or NULL when the attribute is
 * absent. A present-but-empty attribute yields a "" string (distinguishable). */
static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen) {
    size_t L = 0;
    const lxb_char_t *v =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)name, namelen, &L);
    if (v == NULL) return NULL;
    return dup_n((const char *)v, L);
}

/* Records a <form> element. Returns 0, or -1 on OOM. */
static int forms_add(form_table *ft, const lxb_dom_node_t *node) {
    if (ft->count == ft->cap) {
        size_t nc = ft->cap ? ft->cap * 2 : 8;
        form_rec *g = (form_rec *)realloc(ft->recs, nc * sizeof *g);
        if (g == NULL) return -1;
        ft->recs = g; ft->cap = nc;
    }
    lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node);
    char *method = attr_dup(el, "method", 6);
    int m = ascii_ieq(method, "post") ? PV_METHOD_POST : PV_METHOD_GET;
    free(method);

    form_rec *r = &ft->recs[ft->count++];
    r->node = node;
    r->action = attr_dup(el, "action", 6); /* may be NULL (submit to current doc) */
    r->method = m;
    return 0;
}

/* Index of the nearest enclosing recorded form, or -1 when the control has none. */
static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_dom_node_t *base) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT && node_tag(p) == LXB_TAG_FORM) {
            for (size_t i = 0; i < ft->count; ++i)
                if (ft->recs[i].node == p) return (int)i;
        }
        if (p == base) break;
    }
    return -1;
}

/* Concatenates the descendant text of el into an owned NUL-terminated string (the
 * value of a <textarea> / the label of a <button>). Never NULL on success. */
static char *collect_text(const lxb_dom_node_t *el) {
    size_t cap = 0, len = 0;
    char *buf = NULL;
    for (lxb_dom_node_t *n = el->first_child; n != NULL; n = node_next(n, el)) {
        if (n->type != LXB_DOM_NODE_TYPE_TEXT) continue;
        lxb_dom_text_t *txt = lxb_dom_interface_text(n);
        const char *raw = (const char *)txt->char_data.data.data;
        size_t rl = txt->char_data.data.length;
        if (raw == NULL || rl == 0) continue;
        if (len + rl + 1 > cap) {
            size_t nc = (len + rl + 1) * 2;
            char *g = (char *)realloc(buf, nc);
            if (g == NULL) { free(buf); return NULL; }
            buf = g; cap = nc;
        }
        memcpy(buf + len, raw, rl);
        len += rl;
    }
    if (buf == NULL) return dup_n("", 0);
    buf[len] = '\0';
    return buf;
}

static pv_input_type classify_input(const char *type) {
    if (type == NULL) return PV_IN_TEXT; /* default input type is text */
    if (ascii_ieq(type, "hidden"))   return PV_IN_HIDDEN;
    if (ascii_ieq(type, "password")) return PV_IN_PASSWORD;
    if (ascii_ieq(type, "submit"))   return PV_IN_SUBMIT;
    if (ascii_ieq(type, "image"))    return PV_IN_SUBMIT; /* image button submits */
    if (ascii_ieq(type, "button"))   return PV_IN_BUTTON;
    if (ascii_ieq(type, "reset"))    return PV_IN_BUTTON;
    /* text/search/email/url/tel/number and any other (date, color, checkbox, ...)
     * collapse to a one-line editable box for v1 (see spec: checkbox/radio/select
     * are out of scope). */
    return PV_IN_TEXT;
}

/* Fills owned label/name/value for a control element and its classified type.
 * Returns 0, or -1 on OOM (caller frees whatever is non-NULL). */
static int describe_control(lxb_dom_element_t *el, lxb_tag_id_t tag,
                            const lxb_dom_node_t *node, pv_input_type *out_type,
                            char **out_label, char **out_name, char **out_value) {
    *out_label = NULL; *out_name = NULL; *out_value = NULL;
    *out_type = PV_IN_TEXT;

    if (tag == LXB_TAG_TEXTAREA) {
        *out_type = PV_IN_TEXTAREA;
        *out_name = attr_dup(el, "name", 4);
        *out_value = collect_text(node);
        char *ph = attr_dup(el, "placeholder", 11);
        *out_label = (ph != NULL) ? ph : dup_n("", 0);
        if (*out_value == NULL || *out_label == NULL) return -1;
        return 0;
    }

    if (tag == LXB_TAG_BUTTON) {
        char *type = attr_dup(el, "type", 4);
        *out_type = (ascii_ieq(type, "button") || ascii_ieq(type, "reset"))
                    ? PV_IN_BUTTON : PV_IN_SUBMIT; /* default button type is submit */
        free(type);
        *out_name = attr_dup(el, "name", 4);
        *out_value = attr_dup(el, "value", 5);
        char *txt = collect_text(node);
        if (txt == NULL) return -1;
        char *lab = collapse_ws(txt, strlen(txt));
        free(txt);
        if (lab == NULL) return -1;
        if (lab[0] == '\0') { /* empty label: fall back to value or a generic word */
            free(lab);
            const char *fb = (*out_value != NULL && (*out_value)[0] != '\0') ? *out_value
                             : (*out_type == PV_IN_SUBMIT ? "Submit" : "Button");
            lab = dup_n(fb, strlen(fb));
        }
        *out_label = lab;
        if (*out_label == NULL) return -1;
        return 0;
    }

    /* <input> */
    char *type = attr_dup(el, "type", 4);
    *out_type = classify_input(type);
    free(type);
    *out_name = attr_dup(el, "name", 4);
    *out_value = attr_dup(el, "value", 5);
    if (*out_type == PV_IN_SUBMIT || *out_type == PV_IN_BUTTON) {
        const char *def = (*out_type == PV_IN_SUBMIT) ? "Submit" : "Button";
        const char *lab = (*out_value != NULL && (*out_value)[0] != '\0') ? *out_value : def;
        *out_label = dup_n(lab, strlen(lab));
    } else {
        char *ph = attr_dup(el, "placeholder", 11);
        *out_label = (ph != NULL) ? ph : dup_n("", 0);
    }
    if (*out_label == NULL) return -1;
    return 0;
}

/* --- public: builder --- */

pv_status pv_build(const hp_document *doc, pv_view **out) {
    if (doc == NULL || out == NULL) return PV_ERR_NULL_ARG;
    *out = NULL;

    pv_view *v = pv_new();
    if (v == NULL) return PV_ERR_OOM;

    lxb_dom_node_t *root = (lxb_dom_node_t *)hp_document_root(doc);
    if (root == NULL) { *out = v; return PV_OK; } /* empty document */

    lxb_dom_node_t *body = find_body(root);
    lxb_dom_node_t *base = (body != NULL) ? body : root;

    const lxb_dom_node_t *prev_block = NULL;
    int pending_break = 0;
    form_table forms = { NULL, 0, 0 };
    pv_status rc = PV_OK;

    for (lxb_dom_node_t *n = base; n != NULL; n = node_next(n, base)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(n);
            if (t == LXB_TAG_BR || t == LXB_TAG_HR) { pending_break = 1; continue; }

            if (t == LXB_TAG_FORM) {
                if (forms_add(&forms, n) != 0) { rc = PV_ERR_OOM; goto cleanup; }
                continue;
            }

            if ((t == LXB_TAG_INPUT || t == LXB_TAG_TEXTAREA || t == LXB_TAG_BUTTON)
                && !in_skipped_subtree(n, base)) {
                lxb_dom_element_t *el = lxb_dom_interface_element(n);

                const char *unused_href = NULL;
                size_t unused_hl = 0;
                const lxb_dom_node_t *block = NULL;
                int heading = 0, unused_fg = -1;
                resolve_context(n, base, &unused_href, &unused_hl, &block, &heading, &unused_fg);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                int fidx = form_for(&forms, n, base);
                const char *action = (fidx >= 0) ? forms.recs[fidx].action : NULL;
                int method = (fidx >= 0) ? forms.recs[fidx].method : PV_METHOD_GET;

                pv_input_type itype;
                char *label = NULL, *name = NULL, *value = NULL;
                if (describe_control(el, t, n, &itype, &label, &name, &value) != 0) {
                    free(label); free(name); free(value);
                    rc = PV_ERR_OOM; goto cleanup;
                }
                pv_status st = pv_append_input(v, heading, brk, itype, label,
                                               name, value, action, fidx, method);
                free(label); free(name); free(value);
                if (st != PV_OK) { rc = st; goto cleanup; }
                continue;
            }

            if (t == LXB_TAG_IMG && !in_skipped_subtree(n, base)) {
                lxb_dom_element_t *el = lxb_dom_interface_element(n);
                size_t sl = 0;
                const lxb_char_t *src =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"src", 3, &sl);
                if (src == NULL || sl == 0) continue; /* no source: nothing to show */

                size_t al = 0;
                const lxb_char_t *alt =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"alt", 3, &al);
                size_t wl = 0, hl = 0;
                const lxb_char_t *ws =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"width", 5, &wl);
                const lxb_char_t *hs =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"height", 6, &hl);
                int iw = parse_dim(ws, wl);
                int ih = parse_dim(hs, hl);

                const char *unused_href = NULL;
                size_t unused_hl = 0;
                const lxb_dom_node_t *block = NULL;
                int heading = 0, unused_fg = -1;
                resolve_context(n, base, &unused_href, &unused_hl, &block, &heading, &unused_fg);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                char *src_dup = dup_n((const char *)src, sl);
                if (src_dup == NULL) { rc = PV_ERR_OOM; goto cleanup; }
                char *alt_dup = (alt != NULL) ? collapse_ws((const char *)alt, al) : dup_n("", 0);
                if (alt_dup == NULL) { free(src_dup); rc = PV_ERR_OOM; goto cleanup; }

                pv_status st = pv_append_image(v, heading, brk, alt_dup, src_dup, iw, ih);
                free(src_dup);
                free(alt_dup);
                if (st != PV_OK) { rc = st; goto cleanup; }
            }
            continue;
        }
        if (n->type != LXB_DOM_NODE_TYPE_TEXT) continue;
        if (in_skipped_subtree(n, base)) continue;

        lxb_dom_text_t *txt = lxb_dom_interface_text(n);
        const char *raw = (const char *)txt->char_data.data.data;
        size_t raw_len = txt->char_data.data.length;
        if (raw == NULL || raw_len == 0) continue;

        char *collapsed = collapse_ws(raw, raw_len);
        if (collapsed == NULL) { rc = PV_ERR_OOM; goto cleanup; }
        if (collapsed[0] == '\0') { free(collapsed); continue; }

        const char *href = NULL;
        size_t href_len = 0;
        const lxb_dom_node_t *block = NULL;
        int heading = 0, fg = -1;
        resolve_context(n, base, &href, &href_len, &block, &heading, &fg);

        int brk = pending_break || (block != prev_block);
        pending_break = 0;
        prev_block = block;

        char *href_dup = NULL;
        if (href != NULL) {
            href_dup = dup_n(href, href_len);
            if (href_dup == NULL) { free(collapsed); rc = PV_ERR_OOM; goto cleanup; }
        }

        pv_status st = pv_append(v, href_dup != NULL ? PV_LINK : PV_TEXT,
                                 heading, brk, collapsed, href_dup);
        free(collapsed);
        free(href_dup);
        if (st != PV_OK) { rc = st; goto cleanup; }
        pv_set_color(v, fg);
    }

    *out = v;
    forms_free(&forms);
    return PV_OK;

cleanup:
    forms_free(&forms);
    pv_free(v);
    return rc;
}
