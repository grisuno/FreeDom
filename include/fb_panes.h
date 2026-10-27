#ifndef FREEDOM_FB_PANES_H
#define FREEDOM_FB_PANES_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * fb_panes -- the tab model of the Freebug devtools window (spec/fb_panes.md).
 * Pure: no I/O, no Cairo, no allocation, no global state. The window paints the tab
 * bar this module lays out and sends the expression it builds to the page's REPL
 * worker; the headless --dump-pane uses the same expression.
 */

typedef enum fbp_tab {
    FBP_CONSOLE = 0,
    FBP_HTML,
    FBP_CSS,
    FBP_SCRIPT,
    FBP_NET,
    FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted) */
    FBP_THROWS,    /* every exception thrown, caught ones included ("break on throw" log) */
    FBP_DOM,       /* properties of one element: attributes, geometry, state */
    FBP_STORAGE,   /* cookies, localStorage and sessionStorage of the page */
    FBP_COUNT
} fbp_tab;

#define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index / filter) */
#define FBP_EXPR_MAX     6144  /* a buffer this size always holds an expression */

/* Label of a tab; an out-of-range id is the console. Never NULL. */
const char *fbp_tab_label(int tab);

/* Tab named `name` (case-insensitive), or -1 when unknown / NULL. */
int fbp_tab_from_name(const char *name);

/* The tab `dir` steps away (cyclic); an invalid `tab` counts as the console. */
int fbp_tab_wrap(int tab, int dir);

/* x-extent of a tab in the bar: each is (letters + 2 * pad_cells) cells wide, contiguous. */
void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w);

/* The tab under pointer x, or -1 outside the bar. Exact inverse of fbp_tab_span. */
int fbp_tab_at(double x, double cell_w, double pad_cells);

/* Whether the tab's editor argument is meaningful (console: JS; others: selector/index/filter). */
int fbp_is_pane(int tab);

/* JS string literal for s[0,n) (double-quoted). Returns its length, or 0 on failure
 * (n too long, embedded NUL, cap too small). */
size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap);

/* The expression that fills `tab`'s panel for argument sel[0,n); NUL-terminated in out.
 * Returns its length, or 0 for the console, a hostile/oversized argument or a small cap. */
size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap);

#endif /* FREEDOM_FB_PANES_H */
