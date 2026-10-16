/*
 * css_index -- cascade rule index (spec/css_index.md).
 *
 * A pre-filter over a sheet's selectors keyed by the subject compound's most
 * selective simple selector (id, else first class, else tag, else universal).
 * cix_candidates returns, in ascending document order and without duplicates,
 * every selector that CAN match an element; csel_matches still decides. Pure,
 * no global state, owned by the sheet.
 */
#ifndef FREEDOM_CSS_INDEX_H
#define FREEDOM_CSS_INDEX_H

#include "css_select.h"

#include <stddef.h>
#include <stdint.h>

typedef struct cix_entry {
    uint64_t key;
    uint32_t sel;
} cix_entry;

typedef struct cix_index {
    cix_entry *keyed;      /* sorted by (key, sel) */
    size_t     nkeyed;
    uint32_t  *universal;  /* ascending */
    size_t     nuniversal;
    size_t     nsels;      /* number of selectors the index was built for */
    int        valid;      /* 0 = absent/OOM: callers scan linearly */
} cix_index;

/* Builds the index over sels[0,n) into *idx, overwriting it (a built index must be
 * cix_free'd first). On OOM leaves *idx invalid (valid == 0). */
void cix_build(const css_sel *sels, size_t n, cix_index *idx);

/* Releases the index; idempotent. Leaves it invalid. */
void cix_free(cix_index *idx);

/* Candidate selector indices for el into *buf (grown with realloc, capacity *cap),
 * ascending and unique; returns the count, or (size_t)-1 on OOM or an invalid
 * index (the caller then scans linearly). */
size_t cix_candidates(const cix_index *idx, const css_element *el,
                      uint32_t **buf, size_t *cap);

#endif
