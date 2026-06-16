/*
 * disk_store — implementation: atomic encrypted persistence for local_store.
 *
 * Orchestrator only: filesystem I/O wired to the pure crypto of local_store.
 * Writes go to a sibling mkstemp file (same directory => atomic rename), are
 * fsync'd, then renamed over the target; on any error the temp is removed and
 * the target is left untouched. Reads are bounded, decrypted, and the ciphertext
 * buffer is securely wiped.
 */

#define _POSIX_C_SOURCE 200809L

#include "disk_store.h"

#include "local_store.h"

#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

/* --- framed I/O over a single fd --- */

static int write_full(int fd, const void *buf, size_t n) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t done = 0;
    while (done < n) {
        ssize_t w = write(fd, p + done, n - done);
        if (w < 0) { if (errno == EINTR) continue; return -1; }
        done += (size_t)w;
    }
    return 0;
}

static int read_full(int fd, void *buf, size_t n) {
    uint8_t *p = (uint8_t *)buf;
    size_t got = 0;
    while (got < n) {
        ssize_t r = read(fd, p + got, n - got);
        if (r < 0) { if (errno == EINTR) continue; return -1; }
        if (r == 0) return -1; /* unexpected EOF (file shrank) */
        got += (size_t)r;
    }
    return 0;
}

/* Best-effort fsync of the directory holding path, for crash durability of the
 * rename. Failures are non-fatal (some filesystems do not support it). */
static void fsync_dir(const char *path) {
    char *dup = strdup(path);
    if (dup == NULL) return;
    char *slash = strrchr(dup, '/');
    const char *dir;
    if (slash == dup) {
        dir = "/";
    } else if (slash != NULL) {
        *slash = '\0';
        dir = dup;
    } else {
        dir = ".";
    }
    int dfd = open(dir, O_RDONLY | O_DIRECTORY | O_CLOEXEC);
    if (dfd >= 0) { (void)fsync(dfd); close(dfd); }
    free(dup);
}

static ds_status map_ls(ls_status s) {
    switch (s) {
        case LS_OK:            return DS_OK;
        case LS_ERR_NULL_ARG:  return DS_ERR_NULL_ARG;
        case LS_ERR_TOO_LARGE: return DS_ERR_TOO_LARGE;
        case LS_ERR_FORMAT:    return DS_ERR_FORMAT;
        case LS_ERR_AUTH:      return DS_ERR_AUTH;
        case LS_ERR_OOM:       return DS_ERR_OOM;
        case LS_ERR_KDF:
        case LS_ERR_CRYPTO:
        default:               return DS_ERR_CRYPTO;
    }
}

/* --- public --- */

ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
                   const uint8_t *plaintext, size_t pt_len) {
    if (path == NULL || key == NULL) return DS_ERR_NULL_ARG;
    if (plaintext == NULL && pt_len > 0) return DS_ERR_NULL_ARG;
    if (pt_len > LS_MAX_PLAINTEXT) return DS_ERR_TOO_LARGE;

    uint8_t *blob = NULL;
    size_t blob_len = 0;
    ls_status ls = ls_seal(key, aead, plaintext, pt_len, &blob, &blob_len);
    if (ls != LS_OK) return map_ls(ls);

    size_t plen = strlen(path);
    char *tmp = (char *)malloc(plen + sizeof ".XXXXXX");
    if (tmp == NULL) { ls_free(blob, blob_len); return DS_ERR_OOM; }
    memcpy(tmp, path, plen);
    memcpy(tmp + plen, ".XXXXXX", sizeof ".XXXXXX");

    int fd = mkstemp(tmp);
    if (fd < 0) { free(tmp); ls_free(blob, blob_len); return DS_ERR_IO; }
    (void)fchmod(fd, 0600); /* mkstemp already yields 0600; make it explicit */

    ds_status rc = DS_OK;
    if (write_full(fd, blob, blob_len) != 0) rc = DS_ERR_IO;
    if (rc == DS_OK && fsync(fd) != 0)        rc = DS_ERR_IO;
    if (close(fd) != 0 && rc == DS_OK)        rc = DS_ERR_IO;

    if (rc == DS_OK && rename(tmp, path) != 0) rc = DS_ERR_IO;

    if (rc != DS_OK) unlink(tmp);
    else             fsync_dir(path);

    free(tmp);
    ls_free(blob, blob_len);
    return rc;
}

ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **out, size_t *out_len) {
    if (out == NULL || out_len == NULL) return DS_ERR_NULL_ARG;
    *out = NULL; *out_len = 0;
    if (path == NULL || key == NULL) return DS_ERR_NULL_ARG;

    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) return DS_ERR_IO;

    struct stat st;
    if (fstat(fd, &st) != 0) { close(fd); return DS_ERR_IO; }
    if (!S_ISREG(st.st_mode)) { close(fd); return DS_ERR_IO; }
    if (st.st_size < 0 ||
        (uintmax_t)st.st_size > (uintmax_t)(LS_OVERHEAD + LS_MAX_PLAINTEXT)) {
        close(fd);
        return DS_ERR_TOO_LARGE;
    }

    size_t n = (size_t)st.st_size;
    uint8_t *blob = (uint8_t *)malloc(n ? n : 1);
    if (blob == NULL) { close(fd); return DS_ERR_OOM; }
    if (n != 0 && read_full(fd, blob, n) != 0) {
        ls_free(blob, n);
        close(fd);
        return DS_ERR_IO;
    }
    close(fd);

    ls_status ls = ls_open(key, blob, n, out, out_len);
    ls_free(blob, n); /* ciphertext buffer: wipe and free */
    return map_ls(ls);
}

void ds_free(uint8_t *buf, size_t len) {
    ls_free(buf, len);
}
