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
#include "url.h"
#include "import_map.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>

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
    if (vlen == (size_t)-1) return;
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


/* --- ES module graph (spec/prefetch.md section 8) --- */

static int js_ident_ch(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
        || c == '_' || c == '$';
}

static size_t js_skip_ws(const char *s, size_t i, size_t n) {
    while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == '\r'))
        ++i;
    return i;
}

/* Index just past the string or template literal opening at s[i]. */
static size_t js_skip_string(const char *s, size_t i, size_t n) {
    char q = s[i++];
    while (i < n && s[i] != q) i += (s[i] == '\\') ? 2 : 1;
    return (i < n) ? i + 1 : n;
}

/* Captures the quoted specifier at s[i] when it is URL-shaped. */
static void js_take_spec(const char *s, size_t i, size_t n,
                         char (*out)[PF_SPEC_MAX], size_t cap, size_t *k) {
    if (i >= n || (s[i] != '"' && s[i] != '\'') || *k >= cap) return;
    char q = s[i];
    size_t a = i + 1, b = a;
    while (b < n && s[b] != q && s[b] != '\\' && s[b] != '\n') ++b;
    if (b >= n || s[b] != q) return;
    size_t len = b - a;
    if (len == 0 || len >= PF_SPEC_MAX) return;
    const char *sp = s + a;
    memcpy(out[*k], sp, len);
    out[*k][len] = '\0';
    ++*k;
}

size_t pf_scan_imports(const char *js, size_t len, char (*out)[PF_SPEC_MAX], size_t cap) {
    if (js == NULL || out == NULL || cap == 0) return 0;
    size_t k = 0, i = 0;
    int clause = 0;   /* inside `import ...`/`export ...` awaiting `from` */
    while (i < len && k < cap) {
        char c = js[i];
        if (c == '/' && i + 1 < len && js[i + 1] == '/') {
            while (i < len && js[i] != '\n') ++i;
            continue;
        }
        if (c == '/' && i + 1 < len && js[i + 1] == '*') {
            i += 2;
            while (i + 1 < len && !(js[i] == '*' && js[i + 1] == '/')) ++i;
            i = (i + 1 < len) ? i + 2 : len;
            continue;
        }
        if (c == '"' || c == '\'' || c == '`') { i = js_skip_string(js, i, len); continue; }
        if (c == ';') { clause = 0; ++i; continue; }
        if (!js_ident_ch(c)) { ++i; continue; }
        size_t a = i;
        while (i < len && js_ident_ch(js[i])) ++i;
        size_t wl = i - a;
        int boundary = (a == 0) || (js[a - 1] != '.' && !js_ident_ch(js[a - 1]));
        if (!boundary) continue;
        if (wl == 6 && memcmp(js + a, "import", 6) == 0) {
            size_t j = js_skip_ws(js, i, len);
            if (j < len && (js[j] == '"' || js[j] == '\'')) {   /* import "x" */
                js_take_spec(js, j, len, out, cap, &k);
                i = js_skip_string(js, j, len);
                clause = 0;
            } else if (j < len && (js[j] == '(' || js[j] == '.')) {
                clause = 0;   /* import() / import.meta: never prefetched */
            } else {
                clause = 1;
            }
        } else if (wl == 6 && memcmp(js + a, "export", 6) == 0) {
            clause = 1;
        } else if (wl == 4 && memcmp(js + a, "from", 4) == 0 && clause) {
            size_t j = js_skip_ws(js, i, len);
            js_take_spec(js, j, len, out, cap, &k);
            if (j < len && (js[j] == '"' || js[j] == '\'')) i = js_skip_string(js, j, len);
            clause = 0;
        }
    }
    return k;
}

int pf_pool_add(pf_pool *p, const char *url) {
    if (p == NULL || url == NULL || url[0] == '\0') return 0;
    pthread_mutex_lock(&p->lock);
    int added = 0;
    if (p->started && !p->closing && p->count < PF_MAX_JOBS) {
        int dup = 0;
        for (size_t j = 0; j < p->count; ++j)
            if (strcmp(p->jobs[j].url, url) == 0) { dup = 1; break; }
        if (!dup) {
            char *u = strdup(url);
            if (u != NULL) {
                p->jobs[p->count].url = u;
                p->jobs[p->count].state = PF_JOB_PENDING;
                p->count++;
                pthread_cond_signal(&p->work_cv);
                added = 1;
            }
        }
    }
    pthread_mutex_unlock(&p->lock);
    return added;
}

