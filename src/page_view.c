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
#include "box_style.h"
#include "css.h"
#include "css_color.h"
#include "flex_layout.h"
#include "html_parse.h"

#include <stdint.h>
#include <stdio.h>
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
 * so page_view stays self-contained. Valid UTF-8 passes through; a byte that is
 * not part of a valid sequence is reinterpreted as Windows-1252 (a superset of
 * Latin-1) and re-emitted as UTF-8, recovering accents instead of dropping to '?'.
 * Output may be longer than the input (a single byte >=0x80 -> up to 3 UTF-8
 * bytes), so the caller sizes for 3x. --- */

static size_t utf8_seq_len(unsigned char c) {
    if (c < 0x80) return 1;
    if (c >= 0xC2 && c <= 0xDF) return 2;
    if (c >= 0xE0 && c <= 0xEF) return 3;
    if (c >= 0xF0 && c <= 0xF4) return 4;
    return 0;
}

/* Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0..
 * 0xFF map identically to Latin-1 (code point == byte). 0x80..0x9F carry the
 * Windows-1252 printable glyphs; the five undefined positions return 0 (the caller
 * emits '?'). */
static unsigned int cp1252_to_ucs(unsigned char c) {
    static const unsigned short hi[32] = {
        0x20AC, 0x0000, 0x201A, 0x0192, 0x201E, 0x2026, 0x2020, 0x2021,
        0x02C6, 0x2030, 0x0160, 0x2039, 0x0152, 0x0000, 0x017D, 0x0000,
        0x0000, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
        0x02DC, 0x2122, 0x0161, 0x203A, 0x0153, 0x0000, 0x017E, 0x0178
    };
    if (c < 0x80) return c;
    if (c < 0xA0) return hi[c - 0x80];
    return c; /* 0xA0..0xFF: Latin-1 == Unicode code point */
}

/* Encodes a BMP scalar (<= 0xFFFF, which covers all Windows-1252 targets) as
 * UTF-8 into out (up to 3 bytes); returns the byte count written. */
static size_t utf8_encode(unsigned int cp, char *out) {
    if (cp < 0x80) { out[0] = (char)cp; return 1; }
    if (cp < 0x800) {
        out[0] = (char)(0xC0 | (cp >> 6));
        out[1] = (char)(0x80 | (cp & 0x3F));
        return 2;
    }
    out[0] = (char)(0xE0 | (cp >> 12));
    out[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
    out[2] = (char)(0x80 | (cp & 0x3F));
    return 3;
}

static char *utf8_sanitized_dup(const char *s) {
    size_t n = strlen(s);
    char *d = (char *)malloc(3 * n + 1); /* worst case: every byte -> 3-byte UTF-8 */
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
            /* Not valid UTF-8: treat the lone byte as Windows-1252. Undefined
             * positions (cp == 0) keep the legacy '?' fallback. */
            unsigned int cp = cp1252_to_ucs(c);
            if (cp == 0) d[o++] = '?';
            else o += utf8_encode(cp, d + o);
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

/* Box engine (Hito 23b-8 Step A): the no-op defaults for the box identity/decoration
 * fields, shared by all three append helpers so a run with no author box renders
 * identically. Sentinels mirror the css module (PV_LEN_UNSET width/radius, -1 color,
 * 0 the rest). */
static void run_init_box_defaults(pv_run *r) {
    r->block_id = -1;
    r->box_sizing = 0;
    r->pad_t = r->pad_r = r->pad_b = r->pad_l = 0;
    r->bord_tw = r->bord_rw = r->bord_bw = r->bord_lw = PV_LEN_UNSET;
    r->bord_ts = r->bord_rs = r->bord_bs = r->bord_ls = 0;
    r->bord_tc = r->bord_rc = r->bord_bc = r->bord_lc = -1;
    r->border_radius = PV_LEN_UNSET;
    r->bsh_dx = r->bsh_dy = r->bsh_blur = r->bsh_spread = 0;
    r->bsh_color = -1;
    r->bsh_inset = -1;
    r->outline_w = PV_LEN_UNSET;
    r->outline_style = 0;
    r->outline_color = -1;
}

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
    r->bold = 0;
    r->italic = 0;
    r->indent = 0;
    r->block_break = block_break;
    r->text = t;
    r->href = h;
    r->src = NULL;
    r->img_w = -1;
    r->img_h = -1;
    r->fg_rgb = -1;
    r->bg_rgb = -1;
    r->text_align = 0;
    r->font_scale = 0;
    r->line_scale = 0;
    r->text_decoration = -1;
    r->font_family = 0;
    r->text_transform = 0;
    r->letter_spacing = PV_LEN_UNSET;
    r->word_spacing = PV_LEN_UNSET;
    r->shadow_dx = 0;
    r->shadow_dy = 0;
    r->shadow_color = -1;
    r->opacity = -1;
    r->valign = 0;
    r->text_indent = PV_LEN_UNSET;
    r->white_space = 0;
    r->cont_id = -1;
    r->cont_display = 0;
    r->cont_gap = 0;
    r->cont_justify = 0;
    r->cont_cols = 0;
    r->box_l = 0;
    r->box_r = 0;
    r->box_w = 0;
    r->box_center = 0;
    r->box_mt = PV_LEN_UNSET;
    r->box_mb = PV_LEN_UNSET;
    run_init_box_defaults(r);
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
    r->bold = 0;
    r->italic = 0;
    r->indent = 0;
    r->block_break = block_break;
    r->text = t;
    r->href = NULL;
    r->src = s;
    r->img_w = w;
    r->img_h = h;
    r->fg_rgb = -1;
    r->bg_rgb = -1;
    r->text_align = 0;
    r->font_scale = 0;
    r->line_scale = 0;
    r->text_decoration = -1;
    r->font_family = 0;
    r->text_transform = 0;
    r->letter_spacing = PV_LEN_UNSET;
    r->word_spacing = PV_LEN_UNSET;
    r->shadow_dx = 0;
    r->shadow_dy = 0;
    r->shadow_color = -1;
    r->opacity = -1;
    r->valign = 0;
    r->text_indent = PV_LEN_UNSET;
    r->white_space = 0;
    r->cont_id = -1;
    r->cont_display = 0;
    r->cont_gap = 0;
    r->cont_justify = 0;
    r->cont_cols = 0;
    r->box_l = 0;
    r->box_r = 0;
    r->box_w = 0;
    r->box_center = 0;
    r->box_mt = PV_LEN_UNSET;
    r->box_mb = PV_LEN_UNSET;
    run_init_box_defaults(r);
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
    r->bold = 0;
    r->italic = 0;
    r->indent = 0;
    r->block_break = block_break;
    r->text = t;
    r->href = ac;
    r->src = NULL;
    r->img_w = -1;
    r->img_h = -1;
    r->fg_rgb = -1;
    r->bg_rgb = -1;
    r->text_align = 0;
    r->font_scale = 0;
    r->line_scale = 0;
    r->text_decoration = -1;
    r->font_family = 0;
    r->text_transform = 0;
    r->letter_spacing = PV_LEN_UNSET;
    r->word_spacing = PV_LEN_UNSET;
    r->shadow_dx = 0;
    r->shadow_dy = 0;
    r->shadow_color = -1;
    r->opacity = -1;
    r->valign = 0;
    r->text_indent = PV_LEN_UNSET;
    r->white_space = 0;
    r->cont_id = -1;
    r->cont_display = 0;
    r->cont_gap = 0;
    r->cont_justify = 0;
    r->cont_cols = 0;
    r->box_l = 0;
    r->box_r = 0;
    r->box_w = 0;
    r->box_center = 0;
    r->box_mt = PV_LEN_UNSET;
    r->box_mb = PV_LEN_UNSET;
    run_init_box_defaults(r);
    r->input_type = (int)input_type;
    r->name = nm;
    r->value = vl;
    r->form_id = form_id;
    r->form_method = method;
    return PV_OK;
}

void pv_set_emphasis(pv_view *v, int bold, int italic) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->bold = bold ? 1 : 0;
    r->italic = italic ? 1 : 0;
}

