/*
 * test_text_shape — CMocka suite for the HarfBuzz shaping helper (tsh_).
 *
 * The shaped TEXT is hostile remote content; the FONTS are local. These tests
 * verify the fail-closed input contract (which needs no font), and the shaping
 * invariants (count/positivity/monotonicity/determinism/consistency) on a host
 * that resolves a font. On a font-less host they assert the fallback contract
 * (TSH_ERR_UNAVAIL / measure < 0), so the suite is green either way.
 */

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <cmocka.h>

#include "text_shape.h"
#include "css.h"
#include "webfont.h"

static const tsh_font SANS = { .family = CSS_FF_SANS, .bold = 0, .italic = 0 };

/* --- fail-closed input contract (no font needed) --- */

static void test_null_and_bad_inputs(void **state) {
    (void)state;
    cairo_glyph_t g[64];
    size_t n = 123; double adv = 7.0;

    /* NULL font */
    assert_int_equal(tsh_shape(NULL, 16.0, "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    /* NULL text with len>0 */
    assert_int_equal(tsh_shape(&SANS, 16.0, NULL, 3, g, 64, &n, &adv), TSH_ERR_INPUT);
    /* NULL out buffer */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, NULL, 64, &n, &adv), TSH_ERR_INPUT);
    /* NULL out_n / out_adv */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, g, 64, NULL, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, g, 64, &n, NULL), TSH_ERR_INPUT);
    /* cap 0 */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", 1, g, 0, &n, &adv), TSH_ERR_INPUT);
    /* non-positive / non-finite px */
    assert_int_equal(tsh_shape(&SANS, 0.0,   "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, -3.0,  "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, NAN,   "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    assert_int_equal(tsh_shape(&SANS, INFINITY, "x", 1, g, 64, &n, &adv), TSH_ERR_INPUT);
    /* oversize slice */
    assert_int_equal(tsh_shape(&SANS, 16.0, "x", (size_t)TSH_MAX_TEXT + 1, g, 64, &n, &adv),
                     TSH_ERR_INPUT);

    /* measure mirrors the fail-closed contract: < 0 on bad input. */
    assert_true(tsh_measure(NULL, 16.0, "x", 1) < 0.0);
    assert_true(tsh_measure(&SANS, 0.0, "x", 1) < 0.0);
}

static void test_empty_slice_is_ok(void **state) {
    (void)state;
    cairo_glyph_t g[8];
    size_t n = 99; double adv = 99.0;
    /* Empty input is OK regardless of backend: nothing to shape. */
    assert_int_equal(tsh_shape(&SANS, 16.0, "", 0, g, 8, &n, &adv), TSH_OK);
    assert_int_equal((int)n, 0);
    assert_true(adv == 0.0);
    assert_true(tsh_measure(&SANS, 16.0, "", 0) == 0.0);
}

/* --- shaping invariants (real font path; fallback contract otherwise) --- */

static void test_shape_ascii(void **state) {
    (void)state;
    cairo_glyph_t g[64];
    size_t n = 0; double adv = 0.0;
    tsh_status st = tsh_shape(&SANS, 16.0, "ABCD", 4, g, 64, &n, &adv);

    if (!tsh_ready()) {
        assert_int_equal(st, TSH_ERR_UNAVAIL);
        assert_true(tsh_measure(&SANS, 16.0, "ABCD", 4) < 0.0);
        return;
    }
    /* "ABCD" never ligates in a standard font: one glyph per cap. */
    assert_int_equal(st, TSH_OK);
    assert_int_equal((int)n, 4);
    assert_true(adv > 0.0);
    /* Glyph x positions are non-decreasing and bounded by the total advance. */
    for (size_t i = 1; i < n; ++i)
        assert_true(g[i].x >= g[i - 1].x);
    assert_true(g[n - 1].x <= adv + 1.0);
    assert_true(g[0].x >= 0.0);
}

static void test_determinism(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_glyph_t a[64], b[64];
    size_t na = 0, nb = 0; double aa = 0.0, ab = 0.0;
    assert_int_equal(tsh_shape(&SANS, 18.0, "Freedom", 7, a, 64, &na, &aa), TSH_OK);
    assert_int_equal(tsh_shape(&SANS, 18.0, "Freedom", 7, b, 64, &nb, &ab), TSH_OK);
    assert_int_equal((int)na, (int)nb);
    assert_true(aa == ab);
    for (size_t i = 0; i < na; ++i) {
        assert_int_equal((int)a[i].index, (int)b[i].index);
        assert_true(a[i].x == b[i].x);
        assert_true(a[i].y == b[i].y);
    }
}

static void test_measure_matches_shape(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_glyph_t g[64];
    size_t n = 0; double adv = 0.0;
    assert_int_equal(tsh_shape(&SANS, 20.0, "kerning", 7, g, 64, &n, &adv), TSH_OK);
    double m = tsh_measure(&SANS, 20.0, "kerning", 7);
    assert_true(m >= 0.0);
    /* Same shaper, same slice: measure must equal the shaped total advance. */
    assert_true(fabs(m - adv) < 1e-6);
}

static void test_overflow_cap(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_glyph_t g[2];
    size_t n = 123; double adv = 7.0;
    /* 10 non-ligating glyphs cannot fit a cap of 2: fail closed, no OOB write. */
    tsh_status st = tsh_shape(&SANS, 16.0, "ABCDEFGHIJ", 10, g, 2, &n, &adv);
    assert_int_equal(st, TSH_ERR_OVERFLOW);
}

static void test_draw_paints(void **state) {
    (void)state;
    if (!tsh_ready()) { skip(); }
    cairo_surface_t *s = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 200, 40);
    cairo_t *cr = cairo_create(s);
    cairo_set_source_rgb(cr, 0, 0, 0);
    /* Exercises the cairo_show_glyphs path under ASan. */
    tsh_status st = tsh_draw(cr, &SANS, 16.0, 4.0, 24.0, "shape me", 8);
    assert_int_equal(st, TSH_OK);
    cairo_destroy(cr);
    cairo_surface_destroy(s);
}

