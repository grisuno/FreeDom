#ifndef FREEDOM_CSS_IMPORT_H
#define FREEDOM_CSS_IMPORT_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>

/*
 * css_import -- pure reader of a stylesheet's @import prelude (spec/css_import.md).
 *
 * No I/O, no allocation, no global state. It only says WHAT a sheet imports and
 * under which condition; the caller fetches each URL through the same gated
 * fetcher as a <link rel=stylesheet> and wraps the imported text with ci_wrap so
 * the existing parser applies its layer/supports/media gate.
 */

#define CI_URL_MAX      2048   /* longest import URL kept (raw, unresolved) */
#define CI_COND_MAX      512   /* longest layer name / supports() / media list */
#define CI_MAX_DEPTH       4   /* caller: nesting bound (breaks a -> b -> a) */
#define CI_MAX_PER_PAGE   64   /* caller: imports followed per load */
#define CI_MAX_PER_SHEET  32   /* caller: imports read from one sheet */

typedef struct ci_import {
    char url[CI_URL_MAX];
    int  has_layer;               /* 1: `layer` or `layer(name)` was given */
    char layer[CI_COND_MAX];      /* "" = anonymous layer */
    char supports[CI_COND_MAX];   /* condition without outer parens, "" = none */
    char media[CI_COND_MAX];      /* media query list, "" = all */
} ci_import;

/* Reads the leading @import rules of css[0,len) into out (at most cap). Skips
 * whitespace, comments, @charset and @layer statements; stops at the first other
 * rule. A malformed or oversized import is ignored. NULL/0 args => 0. */
size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);

/* Builds the wrapper for one import: open = "@layer N {@supports (S) {@media M {"
 * (only the parts present) and close = the matching braces. No condition => both
 * empty. Returns 0, or -1 when an argument is NULL or a buffer is too small. */
int ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);

/* 1 iff every comment and string in css[0,len) terminates and the braces outside
 * them never go negative and end at zero; else 0. NULL => 0 (empty text => 1). */
int ci_balanced(const char *css, size_t len);

#endif /* FREEDOM_CSS_IMPORT_H */
