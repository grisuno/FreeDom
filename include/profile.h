#ifndef FREEDOM_PROFILE_H
#define FREEDOM_PROFILE_H

#include <stddef.h>
#include <stdint.h>

#include "local_store.h"
#include "prefs.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * profile — encrypted persistence orchestrator for the prefs model (Hito 10).
 *
 * Wires prefs (pure) to disk through disk_store/local_store: a per-device
 * keyfile (16B salt + 32B secret from the OS RNG, 0600) feeds Argon2id once
 * per launch; prefs.bin is an AEAD-sealed container written atomically.
 * Nothing readable ever lands on disk (Zero Knowledge).
 *
 * Threat-model honesty: the keyfile lives next to the blob (like any browser
 * profile without a master password). It keeps prefs.bin unreadable on its
 * own (partial backups/leaks) but does not resist an attacker with the whole
 * directory; the optional master-passphrase unlock is roadmap and needs no
 * container migration. Fail closed, never clobber: a corrupt keyfile or an
 * unauthenticated prefs.bin is an error, not a rewrite.
 *
 * See spec/profile.md for the full contract.
 */

#define PROFILE_KEY_FILE   "profile.key"  /* 16B salt + 32B secret, 0600 */
#define PROFILE_PREFS_FILE "prefs.bin"    /* sealed local_store container */

typedef enum profile_status {
    PROFILE_OK = 0,
    PROFILE_ERR_NULL_ARG,
    PROFILE_ERR_DIR,     /* dir NULL/empty/too long or missing */
    PROFILE_ERR_KEY,     /* keyfile corrupt (size) or KDF/RNG failure */
    PROFILE_ERR_IO,      /* read/write failure */
    PROFILE_ERR_AUTH,    /* prefs.bin tampered or foreign key (no clobber) */
    PROFILE_ERR_FORMAT,  /* container or prefs text invalid */
    PROFILE_ERR_OOM
} profile_status;

typedef struct profile_ctx {
    char    dir[1024];
    uint8_t key[LS_KEY_LEN];
    int     ready;
} profile_ctx;

/* Opens the profile in dir (must exist; the caller creates it 0700). Creates
 * the keyfile when absent (0600, atomic write); an existing keyfile of the
 * wrong size fails closed (PROFILE_ERR_KEY, never overwritten). Derives the
 * AEAD key (Argon2id, per-device salt) and marks ctx ready. */
profile_status profile_open(profile_ctx *ctx, const char *dir);

/* Loads and decrypts prefs.bin over an out ALREADY initialised (prefs_init).
 * Absent file => PROFILE_OK with defaults (first launch). Tampered/foreign =>
 * PROFILE_ERR_AUTH and out stays at defaults. */
profile_status profile_load(const profile_ctx *ctx, prefs_state *out);

/* Serializes p and writes it sealed and atomic to prefs.bin (0600). */
profile_status profile_save(const profile_ctx *ctx, const prefs_state *p);

/* Securely wipes the key in ctx. Idempotent; NULL-safe. */
void profile_close(profile_ctx *ctx);

#endif /* FREEDOM_PROFILE_H */
