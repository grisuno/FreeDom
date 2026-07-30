/* tests/test_svg_render.c — CMocka suite for the pure inline-SVG parser (sv_).
 *
 * The parser sees hostile bytes, so the suite locks BOTH halves of the contract:
 * what it must render (spec/svg_render.md §3) and what it must never do -- resolve
 * a URL-bearing element, exceed a bound, or leave a half-filled image behind. */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <cmocka.h>

#include "svg_render.h"

static sv_image *img_new(void) {
    sv_image *im = (sv_image *)calloc(1, sizeof *im);
    assert_non_null(im);
    return im;
}

static sv_status parse(sv_image *im, const char *s) {
    return sv_parse(s, strlen(s), im);
}

static void test_null_args(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(sv_parse(NULL, 5, im), SV_ERR_NULL_ARG);
    assert_int_equal(sv_parse("<svg/>", 6, NULL), SV_ERR_NULL_ARG);
    free(im);
}

static void test_empty_and_garbage_do_not_parse(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im, ""), SV_ERR_PARSE);
    assert_int_equal(parse(im, "not markup at all"), SV_ERR_PARSE);
    assert_int_equal(parse(im, "<svg></svg>"), SV_ERR_PARSE);   /* no shapes */
    assert_int_equal(im->nshape, 0);
    free(im);
}

/* Dimensions: explicit width/height win; viewBox alone supplies them; neither
 * falls back to the CSS default replaced size. */
static void test_dimensions_and_viewbox(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg width=\"64\" height=\"32\" viewBox=\"0 0 24 12\"><rect width=\"1\" height=\"1\"/></svg>"),
        SV_OK);
    assert_true(fabs(im->width - 64.0) < 0.01);
    assert_true(fabs(im->height - 32.0) < 0.01);
    assert_true(im->has_viewbox);
    assert_true(fabs(im->vb_w - 24.0) < 0.01);

    assert_int_equal(parse(im, "<svg viewBox=\"0 0 40 20\"><rect width=\"1\" height=\"1\"/></svg>"), SV_OK);
    assert_true(fabs(im->width - 40.0) < 0.01);
    assert_true(fabs(im->height - 20.0) < 0.01);

    assert_int_equal(parse(im, "<svg><rect width=\"1\" height=\"1\"/></svg>"), SV_OK);
    assert_true(fabs(im->width - SV_DEFAULT_W) < 0.01);
    assert_true(fabs(im->height - SV_DEFAULT_H) < 0.01);
    free(im);
}

static void test_basic_shapes(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg width=\"100\" height=\"100\">"
        "<rect x=\"1\" y=\"2\" width=\"3\" height=\"4\"/>"
        "<circle cx=\"5\" cy=\"6\" r=\"7\"/>"
        "<ellipse cx=\"8\" cy=\"9\" rx=\"10\" ry=\"11\"/>"
        "<line x1=\"12\" y1=\"13\" x2=\"14\" y2=\"15\"/>"
        "</svg>"), SV_OK);
    assert_int_equal(im->nshape, 4);
    assert_int_equal(im->shapes[0].kind, SV_RECT);
    assert_true(fabs(im->shapes[0].a - 1.0) < 0.01);
    assert_true(fabs(im->shapes[0].d - 4.0) < 0.01);
    assert_int_equal(im->shapes[1].kind, SV_CIRCLE);
    assert_true(fabs(im->shapes[1].c - 7.0) < 0.01);
    assert_int_equal(im->shapes[2].kind, SV_ELLIPSE);
    assert_true(fabs(im->shapes[2].d - 11.0) < 0.01);
    assert_int_equal(im->shapes[3].kind, SV_LINE);
    assert_true(fabs(im->shapes[3].d - 15.0) < 0.01);
    free(im);
}

/* SVG painting defaults: fill is black, stroke is none. An explicit fill="none"
 * disables the fill without turning it black. */
