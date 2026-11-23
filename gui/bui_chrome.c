/*
 * bui_chrome -- the browser chrome painter: tab strip (with the window buttons
 * under client-side decorations), navigation buttons, the URL pill and its
 * connection identity badge.
 *
 * Every rectangle comes from chrome_layout (pure), the same geometry the pointer
 * hit-tests use, so nothing here decides where a thing is -- only how it looks.
 * Icons are drawn as Cairo paths: they never depend on the chrome face having a
 * glyph, and they stay crisp at any scale.
 */

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "browser_ui_internal.h"

#define BUI_TWO_PI        6.28318530717958647692
#define BUI_ICON_LINE     1.6   /* stroke width of every chrome icon */
#define BUI_TAB_RADIUS    7.0
#define BUI_PILL_RADIUS   7.0
#define BUI_TAB_PAD       10.0  /* tab title inset from the tab's left edge */
#define BUI_TAB_FADE      18.0  /* width of the fade-out at the end of a long title */
#define BUI_SPINNER_R     5.5
#define BUI_STOP_HALF     5.5   /* half-size of the Stop cross that replaces reload */
#define BUI_URL_TEXT_PAD  4.0   /* gap between the identity badge and the URL text */
#define BUI_URL_END_PAD   10.0  /* free space kept after the caret at the pill's end */
#define BUI_FOCUS_RING    2.0
#define BUI_INACTIVE_TEXT 0.78  /* alpha of an inactive tab's title */
#define BUI_DISABLED      0.38  /* alpha of a disabled button's icon */
#define BUI_URL_MEASURE   4096  /* longest URL prefix measured on the stack */

static const char BUI_URL_PLACEHOLDER[] = "Search or enter address";

void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r) {
    if (r > w / 2.0) r = w / 2.0;
    if (r > h / 2.0) r = h / 2.0;
    if (r < 0.0) r = 0.0;
    cairo_new_sub_path(cr);
    cairo_arc(cr, x + w - r, y + r, r, -BUI_TWO_PI / 4.0, 0.0);
    cairo_arc(cr, x + w - r, y + h - r, r, 0.0, BUI_TWO_PI / 4.0);
    cairo_arc(cr, x + r, y + h - r, r, BUI_TWO_PI / 4.0, BUI_TWO_PI / 2.0);
    cairo_arc(cr, x + r, y + r, r, BUI_TWO_PI / 2.0, BUI_TWO_PI * 0.75);
    cairo_close_path(cr);
}

/* A tab: rounded top corners, square bottom (it joins the toolbar below). */
static void tab_path(cairo_t *cr, chl_rect t, double r) {
    cairo_new_sub_path(cr);
    cairo_move_to(cr, t.x, t.y + t.h);
    cairo_arc(cr, t.x + r, t.y + r, r, BUI_TWO_PI / 2.0, BUI_TWO_PI * 0.75);
    cairo_arc(cr, t.x + t.w - r, t.y + r, r, BUI_TWO_PI * 0.75, BUI_TWO_PI);
    cairo_line_to(cr, t.x + t.w, t.y + t.h);
    cairo_close_path(cr);
}

static void set_rgba(cairo_t *cr, ui_rgb c, double a) {
    cairo_set_source_rgba(cr, c.r, c.g, c.b, a);
}

void bui_chrome_font(cairo_t *cr, double size) {
    cairo_select_font_face(cr, BUI_CHROME_FONT, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, size);
}

static double rcx(chl_rect r) { return r.x + r.w / 2.0; }
static double rcy(chl_rect r) { return r.y + r.h / 2.0; }

static void icon_stroke(cairo_t *cr) {
    cairo_set_line_width(cr, BUI_ICON_LINE);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join(cr, CAIRO_LINE_JOIN_ROUND);
    cairo_stroke(cr);
}

static void icon_arrow(cairo_t *cr, double cx, double cy, int dir) {
    double s = 6.0 * (double)dir;
    cairo_move_to(cr, cx + s, cy);
    cairo_line_to(cr, cx - s, cy);
    cairo_move_to(cr, cx - s + 5.0 * (double)dir, cy - 5.0);
    cairo_line_to(cr, cx - s, cy);
    cairo_line_to(cr, cx - s + 5.0 * (double)dir, cy + 5.0);
    icon_stroke(cr);
}

/* A circular arrow open at the top right, its head at 12 o'clock pointing clockwise. */
static void icon_reload(cairo_t *cr, double cx, double cy) {
    double r = 6.5;
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, r, -BUI_TWO_PI / 12.0, BUI_TWO_PI * 0.75);
    icon_stroke(cr);
    cairo_move_to(cr, cx + 4.0, cy - r);
    cairo_line_to(cr, cx - 0.5, cy - r - 4.0);
    cairo_line_to(cr, cx - 0.5, cy - r + 4.0);
    cairo_close_path(cr);
    cairo_fill(cr);
}

static void icon_menu(cairo_t *cr, double cx, double cy) {
    for (int i = -1; i <= 1; ++i) {
        cairo_move_to(cr, cx - 7.0, cy + 5.0 * (double)i);
        cairo_line_to(cr, cx + 7.0, cy + 5.0 * (double)i);
    }
    icon_stroke(cr);
}

static void icon_cross(cairo_t *cr, double cx, double cy, double h) {
    cairo_move_to(cr, cx - h, cy - h);
    cairo_line_to(cr, cx + h, cy + h);
    cairo_move_to(cr, cx + h, cy - h);
    cairo_line_to(cr, cx - h, cy + h);
    icon_stroke(cr);
}

