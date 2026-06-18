/*
 * secure_fetch — implementation.
 *
 * Pure validators (sf_validate_url, sf_check_tls_version, sf_check_group_is_pq,
 * sf_check_chain_policy) carry the security policy and are I/O-free.
 * sf_get only orchestrates libcurl + OpenSSL and then enforces the policy by
 * calling those validators on the negotiated connection state.
 *
 * Fails closed: if any guarantee cannot be verified, the request is rejected.
 */

#define _POSIX_C_SOURCE 200809L

#include "secure_fetch.h"
#include "url.h"

#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
#include <openssl/ssl.h>
#include <openssl/x509.h>
#include <openssl/objects.h>

/* --- small helpers (no libc locale dependence) --- */

static int ci_equal(const char *a, const char *b) {
    while (*a && *b) {
        int ca = (unsigned char)*a, cb = (unsigned char)*b;
        if (ca >= 'A' && ca <= 'Z') ca += 'a' - 'A';
        if (cb >= 'A' && cb <= 'Z') cb += 'a' - 'A';
        if (ca != cb) return 0;
        ++a; ++b;
    }
    return *a == '\0' && *b == '\0';
}

/* Case-insensitive: does haystack start with prefix? */
static int ci_starts_with(const char *haystack, const char *prefix) {
    while (*prefix) {
        int ch = (unsigned char)*haystack, cp = (unsigned char)*prefix;
        if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
        if (cp >= 'A' && cp <= 'Z') cp += 'a' - 'A';
        if (ch != cp) return 0;
        ++haystack; ++prefix;
    }
    return 1;
}

/* Case-insensitive index of needle in haystack, or -1. */
static long ci_index(const char *haystack, const char *needle) {
    for (long i = 0; haystack[i]; ++i) {
        if (ci_starts_with(haystack + i, needle)) return i;
    }
    return -1;
}

/* --- public: defaults --- */

sf_config sf_config_default(void) {
    sf_config c;
    c.policy = SF_POLICY_PQ_HYBRID_KE;
    c.timeout_ms = SF_DEFAULT_TIMEOUT_MS;
    c.max_body_bytes = SF_DEFAULT_MAX_BODY;
    c.kex_groups = SF_DEFAULT_KEX_GROUPS;
    c.user_agent = NULL; /* resolved to SF_DEFAULT_USER_AGENT at request time */
    return c;
}

const char *sf_user_agent_or_default(const char *ua) {
    return (ua != NULL && ua[0] != '\0') ? ua : SF_DEFAULT_USER_AGENT;
}

/* --- public: pure validators --- */

sf_status sf_validate_url(const char *url) {
    /* The canonical https-URL rule lives in the pure url module (DRY). */
    return (url_validate_https(url) == URL_OK) ? SF_OK : SF_ERR_INVALID_URL;
}

sf_status sf_check_tls_version(const char *negotiated_version) {
    if (negotiated_version == NULL) return SF_ERR_TLS_VERSION;
    return ci_equal(negotiated_version, "TLSv1.3") ? SF_OK : SF_ERR_TLS_VERSION;
}

sf_status sf_check_group_is_pq(const char *negotiated_group) {
    if (negotiated_group == NULL) return SF_ERR_KEM_NOT_PQ;
    /* Hybrid groups carry a classical KEM prefix followed by "MLKEM".
     * Pure-PQ groups ("MLKEM768") have the token at index 0; pure-classical
     * groups have no token at all. Both are rejected. */
    long at = ci_index(negotiated_group, "MLKEM");
    return (at > 0) ? SF_OK : SF_ERR_KEM_NOT_PQ;
}

sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy) {
    if (chain == NULL) return SF_ERR_NULL_ARG;
    if (policy != SF_POLICY_PERMISSIVE) {
        if (chain->uses_sha1) return SF_ERR_WEAK_ALGO;
        if (chain->rsa_bits != 0 && chain->rsa_bits < 3072) return SF_ERR_WEAK_ALGO;
    }
    if (policy == SF_POLICY_STRICT_PQ && !chain->has_pq_sig) return SF_ERR_CERT_NOT_PQ;
    return SF_OK;
}

