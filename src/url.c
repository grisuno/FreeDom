/*
 * url — implementation: pure URL validation and reference resolution.
 *
 * No I/O, no global state, no TLS stack. RFC 3986 relative resolution with
 * dot-segment canonicalisation. Fails closed: a non-https result is never
 * produced; every assembly is bounded and reports overflow rather than truncate.
 */

#include "url.h"

#include <string.h>

/* --- small ASCII helpers (no locale dependence) --- */

/* Case-insensitive: does haystack start with prefix? */
static int ci_prefix(const char *haystack, const char *prefix) {
    while (*prefix) {
        int ch = (unsigned char)*haystack, cp = (unsigned char)*prefix;
        if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
        if (cp >= 'A' && cp <= 'Z') cp += 'a' - 'A';
        if (ch != cp) return 0;
        ++haystack; ++prefix;
    }
    return 1;
}

/* Bounded copy: out gets src (NUL-terminated). Nonzero on overflow. */
static int copy_checked(char *out, size_t outsz, const char *src) {
    size_t n = strlen(src);
    if (n + 1 > outsz) return -1;
    memcpy(out, src, n + 1);
    return 0;
}

/* Bounded append: out += src. Nonzero on overflow. */
static int cat_checked(char *out, size_t outsz, const char *src) {
    size_t cur = strlen(out);
    size_t n = strlen(src);
    if (cur + n + 1 > outsz) return -1;
    memcpy(out + cur, src, n + 1);
    return 0;
}

/* Bounded append of the first n bytes of src. Nonzero on overflow. */
static int ncat_checked(char *out, size_t outsz, const char *src, size_t n) {
    size_t cur = strlen(out);
    if (cur + n + 1 > outsz) return -1;
    memcpy(out + cur, src, n);
    out[cur + n] = '\0';
    return 0;
}

/* --- public: scheme / validation --- */

int url_has_scheme(const char *s) {
    if (s == NULL) return 0;
    char c0 = s[0];
    if (!((c0 >= 'A' && c0 <= 'Z') || (c0 >= 'a' && c0 <= 'z'))) return 0;
    for (size_t i = 1; s[i] != '\0'; ++i) {
        char c = s[i];
        if (c == ':') return 1;
        int ok = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
              || (c >= '0' && c <= '9') || c == '+' || c == '-' || c == '.';
        if (!ok) return 0;
    }
    return 0;
}

int url_is_https(const char *s) {
    if (s == NULL) return 0;
    if (!ci_prefix(s, "https://")) return 0;
    const char *host = s + 8; /* strlen("https://") */
    return (host[0] != '\0' && host[0] != '/') ? 1 : 0;
}

url_status url_validate_https(const char *url) {
    if (url == NULL) return URL_ERR_NULL_ARG;
    return url_is_https(url) ? URL_OK : URL_ERR_NOT_HTTPS;
}

size_t url_authority_len(const char *url) {
    size_t i = 8; /* strlen("https://"); url assumed validated to start with it */
    while (url[i] != '\0' && url[i] != '/') ++i;
    return i;
}

/* --- public: dot-segment removal (RFC 3986 section 5.2.4) --- */

/* Removes the last path segment (and its preceding '/') from out[0..*olen). */
static void out_pop_segment(char *out, size_t *olen) {
    size_t n = *olen;
    while (n > 0 && out[n - 1] != '/') --n;
    if (n > 0) --n; /* drop the '/' itself */
    *olen = n;
}

