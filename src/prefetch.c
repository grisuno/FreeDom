/*
 * prefetch — trusted-side lookahead scanner + parallel subresource pool.
 *
 * The scanner reads hostile HTML bytes without Lexbor on purpose: it is an
 * optimization HINT extractor, not a parser of record. Correctness never
 * depends on it -- a missed reference just falls back to the serial fetch, and
 * every emitted reference is fetched through the same policy-gated callback
 * the serial path uses. Fail-closed on anything ambiguous: emitting nothing is
 * always safe.
 */

#define _POSIX_C_SOURCE 200809L

#include "prefetch.h"

#include <stdlib.h>
#include <string.h>

/* Longest raw reference the scanner keeps; matches URL_MAX_LEN (url.h) so a
 * ref the fetch path would reject on length is never even queued. */
#define PF_MAX_URL 8192

static int is_ws(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f';
}

static int is_name_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '-';
}

static int lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

/* Case-insensitive: [p,end) starts with kw. */
static int ci_starts(const char *p, const char *end, const char *kw) {
    for (size_t i = 0; kw[i] != '\0'; ++i) {
        if (p + i >= end || lower((unsigned char)p[i]) != (unsigned char)kw[i])
            return 0;
    }
    return 1;
}

/* First case-insensitive occurrence of kw in [p,end), or NULL. */
static const char *ci_find(const char *p, const char *end, const char *kw) {
    size_t n = strlen(kw);
    while (p + n <= end) {
        if (ci_starts(p, end, kw)) return p;
        p++;
    }
    return NULL;
}

static int ci_eq_span(const char *s, size_t n, const char *kw) {
    if (strlen(kw) != n) return 0;
    for (size_t i = 0; i < n; ++i)
        if (lower((unsigned char)s[i]) != (unsigned char)kw[i]) return 0;
    return 1;
}

typedef struct attr_span {
    const char *name; size_t nlen;
    const char *val;  size_t vlen;   /* val NULL when the attribute is bare */
} attr_span;

/* Reads one attribute at *pp inside a tag. Returns 1 and advances past it, or
 * 0 when the tag ends (*pp is then just past '>' or at end). Never stalls: the
 * cursor strictly advances on every path. */
static int next_attr(const char **pp, const char *end, attr_span *a) {
    const char *p = *pp;
    while (p < end && (is_ws(*p) || *p == '/')) p++;
    if (p >= end) { *pp = p; return 0; }
    if (*p == '>') { *pp = p + 1; return 0; }

    a->name = p;
    while (p < end && *p != '=' && *p != '>' && *p != '/' && !is_ws(*p)) p++;
    a->nlen = (size_t)(p - a->name);
    if (a->nlen == 0) { *pp = p + 1; a->val = NULL; a->vlen = 0; return 1; }

    while (p < end && is_ws(*p)) p++;
    if (p < end && *p == '=') {
        p++;
        while (p < end && is_ws(*p)) p++;
        if (p < end && (*p == '"' || *p == '\'')) {
            char q = *p++;
            a->val = p;
            while (p < end && *p != q) p++;
            a->vlen = (size_t)(p - a->val);
            if (p < end) p++;
        } else {
            a->val = p;
            while (p < end && !is_ws(*p) && *p != '>') p++;
            a->vlen = (size_t)(p - a->val);
        }
    } else {
        a->val = NULL;
        a->vlen = 0;
    }
    *pp = p;
    return 1;
}

/* rel is a whitespace-separated token list; only the exact "stylesheet" token
 * qualifies (fail closed: alternate/preload/icon are never prefetched). */
static int rel_has_stylesheet(const char *v, size_t n) {
    size_t i = 0;
    while (i < n) {
        while (i < n && is_ws(v[i])) i++;
        size_t s = i;
        while (i < n && !is_ws(v[i])) i++;
        if (i > s && ci_eq_span(v + s, i - s, "stylesheet")) return 1;
    }
    return 0;
}

