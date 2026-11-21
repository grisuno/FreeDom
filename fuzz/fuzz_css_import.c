/* fuzz_css_import -- hostile stylesheet text through the @import prelude reader
 * (spec/css_import.md). Oracle: every wrapper built from hostile conditions is
 * itself balanced (a condition can never smuggle a brace), and every URL and
 * condition is NUL-terminated within its field. The url() rebase is an identity
 * when the resolver fails, and never changes whether the sheet is balanced (an
 * absolute URL with braces or comment markers rides inside a string). */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "css_import.h"

typedef struct { uint8_t *p; size_t n, cap; } fz_out;

static int fz_emit(void *ctx, const char *s, size_t n) {
    fz_out *o = (fz_out *)ctx;
    if (n > o->cap - o->n) return -1;
    memcpy(o->p + o->n, s, n);
    o->n += n;
    return 0;
}

/* ctx != NULL: fail. Otherwise a hostile resolver: joins with braces and comment
 * openers, the worst a real one could return. */
static int fz_resolve(void *ctx, const char *base, const char *ref, char *out, size_t outsz) {
    (void)base;
    if (ctx != NULL) return -1;
    size_t r = strlen(ref);
    if (r + 8 >= outsz) return -1;
    memcpy(out, "h:/*{}/", 7);
    memcpy(out + 7, ref, r + 1);
    return 0;
}

static void fuzz_rebase(const uint8_t *data, size_t size) {
    size_t cap = size * 2 + 4096 * 8;
    fz_out o = { (uint8_t *)malloc(cap), 0, cap };
    if (o.p == NULL) return;
    int fail = 1;
    if (ci_rebase_urls((const char *)data, size, "b", fz_resolve, &fail, fz_emit, &o) != 0
        || o.n != size || (size > 0 && memcmp(o.p, data, size) != 0))
        abort();
    o.n = 0;
    if (ci_rebase_urls((const char *)data, size, "b", fz_resolve, NULL, fz_emit, &o) == 0
        && ci_balanced((const char *)data, size) != ci_balanced((const char *)o.p, o.n))
        abort();
    free(o.p);
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    static ci_import ims[CI_MAX_PER_SHEET];
    size_t n = ci_scan((const char *)data, size, ims, CI_MAX_PER_SHEET);
    if (n > CI_MAX_PER_SHEET) abort();
    (void)ci_balanced((const char *)data, size);
    for (size_t i = 0; i < n; ++i) {
        if (memchr(ims[i].url, '\0', sizeof ims[i].url) == NULL) abort();
        if (ims[i].url[0] == '\0') abort();
        if (memchr(ims[i].media, '\0', sizeof ims[i].media) == NULL) abort();
        char open[3 * CI_COND_MAX + 64], close[8], both[3 * CI_COND_MAX + 80];
        if (ci_wrap(&ims[i], open, sizeof open, close, sizeof close) != 0) abort();
        size_t ol = strlen(open), cl = strlen(close);
        memcpy(both, open, ol);
        memcpy(both + ol, close, cl);
        if (!ci_balanced(both, ol + cl)) abort();
    }
    fuzz_rebase(data, size);
    return 0;
}
