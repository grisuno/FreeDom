/*
 * tls_impersonate — pure decision + IPC codec for the TLS ClientHello impersonation
 * helper. See spec/tls_impersonate.md and include/tls_impersonate.h.
 *
 * No I/O, no global state. Two pieces: the triple opt-in gate, and a little-endian,
 * length-prefixed, fail-closed serialization of the parent<->helper messages. Every
 * length is validated against a TI_MAX_* bound before allocation, so a hostile or
 * corrupt frame can never drive an over-read or an unbounded allocation.
 */

#include "tls_impersonate.h"

#include <stdlib.h>
#include <string.h>

/* --- the triple opt-in gate --- */

int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          int host_in_impersonate) {
    return (host_in_allowlist && host_js_enabled && host_in_impersonate) ? 1 : 0;
}

/* --- bounded string length (no dependency on strnlen / feature macros) --- */

static size_t bounded_len(const char *s, size_t max) {
    size_t i = 0;
    while (i < max && s[i] != '\0') i++;
    return i;
}

/* --- writer: accumulates into a fixed buffer, latches overflow, never overruns --- */

typedef struct { uint8_t *p; size_t cap; size_t off; int ovf; } ti_wr;

static void put_u8(ti_wr *w, uint8_t v) {
    if (w->ovf || w->off + 1u > w->cap) { w->ovf = 1; return; }
    w->p[w->off++] = v;
}

static void put_u32(ti_wr *w, uint32_t v) {
    if (w->ovf || w->off + 4u > w->cap) { w->ovf = 1; return; }
    w->p[w->off++] = (uint8_t)(v & 0xffu);
    w->p[w->off++] = (uint8_t)((v >> 8) & 0xffu);
    w->p[w->off++] = (uint8_t)((v >> 16) & 0xffu);
    w->p[w->off++] = (uint8_t)((v >> 24) & 0xffu);
}

static void put_u64(ti_wr *w, uint64_t v) {
    if (w->ovf || w->off + 8u > w->cap) { w->ovf = 1; return; }
    for (int i = 0; i < 8; ++i) w->p[w->off++] = (uint8_t)((v >> (8 * i)) & 0xffu);
}

static void put_blob(ti_wr *w, const uint8_t *b, size_t n) {
    put_u32(w, (uint32_t)n);
    if (w->ovf) return;
    if (w->off + n > w->cap) { w->ovf = 1; return; }
    if (n != 0 && b != NULL) { memcpy(w->p + w->off, b, n); w->off += n; }
    else if (n != 0) { w->ovf = 1; } /* claimed length with no data: refuse */
}

/* --- reader: bounds-checked, latches error, allocates owned copies --- */

typedef struct { const uint8_t *p; size_t len; size_t off; int err; } ti_rd;

static uint8_t get_u8(ti_rd *r) {
    if (r->err || r->off + 1u > r->len) { r->err = 1; return 0; }
    return r->p[r->off++];
}

static uint32_t get_u32(ti_rd *r) {
    if (r->err || r->off + 4u > r->len) { r->err = 1; return 0; }
    uint32_t v = (uint32_t)r->p[r->off]
               | ((uint32_t)r->p[r->off + 1] << 8)
               | ((uint32_t)r->p[r->off + 2] << 16)
               | ((uint32_t)r->p[r->off + 3] << 24);
    r->off += 4;
    return v;
}

static uint64_t get_u64(ti_rd *r) {
    if (r->err || r->off + 8u > r->len) { r->err = 1; return 0; }
    uint64_t v = 0;
    for (int i = 0; i < 8; ++i) v |= (uint64_t)r->p[r->off + i] << (8 * i);
    r->off += 8;
    return v;
}

/* Reads a length-prefixed byte blob (<= cap). n==0 yields (NULL,0). */
static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len) {
    *out = NULL; *out_len = 0;
    uint32_t n = get_u32(r);
    if (r->err) return;
    if ((size_t)n > cap || r->off + (size_t)n > r->len) { r->err = 1; return; }
    if (n == 0) return;
    uint8_t *b = malloc(n);
    if (b == NULL) { r->err = 1; return; }
    memcpy(b, r->p + r->off, n);
    r->off += n;
    *out = b; *out_len = n;
}

/* Reads a length-prefixed string (<= cap chars), NUL-terminates it. */
static char *get_str(ti_rd *r, size_t cap) {
    uint32_t n = get_u32(r);
    if (r->err) return NULL;
    if ((size_t)n > cap || r->off + (size_t)n > r->len) { r->err = 1; return NULL; }
    if (n == UINT32_MAX) { r->err = 1; return NULL; }
    char *s = malloc((size_t)n + 1u);
    if (s == NULL) { r->err = 1; return NULL; }
    if (n != 0) memcpy(s, r->p + r->off, n);
    s[n] = '\0';
    r->off += n;
    return s;
}

static int valid_profile(int p) {
    return p == TI_PROFILE_CHROME_CLASSIC || p == TI_PROFILE_CHROME_MLKEM;
}