void pv_set_indent(pv_view *v, int indent) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].indent = (indent > 0) ? indent : 0;
}

void pv_set_color(pv_view *v, int fg_rgb) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].fg_rgb = fg_rgb;
}

void pv_set_bgcolor(pv_view *v, int bg_rgb) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].bg_rgb = bg_rgb;
}

void pv_set_text_style(pv_view *v, int text_align, int font_scale, int line_scale,
                       int text_decoration) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->text_align = text_align;
    r->font_scale = font_scale;
    r->line_scale = line_scale;
    r->text_decoration = text_decoration;
}

void pv_set_text_ext(pv_view *v, int font_family, int text_transform,
                     int letter_spacing, int word_spacing, int shadow_dx, int shadow_dy,
                     int shadow_color, int opacity, int valign, int text_indent,
                     int white_space) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->font_family = font_family;
    r->text_transform = text_transform;
    r->letter_spacing = letter_spacing;
    r->word_spacing = word_spacing;
    r->shadow_dx = shadow_dx;
    r->shadow_dy = shadow_dy;
    r->shadow_color = shadow_color;
    r->opacity = opacity;
    r->valign = valign;
    r->text_indent = text_indent;
    r->white_space = white_space;
}

void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_gap, int cont_justify, int cont_cols) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->cont_id = cont_id;
    r->cont_display = cont_display;
    r->cont_gap = cont_gap;
    r->cont_justify = cont_justify;
    r->cont_cols = cont_cols;
}

void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int box_mt, int box_mb) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->box_l = box_l;
    r->box_r = box_r;
    r->box_w = box_w;
    r->box_center = box_center;
    r->box_mt = box_mt;
    r->box_mb = box_mb;
}

void pv_set_block_id(pv_view *v, int block_id) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].block_id = block_id;
}

void pv_set_box_border(pv_view *v, int tw, int rw, int bw, int lw,
                       int ts, int rs, int bs, int ls,
                       int tc, int rc, int bc, int lc, int radius) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->bord_tw = tw; r->bord_rw = rw; r->bord_bw = bw; r->bord_lw = lw;
    r->bord_ts = ts; r->bord_rs = rs; r->bord_bs = bs; r->bord_ls = ls;
    r->bord_tc = tc; r->bord_rc = rc; r->bord_bc = bc; r->bord_lc = lc;
    r->border_radius = radius;
}

void pv_set_boxdeco(pv_view *v, int box_sizing, int pad_t, int pad_r, int pad_b,
                    int pad_l, int bsh_dx, int bsh_dy, int bsh_blur, int bsh_spread,
                    int bsh_color, int bsh_inset, int outline_w, int outline_style,
                    int outline_color) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->box_sizing = box_sizing;
    r->pad_t = pad_t; r->pad_r = pad_r; r->pad_b = pad_b; r->pad_l = pad_l;
    r->bsh_dx = bsh_dx; r->bsh_dy = bsh_dy; r->bsh_blur = bsh_blur;
    r->bsh_spread = bsh_spread; r->bsh_color = bsh_color; r->bsh_inset = bsh_inset;
    r->outline_w = outline_w; r->outline_style = outline_style;
    r->outline_color = outline_color;
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
     * PV_INPUT, not as page text; suppress their inner text from the normal walk.
     * NOSCRIPT is handled separately (in_skipped_subtree): its fallback content is
     * shown when JS is disabled and hidden when JS runs. */
    return t == LXB_TAG_SCRIPT || t == LXB_TAG_STYLE || t == LXB_TAG_HEAD
        || t == LXB_TAG_TITLE
        || t == LXB_TAG_TEXTAREA || t == LXB_TAG_SELECT || t == LXB_TAG_BUTTON;
}

static lxb_tag_id_t node_tag(const lxb_dom_node_t *n) {
    return lxb_dom_element_tag_id(lxb_dom_interface_element((lxb_dom_node_t *)n));
}

/* Nonzero if any ancestor up to base is a non-rendered container. When js_enabled,
 * a <noscript> ancestor also suppresses content (the script would run, so the
 * fallback is hidden); when JS is off, <noscript> content IS rendered (a no-JS
 * browser shows the fallback). */
static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                              int js_enabled) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(p);
            if (is_skipped_tag(t)) return 1;
            if (t == LXB_TAG_NOSCRIPT && js_enabled) return 1;
        }
        if (p == base) break;
    }
    return 0;
}

/* Largest color token value extracted from markup. A longer value is not a valid
 * color and is ignored (fail closed). */
#define PV_COLOR_TOKEN_MAX 64u

/* Bounds for the element selector inputs handed to css_resolve (anti-DoS; an
 * over-long token simply does not match, which fails closed). */
#define PV_CSS_TAG_MAX     64u
#define PV_CSS_ID_MAX      128u
#define PV_CSS_CLASS_BUF   256u
#define PV_CSS_MAX_CLASSES 16
#define PV_CSS_MAX_ATTRS   16     /* attributes captured per element for [attr] selectors */
#define PV_CSS_ATTR_BUF    512u   /* bytes for all captured attr names+values of one element */

/* Legacy <font color> attribute as a packed 0xRRGGBB, or -1. Not CSS, so it is a
 * separate fallback the cascade consults only when no `color` declaration won. */
static int font_color_attr(lxb_dom_element_t *el) {
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
    return -1;
}

/* Max ancestors carried for combinator matching. A selector reaching past this is
 * not matched (fail closed); 32 is far beyond any real `a b c d` chain. */
#define PV_CSS_CHAIN_MAX 32

/* One element's selector inputs (tag/id/classes) plus its css_element view, with
 * backing storage so the css_element pointers stay valid for the chain's lifetime. */
typedef struct pv_css_node {
    char        tag[PV_CSS_TAG_MAX];
    char        idbuf[PV_CSS_ID_MAX];
    char        clsbuf[PV_CSS_CLASS_BUF];
    const char *clsptr[PV_CSS_MAX_CLASSES];
    char        attrbuf[PV_CSS_ATTR_BUF];
    css_attr    attrs[PV_CSS_MAX_ATTRS];
    css_element el;
} pv_css_node;

/* Fills *node with element e's tag/id/class tokens (no style=, no parent link yet).
 * Over-long tokens are simply absent, which fails closed (does not match). */
