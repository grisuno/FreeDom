/*
 * css_atrule -- @supports evaluation and @layer ranks. See include/css_atrule.h
 * and spec/css_atrule.md.
 */
#include "css_atrule.h"
#include "css_select.h"  /* csel_lower_ch, csel_ident_ch */

#include <string.h>

/* Scratch size for one declaration or selector handed to the caller. Longer
 * text cannot be a declaration this engine accepts (CSS_URL_MAX-sized values)
 * and is answered false. */
#define CAR_TEXT_MAX 1024u

static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

static size_t skip_ws(const char *s, size_t i, size_t b) {
    while (i < b && is_ws(s[i])) ++i;
    return i;
}

/* Case-insensitive keyword at s[i] followed by a non-identifier byte. */
static int keyword_at(const char *s, size_t i, size_t b, const char *kw) {
    size_t n = strlen(kw);
    if (b - i < n) return 0;
    for (size_t k = 0; k < n; ++k)
        if (csel_lower_ch(s[i + k]) != kw[k]) return 0;
    return i + n == b || !csel_ident_ch(s[i + n]);
}

/* Index of the ')' matching the '(' at s[open], or b when unbalanced. Quoted text
 * is opaque. */
static size_t close_paren(const char *s, size_t open, size_t b) {
    int depth = 0;
    char q = 0;
    for (size_t i = open; i < b; ++i) {
        char c = s[i];
        if (q) {
            if (c == '\\' && i + 1 < b) ++i;
            else if (c == q) q = 0;
        } else if (c == '"' || c == '\'') {
            q = c;
        } else if (c == '(') {
            ++depth;
        } else if (c == ')' && --depth == 0) {
            return i;
        }
    }
    return b;
}

/* Copies s[a,b) trimmed into dst (cap bytes, NUL-terminated); 0 if it does not fit
 * or is empty. lower != 0 lowercases it. */
static int copy_trimmed(const char *s, size_t a, size_t b, char *dst, size_t cap, int lower) {
    a = skip_ws(s, a, b);
    while (b > a && is_ws(s[b - 1])) --b;
    if (b == a || b - a >= cap) return 0;
    for (size_t k = 0; k < b - a; ++k) dst[k] = lower ? csel_lower_ch(s[a + k]) : s[a + k];
    dst[b - a] = '\0';
    return 1;
}

static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,
                          int depth, int *ok);

/* True when s[a,b) (inside a pair of parens) is a declaration `prop: value`
 * rather than a nested condition. */
static int eval_declaration(const char *s, size_t a, size_t b, const car_ops *ops, int *ok) {
    size_t i = skip_ws(s, a, b);
    size_t n0 = i;
    while (i < b && (csel_ident_ch(s[i]) || s[i] == '-')) ++i;
    if (i == n0) { *ok = 0; return 0; }
    size_t n1 = i;
    i = skip_ws(s, i, b);
    if (i >= b || s[i] != ':') { *ok = 0; return 0; }
    char prop[CAR_LAYER_NAME_MAX];
    char val[CAR_TEXT_MAX];
    if (!copy_trimmed(s, n0, n1, prop, sizeof prop, 1)) return 0;
    if (!copy_trimmed(s, i + 1, b, val, sizeof val, 0)) return 0;
    if (prop[0] == '-' && prop[1] == '-') return 1;
    return ops != NULL && ops->decl_ok != NULL && ops->decl_ok(ops->ctx, prop, val) != 0;
}

