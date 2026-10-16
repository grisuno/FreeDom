/* Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool.
 * The scanner eats hostile HTML on the trusted side; the pool must fetch every
 * unique URL exactly once, truly in parallel, with single-owner result handoff. */

#define _POSIX_C_SOURCE 200809L

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <cmocka.h>

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "prefetch.h"

/* --- scanner ----------------------------------------------------------- */

static void test_scan_null_args(void **state) {
    (void)state;
    pf_list l;
    assert_int_equal(pf_scan(NULL, 3, &l), -1);
    assert_int_equal(pf_scan("x", 1, NULL), -1);
    assert_int_equal(pf_scan("", 0, &l), 0);
    assert_int_equal(l.count, 0);
    pf_list_free(&l);
}

static void test_scan_basic_stylesheet_and_script(void **state) {
    (void)state;
    const char *html =
        "<html><head>"
        "<link rel=\"stylesheet\" href=\"news.css\">"
        "<script src=\"app.js\"></script>"
        "</head><body><p>hi</p></body></html>";
    pf_list l;
    assert_int_equal(pf_scan(html, strlen(html), &l), 0);
    assert_int_equal(l.count, 2);
    assert_int_equal(l.refs[0].kind, PF_STYLESHEET);
    assert_string_equal(l.refs[0].url, "news.css");
    assert_int_equal(l.refs[1].kind, PF_SCRIPT);
    assert_string_equal(l.refs[1].url, "app.js");
    pf_list_free(&l);
}

/* Attribute order, quote style and tag case must not matter; the raw value is
 * kept verbatim (resolution belongs to the policy-gated fetcher). */
static void test_scan_attr_order_quotes_case(void **state) {
    (void)state;
    const char *html =
        "<LINK HREF='/a/b.css' REL=STYLESHEET>"
        "<link type=\"text/css\" rel = 'stylesheet' href = https://cdn.example/x.css >"
        "<SCRIPT defer SRC=/js/m.js></SCRIPT>";
    pf_list l;
    assert_int_equal(pf_scan(html, strlen(html), &l), 0);
    assert_int_equal(l.count, 3);
    assert_string_equal(l.refs[0].url, "/a/b.css");
    assert_int_equal(l.refs[0].kind, PF_STYLESHEET);
    assert_string_equal(l.refs[1].url, "https://cdn.example/x.css");
    assert_string_equal(l.refs[2].url, "/js/m.js");
    assert_int_equal(l.refs[2].kind, PF_SCRIPT);
    pf_list_free(&l);
}

/* A rel list carrying other tokens still counts iff it contains "stylesheet";
 * any other rel must NOT be prefetched (fail closed: never widen what the page
 * could request). An inline <script> emits nothing. */
static void test_scan_rel_gate_and_inline_script(void **state) {
    (void)state;
    const char *html =
        "<link rel=\"alternate stylesheet\" href=\"alt.css\">"
        "<link rel=\"icon\" href=\"favicon.ico\">"
        "<link rel=\"preload\" href=\"font.woff2\">"
        "<link rel=\"stylesheets\" href=\"typo.css\">"
        "<link href=\"norel.css\">"
        "<script>var x = 1;</script>";
    pf_list l;
    assert_int_equal(pf_scan(html, strlen(html), &l), 0);
    assert_int_equal(l.count, 1);
    assert_string_equal(l.refs[0].url, "alt.css");
    pf_list_free(&l);
}

/* Comment, <script> and <style> CONTENTS are opaque: a tag-shaped string inside
 * them must never be prefetched (the worker would never request it). */
static void test_scan_opaque_regions(void **state) {
    (void)state;
    const char *html =
        "<!-- <link rel=stylesheet href=commented.css> -->"
        "<script>document.write('<link rel=stylesheet href=fromjs.css>');</script>"
        "<style>/* <script src=instyle.js></script> */</style>"
        "<link rel=stylesheet href=real.css>";
    pf_list l;
    assert_int_equal(pf_scan(html, strlen(html), &l), 0);
    assert_int_equal(l.count, 1);
    assert_string_equal(l.refs[0].url, "real.css");
    pf_list_free(&l);
}

/* Bounded: refs past PF_MAX_REFS are dropped, never overflowed. */
static void test_scan_ref_cap(void **state) {
    (void)state;
    char *html = malloc((PF_MAX_REFS + 8) * 64);
    assert_non_null(html);
    size_t off = 0;
    for (int i = 0; i < PF_MAX_REFS + 8; ++i) {
        int r = snprintf(html + off, 64, "<link rel=stylesheet href=s%d.css>", i);
        assert_true(r > 0 && (size_t)r < 64);
        off += (size_t)r;
    }
    pf_list l;
    assert_int_equal(pf_scan(html, off, &l), 0);
    assert_int_equal(l.count, PF_MAX_REFS);
    pf_list_free(&l);
    free(html);
}