static void fill_css_node(lxb_dom_element_t *e, pv_css_node *node) {
    size_t nl = 0;
    const lxb_char_t *ln = lxb_dom_element_local_name(e, &nl);
    size_t tn = (ln != NULL && nl > 0 && nl < sizeof node->tag) ? nl : 0;
    if (tn > 0) memcpy(node->tag, ln, tn);
    node->tag[tn] = '\0';

    node->el.id = NULL;
    size_t il = 0;
    const lxb_char_t *idv =
        lxb_dom_element_get_attribute(e, (const lxb_char_t *)"id", 2, &il);
    if (idv != NULL && il > 0 && il < sizeof node->idbuf) {
        memcpy(node->idbuf, idv, il);
        node->idbuf[il] = '\0';
        node->el.id = node->idbuf;
    }

    size_t nc = 0, cl = 0;
    const lxb_char_t *clv =
        lxb_dom_element_get_attribute(e, (const lxb_char_t *)"class", 5, &cl);
    if (clv != NULL && cl > 0 && cl < sizeof node->clsbuf) {
        memcpy(node->clsbuf, clv, cl);
        node->clsbuf[cl] = '\0';
        size_t i = 0;
        while (i < cl && nc < PV_CSS_MAX_CLASSES) {
            while (i < cl && (node->clsbuf[i] == ' ' || node->clsbuf[i] == '\t' ||
                              node->clsbuf[i] == '\n' || node->clsbuf[i] == '\r' ||
                              node->clsbuf[i] == '\f'))
                node->clsbuf[i++] = '\0';
            if (i >= cl) break;
            node->clsptr[nc++] = &node->clsbuf[i];
            while (i < cl && !(node->clsbuf[i] == ' ' || node->clsbuf[i] == '\t' ||
                               node->clsbuf[i] == '\n' || node->clsbuf[i] == '\r' ||
                               node->clsbuf[i] == '\f'))
                ++i;
        }
    }

    /* Capture all attributes (name lowercased) for [attr] selectors, packed into one
     * bounded buffer. Over-long sets are truncated (anti-DoS): a missing attribute just
     * fails to match (fail closed). id/class/style are attributes too, so [id=...] etc.
     * work alongside the dedicated #id/.class paths. */
    size_t nat = 0, off = 0;
    for (lxb_dom_attr_t *at = lxb_dom_element_first_attribute(e);
         at != NULL && nat < PV_CSS_MAX_ATTRS;
         at = lxb_dom_element_next_attribute(at)) {
        size_t anl = 0, avl = 0;
        const lxb_char_t *an = lxb_dom_attr_local_name(at, &anl);
        const lxb_char_t *av = lxb_dom_attr_value(at, &avl);
        if (an == NULL || anl == 0) continue;
        if (off + anl + 1 + avl + 1 > sizeof node->attrbuf) break;  /* buffer full */
        char *np = node->attrbuf + off;
        for (size_t k = 0; k < anl; ++k) {
            char ch = (char)an[k];
            np[k] = (ch >= 'A' && ch <= 'Z') ? (char)(ch + 32) : ch;
        }
        np[anl] = '\0';
        off += anl + 1;
        char *vp = node->attrbuf + off;
        if (av != NULL && avl > 0) memcpy(vp, av, avl);
        vp[avl] = '\0';
        off += avl + 1;
        node->attrs[nat].name = np;
        node->attrs[nat].value = vp;
        ++nat;
    }

    node->el.tag = (tn > 0) ? node->tag : NULL;
    node->el.classes = node->clsptr;
    node->el.nclasses = nc;
    node->el.attrs = (nat > 0) ? node->attrs : NULL;
    node->el.nattrs = nat;
    node->el.parent = NULL;  /* linked by the caller once the chain is built */
}

/* Resolves the author presentation for one element from the document <style> sheet
 * plus its own inline style= (inline wins; the css module does the cascade). The
 * element and its ancestor chain (bounded) become the selector match inputs, so
 * descendant/child combinators (`div p`, `nav > a`) resolve. Pure (no fetch, no
 * execution): the css module drops url() and @-rules. */
static css_style element_css_style(lxb_dom_element_t *el, const css_sheet *sheet) {
    pv_css_node chain[PV_CSS_CHAIN_MAX];
    int n = 0;
    for (lxb_dom_node_t *p = (lxb_dom_node_t *)el;
         p != NULL && p->type == LXB_DOM_NODE_TYPE_ELEMENT && n < PV_CSS_CHAIN_MAX;
         p = p->parent) {
        fill_css_node(lxb_dom_interface_element(p), &chain[n]);
        ++n;
    }
    for (int i = 0; i < n; ++i)
        chain[i].el.parent = (i + 1 < n) ? &chain[i + 1].el : NULL;

    /* Inline style= applies to the subject element only. */
    size_t sl = 0;
    const lxb_char_t *st =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)"style", 5, &sl);

    return css_resolve_el(sheet, (n > 0) ? &chain[0].el : NULL,
                          (const char *)st, sl);
}

/* --- author flex/grid container layout: structure, not author styling. render_doc
 * applies it ALWAYS, decoupled from caps.css (doctrine "Layout != estilo de autor");
 * only author colors/text-align/font-size stay gated. The display and its params
 * (gap/justify/columns) come from the css cascade (<style> + inline), resolved by
 * element_css_style like the colors. --- */

#define PV_MAX_CONTAINERS   256u
#define PV_MAX_GRID_COLS    64

/* Nearest-container info attached to a run. */
typedef struct pv_cont_info {
    int id, display, gap, justify, cols;
} pv_cont_info;

/* Author box model resolved for a run: horizontal placement (l/r insets, w cap,
 * centered) from the nearest block ancestor that declares a box, plus the leaf
 * block's own vertical-margin override (mt/mb, or PV_LEN_UNSET). */
typedef struct pv_box_info {
    int l, r, w, center, mt, mb;
} pv_box_info;

/* Author text-presentation extensions resolved for a run (Hito 23b-6): each from the
 * nearest ancestor that sets it (they inherit in CSS). list_style drives the <li>
 * marker (structural); the rest are gated by caps.css downstream. Defaults mirror the
 * pv_run / css_style "unset" sentinels. */
typedef struct pv_text_ext {
    int font_family, text_transform, letter_spacing, word_spacing;
    int shadow_dx, shadow_dy, shadow_color;
    int opacity, valign, text_indent, white_space;
    int list_style;
} pv_text_ext;

/* Initialises an ext to "unset" (no author text extension applied). */
static void pv_text_ext_reset(pv_text_ext *e) {
    e->font_family = 0; e->text_transform = 0;
    e->letter_spacing = PV_LEN_UNSET; e->word_spacing = PV_LEN_UNSET;
    e->shadow_dx = 0; e->shadow_dy = 0; e->shadow_color = -1;
    e->opacity = -1; e->valign = 0; e->text_indent = PV_LEN_UNSET;
    e->white_space = 0; e->list_style = 0;
}

/* Merges one ancestor's resolved css_style into ext, nearest ancestor first (a field
 * already set is not overwritten — keeps the nearest, matching inheritance). */
