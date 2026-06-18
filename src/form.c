/*
 * form — implementation: pure construction of an HTML form submission.
 *
 * No I/O, no global state. The action/names/values are hostile data: encoded
 * (application/x-www-form-urlencoded) and resolved through the canonical url
 * module, never executed. Fails closed: a non-https resolved target yields
 * FM_BLOCKED rather than a downgraded request.
 */

#include "form.h"

#include <string.h>

const char FM_CONTENT_TYPE_URLENCODED[] = "application/x-www-form-urlencoded";

/* Appends one byte, keeping room for the trailing NUL. Returns -1 on overflow. */
static int put_char(char *out, size_t outsz, size_t *pos, char c) {
    if (*pos + 1 >= outsz) return -1; /* leave one slot for the NUL */
    out[(*pos)++] = c;
    return 0;
}

/* Encodes one component per the WHATWG application/x-www-form-urlencoded byte
 * serialiser. Returns -1 on overflow. */
static int enc_component(const char *s, char *out, size_t outsz, size_t *pos) {
    static const char hex[] = "0123456789ABCDEF";
    for (const unsigned char *p = (const unsigned char *)s; *p != '\0'; ++p) {
        unsigned char b = *p;
        if (b == 0x20) {
            if (put_char(out, outsz, pos, '+') != 0) return -1;
        } else if (b == 0x2A || b == 0x2D || b == 0x2E || b == 0x5F
                || (b >= '0' && b <= '9') || (b >= 'A' && b <= 'Z') || (b >= 'a' && b <= 'z')) {
            if (put_char(out, outsz, pos, (char)b) != 0) return -1;
        } else {
            if (put_char(out, outsz, pos, '%') != 0) return -1;
            if (put_char(out, outsz, pos, hex[b >> 4]) != 0) return -1;
            if (put_char(out, outsz, pos, hex[b & 0x0F]) != 0) return -1;
        }
    }
    return 0;
}

fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz, size_t *out_len) {
    if (out == NULL || outsz == 0) return FM_ERR_NULL_ARG;
    if (n > 0 && fields == NULL) return FM_ERR_NULL_ARG;

    out[0] = '\0';
    size_t pos = 0;
    int first = 1;
    for (size_t i = 0; i < n; ++i) {
        if (fields[i].name == NULL) continue; /* a nameless control is not submitted */
        if (!first && put_char(out, outsz, &pos, '&') != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; }
        first = 0;
        if (enc_component(fields[i].name, out, outsz, &pos) != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; }
        if (put_char(out, outsz, &pos, '=') != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; }
        const char *v = (fields[i].value != NULL) ? fields[i].value : "";
        if (enc_component(v, out, outsz, &pos) != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; }
    }
    out[pos] = '\0';
    if (out_len != NULL) *out_len = pos;
    return FM_OK;
}

/* Copies src into dst if it fits (including the NUL). Returns -1 on overflow. */
static int copy_fit(char *dst, size_t dstsz, const char *src) {
    size_t n = strlen(src);
    if (n + 1 > dstsz) return -1;
    memcpy(dst, src, n + 1);
    return 0;
}

/* Removes TAB/LF/CR and trims leading/trailing ASCII spaces (WHATWG cleaning of a
 * URL-bearing attribute). Returns -1 if the cleaned value does not fit. */
static int clean_action(const char *action, char *out, size_t outsz) {
    size_t o = 0;
    for (const char *p = action; *p != '\0'; ++p) {
        char c = *p;
        if (c == '\t' || c == '\n' || c == '\r') continue;
        if (o + 1 >= outsz) return -1;
        out[o++] = c;
    }
    out[o] = '\0';
    size_t s = 0, e = o;
    while (s < e && out[s] == ' ') ++s;
    while (e > s && out[e - 1] == ' ') --e;
    if (s > 0) memmove(out, out + s, e - s);
    out[e - s] = '\0';
    return 0;
}

/* Truncates url at the first '?' or '#' (drops query and fragment in place). */
static void strip_query(char *url) {
    for (char *p = url; *p != '\0'; ++p) {
        if (*p == '?' || *p == '#') { *p = '\0'; return; }
    }
}

/* Resolves the cleaned action into a validated absolute https URL R, or returns a
 * block reason. */
