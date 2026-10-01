/*
 * ws_hub — implementation: the trusted-side WebSocket connections of one page.
 * See spec/ws_hub.md.
 */

#define _POSIX_C_SOURCE 200809L

#include "ws_hub.h"

#include <curl/curl.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/socket.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Frames read per wh_on_readable call: a flooding peer cannot starve the UI loop. */
#define WH_READS_PER_PUMP 256
#define WH_RECV_CHUNK     16384u

typedef struct wh_conn {
    int       used;
    int       pending;   /* opening on a thread; ws not yet attached */
    int       id;
    uint64_t  token;     /* unique per open: a late or re-entrant result matches only it */
    sf_ws    *ws;
    char     *msg;       /* message being reassembled */
    size_t    len;
    int       binary;
} wh_conn;

struct wh_hub {
    wh_conn  c[WH_MAX];
    int      pipe_r, pipe_w;
    uint64_t seq;
};

/* One open, owned by its thread until handed over through the pipe. Every string
 * of the config is copied: the thread outlives the caller's buffers. */
typedef struct wh_job {
    int        wfd;       /* the thread's OWN dup of the pipe's write end */
    uint64_t   token;
    int        id;
    char      *url;
    sf_config  cfg;
    char      *strs[8];
    sf_ws     *ws;
    sf_status  st;
} wh_job;

static char *dup_str(const char *s) {
    if (s == NULL) return NULL;
    size_t n = strlen(s);
    if (n == (size_t)-1) return NULL;
    char *d = (char *)malloc(n + 1);
    if (d != NULL) memcpy(d, s, n + 1);
    return d;
}

static void job_free(wh_job *j) {
    if (j == NULL) return;
    free(j->url);
    for (size_t i = 0; i < sizeof j->strs / sizeof j->strs[0]; ++i) free(j->strs[i]);
    free(j);
}

/* Deep-copies one config string field into the job; 0, or -1 on OOM. */
static int job_str(wh_job *j, size_t slot, const char **field) {
    if (*field == NULL) return 0;
    j->strs[slot] = dup_str(*field);
    if (j->strs[slot] == NULL) return -1;
    *field = j->strs[slot];
    return 0;
}

static void *open_thread(void *arg) {
    wh_job *j = (wh_job *)arg;
    j->st = sf_ws_open(j->url, &j->cfg, &j->ws);
    /* MSG_NOSIGNAL: if the hub is gone the send fails with EPIPE instead of raising
     * SIGPIPE, whatever the process's signal disposition. */
    /* Once the pointer is sent the hub OWNS the job and may free it at once: read
     * everything this thread still needs (its fd) BEFORE the hand-over and never
     * touch j after a successful send. */
    int wfd = j->wfd;
    ssize_t w;
    do { w = send(wfd, &j, sizeof j, MSG_NOSIGNAL); } while (w < 0 && errno == EINTR);
    if (w != (ssize_t)sizeof j) {   /* hub gone: nobody will take it */
        sf_ws_close(j->ws);
        job_free(j);
    }
    close(wfd);
    return NULL;
}

static void conn_clear(wh_conn *c) {
    sf_ws_close(c->ws);
    free(c->msg);
    memset(c, 0, sizeof *c);
}

static wh_conn *find_id(wh_hub *h, int id) {
    for (size_t i = 0; i < WH_MAX; ++i)
        if (h->c[i].used && h->c[i].id == id) return &h->c[i];
    return NULL;
}

static wh_conn *find_token(wh_hub *h, uint64_t token) {
    for (size_t i = 0; i < WH_MAX; ++i)
        if (h->c[i].used && h->c[i].token == token) return &h->c[i];
    return NULL;
}

wh_hub *wh_new(void) {
    wh_hub *h = (wh_hub *)calloc(1, sizeof *h);
    if (h == NULL) return NULL;
    int p[2];
    if (socketpair(AF_UNIX, SOCK_STREAM | SOCK_CLOEXEC, 0, p) != 0) { free(h); return NULL; }
    (void)fcntl(p[0], F_SETFL, O_NONBLOCK);
    (void)fcntl(p[0], F_SETFD, FD_CLOEXEC);
    (void)fcntl(p[1], F_SETFD, FD_CLOEXEC);
    h->pipe_r = p[0];
    h->pipe_w = p[1];
    return h;
}

