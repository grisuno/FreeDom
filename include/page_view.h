#ifndef FREEDOM_PAGE_VIEW_H
#define FREEDOM_PAGE_VIEW_H

#include <stddef.h>
#include <stdint.h>

#include "dom.h"
#include "html_parse.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * page_view — a flat, inert "display list" extracted from the inert DOM.
 *
 * The renderer must not walk the hostile DOM directly, and plain text loses the
 * structure a reader needs (headings, links, block boundaries). page_view turns
 * the sanitised tree into an ordered list of inline runs carrying just enough
 * structure to lay out and paint: a kind (text or link), a heading level, a
 * block-break flag, the run text, and a link target.
 *
 * It is data with provenance, never instruction: a link's href is stored but
 * never followed here; navigation re-validates it through secure_fetch.
 *
 * Run text is normalised to well-formed UTF-8 (invalid bytes -> '?') so the text
 * renderer can never be poisoned by a malformed or legacy-encoded document.
 *
 * The Lexbor backend stays encapsulated: no lxb_* type appears here.
 * See spec/page_view.md for the full contract.
 */

typedef enum pv_status {
    PV_OK = 0,
    PV_ERR_NULL_ARG,  /* a required pointer argument was NULL */
    PV_ERR_OOM,       /* allocation failed */
    PV_ERR_INTERNAL   /* backend returned an unexpected state */
} pv_status;

/* Sentinel for an unset author box vertical-margin override (box_mt/box_mb): the
 * presentation layer then uses the user-agent margin. Matches CSS_LEN_UNSET. */
#define PV_LEN_UNSET (-2147483647 - 1)

typedef enum pv_kind {
    PV_TEXT = 0,   /* inline text */
    PV_LINK = 1,   /* inline text that is a hyperlink (href is set) */
    PV_IMAGE = 2,  /* an <img>: src is set, text holds the alt text */
    PV_INPUT = 3   /* a form control (<input>/<textarea>/<button>): see pv_input_type */
} pv_kind;

/* Class of a PV_INPUT control. Drives how the GUI paints and submits it. Unknown
 * input types collapse to PV_IN_TEXT (a one-line editable box). */
typedef enum pv_input_type {
    PV_IN_TEXT = 0,   /* text/search/email/url/tel/number/...: one-line editable box */
    PV_IN_PASSWORD,   /* password: editable, masked when painted */
    PV_IN_TEXTAREA,   /* <textarea>: editable (one-line box for now); value = its content */
    PV_IN_HIDDEN,     /* hidden: not painted; value still submitted */
    PV_IN_SUBMIT,     /* submit button (triggers the owning form) */
    PV_IN_BUTTON      /* non-submitting button (button/reset): painted, inert */
} pv_input_type;

/* Form method carried on a PV_INPUT run (denormalised from the owning <form>). */
typedef enum pv_form_method {
    PV_METHOD_GET = 0,
    PV_METHOD_POST = 1
} pv_form_method;

/* One inline run in document order. text is owned, NUL-terminated, valid UTF-8
 * (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated
 * for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for PV_IMAGE
 * runs (the image URL, data with provenance, never fetched here), NULL otherwise;
 * img_w/img_h carry the declared <img> dimensions in pixels, or -1 when unknown.
 * An image is never a link, so href and src are never both set. fg_rgb carries the
 * author foreground color (nearest inline style "color:" or <font color>) packed
 * as 0xRRGGBB, or -1 when none/unparseable; it is presentation data the renderer
 * applies only when author CSS is enabled. */