static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen) {
    if (out->count >= PF_MAX_REFS || val == NULL || vlen == 0 || vlen >= PF_MAX_URL)
        return;
    char *u = (char *)malloc(vlen + 1);
    if (u == NULL) return;
    memcpy(u, val, vlen);
    u[vlen] = '\0';
    out->refs[out->count].kind = kind;
    out->refs[out->count].url = u;
    out->count++;
}

int pf_scan(const char *html, size_t len, pf_list *out) {
    if (out != NULL) memset(out, 0, sizeof *out);
    if (html == NULL || out == NULL) return -1;

    const char *p = html, *end = html + len;
    while (p < end) {
        const char *lt = memchr(p, '<', (size_t)(end - p));
        if (lt == NULL) break;
        p = lt;

        if (ci_starts(p, end, "<!--")) {
            const char *close = ci_find(p + 4, end, "-->");
            p = (close != NULL) ? close + 3 : end;
            continue;
        }

        if (ci_starts(p, end, "<script") &&
            !(p + 7 < end && is_name_char(p[7]))) {
            const char *cur = p + 7;
            attr_span a;
            const char *src = NULL; size_t srclen = 0;
            while (next_attr(&cur, end, &a)) {
                if (a.val != NULL && ci_eq_span(a.name, a.nlen, "src")) {
                    src = a.val; srclen = a.vlen;
                }
            }
            if (src != NULL) emit(out, PF_SCRIPT, src, srclen);
            /* Raw-text element: the content (inline JS) is opaque. A missing
             * closer skips the rest -- fewer prefetches, never a wrong one. */
            const char *closer = ci_find(cur, end, "</script");
            p = (closer != NULL) ? closer + 8 : end;
            continue;
        }

        if (ci_starts(p, end, "<style") &&
            !(p + 6 < end && is_name_char(p[6]))) {
            const char *closer = ci_find(p + 6, end, "</style");
            p = (closer != NULL) ? closer + 7 : end;
            continue;
        }

        if (ci_starts(p, end, "<link") &&
            !(p + 5 < end && is_name_char(p[5]))) {
            const char *cur = p + 5;
            attr_span a;
            const char *href = NULL, *rel = NULL;
            size_t hlen = 0, rlen = 0;
            while (next_attr(&cur, end, &a)) {
                if (a.val == NULL) continue;
                if (ci_eq_span(a.name, a.nlen, "href")) { href = a.val; hlen = a.vlen; }
                else if (ci_eq_span(a.name, a.nlen, "rel")) { rel = a.val; rlen = a.vlen; }
            }
            if (href != NULL && rel != NULL && rel_has_stylesheet(rel, rlen))
                emit(out, PF_STYLESHEET, href, hlen);
            p = cur;
            continue;
        }

        p++;
    }
    return 0;
}

void pf_list_free(pf_list *l) {
    if (l == NULL) return;
    for (size_t i = 0; i < l->count; ++i) free(l->refs[i].url);
    l->count = 0;
}

/* --- pool -------------------------------------------------------------- */

static void *pf_worker(void *arg) {
    pf_pool *p = (pf_pool *)arg;
    for (;;) {
        pthread_mutex_lock(&p->lock);
        size_t i = p->next;
        if (i >= p->count) {
            pthread_mutex_unlock(&p->lock);
            break;
        }
        p->next++;
        p->jobs[i].state = PF_JOB_RUNNING;
        pthread_mutex_unlock(&p->lock);

        pf_job *j = &p->jobs[i];
        int st = 0; char *b = NULL; size_t l = 0; char *ct = NULL;
        int rc = p->fetch(p->ctx, "GET", j->url, NULL, 0, &st, &b, &l, &ct);

        pthread_mutex_lock(&p->lock);
        j->rc = rc; j->status = st; j->body = b; j->len = l; j->ctype = ct;
        j->state = PF_JOB_DONE;
        pthread_cond_broadcast(&p->done_cv);
        pthread_mutex_unlock(&p->lock);
    }
    return NULL;
}

