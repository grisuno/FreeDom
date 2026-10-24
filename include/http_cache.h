#ifndef FREEDOM_HTTP_CACHE_H
#define FREEDOM_HTTP_CACHE_H

#include <stddef.h>
#include <stdint.h>
#include <time.h>

#include "local_store.h"

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * http_cache -- sealed HTTP cache + permanent-redirect memory (spec/http_cache.md). Pure
 * freshness decisions, plus a directory store whose every file is a pq_seal blob named by a
 * keyed hash. Trusted side only; never linked into the confined worker.
 */

#define HC_VAL_MAX     256u              /* one validator / directive value */
#define HC_URL_MAX     2048u
#define HC_TYPE_MAX    128u
#define HC_MAX_ENTRY   ((size_t)(8u * 1024u * 1024u))
#define HC_MAX_TOTAL   ((size_t)(128u * 1024u * 1024u))
#define HC_REDIRECT_TTL ((time_t)(30 * 24 * 3600))
#define HC_HEURISTIC_CAP ((long)(24 * 3600))

typedef enum hc_status {
    HC_OK = 0,
    HC_MISS,          /* no usable entry (absent, expired, corrupt: a corrupt one is removed) */
    HC_ERR_ARG,
    HC_ERR_IO,
    HC_ERR_CRYPTO,
    HC_ERR_OOM,
    HC_ERR_TOO_LARGE
} hc_status;

typedef enum hc_class {
    HC_UNUSABLE = 0,  /* stale with no validator: fetch again */
    HC_FRESH,         /* serve without the network */
    HC_REVALIDATE     /* send a conditional GET */
} hc_class;

typedef struct hc_meta {
    char   final_url[HC_URL_MAX];
    char   content_type[HC_TYPE_MAX];
    char   etag[HC_VAL_MAX];
    char   last_modified[HC_VAL_MAX];
    char   cache_control[HC_VAL_MAX];
    char   expires[HC_VAL_MAX];
    char   date[HC_VAL_MAX];
    time_t stored;    /* when this response was received */
} hc_meta;

/* RFC 9110 IMF-fixdate ("Sun, 06 Nov 1994 08:49:37 GMT") -> UTC epoch, or -1. */
time_t hc_parse_http_date(const char *s);

/* True when a response may be stored: 200, no `no-store`, body within HC_MAX_ENTRY, and
 * something to reuse it by (validator, max-age or Expires). */
int hc_storable(long http_code, const hc_meta *m, size_t body_len);

/* Freshness lifetime in seconds (>= 0), per the spec's order of rules. */
long hc_lifetime(const hc_meta *m);

hc_class hc_classify(const hc_meta *m, time_t now);

typedef struct hc_store hc_store;

/* Opens (creating, 0700) the cache directory. `wrap` is the profile key. Regenerates the
 * ML-KEM keys and empties the directory when the sealed key cannot be opened. */
hc_status hc_open(hc_store **out, const char *dir, const uint8_t wrap[LS_KEY_LEN]);
void hc_close(hc_store *s);

hc_status hc_get(hc_store *s, const char *partition, const char *url, hc_meta *meta,
                 uint8_t **body, size_t *body_len);
hc_status hc_put(hc_store *s, const char *partition, const char *url, const hc_meta *meta,
                 const uint8_t *body, size_t body_len);
void hc_body_free(uint8_t *body, size_t len);

hc_status hc_redirect_put(hc_store *s, const char *from, const char *to, time_t now);
hc_status hc_redirect_get(hc_store *s, const char *from, time_t now, char *out, size_t cap);

/* Removes every entry. */
void hc_clear(hc_store *s);

#endif /* FREEDOM_HTTP_CACHE_H */
