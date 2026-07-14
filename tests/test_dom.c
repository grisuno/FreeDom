/*
 * TDD suite for dom (Hito 2 -> 3 bridge).
 *
 * RED state until src/dom.c exists: this links and fails on purpose.
 *
 * Build: make test   (requires libcmocka-dev + liblexbor-dev)
 * ASan:  make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "dom.h"
#include "html_parse.h"

static const char HTML[] =
    "<!DOCTYPE html><html><head><title>T</title></head>"
    "<body>"
    "<div id=\"main\" class=\"container box\">"
    "<p class=\"text\">Hello</p>"
    "<p class=\"text muted\">World</p>"
    "<button id=\"go\" class=\"btn\">Go</button>"
    "</div>"
    "</body></html>";

/* Parses HTML and builds the index. Caller frees with teardown_doc. */
static int setup_doc(void **state) {
    hp_document *doc = NULL;
    if (hp_parse(HTML, sizeof HTML - 1, NULL, &doc) != HP_OK) return -1;
    dom_index *idx = NULL;
    if (dom_build(doc, &idx) != DOM_OK) { hp_document_free(doc); return -1; }
    void **pair = (void **)malloc(2 * sizeof(void *));
    if (pair == NULL) { dom_free(idx); hp_document_free(doc); return -1; }
    pair[0] = doc;
    pair[1] = idx;
    *state = pair;
    return 0;
}

static int teardown_doc(void **state) {
    void **pair = (void **)*state;
    if (pair != NULL) {
        dom_free((dom_index *)pair[1]);
        hp_document_free((hp_document *)pair[0]);
        free(pair);
    }
    return 0;
}

#define DOC(state)  ((hp_document *)(((void **)*(state))[0]))
#define IDX(state)  ((dom_index *)(((void **)*(state))[1]))

/* --- lifecycle --- */

static void test_build_null_args(void **state) {
    (void)state;
    dom_index *idx = NULL;
    assert_int_equal(dom_build(NULL, &idx), DOM_ERR_NULL_ARG);
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK);
    assert_int_equal(dom_build(doc, NULL), DOM_ERR_NULL_ARG);
    hp_document_free(doc);
}

static void test_free_null_and_double(void **state) {
    (void)state;
    dom_free(NULL); /* no-op */
    hp_document *doc = NULL;
    assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK);
    dom_index *idx = NULL;
    assert_int_equal(dom_build(doc, &idx), DOM_OK);
    dom_free(idx);
    hp_document_free(doc);
}

static void test_node_count(void **state) {
    assert_true(dom_node_count(IDX(state)) > 0);
    assert_int_equal(dom_node_count(NULL), 0);
}

/* --- by id --- */

static void test_get_by_id(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    assert_int_not_equal(main_id, DOM_NODE_NONE);
    size_t len = 0;
    const char *tag = dom_tag_name(idx, main_id, &len);
    assert_non_null(tag);
    assert_string_equal(tag, "div");

    dom_node_id go = dom_get_element_by_id(idx, "go");
    assert_int_not_equal(go, DOM_NODE_NONE);
    assert_string_equal(dom_tag_name(idx, go, NULL), "button");
}

static void test_get_by_id_absent(void **state) {
    assert_int_equal(dom_get_element_by_id(IDX(state), "nope"), DOM_NODE_NONE);
    assert_int_equal(dom_get_element_by_id(NULL, "main"), DOM_NODE_NONE);
}

/* --- by class / tag --- */

static void test_by_class(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id buf[8];
    assert_int_equal(dom_get_by_class(idx, "text", buf, 8), 2);
    assert_int_equal(dom_get_by_class(idx, "btn", buf, 8), 1);
    assert_int_equal(dom_get_by_class(idx, "muted", buf, 8), 1);
    assert_int_equal(dom_get_by_class(idx, "missing", buf, 8), 0);
}

