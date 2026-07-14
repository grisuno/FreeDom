#ifndef FREEDOM_RENDER_DOC_H
#define FREEDOM_RENDER_DOC_H

#include <stddef.h>

#include "page_view.h"
#include "render_policy.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * render_doc — turns a page_view display list plus the page's render
 * capabilities into a flat, paint-ready document of styled blocks.
 *
 * Pure, I/O-free policy/shape logic: the directly auditable layer between the
 * inert display list (page_view) and the presentation orchestrator (the GUI and
 * the --headless writer). It decides WHAT to show and HOW to label it (a semantic
 * style plus, for images, the render_policy decision); it never produces pixels,
 * fonts or colours, which belong to the presentation layer.
 *
 * Both orchestrators consume the same rd_doc, so the "this is a heading / this is
 * a blocked tracking image / warn the user about images" rules live in exactly
 * one tested place. See spec/render_doc.md for the full contract.
 */

/* Reason an ALLOWed image could not be loaded (post-decision failure). Zero means
 * no failure (loaded OK or not yet attempted). Fetched images that fail network/TLS
 * get IMG_FAIL_FETCH; those that the worker cannot decode get IMG_FAIL_DECODE;
 * local file reads that fail get IMG_FAIL_LOCAL_READ. Stored per block so the
 * painter can give a diagnostic (e.g. "image (TLS/network error)") instead of a
 * generic placeholder. */
typedef enum img_fail_reason {
    IMG_FAIL_OK = 0,
    IMG_FAIL_FETCH,       /* network/TLS/policy error during fetch */
    IMG_FAIL_DECODE,      /* format not recognised by the worker decode (SVG, BMP, ICO, corrupt) */
    IMG_FAIL_LOCAL_READ,  /* local file:// page: read failed (missing, oversized) */
    IMG_FAIL_SURFACE,     /* Cairo surface creation failed (OOM) */
} img_fail_reason;

typedef enum rd_kind {
    RD_HEADING = 0,   /* heading text; heading_level is 1..6 */
    RD_PARAGRAPH,     /* body text */
    RD_LINK,          /* hyperlink text; href is the target */
    RD_IMAGE,         /* image placeholder; href is the src, img_decision is set */
    RD_NOTICE,        /* a user-agent notice (e.g. the image tracking warning) */
    RD_INPUT,         /* a form control; text is placeholder/label, href is the form action */
    RD_VIDEO          /* a <video>/<audio> element; href is the src, text is alt/label
                       * poster_src holds the poster URL (NULL for audio) */
} rd_kind;

/* One paint-ready block in document order. text is owned, NUL-terminated and
 * valid UTF-8. href is owned and NUL-terminated for RD_LINK (link target),
 * RD_IMAGE (image src) and RD_INPUT (the owning form's action); NULL otherwise.
 * img_decision is meaningful only for RD_IMAGE. The input_* fields are meaningful
 * only for RD_INPUT: input_type is a pv_input_type; name/value are owned (NULL when
 * absent) and carry the submitted bytes verbatim; form_id groups controls of one
 * form (-1 = none); form_method is a pv_form_method. */
