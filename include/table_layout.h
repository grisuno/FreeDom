/* table_layout (tl_) -- used column widths of a table (automatic table layout).
 *
 * CSS 2.1 section 17.5.2.2, with the surplus distribution of css-tables-3 3.9. Pure, total,
 * allocation-free, reentrant: arithmetic over doubles with no I/O and no global state. The
 * caller measures each cell (min-content, max-content, declared width) and this module decides
 * how wide every column is.
 *
 * Contract, error table and the out-of-scope list live in spec/table_layout.md.
 */
#ifndef FREEDOM_TABLE_LAYOUT_H
#define FREEDOM_TABLE_LAYOUT_H

#ifdef __cplusplus
#error "Freedom is pure C11 by policy; C++ is not supported."
#endif

#include <stddef.h>

/* Columns one table may have. A table past this is laid out by the caller's fallback. */
#define TL_MAX_COLS 64u

/* Largest width (px) any input may carry; larger values are capped. */
#define TL_WIDTH_MAX 1.0e9

/* A cell's percentage width is carried in per-mille; this is 100%. */
#define TL_PER_MILLE 1000

typedef struct tl_cell {
    int    col;      /* first column the cell occupies, 0-based */
    int    span;     /* columns it covers; < 1 is read as 1 */
    double min_w;    /* min-content width of its border box, px */
    double max_w;    /* max-content width of its border box, px */
    double decl_w;   /* declared border-box width in px; < 0 means auto */
    int    pct;      /* declared width as per-mille of the table (width: N%); 0 = none */
} tl_cell;

/* Writes the used width of each of the ncols columns into out[] and returns the used width of
 * the whole table (columns plus the gaps between them).
 *
 * avail is the containing block's width; table_w the table's declared width already resolved to
 * px (< 0 = auto: the table is as wide as its content, capped at avail). gap is the space
 * between adjacent columns.
 *
 * Returns 0.0 and writes nothing when out is NULL or ncols is 0 or above TL_MAX_COLS. Every
 * non-finite or negative width in the input reads as 0, so no out[] entry is ever negative or
 * non-finite. */
double tl_columns(const tl_cell *cells, size_t n, size_t ncols, double gap,
                  double avail, double table_w, double *out);

/* The table's min-content and max-content widths (columns plus gaps): what it contributes
 * when it is itself a cell of an outer table. Either output may be NULL. Both are 0 for an
 * invalid ncols. */
void tl_intrinsic(const tl_cell *cells, size_t n, size_t ncols, double gap,
                  double *min_total, double *max_total);

#endif /* FREEDOM_TABLE_LAYOUT_H */
