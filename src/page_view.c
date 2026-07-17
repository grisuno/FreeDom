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
#include "css_chain.h"
#include "css_color.h"
#include "flex_layout.h"
#include "html_parse.h"
#include "util.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* The per-run sized-track cap mirrors the css module's; a divergence would
 * silently truncate track sizes on the wire. */
_Static_assert(PV_GRID_TRACKS == CSS_GRID_TRACKS_MAX,
               "PV_GRID_TRACKS must mirror CSS_GRID_TRACKS_MAX");
_Static_assert(PV_BG_URL_MAX == CSS_URL_MAX,
               "PV_BG_URL_MAX must mirror CSS_URL_MAX");
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
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    if (n == (size_t)-1 || n > (size_t)-1 / 3) return NULL;
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
    if (n == (size_t)-1) return NULL; /* guard: n+1 would overflow to 0 */
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    if (n != 0 && s != NULL) memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

/* --- public: model --- */

/* Common field initialization shared by all append helpers. Keeps the three
 * constructors DRY and guarantees every run starts from the same sentinel state
 * (including the Stage 0 node_id and the Step D block_id). */
static void run_init_common(pv_run *r) {
    r->kind = PV_TEXT;
    r->heading = 0;
    r->block_break = 0;
    r->text = NULL;
    r->href = NULL;
    r->src = NULL;
    r->poster_src = NULL;
    r->img_w = -1;
    r->img_h = -1;
    r->bold = 0;
    r->italic = 0;
    r->indent = 0;
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
    r->tab_size = 0;
    r->direction = 0;
    r->font_variant = 0;
    r->list_style_pos = 0;
    r->text_overflow = 0;
    r->word_break = 0;
    r->image_rendering = 0;
    r->caret_color = -1;
    r->object_fit = 0;
    r->cont_id = -1;
    r->cont_display = 0;
    r->cont_gap = 0;
    r->cont_justify = 0;
    r->cont_cols = 0;
    for (int gk = 0; gk < PV_GRID_TRACKS; ++gk) r->cont_col_w[gk] = 0;
    r->grid_span = 0;
    r->flex_grow = -1;
    r->flex_shrink = -1;
    r->flex_basis = CSS_LEN_UNSET;
    r->flex_order = CSS_LEN_UNSET;
    r->flex_direction = 0;
    r->cont_item = -1;
    r->cont_wrap = 0;
    r->cont_row_gap = -1;
    r->cont_align_items = 0;
    r->flex_align_self = 0;
    r->float_side = 0;
    r->float_id = -1;
    r->float_clear = 0;
    r->box_l = 0;
    r->box_r = 0;
    r->box_w = 0;
    r->box_center = 0;
    r->box_mt = PV_LEN_UNSET;
    r->box_mb = PV_LEN_UNSET;
    r->box_w_pct = 0;
    r->node_id = DOM_NODE_NONE;
    r->block_id = -1;
    r->input_type = 0;
    r->name = NULL;
    r->value = NULL;
    r->form_id = -1;
    r->form_method = PV_METHOD_GET;
    r->checked = -1;
    r->select_opts = NULL;
}

/* Forward declaration: the iterative pre-order successor is defined below. */
static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root);

/* Keystone (Stage 0): document-order element identity. page_view builds the same
 * pre-order element walk that dom_build uses, mapping each element pointer to its
 * 0-based id. Runs then stamp the id of their source element so the GUI can map a
 * painted block back to the live DOM node for event dispatch. */
#define PV_NODE_MAP_INIT_CAP 64

typedef struct pv_node_map {
    const lxb_dom_node_t **nodes;
    size_t count;
    size_t cap;
} pv_node_map;

static int pv_node_map_init(pv_node_map *m) {
    m->nodes = (const lxb_dom_node_t **)calloc(PV_NODE_MAP_INIT_CAP, sizeof *m->nodes);
    if (m->nodes == NULL) return -1;
    m->count = 0;
    m->cap = PV_NODE_MAP_INIT_CAP;
    return 0;
}

static void pv_node_map_free(pv_node_map *m) {
    if (m == NULL) return;
    free(m->nodes);
    m->nodes = NULL;
    m->count = m->cap = 0;
}

/* Records an element node in document order. Returns its id, or DOM_NODE_NONE on
 * overflow (anti-DoS: a hostile document with too many elements still renders, but
 * without stable ids for the overflow nodes). */
static dom_node_id pv_node_map_add(pv_node_map *m, const lxb_dom_node_t *node) {
    if (m->count >= m->cap) {
        size_t ncap = m->cap * 2;
        const lxb_dom_node_t **grown =
            (const lxb_dom_node_t **)realloc(m->nodes, ncap * sizeof *grown);
        if (grown == NULL) return DOM_NODE_NONE;
        m->nodes = grown;
        m->cap = ncap;
    }
    dom_node_id id = (dom_node_id)m->count;
    m->nodes[m->count++] = node;
    return id;
}

/* Looks up the document-order id of an element node. Returns DOM_NODE_NONE if the
 * node was not recorded (e.g. overflow or a node from outside the indexed tree). */
static dom_node_id pv_node_map_id(const pv_node_map *m, const lxb_dom_node_t *node) {
    if (m == NULL || node == NULL) return DOM_NODE_NONE;
    for (size_t i = 0; i < m->count; ++i) {
        if (m->nodes[i] == node) return (dom_node_id)i;
    }
    return DOM_NODE_NONE;
}

/* Builds a document-order map of all element nodes under root. Returns 0, or -1 on
 * allocation failure. */
static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root) {
    if (pv_node_map_init(m) != 0) return -1;
    for (const lxb_dom_node_t *n = root; n != NULL; n = node_next((lxb_dom_node_t *)n, root)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT)
            (void)pv_node_map_add(m, n);
    }
    return 0;
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
    run_init_common(r);
    r->kind = kind;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->href = h;
    r->src = NULL;
    r->poster_src = NULL;
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
    run_init_common(r);
    r->kind = PV_IMAGE;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->src = s;
    r->poster_src = NULL;
    r->img_w = w;
    r->img_h = h;
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
    run_init_common(r);
    r->kind = PV_INPUT;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->href = ac;
    r->input_type = (int)input_type;
    r->name = nm;
    r->value = vl;
    r->form_id = form_id;
    r->form_method = method;
    return PV_OK;
}

pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src,
                          const char *poster, int w, int h) {
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
    char *p = NULL;
    if (poster != NULL) {
        p = utf8_sanitized_dup(poster);
        if (p == NULL) { free(t); free(s); return PV_ERR_OOM; }
    }

    pv_run *r = &v->runs[v->count++];
    run_init_common(r);
    r->kind = PV_VIDEO;
    r->heading = heading;
    r->block_break = block_break;
    r->text = t;
    r->src = s;
    r->poster_src = p;
    r->img_w = w;
    r->img_h = h;
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

void pv_set_text_ext(pv_view *v, const pv_text_ext *e) {
    if (v == NULL || v->count == 0 || e == NULL) return;
    pv_run *r = &v->runs[v->count - 1];
    r->font_family = e->font_family;
    r->text_transform = e->text_transform;
    r->letter_spacing = e->letter_spacing;
    r->word_spacing = e->word_spacing;
    r->shadow_dx = e->shadow_dx;
    r->shadow_dy = e->shadow_dy;
    r->shadow_color = e->shadow_color;
    r->opacity = e->opacity;
    r->valign = e->valign;
    r->text_indent = e->text_indent;
    r->white_space = e->white_space;
    r->text_overflow = e->text_overflow;
    r->word_break = e->word_break;
    r->text_decoration_color = e->text_decoration_color;
    r->text_decoration_style = e->text_decoration_style;
    r->text_decoration_thickness = e->text_decoration_thickness;
    r->tab_size = e->tab_size;
    r->direction = e->direction;
    r->font_variant = e->font_variant;
    r->list_style_pos = e->list_style_pos;
    r->image_rendering = e->image_rendering;
    /* CSS_LEN_AUTO is an explicit caret-color:auto -- resolved, but the theme
     * caret is the effect, so the run carries the same -1 as unset. */
    r->caret_color = (e->caret_color == CSS_LEN_AUTO) ? -1 : e->caret_color;
    r->object_fit = e->object_fit;
}

void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_gap, int cont_justify, int cont_cols,
                      int cont_wrap, int cont_row_gap, int cont_align_items) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->cont_id = cont_id;
    r->cont_display = cont_display;
    r->cont_gap = cont_gap;
    r->cont_justify = cont_justify;
    r->cont_cols = cont_cols;
    r->cont_wrap = cont_wrap;
    r->cont_row_gap = cont_row_gap;
    r->cont_align_items = cont_align_items;
}

void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    if (col_w != NULL) {
        int lim = (n < PV_GRID_TRACKS) ? n : PV_GRID_TRACKS;
        for (int k = 0; k < lim; ++k) r->cont_col_w[k] = col_w[k];
    }
    r->grid_span = (col_span > 0) ? col_span : 0;
}

void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int flex_order, int flex_direction, int flex_align_self) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->flex_grow = flex_grow;
    r->flex_shrink = flex_shrink;
    r->flex_basis = flex_basis;
    r->flex_order = flex_order;
    r->flex_direction = flex_direction;
    r->flex_align_self = flex_align_self;
}

void pv_set_cont_item(pv_view *v, int cont_item) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].cont_item = cont_item;
}

void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear) {
    if (v == NULL || v->count == 0) return;
    pv_run *r = &v->runs[v->count - 1];
    r->float_side = float_side;
    r->float_id = float_id;
    r->float_clear = float_clear;
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

void pv_set_box_pct(pv_view *v, int box_w_pct) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].box_w_pct = box_w_pct;
}

void pv_set_node_id(pv_view *v, dom_node_id node_id) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].node_id = node_id;
}

void pv_set_block_id(pv_view *v, int block_id) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].block_id = block_id;
}

void pv_set_input_checked(pv_view *v, int checked) {
    if (v == NULL || v->count == 0) return;
    v->runs[v->count - 1].checked = checked;
}

void pv_set_input_select_opts(pv_view *v, const char *select_opts) {
    if (v == NULL || v->count == 0 || select_opts == NULL) return;
    char *cp = dup_n(select_opts, strlen(select_opts));
    if (cp == NULL) return;
    free(v->runs[v->count - 1].select_opts);
    v->runs[v->count - 1].select_opts = cp;
}

pv_status pv_add_box_def(pv_view *v, const pv_box_def *d) {
    if (v == NULL || d == NULL) return PV_ERR_NULL_ARG;
    if (v->nbox == v->boxcap) {
        size_t nc = v->boxcap ? v->boxcap * 2 : 8;
        pv_box_def *g = (pv_box_def *)realloc(v->boxes, nc * sizeof *g);
        if (g == NULL) return PV_ERR_OOM;
        v->boxes = g;
        v->boxcap = nc;
    }
    v->boxes[v->nbox++] = *d;
    return PV_OK;
}

void pv_free(pv_view *v) {
    if (v == NULL) return;
    for (size_t i = 0; i < v->count; ++i) {
        free(v->runs[i].text);
        free(v->runs[i].href);
        free(v->runs[i].src);
        free(v->runs[i].poster_src);
        free(v->runs[i].name);
        free(v->runs[i].value);
        free(v->runs[i].select_opts);
    }
    free(v->runs);
    free(v->boxes);
    free(v);
}

size_t pv_count(const pv_view *v) {
    return (v != NULL) ? v->count : 0;
}

const pv_run *pv_at(const pv_view *v, size_t i) {
    if (v == NULL || i >= v->count) return NULL;
    return &v->runs[i];
}

