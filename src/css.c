/*
 * css — pure author-CSS parser + simple cascade. See include/css.h, spec/css.md.
 *
 * Hostile content: never fetches (url()/@-rules dropped), bounded (anti-DoS),
 * fails closed. No global state; the only allocation is the sheet.
 */

#include "css.h"
#include "css_color.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>

/* Bounds (anti-DoS). A stylesheet beyond these is truncated, never unbounded. */
#define CSS_TOK_MAX             64u
#define CSS_MAX_CLASSES_PER_SEL 6
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
       P_DISPLAY, P_GAP, P_JUSTIFY, P_GRIDCOLS,
       P_MARGIN_TOP, P_MARGIN_RIGHT, P_MARGIN_BOTTOM, P_MARGIN_LEFT,
       P_PAD_TOP, P_PAD_RIGHT, P_PAD_BOTTOM, P_PAD_LEFT,
       P_WIDTH, P_MAXWIDTH, P_NSLOTS };

typedef struct css_decl {
    int prop;       /* P_* */
    int ival;       /* interpreted value (color packed / enum / scale / bool) */
    int important;  /* 1 if the declaration carried !important (higher cascade tier) */
} css_decl;

/* Combinator joining a compound to the one on its left. */
enum { COMB_DESCENDANT = 0, COMB_CHILD = 1 };

/* Attribute selector operator. PRESENT is bare `[attr]`; the rest carry a value. */
enum { ATTR_PRESENT = 0, ATTR_EQ, ATTR_TILDE, ATTR_PIPE, ATTR_CARET, ATTR_DOLLAR, ATTR_STAR };

/* One attribute selector inside a compound: name OP value, with a case flag. */
typedef struct css_attr_match {
    char name[CSS_TOK_MAX];
    char value[CSS_TOK_MAX];
    int  op;   /* ATTR_* */
    int  ci;   /* 1 = match the value case-insensitively (the trailing `i` flag) */
} css_attr_match;

/* One compound selector: optional type, optional id, zero+ classes, zero+ [attr]. */
typedef struct css_compound {
    char tag[CSS_TOK_MAX];
    int  has_tag;
    char id[CSS_TOK_MAX];
    int  has_id;
    char cls[CSS_MAX_CLASSES_PER_SEL][CSS_TOK_MAX];
    int  ncls;
    css_attr_match attrs[CSS_MAX_ATTR_SEL];
    int  nattrs;
} css_compound;

/* A complex selector: a chain of compounds, parts[nparts-1] being the subject (the
 * element a rule styles). comb[k] (k>=1) is the combinator to the LEFT of parts[k];
 * comb[0] is unused. A single compound is nparts == 1. */
typedef struct css_sel {
    css_compound parts[CSS_MAX_COMPOUNDS];
    int  comb[CSS_MAX_COMPOUNDS];
    int  nparts;
    int  spec;
    int  order;     /* document order (tie-break) */
    int  rule;      /* index into rules[] */
} css_sel;

struct css_sheet {
    css_decl decls[CSS_MAX_DECLS];
    size_t   ndecls;
    struct { size_t start, count; } rules[CSS_MAX_RULES];
    size_t   nrules;
    css_sel  sels[CSS_MAX_SELS];
    size_t   nsels;
};

/* --- small ASCII helpers --- */

static char lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c; }

static int ci_eq(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (lower(*a) != lower(*b)) return 0;
        ++a; ++b;
    }
    return *a == '\0' && *b == '\0';
}

/* True if a[0,n) equals b[0,n) up to n chars (b NUL-terminated), case-folded when ci. */
static int span_eq(const char *a, const char *b, size_t n, int ci) {
    for (size_t i = 0; i < n; ++i) {
        char x = a[i], y = b[i];
        if (ci) { x = lower(x); y = lower(y); }
        if (x != y) return 0;
    }
    return 1;
}

/* Substring test (used both to drop any value carrying url() — always ci — and by the
 * attribute `*=` operator). A non-empty needle only; an empty needle never matches. */
static int substr_match(const char *hay, const char *needle, int ci) {
    size_t nl = strlen(needle), hl = strlen(hay);
    if (nl == 0 || nl > hl) return 0;
    for (size_t off = 0; off + nl <= hl; ++off)
        if (span_eq(hay + off, needle, nl, ci)) return 1;
    return 0;
}

