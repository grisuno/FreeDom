/*
 * css_nest -- implementation (spec/css_nest.md). Pure and bounded: the input is hostile
 * stylesheet text; the output never exceeds CN_MAX_OUT_FACTOR x input + CN_OUT_SLACK and
 * recursion never exceeds CN_MAX_DEPTH.
 */
#include "css_nest.h"

#include <stdlib.h>
#include <string.h>

#define CN_STACK_MAX 32

typedef struct cn_out {
    char  *b;
    size_t n, cap, lim;
    int    oom;
} cn_out;

/* Appends s[0,n). Past the bound the rest is dropped (fail closed): what was emitted
 * is a prefix of whole rules only because callers write a rule in one put_rule. */
static int put(cn_out *o, const char *s, size_t n) {
    if (o->oom) return -1;
    if (n > o->lim - o->n) return -1;
    if (o->n + n + 1 > o->cap) {
        size_t nc = o->cap ? o->cap : 256;
        while (nc < o->n + n + 1) nc *= 2;
        if (nc > o->lim + 1) nc = o->lim + 1;
        char *nb = (char *)realloc(o->b, nc);
        if (nb == NULL) { o->oom = 1; return -1; }
        o->b = nb;
        o->cap = nc;
    }
    memcpy(o->b + o->n, s, n);
    o->n += n;
    o->b[o->n] = '\0';
    return 0;
}

static int puts_(cn_out *o, const char *s) { return put(o, s, strlen(s)); }

/* Drops everything written after `mark` (a rule that did not fit is dropped whole). */
static void rewind_to(cn_out *o, size_t mark) {
    o->n = mark;
    if (o->b != NULL) o->b[mark] = '\0';
}

static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; }

/* Index just past the string or escape starting at i (s[i] is a quote or a backslash). */
static size_t skip_quoted(const char *s, size_t i, size_t n) {
    if (s[i] == '\\') return (i + 2 <= n) ? i + 2 : n;
    char q = s[i++];
    while (i < n && s[i] != q) {
        if (s[i] == '\\' && ++i >= n) break;   /* an escape as the last byte */
        if (s[i] == '\n') break;                /* an unterminated string ends at the line */
        ++i;
    }
    return (i < n) ? i + 1 : n;
}

/* Index of the '}' closing the block whose body starts at i, or n when unbalanced. */
static size_t block_end(const char *s, size_t i, size_t n) {
    int d = 1;
    while (i < n) {
        char c = s[i];
        if (c == '"' || c == '\'' || c == '\\') { i = skip_quoted(s, i, n); continue; }
        if (c == '{') ++d;
        else if (c == '}' && --d == 0) return i;
        ++i;
    }
    return n;
}

/* 1 iff s[i] is escaped: an odd run of backslashes ends right before it (from a). */
static int escaped_at(const char *s, size_t a, size_t i) {
    size_t k = 0;
    while (i > a + k && s[i - 1 - k] == '\\') ++k;
    return (int)(k & 1u);
}

/* Trims whitespace, but never an escaped one: `a\ ` keeps its space, or the re-emitted
 * backslash would escape whatever the output puts after it. A span left ending in an
 * unpaired backslash (only at the end of the input) is emptied: re-emitted, it would
 * escape the brace that closes its block. */
static void trim(const char *s, size_t *a, size_t *b) {
    size_t a0 = *a;
    while (*a < *b && is_ws(s[*a])) ++*a;
    while (*b > *a && is_ws(s[*b - 1]) && !escaped_at(s, a0, *b - 1)) --*b;
    if (*b > *a && s[*b - 1] == '\\' && !escaped_at(s, a0, *b - 1)) { *b = *a; return; }
    /* A bad string (cut by a newline or the end of the input) invalidates what holds it,
     * as in the CSS tokenizer; re-joined with a space it would become a good one and
     * swallow the braces after it. */
    for (size_t i = *a; i < *b; ++i) {
        if (s[i] == '\0') { *b = *a; return; }    /* selectors are kept as C strings */
        if (s[i] == '\\') { ++i; continue; }
        if (s[i] != '"' && s[i] != '\'') continue;
        char q = s[i];
        size_t j = i + 1;
        while (j < *b && s[j] != q && s[j] != '\n' && s[j] != '\0') j += (s[j] == '\\') ? 2 : 1;
        if (j >= *b || s[j] != q) { *b = *a; return; }
        i = j;
    }
}

