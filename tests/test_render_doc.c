/*
 * TDD suite for render_doc — paint-ready document model.
 *
 * Pure: builds pv_view display lists directly (pv_new/pv_append/pv_append_image)
 * and asserts on the rd_doc that rd_build produces, including the image gate
 * decisions and the tracking-warning notice. No I/O.
 *
 * Build: make test   ;   ASan: make asan
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "page_view.h"
#include "render_doc.h"
#include "render_policy.h"

static const char TOP[] = "https://example.com/";

static rdp_caps caps_images_on(void) {
    rdp_caps c = rdp_caps_safe();
    c.images = true;
    return c;
}

/* First block of a given kind, or NULL. */
static const rd_block *first_kind(const rd_doc *d, rd_kind k) {
    for (size_t i = 0; i < rd_count(d); ++i) {
        if (rd_at(d, i)->kind == k) return rd_at(d, i);
    }
    return NULL;
}

/* --- argument / empty handling --- */

static void test_build_null_out(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, NULL), RD_ERR_NULL_ARG);
    pv_free(v);
}

static void test_build_null_view_is_empty(void **state) {
    (void)state;
    rd_doc *d = NULL;
    assert_int_equal(rd_build(NULL, rdp_caps_safe(), TOP, &d), RD_OK);
    assert_non_null(d);
    assert_int_equal((int)rd_count(d), 0);
    assert_int_equal(d->has_images, 0);
    assert_null(rd_at(d, 0));
    rd_free(d);
}

/* --- structural mapping --- */

static void test_heading_paragraph_link(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 2, 1, "Title", NULL), PV_OK);
    assert_int_equal(pv_append(v, PV_TEXT, 0, 1, "body text", NULL), PV_OK);
    assert_int_equal(pv_append(v, PV_LINK, 0, 0, "click", "https://e.example/x"), PV_OK);

    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK);
    assert_int_equal((int)rd_count(d), 3);

    const rd_block *h = rd_at(d, 0);
    assert_int_equal(h->kind, RD_HEADING);
    assert_int_equal(h->heading_level, 2);
    assert_string_equal(h->text, "Title");

    const rd_block *p = rd_at(d, 1);
    assert_int_equal(p->kind, RD_PARAGRAPH);
    assert_int_equal(p->heading_level, 0);

    const rd_block *l = rd_at(d, 2);
    assert_int_equal(l->kind, RD_LINK);
    assert_string_equal(l->href, "https://e.example/x");

    rd_free(d);
    pv_free(v);
}

/* --- images off (default): a notice is prepended and the image is blocked --- */

static void test_image_off_emits_notice_and_blocked(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "intro", NULL), PV_OK);
    assert_int_equal(pv_append_image(v, 0, 1, "Logo", "https://example.com/l.png", 200, 80), PV_OK);

    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK);
    assert_int_equal(d->has_images, 1);

    /* The notice comes first and mentions tracking. */
    const rd_block *notice = rd_at(d, 0);
    assert_int_equal(notice->kind, RD_NOTICE);
    assert_non_null(strstr(notice->text, "track"));

    const rd_block *img = first_kind(d, RD_IMAGE);
    assert_non_null(img);
    assert_int_equal(img->img_decision, RDP_IMG_BLOCK_DISABLED);
    assert_string_equal(img->href, "https://example.com/l.png");
    assert_string_equal(img->text, "Logo");

    rd_free(d);
    pv_free(v);
}

static void test_no_images_no_notice(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "just text", NULL), PV_OK);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK);
    assert_int_equal(d->has_images, 0);
    assert_null(first_kind(d, RD_NOTICE));
    rd_free(d);
    pv_free(v);
}

/* --- images on: per-image decision, no notice --- */

static void test_image_on_allows_normal(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append_image(v, 0, 0, "", "https://example.com/photo.jpg", 640, 480), PV_OK);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, caps_images_on(), TOP, &d), RD_OK);
    assert_null(first_kind(d, RD_NOTICE)); /* enabled: no off-by-default warning */
    const rd_block *img = first_kind(d, RD_IMAGE);
    assert_non_null(img);
    assert_int_equal(img->img_decision, RDP_IMG_ALLOW);
    rd_free(d);
    pv_free(v);
}

static void test_image_on_blocks_tracker(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append_image(v, 0, 0, "", "https://t.example/p.gif", 1, 1), PV_OK);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, caps_images_on(), TOP, &d), RD_OK);
    const rd_block *img = first_kind(d, RD_IMAGE);
    assert_non_null(img);
    assert_int_equal(img->img_decision, RDP_IMG_BLOCK_TRACKER);
    rd_free(d);
    pv_free(v);
}

