#include "css_computed.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

typedef size_t (*ccm_fn)(const ccm_input *in, char *out, size_t cap);

static size_t put(char *out, size_t cap, const char *s) {
    size_t n = strlen(s);
    if (n + 1 > cap) return 0;
    memcpy(out, s, n + 1);
    return n;
}

static size_t putf(char *out, size_t cap, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
static size_t putf(char *out, size_t cap, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int r = vsnprintf(out, cap, fmt, ap);
    va_end(ap);
    if (r < 0 || (size_t)r >= cap) { out[0] = '\0'; return 0; }
    return (size_t)r;
}

static size_t put_rgb(char *out, size_t cap, int rgb, int alpha_pct) {
    int r = (rgb >> 16) & 0xff, g = (rgb >> 8) & 0xff, b = rgb & 0xff;
    if (alpha_pct >= 0 && alpha_pct < 100) {
        if (alpha_pct == 0) return putf(out, cap, "rgba(%d, %d, %d, 0)", r, g, b);
        if (alpha_pct % 10 == 0) return putf(out, cap, "rgba(%d, %d, %d, %d.%d)", r, g, b,
                                             alpha_pct / 100, alpha_pct / 10 % 10);
        return putf(out, cap, "rgba(%d, %d, %d, 0.%02d)", r, g, b, alpha_pct);
    }
    return putf(out, cap, "rgb(%d, %d, %d)", r, g, b);
}

static size_t put_len(char *out, size_t cap, int v, const char *unset_text) {
    if (v == CSS_LEN_UNSET || v == CSS_LEN_AUTO) return put(out, cap, unset_text);
    return putf(out, cap, "%dpx", v);
}

static size_t put_enum(char *out, size_t cap, int v, const char *const *names, size_t n,
                       const char *fallback) {
    return put(out, cap, (v > 0 && (size_t)v < n && names[v] != NULL) ? names[v] : fallback);
}

/* The HTML Rendering UA sheet's `display` for a tag when the cascade declared none
 * (the engine keeps block-ness of plain tags in its own tables, not in the sheet). */
static const char *ua_display(const char *tag) {
    static const char *const none[] = { "head", "link", "meta", "script", "style", "title",
        "template", "area", "base", "datalist", "noembed", "noframes", "param", "rp" };
    static const char *const block[] = { "html", "body", "address", "article", "aside",
        "blockquote", "center", "dd", "details", "dialog", "dir", "div", "dl", "dt", "fieldset",
        "figcaption", "figure", "footer", "form", "h1", "h2", "h3", "h4", "h5", "h6", "header",
        "hgroup", "hr", "legend", "listing", "main", "menu", "nav", "ol", "p", "pre", "search",
        "section", "summary", "ul", "xmp", "optgroup" };
    static const char *const iblock[] = { "button", "input", "select", "textarea", "meter",
        "progress" };
    if (tag == NULL) return "inline";
    for (size_t i = 0; i < sizeof none / sizeof *none; ++i)
        if (strcmp(tag, none[i]) == 0) return "none";
    for (size_t i = 0; i < sizeof block / sizeof *block; ++i)
        if (strcmp(tag, block[i]) == 0) return "block";
    for (size_t i = 0; i < sizeof iblock / sizeof *iblock; ++i)
        if (strcmp(tag, iblock[i]) == 0) return "inline-block";
    if (strcmp(tag, "li") == 0) return "list-item";
    if (strcmp(tag, "table") == 0) return "table";
    if (strcmp(tag, "thead") == 0 || strcmp(tag, "tbody") == 0 || strcmp(tag, "tfoot") == 0)
        return "table-row-group";
    if (strcmp(tag, "tr") == 0) return "table-row";
    if (strcmp(tag, "td") == 0 || strcmp(tag, "th") == 0) return "table-cell";
    if (strcmp(tag, "caption") == 0) return "table-caption";
    if (strcmp(tag, "col") == 0) return "table-column";
    return "inline";
}

static size_t f_display(const ccm_input *in, char *out, size_t cap) {
    switch (in->st->display) {
    case CSS_DISP_NONE:            return put(out, cap, "none");
    case CSS_DISP_BLOCK:           return put(out, cap, "block");
    case CSS_DISP_INLINE_BLOCK:    return put(out, cap, "inline-block");
    case CSS_DISP_LIST_ITEM:       return put(out, cap, "list-item");
    case CSS_DISP_FLEX:            return put(out, cap, "flex");
    case CSS_DISP_GRID:            return put(out, cap, "grid");
    case CSS_DISP_TABLE:           return put(out, cap, "table");
    case CSS_DISP_TABLE_ROW_GROUP: return put(out, cap, "table-row-group");
    case CSS_DISP_TABLE_ROW:       return put(out, cap, "table-row");
    case CSS_DISP_TABLE_CELL:      return put(out, cap, "table-cell");
    case CSS_DISP_TABLE_CAPTION:   return put(out, cap, "table-caption");
    case CSS_DISP_TABLE_COLUMN:    return put(out, cap, "table-column");
    default:                       return put(out, cap, ua_display(in->tag));
    }
}

static size_t f_position(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "static", "relative", "absolute", "fixed", "sticky" };
    return put_enum(out, cap, in->st->position, n, sizeof n / sizeof *n, "static");
}