static void test_by_tag(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id buf[8];
    assert_int_equal(dom_get_by_tag(idx, "p", buf, 8), 2);
    assert_int_equal(dom_get_by_tag(idx, "P", buf, 8), 2); /* case-insensitive */
    assert_int_equal(dom_get_by_tag(idx, "button", buf, 8), 1);
    assert_int_equal(dom_get_by_tag(idx, "marquee", buf, 8), 0);
}

static void test_by_tag_results_in_document_order(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id buf[8];
    size_t n = dom_get_by_tag(idx, "p", buf, 8);
    assert_int_equal(n, 2);
    assert_true(dom_precedes(idx, buf[0], buf[1]));
}

/* --- document order --- */

static void test_document_order(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    dom_node_id go = dom_get_element_by_id(idx, "go");
    assert_true(dom_precedes(idx, main_id, go));
    assert_false(dom_precedes(idx, go, main_id));

    size_t pos = dom_document_position(idx, go);
    assert_int_equal(dom_node_at(idx, pos), go);
    assert_int_equal(dom_node_at(idx, dom_node_count(idx)), DOM_NODE_NONE);
}

/* --- navigation --- */

static void test_navigation(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");

    dom_node_id p1 = dom_first_child(idx, main_id);
    assert_int_not_equal(p1, DOM_NODE_NONE);
    assert_string_equal(dom_tag_name(idx, p1, NULL), "p");

    dom_node_id p2 = dom_next_sibling(idx, p1);
    assert_string_equal(dom_tag_name(idx, p2, NULL), "p");

    dom_node_id btn = dom_next_sibling(idx, p2);
    assert_string_equal(dom_tag_name(idx, btn, NULL), "button");

    assert_int_equal(dom_next_sibling(idx, btn), DOM_NODE_NONE);
    assert_int_equal(dom_parent(idx, btn), main_id);
}

/* --- attributes --- */

static void test_attributes(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    size_t len = 0;
    const char *cls = dom_get_attribute(idx, main_id, "class", &len);
    assert_non_null(cls);
    assert_string_equal(cls, "container box");
    assert_int_equal((int)len, (int)strlen("container box"));

    assert_null(dom_get_attribute(idx, main_id, "data-missing", NULL));
}

/* --- mutation (live JS) --- */

static void test_text_content_read(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id ids[4];
    size_t n = dom_get_by_tag(idx, "p", ids, 4);
    assert_true(n >= 1);
    size_t len = 0;
    const char *t = dom_text_content(idx, ids[0], &len);
    assert_non_null(t);
    assert_string_equal(t, "Hello");
}

static void test_set_text_content_changes_tree(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    assert_int_not_equal(main_id, DOM_NODE_NONE);
    /* Replace the whole subtree's content with plain text. */
    assert_int_equal(dom_set_text_content(idx, main_id, "REPLACED", 8), DOM_OK);
    size_t len = 0;
    const char *t = dom_text_content(idx, main_id, &len);
    assert_non_null(t);
    assert_string_equal(t, "REPLACED");
    /* Memory-safety: handles into the detached subtree are still valid pointers
     * (reads must not crash); the old <p> tag name is still readable. */
    dom_node_id go = dom_get_element_by_id(idx, "go");
    size_t tl = 0;
    const char *tag = dom_tag_name(idx, go, &tl); /* detached but alive */
    assert_non_null(tag);
}

static void test_set_text_content_empty_clears(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    assert_int_equal(dom_set_text_content(idx, main_id, "", 0), DOM_OK);
    size_t len = 1;
    const char *t = dom_text_content(idx, main_id, &len);
    /* empty content: either NULL or "" with len 0 */
    if (t != NULL) assert_int_equal((int)len, 0);
}

static void test_set_text_content_invalid_node(void **state) {
    dom_index *idx = IDX(state);
    assert_int_equal(dom_set_text_content(idx, DOM_NODE_NONE, "x", 1), DOM_ERR_NULL_ARG);
}

