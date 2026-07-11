/*
 * box_style — implementation: the pure user-agent box model.
 *
 * Two sorted reference tables drive everything: one maps an HTML tag to its
 * default box (display + margins/padding in em), the other maps a CSS display
 * keyword to a bx_display. Both are looked up by case-insensitive binary search,
 * so there are no magic indices and the rules live as auditable data. No I/O, no
 * global mutable state, no dynamic allocation; every result is returned by value
 * or written to a caller buffer.
 */

#include "box_style.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/* Longest recognised tag is "blockquote" (10); longest display keyword is
 * "inline-block" (12). The buffers are generous so a normal token always fits and
 * anything longer fails closed instead of truncating. */
#define BX_TAG_MAX     32u
#define BX_DISPLAY_MAX 24u

static char lc(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}

static int is_ws(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

/* Copies in into out, trimming ASCII whitespace and lowercasing. Returns 0 on
 * success, -1 if in is NULL, the trimmed token is empty, or it does not fit. */
static int copy_lower_trim(const char *in, char *out, size_t out_size) {
    if (in == NULL) return -1;
    while (*in != '\0' && is_ws(*in)) ++in;
    size_t end = strlen(in);
    while (end > 0 && is_ws(in[end - 1])) --end;
    if (end == 0 || end + 1 > out_size) return -1;
    for (size_t i = 0; i < end; ++i) out[i] = lc(in[i]);
    out[end] = '\0';
    return 0;
}

/* Both row structs start with `const char *name`, so a pointer to a row is also a
 * pointer to its name field: one comparator serves both binary searches. */
static int name_cmp(const void *key, const void *elem) {
    return strcmp((const char *)key, *(const char *const *)elem);
}

/* --- tag -> box table (CSS 2.1 user-agent defaults; margins/padding in em) --- */

typedef struct tag_row {
    const char *name;
    bx_box      box;
} tag_row;

#define BLOCK   BX_DISPLAY_BLOCK
#define INLINE  BX_DISPLAY_INLINE
#define IBLOCK  BX_DISPLAY_INLINE_BLOCK
#define LITEM   BX_DISPLAY_LIST_ITEM
#define NONE    BX_DISPLAY_NONE
#define EDG(t, r, b, l) { (t), (r), (b), (l) }
#define ZERO    EDG(0.0, 0.0, 0.0, 0.0)

/* Sorted by name (ASCII, lowercase) for binary search. body has zero margin: the
 * window chrome supplies the page gutter, so there is no double margin. */
static const tag_row TAG_TABLE[] = {
    { "a",          { INLINE, ZERO, ZERO } },
    { "article",    { BLOCK,  ZERO, ZERO } },
    { "aside",      { BLOCK,  ZERO, ZERO } },
    { "b",          { INLINE, ZERO, ZERO } },
    { "base",       { NONE,   ZERO, ZERO } },
    { "blockquote", { BLOCK,  EDG(1.0, 2.5, 1.0, 2.5), ZERO } },
    { "body",       { BLOCK,  ZERO, ZERO } },
    { "button",     { IBLOCK, ZERO, ZERO } },
    { "code",       { INLINE, ZERO, ZERO } },
    { "div",        { BLOCK,  ZERO, ZERO } },
    { "em",         { INLINE, ZERO, ZERO } },
    { "figure",     { BLOCK,  ZERO, ZERO } },
    { "footer",     { BLOCK,  ZERO, ZERO } },
    { "h1",         { BLOCK,  EDG(0.67, 0.0, 0.67, 0.0), ZERO } },
    { "h2",         { BLOCK,  EDG(0.83, 0.0, 0.83, 0.0), ZERO } },
    { "h3",         { BLOCK,  EDG(1.0,  0.0, 1.0,  0.0), ZERO } },
    { "h4",         { BLOCK,  EDG(1.33, 0.0, 1.33, 0.0), ZERO } },
    { "h5",         { BLOCK,  EDG(1.67, 0.0, 1.67, 0.0), ZERO } },
    { "h6",         { BLOCK,  EDG(2.33, 0.0, 2.33, 0.0), ZERO } },
    { "head",       { NONE,   ZERO, ZERO } },
    { "header",     { BLOCK,  ZERO, ZERO } },
    { "hr",         { BLOCK,  EDG(0.5, 0.0, 0.5, 0.0), ZERO } },
    { "i",          { INLINE, ZERO, ZERO } },
    { "img",        { IBLOCK, ZERO, ZERO } },
    { "input",      { IBLOCK, ZERO, ZERO } },
    { "label",      { INLINE, ZERO, ZERO } },
    { "li",         { LITEM,  ZERO, ZERO } },
    { "link",       { NONE,   ZERO, ZERO } },
    { "main",       { BLOCK,  ZERO, ZERO } },
    { "menu",       { BLOCK,  ZERO, ZERO } },
    { "meta",       { NONE,   ZERO, ZERO } },
    { "nav",        { BLOCK,  ZERO, ZERO } },
    { "ol",         { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), EDG(0.0, 0.0, 0.0, 2.5) } },
    { "p",          { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), ZERO } },
    { "pre",        { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), ZERO } },
    { "script",     { NONE,   ZERO, ZERO } },
    { "section",    { BLOCK,  ZERO, ZERO } },
    { "select",     { IBLOCK, ZERO, ZERO } },
    { "small",      { INLINE, ZERO, ZERO } },
    { "span",       { INLINE, ZERO, ZERO } },
    { "strong",     { INLINE, ZERO, ZERO } },
    { "style",      { NONE,   ZERO, ZERO } },
    { "sub",        { INLINE, ZERO, ZERO } },
    { "sup",        { INLINE, ZERO, ZERO } },
    { "textarea",   { IBLOCK, ZERO, ZERO } },
    { "title",      { NONE,   ZERO, ZERO } },
    { "ul",         { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), EDG(0.0, 0.0, 0.0, 2.5) } },
};
#define TAG_N (sizeof TAG_TABLE / sizeof TAG_TABLE[0])