typedef struct pv_run {
    pv_kind kind;
    int     heading;      /* 0 = body text; 1..6 = inside h1..h6 */
    int     bold;         /* nonzero: inside <b>/<strong>/<th> (inline emphasis) */
    int     italic;       /* nonzero: inside <i>/<em> (inline emphasis) */
    int     indent;       /* list nesting depth (count of <ul>/<ol> ancestors); 0 if none */
    int     block_break;  /* nonzero: a block boundary precedes this run */
    char   *text;         /* PV_INPUT: the placeholder (text) or button label */
    char   *href;         /* PV_LINK target; PV_INPUT: the owning form's raw action */
    char   *src;          /* PV_IMAGE only: image URL; NULL otherwise */
    int     img_w;        /* PV_IMAGE declared width in px, or -1 if unknown */
    int     img_h;        /* PV_IMAGE declared height in px, or -1 if unknown */
    int     fg_rgb;       /* author color packed 0xRRGGBB, or -1 if none */
    int     bg_rgb;       /* author background-color packed 0xRRGGBB, or -1 if none */
    /* Author text presentation resolved from <style> + inline style= (the css
     * module). text_align is a css_align (0 unset, 1 left, 2 center, 3 right,
     * 4 justify); font_scale is a font-size percent (100 = normal) or 0 (unset);
     * line_scale is a line-height percent of the natural line box (0 = unset).
     * All are presentation: render_doc applies them only with caps.css, exactly
     * like fg_rgb/bg_rgb. Defaults: text_align 0, font_scale 0, line_scale 0. */
    int     text_align;
    int     font_scale;
    int     line_scale;
    /* Author text-decoration (OR of CSS_DECO_UNDERLINE/LINE_THROUGH/OVERLINE; 0 =
     * none, -1 = unset). Presentation: render_doc applies it only with caps.css,
     * like fg_rgb/bg_rgb. Resolved from the nearest ancestor that sets it. */
    int     text_decoration;
    /* Author text-decoration sub-properties: color (0xRRGGBB / -1 unset, falls back
     * to fg_rgb at paint time), style (css_text_decoration_style, 0 unset -> solid)
     * and thickness (px, -1 unset, 0 from-font). Same caps.css gate as
     * text_decoration. Resolved from the nearest ancestor that sets them. */
    int     text_decoration_color;
    int     text_decoration_style;
    int     text_decoration_thickness;
    /* Author text-presentation extensions (Hito 23b-6), each resolved from the
     * nearest ancestor that sets it (they inherit). Presentation: render_doc applies
     * them only with caps.css. Defaults (no author value): font_family 0 (unset ->
     * sans), text_transform 0 (none), letter_spacing/word_spacing/text_indent
     * PV_LEN_UNSET, shadow_dx/dy 0 + shadow_color -1 (no shadow), opacity -1 (opaque),
     * valign 0 (baseline), white_space 0 (normal/wrap). */
    int     font_family;     /* css_font_family */
    int     text_transform;  /* css_text_transform */
    int     letter_spacing;  /* signed px, PV_LEN_UNSET unset */
    int     word_spacing;    /* signed px, PV_LEN_UNSET unset */
    int     shadow_dx, shadow_dy; /* text-shadow offsets px */
    int     shadow_color;    /* 0xRRGGBB, or -1 (no shadow) */
    int     opacity;         /* percent 0..100, or -1 (unset/opaque) */
    int     valign;          /* css_valign */
    int     text_indent;     /* signed px first-line indent, PV_LEN_UNSET unset */
    int     white_space;     /* css_white_space */
    /* More text-presentation extensions (this batch, 2026-07-10): each resolved from
     * the nearest ancestor that sets it (they inherit). Presentation: render_doc
     * applies them only with caps.css. Defaults: tab_size 0 (unset -> 8 in <pre>),
     * direction 0 (unset -> LTR), font_variant 0 (unset -> normal), list_style_pos
     * 0 (unset -> outside). */
    int     tab_size;        /* number of spaces for a tab character; 0 unset */
    int     direction;       /* css_direction */
    int     font_variant;    /* css_font_variant (small-caps etc.) */
    int     list_style_pos;  /* css_list_pos (inside/outside) */
    /* text-overflow / word-break (see css_word_break for the word-break/overflow-wrap/
     * word-wrap unification), each resolved from the nearest ancestor that sets it
     * (they inherit, like white_space). Presentation: render_doc applies them only
     * with caps.css. Defaults: 0 (unset). */
    int     text_overflow;   /* css_text_overflow */
    int     word_break;      /* css_word_break */
    /* Nearest author flex/grid container ancestor (display:flex|grid in style), so
     * the presentation layer can lay the container's children out with box_tree.
     * cont_id groups runs of one container (-1 = none); cont_display is the
     * bx_display (flex/grid); the rest are the container's parsed params. Defaults:
     * cont_id -1, the others 0. Carried by render_doc regardless of caps.css
     * (layout is structure; only author colors are gated). */
    int     cont_id;      /* container group id in document order, or -1 */
    int     cont_display; /* bx_display of the container (flex/grid), or 0 */
    int     cont_gap;     /* container gap in px (>= 0) */
    int     cont_justify; /* fx_justify of the container */
    int     cont_cols;    /* grid column count (>= 1 for grid), or 0 */
    /* Stage 3a: flex per-item values from the BLOCK element's own css_style (the
     * flex item = the nearest block ancestor of this run). Like cont_*, these are
     * layout STRUCTURE (not author styling), carried regardless of caps.css. The
     * GUI's layout_container feeds them to bt_node.grow/shrink/basis. Defaults:
     * flex_grow -1 (unset -> CSS 0), flex_shrink -1 (unset -> CSS 1.0),
     * flex_basis CSS_LEN_UNSET (unset -> auto -> content size), flex_order
     * CSS_LEN_UNSET (unset -> 0), flex_direction 0 (unset -> row). */
    int     flex_grow;    /* x100 (1.0 -> 100), or -1 (unset) */
    int     flex_shrink;  /* x100 (1.0 -> 100), or -1 (unset) */
    int     flex_basis;   /* px >= 0, CSS_LEN_AUTO, or CSS_LEN_UNSET */
    int     flex_order;   /* signed, or CSS_LEN_UNSET (unset -> 0) */
    int     flex_direction; /* css_flex_direction, 0 (unset -> row) */
    /* Container-item identity: ordinal of the container's direct child this run
     * belongs to (the CSS flex/grid item). Consecutive runs sharing (cont_id,
     * cont_item) are fragments of ONE item and flow together in one cell; each
     * collected table cell keeps its own ordinal. Structure like cont_*. -1 = no
     * container. */
    int     cont_item;
    /* flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM). Structure
     * like the rest of the cont_ and flex_ fields, carried regardless of caps.css.
     * Defaults:
     * cont_wrap 0 (unset -> nowrap), cont_row_gap -1 (unset -> falls back to
     * cont_gap), cont_align_items/flex_align_self 0 (CSS_AK_UNSET -> start). */
    int     cont_wrap;        /* css_flex_wrap of the container */
    int     cont_row_gap;     /* px >= 0, or -1 (unset) */
    int     cont_align_items; /* css_align_kw of the container (align-items) */
    int     flex_align_self;  /* css_align_kw of the ITEM (align-self); AUTO/UNSET
                               * defer to cont_align_items */
    /* Float layout (spec/float.md). float_side is the css_float of the nearest floated
     * self-or-ancestor block (0 none, 2 left, 3 right — the css_float values); float_id
     * groups the runs of ONE floated element in document order (-1 = not in a float);
     * float_clear is this run's own block's css_clear (0 unset .. 4 both). Structure
     * like cont_*, carried regardless of caps.css. Defaults: 0 / -1 / 0. */
    int     float_side;
    int     float_id;
    int     float_clear;
    /* Author box model pre-resolved to px (Hito 23b-3), gated by caps.css. box_l/
     * box_r are the left/right insets (padding + non-auto margin of that side);
     * box_w is the content-width cap (min width/max-width, 0 = none); box_center is
     * 1 for `margin: 0 auto`; box_mt/box_mb override the block's top/bottom margin,
     * or PV_LEN_UNSET to keep the user-agent margin. Defaults: 0/0/0/0/UNSET/UNSET. */
    int     box_l;
    int     box_r;
    int     box_w;
    int     box_center;
    int     box_mt;
    int     box_mb;
    /* Keystone (Stage 0): stable document-order element identity. node_id is the
     * dom_node_id of the source element for this run, assigned by the same pre-order
     * walk that dom_build uses, so it agrees with the JS sandbox's index. It is
     * STRUCTURE (like block_id/cont_id), carried regardless of caps.css. DOM_NODE_NONE
     * when the run has no single source element (e.g. an anonymous text run outside a
     * block, or a synthesized notice). */
    dom_node_id node_id;
    /* Box engine (Hito 23b-8): block_id groups the runs of one block-level box in
     * document order (-1 = no box-carrying block). It is STRUCTURE, carried by
     * render_doc regardless of caps.css (like cont_id). The box's decoration and
     * parent_id live on the box-definition list (pv_box_def, indexed by block_id) —
     * NOT duplicated per run — so a text-less wrapper box is representable and the
     * decoration is described once. See pv_box_def. */
    int     block_id;
    /* form controls (PV_INPUT only; defaults: type 0, name/value NULL, form_id -1,
     * method GET). name/value carry the submitted bytes verbatim (not whitespace
     * collapsed); form_id groups controls of the same <form> (-1 = no form). */
    int     input_type;   /* pv_input_type */
    char   *name;         /* control name, or NULL */
    char   *value;        /* control current/default value, or NULL */
    int     form_id;      /* owning-form group id in document order, or -1 */
    int     form_method;  /* pv_form_method of the owning form */
} pv_run;