static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs) {
    if (e->font_family == 0 && cs->font_family != CSS_FF_UNSET) e->font_family = cs->font_family;
    if (e->text_transform == 0 && cs->text_transform != CSS_TT_UNSET) e->text_transform = cs->text_transform;
    if (e->letter_spacing == PV_LEN_UNSET && cs->letter_spacing != CSS_LEN_UNSET)
        e->letter_spacing = cs->letter_spacing;
    if (e->word_spacing == PV_LEN_UNSET && cs->word_spacing != CSS_LEN_UNSET)
        e->word_spacing = cs->word_spacing;
    if (e->shadow_color == -1 && cs->shadow_color != -1) {
        e->shadow_dx = cs->shadow_dx; e->shadow_dy = cs->shadow_dy;
        e->shadow_color = cs->shadow_color;
    }
    if (e->opacity == -1 && cs->opacity != -1) e->opacity = cs->opacity;
    if (e->valign == 0 && cs->valign != CSS_VA_UNSET) e->valign = cs->valign;
    if (e->text_indent == PV_LEN_UNSET && cs->text_indent != CSS_LEN_UNSET)
        e->text_indent = cs->text_indent;
    if (e->white_space == 0 && cs->white_space != CSS_WS_UNSET) e->white_space = cs->white_space;
    if (e->list_style == 0 && cs->list_style != CSS_LS_UNSET) e->list_style = cs->list_style;
}

/* True if the resolved style declares any HORIZONTAL box property. */
static int css_has_hbox(const css_style *cs) {
    return cs->margin_left != CSS_LEN_UNSET || cs->margin_right != CSS_LEN_UNSET ||
           cs->pad_left   != CSS_LEN_UNSET || cs->pad_right   != CSS_LEN_UNSET ||
           cs->width != CSS_LEN_UNSET || cs->max_width != CSS_LEN_UNSET;
}

/* Pre-resolves the horizontal box (px) into a run's wire fields: l/r insets =
 * padding + non-auto margin of each side (clamped >= 0); w = the tightest of
 * width/max-width (0 = none); center = margin: 0 auto with a width cap. */
static void css_hbox_resolve(const css_style *cs, pv_box_info *out) {
    int ml = cs->margin_left, mr = cs->margin_right;
    int pl = (cs->pad_left  != CSS_LEN_UNSET) ? cs->pad_left  : 0;
    int pr = (cs->pad_right != CSS_LEN_UNSET) ? cs->pad_right : 0;
    int l = pl + ((ml != CSS_LEN_UNSET && ml != CSS_LEN_AUTO) ? ml : 0);
    int r = pr + ((mr != CSS_LEN_UNSET && mr != CSS_LEN_AUTO) ? mr : 0);
    int w = CSS_LEN_UNSET;
    if (cs->width != CSS_LEN_UNSET) w = cs->width;
    if (cs->max_width != CSS_LEN_UNSET && (w == CSS_LEN_UNSET || cs->max_width < w))
        w = cs->max_width;
    out->l = (l > 0) ? l : 0;
    out->r = (r > 0) ? r : 0;
    out->w = (w != CSS_LEN_UNSET && w > 0) ? w : 0;
    out->center = (ml == CSS_LEN_AUTO && mr == CSS_LEN_AUTO && out->w > 0) ? 1 : 0;
}

/* Box engine (Hito 23b-8 Step A): identity + decoration resolved for a run from the
 * nearest block-level ancestor that declares a box. Sentinels mirror pv_run. */
typedef struct pv_box_deco {
    int block_id;
    int box_sizing;
    int pad_t, pad_r, pad_b, pad_l;
    int bord_tw, bord_rw, bord_bw, bord_lw;
    int bord_ts, bord_rs, bord_bs, bord_ls;
    int bord_tc, bord_rc, bord_bc, bord_lc;
    int border_radius;
    int bsh_dx, bsh_dy, bsh_blur, bsh_spread, bsh_color, bsh_inset;
    int outline_w, outline_style, outline_color;
} pv_box_deco;

static void pv_box_deco_reset(pv_box_deco *d) {
    d->block_id = -1;
    d->box_sizing = 0;
    d->pad_t = d->pad_r = d->pad_b = d->pad_l = 0;
    d->bord_tw = d->bord_rw = d->bord_bw = d->bord_lw = PV_LEN_UNSET;
    d->bord_ts = d->bord_rs = d->bord_bs = d->bord_ls = 0;
    d->bord_tc = d->bord_rc = d->bord_bc = d->bord_lc = -1;
    d->border_radius = PV_LEN_UNSET;
    d->bsh_dx = d->bsh_dy = d->bsh_blur = d->bsh_spread = 0;
    d->bsh_color = -1; d->bsh_inset = -1;
    d->outline_w = PV_LEN_UNSET; d->outline_style = 0; d->outline_color = -1;
}

/* True if the resolved style declares any paintable box (border/padding/radius/
 * shadow/outline). box-sizing alone is not a box (it only matters with a width). */
static int css_has_boxdeco(const css_style *cs) {
    return cs->pad_top != CSS_LEN_UNSET || cs->pad_right != CSS_LEN_UNSET ||
           cs->pad_bottom != CSS_LEN_UNSET || cs->pad_left != CSS_LEN_UNSET ||
           cs->border_top_width != CSS_LEN_UNSET || cs->border_right_width != CSS_LEN_UNSET ||
           cs->border_bottom_width != CSS_LEN_UNSET || cs->border_left_width != CSS_LEN_UNSET ||
           cs->border_radius != CSS_LEN_UNSET || cs->box_shadow_color != -1 ||
           cs->outline_width != CSS_LEN_UNSET;
}

/* Copies the box-decoration values from a resolved style into d, stamping block_id.
 * Padding unset -> 0 (geometry default); the rest keep css's sentinels (the painter
 * reads them). */
static void css_boxdeco_resolve(const css_style *cs, int block_id, pv_box_deco *d) {
    d->block_id = block_id;
    d->box_sizing = cs->box_sizing;
    d->pad_t = (cs->pad_top    != CSS_LEN_UNSET) ? cs->pad_top    : 0;
    d->pad_r = (cs->pad_right  != CSS_LEN_UNSET) ? cs->pad_right  : 0;
    d->pad_b = (cs->pad_bottom != CSS_LEN_UNSET) ? cs->pad_bottom : 0;
    d->pad_l = (cs->pad_left   != CSS_LEN_UNSET) ? cs->pad_left   : 0;
    d->bord_tw = cs->border_top_width;    d->bord_rw = cs->border_right_width;
    d->bord_bw = cs->border_bottom_width; d->bord_lw = cs->border_left_width;
    d->bord_ts = cs->border_top_style;    d->bord_rs = cs->border_right_style;
    d->bord_bs = cs->border_bottom_style; d->bord_ls = cs->border_left_style;
    d->bord_tc = cs->border_top_color;    d->bord_rc = cs->border_right_color;
    d->bord_bc = cs->border_bottom_color; d->bord_lc = cs->border_left_color;
    d->border_radius = cs->border_radius;
    d->bsh_dx = cs->shadow2_dx; d->bsh_dy = cs->shadow2_dy;
    d->bsh_blur = cs->shadow2_blur; d->bsh_spread = cs->shadow2_spread;
    d->bsh_color = cs->box_shadow_color; d->bsh_inset = cs->box_shadow_inset;
    d->outline_w = cs->outline_width; d->outline_style = cs->outline_style;
    d->outline_color = cs->outline_color;
}

