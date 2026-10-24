#define _GNU_SOURCE
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cmocka.h>

#include "http_cache.h"

static const uint8_t WRAP[LS_KEY_LEN] = { 7, 7, 7 };
#define NOW ((time_t)1800000000)

static hc_meta meta_of(const char *cc, const char *etag, const char *lm, const char *date,
                       const char *expires) {
    hc_meta m;
    memset(&m, 0, sizeof m);
    snprintf(m.final_url, sizeof m.final_url, "https://a.test/x.js");
    snprintf(m.content_type, sizeof m.content_type, "text/javascript");
    if (cc) snprintf(m.cache_control, sizeof m.cache_control, "%s", cc);
    if (etag) snprintf(m.etag, sizeof m.etag, "%s", etag);
    if (lm) snprintf(m.last_modified, sizeof m.last_modified, "%s", lm);
    if (date) snprintf(m.date, sizeof m.date, "%s", date);
    if (expires) snprintf(m.expires, sizeof m.expires, "%s", expires);
    m.stored = NOW;
    return m;
}

/* --- pure decisions --- */

static void test_http_date_parses_imf_fixdate(void **state) {
    (void)state;
    assert_int_equal(hc_parse_http_date("Sun, 06 Nov 1994 08:49:37 GMT"), 784111777);
    assert_int_equal(hc_parse_http_date("Thu, 01 Jan 1970 00:00:00 GMT"), 0);
    assert_int_equal(hc_parse_http_date("garbage"), -1);
    assert_int_equal(hc_parse_http_date("Sun, 32 Nov 1994 08:49:37 GMT"), -1);
    assert_int_equal(hc_parse_http_date(NULL), -1);
}

static void test_lifetime_rules_in_order(void **state) {
    (void)state;
    hc_meta a = meta_of("public, max-age=600", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_lifetime(&a), 600);
    hc_meta nc = meta_of("no-cache, max-age=600", "\"e\"", NULL, NULL, NULL);
    assert_int_equal(hc_lifetime(&nc), 0);
    hc_meta ex = meta_of(NULL, NULL, NULL, "Sun, 06 Nov 1994 08:49:37 GMT", "Sun, 06 Nov 1994 09:49:37 GMT");
    assert_int_equal(hc_lifetime(&ex), 3600);
    /* heuristic: 10% of (Date - Last-Modified) = 1000s, capped at one day */
    hc_meta h = meta_of(NULL, NULL, "Sun, 06 Nov 1994 08:00:00 GMT", "Sun, 06 Nov 1994 10:46:40 GMT", NULL);
    assert_int_equal(hc_lifetime(&h), 1000);
    hc_meta big = meta_of(NULL, NULL, "Sun, 06 Nov 1994 08:00:00 GMT", "Sun, 06 Nov 2001 08:00:00 GMT", NULL);
    assert_int_equal(hc_lifetime(&big), HC_HEURISTIC_CAP);
    hc_meta none = meta_of(NULL, "\"e\"", NULL, NULL, NULL);
    assert_int_equal(hc_lifetime(&none), 0);
    hc_meta junk = meta_of("max-age=abc", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_lifetime(&junk), 0);
}

static void test_classify_fresh_revalidate_unusable(void **state) {
    (void)state;
    hc_meta m = meta_of("max-age=100", "\"e\"", NULL, NULL, NULL);
    assert_int_equal(hc_classify(&m, NOW + 50), HC_FRESH);
    assert_int_equal(hc_classify(&m, NOW + 100), HC_REVALIDATE);
    hc_meta nv = meta_of("max-age=100", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_classify(&nv, NOW + 500), HC_UNUSABLE);
    hc_meta nc = meta_of("no-cache", "\"e\"", NULL, NULL, NULL);
    assert_int_equal(hc_classify(&nc, NOW), HC_REVALIDATE);
    hc_meta back = meta_of("max-age=100", "\"e\"", NULL, NULL, NULL);
    assert_int_equal(hc_classify(&back, NOW - 5), HC_FRESH);   /* clock went back: not negative age */
}

