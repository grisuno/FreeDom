#ifndef FREEDOM_PAGE_VIEW_H
#define FREEDOM_PAGE_VIEW_H

#include <stddef.h>
#include <stdint.h>

#include "dom.h"
#include "html_parse.h"
#include "css.h"   /* css_drop_log, for the pv_css_drops diagnostic */

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
#define PV_LEN_AUTO  (-2147483647)     /* matches CSS_LEN_AUTO: center */
#define PV_LEN_END   (-2147483646)     /* matches CSS_LEN_END: right/bottom edge */
/* Sized grid tracks carried per run (2026-07-11). Mirrors CSS_GRID_TRACKS_MAX in
 * css.h (page_view.c static-asserts they agree); tracks past it lay out as auto. */
#define PV_GRID_TRACKS 8
/* Depth of the flex/grid container chain page_view tracks and the presentation layer
 * walks. Real pages nest a few levels (header > nav > ul, or grid > flex card > flex
 * row); past this the outer levels are dropped and those containers lay out as top
 * level -- degrading to flat layout, never looping. */
#define PV_CONT_DEPTH 8
/* Background-image url() buffer (2026-07-16). Mirrors CSS_URL_MAX in css.h
 * (page_view.c static-asserts they agree); page_view stays decoupled from
 * css.h in this header, like the rest of the css-enum-mirroring int fields.
 * Sized to hold the RESOLVED absolute URL too (render_doc.c resolves in
 * place), not just the raw author-CSS token. */
#define PV_BG_URL_MAX 1024

typedef enum pv_kind {
    PV_TEXT = 0,   /* inline text */
    PV_LINK = 1,   /* inline text that is a hyperlink (href is set) */
    PV_IMAGE = 2,  /* an <img>: src is set, text holds the alt text */
    PV_INPUT = 3,  /* a form control (<input>/<textarea>/<button>): see pv_input_type */
    PV_VIDEO = 4,  /* a <video> or <audio> element: src is set, text is alt/label,
                    * poster_src is the poster URL (NULL for audio), img_w/img_h
                    * hold declared dimensions (-1 unknown) */
    PV_SVG = 5,    /* an inline <svg>: text holds the serialised markup (inert data,
                    * parsed by svg_render at paint time), img_w/img_h the intrinsic
                    * size in px. src is NULL -- inline SVG names no resource, which
                    * is why it renders without the images capability. */
} pv_kind;

/* Class of a PV_INPUT control. Drives how the GUI paints and submits it. Unknown
 * input types collapse to PV_IN_TEXT (a one-line editable box). */
