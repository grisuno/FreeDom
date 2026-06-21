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

/* Property slots. The enum value IS the css_style slot index used by apply(). */
enum { P_COLOR = 0, P_BG, P_ALIGN, P_FONTSIZE, P_WEIGHT, P_STYLE, P_DISPLAY, P_NSLOTS };

typedef struct css_decl {
    int prop;  /* P_* */
    int ival;  /* interpreted value (color packed / enum / scale / bool) */
} css_decl;

typedef struct css_sel {
    char tag[CSS_TOK_MAX];
    int  has_tag;
    char id[CSS_TOK_MAX];
    int  has_id;
    char cls[CSS_MAX_CLASSES_PER_SEL][CSS_TOK_MAX];
    int  ncls;
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

/* Case-insensitive substring test (used to drop any value carrying url(). */
static int ci_contains(const char *hay, const char *needle) {
    size_t nl = strlen(needle);
    if (nl == 0) return 1;
    for (const char *p = hay; *p != '\0'; ++p) {
        size_t i = 0;
        while (i < nl && p[i] != '\0' && lower(p[i]) == lower(needle[i])) ++i;
        if (i == nl) return 1;
    }
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
    if (ci_contains(v, "url(")) return -1;   /* never phone home */
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

/* Interprets one declaration span s[0,n) into *out. Returns 1 if it names a
 * supported property with a valid value. */
static int parse_one_decl(const char *s, size_t n, css_decl *out) {
    size_t c = 0;
    while (c < n && s[c] != ':') ++c;
    if (c >= n) return 0;  /* no colon */

    char prop[CSS_TOK_MAX];
    char val[CSS_TOK_MAX];
    if (copy_trim(s, 0, c, prop, sizeof prop) == (size_t)-1) return 0;
    if (copy_trim(s, c + 1, n, val, sizeof val) == (size_t)-1) return 0;
    if (prop[0] == '\0' || val[0] == '\0') return 0;
    for (char *p = prop; *p != '\0'; ++p) *p = lower(*p);

    int prop_id, ival;
    if (strcmp(prop, "color") == 0)                 { prop_id = P_COLOR;    ival = interp_color(val); }
    else if (strcmp(prop, "background-color") == 0 ||
             strcmp(prop, "background") == 0)        { prop_id = P_BG;       ival = interp_bg(val); }
    else if (strcmp(prop, "text-align") == 0)        { prop_id = P_ALIGN;    ival = interp_align(val); }
    else if (strcmp(prop, "font-size") == 0)         { prop_id = P_FONTSIZE; ival = interp_fontsize(val); }
    else if (strcmp(prop, "font-weight") == 0)       { prop_id = P_WEIGHT;   ival = interp_weight(val); }
    else if (strcmp(prop, "font-style") == 0)        { prop_id = P_STYLE;    ival = interp_style(val); }
    else if (strcmp(prop, "display") == 0)           { prop_id = P_DISPLAY;  ival = interp_display(val); }
    else return 0;

    if (ival < 0) return 0;  /* unsupported value */
    out->prop = prop_id;
    out->ival = ival;
    return 1;
}

/* Splits a ';'-separated declaration block into dst (up to cap). Returns count. */
static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap) {
    size_t count = 0, i = 0;
    while (i < n && count < cap) {
        size_t j = i;
        while (j < n && s[j] != ';') ++j;
        if (parse_one_decl(s + i, j - i, &dst[count])) ++count;
        i = (j < n) ? j + 1 : j;
    }
    return count;
}

/* Parses one compound selector span s[a,b) into *sel. Returns 1 if supported
 * (simple/compound only: type, .class, #id, *, no combinators). */
static int parse_selector(const char *s, size_t a, size_t b, css_sel *sel) {
    while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a;
    while (b > a && (s[b-1] == ' ' || s[b-1] == '\t' || s[b-1] == '\n' || s[b-1] == '\r')) --b;
    if (a >= b) return 0;

    /* any combinator or unsupported syntax => drop this selector. */
    for (size_t i = a; i < b; ++i) {
        char c = s[i];
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r' ||
            c == '>' || c == '+' || c == '~' || c == '[' || c == ']' ||
            c == ':' || c == '(' || c == ')') return 0;
    }

    memset(sel, 0, sizeof *sel);
    size_t i = a;
    if (s[i] == '*') {
        ++i;  /* universal: no type */
    } else if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')) {
        size_t k = 0;
        while (i < b && is_ident_ch(s[i])) {
            if (k + 1 < sizeof sel->tag) sel->tag[k++] = lower(s[i]);
            ++i;
        }
        sel->tag[k] = '\0';
        sel->has_tag = 1;
    } else if (s[i] != '.' && s[i] != '#') {
        return 0;
    }

    while (i < b) {
        if (s[i] == '.') {
            ++i;
            if (i >= b || !is_ident_ch(s[i])) return 0;
            if (sel->ncls >= CSS_MAX_CLASSES_PER_SEL) return 0;
            size_t k = 0;
            while (i < b && is_ident_ch(s[i])) {
                if (k + 1 < CSS_TOK_MAX) sel->cls[sel->ncls][k++] = s[i];
                ++i;
            }
            sel->cls[sel->ncls][k] = '\0';
            ++sel->ncls;
        } else if (s[i] == '#') {
            ++i;
            if (i >= b || !is_ident_ch(s[i]) || sel->has_id) return 0;
            size_t k = 0;
            while (i < b && is_ident_ch(s[i])) {
                if (k + 1 < sizeof sel->id) sel->id[k++] = s[i];
                ++i;
            }
            sel->id[k] = '\0';
            sel->has_id = 1;
        } else {
            return 0;
        }
    }

    sel->spec = 100 * (sel->has_id ? 1 : 0) + 10 * sel->ncls + (sel->has_tag ? 1 : 0);
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
        if (parse_selector(s, i, j, &tmp[got])) ++got;
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

