/*
 * test_net_realm — CMocka suite for the pure realm classifier and router.
 *
 * Covers TLD-suffix classification (.onion / .i2p / clearnet, case, trailing dot,
 * lookalikes that must NOT match), URL host extraction, the routing table (realm x
 * config), and the two anonymity invariants: realm isolation (.onion only via Tor,
 * .i2p only via I2P) and fail-closed (missing proxy or unclassifiable URL => blocked).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "net_realm.h"

/* --- nr_classify_host --- */

static void test_classify_host_onion(void **state) {
    (void)state;
    assert_int_equal(nr_classify_host("expyuzz4wqqyqhjn.onion"), NR_ONION);
    assert_int_equal(nr_classify_host("sub.host.onion"), NR_ONION);
    assert_int_equal(nr_classify_host("HOST.ONION"), NR_ONION);   /* case-insensitive */
    assert_int_equal(nr_classify_host("host.onion."), NR_ONION);  /* trailing dot trimmed */
}

static void test_classify_host_i2p(void **state) {
    (void)state;
    assert_int_equal(nr_classify_host("stats.i2p"), NR_I2P);
    assert_int_equal(nr_classify_host("a.b.i2p"), NR_I2P);
    assert_int_equal(nr_classify_host("SITE.I2P"), NR_I2P);
}

static void test_classify_host_clearnet(void **state) {
    (void)state;
    assert_int_equal(nr_classify_host("example.com"), NR_CLEARNET);
    assert_int_equal(nr_classify_host("news.ycombinator.com"), NR_CLEARNET);
}

/* Lookalikes that must NOT be treated as a realm (the suffix is the FINAL label). */
static void test_classify_host_lookalikes(void **state) {
    (void)state;
    assert_int_equal(nr_classify_host("x.onion.com"), NR_CLEARNET);  /* ends in .com */
    assert_int_equal(nr_classify_host("notonion"), NR_CLEARNET);     /* no dot */
    assert_int_equal(nr_classify_host("onion"), NR_CLEARNET);        /* bare, no label */
    assert_int_equal(nr_classify_host("i2p"), NR_CLEARNET);          /* bare, no label */
    assert_int_equal(nr_classify_host("fooonion"), NR_CLEARNET);     /* no dot before */
    assert_int_equal(nr_classify_host("a.i2p.net"), NR_CLEARNET);    /* ends in .net */
}

static void test_classify_host_edges(void **state) {
    (void)state;
    assert_int_equal(nr_classify_host(NULL), NR_CLEARNET);
    assert_int_equal(nr_classify_host(""), NR_CLEARNET);
    assert_int_equal(nr_classify_host(".onion"), NR_CLEARNET);  /* empty leading label */
    char big[300];
    memset(big, 'a', sizeof big);
    big[sizeof big - 1] = '\0';
    assert_int_equal(nr_classify_host(big), NR_CLEARNET);       /* oversize */
}

/* --- nr_classify_url --- */

static void test_classify_url(void **state) {
    (void)state;
    assert_int_equal(nr_classify_url("https://abc.onion/path?q=1"), NR_ONION);
    assert_int_equal(nr_classify_url("http://site.i2p/"), NR_I2P);
    assert_int_equal(nr_classify_url("https://example.com:443/x"), NR_CLEARNET);
    assert_int_equal(nr_classify_url("https://host.onion:8080/"), NR_ONION);
    assert_int_equal(nr_classify_url("garbage-no-host"), NR_CLEARNET);
    assert_int_equal(nr_classify_url(NULL), NR_CLEARNET);
}

/* --- nr_route_for: the routing table --- */

static void test_route_onion(void **state) {
    (void)state;
    nr_config tor_on = { .tor_enabled = 1, .i2p_enabled = 0, .torify_clearnet = 0 };
    nr_config tor_off = { .tor_enabled = 0, .i2p_enabled = 1, .torify_clearnet = 1 };
    assert_int_equal(nr_route_for("https://x.onion/", tor_on), NR_ROUTE_TOR);
    /* Fail-closed: .onion with no Tor proxy is BLOCKED, never direct. */
    assert_int_equal(nr_route_for("https://x.onion/", tor_off), NR_ROUTE_BLOCKED);
}

