#ifndef FREEDOM_NET_REALM_H
#define FREEDOM_NET_REALM_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * net_realm — network realm classification and routing (Tor / I2P / clearnet).
 *
 * Pure, I/O-free, allocation-free decision logic (the directly auditable surface):
 * given a host or URL it decides the realm (clearnet, .onion, .i2p) and, given which
 * proxies are enabled, how to route it (direct, via Tor, via I2P, or blocked). It
 * opens no sockets and talks to no proxy; the orchestrator (secure_fetch / GUI)
 * carries out the decision.
 *
 * Two anonymity invariants are guaranteed here, testable without a network:
 *   1. Realm isolation: a .onion address can ONLY exit through Tor; a .i2p only
 *      through I2P. Never through clearnet DNS (which would leak the lookup).
 *   2. Fail-closed: a realm that needs a proxy that is not enabled is BLOCKED, never
 *      silently downgraded to a direct (de-anonymizing) connection.
 *
 * The Tor daemon is NOT embedded (huge attack surface, against doctrine): integration
 * is "at the socket level" against a local proxy the user runs (tor, i2pd).
 *
 * See spec/net_realm.md for the full contract.
 */

typedef enum nr_realm {
    NR_CLEARNET = 0,  /* ordinary DNS host */
    NR_ONION,         /* *.onion -> Tor */
    NR_I2P            /* *.i2p   -> I2P */
} nr_realm;

typedef enum nr_route {
    NR_ROUTE_DIRECT = 0,  /* connect directly (clearnet) */
    NR_ROUTE_TOR,         /* via the Tor SOCKS5h proxy (remote DNS) */
    NR_ROUTE_I2P,         /* via the I2P HTTP proxy */
    NR_ROUTE_BLOCKED      /* unreachable under the current config (fail closed) */
} nr_route;

typedef struct nr_config {
    int tor_enabled;      /* a Tor proxy is available/configured */
    int i2p_enabled;      /* an I2P proxy is available/configured */
    int torify_clearnet;  /* route ordinary clearnet through Tor too (only if tor_enabled) */
} nr_config;

/* Realm of a host, by final TLD label (case-insensitive, one trailing dot trimmed):
 * ".onion" => NR_ONION, ".i2p" => NR_I2P, else NR_CLEARNET. host NULL/empty/>253, or
 * a bare "onion"/"i2p" with no leading label, => NR_CLEARNET. */
nr_realm nr_classify_host(const char *host);

/* Realm of a URL: extracts its host and classifies it. No host => NR_CLEARNET. */
nr_realm nr_classify_url(const char *url);

/* Route for a URL under cfg (see the table in spec/net_realm.md). url NULL =>
 * NR_ROUTE_BLOCKED (fail closed: never route what cannot be classified). A realm
 * whose proxy is not enabled => NR_ROUTE_BLOCKED. */
nr_route nr_route_for(const char *url, nr_config cfg);

/* 1 iff plain http:// is acceptable for this realm. An overlay realm authenticates
 * and encrypts by its address (the I2P destination / onion key), so http over it is
 * not a downgrade. Currently: NR_I2P => 1 (eepsites are http); NR_ONION => 0 (owner
 * keeps .onion https-only); NR_CLEARNET => 0 (clearnet is always https). The caller
 * must still route the request through the overlay proxy. */
int nr_realm_allows_http(nr_realm r);

/* Stable short English names for structured/agent output and toasts. Never NULL. */
const char *nr_realm_name(nr_realm r);
const char *nr_route_name(nr_route r);

#endif /* FREEDOM_NET_REALM_H */
