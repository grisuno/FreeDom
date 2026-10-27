#define _POSIX_C_SOURCE 200809L
/*
 * test_frame_host -- CMocka suite for the trusted-parent iframe host, over REAL confined workers:
 * an <iframe> opens a frame worker, messages are routed with origin checks in both directions,
 * a mismatched targetOrigin is dropped, and removing the iframe closes its worker.
 */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "frame_host.h"
#include "tab.h"

static const char TOP_PAGE[] =
    "<html><body><iframe id=\"f\" src=\"https://rc.test/anchor\"></iframe><script>"
    "window.addEventListener('message',function(e){"
    "  document.getElementById('f').contentWindow.postMessage('ack:'+e.data.hello,'https://rc.test'); });"
    "</script></body></html>";

static const char FRAME_PAGE[] =
    "<html><body><script>"
    "window.addEventListener('message',function(e){"
    "  parent.postMessage({done:e.data,origin:e.origin},'https://top.test'); });"
    "parent.postMessage({hello:1},'https://top.test');"
    "parent.postMessage({leak:1},'https://evil.test');"
    "</script></body></html>";

static char  g_log[4][256];
static int   g_nlog;
static int   g_fetches;

static void on_top_msg(void *ctx, const char *data, size_t len) {
    (void)ctx;
    if (g_nlog < 4 && len < sizeof g_log[0]) { memcpy(g_log[g_nlog], data, len); g_log[g_nlog][len] = '\0'; g_nlog++; }
}

static int stub_fetch(void *ctx, const char *method, const char *url, const char *body, size_t bl,
                      int *st, char **ob, size_t *ol, char **oct) {
    (void)ctx; (void)method; (void)body; (void)bl;
    *st = 0; *ob = NULL; *ol = 0; *oct = NULL;
    if (strcmp(url, "https://rc.test/anchor") != 0) return -1;
    g_fetches++;
    *ob = strdup(FRAME_PAGE);
    *ol = sizeof FRAME_PAGE - 1;
    *oct = strdup("text/html");
    *st = 200;
    return 0;
}

static void test_open_route_both_ways_and_drop_mismatch(void **state) {
    (void)state;
    g_nlog = 0; g_fetches = 0;
    tab *top = NULL;
    assert_int_equal(tab_open(&top), TAB_OK);
    tab_set_net_allowed(top, 1);
    fh_host *h = fh_new("https://top.test/", stub_fetch, NULL, on_top_msg, NULL);
    assert_non_null(h);

    tab_page p;
    assert_int_equal(tab_load_full(top, TOP_PAGE, sizeof TOP_PAGE - 1, "https://top.test/",
                                   1, 0, 0, &p), TAB_OK);
    fh_apply_top(h, &p);
    tab_page_free(&p);
    assert_int_equal(g_fetches, 1);
    assert_int_equal(fh_count(h), 1);
    /* the frame's {hello} reached the top; its {leak} to evil.test was dropped */
    assert_int_equal(g_nlog, 1);
    assert_string_equal(g_log[0], "https://rc.test\nc1\n{\"hello\":1}");

    /* top answers: delivered to the frame, which answers back */
    tab_page c;
    assert_int_equal(tab_ws_event(top, 0, TAB_WSE_FRAME_MSG, 0, g_log[0], strlen(g_log[0]), &c), TAB_OK);
    fh_apply_top(h, &c);
    tab_page_free(&c);
    assert_int_equal(g_nlog, 2);
    assert_string_equal(g_log[1], "https://rc.test\nc1\n{\"done\":\"ack:1\",\"origin\":\"https://top.test\"}");

    fh_free(h);
    tab_close(top);
}

static void test_removing_iframe_closes_worker(void **state) {
    (void)state;
    g_nlog = 0;
    tab *top = NULL;
    assert_int_equal(tab_open(&top), TAB_OK);
    tab_set_net_allowed(top, 1);
    fh_host *h = fh_new("https://top.test/", stub_fetch, NULL, on_top_msg, NULL);
    tab_page p;
    assert_int_equal(tab_load_full(top, TOP_PAGE, sizeof TOP_PAGE - 1, "https://top.test/",
                                   1, 0, 0, &p), TAB_OK);
    fh_apply_top(h, &p);
    tab_page_free(&p);
    assert_int_equal(fh_count(h), 1);
    tab_eval_result e;
    assert_int_equal(tab_eval(top, "var f=document.getElementById('f'); f.parentNode.removeChild(f); 1", 66, &e), TAB_OK);
    tab_eval_result_free(&e);
    tab_page t;
    assert_int_equal(tab_tick(top, 0, &t), TAB_OK);
    fh_apply_top(h, &t);
    tab_page_free(&t);
    assert_int_equal(fh_count(h), 0);
    fh_free(h);
    tab_close(top);
}

static void test_failed_fetch_leaves_no_frame(void **state) {
    (void)state;
    tab *top = NULL;
    assert_int_equal(tab_open(&top), TAB_OK);
    tab_set_net_allowed(top, 1);
    fh_host *h = fh_new("https://top.test/", stub_fetch, NULL, on_top_msg, NULL);
    static const char page[] = "<html><body><iframe src=\"https://nowhere.test/x\"></iframe></body></html>";
    tab_page p;
    assert_int_equal(tab_load_full(top, page, sizeof page - 1, "https://top.test/", 1, 0, 0, &p), TAB_OK);
    fh_apply_top(h, &p);
    tab_page_free(&p);
    assert_int_equal(fh_count(h), 0);
    fh_free(h);
    tab_close(top);
}

static void test_bad_args(void **state) {
    (void)state;
    assert_null(fh_new(NULL, stub_fetch, NULL, on_top_msg, NULL));
    assert_null(fh_new("https://t/", NULL, NULL, on_top_msg, NULL));
    fh_free(NULL);
    fh_apply_top(NULL, NULL);
    assert_int_equal(fh_tick(NULL, 10), -1);
}

int main(int argc, char **argv) {
    tab_worker_dispatch(argc, argv);   /* the re-exec'd worker entry: must be first */
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_open_route_both_ways_and_drop_mismatch),
        cmocka_unit_test(test_removing_iframe_closes_worker),
        cmocka_unit_test(test_failed_fetch_leaves_no_frame),
        cmocka_unit_test(test_bad_args),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