static int pf_is_js(const char *url, const char *ctype) {
    if (ctype != NULL && strstr(ctype, "javascript") != NULL) return 1;
    if (url == NULL) return 0;
    size_t n = strcspn(url, "?#");
    return (n >= 3 && memcmp(url + n - 3, ".js", 3) == 0)
        || (n >= 4 && memcmp(url + n - 4, ".mjs", 4) == 0);
}

static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz) {
    (void)ctx;
    return (url_resolve_https(base, ref, out, outsz) == URL_OK) ? 0 : -1;
}

static int pf_url_shaped(const char *sp) {
    return (sp[0] == '.' && sp[1] == '/') || (sp[0] == '.' && sp[1] == '.' && sp[2] == '/')
        || sp[0] == '/' || strncmp(sp, "https://", 8) == 0;
}

/* Queues the static imports of a fetched module body, resolved the way the module
 * loader resolves them: through the page's import map (which also covers bare
 * specifiers), else as a URL against the module's own. imap is immutable once the
 * pool started, so reading it from any thread needs no lock. */
static void pf_follow_imports(pf_pool *p, const char *base, const char *body, size_t len) {
    char (*specs)[PF_SPEC_MAX] = calloc(PF_MAX_IMPORTS, sizeof *specs);
    if (specs == NULL) return;
    size_t n = pf_scan_imports(body, len, specs, PF_MAX_IMPORTS);
    char abs[PF_SPEC_MAX * 2];
    for (size_t k = 0; k < n; ++k) {
        int ok = -1;
        if (p->imap != NULL)
            ok = im_resolve(p->imap, base, specs[k], pf_url_cb, NULL, abs, sizeof abs);
        if (ok != 0 && pf_url_shaped(specs[k]))
            ok = pf_url_cb(NULL, base, specs[k], abs, sizeof abs);
        if (ok == 0) (void)pf_pool_add(p, abs);
    }
    free(specs);
}

static void *pf_worker(void *arg) {
    pf_pool *p = (pf_pool *)arg;
    for (;;) {
        pthread_mutex_lock(&p->lock);
        /* Threads live until finish: a module fetched later may queue more work. */
        while (p->next >= p->count && !p->closing)
            pthread_cond_wait(&p->work_cv, &p->lock);
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
        /* Queue this module's imports BEFORE publishing it: the worker that takes
         * it requests them next, and must find them already in the pool. */
        if (rc == 0 && b != NULL && st >= 200 && st < 300 && pf_is_js(j->url, ct))
            pf_follow_imports(p, j->url, b, l);

        pthread_mutex_lock(&p->lock);
        j->rc = rc; j->status = st; j->body = b; j->len = l; j->ctype = ct;
        j->state = PF_JOB_DONE;
        pthread_cond_broadcast(&p->done_cv);
        pthread_mutex_unlock(&p->lock);
    }
    return NULL;
}

static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                      pf_fetch_fn fetch, void *ctx, struct im_map *map,
                      const char *page_url);
static int pf_url_cb(void *ctx, const char *base, const char *ref, char *out, size_t outsz);

int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_fn fetch, void *ctx) {
    return pool_start(p, urls, nurls, fetch, ctx, NULL, NULL);
}

/* map (owned on success) is set BEFORE the threads start: they read it after a
 * fetch, unlocked, and it never changes afterwards. */
