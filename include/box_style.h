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

/* UA default box for an HTML tag name (case-insensitive). tag == NULL, empty, or
 * unknown yields a neutral inline box with zero margins and padding (the safe
 * default: an unknown element invents no spacing). Returned by value; no
 * allocation. */
bx_box bx_default_for_tag(const char *tag);

/* Decodes a CSS display keyword token (case-insensitive, ASCII-trimmed) into *out.
 * Recognises none / block / inline / inline-block / list-item / flex / inline-flex
 * / grid / inline-grid (inline-flex => FLEX, inline-grid => GRID). token/out NULL
 * => BX_ERR_NULL_ARG; empty, oversized, or unsupported => BX_ERR_SYNTAX (out
 * untouched). On BX_OK, *out is set. */
bx_status bx_parse_display(const char *token, bx_display *out);

/* Stable, short English name of a display type for structured/agent output. Never
 * NULL; an unknown enum value yields "inline". */
const char *bx_display_name(bx_display d);

#endif /* FREEDOM_BOX_STYLE_H */
