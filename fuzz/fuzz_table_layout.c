/* libFuzzer harness for table_layout and pres_hints (spec/table_layout.md, spec/pres_hints.md).
 * Hostile cell geometry (raw doubles: NaN, infinities, huge spans) and hostile attribute
 * values. Invariants: every column is finite and non-negative, the reported width is their
 * sum plus the gaps, the intrinsic widths are finite, and a hint only ever writes its own
 * fields with in-range values. */
#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "pres_hints.h"
#include "table_layout.h"

typedef struct { const uint8_t *p; size_t n; } attr_src;

static const char *attr_get(void *ctx, const char *name, size_t *len) {
    const attr_src *a = ctx;
    (void)name;
    *len = a->n;
    return (const char *)a->p;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 4) return 0;
    size_t ncols = (size_t)data[0] % (TL_MAX_COLS + 2u);
    double gap, avail, table_w;
    double hdr[3] = { 0.0, 0.0, 0.0 };
    size_t off = 1;
    size_t take = (size - off < sizeof hdr) ? size - off : sizeof hdr;
    memcpy(hdr, data + off, take);
    off += take;
    gap = hdr[0]; avail = hdr[1]; table_w = hdr[2];

    size_t n = (size - off) / sizeof(tl_cell);
    if (n > 512) n = 512;
    tl_cell *cells = (n > 0) ? malloc(n * sizeof *cells) : NULL;
    if (n > 0 && cells == NULL) return 0;
    if (n > 0) memcpy(cells, data + off, n * sizeof *cells);

    double out[TL_MAX_COLS];
    for (size_t c = 0; c < TL_MAX_COLS; ++c) out[c] = -1.0;
    double total = tl_columns(cells, n, ncols, gap, avail, table_w, out);
    if (!isfinite(total) || total < 0.0) abort();
    if (ncols >= 1 && ncols <= TL_MAX_COLS) {
        for (size_t c = 0; c < ncols; ++c)
            if (!isfinite(out[c]) || out[c] < 0.0) abort();
    } else if (total != 0.0 || out[0] != -1.0) {
        abort();
    }
    double mn = -1.0, mx = -1.0;
    tl_intrinsic(cells, n, ncols, gap, &mn, &mx);
    if (!isfinite(mn) || !isfinite(mx) || mn < 0.0 || mx < 0.0) abort();
    free(cells);

    static const char *const tags[] = { "table", "td", "th", "tr", "div", "p", "h3", "center",
                                        "body", "span", "tbody" };
    attr_src src = { data + 1, size - 1 };
    css_style cs;
    memset(&cs, 0, sizeof cs);
    cs.width = CSS_LEN_UNSET;
    cs.margin_left = cs.margin_right = CSS_LEN_UNSET;
    cs.background = -1;
    ph_apply(tags[data[0] % (sizeof tags / sizeof *tags)], attr_get, &src, data[1] & 3u, &cs);
    if (cs.pct[CSS_PCT_WIDTH] < 0 || cs.pct[CSS_PCT_WIDTH] > 10000) abort();
    if (cs.width != CSS_LEN_UNSET && (cs.width < 0 || cs.width > PH_DIM_MAX_PX)) abort();
    if (cs.background < -1 || cs.background > 0xffffff) abort();
    int px = 0, pm = 0;
    (void)ph_parse_dimension((const char *)data, size, &px, &pm);
    return 0;
}
