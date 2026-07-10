#ifndef FREEDOM_CSS_H
#define FREEDOM_CSS_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css — pure parser + simple cascade for AUTHOR CSS (<style> blocks and inline
 * style= attributes). Renders the page closer to what the webmaster intended,
 * with a deliberately simpler subset.
 *
 * CSS is hostile remote content, so this module is an auditable surface:
 *   - It NEVER phones home: any value containing url( is dropped, and every
 *     @-rule (@import/@font-face/@media/...) is skipped.
 *   - It is bounded (anti-DoS): rules/selectors/declarations are capped.
 *   - It fails closed: unparseable selectors/declarations are dropped, not guessed.
 *   - It executes nothing (expression()/var()/calc()/JS URLs are unknown -> ignored).
 *
 * It produces no pixels and opens no sockets: it resolves a small css_style value
 * for an element. page_view consults it; render_doc still gates the result behind
 * caps.css (Privacy by Default). See spec/css.md for the full contract.
 */

typedef enum css_status {
    CSS_OK = 0,
    CSS_ERR_NULL_ARG, /* out was NULL */
    CSS_ERR_OOM       /* allocation failed */
} css_status;

typedef enum css_align {
    CSS_ALIGN_UNSET = 0,
    CSS_ALIGN_LEFT,
    CSS_ALIGN_CENTER,
    CSS_ALIGN_RIGHT,
    CSS_ALIGN_JUSTIFY
} css_align;

typedef enum css_display {
    CSS_DISP_UNSET = 0,
    CSS_DISP_NONE,
    CSS_DISP_BLOCK,
    CSS_DISP_INLINE,
    CSS_DISP_INLINE_BLOCK,
    CSS_DISP_FLEX,
    CSS_DISP_GRID,
    CSS_DISP_OTHER
} css_display;

typedef enum css_justify {  /* justify-content (flex/grid main axis) */
    CSS_JUSTIFY_UNSET = 0,
    CSS_JUSTIFY_START,
    CSS_JUSTIFY_END,
    CSS_JUSTIFY_CENTER,
    CSS_JUSTIFY_SPACE_BETWEEN,
    CSS_JUSTIFY_SPACE_AROUND,
    CSS_JUSTIFY_SPACE_EVENLY
} css_justify;

/* Anti-DoS bounds for the flex/grid container params. */
#define CSS_GAP_MAX       4096   /* px cap on gap */
#define CSS_GRID_COLS_MAX 64     /* cap on grid-template-columns track count */
#define CSS_LINE_MIN      50     /* line-height clamp floor (percent) */
#define CSS_LINE_MAX      400    /* line-height clamp ceiling (percent, anti-DoS) */

/* text-decoration line bits, OR-combined into css_style.text_decoration. The field
 * is -1 when unset and 0 for an explicit `none` (so `a { text-decoration: none }`
 * can drop the default link underline). */
#define CSS_DECO_UNDERLINE    0x1
#define CSS_DECO_LINE_THROUGH 0x2
#define CSS_DECO_OVERLINE     0x4

/* Generic font family bucket (font-family). A specific family name is mapped to its
 * generic group; an unrecognised name leaves the field unset (UA sans-serif). */
typedef enum css_font_family {
    CSS_FF_UNSET = 0, CSS_FF_SERIF, CSS_FF_SANS, CSS_FF_MONO,
    CSS_FF_CURSIVE, CSS_FF_FANTASY
} css_font_family;

/* text-transform. 0 is unset; CSS_TT_NONE is an explicit `none`. */
typedef enum css_text_transform {
    CSS_TT_UNSET = 0, CSS_TT_NONE, CSS_TT_UPPERCASE, CSS_TT_LOWERCASE, CSS_TT_CAPITALIZE
} css_text_transform;

/* vertical-align (subset: only the inline shifts). 0 unset. */
typedef enum css_valign {
    CSS_VA_UNSET = 0, CSS_VA_BASELINE, CSS_VA_SUB, CSS_VA_SUPER
} css_valign;

/* white-space (subset: only the wrap/keep distinction is consumed). 0 unset. */
typedef enum css_white_space {
    CSS_WS_UNSET = 0, CSS_WS_NORMAL, CSS_WS_NOWRAP, CSS_WS_PRE,
    CSS_WS_PRE_WRAP, CSS_WS_PRE_LINE
} css_white_space;

/* list-style-type (and the type token of the list-style shorthand). 0 unset. */
typedef enum css_list_style {
    CSS_LS_UNSET = 0, CSS_LS_NONE, CSS_LS_DISC, CSS_LS_CIRCLE, CSS_LS_SQUARE,
    CSS_LS_DECIMAL, CSS_LS_LOWER_ALPHA, CSS_LS_UPPER_ALPHA,
    CSS_LS_LOWER_ROMAN, CSS_LS_UPPER_ROMAN
} css_list_style;

/* --- Layout / box decoration (Hito 23b-7) ---------------------------------- */

/* position. 0 unset; STATIC is the explicit in-flow default. RELATIVE offsets the
 * box from its in-flow spot; ABSOLUTE/FIXED take it out of flow; STICKY is the
 * scroll-pinned hybrid. The engine resolves the keyword here; how far each is
 * honoured at paint time is the presentation layer's call (a later milestone). */
typedef enum css_position {
    CSS_POS_UNSET = 0, CSS_POS_STATIC, CSS_POS_RELATIVE,
    CSS_POS_ABSOLUTE, CSS_POS_FIXED, CSS_POS_STICKY
} css_position;

/* box-sizing. 0 unset; CONTENT is content-box (width excludes padding/border),
 * BORDER is border-box (width includes them). */
typedef enum css_box_sizing {
    CSS_BOXS_UNSET = 0, CSS_BOXS_CONTENT, CSS_BOXS_BORDER
} css_box_sizing;

/* border-style / outline-style (subset). 0 unset; NONE/HIDDEN paint nothing. The
 * decorative variants are recognised so the cascade keeps them; the painter may
 * collapse the fancier ones (groove/ridge/inset/outset) to solid. */
typedef enum css_border_style {
    CSS_BST_UNSET = 0, CSS_BST_NONE, CSS_BST_HIDDEN, CSS_BST_SOLID,
    CSS_BST_DASHED, CSS_BST_DOTTED, CSS_BST_DOUBLE,
    CSS_BST_GROOVE, CSS_BST_RIDGE, CSS_BST_INSET, CSS_BST_OUTSET
} css_border_style;

/* flex-direction. 0 unset. */
typedef enum css_flex_direction {
    CSS_FD_UNSET = 0, CSS_FD_ROW, CSS_FD_ROW_REVERSE,
    CSS_FD_COLUMN, CSS_FD_COLUMN_REVERSE
} css_flex_direction;

/* flex-wrap. 0 unset. */
typedef enum css_flex_wrap {
    CSS_FW_UNSET = 0, CSS_FW_NOWRAP, CSS_FW_WRAP, CSS_FW_WRAP_REVERSE
} css_flex_wrap;

/* align-items / align-self / align-content / justify-items (cross-axis alignment).
 * 0 unset. AUTO only applies to align-self (it inherits the parent's align-items). */
typedef enum css_align_kw {
    CSS_AK_UNSET = 0, CSS_AK_AUTO, CSS_AK_STRETCH, CSS_AK_START, CSS_AK_END,
    CSS_AK_CENTER, CSS_AK_BASELINE,
    CSS_AK_SPACE_BETWEEN, CSS_AK_SPACE_AROUND, CSS_AK_SPACE_EVENLY
} css_align_kw;

/* grid-auto-flow (subset: the row/column axis only; `dense` is ignored). 0 unset. */
typedef enum css_grid_flow {
    CSS_GF_UNSET = 0, CSS_GF_ROW, CSS_GF_COLUMN
} css_grid_flow;

/* float. 0 unset; NONE is the explicit in-flow default. LEFT/RIGHT take the box out of
 * normal flow into a side-by-side float band (see spec/float.md). */
typedef enum css_float {
    CSS_FLOAT_UNSET = 0, CSS_FLOAT_NONE, CSS_FLOAT_LEFT, CSS_FLOAT_RIGHT
} css_float;

/* clear. 0 unset; NONE is the default. LEFT/RIGHT/BOTH drop the box below preceding
 * floats (v1 collapses the three to "end the float band"). */
typedef enum css_clear {
    CSS_CLEAR_UNSET = 0, CSS_CLEAR_NONE, CSS_CLEAR_LEFT, CSS_CLEAR_RIGHT, CSS_CLEAR_BOTH
} css_clear;

/* visibility. 0 unset; VISIBLE is the explicit default. HIDDEN paints nothing for the
 * box and its content but keeps its layout space (unlike display:none, which removes
 * it). COLLAPSE (meant for table rows/columns) has no real table-row model here, so it
 * collapses to the same HIDDEN behaviour -- a documented simplification. */
typedef enum css_visibility {
    CSS_VIS_UNSET = 0, CSS_VIS_VISIBLE, CSS_VIS_HIDDEN, CSS_VIS_COLLAPSE
} css_visibility;

/* overflow / overflow-x / overflow-y. 0 unset; VISIBLE is the explicit default. This
 * static, non-interactive renderer has no scrollbar machinery, so SCROLL/AUTO/HIDDEN
 * are resolved distinctly (for debug_dom / a future scrolling milestone) but the v1
 * presentation layer only distinguishes "clips" (HIDDEN/SCROLL/AUTO) from VISIBLE --
 * see spec/css.md for the exact staged scope. */
typedef enum css_overflow {
    CSS_OF_UNSET = 0, CSS_OF_VISIBLE, CSS_OF_HIDDEN, CSS_OF_SCROLL, CSS_OF_AUTO
} css_overflow;

/* cursor (subset of the CSS keyword list). 0 unset. v1 paint only distinguishes
 * POINTER (shows the hand cursor already used for links) from every other value
 * (shows the default arrow); the rest are resolved for completeness/debug_dom and a
 * future milestone that loads more cursor theme shapes -- see spec/css.md. */
typedef enum css_cursor {
    CSS_CUR_UNSET = 0, CSS_CUR_AUTO, CSS_CUR_DEFAULT, CSS_CUR_POINTER, CSS_CUR_TEXT,
    CSS_CUR_MOVE, CSS_CUR_NOT_ALLOWED, CSS_CUR_HELP, CSS_CUR_WAIT, CSS_CUR_CROSSHAIR,
    CSS_CUR_GRAB, CSS_CUR_ZOOM_IN, CSS_CUR_NONE
} css_cursor;

/* text-overflow. 0 unset; CLIP is the explicit default. ELLIPSIS only has a visible
 * effect where a line cannot wrap (white-space:nowrap) and would otherwise overflow
 * its box -- see spec/css.md. */
typedef enum css_text_overflow {
    CSS_TO_UNSET = 0, CSS_TO_CLIP, CSS_TO_ELLIPSIS
} css_text_overflow;

/* word-break / overflow-wrap / word-wrap, UNIFIED (a deliberate simplification, see
 * spec/css.md): 0 unset; NORMAL is the explicit UA default (no mid-word break);
 * BREAK allows a mid-word split when a single word does not fit its line. Real CSS
 * gives `word-break: break-all` (breaks greedily) and `overflow-wrap: break-word`/
 * `anywhere` (breaks only as a last resort) different semantics; this engine only
 * models "may a long word split", so all three keywords that request breaking map to
 * the same BREAK value. */
typedef enum css_word_break {
    CSS_WB_UNSET = 0, CSS_WB_NORMAL, CSS_WB_BREAK
} css_word_break;

/* text-decoration-style (Hito 23b-6 extension). 0 unset; the line drawing style
 * for underline/overline/line-through. The painter may collapse the fancier ones to
 * solid (v1 fallback). */
typedef enum css_text_decoration_style {
    CSS_TDS_UNSET = 0, CSS_TDS_SOLID, CSS_TDS_DOUBLE, CSS_TDS_DOTTED,
    CSS_TDS_DASHED, CSS_TDS_WAVY
} css_text_decoration_style;

/* direction (Hito 23b-6 extension). 0 unset; LTR is the explicit default. RTL
 * flips the inline flow direction. */
typedef enum css_direction {
    CSS_DIR_UNSET = 0, CSS_DIR_LTR, CSS_DIR_RTL
} css_direction;

/* border-collapse. 0 unset; SEPARATE is the explicit default (separate cell
 * borders); COLLAPSE merges adjacent borders into one. */
typedef enum css_border_collapse {
    CSS_BCOL_UNSET = 0, CSS_BCOL_COLLAPSE, CSS_BCOL_SEPARATE
} css_border_collapse;

/* empty-cells. 0 unset; SHOW draws cell background/border for empty <td>/<th>;
 * HIDE suppresses them (only when border-collapse is separate). */
typedef enum css_empty_cells {
    CSS_EC_UNSET = 0, CSS_EC_SHOW, CSS_EC_HIDE
} css_empty_cells;

/* caption-side. 0 unset; TOP is the explicit default; BOTTOM places the
 * <caption> below the table. */
typedef enum css_caption_side {
    CSS_CS_UNSET = 0, CSS_CS_TOP, CSS_CS_BOTTOM
} css_caption_side;

/* table-layout. 0 unset; AUTO is the explicit default (automatic table layout);
 * FIXED uses the declared column widths first. */
typedef enum css_table_layout {
    CSS_TL_UNSET = 0, CSS_TL_AUTO, CSS_TL_FIXED
} css_table_layout;

/* font-variant (subset: only small-caps). 0 unset; NONE is the explicit default;
 * SMALL_CAPS renders lowercase as small capitals. */
typedef enum css_font_variant {
    CSS_FV_UNSET = 0, CSS_FV_NORMAL, CSS_FV_SMALL_CAPS
} css_font_variant;

/* hyphens. 0 unset; MANUAL is the explicit default (hyphen only at &shy;);
 * AUTO allows the UA to hyphenate; NONE disables hyphenation. */
typedef enum css_hyphens {
    CSS_HY_UNSET = 0, CSS_HY_NONE, CSS_HY_MANUAL, CSS_HY_AUTO
} css_hyphens;

/* user-select. 0 unset; AUTO is the explicit default; NONE prevents selection;
 * TEXT allows; ALL selects all on one click. */
typedef enum css_user_select {
    CSS_US_UNSET = 0, CSS_US_NONE, CSS_US_TEXT, CSS_US_ALL, CSS_US_AUTO
} css_user_select;

/* appearance. 0 unset; AUTO is the explicit default (native-looking);
 * NONE removes native styling (common CSS reset). */
typedef enum css_appearance {
    CSS_AP_UNSET = 0, CSS_AP_AUTO, CSS_AP_NONE
} css_appearance;

/* pointer-events. 0 unset; AUTO is the explicit default; NONE makes the
 * element not a hit-test target. */
typedef enum css_pointer_events {
    CSS_PE_UNSET = 0, CSS_PE_AUTO, CSS_PE_NONE
} css_pointer_events;

/* background-repeat. 0 unset. */
typedef enum css_bg_repeat {
    CSS_BGR_UNSET = 0, CSS_BGR_REPEAT, CSS_BGR_NO_REPEAT,
    CSS_BGR_REPEAT_X, CSS_BGR_REPEAT_Y, CSS_BGR_SPACE, CSS_BGR_ROUND
} css_bg_repeat;
/* background-size. 0 unset. */
typedef enum css_bg_size {
    CSS_BGS_UNSET = 0, CSS_BGS_AUTO, CSS_BGS_COVER, CSS_BGS_CONTAIN
} css_bg_size;
/* background-clip. 0 unset. */
typedef enum css_bg_clip {
    CSS_BGC_UNSET = 0, CSS_BGC_BORDER_BOX, CSS_BGC_PADDING_BOX,
    CSS_BGC_CONTENT_BOX, CSS_BGC_TEXT
} css_bg_clip;
/* background-origin. 0 unset. */
typedef enum css_bg_origin {
    CSS_BGO_UNSET = 0, CSS_BGO_PADDING_BOX, CSS_BGO_BORDER_BOX, CSS_BGO_CONTENT_BOX
} css_bg_origin;
/* background-attachment. 0 unset. */
typedef enum css_bg_attachment {
    CSS_BGA_UNSET = 0, CSS_BGA_SCROLL, CSS_BGA_FIXED, CSS_BGA_LOCAL
} css_bg_attachment;
/* isolation. 0 unset. */
typedef enum css_isolation {
    CSS_ISO_UNSET = 0, CSS_ISO_AUTO, CSS_ISO_ISOLATE
} css_isolation;
/* contain bitmask values. 0 = none/unset. */
#define CSS_CONTAIN_SIZE   1
#define CSS_CONTAIN_LAYOUT 2
#define CSS_CONTAIN_STYLE  4
#define CSS_CONTAIN_PAINT  8
/* content-visibility. 0 unset. */
typedef enum css_content_visibility {
    CSS_CV_UNSET = 0, CSS_CV_VISIBLE, CSS_CV_AUTO, CSS_CV_HIDDEN
} css_content_visibility;
/* image-rendering. 0 unset. */
typedef enum css_image_rendering {
    CSS_IR_UNSET = 0, CSS_IR_AUTO, CSS_IR_PIXELATED, CSS_IR_CRISP_EDGES
} css_image_rendering;
/* color-scheme. 0 unset. */
typedef enum css_color_scheme {
    CSS_CSH_UNSET = 0, CSS_CSH_NORMAL, CSS_CSH_LIGHT, CSS_CSH_DARK
} css_color_scheme;
/* print-color-adjust. 0 unset. */
typedef enum css_print_color_adjust {
    CSS_PCA_UNSET = 0, CSS_PCA_ECONOMY, CSS_PCA_EXACT
} css_print_color_adjust;
/* forced-color-adjust. 0 unset. */
typedef enum css_forced_color_adjust {
    CSS_FCA_UNSET = 0, CSS_FCA_AUTO, CSS_FCA_NONE
} css_forced_color_adjust;

/* Anti-DoS clamps for the layout properties. Insets/z-index/order reuse CSS_LEN_*.
 * Border/outline widths and radius are non-negative px clamped to CSS_LEN_MAX.
 * border-spacing is clamped to [0, CSS_SPACING_MAX] like letter-spacing (a table
 * with 200+ px cell spacing is layout-poison, not a legitimate value). */
#define CSS_BORDER_W_MAX  CSS_LEN_MAX
#define CSS_BORDER_SPACING_MAX 200
#define CSS_FLEX_FACTOR_MAX 100000  /* flex-grow/-shrink stored x100; ~1000.0 cap */
#define CSS_GRID_SPAN_MAX 1000      /* grid-column/-row `span N` cap */

/* Anti-DoS clamps for the new metric properties (px, absolute value). text-indent
 * reuses the box-model CSS_LEN_MAX clamp (below). */
#define CSS_SPACING_MAX 200      /* letter-spacing / word-spacing */
#define CSS_SHADOW_MAX  100      /* text-shadow offsets */

/* Box-model lengths (margin/padding/width/max-width), in px. Two out-of-band
 * sentinels distinguish "not declared" and the 'auto' keyword from a real length;
 * a real length is clamped to [-CSS_LEN_MAX, CSS_LEN_MAX] (anti-DoS). */
#define CSS_LEN_MAX       100000
#define CSS_LEN_UNSET     (-2147483647 - 1) /* INT_MIN: property not set */
#define CSS_LEN_AUTO      (-2147483647)     /* INT_MIN+1: the 'auto' keyword */

/* Max compounds in one complex selector (subject + ancestor/parent constraints).
 * A deeper chain is dropped (fail closed). */
#define CSS_MAX_COMPOUNDS 4

/* Max attribute selectors ([attr], [attr=v], ...) in one compound. More are dropped
 * (the whole selector fails closed). */
#define CSS_MAX_ATTR_SEL  4

/* Max pseudo-classes (:link, :nth-child(...), ...) in one compound. More are
 * dropped (the whole selector fails closed). */
#define CSS_MAX_PSEUDO_SEL 4

/* Bound on the A/B coefficients of :nth-child(An+B) (anti-DoS; larger drops the
 * selector, fail closed). */
#define CSS_NTH_MAX 100000

/* A resolved presentation. Each field uses a sentinel for "unset" so the caller
 * can layer inheritance (take the first ancestor that sets each inheriting one).
 * The flex/grid container fields (gap/justify/grid_cols) are NOT inherited: they
 * describe the container element itself, so the caller reads them from that
 * element's resolved style, not up the ancestor chain. */
typedef struct css_style {
    int         color;       /* 0xRRGGBB or -1 (unset) */
    int         background;  /* 0xRRGGBB or -1 (unset) */
    css_align   text_align;  /* CSS_ALIGN_UNSET if absent */
    int         font_scale;  /* percent (e.g. 150), or 0 (unset) */
    int         line_scale;  /* line-height percent of the natural line box, or 0 (unset) */
    int         text_decoration; /* OR of CSS_DECO_*; 0 = none; -1 = unset */
    int         text_decoration_color; /* 0xRRGGBB or -1 (unset) */
    int         text_decoration_style; /* css_text_decoration_style, 0 (unset) */
    int         bold;        /* 1, 0, or -1 (unset) */
    int         italic;      /* 1, 0, or -1 (unset) */
    css_display display;     /* CSS_DISP_UNSET if absent */
    int         gap;         /* px between flex/grid items, or -1 (unset) */
    css_justify justify;     /* justify-content; CSS_JUSTIFY_UNSET if absent */
    int         grid_cols;   /* grid-template-columns track count, or 0 (unset) */
    /* Author box model (px; NOT inherited — read from the element's own style).
     * margins: CSS_LEN_UNSET / CSS_LEN_AUTO / signed px. padding: CSS_LEN_UNSET /
     * px >= 0. width/max_width: CSS_LEN_UNSET / px > 0 (auto/none -> unset). */
    int         margin_top, margin_right, margin_bottom, margin_left;
    int         pad_top, pad_right, pad_bottom, pad_left;
    int         width, max_width, min_width;
    int         height, min_height, max_height;
    /* Author text-presentation extensions (Hito 23b-6). All inherit in CSS; in this
     * flat model the caller takes the nearest ancestor that sets each. Like the other
     * author presentation, they are gated behind caps.css downstream. */
    int         font_family;     /* css_font_family, 0 (unset) */
    int         text_transform;  /* css_text_transform, 0 (unset) */
    int         letter_spacing;  /* px (signed), 0 = normal, CSS_LEN_UNSET (unset) */
    int         word_spacing;    /* px (signed), 0 = normal, CSS_LEN_UNSET (unset) */
    int         shadow_dx;       /* text-shadow x offset px (signed), 0 if no shadow */
    int         shadow_dy;       /* text-shadow y offset px (signed), 0 if no shadow */
    int         shadow_color;    /* text-shadow color 0xRRGGBB, or -1 (none/unset) */
    int         opacity;         /* percent 0..100, or -1 (unset) */
    int         valign;          /* css_valign, 0 (unset) */
    int         text_indent;     /* px (signed), CSS_LEN_UNSET (unset) */
    int         white_space;     /* css_white_space, 0 (unset) */
    int         tab_size;        /* number of spaces for tab, 0 (unset) */
    int         list_style;      /* css_list_style, 0 (unset) */
    int         direction;       /* css_direction, 0 (unset) */
    /* --- Layout / box decoration (Hito 23b-7). NOT inherited (read from the
     * element's own resolved style), like the box model. All gated behind caps.css
     * downstream except `display`/flex/grid container params, which are structure. */
    int         position;        /* css_position, 0 (unset) */
    int         inset_top, inset_right, inset_bottom, inset_left; /* CSS_LEN_UNSET/AUTO/px */
    int         z_index;         /* signed, or CSS_LEN_UNSET (unset; `auto` -> unset) */
    int         box_sizing;      /* css_box_sizing, 0 (unset) */
    /* Per-side border. widths: px >= 0 or CSS_LEN_UNSET. styles: css_border_style.
     * colors: 0xRRGGBB or -1 (unset). */
    int         border_top_width, border_right_width, border_bottom_width, border_left_width;
    int         border_top_style, border_right_style, border_bottom_style, border_left_style;
    int         border_top_color, border_right_color, border_bottom_color, border_left_color;
    int         border_radius;   /* px >= 0, or CSS_LEN_UNSET */
    /* box-shadow (single layer). offsets/blur/spread px; color 0xRRGGBB or -1 (none/
     * unset); inset 1/0, or -1 (unset). */
    int         shadow2_dx, shadow2_dy, shadow2_blur, shadow2_spread;
    int         box_shadow_color;
    int         box_shadow_inset;
    int         outline_width;   /* px >= 0, or CSS_LEN_UNSET */
    int         outline_style;   /* css_border_style */
    int         outline_color;   /* 0xRRGGBB or -1 */
    int         outline_offset;  /* px (signed), CSS_LEN_UNSET (unset) */
    /* Flex item + container extras. grow/shrink stored x100 (1.0 -> 100), -1 unset.
     * basis: px >= 0 / CSS_LEN_AUTO / CSS_LEN_UNSET. order/z reuse CSS_LEN_UNSET. */
    int         flex_grow, flex_shrink, flex_basis;
    int         order;           /* signed, or CSS_LEN_UNSET */
    int         align_items, align_self, align_content, justify_items; /* css_align_kw */
    int         flex_direction;  /* css_flex_direction */
    int         flex_wrap;       /* css_flex_wrap */
    /* Grid extras. grid_rows: track count, 0 unset. row_gap: px or -1 unset. */
    int         grid_rows;
    int         row_gap;
    int         grid_auto_flow;  /* css_grid_flow */
    int         grid_col_span, grid_row_span; /* `span N`, 0 unset */
    /* Float layout (spec/float.md). NOT inherited (read from the element's own resolved
     * style, like the box model). Layout structure, applied regardless of caps.css. */
    int         float_side;      /* css_float, 0 (unset) */
    int         clear;           /* css_clear, 0 (unset) */
    /* visibility / overflow / cursor. NOT inherited (read from the element's own
     * resolved style, like position/border). All gated behind caps.css downstream
     * (presentation, like the box decoration). */
    int         visibility;      /* css_visibility, 0 (unset) */
    int         overflow_x;      /* css_overflow, 0 (unset) */
    int         overflow_y;      /* css_overflow, 0 (unset) */
    int         cursor;          /* css_cursor, 0 (unset) */
    /* text-overflow / word-break (unified, see css_word_break). These INHERIT like
     * white-space, so the caller (page_view) takes the nearest ancestor that sets
     * each. Gated behind caps.css downstream. */
    int         text_overflow;   /* css_text_overflow, 0 (unset) */
    int         word_break;      /* css_word_break, 0 (unset) */
    /* Table properties. NOT inherited (read from the element's own resolved style). */
    int         border_collapse; /* css_border_collapse, 0 (unset) */
    int         border_spacing;  /* px (signed), CSS_LEN_UNSET (unset) */
    int         empty_cells;     /* css_empty_cells, 0 (unset) */
    int         caption_side;    /* css_caption_side, 0 (unset) */
    int         table_layout;    /* css_table_layout, 0 (unset) */
    /* Text-presentation extension (font-variant). INHERITS like other text props. */
    int         font_variant;    /* css_font_variant, 0 (unset) */
    /* Text/interaction properties. INHERIT by default (user-select, hyphens,
     * caret-color, pointer-events inherit per spec; appearance does not). */
    int         hyphens;         /* css_hyphens, 0 (unset) */
    int         user_select;     /* css_user_select, 0 (unset) */
    int         caret_color;     /* 0xRRGGBB or -1 (unset) */
    int         appearance;      /* css_appearance, 0 (unset) */
    int         pointer_events;   /* css_pointer_events, 0 (unset) */
    int         bg_repeat;        /* css_bg_repeat, 0 (unset) */
    int         bg_size;          /* css_bg_size, 0 (unset) */
    int         bg_clip;          /* css_bg_clip, 0 (unset) */
    int         bg_origin;        /* css_bg_origin, 0 (unset) */
    int         bg_attachment;    /* css_bg_attachment, 0 (unset) */
    int         isolation;        /* css_isolation, 0 (unset) */
    int         contain;          /* bitmask CSS_CONTAIN_*, 0 = none/unset */
    int         content_visibility; /* css_content_visibility, 0 (unset) */
    int         image_rendering;  /* css_image_rendering, 0 (unset) */
    int         color_scheme;     /* css_color_scheme, 0 (unset) */
    int         accent_color;     /* 0xRRGGBB or -1 (unset) */
    int         print_color_adjust;   /* css_print_color_adjust, 0 (unset) */
    int         forced_color_adjust;  /* css_forced_color_adjust, 0 (unset) */
} css_style;

typedef struct css_sheet css_sheet; /* opaque; owns the parsed rules */

/* Render-time media context for evaluating @media at parse time. width_px is a
 * fixed, normalized desktop width, so a (min/max-width) query leaks no real viewport
 * size (anti-fingerprinting). */
typedef struct css_media {
    int prefers_dark; /* 1: the user prefers a dark color scheme */
    int print;        /* 1: rendering for print (PDF); 0: screen */
    int width_px;     /* assumed viewport width for min/max-width queries */
} css_media;

#define CSS_MEDIA_DEFAULT_WIDTH 1920

/* Parses a <style> text (one or many blocks concatenated) into *out. Malformed
 * input never fails: unparseable rules are skipped. text == NULL is treated as
 * empty. out == NULL => CSS_ERR_NULL_ARG; allocation failure => CSS_ERR_OOM. On
 * CSS_OK, *out must be freed with css_free. Equivalent to css_parse_media with a
 * default screen / light / 1920px context. */
css_status css_parse(const char *text, size_t len, css_sheet **out);

/* As css_parse, but @media blocks are gated against *media (prefers-color-scheme,
 * screen/print/all, min/max-width). media == NULL uses the default screen/light/
 * 1920px context. Matched @media rules fold into the sheet as if unconditional, so
 * css_resolve is unchanged. @import/@font-face/other @-rules are still skipped. */
css_status css_parse_media(const char *text, size_t len, const css_media *media,
                           css_sheet **out);

/* Idempotent; NULL-safe. */
void css_free(css_sheet *s);

/* Computes the presentation for one element: every matching sheet rule applied in
 * cascade order (specificity, then document order), then the element's own
 * inline_style (which wins). sheet/tag/classes/inline_style may be NULL. Pure,
 * allocates nothing, reentrant. Inheritance is the caller's job (call per ancestor,
 * merge unset fields). */
css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                      const char *const *classes, size_t nclasses,
                      const char *inline_style, size_t inline_len);

