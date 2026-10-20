#ifndef FREEDOM_CSS_MASK_H
#define FREEDOM_CSS_MASK_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include "css_decl.h"

/* CSS Masking 1, alpha gradients only (spec/css_mask.md). Pure: no I/O, a mask can never fetch. */

#define CM_LAYERS 2

typedef enum cm_comp { CM_COMP_ADD = 0, CM_COMP_SUBTRACT, CM_COMP_INTERSECT, CM_COMP_EXCLUDE } cm_comp;
typedef enum cm_clip { CM_CLIP_BORDER = 0, CM_CLIP_PADDING, CM_CLIP_CONTENT } cm_clip;

/* One decoded layer. angle is CSS degrees; alpha[] is 0..255; pos[] is per-mille, -1 = evenly
 * spaced. kind 0 = no layer. */
typedef struct cm_layer {
    int kind;
    int nst;
    int angle;
    int alpha[4];
    int pos[4];
} cm_layer;

/* True for every property name this module owns (after the vendor prefix is removed). */
int cm_is_mask_prop(const char *prop);

/* Expands one mask declaration into cascade slots. Returns the number of decls written, 0 when
 * the value is unsupported or malformed (the caller drops the declaration). */
int cm_expand(const char *prop, const char *val, css_decl *dst, int cap, int webkit_vocab);

/* The three compact words of a layer, and back. */
void cm_encode_layer(const cm_layer *l, int *meta, int *alphas, int *poss);
void cm_decode_layer(int meta, int alphas, int poss, cm_layer *out);

#endif
