#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "css_mask.h"

/* Finds the value a decl list assigns to prop, or def when absent. */
static int val_of(const css_decl *d, int n, int prop, int def) {
    for (int i = n - 1; i >= 0; --i) if (d[i].prop == prop) return d[i].ival;
    return def;
}
static int has(const css_decl *d, int n, int prop) {
    for (int i = 0; i < n; ++i) if (d[i].prop == prop) return 1;
    return 0;
}

static void test_prop_names(void **state)
{
    (void)state;
    assert_true(cm_is_mask_prop("mask"));
    assert_true(cm_is_mask_prop("mask-image"));
    assert_true(cm_is_mask_prop("mask-composite"));
    assert_true(cm_is_mask_prop("mask-clip"));
    assert_true(cm_is_mask_prop("mask-origin"));
    assert_false(cm_is_mask_prop("mask-size"));
    assert_false(cm_is_mask_prop("margin"));
    assert_false(cm_is_mask_prop(NULL));
}

static void test_fade_gradient(void **state)
{
    (void)state;
    css_decl d[16];
    int n = cm_expand("mask-image", "linear-gradient(#fff0, #fff 25%)", d, 16, 0);
    assert_true(n > 0);
    assert_int_equal(val_of(d, n, P_MASK_N, -1), 1);
    cm_layer l;
    cm_decode_layer(val_of(d, n, P_MASK_L0A, 0), val_of(d, n, P_MASK_L0B, 0),
                    val_of(d, n, P_MASK_L0C, 0), &l);
    assert_int_equal(l.kind, 1);
    assert_int_equal(l.nst, 2);
    assert_int_equal(l.angle, 180);
    assert_int_equal(l.alpha[0], 0);
    assert_int_equal(l.alpha[1], 255);
    assert_int_equal(l.pos[0], -1);
    /* positions keep 0.4% resolution (one byte each) */
    assert_true(l.pos[1] >= 246 && l.pos[1] <= 254);
}

/* A `url()` mask image is never fetched (no third-party request for decoration). Firefox does not
 * paint an element whose mask image is unavailable -- alone, XORed or ADDed with a gradient -- so
 * the layer list collapses to ONE fully transparent layer (GitLab's grey "mask" slabs, tanda 61). */
static void test_url_mask_is_unavailable_so_element_is_hidden(void **state)
{
    (void)state;
    const char *vals[] = {
        "url(https://x.invalid/a.svg)",
        "linear-gradient(#000,#000),url(https://x.invalid/a.svg)",
        "url(https://x.invalid/a.svg) center/cover no-repeat",
    };
    for (size_t k = 0; k < 3; ++k) {
        css_decl d[24];
        int n = cm_expand(k == 2 ? "mask" : "mask-image", vals[k], d, 24, 0);
        assert_true(n > 0);
        assert_int_equal(val_of(d, n, P_MASK_N, -1), 1);
        cm_layer l;
        cm_decode_layer(val_of(d, n, P_MASK_L0A, 0), val_of(d, n, P_MASK_L0B, 0),
                        val_of(d, n, P_MASK_L0C, 0), &l);
        assert_int_equal(l.kind, 1);
        assert_int_equal(l.alpha[0], 0);
        assert_int_equal(l.alpha[1], 0);
    }
}

static void test_gradient_border_technique(void **state)
{
    (void)state;
    css_decl d[24];
    int n = cm_expand("mask", "linear-gradient(#000 0 0) content-box,linear-gradient(#000 0 0)",
                      d, 24, 0);
    assert_true(n > 0);
    assert_int_equal(val_of(d, n, P_MASK_N, -1), 2);
    assert_int_equal(val_of(d, n, P_MASK_CLIP, -1), CM_CLIP_CONTENT | (CM_CLIP_BORDER << 2));
    cm_layer l;
    cm_decode_layer(val_of(d, n, P_MASK_L0A, 0), val_of(d, n, P_MASK_L0B, 0),
                    val_of(d, n, P_MASK_L0C, 0), &l);
    assert_int_equal(l.kind, 1);
    assert_int_equal(l.alpha[0], 255);
    assert_int_equal(l.alpha[1], 255);
    cm_decode_layer(val_of(d, n, P_MASK_L1A, 0), val_of(d, n, P_MASK_L1B, 0),
                    val_of(d, n, P_MASK_L1C, 0), &l);
    assert_int_equal(l.kind, 1);
    /* The shorthand resets the composite to add; mask-composite then sets it. */
    assert_int_equal(val_of(d, n, P_MASK_COMP, -1), CM_COMP_ADD);
    n = cm_expand("mask-composite", "exclude", d, 24, 0);
    assert_int_equal(n, 1);
    assert_int_equal(val_of(d, n, P_MASK_COMP, -1), CM_COMP_EXCLUDE);
}

