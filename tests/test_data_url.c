/*
 * test_data_url — CMocka suite for the pure data_url module.
 *
 * Covers scheme detection, base64-payload slicing (RFC 2397) and base64 decoding
 * (RFC 4648): the fail-closed edges (malformed length, misplaced padding, invalid
 * characters, oversized payload) matter as much as the happy path since this feeds
 * bytes into an image format decoder.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <cmocka.h>

#include "data_url.h"

/* --- du_is_data_url --- */

static void test_is_data_url_true(void **state) {
    (void)state;
    assert_int_not_equal(du_is_data_url("data:image/png;base64,QQ=="), 0);
    assert_int_not_equal(du_is_data_url("DATA:image/png;base64,QQ=="), 0);
    assert_int_not_equal(du_is_data_url("Data:,plain"), 0);
    assert_int_not_equal(du_is_data_url("data:"), 0);
}

static void test_is_data_url_false(void **state) {
    (void)state;
    assert_int_equal(du_is_data_url("https://example.com/logo.png"), 0);
    assert_int_equal(du_is_data_url("http://example.com"), 0);
    assert_int_equal(du_is_data_url("javascript:alert(1)"), 0);
    assert_int_equal(du_is_data_url(""), 0);
    assert_int_equal(du_is_data_url(NULL), 0);
    assert_int_equal(du_is_data_url("dat:notdata"), 0);
}

/* --- du_base64_payload --- */

static void test_payload_basic(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    du_status s = du_base64_payload("data:image/png;base64,QQ==", &payload, &plen);
    assert_int_equal(s, DU_OK);
    assert_non_null(payload);
    assert_int_equal(plen, 4);
    assert_memory_equal(payload, "QQ==", 4);
}

static void test_payload_no_mediatype(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    du_status s = du_base64_payload("data:;base64,QQ==", &payload, &plen);
    assert_int_equal(s, DU_OK);
    assert_int_equal(plen, 4);
}

static void test_payload_empty(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    du_status s = du_base64_payload("data:image/png;base64,", &payload, &plen);
    assert_int_equal(s, DU_OK);
    assert_non_null(payload);
    assert_int_equal(plen, 0);
}

static void test_payload_not_data_url(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    assert_int_equal(du_base64_payload("https://example.com/x.png", &payload, &plen),
                     DU_ERR_NOT_DATA_URL);
}

static void test_payload_percent_encoded_not_supported(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    assert_int_equal(du_base64_payload("data:image/svg+xml,<svg/>", &payload, &plen),
                     DU_ERR_NOT_BASE64);
}

static void test_payload_no_comma(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    assert_int_equal(du_base64_payload("data:image/png;base64", &payload, &plen),
                     DU_ERR_NOT_BASE64);
}

static void test_payload_base64_flag_case_insensitive(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    du_status s = du_base64_payload("data:image/png;BASE64,QQ==", &payload, &plen);
    assert_int_equal(s, DU_OK);
    assert_int_equal(plen, 4);
}

static void test_payload_too_large(void **state) {
    (void)state;
    size_t huge_len = DU_MAX_ENCODED_LEN + 4;
    char *url = (char *)malloc(strlen("data:image/png;base64,") + huge_len + 1);
    assert_non_null(url);
    strcpy(url, "data:image/png;base64,");
    memset(url + strlen(url), 'A', huge_len);
    url[strlen("data:image/png;base64,") + huge_len] = '\0';

    const char *payload = NULL;
    size_t plen = 0;
    du_status s = du_base64_payload(url, &payload, &plen);
    assert_int_equal(s, DU_ERR_TOO_LARGE);
    free(url);
}

static void test_payload_nulls(void **state) {
    (void)state;
    const char *payload = NULL;
    size_t plen = 0;
    assert_int_equal(du_base64_payload(NULL, &payload, &plen), DU_ERR_NULL_ARG);
    assert_int_equal(du_base64_payload("data:image/png;base64,QQ==", NULL, &plen),
                     DU_ERR_NULL_ARG);
    assert_int_equal(du_base64_payload("data:image/png;base64,QQ==", &payload, NULL),
                     DU_ERR_NULL_ARG);
}

/* --- du_base64_decode --- */

static void test_decode_one_byte_double_pad(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    du_status s = du_base64_decode("QQ==", 4, &out, &out_len);
    assert_int_equal(s, DU_OK);
    assert_int_equal(out_len, 1);
    assert_int_equal(out[0], 'A');
    free(out);
}

static void test_decode_two_bytes_single_pad(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    /* "QUI=" decodes to "AB" */
    du_status s = du_base64_decode("QUI=", 4, &out, &out_len);
    assert_int_equal(s, DU_OK);
    assert_int_equal(out_len, 2);
    assert_int_equal(out[0], 'A');
    assert_int_equal(out[1], 'B');
    free(out);
}