static void icon_plus(cairo_t *cr, double cx, double cy, double h) {
    cairo_move_to(cr, cx - h, cy);
    cairo_line_to(cr, cx + h, cy);
    cairo_move_to(cr, cx, cy - h);
    cairo_line_to(cr, cx, cy + h);
    icon_stroke(cr);
}

static void spinner(cairo_t *cr, ui_rgb c, double cx, double cy, double phase) {
    set_rgba(cr, c, 0.25);
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, BUI_SPINNER_R, 0.0, BUI_TWO_PI);
    icon_stroke(cr);
    set_rgb(cr, c);
    double a0 = phase * BUI_TWO_PI;
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, BUI_SPINNER_R, a0, a0 + BUI_TWO_PI * 0.28);
    icon_stroke(cr);
}

/* --- identity badge glyphs, centred at (cx, cy), ~14 px --- */

static void glyph_shield(cairo_t *cr, double cx, double cy, int check, int fill) {
    cairo_new_sub_path(cr);
    cairo_move_to(cr, cx, cy - 7.0);
    cairo_line_to(cr, cx + 6.0, cy - 4.5);
    cairo_curve_to(cr, cx + 6.0, cy + 2.0, cx + 3.5, cy + 5.5, cx, cy + 7.5);
    cairo_curve_to(cr, cx - 3.5, cy + 5.5, cx - 6.0, cy + 2.0, cx - 6.0, cy - 4.5);
    cairo_close_path(cr);
    if (fill) {
        cairo_fill_preserve(cr);
    }
    icon_stroke(cr);
    if (check) {
        cairo_save(cr);
        cairo_set_source_rgb(cr, 0.07, 0.10, 0.08);
        cairo_move_to(cr, cx - 2.8, cy + 0.2);
        cairo_line_to(cr, cx - 0.6, cy + 2.6);
        cairo_line_to(cr, cx + 3.0, cy - 2.4);
        cairo_set_line_width(cr, 1.8);
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        cairo_stroke(cr);
        cairo_restore(cr);
    }
}

static void glyph_lock(cairo_t *cr, double cx, double cy) {
    bui_round_rect(cr, cx - 5.5, cy - 1.5, 11.0, 8.5, 1.5);
    cairo_fill(cr);
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy - 3.5, 3.5, BUI_TWO_PI / 2.0, BUI_TWO_PI);
    cairo_move_to(cr, cx - 3.5, cy - 3.5);
    cairo_line_to(cr, cx - 3.5, cy - 1.5);
    cairo_move_to(cr, cx + 3.5, cy - 3.5);
    cairo_line_to(cr, cx + 3.5, cy - 1.5);
    icon_stroke(cr);
}

static void glyph_warning(cairo_t *cr, double cx, double cy) {
    cairo_new_sub_path(cr);
    cairo_move_to(cr, cx, cy - 7.0);
    cairo_line_to(cr, cx + 7.5, cy + 6.0);
    cairo_line_to(cr, cx - 7.5, cy + 6.0);
    cairo_close_path(cr);
    cairo_fill(cr);
    cairo_save(cr);
    cairo_set_source_rgb(cr, 0.10, 0.08, 0.06);
    cairo_move_to(cr, cx, cy - 2.5);
    cairo_line_to(cr, cx, cy + 1.5);
    cairo_move_to(cr, cx, cy + 4.0);
    cairo_line_to(cr, cx, cy + 4.1);
    cairo_set_line_width(cr, 1.8);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_stroke(cr);
    cairo_restore(cr);
}

static void glyph_overlay(cairo_t *cr, double cx, double cy) {
    for (int i = 1; i <= 3; ++i) {
        cairo_new_sub_path(cr);
        cairo_arc(cr, cx, cy, 2.2 * (double)i, 0.0, BUI_TWO_PI);
    }
    icon_stroke(cr);
}

static void glyph_page(cairo_t *cr, double cx, double cy) {
    cairo_move_to(cr, cx - 4.5, cy - 6.5);
    cairo_line_to(cr, cx + 1.5, cy - 6.5);
    cairo_line_to(cr, cx + 4.5, cy - 3.5);
    cairo_line_to(cr, cx + 4.5, cy + 6.5);
    cairo_line_to(cr, cx - 4.5, cy + 6.5);
    cairo_close_path(cr);
    icon_stroke(cr);
}

static void glyph_info(cairo_t *cr, double cx, double cy) {
    cairo_new_sub_path(cr);
    cairo_arc(cr, cx, cy, 6.5, 0.0, BUI_TWO_PI);
    cairo_move_to(cr, cx, cy - 0.5);
    cairo_line_to(cr, cx, cy + 3.5);
    cairo_move_to(cr, cx, cy - 3.2);
    cairo_line_to(cr, cx, cy - 3.1);
    icon_stroke(cr);
}

