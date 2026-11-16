/* table_layout (tl_) -- see include/table_layout.h and spec/table_layout.md. */
#include "table_layout.h"

#include <math.h>

/* A width from the caller: non-finite or negative reads as 0, and anything past TL_WIDTH_MAX
 * is capped so sums over 64 columns stay finite (a hostile calc() can yield 1e308). */
static double tl_width(double v) {
    if (!isfinite(v) || v <= 0.0) return 0.0;
    return (v > TL_WIDTH_MAX) ? TL_WIDTH_MAX : v;
}

/* Adds `extra` to w[c0..c1), in proportion to weight[] (equally when the weights sum to 0). */
static void tl_spread(double *w, const double *weight, size_t c0, size_t c1, double extra) {
    double base = 0.0;
    for (size_t c = c0; c < c1; ++c) base += weight[c];
    double each = extra / (double)(c1 - c0);
    for (size_t c = c0; c < c1; ++c)
        w[c] += (base > 0.0) ? extra * weight[c] / base : each;
}

/* Min-content and max-content width of every column (CSS 2.1 17.5.2.2 steps 1-3). */
static void tl_measure(const tl_cell *cells, size_t n, size_t ncols, double gap,
                       double *minw, double *maxw, int *sized, int *pct) {
    for (size_t c = 0; c < ncols; ++c) { minw[c] = 0.0; maxw[c] = 0.0; sized[c] = 0; pct[c] = 0; }

    /* Cells of one column. */
    for (size_t i = 0; i < n; ++i) {
        const tl_cell *k = &cells[i];
        if (k->col < 0 || (size_t)k->col >= ncols || k->span > 1) continue;
        size_t c = (size_t)k->col;
        double mn = tl_width(k->min_w), mx = tl_width(k->max_w);
        if (mx < mn) mx = mn;
        if (isfinite(k->decl_w) && k->decl_w >= 0.0) {
            double dw = tl_width(k->decl_w);
            mx = (dw > mn) ? dw : mn;
            sized[c] = 1;
        }
        if (mn > minw[c]) minw[c] = mn;
        if (mx > maxw[c]) maxw[c] = mx;
        int share = (k->pct > TL_PER_MILLE) ? TL_PER_MILLE : k->pct;
        if (share > pct[c]) pct[c] = share;
    }

    /* Spanning cells, narrowest span first: what the covered columns lack is spread over
     * them. The weights are the max widths BEFORE this cell, so the proportions a row of
     * plain cells established are kept. */
    for (size_t span = 2; span <= ncols; ++span) {
        for (size_t i = 0; i < n; ++i) {
            const tl_cell *k = &cells[i];
            if (k->col < 0 || (size_t)k->col >= ncols || k->span < 2) continue;
            size_t c0 = (size_t)k->col;
            size_t sp = (size_t)k->span;
            if (sp > ncols - c0) sp = ncols - c0;
            if (sp != span) continue;
            size_t c1 = c0 + sp;
            double mn = tl_width(k->min_w), mx = tl_width(k->max_w);
            if (mx < mn) mx = mn;
            if (isfinite(k->decl_w) && k->decl_w >= 0.0) {
                double dw = tl_width(k->decl_w);
                mx = (dw > mn) ? dw : mn;
            }
            double inner = gap * (double)(sp - 1);
            double have_min = inner, have_max = inner;
            double weight[TL_MAX_COLS];
            for (size_t c = c0; c < c1; ++c) {
                have_min += minw[c]; have_max += maxw[c];
                weight[c] = maxw[c];
            }
            if (mn > have_min) tl_spread(minw, weight, c0, c1, mn - have_min);
            if (mx > have_max) tl_spread(maxw, weight, c0, c1, mx - have_max);
            for (size_t c = c0; c < c1; ++c)
                if (maxw[c] < minw[c]) maxw[c] = minw[c];
        }
    }
}

void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap,
                  double *min_total, double *max_total) {
    if (min_total != NULL) *min_total = 0.0;
    if (max_total != NULL) *max_total = 0.0;
    if (ncols == 0 || ncols > TL_MAX_COLS) return;
    if (cells == NULL) n = 0;
    gap = tl_width(gap);
    double minw[TL_MAX_COLS], maxw[TL_MAX_COLS];
    int sized[TL_MAX_COLS], pct[TL_MAX_COLS];
    tl_measure(cells, n, ncols, gap, minw, maxw, sized, pct);
    double mn = gap * (double)(ncols - 1), mx = mn;
    for (size_t c = 0; c < ncols; ++c) { mn += minw[c]; mx += maxw[c]; }
    if (min_total != NULL) *min_total = mn;
    if (max_total != NULL) *max_total = mx;
}

/* Shares `used` px among the columns with take[c] != 0 (CSS 2.1 17.5.2.2, css-tables-3 3.9):
 * above the sum of their max widths the surplus goes to the auto columns in proportion to
 * their max (to all, when none is auto; equally on a zero base); between min and max each gets
 * its min plus a share of the slack; below the sum of minima they shrink in proportion. */
