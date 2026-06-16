#ifndef FREEDOM_RENDERER_H
#define FREEDOM_RENDERER_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * renderer — out-of-process, seccomp-confined parsing of untrusted content.
 *
 * Tab isolation: each render runs in its own forked, seccomp-hardened child
 * process; the parent never touches the hostile bytes and survives a child
 * crash/exploit (returning RD_ERR_RENDER). Combines os_sandbox + html_parse.
 *
 * See spec/renderer.md for the full contract.
 */

typedef enum rd_status {
    RD_OK = 0,
    RD_ERR_NULL_ARG,
    RD_ERR_TOO_LARGE,  /* input exceeded RD_MAX_INPUT */
    RD_ERR_SPAWN,      /* pipe()/fork() failed */
    RD_ERR_RENDER,     /* child failed/crashed (isolated): the parent is intact */
    RD_ERR_OOM
} rd_status;

typedef struct rd_result {
    rd_status status;
    char  *title;     /* owned; NUL-terminated; may be NULL */
    size_t title_len; /* excludes the trailing NUL */
    char  *text;      /* owned; NUL-terminated; may be NULL */
    size_t text_len;
} rd_result;

#define RD_MAX_INPUT ((size_t)(32u * 1024u * 1024u))
#define RD_MAX_FIELD ((size_t)(64u * 1024u * 1024u))

/* Renders untrusted HTML out-of-process and returns an inert title + text.
 * html == NULL or out == NULL => RD_ERR_NULL_ARG. On return, *out is populated
 * and must be released with rd_result_free. */
rd_status rd_render_html(const char *html, size_t len, rd_result *out);

/* Idempotent; safe on a zero-initialised struct and safe to call twice. */
void rd_result_free(rd_result *out);

#endif /* FREEDOM_RENDERER_H */
