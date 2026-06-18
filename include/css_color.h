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
 * rgb()/rgba() with integer or percentage components, and the extended set of CSS
 * named colors. Anything else (hsl(), currentColor, var(), unknown names, junk)
 * is CC_ERR_SYNTAX so the caller can fall back to the theme color.
 *
 * See spec/css_color.md for the full contract.
 */

typedef struct cc_rgb {
    unsigned char r, g, b;
} cc_rgb;

typedef enum cc_status {
    CC_OK = 0,
    CC_ERR_NULL_ARG,  /* token or out was NULL */
    CC_ERR_SYNTAX     /* not a recognised color (fails closed) */
} cc_status;

/* Parses a CSS color token into out (opaque RGB). Case-insensitive; surrounding
 * ASCII whitespace is trimmed. token/out == NULL => CC_ERR_NULL_ARG; an empty,
 * oversized, out-of-range, transparent, or unsupported token => CC_ERR_SYNTAX
 * (out untouched). On CC_OK, *out is set. */
cc_status cc_parse(const char *token, cc_rgb *out);

/* Packs a color into a non-negative 0x00RRGGBB integer (suitable for transport
 * and for the pipeline's "no color" sentinel of -1). */
int cc_pack(cc_rgb c);

/* Inverse of cc_pack; bits above the low 24 are ignored. */
cc_rgb cc_unpack(int packed);

#endif /* FREEDOM_CSS_COLOR_H */