/* One item of a block body: a declaration [a,b) (open == 0) or a nested block with
 * prelude [a,b) and body [open+1, close). *next is where scanning resumes. */
typedef struct cn_item { size_t a, b, open, close, next; } cn_item;

static int next_item(const char *s, size_t i, size_t n, cn_item *it) {
    while (i < n && (is_ws(s[i]) || s[i] == ';')) ++i;
    if (i >= n) return 0;
    if (s[i] == '}') {                       /* a stray closer: skip it */
        it->a = it->b = i;
        it->open = it->close = 0;
        it->next = i + 1;
        return 1;
    }
    size_t a = i;
    int custom = (i + 1 < n && s[i] == '-' && s[i + 1] == '-');
    int paren = 0;
    while (i < n) {
        char c = s[i];
        if (c == '"' || c == '\'' || c == '\\') { i = skip_quoted(s, i, n); continue; }
        if (c == '(' || c == '[') ++paren;
        else if ((c == ')' || c == ']') && paren > 0) --paren;
        else if (paren == 0 && c == ';') break;
        else if (c == '{') {
            if (custom) { i = block_end(s, i + 1, n); if (i < n) ++i; continue; }
            it->a = a;
            it->b = i;
            it->open = i;
            it->close = block_end(s, i + 1, n);
            it->next = (it->close < n) ? it->close + 1 : n;
            return 1;
        } else if (c == '}') break;   /* the enclosing block's closer: braces dominate */
        ++i;
    }
    it->a = a;
    it->b = i;
    it->open = it->close = 0;
    it->next = (i < n && s[i] == ';') ? i + 1 : i;
    if (it->next == a) it->next = a + 1;     /* always advance */
    return 1;
}

/* Lower-case at-rule name after '@' at s[a], into nm (truncated). */
static void at_name(const char *s, size_t a, size_t b, char *nm, size_t cap) {
    size_t k = 0, i = a + 1;
    while (i < b && k + 1 < cap) {
        char c = s[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '-')) break;
        nm[k++] = (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c;
        ++i;
    }
    nm[k] = '\0';
}

/* Conditional group rules: their body holds rules (or, nested, declarations). */
static int at_is_group(const char *nm) {
    static const char *const g[] = { "media", "supports", "container", "layer", "scope",
                                     "document", "-moz-document", "starting-style" };
    for (size_t k = 0; k < sizeof g / sizeof g[0]; ++k)
        if (strcmp(nm, g[k]) == 0) return 1;
    return 0;
}

/* --- selectors ----------------------------------------------------------------- */

typedef struct cn_sels {
    char  *s[CN_MAX_SELECTORS];
    size_t n;
} cn_sels;

static void sels_free(cn_sels *l) {
    for (size_t k = 0; k < l->n; ++k) free(l->s[k]);
    l->n = 0;
}

/* Splits s[a,b) at top-level commas into trimmed spans. Returns the count, or -1 when
 * more than `max`. */
static int split_list(const char *s, size_t a, size_t b, size_t *sa, size_t *sb, int max) {
    int k = 0, paren = 0;
    size_t start = a;
    for (size_t i = a; i <= b; ++i) {
        if (i < b) {
            char c = s[i];
            if (c == '"' || c == '\'' || c == '\\') { i = skip_quoted(s, i, b) - 1; continue; }
            if (c == '(' || c == '[') { ++paren; continue; }
            if ((c == ')' || c == ']') && paren > 0) { --paren; continue; }
            if (c != ',' || paren > 0) continue;
        }
        size_t x = start, y = i;
        trim(s, &x, &y);
        if (y > x) {
            if (k >= max) return -1;
            sa[k] = x;
            sb[k] = y;
            ++k;
        }
        start = i + 1;
    }
    return k;
}

