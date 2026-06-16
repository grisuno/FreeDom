/*
 * TDD suite for local_store (Hito 5 - Zero Knowledge: encrypted local state).
 *
 * RED state until src/local_store.c exists: this links and fails on purpose.
 *
 * Build: make test   (cmocka + libcrypto)   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "local_store.h"

static const uint8_t KEY[LS_KEY_LEN] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

static const char PT[] = "freedom: secret bookmark https://example.onion";

/* --- raw-key round trip, both AEADs --- */

static void roundtrip_raw(ls_aead aead) {
    uint8_t *blob = NULL, *out = NULL;
    size_t blob_len = 0, out_len = 0;

    assert_int_equal(
        ls_seal(KEY, aead, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len),
        LS_OK);
    assert_non_null(blob);
    assert_int_equal(blob_len, LS_OVERHEAD + (sizeof PT - 1));

    assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_OK);
    assert_int_equal(out_len, sizeof PT - 1);
    assert_memory_equal(out, PT, sizeof PT - 1);

    ls_free(blob, blob_len);
    ls_free(out, out_len);
}

static void test_roundtrip_aes(void **s) { (void)s; roundtrip_raw(LS_AEAD_AES256_GCM); }
static void test_roundtrip_chacha(void **s) { (void)s; roundtrip_raw(LS_AEAD_CHACHA20_POLY1305); }

/* --- empty plaintext --- */

static void test_empty_plaintext(void **s) {
    (void)s;
    uint8_t *blob = NULL, *out = NULL;
    size_t blob_len = 0, out_len = 99;
    assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, NULL, 0, &blob, &blob_len), LS_OK);
    assert_int_equal(blob_len, LS_OVERHEAD);
    assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_OK);
    assert_int_equal(out_len, 0);
    ls_free(blob, blob_len);
    ls_free(out, out_len);
}

/* --- wrong key fails closed --- */

static void test_wrong_key(void **s) {
    (void)s;
    uint8_t *blob = NULL, *out = (uint8_t *)0x1;
    size_t blob_len = 0, out_len = 1;
    assert_int_equal(
        ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len),
        LS_OK);

    uint8_t bad[LS_KEY_LEN];
    memcpy(bad, KEY, LS_KEY_LEN);
    bad[0] ^= 0x80;
    assert_int_equal(ls_open(bad, blob, blob_len, &out, &out_len), LS_ERR_AUTH);
    assert_null(out); /* no plaintext released */
    ls_free(blob, blob_len);
}

/* --- tampering any region fails closed --- */

static void tamper_at(size_t off) {
    uint8_t *blob = NULL, *out = NULL;
    size_t blob_len = 0, out_len = 0;
    assert_int_equal(
        ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len),
        LS_OK);
    assert_true(off < blob_len);
    blob[off] ^= 0x01;
    ls_status st = ls_open(KEY, blob, blob_len, &out, &out_len);
    assert_true(st == LS_ERR_AUTH || st == LS_ERR_FORMAT);
    assert_null(out);
    ls_free(blob, blob_len);
}

static void test_tamper_ciphertext(void **s) { (void)s; tamper_at(LS_HEADER_LEN + 2); }
static void test_tamper_tag(void **s)        { (void)s; tamper_at(LS_OVERHEAD + (sizeof PT - 1) - 1); }
static void test_tamper_nonce(void **s)      { (void)s; tamper_at(24); }
static void test_tamper_salt(void **s)       { (void)s; tamper_at(8); }
static void test_tamper_aead_id(void **s)    { (void)s; tamper_at(5); }

/* --- nondeterministic output (random nonce/salt) --- */

static void test_nondeterministic(void **s) {
    (void)s;
    uint8_t *a = NULL, *b = NULL;
    size_t al = 0, bl = 0;
    assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &a, &al), LS_OK);
    assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &b, &bl), LS_OK);
    assert_int_equal(al, bl);
    assert_memory_not_equal(a, b, al); /* different nonce => different blob */
    ls_free(a, al);
    ls_free(b, bl);
}

/* --- passphrase round trip + wrong passphrase --- */