size_t pv_box_count(const pv_view *v) {
    return (v != NULL) ? v->nbox : 0;
}

const pv_box_def *pv_box_at(const pv_view *v, size_t i) {
    if (v == NULL || i >= v->nbox) return NULL;
    return &v->boxes[i];
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
        case LXB_TAG_FORM: case LXB_TAG_FIELDSET:         case LXB_TAG_DL:
        case LXB_TAG_DT: case LXB_TAG_DD:
        case LXB_TAG_MENU:
        case LXB_TAG_DETAILS: case LXB_TAG_SUMMARY:
            return 1;
        default:
            return 0;
    }
}

/* An element should be treated as block-like (eligible for box registration,
 * hbox, float) when its CSS display property indicates a block-level box, even
 * if the tag itself is normally inline. This lets author CSS like
 *   a { display: inline-block; width: 22px; }
 * actually create a box for the <a> tag. */
static int is_block_like(lxb_tag_id_t t, css_display display) {
    if (display == CSS_DISP_INLINE) return 0;
    if (display == CSS_DISP_BLOCK || display == CSS_DISP_INLINE_BLOCK
        || display == CSS_DISP_LIST_ITEM) return 1;
    return is_block_tag(t);
}

/* Returns 1 when the element should cause a block break (start a new line).
 * display:inline-block and display:inline do NOT cause a break; they flow
 * inline while still being eligible for box registration. */
static int causes_block_break(lxb_tag_id_t t, css_display display) {
    if (display == CSS_DISP_INLINE || display == CSS_DISP_INLINE_BLOCK) return 0;
    if (display == CSS_DISP_BLOCK) return 1;
    return is_block_tag(t);
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
     * shown when JS is disabled and hidden when JS runs.
     * PROGRESS/METER/LEGEND content is captured as attributes/text and emitted
     * as PV_INPUT runs with their respective types. */
    return t == LXB_TAG_SCRIPT || t == LXB_TAG_STYLE || t == LXB_TAG_HEAD
        || t == LXB_TAG_TITLE
        || t == LXB_TAG_TEXTAREA || t == LXB_TAG_SELECT || t == LXB_TAG_BUTTON
        || t == LXB_TAG_PROGRESS || t == LXB_TAG_METER || t == LXB_TAG_LEGEND;
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

/* A color-valued legacy attribute (e.g. <font color>, bgcolor) as a packed
 * 0xRRGGBB, or -1. Not CSS: a separate fallback consulted only when no CSS
 * declaration for that channel won. */
static int color_attr(lxb_dom_element_t *el, const char *name, size_t name_len) {
    size_t cl = 0;
    const lxb_char_t *col =
        lxb_dom_element_get_attribute(el, (const lxb_char_t *)name, name_len, &cl);
    if (col != NULL && cl > 0 && cl < PV_COLOR_TOKEN_MAX) {
        char buf[PV_COLOR_TOKEN_MAX];
        memcpy(buf, col, cl);
        buf[cl] = '\0';
        cc_rgb rgb;
        cc_status st = cc_parse(buf, &rgb);
        if (st == CC_OK) return cc_pack(rgb);
        if (st == CC_TRANSPARENT) return CC_COLOR_TRANSPARENT;
        if (st == CC_CURRENT_COLOR) return CC_COLOR_CURRENT;
    }
    return -1;
}

static int font_color_attr(lxb_dom_element_t *el) {
    return color_attr(el, "color", 5);
}

/* Legacy bgcolor attribute (body/table/tr/td), the background twin of <font
 * color>: pre-CSS sites (Hacker News' orange bar and beige page) still use it. */
static int bgcolor_attr(lxb_dom_element_t *el) {
    return color_attr(el, "bgcolor", 7);
}

/* --- author flex/grid container layout: structure, not author styling. render_doc
 * applies it ALWAYS, decoupled from caps.css (doctrine "Layout != estilo de autor");
 * only author colors/text-align/font-size stay gated. The display and its params
 * (gap/justify/columns) come from the css cascade (<style> + inline), resolved by
 * cch_element_style like the colors. --- */

#define PV_MAX_CONTAINERS   256u
#define PV_MAX_GRID_COLS    64

/* Nearest-container info attached to a run, plus the flex per-item values (Stage 3):
 * grow/shrink/basis/order come from the ITEM element (the container's direct child on
 * the run's ancestor chain); direction from the container itself. Unset sentinels:
 * grow/shrink -1, basis/order CSS_LEN_UNSET, direction 0. `item` is that same direct
 * child (NULL = anonymous item: text directly inside the container); pv_build maps it
 * to the run's cont_item ordinal so inline fragments of one child share one item. */
typedef struct pv_cont_info {
    int id, display, gap, justify, cols;
    /* Grid track sizes of the container (0 auto / >0 px / <0 fr x100) and the
     * ITEM's grid-column span (tracked like grow/shrink via the previous element
     * on the walk; 0 = 1 column). */
    int col_w[PV_GRID_TRACKS];
    int col_span;
    int grow, shrink, basis, order, direction;
    const lxb_dom_node_t *item;
    /* Float context (spec/float.md): float_side/float_id from the nearest floated
     * self-or-ancestor block, float_clear from the run's own leaf block. */
    int float_side, float_id, float_clear;
/* flex-wrap / row-gap / align-items (CONTAINER); align-self (ITEM, tracked
 * like grow/shrink/basis/order via the previous element on the walk).
 * align_content / justify_items (CONTAINER), grid_rows / grid_flow (grid
 * container), row_span (ITEM) — 2026-07-12 batch. */
int wrap, row_gap, align_items, align_self;
int align_content, justify_items;
int grid_rows, grid_flow, row_span;
} pv_cont_info;

/* Per-container item-ordinal tracker: ord[cid] is the ordinal last handed out for
 * container cid, node[cid] the direct-child element it belongs to. A run whose item
 * differs from the tracked one (or is NULL = anonymous) opens the next ordinal, so
 * consecutive runs of one child share it and nested-container interruptions do not
 * break the outer container's item continuity. */
typedef struct pv_item_track {
    const lxb_dom_node_t *node[PV_MAX_CONTAINERS];
    int ord[PV_MAX_CONTAINERS];
} pv_item_track;

/* Ordinal for a run of container `cid` whose direct-child item is `item` (NULL =
 * anonymous: every such run is its own item). -1 when the run has no container. */
static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item) {
    if (cid < 0 || (size_t)cid >= PV_MAX_CONTAINERS) return -1;
    if (item == NULL || item != tr->node[cid]) {
        tr->ord[cid]++;
        tr->node[cid] = item;
    }
    return tr->ord[cid];
}

/* Author box model resolved for a run: horizontal placement (l/r insets, w cap,
 * centered) from the nearest block ancestor that declares a box, plus the leaf
 * block's own vertical-margin override (mt/mb, or PV_LEN_UNSET). */
typedef struct pv_box_info {
    int l, r, w, center, mt, mb;
    int w_pct;   /* per-mille width cap (Hito 32), 0 = none; LAST so the existing
                  * positional initializers keep meaning what they say */
} pv_box_info;

/* The author text-presentation extensions struct (pv_text_ext) is public now
 * (include/page_view.h): each field resolves from the nearest ancestor that sets
 * it (they inherit in CSS). list_style drives the <li> marker (structural); the
 * rest are gated by caps.css downstream. */

void pv_text_ext_reset(pv_text_ext *e) {
    if (e == NULL) return;
    e->font_family = 0; e->text_transform = 0;
    e->letter_spacing = PV_LEN_UNSET; e->word_spacing = PV_LEN_UNSET;
    e->shadow_dx = 0; e->shadow_dy = 0; e->shadow_color = -1;
    e->opacity = -1; e->valign = 0; e->text_indent = PV_LEN_UNSET;
    e->white_space = 0; e->list_style = 0;
    e->text_overflow = 0; e->word_break = 0;
    e->text_decoration_color = -1;
    e->text_decoration_style = 0;
    e->text_decoration_thickness = -1;
    e->tab_size = 0; e->direction = 0; e->font_variant = 0; e->list_style_pos = 0;
    e->image_rendering = 0;
    e->caret_color = -1;
    e->object_fit = 0;
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
    if (e->text_overflow == 0 && cs->text_overflow != CSS_TO_UNSET)
        e->text_overflow = cs->text_overflow;
    if (e->word_break == 0 && cs->word_break != CSS_WB_UNSET) e->word_break = cs->word_break;
    if (e->text_decoration_color == -1 && cs->text_decoration_color != -1)
        e->text_decoration_color = cs->text_decoration_color;
    if (e->text_decoration_style == 0 && cs->text_decoration_style != CSS_TDS_UNSET)
        e->text_decoration_style = cs->text_decoration_style;
    if (e->text_decoration_thickness == -1 && cs->text_decoration_thickness != -1)
        e->text_decoration_thickness = cs->text_decoration_thickness;
    if (e->tab_size == 0 && cs->tab_size > 0) e->tab_size = cs->tab_size;
    if (e->direction == 0 && cs->direction != CSS_DIR_UNSET) e->direction = cs->direction;
    if (e->font_variant == 0 && cs->font_variant != CSS_FV_UNSET) e->font_variant = cs->font_variant;
    if (e->list_style_pos == 0 && cs->list_style_pos != CSS_LP_UNSET) e->list_style_pos = cs->list_style_pos;
    if (e->image_rendering == 0 && cs->image_rendering != CSS_IR_UNSET)
        e->image_rendering = cs->image_rendering;
    /* caret-color: an explicit `auto` (CSS_LEN_AUTO) on a nearer ancestor is a
     * resolved value -- it stops the walk, and pv_set_text_ext maps it to -1. */
    if (e->caret_color == -1 && cs->caret_color != -1) e->caret_color = cs->caret_color;
    if (e->object_fit == 0 && cs->object_fit != CSS_OFI_UNSET) e->object_fit = cs->object_fit;
}

/* True if the resolved style declares any HORIZONTAL box property. */
static int css_has_hbox(const css_style *cs) {
    return cs->margin_left != CSS_LEN_UNSET || cs->margin_right != CSS_LEN_UNSET ||
           cs->pad_left   != CSS_LEN_UNSET || cs->pad_right   != CSS_LEN_UNSET ||
           cs->width != CSS_LEN_UNSET || cs->max_width != CSS_LEN_UNSET ||
           cs->width_pct > 0 || cs->max_width_pct > 0 ||
           cs->min_width > 0;
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
    /* Percentage caps stay symbolic (per-mille, both against the same containing
     * width, so the tighter per-mille IS the tighter cap); the painter resolves
     * px-vs-pct with bx_width_cap at layout time. */
    int wp = (cs->width_pct > 0) ? cs->width_pct : 0;
    if (cs->max_width_pct > 0 && (wp == 0 || cs->max_width_pct < wp))
        wp = cs->max_width_pct;
    out->l = (l > 0) ? l : 0;
    out->r = (r > 0) ? r : 0;
    out->w = (w != CSS_LEN_UNSET && w > 0) ? w : 0;
    out->w_pct = wp;
    out->center = (ml == CSS_LEN_AUTO && mr == CSS_LEN_AUTO &&
                   (out->w > 0 || wp > 0)) ? 1 : 0;
}

/* True if the resolved style declares any paintable box (border/padding/radius/
 * shadow/outline). box-sizing alone is not a box (it only matters with a width). */
/* A real (non-static) position makes a block box-carrying too, so its position/insets/
 * z-index ride the box-def tree (painted for relative; carried for the box engine). */