static char *dup_span(const char *s, size_t n) {
    if (n == (size_t)-1) return NULL;
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

/* The child selector c[0,cn) resolved against parent p: every '&' outside a string
 * replaced by p, or `p c` when there is none. */
static char *resolve_one(const char *p, const char *c, size_t cn) {
    size_t pl = strlen(p), amps = 0;
    for (size_t i = 0; i < cn; ++i) {
        if (c[i] == '"' || c[i] == '\'' || c[i] == '\\') { i = skip_quoted(c, i, cn) - 1; continue; }
        if (c[i] == '&') ++amps;
    }
    if (amps == 0) {
        char *d = (char *)malloc(pl + 1 + cn + 1);
        if (d == NULL) return NULL;
        memcpy(d, p, pl);
        d[pl] = ' ';
        memcpy(d + pl + 1, c, cn);
        d[pl + 1 + cn] = '\0';
        return d;
    }
    if (amps > 64 || pl > 4096) return NULL;
    size_t len = cn - amps + amps * pl;
    char *d = (char *)malloc(len + 1);
    if (d == NULL) return NULL;
    size_t o = 0;
    for (size_t i = 0; i < cn; ++i) {
        if (c[i] == '"' || c[i] == '\'' || c[i] == '\\') {
            size_t e = skip_quoted(c, i, cn);
            memcpy(d + o, c + i, e - i);
            o += e - i;
            i = e - 1;
            continue;
        }
        if (c[i] == '&') { memcpy(d + o, p, pl); o += pl; }
        else d[o++] = c[i];
    }
    d[o] = '\0';
    return d;
}

/* The selector list s[a,b) resolved against parents (NULL = top level) into out.
 * 0, or -1 when the cross product exceeds CN_MAX_SELECTORS or memory runs out. */
static int resolve_list(const char *s, size_t a, size_t b, const cn_sels *parents,
                        cn_sels *out) {
    size_t sa[CN_MAX_SELECTORS], sb[CN_MAX_SELECTORS];
    out->n = 0;
    int k = split_list(s, a, b, sa, sb, CN_MAX_SELECTORS);
    if (k <= 0) return -1;
    if (parents == NULL) {
        for (int j = 0; j < k; ++j) {
            char *d = dup_span(s + sa[j], sb[j] - sa[j]);
            if (d == NULL) { sels_free(out); return -1; }
            out->s[out->n++] = d;
        }
        return 0;
    }
    if (parents->n * (size_t)k > CN_MAX_SELECTORS) return -1;
    for (size_t pi = 0; pi < parents->n; ++pi)
        for (int j = 0; j < k; ++j) {
            char *d = resolve_one(parents->s[pi], s + sa[j], sb[j] - sa[j]);
            if (d == NULL) { sels_free(out); return -1; }
            out->s[out->n++] = d;
        }
    return 0;
}

static int put_sels(cn_out *o, const cn_sels *l) {
    for (size_t k = 0; k < l->n; ++k) {
        if (k > 0 && put(o, ",", 1) != 0) return -1;
        if (puts_(o, l->s[k]) != 0) return -1;
    }
    return 0;
}

/* --- flattening ---------------------------------------------------------------- */

static void flatten_top(cn_out *o, const char *s, size_t a, size_t b, int depth);

/* A style rule's body [a,b) under the resolved selectors `sels`: its own declarations
 * as one rule, then each nested rule / hoisted group rule in order. */
static void flatten_style(cn_out *o, const char *s, size_t a, size_t b, const cn_sels *sels,
                          int depth) {
    /* Pass 1: the rule's own declarations, written whole or not at all. */
    size_t mark = o->n;
    int any = 0;
    cn_item it;
    for (size_t i = a; i < b && next_item(s, i, b, &it); i = it.next) {
        if (it.open != 0 || it.b <= it.a) continue;
        size_t x = it.a, y = it.b;
        trim(s, &x, &y);
        if (y <= x) continue;
        if (!any) {
            if (put_sels(o, sels) != 0 || put(o, "{", 1) != 0) goto undo;
            any = 1;
        } else if (put(o, ";", 1) != 0) goto undo;
        if (put(o, s + x, y - x) != 0) goto undo;
    }
    if (any && put(o, "}", 1) != 0) goto undo;
    goto nested;
undo:
    rewind_to(o, mark);
    return;
nested:
    if (depth >= CN_MAX_DEPTH) return;
    for (size_t i = a; i < b && next_item(s, i, b, &it); i = it.next) {
        if (it.open == 0) continue;
        size_t x = it.a, y = it.b;
        trim(s, &x, &y);
        if (y <= x) continue;
        size_t m2 = o->n;
        if (s[x] == '@') {
            char nm[32];
            at_name(s, x, y, nm, sizeof nm);
            if (!at_is_group(nm)) continue;  /* nothing else is meaningful inside a rule */
            if (put(o, s + x, y - x) != 0 || put(o, "{", 1) != 0) { rewind_to(o, m2); break; }
            flatten_style(o, s, it.open + 1, it.close, sels, depth + 1);
            if (put(o, "}", 1) != 0) { rewind_to(o, m2); break; }
            continue;
        }
        cn_sels child;
        child.n = 0;
        if (resolve_list(s, x, y, sels, &child) != 0) continue;   /* fail closed */
        flatten_style(o, s, it.open + 1, it.close, &child, depth + 1);
        sels_free(&child);
    }
}

/* Top-level (or group-rule) content [a,b): rules, group rules, statements. */
static void flatten_top(cn_out *o, const char *s, size_t a, size_t b, int depth) {
    cn_item it;
    for (size_t i = a; i < b && next_item(s, i, b, &it); i = it.next) {
        size_t x = it.a, y = it.b;
        trim(s, &x, &y);
        if (y <= x) continue;
        if (it.open == 0) {
            /* Only an at-rule statement (`@import ...;`, `@layer a,b;`) survives here. */
            if (s[x] == '@' && (put(o, s + x, y - x) != 0 || put(o, ";", 1) != 0)) return;
            continue;
        }
        size_t m = o->n;
        if (s[x] == '@') {
            char nm[32];
            at_name(s, x, y, nm, sizeof nm);
            if (!at_is_group(nm)) {
                size_t e = (it.close < b) ? it.close : b;
                if (put(o, s + x, y - x) != 0 || put(o, "{", 1) != 0 ||
                    put(o, s + it.open + 1, e - (it.open + 1)) != 0 || put(o, "}", 1) != 0) {
                    rewind_to(o, m);
                    return;
                }
                continue;
            }
            if (depth >= CN_MAX_DEPTH) continue;
            if (put(o, s + x, y - x) != 0 || put(o, "{", 1) != 0) { rewind_to(o, m); return; }
            flatten_top(o, s, it.open + 1, it.close, depth + 1);
            if (put(o, "}", 1) != 0) { rewind_to(o, m); return; }
            continue;
        }
        cn_sels sels;
        sels.n = 0;
        if (resolve_list(s, x, y, NULL, &sels) != 0) continue;
        flatten_style(o, s, it.open + 1, it.close, &sels, depth + 1);
        sels_free(&sels);
    }
}

cn_status cn_flatten(const char *css, size_t len, char **out, size_t *out_len) {
    if (css == NULL || out == NULL || out_len == NULL) return CN_ERR_ARG;
    *out = NULL;
    *out_len = 0;
    if (len > ((size_t)-1 - CN_OUT_SLACK) / CN_MAX_OUT_FACTOR) return CN_ERR_ARG;
    cn_out o = { NULL, 0, 0, len * CN_MAX_OUT_FACTOR + CN_OUT_SLACK, 0 };
    if (put(&o, "", 0) != 0 || o.b == NULL) {
        o.b = (char *)calloc(1, 1);
        if (o.b == NULL) return CN_ERR_OOM;
    }
    flatten_top(&o, css, 0, len, 0);
    if (o.oom) { free(o.b); return CN_ERR_OOM; }
    if (o.b == NULL) { o.b = (char *)calloc(1, 1); if (o.b == NULL) return CN_ERR_OOM; }
    *out = o.b;
    *out_len = o.n;
    return CN_OK;
}

/* --- detection ----------------------------------------------------------------- */

/* Walks with the SAME item scanner as the flattener, so the two never disagree on where
 * a block starts or ends (a second hand-written scanner did, on hostile text). */
static int has_in(const char *s, size_t a, size_t b, int style, int depth) {
    if (depth >= CN_STACK_MAX) return 1;    /* let cn_flatten bound it */
    cn_item it;
    for (size_t i = a; i < b && next_item(s, i, b, &it); i = it.next) {
        if (it.open == 0) continue;
        if (style) return 1;
        size_t x = it.a, y = it.b;
        trim(s, &x, &y);
        if (y <= x) continue;
        if (s[x] == '@') {
            char nm[32];
            at_name(s, x, y, nm, sizeof nm);
            if (at_is_group(nm) && has_in(s, it.open + 1, it.close, 0, depth + 1)) return 1;
            continue;
        }
        if (has_in(s, it.open + 1, it.close, 1, depth + 1)) return 1;
    }
    return 0;
}

int cn_has_nesting(const char *css, size_t len) {
    if (css == NULL) return 0;
    return has_in(css, 0, len, 0, 0);
}
