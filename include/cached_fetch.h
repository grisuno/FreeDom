#ifndef FREEDOM_CACHED_FETCH_H
#define FREEDOM_CACHED_FETCH_H

#include <time.h>

#include "http_cache.h"
#include "secure_fetch.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * cached_fetch -- the HTTP cache in front of the gated fetcher (spec/http_cache.md). GET only,
 * https only, never with credentials or a Range; a hit changes WHEN bytes move, never WHAT is
 * fetched: a miss or a revalidation goes through the same fetcher and policy as before.
 */

typedef sf_status (*cf_fetch_fn)(const char *url, sf_config *cfg, sf_response *out,
                                 int *downgraded, int allowlisted);

/* Cache-aware GET. `partition` is the top-level site (double keying). On a fresh hit the
 * response is rebuilt from the cache with no network; on a stale entry with a validator one
 * conditional GET is sent to the stored FINAL url and a 304 serves the stored body. */
sf_status cf_get_with(hc_store *store, cf_fetch_fn fetch, const char *partition, const char *url,
                      sf_config *cfg, sf_response *out, int *downgraded, int allowlisted,
                      time_t now);

/* Process-wide store used by cf_get (NULL = caching off; set once at startup). */
void cf_set_store(hc_store *store);
hc_store *cf_store(void);

/* cf_get_with over the process store, the real gated fetcher and the wall clock. */
sf_status cf_get(const char *partition, const char *url, sf_config *cfg, sf_response *out,
                 int *downgraded, int allowlisted);

/* Persists permanent redirects (301/308) in the store and consults it on a RAM miss. */
void cf_attach_redirect_memory(hc_store *store);

#endif /* FREEDOM_CACHED_FETCH_H */
