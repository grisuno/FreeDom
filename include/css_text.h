#ifndef FREEDOM_CSS_TEXT_H
#define FREEDOM_CSS_TEXT_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include "css_decl.h"

int ct_interp_fontfamily(const char *v);
int ct_interp_texttransform(const char *v);
int ct_interp_opacity(const char *v);
int ct_interp_valign(const char *v);
int ct_expand_valign(const char *val, css_decl *dst, int cap);
int ct_interp_transition_property(const char *v);
int ct_interp_whitespace(const char *v);
int ct_interp_tabsize(const char *v);
int ct_interp_textdeco_style(const char *v);
int ct_interp_textdeco_thickness(const char *v);
int ct_interp_aspect_ratio(const char *v, int *num, int *den);
int ct_interp_direction(const char *v);
int ct_interp_liststyle(const char *v);
int ct_interp_spacing(const char *v, int *out);
int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);
int ct_expand_shadow(const char *val, css_decl *dst, int cap);

#endif
