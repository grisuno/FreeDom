/* svg_paint — Cairo back end for the shapes svg_render extracted.
 *
 * Trusted side. Takes only validated geometry (no strings to interpret, no URL to
 * resolve) and turns it into Cairo calls. Everything hostile was already handled by
 * the pure parser; what is left here is arithmetic and drawing.
 *
 * See spec/svg_render.md.
 */

#include "svg_paint.h"

#include <math.h>
#include <string.h>

#include "css_color.h"

/* Resolves a shape's packed paint into an RGB triple. Returns 0 when the shape
 * asked for no paint at all (fill="none"), so the caller skips the operation. */
static int svp_color(int packed, int current_rgb, double *r, double *g, double *b) {
    int c = packed;
    if (c == CC_COLOR_CURRENT) c = current_rgb;
    if (c < 0) return 0;
    *r = (double)((c >> 16) & 0xFF) / 255.0;
    *g = (double)((c >> 8) & 0xFF) / 255.0;
    *b = (double)(c & 0xFF) / 255.0;
    return 1;
}

/* alpha = group opacity x the per-paint opacity, both 0..100. */
static double svp_alpha(int opacity, int paint_opacity) {
    double o = (opacity >= 0 && opacity <= 100) ? opacity / 100.0 : 1.0;
    double p = (paint_opacity >= 0 && paint_opacity <= 100) ? paint_opacity / 100.0 : 1.0;
    return o * p;
}

/* Appends a rounded rectangle (or a plain one when the radii are zero). */
static void svp_rect_path(cairo_t *cr, const sv_shape *sh) {
    double x = sh->a, y = sh->b, w = sh->c, h = sh->d;
    double rx = sh->rx, ry = sh->ry;
    if (rx <= 0.0 || ry <= 0.0) {
        cairo_rectangle(cr, x, y, w, h);
        return;
    }
    /* Corner arcs drawn on a unit circle scaled to (rx, ry): one save/restore per
     * corner would reset the path, so the ellipse is produced by scaling the
     * coordinate system around each corner centre instead. */
    const double PI = 3.14159265358979323846;
    cairo_new_sub_path(cr);
    cairo_save(cr);
    cairo_translate(cr, x + rx, y + ry);
    cairo_scale(cr, rx, ry);
    cairo_arc(cr, 0.0, 0.0, 1.0, PI, 1.5 * PI);
    cairo_restore(cr);
    cairo_save(cr);
    cairo_translate(cr, x + w - rx, y + ry);
    cairo_scale(cr, rx, ry);
    cairo_arc(cr, 0.0, 0.0, 1.0, 1.5 * PI, 2.0 * PI);
    cairo_restore(cr);
    cairo_save(cr);
    cairo_translate(cr, x + w - rx, y + h - ry);
    cairo_scale(cr, rx, ry);
    cairo_arc(cr, 0.0, 0.0, 1.0, 0.0, 0.5 * PI);
    cairo_restore(cr);
    cairo_save(cr);
    cairo_translate(cr, x + rx, y + h - ry);
    cairo_scale(cr, rx, ry);
    cairo_arc(cr, 0.0, 0.0, 1.0, 0.5 * PI, PI);
    cairo_restore(cr);
    cairo_close_path(cr);
}

static void svp_shape_path(cairo_t *cr, const sv_image *img, const sv_shape *sh) {
    const double PI = 3.14159265358979323846;
    switch (sh->kind) {
        case SV_RECT:
            svp_rect_path(cr, sh);
            break;
        case SV_CIRCLE:
            cairo_new_sub_path(cr);
            cairo_arc(cr, sh->a, sh->b, sh->c, 0.0, 2.0 * PI);
            break;
        case SV_ELLIPSE:
            cairo_save(cr);
            cairo_translate(cr, sh->a, sh->b);
            cairo_scale(cr, sh->c, sh->d);
            cairo_new_sub_path(cr);
            cairo_arc(cr, 0.0, 0.0, 1.0, 0.0, 2.0 * PI);
            cairo_restore(cr);
            break;
        case SV_LINE:
            cairo_move_to(cr, sh->a, sh->b);
            cairo_line_to(cr, sh->c, sh->d);
            break;
        case SV_POLYLINE:
        case SV_POLYGON:
            for (size_t k = 0; k < sh->count; ++k) {
                size_t idx = sh->first + k;
                if (idx >= img->npt) break;
                if (k == 0) cairo_move_to(cr, img->px[idx], img->py[idx]);
                else        cairo_line_to(cr, img->px[idx], img->py[idx]);
            }
            if (sh->kind == SV_POLYGON) cairo_close_path(cr);
            break;
        case SV_PATH:
            for (size_t k = 0; k < sh->count; ++k) {
                size_t idx = sh->first + k;
                if (idx >= img->nseg) break;
                const sv_seg *sg = &img->segs[idx];
                switch (sg->verb) {
                    case SV_MOVE:   cairo_move_to(cr, sg->x[0], sg->y[0]); break;
                    case SV_LINETO: cairo_line_to(cr, sg->x[0], sg->y[0]); break;
                    case SV_CUBIC:  cairo_curve_to(cr, sg->x[0], sg->y[0],
                                                   sg->x[1], sg->y[1],
                                                   sg->x[2], sg->y[2]); break;
                    case SV_CLOSE:  cairo_close_path(cr); break;
                    default: break;
                }
            }
            break;
        default:
            break;
    }
}

