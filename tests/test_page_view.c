/*
 * TDD suite for page_view (Hito 5->6: HTML rendering display list).
 *
 * The pure model (pv_new/pv_append/pv_free) is tested directly; the DOM->list
 * builder (pv_build) is exercised by parsing real HTML with html_parse and
 * asserting on the produced runs.
 *
 * Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "html_parse.h"
#include "page_view.h"

/* Parse helper: aborts the test on parse failure. Caller frees *doc. */
static hp_document *parse(const char *html) {
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(html, strlen(html), NULL, &doc), HP_OK);
    assert_non_null(doc);
    return doc;
}

/* Finds the i-th run whose collapsed text equals `text`; NULL if none. */
static const pv_run *find_text(const pv_view *v, const char *text) {
    for (size_t i = 0; i < pv_count(v); ++i) {
        const pv_run *r = pv_at(v, i);
        if (r->text != NULL && strcmp(r->text, text) == 0) return r;
    }
    return NULL;
}

/* --- pure model: pv_new / pv_append / pv_free --- */

static void test_new_is_empty(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_non_null(v);
    assert_int_equal((int)pv_count(v), 0);
    assert_null(pv_at(v, 0));
    pv_free(v);
}

static void test_append_copies_fields(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 2, 1, "hello", NULL), PV_OK);
    assert_int_equal(pv_append(v, PV_LINK, 0, 0, "site", "https://x.example/"), PV_OK);
    assert_int_equal((int)pv_count(v), 2);

    const pv_run *a = pv_at(v, 0);
    assert_int_equal(a->kind, PV_TEXT);
    assert_int_equal(a->heading, 2);
    assert_int_equal(a->block_break, 1);
    assert_string_equal(a->text, "hello");
    assert_null(a->href);

    const pv_run *b = pv_at(v, 1);
    assert_int_equal(b->kind, PV_LINK);
    assert_string_equal(b->text, "site");
    assert_string_equal(b->href, "https://x.example/");
    pv_free(v);
}

static void test_append_sanitizes_utf8(void **state) {
    (void)state;
    pv_view *v = pv_new();
    const char latin1[] = { 'I', 'm', (char)0xE1, 'g', '\0' }; /* lone 0xE1 */
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, latin1, NULL), PV_OK);
    assert_string_equal(pv_at(v, 0)->text, "Im?g");
    pv_free(v);
}

static void test_append_null_args(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(NULL, PV_TEXT, 0, 0, "x", NULL), PV_ERR_NULL_ARG);
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, NULL, NULL), PV_ERR_NULL_ARG);
    pv_free(v);
}

static void test_free_null_and_double(void **state) {
    (void)state;
    pv_free(NULL);
    pv_view *v = pv_new();
    pv_free(v);
}

/* --- builder: pv_build --- */

static void test_build_null_args(void **state) {
    (void)state;
    pv_view *v = NULL;
    assert_int_equal(pv_build(NULL, &v), PV_ERR_NULL_ARG);
    hp_document *doc = parse("<p>x</p>");
    assert_int_equal(pv_build(doc, NULL), PV_ERR_NULL_ARG);
    hp_document_free(doc);
}

static void test_build_plain_text(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>Hello world</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *r = find_text(v, "Hello world");
    assert_non_null(r);
    assert_int_equal(r->kind, PV_TEXT);
    assert_int_equal(r->heading, 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_heading_level(void **state) {
    (void)state;
    hp_document *doc = parse("<body><h2>Title</h2><p>body</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *h = find_text(v, "Title");
    assert_non_null(h);
    assert_int_equal(h->heading, 2);
    const pv_run *p = find_text(v, "body");
    assert_non_null(p);
    assert_int_equal(p->heading, 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_link_with_href(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>see <a href=\"https://e.example/x\">here</a> now</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);

    const pv_run *link = find_text(v, "here");
    assert_non_null(link);
    assert_int_equal(link->kind, PV_LINK);
    assert_string_equal(link->href, "https://e.example/x");

    const pv_run *before = find_text(v, "see ");
    assert_non_null(before);
    assert_int_equal(before->kind, PV_TEXT);
    assert_null(before->href);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_block_break_between_paragraphs(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>one</p><p>two</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    const pv_run *two = find_text(v, "two");
    assert_non_null(two);
    assert_int_equal(two->block_break, 1);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_skips_script_and_style(void **state) {
    (void)state;
    /* script is stripped by html_parse; style text must not leak into runs. */
    hp_document *doc = parse("<body><style>p{color:red}</style><p>visible</p>"
                             "<script>var x=1;</script></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_non_null(find_text(v, "visible"));
    assert_null(find_text(v, "p{color:red}"));
    assert_null(find_text(v, "var x=1;"));
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_inline_link_no_break_within_paragraph(void **state) {
    (void)state;
    hp_document *doc = parse("<body><p>a<a href=\"/b\">b</a>c</p></body>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    /* "a", link "b", "c" are all in the same block: only the first carries the
     * block break (from entering <p>); the inline link and trailing text do not. */
    const pv_run *b = find_text(v, "b");
    assert_non_null(b);
    assert_int_equal(b->kind, PV_LINK);
    assert_int_equal(b->block_break, 0);
    const pv_run *c = find_text(v, "c");
    assert_non_null(c);
    assert_int_equal(c->block_break, 0);
    pv_free(v);
    hp_document_free(doc);
}

static void test_build_empty_document(void **state) {
    (void)state;
    hp_document *doc = parse("<html><head><title>t</title></head><body></body></html>");
    pv_view *v = NULL;
    assert_int_equal(pv_build(doc, &v), PV_OK);
    assert_non_null(v);
    /* No visible body text => no runs (title lives outside the body view). */
    assert_int_equal((int)pv_count(v), 0);
    pv_free(v);
    hp_document_free(doc);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_is_empty),
        cmocka_unit_test(test_append_copies_fields),
        cmocka_unit_test(test_append_sanitizes_utf8),
        cmocka_unit_test(test_append_null_args),
        cmocka_unit_test(test_free_null_and_double),
        cmocka_unit_test(test_build_null_args),
        cmocka_unit_test(test_build_plain_text),
        cmocka_unit_test(test_build_heading_level),
        cmocka_unit_test(test_build_link_with_href),
        cmocka_unit_test(test_build_block_break_between_paragraphs),
        cmocka_unit_test(test_build_skips_script_and_style),
        cmocka_unit_test(test_build_inline_link_no_break_within_paragraph),
        cmocka_unit_test(test_build_empty_document),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
