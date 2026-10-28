# include: subreq_batch

*Community 11 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `SQB_MAX_JOBS`, `SUBREQ_BATCH_H`, `_GNU_SOURCE`, `dup_n`, `job_free`, `job_main`, `main`, `mk`. Core file: `src/subreq_batch.c` (14 symbols). Documented purpose: subreq_batch -- see include/subreq_batch.h and spec/subreq_async.md..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/subreq_batch.h` | h | utility | 13 | no |
| `src/subreq_batch.c` | c | utility | 14 | yes |
| `tests/test_subreq_batch.c` | c | testing | 9 | yes |

## Key Symbols

- `SUBREQ_BATCH_H` (macro, `include/subreq_batch.h:10`) `#define SUBREQ_BATCH_H`
- `SQB_MAX_JOBS` (macro, `include/subreq_batch.h:14`) `#define SQB_MAX_JOBS`
- `sqb_req` (struct, `include/subreq_batch.h:16`)
- `sqb_res` (struct, `include/subreq_batch.h:23`) - #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS 64 typedef st
- `ok` (type_alias, `include/subreq_batch.h:23`) `typedef struct sqb_res { int ok;` - #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS 64 typedef st
- `sqb` (type_alias, `include/subreq_batch.h:34`) `typedef struct sqb sqb;`
- `sqb_new` (function, `include/subreq_batch.h:37`) `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);`
- `sqb_submit` (function, `include/subreq_batch.h:41`) `int sqb_submit(sqb *b, int refused, const sqb_req *req);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_count` (function, `include/subreq_batch.h:42`) `size_t sqb_count(const sqb *b);`
- `sqb_wait_all` (function, `include/subreq_batch.h:44`) `void sqb_wait_all(sqb *b);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_result` (function, `include/subreq_batch.h:46`) `const sqb_res *sqb_result(const sqb *b, size_t i);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_reset` (function, `include/subreq_batch.h:48`) `void sqb_reset(sqb *b);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_free` (function, `include/subreq_batch.h:49`) `void sqb_free(sqb *b);`
- `_GNU_SOURCE` (macro, `src/subreq_batch.c:2`) `#define _GNU_SOURCE`
- `sqb_job` (struct, `src/subreq_batch.c:11`)
- `sqb` (struct, `src/subreq_batch.c:21`)
- `dup_n` (function, `src/subreq_batch.c:30`) `static char *dup_n(const char *s, size_t n)`
- `res_clear` (function, `src/subreq_batch.c:39`) `static void res_clear(sqb_res *r)`
- `job_free` (function, `src/subreq_batch.c:44`) `static void job_free(sqb_job *j)`
- `job_main` (function, `src/subreq_batch.c:51`) `static void *job_main(void *arg)`
- `sqb_new` (function, `src/subreq_batch.c:75`) `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx)`
- `sqb_submit` (function, `src/subreq_batch.c:86`) `int sqb_submit(sqb *b, int refused, const sqb_req *req)`
- `sqb_count` (function, `src/subreq_batch.c:112`) `size_t sqb_count(const sqb *b)`
- `sqb_wait_all` (function, `src/subreq_batch.c:114`) `void sqb_wait_all(sqb *b)`
- `sqb_result` (function, `src/subreq_batch.c:122`) `const sqb_res *sqb_result(const sqb *b, size_t i)`
- `sqb_reset` (function, `src/subreq_batch.c:126`) `void sqb_reset(sqb *b)`
- `sqb_free` (function, `src/subreq_batch.c:133`) `void sqb_free(sqb *b)`
- `_GNU_SOURCE` (macro, `tests/test_subreq_batch.c:2`) `#define _GNU_SOURCE`
- `slow_run` (function, `tests/test_subreq_batch.c:18`) `static int slow_run(void *ctx, const sqb_req *rq, sqb_res *out)`
- `mk` (function, `tests/test_subreq_batch.c:30`) `static sqb_req mk(const char *u)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `include/subreq_batch.h`)? What purpose do they serve?
- What would break if the most connected file in include: subreq_batch changed?
- Should include: subreq_batch be split, given cohesion 0.67?

## Sources

- `include/subreq_batch.h`
- `src/subreq_batch.c`
- `tests/test_subreq_batch.c`
