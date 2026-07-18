#ifndef FREEDOM_PERF_TRACE_H
#define FREEDOM_PERF_TRACE_H

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

#include <stddef.h>
#include <stdint.h>

/*
 * perf_trace (pt_) — pure per-stage render timing accumulator. Phase R0
 * (render optimization plan). Records elapsed-microsecond samples per
 * pipeline stage in a bounded ring buffer; never reads the clock itself
 * (the caller supplies clock_gettime deltas). No I/O, no allocation, no
 * global state. See spec/perf_trace.md.
 */

typedef enum {
    PT_FETCH = 0,
    PT_PARSE,
    PT_STYLE,
    PT_IPC,
    PT_RD_BUILD,
    PT_LAYOUT,
    PT_PAINT,
    PT_COMMIT,
    PT_SHAPE,
    PT_STAGE_COUNT
} pt_stage;

#define PT_MAX_SAMPLES 256

typedef struct pt_stage_stats {
    uint64_t samples[PT_MAX_SAMPLES];
    size_t   fill;   /* valid samples currently held, <= PT_MAX_SAMPLES */
    size_t   next;   /* next ring write position */
    size_t   total;  /* samples ever seen, including evicted ones */
} pt_stage_stats;

typedef struct pt_trace {
    pt_stage_stats stage[PT_STAGE_COUNT];
} pt_trace;

/* Reset all stages to empty. NULL-safe (no-op). */
void pt_init(pt_trace *t);

/* end_us - start_us with an anti-underflow guard: end < start yields 0
 * instead of wrapping to a huge uint64_t. Pure. */
uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);

/* Record one sample (microseconds) for the given stage. NULL-safe and
 * stage-bounds-safe: t==NULL or an out-of-range stage is a no-op. */
void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);

/* Samples currently held in the stage's ring (<= PT_MAX_SAMPLES). */
size_t pt_count(const pt_trace *t, pt_stage stage);

/* Most recently recorded sample; 0 if none or t==NULL. */
uint64_t pt_last_us(const pt_trace *t, pt_stage stage);

/* Min / max / median over the samples currently in the ring. 0 if empty. */
uint64_t pt_min_us(const pt_trace *t, pt_stage stage);
uint64_t pt_max_us(const pt_trace *t, pt_stage stage);
uint64_t pt_median_us(const pt_trace *t, pt_stage stage);

/* Short lowercase stage name ("fetch".."shape"); "unknown" if out of range.
 * Static string, never NULL. */
const char *pt_stage_name(pt_stage stage);

/* Deterministic dump, one line per stage with count > 0, enum order:
 *   stage=<name> n=<total> last_us=<n> min_us=<n> max_us=<n> median_us=<n>\n
 * snprintf fail-closed (V-004): truncates at a line boundary if buf fills,
 * never overflows. Returns bytes written (excluding the NUL). buf==NULL or
 * cap==0 returns 0 without writing. */
size_t pt_format(const pt_trace *t, char *buf, size_t cap);

#endif /* FREEDOM_PERF_TRACE_H */
