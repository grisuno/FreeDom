/* subreq_batch -- see include/subreq_batch.h and spec/subreq_async.md. */
#define _GNU_SOURCE
#include "subreq_batch.h"

#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct sqb_job {
    sqb       *owner;
    char      *method, *url, *body, *headers;
    size_t     body_len;
    int        refused;
    int        started;
    pthread_t  th;
    sqb_res    res;
} sqb_job;

struct sqb {
    sqb_run_fn run;
    void      *ctx;
    sem_t      slots;
    int        sem_ok;
    sqb_job   *jobs[SQB_MAX_JOBS];
    size_t     n;
};

static char *dup_n(const char *s, size_t n) {
    if (n == (size_t)-1) return NULL;
    char *d = (char *)malloc(n + 1);
    if (d == NULL) return NULL;
    if (n != 0) memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

static void res_clear(sqb_res *r) {
    free(r->body); free(r->ctype); free(r->resp_headers);
    memset(r, 0, sizeof *r);
}

static void job_free(sqb_job *j) {
    if (j == NULL) return;
    free(j->method); free(j->url); free(j->body); free(j->headers);
    res_clear(&j->res);
    free(j);
}

static void *job_main(void *arg) {
    sqb_job *j = (sqb_job *)arg;
    sqb *b = j->owner;
    sem_wait(&b->slots);
    sqb_req rq = { j->method, j->url, j->body, j->body_len, j->headers };
    sqb_res out;
    memset(&out, 0, sizeof out);
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    int rc = b->run(b->ctx, &rq, &out);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    long ms = (long)((t1.tv_sec - t0.tv_sec) * 1000L + (t1.tv_nsec - t0.tv_nsec) / 1000000L);
    if (ms < 0) ms = 0;
    if (ms > 3600000L) ms = 3600000L;
    if (rc == 0 && out.ok) {
        j->res = out;
    } else {
        res_clear(&out);
    }
    j->res.elapsed_ms = (int)ms;
    sem_post(&b->slots);
    return NULL;
}

sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx) {
    if (run == NULL || max_threads < 1) return NULL;
    sqb *b = (sqb *)calloc(1, sizeof *b);
    if (b == NULL) return NULL;
    b->run = run;
    b->ctx = ctx;
    if (sem_init(&b->slots, 0, (unsigned)max_threads) != 0) { free(b); return NULL; }
    b->sem_ok = 1;
    return b;
}

int sqb_submit(sqb *b, int refused, const sqb_req *req) {
    if (b == NULL || req == NULL || b->n >= SQB_MAX_JOBS) return -1;
    sqb_job *j = (sqb_job *)calloc(1, sizeof *j);
    if (j == NULL) return -1;
    j->owner = b;
    j->refused = refused;
    if (!refused) {
        j->method  = dup_n(req->method ? req->method : "", req->method ? strlen(req->method) : 0);
        j->url     = dup_n(req->url ? req->url : "", req->url ? strlen(req->url) : 0);
        j->body    = dup_n(req->body ? req->body : "", req->body_len);
        j->body_len = req->body_len;
        j->headers = dup_n(req->headers ? req->headers : "", req->headers ? strlen(req->headers) : 0);
        if (j->method == NULL || j->url == NULL || j->body == NULL || j->headers == NULL) {
            job_free(j);
            return -1;
        }
        if (pthread_create(&j->th, NULL, job_main, j) != 0) {
            job_free(j);
            return -1;
        }
        j->started = 1;
    }
    b->jobs[b->n++] = j;
    return 0;
}

size_t sqb_count(const sqb *b) { return b != NULL ? b->n : 0; }

void sqb_wait_all(sqb *b) {
    if (b == NULL) return;
    for (size_t i = 0; i < b->n; ++i) {
        sqb_job *j = b->jobs[i];
        if (j->started) { pthread_join(j->th, NULL); j->started = 0; }
    }
}

const sqb_res *sqb_result(const sqb *b, size_t i) {
    return (b != NULL && i < b->n) ? &b->jobs[i]->res : NULL;
}

void sqb_reset(sqb *b) {
    if (b == NULL) return;
    sqb_wait_all(b);
    for (size_t i = 0; i < b->n; ++i) { job_free(b->jobs[i]); b->jobs[i] = NULL; }
    b->n = 0;
}

void sqb_free(sqb *b) {
    if (b == NULL) return;
    sqb_reset(b);
    if (b->sem_ok) sem_destroy(&b->slots);
    free(b);
}