/* One <supports-in-parens> starting at s[*i]; advances *i past it. */
static int eval_in_parens(const char *s, size_t *i, size_t b, const car_ops *ops,
                          int depth, int *ok) {
    size_t p = skip_ws(s, *i, b);
    if (p >= b) { *ok = 0; return 0; }
    if (s[p] == '(') {
        size_t e = close_paren(s, p, b);
        if (e >= b) { *ok = 0; return 0; }
        *i = e + 1;
        size_t in = skip_ws(s, p + 1, e);
        /* A nested condition starts with '(' or `not`/`selector(`; otherwise it is
         * a declaration. */
        if (in < e && (s[in] == '(' || keyword_at(s, in, e, "not") ||
                       keyword_at(s, in, e, "selector")))
            return eval_condition(s, p + 1, e, ops, depth + 1, ok);
        return eval_declaration(s, p + 1, e, ops, ok);
    }
    /* A function form: selector(...) is answered; any other is false. */
    size_t f = p;
    while (f < b && (csel_ident_ch(s[f]) || s[f] == '-')) ++f;
    if (f == p || f >= b || s[f] != '(') { *ok = 0; return 0; }
    size_t e = close_paren(s, f, b);
    if (e >= b) { *ok = 0; return 0; }
    *i = e + 1;
    if (!keyword_at(s, p, f, "selector") || f - p != 8) return 0;
    char sel[CAR_TEXT_MAX];
    if (!copy_trimmed(s, f + 1, e, sel, sizeof sel, 0)) return 0;
    return ops != NULL && ops->selector_ok != NULL && ops->selector_ok(ops->ctx, sel) != 0;
}

static int eval_condition(const char *s, size_t a, size_t b, const car_ops *ops,
                          int depth, int *ok) {
    if (depth > CAR_MAX_DEPTH) { *ok = 0; return 0; }
    size_t i = skip_ws(s, a, b);
    if (keyword_at(s, i, b, "not")) {
        i += 3;
        int v = eval_in_parens(s, &i, b, ops, depth, ok);
        if (skip_ws(s, i, b) != b) *ok = 0;
        return !v;
    }
    int v = eval_in_parens(s, &i, b, ops, depth, ok);
    int mode = 0;   /* 1 = and, 2 = or: CSS forbids mixing them unparenthesised */
    for (;;) {
        i = skip_ws(s, i, b);
        if (i >= b || !*ok) break;
        int m;
        if (keyword_at(s, i, b, "and")) { m = 1; i += 3; }
        else if (keyword_at(s, i, b, "or")) { m = 2; i += 2; }
        else { *ok = 0; break; }
        if (mode != 0 && mode != m) { *ok = 0; break; }
        mode = m;
        int w = eval_in_parens(s, &i, b, ops, depth, ok);
        v = (m == 1) ? (v && w) : (v || w);
    }
    return v;
}

int car_supports(const char *s, size_t a, size_t b, const car_ops *ops) {
    if (s == NULL || a >= b) return 0;
    int ok = 1;
    int v = eval_condition(s, a, b, ops, 0, &ok);
    return ok && v;
}

int car_layer_rank(car_layers *L, const char *name, size_t len) {
    if (L == NULL) return CAR_MAX_LAYERS;
    if (len == 0) {
        if (L->n >= CAR_MAX_LAYERS) return CAR_MAX_LAYERS;
        /* Synthetic name no author text can spell (a leading space). */
        char *d = L->name[L->n];
        int k = L->anon++;
        size_t o = 0;
        d[o++] = ' ';
        do { d[o++] = (char)('0' + k % 10); k /= 10; } while (k > 0 && o + 1 < CAR_LAYER_NAME_MAX);
        d[o] = '\0';
        return (int)++L->n;
    }
    if (name == NULL || len >= CAR_LAYER_NAME_MAX) return CAR_MAX_LAYERS;
    for (size_t k = 0; k < L->n; ++k)
        if (strlen(L->name[k]) == len && memcmp(L->name[k], name, len) == 0)
            return (int)k + 1;
    if (L->n >= CAR_MAX_LAYERS) return CAR_MAX_LAYERS;
    memcpy(L->name[L->n], name, len);
    L->name[L->n][len] = '\0';
    return (int)++L->n;
}

int car_effective_spec(int spec, int layer, int important) {
    if (spec < 0) spec = 0;
    if (spec > 0xFFFF) spec = 0xFFFF;
    if (layer < 0) layer = 0;
    if (layer > CAR_MAX_LAYERS) layer = CAR_MAX_LAYERS;
    int rank = (layer == 0) ? CAR_MAX_LAYERS + 1 : layer;
    if (important) rank = CAR_MAX_LAYERS + 1 - rank;
    return (rank << 16) | spec;
}
