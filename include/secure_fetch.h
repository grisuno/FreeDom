#ifndef FREEDOM_SECURE_FETCH_H
#define FREEDOM_SECURE_FETCH_H

#include <stddef.h>
#include <stdint.h>

#include "anti_fp.h" /* normalized network identity (User-Agent / Accept-Language) */

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * secure_fetch — the only network egress of the browser.
 *
 * Secure by default: an insecure request is not representable through this API.
 * The security logic lives in pure validators (no I/O); sf_get only orchestrates.
 *
 * See spec/secure_fetch.md for the full contract.
 */

/* Result codes. SF_OK == 0; every other value is a hard failure. */
typedef enum sf_status {
    SF_OK = 0,
    SF_ERR_NULL_ARG,     /* a required pointer argument was NULL */
    SF_ERR_INVALID_URL,  /* URL missing, malformed, or scheme != https */
    SF_ERR_TLS_VERSION,  /* negotiated protocol below TLS 1.3 */
    SF_ERR_KEM_NOT_PQ,   /* negotiated key-exchange group is not PQ-hybrid */
    SF_ERR_WEAK_ALGO,    /* chain uses a forbidden primitive (RSA < 3072, SHA-1) */
    SF_ERR_CERT_INVALID, /* certificate chain failed verification */
    SF_ERR_CERT_NOT_PQ,  /* strict policy: chain carries no PQ signature */
    SF_ERR_TOO_LARGE,    /* response body exceeded max_body_bytes */
    SF_ERR_NETWORK,      /* connect / read / timeout at the transport layer */
    SF_ERR_OOM,          /* allocation failed */
    SF_ERR_TOO_MANY_REDIRECTS, /* sf_get_follow exceeded max_redirects hops */
    SF_ERR_INTERNAL      /* transport library returned an unexpected state */
} sf_status;

/* Post-quantum enforcement policy. */
typedef enum sf_policy {
    SF_POLICY_PQ_HYBRID_KE = 0, /* default: require PQ-hybrid KE; allow classical certs */
    SF_POLICY_STRICT_PQ,        /* additionally require a PQ signature in the chain */
    SF_POLICY_PERMISSIVE,       /* keep TLS 1.3 + PQ-hybrid KE; allow weak certs on explicit user override */
    SF_POLICY_ALLOW_CLASSICAL_KE, /* navigability fallback: keep TLS 1.3 + full cert validation, but allow a
                                  * classical (non-PQ) key exchange so a non-PQ host does not block
                                  * navigation. The caller MUST surface the downgrade to the user (e.g. a
                                  * toast). Only the PQ-ness of the KE is relaxed; nothing else. */
    SF_POLICY_ALLOWLISTED_INSECURE /* explicit per-host user override (the allowlist): navigate a site below
                                  * Freedom's elevated standard. Accepts TLS 1.2 (min; 1.3 still preferred),
                                  * a classical KE, and weak-but-valid leaf primitives (RSA < 3072, SHA-1).
                                  * The certificate chain is STILL authenticated (transport VERIFYPEER stays
                                  * on): this relaxes crypto strength, never authenticity -- you reach the
                                  * real site over older crypto, not an impostor. Below TLS 1.2 is refused.
                                  * The caller MUST warn the user. This is the "not a dictatorship" escape
                                  * hatch: secure by default, but the user is sovereign over their own hosts. */
} sf_policy;

/* Minimal view of the verified certificate chain, used by sf_check_chain_policy.
 * Kept as plain data so the policy check is a pure, directly testable function. */
typedef struct sf_chain_info {
    const char *leaf_sig_alg; /* e.g. "ML-DSA-65", "rsaEncryption", "ecdsa-with-SHA256" */
    int         rsa_bits;     /* end-entity (leaf) RSA modulus size in bits, or 0 if leaf is not RSA */
    int         uses_sha1;    /* nonzero if any cert in the chain was signed with SHA-1 */
    int         has_pq_sig;   /* nonzero if any cert in the chain uses an ML-DSA/SLH-DSA sig */
} sf_chain_info;

/* Socket-level anonymity proxy (Privacy by Default, Principle 3). The realm router
 * (net_realm) decides which one to use per request; secure_fetch just applies it. */
typedef enum sf_proxy_type {
    SF_PROXY_NONE = 0,  /* connect directly */
    SF_PROXY_SOCKS5H,   /* SOCKS5 with REMOTE DNS (Tor): no DNS leak, resolves .onion */
    SF_PROXY_HTTP       /* HTTP proxy (I2P) */
} sf_proxy_type;

