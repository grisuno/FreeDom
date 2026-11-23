/*
 * subreq_batch -- a batch of subresource fetches run in parallel (spec/subreq_async.md).
 *
 * The trusted parent submits each deferred XHR/fetch of a worker here as the frame arrives, and
 * collects every result, in submission order, when the worker asks for the batch. The module owns
 * only threads and buffers: WHAT a request may reach (policy, grants, headers) is decided by the
 * caller before submit and inside the run callback. At most `max_threads` runs overlap.
 */
#ifndef SUBREQ_BATCH_H
#define SUBREQ_BATCH_H

#include <stddef.h>

#define SQB_MAX_JOBS 64

typedef struct sqb_req {
    const char *method, *url, *body;
    size_t      body_len;
    const char *headers;            /* already sanitized by the caller; may be "" */
} sqb_req;

/* Filled by the run callback; every pointer malloc'd and owned by the batch afterwards. */
typedef struct sqb_res {
    int     ok;                     /* 0 = refused/failed: status 0, no body */
    int     status;
    int     elapsed_ms;             /* wall time of the fetch itself, queueing excluded */
    char   *body;  size_t body_len;
    char   *ctype;
    char   *resp_headers;
} sqb_res;

/* Runs ON A POOL THREAD for one request. Return 0 with `out` filled on success. */
typedef int (*sqb_run_fn)(void *ctx, const sqb_req *req, sqb_res *out);

typedef struct sqb sqb;

sqb  *sqb_new(int max_threads, sqb_run_fn run, void *ctx);
/* sqb_new whose ctx the batch OWNS: free_ctx(ctx) runs once the batch is freed AND every
 * abandoned request has finished -- the run callback may use ctx until then. */
sqb  *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *));
/* Frees every finished job and ABANDONS every running one: its thread is detached, its result
 * is discarded when it ends, and nothing here waits. The batch is empty and reusable. */
void  sqb_abandon(sqb *b);
/* Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the
 * result count always equals the submit count. Returns 0, or -1 when full / out of memory (nothing
 * queued: the caller must answer the worker itself). */
int   sqb_submit(sqb *b, int refused, const sqb_req *req);
size_t sqb_count(const sqb *b);
/* Joins every running request. */
void  sqb_wait_all(sqb *b);
/* Valid after sqb_wait_all, for i < sqb_count. */
const sqb_res *sqb_result(const sqb *b, size_t i);
/* Waits until every request finished or `wait_ms` elapsed (0 = do not wait), then writes the
 * indices of EVERY finished request, ascending, into idx (at most cap) and returns how many
 * (spec/subreq_async.md, "Entrega con plazo"). Those results are valid through sqb_result. */
size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap);
/* Joins and frees the jobs at the k ascending indices (unfinished or out-of-range ones are
 * skipped); the others keep running and keep their relative order. */
void  sqb_remove(sqb *b, const size_t *idx, size_t k);
/* Joins (waits for) and frees every job and result; the batch is reusable. */
void  sqb_reset(sqb *b);
/* Abandons what is still running (sqb_abandon) and releases the batch; the memory goes when the
 * last abandoned request ends. Never waits. */
void  sqb_free(sqb *b);

#endif
