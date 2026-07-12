/*
 * test_tls_impersonate — CMocka suite for the pure TLS-impersonation surface.
 *
 * Two pieces (spec/tls_impersonate.md): the TRIPLE opt-in gate
 * (ti_should_impersonate) and the length-prefixed, fail-closed IPC codec
 * (ti_encode/decode_req/resp). No I/O; the BoringSSL handshake is out of scope here.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include <cmocka.h>

#include "tls_impersonate.h"

/* --- the triple gate: 1 IFF all three signals set (fail-closed otherwise) --- */

static void test_gate_requires_all_three_signals(void **state) {
    (void)state;
    assert_int_equal(ti_should_impersonate(1, 1, 1), 1);
    /* any single missing signal fails closed */
    assert_int_equal(ti_should_impersonate(0, 1, 1), 0);
    assert_int_equal(ti_should_impersonate(1, 0, 1), 0);
    assert_int_equal(ti_should_impersonate(1, 1, 0), 0);
    /* two or three missing */
    assert_int_equal(ti_should_impersonate(1, 0, 0), 0);
    assert_int_equal(ti_should_impersonate(0, 0, 0), 0);
    /* non-1 truthy values still gate correctly (normalized booleans) */
    assert_int_equal(ti_should_impersonate(7, 3, 9), 1);
    assert_int_equal(ti_should_impersonate(7, 3, 0), 0);
}

/* --- request codec round-trip --- */

static void test_encode_decode_req_roundtrip(void **state) {
    (void)state;
    const uint8_t body[] = "user=x&pw=y";
    ti_req in = {
        .url = "https://accounts.google.com/signin",
        .method = "POST",
        .headers = "Accept: text/html\r\nCookie: a=b",
        .body = body,
        .body_len = sizeof body - 1,
        .profile = TI_PROFILE_CHROME_CLASSIC,
    };
    uint8_t buf[4096];
    size_t n = ti_encode_req(&in, buf, sizeof buf);
    assert_true(n > 0);

    ti_req out;
    assert_int_equal(ti_decode_req(buf, n, &out), 0);
    assert_string_equal(out.url, in.url);
    assert_string_equal(out.method, in.method);
    assert_string_equal(out.headers, in.headers);
    assert_int_equal((int)out.body_len, (int)in.body_len);
    assert_memory_equal(out.body, in.body, in.body_len);
    assert_int_equal(out.profile, in.profile);
    ti_req_free(&out);
}

static void test_encode_decode_req_empty_body(void **state) {
    (void)state;
    ti_req in = {
        .url = "https://youtube.com/",
        .method = "GET",
        .headers = "",
        .body = NULL,
        .body_len = 0,
        .profile = TI_PROFILE_CHROME_CLASSIC,
    };
    uint8_t buf[1024];
    size_t n = ti_encode_req(&in, buf, sizeof buf);
    assert_true(n > 0);
    ti_req out;
    assert_int_equal(ti_decode_req(buf, n, &out), 0);
    assert_string_equal(out.url, in.url);
    assert_string_equal(out.method, in.method);
    assert_string_equal(out.headers, "");
    assert_int_equal((int)out.body_len, 0);
    ti_req_free(&out);
}

/* --- response codec round-trip (carries the chain + negotiated group) --- */

static void test_encode_decode_resp_roundtrip(void **state) {
    (void)state;
    const uint8_t bodyb[] = "<html>hi</html>";
    const uint8_t chain[] = { 0x30, 0x82, 0x01, 0x02, 0xFF, 0x00, 0xAB };
    ti_resp in = {
        .status = 200,
        .headers = (char *)"content-type: text/html\r\nserver: gws",
        .body = (uint8_t *)bodyb,
        .body_len = sizeof bodyb - 1,
        .peer_chain_der = (uint8_t *)chain,
        .peer_chain_len = sizeof chain,
        .tls_version = 0x0304, /* TLS 1.3 marker (opaque here) */
    };
    strncpy(in.negotiated_group, "x25519", sizeof in.negotiated_group - 1);

    uint8_t buf[4096];
    size_t n = ti_encode_resp(&in, buf, sizeof buf);
    assert_true(n > 0);

    ti_resp out;
    assert_int_equal(ti_decode_resp(buf, n, &out), 0);
    assert_int_equal((int)out.status, 200);
    assert_string_equal(out.headers, in.headers);
    assert_int_equal((int)out.body_len, (int)in.body_len);
    assert_memory_equal(out.body, bodyb, in.body_len);
    assert_int_equal((int)out.peer_chain_len, (int)sizeof chain);
    assert_memory_equal(out.peer_chain_der, chain, sizeof chain);
    assert_string_equal(out.negotiated_group, "x25519");
    assert_int_equal((int)out.tls_version, 0x0304);
    ti_resp_free(&out);
}

