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
                             const int *row_span,
                             const int *fixed_row, const int *fixed_col,
                             size_t *out_row, size_t *out_col) {
    if (nitems == 0) return FX_OK;
    if (ncols == 0 || nitems > FX_MAX_ITEMS) return FX_ERR_RANGE;
    if (out_row == NULL || out_col == NULL) return FX_ERR_NULL_ARG;

    /* Track columns occupied by row-spanning items from previous rows.
     * occ[r] bitmask: bit c set = column c is taken by a spanning item. */
    size_t occ[FX_MAX_ITEMS];  /* max rows <= nitems */
    size_t nocc = 0;
    for (size_t i = 0; i < FX_MAX_ITEMS; ++i) occ[i] = 0;

    /* Pass 1 -- EXPLICIT placement (CSS Grid 1 section 8.3). An item whose cell the
     * author named takes that rectangle and marks it occupied, BEFORE any automatic
     * item is placed, so the automatic ones can flow around it (section 8.5). Doing
     * it in one interleaved pass instead would let an earlier automatic item sit in
     * a cell a later named item owns. With fixed_row/fixed_col NULL this pass places
     * nothing and the loop below is bit-for-bit the pre-2026-08-14 algorithm. */
    for (size_t i = 0; i < nitems; ++i) {
        int fr = (fixed_row != NULL) ? fixed_row[i] : -1;
        int fc = (fixed_col != NULL) ? fixed_col[i] : -1;
        if (fr < 0 && fc < 0) continue;
        size_t sp = 1;
        if (span != NULL && span[i] > 1)
            sp = ((size_t)span[i] > ncols) ? ncols : (size_t)span[i];
        size_t rsp = 1;
        if (row_span != NULL && row_span[i] > 1)
            rsp = (size_t)row_span[i];
        /* A cell outside the grid is CLAMPED, not dropped: an item at the edge is
         * a smaller error than an item that disappears. */
        size_t pr = (fr > 0) ? (size_t)fr : 0;
        size_t pc = (fc > 0) ? (size_t)fc : 0;
        if (pc >= ncols) pc = ncols - 1;
        if (pc + sp > ncols) sp = ncols - pc;
        /* The row is NOT bounded by the item count: a named area may legitimately
         * sit in the fourth row of a template with one item in it. The only real
         * bound is the occupancy array. */
        if (pr >= FX_MAX_ITEMS) pr = FX_MAX_ITEMS - 1;
        out_row[i] = pr;
        out_col[i] = pc;
        size_t mask = ((1ull << sp) - 1ull) << pc;
        for (size_t kr = pr; kr < pr + rsp && kr < FX_MAX_ITEMS; ++kr) {
            while (nocc <= kr) { occ[nocc] = 0; ++nocc; }
            occ[kr] |= mask;
        }
    }

    /* Pass 2 -- AUTOMATIC placement over whatever cells are left. */
    size_t r = 0, c = 0;
    for (size_t i = 0; i < nitems; ++i) {
        if ((fixed_row != NULL && fixed_row[i] >= 0) ||
            (fixed_col != NULL && fixed_col[i] >= 0)) continue;   /* placed above */
        size_t sp = 1;
        if (span != NULL && span[i] > 1)
            sp = ((size_t)span[i] > ncols) ? ncols : (size_t)span[i];
        size_t rsp = 1;
        if (row_span != NULL && row_span[i] > 1)
            rsp = (size_t)row_span[i];

        /* Find the first row where `sp` consecutive columns are free,
         * accounting for occupied cells from row-spanning items above.
         * Start from current `r,c` (the cursor was advanced past the
         * previous item). If this is a fresh function call r=c=0. */
        int placed = 0;
        while (!placed && r <= nitems) {
            /* Ensure occ has an entry for this row. */
            while (nocc <= r) { occ[nocc] = 0; ++nocc; }
            /* Search forward from current column. If c was advanced past
             * ncols on the previous item, this inner loop body won't
             * execute and we'll move to the next row below. */
            while (c + sp <= ncols) {
                size_t mask = ((1ull << sp) - 1ull) << c;
                if (mask == 0 || !(occ[r] & mask)) { placed = 1; break; }
                ++c;
            }
            if (!placed) { ++r; c = 0; }
        }
        if (!placed) return FX_ERR_RANGE;

        out_row[i] = r;
        out_col[i] = c;

        /* Advance the cursor so the next item does not re-use these cols. */
        c += sp;
        if (c >= ncols) { ++r; c = 0; }

        /* If this item spans multiple rows, mark its occupied columns in
         * the subsequent (rsp - 1) rows so later items skip them. */
        if (rsp > 1) {
            size_t mask = ((1ull << sp) - 1ull) << out_col[i];
            for (size_t kr = r + 1; kr < r + rsp; ++kr) {
                while (nocc <= kr) { occ[nocc] = 0; ++nocc; }
                occ[kr] |= mask;
            }
        }
    }
    return FX_OK;
}


