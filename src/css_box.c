#include "css_box.h"
#include "css_decl.h"
#include "css.h"
#include "css_color.h"
#include "css_length.h"
#include "css_select.h"
#include "css_values.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

static int cb_parse_num(const char *s, double *out, const char **endp)
{
    return cl_number(s, out, endp);
}

static int cb_wide_keyword(const char *v)
{
    return csel_ci_eq(v, "initial") || csel_ci_eq(v, "inherit") ||
           csel_ci_eq(v, "unset") || csel_ci_eq(v, "revert") ||
           csel_ci_eq(v, "revert-layer");
}

static size_t cb_copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)
{
    size_t n;
    if (s == NULL || dst == NULL || cap == 0 || a >= b) {
        return (size_t)-1;
    }
    while (a < b && (s[a] == ' ' || s[a] == '\t')) {
        ++a;
    }
    while (b > a && (s[b - 1] == ' ' || s[b - 1] == '\t')) {
        --b;
    }
    n = b - a;
    if (n + 1 > cap) {
        return (size_t)-1;
    }
    memcpy(dst, s + a, n);
    dst[n] = '\0';
    return n;
}

/* Resolves a NUL-terminated <length> token to px through the canonical
 * resolver. Returns 1 on success. This is the ONLY place in the cascade that
 * turns a unit into pixels -- see spec/css_length.md for why that matters. */
int cb_length_px(const char *v, double *px) {
    cl_ctx ctx = cl_ctx_initial();
    return cl_resolve(v, &ctx, px) == CL_OK;
}

int cb_interp_align(const char *v) {
    if (csel_ci_eq(v, "left") || csel_ci_eq(v, "start")) return CSS_ALIGN_LEFT;
    if (csel_ci_eq(v, "center")) return CSS_ALIGN_CENTER;
    if (csel_ci_eq(v, "right") || csel_ci_eq(v, "end")) return CSS_ALIGN_RIGHT;
    if (csel_ci_eq(v, "justify")) return CSS_ALIGN_JUSTIFY;
    return -1;
}

/* font-size as a percent, plus whether that percent is ABSOLUTE (of the 16px root)
 * or RELATIVE (of the inherited size). Absolute: px/pt/rem/viewport units and the
 * absolute keywords. Relative: em, %, and smaller/larger. *abs is written on every
 * path, including the -1 failure, so the caller never reads it uninitialised.
 *
 * The distinction is load-bearing, not cosmetic: without it the painter multiplied
 * an absolute `font-size: 40px` onto the user-agent heading scale and every author-
 * styled <h1> came out at 80px. See spec/css.md "font-size: absolute vs relative". */
int cb_interp_fontsize_ex(const char *v, int *abs_out) {
    *abs_out = 1;
    if (csel_ci_eq(v, "medium")) return 100;
    if (csel_ci_eq(v, "small")) return 85;
    if (csel_ci_eq(v, "large")) return 120;
    if (csel_ci_eq(v, "x-large")) return 150;
    if (csel_ci_eq(v, "xx-large")) return 200;
    if (csel_ci_eq(v, "x-small")) return 75;
    if (csel_ci_eq(v, "xx-small")) return 60;
    /* smaller/larger step off the INHERITED size, so they stay relative. */
    if (csel_ci_eq(v, "smaller")) { *abs_out = 0; return 85; }
    if (csel_ci_eq(v, "larger"))  { *abs_out = 0; return 120; }

    double num;
    const char *end;
    if (!cb_parse_num(v, &num, &end)) { *abs_out = 0; return -1; }
    while (*end == ' ' || *end == '\t') ++end;

    /* A percentage is not a <length>: it is relative to the INHERITED size by
     * definition, so it is handled here and never reaches the resolver. */
    if (end[0] == '%' && end[1] == '\0') {
        *abs_out = 0;
        return css_round_clamp(num, 10, 1000);
    }

    /* Everything else is a real length. Whether it is absolute or relative is
     * derived from the unit family instead of a hand-written whitelist: a
     * font-relative unit (em/ex/ch/cap/ic/lh) steps off the inherited size,
     * while px/pt/cm/rem/vw and friends do not. Adding a unit to css_length
     * classifies it correctly here for free. */
    double px;
    if (!cb_length_px(v, &px)) { *abs_out = 0; return -1; }
    *abs_out = !cl_unit_is_font_relative(end, 0);

    /* One formula for both families. The resolver ran with font_size at the CSS
     * initial value, so px/initial is the absolute size in "initial units" for
     * an absolute unit AND the multiple of the inherited size for a relative
     * one -- `2ex` correctly yields 100% (2 x 0.5em), not 200%. */
    return css_round_clamp(px / CL_INITIAL_FONT_SIZE * 100.0, 10, 1000);
}


/* line-height as a percent of the natural line box. A unitless multiplier ("1.5" ->
 * 150) or a percent ("160%" -> 160); "normal" is unset (the UA default). Absolute px/em
 * line-heights need a font size we don't have here, so they are dropped (return -1).
 * Clamped to [CSS_LINE_MIN, CSS_LINE_MAX] (anti-DoS). */
int cb_interp_lineheight(const char *v) {
    if (csel_ci_eq(v, "normal")) return 0;
    double num;
    const char *end;
    if (!cb_parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    double pct;
    if (end[0] == '\0')                       pct = num * 100.0; /* unitless */
    else if (end[0] == '%' && end[1] == '\0') pct = num;
    else {
        /* Any real <length> -- including pt/pc/cm/ex/ch, all of which used to be
         * dropped here while px and em were accepted. Stored as a percentage of
         * the CSS initial font-size; layout re-multiplies it by the fragment's
         * own font-size (CSS 2.1 section 10.8.1). */
        double px;
        if (!cb_length_px(v, &px)) return -1;
        pct = px / CL_INITIAL_FONT_SIZE * 100.0;
    }
    return css_round_clamp(pct, CSS_LINE_MIN, CSS_LINE_MAX);
}

int cb_interp_weight(const char *v) {
    if (csel_ci_eq(v, "bold") || csel_ci_eq(v, "bolder")) return 1;
    if (csel_ci_eq(v, "normal") || csel_ci_eq(v, "lighter")) return 0;
    double num;
    const char *end;
    if (cb_parse_num(v, &num, &end) && *end == '\0') return num >= 600.0 ? 1 : 0;
    return -1;
}

int cb_interp_style(const char *v) {
    if (csel_ci_eq(v, "italic") || csel_ci_eq(v, "oblique")) return 1;
    if (csel_ci_eq(v, "normal")) return 0;
    return -1;
}

/* text-decoration / text-decoration-line: OR of the line keywords underline /
 * overline / line-through found in the (space-separated) value. "none" -> 0
 * (explicit removal). Style/color/thickness tokens (wavy, red, 2px, solid, ...) are
 * ignored. A value carrying no line keyword at all is unsupported -> -1 (dropped). */
int cb_interp_textdeco(const char *v) {
    int bits = 0, saw_keyword = 0;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        while (*p != '\0' && *p != ' ' && *p != '\t') ++p;  /* drop an over-long token tail */
        if (csel_ci_eq(tok, "none")) return 0;
        else if (csel_ci_eq(tok, "underline"))    { bits |= CSS_DECO_UNDERLINE;    saw_keyword = 1; }
        else if (csel_ci_eq(tok, "overline"))     { bits |= CSS_DECO_OVERLINE;     saw_keyword = 1; }
        else if (csel_ci_eq(tok, "line-through")) { bits |= CSS_DECO_LINE_THROUGH; saw_keyword = 1; }
        /* anything else (style/color/thickness): ignored */
    }
    return saw_keyword ? bits : -1;
}

