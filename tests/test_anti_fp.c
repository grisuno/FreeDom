/*
 * TDD suite for anti_fp (Hito 5 - anti-fingerprinting).
 *
 * Pure primitives: no I/O. Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "anti_fp.h"

/* --- clocks --- */

static void test_coarsen_time(void **state) {
    (void)state;
    uint64_t res = fp_timer_resolution_ms();
    assert_true(res > 0);
    assert_int_equal((int)fp_coarsen_time_ms(0), 0);
    assert_int_equal((int)fp_coarsen_time_ms(res - 1), 0);
    assert_int_equal((int)fp_coarsen_time_ms(res), (int)res);
    assert_int_equal((int)fp_coarsen_time_ms(res + 1), (int)res);
    /* idempotent on aligned values */
    uint64_t a = fp_coarsen_time_ms(12345);
    assert_int_equal((int)fp_coarsen_time_ms(a), (int)a);
    assert_int_equal((int)(a % res), 0);
}

/* --- normalized identity --- */

static void test_identity_is_fixed(void **state) {
    (void)state;
    assert_non_null(fp_user_agent());
    assert_true(strlen(fp_user_agent()) > 0);
    /* The normalized identity must blend in, not advertise the browser name: a UA
     * containing "Freedom" is a unique fingerprint and trips bot detection. */
    assert_null(strstr(fp_user_agent(), "Freedom"));
    assert_non_null(strstr(fp_user_agent(), "Firefox"));
    assert_string_equal(fp_user_agent(), FP_USER_AGENT);
    assert_non_null(fp_accept_language());
    /* Header form carries a q-value; list form does not (it feeds navigator.languages). */
    assert_string_equal(fp_accept_language(), "en-US,en");
    assert_string_equal(fp_accept_language_header(), "en-US,en;q=0.5");
    assert_non_null(strstr(fp_accept_language_header(), "en-US"));
    assert_null(strchr(fp_accept_language(), ';'));
    assert_string_equal(fp_timezone(), "UTC");
    assert_string_equal(fp_platform(), "Linux x86_64");
    assert_string_equal(fp_vendor(), "");
    assert_true(fp_hardware_concurrency() > 0);
    assert_true(fp_device_memory_gb() > 0);
    /* stable across calls */
    assert_string_equal(fp_user_agent(), fp_user_agent());
    assert_string_equal(fp_platform(), fp_platform());
}

/* --- legacy navigator identity (Hito 30b: blend-in surface) --- */

static void test_legacy_identity_fixed(void **state) {
    (void)state;
    assert_non_null(fp_app_version());
    assert_string_equal(fp_app_version(), FP_USER_AGENT);
    assert_string_equal(fp_app_code_name(), "Mozilla");
    assert_string_equal(fp_app_name(), "Netscape");
    assert_string_equal(fp_product(), "Gecko");
    assert_string_equal(fp_product_sub(), "20100101");
    assert_string_equal(fp_oscpu(), "Linux x86_64");
    assert_non_null(fp_build_id());
    assert_true(strlen(fp_build_id()) > 0);
}

static void test_boolean_props(void **state) {
    (void)state;
    assert_int_equal(fp_max_touch_points(), 0);
    assert_int_equal(fp_on_line(), 1);
    assert_int_equal(fp_cookie_enabled(), 1);
}

/* --- screen bucketing --- */

static void test_bucket_screen(void **state) {
    (void)state;
    int w = 0, h = 0;
    fp_bucket_screen(1920, 1080, &w, &h);
    assert_int_equal(w, 1920); assert_int_equal(h, 1080);

    fp_bucket_screen(1680, 1050, &w, &h);
    assert_int_equal(w, 1600); assert_int_equal(h, 900); /* largest that fits */

    fp_bucket_screen(1366, 768, &w, &h);
    assert_int_equal(w, 1366); assert_int_equal(h, 768);

    fp_bucket_screen(640, 480, &w, &h);
    assert_int_equal(w, 800); assert_int_equal(h, 600); /* none fits: smallest */
}

/* --- readback poisoning --- */

static void test_perturb_deterministic(void **state) {
    (void)state;
    uint8_t a[4096], b[4096];
    memset(a, 0x80, sizeof a);
    memcpy(b, a, sizeof b);
    fp_perturb(a, sizeof a, 0xABCDEF1234567890ULL);
    fp_perturb(b, sizeof b, 0xABCDEF1234567890ULL);
    assert_memory_equal(a, b, sizeof a); /* same key => same output */
}

