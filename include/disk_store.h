#ifndef FREEDOM_DISK_STORE_H
#define FREEDOM_DISK_STORE_H

#include <stddef.h>
#include <stdint.h>

#include "local_store.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * disk_store — atomic encrypted persistence for local_store blobs.
 *
 * The persistence orchestrator: it wires filesystem I/O to the pure crypto of
 * local_store. Nothing readable ever lands on disk; writes are atomic (temp +
 * fsync + rename) with 0600 permissions; reads of a tampered file or with a
 * wrong key fail closed without releasing plaintext.
 *
 * Keys are raw 32-byte keys (derive once with ls_derive_key at unlock, reuse).
 * See spec/disk_store.md for the full contract.
 */

typedef enum ds_status {
    DS_OK = 0,
    DS_ERR_NULL_ARG,
    DS_ERR_IO,         /* open/read/write/rename/fsync failed */
    DS_ERR_TOO_LARGE,  /* file or plaintext exceeds limits */
    DS_ERR_FORMAT,     /* not a valid local_store container */
    DS_ERR_AUTH,       /* wrong key or tampering */
    DS_ERR_CRYPTO,     /* unexpected AEAD/RNG failure */
    DS_ERR_OOM
} ds_status;

/* Seals plaintext under key with the given AEAD and writes it atomically to
 * path with 0600 permissions. */
ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
                   const uint8_t *plaintext, size_t pt_len);

/* Reads and decrypts path. Wrong key / tampering => DS_ERR_AUTH (no plaintext).
 * *out is owned; release with ds_free. */
ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **out, size_t *out_len);

/* Secure free of a buffer returned by ds_read (delegates to ls_free). */
void ds_free(uint8_t *buf, size_t len);

#endif /* FREEDOM_DISK_STORE_H */