int cb_interp_display(const char *v) {
    if (csel_ci_eq(v, "none")) return CSS_DISP_NONE;
    if (csel_ci_eq(v, "block")) return CSS_DISP_BLOCK;
    if (csel_ci_eq(v, "inline")) return CSS_DISP_INLINE;
    if (csel_ci_eq(v, "inline-block")) return CSS_DISP_INLINE_BLOCK;
    if (csel_ci_eq(v, "list-item")) return CSS_DISP_LIST_ITEM;
    if (csel_ci_eq(v, "flex") || csel_ci_eq(v, "inline-flex")) return CSS_DISP_FLEX;
    if (csel_ci_eq(v, "grid") || csel_ci_eq(v, "inline-grid")) return CSS_DISP_GRID;
    /* The table roles (CSS 2.1 17.2). Dropping these collapsed every CSS-built table
     * to one cell per row; see spec/css.md "display de la familia tabla". */
    if (csel_ci_eq(v, "table") || csel_ci_eq(v, "inline-table")) return CSS_DISP_TABLE;
    if (csel_ci_eq(v, "table-row")) return CSS_DISP_TABLE_ROW;
    if (csel_ci_eq(v, "table-cell")) return CSS_DISP_TABLE_CELL;
    if (csel_ci_eq(v, "table-caption")) return CSS_DISP_TABLE_CAPTION;
    if (csel_ci_eq(v, "table-row-group") || csel_ci_eq(v, "table-header-group")
        || csel_ci_eq(v, "table-footer-group")) return CSS_DISP_TABLE_ROW_GROUP;
    if (csel_ci_eq(v, "table-column") || csel_ci_eq(v, "table-column-group"))
        return CSS_DISP_TABLE_COLUMN;
    /* `flow-root` is a block box that establishes a block formatting context
     * (CSS Display 3 2.1) -- the modern clearfix. This engine gives every block
     * box its own formatting context already, so `block` IS its used behaviour
     * here; the distinction it draws is one this layout cannot currently observe.
     * The two-keyword `display: <outer> <inner>` forms of Display 3 2 reduce the
     * same way: the OUTER keyword is what the box model reads. */
    if (csel_ci_eq(v, "flow-root") || csel_ci_eq(v, "block flow") ||
        csel_ci_eq(v, "block flow-root")) return CSS_DISP_BLOCK;
    if (csel_ci_eq(v, "inline flow-root")) return CSS_DISP_INLINE_BLOCK;
    if (csel_ci_eq(v, "block flex") || csel_ci_eq(v, "inline flex"))
        return CSS_DISP_FLEX;
    if (csel_ci_eq(v, "block grid") || csel_ci_eq(v, "inline grid"))
        return CSS_DISP_GRID;
    /* The vendor spellings of `flex` ARE `flex`: -webkit-flex and -ms-flexbox name
     * the same formatting context with the same box model, so an autoprefixed sheet
     * that writes both gets one answer either way. */
    if (csel_ci_eq(v, "-webkit-flex") || csel_ci_eq(v, "-moz-flex") ||
        csel_ci_eq(v, "-ms-flexbox") ||
        csel_ci_eq(v, "-webkit-inline-flex") || csel_ci_eq(v, "-moz-inline-flex") ||
        csel_ci_eq(v, "-ms-inline-flexbox")) return CSS_DISP_FLEX;
    if (csel_ci_eq(v, "-ms-grid") || csel_ci_eq(v, "-ms-inline-grid"))
        return CSS_DISP_GRID;
    /* `-webkit-box` / `-webkit-flexbox` is the 2009 flexbox draft. It is a
     * DIFFERENT spec, but the difference is in the item properties (box-flex,
     * box-pack, box-orient), not in the container's box: it is a block-level box
     * whose children lay out along one axis, which is what CSS_DISP_FLEX models
     * here. Leaving it unset was not neutral -- it is the container half of the
     * `-webkit-line-clamp` idiom (Overflow 3 "Legacy"), so dropping it dropped
     * every clamped card title with it. The single-axis default of the 2009 draft
     * is horizontal, same as flex-direction's, so the mapping needs no extra rule;
     * `-webkit-box-orient: vertical` supplies the column case and is handled as an
     * alias of flex-direction. */
    if (csel_ci_eq(v, "-webkit-box") || csel_ci_eq(v, "-moz-box") ||
        csel_ci_eq(v, "-webkit-inline-box") || csel_ci_eq(v, "-moz-inline-box"))
        return CSS_DISP_FLEX;
    /* `contents` makes the element generate no box of its own while its children
     * still generate theirs (Display 3 3). This engine has no box-less pass-through,
     * and treating it as `none` would DELETE the subtree -- the opposite of what it
     * means -- so it reduces to the element's normal block box, which keeps every
     * child rendered. */
    if (csel_ci_eq(v, "contents")) return CSS_DISP_BLOCK;
    if (csel_ci_eq(v, "inline-list-item")) return CSS_DISP_LIST_ITEM;
    /* Ruby has no formatting context here; its boxes are inline (Ruby 1 2). */
    if (csel_ci_eq(v, "ruby") || csel_ci_eq(v, "ruby-base") ||
        csel_ci_eq(v, "ruby-text") || csel_ci_eq(v, "ruby-base-container") ||
        csel_ci_eq(v, "ruby-text-container")) return CSS_DISP_INLINE;
    return -1;  /* unknown display: leave unset */
}

/* gap / grid-gap / column-gap: leading length as px (a two-value gap keeps the
 * first), "normal" -> 0; clamped to [0, CSS_GAP_MAX]. -1 when not a length. */
int cb_interp_len(const char *v, int allow_auto, int *out);


/* One gap length. Reuses interp_len (px / em / rem / bare 0 / calc() / math
 * functions), so a `gap: 1em` is 16px instead of the old misparse-as-1px, and a
 * trailing junk token fails closed. Negative fails; clamped to CSS_GAP_MAX. */
int cb_interp_gap(const char *v) {
    if (csel_ci_eq(v, "normal")) return 0;
    int px;
    if (!cb_interp_len(v, 0, &px) || px < 0) return -1;
    return (px > CSS_GAP_MAX) ? CSS_GAP_MAX : px;
}

int cb_interp_justify(const char *v) {
    if (csel_ci_eq(v, "flex-start") || csel_ci_eq(v, "start") || csel_ci_eq(v, "normal"))
        return CSS_JUSTIFY_START;
    if (csel_ci_eq(v, "flex-end") || csel_ci_eq(v, "end")) return CSS_JUSTIFY_END;
    if (csel_ci_eq(v, "center")) return CSS_JUSTIFY_CENTER;
    if (csel_ci_eq(v, "space-between")) return CSS_JUSTIFY_SPACE_BETWEEN;
    if (csel_ci_eq(v, "space-around")) return CSS_JUSTIFY_SPACE_AROUND;
    if (csel_ci_eq(v, "space-evenly")) return CSS_JUSTIFY_SPACE_EVENLY;
    return -1;  /* unknown: fail closed */
}

