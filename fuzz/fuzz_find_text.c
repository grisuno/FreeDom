/* libFuzzer harness for find_text (spec/find_text.md). Input: [qlen][query][pieces...],
 * pieces split at 0x00 (gap) or 0x01 (no gap). Invariants: every match lies inside its
 * pieces, matches are ordered and disjoint, spans stay inside their piece. */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "find_text.h"

#define MAXP 64

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 1) return 0;
    size_t ql = data[0];
    if (ql > size - 1) ql = size - 1;
    const char *q = (const char *)data + 1;
    const uint8_t *t = data + 1 + ql;
    size_t tl = size - 1 - ql;
    ft_piece p[MAXP];
    size_t np = 0, st = 0;
    int gap = 0;
    for (size_t i = 0; i <= tl && np < MAXP; ++i) {
        if (i == tl || t[i] <= 1) {
            p[np].text = (const char *)t + st;
            p[np].len = i - st;
            p[np].gap_before = gap;
            ++np;
            if (i < tl) gap = (t[i] == 0);
            st = i + 1;
        }
    }
    uint32_t qc[FT_QUERY_MAX];
    size_t qn = ft_compile(q, ql, qc, FT_QUERY_MAX);
    if (qn > 0 && (qc[0] == ' ' || qc[qn - 1] == ' ')) abort();
    ft_match m[32];
    size_t nm = 0;
    int trunc = 0;
    if (ft_search(p, np, qc, qn, m, 32, &nm, &trunc) != FT_OK) abort();
    if (nm > 32) abort();
    for (size_t i = 0; i < nm; ++i) {
        if (m[i].start.piece >= np || m[i].end.piece >= np) abort();
        if (m[i].start.off >= p[m[i].start.piece].len) abort();
        if (m[i].end.off > p[m[i].end.piece].len || m[i].end.off == 0) abort();
        if (m[i].end.piece < m[i].start.piece) abort();
        if (m[i].end.piece == m[i].start.piece && m[i].end.off <= m[i].start.off) abort();
        if (i > 0) {
            ft_pos a = m[i - 1].end, b = m[i].start;
            if (b.piece < a.piece || (b.piece == a.piece && b.off < a.off)) abort();
        }
    }
    ft_span s[128];
    size_t ns = ft_spans(p, np, m, nm, s, 128);
    for (size_t i = 0; i < ns; ++i)
        if (s[i].piece >= np || s[i].start >= s[i].end || s[i].end > p[s[i].piece].len
            || s[i].match >= nm) abort();
    long c = ft_step((long)(size % 7) - 2, nm, (size & 1) ? 1 : -1);
    if (nm == 0 ? c != -1 : (c < 0 || (size_t)c >= nm)) abort();
    return 0;
}
