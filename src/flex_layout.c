/*
 * flex_layout — implementation: pure flexbox (single-line) and basic grid.
 *
 * No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers
 * bounded by FX_MAX_ITEMS (no VLAs). The flex algorithm follows the CSS single-line
 * model: grow distributes positive free space by grow factor; shrink distributes
 * negative free space by (shrink * basis), freezing any item that hits its minimum
 * and redistributing among the rest; justify-content then places leftover space.
 */

#include "flex_layout.h"

#include <stddef.h>

#define FX_EPS 1e-9

/* Negative inputs are clamped to zero (CSS treats them as invalid). */
static double nn(double v) {
    return (v > 0.0) ? v : 0.0;
}

fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                       fx_justify justify, fx_result *out) {
    if (n == 0) return FX_OK;
    if (items == NULL || out == NULL) return FX_ERR_NULL_ARG;
    if (avail < 0.0 || gap < 0.0 || n > FX_MAX_ITEMS) return FX_ERR_RANGE;

    unsigned char frozen[FX_MAX_ITEMS];
    double basis[FX_MAX_ITEMS];
    double total_gap = gap * (double)(n - 1);

    double basis_sum = 0.0;
    for (size_t i = 0; i < n; ++i) {
        basis[i] = nn(items[i].basis);
        frozen[i] = 0;
        out[i].size = basis[i];
        basis_sum += basis[i];
    }

    double free_space = avail - basis_sum - total_gap;

    if (free_space >= 0.0) {
        /* Grow: distribute positive free space by grow factor (no max -> one pass).
         * With no grow factors, sizes stay at basis and justify-content gets the
         * leftover. */
        double sum_grow = 0.0;
        for (size_t i = 0; i < n; ++i) sum_grow += nn(items[i].grow);
        if (sum_grow > 0.0) {
            for (size_t i = 0; i < n; ++i)
                out[i].size = basis[i] + free_space * nn(items[i].grow) / sum_grow;
        }
    } else {
        /* Shrink: distribute negative free space by (shrink * basis), freezing any
         * item that would fall below its min and redistributing. Converges in at
         * most n passes (each pass freezes at least one item, or stops). */
        for (size_t iter = 0; iter < n; ++iter) {
            double frozen_main = 0.0, free_basis = 0.0, scaled = 0.0;
            for (size_t i = 0; i < n; ++i) {
                if (frozen[i]) {
                    frozen_main += out[i].size;
                } else {
                    free_basis += basis[i];
                    scaled += nn(items[i].shrink) * basis[i];
                }
            }
            double remaining = avail - total_gap - frozen_main - free_basis;
            if (remaining >= 0.0 || scaled <= 0.0) break;  /* fits, or nothing can shrink */

            int clamped = 0;
            for (size_t i = 0; i < n; ++i) {
                if (frozen[i]) continue;
                double r = (nn(items[i].shrink) * basis[i]) / scaled;
                double s = basis[i] + remaining * r;  /* remaining < 0 */
                double mn = nn(items[i].min);
                if (s < mn) {
                    out[i].size = mn;
                    frozen[i] = 1;
                    clamped = 1;
                } else {
                    out[i].size = s;
                }
            }
            if (!clamped) break;
        }
    }

    /* Position along the main axis. Leftover space (only when items did not grow to
     * fill the line) is distributed per justify-content, added on top of the gap. */
    double used = total_gap;
    for (size_t i = 0; i < n; ++i) used += out[i].size;
    double leftover = avail - used;

    double start = 0.0, extra = 0.0;
    if (leftover > FX_EPS) {
        switch (justify) {
            case FX_JUSTIFY_END:    start = leftover;       break;
            case FX_JUSTIFY_CENTER: start = leftover / 2.0; break;
            case FX_JUSTIFY_SPACE_BETWEEN:
                if (n > 1) extra = leftover / (double)(n - 1);  /* single item: start */
                break;
            case FX_JUSTIFY_SPACE_AROUND: {
                double s = leftover / (double)n;
                start = s / 2.0;
                extra = s;
                break;
            }
            case FX_JUSTIFY_SPACE_EVENLY: {
                double s = leftover / (double)(n + 1);
                start = s;
                extra = s;
                break;
            }
            case FX_JUSTIFY_START:
            default:
                break;
        }
    }

    double cursor = start;
    for (size_t i = 0; i < n; ++i) {
        out[i].pos = cursor;
        cursor += out[i].size + gap + extra;
    }
    return FX_OK;
}

fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          double *col_x, double *col_w) {
    return fx_grid_columns_weighted(avail, ncols, gap, NULL, 0, col_x, col_w);
}

fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                                   const int *track, size_t ntrack,
                                   double *col_x, double *col_w) {
    if (ncols == 0) return FX_OK;
    if (avail < 0.0 || gap < 0.0 || ncols > FX_MAX_ITEMS) return FX_ERR_RANGE;
    if (col_x == NULL || col_w == NULL) return FX_ERR_NULL_ARG;

    double fixed = 0.0, frsum = 0.0;
    for (size_t i = 0; i < ncols; ++i) {
        int t = (track != NULL && i < ntrack) ? track[i] : 0;
        if (t > 0) fixed += (double)t;
        else if (t < 0) frsum += (double)(-t) / 100.0;
        else frsum += 1.0;   /* auto = a 1fr share */
    }
    double remaining = avail - gap * (double)(ncols - 1) - fixed;
    if (remaining < 0.0) remaining = 0.0;  /* fixed overflow: fr tracks collapse to 0 */

    double x = 0.0;
    for (size_t i = 0; i < ncols; ++i) {
        int t = (track != NULL && i < ntrack) ? track[i] : 0;
        double w;
        if (t > 0) {
            w = (double)t;
        } else {
            double fr = (t < 0) ? (double)(-t) / 100.0 : 1.0;
            w = (frsum > 0.0) ? remaining * fr / frsum : 0.0;
        }
        col_x[i] = x;
        col_w[i] = w;
        x += w + gap;
    }
    return FX_OK;
}

fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                             size_t *out_row, size_t *out_col) {
    if (nitems == 0) return FX_OK;
    if (ncols == 0 || nitems > FX_MAX_ITEMS) return FX_ERR_RANGE;
    if (out_row == NULL || out_col == NULL) return FX_ERR_NULL_ARG;

    size_t r = 0, c = 0;
    for (size_t i = 0; i < nitems; ++i) {
        size_t sp = 1;
        if (span != NULL && span[i] > 1)
            sp = ((size_t)span[i] > ncols) ? ncols : (size_t)span[i];
        if (c + sp > ncols) { ++r; c = 0; }   /* does not fit: next row */
        out_row[i] = r;
        out_col[i] = c;
        c += sp;
        if (c >= ncols) { ++r; c = 0; }        /* row full */
    }
    return FX_OK;
}

/* Shared packer: wrap == 0 is the single-row v1 contract (overflow clamps in
 * place); wrap != 0 starts a new row (cursors reset) for an item that no longer
 * fits between the cursors, reporting rows via out_row. Half-pixel tolerance so
 * a 99.8% item is not wrapped by floating-point jitter. */
static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                                 double avail, double gap, int wrap,
                                 double *out_x, size_t *out_row) {
    if (n == 0) return FX_OK;
    if (width == NULL || side == NULL || out_x == NULL ||
        (wrap && out_row == NULL))
        return FX_ERR_NULL_ARG;
    if (avail < 0.0 || gap < 0.0 || n > FX_MAX_ITEMS) return FX_ERR_RANGE;

    double cur_l = 0.0;      /* left cursor advances rightward */
    double cur_r = avail;    /* right cursor advances leftward */
    size_t row = 0;
    int row_used = 0;
    for (size_t i = 0; i < n; ++i) {
        double w = nn(width[i]);
        if (wrap && row_used) {
            int fits = (side[i] == 1) ? (cur_r - w >= cur_l - 0.5)
                                      : (cur_l + w <= cur_r + 0.5);
            if (!fits) {
                ++row;
                cur_l = 0.0;
                cur_r = avail;
                row_used = 0;
            }
        }
        if (side[i] == 1) {          /* right float: pack from the right edge */
            double x = cur_r - w;
            if (x < 0.0) x = 0.0;
            out_x[i] = x;
            cur_r = x - gap;
        } else {                     /* left float (default): pack from the left edge */
            out_x[i] = (cur_l < 0.0) ? 0.0 : cur_l;
            cur_l += w + gap;
        }
        if (out_row != NULL) out_row[i] = row;
        row_used = 1;
    }
    return FX_OK;
}

fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        double avail, double gap, double *out_x) {
    return float_pack_impl(width, side, n, avail, gap, 0, out_x, NULL);
}

fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                             double avail, double gap, double *out_x,
                             size_t *out_row) {
    return float_pack_impl(width, side, n, avail, gap, 1, out_x, out_row);
}

void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col) {
    if (row == NULL || col == NULL) return;
    if (ncols == 0) {
        *row = 0;
        *col = 0;
        return;
    }
    *row = index / ncols;
    *col = index % ncols;
}

const char *fx_justify_name(fx_justify j) {
    switch (j) {
        case FX_JUSTIFY_START:         return "start";
        case FX_JUSTIFY_END:           return "end";
        case FX_JUSTIFY_CENTER:        return "center";
        case FX_JUSTIFY_SPACE_BETWEEN: return "space-between";
        case FX_JUSTIFY_SPACE_AROUND:  return "space-around";
        case FX_JUSTIFY_SPACE_EVENLY:  return "space-evenly";
    }
    return "start";
}