/* Document-order registry of flex/grid container nodes, so the runs of one
 * container share a stable id. */
typedef struct pv_container_reg {
    const lxb_dom_node_t *node[PV_MAX_CONTAINERS];
    size_t count;
} pv_container_reg;

/* Id of node in reg, registering it on first sight. -1 when reg is full. */
static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node) {
    for (size_t i = 0; i < reg->count; ++i)
        if (reg->node[i] == node) return (int)i;
    if (reg->count >= PV_MAX_CONTAINERS) return -1;
    reg->node[reg->count] = node;
    return (int)reg->count++;
}

/* Maps a css_justify (resolved by the css cascade) to a flex_layout fx_justify.
 * Unset / start / unknown all fall to FX_JUSTIFY_START (the default). */
static int css_to_fx_justify(css_justify j) {
    switch (j) {
        case CSS_JUSTIFY_END:           return FX_JUSTIFY_END;
        case CSS_JUSTIFY_CENTER:        return FX_JUSTIFY_CENTER;
        case CSS_JUSTIFY_SPACE_BETWEEN: return FX_JUSTIFY_SPACE_BETWEEN;
        case CSS_JUSTIFY_SPACE_AROUND:  return FX_JUSTIFY_SPACE_AROUND;
        case CSS_JUSTIFY_SPACE_EVENLY:  return FX_JUSTIFY_SPACE_EVENLY;
        case CSS_JUSTIFY_START:
        case CSS_JUSTIFY_UNSET:
        default:                        return FX_JUSTIFY_START;
    }
}

/* Inline emphasis carried by a tag: bold from <b>/<strong>/<th>, italic from
 * <i>/<em>. <th> is a header cell, conventionally bold. */
static int is_bold_tag(lxb_tag_id_t t) {
    return t == LXB_TAG_B || t == LXB_TAG_STRONG || t == LXB_TAG_TH;
}
static int is_italic_tag(lxb_tag_id_t t) {
    return t == LXB_TAG_I || t == LXB_TAG_EM;
}

/* Resolves the inline context of a text node: nearest <a href>, nearest heading
 * level, nearest block-level ancestor (defaults to base), the inherited author
 * color (nearest ancestor that sets one, packed 0xRRGGBB, or -1), the author
 * background (nearest ancestor that sets one), the inline emphasis (bold/italic),
 * the author text-align (*align, a css_align) and font-size (*font_scale, percent),
 * and the list context: the nearest <li> ancestor (*li, or NULL), the list nesting
 * depth (*list_depth = count of <ul>/<ol> ancestors), and whether the innermost
 * list is ordered (*ordered).
 *
 * Author presentation now comes from the css module: for each ancestor element its
 * computed css_style (document <style> sheet + that element's inline style=, inline
 * winning) is merged into the inheriting fields, nearest ancestor first. Inline
 * emphasis from tags (<b>/<em>/...) still applies; an explicit CSS font-weight /
 * font-style on the nearest ancestor that sets it takes precedence over the tag
 * default. The <font color> attribute is a legacy fallback when no CSS color won. */
static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                            const css_sheet *sheet,
                            const char **href, size_t *href_len,
                            const lxb_dom_node_t **block, int *heading,
                            int *fg, int *bg, int *bold, int *italic,
                            int *align, int *font_scale, int *line_scale, int *deco,
                            const lxb_dom_node_t **li, int *list_depth, int *ordered,
                            pv_container_reg *reg, pv_cont_info *cont, pv_box_info *box,
                            pv_text_ext *ext, pv_container_reg *block_reg,
                            pv_box_deco *deco_out) {
    *href = NULL; *href_len = 0; *block = base; *heading = 0; *fg = -1; *bg = -1;
    *bold = 0; *italic = 0; *align = CSS_ALIGN_UNSET; *font_scale = 0; *line_scale = 0;
    *deco = -1;
    *li = NULL; *list_depth = 0; *ordered = 0;
    cont->id = -1; cont->display = 0; cont->gap = 0;
    cont->justify = FX_JUSTIFY_START; cont->cols = 0;
    box->l = 0; box->r = 0; box->w = 0; box->center = 0;
    box->mt = PV_LEN_UNSET; box->mb = PV_LEN_UNSET;
    pv_text_ext_reset(ext);
    pv_box_deco_reset(deco_out);
    int got_link = 0, got_block = 0, got_heading = 0, got_color = 0, got_bg = 0, got_cont = 0;
    int got_align = 0, got_fs = 0, got_lh = 0, got_deco = 0, got_hbox = 0, got_boxdeco = 0;
    int got_li = 0, got_list_kind = 0;
    int tag_bold = 0, tag_italic = 0;
    int css_bold = 0, css_italic = 0, got_css_bold = 0, got_css_italic = 0;

    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)p);
            lxb_tag_id_t t = lxb_dom_element_tag_id(el);
            css_style cs = element_css_style(el, sheet);
            pv_text_ext_merge(ext, &cs);

            if (is_bold_tag(t)) tag_bold = 1;
            if (is_italic_tag(t)) tag_italic = 1;
            if (!got_css_bold && cs.bold != -1) { css_bold = cs.bold; got_css_bold = 1; }
            if (!got_css_italic && cs.italic != -1) { css_italic = cs.italic; got_css_italic = 1; }
            if (!got_li && t == LXB_TAG_LI) { *li = p; got_li = 1; }
            if (t == LXB_TAG_UL || t == LXB_TAG_OL) {
                ++(*list_depth);
                if (!got_list_kind) { *ordered = (t == LXB_TAG_OL); got_list_kind = 1; }
            }
            if (!got_link && t == LXB_TAG_A) {
                size_t hl = 0;
                const lxb_char_t *h =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"href", 4, &hl);
                if (h != NULL && hl > 0) { *href = (const char *)h; *href_len = hl; got_link = 1; }
            }
            if (!got_heading) { int lv = heading_level(t); if (lv) { *heading = lv; got_heading = 1; } }
            if (!got_block && is_block_tag(t)) {
                *block = p; got_block = 1;
                /* The leaf block's OWN vertical margins override the UA (a wrapper's
                 * do not, so they are not duplicated across its inner blocks). */
                box->mt = (cs.margin_top != CSS_LEN_UNSET) ? cs.margin_top : PV_LEN_UNSET;
                box->mb = (cs.margin_bottom != CSS_LEN_UNSET) ? cs.margin_bottom : PV_LEN_UNSET;
            }
            /* Horizontal box from the nearest block ancestor that declares one, so a
             * wrapper's max-width/centering/padding reaches all its descendants. */
            if (!got_hbox && is_block_tag(t) && css_has_hbox(&cs)) {
                css_hbox_resolve(&cs, box);
                got_hbox = 1;
            }
            /* Box engine (Hito 23b-8): the nearest block ancestor that declares a
             * paintable box (border/padding/shadow/outline). Its runs share one
             * block_id (document order, separate registry from containers) and carry
             * its decoration. Structure (block_id) + author presentation (decoration);
             * render_doc gates the latter behind caps.css. */
            if (!got_boxdeco && block_reg != NULL && is_block_tag(t) && css_has_boxdeco(&cs)) {
                int bid = container_id(block_reg, p);
                css_boxdeco_resolve(&cs, bid, deco_out);
                got_boxdeco = 1;
            }
            if (!got_color) {
                int c = (cs.color >= 0) ? cs.color
                        : ((t == LXB_TAG_FONT) ? font_color_attr(el) : -1);
                if (c >= 0) { *fg = c; got_color = 1; }
            }
            /* background-color does not inherit in CSS; in this flat model we take
             * the nearest ancestor's so a block's background shows behind its text. */
            if (!got_bg && cs.background >= 0) { *bg = cs.background; got_bg = 1; }
            if (!got_align && cs.text_align != CSS_ALIGN_UNSET) {
                *align = (int)cs.text_align; got_align = 1;
            }
            if (!got_fs && cs.font_scale != 0) { *font_scale = cs.font_scale; got_fs = 1; }
            if (!got_lh && cs.line_scale != 0) { *line_scale = cs.line_scale; got_lh = 1; }
            /* text-decoration: nearest ancestor that sets it (incl. an explicit
             * `none` = 0, which drops a link underline). -1 means still unset. */
            if (!got_deco && cs.text_decoration != -1) { *deco = cs.text_decoration; got_deco = 1; }
            /* Nearest flex/grid container: derived from the SAME resolved css_style
             * (cs) as the colors above, so a <style> rule feeds gap/justify/columns,
             * not just an inline style=. Its runs share one id so the presentation
             * layer can lay the container out. Structure, so render_doc applies it
             * regardless of caps.css. */
            if (!got_cont && reg != NULL &&
                (cs.display == CSS_DISP_FLEX || cs.display == CSS_DISP_GRID)) {
                cont->display = (cs.display == CSS_DISP_FLEX) ? BX_DISPLAY_FLEX
                                                             : BX_DISPLAY_GRID;
                cont->gap = (cs.gap >= 0) ? cs.gap : 0;
                cont->justify = css_to_fx_justify(cs.justify);
                cont->cols = (cs.display == CSS_DISP_GRID)
                             ? (cs.grid_cols > 0 ? cs.grid_cols : 1) : 0;
                cont->id = container_id(reg, p);
                got_cont = 1;
            }
        }
        if (p == base) break;
    }

    *bold = got_css_bold ? css_bold : tag_bold;
    *italic = got_css_italic ? css_italic : tag_italic;
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

