#define _GNU_SOURCE
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "cached_fetch.h"

#define NOW ((time_t)1800000000)
static const uint8_t WRAP[LS_KEY_LEN] = { 5, 5, 5 };
static char dir[256];
static hc_store *store;

/* ---- scripted fetcher ---- */
static int calls;
static char last_inm[256], last_ims[256], last_url[512];
static long next_code;
static const char *next_body, *next_cc, *next_etag, *next_lm;

static sf_status fake_fetch(const char *url, sf_config *cfg, sf_response *out, int *dg, int al) {
    (void)dg; (void)al;
    calls++;
    snprintf(last_url, sizeof last_url, "%s", url);
    snprintf(last_inm, sizeof last_inm, "%s", cfg->if_none_match ? cfg->if_none_match : "");
    snprintf(last_ims, sizeof last_ims, "%s", cfg->if_modified_since ? cfg->if_modified_since : "");
    memset(out, 0, sizeof *out);
    out->status = SF_OK;
    out->http_code = next_code;
    size_t bl = next_body ? strlen(next_body) : 0;
    out->body = (uint8_t *)malloc(bl + 1);
    memcpy(out->body, next_body ? next_body : "", bl + 1);
    out->body_len = bl;
    out->content_type = strdup("text/javascript");
    out->final_url = strdup(url);
    if (next_cc) snprintf(out->cache_control, sizeof out->cache_control, "%s", next_cc);
    if (next_etag) snprintf(out->etag, sizeof out->etag, "%s", next_etag);
    if (next_lm) snprintf(out->last_modified, sizeof out->last_modified, "%s", next_lm);
    return SF_OK;
}

static int setup(void **state) {
    (void)state;
    snprintf(dir, sizeof dir, "/tmp/fcf-test-XXXXXX");
    if (mkdtemp(dir) == NULL) return -1;
    if (hc_open(&store, dir, WRAP) != HC_OK) return -1;
    calls = 0; last_inm[0] = last_ims[0] = last_url[0] = '\0';
    next_code = 200; next_body = "body-1"; next_cc = "max-age=100"; next_etag = "\"v1\""; next_lm = NULL;
    return 0;
}
static int teardown(void **state) {
    (void)state;
    hc_close(store);
    char cmd[300];
    snprintf(cmd, sizeof cmd, "rm -rf %s", dir);
    return system(cmd) == 0 ? 0 : -1;
}

static sf_status get(const char *part, const char *url, sf_config *cfg, sf_response *r, time_t now) {
    int dg = 0;
    return cf_get_with(store, fake_fetch, part, url, cfg, r, &dg, 0, now);
}

static void test_miss_fetches_stores_then_fresh_hit_skips_network(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    assert_int_equal(get("site.test", "https://cdn.test/a.js", &cfg, &r, NOW), SF_OK);
    assert_int_equal(calls, 1);
    assert_string_equal((char *)r.body, "body-1");
    sf_response_free(&r);
    assert_int_equal(get("site.test", "https://cdn.test/a.js", &cfg, &r, NOW + 50), SF_OK);
    assert_int_equal(calls, 1);                              /* served from the cache */
    assert_int_equal(r.http_code, 200);
    assert_string_equal((char *)r.body, "body-1");
    assert_string_equal(r.content_type, "text/javascript");
    sf_response_free(&r);
}

static void test_stale_entry_revalidates_and_304_serves_cached_body(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    assert_int_equal(get("s", "https://cdn.test/a.js", &cfg, &r, NOW), SF_OK);
    sf_response_free(&r);
    next_code = 304; next_body = "";
    assert_int_equal(get("s", "https://cdn.test/a.js", &cfg, &r, NOW + 500), SF_OK);
    assert_int_equal(calls, 2);
    assert_string_equal(last_inm, "\"v1\"");                  /* conditional GET */
    assert_int_equal(r.http_code, 200);
    assert_string_equal((char *)r.body, "body-1");            /* the stored body */
    sf_response_free(&r);
    /* the 304 renewed the entry: fresh again, no further network */
    assert_int_equal(get("s", "https://cdn.test/a.js", &cfg, &r, NOW + 550), SF_OK);
    assert_int_equal(calls, 2);
    sf_response_free(&r);
}

