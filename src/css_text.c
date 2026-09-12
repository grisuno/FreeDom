#include "css_text.h"
#include "css_decl.h"
#include "css.h"
#include "css_box.h"
#include "css_color.h"
#include "css_length.h"
#include "css_select.h"
#include "css_values.h"

#include <string.h>
#include <stdlib.h>

/* --- text-presentation extensions (Hito 23b-6) --- */

/* Maps one font-family name (a generic keyword or a common family) to a generic
 * css_font_family bucket; -1 if unrecognised. Case-insensitive; multi-word names
 * (e.g. "times new roman") are compared whole. */
static int ct_family_of(const char *name) {
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
        { "glass tty vt220", CSS_FF_MONO }, { "glass tty vt220 medium", CSS_FF_MONO },
        { "vt220", CSS_FF_MONO }, { "xterm", CSS_FF_MONO },
        { "terminus", CSS_FF_MONO }, { "liberation mono", CSS_FF_MONO },
        { "inconsolata", CSS_FF_MONO }, { "source code pro", CSS_FF_MONO },
        { "cursive", CSS_FF_CURSIVE }, { "comic sans ms", CSS_FF_CURSIVE },
        { "fantasy", CSS_FF_FANTASY }, { "impact", CSS_FF_FANTASY },
    };
    for (size_t i = 0; i < sizeof tbl / sizeof tbl[0]; ++i)
        if (csel_ci_eq(name, tbl[i].n)) return tbl[i].f;
    return -1;
}

/* font-family: the first recognised name in the comma-separated stack wins (its
 * generic bucket). Quotes are stripped. url() defensively dropped. -1 if none known. */
int ct_interp_fontfamily(const char *v) {
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
        int f = ct_family_of(buf);
        if (f >= 0) return f;
    }
    return -1;
}

int ct_interp_texttransform(const char *v) {
    if (csel_ci_eq(v, "none"))       return CSS_TT_NONE;
    if (csel_ci_eq(v, "uppercase"))  return CSS_TT_UPPERCASE;
    if (csel_ci_eq(v, "lowercase"))  return CSS_TT_LOWERCASE;
    if (csel_ci_eq(v, "capitalize")) return CSS_TT_CAPITALIZE;
    return -1;  /* full-width/full-size-kana/...: out of scope, fail closed */
}

/* opacity: a unitless 0..1 alpha (or a percentage), mapped to 0..100 and clamped.
 * A negative or unparseable value is dropped (-1). */