static void svp_draw_text(cairo_t *cr, const sv_shape *sh, int current_rgb) {
    double r, g, b;
    if (!svp_color(sh->fill, current_rgb, &r, &g, &b)) return;
    cairo_save(cr);
    cairo_set_source_rgba(cr, r, g, b, svp_alpha(sh->opacity, sh->fill_opacity));
    cairo_select_font_face(cr, "sans-serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, (sh->c > 0.0) ? sh->c : 16.0);
    cairo_move_to(cr, sh->a, sh->b);
    cairo_show_text(cr, sh->text);
    cairo_new_path(cr);
    cairo_restore(cr);
}

void svp_draw(cairo_t *cr, const sv_image *img,
              double x, double y, double w, double h, int current_rgb) {
    if (cr == NULL || img == NULL || w <= 0.0 || h <= 0.0) return;

    double scale = 1.0, off_x = 0.0, off_y = 0.0;
    sv_fit(img, w, h, &scale, &off_x, &off_y);

    cairo_save(cr);
    /* Clip to the box the layout reserved: a hostile transform inside the markup
     * cannot paint over the rest of the page. */
    cairo_rectangle(cr, x, y, w, h);
    cairo_clip(cr);
    cairo_translate(cr, x + off_x, y + off_y);
    cairo_scale(cr, scale, scale);
    if (img->has_viewbox) cairo_translate(cr, -img->vb_x, -img->vb_y);

    for (size_t i = 0; i < img->nshape && i < SV_MAX_SHAPES; ++i) {
        const sv_shape *sh = &img->shapes[i];
        cairo_save(cr);
        cairo_matrix_t m;
        cairo_matrix_init(&m, sh->m[0], sh->m[1], sh->m[2], sh->m[3], sh->m[4], sh->m[5]);
        cairo_transform(cr, &m);

        if (sh->kind == SV_TEXT) {
            svp_draw_text(cr, sh, current_rgb);
            cairo_restore(cr);
            continue;
        }

        cairo_new_path(cr);
        svp_shape_path(cr, img, sh);

        double r, g, b;
        if (svp_color(sh->fill, current_rgb, &r, &g, &b)) {
            cairo_set_source_rgba(cr, r, g, b, svp_alpha(sh->opacity, sh->fill_opacity));
            cairo_set_fill_rule(cr, sh->fill_even_odd ? CAIRO_FILL_RULE_EVEN_ODD
                                                      : CAIRO_FILL_RULE_WINDING);
            cairo_fill_preserve(cr);
        }
        if (sh->stroke_w > 0.0 && svp_color(sh->stroke, current_rgb, &r, &g, &b)) {
            cairo_set_source_rgba(cr, r, g, b, svp_alpha(sh->opacity, sh->stroke_opacity));
            cairo_set_line_width(cr, sh->stroke_w);
            cairo_set_line_cap(cr, (sh->linecap == 1) ? CAIRO_LINE_CAP_ROUND
                                 : (sh->linecap == 2) ? CAIRO_LINE_CAP_SQUARE
                                                      : CAIRO_LINE_CAP_BUTT);
            cairo_set_line_join(cr, (sh->linejoin == 1) ? CAIRO_LINE_JOIN_ROUND
                                  : (sh->linejoin == 2) ? CAIRO_LINE_JOIN_BEVEL
                                                        : CAIRO_LINE_JOIN_MITER);
            cairo_stroke(cr);
        }
        cairo_new_path(cr);
        cairo_restore(cr);
    }
    cairo_restore(cr);
}
