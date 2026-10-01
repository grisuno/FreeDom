/*
 * TDD suite for import_map (spec/import_map.md).
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdio.h>
#include <string.h>
#include <cmocka.h>

#include "import_map.h"

/* Test URL resolver: absolute https passes, "/x" is origin-relative, "./x" and "../x"
 * are directory-relative to base; anything else (bare) fails. */
static int tres(void *ctx, const char *base, const char *ref, char *out, size_t outsz) {
    (void)ctx;
    int n;
    if (strncmp(ref, "https://", 8) == 0) {
        n = snprintf(out, outsz, "%s", ref);
    } else if (ref[0] == '/') {
        const char *p = strchr(base + 8, '/');
        size_t o = p ? (size_t)(p - base) : strlen(base);
        n = snprintf(out, outsz, "%.*s%s", (int)o, base, ref);
    } else if (strncmp(ref, "./", 2) == 0 || strncmp(ref, "../", 3) == 0) {
        const char *slash = strrchr(base, '/');
        size_t dir = slash ? (size_t)(slash - base) + 1 : strlen(base);
        n = snprintf(out, outsz, "%.*s%s", (int)dir, base, ref[1] == '/' ? ref + 2 : ref);
    } else {
        return -1;
    }
    return (n > 0 && (size_t)n < outsz) ? 0 : -1;
}

#define DOC "https://site.test/app/index.html"

static void expect_res(const im_map *m, const char *base, const char *spec, const char *want) {
    char out[512];
    if (want == NULL) {
        assert_int_equal(im_resolve(m, base, spec, tres, NULL, out, sizeof out), -1);
    } else {
        assert_int_equal(im_resolve(m, base, spec, tres, NULL, out, sizeof out), 0);
        assert_string_equal(out, want);
    }
}

static void test_exact_and_prefix_imports(void **state) {
    (void)state;
    const char *j =
        "{ \"imports\": {"
        "  \"react\": \"https://cdn.test/react-1.js\","
        "  \"react-dom/client\": \"/assets/rdc.js\","
        "  \"lodash/\": \"./vendor/lodash/\","
        "  \"lodash/fp/\": \"https://fp.test/\","
        "  \"./local.js\": \"./mapped-local.js\","
        "  \"bad/\": \"https://nodir.test/x.js\""
        "} }";
    im_map *m = im_parse(j, strlen(j), DOC, tres, NULL);
    assert_non_null(m);
    assert_int_equal(im_count(m), 6);
    expect_res(m, DOC, "react", "https://cdn.test/react-1.js");
    expect_res(m, DOC, "react-dom/client", "https://site.test/assets/rdc.js");
    expect_res(m, DOC, "lodash/map.js", "https://site.test/app/vendor/lodash/map.js");
    expect_res(m, DOC, "lodash/fp/curry.js", "https://fp.test/curry.js");   /* longest prefix */
    expect_res(m, "https://site.test/app/main.js", "./local.js",
               "https://site.test/app/mapped-local.js");                     /* URL-like key */
    expect_res(m, DOC, "bad/x", NULL);                  /* prefix target must end in '/' */
    expect_res(m, DOC, "vue", NULL);                    /* unmapped bare: fails */
    expect_res(m, DOC, "./other.js", "https://site.test/app/other.js");   /* URL passes */
    im_free(m);
}

static void test_scopes_win_by_longest_prefix(void **state) {
    (void)state;
    const char *j =
        "{ \"imports\": { \"dep\": \"https://cdn.test/dep-v1.js\" },"
        "  \"scopes\": {"
        "    \"/legacy/\": { \"dep\": \"https://cdn.test/dep-v0.js\" },"
        "    \"/legacy/deep/\": { \"dep\": \"https://cdn.test/dep-v00.js\" }"
        "  } }";
    im_map *m = im_parse(j, strlen(j), DOC, tres, NULL);
    assert_non_null(m);
    expect_res(m, "https://site.test/app/m.js", "dep", "https://cdn.test/dep-v1.js");
    expect_res(m, "https://site.test/legacy/m.js", "dep", "https://cdn.test/dep-v0.js");
    expect_res(m, "https://site.test/legacy/deep/m.js", "dep", "https://cdn.test/dep-v00.js");
    im_free(m);
}

static void test_json_escapes_and_ignored_members(void **state) {
    (void)state;
    const char *j =
        "{\"integrity\":{\"x\":\"sha384-abc\"},\"imports\":{\"a\\u0062c\":\"https:\\/\\/e.test\\/\\u00e9.js\"},"
        "\"future\":[1,2,{\"n\":null}]}";
    im_map *m = im_parse(j, strlen(j), DOC, tres, NULL);
    assert_non_null(m);
    assert_int_equal(im_count(m), 1);
    expect_res(m, DOC, "abc", "https://e.test/\xc3\xa9.js");
    im_free(m);
}

static void test_invalid_input_yields_empty_map(void **state) {
    (void)state;
    const char *bad[] = {
        "", "[]", "{", "{\"imports\":[\"x\"]}", "{\"imports\":{\"a\":1}}",
        "{\"imports\":{\"a\":\"https://x.test/\"}", "{\"imports\":{\"a\":\"\\uZZZZ\"}}",
        "{\"imports\":{\"a\":\"x\"}} trailing", "{\"scopes\":{\"/p/\":\"notobj\"}}",
        "{\"imports\":{\"a\":\"\\ud800\"}}",
    };
    for (size_t i = 0; i < sizeof bad / sizeof bad[0]; ++i) {
        im_map *m = im_parse(bad[i], strlen(bad[i]), DOC, tres, NULL);
        assert_non_null(m);
        assert_int_equal(im_count(m), 0);
        expect_res(m, DOC, "a", NULL);
        im_free(m);
    }
    im_free(NULL);
    assert_int_equal(im_count(NULL), 0);
    char out[64];
    assert_int_equal(im_resolve(NULL, DOC, "./x.js", tres, NULL, out, sizeof out), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_exact_and_prefix_imports),
        cmocka_unit_test(test_scopes_win_by_longest_prefix),
        cmocka_unit_test(test_json_escapes_and_ignored_members),
        cmocka_unit_test(test_invalid_input_yields_empty_map),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
