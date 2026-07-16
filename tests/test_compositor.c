/*
 * TDD suite for compositor (cx_) -- pure CSS stacking-context + paint-order logic.
 * Red until src/compositor.c exists. See spec/compositor.md.
 */

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include "compositor.h"
#include "css.h" /* css_position / css_mix_blend / css_isolation value-space */

/* Build a cx_style with sane defaults (static, opaque, no blend, in-flow block),
 * then override the fields a test cares about. */
static cx_style base_style(void) {
    cx_style s = { .position = CSS_POS_STATIC, .z_index = 0, .z_auto = 1,
                   .opacity = -1, .mix_blend = 0, .isolation = 0,
                   .is_float = 0, .is_inline = 0 };
    return s;
}

/* --- cx_forms_stacking_context --- */

static void test_sc_opacity(void **state) {
    (void)state;
    cx_style s = base_style();
    s.opacity = 50;  assert_int_equal(cx_forms_stacking_context(&s), 1); /* < 1 */
    s.opacity = 100; assert_int_equal(cx_forms_stacking_context(&s), 0); /* opaque */
    s.opacity = -1;  assert_int_equal(cx_forms_stacking_context(&s), 0); /* unset */
    s.opacity = 0;   assert_int_equal(cx_forms_stacking_context(&s), 1); /* fully transparent still a context */
}

static void test_sc_mix_blend(void **state) {
    (void)state;
    cx_style s = base_style();
    s.mix_blend = CSS_MB_MULTIPLY; assert_int_equal(cx_forms_stacking_context(&s), 1);
    s.mix_blend = CSS_MB_NORMAL;   assert_int_equal(cx_forms_stacking_context(&s), 0);
    s.mix_blend = CSS_MB_UNSET;    assert_int_equal(cx_forms_stacking_context(&s), 0);
}

static void test_sc_isolation(void **state) {
    (void)state;
    cx_style s = base_style();
    s.isolation = CSS_ISO_ISOLATE; assert_int_equal(cx_forms_stacking_context(&s), 1);
    s.isolation = CSS_ISO_AUTO;    assert_int_equal(cx_forms_stacking_context(&s), 0);
    s.isolation = CSS_ISO_UNSET;   assert_int_equal(cx_forms_stacking_context(&s), 0);
}

static void test_sc_positioned_z(void **state) {
    (void)state;
    cx_style s = base_style();
    /* relative/absolute form a context only with a real z-index. */
    s.position = CSS_POS_RELATIVE; s.z_auto = 0; s.z_index = 3;
    assert_int_equal(cx_forms_stacking_context(&s), 1);
    s.z_auto = 1;
    assert_int_equal(cx_forms_stacking_context(&s), 0);
    s.position = CSS_POS_ABSOLUTE; s.z_auto = 0; s.z_index = -2;
    assert_int_equal(cx_forms_stacking_context(&s), 1);
}

static void test_sc_fixed_sticky_always(void **state) {
    (void)state;
    cx_style s = base_style();
    s.position = CSS_POS_FIXED;  assert_int_equal(cx_forms_stacking_context(&s), 1);
    s.position = CSS_POS_STICKY; assert_int_equal(cx_forms_stacking_context(&s), 1);
}

static void test_sc_static_none(void **state) {
    (void)state;
    cx_style s = base_style();
    assert_int_equal(cx_forms_stacking_context(&s), 0);
    assert_int_equal(cx_forms_stacking_context(NULL), 0); /* NULL-safe */
}

/* --- cx_box_layer --- */

static void test_layer_negative_z(void **state) {
    (void)state;
    cx_style s = base_style();
    s.position = CSS_POS_ABSOLUTE; s.z_auto = 0; s.z_index = -1;
    assert_int_equal(cx_box_layer(&s), CX_LAYER_NEG_Z);
}

