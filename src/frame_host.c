/*
 * frame_host -- trusted-parent side of iframes (spec/frame_broker.md section 4).
 * Every frame is its own confined worker; this module only routes strings between them, after
 * frame_broker has decided the addressee and the origin match.
 */
#include "frame_host.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "frame_broker.h"

typedef struct fh_slot {
    tab *t;
    int  token;          /* the token the PARENT document's JS gave this <iframe> */
    int  next_timer_ms;  /* -1 when none */
} fh_slot;

struct fh_host {
    fbk_table     tbl;
    fh_slot       slot[FBK_MAX_FRAMES];
    tab_fetch_fn  fetch;
    void         *fetch_ctx;
    fh_top_msg_fn top_msg;
    void         *top_ctx;
    int           depth;
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

/* Closes the worker of every frame that is no longer in the table. */
static void reap(fh_host *h) {
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        if (h->slot[i].t != NULL && fbk_origin(&h->tbl, i) == NULL) {
            tab_close(h->slot[i].t);
            h->slot[i].t = NULL;
            h->slot[i].next_timer_ms = -1;
        }
    }
}

void fh_free(fh_host *h) {
    if (h == NULL) return;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        if (h->slot[i].t != NULL) tab_close(h->slot[i].t);
    }
    free(h);
}

int fh_count(const fh_host *h) {
    int n = 0;
    if (h == NULL) return 0;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) if (h->slot[i].t != NULL) ++n;
    return n;
}

/* Loads the document of frame `id` (already registered in the table). On any failure the frame is
 * removed again: the table never lists a frame without a worker. */
static void load_frame(fh_host *h, int id, const char *url) {
    int status = 0;
    char *body = NULL, *ctype = NULL;
    size_t blen = 0;
    tab *t = NULL;
    if (h->fetch(h->fetch_ctx, "GET", url, NULL, 0, &status, &body, &blen, &ctype) != 0
        || status < 200 || status >= 300 || body == NULL || blen == 0 || blen > TAB_MAX_INPUT) {
        free(body); free(ctype);
        fbk_remove(&h->tbl, id);
        return;
    }
    free(ctype);
    if (tab_open(&t) != TAB_OK) { free(body); fbk_remove(&h->tbl, id); return; }
    tab_set_net_allowed(t, 1);
    tab_set_css_allowed(t, 1);
    tab_set_fetcher(t, h->fetch, h->fetch_ctx);
    tab_set_frame_id(t, id);
    h->slot[id].t = t;
    tab_page pg;
    memset(&pg, 0, sizeof pg);
    if (tab_load_full(t, body, blen, url, 1, 0, 0, &pg) != TAB_OK) {
        free(body);
        tab_page_free(&pg);
        fbk_remove(&h->tbl, id);
        reap(h);
        return;
    }
    free(body);
    h->slot[id].next_timer_ms = pg.next_timer_ms;
    if (fbk_origin(&h->tbl, id) != NULL) apply_ops(h, id, pg.ws, pg.nws);
    tab_page_free(&pg);
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
    int next = -1;
    for (int i = 1; i < FBK_MAX_FRAMES; ++i) {
        if (h->slot[i].t == NULL) continue;
        tab_page pg;
        memset(&pg, 0, sizeof pg);
        if (tab_tick(h->slot[i].t, elapsed_ms, &pg) == TAB_OK) {
            h->slot[i].next_timer_ms = pg.next_timer_ms;
            if (fbk_origin(&h->tbl, i) != NULL) apply_ops(h, i, pg.ws, pg.nws);
        }
        tab_page_free(&pg);
        int t = h->slot[i].t != NULL ? h->slot[i].next_timer_ms : -1;
        if (t >= 0 && (next < 0 || t < next)) next = t;
    }
    return next;
}
