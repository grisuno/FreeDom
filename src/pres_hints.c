/* pres_hints (ph_) -- see include/pres_hints.h and spec/pres_hints.md. */
#include "pres_hints.h"

#include <string.h>

#include "css_color.h"

#define PH_PER_MILLE_MAX 10000   /* 1000% */

static int ph_is_space(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

int ph_parse_dimension(const char *s, size_t len, int *px, int *per_mille) {
    if (s == NULL || len == 0 || len > PH_ATTR_MAX) return 0;
    size_t i = 0;
    while (i < len && ph_is_space(s[i])) ++i;
    long whole = 0;
    size_t digits = 0;
    for (; i < len && s[i] >= '0' && s[i] <= '9'; ++i, ++digits) {
        whole = whole * 10 + (s[i] - '0');
        if (whole > PH_DIM_MAX_PX) return 0;
    }
    if (digits == 0) return 0;
    long tenth = 0;
    if (i < len && s[i] == '.') {
        ++i;
        if (i < len && s[i] >= '0' && s[i] <= '9') tenth = s[i] - '0';
        while (i < len && s[i] >= '0' && s[i] <= '9') ++i;
    }
    if (i < len && s[i] == '%') {
        long pm = whole * 10 + tenth;
        if (pm <= 0 || pm > PH_PER_MILLE_MAX) return 0;
        if (per_mille != NULL) *per_mille = (int)pm;
        return 2;
    }
    if (whole <= 0) return 0;
    if (px != NULL) *px = (int)whole;
    return 1;
}

static int ph_ci_eq(const char *s, size_t len, const char *word) {
    size_t wl = strlen(word);
    if (len != wl) return 0;
    for (size_t i = 0; i < len; ++i) {
        char c = s[i];
        if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
        if (c != word[i]) return 0;
    }
    return 1;
}

static css_align ph_align(ph_attr_fn get, void *ctx) {
    size_t len = 0;
    const char *v = get(ctx, "align", &len);
    if (v == NULL || len > PH_ATTR_MAX) return CSS_ALIGN_UNSET;
    if (ph_ci_eq(v, len, "left"))    return CSS_ALIGN_LEFT;
    if (ph_ci_eq(v, len, "center") || ph_ci_eq(v, len, "middle")) return CSS_ALIGN_CENTER;
    if (ph_ci_eq(v, len, "right"))   return CSS_ALIGN_RIGHT;
    if (ph_ci_eq(v, len, "justify")) return CSS_ALIGN_JUSTIFY;
    return CSS_ALIGN_UNSET;
}

static void ph_width(ph_attr_fn get, void *ctx, css_style *cs) {
    if (cs->width != CSS_LEN_UNSET || cs->pct[CSS_PCT_WIDTH] != 0) return;
    size_t len = 0;
    const char *v = get(ctx, "width", &len);
    int px = 0, pm = 0;
    switch (ph_parse_dimension(v, len, &px, &pm)) {
        case 1: cs->width = px; cs->pct[CSS_PCT_WIDTH] = 0;  break;
        case 2: cs->width = 0;  cs->pct[CSS_PCT_WIDTH] = pm; break;
        default: break;
    }
}

static int ph_is_heading(const char *tag) {
    return tag[0] == 'h' && tag[1] >= '1' && tag[1] <= '6' && tag[2] == '\0';
}

/* bgcolor on the elements HTML gives it to: the element's background colour. */
static void ph_bgcolor(ph_attr_fn get, void *ctx, css_style *cs) {
    if (cs->background != -1 || cs->bg_grad_n >= 2 || cs->bg_image_url[0] != '\0') return;
    size_t len = 0;
    const char *v = get(ctx, "bgcolor", &len);
    if (v == NULL || len == 0 || len > PH_ATTR_MAX) return;
    char buf[PH_ATTR_MAX + 1];
    memcpy(buf, v, len);
    buf[len] = '\0';
    cc_rgb rgb;
    if (cc_parse(buf, &rgb) == CC_OK) cs->background = cc_pack(rgb);
}

void ph_apply(const char *tag, ph_attr_fn get, void *ctx, unsigned flags, css_style *cs) {
    if (tag == NULL || get == NULL || cs == NULL) return;
    int centered = (flags & PH_CENTERED) != 0;
    int is_table = strcmp(tag, "table") == 0;
    int is_cell = strcmp(tag, "td") == 0 || strcmp(tag, "th") == 0;

    if (is_table || is_cell || strcmp(tag, "tr") == 0 || strcmp(tag, "body") == 0 ||
        strcmp(tag, "tbody") == 0 || strcmp(tag, "thead") == 0 || strcmp(tag, "tfoot") == 0)
        ph_bgcolor(get, ctx, cs);

    if (is_table) {
        ph_width(get, ctx, cs);
        /* A table's width is its border box (the UA sheet's box-sizing: border-box). */
        if (cs->box_sizing == CSS_BOXS_UNSET) cs->box_sizing = CSS_BOXS_BORDER;
        /* Quirks mode: a table does not inherit text-align (the UA sheet resets it), so a
         * table inside <center> is centred but its cells still start at the left. */
        if ((flags & PH_QUIRKS) != 0 && cs->text_align == CSS_ALIGN_UNSET)
            cs->text_align = CSS_ALIGN_LEFT;
        if ((centered || ph_align(get, ctx) == CSS_ALIGN_CENTER) &&
            cs->margin_left == CSS_LEN_UNSET && cs->margin_right == CSS_LEN_UNSET) {
            cs->margin_left = CSS_LEN_AUTO;
            cs->margin_right = CSS_LEN_AUTO;
        }
        return;
    }
    if (is_cell) {
        ph_width(get, ctx, cs);
        size_t len = 0;
        if (cs->white_space == CSS_WS_UNSET && get(ctx, "nowrap", &len) != NULL)
            cs->white_space = CSS_WS_NOWRAP;
    }
    if (strcmp(tag, "center") == 0) {
        if (cs->text_align == CSS_ALIGN_UNSET) cs->text_align = CSS_ALIGN_CENTER;
        return;
    }
    if (is_cell || strcmp(tag, "tr") == 0 || strcmp(tag, "div") == 0 ||
        strcmp(tag, "p") == 0 || ph_is_heading(tag)) {
        if (cs->text_align == CSS_ALIGN_UNSET) cs->text_align = ph_align(get, ctx);
    }
}