/* --- pool -------------------------------------------------------------- */

/* Deterministic fake fetcher: body echoes the URL so take() can verify the
 * per-URL mapping; a barrier proves REAL concurrency (the test only passes if
 * PF_MAX_THREADS fetches are simultaneously inside the callback). */
typedef struct fake_ctx {
    pthread_barrier_t barrier;
    int               use_barrier;
    int               calls;         /* guarded by lock */
    pthread_mutex_t   lock;
    const char       *fail_url;      /* this URL's fetch reports failure */
    int               allow_post;    /* adapter test passes a POST through */
} fake_ctx;

static int fake_fetch(void *vctx, const char *method, const char *url,
                      const char *body, size_t body_len,
                      int *st, char **ob, size_t *ol, char **oct) {
    fake_ctx *c = vctx;
    (void)body; (void)body_len;
    if (!c->allow_post) assert_string_equal(method, "GET");
    pthread_mutex_lock(&c->lock);
    c->calls++;
    pthread_mutex_unlock(&c->lock);
    if (c->use_barrier) pthread_barrier_wait(&c->barrier);
    if (c->fail_url != NULL && strcmp(url, c->fail_url) == 0) return -1;
    *st = 200;
    *ob = strdup(url);
    *ol = strlen(url);
    *oct = strdup("text/css");
    return (*ob != NULL && *oct != NULL) ? 0 : -1;
}

static void test_pool_parallel_fetch_and_take(void **state) {
    (void)state;
    /* One URL per thread, however many threads the pool runs. */
    char names[PF_MAX_THREADS][16];
    const char *urls[PF_MAX_THREADS];
    for (int k = 0; k < PF_MAX_THREADS; ++k) {
        snprintf(names[k], sizeof names[k], "%c.css", 'a' + k);
        urls[k] = names[k];
    }
    fake_ctx c;
    memset(&c, 0, sizeof c);
    pthread_mutex_init(&c.lock, NULL);
    pthread_barrier_init(&c.barrier, NULL, PF_MAX_THREADS);
    c.use_barrier = 1;

    pf_pool p;
    assert_int_equal(pf_pool_start(&p, urls, PF_MAX_THREADS, fake_fetch, &c), 0);

    /* Take in reverse order to prove results map per-URL, not per-arrival. */
    for (int i = PF_MAX_THREADS - 1; i >= 0; --i) {
        int rc = -1, st = 0;
        char *b = NULL, *ct = NULL;
        size_t len = 0;
        assert_int_equal(pf_pool_take(&p, urls[i], &rc, &st, &b, &len, &ct), 1);
        assert_int_equal(rc, 0);
        assert_int_equal(st, 200);
        assert_non_null(b);
        assert_string_equal(b, urls[i]);
        assert_int_equal(len, strlen(urls[i]));
        assert_string_equal(ct, "text/css");
        free(b); free(ct);
    }
    pf_pool_finish(&p);
    assert_int_equal(c.calls, PF_MAX_THREADS);
    pthread_barrier_destroy(&c.barrier);
    pthread_mutex_destroy(&c.lock);
}

static void test_pool_miss_consume_and_failure(void **state) {
    (void)state;
    const char *urls[3] = { "x.css", "x.css", "bad.css" }; /* dup deduplicated */
    fake_ctx c;
    memset(&c, 0, sizeof c);
    pthread_mutex_init(&c.lock, NULL);
    c.fail_url = "bad.css";

    pf_pool p;
    assert_int_equal(pf_pool_start(&p, urls, 3, fake_fetch, &c), 0);

    int rc = 0, st = 0;
    char *b = NULL, *ct = NULL;
    size_t len = 0;

    /* Unknown URL: miss, caller falls back to the direct fetch. */
    assert_int_equal(pf_pool_take(&p, "nope.css", &rc, &st, &b, &len, &ct), 0);

    /* Hit, then single-owner consumption: the second take of x.css misses. */
    assert_int_equal(pf_pool_take(&p, "x.css", &rc, &st, &b, &len, &ct), 1);
    assert_int_equal(rc, 0);
    assert_string_equal(b, "x.css");
    free(b); free(ct);
    b = NULL; ct = NULL;
    assert_int_equal(pf_pool_take(&p, "x.css", &rc, &st, &b, &len, &ct), 0);

    /* A failed fetch is a HIT with rc != 0 (never retried by the caller). */
    assert_int_equal(pf_pool_take(&p, "bad.css", &rc, &st, &b, &len, &ct), 1);
    assert_int_not_equal(rc, 0);
    assert_null(b);

    pf_pool_finish(&p);
    /* Dedup: x.css fetched once, bad.css once. */
    assert_int_equal(c.calls, 2);
    pthread_mutex_destroy(&c.lock);

    /* After finish every take misses (and unconsumed results were freed --
     * verified by the ASan run of this suite). */
    assert_int_equal(pf_pool_take(&p, "x.css", &rc, &st, &b, &len, &ct), 0);
}

