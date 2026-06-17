#ifndef FREEDOM_URL_H
#define FREEDOM_URL_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * url — pure URL operations: validation and reference resolution.
 *
 * No I/O, no global state, no TLS stack. This is the canonical, directly
 * auditable knowledge of "what is a valid absolute https URL" and "how a
 * reference resolves against a base URL", shared by secure_fetch (HTTP redirects)
 * and link_nav (clicked hyperlinks) so the rule lives in exactly one tested place.
 *
 * Secure by Default: a non-https URL is not a representable result of
 * url_resolve_https; an http:// downgrade and every other explicit scheme are
 * rejected. Fails closed: any doubt rejects rather than degrades.
 *
 * See spec/url.md for the full contract.
 */

/* Hard cap for any single URL the browser will act on. */
#define URL_MAX_LEN 2048u

typedef enum url_status {
    URL_OK = 0,
    URL_ERR_NULL_ARG,   /* a required pointer was NULL, or outsz == 0 */
    URL_ERR_NOT_HTTPS,  /* not an absolute https URL / rejected scheme / empty host */
    URL_ERR_OVERFLOW    /* the result did not fit in the caller buffer */
} url_status;

/* Nonzero iff s begins (case-insensitively) with "https://" and the host is
 * neither empty nor a leading '/'. NULL => 0. */
int url_is_https(const char *s);

/* Nonzero iff s begins with "<scheme>:" per RFC 3986
 * (ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":"). NULL => 0. */
int url_has_scheme(const char *s);

/* Length of "https://host[:port]" within a validated absolute https URL: the
 * index of the first '/' after the scheme, or the whole length if there is no
 * path. Assumes url passed url_validate_https. */
size_t url_authority_len(const char *url);

/* URL_OK only for a syntactically valid absolute https URL with a non-empty host.
 * url == NULL => URL_ERR_NULL_ARG; otherwise URL_ERR_NOT_HTTPS. */
url_status url_validate_https(const char *url);

/* RFC 3986 section 5.2.4 dot-segment removal on a path component: collapses "."
 * and ".." segments. Preserves a leading '/' (absolute path) and a trailing '/'.
 * NULL path/out or outsz == 0 => URL_ERR_NULL_ARG; overflow => URL_ERR_OVERFLOW. */
url_status url_remove_dot_segments(const char *path, char *out, size_t outsz);

/* Resolves reference ref against base into out (NUL-terminated), always yielding
 * an absolute https URL or failing closed. base must be a valid absolute https URL
 * (else URL_ERR_NOT_HTTPS, fail closed). Handles absolute https, scheme-relative
 * ("//host/..."), absolute-path ("/...") and relative-path references; the result
 * path is canonicalised with url_remove_dot_segments. Rejects http:// downgrade and
 * every other explicit scheme. The result is validated with url_validate_https
 * before return. NULL args / outsz == 0 => URL_ERR_NULL_ARG; overflow =>
 * URL_ERR_OVERFLOW. */
url_status url_resolve_https(const char *base, const char *ref, char *out, size_t outsz);

#endif /* FREEDOM_URL_H */
