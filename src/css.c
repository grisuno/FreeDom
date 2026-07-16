/*
 * css — pure author-CSS parser + simple cascade. See include/css.h, spec/css.md.
 *
 * Hostile content: never fetches (url()/@-rules dropped), bounded (anti-DoS),
 * fails closed. No global state; the only allocation is the sheet.
 */

#include "css.h"
#include "css_color.h"
#include "css_select.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* Bounds (anti-DoS). A stylesheet beyond these is truncated, never unbounded.
 * CSS_TOK_MAX / CSS_MAX_CLASSES_PER_SEL live in css_select.h (shared with the
 * selector engine).
 *
 * These were 512/2048/384 until a real-world audit (a single vendored, minified
 * Bootstrap 4.5.2 stylesheet -- ~2100 rules, ~3600 individual selectors once
 * comma groups are split, ~2100 declarations) showed CSS_MAX_RULES silently
 * dropping essentially every utility class (.bg-dark, .text-success, ...): they
 * sit near the end of a real compiled stylesheet, past rule #384, so the visible
 * symptom was "the whole page ignores your background/text-color classes" with
 * no error anywhere (truncation here is deliberately silent -- see parse_block's
 * "leave decls; harmless, unreferenced" comment). Raised 16x to comfortably fit
 * one real component-library stylesheet plus a handful of smaller ones (this is
 * still a hard, finite cap -- a hostile/pathological sheet is still bounded, just
 * at a size that matches real pages instead of a toy one). Paired with the
 * per-element style cache in page_view.c's pv_style_cache: with the cascade now
 * O(nsels) per unique element instead of per (element, ancestor-visit) pair,
 * a bigger nsels does not multiply page_view's runtime by every text node. */
#define CSS_MAX_SELS            8192u
#define CSS_MAX_DECLS           32768u
#define CSS_MAX_RULES           6144u
#define CSS_SELS_PER_GROUP      32
#define CSS_INLINE_DECLS        64u
#define CSS_INLINE_SPEC         (1 << 20)

/* Custom properties (--name: value) + var(--name[, fallback]) (see the "Custom
 * properties" section of spec/css.md). Deliberately simplified vs. real CSS custom
 * property scoping: every `--name` declaration found ANYWHERE in the stylesheet
 * (any rule, any @media) feeds one flat, page-global table (last declaration for a
 * name wins), which covers the overwhelmingly common `:root { --x: ... }` pattern.
 * A value is capped at CSS_TOK_MAX like every other token here (an overlong one
 * could never fit a re-substituted declaration value anyway), and lookups recurse
 * at most CSS_VAR_MAX_DEPTH deep (a chain or cycle beyond that fails the var(),
 * bounding the work to O(depth * CSS_TOK_MAX) -- anti-DoS, never a crash or hang). */
#define CSS_MAX_CUSTOM_PROPS 64u
#define CSS_VAR_MAX_DEPTH    4

/* Property slots. The enum value IS the css_style slot index used by apply().
 * The four margin slots are contiguous in CSS shorthand order (top,right,bottom,
 * left); the four padding slots likewise — expand_box4 relies on that. */
enum { P_COLOR = 0, P_BG, P_ALIGN, P_FONTSIZE, P_LINEHEIGHT, P_WEIGHT, P_STYLE,
       P_TEXTDECO, P_TEXTDECO_COLOR, P_TEXTDECO_STYLE,
       P_DISPLAY, P_GAP, P_JUSTIFY, P_GRIDCOLS,
       P_MARGIN_TOP, P_MARGIN_RIGHT, P_MARGIN_BOTTOM, P_MARGIN_LEFT,
       P_PAD_TOP, P_PAD_RIGHT, P_PAD_BOTTOM, P_PAD_LEFT,
       P_WIDTH, P_MAXWIDTH, P_MINWIDTH, P_HEIGHT, P_MINHEIGHT, P_MAXHEIGHT,
       P_WIDTH_PCT, P_MAXWIDTH_PCT,
       /* Text-presentation extensions (Hito 23b-6). The three text-shadow slots are
        * contiguous (dx,dy,color) so expand_shadow writes them as a group. */
       P_FONTFAMILY, P_TEXTTRANSFORM, P_LETTERSPACING, P_WORDSPACING,
       P_SHADOW_DX, P_SHADOW_DY, P_SHADOW_COLOR,
       P_OPACITY, P_VALIGN, P_TEXTINDENT, P_WHITESPACE, P_TABSIZE, P_LISTSTYLE, P_DIRECTION,
       /* Layout / box decoration (Hito 23b-7). Contiguous groups feed the box4-style
        * expanders: insets (T R B L); border widths/styles/colors (each T R B L);
        * box-shadow (dx dy blur spread color inset); flex (grow shrink basis). */
       P_POSITION,
       P_INSET_TOP, P_INSET_RIGHT, P_INSET_BOTTOM, P_INSET_LEFT,
       P_ZINDEX, P_BOXSIZING,
       P_BW_TOP, P_BW_RIGHT, P_BW_BOTTOM, P_BW_LEFT,
       P_BS_TOP, P_BS_RIGHT, P_BS_BOTTOM, P_BS_LEFT,
       P_BC_TOP, P_BC_RIGHT, P_BC_BOTTOM, P_BC_LEFT,
       P_BORDER_RADIUS,
       P_BSHADOW_DX, P_BSHADOW_DY, P_BSHADOW_BLUR, P_BSHADOW_SPREAD,
       P_BSHADOW_COLOR, P_BSHADOW_INSET,
       P_OUTLINE_W, P_OUTLINE_S, P_OUTLINE_C, P_OUTLINE_OFFSET,
       P_FLEX_GROW, P_FLEX_SHRINK, P_FLEX_BASIS,
       P_ORDER, P_ALIGN_ITEMS, P_ALIGN_SELF, P_ALIGN_CONTENT, P_JUSTIFY_ITEMS,
       P_FLEX_DIR, P_FLEX_WRAP,
       P_GRID_ROWS, P_ROW_GAP, P_GRID_FLOW, P_GRID_COL_SPAN, P_GRID_ROW_SPAN,
       P_FLOAT, P_CLEAR,
        P_VISIBILITY, P_OVERFLOW_X, P_OVERFLOW_Y, P_CURSOR,
        P_TEXT_OVERFLOW, P_WORD_BREAK,
        P_BORDER_COLLAPSE, P_BORDER_SPACING, P_EMPTY_CELLS,
        P_CAPTION_SIDE, P_TABLE_LAYOUT,
        P_FONT_VARIANT, P_HYPHENS, P_USER_SELECT, P_CARET_COLOR,
        P_APPEARANCE, P_POINTER_EVENTS,
        P_BG_REPEAT, P_BG_SIZE, P_BG_CLIP, P_BG_ORIGIN, P_BG_ATTACHMENT,
        P_ISOLATION, P_CONTAIN, P_CONTENT_VISIBILITY, P_IMAGE_RENDERING,
        P_COLOR_SCHEME, P_ACCENT_COLOR, P_PRINT_COLOR_ADJUST, P_FORCED_COLOR_ADJUST,
        P_MIX_BLEND_MODE, P_OBJECT_FIT, P_LIST_STYLE_POS,
        P_FONT_KERNING, P_TEXT_RENDERING, P_FONT_STRETCH,
        P_RESIZE, P_SCROLL_BEHAVIOR, P_TOUCH_ACTION, P_OVERSCROLL_BEHAVIOR,
        P_BACKFACE_VISIBILITY,
        P_TEXTDECO_THICKNESS, P_ASPECT_NUM, P_ASPECT_DEN,
        /* linear-gradient background (2026-07-11). Contiguous group: one declaration
         * emits angle + stop count + the stop colors in lock-step. */
        P_BG_GRAD_ANGLE, P_BG_GRAD_N,
        P_BG_GRAD_C0, P_BG_GRAD_C1, P_BG_GRAD_C2, P_BG_GRAD_C3,
        /* grid-template-columns track sizes (2026-07-11). Contiguous group of
         * CSS_GRID_TRACKS_MAX slots emitted in lock-step with P_GRIDCOLS. */
        P_GRID_TRACK0, P_GRID_TRACK1, P_GRID_TRACK2, P_GRID_TRACK3,
        P_GRID_TRACK4, P_GRID_TRACK5, P_GRID_TRACK6, P_GRID_TRACK7,
        /* transform (M1.2): translate()/translateX()/translateY() px offsets. */
        P_TRANSFORM_TX, P_TRANSFORM_TY,
        P_NSLOTS };

typedef struct css_decl {
    int prop;       /* P_* */
    int ival;       /* interpreted value (color packed / enum / scale / bool) */
    int important;  /* 1 if the declaration carried !important (higher cascade tier) */
} css_decl;

/* One custom property (--name: value), for var() lookups. Both fields are bounded
 * like every other token buffer here. */
typedef struct css_custom_prop {
    char name[CSS_TOK_MAX];
    char value[CSS_TOK_MAX];
} css_custom_prop;

/* The selector types (css_attr_match/css_compound/css_sel) and their parser/matcher
 * live in css_select.{h,c}. */

struct css_sheet {
    css_decl decls[CSS_MAX_DECLS];
    size_t   ndecls;
    struct { size_t start, count; } rules[CSS_MAX_RULES];
    size_t   nrules;
    css_sel  sels[CSS_MAX_SELS];
    size_t   nsels;
    css_custom_prop custom[CSS_MAX_CUSTOM_PROPS];  /* --name table, page-global */
    size_t          ncustom;
};

/* The small ASCII helpers (csel_lower_ch / csel_ci_eq / csel_substr /
 * csel_ident_ch) are shared with the selector engine via css_select.h. */

/* Parses a leading non-negative number (digits + optional fraction). Returns 1 on
 * success, setting *out and *endp to the first unconsumed char. */
static int parse_num(const char *s, double *out, const char **endp) {
    const char *p = s;
    double v = 0.0;
    int any = 0;
    while (*p >= '0' && *p <= '9') { v = v * 10.0 + (*p - '0'); any = 1; ++p; }
    if (*p == '.') {
        ++p;
        double f = 0.1;
        while (*p >= '0' && *p <= '9') { v += (*p - '0') * f; f *= 0.1; ++p; }
    }
    if (!any) return 0;
    *out = v;
    *endp = p;
    return 1;
}

/* Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the
 * cast avoids undefined behaviour: casting an out-of-range double (e.g. a hostile
 * "99999999999px") to int is UB. Every value interpreter that casts a parsed double
 * routes through here. */
static int round_clamp(double v, int lo, int hi) {
    if (v >= (double)hi) return hi;
    if (v <= (double)lo) return lo;
    return (int)(v + (v < 0.0 ? -0.5 : 0.5));
}

/* --- value interpreters (return -1 / sentinel when the value is unsupported) --- */

/* Like cc_parse but returns packed int with sentinels for currentColor/transparent. */
static int parse_color(const char *v) {
    cc_rgb c;
    cc_status st = cc_parse(v, &c);
    if (st == CC_OK) return cc_pack(c);
    if (st == CC_CURRENT_COLOR) return CC_COLOR_CURRENT;
    if (st == CC_TRANSPARENT) return CC_COLOR_TRANSPARENT;
    return -1;
}

static int interp_color(const char *v) {
    return parse_color(v);
}

static int interp_bg(const char *v) {
    int result = parse_color(v);
    if (result != -1) return result;
    /* token-iterate: skip url() tokens (never phone home), parse each other
     * token as a color */
    char tok[CSS_TOK_MAX];
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        if (*p == 'u' || *p == 'U') {
            /* skip url(...) token */
            if ((p[0] == 'u' || p[0] == 'U') && (p[1] == 'r' || p[1] == 'R') &&
                (p[2] == 'l' || p[2] == 'L') && p[3] == '(') {
                while (*p != '\0' && *p != ')') ++p;
                if (*p == ')') ++p;
                continue;
            }
        }
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        int tok_col = parse_color(tok);
        if (tok_col != -1) return tok_col;
    }
    return -1;
}

/* --- linear-gradient backgrounds (2026-07-11, spec/css.md) ---
 * The accepted grammar has no URL form, so a gradient can never fetch. Everything
 * else about it fails closed: an unparseable direction or color, unbalanced parens
 * or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole declaration). */

/* `to <side-or-corner>` (two keywords in either order) or `<int>deg` -> CSS degrees
 * normalized [0,359]. Returns -1 when seg is not direction syntax at all (it may be
 * the first color stop), -2 when it IS direction syntax but invalid (poisons the
 * gradient). */
static int grad_direction(const char *seg) {
    const char *p = seg;
    if (*p == '-' || *p == '+' || (*p >= '0' && *p <= '9')) {
        char *end = NULL;
        long a = strtol(seg, &end, 10);
        if (end != seg && csel_ci_eq(end, "deg"))
            return (int)(((a % 360) + 360) % 360);
        return -2;   /* rad/grad/turn/junk angles: unsupported */
    }
    if (!(csel_lower_ch(p[0]) == 't' && csel_lower_ch(p[1]) == 'o' &&
          (p[2] == ' ' || p[2] == '\t')))
        return -1;
    p += 3;
    int vert = -1, horiz = -1;
    for (int w = 0; w < 2; ++w) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char word[16];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof word)
            word[k++] = csel_lower_ch(*p++);
        word[k] = '\0';
        if      (strcmp(word, "top") == 0    && vert  < 0) vert = 0;
        else if (strcmp(word, "bottom") == 0 && vert  < 0) vert = 1;
        else if (strcmp(word, "right") == 0  && horiz < 0) horiz = 0;
        else if (strcmp(word, "left") == 0   && horiz < 0) horiz = 1;
        else return -2;
    }
    while (*p == ' ' || *p == '\t') ++p;
    if (*p != '\0') return -2;
    if (vert < 0 && horiz < 0) return -2;
    if (horiz < 0) return vert == 0 ? 0 : 180;
    if (vert < 0)  return horiz == 0 ? 90 : 270;
    if (vert == 0) return horiz == 0 ? 45 : 315;
    return horiz == 0 ? 135 : 225;
}

/* Locates a plain linear-gradient(...) call in v (case-insensitive; an occurrence
 * that is the tail of a longer ident, e.g. repeating-linear-gradient, does not
 * count). Writes the call span [start,end) (end past the closing paren) and the
 * argument span. 1 = found, 0 = absent, -1 = found but unbalanced (malformed). */
static int find_linear_gradient(const char *v, size_t *start, size_t *end,
                                size_t *args, size_t *argn) {
    static const char fn[] = "linear-gradient(";
    const size_t fnlen = sizeof fn - 1;
    size_t n = strlen(v);
    for (size_t i = 0; i + fnlen <= n; ++i) {
        size_t k = 0;
        while (k < fnlen && csel_lower_ch(v[i + k]) == fn[k]) ++k;
        if (k != fnlen) continue;
        if (i > 0) {
            char pc = v[i - 1];
            if (pc == '-' || (pc >= 'a' && pc <= 'z') || (pc >= 'A' && pc <= 'Z') ||
                (pc >= '0' && pc <= '9'))
                continue;
        }
        size_t j = i + fnlen;
        int depth = 1;
        while (j < n && depth > 0) {
            if (v[j] == '(') ++depth;
            else if (v[j] == ')') --depth;
            ++j;
        }
        if (depth != 0) return -1;
        *start = i; *end = j;
        *args = i + fnlen; *argn = (j - 1) - (i + fnlen);
        return 1;
    }
    return 0;
}

/* Parses the argument list of linear-gradient (s[0,n) is the text inside the
 * parens): optional direction, then color stops split on top-level commas. Stop
 * positions after a color are accepted and ignored (evenly spaced in v1). Fills
 * *angle and colors[CSS_GRAD_STOPS_MAX]; returns the stop count clamped to
 * CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when the
 * gradient fails closed. */
static int parse_linear_gradient_args(const char *s, size_t n, int *angle, int *colors) {
    *angle = 180;
    int nstops = 0, first = 1;
    size_t i = 0;
    while (i < n) {
        size_t j = i;
        int depth = 0;
        while (j < n && (depth > 0 || s[j] != ',')) {
            if (s[j] == '(') ++depth;
            else if (s[j] == ')' && depth > 0) --depth;
            ++j;
        }
        size_t a = i, b = j;
        while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
        while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
        if (a == b) return 0;   /* empty segment */
        char seg[CSS_TOK_MAX];
        size_t len = b - a;
        if (len >= sizeof seg) return 0;
        memcpy(seg, s + a, len);
        seg[len] = '\0';

        if (first) {
            first = 0;
            int d = grad_direction(seg);
            if (d >= 0) { *angle = d; i = j + 1; continue; }
            if (d == -2) return 0;
        }
        if (nstops < CSS_GRAD_STOPS_MAX) {
            size_t ce = 0;
            const char *lp = strchr(seg, '(');
            if (lp != NULL) {
                const char *rp = strchr(lp, ')');
                if (rp == NULL) return 0;
                ce = (size_t)(rp - seg) + 1;
            } else {
                while (seg[ce] != '\0' && seg[ce] != ' ' && seg[ce] != '\t') ++ce;
            }
            char color[CSS_TOK_MAX];
            memcpy(color, seg, ce);
            color[ce] = '\0';
            int cv = parse_color(color);
            if (cv == -1) return 0;
            colors[nstops] = cv;
        }
        ++nstops;
        i = j + 1;
    }
    if (nstops < 2) return 0;
    return nstops > CSS_GRAD_STOPS_MAX ? CSS_GRAD_STOPS_MAX : nstops;
}

/* Emits the gradient decl group. nstops == 0 emits only the explicit reset
 * (P_BG_GRAD_N = 0), which is how a shorthand clears a lower-tier gradient. */
static int emit_gradient(css_decl *dst, int cap, int angle, int nstops, const int *colors) {
    if (nstops <= 0) {
        if (cap < 1) return 0;
        dst[0].prop = P_BG_GRAD_N;
        dst[0].ival = 0;
        return 1;
    }
    if (cap < 2 + nstops) return 0;
    dst[0].prop = P_BG_GRAD_ANGLE; dst[0].ival = angle;
    dst[1].prop = P_BG_GRAD_N;     dst[1].ival = nstops;
    for (int k = 0; k < nstops; ++k) {
        dst[2 + k].prop = P_BG_GRAD_C0 + k;
        dst[2 + k].ival = colors[k];
    }
    return 2 + nstops;
}

/* background-image: linear-gradient resolves to the gradient group; url()/none/
 * radial/conic/repeating-gradients/malformed all emit the explicit gradient reset
 * (never fetch, fail closed). */
static int expand_bg_image(const char *val, css_decl *dst, int cap) {
    size_t gs, ge, as, an;
    int colors[CSS_GRAD_STOPS_MAX] = { -1, -1, -1, -1 };
    int angle = 180, nst = 0;
    if (find_linear_gradient(val, &gs, &ge, &as, &an) == 1)
        nst = parse_linear_gradient_args(val + as, an, &angle, colors);
    return emit_gradient(dst, cap, angle, nst, colors);
}

/* background shorthand: CSS resets BOTH the color and the image layer, so a color
 * emits gradient-unset and a gradient emits color-unset. A present-but-broken
 * gradient drops the whole declaration (fail closed); a value with neither a color
 * nor a gradient keeps the historical drop path (url()-only stays unset). */
static int expand_background(const char *val, css_decl *dst, int cap) {
    size_t gs = 0, ge = 0, as = 0, an = 0;
    int colors[CSS_GRAD_STOPS_MAX] = { -1, -1, -1, -1 };
    int angle = 180, nst = 0;
    int f = find_linear_gradient(val, &gs, &ge, &as, &an);
    if (f < 0) return 0;
    if (f == 1) {
        nst = parse_linear_gradient_args(val + as, an, &angle, colors);
        if (nst == 0) return 0;
    }
    char rest[CSS_TOK_MAX];
    size_t n = strlen(val), r = 0;
    for (size_t i = 0; i < n && r + 1 < sizeof rest; ++i) {
        if (f == 1 && i >= gs && i < ge) continue;
        rest[r++] = val[i];
    }
    rest[r] = '\0';
    int color = interp_bg(rest);
    if (f != 1 && color < 0) return 0;
    if (cap < 1) return 0;
    dst[0].prop = P_BG;
    dst[0].ival = color;
    return 1 + emit_gradient(dst + 1, cap - 1, angle, nst, colors);
}

