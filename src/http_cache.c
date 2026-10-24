/*
 * http_cache -- see spec/http_cache.md. Pure freshness rules + a directory of pq_seal blobs
 * named by keyed hashes. The first three entry types of the spec's privacy section live here:
 * sealed contents, anonymized names, per-site partitions.
 */

#define _POSIX_C_SOURCE 200809L

#include "http_cache.h"

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>

#include <pthread.h>

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>

#include "disk_store.h"
#include "pq_seal.h"

#define HC_KEY_FILE   "pq.key"
#define HC_MAGIC      "FHC1\n"
#define HC_NAME_HEX   64u
#define HC_EVICT_EVERY 16u
#define HC_MAX_AGE_CAP 31536000L          /* a year: max-age beyond this is clamped */

/* ---- pure rules ---- */

static int days_in_month(int y, int m) {
    static const int dm[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) return 29;
    return dm[m - 1];
}

/* Days since 1970-01-01 of a proleptic Gregorian date (Howard Hinnant's algorithm). */
static long days_from_civil(int y, int m, int d) {
    y -= m <= 2;
    long era = (y >= 0 ? y : y - 399) / 400;
    unsigned yoe = (unsigned)(y - era * 400);
    unsigned doy = (unsigned)((153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1);
    unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + (long)doe - 719468;
}

time_t hc_parse_http_date(const char *s) {
    if (s == NULL) return (time_t)-1;
    const char *c = strchr(s, ',');
    if (c == NULL) return (time_t)-1;
    int d = 0, y = 0, hh = 0, mm = 0, ss = 0;
    char mon[4] = "";
    if (sscanf(c + 1, " %d %3s %d %d:%d:%d GMT", &d, mon, &y, &hh, &mm, &ss) != 6)
        return (time_t)-1;
    static const char *const months[12] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
    int m = 0;
    for (int i = 0; i < 12; ++i) if (strcasecmp(mon, months[i]) == 0) m = i + 1;
    if (m == 0 || y < 1970 || y > 9999 || d < 1 || d > days_in_month(y, m)
        || hh < 0 || hh > 23 || mm < 0 || mm > 59 || ss < 0 || ss > 60)
        return (time_t)-1;
    return (time_t)(days_from_civil(y, m, d) * 86400L + hh * 3600L + mm * 60L + ss);
}

/* True when the Cache-Control list has directive `name` (whole token, case-insensitive). */
static int cc_find(const char *cc, const char *name, const char **val) {
    size_t nl = strlen(name);
    const char *p = cc;
    while (*p != '\0') {
        while (*p == ',' || *p == ' ' || *p == '\t') ++p;
        const char *e = p;
        while (*e != '\0' && *e != ',' && *e != '=' && *e != ' ' && *e != '\t') ++e;
        if ((size_t)(e - p) == nl && strncasecmp(p, name, nl) == 0) {
            if (val != NULL) *val = (*e == '=') ? e + 1 : NULL;
            return 1;
        }
        while (*e != '\0' && *e != ',') ++e;
        p = e;
    }
    return 0;
}

/* max-age=N: digits only; anything else is "absent" (RFC 9111 4.2.1 treats it as stale). */
static int cc_max_age(const char *cc, long *out) {
    const char *v = NULL;
    if (!cc_find(cc, "max-age", &v) || v == NULL) return 0;
    if (*v == '"') ++v;
    if (!isdigit((unsigned char)*v)) return 0;
    long n = 0;
    while (isdigit((unsigned char)*v)) {
        n = n * 10 + (*v - '0');
        if (n > HC_MAX_AGE_CAP) { n = HC_MAX_AGE_CAP; break; }
        ++v;
    }
    *out = n;
    return 1;
}

int hc_storable(long http_code, const hc_meta *m, size_t body_len) {
    if (m == NULL || http_code != 200 || body_len > HC_MAX_ENTRY) return 0;
    if (cc_find(m->cache_control, "no-store", NULL)) return 0;
    long ma = 0;
    return m->etag[0] != '\0' || m->last_modified[0] != '\0' || m->expires[0] != '\0'
           || (cc_max_age(m->cache_control, &ma) && ma > 0);
}

long hc_lifetime(const hc_meta *m) {
    if (m == NULL) return 0;
    if (cc_find(m->cache_control, "no-cache", NULL)) return 0;
    long ma = 0;
    if (cc_max_age(m->cache_control, &ma)) return ma;
    time_t date = hc_parse_http_date(m->date);
    if (date == (time_t)-1) date = m->stored;
    time_t exp = hc_parse_http_date(m->expires);
    if (m->expires[0] != '\0') {                 /* an invalid Expires ("0", "-1") means stale */
        if (exp == (time_t)-1 || exp <= date) return 0;
        long d = (long)(exp - date);
        return d > HC_MAX_AGE_CAP ? HC_MAX_AGE_CAP : d;
    }
    time_t lm = hc_parse_http_date(m->last_modified);
    if (lm != (time_t)-1 && date > lm) {
        long h = (long)((date - lm) / 10);
        return h > HC_HEURISTIC_CAP ? HC_HEURISTIC_CAP : h;
    }
    return 0;
}

hc_class hc_classify(const hc_meta *m, time_t now) {
    if (m == NULL) return HC_UNUSABLE;
    long age = (long)(now - m->stored);
    if (age < 0) age = 0;                       /* the clock went back: never a negative age */
    if (age < hc_lifetime(m)) return HC_FRESH;
    return (m->etag[0] != '\0' || m->last_modified[0] != '\0') ? HC_REVALIDATE : HC_UNUSABLE;
}

/* ---- store ---- */

struct hc_store {
    char       dir[1024];
    uint8_t    wrap[LS_KEY_LEN];
    uint8_t    name_key[LS_KEY_LEN];
    pqs_keys  *keys;
    unsigned   puts;
    pthread_mutex_t lock;   /* the store is shared by every fetching thread */
};

static void hex_of(const uint8_t *b, size_t n, char *out) {
    static const char H[] = "0123456789abcdef";
    for (size_t i = 0; i < n; ++i) { out[2 * i] = H[b[i] >> 4]; out[2 * i + 1] = H[b[i] & 15]; }
    out[2 * n] = '\0';
}

/* File name of an entry: hex(HMAC-SHA256(name_key, kind || 0 || partition || 0 || url)). */
static int entry_path(const hc_store *s, char kind, const char *partition, const char *url,
                      char *path, size_t cap) {
    size_t pl = strlen(partition), ul = strlen(url);
    if (pl > HC_URL_MAX || ul > HC_URL_MAX) return -1;
    uint8_t msg[2 + HC_URL_MAX + 1 + HC_URL_MAX];
    size_t n = 0;
    msg[n++] = (uint8_t)kind; msg[n++] = 0;
    memcpy(msg + n, partition, pl); n += pl; msg[n++] = 0;
    memcpy(msg + n, url, ul); n += ul;
    uint8_t mac[EVP_MAX_MD_SIZE];
    unsigned ml = 0;
    if (HMAC(EVP_sha256(), s->name_key, LS_KEY_LEN, msg, n, mac, &ml) == NULL || ml != 32) return -1;
    char hex[HC_NAME_HEX + 1];
    hex_of(mac, 32, hex);
    int r = snprintf(path, cap, "%s/%s", s->dir, hex);
    return (r > 0 && (size_t)r < cap) ? 0 : -1;
}

static void remove_entries(const char *dir) {
    DIR *d = opendir(dir);
    if (d == NULL) return;
    struct dirent *e;
    while ((e = readdir(d)) != NULL) {
        if (e->d_name[0] == '.' || strcmp(e->d_name, HC_KEY_FILE) == 0) continue;
        char p[1280];
        if (snprintf(p, sizeof p, "%s/%s", dir, e->d_name) < (int)sizeof p) (void)unlink(p);
    }
    closedir(d);
}

static int write_atomic(const char *path, const uint8_t *data, size_t len) {
    char tmp[1300];
    if (snprintf(tmp, sizeof tmp, "%s.tmp", path) >= (int)sizeof tmp) return -1;
    int fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0600);
    if (fd < 0) return -1;
    size_t off = 0;
    while (off < len) {
        ssize_t w = write(fd, data + off, len - off);
        if (w < 0) { if (errno == EINTR) continue; close(fd); unlink(tmp); return -1; }
        off += (size_t)w;
    }
    if (close(fd) != 0) { unlink(tmp); return -1; }
    if (rename(tmp, path) != 0) { unlink(tmp); return -1; }
    return 0;
}