/* Box engine (Hito 23b-8 Step D): one entry of the box-definition TREE. The box
 * decoration and the parent link live here, not on each run, so a box is described
 * once (extinguishing the Step A per-run duplication) and a TEXT-LESS wrapper box
 * (one that owns no direct run, e.g. a card div whose only child is a body div) is
 * still representable. A box's block_id IS its index in pv_view.boxes; a run carries
 * only its block_id (which box it belongs to) and finds its parent via
 * boxes[block_id].parent_id. parent_id is the block_id of the nearest box-carrying
 * block ancestor, or -1 for a root box. The decoration fields mirror the Step A
 * sentinels exactly (border widths/radius/outline width PV_LEN_UNSET, colors -1,
 * the rest 0). The whole list is author presentation: render_doc copies it only with
 * caps.css (empty otherwise -> default render byte-identical). */
typedef struct pv_box_def {
    int parent_id;
    /* Horizontal box placement of this box (resolved like a run's box_l/r/w/center,
     * Hito 23b-3): l/r insets = padding + non-auto margin px; w = width/max-width cap
     * (0 = none); center = margin:0 auto. Carried on the def so the painter can place
     * a box (incl. a text-less wrapper) without a run to read it from. */
    int box_l, box_r, box_w, box_center;
    /* Author vertical dimensions (this batch, 2026-07-10): height/min-height/max-height
     * in px, 0 unset (the engine paints min-height as a floor, max-height as a cap
     * on the painted box, and a fixed height only when no content-driven size wins).
     * Like the rest of the box model, gated by caps.css upstream. */
    int box_h;          /* height (px > 0), or 0 unset */
    int box_min_h;      /* min-height (px >= 0), or 0 unset */
    int box_max_h;      /* max-height (px > 0), or 0 unset */
    int box_min_w;      /* min-width  (px >= 0), or 0 unset */
    int bg_rgb;   /* author background-color of the box (0xRRGGBB), or -1 */
    int box_sizing;
    int pad_t, pad_r, pad_b, pad_l;
    int bord_tw, bord_rw, bord_bw, bord_lw;
    int bord_ts, bord_rs, bord_bs, bord_ls;
    int bord_tc, bord_rc, bord_bc, bord_lc;
    int border_radius;
    int bsh_dx, bsh_dy, bsh_blur, bsh_spread, bsh_color, bsh_inset;
    int outline_w, outline_style, outline_color;
    /* outline-offset: distance in px between the border edge and the outline (CSS:
     * 0 by default, or any length). -1 = unset. Painted as an outset of the outline
     * rect (positive pushes the outline further out, negative pulls it inside). */
    int outline_offset;
    /* Positioning (Hito 23b-8 follow-up). position is a css_position (0 unset/static,
     * RELATIVE/ABSOLUTE/FIXED/STICKY). inset_* are top/right/bottom/left in px, or
     * CSS_LEN_UNSET (unset) / CSS_LEN_AUTO. z_index is signed, or CSS_LEN_UNSET. v1
     * paints only position:relative (an in-flow offset, reader-safe); out-of-flow
     * absolute/fixed/sticky + z-index stacking are deferred to the box engine (they
     * need out-of-flow placement, which for a reader browser is also a policy call --
     * see spec/box_engine.md). The values are still carried so the box engine and the
     * debug_dom dump can see them. */
    int position;
    int inset_top, inset_right, inset_bottom, inset_left;
    int z_index;
    /* visibility / overflow / cursor (not inherited, like border/position -- read
     * from the box's own resolved style). visibility gates painting of this box and
     * everything it encloses while still reserving its layout space (see
     * css_visibility). overflow_x/_y clip in-flow rows and positioned boxes to
     * ancestor overflow:hidden rects (2026-07-09). cursor drives the hover cursor
     * shape (see css_cursor). */
    int visibility;
    int overflow_x, overflow_y;
    int cursor;
    /* aspect-ratio (numerator/denominator x1000, both 0 = unset/auto) */
    int aspect_num, aspect_den;
} pv_box_def;