static int interp_align(const char *v) {
    if (csel_ci_eq(v, "left") || csel_ci_eq(v, "start")) return CSS_ALIGN_LEFT;
    if (csel_ci_eq(v, "center")) return CSS_ALIGN_CENTER;
    if (csel_ci_eq(v, "right") || csel_ci_eq(v, "end")) return CSS_ALIGN_RIGHT;
    if (csel_ci_eq(v, "justify")) return CSS_ALIGN_JUSTIFY;
    return -1;
}

static int interp_fontsize(const char *v) {
    if (csel_ci_eq(v, "medium")) return 100;
    if (csel_ci_eq(v, "small") || csel_ci_eq(v, "smaller")) return 85;
    if (csel_ci_eq(v, "large") || csel_ci_eq(v, "larger")) return 120;
    if (csel_ci_eq(v, "x-large")) return 150;
    if (csel_ci_eq(v, "xx-large")) return 200;
    if (csel_ci_eq(v, "x-small")) return 75;
    if (csel_ci_eq(v, "xx-small")) return 60;

    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    double scale;
    if (csel_ci_eq(end, "px")) scale = num / 16.0 * 100.0;
    else if (csel_ci_eq(end, "em") || csel_ci_eq(end, "rem")) scale = num * 100.0;
    else if (end[0] == '%' && end[1] == '\0') scale = num;
    else if (csel_ci_eq(end, "pt")) scale = num * 1.333 / 16.0 * 100.0;
    else return -1;
    return round_clamp(scale, 10, 1000);
}

/* line-height as a percent of the natural line box. A unitless multiplier ("1.5" ->
 * 150) or a percent ("160%" -> 160); "normal" is unset (the UA default). Absolute px/em
 * line-heights need a font size we don't have here, so they are dropped (return -1).
 * Clamped to [CSS_LINE_MIN, CSS_LINE_MAX] (anti-DoS). */
static int interp_lineheight(const char *v) {
    if (csel_ci_eq(v, "normal")) return 0;
    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    double pct;
    if (end[0] == '\0')                       pct = num * 100.0; /* unitless */
    else if (end[0] == '%' && end[1] == '\0') pct = num;
    else if (csel_ci_eq(end, "px"))           pct = num / 16.0 * 100.0; /* rel to base */
    else if (csel_ci_eq(end, "em") || csel_ci_eq(end, "rem")) pct = num * 100.0;
    else return -1;  /* other: out of scope, dropped */
    return round_clamp(pct, CSS_LINE_MIN, CSS_LINE_MAX);
}

static int interp_weight(const char *v) {
    if (csel_ci_eq(v, "bold") || csel_ci_eq(v, "bolder")) return 1;
    if (csel_ci_eq(v, "normal") || csel_ci_eq(v, "lighter")) return 0;
    double num;
    const char *end;
    if (parse_num(v, &num, &end) && *end == '\0') return num >= 600.0 ? 1 : 0;
    return -1;
}

static int interp_style(const char *v) {
    if (csel_ci_eq(v, "italic") || csel_ci_eq(v, "oblique")) return 1;
    if (csel_ci_eq(v, "normal")) return 0;
    return -1;
}

/* text-decoration / text-decoration-line: OR of the line keywords underline /
 * overline / line-through found in the (space-separated) value. "none" -> 0
 * (explicit removal). Style/color/thickness tokens (wavy, red, 2px, solid, ...) are
 * ignored. A value carrying no line keyword at all is unsupported -> -1 (dropped). */