static int pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                      pf_fetch_fn fetch, void *ctx, struct im_map *map,
                      const char *page_url) {
    if (p == NULL) return -1;
    memset(p, 0, sizeof *p);
    if (urls == NULL || nurls == 0 || fetch == NULL) return -1;

    for (size_t i = 0; i < nurls && p->count < PF_MAX_JOBS; ++i) {
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
    pthread_cond_init(&p->work_cv, NULL);
    p->fetch = fetch;
    p->ctx = ctx;
    p->imap = map;
    p->page_url = (page_url != NULL) ? strdup(page_url) : NULL;
    p->started = 1;   /* before the threads: a module they fetch may add jobs */

    /* Every thread: the module graph grows the job list after start. */
    for (size_t i = 0; i < PF_MAX_THREADS; ++i) {
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
        pthread_cond_destroy(&p->work_cv);
        free(p->page_url);
        memset(p, 0, sizeof *p);   /* map stays the caller's on failure */
        return -1;
    }
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

int pf_find_importmap(const char *html, size_t len, size_t *start, size_t *n) {
    if (html == NULL || start == NULL || n == NULL) return 0;
    for (size_t i = 0; i + 7 < len; ++i) {
        if (html[i] != '<' || strncasecmp(html + i + 1, "script", 6) != 0) continue;
        size_t e = i + 7;
        while (e < len && html[e] != '>') ++e;
        if (e >= len) return 0;
        int is_map = 0;
        for (size_t k = i + 7; k + 9 <= e; ++k)
            if (strncasecmp(html + k, "importmap", 9) == 0) { is_map = 1; break; }
        if (!is_map) continue;
        size_t b = e + 1, c = b;
        while (c + 9 <= len && strncasecmp(html + c, "</script", 8) != 0) ++c;
        if (c + 9 > len) return 0;
        *start = b;
        *n = c - b;
        return 1;
    }
    return 0;
}

int pf_pool_start_page(pf_pool *p, const char *html, size_t len, const char *page_url,
                       int css_grant, int js_grant, pf_fetch_fn fetch, void *ctx) {
    if (p == NULL) return -1;
    memset(p, 0, sizeof *p);
    if (!(css_grant || js_grant)) return -1;
    pf_list scanned;
    scanned.count = 0;
    if (pf_scan(html, len, &scanned) != 0) return -1;
    /* Keys are ABSOLUTE: a classic script is requested by its raw src, a module
     * already resolved, and both must find the same job (pf_pooled_fetch
     * normalizes the request the same way). */
    const char *urls[PF_MAX_REFS];
    char (*absu)[PF_SPEC_MAX * 2] = calloc(PF_MAX_REFS, sizeof *absu);
    if (absu == NULL) { pf_list_free(&scanned); return -1; }
    size_t nurl = 0;
    for (size_t i = 0; i < scanned.count && nurl < PF_MAX_REFS; ++i) {
        int want = (scanned.refs[i].kind == PF_STYLESHEET) ? css_grant : js_grant;
        if (!want) continue;
        if (page_url != NULL &&
            pf_url_cb(NULL, page_url, scanned.refs[i].url, absu[nurl], sizeof absu[nurl]) == 0)
            urls[nurl] = absu[nurl];
        else
            urls[nurl] = scanned.refs[i].url;
        ++nurl;
    }
    struct im_map *map = NULL;
    size_t ms = 0, mn = 0;
    if (js_grant && page_url != NULL && pf_find_importmap(html, len, &ms, &mn))
        map = im_parse(html + ms, mn, page_url, pf_url_cb, NULL);
    int rc = (nurl > 0) ? pool_start(p, urls, nurl, fetch, ctx, map, page_url) : -1;
    free(absu);
    pf_list_free(&scanned);
    if (rc != 0) { im_free(map); return -1; }
    return 0;
}

void pf_pool_finish(pf_pool *p) {
    if (p == NULL || !p->started) return;
    pthread_mutex_lock(&p->lock);
    p->closing = 1;
    pthread_cond_broadcast(&p->work_cv);
    pthread_mutex_unlock(&p->lock);
    for (size_t i = 0; i < p->nthreads; ++i)
        pthread_join(p->threads[i], NULL);
    for (size_t i = 0; i < p->count; ++i) {
        free(p->jobs[i].url);
        free(p->jobs[i].body);
        free(p->jobs[i].ctype);
    }
    im_free(p->imap);
    free(p->page_url);
    pthread_mutex_destroy(&p->lock);
    pthread_cond_destroy(&p->done_cv);
    pthread_cond_destroy(&p->work_cv);
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
        /* The same absolute key the pool was filled with; the fetch on a miss
         * still goes out with the request exactly as the worker made it. */
        char key[PF_SPEC_MAX * 2];
        const char *k = url;
        if (g->pool->page_url != NULL && url != NULL &&
            pf_url_cb(NULL, g->pool->page_url, url, key, sizeof key) == 0)
            k = key;
        if (pf_pool_take(g->pool, k, &rc, out_status, out_body, out_len,
                         out_ctype) == 1)
            return rc;
    }
    return g->inner(g->inner_ctx, method, url, body, body_len,
                    out_status, out_body, out_len, out_ctype);
}

