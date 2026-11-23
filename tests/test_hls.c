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

static void fill_ts(unsigned char *b, size_t off, size_t packets) {
    for (size_t p = 0; p < packets; ++p) {
        memset(b + off + p * 188, 0x11, 188);
        b[off + p * 188] = 0x47;
    }
}

static void test_segment_error_status_rejected(void **state) {
    (void)state;
    unsigned char b[188 * 3];
    fill_ts(b, 0, 3);
    assert_int_equal(hls_segment_payload(500, b, sizeof b), -1);
    assert_int_equal(hls_segment_payload(404, b, sizeof b), -1);
    assert_int_equal(hls_segment_payload(0, b, sizeof b), -1);
    assert_int_equal(hls_segment_payload(200, b, sizeof b), 0);
    assert_int_equal(hls_segment_payload(206, b, sizeof b), 0);
}

static void test_segment_text_body_rejected(void **state) {
    (void)state;
    const char *err = "500 Internal Server Error\n\nServer got itself in trouble";
    assert_int_equal(hls_segment_payload(200, (const unsigned char *)err, strlen(err)), -1);
    const char *html = "<html><body>G</body></html>";
    assert_int_equal(hls_segment_payload(200, (const unsigned char *)html, strlen(html)), -1);
    const char *gw = "Gateway Timeout";
    assert_int_equal(hls_segment_payload(200, (const unsigned char *)gw, strlen(gw)), -1);
    assert_int_equal(hls_segment_payload(200, NULL, 10), -1);
    assert_int_equal(hls_segment_payload(200, (const unsigned char *)"x", 0), -1);
}

static void test_segment_ts_behind_fake_png(void **state) {
    (void)state;
    static unsigned char b[120 + 188 * 4];
    memset(b, 0, sizeof b);
    memcpy(b, "\x89PNG\r\n\x1a\n", 8);
    b[50] = 0x47;  /* lone sync byte inside the fake image: not a stream */
    fill_ts(b, 120, 4);
    assert_int_equal(hls_segment_payload(200, b, sizeof b), 120);
}

static void test_segment_single_packet_and_bmff(void **state) {
    (void)state;
    unsigned char ts[188];
    fill_ts(ts, 0, 1);
    assert_int_equal(hls_segment_payload(200, ts, sizeof ts), 0);
    unsigned char mp4[16] = { 0, 0, 0, 16, 'f', 't', 'y', 'p', 'i', 's', 'o', 'm', 0, 0, 0, 1 };
    assert_int_equal(hls_segment_payload(200, mp4, sizeof mp4), 0);
    memcpy(mp4 + 4, "moof", 4);
    assert_int_equal(hls_segment_payload(200, mp4, sizeof mp4), 0);
    unsigned char id3[10] = { 'I', 'D', '3', 4, 0, 0, 0, 0, 0, 0 };
    assert_int_equal(hls_segment_payload(200, id3, sizeof id3), 0);
}

/* Regression (fuzz-hls): a tag cut at the end of an unterminated buffer was read past it. */
static void test_unterminated_tag_stays_in_bounds(void **state) {
    (void)state;
    static const char src[] = "#EXTM3U\n#E";
    char *buf = (char *)malloc(sizeof src - 1);
    assert_non_null(buf);
    memcpy(buf, src, sizeof src - 1);
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(buf, sizeof src - 1, &pl), HLS_OK);
    hls_playlist_free(pl);
    static const char td[] = "#EXTM3U\n#EXT-X-TARGETDURATION:9";
    char *b2 = (char *)malloc(sizeof td - 1);
    assert_non_null(b2);
    memcpy(b2, td, sizeof td - 1);
    assert_int_equal(hls_parse(b2, sizeof td - 1, &pl), HLS_OK);
    assert_true(pl->target_duration > 8.9 && pl->target_duration < 9.1);
    hls_playlist_free(pl);
    free(b2);
    free(buf);
}

static hls_playlist *mirror_pl(void) {
    const char *t =
        "#EXTM3U\n#EXTINF:5,\nhttps://cdn6.x.example/p/20.ts\n"
        "#EXTINF:5,\nhttps://cdn2.x.example/p/21.ts\n"
        "#EXTINF:5,\nhttps://evil.example/p/22.ts\n"
        "#EXTINF:5,\nhttps://cdn2.x.example/p/23.ts\n"
        "#EXTINF:5,\nhttps://cdn5.x.example:8443/p/24.ts\n"
        "#EXTINF:5,\nhttp://cdn9.x.example/p/25.ts\n"
        "#EXTINF:5,\nrel/26.ts\n";
    hls_playlist *pl = NULL;
    assert_int_equal(hls_parse(t, strlen(t), &pl), HLS_OK);
    return pl;
}

static void test_mirror_uses_declared_sibling_hosts(void **state) {
    (void)state;
    hls_playlist *pl = mirror_pl();
    char out[256];
    assert_int_equal(hls_mirror_url(pl, "https://cdn6.x.example/p/20.ts?a=1", 0, out, sizeof out),
                     strlen("https://cdn2.x.example/p/20.ts?a=1"));
    assert_string_equal(out, "https://cdn2.x.example/p/20.ts?a=1");
    assert_true(hls_mirror_url(pl, "https://cdn6.x.example/p/20.ts", 1, out, sizeof out) > 0);
    assert_string_equal(out, "https://cdn5.x.example:8443/p/20.ts");
    /* no third: evil.example is another site, cdn9 is http, rel/ is relative */
    assert_int_equal(hls_mirror_url(pl, "https://cdn6.x.example/p/20.ts", 2, out, sizeof out), 0);
    hls_playlist_free(pl);
}

static void test_mirror_rejects_bad_inputs(void **state) {
    (void)state;
    hls_playlist *pl = mirror_pl();
    char out[16];
    assert_int_equal(hls_mirror_url(pl, "https://cdn6.x.example/p/20.ts", 0, out, sizeof out), 0);
    char big[256];
    assert_int_equal(hls_mirror_url(pl, "http://cdn6.x.example/p/20.ts", 0, big, sizeof big), 0);
    assert_int_equal(hls_mirror_url(pl, "https://other.example/p/20.ts", 0, big, sizeof big), 0);
    assert_int_equal(hls_mirror_url(NULL, "https://cdn6.x.example/p/20.ts", 0, big, sizeof big), 0);
    assert_int_equal(hls_mirror_url(pl, NULL, 0, big, sizeof big), 0);
    /* the failing host itself is never its own mirror */
    assert_true(hls_mirror_url(pl, "https://cdn2.x.example/p/21.ts", 0, big, sizeof big) > 0);
    assert_string_equal(big, "https://cdn6.x.example/p/21.ts");
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
        cmocka_unit_test(test_segment_error_status_rejected),
        cmocka_unit_test(test_segment_text_body_rejected),
        cmocka_unit_test(test_segment_ts_behind_fake_png),
        cmocka_unit_test(test_segment_single_packet_and_bmff),
        cmocka_unit_test(test_mirror_uses_declared_sibling_hosts),
        cmocka_unit_test(test_unterminated_tag_stays_in_bounds),
        cmocka_unit_test(test_mirror_rejects_bad_inputs),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
