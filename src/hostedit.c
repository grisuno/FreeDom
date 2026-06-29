/*
 * hostedit — implementation: pure, I/O-free host-list line builder.
 *
 * No allocation, no globals, no I/O. The hostile input (a hostname derived from the
 * current page URL) is validated fail-closed before any line is produced.
 */

#include "hostedit.h"

#include <string.h>

static char he_lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c;
}

static int is_label_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '-';
}

/* True if host is a plausible registrable hostname (see he_make_line contract). */
static int valid_host(const char *host, size_t n) {
    if (n == 0 || n > HE_MAX_HOST) return 0;
    if (host[0] == '.' || host[n - 1] == '.') return 0;  /* no empty edge label */
    size_t label = 0;
    for (size_t i = 0; i < n; ++i) {
        char c = host[i];
        if (c == '.') {
            if (label == 0) return 0;                    /* "a..b" / leading dot */
            label = 0;
            continue;
        }
        if (!is_label_char(c)) return 0;                 /* rejects / : @ ? # ws ctrl */
        if (c == '-' && (label == 0 || i + 1 == n || host[i + 1] == '.'))
            return 0;                                    /* label may not edge on '-' */
        if (++label > 63) return 0;                      /* DNS label limit */
    }
    return 1;
}

he_status he_make_line(const char *host, char *out, size_t cap) {
    if (host == NULL || out == NULL) return HE_ERR_NULL_ARG;
    size_t n = strlen(host);
    if (!valid_host(host, n)) return HE_ERR_INVALID_HOST;
    if (cap < n + 2) return HE_ERR_RANGE;                /* host + '\n' + '\0' */
    for (size_t i = 0; i < n; ++i) out[i] = he_lower(host[i]);
    out[n] = '\n';
    out[n + 1] = '\0';
    return HE_OK;
}

/* Case-insensitive compare of a token [ts,te) against host (NUL-terminated), with a
 * single trailing dot on the token ignored (a FQDN root). */
static int token_eq_host(const char *ts, const char *te, const char *host) {
    size_t tl = (size_t)(te - ts);
    if (tl > 0 && ts[tl - 1] == '.') --tl;               /* ignore one root dot */
    size_t i = 0;
    for (; i < tl; ++i) {
        if (host[i] == '\0') return 0;
        if (he_lower(ts[i]) != he_lower(host[i])) return 0;
    }
    return host[i] == '\0';
}

/* True if the token looks like an IPv4 dotted-quad / contains only digits and dots
 * (matches hostblock's is_ip_token spirit: such a leading token is the ignored IP). */
static int is_ip_token(const char *ts, const char *te) {
    int saw_digit = 0;
    for (const char *q = ts; q < te; ++q) {
        if (*q == '.') continue;
        if (*q < '0' || *q > '9') return 0;
        saw_digit = 1;
    }
    return saw_digit;
}

/* Visits each domain token (non-comment, non-IP) of a hosts-format text in document
 * order, calling fn(ts, tl, ctx). If fn returns nonzero, iteration stops and he_scan
 * returns 1; otherwise 0. Single source of the line/token tokenisation. */
static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx) {
    const char *p = text;
    while (*p != '\0') {
        const char *line = p;
        while (*p != '\0' && *p != '\n') ++p;
        const char *end = p;
        if (*p == '\n') ++p;
        for (const char *q = line; q < end; ++q)
            if (*q == '#') { end = q; break; }           /* strip comment */

        const char *q = line;
        while (q < end) {
            while (q < end && (*q == ' ' || *q == '\t' || *q == '\r' ||
                               *q == '\f' || *q == '\v')) ++q;
            const char *ts = q;
            while (q < end && !(*q == ' ' || *q == '\t' || *q == '\r' ||
                                *q == '\f' || *q == '\v')) ++q;
            if (q == ts) continue;
            if (is_ip_token(ts, q)) continue;            /* ignore the "0.0.0.0" field */
            if (fn(ts, (size_t)(q - ts), ctx)) return 1;
        }
    }
    return 0;
}

static int has_host_cb(const char *ts, size_t tl, void *ctx) {
    return token_eq_host(ts, ts + tl, (const char *)ctx);
}

int he_text_has_host(const char *text, const char *host) {
    if (text == NULL || host == NULL || host[0] == '\0') return 0;
    return he_scan(text, has_host_cb, (void *)host);
}

/* Lowercase substring search: 1 if needle (lowercased) occurs in [hs,he). */
static int contains_ci(const char *hs, size_t hl, const char *needle) {
    size_t nl = strlen(needle);
    if (nl == 0) return 1;
    if (nl > hl) return 0;
    for (size_t i = 0; i + nl <= hl; ++i) {
        size_t k = 0;
        for (; k < nl; ++k)
            if (he_lower(hs[i + k]) != he_lower(needle[k])) break;
        if (k == nl) return 1;
    }
    return 0;
}

static int starts_with_ci(const char *hs, size_t hl, const char *pfx) {
    size_t pl = strlen(pfx);
    if (pl > hl) return 0;
    for (size_t k = 0; k < pl; ++k)
        if (he_lower(hs[k]) != he_lower(pfx[k])) return 0;
    return 1;
}

struct suggest_ctx {
    const char *query;
    int prefix_only;                       /* pass 1 collects prefix matches only */
    char (*results)[HE_MAX_HOST + 1];
    int max;
    int n;
};

static int suggest_cb(const char *ts, size_t tl, void *vctx) {
    struct suggest_ctx *c = (struct suggest_ctx *)vctx;
    if (tl == 0 || tl > HE_MAX_HOST) return 0;           /* skip unstorable hosts */
    if (c->prefix_only) {
        if (!starts_with_ci(ts, tl, c->query)) return 0;
    } else {
        if (!contains_ci(ts, tl, c->query)) return 0;
        if (starts_with_ci(ts, tl, c->query)) return 0;  /* already taken in pass 1 */
    }
    for (int i = 0; i < c->n; ++i) {                     /* dedup (case-insensitive) */
        size_t j = 0;
        for (; j < tl && c->results[i][j] != '\0'; ++j)
            if (he_lower(c->results[i][j]) != he_lower(ts[j])) break;
        if (j == tl && c->results[i][j] == '\0') return 0;
    }
    for (size_t k = 0; k < tl; ++k) c->results[c->n][k] = he_lower(ts[k]);
    c->results[c->n][tl] = '\0';
    return (++c->n >= c->max);                            /* stop when full */
}

int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1], int max) {
    if (text == NULL || query == NULL || results == NULL || max <= 0) return 0;
    struct suggest_ctx c = { query, 1, results, max, 0 };
    he_scan(text, suggest_cb, &c);       /* pass 1: prefix matches */
    if (c.n < max) { c.prefix_only = 0; he_scan(text, suggest_cb, &c); }  /* pass 2 */
    return c.n;
}