void wh_free(wh_hub *h) {
    if (h == NULL) return;
    wh_close_all(h);
    /* Drain finished jobs; a still-running thread's send to the closed pair fails
     * with EPIPE (MSG_NOSIGNAL) and it frees its own job. */
    wh_job *j = NULL;
    while (read(h->pipe_r, &j, sizeof j) == (ssize_t)sizeof j) {
        sf_ws_close(j->ws);
        job_free(j);
    }
    close(h->pipe_r);
    close(h->pipe_w);
    free(h);
}

int wh_notify_fd(const wh_hub *h) {
    return (h != NULL) ? h->pipe_r : -1;
}

int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg) {
    if (h == NULL || url == NULL) return -1;
    if (find_id(h, id) != NULL) return -1;
    wh_conn *slot = NULL;
    for (size_t i = 0; i < WH_MAX && slot == NULL; ++i)
        if (!h->c[i].used) slot = &h->c[i];
    if (slot == NULL) return -1;

    wh_job *j = (wh_job *)calloc(1, sizeof *j);
    if (j == NULL) return -1;
    j->url = dup_str(url);
    j->cfg = (cfg != NULL) ? *cfg : sf_config_default();
    j->cfg.progress_cb = NULL;
    j->cfg.progress_ctx = NULL;
    if (j->url == NULL
        || job_str(j, 0, &j->cfg.kex_groups) != 0 || job_str(j, 1, &j->cfg.user_agent) != 0
        || job_str(j, 2, &j->cfg.proxy_address) != 0 || job_str(j, 3, &j->cfg.username) != 0
        || job_str(j, 4, &j->cfg.password) != 0 || job_str(j, 5, &j->cfg.referrer_url) != 0
        || job_str(j, 6, &j->cfg.sec_fetch_dest) != 0
        || job_str(j, 7, &j->cfg.sec_fetch_mode) != 0) {
        job_free(j);
        return -1;
    }
    j->wfd = fcntl(h->pipe_w, F_DUPFD_CLOEXEC, 0);
    if (j->wfd < 0) { job_free(j); return -1; }
    j->id = id;
    j->token = ++h->seq;

    pthread_t th;
    pthread_attr_t at;
    if (pthread_attr_init(&at) != 0) { close(j->wfd); job_free(j); return -1; }
    (void)pthread_attr_setdetachstate(&at, PTHREAD_CREATE_DETACHED);
    int rc = pthread_create(&th, &at, open_thread, j);
    pthread_attr_destroy(&at);
    if (rc != 0) { close(j->wfd); job_free(j); return -1; }

    memset(slot, 0, sizeof *slot);
    slot->used = 1;
    slot->pending = 1;
    slot->id = id;
    slot->token = j->token;
    return 0;
}

void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx) {
    if (h == NULL) return;
    wh_job *j = NULL;
    while (read(h->pipe_r, &j, sizeof j) == (ssize_t)sizeof j) {
        wh_conn *c = find_token(h, j->token);
        if (c == NULL || !c->pending) {          /* closed meanwhile: drop silently */
            sf_ws_close(j->ws);
            job_free(j);
            continue;
        }
        int id = j->id;
        if (j->st == SF_OK && j->ws != NULL) {
            c->ws = j->ws;
            c->pending = 0;
            j->ws = NULL;
            job_free(j);
            if (emit != NULL) emit(ctx, id, WH_EV_OPEN, 0, NULL, 0);
        } else {
            sf_ws_close(j->ws);
            job_free(j);
            memset(c, 0, sizeof *c);
            if (emit != NULL) {
                emit(ctx, id, WH_EV_ERROR, 0, NULL, 0);
                emit(ctx, id, WH_EV_CLOSE, WH_CLOSE_ABNORMAL, NULL, 0);
            }
        }
    }
}