static size_t f_visibility(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "visible", "hidden", "collapse" };
    return put_enum(out, cap, in->st->visibility, n, sizeof n / sizeof *n, "visible");
}

static size_t f_float(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "none", "left", "right" };
    return put_enum(out, cap, in->st->float_side, n, sizeof n / sizeof *n, "none");
}

static size_t f_clear(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "none", "left", "right", "both" };
    return put_enum(out, cap, in->st->clear, n, sizeof n / sizeof *n, "none");
}

static size_t f_overflow_x(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "visible", "hidden", "scroll", "auto" };
    return put_enum(out, cap, in->st->overflow_x, n, sizeof n / sizeof *n, "visible");
}

static size_t f_overflow_y(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "visible", "hidden", "scroll", "auto" };
    return put_enum(out, cap, in->st->overflow_y, n, sizeof n / sizeof *n, "visible");
}

static size_t f_text_align(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "left", "center", "right" };
    return put_enum(out, cap, (int)in->st->text_align, n, sizeof n / sizeof *n, "start");
}

static size_t f_box_sizing(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "content-box", "border-box" };
    return put_enum(out, cap, in->st->box_sizing, n, sizeof n / sizeof *n, "content-box");
}

static size_t f_flex_direction(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "row", "row-reverse", "column", "column-reverse" };
    return put_enum(out, cap, in->st->flex_direction, n, sizeof n / sizeof *n, "row");
}

static size_t f_flex_wrap(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "nowrap", "wrap", "wrap-reverse" };
    return put_enum(out, cap, in->st->flex_wrap, n, sizeof n / sizeof *n, "nowrap");
}

static size_t f_justify(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "flex-start", "flex-end", "center", "space-between",
                                     "space-around", "space-evenly" };
    return put_enum(out, cap, (int)in->st->justify, n, sizeof n / sizeof *n, "normal");
}

static size_t f_align_items(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "auto", "stretch", "flex-start", "flex-end", "center",
                                     "baseline", "space-between", "space-around", "space-evenly" };
    return put_enum(out, cap, in->st->align_items, n, sizeof n / sizeof *n, "normal");
}

static size_t f_cursor(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "auto", "default", "pointer", "text", "move",
        "not-allowed", "help", "wait", "crosshair", "grab", "zoom-in", "none" };
    return put_enum(out, cap, in->st->cursor, n, sizeof n / sizeof *n, "auto");
}

static size_t f_white_space(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "normal", "nowrap", "pre", "pre-wrap", "pre-line" };
    return put_enum(out, cap, in->st->white_space, n, sizeof n / sizeof *n, "normal");
}

static size_t f_text_transform(const ccm_input *in, char *out, size_t cap) {
    static const char *const n[] = { NULL, "none", "uppercase", "lowercase", "capitalize" };
    return put_enum(out, cap, in->st->text_transform, n, sizeof n / sizeof *n, "none");
}

static size_t f_font_style(const ccm_input *in, char *out, size_t cap) {
    return put(out, cap, in->st->italic == 1 ? "italic" : "normal");
}

static size_t f_font_weight(const ccm_input *in, char *out, size_t cap) {
    return put(out, cap, in->st->bold == 1 ? "700" : "400");
}

