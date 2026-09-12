#ifndef FREEDOM_CSS_GRADIENT_H
#define FREEDOM_CSS_GRADIENT_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>
#include "css_decl.h"

int cg_expand_bg_image(const char *val, css_decl *dst, int cap,
                       char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);
int cg_expand_background(const char *val, css_decl *dst, int cap,
                         char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);

#endif
