/*
 * test_identity -- CMocka suite for the user identity settings (spec/identity.md).
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <cmocka.h>

#include "anti_fp.h"
#include "identity.h"

static void test_defaults_are_the_anti_fp_identity(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    assert_true(idn_is_default(&c));
    assert_string_equal(idn_user_agent(&c), fp_user_agent());
    char buf[128];
    assert_true(idn_accept_language(&c, buf, sizeof buf) > 0);
    assert_string_equal(buf, fp_accept_language_header());
    idn_primary_language(&c, buf, sizeof buf);
    assert_string_equal(buf, "en-US");
    assert_int_equal(c.geo_mode, IDN_GEO_OFF);
    assert_true(idn_is_default(NULL));
}

static void test_user_agent_validation_is_fail_closed(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    assert_int_equal(idn_set_user_agent(&c, "Mozilla/5.0 Custom"), 0);
    assert_string_equal(idn_user_agent(&c), "Mozilla/5.0 Custom");
    assert_false(idn_is_default(&c));
    assert_int_equal(idn_set_user_agent(&c, "bad\r\nHeader: x"), -1);   /* header injection */
    assert_int_equal(idn_set_user_agent(&c, "tab\there"), -1);
    assert_int_equal(idn_set_user_agent(&c, "caf\xc3\xa9"), -1);        /* non-ASCII */
    assert_int_equal(idn_set_user_agent(&c, "   "), -1);
    char big[IDN_UA_MAX + 8];
    memset(big, 'a', sizeof big - 1);
    big[sizeof big - 1] = '\0';
    assert_int_equal(idn_set_user_agent(&c, big), -1);
    assert_int_equal(idn_set_user_agent(&c, NULL), -1);
    assert_string_equal(idn_user_agent(&c), "Mozilla/5.0 Custom");      /* untouched */
    assert_int_equal(idn_set_user_agent(&c, ""), 0);                    /* reset */
    assert_true(idn_is_default(&c));
}

static void test_languages_build_header_and_primary(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    assert_int_equal(idn_set_languages(&c, "es-AR, es,en"), 0);
    char buf[160];
    idn_accept_language(&c, buf, sizeof buf);
    assert_string_equal(buf, "es-AR,es;q=0.9,en;q=0.8");
    idn_primary_language(&c, buf, sizeof buf);
    assert_string_equal(buf, "es-AR");
    assert_int_equal(idn_set_languages(&c, "en_US"), -1);
    assert_int_equal(idn_set_languages(&c, "e"), -1);
    assert_int_equal(idn_set_languages(&c, "es,,en"), -1);
    assert_int_equal(idn_set_languages(&c, "a1"), -1);
    assert_int_equal(idn_set_languages(&c, "en,fr,de,es,it,pt,ja,ko,zh"), -1);   /* > 8 tags */
    idn_accept_language(&c, buf, sizeof buf);
    assert_string_equal(buf, "es-AR,es;q=0.9,en;q=0.8");                    /* untouched */
    assert_int_equal(idn_set_languages(&c, ""), 0);
    assert_true(idn_is_default(&c));
    assert_int_equal(idn_accept_language(&c, buf, 4), 0);                     /* cap too small */
}

static void test_geo_validation(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    assert_int_equal(idn_set_geo(&c, -34.6037, -58.3816, 50.0), 0);
    assert_int_equal(c.geo_mode, IDN_GEO_FIXED);
    assert_false(idn_is_default(&c));
    assert_int_equal(idn_set_geo(&c, 91.0, 0.0, 10.0), -1);
    assert_int_equal(idn_set_geo(&c, 0.0, 181.0, 10.0), -1);
    assert_int_equal(idn_set_geo(&c, 0.0, 0.0, 0.5), -1);
    assert_int_equal(idn_set_geo(&c, 0.0, 0.0, 200000.0), -1);
    double nan = 0.0 / (volatile double)0.0;
    assert_int_equal(idn_set_geo(&c, nan, 0.0, 10.0), -1);
    assert_true(c.geo_lat < -34.0 && c.geo_lat > -35.0);                     /* untouched */
    idn_clear_geo(&c);
    assert_true(idn_is_default(&c));
}

static void test_serialize_roundtrip_and_escaping(void **state) {
    (void)state;
    idn_config c, d;
    idn_defaults(&c);
    assert_int_equal(idn_set_user_agent(&c, "A|B%C"), 0);
    assert_int_equal(idn_set_languages(&c, "es-AR,en"), 0);
    assert_int_equal(idn_set_geo(&c, 40.25, -3.5, 25.0), 0);
    char s[IDN_SERIAL_MAX];
    size_t n = idn_serialize(&c, s, sizeof s);
    assert_true(n > 0);
    assert_null(strchr(s, '\n'));
    idn_defaults(&d);
    idn_parse(&d, s);
    assert_string_equal(d.user_agent, "A|B%C");
    assert_string_equal(d.languages, "es-AR,en");
    assert_int_equal(d.geo_mode, IDN_GEO_FIXED);
    assert_true(d.geo_lat == 40.25 && d.geo_lon == -3.5 && d.geo_accuracy_m == 25.0);
    assert_int_equal(idn_serialize(&c, s, 8), 0);
    assert_string_equal(s, "");
}