static void paint_identity(cairo_t *cr, const bui_chrome_view *v) {
    const ui_theme *th = v->th;
    chl_rect r = v->l->identity;
    if (r.w <= 0.0) return;
    if (v->hot_part == CHL_PART_IDENTITY) {
        set_rgb(cr, th->btn_hover_bg);
        bui_round_rect(cr, r.x, r.y, r.w, r.h, BUI_PILL_RADIUS - 2.0);
        cairo_fill(cr);
    }
    double cx = rcx(r), cy = rcy(r);
    switch (v->identity) {
        case CHL_ID_PQ:
            set_rgb(cr, th->id_good);
            glyph_shield(cr, cx, cy, 1, 1);
            break;
        case CHL_ID_CLASSICAL:
            set_rgb(cr, th->id_warn);
            glyph_lock(cr, cx, cy);
            break;
        case CHL_ID_WEAK:
            set_rgb(cr, th->id_warn);
            glyph_warning(cr, cx, cy);
            break;
        case CHL_ID_UNVERIFIED:
        case CHL_ID_INSECURE:
            set_rgb(cr, th->id_bad);
            glyph_warning(cr, cx, cy);
            break;
        case CHL_ID_OVERLAY:
            set_rgb(cr, th->id_overlay);
            glyph_overlay(cr, cx, cy);
            break;
        case CHL_ID_LOCAL:
            set_rgb(cr, th->url_text_dim);
            glyph_page(cr, cx, cy);
            break;
        case CHL_ID_INTERNAL:
            set_rgb(cr, th->url_text_dim);
            glyph_shield(cr, cx, cy, 0, 0);
            break;
        case CHL_ID_UNKNOWN:
        default:
            set_rgb(cr, th->url_text_dim);
            glyph_info(cr, cx, cy);
            break;
    }
}

/* --- text measurement (the toy API never kerns, so a prefix width is the sum of
 * its characters' advances) --- */

static size_t utf8_next(const char *s, size_t n, size_t i) {
    if (i >= n) return n;
    ++i;
    while (i < n && ((unsigned char)s[i] & 0xC0u) == 0x80u) ++i;
    return i;
}

static double text_w(cairo_t *cr, const char *s, size_t n) {
    char buf[BUI_URL_MEASURE];
    if (n >= sizeof buf) n = sizeof buf - 1;
    memcpy(buf, s, n);
    buf[n] = '\0';
    cairo_text_extents_t te;
    cairo_text_extents(cr, buf, &te);
    return te.x_advance;
}

static void show_n(cairo_t *cr, const char *s, size_t n) {
    char buf[BUI_URL_MEASURE];
    if (n >= sizeof buf) n = sizeof buf - 1;
    memcpy(buf, s, n);
    buf[n] = '\0';
    cairo_show_text(cr, buf);
}

double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift) {
    const chl_rect id = v->l->identity, url = v->l->url;
    double x = id.x + id.w + BUI_URL_TEXT_PAD;
    double s = 0.0;
    if (v->url_focused && v->url != NULL) {
        size_t cur = v->cursor < v->url_len ? v->cursor : v->url_len;
        double caret = text_w(cr, v->url, cur);
        double avail = url.x + url.w - BUI_URL_END_PAD - x;
        if (caret > avail && avail > 0.0) s = caret - avail;
    }
    if (shift != NULL) *shift = s;
    return x;
}

size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x) {
    if (v->url == NULL) return 0;
    bui_chrome_font(cr, BUI_URL_FONT_SIZE);
    double shift = 0.0;
    double tx = bui_url_text_x(v, cr, &shift) - shift;
    double target = x - tx;
    size_t best = 0;
    double acc = 0.0;
    for (size_t i = 0; i < v->url_len;) {
        size_t j = utf8_next(v->url, v->url_len, i);
        double adv = text_w(cr, v->url + i, j - i);
        if (target < acc + adv / 2.0) return i;
        acc += adv;
        best = j;
        i = j;
    }
    return best;
}

/* Length of the scheme prefix and the host that follows it, for the unfocused
 * display that dims everything but the host (the part a phishing URL disguises). */
static void host_span(const char *u, size_t n, size_t *h0, size_t *h1) {
    *h0 = 0;
    *h1 = n;
    const char *sep = NULL;
    for (size_t i = 0; i + 2 < n; ++i) {
        if (u[i] == ':' && u[i + 1] == '/' && u[i + 2] == '/') { sep = u + i; break; }
        if (u[i] == '/' || u[i] == '?' || u[i] == '#') break;
    }
    if (sep == NULL) return;
    size_t a = (size_t)(sep - u) + 3;
    size_t b = a;
    while (b < n && u[b] != '/' && u[b] != '?' && u[b] != '#') ++b;
    *h0 = a;
    *h1 = b;
}