bx_box bx_default_for_tag(const char *tag) {
    const bx_box neutral = { INLINE, ZERO, ZERO };
    char buf[BX_TAG_MAX];
    if (copy_lower_trim(tag, buf, sizeof buf) != 0) return neutral;
    const tag_row *r = bsearch(buf, TAG_TABLE, TAG_N, sizeof TAG_TABLE[0], name_cmp);
    return (r != NULL) ? r->box : neutral;
}

/* --- display keyword -> value table --- */

typedef struct disp_row {
    const char *name;
    bx_display  value;
} disp_row;

/* Sorted by name. inline-flex / inline-grid map to the block-level flex / grid
 * values: the basic engine does not distinguish the container's outer level. */
static const disp_row DISP_TABLE[] = {
    { "block",        BX_DISPLAY_BLOCK },
    { "flex",         BX_DISPLAY_FLEX },
    { "grid",         BX_DISPLAY_GRID },
    { "inline",       BX_DISPLAY_INLINE },
    { "inline-block", BX_DISPLAY_INLINE_BLOCK },
    { "inline-flex",  BX_DISPLAY_FLEX },
    { "inline-grid",  BX_DISPLAY_GRID },
    { "list-item",    BX_DISPLAY_LIST_ITEM },
    { "none",         BX_DISPLAY_NONE },
};
#define DISP_N (sizeof DISP_TABLE / sizeof DISP_TABLE[0])

bx_status bx_parse_display(const char *token, bx_display *out) {
    if (token == NULL || out == NULL) return BX_ERR_NULL_ARG;
    char buf[BX_DISPLAY_MAX];
    if (copy_lower_trim(token, buf, sizeof buf) != 0) return BX_ERR_SYNTAX;
    const disp_row *r = bsearch(buf, DISP_TABLE, DISP_N, sizeof DISP_TABLE[0], name_cmp);
    if (r == NULL) return BX_ERR_SYNTAX;
    *out = r->value;
    return BX_OK;
}

bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                   double avail_w) {
    if (inset_l < 0.0) inset_l = 0.0;
    if (inset_r < 0.0) inset_r = 0.0;
    if (avail_w < 1.0) avail_w = 1.0;
    double inner = avail_w - inset_l - inset_r;
    if (inner < 1.0) inner = 1.0;
    double w = (width_cap > 0.0 && width_cap < inner) ? width_cap : inner;
    double x = inset_l;
    if (center && width_cap > 0.0) {
        double slack = inner - w;
        if (slack > 0.0) x = inset_l + slack / 2.0;
    }
    bx_hplace p = { x, w };
    return p;
}

double bx_width_cap(int w_px, int w_pct, double avail_w) {
    double px = (w_px > 0) ? (double)w_px : 0.0;
    double pc = (w_pct > 0 && avail_w > 0.0)
                ? avail_w * (double)w_pct / 1000.0 : 0.0;
    if (px > 0.0 && pc > 0.0) return (px < pc) ? px : pc;
    return (px > 0.0) ? px : pc;
}

const char *bx_display_name(bx_display d) {
    switch (d) {
        case BX_DISPLAY_BLOCK:        return "block";
        case BX_DISPLAY_INLINE:       return "inline";
        case BX_DISPLAY_INLINE_BLOCK: return "inline-block";
        case BX_DISPLAY_LIST_ITEM:    return "list-item";
        case BX_DISPLAY_FLEX:         return "flex";
        case BX_DISPLAY_GRID:         return "grid";
        case BX_DISPLAY_NONE:         return "none";
    }
    return "inline";
}
