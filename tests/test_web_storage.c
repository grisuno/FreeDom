/*
 * TDD suite for web_storage (spec/web_storage.md): the in-memory localStorage the
 * trusted parent keeps per origin, and the validation of the worker's snapshot.
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmocka.h>

#include "web_storage.h"

/* Builds a snapshot from (key, value) C strings. */
static size_t put_u32(char *b, size_t o, uint32_t v) {
    b[o] = (char)(v & 0xFF); b[o + 1] = (char)((v >> 8) & 0xFF);
    b[o + 2] = (char)((v >> 16) & 0xFF); b[o + 3] = (char)((v >> 24) & 0xFF);
    return o + 4;
}

static size_t build(char *b, const char *const *kv, uint32_t n) {
    size_t o = put_u32(b, 0, n);
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t kl = (uint32_t)strlen(kv[2 * i]), vl = (uint32_t)strlen(kv[2 * i + 1]);
        o = put_u32(b, o, kl); memcpy(b + o, kv[2 * i], kl); o += kl;
        o = put_u32(b, o, vl); memcpy(b + o, kv[2 * i + 1], vl); o += vl;
    }
    return o;
}

static void test_unknown_origin_encodes_empty(void **state) {
    (void)state;
    wst_db *db = wst_new();
    assert_non_null(db);
    char *out = NULL;
    size_t len = 0;
    assert_int_equal(wst_encode(db, "https://a.test", &out, &len), 0);
    assert_int_equal(len, 4);
    assert_int_equal(wst_decode_check(out, len), 0);
    free(out);
    assert_int_equal(wst_origin_bytes(db, "https://a.test"), 0);
    wst_free(db);
    wst_free(NULL);
}

static void test_replace_then_encode_roundtrip(void **state) {
    (void)state;
    wst_db *db = wst_new();
    char b[256];
    const char *kv[] = { "theme", "dark", "draft", "hola \xc3\xb1" };
    size_t n = build(b, kv, 2);
    assert_int_equal(wst_replace(db, "https://a.test", b, n), 0);
    assert_int_equal(wst_origin_bytes(db, "https://a.test"), 5 + 4 + 5 + 7);
    /* other origin untouched */
    assert_int_equal(wst_origin_bytes(db, "https://b.test"), 0);
    char *out = NULL;
    size_t len = 0;
    assert_int_equal(wst_encode(db, "https://a.test", &out, &len), 0);
    assert_int_equal(len, n);
    assert_memory_equal(out, b, n);
    free(out);
    /* a later snapshot REPLACES (clear/removeItem reach the parent) */
    const char *kv2[] = { "theme", "light" };
    n = build(b, kv2, 1);
    assert_int_equal(wst_replace(db, "https://a.test", b, n), 0);
    assert_int_equal(wst_origin_bytes(db, "https://a.test"), 5 + 5);
    wst_free(db);
}

static void test_hostile_snapshots_rejected_and_db_unchanged(void **state) {
    (void)state;
    wst_db *db = wst_new();
    char b[256];
    const char *kv[] = { "k", "v" };
    size_t n = build(b, kv, 1);
    assert_int_equal(wst_replace(db, "https://a.test", b, n), 0);

    char bad[64];
    memcpy(bad, b, n);
    /* truncated */
    assert_int_equal(wst_replace(db, "https://a.test", bad, n - 1), -1);
    /* trailing garbage */
    bad[n] = 'x';
    assert_int_equal(wst_replace(db, "https://a.test", bad, n + 1), -1);
    /* count larger than content */
    put_u32(bad, 0, 2);
    assert_int_equal(wst_replace(db, "https://a.test", bad, n), -1);
    /* giant length */
    memcpy(bad, b, n);
    put_u32(bad, 4, 0xFFFFFFF0u);
    assert_int_equal(wst_replace(db, "https://a.test", bad, n), -1);
    /* invalid UTF-8 */
    const char *kvu[] = { "k", "\xc3\x28" };
    size_t nu = build(bad, kvu, 1);
    assert_int_equal(wst_decode_check(bad, nu), -1);
    /* duplicate keys */
    const char *kvd[] = { "k", "1", "k", "2" };
    size_t nd = build(bad, kvd, 2);
    assert_int_equal(wst_decode_check(bad, nd), -1);
    assert_int_equal(wst_decode_check(NULL, 4), -1);
    assert_int_equal(wst_decode_check(b, 3), -1);
    /* the stored content survived every rejection */
    assert_int_equal(wst_origin_bytes(db, "https://a.test"), 2);
    assert_int_equal(wst_replace(NULL, "https://a.test", b, n), -1);
    assert_int_equal(wst_replace(db, NULL, b, n), -1);
    wst_free(db);
}

