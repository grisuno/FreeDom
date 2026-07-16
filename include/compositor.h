#ifndef FREEDOM_COMPOSITOR_H
#define FREEDOM_COMPOSITOR_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * compositor (cx_) -- pure CSS stacking-context + paint-order logic (CSS 2.1
 * Appendix E / CSS Positioned Layout). No I/O, no Cairo, no GPU, no surface
 * allocation: given a box's already-resolved style scalars it decides (a) whether
 * the box establishes a stacking context and (b) which of the seven paint-order
 * layers it paints in, and gives a deterministic total order for painting a set of
 * boxes. It is the single source of truth for "what paints on top of what" -- the
 * foundation the layer/compositor painter (M1.1) and transform/animation/filter
 * (M1.2..M1.4) build on. Like js_policy/webcaps it is decision logic over validated
 * scalars, so it is directly testable and needs no fuzzing (it parses no remote
 * content). The Cairo orchestration (offscreen layer surfaces, group opacity,
 * blend) lives on the trusted side and consumes this module.
 *
 * See spec/compositor.md.
 */

/* Paint-order layers within one stacking context, back to front (CSS 2.1 App E). */
typedef enum cx_layer {
    CX_LAYER_ROOT_BG = 0, /* the context element's own background + borders */
    CX_LAYER_NEG_Z,       /* child stacking contexts with z-index < 0 */
    CX_LAYER_BLOCK,       /* in-flow, non-positioned, block-level descendants */
    CX_LAYER_FLOAT,       /* non-positioned floats */
    CX_LAYER_INLINE,      /* in-flow, inline-level, non-positioned descendants */
    CX_LAYER_ZERO_Z,      /* z-index:0 stacking contexts + z-index:auto positioned */
    CX_LAYER_POS_Z        /* child stacking contexts with z-index > 0 */
} cx_layer;

/* A box's resolved style, in the SAME value-spaces as css.h: position uses
 * css_position (CSS_POS_STATIC/RELATIVE/ABSOLUTE/FIXED/STICKY), mix_blend uses
 * css_mix_blend (0 unset, CSS_MB_NORMAL, or a real blend), isolation uses
 * css_isolation (0 unset, CSS_ISO_AUTO, CSS_ISO_ISOLATE). z_auto == 1 means the
 * z-index is auto/unset (z_index is then ignored). opacity is a percent 0..100, or
 * -1 for unset (opaque). is_float / is_inline classify the box's in-flow role. */
typedef struct cx_style {
    int position;
    int z_index;
    int z_auto;
    int opacity;
    int mix_blend;
    int isolation;
    int is_float;
    int is_inline;
} cx_style;

/* Does this box establish a stacking context? (The root context is the caller's.)
 * NULL-safe: returns 0. See spec/compositor.md section 2 for the rule set. */
int cx_forms_stacking_context(const cx_style *s);

/* The paint-order layer this box belongs to within its parent stacking context.
 * NULL-safe: returns CX_LAYER_BLOCK (the in-flow default). */
cx_layer cx_box_layer(const cx_style *s);

/* One box to order for painting: its layer, z-index (z_auto treated as 0 within the
 * ZERO_Z layer), document order (stable tie-break), and an opaque caller handle
 * (e.g. a box index) that this module never interprets. */
typedef struct cx_item {
    cx_layer layer;
    int      z_index;
    int      z_auto;
    size_t   doc_order;
    size_t   ref;
} cx_item;

/* Total paint order: layer ascending, then z-index ascending (auto == 0), then
 * document order ascending. Returns <0, 0 or >0 like a qsort comparator. NULL-safe
 * (a NULL operand sorts first, defensively). */
int cx_item_compare(const cx_item *a, const cx_item *b);

/* Stable in-place sort of `items` into paint order (uses cx_item_compare). Stable:
 * equal keys keep their original relative order. NULL or n == 0 is a no-op. */
void cx_sort(cx_item *items, size_t n);

#endif /* FREEDOM_COMPOSITOR_H */
