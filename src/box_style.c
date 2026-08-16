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

/* Longest display keyword is "inline-block" (12); the tag bound is the public
 * BX_TAG_NAME_MAX (box_style.h) so a caller building a tag buffer and this module
 * agree on one number. Both are generous, so a normal token always fits and
 * anything longer fails closed instead of truncating. */
#define BX_TAG_MAX     BX_TAG_NAME_MAX
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

/* One row of the user-agent sheet. `role` is the table role the UA sheet assigns the
 * tag (CSS 2.1 17.2: `table{display:table}`, `td{display:table-cell}`, ...); it stays
 * on the SAME row as the metrics so the sheet keeps one source of truth per tag.
 * Rows that omit it get BX_TROLE_NONE from aggregate zero-init, which is the correct
 * answer for every non-table element. */
typedef struct tag_row {
    const char   *name;
    bx_box        box;
    bx_table_role role;
} tag_row;

#define BLOCK   BX_DISPLAY_BLOCK
#define INLINE  BX_DISPLAY_INLINE
#define IBLOCK  BX_DISPLAY_INLINE_BLOCK
#define LITEM   BX_DISPLAY_LIST_ITEM
#define NONE    BX_DISPLAY_NONE
#define EDG(t, r, b, l) { (t), (r), (b), (l) }
#define ZERO    EDG(0.0, 0.0, 0.0, 0.0)
/* Table roles, aliased like the display values above so a row stays one line. */
#define T_NO    BX_TROLE_NONE
#define T_TBL   BX_TROLE_TABLE
#define T_GRP   BX_TROLE_ROW_GROUP
#define T_ROW   BX_TROLE_ROW
#define T_CELL  BX_TROLE_CELL
#define T_CAP   BX_TROLE_CAPTION
#define T_COL   BX_TROLE_COLUMN

/* Sorted by name (ASCII, lowercase) for binary search. body has zero margin: the
 * window chrome supplies the page gutter, so there is no double margin.
 *
 * The vertical margins mirror the HTML user-agent sheet, which is far stingier than
 * it looks: only p, h1-h6, ul/ol/menu, dl, pre, blockquote, figure and hr get one.
 * Every structural wrapper -- div, section, header, article, footer, nav, main, and
 * the whole table and form families -- gets ZERO. Listing them explicitly is not
 * redundant with the unknown-tag fallback: it documents that the zero is the
 * user-agent sheet's answer and not an accident of the lookup missing. */
