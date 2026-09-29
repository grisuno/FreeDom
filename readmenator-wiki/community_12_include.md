# include

*Community 12 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `FREEDOM_PERF_TRACE_H`, `PT_LINE_CAP`, `PT_MAX_SAMPLES`, `cmp_u64`, `main`, `order`, `pt_count`, `pt_elapsed_us`. Core file: `include/perf_trace.h` (17 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/perf_trace.h` | h | utility | 17 | no |
| `src/perf_trace.c` | c | utility | 12 | no |
| `tests/test_perf_trace.c` | c | testing | 12 | no |

## Key Symbols

- `FREEDOM_PERF_TRACE_H` (macro, `include/perf_trace.h:2`) `#define FREEDOM_PERF_TRACE_H`
- `PT_MAX_SAMPLES` (macro, `include/perf_trace.h:32`) `#define PT_MAX_SAMPLES`
- `samples` (type_alias, `include/perf_trace.h:33`) `typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES];` - define PT_MAX_SAMPLES 256
- `pt_stage_stats` (struct, `include/perf_trace.h:34`)
- `stage` (type_alias, `include/perf_trace.h:40`) `typedef struct pt_trace { pt_stage_stats stage[PT_STAGE_COUNT];`
- `pt_trace` (struct, `include/perf_trace.h:41`)
- `pt_init` (function, `include/perf_trace.h:46`) `void pt_init(pt_trace *t);` - #define PT_MAX_SAMPLES 256 typedef struct pt_stage_stats { uint64_t samples[PT_MAX_SAMPLES]; size_t
- `pt_elapsed_us` (function, `include/perf_trace.h:50`) `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);` - end_us - start_us with an anti-underflow guard: end < start yields 0 * instead of wrapping to a huge
- `pt_record` (function, `include/perf_trace.h:54`) `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);` - Record one sample (microseconds) for the given stage. NULL-safe and * stage-bounds-safe: t==NULL or
- `pt_count` (function, `include/perf_trace.h:57`) `size_t pt_count(const pt_trace *t, pt_stage stage);` - Record one sample (microseconds) for the given stage. NULL-safe and * stage-bounds-safe: t==NULL or
- `pt_last_us` (function, `include/perf_trace.h:60`) `uint64_t pt_last_us(const pt_trace *t, pt_stage stage);` - Record one sample (microseconds) for the given stage. NULL-safe and * stage-bounds-safe: t==NULL or
- `pt_min_us` (function, `include/perf_trace.h:63`) `uint64_t pt_min_us(const pt_trace *t, pt_stage stage);` - Record one sample (microseconds) for the given stage. NULL-safe and * stage-bounds-safe: t==NULL or
- `pt_max_us` (function, `include/perf_trace.h:64`) `uint64_t pt_max_us(const pt_trace *t, pt_stage stage);`
- `pt_median_us` (function, `include/perf_trace.h:65`) `uint64_t pt_median_us(const pt_trace *t, pt_stage stage);`
- `pt_stage_name` (function, `include/perf_trace.h:69`) `const char *pt_stage_name(pt_stage stage);` - Short lowercase stage name ("fetch".."shape"); "unknown" if out of range. * Static string, never NUL
- `order` (enum, `include/perf_trace.h:71`)
- `pt_format` (function, `include/perf_trace.h:76`) `size_t pt_format(const pt_trace *t, char *buf, size_t cap);` - Deterministic dump, one line per stage with count > 0, enum order: stage=<name> n=<total> last_us=<n
- `pt_init` (function, `src/perf_trace.c:16`) `void pt_init(pt_trace *t)`
- `pt_elapsed_us` (function, `src/perf_trace.c:21`) `uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us)`
- `pt_record` (function, `src/perf_trace.c:26`) `void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us)`
- `pt_count` (function, `src/perf_trace.c:35`) `size_t pt_count(const pt_trace *t, pt_stage stage)`
- `pt_last_us` (function, `src/perf_trace.c:40`) `uint64_t pt_last_us(const pt_trace *t, pt_stage stage)`
- `pt_min_us` (function, `src/perf_trace.c:49`) `uint64_t pt_min_us(const pt_trace *t, pt_stage stage)`
- `pt_max_us` (function, `src/perf_trace.c:60`) `uint64_t pt_max_us(const pt_trace *t, pt_stage stage)`
- `cmp_u64` (function, `src/perf_trace.c:71`) `static int cmp_u64(const void *a, const void *b)`
- `pt_median_us` (function, `src/perf_trace.c:79`) `uint64_t pt_median_us(const pt_trace *t, pt_stage stage)`
- `pt_stage_name` (function, `src/perf_trace.c:89`) `const char *pt_stage_name(pt_stage stage)`
- `PT_LINE_CAP` (macro, `src/perf_trace.c:107`) `#define PT_LINE_CAP`
- `pt_format` (function, `src/perf_trace.c:109`) `size_t pt_format(const pt_trace *t, char *buf, size_t cap)`
- `test_single_record` (function, `tests/test_perf_trace.c:28`) `static void test_single_record(void **state)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 2 <-> 12 (strength 0.9): Extracted import edge crosses communities: src/freedom.c imports include/perf_trace.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `include/perf_trace.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.67?

## Sources

- `include/perf_trace.h`
- `src/perf_trace.c`
- `tests/test_perf_trace.c`
