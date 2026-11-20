/* css_import -- @import prelude reader (spec/css_import.md). Pure: no I/O, no
 * allocation, no global state. Every read is bounded by len. */
#include "css_import.h"

#include <stdio.h>
#include <string.h>

static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; }

static char lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c; }

/* Case-insensitive match of the ASCII keyword kw at s[i, e). */
static int kw_at(const char *s, size_t i, size_t e, const char *kw) {
    size_t n = strlen(kw);
    if (e - i < n) return 0;
    for (size_t k = 0; k < n; ++k)
        if (lower(s[i + k]) != kw[k]) return 0;
    return 1;
}

static int is_ident_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
        || c == '-' || c == '_' || (unsigned char)c >= 0x80;
}

/* Skips whitespace and comments; an unterminated comment runs to e. */
static size_t skip_ws(const char *s, size_t i, size_t e) {
    for (;;) {
        while (i < e && is_ws(s[i])) ++i;
        if (i + 1 < e && s[i] == '/' && s[i + 1] == '*') {
            size_t j = i + 2;
            while (j + 1 < e && !(s[j] == '*' && s[j + 1] == '/')) ++j;
            i = (j + 1 < e) ? j + 2 : e;
            continue;
        }
        return i;
    }
}

/* Past the string that opens at s[i] (a quote), or (size_t)-1 when it does not
 * terminate before e or a newline (a CSS bad-string). */
static size_t skip_string(const char *s, size_t i, size_t e) {
    char q = s[i];
    for (size_t j = i + 1; j < e; ++j) {
        if (s[j] == '\\') { if (++j >= e) return (size_t)-1; continue; }
        if (s[j] == '\n' || s[j] == '\r' || s[j] == '\f') return (size_t)-1;
        if (s[j] == q) return j + 1;
    }
    return (size_t)-1;
}

/* Copies s[a, b) trimmed into dst; -1 when it does not fit. */
static int copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap) {
    while (a < b && is_ws(s[a])) ++a;
    while (b > a && is_ws(s[b - 1])) --b;
    if (b - a >= cap) return -1;
    memcpy(dst, s + a, b - a);
    dst[b - a] = '\0';
    return 0;
}

/* Copies the body of the string opening at s[a] (quotes stripped, escapes kept
 * verbatim except an escaped quote). Returns the index past it or (size_t)-1. */
static size_t read_string(const char *s, size_t a, size_t e, char *dst, size_t cap) {
    size_t end = skip_string(s, a, e);
    if (end == (size_t)-1) return end;
    size_t n = 0;
    for (size_t j = a + 1; j + 1 < end; ++j) {
        char c = s[j];
        if (c == '\\' && j + 2 < end) c = s[++j];
        if (n + 1 >= cap) return (size_t)-1;
        dst[n++] = c;
    }
    dst[n] = '\0';
    return end;
}

/* Past the ')' that closes the '(' at s[i], skipping strings; (size_t)-1 if none. */
static size_t match_paren(const char *s, size_t i, size_t e) {
    int depth = 0;
    for (size_t j = i; j < e; ++j) {
        if (s[j] == '"' || s[j] == '\'') {
            size_t k = skip_string(s, j, e);
            if (k == (size_t)-1) return k;
            j = k - 1;
        } else if (s[j] == '(') {
            ++depth;
        } else if (s[j] == ')') {
            if (--depth == 0) return j + 1;
        }
    }
    return (size_t)-1;
}

/* Parses one import prelude s[a, b) (after "@import", before ';') into im.
 * Returns 0, or -1 when the import is invalid (ignored by the caller). */
static int parse_prelude(const char *s, size_t a, size_t b, ci_import *im) {
    memset(im, 0, sizeof *im);
    for (size_t j = a; j < b; ++j)
        if (s[j] == '{' || s[j] == '}') return -1;
    size_t i = skip_ws(s, a, b);
    if (i >= b) return -1;
    if (s[i] == '"' || s[i] == '\'') {
        i = read_string(s, i, b, im->url, sizeof im->url);
        if (i == (size_t)-1) return -1;
    } else if (kw_at(s, i, b, "url(")) {
        size_t j = skip_ws(s, i + 4, b);
        if (j < b && (s[j] == '"' || s[j] == '\'')) {
            j = read_string(s, j, b, im->url, sizeof im->url);
            if (j == (size_t)-1) return -1;
            j = skip_ws(s, j, b);
            if (j >= b || s[j] != ')') return -1;
            i = j + 1;
        } else {
            size_t k = j;
            while (k < b && s[k] != ')' && !is_ws(s[k]) && s[k] != '"' && s[k] != '\''
                   && s[k] != '(')
                ++k;
            size_t close = skip_ws(s, k, b);
            if (close >= b || s[close] != ')') return -1;
            if (k - j >= sizeof im->url) return -1;
            memcpy(im->url, s + j, k - j);
            im->url[k - j] = '\0';
            i = close + 1;
        }
    } else {
        return -1;
    }
    if (im->url[0] == '\0') return -1;

    i = skip_ws(s, i, b);
    if (kw_at(s, i, b, "layer") && (i + 5 >= b || !is_ident_char(s[i + 5]))) {
        im->has_layer = 1;
        size_t j = i + 5;
        if (j < b && s[j] == '(') {
            size_t k = match_paren(s, j, b);
            if (k == (size_t)-1) return -1;
            if (copy_trim(s, j + 1, k - 1, im->layer, sizeof im->layer) != 0) return -1;
            if (im->layer[0] == '\0') return -1;
            j = k;
        }
        i = skip_ws(s, j, b);
    }
    if (kw_at(s, i, b, "supports(")) {
        size_t k = match_paren(s, i + 8, b);
        if (k == (size_t)-1) return -1;
        if (copy_trim(s, i + 9, k - 1, im->supports, sizeof im->supports) != 0) return -1;
        if (im->supports[0] == '\0') return -1;
        i = skip_ws(s, k, b);
    }
    if (kw_at(s, i, b, "layer") || kw_at(s, i, b, "supports(")) return -1;  /* out of order */
    if (copy_trim(s, i, b, im->media, sizeof im->media) != 0) return -1;
    return 0;
}

