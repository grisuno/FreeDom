#ifndef FREEDOM_CSS_VALUES_H
#define FREEDOM_CSS_VALUES_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/* Single owner of CSS value interpretation for colors and backgrounds.
 * Extracted from css.c value-interpreter block. Pure, bounded, fail-closed.
 * See spec/css_values.md. */

int cv_parse_color(const char *v);
int cv_interp_color(const char *v);
int cv_color_ok(int c);
int cv_bg_alpha_of(const char *v);
/* cv_parse_color with the color's alpha as TRANSPARENCY in bits 24..30 (0 opaque,
 * 127 clear): an opaque color is exactly cv_parse_color's 0xRRGGBB. Sentinels
 * (-1 invalid, CC_COLOR_CURRENT, CC_COLOR_TRANSPARENT) pass through unchanged. */
int cv_parse_color_t7(const char *v);
int cv_interp_bg(const char *v);

#endif