static void test_parse_keeps_valid_fields_and_defaults_the_bad(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    idn_parse(&c, "ua=ok%0D%0Ax|lang=es|geo=999,0,10");
    assert_string_equal(c.user_agent, "");                 /* control chars decoded -> rejected */
    assert_string_equal(c.languages, "es");                /* the valid field survives */
    assert_int_equal(c.geo_mode, IDN_GEO_OFF);
    idn_parse(&c, NULL);
    assert_true(idn_is_default(&c));
    idn_parse(&c, "garbage||=|ua");
    assert_true(idn_is_default(&c));
}

static void test_apply_query(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    unsigned rej = idn_apply_query(&c, "ua=Mozilla%2F5.0+Test&lang=es-AR%2Cen&geo=fixed&lat=-34.6&lon=-58.38&acc=30");
    assert_int_equal(rej, 0);
    assert_string_equal(c.user_agent, "Mozilla/5.0 Test");
    assert_string_equal(c.languages, "es-AR,en");
    assert_int_equal(c.geo_mode, IDN_GEO_FIXED);
    assert_true(c.geo_lat == -34.6 && c.geo_accuracy_m == 30.0);
    rej = idn_apply_query(&c, "ua=bad%0D%0Ax&lang=en_US&lat=95&lon=0&acc=10&geo=fixed");
    assert_int_equal(rej, IDN_REJ_UA | IDN_REJ_LANG | IDN_REJ_GEO);
    assert_string_equal(c.user_agent, "Mozilla/5.0 Test");     /* rejected fields change nothing */
    assert_string_equal(c.languages, "es-AR,en");
    assert_true(c.geo_lat == -34.6);
    /* The page's own form has no mode field: empty coordinates = off, all three = fixed. */
    assert_int_equal(idn_apply_query(&c, "ua=&lang=&lat=1.5&lon=-2.5&acc=40"), 0);
    assert_int_equal(c.geo_mode, IDN_GEO_FIXED);
    assert_true(c.geo_lat == 1.5 && c.geo_lon == -2.5 && c.geo_accuracy_m == 40.0);
    assert_string_equal(c.user_agent, "");
    assert_int_equal(idn_apply_query(&c, "lat=3&lon=&acc="), IDN_REJ_GEO);      /* partial: refused */
    assert_true(c.geo_lat == 1.5);
    assert_int_equal(idn_apply_query(&c, "lat=&lon=&acc="), 0);                /* all empty: off */
    assert_int_equal(c.geo_mode, IDN_GEO_OFF);
    assert_int_equal(idn_apply_query(&c, "geo=off"), 0);
    assert_int_equal(c.geo_mode, IDN_GEO_OFF);
    assert_int_equal(idn_apply_query(&c, "reset=1"), 0);
    assert_true(idn_is_default(&c));
    assert_int_equal(idn_apply_query(&c, "unknown=1&=&&x"), 0);
    assert_true(idn_is_default(&c));
    assert_int_equal(idn_apply_query(NULL, "ua=x"), 0);
}

static void test_page_escapes_user_values_and_states_unavailable_apis(void **state) {
    (void)state;
    idn_config c;
    idn_defaults(&c);
    assert_int_equal(idn_set_user_agent(&c, "<script>alert(1)</script>\"'&"), 0);
    char page[IDN_PAGE_MAX];
    size_t n = idn_render_page(&c, page, sizeof page);
    assert_true(n > 0 && n == strlen(page));
    assert_null(strstr(page, "<script>"));
    assert_non_null(strstr(page, "&lt;script&gt;"));
    assert_non_null(strstr(page, "&quot;"));
    assert_non_null(strstr(page, "<form"));
    assert_non_null(strstr(page, "name=\"ua\""));
    assert_non_null(strstr(page, "name=\"lat\""));
    assert_null(strstr(page, "name=\"geo\""));                    /* no mode field: coordinates decide */
    assert_non_null(strstr(page, "WebGL"));
    assert_non_null(strstr(page, "Service Workers"));
    assert_non_null(strstr(page, "not available"));
    assert_int_equal(idn_render_page(&c, page, 64), 0);
    assert_string_equal(page, "");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_defaults_are_the_anti_fp_identity),
        cmocka_unit_test(test_user_agent_validation_is_fail_closed),
        cmocka_unit_test(test_languages_build_header_and_primary),
        cmocka_unit_test(test_geo_validation),
        cmocka_unit_test(test_serialize_roundtrip_and_escaping),
        cmocka_unit_test(test_parse_keeps_valid_fields_and_defaults_the_bad),
        cmocka_unit_test(test_apply_query),
        cmocka_unit_test(test_page_escapes_user_values_and_states_unavailable_apis),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
