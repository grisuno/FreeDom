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
int cv_interp_bg(const char *v);

#endif