/* grid-template-columns / grid-template-rows: counts the tracks in a track-list,
 * paren-aware (a token may contain balanced parens, e.g. "minmax(100px, 1fr)", and
 * is then ONE track, not split by its internal comma/space) and expanding
 * repeat(<positive-integer>, <track-list>) into (count * tracks-in-pattern).
 * repeat(auto-fill|...) / repeat(auto-fit|...) need an available width this pure
 * parser does not have, so they fail the WHOLE value (return -1), like %/vw
 * elsewhere in this module -- never a wrong guess. A malformed repeat() (no comma,
 * non-integer count) likewise fails the whole value.
 * TRACK SIZES (2026-07-11): the walker optionally resolves the size of each of the
 * first `szcap` tracks into `sizes` (0 auto / >0 px / <0 fr x100 -- see
 * css_style.grid_col_w); *pos is the running track index across the recursion.
 * count_tracks (sizes == NULL) keeps the count-only behaviour. */
static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos);

static int cb_starts_with_ci(const char *s, const char *pre) {
    for (; *pre != '\0'; ++s, ++pre)
        if (csel_lower_ch(*s) != csel_lower_ch(*pre)) return 0;
    return 1;
}

static int count_tracks(const char *s, size_t n) {
    int pos = 0;
    return walk_tracks(s, n, NULL, 0, &pos);
}

/* Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0);
 * minmax(a,b) -> the size of its max component b; auto/%/unknown -> 0 (an equal
 * `auto` share downstream, never a wrong guess). */
static int track_size_of(const char *tok) {
    size_t len = strlen(tok);
    if (len > 7 && cb_starts_with_ci(tok, "minmax(") && tok[len - 1] == ')') {
        /* take the max component: the part after the top-level comma */
        size_t comma = 0;
        int depth = 0;
        for (size_t k = 7; k + 1 < len; ++k) {
            if (tok[k] == '(') ++depth;
            else if (tok[k] == ')') --depth;
            else if (tok[k] == ',' && depth == 0) { comma = k; break; }
        }
        if (comma == 0) return 0;
        char mx[CSS_TOK_MAX];
        size_t a = comma + 1, b = len - 1;
        while (a < b && (tok[a] == ' ' || tok[a] == '\t')) ++a;
        while (b > a && (tok[b - 1] == ' ' || tok[b - 1] == '\t')) --b;
        if (a >= b || b - a >= sizeof mx) return 0;
        memcpy(mx, tok + a, b - a);
        mx[b - a] = '\0';
        return track_size_of(mx);
    }
    double num;
    const char *end;
    if (cb_parse_num(tok, &num, &end) && csel_ci_eq(end, "fr") && num > 0.0)
        return -css_round_clamp(num * 100.0, 1, CSS_FLEX_FACTOR_MAX);
    int px;
    if (cb_interp_len(tok, 0, &px) && px > 0) return px;
    return 0;
}

static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                            int *sizes, int szcap, int *pos) {
    size_t inner_a = tokstart + 7;                  /* past "repeat(" */
    size_t inner_b = tokstart + toklen - 1;          /* before the matching ')' */
    size_t comma = inner_b;
    int depth = 0;
    for (size_t k = inner_a; k < inner_b; ++k) {
        if (s[k] == '(') ++depth;
        else if (s[k] == ')') --depth;
        else if (s[k] == ',' && depth == 0) { comma = k; break; }
    }
    if (comma >= inner_b) return -1;                 /* no comma: malformed */
    size_t ca = inner_a, cb = comma;
    while (ca < cb && (s[ca] == ' ' || s[ca] == '\t')) ++ca;
    while (cb > ca && (s[cb - 1] == ' ' || s[cb - 1] == '\t')) --cb;
    char cbuf[CSS_TOK_MAX];
    size_t clen = cb - ca;
    if (clen == 0 || clen >= sizeof cbuf) return -1;
    memcpy(cbuf, s + ca, clen);
    cbuf[clen] = '\0';
    if (csel_ci_eq(cbuf, "auto-fill") || csel_ci_eq(cbuf, "auto-fit")) return -1;
    double num;
    const char *end;
    if (!cb_parse_num(cbuf, &num, &end) || *end != '\0' || num < 1.0) return -1;
    int reps = css_round_clamp(num, 1, (int)CSS_GRID_COLS_MAX);
    /* Walk the pattern once (its own sizes into a local buffer), then replicate. */
    int inner_sz[CSS_GRID_TRACKS_MAX];
    int inner_pos = 0;
    int inner_tracks = walk_tracks(s + comma + 1, inner_b - (comma + 1),
                                   (sizes != NULL) ? inner_sz : NULL,
                                   (sizes != NULL) ? CSS_GRID_TRACKS_MAX : 0,
                                   &inner_pos);
    if (inner_tracks < 1) return -1;
    for (int r = 0; r < reps; ++r)
        for (int t = 0; t < inner_tracks; ++t) {
            if (sizes != NULL && *pos < szcap)
                sizes[*pos] = (t < CSS_GRID_TRACKS_MAX) ? inner_sz[t] : 0;
            if (*pos < (int)CSS_GRID_COLS_MAX) ++(*pos);
        }
    long total = (long)reps * (long)inner_tracks;
    return (total > (long)CSS_GRID_COLS_MAX) ? (int)CSS_GRID_COLS_MAX : (int)total;
}

static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos) {
    int total = 0;
    size_t i = 0;
    while (i < n) {
        while (i < n && (s[i] == ' ' || s[i] == '\t')) ++i;
        if (i >= n) break;
        size_t start = i;
        int depth = 0;
        while (i < n) {
            if (s[i] == '(') ++depth;
            else if (s[i] == ')') { if (depth > 0) --depth; }
            else if (depth == 0 && (s[i] == ' ' || s[i] == '\t')) break;
            ++i;
        }
        size_t toklen = i - start;
        int is_repeat = toklen > 7 && s[start + toklen - 1] == ')' &&
            csel_lower_ch(s[start]) == 'r' && csel_lower_ch(s[start + 1]) == 'e' &&
            csel_lower_ch(s[start + 2]) == 'p' && csel_lower_ch(s[start + 3]) == 'e' &&
            csel_lower_ch(s[start + 4]) == 'a' && csel_lower_ch(s[start + 5]) == 't' &&
            s[start + 6] == '(';
        if (is_repeat) {
            int rc = count_one_repeat(s, start, toklen, sizes, szcap, pos);
            if (rc < 0) return -1;
            total += rc;
        } else {
            if (sizes != NULL && *pos < szcap) {
                char tok[CSS_TOK_MAX];
                if (toklen < sizeof tok) {
                    memcpy(tok, s + start, toklen);
                    tok[toklen] = '\0';
                    sizes[*pos] = track_size_of(tok);
                } else {
                    sizes[*pos] = 0;   /* overlong token: auto */
                }
            }
            if (*pos < (int)CSS_GRID_COLS_MAX) ++(*pos);
            total += 1;
        }
        if (total > (int)CSS_GRID_COLS_MAX) total = (int)CSS_GRID_COLS_MAX;
    }
    return total;
}

/* grid-template-columns / -rows: track count via count_tracks (repeat()/minmax()
 * aware), clamped to [1, CSS_GRID_COLS_MAX]. "none"/empty -> -1 (unset). url()
 * defensively dropped (never reachable in practice: a track size cannot be a URL,
 * but this mirrors the same guard the other properties carry). */