static int is_ident_ch(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_' || c == '-';
}

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

/* --- value interpreters (return -1 / sentinel when the value is unsupported) --- */

static int interp_color(const char *v) {
    cc_rgb c;
    return (cc_parse(v, &c) == CC_OK) ? cc_pack(c) : -1;
}

static int interp_bg(const char *v) {
    if (substr_match(v, "url(", 1)) return -1;   /* never phone home */
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
    if (ci_eq(v, "left") || ci_eq(v, "start")) return CSS_ALIGN_LEFT;
    if (ci_eq(v, "center")) return CSS_ALIGN_CENTER;
    if (ci_eq(v, "right") || ci_eq(v, "end")) return CSS_ALIGN_RIGHT;
    if (ci_eq(v, "justify")) return CSS_ALIGN_JUSTIFY;
    return -1;
}

static int interp_fontsize(const char *v) {
    if (ci_eq(v, "medium")) return 100;
    if (ci_eq(v, "small") || ci_eq(v, "smaller")) return 85;
    if (ci_eq(v, "large") || ci_eq(v, "larger")) return 120;
    if (ci_eq(v, "x-large")) return 150;
    if (ci_eq(v, "xx-large")) return 200;
    if (ci_eq(v, "x-small")) return 75;
    if (ci_eq(v, "xx-small")) return 60;

    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    int scale;
    if (ci_eq(end, "px")) scale = (int)(num / 16.0 * 100.0 + 0.5);
    else if (ci_eq(end, "em") || ci_eq(end, "rem")) scale = (int)(num * 100.0 + 0.5);
    else if (end[0] == '%' && end[1] == '\0') scale = (int)(num + 0.5);
    else if (ci_eq(end, "pt")) scale = (int)(num * 1.333 / 16.0 * 100.0 + 0.5);
    else return -1;
    if (scale < 10) scale = 10;
    if (scale > 1000) scale = 1000;
    return scale;
}

/* line-height as a percent of the natural line box. A unitless multiplier ("1.5" ->
 * 150) or a percent ("160%" -> 160); "normal" is unset (the UA default). Absolute px/em
 * line-heights need a font size we don't have here, so they are dropped (return -1).
 * Clamped to [CSS_LINE_MIN, CSS_LINE_MAX] (anti-DoS). */
static int interp_lineheight(const char *v) {
    if (ci_eq(v, "normal")) return 0;
    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    int pct;
    if (end[0] == '\0')                       pct = (int)(num * 100.0 + 0.5); /* unitless */
    else if (end[0] == '%' && end[1] == '\0') pct = (int)(num + 0.5);
    else return -1;  /* px/em/other: out of scope, dropped */
    if (pct < CSS_LINE_MIN) pct = CSS_LINE_MIN;
    if (pct > CSS_LINE_MAX) pct = CSS_LINE_MAX;
    return pct;
}

static int interp_weight(const char *v) {
    if (ci_eq(v, "bold") || ci_eq(v, "bolder")) return 1;
    if (ci_eq(v, "normal") || ci_eq(v, "lighter")) return 0;
    double num;
    const char *end;
    if (parse_num(v, &num, &end) && *end == '\0') return num >= 600.0 ? 1 : 0;
    return -1;
}

static int interp_style(const char *v) {
    if (ci_eq(v, "italic") || ci_eq(v, "oblique")) return 1;
    if (ci_eq(v, "normal")) return 0;
    return -1;
}

static int interp_display(const char *v) {
    if (ci_eq(v, "none")) return CSS_DISP_NONE;
    if (ci_eq(v, "block")) return CSS_DISP_BLOCK;
    if (ci_eq(v, "inline")) return CSS_DISP_INLINE;
    if (ci_eq(v, "inline-block")) return CSS_DISP_INLINE_BLOCK;
    if (ci_eq(v, "flex") || ci_eq(v, "inline-flex")) return CSS_DISP_FLEX;
    if (ci_eq(v, "grid") || ci_eq(v, "inline-grid")) return CSS_DISP_GRID;
    return -1;  /* unknown display: leave unset */
}

/* gap / grid-gap / column-gap: leading length as px (a two-value gap keeps the
 * first), "normal" -> 0; clamped to [0, CSS_GAP_MAX]. -1 when not a length. */