static int interp_textdeco(const char *v) {
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

static int interp_display(const char *v) {
    if (csel_ci_eq(v, "none")) return CSS_DISP_NONE;
    if (csel_ci_eq(v, "block")) return CSS_DISP_BLOCK;
    if (csel_ci_eq(v, "inline")) return CSS_DISP_INLINE;
    if (csel_ci_eq(v, "inline-block")) return CSS_DISP_INLINE_BLOCK;
    if (csel_ci_eq(v, "list-item")) return CSS_DISP_LIST_ITEM;
    if (csel_ci_eq(v, "flex") || csel_ci_eq(v, "inline-flex")) return CSS_DISP_FLEX;
    if (csel_ci_eq(v, "grid") || csel_ci_eq(v, "inline-grid")) return CSS_DISP_GRID;
    return -1;  /* unknown display: leave unset */
}

/* gap / grid-gap / column-gap: leading length as px (a two-value gap keeps the
 * first), "normal" -> 0; clamped to [0, CSS_GAP_MAX]. -1 when not a length. */
static int interp_len(const char *v, int allow_auto, int *out);

/* One gap length. Reuses interp_len (px / em / rem / bare 0 / calc() / math
 * functions), so a `gap: 1em` is 16px instead of the old misparse-as-1px, and a
 * trailing junk token fails closed. Negative fails; clamped to CSS_GAP_MAX. */
static int interp_gap(const char *v) {
    if (csel_ci_eq(v, "normal")) return 0;
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return -1;
    return (px > CSS_GAP_MAX) ? CSS_GAP_MAX : px;
}

static int interp_justify(const char *v) {
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
static int starts_with_ci(const char *s, const char *pre);

static int count_tracks(const char *s, size_t n) {
    int pos = 0;
    return walk_tracks(s, n, NULL, 0, &pos);
}

/* Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0);
 * minmax(a,b) -> the size of its max component b; auto/%/unknown -> 0 (an equal
 * `auto` share downstream, never a wrong guess). */
static int track_size_of(const char *tok) {
    size_t len = strlen(tok);
    if (len > 7 && starts_with_ci(tok, "minmax(") && tok[len - 1] == ')') {
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
    if (parse_num(tok, &num, &end) && csel_ci_eq(end, "fr") && num > 0.0)
        return -round_clamp(num * 100.0, 1, CSS_FLEX_FACTOR_MAX);
    int px;
    if (interp_len(tok, 0, &px) && px > 0) return px;
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
    if (!parse_num(cbuf, &num, &end) || *end != '\0' || num < 1.0) return -1;
    int reps = round_clamp(num, 1, (int)CSS_GRID_COLS_MAX);
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
static int interp_gridcols(const char *v) {
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
static int expand_grid_template_cols(const char *val, css_decl *dst, int cap) {
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
 * plain numbers or px/em/rem lengths -- the same units interp_len itself accepts
 * (no %/vw/vh: this engine has no containing-block/viewport width to resolve them
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

typedef struct calc_val { double px; int is_length; } calc_val;
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
    if (kind == 2) {
        if (nargs != 3) return 0;
        double m = (args[1].px < args[2].px) ? args[1].px : args[2].px;
        out->px = (args[0].px > m) ? args[0].px : m;
        out->is_length = args[0].is_length;
        return 1;
    }
    double best = args[0].px;
    for (int k = 1; k < nargs; ++k) {
        if (kind == 0) { if (args[k].px < best) best = args[k].px; }
        else           { if (args[k].px > best) best = args[k].px; }
    }
    out->px = best;
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
    if (!parse_num(p->s + p->i, &num, &end)) return 0;
    p->i += (size_t)(end - (p->s + p->i));
    if (neg) num = -num;
    if (p->i + 2 <= p->n && csel_lower_ch(p->s[p->i]) == 'p' && csel_lower_ch(p->s[p->i + 1]) == 'x') {
        out->px = num; out->is_length = 1; p->i += 2; return 1;
    }
    if (p->i + 3 <= p->n && csel_lower_ch(p->s[p->i]) == 'r' &&
        csel_lower_ch(p->s[p->i + 1]) == 'e' && csel_lower_ch(p->s[p->i + 2]) == 'm') {
        out->px = num * 16.0; out->is_length = 1; p->i += 3; return 1;
    }
    if (p->i + 2 <= p->n && csel_lower_ch(p->s[p->i]) == 'e' && csel_lower_ch(p->s[p->i + 1]) == 'm') {
        out->px = num * 16.0; out->is_length = 1; p->i += 2; return 1;
    }
    out->px = num;                      /* a bare number: length only if exactly 0 */
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
            out->px = out->px * rhs.px;
            out->is_length = out->is_length || rhs.is_length;
        } else {
            if (rhs.is_length || rhs.px == 0.0) return 0;    /* divisor must be a nonzero number */
            out->px = out->px / rhs.px;
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
    }
    return 1;
}

/* Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching
 * ")" already stripped by the caller). Fails closed on any leftover/unparsed input,
 * mismatched parens, a dimensionless result, or a dimensional error. */
static int calc_eval(const char *v, size_t vlen, double *out_px) {
    calc_parser p = { v, vlen, 0 };
    calc_val r;
    if (!calc_expr(&p, &r, 0)) return 0;
    calc_skip_ws(&p);
    if (p.i != vlen || !r.is_length) return 0;
    *out_px = r.px;
    return 1;
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
 * the engine's base font), "calc(...)" over the same units (+, -, *, /, parens;
 * see calc_eval), and (when allow_auto) "auto". Rejects %/viewport units and bare
 * non-zero numbers outside calc() (fail closed: they need a containing block the
 * parser does not have). Returns 1 with *out = CSS_LEN_AUTO or a signed px clamped
 * to [-CSS_LEN_MAX, CSS_LEN_MAX]; 0 if unsupported. */
static int interp_len(const char *v, int allow_auto, int *out) {
    if (allow_auto && csel_ci_eq(v, "auto")) { *out = CSS_LEN_AUTO; return 1; }

    size_t cs, cl;
    if (calc_unwrap(v, &cs, &cl)) {
        double px;
        if (!calc_eval(v + cs, cl, &px)) return 0;
        *out = round_clamp(px, -CSS_LEN_MAX, CSS_LEN_MAX);
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
            *out = round_clamp(r.px, -CSS_LEN_MAX, CSS_LEN_MAX);
            return 1;
        }
    }

    const char *p = v;
    int neg = 0;
    if (*p == '+') ++p;
    else if (*p == '-') { neg = 1; ++p; }
    double num;
    const char *end;
    if (!parse_num(p, &num, &end)) return 0;
    while (*end == ' ' || *end == '\t') ++end;
    double px;
    if (end[0] == '\0') {
        if (num != 0.0) return 0;       /* unitless non-zero length: invalid */
        px = 0.0;
    } else if (csel_ci_eq(end, "px")) {
        px = num;
    } else if (csel_ci_eq(end, "em") || csel_ci_eq(end, "rem")) {
        px = num * 16.0;
    } else {
        return 0;                       /* %, vw/vh, pt, ... */
    }
    int val = round_clamp(px, 0, CSS_LEN_MAX);   /* px >= 0 here; sign applied next */
    if (neg) val = -val;
    *out = val;
    return 1;
}

/* Emits one box length declaration for slot into dst (cap permitting). A negative
 * value is rejected unless allow_neg (margins allow it; padding/width do not).
 * Returns 1 on success, 0 if the value is unsupported or does not fit. */
static int emit_len(css_decl *dst, int cap, int slot, const char *val,
                    int allow_auto, int allow_neg) {
    int o;
    if (cap < 1 || !interp_len(val, allow_auto, &o)) return 0;
    if (!allow_neg && o != CSS_LEN_AUTO && o < 0) return 0;
    dst[0].prop = slot;
    dst[0].ival = o;
    return 1;
}

/* Emits a symbolic percentage width for slot (Hito 32): "<num>%" with num > 0,
 * carried as per-mille (99.8% -> 998) and saturating at 1000% (10000). The parser
 * has no containing block, so the value stays symbolic until layout resolves it
 * (bx_width_cap). Junk or a non-positive number fails closed (returns 0). */
static int emit_pct(css_decl *dst, int cap, int slot, const char *val) {
    if (cap < 1) return 0;
    const char *p = val;
    if (*p == '+') ++p;
    double num;
    const char *end;
    if (!parse_num(p, &num, &end)) return 0;
    while (*end == ' ' || *end == '\t') ++end;
    if (end[0] != '%' || end[1] != '\0') return 0;
    if (num <= 0.0) return 0;
    double pm = num * 10.0;
    if (pm > 10000.0) pm = 10000.0;
    int v = (int)(pm + 0.5);
    if (v < 1) return 0;
    dst[0].prop = slot;
    dst[0].ival = v;
    return 1;
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
static int next_ws_token(const char **p, char *tok, size_t cap) {
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
static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
                       css_decl *dst, int cap) {
    int vals[4], nv = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (nv < 4 && next_ws_token(&p, tok, sizeof tok)) {
        int o;
        if (!interp_len(tok, allow_auto, &o)) return 0;
        if (!allow_neg && o != CSS_LEN_AUTO && o < 0) return 0;
        vals[nv++] = o;
    }
    if (nv == 0) return 0;
    int top, right, bottom, left;
    switch (nv) {
        case 1: top = right = bottom = left = vals[0]; break;
        case 2: top = bottom = vals[0]; right = left = vals[1]; break;
        case 3: top = vals[0]; right = left = vals[1]; bottom = vals[2]; break;
        default: top = vals[0]; right = vals[1]; bottom = vals[2]; left = vals[3]; break;
    }
    int sides[4] = { top, right, bottom, left };
    int n = 0;
    for (int s = 0; s < 4 && n < cap; ++s) {
        dst[n].prop = slot_top + s;
        dst[n].ival = sides[s];
        ++n;
    }
    return n;
}

/* Expands a two-slot logical shorthand (margin-inline / padding-block /
 * inset-inline: one value sets both sides, two set start then end; 2026-07-10).
 * Fail closed on zero, more than two, or any uninterpretable token. */
static int expand_box2(const char *val, int slot_start, int slot_end,
                       int allow_auto, int allow_neg, css_decl *dst, int cap) {
    int vals[2], nv = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (nv < 2 && next_ws_token(&p, tok, sizeof tok)) {
        int o;
        if (!interp_len(tok, allow_auto, &o)) return 0;
        if (!allow_neg && o != CSS_LEN_AUTO && o < 0) return 0;
        vals[nv++] = o;
    }
    if (nv == 0 || next_ws_token(&p, tok, sizeof tok)) return 0;
    if (cap < 2) return 0;
    dst[0].prop = slot_start; dst[0].ival = vals[0];
    dst[1].prop = slot_end;   dst[1].ival = (nv == 2) ? vals[1] : vals[0];
    return 2;
}

/* --- text-presentation extensions (Hito 23b-6) --- */

/* Maps one font-family name (a generic keyword or a common family) to a generic
 * css_font_family bucket; -1 if unrecognised. Case-insensitive; multi-word names
 * (e.g. "times new roman") are compared whole. */
static int family_of(const char *name) {
    static const struct { const char *n; int f; } tbl[] = {
        { "serif", CSS_FF_SERIF }, { "ui-serif", CSS_FF_SERIF },
        { "times", CSS_FF_SERIF }, { "times new roman", CSS_FF_SERIF },
        { "georgia", CSS_FF_SERIF }, { "garamond", CSS_FF_SERIF },
        { "cambria", CSS_FF_SERIF }, { "palatino", CSS_FF_SERIF },
        { "sans-serif", CSS_FF_SANS }, { "ui-sans-serif", CSS_FF_SANS },
        { "system-ui", CSS_FF_SANS }, { "arial", CSS_FF_SANS },
        { "helvetica", CSS_FF_SANS }, { "verdana", CSS_FF_SANS },
        { "tahoma", CSS_FF_SANS }, { "segoe ui", CSS_FF_SANS },
        { "roboto", CSS_FF_SANS }, { "open sans", CSS_FF_SANS },
        { "monospace", CSS_FF_MONO }, { "ui-monospace", CSS_FF_MONO },
        { "courier", CSS_FF_MONO }, { "courier new", CSS_FF_MONO },
        { "consolas", CSS_FF_MONO }, { "monaco", CSS_FF_MONO },
        { "menlo", CSS_FF_MONO }, { "dejavu sans mono", CSS_FF_MONO },
        { "cursive", CSS_FF_CURSIVE }, { "comic sans ms", CSS_FF_CURSIVE },
        { "fantasy", CSS_FF_FANTASY }, { "impact", CSS_FF_FANTASY },
    };
    for (size_t i = 0; i < sizeof tbl / sizeof tbl[0]; ++i)
        if (csel_ci_eq(name, tbl[i].n)) return tbl[i].f;
    return -1;
}

/* font-family: the first recognised name in the comma-separated stack wins (its
 * generic bucket). Quotes are stripped. url() defensively dropped. -1 if none known. */
static int interp_fontfamily(const char *v) {
    if (csel_substr(v, "url(", 1)) return -1;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t' || *p == ',') ++p;
        if (*p == '\0') break;
        const char *st = p;
        while (*p != '\0' && *p != ',') ++p;       /* one comma entry */
        size_t e = (size_t)(p - st);
        while (e > 0 && (st[e-1] == ' ' || st[e-1] == '\t')) --e;
        size_t a = 0;
        if (e >= 2 && (st[0] == '"' || st[0] == '\'') && st[e-1] == st[0]) { a = 1; --e; }
        char buf[CSS_TOK_MAX];
        size_t k = 0;
        for (size_t i = a; i < e && k + 1 < sizeof buf; ++i) buf[k++] = st[i];
        buf[k] = '\0';
        int f = family_of(buf);
        if (f >= 0) return f;
    }
    return -1;
}

static int interp_texttransform(const char *v) {
    if (csel_ci_eq(v, "none"))       return CSS_TT_NONE;
    if (csel_ci_eq(v, "uppercase"))  return CSS_TT_UPPERCASE;
    if (csel_ci_eq(v, "lowercase"))  return CSS_TT_LOWERCASE;
    if (csel_ci_eq(v, "capitalize")) return CSS_TT_CAPITALIZE;
    return -1;  /* full-width/full-size-kana/...: out of scope, fail closed */
}

/* opacity: a unitless 0..1 alpha (or a percentage), mapped to 0..100 and clamped.
 * A negative or unparseable value is dropped (-1). */
static int interp_opacity(const char *v) {
    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    double pct;
    if (end[0] == '%' && end[1] == '\0') pct = num;
    else if (end[0] == '\0')             pct = num * 100.0;
    else return -1;
    return round_clamp(pct, 0, 100);
}

static int interp_valign(const char *v) {
    if (csel_ci_eq(v, "baseline")) return CSS_VA_BASELINE;
    if (csel_ci_eq(v, "sub"))      return CSS_VA_SUB;
    if (csel_ci_eq(v, "super"))    return CSS_VA_SUPER;
    return -1;  /* top/middle/bottom/<length>: out of scope, fail closed */
}

static int interp_whitespace(const char *v) {
    if (csel_ci_eq(v, "normal"))   return CSS_WS_NORMAL;
    if (csel_ci_eq(v, "nowrap"))   return CSS_WS_NOWRAP;
    if (csel_ci_eq(v, "pre"))      return CSS_WS_PRE;
    if (csel_ci_eq(v, "pre-wrap")) return CSS_WS_PRE_WRAP;
    if (csel_ci_eq(v, "pre-line")) return CSS_WS_PRE_LINE;
    /* break-spaces preserves whitespace and wraps; this engine only models the
     * wrap/keep distinction, so it collapses to pre-wrap (2026-07-10). */
    if (csel_ci_eq(v, "break-spaces")) return CSS_WS_PRE_WRAP;
    return -1;
}

/* tab-size: a non-negative integer (number of spaces). -1 if unsupported. */
static int interp_tabsize(const char *v) {
    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    if (*end != '\0') return -1;  /* units/lengths dropped; only bare number */
    int n = round_clamp(num, 0, 64);
    return (n > 0) ? n : -1;  /* 0 or unparseable -> unset */
}

/* text-decoration-style: solid/wavy/dotted/dashed/double. -1 if unknown. */
static int interp_textdeco_style(const char *v) {
    if (csel_ci_eq(v, "solid"))  return CSS_TDS_SOLID;
    if (csel_ci_eq(v, "double")) return CSS_TDS_DOUBLE;
    if (csel_ci_eq(v, "dotted")) return CSS_TDS_DOTTED;
    if (csel_ci_eq(v, "dashed")) return CSS_TDS_DASHED;
    if (csel_ci_eq(v, "wavy"))   return CSS_TDS_WAVY;
    return -1;
}

/* text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length
 * (px -> px, em/rem x16). -1 if unsupported (negative, %, etc -> dropped). */
static int interp_textdeco_thickness(const char *v) {
    if (csel_ci_eq(v, "from-font")) return 0;
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return -1;
    return px;
}

/* aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>`
 * (auto fallback). Stores both numerator and denominator x1000 (for sub-integer
 * ratios like 1.5 -> 1500/1000). Returns 1 with *num and *den set, 0 if unsupported.
 * A bare number 1.5 is stored as 1500/1000; 16/9 as 16000/9000;
 * auto / unparseable -> 0 (unset). */
static int interp_aspect_ratio(const char *v, int *num, int *den) {
    *num = *den = 0;
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    if (csel_ci_eq(p, "auto")) return 1;  /* auto alone -> unset (natural sizing) */
    char buf[CSS_TOK_MAX];
    size_t k = 0;
    while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof buf) buf[k++] = *p++;
    buf[k] = '\0';
    if (k == 0) return 1;
    /* Look for a '/' separator */
    char *slash = strchr(buf, '/');
    if (slash != NULL) {
        *slash = '\0';
        char *nend = slash + 1;
        double nv, dv;
        const char *ne, *de;
        if (!parse_num(buf, &nv, &ne) || *ne != '\0') return 1;   /* fail -> unset */
        if (!parse_num(nend, &dv, &de) || *de != '\0' || dv <= 0.0) return 1;
        *num = round_clamp(nv * 1000.0, 1, CSS_LEN_MAX);
        *den = round_clamp(dv * 1000.0, 1, CSS_LEN_MAX);
        return 1;
    }
    /* Bare number: treat as w/h = N/1 */
    double nv;
    const char *ne;
    if (!parse_num(buf, &nv, &ne) || *ne != '\0' || nv <= 0.0) return 1;
    *num = round_clamp(nv * 1000.0, 1, CSS_LEN_MAX);
    *den = 1000;
    return 1;
}

/* direction: ltr/rtl. -1 if unknown. */
static int interp_direction(const char *v) {
    if (csel_ci_eq(v, "ltr")) return CSS_DIR_LTR;
    if (csel_ci_eq(v, "rtl")) return CSS_DIR_RTL;
    return -1;
}

static int liststyle_kw(const char *t) {
    if (csel_ci_eq(t, "none"))        return CSS_LS_NONE;
    if (csel_ci_eq(t, "disc"))        return CSS_LS_DISC;
    if (csel_ci_eq(t, "circle"))      return CSS_LS_CIRCLE;
    if (csel_ci_eq(t, "square"))      return CSS_LS_SQUARE;
    if (csel_ci_eq(t, "decimal"))     return CSS_LS_DECIMAL;
    if (csel_ci_eq(t, "lower-alpha") || csel_ci_eq(t, "lower-latin")) return CSS_LS_LOWER_ALPHA;
    if (csel_ci_eq(t, "upper-alpha") || csel_ci_eq(t, "upper-latin")) return CSS_LS_UPPER_ALPHA;
    if (csel_ci_eq(t, "lower-roman")) return CSS_LS_LOWER_ROMAN;
    if (csel_ci_eq(t, "upper-roman")) return CSS_LS_UPPER_ROMAN;
    return -1;
}

/* list-style-type, or the type token of the list-style shorthand: the first
 * recognised keyword wins. url() (a list-style-image) is dropped: never fetch. */
static int interp_liststyle(const char *v) {
    if (csel_substr(v, "url(", 1)) return -1;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        while (*p != '\0' && *p != ' ' && *p != '\t') ++p;
        int ls = liststyle_kw(tok);
        if (ls >= 0) return ls;
    }
    return -1;
}

/* letter-spacing / word-spacing: "normal" -> 0, else a signed length (px/em/0),
 * clamped to [-CSS_SPACING_MAX, CSS_SPACING_MAX]. Returns 1 with *out set, 0 if
 * the value is unsupported (%/vw/calc/bare number -> dropped, fail closed). */
static int interp_spacing(const char *v, int *out) {
    if (csel_ci_eq(v, "normal")) { *out = 0; return 1; }
    int px;
    if (!interp_len(v, 0, &px)) return 0;
    if (px > CSS_SPACING_MAX) px = CSS_SPACING_MAX;
    if (px < -CSS_SPACING_MAX) px = -CSS_SPACING_MAX;
    *out = px;
    return 1;
}

static int emit_spacing(css_decl *dst, int cap, int slot, const char *val) {
    int o;
    if (cap < 1 || !interp_spacing(val, &o)) return 0;
    dst[0].prop = slot;
    dst[0].ival = o;
    return 1;
}

/* text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is
 * ignored) and an optional color, in any order. "none" emits an explicit no-shadow.
 * Needs at least dx and dy or the whole declaration is dropped (fail closed). When no
 * color is given it defaults to black. url() dropped: never fetch. Writes the three
 * contiguous P_SHADOW_* slots; offsets clamped to [-CSS_SHADOW_MAX, CSS_SHADOW_MAX]. */
static int expand_shadow(const char *val, css_decl *dst, int cap) {
    if (cap < 3) return 0;
    if (csel_substr(val, "url(", 1)) return 0;
    if (csel_ci_eq(val, "none")) {
        dst[0].prop = P_SHADOW_DX;    dst[0].ival = 0;
        dst[1].prop = P_SHADOW_DY;    dst[1].ival = 0;
        dst[2].prop = P_SHADOW_COLOR; dst[2].ival = -1;
        return 3;
    }
    int lens[3], nlen = 0, color = 0, have_color = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (next_ws_token(&p, tok, sizeof tok)) {
        int px;
        if (interp_len(tok, 0, &px)) { if (nlen < 3) lens[nlen++] = px; }
        else if (!have_color) { int cv = parse_color(tok); if (cv != -1) { color = cv; have_color = 1; } }
    }
    if (nlen < 2) return 0;  /* need both offsets */
    int dx = lens[0], dy = lens[1];
    if (dx > CSS_SHADOW_MAX) dx = CSS_SHADOW_MAX;
    if (dx < -CSS_SHADOW_MAX) dx = -CSS_SHADOW_MAX;
    if (dy > CSS_SHADOW_MAX) dy = CSS_SHADOW_MAX;
    if (dy < -CSS_SHADOW_MAX) dy = -CSS_SHADOW_MAX;
    dst[0].prop = P_SHADOW_DX;    dst[0].ival = dx;
    dst[1].prop = P_SHADOW_DY;    dst[1].ival = dy;
    dst[2].prop = P_SHADOW_COLOR; dst[2].ival = have_color ? color : CC_COLOR_CURRENT;
    return 3;
}

/* --- Layout / box decoration (Hito 23b-7) --------------------------------- */

static int interp_position(const char *v) {
    if (csel_ci_eq(v, "static"))   return CSS_POS_STATIC;
    if (csel_ci_eq(v, "relative")) return CSS_POS_RELATIVE;
    if (csel_ci_eq(v, "absolute")) return CSS_POS_ABSOLUTE;
    if (csel_ci_eq(v, "fixed"))    return CSS_POS_FIXED;
    if (csel_ci_eq(v, "sticky"))   return CSS_POS_STICKY;
    return -1;
}

static int interp_boxsizing(const char *v) {
    if (csel_ci_eq(v, "content-box")) return CSS_BOXS_CONTENT;
    if (csel_ci_eq(v, "border-box"))  return CSS_BOXS_BORDER;
    return -1;
}

static int interp_float(const char *v) {
    if (csel_ci_eq(v, "none"))  return CSS_FLOAT_NONE;
    if (csel_ci_eq(v, "left"))  return CSS_FLOAT_LEFT;
    if (csel_ci_eq(v, "right")) return CSS_FLOAT_RIGHT;
    return -1;
}

static int interp_clear(const char *v) {
    if (csel_ci_eq(v, "none"))  return CSS_CLEAR_NONE;
    if (csel_ci_eq(v, "left"))  return CSS_CLEAR_LEFT;
    if (csel_ci_eq(v, "right")) return CSS_CLEAR_RIGHT;
    if (csel_ci_eq(v, "both"))  return CSS_CLEAR_BOTH;
    return -1;
}

/* --- visibility / overflow / cursor / text-overflow / word-break ---------- */

static int interp_visibility(const char *v) {
    if (csel_ci_eq(v, "visible"))  return CSS_VIS_VISIBLE;
    if (csel_ci_eq(v, "hidden"))   return CSS_VIS_HIDDEN;
    if (csel_ci_eq(v, "collapse")) return CSS_VIS_COLLAPSE;
    return -1;
}

static int interp_overflow(const char *v) {
    if (csel_ci_eq(v, "visible")) return CSS_OF_VISIBLE;
    if (csel_ci_eq(v, "hidden"))  return CSS_OF_HIDDEN;
    if (csel_ci_eq(v, "clip"))    return CSS_OF_HIDDEN; /* clip: like hidden, never scrolls */
    if (csel_ci_eq(v, "scroll"))  return CSS_OF_SCROLL;
    if (csel_ci_eq(v, "auto"))    return CSS_OF_AUTO;
    return -1;
}

/* `overflow: X` sets both overflow-x and overflow-y to the same value. The two-token
 * per-axis form (`overflow: hidden visible`) is out of scope -- use the longhands. */
static int expand_overflow(const char *val, css_decl *dst, int cap) {
    int o = interp_overflow(val);
    if (o < 0 || cap < 2) return 0;
    dst[0].prop = P_OVERFLOW_X; dst[0].ival = o;
    dst[1].prop = P_OVERFLOW_Y; dst[1].ival = o;
    return 2;
}

static int interp_cursor(const char *v) {
    if (csel_ci_eq(v, "auto"))        return CSS_CUR_AUTO;
    if (csel_ci_eq(v, "default"))     return CSS_CUR_DEFAULT;
    if (csel_ci_eq(v, "pointer"))     return CSS_CUR_POINTER;
    if (csel_ci_eq(v, "text"))        return CSS_CUR_TEXT;
    if (csel_ci_eq(v, "move"))        return CSS_CUR_MOVE;
    if (csel_ci_eq(v, "not-allowed")) return CSS_CUR_NOT_ALLOWED;
    if (csel_ci_eq(v, "help"))        return CSS_CUR_HELP;
    if (csel_ci_eq(v, "wait"))        return CSS_CUR_WAIT;
    if (csel_ci_eq(v, "crosshair"))   return CSS_CUR_CROSSHAIR;
    if (csel_ci_eq(v, "grab"))        return CSS_CUR_GRAB;
    if (csel_ci_eq(v, "zoom-in"))     return CSS_CUR_ZOOM_IN;
    if (csel_ci_eq(v, "none"))        return CSS_CUR_NONE;
    return -1;
}

static int interp_text_overflow(const char *v) {
    if (csel_ci_eq(v, "clip"))     return CSS_TO_CLIP;
    if (csel_ci_eq(v, "ellipsis")) return CSS_TO_ELLIPSIS;
    return -1;
}

static int interp_word_break(const char *v) {
    if (csel_ci_eq(v, "normal"))    return CSS_WB_NORMAL;
    if (csel_ci_eq(v, "break-all")) return CSS_WB_BREAK;
    if (csel_ci_eq(v, "keep-all"))  return CSS_WB_NORMAL; /* CJK line-breaking not modeled */
    return -1;
}

static int interp_overflow_wrap(const char *v) {
    if (csel_ci_eq(v, "normal"))     return CSS_WB_NORMAL;
    if (csel_ci_eq(v, "break-word")) return CSS_WB_BREAK;
    if (csel_ci_eq(v, "anywhere"))   return CSS_WB_BREAK;
    return -1;
}

/* border-collapse: collapse/separate. -1 if unknown. */
static int interp_border_collapse(const char *v) {
    if (csel_ci_eq(v, "collapse")) return CSS_BCOL_COLLAPSE;
    if (csel_ci_eq(v, "separate")) return CSS_BCOL_SEPARATE;
    return -1;
}

/* border-spacing: the first length only (a single value: uniform; the two-value
 * h/v form gives horizontal and only the first is honoured in v1). px/em/rem/0,
 * clamped to [0, CSS_BORDER_SPACING_MAX]. -1 unsupported. Also accepts a bare
 * number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_spacing(const char *v) {
    char tok[CSS_TOK_MAX];
    size_t k = 0;
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
    tok[k] = '\0';
    /* Try interp_len first (handles px/em/rem/0/calc). A bare non-zero number
     * fails there, so fall back to a simple numeric parse as px. */
    int px;
    if (interp_len(tok, 0, &px) && px >= 0) {
        if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX;
        return px;
    }
    double num;
    const char *end;
    if (parse_num(tok, &num, &end) && *end == '\0' && num >= 0.0) {
        px = round_clamp(num, 0, CSS_BORDER_SPACING_MAX);
        return px;
    }
    return -1;
}

/* empty-cells: show/hide. -1 unknown. */
static int interp_empty_cells(const char *v) {
    if (csel_ci_eq(v, "show")) return CSS_EC_SHOW;
    if (csel_ci_eq(v, "hide")) return CSS_EC_HIDE;
    return -1;
}

/* caption-side: top/bottom. -1 unknown. */
static int interp_caption_side(const char *v) {
    if (csel_ci_eq(v, "top"))    return CSS_CS_TOP;
    if (csel_ci_eq(v, "bottom")) return CSS_CS_BOTTOM;
    return -1;
}

/* table-layout: auto/fixed. -1 unknown. */
static int interp_table_layout(const char *v) {
    if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO;
    if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED;
    return -1;
}

/* font-variant (subset: only small-caps). normal/small-caps. -1 unknown. */
static int interp_font_variant(const char *v) {
    if (csel_ci_eq(v, "normal"))     return CSS_FV_NORMAL;
    if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS;
    /* all-small-caps, petite-caps, etc: out of scope, fail closed */
    return -1;
}

/* hyphens: none/manual/auto. -1 unknown. */
static int interp_hyphens(const char *v) {
    if (csel_ci_eq(v, "none"))   return CSS_HY_NONE;
    if (csel_ci_eq(v, "manual")) return CSS_HY_MANUAL;
    if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO;
    return -1;
}

/* user-select: none/text/all/auto. -1 unknown. */
static int interp_user_select(const char *v) {
    if (csel_ci_eq(v, "none")) return CSS_US_NONE;
    if (csel_ci_eq(v, "text")) return CSS_US_TEXT;
    if (csel_ci_eq(v, "all"))  return CSS_US_ALL;
    if (csel_ci_eq(v, "auto")) return CSS_US_AUTO;
    return -1;
}

/* caret-color: auto -> CSS_LEN_AUTO sentinel; color -> 0xRRGGBB; -1 unset. */
static int interp_caret_color(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO;
    return parse_color(v);
}

/* appearance: auto/none. -1 unknown. */
static int interp_appearance(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_AP_AUTO;
    if (csel_ci_eq(v, "none")) return CSS_AP_NONE;
    return -1;
}

/* pointer-events: auto/none. -1 unknown. */
static int interp_pointer_events(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_PE_AUTO;
    if (csel_ci_eq(v, "none")) return CSS_PE_NONE;
    return -1;
}

/* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. */
static int interp_bg_repeat(const char *v) {
    if (csel_ci_eq(v, "repeat"))    return CSS_BGR_REPEAT;
    if (csel_ci_eq(v, "no-repeat")) return CSS_BGR_NO_REPEAT;
    if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X;
    if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y;
    if (csel_ci_eq(v, "space"))     return CSS_BGR_SPACE;
    if (csel_ci_eq(v, "round"))     return CSS_BGR_ROUND;
    return -1;
}
/* background-size: auto/cover/contain. -1 unknown (lengths dropped). */
static int interp_bg_size(const char *v) {
    if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO;
    if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER;
    if (csel_ci_eq(v, "contain")) return CSS_BGS_CONTAIN;
    return -1;
}
/* background-clip: border-box/padding-box/content-box/text. -1 unknown. */
static int interp_bg_clip(const char *v) {
    if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX;
    if (csel_ci_eq(v, "padding-box"))  return CSS_BGC_PADDING_BOX;
    if (csel_ci_eq(v, "content-box"))  return CSS_BGC_CONTENT_BOX;
    if (csel_ci_eq(v, "text"))         return CSS_BGC_TEXT;
    return -1;
}
/* background-origin: padding-box/border-box/content-box. -1 unknown. */
static int interp_bg_origin(const char *v) {
    if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX;
    if (csel_ci_eq(v, "border-box"))   return CSS_BGO_BORDER_BOX;
    if (csel_ci_eq(v, "content-box"))  return CSS_BGO_CONTENT_BOX;
    return -1;
}
/* background-attachment: scroll/fixed/local. -1 unknown. */
static int interp_bg_attachment(const char *v) {
    if (csel_ci_eq(v, "scroll")) return CSS_BGA_SCROLL;
    if (csel_ci_eq(v, "fixed"))  return CSS_BGA_FIXED;
    if (csel_ci_eq(v, "local"))  return CSS_BGA_LOCAL;
    return -1;
}
/* isolation: auto/isolate. -1 unknown. */
static int interp_isolation(const char *v) {
    if (csel_ci_eq(v, "auto"))    return CSS_ISO_AUTO;
    if (csel_ci_eq(v, "isolate")) return CSS_ISO_ISOLATE;
    return -1;
}
/* contain: none/strict/content / space-separated size layout style paint. */
static int interp_contain(const char *v) {
    if (csel_ci_eq(v, "none"))    return 0;
    if (csel_ci_eq(v, "strict"))  return CSS_CONTAIN_SIZE|CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT;
    if (csel_ci_eq(v, "content")) return CSS_CONTAIN_LAYOUT|CSS_CONTAIN_STYLE|CSS_CONTAIN_PAINT;
    int mask = 0;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        if (csel_ci_eq(tok, "size"))   mask |= CSS_CONTAIN_SIZE;
        else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT;
        else if (csel_ci_eq(tok, "style"))  mask |= CSS_CONTAIN_STYLE;
        else if (csel_ci_eq(tok, "paint"))  mask |= CSS_CONTAIN_PAINT;
    }
    return mask;
}
/* content-visibility: visible/auto/hidden. -1 unknown. */
static int interp_content_visibility(const char *v) {
    if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE;
    if (csel_ci_eq(v, "auto"))    return CSS_CV_AUTO;
    if (csel_ci_eq(v, "hidden"))  return CSS_CV_HIDDEN;
    return -1;
}
/* image-rendering: auto/pixelated/crisp-edges. -1 unknown. */
static int interp_image_rendering(const char *v) {
    if (csel_ci_eq(v, "auto"))        return CSS_IR_AUTO;
    if (csel_ci_eq(v, "pixelated"))   return CSS_IR_PIXELATED;
    if (csel_ci_eq(v, "crisp-edges")) return CSS_IR_CRISP_EDGES;
    return -1;
}
/* color-scheme: normal/light/dark; multi-keyword "light dark" -> first wins. -1 unknown. */
static int interp_color_scheme(const char *v) {
    if (csel_ci_eq(v, "normal")) return CSS_CSH_NORMAL;
    if (csel_ci_eq(v, "light"))  return CSS_CSH_LIGHT;
    if (csel_ci_eq(v, "dark"))   return CSS_CSH_DARK;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        if (csel_ci_eq(tok, "light")) return CSS_CSH_LIGHT;
        if (csel_ci_eq(tok, "dark"))  return CSS_CSH_DARK;
    }
    return -1;
}
/* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. */
static int interp_accent_color(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO;
    return parse_color(v);
}
/* print-color-adjust: economy/exact. -1 unknown. */
static int interp_print_color_adjust(const char *v) {
    if (csel_ci_eq(v, "economy")) return CSS_PCA_ECONOMY;
    if (csel_ci_eq(v, "exact"))   return CSS_PCA_EXACT;
    return -1;
}
/* forced-color-adjust: auto/none. -1 unknown. */
static int interp_forced_color_adjust(const char *v) {
    if (csel_ci_eq(v, "auto")) return CSS_FCA_AUTO;
    if (csel_ci_eq(v, "none")) return CSS_FCA_NONE;
    return -1;
}