typedef enum pv_input_type {
    PV_IN_TEXT = 0,   /* text/search/email/url/tel/number/...: one-line editable box */
    PV_IN_PASSWORD,   /* password: editable, masked when painted */
    PV_IN_TEXTAREA,   /* <textarea>: editable (one-line box for now); value = its content */
    PV_IN_HIDDEN,     /* hidden: not painted; value still submitted */
    PV_IN_SUBMIT,     /* submit button (triggers the owning form) */
    PV_IN_BUTTON,     /* non-submitting button (button/reset): painted, inert */
    PV_IN_CHECKBOX,   /* <input type="checkbox">: toggleable box, checked=value set */
    PV_IN_RADIO,      /* <input type="radio">: grouped by name, one selected */
    PV_IN_RANGE,      /* <input type="range">: slider with min/max/value */
    PV_IN_SELECT,     /* <select> with <option> children: painted value, click->options */
    PV_IN_PROGRESS,   /* <progress>: value/max bar, not interactive */
    PV_IN_METER,      /* <meter>: colored bar with value/min/max/low/high/optimum */
    PV_IN_LEGEND      /* <legend> inside <fieldset>: text displayed overlapping border */
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
    char   *src;          /* PV_IMAGE/PV_VIDEO: image/video URL; NULL otherwise */
    char   *poster_src;   /* PV_VIDEO only: poster image URL; NULL otherwise */
    int     img_w;        /* PV_IMAGE/PV_VIDEO declared width in px, or -1 if unknown */
    int     img_h;        /* PV_IMAGE/PV_VIDEO declared height in px, or -1 if unknown */
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
    /* Whether font_scale is a percent of the 16px ROOT (1) or of the block's
     * user-agent size (0). An absolute size REPLACES the UA heading scale; a
     * relative one multiplies it. spec/css.md "font-size: absolute vs relative". */
    int     font_abs;
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
    /* visibility (css_visibility), resolved from the nearest ancestor that sets it.
     * It INHERITS (CSS 2.1 11.2) and a descendant may set itself back to `visible`,
     * so it rides here with the other inherited text properties rather than being
     * read off the element's own box: text with no box of its own must hide too.
     * The box-level copy (pv_box_def.visibility) still gates the DECORATION. 0 unset. */
    int     visibility;      /* css_visibility */
    /* 2026-07-10 wiring batch, both inherited like the rest of the text
     * extensions and gated by caps.css downstream. image_rendering asks the
     * painter for a nearest-neighbour filter when blitting a decoded image
     * (pixelated/crisp-edges); caret_color tints the caret of a focused form
     * control (0xRRGGBB, or -1 for auto/unset). */
    int     image_rendering; /* css_image_rendering, 0 (unset) */
    int     caret_color;     /* 0xRRGGBB, or -1 (auto/unset) */
    /* Image/video object-fit from the element's own CSS (2026-07-12). Controls how
     * the decoded image is scaled into its declared box: fill/contain/cover/none/
     * scale-down. 0 = unset (fill). Non-inherited; meaningful only on PV_IMAGE and
     * PV_VIDEO runs but carried on all for simplicity. */
    int     object_fit;      /* css_object_fit, 0 (unset, same as fill) */
    /* Gradient text (2026-07-19): the nearest ancestor with background-clip:
     * text + -webkit-text-fill-color:transparent hands its background gradient
     * to the runs inside it; the painter fills the glyphs with it (the band
     * behind the text does NOT paint that background). grad_text_n 0 = none;
     * angle in CSS degrees; c[] packed 0xRRGGBB stops (-1 unused). Author
     * presentation: render_doc applies it only with caps.css, like fg_rgb. */
    int     grad_text_n;
    int     grad_text_angle;
    int     grad_text_c[4];
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
    int     cont_rows;    /* grid row count (explicit grid-template-rows), or 0 */
    /* The box that ENCLOSES this container's items: the container element's own box
     * when it registers one (its background/padding/border), else the nearest
     * box-carrying ancestor, else -1. The presentation layer lays the items out
     * inside this rect, and an item's own root box must be a STRICT DESCENDANT of
     * it -- without that, a container whose items carry no box of their own had
     * every item claim the CONTAINER's box as its root and paint the container
     * background once per item (a `space-between` header painted two bands with the
     * page showing through the middle). Structure, never gated. */
    int     cont_box_id;
    /* Grid track sizes of the container (2026-07-11; mirrors css_style.grid_col_w:
     * 0 auto / >0 px / <0 fr x100, first PV_GRID_TRACKS tracks) and this run's
     * ITEM column span (grid-column: span N; <= 0 = 1). Structure like cont_*,
     * carried regardless of caps.css. Defaults: all 0. */
    int     cont_col_w[PV_GRID_TRACKS];
    int     grid_span;
    int     row_span;
    /* Named grid placement (2026-08-14, CSS Grid 1 8.4): the cell this item's
     * `grid-area: <name>` resolved to inside its container's
     * `grid-template-areas`, or -1 when the item is auto-placed. Numbers, not a
     * name: page_view does the name matching, so the painter (and the codec) only
     * ever carry a row and a column. */
    int     grid_row_start, grid_col_start;
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
    /* The percentage half of the box placement above: per-mille of the
     * CONTAINING BLOCK WIDTH (99.8% -> 998), 0 = none. Rides beside each px
     * field; the painter combines the two exactly once, with bx_lp_px, against
     * the real available width.
     *
     * box_mt_pct/box_mb_pct are the VERTICAL margins, and they too resolve
     * against the containing WIDTH -- CSS 2.1 8.3, not a simplification.
     * Gated by caps.css like the px halves. */
    int     box_w_pct;
    int     box_l_pct, box_r_pct;
    int     box_mt_pct, box_mb_pct;
    /* User-agent box identity of this run's nearest BLOCK-LEVEL ancestor: a bx_ua_tag
     * code (BX_UA_NONE = the element gets no UA margin, which is the answer for
     * div/section/td/... and for anything unclassified).
     *
     * It exists because rd_kind cannot answer the question: every body-text block
     * arrives as RD_PARAGRAPH, so without this the painter guessed "p" and gave a
     * plain <div> a paragraph's 1em margins -- a blank line before EVERY block of
     * every page. It is STRUCTURE, carried regardless of caps.css: a user-agent
     * margin is the UA sheet, not author styling (CLAUDE.md 7.2 "Layout != estilo de
     * autor"). spec/box_style.md 4d. */
    int     ua_tag;
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
    /* The REPLACED element's own box def index (-1 = none), for <img>/<video>/<svg>.
     *
     * Deliberately NOT block_id: those answer two different questions. block_id says
     * which box a run belongs to and is what box reconciliation walks; this says
     * where the element's own declared width and aspect-ratio live, and is read for
     * SIZING only. Overloading block_id for both reshuffled the box structure of
     * every page carrying inline icons (measured on slashdot: story headings started
     * overlapping the body text), while leaving it unset meant an unavailable image
     * had no box at all -- so its `alt` reflowed as ordinary text and every card in
     * a thumbnail grid grew to fit a title it already displayed underneath. */
    int     own_box_id;
    /* form controls (PV_INPUT only; defaults: type 0, name/value NULL, form_id -1,
     * method GET). name/value carry the submitted bytes verbatim (not whitespace
     * collapsed); form_id groups controls of the same <form> (-1 = no form). */
    int     input_type;   /* pv_input_type */
    char   *name;         /* control name, or NULL */
    char   *value;        /* control current/default value, or NULL */
    int     form_id;      /* owning-form group id in document order, or -1 */
    int     form_method;  /* pv_form_method of the owning form */
    int     checked;       /* -1=n/a, 0=unchecked, 1=checked (checkbox/radio) */
    char   *select_opts;   /* NULL or "optval||lbl||optval||lbl" for <select> */
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
    int box_h_set;      /* 1 when height was explicitly declared (including 0px),
                         * 0 when height is auto/unset. Sent so close_top_box can
                         * honour height:0 with overflow:hidden (clip content). */
    int box_min_h;      /* min-height (px >= 0), or 0 unset */
    int box_max_h;      /* max-height (px > 0), or 0 unset */
    int box_min_w;      /* min-width  (px >= 0), or 0 unset */
    /* Percentage halves (per-mille of the containing block WIDTH, 0 = none),
     * one per px field. See the pv_run block for why even the vertical padding
     * resolves against the width (CSS 2.1 8.4). */
    /* The box's OWN vertical margins (2026-08-14), px + per-mille percentage half,
     * PV_LEN_UNSET/0 = not declared by the author. Horizontal margins are folded
     * into box_l/box_r above because they only shift the box within its line; the
     * vertical ones cannot be folded anywhere, because they COLLAPSE with the
     * adjacent sibling's (CSS 2.1 8.3.1) and so must survive as their own value
     * until the two are next to each other. Without them the painter had no
     * margin to read for a box-generating block and substituted a theme constant,
     * which is why three 20px divs with margin-bottom:30px stacked at 0/20/40
     * instead of Firefox's 0/50/100. ua_tag names the element so the USER-AGENT
     * margin can be looked up (bx_block_ua_box) when the author declares none --
     * the same identity, from the same table, that a text run carries. */
    int box_mt, box_mb;
    int box_mt_pct, box_mb_pct;
    int ua_tag;
    /* The element's COMPUTED font-size in px. The user-agent margins the ua_tag
     * above selects are expressed in em (`p { margin: 1em 0 }` IS the UA sheet), so
     * without the element's own font-size the painter would have to multiply them by
     * a constant -- which is the bug this whole batch exists to remove. 0 = unknown,
     * and the painter then falls back to the theme's body size. */
    int font_px;
    int box_w_pct;      /* width/max-width cap */
    int box_l_pct, box_r_pct;              /* the l/r insets (padding + margin) */
    int box_min_w_pct;                     /* min-width */
    int pad_t_pct, pad_r_pct, pad_b_pct, pad_l_pct;
    int bg_rgb;   /* author background-color of the box (0xRRGGBB), or -1 */
    /* Background alpha percent 0..100 from rgba()/hsla() (2026-07-19);
     * PV_LEN_UNSET = opaque. The box background fill multiplies by it. */
    int bg_alpha;
    int box_sizing;
    int pad_t, pad_r, pad_b, pad_l;
    int bord_tw, bord_rw, bord_bw, bord_lw;
    int bord_ts, bord_rs, bord_bs, bord_ls;
    int bord_tc, bord_rc, bord_bc, bord_lc;
    /* The four border-radius corners in CSS corner order (top-left, top-right,
     * bottom-right, bottom-left) plus their percentage halves (per-mille,
     * resolved against the box's own smaller dimension -- see css_pct_slot).
     * border_radius IS the top-left corner. */
    int border_radius, border_radius_tr, border_radius_br, border_radius_bl;
    int radius_tl_pct, radius_tr_pct, radius_br_pct, radius_bl_pct;
    /* translate() percentage halves (per-mille). Unlike every other percentage
     * on this struct these measure the box's OWN border box, x against its
     * width and y against its height (CSS Transforms 1 section 8). */
    int transform_tx_pct, transform_ty_pct;
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
    /* Percentage halves of the four insets, per-mille (0 = none). left/right
     * resolve against the containing block WIDTH, top/bottom against its
     * HEIGHT (CSS 2.1 9.3.2) -- the one place in the box model where the two
     * axes really do use different bases. `left:50%` + `translate(-50%,-50%)`
     * is the universal centring idiom, so dropping these dropped the whole
     * pattern. */
    int inset_top_pct, inset_right_pct, inset_bottom_pct, inset_left_pct;
    int z_index;
    /* visibility / overflow / cursor (not inherited, like border/position -- read
     * from the box's own resolved style). visibility gates painting of this box and
     * everything it encloses while still reserving its layout space (see
     * css_visibility). A content-visibility:hidden on the element folds into
     * visibility here (page_view maps it to CSS_VIS_HIDDEN when visibility itself
     * is unset -- same documented simplification as visibility:collapse).
     * overflow_x/_y clip in-flow rows and positioned boxes to ancestor
     * overflow:hidden rects (2026-07-09). cursor drives the hover cursor shape
     * (see css_cursor). */
    int visibility;
    int overflow_x, overflow_y;
    int cursor;
    /* pointer-events (2026-07-10). CSS_PE_NONE on this box (or, at hit-test time,
     * on an ancestor box -- the GUI resolves the nearest box in the parent chain
     * that sets the property, like cursor) removes the box's content from
     * hit-testing: links under it do not hover or click, and cursor does not
     * resolve there. Rides the box-def tree, so it is caps.css-gated by
     * construction (no boxes without author CSS). */
    int pointer_events;
    /* Multi-column container params (CSS Multi-column Layout 1). col_count 0 =
     * `auto`, col_width 0 = `auto`; with both 0 the box is NOT a multi-column
     * container and lays out exactly as before this existed. col_gap is the
     * used `column-gap` in px, -1 = `normal` (the painter then uses 1em, the
     * spec's initial value). The rule fields paint the line between columns.
     * STRUCTURE, like the flex/grid cont_* fields. */
    /* line-clamp: at most this many line boxes paint inside the box, the rest
     * are clipped (CSS Overflow 4). 0 = no clamp. STRUCTURE, like col_*. */
    int line_clamp;
    int col_count, col_width, col_gap;
    int col_fill, col_span;
    int col_rule_w, col_rule_style, col_rule_color;
    /* aspect-ratio (numerator/denominator x1000, both 0 = unset/auto) */
    int aspect_num, aspect_den;
    /* linear-gradient background (2026-07-11): stop count (0 = none, else
     * 2..CSS_GRAD_STOPS_MAX), CSS degrees (0 = to top, 90 = to right), and the
     * packed 0xRRGGBB stops (unused -1). Painted evenly spaced across the border
     * box, rounded by border_radius. When set it wins over bg_rgb. */
    int grad_n, grad_angle;
    int grad_c0, grad_c1, grad_c2, grad_c3;
    /* box-level opacity (M1.1 increment 3, compositor group opacity): percent
     * 0..100, or -1 (unset/opaque). The single trigger of cx_forms_stacking_context
     * this engine currently wires end-to-end -- the painter composites the whole
     * box (decoration + its content) to an offscreen surface and blends it as ONE
     * unit at this alpha, not per-element (see gui/browser_ui.c paint_positioned_one
     * and spec/compositor.md). Distinct from pv_run.opacity (per text-run color
     * alpha, pre-existing, not a stacking context). */
    int opacity;
    /* mix-blend-mode / isolation (M1.1 increment 4, compositor.md's remaining
     * cx_forms_stacking_context triggers): css_mix_blend (0 unset) and
     * css_isolation (0 unset). mix_blend maps 1:1 to a Cairo compositing operator
     * (CAIRO_OPERATOR_MULTIPLY etc.) when the box's group is composited back; the
     * push_group itself already gives isolation's semantics (blending confined to
     * the group), so isolation has no separate painter step -- it is carried here
     * so cx_forms_stacking_context/cx_box_layer (box_tree.c ordering) see the true
     * value instead of a hardcoded 0. */
    int mix_blend;
    int isolation;
    /* transform (M1.2 translate; M1.2b adds scale/rotate): signed px offsets
     * (transform_tx/ty), scale as a PERCENT of identity (transform_sx/sy, 100 =
     * scale(1)) and rotate in whole degrees (transform_rotate); PV_LEN_UNSET on
     * any field means that function was not declared. Applied as a real Cairo
     * affine transform (translate+rotate+scale, pivoted at the box's own
     * center) to the box's paint calls only (gui/browser_ui.c
     * box_transform_matrix) -- the box's own x/y/w/h here and everywhere else
     * (hit-testing, click dispatch, overflow-clip ancestor rects) stay at the
     * UNTRANSFORMED layout position. Transformed hit-testing is out of scope
     * for this increment (see spec/compositor.md). */
    int transform_tx, transform_ty;
    int transform_sx, transform_sy;
    int transform_rotate;
    /* M1.2c: skew()/skewX()/skewY() whole degrees (PV_LEN_UNSET = unset) and
     * transform-origin percents (PV_LEN_UNSET = the CSS default 50% center).
     * origin alone is inert: it does not trigger box registration nor a
     * stacking context (see spec/compositor.md M1.2c). */
    int transform_skx, transform_sky;
    int transform_ox, transform_oy;
    /* background-image: url(...) (2026-07-16). The RAW, UNRESOLVED url() text (css
     * and page_view never fetch/resolve); render_doc.c resolves it against the
     * page origin and gates it exactly like an <img> src (caps.images +
     * rdp_image_decision) before the GUI fetches/decodes/paints it. "" = none.
     * PV_BG_URL_MAX duplicates css.h's CSS_URL_MAX (page_view stays decoupled
     * from css.h in this header, like the rest of the css-enum-mirroring int
     * fields below). bg_size/bg_repeat mirror css_bg_size/css_bg_repeat (same
     * int encoding, 0 = unset). When bg_image_url is set it paints UNDER any
     * bg_rgb/gradient (CSS background layering: image on top of color). */
    char bg_image_url[PV_BG_URL_MAX];
    /* R5b: second background-image layer (behind the first). "" = none. */
    char bg_image_url2[PV_BG_URL_MAX];
    int bg_grad_pos[4];  /* R5d */
    int bg_grad_radial;
    int bg_size;
    int bg_repeat;
    /* animation-duration (Phase R1): parsed time in ms, 0 = no animation.
     * Other animation params and @keyframes are follow-up work. */
    int anim_duration_ms;
    /* filter (Phase R3) */
    int filter_blur;
    int filter_grayscale;
    int filter_brightness;
    int filter_contrast;
    int filter_sepia;
    int filter_invert;
    int filter_saturate;
    int filter_hue_rotate;
    /* filter: drop-shadow (2026-07-19): signed px offsets, blur px, packed
     * color (-1 = none). Painted from the ALPHA silhouette of the composited
     * group (the real content shape), unlike box-shadow's rect. */
    int filter_drop_dx;
    int filter_drop_dy;
    int filter_drop_blur;
    int filter_drop_color;
    /* backdrop-filter: blur(Npx) (2026-07-19). 0 = none. The painter blurs the
     * already-painted backdrop under the box rect before the box's own
     * (typically translucent) background composites on top; forces a stacking
     * context like filter. See spec/compositor.md. */
    int backdrop_blur;
    /* clip: rect(top,right,bottom,left) for positioned boxes (CSS 2.1 §11.1.2).
     * px values, PV_LEN_UNSET = auto (the border-box edge). Only applied by the
     * positioned painter (paint_positioned_one) to absolute/fixed boxes. */
    int clip_top;
    int clip_right;
    int clip_bottom;
    int clip_left;
    /* background-position (R5a): px offsets, PV_LEN_UNSET = unset. */
    int bg_pos_x;
    int bg_pos_y;
    /* R8: ::before/::after generated content text. Empty string = none. */
    char content_str[PV_BG_URL_MAX];
    char content_before_str[PV_BG_URL_MAX];
    char content_after_str[PV_BG_URL_MAX];
    /* Phase R1b: animation iteration count (-1 = infinite) and timing function. */
    int anim_iterations;
    int anim_timing;
    /* Phase R4 (2026-07-16): animation direction, fill-mode, delay, and
     * @keyframes name. anim_direction maps to ip_direction (0=normal,
     * 1=reverse, 2=alternate, 3=alternate-reverse, -1=unset).
     * anim_fill_mode maps to ip_fill_mode (-1=unset). anim_delay_ms is
     * the delay in ms (0=none). anim_name is the @keyframes rule name
     * (carried for forward compat; the v1 painter uses these only for
     * the existing opacity animation, not for arbitrary keyframe
     * property animation which requires the @keyframes engine). */
    int anim_direction;
    int anim_fill_mode;
    int anim_delay_ms;
    char anim_name[64];
    /* Resolved @keyframes data (Phase R1c): keyframe stops from the matching
     * @keyframes rule. anim_nkf=0 means no keyframes (use default 0->100). */
    int anim_nkf;
    int anim_kf_pct[8];  /* percentage * 100, max 8 stops */
    int anim_kf_val[8];  /* opacity 0-100 */
    /* Phase R1d: transform keyframe values per stop. PV_LEN_UNSET = unset for
     * tx/ty; 0 = unset for sx/sy/rotate (identity). */
    int anim_kf_tx[8];
    int anim_kf_ty[8];
    int anim_kf_sx[8];
    int anim_kf_sy[8];
    int anim_kf_rot[8];
    /* Phase R1e: background/foreground color keyframe values per stop. */
    int anim_kf_bg[8];  /* bg color 0xRRGGBB or -1 */
    int anim_kf_fg[8];  /* fg color 0xRRGGBB or -1 */
    /* The element's css_display. The painter needs it to tell an INLINE-LEVEL box
     * (inline-block: a button, a badge, a pill) from a block one: an inline-level
     * box shrink-wraps to its content and is placed by the parent's text-align,
     * instead of opening a full-width block box. CSS_DISP_UNSET (0) = not stated. */
    int display;
    /* convenience: last field marker for IPC count */
} pv_box_def;