static void test_paint_attributes(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg><rect width=\"1\" height=\"1\"/>"
        "<rect width=\"1\" height=\"1\" fill=\"#ff0000\" stroke=\"#00ff00\" stroke-width=\"3\"/>"
        "<rect width=\"1\" height=\"1\" fill=\"none\"/>"
        "<rect width=\"1\" height=\"1\" style=\"fill:#0000ff;stroke-width:5\"/>"
        "</svg>"), SV_OK);
    assert_int_equal(im->nshape, 4);
    assert_int_equal(im->shapes[0].fill, 0x000000);
    assert_int_equal(im->shapes[0].stroke, -1);
    assert_int_equal(im->shapes[1].fill, 0xff0000);
    assert_int_equal(im->shapes[1].stroke, 0x00ff00);
    assert_true(fabs(im->shapes[1].stroke_w - 3.0) < 0.01);
    assert_int_equal(im->shapes[2].fill, -1);
    assert_int_equal(im->shapes[3].fill, 0x0000ff);
    assert_true(fabs(im->shapes[3].stroke_w - 5.0) < 0.01);
    free(im);
}

/* <g> passes presentation attributes down and composes its transform. */
static void test_group_inheritance_and_transform(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg><g fill=\"#123456\" transform=\"translate(10,20)\">"
        "<rect width=\"1\" height=\"1\"/>"
        "<g transform=\"scale(2)\"><circle r=\"3\"/></g>"
        "</g><rect width=\"1\" height=\"1\"/></svg>"), SV_OK);
    assert_int_equal(im->nshape, 3);
    assert_int_equal(im->shapes[0].fill, 0x123456);
    assert_true(fabs(im->shapes[0].m[4] - 10.0) < 0.01);   /* x0 */
    assert_true(fabs(im->shapes[0].m[5] - 20.0) < 0.01);   /* y0 */
    assert_int_equal(im->shapes[1].fill, 0x123456);        /* inherited two levels */
    assert_true(fabs(im->shapes[1].m[0] - 2.0) < 0.01);    /* composed scale */
    assert_true(fabs(im->shapes[1].m[4] - 10.0) < 0.01);   /* under the translate */
    /* The sibling outside the group is untouched by either. */
    assert_int_equal(im->shapes[2].fill, 0x000000);
    assert_true(fabs(im->shapes[2].m[0] - 1.0) < 0.01);
    assert_true(fabs(im->shapes[2].m[4]) < 0.01);
    free(im);
}

static void test_polygon_points(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg><polygon points=\"1,2 3,4 5,6\"/>"
        "<polyline points=\"7 8, 9 10\"/></svg>"), SV_OK);
    assert_int_equal(im->nshape, 2);
    assert_int_equal(im->shapes[0].kind, SV_POLYGON);
    assert_int_equal(im->shapes[0].count, 3);
    assert_true(fabs(im->px[im->shapes[0].first] - 1.0) < 0.01);
    assert_true(fabs(im->py[im->shapes[0].first + 2] - 6.0) < 0.01);
    assert_int_equal(im->shapes[1].kind, SV_POLYLINE);
    assert_int_equal(im->shapes[1].count, 2);
    assert_true(fabs(im->px[im->shapes[1].first + 1] - 9.0) < 0.01);
    free(im);
}

/* Path data: absolute and relative moves/lines, a cubic, and the implicit
 * repeat of the previous command when coordinates keep coming. */
static void test_path_commands(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg><path d=\"M 10 20 L 30 40 l 5 5 H 50 V 60 Z\"/></svg>"), SV_OK);
    assert_int_equal(im->nshape, 1);
    assert_int_equal(im->shapes[0].kind, SV_PATH);
    const sv_seg *sg = &im->segs[im->shapes[0].first];
    assert_int_equal(sg[0].verb, SV_MOVE);
    assert_true(fabs(sg[0].x[0] - 10.0) < 0.01);
    assert_int_equal(sg[1].verb, SV_LINETO);
    assert_true(fabs(sg[1].x[0] - 30.0) < 0.01);
    assert_int_equal(sg[2].verb, SV_LINETO);
    assert_true(fabs(sg[2].x[0] - 35.0) < 0.01);   /* relative l 5 5 */
    assert_int_equal(sg[3].verb, SV_LINETO);
    assert_true(fabs(sg[3].x[0] - 50.0) < 0.01);   /* H 50 keeps y */
    assert_true(fabs(sg[3].y[0] - 45.0) < 0.01);
    assert_int_equal(sg[4].verb, SV_LINETO);
    assert_true(fabs(sg[4].y[0] - 60.0) < 0.01);   /* V 60 keeps x */
    assert_int_equal(sg[5].verb, SV_CLOSE);

    /* A cubic stays a cubic; a quadratic is converted into one. */
    assert_int_equal(parse(im, "<svg><path d=\"M0 0 C 1 2 3 4 5 6\"/></svg>"), SV_OK);
    assert_int_equal(im->segs[im->shapes[0].first + 1].verb, SV_CUBIC);
    assert_true(fabs(im->segs[im->shapes[0].first + 1].x[2] - 5.0) < 0.01);
    assert_int_equal(parse(im, "<svg><path d=\"M0 0 Q 3 0 6 6\"/></svg>"), SV_OK);
    assert_int_equal(im->segs[im->shapes[0].first + 1].verb, SV_CUBIC);
    assert_true(fabs(im->segs[im->shapes[0].first + 1].x[2] - 6.0) < 0.01);
    free(im);
}