static void test_set_and_get_document_title(void **state) {
    dom_index *idx = IDX(state);
    size_t len = 0;
    const char *t0 = dom_document_title(idx, &len);
    assert_non_null(t0);
    assert_string_equal(t0, "T");
    assert_int_equal(dom_set_document_title(idx, "New Title", 9), DOM_OK);
    const char *t1 = dom_document_title(idx, &len);
    assert_non_null(t1);
    assert_string_equal(t1, "New Title");
}

static void test_create_and_append(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    dom_node_id created = DOM_NODE_NONE;
    assert_int_equal(dom_create_element(idx, "SPAN", &created), DOM_OK);
    assert_int_not_equal(created, DOM_NODE_NONE);
    /* new node is queryable (handle valid) and tagged span (lowercased) */
    size_t tl = 0;
    assert_string_equal(dom_tag_name(idx, created, &tl), "span");
    assert_int_equal(dom_set_text_content(idx, created, "fresh", 5), DOM_OK);
    assert_int_equal(dom_append_child(idx, main_id, created), DOM_OK);
    /* it is now a child of #main: parent navigation finds it */
    assert_int_equal(dom_parent(idx, created), main_id);
    /* and getByTag now includes it */
    dom_node_id spans[4];
    assert_true(dom_get_by_tag(idx, "span", spans, 4) >= 1);
}

static void test_append_rejects_cycle(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    /* main is an ancestor of go; appending main under go would cycle */
    dom_node_id go = dom_get_element_by_id(idx, "go");
    assert_int_equal(dom_append_child(idx, go, main_id), DOM_ERR_NULL_ARG);
    /* self-append rejected */
    assert_int_equal(dom_append_child(idx, main_id, main_id), DOM_ERR_NULL_ARG);
}

static void test_remove_child(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    dom_node_id go = dom_get_element_by_id(idx, "go");
    assert_int_equal(dom_remove_child(idx, main_id, go), DOM_OK);
    /* go is detached but still a valid handle (memory-safe) */
    size_t tl = 0;
    assert_string_equal(dom_tag_name(idx, go, &tl), "button");
    /* removing a non-child fails closed */
    assert_int_equal(dom_remove_child(idx, go, main_id), DOM_ERR_NULL_ARG);
}

static void test_set_attribute_reindexes_id(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id created = DOM_NODE_NONE;
    assert_int_equal(dom_create_element(idx, "div", &created), DOM_OK);
    assert_int_equal(dom_set_attribute(idx, created, "id", "dynamic"), DOM_OK);
    /* getElementById now finds the dynamically-id'd node */
    assert_int_equal(dom_get_element_by_id(idx, "dynamic"), created);
    /* a plain attribute round-trips */
    assert_int_equal(dom_set_attribute(idx, created, "data-x", "1"), DOM_OK);
    size_t len = 0;
    assert_string_equal(dom_get_attribute(idx, created, "data-x", &len), "1");
}

static void test_remove_attribute(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id created = DOM_NODE_NONE;
    assert_int_equal(dom_create_element(idx, "div", &created), DOM_OK);
    assert_int_equal(dom_set_attribute(idx, created, "data-x", "1"), DOM_OK);
    size_t len = 0;
    assert_string_equal(dom_get_attribute(idx, created, "data-x", &len), "1");
    /* remove it: getAttribute now reports absent (NULL) */
    assert_int_equal(dom_remove_attribute(idx, created, "data-x"), DOM_OK);
    assert_null(dom_get_attribute(idx, created, "data-x", &len));
    /* removing an absent attribute is a no-op success */
    assert_int_equal(dom_remove_attribute(idx, created, "nope"), DOM_OK);
    /* invalid args fail closed */
    assert_int_equal(dom_remove_attribute(idx, DOM_NODE_NONE, "x"), DOM_ERR_NULL_ARG);
    assert_int_equal(dom_remove_attribute(idx, created, NULL), DOM_ERR_NULL_ARG);
}

