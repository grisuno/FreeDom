/*
 * test_hostblock — CMocka suite for the pure /etc/hosts-format host filter.
 *
 * Covers parsing (hosts lines with a leading IP, bare-domain lines, comments,
 * multiple tokens, blank lines), token normalisation (lowercasing, trailing-dot
 * trimming, charset/length validation, IP-only tokens ignored), accumulation and
 * de-duplication, and the decision logic (blocklist covers subdomains, allowlist
 * wins and covers subdomains, sibling isolation, fail-open on NULL/empty/oversize).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "hostblock.h"

/* --- lifecycle --- */

static void test_new_free(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_non_null(s);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 0);
    assert_int_equal(hb_count(s, HB_LIST_ALLOW), 0);
    hb_free(s);
}

static void test_free_null_idempotent(void **state) {
    (void)state;
    hb_free(NULL);  /* must not crash */
}

static void test_count_null_set(void **state) {
    (void)state;
    assert_int_equal(hb_count(NULL, HB_LIST_BLOCK), 0);
    assert_int_equal(hb_count(NULL, HB_LIST_ALLOW), 0);
}

/* --- load: argument validation --- */

static void test_load_null_args(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(NULL, "example.com", HB_LIST_BLOCK), HB_ERR_NULL_ARG);
    assert_int_equal(hb_load(s, NULL, HB_LIST_BLOCK), HB_ERR_NULL_ARG);
    hb_free(s);
}

/* --- load: /etc/hosts format parsing --- */

static void test_hosts_line_drops_ip(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "0.0.0.0 ads.example.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 1);
    assert_int_equal(hb_check(s, "ads.example.com"), HB_BLOCK);
    hb_free(s);
}

static void test_various_ip_tokens_ignored(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "127.0.0.1 a.com\n::1 b.com\n", HB_LIST_BLOCK), HB_OK);
    /* Only the two domains are stored; the IPs (v4 and v6) are dropped. */
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2);
    hb_free(s);
}