int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_fn fetch, void *ctx) {
    if (p == NULL) return -1;
    memset(p, 0, sizeof *p);
    if (urls == NULL || nurls == 0 || fetch == NULL) return -1;

    for (size_t i = 0; i < nurls && p->count < PF_MAX_REFS; ++i) {
        if (urls[i] == NULL || urls[i][0] == '\0') continue;
        int dup = 0;
        for (size_t j = 0; j < p->count; ++j)
            if (strcmp(p->jobs[j].url, urls[i]) == 0) { dup = 1; break; }
        if (dup) continue;
        char *u = strdup(urls[i]);
        if (u == NULL) continue;
        p->jobs[p->count].url = u;
        p->jobs[p->count].state = PF_JOB_PENDING;
        p->count++;
    }
    if (p->count == 0) return -1;

    pthread_mutex_init(&p->lock, NULL);
    pthread_cond_init(&p->done_cv, NULL);
    p->fetch = fetch;
    p->ctx = ctx;

    size_t want = (p->count < PF_MAX_THREADS) ? p->count : PF_MAX_THREADS;
    for (size_t i = 0; i < want; ++i) {
        if (pthread_create(&p->threads[p->nthreads], NULL, pf_worker, p) != 0)
            break;
        p->nthreads++;
    }
    if (p->nthreads == 0) {
        /* No threads at all: performance fails open (caller fetches serially),
         * nothing may be left half-owned. */
        for (size_t i = 0; i < p->count; ++i) free(p->jobs[i].url);
        pthread_mutex_destroy(&p->lock);
        pthread_cond_destroy(&p->done_cv);
        memset(p, 0, sizeof *p);
        return -1;
    }
    p->started = 1;
    return 0;
}

int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body, size_t *len, char **ctype) {
    if (rc != NULL) *rc = -1;
    if (status != NULL) *status = 0;
    if (body != NULL) *body = NULL;
    if (len != NULL) *len = 0;
    if (ctype != NULL) *ctype = NULL;
    if (p == NULL || url == NULL || !p->started) return 0;

    pthread_mutex_lock(&p->lock);
    pf_job *j = NULL;
    for (size_t i = 0; i < p->count; ++i) {
        if (p->jobs[i].state != PF_JOB_CONSUMED &&
            strcmp(p->jobs[i].url, url) == 0) {
            j = &p->jobs[i];
            break;
        }
    }
    if (j == NULL) {
        pthread_mutex_unlock(&p->lock);
        return 0;
    }
    while (j->state != PF_JOB_DONE)
        pthread_cond_wait(&p->done_cv, &p->lock);

    if (rc != NULL) *rc = j->rc;
    if (status != NULL) *status = j->status;
    if (body != NULL) { *body = j->body; j->body = NULL; }
    if (len != NULL) *len = j->len;
    if (ctype != NULL) { *ctype = j->ctype; j->ctype = NULL; }
    /* Anything not moved out is freed here: exactly one owner either way. */
    free(j->body);  j->body = NULL;
    free(j->ctype); j->ctype = NULL;
    j->len = 0;
    j->state = PF_JOB_CONSUMED;
    pthread_mutex_unlock(&p->lock);
    return 1;
}

void pf_pool_finish(pf_pool *p) {
    if (p == NULL || !p->started) return;
    for (size_t i = 0; i < p->nthreads; ++i)
        pthread_join(p->threads[i], NULL);
    for (size_t i = 0; i < p->count; ++i) {
        free(p->jobs[i].url);
        free(p->jobs[i].body);
        free(p->jobs[i].ctype);
    }
    pthread_mutex_destroy(&p->lock);
    pthread_cond_destroy(&p->done_cv);
    memset(p, 0, sizeof *p);
}

int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const char *body, size_t body_len,
                    int *out_status, char **out_body, size_t *out_len,
                    char **out_ctype) {
    pf_gated_fetch *g = (pf_gated_fetch *)vctx;
    if (g == NULL || g->inner == NULL) return -1;
    if (g->pool != NULL && method != NULL && strcmp(method, "GET") == 0) {
        int rc = -1;
        if (pf_pool_take(g->pool, url, &rc, out_status, out_body, out_len,
                         out_ctype) == 1)
            return rc;
    }
    return g->inner(g->inner_ctx, method, url, body, body_len,
                    out_status, out_body, out_len, out_ctype);
}
