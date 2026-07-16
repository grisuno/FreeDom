/*
 * compositor (cx_) -- pure CSS stacking-context + paint-order logic.
 * See include/compositor.h and spec/compositor.md. No I/O, no Cairo, no allocation.
 */

#include "compositor.h"
#include "css.h" /* css_position / css_mix_blend / css_isolation constants */

/* A box is "positioned" for stacking purposes when position is anything but static
 * (and set). unset (0) behaves like static: in-flow. */
static int is_positioned(int position) {
    return position == CSS_POS_RELATIVE || position == CSS_POS_ABSOLUTE
        || position == CSS_POS_FIXED    || position == CSS_POS_STICKY;
}

int cx_forms_stacking_context(const cx_style *s) {
    if (s == NULL) return 0;
    /* opacity < 1 (a set percentage below 100). */
    if (s->opacity >= 0 && s->opacity < 100) return 1;
    /* mix-blend-mode other than normal (any real blend). */
    if (s->mix_blend > CSS_MB_NORMAL) return 1;
    /* isolation: isolate. */
    if (s->isolation == CSS_ISO_ISOLATE) return 1;
    /* transform other than none (M1.2). */
    if (s->has_transform) return 1;
    /* relative/absolute WITH a real z-index. */
    if ((s->position == CSS_POS_RELATIVE || s->position == CSS_POS_ABSOLUTE)
        && !s->z_auto) return 1;
    /* fixed / sticky always establish a stacking context. */
    if (s->position == CSS_POS_FIXED || s->position == CSS_POS_STICKY) return 1;
    return 0;
}

cx_layer cx_box_layer(const cx_style *s) {
    if (s == NULL) return CX_LAYER_BLOCK;
    if (cx_forms_stacking_context(s)) {
        if (!s->z_auto && s->z_index < 0) return CX_LAYER_NEG_Z;
        if (!s->z_auto && s->z_index > 0) return CX_LAYER_POS_Z;
        return CX_LAYER_ZERO_Z; /* z-index 0 or auto */
    }
    /* Not a stacking context: a positioned box with z:auto still paints in the
     * positioned/zero layer (CSS 2.1 App E point 8). */
    if (is_positioned(s->position)) return CX_LAYER_ZERO_Z;
    if (s->is_float) return CX_LAYER_FLOAT;
    if (s->is_inline) return CX_LAYER_INLINE;
    return CX_LAYER_BLOCK;
}

/* Effective z used to order within a layer: auto collapses to 0 (the ZERO_Z layer). */
static int eff_z(const cx_item *it) {
    return it->z_auto ? 0 : it->z_index;
}

int cx_item_compare(const cx_item *a, const cx_item *b) {
    if (a == NULL || b == NULL) {
        if (a == b) return 0;
        return (a == NULL) ? -1 : 1; /* NULL sorts first, defensively */
    }
    if (a->layer != b->layer) return (a->layer < b->layer) ? -1 : 1;
    int za = eff_z(a), zb = eff_z(b);
    if (za != zb) return (za < zb) ? -1 : 1;
    if (a->doc_order != b->doc_order) return (a->doc_order < b->doc_order) ? -1 : 1;
    return 0;
}

/* Stable insertion sort: n is bounded by the caller (BT_MAX_POSITIONED), so O(n^2)
 * is fine, and stability keeps equal-key boxes in their original relative order
 * (document order is already the final tie-break, so this only matters on true
 * key collisions). No allocation. */
void cx_sort(cx_item *items, size_t n) {
    if (items == NULL || n < 2) return;
    for (size_t i = 1; i < n; ++i) {
        cx_item key = items[i];
        size_t j = i;
        /* Shift strictly-greater elements up; `>= 0` compare keeps equal keys stable
         * because we stop as soon as items[j-1] is not greater than key. */
        while (j > 0 && cx_item_compare(&items[j - 1], &key) > 0) {
            items[j] = items[j - 1];
            --j;
        }
        items[j] = key;
    }
}
