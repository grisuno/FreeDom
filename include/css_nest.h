/*
 * css_nest -- CSS Nesting by desugaring (spec/css_nest.md). Pure: no I/O, no global
 * state, bounded output.
 *
 * The flat parser cut `P{d; & > p{...}}` at the first `}`. Flattening the TEXT before
 * it is parsed keeps the parser, the cascade, the selector index and the @media gate
 * unchanged: a nested rule becomes an ordinary rule with its selector resolved.
 */
#ifndef FREEDOM_CSS_NEST_H
#define FREEDOM_CSS_NEST_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>

#define CN_MAX_DEPTH        8    /* nesting levels followed; deeper blocks are dropped */
#define CN_MAX_SELECTORS   64    /* resolved selectors of one nested rule (cross product) */
#define CN_MAX_OUT_FACTOR   8    /* output bound: factor x input + CN_OUT_SLACK */
#define CN_OUT_SLACK    65536

typedef enum cn_status { CN_OK = 0, CN_ERR_ARG = -1, CN_ERR_OOM = -2 } cn_status;

/* 1 iff some style rule's block holds a nested block (a rule or a conditional at-rule).
 * Linear, allocation-free. 0 => the caller keeps the text as it is. NULL => 0. */
int cn_has_nesting(const char *css, size_t len);

/* Writes a nesting-free equivalent of css[0,len) into a fresh NUL-terminated buffer
 * (*out, caller frees) of *out_len bytes. The input carries no comments (the parser
 * strips them first); strings and escapes are respected. */
cn_status cn_flatten(const char *css, size_t len, char **out, size_t *out_len);

#endif