sf_status sf_enforce_policy(const char *tls_version, const char *group,
                            const sf_chain_info *chain, sf_policy policy) {
    sf_status s = sf_check_tls_version(tls_version);
    if (s != SF_OK) return s;
    s = sf_check_group_is_pq(group);
    if (s != SF_OK) return s;
    if (chain == NULL) return SF_ERR_INTERNAL; /* fail closed: chain not inspectable */
    return sf_check_chain_policy(chain, policy);
}

/* --- bounded string helper (overflow => -1, never truncate) --- */

static int copy_checked(char *dst, size_t dstsz, const char *src) {
    size_t n = strlen(src);
    if (n + 1 > dstsz) return -1;
    memcpy(dst, src, n + 1);
    return 0;
}

/* --- public: pure redirect logic --- */

int sf_is_redirect_code(long http_code) {
    switch (http_code) {
        case 301: case 302: case 303: case 307: case 308: return 1;
        default: return 0;
    }
}

sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz) {
    if (header_line == NULL || out == NULL || outsz == 0) return SF_ERR_INVALID_URL;
    if (!ci_starts_with(header_line, "location:")) return SF_ERR_INVALID_URL;

    const char *p = header_line + 9; /* strlen("location:") */
    while (*p == ' ' || *p == '\t') ++p;

    size_t end = 0;
    while (p[end] != '\0' && p[end] != '\r' && p[end] != '\n') ++end;
    while (end > 0 && (p[end - 1] == ' ' || p[end - 1] == '\t')) --end;

    if (end == 0) return SF_ERR_INVALID_URL;       /* empty value */
    if (end + 1 > outsz) return SF_ERR_INVALID_URL; /* would not fit */
    memcpy(out, p, end);
    out[end] = '\0';
    return SF_OK;
}

sf_status sf_resolve_redirect(const char *base_url, const char *location,
                              char *out, size_t outsz) {
    if (base_url == NULL || location == NULL || out == NULL || outsz == 0)
        return SF_ERR_NULL_ARG;
    /* Reference resolution + the https-only / no-downgrade policy live in the
     * pure url module (DRY); a redirect is just a reference resolved against the
     * current URL, fail-closed to an absolute https URL. */
    return (url_resolve_https(base_url, location, out, outsz) == URL_OK)
               ? SF_OK : SF_ERR_INVALID_URL;
}

/* --- public: cleanup --- */

void sf_response_free(sf_response *resp) {
    if (resp == NULL) return;
    free(resp->tls_version);
    free(resp->negotiated_group);
    free(resp->body);
    free(resp->location);
    resp->tls_version = NULL;
    resp->negotiated_group = NULL;
    resp->body = NULL;
    resp->body_len = 0;
    resp->location = NULL;
    resp->http_code = 0;
    resp->status = SF_OK;
}

/* --- orchestrator internals --- */

typedef struct body_sink {
    uint8_t *data;
    size_t   len;
    size_t   cap;
    size_t   limit;
    int      overflow;
} body_sink;

/* Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a
 * transfer is in progress (via CURLINFO_TLS_SSL_PTR); after curl_easy_perform
 * returns, internals is NULL. So we capture from inside the header/write
 * callbacks and copy everything into owned storage, since SSL_get0_group_name /
 * the chain pointers are only valid while the SSL object lives. */
typedef struct tls_capture {
    CURL         *curl;
    int           have;            /* nonzero once the snapshot was taken */
    char          version[32];
    char          group[64];
    int           chain_ok;        /* chain could be inspected */
    sf_chain_info chain;
    char          sigbuf[128];
} tls_capture;

typedef struct fetch_ctx {
    body_sink   sink;
    tls_capture cap;
    char        location[SF_MAX_URL]; /* last Location header value seen, if any */
    int         have_location;
} fetch_ctx;

static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len);

static void copy_bounded(char *dst, size_t dstsz, const char *src) {
    if (dstsz == 0) return;
    dst[0] = '\0';
    if (src == NULL) return;
    size_t i = 0;
    for (; src[i] != '\0' && i + 1 < dstsz; ++i) dst[i] = src[i];
    dst[i] = '\0';
}