/* 1-based position of an <li> among its <li> siblings (an <ol> counter, basic: the
 * `start`/`value` attributes are out of scope). Counts preceding element siblings
 * that are <li>. */
static int li_ordinal(const lxb_dom_node_t *li) {
    int n = 1;
    for (const lxb_dom_node_t *p = li->prev; p != NULL; p = p->prev) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT && node_tag(p) == LXB_TAG_LI) ++n;
    }
    return n;
}

/* Spreadsheet-style alphabetic ordinal (1->a, 26->z, 27->aa), written as "a. " into
 * out (size cap). upper selects A..Z. */
static void alpha_marker(int n, int upper, char *out, size_t cap) {
    char buf[8];
    int k = 0;
    if (n < 1) n = 1;
    while (n > 0 && k < (int)sizeof buf) {
        int r = (n - 1) % 26;
        buf[k++] = (char)((upper ? 'A' : 'a') + r);
        n = (n - 1) / 26;
    }
    size_t o = 0;
    while (k > 0 && o + 1 < cap) out[o++] = buf[--k];     /* reverse */
    if (o + 2 < cap) { out[o++] = '.'; out[o++] = ' '; }
    if (o < cap) out[o] = '\0';
}

/* Roman-numeral ordinal (1->i, 4->iv, clamped to [1,3999]) as "iv. " into out. */
static void roman_marker(int n, int upper, char *out, size_t cap) {
    static const int vals[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };
    static const char *const up[] = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };
    static const char *const lo[] = { "m","cm","d","cd","c","xc","l","xl","x","ix","v","iv","i" };
    if (cap == 0) return;
    if (n < 1) n = 1;
    if (n > 3999) n = 3999;
    size_t o = 0;
    for (int i = 0; i < 13; ++i) {
        const char *s = upper ? up[i] : lo[i];
        while (n >= vals[i]) {
            for (const char *p = s; *p != '\0' && o + 1 < cap; ++p) out[o++] = *p;
            n -= vals[i];
        }
    }
    if (o + 2 < cap) { out[o++] = '.'; out[o++] = ' '; }
    out[o < cap ? o : cap - 1] = '\0';
}

/* Builds the list marker for the first run of an <li>. With no author list-style
 * (CSS_LS_UNSET) it is the UA default: "N. " for an ordered list, "* " (bullet)
 * otherwise. An author list-style-type selects the glyph/numbering (disc/circle/
 * square or decimal/alpha/roman). Written into out (size cap); ASCII or short UTF-8,
 * so it is valid UTF-8 and safe to paint. CSS_LS_NONE is handled by the caller (no
 * marker emitted at all). */
static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                        char *out, size_t cap) {
    if (cap == 0) return;
    int ord = (li != NULL) ? li_ordinal(li) : 1;
    switch (list_style) {
        case CSS_LS_DISC:        snprintf(out, cap, "\xE2\x80\xA2 "); return; /* U+2022 bullet */
        case CSS_LS_CIRCLE:      snprintf(out, cap, "\xE2\x97\xA6 "); return; /* U+25E6 white bullet */
        case CSS_LS_SQUARE:      snprintf(out, cap, "\xE2\x96\xAA "); return; /* U+25AA small square */
        case CSS_LS_DECIMAL:     snprintf(out, cap, "%d. ", ord); return;
        case CSS_LS_LOWER_ALPHA: alpha_marker(ord, 0, out, cap); return;
        case CSS_LS_UPPER_ALPHA: alpha_marker(ord, 1, out, cap); return;
        case CSS_LS_LOWER_ROMAN: roman_marker(ord, 0, out, cap); return;
        case CSS_LS_UPPER_ROMAN: roman_marker(ord, 1, out, cap); return;
        default: break;  /* unset: UA default below */
    }
    if (ordered && li != NULL) snprintf(out, cap, "%d. ", ord);
    else                       snprintf(out, cap, "\xE2\x80\xA2 ");
}

/* Nearest <table> ancestor of n (up to base), or NULL. */
static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT && node_tag(p) == LXB_TAG_TABLE) return p;
        if (p == base) break;
    }
    return NULL;
}

/* Nonzero if n has a <td>/<th> ancestor up to base: its text was already emitted as
 * one collected cell run, so the normal walk must not re-emit the inner text. */
static int in_cell_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(p);
            if (t == LXB_TAG_TD || t == LXB_TAG_TH) return 1;
        }
        if (p == base) break;
    }
    return 0;
}

/* Grid column count of a table: the maximum number of <td>/<th> direct children of
 * any descendant <tr>, clamped to [1, PV_MAX_GRID_COLS]. A table is laid out as a
 * grid of equal columns (basic: colspan/rowspan are out of scope). */
