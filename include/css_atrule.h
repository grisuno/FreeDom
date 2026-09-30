#ifndef FREEDOM_CSS_ATRULE_H
#define FREEDOM_CSS_ATRULE_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_atrule -- @supports condition evaluation and @layer cascade ranks.
 * Pure: no I/O, no DOM, no allocation. See spec/css_atrule.md.
 */

#define CAR_MAX_DEPTH      16     /* nested parens in one @supports condition */
#define CAR_MAX_LAYERS     256    /* distinct named/anonymous layers per sheet */
#define CAR_LAYER_NAME_MAX 128    /* bytes of a full dotted layer name, exclusive */
#define CAR_INLINE_SPEC    ((CAR_MAX_LAYERS + 2) << 16)

/* The questions @supports asks the caller's own engine. prop is lowercased and
 * both strings are trimmed and NUL-terminated. Nonzero = supported. */
typedef struct car_ops {
    int (*decl_ok)(void *ctx, const char *prop, const char *value);
    int (*selector_ok)(void *ctx, const char *sel);
    void *ctx;
} car_ops;

/* Evaluates the @supports prelude s[a,b). 1 = true, 0 = false or malformed. */
int car_supports(const char *s, size_t a, size_t b, const car_ops *ops);

typedef struct car_layers {
    char   name[CAR_MAX_LAYERS][CAR_LAYER_NAME_MAX];
    size_t n;
    int    anon;   /* anonymous layers registered so far (their names are synthetic) */
} car_layers;

/* Rank (1..CAR_MAX_LAYERS) of the layer whose full dotted name is name[0,len),
 * registering it on first sight. len == 0 registers a fresh anonymous layer. A
 * name at/over CAR_LAYER_NAME_MAX, or a full registry, maps to CAR_MAX_LAYERS. */
int car_layer_rank(car_layers *L, const char *name, size_t len);

/* Folds layer rank and specificity into one comparable value (layer first). layer
 * 0 = unlayered. Important declarations reverse the layer order. */
int car_effective_spec(int spec, int layer, int important);

#endif /* FREEDOM_CSS_ATRULE_H */