static int interp_gap(const char *v) {
    if (ci_eq(v, "normal")) return 0;
    double num;
    const char *end;
    if (!parse_num(v, &num, &end)) return -1;
    int px = (int)(num + 0.5);
    if (px < 0) px = 0;
    if (px > CSS_GAP_MAX) px = CSS_GAP_MAX;
    return px;
}

static int interp_justify(const char *v) {
    if (ci_eq(v, "flex-start") || ci_eq(v, "start") || ci_eq(v, "normal"))
        return CSS_JUSTIFY_START;
    if (ci_eq(v, "flex-end") || ci_eq(v, "end")) return CSS_JUSTIFY_END;
    if (ci_eq(v, "center")) return CSS_JUSTIFY_CENTER;
    if (ci_eq(v, "space-between")) return CSS_JUSTIFY_SPACE_BETWEEN;
    if (ci_eq(v, "space-around")) return CSS_JUSTIFY_SPACE_AROUND;
    if (ci_eq(v, "space-evenly")) return CSS_JUSTIFY_SPACE_EVENLY;
    return -1;  /* unknown: fail closed */
}

/* grid-template-columns: count of whitespace-separated track tokens, clamped to
 * [1, CSS_GRID_COLS_MAX]. "none"/empty -> -1 (unset). repeat()/minmax() are counted
 * as literal tokens (out of scope). url() defensively dropped. */
static int interp_gridcols(const char *v) {
    if (substr_match(v, "url(", 1)) return -1;
    if (ci_eq(v, "none")) return -1;
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
    if (allow_auto && ci_eq(v, "auto")) { *out = CSS_LEN_AUTO; return 1; }
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
    } else if (ci_eq(end, "px")) {
        px = num;
    } else if (ci_eq(end, "em") || ci_eq(end, "rem")) {
        px = num * 16.0;
    } else {
        return 0;                       /* %, vw/vh, pt, calc(...), ... */
    }
    int val = (int)(px + 0.5);
    if (neg) val = -val;
    if (val > CSS_LEN_MAX) val = CSS_LEN_MAX;
    if (val < -CSS_LEN_MAX) val = -CSS_LEN_MAX;
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
        if (!ci_eq(r, "important")) return 0;   /* a non-!important '!': leave as-is */
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

    int prop_id, ival;
    if (strcmp(prop, "color") == 0)                 { prop_id = P_COLOR;    ival = interp_color(val); }
    else if (strcmp(prop, "background-color") == 0 ||
             strcmp(prop, "background") == 0)        { prop_id = P_BG;       ival = interp_bg(val); }
    else if (strcmp(prop, "text-align") == 0)        { prop_id = P_ALIGN;    ival = interp_align(val); }
    else if (strcmp(prop, "font-size") == 0)         { prop_id = P_FONTSIZE; ival = interp_fontsize(val); }
    else if (strcmp(prop, "line-height") == 0)       { prop_id = P_LINEHEIGHT; ival = interp_lineheight(val); }
    else if (strcmp(prop, "font-weight") == 0)       { prop_id = P_WEIGHT;   ival = interp_weight(val); }
    else if (strcmp(prop, "font-style") == 0)        { prop_id = P_STYLE;    ival = interp_style(val); }
    else if (strcmp(prop, "display") == 0)           { prop_id = P_DISPLAY;  ival = interp_display(val); }
    else if (strcmp(prop, "gap") == 0 ||
             strcmp(prop, "grid-gap") == 0 ||
             strcmp(prop, "column-gap") == 0)         { prop_id = P_GAP;      ival = interp_gap(val); }
    else if (strcmp(prop, "justify-content") == 0)    { prop_id = P_JUSTIFY;  ival = interp_justify(val); }
    else if (strcmp(prop, "grid-template-columns") == 0) { prop_id = P_GRIDCOLS; ival = interp_gridcols(val); }
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
    for (char *p = prop; *p != '\0'; ++p) *p = lower(*p);

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

/* Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am.
 * Advances *ip past the closing ']'. Returns 1 if supported, 0 (fail closed) on any
 * malformation (no name, unknown operator, unterminated). Grammar:
 *   '[' ws name ws ( ']' | op '=' ws value ws (i|s)? ws ']' )
 * value may be quoted (single/double; quotes stripped, may contain whitespace). */
