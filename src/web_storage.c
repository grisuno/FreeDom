/*
 * web_storage — implementation: in-memory per-origin localStorage snapshots.
 * See spec/web_storage.md. Pure: no I/O, nothing ever reaches the disk.
 */

#include "web_storage.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct wst_origin {
    char     *origin;
    char     *blob;       /* the validated snapshot, stored verbatim */
    size_t    len;
    size_t    bytes;      /* key + value bytes (the quota measure) */
    uint64_t  used;       /* LRU clock */
} wst_origin;

struct wst_db {
    wst_origin o[WST_MAX_ORIGINS];
    uint64_t   clock;
};

static uint32_t get_u32(const unsigned char *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

/* Well-formed UTF-8, allowing encoded surrogates (WTF-8): a JS string may hold a lone
 * surrogate and rejecting it would drop a legitimate page's whole store. Overlong
 * forms and code points past U+10FFFF are rejected. */
static int utf8_ok(const unsigned char *s, size_t n) {
    size_t i = 0;
    while (i < n) {
        unsigned char c = s[i];
        size_t k;
        uint32_t cp, min;
        if (c < 0x80) { ++i; continue; }
        if ((c & 0xE0) == 0xC0)      { k = 1; cp = c & 0x1F; min = 0x80; }
        else if ((c & 0xF0) == 0xE0) { k = 2; cp = c & 0x0F; min = 0x800; }
        else if ((c & 0xF8) == 0xF0) { k = 3; cp = c & 0x07; min = 0x10000; }
        else return 0;
        if (k > n - i - 1) return 0;
        for (size_t j = 1; j <= k; ++j) {
            if ((s[i + j] & 0xC0) != 0x80) return 0;
            cp = (cp << 6) | (s[i + j] & 0x3F);
        }
        if (cp < min || cp > 0x10FFFF) return 0;
        i += k + 1;
    }
    return 1;
}

typedef struct key_ref { const unsigned char *p; uint32_t n; } key_ref;

static int key_cmp(const void *a, const void *b) {
    const key_ref *x = (const key_ref *)a, *y = (const key_ref *)b;
    uint32_t m = x->n < y->n ? x->n : y->n;
    int c = memcmp(x->p, y->p, m);
    if (c != 0) return c;
    return (x->n > y->n) - (x->n < y->n);
}

/* Full validation; on success *bytes_out (optional) = key + value bytes. */
static int check(const char *blob, size_t len, size_t *bytes_out) {
    if (blob == NULL || len < 4) return -1;
    const unsigned char *b = (const unsigned char *)blob;
    uint32_t n = get_u32(b);
    if (n > WST_MAX_KEYS) return -1;
    key_ref *keys = NULL;
    if (n > 0) {
        keys = (key_ref *)calloc(n, sizeof *keys);
        if (keys == NULL) return -1;
    }
    size_t o = 4, bytes = 0;
    int ok = 1;
    for (uint32_t i = 0; i < n && ok; ++i) {
        for (int part = 0; part < 2 && ok; ++part) {
            if (len - o < 4) { ok = 0; break; }
            uint32_t l = get_u32(b + o);
            o += 4;
            if (l > len - o || l > WST_QUOTA - bytes) { ok = 0; break; }
            if (!utf8_ok(b + o, l)) { ok = 0; break; }
            if (part == 0) { keys[i].p = b + o; keys[i].n = l; }
            bytes += l;
            o += l;
        }
    }
    if (ok && o != len) ok = 0;                     /* trailing bytes */
    if (ok && n > 1) {
        qsort(keys, n, sizeof *keys, key_cmp);
        for (uint32_t i = 1; i < n && ok; ++i)
            if (key_cmp(&keys[i - 1], &keys[i]) == 0) ok = 0;
    }
    free(keys);
    if (!ok) return -1;
    if (bytes_out != NULL) *bytes_out = bytes;
    return 0;
}

int wst_decode_check(const char *blob, size_t len) {
    return check(blob, len, NULL);
}

wst_db *wst_new(void) {
    return (wst_db *)calloc(1, sizeof(wst_db));
}

void wst_free(wst_db *db) {
    if (db == NULL) return;
    for (size_t i = 0; i < WST_MAX_ORIGINS; ++i) {
        free(db->o[i].origin);
        free(db->o[i].blob);
    }
    free(db);
}

static wst_origin *find(const wst_db *db, const char *origin) {
    for (size_t i = 0; i < WST_MAX_ORIGINS; ++i)
        if (db->o[i].origin != NULL && strcmp(db->o[i].origin, origin) == 0)
            return (wst_origin *)&db->o[i];
    return NULL;
}

int wst_encode(const wst_db *db, const char *origin, char **out, size_t *len) {
    if (db == NULL || origin == NULL || out == NULL || len == NULL) return -1;
    *out = NULL;
    *len = 0;
    const wst_origin *e = find(db, origin);
    size_t n = (e != NULL) ? e->len : 4;
    char *c = (char *)malloc(n);
    if (c == NULL) return -1;
    if (e != NULL) memcpy(c, e->blob, n);
    else memset(c, 0, 4);                           /* n = 0: an empty store */
    *out = c;
    *len = n;
    return 0;
}

int wst_replace(wst_db *db, const char *origin, const char *blob, size_t len) {
    if (db == NULL || origin == NULL) return -1;
    size_t olen = strlen(origin);
    if (olen == 0 || olen >= WST_ORIGIN_MAX) return -1;
    size_t bytes = 0;
    if (check(blob, len, &bytes) != 0) return -1;
    char *copy = (char *)malloc(len);
    if (copy == NULL) return -1;
    memcpy(copy, blob, len);

    wst_origin *e = find(db, origin);
    if (e == NULL) {
        /* A free slot, or evict the least recently used origin. */
        wst_origin *victim = &db->o[0];
        for (size_t i = 0; i < WST_MAX_ORIGINS; ++i) {
            if (db->o[i].origin == NULL) { victim = &db->o[i]; break; }
            if (db->o[i].used < victim->used) victim = &db->o[i];
        }
        char *oc = (char *)malloc(olen + 1);
        if (oc == NULL) { free(copy); return -1; }
        memcpy(oc, origin, olen + 1);
        free(victim->origin);
        free(victim->blob);
        memset(victim, 0, sizeof *victim);
        victim->origin = oc;
        e = victim;
    }
    free(e->blob);
    e->blob = copy;
    e->len = len;
    e->bytes = bytes;
    e->used = ++db->clock;
    return 0;
}

size_t wst_origin_bytes(const wst_db *db, const char *origin) {
    if (db == NULL || origin == NULL) return 0;
    const wst_origin *e = find(db, origin);
    return (e != NULL) ? e->bytes : 0;
}

int wst_foreach(const char *blob, size_t len,
                void (*fn)(void *ctx, const char *key, size_t klen,
                           const char *val, size_t vlen),
                void *ctx) {
    if (fn == NULL || check(blob, len, NULL) != 0) return -1;
    const unsigned char *b = (const unsigned char *)blob;
    uint32_t n = get_u32(b);
    size_t o = 4;
    for (uint32_t i = 0; i < n; ++i) {
        uint32_t kl = get_u32(b + o);
        const char *k = blob + o + 4;
        o += 4u + kl;
        uint32_t vl = get_u32(b + o);
        const char *v = blob + o + 4;
        o += 4u + vl;
        fn(ctx, k, kl, v, vl);
    }
    return 0;
}

static void put_u32(char *b, uint32_t v) {
    b[0] = (char)(v & 0xFF); b[1] = (char)((v >> 8) & 0xFF);
    b[2] = (char)((v >> 16) & 0xFF); b[3] = (char)((v >> 24) & 0xFF);
}

int wst_pack(const char *const *keys, const size_t *klens,
             const char *const *vals, const size_t *vlens, size_t n,
             char **out, size_t *len) {
    if (out == NULL || len == NULL) return -1;
    *out = NULL;
    *len = 0;
    if (n > WST_MAX_KEYS) return -1;
    if (n > 0 && (keys == NULL || klens == NULL || vals == NULL || vlens == NULL)) return -1;
    size_t total = 4;
    for (size_t i = 0; i < n; ++i) {
        if (klens[i] > WST_QUOTA || vlens[i] > WST_QUOTA) return -1;
        total += 8u + klens[i] + vlens[i];
        if (total > WST_QUOTA + 8u * (size_t)WST_MAX_KEYS + 4u) return -1;
    }
    char *b = (char *)malloc(total);
    if (b == NULL) return -1;
    put_u32(b, (uint32_t)n);
    size_t o = 4;
    for (size_t i = 0; i < n; ++i) {
        put_u32(b + o, (uint32_t)klens[i]); o += 4;
        if (klens[i] != 0) memcpy(b + o, keys[i], klens[i]);
        o += klens[i];
        put_u32(b + o, (uint32_t)vlens[i]); o += 4;
        if (vlens[i] != 0) memcpy(b + o, vals[i], vlens[i]);
        o += vlens[i];
    }
    /* The builder produces only what the parser accepts. */
    if (check(b, total, NULL) != 0) { free(b); return -1; }
    *out = b;
    *len = total;
    return 0;
}