static void parse_sheet(css_sheet *sh, const char *s, size_t n) {
    size_t i = 0;
    while (i < n) {
        while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r')) ++i;
        if (i >= n) break;
        if (s[i] == '@') { i = skip_at_rule(s, i, n); continue; }
        if (s[i] == '}') { ++i; continue; }  /* stray */

        size_t ss = i;
        while (i < n && s[i] != '{' && s[i] != '}') ++i;
        if (i >= n || s[i] != '{') { if (i < n && s[i] == '}') ++i; continue; }
        size_t se = i;     /* at '{' */
        ++i;
        size_t ds = i;
        while (i < n && s[i] != '}') ++i;
        size_t de = i;     /* at '}' or end */
        if (i < n) ++i;
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
    if (out == NULL) return CSS_ERR_NULL_ARG;
    css_sheet *sh = (css_sheet *)calloc(1, sizeof *sh);
    if (sh == NULL) return CSS_ERR_OOM;
    if (text != NULL) {
        if (len == 0) len = strlen(text);
        size_t clen = 0;
        char *clean = strip_comments(text, len, &clen);
        if (clean == NULL) { free(sh); return CSS_ERR_OOM; }
        parse_sheet(sh, clean, clen);
        free(clean);
    }
    *out = sh;
    return CSS_OK;
}

void css_free(css_sheet *s) {
    free(s);
}

static int sel_matches(const css_sel *s, const char *tag, const char *id,
                       const char *const *classes, size_t nc) {
    if (s->has_tag) { if (tag == NULL || !ci_eq(s->tag, tag)) return 0; }
    if (s->has_id)  { if (id == NULL || strcmp(s->id, id) != 0) return 0; }
    for (int i = 0; i < s->ncls; ++i) {
        int found = 0;
        for (size_t j = 0; j < nc; ++j) {
            if (classes[j] != NULL && strcmp(s->cls[i], classes[j]) == 0) { found = 1; break; }
        }
        if (!found) return 0;
    }
    return 1;
}

static void apply_decl(css_style *o, int *ws, int *wo, const css_decl *d,
                       int spec, int ord) {
    int slot = d->prop;
    if (spec > ws[slot] || (spec == ws[slot] && ord >= wo[slot])) {
        ws[slot] = spec;
        wo[slot] = ord;
        switch (d->prop) {
            case P_COLOR:    o->color = d->ival; break;
            case P_BG:       o->background = d->ival; break;
            case P_ALIGN:    o->text_align = (css_align)d->ival; break;
            case P_FONTSIZE: o->font_scale = d->ival; break;
            case P_WEIGHT:   o->bold = d->ival; break;
            case P_STYLE:    o->italic = d->ival; break;
            case P_DISPLAY:  o->display = (css_display)d->ival; break;
            default: break;
        }
    }
}

css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                      const char *const *classes, size_t nclasses,
                      const char *inline_style, size_t inline_len) {
    css_style out = { -1, -1, CSS_ALIGN_UNSET, 0, -1, -1, CSS_DISP_UNSET };
    int ws[P_NSLOTS], wo[P_NSLOTS];
    for (int k = 0; k < P_NSLOTS; ++k) { ws[k] = -1; wo[k] = -1; }

    if (sheet != NULL) {
        for (size_t si = 0; si < sheet->nsels; ++si) {
            const css_sel *sel = &sheet->sels[si];
            if (!sel_matches(sel, tag, id, classes, nclasses)) continue;
            size_t start = sheet->rules[sel->rule].start;
            size_t cnt = sheet->rules[sel->rule].count;
            for (size_t d = 0; d < cnt; ++d)
                apply_decl(&out, ws, wo, &sheet->decls[start + d], sel->spec, sel->order);
        }
    }

    if (inline_style != NULL) {
        if (inline_len == 0) inline_len = strlen(inline_style);
        css_decl tmp[CSS_INLINE_DECLS];
        size_t dn = interpret_decls(inline_style, inline_len, tmp, CSS_INLINE_DECLS);
        for (size_t d = 0; d < dn; ++d)
            apply_decl(&out, ws, wo, &tmp[d], CSS_INLINE_SPEC, INT_MAX);
    }

    return out;
}

css_style css_parse_inline(const char *style, size_t len) {
    return css_resolve(NULL, NULL, NULL, NULL, 0, style, len);
}
