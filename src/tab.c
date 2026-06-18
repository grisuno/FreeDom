/*
 * tab — implementation: a long-lived, sandboxed per-tab worker process.
 *
 * Evolved from the one-shot renderer. tab_open forks a child that confines
 * itself once (Landlock no-FS, best-effort; seccomp-bpf, mandatory/fail-closed)
 * before touching any content, then serves a request loop over two pipes. Inside
 * the confinement the child parses hostile HTML (html_parse), builds the inert
 * DOM (dom), and runs untrusted JS (js_sandbox) bound to that DOM plus the
 * normalized anti-fp environment (js_dom + js_env). The parent never parses or
 * executes the hostile bytes; it drives the child and survives a child crash,
 * reporting TAB_ERR_DEAD instead of dying with it.
 */

#define _GNU_SOURCE

#include "tab.h"

#include "dom.h"
#include "html_parse.h"
#include "js_dom.h"
#include "js_env.h"
#include "js_sandbox.h"
#include "os_sandbox.h"
#include "page_view.h"

#include <errno.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/random.h>
#include <sys/wait.h>

/* Fixed, normalized output size; fp_bucket_screen snaps it the same for all. */
#define TAB_SCREEN_W 1920
#define TAB_SCREEN_H 1080

/* Anti-amplification cap on the number of display-list runs the parent will
 * accept from the (possibly exploited) child. Plenty for any real page. */
#define TAB_MAX_RUNS ((size_t)(2u * 1024u * 1024u))

/* Request opcodes (parent -> child). */
enum { OP_LOAD = 1, OP_EVAL = 2, OP_QUIT = 3 };

/* Handshake bytes (child -> parent) after the confinement attempt. */
enum { TAB_READY = 0x55, TAB_NO_CONFINE = 0xAA };

/* --- framed pipe I/O (EINTR-safe, all-or-nothing) --- */

static int write_full(int fd, const void *buf, size_t n) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t done = 0;
    while (done < n) {
        ssize_t w = write(fd, p + done, n - done);
        if (w < 0) { if (errno == EINTR) continue; return -1; }
        done += (size_t)w;
    }
    return 0;
}

static int read_full(int fd, void *buf, size_t n) {
    uint8_t *p = (uint8_t *)buf;
    size_t got = 0;
    while (got < n) {
        ssize_t r = read(fd, p + got, n - got);
        if (r < 0) { if (errno == EINTR) continue; return -1; }
        if (r == 0) return -1; /* EOF before n bytes */
        got += (size_t)r;
    }
    return 0;
}

/* =========================== child side ============================== */

typedef struct child_state {
    hp_document *doc;
    dom_index   *idx;
    js_context  *js;
    uint64_t     session_key;
} child_state;

static void child_reset_page(child_state *cs) {
    if (cs->js  != NULL) { js_context_free(cs->js);  cs->js  = NULL; }
    if (cs->idx != NULL) { dom_free(cs->idx);          cs->idx = NULL; }
    if (cs->doc != NULL) { hp_document_free(cs->doc);  cs->doc = NULL; }
}

/* Parse + index + fresh JS context bound to the page and the anti-fp env. */
static int child_load(child_state *cs, const char *html, size_t len) {
    child_reset_page(cs);

    hp_document *doc = NULL;
    if (hp_parse(html, len, NULL, &doc) != HP_OK) return -1;

    dom_index *idx = NULL;
    if (dom_build(doc, &idx) != DOM_OK) { hp_document_free(doc); return -1; }

    js_context *js = NULL;
    if (js_context_new(NULL, &js) != JS_OK) {
        dom_free(idx); hp_document_free(doc); return -1;
    }
    if (jd_install(js, idx) != JD_OK
     || je_install(js, TAB_SCREEN_W, TAB_SCREEN_H) != JE_OK
     || je_install_canvas(js, cs->session_key) != JE_OK) {
        js_context_free(js); dom_free(idx); hp_document_free(doc); return -1;
    }

    cs->doc = doc; cs->idx = idx; cs->js = js;
    return 0;
}