static uint8_t *read_file(const char *path, size_t max, size_t *len) {
    int fd = open(path, O_RDONLY | O_CLOEXEC);
    if (fd < 0) return NULL;
    struct stat st;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode) || st.st_size <= 0 || (size_t)st.st_size > max) {
        close(fd); return NULL;
    }
    size_t n = (size_t)st.st_size;
    uint8_t *buf = (uint8_t *)malloc(n);
    if (buf == NULL) { close(fd); return NULL; }
    size_t off = 0;
    while (off < n) {
        ssize_t r = read(fd, buf + off, n - off);
        if (r < 0 && errno == EINTR) continue;
        if (r <= 0) { free(buf); close(fd); return NULL; }
        off += (size_t)r;
    }
    close(fd);
    *len = n;
    return buf;
}

hc_status hc_open(hc_store **out, const char *dir, const uint8_t wrap[LS_KEY_LEN]) {
    if (out == NULL || dir == NULL || wrap == NULL) return HC_ERR_ARG;
    *out = NULL;
    if (dir[0] == '\0' || strlen(dir) >= sizeof ((hc_store *)0)->dir - 64) return HC_ERR_ARG;
    if (mkdir(dir, 0700) != 0 && errno != EEXIST) return HC_ERR_IO;
    hc_store *s = (hc_store *)calloc(1, sizeof *s);
    if (s == NULL) return HC_ERR_OOM;
    memcpy(s->dir, dir, strlen(dir) + 1);
    memcpy(s->wrap, wrap, LS_KEY_LEN);
    pthread_mutex_init(&s->lock, NULL);
    /* The name key is its own derivation, so the file names never expose the wrap key itself. */
    static const char label[] = "freedom-hc-name-v1";
    EVP_MD_CTX *md = EVP_MD_CTX_new();
    unsigned dl = 0;
    int ok = md != NULL && EVP_DigestInit_ex(md, EVP_sha256(), NULL) == 1
          && EVP_DigestUpdate(md, label, sizeof label - 1) == 1
          && EVP_DigestUpdate(md, wrap, LS_KEY_LEN) == 1
          && EVP_DigestFinal_ex(md, s->name_key, &dl) == 1;
    EVP_MD_CTX_free(md);
    if (!ok) { free(s); return HC_ERR_CRYPTO; }

    char kp[1100];
    snprintf(kp, sizeof kp, "%s/%s", dir, HC_KEY_FILE);
    uint8_t *der = NULL;
    size_t dlen = 0;
    if (ds_read(kp, wrap, &der, &dlen) == DS_OK) {
        pqs_status ps = pqs_import(der, dlen, &s->keys);
        ds_free(der, dlen);
        if (ps != PQS_OK) s->keys = NULL;
    }
    if (s->keys == NULL) {
        /* No usable key (first run, or the profile key changed): it is only a cache, so
         * start clean instead of keeping blobs nobody can open. */
        remove_entries(dir);
        if (pqs_generate(&s->keys) != PQS_OK) { free(s); return HC_ERR_CRYPTO; }
        uint8_t *nd = NULL;
        size_t nl = 0;
        if (pqs_export(s->keys, &nd, &nl) != PQS_OK
            || ds_write(kp, wrap, LS_AEAD_CHACHA20_POLY1305, nd, nl) != DS_OK) {
            pqs_buf_free(nd, nl);
            pqs_free(s->keys); free(s);
            return HC_ERR_IO;
        }
        pqs_buf_free(nd, nl);
    }
    *out = s;
    return HC_OK;
}

