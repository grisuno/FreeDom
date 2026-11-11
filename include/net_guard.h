/*
 * net_guard -- remote content must not reach the private network (spec/net_guard.md).
 *
 * Pure: no I/O, no global state. Classifies a resolved peer address and decides whether
 * a request may connect to it given who asked. The user may navigate to a private host;
 * a public page (or a redirect it controls) may not do so on the user's behalf.
 */
#ifndef FREEDOM_NET_GUARD_H
#define FREEDOM_NET_GUARD_H

#include <stddef.h>

#ifndef __STDC_VERSION__
#error "net_guard requires C11"
#endif
#ifdef __cplusplus
#error "net_guard is C only"
#endif

typedef enum ng_verdict { NG_ALLOW = 0, NG_DENY = 1 } ng_verdict;

#define NG_FAMILY_V4 4
#define NG_FAMILY_V6 6

/* Who is asking for a connection. */
typedef struct ng_request {
    const char *initiator_host; /* host of the page or redirect hop that caused the
                                 * request; NULL = the user's own top-level navigation */
    int         same_site;      /* nonzero: target and initiator share a registrable domain */
    int         via_proxy;      /* nonzero: an overlay proxy carries the request, so the
                                 * peer address is the proxy's, not the target's */
} ng_request;

/* 1 when the address is not globally routable (loopback, RFC 1918, link-local, CGNAT,
 * documentation, multicast, reserved, IPv6 unique-local, and every IPv4-in-IPv6
 * embedding of those). family is NG_FAMILY_V4 (len 4) or NG_FAMILY_V6 (len 16), bytes
 * in network order. Anything else answers 1 (fail closed). */
int ng_addr_is_private(int family, const unsigned char *addr, size_t len);

/* As ng_addr_is_private over a textual IPv4/IPv6 address (optionally bracketed). Text
 * that is not exactly one address answers 1 (fail closed). */
int ng_text_is_private(const char *ip_text);

/* 1 when host is an IPv4/IPv6 literal (optionally bracketed), 0 for a name or NULL. A
 * registrable-domain comparison is meaningless for literals: compare them whole. */
int ng_host_is_ip(const char *host);

/* 1 when host names this machine or a private address without resolving anything:
 * "localhost", any "*.localhost", or a private IP literal. NULL/"" answers 0. */
int ng_host_is_local(const char *host);

/* The decision. peer_private is ng_addr_is_private of the address about to be (or
 * already) connected. r == NULL denies a private peer. */
ng_verdict ng_decide(const ng_request *r, int peer_private);

#endif /* FREEDOM_NET_GUARD_H */