static void test_bare_domain_per_line(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "tracker.com\nads.net\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2);
    assert_int_equal(hb_check(s, "tracker.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "ads.net"), HB_BLOCK);
    hb_free(s);
}

static void test_comments_and_blanks(void **state) {
    (void)state;
    hb_set *s = hb_new();
    const char *txt =
        "# this is a comment\n"
        "\n"
        "0.0.0.0 evil.com  # trailing comment\n"
        "   \t  \n"
        "good.com\n";
    assert_int_equal(hb_load(s, txt, HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2);
    assert_int_equal(hb_check(s, "evil.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "good.com"), HB_BLOCK);
    hb_free(s);
}

static void test_multiple_tokens_per_line(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "0.0.0.0 a.com b.com c.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 3);
    hb_free(s);
}

static void test_no_trailing_newline(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "0.0.0.0 last.com", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 1);
    assert_int_equal(hb_check(s, "last.com"), HB_BLOCK);
    hb_free(s);
}

/* --- load: normalisation and validation --- */

static void test_lowercased(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "ADS.Example.COM\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 1);
    assert_int_equal(hb_check(s, "ads.example.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "ADS.EXAMPLE.COM"), HB_BLOCK);
    hb_free(s);
}

static void test_trailing_dot_trimmed(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "example.com.\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 1);
    /* The stored form has no trailing dot; both query forms match. */
    assert_int_equal(hb_check(s, "example.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "example.com."), HB_BLOCK);
    hb_free(s);
}

static void test_invalid_tokens_skipped(void **state) {
    (void)state;
    hb_set *s = hb_new();
    /* Bad chars and a too-long label-soup are dropped; the good one stays. */
    const char *txt =
        "bad/slash.com\n"
        "has space\n"      /* two tokens: "has" and "space" -- both valid bare domains */
        "ok.com\n"
        "sp*ce.com\n";
    assert_int_equal(hb_load(s, txt, HB_LIST_BLOCK), HB_OK);
    /* valid: has, space, ok.com  (bad/slash.com and sp*ce.com rejected) */
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 3);
    assert_int_equal(hb_check(s, "ok.com"), HB_BLOCK);
    hb_free(s);
}

static void test_oversize_token_skipped(void **state) {
    (void)state;
    hb_set *s = hb_new();
    char big[300];
    memset(big, 'a', sizeof big);
    big[sizeof big - 1] = '\0';   /* 299 'a's: over the 253 limit */
    assert_int_equal(hb_load(s, big, HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 0);
    hb_free(s);
}

static void test_underscore_and_hyphen_valid(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "cdn-1.example.com\n_dmarc.example.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2);
    hb_free(s);
}

static void test_dedup_and_accumulate(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "dup.com\ndup.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 1);
    /* A second load accumulates; the repeat is still deduped. */
    assert_int_equal(hb_load(s, "dup.com\nother.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2);
    hb_free(s);
}

static void test_lists_independent(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "a.com\nb.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_load(s, "c.com\n", HB_LIST_ALLOW), HB_OK);
    assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2);
    assert_int_equal(hb_count(s, HB_LIST_ALLOW), 1);
    hb_free(s);
}

/* --- check: decision logic --- */

static void test_block_covers_subdomains(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "example.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_check(s, "example.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "ads.example.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "a.b.example.com"), HB_BLOCK);
    /* A sibling registrable domain is untouched. */
    assert_int_equal(hb_check(s, "example.org"), HB_ALLOW);
    assert_int_equal(hb_check(s, "notexample.com"), HB_ALLOW);
    hb_free(s);
}

static void test_allow_wins_and_covers_subdomains(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "example.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_load(s, "cdn.example.com\n", HB_LIST_ALLOW), HB_OK);
    /* The whitelisted subdomain (and its children) is visible despite the block. */
    assert_int_equal(hb_check(s, "cdn.example.com"), HB_ALLOW);
    assert_int_equal(hb_check(s, "x.cdn.example.com"), HB_ALLOW);
    /* The rest of the blocked domain stays blocked. */
    assert_int_equal(hb_check(s, "example.com"), HB_BLOCK);
    assert_int_equal(hb_check(s, "ads.example.com"), HB_BLOCK);
    hb_free(s);
}

static void test_no_lists_allows(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_check(s, "anything.com"), HB_ALLOW);
    hb_free(s);
}

static void test_is_allowlisted(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "example.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_load(s, "cdn.example.com\n", HB_LIST_ALLOW), HB_OK);

    /* Explicitly allowlisted, and covers subdomains. */
    assert_int_equal(hb_is_allowlisted(s, "cdn.example.com"), 1);
    assert_int_equal(hb_is_allowlisted(s, "x.cdn.example.com"), 1);
    /* Blocked-but-not-allowlisted, and a host on no list: both report 0 (not an
     * explicit allowlist entry, even though hb_check would ALLOW the unlisted one). */
    assert_int_equal(hb_is_allowlisted(s, "example.com"), 0);
    assert_int_equal(hb_is_allowlisted(s, "ads.example.com"), 0);
    assert_int_equal(hb_is_allowlisted(s, "unlisted.org"), 0);
    /* Edges fail to 0. */
    assert_int_equal(hb_is_allowlisted(NULL, "cdn.example.com"), 0);
    assert_int_equal(hb_is_allowlisted(s, NULL), 0);
    assert_int_equal(hb_is_allowlisted(s, ""), 0);
    hb_free(s);
}

static void test_check_fail_open_edges(void **state) {
    (void)state;
    hb_set *s = hb_new();
    assert_int_equal(hb_load(s, "example.com\n", HB_LIST_BLOCK), HB_OK);
    assert_int_equal(hb_check(NULL, "example.com"), HB_ALLOW);
    assert_int_equal(hb_check(s, NULL), HB_ALLOW);
    assert_int_equal(hb_check(s, ""), HB_ALLOW);
    char big[300];
    memset(big, 'a', sizeof big);
    big[sizeof big - 1] = '\0';
    assert_int_equal(hb_check(s, big), HB_ALLOW);  /* oversize host: fail open */
    hb_free(s);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_new_free),
        cmocka_unit_test(test_free_null_idempotent),
        cmocka_unit_test(test_count_null_set),
        cmocka_unit_test(test_load_null_args),
        cmocka_unit_test(test_hosts_line_drops_ip),
        cmocka_unit_test(test_various_ip_tokens_ignored),
        cmocka_unit_test(test_bare_domain_per_line),
        cmocka_unit_test(test_comments_and_blanks),
        cmocka_unit_test(test_multiple_tokens_per_line),
        cmocka_unit_test(test_no_trailing_newline),
        cmocka_unit_test(test_lowercased),
        cmocka_unit_test(test_trailing_dot_trimmed),
        cmocka_unit_test(test_invalid_tokens_skipped),
        cmocka_unit_test(test_oversize_token_skipped),
        cmocka_unit_test(test_underscore_and_hyphen_valid),
        cmocka_unit_test(test_dedup_and_accumulate),
        cmocka_unit_test(test_lists_independent),
        cmocka_unit_test(test_block_covers_subdomains),
        cmocka_unit_test(test_allow_wins_and_covers_subdomains),
        cmocka_unit_test(test_no_lists_allows),
        cmocka_unit_test(test_is_allowlisted),
        cmocka_unit_test(test_check_fail_open_edges),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