static const tag_row TAG_TABLE[] = {
    { "a",          { INLINE, ZERO, ZERO }, T_NO },
    { "address",    { BLOCK,  ZERO, ZERO }, T_NO },
    { "article",    { BLOCK,  ZERO, ZERO }, T_NO },
    { "aside",      { BLOCK,  ZERO, ZERO }, T_NO },
    { "b",          { INLINE, ZERO, ZERO }, T_NO },
    { "base",       { NONE,   ZERO, ZERO }, T_NO },
    { "blockquote", { BLOCK,  EDG(1.0, 2.5, 1.0, 2.5), ZERO }, T_NO },
    { "body",       { BLOCK,  ZERO, ZERO }, T_NO },
    { "button",     { IBLOCK, ZERO, ZERO }, T_NO },
    { "caption",    { BLOCK,  ZERO, ZERO }, T_CAP },
    { "code",       { INLINE, ZERO, ZERO }, T_NO },
    { "col",        { NONE,   ZERO, ZERO }, T_COL },
    { "colgroup",   { NONE,   ZERO, ZERO }, T_COL },
    { "dd",         { BLOCK,  EDG(0.0, 0.0, 0.0, 2.5), ZERO }, T_NO },
    { "details",    { BLOCK,  ZERO, ZERO }, T_NO },
    { "div",        { BLOCK,  ZERO, ZERO }, T_NO },
    { "dl",         { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), ZERO }, T_NO },
    { "dt",         { BLOCK,  ZERO, ZERO }, T_NO },
    { "em",         { INLINE, ZERO, ZERO }, T_NO },
    { "fieldset",   { BLOCK,  ZERO, ZERO }, T_NO },
    { "figcaption", { BLOCK,  ZERO, ZERO }, T_NO },
    { "figure",     { BLOCK,  EDG(1.0, 2.5, 1.0, 2.5), ZERO }, T_NO },
    { "footer",     { BLOCK,  ZERO, ZERO }, T_NO },
    { "form",       { BLOCK,  ZERO, ZERO }, T_NO },
    { "h1",         { BLOCK,  EDG(0.67, 0.0, 0.67, 0.0), ZERO }, T_NO },
    { "h2",         { BLOCK,  EDG(0.83, 0.0, 0.83, 0.0), ZERO }, T_NO },
    { "h3",         { BLOCK,  EDG(1.0,  0.0, 1.0,  0.0), ZERO }, T_NO },
    { "h4",         { BLOCK,  EDG(1.33, 0.0, 1.33, 0.0), ZERO }, T_NO },
    { "h5",         { BLOCK,  EDG(1.67, 0.0, 1.67, 0.0), ZERO }, T_NO },
    { "h6",         { BLOCK,  EDG(2.33, 0.0, 2.33, 0.0), ZERO }, T_NO },
    { "head",       { NONE,   ZERO, ZERO }, T_NO },
    { "header",     { BLOCK,  ZERO, ZERO }, T_NO },
    { "hr",         { BLOCK,  EDG(0.5, 0.0, 0.5, 0.0), ZERO }, T_NO },
    { "i",          { INLINE, ZERO, ZERO }, T_NO },
    { "img",        { IBLOCK, ZERO, ZERO }, T_NO },
    { "input",      { IBLOCK, ZERO, ZERO }, T_NO },
    { "label",      { INLINE, ZERO, ZERO }, T_NO },
    { "legend",     { BLOCK,  ZERO, ZERO }, T_NO },
    { "li",         { LITEM,  ZERO, ZERO }, T_NO },
    { "link",       { NONE,   ZERO, ZERO }, T_NO },
    { "main",       { BLOCK,  ZERO, ZERO }, T_NO },
    { "menu",       { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), EDG(0.0, 0.0, 0.0, 2.5) }, T_NO },
    { "meta",       { NONE,   ZERO, ZERO }, T_NO },
    { "nav",        { BLOCK,  ZERO, ZERO }, T_NO },
    { "ol",         { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), EDG(0.0, 0.0, 0.0, 2.5) }, T_NO },
    { "p",          { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), ZERO }, T_NO },
    { "pre",        { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), ZERO }, T_NO },
    { "script",     { NONE,   ZERO, ZERO }, T_NO },
    { "section",    { BLOCK,  ZERO, ZERO }, T_NO },
    { "select",     { IBLOCK, ZERO, ZERO }, T_NO },
    { "small",      { INLINE, ZERO, ZERO }, T_NO },
    { "span",       { INLINE, ZERO, ZERO }, T_NO },
    { "strong",     { INLINE, ZERO, ZERO }, T_NO },
    { "style",      { NONE,   ZERO, ZERO }, T_NO },
    { "sub",        { INLINE, ZERO, ZERO }, T_NO },
    { "summary",    { BLOCK,  ZERO, ZERO }, T_NO },
    { "sup",        { INLINE, ZERO, ZERO }, T_NO },
    { "table",      { BLOCK,  ZERO, ZERO }, T_TBL },
    { "tbody",      { BLOCK,  ZERO, ZERO }, T_GRP },
    { "td",         { BLOCK,  ZERO, ZERO }, T_CELL },
    { "textarea",   { IBLOCK, ZERO, ZERO }, T_NO },
    { "tfoot",      { BLOCK,  ZERO, ZERO }, T_GRP },
    { "th",         { BLOCK,  ZERO, ZERO }, T_CELL },
    { "thead",      { BLOCK,  ZERO, ZERO }, T_GRP },
    { "title",      { NONE,   ZERO, ZERO }, T_NO },
    { "tr",         { BLOCK,  ZERO, ZERO }, T_ROW },
    { "ul",         { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), EDG(0.0, 0.0, 0.0, 2.5) }, T_NO },
};
#define TAG_N (sizeof TAG_TABLE / sizeof TAG_TABLE[0])

bx_box bx_default_for_tag(const char *tag) {
    const bx_box neutral = { INLINE, ZERO, ZERO };
    char buf[BX_TAG_MAX];
    if (copy_lower_trim(tag, buf, sizeof buf) != 0) return neutral;
    const tag_row *r = bsearch(buf, TAG_TABLE, TAG_N, sizeof TAG_TABLE[0], name_cmp);
    return (r != NULL) ? r->box : neutral;
}

bx_table_role bx_table_role_of(const char *tag, css_display display) {
    /* The computed display decides when it names a role: that is what a table box
     * IS in CSS 2.1 17.2. The UA sheet is only the default supplier of these values,
     * so an author display both CREATES a role on a <div> and REMOVES it from a <td>. */
    switch (display) {
        case CSS_DISP_TABLE:            return BX_TROLE_TABLE;
        case CSS_DISP_TABLE_ROW_GROUP:  return BX_TROLE_ROW_GROUP;
        case CSS_DISP_TABLE_ROW:        return BX_TROLE_ROW;
        case CSS_DISP_TABLE_CELL:       return BX_TROLE_CELL;
        case CSS_DISP_TABLE_CAPTION:    return BX_TROLE_CAPTION;
        case CSS_DISP_TABLE_COLUMN:     return BX_TROLE_COLUMN;
        case CSS_DISP_UNSET:            break;   /* no author display: ask the UA sheet */
        default:                        return BX_TROLE_NONE;  /* block/flex/none/... */
    }
    char buf[BX_TAG_MAX];
    if (copy_lower_trim(tag, buf, sizeof buf) != 0) return BX_TROLE_NONE;
    const tag_row *r = bsearch(buf, TAG_TABLE, TAG_N, sizeof TAG_TABLE[0], name_cmp);
    return (r != NULL) ? r->role : BX_TROLE_NONE;
}

