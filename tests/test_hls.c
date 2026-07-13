/*
 * TDD suite for the pure m3u8 playlist parser (spec/hls.md).
 *
 * Build: make test   ;   ASan: make asan
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <cmocka.h>

#include "hls.h"

static void test_not_m3u8_returns_parse_error(void **state) {
    (void)state;
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse("this is not a playlist", 22, &pl), HLS_ERR_PARSE);
    assert_null(pl);
}

static void test_empty_m3u8_is_ok(void **state) {
    (void)state;
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse("#EXTM3U\n", 8, &pl), HLS_OK);
    assert_non_null(pl);
    assert_int_equal((int)pl->count, 0);
    hls_playlist_free(pl);
}

static void test_single_segment(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXTINF:10.5,\n"
        "seg1.ts\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_non_null(pl);
    assert_int_equal((int)pl->count, 1);
    assert_string_equal(pl->segments[0].url, "seg1.ts");
    assert_float_equal(pl->segments[0].duration, 10.5, 0.01);
    hls_playlist_free(pl);
}

static void test_multiple_segments(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXTINF:10.0,\n"
        "seg1.ts\n"
        "#EXTINF:9.5,\n"
        "seg2.ts\n"
        "#EXTINF:11.2,\n"
        "subdir/seg3.ts\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_non_null(pl);
    assert_int_equal((int)pl->count, 3);
    assert_string_equal(pl->segments[0].url, "seg1.ts");
    assert_float_equal(pl->segments[0].duration, 10.0, 0.01);
    assert_string_equal(pl->segments[1].url, "seg2.ts");
    assert_float_equal(pl->segments[1].duration, 9.5, 0.01);
    assert_string_equal(pl->segments[2].url, "subdir/seg3.ts");
    hls_playlist_free(pl);
}

static void test_target_duration_is_parsed(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXT-X-TARGETDURATION:10\n"
        "#EXTINF:9.0,\n"
        "seg.ts\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_non_null(pl);
    assert_float_equal(pl->target_duration, 10.0, 0.01);
    assert_false(pl->is_variant);
    hls_playlist_free(pl);
}

static void test_variant_playlist_detected(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,RESOLUTION=720x480\n"
        "medium.m3u8\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_non_null(pl);
    assert_true(pl->is_variant);
    assert_int_equal((int)pl->count, 0);
    hls_playlist_free(pl);
}

static void test_variant_playlist_collects_variants(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,RESOLUTION=720x480\n"
        "medium.m3u8\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_non_null(pl);
    assert_int_equal((int)pl->nvariants, 1);
    assert_string_equal(pl->variants[0].url, "medium.m3u8");
    assert_int_equal((int)pl->variants[0].bandwidth, 1280000);
    assert_int_equal(pl->variants[0].width, 720);
    assert_int_equal(pl->variants[0].height, 480);
    hls_playlist_free(pl);
}

static void test_multi_variant_collects_all(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=500000,RESOLUTION=320x240\n"
        "low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,RESOLUTION=720x480\n"
        "medium.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=4000000,RESOLUTION=1920x1080\n"
        "high.m3u8\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_non_null(pl);
    assert_true(pl->is_variant);
    assert_int_equal((int)pl->nvariants, 3);
    assert_string_equal(pl->variants[0].url, "low.m3u8");
    assert_string_equal(pl->variants[1].url, "medium.m3u8");
    assert_string_equal(pl->variants[2].url, "high.m3u8");
    hls_playlist_free(pl);
}

static void test_select_variant_highest_bandwidth_no_limit(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=500000,RESOLUTION=320x240\n"
        "low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,RESOLUTION=720x480\n"
        "medium.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=4000000,RESOLUTION=1920x1080\n"
        "high.m3u8\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    size_t sel = hls_select_variant(pl, 0, 0);
    assert_int_equal((int)sel, 2); /* highest bandwidth wins */
    hls_playlist_free(pl);
}

static void test_select_variant_respects_max_dimensions(void **state) {
    (void)state;
    const char *m3u8 =
        "#EXTM3U\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=500000,RESOLUTION=320x240\n"
        "low.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=1280000,RESOLUTION=720x480\n"
        "medium.m3u8\n"
        "#EXT-X-STREAM-INF:BANDWIDTH=4000000,RESOLUTION=1920x1080\n"
        "high.m3u8\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    /* Cap at 720p: medium should be chosen (highest bandwidth that fits) */
    size_t sel = hls_select_variant(pl, 1280, 720);
    assert_int_equal((int)sel, 1);
    hls_playlist_free(pl);
}

static void test_select_variant_empty_returns_error(void **state) {
    (void)state;
    const char *m3u8 = "#EXTM3U\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(m3u8, strlen(m3u8), &pl), HLS_OK);
    assert_int_equal((int)hls_select_variant(pl, 1920, 1080), -1);
    assert_int_equal((int)hls_select_variant(NULL, 0, 0), -1);
    hls_playlist_free(pl);
}

static void test_resolve_url_absolute_passthrough(void **state) {
    (void)state;
    char out[512];
    size_t n = hls_resolve_url("https://e.example/playlist.m3u8",
                                "https://cdn.e/seg.ts",
                                out, sizeof out);
    assert_int_not_equal((int)n, 0);
    assert_string_equal(out, "https://cdn.e/seg.ts");
}

static void test_resolve_url_relative(void **state) {
    (void)state;
    char out[512];
    size_t n = hls_resolve_url("https://e.example/hls/playlist.m3u8",
                                "seg001.ts",
                                out, sizeof out);
    assert_int_not_equal((int)n, 0);
    assert_string_equal(out, "https://e.example/hls/seg001.ts");
}

static void test_resolve_url_deep_relative(void **state) {
    (void)state;
    char out[512];
    size_t n = hls_resolve_url("https://e.example/a/b/c/play.m3u8",
                                "d/seg.ts", out, sizeof out);
    assert_int_not_equal((int)n, 0);
    assert_string_equal(out, "https://e.example/a/b/c/d/seg.ts");
}

static void test_handles_windows_line_endings(void **state) {
    (void)state;
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse("#EXTM3U\r\n#EXTINF:5.0,\r\nseg.ts\r\n", 31, &pl), HLS_OK);
    assert_non_null(pl);
    assert_int_equal((int)pl->count, 1);
    assert_string_equal(pl->segments[0].url, "seg.ts");
    hls_playlist_free(pl);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_not_m3u8_returns_parse_error),
        cmocka_unit_test(test_empty_m3u8_is_ok),
        cmocka_unit_test(test_single_segment),
        cmocka_unit_test(test_multiple_segments),
        cmocka_unit_test(test_target_duration_is_parsed),
        cmocka_unit_test(test_variant_playlist_detected),
        cmocka_unit_test(test_variant_playlist_collects_variants),
        cmocka_unit_test(test_multi_variant_collects_all),
        cmocka_unit_test(test_select_variant_highest_bandwidth_no_limit),
        cmocka_unit_test(test_select_variant_respects_max_dimensions),
        cmocka_unit_test(test_select_variant_empty_returns_error),
        cmocka_unit_test(test_resolve_url_absolute_passthrough),
        cmocka_unit_test(test_resolve_url_relative),
        cmocka_unit_test(test_resolve_url_deep_relative),
        cmocka_unit_test(test_handles_windows_line_endings),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