int cb_interp_gridcols(const char *v) {
    if (csel_substr(v, "url(", 1)) return -1;
    if (csel_ci_eq(v, "none")) return -1;
    int n = count_tracks(v, strlen(v));
    if (n < 1) return -1;
    if (n > CSS_GRID_COLS_MAX) n = CSS_GRID_COLS_MAX;
    return n;
}

/* grid-template-columns: track count PLUS the first CSS_GRID_TRACKS_MAX track
 * sizes, emitted in lock-step (P_GRIDCOLS + P_GRID_TRACK0..7; unsized slots emit
 * 0 = auto so a higher-tier declaration fully resets a lower-tier one).
 * none/url()/malformed drop the declaration, exactly like interp_gridcols. */
int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap) {
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "none")) return 0;
    int sizes[CSS_GRID_TRACKS_MAX] = { 0 };
    int pos = 0;
    int n = walk_tracks(val, strlen(val), sizes, CSS_GRID_TRACKS_MAX, &pos);
    if (n < 1) return 0;
    if (n > CSS_GRID_COLS_MAX) n = CSS_GRID_COLS_MAX;
    if (cap < 1 + CSS_GRID_TRACKS_MAX) return 0;
    dst[0].prop = P_GRIDCOLS;
    dst[0].ival = n;
    for (int k = 0; k < CSS_GRID_TRACKS_MAX; ++k) {
        dst[1 + k].prop = P_GRID_TRACK0 + k;
        dst[1 + k].ival = sizes[k];
    }
    return 1 + CSS_GRID_TRACKS_MAX;
}

/* --- calc() for length values -------------------------------------------------
 *
 * A small recursive-descent evaluator over +, -, *, / and parens. Operands are
 * plain numbers or px/em/rem/vw/vh/vmin/vmax lengths -- the same units interp_len
 * itself accepts (no %: this engine has no containing block to resolve it
 * against, so calc() cannot reach further than interp_len already can). Bounded:
 * the whole expression already lives inside one CSS_TOK_MAX (64-byte) token,
 * and CSS_CALC_MAX_DEPTH additionally caps parenthesis nesting -- never unbounded
 * recursion. Dimensionally checked like real calc(): +/- require both sides to be
 * the same "shape" (both lengths, or both bare numbers); * requires at least one
 * bare-number side; / requires a bare-number, non-zero divisor. A bare-number
 * *result* (e.g. calc(2 * 3), no length anywhere) is not a valid length -> fails. */
#define CSS_CALC_MAX_DEPTH 8

/* Max arguments of one min()/max() call (clamp() takes exactly three). More fail
 * the declaration (anti-DoS; the whole value already fits one CSS_TOK_MAX token). */
#define CSS_MATHFN_MAX_ARGS 8

/* A calc() term: its value at the parse context PLUS its derivative with
 * respect to the element's font-size (spec/css_length.md section 8.4). Carrying
 * `em` through the arithmetic is what makes `calc(2em + 10px)` exact at any
 * font-size instead of frozen at the initial 16px. */
/* `pct` is the percentage component, carried through the arithmetic exactly like
 * `em` and for exactly the same reason: a calc() result is the affine combination
 * a*1px + b*1em + c*1%, and CSS Values 4 section 10 lets an author mix all three.
 * Collapsing the percentage at parse time is impossible -- its basis is the
 * containing block, which the element-free cascade does not know -- so it travels
 * symbolically to bx_lp_px, the one place a percentage becomes pixels.
 *
 * Before this, calc() understood no percentage at all, so `width: calc(100% - 2rem)`
 * -- the single most common responsive idiom on the web -- was dropped whole. */
typedef struct calc_val { double px; double em; double pct; int is_length; } calc_val;
typedef struct calc_parser { const char *s; size_t n, i; } calc_parser;

static void calc_skip_ws(calc_parser *p) {
    while (p->i < p->n && (p->s[p->i] == ' ' || p->s[p->i] == '\t')) ++p->i;
}

static int calc_expr(calc_parser *p, calc_val *out, int depth);

/* Consumes "name(" (case-insensitive) at the cursor; 0 leaves the cursor put. */
static int calc_match_fn(calc_parser *p, const char *name) {
    size_t len = strlen(name);
    if (p->i + len + 1 > p->n) return 0;
    for (size_t k = 0; k < len; ++k)
        if (csel_lower_ch(p->s[p->i + k]) != name[k]) return 0;
    if (p->s[p->i + len] != '(') return 0;
    p->i += len + 1;
    return 1;
}

/*
 * The font-size derivative of a min()/max()/clamp() result.
 *
 * These are piecewise linear, not affine: WHICH operand wins depends on the
 * font-size, so once two operands disagree about their derivative the result
 * has no single slope and cannot be folded later. That fails closed to 0 --
 * i.e. the value stays frozen at the initial context, which is exactly what the
 * engine did before font-relative folding existed. Inventing a slope would be
 * worse than keeping the old answer.
 *
 * When every operand shares one derivative the result provably has it too,
 * whichever operand wins, so that case IS exact and is kept.
 */
/* Shared by BOTH symbolic components: the percentage is piecewise for exactly the
 * same reason the em derivative is -- which operand min()/max()/clamp() selects
 * depends on the containing block, which is unknown here -- so it obeys the same
 * rule instead of a second copy of it. want_pct selects the component. */
static double calc_piecewise(const calc_val *args, int nargs, int want_pct) {
    if (nargs <= 0) return 0.0;
    double first = want_pct ? args[0].pct : args[0].em;
    for (int k = 1; k < nargs; ++k) {
        double v = want_pct ? args[k].pct : args[k].em;
        if (v != first) return 0.0;
    }
    return first;
}

/* min()/max()/clamp() (2026-07-10): comma-separated full expressions, every
 * argument the same shape (all lengths or all bare numbers, like +/-). clamp(lo,
 * mid, hi) is max(lo, min(mid, hi)) per CSS and takes exactly three arguments;
 * min/max take 1..CSS_MATHFN_MAX_ARGS. Depth-bounded with the parens. kind: 0
 * min, 1 max, 2 clamp. */