/* An arc must become cubics that actually land on the requested end point --
 * the failure mode that matters is a path that silently goes somewhere else. */
static void test_path_arc_reaches_endpoint(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im, "<svg><path d=\"M 0 0 A 10 10 0 0 1 20 0\"/></svg>"), SV_OK);
    const sv_shape *sh = &im->shapes[0];
    assert_true(sh->count >= 2);
    const sv_seg *last = &im->segs[sh->first + sh->count - 1];
    assert_int_equal(last->verb, SV_CUBIC);
    assert_true(fabs(last->x[2] - 20.0) < 0.5);
    assert_true(fabs(last->y[2] - 0.0) < 0.5);
    free(im);
}

/* THE security lock: no element that could name a resource is ever turned into a
 * shape, and its content is dropped with it. If this ever regresses, inline SVG
 * would become a fetch surface. */
static void test_url_bearing_elements_are_dropped(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg>"
        "<image href=\"https://tracker.example/p.png\" width=\"10\" height=\"10\"/>"
        "<use xlink:href=\"#icon\"/>"
        "<script>fetch('https://tracker.example')</script>"
        "<style>rect{fill:url(https://tracker.example/g)}</style>"
        "<foreignObject><img src=\"https://tracker.example/x\"></foreignObject>"
        "</svg>"), SV_ERR_PARSE);
    assert_int_equal(im->nshape, 0);

    /* A legitimate shape alongside them still renders; the URL ones still do not. */
    assert_int_equal(parse(im,
        "<svg><image href=\"https://tracker.example/p.png\"/>"
        "<rect width=\"5\" height=\"5\"/></svg>"), SV_OK);
    assert_int_equal(im->nshape, 1);
    assert_int_equal(im->shapes[0].kind, SV_RECT);
    free(im);
}

/* Bounds hold under a hostile document, and a rejected oversize input leaves the
 * image empty rather than partly filled. */
static void test_bounds_are_enforced(void **state) {
    (void)state;
    sv_image *im = img_new();

    size_t n = SV_MAX_SHAPES + 64;
    size_t cap = 64 + n * 32;
    char *buf = (char *)calloc(1, cap);
    assert_non_null(buf);
    size_t o = (size_t)snprintf(buf, cap, "<svg>");
    for (size_t i = 0; i < n && o + 32 < cap; ++i)
        o += (size_t)snprintf(buf + o, cap - o, "<rect width=\"1\" height=\"1\"/>");
    snprintf(buf + o, cap - o, "</svg>");
    assert_int_equal(sv_parse(buf, strlen(buf), im), SV_OK);
    assert_true(im->nshape <= SV_MAX_SHAPES);
    free(buf);

    /* Deep <g> nesting past the depth cap must not recurse without bound. */
    size_t deep_cap = (SV_MAX_DEPTH + 40) * 8 + 64;
    char *deep = (char *)calloc(1, deep_cap);
    assert_non_null(deep);
    size_t d = (size_t)snprintf(deep, deep_cap, "<svg>");
    for (int i = 0; i < SV_MAX_DEPTH + 20 && d + 8 < deep_cap; ++i)
        d += (size_t)snprintf(deep + d, deep_cap - d, "<g>");
    snprintf(deep + d, deep_cap - d, "<rect width=\"1\" height=\"1\"/></svg>");
    (void)sv_parse(deep, strlen(deep), im);   /* must return, not smash the stack */
    free(deep);

    char *big = (char *)calloc(1, SV_MAX_INPUT + 16);
    assert_non_null(big);
    memset(big, 'a', SV_MAX_INPUT + 8);
    assert_int_equal(sv_parse(big, SV_MAX_INPUT + 8, im), SV_ERR_LIMIT);
    assert_int_equal(im->nshape, 0);
    free(big);
    free(im);
}