/* Flex/grid container descriptor (2026-07-31). One entry per container element, its
 * index IS the run's cont_id. Two reasons it exists instead of the container params
 * riding every run:
 *
 *   1. NESTING. A run carries only its INNERMOST container. Laying out an outer
 *      container needs the outer container's own parameters, and there is a common
 *      case where no run carries them at all: a grid whose children are all flex
 *      containers (`.cards{display:grid}` holding `display:flex` cards) has no run
 *      with cont_id == the grid. parent_id/parent_item rebuild the whole chain.
 *   2. The parameters are per-container, not per-run: carrying them on every run of
 *      a container was pure duplication across the IPC.
 *
 * parent_id is the id of the enclosing container (-1 = top level) and parent_item is
 * THIS container's item ordinal within that parent, so a nested container is one item
 * of its parent. Structure (like cont_id itself), carried regardless of caps.css. */
typedef struct pv_cont_def {
    int parent_id;      /* enclosing container id, or -1 */
    int parent_item;    /* this container's item ordinal in its parent, or -1 */
    int display;        /* bx_display (flex/grid) */
    int gap;            /* column gap px */
    int justify;        /* fx_justify */
    int cols;           /* grid column count (>= 1 for grid), else 0 */
    int rows;           /* explicit grid-template-rows count, else 0 */
    int direction;      /* css_flex_direction */
    int col_w[PV_GRID_TRACKS];  /* grid track sizes (0 auto / >0 px / <0 fr x100) */
    int wrap;           /* css_flex_wrap */
    int row_gap;        /* px, or -1 (unset -> falls back to gap) */
    int align_items;    /* css_align_kw */
    int align_content;  /* css_align_kw */
    int justify_items;  /* css_align_kw */
    int grid_flow;      /* css_grid_auto_flow */
    int box_id;         /* box enclosing this container's items, or -1 */
    int anon_row;       /* 1 = anonymous row synthesised for an inline-block parent */
    /* 1 = this grid container was SYNTHESISED from a <table>, not declared by the
     * author. A table sizes its columns to their content (CSS 2.1 section 17.5.2
     * automatic table layout); an author grid with auto tracks keeps the historical
     * equal split. Without the distinction there is no way to tell the two apart
     * downstream -- both arrive as display:grid with all-auto tracks. */
    int is_table;
    /* The flex/grid ITEM properties of the element this container occupies as one
     * item of its PARENT container: grow/shrink (x100, -1 unset), basis (px, or a
     * percentage encoded -(1000000+per_mille), or CSS_LEN_AUTO/CSS_LEN_UNSET), order
     * (CSS_LEN_UNSET unset) and align_self (css_align_kw, CSS_AK_UNSET=0 unset). A
     * nested container's item props live on the wrapper element between it and the
     * parent (e.g. Bootstrap's `.col{flex:1 0 0%}` wrapping a `.row`); that wrapper
     * carries no run of its own, so the parent could not read them from a run and
     * fell back to a run INSIDE the nested container -- the wrong element -- so the
     * item never grew. Set only when parent_id >= 0. */
    int item_grow, item_shrink, item_basis, item_order, item_align_self;
} pv_cont_def;

