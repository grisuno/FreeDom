/*
 * css_counter -- implementation (spec/css_counter.md). Pure and bounded: every
 * input is hostile stylesheet text, every output is capped and NUL-terminated.
 */
#include "css_counter.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CNT_SEQ_MARK "\x01seq:"
#define CNT_ITEM_END '\x1e'
#define CNT_FIELD_SEP '\x1f'
#define CNT_VALUE_LIMIT 1000000000L
#define CNT_STR_MAX 192

unsigned cnt_hash(const char *name, size_t len) {
    unsigned hsh = 2166136261u;
    for (size_t i = 0; i < len; ++i) {
        hsh ^= (unsigned char)name[i];
        hsh *= 16777619u;
    }
    return hsh != 0 ? hsh : 1u;
}

static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; }

static int is_ident_start(unsigned char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' || c == '-' || c >= 0x80;
}
static int is_ident_char(unsigned char c) { return is_ident_start(c) || (c >= '0' && c <= '9'); }

static int ci_eq(const char *a, const char *b) {
    for (; *a != '\0' && *b != '\0'; ++a, ++b) {
        char x = (*a >= 'A' && *a <= 'Z') ? (char)(*a + 32) : *a;
        char y = (*b >= 'A' && *b <= 'Z') ? (char)(*b + 32) : *b;
        if (x != y) return 0;
    }
    return *a == *b;
}

/* A <custom-ident> usable as a counter name: identifier syntax, not a CSS-wide
 * keyword or `none`, and short enough to be a name. */
static int valid_name(const char *s, size_t n) {
    if (n == 0 || n >= CNT_NAME_MAX) return 0;
    if (!is_ident_start((unsigned char)s[0])) return 0;
    if (s[0] == '-' && (n == 1 || (s[1] >= '0' && s[1] <= '9'))) return 0;
    for (size_t i = 0; i < n; ++i)
        if (!is_ident_char((unsigned char)s[i])) return 0;
    char t[CNT_NAME_MAX];
    memcpy(t, s, n);
    t[n] = '\0';
    return !(ci_eq(t, "none") || ci_eq(t, "inherit") || ci_eq(t, "initial") ||
             ci_eq(t, "unset") || ci_eq(t, "revert") || ci_eq(t, "revert-layer") ||
             ci_eq(t, "default"));
}

int cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL]) {
    const char *p = val;
    int n = 0;
    while (is_ws(*p)) ++p;
    if (*p == '\0') return -1;
    for (;;) {
        while (is_ws(*p)) ++p;
        if (*p == '\0') break;
        const char *s = p;
        while (*p != '\0' && !is_ws(*p)) ++p;
        size_t len = (size_t)(p - s);
        if (len == 4 && n == 0 && strncmp(s, "none", 4) == 0) {
            const char *q = p;
            while (is_ws(*q)) ++q;
            return (*q == '\0') ? 0 : -1;
        }
        if (!valid_name(s, len) || n >= CNT_MAX_DECL) return -1;
        out[n].name = cnt_hash(s, len);
        out[n].value = dflt;
        const char *q = p;
        while (is_ws(*q)) ++q;
        if (*q == '-' || *q == '+' || (*q >= '0' && *q <= '9')) {
            const char *ns = q;
            ++q;
            while (*q >= '0' && *q <= '9') ++q;
            if (*q != '\0' && !is_ws(*q)) return -1;
            char buf[16];
            size_t bl = (size_t)(q - ns);
            if (bl == 0 || bl >= sizeof buf || (bl == 1 && (*ns == '-' || *ns == '+'))) return -1;
            memcpy(buf, ns, bl);
            buf[bl] = '\0';
            long v = strtol(buf, NULL, 10);
            if (v > CNT_VALUE_LIMIT || v < -CNT_VALUE_LIMIT) return -1;
            out[n].value = (int)v;
            p = q;
        }
        ++n;
    }
    return n;
}

/* --- number formatting ------------------------------------------------------ */

static size_t put(char *out, size_t cap, size_t o, const char *s) {
    for (; *s != '\0' && o + 1 < cap; ++s) out[o++] = *s;
    return o;
}

