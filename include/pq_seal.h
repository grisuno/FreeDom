#ifndef FREEDOM_PQ_SEAL_H
#define FREEDOM_PQ_SEAL_H

#include <stddef.h>
#include <stdint.h>

#include "local_store.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * pq_seal -- hybrid at-rest sealing: ML-KEM-512 (FIPS 203, OpenSSL default provider) combined
 * with the profile's symmetric key. The data key needs BOTH secrets (HKDF over the KEM shared
 * secret and the profile key), so neither a broken KEM nor a leaked profile key opens a blob.
 * Trusted side only. See spec/pq_seal.md.
 */

#define PQS_MAGIC     "FPQ1"
#define PQS_MAGIC_LEN 4u
#define PQS_CT_LEN    768u   /* ML-KEM-512 ciphertext */

typedef enum pqs_status {
    PQS_OK = 0,
    PQS_ERR_NULL_ARG,
    PQS_ERR_CRYPTO,   /* keygen/encapsulation/KDF failed */
    PQS_ERR_FORMAT,   /* not an FPQ1 blob (magic, truncated) */
    PQS_ERR_AUTH,     /* tampering, foreign key or wrong wrap key (no plaintext released) */
    PQS_ERR_TOO_LARGE,
    PQS_ERR_OOM
} pqs_status;

typedef struct pqs_keys pqs_keys;   /* opaque ML-KEM-512 key pair */

pqs_status pqs_generate(pqs_keys **out);
/* DER of the PRIVATE key: secret, the caller seals it before it touches disk. *der is owned
 * (release with pqs_buf_free). */
pqs_status pqs_export(const pqs_keys *k, uint8_t **der, size_t *len);
pqs_status pqs_import(const uint8_t *der, size_t len, pqs_keys **out);
void pqs_free(pqs_keys *k);

/* Seals pt under keys + wrap. *out is owned (pqs_buf_free). */
pqs_status pqs_seal(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const uint8_t *pt, size_t pt_len, uint8_t **out, size_t *out_len);
/* Opens a pqs_seal blob. Wrong keys/wrap/tamper => PQS_ERR_AUTH. *out is owned. */
pqs_status pqs_open(const pqs_keys *k, const uint8_t wrap[LS_KEY_LEN],
                    const uint8_t *in, size_t in_len, uint8_t **out, size_t *out_len);

/* Zeroes then frees a buffer returned by this module. */
void pqs_buf_free(uint8_t *buf, size_t len);

#endif /* FREEDOM_PQ_SEAL_H */