static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind) {
    if (depth >= CSS_CALC_MAX_DEPTH) return 0;
    calc_val args[CSS_MATHFN_MAX_ARGS];
    int nargs = 0;
    for (;;) {
        if (nargs >= CSS_MATHFN_MAX_ARGS) return 0;
        if (!calc_expr(p, &args[nargs], depth + 1)) return 0;
        ++nargs;
        calc_skip_ws(p);
        if (p->i < p->n && p->s[p->i] == ',') { ++p->i; continue; }
        break;
    }
    if (p->i >= p->n || p->s[p->i] != ')') return 0;
    ++p->i;
    for (int k = 1; k < nargs; ++k)
        if (args[k].is_length != args[0].is_length) return 0;
    /* A PERCENTAGE inside min()/max()/clamp() is not resolvable here and must fail
     * closed, not degrade. Unlike the em derivative -- where falling back to slope
     * 0 still leaves a valid pixel value -- the comparison itself is meaningless
     * without the basis: min(50%, 600px) would compare a px half of 0 against 600
     * and pick 0, i.e. collapse the element to zero width. Dropping the declaration
     * leaves the element at its content size, which is the honest answer.
     * Percentages in a plain calc() ARE resolvable (they stay symbolic and are
     * summed later); only the piecewise functions have to refuse. */
    for (int k = 0; k < nargs; ++k)
        if (args[k].pct != 0.0) return 0;
    if (kind == 2) {
        if (nargs != 3) return 0;
        double m = (args[1].px < args[2].px) ? args[1].px : args[2].px;
        out->px = (args[0].px > m) ? args[0].px : m;
        out->em  = calc_piecewise(args, nargs, 0);
        out->pct = calc_piecewise(args, nargs, 1);
        out->is_length = args[0].is_length;
        return 1;
    }
    double best = args[0].px;
    for (int k = 1; k < nargs; ++k) {
        if (kind == 0) { if (args[k].px < best) best = args[k].px; }
        else           { if (args[k].px > best) best = args[k].px; }
    }
    out->px = best;
    out->em  = calc_piecewise(args, nargs, 0);
    out->pct = calc_piecewise(args, nargs, 1);
    out->is_length = args[0].is_length;
    return 1;
}

/* One number or length token, a parenthesized sub-expression, a nested calc(),
 * or a math function call (min/max/clamp). */
static int calc_factor(calc_parser *p, calc_val *out, int depth) {
    calc_skip_ws(p);
    if (calc_match_fn(p, "min"))   return calc_mathfn(p, out, depth, 0);
    if (calc_match_fn(p, "max"))   return calc_mathfn(p, out, depth, 1);
    if (calc_match_fn(p, "clamp")) return calc_mathfn(p, out, depth, 2);
    if (calc_match_fn(p, "calc")) {          /* nested calc(): plain grouping */
        if (depth >= CSS_CALC_MAX_DEPTH) return 0;
        if (!calc_expr(p, out, depth + 1)) return 0;
        calc_skip_ws(p);
        if (p->i >= p->n || p->s[p->i] != ')') return 0;
        ++p->i;
        return 1;
    }
    if (p->i < p->n && p->s[p->i] == '(') {
        if (depth >= CSS_CALC_MAX_DEPTH) return 0;
        ++p->i;
        if (!calc_expr(p, out, depth + 1)) return 0;
        calc_skip_ws(p);
        if (p->i >= p->n || p->s[p->i] != ')') return 0;
        ++p->i;
        return 1;
    }
    int neg = 0;
    if (p->i < p->n && (p->s[p->i] == '+' || p->s[p->i] == '-')) {
        neg = (p->s[p->i] == '-');
        ++p->i;
        calc_skip_ws(p);
    }
    double num;
    const char *end;
    if (!cb_parse_num(p->s + p->i, &num, &end)) return 0;
    p->i += (size_t)(end - (p->s + p->i));
    if (neg) num = -num;
    /* Collect the unit identifier that follows the number and resolve it
     * through the canonical table, so calc() understands exactly the same set
     * of units as a plain declaration -- it used to know only px/em/rem and the
     * viewport units, which made `calc(100% - 12pt)` fail as a whole while
     * `calc(100% - 12px)` worked. A run that is not a length unit falls through
     * to the bare-number path, whose leftover characters then fail the whole
     * expression (fail closed). */
    size_t un = 0;
    while (p->i + un < p->n && un < CL_MAX_TOKEN) {
        char c = csel_lower_ch(p->s[p->i + un]);
        if (c < 'a' || c > 'z') break;
        ++un;
    }
    if (un > 0) {
        cl_ctx ctx = cl_ctx_initial();
        double per;
        if (cl_unit_scale(p->s + p->i, un, &ctx, &per) == CL_OK) {
            out->px = num * per;
            out->em = num * cl_unit_font_ratio(p->s + p->i, un);
            out->pct = 0.0;
            out->is_length = 1; p->i += un; return 1;
        }
    }
    if (p->i < p->n && p->s[p->i] == '%') {
        out->px = 0.0;
        out->em = 0.0;
        out->pct = num;
        out->is_length = 1;   /* a <percentage> is dimensional, like a length */
        ++p->i;
        return 1;
    }
    out->px = num;                      /* a bare number: length only if exactly 0 */
    out->em = 0.0;
    out->pct = 0.0;
    out->is_length = (num == 0.0);
    return 1;
}

/* '*' and '/' bind tighter than '+'/'-'. */
static int calc_term(calc_parser *p, calc_val *out, int depth) {
    if (!calc_factor(p, out, depth)) return 0;
    for (;;) {
        calc_skip_ws(p);
        if (p->i >= p->n || (p->s[p->i] != '*' && p->s[p->i] != '/')) break;
        char op = p->s[p->i++];
        calc_val rhs;
        if (!calc_factor(p, &rhs, depth)) return 0;
        if (op == '*') {
            if (out->is_length && rhs.is_length) return 0;   /* length*length: invalid */
            out->em = out->em * rhs.px + rhs.em * out->px;
            out->pct = out->pct * rhs.px + rhs.pct * out->px;
            out->px = out->px * rhs.px;
            out->is_length = out->is_length || rhs.is_length;
        } else {
            if (rhs.is_length || rhs.px == 0.0) return 0;    /* divisor must be a nonzero number */
            out->px = out->px / rhs.px;
            out->em = out->em / rhs.px;
            out->pct = out->pct / rhs.px;
        }
    }
    return 1;
}

static int calc_expr(calc_parser *p, calc_val *out, int depth) {
    if (!calc_term(p, out, depth)) return 0;
    for (;;) {
        calc_skip_ws(p);
        if (p->i >= p->n || (p->s[p->i] != '+' && p->s[p->i] != '-')) break;
        char op = p->s[p->i++];
        calc_val rhs;
        if (!calc_term(p, &rhs, depth)) return 0;
        if (out->is_length != rhs.is_length) return 0;       /* length +/- number: invalid */
        out->px = (op == '+') ? out->px + rhs.px : out->px - rhs.px;
        out->em = (op == '+') ? out->em + rhs.em : out->em - rhs.em;
        out->pct = (op == '+') ? out->pct + rhs.pct : out->pct - rhs.pct;
    }
    return 1;
}

/* Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching
 * ")" already stripped by the caller). Fails closed on any leftover/unparsed input,
 * mismatched parens, a dimensionless result, or a dimensional error. */
static int calc_eval_full(const char *v, size_t vlen, double *out_px, double *out_em,
                          double *out_pct) {
    calc_parser p = { v, vlen, 0 };
    calc_val r;
    if (!calc_expr(&p, &r, 0)) return 0;
    calc_skip_ws(&p);
    if (p.i != vlen || !r.is_length) return 0;
    *out_px = r.px;
    if (out_em != NULL) *out_em = r.em;
    if (out_pct != NULL) *out_pct = r.pct;
    return 1;
}

/* The pure-length entry point: a percentage in the expression makes the result a
 * <length-percentage>, which this caller's property does not accept, so it fails
 * closed here rather than silently dropping the percentage term. */
static int calc_eval(const char *v, size_t vlen, double *out_px) {
    double pct = 0.0;
    if (!calc_eval_full(v, vlen, out_px, NULL, &pct)) return 0;
    return pct == 0.0;
}