/* Idempotent: takes the TLS snapshot the first time the SSL* is reachable. */
static void tls_capture_try(tls_capture *cap) {
    if (cap->have) return;
    struct curl_tlssessioninfo *ti = NULL;
    if (curl_easy_getinfo(cap->curl, CURLINFO_TLS_SSL_PTR, &ti) != CURLE_OK) return;
    if (ti == NULL || ti->backend != CURLSSLBACKEND_OPENSSL || ti->internals == NULL) return;

    SSL *ssl = (SSL *)ti->internals;
    copy_bounded(cap->version, sizeof cap->version, SSL_get_version(ssl));
    copy_bounded(cap->group, sizeof cap->group, SSL_get0_group_name(ssl));
    memset(&cap->chain, 0, sizeof cap->chain);
    cap->chain_ok = (inspect_chain(ssl, &cap->chain, cap->sigbuf, sizeof cap->sigbuf) == 0);
    cap->have = 1;
}

/* Fires for every HTTP response (status line + headers) even when there is no
 * body, so it is the reliable point to snapshot the negotiated TLS state. */
static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata) {
    fetch_ctx *ctx = (fetch_ctx *)userdata;
    tls_capture_try(&ctx->cap);

    size_t n = size * nitems;
    if (size != 0 && n / size != nitems) return 0; /* multiplication overflow */

    /* curl delivers one header line here, not NUL-terminated. Make a bounded
     * NUL-terminated copy so the pure parser can inspect it. */
    char line[SF_MAX_URL + 64];
    size_t m = n < sizeof line - 1 ? n : sizeof line - 1;
    memcpy(line, buffer, m);
    line[m] = '\0';

    char val[SF_MAX_URL];
    if (sf_parse_location_header(line, val, sizeof val) == SF_OK) {
        memcpy(ctx->location, val, strlen(val) + 1);
        ctx->have_location = 1;
    }
    return size * nitems;
}

static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata) {
    fetch_ctx *ctx = (fetch_ctx *)userdata;
    body_sink *sink = &ctx->sink;
    tls_capture_try(&ctx->cap);
    size_t incoming = size * nmemb;
    if (size != 0 && incoming / size != nmemb) { /* multiplication overflow */
        sink->overflow = 1;
        return 0;
    }
    if (sink->len + incoming > sink->limit) {
        sink->overflow = 1;
        return 0; /* abort transfer */
    }
    if (sink->len + incoming + 1 > sink->cap) {
        size_t want = sink->len + incoming + 1;
        size_t newcap = sink->cap ? sink->cap : 4096;
        while (newcap < want) newcap *= 2;
        uint8_t *grown = (uint8_t *)realloc(sink->data, newcap);
        if (grown == NULL) {
            sink->overflow = 2; /* OOM marker */
            return 0;
        }
        sink->data = grown;
        sink->cap = newcap;
    }
    memcpy(sink->data + sink->len, ptr, incoming);
    sink->len += incoming;
    sink->data[sink->len] = '\0';
    return incoming;
}

/* Returns nonzero if the short or long name denotes an ML-DSA / SLH-DSA signature. */
static int name_is_pq_sig(int pknid) {
    const char *sn = OBJ_nid2sn(pknid);
    const char *ln = OBJ_nid2ln(pknid);
    if (sn && (ci_starts_with(sn, "ML-DSA") || ci_starts_with(sn, "SLH-DSA"))) return 1;
    if (ln && (ci_index(ln, "ML-DSA") >= 0 || ci_index(ln, "SLH-DSA") >= 0)) return 1;
    return 0;
}

/* Walks the verified chain into *info. sigbuf receives the leaf signature alg name.
 * Returns 0 on success, nonzero if the chain could not be inspected. */