static void utf8_put(char *buf, unsigned cp) {
    if (cp < 0x80) { buf[0] = (char)cp; buf[1] = '\0'; }
    else if (cp < 0x800) {
        buf[0] = (char)(0xC0 | (cp >> 6)); buf[1] = (char)(0x80 | (cp & 0x3F)); buf[2] = '\0';
    } else if (cp < 0x10000) {
        buf[0] = (char)(0xE0 | (cp >> 12)); buf[1] = (char)(0x80 | ((cp >> 6) & 0x3F));
        buf[2] = (char)(0x80 | (cp & 0x3F)); buf[3] = '\0';
    } else {
        buf[0] = (char)(0xF0 | (cp >> 18)); buf[1] = (char)(0x80 | ((cp >> 12) & 0x3F));
        buf[2] = (char)(0x80 | ((cp >> 6) & 0x3F)); buf[3] = (char)(0x80 | (cp & 0x3F)); buf[4] = '\0';
    }
}

size_t cnt_format(int style, long value, char *out, size_t cap) {
    if (cap == 0) return 0;
    char tmp[64];
    tmp[0] = '\0';
    switch (style) {
    case CNT_NONE: break;
    case CNT_DISC:   snprintf(tmp, sizeof tmp, "\xE2\x80\xA2"); break;
    case CNT_CIRCLE: snprintf(tmp, sizeof tmp, "\xE2\x97\xA6"); break;
    case CNT_SQUARE: snprintf(tmp, sizeof tmp, "\xE2\x96\xAA"); break;
    case CNT_DECIMAL_ZERO:
        if (value > -10 && value < 10)
            snprintf(tmp, sizeof tmp, "%s0%ld", value < 0 ? "-" : "", value < 0 ? -value : value);
        else snprintf(tmp, sizeof tmp, "%ld", value);
        break;
    case CNT_LOWER_ROMAN: case CNT_UPPER_ROMAN: {
        if (value < 1 || value > 3999) { snprintf(tmp, sizeof tmp, "%ld", value); break; }
        static const int vals[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };
        static const char *const up[] = { "M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I" };
        static const char *const lo[] = { "m","cm","d","cd","c","xc","l","xl","x","ix","v","iv","i" };
        size_t o = 0;
        long n = value;
        for (int i = 0; i < 13; ++i)
            while (n >= vals[i]) {
                o = put(tmp, sizeof tmp, o, style == CNT_UPPER_ROMAN ? up[i] : lo[i]);
                n -= vals[i];
            }
        tmp[o] = '\0';
        break;
    }
    case CNT_LOWER_ALPHA: case CNT_UPPER_ALPHA: {
        if (value < 1) { snprintf(tmp, sizeof tmp, "%ld", value); break; }
        char rev[16];
        int k = 0;
        long n = value;
        while (n > 0 && k < (int)sizeof rev) {
            rev[k++] = (char)((style == CNT_UPPER_ALPHA ? 'A' : 'a') + (n - 1) % 26);
            n = (n - 1) / 26;
        }
        size_t o = 0;
        while (k > 0 && o + 1 < sizeof tmp) tmp[o++] = rev[--k];
        tmp[o] = '\0';
        break;
    }
    case CNT_LOWER_GREEK:
        if (value < 1 || value > 24) { snprintf(tmp, sizeof tmp, "%ld", value); break; }
        utf8_put(tmp, value <= 17 ? (unsigned)(0x3B1 + value - 1) : (unsigned)(0x3C3 + value - 18));
        break;
    default: snprintf(tmp, sizeof tmp, "%ld", value); break;
    }
    size_t o = put(out, cap, 0, tmp);
    out[o] = '\0';
    return o;
}

static int style_of(const char *name) {
    static const struct { const char *n; int s; } T[] = {
        { "decimal", CNT_DECIMAL }, { "decimal-leading-zero", CNT_DECIMAL_ZERO },
        { "lower-roman", CNT_LOWER_ROMAN }, { "upper-roman", CNT_UPPER_ROMAN },
        { "lower-alpha", CNT_LOWER_ALPHA }, { "lower-latin", CNT_LOWER_ALPHA },
        { "upper-alpha", CNT_UPPER_ALPHA }, { "upper-latin", CNT_UPPER_ALPHA },
        { "lower-greek", CNT_LOWER_GREEK }, { "disc", CNT_DISC }, { "circle", CNT_CIRCLE },
        { "square", CNT_SQUARE }, { "none", CNT_NONE },
    };
    for (size_t i = 0; i < sizeof T / sizeof *T; ++i)
        if (ci_eq(name, T[i].n)) return T[i].s;
    return CNT_DECIMAL;   /* Counter Styles 3 section 7.1 */
}