typedef struct pv_view {
    pv_run    *runs;
    size_t     count;
    size_t     cap;
    pv_box_def *boxes;   /* the box tree (Step D); boxes[block_id] describes a box */
    size_t      nbox;
    size_t      boxcap;
} pv_view;

/* Builds the display list from an already-parsed, sanitised document.
 * doc == NULL / out == NULL => PV_ERR_NULL_ARG.
 * On PV_OK, *out must be released with pv_free. An empty document yields a valid
 * view with count == 0. */
pv_status pv_build(const hp_document *doc, pv_view **out); /* == pv_build_ex(doc, 0, out) */

/* As pv_build, but js_enabled selects <noscript> handling: when 0 (JS off, the
 * default) the <noscript> fallback content IS rendered (a no-JS browser shows it);
 * when nonzero (JS allowed for this page) the <noscript> subtree is suppressed. */
pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out);

/* As pv_build_ex, plus a distraction-free (reader) flag and the user's color-scheme
 * preference (prefers_dark != 0 selects dark for the author's
 * @media(prefers-color-scheme) rules). When reader is nonzero, boilerplate subtrees
 * (<nav>/<header>/<footer>/<aside>) are skipped so only the main content is emitted;
 * author CSS is still resolved (the presentation layer decides whether to apply it).
 * pv_build_ex is pv_build_full with reader == 0 and prefers_dark == 0. */
pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                        int prefers_dark, pv_view **out);

/* As pv_build_full, plus a pre-fetched external stylesheet text (Hito 27).
 * extern_css/extern_len (NULL/0 => none: byte-identical to pv_build_full) is the
 * concatenated body of the page's <link rel=stylesheet> sheets, fetched by the
 * TRUSTED parent under full network policy (spec/tab.md §8) -- page_view stays
 * pure and never fetches. The external text precedes the document's own <style>
 * blocks in the parsed sheet (document-order approximation: at equal specificity
 * the page's <style> wins), and the combined text is capped (anti-DoS). Hostile
 * input: it flows through the same bounded, fail-closed css parser (url()/@import
 * dropped -- it can never phone home). */
pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                          int prefers_dark, const char *extern_css, size_t extern_len,
                          pv_view **out);

/* Allocates an empty view (used by the IPC deserialiser to rebuild a view on the
 * receiving side). Returns NULL on allocation failure. */
pv_view *pv_new(void);

/* Appends one text or link run, copying text (required) and href (NULL for
 * non-links). text is normalised to valid UTF-8; the image fields are cleared
 * (src=NULL, img_w=img_h=-1). Returns PV_OK or PV_ERR_OOM / PV_ERR_NULL_ARG. */
pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    const char *text, const char *href);

