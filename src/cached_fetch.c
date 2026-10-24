/*
 * cached_fetch -- HTTP cache in front of the gated fetcher (spec/http_cache.md). A hit changes
 * WHEN bytes move, never WHAT is fetched: a miss or a revalidation goes through the same
 * fetcher, and so the same policy, as an uncached request.
 */

#define _POSIX_C_SOURCE 200809L

#include "cached_fetch.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static hc_store *g_store;

/* FREEDOM_TRACE_FETCH=1: one line per cache decision (hit = no network). */
static void trace(const char *what, const char *url) {
    if (getenv("FREEDOM_TRACE_FETCH") != NULL) fprintf(stderr, "cache[%s] %s\n", what, url);
}

void cf_set_store(hc_store *store) { g_store = store; }
hc_store *cf_store(void) { return g_store; }

/* GET over https with no credentials and no byte range: the only requests worth sharing. */
static int cacheable_request(const sf_config *cfg, const char *url) {
    if (strncmp(url, "https://", 8) != 0 || strlen(url) >= HC_URL_MAX) return 0;
    if (cfg->username != NULL && cfg->username[0] != '\0') return 0;
    if (cfg->range_start >= 0) return 0;
    return !cfg->allow_overlay_http;
}

static void copy_val(char *dst, size_t cap, const char *src) {
    size_t n = strlen(src);
    if (n >= cap) n = 0;                         /* too long: dropped, never truncated */
    memcpy(dst, src, n);
    dst[n] = '\0';
}

static void meta_from_response(hc_meta *m, const sf_response *r, const char *url, time_t now) {
    memset(m, 0, sizeof *m);
    copy_val(m->final_url, sizeof m->final_url, (r->final_url != NULL) ? r->final_url : url);
    if (r->content_type != NULL) copy_val(m->content_type, sizeof m->content_type, r->content_type);
    copy_val(m->etag, sizeof m->etag, r->etag);
    copy_val(m->last_modified, sizeof m->last_modified, r->last_modified);
    copy_val(m->cache_control, sizeof m->cache_control, r->cache_control);
    copy_val(m->expires, sizeof m->expires, r->expires);
    copy_val(m->date, sizeof m->date, r->date);
    m->stored = now;
}

/* Rebuilds a 200 response from a stored entry. Takes ownership of `body`. */
static int response_from_cache(sf_response *out, const hc_meta *m, uint8_t *body, size_t len) {
    memset(out, 0, sizeof *out);
    out->content_type = (m->content_type[0] != '\0') ? strdup(m->content_type) : NULL;
    out->final_url = strdup(m->final_url);
    out->tls_version = strdup("cache");
    if ((m->content_type[0] != '\0' && out->content_type == NULL) || out->final_url == NULL
        || out->tls_version == NULL) {
        free(out->content_type); free(out->final_url); free(out->tls_version);
        memset(out, 0, sizeof *out);
        free(body);
        return -1;
    }
    out->status = SF_OK;
    out->http_code = 200;
    out->body = body;
    out->body_len = len;
    copy_val(out->etag, sizeof out->etag, m->etag);
    copy_val(out->last_modified, sizeof out->last_modified, m->last_modified);
    copy_val(out->cache_control, sizeof out->cache_control, m->cache_control);
    copy_val(out->expires, sizeof out->expires, m->expires);
    copy_val(out->date, sizeof out->date, m->date);
    return 0;
}

static void remember(hc_store *store, const char *partition, const char *url,
                     const sf_response *r, time_t now) {
    hc_meta m;
    meta_from_response(&m, r, url, now);
    if (!hc_storable(r->http_code, &m, r->body_len)) return;
    (void)hc_put(store, partition, url, &m, r->body, r->body_len);
}

sf_status cf_get_with(hc_store *store, cf_fetch_fn fetch, const char *partition, const char *url,
                      sf_config *cfg, sf_response *out, int *downgraded, int allowlisted,
                      time_t now) {
    if (fetch == NULL || url == NULL || cfg == NULL || out == NULL) return SF_ERR_INTERNAL;
    if (store == NULL || partition == NULL || partition[0] == '\0' || !cacheable_request(cfg, url))
        return fetch(url, cfg, out, downgraded, allowlisted);

    hc_meta m;
    uint8_t *body = NULL;
    size_t blen = 0;
    if (hc_get(store, partition, url, &m, &body, &blen) == HC_OK) {
        hc_class cls = hc_classify(&m, now);
        if (cls == HC_FRESH) {
            trace("hit", url);
            if (response_from_cache(out, &m, body, blen) == 0) return SF_OK;
            return fetch(url, cfg, out, downgraded, allowlisted);
        }
        if (cls == HC_REVALIDATE) {
            /* Validate against the FINAL url that produced the body: a validator is a
             * fingerprint of that resource and must not travel to another origin. */
            sf_config cond = *cfg;
            cond.if_none_match = (m.etag[0] != '\0') ? m.etag : NULL;
            cond.if_modified_since = (m.last_modified[0] != '\0') ? m.last_modified : NULL;
            sf_status st = fetch(m.final_url, &cond, out, downgraded, allowlisted);
            trace((st == SF_OK && out->http_code == 304) ? "revalidated" : "changed", url);
            if (st == SF_OK && out->http_code == 304) {
                m.stored = now;
                if (out->cache_control[0] != '\0') copy_val(m.cache_control, sizeof m.cache_control, out->cache_control);
                if (out->expires[0] != '\0') copy_val(m.expires, sizeof m.expires, out->expires);
                if (out->date[0] != '\0') copy_val(m.date, sizeof m.date, out->date);
                if (out->etag[0] != '\0') copy_val(m.etag, sizeof m.etag, out->etag);
                (void)hc_put(store, partition, url, &m, body, blen);
                sf_response_free(out);
                if (response_from_cache(out, &m, body, blen) == 0) return SF_OK;
                return fetch(url, cfg, out, downgraded, allowlisted);
            }
            hc_body_free(body, blen);
            if (st == SF_OK) remember(store, partition, url, out, now);
            return st;
        }
        hc_body_free(body, blen);                /* stale, no validator: ask again */
    }
    trace("miss", url);
    sf_status st = fetch(url, cfg, out, downgraded, allowlisted);
    if (st == SF_OK) remember(store, partition, url, out, now);
    return st;
}

sf_status cf_get(const char *partition, const char *url, sf_config *cfg, sf_response *out,
                 int *downgraded, int allowlisted) {
    return cf_get_with(g_store, sf_get_follow_navigable, partition, url, cfg, out, downgraded,
                       allowlisted, time(NULL));
}

/* Redirect memory: the backing the secure fetcher consults on a RAM miss. */
static int redirect_load(void *ctx, const char *from, time_t now, char *out, size_t cap) {
    return hc_redirect_get((hc_store *)ctx, from, now, out, cap) == HC_OK;
}

static void redirect_save(void *ctx, const char *from, const char *to, time_t now) {
    (void)hc_redirect_put((hc_store *)ctx, from, to, now);
}

void cf_attach_redirect_memory(hc_store *store) {
    if (store == NULL) sf_rcache_set_backing(NULL, NULL, NULL);
    else sf_rcache_set_backing(redirect_load, redirect_save, store);
}
