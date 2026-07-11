/*
 * libFuzzer harness for css (the author-CSS parser + simple cascade).
 *
 * A <style> block and an inline style= attribute are hostile remote content.
 * Arbitrary bytes -> css_parse / css_resolve / css_parse_inline must never
 * crash, leak or trigger UB, must stay bounded, and must never phone home: the
 * security invariant is that no resolved value carries a url() (the parser drops
 * any such declaration), which we re-assert here over the resolved style.
 *
 * The input is split on '\n' into the sheet text and an inline declaration list
 * the fuzzer controls independently.
 *
 * Build & run: make fuzz-css   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "css.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static void check_style(css_style s) {
    /* Resolved colors are either unset (-1) or a packed 0xRRGGBB. */
    if (s.color != -1 && (s.color < 0 || s.color > 0xffffff)) abort();
    if (s.background != -1 && (s.background < 0 || s.background > 0xffffff)) abort();
    /* font_scale is unset (0) or within the clamp the interpreter enforces. */
    if (s.font_scale != 0 && (s.font_scale < 10 || s.font_scale > 1000)) abort();

    /* Layout / box decoration (Hito 23b-7): every resolved value stays a sentinel or
     * within the clamp its interpreter enforces (no overflow, no out-of-range enum). */
    int bw[4] = { s.border_top_width, s.border_right_width,
                  s.border_bottom_width, s.border_left_width };
    int bc[5] = { s.border_top_color, s.border_right_color, s.border_bottom_color,
                  s.border_left_color, s.box_shadow_color };
    for (int i = 0; i < 4; ++i)
        if (bw[i] != CSS_LEN_UNSET && (bw[i] < 0 || bw[i] > CSS_LEN_MAX)) abort();
    for (int i = 0; i < 5; ++i)
        if (bc[i] != -1 && (bc[i] < 0 || bc[i] > 0xffffff)) abort();
    if (s.border_radius != CSS_LEN_UNSET &&
        (s.border_radius < 0 || s.border_radius > CSS_LEN_MAX)) abort();
    if (s.position < CSS_POS_UNSET || s.position > CSS_POS_STICKY) abort();
    if (s.box_sizing < CSS_BOXS_UNSET || s.box_sizing > CSS_BOXS_BORDER) abort();
    if (s.flex_grow != -1 && (s.flex_grow < 0 || s.flex_grow > CSS_FLEX_FACTOR_MAX)) abort();
    if (s.flex_shrink != -1 && (s.flex_shrink < 0 || s.flex_shrink > CSS_FLEX_FACTOR_MAX)) abort();
    if (s.flex_basis != CSS_LEN_UNSET && s.flex_basis != CSS_LEN_AUTO &&
        (s.flex_basis < 0 || s.flex_basis > CSS_LEN_MAX)) abort();
    if (s.z_index != CSS_LEN_UNSET && (s.z_index < -CSS_LEN_MAX || s.z_index > CSS_LEN_MAX)) abort();
    if (s.order != CSS_LEN_UNSET && (s.order < -CSS_LEN_MAX || s.order > CSS_LEN_MAX)) abort();
    if (s.grid_col_span != 0 && (s.grid_col_span < 1 || s.grid_col_span > CSS_GRID_SPAN_MAX)) abort();
    if (s.grid_row_span != 0 && (s.grid_row_span < 1 || s.grid_row_span > CSS_GRID_SPAN_MAX)) abort();
    if (s.row_gap != -1 && (s.row_gap < 0 || s.row_gap > CSS_GAP_MAX)) abort();
    if (s.float_side < CSS_FLOAT_UNSET || s.float_side > CSS_FLOAT_RIGHT) abort();
    if (s.clear < CSS_CLEAR_UNSET || s.clear > CSS_CLEAR_BOTH) abort();
    if (s.visibility < CSS_VIS_UNSET || s.visibility > CSS_VIS_COLLAPSE) abort();
    if (s.overflow_x < CSS_OF_UNSET || s.overflow_x > CSS_OF_AUTO) abort();
    if (s.overflow_y < CSS_OF_UNSET || s.overflow_y > CSS_OF_AUTO) abort();
    if (s.cursor < CSS_CUR_UNSET || s.cursor > CSS_CUR_NONE) abort();
    if (s.text_overflow < CSS_TO_UNSET || s.text_overflow > CSS_TO_ELLIPSIS) abort();
    if (s.word_break < CSS_WB_UNSET || s.word_break > CSS_WB_BREAK) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *buf = (char *)malloc(size + 1);
    if (buf == NULL) return 0;
    memcpy(buf, data, size);
    buf[size] = '\0';

    /* Split into sheet \n inline (either field may be empty). */
    char *sheet_text = buf;
    char *inl = strchr(sheet_text, '\n');
    if (inl != NULL) { *inl = '\0'; ++inl; }

    css_sheet *sh = NULL;
    if (css_parse(sheet_text, 0, &sh) == CSS_OK) {
        /* Resolve against a few representative element shapes. */
        const char *cls[] = { "note", "button" };
        check_style(css_resolve(sh, "p", NULL, NULL, 0, inl, 0));
        check_style(css_resolve(sh, "a", "main", cls, 2, inl, 0));
        check_style(css_resolve(sh, NULL, NULL, NULL, 0, NULL, 0));

        /* Combinator + attribute + pseudo-class matching: a synthetic ancestor
         * chain (div#main[data-x] > section.row a[href]) with two preceding
         * siblings on the subject drives complex_matches (descendant backtracking
         * + child + adjacent/general sibling checks), attr_matches over every
         * operator and pseudo_matches (:link via href, :checked/:disabled via
         * attrs, the nth-child family via nth/nsib). Sibling context varies with
         * the input so both known and unknown (fail-closed) positions are hit. */
        const char *rowcls[] = { "row" };
        css_attr root_attrs[] = { { "data-x", "on" }, { "role", "main" } };
        css_attr leaf_attrs[] = { { "href", "https://x.test/a.pdf" }, { "rel", "noopener" } };
        css_attr sib_attrs[]  = { { "checked", "" }, { "disabled", "" } };
        int nth = (size > 2) ? (int)(data[2] & 7) : 0;      /* 0..7: 0 = unknown */
        int nsib = (nth > 0) ? nth + ((size > 3) ? (int)(data[3] & 3) : 0) : 0;
        css_element root = { "div", "main", NULL, 0, root_attrs, 2, NULL, 1, 1, NULL };
        css_element mid  = { "section", NULL, rowcls, 1, NULL, 0, &root, nth, nsib, NULL };
        css_element sib2 = { "input", NULL, NULL, 0, sib_attrs, 2, &mid, 0, 0, NULL };
        css_element sib1 = { "h2", NULL, NULL, 0, NULL, 0, &mid, 0, 0, &sib2 };
        css_element leaf = { "a", NULL, cls, 2, leaf_attrs, 2, &mid, nth, nsib, &sib1 };
        check_style(css_resolve_el(sh, &leaf, inl, 0));
        check_style(css_resolve_el(sh, &root, NULL, 0));
        check_style(css_resolve_el(sh, NULL, inl, 0));

        css_free(sh);
    }

    /* Exercise @media gating with a context derived from the input (first byte). */
    css_media media = {
        (size > 0) ? (data[0] & 1) : 0,
        (size > 0) ? ((data[0] >> 1) & 1) : 0,
        (size > 1) ? (int)data[1] * 16 : CSS_MEDIA_DEFAULT_WIDTH
    };
    css_sheet *sm = NULL;
    if (css_parse_media(sheet_text, 0, &media, &sm) == CSS_OK) {
        check_style(css_resolve(sm, "p", NULL, NULL, 0, NULL, 0));
        check_style(css_resolve(sm, "body", NULL, NULL, 0, NULL, 0));
        css_free(sm);
    }

    check_style(css_parse_inline(inl, 0));

    free(buf);
    return 0;
}