static void test_perturb_bounded_lsb(void **state) {
    (void)state;
    uint8_t orig[2048], buf[2048];
    for (size_t i = 0; i < sizeof orig; ++i) orig[i] = (uint8_t)(i & 0xFF);
    memcpy(buf, orig, sizeof buf);
    fp_perturb(buf, sizeof buf, 42);
    int changed = 0;
    for (size_t i = 0; i < sizeof buf; ++i) {
        uint8_t diff = buf[i] ^ orig[i];
        assert_true(diff == 0 || diff == 1); /* only the LSB may flip */
        if (diff) ++changed;
    }
    assert_true(changed > 0); /* on a large buffer, some bytes flip */
}

static void test_perturb_key_sensitive(void **state) {
    (void)state;
    uint8_t a[4096], b[4096];
    memset(a, 0, sizeof a);
    memset(b, 0, sizeof b);
    fp_perturb(a, sizeof a, 1);
    fp_perturb(b, sizeof b, 2);
    assert_memory_not_equal(a, b, sizeof a); /* different key => different output */
}

static void test_perturb_safe_edges(void **state) {
    (void)state;
    fp_perturb(NULL, 100, 1); /* NULL: no-op, no crash */
    uint8_t x = 5;
    fp_perturb(&x, 0, 1);     /* len 0: no-op */
    assert_int_equal(x, 5);
}

/* --- per-origin readback key (fp_origin_key) --- */

static void test_origin_key_deterministic(void **state) {
    (void)state;
    uint64_t k1 = fp_origin_key(0x0000DEADBEEFCAFEULL, "example.com");
    uint64_t k2 = fp_origin_key(0x0000DEADBEEFCAFEULL, "example.com");
    assert_true(k1 == k2); /* same (session, site) => same key */
}

static void test_origin_key_per_site(void **state) {
    (void)state;
    uint64_t sess = 0x0123456789ABCDEFULL;
    uint64_t a = fp_origin_key(sess, "example.com");
    uint64_t b = fp_origin_key(sess, "other.org");
    uint64_t c = fp_origin_key(sess, "evil.net");
    /* Different sites in one session => unlinkable keys. */
    assert_true(a != b);
    assert_true(a != c);
    assert_true(b != c);
}

static void test_origin_key_per_session(void **state) {
    (void)state;
    /* Same site, different session secret => different key. */
    assert_true(fp_origin_key(1, "example.com") != fp_origin_key(2, "example.com"));
}

static void test_origin_key_empty_namespace(void **state) {
    (void)state;
    uint64_t sess = 99;
    uint64_t null_k  = fp_origin_key(sess, NULL);
    uint64_t empty_k = fp_origin_key(sess, "");
    assert_true(null_k == empty_k);                            /* NULL and "" are one namespace */
    assert_true(null_k != fp_origin_key(sess, "example.com")); /* distinct from a real site */
}

/* The property that actually matters: the same canvas buffer poisoned under two
 * different sites' keys diverges, so a tracker cannot link the two readbacks;
 * and the same site reproduces the same poisoning. */
static void test_origin_key_unlinks_readback(void **state) {
    (void)state;
    uint64_t sess = 0x00000000FEEDFACEULL;
    uint8_t a[4096], b[4096], c[4096];
    memset(a, 0x80, sizeof a);
    memcpy(b, a, sizeof b);
    memcpy(c, a, sizeof c);
    fp_perturb(a, sizeof a, fp_origin_key(sess, "site-a.com"));
    fp_perturb(b, sizeof b, fp_origin_key(sess, "site-b.com"));
    fp_perturb(c, sizeof c, fp_origin_key(sess, "site-a.com"));
    assert_memory_not_equal(a, b, sizeof a); /* cross-origin: diverges */
    assert_memory_equal(a, c, sizeof a);     /* same origin: reproducible */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_coarsen_time),
        cmocka_unit_test(test_identity_is_fixed),
        cmocka_unit_test(test_legacy_identity_fixed),
        cmocka_unit_test(test_boolean_props),
        cmocka_unit_test(test_bucket_screen),
        cmocka_unit_test(test_perturb_deterministic),
        cmocka_unit_test(test_perturb_bounded_lsb),
        cmocka_unit_test(test_perturb_key_sensitive),
        cmocka_unit_test(test_perturb_safe_edges),
        cmocka_unit_test(test_origin_key_deterministic),
        cmocka_unit_test(test_origin_key_per_site),
        cmocka_unit_test(test_origin_key_per_session),
        cmocka_unit_test(test_origin_key_empty_namespace),
        cmocka_unit_test(test_origin_key_unlinks_readback),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