typedef struct pv_view {
    pv_run    *runs;
    size_t     count;
    size_t     cap;
    pv_box_def *boxes;   /* the box tree (Step D); boxes[block_id] describes a box */
    size_t      nbox;
    size_t      boxcap;
    pv_cont_def *conts;  /* flex/grid containers; conts[cont_id] describes one */
    size_t       ncont;
    size_t       contcap;
    int         canvas_bg;  /* CSS 2.1 §14.2: root <html> background → canvas background.
                             * Packed 0xRRGGBB, or -1 if none (theme default). */
    int         html_max_width;  /* root <html> max-width in px, or -1 unset */
    int         html_margin_top; /* root <html> margin-top in px, or 0 */
    int         html_center;     /* 1 if root has margin-left:auto && margin-right:auto */
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
/* viewport_w is the render viewport width in px used to evaluate @media width
 * queries (min-width/max-width): it MUST equal the width the page is painted at, or
 * a responsive page selects rules for the wrong breakpoint (e.g. Wikipedia's Vector
 * body activates its >=1680px pinned-sidebar grid at a 1000px paint and squeezes the
 * article). 0 (or negative) falls back to CSS_MEDIA_DEFAULT_WIDTH, keeping every
 * caller that predates this parameter byte-identical. */
pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                          int prefers_dark, const char *extern_css, size_t extern_len,
                          int viewport_w, pv_view **out);

