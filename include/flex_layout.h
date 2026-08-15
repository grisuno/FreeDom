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

/* Grid columns with per-track sizes (2026-07-11). track[i] encodes track i:
 * 0 = auto (a 1fr share), > 0 = fixed px, < 0 = fr weight x100 (2fr -> -200);
 * tracks at i >= ntrack (or a NULL track) are auto. Fixed tracks reserve their px
 * first; the remaining space (avail - gaps - fixed, clamped >= 0) splits
 * proportionally by fr weight. All-auto reproduces fx_grid_columns exactly.
 * Same contracts as fx_grid_columns otherwise. */
fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                                   const int *track, size_t ntrack,
                                   double *col_x, double *col_w);

/* Row-major placement honouring grid-column spans (2026-07-11). span[i] (<= 0 or a
 * NULL span array = 1) is clamped to [1, ncols]; an item whose span does not fit in
 * the columns remaining on its row jumps to the next row (CSS auto-placement).
 * Writes each item's row and starting column. nitems == 0 is a no-op; ncols == 0 or
 * nitems > FX_MAX_ITEMS fails closed.
 *
 * fixed_row/fixed_col (2026-08-14, either or both may be NULL; -1 in an entry means
 * "auto") give an item an EXPLICIT cell -- what `grid-area: <name>` resolves to via
 * fx_grid_area_rect. Such an item claims its rectangle and does not move the
 * auto-placement cursor; the automatic items then flow around the cells already
 * taken, which is CSS Grid 1 section 8.5. With both arrays NULL the result is
 * byte-identical to the pre-2026-08-14 behaviour. */
fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                              const int *row_span,
                              const int *fixed_row, const int *fixed_col,
                              size_t *out_row, size_t *out_col);

/* --- grid-template-areas: named placement (CSS Grid 1 sections 7.3 + 8.4) ------
 * Full contract, error table and out-of-scope list: spec/grid_areas.md. */

/* Bounds on a parsed area template. The template is author CSS -- i.e. attacker
 * chosen -- so every one of these is checked BEFORE anything is written. */
#define FX_AREA_MAX_ROWS  16
#define FX_AREA_MAX_COLS  16
#define FX_AREA_MAX_CELLS 128
#define FX_AREA_NAME_MAX  64

/* A parsed grid-template-areas: a rows x cols grid of NAME HASHES in row-major
 * order. 0 is the null cell token (`.`), never a name. rows == 0 means "no valid
 * template" -- the only state fx_grid_areas_parse leaves behind on failure. */
typedef struct fx_area_map {
    int      rows, cols;
    unsigned cell[FX_AREA_MAX_CELLS];
} fx_area_map;

/* FNV-1a of a trimmed, case-sensitive CSS identifier; never returns 0 for a
 * non-empty name (0 is reserved for "unnamed"). NULL/empty/blank -> 0. Comparing
 * hashes rather than strings is what lets an item's area name cross the IPC codec
 * as one int; see spec/grid_areas.md section 2 on collisions. */
unsigned fx_grid_area_hash(const char *name);

/* Parses the raw `grid-template-areas` value (quoted strings, one per row) into
 * *out. Ragged rows, an over-large template and an empty template all fail closed
 * with FX_ERR_RANGE and out->rows == 0. Allocation-free. */
fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out);

/* The rectangle of the named area: the smallest rect covering every cell with that
 * name. FX_ERR_RANGE (outputs untouched) when the name is absent, is 0, or its
 * cells do not form a filled rectangle -- the caller then auto-places the item,
 * which is what a browser does with a grid-area that names nothing. */
fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name,
                            int *row, int *col, int *row_span, int *col_span);

/* Float packing (one band; spec/float.md). Packs n float items along one axis:
 * side[i] == 0 (left) items advance a cursor from the content start (0) rightward in
 * document order; side[i] == 1 (right) items advance a cursor from `avail` leftward in
 * document order; adjacent same-side items are separated by gap. Writes each item's x
 * offset (from the content start, clamped to >= 0) to out_x[n]. The band does NOT wrap
 * (v1): an item that would overflow still gets a clamped position. Pure, no allocation.
 * n == 0 is a no-op (pointers may be NULL). Returns FX_ERR_NULL_ARG (a required pointer
 * NULL with n > 0), FX_ERR_RANGE (avail/gap negative, or n > FX_MAX_ITEMS). */
fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        double avail, double gap, double *out_x);

/* Float packing with greedy row wrap (v2, Hito 32; spec/float.md §7b). Same cursor
 * discipline as fx_float_pack, but an item that no longer fits between the two
 * cursors starts a NEW row (cursors reset; out_row[n] receives each item's 0-based
 * row). An item wider than avail alone still gets a clamped x = 0 and consumes its
 * row. This is what makes consecutive full-width floats
 * (.grid_24 { width:99.8%; float:left }) STACK instead of cramming one row.
 * out_row is required (NULL with n > 0 yields FX_ERR_NULL_ARG); other errors as
 * fx_float_pack. */
fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                             double avail, double gap, double *out_x,
                             size_t *out_row);

/* Minimum room a line box keeps beside a float, in px. A float wider than its
 * container must still leave a usable line rather than a zero/negative one. */
#define FX_FLOAT_MIN_LINE 1.0

/* One float exclusion (v3, spec/float.md §6b.2): the vertical band a float occupies
 * and the INNER content edge it steals. `edge` is measured from the content start:
 * for side 0 (left) it is the x just past the float's right margin; for side 1
 * (right) it is the x of the float's left margin. */
