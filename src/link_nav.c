/*
 * link_nav — implementation: pure navigation policy for a clicked hyperlink.
 *
 * No I/O, no global state. The href is hostile data with provenance: it is
 * cleaned (tab/newline/CR removed, whitespace trimmed), classified, and resolved
 * against the page location, failing closed to LN_BLOCKED on anything not
 * provably safe to navigate. https resolution reuses the pure url module; local
 * file paths use a relativeness-preserving segment normaliser (so "../x" against
 * a relative base stays relative and never silently becomes an absolute path).
 */

#include "link_nav.h"
#include "url.h"

#include <string.h>

/* Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place
 * into out. Returns 0, or -1 if the href does not fit in out. */
static int clean_href(const char *href, char *out, size_t outsz) {
    size_t o = 0;
    for (size_t i = 0; href[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)href[i];
        if (c == '\t' || c == '\n' || c == '\r') continue;
        if (o + 1 >= outsz) return -1;
        out[o++] = (char)c;
    }
    out[o] = '\0';

    size_t start = 0;
    while (out[start] == ' ') ++start;
    if (start > 0) memmove(out, out + start, strlen(out + start) + 1);
    size_t len = strlen(out);
    while (len > 0 && out[len - 1] == ' ') out[--len] = '\0';
    return 0;
}

/* Length of base up to and including the last '/'; 0 when base has no '/'. */
static size_t file_dir_len(const char *base) {
    size_t last = 0;
    int found = 0;
    for (size_t i = 0; base[i] != '\0'; ++i) {
        if (base[i] == '/') { last = i; found = 1; }
    }
    return found ? last + 1 : 0;
}

/* Nonzero iff the last segment of body[0..blen) is exactly "..". */
static int last_seg_is_dotdot(const char *body, size_t blen) {
    size_t s = blen;
    while (s > 0 && body[s - 1] != '/') --s;
    return (blen - s == 2 && body[s] == '.' && body[s + 1] == '.');
}

/* Appends seg to body (with a '/' separator when non-empty). 0, or -1 on overflow. */
static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *seg, size_t seglen) {
    size_t need = (*blen > 0 ? 1u : 0u) + seglen;
    if (*blen + need + 1 > bodysz) return -1;
    if (*blen > 0) body[(*blen)++] = '/';
    memcpy(body + *blen, seg, seglen);
    *blen += seglen;
    body[*blen] = '\0';
    return 0;
}

/* Drops the last segment (and its preceding '/') from body. */
static void pop_seg(char *body, size_t *blen) {
    size_t n = *blen;
    while (n > 0 && body[n - 1] != '/') --n;
    if (n > 0) --n;
    *blen = n;
    body[n] = '\0';
}

/* Normalises a filesystem path: collapses "." and "..", preserving whether the
 * path is absolute (a ".." cannot climb above root) or relative (".." beyond the
 * start stays as ".."). Returns 0, or -1 on overflow or an empty result. */
static int normalize_file_path(const char *path, char *out, size_t outsz) {
    int absolute = (path[0] == '/');
    char body[LN_MAX_TARGET];
    size_t blen = 0;
    body[0] = '\0';

    size_t i = 0;
    while (path[i] != '\0') {
        if (path[i] == '/') { ++i; continue; }
        size_t s = i;
        while (path[i] != '\0' && path[i] != '/') ++i;
        size_t seglen = i - s;

        if (seglen == 1 && path[s] == '.') {
            continue;
        }
        if (seglen == 2 && path[s] == '.' && path[s + 1] == '.') {
            if (blen > 0 && !last_seg_is_dotdot(body, blen)) {
                pop_seg(body, &blen);
            } else if (!absolute) {
                if (append_seg(body, sizeof body, &blen, "..", 2) != 0) return -1;
            }
            continue;
        }
        if (append_seg(body, sizeof body, &blen, path + s, seglen) != 0) return -1;
    }

    size_t need = (absolute ? 1u : 0u) + blen;
    if (need + 1 > outsz) return -1;
    if (need == 0) return -1; /* empty result is not a navigable target */

    size_t o = 0;
    if (absolute) out[o++] = '/';
    memcpy(out + o, body, blen);
    out[o + blen] = '\0';
    return 0;
}

/* Resolves a local file reference (relative or absolute path) against base into
 * out. The fragment (#...) is dropped. Returns 0, or -1 on overflow/empty. */
static int resolve_file(const char *base, const char *ref, char *out, size_t outsz) {
    char r[LN_MAX_TARGET];
    size_t i = 0;
    for (; ref[i] != '\0' && ref[i] != '#'; ++i) {
        if (i + 1 >= sizeof r) return -1;
        r[i] = ref[i];
    }
    r[i] = '\0';
    if (r[0] == '\0') return -1;

    char merged[LN_MAX_TARGET];
    if (r[0] == '/') {
        if (strlen(r) + 1 > sizeof merged) return -1;
        memcpy(merged, r, strlen(r) + 1);
    } else {
        size_t dl = file_dir_len(base);
        if (dl + strlen(r) + 1 > sizeof merged) return -1;
        memcpy(merged, base, dl);
        memcpy(merged + dl, r, strlen(r) + 1);
    }
    return normalize_file_path(merged, out, outsz);
}

ln_status ln_resolve(const char *base, const char *href, ln_result *out) {
    if (out == NULL) return LN_ERR_NULL_ARG;
    out->action = LN_BLOCKED;
    out->kind = LN_TARGET_NONE;
    out->target[0] = '\0';

    if (href == NULL) return LN_OK;

    char clean[LN_MAX_TARGET];
    if (clean_href(href, clean, sizeof clean) != 0) return LN_OK; /* overflow: blocked */

    if (clean[0] == '\0' || clean[0] == '#') {
        out->action = LN_SAME_DOCUMENT;
        return LN_OK;
    }

    /* An https page resolves every reference (relative, absolute-path,
     * scheme-relative, absolute) through the url module, which already rejects
     * the http downgrade and every foreign scheme. */
    if (base != NULL && url_is_https(base)) {
        if (url_resolve_https(base, clean, out->target, sizeof out->target) == URL_OK) {
            out->action = LN_NAVIGATE;
            out->kind = LN_TARGET_HTTPS;
        } else {
            out->target[0] = '\0';
        }
        return LN_OK;
    }

    /* Non-https base (local file or none): only an explicit https URL or, under a
     * local base, a local path is navigable. */
    if (url_has_scheme(clean)) {
        if (url_is_https(clean) && strlen(clean) + 1 <= sizeof out->target) {
            memcpy(out->target, clean, strlen(clean) + 1);
            out->action = LN_NAVIGATE;
            out->kind = LN_TARGET_HTTPS;
        }
        return LN_OK;
    }

    if (clean[0] == '/' && clean[1] == '/') return LN_OK; /* scheme-relative: no origin */

    if (base == NULL) return LN_OK; /* no base to resolve a path against */

    if (resolve_file(base, clean, out->target, sizeof out->target) == 0) {
        out->action = LN_NAVIGATE;
        out->kind = LN_TARGET_FILE;
    } else {
        out->target[0] = '\0';
    }
    return LN_OK;
}
