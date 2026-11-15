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

/* @container condition s[0,len) (optionally led by a container name) is SURELY true
 * for every container no wider than max_width: it must be a pure width interval
 * (width/inline-size comparisons joined by `and`) true at width 0 and at max_width.
 * Anything else -- or, not, height, style(), unknown -- is 0. spec/css_mq.md. */
int cmq_container_surely(const char *s, size_t len, int max_width);

/* Query containers known to the engine (spec/css_mq.md, "Container queries con layout"). */
#define CMQ_CONTAINER_NAMES 2
enum { CMQ_CT_NORMAL = 0, CMQ_CT_INLINE = 1, CMQ_CT_SIZE = 2 };

/* One ancestor of the element being resolved, nearest first through `parent`. */
typedef struct cmq_container {
    unsigned names[CMQ_CONTAINER_NAMES];   /* cmq_name_hash of each container-name, 0 = none */
    int      type;                         /* CMQ_CT_* */
    int      width_px;                     /* content-box inline size, -1 = unknown */
    const struct cmq_container *parent;
} cmq_container;

/* Case-sensitive hash of a container name (custom-ident); never 0 for a non-empty
 * name, 0 for NULL/empty. */
unsigned cmq_name_hash(const char *s, size_t n);

/* @container prelude s[0,len) ("[name] <condition>") against the scope chain: the
 * nearest ancestor with type != CMQ_CT_NORMAL (and that name, when one is given)
 * answers with its width when known; with no such container or an unknown width the
 * result is cmq_container_surely(s, len, max_width). Vetoed forms stay 0. */
int cmq_container_holds(const char *s, size_t len, const cmq_container *scope, int max_width);

/* Interprets a `container-type`, `container-name` or `container` declaration value.
 * *type (CMQ_CT_*) is written when the property carries a type, names[] (hashes, 0 =
 * unused) when it carries names; *has_type / *has_names say which. Returns 1 when the
 * value is valid for the property, 0 otherwise (nothing written is meaningful then).
 * `container: a b / inline-size` sets both; without a `/` the type is normal. */
int cmq_container_decl(const char *prop, const char *val, int *type,
                       unsigned names[CMQ_CONTAINER_NAMES], int *has_type, int *has_names);

#endif /* FREEDOM_CSS_MQ_H */