/* mix-blend-mode: normal/multiply/screen/… -1 unknown. */
static int interp_mix_blend_mode(const char *v) {
    if (csel_ci_eq(v, "normal"))       return CSS_MB_NORMAL;
    if (csel_ci_eq(v, "multiply"))     return CSS_MB_MULTIPLY;
    if (csel_ci_eq(v, "screen"))       return CSS_MB_SCREEN;
    if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY;
    if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN;
    if (csel_ci_eq(v, "lighten"))      return CSS_MB_LIGHTEN;
    if (csel_ci_eq(v, "color-dodge"))  return CSS_MB_COLOR_DODGE;
    if (csel_ci_eq(v, "color-burn"))   return CSS_MB_COLOR_BURN;
    if (csel_ci_eq(v, "difference"))   return CSS_MB_DIFFERENCE;
    if (csel_ci_eq(v, "exclusion"))    return CSS_MB_EXCLUSION;
    if (csel_ci_eq(v, "hue"))          return CSS_MB_HUE;
    if (csel_ci_eq(v, "saturation"))   return CSS_MB_SATURATION;
    if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR;
    if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY;
    return -1;
}
/* object-fit: fill/contain/cover/none/scale-down. -1 unknown. */
static int interp_object_fit(const char *v) {
    if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL;
    if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN;
    if (csel_ci_eq(v, "cover"))       return CSS_OFI_COVER;
    if (csel_ci_eq(v, "none"))        return CSS_OFI_NONE;
    if (csel_ci_eq(v, "scale-down"))  return CSS_OFI_SCALE_DOWN;
    return -1;
}
/* list-style-position: inside/outside. -1 unknown. */
static int interp_list_style_pos(const char *v) {
    if (csel_ci_eq(v, "inside"))  return CSS_LP_INSIDE;
    if (csel_ci_eq(v, "outside")) return CSS_LP_OUTSIDE;
    return -1;
}
/* font-kerning: auto/normal/none. -1 unknown. */
static int interp_font_kerning(const char *v) {
    if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO;
    if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL;
    if (csel_ci_eq(v, "none"))   return CSS_FK_NONE;
    return -1;
}
/* text-rendering: auto/optimizeSpeed/optimizeLegibility/geometricPrecision. -1 unknown. */
static int interp_text_rendering(const char *v) {
    if (csel_ci_eq(v, "auto"))                return CSS_TR_AUTO;
    if (csel_ci_eq(v, "optimizeSpeed"))       return CSS_TR_OPTIMIZE_SPEED;
    if (csel_ci_eq(v, "optimizeLegibility"))  return CSS_TR_OPTIMIZE_LEGIBILITY;
    if (csel_ci_eq(v, "geometricPrecision"))  return CSS_TR_GEOMETRIC_PRECISION;
    return -1;
}
/* font-stretch: normal/condensed/expanded/etc. -1 unknown. */
static int interp_font_stretch(const char *v) {
    if (csel_ci_eq(v, "normal"))             return CSS_FS_NORMAL;
    if (csel_ci_eq(v, "condensed"))          return CSS_FS_CONDENSED;
    if (csel_ci_eq(v, "expanded"))           return CSS_FS_EXPANDED;
    if (csel_ci_eq(v, "ultra-condensed"))    return CSS_FS_ULTRA_CONDENSED;
    if (csel_ci_eq(v, "extra-condensed"))    return CSS_FS_EXTRA_CONDENSED;
    if (csel_ci_eq(v, "semi-condensed"))     return CSS_FS_SEMI_CONDENSED;
    if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED;
    if (csel_ci_eq(v, "extra-expanded"))     return CSS_FS_EXTRA_EXPANDED;
    if (csel_ci_eq(v, "ultra-expanded"))     return CSS_FS_ULTRA_EXPANDED;
    return -1;
}
/* resize: none/both/horizontal/vertical. -1 unknown. */
static int interp_resize(const char *v) {
    if (csel_ci_eq(v, "none"))        return CSS_RS_NONE;
    if (csel_ci_eq(v, "both"))        return CSS_RS_BOTH;
    if (csel_ci_eq(v, "horizontal"))  return CSS_RS_HORIZONTAL;
    if (csel_ci_eq(v, "vertical"))    return CSS_RS_VERTICAL;
    return -1;
}
/* scroll-behavior: auto/smooth. -1 unknown. */
static int interp_scroll_behavior(const char *v) {
    if (csel_ci_eq(v, "auto"))   return CSS_SB_AUTO;
    if (csel_ci_eq(v, "smooth")) return CSS_SB_SMOOTH;
    return -1;
}
/* touch-action: auto/none/manipulation. -1 unknown. */
static int interp_touch_action(const char *v) {
    if (csel_ci_eq(v, "auto"))         return CSS_TA_AUTO;
    if (csel_ci_eq(v, "none"))         return CSS_TA_NONE;
    if (csel_ci_eq(v, "manipulation")) return CSS_TA_MANIPULATION;
    return -1;
}
/* overscroll-behavior: auto/contain/none. -1 unknown. */
static int interp_overscroll_behavior(const char *v) {
    if (csel_ci_eq(v, "auto"))    return CSS_OS_AUTO;
    if (csel_ci_eq(v, "contain")) return CSS_OS_CONTAIN;
    if (csel_ci_eq(v, "none"))    return CSS_OS_NONE;
    return -1;
}
/* backface-visibility: visible/hidden. -1 unknown. */
static int interp_backface_visibility(const char *v) {
    if (csel_ci_eq(v, "visible")) return CSS_BF_VISIBLE;
    if (csel_ci_eq(v, "hidden"))  return CSS_BF_HIDDEN;
    return -1;
}
/* Signed integer (z-index/order). Returns 1 with *out (clamped to +-CSS_LEN_MAX),
 * 0 if not a pure integer (auto / floats / units -> dropped, leaving unset). */
static int interp_int(const char *v, int *out) {
    const char *p = v;
    int neg = 0;
    if (*p == '+') ++p; else if (*p == '-') { neg = 1; ++p; }
    if (*p < '0' || *p > '9') return 0;
    long val = 0;
    while (*p >= '0' && *p <= '9') {
        val = val * 10 + (*p - '0');
        if (val > CSS_LEN_MAX) val = CSS_LEN_MAX;
        ++p;
    }
    if (*p != '\0') return 0;   /* trailing fraction/unit: not an integer */
    *out = neg ? -(int)val : (int)val;
    return 1;
}

static int interp_border_style(const char *v) {
    if (csel_ci_eq(v, "none"))   return CSS_BST_NONE;
    if (csel_ci_eq(v, "hidden")) return CSS_BST_HIDDEN;
    if (csel_ci_eq(v, "solid"))  return CSS_BST_SOLID;
    if (csel_ci_eq(v, "dashed")) return CSS_BST_DASHED;
    if (csel_ci_eq(v, "dotted")) return CSS_BST_DOTTED;
    if (csel_ci_eq(v, "double")) return CSS_BST_DOUBLE;
    if (csel_ci_eq(v, "groove")) return CSS_BST_GROOVE;
    if (csel_ci_eq(v, "ridge"))  return CSS_BST_RIDGE;
    if (csel_ci_eq(v, "inset"))  return CSS_BST_INSET;
    if (csel_ci_eq(v, "outset")) return CSS_BST_OUTSET;
    return -1;
}

/* Border/outline width token: thin/medium/thick keywords or a non-negative length.
 * Returns 1 with *out (px >= 0), 0 if unsupported. */
static int interp_border_width(const char *v, int *out) {
    if (csel_ci_eq(v, "thin"))   { *out = 1; return 1; }
    if (csel_ci_eq(v, "medium")) { *out = 3; return 1; }
    if (csel_ci_eq(v, "thick"))  { *out = 5; return 1; }
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return 0;
    *out = px;
    return 1;
}

static int interp_bwidth1(const char *v) {
    int o;
    return interp_border_width(v, &o) ? o : -1;
}

/* border-radius: the first value only (corner-by-corner / elliptical out of scope).
 * px >= 0, or -1 (unsupported: %/units dropped -> stays unset). */
static int interp_border_radius(const char *v) {
    char tok[CSS_TOK_MAX];
    size_t k = 0;
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '/' && k + 1 < sizeof tok)
        tok[k++] = *p++;
    tok[k] = '\0';
    int px;
    if (!interp_len(tok, 0, &px) || px < 0) return -1;
    return px;
}

/* token classifiers for the per-category border-{width,style,color} quad expanders. */
static int interp_bw_tok(const char *t, int *o) { return interp_border_width(t, o); }
static int interp_bs_tok(const char *t, int *o) { int r = interp_border_style(t); if (r < 0) return 0; *o = r; return 1; }
static int interp_bc_tok(const char *t, int *o) { int r = interp_color(t); if (r < 0) return 0; *o = r; return 1; }

typedef int (*tok_interp)(const char *tok, int *out);

/* Expands a 1-4 value box property (CSS order all / `v h` / `t h b` / `t r b l`) over
 * a token classifier f into the four contiguous slots from slot_top. Any unsupported
 * token drops the WHOLE shorthand (fail closed). Returns the number written (<= cap). */
static int expand_quad(const char *val, int slot_top, tok_interp f, css_decl *dst, int cap) {
    int vals[4], nv = 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (nv < 4 && next_ws_token(&p, tok, sizeof tok)) {
        int o;
        if (!f(tok, &o)) return 0;
        vals[nv++] = o;
    }
    if (nv == 0) return 0;
    int top, right, bottom, left;
    switch (nv) {
        case 1: top = right = bottom = left = vals[0]; break;
        case 2: top = bottom = vals[0]; right = left = vals[1]; break;
        case 3: top = vals[0]; right = left = vals[1]; bottom = vals[2]; break;
        default: top = vals[0]; right = vals[1]; bottom = vals[2]; left = vals[3]; break;
    }
    int sides[4] = { top, right, bottom, left };
    int n = 0;
    for (int s = 0; s < 4 && n < cap; ++s) { dst[n].prop = slot_top + s; dst[n].ival = sides[s]; ++n; }
    return n;
}

/* Classifies a `border`/`outline` shorthand value into an optional width, style and
 * color (each at most once, any order). An unrecognised token drops the whole edge
 * (fail closed). url() is dropped (never fetch). Returns 1 if any part was set. */
static int classify_box_edge(const char *val, int *w, int *hw, int *s, int *hs,
                             int *c, int *hc) {
    *hw = *hs = *hc = 0;
    if (csel_substr(val, "url(", 1)) return 0;
    const char *p = val;
    char tok[CSS_TOK_MAX];
    while (next_ws_token(&p, tok, sizeof tok)) {
        int tmp;
        if (!*hw && interp_border_width(tok, &tmp)) { *w = tmp; *hw = 1; }
        else if (!*hs && (tmp = interp_border_style(tok)) >= 0) { *s = tmp; *hs = 1; }
        else if (!*hc && (tmp = interp_color(tok)) >= 0) { *c = tmp; *hc = 1; }
        else return 0;   /* unrecognised token: drop the whole shorthand */
    }
    return (*hw || *hs || *hc);
}

/* border / border-<side> shorthand: sets the present width/style/color for each side
 * named in mask (bit s: 0 top, 1 right, 2 bottom, 3 left). Only the parts given are
 * emitted (omitted longhands stay unset — no initial-value reset). */
static int expand_border_shorthand(const char *val, int mask, css_decl *dst, int cap) {
    int w = 0, s = 0, c = 0, hw, hs, hc;
    if (!classify_box_edge(val, &w, &hw, &s, &hs, &c, &hc)) return 0;
    int n = 0;
    for (int side = 0; side < 4; ++side) {
        if (!(mask & (1 << side))) continue;
        if (hw && n < cap) { dst[n].prop = P_BW_TOP + side; dst[n].ival = w; ++n; }
        if (hs && n < cap) { dst[n].prop = P_BS_TOP + side; dst[n].ival = s; ++n; }
        if (hc && n < cap) { dst[n].prop = P_BC_TOP + side; dst[n].ival = c; ++n; }
    }
    return n;
}

static int expand_outline(const char *val, css_decl *dst, int cap) {
    int w = 0, s = 0, c = 0, hw, hs, hc;
    if (!classify_box_edge(val, &w, &hw, &s, &hs, &c, &hc)) return 0;
    int n = 0;
    if (hw && n < cap) { dst[n].prop = P_OUTLINE_W; dst[n].ival = w; ++n; }
    if (hs && n < cap) { dst[n].prop = P_OUTLINE_S; dst[n].ival = s; ++n; }
    if (hc && n < cap) { dst[n].prop = P_OUTLINE_C; dst[n].ival = c; ++n; }
    return n;
}

/* box-shadow (single layer): up to four lengths in order dx, dy, blur, spread, an
 * optional color, and an optional `inset` keyword, in any order. Needs >= 2 lengths
 * (dx, dy) or the whole declaration is dropped (fail closed). `none` is an explicit
 * no-shadow. url() dropped: never fetch. Writes the six contiguous P_BSHADOW_* slots. */
static int expand_box_shadow(const char *val, css_decl *dst, int cap) {
    if (cap < 6) return 0;
    if (csel_substr(val, "url(", 1)) return 0;
    int lens[4], nlen = 0, color = 0, have_color = 0, inset = 0;
    if (!csel_ci_eq(val, "none")) {
        const char *p = val;
        char tok[CSS_TOK_MAX];
        while (next_ws_token(&p, tok, sizeof tok)) {
            if (csel_ci_eq(tok, "inset")) { inset = 1; continue; }
            int px;
            if (interp_len(tok, 0, &px)) { if (nlen < 4) lens[nlen++] = px; }
            else if (!have_color) { int cv = parse_color(tok); if (cv != -1) { color = cv; have_color = 1; } }
            /* else: unknown token ignored */
        }
        if (nlen < 2) return 0;   /* need both offsets */
    }
    dst[0].prop = P_BSHADOW_DX;     dst[0].ival = nlen > 0 ? lens[0] : 0;
    dst[1].prop = P_BSHADOW_DY;     dst[1].ival = nlen > 1 ? lens[1] : 0;
    dst[2].prop = P_BSHADOW_BLUR;   dst[2].ival = nlen > 2 ? lens[2] : 0;
    dst[3].prop = P_BSHADOW_SPREAD; dst[3].ival = nlen > 3 ? lens[3] : 0;
    dst[4].prop = P_BSHADOW_COLOR;  dst[4].ival = csel_ci_eq(val, "none") ? -1
                                                : (have_color ? color : CC_COLOR_CURRENT);
    dst[5].prop = P_BSHADOW_INSET;  dst[5].ival = inset;
    return 6;
}

/* flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to
 * [0, CSS_FLEX_FACTOR_MAX]. Negative / unparseable -> -1 (dropped, stays unset). */
static int interp_flex_factor(const char *v) {
    double num;
    const char *end;
    if (!parse_num(v, &num, &end) || *end != '\0' || num < 0.0) return -1;
    return round_clamp(num * 100.0, 0, CSS_FLEX_FACTOR_MAX);
}

/* flex-basis: `auto`/`content` -> CSS_LEN_AUTO; a non-negative length -> px; %/units
 * dropped (returns 0, leaving unset). Returns 1 with *out, 0 if unsupported. */
static int interp_flex_basis(const char *v, int *out) {
    if (csel_ci_eq(v, "auto") || csel_ci_eq(v, "content")) { *out = CSS_LEN_AUTO; return 1; }
    int px;
    if (!interp_len(v, 0, &px) || px < 0) return 0;
    *out = px;
    return 1;
}

/* flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots. Keywords
 * none/auto/initial; otherwise up to three values (a unitless number is grow then
 * shrink; a length/auto is basis). Defaults: shrink 1, basis 0 when a grow is given,
 * else basis auto. */
static int expand_flex(const char *val, css_decl *dst, int cap) {
    if (cap < 3) return 0;
    int grow, shrink, basis;
    if (csel_ci_eq(val, "none"))         { grow = 0;   shrink = 0;   basis = CSS_LEN_AUTO; }
    else if (csel_ci_eq(val, "auto"))    { grow = 100; shrink = 100; basis = CSS_LEN_AUTO; }
    else if (csel_ci_eq(val, "initial")) { grow = 0;   shrink = 100; basis = CSS_LEN_AUTO; }
    else {
        int g = 0, sh = 0, ba = 0, have_g = 0, have_sh = 0, have_ba = 0;
        const char *p = val;
        int ntok = 0;
        char tok[CSS_TOK_MAX];
        while (ntok < 4 && next_ws_token(&p, tok, sizeof tok)) {
            ++ntok;
            double num;
            const char *end;
            if (parse_num(tok, &num, &end) && *end == '\0') {  /* unitless number */
                if (num < 0.0) return 0;
                int x100 = round_clamp(num * 100.0, 0, CSS_FLEX_FACTOR_MAX);
                if (!have_g)       { g = x100;  have_g = 1; }
                else if (!have_sh) { sh = x100; have_sh = 1; }
                else return 0;
            } else {                                            /* a length / auto */
                int b;
                if (have_ba || !interp_flex_basis(tok, &b)) return 0;
                ba = b; have_ba = 1;
            }
        }
        if (!have_g && !have_ba) return 0;   /* nothing usable */
        grow   = have_g  ? g  : 100;
        shrink = have_sh ? sh : 100;
        basis  = have_ba ? ba : (have_g ? 0 : CSS_LEN_AUTO);
    }
    dst[0].prop = P_FLEX_GROW;   dst[0].ival = grow;
    dst[1].prop = P_FLEX_SHRINK; dst[1].ival = shrink;
    dst[2].prop = P_FLEX_BASIS;  dst[2].ival = basis;
    return 3;
}

/* align-items / align-self / align-content / justify-items keyword. allow_auto is for
 * align-self; allow_dist (space-*) is for align-content. Unknown -> -1 (drop). */
static int interp_align_kw(const char *v, int allow_auto, int allow_dist) {
    if (allow_auto && csel_ci_eq(v, "auto")) return CSS_AK_AUTO;
    if (csel_ci_eq(v, "stretch")) return CSS_AK_STRETCH;
    if (csel_ci_eq(v, "flex-start") || csel_ci_eq(v, "start")) return CSS_AK_START;
    if (csel_ci_eq(v, "flex-end") || csel_ci_eq(v, "end")) return CSS_AK_END;
    if (csel_ci_eq(v, "center")) return CSS_AK_CENTER;
    if (csel_ci_eq(v, "baseline")) return CSS_AK_BASELINE;
    if (allow_dist && csel_ci_eq(v, "space-between")) return CSS_AK_SPACE_BETWEEN;
    if (allow_dist && csel_ci_eq(v, "space-around")) return CSS_AK_SPACE_AROUND;
    if (allow_dist && csel_ci_eq(v, "space-evenly")) return CSS_AK_SPACE_EVENLY;
    return -1;
}

static int interp_flex_direction(const char *v) {
    if (csel_ci_eq(v, "row")) return CSS_FD_ROW;
    if (csel_ci_eq(v, "row-reverse")) return CSS_FD_ROW_REVERSE;
    if (csel_ci_eq(v, "column")) return CSS_FD_COLUMN;
    if (csel_ci_eq(v, "column-reverse")) return CSS_FD_COLUMN_REVERSE;
    return -1;
}