static int table_columns(const lxb_dom_node_t *table) {
    int maxc = 1;
    for (lxb_dom_node_t *n = table->first_child; n != NULL; n = node_next(n, table)) {
        if (n->type != LXB_DOM_NODE_TYPE_ELEMENT || node_tag(n) != LXB_TAG_TR) continue;
        int c = 0;
        for (const lxb_dom_node_t *k = n->first_child; k != NULL; k = k->next) {
            if (k->type == LXB_DOM_NODE_TYPE_ELEMENT) {
                lxb_tag_id_t t = node_tag(k);
                if (t == LXB_TAG_TD || t == LXB_TAG_TH) ++c;
            }
        }
        if (c > maxc) maxc = c;
    }
    if (maxc > PV_MAX_GRID_COLS) maxc = PV_MAX_GRID_COLS;
    return maxc;
}

/* Upper bound on concatenated <style> text (anti-DoS): a pathological document
 * cannot make the parser allocate without limit. The css module is itself bounded;
 * this caps the text fed to it. */
#define PV_MAX_STYLE_BYTES (1u << 20)

/* Concatenates the text of every <style> element in the document (head included)
 * into one owned, NUL-terminated buffer, capped at PV_MAX_STYLE_BYTES. Returns NULL
 * when there is no <style> (or on OOM, treated by the caller as "no author CSS").
 * *outlen receives the length. */
static char *collect_style_text(lxb_dom_node_t *root, size_t *outlen) {
    *outlen = 0;
    size_t cap = 0, len = 0;
    char *buf = NULL;
    for (lxb_dom_node_t *n = root; n != NULL && len < PV_MAX_STYLE_BYTES;
         n = node_next(n, root)) {
        if (n->type != LXB_DOM_NODE_TYPE_ELEMENT || node_tag(n) != LXB_TAG_STYLE) continue;
        for (lxb_dom_node_t *k = n->first_child; k != NULL; k = k->next) {
            if (k->type != LXB_DOM_NODE_TYPE_TEXT) continue;
            lxb_dom_text_t *txt = lxb_dom_interface_text(k);
            const char *raw = (const char *)txt->char_data.data.data;
            size_t rl = txt->char_data.data.length;
            if (raw == NULL || rl == 0) continue;
            if (rl > PV_MAX_STYLE_BYTES - len) rl = PV_MAX_STYLE_BYTES - len;
            if (rl == 0) break;
            if (len + rl + 1 > cap) {
                size_t nc = cap ? cap * 2 : 1024;
                while (nc < len + rl + 1) nc *= 2;
                char *g = (char *)realloc(buf, nc);
                if (g == NULL) { free(buf); return NULL; }
                buf = g; cap = nc;
            }
            memcpy(buf + len, raw, rl);
            len += rl;
        }
    }
    if (buf != NULL) buf[len] = '\0';
    *outlen = len;
    return buf;
}

/* Nonzero if n or any ancestor up to base has display:none (from the <style> sheet
 * or its inline style=). display:none is structural visibility, applied regardless
 * of caps.css (hidden content stays hidden, like the JS-off display:none caveat). */
static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                             const css_sheet *sheet) {
    for (const lxb_dom_node_t *p = n; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)p);
            if (element_css_style(el, sheet).display == CSS_DISP_NONE) return 1;
        }
        if (p == base) break;
    }
    return 0;
}

/* Nonzero if n or any ancestor up to base is page boilerplate (<nav>/<header>/
 * <footer>/<aside>). Used only in distraction-free (reader) mode to drop chrome and
 * keep the main content. Deterministic, not heuristic article extraction. */
static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base) {
    for (const lxb_dom_node_t *p = n; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(p);
            if (t == LXB_TAG_NAV || t == LXB_TAG_HEADER ||
                t == LXB_TAG_FOOTER || t == LXB_TAG_ASIDE) return 1;
        }
        if (p == base) break;
    }
    return 0;
}

pv_status pv_build(const hp_document *doc, pv_view **out) {
    return pv_build_full(doc, 0, 0, 0, out); /* JS off by default: <noscript> fallback shown */
}

pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out) {
    return pv_build_full(doc, js_enabled, 0, 0, out);
}

pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                        int prefers_dark, pv_view **out) {
    if (doc == NULL || out == NULL) return PV_ERR_NULL_ARG;
    *out = NULL;

    pv_view *v = pv_new();
    if (v == NULL) return PV_ERR_OOM;

    lxb_dom_node_t *root = (lxb_dom_node_t *)hp_document_root(doc);
    if (root == NULL) { *out = v; return PV_OK; } /* empty document */

    lxb_dom_node_t *body = find_body(root);
    lxb_dom_node_t *base = (body != NULL) ? body : root;

    /* Parse the document's <style> blocks once into a bounded sheet (pure: it never
     * fetches and drops url()/@-rules). A NULL sheet is treated as empty by the css
     * module, so OOM here degrades to "no author CSS", not a failure. */
    size_t style_len = 0;
    char *style_text = collect_style_text(root, &style_len);
    css_sheet *sheet = NULL;
    /* @media gated against the user's color scheme (auto dark mode) and a fixed,
     * normalized desktop width (no real viewport size leaks). Screen context. */
    css_media media = { prefers_dark ? 1 : 0, 0, CSS_MEDIA_DEFAULT_WIDTH };
    (void)css_parse_media(style_text, style_len, &media, &sheet);
    free(style_text);

    const lxb_dom_node_t *prev_block = NULL;
    const lxb_dom_node_t *prev_li = NULL;  /* last <li> seen, to mark each item once */
    int pending_break = 0;
    form_table forms = { NULL, 0, 0 };
    pv_status rc = PV_OK;
    pv_container_reg reg = { { NULL }, 0 };  /* flex/grid containers, document order */
    pv_container_reg block_reg = { { NULL }, 0 };  /* box-carrying blocks, document order */

    for (lxb_dom_node_t *n = base; n != NULL; n = node_next(n, base)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(n);
            if (t == LXB_TAG_BR || t == LXB_TAG_HR) { pending_break = 1; continue; }

            if (t == LXB_TAG_FORM) {
                if (forms_add(&forms, n) != 0) { rc = PV_ERR_OOM; goto cleanup; }
                continue;
            }

            /* A table cell becomes one collected text run annotated as a grid item:
             * the table is a grid container (cont_id), its column count is the widest
             * row, and each cell is one column. This reuses the flex/grid layout
             * engine (layout_container/box_tree) so cells align across rows. <th> is
             * bold. The cell's inner text nodes are suppressed below (in_cell_subtree)
             * so they are not re-emitted. Nested cells are handled by the outer cell. */
            if ((t == LXB_TAG_TD || t == LXB_TAG_TH)
                && !in_skipped_subtree(n, base, js_enabled) && !in_cell_subtree(n, base)
                && !in_hidden_subtree(n, base, sheet)
                && !(reader && in_boilerplate_subtree(n, base))) {
                const lxb_dom_node_t *table = nearest_table(n, base);
                int cols = (table != NULL) ? table_columns(table) : 1;
                int cid = (table != NULL) ? container_id(&reg, table) : -1;

                char *raw = collect_text(n);
                if (raw == NULL) { rc = PV_ERR_OOM; goto cleanup; }
                char *cell = collapse_ws(raw, strlen(raw));
                free(raw);
                if (cell == NULL) { rc = PV_ERR_OOM; goto cleanup; }

                /* The whole table is one block: the first cell breaks from the prior
                 * block, the rest share it, so the grid is laid out as one unit. */
                const lxb_dom_node_t *tblk = (table != NULL) ? table : n;
                int brk = pending_break || (tblk != prev_block);
                pending_break = 0;
                prev_block = tblk;

                /* An empty cell still occupies its column. */
                pv_status st = pv_append(v, PV_TEXT, 0, brk,
                                         (cell[0] != '\0') ? cell : " ", NULL);
                free(cell);
                if (st != PV_OK) { rc = st; goto cleanup; }
                pv_set_emphasis(v, (t == LXB_TAG_TH) ? 1 : 0, 0);
                pv_set_container(v, cid, BX_DISPLAY_GRID, 0, FX_JUSTIFY_START, cols);
                continue;
            }

            if ((t == LXB_TAG_INPUT || t == LXB_TAG_TEXTAREA || t == LXB_TAG_BUTTON)
                && !in_skipped_subtree(n, base, js_enabled)
                && !in_hidden_subtree(n, base, sheet)
                && !(reader && in_boilerplate_subtree(n, base))) {
                lxb_dom_element_t *el = lxb_dom_interface_element(n);

                const char *unused_href = NULL;
                size_t unused_hl = 0;
                const lxb_dom_node_t *block = NULL;
                int heading = 0, unused_fg = -1, unused_bg = -1;
                int unused_bold = 0, unused_italic = 0, unused_align = 0, unused_fs = 0, unused_lh = 0, unused_deco = 0;
                const lxb_dom_node_t *unused_li = NULL;
                int unused_depth = 0, unused_ordered = 0;
                pv_cont_info unused_cont;
                pv_box_info unused_box;
                pv_text_ext unused_ext;
                pv_box_deco unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &unused_ext,
                                &block_reg, &unused_bdeco);
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

            if (t == LXB_TAG_IMG && !in_skipped_subtree(n, base, js_enabled)
                && !in_hidden_subtree(n, base, sheet)
                && !(reader && in_boilerplate_subtree(n, base))) {
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
                int heading = 0, unused_fg = -1, unused_bg = -1;
                int unused_bold = 0, unused_italic = 0, unused_align = 0, unused_fs = 0, unused_lh = 0, unused_deco = 0;
                const lxb_dom_node_t *unused_li = NULL;
                int unused_depth = 0, unused_ordered = 0;
                pv_cont_info unused_cont;
                pv_box_info unused_box;
                pv_text_ext unused_ext;
                pv_box_deco unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &unused_ext,
                                &block_reg, &unused_bdeco);
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
        if (in_skipped_subtree(n, base, js_enabled)) continue;
        if (in_cell_subtree(n, base)) continue; /* already emitted as a collected cell run */
        if (in_hidden_subtree(n, base, sheet)) continue; /* display:none */
        if (reader && in_boilerplate_subtree(n, base)) continue; /* distraction-free */

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
        int heading = 0, fg = -1, bg = -1, bold = 0, italic = 0, align = 0, font_scale = 0;
        int line_scale = 0, text_decoration = -1;
        const lxb_dom_node_t *li = NULL;
        int list_depth = 0, ordered = 0;
        pv_cont_info cont;
        pv_box_info box;
        pv_text_ext ext;
        pv_box_deco bdeco;
        resolve_context(n, base, sheet, &href, &href_len, &block, &heading, &fg, &bg,
                        &bold, &italic, &align, &font_scale, &line_scale, &text_decoration,
                        &li, &list_depth, &ordered, &reg, &cont, &box, &ext,
                        &block_reg, &bdeco);

        int brk = pending_break || (block != prev_block);
        pending_break = 0;
        prev_block = block;

        /* Prepend the list marker ("* "/"N. ") to the first text run of each <li>,
         * once per item. The marker is plain ASCII text, so it inherits the run's
         * style and needs no special painting; the GUI indents the whole item by
         * list_depth. A run that is only whitespace (e.g. between a nested </ul> and
         * its </li>) carries no content, so it never claims the marker. */
        int has_content = 0;
        for (const char *c = collapsed; *c != '\0'; ++c) {
            if (*c != ' ') { has_content = 1; break; }
        }
        char *marked = NULL;
        if (li != NULL && li != prev_li && has_content && ext.list_style != CSS_LS_NONE) {
            char mk[32];
            list_marker(ordered, li, ext.list_style, mk, sizeof mk);
            size_t ml = strlen(mk), cl = strlen(collapsed);
            marked = (char *)malloc(ml + cl + 1);
            if (marked == NULL) { free(collapsed); rc = PV_ERR_OOM; goto cleanup; }
            memcpy(marked, mk, ml);
            memcpy(marked + ml, collapsed, cl + 1);
        }
        if (has_content) prev_li = li;
        const char *text_for_run = (marked != NULL) ? marked : collapsed;

        char *href_dup = NULL;
        if (href != NULL) {
            href_dup = dup_n(href, href_len);
            if (href_dup == NULL) { free(collapsed); free(marked); rc = PV_ERR_OOM; goto cleanup; }
        }

        pv_status st = pv_append(v, href_dup != NULL ? PV_LINK : PV_TEXT,
                                 heading, brk, text_for_run, href_dup);
        free(collapsed);
        free(marked);
        free(href_dup);
        if (st != PV_OK) { rc = st; goto cleanup; }
        pv_set_emphasis(v, bold, italic);
        pv_set_indent(v, list_depth);
        pv_set_color(v, fg);
        pv_set_bgcolor(v, bg);
        pv_set_text_style(v, align, font_scale, line_scale, text_decoration);
        pv_set_container(v, cont.id, cont.display, cont.gap, cont.justify, cont.cols);
        pv_set_box(v, box.l, box.r, box.w, box.center, box.mt, box.mb);
        pv_set_text_ext(v, ext.font_family, ext.text_transform, ext.letter_spacing,
                        ext.word_spacing, ext.shadow_dx, ext.shadow_dy, ext.shadow_color,
                        ext.opacity, ext.valign, ext.text_indent, ext.white_space);
        pv_set_block_id(v, bdeco.block_id);
        pv_set_box_border(v, bdeco.bord_tw, bdeco.bord_rw, bdeco.bord_bw, bdeco.bord_lw,
                          bdeco.bord_ts, bdeco.bord_rs, bdeco.bord_bs, bdeco.bord_ls,
                          bdeco.bord_tc, bdeco.bord_rc, bdeco.bord_bc, bdeco.bord_lc,
                          bdeco.border_radius);
        pv_set_boxdeco(v, bdeco.box_sizing, bdeco.pad_t, bdeco.pad_r, bdeco.pad_b,
                       bdeco.pad_l, bdeco.bsh_dx, bdeco.bsh_dy, bdeco.bsh_blur,
                       bdeco.bsh_spread, bdeco.bsh_color, bdeco.bsh_inset,
                       bdeco.outline_w, bdeco.outline_style, bdeco.outline_color);
    }

    *out = v;
    forms_free(&forms);
    css_free(sheet);
    return PV_OK;

cleanup:
    forms_free(&forms);
    css_free(sheet);
    pv_free(v);
    return rc;
}
