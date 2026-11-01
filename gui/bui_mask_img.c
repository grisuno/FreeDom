/* bui_mask_img -- paints a mask-image: url() layer into a mask surface.
 *
 * Trusted side. The image pixels were decoded inside the confined worker (PNG/JPEG/
 * WebP/GIF, or an SVG rasterized by svg_raster); the geometry -- where the image
 * sits and how big it is -- is the pure bx_background_layer, the SAME function that
 * places a background-image, because CSS Masking 1 7.4-7.6 define mask-repeat,
 * mask-position and mask-size by reference to Backgrounds 3. What is left here is
 * clipping and tiling. Kept out of browser_ui.c (anti-monolith clause). */

#include "browser_ui_internal.h"

#include <cairo.h>

#include "box_style.h"
#include "css.h"

int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,
                         const int geo[CSS_MASK_GEO_N],
                         double ax, double ay, double aw, double ah) {
    if (c == NULL || img == NULL || geo == NULL || nat_w <= 0 || nat_h <= 0) return 0;
    if (!(aw > 0.0) || !(ah > 0.0)) return 0;
    bx_bg_layer L = {
        .nat_w = (double)nat_w, .nat_h = (double)nat_h,
        .area_w = aw, .area_h = ah,
        .size_kw = geo[CSS_MG_SIZE],
        .size_w = geo[CSS_MG_SIZE_W], .size_h = geo[CSS_MG_SIZE_H],
        .size_w_pct = geo[CSS_MG_SIZE_WP], .size_h_pct = geo[CSS_MG_SIZE_HP],
        .pos_x = geo[CSS_MG_POS_X], .pos_y = geo[CSS_MG_POS_Y],
        .pos_x_pct = geo[CSS_MG_POS_XP], .pos_y_pct = geo[CSS_MG_POS_YP],
    };
    double iw = 0.0, ih = 0.0, ox = 0.0, oy = 0.0;
    if (!bx_background_layer(&L, &iw, &ih, &ox, &oy)) return 0;
    int rep = geo[CSS_MG_REPEAT];
    cairo_save(c);
    cairo_rectangle(c, ax, ay, aw, ah);
    cairo_clip(c);
    /* EXTEND_REPEAT tiles both axes; repeat-x / repeat-y clip to one strip. */
    if (rep == CSS_BGR_REPEAT_X) {
        cairo_rectangle(c, ax, ay + oy, aw, ih);
        cairo_clip(c);
    } else if (rep == CSS_BGR_REPEAT_Y) {
        cairo_rectangle(c, ax + ox, ay, iw, ah);
        cairo_clip(c);
    }
    cairo_translate(c, ax + ox, ay + oy);
    cairo_scale(c, iw / (double)nat_w, ih / (double)nat_h);
    cairo_pattern_t *pat = cairo_pattern_create_for_surface(img);
    cairo_pattern_set_extend(pat, rep == CSS_BGR_NO_REPEAT ? CAIRO_EXTEND_NONE : CAIRO_EXTEND_REPEAT);
    cairo_pattern_set_filter(pat, CAIRO_FILTER_GOOD);
    cairo_set_source(c, pat);
    cairo_paint(c);
    cairo_pattern_destroy(pat);
    cairo_restore(c);
    return 1;
}