/* Serialises the display list:
 *   [count]( kind,heading,break, text, href, src, img_w,img_h, fg_rgb,
 *            input_type,form_id,form_method, name, value )*
 * with each string length-prefixed (a length of 0 means absent). The fixed-width
 * fields travel for every run so a hostile child cannot desync the stream by
 * varying the per-run layout; non-image runs carry an empty src and -1 dimensions,
 * a run without an author color carries fg_rgb == -1, and non-input runs carry an
 * empty name/value, form_id == -1 and form_method == 0. */
static int write_view(int wfd, const pv_view *v) {
    size_t n = pv_count(v);
    if (write_full(wfd, &n, sizeof n) != 0) return -1;
    for (size_t i = 0; i < n; ++i) {
        const pv_run *r = pv_at(v, i);
        int32_t kind = (int32_t)r->kind;
        int32_t heading = (int32_t)r->heading;
        int32_t brk = (int32_t)r->block_break;
        int32_t img_w = (int32_t)r->img_w;
        int32_t img_h = (int32_t)r->img_h;
        int32_t fg = (int32_t)r->fg_rgb;
        int32_t itype = (int32_t)r->input_type;
        int32_t fid = (int32_t)r->form_id;
        int32_t method = (int32_t)r->form_method;
        size_t tlen = (r->text != NULL) ? strlen(r->text) : 0;
        size_t hlen = (r->href != NULL) ? strlen(r->href) : 0;
        size_t slen = (r->src != NULL) ? strlen(r->src) : 0;
        size_t nmlen = (r->name != NULL) ? strlen(r->name) : 0;
        size_t vllen = (r->value != NULL) ? strlen(r->value) : 0;
        if (write_full(wfd, &kind, sizeof kind) != 0) return -1;
        if (write_full(wfd, &heading, sizeof heading) != 0) return -1;
        if (write_full(wfd, &brk, sizeof brk) != 0) return -1;
        if (write_full(wfd, &tlen, sizeof tlen) != 0) return -1;
        if (tlen != 0 && write_full(wfd, r->text, tlen) != 0) return -1;
        if (write_full(wfd, &hlen, sizeof hlen) != 0) return -1;
        if (hlen != 0 && write_full(wfd, r->href, hlen) != 0) return -1;
        if (write_full(wfd, &slen, sizeof slen) != 0) return -1;
        if (slen != 0 && write_full(wfd, r->src, slen) != 0) return -1;
        if (write_full(wfd, &img_w, sizeof img_w) != 0) return -1;
        if (write_full(wfd, &img_h, sizeof img_h) != 0) return -1;
        if (write_full(wfd, &fg, sizeof fg) != 0) return -1;
        if (write_full(wfd, &itype, sizeof itype) != 0) return -1;
        if (write_full(wfd, &fid, sizeof fid) != 0) return -1;
        if (write_full(wfd, &method, sizeof method) != 0) return -1;
        if (write_full(wfd, &nmlen, sizeof nmlen) != 0) return -1;
        if (nmlen != 0 && write_full(wfd, r->name, nmlen) != 0) return -1;
        if (write_full(wfd, &vllen, sizeof vllen) != 0) return -1;
        if (vllen != 0 && write_full(wfd, r->value, vllen) != 0) return -1;
    }
    return 0;
}

/* Response: [ok:int32][title_len][title][text_len][text][view]. On any failure
 * the page is reset and ok==0 is reported (no partial/leaked state). */
static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len) {
    char  *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    pv_view *view = NULL;
    int ok = (child_load(cs, html, len) == 0);
    if (ok) {
        title = hp_get_title(cs->doc, &tl);
        text  = hp_extract_text(cs->doc, &xl);
        if (title == NULL || text == NULL || pv_build(cs->doc, &view) != PV_OK) {
            ok = 0;
            child_reset_page(cs);
        }
    }

    int32_t k = ok ? 1 : 0;
    if (write_full(wfd, &k, sizeof k) == 0 && ok) {
        (void)(write_full(wfd, &tl, sizeof tl) == 0
            && (tl == 0 || write_full(wfd, title, tl) == 0)
            && write_full(wfd, &xl, sizeof xl) == 0
            && (xl == 0 || write_full(wfd, text, xl) == 0)
            && write_view(wfd, view) == 0);
    }
    hp_free(title);
    hp_free(text);
    pv_free(view);
}

/* Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a
 * worker-level failure (no page loaded); a JS-level error is ok==1 with the
 * exception flag set. */
