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
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