static void test_route_i2p(void **state) {
    (void)state;
    nr_config i2p_on = { .tor_enabled = 0, .i2p_enabled = 1, .torify_clearnet = 0 };
    nr_config i2p_off = { .tor_enabled = 1, .i2p_enabled = 0, .torify_clearnet = 1 };
    assert_int_equal(nr_route_for("http://x.i2p/", i2p_on), NR_ROUTE_I2P);
    assert_int_equal(nr_route_for("http://x.i2p/", i2p_off), NR_ROUTE_BLOCKED);
}

static void test_route_clearnet(void **state) {
    (void)state;
    nr_config direct = { .tor_enabled = 0, .i2p_enabled = 0, .torify_clearnet = 0 };
    nr_config tor_no_torify = { .tor_enabled = 1, .i2p_enabled = 0, .torify_clearnet = 0 };
    nr_config torify = { .tor_enabled = 1, .i2p_enabled = 0, .torify_clearnet = 1 };
    nr_config torify_but_no_tor = { .tor_enabled = 0, .i2p_enabled = 0, .torify_clearnet = 1 };

    assert_int_equal(nr_route_for("https://example.com/", direct), NR_ROUTE_DIRECT);
    assert_int_equal(nr_route_for("https://example.com/", tor_no_torify), NR_ROUTE_DIRECT);
    assert_int_equal(nr_route_for("https://example.com/", torify), NR_ROUTE_TOR);
    /* torify requested but Tor not enabled: clearnet stays direct (torify is moot). */
    assert_int_equal(nr_route_for("https://example.com/", torify_but_no_tor), NR_ROUTE_DIRECT);
}

static void test_route_null_blocked(void **state) {
    (void)state;
    nr_config all_on = { .tor_enabled = 1, .i2p_enabled = 1, .torify_clearnet = 1 };
    assert_int_equal(nr_route_for(NULL, all_on), NR_ROUTE_BLOCKED);
}

/* --- name helpers --- */

static void test_realm_allows_http(void **state) {
    (void)state;
    /* I2P eepsites are http; .onion stays https-only; clearnet always https. */
    assert_int_equal(nr_realm_allows_http(NR_I2P), 1);
    assert_int_equal(nr_realm_allows_http(NR_ONION), 0);
    assert_int_equal(nr_realm_allows_http(NR_CLEARNET), 0);
}

static void test_names(void **state) {
    (void)state;
    assert_string_equal(nr_realm_name(NR_CLEARNET), "clearnet");
    assert_string_equal(nr_realm_name(NR_ONION), "onion");
    assert_string_equal(nr_realm_name(NR_I2P), "i2p");
    assert_string_equal(nr_route_name(NR_ROUTE_DIRECT), "direct");
    assert_string_equal(nr_route_name(NR_ROUTE_TOR), "tor");
    assert_string_equal(nr_route_name(NR_ROUTE_I2P), "i2p");
    assert_string_equal(nr_route_name(NR_ROUTE_BLOCKED), "blocked");
    /* Unknown enum values never return NULL. */
    assert_non_null(nr_realm_name((nr_realm)999));
    assert_non_null(nr_route_name((nr_route)999));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_classify_host_onion),
        cmocka_unit_test(test_classify_host_i2p),
        cmocka_unit_test(test_classify_host_clearnet),
        cmocka_unit_test(test_classify_host_lookalikes),
        cmocka_unit_test(test_classify_host_edges),
        cmocka_unit_test(test_classify_url),
        cmocka_unit_test(test_route_onion),
        cmocka_unit_test(test_route_i2p),
        cmocka_unit_test(test_route_clearnet),
        cmocka_unit_test(test_route_null_blocked),
        cmocka_unit_test(test_realm_allows_http),
        cmocka_unit_test(test_names),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