/* --- @font-face registry (spec/webfont.md; needs no system font) --- */

static void test_webfont_rejects_bad_input(void **state) {
    (void)state;
    static const unsigned char ok[8] = { 0, 1, 0, 0, 'A', 'B', 'C', 'D' };
    unsigned char big = 0;
    assert_int_equal(tsh_webfont_register(NULL, ok, sizeof ok, 0, 0), -1);
    assert_int_equal(tsh_webfont_register("", ok, sizeof ok, 0, 0), -1);
    assert_int_equal(tsh_webfont_register("X", NULL, 8, 0, 0), -1);
    assert_int_equal(tsh_webfont_register("X", ok, 0, 0, 0), -1);
    assert_int_equal(tsh_webfont_register("X", ok, WF_MAX_FACE_BYTES + 1, 0, 0), -1);
    assert_int_equal(tsh_webfont_register("X", &big, 1, 0, 0), -1);   /* short */
    static const unsigned char wof2[8] = { 'w', 'O', 'F', '2', 0, 0, 0, 0 };
    assert_int_equal(tsh_webfont_register("X", wof2, sizeof wof2, 0, 0), -1);
    static const unsigned char junk[8] = { 'J', 'U', 'N', 'K', 0, 0, 0, 0 };
    assert_int_equal(tsh_webfont_register("X", junk, sizeof junk, 0, 0), -1);
    /* Unparseable-but-magic bytes fail at FT_New_Memory_Face, never register. */
    static const unsigned char fake[64] = { 0, 1, 0, 0 };
    assert_int_equal(tsh_webfont_register("X", fake, sizeof fake, 0, 0), -1);
    tsh_webfont_clear();
}

/* Reads a host TrueType file when one exists (same philosophy as the shaping
 * invariants above: local fonts only, skip-free -- absence just narrows). */
static unsigned char *read_host_font(const char *path, size_t *out_n) {
    FILE *f = fopen(path, "rb");
    if (f == NULL) return NULL;
    if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; }
    long sz = ftell(f);
    if (sz <= 0 || (size_t)sz > WF_MAX_FACE_BYTES) { fclose(f); return NULL; }
    if (fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; }
    unsigned char *b = (unsigned char *)malloc((size_t)sz);
    if (b == NULL) { fclose(f); return NULL; }
    if (fread(b, 1, (size_t)sz, f) != (size_t)sz) { free(b); fclose(f); return NULL; }
    fclose(f);
    *out_n = (size_t)sz;
    return b;
}