static fm_block_reason resolve_target(const char *base, const char *act,
                                      char *R, size_t Rsz) {
    if (act[0] == '\0') {
        /* No action: submit to the current document URL (must be https). */
        if (url_validate_https(base) != URL_OK) return FM_BLOCK_INSECURE;
        return (copy_fit(R, Rsz, base) != 0) ? FM_BLOCK_OVERFLOW : FM_BLOCK_NONE;
    }
    if (url_is_https(act)) {
        /* Absolute https action: valid regardless of the base (e.g. a local test
         * page pointing at a real search engine). */
        if (url_validate_https(act) != URL_OK) return FM_BLOCK_INSECURE;
        return (copy_fit(R, Rsz, act) != 0) ? FM_BLOCK_OVERFLOW : FM_BLOCK_NONE;
    }
    /* Relative / absolute-path / scheme-relative: needs an https base. */
    url_status us = url_resolve_https(base, act, R, Rsz);
    if (us == URL_ERR_OVERFLOW) return FM_BLOCK_OVERFLOW;
    return (us == URL_OK) ? FM_BLOCK_NONE : FM_BLOCK_INSECURE;
}

fm_status fm_build(const char *base, const char *action, fm_method method,
                   const fm_field *fields, size_t n, fm_plan *out) {
    if (base == NULL || out == NULL) return FM_ERR_NULL_ARG;

    memset(out, 0, sizeof *out); /* url/body empty, body_len 0 */
    out->kind = FM_BLOCKED;
    out->reason = FM_BLOCK_NONE;
    out->content_type = NULL;

    if (n > FM_MAX_FIELDS) { out->reason = FM_BLOCK_INVALID; return FM_OK; }
    if (n > 0 && fields == NULL) { out->reason = FM_BLOCK_INVALID; return FM_OK; }
    for (size_t i = 0; i < n; ++i) {
        if (fields[i].name == NULL) { out->reason = FM_BLOCK_INVALID; return FM_OK; }
    }

    char act[URL_MAX_LEN + 1];
    if (action == NULL) {
        act[0] = '\0';
    } else if (clean_action(action, act, sizeof act) != 0) {
        out->reason = FM_BLOCK_OVERFLOW;
        return FM_OK;
    }

    char R[FM_URL_MAX];
    fm_block_reason rr = resolve_target(base, act, R, sizeof R);
    if (rr != FM_BLOCK_NONE) { out->reason = rr; return FM_OK; }

    char enc[FM_BODY_MAX];
    size_t enc_len = 0;
    if (fm_encode(fields, n, enc, sizeof enc, &enc_len) != FM_OK) {
        out->reason = FM_BLOCK_OVERFLOW;
        return FM_OK;
    }

    if (method == FM_POST) {
        if (copy_fit(out->url, sizeof out->url, R) != 0) {
            out->url[0] = '\0';
            out->reason = FM_BLOCK_OVERFLOW;
            return FM_OK;
        }
        memcpy(out->body, enc, enc_len + 1); /* enc is NUL-terminated */
        out->body_len = enc_len;
        out->content_type = FM_CONTENT_TYPE_URLENCODED;
        out->kind = FM_POST_REQUEST;
        out->reason = FM_BLOCK_NONE;
        return FM_OK;
    }

    /* GET: replace the action's query with the form data set. */
    strip_query(R);
    size_t rlen = strlen(R);
    if (rlen + 1 /* '?' */ + enc_len + 1 /* NUL */ > sizeof out->url) {
        out->reason = FM_BLOCK_OVERFLOW;
        return FM_OK;
    }
    size_t p = 0;
    memcpy(out->url + p, R, rlen); p += rlen;
    out->url[p++] = '?';
    memcpy(out->url + p, enc, enc_len); p += enc_len;
    out->url[p] = '\0';

    /* Defence in depth: the assembled GET URL must still be a valid https URL. */
    if (url_validate_https(out->url) != URL_OK) {
        out->url[0] = '\0';
        out->reason = FM_BLOCK_INSECURE;
        return FM_OK;
    }
    out->body_len = 0;
    out->content_type = NULL;
    out->kind = FM_NAVIGATE;
    out->reason = FM_BLOCK_NONE;
    return FM_OK;
}
