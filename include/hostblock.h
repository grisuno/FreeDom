#ifndef FREEDOM_HOSTBLOCK_H
#define FREEDOM_HOSTBLOCK_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * hostblock — Privacy by Default: a host filter built from /etc/hosts-format
 * lists (.conf files), with a blocklist and an allowlist.
 *
 * Pure, I/O-free, no global mutable state (the directly auditable surface): the
 * caller reads the list files and passes their text in; this module parses them
 * into hash tables and decides whether a host is blocked. It opens no sockets and
 * reads no files. The orchestrator consults hb_check() BEFORE opening a socket.
 *
 * A blocklist entry blocks a domain and all its subdomains; an allowlist entry
 * re-enables a domain and its subdomains, so a single subdomain can be seen even
 * when its parent domain is blocked. The allowlist wins over the blocklist.
 *
 * This is an adblock-style filter, not the security boundary (that is the sandbox
 * and the network policy): on any doubt it fails OPEN (does not over-block), since
 * silently dropping content is worse here than letting one tracker through.
 *
 * See spec/hostblock.md for the full contract.
 */

typedef struct hb_set hb_set;   /* opaque: a block hash table plus an allow one */

typedef enum hb_list {
    HB_LIST_BLOCK = 0,  /* domains (and subdomains) to block */
    HB_LIST_ALLOW       /* domains (and subdomains) to re-enable; wins over block */
} hb_list;

typedef enum hb_decision {
    HB_ALLOW = 0,  /* the host may be contacted */
    HB_BLOCK       /* the host is on the blocklist (and not re-enabled) */
} hb_decision;

typedef enum hb_status {
    HB_OK = 0,
    HB_ERR_NULL_ARG,  /* set or text was NULL */
    HB_ERR_OOM        /* allocation failure while growing a table */
} hb_status;

/* Allocates an empty set. Returns NULL on OOM. */
hb_set *hb_new(void);

/* Frees a set and every domain it owns. Idempotent and safe on NULL. */
void hb_free(hb_set *s);

/* Parses /etc/hosts-format text and adds its domains to the given list. A leading
 * IP token per line (only digits, '.' and ':') is ignored, so "0.0.0.0 ads.x.com"
 * contributes only "ads.x.com"; bare-domain-per-line lists work too. Tokens are
 * lowercased, a trailing dot trimmed, then validated (1..253 chars; a-z 0-9 . - _);
 * invalid tokens are skipped without aborting the load. Cumulative; duplicates are
 * ignored. set/text NULL => HB_ERR_NULL_ARG; allocation failure => HB_ERR_OOM. */
hb_status hb_load(hb_set *s, const char *text, hb_list list);

/* Decision for a host. s/host NULL, empty, or longer than 253 chars => HB_ALLOW
 * (without a list, or for a nonsense host, the filter does not over-block). The
 * host is lowercased and a trailing dot trimmed, then its domain suffixes are
 * walked (the host, then without its first label, ...): any suffix on the allowlist
 * => HB_ALLOW (allow wins, covers subdomains); else any suffix on the blocklist
 * => HB_BLOCK; else HB_ALLOW. */
hb_decision hb_check(const hb_set *s, const char *host);

/* 1 iff a domain suffix of host is explicitly on the allowlist (covers subdomains),
 * else 0. Distinct from hb_check: this reports an EXPLICIT allowlist entry, not the
 * "allowed because nothing blocks it" default. The orchestrator uses it as the
 * user's sovereign per-host override -- e.g. to navigate a site below Freedom's TLS
 * standard. s/host NULL, empty, or longer than 253 chars => 0. */
int hb_is_allowlisted(const hb_set *s, const char *host);

/* Number of unique domains on the given list (for tests/diagnostics). 0 if s is
 * NULL. */
size_t hb_count(const hb_set *s, hb_list list);

#endif /* FREEDOM_HOSTBLOCK_H */
