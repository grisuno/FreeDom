#ifndef FREEDOM_SHA2_H
#define FREEDOM_SHA2_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4), pure and allocation-free.
 * Backs crypto.subtle.digest in the confined worker, which has no libcrypto. See spec/js_env.md.
 */

typedef enum sha_alg { SHA_1 = 0, SHA_256, SHA_384, SHA_512 } sha_alg;

#define SHA_MAX_DIGEST 64

/* Digest length in bytes of alg (20/32/48/64), or 0 for an unknown alg. */
size_t sha_digest_len(sha_alg alg);

/* Maps a WebCrypto algorithm name ("SHA-256", case-insensitive) to alg. 0 on success, -1 unknown. */
int sha_alg_from_name(const char *name, sha_alg *out);

/* Hashes data[0..len) into out (>= sha_digest_len(alg) bytes). 0 on success, -1 on a bad argument.
 * data may be NULL only when len == 0. */
int sha_digest(sha_alg alg, const void *data, size_t len, uint8_t *out);

#endif /* FREEDOM_SHA2_H */