/* The font-size derivative of a calc() body, for value_em_milli. */
static int calc_eval_em(const char *v, size_t vlen, double *out_em) {
    double px;
    return calc_eval_full(v, vlen, &px, out_em, NULL);
}

/* True if s (already trimmed) is a "calc(...)" call spanning the whole string
 * (case-insensitive keyword, balanced trailing paren); on success the argument
 * span is written to *inner_start / *inner_len. */
static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len) {
    size_t n = strlen(s);
    if (n < 6) return 0;   /* "calc()" minimum */
    if (csel_lower_ch(s[0]) != 'c' || csel_lower_ch(s[1]) != 'a' || csel_lower_ch(s[2]) != 'l' ||
        csel_lower_ch(s[3]) != 'c' || s[4] != '(' || s[n - 1] != ')')
        return 0;
    *inner_start = 5;
    *inner_len = n - 6;
    return 1;
}

/* Parses one box-model length. Accepts "Npx", a bare "0", "Nem"/"Nrem" (x16 px,
 * the engine's base font), viewport units (vw/vh/vmin/vmax vs the normalized
 * 1920x1080 viewport; see viewport_unit_px), "calc(...)" over the same units
 * (+, -, *, /, parens; see calc_eval), and (when allow_auto) "auto". Rejects %
 * and bare non-zero numbers outside calc() (fail closed: they need a containing
 * block the parser does not have). Returns 1 with *out = CSS_LEN_AUTO or a
 * signed px clamped to [-CSS_LEN_MAX, CSS_LEN_MAX]; 0 if unsupported. */
int cb_interp_len(const char *v, int allow_auto, int *out) {
    if (allow_auto && csel_ci_eq(v, "auto")) { *out = CSS_LEN_AUTO; return 1; }

    size_t cs, cl;
    if (calc_unwrap(v, &cs, &cl)) {
        double px;
        if (!calc_eval(v + cs, cl, &px)) return 0;
        *out = css_round_clamp(px, -CSS_LEN_MAX, CSS_LEN_MAX);
        return 1;
    }
    /* A bare math-function value (min()/max()/clamp() without a calc() wrapper).
     * The m/c prefix check keeps plain lengths off the calc machinery; the whole
     * value must be exactly one function call whose result is a length. */
    if (csel_lower_ch(v[0]) == 'm' || csel_lower_ch(v[0]) == 'c') {
        size_t n = strlen(v);
        calc_parser p = { v, n, 0 };
        int kind = -1;
        if (calc_match_fn(&p, "min")) kind = 0;
        else if (calc_match_fn(&p, "max")) kind = 1;
        else if (calc_match_fn(&p, "clamp")) kind = 2;
        if (kind >= 0) {
            calc_val r;
            if (!calc_mathfn(&p, &r, 0, kind)) return 0;
            calc_skip_ws(&p);
            if (p.i != n || !r.is_length) return 0;
            *out = css_round_clamp(r.px, -CSS_LEN_MAX, CSS_LEN_MAX);
            return 1;
        }
    }

    /* Every unit CSS defines as a <length>, through the one canonical resolver.
     * This used to be a private four-unit table that silently dropped pt (and
     * pc/cm/mm/in/Q/ex/ch/lh), so a page written in points -- Hacker News, for
     * one -- lost every padding, margin and width it declared. */
    double px;
    if (!cb_length_px(v, &px)) return 0;
    *out = css_round_clamp(px, -CSS_LEN_MAX, CSS_LEN_MAX);
    return 1;
}

/* The css_pct_slot mirroring a px length slot, or -1 when the property does not
 * accept the <length-percentage> type. ONE table, so adding a percentage-capable
 * property is one row here and nothing else -- and so a property that must keep
 * rejecting `%` (letter-spacing, border-width, ...) does so by simply not
 * appearing. */
static int pct_slot_of(int slot) {
    switch (slot) {
        case P_MARGIN_TOP:    return CSS_PCT_MARGIN_TOP;
        case P_MARGIN_RIGHT:  return CSS_PCT_MARGIN_RIGHT;
        case P_MARGIN_BOTTOM: return CSS_PCT_MARGIN_BOTTOM;
        case P_MARGIN_LEFT:   return CSS_PCT_MARGIN_LEFT;
        case P_PAD_TOP:       return CSS_PCT_PAD_TOP;
        case P_PAD_RIGHT:     return CSS_PCT_PAD_RIGHT;
        case P_PAD_BOTTOM:    return CSS_PCT_PAD_BOTTOM;
        case P_PAD_LEFT:      return CSS_PCT_PAD_LEFT;
        case P_WIDTH:         return CSS_PCT_WIDTH;
        case P_MAXWIDTH:      return CSS_PCT_MAX_WIDTH;
        case P_MINWIDTH:      return CSS_PCT_MIN_WIDTH;
        case P_HEIGHT:        return CSS_PCT_HEIGHT;
        case P_MINHEIGHT:     return CSS_PCT_MIN_HEIGHT;
        case P_MAXHEIGHT:     return CSS_PCT_MAX_HEIGHT;
        case P_INSET_TOP:     return CSS_PCT_INSET_TOP;
        case P_INSET_RIGHT:   return CSS_PCT_INSET_RIGHT;
        case P_INSET_BOTTOM:  return CSS_PCT_INSET_BOTTOM;
        case P_INSET_LEFT:    return CSS_PCT_INSET_LEFT;
        case P_TEXTINDENT:    return CSS_PCT_TEXT_INDENT;
        case P_BORDER_RADIUS: return CSS_PCT_RADIUS_TL;
        case P_RADIUS_TR:     return CSS_PCT_RADIUS_TR;
        case P_RADIUS_BR:     return CSS_PCT_RADIUS_BR;
        case P_RADIUS_BL:     return CSS_PCT_RADIUS_BL;
        case P_TRANSFORM_TX:  return CSS_PCT_TRANSLATE_X;
        case P_TRANSFORM_TY:  return CSS_PCT_TRANSLATE_Y;
        case P_FLEX_BASIS:    return CSS_PCT_FLEX_BASIS;
        default:              return -1;
    }
}

/* Parses one <length-percentage> into its two components: *out_px (a px value,
 * CSS_LEN_AUTO, or 0 when the value is a pure percentage) and *out_pm (the
 * percentage in per-mille, 0 when there is none). Percentages are accepted only
 * when the caller asks (allow_pct), which is how properties whose grammar is a
 * bare <length> keep failing closed.
 *
 * calc() is resolved by the existing evaluator, which works in px and has no
 * containing block, so a calc() MIXING a percentage with a length still fails
 * closed rather than silently dropping the percentage half. */
/* The font-relative derivative of `v`, in thousandths of an em, saturating at
 * CSS_EM_MILLI_MAX. Zero for anything that does not move with the font-size --
 * which includes a plain px value, a percentage, `auto`, and any value this
 * module could not parse as a length at all.
 *
 * Deliberately re-resolves rather than being plumbed through interp_len's 17
 * call sites: the derivative is a property of the VALUE TEXT, so asking the one
 * canonical resolver for it keeps a single source of truth. calc() answers for
 * its own sum via calc_eval; a bare token answers through cl_resolve_lp. */