static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len) {
    STACK_OF(X509) *chain = SSL_get0_verified_chain(ssl);
    if (chain == NULL) chain = SSL_get_peer_cert_chain(ssl);
    if (chain == NULL) return 1;

    int n = sk_X509_num(chain);
    if (n <= 0) return 1;

    info->leaf_sig_alg = sigbuf;
    info->rsa_bits = 0;
    info->uses_sha1 = 0;
    info->has_pq_sig = 0;
    sigbuf[0] = '\0';

    for (int i = 0; i < n; ++i) {
        X509 *cert = sk_X509_value(chain, i);
        if (cert == NULL) continue;

        /* SHA-1 and PQ-signature detection scan the whole chain: a SHA-1
         * signature anywhere is a real forgery risk, so it is fatal regardless
         * of position. */
        int mdnid = 0, pknid = 0, secbits = 0;
        uint32_t flags = 0;
        if (X509_get_signature_info(cert, &mdnid, &pknid, &secbits, &flags)) {
            if (mdnid == NID_sha1) info->uses_sha1 = 1;
            if (name_is_pq_sig(pknid)) info->has_pq_sig = 1;
        }

        if (i == 0) {
            /* The weak-RSA gate targets the end-entity (leaf) key only: that is
             * what the site operator controls and what authenticates the
             * session. Public CA intermediates are universally RSA 2048 in 2026
             * and out of the site's control, so they are not held to RSA>=3072. */
            EVP_PKEY *pk = X509_get0_pubkey(cert);
            if (pk != NULL && EVP_PKEY_get_base_id(pk) == EVP_PKEY_RSA) {
                int bits = EVP_PKEY_get_bits(pk);
                if (bits > 0) info->rsa_bits = bits;
            }

            const X509_ALGOR *alg = NULL;
            X509_get0_signature(NULL, &alg, cert);
            if (alg != NULL) {
                const ASN1_OBJECT *aobj = NULL;
                X509_ALGOR_get0(&aobj, NULL, NULL, alg);
                if (aobj != NULL) {
                    OBJ_obj2txt(sigbuf, (int)sigbuf_len, aobj, 0);
                }
            }
        }
    }
    return 0;
}

static sf_status map_curl_error(CURLcode rc, const body_sink *sink) {
    if (sink->overflow == 1) return SF_ERR_TOO_LARGE;
    if (sink->overflow == 2) return SF_ERR_OOM;
    switch (rc) {
        case CURLE_OPERATION_TIMEDOUT:
        case CURLE_COULDNT_CONNECT:
        case CURLE_COULDNT_RESOLVE_HOST:
        case CURLE_COULDNT_RESOLVE_PROXY:
        case CURLE_RECV_ERROR:
        case CURLE_SEND_ERROR:
            return SF_ERR_NETWORK;
        case CURLE_PEER_FAILED_VERIFICATION:
        case CURLE_SSL_CERTPROBLEM:
        case CURLE_SSL_CONNECT_ERROR:
            return SF_ERR_CERT_INVALID;
        case CURLE_UNSUPPORTED_PROTOCOL:
        case CURLE_URL_MALFORMAT:
            return SF_ERR_INVALID_URL;
        default:
            return SF_ERR_INTERNAL;
    }
}

/* --- public: orchestrator --- */

/* The shared request engine for sf_get and sf_post. When post_body == NULL it is a
 * GET; otherwise it is a POST carrying body (post_len bytes) with content_type. The
 * full TLS/PQ/chain policy is enforced identically for both methods (Zero Trust:
 * the method changes nothing about how the connection is judged). */
