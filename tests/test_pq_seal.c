#define _GNU_SOURCE
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "pq_seal.h"

static const uint8_t WRAP[LS_KEY_LEN] = { 1, 2, 3, 4, 5, 6, 7, 8 };

static void test_seal_open_roundtrip(void **state) {
    (void)state;
    pqs_keys *k = NULL;
    assert_int_equal(pqs_generate(&k), PQS_OK);
    const char *msg = "permanent redirect memory";
    uint8_t *blob = NULL, *back = NULL;
    size_t bl = 0, ol = 0;
    assert_int_equal(pqs_seal(k, WRAP, (const uint8_t *)msg, strlen(msg), &blob, &bl), PQS_OK);
    assert_memory_equal(blob, PQS_MAGIC, PQS_MAGIC_LEN);
    assert_true(bl > PQS_MAGIC_LEN + PQS_CT_LEN + LS_OVERHEAD);
    assert_null(memmem(blob, bl, msg, strlen(msg)));
    assert_int_equal(pqs_open(k, WRAP, blob, bl, &back, &ol), PQS_OK);
    assert_int_equal(ol, strlen(msg));
    assert_memory_equal(back, msg, ol);
    pqs_buf_free(back, ol);
    pqs_buf_free(blob, bl);
    pqs_free(k);
}

static void test_each_seal_is_fresh(void **state) {
    (void)state;
    pqs_keys *k = NULL;
    assert_int_equal(pqs_generate(&k), PQS_OK);
    uint8_t *a = NULL, *b = NULL;
    size_t al = 0, bl = 0;
    assert_int_equal(pqs_seal(k, WRAP, (const uint8_t *)"x", 1, &a, &al), PQS_OK);
    assert_int_equal(pqs_seal(k, WRAP, (const uint8_t *)"x", 1, &b, &bl), PQS_OK);
    assert_true(al != bl || memcmp(a, b, al) != 0);
    pqs_buf_free(a, al); pqs_buf_free(b, bl); pqs_free(k);
}

/* Both secrets are needed: a wrong wrap key, foreign KEM keys or one flipped bit all fail closed. */
static void test_requires_both_secrets_and_detects_tamper(void **state) {
    (void)state;
    pqs_keys *k = NULL, *other = NULL;
    assert_int_equal(pqs_generate(&k), PQS_OK);
    assert_int_equal(pqs_generate(&other), PQS_OK);
    uint8_t *blob = NULL, *out = NULL;
    size_t bl = 0, ol = 0;
    assert_int_equal(pqs_seal(k, WRAP, (const uint8_t *)"secret", 6, &blob, &bl), PQS_OK);
    uint8_t wrong[LS_KEY_LEN] = { 9 };
    assert_int_equal(pqs_open(k, wrong, blob, bl, &out, &ol), PQS_ERR_AUTH);
    assert_null(out);
    assert_int_equal(pqs_open(other, WRAP, blob, bl, &out, &ol), PQS_ERR_AUTH);
    assert_null(out);
    blob[bl - 1] ^= 1;
    assert_int_equal(pqs_open(k, WRAP, blob, bl, &out, &ol), PQS_ERR_AUTH);
    blob[bl - 1] ^= 1;
    blob[PQS_MAGIC_LEN + 5] ^= 1;   /* inside the KEM ciphertext */
    assert_int_equal(pqs_open(k, WRAP, blob, bl, &out, &ol), PQS_ERR_AUTH);
    pqs_buf_free(blob, bl); pqs_free(k); pqs_free(other);
}

static void test_format_errors(void **state) {
    (void)state;
    pqs_keys *k = NULL;
    assert_int_equal(pqs_generate(&k), PQS_OK);
    uint8_t *out = NULL;
    size_t ol = 0;
    assert_int_equal(pqs_open(k, WRAP, (const uint8_t *)"XXXX", 4, &out, &ol), PQS_ERR_FORMAT);
    assert_int_equal(pqs_open(k, WRAP, (const uint8_t *)"FPQ1short", 9, &out, &ol), PQS_ERR_FORMAT);
    assert_int_equal(pqs_open(NULL, WRAP, (const uint8_t *)"FPQ1", 4, &out, &ol), PQS_ERR_NULL_ARG);
    pqs_free(k);
}

static void test_export_import_keeps_decapsulation(void **state) {
    (void)state;
    pqs_keys *k = NULL, *k2 = NULL;
    assert_int_equal(pqs_generate(&k), PQS_OK);
    uint8_t *der = NULL, *blob = NULL, *out = NULL;
    size_t dl = 0, bl = 0, ol = 0;
    assert_int_equal(pqs_export(k, &der, &dl), PQS_OK);
    assert_int_equal(pqs_import(der, dl, &k2), PQS_OK);
    assert_int_equal(pqs_seal(k, WRAP, (const uint8_t *)"persist", 7, &blob, &bl), PQS_OK);
    assert_int_equal(pqs_open(k2, WRAP, blob, bl, &out, &ol), PQS_OK);
    assert_int_equal(ol, 7);
    pqs_keys *junk = NULL;
    assert_int_equal(pqs_import((const uint8_t *)"junk", 4, &junk), PQS_ERR_CRYPTO);
    assert_null(junk);
    pqs_buf_free(out, ol); pqs_buf_free(blob, bl); pqs_buf_free(der, dl);
    pqs_free(k); pqs_free(k2);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_seal_open_roundtrip),
        cmocka_unit_test(test_each_seal_is_fresh),
        cmocka_unit_test(test_requires_both_secrets_and_detects_tamper),
        cmocka_unit_test(test_format_errors),
        cmocka_unit_test(test_export_import_keeps_decapsulation),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