typedef struct sf_config {
    sf_policy   policy;
    long        timeout_ms;     /* total request timeout; 0 => SF_DEFAULT_TIMEOUT_MS */
    size_t      max_body_bytes; /* hard cap on buffered response; 0 => SF_DEFAULT_MAX_BODY */
    const char *kex_groups;     /* OpenSSL group list; NULL => SF_DEFAULT_KEX_GROUPS */
    const char *user_agent;     /* User-Agent header; NULL/"" => SF_DEFAULT_USER_AGENT */
    sf_proxy_type proxy_type;   /* SF_PROXY_NONE => direct connection */
    const char *proxy_address;  /* "host:port" for the proxy; used iff proxy_type != NONE */
    int allow_overlay_http;     /* allow plain http:// (no TLS) -- ONLY for overlay realms
                                 * (.onion/.i2p) routed through their proxy, where the overlay
                                 * itself encrypts and authenticates. Never set for clearnet. */
    const char *username;       /* HTTP Basic Auth username (NULL/"" => no auth) */
    const char *password;       /* HTTP Basic Auth password (ignored when username is NULL/empty) */
    int         insecure;       /* skip TLS cert verification (self-signed/dev); default 0 */
    int         impersonate;    /* interim TLS-ClientHello blend for a triple-opt-in trusted host
                                 * (allow.conf AND js.conf AND impersonate.conf): drop the
                                 * X25519MLKEM768 group (the loudest JA3 tell under our Firefox UA)
                                 * and order the TLS 1.3 ciphersuites like the browser we already
                                 * present. Reduces the JA3-vs-UA mismatch; NOT byte-exact JA3 (that
                                 * is the BoringSSL helper, spec/tls_impersonate.md Fase 1). Only the
                                 * KE strength relaxes to classical, so the caller MUST use a
                                 * classical-KE-tolerant policy (impersonate hosts are on allow.conf
                                 * => SF_POLICY_ALLOWLISTED_INSECURE, which already tolerates it). */
    /* Sec-Fetch metadata for bot-blending (Hito 30b). All real browsers send these
     * per-section headers; their absence is a bot signal. dest/mode NULL => navigation
     * defaults ("document"/"navigate"). referrer_url is the current page URL used to
     * compute Sec-Fetch-Site (NULL => "none" for top-level navigation). */
    const char *referrer_url;    /* document URL of the initiator; NULL => top-level nav */
    const char *sec_fetch_dest;  /* NULL => "document"; set to "script"/"image"/"style" etc. */
    const char *sec_fetch_mode;  /* NULL => "navigate"; set to "no-cors"/"cors" etc. */
    /* Streaming progress: called ~1/sec during download with the accumulated body so
     * far, allowing the caller to progressively render before the full response arrives.
     * The callback runs on the curl transfer thread (same thread as sf_get), so data
     * must be copied to thread-safe storage. NULL/0 => no callback. */
    void *progress_ctx;       /* userdata for progress_cb */
    void (*progress_cb)(const uint8_t *body, size_t body_len, void *ctx);
    /* Byte-range request (HTTP Range: header). range_start >= 0 enables it;
     * range_end >= range_start specifies an inclusive end, or -1 for open-ended. */
    int64_t range_start;
    int64_t range_end;
} sf_config;

typedef struct sf_response {
    sf_status status;
    long      http_code;
    char     *tls_version;      /* owned; e.g. "TLSv1.3"; may be NULL */
    char     *negotiated_group; /* owned; e.g. "X25519MLKEM768"; may be NULL */
    uint8_t  *body;             /* owned; NUL-terminated for convenience; may be NULL */
    size_t    body_len;         /* bytes in body excluding the trailing NUL */
    char     *location;         /* owned; raw Location header value, or NULL if absent */
    char     *final_url;        /* owned; the absolute https URL that produced this body
                                 * (the last hop after sf_get_follow's redirects, or the
                                 * requested URL for sf_get); NULL if unset. The correct
                                 * base for resolving the document's relative references. */
    char     *content_type;     /* owned; the response Content-Type (e.g. "text/html;
                                 * charset=utf-8"), or NULL if the server omitted it. Used
                                 * to decide render-vs-download; never trusted to execute. */
    char     *content_disposition; /* owned; the raw Content-Disposition header value, or
                                 * NULL if absent. Hostile input (its filename is sanitized
                                 * fail-closed before any disk use; see download.h). */
} sf_response;

/* PQ-hybrid is preferred (listed first); classical groups are also offered so a
 * non-PQ host completes the TLS 1.3 handshake and yields a clean SF_ERR_KEM_NOT_PQ
 * under the strict policy (instead of an opaque handshake failure) — which lets the
 * orchestrator offer the classical-KE navigability fallback. Offering a classical
 * group never weakens the strict policy: a classical *negotiated* group is still
 * rejected by sf_check_group_is_pq. */