static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len) {
    if (cs->js == NULL) {
        int32_t k = 0;
        (void)write_full(wfd, &k, sizeof k);
        return;
    }

    js_result r;
    js_status s = js_eval(cs->js, js, len, &r);
    int32_t  ok = 1;
    int32_t  is_exc = (s != JS_OK) ? 1 : 0;
    const char *val = (r.value != NULL) ? r.value : "";
    size_t   vlen = (r.value != NULL) ? r.value_len : 0;

    if (write_full(wfd, &ok, sizeof ok) == 0) {
        (void)(write_full(wfd, &is_exc, sizeof is_exc) == 0
            && write_full(wfd, &vlen, sizeof vlen) == 0
            && (vlen == 0 || write_full(wfd, val, vlen) == 0));
    }
    js_result_free(&r);
}

static uint64_t gen_session_key(void) {
    uint64_t k = 0;
    uint8_t *p = (uint8_t *)&k;
    size_t got = 0;
    while (got < sizeof k) {
        ssize_t r = getrandom(p + got, sizeof k - got, 0);
        if (r < 0) { if (errno == EINTR) continue; break; }
        got += (size_t)r;
    }
    if (got < sizeof k) { /* fallback: still distinct per process start */
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        k ^= ((uint64_t)ts.tv_sec << 20) ^ (uint64_t)ts.tv_nsec
           ^ ((uint64_t)getpid() << 1);
    }
    return k;
}

/* The confined request loop. Never returns to the caller (always _exit). */
static void child_main(int rfd, int wfd) {
    child_state cs;
    memset(&cs, 0, sizeof cs);
    cs.session_key = gen_session_key();

    /* Confine before any content. Landlock is best-effort defense in depth
     * (seccomp already excludes open/socket/exec); seccomp is mandatory: if it
     * cannot be installed, report not-confined and exit (fail closed). */
    os_landlock_restrict(NULL, 0);
    uint8_t hs = (os_harden(OS_VIOLATION_KILL) == OS_OK) ? TAB_READY : TAB_NO_CONFINE;
    if (write_full(wfd, &hs, 1) != 0 || hs != TAB_READY) {
        _exit(hs == TAB_READY ? 0 : 70);
    }

    for (;;) {
        uint8_t op;
        if (read_full(rfd, &op, 1) != 0) break; /* EOF / error => quit */
        if (op == OP_QUIT) break;
        if (op != OP_LOAD && op != OP_EVAL) break; /* protocol desync */

        size_t len = 0;
        if (read_full(rfd, &len, sizeof len) != 0) break;
        if (len > TAB_MAX_INPUT) break; /* parent enforces; defensive */

        char *buf = (char *)malloc(len + 1);
        if (buf == NULL) break;
        if (len != 0 && read_full(rfd, buf, len) != 0) { free(buf); break; }
        buf[len] = '\0';

        if (op == OP_LOAD) child_handle_load(wfd, &cs, buf, len);
        else               child_handle_eval(wfd, &cs, buf, len);
        free(buf);
    }

    child_reset_page(&cs);
    _exit(0);
}

/* =========================== parent side ============================= */

struct tab {
    pid_t pid;
    int   req_fd;   /* parent writes requests here */
    int   resp_fd;  /* parent reads responses here */
    int   alive;
    int   reaped;   /* the child has been waited on; do not kill/wait again */
};

/* A write to a dead child must not kill the parent with SIGPIPE. Idempotent;
 * no module-level mutable state of our own (the disposition is process-wide). */
static void ignore_sigpipe(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGPIPE, &sa, NULL);
}

static void tab_refresh_alive(tab *t) {
    if (t == NULL || t->reaped || t->pid <= 0) return;
    int st;
    pid_t r = waitpid(t->pid, &st, WNOHANG);
    if (r == t->pid)                   { t->alive = 0; t->reaped = 1; }
    else if (r < 0 && errno == ECHILD) { t->alive = 0; t->reaped = 1; }
    /* r == 0: still running, liveness unchanged. */
}

/* Read one length-prefixed owned field from the child, capped against
 * amplification. *out is NUL-terminated. */
