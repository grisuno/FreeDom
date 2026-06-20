#ifndef FREEDOM_FLEX_LAYOUT_H
#define FREEDOM_FLEX_LAYOUT_H

#include <stddef.h>

#ifdef __cplusplus
#error "Freedom is pure C (C11). C++ is not supported."
#endif

/*
 * flex_layout — pure flexbox (single-line) and basic grid geometry solver.
 *
 * No I/O, no global state, no dynamic allocation: given a container size and each
 * item's flex parameters, it computes positions and sizes along the main axis. It
 * measures no text, paints nothing, touches no DOM. The presentation layer applies
 * the resulting rectangles to Cairo; the box-tree builder feeds the inputs.
 *
 * It is the continuation of box_style: once an element is classified
 * BX_DISPLAY_FLEX or BX_DISPLAY_GRID, this solver resolves the geometry. Isolating
 * the flex arithmetic here makes the place a hostile document could try to force
 * overflow or a divide-by-zero auditable without Wayland or the network.
 *
 * See spec/flex_layout.md for the full contract.
 */

/* Upper bound on items per flex line / grid columns. Caps the O(n) shrink loop and
 * keeps the fixed-size scratch buffers bounded (anti-DoS; no VLAs). */
#define FX_MAX_ITEMS 512u

typedef enum fx_justify {
    FX_JUSTIFY_START = 0,
    FX_JUSTIFY_END,
    FX_JUSTIFY_CENTER,
    FX_JUSTIFY_SPACE_BETWEEN,
    FX_JUSTIFY_SPACE_AROUND,
    FX_JUSTIFY_SPACE_EVENLY
} fx_justify;

/* One flex item, all sizes in px. Negative fields are treated as 0. */
typedef struct fx_item {
    double basis;   /* flex-basis: preferred main-axis size */
    double grow;    /* flex-grow factor */
    double shrink;  /* flex-shrink factor */
    double min;     /* minimum main-axis size; the item never shrinks below it */
} fx_item;

/* One resolved item: main-axis offset from the container content start, and size. */
typedef struct fx_result {
    double pos;
    double size;
} fx_result;

typedef enum fx_status {
    FX_OK = 0,
    FX_ERR_NULL_ARG,  /* a required pointer was NULL with n/ncols > 0 */
    FX_ERR_RANGE      /* avail/gap negative, or n/ncols above FX_MAX_ITEMS */
} fx_status;

/* Resolves one flex line along the main axis. avail is the container's main
 * content size (px); gap is the space between adjacent items; justify distributes
 * leftover space only when the items do not grow to fill the line. Writes n
 * fx_result to out (caller-owned). n == 0 is a no-op (out may be NULL). */
fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                       fx_justify justify, fx_result *out);

/* Basic grid: ncols equal-width columns (repeat(ncols, 1fr)) separated by gap.
 * Writes each column's x offset to col_x[ncols] and width to col_w[ncols].
 * ncols == 0 is a no-op (pointers may be NULL). */
fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          double *col_x, double *col_w);

/* Row and column of the index-th item placed row-major into ncols columns.
 * ncols == 0 yields row = col = 0 (defensive; no divide-by-zero). */
void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);

/* Stable, short English name of a justify mode for structured/agent output. Never
 * NULL; an unknown enum value yields "start". */
const char *fx_justify_name(fx_justify j);

#endif /* FREEDOM_FLEX_LAYOUT_H */