static void paint_url(cairo_t *cr, const bui_chrome_view *v) {
    const ui_theme *th = v->th;
    chl_rect p = v->l->url;
    if (p.w <= 0.0) return;

    set_rgb(cr, v->url_focused ? th->url_bg_focused : th->url_bg);
    bui_round_rect(cr, p.x, p.y, p.w, p.h, BUI_PILL_RADIUS);
    cairo_fill(cr);
    if (v->url_focused) {
        set_rgb(cr, th->accent);
        cairo_set_line_width(cr, BUI_FOCUS_RING);
        bui_round_rect(cr, p.x + 1.0, p.y + 1.0, p.w - 2.0, p.h - 2.0, BUI_PILL_RADIUS - 1.0);
        cairo_stroke(cr);
    } else if (v->hot_part == CHL_PART_URL) {
        set_rgba(cr, th->url_border, 1.0);
        cairo_set_line_width(cr, 1.0);
        bui_round_rect(cr, p.x + 0.5, p.y + 0.5, p.w - 1.0, p.h - 1.0, BUI_PILL_RADIUS);
        cairo_stroke(cr);
    }
    paint_identity(cr, v);

    bui_chrome_font(cr, BUI_URL_FONT_SIZE);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double shift = 0.0;
    double tx = bui_url_text_x(v, cr, &shift);
    double ty = rcy(p) + (fe.ascent - fe.descent) / 2.0;

    cairo_save(cr);
    cairo_rectangle(cr, tx, p.y, p.x + p.w - BUI_URL_TEXT_PAD - tx, p.h);
    cairo_clip(cr);
    tx -= shift;

    const char *u = (v->url != NULL) ? v->url : "";
    size_t n = (v->url != NULL) ? v->url_len : 0;
    if (n == 0 && !v->url_focused) {
        set_rgb(cr, th->url_text_dim);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, BUI_URL_PLACEHOLDER);
    } else if (v->url_focused) {
        if (v->sel_len > 0 && v->sel_start < n) {
            size_t se = v->sel_start + v->sel_len;
            if (se > n) se = n;
            double sx = tx + text_w(cr, u, v->sel_start);
            double ex = tx + text_w(cr, u, se);
            set_rgb(cr, th->url_select_bg);
            cairo_rectangle(cr, sx, ty - fe.ascent, ex - sx, fe.height);
            cairo_fill(cr);
        }
        set_rgb(cr, th->url_text);
        cairo_move_to(cr, tx, ty);
        show_n(cr, u, n);
        size_t cur = v->cursor < n ? v->cursor : n;
        set_rgb(cr, th->url_caret);
        cairo_rectangle(cr, tx + text_w(cr, u, cur), ty - fe.ascent, 1.5, fe.height);
        cairo_fill(cr);
    } else {
        size_t h0, h1;
        host_span(u, n, &h0, &h1);
        cairo_move_to(cr, tx, ty);
        set_rgb(cr, th->url_text_dim);
        show_n(cr, u, h0);
        set_rgb(cr, th->url_text);
        show_n(cr, u + h0, h1 - h0);
        set_rgb(cr, th->url_text_dim);
        show_n(cr, u + h1, n - h1);
    }
    cairo_restore(cr);
}

/* --- rows --- */

static void round_button(cairo_t *cr, const bui_chrome_view *v, chl_rect r, chl_part part,
                         int enabled) {
    if (enabled && v->hot_part == part) {
        set_rgb(cr, v->th->btn_hover_bg);
        cairo_new_sub_path(cr);
        cairo_arc(cr, rcx(r), rcy(r), r.w / 2.0, 0.0, BUI_TWO_PI);
        cairo_fill(cr);
    }
    set_rgba(cr, v->th->chrome_text, enabled ? 1.0 : BUI_DISABLED);
}

static void paint_toolbar(cairo_t *cr, const bui_chrome_view *v) {
    const chl_layout *l = v->l;
    set_rgb(cr, v->th->toolbar_bg);
    cairo_rectangle(cr, 0.0, l->toolbar_top, l->width, CHL_TOOLBAR_H);
    cairo_fill(cr);

    round_button(cr, v, l->back, CHL_PART_BACK, v->can_back);
    icon_arrow(cr, rcx(l->back), rcy(l->back), 1);
    round_button(cr, v, l->fwd, CHL_PART_FWD, v->can_fwd);
    icon_arrow(cr, rcx(l->fwd), rcy(l->fwd), -1);
    round_button(cr, v, l->reload, CHL_PART_RELOAD, 1);
    if (v->loading) icon_cross(cr, rcx(l->reload), rcy(l->reload), BUI_STOP_HALF);
    else            icon_reload(cr, rcx(l->reload), rcy(l->reload));
    round_button(cr, v, l->menu, CHL_PART_MENU, 1);
    icon_menu(cr, rcx(l->menu), rcy(l->menu));
    paint_url(cr, v);
}

/* A title clipped to [x0, x1) with a fade-out where it overflows. */
static void tab_title(cairo_t *cr, const char *s, ui_rgb c, double alpha,
                      double x0, double x1, double baseline, double y, double h) {
    if (x1 <= x0) return;
    cairo_text_extents_t te;
    cairo_text_extents(cr, s, &te);
    cairo_save(cr);
    cairo_rectangle(cr, x0, y, x1 - x0, h);
    cairo_clip(cr);
    if (te.x_advance <= x1 - x0) {
        set_rgba(cr, c, alpha);
        cairo_move_to(cr, x0, baseline);
        cairo_show_text(cr, s);
    } else {
        cairo_push_group(cr);
        set_rgba(cr, c, alpha);
        cairo_move_to(cr, x0, baseline);
        cairo_show_text(cr, s);
        cairo_pattern_t *text = cairo_pop_group(cr);
        double f0 = x1 - BUI_TAB_FADE;
        if (f0 < x0) f0 = x0;
        cairo_pattern_t *fade = cairo_pattern_create_linear(f0, 0.0, x1, 0.0);
        cairo_pattern_add_color_stop_rgba(fade, 0.0, 0, 0, 0, 1.0);
        cairo_pattern_add_color_stop_rgba(fade, 1.0, 0, 0, 0, 0.0);
        cairo_set_source(cr, text);
        cairo_mask(cr, fade);
        cairo_pattern_destroy(fade);
        cairo_pattern_destroy(text);
    }
    cairo_restore(cr);
}

/* A chevron pointing left (dir < 0) or right. */
static void icon_side_chevron(cairo_t *cr, double cx, double cy, int dir) {
    double d = (dir < 0) ? -1.0 : 1.0;
    cairo_move_to(cr, cx - 2.5 * d, cy - 5.0);
    cairo_line_to(cr, cx + 2.5 * d, cy);
    cairo_line_to(cr, cx - 2.5 * d, cy + 5.0);
    icon_stroke(cr);
}