void hc_close(hc_store *s) {
    if (s == NULL) return;
    pqs_free(s->keys);
    pthread_mutex_destroy(&s->lock);
    OPENSSL_cleanse(s, sizeof *s);
    free(s);
}

void hc_body_free(uint8_t *body, size_t len) {
    if (body == NULL) return;
    OPENSSL_cleanse(body, len);
    free(body);
}

static int has_nl(const char *s) { return strpbrk(s, "\r\n") != NULL; }

static int meta_ok(const hc_meta *m) {
    return !has_nl(m->final_url) && !has_nl(m->content_type) && !has_nl(m->etag)
        && !has_nl(m->last_modified) && !has_nl(m->cache_control) && !has_nl(m->expires)
        && !has_nl(m->date) && m->final_url[0] != '\0';
}

/* Serializes meta + body, seals it, writes it atomically. */
static hc_status store_entry(hc_store *s, const char *path, const hc_meta *m,
                             const uint8_t *body, size_t body_len) {
    char head[HC_URL_MAX + HC_TYPE_MAX + 5 * HC_VAL_MAX + 128];
    int hn = snprintf(head, sizeof head, HC_MAGIC "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%lld\n\n",
                      m->final_url, m->content_type, m->etag, m->last_modified,
                      m->cache_control, m->expires, m->date, (long long)m->stored);
    if (hn <= 0 || (size_t)hn >= sizeof head) return HC_ERR_ARG;
    if (body_len > HC_MAX_ENTRY) return HC_ERR_TOO_LARGE;
    size_t total = (size_t)hn + body_len;
    uint8_t *pt = (uint8_t *)malloc(total);
    if (pt == NULL) return HC_ERR_OOM;
    memcpy(pt, head, (size_t)hn);
    if (body_len != 0) memcpy(pt + hn, body, body_len);
    uint8_t *blob = NULL;
    size_t bl = 0;
    pqs_status ps = pqs_seal(s->keys, s->wrap, pt, total, &blob, &bl);
    OPENSSL_cleanse(pt, total);
    free(pt);
    if (ps != PQS_OK) return ps == PQS_ERR_OOM ? HC_ERR_OOM : HC_ERR_CRYPTO;
    int wr = write_atomic(path, blob, bl);
    pqs_buf_free(blob, bl);
    return wr == 0 ? HC_OK : HC_ERR_IO;
}

