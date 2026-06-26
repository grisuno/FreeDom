/*
 * renderer — implementation: fork a seccomp-confined child to parse untrusted
 * HTML and return an inert title + text over a pipe. The parent never parses
 * the hostile bytes; a child crash yields RD_ERR_RENDER, never a parent crash.
 */

#define _POSIX_C_SOURCE 200809L

#include "renderer.h"

#include "html_parse.h"
#include "os_sandbox.h"

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/* --- framed pipe I/O --- */

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

/* --- child: confine, parse, emit framed result, never return to caller --- */

static void child_render(int wfd, const char *html, size_t len) {
    /* Confine before touching untrusted content: a parse that tried to open a
     * file, a socket or exec would be killed by the kernel. Drop dumpability first
     * so a crash cannot spill the parsed content to a core file. */
    os_no_dump();
    if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(90);

    hp_document *doc = NULL;
    if (hp_parse(html, len, NULL, &doc) != HP_OK) _exit(91);

    size_t tl = 0, xl = 0;
    char *title = hp_get_title(doc, &tl);
    char *text = hp_extract_text(doc, &xl);

    int ok = (title != NULL && text != NULL)
          && write_full(wfd, &tl, sizeof tl) == 0
          && (tl == 0 || write_full(wfd, title, tl) == 0)
          && write_full(wfd, &xl, sizeof xl) == 0
          && (xl == 0 || write_full(wfd, text, xl) == 0);

    hp_free(title);
    hp_free(text);
    hp_document_free(doc);
    _exit(ok ? 0 : 92);
}

/* --- parent: read one length-prefixed owned field (capped) --- */

static int read_field(int fd, char **out, size_t *out_len) {
    size_t n = 0;
    if (read_full(fd, &n, sizeof n) != 0) return -1;
    if (n > RD_MAX_FIELD) return -1; /* anti-amplification: reject huge lengths */

    char *buf = (char *)malloc(n + 1);
    if (buf == NULL) return -1;
    if (n != 0 && read_full(fd, buf, n) != 0) { free(buf); return -1; }
    buf[n] = '\0';
    *out = buf;
    *out_len = n;
    return 0;
}

/* --- public --- */

rd_status rd_render_html(const char *html, size_t len, rd_result *out) {
    if (html == NULL || out == NULL) return RD_ERR_NULL_ARG;
    memset(out, 0, sizeof *out);
    if (len > RD_MAX_INPUT) { out->status = RD_ERR_TOO_LARGE; return RD_ERR_TOO_LARGE; }

    int fds[2];
    if (pipe(fds) != 0) { out->status = RD_ERR_SPAWN; return RD_ERR_SPAWN; }

    pid_t pid = fork();
    if (pid < 0) {
        close(fds[0]);
        close(fds[1]);
        out->status = RD_ERR_SPAWN;
        return RD_ERR_SPAWN;
    }

    if (pid == 0) {
        close(fds[0]);
        child_render(fds[1], html, len);
        _exit(93); /* unreachable */
    }

    /* Parent: never parses untrusted bytes; only reads the inert result. */
    close(fds[1]);

    char *title = NULL, *text = NULL;
    size_t tl = 0, xl = 0;
    int read_ok = (read_field(fds[0], &title, &tl) == 0)
               && (read_field(fds[0], &text, &xl) == 0);
    close(fds[0]);

    int st = 0;
    while (waitpid(pid, &st, 0) < 0 && errno == EINTR) { /* retry */ }

    int child_ok = read_ok && WIFEXITED(st) && WEXITSTATUS(st) == 0;
    if (!child_ok) {
        free(title);
        free(text);
        out->status = RD_ERR_RENDER;
        return RD_ERR_RENDER;
    }

    out->title = title;
    out->title_len = tl;
    out->text = text;
    out->text_len = xl;
    out->status = RD_OK;
    return RD_OK;
}

void rd_result_free(rd_result *out) {
    if (out == NULL) return;
    free(out->title);
    free(out->text);
    out->title = NULL;
    out->text = NULL;
    out->title_len = 0;
    out->text_len = 0;
    out->status = RD_OK;
}