int ct_interp_opacity(const char *v) {
    double num;
    const char *end;
    if (!cl_number(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    double pct;
    if (end[0] == '%' && end[1] == '\0') pct = num;
    else if (end[0] == '\0')             pct = num * 100.0;
    else return -1;
    return css_round_clamp(pct, 0, 100);
}

int ct_interp_valign(const char *v) {
    if (csel_ci_eq(v, "baseline")) return CSS_VA_BASELINE;
    if (csel_ci_eq(v, "sub"))      return CSS_VA_SUB;
    if (csel_ci_eq(v, "super"))    return CSS_VA_SUPER;
    if (csel_ci_eq(v, "middle"))   return CSS_VA_MIDDLE;
    if (csel_ci_eq(v, "top"))      return CSS_VA_TOP;
    if (csel_ci_eq(v, "bottom"))   return CSS_VA_BOTTOM;
    /* `text-top`/`text-bottom` align with the parent's CONTENT box rather than the
     * line box (CSS 2.1 section 10.8.1). This engine has one line box per line and
     * no separate parent content edge to align against, so the two collapse onto
     * top/bottom -- the same edge, measured on the box it does have. Dropping them
     * instead left the element on the baseline, which is a different place
     * entirely; 17 declarations on one corpus page. */
    if (csel_ci_eq(v, "text-top"))    return CSS_VA_TOP;
    if (csel_ci_eq(v, "text-bottom")) return CSS_VA_BOTTOM;
    /* The <length-percentage> production is a different KIND of value and gets its
     * own slot: see expand_valign. */
    return -1;
}

/* vertical-align (CSS 2.1 section 10.8.1) has two productions: a keyword, and a
 * <length-percentage> baseline SHIFT (positive raises). They are different kinds of
 * value, so they take different slots -- a keyword enum cannot also hold a signed
 * length -- and both are emitted on every declaration so that whichever the author
 * wrote CLEARS the other. Without that, `vertical-align: middle` under a
 * lower-specificity `vertical-align: -2px` would apply both.
 *
 * The percentage resolves against the element's own line-height, which is the one
 * basis in CSS Values that is neither a containing block nor the element's border
 * box, so it has its own pct slot. Measured: jkanime's icon font sets `.255em` on
 * every glyph, and the whole declaration was dropped. */
int ct_expand_valign(const char *val, css_decl *dst, int cap) {
    if (cap < 3) return 0;
    int kw = ct_interp_valign(val);
    int shift = CSS_LEN_UNSET, pm = 0, emil = 0;
    if (kw < 0) {
        if (!cb_interp_lp(val, 0, 1, &shift, &pm)) return 0;
        emil = cb_value_em_milli(val);
        kw = CSS_VA_UNSET;
    }
    dst[0].prop = P_VALIGN;        dst[0].ival = kw;
    dst[1].prop = P_VALIGN_SHIFT;  dst[1].ival = shift; dst[1].emil = emil;
    dst[2].prop = P_PCT_FIRST + CSS_PCT_VALIGN; dst[2].ival = pm;
    return 3;
}

/* transition-property value encoding: -1 = unset, 0 = none, 1 = all,
 * 2 = opacity, 3 = transform. Other values not yet supported. */
int ct_interp_transition_property(const char *v) {
    if (csel_ci_eq(v, "none"))  return 0;
    if (csel_ci_eq(v, "all"))   return 1;
    if (csel_ci_eq(v, "opacity"))    return 2;
    if (csel_ci_eq(v, "transform"))  return 3;
    return -1;
}

int ct_interp_whitespace(const char *v) {
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
int ct_interp_tabsize(const char *v) {
    double num;
    const char *end;
    if (!cl_number(v, &num, &end)) return -1;
    while (*end == ' ' || *end == '\t') ++end;
    if (*end != '\0') return -1;  /* units/lengths dropped; only bare number */
    int n = css_round_clamp(num, 0, 64);
    return (n > 0) ? n : -1;  /* 0 or unparseable -> unset */
}

/* text-decoration-style: solid/wavy/dotted/dashed/double. -1 if unknown. */
int ct_interp_textdeco_style(const char *v) {
    if (csel_ci_eq(v, "solid"))  return CSS_TDS_SOLID;
    if (csel_ci_eq(v, "double")) return CSS_TDS_DOUBLE;
    if (csel_ci_eq(v, "dotted")) return CSS_TDS_DOTTED;
    if (csel_ci_eq(v, "dashed")) return CSS_TDS_DASHED;
    if (csel_ci_eq(v, "wavy"))   return CSS_TDS_WAVY;
    return -1;
}

/* text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length
 * (px -> px, em/rem x16). -1 if unsupported (negative, %, etc -> dropped). */
int ct_interp_textdeco_thickness(const char *v) {
    if (csel_ci_eq(v, "from-font")) return 0;
    int px;
    if (!cb_interp_len(v, 0, &px) || px < 0) return -1;
    return px;
}

/* aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>`
 * (auto fallback). Stores both numerator and denominator x1000 (for sub-integer
 * ratios like 1.5 -> 1500/1000). Returns 1 with *num and *den set, 0 if unsupported.
 * A bare number 1.5 is stored as 1500/1000; 16/9 as 16000/9000;
 * auto / unparseable -> 0 (unset). */
int ct_interp_aspect_ratio(const char *v, int *num, int *den) {
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
        if (!cl_number(buf, &nv, &ne) || *ne != '\0') return 1;   /* fail -> unset */
        if (!cl_number(nend, &dv, &de) || *de != '\0' || dv <= 0.0) return 1;
        *num = css_round_clamp(nv * 1000.0, 1, CSS_LEN_MAX);
        *den = css_round_clamp(dv * 1000.0, 1, CSS_LEN_MAX);
        return 1;
    }
    /* Bare number: treat as w/h = N/1 */
    double nv;
    const char *ne;
    if (!cl_number(buf, &nv, &ne) || *ne != '\0' || nv <= 0.0) return 1;
    *num = css_round_clamp(nv * 1000.0, 1, CSS_LEN_MAX);
    *den = 1000;
    return 1;
}

/* direction: ltr/rtl. -1 if unknown. */
int ct_interp_direction(const char *v) {
    if (csel_ci_eq(v, "ltr")) return CSS_DIR_LTR;
    if (csel_ci_eq(v, "rtl")) return CSS_DIR_RTL;
    return -1;
}

static int ct_liststyle_kw(const char *t) {
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

/* A <counter-style> name this engine has no glyph set for.
 *
 * CSS Counter Styles 3 section 7.1 is explicit: a counter style that cannot be used
 * falls back to `decimal`, it does not make the declaration invalid. So
 * `list-style-type: persian` numbers the list in decimal -- which is what every
 * engine does when it lacks the style -- instead of dropping the declaration and
 * leaving the list with whatever marker a lower-specificity rule set. The name must
 * still LOOK like an identifier, so junk keeps failing closed. */
static int ct_liststyle_unknown_name(const char *t) {
    if (t[0] == '\0') return 0;
    for (const char *p = t; *p != '\0'; ++p) {
        char c = csel_lower_ch(*p);
        if (!((c >= 'a' && c <= 'z') || c == '-' || (*p >= '0' && *p <= '9'))) return 0;
    }
    return 1;
}

/* list-style-type, or the type token of the list-style shorthand: the first
 * recognised keyword wins. url() (a list-style-image) is dropped: never fetch. */
int ct_interp_liststyle(const char *v) {
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
        int ls = ct_liststyle_kw(tok);
        if (ls >= 0) return ls;
        /* An identifier this engine has no glyph set for is `decimal`, not a
         * parse error (CSS Counter Styles 3 section 7.1). `inside`/`outside` and
         * `none` are handled by liststyle_kw / the position longhand, so what
         * reaches here is a counter-style name. */
        if (ct_liststyle_unknown_name(tok)) return CSS_LS_DECIMAL;
    }
    return -1;
}

/* letter-spacing / word-spacing: "normal" -> 0, else a signed length (px/em/0),
 * clamped to [-CSS_SPACING_MAX, CSS_SPACING_MAX]. Returns 1 with *out set, 0 if
 * the value is unsupported (%/vw/calc/bare number -> dropped, fail closed). */
int ct_interp_spacing(const char *v, int *out) {
    if (csel_ci_eq(v, "normal")) { *out = 0; return 1; }
    int px;
    if (!cb_interp_len(v, 0, &px)) return 0;
    if (px > CSS_SPACING_MAX) px = CSS_SPACING_MAX;
    if (px < -CSS_SPACING_MAX) px = -CSS_SPACING_MAX;
    *out = px;
    return 1;
}

int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val) {
    int o;
    if (cap < 1 || !ct_interp_spacing(val, &o)) return 0;
    dst[0].prop = slot;
    dst[0].ival = o;
    return 1;
}

/* text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is
 * ignored) and an optional color, in any order. "none" emits an explicit no-shadow.
 * Needs at least dx and dy or the whole declaration is dropped (fail closed). When no
 * color is given it defaults to black. url() dropped: never fetch. Writes the three
 * contiguous P_SHADOW_* slots; offsets clamped to [-CSS_SHADOW_MAX, CSS_SHADOW_MAX]. */
int ct_expand_shadow(const char *val, css_decl *dst, int cap) {
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
    while (cb_next_ws_token(&p, tok, sizeof tok)) {
        int px;
        if (cb_interp_len(tok, 0, &px)) { if (nlen < 3) lens[nlen++] = px; }
        else if (!have_color) { int cv = cv_parse_color(tok); if (cv != -1) { color = cv; have_color = 1; } }
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