/* Diagnostic: runs exactly the CSS collection and parse pv_build_styled runs, and
 * reports into *log every declaration the parser DISCARDED, by property and by
 * cause (spec/css_drops.md). Builds no view and changes nothing -- it exists so
 * "what is this page's CSS losing?" is a measurement instead of a grep over the
 * dispatch, which sees property names only and is blind to a rejected VALUE on a
 * property that is already implemented. Shares collect_style_text/collect_root_scope
 * with the real path, so the answer is about the same bytes the renderer parsed.
 * Returns PV_ERR_NULL_ARG if doc or log is NULL. */
pv_status pv_css_drops(const hp_document *doc, int prefers_dark,
                       const char *extern_css, size_t extern_len,
                       int viewport_w, css_drop_log *log);

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

/* Appends one PV_VIDEO run (a <video> or <audio> element). src is required (the
 * media URL); alt may be NULL (stored as ""). poster is the poster image URL (may
 * be NULL, only meaningful for video). w/h are the declared dimensions, or -1
 * when unknown. text/alt/src/poster are normalised to valid UTF-8. Returns PV_OK
 * or PV_ERR_OOM / PV_ERR_NULL_ARG. */
pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src,
                          const char *poster, int w, int h);

/* Appends one PV_SVG run. markup is the serialised <svg> subtree (copied; may be
 * any bytes -- it is parsed later by the bounded, fuzzed svg_render, never
 * executed). w/h are the intrinsic pixel dimensions, or -1 when undeclared. */