static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am) {
    size_t i = *ip + 1;  /* past '[' */
    memset(am, 0, sizeof *am);
    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;

    size_t k = 0;
    while (i < b && is_ident_ch(s[i])) {
        if (k + 1 < CSS_TOK_MAX) am->name[k++] = lower(s[i]);
        ++i;
    }
    am->name[k] = '\0';
    if (k == 0) return 0;  /* no attribute name */
    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;

    if (i < b && s[i] == ']') { am->op = ATTR_PRESENT; *ip = i + 1; return 1; }

    if (i < b && s[i] == '=') { am->op = ATTR_EQ; ++i; }
    else if (i + 1 < b && s[i + 1] == '=') {
        switch (s[i]) {
            case '~': am->op = ATTR_TILDE;  break;
            case '|': am->op = ATTR_PIPE;   break;
            case '^': am->op = ATTR_CARET;  break;
            case '$': am->op = ATTR_DOLLAR; break;
            case '*': am->op = ATTR_STAR;   break;
            default:  return 0;            /* unknown operator */
        }
        i += 2;
    } else {
        return 0;
    }

    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
    char q = 0;
    if (i < b && (s[i] == '"' || s[i] == '\'')) { q = s[i]; ++i; }
    size_t vk = 0;
    while (i < b) {
        char ch = s[i];
        if (q) { if (ch == q) { ++i; break; } }
        else if (ch == ']' || ch == ' ' || ch == '\t') break;
        if (vk + 1 < CSS_TOK_MAX) am->value[vk++] = ch;
        ++i;
    }
    am->value[vk] = '\0';

    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i < b && (s[i] == 'i' || s[i] == 'I')) { am->ci = 1; ++i; }
    else if (i < b && (s[i] == 's' || s[i] == 'S')) { am->ci = 0; ++i; }
    while (i < b && (s[i] == ' ' || s[i] == '\t')) ++i;
    if (i >= b || s[i] != ']') return 0;   /* unterminated attribute selector */
    *ip = i + 1;
    return 1;
}

/* Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space)
 * into *cp. Returns 1 if supported (type, .class, #id, *, [attr]). */
static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp) {
    if (a >= b) return 0;
    memset(cp, 0, sizeof *cp);
    size_t i = a;
    if (s[i] == '*') {
        ++i;  /* universal: no type */
    } else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
        size_t k = 0;
        while (i < b && is_ident_ch(s[i])) {
            if (k + 1 < sizeof cp->tag) cp->tag[k++] = lower(s[i]);
            ++i;
        }
        cp->tag[k] = '\0';
        cp->has_tag = 1;
    } else if (s[i] != '.' && s[i] != '#' && s[i] != '[') {
        return 0;
    }

    while (i < b) {
        if (s[i] == '.') {
            ++i;
            if (i >= b || !is_ident_ch(s[i])) return 0;
            if (cp->ncls >= CSS_MAX_CLASSES_PER_SEL) return 0;
            size_t k = 0;
            while (i < b && is_ident_ch(s[i])) {
                if (k + 1 < CSS_TOK_MAX) cp->cls[cp->ncls][k++] = s[i];
                ++i;
            }
            cp->cls[cp->ncls][k] = '\0';
            ++cp->ncls;
        } else if (s[i] == '#') {
            ++i;
            if (i >= b || !is_ident_ch(s[i]) || cp->has_id) return 0;
            size_t k = 0;
            while (i < b && is_ident_ch(s[i])) {
                if (k + 1 < sizeof cp->id) cp->id[k++] = s[i];
                ++i;
            }
            cp->id[k] = '\0';
            cp->has_id = 1;
        } else if (s[i] == '[') {
            if (cp->nattrs >= CSS_MAX_ATTR_SEL) return 0;
            if (!parse_attr_sel(s, &i, b, &cp->attrs[cp->nattrs])) return 0;
            ++cp->nattrs;
        } else {
            return 0;  /* unexpected char inside a compound */
        }
    }
    return 1;
}

/* Parses a complex selector span s[a,b) into *sel: a chain of compounds joined by
 * the descendant (whitespace) or child (`>`) combinator. Returns 1 if supported.
 * Attribute selectors `[...]` are now supported; the sibling combinators (`+`/`~`)
 * and pseudo-classes (`:`) are unsupported: the whole selector is dropped (fail
 * closed). A chain deeper than CSS_MAX_COMPOUNDS is dropped. Whitespace inside a
 * bracket (a quoted attribute value) does NOT split a compound. Specificity is the
 * sum over all compounds (id*100 + (class+attr)*10 + type). */
