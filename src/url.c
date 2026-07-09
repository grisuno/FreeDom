/*
 * url — implementation: pure URL validation and reference resolution.
 *
 * No I/O, no global state, no TLS stack. RFC 3986 relative resolution with
 * dot-segment canonicalisation. Fails closed: a non-https result is never
 * produced; every assembly is bounded and reports overflow rather than truncate.
 */

#define _POSIX_C_SOURCE 200809L

#include "url.h"

#include <stdlib.h>
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
    /* Fail closed past the hard cap: a URL longer than URL_MAX_LEN is not a URL
     * the browser will act on (it would not fit the fixed buffers downstream).
     * Bounded scan (pure C11; no strnlen feature-test macro dependency). */
    size_t i = 0;
    while (i <= URL_MAX_LEN && url[i] != '\0') ++i;
    if (i > URL_MAX_LEN) return URL_ERR_NOT_HTTPS;
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

/* --- omnibox --- */

static int is_space(int c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

static int is_unreserved(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
           (c >= '0' && c <= '9') || c == '-' || c == '.' || c == '_' || c == '~';
}

/* Percent-encodes src into a query value appended to out (space -> '+', every
 * non-unreserved byte -> %XX). Nonzero on overflow. */
static int append_query_encoded(char *out, size_t outsz, const char *src) {
    static const char hex[] = "0123456789ABCDEF";
    size_t cur = strlen(out);
    for (const char *p = src; *p != '\0'; ++p) {
        unsigned char c = (unsigned char)*p;
        if (c == ' ') {
            if (cur + 1 + 1 > outsz) return -1;
            out[cur++] = '+';
        } else if (is_unreserved(c)) {
            if (cur + 1 + 1 > outsz) return -1;
            out[cur++] = (char)c;
        } else {
            if (cur + 3 + 1 > outsz) return -1;
            out[cur++] = '%';
            out[cur++] = hex[(c >> 4) & 0xF];
            out[cur++] = hex[c & 0xF];
        }
    }
    out[cur] = '\0';
    return 0;
}

/* Does the authority of s (up to the first '/', '?' or '#', minus any ":port")
 * look like a registrable host: "localhost", or labels of [A-Za-z0-9-] joined by
 * dots with a final all-alphabetic label of length >= 2 (a TLD)? No whitespace is
 * assumed (the caller already routed whitespace to search). */
static int looks_like_host(const char *s) {
    size_t authlen = 0;
    while (s[authlen] != '\0' && s[authlen] != '/' &&
           s[authlen] != '?' && s[authlen] != '#') {
        ++authlen;
    }
    /* Drop a ":port" suffix from the authority. */
    size_t hostlen = authlen;
    for (size_t i = 0; i < authlen; ++i) {
        if (s[i] == ':') { hostlen = i; break; }
    }
    if (hostlen == 0) return 0;

    if (hostlen == 9 && ci_prefix(s, "localhost") && (s[9] == '\0' || s[9] == ':' ||
        s[9] == '/' || s[9] == '?' || s[9] == '#')) {
        return 1;
    }

    int dots = 0;
    size_t label_start = 0;
    size_t last_label_start = 0;
    for (size_t i = 0; i <= hostlen; ++i) {
        char c = (i < hostlen) ? s[i] : '.'; /* virtual trailing '.' closes the last label */
        if (c == '.') {
            size_t label_len = i - label_start;
            if (label_len == 0) return 0;                 /* empty label ("a..b", ".a") */
            if (s[label_start] == '-' || s[i - 1] == '-') return 0; /* hyphen at edge */
            if (i < hostlen) ++dots;
            last_label_start = label_start;
            label_start = i + 1;
        } else {
            int ok = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
                     (c >= '0' && c <= '9') || c == '-';
            if (!ok) return 0;
        }
    }
    if (dots < 1) return 0;

    /* The final label (the TLD) must be all-alphabetic and at least 2 chars. */
    size_t tld_len = hostlen - last_label_start;
    if (tld_len < 2) return 0;
    for (size_t i = last_label_start; i < hostlen; ++i) {
        char c = s[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0;
    }
    return 1;
}

static url_status build_search(const char *query, char *out, size_t outsz) {
    if (copy_checked(out, outsz, URL_SEARCH_ENDPOINT) != 0) return URL_ERR_OVERFLOW;
    if (append_query_encoded(out, outsz, query) != 0) return URL_ERR_OVERFLOW;
    return URL_OK;
}

url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz) {
    if (input == NULL || kind == NULL || out == NULL || outsz == 0)
        return URL_ERR_NULL_ARG;

    /* Trim surrounding whitespace; the original (untrimmed) input still feeds a
     * search query so a copy-pasted "  foo bar  " searches for "foo bar". */
    const char *start = input;
    while (*start != '\0' && is_space((unsigned char)*start)) ++start;
    const char *end = start + strlen(start);
    while (end > start && is_space((unsigned char)end[-1])) --end;
    size_t trimlen = (size_t)(end - start);

    if (trimlen == 0) { *kind = URL_OMNI_SEARCH; return build_search("", out, outsz); }

    /* Internal whitespace can never be a URL: it is a query. */
    for (size_t i = 0; i < trimlen; ++i) {
        if (is_space((unsigned char)start[i])) {
            *kind = URL_OMNI_SEARCH;
            return build_search(start, out, outsz);
        }
    }

    /* The trimmed token has no whitespace; copy it NUL-terminated for the scheme
     * checks and host build (bounded by URL_MAX_LEN like every URL we act on). */
    char tok[URL_MAX_LEN + 1];
    if (trimlen + 1 > sizeof tok) { *kind = URL_OMNI_SEARCH; return build_search(start, out, outsz); }
    memcpy(tok, start, trimlen);
    tok[trimlen] = '\0';

    if (ci_prefix(tok, "https://")) {
        if (url_validate_https(tok) != URL_OK) { *kind = URL_OMNI_SEARCH; return build_search(start, out, outsz); }
        *kind = URL_OMNI_NAVIGATE;
        return copy_checked(out, outsz, tok) != 0 ? URL_ERR_OVERFLOW : URL_OK;
    }

    if (ci_prefix(tok, "http://")) {
        /* HTTPS-only upgrade: rebuild as https and validate. */
        char up[URL_MAX_LEN + 1];
        up[0] = '\0';
        if (cat_checked(up, sizeof up, "https://") != 0 ||
            cat_checked(up, sizeof up, tok + 7) != 0 ||
            url_validate_https(up) != URL_OK) {
            *kind = URL_OMNI_SEARCH;
            return build_search(start, out, outsz);
        }
        *kind = URL_OMNI_NAVIGATE;
        return copy_checked(out, outsz, up) != 0 ? URL_ERR_OVERFLOW : URL_OK;
    }

    /* A host shape is checked BEFORE the generic scheme guard: "host:port" (e.g.
     * "localhost:8443") syntactically parses as "<scheme>:" but is really a host. */
    if (looks_like_host(tok)) {
        char built[URL_MAX_LEN + 1];
        built[0] = '\0';
        if (cat_checked(built, sizeof built, "https://") == 0 &&
            cat_checked(built, sizeof built, tok) == 0 &&
            url_validate_https(built) == URL_OK) {
            *kind = URL_OMNI_NAVIGATE;
            return copy_checked(out, outsz, built) != 0 ? URL_ERR_OVERFLOW : URL_OK;
        }
    }

    /* Any remaining explicit scheme is never executed nor downgraded: search for it
     * (so "javascript:...", "file:...", "ftp://..." become harmless queries). */
    *kind = URL_OMNI_SEARCH;
    return build_search(start, out, outsz);
}

/* --- HTTP Basic Auth: extract userinfo from URL --- */

url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                                char **username_out, char **password_out) {
    if (url == NULL || out == NULL || outsz == 0) return URL_ERR_NULL_ARG;
    if (!url_is_https(url)) {
        if (copy_checked(out, outsz, url) != 0) return URL_ERR_OVERFLOW;
        if (username_out != NULL) *username_out = NULL;
        if (password_out != NULL) *password_out = NULL;
        return URL_OK; /* not an error: no auth expected for non-https */
    }

    /* Scan the authority part for '@'. Authority = bytes after "https://" up to
     * the first '/', '?' or '#'. */
    const char *auth = url + 8; /* strlen("https://") */
    const char *at = NULL;
    for (const char *p = auth; *p != '\0' && *p != '/' && *p != '?' && *p != '#'; ++p) {
        if (*p == '@') { at = p; break; }
    }

    if (at == NULL) {
        /* No userinfo: pass through the original URL. */
        if (copy_checked(out, outsz, url) != 0) return URL_ERR_OVERFLOW;
        if (username_out != NULL) *username_out = NULL;
        if (password_out != NULL) *password_out = NULL;
        return URL_OK;
    }

    /* There IS userinfo. The "user:password" part is between the scheme and '@'. */
    size_t userinfo_len = (size_t)(at - auth);
    if (userinfo_len == 0) {
        if (copy_checked(out, outsz, url) != 0) return URL_ERR_OVERFLOW;
        if (username_out != NULL) *username_out = NULL;
        if (password_out != NULL) *password_out = NULL;
        return URL_OK; /* "@" at the start of authority: not valid userinfo */
    }

    /* Split userinfo on the first ':' (if any) -> username and password. */
    const char *colon = NULL;
    for (size_t i = 0; i < userinfo_len; ++i) {
        if (auth[i] == ':') { colon = auth + i; break; }
    }

    size_t user_len = (colon != NULL) ? (size_t)(colon - auth) : userinfo_len;
    size_t pass_len = (colon != NULL) ? userinfo_len - user_len - 1 : 0;

    char username[256];
    if (user_len > sizeof username - 1) {
        if (copy_checked(out, outsz, url) != 0) return URL_ERR_OVERFLOW;
        if (username_out != NULL) *username_out = NULL;
        if (password_out != NULL) *password_out = NULL;
        return URL_OK; /* userinfo too long: skip auth, use URL as-is */
    }
    memcpy(username, auth, user_len);
    username[user_len] = '\0';

    char password[256];
    if (pass_len >= sizeof password) {
        if (copy_checked(out, outsz, url) != 0) return URL_ERR_OVERFLOW;
        if (username_out != NULL) *username_out = NULL;
        if (password_out != NULL) *password_out = NULL;
        return URL_OK;
    }
    if (pass_len > 0) {
        memcpy(password, colon + 1, pass_len);
        password[pass_len] = '\0';
    } else {
        password[0] = '\0';
    }

    /* Build the cleaned URL: "https://" + host_part (everything after the '@'). */
    const char *remain = at + 1; /* points to the host (after '@') */
    char cleaned[URL_MAX_LEN + 1];
    cleaned[0] = '\0';
    if (cat_checked(cleaned, sizeof cleaned, "https://") != 0 ||
        cat_checked(cleaned, sizeof cleaned, remain) != 0) {
        return URL_ERR_OVERFLOW;
    }
    if (copy_checked(out, outsz, cleaned) != 0) return URL_ERR_OVERFLOW;

    if (username_out != NULL) {
        *username_out = strdup(username);
        if (*username_out == NULL) return URL_ERR_NULL_ARG;
    }
    if (password_out != NULL) {
        *password_out = (pass_len > 0) ? strdup(password) : strdup("");
        if (*password_out == NULL) {
            if (username_out != NULL) { free(*username_out); *username_out = NULL; }
            return URL_ERR_NULL_ARG;
        }
    }
    return URL_OK;
}