/* Reads and opens an entry; a file that does not open is removed (a miss, never data). */
static hc_status load_entry(hc_store *s, const char *path, hc_meta *m, uint8_t **body,
                            size_t *body_len) {
    size_t fl = 0;
    uint8_t *file = read_file(path, HC_MAX_ENTRY + 16384u, &fl);
    if (file == NULL) return HC_MISS;
    uint8_t *pt = NULL;
    size_t pl = 0;
    pqs_status ps = pqs_open(s->keys, s->wrap, file, fl, &pt, &pl);
    free(file);
    if (ps != PQS_OK) { (void)unlink(path); return HC_MISS; }

    hc_status rc = HC_MISS;
    size_t mg = sizeof HC_MAGIC - 1;
    if (pl < mg || memcmp(pt, HC_MAGIC, mg) != 0) goto bad;
    {
        const char *p = (const char *)pt + mg, *end = (const char *)pt + pl;
        char *dst[7] = { m->final_url, m->content_type, m->etag, m->last_modified,
                         m->cache_control, m->expires, m->date };
        size_t cap[7] = { HC_URL_MAX, HC_TYPE_MAX, HC_VAL_MAX, HC_VAL_MAX, HC_VAL_MAX,
                          HC_VAL_MAX, HC_VAL_MAX };
        memset(m, 0, sizeof *m);
        for (int i = 0; i < 7; ++i) {
            const char *nl = memchr(p, '\n', (size_t)(end - p));
            if (nl == NULL || (size_t)(nl - p) >= cap[i]) goto bad;
            memcpy(dst[i], p, (size_t)(nl - p));
            p = nl + 1;
        }
        const char *nl = memchr(p, '\n', (size_t)(end - p));
        if (nl == NULL || nl - p > 20) goto bad;
        char num[24];
        memcpy(num, p, (size_t)(nl - p));
        num[nl - p] = '\0';
        char *ep = NULL;
        long long st = strtoll(num, &ep, 10);
        if (ep == num || *ep != '\0') goto bad;
        m->stored = (time_t)st;
        p = nl + 1;
        if (p >= end || *p != '\n') goto bad;
        ++p;
        size_t bl = (size_t)(end - p);
        if (body != NULL) {
            uint8_t *b = (uint8_t *)malloc(bl + 1);
            if (b == NULL) { rc = HC_ERR_OOM; goto done; }
            if (bl != 0) memcpy(b, p, bl);
            b[bl] = '\0';
            *body = b;
            if (body_len != NULL) *body_len = bl;
        }
        rc = HC_OK;
        goto done;
    }
bad:
    (void)unlink(path);
done:
    pqs_buf_free(pt, pl);
    return rc;
}