#define SF_DEFAULT_KEX_GROUPS  "X25519MLKEM768:X25519:secp256r1"
/* Interim impersonation ClientHello shaping (OpenSSL, Hito TLS Fase 3). A classical
 * profile consistent with FP_USER_AGENT (Firefox): it DROPS X25519MLKEM768 (almost no
 * shipping Firefox of our advertised version offers MLKEM, so offering it under that UA
 * is the single loudest TLS tell) and orders the TLS 1.3 ciphersuites Firefox-style
 * (AES-128-GCM, CHACHA20, AES-256-GCM). A Chrome ClientHello under a Firefox UA would be
 * a NEW mismatch, so the interim matches the identity we already send; byte-exact Chrome
 * JA3 is the BoringSSL helper (spec/tls_impersonate.md). Groups mirror Firefox 128's
 * supported_groups order. */
#define SF_IMPERSONATE_KEX_GROUPS    "X25519:secp256r1:secp384r1:secp521r1:ffdhe2048:ffdhe3072"
#define SF_IMPERSONATE_TLS13_CIPHERS "TLS_AES_128_GCM_SHA256:TLS_CHACHA20_POLY1305_SHA256:TLS_AES_256_GCM_SHA384"
/* Firefox 128 TLS 1.2 ciphersuite list (OpenSSL names, in wire order). OpenSSL's
 * default advertises ~80 TLS 1.2 suites; Firefox advertises ~14, so restricting the
 * list is the single biggest shrink of the JA3/JA4 cipher field toward the browser. */
#define SF_IMPERSONATE_TLS12_CIPHERS \
    "ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:" \
    "ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:" \
    "ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:" \
    "ECDHE-ECDSA-AES256-SHA:ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES128-SHA:" \
    "ECDHE-RSA-AES256-SHA:AES128-GCM-SHA256:AES256-GCM-SHA384:AES128-SHA:AES256-SHA"
/* The default User-Agent IS the anti-fingerprinting identity (FP_USER_AGENT): it
 * must match navigator.userAgent exactly and must not advertise "Freedom" (that is
 * a unique fingerprint and a bot signal that breaks sites like Google). Demoting
 * the old "Freedom/0.1" to merely a brand string was deliberate; never reintroduce
 * a product name here. The user can still override per session in the menu. */
#define SF_DEFAULT_USER_AGENT  FP_USER_AGENT
#define SF_DEFAULT_MAX_BODY    ((size_t)(16u * 1024u * 1024u))
#define SF_DEFAULT_TIMEOUT_MS  30000L
#define SF_DEFAULT_MAX_REDIRECTS 10
#define SF_MAX_URL             8192u  /* hard cap for any single URL we will act on (matches URL_MAX_LEN; modern bundler URLs exceed 2 KiB) */

/* Initialises process-global transport state (libcurl/OpenSSL) once, from the main
 * thread, before any concurrent sf_get/sf_post. libcurl's implicit init on first use
 * is NOT thread-safe, so an orchestrator that fetches from worker threads MUST call
 * this first. Idempotent; safe to call more than once. A single-threaded caller need
 * not call it. There is intentionally no cleanup: it would race in-flight fetches at
 * shutdown, and the OS reclaims everything on exit. */
void sf_global_init(void);

/* --- ephemeral session cookie jar (in-memory, never persisted) --- */

/* Builds the document.cookie view ("name=value; name=value") for url from the shared
 * in-memory jar into out (NUL-terminated, bounded), returning its length. HttpOnly
 * cookies are EXCLUDED (network-only, never exposed to JS) and expired cookies skipped.
 * Only for a TRUSTED host (the caller gates on allow.conf AND js.conf). 0 on empty/error. */
size_t sf_cookie_header_for(const char *url, char *out, size_t outsz);

/* Injects a JS-set cookie ("name=value") into the shared jar, scoped to url's host, as if
 * it arrived via Set-Cookie -- so a trusted page's document.cookie writes reach the next
 * request. namevalue past the first ';' (attributes) is ignored. No-op on malformed input. */
void sf_cookie_put(const char *url, const char *namevalue);

/* Pure: parses one CURLINFO_COOKIELIST Netscape line ("domain\\tflag\\tpath\\tsecure\\t
 * expiry\\tname\\tvalue"); if the cookie applies to (host, path), is not HttpOnly and is
 * unexpired at `now`, writes "name=value" to out (bounded) and returns 1, else 0. */