/* --- local file:// origin --- */

int url_is_file(const char *s) {
    if (s == NULL) return 0;
    if (!ci_prefix(s, "file://")) return 0;
    return s[7] == '/'; /* file:/// => absolute path follows */
}

const char *url_file_path(const char *s) {
    return url_is_file(s) ? s + 7 : NULL; /* the leading '/' of the absolute path */
}

url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz) {
    if (base == NULL || ref == NULL || out == NULL || outsz == 0)
        return URL_ERR_NULL_ARG;
    if (!url_is_file(base)) return URL_ERR_NOT_LOCAL;

    const char *base_path = base + 7; /* absolute, starts with '/' */
    /* Base directory = up to and including the last '/'. base_path is absolute, so
     * there is always at least the root '/'. */
    size_t dir_end = 0;
    for (size_t i = 0; base_path[i] != '\0'; ++i)
        if (base_path[i] == '/') dir_end = i + 1;
    if (dir_end == 0) return URL_ERR_NOT_LOCAL; /* defensive: not absolute */

    /* Pick the candidate absolute path to canonicalize. */
    char merged[URL_MAX_LEN + 1];
    if (url_has_scheme(ref)) {
        /* Only a file:// reference is local; a remote/foreign scheme on a local
         * page is rejected (no phone-home, no foreign scheme). */
        if (!url_is_file(ref)) return URL_ERR_NOT_LOCAL;
        if (copy_checked(merged, sizeof merged, ref + 7) != 0) return URL_ERR_OVERFLOW;
    } else if (ref[0] == '/' && ref[1] == '/') {
        return URL_ERR_NOT_LOCAL; /* scheme-relative: no local meaning */
    } else if (ref[0] == '/') {
        if (copy_checked(merged, sizeof merged, ref) != 0) return URL_ERR_OVERFLOW;
    } else if (ref[0] == '\0') {
        return URL_ERR_NOT_LOCAL; /* empty reference */
    } else {
        merged[0] = '\0';
        if (ncat_checked(merged, sizeof merged, base_path, dir_end) != 0) return URL_ERR_OVERFLOW;
        if (cat_checked(merged, sizeof merged, ref) != 0) return URL_ERR_OVERFLOW;
    }

    char canon[URL_MAX_LEN + 1];
    url_status ns = url_remove_dot_segments(merged, canon, sizeof canon);
    if (ns != URL_OK) return ns;

    /* Confinement: the canonical path must stay inside the base directory subtree.
     * base directory text = base_path[0..dir_end) (ends with '/'), so a strict
     * prefix match rejects "../" escapes and absolute paths elsewhere. */
    if (strncmp(canon, base_path, dir_end) != 0) return URL_ERR_NOT_LOCAL;

    out[0] = '\0';
    if (cat_checked(out, outsz, "file://") != 0) return URL_ERR_OVERFLOW;
    if (cat_checked(out, outsz, canon) != 0) return URL_ERR_OVERFLOW;
    return URL_OK;
}

