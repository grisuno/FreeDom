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
 * selector engine). */
#define CSS_MAX_SELS            512u
#define CSS_MAX_DECLS           2048u
#define CSS_MAX_RULES           384u
#define CSS_SELS_PER_GROUP      32
#define CSS_INLINE_DECLS        64u
#define CSS_INLINE_SPEC         (1 << 20)

/* Property slots. The enum value IS the css_style slot index used by apply().
 * The four margin slots are contiguous in CSS shorthand order (top,right,bottom,
 * left); the four padding slots likewise — expand_box4 relies on that. */
enum { P_COLOR = 0, P_BG, P_ALIGN, P_FONTSIZE, P_LINEHEIGHT, P_WEIGHT, P_STYLE,
       P_TEXTDECO, P_DISPLAY, P_GAP, P_JUSTIFY, P_GRIDCOLS,
       P_MARGIN_TOP, P_MARGIN_RIGHT, P_MARGIN_BOTTOM, P_MARGIN_LEFT,
       P_PAD_TOP, P_PAD_RIGHT, P_PAD_BOTTOM, P_PAD_LEFT,
       P_WIDTH, P_MAXWIDTH,
       /* Text-presentation extensions (Hito 23b-6). The three text-shadow slots are
        * contiguous (dx,dy,color) so expand_shadow writes them as a group. */
       P_FONTFAMILY, P_TEXTTRANSFORM, P_LETTERSPACING, P_WORDSPACING,
       P_SHADOW_DX, P_SHADOW_DY, P_SHADOW_COLOR,
       P_OPACITY, P_VALIGN, P_TEXTINDENT, P_WHITESPACE, P_LISTSTYLE,
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
       P_OUTLINE_W, P_OUTLINE_S, P_OUTLINE_C,
       P_FLEX_GROW, P_FLEX_SHRINK, P_FLEX_BASIS,
       P_ORDER, P_ALIGN_ITEMS, P_ALIGN_SELF, P_ALIGN_CONTENT, P_JUSTIFY_ITEMS,
       P_FLEX_DIR, P_FLEX_WRAP,
       P_GRID_ROWS, P_ROW_GAP, P_GRID_FLOW, P_GRID_COL_SPAN, P_GRID_ROW_SPAN,
       P_FLOAT, P_CLEAR,
       P_NSLOTS };

typedef struct css_decl {
    int prop;       /* P_* */
    int ival;       /* interpreted value (color packed / enum / scale / bool) */
    int important;  /* 1 if the declaration carried !important (higher cascade tier) */
} css_decl;

/* The selector types (css_attr_match/css_compound/css_sel) and their parser/matcher
 * live in css_select.{h,c}. */