static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
                            const void *post_body, size_t post_len,
                            const char *content_type) {
    if (url == NULL || out == NULL) return SF_ERR_NULL_ARG;

    memset(out, 0, sizeof *out);

    sf_config local = (cfg != NULL) ? *cfg : sf_config_default();
    if (local.timeout_ms == 0) local.timeout_ms = SF_DEFAULT_TIMEOUT_MS;
    if (local.max_body_bytes == 0) local.max_body_bytes = SF_DEFAULT_MAX_BODY;
    if (local.kex_groups == NULL) local.kex_groups = SF_DEFAULT_KEX_GROUPS;

    sf_status vs = sf_validate_url(url);
    if (vs != SF_OK) { out->status = vs; return vs; }

    CURL *curl = curl_easy_init();
    if (curl == NULL) { out->status = SF_ERR_OOM; return SF_ERR_OOM; }

    fetch_ctx ctx;
    memset(&ctx, 0, sizeof ctx);
    ctx.sink.limit = local.max_body_bytes;
    ctx.cap.curl = curl;

    struct curl_slist *hdrs = NULL;
    sf_status result = SF_ERR_INTERNAL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_SSLVERSION,
                     (long)(CURL_SSLVERSION_TLSv1_3 | CURL_SSLVERSION_MAX_TLSv1_3));
    curl_easy_setopt(curl, CURLOPT_SSL_EC_CURVES, local.kex_groups);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS_STR, "https");
    curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS_STR, "https");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, local.timeout_ms);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, sf_user_agent_or_default(local.user_agent));
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ctx);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_cb);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &ctx);

    if (post_body != NULL || post_len != 0) {
        const char *ct = (content_type != NULL) ? content_type
                                                 : "application/x-www-form-urlencoded";
        char hbuf[256];
        int hn = snprintf(hbuf, sizeof hbuf, "Content-Type: %s", ct);
        if (hn < 0 || (size_t)hn >= sizeof hbuf) { result = SF_ERR_INVALID_URL; goto done; }
        hdrs = curl_slist_append(NULL, hbuf);
        /* Suppress libcurl's "Expect: 100-continue" so a small POST is one round trip. */
        hdrs = curl_slist_append(hdrs, "Expect:");
        if (hdrs == NULL) { result = SF_ERR_OOM; goto done; }
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hdrs);
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)post_len);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (post_body != NULL) ? post_body : "");
    }

    CURLcode rc = curl_easy_perform(curl);
    if (rc != CURLE_OK) {
        result = map_curl_error(rc, &ctx.sink);
        goto done;
    }

    /* The negotiated TLS state was snapshotted during the transfer. If the
     * snapshot never happened (no callback could read the SSL*), fail closed. */
    if (!ctx.cap.have) {
        result = SF_ERR_INTERNAL;
        goto done;
    }

    sf_chain_info *chain_ptr = ctx.cap.chain_ok ? &ctx.cap.chain : NULL;
    result = sf_enforce_policy(ctx.cap.version, ctx.cap.group, chain_ptr, local.policy);
    if (result != SF_OK) goto done;

    /* All guarantees met: publish the response. */
    long code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

    char *ver = strdup(ctx.cap.version);
    char *grp = strdup(ctx.cap.group);
    char *loc = ctx.have_location ? strdup(ctx.location) : NULL;
    if (ver == NULL || grp == NULL || (ctx.have_location && loc == NULL)) {
        free(ver);
        free(grp);
        free(loc);
        result = SF_ERR_OOM;
        goto done;
    }
    out->status = SF_OK;
    out->http_code = code;
    out->tls_version = ver;
    out->negotiated_group = grp;
    out->location = loc;
    out->body = ctx.sink.data;
    out->body_len = ctx.sink.len;
    ctx.sink.data = NULL; /* ownership transferred */
    curl_slist_free_all(hdrs);
    curl_easy_cleanup(curl);
    return SF_OK;

done:
    free(ctx.sink.data);
    out->status = result;
    curl_slist_free_all(hdrs);
    curl_easy_cleanup(curl);
    return result;
}

sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out) {
    return sf_perform(url, cfg, out, NULL, 0, NULL);
}

sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size_t body_len, const char *content_type,
                  sf_response *out) {
    if (url == NULL || out == NULL) return SF_ERR_NULL_ARG;
    if (body == NULL && body_len != 0) {
        memset(out, 0, sizeof *out);
        out->status = SF_ERR_NULL_ARG;
        return SF_ERR_NULL_ARG;
    }
    /* A non-empty body forces the POST path; an empty POST still sets POST via a
     * zero-length body pointer. */
    return sf_perform(url, cfg, out, (body != NULL) ? body : "", body_len, content_type);
}

sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                        int max_redirects) {
    if (url == NULL || out == NULL) return SF_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (max_redirects < 0) max_redirects = 0;

    char current[SF_MAX_URL];
    if (copy_checked(current, sizeof current, url) != 0) {
        out->status = SF_ERR_INVALID_URL;
        return SF_ERR_INVALID_URL;
    }

    for (int hops = 0; ; ++hops) {
        /* Each hop is a fresh request: the full TLS/PQ/chain policy is enforced
         * again. Nothing from the previous hop is trusted but the resolved URL. */
        sf_status s = sf_get(current, cfg, out);
        if (s != SF_OK) return s; /* out carries the failure reason */

        if (!sf_is_redirect_code(out->http_code) || out->location == NULL) {
            return SF_OK; /* final response */
        }
        if (hops >= max_redirects) {
            sf_response_free(out);
            out->status = SF_ERR_TOO_MANY_REDIRECTS;
            return SF_ERR_TOO_MANY_REDIRECTS;
        }

        char next[SF_MAX_URL];
        sf_status rs = sf_resolve_redirect(current, out->location, next, sizeof next);
        if (rs != SF_OK) {
            sf_response_free(out);
            out->status = rs;
            return rs;
        }

        sf_response_free(out);
        memcpy(current, next, strlen(next) + 1);
    }
}
