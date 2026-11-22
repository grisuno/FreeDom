/* Suite for site_panel (spec/site_panel.md). */
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <math.h>
#include <string.h>

#include "site_panel.h"

static sp_facts pq_facts(void) {
    sp_facts f;
    memset(&f, 0, sizeof f);
    f.url = "https://user@example.org:8443/x?y#z";
    f.identity = CHL_ID_PQ;
    f.tls_version = "TLSv1.3";
    f.group = "X25519MLKEM768";
    f.route = SP_ROUTE_DIRECT;
    f.listable = 1;
    return f;
}

static const sp_row *row(const sp_panel *p, const char *label) {
    for (int i = 0; i < p->row_count; ++i)
        if (strcmp(p->rows[i].label, label) == 0) return &p->rows[i];
    return NULL;
}

static void test_rejects_null(void **state) {
    (void)state;
    sp_panel p;
    sp_facts f = pq_facts();
    assert_int_equal(sp_build(NULL, &p), SP_EINVAL);
    assert_int_equal(sp_build(&f, NULL), SP_EINVAL);
}

static void test_pq_page(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_string_equal(p.title, "example.org");
    assert_int_equal(p.tone, SP_TONE_GOOD);
    assert_string_equal(p.headline, chl_identity_label(CHL_ID_PQ));
    assert_non_null(row(&p, "Connection"));
    assert_string_equal(row(&p, "Connection")->value, "TLSv1.3 / X25519MLKEM768");
    assert_string_equal(row(&p, "Key exchange")->value, "Hybrid post-quantum (ML-KEM + classical)");
    assert_int_equal(row(&p, "Key exchange")->tone, SP_TONE_GOOD);
    assert_string_equal(row(&p, "Certificate")->value, "Verified");
    assert_string_equal(row(&p, "Route")->value, "Direct");
    assert_string_equal(row(&p, "Third parties")->value, "Blocked");
    assert_string_equal(row(&p, "JavaScript")->value, "Off");
    assert_string_equal(row(&p, "Cookies")->value, "None");
    assert_int_equal(p.action_count, 2);
    assert_int_equal(p.actions[0], SP_ACT_ALLOW);
    assert_int_equal(p.actions[1], SP_ACT_JS);
}

static void test_trusted_site_offers_nothing(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    f.allowlisted = f.js_site = f.trusted = 1;
    f.route = SP_ROUTE_TOR;
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal(p.action_count, 0);
    assert_string_equal(row(&p, "Third parties")->value, "Allowed (site trusted)");
    assert_string_equal(row(&p, "JavaScript")->value, "On for this site");
    assert_string_equal(row(&p, "Cookies")->value, "Session only, in memory");
    assert_string_equal(row(&p, "Route")->value, "Tor (SOCKS5h, remote DNS)");
}

static void test_unlistable_host_offers_nothing(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    f.url = "https://localhost:8443/";
    f.listable = 0;   /* hostedit refuses a single-label host: a button would do nothing */
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal(p.action_count, 0);
    assert_string_equal(p.title, "localhost");
}

static void test_unknown_never_claims_pq(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    f.identity = CHL_ID_UNKNOWN;
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal(p.tone, SP_TONE_WARN);
    assert_null(row(&p, "Key exchange"));
    assert_string_equal(row(&p, "Connection")->value, "Unknown: not delivered by a checked fetch");
    assert_null(row(&p, "Certificate"));
}

static void test_classical_weak_unverified(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    f.group = "X25519";
    f.identity = CHL_ID_CLASSICAL;
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal(p.tone, SP_TONE_WARN);
    assert_string_equal(row(&p, "Key exchange")->value, "Classical: not quantum-resistant");
    assert_int_equal(row(&p, "Key exchange")->tone, SP_TONE_WARN);

    f.identity = CHL_ID_WEAK;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_string_equal(row(&p, "Certificate")->value, "Verified; weak crypto allowed by allow.conf");

    f.identity = CHL_ID_UNVERIFIED;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal(p.tone, SP_TONE_BAD);
    assert_string_equal(row(&p, "Certificate")->value, "NOT verified (--insecure)");
    assert_int_equal(row(&p, "Certificate")->tone, SP_TONE_BAD);

    /* A PQ group with a non-PQ identity is still not claimed hybrid. */
    f.group = "X25519MLKEM768";
    f.identity = CHL_ID_CLASSICAL;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_string_equal(row(&p, "Key exchange")->value, "Classical: not quantum-resistant");
}