/* finish() with results nobody took must free them all (ASan-verified) and be
 * idempotent. An empty pool is a no-op that reports -1 from start. */
static void test_pool_finish_unconsumed_and_empty(void **state) {
    (void)state;
    const char *urls[2] = { "left.css", "over.css" };
    fake_ctx c;
    memset(&c, 0, sizeof c);
    pthread_mutex_init(&c.lock, NULL);

    pf_pool p;
    assert_int_equal(pf_pool_start(&p, urls, 2, fake_fetch, &c), 0);
    pf_pool_finish(&p);
    pf_pool_finish(&p); /* idempotent */
    assert_int_equal(c.calls, 2);
    pthread_mutex_destroy(&c.lock);

    pf_pool q;
    assert_int_equal(pf_pool_start(&q, NULL, 0, fake_fetch, &c), -1);
    pf_pool_finish(&q); /* safe on a never-started pool */
}

/* The shared cache-first adapter: pooled GETs hit the pool, everything else
 * (POST, miss, no pool) falls through to the inner fetcher exactly once. */
static void test_pooled_fetch_adapter(void **state) {
    (void)state;
    const char *urls[1] = { "pooled.css" };
    fake_ctx c;
    memset(&c, 0, sizeof c);
    pthread_mutex_init(&c.lock, NULL);
    c.allow_post = 1;

    pf_pool p;
    assert_int_equal(pf_pool_start(&p, urls, 1, fake_fetch, &c), 0);
    pf_gated_fetch g = { fake_fetch, &c, &p };

    int st = 0; char *b = NULL, *ct = NULL; size_t len = 0;
    assert_int_equal(pf_pooled_fetch(&g, "GET", "pooled.css", NULL, 0,
                                     &st, &b, &len, &ct), 0);
    assert_string_equal(b, "pooled.css");
    free(b); free(ct); b = NULL; ct = NULL;

    /* Miss (unknown URL) and POST both go to the inner fetcher directly. */
    assert_int_equal(pf_pooled_fetch(&g, "GET", "direct.css", NULL, 0,
                                     &st, &b, &len, &ct), 0);
    assert_string_equal(b, "direct.css");
    free(b); free(ct); b = NULL; ct = NULL;
    assert_int_equal(pf_pooled_fetch(&g, "POST", "pooled.css", "x", 1,
                                     &st, &b, &len, &ct), 0);
    free(b); free(ct); b = NULL; ct = NULL;

    pf_pool_finish(&p);
    /* pool(1) + direct miss(1) + POST(1) = 3 inner calls total. */
    assert_int_equal(c.calls, 3);

    /* With no pool the adapter is a transparent passthrough. */
    g.pool = NULL;
    assert_int_equal(pf_pooled_fetch(&g, "GET", "plain.css", NULL, 0,
                                     &st, &b, &len, &ct), 0);
    assert_string_equal(b, "plain.css");
    free(b); free(ct);
    pthread_mutex_destroy(&c.lock);
}


/* --- ES module graph (spec/prefetch.md section 8) ----------------------- */

static void test_scan_imports_static_only(void **state) {
    (void)state;
    char out[8][PF_SPEC_MAX];
    const char *js = "import{a}from\"./a.js\";export*from'../b.mjs';"
                     "import \"https://x.example/c.js\";\n"
                     "import x from \"react\";const l=import(\"./lazy.js\");"
                     "// import \"./no1.js\"\n/* import \"./no2.js\" */"
                     "import def, {b as c} from \"/abs/d.js\"";
    size_t n = pf_scan_imports(js, strlen(js), out, 8);
    /* Bare specifiers are returned too: the pool resolves them through the
     * page's import map (or drops them when there is none). */
    assert_int_equal(n, 5);
    assert_string_equal(out[0], "./a.js");
    assert_string_equal(out[1], "../b.mjs");
    assert_string_equal(out[2], "https://x.example/c.js");
    assert_string_equal(out[3], "react");
    assert_string_equal(out[4], "/abs/d.js");
    assert_int_equal(pf_scan_imports(NULL, 3, out, 8), 0);
    assert_int_equal(pf_scan_imports("import \"./x.js\"", 16, out, 0), 0);
}