static int parse_complex_selector(const char *s, size_t a, size_t b, css_sel *sel) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    if (a >= b) return 0;

    /* Unsupported syntax OUTSIDE brackets => drop the whole selector. `>` and
     * whitespace are combinators; `[`/`]` open an attribute selector (whose contents
     * may legitimately contain `~`/`+`/`*`/etc, so they are skipped here). */
    int in_br = 0;
    for (size_t i = a; i < b; ++i) {
        char c = s[i];
        if (c == '[') { if (in_br) return 0; in_br = 1; continue; }
        if (c == ']') { if (!in_br) return 0; in_br = 0; continue; }
        if (in_br) continue;
        if (c == '+' || c == '~' || c == ':' || c == '(' || c == ')') return 0;
    }
    if (in_br) return 0;  /* unbalanced bracket */

    memset(sel, 0, sizeof *sel);
    int n = 0;
    size_t i = a;
    while (i < b) {
        /* Skip the separator before this compound, noting a `>` (child combinator). */
        int child = 0;
        while (i < b && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' ||
                         s[i] == '\r' || s[i] == '>')) {
            if (s[i] == '>') { if (child) return 0; child = 1; }  /* `>>` invalid */
            ++i;
        }
        if (i >= b) { if (child) return 0; break; }   /* trailing `>` with no compound */
        if (n == 0 && child) return 0;                /* leading `>` */

        /* The compound runs until whitespace/`>` at bracket depth 0; a `[..]` keeps a
         * quoted value with spaces in the same compound. */
        size_t ts = i;
        int br = 0;
        while (i < b) {
            char c = s[i];
            if (c == '[') br = 1;
            else if (c == ']') br = 0;
            else if (!br && (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '>'))
                break;
            ++i;
        }
        if (n >= CSS_MAX_COMPOUNDS) return 0;          /* too deep: fail closed */
        if (!parse_compound(s, ts, i, &sel->parts[n])) return 0;
        sel->comb[n] = (n == 0) ? COMB_DESCENDANT : (child ? COMB_CHILD : COMB_DESCENDANT);
        ++n;
    }
    if (n == 0) return 0;
    sel->nparts = n;

    int spec = 0;
    for (int k = 0; k < n; ++k)
        spec += 100 * (sel->parts[k].has_id ? 1 : 0) +
                10 * (sel->parts[k].ncls + sel->parts[k].nattrs) +
                (sel->parts[k].has_tag ? 1 : 0);
    sel->spec = spec;
    return 1;
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
        if (parse_complex_selector(s, i, j, &tmp[got])) ++got;
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
    return parse_num(v, &d, &e) ? (int)(d + 0.5) : 0;
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
    for (size_t i = 0; i < n; ++i) dst[i] = lower(dst[i]);
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
    for (int k = 0; k < 5; ++k) if (lower(s[i + 1 + k]) != kw[k]) return 0;
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

/* The value of element attribute `name` (case-insensitive name), or NULL if absent.
 * A present attribute with no value reads as "". */
static const char *el_attr_value(const css_element *el, const char *name) {
    if (el->attrs == NULL) return NULL;
    for (size_t i = 0; i < el->nattrs; ++i) {
        if (el->attrs[i].name != NULL && ci_eq(el->attrs[i].name, name))
            return el->attrs[i].value != NULL ? el->attrs[i].value : "";
    }
    return NULL;
}

/* True if `v` ends with `suf` (non-empty), case-folded when ci. */
static int ends_with(const char *v, const char *suf, int ci) {
    size_t vl = strlen(v), fl = strlen(suf);
    if (fl == 0 || fl > vl) return 0;
    return span_eq(v + vl - fl, suf, fl, ci);
}

/* True if `v` is a whitespace-separated list containing the word `w` (non-empty),
 * case-folded when ci (the `~=` operator). */
static int has_word(const char *v, const char *w, int ci) {
    size_t wl = strlen(w);
    if (wl == 0) return 0;
    const char *p = v;
    while (*p != '\0') {
        while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '\f') ++p;
        const char *st = p;
        while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n' &&
               *p != '\r' && *p != '\f') ++p;
        if ((size_t)(p - st) == wl && span_eq(st, w, wl, ci)) return 1;
    }
    return 0;
}

