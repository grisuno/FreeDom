/*
 * TDD suite for render_policy — render capabilities gate + image load decision.
 *
 * Pure policy logic: no I/O. Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "render_policy.h"

/* --- rdp_caps_safe --- */

static void test_caps_safe_is_all_off(void **state) {
    (void)state;
    rdp_caps c = rdp_caps_safe();
    assert_false(c.images);
    assert_false(c.css);
    assert_false(c.js);
}

static void test_caps_zero_value_is_safe(void **state) {
    (void)state;
    /* The zero value of the struct must equal the safe baseline: insecure config
     * is not representable as a default. */
    rdp_caps z = {0};
    rdp_caps s = rdp_caps_safe();
    assert_memory_equal(&z, &s, sizeof(rdp_caps));
}

/* --- rdp_is_tracking_pixel --- */

static void test_tracking_pixel_tiny(void **state) {
    (void)state;
    assert_int_equal(rdp_is_tracking_pixel(1, 1), 1);
    assert_int_equal(rdp_is_tracking_pixel(2, 2), 1);
    assert_int_equal(rdp_is_tracking_pixel(1, 2), 1);
    assert_int_equal(rdp_is_tracking_pixel(2, 1), 1);
}

static void test_tracking_pixel_zero_area(void **state) {
    (void)state;
    assert_int_equal(rdp_is_tracking_pixel(0, 0), 1);
    assert_int_equal(rdp_is_tracking_pixel(0, 500), 1);
    assert_int_equal(rdp_is_tracking_pixel(500, 0), 1);
}

static void test_tracking_pixel_normal(void **state) {
    (void)state;
    assert_int_equal(rdp_is_tracking_pixel(16, 16), 0);
    assert_int_equal(rdp_is_tracking_pixel(3, 3), 0);
    /* Only one dim tiny but the other large: a thin image with known size is not
     * classified as a tracker by the size heuristic. */
    assert_int_equal(rdp_is_tracking_pixel(1, 300), 0);
    assert_int_equal(rdp_is_tracking_pixel(800, 600), 0);
}

static void test_tracking_pixel_unknown(void **state) {
    (void)state;
    /* Negative = unknown: cannot classify, do not block on this basis. */
    assert_int_equal(rdp_is_tracking_pixel(-1, -1), 0);
    assert_int_equal(rdp_is_tracking_pixel(-1, 1), 0);
    assert_int_equal(rdp_is_tracking_pixel(1, -1), 0);
}

/* --- rdp_image_decision: capability gate --- */

static void test_image_disabled_by_default(void **state) {
    (void)state;
    rdp_caps off = rdp_caps_safe();
    /* Images off: even a perfectly valid same-site image is blocked, and the URL
     * is not even consulted (a bogus URL still yields BLOCK_DISABLED). */
    assert_int_equal(
        rdp_image_decision(off, "https://example.com/", "https://example.com/a.png", 64, 64),
        RDP_IMG_BLOCK_DISABLED);
    assert_int_equal(
        rdp_image_decision(off, "https://example.com/", "not-a-url", -1, -1),
        RDP_IMG_BLOCK_DISABLED);
    assert_int_equal(
        rdp_image_decision(off, NULL, NULL, -1, -1),
        RDP_IMG_BLOCK_DISABLED);
}

/* --- rdp_image_decision: images enabled --- */

static rdp_caps caps_images_on(void) {
    rdp_caps c = rdp_caps_safe();
    c.images = true;
    return c;
}

static void test_image_allow_same_site(void **state) {
    (void)state;
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "https://example.com/logo.png", 200, 80),
        RDP_IMG_ALLOW);
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://www.example.com/",
                           "https://cdn.example.com/a.jpg", -1, -1),
        RDP_IMG_ALLOW);
}

static void test_image_allow_cross_site_when_enabled(void **state) {
    (void)state;
    /* Chosen posture ("load all but trackers"): a cross-site image is allowed
     * once the user opts in. This is the deliberate difference from rp_evaluate,
     * which blocks third parties for other subresources. */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "https://images.othercdn.net/p.jpg", 300, 250),
        RDP_IMG_ALLOW);
}

static void test_image_block_tracker(void **state) {
    (void)state;
    /* A 1x1 cross-site image is the canonical tracking pixel: blocked even when
     * images are enabled. */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "https://tracker.net/p.gif", 1, 1),
        RDP_IMG_BLOCK_TRACKER);
    /* Same-site tracking beacon is blocked too. */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "https://example.com/beacon.gif", 1, 1),
        RDP_IMG_BLOCK_TRACKER);
}

static void test_image_block_scheme(void **state) {
    (void)state;
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "http://example.com/a.png", 64, 64),
        RDP_IMG_BLOCK_SCHEME);
}

