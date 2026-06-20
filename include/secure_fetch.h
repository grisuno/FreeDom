#ifndef FREEDOM_SECURE_FETCH_H
#define FREEDOM_SECURE_FETCH_H

#include <stddef.h>
#include <stdint.h>

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

typedef struct sf_config {
    sf_policy   policy;
    long        timeout_ms;     /* total request timeout; 0 => SF_DEFAULT_TIMEOUT_MS */
    size_t      max_body_bytes; /* hard cap on buffered response; 0 => SF_DEFAULT_MAX_BODY */
    const char *kex_groups;     /* OpenSSL group list; NULL => SF_DEFAULT_KEX_GROUPS */
    const char *user_agent;     /* User-Agent header; NULL/"" => SF_DEFAULT_USER_AGENT */
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
} sf_response;

/* PQ-hybrid is preferred (listed first); classical groups are also offered so a
 * non-PQ host completes the TLS 1.3 handshake and yields a clean SF_ERR_KEM_NOT_PQ
 * under the strict policy (instead of an opaque handshake failure) — which lets the
 * orchestrator offer the classical-KE navigability fallback. Offering a classical
 * group never weakens the strict policy: a classical *negotiated* group is still
 * rejected by sf_check_group_is_pq. */
#define SF_DEFAULT_KEX_GROUPS  "X25519MLKEM768:X25519:secp256r1"
#define SF_DEFAULT_USER_AGENT  "Freedom/0.1"
#define SF_DEFAULT_MAX_BODY    ((size_t)(16u * 1024u * 1024u))
#define SF_DEFAULT_TIMEOUT_MS  30000L
#define SF_DEFAULT_MAX_REDIRECTS 10
#define SF_MAX_URL             2048u  /* hard cap for any single URL we will act on */

/* Returns a configuration with the secure defaults applied. */
sf_config sf_config_default(void);

/* Returns ua when it is a non-empty string, else SF_DEFAULT_USER_AGENT. Pure: the
 * single place that resolves the effective User-Agent, so the orchestrator never
 * sends an empty header and the default lives in one tested spot. */
const char *sf_user_agent_or_default(const char *ua);

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