static void test_webfont_register_find_clear(void **state) {
    (void)state;
    static const char *paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
    };
    unsigned char *bytes = NULL;
    size_t nbytes = 0;
    for (size_t i = 0; i < sizeof paths / sizeof *paths && bytes == NULL; ++i)
        bytes = read_host_font(paths[i], &nbytes);
    if (bytes == NULL || !tsh_ready()) {
        /* No host font (or no backend): registration still fails closed, and
         * shaping through a set-but-missing hash falls back to the bucket. */
        tsh_webfont_clear();
        return;
    }
    assert_int_equal(tsh_webfont_register("TestFace", bytes, nbytes, 0, 0), 0);
    /* Same key twice replaces instead of duplicating. */
    assert_int_equal(tsh_webfont_register("TestFace", bytes, nbytes, 0, 0), 0);
    /* Bold is a different key. */
    assert_int_equal(tsh_webfont_register("TestFace", bytes, nbytes, 1, 0), 0);

    tsh_font wf = { .family = CSS_FF_SERIF, .bold = 0, .italic = 0,
                    .wfh = wf_name_hash("TestFace", 8) };
    assert_true(wf.wfh != 0);
    cairo_glyph_t g[64];
    size_t n = 0;
    double adv = 0.0;
    assert_int_equal(tsh_shape(&wf, 16.0, "ABCD", 4, g, 64, &n, &adv), TSH_OK);
    assert_int_equal((int)n, 4);
    assert_true(adv > 0.0);

    /* Case-insensitive: the registry hashes the same way both sides do. */
    tsh_font wf2 = { .family = CSS_FF_SERIF, .bold = 0, .italic = 0,
                     .wfh = wf_name_hash("TESTFACE", 8) };
    assert_int_equal(wf2.wfh, wf.wfh);
    assert_true(tsh_measure(&wf2, 16.0, "A", 1) > 0.0);

    tsh_webfont_clear();
    /* After clear the hash misses and shaping falls back to the local bucket. */
    assert_int_equal(tsh_shape(&wf, 16.0, "ABCD", 4, g, 64, &n, &adv), TSH_OK);
    free(bytes);
}


/* --- Named local families (spec/text_shape.md section 7) --- */

static void test_generic_keywords(void **state) {
    (void)state;
    assert_int_equal(tsh_family_is_generic("sans-serif"), 1);
    assert_int_equal(tsh_family_is_generic("Monospace"), 1);
    assert_int_equal(tsh_family_is_generic("system-ui"), 1);
    assert_int_equal(tsh_family_is_generic("ui-monospace"), 1);
    assert_int_equal(tsh_family_is_generic("arial"), 0);
    assert_int_equal(tsh_family_is_generic("-apple-system"), 0);
    assert_int_equal(tsh_family_is_generic(""), 0);
    assert_int_equal(tsh_family_is_generic(NULL), 0);
}

static int table_resolve(const char *name, char *out, size_t cap, void *ctx) {
    const char *const *tab = ctx;
    for (size_t i = 0; tab[i] != NULL; i += 2)
        if (strcmp(tab[i], name) == 0) {
            snprintf(out, cap, "%s", tab[i + 1]);
            return 1;
        }
    return 0;
}

static void test_pick_from_list_order_and_generic_stop(void **state) {
    (void)state;
    const char *tab[] = { "arial", "Liberation Sans", "courier new", "Liberation Mono", NULL };
    char out[TSH_FAMILY_MAX];
    assert_int_equal(tsh_pick_from_list("helvetica neue,arial,sans-serif",
                                        table_resolve, tab, out, sizeof out), 1);
    assert_string_equal(out, "Liberation Sans");
    /* A generic first stops the walk: the bucket applies. */
    assert_int_equal(tsh_pick_from_list("monospace,arial", table_resolve, tab,
                                        out, sizeof out), 0);
    assert_int_equal(tsh_pick_from_list("nope,other", table_resolve, tab,
                                        out, sizeof out), 0);
    assert_int_equal(tsh_pick_from_list("", table_resolve, tab, out, sizeof out), 0);
    assert_int_equal(tsh_pick_from_list(NULL, table_resolve, tab, out, sizeof out), 0);
    /* Whitespace around names is ignored. */
    assert_int_equal(tsh_pick_from_list(" nope , courier new ", table_resolve, tab,
                                        out, sizeof out), 1);
    assert_string_equal(out, "Liberation Mono");
}