static hc_status get_locked(hc_store *s, const char *partition, const char *url, hc_meta *meta,
                            uint8_t **body, size_t *body_len) {
    if (s == NULL || partition == NULL || url == NULL || meta == NULL || body == NULL
        || body_len == NULL) return HC_ERR_ARG;
    *body = NULL; *body_len = 0;
    char path[1300];
    if (entry_path(s, 'c', partition, url, path, sizeof path) != 0) return HC_ERR_ARG;
    return load_entry(s, path, meta, body, body_len);
}

/* Drops the oldest files until the directory fits HC_MAX_TOTAL (90 % target). */
static void evict(hc_store *s) {
    typedef struct { time_t mt; size_t sz; char name[80]; } ent;
    size_t cap = 256, n = 0, total = 0;
    ent *v = (ent *)malloc(cap * sizeof *v);
    if (v == NULL) return;
    DIR *d = opendir(s->dir);
    struct dirent *e;
    while (d != NULL && (e = readdir(d)) != NULL) {
        if (e->d_name[0] == '.' || strcmp(e->d_name, HC_KEY_FILE) == 0 || strlen(e->d_name) >= 80) continue;
        char p[1300];
        struct stat st;
        if (snprintf(p, sizeof p, "%s/%s", s->dir, e->d_name) >= (int)sizeof p || stat(p, &st) != 0
            || !S_ISREG(st.st_mode)) continue;
        if (n == cap) {
            if (cap > ((size_t)-1) / 2 / sizeof *v) break;
            ent *nv = (ent *)realloc(v, cap * 2 * sizeof *v);
            if (nv == NULL) break;
            v = nv; cap *= 2;
        }
        v[n].mt = st.st_mtime; v[n].sz = (size_t)st.st_size;
        memcpy(v[n].name, e->d_name, strlen(e->d_name) + 1);
        total += v[n].sz; ++n;
    }
    if (d != NULL) closedir(d);
    if (total > HC_MAX_TOTAL) {
        size_t target = HC_MAX_TOTAL / 10 * 9;
        while (total > target && n > 0) {
            size_t oldest = 0;
            for (size_t i = 1; i < n; ++i) if (v[i].mt < v[oldest].mt) oldest = i;
            char p[1300];
            if (snprintf(p, sizeof p, "%s/%s", s->dir, v[oldest].name) < (int)sizeof p) (void)unlink(p);
            total -= v[oldest].sz;
            v[oldest] = v[--n];
        }
    }
    free(v);
}

