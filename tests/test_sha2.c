/* test_sha2 -- CMocka suite for the pure SHA-1/256/384/512 (FIPS 180-4 vectors). */
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "sha2.h"

static void hex(const uint8_t *d, size_t n, char *out) {
    for (size_t i = 0; i < n; ++i) sprintf(out + 2 * i, "%02x", d[i]);
}

static void check(sha_alg a, const char *msg, size_t rep, const char *want) {
    size_t ml = strlen(msg), len = ml * rep;
    char *buf = (char *)malloc(len + 1);
    assert_non_null(buf);
    for (size_t i = 0; i < rep; ++i) memcpy(buf + i * ml, msg, ml);
    uint8_t d[SHA_MAX_DIGEST];
    char h[2 * SHA_MAX_DIGEST + 1];
    assert_int_equal(sha_digest(a, buf, len, d), 0);
    hex(d, sha_digest_len(a), h);
    assert_string_equal(h, want);
    free(buf);
}

static void test_abc_vectors(void **state) {
    (void)state;
    check(SHA_1, "abc", 1, "a9993e364706816aba3e25717850c26c9cd0d89d");
    check(SHA_256, "abc", 1, "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    check(SHA_384, "abc", 1, "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7");
    check(SHA_512, "abc", 1, "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f");
}

static void test_empty_and_long(void **state) {
    (void)state;
    uint8_t d[SHA_MAX_DIGEST];
    char h[2 * SHA_MAX_DIGEST + 1];
    assert_int_equal(sha_digest(SHA_256, NULL, 0, d), 0);
    hex(d, 32, h);
    assert_string_equal(h, "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
    /* one million 'a' (padding crosses many blocks) */
    check(SHA_1, "a", 1000000, "34aa973cd4c4daa4f61eeb2bdbad27316534016f");
    check(SHA_256, "a", 1000000, "cdc76e5c9914fb9281a1c7e284d73e67f1809a48a497200e046d39ccc7112cd0");
    check(SHA_512, "a", 1000000, "e718483d0ce769644e2e42c7bc15b4638e1f98b13b2044285632a803afa973ebde0ff244877ea60a4cb0432ce577c31beb009c5c2c49aa2e4eadb217ad8cc09b");
}

static void test_padding_boundaries(void **state) {
    (void)state;
    /* 55/56/63/64 bytes straddle the one-block / two-block padding edge of SHA-256 */
    check(SHA_256, "a", 55, "9f4390f8d30c2dd92ec9f095b65e2b9ae9b0a925a5258e241c9f1e910f734318");
    check(SHA_256, "a", 56, "b35439a4ac6f0948b6d6f9e3c6af0f5f590ce20f1bde7090ef7970686ec6738a");
    check(SHA_256, "a", 64, "ffe054fe7ae0cb6dc65c3af9b61d5209f439851db43d0ba5997337df154668eb");
}

static void test_names_and_errors(void **state) {
    (void)state;
    sha_alg a;
    assert_int_equal(sha_alg_from_name("sha-256", &a), 0);
    assert_int_equal(a, SHA_256);
    assert_int_equal(sha_alg_from_name("MD5", &a), -1);
    assert_int_equal(sha_alg_from_name(NULL, &a), -1);
    uint8_t d[SHA_MAX_DIGEST];
    assert_int_equal(sha_digest(SHA_256, NULL, 5, d), -1);
    assert_int_equal(sha_digest(SHA_256, "x", 1, NULL), -1);
    assert_int_equal(sha_digest((sha_alg)99, "x", 1, d), -1);
    assert_int_equal((int)sha_digest_len((sha_alg)99), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_abc_vectors),
        cmocka_unit_test(test_empty_and_long),
        cmocka_unit_test(test_padding_boundaries),
        cmocka_unit_test(test_names_and_errors),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
