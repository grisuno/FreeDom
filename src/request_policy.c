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

#define RP_MAX_HOST   255u  /* RFC 1035 maximum host length */
#define RP_MAX_LABELS 128u  /* far above any real host's label count */

/* --- helpers --- */

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}

static int ci_starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s == '\0' || lower(*s) != lower(*prefix)) return 0;
        ++s; ++prefix;
    }
    return 1;
}

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

    const char *p = strstr(url, "://");
    if (p == NULL) return -1;
    p += 3;

    /* Skip past userinfo (user:password@) if present, so the first colon
     * that terminates the host scan is not the one in the credentials. */
    const char *at;
    for (at = p; *at != '\0' && *at != '/' && *at != '?' && *at != '#'; ++at) {
        if (*at == '@') { p = at + 1; break; }
    }

    size_t n = 0;
    while (p[n] != '\0' && p[n] != '/' && p[n] != ':' &&
           p[n] != '?' && p[n] != '#') {
        ++n;
    }
    if (n == 0 || n + 1 > out_size) return -1;

    for (size_t i = 0; i < n; ++i) out[i] = lower(p[i]);
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
    char rh[256], th[256], rs[256], ts[256];

    /* The request must name a host and use https. */
    if (rp_host_of(request_url, rh, sizeof rh) != 0) return RP_BLOCK_INVALID;
    if (!ci_starts_with(request_url, "https://")) return RP_BLOCK_SCHEME;

    /* The top-level document must be locatable and https, or we fail closed. */
    if (rp_host_of(top_level_url, th, sizeof th) != 0) return RP_BLOCK_INVALID;
    if (!ci_starts_with(top_level_url, "https://")) return RP_BLOCK_INVALID;

    if (rp_site_of(rh, rs, sizeof rs) != 0) return RP_BLOCK_INVALID;
    if (rp_site_of(th, ts, sizeof ts) != 0) return RP_BLOCK_INVALID;

    return (strcmp(rs, ts) == 0) ? RP_ALLOW : RP_BLOCK_THIRD_PARTY;
}

/* --- request headers a page may attach (spec/request_headers.md) --- */

static int hdr_lower(int c) { return (c >= 'A' && c <= 'Z') ? c + 32 : c; }

static int hdr_name_ieq(const char *a, size_t alen, const char *lit) {
    size_t n = strlen(lit);
    if (alen != n) return 0;
    for (size_t i = 0; i < n; ++i) if (hdr_lower((unsigned char)a[i]) != lit[i]) return 0;
    return 1;
}

static int hdr_name_has_prefix(const char *a, size_t alen, const char *lit) {
    size_t n = strlen(lit);
    if (alen < n) return 0;
    for (size_t i = 0; i < n; ++i) if (hdr_lower((unsigned char)a[i]) != lit[i]) return 0;
    return 1;
}

static int hdr_token_char(unsigned char c) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) return 1;
    return c != 0 && strchr("!#$%&'*+-.^_`|~", c) != NULL;
}

/* Identity and framing headers the browser owns: the page may not set or override them. */
static int hdr_forbidden(const char *n, size_t len) {
    static const char *const exact[] = {
        "host", "cookie", "cookie2", "set-cookie", "referer", "user-agent", "accept-language",
        "accept-encoding", "connection", "content-length", "transfer-encoding", "te", "upgrade",
        "keep-alive", "expect", "date", "dnt", "via", "trailer", "origin", "content-encoding",
    };
    for (size_t i = 0; i < sizeof exact / sizeof exact[0]; ++i)
        if (hdr_name_ieq(n, len, exact[i])) return 1;
    return hdr_name_has_prefix(n, len, "sec-") || hdr_name_has_prefix(n, len, "proxy-")
        || hdr_name_has_prefix(n, len, "x-http-method")
        || hdr_name_has_prefix(n, len, "access-control-request-");
}

int rp_sanitize_request_headers(const char *raw, char *out, size_t cap) {
    if (raw == NULL || out == NULL || cap == 0) return -1;
    out[0] = '\0';
    size_t used = 0;
    int kept = 0;
    const char *p = raw;
    while (*p != '\0' && kept < RP_HDR_MAX_COUNT) {
        const char *eol = strchr(p, '\n');
        size_t linelen = (eol != NULL) ? (size_t)(eol - p) : strlen(p);
        const char *line = p;
        p = (eol != NULL) ? eol + 1 : p + linelen;

        const char *colon = memchr(line, ':', linelen);
        if (colon == NULL || colon == line) continue;
        size_t nlen = (size_t)(colon - line);
        if (nlen > RP_HDR_NAME_MAX) continue;
        int ok = 1;
        for (size_t i = 0; i < nlen; ++i) if (!hdr_token_char((unsigned char)line[i])) { ok = 0; break; }
        if (!ok || hdr_forbidden(line, nlen)) continue;

        const char *v = colon + 1;
        const char *ve = line + linelen;
        while (v < ve && (*v == ' ' || *v == '\t')) ++v;
        while (ve > v && (ve[-1] == ' ' || ve[-1] == '\t')) --ve;
        size_t vlen = (size_t)(ve - v);
        if (vlen > RP_HDR_VALUE_MAX) continue;
        for (size_t i = 0; i < vlen; ++i) {
            unsigned char c = (unsigned char)v[i];
            if ((c < 0x20 && c != '\t') || c == 0x7f) { ok = 0; break; }
        }
        if (!ok) continue;

        char lower[RP_HDR_NAME_MAX + 1];
        for (size_t i = 0; i < nlen; ++i) lower[i] = (char)hdr_lower((unsigned char)line[i]);
        lower[nlen] = '\0';
        if (rp_headers_have(out, lower)) continue;

        size_t need = nlen + 2 + vlen + 1;               /* "Name: value\n" */
        if (used + need + 1 > cap || used + need > RP_HDR_MAX_BYTES) continue;
        memcpy(out + used, line, nlen); used += nlen;
        out[used++] = ':'; out[used++] = ' ';
        memcpy(out + used, v, vlen); used += vlen;
        out[used++] = '\n';
        out[used] = '\0';
        ++kept;
    }
    return kept;
}