static void test_storable_rules(void **state) {
    (void)state;
    hc_meta ok = meta_of("max-age=60", NULL, NULL, NULL, NULL);
    assert_true(hc_storable(200, &ok, 100));
    assert_false(hc_storable(404, &ok, 100));
    assert_false(hc_storable(200, &ok, HC_MAX_ENTRY + 1));
    hc_meta ns = meta_of("no-store, max-age=60", "\"e\"", NULL, NULL, NULL);
    assert_false(hc_storable(200, &ns, 100));
    hc_meta none = meta_of(NULL, NULL, NULL, NULL, NULL);
    assert_false(hc_storable(200, &none, 100));
    hc_meta val = meta_of(NULL, "\"e\"", NULL, NULL, NULL);
    assert_true(hc_storable(200, &val, 100));
}

/* --- store --- */

static char dir[256];
static int setup(void **state) {
    (void)state;
    snprintf(dir, sizeof dir, "/tmp/fhc-test-XXXXXX");
    return mkdtemp(dir) == NULL ? -1 : 0;
}
static int teardown(void **state) {
    (void)state;
    char cmd[300];
    snprintf(cmd, sizeof cmd, "rm -rf %s", dir);
    return system(cmd) == 0 ? 0 : -1;
}

static size_t count_files(const char *skip) {
    DIR *d = opendir(dir);
    size_t n = 0;
    struct dirent *e;
    while (d && (e = readdir(d)) != NULL)
        if (e->d_name[0] != '.' && (skip == NULL || strcmp(e->d_name, skip) != 0)) n++;
    if (d) closedir(d);
    return n;
}

static void test_put_get_roundtrip_and_no_plaintext_on_disk(void **state) {
    (void)state;
    hc_store *s = NULL;
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);
    hc_meta m = meta_of("max-age=60", "\"abc\"", NULL, NULL, NULL);
    const char *body = "console.log('very secret site content')";
    assert_int_equal(hc_put(s, "site.test", "https://a.test/x.js", &m, (const uint8_t *)body, strlen(body)), HC_OK);
    hc_meta got;
    uint8_t *b = NULL;
    size_t bl = 0;
    assert_int_equal(hc_get(s, "site.test", "https://a.test/x.js", &got, &b, &bl), HC_OK);
    assert_int_equal(bl, strlen(body));
    assert_memory_equal(b, body, bl);
    assert_string_equal(got.etag, "\"abc\"");
    assert_string_equal(got.final_url, "https://a.test/x.js");
    hc_body_free(b, bl);
    /* nothing readable: no URL, host or body text in any file name or content */
    char cmd[400];
    snprintf(cmd, sizeof cmd, "grep -rqE 'a\\.test|secret|site\\.test|x\\.js' %s", dir);
    assert_int_not_equal(system(cmd), 0);
    hc_close(s);
}

static void test_partitions_do_not_share_entries(void **state) {
    (void)state;
    hc_store *s = NULL;
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);
    hc_meta m = meta_of("max-age=60", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_put(s, "one.test", "https://cdn.test/lib.js", &m, (const uint8_t *)"A", 1), HC_OK);
    hc_meta g; uint8_t *b = NULL; size_t bl = 0;
    assert_int_equal(hc_get(s, "two.test", "https://cdn.test/lib.js", &g, &b, &bl), HC_MISS);
    assert_int_equal(hc_get(s, "one.test", "https://cdn.test/lib.js", &g, &b, &bl), HC_OK);
    hc_body_free(b, bl);
    hc_close(s);
}