int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary) {
    if (h == NULL) return -1;
    wh_conn *c = find_id(h, id);
    if (c == NULL || c->pending || c->ws == NULL) return -1;
    return (sf_ws_send(c->ws, data, len, binary) == SF_OK) ? 0 : -1;
}

void wh_close(wh_hub *h, int id) {
    if (h == NULL) return;
    wh_conn *c = find_id(h, id);
    if (c != NULL) conn_clear(c);   /* a pending open's result will not match any slot */
}

void wh_close_all(wh_hub *h) {
    if (h == NULL) return;
    for (size_t i = 0; i < WH_MAX; ++i)
        if (h->c[i].used) conn_clear(&h->c[i]);
}

size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap) {
    if (h == NULL || out == NULL || ids == NULL) return 0;
    size_t n = 0;
    for (size_t i = 0; i < WH_MAX && n < cap; ++i) {
        const wh_conn *c = &h->c[i];
        if (!c->used || c->pending || c->ws == NULL) continue;
        int fd = sf_ws_fd(c->ws);
        if (fd < 0) continue;
        out[n].fd = fd;
        out[n].events = POLLIN;
        out[n].revents = 0;
        ids[n] = c->id;
        ++n;
    }
    return n;
}

/* Frees the connection and reports an abnormal closure. */
static void fail_conn(wh_conn *c, int id, wh_emit_fn emit, void *ctx) {
    conn_clear(c);
    if (emit != NULL) {
        emit(ctx, id, WH_EV_ERROR, 0, NULL, 0);
        emit(ctx, id, WH_EV_CLOSE, WH_CLOSE_ABNORMAL, NULL, 0);
    }
}

void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx) {
    if (h == NULL) return;
    wh_conn *c = find_id(h, id);
    if (c == NULL || c->pending || c->ws == NULL) return;
    uint64_t token = c->token;
    char *buf = (char *)malloc(WH_RECV_CHUNK);
    if (buf == NULL) return;
    for (int n = 0; n < WH_READS_PER_PUMP; ++n) {
        /* An emit re-enters the page, which may close this very socket. */
        c = find_token(h, token);
        if (c == NULL) break;
        size_t got = 0, left = 0;
        int flags = 0;
        sf_status st = sf_ws_recv(c->ws, buf, WH_RECV_CHUNK, &got, &flags, &left);
        if (st != SF_OK) { fail_conn(c, id, emit, ctx); break; }
        if (got == 0 && flags == 0) break;                 /* nothing pending */
        if (flags & CURLWS_CLOSE) {
            int code = 1005;                               /* no status code present */
            if (got >= 2)
                code = (int)(((unsigned char)buf[0] << 8) | (unsigned char)buf[1]);
            const char *reason = (got > 2) ? buf + 2 : NULL;
            size_t rlen = (got > 2) ? got - 2 : 0;
            conn_clear(c);
            if (emit != NULL) emit(ctx, id, WH_EV_CLOSE, code, reason, rlen);
            break;
        }
        if (flags & (CURLWS_PING | CURLWS_PONG)) continue; /* control: curl answers pings */
        if (c->len == 0) c->binary = (flags & CURLWS_BINARY) != 0;
        if (got > SF_WS_MAX_MESSAGE - c->len) { fail_conn(c, id, emit, ctx); break; }
        char *grown = (char *)realloc(c->msg, c->len + got + 1);
        if (grown == NULL) { fail_conn(c, id, emit, ctx); break; }
        c->msg = grown;
        memcpy(c->msg + c->len, buf, got);
        c->len += got;
        c->msg[c->len] = '\0';
        if (left == 0 && (flags & CURLWS_CONT) == 0) {
            char *msg = c->msg;
            size_t len = c->len;
            int kind = c->binary ? WH_EV_BINARY : WH_EV_TEXT;
            c->msg = NULL;
            c->len = 0;
            if (emit != NULL) emit(ctx, id, kind, 0, msg, len);
            free(msg);
        }
    }
    free(buf);
}

size_t wh_count(const wh_hub *h) {
    if (h == NULL) return 0;
    size_t n = 0;
    for (size_t i = 0; i < WH_MAX; ++i)
        if (h->c[i].used && !h->c[i].pending) ++n;
    return n;
}