/* Appends one PV_IMAGE run. src is required (an image with no source is not
 * representable); alt may be NULL (stored as the empty string). Both alt and src
 * are copied and normalised to valid UTF-8 so they are safe to paint. w/h are the
 * declared dimensions, or -1 when unknown. Returns PV_OK or PV_ERR_OOM /
 * PV_ERR_NULL_ARG. */
pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src, int w, int h);

/* Appends one PV_INPUT run (a form control). text is the placeholder/label (may be
 * NULL -> ""); name/value are the control identity and value (may be NULL); action
 * is the owning form's raw action href (may be NULL); form_id groups controls of a
 * form (-1 if none); method is the form's pv_form_method. text is normalised to
 * valid UTF-8 (display); name/value/action are copied verbatim (submitted bytes /
 * resolved later). Returns PV_OK or PV_ERR_OOM / PV_ERR_NULL_ARG. */
pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_input_type input_type, const char *text,
                          const char *name, const char *value,
                          const char *action, int form_id, int method);

/* Sets the author foreground color (packed 0xRRGGBB, or -1 for none) on the most
 * recently appended run. No-op when the view is empty or NULL. Both append helpers
 * default a new run's color to -1, so this only needs calling when a color is
 * present. */
/* Sets the inline emphasis flags (bold from <b>/<strong>/<th>, italic from
 * <i>/<em>) on the most recently appended run. No-op on an empty or NULL view.
 * Both append helpers default a new run to bold=0, italic=0. Emphasis is structure
 * (which glyph weight/slant), not author styling, so it is carried by default and
 * is not gated by caps.css. */
void pv_set_emphasis(pv_view *v, int bold, int italic);

/* Sets the list nesting depth (count of <ul>/<ol> ancestors) on the most recently
 * appended run. No-op on an empty or NULL view; defaults to 0. The list marker
 * ("* " or "N. ") is prepended to the run text by pv_build, not here. List
 * structure is carried by default (not gated by caps.css). */
void pv_set_indent(pv_view *v, int indent);

void pv_set_color(pv_view *v, int fg_rgb);

/* Sets the author background-color (packed 0xRRGGBB, or -1 for none) on the most
 * recently appended run. No-op when the view is empty or NULL. Both append helpers
 * default a new run's bg_rgb to -1. background-color does not inherit in CSS; in
 * this flat model pv_build resolves it from the nearest ancestor that sets one, so
 * a block's background shows behind its text runs. */
void pv_set_bgcolor(pv_view *v, int bg_rgb);

/* Sets the author text presentation (text_align as a css_align, font_scale as a
 * font-size percent or 0, line_scale as a line-height percent or 0, text_decoration
 * as an OR of CSS_DECO_* / 0 none / -1 unset) on the most recently appended run.
 * No-op on an empty or NULL view. The append helpers default text_align/font_scale/
 * line_scale to 0 and text_decoration to -1. Like author colors, render_doc applies
 * these only with caps.css. */
void pv_set_text_style(pv_view *v, int text_align, int font_scale, int line_scale,
                       int text_decoration);

/* Sets the author text-presentation extensions (Hito 23b-6, plus text_overflow/
 * word_break, plus the 2026-07-10 batch: tab_size/direction/font_variant/list_style_pos)
 * on the most recently appended run: the generic font_family, text_transform, signed
 * letter_spacing/word_spacing (PV_LEN_UNSET = unset), text-shadow (shadow_dx/dy
 * offsets + shadow_color packed 0xRRGGBB or -1 for none), opacity (0..100 or -1),
 * valign, signed text_indent (PV_LEN_UNSET = unset), white_space, text_overflow
 * (css_text_overflow), word_break (css_word_break), the text-decoration sub-
 * properties (color/style/thickness), and the new batch: tab_size (0 unset ->
 * 8 in <pre>), direction (css_direction), font_variant (css_font_variant) and
 * list_style_pos (css_list_pos). No-op on an empty or NULL view. Like author
 * colors, render_doc applies these only with caps.css. */