static int css_has_position(const css_style *cs) {
    return cs->position == CSS_POS_RELATIVE || cs->position == CSS_POS_ABSOLUTE ||
           cs->position == CSS_POS_FIXED   || cs->position == CSS_POS_STICKY;
}

static int css_has_boxdeco(const css_style *cs) {
    return cs->pad_top != CSS_LEN_UNSET || cs->pad_right != CSS_LEN_UNSET ||
           cs->pad_bottom != CSS_LEN_UNSET || cs->pad_left != CSS_LEN_UNSET ||
           cs->border_top_width != CSS_LEN_UNSET || cs->border_right_width != CSS_LEN_UNSET ||
           cs->border_bottom_width != CSS_LEN_UNSET || cs->border_left_width != CSS_LEN_UNSET ||
           cs->border_radius != CSS_LEN_UNSET || cs->box_shadow_color != -1 ||
           cs->outline_width != CSS_LEN_UNSET || css_has_position(cs) ||
           cs->visibility != CSS_VIS_UNSET || cs->overflow_x != CSS_OF_UNSET ||
           cs->overflow_y != CSS_OF_UNSET || cs->cursor != CSS_CUR_UNSET ||
           /* pointer-events / content-visibility:hidden alone make the box worth
            * tracking (hit-test skip / the visibility fold need the def). */
           cs->pointer_events != CSS_PE_UNSET ||
           cs->content_visibility == CSS_CV_HIDDEN ||
           /* Author vertical dimensions or aspect-ratio alone make the box worth
            * tracking (the painter needs them at open_box). */
           cs->height > 0 || cs->min_height > 0 || cs->max_height > 0 ||
           (cs->aspect_num > 0 && cs->aspect_den > 0) ||
           /* min-width alone too: a div with only `min-width:Npx` is a paintable
            * floor; the painter needs the box entry to honour it. */
           cs->min_width > 0 ||
           /* a linear-gradient background needs the box machinery to paint (a solid
            * background alone still rides the runs, unchanged). */
           cs->bg_grad_n >= 2 ||
           /* M1.1 increments 3-4 / M1.2: opacity, mix-blend-mode, isolation and
            * transform all need the box def to reach the painter's group-
            * compositing path (gui/browser_ui.c box_forms_stacking_context) --
            * without a box entry a plain `<div style="opacity:.5">` (no padding/
            * border/position alongside it) would silently never fade, exactly
            * the class of bug this whole box-registration gate exists to avoid
            * for every other author-CSS box property above. */
           cs->opacity != -1 || cs->mix_blend_mode != CSS_MB_UNSET ||
           cs->isolation != CSS_ISO_UNSET ||
           cs->transform_tx != CSS_LEN_UNSET || cs->transform_ty != CSS_LEN_UNSET ||
           cs->transform_sx != CSS_LEN_UNSET || cs->transform_sy != CSS_LEN_UNSET ||
           cs->transform_rotate != CSS_LEN_UNSET ||
           /* background-image: url(...) (2026-07-16): same reasoning as the
            * gradient case above -- a `<div style="background-image:url(x)">`
            * with no other box-triggering property alone still needs the box
            * def to reach the painter's image path. */
            cs->bg_image_url[0] != '\0' ||
            cs->bg_image_url2[0] != '\0' ||
            /* animation-duration (Phase R1): a box with an animation needs the box
             * def for the painter's animation-tick path. */
            cs->anim_duration_ms > 0 ||
            /* filter (Phase R3): needs box def for group compositing path */
            cs->filter_blur > 0 || cs->filter_grayscale > 0;
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

/* Box engine (Hito 23b-8 Step D): document-order registry of box-carrying block
 * nodes plus each box's resolved definition (decoration + parent link). A box's
 * block_id is its index here, so the painter can reconstruct the box tree. */
typedef struct pv_box_reg {
    const lxb_dom_node_t *node[PV_MAX_CONTAINERS];
    pv_box_def            def[PV_MAX_CONTAINERS];
    size_t                count;
} pv_box_reg;

/* Fills *d (decoration + hbox + bg; parent_id defaults to -1) from a resolved style.
 * Padding unset -> 0 (geometry default); the rest keep the css module's sentinels
 * (PV_LEN_UNSET width/radius/outline width, -1 colors, 0 the rest). */
static void boxdef_from_style(pv_box_def *d, const css_style *cs) {
    d->parent_id = -1;
    pv_box_info hb = { 0, 0, 0, 0, PV_LEN_UNSET, PV_LEN_UNSET, 0 };
    css_hbox_resolve(cs, &hb);
    d->box_l = hb.l; d->box_r = hb.r; d->box_w = hb.w; d->box_center = hb.center;
    d->box_w_pct = hb.w_pct;
    int bg = cs->background;
    d->bg_rgb = (bg >= 0) ? bg
              : (bg == CC_COLOR_TRANSPARENT) ? CC_COLOR_TRANSPARENT
              : (bg == CC_COLOR_CURRENT) ? -1
              : -1;
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
    d->outline_offset = cs->outline_offset;
    d->position = cs->position;
    d->inset_top = cs->inset_top; d->inset_right = cs->inset_right;
    d->inset_bottom = cs->inset_bottom; d->inset_left = cs->inset_left;
    d->z_index = cs->z_index;
    d->visibility = cs->visibility;
    /* content-visibility: hidden folds into visibility (skip paint, keep space --
     * the documented visibility:collapse simplification). An explicit visibility
     * on the element wins. */
    if (d->visibility == CSS_VIS_UNSET && cs->content_visibility == CSS_CV_HIDDEN)
        d->visibility = CSS_VIS_HIDDEN;
    d->overflow_x = cs->overflow_x; d->overflow_y = cs->overflow_y;
    d->cursor = cs->cursor;
    d->pointer_events = cs->pointer_events;
    d->aspect_num = cs->aspect_num; d->aspect_den = cs->aspect_den;
    /* Author vertical dimensions (this batch, 2026-07-10): height/min-height/
     * max-height in px, 0 unset; min-width too. A negative css_style value is the
     * CSS_LEN_AUTO sentinel for height/width -- the user-agent's auto-sizing is
     * always 0 here (the engine sizes boxes by their content). */
    d->box_h = (cs->height > 0) ? cs->height : 0;
    d->box_min_h = (cs->min_height > 0) ? cs->min_height : 0;
    d->box_max_h = (cs->max_height > 0) ? cs->max_height : 0;
    d->box_min_w = (cs->min_width > 0) ? cs->min_width : 0;
    d->grad_n = (cs->bg_grad_n >= 2) ? cs->bg_grad_n : 0;
    d->grad_angle = cs->bg_grad_angle;
    d->grad_c0 = cs->bg_grad_c[0]; d->grad_c1 = cs->bg_grad_c[1];
    d->grad_c2 = cs->bg_grad_c[2]; d->grad_c3 = cs->bg_grad_c[3];
    d->opacity = cs->opacity;
    d->mix_blend = cs->mix_blend_mode;
    d->isolation = cs->isolation;
    d->transform_tx = cs->transform_tx;
    d->transform_ty = cs->transform_ty;
    d->transform_sx = cs->transform_sx;
    d->transform_sy = cs->transform_sy;
    d->transform_rotate = cs->transform_rotate;
    /* background-image: url(...) (2026-07-16). Raw, unresolved -- render_doc.c
     * resolves it against the page origin and gates it like an <img>. */
    memcpy(d->bg_image_url, cs->bg_image_url, PV_BG_URL_MAX);
    d->bg_image_url[PV_BG_URL_MAX - 1] = '\0';
    memcpy(d->bg_image_url2, cs->bg_image_url2, PV_BG_URL_MAX);
    d->bg_image_url2[PV_BG_URL_MAX - 1] = '\0';
    for (int k = 0; k < 4; ++k) d->bg_grad_pos[k] = cs->bg_grad_pos[k];
    d->bg_grad_radial = cs->bg_grad_radial;
    d->bg_size = cs->bg_size;
    d->bg_repeat = cs->bg_repeat;
    d->anim_duration_ms = cs->anim_duration_ms;
    d->filter_blur = cs->filter_blur;
    d->filter_grayscale = cs->filter_grayscale;
    d->bg_pos_x = cs->bg_pos_x;
    d->bg_pos_y = cs->bg_pos_y;
    d->anim_iterations = cs->anim_iterations;
    d->anim_timing = cs->anim_timing;
    /* R8: ::before/::after generated content. Copy up to the field size. */
    if (cs->content_str[0] != '\0') {
        size_t clen = strlen(cs->content_str);
        if (clen >= sizeof d->content_str) clen = sizeof d->content_str - 1;
        memcpy(d->content_str, cs->content_str, clen);
        d->content_str[clen] = '\0';
    } else {
        d->content_str[0] = '\0';
    }
}

/* Id of node in the box registry, recording its decoration on first sight. -1 when
 * full. The parent link is stamped separately as the ancestor walk continues. */
static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs) {
    for (size_t i = 0; i < r->count; ++i)
        if (r->node[i] == node) return (int)i;
    if (r->count >= PV_MAX_CONTAINERS) return -1;
    size_t id = r->count++;
    r->node[id] = node;
    boxdef_from_style(&r->def[id], cs);
    return (int)id;
}

/* Per-document memo of cch_element_style() results, keyed by element pointer.
 * resolve_context()/in_hidden_subtree() call cch_element_style once per ANCESTOR
 * on every walk from a node up to `base`; a common ancestor (e.g. <body>, a
 * wrapper <div>) is revisited once per descendant text/element node, and each
 * revisit re-runs the full O(nsels) cascade from scratch. On a page with a real
 * stylesheet (hundreds to thousands of selectors -- see css.c's CSS_MAX_* caps)
 * that redundant work dominates page_view's runtime. The cache trades it for one
 * cascade per unique element plus a linear scan (bounded by the document's own
 * element count, normally far smaller than the selector count). Grows like
 * pv_node_map: a dynamic array, doubling, degrading to "no cache" (not a crash)
 * on OOM. */
typedef struct pv_style_cache {
    const lxb_dom_node_t **node;
    css_style             *style;
    size_t                 count, cap;
} pv_style_cache;

static int pv_style_cache_init(pv_style_cache *c) {
    c->cap = 64;
    c->node = (const lxb_dom_node_t **)calloc(c->cap, sizeof *c->node);
    c->style = (css_style *)calloc(c->cap, sizeof *c->style);
    if (c->node == NULL || c->style == NULL) {
        free(c->node); free(c->style);
        c->node = NULL; c->style = NULL; c->cap = 0;
        return -1;
    }
    c->count = 0;
    return 0;
}

static void pv_style_cache_free(pv_style_cache *c) {
    free(c->node); free(c->style);
    c->node = NULL; c->style = NULL; c->count = c->cap = 0;
}

/* cch_element_style(el, sheet), memoized in *cache. A NULL cache (OOM at init,
 * or a caller that opts out) simply calls through uncached -- never a hard
 * failure, matching every other degrade-on-OOM path in this module. */
