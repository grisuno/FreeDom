#ifndef FREEDOM_PREFETCH_H
#define FREEDOM_PREFETCH_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>
#include <pthread.h>

/*
 * prefetch — trusted-side lookahead scanner + parallel subresource pool (Hito 29).
 *
 * The confined worker requests subresources one at a time over a blocking pipe
 * (TAG_SUBREQ; io_uring is forbidden there), so N resources cost the SUM of their
 * latencies. This module brings the browser "preload scanner" pattern to the
 * TRUSTED side only: pf_scan (pure, no I/O) extracts <link rel=stylesheet href>
 * and <script src> references from the raw hostile HTML, and pf_pool_* downloads
 * a URL list in parallel through the SAME policy-gated fetch callback that would
 * serve the serial request. The worker protocol does not change; a pool miss just
 * falls back to the direct fetch. Removing the pool changes WHEN bytes are
 * fetched, never WHAT.
 *
 * Threads only touch the pool's own state (under its mutex) and the fetch
 * callback, which must be reentrant and apply the full network policy. take() and
 * finish() are called from the single orchestrating (load) thread.
 *
 * See spec/prefetch.md for the full contract.
 */

/* Subresource kinds the lookahead scanner recognizes. Anything else (icons,
 * preload hints, images) is deliberately NOT scanned: prefetch never widens what
 * the page could request (images are pooled from the post-rd_build, policy-decided
 * list instead). */
typedef enum pf_kind {
    PF_STYLESHEET = 0,  /* <link rel="stylesheet" href=...> */
    PF_SCRIPT           /* <script src=...> */
} pf_kind;

/* One scanned reference. url is the RAW attribute value (the policy-gated fetcher
 * resolves and validates it, exactly as it does for the worker's own request). */
typedef struct pf_ref {
    pf_kind kind;
    char   *url;   /* owned by the pf_list */
} pf_ref;

#define PF_MAX_REFS    64   /* anti-DoS cap for the scanner and the pool */
#define PF_MAX_THREADS 4    /* maximum simultaneous downloads */

typedef struct pf_list {
    pf_ref refs[PF_MAX_REFS];
    size_t count;
} pf_list;

/* Lookahead scan of hostile HTML. Fills out (owns the URLs; free with
 * pf_list_free). Comment, <script> and <style> contents are opaque; a <link>
 * whose rel list lacks the "stylesheet" token is ignored (fail closed). Returns 0
 * (even with zero refs) or -1 on NULL arguments. Never performs I/O. */
int  pf_scan(const char *html, size_t len, pf_list *out);
void pf_list_free(pf_list *l);

/* Fetch callback: signature identical to tab_fetch_fn (tab.h). Invoked from pool
 * threads; must be reentrant and must apply the FULL network policy (it is the
 * same callback that serves the serial TAG_SUBREQ path). */
typedef int (*pf_fetch_fn)(void *ctx, const char *method, const char *url,
                           const char *body, size_t body_len,
                           int *out_status, char **out_body, size_t *out_len,
                           char **out_ctype);

typedef enum pf_job_state {
    PF_JOB_PENDING = 0,
    PF_JOB_RUNNING,
    PF_JOB_DONE,
    PF_JOB_CONSUMED
} pf_job_state;

typedef struct pf_job {
    char        *url;    /* owned by the pool */
    pf_job_state state;
    int          rc;     /* the fetch callback's return value */
    int          status; /* HTTP status when rc == 0 */
    char        *body;   /* owned until taken or finish() */
    size_t       len;
    char        *ctype;  /* owned until taken or finish(); may be NULL */
} pf_job;

typedef struct pf_pool {
    pf_job          jobs[PF_MAX_REFS];
    size_t          count;
    pf_fetch_fn     fetch;
    void           *ctx;
    pthread_t       threads[PF_MAX_THREADS];
    size_t          nthreads;
    pthread_mutex_t lock;
    pthread_cond_t  done_cv;
    size_t          next;    /* next job index a worker thread claims */
    int             started;
} pf_pool;

/* Starts the pool over urls[0..nurls) (deep-copied; duplicates and entries past
 * PF_MAX_REFS are dropped) with min(PF_MAX_THREADS, jobs) worker threads, each
 * claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or
 * -1 when no thread could start (the caller just falls back to serial fetching:
 * performance fails open, policy is unaffected). */
int  pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                   pf_fetch_fn fetch, void *ctx);

/* Cache-first take. On a hit (url matches an unconsumed job) WAITS for that job
 * and MOVES the result to the caller: *rc is the callback's return value and, when
 * *rc == 0, the caller owns the returned body and ctype. Returns 1 on hit, 0 on miss (unknown or
 * already-consumed URL, pool not started): the caller then fetches directly. A
 * fetch failure is a hit with *rc != 0 -- the caller must NOT retry (same outcome
 * as the serial path, without duplicating requests). Single owner: a second take
 * of the same URL is a miss. */
int  pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                  char **body, size_t *len, char **ctype);

/* Joins the worker threads and frees every unconsumed result. Blocks until
 * in-flight fetches end (bounded by the fetcher's timeouts). Idempotent; after
 * finish, take always misses. */
void pf_pool_finish(pf_pool *p);

/* Cache-first fetcher adapter, shared by every frontend (DRY): install
 * pf_pooled_fetch as the tab fetcher with a pf_gated_fetch as its ctx. A GET
 * whose URL is pooled is served from the pool (a failed prefetch propagates the
 * failure -- never refetched); everything else (POST, miss, pool == NULL) goes
 * straight to the inner policy-gated fetcher. The pf_gated_fetch must outlive
 * the tab_load_full call; reset the tab's fetcher to the inner one afterwards. */
typedef struct pf_gated_fetch {
    pf_fetch_fn inner;
    void       *inner_ctx;
    pf_pool    *pool;   /* NULL: always direct */
} pf_gated_fetch;

int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const char *body, size_t body_len,
                    int *out_status, char **out_body, size_t *out_len,
                    char **out_ctype);

#endif /* FREEDOM_PREFETCH_H */
