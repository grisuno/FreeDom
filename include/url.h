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
    URL_ERR_OVERFLOW,   /* the result did not fit in the caller buffer */
    URL_ERR_NOT_LOCAL   /* not a valid local file:// reference, or it escapes the base dir */
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

/* --- omnibox: classify free-form URL-bar input --- */

/* The no-JS DuckDuckGo HTML endpoint (the percent-encoded query is appended). It
 * works without scripting, which is why it is the default search target. */
#define URL_SEARCH_ENDPOINT "https://html.duckduckgo.com/html/?q="

typedef enum url_omni_kind {
    URL_OMNI_NAVIGATE = 0, /* out holds an absolute https URL to load */
    URL_OMNI_SEARCH        /* out holds the https DuckDuckGo HTML search URL */
} url_omni_kind;

/* Resolves free-form URL-bar text into an absolute https URL, deciding whether it
 * names a site to navigate or a query to search. Pure, fail-closed and Secure by
 * Default:
 *   - input that already is an absolute https URL  -> NAVIGATE (copied verbatim);
 *   - a bare host shape ("example.com", "host:8443/p", "localhost") -> NAVIGATE,
 *     prefixed with "https://";
 *   - an "http://" prefix -> NAVIGATE, UPGRADED to https (HTTPS-only; never a
 *     downgrade, and the secure scheme is the only representable one);
 *   - anything else -- whitespace, a non-http(s) scheme (so "javascript:..." is
 *     searched for, never executed), or a non-host token -> SEARCH.
 * Does NOT handle local files: the orchestrator must resolve an existing local
 * path before calling this (a pure function cannot stat the filesystem).
 * out is NUL-terminated on URL_OK. NULL args / outsz == 0 => URL_ERR_NULL_ARG;
 * a built URL that does not fit => URL_ERR_OVERFLOW. */
url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz);

/* --- local file:// origin (for local pages, "acting like https") --- */

/* Nonzero iff s begins (case-insensitively) with "file://" followed by an
 * absolute path ("file:///..."). NULL => 0. */
int url_is_file(const char *s);

/* Returns the absolute filesystem path inside a "file:///path" URL (i.e. the
 * "/path" part), or NULL when s is not a valid file:// URL. The pointer aliases s
 * (not owned). */
const char *url_file_path(const char *s);

/* --- WHATWG-location decomposition (for a page's JS `location.*`) --- */

/* Components of a validated absolute https URL, sliced for a JS location object.
 * Every field ALIASES the input url (not owned, valid while url is alive); lengths
 * exclude any NUL. Absent components have length 0. pathname is the literal path
 * span and is empty when the URL has no path (the location shim presents "" as "/"). */
typedef struct url_parts {
    const char *href;     size_t href_len;     /* the whole URL */
    const char *protocol; size_t protocol_len; /* "https:" */
    const char *origin;   size_t origin_len;   /* "https://host[:port]" */
    const char *host;     size_t host_len;     /* "host[:port]" */
    const char *hostname; size_t hostname_len; /* "host" (brackets kept for IPv6) */
    const char *port;     size_t port_len;     /* "" or decimal digits */
    const char *pathname; size_t pathname_len; /* "/..." or "" */
    const char *search;   size_t search_len;   /* "?..." or "" */
    const char *hash;     size_t hash_len;     /* "#..." or "" */
} url_parts;

/* Decomposes a validated absolute https URL into WHATWG-location components, each
 * field aliasing url (zero-copy). Reuses url_authority_len / url_validate_https.
 * Fail-closed and https-only (the read side of `location`; the navigate decision
 * belongs to link_nav): url == NULL / out == NULL => URL_ERR_NULL_ARG; a URL that
 * is not a valid absolute https URL => URL_ERR_NOT_HTTPS. On URL_OK every field
 * points into url. */
url_status url_split(const char *url, url_parts *out);

/* Resolves a (relative or absolute) reference ref against a "file:///dir/page"
 * base into out as a canonical "file:///..." URL. Security-critical and
 * fail-closed: the result is CONFINED to base's own directory subtree — a "../"
 * escape, an absolute path outside it, a scheme-relative ("//..") or any non-file
 * scheme (so a remote https or foreign-scheme src on a local page) yields
 * URL_ERR_NOT_LOCAL. So a hostile local document cannot auto-load /etc/passwd nor
 * phone home through an image. base must be a valid file:// URL (else
 * URL_ERR_NOT_LOCAL). Dot segments are collapsed before the confinement check.
 * NULL args / outsz == 0 => URL_ERR_NULL_ARG; overflow => URL_ERR_OVERFLOW. */
url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz);

#endif /* FREEDOM_URL_H */