size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap) {
    if (css == NULL || out == NULL || cap == 0) return 0;
    size_t n = 0, i = 0;
    while (n < cap) {
        i = skip_ws(css, i, len);
        if (i >= len || css[i] != '@') break;
        size_t k = i + 1;
        while (k < len && is_ident_char(css[k])) ++k;
        int is_import = (k - i - 1 == 6) && kw_at(css, i + 1, k, "import");
        int is_skip = ((k - i - 1 == 7) && kw_at(css, i + 1, k, "charset"))
                   || ((k - i - 1 == 5) && kw_at(css, i + 1, k, "layer"));
        if (!is_import && !is_skip) break;
        /* Find the ';' that ends this statement at nesting depth 0, outside strings.
         * A '{' at depth 0 means a block rule (an @layer block, or a broken import
         * whose recovery swallows the rest): the prelude is over. */
        size_t j = k, semi = (size_t)-1;
        int depth = 0, stop = 0;
        while (j < len) {
            char c = css[j];
            if (c == '"' || c == '\'') {
                size_t q = skip_string(css, j, len);
                if (q == (size_t)-1) { stop = 1; break; }
                j = q;
                continue;
            }
            if (c == '(') ++depth;
            else if (c == ')') { if (depth > 0) --depth; }
            else if ((c == '{' || c == '}') && depth == 0) { stop = 1; break; }
            else if (c == ';' && depth == 0) { semi = j; break; }
            ++j;
        }
        if (stop || semi == (size_t)-1) break;
        if (is_import && parse_prelude(css, k, semi, &out[n]) == 0) ++n;
        i = semi + 1;
    }
    return n;
}

int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap) {
    if (im == NULL || open == NULL || close == NULL || ocap == 0 || ccap == 0) return -1;
    size_t on = 0, cn = 0;
    open[0] = '\0';
    close[0] = '\0';
    const char *fmt[3] = { NULL, NULL, NULL };
    const char *arg[3] = { NULL, NULL, NULL };
    int parts = 0;
    if (im->has_layer) {
        fmt[parts] = (im->layer[0] != '\0') ? "@layer %s {" : "@layer%s {";
        arg[parts++] = im->layer;
    }
    if (im->supports[0] != '\0') { fmt[parts] = "@supports (%s) {"; arg[parts++] = im->supports; }
    if (im->media[0] != '\0') { fmt[parts] = "@media %s {"; arg[parts++] = im->media; }
    for (int p = 0; p < parts; ++p) {
        size_t space = ocap - on;
        int r = snprintf(open + on, space, fmt[p], arg[p]);
        if (r < 0 || (size_t)r >= space) { open[0] = '\0'; return -1; }
        on += (size_t)r;
        if (cn + 1 >= ccap) { open[0] = '\0'; close[0] = '\0'; return -1; }
        close[cn++] = '}';
        close[cn] = '\0';
    }
    return 0;
}

int ci_balanced(const char *css, size_t len) {
    if (css == NULL) return 0;
    long depth = 0;
    for (size_t i = 0; i < len; ++i) {
        char c = css[i];
        if (c == '/' && i + 1 < len && css[i + 1] == '*') {
            size_t j = i + 2;
            while (j + 1 < len && !(css[j] == '*' && css[j + 1] == '/')) ++j;
            if (j + 1 >= len) return 0;
            i = j + 1;
        } else if (c == '"' || c == '\'') {
            size_t j = skip_string(css, i, len);
            if (j == (size_t)-1) return 0;
            i = j - 1;
        } else if (c == '{') {
            ++depth;
        } else if (c == '}') {
            if (--depth < 0) return 0;
        }
    }
    return depth == 0;
}
