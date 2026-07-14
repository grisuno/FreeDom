#ifndef FREEDOM_CSS_COLOR_H
#define FREEDOM_CSS_COLOR_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_color — pure CSS color token parser.
 *
 * No I/O, no global state, no allocation. Decodes a single CSS color token
 * (hostile data with provenance) into an opaque 8-bit-per-channel RGB, or fails
 * closed. It paints nothing; it only decodes, so the rule lives in exactly one
 * auditable, tested place (page_view consults it when extracting an author color;
 * the rest of the pipeline carries the validated result).
 *
 * Supports #rgb / #rgba / #rrggbb / #rrggbbaa hex (alpha validated then dropped),
 * rgb()/rgba() with integer or percentage components, hsl()/hsla() with integer
 * H and percentage S/L, the extended set of CSS named colors,
 * transparent (stores as rbga(0,0,0,0)), and currentColor (resolved at render
 * time to the element's `color` property). Anything else (var(), color-mix(),
 * unknown names, junk) is CC_ERR_SYNTAX so the caller can fall back to the theme.
 *
 * See spec/css_color.md for the full contract.
 */

typedef struct cc_rgb {
    unsigned char r, g, b;
} cc_rgb;

typedef enum cc_status {
    CC_OK = 0,
    CC_ERR_NULL_ARG,  /* token or out was NULL */
    CC_ERR_SYNTAX,    /* not a recognised color (fails closed) */
    CC_CURRENT_COLOR, /* token was "currentColor" */
    CC_TRANSPARENT    /* token was "transparent" */
} cc_status;

/* Parses a CSS color token into out (opaque RGB). Case-insensitive; surrounding
 * ASCII whitespace is trimmed. token/out == NULL => CC_ERR_NULL_ARG; an empty,
 * oversized, out-of-range, or unsupported token => CC_ERR_SYNTAX
 * (out untouched). Returns CC_CURRENT_COLOR for "currentColor" or
 * CC_TRANSPARENT for "transparent" (out is set to black, the caller
 * must handle the sentinel via the packed color). */
cc_status cc_parse(const char *token, cc_rgb *out);

/* Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport
 * and for the pipeline's "no color" sentinel of -1). */
int cc_pack(cc_rgb c);

/* Inverse of cc_pack; bits above the low 24 are ignored. */
cc_rgb cc_unpack(int packed);

/* Sentinel values used by the cascade to represent special CSS color keywords.
 * -1  = unset / not specified (inherits or defaults to theme)
 * -2  = CC_COLOR_CURRENT   ("currentColor": use the element's `color` value)
 * -3  = CC_COLOR_TRANSPARENT ("transparent": fully transparent)
 */
#define CC_COLOR_CURRENT    (-2)
#define CC_COLOR_TRANSPARENT (-3)

#endif /* FREEDOM_CSS_COLOR_H */
