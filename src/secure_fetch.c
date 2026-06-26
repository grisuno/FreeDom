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

void sf_global_init(void) {
    /* Refcounted by libcurl; the first call from the main thread does the real (not
     * thread-safe) global setup so later per-thread curl_easy_init calls are safe. */
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

sf_config sf_config_default(void) {
    sf_config c;
    c.policy = SF_POLICY_PQ_HYBRID_KE;
    c.timeout_ms = SF_DEFAULT_TIMEOUT_MS;
    c.max_body_bytes = SF_DEFAULT_MAX_BODY;
    c.kex_groups = SF_DEFAULT_KEX_GROUPS;
    c.user_agent = NULL; /* resolved to SF_DEFAULT_USER_AGENT at request time */
    c.proxy_type = SF_PROXY_NONE; /* direct by default; Tor/I2P is opt-in */
    c.proxy_address = NULL;
    c.allow_overlay_http = 0;     /* https-only unless an overlay realm opts in */
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

/* Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host.
 * Plain http is only ever permitted for overlay (.onion/.i2p) realms, gated by
 * sf_config.allow_overlay_http; the overlay layer provides encryption + authenticity. */
static int sf_url_is_http(const char *url) {
    static const char pre[] = "http://";
    if (url == NULL) return 0;
    for (size_t i = 0; i < sizeof pre - 1; ++i) {
        char a = url[i];
        if (a >= 'A' && a <= 'Z') a += 'a' - 'A';
        if (a != pre[i]) return 0;
    }
    const char *h = url + (sizeof pre - 1);
    return (h[0] != '\0' && h[0] != '/' && h[0] != ':' && h[0] != '?' && h[0] != '#');
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
    if (policy == SF_POLICY_ALLOWLISTED_INSECURE) {
        /* Explicit per-host user override (the allowlist). Tolerate TLS 1.2 (1.3 is
         * still preferred by the handshake), a classical key exchange, and weak-but-
         * valid leaf primitives. The chain is still authenticated by the transport's
         * VERIFYPEER and re-checked here permissively: crypto strength is relaxed,
         * authenticity is not. Anything below TLS 1.2 stays refused. */
        if (tls_version == NULL ||
            (!ci_equal(tls_version, "TLSv1.3") && !ci_equal(tls_version, "TLSv1.2")))
            return SF_ERR_TLS_VERSION;
        if (chain == NULL) return SF_ERR_INTERNAL; /* fail closed: chain not inspectable */
        return sf_check_chain_policy(chain, SF_POLICY_PERMISSIVE);
    }

    sf_status s = sf_check_tls_version(tls_version);
    if (s != SF_OK) return s;
    /* The navigability fallback accepts a classical KE; every other policy requires
     * a PQ-hybrid group. The certificate chain is always validated below. */
    if (policy != SF_POLICY_ALLOW_CLASSICAL_KE) {
        s = sf_check_group_is_pq(group);
        if (s != SF_OK) return s;
    }
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

/* Case-insensitive prefix test. */
static int sf_ci_prefix(const char *s, const char *p) {
    for (; *p; ++s, ++p) {
        char a = *s, b = *p;
        if (a >= 'A' && a <= 'Z') a += 'a' - 'A';
        if (b >= 'A' && b <= 'Z') b += 'a' - 'A';
        if (a != b) return 0;
    }
    return 1;
}

/* Resolves a redirect for an overlay (plain-http) request, reusing the tested https
 * reference resolver by swapping http<->https around it. A redirect that explicitly
 * names https is refused (an eepsite must not bounce navigation onto the clearnet
 * from behind the overlay proxy: fail closed). The base must be an http URL. */
static sf_status sf_resolve_redirect_overlay(const char *base, const char *location,
                                             char *out, size_t outsz) {
    if (base == NULL || location == NULL || out == NULL || outsz == 0)
        return SF_ERR_NULL_ARG;
    if (sf_ci_prefix(location, "https://")) return SF_ERR_INVALID_URL;
    if (!sf_ci_prefix(base, "http://")) return SF_ERR_INVALID_URL;

    char hbase[SF_MAX_URL], hloc[SF_MAX_URL], tmp[SF_MAX_URL];
    if (snprintf(hbase, sizeof hbase, "https://%s", base + 7) >= (int)sizeof hbase)
        return SF_ERR_INVALID_URL;
    /* Absolute http reference -> https for resolution; relative refs pass through. */
    if (sf_ci_prefix(location, "http://")) {
        if (snprintf(hloc, sizeof hloc, "https://%s", location + 7) >= (int)sizeof hloc)
            return SF_ERR_INVALID_URL;
    } else {
        if (snprintf(hloc, sizeof hloc, "%s", location) >= (int)sizeof hloc)
            return SF_ERR_INVALID_URL;
    }
    if (url_resolve_https(hbase, hloc, tmp, sizeof tmp) != URL_OK) return SF_ERR_INVALID_URL;
    if (!sf_ci_prefix(tmp, "https://")) return SF_ERR_INVALID_URL;
    if (snprintf(out, outsz, "http://%s", tmp + 8) >= (int)outsz) return SF_ERR_INVALID_URL;
    return SF_OK;
}

/* --- public: cleanup --- */

void sf_response_free(sf_response *resp) {
    if (resp == NULL) return;
    free(resp->tls_version);
    free(resp->negotiated_group);
    free(resp->body);
    free(resp->location);
    free(resp->final_url);
    free(resp->content_type);
    free(resp->content_disposition);
    resp->tls_version = NULL;
    resp->negotiated_group = NULL;
    resp->body = NULL;
    resp->body_len = 0;
    resp->location = NULL;
    resp->final_url = NULL;
    resp->content_type = NULL;
    resp->content_disposition = NULL;
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
    char        disposition[SF_MAX_URL]; /* last Content-Disposition value, if any */
    int         have_disposition;
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
    /* Read the REAL negotiated group from OpenSSL. A previous "fix" hardcoded this
     * to "X25519", which made sf_check_group_is_pq reject every connection as
     * non-PQ (status 4) — no site could load. NULL (no group / not TLS 1.3) copies
     * to "" and is then rejected by the policy, which is the correct fail-closed. */
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
    /* Capture Content-Disposition: its filename drives the download name (hostile;
     * sanitized fail-closed downstream). The header name is matched case-insensitively;
     * the value is the trimmed remainder after the colon. */
    if (ci_starts_with(line, "content-disposition:")) {
        const char *p = line + 20; /* strlen("content-disposition:") */
        while (*p == ' ' || *p == '\t') ++p;
        size_t vlen = strlen(p);
        while (vlen > 0 && (p[vlen - 1] == '\r' || p[vlen - 1] == '\n' ||
                            p[vlen - 1] == ' '  || p[vlen - 1] == '\t')) --vlen;
        if (vlen >= sizeof ctx->disposition) vlen = sizeof ctx->disposition - 1;
        memcpy(ctx->disposition, p, vlen);
        ctx->disposition[vlen] = '\0';
        ctx->have_disposition = 1;
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

    /* https is required everywhere except an overlay (.onion/.i2p) request that opted
     * into plain http: there the overlay layer authenticates and encrypts, so http is
     * not a downgrade. A malformed http URL (no host) still falls through to the
     * strict https validation and is rejected. */
    int http_overlay = local.allow_overlay_http && sf_url_is_http(url);
    if (!http_overlay) {
        sf_status vs = sf_validate_url(url);
        if (vs != SF_OK) { out->status = vs; return vs; }
    }

    CURL *curl = curl_easy_init();
    if (curl == NULL) { out->status = SF_ERR_OOM; return SF_ERR_OOM; }

    fetch_ctx ctx;
    memset(&ctx, 0, sizeof ctx);
    ctx.sink.limit = local.max_body_bytes;
    ctx.cap.curl = curl;

    struct curl_slist *hdrs = NULL;
    sf_status result = SF_ERR_INTERNAL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* Socket-level anonymity proxy (Tor SOCKS5h / I2P HTTP). SOCKS5_HOSTNAME keeps DNS
     * resolution at the proxy (no local lookup => no DNS leak; resolves .onion). When
     * a proxy is set, libcurl never bypasses it, so there is no de-anonymizing direct
     * fallback. The realm router (net_realm) chose this in the orchestrator. */
    if (local.proxy_type != SF_PROXY_NONE && local.proxy_address != NULL) {
        curl_easy_setopt(curl, CURLOPT_PROXY, local.proxy_address);
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE,
                         (local.proxy_type == SF_PROXY_HTTP)
                             ? (long)CURLPROXY_HTTP
                             : (long)CURLPROXY_SOCKS5_HOSTNAME);
    }
    /* TLS 1.3 is the floor everywhere except the explicit allowlist override, which
     * lowers the floor to TLS 1.2 (1.3 still the ceiling, so it is preferred). The
     * negotiated version is re-checked against the policy in sf_enforce_policy. */
    long sslmin = (local.policy == SF_POLICY_ALLOWLISTED_INSECURE)
                  ? CURL_SSLVERSION_TLSv1_2 : CURL_SSLVERSION_TLSv1_3;
    curl_easy_setopt(curl, CURLOPT_SSLVERSION,
                     (long)(sslmin | CURL_SSLVERSION_MAX_TLSv1_3));
    curl_easy_setopt(curl, CURLOPT_SSL_EC_CURVES, local.kex_groups);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
    /* https only, except an overlay request that also allows plain http. */
    const char *protos = local.allow_overlay_http ? "http,https" : "https";
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS_STR, protos);
    curl_easy_setopt(curl, CURLOPT_REDIR_PROTOCOLS_STR, protos);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 0L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, local.timeout_ms);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, sf_user_agent_or_default(local.user_agent));
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ctx);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_cb);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &ctx);

    /* Send a normalized Accept-Language on every request (anti-fingerprinting): the
     * value matches the JS-visible identity, so the on-the-wire and in-page locales
     * agree. Omitting it is itself a signal; the real system locale must never leak. */
    hdrs = curl_slist_append(hdrs, "Accept-Language: " FP_ACCEPT_LANGUAGE_HEADER);
    if (hdrs == NULL) { result = SF_ERR_OOM; goto done; }

    if (post_body != NULL || post_len != 0) {
        const char *ct = (content_type != NULL) ? content_type
                                                 : "application/x-www-form-urlencoded";
        char hbuf[256];
        int hn = snprintf(hbuf, sizeof hbuf, "Content-Type: %s", ct);
        if (hn < 0 || (size_t)hn >= sizeof hbuf) { result = SF_ERR_INVALID_URL; goto done; }
        hdrs = curl_slist_append(hdrs, hbuf);
        /* Suppress libcurl's "Expect: 100-continue" so a small POST is one round trip. */
        hdrs = curl_slist_append(hdrs, "Expect:");
        if (hdrs == NULL) { result = SF_ERR_OOM; goto done; }
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE_LARGE, (curl_off_t)post_len);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (post_body != NULL) ? post_body : "");
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hdrs);

    CURLcode rc = curl_easy_perform(curl);
    if (rc != CURLE_OK) {
        result = map_curl_error(rc, &ctx.sink);
        goto done;
    }

    /* The negotiated TLS state was snapshotted during the transfer. */
    if (ctx.cap.have) {
        /* A TLS connection: enforce the full TLS/PQ/chain policy. */
        sf_chain_info *chain_ptr = ctx.cap.chain_ok ? &ctx.cap.chain : NULL;
        result = sf_enforce_policy(ctx.cap.version, ctx.cap.group, chain_ptr, local.policy);
        if (result != SF_OK) goto done;
    } else if (!local.allow_overlay_http) {
        /* No TLS captured and this was not an accepted plain-http overlay request:
         * fail closed (an https response we could not inspect is never trusted). */
        result = SF_ERR_INTERNAL;
        goto done;
    }
    /* else: plain http over the overlay (Tor/I2P). The overlay layer encrypts and
     * authenticates by the destination address, so there is no TLS to enforce. */

    /* All guarantees met: publish the response. */
    long code = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);

    char *ver = strdup(ctx.cap.version);
    char *grp = strdup(ctx.cap.group);
    char *loc = ctx.have_location ? strdup(ctx.location) : NULL;
    /* Content-Type comes straight from curl (already de-folded); Content-Disposition
     * we captured by hand. Both feed the pure render-vs-download decision. */
    const char *ct_raw = NULL;
    curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &ct_raw);
    char *ctype = (ct_raw != NULL) ? strdup(ct_raw) : NULL;
    char *disp  = ctx.have_disposition ? strdup(ctx.disposition) : NULL;
    if (ver == NULL || grp == NULL || (ctx.have_location && loc == NULL) ||
        (ct_raw != NULL && ctype == NULL) || (ctx.have_disposition && disp == NULL)) {
        free(ver);
        free(grp);
        free(loc);
        free(ctype);
        free(disp);
        result = SF_ERR_OOM;
        goto done;
    }
    out->status = SF_OK;
    out->http_code = code;
    out->tls_version = ver;
    out->negotiated_group = grp;
    out->location = loc;
    out->content_type = ctype;
    out->content_disposition = disp;
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
        /* An overlay (plain-http) hop resolves redirects in the http scheme; every
         * other request stays strictly https. */
        int overlay = (cfg != NULL && cfg->allow_overlay_http && sf_url_is_http(current));
        sf_status rs = overlay
            ? sf_resolve_redirect_overlay(current, out->location, next, sizeof next)
            : sf_resolve_redirect(current, out->location, next, sizeof next);
        if (rs != SF_OK) {
            sf_response_free(out);
            out->status = rs;
            return rs;
        }

        sf_response_free(out);
        memcpy(current, next, strlen(next) + 1);
    }
}
