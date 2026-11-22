/*
 * find_text (ft_) -- find in page over the rendered text (spec/find_text.md).
 *
 * Pure: no I/O, no global state, reentrant. The text is hostile UTF-8 (never read
 * outside [text, text + len)); the query is the user's.
 */
#ifndef FREEDOM_FIND_TEXT_H
#define FREEDOM_FIND_TEXT_H

#ifdef __cplusplus
#error "find_text is C11 only"
#endif

#include <stddef.h>
#include <stdint.h>

#define FT_QUERY_MAX 256u   /* folded code points kept from the query */
#define FT_MATCH_MAX 1000u  /* matches the GUI keeps (Firefox: "More than 1000") */

typedef enum ft_status { FT_OK = 0, FT_EINVAL = -1 } ft_status;

/* One laid-out text piece. gap_before = 1: white space separates it from the previous
 * piece (another line or block, or a pen gap between words). */
typedef struct ft_piece {
    const char *text;
    size_t      len;
    int         gap_before;
} ft_piece;

typedef struct ft_pos   { size_t piece; size_t off; } ft_pos;
typedef struct ft_match { ft_pos start, end; } ft_match;    /* end exclusive */
typedef struct ft_span  { size_t piece, start, end, match; } ft_span;

/* Case- and (Latin) diacritic-insensitive fold of one code point. */
uint32_t ft_fold(uint32_t cp);

/* Folds the query, trims it and collapses white space to one ' ' (U+0020). Returns the
 * number of code points written (<= cap, <= FT_QUERY_MAX); 0 for an empty query. */
size_t ft_compile(const char *q, size_t qlen, uint32_t *out, size_t cap);

/* Non-overlapping matches of q[0..qn) in document order. *truncated = 1 when more than
 * cap matches exist (truncated may be NULL). */
ft_status ft_search(const ft_piece *pieces, size_t n, const uint32_t *q, size_t qn,
                    ft_match *out, size_t cap, size_t *nout, int *truncated);

/* Splits matches into per-piece spans (one per piece a match touches, empty spans
 * dropped), in order. Returns the number written (<= cap). */
size_t ft_spans(const ft_piece *pieces, size_t n, const ft_match *m, size_t nm,
                ft_span *out, size_t cap);

/* Next (dir > 0) or previous (dir < 0) match index with wrap-around; -1 when n == 0.
 * A cur outside [0, n) starts at the first (dir > 0) or last (dir < 0) match. */
long ft_step(long cur, size_t n, int dir);

#endif /* FREEDOM_FIND_TEXT_H */