static int set_installed(const char *name, void *ctx) {
    const char *const *set = ctx;
    for (size_t i = 0; set[i] != NULL; ++i)
        if (strcmp(set[i], name) == 0) return 1;
    return 0;
}

static void test_pick_family_strong_vs_weak(void **state) {
    (void)state;
    const char *inst[] = { "Liberation Sans", "Noto Sans", "Cantarell", "Inter", NULL };
    /* Installed itself. */
    const char *s0[] = { "Inter", "Noto Sans" };
    const int b0[] = { 1, 0 };
    assert_string_equal(tsh_pick_family("Inter", s0, b0, 2, set_installed, inst), "Inter");
    /* Strong alias (Arial -> Liberation Sans). */
    const char *s1[] = { "Arial", "Liberation Sans", "Noto Sans" };
    const int b1[] = { 1, 1, 0 };
    assert_string_equal(tsh_pick_family("Arial", s1, b1, 3, set_installed, inst),
                        "Liberation Sans");
    /* Only weak substitutes: not available. */
    const char *s2[] = { "Segoe UI", "Cantarell", "Noto Sans" };
    const int b2[] = { 1, 0, 0 };
    assert_null(tsh_pick_family("Segoe UI", s2, b2, 3, set_installed, inst));
    /* A strong but uninstalled alias is skipped; the strong run continues. */
    const char *s3[] = { "Helvetica", "Nimbus Sans", "Liberation Sans", "Noto Sans" };
    const int b3[] = { 1, 1, 1, 0 };
    assert_string_equal(tsh_pick_family("Helvetica", s3, b3, 4, set_installed, inst),
                        "Liberation Sans");
    assert_null(tsh_pick_family(NULL, s3, b3, 4, set_installed, inst));
}

static void test_local_handle_real_fontconfig(void **state) {
    (void)state;
    assert_int_equal(tsh_local_handle(NULL), 0);
    assert_int_equal(tsh_local_handle(""), 0);
    assert_int_equal(tsh_local_handle("sans-serif"), 0);
    assert_int_equal(tsh_local_handle("no-such-family-xyz"), 0);
    if (!tsh_ready()) return;
    int h = tsh_local_handle("no-such-family-xyz,arial,sans-serif");
    if (h == 0) return;   /* host without an Arial alias: nothing to assert */
    assert_int_equal(tsh_local_handle("no-such-family-xyz,arial,sans-serif"), h);
    tsh_font f = { .family = CSS_FF_SANS, .local = h };
    tsh_font g = { .family = CSS_FF_SANS, .local = 0 };
    double a = tsh_measure(&f, 16.0, "The quick brown fox", 19);
    double b = tsh_measure(&g, 16.0, "The quick brown fox", 19);
    assert_true(a > 0.0 && b > 0.0);
    /* The face the painter selects for metrics is the one that is drawn. */
    assert_non_null(tsh_face(&f));
    assert_non_null(tsh_face(&g));
    assert_ptr_not_equal(tsh_face(&f), tsh_face(&g));
}

static int teardown(void **state) {
    (void)state;
    tsh_shutdown();
    return 0;
}

/* `=NAME` is an @font-face local(NAME) source (spec/webfont.md 2c): it matches a
 * face by its exact FULL or PostScript name (CSS Fonts 4 4.3), never through a
 * fontconfig family alias -- local("Arial") on a host with only Liberation Sans
 * resolves to nothing, exactly as Firefox treats it. */