static void test_set_inner_html(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    assert_int_equal(dom_set_inner_html(idx, main_id,
        "<p id=\"np\">parsed</p><span class=\"sc\">two</span>", 44), DOM_OK);
    /* the parsed subtree is queryable and rendered text reflects it */
    dom_node_id np = dom_get_element_by_id(idx, "np");
    assert_int_not_equal(np, DOM_NODE_NONE);
    size_t len = 0;
    assert_string_equal(dom_text_content(idx, np, &len), "parsed");
    assert_true(dom_get_by_class(idx, "sc", NULL, 0) >= 1);
    /* the old children (#go etc.) were detached but their handles stay valid */
    dom_node_id go = dom_get_element_by_id(idx, "go");
    assert_string_equal(dom_tag_name(idx, go, &len), "button");
}

static void test_construction_invalid_args(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id out = DOM_NODE_NONE;
    assert_int_equal(dom_create_element(idx, "", &out), DOM_ERR_NULL_ARG);
    assert_int_equal(dom_append_child(idx, DOM_NODE_NONE, 0), DOM_ERR_NULL_ARG);
    assert_int_equal(dom_set_attribute(idx, DOM_NODE_NONE, "id", "x"), DOM_ERR_NULL_ARG);
}

static void test_get_inner_html(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    char *html = NULL;
    size_t len = 0;
    assert_int_equal(dom_get_inner_html(idx, main_id, &html, &len), DOM_OK);
    assert_non_null(html);
    assert_int_equal(strlen(html), len);
    /* children of #main serialize back with their markup */
    assert_non_null(strstr(html, "<p class=\"text\">Hello</p>"));
    assert_non_null(strstr(html, "<button id=\"go\""));
    free(html);
    /* roundtrip: set then get reflects the new subtree */
    assert_int_equal(dom_set_inner_html(idx, main_id, "<em>x</em>", 10), DOM_OK);
    assert_int_equal(dom_get_inner_html(idx, main_id, &html, &len), DOM_OK);
    assert_non_null(strstr(html, "<em>x</em>"));
    free(html);
    /* fail closed on invalid args */
    assert_int_equal(dom_get_inner_html(idx, DOM_NODE_NONE, &html, &len),
                     DOM_ERR_NULL_ARG);
    assert_int_equal(dom_get_inner_html(idx, main_id, NULL, &len), DOM_ERR_NULL_ARG);
}

/* --- CSS-selector queries (querySelector / matches / closest) --- */

/* Fixture tree (inside body): div#main.container.box > [ p.text "Hello",
 * p.text.muted "World", button#go.btn "Go" ]. */

static void test_query_selector_type_class_id(void **state) {
    dom_index *idx = IDX(state);
    /* First p.text in document order == the "Hello" p == first result of getByTag. */
    dom_node_id buf[8];
    dom_get_by_tag(idx, "p", buf, 8);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "p.text"), buf[0]);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "#go"),
                     dom_get_element_by_id(idx, "go"));
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "button#go.btn"),
                     dom_get_element_by_id(idx, "go"));
    /* No match -> DOM_NODE_NONE. */
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "marquee"), DOM_NODE_NONE);
}

static void test_query_selector_all_counts(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id buf[8];
    assert_int_equal(dom_query_selector_all(idx, DOM_NODE_NONE, "p.text", buf, 8), 2);
    /* Selector list: p, button -> 3 elements. */
    assert_int_equal(dom_query_selector_all(idx, DOM_NODE_NONE, "p, button", buf, 8), 3);
    assert_int_equal(dom_query_selector_all(idx, DOM_NODE_NONE, ".muted", buf, 8), 1);
    /* total may exceed cap; results are still document-ordered. */
    assert_true(dom_precedes(idx, buf[0], buf[0]) == 0);
}