static void test_image_block_invalid(void **state) {
    (void)state;
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "https:///a.png", 64, 64),
        RDP_IMG_BLOCK_INVALID);
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "javascript:alert(1)", 64, 64),
        RDP_IMG_BLOCK_INVALID);
    /* Top-level not https: fail closed even for a same-site-looking image. */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "http://example.com/",
                           "https://example.com/a.png", 64, 64),
        RDP_IMG_BLOCK_INVALID);
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/", NULL, 64, 64),
        RDP_IMG_BLOCK_INVALID);
}

/* A data: URI embeds its bytes inline: no socket opens, so it skips the https/
 * host/tracker checks above but still needs caps.images. See spec/data_url.md. */
static void test_image_allow_data_url(void **state) {
    (void)state;
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "data:image/png;base64,QQ==", 64, 64),
        RDP_IMG_ALLOW);
    /* Even a "tracking pixel"-sized data: URI is allowed: no request, no
     * correlation possible. */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "data:image/png;base64,QQ==", 1, 1),
        RDP_IMG_ALLOW);
    /* Works with no top-level URL at all (e.g. a bare fragment being tested). */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), NULL,
                           "data:image/gif;base64,QQ==", 64, 64),
        RDP_IMG_ALLOW);
}

static void test_image_data_url_disabled_by_default(void **state) {
    (void)state;
    assert_int_equal(
        rdp_image_decision(rdp_caps_safe(), "https://example.com/",
                           "data:image/png;base64,QQ==", 64, 64),
        RDP_IMG_BLOCK_DISABLED);
}

static void test_image_data_url_malformed_is_invalid(void **state) {
    (void)state;
    /* Percent-encoded (no ;base64 flag) or otherwise malformed data: URIs fail
     * closed rather than falling through to the https scheme check. */
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "data:image/svg+xml,<svg/>", 64, 64),
        RDP_IMG_BLOCK_INVALID);
    assert_int_equal(
        rdp_image_decision(caps_images_on(), "https://example.com/",
                           "data:image/png;base64", 64, 64),
        RDP_IMG_BLOCK_INVALID);
}

/* Disabled capability beats every other reason: a tracker URL with images off is
 * reported as DISABLED, not TRACKER (the gate short-circuits first). */
static void test_image_disabled_precedence(void **state) {
    (void)state;
    rdp_caps off = rdp_caps_safe();
    assert_int_equal(
        rdp_image_decision(off, "https://example.com/", "https://tracker.net/p.gif", 1, 1),
        RDP_IMG_BLOCK_DISABLED);
}

/* --- reason / warning strings --- */

static void test_img_reason_total_and_stable(void **state) {
    (void)state;
    const rdp_img_decision all[] = {
        RDP_IMG_ALLOW, RDP_IMG_BLOCK_DISABLED, RDP_IMG_BLOCK_INVALID,
        RDP_IMG_BLOCK_SCHEME, RDP_IMG_BLOCK_TRACKER,
    };
    for (size_t i = 0; i < sizeof all / sizeof all[0]; ++i) {
        const char *r = rdp_img_reason(all[i]);
        assert_non_null(r);
        assert_true(strlen(r) > 0);
    }
    /* Unknown enum value is total: never NULL. */
    assert_string_equal(rdp_img_reason((rdp_img_decision)999), "unknown");
}

static void test_images_warning_present(void **state) {
    (void)state;
    const char *w = rdp_images_warning();
    assert_non_null(w);
    assert_true(strlen(w) > 0);
    /* The warning must actually mention tracking, the whole point of the gate. */
    assert_non_null(strstr(w, "track"));
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_caps_safe_is_all_off),
        cmocka_unit_test(test_caps_zero_value_is_safe),
        cmocka_unit_test(test_tracking_pixel_tiny),
        cmocka_unit_test(test_tracking_pixel_zero_area),
        cmocka_unit_test(test_tracking_pixel_normal),
        cmocka_unit_test(test_tracking_pixel_unknown),
        cmocka_unit_test(test_image_disabled_by_default),
        cmocka_unit_test(test_image_allow_same_site),
        cmocka_unit_test(test_image_allow_cross_site_when_enabled),
        cmocka_unit_test(test_image_block_tracker),
        cmocka_unit_test(test_image_block_scheme),
        cmocka_unit_test(test_image_block_invalid),
        cmocka_unit_test(test_image_allow_data_url),
        cmocka_unit_test(test_image_data_url_disabled_by_default),
        cmocka_unit_test(test_image_data_url_malformed_is_invalid),
        cmocka_unit_test(test_image_disabled_precedence),
        cmocka_unit_test(test_img_reason_total_and_stable),
        cmocka_unit_test(test_images_warning_present),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