pv_status pv_append_svg(pv_view *v, int heading, int block_break,
                        const char *markup, int w, int h);

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
 * font-size percent or 0, font_abs as 1 when that percent is of the 16px root,
 * line_scale as a line-height percent or 0, text_decoration as an OR of
 * CSS_DECO_* / 0 none / -1 unset) on the most recently appended run.
 * No-op on an empty or NULL view. The append helpers default text_align/font_scale/
 * font_abs/line_scale to 0 and text_decoration to -1. Like author colors, render_doc
 * applies these only with caps.css. */
void pv_set_text_style(pv_view *v, int text_align, int font_scale, int font_abs,
                       int line_scale, int text_decoration);

/* Sets the author text-presentation extensions (Hito 23b-6, plus text_overflow/
 * word_break, plus the 2026-07-10 batch: tab_size/direction/font_variant/list_style_pos)
 * on the most recently appended run, from a pv_text_ext value (below). No-op on an
 * empty or NULL view (or a NULL ext). Like author colors, render_doc applies these
 * only with caps.css. */

/* The author text-presentation extensions of one run, resolved from the nearest
 * ancestor that sets each field (they all inherit in CSS). The 20+ fields used to
 * be positional parameters of pv_set_text_ext -- a signature that grew with every
 * property batch; the struct is the contract now. list_style is resolved here too
 * but is NOT a run field: page_view bakes the <li> marker into the run text
 * (structure), so pv_set_text_ext ignores it. Initialise with pv_text_ext_reset
 * (every field to its "unset" sentinel), then set what the caller resolved. */
