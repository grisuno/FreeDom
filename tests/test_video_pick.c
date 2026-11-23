#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "video_pick.h"

static pv_view *view_with(const char *const *srcs, size_t n) {
    pv_view *v = pv_new();
    assert_non_null(v);
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "intro", NULL), PV_OK);
    for (size_t i = 0; i < n; ++i)
        assert_int_equal(pv_append_video(v, 0, 1, NULL, srcs[i], NULL, -1, -1), PV_OK);
    return v;
}

static void null_and_empty_views_have_no_video(void **st) {
    (void)st;
    assert_null(vpk_first_video(NULL));
    pv_view *v = view_with(NULL, 0);
    assert_null(vpk_first_video(v));
    pv_free(v);
}

static void first_non_empty_src_wins(void **st) {
    (void)st;
    const char *s[] = { "", "https://a.example/one.m3u8", "https://a.example/two.m3u8" };
    pv_view *v = view_with(s, 3);
    const char *got = vpk_first_video(v);
    assert_non_null(got);
    assert_string_equal(got, "https://a.example/one.m3u8");
    pv_free(v);
}

static void frame_video_beats_top_video(void **st) {
    (void)st;
    const char *fs[] = { "https://f.example/frame.m3u8" };
    pv_view *f = view_with(fs, 1);
    assert_string_equal(vpk_for_frame(f, "https://t.example/top.m3u8"), "https://f.example/frame.m3u8");
    pv_free(f);
}

static void frame_without_video_falls_back_to_top(void **st) {
    (void)st;
    pv_view *f = view_with(NULL, 0);
    assert_string_equal(vpk_for_frame(f, "https://t.example/top.m3u8"), "https://t.example/top.m3u8");
    assert_string_equal(vpk_for_frame(NULL, "https://t.example/top.m3u8"), "https://t.example/top.m3u8");
    pv_free(f);
}

static void nothing_anywhere_is_null(void **st) {
    (void)st;
    pv_view *f = view_with(NULL, 0);
    assert_null(vpk_for_frame(f, NULL));
    assert_null(vpk_for_frame(f, ""));
    assert_null(vpk_for_frame(NULL, NULL));
    pv_free(f);
}

static void non_url_src_is_not_a_video(void **st) {
    (void)st;
    const char *fs[] = { "[object Object]", "blob:https://f.example/1", "javascript:alert(1)" };
    pv_view *f = view_with(fs, 3);
    assert_null(vpk_first_video(f));
    assert_string_equal(vpk_for_frame(f, "https://t.example/top.m3u8"), "https://t.example/top.m3u8");
    assert_null(vpk_for_frame(f, "[object Object]"));
    pv_free(f);
    const char *ok[] = { "HTTPS://f.example/a.m3u8" };
    pv_view *g = view_with(ok, 1);
    assert_string_equal(vpk_first_video(g), "HTTPS://f.example/a.m3u8");
    pv_free(g);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_and_empty_views_have_no_video),
        cmocka_unit_test(first_non_empty_src_wins),
        cmocka_unit_test(frame_video_beats_top_video),
        cmocka_unit_test(frame_without_video_falls_back_to_top),
        cmocka_unit_test(nothing_anywhere_is_null),
        cmocka_unit_test(non_url_src_is_not_a_video),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
