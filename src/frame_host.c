/*
 * frame_host -- trusted-parent side of iframes (spec/frame_broker.md section 4).
 * Every frame is its own confined worker; this module only routes strings between them, after
 * frame_broker has decided the addressee and the origin match.
 */
#include "frame_host.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frame_broker.h"

/* One frame load: fetch + confined worker + its first load. Run inline (headless) or on its own
 * thread (fh_set_async); `done`/`orphan` are guarded by mu. An orphaned job (frame closed or host
 * freed while it ran) is freed by its own thread. */
typedef struct fh_job {
    pthread_mutex_t mu;
    pthread_t    th;
    int          threaded, done, orphan;
    tab_fetch_fn fetch;
    void        *fetch_ctx;
    int          id;
    char        *url;
    tab         *t;
    tab_page     pg;
    int          ok;
} fh_job;

typedef struct fh_slot {
    fh_job *job;         /* a background load in flight (async hosts only) */
    tab *t;
    int  token;          /* the token the PARENT document's JS gave this <iframe> */
    int  next_timer_ms;  /* -1 when none */
    pv_view *view;       /* the frame document as its worker last built it (owned) */
    char    *url;        /* the URL it was loaded from (owned) */
} fh_slot;

struct fh_host {
    fbk_table     tbl;
    fh_slot       slot[FBK_MAX_FRAMES];
    tab_fetch_fn  fetch;
    void         *fetch_ctx;
    fh_top_msg_fn top_msg;
    void         *top_ctx;
    int           depth;
    int           async; /* fh_set_async: FRAME_OPEN loads on a background thread */
    unsigned      gen;   /* bumped whenever a frame's view changes: the painter's refresh cue */
};

static void apply_ops(fh_host *h, int from, const tab_ws_op *ops, size_t n);

fh_host *fh_new(const char *top_url, tab_fetch_fn fetch, void *fetch_ctx,
                fh_top_msg_fn top_msg, void *top_ctx) {
    if (top_url == NULL || fetch == NULL || top_msg == NULL) return NULL;
    fh_host *h = (fh_host *)calloc(1, sizeof *h);
    if (h == NULL) return NULL;
    if (fbk_init(&h->tbl, top_url) != 0) { free(h); return NULL; }
    h->fetch = fetch; h->fetch_ctx = fetch_ctx;
    h->top_msg = top_msg; h->top_ctx = top_ctx;
    for (int i = 0; i < FBK_MAX_FRAMES; ++i) h->slot[i].next_timer_ms = -1;
    return h;
}

static void slot_release_view(fh_slot *sl) {
    pv_free(sl->view);
    sl->view = NULL;
    free(sl->url);
    sl->url = NULL;
}

static void job_destroy(fh_job *j) {
    if (j == NULL) return;
    if (j->t != NULL) tab_close(j->t);
    tab_page_free(&j->pg);
    free(j->url);
    pthread_mutex_destroy(&j->mu);
    free(j);
}

/* Fetch the frame document and load it into a fresh confined worker (no host state touched). */
static void job_run(fh_job *j) {
    int status = 0;
    char *body = NULL, *ctype = NULL;
    size_t blen = 0;
    j->ok = 0;
    if (j->fetch(j->fetch_ctx, "GET", j->url, NULL, 0, &status, &body, &blen, &ctype) != 0
        || status < 200 || status >= 300 || body == NULL || blen == 0 || blen > TAB_MAX_INPUT) {
        free(body); free(ctype);
        return;
    }
    free(ctype);
    if (tab_open(&j->t) != TAB_OK) { j->t = NULL; free(body); return; }
    tab_set_lazy_ticks(j->t, 1);   /* fh_tick keeps the frame's last view when a tick sends none */
    tab_set_net_allowed(j->t, 1);
    tab_set_css_allowed(j->t, 1);
    tab_set_fetcher(j->t, j->fetch, j->fetch_ctx);
    tab_set_frame_id(j->t, j->id);
    memset(&j->pg, 0, sizeof j->pg);
    j->ok = (tab_load_full(j->t, body, blen, j->url, 1, 0, 0, &j->pg) == TAB_OK);
    free(body);
}

static void *job_main(void *arg) {
    fh_job *j = (fh_job *)arg;
    job_run(j);
    pthread_mutex_lock(&j->mu);
    j->done = 1;
    int orphan = j->orphan;
    pthread_mutex_unlock(&j->mu);
    if (orphan) job_destroy(j);
    return NULL;
}

/* Owner thread: forget a job; a running one finishes and frees itself. */
static void job_abandon(fh_job *j) {
    if (j == NULL) return;
    if (!j->threaded) { job_destroy(j); return; }
    pthread_mutex_lock(&j->mu);
    int done = j->done;
    if (!done) j->orphan = 1;
    pthread_mutex_unlock(&j->mu);
    if (done) { pthread_join(j->th, NULL); job_destroy(j); }
    else pthread_detach(j->th);
}