static int interp_flex_wrap(const char *v) {
    if (csel_ci_eq(v, "nowrap")) return CSS_FW_NOWRAP;
    if (csel_ci_eq(v, "wrap")) return CSS_FW_WRAP;
    if (csel_ci_eq(v, "wrap-reverse")) return CSS_FW_WRAP_REVERSE;
    return -1;
}

/* grid-auto-flow: the first row/column axis keyword wins; `dense` ignored. */
static int interp_grid_flow(const char *v) {
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        if (csel_ci_eq(tok, "row")) return CSS_GF_ROW;
        if (csel_ci_eq(tok, "column")) return CSS_GF_COLUMN;
        /* dense / other: skip */
    }
    return -1;
}

/* True if s begins with the NUL-terminated prefix pre (case-insensitive), stopping at
 * the first NUL (no out-of-bounds read past a short s). */
static int starts_with_ci(const char *s, const char *pre) {
    for (; *pre != '\0'; ++s, ++pre)
        if (csel_lower_ch(*s) != csel_lower_ch(*pre)) return 0;
    return 1;
}

/* grid-column / grid-row: only the `span N` form is supported -> N (clamped to
 * [1, CSS_GRID_SPAN_MAX]). Line-number / named-line placement is out of scope (-1). */
static int interp_grid_span(const char *v) {
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    if (!starts_with_ci(p, "span")) return -1;
    p += 4;
    if (*p != ' ' && *p != '\t') return -1;   /* "span" must be followed by a count */
    while (*p == ' ' || *p == '\t') ++p;
    double num;
    const char *end;
    if (!parse_num(p, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    if (*end != '\0') return -1;
    int n = round_clamp(num, 0, CSS_GRID_SPAN_MAX);
    if (n < 1) return -1;
    return n;
}

/* Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from
 * both ends. Returns the trimmed length, or SIZE_MAX if it does not fit dst. */
static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    size_t n = b - a;
    if (n + 1 > cap) return (size_t)-1;
    memcpy(dst, s + a, n);
    dst[n] = '\0';
    return n;
}

/* Strips a trailing "!important" (case-insensitive, with optional whitespace before
 * '!' and between '!' and the keyword) from val, in place. Returns 1 if found. A '!'
 * that does not begin "!important" is left intact (the value will fail to interpret). */
static int strip_important(char *val) {
    size_t len = strlen(val);
    for (size_t i = len; i-- > 0; ) {
        if (val[i] != '!') continue;
        const char *r = val + i + 1;
        while (*r == ' ' || *r == '\t') ++r;
        if (!csel_ci_eq(r, "important")) return 0;   /* a non-!important '!': leave as-is */
        size_t e = i;
        while (e > 0 && (val[e-1] == ' ' || val[e-1] == '\t')) --e;
        val[e] = '\0';
        return 1;
    }
    return 0;
}

/* --- Custom properties (--name: value) + var(--name[, fallback]) ---------------
 *
 * Deliberately simplified: collect_custom_props scans the WHOLE stylesheet text
 * once for `--ident: value` pairs regardless of which rule/selector/@media they
 * appear in (a later occurrence of the same name overwrites an earlier one), into
 * one flat page-global table. This covers the overwhelmingly common
 * `:root { --x: ... }` pattern without needing real cascade-scoped custom
 * properties. resolve_var then substitutes var() references against that table
 * when a declaration's value is interpreted (parse_one_decl), bounded to
 * CSS_VAR_MAX_DEPTH nested lookups so a reference cycle (`--a: var(--a)`) or a
 * long chain fails the declaration instead of recursing/expanding unboundedly. */

/* Scans s[0,n) for `--ident : value ;|}` declarations anywhere in the text. A name
 * is recognised only where it cannot be part of a longer identifier (its preceding
 * character, if any, is not itself an identifier character), so it never matches
 * inside e.g. a longer token. Later occurrences of the same name overwrite earlier
 * ones (last-in-source wins, approximating cascade for the common single-:root
 * case). An overlong name or value (would not fit CSS_TOK_MAX) is dropped, not
 * truncated -- a truncated custom property would silently feed a wrong value to
 * every var() that references it. Bounded to cap entries (extra distinct names are
 * ignored, fail closed, never an overflow). */
static void collect_custom_props(const char *s, size_t n, css_custom_prop *tab,
                                 size_t cap, size_t *ntab) {
    *ntab = 0;
    size_t i = 0;
    while (i < n) {
        if (s[i] == '-' && i + 1 < n && s[i + 1] == '-' &&
            (i == 0 || !csel_ident_ch(s[i - 1]))) {
            size_t j = i + 2;
            while (j < n && csel_ident_ch(s[j])) ++j;
            size_t name_len = j - i;
            size_t k = j;
            while (k < n && (s[k] == ' ' || s[k] == '\t' || s[k] == '\n' || s[k] == '\r')) ++k;
            if (k < n && s[k] == ':' && name_len < CSS_TOK_MAX) {
                size_t v0 = k + 1;
                size_t v = v0;
                while (v < n && s[v] != ';' && s[v] != '}') ++v;
                char namebuf[CSS_TOK_MAX];
                memcpy(namebuf, s + i, name_len);
                namebuf[name_len] = '\0';
                char valbuf[CSS_TOK_MAX];
                size_t vlen = copy_trim(s, v0, v, valbuf, sizeof valbuf);
                if (vlen != (size_t)-1 && vlen > 0) {
                    strip_important(valbuf);
                    size_t slot = *ntab;
                    for (size_t e = 0; e < *ntab; ++e) {
                        if (strcmp(tab[e].name, namebuf) == 0) { slot = e; break; }
                    }
                    if (slot < cap) {
                        memcpy(tab[slot].name, namebuf, name_len + 1);
                        strcpy(tab[slot].value, valbuf);
                        if (slot == *ntab) ++*ntab;
                    }
                }
                i = v;
                continue;
            }
        }
        ++i;
    }
}

static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap,
                           size_t *o, const css_custom_prop *tab, size_t ntab, int depth);

/* Appends s[0,n) to out at *o; fails (0) if it would not fit outcap. */
static int var_append(char *out, size_t outcap, size_t *o, const char *s, size_t n) {
    if (*o + n >= outcap) return 0;
    memcpy(out + *o, s, n);
    *o += n;
    return 1;
}

/* Looks up name ("--ident", NUL-terminated) in tab; on a hit, recursively resolves
 * ITS stored value (which may itself reference var()) into out. Returns 1 on a
 * successful (found and resolved) expansion, 0 if not found or the nested
 * resolution failed/overflowed/exceeded depth. */
static int expand_lookup(const char *name, char *out, size_t outcap, size_t *o,
                         const css_custom_prop *tab, size_t ntab, int depth) {
    if (depth >= CSS_VAR_MAX_DEPTH) return 0;
    for (size_t i = 0; i < ntab; ++i) {
        if (strcmp(tab[i].name, name) == 0)
            return resolve_var_rec(tab[i].value, strlen(tab[i].value), out, outcap, o,
                                   tab, ntab, depth + 1);
    }
    return 0;
}

/* Copies val[0,vlen) to out (via *o), expanding every var(...) call found at the
 * top level (recursively, bounded by depth via expand_lookup). Returns 1 if the
 * whole value was resolved and fit within outcap; 0 on an unresolved var() (no
 * matching custom property and no fallback), a malformed/unbalanced var(...), or
 * an overflow -- the caller (resolve_var) then drops the whole declaration, like
 * any other unsupported value (fail closed, never a partially-substituted value). */
static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap,
                           size_t *o, const css_custom_prop *tab, size_t ntab, int depth) {
    size_t i = 0;
    while (i < vlen) {
        if (i + 4 <= vlen && csel_lower_ch(val[i]) == 'v' && csel_lower_ch(val[i + 1]) == 'a' &&
            csel_lower_ch(val[i + 2]) == 'r' && val[i + 3] == '(') {
            size_t j = i + 4;
            int pdepth = 1;
            size_t argstart = j;
            while (j < vlen && pdepth > 0) {
                if (val[j] == '(') ++pdepth;
                else if (val[j] == ')') { if (--pdepth == 0) break; }
                ++j;
            }
            if (pdepth != 0) return 0;             /* unbalanced var(...): invalid */
            size_t argend = j;
            size_t after = j + 1;                  /* past the matching ')' */

            /* Split the argument on the first TOP-LEVEL comma (a fallback like
             * rgb(1,2,3) must not split there). */
            size_t comma = argend;
            int cd = 0;
            for (size_t k = argstart; k < argend; ++k) {
                if (val[k] == '(') ++cd;
                else if (val[k] == ')') --cd;
                else if (val[k] == ',' && cd == 0) { comma = k; break; }
            }
            size_t na = argstart, nb = comma;
            while (na < nb && (val[na] == ' ' || val[na] == '\t')) ++na;
            while (nb > na && (val[nb - 1] == ' ' || val[nb - 1] == '\t')) --nb;
            size_t nlen = nb - na;
            char namebuf[CSS_TOK_MAX];
            if (nlen == 0 || nlen >= sizeof namebuf ||
                val[na] != '-' || na + 1 >= nb || val[na + 1] != '-')
                return 0;                           /* not a custom-property reference */
            memcpy(namebuf, val + na, nlen);
            namebuf[nlen] = '\0';

            if (!expand_lookup(namebuf, out, outcap, o, tab, ntab, depth)) {
                if (comma >= argend) return 0;      /* unresolved, no fallback: invalid */
                size_t fa = comma + 1, fb = argend;
                while (fa < fb && (val[fa] == ' ' || val[fa] == '\t')) ++fa;
                while (fb > fa && (val[fb - 1] == ' ' || val[fb - 1] == '\t')) --fb;
                if (depth >= CSS_VAR_MAX_DEPTH) return 0;
                if (!resolve_var_rec(val + fa, fb - fa, out, outcap, o, tab, ntab, depth + 1))
                    return 0;
            }
            i = after;
            continue;
        }
        if (!var_append(out, outcap, o, val + i, 1)) return 0;
        ++i;
    }
    return 1;
}

/* Entry point: if val contains no "var(" this is a no-op (caller keeps using val
 * directly); otherwise resolves every var() against tab/ntab into out (bounded to
 * outcap, NUL-terminated). Returns 1 on success, 0 if resolution failed or
 * overflowed (caller drops the declaration). */
static int resolve_var(const char *val, char *out, size_t outcap,
                       const css_custom_prop *tab, size_t ntab) {
    if (outcap == 0) return 0;
    size_t o = 0;
    if (!resolve_var_rec(val, strlen(val), out, outcap - 1, &o, tab, ntab, 0)) return 0;
    out[o] = '\0';
    return 1;
}

/* transform (M1.2, 2D translate only): translate()/translateX()/translateY(),
 * offsets in px via interp_len (allow_auto=0 -- %, viewport units and bare
 * non-calc numbers all fail closed, same as any other box-model length here).
 * Any other transform function (scale/rotate/skew/matrix/perspective), multiple
 * space-separated functions, or unparseable syntax reject the WHOLE declaration
 * (no decl emitted -> cascades as unset, byte-identical to a page that never
 * declared transform at all -- fail closed, never a half-applied transform).
 * rotate/scale/matrix are architecturally deferred: they need real Cairo matrix
 * composition AND transformed hit-testing coordinates, out of scope for this
 * increment (paint position only; see spec/compositor.md and the "fuera de
 * alcance" note there). "none" is not special-cased -- it simply fails the
 * translate*( prefix match below and emits nothing, same net effect (unset). */
static int expand_transform(const char *val, css_decl *dst, int cap) {
    if (cap < 2) return 0;
    const char *p = val;
    while (*p == ' ' || *p == '\t') ++p;

    enum { TR_X, TR_Y, TR_BOTH } kind;
    if (csel_span_eq(p, "translatex(", 11, 1))      { kind = TR_X;    p += 11; }
    else if (csel_span_eq(p, "translatey(", 11, 1)) { kind = TR_Y;    p += 11; }
    else if (csel_span_eq(p, "translate(", 10, 1))  { kind = TR_BOTH; p += 10; }
    else return 0;

    size_t n = strlen(p);
    size_t j = 0;
    int depth = 1;
    while (j < n && depth > 0) {
        if (p[j] == '(') ++depth;
        else if (p[j] == ')') --depth;
        ++j;
    }
    if (depth != 0) return 0;                 /* unbalanced parens */
    size_t argn = j - 1;                       /* [0, argn) is the arg list */
    const char *rest = p + j;
    while (*rest == ' ' || *rest == '\t') ++rest;
    if (*rest != '\0') return 0;               /* trailing junk: v1 allows one function only */

    size_t comma = argn;
    for (size_t k = 0; k < argn; ++k) {
        if (p[k] == ',') { comma = k; break; }
    }
    int has_second = comma < argn;

    char a[CSS_TOK_MAX], b[CSS_TOK_MAX];
    if (copy_trim(p, 0, comma, a, sizeof a) == (size_t)-1 || a[0] == '\0') return 0;
    if (has_second &&
        (copy_trim(p, comma + 1, argn, b, sizeof b) == (size_t)-1 || b[0] == '\0'))
        return 0;

    /* Emit only the axis/axes this function actually specifies: translateX/Y are
     * single-axis (the OTHER axis must stay CSS_LEN_UNSET, not become an implicit
     * 0 -- a `<div>` with only translateX() must not also pick up a phantom
     * translateY(0) declaration that shadows a separately-cascaded translateY).
     * translate(x) alone DOES mean translate(x, 0) per spec, so TR_BOTH always
     * emits both slots. */
    int tx, ty;
    if (kind == TR_X) {
        if (has_second || !interp_len(a, 0, &tx)) return 0;
        dst[0].prop = P_TRANSFORM_TX; dst[0].ival = tx;
        return 1;
    }
    if (kind == TR_Y) {
        if (has_second || !interp_len(a, 0, &ty)) return 0;
        dst[0].prop = P_TRANSFORM_TY; dst[0].ival = ty;
        return 1;
    }
    ty = 0;
    if (!interp_len(a, 0, &tx)) return 0;
    if (has_second && !interp_len(b, 0, &ty)) return 0;
    dst[0].prop = P_TRANSFORM_TX; dst[0].ival = tx;
    dst[1].prop = P_TRANSFORM_TY; dst[1].ival = ty;
    return 2;
}

/* gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both
 * axes; row-gap stays unset and falls back to gap downstream), two values are
 * `<row> <col>` (row feeds row-gap, col feeds gap). column-gap stays a
 * single-value longhand in the dispatch below. */
static int expand_gap(const char *val, css_decl *dst, int cap) {
    char a[CSS_TOK_MAX], b[CSS_TOK_MAX], extra[CSS_TOK_MAX];
    const char *p = val;
    if (!next_ws_token(&p, a, sizeof a)) return 0;
    int has_b = next_ws_token(&p, b, sizeof b);
    if (has_b && next_ws_token(&p, extra, sizeof extra)) return 0;
    int ga = interp_gap(a);
    if (ga < 0 || cap < 1) return 0;
    if (!has_b) { dst[0].prop = P_GAP; dst[0].ival = ga; return 1; }
    int gb = interp_gap(b);
    if (gb < 0 || cap < 2) return 0;
    dst[0].prop = P_ROW_GAP; dst[0].ival = ga;
    dst[1].prop = P_GAP;     dst[1].ival = gb;
    return 2;
}

/* place-items / place-content / place-self (2026-07-10): `<align> [<justify>]`,
 * the justify half defaulting to the align token. place-content's justify half
 * feeds justify-content (its own keyword set). place-self's justify half has no
 * engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An uninterpretable align token (or, where a slot exists, an
 * uninterpretable justify token) drops the whole shorthand (fail closed). */
static int expand_place(const char *prop, const char *val, css_decl *dst, int cap) {
    char a[CSS_TOK_MAX], b[CSS_TOK_MAX], extra[CSS_TOK_MAX];
    const char *p = val;
    if (!next_ws_token(&p, a, sizeof a)) return 0;
    int has_b = next_ws_token(&p, b, sizeof b);
    if (has_b && next_ws_token(&p, extra, sizeof extra)) return 0;

    if (strcmp(prop, "place-self") == 0) {
        int av = interp_align_kw(a, 1, 0);
        if (av < 0 || cap < 1) return 0;
        dst[0].prop = P_ALIGN_SELF; dst[0].ival = av;
        return 1;
    }
    if (strcmp(prop, "place-items") == 0) {
        int av = interp_align_kw(a, 0, 0);
        int jv = interp_align_kw(has_b ? b : a, 0, 0);
        if (av < 0 || jv < 0 || cap < 2) return 0;
        dst[0].prop = P_ALIGN_ITEMS;   dst[0].ival = av;
        dst[1].prop = P_JUSTIFY_ITEMS; dst[1].ival = jv;
        return 2;
    }
    int av = interp_align_kw(a, 0, 1);
    int jv = interp_justify(has_b ? b : a);
    if (av < 0 || jv < 0 || cap < 2) return 0;
    dst[0].prop = P_ALIGN_CONTENT; dst[0].ival = av;
    dst[1].prop = P_JUSTIFY;       dst[1].ival = jv;
    return 2;
}

/* font shorthand (2026-07-10): `[style|variant|weight|normal]* size[/line-height]
 * family...`. size and family are both required (per CSS); system keywords
 * (`font: caption` etc.) have no size token and drop the whole shorthand (fail
 * closed). Unmentioned longhands stay unset -- this cascade has no
 * reset-to-initial, a documented simplification. A family that maps to no
 * generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand dropping an unknown name). */
static int expand_font(const char *val, css_decl *dst, int cap) {
    const char *p = val;
    char tok[CSS_TOK_MAX];
    int style = -1, weight = -1, variant = -1;

    for (;;) {
        const char *save = p;
        if (!next_ws_token(&p, tok, sizeof tok)) return 0;  /* ran out: no size */
        if (csel_ci_eq(tok, "normal")) continue;  /* ambiguous reset: leave unset */
        if (csel_ci_eq(tok, "italic") || csel_ci_eq(tok, "oblique")) { style = 1; continue; }
        if (csel_ci_eq(tok, "small-caps")) { variant = CSS_FV_SMALL_CAPS; continue; }
        if (csel_ci_eq(tok, "bold") || csel_ci_eq(tok, "bolder")) { weight = 1; continue; }
        if (csel_ci_eq(tok, "lighter")) { weight = 0; continue; }
        {   /* a bare 100..900 number is a weight (a size always carries a unit) */
            const char *q = tok;
            int all_digits = (*q != '\0');
            while (*q != '\0') { if (*q < '0' || *q > '9') { all_digits = 0; break; } ++q; }
            if (all_digits) {
                int w = interp_weight(tok);
                if (w >= 0) { weight = w; continue; }
            }
        }
        p = save;   /* not a leading keyword: must be the size token */
        break;
    }

    if (!next_ws_token(&p, tok, sizeof tok)) return 0;
    int line = 0;
    char *slash = strchr(tok, '/');
    if (slash != NULL) *slash = '\0';
    int size = interp_fontsize(tok);
    if (size < 0) return 0;
    if (slash != NULL) {
        line = interp_lineheight(slash + 1);
        if (line < 0) return 0;   /* a present but invalid line-height: all invalid */
    }

    while (*p == ' ' || *p == '\t') ++p;
    if (*p == '\0') return 0;     /* family required */
    int fam = interp_fontfamily(p);

    int n = 0;
    if (cap < 6) return 0;
    if (style >= 0)   { dst[n].prop = P_STYLE;        dst[n].ival = style;   ++n; }
    if (weight >= 0)  { dst[n].prop = P_WEIGHT;       dst[n].ival = weight;  ++n; }
    if (variant >= 0) { dst[n].prop = P_FONT_VARIANT; dst[n].ival = variant; ++n; }
    dst[n].prop = P_FONTSIZE; dst[n].ival = size; ++n;
    if (line > 0)     { dst[n].prop = P_LINEHEIGHT;   dst[n].ival = line;    ++n; }
    if (fam > 0)      { dst[n].prop = P_FONTFAMILY;   dst[n].ival = fam;     ++n; }
    return n;
}

