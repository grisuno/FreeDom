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
    int        done;                /* guarded by owner->mu */
    int        orphan;              /* abandoned: the thread frees the job (guarded by owner->mu) */
    pthread_t  th;
    sqb_res    res;
} sqb_job;

struct sqb {
    sqb_run_fn run;
    void      *ctx;
    sem_t      slots;
    int        sem_ok;
    pthread_mutex_t mu;             /* guards job->done; cv signals each completion */
    pthread_cond_t  cv;
    int        sync_ok;
    int        refs;                /* 1 for the owner + 1 per abandoned running job (mu) */
    void     (*free_ctx)(void *);
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

static void batch_destroy(sqb *b) {
    if (b->free_ctx != NULL) b->free_ctx(b->ctx);
    if (b->sem_ok) sem_destroy(&b->slots);
    if (b->sync_ok) { pthread_cond_destroy(&b->cv); pthread_mutex_destroy(&b->mu); }
    free(b);
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
    pthread_mutex_lock(&b->mu);
    j->done = 1;
    int orphan = j->orphan, last = 0;
    if (orphan) last = (--b->refs == 0);
    pthread_cond_broadcast(&b->cv);
    pthread_mutex_unlock(&b->mu);
    if (orphan) job_free(j);
    if (last) batch_destroy(b);
    return NULL;
}

sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx) {
    return sqb_new_owned(max_threads, run, ctx, NULL);
}

sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(void *)) {
    if (run == NULL || max_threads < 1) return NULL;
    sqb *b = (sqb *)calloc(1, sizeof *b);
    if (b == NULL) return NULL;
    b->run = run;
    b->ctx = ctx;
    if (sem_init(&b->slots, 0, (unsigned)max_threads) != 0) { free(b); return NULL; }
    b->sem_ok = 1;
    if (pthread_mutex_init(&b->mu, NULL) != 0) { sem_destroy(&b->slots); free(b); return NULL; }
    pthread_condattr_t ca;
    int cv_rc = pthread_condattr_init(&ca);
    if (cv_rc == 0) {
        (void)pthread_condattr_setclock(&ca, CLOCK_MONOTONIC);
        cv_rc = pthread_cond_init(&b->cv, &ca);
        pthread_condattr_destroy(&ca);
    }
    if (cv_rc != 0) {
        pthread_mutex_destroy(&b->mu); sem_destroy(&b->slots); free(b);
        return NULL;
    }
    b->sync_ok = 1;
    b->refs = 1;
    b->free_ctx = free_ctx;
    return b;
}

int sqb_submit(sqb *b, int refused, const sqb_req *req) {
    if (b == NULL || req == NULL || b->n >= SQB_MAX_JOBS) return -1;
    sqb_job *j = (sqb_job *)calloc(1, sizeof *j);
    if (j == NULL) return -1;
    j->owner = b;
    j->refused = refused;
    j->done = refused ? 1 : 0;
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

static int all_done_locked(const sqb *b) {
    for (size_t i = 0; i < b->n; ++i) if (!b->jobs[i]->done) return 0;
    return 1;
}

size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap) {
    if (b == NULL || idx == NULL) return 0;
    if (wait_ms < 0) wait_ms = 0;
    struct timespec dl;
    clock_gettime(CLOCK_MONOTONIC, &dl);
    dl.tv_sec  += wait_ms / 1000;
    dl.tv_nsec += (wait_ms % 1000) * 1000000L;
    if (dl.tv_nsec >= 1000000000L) { dl.tv_sec += 1; dl.tv_nsec -= 1000000000L; }
    pthread_mutex_lock(&b->mu);
    while (wait_ms > 0 && !all_done_locked(b))
        if (pthread_cond_timedwait(&b->cv, &b->mu, &dl) != 0) break;   /* timed out (or error) */
    size_t k = 0;
    for (size_t i = 0; i < b->n && k < cap; ++i) if (b->jobs[i]->done) idx[k++] = i;
    pthread_mutex_unlock(&b->mu);
    /* A finished job's thread is about to return: join it so its result is fully published. */
    for (size_t i = 0; i < k; ++i) {
        sqb_job *j = b->jobs[idx[i]];
        if (j->started) { pthread_join(j->th, NULL); j->started = 0; }
    }
    return k;
}

void sqb_remove(sqb *b, const size_t *idx, size_t k) {
    if (b == NULL || idx == NULL || k == 0) return;
    int drop[SQB_MAX_JOBS];
    memset(drop, 0, sizeof drop);
    pthread_mutex_lock(&b->mu);
    for (size_t i = 0; i < k; ++i)
        if (idx[i] < b->n && b->jobs[idx[i]]->done) drop[idx[i]] = 1;
    pthread_mutex_unlock(&b->mu);
    size_t w = 0;
    for (size_t i = 0; i < b->n; ++i) {
        sqb_job *j = b->jobs[i];
        if (drop[i]) {
            if (j->started) { pthread_join(j->th, NULL); j->started = 0; }
            job_free(j);
        } else {
            b->jobs[w++] = j;
        }
    }
    for (size_t i = w; i < b->n; ++i) b->jobs[i] = NULL;
    b->n = w;
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

void sqb_abandon(sqb *b) {
    if (b == NULL) return;
    pthread_mutex_lock(&b->mu);
    for (size_t i = 0; i < b->n; ++i) {
        sqb_job *j = b->jobs[i];
        if (j->done) continue;
        j->orphan = 1;              /* its thread frees it; the batch lives until then */
        b->refs++;
        pthread_detach(j->th);
        j->started = 0;
        b->jobs[i] = NULL;
    }
    pthread_mutex_unlock(&b->mu);
    for (size_t i = 0; i < b->n; ++i) {
        sqb_job *j = b->jobs[i];
        if (j == NULL) continue;
        if (j->started) { pthread_join(j->th, NULL); j->started = 0; }
        job_free(j);
        b->jobs[i] = NULL;
    }
    b->n = 0;
}

void sqb_free(sqb *b) {
    if (b == NULL) return;
    sqb_abandon(b);
    pthread_mutex_lock(&b->mu);
    int last = (--b->refs == 0);
    pthread_mutex_unlock(&b->mu);
    if (last) batch_destroy(b);
}
