#ifndef FREEDOM_REQUEST_POLICY_H
#define FREEDOM_REQUEST_POLICY_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * request_policy — Privacy by Default: block all third-party subresource
 * requests at the network engine.
 *
 * Pure, I/O-free policy logic (the directly auditable surface): a page loader
 * consults rp_evaluate() before letting secure_fetch touch any subresource.
 * Allowing third parties is deliberately not representable.
 *
 * See spec/request_policy.md for the full contract.
 */

typedef enum rp_decision {
    RP_ALLOW = 0,          /* same-site: allowed */
    RP_BLOCK_THIRD_PARTY,  /* cross-site subresource: blocked by default */
    RP_BLOCK_SCHEME,       /* scheme is not https */
    RP_BLOCK_INVALID       /* URL missing / unparseable (fails closed) */
} rp_decision;

/* Lowercased host of an absolute URL into out. Returns 0 on success, -1 if no
 * host can be parsed or it does not fit in out. */
int rp_host_of(const char *url, char *out, size_t out_size);

/* Registrable domain ("site") of a host into out (simplified public-suffix
 * rule). Returns 0 on success, -1 on empty host or insufficient buffer. */
int rp_site_of(const char *host, char *out, size_t out_size);

/* 1 if both URLs share the same site, 0 otherwise (including parse failure). */
int rp_same_site(const char *top_level_url, const char *request_url);

/* Decision for a subresource request given the top-level document URL. */
rp_decision rp_evaluate(const char *top_level_url, const char *request_url);

#endif /* FREEDOM_REQUEST_POLICY_H */
