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
/* Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the
 * result count always equals the submit count. Returns 0, or -1 when full / out of memory (nothing
 * queued: the caller must answer the worker itself). */
int   sqb_submit(sqb *b, int refused, const sqb_req *req);
size_t sqb_count(const sqb *b);
/* Joins every running request. */
void  sqb_wait_all(sqb *b);
/* Valid after sqb_wait_all, for i < sqb_count. */
const sqb_res *sqb_result(const sqb *b, size_t i);
/* Joins and frees every job and result; the batch is reusable. */
void  sqb_reset(sqb *b);
void  sqb_free(sqb *b);

#endif