int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                           long now, char *out, size_t outsz);

/* Returns a configuration with the secure defaults applied. */
sf_config sf_config_default(void);

/* Returns ua when it is a non-empty string, else SF_DEFAULT_USER_AGENT. Pure: the
 * single place that resolves the effective User-Agent, so the orchestrator never
 * sends an empty header and the default lives in one tested spot. */
const char *sf_user_agent_or_default(const char *ua);

/* The interim impersonation ClientHello strings (pure; single source of truth so the
 * shaping is unit-testable without a live handshake). Both are classical (no MLKEM). */
const char *sf_impersonate_kex_groups(void);
const char *sf_impersonate_tls13_ciphers(void);

/* --- Pure validators (no I/O): the primary unit-test surface. --- */

/* SF_OK only for an absolute "https://host..." URL. */
sf_status sf_validate_url(const char *url);

/* SF_OK only for exactly "TLSv1.3". */
sf_status sf_check_tls_version(const char *negotiated_version);

/* SF_OK only for a PQ-hybrid group (classical KEM + ML-KEM).
 * Pure-classical and pure-PQ groups are rejected with SF_ERR_KEM_NOT_PQ. */
sf_status sf_check_group_is_pq(const char *negotiated_group);

/* Applies weak-primitive rejection in every policy; under SF_POLICY_STRICT_PQ
 * additionally requires has_pq_sig. */
sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy);

/* Enforces the full connection policy in order: TLS version, then KE group, then
 * certificate chain. Under SF_POLICY_ALLOW_CLASSICAL_KE the KE-group PQ check is
 * skipped (a classical key exchange is accepted); every other check, including the
 * full certificate-chain validation, still applies. Fails closed: a NULL chain
 * (could not be inspected) yields SF_ERR_INTERNAL rather than trusting the
 * connection. This is the exact glue sf_get applies to the negotiated state,
 * exposed as a pure function for testing. */
sf_status sf_enforce_policy(const char *tls_version, const char *group,
                            const sf_chain_info *chain, sf_policy policy);

/* --- Pure redirect logic (no I/O). --- */

/* Nonzero only for HTTP redirect status codes (301, 302, 303, 307, 308). */
int sf_is_redirect_code(long http_code);

/* Extracts the value of a "Location:" header line into out (NUL-terminated).
 * The header name is matched case-insensitively; leading whitespace and a
 * trailing CR/LF are stripped. SF_OK only when the line is a Location header
 * with a non-empty value that fits in out; otherwise SF_ERR_INVALID_URL. */
sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz);

/* Resolves a redirect target against base_url, always yielding an absolute
 * https URL in out or failing closed. Rejects downgrade to http:// and any
 * non-https scheme. The result is validated with sf_validate_url before return. */
sf_status sf_resolve_redirect(const char *base_url, const char *location,
                              char *out, size_t outsz);

/* --- Orchestrator (I/O). --- */

/* Performs an HTTPS GET under the given policy.
 * cfg == NULL is treated as sf_config_default().
 * url == NULL or out == NULL => SF_ERR_NULL_ARG (no allocation).
 * On SF_OK, *out is populated and must be released with sf_response_free.
 * On failure, out->status carries the reason and no body is allocated. */
sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out);

/* Like sf_get, but transparently follows HTTP redirects up to max_redirects
 * hops. Every hop is a fresh sf_get, so the full TLS/PQ/chain policy is enforced
 * on each connection (Zero Trust). Each target is re-validated and a downgrade
 * to http:// is refused. Exceeding max_redirects => SF_ERR_TOO_MANY_REDIRECTS.
 * On SF_OK, *out is the final response and must be released with
 * sf_response_free. max_redirects < 0 is treated as 0 (do not follow). */
sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                        int max_redirects);

/* Performs an HTTPS POST under the given policy, sending body (body_len bytes)
 * with the given Content-Type. Enforces the exact same TLS/PQ/chain policy as
 * sf_get (Zero Trust): an insecure POST is not representable. Does not follow
 * redirects (the caller inspects out->http_code / out->location and decides).
 * cfg == NULL => sf_config_default(). url == NULL / out == NULL => SF_ERR_NULL_ARG.
 * body may be NULL only when body_len == 0. content_type == NULL =>
 * application/x-www-form-urlencoded. On SF_OK, *out must be released with
 * sf_response_free. */
sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size_t body_len, const char *content_type,
                  sf_response *out);

/* Idempotent; safe on a zero-initialised struct and safe to call twice. */
void sf_response_free(sf_response *resp);

#endif /* FREEDOM_SECURE_FETCH_H */