typedef struct fx_float_rect {
    double top, bottom;
    double edge;
    int    side;        /* 0 = left float, 1 = right float */
} fx_float_rect;

/* Insets a line box occupying [y, y + h) must apply to avoid n float exclusions
 * (CSS 2.1 section 9.5: a float shortens the line boxes it overlaps, it does not move
 * the block). *out_l is the left inset, *out_r the right inset, both from the content
 * edges of an `avail`-wide content rect. A rect contributes only while it vertically
 * overlaps the half-open band, so a line that clears a float's bottom returns to the
 * full width. Both insets are clamped to >= 0 and to leave at least FX_FLOAT_MIN_LINE
 * of room: a float wider than avail yields a narrow line, never a negative one
 * (fail-open geometry). Pure, no allocation, no I/O. n == 0 writes 0/0.
 * Returns FX_ERR_NULL_ARG (a required pointer NULL with n > 0), FX_ERR_RANGE
 * (negative h/avail, or n > FX_MAX_ITEMS); nothing is written on error. */
fx_status fx_float_insets(const fx_float_rect *r, size_t n, double y, double h,
                          double avail, double *out_l, double *out_r);

/* Automatic minimum size of a flex item along the main axis (CSS Flexbox 4.5), in px.
 * This is what `min-width: auto` -- the INITIAL value, so the case for almost every
 * item on the web -- resolves to. It is the floor fx_flex_line must not shrink an
 * item below, and getting it wrong is visible everywhere: with a floor of zero an
 * overflowing line grinds every item down to a sliver and its text falls to one
 * character per line.
 *
 *   min_content  the item's min-content size (its longest unbreakable word, or a
 *                replaced element's intrinsic size), in the same border-box+margin
 *                units as fx_item.basis. Negative is treated as 0.
 *   basis        the item's base size, used as the "specified size suggestion": the
 *                content-based minimum is clamped by it, so an item the author sized
 *                small is not inflated by one long word. Negative is treated as 0.
 *   author_min   the author's own `min-width` in px when they set one (min-width is
 *                then NOT `auto` and wins outright, larger OR smaller), or < 0 when
 *                unset.
 *   scroll_container  non-zero when the item's `overflow` is anything but `visible`.
 *                Such an item has an automatic minimum size of ZERO -- this is what
 *                makes the near-universal `overflow:hidden` truncation idiom work.
 *
 * Pure, total, no allocation. The result is never negative. */
double fx_auto_min_size(double min_content, double basis, double author_min,
                        int scroll_container);

/* Maximum columns a multi-column container is laid out with (anti-DoS). A larger
 * `column-count` is clamped to it; real stylesheets ask for two to four. */
#define FX_MAX_COLUMNS 16u

/*
 * Used column count and column width of a multi-column container (CSS
 * Multi-column Layout Level 1, section 3.4).
 *
 *   avail_w        the container's content width (px).
 *   column_count   the author's `column-count`, or 0/negative for `auto`.
 *   column_width   the author's `column-width` in px, or 0/negative for `auto`.
 *   gap            the used `column-gap` in px (negative is treated as 0).
 *
 * The rule, and the reason it cannot be simplified: `column-width` is a MINIMUM,
 * not a fixed width. The count falls out of how many columns of at least that
 * width fit, which is what makes one stylesheet render one column on a narrow
 * viewport and three on a wide one. Hardcoding either half would turn
 * `column-width` into a no-op or a fixed division -- both invented rules.
 *
 *   both auto      -> not a multi-column container: *out_n = 1, *out_w = avail_w
 *   width auto     -> N = column-count
 *   count auto     -> N = max(1, floor((avail_w + gap) / (column_width + gap)))
 *   both           -> N = min(column-count, that same fitting count)
 *
 * and in every case *out_w = (avail_w - (N-1)*gap) / N, floored at 1px.
 *
 * N is clamped to [1, FX_MAX_COLUMNS]. Pure, total, no allocation. Returns
 * FX_ERR_NULL_ARG if either out pointer is NULL; otherwise FX_OK.
 */
fx_status fx_multicol_used(double avail_w, int column_count, double column_width,
                           double gap, int *out_n, double *out_w);

/*
 * Distributes `n` already-measured row heights over `ncol` columns so the
 * columns come out as even as possible -- the initial `column-fill: balance`.
 *
 * A row is never split: the smallest fragmentation unit this engine has is the
 * line box, which is also what CSS Fragmentation calls a class A break point
 * (between line boxes). So a single row taller than the balanced target simply
 * makes its column taller, exactly as in a real UA.
 *
 *   heights   per-row heights in document order (negative is treated as 0).
 *   out_col   receives each row's 0-based column index (caller-owned, n entries).
 *   out_colh  receives each column's total height (caller-owned, ncol entries).
 *
 * ncol outside [1, FX_MAX_COLUMNS] or n > FX_MAX_ITEMS fails closed with
 * FX_ERR_RANGE. Pure, total, no allocation.
 */
fx_status fx_multicol_balance(const double *heights, size_t n, int ncol,
                              int *out_col, double *out_colh);

/* Stable, short English name of a justify mode for structured/agent output. Never
 * NULL; an unknown enum value yields "start". */
const char *fx_justify_name(fx_justify j);

#endif /* FREEDOM_FLEX_LAYOUT_H */
