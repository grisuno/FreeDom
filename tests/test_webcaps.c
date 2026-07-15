/*
 * test_webcaps — CMocka suite for the pure webcaps capability model (M0.1).
 *
 * Covers the per-host derivation matrix (leak-free vs privacy-sensitive gating),
 * reader mode winning, JSP_ON-without-allowlist NOT being trust, the rdp_caps
 * projection, and the headless operator-flag path.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "webcaps.h"

/* Convenience: an input with the given trust signals, no reader, no user toggles. */
static wc_input mk(jsp_mode mode, int in_js, int in_allow) {
    wc_input in;
    memset(&in, 0, sizeof in);
    in.js_mode = mode;
    in.host_in_js = in_js;
    in.host_in_allow = in_allow;
    return in;
}

static void test_safe_is_all_off(void **state) {
    (void)state;
    wc_caps c = wc_safe();
    wc_caps zero;
    memset(&zero, 0, sizeof zero);
    assert_memory_equal(&c, &zero, sizeof c);
}

/* A fully trusted host (allow.conf AND js.conf, allowlist JS mode) gets everything. */
static void test_trusted_host_gets_all_caps(void **state) {
    (void)state;
    wc_caps c = wc_derive(mk(JSP_ALLOWLIST, 1, 1));
    assert_true(c.js);
    assert_true(c.css);
    assert_true(c.images);
    assert_true(c.net);
    assert_true(c.cookies);
    assert_true(c.persist);
    assert_true(c.readback);
    assert_true(c.gpu);
    assert_true(c.sw);
    assert_true(c.rtc);
}

/* Presentation-trust: allow.conf ALONE (not in js.conf) unlocks author CSS + images
 * but NEVER the privacy-sensitive caps (net/cookies/persist/...). JS stays off since
 * the host is not on js.conf under the default allowlist mode. */
static void test_present_trust_css_images_only(void **state) {
    (void)state;
    wc_caps c = wc_derive(mk(JSP_ALLOWLIST, 0, 1));
    assert_false(c.js);      /* not on js.conf */
    assert_true(c.css);      /* presentation-trust */
    assert_true(c.images);   /* presentation-trust */
    assert_false(c.net);     /* privacy: needs allow AND js */
    assert_false(c.cookies);
    assert_false(c.persist);
    assert_false(c.readback);
    assert_false(c.gpu);
    assert_false(c.sw);
    assert_false(c.rtc);
}

/* A host on js.conf but NOT allow.conf: JS runs (leak-free) but no presentation-trust
 * and no privacy caps (both need allow.conf). css/images stay off (no user toggle). */
static void test_js_without_allow_is_not_trust(void **state) {
    (void)state;
    wc_caps c = wc_derive(mk(JSP_ALLOWLIST, 1, 0));
    assert_true(c.js);
    assert_false(c.css);
    assert_false(c.images);
    assert_false(c.net);
    assert_false(c.persist);
}

/* Global JSP_ON enables JS everywhere, but is NOT trust: a host absent from
 * allow.conf gets JS yet no network / privacy caps. */
static void test_jspon_alone_is_not_trust(void **state) {
    (void)state;
    wc_caps c = wc_derive(mk(JSP_ON, 0, 0));
    assert_true(c.js);       /* JSP_ON runs JS for every host */
    assert_false(c.css);     /* not allowlisted, no user toggle */
    assert_false(c.images);
    assert_false(c.net);     /* JSP_ON is not allow.conf trust */
    assert_false(c.gpu);
    /* But JSP_ON + allow.conf IS trust. */
    wc_caps t = wc_derive(mk(JSP_ON, 0, 1));
    assert_true(t.net);
    assert_true(t.persist);
}

/* User session toggles turn on the leak-free presentation caps without any trust. */
static void test_user_toggles_grant_leakfree(void **state) {
    (void)state;
    wc_input in = mk(JSP_OFF, 0, 0);
    in.user_css = 1;
    in.user_images = 1;
    wc_caps c = wc_derive(in);
    assert_true(c.css);
    assert_true(c.images);
    assert_false(c.js);      /* JS off (no toggle path here) */
    assert_false(c.net);     /* no trust */
}

/* Reader mode wins: css and images are forced off even for a fully trusted host,
 * while the privacy caps (driven by trust, not presentation) are unaffected. */
static void test_reader_forces_css_images_off(void **state) {
    (void)state;
    wc_input in = mk(JSP_ALLOWLIST, 1, 1);
    in.reader = 1;
    wc_caps c = wc_derive(in);
    assert_false(c.css);
    assert_false(c.images);
    assert_true(c.js);       /* execution is not presentation */
    assert_true(c.net);      /* trust unaffected by reader */
    assert_true(c.persist);
}

/* Fail-closed: an out-of-range mode never enables JS (delegates to jsp_enabled). */
static void test_bad_mode_fails_closed(void **state) {
    (void)state;
    wc_caps c = wc_derive(mk((jsp_mode)999, 1, 1));
    assert_false(c.js);
    /* allow.conf still grants presentation-trust independent of JS. */
    assert_true(c.css);
    /* but trust needs js_enabled, which is false here, so no network. */
    assert_false(c.net);
}

/* The rdp_caps projection carries exactly the leak-free triple. */
static void test_render_caps_projection(void **state) {
    (void)state;
    wc_caps c = wc_derive(mk(JSP_ALLOWLIST, 1, 1));
    rdp_caps r = wc_render_caps(c);
    assert_true(r.images);
    assert_true(r.css);
    assert_true(r.js);
    /* Safe caps project to all-off. */
    rdp_caps z = wc_render_caps(wc_safe());
    assert_false(z.images);
    assert_false(z.css);
    assert_false(z.js);
}

/* Headless operator-flag path: --js=on is the trust signal; flags are orthogonal. */
static void test_from_flags_headless(void **state) {
    (void)state;
    /* --js=on only. */
    wc_caps j = wc_from_flags(true, false, false);
    assert_true(j.js);
    assert_true(j.net);
    assert_true(j.cookies);
    assert_true(j.persist);
    assert_false(j.css);
    assert_false(j.images);
    /* --author-css only: presentation on, no network. */
    wc_caps c = wc_from_flags(false, true, false);
    assert_true(c.css);
    assert_false(c.js);
    assert_false(c.net);
    /* --images only. */
    wc_caps i = wc_from_flags(false, false, true);
    assert_true(i.images);
    assert_false(i.net);
    /* nothing: all off. */
    wc_caps n = wc_from_flags(false, false, false);
    rdp_caps zero;
    memset(&zero, 0, sizeof zero);
    assert_memory_equal(&(rdp_caps){0}, &zero, sizeof zero);
    assert_false(n.js);
    assert_false(n.net);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_safe_is_all_off),
        cmocka_unit_test(test_trusted_host_gets_all_caps),
        cmocka_unit_test(test_present_trust_css_images_only),
        cmocka_unit_test(test_js_without_allow_is_not_trust),
        cmocka_unit_test(test_jspon_alone_is_not_trust),
        cmocka_unit_test(test_user_toggles_grant_leakfree),
        cmocka_unit_test(test_reader_forces_css_images_off),
        cmocka_unit_test(test_bad_mode_fails_closed),
        cmocka_unit_test(test_render_caps_projection),
        cmocka_unit_test(test_from_flags_headless),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
