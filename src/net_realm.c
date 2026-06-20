/*
 * net_realm — implementation: pure realm classification and routing.
 *
 * No I/O, no global state, no allocation. Classification is a case-insensitive
 * final-label suffix test (".onion" / ".i2p"); routing is a small fail-closed table
 * over the enabled proxies. The two anonymity invariants (realm isolation and
 * fail-closed) are enforced structurally here so they can be tested without a network.
 */

#include "net_realm.h"

#include <stddef.h>
#include <string.h>

#define NR_MAX_HOST 253u

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c;
}

/* True if the lowercased host (length n) ends with ".suffix" AND has at least one
 * non-empty label before the dot. suffix is given without its leading dot. */
static int ends_with_realm(const char *host, size_t n, const char *suffix) {
    size_t sl = strlen(suffix);
    if (n < sl + 2) return 0;            /* need at least "x." + suffix */
    if (host[n - sl - 1] != '.') return 0;
    for (size_t i = 0; i < sl; ++i) {
        if (host[n - sl + i] != suffix[i]) return 0;  /* host already lowercased */
    }
    /* The label before the dot must be non-empty (reject ".onion"). */
    return (n - sl - 1) > 0;
}

nr_realm nr_classify_host(const char *host) {
    if (host == NULL) return NR_CLEARNET;
    size_t len = strlen(host);
    if (len == 0 || len > NR_MAX_HOST) return NR_CLEARNET;

    char buf[NR_MAX_HOST + 1];
    for (size_t i = 0; i < len; ++i) buf[i] = lower(host[i]);
    buf[len] = '\0';
    if (buf[len - 1] == '.') { --len; buf[len] = '\0'; }  /* trim one trailing dot */
    if (len == 0) return NR_CLEARNET;

    if (ends_with_realm(buf, len, "onion")) return NR_ONION;
    if (ends_with_realm(buf, len, "i2p")) return NR_I2P;
    return NR_CLEARNET;
}

/* Extracts the host of scheme://host[:port][/...] into out (lowercased not required
 * here; nr_classify_host lowercases). Returns 0 on success, -1 if no host. */
static int host_of(const char *url, char *out, size_t out_size) {
    if (url == NULL || out == NULL || out_size == 0) return -1;
    const char *p = strstr(url, "://");
    if (p == NULL) return -1;
    p += 3;
    size_t n = 0;
    while (p[n] != '\0' && p[n] != '/' && p[n] != ':' &&
           p[n] != '?' && p[n] != '#') {
        ++n;
    }
    if (n == 0 || n + 1 > out_size) return -1;
    memcpy(out, p, n);
    out[n] = '\0';
    return 0;
}

nr_realm nr_classify_url(const char *url) {
    char host[NR_MAX_HOST + 1];
    if (host_of(url, host, sizeof host) != 0) return NR_CLEARNET;
    return nr_classify_host(host);
}

nr_route nr_route_for(const char *url, nr_config cfg) {
    if (url == NULL) return NR_ROUTE_BLOCKED;  /* fail closed */
    switch (nr_classify_url(url)) {
        case NR_ONION:
            return cfg.tor_enabled ? NR_ROUTE_TOR : NR_ROUTE_BLOCKED;
        case NR_I2P:
            return cfg.i2p_enabled ? NR_ROUTE_I2P : NR_ROUTE_BLOCKED;
        case NR_CLEARNET:
        default:
            return (cfg.tor_enabled && cfg.torify_clearnet) ? NR_ROUTE_TOR
                                                            : NR_ROUTE_DIRECT;
    }
}

int nr_realm_allows_http(nr_realm r) {
    /* I2P eepsites are http; the I2P layer encrypts and authenticates by destination.
     * .onion stays https-only (owner's choice); clearnet is always https. */
    return r == NR_I2P;
}

const char *nr_realm_name(nr_realm r) {
    switch (r) {
        case NR_CLEARNET: return "clearnet";
        case NR_ONION:    return "onion";
        case NR_I2P:      return "i2p";
    }
    return "clearnet";
}

const char *nr_route_name(nr_route r) {
    switch (r) {
        case NR_ROUTE_DIRECT:  return "direct";
        case NR_ROUTE_TOR:     return "tor";
        case NR_ROUTE_I2P:     return "i2p";
        case NR_ROUTE_BLOCKED: return "blocked";
    }
    return "blocked";
}