typedef struct pv_text_ext {
    int font_family, text_transform, letter_spacing, word_spacing;
    int shadow_dx, shadow_dy, shadow_color;
    int opacity, valign, text_indent, white_space;
    int list_style;
    int text_overflow, word_break;
    int visibility;      /* css_visibility, 0 unset -- inherits (CSS 2.1 11.2) */
    int text_decoration_color;     /* 0xRRGGBB, or -1 (unset) */
    int text_decoration_style;     /* css_text_decoration_style, 0 unset */
    int text_decoration_thickness; /* px, -1 unset, 0 from-font */
    int tab_size;        /* 0 unset -> 8 at paint time */
    int direction;       /* css_direction */
    int font_variant;    /* css_font_variant */
    int list_style_pos;  /* css_list_pos */
    /* 2026-07-10 wiring batch. */
    int image_rendering; /* css_image_rendering, 0 unset */
    int caret_color;     /* 0xRRGGBB, -1 unset; CSS_LEN_AUTO = explicit auto */
    int object_fit;      /* css_object_fit; 0 (unset) = fill */
    /* Gradient text (2026-07-19). text_fill: -webkit-text-fill-color from the
     * nearest ancestor that sets it (packed / CC_COLOR_TRANSPARENT / -1 unset).
     * bgclip_seen latches the NEAREST ancestor with background-clip:text; that
     * ancestor's gradient lands in grad_text_* (or its solid background in
     * bgclip_src_bg) as the glyph fill source. */
    int text_fill;
    int bgclip_seen;
    int bgclip_src_bg;   /* solid background of the bg-clip:text ancestor, -1 none */
    int grad_text_n, grad_text_angle;
    int grad_text_c[4];
} pv_text_ext;

/* Initialises every field of *e to its "unset" sentinel. NULL-safe. */
void pv_text_ext_reset(pv_text_ext *e);

/* Does content with this resolved visibility paint? (CSS 2.1 11.2, pure.)
 * `box_hidden` is what the enclosing box stack decided (an ancestor box carrying
 * visibility:hidden); `run_visibility` is the value page_view resolved for the run
 * itself by walking its ancestors (css_visibility, 0 = unset).
 *
 * An explicit value on the run WINS over the box stack in both directions: that is
 * what makes `visibility` inherited-but-overridable, so a descendant of a hidden
 * subtree can declare `visible` and reappear. With nothing declared the box stack
 * decides, which keeps a box-only hidden subtree behaving exactly as before.
 * Returns 1 when the content must not paint (its layout space is still reserved --
 * unlike display:none, which removes the box entirely). */