/* One element attribute, for attribute selectors ([attr], [attr=v], [attr~=v], ...).
 * name is the lowercased local name; value is the attribute text ("" if empty). Both
 * alias caller storage (nothing is copied/owned). */
typedef struct css_attr {
    const char *name;
    const char *value;
} css_attr;

/* An element plus its ancestor chain, for combinator matching. Each field aliases
 * caller storage (nothing is copied/owned). parent walks toward the root (NULL at
 * the top). A bounded/partial chain is fine: a descendant compound that would have
 * matched a missing deeper ancestor simply does not match (fail closed). attrs/nattrs
 * may be empty (NULL/0): an attribute selector then simply does not match. */
typedef struct css_element {
    const char *tag;                  /* lowercased local name, or NULL */
    const char *id;                   /* id attribute value, or NULL */
    const char *const *classes;       /* class tokens (not NUL-joined) */
    size_t nclasses;
    const css_attr *attrs;            /* element attributes, or NULL */
    size_t nattrs;
    const struct css_element *parent; /* parent element, or NULL at the root */
    /* Sibling context (Hito 23b-9). All optional; zero/NULL = unknown, and the
     * structural pseudo-classes / sibling combinators then fail closed (never
     * mis-match). nth is the 1-based index among element siblings; nsib the
     * total element siblings including self; prev the previous element sibling. */
    int nth;
    int nsib;
    const struct css_element *prev;
} css_element;

/* As css_resolve, but matches descendant (`A B`) and child (`A > B`) combinators
 * against el's ancestor chain. el == NULL resolves only inline_style. Pure,
 * allocates nothing, reentrant. css_resolve is this with a parentless element. */
css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         const char *inline_style, size_t inline_len);

/* Convenience: resolve only an inline declaration list (no sheet, no selectors). */
css_style css_parse_inline(const char *style, size_t len);

#endif /* FREEDOM_CSS_H */