/* A fake fetcher serving a two-module graph: a.js imports ./b.js. */
static int graph_fetch(void *ctx, const char *method, const char *url,
                       const char *body, size_t body_len,
                       int *out_status, char **out_body, size_t *out_len,
                       char **out_ctype) {
    (void)ctx; (void)method; (void)body; (void)body_len;
    const char *src = strstr(url, "/a.js") ? "import\"./b.js\";" : "export const b=1;";
    *out_status = 200;
    *out_body = strdup(src);
    *out_len = strlen(src);
    *out_ctype = strdup("text/javascript");
    return 0;
}

static int bare_fetch(void *ctx, const char *method, const char *url,
                      const char *body, size_t body_len,
                      int *out_status, char **out_body, size_t *out_len,
                      char **out_ctype) {
    (void)ctx; (void)method; (void)body; (void)body_len;
    const char *src = strstr(url, "/a2.js") ? "import{x}from\"lib\";" : "export const x=1;";
    *out_status = 200;
    *out_body = strdup(src);
    *out_len = strlen(src);
    *out_ctype = strdup("text/javascript");
    return 0;
}

static void test_pool_follows_module_graph(void **state) {
    (void)state;
    pf_pool p;
    const char *urls[] = { "https://h.example/js/a.js" };
    assert_int_equal(pf_pool_start(&p, urls, 1, graph_fetch, NULL), 0);
    int rc = -1, st = 0;
    char *b = NULL, *ct = NULL;
    size_t l = 0;
    assert_int_equal(pf_pool_take(&p, "https://h.example/js/a.js", &rc, &st, &b, &l, &ct), 1);
    free(b); free(ct);
    /* b.js was queued by the pool thread that fetched a.js. */
    assert_int_equal(pf_pool_take(&p, "https://h.example/js/b.js", &rc, &st, &b, &l, &ct), 1);
    assert_int_equal(rc, 0);
    assert_string_equal(b, "export const b=1;");
    free(b); free(ct);
    assert_int_equal(pf_pool_add(&p, "https://h.example/js/a.js"), 0);   /* dedupe */
    pf_pool_finish(&p);
}


static void test_find_importmap(void **state) {
    (void)state;
    const char *h = "<html><script src=a.js></script><SCRIPT type=\"importmap\">"
                    "{\"imports\":{\"react\":\"/r.js\"}}</script></html>";
    size_t st = 0, n = 0;
    assert_int_equal(pf_find_importmap(h, strlen(h), &st, &n), 1);
    assert_int_equal(n, strlen("{\"imports\":{\"react\":\"/r.js\"}}"));
    assert_int_equal(memcmp(h + st, "{\"imports\"", 10), 0);
    assert_int_equal(pf_find_importmap("<script>x</script>", 18, &st, &n), 0);
}

/* A bare specifier resolves through the page's import map. */
static void test_pool_start_page_import_map(void **state) {
    (void)state;
    const char *h = "<html><script type=importmap>{\"imports\":{\"lib\":\"/js/b.js\"}}"
                    "</script><script type=module src=\"/js/a2.js\"></script></html>";
    pf_pool p;
    assert_int_equal(pf_pool_start_page(&p, h, strlen(h), "https://h.example/page", 0, 1,
                                        bare_fetch, NULL), 0);
    int rc = -1, st = 0;
    char *b = NULL, *ct = NULL;
    size_t l = 0;
    assert_int_equal(pf_pool_take(&p, "https://h.example/js/a2.js", &rc, &st, &b, &l, &ct), 1);
    free(b); free(ct);
    assert_int_equal(pf_pool_take(&p, "https://h.example/js/b.js", &rc, &st, &b, &l, &ct), 1);
    free(b); free(ct);
    pf_pool_finish(&p);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_scan_null_args),
        cmocka_unit_test(test_scan_basic_stylesheet_and_script),
        cmocka_unit_test(test_scan_attr_order_quotes_case),
        cmocka_unit_test(test_scan_rel_gate_and_inline_script),
        cmocka_unit_test(test_scan_opaque_regions),
        cmocka_unit_test(test_scan_ref_cap),
        cmocka_unit_test(test_pool_parallel_fetch_and_take),
        cmocka_unit_test(test_pool_miss_consume_and_failure),
        cmocka_unit_test(test_pool_finish_unconsumed_and_empty),
        cmocka_unit_test(test_pooled_fetch_adapter),
        cmocka_unit_test(test_scan_imports_static_only),
        cmocka_unit_test(test_pool_follows_module_graph),
        cmocka_unit_test(test_find_importmap),
        cmocka_unit_test(test_pool_start_page_import_map),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
