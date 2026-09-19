# include

*Community 3 | 4 files | cohesion 0.60*

## Definition

This community groups 4 file(s) rooted at `include` with dominant language c (cohesion 0.60). Central symbols: `FREEDOM_PREFETCH_H`, `LLVMFuzzerTestOneInput`, `PF_MAX_REFS`, `PF_MAX_THREADS`, `PF_MAX_URL`, `_POSIX_C_SOURCE`, `attr_span`, `barrier`. Core file: `include/prefetch.h` (21 symbols). Documented purpose: libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_prefetch.c` | c | utility | 1 | yes |
| `include/prefetch.h` | h | utility | 21 | no |
| `src/prefetch.c` | c | utility | 17 | no |
| `tests/test_prefetch.c` | c | testing | 12 | yes |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_prefetch.c:10`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_PREFETCH_H` (macro, `include/prefetch.h:2`) `#define FREEDOM_PREFETCH_H`
- `pf_kind` (enum, `include/prefetch.h:35`) - Subresource kinds the lookahead scanner recognizes. Anything else (icons, preload hints, images) is
- `pf_ref` (struct, `include/prefetch.h:42`) - One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and valid
- `kind` (type_alias, `include/prefetch.h:42`) `typedef struct pf_ref { pf_kind kind;` - One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and valid
- `PF_MAX_REFS` (macro, `include/prefetch.h:47`) `#define PF_MAX_REFS`
- `PF_MAX_THREADS` (macro, `include/prefetch.h:48`) `#define PF_MAX_THREADS`
- `refs` (type_alias, `include/prefetch.h:49`) `typedef struct pf_list { pf_ref refs[PF_MAX_REFS];` - One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and valid
- `pf_list` (struct, `include/prefetch.h:50`)
- `pf_scan` (function, `include/prefetch.h:59`) `int pf_scan(const char *html, size_t len, pf_list *out);` - Lookahead scan of hostile HTML. Fills out (owns the URLs; free with pf_list_free). Comment, <script>
- `pf_list_free` (function, `include/prefetch.h:60`) `void pf_list_free(pf_list *l);`
- `pf_job_state` (enum, `include/prefetch.h:70`)
- `pf_job` (struct, `include/prefetch.h:77`)
- `jobs` (type_alias, `include/prefetch.h:86`) `typedef struct pf_pool { pf_job jobs[PF_MAX_REFS];`
- `pf_pool` (struct, `include/prefetch.h:87`)
- `fetch` (function, `include/prefetch.h:102`) `* claiming jobs and running fetch(ctx, "GET", url, ...). Returns 0 on success or`
- `pf_pool_take` (function, `include/prefetch.h:115`) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status, char **body,` - Cache-first take. On a hit (url matches an unconsumed job) WAITS for that job and MOVES the result t
- `pf_pool_finish` (function, `include/prefetch.h:121`) `void pf_pool_finish(pf_pool *p);` - Joins the worker threads and frees every unconsumed result. Blocks until in-flight fetches end (boun
- `pool` (function, `include/prefetch.h:125`) `* whose URL is pooled is served from the pool (a failed prefetch propagates the`
- `pf_gated_fetch` (struct, `include/prefetch.h:129`) - Cache-first fetcher adapter, shared by every frontend (DRY): install pf_pooled_fetch as the tab fetc
- `inner` (type_alias, `include/prefetch.h:129`) `typedef struct pf_gated_fetch { pf_fetch_fn inner;` - Cache-first fetcher adapter, shared by every frontend (DRY): install pf_pooled_fetch as the tab fetc
- `pf_pooled_fetch` (function, `include/prefetch.h:135`) `int pf_pooled_fetch(void *vctx, const char *method, const char *url, const char`
- `_POSIX_C_SOURCE` (macro, `src/prefetch.c:12`) `#define _POSIX_C_SOURCE`
- `PF_MAX_URL` (macro, `src/prefetch.c:21`) `#define PF_MAX_URL`
- `is_ws` (function, `src/prefetch.c:23`) `static int is_ws(char c)`
- `is_name_char` (function, `src/prefetch.c:27`) `static int is_name_char(char c)`
- `lower` (function, `src/prefetch.c:32`) `static int lower(int c)`
- `ci_starts` (function, `src/prefetch.c:37`) `static int ci_starts(const char *p, const char *end, const char *kw)` - static int is_ws(char c) { return c == ' ' \|\| c == '\t' \|\| c == '\n' \|\| c == '\r' \|\| c == '\f'; } st
- `ci_find` (function, `src/prefetch.c:46`) `static const char *ci_find(const char *p, const char *end, const char *kw)` - static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Case-insensitive
- `ci_eq_span` (function, `src/prefetch.c:55`) `static int ci_eq_span(const char *s, size_t n, const char *kw)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/prefetch.h.
- [INFERRED] shares_context community 1 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 3 (include).
- [INFERRED] shares_context community 2 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 2 (include) and community 3 (include).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `include/prefetch.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.60?

## Sources

- `fuzz/fuzz_prefetch.c`
- `include/prefetch.h`
- `src/prefetch.c`
- `tests/test_prefetch.c`
