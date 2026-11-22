#ifndef FREEDOM_MASK_CACHE_H
#define FREEDOM_MASK_CACHE_H

#ifdef __cplusplus
#error "Freedom is pure C11"
#endif

#include <stddef.h>

/* mask_cache (mkc_) -- 8-bit alpha masks retained across frames (spec/mask_cache.md).
 * A blurred box-shadow silhouette depends only on its geometry and sigma, never on the
 * scroll offset or the clock, so the painter builds it once and reuses it. Pure: no I/O,
 * no Cairo, no global state. One owner (the window), one idempotent destructor. */

/* Every input the cached mask is a function of. Compared field by field (exact: no hash;
 * a NaN never equals, so it never hits). */
typedef struct mkc_key {
    int    w, h;        /* mask size in px */
    double sx, sy;      /* silhouette origin inside the mask */
    double sw, sh, sr;  /* silhouette size and corner radius */
    double sigma;       /* blur standard deviation */
    int    inset;       /* 1 = inner shadow (inverted silhouette) */
} mkc_key;

typedef struct mkc_cache mkc_cache;

/* A cache holding at most byte_budget bytes of mask buffers in at most max_entries masks.
 * NULL when either bound is 0 or on allocation failure. */
mkc_cache *mkc_new(size_t byte_budget, size_t max_entries);

/* Releases the cache and every buffer. NULL-safe. */
void mkc_free(mkc_cache *c);

/* Drops every retained mask (document change). NULL-safe, idempotent. */
void mkc_clear(mkc_cache *c);

/* The buffer retained for k (stride bytes per row) and makes it the most recent, or NULL.
 * Valid until the next mkc_put / mkc_clear / mkc_free. */
const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride);

/* Reserves a zeroed buffer of stride * k->h bytes owned by the cache for k (replacing any
 * entry for k), evicting least-recently-used masks until it fits, and returns it for the
 * caller to fill. NULL, cache untouched, when an argument is invalid (stride < w, a size
 * <= 0, an overflowing or over-budget size) or the allocation fails. */
unsigned char *mkc_put(mkc_cache *c, const mkc_key *k, int stride);

/* Bytes currently retained / number of masks retained (0 for NULL). */
size_t mkc_bytes(const mkc_cache *c);
size_t mkc_count(const mkc_cache *c);

#endif