typedef struct rd_block {
    rd_kind          kind;
    int              heading_level;  /* 1..6 for RD_HEADING, else 0 */
    int              bold;           /* inline emphasis: inside <b>/<strong>/<th> */
    int              italic;         /* inline emphasis: inside <i>/<em> */
    int              indent;         /* list nesting depth (ul/ol ancestors); 0 if none */
    int              block_break;    /* nonzero: a block boundary precedes this block */
    char            *text;
    char            *href;
    rdp_img_decision img_decision;
    img_fail_reason  img_fail;       /* IMG_OK unless the image's fetch/decode failed */
    char            *poster_src;     /* RD_VIDEO: poster image URL; NULL otherwise */
    int              video_w;        /* RD_VIDEO: declared width in px, or -1 */
    int              video_h;        /* RD_VIDEO: declared height in px, or -1 */
    int              fg_rgb;         /* author color packed 0xRRGGBB, or -1; set only with caps.css */
    int              bg_rgb;         /* author background-color packed 0xRRGGBB, or -1; set only with caps.css */
    int              text_align;     /* author text-align (css_align); set only with caps.css, else 0 */
    int              font_scale;     /* author font-size percent (100=normal); set only with caps.css, else 0 */
    int              line_scale;     /* author line-height percent of the line box; set only with caps.css, else 0 */
    int              text_decoration;/* author text-decoration (OR of CSS_DECO_*); set only with caps.css, else -1 (unset) */
    /* Author text-decoration sub-properties (color/style/thickness). Same caps.css
     * gate as text_decoration above. Defaults: color -1, style 0, thickness -1. */
    int              text_decoration_color;
    int              text_decoration_style;
    int              text_decoration_thickness;
    /* Author text-presentation extensions (Hito 23b-6); set only with caps.css, else
     * their no-effect defaults (font_family 0, text_transform 0, letter/word/indent
     * PV_LEN_UNSET, shadow_color -1, opacity -1, valign 0, white_space 0). */
    int              font_family;
    int              text_transform;
    int              letter_spacing;
    int              word_spacing;
    int              shadow_dx, shadow_dy, shadow_color;
    int              opacity;
    int              valign;
    int              text_indent;
    int              white_space;
    /* 2026-07-10 text-extension batch (set only with caps.css, else their
     * no-effect defaults set by rd_push): tab_size (0 -> 8 in <pre>), direction
     * (css_direction), font_variant (css_font_variant), list_style_pos (css_list_pos). */
    int              tab_size;
    int              direction;
    int              font_variant;
    int              list_style_pos;
    int              text_overflow;  /* author text-overflow (css_text_overflow); set only with caps.css, else 0 */
    int              word_break;     /* author word-break (css_word_break); set only with caps.css, else 0 */
    /* 2026-07-10 wiring batch, same caps.css gate. image_rendering is meaningful
     * on RD_IMAGE (pixelated/crisp-edges ask the painter for a nearest-neighbour
     * scaling filter); caret_color on RD_INPUT (tints the focused control's
     * caret; -1 = theme caret). */
    int              image_rendering; /* css_image_rendering; set only with caps.css, else 0 */
    int              caret_color;     /* 0xRRGGBB; set only with caps.css, else -1 */
    /* Nearest author flex/grid container of this block (page_view), carried by
     * default (layout is structure, not author styling, and leaks nothing to the
     * network) so the presentation layer can lay it out with box_tree/flex_layout.
     * cont_id groups blocks of one container (-1 = none); the rest are its params. */
    int              cont_id;        /* container group id, or -1 */
    int              cont_display;   /* bx_display (flex/grid), or 0 */
    int              cont_gap;       /* container gap in px */
    int              cont_justify;   /* fx_justify of the container */
    int              cont_cols;      /* grid column count, or 0 */
    /* Grid track sizes of the container (2026-07-11; 0 auto / >0 px / <0 fr x100,
     * see pv_run) and this block's ITEM column span (<= 0 = 1). Structure like
     * cont_*, never gated. */
    int              cont_col_w[PV_GRID_TRACKS];
    int              grid_span;
    /* Stage 3a: flex per-item values (structure, carried regardless of caps.css,
     * like cont_*). Copied from pv_run; the GUI's layout_container feeds them to
     * bt_node.grow/shrink/basis. Defaults: grow -1, shrink -1, basis CSS_LEN_UNSET,
     * order CSS_LEN_UNSET, direction 0. */
    int              flex_grow;      /* x100 (1.0 -> 100), or -1 (unset) */
    int              flex_shrink;    /* x100 (1.0 -> 100), or -1 (unset) */
    int              flex_basis;     /* px, CSS_LEN_AUTO, or CSS_LEN_UNSET */
    int              flex_order;     /* signed, or CSS_LEN_UNSET (unset) */
    int              flex_direction; /* css_flex_direction, 0 (unset -> row) */
    /* Container-item ordinal: consecutive blocks sharing (cont_id, cont_item) are
     * fragments of ONE flex/grid item and flow together in one cell. Structure like
     * cont_* (never gated). -1 = no container. */
    int              cont_item;
    /* flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM). Structure,
     * never gated. Defaults: cont_wrap 0, cont_row_gap -1 (falls back to cont_gap),
     * cont_align_items/flex_align_self 0 (CSS_AK_UNSET). */
    int              cont_wrap;
    int              cont_row_gap;
    int              cont_align_items;
    int              flex_align_self;
    /* Float layout (spec/float.md). float_side (css_float), float_id (floated-element
     * group id, -1 = none), float_clear (css_clear). Structure like cont_* (never
     * gated). Defaults: 0 / -1 / 0. */
    int              float_side, float_id, float_clear;
    /* Author box model (Hito 23b-3); set only with caps.css, else 0 / PV_LEN_UNSET.
     * box_l/box_r: left/right insets px; box_w: content-width cap px (0 = none);
     * box_center: margin: 0 auto; box_mt/box_mb: top/bottom margin override px or
     * PV_LEN_UNSET (use the user-agent margin). */
    int              box_l, box_r, box_w, box_center, box_mt, box_mb;
    /* Symbolic per-mille width cap (Hito 32), 0 = none; resolved against the real
     * available width by the painter (bx_width_cap). Gated by caps.css like box_w. */
    int              box_w_pct;
    /* Keystone (Stage 0): stable document-order element identity. node_id is the
     * dom_node_id of the source element for this block, copied from pv_run. It is
     * STRUCTURE, carried regardless of caps.css (like block_id). DOM_NODE_NONE when
     * the block has no single source element. This is the link that lets the GUI
     * dispatch a click on a painted block to the worker's live DOM handler. */
    dom_node_id      node_id;
    /* Box engine (Hito 23b-8 Step D). block_id says which block-level box this block
     * belongs to (-1 = none); the box's decoration and parent_id live on the box-def
     * tree (rd_doc.boxes[block_id]), not here. block_id is gated by caps.css (like the
     * box tree): with author styling off there is no box, so blocks are not grouped
     * and the layout is byte-identical. See spec/box_engine.md. */
    int              block_id;
    int              input_type;     /* RD_INPUT: pv_input_type, else 0 */
    char            *name;           /* RD_INPUT: control name, or NULL */
    char            *value;          /* RD_INPUT: control value, or NULL */
    int              form_id;        /* RD_INPUT: owning-form group id, or -1 */
    int              form_method;    /* RD_INPUT: pv_form_method */
    int              checked;        /* RD_INPUT: -1=n/a, 0=unchecked, 1=checked */
    char            *select_opts;    /* RD_INPUT: pipe-sep options for select, or NULL */
} rd_block;