/* Closes the worker of every frame that is no longer in the table. */
static void reap(fh_host *h) {
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        if (h->slot[i].job != NULL && fbk_origin(&h->tbl, i) == NULL) {
            job_abandon(h->slot[i].job);
            h->slot[i].job = NULL;
        }
        if (h->slot[i].t != NULL && fbk_origin(&h->tbl, i) == NULL) {
            tab_close(h->slot[i].t);
            h->slot[i].t = NULL;
            h->slot[i].next_timer_ms = -1;
            slot_release_view(&h->slot[i]);
            h->gen++;
        }
    }
}

void fh_free(fh_host *h) {
    if (h == NULL) return;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        job_abandon(h->slot[i].job);
        h->slot[i].job = NULL;
        if (h->slot[i].t != NULL) tab_close(h->slot[i].t);
        slot_release_view(&h->slot[i]);
    }
    free(h);
}

int fh_count(const fh_host *h) {
    int n = 0;
    if (h == NULL) return 0;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) if (h->slot[i].t != NULL) ++n;
    return n;
}

/* Installs a finished load into slot `id` and processes the ops of its load. A failed load, or a
 * frame no longer in the table, leaves no frame (fail-closed, no hole in the tree). */
static void integrate(fh_host *h, fh_job *j) {
    int id = j->id;
    if (!j->ok || j->t == NULL || fbk_origin(&h->tbl, id) == NULL) {
        if (fbk_origin(&h->tbl, id) != NULL) fbk_remove(&h->tbl, id);
        job_destroy(j);
        reap(h);
        return;
    }
    h->slot[id].t = j->t;
    j->t = NULL;
    h->slot[id].next_timer_ms = j->pg.next_timer_ms;
    /* Keep the document the worker built: the painter renders it into the <iframe> box. */
    slot_release_view(&h->slot[id]);
    h->slot[id].view = j->pg.view;
    j->pg.view = NULL;
    h->slot[id].url = j->url;
    j->url = NULL;
    h->gen++;
    if (fbk_origin(&h->tbl, id) != NULL) apply_ops(h, id, j->pg.ws, j->pg.nws);
    job_destroy(j);
}

/* Loads the document of frame `id` (already registered in the table): inline, or on a thread
 * that fh_tick collects (fh_set_async). */
static void load_frame(fh_host *h, int id, const char *url) {
    fh_job *j = (fh_job *)calloc(1, sizeof *j);
    size_t ul = strlen(url);
    if (j == NULL || ul == (size_t)-1 || pthread_mutex_init(&j->mu, NULL) != 0) {
        free(j); fbk_remove(&h->tbl, id); return;
    }
    j->url = (char *)malloc(ul + 1);
    if (j->url == NULL) { pthread_mutex_destroy(&j->mu); free(j); fbk_remove(&h->tbl, id); return; }
    memcpy(j->url, url, ul + 1);
    j->fetch = h->fetch;
    j->fetch_ctx = h->fetch_ctx;
    j->id = id;
    if (h->async) {
        j->threaded = 1;
        if (pthread_create(&j->th, NULL, job_main, j) == 0) { h->slot[id].job = j; return; }
        j->threaded = 0;                              /* no thread: load inline instead */
    }
    job_run(j);
    integrate(h, j);
}

/* Collects the background loads that finished (owner thread). Returns how many are in flight. */
static int collect_jobs(fh_host *h) {
    int pending = 0;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        fh_job *j = h->slot[i].job;
        if (j == NULL) continue;
        pthread_mutex_lock(&j->mu);
        int done = j->done;
        pthread_mutex_unlock(&j->mu);
        if (!done) { ++pending; continue; }
        pthread_join(j->th, NULL);
        h->slot[i].job = NULL;
        integrate(h, j);
    }
    return pending;
}

void fh_set_async(fh_host *h, int on) {
    if (h != NULL) h->async = on ? 1 : 0;
}

static int find_child(const fh_host *h, int parent, int token) {
    for (int i = 1; i < FBK_MAX_FRAMES; ++i)
        if (h->tbl.f[i].used && h->tbl.f[i].parent == parent && h->slot[i].token == token) return i;
    return -1;
}

/* Token a receiving frame knows `from` by: from's own token when it is a direct child, otherwise
 * that of the ancestor of `from` that is a direct child of `dest`. -1 when dest is not an ancestor. */
static int token_seen_by(const fh_host *h, int dest, int from) {
    int cur = from;
    while (cur > 0 && h->tbl.f[cur].parent != dest) cur = h->tbl.f[cur].parent;
    return (cur > 0 && h->tbl.f[cur].used) ? h->slot[cur].token : -1;
}