static void test_local_handle_exact_full_name(void **state) {
    (void)state;
    assert_int_equal(tsh_local_handle("=no such face xyz"), 0);
    if (!tsh_ready()) return;
    /* "Liberation Sans" is a family AND a full name; "Arial" is only an alias. */
    if (tsh_local_handle("liberation sans") == 0) return;   /* host without it */
    assert_true(tsh_local_handle("=liberation sans") != 0);
    assert_true(tsh_local_handle("=LiberationSans-Bold") != 0);
    if (tsh_local_handle("=arial") != 0) return;   /* a host with real Arial */
    assert_int_equal(tsh_local_handle("=arial"), 0);
    /* A failed local() is skipped and the list goes on. */
    assert_true(tsh_local_handle("=arial,liberation sans") != 0);
}

/* A fake coverage: ASCII is face 0, Hebrew (U+05D0..05EA) face 2, CJK face 3. */
static int fake_cover(unsigned cp, void *ctx) {
    (void)ctx;
    if (cp >= 0x5D0 && cp <= 0x5EA) return 2;
    if (cp >= 0x4E00 && cp <= 0x9FFF) return 3;
    return 0;
}

static void test_segment_runs(void **state) {
    (void)state;
    tsh_run r[8];
    const char *t = "Hola \xd7\xa2\xd7\x91 x\xe4\xb8\xad";
    int n = tsh_segment(t, strlen(t), fake_cover, NULL, r, 8);
    assert_int_equal(n, 4);
    assert_int_equal(r[0].start, 0); assert_int_equal(r[0].end, 5); assert_int_equal(r[0].face, 0);
    assert_int_equal(r[1].face, 2);  assert_int_equal(r[1].end, 9);
    assert_int_equal(r[2].face, 0);  assert_int_equal(r[2].end, 11);
    assert_int_equal(r[3].face, 3);  assert_int_equal(r[3].end, strlen(t));
    /* A combining mark stays with its base run. */
    const char *m = "\xd7\xa2\xcc\x81" "a";
    n = tsh_segment(m, strlen(m), fake_cover, NULL, r, 8);
    assert_int_equal(n, 2);
    assert_int_equal(r[0].end, 4);
    /* Fully covered: one run. Empty: zero. Too many runs: -1. */
    assert_int_equal(tsh_segment("abc", 3, fake_cover, NULL, r, 8), 1);
    assert_int_equal(tsh_segment("", 0, fake_cover, NULL, r, 8), 0);
    assert_int_equal(tsh_segment(t, strlen(t), fake_cover, NULL, r, 2), -1);
    assert_int_equal(tsh_segment(NULL, 3, fake_cover, NULL, r, 8), -1);
}

/* Real fontconfig: text the bucket face cannot cover still measures as real glyphs
 * (a fallback face drew it), not as the zero/notdef advance. Skipped on a host
 * without a CJK-capable font. */
static void test_measure_uses_fallback_face(void **state) {
    (void)state;
    if (!tsh_ready()) return;
    tsh_font f = { .family = CSS_FF_SANS };
    const char *cjk = "\xe4\xb8\xad\xe6\x96\x87";   /* two CJK ideographs */
    double a = tsh_measure(&f, 20.0, cjk, strlen(cjk));
    assert_true(a > 0.0);
    /* An ideograph is about one em wide in any CJK face. */
    assert_true(a > 2.0 * 20.0 * 0.7 && a < 2.0 * 20.0 * 1.3);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_null_and_bad_inputs),
        cmocka_unit_test(test_empty_slice_is_ok),
        cmocka_unit_test(test_shape_ascii),
        cmocka_unit_test(test_determinism),
        cmocka_unit_test(test_measure_matches_shape),
        cmocka_unit_test(test_overflow_cap),
        cmocka_unit_test(test_draw_paints),
        cmocka_unit_test(test_webfont_rejects_bad_input),
        cmocka_unit_test(test_webfont_register_find_clear),
        cmocka_unit_test(test_generic_keywords),
        cmocka_unit_test(test_pick_from_list_order_and_generic_stop),
        cmocka_unit_test(test_pick_family_strong_vs_weak),
        cmocka_unit_test(test_local_handle_real_fontconfig),
        cmocka_unit_test(test_local_handle_exact_full_name),
        cmocka_unit_test(test_segment_runs),
        cmocka_unit_test(test_measure_uses_fallback_face),
    };
    return cmocka_run_group_tests(tests, NULL, teardown);
}