int cb_value_em_milli(const char *v) {
    double em = 0.0;

    size_t cs, cl;
    if (calc_unwrap(v, &cs, &cl)) {
        if (!calc_eval_em(v + cs, cl, &em)) return 0;
    } else {
        cl_ctx ctx = cl_ctx_initial();
        cl_lp lp;
        if (cl_resolve_lp(v, &ctx, &lp) != CL_OK) return 0;
        em = lp.em;
    }
    if (!isfinite(em) || em == 0.0) return 0;

    double milli = em * 1000.0;
    if (milli >  (double)CSS_EM_MILLI_MAX) milli =  (double)CSS_EM_MILLI_MAX;
    if (milli < -(double)CSS_EM_MILLI_MAX) milli = -(double)CSS_EM_MILLI_MAX;
    return (int)(milli < 0.0 ? milli - 0.5 : milli + 0.5);
}

int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                     int *out_px, int *out_pm) {
    *out_pm = 0;
    if (cb_interp_len(v, allow_auto, out_px)) return 1;
    if (!allow_pct) return 0;

    /* calc() that MIXES a percentage with a length. interp_len above already ran
     * the same expression and failed closed on the percentage term (its property
     * may not accept one); here the property does, so both halves are kept and
     * travel symbolically to bx_lp_px. `width: calc(100% - 2rem)` is the most
     * common responsive idiom on the web and used to be dropped whole. */
    size_t cs, cl;
    if (calc_unwrap(v, &cs, &cl)) {
        double px = 0.0, pct = 0.0;
        if (!calc_eval_full(v + cs, cl, &px, NULL, &pct)) return 0;
        double pm = pct * 10.0;
        if (pm >  (double)CSS_PCT_MAX) pm =  (double)CSS_PCT_MAX;
        if (pm < -(double)CSS_PCT_MAX) pm = -(double)CSS_PCT_MAX;
        *out_pm = (int)(pm < 0.0 ? pm - 0.5 : pm + 0.5);
        *out_px = css_round_clamp(px, -CSS_LEN_MAX, CSS_LEN_MAX);
        return 1;
    }

    cl_ctx ctx = cl_ctx_initial();
    cl_lp lp;
    if (cl_resolve_lp(v, &ctx, &lp) != CL_OK || !lp.has_pct) return 0;

    double pm = lp.pct * 10.0;
    if (pm >  (double)CSS_PCT_MAX) pm =  (double)CSS_PCT_MAX;
    if (pm < -(double)CSS_PCT_MAX) pm = -(double)CSS_PCT_MAX;
    *out_pm = (int)(pm < 0.0 ? pm - 0.5 : pm + 0.5);
    *out_px = css_round_clamp(lp.px, -CSS_LEN_MAX, CSS_LEN_MAX);
    return 1;
}

/* Whether a <length-percentage> whose two halves are (px_val, pct_pm) can be
 * non-negative once its basis is known.
 *
 * A property that forbids negative values (width, padding, ...) cannot decide that
 * by looking at one half: `calc(100% - 6px)` has a NEGATIVE px half and a positive
 * percentage half, and its used value is positive for any containing block wider
 * than 6px. Rejecting on the px half alone dropped the single most common
 * responsive idiom on the web. CSS Values 4 section 10.1 is explicit that a
 * calc() result out of range is CLAMPED at used-value time, not invalid at parse
 * time -- so the only thing rejected here is a value that can never be positive.
 * The clamp itself belongs to the consumer of the used value, not to the cascade. */
int cb_lp_can_be_nonneg(int px_val, int pct_pm) {
    if (px_val == CSS_LEN_AUTO || px_val == CSS_LEN_UNSET) return 1;
    if (px_val >= 0 && pct_pm >= 0) return 1;
    /* Mixed signs: the basis decides, so it is representable. */
    return (px_val < 0 && pct_pm > 0) || (pct_pm < 0 && px_val > 0);
}

/* Emits one box length declaration for slot into dst (cap permitting). A negative
 * value is rejected unless allow_neg (margins allow it; padding/width do not).
 *
 * When the property accepts <length-percentage> (pct_slot_of(slot) >= 0) this
 * writes BOTH halves, always -- including a 0 percentage for a plain length.
 * Emitting only the half that changed would leave a lower-specificity `width:50%`
 * combining with a winning `width:200px`, which is exactly the cascade bug the
 * old separate P_WIDTH_PCT slot had.
 *
 * Returns the number of decls written (0 = unsupported value or no room). */
/* How `auto` is treated for a given <length-percentage> slot.
 *
 * The distinction is not cosmetic. On a margin, `auto` is a real value with real
 * behaviour (it absorbs free space, which is how `margin:0 auto` centres). On
 * width/height/min/max it means "size to content" -- and content sizing IS this
 * engine's behaviour for an undeclared box dimension, so the correct
 * representation of `width:auto` is an unset dimension whose CASCADE SLOT is
 * claimed. Claiming matters: `.a{width:200px} .a.b{width:auto}` must come out
 * content-sized, and dropping the second declaration (which is what happened
 * before) left the 200px in place. 90 declarations in the measured corpus. */
#define AUTO_REJECT 0   /* `auto` is not in this property's value grammar */
#define AUTO_VALUE  1   /* `auto` is a distinct value -> CSS_LEN_AUTO */
#define AUTO_RESET  2   /* `auto` is this engine's unset behaviour -> claim, write nothing */
/* max-width/max-height take `none`, not `auto`, as their "no constraint" initial
 * value (CSS 2.1 section 10.4). Same reset semantics, different spelling -- kept a
 * distinct mode so `width:none`, which is not valid CSS, still fails closed. */
#define AUTO_RESET_NONE 3