/* --- source-element identity across the render IPC (spec/box_style.md 4d) --- */

/* The canonical tag name behind each bx_ua_tag code, indexed BY the code. It holds no
 * metrics of its own: bx_default_for_ua feeds the name straight back into TAG_TABLE,
 * so the user-agent sheet keeps exactly ONE definition and the two lookup directions
 * cannot drift apart. BX_UA_NONE has no name -- it is the absence of a UA margin. */
static const char *const UA_NAME[BX_UA_COUNT] = {
    NULL,
    "p",
    "h1", "h2", "h3", "h4", "h5", "h6",
    "ul", "ol", "menu",
    "dl",
    "pre",
    "blockquote",
    "figure",
    "hr",
    "li",
};

bx_ua_tag bx_ua_of_tag(const char *tag) {
    char buf[BX_TAG_MAX];
    if (copy_lower_trim(tag, buf, sizeof buf) != 0) return BX_UA_NONE;
    for (int i = BX_UA_NONE + 1; i < BX_UA_COUNT; ++i) {
        if (strcmp(buf, UA_NAME[i]) == 0) return (bx_ua_tag)i;
    }
    return BX_UA_NONE;
}

bx_box bx_default_for_ua(bx_ua_tag id) {
    const bx_box neutral = { INLINE, ZERO, ZERO };
    if (id == BX_UA_NONE || id >= BX_UA_COUNT) return neutral;
    return bx_default_for_tag(UA_NAME[id]);
}

bx_box bx_block_ua_box(int heading_level, int in_list, bx_ua_tag ua) {
    /* A heading is picked by its own level: RD_HEADING carries exactly that, and it
     * outranks both the list-item approximation and the ancestor identity. */
    if (heading_level > 0) {
        if (heading_level > 6) heading_level = 6;
        return bx_default_for_ua((bx_ua_tag)(BX_UA_H1 + (heading_level - 1)));
    }
    /* Inside a list, the item's box wins so entries stay tight (spec 4d). */
    if (in_list) return bx_default_for_ua(BX_UA_LI);
    /* Otherwise the nearest block-level ancestor is the answer -- and the only
     * source that HAS one, since an inline-level element has no vertical margin. */
    return bx_default_for_ua(ua);
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
    /* One <length-percentage>, one resolver: the halves are SUMMED through
     * bx_lp_px, not raced against each other. `width: calc(100% - 6px)` carries a
     * px half of -6 and a percentage half of 100%, and its used width is 794 of an
     * 800px containing block -- taking the tighter of the two answered 800 and
     * dropped the -6px on the floor. */
    /* The intrinsic sizing keywords are not lengths: they name a measurement the
     * caller has to take (Sizing 3 section 5.1), so to a resolver that only sums a
     * px and a percentage half they read exactly like `auto` -- no declared width.
     * Letting the sentinel through would have it summed as a length, and it is a
     * large negative number. */
    int has_px  = (w_px != 0 && w_px != CSS_LEN_UNSET && w_px != CSS_LEN_AUTO &&
                   w_px != CSS_LEN_END && !CSS_LEN_IS_INTRINSIC(w_px));
    int has_pct = (w_pct != 0);
    if (!has_px && !has_pct) return 0.0;              /* no declared width */
    if (has_pct && !(avail_w > 0.0) && !has_px) return 0.0;  /* % with no basis */

    double v = bx_lp_px(w_px, w_pct, avail_w);
    /* An out-of-range result is clamped at used-value time (CSS Values 4 section
     * 10.1), and 0 is this function's "no cap" answer -- a negative cap would read
     * as a width the caller must honour. */
    return (v > 0.0) ? v : 0.0;
}


int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den,
                    double avail_w, double *out_w, double *out_h) {
    if (out_w == NULL || out_h == NULL) return 0;
    if (aspect_num <= 0 || aspect_den <= 0) return 0;
    double w = bx_width_cap(w_px, w_pct, avail_w);
    if (!(w > 0.0)) return 0;
    /* aspect-ratio is width/height, so the height is width * den/num. */
    double h = w * (double)aspect_den / (double)aspect_num;
    if (!(h > 0.0) || h != h) return 0;   /* NaN-safe, fail closed */
    *out_w = w;
    *out_h = h;
    return 1;
}

