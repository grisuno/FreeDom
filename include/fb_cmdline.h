#ifndef FREEDOM_FB_CMDLINE_H
#define FREEDOM_FB_CMDLINE_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * fb_cmdline -- the Freebug command line model (spec/fb_cmdline.md): REPL history, property
 * completion and the console level filter. Pure: no I/O, no global state, reentrant.
 */

#define FBC_HIST_MAX   64     /* entries kept; the oldest falls off */
#define FBC_ENTRY_MAX  4096   /* bytes of one history entry */
#define FBC_BASE_MAX   256    /* bytes of a completion base path */
#define FBC_LIST_NAMES 40     /* candidates shown when a completion is ambiguous */

typedef struct fbc_history {
    char  *items[FBC_HIST_MAX];  /* oldest first */
    size_t n;
    size_t pos;                  /* index being shown; == n on the live line */
    char  *draft;                /* the live line, saved while browsing */
} fbc_history;

void fbc_history_init(fbc_history *h);
void fbc_history_free(fbc_history *h);   /* idempotent */

/* 0 stored/ignored-benign (empty, same as the newest), -1 too long or out of memory. Returns to the live line. */
int fbc_history_push(fbc_history *h, const char *text, size_t len);

/* Older entry (saves cur as the draft when leaving the live line), or NULL when there is none.
 * The pointer is valid until the next call on h. */
const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen);

/* Newer entry; past the newest, the draft ("" when none). NULL when already on the live line. */
const char *fbc_history_next(fbc_history *h);

/* Splits the trailing property path of text[0,n): base ("a.b" of "a.b.c", "" = global) into base[cap],
 * *prefix_off = where the prefix starts. Returns the prefix length, or -1 when nothing is completable. */
long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size_t *prefix_off);

/* JS expression returning the newline-joined property names reachable from the path `base`
 * (no getter is run). Returns its length, 0 on a bad path or small cap. */
size_t fbc_names_expr(const char *base, char *out, size_t cap);

/* From the newline-separated `names`, those starting with prefix[0,plen): `ins` gets the longest common
 * extension beyond the prefix, `list` the candidates space-separated; *count how many matched. Returns
 * the length of the insertion. */
size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen,
                         char *ins, size_t ins_cap, char *list, size_t list_cap, size_t *count);

typedef enum fbc_filter {
    FBC_FILTER_ALL = 0,
    FBC_FILTER_ERRORS,
    FBC_FILTER_WARNINGS,
    FBC_FILTER_LOGS,
    FBC_FILTER_COUNT
} fbc_filter;

int fbc_filter_passes(int filter, int level);   /* level is an fb_level */
int fbc_filter_next(int filter);                /* cyclic; an invalid filter counts as ALL */
const char *fbc_filter_label(int filter);

#endif /* FREEDOM_FB_CMDLINE_H */