typedef struct rd_doc {
    rd_block *blocks;
    size_t    count;
    size_t    cap;
    int       has_images;  /* the page declared at least one image */
    /* Box engine (Hito 23b-8 Step D): the box-definition TREE. boxes[block_id]
     * describes one block-level box (decoration + parent_id); a block finds its box
     * via its block_id and its parent via boxes[block_id].parent_id. The whole list
     * is author presentation, so rd_build copies it ONLY with caps.css (empty
     * otherwise -> default render byte-identical). Reuses pv_box_def (same shape). */
    pv_box_def *boxes;
    size_t      nbox;
    size_t      boxcap;
} rd_doc;

typedef enum rd_status {
    RD_OK = 0,
    RD_ERR_NULL_ARG,  /* a required out pointer was NULL */
    RD_ERR_OOM        /* allocation failed */
} rd_status;

/* Builds the paint-ready document from an inert display list and the page's
 * capabilities. view == NULL is treated as an empty view. When the page declares
 * images and caps.images is false, a single RD_NOTICE block carrying
 * rdp_images_warning() is prepended so the user is always told. Each image
 * becomes an RD_IMAGE block whose img_decision is computed with
 * rdp_image_decision(caps, top_level_url, src, img_w, img_h) — Zero Trust,
 * revalidated per image. top_level_url may be NULL (e.g. a local file): image
 * decisions then fail closed. out == NULL => RD_ERR_NULL_ARG. On RD_OK, *out must
 * be released with rd_free. */
rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_url, rd_doc **out);

/* Idempotent; safe on NULL and safe to call twice. */
void rd_free(rd_doc *d);

/* Read accessors. NULL-safe. */
size_t          rd_count(const rd_doc *d);
const rd_block *rd_at(const rd_doc *d, size_t i);

/* Box tree accessors (Step D). rd_box_count is the number of box definitions (0 when
 * caps.css is off); rd_box_at returns boxes[i] (i == a block_id) or NULL. */
size_t            rd_box_count(const rd_doc *d);
const pv_box_def *rd_box_at(const rd_doc *d, size_t i);

/* Stable, short English name of a block kind for structured/agent output. Never
 * NULL; an unknown enum value yields "block". */
const char *rd_kind_name(rd_kind k);

/* Canonical HTML tag name for a block, so the presentation layer can look up its
 * user-agent box (box_style) without re-deriving the kind->tag mapping at the call
 * site. RD_HEADING -> "h1".."h6" (heading_level clamped to 1..6), RD_PARAGRAPH ->
 * "p", RD_LINK -> "a", RD_IMAGE -> "img", RD_INPUT -> "textarea"/"button"/"input"
 * by input_type. RD_NOTICE (a user-agent banner, not an HTML element) and a NULL
 * block yield NULL. The returned string is a static literal (not owned). */
const char *rd_block_tag(const rd_block *b);

/* Stable, short English label for an image placeholder, derived from its
 * decision (e.g. "image (allowed)" / "image blocked: tracking pixel"). Never
 * NULL. */
const char *rd_image_label(rdp_img_decision d);

/* Stable, short English diagnostic for a post-decision image failure (the reason
 * an ALLOWed image ended up as a placeholder). Returns NULL when reason is
 * IMG_FAIL_OK (not a failure) or the reason is unknown. */
const char *rd_image_fail_label(img_fail_reason reason);

/* Stable, short English name of a form control type (a pv_input_type value), e.g.
 * "text" / "password" / "submit". Never NULL; an unknown value yields "field". */
const char *rd_input_label(int input_type);

#endif /* FREEDOM_RENDER_DOC_H */