void pv_set_text_ext(pv_view *v, int font_family, int text_transform,
                     int letter_spacing, int word_spacing, int shadow_dx, int shadow_dy,
                     int shadow_color, int opacity, int valign, int text_indent,
                     int white_space, int text_overflow, int word_break,
                     int text_decoration_color, int text_decoration_style,
                     int text_decoration_thickness,
                     int tab_size, int direction, int font_variant, int list_style_pos);

/* Sets the nearest flex/grid container annotation on the most recently appended
 * run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/
 * row-gap/align-items). No-op on an empty or NULL view. Both append helpers
 * default cont_id to -1 (no container), cont_wrap/cont_align_items to 0,
 * cont_row_gap to -1. */
void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_gap, int cont_justify, int cont_cols,
                      int cont_wrap, int cont_row_gap, int cont_align_items);

/* Stage 3: sets the flex per-item values on the most recently appended run — the
 * ITEM's resolved grow/shrink (x100, -1 unset), basis (px / CSS_LEN_AUTO /
 * CSS_LEN_UNSET), order (CSS_LEN_UNSET unset) and align-self (css_align_kw, 0
 * unset), plus the CONTAINER's flex-direction (css_flex_direction, 0 unset ->
 * row). No-op on an empty or NULL view. The append helpers default them to the
 * unset sentinels. */
void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int flex_order, int flex_direction, int flex_align_self);

/* Sets the container-item ordinal on the most recently appended run (-1 = none).
 * No-op on an empty or NULL view; the append helpers default cont_item to -1. */
void pv_set_cont_item(pv_view *v, int cont_item);

/* Float layout setter for the most recently appended run (spec/float.md): float_side
 * (css_float), float_id (floated-element group id, -1 = none), float_clear (css_clear).
 * No-op on an empty or NULL view; the append helpers default to 0 / -1 / 0. */
void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear);

/* Sets the author box model on the most recently appended run (left/right insets,
 * width cap, centered flag, and top/bottom margin overrides in px; box_mt/box_mb
 * may be PV_LEN_UNSET). No-op on an empty or NULL view. The append helpers default
 * box_l/r/w/center to 0 and box_mt/box_mb to PV_LEN_UNSET. */
void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int box_mt, int box_mb);

/* Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of
 * the source element. No-op on an empty or NULL view; the append helpers default
 * node_id to DOM_NODE_NONE. */
void pv_set_node_id(pv_view *v, dom_node_id node_id);

/* Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of
 * the box-carrying block it belongs to (-1 = none). No-op on an empty or NULL view;
 * the append helpers default block_id to -1. The box's decoration is on pv_box_def. */
void pv_set_block_id(pv_view *v, int block_id);

/* Box engine (Hito 23b-8 Step D): appends one box definition to the box tree,
 * taking an owned copy of *d. The append order IS the block_id order (callers append
 * box 0, then 1, ...), so the new box's index equals its block_id. No-op returning
 * PV_ERR_NULL_ARG on NULL args. Used by pv_build (after the run walk) and by the IPC
 * deserialiser. */
pv_status pv_add_box_def(pv_view *v, const pv_box_def *d);

/* Idempotent; safe on NULL and safe to call twice. */
void pv_free(pv_view *v);

/* Read accessors. NULL-safe. */
size_t        pv_count(const pv_view *v);
const pv_run *pv_at(const pv_view *v, size_t i);

/* Box tree accessors (Step D). pv_box_count is the number of box definitions;
 * pv_box_at returns boxes[i] (i == a block_id) or NULL when out of range / NULL. */
size_t            pv_box_count(const pv_view *v);
const pv_box_def *pv_box_at(const pv_view *v, size_t i);

#endif /* FREEDOM_PAGE_VIEW_H */