static size_t f_font_size(const ccm_input *in, char *out, size_t cap) {
    double px = in->font_px > 0.0 ? in->font_px : 16.0;
    if (px == (double)(int)px) return putf(out, cap, "%dpx", (int)px);
    return putf(out, cap, "%.4gpx", px);
}

static size_t f_line_height(const ccm_input *in, char *out, size_t cap) {
    int ls = in->st->line_scale;
    if (ls >= CSS_LINE_ABS_BASE) return putf(out, cap, "%dpx", (ls - CSS_LINE_ABS_BASE) / 10);
    return put(out, cap, "normal");
}

static size_t f_color(const ccm_input *in, char *out, size_t cap) {
    int c = in->st->color >= 0 ? in->st->color : (in->inherited_color >= 0 ? in->inherited_color : 0);
    return put_rgb(out, cap, c, -1);
}

static size_t f_background_color(const ccm_input *in, char *out, size_t cap) {
    if (in->st->background < 0) return put(out, cap, "rgba(0, 0, 0, 0)");
    int a = (in->st->bg_alpha == CSS_LEN_UNSET) ? -1 : in->st->bg_alpha;
    return put_rgb(out, cap, in->st->background, a);
}

static size_t f_opacity(const ccm_input *in, char *out, size_t cap) {
    int o = in->st->opacity;
    if (o < 0 || o >= 100) return put(out, cap, "1");
    if (o == 0) return put(out, cap, "0");
    if (o % 10 == 0) return putf(out, cap, "0.%d", o / 10);
    return putf(out, cap, "0.%02d", o);
}

static size_t f_z_index(const ccm_input *in, char *out, size_t cap) {
    if (in->st->z_index == CSS_LEN_UNSET) return put(out, cap, "auto");
    return putf(out, cap, "%d", in->st->z_index);
}

static size_t f_border_style(int v, char *out, size_t cap) {
    static const char *const n[] = { NULL, "none", "hidden", "solid", "dashed", "dotted",
                                     "double", "groove", "ridge", "inset", "outset" };
    return put_enum(out, cap, v, n, sizeof n / sizeof *n, "none");
}

#define LEN_FIELD(NAME, FIELD, UNSET) \
    static size_t NAME(const ccm_input *in, char *out, size_t cap) { \
        return put_len(out, cap, in->st->FIELD, UNSET); }
LEN_FIELD(f_margin_top, margin_top, "0px")
LEN_FIELD(f_margin_right, margin_right, "0px")
LEN_FIELD(f_margin_bottom, margin_bottom, "0px")
LEN_FIELD(f_margin_left, margin_left, "0px")
LEN_FIELD(f_padding_top, pad_top, "0px")
LEN_FIELD(f_padding_right, pad_right, "0px")
LEN_FIELD(f_padding_bottom, pad_bottom, "0px")
LEN_FIELD(f_padding_left, pad_left, "0px")
LEN_FIELD(f_width, width, "auto")
LEN_FIELD(f_height, height, "auto")
LEN_FIELD(f_min_width, min_width, "0px")
LEN_FIELD(f_min_height, min_height, "0px")
LEN_FIELD(f_max_width, max_width, "none")
LEN_FIELD(f_max_height, max_height, "none")
LEN_FIELD(f_top, inset_top, "auto")
LEN_FIELD(f_right, inset_right, "auto")
LEN_FIELD(f_bottom, inset_bottom, "auto")
LEN_FIELD(f_left, inset_left, "auto")
static size_t f_gap(const ccm_input *in, char *out, size_t cap) {
    return in->st->gap < 0 ? put(out, cap, "normal") : putf(out, cap, "%dpx", in->st->gap);
}
LEN_FIELD(f_border_top_width, border_top_width, "0px")
LEN_FIELD(f_border_right_width, border_right_width, "0px")
LEN_FIELD(f_border_bottom_width, border_bottom_width, "0px")
LEN_FIELD(f_border_left_width, border_left_width, "0px")
LEN_FIELD(f_border_top_left_radius, border_radius, "0px")
LEN_FIELD(f_border_top_right_radius, border_radius_tr, "0px")
LEN_FIELD(f_border_bottom_right_radius, border_radius_br, "0px")
LEN_FIELD(f_border_bottom_left_radius, border_radius_bl, "0px")