static int read_field(int fd, char **out, size_t *out_len) {
    size_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n > TAB_MAX_INPUT) return -1;
    char *buf = (char *)malloc(n + 1);
    if (buf == NULL) return -1;
    if (n != 0 && read_full(fd, buf, n) != 0) { free(buf); return -1; }
    buf[n] = '\0';
    *out = buf;
    *out_len = n;
    return 0;
}

/* Reads a display list serialised by write_view into a fresh pv_view. The run
 * count and each field are capped against amplification from a hostile child. */
static int read_view(int fd, pv_view **out) {
    *out = NULL;
    size_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n > TAB_MAX_RUNS) return -1;

    pv_view *v = pv_new();
    if (v == NULL) return -1;

    for (size_t i = 0; i < n; ++i) {
        int32_t kind = 0, heading = 0, brk = 0, img_w = -1, img_h = -1, fg = -1;
        int32_t itype = 0, fid = -1, method = 0;
        if (read_full(fd, &kind, sizeof kind) != 0
         || read_full(fd, &heading, sizeof heading) != 0
         || read_full(fd, &brk, sizeof brk) != 0) {
            pv_free(v);
            return -1;
        }
        char *text = NULL, *href = NULL, *src = NULL, *name = NULL, *value = NULL;
        size_t tl = 0, hl = 0, sl = 0, nl = 0, vl = 0;
        if (read_field(fd, &text, &tl) != 0) { pv_free(v); return -1; }
        if (read_field(fd, &href, &hl) != 0) { free(text); pv_free(v); return -1; }
        if (read_field(fd, &src, &sl) != 0) { free(text); free(href); pv_free(v); return -1; }
        if (read_full(fd, &img_w, sizeof img_w) != 0
         || read_full(fd, &img_h, sizeof img_h) != 0
         || read_full(fd, &fg, sizeof fg) != 0
         || read_full(fd, &itype, sizeof itype) != 0
         || read_full(fd, &fid, sizeof fid) != 0
         || read_full(fd, &method, sizeof method) != 0) {
            free(text); free(href); free(src); pv_free(v); return -1;
        }
        if (read_field(fd, &name, &nl) != 0) { free(text); free(href); free(src); pv_free(v); return -1; }
        if (read_field(fd, &value, &vl) != 0) {
            free(text); free(href); free(src); free(name); pv_free(v); return -1;
        }

        pv_status st;
        if (kind == PV_INPUT) {
            st = pv_append_input(v, heading, brk, (pv_input_type)itype, text,
                                 (nl > 0) ? name : NULL, (vl > 0) ? value : NULL,
                                 (hl > 0) ? href : NULL, (int)fid, (int)method);
        } else if (kind == PV_IMAGE && sl > 0) {
            st = pv_append_image(v, heading, brk, text, src, img_w, img_h);
        } else {
            pv_kind k = (kind == PV_LINK && hl > 0) ? PV_LINK : PV_TEXT;
            st = pv_append(v, k, heading, brk, text, (hl > 0) ? href : NULL);
        }
        free(text);
        free(href);
        free(src);
        free(name);
        free(value);
        if (st != PV_OK) { pv_free(v); return -1; }
        if (kind != PV_INPUT) pv_set_color(v, (int)fg);
    }

    *out = v;
    return 0;
}

/* Sends [op][len][payload]; classifies a transport failure as dead vs io. */
static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len) {
    if (write_full(t->req_fd, &op, 1) != 0
     || write_full(t->req_fd, &len, sizeof len) != 0
     || (len != 0 && write_full(t->req_fd, payload, len) != 0)) {
        tab_refresh_alive(t);
        return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
    }
    return TAB_OK;
}

static tab_status io_failure(tab *t) {
    tab_refresh_alive(t);
    return t->alive ? TAB_ERR_IO : TAB_ERR_DEAD;
}

