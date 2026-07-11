/*
 * profile — implementation: encrypted persistence orchestrator (Hito 10).
 *
 * Wires the pure prefs model to disk through disk_store/local_store. A
 * per-device keyfile (16B salt + 32B secret from the OS RNG, 0600, written
 * atomically) feeds Argon2id once per launch; prefs.bin is an AEAD-sealed
 * container. Fail closed, never clobber: a corrupt keyfile or a blob that
 * does not authenticate is an error, not a rewrite. See spec/profile.md.
 */

#define _POSIX_C_SOURCE 200809L

#include "profile.h"
#include "disk_store.h"

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <openssl/crypto.h>
#include <openssl/rand.h>

#define PROFILE_KEYFILE_LEN (LS_SALT_LEN + LS_KEY_LEN)  /* 16 + 32 */

static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, size_t cap) {
    int n = snprintf(out, cap, "%s/%s", ctx->dir, name);
    return (n > 0 && (size_t)n < cap) ? 0 : -1;
}

/* Writes the fresh keyfile atomically (tmp 0600 + fsync + rename). */
static profile_status keyfile_create(const char *dir, const char *path,
                                     uint8_t kf[PROFILE_KEYFILE_LEN]) {
    if (RAND_bytes(kf, PROFILE_KEYFILE_LEN) != 1) return PROFILE_ERR_KEY;
    char tmp[1088];
    int n = snprintf(tmp, sizeof tmp, "%s/.profile.key.XXXXXX", dir);
    if (n <= 0 || (size_t)n >= sizeof tmp) return PROFILE_ERR_DIR;
    int fd = mkstemp(tmp);
    if (fd < 0) return PROFILE_ERR_IO;
    if (fchmod(fd, 0600) != 0 ||
        write(fd, kf, PROFILE_KEYFILE_LEN) != (ssize_t)PROFILE_KEYFILE_LEN ||
        fsync(fd) != 0) {
        close(fd);
        unlink(tmp);
        return PROFILE_ERR_IO;
    }
    close(fd);
    if (rename(tmp, path) != 0) {
        unlink(tmp);
        return PROFILE_ERR_IO;
    }
    return PROFILE_OK;
}

profile_status profile_open(profile_ctx *ctx, const char *dir) {
    if (ctx == NULL || dir == NULL) return PROFILE_ERR_NULL_ARG;
    memset(ctx, 0, sizeof *ctx);
    size_t dlen = strlen(dir);
    if (dlen == 0 || dlen >= sizeof ctx->dir - 32) return PROFILE_ERR_DIR;
    struct stat st;
    if (stat(dir, &st) != 0 || !S_ISDIR(st.st_mode)) return PROFILE_ERR_DIR;
    memcpy(ctx->dir, dir, dlen + 1);

    char path[1088];
    if (join_path(ctx, PROFILE_KEY_FILE, path, sizeof path) != 0)
        return PROFILE_ERR_DIR;

    uint8_t kf[PROFILE_KEYFILE_LEN];
    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) {
        if (errno != ENOENT) return PROFILE_ERR_IO;
        profile_status ps = keyfile_create(ctx->dir, path, kf);
        if (ps != PROFILE_OK) return ps;
    } else {
        struct stat kst;
        if (fstat(fd, &kst) != 0 ||
            kst.st_size != (off_t)PROFILE_KEYFILE_LEN) {
            close(fd);
            return PROFILE_ERR_KEY;  /* fail closed, never clobber */
        }
        ssize_t got = read(fd, kf, PROFILE_KEYFILE_LEN);
        close(fd);
        if (got != (ssize_t)PROFILE_KEYFILE_LEN) return PROFILE_ERR_IO;
    }

    ls_status ls = ls_derive_key(kf + LS_SALT_LEN, LS_KEY_LEN,
                                 kf, LS_SALT_LEN, ctx->key);
    OPENSSL_cleanse(kf, sizeof kf);
    if (ls != LS_OK) return PROFILE_ERR_KEY;
    ctx->ready = 1;
    return PROFILE_OK;
}

static profile_status map_ds(ds_status ds) {
    switch (ds) {
    case DS_OK:            return PROFILE_OK;
    case DS_ERR_NULL_ARG:  return PROFILE_ERR_NULL_ARG;
    case DS_ERR_AUTH:      return PROFILE_ERR_AUTH;
    case DS_ERR_FORMAT:    return PROFILE_ERR_FORMAT;
    case DS_ERR_TOO_LARGE: return PROFILE_ERR_FORMAT;
    case DS_ERR_OOM:       return PROFILE_ERR_OOM;
    case DS_ERR_IO:
    case DS_ERR_CRYPTO:
    default:               return PROFILE_ERR_IO;
    }
}

profile_status profile_load(const profile_ctx *ctx, prefs_state *out) {
    if (ctx == NULL || out == NULL || !ctx->ready) return PROFILE_ERR_NULL_ARG;
    char path[1088];
    if (join_path(ctx, PROFILE_PREFS_FILE, path, sizeof path) != 0)
        return PROFILE_ERR_DIR;
    struct stat st;
    if (stat(path, &st) != 0) {
        if (errno == ENOENT) return PROFILE_OK;  /* first launch: defaults */
        return PROFILE_ERR_IO;
    }
    uint8_t *pt = NULL;
    size_t pt_len = 0;
    ds_status ds = ds_read(path, ctx->key, &pt, &pt_len);
    if (ds != DS_OK) return map_ds(ds);
    prefs_status ps = prefs_parse((const char *)pt, pt_len, out);
    ds_free(pt, pt_len);
    if (ps == PREFS_ERR_OOM) return PROFILE_ERR_OOM;
    if (ps != PREFS_OK) return PROFILE_ERR_FORMAT;
    return PROFILE_OK;
}

profile_status profile_save(const profile_ctx *ctx, const prefs_state *p) {
    if (ctx == NULL || p == NULL || !ctx->ready) return PROFILE_ERR_NULL_ARG;
    char path[1088];
    if (join_path(ctx, PROFILE_PREFS_FILE, path, sizeof path) != 0)
        return PROFILE_ERR_DIR;
    char *text = NULL;
    size_t len = 0;
    prefs_status ps = prefs_format(p, &text, &len);
    if (ps != PREFS_OK)
        return (ps == PREFS_ERR_OOM) ? PROFILE_ERR_OOM : PROFILE_ERR_FORMAT;
    ds_status ds = ds_write(path, ctx->key, LS_AEAD_AES256_GCM,
                            (const uint8_t *)text, len);
    ls_free((uint8_t *)text, len);  /* secure wipe of the plaintext */
    return map_ds(ds);
}

void profile_close(profile_ctx *ctx) {
    if (ctx == NULL) return;
    OPENSSL_cleanse(ctx->key, sizeof ctx->key);
    ctx->ready = 0;
}
