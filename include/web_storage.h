#ifndef FREEDOM_WEB_STORAGE_H
#define FREEDOM_WEB_STORAGE_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * web_storage — in-MEMORY localStorage for trusted hosts (owner decision: nothing
 * persists to disk). Pure, I/O-free: a per-origin key/value database with a quota,
 * plus the bounded wire snapshot the confined worker sends back, validated in full
 * before it may touch the database. See spec/web_storage.md.
 */

#define WST_MAX_ORIGINS 256u
#define WST_MAX_KEYS    65536u
#define WST_QUOTA       ((size_t)(5u * 1024u * 1024u))   /* key + value bytes per origin */
#define WST_ORIGIN_MAX  512u

typedef struct wst_db wst_db;

/* Empty database, or NULL on OOM. */
wst_db *wst_new(void);

/* Frees everything. NULL is a no-op. */
void wst_free(wst_db *db);

/* Snapshot of origin's pairs ([n:u32]([klen:u32][key][vlen:u32][val])*, little-endian)
 * into an owned *out of *len bytes. An unknown origin yields a valid empty snapshot.
 * 0, or -1 on NULL args / OOM. */
int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);

/* Pure validation of a snapshot: 0 when it is complete and well-formed (counts and
 * lengths fit, total <= WST_QUOTA, keys unique, UTF-8 well-formed), else -1. */
int wst_decode_check(const char *blob, size_t len);

/* Replaces origin's contents with the snapshot after wst_decode_check. On any
 * failure returns -1 and the database is unchanged. A full origin table evicts the
 * least recently used origin. */
int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);

/* Calls fn(ctx, key, klen, val, vlen) for every pair of a snapshot, in order, after
 * validating it in full (wst_decode_check). Returns 0, or -1 when invalid (fn is then
 * never called). The one parser of the format, shared by the worker. */
int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *key, size_t klen,
                           const char *val, size_t vlen),
                void *ctx);

/* Builds a snapshot from n pairs into an owned *out. Fails (-1) on NULL args, OOM
 * or when the result would not pass wst_decode_check (quota, count, UTF-8, dups). */
int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, const size_t *vlens, size_t n,
             char **out, size_t *len);

/* Key + value bytes stored for origin (0 if unknown). */
size_t wst_origin_bytes(const wst_db *db, const char *origin);

#endif /* FREEDOM_WEB_STORAGE_H */