/* --- request codec --- */

size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap) {
    if (r == NULL || out == NULL) return 0;
    if (r->url == NULL || r->method == NULL || r->headers == NULL) return 0;
    if (!valid_profile((int)r->profile)) return 0;
    size_t ul = strlen(r->url), ml = strlen(r->method), hl = strlen(r->headers);
    if (ul > TI_MAX_URL || ml > TI_MAX_METHOD || hl > TI_MAX_HEADERS
     || r->body_len > TI_MAX_BODY) return 0;

    ti_wr w = { out, out_cap, 0, 0 };
    put_u32(&w, TI_MAGIC);
    put_u8(&w, (uint8_t)r->profile);
    put_blob(&w, (const uint8_t *)r->url, ul);
    put_blob(&w, (const uint8_t *)r->method, ml);
    put_blob(&w, (const uint8_t *)r->headers, hl);
    put_blob(&w, r->body, r->body_len);
    return w.ovf ? 0 : w.off;
}

int ti_decode_req(const uint8_t *in, size_t len, ti_req *out) {
    if (in == NULL || out == NULL) return -1;
    memset(out, 0, sizeof *out);

    ti_rd r = { in, len, 0, 0 };
    uint32_t magic = get_u32(&r);
    if (r.err || magic != TI_MAGIC) return -1;
    uint8_t prof = get_u8(&r);
    if (r.err || !valid_profile(prof)) return -1;

    char *url = get_str(&r, TI_MAX_URL);
    char *method = get_str(&r, TI_MAX_METHOD);
    char *headers = get_str(&r, TI_MAX_HEADERS);
    uint8_t *body = NULL; size_t body_len = 0;
    get_bytes(&r, TI_MAX_BODY, &body, &body_len);

    if (r.err || r.off != r.len) {
        free(url); free(method); free(headers); free(body);
        return -1;
    }
    out->url = url; out->method = method; out->headers = headers;
    out->body = body; out->body_len = body_len;
    out->profile = (ti_profile)prof;
    return 0;
}

void ti_req_free(ti_req *r) {
    if (r == NULL) return;
    free((void *)r->url);
    free((void *)r->method);
    free((void *)r->headers);
    free((void *)r->body);
    memset(r, 0, sizeof *r);
}

/* --- response codec --- */

size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap) {
    if (r == NULL || out == NULL) return 0;
    const char *hdr = (r->headers != NULL) ? r->headers : "";
    size_t hl = strlen(hdr);
    size_t gl = bounded_len(r->negotiated_group, TI_MAX_GROUP);
    if (hl > TI_MAX_RESP_HDR || r->body_len > TI_MAX_RESP_BODY
     || r->peer_chain_len > TI_MAX_CHAIN || gl >= TI_MAX_GROUP) return 0;

    ti_wr w = { out, out_cap, 0, 0 };
    put_u32(&w, TI_MAGIC);
    put_u64(&w, (uint64_t)(int64_t)r->status);
    put_blob(&w, (const uint8_t *)hdr, hl);
    put_blob(&w, r->body, r->body_len);
    put_blob(&w, r->peer_chain_der, r->peer_chain_len);
    put_blob(&w, (const uint8_t *)r->negotiated_group, gl);
    put_u64(&w, (uint64_t)(int64_t)r->tls_version);
    return w.ovf ? 0 : w.off;
}

int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out) {
    if (in == NULL || out == NULL) return -1;
    memset(out, 0, sizeof *out);

    ti_rd r = { in, len, 0, 0 };
    uint32_t magic = get_u32(&r);
    if (r.err || magic != TI_MAGIC) return -1;
    uint64_t status = get_u64(&r);
    char *hdr = get_str(&r, TI_MAX_RESP_HDR);
    uint8_t *body = NULL; size_t body_len = 0;
    get_bytes(&r, TI_MAX_RESP_BODY, &body, &body_len);
    uint8_t *chain = NULL; size_t chain_len = 0;
    get_bytes(&r, TI_MAX_CHAIN, &chain, &chain_len);
    char *grp = get_str(&r, TI_MAX_GROUP - 1u);
    uint64_t ver = get_u64(&r);

    if (r.err || r.off != r.len) {
        free(hdr); free(body); free(chain); free(grp);
        return -1;
    }
    out->status = (long)(int64_t)status;
    out->headers = hdr;
    out->body = body; out->body_len = body_len;
    out->peer_chain_der = chain; out->peer_chain_len = chain_len;
    if (grp != NULL) {
        size_t gl = bounded_len(grp, TI_MAX_GROUP - 1u);
        memcpy(out->negotiated_group, grp, gl);
        out->negotiated_group[gl] = '\0';
        free(grp);
    }
    out->tls_version = (long)(int64_t)ver;
    return 0;
}

void ti_resp_free(ti_resp *r) {
    if (r == NULL) return;
    free(r->headers);
    free(r->body);
    free(r->peer_chain_der);
    memset(r, 0, sizeof *r);
}