static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
                                      pv_style_cache *cache) {
    const lxb_dom_node_t *node = (const lxb_dom_node_t *)el;
    if (cache != NULL) {
        for (size_t i = 0; i < cache->count; ++i)
            if (cache->node[i] == node) return cache->style[i];
    }
    css_style cs = cch_element_style(el, sheet);
    if (cache != NULL) {
        if (cache->count == cache->cap) {
            size_t ncap = cache->cap * 2;
            const lxb_dom_node_t **nn =
                (const lxb_dom_node_t **)realloc(cache->node, ncap * sizeof *nn);
            if (nn != NULL) cache->node = nn;
            css_style *ns = (css_style *)realloc(cache->style, ncap * sizeof *ns);
            if (ns != NULL) cache->style = ns;
            if (nn != NULL && ns != NULL) cache->cap = ncap;
        }
        if (cache->count < cache->cap) {
            cache->node[cache->count] = node;
            cache->style[cache->count] = cs;
            ++cache->count;
        }
    }
    return cs;
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
                            pv_text_ext *ext, pv_box_reg *box_reg,
                            pv_container_reg *float_reg, int *block_id_out,
                            pv_style_cache *style_cache) {
    *href = NULL; *href_len = 0; *block = base; *heading = 0; *fg = -1; *bg = -1;
    *bold = 0; *italic = 0; *align = CSS_ALIGN_UNSET; *font_scale = 0; *line_scale = 0;
    *deco = -1;
    *li = NULL; *list_depth = 0; *ordered = 0;
    cont->id = -1; cont->display = 0; cont->gap = 0;
    cont->justify = FX_JUSTIFY_START; cont->cols = 0;
    for (int gk = 0; gk < PV_GRID_TRACKS; ++gk) cont->col_w[gk] = 0;
    cont->col_span = 0;
    cont->grow = -1; cont->shrink = -1; cont->basis = CSS_LEN_UNSET;
    cont->order = CSS_LEN_UNSET; cont->direction = 0;
    cont->item = NULL;
    cont->float_side = 0; cont->float_id = -1; cont->float_clear = 0;
    cont->wrap = 0; cont->row_gap = -1; cont->align_items = 0; cont->align_self = 0;
    cont->align_content = 0; cont->justify_items = 0;
    cont->grid_rows = 0; cont->grid_flow = 0; cont->row_span = 0;
    box->l = 0; box->r = 0; box->w = 0; box->center = 0;
    box->mt = PV_LEN_UNSET; box->mb = PV_LEN_UNSET;
    pv_text_ext_reset(ext);
    *block_id_out = -1;
    int got_link = 0, got_block = 0, got_heading = 0, got_color = 0, got_bg = 0, got_cont = 0;
    int got_align = 0, got_fs = 0, got_lh = 0, got_deco = 0, got_hbox = 0, got_boxdeco = 0;
    int got_li = 0, got_list_kind = 0, got_float = 0;
    int prev_box_id = -1;  /* the box-carrying block seen one step more inner, for parent linking */
    int tag_bold = 0, tag_italic = 0;
    int css_bold = 0, css_italic = 0, got_css_bold = 0, got_css_italic = 0;
    /* Stage 3: the flex ITEM is the element visited just before the container on
     * this walk (its direct child on the run's path). Track the previous element's
     * flex values so the container hit can adopt them; text directly inside the
     * container (anonymous item) has no previous element and keeps the sentinels. */
    int prev_grow = -1, prev_shrink = -1;
    int prev_basis = CSS_LEN_UNSET, prev_order = CSS_LEN_UNSET;
    int prev_align_self = CSS_AK_UNSET;
    int prev_col_span = 0;
    int prev_row_span = 0;
    int have_prev_el = 0;
    const lxb_dom_node_t *prev_el = NULL;

    /* A text node's context starts at its parent element; an ELEMENT passed
     * directly (a collected table cell, an input, an image) starts at itself,
     * so its own rules (td{...}) and inline style= are not skipped. */
    const lxb_dom_node_t *start =
        (n->type == LXB_DOM_NODE_TYPE_ELEMENT) ? n : n->parent;
    for (const lxb_dom_node_t *p = start; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)p);
            lxb_tag_id_t t = lxb_dom_element_tag_id(el);
            css_style cs = cached_element_style(el, sheet, style_cache);
            pv_text_ext_merge(ext, &cs);

            /* UA default styles for specific elements */
            if (t == LXB_TAG_FIELDSET) {
                if (cs.border_top_width == CSS_LEN_UNSET || cs.border_top_width <= 0) {
                    cs.border_top_width = 1;  cs.border_right_width = 1;
                    cs.border_bottom_width = 1; cs.border_left_width = 1;
                    cs.border_top_style = CSS_BST_SOLID; cs.border_right_style = CSS_BST_SOLID;
                    cs.border_bottom_style = CSS_BST_SOLID; cs.border_left_style = CSS_BST_SOLID;
                    cs.border_top_color = 0xCCCCCC; cs.border_right_color = 0xCCCCCC;
                    cs.border_bottom_color = 0xCCCCCC; cs.border_left_color = 0xCCCCCC;
                }
                if (cs.pad_top == CSS_LEN_UNSET || cs.pad_top <= 0) {
                    cs.pad_top = 8; cs.pad_right = 8;
                    cs.pad_bottom = 8; cs.pad_left = 8;
                }
            }

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
            if (!got_block && causes_block_break(t, cs.display)) {
                *block = p; got_block = 1;
                /* The leaf block's OWN vertical margins override the UA (a wrapper's
                 * do not, so they are not duplicated across its inner blocks). */
                box->mt = (cs.margin_top != CSS_LEN_UNSET) ? cs.margin_top : PV_LEN_UNSET;
                box->mb = (cs.margin_bottom != CSS_LEN_UNSET) ? cs.margin_bottom : PV_LEN_UNSET;
                /* The leaf block's own `clear` ends any preceding float band (float.md). */
                cont->float_clear = (cs.clear != CSS_CLEAR_UNSET) ? cs.clear : 0;
            }
            /* Nearest floated self-or-ancestor block: its side + a document-order id so
             * the painter groups the runs of one floated element into one column. */
            if (!got_float && float_reg != NULL && is_block_like(t, cs.display) &&
                (cs.float_side == CSS_FLOAT_LEFT || cs.float_side == CSS_FLOAT_RIGHT)) {
                cont->float_side = cs.float_side;
                cont->float_id = container_id(float_reg, p);
                got_float = 1;
            }
            /* Horizontal box from the nearest block ancestor that declares one, so a
             * wrapper's max-width/centering/padding reaches all its descendants. */
            if (!got_hbox && is_block_like(t, cs.display) && css_has_hbox(&cs)) {
                css_hbox_resolve(&cs, box);
                got_hbox = 1;
            }
            /* Box engine (Hito 23b-8 Step D): EVERY box-carrying block ancestor is
             * registered so the box tree has an entry for it (text-less wrappers
             * included). The nearest one is the run's block_id (*block_id_out). As the
             * walk moves outward, each inner box's parent_id is stamped with the next
             * (outer) box found, so the registry holds the parent links. block_id is
             * structure; the decoration (on the box def) is author presentation that
             * render_doc gates behind caps.css. */
            if (box_reg != NULL && is_block_like(t, cs.display) && css_has_boxdeco(&cs)) {
                int bid = box_reg_id(box_reg, p, &cs);
                if (bid >= 0) {
                    if (!got_boxdeco) {
                        *block_id_out = bid;
                        got_boxdeco = 1;
                    }
                    if (prev_box_id >= 0)
                        box_reg->def[prev_box_id].parent_id = bid;
                    prev_box_id = bid;
                }
            }
            if (!got_color) {
                int c = -1;
                if (cs.color >= 0) c = cs.color;
                else if (t == LXB_TAG_FONT) c = font_color_attr(el);
                if (c >= 0) { *fg = c; got_color = 1; }
            }
            /* background-color does not inherit in CSS; in this flat model we take
             * the nearest ancestor's so a block's background shows behind its text.
             * The legacy bgcolor attribute is the fallback when no CSS won.
             * currentColor resolves to the element's own color (already resolved in
             * this pass), and transparent propagates as a sentinel. */
            if (!got_bg) {
                int b = -1;
                if (cs.background >= 0) b = cs.background;
                else if (cs.background == CC_COLOR_CURRENT && got_color) b = *fg;
                else if (cs.background == CC_COLOR_TRANSPARENT) b = CC_COLOR_TRANSPARENT;
                else b = bgcolor_attr(el);
                if (b >= 0 || b == CC_COLOR_TRANSPARENT) { *bg = b; got_bg = 1; }
            }
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
                if (cs.display == CSS_DISP_GRID)
                    for (int gk = 0; gk < PV_GRID_TRACKS; ++gk)
                        cont->col_w[gk] = cs.grid_col_w[gk];
                cont->id = container_id(reg, p);
                /* Stage 3: direction is the CONTAINER's; grow/shrink/basis/order are
                 * the ITEM's (the element one step more inner on this walk). */
                cont->direction = (cs.flex_direction != CSS_FD_UNSET) ? cs.flex_direction : 0;
                /* flex-wrap / row-gap / align-items are the CONTAINER's own; row-gap
                 * falls back to -1 (unset -> the presentation layer uses cont_gap). */
                cont->wrap = (cs.flex_wrap != CSS_FW_UNSET) ? cs.flex_wrap : 0;
                cont->row_gap = (cs.row_gap >= 0) ? cs.row_gap : -1;
                cont->align_items = (cs.align_items != CSS_AK_UNSET) ? cs.align_items : 0;
                /* 2026-07-12 batch: container alignment extras. */
                cont->align_content = (cs.align_content != CSS_AK_UNSET) ? cs.align_content : 0;
                cont->justify_items = (cs.justify_items != CSS_AK_UNSET) ? cs.justify_items : 0;
                /* Grid extras (grid container only). */
                if (cs.display == CSS_DISP_GRID) {
                    cont->grid_rows = (cs.grid_rows > 0) ? cs.grid_rows : 0;
                    cont->grid_flow = (cs.grid_auto_flow != CSS_GF_UNSET) ? cs.grid_auto_flow : 0;
                }
                if (have_prev_el) {
                    cont->grow = prev_grow; cont->shrink = prev_shrink;
                    cont->basis = prev_basis; cont->order = prev_order;
                    cont->align_self = prev_align_self;
                    cont->col_span = prev_col_span;
                    cont->row_span = prev_row_span;
                    cont->item = prev_el;
                }
                got_cont = 1;
            }
            prev_grow = cs.flex_grow; prev_shrink = cs.flex_shrink;
            prev_basis = cs.flex_basis; prev_order = cs.order;
            prev_align_self = cs.align_self;
            prev_col_span = (cs.grid_col_span > 0) ? cs.grid_col_span : 0;
            have_prev_el = 1;
            prev_el = p;
        }
        if (p == base) break;
    }

    *bold = got_css_bold ? css_bold : tag_bold;
    *italic = got_css_italic ? css_italic : tag_italic;
}