tab_status tab_open(tab **out) {
    if (out == NULL) return TAB_ERR_NULL_ARG;
    *out = NULL;

    int req[2], resp[2];
    if (pipe(req) != 0) return TAB_ERR_SPAWN;
    if (pipe(resp) != 0) {
        close(req[0]); close(req[1]);
        return TAB_ERR_SPAWN;
    }

    ignore_sigpipe();

    pid_t pid = fork();
    if (pid < 0) {
        close(req[0]); close(req[1]); close(resp[0]); close(resp[1]);
        return TAB_ERR_SPAWN;
    }
    if (pid == 0) {
        close(req[1]); close(resp[0]);
        child_main(req[0], resp[1]);
        _exit(0); /* unreachable */
    }

    /* Parent: keep the request-write and response-read ends only. */
    close(req[0]);
    close(resp[1]);

    /* Confirm the child confined itself before trusting it with content. */
    uint8_t hs = 0;
    if (read_full(resp[0], &hs, 1) != 0 || hs != TAB_READY) {
        close(req[1]); close(resp[0]);
        int st; while (waitpid(pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }
        return TAB_ERR_CONFINE;
    }

    tab *t = (tab *)calloc(1, sizeof *t);
    if (t == NULL) {
        close(req[1]); close(resp[0]);
        kill(pid, SIGKILL);
        int st; while (waitpid(pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }
        return TAB_ERR_OOM;
    }
    t->pid = pid;
    t->req_fd = req[1];
    t->resp_fd = resp[0];
    t->alive = 1;
    t->reaped = 0;
    *out = t;
    return TAB_OK;
}

tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out) {
    if (t == NULL || out == NULL || html == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > TAB_MAX_INPUT) return TAB_ERR_TOO_LARGE;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    tab_status sr = send_request(t, OP_LOAD, html, len);
    if (sr != TAB_OK) return sr;

    int32_t ok = 0;
    if (read_full(t->resp_fd, &ok, sizeof ok) != 0) return io_failure(t);
    if (!ok) return TAB_ERR_RENDER;

    char *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    if (read_field(t->resp_fd, &title, &tl) != 0
     || read_field(t->resp_fd, &text, &xl) != 0) {
        free(title); free(text);
        return io_failure(t);
    }
    pv_view *view = NULL;
    if (read_view(t->resp_fd, &view) != 0) {
        free(title); free(text);
        return io_failure(t);
    }
    out->title = title; out->title_len = tl;
    out->text  = text;  out->text_len  = xl;
    out->view  = view;
    return TAB_OK;
}

tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out) {
    if (t == NULL || out == NULL || js == NULL) return TAB_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > TAB_MAX_INPUT) return TAB_ERR_TOO_LARGE;

    tab_refresh_alive(t);
    if (!t->alive) return TAB_ERR_DEAD;

    tab_status sr = send_request(t, OP_EVAL, js, len);
    if (sr != TAB_OK) return sr;

    int32_t ok = 0;
    if (read_full(t->resp_fd, &ok, sizeof ok) != 0) return io_failure(t);
    if (!ok) return TAB_ERR_SCRIPT; /* no page loaded / worker-level failure */

    int32_t is_exc = 0;
    if (read_full(t->resp_fd, &is_exc, sizeof is_exc) != 0) return io_failure(t);

    char *val = NULL;
    size_t vlen = 0;
    if (read_field(t->resp_fd, &val, &vlen) != 0) return io_failure(t);

    out->value = val;
    out->value_len = vlen;
    out->is_exception = is_exc ? 1 : 0;
    return TAB_OK;
}

int tab_alive(const tab *t) {
    if (t == NULL) return 0;
    tab_refresh_alive((tab *)t);
    return t->alive;
}

pid_t tab_child_pid(const tab *t) {
    return (t != NULL) ? t->pid : -1;
}

void tab_close(tab *t) {
    if (t == NULL) return;
    if (t->req_fd >= 0) close(t->req_fd);   /* EOF => the child quits its loop */
    if (t->resp_fd >= 0) close(t->resp_fd);
    if (t->pid > 0 && !t->reaped) {
        kill(t->pid, SIGKILL); /* defensive: guarantee prompt teardown */
        int st;
        while (waitpid(t->pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }
    }
    free(t);
}

void tab_page_free(tab_page *p) {
    if (p == NULL) return;
    free(p->title);
    free(p->text);
    pv_free(p->view);
    p->title = NULL;
    p->text = NULL;
    p->view = NULL;
    p->title_len = 0;
    p->text_len = 0;
}

void tab_eval_result_free(tab_eval_result *r) {
    if (r == NULL) return;
    free(r->value);
    r->value = NULL;
    r->value_len = 0;
    r->is_exception = 0;
}