static hc_status put_locked(hc_store *s, const char *partition, const char *url, const hc_meta *meta,
                            const uint8_t *body, size_t body_len) {
    if (s == NULL || partition == NULL || url == NULL || meta == NULL || (body == NULL && body_len != 0))
        return HC_ERR_ARG;
    if (!meta_ok(meta) || has_nl(partition) || has_nl(url)) return HC_ERR_ARG;
    char path[1300];
    if (entry_path(s, 'c', partition, url, path, sizeof path) != 0) return HC_ERR_ARG;
    hc_status rc = store_entry(s, path, meta, body, body_len);
    if (rc == HC_OK && (++s->puts % HC_EVICT_EVERY) == 0) evict(s);
    return rc;
}

static hc_status redirect_put_locked(hc_store *s, const char *from, const char *to, time_t now) {
    if (s == NULL || from == NULL || to == NULL) return HC_ERR_ARG;
    if (strncmp(to, "https://", 8) != 0 || strcmp(from, to) == 0 || has_nl(from) || has_nl(to)
        || strlen(to) >= HC_URL_MAX) return HC_ERR_ARG;
    hc_meta m;
    memset(&m, 0, sizeof m);
    memcpy(m.final_url, to, strlen(to) + 1);
    m.stored = now;
    char path[1300];
    if (entry_path(s, 'r', "", from, path, sizeof path) != 0) return HC_ERR_ARG;
    return store_entry(s, path, &m, NULL, 0);
}

static hc_status redirect_get_locked(hc_store *s, const char *from, time_t now, char *out, size_t cap) {
    if (s == NULL || from == NULL || out == NULL || cap == 0) return HC_ERR_ARG;
    char path[1300];
    if (entry_path(s, 'r', "", from, path, sizeof path) != 0) return HC_ERR_ARG;
    hc_meta m;
    hc_status rc = load_entry(s, path, &m, NULL, NULL);
    if (rc != HC_OK) return rc;
    if (now < m.stored || now - m.stored > HC_REDIRECT_TTL) { (void)unlink(path); return HC_MISS; }
    size_t l = strlen(m.final_url);
    if (l >= cap || strncmp(m.final_url, "https://", 8) != 0) return HC_MISS;
    memcpy(out, m.final_url, l + 1);
    return HC_OK;
}

void hc_clear(hc_store *s) {
    if (s == NULL) return;
    pthread_mutex_lock(&s->lock);
    remove_entries(s->dir);
    pthread_mutex_unlock(&s->lock);
}

hc_status hc_get(hc_store *s, const char *partition, const char *url, hc_meta *meta,
                 uint8_t **body, size_t *body_len) {
    if (s == NULL) return HC_ERR_ARG;
    pthread_mutex_lock(&s->lock);
    hc_status r = get_locked(s, partition, url, meta, body, body_len);
    pthread_mutex_unlock(&s->lock);
    return r;
}

hc_status hc_put(hc_store *s, const char *partition, const char *url, const hc_meta *meta,
                 const uint8_t *body, size_t body_len) {
    if (s == NULL) return HC_ERR_ARG;
    pthread_mutex_lock(&s->lock);
    hc_status r = put_locked(s, partition, url, meta, body, body_len);
    pthread_mutex_unlock(&s->lock);
    return r;
}

hc_status hc_redirect_put(hc_store *s, const char *from, const char *to, time_t now) {
    if (s == NULL) return HC_ERR_ARG;
    pthread_mutex_lock(&s->lock);
    hc_status r = redirect_put_locked(s, from, to, now);
    pthread_mutex_unlock(&s->lock);
    return r;
}

hc_status hc_redirect_get(hc_store *s, const char *from, time_t now, char *out, size_t cap) {
    if (s == NULL) return HC_ERR_ARG;
    pthread_mutex_lock(&s->lock);
    hc_status r = redirect_get_locked(s, from, now, out, cap);
    pthread_mutex_unlock(&s->lock);
    return r;
}