/* --- content parsing -------------------------------------------------------- */

typedef struct { char *o; size_t n, cap; int bad; } sink;

static void sk_char(sink *k, char c) {
    if (k->n + 1 >= k->cap) { k->bad = 1; return; }
    k->o[k->n++] = c;
}
static void sk_str(sink *k, const char *s) { for (; *s != '\0'; ++s) sk_char(k, *s); }

/* A quoted string at p (p[0] is the quote). Writes the decoded body into dst (sanitised:
 * control bytes dropped so the item framing stays unambiguous). Returns the position just
 * past the closing quote, or NULL when unterminated. */
static const char *read_string(const char *p, char *dst, size_t cap) {
    char q = *p++;
    size_t o = 0;
    while (*p != '\0' && *p != q) {
        unsigned cp = (unsigned char)*p;
        if (*p == '\\') {
            ++p;
            if (*p == '\0') return NULL;
            if (*p == '\n') { ++p; continue; }
            if ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') || (*p >= 'A' && *p <= 'F')) {
                unsigned v = 0;
                int d = 0;
                while (d < 6 && ((*p >= '0' && *p <= '9') || (*p >= 'a' && *p <= 'f') ||
                                 (*p >= 'A' && *p <= 'F'))) {
                    v = v * 16 + (unsigned)((*p <= '9') ? *p - '0' : (*p | 32) - 'a' + 10);
                    ++p; ++d;
                }
                if (is_ws(*p)) ++p;
                cp = (v == 0 || v > 0x10FFFF || (v >= 0xD800 && v <= 0xDFFF)) ? 0xFFFD : v;
                char u[5];
                utf8_put(u, cp);
                for (const char *c = u; *c != '\0'; ++c)
                    if (o + 1 < cap && (unsigned char)*c >= 0x20) dst[o++] = *c;
                continue;
            }
            cp = (unsigned char)*p;
        }
        if (cp >= 0x20 && o + 1 < cap) dst[o++] = (char)cp;
        else if (cp >= 0x20) return NULL;
        ++p;
    }
    if (*p != q) return NULL;
    dst[o] = '\0';
    return p + 1;
}

/* Splits the argument text [a, b) at top-level commas into up to `max` trimmed fields. */
static int split_args(const char *a, const char *b, char (*f)[CNT_STR_MAX], int max) {
    int n = 0;
    const char *p = a;
    while (p <= b) {
        while (p < b && is_ws(*p)) ++p;
        char tmp[CNT_STR_MAX];
        if (p < b && (*p == '"' || *p == '\'')) {
            const char *e = read_string(p, tmp, sizeof tmp - 1);
            if (e == NULL || e > b) return -1;
            if (n >= max) return -1;
            /* A leading quote marks a string field (tmp is at most CNT_STR_MAX - 1 long). */
            f[n][0] = '"';
            memcpy(f[n] + 1, tmp, strlen(tmp) + 1 > CNT_STR_MAX - 1 ? CNT_STR_MAX - 2 : strlen(tmp) + 1);
            f[n][CNT_STR_MAX - 1] = '\0';
            ++n;
            p = e;
            while (p < b && is_ws(*p)) ++p;
        } else {
            const char *s = p;
            while (p < b && *p != ',') ++p;
            const char *e = p;
            while (e > s && is_ws(e[-1])) --e;
            if (e == s || (size_t)(e - s) >= CNT_STR_MAX || n >= max) return -1;
            memcpy(f[n], s, (size_t)(e - s));
            f[n][e - s] = '\0';
            ++n;
        }
        if (p >= b) break;
        if (*p != ',') return -1;
        ++p;
    }
    return n;
}

int cnt_is_marker(const char *s) {
    return s != NULL && strncmp(s, CNT_SEQ_MARK, sizeof CNT_SEQ_MARK - 1) == 0;
}

static int has_counter_fn(const char *v) {
    for (const char *p = v; *p != '\0'; ++p) {
        if ((p[0] | 32) == 'c' && (p[1] | 32) == 'o' && (p[2] | 32) == 'u' && (p[3] | 32) == 'n' &&
            (p[4] | 32) == 't' && (p[5] | 32) == 'e' && (p[6] | 32) == 'r' &&
            (p[7] == '(' || ((p[7] | 32) == 's' && p[8] == '(')))
            return 1;
    }
    return 0;
}