static void test_passphrase_roundtrip(void **s) {
    (void)s;
    const char *pass = "correct horse battery staple";
    uint8_t *blob = NULL, *out = NULL;
    size_t blob_len = 0, out_len = 0;
    assert_int_equal(
        ls_seal_passphrase((const uint8_t *)pass, strlen(pass), LS_AEAD_AES256_GCM,
                           (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len),
        LS_OK);
    assert_int_equal(
        ls_open_passphrase((const uint8_t *)pass, strlen(pass), blob, blob_len, &out, &out_len),
        LS_OK);
    assert_int_equal(out_len, sizeof PT - 1);
    assert_memory_equal(out, PT, sizeof PT - 1);
    ls_free(out, out_len);

    const char *wrong = "Tr0ub4dor&3";
    uint8_t *out2 = (uint8_t *)0x1;
    size_t out2_len = 1;
    assert_int_equal(
        ls_open_passphrase((const uint8_t *)wrong, strlen(wrong), blob, blob_len, &out2, &out2_len),
        LS_ERR_AUTH);
    assert_null(out2);
    ls_free(blob, blob_len);
}

/* --- KDF determinism --- */

static void test_derive_key(void **s) {
    (void)s;
    const char *pass = "passphrase";
    uint8_t salt1[LS_SALT_LEN], salt2[LS_SALT_LEN];
    memset(salt1, 0xAA, sizeof salt1);
    memset(salt2, 0xBB, sizeof salt2);

    uint8_t k1[LS_KEY_LEN], k1b[LS_KEY_LEN], k2[LS_KEY_LEN];
    assert_int_equal(ls_derive_key((const uint8_t *)pass, strlen(pass), salt1, sizeof salt1, k1), LS_OK);
    assert_int_equal(ls_derive_key((const uint8_t *)pass, strlen(pass), salt1, sizeof salt1, k1b), LS_OK);
    assert_int_equal(ls_derive_key((const uint8_t *)pass, strlen(pass), salt2, sizeof salt2, k2), LS_OK);
    assert_memory_equal(k1, k1b, LS_KEY_LEN);    /* same salt => same key */
    assert_memory_not_equal(k1, k2, LS_KEY_LEN); /* different salt => different key */
}

/* --- format and argument validation --- */

static void test_format_errors(void **s) {
    (void)s;
    uint8_t *out = NULL;
    size_t out_len = 0;
    uint8_t tiny[LS_OVERHEAD - 1] = {0};
    assert_int_equal(ls_open(KEY, tiny, sizeof tiny, &out, &out_len), LS_ERR_FORMAT);

    uint8_t *blob = NULL;
    size_t blob_len = 0;
    assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len), LS_OK);
    blob[0] ^= 0xFF; /* corrupt magic */
    assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_ERR_FORMAT);
    ls_free(blob, blob_len);
}

static void test_null_and_limits(void **s) {
    (void)s;
    uint8_t *blob = NULL;
    size_t blob_len = 0;
    assert_int_equal(ls_seal(NULL, LS_AEAD_AES256_GCM, (const uint8_t *)PT, 1, &blob, &blob_len), LS_ERR_NULL_ARG);
    assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, 1, NULL, &blob_len), LS_ERR_NULL_ARG);
    assert_int_equal(
        ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, LS_MAX_PLAINTEXT + 1, &blob, &blob_len),
        LS_ERR_TOO_LARGE);
    ls_free(NULL, 0); /* no crash */
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_roundtrip_aes),
        cmocka_unit_test(test_roundtrip_chacha),
        cmocka_unit_test(test_empty_plaintext),
        cmocka_unit_test(test_wrong_key),
        cmocka_unit_test(test_tamper_ciphertext),
        cmocka_unit_test(test_tamper_tag),
        cmocka_unit_test(test_tamper_nonce),
        cmocka_unit_test(test_tamper_salt),
        cmocka_unit_test(test_tamper_aead_id),
        cmocka_unit_test(test_nondeterministic),
        cmocka_unit_test(test_passphrase_roundtrip),
        cmocka_unit_test(test_derive_key),
        cmocka_unit_test(test_format_errors),
        cmocka_unit_test(test_null_and_limits),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
