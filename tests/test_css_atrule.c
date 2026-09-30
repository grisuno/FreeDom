/* test_css_atrule -- @supports evaluation and @layer ranks (spec/css_atrule.md). */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "css_atrule.h"

/* A toy engine: supports display:grid|flex, gap:<anything>, custom properties;
 * selectors that are a single class. */
static int toy_decl(void *ctx, const char *prop, const char *value) {
    (void)ctx;
    if (strcmp(prop, "display") == 0)
        return strcmp(value, "grid") == 0 || strcmp(value, "flex") == 0;
    return strcmp(prop, "gap") == 0;
}

static int toy_sel(void *ctx, const char *sel) {
    (void)ctx;
    return sel[0] == '.' && strchr(sel, ' ') == NULL;
}

static const car_ops OPS = { toy_decl, toy_sel, NULL };

static int sup(const char *c) { return car_supports(c, 0, strlen(c), &OPS); }

static void test_declaration_tests(void **state) {
    (void)state;
    assert_int_equal(sup("(display: grid)"), 1);
    assert_int_equal(sup("  ( DISPLAY :grid ) "), 1);
    assert_int_equal(sup("(display: subgrid)"), 0);
    assert_int_equal(sup("(-webkit-touch-callout: none)"), 0);
    assert_int_equal(sup("(--x: anything at all)"), 1);
}

static void test_boolean_combinators(void **state) {
    (void)state;
    assert_int_equal(sup("not (display: subgrid)"), 1);
    assert_int_equal(sup("NOT (display:grid)"), 0);
    assert_int_equal(sup("(display:grid) and (gap:1px)"), 1);
    assert_int_equal(sup("(display:grid) and (display:table)"), 0);
    assert_int_equal(sup("(display:table) or (display:flex)"), 1);
    assert_int_equal(sup("((display:table) or (display:flex)) and (not (display:x))"), 1);
}

static void test_selector_function(void **state) {
    (void)state;
    assert_int_equal(sup("selector(.a)"), 1);
    assert_int_equal(sup("selector(.a .b)"), 0);
    assert_int_equal(sup("not selector(:has(a))"), 1);
}

static void test_malformed_is_false(void **state) {
    (void)state;
    assert_int_equal(sup(""), 0);
    assert_int_equal(sup("(display:grid"), 0);
    assert_int_equal(sup("(display:grid) and (gap:1px) or (display:flex)"), 0);
    assert_int_equal(sup("font-tech(color-COLRv1)"), 0);
    assert_int_equal(sup("(display:grid) andx (gap:1px)"), 0);
    assert_int_equal(sup("(display)"), 0);
    char deep[256] = "";
    for (int i = 0; i < CAR_MAX_DEPTH + 2; ++i) strcat(deep, "(");
    strcat(deep, "display:grid");
    for (int i = 0; i < CAR_MAX_DEPTH + 2; ++i) strcat(deep, ")");
    assert_int_equal(sup(deep), 0);
}

static void test_layer_ranks_first_appearance(void **state) {
    (void)state;
    car_layers *L = (car_layers *)calloc(1, sizeof *L);
    assert_non_null(L);
    assert_int_equal(car_layer_rank(L, "theme", 5), 1);
    assert_int_equal(car_layer_rank(L, "base", 4), 2);
    assert_int_equal(car_layer_rank(L, "theme", 5), 1);
    assert_int_equal(car_layer_rank(L, "", 0), 3);
    assert_int_equal(car_layer_rank(L, "", 0), 4);
    for (int i = 0; i < CAR_MAX_LAYERS + 10; ++i) (void)car_layer_rank(L, "", 0);
    assert_int_equal(car_layer_rank(L, "late", 4), CAR_MAX_LAYERS);
    free(L);
}

static void test_effective_spec_orders(void **state) {
    (void)state;
    /* Normal: unlayered beats any layer regardless of specificity; a later
     * layer beats an earlier one. */
    assert_true(car_effective_spec(1, 0, 0) > car_effective_spec(1000, 5, 0));
    assert_true(car_effective_spec(1, 2, 0) > car_effective_spec(1000, 1, 0));
    assert_true(car_effective_spec(20, 1, 0) > car_effective_spec(10, 1, 0));
    /* Important: reversed. */
    assert_true(car_effective_spec(1, 1, 1) > car_effective_spec(1000, 2, 1));
    assert_true(car_effective_spec(1, 5, 1) > car_effective_spec(1000, 0, 1));
    /* Inline beats everything normal. */
    assert_true(CAR_INLINE_SPEC > car_effective_spec(0xFFFF, 0, 0));
    assert_true(car_effective_spec(1 << 20, 0, 0) <= car_effective_spec(0xFFFF, 0, 0));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_declaration_tests),
        cmocka_unit_test(test_boolean_combinators),
        cmocka_unit_test(test_selector_function),
        cmocka_unit_test(test_malformed_is_false),
        cmocka_unit_test(test_layer_ranks_first_appearance),
        cmocka_unit_test(test_effective_spec_orders),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
