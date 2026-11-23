#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <string.h>
#include <math.h>
#include <cmocka.h>

#include "video_controls.h"

static hls_playlist *pl_of(const double *d, size_t n, hls_segment *segs) {
    static hls_playlist pl;
    memset(&pl, 0, sizeof pl);
    for (size_t i = 0; i < n; ++i) {
        segs[i].url = (char *)"s.ts";
        segs[i].url_len = 4;
        segs[i].duration = d[i];
    }
    pl.segments = segs;
    pl.count = n;
    pl.cap = n;
    return &pl;
}

static void layout_puts_bar_at_bottom_and_rejects_tiny(void **st) {
    (void)st;
    vcl_geom g;
    assert_int_equal(vcl_layout(100, 50, 640, 360, &g), 1);
    assert_true(g.bar.y + g.bar.h <= 50 + 360 + 1e-9);
    assert_true(g.bar.y >= 50 + 360 - VCL_BAR_H - 1e-9);
    assert_true(g.play.x >= 100);
    assert_true(g.track.x > g.play.x + g.play.w);
    assert_true(g.track.x + g.track.w < 100 + 640);
    assert_int_equal(vcl_layout(0, 0, 60, 360, &g), 0);
    assert_int_equal(vcl_layout(0, 0, 640, 40, &g), 0);
    assert_int_equal(vcl_layout(NAN, 0, 640, 360, &g), 0);
    assert_int_equal(vcl_layout(0, 0, INFINITY, 360, &g), 0);
    assert_int_equal(vcl_layout(0, 0, 640, 360, NULL), 0);
}

static void hit_classifies_button_track_bar_surface(void **st) {
    (void)st;
    vcl_geom g;
    vcl_rect v = { 0, 0, 640, 360 };
    assert_int_equal(vcl_layout(v.x, v.y, v.w, v.h, &g), 1);
    double f = -1;
    assert_int_equal(vcl_hit(&g, &v, -5, 10, &f), VCL_HIT_NONE);
    assert_int_equal(vcl_hit(&g, &v, 320, 100, &f), VCL_HIT_TOGGLE);
    assert_int_equal(vcl_hit(&g, &v, g.play.x + 1, g.play.y + 1, &f), VCL_HIT_TOGGLE);
    assert_int_equal(vcl_hit(&g, &v, g.track.x, g.bar.y + 2, &f), VCL_HIT_SEEK);
    assert_true(f >= 0.0 && f < 0.01);
    assert_int_equal(vcl_hit(&g, &v, g.track.x + g.track.w / 2, g.bar.y + 2, &f), VCL_HIT_SEEK);
    assert_true(fabs(f - 0.5) < 1e-9);
    assert_int_equal(vcl_hit(&g, &v, g.track.x + g.track.w, g.bar.y + 2, &f), VCL_HIT_SEEK);
    assert_true(f <= 1.0);
    /* The time label area belongs to the bar, not to the video below it. */
    assert_int_equal(vcl_hit(&g, &v, 639, g.bar.y + 2, &f), VCL_HIT_BAR);
    /* No bar: the surface still toggles. */
    assert_int_equal(vcl_hit(NULL, &v, 320, 355, &f), VCL_HIT_TOGGLE);
    assert_int_equal(vcl_hit(NULL, NULL, 320, 355, &f), VCL_HIT_NONE);
}

static void hostile_durations_stay_finite(void **st) {
    (void)st;
    hls_segment s[6];
    double d[6] = { 4.0, NAN, -3.0, INFINITY, 1e300, 6.0 };
    hls_playlist *pl = pl_of(d, 6, s);
    double t = vcl_total(pl);
    assert_true(isfinite(t));
    assert_true(fabs(t - (4.0 + 6.0 + 2 * VCL_MAX_SEGMENT_S)) < 1e-6);
    assert_true(vcl_total(NULL) == 0.0);
    assert_true(vcl_seg_duration(NAN) == 0.0);
    assert_true(vcl_seg_duration(-1.0) == 0.0);
}

static void segment_at_maps_time_and_clamps(void **st) {
    (void)st;
    hls_segment s[3];
    double d[3] = { 10.0, 10.0, 5.0 };
    hls_playlist *pl = pl_of(d, 3, s);
    double start = -1;
    assert_int_equal(vcl_segment_at(pl, 0.0, &start), 0);
    assert_true(start == 0.0);
    assert_int_equal(vcl_segment_at(pl, 9.99, &start), 0);
    assert_int_equal(vcl_segment_at(pl, 10.0, &start), 1);
    assert_true(start == 10.0);
    assert_int_equal(vcl_segment_at(pl, 22.0, &start), 2);
    assert_true(start == 20.0);
    assert_int_equal(vcl_segment_at(pl, 1e9, &start), 2);
    assert_int_equal(vcl_segment_at(pl, -5.0, &start), 0);
    assert_int_equal(vcl_segment_at(pl, NAN, &start), 0);
    assert_int_equal(vcl_segment_at(NULL, 3.0, &start), 0);
    assert_true(start == 0.0);
    assert_true(vcl_segment_start(pl, 2) == 20.0);
    assert_true(vcl_segment_start(pl, 99) == 20.0);
}

static void position_is_clamped(void **st) {
    (void)st;
    assert_true(fabs(vcl_position(20.0, 1000000, 3500000, 100.0) - 22.5) < 1e-9);
    assert_true(vcl_position(20.0, 5000000, 1000000, 100.0) == 20.0);
    assert_true(vcl_position(20.0, 0, INT64_MAX, 100.0) == 100.0);
    assert_true(vcl_position(20.0, INT64_MAX, INT64_MIN, 100.0) == 20.0);
    assert_true(vcl_position(NAN, 0, 0, 100.0) == 0.0);
    assert_true(vcl_position(500.0, 0, 0, 100.0) == 100.0);
}

static void frac_and_time_format(void **st) {
    (void)st;
    assert_true(vcl_clamp_frac(NAN) == 0.0);
    assert_true(vcl_clamp_frac(-1) == 0.0);
    assert_true(vcl_clamp_frac(2) == 1.0);
    char b[16];
    assert_int_equal(vcl_format_time(0, b, sizeof b), 4);
    assert_string_equal(b, "0:00");
    vcl_format_time(65.9, b, sizeof b);
    assert_string_equal(b, "1:05");
    vcl_format_time(3723, b, sizeof b);
    assert_string_equal(b, "1:02:03");
    vcl_format_time(NAN, b, sizeof b);
    assert_string_equal(b, "0:00");
    vcl_format_time(-4, b, sizeof b);
    assert_string_equal(b, "0:00");
    vcl_format_time(1e300, b, sizeof b);
    assert_true(strlen(b) > 0);
    char t[3];
    assert_int_equal(vcl_format_time(65, t, sizeof t), 0);
    assert_string_equal(t, "");
    assert_int_equal(vcl_format_time(65, NULL, 0), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(layout_puts_bar_at_bottom_and_rejects_tiny),
        cmocka_unit_test(hit_classifies_button_track_bar_surface),
        cmocka_unit_test(hostile_durations_stay_finite),
        cmocka_unit_test(segment_at_maps_time_and_clamps),
        cmocka_unit_test(position_is_clamped),
        cmocka_unit_test(frac_and_time_format),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