int cnt_parse_content(const char *val, char *out, size_t cap) {
    if (!has_counter_fn(val)) return 0;
    sink k = { out, 0, cap, 0 };
    sk_str(&k, CNT_SEQ_MARK);
    int saw_counter = 0, items = 0;
    const char *p = val;
    for (;;) {
        while (is_ws(*p)) ++p;
        if (*p == '\0') break;
        if (++items > 32) return -1;
        if (*p == '"' || *p == '\'') {
            char tmp[CNT_STR_MAX];
            p = read_string(p, tmp, sizeof tmp);
            if (p == NULL) return -1;
            sk_char(&k, 'S'); sk_str(&k, tmp); sk_char(&k, CNT_ITEM_END);
            continue;
        }
        const char *w = p;
        while (*p != '\0' && !is_ws(*p) && *p != '(') ++p;
        size_t wl = (size_t)(p - w);
        char word[24];
        if (wl == 0 || wl >= sizeof word) return -1;
        memcpy(word, w, wl);
        word[wl] = '\0';
        if (*p != '(') {
            if (ci_eq(word, "open-quote")) { sk_char(&k, 'S'); sk_str(&k, "\xE2\x80\x9C"); sk_char(&k, CNT_ITEM_END); }
            else if (ci_eq(word, "close-quote")) { sk_char(&k, 'S'); sk_str(&k, "\xE2\x80\x9D"); sk_char(&k, CNT_ITEM_END); }
            else if (!(ci_eq(word, "no-open-quote") || ci_eq(word, "no-close-quote"))) return -1;
            continue;
        }
        const char *args = p + 1;
        const char *e = args;
        char q = 0;
        while (*e != '\0' && (q != 0 || *e != ')')) {
            if (q != 0) { if (*e == '\\' && e[1] != '\0') ++e; else if (*e == q) q = 0; }
            else if (*e == '"' || *e == '\'') q = *e;
            ++e;
        }
        if (*e != ')') return -1;
        char f[3][CNT_STR_MAX];
        int na = split_args(args, e, f, 3);
        if (na < 1) return -1;
        if (ci_eq(word, "counter")) {
            if (na > 2 || f[0][0] == '"' || !valid_name(f[0], strlen(f[0]))) return -1;
            if (na == 2 && f[1][0] == '"') return -1;
            sk_char(&k, 'C'); sk_str(&k, f[0]); sk_char(&k, CNT_FIELD_SEP);
            sk_char(&k, (char)('0' + (na == 2 ? style_of(f[1]) : CNT_DECIMAL)));
            sk_char(&k, CNT_ITEM_END);
            saw_counter = 1;
        } else if (ci_eq(word, "counters")) {
            if (na < 2 || f[0][0] == '"' || f[1][0] != '"' || !valid_name(f[0], strlen(f[0]))) return -1;
            if (na == 3 && f[2][0] == '"') return -1;
            sk_char(&k, 'N'); sk_str(&k, f[0]); sk_char(&k, CNT_FIELD_SEP);
            sk_str(&k, f[1] + 1); sk_char(&k, CNT_FIELD_SEP);
            sk_char(&k, (char)('0' + (na == 3 ? style_of(f[2]) : CNT_DECIMAL)));
            sk_char(&k, CNT_ITEM_END);
            saw_counter = 1;
        } else if (ci_eq(word, "attr")) {
            if (na != 1 || f[0][0] == '"') return -1;
            for (const char *c = f[0]; *c != '\0'; ++c)
                if (!(is_ident_char((unsigned char)*c) || *c == ':' || *c == '.')) return -1;
            sk_char(&k, 'A'); sk_str(&k, f[0]); sk_char(&k, CNT_ITEM_END);
        } else return -1;
        p = e + 1;
    }
    if (!saw_counter) return 0;
    if (k.bad || k.n + 1 > cap) return -1;
    out[k.n] = '\0';
    return 1;
}

/* --- document-order state --------------------------------------------------- */

typedef struct { unsigned name; int value; int depth; } cnt_inst;

struct cnt_state {
    size_t   n;
    cnt_inst a[CNT_MAX_INSTANCES];
};

