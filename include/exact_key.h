#ifndef FREEDOM_EXACT_KEY_H
#define FREEDOM_EXACT_KEY_H

#ifdef __cplusplus
#error "Freedom is pure C11"
#endif

#include <stddef.h>

/* exact_key (ek_) -- a cache key built by OBSERVING every input of what is cached, compared
 * byte for byte (spec/exact_key.md). No hash: a false hit would be a wrong render. Pure, no
 * global state; one owner, one idempotent destructor. */

/* Largest key (anti-DoS); a bigger one is marked bad and never equals anything. */
#define EK_MAX_BYTES ((size_t)1 << 20)

typedef struct ek_key {
    unsigned char *b;
    size_t         n, cap;
    int            bad;   /* an append failed or overflowed: never equal (fail-closed) */
} ek_key;

/* An empty key with no memory. NULL-safe. */
void ek_init(ek_key *k);

/* Empties the key (n = 0, bad = 0) and keeps its memory. NULL-safe. */
void ek_reset(ek_key *k);

/* Appends len bytes of p. A failed or oversized append, or p == NULL with len > 0, marks the
 * key bad. NULL key is a no-op. */
void ek_put(ek_key *k, const void *p, size_t len);

/* 1 when a and b hold the same byte sequence and neither is bad, else 0 (NULL = 0). */
int ek_equal(const ek_key *a, const ek_key *b);

/* Exchanges the contents of a and b without copying. NULL-safe. */
void ek_swap(ek_key *a, ek_key *b);

/* Releases the key's memory and leaves it empty. NULL-safe, idempotent. */
void ek_free(ek_key *k);

#endif