static void tl_distribute(const double *minw, const double *maxw, const int *sized,
                          const int *take, size_t ncols, double used, double *out) {
    double sum_min = 0.0, sum_max = 0.0;
    int any_auto = 0;
    size_t takers = 0;
    for (size_t c = 0; c < ncols; ++c) {
        if (!take[c]) continue;
        sum_min += minw[c]; sum_max += maxw[c];
        if (!sized[c]) any_auto = 1;
    }
    if (used >= sum_max) {
        double surplus = used - sum_max, base = 0.0;
        for (size_t c = 0; c < ncols; ++c) {
            if (!take[c]) continue;
            out[c] = maxw[c];
            if (any_auto && sized[c]) continue;
            base += maxw[c];
            ++takers;
        }
        if (surplus <= 0.0 || takers == 0) return;
        for (size_t c = 0; c < ncols; ++c) {
            if (!take[c] || (any_auto && sized[c])) continue;
            out[c] += (base > 0.0) ? surplus * maxw[c] / base : surplus / (double)takers;
        }
    } else if (used >= sum_min) {
        double slack = used - sum_min, range = sum_max - sum_min;
        for (size_t c = 0; c < ncols; ++c)
            if (take[c])
                out[c] = minw[c] + ((range > 0.0) ? slack * (maxw[c] - minw[c]) / range : 0.0);
    } else {
        double k = (sum_min > 0.0 && used > 0.0) ? used / sum_min : 0.0;
        for (size_t c = 0; c < ncols; ++c)
            if (take[c]) out[c] = minw[c] * k;
    }
}

double tl_columns(const tl_cell *cells, size_t n, size_t ncols, double gap,
                  double avail, double table_w, double *out) {
    if (out == NULL || ncols == 0 || ncols > TL_MAX_COLS) return 0.0;
    if (cells == NULL) n = 0;
    gap = tl_width(gap);
    avail = tl_width(avail);
    if (avail < 1.0) avail = 1.0;
    if (isfinite(table_w) && table_w > TL_WIDTH_MAX) table_w = TL_WIDTH_MAX;

    double minw[TL_MAX_COLS], maxw[TL_MAX_COLS];
    int sized[TL_MAX_COLS], pct[TL_MAX_COLS], take[TL_MAX_COLS];
    tl_measure(cells, n, ncols, gap, minw, maxw, sized, pct);

    double gaps = gap * (double)(ncols - 1);
    double sum_min = 0.0, sum_max = 0.0;
    for (size_t c = 0; c < ncols; ++c) { sum_min += minw[c]; sum_max += maxw[c]; }

    /* The width the columns share (gaps excluded). */
    double room = avail - gaps;
    if (room < 1.0) room = 1.0;
    int fixed_w = isfinite(table_w) && table_w >= 0.0;
    double used;
    if (fixed_w) {
        used = table_w - gaps;
        if (used < sum_min) used = sum_min;
    } else {
        used = (sum_max < room) ? sum_max : room;
        if (used < sum_min) used = sum_min;   /* min-content is a floor: the table overflows */
    }

    /* Percentage columns take their share of a SIZED table first (an auto table has no width
     * to take a share of). Shares are capped at the whole table in column order and floored
     * at the column's min-content. */
    double pct_total = 0.0, pct_slack = 0.0, rest_min = 0.0;
    int npct = 0, nrest = 0, cum = 0;
    for (size_t c = 0; c < ncols; ++c) {
        take[c] = 1;
        if (!fixed_w || pct[c] <= 0) { ++nrest; rest_min += minw[c]; continue; }
        int share = (pct[c] < TL_PER_MILLE - cum) ? pct[c] : TL_PER_MILLE - cum;
        cum += share;
        pct[c] = share;
        double want = used * (double)share / (double)TL_PER_MILLE;
        out[c] = (want > minw[c]) ? want : minw[c];
        pct_total += out[c];
        pct_slack += out[c] - minw[c];
        take[c] = 0;
        ++npct;
    }
    if (npct > 0) {
        double rest = used - pct_total;
        /* What the others need at least (or an overdraw with no others) comes back out of
         * the percentage columns that have room above their minimum. */
        double need = (nrest > 0) ? rest_min - rest : -rest;
        if (need > 0.0 && pct_slack > 0.0) {
            double back = (need < pct_slack) ? need : pct_slack;
            for (size_t c = 0; c < ncols; ++c)
                if (!take[c]) out[c] -= back * (out[c] - minw[c]) / pct_slack;
            rest += back;
        }
        if (nrest == 0 && rest > 0.0) {
            for (size_t c = 0; c < ncols; ++c)
                out[c] += (cum > 0) ? rest * (double)pct[c] / (double)cum : rest / (double)npct;
        }
        if (nrest > 0) tl_distribute(minw, maxw, sized, take, ncols, rest, out);
    } else {
        tl_distribute(minw, maxw, sized, take, ncols, used, out);
    }

    double total = gaps;
    for (size_t c = 0; c < ncols; ++c) {
        if (!isfinite(out[c]) || out[c] < 0.0) out[c] = 0.0;
        total += out[c];
    }
    return total;
}