static void test_stale_entry_with_new_200_replaces_the_body(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    assert_int_equal(get("s", "https://cdn.test/a.js", &cfg, &r, NOW), SF_OK);
    sf_response_free(&r);
    next_code = 200; next_body = "body-2"; next_etag = "\"v2\"";
    assert_int_equal(get("s", "https://cdn.test/a.js", &cfg, &r, NOW + 500), SF_OK);
    assert_string_equal((char *)r.body, "body-2");
    sf_response_free(&r);
    next_code = 304;
    assert_int_equal(get("s", "https://cdn.test/a.js", &cfg, &r, NOW + 700), SF_OK);
    assert_string_equal(last_inm, "\"v2\"");
    assert_string_equal((char *)r.body, "body-2");
    sf_response_free(&r);
}

static void test_partitions_isolated(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    assert_int_equal(get("one.test", "https://cdn.test/a.js", &cfg, &r, NOW), SF_OK);
    sf_response_free(&r);
    assert_int_equal(get("two.test", "https://cdn.test/a.js", &cfg, &r, NOW + 1), SF_OK);
    assert_int_equal(calls, 2);                               /* another site: not shared */
    sf_response_free(&r);
}

static void test_no_store_credentials_range_and_non_200_are_never_cached(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    next_cc = "no-store";
    assert_int_equal(get("s", "https://x.test/1", &cfg, &r, NOW), SF_OK); sf_response_free(&r);
    assert_int_equal(get("s", "https://x.test/1", &cfg, &r, NOW + 1), SF_OK); sf_response_free(&r);
    assert_int_equal(calls, 2);
    next_cc = "max-age=100";
    cfg.username = "u"; cfg.password = "p";
    assert_int_equal(get("s", "https://x.test/2", &cfg, &r, NOW), SF_OK); sf_response_free(&r);
    assert_int_equal(get("s", "https://x.test/2", &cfg, &r, NOW + 1), SF_OK); sf_response_free(&r);
    assert_int_equal(calls, 4);
    cfg = sf_config_default();
    cfg.range_start = 0; cfg.range_end = 99;
    assert_int_equal(get("s", "https://x.test/3", &cfg, &r, NOW), SF_OK); sf_response_free(&r);
    assert_int_equal(get("s", "https://x.test/3", &cfg, &r, NOW + 1), SF_OK); sf_response_free(&r);
    assert_int_equal(calls, 6);
    cfg = sf_config_default();
    next_code = 404;
    assert_int_equal(get("s", "https://x.test/4", &cfg, &r, NOW), SF_OK); sf_response_free(&r);
    assert_int_equal(get("s", "https://x.test/4", &cfg, &r, NOW + 1), SF_OK); sf_response_free(&r);
    assert_int_equal(calls, 8);
}

static void test_non_https_url_bypasses_the_cache(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    assert_int_equal(get("s", "http://plain.test/a", &cfg, &r, NOW), SF_OK); sf_response_free(&r);
    assert_int_equal(get("s", "http://plain.test/a", &cfg, &r, NOW + 1), SF_OK); sf_response_free(&r);
    assert_int_equal(calls, 2);
}

static void test_null_store_is_a_plain_fetch(void **state) {
    (void)state;
    sf_config cfg = sf_config_default();
    sf_response r;
    int dg = 0;
    assert_int_equal(cf_get_with(NULL, fake_fetch, "s", "https://a.test/", &cfg, &r, &dg, 0, NOW), SF_OK);
    assert_int_equal(calls, 1);
    sf_response_free(&r);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(test_miss_fetches_stores_then_fresh_hit_skips_network, setup, teardown),
        cmocka_unit_test_setup_teardown(test_stale_entry_revalidates_and_304_serves_cached_body, setup, teardown),
        cmocka_unit_test_setup_teardown(test_stale_entry_with_new_200_replaces_the_body, setup, teardown),
        cmocka_unit_test_setup_teardown(test_partitions_isolated, setup, teardown),
        cmocka_unit_test_setup_teardown(test_no_store_credentials_range_and_non_200_are_never_cached, setup, teardown),
        cmocka_unit_test_setup_teardown(test_non_https_url_bypasses_the_cache, setup, teardown),
        cmocka_unit_test_setup_teardown(test_null_store_is_a_plain_fetch, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