/* --- grid-template-areas: named placement (spec/grid_areas.md) --------------- */

unsigned fx_grid_area_hash(const char *name) {
    if (name == NULL) return 0u;
    /* Trim both ends first, so the hash of a template token and the hash of the
     * item's `grid-area` value agree no matter how either was spaced. */
    const char *b = name;
    while (*b == ' ' || *b == '\t' || *b == '\n' || *b == '\r' || *b == '\f') ++b;
    const char *e = b;
    while (*e != '\0') ++e;
    while (e > b && (e[-1] == ' ' || e[-1] == '\t' || e[-1] == '\n' ||
                     e[-1] == '\r' || e[-1] == '\f')) --e;
    if (e == b) return 0u;

    /* FNV-1a, 32-bit. */
    unsigned h = 2166136261u;
    for (const char *p = b; p < e; ++p) {
        h ^= (unsigned char)*p;
        h *= 16777619u;
    }
    /* 0 is reserved for "no name" (the null cell token), so a name that hashes to
     * it is nudged; the alternative is a name that silently reads as a hole. */
    return (h == 0u) ? 1u : h;
}

/* True for the null cell token: a single `.` or a run of them (CSS Grid 1 7.3). */
static int area_token_is_null_cell(const char *tok, size_t len) {
    if (len == 0) return 0;
    for (size_t i = 0; i < len; ++i) if (tok[i] != '.') return 0;
    return 1;
}

fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out) {
    if (tmpl == NULL || out == NULL) return FX_ERR_NULL_ARG;
    out->rows = 0;
    out->cols = 0;
    for (size_t i = 0; i < FX_AREA_MAX_CELLS; ++i) out->cell[i] = 0u;

    int rows = 0, cols = -1;
    const char *p = tmpl;
    while (*p != '\0') {
        /* Each ROW of the template is one quoted string; anything between them is
         * ignored (that is where the `grid-template` shorthand's track sizes live). */
        while (*p != '\0' && *p != '\'' && *p != '"') ++p;
        if (*p == '\0') break;
        char quote = *p++;
        const char *row_start = p;
        while (*p != '\0' && *p != quote) ++p;
        if (*p == '\0') { out->rows = 0; return FX_ERR_RANGE; }  /* unterminated */
        const char *row_end = p++;

        if (rows >= FX_AREA_MAX_ROWS) { out->rows = 0; return FX_ERR_RANGE; }

        /* Split this row into whitespace-separated cell tokens. */
        int c = 0;
        const char *q = row_start;
        while (q < row_end) {
            while (q < row_end && (*q == ' ' || *q == '\t')) ++q;
            if (q >= row_end) break;
            const char *tok = q;
            while (q < row_end && *q != ' ' && *q != '\t') ++q;
            size_t len = (size_t)(q - tok);

            if (c >= FX_AREA_MAX_COLS) { out->rows = 0; return FX_ERR_RANGE; }
            size_t idx = (size_t)rows * (size_t)FX_AREA_MAX_COLS + (size_t)c;
            if (idx >= FX_AREA_MAX_CELLS) { out->rows = 0; return FX_ERR_RANGE; }

            if (area_token_is_null_cell(tok, len) || len >= FX_AREA_NAME_MAX) {
                /* A null cell, or a name too long to hold: both are HOLES. An
                 * over-long name is deliberately not truncated -- truncating would
                 * invent a different name and could collide with a real one. */
                out->cell[idx] = 0u;
            } else {
                char name[FX_AREA_NAME_MAX];
                for (size_t k = 0; k < len; ++k) name[k] = tok[k];
                name[len] = '\0';
                out->cell[idx] = fx_grid_area_hash(name);
            }
            ++c;
        }

        if (c == 0) { out->rows = 0; return FX_ERR_RANGE; }      /* empty row */
        /* Every row must declare the same number of columns; CSS 7.3 calls a ragged
         * template invalid, and a ragged grid has no defined geometry to place into. */
        if (cols < 0) cols = c;
        else if (c != cols) { out->rows = 0; return FX_ERR_RANGE; }
        ++rows;
    }

    if (rows == 0 || cols <= 0) { out->rows = 0; return FX_ERR_RANGE; }
    if ((size_t)rows * (size_t)cols > FX_AREA_MAX_CELLS) { out->rows = 0; return FX_ERR_RANGE; }

    /* Cells were written on an FX_AREA_MAX_COLS stride so a ragged template could be
     * detected before committing; compact to the real stride now that cols is known. */
    if (cols != FX_AREA_MAX_COLS) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                out->cell[(size_t)r * (size_t)cols + (size_t)c] =
                    out->cell[(size_t)r * (size_t)FX_AREA_MAX_COLS + (size_t)c];
            }
        }
    }
    out->rows = rows;
    out->cols = cols;
    return FX_OK;
}

fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int *row, int *col, int *row_span, int *col_span) {
    if (m == NULL || row == NULL || col == NULL ||
        row_span == NULL || col_span == NULL) return FX_ERR_NULL_ARG;
    if (name == 0u || m->rows <= 0 || m->cols <= 0) return FX_ERR_RANGE;

    int r0 = m->rows, r1 = -1, c0 = m->cols, c1 = -1;
    int found = 0;
    for (int r = 0; r < m->rows; ++r) {
        for (int c = 0; c < m->cols; ++c) {
            if (m->cell[(size_t)r * (size_t)m->cols + (size_t)c] != name) continue;
            found = 1;
            if (r < r0) r0 = r;
            if (r > r1) r1 = r;
            if (c < c0) c0 = c;
            if (c > c1) c1 = c;
        }
    }
    if (!found) return FX_ERR_RANGE;

    /* A named area is rectangular BY DEFINITION (CSS Grid 1 7.3): if the bounding
     * box holds a cell that is not this name, the template is invalid. Reporting
     * that as "no placement" degrades the one item to auto-placement instead of
     * silently giving it a rectangle that covers someone else's cells. */
    for (int r = r0; r <= r1; ++r) {
        for (int c = c0; c <= c1; ++c) {
            if (m->cell[(size_t)r * (size_t)m->cols + (size_t)c] != name)
                return FX_ERR_RANGE;
        }
    }

    *row = r0;
    *col = c0;
    *row_span = r1 - r0 + 1;
    *col_span = c1 - c0 + 1;
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

fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                          double avail, double *out_l, double *out_r) {
    if (out_l == NULL || out_r == NULL) return FX_ERR_NULL_ARG;
    if (r == NULL && n > 0) return FX_ERR_NULL_ARG;
    if (h < 0.0 || avail < 0.0 || n > FX_MAX_ITEMS) return FX_ERR_RANGE;

    double left = 0.0;
    double right_edge = avail;      /* innermost left edge of any right float */
    for (size_t i = 0; i < n; ++i) {
        /* Half-open overlap: a line that starts exactly at a float's bottom has
         * cleared it and returns to the full width. A zero-height line (measured
         * before its height is known) still consults a float starting at its y,
         * hence the `>=` on the top edge rather than a strict band intersection. */
        if (r[i].bottom <= y) continue;
        if (r[i].top > y + h) continue;
        if (h > 0.0 && r[i].top >= y + h) continue;
        if (r[i].side == 1) {
            if (r[i].edge < right_edge) right_edge = r[i].edge;
        } else {
            if (r[i].edge > left) left = r[i].edge;
        }
    }
    double right = avail - right_edge;
    if (left < 0.0) left = 0.0;
    if (right < 0.0) right = 0.0;

    /* Fail-open geometry: a float wider than its container (or a left and a right
     * float that together overflow it) must still leave a usable line box. The left
     * inset yields first, since dropping it keeps text inside the content rect. */
    double room = avail - FX_FLOAT_MIN_LINE;
    if (room < 0.0) room = 0.0;
    if (right > room) right = room;
    if (left > room - right) left = room - right;
    if (left < 0.0) left = 0.0;

    *out_l = left;
    *out_r = right;
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

/* CSS Flexbox 4.5. See the contract in flex_layout.h. */
double fx_auto_min_size(double min_content, double basis, double author_min,
                        int scroll_container) {
    /* An explicit author min-width means min-width is not `auto`, so the automatic
     * minimum size never applies -- it wins whether it is larger or smaller. */
    if (author_min >= 0.0) return author_min;
    /* A scroll container's automatic minimum size is 0: its content can be scrolled
     * (or clipped) rather than forcing the box wider. */
    if (scroll_container) return 0.0;
    double mc = nn(min_content);
    double b  = nn(basis);
    /* Content size suggestion, clamped by the specified size suggestion. */
    return (mc < b) ? mc : b;
}

fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
                           double gap, int *out_n, double *out_w) {
    if (out_n == NULL || out_w == NULL) return FX_ERR_NULL_ARG;

    if (!(avail_w > 0.0)) { *out_n = 1; *out_w = (avail_w > 0.0) ? avail_w : 1.0; return FX_OK; }
    if (!(gap > 0.0)) gap = 0.0;

    int have_count = (column_count > 0);
    int have_width = (column_width > 0.0);

    int n;
    if (!have_count && !have_width) {
        /* Not a multi-column container. Fail closed: with neither property the
         * element must lay out exactly as it did before this feature existed. */
        *out_n = 1;
        *out_w = avail_w;
        return FX_OK;
    }
    if (!have_width) {
        n = column_count;
    } else {
        /* How many columns of at least column_width fit, gaps included. */
        double fit = (avail_w + gap) / (column_width + gap);
        n = (fit >= 1.0) ? (int)fit : 1;
        if (have_count && column_count < n) n = column_count;
    }
    if (n < 1) n = 1;
    if (n > (int)FX_MAX_COLUMNS) n = (int)FX_MAX_COLUMNS;

    double w = (avail_w - gap * (double)(n - 1)) / (double)n;
    if (!(w >= 1.0)) w = 1.0;

    *out_n = n;
    *out_w = w;
    return FX_OK;
}

fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                              int *out_col, double *out_colh) {
    if (ncol < 1 || ncol > (int)FX_MAX_COLUMNS) return FX_ERR_RANGE;
    if (n > FX_MAX_ITEMS) return FX_ERR_RANGE;
    if (out_colh == NULL) return FX_ERR_NULL_ARG;
    for (int c = 0; c < ncol; ++c) out_colh[c] = 0.0;
    if (n == 0) return FX_OK;
    if (heights == NULL || out_col == NULL) return FX_ERR_NULL_ARG;

    double total = 0.0;
    for (size_t i = 0; i < n; ++i) if (heights[i] > 0.0) total += heights[i];
    double target = total / (double)ncol;

    int c = 0;
    double acc = 0.0;
    for (size_t i = 0; i < n; ++i) {
        double h = (heights[i] > 0.0) ? heights[i] : 0.0;
        /* Move on once this column has reached the balanced target, but never
         * leave a column empty just to honour it, and never run past the last
         * column -- the remainder always lands somewhere. */
        if (c < ncol - 1 && acc > 0.0 && acc >= target) {
            ++c;
            acc = 0.0;
        }
        out_col[i] = c;
        acc += h;
        out_colh[c] += h;
    }
    return FX_OK;
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
