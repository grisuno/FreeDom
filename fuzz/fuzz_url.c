/*
 * libFuzzer harness for url_split (the read side of a page's JS `location.*`) and
 * the JS-navigation gate (link_nav's ln_resolve, fed the same hostile bytes).
 *
 * The page URL and any JS-requested navigation target are semi-trusted/hostile
 * input (redirects, user typing, a possibly compromised worker). url_split must
 * never crash, leak or read out of bounds, and every component span it returns on
 * URL_OK must alias the input within bounds. ln_resolve must never produce a
 * non-https / non-local target. The invariants below abort here on a containment
 * bug, not only on a memory bug.
 *
 * The input is split on '\n' into base \n ref so the fuzzer drives both independently.
 *
 * Build & run: make fuzz-url   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "link_nav.h"
#include "url.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* p[0..len) must lie within base[0..total]. */
static void in_bounds(const char *p, size_t len, const char *base, size_t total) {
    if (p < base || p > base + total) abort();
    if (len > (size_t)((base + total) - p)) abort();
}

static void check_split(const char *url) {
    url_parts u;
    if (url_split(url, &u) != URL_OK) return;
    size_t total = strlen(url);

    if (u.href != url || u.href_len != total) abort();
    if (u.protocol_len != 6) abort();

    in_bounds(u.protocol, u.protocol_len, url, total);
    in_bounds(u.origin,   u.origin_len,   url, total);
    in_bounds(u.host,     u.host_len,     url, total);
    in_bounds(u.hostname, u.hostname_len, url, total);
    in_bounds(u.port,     u.port_len,     url, total);
    in_bounds(u.pathname, u.pathname_len, url, total);
    in_bounds(u.search,   u.search_len,   url, total);
    in_bounds(u.hash,     u.hash_len,     url, total);

    /* host = origin without "https://"; hostname is a prefix of host. */
    if (u.host != url + 8 || u.host_len + 8 != u.origin_len) abort();
    if (u.hostname != u.host || u.hostname_len > u.host_len) abort();

    /* pathname/search/hash partition the remainder after the authority, in order. */
    if (u.pathname != url + u.origin_len) abort();
    if (u.search != u.pathname + u.pathname_len) abort();
    if (u.hash != u.search + u.search_len) abort();
    if (u.origin_len + u.pathname_len + u.search_len + u.hash_len != total) abort();
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    char *buf = (char *)malloc(size + 1);
    if (buf == NULL) return 0;
    memcpy(buf, data, size);
    buf[size] = '\0';

    char *base = buf;
    char *ref = strchr(base, '\n');
    if (ref != NULL) { *ref = '\0'; ++ref; }

    check_split(base);
    if (ref != NULL) check_split(ref);

    (void)url_validate_https(base);

    /* The JS-navigation gate: ln_resolve(page_url, raw_request). A NAVIGATE result
     * must be an https URL or a local file path -- never a downgrade/foreign scheme. */
    if (ref != NULL) {
        ln_result r;
        if (ln_resolve(base, ref, &r) == LN_OK && r.action == LN_NAVIGATE) {
            if (r.kind == LN_TARGET_HTTPS) {
                if (!url_is_https(r.target)) abort(); /* never a downgrade/foreign scheme */
            } else if (r.kind == LN_TARGET_FILE) {
                /* A local file path (absolute when the base is a real file URL; a fuzzer
                 * may pass a degenerate base). Always a concrete, non-empty target. */
                if (r.target[0] == '\0') abort();
            } else {
                abort(); /* NAVIGATE must carry a concrete target kind */
            }
        }
    }

    free(buf);
    return 0;
}