/* --- WHATWG-location decomposition (zero-copy; reads side of `location`) --- */

url_status url_split(const char *url, url_parts *out) {
    if (url == NULL || out == NULL) return URL_ERR_NULL_ARG;
    if (!url_is_https(url)) return URL_ERR_NOT_HTTPS; /* https-only, fail closed */

    memset(out, 0, sizeof *out);
    size_t total = strlen(url);
    out->href = url;     out->href_len = total;
    out->protocol = url; out->protocol_len = 6; /* "https:" */

    /* origin = "https://host[:port]"; host = origin without the "https://" prefix.
     * url_is_https guarantees the host is non-empty. */
    size_t auth = url_authority_len(url); /* first '/' after scheme, or total */
    out->origin = url;     out->origin_len = auth;
    const char *host = url + 8;            /* strlen("https://") */
    size_t host_len = auth - 8;
    out->host = host;      out->host_len = host_len;

    /* hostname / port. An IPv6 literal "[..]" keeps its brackets in hostname; the
     * port (if any) follows "]:". Otherwise the first ':' splits host:port. */
    size_t hn = host_len;
    const char *port = host + host_len;
    size_t port_len = 0;
    if (host_len > 0 && host[0] == '[') {
        size_t k = 0;
        while (k < host_len && host[k] != ']') ++k;
        if (k < host_len) {       /* found the closing bracket */
            hn = k + 1;           /* include ']' in hostname */
            if (hn < host_len && host[hn] == ':') {
                port = host + hn + 1;
                port_len = host_len - (hn + 1);
            }
        }
    } else {
        for (size_t k = 0; k < host_len; ++k) {
            if (host[k] == ':') {
                hn = k;
                port = host + k + 1;
                port_len = host_len - (k + 1);
                break;
            }
        }
    }
    out->hostname = host; out->hostname_len = hn;
    out->port = port;     out->port_len = port_len;

    /* pathname / search / hash from the remainder after the authority. Each is a
     * span: search includes the leading '?', hash includes the leading '#', and
     * pathname may be empty (no path) — the consumer presents that as "/". */
    const char *rem = url + auth;
    size_t rem_len = total - auth;
    size_t hpos = rem_len;
    for (size_t k = 0; k < rem_len; ++k) { if (rem[k] == '#') { hpos = k; break; } }
    size_t qpos = hpos;
    for (size_t k = 0; k < hpos; ++k) { if (rem[k] == '?') { qpos = k; break; } }

    out->pathname = rem;        out->pathname_len = qpos;
    out->search   = rem + qpos; out->search_len   = hpos - qpos;
    out->hash     = rem + hpos; out->hash_len     = rem_len - hpos;
    return URL_OK;
}