struct css_sheet {
    css_decl decls[CSS_MAX_DECLS];
    size_t   ndecls;
    struct { size_t start, count; } rules[CSS_MAX_RULES];
    size_t   nrules;
    css_sel  sels[CSS_MAX_SELS];
    size_t   nsels;
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

static int interp_color(const char *v) {
    cc_rgb c;
    return (cc_parse(v, &c) == CC_OK) ? cc_pack(c) : -1;
}

static int interp_bg(const char *v) {
    if (csel_substr(v, "url(", 1)) return -1;   /* never phone home */
    cc_rgb c;
    if (cc_parse(v, &c) == CC_OK) return cc_pack(c);
    /* shorthand: try the first whitespace-delimited token as a color. */
    char tok[CSS_TOK_MAX];
    size_t k = 0;
    const char *p = v;
    while (*p == ' ' || *p == '\t') ++p;
    while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
    tok[k] = '\0';
    return (cc_parse(tok, &c) == CC_OK) ? cc_pack(c) : -1;
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
    else return -1;  /* px/em/other: out of scope, dropped */
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
    if (csel_ci_eq(v, "flex") || csel_ci_eq(v, "inline-flex")) return CSS_DISP_FLEX;
    if (csel_ci_eq(v, "grid") || csel_ci_eq(v, "inline-grid")) return CSS_DISP_GRID;
    return -1;  /* unknown display: leave unset */
}

/* gap / grid-gap / column-gap: leading length as px (a two-value gap keeps the
 * first), "normal" -> 0; clamped to [0, CSS_GAP_MAX]. -1 when not a length. */
static int interp_gap(const char *v) {
    if (csel_ci_eq(v, "normal")) return 0;
    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    return round_clamp(num, 0, CSS_GAP_MAX);
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

/* grid-template-columns: count of whitespace-separated track tokens, clamped to
 * [1, CSS_GRID_COLS_MAX]. "none"/empty -> -1 (unset). repeat()/minmax() are counted
 * as literal tokens (out of scope). url() defensively dropped. */
static int interp_gridcols(const char *v) {
    if (csel_substr(v, "url(", 1)) return -1;
    if (csel_ci_eq(v, "none")) return -1;
    int n = 0, in_tok = 0;
    for (const char *p = v; *p != '\0'; ++p) {
        int ws = (*p == ' ' || *p == '\t');
        if (!ws && !in_tok) { ++n; in_tok = 1; }
        else if (ws) in_tok = 0;
    }
    if (n < 1) return -1;
    if (n > CSS_GRID_COLS_MAX) n = CSS_GRID_COLS_MAX;
    return n;
}

/* Parses one box-model length. Accepts "Npx", a bare "0", "Nem"/"Nrem" (x16 px,
 * the engine's base font), and (when allow_auto) "auto". Rejects %/viewport units,
 * calc()/var() and bare non-zero numbers (fail closed: they need a containing block
 * the parser does not have). Returns 1 with *out = CSS_LEN_AUTO or a signed px
 * clamped to [-CSS_LEN_MAX, CSS_LEN_MAX]; 0 if unsupported. */
static int interp_len(const char *v, int allow_auto, int *out) {
    if (allow_auto && csel_ci_eq(v, "auto")) { *out = CSS_LEN_AUTO; return 1; }
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
        return 0;                       /* %, vw/vh, pt, calc(...), ... */
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

/* Expands a margin/padding shorthand (1..4 whitespace-separated lengths, CSS order
 * all / "v h" / "t h b" / "t r b l") into the four contiguous slots starting at
 * slot_top (top,right,bottom,left). Any unsupported token drops the WHOLE shorthand
 * (fail closed, never a partial box). Returns the number of decls written (<= cap). */
static int expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
                       css_decl *dst, int cap) {
    int vals[4], nv = 0;
    const char *p = val;
    while (nv < 4) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
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
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
        while (*p != '\0' && *p != ' ' && *p != '\t') ++p;
        int px;
        cc_rgb c;
        if (interp_len(tok, 0, &px)) { if (nlen < 3) lens[nlen++] = px; }
        else if (!have_color && cc_parse(tok, &c) == CC_OK) { color = cc_pack(c); have_color = 1; }
    }
    if (nlen < 2) return 0;  /* need both offsets */
    int dx = lens[0], dy = lens[1];
    if (dx > CSS_SHADOW_MAX) dx = CSS_SHADOW_MAX;
    if (dx < -CSS_SHADOW_MAX) dx = -CSS_SHADOW_MAX;
    if (dy > CSS_SHADOW_MAX) dy = CSS_SHADOW_MAX;
    if (dy < -CSS_SHADOW_MAX) dy = -CSS_SHADOW_MAX;
    dst[0].prop = P_SHADOW_DX;    dst[0].ival = dx;
    dst[1].prop = P_SHADOW_DY;    dst[1].ival = dy;
    dst[2].prop = P_SHADOW_COLOR; dst[2].ival = have_color ? color : 0x000000;
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
    while (nv < 4) {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
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
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0') break;
        char tok[CSS_TOK_MAX];
        size_t k = 0;
        while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
        tok[k] = '\0';
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
        while (*p != '\0') {
            while (*p == ' ' || *p == '\t') ++p;
            if (*p == '\0') break;
            char tok[CSS_TOK_MAX];
            size_t k = 0;
            while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
            tok[k] = '\0';
            if (csel_ci_eq(tok, "inset")) { inset = 1; continue; }
            int px;
            cc_rgb c;
            if (interp_len(tok, 0, &px)) { if (nlen < 4) lens[nlen++] = px; }
            else if (!have_color && cc_parse(tok, &c) == CC_OK) { color = cc_pack(c); have_color = 1; }
            /* else: unknown token ignored */
        }
        if (nlen < 2) return 0;   /* need both offsets */
    }
    dst[0].prop = P_BSHADOW_DX;     dst[0].ival = nlen > 0 ? lens[0] : 0;
    dst[1].prop = P_BSHADOW_DY;     dst[1].ival = nlen > 1 ? lens[1] : 0;
    dst[2].prop = P_BSHADOW_BLUR;   dst[2].ival = nlen > 2 ? lens[2] : 0;
    dst[3].prop = P_BSHADOW_SPREAD; dst[3].ival = nlen > 3 ? lens[3] : 0;
    dst[4].prop = P_BSHADOW_COLOR;  dst[4].ival = csel_ci_eq(val, "none") ? -1
                                                : (have_color ? color : 0x000000);
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
        while (*p != '\0' && ntok < 4) {
            while (*p == ' ' || *p == '\t') ++p;
            if (*p == '\0') break;
            char tok[CSS_TOK_MAX];
            size_t k = 0;
            while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++;
            tok[k] = '\0';
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
    if (strcmp(prop, "width") == 0)     return emit_len(dst, cap, P_WIDTH, val, 0, 0);
    if (strcmp(prop, "max-width") == 0) return emit_len(dst, cap, P_MAXWIDTH, val, 0, 0);

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

    int prop_id, ival;
    if (strcmp(prop, "color") == 0)                 { prop_id = P_COLOR;    ival = interp_color(val); }
    else if (strcmp(prop, "background-color") == 0 ||
             strcmp(prop, "background") == 0)        { prop_id = P_BG;       ival = interp_bg(val); }
    else if (strcmp(prop, "text-align") == 0)        { prop_id = P_ALIGN;    ival = interp_align(val); }
    else if (strcmp(prop, "font-size") == 0)         { prop_id = P_FONTSIZE; ival = interp_fontsize(val); }
    else if (strcmp(prop, "line-height") == 0)       { prop_id = P_LINEHEIGHT; ival = interp_lineheight(val); }
    else if (strcmp(prop, "font-weight") == 0)       { prop_id = P_WEIGHT;   ival = interp_weight(val); }
    else if (strcmp(prop, "font-style") == 0)        { prop_id = P_STYLE;    ival = interp_style(val); }
    else if (strcmp(prop, "text-decoration") == 0 ||
             strcmp(prop, "text-decoration-line") == 0) { prop_id = P_TEXTDECO; ival = interp_textdeco(val); }
    else if (strcmp(prop, "display") == 0)           { prop_id = P_DISPLAY;  ival = interp_display(val); }
    else if (strcmp(prop, "gap") == 0 ||
             strcmp(prop, "grid-gap") == 0 ||
             strcmp(prop, "column-gap") == 0)         { prop_id = P_GAP;      ival = interp_gap(val); }
    else if (strcmp(prop, "justify-content") == 0)    { prop_id = P_JUSTIFY;  ival = interp_justify(val); }
    else if (strcmp(prop, "grid-template-columns") == 0) { prop_id = P_GRIDCOLS; ival = interp_gridcols(val); }
    else if (strcmp(prop, "font-family") == 0)        { prop_id = P_FONTFAMILY;    ival = interp_fontfamily(val); }
    else if (strcmp(prop, "text-transform") == 0)     { prop_id = P_TEXTTRANSFORM; ival = interp_texttransform(val); }
    else if (strcmp(prop, "opacity") == 0)            { prop_id = P_OPACITY;       ival = interp_opacity(val); }
    else if (strcmp(prop, "vertical-align") == 0)     { prop_id = P_VALIGN;        ival = interp_valign(val); }
    else if (strcmp(prop, "white-space") == 0)        { prop_id = P_WHITESPACE;    ival = interp_whitespace(val); }
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
    else return 0;

    if (ival < 0) return 0;  /* unsupported value */
    dst[0].prop = prop_id;
    dst[0].ival = ival;
    return 1;
}

/* Interprets one declaration span s[0,n) into dst (up to cap). Returns the number of
 * css_decl written (0 if unsupported). Splits `prop: value`, strips a trailing
 * `!important` (stamping every emitted decl), then dispatches on the property. */
static int parse_one_decl(const char *s, size_t n, css_decl *dst, int cap) {
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

    int nw = interpret_prop(prop, val, dst, cap);
    for (int i = 0; i < nw; ++i) dst[i].important = important;
    return nw;
}

/* Splits a ';'-separated declaration block into dst (up to cap). Returns count. */
static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap) {
    size_t count = 0, i = 0;
    while (i < n && count < cap) {
        size_t j = i;
        while (j < n && s[j] != ';') ++j;
        count += (size_t)parse_one_decl(s + i, j - i, &dst[count], (int)(cap - count));
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
    size_t dn = interpret_decls(s + ds, de - ds, &sh->decls[dstart], CSS_MAX_DECLS - dstart);
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
            case P_ALIGN:    o->text_align = (css_align)d->ival; break;
            case P_FONTSIZE: o->font_scale = d->ival; break;
            case P_LINEHEIGHT: o->line_scale = d->ival; break;
            case P_WEIGHT:   o->bold = d->ival; break;
            case P_STYLE:    o->italic = d->ival; break;
            case P_TEXTDECO: o->text_decoration = d->ival; break;
            case P_DISPLAY:  o->display = (css_display)d->ival; break;
            case P_GAP:      o->gap = d->ival; break;
            case P_JUSTIFY:  o->justify = (css_justify)d->ival; break;
            case P_GRIDCOLS: o->grid_cols = d->ival; break;
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
            case P_LISTSTYLE:     o->list_style = d->ival; break;
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
        .font_scale = 0, .line_scale = 0, .text_decoration = -1,
        .bold = -1, .italic = -1, .display = CSS_DISP_UNSET,
        .gap = -1, .justify = CSS_JUSTIFY_UNSET, .grid_cols = 0,
        .margin_top = CSS_LEN_UNSET, .margin_right = CSS_LEN_UNSET,
        .margin_bottom = CSS_LEN_UNSET, .margin_left = CSS_LEN_UNSET,
        .pad_top = CSS_LEN_UNSET, .pad_right = CSS_LEN_UNSET,
        .pad_bottom = CSS_LEN_UNSET, .pad_left = CSS_LEN_UNSET,
        .width = CSS_LEN_UNSET, .max_width = CSS_LEN_UNSET,
        .font_family = CSS_FF_UNSET, .text_transform = CSS_TT_UNSET,
        .letter_spacing = CSS_LEN_UNSET, .word_spacing = CSS_LEN_UNSET,
        .shadow_dx = 0, .shadow_dy = 0, .shadow_color = -1,
        .opacity = -1, .valign = CSS_VA_UNSET,
        .text_indent = CSS_LEN_UNSET, .white_space = CSS_WS_UNSET,
        .list_style = CSS_LS_UNSET,
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
        .outline_width = CSS_LEN_UNSET, .outline_style = CSS_BST_UNSET, .outline_color = -1,
        .flex_grow = -1, .flex_shrink = -1, .flex_basis = CSS_LEN_UNSET,
        .order = CSS_LEN_UNSET,
        .align_items = CSS_AK_UNSET, .align_self = CSS_AK_UNSET,
        .align_content = CSS_AK_UNSET, .justify_items = CSS_AK_UNSET,
        .flex_direction = CSS_FD_UNSET, .flex_wrap = CSS_FW_UNSET,
        .grid_rows = 0, .row_gap = -1, .grid_auto_flow = CSS_GF_UNSET,
        .grid_col_span = 0, .grid_row_span = 0,
        .float_side = CSS_FLOAT_UNSET, .clear = CSS_CLEAR_UNSET,
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
        css_decl tmp[CSS_INLINE_DECLS];
        size_t dn = interpret_decls(inline_style, inline_len, tmp, CSS_INLINE_DECLS);
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
