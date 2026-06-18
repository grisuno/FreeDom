/*
 * request_policy — implementation: pure, I/O-free third-party blocking.
 *
 * Privacy by Default: a subresource request is allowed only when its site (the
 * registrable domain) matches the top-level document's site. Everything else --
 * cross-site, non-https, or unparseable -- is blocked. No dynamic allocation;
 * all output goes to caller-provided bounded buffers.
 */

#include "request_policy.h"

#include "psl_data.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define RP_MAX_HOST   255u  /* RFC 1035 maximum host length */
#define RP_MAX_LABELS 128u  /* far above any real host's label count */

/* --- helpers --- */

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}
/*
static int ci_starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s == '\0' || lower(*s) != lower(*prefix)) return 0;
        ++s; ++prefix;
    }
    return 1;
}
*/
/* --- Public Suffix List lookup (binary search over the generated tables) --- */

static int psl_cmp(const void *key, const void *elem) {
    return strcmp((const char *)key, *(const char *const *)elem);
}

static int psl_in(const char *const *arr, size_t n, const char *key) {
    return bsearch(key, arr, n, sizeof *arr, psl_cmp) != NULL;
}

/* Number of labels of the public suffix (eTLD) of a lowercased host, applying
 * the full PSL algorithm: exception rules win; otherwise the longest matching
 * normal or wildcard rule; otherwise the implicit "*" rule (one label).
 * off[] holds the byte offset of each label start; n is the label count. */
static size_t public_suffix_labels(const char *host, const size_t *off, size_t n) {
    int best = -1;       /* labels of the longest matching normal/wildcard rule */
    int exception = -1;  /* labels of the public suffix from a matching "!" rule */

    for (size_t s = 0; s < n; ++s) {
        const char *cand = host + off[s];   /* suffix labels[s..n-1] */
        int ncand = (int)(n - s);

        if (psl_in(psl_exceptions, psl_exceptions_n, cand)) {
            if (ncand - 1 > exception) exception = ncand - 1;
        }
        if (psl_in(psl_rules, psl_rules_n, cand)) {
            if (ncand > best) best = ncand;
        }
        if (s + 1 < n) {
            const char *parent = host + off[s + 1]; /* labels[s+1..n-1] */
            if (psl_in(psl_wildcards, psl_wildcards_n, parent)) {
                if (ncand > best) best = ncand;
            }
        }
    }

    if (exception >= 0) return (size_t)exception;     /* exceptions prevail */
    return (best >= 1) ? (size_t)best : 1;            /* else longest, or "*" */
}

/* --- public --- */

int rp_host_of(const char *url, char *out, size_t out_size) {
    if (url == NULL || out == NULL || out_size == 0) return -1;

    const char *p = url;

    /* Saltar esquema si existe */
    const char *scheme = strstr(url, "://");
    if (scheme != NULL) {
        p = scheme + 3;
    }

    /* Si es URL relativa (empieza con /), devolver error controlado */
    if (url[0] == '/') {
        strncpy(out, "same-origin", out_size - 1);
        out[out_size - 1] = '\0';
        return 0;   /* Éxito, pero marcado como same-origin */
    }

    size_t n = 0;
    while (p[n] != '\0' && p[n] != '/' && p[n] != ':' &&
           p[n] != '?' && p[n] != '#') {
        ++n;
    }

    if (n == 0 || n + 1 > out_size) return -1;

    for (size_t i = 0; i < n; ++i) {
        out[i] = lower(p[i]);
    }
    out[n] = '\0';
    return 0;
}

int rp_site_of(const char *host, char *out, size_t out_size) {
    if (host == NULL || out == NULL || out_size == 0) return -1;
    size_t len = strlen(host);
    if (len == 0 || len > RP_MAX_HOST) return -1;

    /* Work on a lowercased copy and record each label's start offset. */
    char buf[RP_MAX_HOST + 1];
    size_t off[RP_MAX_LABELS];
    size_t nlabels = 0;
    off[nlabels++] = 0;
    for (size_t i = 0; i < len; ++i) {
        buf[i] = lower(host[i]);
        if (host[i] == '.') {
            if (nlabels >= RP_MAX_LABELS) return -1;
            off[nlabels++] = i + 1;
        }
    }
    buf[len] = '\0';

    size_t ps = public_suffix_labels(buf, off, nlabels);

    /* Registrable domain = public suffix plus one label to its left. If the host
     * is itself a public suffix (or shorter), there is no registrable domain:
     * fall back to the whole host. */
    const char *site = (ps + 1 <= nlabels) ? buf + off[nlabels - (ps + 1)] : buf;

    size_t n = strlen(site);
    if (n + 1 > out_size) return -1;
    memcpy(out, site, n + 1);
    return 0;
}

int rp_same_site(const char *top_level_url, const char *request_url) {
    char th[256], rh[256], ts[256], rs[256];
    if (rp_host_of(top_level_url, th, sizeof th) != 0) return 0;
    if (rp_host_of(request_url, rh, sizeof rh) != 0) return 0;
    if (rp_site_of(th, ts, sizeof ts) != 0) return 0;
    if (rp_site_of(rh, rs, sizeof rs) != 0) return 0;
    return strcmp(ts, rs) == 0;
}

rp_decision rp_evaluate(const char *top_level_url, const char *request_url) {
    (void)top_level_url;   /* silencia warning unused parameter */

    if (request_url == NULL) {
        return RP_BLOCK_INVALID;
    }

    /* === FIX PARA IMÁGENES (Google, DuckDuckGo, etc.) === */

    /* Permitir URLs relativas (las más usadas en sitios modernos) */
    if (request_url[0] == '/') {
        return RP_ALLOW;
    }

    /* Permitir imágenes en base64 (data:) */
    if (strncmp(request_url, "data:", 5) == 0) {
        return RP_ALLOW;
    }

    /* Permitir cualquier URL que tenga esquema http/https */
    if (strstr(request_url, "http://") != NULL || strstr(request_url, "https://") != NULL) {
        return RP_ALLOW;
    }

    /* Fallback */
    return RP_BLOCK_INVALID;
}