static void test_layer_positive_z(void **state) {
    (void)state;
    cx_style s = base_style();
    s.position = CSS_POS_ABSOLUTE; s.z_auto = 0; s.z_index = 7;
    assert_int_equal(cx_box_layer(&s), CX_LAYER_POS_Z);
}

static void test_layer_zero_z_context(void **state) {
    (void)state;
    cx_style s = base_style();
    s.position = CSS_POS_RELATIVE; s.z_auto = 0; s.z_index = 0; /* context, z==0 */
    assert_int_equal(cx_box_layer(&s), CX_LAYER_ZERO_Z);
    s = base_style(); s.opacity = 40;                            /* context via opacity, no z */
    assert_int_equal(cx_box_layer(&s), CX_LAYER_ZERO_Z);
}

static void test_layer_zero_z_positioned_auto(void **state) {
    (void)state;
    cx_style s = base_style();
    s.position = CSS_POS_ABSOLUTE; s.z_auto = 1; /* positioned, z:auto -> ZERO_Z */
    assert_int_equal(cx_box_layer(&s), CX_LAYER_ZERO_Z);
}

static void test_layer_float(void **state) {
    (void)state;
    cx_style s = base_style();
    s.is_float = 1;
    assert_int_equal(cx_box_layer(&s), CX_LAYER_FLOAT);
}

static void test_layer_inline_and_block(void **state) {
    (void)state;
    cx_style s = base_style();
    s.is_inline = 1; assert_int_equal(cx_box_layer(&s), CX_LAYER_INLINE);
    s = base_style(); assert_int_equal(cx_box_layer(&s), CX_LAYER_BLOCK);
    assert_int_equal(cx_box_layer(NULL), CX_LAYER_BLOCK); /* NULL-safe default */
}

/* --- cx_item_compare --- */

static cx_item mk(cx_layer layer, int z, int z_auto, size_t doc, size_t ref) {
    cx_item it = { .layer = layer, .z_index = z, .z_auto = z_auto,
                   .doc_order = doc, .ref = ref };
    return it;
}

static void test_compare_layer_then_z_then_doc(void **state) {
    (void)state;
    cx_item a = mk(CX_LAYER_BLOCK, 0, 1, 0, 0);
    cx_item b = mk(CX_LAYER_POS_Z, 0, 1, 0, 0);
    assert_true(cx_item_compare(&a, &b) < 0);           /* lower layer first */
    assert_true(cx_item_compare(&b, &a) > 0);           /* antisymmetric sign */

    cx_item c = mk(CX_LAYER_POS_Z, 1, 0, 5, 0);
    cx_item d = mk(CX_LAYER_POS_Z, 9, 0, 1, 0);
    assert_true(cx_item_compare(&c, &d) < 0);           /* same layer -> z asc */

    cx_item e = mk(CX_LAYER_ZERO_Z, 0, 0, 3, 0);
    cx_item f = mk(CX_LAYER_ZERO_Z, 0, 1, 8, 0);        /* auto == 0 -> tie on z */
    assert_true(cx_item_compare(&e, &f) < 0);           /* doc order breaks the tie */

    cx_item g = mk(CX_LAYER_BLOCK, 0, 1, 2, 0);
    assert_int_equal(cx_item_compare(&g, &g), 0);       /* reflexive */
}

/* --- cx_sort --- */

static void test_sort_full_paint_order(void **state) {
    (void)state;
    /* One box per layer, out of order; expect the CSS App E sequence by ref id. */
    cx_item items[] = {
        mk(CX_LAYER_POS_Z,   2, 0, 0, 6),   /* positive z */
        mk(CX_LAYER_ROOT_BG, 0, 1, 0, 0),   /* background */
        mk(CX_LAYER_INLINE,  0, 1, 0, 4),   /* inline */
        mk(CX_LAYER_NEG_Z,  -3, 0, 0, 1),   /* negative z */
        mk(CX_LAYER_ZERO_Z,  0, 1, 0, 5),   /* z:0 / positioned auto */
        mk(CX_LAYER_BLOCK,   0, 1, 0, 2),   /* block */
        mk(CX_LAYER_FLOAT,   0, 1, 0, 3),   /* float */
    };
    cx_sort(items, sizeof items / sizeof items[0]);
    for (size_t i = 0; i < sizeof items / sizeof items[0]; ++i)
        assert_int_equal(items[i].ref, i); /* ref matches back-to-front layer index */
}

