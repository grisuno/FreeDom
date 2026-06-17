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
    return PV_OK;
}

void pv_free(pv_view *v) {
    if (v == NULL) return;
    for (size_t i = 0; i < v->count; ++i) {
        free(v->runs[i].text);
        free(v->runs[i].href);
        free(v->runs[i].src);
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
    return t == LXB_TAG_SCRIPT || t == LXB_TAG_STYLE || t == LXB_TAG_HEAD
        || t == LXB_TAG_TITLE  || t == LXB_TAG_NOSCRIPT;
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

/* Resolves the inline context of a text node: nearest <a href>, nearest heading
 * level, and nearest block-level ancestor (defaults to base). */
static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                            const char **href, size_t *href_len,
                            const lxb_dom_node_t **block, int *heading) {
    *href = NULL; *href_len = 0; *block = base; *heading = 0;
    int got_link = 0, got_block = 0, got_heading = 0;

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

    for (lxb_dom_node_t *n = base; n != NULL; n = node_next(n, base)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(n);
            if (t == LXB_TAG_BR || t == LXB_TAG_HR) { pending_break = 1; continue; }
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
                int heading = 0;
                resolve_context(n, base, &unused_href, &unused_hl, &block, &heading);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                char *src_dup = dup_n((const char *)src, sl);
                if (src_dup == NULL) { pv_free(v); return PV_ERR_OOM; }
                char *alt_dup = (alt != NULL) ? collapse_ws((const char *)alt, al) : dup_n("", 0);
                if (alt_dup == NULL) { free(src_dup); pv_free(v); return PV_ERR_OOM; }

                pv_status st = pv_append_image(v, heading, brk, alt_dup, src_dup, iw, ih);
                free(src_dup);
                free(alt_dup);
                if (st != PV_OK) { pv_free(v); return st; }
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
        if (collapsed == NULL) { pv_free(v); return PV_ERR_OOM; }
        if (collapsed[0] == '\0') { free(collapsed); continue; }

        const char *href = NULL;
        size_t href_len = 0;
        const lxb_dom_node_t *block = NULL;
        int heading = 0;
        resolve_context(n, base, &href, &href_len, &block, &heading);

        int brk = pending_break || (block != prev_block);
        pending_break = 0;
        prev_block = block;

        char *href_dup = NULL;
        if (href != NULL) {
            href_dup = dup_n(href, href_len);
            if (href_dup == NULL) { free(collapsed); pv_free(v); return PV_ERR_OOM; }
        }

        pv_status st = pv_append(v, href_dup != NULL ? PV_LINK : PV_TEXT,
                                 heading, brk, collapsed, href_dup);
        free(collapsed);
        free(href_dup);
        if (st != PV_OK) { pv_free(v); return st; }
    }

    *out = v;
    return PV_OK;
}
