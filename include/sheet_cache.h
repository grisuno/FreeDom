/*
 * sheet_cache -- parsed stylesheet retained under an exact key (spec/sheet_cache.md).
 *
 * css_parse_scoped is a pure function of its inputs, and a page re-derives its view on
 * every timer tick and event with the stylesheet text unchanged. This module retains the
 * LAST parsed sheet and hands it back when every parse input is byte-identical. One
 * entry, exact comparison (no hash, so no collision can serve the wrong sheet).
 *
 * Ownership: the cache has a single owner (shc_new / shc_free). Every shc_acquire returns
 * one reference the caller drops with shc_release; a sheet outlives the cache entry and
 * the cache itself for as long as a reference is held. No global state, no I/O.
 */
#ifndef FREEDOM_SHEET_CACHE_H
#define FREEDOM_SHEET_CACHE_H

#include <stddef.h>

#include "css.h"

#ifndef __STDC_VERSION__
#error "sheet_cache requires C11"
#endif
#ifdef __cplusplus
#error "sheet_cache is C only"
#endif

typedef struct shc_cache shc_cache;
typedef struct shc_sheet shc_sheet;

/* Every input of the parse. `media` carries the @media gate and the optional root
 * matcher, a callback into the live DOM. The module records each question the parse
 * asks that matcher and the answer; a later acquire is a hit only when the static
 * inputs are byte-identical AND the matcher passed in *that* key still gives every
 * recorded answer. So the matcher must be a deterministic function of the selector and
 * the caller's current DOM, free of side effects. All pointers are borrowed. */
typedef struct shc_key {
    const char      *text;
    size_t           len;
    const css_media *media;       /* NULL: css_parse_scoped's own default */
    const char      *root_scope;  /* NULL is distinct from "" */
} shc_key;

typedef struct shc_stats {
    unsigned long hits;      /* served without parsing */
    unsigned long misses;    /* parsed and retained */
    unsigned long bypasses;  /* parsed, not retained (oversized, too many matcher
                              * questions, OOM) */
} shc_stats;

/* max_text_bytes: texts longer than this are parsed but never retained; 0 selects
 * FC_SHC_MAX_TEXT_BYTES. NULL on OOM. */
shc_cache *shc_new(size_t max_text_bytes);

/* Drops the cache's own reference to its entry. NULL-safe. */
void shc_free(shc_cache *c);

/* The parsed sheet for *key: the retained one when every input matches, a fresh parse
 * otherwise. cache == NULL parses without retaining. Returns NULL on a NULL key, a NULL
 * text with len > 0, len == SIZE_MAX, or OOM of the handle. */
shc_sheet *shc_acquire(shc_cache *cache, const shc_key *key);

/* The read-only sheet behind a handle; NULL when the parse itself failed (the css
 * module treats a NULL sheet as empty) or s is NULL. */
const css_sheet *shc_css(const shc_sheet *s);

/* Drops one reference. NULL-safe. */
void shc_release(shc_sheet *s);

/* Counters since shc_new; zeroes *out on a NULL cache. */
void shc_stats_get(const shc_cache *c, shc_stats *out);

#endif /* FREEDOM_SHEET_CACHE_H */