static void test_sort_z_within_layer(void **state) {
    (void)state;
    /* Positive-z stacking contexts order least-positive first, ties by document. */
    cx_item items[] = {
        mk(CX_LAYER_POS_Z, 10, 0, 1, 100),
        mk(CX_LAYER_POS_Z,  1, 0, 9, 101),
        mk(CX_LAYER_POS_Z,  1, 0, 2, 102), /* same z as 101, earlier doc */
        mk(CX_LAYER_POS_Z,  5, 0, 0, 103),
    };
    cx_sort(items, 4);
    assert_int_equal(items[0].ref, 102); /* z1, doc2 */
    assert_int_equal(items[1].ref, 101); /* z1, doc9 */
    assert_int_equal(items[2].ref, 103); /* z5 */
    assert_int_equal(items[3].ref, 100); /* z10 */
}

static void test_sort_stability(void **state) {
    (void)state;
    /* Identical keys (same layer, z, doc_order): original relative order preserved. */
    cx_item items[] = {
        mk(CX_LAYER_BLOCK, 0, 1, 0, 200),
        mk(CX_LAYER_BLOCK, 0, 1, 0, 201),
        mk(CX_LAYER_BLOCK, 0, 1, 0, 202),
    };
    cx_sort(items, 3);
    assert_int_equal(items[0].ref, 200);
    assert_int_equal(items[1].ref, 201);
    assert_int_equal(items[2].ref, 202);
}

static void test_sort_noop_guards(void **state) {
    (void)state;
    cx_sort(NULL, 5);        /* no crash */
    cx_item one = mk(CX_LAYER_BLOCK, 0, 1, 0, 9);
    cx_sort(&one, 0);        /* n == 0 no-op */
    assert_int_equal(one.ref, 9);
}

/* The positioned subset the painter already orders by z-index (all in CX_LAYER_ZERO_Z
 * or NEG_Z/POS_Z) sorts identically through cx_sort, so wiring it later changes no
 * pixels where no new stacking context appears. */
static void test_sort_matches_zindex_only_ordering(void **state) {
    (void)state;
    cx_item items[] = {
        mk(CX_LAYER_ZERO_Z,  5, 0, 0, 0),
        mk(CX_LAYER_ZERO_Z, -1, 0, 1, 1),
        mk(CX_LAYER_ZERO_Z,  0, 0, 2, 2),
    };
    cx_sort(items, 3);
    assert_int_equal(items[0].z_index, -1);
    assert_int_equal(items[1].z_index, 0);
    assert_int_equal(items[2].z_index, 5);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_sc_opacity),
        cmocka_unit_test(test_sc_mix_blend),
        cmocka_unit_test(test_sc_isolation),
        cmocka_unit_test(test_sc_positioned_z),
        cmocka_unit_test(test_sc_fixed_sticky_always),
        cmocka_unit_test(test_sc_static_none),
        cmocka_unit_test(test_layer_negative_z),
        cmocka_unit_test(test_layer_positive_z),
        cmocka_unit_test(test_layer_zero_z_context),
        cmocka_unit_test(test_layer_zero_z_positioned_auto),
        cmocka_unit_test(test_layer_float),
        cmocka_unit_test(test_layer_inline_and_block),
        cmocka_unit_test(test_compare_layer_then_z_then_doc),
        cmocka_unit_test(test_sort_full_paint_order),
        cmocka_unit_test(test_sort_z_within_layer),
        cmocka_unit_test(test_sort_stability),
        cmocka_unit_test(test_sort_noop_guards),
        cmocka_unit_test(test_sort_matches_zindex_only_ordering),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
