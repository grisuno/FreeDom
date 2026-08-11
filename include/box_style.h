#ifndef FREEDOM_BOX_STYLE_H
#define FREEDOM_BOX_STYLE_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * box_style — the user-agent box model, per HTML tag.
 *
 * Pure, I/O-free, allocation-free classification (the directly auditable layer
 * between the DOM and the layout). Given a tag name it returns the default box
 * metrics (margins and padding, in em) and the display type; given an author
 * display token it decodes the keyword. It measures nothing and paints nothing.
 *
 * This is Freedom's user-agent stylesheet: the subset of CSS 2.1 default rules the
 * engine always applies. They are not author styles, so they are not gated by
 * caps.css. The author display parser (bx_parse_display) only decodes the token;
 * the CALLER decides whether to honour it, gated by caps.css (Secure by Default: a
 * document does not reconfigure the engine unless the user allows it).
 *
 * It is also the entry point to flex_layout: once an element is classified
 * BX_DISPLAY_FLEX or BX_DISPLAY_GRID, the geometric solver takes over.
 *
 * See spec/box_style.md for the full contract.
 */

typedef enum bx_display {
    BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width */
    BX_DISPLAY_INLINE,        /* flows with text; vertical margins ignored by layout */
    BX_DISPLAY_INLINE_BLOCK,  /* in-line box with its own dimensions (img, input) */
    BX_DISPLAY_LIST_ITEM,     /* like block, but the layout draws a marker (li) */
    BX_DISPLAY_FLEX,          /* flex container: resolved by flex_layout */
    BX_DISPLAY_GRID,          /* grid container: resolved by flex_layout */
    BX_DISPLAY_NONE           /* not rendered and takes no space (head, script...) */
} bx_display;

/* Box edges in em (multiples of the element's own font size). */
typedef struct bx_edges {
    double top, right, bottom, left;
} bx_edges;

typedef struct bx_box {
    bx_display display;
    bx_edges   margin;
    bx_edges   padding;
} bx_box;

typedef enum bx_status {
    BX_OK = 0,
    BX_ERR_NULL_ARG,  /* token or out was NULL */
    BX_ERR_SYNTAX     /* not a recognised display keyword (fails closed) */
} bx_status;

/* Horizontal placement of an author box inside an available width (px). */
typedef struct bx_hplace {
    double x_off;      /* left offset from the content area's left edge */
    double content_w;  /* width available to the block's inline content */
} bx_hplace;

/* UA default box for an HTML tag name (case-insensitive). tag == NULL, empty, or
 * unknown yields a neutral inline box with zero margins and padding (the safe
 * default: an unknown element invents no spacing). Returned by value; no
 * allocation. */
bx_box bx_default_for_tag(const char *tag);

/* Compact, stable identity of a block's SOURCE element, just wide enough to recover
 * its user-agent box on the far side of the render IPC without shipping a tag string
 * per block. Only the tags the HTML user-agent sheet gives a non-zero vertical margin
 * need a code: everything else (div, section, header, article, footer, nav, main,
 * table, tr, td, form, ...) shares BX_UA_NONE, whose UA margin is zero -- which is
 * both the correct answer and the fail-closed one (an unrecognised element invents no
 * spacing). spec/box_style.md 4d.
 *
 * The codes are an ABI between page_view, the IPC codec and the painter; APPEND
 * only, never renumber. */
typedef enum bx_ua_tag {
    BX_UA_NONE = 0,   /* no user-agent margin: div/section/td/... and unknown tags */
    BX_UA_P,
    BX_UA_H1, BX_UA_H2, BX_UA_H3, BX_UA_H4, BX_UA_H5, BX_UA_H6,
    BX_UA_UL, BX_UA_OL, BX_UA_MENU,
    BX_UA_DL,
    BX_UA_PRE,
    BX_UA_BLOCKQUOTE,
    BX_UA_FIGURE,
    BX_UA_HR,
    BX_UA_LI,         /* zero margin, but distinct: a list item is NOT an unknown tag */
    BX_UA_COUNT
} bx_ua_tag;

/* Maps an HTML tag name (case-insensitive) to its bx_ua_tag code. A tag the user-agent
 * sheet gives no vertical margin -- and any unknown, empty or NULL tag -- maps to
 * BX_UA_NONE. Pure, allocation-free, total. */
bx_ua_tag bx_ua_of_tag(const char *tag);

/* UA default box for a bx_ua_tag code: the same row of the same table
 * bx_default_for_tag reads, so the user-agent sheet has ONE definition. A code
 * outside 0..BX_UA_COUNT-1 fails closed to the neutral zero-margin box. Pure. */
bx_box bx_default_for_ua(bx_ua_tag id);

/* Decodes a CSS display keyword token (case-insensitive, ASCII-trimmed) into *out.
 * Recognises none / block / inline / inline-block / list-item / flex / inline-flex
 * / grid / inline-grid (inline-flex => FLEX, inline-grid => GRID). token/out NULL
 * => BX_ERR_NULL_ARG; empty, oversized, or unsupported => BX_ERR_SYNTAX (out
 * untouched). On BX_OK, *out is set. */
bx_status bx_parse_display(const char *token, bx_display *out);

/* Stable, short English name of a display type for structured/agent output. Never
 * NULL; an unknown enum value yields "inline". */
const char *bx_display_name(bx_display d);

/* Resolves the horizontal placement of an author box within avail_w (px). inset_l/
 * inset_r are the left/right insets (padding + non-auto margin of that side);
 * width_cap is the content-width cap (min of width/max-width already resolved, 0 =
 * none); center is 1 for `margin: 0 auto` (both horizontal margins auto + a width
 * cap). Pure, no allocation. Negative insets are clamped to 0; avail_w < 1 is
 * raised to 1; the result always has content_w >= 1 and x_off >= 0. With no box
 * (inset_l=inset_r=0, width_cap=0) it returns x_off 0 and content_w == avail_w. */
bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                   double avail_w);

/* Effective width cap combining the px cap (w_px, 0 = none) with a symbolic
 * per-mille cap (w_pct, 0 = none; Hito 32) resolved against the real available
 * width: both set => the tighter wins; neither (or avail_w <= 0 for the pct)
 * => 0 (no cap). Never negative. Pure. */
double bx_width_cap(int w_px, int w_pct, double avail_w);

/* Content-width cap adjusted for box-sizing (2026-07-11). With border_box set,
 * the declared width includes the horizontal padding and border, so the cap on
 * the CONTENT is width_cap minus those edges, clamped >= 1 (a border-box
 * narrower than its own edges never yields a negative width). border_box == 0
 * (content-box or unset) or width_cap <= 0 (no cap) are the identity. Negative
 * edges are treated as 0. Pure. */
double bx_content_cap(double width_cap, int border_box,
                      double pad_l, double pad_r, double bord_l, double bord_r);

#endif /* FREEDOM_BOX_STYLE_H */