/* True if attribute selector `am` matches element `el`. */
static int attr_matches(const css_attr_match *am, const css_element *el) {
    const char *v = el_attr_value(el, am->name);
    if (v == NULL) return 0;                 /* attribute absent */
    if (am->op == ATTR_PRESENT) return 1;
    size_t vl = strlen(v), nl = strlen(am->value);
    switch (am->op) {
        case ATTR_EQ:     return vl == nl && span_eq(v, am->value, nl, am->ci);
        case ATTR_TILDE:  return has_word(v, am->value, am->ci);
        case ATTR_PIPE:   return (vl == nl && span_eq(v, am->value, nl, am->ci)) ||
                                 (vl > nl && span_eq(v, am->value, nl, am->ci) && v[nl] == '-');
        case ATTR_CARET:  return nl > 0 && vl >= nl && span_eq(v, am->value, nl, am->ci);
        case ATTR_DOLLAR: return ends_with(v, am->value, am->ci);
        case ATTR_STAR:   return substr_match(v, am->value, am->ci);
        default:          return 0;
    }
}

/* True if one compound matches one element (no ancestor context). */
static int compound_matches(const css_compound *c, const css_element *el) {
    if (el == NULL) return 0;
    if (c->has_tag) { if (el->tag == NULL || !ci_eq(c->tag, el->tag)) return 0; }
    if (c->has_id)  { if (el->id == NULL || strcmp(c->id, el->id) != 0) return 0; }
    for (int i = 0; i < c->ncls; ++i) {
        int found = 0;
        for (size_t j = 0; j < el->nclasses; ++j) {
            if (el->classes[j] != NULL && strcmp(c->cls[i], el->classes[j]) == 0) {
                found = 1; break;
            }
        }
        if (!found) return 0;
    }
    for (int i = 0; i < c->nattrs; ++i)
        if (!attr_matches(&c->attrs[i], el)) return 0;
    return 1;
}

/* True if parts[0..k] match the ancestor chain ending at el (el matches parts[k]).
 * Right-to-left: child requires the immediate parent; descendant tries each ancestor
 * (the recursion backtracks). Bounded by k (<= CSS_MAX_COMPOUNDS) and the chain. */
static int complex_matches(const css_sel *sel, int k, const css_element *el) {
    if (!compound_matches(&sel->parts[k], el)) return 0;
    if (k == 0) return 1;
    if (sel->comb[k] == COMB_CHILD) {
        return (el->parent != NULL) && complex_matches(sel, k - 1, el->parent);
    }
    for (const css_element *anc = el->parent; anc != NULL; anc = anc->parent)
        if (complex_matches(sel, k - 1, anc)) return 1;
    return 0;
}

static int sel_matches_el(const css_sel *s, const css_element *el) {
    return complex_matches(s, s->nparts - 1, el);
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
            default: break;
        }
    }
}

css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         const char *inline_style, size_t inline_len) {
    css_style out = { -1, -1, CSS_ALIGN_UNSET, 0, 0, -1, -1, CSS_DISP_UNSET,
                      -1, CSS_JUSTIFY_UNSET, 0,
                      /* margin t,r,b,l / padding t,r,b,l / width / max_width */
                      CSS_LEN_UNSET, CSS_LEN_UNSET, CSS_LEN_UNSET, CSS_LEN_UNSET,
                      CSS_LEN_UNSET, CSS_LEN_UNSET, CSS_LEN_UNSET, CSS_LEN_UNSET,
                      CSS_LEN_UNSET, CSS_LEN_UNSET };
    int wi[P_NSLOTS], ws[P_NSLOTS], wo[P_NSLOTS];
    for (int k = 0; k < P_NSLOTS; ++k) { wi[k] = -1; ws[k] = -1; wo[k] = -1; }

    if (sheet != NULL && el != NULL) {
        for (size_t si = 0; si < sheet->nsels; ++si) {
            const css_sel *sel = &sheet->sels[si];
            if (!sel_matches_el(sel, el)) continue;
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
    css_element el = { tag, id, classes, nclasses, NULL, 0, NULL };
    return css_resolve_el(sheet, &el, inline_style, inline_len);
}

css_style css_parse_inline(const char *style, size_t len) {
    return css_resolve(NULL, NULL, NULL, NULL, 0, style, len);
}