/* Maps property name `prop` (lowercased) + value `val` to css_decl(s) in dst (up to
 * cap). Returns the number written (0 if unsupported). Most properties emit one; the
 * margin/padding shorthands expand to up to four (one per side). The important flag is
 * left to the caller (parse_one_decl stamps it). */
static int interpret_prop(const char *prop, const char *val, css_decl *dst, int cap) {
    /* Box model: margins allow 'auto' and negatives; padding/width neither. The
     * shorthands expand; the longhands and width/max-width emit one. */
    if (strcmp(prop, "margin") == 0)  return expand_box4(val, P_MARGIN_TOP, 1, 1, dst, cap);
    if (strcmp(prop, "padding") == 0) return expand_box4(val, P_PAD_TOP, 0, 0, dst, cap);
    if (strcmp(prop, "margin-top") == 0)     return emit_len(dst, cap, P_MARGIN_TOP, val, 1, 1);
    if (strcmp(prop, "margin-right") == 0)   return emit_len(dst, cap, P_MARGIN_RIGHT, val, 1, 1);
    if (strcmp(prop, "margin-bottom") == 0)  return emit_len(dst, cap, P_MARGIN_BOTTOM, val, 1, 1);
    if (strcmp(prop, "margin-left") == 0)    return emit_len(dst, cap, P_MARGIN_LEFT, val, 1, 1);
    if (strcmp(prop, "padding-top") == 0)    return emit_len(dst, cap, P_PAD_TOP, val, 0, 0);
    if (strcmp(prop, "padding-right") == 0)  return emit_len(dst, cap, P_PAD_RIGHT, val, 0, 0);
    if (strcmp(prop, "padding-bottom") == 0) return emit_len(dst, cap, P_PAD_BOTTOM, val, 0, 0);
    if (strcmp(prop, "padding-left") == 0)   return emit_len(dst, cap, P_PAD_LEFT, val, 0, 0);
    /* width/max-width: px path first; a % value is carried symbolically (Hito 32). */
    if (strcmp(prop, "width") == 0)
        return emit_len(dst, cap, P_WIDTH, val, 0, 0)
            || emit_pct(dst, cap, P_WIDTH_PCT, val);
    if (strcmp(prop, "max-width") == 0)
        return emit_len(dst, cap, P_MAXWIDTH, val, 0, 0)
            || emit_pct(dst, cap, P_MAXWIDTH_PCT, val);
    if (strcmp(prop, "min-width") == 0) return emit_len(dst, cap, P_MINWIDTH, val, 0, 0);
    if (strcmp(prop, "height") == 0)    return emit_len(dst, cap, P_HEIGHT, val, 0, 0);
    if (strcmp(prop, "min-height") == 0)return emit_len(dst, cap, P_MINHEIGHT, val, 0, 0);
    if (strcmp(prop, "max-height") == 0)return emit_len(dst, cap, P_MAXHEIGHT, val, 0, 0);

    /* Logical properties (2026-07-10): physical horizontal-tb LTR mapping (the
     * engine has no writing-mode, and the cascade interprets values before it
     * knows the element's resolved direction -- see spec/css.md). */
    if (strcmp(prop, "margin-inline-start") == 0)  return emit_len(dst, cap, P_MARGIN_LEFT, val, 1, 1);
    if (strcmp(prop, "margin-inline-end") == 0)    return emit_len(dst, cap, P_MARGIN_RIGHT, val, 1, 1);
    if (strcmp(prop, "margin-block-start") == 0)   return emit_len(dst, cap, P_MARGIN_TOP, val, 1, 1);
    if (strcmp(prop, "margin-block-end") == 0)     return emit_len(dst, cap, P_MARGIN_BOTTOM, val, 1, 1);
    if (strcmp(prop, "margin-inline") == 0)  return expand_box2(val, P_MARGIN_LEFT, P_MARGIN_RIGHT, 1, 1, dst, cap);
    if (strcmp(prop, "margin-block") == 0)   return expand_box2(val, P_MARGIN_TOP, P_MARGIN_BOTTOM, 1, 1, dst, cap);
    if (strcmp(prop, "padding-inline-start") == 0) return emit_len(dst, cap, P_PAD_LEFT, val, 0, 0);
    if (strcmp(prop, "padding-inline-end") == 0)   return emit_len(dst, cap, P_PAD_RIGHT, val, 0, 0);
    if (strcmp(prop, "padding-block-start") == 0)  return emit_len(dst, cap, P_PAD_TOP, val, 0, 0);
    if (strcmp(prop, "padding-block-end") == 0)    return emit_len(dst, cap, P_PAD_BOTTOM, val, 0, 0);
    if (strcmp(prop, "padding-inline") == 0) return expand_box2(val, P_PAD_LEFT, P_PAD_RIGHT, 0, 0, dst, cap);
    if (strcmp(prop, "padding-block") == 0)  return expand_box2(val, P_PAD_TOP, P_PAD_BOTTOM, 0, 0, dst, cap);
    if (strcmp(prop, "inset-inline-start") == 0)   return emit_len(dst, cap, P_INSET_LEFT, val, 1, 1);
    if (strcmp(prop, "inset-inline-end") == 0)     return emit_len(dst, cap, P_INSET_RIGHT, val, 1, 1);
    if (strcmp(prop, "inset-block-start") == 0)    return emit_len(dst, cap, P_INSET_TOP, val, 1, 1);
    if (strcmp(prop, "inset-block-end") == 0)      return emit_len(dst, cap, P_INSET_BOTTOM, val, 1, 1);
    if (strcmp(prop, "inset-inline") == 0)   return expand_box2(val, P_INSET_LEFT, P_INSET_RIGHT, 1, 1, dst, cap);
    if (strcmp(prop, "inset-block") == 0)    return expand_box2(val, P_INSET_TOP, P_INSET_BOTTOM, 1, 1, dst, cap);
    if (strcmp(prop, "inline-size") == 0)
        return emit_len(dst, cap, P_WIDTH, val, 0, 0)
            || emit_pct(dst, cap, P_WIDTH_PCT, val);
    if (strcmp(prop, "block-size") == 0)      return emit_len(dst, cap, P_HEIGHT, val, 0, 0);
    if (strcmp(prop, "min-inline-size") == 0) return emit_len(dst, cap, P_MINWIDTH, val, 0, 0);
    if (strcmp(prop, "max-inline-size") == 0)
        return emit_len(dst, cap, P_MAXWIDTH, val, 0, 0)
            || emit_pct(dst, cap, P_MAXWIDTH_PCT, val);
    if (strcmp(prop, "min-block-size") == 0)  return emit_len(dst, cap, P_MINHEIGHT, val, 0, 0);
    if (strcmp(prop, "max-block-size") == 0)  return emit_len(dst, cap, P_MAXHEIGHT, val, 0, 0);

    /* Multi-slot shorthands (2026-07-10): two-value gap, place-*, font. */
    if (strcmp(prop, "gap") == 0 || strcmp(prop, "grid-gap") == 0)
        return expand_gap(val, dst, cap);
    if (strcmp(prop, "place-items") == 0 || strcmp(prop, "place-content") == 0 ||
        strcmp(prop, "place-self") == 0)
        return expand_place(prop, val, dst, cap);
    if (strcmp(prop, "font") == 0) return expand_font(val, dst, cap);
    if (strcmp(prop, "transform") == 0) return expand_transform(val, dst, cap);

    /* Text-presentation extensions whose value may legitimately be 0 or negative
     * (so they bypass the generic ival<0 drop, like the box-model lengths). */
    if (strcmp(prop, "text-shadow") == 0)    return expand_shadow(val, dst, cap);
    if (strcmp(prop, "letter-spacing") == 0) return emit_spacing(dst, cap, P_LETTERSPACING, val);
    if (strcmp(prop, "word-spacing") == 0)   return emit_spacing(dst, cap, P_WORDSPACING, val);
    if (strcmp(prop, "text-indent") == 0)    return emit_len(dst, cap, P_TEXTINDENT, val, 0, 1);

    /* Layout box properties whose value may be negative or a sentinel (insets allow
     * auto + negatives; z-index/order are signed; flex-basis can be auto), or which
     * expand to several slots (border / box-shadow / outline / flex). */
    if (strcmp(prop, "top") == 0)     return emit_len(dst, cap, P_INSET_TOP, val, 1, 1);
    if (strcmp(prop, "right") == 0)   return emit_len(dst, cap, P_INSET_RIGHT, val, 1, 1);
    if (strcmp(prop, "bottom") == 0)  return emit_len(dst, cap, P_INSET_BOTTOM, val, 1, 1);
    if (strcmp(prop, "left") == 0)    return emit_len(dst, cap, P_INSET_LEFT, val, 1, 1);
    if (strcmp(prop, "inset") == 0)   return expand_box4(val, P_INSET_TOP, 1, 1, dst, cap);
    if (strcmp(prop, "z-index") == 0) {
        int o;
        if (cap < 1 || !interp_int(val, &o)) return 0;
        dst[0].prop = P_ZINDEX; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "order") == 0) {
        int o;
        if (cap < 1 || !interp_int(val, &o)) return 0;
        dst[0].prop = P_ORDER; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "flex-basis") == 0) {
        int o;
        if (cap < 1 || !interp_flex_basis(val, &o)) return 0;
        dst[0].prop = P_FLEX_BASIS; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "flex") == 0)         return expand_flex(val, dst, cap);
    if (strcmp(prop, "border") == 0)        return expand_border_shorthand(val, 0xF, dst, cap);
    if (strcmp(prop, "border-top") == 0)    return expand_border_shorthand(val, 0x1, dst, cap);
    if (strcmp(prop, "border-right") == 0)  return expand_border_shorthand(val, 0x2, dst, cap);
    if (strcmp(prop, "border-bottom") == 0) return expand_border_shorthand(val, 0x4, dst, cap);
    if (strcmp(prop, "border-left") == 0)   return expand_border_shorthand(val, 0x8, dst, cap);
    if (strcmp(prop, "border-width") == 0)  return expand_quad(val, P_BW_TOP, interp_bw_tok, dst, cap);
    if (strcmp(prop, "border-style") == 0)  return expand_quad(val, P_BS_TOP, interp_bs_tok, dst, cap);
    if (strcmp(prop, "border-color") == 0)  return expand_quad(val, P_BC_TOP, interp_bc_tok, dst, cap);
    if (strcmp(prop, "box-shadow") == 0)    return expand_box_shadow(val, dst, cap);
    if (strcmp(prop, "outline") == 0)       return expand_outline(val, dst, cap);
    if (strcmp(prop, "outline-offset") == 0) return emit_len(dst, cap, P_OUTLINE_OFFSET, val, 0, 1);
    if (strcmp(prop, "outline-width") == 0) {
        int o = interp_bwidth1(val);
        if (o < 0) return 0;
        dst[0].prop = P_OUTLINE_W; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "outline-style") == 0) {
        int o = interp_border_style(val);
        if (o < 0) return 0;
        dst[0].prop = P_OUTLINE_S; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "outline-color") == 0) {
        int o = interp_color(val);
        if (o < 0) return 0;
        dst[0].prop = P_OUTLINE_C; dst[0].ival = o; return 1;
    }
    if (strcmp(prop, "overflow") == 0)      return expand_overflow(val, dst, cap);
    if (strcmp(prop, "background") == 0)       return expand_background(val, dst, cap);
    if (strcmp(prop, "background-image") == 0) return expand_bg_image(val, dst, cap);
    if (strcmp(prop, "grid-template-columns") == 0)
        return expand_grid_template_cols(val, dst, cap);

    int prop_id, ival;
    if (strcmp(prop, "color") == 0)                 { prop_id = P_COLOR;    ival = interp_color(val); }
    else if (strcmp(prop, "background-color") == 0)  { prop_id = P_BG;       ival = interp_bg(val); }
    else if (strcmp(prop, "text-align") == 0)        { prop_id = P_ALIGN;    ival = interp_align(val); }
    else if (strcmp(prop, "font-size") == 0)         { prop_id = P_FONTSIZE; ival = interp_fontsize(val); }
    else if (strcmp(prop, "line-height") == 0)       { prop_id = P_LINEHEIGHT; ival = interp_lineheight(val); }
    else if (strcmp(prop, "font-weight") == 0)       { prop_id = P_WEIGHT;   ival = interp_weight(val); }
    else if (strcmp(prop, "font-style") == 0)        { prop_id = P_STYLE;    ival = interp_style(val); }
    else if (strcmp(prop, "text-decoration") == 0 ||
             strcmp(prop, "text-decoration-line") == 0) { prop_id = P_TEXTDECO; ival = interp_textdeco(val); }
    else if (strcmp(prop, "text-decoration-color") == 0) { prop_id = P_TEXTDECO_COLOR; ival = interp_color(val); }
    else if (strcmp(prop, "text-decoration-style") == 0) { prop_id = P_TEXTDECO_STYLE; ival = interp_textdeco_style(val); }
    else if (strcmp(prop, "text-decoration-thickness") == 0) { prop_id = P_TEXTDECO_THICKNESS; ival = interp_textdeco_thickness(val); }
    /* aspect-ratio emits TWO property-value pairs (num + den) so the cascade can
     * keep them in lock-step; the only caller that drops > 1 decl (var() in
     * shorthand expansion) sees the same order in parse_one_decl's fall-through. */
    else if (strcmp(prop, "aspect-ratio") == 0) {
        int num, den;
        interp_aspect_ratio(val, &num, &den);
        if (cap < 2) return 0;
        dst[0].prop = P_ASPECT_NUM; dst[0].ival = num;
        dst[1].prop = P_ASPECT_DEN; dst[1].ival = den;
        return 2;
    }
    else if (strcmp(prop, "display") == 0)           { prop_id = P_DISPLAY;  ival = interp_display(val); }
    else if (strcmp(prop, "column-gap") == 0)         { prop_id = P_GAP;      ival = interp_gap(val); }
    else if (strcmp(prop, "justify-content") == 0)    { prop_id = P_JUSTIFY;  ival = interp_justify(val); }
    else if (strcmp(prop, "font-family") == 0)        { prop_id = P_FONTFAMILY;    ival = interp_fontfamily(val); }
    else if (strcmp(prop, "text-transform") == 0)     { prop_id = P_TEXTTRANSFORM; ival = interp_texttransform(val); }
    else if (strcmp(prop, "opacity") == 0)            { prop_id = P_OPACITY;       ival = interp_opacity(val); }
    else if (strcmp(prop, "vertical-align") == 0)     { prop_id = P_VALIGN;        ival = interp_valign(val); }
    else if (strcmp(prop, "white-space") == 0)        { prop_id = P_WHITESPACE;    ival = interp_whitespace(val); }
    else if (strcmp(prop, "tab-size") == 0)            { prop_id = P_TABSIZE;       ival = interp_tabsize(val); }
    else if (strcmp(prop, "direction") == 0)           { prop_id = P_DIRECTION;     ival = interp_direction(val); }
    else if (strcmp(prop, "list-style-type") == 0 ||
             strcmp(prop, "list-style") == 0)          { prop_id = P_LISTSTYLE;     ival = interp_liststyle(val); }
    else if (strcmp(prop, "position") == 0)            { prop_id = P_POSITION;      ival = interp_position(val); }
    else if (strcmp(prop, "box-sizing") == 0)          { prop_id = P_BOXSIZING;     ival = interp_boxsizing(val); }
    else if (strcmp(prop, "border-radius") == 0)       { prop_id = P_BORDER_RADIUS; ival = interp_border_radius(val); }
    else if (strcmp(prop, "border-top-width") == 0)    { prop_id = P_BW_TOP;        ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-right-width") == 0)  { prop_id = P_BW_RIGHT;      ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-bottom-width") == 0) { prop_id = P_BW_BOTTOM;     ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-left-width") == 0)   { prop_id = P_BW_LEFT;       ival = interp_bwidth1(val); }
    else if (strcmp(prop, "border-top-style") == 0)    { prop_id = P_BS_TOP;        ival = interp_border_style(val); }
    else if (strcmp(prop, "border-right-style") == 0)  { prop_id = P_BS_RIGHT;      ival = interp_border_style(val); }
    else if (strcmp(prop, "border-bottom-style") == 0) { prop_id = P_BS_BOTTOM;     ival = interp_border_style(val); }
    else if (strcmp(prop, "border-left-style") == 0)   { prop_id = P_BS_LEFT;       ival = interp_border_style(val); }
    else if (strcmp(prop, "border-top-color") == 0)    { prop_id = P_BC_TOP;        ival = interp_color(val); }
    else if (strcmp(prop, "border-right-color") == 0)  { prop_id = P_BC_RIGHT;      ival = interp_color(val); }
    else if (strcmp(prop, "border-bottom-color") == 0) { prop_id = P_BC_BOTTOM;     ival = interp_color(val); }
    else if (strcmp(prop, "border-left-color") == 0)   { prop_id = P_BC_LEFT;       ival = interp_color(val); }
    else if (strcmp(prop, "flex-grow") == 0)           { prop_id = P_FLEX_GROW;     ival = interp_flex_factor(val); }
    else if (strcmp(prop, "flex-shrink") == 0)         { prop_id = P_FLEX_SHRINK;   ival = interp_flex_factor(val); }
    else if (strcmp(prop, "align-items") == 0)         { prop_id = P_ALIGN_ITEMS;   ival = interp_align_kw(val, 0, 0); }
    else if (strcmp(prop, "align-self") == 0)          { prop_id = P_ALIGN_SELF;    ival = interp_align_kw(val, 1, 0); }
    else if (strcmp(prop, "align-content") == 0)       { prop_id = P_ALIGN_CONTENT; ival = interp_align_kw(val, 0, 1); }
    else if (strcmp(prop, "justify-items") == 0)       { prop_id = P_JUSTIFY_ITEMS; ival = interp_align_kw(val, 0, 0); }
    else if (strcmp(prop, "flex-direction") == 0)      { prop_id = P_FLEX_DIR;      ival = interp_flex_direction(val); }
    else if (strcmp(prop, "flex-wrap") == 0)           { prop_id = P_FLEX_WRAP;     ival = interp_flex_wrap(val); }
    else if (strcmp(prop, "grid-template-rows") == 0)  { prop_id = P_GRID_ROWS;     ival = interp_gridcols(val); }
    else if (strcmp(prop, "row-gap") == 0)             { prop_id = P_ROW_GAP;       ival = interp_gap(val); }
    else if (strcmp(prop, "grid-auto-flow") == 0)      { prop_id = P_GRID_FLOW;     ival = interp_grid_flow(val); }
    else if (strcmp(prop, "grid-column") == 0)         { prop_id = P_GRID_COL_SPAN; ival = interp_grid_span(val); }
    else if (strcmp(prop, "grid-row") == 0)            { prop_id = P_GRID_ROW_SPAN; ival = interp_grid_span(val); }
    else if (strcmp(prop, "float") == 0)               { prop_id = P_FLOAT;         ival = interp_float(val); }
    else if (strcmp(prop, "clear") == 0)               { prop_id = P_CLEAR;         ival = interp_clear(val); }
    else if (strcmp(prop, "visibility") == 0)          { prop_id = P_VISIBILITY;    ival = interp_visibility(val); }
    else if (strcmp(prop, "overflow-x") == 0)          { prop_id = P_OVERFLOW_X;    ival = interp_overflow(val); }
    else if (strcmp(prop, "overflow-y") == 0)          { prop_id = P_OVERFLOW_Y;    ival = interp_overflow(val); }
    else if (strcmp(prop, "cursor") == 0)              { prop_id = P_CURSOR;        ival = interp_cursor(val); }
    else if (strcmp(prop, "text-overflow") == 0)       { prop_id = P_TEXT_OVERFLOW; ival = interp_text_overflow(val); }
    else if (strcmp(prop, "word-break") == 0)          { prop_id = P_WORD_BREAK;    ival = interp_word_break(val); }
    else if (strcmp(prop, "overflow-wrap") == 0 ||
             strcmp(prop, "word-wrap") == 0)            { prop_id = P_WORD_BREAK;    ival = interp_overflow_wrap(val); }
    else if (strcmp(prop, "border-collapse") == 0)      { prop_id = P_BORDER_COLLAPSE; ival = interp_border_collapse(val); }
    else if (strcmp(prop, "border-spacing") == 0)       { prop_id = P_BORDER_SPACING;  ival = interp_border_spacing(val); }
    else if (strcmp(prop, "empty-cells") == 0)           { prop_id = P_EMPTY_CELLS;     ival = interp_empty_cells(val); }
    else if (strcmp(prop, "caption-side") == 0)          { prop_id = P_CAPTION_SIDE;    ival = interp_caption_side(val); }
    else if (strcmp(prop, "table-layout") == 0)          { prop_id = P_TABLE_LAYOUT;    ival = interp_table_layout(val); }
    else if (strcmp(prop, "font-variant") == 0)          { prop_id = P_FONT_VARIANT;    ival = interp_font_variant(val); }
    else if (strcmp(prop, "hyphens") == 0)               { prop_id = P_HYPHENS;         ival = interp_hyphens(val); }
    else if (strcmp(prop, "user-select") == 0)           { prop_id = P_USER_SELECT;     ival = interp_user_select(val); }
    else if (strcmp(prop, "caret-color") == 0) {
        int o = interp_caret_color(val);
        if (o != CSS_LEN_AUTO && o < 0) return 0;
        dst[0].prop = P_CARET_COLOR; dst[0].ival = o; return 1;
    }
    else if (strcmp(prop, "appearance") == 0)            { prop_id = P_APPEARANCE;      ival = interp_appearance(val); }
    else if (strcmp(prop, "pointer-events") == 0)        { prop_id = P_POINTER_EVENTS;  ival = interp_pointer_events(val); }
    else if (strcmp(prop, "background-repeat") == 0)    { prop_id = P_BG_REPEAT;     ival = interp_bg_repeat(val); }
    else if (strcmp(prop, "background-size") == 0)      { prop_id = P_BG_SIZE;       ival = interp_bg_size(val); }
    else if (strcmp(prop, "background-clip") == 0)      { prop_id = P_BG_CLIP;       ival = interp_bg_clip(val); }
    else if (strcmp(prop, "background-origin") == 0)    { prop_id = P_BG_ORIGIN;     ival = interp_bg_origin(val); }
    else if (strcmp(prop, "background-attachment") == 0){ prop_id = P_BG_ATTACHMENT; ival = interp_bg_attachment(val); }
    else if (strcmp(prop, "isolation") == 0)            { prop_id = P_ISOLATION;     ival = interp_isolation(val); }
    else if (strcmp(prop, "contain") == 0)              { prop_id = P_CONTAIN;       ival = interp_contain(val); }
    else if (strcmp(prop, "content-visibility") == 0)   { prop_id = P_CONTENT_VISIBILITY; ival = interp_content_visibility(val); }
    else if (strcmp(prop, "image-rendering") == 0)      { prop_id = P_IMAGE_RENDERING;    ival = interp_image_rendering(val); }
    else if (strcmp(prop, "color-scheme") == 0)         { prop_id = P_COLOR_SCHEME;       ival = interp_color_scheme(val); }
    else if (strcmp(prop, "accent-color") == 0) {
        int o = interp_accent_color(val);
        if (o != CSS_LEN_AUTO && o < 0) return 0;
        dst[0].prop = P_ACCENT_COLOR; dst[0].ival = o; return 1;
    }
    else if (strcmp(prop, "print-color-adjust") == 0)   { prop_id = P_PRINT_COLOR_ADJUST;   ival = interp_print_color_adjust(val); }
    else if (strcmp(prop, "forced-color-adjust") == 0)  { prop_id = P_FORCED_COLOR_ADJUST;  ival = interp_forced_color_adjust(val); }
    else if (strcmp(prop, "mix-blend-mode") == 0)       { prop_id = P_MIX_BLEND_MODE;   ival = interp_mix_blend_mode(val); }
    else if (strcmp(prop, "object-fit") == 0)           { prop_id = P_OBJECT_FIT;       ival = interp_object_fit(val); }
    else if (strcmp(prop, "list-style-position") == 0)  { prop_id = P_LIST_STYLE_POS;   ival = interp_list_style_pos(val); }
    else if (strcmp(prop, "font-kerning") == 0)         { prop_id = P_FONT_KERNING;     ival = interp_font_kerning(val); }
    else if (strcmp(prop, "text-rendering") == 0)       { prop_id = P_TEXT_RENDERING;   ival = interp_text_rendering(val); }
    else if (strcmp(prop, "font-stretch") == 0)         { prop_id = P_FONT_STRETCH;     ival = interp_font_stretch(val); }
    else if (strcmp(prop, "resize") == 0)               { prop_id = P_RESIZE;           ival = interp_resize(val); }
    else if (strcmp(prop, "scroll-behavior") == 0)      { prop_id = P_SCROLL_BEHAVIOR;  ival = interp_scroll_behavior(val); }
    else if (strcmp(prop, "touch-action") == 0)         { prop_id = P_TOUCH_ACTION;     ival = interp_touch_action(val); }
    else if (strcmp(prop, "overscroll-behavior") == 0)  { prop_id = P_OVERSCROLL_BEHAVIOR; ival = interp_overscroll_behavior(val); }
    else if (strcmp(prop, "backface-visibility") == 0)  { prop_id = P_BACKFACE_VISIBILITY; ival = interp_backface_visibility(val); }
    else return 0;

    if (ival < 0) return 0;  /* unsupported value */
    dst[0].prop = prop_id;
    dst[0].ival = ival;
    return 1;
}