static void test_tampered_entry_is_removed_and_misses(void **state) {
    (void)state;
    hc_store *s = NULL;
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);
    hc_meta m = meta_of("max-age=60", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_put(s, "p", "https://a.test/u", &m, (const uint8_t *)"data", 4), HC_OK);
    DIR *d = opendir(dir);
    struct dirent *e;
    char path[512] = "";
    while ((e = readdir(d)) != NULL)
        if (strlen(e->d_name) == 64) snprintf(path, sizeof path, "%s/%s", dir, e->d_name);
    closedir(d);
    assert_true(path[0] != '\0');
    FILE *f = fopen(path, "r+b");
    fseek(f, -3, SEEK_END);
    fputc('X', f); fputc('Y', f);
    fclose(f);
    hc_meta g; uint8_t *b = NULL; size_t bl = 0;
    assert_int_equal(hc_get(s, "p", "https://a.test/u", &g, &b, &bl), HC_MISS);
    assert_null(b);
    assert_int_not_equal(access(path, F_OK), 0);
    hc_close(s);
}

static void test_foreign_profile_key_empties_the_cache(void **state) {
    (void)state;
    hc_store *s = NULL;
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);
    hc_meta m = meta_of("max-age=60", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_put(s, "p", "https://a.test/u", &m, (const uint8_t *)"data", 4), HC_OK);
    hc_close(s);
    uint8_t other[LS_KEY_LEN] = { 9 };
    assert_int_equal(hc_open(&s, dir, other), HC_OK);
    hc_meta g; uint8_t *b = NULL; size_t bl = 0;
    assert_int_equal(hc_get(s, "p", "https://a.test/u", &g, &b, &bl), HC_MISS);
    hc_close(s);
}

static void test_redirect_memory_persists_and_expires(void **state) {
    (void)state;
    hc_store *s = NULL;
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);
    assert_int_equal(hc_redirect_put(s, "http://old.test/", "https://new.test/home", NOW), HC_OK);
    hc_close(s);
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);   /* a later session */
    char out[256];
    assert_int_equal(hc_redirect_get(s, "http://old.test/", NOW + 3600, out, sizeof out), HC_OK);
    assert_string_equal(out, "https://new.test/home");
    assert_int_equal(hc_redirect_get(s, "http://other.test/", NOW, out, sizeof out), HC_MISS);
    assert_int_equal(hc_redirect_get(s, "http://old.test/", NOW + HC_REDIRECT_TTL + 1, out, sizeof out), HC_MISS);
    /* only https destinations are remembered */
    assert_int_equal(hc_redirect_put(s, "https://a.test/", "http://downgrade.test/", NOW), HC_ERR_ARG);
    assert_int_equal(hc_redirect_put(s, "https://a.test/", "https://a.test/", NOW), HC_ERR_ARG);
    hc_close(s);
}

static void test_clear_removes_every_entry(void **state) {
    (void)state;
    hc_store *s = NULL;
    assert_int_equal(hc_open(&s, dir, WRAP), HC_OK);
    hc_meta m = meta_of("max-age=60", NULL, NULL, NULL, NULL);
    assert_int_equal(hc_put(s, "p", "https://a.test/1", &m, (const uint8_t *)"1", 1), HC_OK);
    assert_int_equal(hc_redirect_put(s, "http://o.test/", "https://n.test/", NOW), HC_OK);
    assert_true(count_files("pq.key") >= 2);
    hc_clear(s);
    assert_int_equal(count_files("pq.key"), 0);
    hc_close(s);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_http_date_parses_imf_fixdate),
        cmocka_unit_test(test_lifetime_rules_in_order),
        cmocka_unit_test(test_classify_fresh_revalidate_unusable),
        cmocka_unit_test(test_storable_rules),
        cmocka_unit_test_setup_teardown(test_put_get_roundtrip_and_no_plaintext_on_disk, setup, teardown),
        cmocka_unit_test_setup_teardown(test_partitions_do_not_share_entries, setup, teardown),
        cmocka_unit_test_setup_teardown(test_tampered_entry_is_removed_and_misses, setup, teardown),
        cmocka_unit_test_setup_teardown(test_foreign_profile_key_empties_the_cache, setup, teardown),
        cmocka_unit_test_setup_teardown(test_redirect_memory_persists_and_expires, setup, teardown),
        cmocka_unit_test_setup_teardown(test_clear_removes_every_entry, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