/* Hidden-tabs indicator: a chevron toward the hidden tabs with their count under it;
 * dimmed (and inert, chl_hit) when nothing is hidden on that side. */
static void paint_more(cairo_t *cr, const bui_chrome_view *v, chl_rect r, int hidden,
                       chl_part part, int dir) {
    if (r.w <= 0.0) return;
    const ui_theme *th = v->th;
    if (hidden > 0 && v->hot_part == part) {
        set_rgb(cr, th->btn_hover_bg);
        bui_round_rect(cr, r.x, r.y + 2.0, r.w, r.h - 6.0, 6.0);
        cairo_fill(cr);
    }
    set_rgba(cr, th->chrome_text, hidden > 0 ? 0.9 : BUI_DISABLED * 0.6);
    double cx = rcx(r), cy = rcy(r) - 6.0;
    icon_side_chevron(cr, cx, cy, dir);
    if (hidden <= 0) return;
    char num[8];
    if (hidden > 99) snprintf(num, sizeof num, "99+");
    else             snprintf(num, sizeof num, "%d", hidden);
    bui_chrome_font(cr, 9.5);
    cairo_text_extents_t te;
    cairo_text_extents(cr, num, &te);
    cairo_move_to(cr, cx - te.x_advance / 2.0, cy + 16.0);
    cairo_show_text(cr, num);
}

static void paint_tabstrip(cairo_t *cr, const bui_chrome_view *v) {
    const chl_layout *l = v->l;
    const ui_theme *th = v->th;
    set_rgb(cr, th->titlebar_bg);
    cairo_rectangle(cr, 0.0, l->tabbar_top, l->width, CHL_TABBAR_H);
    cairo_fill(cr);

    bui_chrome_font(cr, BUI_CHROME_FONT_SIZE);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);

    for (int i = l->tab_first; i < l->tab_first + l->tabs_visible; ++i) {
        chl_rect t;
        if (!chl_tab_rect(l, i, &t)) continue;
        int active = (i == l->active);
        int hot = (v->hot_tab == i);
        if (active) {
            set_rgb(cr, th->tab_active_bg);
            tab_path(cr, t, BUI_TAB_RADIUS);
            cairo_fill(cr);
        } else if (hot) {
            set_rgb(cr, th->btn_hover_bg);
            bui_round_rect(cr, t.x, t.y + 1.0, t.w, t.h - 5.0, BUI_TAB_RADIUS - 1.0);
            cairo_fill(cr);
        }

        double tx = t.x + BUI_TAB_PAD;
        double mid = t.y + (active ? t.h : t.h - 4.0) / 2.0;
        int loading = (v->tab_loading != NULL && v->tab_loading[i]);
        if (loading) {
            spinner(cr, th->accent, tx + BUI_SPINNER_R, mid, v->phase);
            tx += 2.0 * BUI_SPINNER_R + 6.0;
        }
        chl_rect c;
        int has_close = chl_tab_close_rect(l, i, &c);
        double tend = has_close ? c.x - 2.0 : t.x + t.w - BUI_TAB_PAD;
        bui_chrome_font(cr, BUI_CHROME_FONT_SIZE);
        tab_title(cr, v->titles[i], th->chrome_text, active ? 1.0 : BUI_INACTIVE_TEXT,
                  tx, tend, mid + (fe.ascent - fe.descent) / 2.0, t.y, t.h);
        if (has_close) {
            if (v->hot_part == CHL_PART_TAB_CLOSE && v->hot_tab == i) {
                set_rgb(cr, th->btn_hover_bg);
                bui_round_rect(cr, c.x, c.y, c.w, c.h, 4.0);
                cairo_fill(cr);
            }
            set_rgba(cr, th->chrome_text, active ? 0.9 : 0.7);
            icon_cross(cr, rcx(c), rcy(c), 3.5);
        }
    }

    paint_more(cr, v, l->more_left, l->hidden_left, CHL_PART_TABS_LEFT, -1);
    paint_more(cr, v, l->more_right, l->hidden_right, CHL_PART_TABS_RIGHT, 1);

    chl_rect n = l->new_tab;
    if (v->hot_part == CHL_PART_NEW_TAB) {
        set_rgb(cr, th->btn_hover_bg);
        bui_round_rect(cr, n.x, n.y, n.w, n.h, 6.0);
        cairo_fill(cr);
    }
    set_rgb(cr, th->chrome_text);
    icon_plus(cr, rcx(n), rcy(n), 5.5);

    if (!l->csd) return;
    if (v->hot_part == CHL_PART_WIN_MIN || v->hot_part == CHL_PART_WIN_MAX) {
        chl_rect h = (v->hot_part == CHL_PART_WIN_MIN) ? l->win_min : l->win_max;
        set_rgb(cr, th->btn_hover_bg);
        cairo_rectangle(cr, h.x, h.y, h.w, h.h);
        cairo_fill(cr);
    } else if (v->hot_part == CHL_PART_WIN_CLOSE) {
        set_rgb(cr, th->win_close_hot);
        cairo_rectangle(cr, l->win_close.x, l->win_close.y, l->win_close.w, l->win_close.h);
        cairo_fill(cr);
    }
    set_rgb(cr, th->chrome_text);
    double my = rcy(l->win_min);
    cairo_move_to(cr, rcx(l->win_min) - 5.0, my + 0.5);
    cairo_line_to(cr, rcx(l->win_min) + 5.0, my + 0.5);
    icon_stroke(cr);
    double qx = rcx(l->win_max), qy = rcy(l->win_max);
    if (v->maximized) {
        cairo_rectangle(cr, qx - 5.0, qy - 3.0, 8.0, 8.0);
        cairo_move_to(cr, qx - 3.0, qy - 5.0);
        cairo_line_to(cr, qx + 5.0, qy - 5.0);
        cairo_line_to(cr, qx + 5.0, qy + 3.0);
    } else {
        cairo_rectangle(cr, qx - 5.0, qy - 5.0, 10.0, 10.0);
    }
    cairo_set_line_width(cr, 1.2);
    cairo_stroke(cr);
    icon_cross(cr, rcx(l->win_close), rcy(l->win_close), 5.0);
}

