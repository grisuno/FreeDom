/* block_flow (bf_) -- vertical margin collapsing for block-level boxes.
 *
 * CSS 2.1 section 8.3.1. Pure, total, allocation-free, reentrant: every function
 * here is arithmetic over doubles with no I/O and no global state, so the rule
 * that decides the vertical space between two blocks can be tested in isolation
 * instead of being spelled out inline at each of the layout engine's call sites.
 *
 * Contract, error table and the out-of-scope list live in spec/block_flow.md.
 */
#ifndef FREEDOM_BLOCK_FLOW_H
#define FREEDOM_BLOCK_FLOW_H

#ifdef __cplusplus
#error "Freedom is pure C11 by policy; C++ is not supported."
#endif

#include <stddef.h>

/* The used space between two ADJOINING vertical margins (CSS 2.1 section 8.3.1):
 * the maximum of the positive margins, plus the most negative of the negative
 * ones. This is NOT max(a, b) -- that only coincides with the rule while both
 * margins are positive, and `margin-top: -1px` to overlap adjacent borders is a
 * commonplace idiom.
 *
 * Non-finite inputs (NaN, +/-inf, which a hostile calc() can produce) are treated
 * as ABSENT (0) rather than propagated: a poisoned length must not spread into
 * the geometry of the rest of the page. */
double bf_collapse(double a, double b);

/* The same rule over a set of margins that all adjoin each other (a chain of empty
 * boxes; a parent's margin adjoining its first/last child's). Returns 0.0 for
 * n == 0 or m == NULL. Associative and consistent with bf_collapse:
 * bf_collapse_n((double[]){a, b}, 2) == bf_collapse(a, b). */
double bf_collapse_n(const double *m, size_t n);

/* Whether two vertical margins separated by this much border and padding ADJOIN,
 * i.e. whether they collapse at all (CSS 2.1 section 8.3.1): they do only when
 * nothing separates them. Returns 1 when both are exactly zero, 0 otherwise.
 *
 * Fails CLOSED on non-finite input (returns 0, "does not collapse"): collapsing a
 * margin that should not collapse deletes space the author asked for and fuses two
 * blocks into one, which is the more destructive of the two errors. */
int bf_margins_adjoin(double border_px, double padding_px);

#endif /* FREEDOM_BLOCK_FLOW_H */
