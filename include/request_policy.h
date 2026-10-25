#ifndef FREEDOM_REQUEST_POLICY_H
#define FREEDOM_REQUEST_POLICY_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * request_policy — Privacy by Default: block all third-party subresource
 * requests at the network engine.
 *
 * Pure, I/O-free policy logic (the directly auditable surface): a page loader
 * consults rp_evaluate() before letting secure_fetch touch any subresource.
 * Allowing third parties is deliberately not representable.
 *
 * See spec/request_policy.md for the full contract.
 */

typedef enum rp_decision {
    RP_ALLOW = 0,          /* same-site: allowed */
    RP_BLOCK_THIRD_PARTY,  /* cross-site subresource: blocked by default */
    RP_BLOCK_SCHEME,       /* scheme is not https */
    RP_BLOCK_INVALID       /* URL missing / unparseable (fails closed) */
} rp_decision;

/* Lowercased host of an absolute URL into out. Returns 0 on success, -1 if no
 * host can be parsed or it does not fit in out. */
int rp_host_of(const char *url, char *out, size_t out_size);

/* Registrable domain ("site") of a host into out (simplified public-suffix
 * rule). Returns 0 on success, -1 on empty host or insufficient buffer. */
int rp_site_of(const char *host, char *out, size_t out_size);

/* 1 if both URLs share the same site, 0 otherwise (including parse failure). */
int rp_same_site(const char *top_level_url, const char *request_url);

/* Decision for a subresource request given the top-level document URL. */
rp_decision rp_evaluate(const char *top_level_url, const char *request_url);

/* --- Request headers a page may attach to its XHR/fetch (spec/request_headers.md) --- */
#define RP_HDR_MAX_COUNT 32
#define RP_HDR_MAX_BYTES 4096
#define RP_HDR_NAME_MAX  64
#define RP_HDR_VALUE_MAX 1024

/* Filters the page-supplied header block `raw` ("Name: value" lines separated by '\n') into
 * `out` (same format, '\n'-terminated lines, NUL-terminated) keeping ONLY headers a page may
 * set: well-formed token name and a value free of control bytes, within the count/size caps,
 * and not on the forbidden list (identity and framing headers the browser owns: Host, Cookie,
 * Referer, User-Agent, Accept-Language, Accept-Encoding, Connection, Content-Length,
 * Transfer-Encoding, TE, Upgrade, Expect, Date, DNT, Via, Origin, Sec-*, Proxy-*, X-HTTP-Method*,
 * Access-Control-Request-*). A repeated name keeps its first occurrence. Pure; fail-closed
 * (anything doubtful is dropped, never rewritten). Returns the number of headers kept, or -1
 * on NULL/zero-capacity arguments. */
int rp_sanitize_request_headers(const char *raw, char *out, size_t cap);

/* 1 when the sanitized block `lines` carries a header called `name` (case-insensitive). Inline so
 * secure_fetch can ask it without linking the policy module. */
static inline int rp_headers_have(const char *lines, const char *name) {
    if (lines == NULL || name == NULL) return 0;
    size_t nlen = 0;
    while (name[nlen] != '\0') ++nlen;
    for (const char *p = lines; *p != '\0'; ) {
        size_t l = 0;
        while (p[l] != '\0' && p[l] != '\n' && p[l] != ':') ++l;
        if (p[l] == ':' && l == nlen) {
            size_t i = 0;
            for (; i < l; ++i) {
                char a = p[i], b = name[i];
                if (a >= 'A' && a <= 'Z') a = (char)(a + 32);
                if (b >= 'A' && b <= 'Z') b = (char)(b + 32);
                if (a != b) break;
            }
            if (i == l) return 1;
        }
        while (*p != '\0' && *p != '\n') ++p;
        if (*p == '\n') ++p;
    }
    return 0;
}

#endif /* FREEDOM_REQUEST_POLICY_H */
