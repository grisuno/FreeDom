#ifndef FREEDOM_CSS_MQ_H
#define FREEDOM_CSS_MQ_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * css_mq -- Media Queries 4 evaluation (spec/css_mq.md). Pure: no I/O, no DOM,
 * no allocation. Device features answer the NORMALIZED desktop identity
 * (anti-fingerprinting); only the render width is real.
 */

#define CMQ_MAX_DEPTH 16   /* nested parentheses in one condition */
#define CMQ_TOK_MAX   128  /* bytes of one feature name or value */

typedef struct cmq_env {
    int width_px;      /* render viewport width */
    int height_px;     /* normalized viewport height */
    int prefers_dark;  /* 1: the user prefers a dark color scheme */
    int print;         /* 1: rendering for print */
} cmq_env;

/* 1 iff the media query list s[0,len) matches env; malformed/unknown parts fail
 * closed. An empty list matches (all). NULL s or env -> 0. */
int cmq_matches(const char *s, size_t len, const cmq_env *env);

#endif /* FREEDOM_CSS_MQ_H */
