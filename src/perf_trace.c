/*
 * perf_trace (pt_) — pure per-stage render timing accumulator. Phase R0.
 * See spec/perf_trace.md.
 */

#include "perf_trace.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int stage_valid(pt_stage stage) {
    return stage >= 0 && stage < PT_STAGE_COUNT;
}

void pt_init(pt_trace *t) {
    if (!t) return;
    memset(t, 0, sizeof(*t));
}

uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us) {
    if (end_us < start_us) return 0;
    return end_us - start_us;
}

void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us) {
    if (!t || !stage_valid(stage)) return;
    pt_stage_stats *s = &t->stage[stage];
    s->samples[s->next] = elapsed_us;
    s->next = (s->next + 1) % PT_MAX_SAMPLES;
    if (s->fill < PT_MAX_SAMPLES) s->fill++;
    s->total++;
}

size_t pt_count(const pt_trace *t, pt_stage stage) {
    if (!t || !stage_valid(stage)) return 0;
    return t->stage[stage].fill;
}

uint64_t pt_last_us(const pt_trace *t, pt_stage stage) {
    if (!t || !stage_valid(stage)) return 0;
    const pt_stage_stats *s = &t->stage[stage];
    if (s->fill == 0) return 0;
    /* next points one past the most recently written slot (with wrap) */
    size_t last_idx = (s->next + PT_MAX_SAMPLES - 1) % PT_MAX_SAMPLES;
    return s->samples[last_idx];
}

uint64_t pt_min_us(const pt_trace *t, pt_stage stage) {
    if (!t || !stage_valid(stage)) return 0;
    const pt_stage_stats *s = &t->stage[stage];
    if (s->fill == 0) return 0;
    uint64_t m = s->samples[0];
    for (size_t i = 1; i < s->fill; ++i) {
        if (s->samples[i] < m) m = s->samples[i];
    }
    return m;
}

uint64_t pt_max_us(const pt_trace *t, pt_stage stage) {
    if (!t || !stage_valid(stage)) return 0;
    const pt_stage_stats *s = &t->stage[stage];
    if (s->fill == 0) return 0;
    uint64_t m = s->samples[0];
    for (size_t i = 1; i < s->fill; ++i) {
        if (s->samples[i] > m) m = s->samples[i];
    }
    return m;
}

static int cmp_u64(const void *a, const void *b) {
    uint64_t x = *(const uint64_t *)a;
    uint64_t y = *(const uint64_t *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

uint64_t pt_median_us(const pt_trace *t, pt_stage stage) {
    if (!t || !stage_valid(stage)) return 0;
    const pt_stage_stats *s = &t->stage[stage];
    if (s->fill == 0) return 0;
    uint64_t sorted[PT_MAX_SAMPLES];
    memcpy(sorted, s->samples, s->fill * sizeof(uint64_t));
    qsort(sorted, s->fill, sizeof(uint64_t), cmp_u64);
    return sorted[s->fill / 2];
}

const char *pt_stage_name(pt_stage stage) {
    switch (stage) {
        case PT_FETCH:    return "fetch";
        case PT_PARSE:    return "parse";
        case PT_STYLE:    return "style";
        case PT_IPC:      return "ipc";
        case PT_RD_BUILD: return "rd_build";
        case PT_LAYOUT:   return "layout";
        case PT_PAINT:    return "paint";
        case PT_COMMIT:   return "commit";
        case PT_SHAPE:    return "shape";
        default:          return "unknown";
    }
}

/* Upper bound on one formatted line: longest stage name ("rd_build", 8) plus
 * five uint64_t fields (<=20 digits each) and literal text comfortably fits
 * in 160 bytes; verified by construction, not by truncation. */
#define PT_LINE_CAP 160

size_t pt_format(const pt_trace *t, char *buf, size_t cap) {
    if (!t || !buf || cap == 0) return 0;
    size_t n = 0;
    for (int st = 0; st < PT_STAGE_COUNT; ++st) {
        size_t cnt = pt_count(t, (pt_stage)st);
        if (cnt == 0) continue;

        char line[PT_LINE_CAP];
        int r = snprintf(line, sizeof(line),
                          "stage=%s n=%zu last_us=%llu min_us=%llu max_us=%llu median_us=%llu\n",
                          pt_stage_name((pt_stage)st),
                          t->stage[st].total,
                          (unsigned long long)pt_last_us(t, (pt_stage)st),
                          (unsigned long long)pt_min_us(t, (pt_stage)st),
                          (unsigned long long)pt_max_us(t, (pt_stage)st),
                          (unsigned long long)pt_median_us(t, (pt_stage)st));
        if (r < 0) break; /* formatting error: fail-closed, stop here */
        size_t len = (size_t)r;
        if (len >= sizeof(line)) len = sizeof(line) - 1; /* defensive clamp */

        /* Only commit this line to buf if it (plus its NUL) fits within cap.
         * This never partially copies a line into the caller's buffer, so
         * buf[n] is always the '\0' right after the last COMPLETE line. */
        if (n + len >= cap) break;
        memcpy(buf + n, line, len);
        n += len;
    }
    buf[n] = '\0';
    return n;
}
