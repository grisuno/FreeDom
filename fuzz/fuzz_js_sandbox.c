/*
 * libFuzzer harness for js_sandbox (Hito 3).
 *
 * Goal: arbitrary bytes treated as untrusted script through the full
 * eval + result + free pipeline must never crash, leak, or trigger UB on the
 * host. Tight limits keep each input cheap and bound time/memory per run.
 *
 * Build & run: make fuzz-js   (clang + -fsanitize=fuzzer,address,undefined)
 */

#include "js_sandbox.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* Module host for the fuzzer: every "./" specifier resolves, and "./self.js" loads
 * the input itself (so hostile code imports hostile code, cycles included); anything
 * else loads a small fixed module or fails. */
typedef struct fz_mod { const uint8_t *data; size_t size; } fz_mod;

static int fz_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz) {
    (void)host; (void)base;
    if (strncmp(spec, "./", 2) != 0) return -1;
    size_t n = strlen(spec);
    if (n + 16 >= outsz) return -1;
    memcpy(out, "https://f.test/", 15);
    memcpy(out + 15, spec + 2, n - 1);
    return 0;
}

static char *fz_fetch(void *host, const char *url, size_t *len) {
    fz_mod *m = (fz_mod *)host;
    const char *src = NULL;
    size_t n = 0;
    if (strcmp(url, "https://f.test/self.js") == 0) { src = (const char *)m->data; n = m->size; }
    else if (strcmp(url, "https://f.test/lib.js") == 0) { src = "export const v = 1;"; n = 19; }
    if (src == NULL) return NULL;
    char *c = (char *)malloc(n + 1);
    if (c == NULL) return NULL;
    if (n != 0) memcpy(c, src, n);
    c[n] = '\0';
    *len = n;
    return c;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    /* The pure stack parser sees engine-derived strings whose function names and
     * filenames are script-controlled, so fuzz it directly on the raw bytes (cheap,
     * no engine). It must never read out of bounds on any input. */
    char *nt = (char *)malloc(size + 1);
    if (nt != NULL) {
        if (size != 0) memcpy(nt, data, size);
        nt[size] = '\0';
        char file[JS_LOC_FILE_MAX];
        int line = 0, col = 0;
        (void)js_loc_from_stack(nt, file, sizeof file, &line, &col);
        (void)js_loc_from_stack(nt, NULL, 0, NULL, NULL); /* NULL outputs tolerated */
        free(nt);
    }

    js_limits lim = js_limits_default();
    lim.memory_limit_bytes = 16u * 1024u * 1024u;
    lim.time_budget_ms = 100;
    lim.max_source_bytes = 1u * 1024u * 1024u;

    js_result r;
    js_eval_once((const char *)data, size, &lim, &r);
    js_result_free(&r);

    /* The same bytes as an ES module, through a module host (spec/js_sandbox.md 7b). */
    js_context *ctx = NULL;
    if (size != 0 && js_context_new(&lim, &ctx) == JS_OK) {
        fz_mod m = { data, size };
        js_set_module_host(ctx, fz_resolve, fz_fetch, &m);
        memset(&r, 0, sizeof r);
        (void)js_eval_module(ctx, (const char *)data, size, "https://f.test/main.js", &r);
        js_result_free(&r);
        (void)js_pump_jobs(ctx, 64);
        js_context_free(ctx);
    }
    return 0;
}