/* Collapses ASCII whitespace runs to a single space into a fresh buffer. */
static char *collapse_ws(const char *s, size_t n) {
    if (n == (size_t)-1) return NULL;
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

/* First candidate URL from a srcset attribute value ("url1 1x, url2 2x, ..."),
 * used as a fallback source when an <img> has no plain src -- the common shape
 * of responsive-image markup and of <picture><source srcset=...> (this parser
 * has no viewport/DPR to pick among candidates, so the first one is the
 * deterministic choice, matching how src is otherwise used verbatim). A regular
 * URL candidate ends at the first whitespace or comma (an optional density/width
 * descriptor, e.g. "2x", is separated from it by whitespace); a data: URL is
 * scanned to the first whitespace or the end of the string instead, since its
 * ";base64," marker contains a comma that is not a candidate separator. Returns
 * the span via *out and *out_len (points into srcset, not owned, not
 * NUL-terminated); *out stays NULL when srcset has no usable candidate. */
static void srcset_first_url(const lxb_char_t *srcset, size_t len,
                             const char **out, size_t *out_len) {
    *out = NULL;
    *out_len = 0;
    if (srcset == NULL) return;

    size_t i = 0;
    while (i < len && (srcset[i] == ' ' || srcset[i] == '\t' || srcset[i] == '\n'
                     || srcset[i] == '\r' || srcset[i] == ',')) ++i;
    if (i >= len) return;

    int is_data = (len - i >= 5)
        && (srcset[i]   == 'd' || srcset[i]   == 'D')
        && (srcset[i+1] == 'a' || srcset[i+1] == 'A')
        && (srcset[i+2] == 't' || srcset[i+2] == 'T')
        && (srcset[i+3] == 'a' || srcset[i+3] == 'A')
        && srcset[i+4]  == ':';

    size_t start = i;
    while (i < len) {
        lxb_char_t c = srcset[i];
        int is_ws = (c == ' ' || c == '\t' || c == '\n' || c == '\r');
        if (is_ws || (!is_data && c == ',')) break;
        ++i;
    }
    if (i > start) {
        *out = (const char *)(srcset + start);
        *out_len = i - start;
    }
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

/* Nonzero if a descendant text node sits under a non-rendered element (a <style>
 * or <script> nested in the collected subtree -- with run_js the parser keeps
 * <script> nodes in the tree, so a flattened cell or a <button> label would
 * otherwise paint raw CSS/JS source as content, as google.com's markup showed). */
static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL && p != el; p = p->parent) {
        if (p->type != LXB_DOM_NODE_TYPE_ELEMENT) continue;
        lxb_tag_id_t t = node_tag(p);
        if (t == LXB_TAG_SCRIPT || t == LXB_TAG_STYLE
            || t == LXB_TAG_HEAD || t == LXB_TAG_TITLE) return 1;
    }
    return 0;
}

/* Concatenates the descendant text of el into an owned NUL-terminated string (the
 * value of a <textarea> / the label of a <button> / a flattened table cell),
 * skipping text under non-rendered descendants. Never NULL on success. */
static char *collect_text(const lxb_dom_node_t *el) {
    size_t cap = 0, len = 0;
    char *buf = NULL;
    for (lxb_dom_node_t *n = el->first_child; n != NULL; n = node_next(n, el)) {
        if (n->type != LXB_DOM_NODE_TYPE_TEXT) continue;
        if (under_unrendered(n, el)) continue;
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
    if (ascii_ieq(type, "checkbox")) return PV_IN_CHECKBOX;
    if (ascii_ieq(type, "radio"))    return PV_IN_RADIO;
    return PV_IN_TEXT;
}

/* Fills owned label/name/value for a control element and its classified type,
 * plus the checked state (-1, 0, 1) and the pipe-separated options string for
 * <select>. Returns 0, or -1 on OOM (caller frees whatever is non-NULL). */
static int describe_control(lxb_dom_element_t *el, lxb_tag_id_t tag,
                            const lxb_dom_node_t *node, pv_input_type *out_type,
                            char **out_label, char **out_name, char **out_value,
                            int *out_checked, char **out_select_opts) {
    *out_label = NULL; *out_name = NULL; *out_value = NULL;
    *out_checked = -1; *out_select_opts = NULL;
    *out_type = PV_IN_TEXT;

    if (tag == LXB_TAG_SELECT) {
        *out_type = PV_IN_SELECT;
        *out_name = attr_dup(el, "name", 4);
        /* Build pipe-separated "value||label||value||label" from <option> children */
        size_t opts_cap = 256, opts_len = 0;
        char *opts = (char *)malloc(opts_cap);
        if (opts == NULL) return -1;
        opts[0] = '\0';
        for (lxb_dom_node_t *ch = node->first_child; ch != NULL; ch = ch->next) {
            if (ch->type != LXB_DOM_NODE_TYPE_ELEMENT || node_tag(ch) != LXB_TAG_OPTION)
                continue;
            lxb_dom_element_t *opt_el = lxb_dom_interface_element(ch);
            /* value attribute, or the option's text content */
            size_t vl = 0;
            const lxb_char_t *vattr =
                lxb_dom_element_get_attribute(opt_el, (const lxb_char_t *)"value", 5, &vl);
            char *opt_val = NULL;
            if (vattr != NULL && vl > 0) {
                opt_val = dup_n((const char *)vattr, vl);
            } else {
                opt_val = collect_text(ch);
            }
            if (opt_val == NULL) continue;
            char *opt_label = collect_text(ch);
            if (opt_label == NULL) { free(opt_val); continue; }
            size_t need = strlen(opt_val) + 2 + strlen(opt_label) + 2;
            if (opts_len + need >= opts_cap) {
                size_t ncap = opts_cap * 2;
                if (ncap < opts_len + need + 1) ncap = opts_len + need + 1;
                char *g = (char *)realloc(opts, ncap);
                if (g == NULL) { free(opt_val); free(opt_label); break; }
                opts = g; opts_cap = ncap;
            }
            size_t space = opts_cap - opts_len;
            if (space == 0) { free(opt_val); free(opt_label); continue; }
            int r = snprintf(opts + opts_len, space, "%s||%s||", opt_val, opt_label);
            if (r < 0 || (size_t)r >= space) { free(opt_val); free(opt_label); continue; }
            opts_len += (size_t)r;
            free(opt_val); free(opt_label);
        }
        /* Remove trailing || if present */
        if (opts_len >= 2 && memcmp(opts + opts_len - 2, "||", 2) == 0) {
            opts_len -= 2;
            opts[opts_len] = '\0';
        }
        *out_select_opts = opts;
        *out_label = dup_n("", 0);
        char *ph = attr_dup(el, "placeholder", 11);
        if (ph != NULL) { free(*out_label); *out_label = ph; }
        /* Default value: first selected option or the first option */
        char *sel = collect_text(node);
        if (sel != NULL && sel[0] != '\0') {
            char *trimmed = collapse_ws(sel, strlen(sel));
            free(sel); sel = trimmed;
        }
        *out_value = (sel != NULL) ? sel : dup_n("", 0);
        if (*out_label == NULL || *out_value == NULL) return -1;
        return 0;
    }

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
    /* checked attribute for checkbox/radio */
    if (*out_type == PV_IN_CHECKBOX || *out_type == PV_IN_RADIO) {
        size_t cl = 0;
        const lxb_char_t *ch =
            lxb_dom_element_get_attribute(el, (const lxb_char_t *)"checked", 7, &cl);
        *out_checked = (ch != NULL) ? 1 : 0;
    }
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

/* Nearest <tr> ancestor of n up to base, or NULL. Used so each table ROW is its own
 * block: the first cell of a row breaks to a new line, the rest share it, so a table
 * that overflows the grid engine still degrades to one row per line (not one blob). */
static const lxb_dom_node_t *nearest_row(const lxb_dom_node_t *n, const lxb_dom_node_t *base) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT && node_tag(p) == LXB_TAG_TR) return p;
        if (p == base) break;
    }
    return NULL;
}

/* Nonzero if cell has a descendant <table>: it is then a structural CONTAINER, not a
 * leaf cell. Only leaf cells (no nested table) are collected as one text run; a
 * container cell is walked so the inner table's cells are collected separately. This
 * is what stops a legacy table-in-table layout (e.g. Hacker News: the story list is a
 * <table> nested inside a <td> of the outer table) from flattening its whole subtree
 * into one giant run. Early-exit on the first nested table (bounded by the subtree). */
static int cell_has_nested_table(const lxb_dom_node_t *cell) {
    for (lxb_dom_node_t *k = cell->first_child; k != NULL; k = node_next(k, cell)) {
        if (k->type == LXB_DOM_NODE_TYPE_ELEMENT && node_tag(k) == LXB_TAG_TABLE) return 1;
    }
    return 0;
}

/* Pre-order successor that does NOT descend into n's children (used to skip an
 * already-decided subtree during the table scan). */
static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root) {
    while (n != root && n->next == NULL) {
        if (n->parent == NULL) return NULL;
        n = n->parent;
    }
    if (n == root) return NULL;
    return n->next;
}

/* First <a href> element in the cell's subtree, with *count receiving how many
 * such anchors exist, capped at 2 (only none / exactly-one / several matters). */
static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count) {
    const lxb_dom_node_t *first = NULL;
    *count = 0;
    for (lxb_dom_node_t *k = cell->first_child; k != NULL; k = node_next(k, cell)) {
        if (k->type != LXB_DOM_NODE_TYPE_ELEMENT || node_tag(k) != LXB_TAG_A) continue;
        size_t hl = 0;
        const lxb_char_t *h = lxb_dom_element_get_attribute(
            lxb_dom_interface_element(k), (const lxb_char_t *)"href", 4, &hl);
        if (h == NULL || hl == 0) continue;
        if (first == NULL) first = k;
        if (++*count >= 2) break;
    }
    return first;
}

/* Nonzero when the table is navigation/layout rather than data: some leaf cell of
 * ITS OWN (nested tables decide for themselves; their subtrees are skipped) holds
 * two or more anchors. Flattening such a cell into one collected run would destroy
 * its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows the table's cells through the normal walk instead of gridding them. */
static int table_prefers_flow(const lxb_dom_node_t *table) {
    lxb_dom_node_t *n = table->first_child;
    while (n != NULL) {
        int skip_children = 0;
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(n);
            if (t == LXB_TAG_TABLE) {
                skip_children = 1;
            } else if ((t == LXB_TAG_TD || t == LXB_TAG_TH)
                       && !cell_has_nested_table(n)) {
                int nanch = 0;
                (void)cell_anchors(n, &nanch);
                if (nanch >= 2) return 1;
                skip_children = 1; /* the whole leaf cell was just scanned */
            }
        }
        n = skip_children ? next_skip(n, (const lxb_dom_node_t *)table)
                          : node_next(n, table);
    }
    return 0;
}

/* Cache of the per-table flow decision (a table subtree is scanned at most once,
 * anti-DoS). Registry full => grid (the previous behaviour), bounded fail-closed. */
typedef struct pv_flow_reg {
    const lxb_dom_node_t *node[PV_MAX_CONTAINERS];
    unsigned char         flow[PV_MAX_CONTAINERS];
    size_t                count;
} pv_flow_reg;

static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table) {
    if (table == NULL) return 0;
    for (size_t i = 0; i < fr->count; ++i)
        if (fr->node[i] == table) return fr->flow[i];
    if (fr->count >= PV_MAX_CONTAINERS) return 0;
    int f = table_prefers_flow(table) ? 1 : 0;
    fr->node[fr->count] = table;
    fr->flow[fr->count] = (unsigned char)f;
    fr->count++;
    return f;
}

/* Nonzero if n's NEAREST <td>/<th> ancestor (up to base) is a COLLECTED leaf cell:
 * its text was already emitted as one collected cell run, so the normal walk must
 * not re-emit it. A container cell (one wrapping a nested table) and a cell of a
 * FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their text/links are emitted normally. */
static int in_collected_cell(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                             pv_flow_reg *fr) {
    for (const lxb_dom_node_t *p = n->parent; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(p);
            if (t == LXB_TAG_TD || t == LXB_TAG_TH) {
                if (cell_has_nested_table(p)) return 0;
                if (flow_table(fr, nearest_table(p, base))) return 0;
                return 1;
            }
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
                             const css_sheet *sheet, pv_style_cache *style_cache) {
    for (const lxb_dom_node_t *p = n; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)p);
            if (cached_element_style(el, sheet, style_cache).display == CSS_DISP_NONE) return 1;
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

/* Nonzero if n or any ancestor up to base is inside a <details> without an `open`
 * attribute and n is NOT inside its <summary> (the summary is always visible).
 * Used to suppress content of collapsed disclosure widgets. */
static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base) {
    int passed_summary = 0;
    for (const lxb_dom_node_t *p = n; p != NULL; p = p->parent) {
        if (p->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(p);
            if (t == LXB_TAG_SUMMARY) passed_summary = 1;
            if (t == LXB_TAG_DETAILS) {
                lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)p);
                int has_open = lxb_dom_element_has_attribute(el,
                    (const lxb_char_t *)"open", 4);
                if (!has_open && !passed_summary) return 1; /* closed, hide */
                /* Open details or inside summary: keep walking up to catch outer closed details. */
                passed_summary = 0;
            }
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
    return pv_build_styled(doc, js_enabled, reader, prefers_dark, NULL, 0, out);
}

pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                          int prefers_dark, const char *extern_css, size_t extern_len,
                          pv_view **out) {
    if (doc == NULL || out == NULL) return PV_ERR_NULL_ARG;
    *out = NULL;

    pv_view *v = pv_new();
    if (v == NULL) return PV_ERR_OOM;

    lxb_dom_node_t *root = (lxb_dom_node_t *)hp_document_root(doc);
    if (root == NULL) { *out = v; return PV_OK; } /* empty document */

    lxb_dom_node_t *body = find_body(root);
    lxb_dom_node_t *base = (body != NULL) ? body : root;

    /* Keystone (Stage 0): build a document-order element map from the root so that
     * every emitted run can carry the same element id that dom_build assigns. This
     * makes pv_run.node_id agree with dom_node_id even though page_view walks from
     * `base` (usually body) while the DOM index counts from root. */
    pv_node_map node_map;
    if (pv_node_map_build(&node_map, root) != 0) { pv_free(v); return PV_ERR_OOM; }

    /* Parse the document's <style> blocks once into a bounded sheet (pure: it never
     * fetches and drops url()/@-rules). A NULL sheet is treated as empty by the css
     * module, so OOM here degrades to "no author CSS", not a failure. */
    size_t style_len = 0;
    char *style_text = collect_style_text(root, &style_len);
    /* Pre-fetched external sheets (Hito 27) precede the document's own <style>
     * text: document-order approximation, so at equal specificity the page's
     * inline sheet (later in the text) wins the cascade. The combined text stays
     * capped at PV_MAX_STYLE_BYTES; OOM degrades to document styles only. */
    if (extern_css != NULL && extern_len != 0) {
        if (extern_len > PV_MAX_STYLE_BYTES) extern_len = PV_MAX_STYLE_BYTES;
        size_t dlen = style_len;
        if (dlen > PV_MAX_STYLE_BYTES - extern_len) dlen = PV_MAX_STYLE_BYTES - extern_len;
        if (extern_len != (size_t)-1 && dlen != (size_t)-1) {
            char *comb = (char *)malloc(extern_len + 1 + dlen + 1);
            if (comb != NULL) {
                memcpy(comb, extern_css, extern_len);
                comb[extern_len] = '\n';
                if (dlen != 0) memcpy(comb + extern_len + 1, style_text, dlen);
                comb[extern_len + 1 + dlen] = '\0';
                free(style_text);
                style_text = comb;
                style_len = extern_len + 1 + dlen;
            }
        }
    }
    css_sheet *sheet = NULL;
    /* @media gated against the user's color scheme (auto dark mode) and a fixed,
     * normalized desktop width (no real viewport size leaks). Screen context. */
    css_media media = { prefers_dark ? 1 : 0, 0, CSS_MEDIA_DEFAULT_WIDTH };
    (void)css_parse_media(style_text, style_len, &media, &sheet);
    free(style_text);

    const lxb_dom_node_t *prev_block = NULL;
    const lxb_dom_node_t *prev_li = NULL;  /* last <li> seen, to mark each item once */
    int pending_break = 0;
    int prev_float_id = -1;  /* adjacent floats in the same group suppress block_break */
    form_table forms = { NULL, 0, 0 };
    pv_status rc = PV_OK;
    pv_container_reg reg = { { NULL }, 0 };  /* flex/grid containers, document order */
    pv_container_reg float_reg = { { NULL }, 0 };  /* floated elements, document order */
    pv_box_reg box_reg = { { NULL }, { { 0 } }, 0 };  /* box-carrying blocks + their defs */
    pv_flow_reg flowreg = { { NULL }, { 0 }, 0 };  /* per-table flow-vs-grid decisions */
    pv_item_track items = { { NULL }, { 0 } };  /* per-container item ordinals */
    int last_was_gap = 0;  /* dedupe for inter-cell separator runs of flowed tables */
    pv_style_cache cache;  /* memoized cch_element_style() per element (see above) */
    (void)pv_style_cache_init(&cache);  /* on OOM: cap stays 0, every lookup degrades to uncached */

    for (lxb_dom_node_t *n = base; n != NULL; n = node_next(n, base)) {
        if (n->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_tag_id_t t = node_tag(n);
            if (t == LXB_TAG_BR || t == LXB_TAG_HR) { pending_break = 1; continue; }

            if (t == LXB_TAG_FORM) {
                if (forms_add(&forms, n) != 0) { rc = PV_ERR_OOM; goto cleanup; }
                continue;
            }

            /* Skip elements inside a collapsed <details> (no `open` attribute).
             * The <summary> is always visible, but its children are already text
             * nodes that pass through the filter below. */
            if (in_closed_details_subtree(n, base)) continue;

            /* A table cell of a DATA table becomes one collected text run annotated
             * as a grid item: the table is a grid container (cont_id), its column
             * count is the widest row, and each cell is one column. This reuses the
             * flex/grid layout engine (layout_container/box_tree) so cells align
             * across rows. <th> is bold. The cell's inner text nodes are suppressed
             * below (in_collected_cell) so they are not re-emitted. A container cell
             * (nested table) and every cell of a FLOW table (one with a multi-link
             * cell: flattening would destroy the links -- the Hacker News case) are
             * WALKED instead: their text/links flow through the normal path, each
             * <tr> a block, with a separator run between adjacent walked cells. */
            if ((t == LXB_TAG_TD || t == LXB_TAG_TH)
                && !in_skipped_subtree(n, base, js_enabled)
                && !in_collected_cell(n, base, &flowreg)
                && !in_hidden_subtree(n, base, sheet, &cache)
                && !(reader && in_boilerplate_subtree(n, base))) {
                const lxb_dom_node_t *table = nearest_table(n, base);
                if (cell_has_nested_table(n) || flow_table(&flowreg, table)) {
                    /* Walked cell. If it continues the row block already open, emit
                     * one inter-cell gap so cell texts do not fuse ("1."+"Title"). */
                    const lxb_dom_node_t *row = nearest_row(n, base);
                    const lxb_dom_node_t *tblk = (row != NULL) ? row : table;
                    if (!pending_break && tblk != NULL && tblk == prev_block
                        && !last_was_gap) {
                        pv_status st = pv_append(v, PV_TEXT, 0, 0, " ", NULL);
                        if (st != PV_OK) { rc = st; goto cleanup; }
                        last_was_gap = 1;
                    }
                    continue;
                }
                int cols = (table != NULL) ? table_columns(table) : 1;
                int cid = (table != NULL) ? container_id(&reg, table) : -1;

                char *raw = collect_text(n);
                if (raw == NULL) { rc = PV_ERR_OOM; goto cleanup; }
                char *cell = collapse_ws(raw, strlen(raw));
                free(raw);
                if (cell == NULL) { rc = PV_ERR_OOM; goto cleanup; }

                /* Each table ROW is one block: the first cell of a row breaks from the
                 * prior row, the rest of the row share it. The grid (cont_id on the
                 * table) still aligns columns when it fits the engine; when a table
                 * overflows the engine it degrades to one row per line, not one blob. */
                const lxb_dom_node_t *row = nearest_row(n, base);
                const lxb_dom_node_t *tblk = (row != NULL) ? row : (table != NULL ? table : n);
                int brk = pending_break || (tblk != prev_block);
                pending_break = 0;
                prev_block = tblk;

                /* A cell whose subtree holds exactly ONE anchor is collected as a
                 * LINK run: clickable without breaking column alignment (still one
                 * run = one grid item). Several anchors cannot happen here (the
                 * table would be flowed). */
                int nanch = 0;
                const lxb_dom_node_t *a1 = cell_anchors(n, &nanch);
                char *cell_href = NULL;
                if (nanch == 1 && a1 != NULL) {
                    size_t hl = 0;
                    const lxb_char_t *h = lxb_dom_element_get_attribute(
                        lxb_dom_interface_element((lxb_dom_node_t *)a1),
                        (const lxb_char_t *)"href", 4, &hl);
                    if (h != NULL && hl > 0) cell_href = dup_n((const char *)h, hl);
                }

                /* The collected run carries the cell's author presentation too:
                 * resolve the context AT the cell element (its own td/th rules,
                 * plus row/table inheritance — zebra tr:nth-child backgrounds,
                 * tr:first-child bold...). Geometry stays the table grid's: the
                 * container annotation below overrides the resolved one, and the
                 * author box/block-decoration are not applied to grid items. */
                const char *cu_href = NULL;
                size_t cu_hl = 0;
                const lxb_dom_node_t *cu_block = NULL;
                const lxb_dom_node_t *cu_li = NULL;
                int cu_heading = 0, cfg = -1, cbg = -1, cbold = 0, citalic = 0;
                int calign = 0, cfs = 0, clh = 0, cdeco = -1;
                int cu_depth = 0, cu_ordered = 0, cu_bdeco = -1;
                pv_cont_info cu_cont;
                pv_box_info cu_box;
                pv_text_ext cext;
                resolve_context(n, base, sheet, &cu_href, &cu_hl, &cu_block,
                                &cu_heading, &cfg, &cbg, &cbold, &citalic,
                                &calign, &cfs, &clh, &cdeco,
                                &cu_li, &cu_depth, &cu_ordered,
                                &reg, &cu_cont, &cu_box, &cext,
                                &box_reg, &float_reg, &cu_bdeco, &cache);

                /* An empty cell still occupies its column. */
                pv_status st = pv_append(v, (cell_href != NULL) ? PV_LINK : PV_TEXT,
                                         0, brk,
                                         (cell[0] != '\0') ? cell : " ", cell_href);
                free(cell);
                free(cell_href);
                if (st != PV_OK) { rc = st; goto cleanup; }
                last_was_gap = 0;
                pv_set_emphasis(v, (t == LXB_TAG_TH) ? 1 : cbold, citalic);
                pv_set_color(v, cfg);
                pv_set_bgcolor(v, cbg);
                pv_set_text_style(v, calign, cfs, clh, cdeco);
                pv_set_text_ext(v, &cext);
                pv_set_container(v, cid, BX_DISPLAY_GRID, 0, FX_JUSTIFY_START, cols,
                                 0, -1, CSS_AK_UNSET);
                /* Every collected cell is its own grid item (the cell node is the
                 * item identity), so item-grouping downstream never merges cells. */
                pv_set_cont_item(v, item_ordinal(&items, cid, n));
                pv_set_float(v, cu_cont.float_side, cu_cont.float_id, cu_cont.float_clear);
                pv_set_node_id(v, pv_node_map_id(&node_map, n));
                continue;
            }

            if ((t == LXB_TAG_INPUT || t == LXB_TAG_TEXTAREA || t == LXB_TAG_BUTTON
                 || t == LXB_TAG_SELECT)
                && !in_skipped_subtree(n, base, js_enabled)
                && !in_hidden_subtree(n, base, sheet, &cache)
                && !(reader && in_boilerplate_subtree(n, base))) {
                lxb_dom_element_t *el = lxb_dom_interface_element(n);
                pv_input_type itype;
                char *label = NULL, *name = NULL, *value = NULL;

                const char *unused_href = NULL;
                size_t unused_hl = 0;
                const lxb_dom_node_t *block = NULL;
                int heading = 0, unused_fg = -1, unused_bg = -1;
                int unused_bold = 0, unused_italic = 0, unused_align = 0, unused_fs = 0, unused_lh = 0, unused_deco = 0;
                const lxb_dom_node_t *unused_li = NULL;
                int unused_depth = 0, unused_ordered = 0;
                pv_cont_info unused_cont;
                pv_box_info unused_box;
                pv_text_ext ctl_ext;
                int unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &ctl_ext,
                                &box_reg, &float_reg, &unused_bdeco, &cache);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                int fidx = form_for(&forms, n, base);
                const char *action = (fidx >= 0) ? forms.recs[fidx].action : NULL;
                int method = (fidx >= 0) ? forms.recs[fidx].method : PV_METHOD_GET;

                /* Extract checked and options too for checkbox/radio/select */
                int ictl_checked = -1;
                char *ictl_opts = NULL;
                if (describe_control(el, t, n, &itype, &label, &name, &value,
                                     &ictl_checked, &ictl_opts) != 0) {
                    free(label); free(name); free(value); free(ictl_opts);
                    rc = PV_ERR_OOM; goto cleanup;
                }
                pv_status st = pv_append_input(v, heading, brk, itype, label,
                                               name, value, action, fidx, method);
                free(label); free(name); free(value);
                if (st != PV_OK) { free(ictl_opts); rc = st; goto cleanup; }
                if (ictl_checked >= 0) pv_set_input_checked(v, ictl_checked);
                if (ictl_opts != NULL) {
                    pv_set_input_select_opts(v, ictl_opts);
                    free(ictl_opts);
                }
                /* The resolved inherited text extensions ride the input run too:
                 * caret_color tints the caret of the focused control (2026-07-10). */
                pv_set_text_ext(v, &ctl_ext);
                pv_set_node_id(v, pv_node_map_id(&node_map, n));
                continue;
            }

            /* <progress> and <meter> — native bar widgets */
            if ((t == LXB_TAG_PROGRESS || t == LXB_TAG_METER)
                && !in_skipped_subtree(n, base, js_enabled)
                && !in_hidden_subtree(n, base, sheet, &cache)
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
                pv_text_ext ctl_ext;
                int unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &ctl_ext,
                                &box_reg, &float_reg, &unused_bdeco, &cache);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                size_t vl = 0, ml = 0;
                const lxb_char_t *vattr = lxb_dom_element_get_attribute(el,
                    (const lxb_char_t *)"value", 5, &vl);
                const lxb_char_t *mattr = lxb_dom_element_get_attribute(el,
                    (const lxb_char_t *)"max", 3, &ml);

                char *val_str = (vattr != NULL && vl > 0)
                    ? dup_n((const char *)vattr, vl) : dup_n("0", 1);
                char *max_str = (mattr != NULL && ml > 0)
                    ? dup_n((const char *)mattr, ml) : dup_n("1", 1);

                if (t == LXB_TAG_METER) {
                    /* Encode min/max/low/high/optimum as comma-separated */
                    size_t minl = 0, lowl = 0, highl = 0, optl = 0;
                    const lxb_char_t *minattr = lxb_dom_element_get_attribute(el,
                        (const lxb_char_t *)"min", 3, &minl);
                    const lxb_char_t *lowattr = lxb_dom_element_get_attribute(el,
                        (const lxb_char_t *)"low", 3, &lowl);
                    const lxb_char_t *highattr = lxb_dom_element_get_attribute(el,
                        (const lxb_char_t *)"high", 4, &highl);
                    const lxb_char_t *optattr = lxb_dom_element_get_attribute(el,
                        (const lxb_char_t *)"optimum", 7, &optl);
                    char meta[256];
                    int nw = snprintf(meta, sizeof meta, "%s,%s,%s,%s,%s",
                        (minattr && minl > 0) ? (const char *)minattr : "0",
                        max_str,
                        (lowattr && lowl > 0) ? (const char *)lowattr : "",
                        (highattr && highl > 0) ? (const char *)highattr : "",
                        (optattr && optl > 0) ? (const char *)optattr : "");
                    (void)nw;
                    free(max_str);
                    max_str = dup_n(meta, strlen(meta));
                    if (max_str == NULL) { free(val_str); rc = PV_ERR_OOM; goto cleanup; }
                }

                pv_input_type itype = (t == LXB_TAG_METER) ? PV_IN_METER : PV_IN_PROGRESS;
                pv_status st = pv_append_input(v, heading, brk, itype,
                    max_str, NULL, val_str, NULL, -1, 0);
                free(val_str); free(max_str);
                if (st != PV_OK) { rc = st; goto cleanup; }
                pv_set_text_ext(v, &ctl_ext);
                pv_set_node_id(v, pv_node_map_id(&node_map, n));
                continue;
            }

            /* <legend> inside a <fieldset> */
            if (t == LXB_TAG_LEGEND
                && !in_skipped_subtree(n, base, js_enabled)
                && !in_hidden_subtree(n, base, sheet, &cache)
                && !(reader && in_boilerplate_subtree(n, base))) {
                char *legend_text = collect_text(n);
                if (legend_text == NULL) { rc = PV_ERR_OOM; goto cleanup; }
                char *collapsed = collapse_ws(legend_text, strlen(legend_text));
                free(legend_text);
                if (collapsed == NULL) { rc = PV_ERR_OOM; goto cleanup; }

                const char *unused_href = NULL;
                size_t unused_hl = 0;
                const lxb_dom_node_t *block = NULL;
                int heading = 0, unused_fg = -1, unused_bg = -1;
                int unused_bold = 0, unused_italic = 0, unused_align = 0, unused_fs = 0, unused_lh = 0, unused_deco = 0;
                const lxb_dom_node_t *unused_li = NULL;
                int unused_depth = 0, unused_ordered = 0;
                pv_cont_info unused_cont;
                pv_box_info unused_box;
                pv_text_ext ctl_ext;
                int unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &ctl_ext,
                                &box_reg, &float_reg, &unused_bdeco, &cache);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                pv_status st = pv_append_input(v, heading, brk, PV_IN_LEGEND,
                    collapsed, NULL, collapsed, NULL, -1, 0);
                free(collapsed);
                if (st != PV_OK) { rc = st; goto cleanup; }
                pv_set_text_ext(v, &ctl_ext);
                pv_set_node_id(v, pv_node_map_id(&node_map, n));
                continue;
            }

            if (t == LXB_TAG_IMG && !in_skipped_subtree(n, base, js_enabled)
                && !in_hidden_subtree(n, base, sheet, &cache)
                && !(reader && in_boilerplate_subtree(n, base))) {
                lxb_dom_element_t *el = lxb_dom_interface_element(n);
                size_t sl = 0;
                const lxb_char_t *src =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"src", 3, &sl);
                const char *img_src = (const char *)src;
                size_t img_src_len = sl;
                if (img_src == NULL || img_src_len == 0) {
                    /* No plain src: fall back to the first srcset candidate, the
                     * common shape of responsive-image markup (a bare src is not
                     * guaranteed even inside <picture>, whose own <source
                     * srcset=...> siblings this loop does not visit at all). */
                    size_t ssl = 0;
                    const lxb_char_t *srcset = lxb_dom_element_get_attribute(
                        el, (const lxb_char_t *)"srcset", 6, &ssl);
                    srcset_first_url(srcset, ssl, &img_src, &img_src_len);
                    if (img_src == NULL) continue; /* no usable source: nothing to show */
                }

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
                pv_text_ext img_ext;
                int unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &img_ext,
                                &box_reg, &float_reg, &unused_bdeco, &cache);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                char *src_dup = dup_n(img_src, img_src_len);
                if (src_dup == NULL) { rc = PV_ERR_OOM; goto cleanup; }
                char *alt_dup = (alt != NULL) ? collapse_ws((const char *)alt, al) : dup_n("", 0);
                if (alt_dup == NULL) { free(src_dup); rc = PV_ERR_OOM; goto cleanup; }

                pv_status st = pv_append_image(v, heading, brk, alt_dup, src_dup, iw, ih);
                free(src_dup);
                free(alt_dup);
                if (st != PV_OK) { rc = st; goto cleanup; }
                /* The resolved inherited text extensions ride the image run too:
                 * image_rendering picks the paint scaling filter (2026-07-10). */
                pv_set_text_ext(v, &img_ext);
                pv_set_node_id(v, pv_node_map_id(&node_map, n));
            } else if ((t == LXB_TAG_VIDEO || t == LXB_TAG_AUDIO)
                       && !in_skipped_subtree(n, base, js_enabled)
                       && !in_hidden_subtree(n, base, sheet, &cache)
                       && !(reader && in_boilerplate_subtree(n, base))) {
                lxb_dom_element_t *el = lxb_dom_interface_element(n);
                size_t sl = 0;
                const lxb_char_t *src =
                    lxb_dom_element_get_attribute(el, (const lxb_char_t *)"src", 3, &sl);
                /* If no direct src, try the first <source> child */
                if ((src == NULL || sl == 0)) {
                    for (lxb_dom_node_t *ch = n->first_child; ch != NULL; ch = ch->next) {
                        if (ch->type == LXB_DOM_NODE_TYPE_ELEMENT
                            && node_tag(ch) == LXB_TAG_SOURCE) {
                            lxb_dom_element_t *sel = lxb_dom_interface_element(ch);
                            src = lxb_dom_element_get_attribute(sel,
                                (const lxb_char_t *)"src", 3, &sl);
                            if (src != NULL && sl > 0) break;
                        }
                    }
                }
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

                size_t pl = 0;
                const lxb_char_t *poster = NULL;
                if (t == LXB_TAG_VIDEO) {
                    poster = lxb_dom_element_get_attribute(el,
                        (const lxb_char_t *)"poster", 6, &pl);
                }

                const char *unused_href = NULL;
                size_t unused_hl = 0;
                const lxb_dom_node_t *block = NULL;
                int heading = 0, unused_fg = -1, unused_bg = -1;
                int unused_bold = 0, unused_italic = 0, unused_align = 0, unused_fs = 0, unused_lh = 0, unused_deco = 0;
                const lxb_dom_node_t *unused_li = NULL;
                int unused_depth = 0, unused_ordered = 0;
                pv_cont_info unused_cont;
                pv_box_info unused_box;
                pv_text_ext vid_ext;
                int unused_bdeco;
                resolve_context(n, base, sheet, &unused_href, &unused_hl, &block, &heading,
                                &unused_fg, &unused_bg, &unused_bold, &unused_italic,
                                &unused_align, &unused_fs, &unused_lh, &unused_deco,
                                &unused_li, &unused_depth, &unused_ordered,
                                &reg, &unused_cont, &unused_box, &vid_ext,
                                &box_reg, &float_reg, &unused_bdeco, &cache);
                int brk = pending_break || (block != prev_block);
                pending_break = 0;
                prev_block = block;

                char *src_dup = dup_n((const char *)src, sl);
                if (src_dup == NULL) { rc = PV_ERR_OOM; goto cleanup; }
                char *alt_dup = (alt != NULL) ? collapse_ws((const char *)alt, al) : dup_n("", 0);
                if (alt_dup == NULL) { free(src_dup); rc = PV_ERR_OOM; goto cleanup; }
                char *poster_dup = (poster != NULL && pl > 0)
                                   ? dup_n((const char *)poster, pl) : NULL;
                if (poster != NULL && pl > 0 && poster_dup == NULL) {
                    free(src_dup); free(alt_dup); rc = PV_ERR_OOM; goto cleanup;
                }

                pv_status st = pv_append_video(v, heading, brk, alt_dup,
                                                src_dup, poster_dup, iw, ih);
                free(src_dup);
                free(alt_dup);
                free(poster_dup);
                if (st != PV_OK) { rc = st; goto cleanup; }
                pv_set_node_id(v, pv_node_map_id(&node_map, n));
            }
            continue;
        }
        if (n->type != LXB_DOM_NODE_TYPE_TEXT) continue;
        if (in_skipped_subtree(n, base, js_enabled)) continue;
        if (in_collected_cell(n, base, &flowreg)) continue; /* emitted as a collected cell run */
        if (in_hidden_subtree(n, base, sheet, &cache)) continue; /* display:none */
        if (in_closed_details_subtree(n, base)) continue; /* collapsed <details> */
        if (reader && in_boilerplate_subtree(n, base)) continue; /* distraction-free */

        lxb_dom_text_t *txt = lxb_dom_interface_text(n);
        const char *raw = (const char *)txt->char_data.data.data;
        size_t raw_len = txt->char_data.data.length;
        if (raw == NULL || raw_len == 0) continue;

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
        int bdeco;
        resolve_context(n, base, sheet, &href, &href_len, &block, &heading, &fg, &bg,
                        &bold, &italic, &align, &font_scale, &line_scale, &text_decoration,
                        &li, &list_depth, &ordered, &reg, &cont, &box, &ext,
                        &box_reg, &float_reg, &bdeco, &cache);

        /* Pre-like blocks (white-space: pre / pre-wrap / pre-line) preserve
         * whitespace: the HTML parser keeps the source tabs and newlines, and
         * page_view must NOT collapse them. CSS tab-size then expands the tabs
         * at paint time (flow_text). Other blocks collapse runs of any
         * whitespace to a single space (the spec). A <pre> tag's UA default
         * of white-space:pre is honored too (a pre with no CSS still preserves
         * whitespace; otherwise the parser keeps tabs that we then collapse). */
        int is_pre_like = (ext.white_space == CSS_WS_PRE ||
                           ext.white_space == CSS_WS_PRE_WRAP ||
                           ext.white_space == CSS_WS_PRE_LINE ||
                           (block != NULL && node_tag(block) == LXB_TAG_PRE));
        char *collapsed = is_pre_like ? dup_n(raw, raw_len) : collapse_ws(raw, raw_len);
        if (collapsed == NULL) { rc = PV_ERR_OOM; goto cleanup; }
        if (collapsed[0] == '\0') { free(collapsed); continue; }

        /* UA-defaults for <pre>: white-space:pre to preserve whitespace,
         * font-family:monospace as required by the HTML spec. */
        if (block != NULL && node_tag(block) == LXB_TAG_PRE) {
            if (ext.white_space == 0)
                ext.white_space = CSS_WS_PRE;
            if (ext.font_family == CSS_FF_UNSET)
                ext.font_family = CSS_FF_MONO;
        }

        /* R8: ::before generated content. Emit once per element: check if the
         * text node's parent element has non-empty content_str in its resolved
         * style (the ::before content). We compare directly against the block
         * (most common) and also check the parent inline element. */
        if (n->parent != NULL && n->parent->type == LXB_DOM_NODE_TYPE_ELEMENT) {
            lxb_dom_element_t *pel = lxb_dom_interface_element(n->parent);
            css_style pcs = cached_element_style(pel, sheet, &cache);
            if (pcs.content_str[0] != '\0') {
                int fresh = 1;
                for (size_t bi = 0; bi < box_reg.count; ++bi) {
                    if (box_reg.node[bi] == n->parent) {
                        if (box_reg.def[bi].content_str[0] == '\0') fresh = 0;
                        else box_reg.def[bi].content_str[0] = '\0';
                        break;
                    }
                }
                if (fresh) {
                    char *content_dup = dup_n(pcs.content_str, strlen(pcs.content_str));
                    if (content_dup == NULL) { free(collapsed); rc = PV_ERR_OOM; goto cleanup; }
                    pv_status st = pv_append(v, PV_TEXT, 0, pending_break ? 1 : 0,
                                             content_dup, NULL);
                    free(content_dup);
                    if (st != PV_OK) { free(collapsed); rc = st; goto cleanup; }
                    pv_set_node_id(v, pv_node_map_id(&node_map, n->parent));
                    pv_set_color(v, pcs.color);
                    pv_set_bgcolor(v, pcs.background);
                    pv_set_emphasis(v, pcs.bold > 0, pcs.italic > 0);
                    pending_break = 0;
                }
            }
        }

        int brk = pending_break || (block != prev_block);
        pending_break = 0;
        prev_block = block;

        /* <pre> elements split each source newline into its own run with a
         * block_break, so ASCII art and code blocks render line-by-line.
         * The UA white-space:pre preserves the raw \n chars; here they become
         * structural breaks instead of flowing as one long nowrap line. */
        int is_pre_tag = (is_pre_like && block != NULL && node_tag(block) == LXB_TAG_PRE);
        if (is_pre_tag) {
            char *start = collapsed;
            int first = 1;
            while (*start != '\0') {
                char *nl = strchr(start, '\n');
                size_t len = nl ? (size_t)(nl - start) : strlen(start);
                if (len > 0 && start[len - 1] == '\r') --len;

                char *href_dup2 = NULL;
                if (href != NULL) {
                    href_dup2 = dup_n(href, href_len);
                    if (href_dup2 == NULL) { free(collapsed); rc = PV_ERR_OOM; goto cleanup; }
                }
                char *line = dup_n(start, len);
                if (line == NULL) { free(href_dup2); free(collapsed); rc = PV_ERR_OOM; goto cleanup; }

                int line_brk = first ? brk : 1;
                first = 0;
                pv_status st = pv_append(v, href_dup2 != NULL ? PV_LINK : PV_TEXT,
                                         heading, line_brk, line, href_dup2);
                free(line);
                free(href_dup2);
                if (st != PV_OK) { free(collapsed); rc = st; goto cleanup; }

                pv_set_emphasis(v, bold, italic);
                pv_set_indent(v, list_depth);
                pv_set_color(v, fg);
                pv_set_bgcolor(v, bg);
                pv_set_text_style(v, align, font_scale, line_scale, text_decoration);
                pv_set_container(v, cont.id, cont.display, cont.gap, cont.justify, cont.cols,
                                 cont.wrap, cont.row_gap, cont.align_items);
                pv_set_grid(v, cont.col_w, PV_GRID_TRACKS, cont.col_span);
                pv_set_flex(v, cont.grow, cont.shrink, cont.basis, cont.order, cont.direction,
                           cont.align_self);
                pv_set_cont_item(v, item_ordinal(&items, cont.id, cont.item));
                pv_set_float(v, cont.float_side, cont.float_id, cont.float_clear);
                pv_set_box(v, box.l, box.r, box.w, box.center, box.mt, box.mb);
                pv_set_box_pct(v, box.w_pct);
                pv_set_text_ext(v, &ext);
                pv_set_block_id(v, bdeco);
                pv_set_node_id(v, pv_node_map_id(&node_map, n->parent));

                if (nl == NULL) break;
                start = nl + 1;
            }
            last_was_gap = 0;
            free(collapsed);
            continue;
        }

        /* Prepend the list marker ("* "/"N. ") to the first text run of each <li>,
         * once per item. The marker is plain ASCII text, so it inherits the run's
         * style and needs no special painting; the GUI indents the whole item by
         * list_depth. A run that is only whitespace (e.g. between a nested </ul> and
         * its </li>) carries no content, so it never claims the marker. */
        int has_content = 0;
        for (const char *c = collapsed; *c != '\0'; ++c) {
            if (*c != ' ') { has_content = 1; break; }
        }
        /* Whitespace-only text inside a heading is source formatting, never content:
         * a heading's visual identity comes from its child elements (links, spans).
         * Emitting an empty heading block for a \n between <h2> and <a> creates
         * a gap equal to the heading's font size + margins that has no text in it,
         * and on article-heavy sites that means dozens of blank lines. */
        if (heading != 0 && !has_content) {
            free(collapsed);
            continue;
        }
        /* CSS anonymous-box rules for whitespace-only text: (a) one that would START
         * a block generates no box at all — each source newline between <div>s used
         * to paint an empty line (Wikipedia: 412 such runs = ~11000px of blank page);
         * the break stays pending so the block's first real content still opens it.
         * (b) One directly inside a flex/grid container creates no anonymous item
         * even mid-block (source newlines between items must not become columns).
         * A mid-block separator space between two inlines is content and IS emitted;
         * the flowed-table inter-cell separator is appended elsewhere (no break). */
        if (!has_content) {
            int direct_in_cont = cont.id >= 0 && (size_t)cont.id < reg.count &&
                                  n->parent == reg.node[cont.id];
            if (brk || direct_in_cont) {
                if (brk) pending_break = 1;
                free(collapsed);
                continue;
            }
        }
        char *marked = NULL;
        if (li != NULL && li != prev_li && has_content && ext.list_style != CSS_LS_NONE) {
            char mk[32];
            list_marker(ordered, li, ext.list_style, mk, sizeof mk);
            size_t ml = strlen(mk), cl = strlen(collapsed);
            if (ml == (size_t)-1 || cl == (size_t)-1) { free(collapsed); rc = PV_ERR_OOM; goto cleanup; }
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
        last_was_gap = 0;
        /* Adjacent floated elements in the same float group (e.g. <li> links in a
         * navigation bar) flow side-by-side as one float column; suppress the block
         * break so the next one does not stack as a separate vertical block. Applied
         * AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.float_id >= 0) {
            if (cont.float_id == prev_float_id)
                v->runs[v->count - 1].block_break = 0;
            prev_float_id = cont.float_id;
        } else {
            prev_float_id = -1;
        }
        pv_set_emphasis(v, bold, italic);
        pv_set_indent(v, list_depth);
        pv_set_color(v, fg);
        pv_set_bgcolor(v, bg);
        pv_set_text_style(v, align, font_scale, line_scale, text_decoration);
        pv_set_container(v, cont.id, cont.display, cont.gap, cont.justify, cont.cols,
                          cont.wrap, cont.row_gap, cont.align_items);
        pv_set_grid(v, cont.col_w, PV_GRID_TRACKS, cont.col_span);
        pv_set_flex(v, cont.grow, cont.shrink, cont.basis, cont.order, cont.direction,
                   cont.align_self);
        pv_set_cont_item(v, item_ordinal(&items, cont.id, cont.item));
        pv_set_float(v, cont.float_side, cont.float_id, cont.float_clear);
        pv_set_box(v, box.l, box.r, box.w, box.center, box.mt, box.mb);
        pv_set_box_pct(v, box.w_pct);
        pv_set_text_ext(v, &ext);
        pv_set_block_id(v, bdeco);
        pv_set_node_id(v, pv_node_map_id(&node_map, n->parent));
    }

    /* Box engine (Step D): publish the box tree. box_reg holds one def per
     * box-carrying block in document order (id == index) with parent links resolved
     * during the ancestor walks; copy them into the view in id order. */
    for (size_t bi = 0; bi < box_reg.count; ++bi) {
        pv_status st = pv_add_box_def(v, &box_reg.def[bi]);
        if (st != PV_OK) { rc = st; goto cleanup; }
    }

    *out = v;
    forms_free(&forms);
    css_free(sheet);
    pv_node_map_free(&node_map);
    pv_style_cache_free(&cache);
    return PV_OK;

cleanup:
    forms_free(&forms);
    css_free(sheet);
    pv_node_map_free(&node_map);
    pv_style_cache_free(&cache);
    pv_free(v);
    return rc;
}
