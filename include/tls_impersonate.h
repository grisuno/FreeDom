#ifndef FREEDOM_TLS_IMPERSONATE_H
#define FREEDOM_TLS_IMPERSONATE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * tls_impersonate (prefix ti_) — pure decision + IPC codec for the TLS ClientHello
 * impersonation helper. See spec/tls_impersonate.md.
 *
 * NO I/O, NO global mutable state (the directly auditable surface). The transport
 * (fork/exec of the freedom-tls-helper worker, the socketpair round-trip, the
 * BoringSSL handshake) lives in the orchestrator; this module is the two pure,
 * testable, fuzzable pieces:
 *
 *   1. ti_should_impersonate() — the TRIPLE opt-in gate. A host uses the
 *      Chrome-blending TLS route ONLY when it is simultaneously on allow.conf,
 *      js.conf AND impersonate.conf. Any missing signal fails closed to the default
 *      hardened OpenSSL path. This is the sole place the helper is authorized.
 *
 *   2. ti_encode_x / ti_decode_x — the length-prefixed, fail-closed serialization of
 *      the parent<->helper request/response. Every field is bounded (TI_MAX_*);
 *      any truncated, over-cap or malformed frame is rejected without overrun.
 *
 * The response carries the peer certificate chain (DER) and the negotiated group so
 * the TRUSTED PARENT re-applies the strength policy (RSA<3072 leaf, SHA-1 fatal,
 * hybrid-KE) with OpenSSL over what BoringSSL actually verified. Authenticity is
 * done in the helper (VERIFYPEER); strength is re-checked in the parent.
 */

/* Browser profile imitated on the wire. Owner decision (2026-07-12):
 * TI_PROFILE_CHROME_CLASSIC — maximally-common JA3, CLASSICAL key exchange (no
 * X25519MLKEM768) on this route, accepted per-host via impersonate.conf. */
typedef enum ti_profile {
    TI_PROFILE_CHROME_CLASSIC = 0,
    TI_PROFILE_CHROME_MLKEM   = 1   /* reserved: would keep PQ KE; not the default */
} ti_profile;

/*
 * The triple opt-in gate (pure). Returns 1 IFF all three signals are set:
 *   host_in_allowlist  — an explicit allow.conf entry (hb_is_allowlisted)
 *   host_js_enabled    — JS permitted for this host (js_policy / js.conf)
 *   host_in_impersonate— an explicit impersonate.conf entry (hb_is_allowlisted on
 *                        the impersonate set)
 * Any zero => 0 (fail-closed: the default hardened OpenSSL path is used). A global
 * JSP_ON does NOT substitute for the explicit allow.conf / impersonate.conf entries.
 */
int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          int host_in_impersonate);

/* Anti-DoS bounds: a hostile helper or a corrupt frame must never overrun. */
#define TI_MAGIC          0x54494D50u        /* "TIMP" */
#define TI_MAX_URL        8192u
#define TI_MAX_METHOD     16u
#define TI_MAX_HEADERS    16384u
#define TI_MAX_BODY       (16u * 1024u * 1024u)
#define TI_MAX_RESP_HDR   65536u
#define TI_MAX_RESP_BODY  (32u * 1024u * 1024u)
#define TI_MAX_CHAIN      (64u * 1024u)
#define TI_MAX_GROUP      64u

/* Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied);
 * ti_decode_req allocates its own copies, released by ti_req_free. */
typedef struct ti_req {
    const char   *url;        /* https only on this route (bounded TI_MAX_URL) */
    const char   *method;     /* "GET" / "POST" (bounded TI_MAX_METHOD) */
    const char   *headers;    /* CRLF-joined, already normalized by the parent */
    const uint8_t *body;
    size_t        body_len;
    ti_profile    profile;
} ti_req;

/* Response: helper -> parent. ti_decode_resp allocates; ti_resp_free releases. */
typedef struct ti_resp {
    long      status;         /* HTTP status; 0 => transport/verification failure */
    char     *headers;        /* NUL-terminated response headers (owned) */
    uint8_t  *body;
    size_t    body_len;
    uint8_t  *peer_chain_der; /* chain BoringSSL verified (owned); may be NULL */
    size_t    peer_chain_len;
    char      negotiated_group[TI_MAX_GROUP]; /* e.g. "x25519" (NUL-terminated) */
    long      tls_version;    /* CURL_SSLVERSION_* negotiated */
} ti_resp;

/*
 * Serialization over the socketpair. All little-endian, length-prefixed, fail-closed.
 *   ti_encode_*  returns bytes written, or 0 if the frame would not fit out_cap or a
 *                field exceeds its TI_MAX_* bound.
 *   ti_decode_*  returns 0 on success (out fully populated), <0 on any malformed,
 *                truncated or over-cap input (out left zeroed / owned buffers freed).
 */
size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap);
int    ti_decode_req(const uint8_t *in, size_t len, ti_req *out);
void   ti_req_free(ti_req *r);

size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);
int    ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);
void   ti_resp_free(ti_resp *r);

#endif /* FREEDOM_TLS_IMPERSONATE_H */