void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v) {
    if (cr == NULL || v == NULL || v->l == NULL || v->th == NULL || v->titles == NULL) return;
    cairo_save(cr);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    paint_tabstrip(cr, v);
    paint_toolbar(cr, v);
    /* A hairline separates the chrome from the page. */
    set_rgba(cr, v->th->url_border, 0.6);
    cairo_rectangle(cr, 0.0, v->l->content_top - 1.0, v->l->width, 1.0);
    cairo_fill(cr);
    cairo_restore(cr);
}

/* --- find bar (spec/find_text.md) --- */

static const char BUI_FIND_PLACEHOLDER[] = "Find in page";

static void paint_find_field(cairo_t *cr, const bui_find_view *v) {
    const ui_theme *th = v->th;
    chl_rect p = v->f->field;
    if (p.w <= 0.0) return;
    int none = (v->len > 0 && v->total == 0);
    set_rgb(cr, v->focused ? th->url_bg_focused : th->url_bg);
    bui_round_rect(cr, p.x, p.y, p.w, p.h, BUI_PILL_RADIUS);
    cairo_fill(cr);
    if (v->focused || none) {
        set_rgb(cr, none ? th->id_bad : th->accent);
        cairo_set_line_width(cr, BUI_FOCUS_RING);
        bui_round_rect(cr, p.x + 1.0, p.y + 1.0, p.w - 2.0, p.h - 2.0, BUI_PILL_RADIUS - 1.0);
        cairo_stroke(cr);
    }
    bui_chrome_font(cr, BUI_URL_FONT_SIZE);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double tx = p.x + BUI_URL_END_PAD;
    double ty = rcy(p) + (fe.ascent - fe.descent) / 2.0;
    double room = p.w - 2.0 * BUI_URL_END_PAD;
    size_t n = v->len, cur = v->cursor < n ? v->cursor : n;
    double shift = text_w(cr, v->text, cur) - room;   /* keep the caret in view */
    if (shift < 0.0) shift = 0.0;
    cairo_save(cr);
    cairo_rectangle(cr, tx, p.y, room, p.h);
    cairo_clip(cr);
    tx -= shift;
    if (n == 0) {
        set_rgb(cr, th->url_text_dim);
        cairo_move_to(cr, tx, ty);
        cairo_show_text(cr, BUI_FIND_PLACEHOLDER);
    } else {
        if (v->selected) {
            set_rgb(cr, th->url_select_bg);
            cairo_rectangle(cr, tx, ty - fe.ascent, text_w(cr, v->text, n), fe.height);
            cairo_fill(cr);
        }
        set_rgb(cr, th->url_text);
        cairo_move_to(cr, tx, ty);
        show_n(cr, v->text, n);
    }
    if (v->focused) {
        set_rgb(cr, th->url_caret);
        cairo_rectangle(cr, tx + text_w(cr, v->text, cur), ty - fe.ascent, 1.5, fe.height);
        cairo_fill(cr);
    }
    cairo_restore(cr);
}

static void find_button(cairo_t *cr, const bui_find_view *v, chl_rect r, chl_find_part part,
                        int enabled) {
    if (r.w <= 0.0) return;
    if (enabled && v->hot == part) {
        set_rgb(cr, v->th->btn_hover_bg);
        bui_round_rect(cr, r.x, r.y, r.w, r.h, 6.0);
        cairo_fill(cr);
    }
    set_rgba(cr, v->th->chrome_text, enabled ? 1.0 : BUI_DISABLED);
}

/* A chevron pointing up (dir > 0) or down. */
static void icon_chevron(cairo_t *cr, double cx, double cy, int dir) {
    double d = (dir > 0) ? -1.0 : 1.0;
    cairo_move_to(cr, cx - 5.0, cy - 2.5 * d);
    cairo_line_to(cr, cx, cy + 2.5 * d);
    cairo_line_to(cr, cx + 5.0, cy - 2.5 * d);
    icon_stroke(cr);
}