int pv_content_hidden(int box_hidden, int run_visibility);

void pv_set_text_ext(pv_view *v, const pv_text_ext *e);

/* Sets the gradient-text fill (grad_text_*) verbatim on the most recently
 * appended run. n < 2 is a no-op (no gradient). Used by the IPC read path,
 * which receives the already-resolved fields; the build path engages gradient
 * text through pv_set_text_ext's bg-clip:text + transparent-fill rule. */
void pv_set_grad_text(pv_view *v, int n, int angle, const int *c4);

/* Sets the nearest flex/grid container annotation on the most recently appended
 * run (cont_id, the bx_display, the parsed gap/justify/cols, plus flex-wrap/
 * row-gap/align-items). No-op on an empty or NULL view. Both append helpers
 * default cont_id to -1 (no container), cont_wrap/cont_align_items to 0,
 * cont_row_gap to -1. */
void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_gap, int cont_justify, int cont_cols,
                      int cont_wrap, int cont_row_gap, int cont_align_items);

/* Sets the container's grid track sizes and this run's ITEM column span on the
 * most recently appended run (2026-07-11). col_w points at up to PV_GRID_TRACKS
 * encoded sizes (0 auto / >0 px / <0 fr x100; NULL or n <= 0 leaves all-auto);
 * col_span is the item's `grid-column: span N` (<= 0 = 1). No-op on an empty or
 * NULL view. The append helpers default everything to 0. */
void pv_set_row_span(pv_view *v, int row_span);

/* Sets the last run's RESOLVED named-grid cell (-1, -1 = auto-placed). See
 * spec/grid_areas.md; the name matching happens in pv_build, never downstream. */
void pv_set_grid_area(pv_view *v, int row_start, int col_start);
void pv_set_grid_rows(pv_view *v, int grid_rows);

/* Sets the last run's ua_tag (a bx_ua_tag code: the user-agent box identity of its
 * nearest block-level ancestor). Out-of-range values fail closed to BX_UA_NONE, i.e.
 * no user-agent margin. No-op on an empty view. spec/box_style.md 4d. */
void pv_set_ua_tag(pv_view *v, int ua_tag);

/* Sets the last run's cont_box_id (the box enclosing its container's items; -1 =
 * none). No-op on an empty view. */
void pv_set_cont_box(pv_view *v, int cont_box_id);
void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span);

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

/* Sets the symbolic percentage width cap (per-mille, 0 = none; Hito 32) on the
 * most recently appended run. No-op on an empty or NULL view; the append helpers
 * default box_w_pct to 0. */
void pv_set_box_pct(pv_view *v, int box_w_pct, int box_l_pct, int box_r_pct,
                    int box_mt_pct, int box_mb_pct);

/* Keystone (Stage 0) setter for the most recently appended run: the dom_node_id of
 * the source element. No-op on an empty or NULL view; the append helpers default
 * node_id to DOM_NODE_NONE. */
void pv_set_node_id(pv_view *v, dom_node_id node_id);

/* Box engine (Hito 23b-8) setter for the most recently appended run: the block_id of
 * the box-carrying block it belongs to (-1 = none). No-op on an empty or NULL view;
 * the append helpers default block_id to -1. The box's decoration is on pv_box_def. */
void pv_set_block_id(pv_view *v, int block_id);

/* Records the replaced element's own box def index on the last appended run. See
 * pv_run.own_box_id for why this is separate from pv_set_block_id. */
void pv_set_own_box(pv_view *v, int box_id);

/* Box engine (Hito 23b-8 Step D): appends one box definition to the box tree,
 * taking an owned copy of *d. The append order IS the block_id order (callers append
 * box 0, then 1, ...), so the new box's index equals its block_id. No-op returning
 * PV_ERR_NULL_ARG on NULL args. Used by pv_build (after the run walk) and by the IPC
 * deserialiser. */
pv_status pv_add_box_def(pv_view *v, const pv_box_def *d);

/* Appends a container descriptor; its index becomes a cont_id. NULL args =>
 * PV_ERR_NULL_ARG, allocation failure => PV_ERR_OOM. */
pv_status pv_add_cont_def(pv_view *v, const pv_cont_def *d);

/* pv_cont_count is v->ncont (0 when v is NULL); pv_cont_at returns conts[i]
 * (i == a cont_id) or NULL when out of range / NULL view. */
size_t pv_cont_count(const pv_view *v);
const pv_cont_def *pv_cont_at(const pv_view *v, size_t i);

/* Sets the input's checked state (-1 n/a, 0 unchecked, 1 checked) on the most
 * recently appended run. No-op on an empty or NULL view. */
void pv_set_input_checked(pv_view *v, int checked);

/* Sets the <select> options string ("opt||label||opt||label") on the most recently
 * appended run, taking an owned copy. No-op on a NULL view or empty cap. */
void pv_set_input_select_opts(pv_view *v, const char *select_opts);

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