/* Interprets one declaration span s[0,n) into dst (up to cap). Returns the number of
 * css_decl written (0 if unsupported). Splits `prop: value`, strips a trailing
 * `!important` (stamping every emitted decl), resolves any var() reference against
 * tab/ntab (a custom-property declaration itself, `--name: ...`, is not a real
 * property and falls through interpret_prop's unknown-property path unchanged),
 * then dispatches on the property. */
static int parse_one_decl(const char *s, size_t n, css_decl *dst, int cap,
                          const css_custom_prop *tab, size_t ntab) {
    if (cap < 1) return 0;
    size_t c = 0;
    while (c < n && s[c] != ':') ++c;
    if (c >= n) return 0;  /* no colon */

    char prop[CSS_TOK_MAX];
    char val[CSS_TOK_MAX];
    if (copy_trim(s, 0, c, prop, sizeof prop) == (size_t)-1) return 0;
    if (copy_trim(s, c + 1, n, val, sizeof val) == (size_t)-1) return 0;
    if (prop[0] == '\0' || val[0] == '\0') return 0;
    for (char *p = prop; *p != '\0'; ++p) *p = csel_lower_ch(*p);

    int important = strip_important(val);
    if (val[0] == '\0') return 0;  /* bare "!important" with no value */

    const char *use_val = val;
    char resolved[CSS_TOK_MAX];
    if (csel_substr(val, "var(", 1)) {
        if (!resolve_var(val, resolved, sizeof resolved, tab, ntab)) return 0;
        use_val = resolved;
    }

    int nw = interpret_prop(prop, use_val, dst, cap);
    for (int i = 0; i < nw; ++i) dst[i].important = important;
    return nw;
}

/* Splits a ';'-separated declaration block into dst (up to cap). Returns count.
 * tab/ntab is the custom-property table var() resolves against (NULL/0 when none,
 * e.g. an inline style resolved against a NULL sheet). */
static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
                              const css_custom_prop *tab, size_t ntab) {
    size_t count = 0, i = 0;
    while (i < n && count < cap) {
        size_t j = i;
        while (j < n && s[j] != ';') ++j;
        count += (size_t)parse_one_decl(s + i, j - i, &dst[count], (int)(cap - count), tab, ntab);
        i = (j < n) ? j + 1 : j;
    }
    return count;
}

/* Adds a rule: selector list s[ss,se), declaration block s[ds,de). */
static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     size_t ds, size_t de) {
    css_sel tmp[CSS_SELS_PER_GROUP];
    int got = 0;
    size_t i = ss;
    while (i < se && got < CSS_SELS_PER_GROUP) {
        size_t j = i;
        while (j < se && s[j] != ',') ++j;
        if (csel_parse(s, i, j, &tmp[got])) ++got;
        i = (j < se) ? j + 1 : j;
    }
    if (got == 0) return;  /* no supported selector: skip the whole rule */

    size_t dstart = sh->ndecls;
    size_t dn = interpret_decls(s + ds, de - ds, &sh->decls[dstart], CSS_MAX_DECLS - dstart,
                                sh->custom, sh->ncustom);
    if (dn == 0) return;
    if (sh->nrules >= CSS_MAX_RULES) return;  /* leave decls; harmless, unreferenced */

    sh->ndecls += dn;
    size_t rule_idx = sh->nrules;
    sh->rules[rule_idx].start = dstart;
    sh->rules[rule_idx].count = dn;
    ++sh->nrules;

    for (int g = 0; g < got && sh->nsels < CSS_MAX_SELS; ++g) {
        css_sel *dst = &sh->sels[sh->nsels];
        *dst = tmp[g];
        dst->rule = (int)rule_idx;
        dst->order = (int)sh->nsels;
        ++sh->nsels;
    }
}

/* Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a
 * brace-balanced block. Returns the index just past it. */
static size_t skip_at_rule(const char *s, size_t i, size_t n) {
    while (i < n && s[i] != ';' && s[i] != '{') ++i;
    if (i < n && s[i] == ';') return i + 1;
    if (i < n && s[i] == '{') {
        int depth = 0;
        while (i < n) {
            if (s[i] == '{') ++depth;
            else if (s[i] == '}') { --depth; ++i; if (depth == 0) return i; continue; }
            ++i;
        }
    }
    return i;
}

/* Index just past the '}' that closes the block whose '{' is at s[open]. n if
 * unbalanced. */
static size_t block_end(const char *s, size_t open, size_t n) {
    int depth = 0;
    for (size_t i = open; i < n; ++i) {
        if (s[i] == '{') ++depth;
        else if (s[i] == '}') { --depth; if (depth == 0) return i + 1; }
    }
    return n;
}

/* --- @media query evaluation (Hito 23b). All inputs are bounded substrings; the
 * query never fetches and unknown features fail closed (do not match). --- */

#define CSS_MEDIA_TOK 128u

/* Leading non-negative integer of a length value ("600px" -> 600), unit ignored. */
static int css_px(const char *v) {
    double d;
    const char *e;
    return parse_num(v, &d, &e) ? round_clamp(d, 0, CSS_LEN_MAX) : 0;
}

/* Trims ASCII spaces/tabs from both ends of a NUL-terminated string, in place. */
static void trim_inplace(char *s) {
    size_t a = 0;
    while (s[a] == ' ' || s[a] == '\t') ++a;
    size_t n = strlen(s + a);
    memmove(s, s + a, n + 1);
    while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\t')) s[--n] = '\0';
}

/* Lowercased, trimmed copy of s[a,b) into dst; SIZE_MAX if it does not fit. */
static size_t copy_lower_trim(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    size_t n = copy_trim(s, a, b, dst, cap);
    if (n == (size_t)-1) return (size_t)-1;
    for (size_t i = 0; i < n; ++i) dst[i] = csel_lower_ch(dst[i]);
    return n;
}

/* One media part: a type word ("screen"/"print"/"all") or a "(feature: value)".
 * p is already lowercased and trimmed. Unknown -> 0 (fail closed). */
static int media_part_matches(const char *p, const css_media *m) {
    if (p[0] == '(') {
        size_t L = strlen(p);
        if (L < 2 || p[L-1] != ')') return 0;
        char inner[CSS_MEDIA_TOK];
        size_t k = 0;
        for (size_t i = 1; i + 1 < L && k + 1 < sizeof inner; ++i) inner[k++] = p[i];
        inner[k] = '\0';
        char *colon = strchr(inner, ':');
        if (colon == NULL) return 0;  /* boolean feature (e.g. "(color)"): fail closed */
        *colon = '\0';
        char *name = inner, *value = colon + 1;
        trim_inplace(name);
        trim_inplace(value);
        if (strcmp(name, "prefers-color-scheme") == 0)
            return (strcmp(value, "dark") == 0)  ? (m->prefers_dark ? 1 : 0)
                 : (strcmp(value, "light") == 0) ? (m->prefers_dark ? 0 : 1) : 0;
        if (strcmp(name, "min-width") == 0) return m->width_px >= css_px(value);
        if (strcmp(name, "max-width") == 0) return m->width_px <= css_px(value);
        return 0;  /* unknown feature: fail closed */
    }
    if (strcmp(p, "all") == 0) return 1;
    if (strcmp(p, "screen") == 0) return m->print ? 0 : 1;
    if (strcmp(p, "print") == 0) return m->print ? 1 : 0;
    return 0;  /* unknown media type: fail closed */
}

/* One media query segment (between commas): an AND of parts. `not`/`or`/unknown
 * fail closed. An empty segment matches (all). */
static int media_segment_matches(const char *s, size_t a, size_t b, const css_media *m) {
    int result = 1, any = 0;
    size_t i = a;
    while (i < b) {
        while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
        if (i >= b) break;
        size_t ts = i;
        char buf[CSS_MEDIA_TOK];
        if (s[i] == '(') {
            int d = 0;
            while (i < b) {
                if (s[i] == '(') ++d;
                else if (s[i] == ')') { ++i; if (--d == 0) break; continue; }
                ++i;
            }
            if (copy_lower_trim(s, ts, i, buf, sizeof buf) == (size_t)-1) return 0;
            if (!media_part_matches(buf, m)) result = 0;
            any = 1;
        } else {
            size_t we = i;
            while (we < b && s[we] != ' ' && s[we] != '\t' && s[we] != '(') ++we;
            if (copy_lower_trim(s, ts, we, buf, sizeof buf) == (size_t)-1) return 0;
            i = we;
            if (strcmp(buf, "and") == 0 || strcmp(buf, "only") == 0) {
                /* connector / legacy keyword: ignore */
            } else if (strcmp(buf, "not") == 0 || strcmp(buf, "or") == 0) {
                return 0;  /* negation / level-4 or: fail closed */
            } else {
                if (!media_part_matches(buf, m)) result = 0;
                any = 1;
            }
        }
    }
    return any ? result : 1;
}

/* A media query list s[a,b): comma-separated segments OR'd together. */
static int media_matches(const char *s, size_t a, size_t b, const css_media *m) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    if (a >= b) return 1;  /* empty query == all */
    size_t i = a;
    while (i < b) {
        size_t seg = i;
        while (i < b && s[i] != ',') ++i;
        if (media_segment_matches(s, seg, i, m)) return 1;
        if (i < b) ++i;
    }
    return 0;
}

/* True when s[i] ('@') begins an "@media" at-rule. */
static int at_is_media(const char *s, size_t i, size_t n) {
    static const char kw[5] = { 'm', 'e', 'd', 'i', 'a' };
    if (i + 6 > n) return 0;
    for (int k = 0; k < 5; ++k) if (csel_lower_ch(s[i + 1 + k]) != kw[k]) return 0;
    size_t j = i + 6;
    return j >= n || s[j] == ' ' || s[j] == '\t' || s[j] == '\n' || s[j] == '\r'
        || s[j] == '{' || s[j] == '(';
}

#define CSS_MEDIA_MAX_DEPTH 4

/* Parses rules in s[start,end). A matched @media block is descended into (bounded
 * depth); @import/@font-face/other @-rules and a non-matching @media are skipped. */
static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                        const css_media *media, int depth) {
    size_t i = start;
    while (i < end) {
        while (i < end && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) ++i;
        if (i >= end) break;
        if (s[i] == '@') {
            if (at_is_media(s, i, end)) {
                size_t q = i + 6;
                while (q < end && s[q] != '{' && s[q] != ';') ++q;
                if (q < end && s[q] == '{') {
                    size_t be = block_end(s, q, end);     /* past the closing '}' */
                    size_t body_start = q + 1;
                    size_t body_end = (be > body_start) ? be - 1 : body_start;
                    if (depth < CSS_MEDIA_MAX_DEPTH && media_matches(s, i + 6, q, media))
                        parse_block(sh, s, body_start, body_end, media, depth + 1);
                    i = be;
                    continue;
                }
                i = (q < end && s[q] == ';') ? q + 1 : end;  /* @media with no block */
                continue;
            }
            i = skip_at_rule(s, i, end);
            continue;
        }
        if (s[i] == '}') { ++i; continue; }  /* stray */

        size_t ss = i;
        while (i < end && s[i] != '{' && s[i] != '}') ++i;
        if (i >= end || s[i] != '{') { if (i < end && s[i] == '}') ++i; continue; }
        size_t se = i;     /* at '{' */
        ++i;
        size_t ds = i;
        while (i < end && s[i] != '}') ++i;
        size_t de = i;     /* at '}' or end */
        if (i < end) ++i;
        add_rule(sh, s, ss, se, ds, de);
    }
}

/* Removes C-style block comments into a fresh NUL-terminated buffer (each comment
 * becomes one space). Caller frees. */
static char *strip_comments(const char *text, size_t len, size_t *outlen) {
    if (len == (size_t)-1) return NULL;
    char *buf = (char *)malloc(len + 1);
    if (buf == NULL) return NULL;
    size_t o = 0, i = 0;
    while (i < len) {
        if (i + 1 < len && text[i] == '/' && text[i+1] == '*') {
            i += 2;
            while (i + 1 < len && !(text[i] == '*' && text[i+1] == '/')) ++i;
            i = (i + 1 < len) ? i + 2 : len;
            buf[o++] = ' ';
        } else {
            buf[o++] = text[i++];
        }
    }
    buf[o] = '\0';
    *outlen = o;
    return buf;
}

css_status css_parse(const char *text, size_t len, css_sheet **out) {
    return css_parse_media(text, len, NULL, out);
}

css_status css_parse_media(const char *text, size_t len, const css_media *media,
                           css_sheet **out) {
    if (out == NULL) return CSS_ERR_NULL_ARG;
    css_sheet *sh = (css_sheet *)calloc(1, sizeof *sh);
    if (sh == NULL) return CSS_ERR_OOM;
    css_media def = { 0, 0, CSS_MEDIA_DEFAULT_WIDTH };  /* screen / light / desktop */
    const css_media *m = (media != NULL) ? media : &def;
    if (text != NULL) {
        if (len == 0) len = strlen(text);
        size_t clen = 0;
        char *clean = strip_comments(text, len, &clen);
        if (clean == NULL) { free(sh); return CSS_ERR_OOM; }
        collect_custom_props(clean, clen, sh->custom, CSS_MAX_CUSTOM_PROPS, &sh->ncustom);
        parse_block(sh, clean, 0, clen, m, 0);
        free(clean);
    }
    *out = sh;
    return CSS_OK;
}

void css_free(css_sheet *s) {
    free(s);
}


/* Applies one declaration to the running style if it wins its property slot. The
 * cascade is two-tiered: an !important declaration beats any non-important one
 * (regardless of specificity); within a tier the higher specificity wins, ties
 * broken by document order. wi/ws/wo track the winning tier/specificity/order so far. */