url_status url_remove_dot_segments(const char *path, char *out, size_t outsz) {
    if (path == NULL || out == NULL || outsz == 0) return URL_ERR_NULL_ARG;

    char work[URL_MAX_LEN + 1];
    size_t plen = strlen(path);
    if (plen + 1 > sizeof work) return URL_ERR_OVERFLOW;
    memcpy(work, path, plen + 1);

    char  *in = work;
    size_t olen = 0;

    while (*in != '\0') {
        if (strncmp(in, "../", 3) == 0) {
            in += 3;
        } else if (strncmp(in, "./", 2) == 0) {
            in += 2;
        } else if (strncmp(in, "/./", 3) == 0) {
            in += 2; /* leaves a leading '/' on the remainder */
        } else if (strcmp(in, "/.") == 0) {
            in[1] = '\0'; /* becomes "/" */
        } else if (strncmp(in, "/../", 4) == 0) {
            in += 3;
            out_pop_segment(out, &olen);
        } else if (strcmp(in, "/..") == 0) {
            in[1] = '\0'; /* becomes "/" */
            out_pop_segment(out, &olen);
        } else if (strcmp(in, ".") == 0 || strcmp(in, "..") == 0) {
            in += strlen(in);
        } else {
            /* Move the first path segment (the leading '/' if any, then bytes up
             * to but not including the next '/') from in to out. */
            size_t seg = (in[0] == '/') ? 1 : 0;
            while (in[seg] != '\0' && in[seg] != '/') ++seg;
            for (size_t k = 0; k < seg; ++k) {
                if (olen + 1 >= outsz) return URL_ERR_OVERFLOW;
                out[olen++] = in[k];
            }
            in += seg;
        }
    }

    if (olen + 1 > outsz) return URL_ERR_OVERFLOW;
    out[olen] = '\0';
    return URL_OK;
}

/* --- public: reference resolution --- */

/* Length of base up to and including the last path '/', ignoring query/fragment.
 * If the path carries no slash, returns the authority length. */
static size_t dir_len(const char *base) {
    size_t auth = url_authority_len(base);
    size_t last = auth;
    int found = 0;
    for (size_t i = auth; base[i] != '\0'; ++i) {
        if (base[i] == '?' || base[i] == '#') break;
        if (base[i] == '/') { last = i; found = 1; }
    }
    return found ? last + 1 : auth;
}

url_status url_resolve_https(const char *base, const char *ref,
                             char *out, size_t outsz) {
    if (base == NULL || ref == NULL || out == NULL || outsz == 0)
        return URL_ERR_NULL_ARG;
    if (url_validate_https(base) != URL_OK) return URL_ERR_NOT_HTTPS; /* fail closed */
    if (ref[0] == '\0') return URL_ERR_NOT_HTTPS;

    if (ci_prefix(ref, "https://")) {
        if (copy_checked(out, outsz, ref) != 0) return URL_ERR_OVERFLOW;
    } else if (ci_prefix(ref, "http://")) {
        return URL_ERR_NOT_HTTPS; /* refuse cleartext downgrade */
    } else if (ref[0] == '/' && ref[1] == '/') {
        /* scheme-relative: //host/path => https://host/path */
        if (copy_checked(out, outsz, "https:") != 0) return URL_ERR_OVERFLOW;
        if (cat_checked(out, outsz, ref) != 0) return URL_ERR_OVERFLOW;
    } else if (url_has_scheme(ref)) {
        return URL_ERR_NOT_HTTPS; /* javascript:, data:, mailto:, ftp:, file:, ... */
    } else {
        size_t auth = url_authority_len(base);
        if (auth <= 8) return URL_ERR_NOT_HTTPS; /* empty host */

        char merged[URL_MAX_LEN + 1];
        merged[0] = '\0';
        if (ref[0] == '/') {
            if (copy_checked(merged, sizeof merged, ref) != 0) return URL_ERR_OVERFLOW;
        } else {
            size_t dir = dir_len(base);
            if (ncat_checked(merged, sizeof merged, base + auth, dir - auth) != 0)
                return URL_ERR_OVERFLOW;
            if (dir == auth && cat_checked(merged, sizeof merged, "/") != 0)
                return URL_ERR_OVERFLOW;
            if (cat_checked(merged, sizeof merged, ref) != 0) return URL_ERR_OVERFLOW;
        }

        char norm[URL_MAX_LEN + 1];
        url_status ns = url_remove_dot_segments(merged, norm, sizeof norm);
        if (ns != URL_OK) return ns;

        out[0] = '\0';
        if (ncat_checked(out, outsz, base, auth) != 0) return URL_ERR_OVERFLOW;
        if (cat_checked(out, outsz, norm) != 0) return URL_ERR_OVERFLOW;
    }

    return url_validate_https(out);
}