static void test_resp_no_chain_ok(void **state) {
    (void)state;
    ti_resp in = {
        .status = 0, /* transport failure: no body, no chain */
        .headers = (char *)"",
        .body = NULL, .body_len = 0,
        .peer_chain_der = NULL, .peer_chain_len = 0,
        .tls_version = 0,
    };
    in.negotiated_group[0] = '\0';
    uint8_t buf[256];
    size_t n = ti_encode_resp(&in, buf, sizeof buf);
    assert_true(n > 0);
    ti_resp out;
    assert_int_equal(ti_decode_resp(buf, n, &out), 0);
    assert_int_equal((int)out.status, 0);
    assert_null(out.peer_chain_der);
    assert_int_equal((int)out.peer_chain_len, 0);
    ti_resp_free(&out);
}

/* --- fail-closed: truncated / malformed frames are rejected, never overrun --- */

static void test_decode_rejects_truncated(void **state) {
    (void)state;
    ti_req in = {
        .url = "https://facebook.com/", .method = "GET", .headers = "h: v",
        .body = NULL, .body_len = 0, .profile = TI_PROFILE_CHROME_CLASSIC,
    };
    uint8_t buf[1024];
    size_t n = ti_encode_req(&in, buf, sizeof buf);
    assert_true(n > 2);
    ti_req out;
    /* every proper prefix must be rejected (no partial accept, no read past end) */
    for (size_t k = 0; k < n; ++k) {
        assert_true(ti_decode_req(buf, k, &out) < 0);
    }
    /* the full frame still decodes */
    assert_int_equal(ti_decode_req(buf, n, &out), 0);
    ti_req_free(&out);
}

static void test_decode_rejects_bad_magic(void **state) {
    (void)state;
    ti_req in = {
        .url = "https://x.com/", .method = "GET", .headers = "",
        .body = NULL, .body_len = 0, .profile = TI_PROFILE_CHROME_CLASSIC,
    };
    uint8_t buf[512];
    size_t n = ti_encode_req(&in, buf, sizeof buf);
    assert_true(n > 4);
    buf[0] ^= 0xFF; /* corrupt the magic */
    ti_req out;
    assert_true(ti_decode_req(buf, n, &out) < 0);
}

static void test_decode_rejects_overlong_field(void **state) {
    (void)state;
    /* Hand-craft a frame whose URL length prefix claims more than TI_MAX_URL. */
    uint8_t buf[64];
    size_t o = 0;
    buf[o++] = 0x50; buf[o++] = 0x4D; buf[o++] = 0x49; buf[o++] = 0x54; /* magic LE */
    buf[o++] = TI_PROFILE_CHROME_CLASSIC;
    /* url length = TI_MAX_URL + 1 (little-endian u32) */
    uint32_t bad = TI_MAX_URL + 1u;
    buf[o++] = (uint8_t)(bad); buf[o++] = (uint8_t)(bad >> 8);
    buf[o++] = (uint8_t)(bad >> 16); buf[o++] = (uint8_t)(bad >> 24);
    ti_req out;
    assert_true(ti_decode_req(buf, o, &out) < 0);
}

static void test_encode_fails_when_no_room(void **state) {
    (void)state;
    ti_req in = {
        .url = "https://averylongurl.example.com/path/that/does/not/fit",
        .method = "GET", .headers = "", .body = NULL, .body_len = 0,
        .profile = TI_PROFILE_CHROME_CLASSIC,
    };
    uint8_t tiny[8];
    assert_int_equal((int)ti_encode_req(&in, tiny, sizeof tiny), 0);
}

static void test_encode_rejects_oversize_url(void **state) {
    (void)state;
    char *huge = malloc(TI_MAX_URL + 10);
    assert_non_null(huge);
    memset(huge, 'a', TI_MAX_URL + 8);
    huge[TI_MAX_URL + 8] = '\0';
    ti_req in = {
        .url = huge, .method = "GET", .headers = "", .body = NULL, .body_len = 0,
        .profile = TI_PROFILE_CHROME_CLASSIC,
    };
    uint8_t buf[TI_MAX_URL + 64];
    assert_int_equal((int)ti_encode_req(&in, buf, sizeof buf), 0);
    free(huge);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_gate_requires_all_three_signals),
        cmocka_unit_test(test_encode_decode_req_roundtrip),
        cmocka_unit_test(test_encode_decode_req_empty_body),
        cmocka_unit_test(test_encode_decode_resp_roundtrip),
        cmocka_unit_test(test_resp_no_chain_ok),
        cmocka_unit_test(test_decode_rejects_truncated),
        cmocka_unit_test(test_decode_rejects_bad_magic),
        cmocka_unit_test(test_decode_rejects_overlong_field),
        cmocka_unit_test(test_encode_fails_when_no_room),
        cmocka_unit_test(test_encode_rejects_oversize_url),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