static void test_local_and_internal(void **state) {
    (void)state;
    sp_facts f;
    memset(&f, 0, sizeof f);
    f.url = "file:///tmp/a.html";
    f.identity = CHL_ID_LOCAL;
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_string_equal(p.title, "Local file");
    assert_string_equal(row(&p, "Connection")->value, "No network");
    assert_null(row(&p, "Route"));
    assert_null(row(&p, "Certificate"));
    assert_int_equal(p.action_count, 0);

    f.url = NULL;
    f.identity = CHL_ID_INTERNAL;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_string_equal(p.title, "Freedom");
    assert_int_equal(p.tone, SP_TONE_NEUTRAL);
    assert_int_equal(p.action_count, 0);
}

static void test_insecure_http(void **state) {
    (void)state;
    sp_facts f;
    memset(&f, 0, sizeof f);
    f.url = "http://plain.example/";
    f.identity = CHL_ID_INSECURE;
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal(p.tone, SP_TONE_BAD);
    assert_string_equal(row(&p, "Connection")->value, "Not encrypted");
    assert_int_equal(row(&p, "Connection")->tone, SP_TONE_BAD);
    assert_null(row(&p, "Certificate"));
}

static void test_hostile_host_sanitized(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    f.url = "https://ev\x01il\x1b[31m.example\xc3\xa9/x";
    sp_panel p;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    for (const char *c = p.title; *c != '\0'; ++c)
        assert_true(*c >= 0x20 && *c < 0x7f);
    assert_non_null(strchr(p.title, '?'));

    char longu[300] = "https://";
    memset(longu + 8, 'a', 200);
    longu[208] = '\0';
    f.url = longu;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    assert_int_equal((int)strlen(p.title), SP_HOST_MAX + 3);
    assert_string_equal(p.title + SP_HOST_MAX, "...");

    f.group = "X\nY\x7f";
    assert_int_equal(sp_build(&f, &p), SP_OK);
    for (int i = 0; i < p.row_count; ++i)
        for (const char *c = p.rows[i].value; *c != '\0'; ++c)
            assert_true(*c >= 0x20 && *c < 0x7f);
}

static void test_layout_fits_and_hits(void **state) {
    (void)state;
    sp_facts f = pq_facts();
    sp_panel p;
    sp_geom g;
    assert_int_equal(sp_build(&f, &p), SP_OK);
    chl_rect anchor = { 120.0, 44.0, 30.0, 28.0 };
    assert_int_equal(sp_layout(&p, anchor, 1300.0, 900.0, &g), SP_OK);
    assert_true(fabs(g.panel.x - anchor.x) < 1e-9);
    assert_true(fabs(g.panel.y - (anchor.y + anchor.h + SP_GAP)) < 1e-9);
    assert_int_equal(g.action_count, 2);
    for (int i = 0; i < g.action_count; ++i) {
        chl_rect a = g.action[i];
        assert_true(a.x >= g.panel.x && a.x + a.w <= g.panel.x + g.panel.w + 1e-9);
        assert_true(a.y >= g.panel.y && a.y + a.h <= g.panel.y + g.panel.h + 1e-9);
        assert_int_equal(sp_hit(&g, a.x + a.w / 2.0, a.y + a.h / 2.0), SP_HIT_ACTION0 + i);
    }
    assert_int_equal(sp_hit(&g, g.panel.x + 4.0, g.panel.y + 4.0), SP_HIT_PANEL);
    assert_int_equal(sp_hit(&g, g.panel.x - 1.0, g.panel.y), SP_HIT_OUTSIDE);
    assert_int_equal(sp_hit(NULL, 0.0, 0.0), SP_HIT_OUTSIDE);

    /* Narrow window: the panel stays inside. */
    chl_rect a2 = { 250.0, 44.0, 30.0, 28.0 };
    assert_int_equal(sp_layout(&p, a2, 300.0, 600.0, &g), SP_OK);
    assert_true(g.panel.x >= SP_MARGIN - 1e-9);
    assert_true(g.panel.x + g.panel.w <= 300.0 - SP_MARGIN + 1e-9);

    /* Hostile sizes stay finite. */
    assert_int_equal(sp_layout(&p, a2, NAN, -5.0, &g), SP_OK);
    assert_true(isfinite(g.panel.x) && isfinite(g.panel.w) && g.panel.w >= 0.0);
    assert_int_equal(sp_layout(NULL, a2, 100, 100, &g), SP_EINVAL);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_rejects_null),
        cmocka_unit_test(test_pq_page),
        cmocka_unit_test(test_trusted_site_offers_nothing),
        cmocka_unit_test(test_unknown_never_claims_pq),
        cmocka_unit_test(test_unlistable_host_offers_nothing),
        cmocka_unit_test(test_classical_weak_unverified),
        cmocka_unit_test(test_local_and_internal),
        cmocka_unit_test(test_insecure_http),
        cmocka_unit_test(test_hostile_host_sanitized),
        cmocka_unit_test(test_layout_fits_and_hits),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