int cb_emit_len(css_decl *dst, int cap, int slot, const char *val,
                    int allow_auto, int allow_neg) {
    int ps = pct_slot_of(slot);
    int need = (ps >= 0) ? 2 : 1;
    if (cap < need) return 0;

    /* A CSS-wide keyword -- and `auto` where auto IS the unset behaviour -- claims
     * the slot(s) and writes nothing. BOTH halves are claimed, for the same reason
     * every other emitter writes both: leaving the % half unclaimed would let a
     * lower-specificity `width:50%` survive underneath a `width:auto` that won. */
    if (cb_wide_keyword(val) ||
        (allow_auto == AUTO_RESET && csel_ci_eq(val, "auto")) ||
        (allow_auto == AUTO_RESET_NONE &&
         (csel_ci_eq(val, "none") || csel_ci_eq(val, "auto")))) {
        dst[0].prop = slot;
        dst[0].ival = CSS_LEN_UNSET;
        dst[0].emil = 0;
        dst[0].wide = 2;
        if (ps < 0) return 1;
        dst[1].prop = P_PCT_FIRST + ps;
        dst[1].ival = 0;
        dst[1].emil = 0;
        dst[1].wide = 2;
        return 2;
    }

    /* The intrinsic sizing keywords (CSS Sizing 3 section 5.1). They are values of
     * the <width> type, not lengths, so like `auto` they ride the out-of-band
     * sentinel channel; the two AUTO_RESET modes are exactly the sizing properties
     * (width, height, min-width, min-height, max-width, max-height) and so
     * exactly where the grammar allows them. `stretch` and its prefixed spellings fill the containing block, which
     * IS a block box's `auto` behaviour, so they claim without a sentinel. */
    if (allow_auto == AUTO_RESET || allow_auto == AUTO_RESET_NONE) {
        int kw = 0;
        if (csel_ci_eq(val, "min-content"))      kw = CSS_LEN_MIN_CONTENT;
        else if (csel_ci_eq(val, "max-content")) kw = CSS_LEN_MAX_CONTENT;
        else if (csel_ci_eq(val, "fit-content")) kw = CSS_LEN_FIT_CONTENT;
        else if (csel_ci_eq(val, "stretch") || csel_ci_eq(val, "available") ||
                 csel_ci_eq(val, "fill") || csel_ci_eq(val, "fill-available"))
            kw = CSS_LEN_UNSET;
        else if (csel_span_eq(val, "fit-content(", 12, 1)) {
            /* fit-content(L) is min(max-content, max(min-content, L)) (Sizing 3
             * section 5.1). Its upper bound is L, and a box that cannot measure its
             * own content uses that bound -- so the length inside is the used value
             * this engine can honour, and it is read with the same resolver as any
             * other length rather than a second parser. */
            size_t vn = strlen(val);
            if (vn > 13u && val[vn - 1] == ')') {
                char inner[CSS_TOK_MAX];
                if (cb_copy_trim(val, 12, vn - 1, inner, sizeof inner) != (size_t)-1 &&
                    inner[0] != '\0')
                    return cb_emit_len(dst, cap, slot, inner, AUTO_REJECT, allow_neg);
            }
            return 0;
        }
        if (kw != 0) {
            dst[0].prop = slot;
            dst[0].ival = kw;
            dst[0].emil = 0;
            dst[0].wide = 2;
            if (ps < 0) return 1;
            dst[1].prop = P_PCT_FIRST + ps;
            dst[1].ival = 0;
            dst[1].emil = 0;
            dst[1].wide = 2;
            return 2;
        }
    }

    int o, pm;
    if (!cb_interp_lp(val, allow_auto, ps >= 0, &o, &pm)) return 0;
    if (!allow_neg && !cb_lp_can_be_nonneg(o, pm)) return 0;

    dst[0].prop = slot;
    dst[0].ival = o;
    /* The font-relative half of the value, alongside the px and % halves. A
     * length emitter is the ONLY thing that writes it, which is what guarantees
     * a non-length slot can never carry one. */
    dst[0].emil = (o == CSS_LEN_AUTO) ? 0 : cb_value_em_milli(val);
    if (ps < 0) return 1;
    /* A pure percentage leaves the px half UNSET, not 0: `width: 50%` states
     * nothing about an absolute width, and zeroing it would read as `width: 0`
     * everywhere the percentage cannot be resolved. */
    if (pm != 0 && o == 0) dst[0].ival = CSS_LEN_UNSET;
    dst[1].prop = P_PCT_FIRST + ps;
    dst[1].ival = pm;
    return 2;
}

/* Extracts the next whitespace-separated token starting at *p into tok (bounded to
 * cap, NUL-terminated), advancing *p past it and any leading whitespace. A token
 * may itself contain balanced parens -- so "calc(1px + 2px)" (which has spaces
 * INSIDE it) is ONE token, not split apart at the space after "1px" -- tracked via
 * a paren-depth counter, so every multi-value shorthand below can carry a calc()
 * value exactly like a single-value property can. Every shorthand tokenizer in
 * this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-basis, border/outline width, text-shadow/box-shadow offsets) uses
 * this helper, so calc() works uniformly instead of only in single-value
 * properties. Returns 0 (tok untouched) when there is nothing left to read. */
int cb_next_ws_token(const char **p, char *tok, size_t cap) {
    while (**p == ' ' || **p == '\t') ++*p;
    if (**p == '\0') return 0;
    size_t k = 0;
    int depth = 0;
    while (**p != '\0') {
        if (**p == '(') ++depth;
        else if (**p == ')') { if (depth > 0) --depth; }
        else if (depth == 0 && (**p == ' ' || **p == '\t')) break;
        if (k + 1 < cap) tok[k++] = **p;
        ++*p;
    }
    tok[k] = '\0';
    return 1;
}

/* Expands a margin/padding shorthand (1..4 whitespace-separated lengths, CSS order
 * all / "v h" / "t h b" / "t r b l") into the four contiguous slots starting at
 * slot_top (top,right,bottom,left). Any unsupported token drops the WHOLE shorthand
 * (fail closed, never a partial box). Returns the number of decls written (<= cap). */
int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
                       css_decl *dst, int cap) {
    int px[4], pm[4], em[4], nv = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int accepts_pct = pct_slot_of(slot_top) >= 0;
    while (nv < 4 && cb_next_ws_token(&p, tok, sizeof tok)) {
        int o, q;
        if (!cb_interp_lp(tok, allow_auto, accepts_pct, &o, &q)) return 0;
        if (!allow_neg && !cb_lp_can_be_nonneg(o, q)) return 0;
        px[nv] = o; pm[nv] = q;
        em[nv] = (o == CSS_LEN_AUTO) ? 0 : cb_value_em_milli(tok);
        ++nv;
    }
    if (nv == 0) return 0;
    {
        char extra[CSS_TOK_MAX];
        if (cb_next_ws_token(&p, extra, sizeof extra)) return 0;
    }
    /* CSS shorthand order: all / "v h" / "t h b" / "t r b l". */
    static const int PICK[4][4] = {
        { 0, 0, 0, 0 }, { 0, 1, 0, 1 }, { 0, 1, 2, 1 }, { 0, 1, 2, 3 }
    };
    const int *pick = PICK[nv - 1];
    int n = 0;
    for (int s = 0; s < 4; ++s) {
        int src = pick[s];
        int slot = slot_top + s;
        int ps = pct_slot_of(slot);
        if (n + ((ps >= 0) ? 2 : 1) > cap) break;
        dst[n].prop = slot;
        /* Same rule as emit_len: a pure percentage leaves the px half unset. */
        dst[n].ival = (pm[src] != 0 && px[src] == 0) ? CSS_LEN_UNSET : px[src];
        dst[n].emil = em[src];
        ++n;
        if (ps >= 0) {
            dst[n].prop = P_PCT_FIRST + ps;
            dst[n].ival = pm[src];
            ++n;
        }
    }
    return n;
}

/* Expands a two-slot logical shorthand (margin-inline / padding-block /
 * inset-inline: one value sets both sides, two set start then end; 2026-07-10).
 * Fail closed on zero, more than two, or any uninterpretable token. */
int cb_expand_box2(const char *val, int slot_start, int slot_end,
                       int allow_auto, int allow_neg, css_decl *dst, int cap) {
    char toks[2][CSS_TOK_MAX];
    int nv = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (nv < 2 && cb_next_ws_token(&p, tok, sizeof tok)) {
        memcpy(toks[nv], tok, sizeof tok);
        ++nv;
    }
    if (nv == 0 || cb_next_ws_token(&p, tok, sizeof tok)) return 0;

    /* Both sides go through emit_len, so the <length-percentage> handling (and
     * the both-halves cascade rule) lives in exactly one place. */
    int slots[2] = { slot_start, slot_end };
    const char *src[2] = { toks[0], (nv == 2) ? toks[1] : toks[0] };
    int n = 0;
    for (int s = 0; s < 2; ++s) {
        int w = cb_emit_len(dst + n, cap - n, slots[s], src[s], allow_auto, allow_neg);
        if (w == 0) return 0;   /* fail closed: never a partial logical pair */
        n += w;
    }
    return n;
}

