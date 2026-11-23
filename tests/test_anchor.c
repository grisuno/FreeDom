/* test_anchor.c — CMocka suite for the anchor module (spec/anchor.md). */
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <math.h>
#include <cmocka.h>

#include "anchor.h"
#include "dom.h"
#include "html_parse.h"
#include "js_geom.h"

typedef struct fixture { hp_document *doc; dom_index *idx; } fixture;

static int load(fixture *f, const char *html) {
    f->doc = NULL; f->idx = NULL;
    if (hp_parse(html, strlen(html), NULL, &f->doc) != HP_OK) return -1;
    if (dom_build(f->doc, &f->idx) != DOM_OK) { hp_document_free(f->doc); return -1; }
    return 0;
}

static void unload(fixture *f) {
    dom_free(f->idx);
    hp_document_free(f->doc);
}

static const char *tag(const fixture *f, dom_node_id n) {
    return dom_tag_name(f->idx, n, NULL);
}

static const char *attr(const fixture *f, dom_node_id n, const char *name) {
    return dom_get_attribute(f->idx, n, name, NULL);
}

static void test_percent_decode(void **state) {
    (void)state;
    char out[32];
    assert_int_equal(anc_percent_decode("caf%C3%A9", out, sizeof out), 5);
    assert_string_equal(out, "caf\xC3\xA9");
    assert_int_equal(anc_percent_decode("a%2", out, sizeof out), 3);
    assert_string_equal(out, "a%2");
    assert_int_equal(anc_percent_decode("%zz%41", out, sizeof out), 4);
    assert_string_equal(out, "%zzA");
    assert_int_equal(anc_percent_decode("abcd", out, 4), (size_t)-1);
    assert_string_equal(out, "");
    assert_int_equal(anc_percent_decode("abc", out, 4), 3);
    assert_int_equal(anc_percent_decode(NULL, out, 4), (size_t)-1);
    assert_int_equal(anc_percent_decode("a", NULL, 4), (size_t)-1);
    assert_int_equal(anc_percent_decode("a", out, 0), (size_t)-1);
}

static void test_resolve_id_then_name(void **state) {
    (void)state;
    fixture f;
    assert_int_equal(load(&f, "<html><body><p id=x>a</p><a name=y></a><a name=x>b</a>"
                              "<h2 id=sec>S</h2></body></html>"), 0);
    dom_node_id t = DOM_NODE_NONE;
    assert_int_equal(anc_resolve(f.idx, "x", &t), ANC_ELEMENT);
    assert_string_equal(tag(&f, t), "p");           /* id wins over an earlier-or-later name */
    assert_int_equal(anc_resolve(f.idx, "y", &t), ANC_ELEMENT);
    assert_string_equal(tag(&f, t), "a");
    assert_string_equal(attr(&f, t, "name"), "y");
    assert_int_equal(anc_resolve(f.idx, "sec", &t), ANC_ELEMENT);
    assert_string_equal(tag(&f, t), "h2");
    assert_int_equal(anc_resolve(f.idx, "Sec", &t), ANC_NONE); /* ids are case-sensitive */
    unload(&f);
}

static void test_resolve_name_only_on_a(void **state) {
    (void)state;
    fixture f;
    assert_int_equal(load(&f, "<body><div name=z>d</div><img name=z></body>"), 0);
    dom_node_id t = DOM_NODE_NONE;
    assert_int_equal(anc_resolve(f.idx, "z", &t), ANC_NONE);
    unload(&f);
}

static void test_resolve_top_and_empty(void **state) {
    (void)state;
    fixture f;
    assert_int_equal(load(&f, "<body><p>a</p></body>"), 0);
    dom_node_id t = 7;
    assert_int_equal(anc_resolve(f.idx, "", &t), ANC_TOP);
    assert_int_equal(anc_resolve(f.idx, "top", &t), ANC_TOP);
    assert_int_equal(anc_resolve(f.idx, "TOP", &t), ANC_TOP);
    assert_int_equal(anc_resolve(f.idx, "%74op", &t), ANC_TOP);
    assert_int_equal(anc_resolve(f.idx, "missing", &t), ANC_NONE);
    unload(&f);
    assert_int_equal(load(&f, "<body><p>a</p><div id=top>t</div></body>"), 0);
    assert_int_equal(anc_resolve(f.idx, "top", &t), ANC_ELEMENT);
    assert_string_equal(tag(&f, t), "div");
    unload(&f);
}