static void test_decode_no_padding_needed(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    /* "QUJD" decodes to "ABC" (3 bytes, no padding). */
    du_status s = du_base64_decode("QUJD", 4, &out, &out_len);
    assert_int_equal(s, DU_OK);
    assert_int_equal(out_len, 3);
    assert_memory_equal(out, "ABC", 3);
    free(out);
}

static void test_decode_multi_group(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    /* "SGVsbG8sIFdvcmxkIQ==" decodes to "Hello, World!" (13 bytes). */
    du_status s = du_base64_decode("SGVsbG8sIFdvcmxkIQ==", 20, &out, &out_len);
    assert_int_equal(s, DU_OK);
    assert_int_equal(out_len, 13);
    assert_memory_equal(out, "Hello, World!", 13);
    free(out);
}

static void test_decode_empty(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    du_status s = du_base64_decode("", 0, &out, &out_len);
    assert_int_equal(s, DU_OK);
    assert_int_equal(out_len, 0);
    free(out);
}

static void test_decode_bad_length_not_multiple_of_4(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    assert_int_equal(du_base64_decode("QQE", 3, &out, &out_len), DU_ERR_BAD_BASE64);
    assert_null(out);
}

static void test_decode_padding_in_wrong_position(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    /* '=' before the final two positions is malformed. */
    assert_int_equal(du_base64_decode("Q=EA", 4, &out, &out_len), DU_ERR_BAD_BASE64);
    assert_null(out);
}

static void test_decode_invalid_character(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    assert_int_equal(du_base64_decode("QQ!=", 4, &out, &out_len), DU_ERR_BAD_BASE64);
    assert_null(out);
    /* Whitespace is not part of the alphabet either -- fail closed, don't skip it. */
    assert_int_equal(du_base64_decode("QQ =", 4, &out, &out_len), DU_ERR_BAD_BASE64);
    assert_null(out);
}

static void test_decode_too_large(void **state) {
    (void)state;
    size_t huge_len = DU_MAX_ENCODED_LEN + 4;
    char *b64 = (char *)malloc(huge_len);
    assert_non_null(b64);
    memset(b64, 'A', huge_len);

    uint8_t *out = NULL;
    size_t out_len = 0;
    du_status s = du_base64_decode(b64, huge_len, &out, &out_len);
    assert_int_equal(s, DU_ERR_TOO_LARGE);
    assert_null(out);
    free(b64);
}

static void test_decode_nulls(void **state) {
    (void)state;
    uint8_t *out = NULL;
    size_t out_len = 0;
    assert_int_equal(du_base64_decode(NULL, 4, &out, &out_len), DU_ERR_NULL_ARG);
    assert_int_equal(du_base64_decode("QQ==", 4, NULL, &out_len), DU_ERR_NULL_ARG);
    assert_int_equal(du_base64_decode("QQ==", 4, &out, NULL), DU_ERR_NULL_ARG);
}

/* --- End-to-end: a real 1x1 PNG data URI round-trips to valid PNG bytes --- */

static void test_end_to_end_png_data_uri(void **state) {
    (void)state;
    const char *url =
        "data:image/png;base64,"
        "iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAIAAACQd1PeAAAADElEQVR4nGP4z8AAAAMBAQDJ/pLv"
        "AAAAAElFTkSuQmCC";

    const char *payload = NULL;
    size_t plen = 0;
    assert_int_equal(du_base64_payload(url, &payload, &plen), DU_OK);

    uint8_t *out = NULL;
    size_t out_len = 0;
    assert_int_equal(du_base64_decode(payload, plen, &out, &out_len), DU_OK);
    assert_true(out_len >= 8);
    /* PNG magic bytes. */
    static const uint8_t PNG_MAGIC[8] = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
    assert_memory_equal(out, PNG_MAGIC, 8);
    free(out);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_is_data_url_true),
        cmocka_unit_test(test_is_data_url_false),
        cmocka_unit_test(test_payload_basic),
        cmocka_unit_test(test_payload_no_mediatype),
        cmocka_unit_test(test_payload_empty),
        cmocka_unit_test(test_payload_not_data_url),
        cmocka_unit_test(test_payload_percent_encoded_not_supported),
        cmocka_unit_test(test_payload_no_comma),
        cmocka_unit_test(test_payload_base64_flag_case_insensitive),
        cmocka_unit_test(test_payload_too_large),
        cmocka_unit_test(test_payload_nulls),
        cmocka_unit_test(test_decode_one_byte_double_pad),
        cmocka_unit_test(test_decode_two_bytes_single_pad),
        cmocka_unit_test(test_decode_no_padding_needed),
        cmocka_unit_test(test_decode_multi_group),
        cmocka_unit_test(test_decode_empty),
        cmocka_unit_test(test_decode_bad_length_not_multiple_of_4),
        cmocka_unit_test(test_decode_padding_in_wrong_position),
        cmocka_unit_test(test_decode_invalid_character),
        cmocka_unit_test(test_decode_too_large),
        cmocka_unit_test(test_decode_nulls),
        cmocka_unit_test(test_end_to_end_png_data_uri),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
