#ifndef FREEDOM_CSS_BOX_H
#define FREEDOM_CSS_BOX_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include "css_decl.h"

#define CB_AUTO_REJECT 0
#define CB_AUTO_VALUE 1
#define CB_AUTO_RESET 2
#define CB_AUTO_RESET_NONE 3

int cb_length_px(const char *v, double *px);
int cb_interp_len(const char *v, int allow_auto, int *out);
int cb_emit_len(css_decl *dst, int cap, int slot, const char *val,
                int allow_auto, int allow_neg);
int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
                   css_decl *dst, int cap);
int cb_expand_box2(const char *val, int slot_start, int slot_end,
                   int allow_auto, int allow_neg, css_decl *dst, int cap);
int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                 int *out_px, int *out_pm);
int cb_value_em_milli(const char *v);
int cb_lp_can_be_nonneg(int px_val, int pct_pm);
int cb_next_ws_token(const char **p, char *tok, size_t cap);
int cb_interp_align(const char *v);
int cb_interp_fontsize_ex(const char *v, int *abs_out);
int cb_interp_lineheight(const char *v);
int cb_interp_weight(const char *v);
int cb_interp_style(const char *v);
int cb_interp_textdeco(const char *v);
int cb_interp_display(const char *v);
int cb_interp_gap(const char *v);
int cb_interp_justify(const char *v);
int cb_interp_gridcols(const char *v);
int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);

#endif