static void post_op(fh_host *h, int from, const tab_ws_op *op) {
    const char *nl = memchr(op->data, '\n', op->len);
    if (nl == NULL) return;
    char target[FBK_ORIGIN_MAX + 8];
    size_t tl = (size_t)(nl - op->data);
    if (tl >= sizeof target) return;
    memcpy(target, op->data, tl);
    target[tl] = '\0';
    const char *json = nl + 1;
    size_t jl = op->len - tl - 1;

    fbk_rel rel;
    int child = 0;
    if (op->id == -1) rel = FBK_REL_PARENT;
    else if (op->id == -2) rel = FBK_REL_TOP;
    else if (op->id > 0) { rel = FBK_REL_CHILD; child = find_child(h, from, op->id); if (child < 0) return; }
    else return;

    int dest = -1;
    if (fbk_route(&h->tbl, from, rel, child, target, jl, &dest) != FBK_DELIVER) return;

    const char *sender_origin = fbk_origin(&h->tbl, from);
    if (sender_origin == NULL) return;
    char relstr[24];
    if (dest == from) return;
    if (h->tbl.f[dest].parent == from) {
        snprintf(relstr, sizeof relstr, "p");            /* the sender is the receiver's parent */
    } else {
        int tok = token_seen_by(h, dest, from);          /* the sender (or its ancestor) is a child */
        if (tok < 0) return;
        snprintf(relstr, sizeof relstr, "c%d", tok);
    }
    size_t sl = strlen(sender_origin), rl = strlen(relstr);
    char *msg = (char *)malloc(sl + 1 + rl + 1 + jl + 1);
    if (msg == NULL) return;
    memcpy(msg, sender_origin, sl); msg[sl] = '\n';
    memcpy(msg + sl + 1, relstr, rl); msg[sl + 1 + rl] = '\n';
    memcpy(msg + sl + rl + 2, json, jl);
    size_t ml = sl + rl + 2 + jl;
    msg[ml] = '\0';

    if (dest == 0) {
        h->top_msg(h->top_ctx, msg, ml);
    } else if (h->slot[dest].t != NULL && h->depth < FH_MAX_DEPTH) {
        tab_page pg;
        memset(&pg, 0, sizeof pg);
        if (tab_ws_event(h->slot[dest].t, 0, TAB_WSE_FRAME_MSG, 0, msg, ml, &pg) == TAB_OK) {
            h->slot[dest].next_timer_ms = pg.next_timer_ms;
            apply_ops(h, dest, pg.ws, pg.nws);
        }
        tab_page_free(&pg);
    }
    free(msg);
}

static void apply_ops(fh_host *h, int from, const tab_ws_op *ops, size_t n) {
    if (h->depth >= FH_MAX_DEPTH) return;
    h->depth++;
    for (size_t i = 0; i < n; ++i) {
        const tab_ws_op *op = &ops[i];
        if (op->kind == TAB_WS_FRAME_OPEN) {
            int id = -1;
            if (op->data == NULL || op->len >= FBK_URL_MAX || op->id <= 0) continue;
            if (from != 0 && h->slot[from].t == NULL) continue;
            if (find_child(h, from, op->id) >= 0) continue;
            if (fbk_add(&h->tbl, from, op->data, &id) != 0) continue;
            h->slot[id].token = op->id;
            load_frame(h, id, op->data);
        } else if (op->kind == TAB_WS_FRAME_CLOSE) {
            int c = find_child(h, from, op->id);
            if (c > 0) { fbk_remove(&h->tbl, c); reap(h); }
        } else if (op->kind == TAB_WS_FRAME_POST && op->data != NULL) {
            post_op(h, from, op);
        }
    }
    h->depth--;
}

void fh_apply_top(fh_host *h, const tab_page *page) {
    if (h == NULL || page == NULL) return;
    apply_ops(h, 0, page->ws, page->nws);
}

int fh_tick(fh_host *h, int elapsed_ms) {
    if (h == NULL) return -1;
    int pending = collect_jobs(h);
    int next = pending > 0 ? FH_POLL_MS : -1;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        if (h->slot[i].t == NULL) continue;
        tab_page pg;
        memset(&pg, 0, sizeof pg);
        if (tab_tick(h->slot[i].t, elapsed_ms, &pg) == TAB_OK) {
            h->slot[i].next_timer_ms = pg.next_timer_ms;
            if (pg.view != NULL) {
                pv_free(h->slot[i].view);
                h->slot[i].view = pg.view;
                pg.view = NULL;
                h->gen++;
            }
            if (fbk_origin(&h->tbl, i) != NULL) apply_ops(h, i, pg.ws, pg.nws);
        }
        tab_page_free(&pg);
        int t = h->slot[i].t != NULL ? h->slot[i].next_timer_ms : -1;
        if (t >= 0 && (next < 0 || t < next)) next = t;
    }
    return next;
}

unsigned fh_generation(const fh_host *h) { return h != NULL ? h->gen : 0; }

const pv_view *fh_frame_view(const fh_host *h, const char *url, tab **t_out) {
    if (t_out != NULL) *t_out = NULL;
    if (h == NULL || url == NULL) return NULL;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        const fh_slot *sl = &h->slot[i];
        if (sl->t != NULL && sl->view != NULL && sl->url != NULL && strcmp(sl->url, url) == 0) {
            if (t_out != NULL) *t_out = sl->t;
            return sl->view;
        }
    }
    return NULL;
}