void bui_paint_findbar(cairo_t *cr, const bui_find_view *v) {
    if (cr == NULL || v == NULL || v->f == NULL || v->th == NULL) return;
    if (v->text == NULL && v->len > 0) return;
    const chl_findbar *f = v->f;
    cairo_save(cr);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    set_rgb(cr, v->th->toolbar_bg);
    cairo_rectangle(cr, f->bar.x, f->bar.y, f->bar.w, f->bar.h);
    cairo_fill(cr);
    set_rgba(cr, v->th->url_border, 0.6);
    cairo_rectangle(cr, f->bar.x, f->bar.y, f->bar.w, 1.0);
    cairo_fill(cr);

    bui_find_view vv = *v;
    if (vv.text == NULL) vv.text = "";
    paint_find_field(cr, &vv);
    int can = (v->total > 0);
    find_button(cr, v, f->prev, CHL_FIND_PREV, can);
    if (f->prev.w > 0.0) icon_chevron(cr, rcx(f->prev), rcy(f->prev), 1);
    find_button(cr, v, f->next, CHL_FIND_NEXT, can);
    if (f->next.w > 0.0) icon_chevron(cr, rcx(f->next), rcy(f->next), -1);
    find_button(cr, v, f->close, CHL_FIND_CLOSE, 1);
    if (f->close.w > 0.0) icon_cross(cr, rcx(f->close), rcy(f->close), 4.5);

    if (f->count.w > 0.0 && v->len > 0) {
        char label[64];
        if (v->total == 0)
            snprintf(label, sizeof label, "No matches");
        else if (v->truncated)
            snprintf(label, sizeof label, "%ld of more than %zu matches", v->current + 1, v->total);
        else
            snprintf(label, sizeof label, "%ld of %zu match%s", v->current + 1, v->total,
                     v->total == 1 ? "" : "es");
        bui_chrome_font(cr, BUI_CHROME_FONT_SIZE);
        cairo_font_extents_t fe;
        cairo_font_extents(cr, &fe);
        cairo_save(cr);
        cairo_rectangle(cr, f->count.x, f->count.y, f->count.w, f->count.h);
        cairo_clip(cr);
        set_rgb(cr, v->total == 0 ? v->th->id_bad : v->th->chrome_text);
        cairo_move_to(cr, f->count.x, rcy(f->count) + (fe.ascent - fe.descent) / 2.0);
        cairo_show_text(cr, label);
        cairo_restore(cr);
    }
    cairo_restore(cr);
}

/* --- site identity panel (spec/site_panel.md) --- */

#define BUI_SP_RADIUS   10.0
#define BUI_SP_LABEL_W  118.0  /* label column; values start after it */

/* a toward b by t in [0,1]: tone colours tuned for the dark chrome read on a light panel. */
static ui_rgb mix_rgb(ui_rgb a, ui_rgb b, double t) {
    ui_rgb c = a;
    c.r = a.r + (b.r - a.r) * t;
    c.g = a.g + (b.g - a.g) * t;
    c.b = a.b + (b.b - a.b) * t;
    return c;
}

static ui_rgb tone_rgb(const ui_theme *th, sp_tone t) {
    switch (t) {
        case SP_TONE_GOOD: return th->id_good;
        case SP_TONE_WARN: return th->id_warn;
        case SP_TONE_BAD:  return th->id_bad;
        case SP_TONE_NEUTRAL:
        default:           return th->menu_text;
    }
}

/* Shows s clipped to [x, x + w). */
static void text_in(cairo_t *cr, const char *s, double x, double baseline, double w, double top,
                    double h) {
    if (w <= 0.0) return;
    cairo_save(cr);
    cairo_rectangle(cr, x, top, w, h);
    cairo_clip(cr);
    cairo_move_to(cr, x, baseline);
    cairo_show_text(cr, s);
    cairo_restore(cr);
}