static void test_quota_enforced(void **state) {
    (void)state;
    size_t big = WST_QUOTA;             /* key "k" (1) + value WST_QUOTA > quota */
    char *b = (char *)malloc(big + 64);
    assert_non_null(b);
    size_t o = put_u32(b, 0, 1);
    o = put_u32(b, o, 1); b[o++] = 'k';
    o = put_u32(b, o, (uint32_t)big); memset(b + o, 'a', big); o += big;
    assert_int_equal(wst_decode_check(b, o), -1);
    /* exactly at quota is fine */
    o = put_u32(b, 0, 1);
    o = put_u32(b, o, 1); b[o++] = 'k';
    o = put_u32(b, o, (uint32_t)(big - 1)); memset(b + o, 'a', big - 1); o += big - 1;
    assert_int_equal(wst_decode_check(b, o), 0);
    free(b);
}

static void test_origin_table_is_bounded_lru(void **state) {
    (void)state;
    wst_db *db = wst_new();
    char b[64];
    const char *kv[] = { "k", "v" };
    size_t n = build(b, kv, 1);
    char origin[64];
    for (unsigned i = 0; i < WST_MAX_ORIGINS + 5; ++i) {
        snprintf(origin, sizeof origin, "https://o%u.test", i);
        assert_int_equal(wst_replace(db, origin, b, n), 0);
    }
    /* the oldest ones were evicted, the newest kept */
    assert_int_equal(wst_origin_bytes(db, "https://o0.test"), 0);
    snprintf(origin, sizeof origin, "https://o%u.test", WST_MAX_ORIGINS + 4);
    assert_int_equal(wst_origin_bytes(db, origin), 2);
    wst_free(db);
}

static void count_pair(void *ctx, const char *k, size_t kl, const char *v, size_t vl) {
    (void)k; (void)v;
    size_t *acc = (size_t *)ctx;
    acc[0]++;
    acc[1] += kl + vl;
}

static void test_pack_foreach_roundtrip(void **state) {
    (void)state;
    const char *keys[] = { "a", "b\xc3\xb1" };
    const char *vals[] = { "1", "" };
    size_t kl[] = { 1, 3 }, vl[] = { 1, 0 };
    char *out = NULL;
    size_t len = 0;
    assert_int_equal(wst_pack(keys, kl, vals, vl, 2, &out, &len), 0);
    assert_int_equal(wst_decode_check(out, len), 0);
    size_t acc[2] = { 0, 0 };
    assert_int_equal(wst_foreach(out, len, count_pair, acc), 0);
    assert_int_equal(acc[0], 2);
    assert_int_equal(acc[1], 5);
    free(out);
    /* empty store packs to a valid empty snapshot */
    assert_int_equal(wst_pack(NULL, NULL, NULL, NULL, 0, &out, &len), 0);
    assert_int_equal(len, 4);
    free(out);
    /* duplicates / bad UTF-8 are refused by the builder too */
    const char *dk[] = { "k", "k" };
    size_t dkl[] = { 1, 1 };
    assert_int_equal(wst_pack(dk, dkl, vals, vl, 2, &out, &len), -1);
    /* an invalid snapshot never reaches the callback */
    acc[0] = 0;
    assert_int_equal(wst_foreach("\x01\x00\x00\x00", 4, count_pair, acc), -1);
    assert_int_equal(acc[0], 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_unknown_origin_encodes_empty),
        cmocka_unit_test(test_replace_then_encode_roundtrip),
        cmocka_unit_test(test_hostile_snapshots_rejected_and_db_unchanged),
        cmocka_unit_test(test_quota_enforced),
        cmocka_unit_test(test_origin_table_is_bounded_lru),
        cmocka_unit_test(test_pack_foreach_roundtrip),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