/* Malformed attribute values degrade to the default and never poison the shape. */
static void test_malformed_values_degrade(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg width=\"abc\"><rect x=\"zzz\" width=\"10\" height=\"10\" "
        "fill=\"notacolor\" stroke-width=\"-\"/></svg>"), SV_OK);
    assert_int_equal(im->nshape, 1);
    assert_true(fabs(im->shapes[0].a) < 0.01);          /* x fell back to 0 */
    assert_true(fabs(im->shapes[0].c - 10.0) < 0.01);   /* width survived */
    assert_true(fabs(im->width - SV_DEFAULT_W) < 0.01); /* bad width -> default */

    /* An unterminated tag / truncated document must terminate cleanly. */
    assert_true(parse(im, "<svg><rect width=\"1\"") == SV_OK ||
                parse(im, "<svg><rect width=\"1\"") == SV_ERR_PARSE);
    assert_true(parse(im, "<svg><path d=\"M 0 0 C 1\"/></svg>") == SV_OK ||
                parse(im, "<svg><path d=\"M 0 0 C 1\"/></svg>") == SV_ERR_PARSE);
    free(im);
}

static void test_text_element(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg><text x=\"10\" y=\"40\" font-size=\"28\" fill=\"#334455\">Hi there</text></svg>"),
        SV_OK);
    assert_int_equal(im->nshape, 1);
    assert_int_equal(im->shapes[0].kind, SV_TEXT);
    assert_true(fabs(im->shapes[0].b - 40.0) < 0.01);
    assert_true(fabs(im->shapes[0].c - 28.0) < 0.01);
    assert_int_equal(im->shapes[0].fill, 0x334455);
    assert_string_equal(im->shapes[0].text, "Hi there");
    free(im);
}

/* sv_fit maps user space onto the destination rect uniformly and centred. */
static void test_fit_uniform_and_centered(void **state) {
    (void)state;
    sv_image *im = img_new();
    assert_int_equal(parse(im,
        "<svg width=\"24\" height=\"24\" viewBox=\"0 0 24 24\"><rect width=\"1\" height=\"1\"/></svg>"),
        SV_OK);
    double sc = 0, ox = 0, oy = 0;
    sv_fit(im, 48.0, 48.0, &sc, &ox, &oy);
    assert_true(fabs(sc - 2.0) < 0.01);
    assert_true(fabs(ox) < 0.01 && fabs(oy) < 0.01);

    /* Non-square destination: uniform scale from the tighter axis, centred on the other. */
    sv_fit(im, 96.0, 48.0, &sc, &ox, &oy);
    assert_true(fabs(sc - 2.0) < 0.01);
    assert_true(fabs(ox - 24.0) < 0.01);
    assert_true(fabs(oy) < 0.01);

    /* A degenerate viewBox must not divide by zero. */
    assert_int_equal(parse(im, "<svg viewBox=\"0 0 0 0\"><rect width=\"1\" height=\"1\"/></svg>"), SV_OK);
    sv_fit(im, 10.0, 10.0, &sc, &ox, &oy);
    assert_true(sc > 0.0);
    free(im);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_args),
        cmocka_unit_test(test_empty_and_garbage_do_not_parse),
        cmocka_unit_test(test_dimensions_and_viewbox),
        cmocka_unit_test(test_basic_shapes),
        cmocka_unit_test(test_paint_attributes),
        cmocka_unit_test(test_group_inheritance_and_transform),
        cmocka_unit_test(test_polygon_points),
        cmocka_unit_test(test_path_commands),
        cmocka_unit_test(test_path_arc_reaches_endpoint),
        cmocka_unit_test(test_url_bearing_elements_are_dropped),
        cmocka_unit_test(test_bounds_are_enforced),
        cmocka_unit_test(test_malformed_values_degrade),
        cmocka_unit_test(test_text_element),
        cmocka_unit_test(test_fit_uniform_and_centered),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