static void test_query_selector_combinators(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id go = dom_get_element_by_id(idx, "go");
    /* Child combinator: only a direct child button of #main. */
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "div#main > button.btn"), go);
    /* Descendant combinator. */
    dom_node_id buf[8];
    dom_get_by_tag(idx, "p", buf, 8);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, ".container p"), buf[0]);
    /* Adjacent sibling: p.muted immediately after the first p. */
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "p + p.muted"), buf[1]);
}

static void test_query_selector_nth_and_structural(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id buf[8];
    dom_get_by_tag(idx, "p", buf, 8);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "p:first-child"), buf[0]);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "p:nth-child(2)"), buf[1]);
    /* :last-child scoped inside #main is the button (its last child); at document
     * scope the first :last-child is <html> itself, so scope the query. */
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    assert_int_equal(dom_query_selector(idx, main_id, ":last-child"),
                     dom_get_element_by_id(idx, "go"));
}

static void test_query_selector_scope_is_descendants_only(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    /* Element scope excludes the element itself: querying #main for "div" finds none. */
    assert_int_equal(dom_query_selector(idx, main_id, "div"), DOM_NODE_NONE);
    /* But document scope finds the div. */
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "div#main"), main_id);
    /* Descendants of #main: the two p's + the button. */
    dom_node_id buf[8];
    assert_int_equal(dom_query_selector_all(idx, main_id, "p", buf, 8), 2);
}

static void test_matches_and_closest(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id go = dom_get_element_by_id(idx, "go");
    dom_node_id main_id = dom_get_element_by_id(idx, "main");
    assert_true(dom_matches(idx, go, "button#go.btn"));
    assert_true(dom_matches(idx, go, "div > button"));
    assert_false(dom_matches(idx, go, "p"));
    /* closest walks up including self. */
    assert_int_equal(dom_closest(idx, go, "button"), go);
    assert_int_equal(dom_closest(idx, go, "div.container"), main_id);
    assert_int_equal(dom_closest(idx, go, "table"), DOM_NODE_NONE);
}

static void test_query_selector_fail_closed(void **state) {
    dom_index *idx = IDX(state);
    dom_node_id buf[8];
    /* Unsupported constructs drop the whole selector -> no match (never a throw). */
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, "p::before"), DOM_NODE_NONE);
    assert_true(dom_query_selector(idx, DOM_NODE_NONE, ":not(div)") != DOM_NODE_NONE);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, ""), DOM_NODE_NONE);
    assert_int_equal(dom_query_selector_all(idx, DOM_NODE_NONE, "@#$%", buf, 8), 0);
    /* But a valid selector in a list survives an invalid sibling. */
    assert_int_equal(dom_query_selector_all(idx, DOM_NODE_NONE, "p::before, p.text", buf, 8), 2);
    /* NULL args fail closed. */
    assert_int_equal(dom_query_selector(NULL, DOM_NODE_NONE, "p"), DOM_NODE_NONE);
    assert_int_equal(dom_query_selector(idx, DOM_NODE_NONE, NULL), DOM_NODE_NONE);
    assert_int_equal(dom_matches(idx, DOM_NODE_NONE, "p"), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_build_null_args),
        cmocka_unit_test(test_free_null_and_double),
        cmocka_unit_test_setup_teardown(test_node_count, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_get_by_id, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_get_by_id_absent, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_by_class, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_by_tag, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_by_tag_results_in_document_order, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_document_order, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_navigation, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_attributes, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_text_content_read, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_set_text_content_changes_tree, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_set_text_content_empty_clears, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_set_text_content_invalid_node, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_set_and_get_document_title, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_create_and_append, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_append_rejects_cycle, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_remove_child, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_set_attribute_reindexes_id, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_remove_attribute, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_set_inner_html, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_get_inner_html, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_construction_invalid_args, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_query_selector_type_class_id, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_query_selector_all_counts, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_query_selector_combinators, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_query_selector_nth_and_structural, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_query_selector_scope_is_descendants_only, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_matches_and_closest, setup_doc, teardown_doc),
        cmocka_unit_test_setup_teardown(test_query_selector_fail_closed, setup_doc, teardown_doc),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