cnt_state *cnt_state_new(void) { return (cnt_state *)calloc(1, sizeof(cnt_state)); }
void cnt_state_free(cnt_state *s) { free(s); }

static cnt_inst *top_of(cnt_state *s, unsigned name) {
    for (size_t i = s->n; i > 0; --i)
        if (s->a[i - 1].name == name) return &s->a[i - 1];
    return NULL;
}

static int clampv(long v) {
    return (int)(v > CNT_VALUE_LIMIT ? CNT_VALUE_LIMIT : v < -CNT_VALUE_LIMIT ? -CNT_VALUE_LIMIT : v);
}

void cnt_reset(cnt_state *s, int depth, const cnt_decl *d, int n) {
    if (s == NULL || d == NULL) return;
    for (int i = 0; i < n; ++i) {
        cnt_inst *t = top_of(s, d[i].name);
        if (t != NULL && t->depth == depth) { t->value = d[i].value; continue; }
        if (s->n >= CNT_MAX_INSTANCES) continue;
        s->a[s->n].name = d[i].name;
        s->a[s->n].value = d[i].value;
        s->a[s->n].depth = depth;
        ++s->n;
    }
}

void cnt_increment(cnt_state *s, int depth, const cnt_decl *d, int n) {
    if (s == NULL || d == NULL) return;
    for (int i = 0; i < n; ++i) {
        cnt_inst *t = top_of(s, d[i].name);
        if (t == NULL) {
            if (s->n >= CNT_MAX_INSTANCES) continue;
            s->a[s->n].name = d[i].name;
            s->a[s->n].value = 0;
            s->a[s->n].depth = depth;
            t = &s->a[s->n++];
        }
        t->value = clampv((long)t->value + (long)d[i].value);
    }
}

void cnt_leave(cnt_state *s, int depth) {
    if (s == NULL) return;
    while (s->n > 0 && s->a[s->n - 1].depth >= depth) --s->n;
}

size_t cnt_resolve(const cnt_state *s, const char *marker, cnt_attr_fn attr, void *ctx,
                   char *out, size_t cap) {
    if (cap == 0) return 0;
    sink k = { out, 0, cap, 0 };
    if (!cnt_is_marker(marker)) {
        sk_str(&k, marker == NULL ? "" : marker);
        out[k.n] = '\0';
        return k.n;
    }
    const char *p = marker + sizeof CNT_SEQ_MARK - 1;
    while (*p != '\0') {
        char type = *p++;
        const char *e = strchr(p, CNT_ITEM_END);
        if (e == NULL) break;
        char item[CNT_STR_MAX * 2];
        size_t il = (size_t)(e - p);
        if (il >= sizeof item) il = sizeof item - 1;
        memcpy(item, p, il);
        item[il] = '\0';
        p = e + 1;
        if (type == 'S') { sk_str(&k, item); continue; }
        if (type == 'A') {
            const char *v = (attr != NULL) ? attr(ctx, item) : NULL;
            if (v != NULL) sk_str(&k, v);
            continue;
        }
        char *sep1 = strchr(item, CNT_FIELD_SEP);
        if (sep1 == NULL) continue;
        *sep1 = '\0';
        unsigned name = cnt_hash(item, strlen(item));
        char num[40];
        if (type == 'C') {
            int st = sep1[1] - '0';
            long v = 0;
            if (s != NULL)
                for (size_t i = s->n; i > 0; --i)
                    if (s->a[i - 1].name == name) { v = s->a[i - 1].value; break; }
            cnt_format(st, v, num, sizeof num);
            sk_str(&k, num);
        } else if (type == 'N') {
            char *sep2 = strchr(sep1 + 1, CNT_FIELD_SEP);
            if (sep2 == NULL) continue;
            *sep2 = '\0';
            int st = sep2[1] - '0';
            int first = 1;
            if (s != NULL)
                for (size_t i = 0; i < s->n; ++i) {
                    if (s->a[i].name != name) continue;
                    if (!first) sk_str(&k, sep1 + 1);
                    first = 0;
                    cnt_format(st, s->a[i].value, num, sizeof num);
                    sk_str(&k, num);
                }
            if (first) { cnt_format(st, 0, num, sizeof num); sk_str(&k, num); }
        }
    }
    out[k.n] = '\0';
    return k.n;
}