static void apply_decl(css_style *o, int *wi, int *ws, int *wo, const css_decl *d,
                       int spec, int ord) {
    int slot = d->prop;
    int imp = d->important;
    int win = imp > wi[slot] ||
              (imp == wi[slot] && (spec > ws[slot] || (spec == ws[slot] && ord >= wo[slot])));
    if (win) {
        wi[slot] = imp;
        ws[slot] = spec;
        wo[slot] = ord;
        switch (d->prop) {
            case P_COLOR:    o->color = d->ival; break;
            case P_BG:       o->background = d->ival; break;
            case P_BG_GRAD_ANGLE: o->bg_grad_angle = d->ival; break;
            case P_BG_GRAD_N:     o->bg_grad_n = d->ival; break;
            case P_BG_GRAD_C0: case P_BG_GRAD_C1:
            case P_BG_GRAD_C2: case P_BG_GRAD_C3:
                o->bg_grad_c[d->prop - P_BG_GRAD_C0] = d->ival; break;
            case P_ALIGN:    o->text_align = (css_align)d->ival; break;
            case P_FONTSIZE: o->font_scale = d->ival; break;
            case P_LINEHEIGHT: o->line_scale = d->ival; break;
            case P_WEIGHT:   o->bold = d->ival; break;
            case P_STYLE:    o->italic = d->ival; break;
            case P_TEXTDECO:       o->text_decoration = d->ival; break;
            case P_TEXTDECO_COLOR: o->text_decoration_color = d->ival; break;
            case P_TEXTDECO_STYLE: o->text_decoration_style = d->ival; break;
            case P_DISPLAY:  o->display = (css_display)d->ival; break;
            case P_GAP:      o->gap = d->ival; break;
            case P_JUSTIFY:  o->justify = (css_justify)d->ival; break;
            case P_GRIDCOLS: o->grid_cols = d->ival; break;
            case P_GRID_TRACK0: case P_GRID_TRACK1: case P_GRID_TRACK2:
            case P_GRID_TRACK3: case P_GRID_TRACK4: case P_GRID_TRACK5:
            case P_GRID_TRACK6: case P_GRID_TRACK7:
                o->grid_col_w[d->prop - P_GRID_TRACK0] = d->ival; break;
            case P_MARGIN_TOP:    o->margin_top = d->ival; break;
            case P_MARGIN_RIGHT:  o->margin_right = d->ival; break;
            case P_MARGIN_BOTTOM: o->margin_bottom = d->ival; break;
            case P_MARGIN_LEFT:   o->margin_left = d->ival; break;
            case P_PAD_TOP:    o->pad_top = d->ival; break;
            case P_PAD_RIGHT:  o->pad_right = d->ival; break;
            case P_PAD_BOTTOM: o->pad_bottom = d->ival; break;
            case P_PAD_LEFT:   o->pad_left = d->ival; break;
            case P_WIDTH:      o->width = d->ival; break;
            case P_MAXWIDTH:   o->max_width = d->ival; break;
            case P_WIDTH_PCT:    o->width_pct = d->ival; break;
            case P_MAXWIDTH_PCT: o->max_width_pct = d->ival; break;
            case P_MINWIDTH:   o->min_width = d->ival; break;
            case P_HEIGHT:     o->height = d->ival; break;
            case P_MINHEIGHT:  o->min_height = d->ival; break;
            case P_MAXHEIGHT:  o->max_height = d->ival; break;
            case P_FONTFAMILY:    o->font_family = d->ival; break;
            case P_TEXTTRANSFORM: o->text_transform = d->ival; break;
            case P_LETTERSPACING: o->letter_spacing = d->ival; break;
            case P_WORDSPACING:   o->word_spacing = d->ival; break;
            case P_SHADOW_DX:     o->shadow_dx = d->ival; break;
            case P_SHADOW_DY:     o->shadow_dy = d->ival; break;
            case P_SHADOW_COLOR:  o->shadow_color = d->ival; break;
            case P_OPACITY:       o->opacity = d->ival; break;
            case P_VALIGN:        o->valign = d->ival; break;
            case P_TEXTINDENT:    o->text_indent = d->ival; break;
            case P_WHITESPACE:    o->white_space = d->ival; break;
            case P_TABSIZE:       o->tab_size = d->ival; break;
            case P_LISTSTYLE:     o->list_style = d->ival; break;
            case P_DIRECTION:     o->direction = d->ival; break;
            case P_POSITION:      o->position = d->ival; break;
            case P_INSET_TOP:     o->inset_top = d->ival; break;
            case P_INSET_RIGHT:   o->inset_right = d->ival; break;
            case P_INSET_BOTTOM:  o->inset_bottom = d->ival; break;
            case P_INSET_LEFT:    o->inset_left = d->ival; break;
            case P_ZINDEX:        o->z_index = d->ival; break;
            case P_BOXSIZING:     o->box_sizing = d->ival; break;
            case P_BW_TOP:        o->border_top_width = d->ival; break;
            case P_BW_RIGHT:      o->border_right_width = d->ival; break;
            case P_BW_BOTTOM:     o->border_bottom_width = d->ival; break;
            case P_BW_LEFT:       o->border_left_width = d->ival; break;
            case P_BS_TOP:        o->border_top_style = d->ival; break;
            case P_BS_RIGHT:      o->border_right_style = d->ival; break;
            case P_BS_BOTTOM:     o->border_bottom_style = d->ival; break;
            case P_BS_LEFT:       o->border_left_style = d->ival; break;
            case P_BC_TOP:        o->border_top_color = d->ival; break;
            case P_BC_RIGHT:      o->border_right_color = d->ival; break;
            case P_BC_BOTTOM:     o->border_bottom_color = d->ival; break;
            case P_BC_LEFT:       o->border_left_color = d->ival; break;
            case P_BORDER_RADIUS: o->border_radius = d->ival; break;
            case P_BSHADOW_DX:     o->shadow2_dx = d->ival; break;
            case P_BSHADOW_DY:     o->shadow2_dy = d->ival; break;
            case P_BSHADOW_BLUR:   o->shadow2_blur = d->ival; break;
            case P_BSHADOW_SPREAD: o->shadow2_spread = d->ival; break;
            case P_BSHADOW_COLOR:  o->box_shadow_color = d->ival; break;
            case P_BSHADOW_INSET:  o->box_shadow_inset = d->ival; break;
            case P_OUTLINE_W:     o->outline_width = d->ival; break;
            case P_OUTLINE_S:     o->outline_style = d->ival; break;
            case P_OUTLINE_C:     o->outline_color = d->ival; break;
            case P_OUTLINE_OFFSET: o->outline_offset = d->ival; break;
            case P_FLEX_GROW:     o->flex_grow = d->ival; break;
            case P_FLEX_SHRINK:   o->flex_shrink = d->ival; break;
            case P_FLEX_BASIS:    o->flex_basis = d->ival; break;
            case P_ORDER:         o->order = d->ival; break;
            case P_ALIGN_ITEMS:   o->align_items = d->ival; break;
            case P_ALIGN_SELF:    o->align_self = d->ival; break;
            case P_ALIGN_CONTENT: o->align_content = d->ival; break;
            case P_JUSTIFY_ITEMS: o->justify_items = d->ival; break;
            case P_FLEX_DIR:      o->flex_direction = d->ival; break;
            case P_FLEX_WRAP:     o->flex_wrap = d->ival; break;
            case P_GRID_ROWS:     o->grid_rows = d->ival; break;
            case P_ROW_GAP:       o->row_gap = d->ival; break;
            case P_GRID_FLOW:     o->grid_auto_flow = d->ival; break;
            case P_GRID_COL_SPAN: o->grid_col_span = d->ival; break;
            case P_GRID_ROW_SPAN: o->grid_row_span = d->ival; break;
            case P_FLOAT:         o->float_side = d->ival; break;
            case P_CLEAR:         o->clear = d->ival; break;
            case P_VISIBILITY:    o->visibility = d->ival; break;
            case P_OVERFLOW_X:    o->overflow_x = d->ival; break;
            case P_OVERFLOW_Y:    o->overflow_y = d->ival; break;
            case P_CURSOR:        o->cursor = d->ival; break;
            case P_TEXT_OVERFLOW:   o->text_overflow = d->ival; break;
            case P_WORD_BREAK:      o->word_break = d->ival; break;
            case P_BORDER_COLLAPSE: o->border_collapse = d->ival; break;
            case P_BORDER_SPACING:  o->border_spacing = d->ival; break;
            case P_EMPTY_CELLS:     o->empty_cells = d->ival; break;
            case P_CAPTION_SIDE:    o->caption_side = d->ival; break;
            case P_TABLE_LAYOUT:    o->table_layout = d->ival; break;
            case P_FONT_VARIANT:    o->font_variant = d->ival; break;
            case P_HYPHENS:         o->hyphens = d->ival; break;
            case P_USER_SELECT:     o->user_select = d->ival; break;
            case P_CARET_COLOR:     o->caret_color = d->ival; break;
            case P_APPEARANCE:      o->appearance = d->ival; break;
            case P_POINTER_EVENTS:      o->pointer_events = d->ival; break;
            case P_BG_REPEAT:           o->bg_repeat = d->ival; break;
            case P_BG_SIZE:             o->bg_size = d->ival; break;
            case P_BG_CLIP:             o->bg_clip = d->ival; break;
            case P_BG_ORIGIN:           o->bg_origin = d->ival; break;
            case P_BG_ATTACHMENT:       o->bg_attachment = d->ival; break;
            case P_ISOLATION:           o->isolation = d->ival; break;
            case P_CONTAIN:             o->contain = d->ival; break;
            case P_CONTENT_VISIBILITY:  o->content_visibility = d->ival; break;
            case P_IMAGE_RENDERING:     o->image_rendering = d->ival; break;
            case P_COLOR_SCHEME:        o->color_scheme = d->ival; break;
            case P_ACCENT_COLOR:        o->accent_color = d->ival; break;
            case P_PRINT_COLOR_ADJUST:  o->print_color_adjust = d->ival; break;
            case P_FORCED_COLOR_ADJUST: o->forced_color_adjust = d->ival; break;
            case P_MIX_BLEND_MODE:      o->mix_blend_mode = d->ival; break;
            case P_TRANSFORM_TX:        o->transform_tx = d->ival; break;
            case P_TRANSFORM_TY:        o->transform_ty = d->ival; break;
            case P_OBJECT_FIT:          o->object_fit = d->ival; break;
            case P_LIST_STYLE_POS:      o->list_style_pos = d->ival; break;
            case P_FONT_KERNING:        o->font_kerning = d->ival; break;
            case P_TEXT_RENDERING:      o->text_rendering = d->ival; break;
            case P_FONT_STRETCH:        o->font_stretch = d->ival; break;
            case P_RESIZE:              o->resize = d->ival; break;
            case P_SCROLL_BEHAVIOR:     o->scroll_behavior = d->ival; break;
            case P_TOUCH_ACTION:        o->touch_action = d->ival; break;
            case P_OVERSCROLL_BEHAVIOR: o->overscroll_behavior = d->ival; break;
            case P_BACKFACE_VISIBILITY: o->backface_visibility = d->ival; break;
            case P_TEXTDECO_THICKNESS: o->text_decoration_thickness = d->ival; break;
            case P_ASPECT_NUM: o->aspect_num = d->ival; break;
            case P_ASPECT_DEN: o->aspect_den = d->ival; break;
            default: break;
        }
    }
}

css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         const char *inline_style, size_t inline_len) {
    /* Designated initializers: robust against field insertion/reordering (every
     * "unset" sentinel is named, so a new field cannot silently default to 0). */
    css_style out = {
        .color = -1, .background = -1, .text_align = CSS_ALIGN_UNSET,
        .font_scale = 0, .line_scale = 0,         .text_decoration = -1, .text_decoration_color = -1,
        .text_decoration_style = CSS_TDS_UNSET,
        .bold = -1, .italic = -1, .display = CSS_DISP_UNSET,
        .gap = -1, .justify = CSS_JUSTIFY_UNSET, .grid_cols = 0,
        .grid_col_w = { 0 },
        .margin_top = CSS_LEN_UNSET, .margin_right = CSS_LEN_UNSET,
        .margin_bottom = CSS_LEN_UNSET, .margin_left = CSS_LEN_UNSET,
        .pad_top = CSS_LEN_UNSET, .pad_right = CSS_LEN_UNSET,
        .pad_bottom = CSS_LEN_UNSET, .pad_left = CSS_LEN_UNSET,
        .width = CSS_LEN_UNSET, .max_width = CSS_LEN_UNSET,
        .min_width = CSS_LEN_UNSET, .height = CSS_LEN_UNSET,
        .min_height = CSS_LEN_UNSET, .max_height = CSS_LEN_UNSET,
        .font_family = CSS_FF_UNSET, .text_transform = CSS_TT_UNSET,
        .letter_spacing = CSS_LEN_UNSET, .word_spacing = CSS_LEN_UNSET,
        .shadow_dx = 0, .shadow_dy = 0, .shadow_color = -1,
        .opacity = -1, .valign = CSS_VA_UNSET,
        .text_indent = CSS_LEN_UNSET, .white_space = CSS_WS_UNSET,
        .tab_size = 0,
        .list_style = CSS_LS_UNSET,
        .direction = CSS_DIR_UNSET,
        .position = CSS_POS_UNSET,
        .inset_top = CSS_LEN_UNSET, .inset_right = CSS_LEN_UNSET,
        .inset_bottom = CSS_LEN_UNSET, .inset_left = CSS_LEN_UNSET,
        .z_index = CSS_LEN_UNSET, .box_sizing = CSS_BOXS_UNSET,
        .border_top_width = CSS_LEN_UNSET, .border_right_width = CSS_LEN_UNSET,
        .border_bottom_width = CSS_LEN_UNSET, .border_left_width = CSS_LEN_UNSET,
        .border_top_style = CSS_BST_UNSET, .border_right_style = CSS_BST_UNSET,
        .border_bottom_style = CSS_BST_UNSET, .border_left_style = CSS_BST_UNSET,
        .border_top_color = -1, .border_right_color = -1,
        .border_bottom_color = -1, .border_left_color = -1,
        .border_radius = CSS_LEN_UNSET,
        .shadow2_dx = 0, .shadow2_dy = 0, .shadow2_blur = 0, .shadow2_spread = 0,
        .box_shadow_color = -1, .box_shadow_inset = -1,
        .outline_width = CSS_LEN_UNSET, .outline_style = CSS_BST_UNSET,
        .outline_color = -1, .outline_offset = CSS_LEN_UNSET,
        .flex_grow = -1, .flex_shrink = -1, .flex_basis = CSS_LEN_UNSET,
        .order = CSS_LEN_UNSET,
        .align_items = CSS_AK_UNSET, .align_self = CSS_AK_UNSET,
        .align_content = CSS_AK_UNSET, .justify_items = CSS_AK_UNSET,
        .flex_direction = CSS_FD_UNSET, .flex_wrap = CSS_FW_UNSET,
        .grid_rows = 0, .row_gap = -1, .grid_auto_flow = CSS_GF_UNSET,
        .grid_col_span = 0, .grid_row_span = 0,
        .float_side = CSS_FLOAT_UNSET, .clear = CSS_CLEAR_UNSET,
        .visibility = CSS_VIS_UNSET,
        .overflow_x = CSS_OF_UNSET, .overflow_y = CSS_OF_UNSET,
        .cursor = CSS_CUR_UNSET,
        .text_overflow = CSS_TO_UNSET, .word_break = CSS_WB_UNSET,
        .border_collapse = CSS_BCOL_UNSET, .border_spacing = CSS_LEN_UNSET,
        .empty_cells = CSS_EC_UNSET, .caption_side = CSS_CS_UNSET,
        .table_layout = CSS_TL_UNSET,
        .font_variant = CSS_FV_UNSET,
        .hyphens = CSS_HY_UNSET, .user_select = CSS_US_UNSET,
        .caret_color = -1,
        .appearance = CSS_AP_UNSET, .pointer_events = CSS_PE_UNSET,
        .bg_repeat = CSS_BGR_UNSET, .bg_size = CSS_BGS_UNSET,
        .bg_clip = CSS_BGC_UNSET, .bg_origin = CSS_BGO_UNSET,
        .bg_attachment = CSS_BGA_UNSET,
        .isolation = CSS_ISO_UNSET, .contain = 0,
        .content_visibility = CSS_CV_UNSET,
        .image_rendering = CSS_IR_UNSET,
        .color_scheme = CSS_CSH_UNSET, .accent_color = -1,
        .print_color_adjust = CSS_PCA_UNSET,
        .forced_color_adjust = CSS_FCA_UNSET,
        .mix_blend_mode = CSS_MB_UNSET, .object_fit = CSS_OFI_UNSET,
        .list_style_pos = CSS_LP_UNSET,
        .font_kerning = CSS_FK_UNSET, .text_rendering = CSS_TR_UNSET,
        .font_stretch = CSS_FS_UNSET,
        .resize = CSS_RS_UNSET, .scroll_behavior = CSS_SB_UNSET,
        .touch_action = CSS_TA_UNSET, .overscroll_behavior = CSS_OS_UNSET,
        .backface_visibility = CSS_BF_UNSET,
        .text_decoration_thickness = -1,
        .aspect_num = 0, .aspect_den = 0,
        .bg_grad_n = 0, .bg_grad_angle = 180,
        .bg_grad_c = { -1, -1, -1, -1 },
        .transform_tx = CSS_LEN_UNSET, .transform_ty = CSS_LEN_UNSET,
    };
    int wi[P_NSLOTS], ws[P_NSLOTS], wo[P_NSLOTS];
    for (int k = 0; k < P_NSLOTS; ++k) { wi[k] = -1; ws[k] = -1; wo[k] = -1; }

    if (sheet != NULL && el != NULL) {
        for (size_t si = 0; si < sheet->nsels; ++si) {
            const css_sel *sel = &sheet->sels[si];
            if (!csel_matches(sel, el)) continue;
            size_t start = sheet->rules[sel->rule].start;
            size_t cnt = sheet->rules[sel->rule].count;
            for (size_t d = 0; d < cnt; ++d)
                apply_decl(&out, wi, ws, wo, &sheet->decls[start + d], sel->spec, sel->order);
        }
    }

    if (inline_style != NULL) {
        if (inline_len == 0) inline_len = strlen(inline_style);
        /* var() in an inline style= can reference a custom property declared
         * either in this SAME inline block (`style="--x:1;color:var(--x)"`) or in
         * the stylesheet (e.g. a `:root` rule). Inline-declared names win on a
         * collision (closer to the use site), so they go first in the combined
         * table -- expand_lookup takes the first match. */
        css_custom_prop combined[2 * CSS_MAX_CUSTOM_PROPS];
        size_t ncombined = 0;
        collect_custom_props(inline_style, inline_len, combined, CSS_MAX_CUSTOM_PROPS, &ncombined);
        if (sheet != NULL) {
            for (size_t i = 0; i < sheet->ncustom && ncombined < 2 * CSS_MAX_CUSTOM_PROPS; ++i) {
                int dup = 0;
                for (size_t k = 0; k < ncombined; ++k)
                    if (strcmp(combined[k].name, sheet->custom[i].name) == 0) { dup = 1; break; }
                if (!dup) combined[ncombined++] = sheet->custom[i];
            }
        }
        css_decl tmp[CSS_INLINE_DECLS];
        size_t dn = interpret_decls(inline_style, inline_len, tmp, CSS_INLINE_DECLS,
                                    combined, ncombined);
        for (size_t d = 0; d < dn; ++d)
            apply_decl(&out, wi, ws, wo, &tmp[d], CSS_INLINE_SPEC, INT_MAX);
    }

    return out;
}

css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                      const char *const *classes, size_t nclasses,
                      const char *inline_style, size_t inline_len) {
    /* No ancestor context: a parentless element. A complex (multi-compound) selector
     * therefore cannot match through its combinator (complex_matches needs parents).
     * No attributes are supplied, so [attr] selectors do not match via this entry
     * point (callers that need them build a css_element with attrs). */
    css_element el = { tag, id, classes, nclasses, NULL, 0, NULL, 0, 0, NULL };
    return css_resolve_el(sheet, &el, inline_style, inline_len);
}

css_style css_parse_inline(const char *style, size_t len) {
    return css_resolve(NULL, NULL, NULL, NULL, 0, style, len);
}