static void test_image_on_blocks_non_https(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append_image(v, 0, 0, "", "http://example.com/a.png", 64, 64), PV_OK);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, caps_images_on(), TOP, &d), RD_OK);
    const rd_block *img = first_kind(d, RD_IMAGE);
    assert_non_null(img);
    assert_int_equal(img->img_decision, RDP_IMG_BLOCK_SCHEME);
    rd_free(d);
    pv_free(v);
}

/* A local file has no https top-level URL: image decisions fail closed once the
 * capability is enabled (disabled still wins when off). */
static void test_image_on_local_top_fails_closed(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append_image(v, 0, 0, "", "https://example.com/a.png", 64, 64), PV_OK);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, caps_images_on(), NULL, &d), RD_OK);
    const rd_block *img = first_kind(d, RD_IMAGE);
    assert_non_null(img);
    assert_int_equal(img->img_decision, RDP_IMG_BLOCK_INVALID);
    rd_free(d);
    pv_free(v);
}

/* --- UTF-8 safety: an invalid href byte is sanitised in the document --- */

static void test_href_sanitised(void **state) {
    (void)state;
    pv_view *v = pv_new();
    /* pv_append stores the href verbatim; render_doc must make it paint-safe. */
    const char bad[] = { 'h', 't', 't', 'p', 's', ':', '/', '/', 'e', '/', (char)0xFF, '\0' };
    assert_int_equal(pv_append(v, PV_LINK, 0, 0, "x", bad), PV_OK);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK);
    const rd_block *l = first_kind(d, RD_LINK);
    assert_non_null(l);
    assert_string_equal(l->href, "https://e/?");
    rd_free(d);
    pv_free(v);
}

/* --- label / name strings are total --- */

static void test_kind_name_total(void **state) {
    (void)state;
    const rd_kind all[] = { RD_HEADING, RD_PARAGRAPH, RD_LINK, RD_IMAGE, RD_NOTICE };
    for (size_t i = 0; i < sizeof all / sizeof all[0]; ++i) {
        assert_non_null(rd_kind_name(all[i]));
        assert_true(strlen(rd_kind_name(all[i])) > 0);
    }
    assert_non_null(rd_kind_name((rd_kind)999));
}

static void test_image_label_total(void **state) {
    (void)state;
    const rdp_img_decision all[] = {
        RDP_IMG_ALLOW, RDP_IMG_BLOCK_DISABLED, RDP_IMG_BLOCK_INVALID,
        RDP_IMG_BLOCK_SCHEME, RDP_IMG_BLOCK_TRACKER,
    };
    for (size_t i = 0; i < sizeof all / sizeof all[0]; ++i) {
        assert_non_null(rd_image_label(all[i]));
        assert_true(strlen(rd_image_label(all[i])) > 0);
    }
    assert_non_null(rd_image_label((rdp_img_decision)999));
}

static void test_free_null_and_double(void **state) {
    (void)state;
    rd_free(NULL);
    rd_doc *d = NULL;
    assert_int_equal(rd_build(NULL, rdp_caps_safe(), TOP, &d), RD_OK);
    rd_free(d);
}

/* Author colors are presentation gated by caps.css (Privacy by Default off): the
 * run's fg_rgb is dropped to -1 unless author CSS is enabled. */
static void test_author_color_gated_by_css(void **state) {
    (void)state;
    pv_view *v = pv_new();
    assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "colored", NULL), PV_OK);
    pv_set_color(v, 0x3366cc);

    /* CSS off (default): color suppressed. */
    rd_doc *d = NULL;
    assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK);
    const rd_block *p = first_kind(d, RD_PARAGRAPH);
    assert_non_null(p);
    assert_int_equal(p->fg_rgb, -1);
    rd_free(d);

    /* CSS on: color carried through. */
    rdp_caps caps = rdp_caps_safe();
    caps.css = true;
    assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK);
    p = first_kind(d, RD_PARAGRAPH);
    assert_non_null(p);
    assert_int_equal(p->fg_rgb, 0x3366cc);
    rd_free(d);

    pv_free(v);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_build_null_out),
        cmocka_unit_test(test_build_null_view_is_empty),
        cmocka_unit_test(test_heading_paragraph_link),
        cmocka_unit_test(test_image_off_emits_notice_and_blocked),
        cmocka_unit_test(test_no_images_no_notice),
        cmocka_unit_test(test_image_on_allows_normal),
        cmocka_unit_test(test_image_on_blocks_tracker),
        cmocka_unit_test(test_image_on_blocks_non_https),
        cmocka_unit_test(test_image_on_local_top_fails_closed),
        cmocka_unit_test(test_href_sanitised),
        cmocka_unit_test(test_kind_name_total),
        cmocka_unit_test(test_image_label_total),
        cmocka_unit_test(test_author_color_gated_by_css),
        cmocka_unit_test(test_free_null_and_double),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