void bui_paint_site_panel(cairo_t *cr, const ui_theme *th, const sp_panel *p, const sp_geom *g,
                          int hot_action) {
    if (cr == NULL || th == NULL || p == NULL || g == NULL) return;
    chl_rect b = g->panel;
    if (b.w <= 0.0 || b.h <= 0.0) return;
    cairo_save(cr);
    cairo_set_antialias(cr, CAIRO_ANTIALIAS_DEFAULT);
    for (int k = 4; k >= 1; --k) {
        cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 0.06);
        bui_round_rect(cr, b.x - (double)k, b.y - (double)k + 3.0, b.w + 2.0 * (double)k,
                       b.h + 2.0 * (double)k, BUI_SP_RADIUS + (double)k);
        cairo_fill(cr);
    }
    set_rgb(cr, th->menu_bg);
    bui_round_rect(cr, b.x, b.y, b.w, b.h, BUI_SP_RADIUS);
    cairo_fill_preserve(cr);
    set_rgba(cr, th->url_border, 0.9);
    cairo_set_line_width(cr, 1.0);
    cairo_stroke(cr);
    bui_round_rect(cr, b.x, b.y, b.w, b.h, BUI_SP_RADIUS);
    cairo_clip(cr);

    /* Header: the badge glyph in its tone, the host, the headline. */
    ui_rgb tc = tone_rgb(th, p->tone);
    double gx = b.x + SP_PAD + 9.0, gy = b.y + 24.0;
    set_rgb(cr, tc);
    switch (p->tone) {
        case SP_TONE_GOOD: glyph_shield(cr, gx, gy, 1, 1); break;
        case SP_TONE_WARN: glyph_lock(cr, gx, gy); break;
        case SP_TONE_BAD:  glyph_warning(cr, gx, gy); break;
        default:           glyph_shield(cr, gx, gy, 0, 0); break;
    }
    double tx = b.x + SP_PAD + 28.0, tw = b.x + b.w - SP_PAD - tx;
    cairo_select_font_face(cr, BUI_CHROME_FONT, CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size(cr, 15.0);
    set_rgb(cr, th->menu_text);
    text_in(cr, p->title, tx, b.y + 28.0, tw, b.y, SP_HEADER_H);
    bui_chrome_font(cr, 12.0);
    set_rgb(cr, p->tone == SP_TONE_NEUTRAL ? tc : mix_rgb(tc, th->menu_text, 0.35));
    text_in(cr, p->headline, tx, b.y + 47.0, tw, b.y, SP_HEADER_H);
    set_rgba(cr, th->url_border, 0.7);
    cairo_rectangle(cr, b.x + SP_PAD, b.y + SP_HEADER_H - 4.0, b.w - 2.0 * SP_PAD, 1.0);
    cairo_fill(cr);

    /* Rows: label (dimmed) and value (in its tone). */
    bui_chrome_font(cr, BUI_CHROME_FONT_SIZE);
    cairo_font_extents_t fe;
    cairo_font_extents(cr, &fe);
    double y = b.y + SP_HEADER_H;
    double vx = b.x + SP_PAD + BUI_SP_LABEL_W, vw = b.x + b.w - SP_PAD - vx;
    for (int i = 0; i < p->row_count && i < SP_MAX_ROWS; ++i) {
        double base = y + SP_ROW_H / 2.0 + (fe.ascent - fe.descent) / 2.0;
        set_rgba(cr, th->menu_text, 0.62);
        text_in(cr, p->rows[i].label, b.x + SP_PAD, base, BUI_SP_LABEL_W - 6.0, y, SP_ROW_H);
        if (p->rows[i].tone != SP_TONE_NEUTRAL) {   /* the tone as a dot, the text readable */
            set_rgb(cr, tone_rgb(th, p->rows[i].tone));
            cairo_new_sub_path(cr);
            cairo_arc(cr, vx + 4.0, y + SP_ROW_H / 2.0, 3.5, 0.0, BUI_TWO_PI);
            cairo_fill(cr);
        }
        set_rgb(cr, th->menu_text);
        text_in(cr, p->rows[i].value, vx + 14.0, base, vw - 14.0, y, SP_ROW_H);
        y += SP_ROW_H;
    }

    /* Actions: full-width buttons, accent on hover. */
    for (int i = 0; i < g->action_count && i < p->action_count && i < SP_MAX_ACTIONS; ++i) {
        chl_rect a = g->action[i];
        int hot = (i == hot_action);
        set_rgb(cr, hot ? th->accent : mix_rgb(th->menu_bg, th->menu_text, 0.10));
        bui_round_rect(cr, a.x, a.y, a.w, a.h, 7.0);
        cairo_fill(cr);
        const char *lab = sp_action_label(p->actions[i]);
        cairo_text_extents_t te;
        cairo_text_extents(cr, lab, &te);
        if (hot) cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        else     set_rgb(cr, th->menu_text);
        text_in(cr, lab, a.x + (a.w - te.x_advance) / 2.0,
                rcy(a) + (fe.ascent - fe.descent) / 2.0, a.w, a.y, a.h);
    }
    cairo_restore(cr);
}

#define BUI_VBAR_ALPHA   0.55  /* bar background over the picture */
#define BUI_VTRACK_ALPHA 0.35  /* unplayed part of the track */
#define BUI_VKNOB_R      6.0
#define BUI_VTEXT_SIZE   12.0

void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos, double total) {
    if (cr == NULL || g == NULL || g->bar.w <= 0.0) return;
    cairo_save(cr);
    cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, BUI_VBAR_ALPHA);
    cairo_rectangle(cr, g->bar.x, g->bar.y, g->bar.w, g->bar.h);
    cairo_fill(cr);

    /* Play when paused, pause bars while playing: the button shows what a click does. */
    double cx = g->play.x + g->play.w / 2.0, cy = g->play.y + g->play.h / 2.0;
    double s = g->play.h * 0.32;
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    if (paused) {
        cairo_move_to(cr, cx - s * 0.8, cy - s);
        cairo_line_to(cr, cx - s * 0.8, cy + s);
        cairo_line_to(cr, cx + s, cy);
        cairo_close_path(cr);
    } else {
        cairo_rectangle(cr, cx - s * 0.8, cy - s, s * 0.55, 2.0 * s);
        cairo_rectangle(cr, cx + s * 0.25, cy - s, s * 0.55, 2.0 * s);
    }
    cairo_fill(cr);

    double frac = (total > 0.0) ? vcl_clamp_frac(pos / total) : 0.0;
    cairo_set_source_rgba(cr, 1.0, 1.0, 1.0, BUI_VTRACK_ALPHA);
    bui_round_rect(cr, g->track.x, g->track.y, g->track.w, g->track.h, g->track.h / 2.0);
    cairo_fill(cr);
    if (total > 0.0) {
        double px = g->track.x + g->track.w * frac;
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
        bui_round_rect(cr, g->track.x, g->track.y, px - g->track.x, g->track.h, g->track.h / 2.0);
        cairo_fill(cr);
        cairo_arc(cr, px, g->track.y + g->track.h / 2.0, BUI_VKNOB_R, 0.0, BUI_TWO_PI);
        cairo_fill(cr);
    }

    if (g->text_x + VCL_TEXT_W <= g->bar.x + g->bar.w + 0.5) {
        char a[16], b[16], line[40];
        vcl_format_time(pos, a, sizeof a);
        vcl_format_time(total, b, sizeof b);
        int n = (total > 0.0) ? snprintf(line, sizeof line, "%s / %s", a, b)
                              : snprintf(line, sizeof line, "%s", a);
        if (n > 0 && (size_t)n < sizeof line) {
            bui_chrome_font(cr, BUI_VTEXT_SIZE);
            cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
            cairo_move_to(cr, g->text_x, g->text_y);
            cairo_show_text(cr, line);
        }
    }
    cairo_restore(cr);
}