static size_t f_border_top_style(const ccm_input *in, char *out, size_t cap) {
    return f_border_style(in->st->border_top_style, out, cap);
}
static size_t f_border_right_style(const ccm_input *in, char *out, size_t cap) {
    return f_border_style(in->st->border_right_style, out, cap);
}
static size_t f_border_bottom_style(const ccm_input *in, char *out, size_t cap) {
    return f_border_style(in->st->border_bottom_style, out, cap);
}
static size_t f_border_left_style(const ccm_input *in, char *out, size_t cap) {
    return f_border_style(in->st->border_left_style, out, cap);
}

static size_t f_flex_grow(const ccm_input *in, char *out, size_t cap) {
    return putf(out, cap, "%d", in->st->flex_grow > 0 ? in->st->flex_grow : 0);
}
static size_t f_flex_shrink(const ccm_input *in, char *out, size_t cap) {
    return putf(out, cap, "%d", in->st->flex_shrink >= 0 ? in->st->flex_shrink : 1);
}

typedef struct ccm_prop { const char *name; ccm_fn fn; } ccm_prop;

static const ccm_prop PROPS[] = {
    { "align-items", f_align_items }, { "background-color", f_background_color },
    { "border-bottom-left-radius", f_border_bottom_left_radius },
    { "border-bottom-right-radius", f_border_bottom_right_radius },
    { "border-bottom-style", f_border_bottom_style },
    { "border-bottom-width", f_border_bottom_width },
    { "border-left-style", f_border_left_style }, { "border-left-width", f_border_left_width },
    { "border-right-style", f_border_right_style }, { "border-right-width", f_border_right_width },
    { "border-top-left-radius", f_border_top_left_radius },
    { "border-top-right-radius", f_border_top_right_radius },
    { "border-top-style", f_border_top_style }, { "border-top-width", f_border_top_width },
    { "bottom", f_bottom }, { "box-sizing", f_box_sizing }, { "clear", f_clear },
    { "color", f_color }, { "cursor", f_cursor }, { "display", f_display },
    { "flex-direction", f_flex_direction }, { "flex-grow", f_flex_grow },
    { "flex-shrink", f_flex_shrink }, { "flex-wrap", f_flex_wrap }, { "float", f_float },
    { "font-size", f_font_size }, { "font-style", f_font_style }, { "font-weight", f_font_weight },
    { "gap", f_gap }, { "height", f_height }, { "justify-content", f_justify },
    { "left", f_left }, { "line-height", f_line_height },
    { "margin-bottom", f_margin_bottom }, { "margin-left", f_margin_left },
    { "margin-right", f_margin_right }, { "margin-top", f_margin_top },
    { "max-height", f_max_height }, { "max-width", f_max_width },
    { "min-height", f_min_height }, { "min-width", f_min_width }, { "opacity", f_opacity },
    { "overflow-x", f_overflow_x }, { "overflow-y", f_overflow_y },
    { "padding-bottom", f_padding_bottom }, { "padding-left", f_padding_left },
    { "padding-right", f_padding_right }, { "padding-top", f_padding_top },
    { "position", f_position }, { "right", f_right }, { "text-align", f_text_align },
    { "text-transform", f_text_transform }, { "top", f_top },
    { "visibility", f_visibility }, { "white-space", f_white_space }, { "width", f_width },
    { "z-index", f_z_index },
};
#define CCM_NPROPS (sizeof PROPS / sizeof PROPS[0])

size_t ccm_get(const ccm_input *in, const char *prop, char *out, size_t cap) {
    if (out == NULL || cap == 0) return 0;
    out[0] = '\0';
    if (in == NULL || in->st == NULL || prop == NULL) return 0;
    for (size_t i = 0; i < CCM_NPROPS; ++i) {
        if (strcmp(PROPS[i].name, prop) != 0) continue;
        size_t n = PROPS[i].fn(in, out, cap);
        if (n == 0) out[0] = '\0';
        return n;
    }
    return 0;
}

size_t ccm_property_count(void) { return CCM_NPROPS; }

const char *ccm_property_name(size_t i) { return i < CCM_NPROPS ? PROPS[i].name : NULL; }
