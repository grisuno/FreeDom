# include: subreq_batch

*Community 12 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `SQB_MAX_JOBS`, `SUBREQ_BATCH_H`, `_GNU_SOURCE`, `all_done_locked`, `batch_destroy`, `count_free`, `dup_n`, `job_free`. Core file: `src/subreq_batch.c` (20 symbols). Documented purpose: subreq_batch -- see include/subreq_batch.h and spec/subreq_async.md..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/subreq_batch.h` | h | utility | 17 | no |
| `src/subreq_batch.c` | c | utility | 20 | yes |
| `tests/test_subreq_batch.c` | c | testing | 13 | yes |

## Key Symbols

- `SUBREQ_BATCH_H` (macro, `include/subreq_batch.h:10`) `#define SUBREQ_BATCH_H`
- `SQB_MAX_JOBS` (macro, `include/subreq_batch.h:14`) `#define SQB_MAX_JOBS`
- `sqb_req` (struct, `include/subreq_batch.h:16`)
- `sqb_res` (struct, `include/subreq_batch.h:23`) - #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS 64 typedef st
- `ok` (type_alias, `include/subreq_batch.h:23`) `typedef struct sqb_res { int ok;` - #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define SQB_MAX_JOBS 64 typedef st
- `sqb` (type_alias, `include/subreq_batch.h:34`) `typedef struct sqb sqb;`
- `sqb_new` (function, `include/subreq_batch.h:37`) `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx);`
- `sqb_new_owned` (function, `include/subreq_batch.h:40`) `sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(` - sqb_new whose ctx the batch OWNS: free_ctx(ctx) runs once the batch is freed AND every * abandoned r
- `sqb_abandon` (function, `include/subreq_batch.h:43`) `void sqb_abandon(sqb *b);` - Frees every finished job and ABANDONS every running one: its thread is detached, its result * is dis
- `sqb_submit` (function, `include/subreq_batch.h:47`) `int sqb_submit(sqb *b, int refused, const sqb_req *req);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_count` (function, `include/subreq_batch.h:48`) `size_t sqb_count(const sqb *b);`
- `sqb_wait_all` (function, `include/subreq_batch.h:50`) `void sqb_wait_all(sqb *b);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_result` (function, `include/subreq_batch.h:52`) `const sqb_res *sqb_result(const sqb *b, size_t i);` - Queues one request. refused != 0 queues a ready-made failure (no thread, no fetch) so the result cou
- `sqb_wait_ready` (function, `include/subreq_batch.h:56`) `size_t sqb_wait_ready(sqb *b, long wait_ms, size_t *idx, size_t cap);` - Waits until every request finished or `wait_ms` elapsed (0 = do not wait), then writes the indices o
- `sqb_remove` (function, `include/subreq_batch.h:59`) `void sqb_remove(sqb *b, const size_t *idx, size_t k);` - Joins and frees the jobs at the k ascending indices (unfinished or out-of-range ones are * skipped);
- `sqb_reset` (function, `include/subreq_batch.h:61`) `void sqb_reset(sqb *b);` - Joins and frees the jobs at the k ascending indices (unfinished or out-of-range ones are * skipped);
- `sqb_free` (function, `include/subreq_batch.h:64`) `void sqb_free(sqb *b);` - Abandons what is still running (sqb_abandon) and releases the batch; the memory goes when the * last
- `_GNU_SOURCE` (macro, `src/subreq_batch.c:2`) `#define _GNU_SOURCE`
- `sqb_job` (struct, `src/subreq_batch.c:11`)
- `sqb` (struct, `src/subreq_batch.c:23`)
- `dup_n` (function, `src/subreq_batch.c:37`) `static char *dup_n(const char *s, size_t n)`
- `res_clear` (function, `src/subreq_batch.c:46`) `static void res_clear(sqb_res *r)`
- `job_free` (function, `src/subreq_batch.c:51`) `static void job_free(sqb_job *j)`
- `batch_destroy` (function, `src/subreq_batch.c:58`) `static void batch_destroy(sqb *b)`
- `job_main` (function, `src/subreq_batch.c:65`) `static void *job_main(void *arg)`
- `sqb_new` (function, `src/subreq_batch.c:97`) `sqb *sqb_new(int max_threads, sqb_run_fn run, void *ctx)`
- `sqb_new_owned` (function, `src/subreq_batch.c:101`) `sqb *sqb_new_owned(int max_threads, sqb_run_fn run, void *ctx, void (*free_ctx)(`
- `sqb_submit` (function, `src/subreq_batch.c:127`) `int sqb_submit(sqb *b, int refused, const sqb_req *req)`
- `sqb_count` (function, `src/subreq_batch.c:154`) `size_t sqb_count(const sqb *b)`
- `sqb_wait_all` (function, `src/subreq_batch.c:156`) `void sqb_wait_all(sqb *b)`

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