static void test_composite_vocabularies(void **state)
{
    (void)state;
    css_decl d[4];
    assert_int_equal(cm_expand("mask-composite", "subtract", d, 4, 0), 1);
    assert_int_equal(d[0].ival, CM_COMP_SUBTRACT);
    assert_int_equal(cm_expand("mask-composite", "intersect", d, 4, 0), 1);
    assert_int_equal(d[0].ival, CM_COMP_INTERSECT);
    /* The old -webkit- words. */
    assert_int_equal(cm_expand("mask-composite", "xor", d, 4, 1), 1);
    assert_int_equal(d[0].ival, CM_COMP_EXCLUDE);
    assert_int_equal(cm_expand("mask-composite", "source-in", d, 4, 1), 1);
    assert_int_equal(d[0].ival, CM_COMP_INTERSECT);
    assert_int_equal(cm_expand("mask-composite", "source-out", d, 4, 1), 1);
    assert_int_equal(d[0].ival, CM_COMP_SUBTRACT);
    assert_int_equal(cm_expand("mask-composite", "source-over", d, 4, 1), 1);
    assert_int_equal(d[0].ival, CM_COMP_ADD);
    assert_int_equal(cm_expand("mask-composite", "bogus", d, 4, 0), 0);
}

static void test_clip_property(void **state)
{
    (void)state;
    css_decl d[4];
    assert_int_equal(cm_expand("mask-clip", "content-box", d, 4, 0), 1);
    assert_int_equal(d[0].prop, P_MASK_CLIP);
    assert_int_equal(d[0].ival, CM_CLIP_CONTENT | (CM_CLIP_CONTENT << 2));
    assert_int_equal(cm_expand("mask-clip", "padding-box", d, 4, 0), 1);
    assert_int_equal(d[0].ival, CM_CLIP_PADDING | (CM_CLIP_PADDING << 2));
    assert_int_equal(cm_expand("mask-clip", "text", d, 4, 0), 0);
}

static void test_unsupported_fails_closed(void **state)
{
    (void)state;
    css_decl d[16];
    assert_true(cm_expand("mask-image", "url(https://t.example/a.svg)", d, 16, 0) > 0); /* unavailable: hidden */
    assert_int_equal(cm_expand("mask-image", "url(data:image/svg+xml;base64,AAAA)", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask-image", "radial-gradient(#000,#fff)", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask-image", "linear-gradient(red)", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask-image", "linear-gradient(#000,#fff),linear-gradient(#000,#fff),"
                               "linear-gradient(#000,#fff)", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask-image", "", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask-image", "linear-gradient(#000,#fff)", d, 2, 0), 0);
    assert_int_equal(cm_expand("mask-image", NULL, d, 16, 0), 0);
}

static void test_none_resets(void **state)
{
    (void)state;
    css_decl d[16];
    int n = cm_expand("mask-image", "none", d, 16, 0);
    assert_true(n > 0);
    assert_int_equal(val_of(d, n, P_MASK_N, -1), 0);
    n = cm_expand("mask", "none", d, 16, 0);
    assert_true(n > 0);
    assert_int_equal(val_of(d, n, P_MASK_N, -1), 0);
    assert_true(has(d, n, P_MASK_COMP));
}

static void test_encode_decode_roundtrip(void **state)
{
    (void)state;
    cm_layer a = { 1, 3, 90, { 0, 128, 255, 0 }, { -1, 500, 1000, -1 } };
    int m, al, p;
    cm_encode_layer(&a, &m, &al, &p);
    cm_layer b;
    cm_decode_layer(m, al, p, &b);
    assert_int_equal(b.kind, 1);
    assert_int_equal(b.nst, 3);
    assert_int_equal(b.angle, 90);
    assert_int_equal(b.alpha[1], 128);
    assert_int_equal(b.alpha[2], 255);
    assert_int_equal(b.pos[0], -1);
    assert_int_equal(b.pos[1], 500);
    assert_int_equal(b.pos[2], 1000);
    /* Hostile words decode to a safe layer, never out of range. */
    cm_decode_layer(-1, -1, -1, &b);
    assert_true(b.nst >= 0 && b.nst <= 4);
    assert_true(b.angle >= 0 && b.angle < 360);
}


static void test_split_never_overruns(void **state)
{
    (void)state;
    css_decl d[16];
    /* More layers than the buffer holds, and more words than a layer's token array: the
     * splitter used to write one slot past the end before checking the limit. */
    assert_int_equal(cm_expand("mask-image", "none,none,none,none,none,none", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask", "a b c d e f g h i j k l m n o p q r s t u v w x y z", d, 16, 0), 0);
    assert_int_equal(cm_expand("mask-clip", "border-box,border-box,border-box,border-box,border-box", d, 16, 0), 0);
    char big[600];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(cm_expand("mask-image", big, d, 16, 0), 0);
}

int main(void)
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_prop_names),
        cmocka_unit_test(test_fade_gradient),
        cmocka_unit_test(test_url_mask_is_unavailable_so_element_is_hidden),
        cmocka_unit_test(test_gradient_border_technique),
        cmocka_unit_test(test_composite_vocabularies),
        cmocka_unit_test(test_clip_property),
        cmocka_unit_test(test_unsupported_fails_closed),
        cmocka_unit_test(test_none_resets),
        cmocka_unit_test(test_encode_decode_roundtrip),
        cmocka_unit_test(test_split_never_overruns),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