double bx_border_box_h(double declared_h, int border_box,
                       double pad_t, double pad_b, double bord_t, double bord_b) {
    if (declared_h < 0.0) declared_h = 0.0;
    if (border_box) return declared_h;
    if (pad_t < 0.0) pad_t = 0.0;
    if (pad_b < 0.0) pad_b = 0.0;
    if (bord_t < 0.0) bord_t = 0.0;
    if (bord_b < 0.0) bord_b = 0.0;
    return declared_h + pad_t + pad_b + bord_t + bord_b;
}

double bx_lp_px(int px_val, int pct_pm, double basis) {
    /* A sentinel is the absence of an absolute length, not a huge negative one.
     * Without this a `padding-left: 5%` (px half CSS_LEN_UNSET) would resolve to
     * INT_MIN plus the percentage. */
    double px = (px_val == CSS_LEN_UNSET || px_val == CSS_LEN_AUTO ||
                 px_val == CSS_LEN_END) ? 0.0 : (double)px_val;
    if (pct_pm == 0) return px;
    if (!(basis > 0.0) || basis != basis) return px;   /* NaN-safe */
    return px + basis * (double)pct_pm / 1000.0;
}

double bx_content_cap(double width_cap, int border_box,
                      double pad_l, double pad_r, double bord_l, double bord_r) {
    if (!border_box || width_cap <= 0.0) return width_cap;
    if (pad_l < 0.0) pad_l = 0.0;
    if (pad_r < 0.0) pad_r = 0.0;
    if (bord_l < 0.0) bord_l = 0.0;
    if (bord_r < 0.0) bord_r = 0.0;
    double w = width_cap - pad_l - pad_r - bord_l - bord_r;
    return (w < 1.0) ? 1.0 : w;
}

/* One background-size component in px, or -1 when it is `auto` (Backgrounds 3
 * section 3.9). `auto` is both the explicit keyword and the absence of a
 * declaration, which are the same thing for sizing. */
static double bg_size_component(int px_val, int pct_pm, double area) {
    if (pct_pm != 0) return bx_lp_px(px_val, pct_pm, area);
    if (px_val == CSS_LEN_AUTO || px_val == CSS_LEN_UNSET ||
        CSS_LEN_IS_INTRINSIC(px_val)) return -1.0;
    return (double)px_val;
}

int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h,
                        double *out_x, double *out_y) {
    if (in == NULL || out_w == NULL || out_h == NULL ||
        out_x == NULL || out_y == NULL) return 0;
    if (!(in->nat_w > 0.0) || !(in->nat_h > 0.0)) return 0;
    if (!(in->area_w > 0.0) || !(in->area_h > 0.0)) return 0;

    double iw, ih;
    if (in->size_kw == CSS_BGS_COVER || in->size_kw == CSS_BGS_CONTAIN) {
        double rx = in->area_w / in->nat_w, ry = in->area_h / in->nat_h;
        double s = (in->size_kw == CSS_BGS_COVER) ? ((rx > ry) ? rx : ry)
                                                  : ((rx < ry) ? rx : ry);
        iw = in->nat_w * s;
        ih = in->nat_h * s;
    } else {
        double cw = bg_size_component(in->size_w, in->size_w_pct, in->area_w);
        double ch = bg_size_component(in->size_h, in->size_h_pct, in->area_h);
        if (cw < 0.0 && ch < 0.0)      { iw = in->nat_w; ih = in->nat_h; }
        /* One auto keeps the intrinsic ratio -- that is what makes a one-value
         * `background-size: 44px` a scaled icon and not a squashed one. */
        else if (ch < 0.0)             { iw = cw; ih = cw * in->nat_h / in->nat_w; }
        else if (cw < 0.0)             { iw = ch * in->nat_w / in->nat_h; ih = ch; }
        else                           { iw = cw; ih = ch; }
    }
    if (!(iw > 0.0) || !(ih > 0.0) || iw != iw || ih != ih) return 0;

    /* A percentage aligns that fraction of the image with the same fraction of
     * the area, so the free space is what it scales (Backgrounds 3 section 3.6). */
    double ox = bx_lp_px((in->pos_x == CSS_LEN_UNSET) ? 0 : in->pos_x,
                         in->pos_x_pct, in->area_w - iw);
    double oy = bx_lp_px((in->pos_y == CSS_LEN_UNSET) ? 0 : in->pos_y,
                         in->pos_y_pct, in->area_h - ih);
    *out_w = iw;
    *out_h = ih;
    *out_x = ox;
    *out_y = oy;
    return 1;
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