static void test_resolve_decoded(void **state) {
    (void)state;
    fixture f;
    assert_int_equal(load(&f, "<meta charset=utf-8><body><p id=\"caf\xC3\xA9\">c</p>"
                              "<p id=\"a%20b\">raw</p><p id=\"a b\">dec</p></body>"), 0);
    dom_node_id t = DOM_NODE_NONE;
    assert_int_equal(anc_resolve(f.idx, "caf%C3%A9", &t), ANC_ELEMENT);
    assert_string_equal(attr(&f, t, "id"), "caf\xC3\xA9");
    /* the raw fragment is tried first: an id that literally contains %20 wins */
    assert_int_equal(anc_resolve(f.idx, "a%20b", &t), ANC_ELEMENT);
    assert_string_equal(attr(&f, t, "id"), "a%20b");
    assert_int_equal(anc_resolve(f.idx, "nul%00x", &t), ANC_NONE);
    unload(&f);
}

static void test_resolve_rejects_detached_and_bad_args(void **state) {
    (void)state;
    fixture f;
    assert_int_equal(load(&f, "<body><div id=keep><span id=gone>g</span></div>"
                              "<a name=n2>x</a></body>"), 0);
    dom_node_id gone = dom_get_element_by_id(f.idx, "gone");
    dom_node_id keep = dom_get_element_by_id(f.idx, "keep");
    assert_int_equal(dom_remove_child(f.idx, keep, gone), DOM_OK);
    dom_node_id t = DOM_NODE_NONE;
    assert_int_equal(anc_resolve(f.idx, "gone", &t), ANC_NONE);
    assert_false(dom_is_connected(f.idx, gone));
    assert_true(dom_is_connected(f.idx, keep));
    char big[ANC_MAX_FRAGMENT + 8];
    memset(big, 'k', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(anc_resolve(f.idx, big, &t), ANC_NONE);
    assert_int_equal(anc_resolve(NULL, "keep", &t), ANC_NONE);
    assert_int_equal(anc_resolve(f.idx, NULL, &t), ANC_NONE);
    assert_int_equal(anc_resolve(f.idx, "keep", NULL), ANC_NONE);
    unload(&f);
}

static void test_collect_subtree_then_following(void **state) {
    (void)state;
    fixture f;
    assert_int_equal(load(&f, "<body><section id=s><h2>T</h2><p><b>x</b></p></section>"
                              "<div id=after><i>y</i></div><footer>z</footer></body>"), 0);
    dom_node_id s = dom_get_element_by_id(f.idx, "s");
    dom_node_id h[16];
    size_t nsub = 99;
    size_t n = anc_collect(f.idx, s, h, 16, &nsub);
    assert_int_equal(nsub, 4);                       /* section h2 p b */
    assert_int_equal(n, 7);                          /* + div i footer */
    assert_int_equal(h[0], s);
    assert_string_equal(tag(&f, h[1]), "h2");
    assert_string_equal(tag(&f, h[3]), "b");
    assert_string_equal(tag(&f, h[4]), "div");
    assert_string_equal(tag(&f, h[5]), "i");
    assert_string_equal(tag(&f, h[6]), "footer");
    /* capped mid-subtree: nsub never exceeds the count written */
    n = anc_collect(f.idx, s, h, 2, &nsub);
    assert_int_equal(n, 2);
    assert_int_equal(nsub, 2);
    assert_int_equal(anc_collect(f.idx, DOM_NODE_NONE, h, 16, &nsub), 0);
    assert_int_equal(nsub, 0);
    assert_int_equal(anc_collect(NULL, s, h, 16, &nsub), 0);
    assert_int_equal(anc_collect(f.idx, s, h, 0, &nsub), 0);
    unload(&f);
}

/* tanda 104 (spec/scroll_req.md): the whole box of the target, for scrollIntoView. */
static void test_target_box(void **state) {
    (void)state;
    jg_table g;
    jg_init(&g);
    assert_int_equal(jg_add(&g, 10, 0, 900, 50, 20), 0);
    assert_int_equal(jg_add(&g, 11, 0, 840, 50, 300), 0);   /* bottom 1140 */
    assert_int_equal(jg_add(&g, 20, 0, 1200, 50, 20), 0);
    assert_int_equal(jg_finish(&g), 0);
    double top = -1.0, bottom = -1.0;
    dom_node_id a[] = { 9, 10, 11, 20 };
    assert_int_equal(anc_target_box(&g, a, 4, 3, &top, &bottom), 0);
    assert_true(top == 840.0 && bottom == 1140.0);
    dom_node_id b[] = { 5, 20 };                              /* empty target: a point */
    assert_int_equal(anc_target_box(&g, b, 2, 1, &top, &bottom), 0);
    assert_true(top == 1200.0 && bottom == 1200.0);
    dom_node_id c[] = { 1 };
    top = bottom = 7.0;
    assert_int_equal(anc_target_box(&g, c, 1, 1, &top, &bottom), -1);
    assert_true(top == 7.0 && bottom == 7.0);
    assert_int_equal(anc_target_box(&g, a, 4, 3, &top, NULL), -1);
    jg_free(&g);
}

static void test_target_top(void **state) {
    (void)state;
    jg_table g;
    jg_init(&g);
    assert_int_equal(jg_add(&g, 10, 0, 900, 50, 20), 0);   /* subtree, lower */
    assert_int_equal(jg_add(&g, 11, 0, 840, 50, 20), 0);   /* subtree, higher (a float) */
    assert_int_equal(jg_add(&g, 20, 0, 1200, 50, 20), 0);  /* following */
    assert_int_equal(jg_finish(&g), 0);
    double top = -1.0;
    dom_node_id a[] = { 9, 10, 11, 20 };
    assert_int_equal(anc_target_top(&g, a, 4, 3, &top), 0);
    assert_true(top == 840.0);
    /* empty target: nothing in the subtree painted, the following content locates it */
    dom_node_id b[] = { 5, 6, 20, 10 };
    assert_int_equal(anc_target_top(&g, b, 4, 2, &top), 0);
    assert_true(top == 1200.0);
    dom_node_id c[] = { 1, 2 };
    top = 7.0;
    assert_int_equal(anc_target_top(&g, c, 2, 1, &top), -1);
    assert_true(top == 7.0);
    assert_int_equal(anc_target_top(NULL, a, 4, 3, &top), -1);
    assert_int_equal(anc_target_top(&g, NULL, 4, 3, &top), -1);
    assert_int_equal(anc_target_top(&g, a, 4, 9, &top), 0);  /* nsub > n is clamped */
    jg_free(&g);
}

static void test_scroll_for(void **state) {
    (void)state;
    assert_true(anc_scroll_for(500.0, 2000.0) == 500.0);
    assert_true(anc_scroll_for(2500.0, 2000.0) == 2000.0);
    assert_true(anc_scroll_for(-40.0, 2000.0) == 0.0);
    assert_true(anc_scroll_for(NAN, 2000.0) == 0.0);
    assert_true(anc_scroll_for(10.0, INFINITY) == 0.0);
    assert_true(anc_scroll_for(10.0, -1.0) == 0.0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_percent_decode),
        cmocka_unit_test(test_resolve_id_then_name),
        cmocka_unit_test(test_resolve_name_only_on_a),
        cmocka_unit_test(test_resolve_top_and_empty),
        cmocka_unit_test(test_resolve_decoded),
        cmocka_unit_test(test_resolve_rejects_detached_and_bad_args),
        cmocka_unit_test(test_collect_subtree_then_following),
        cmocka_unit_test(test_target_top),
        cmocka_unit_test(test_target_box),
        cmocka_unit_test(test_scroll_for),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
