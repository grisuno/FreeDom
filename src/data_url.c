/*
 * data_url — implementation: pure RFC 2397 "data:" URL parsing + RFC 4648 base64
 * decoding.
 *
 * See include/data_url.h and spec/data_url.md for the full contract and the
 * rationale for skipping the network-only checks (https scheme, third-party host,
 * tracking-pixel heuristic) that render_policy applies to remote images: a data:
 * URI never opens a socket.
 */

#include "data_url.h"

#include <stdlib.h>
#include <string.h>

static int lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

static int ci_starts_with(const char *s, const char *prefix) {
    while (*prefix) {
        if (*s == '\0' || lower((unsigned char)*s) != lower((unsigned char)*prefix)) return 0;
        ++s; ++prefix;
    }
    return 1;
}

int du_is_data_url(const char *url) {
    return url != NULL && ci_starts_with(url, "data:");
}

du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len) {
    if (url == NULL || payload == NULL || payload_len == NULL) return DU_ERR_NULL_ARG;
    if (!du_is_data_url(url)) return DU_ERR_NOT_DATA_URL;

    const char *p = url + 5; /* skip "data:" */
    const char *comma = strchr(p, ',');
    if (comma == NULL) return DU_ERR_NOT_BASE64;

    static const char TAG[] = ";base64";
    size_t taglen = sizeof(TAG) - 1;
    size_t header_len = (size_t)(comma - p);
    if (header_len < taglen) return DU_ERR_NOT_BASE64;

    const char *flag = comma - taglen;
    for (size_t i = 0; i < taglen; ++i) {
        if (lower((unsigned char)flag[i]) != TAG[i]) return DU_ERR_NOT_BASE64;
    }

    const char *data = comma + 1;
    size_t data_len = strlen(data);
    if (data_len > DU_MAX_ENCODED_LEN) return DU_ERR_TOO_LARGE;

    *payload = data;
    *payload_len = data_len;
    return DU_OK;
}

/* 0-63 for a base64 alphabet character, -1 otherwise. Kept as a small function
 * (not a 256-entry table) so the mapping stays trivially auditable. */
static int b64_val(unsigned char c) {
    if (c >= 'A' && c <= 'Z') return (int)(c - 'A');
    if (c >= 'a' && c <= 'z') return (int)(c - 'a') + 26;
    if (c >= '0' && c <= '9') return (int)(c - '0') + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len) {
    if (out == NULL || out_len == NULL || (b64 == NULL && b64_len != 0)) return DU_ERR_NULL_ARG;
    if (b64_len > DU_MAX_ENCODED_LEN) return DU_ERR_TOO_LARGE;
    if (b64_len % 4u != 0u) return DU_ERR_BAD_BASE64;

    size_t pad = 0;
    if (b64_len >= 1 && b64[b64_len - 1] == '=') pad++;
    if (b64_len >= 2 && b64[b64_len - 2] == '=') pad++;
    for (size_t i = 0; i + pad < b64_len; ++i) {
        if (b64[i] == '=') return DU_ERR_BAD_BASE64; /* padding outside the tail */
    }

    size_t out_cap = (b64_len / 4u) * 3u - pad;
    uint8_t *buf = (uint8_t *)malloc(out_cap > 0 ? out_cap : 1);
    if (buf == NULL) return DU_ERR_OOM;

    size_t oi = 0;
    for (size_t i = 0; i < b64_len; i += 4) {
        int v[4];
        for (int j = 0; j < 4; ++j) {
            char c = b64[i + (size_t)j];
            if (c == '=') { v[j] = 0; continue; }
            int t = b64_val((unsigned char)c);
            if (t < 0) { free(buf); return DU_ERR_BAD_BASE64; }
            v[j] = t;
        }
        uint32_t triple = ((uint32_t)v[0] << 18) | ((uint32_t)v[1] << 12)
                         | ((uint32_t)v[2] << 6)  |  (uint32_t)v[3];
        if (oi < out_cap) buf[oi++] = (uint8_t)((triple >> 16) & 0xFFu);
        if (oi < out_cap) buf[oi++] = (uint8_t)((triple >> 8) & 0xFFu);
        if (oi < out_cap) buf[oi++] = (uint8_t)(triple & 0xFFu);
    }

    *out = buf;
    *out_len = out_cap;
    return DU_OK;
}

