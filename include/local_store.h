#ifndef FREEDOM_LOCAL_STORE_H
#define FREEDOM_LOCAL_STORE_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * local_store — encrypted local state at rest (Zero Knowledge).
 *
 * Pure cryptographic logic (no filesystem/network I/O; only the OS RNG is read,
 * which is inherent to generating salt/nonce). Seals/opens self-describing blobs
 * with an AEAD (AES-256-GCM by default, or ChaCha20-Poly1305) and an Argon2id
 * KDF, per the project crypto policy. A persistence orchestrator wraps these to
 * write/read the blobs; nothing on disk is ever readable without the key.
 *
 * Fail-closed: a failed authentication releases no plaintext.
 *
 * Backed by OpenSSL 3.x native (ARGON2ID + AEADs in the default provider).
 * See spec/local_store.md for the container format and full contract.
 */

#define LS_KEY_LEN       32u
#define LS_SALT_LEN      16u
#define LS_NONCE_LEN     12u
#define LS_TAG_LEN       16u
#define LS_HEADER_LEN    36u
#define LS_OVERHEAD      52u  /* LS_HEADER_LEN + LS_TAG_LEN */
#define LS_MAX_PLAINTEXT ((size_t)(64u * 1024u * 1024u))

typedef enum ls_aead {
    LS_AEAD_AES256_GCM        = 1,
    LS_AEAD_CHACHA20_POLY1305 = 2
} ls_aead;

typedef enum ls_status {
    LS_OK = 0,
    LS_ERR_NULL_ARG,
    LS_ERR_TOO_LARGE,  /* pt_len > LS_MAX_PLAINTEXT */
    LS_ERR_FORMAT,     /* malformed container: magic/version/aead/kdf/length */
    LS_ERR_AUTH,       /* authentication failed: wrong key or tampering */
    LS_ERR_KDF,        /* Argon2id derivation failed/unavailable */
    LS_ERR_CRYPTO,     /* unexpected AEAD/RNG failure */
    LS_ERR_OOM
} ls_status;

/* Derives a 32-byte key from a passphrase + salt with Argon2id (pinned v1
 * parameters). out_key receives LS_KEY_LEN bytes. */
ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const uint8_t *salt, size_t salt_len,
                        uint8_t out_key[LS_KEY_LEN]);

/* Seals plaintext under a raw 32-byte key (kdf_id = none). A random nonce is
 * generated internally. *out is owned; release with ls_free. */
ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *plaintext, size_t pt_len,
                  uint8_t **out, size_t *out_len);

/* Opens a container produced by ls_seal; verifies the tag. Wrong key/tamper =>
 * LS_ERR_AUTH and no plaintext is released. *out is owned; release with ls_free. */
ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t blob_len,
                  uint8_t **out, size_t *out_len);

/* Passphrase variant: generates a random salt, derives the key with Argon2id,
 * and stores the salt in the container so ls_open_passphrase can re-derive. */
ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
                             const uint8_t *plaintext, size_t pt_len,
                             uint8_t **out, size_t *out_len);

/* Opens a container produced by ls_seal_passphrase (kdf_id must be Argon2id). */
ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                             const uint8_t *blob, size_t blob_len,
                             uint8_t **out, size_t *out_len);

/* Secure free: OPENSSL_cleanse(buf, len) then free. Safe on NULL. */
void ls_free(uint8_t *buf, size_t len);

#endif /* FREEDOM_LOCAL_STORE_H */