static int hexval(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int ascii_ws(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r';
}

/* Case-insensitive suffix test on [s, s+n). */
static int ends_ci(const char *s, size_t n, const char *suf) {
    size_t m = strlen(suf);
    if (n < m) return 0;
    for (size_t i = 0; i < m; ++i) {
        char a = s[n - m + i], b = suf[i];
        if (a >= 'A' && a <= 'Z') a = (char)(a + 32);
        if (a != b) return 0;
    }
    return 1;
}

du_status du_decode(const char *url, char *mime, size_t mime_cap, uint8_t **out, size_t *out_len) {
    if (url == NULL || out == NULL || out_len == NULL) return DU_ERR_NULL_ARG;
    *out = NULL;
    *out_len = 0;
    if (mime != NULL && mime_cap != 0) mime[0] = '\0';
    if (!du_is_data_url(url)) return DU_ERR_NOT_DATA_URL;
    const char *meta = url + 5;
    const char *comma = strchr(meta, ',');
    if (comma == NULL) return DU_ERR_NOT_BASE64;
    const char *body = comma + 1;
    size_t blen = strlen(body);
    if (blen > DU_MAX_ENCODED_LEN) return DU_ERR_TOO_LARGE;

    /* Media type: before the comma, minus a trailing ";base64", trimmed. */
    size_t ml = (size_t)(comma - meta);
    int is_b64 = 0;
    {
        size_t t = ml;
        while (t > 0 && ascii_ws(meta[t - 1])) --t;
        if (ends_ci(meta, t, ";base64")) { is_b64 = 1; ml = t - 7; }
    }
    size_t ms = 0;
    while (ms < ml && ascii_ws(meta[ms])) ++ms;
    while (ml > ms && ascii_ws(meta[ml - 1])) --ml;
    if (mime != NULL && mime_cap != 0) {
        const char *src = meta + ms;
        size_t n = ml - ms;
        if (n == 0) { src = "text/plain;charset=US-ASCII"; n = strlen(src); }
        if (n >= mime_cap) n = mime_cap - 1;
        memcpy(mime, src, n);
        mime[n] = '\0';
    }

    if (is_b64) {
        /* Forgiving base64 (WHATWG Infra): drop ASCII whitespace, padding optional. */
        char *clean = (char *)malloc(blen + 4);
        if (clean == NULL) return DU_ERR_OOM;
        size_t n = 0;
        for (size_t i = 0; i < blen; ++i)
            if (!ascii_ws(body[i])) clean[n++] = body[i];
        while (n > 0 && clean[n - 1] == '=') --n;      /* re-pad canonically below */
        if (n % 4 == 1) { free(clean); return DU_ERR_BAD_BASE64; }
        while (n % 4 != 0) clean[n++] = '=';
        uint8_t *bytes = NULL;
        size_t len = 0;
        du_status st = du_base64_decode(clean, n, &bytes, &len);
        free(clean);
        if (st != DU_OK) return st;
        uint8_t *z = (uint8_t *)realloc(bytes, len + 1);   /* NUL-terminate */
        if (z == NULL) { free(bytes); return DU_ERR_OOM; }
        z[len] = 0;
        *out = z;
        *out_len = len;
        return DU_OK;
    }

    /* Percent-decoding: "%XX" is a byte; any other '%' stays literal. */
    uint8_t *o = (uint8_t *)malloc(blen + 1);
    if (o == NULL) return DU_ERR_OOM;
    size_t n = 0;
    for (size_t i = 0; i < blen; ++i) {
        int hi, lo;
        if (body[i] == '%' && i + 2 < blen        /* both hex digits exist */
            && (hi = hexval(body[i + 1])) >= 0 && (lo = hexval(body[i + 2])) >= 0) {
            o[n++] = (uint8_t)((hi << 4) | lo);
            i += 2;
        } else {
            o[n++] = (uint8_t)body[i];
        }
    }
    o[n] = 0;
    *out = o;
    *out_len = n;
    return DU_OK;
}
