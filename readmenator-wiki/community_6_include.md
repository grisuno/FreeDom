# include

*Community 6 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `ABSENT`, `FREEDOM_BLOCK_FLOW_H`, `bf_collapse`, `bf_collapse_n`, `bf_margins_adjoin`, `dbl_eq`, `finite_or_zero`, `main`. Core file: `tests/test_block_flow.c` (8 symbols). Documented purpose: block_flow (bf_) -- vertical margin collapsing for block-level boxes..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/block_flow.h` | h | utility | 4 | yes |
| `src/block_flow.c` | c | utility | 4 | yes |
| `tests/test_block_flow.c` | c | testing | 8 | no |

## Key Symbols

- `FREEDOM_BLOCK_FLOW_H` (macro, `include/block_flow.h:11`) `#define FREEDOM_BLOCK_FLOW_H`
- `ABSENT` (function, `include/block_flow.h:26`) `* as ABSENT (0) rather than propagated: a poisoned length must not spread into *`
- `bf_collapse_n` (function, `include/block_flow.h:33`) `* bf_collapse_n((double[])`
- `bf_margins_adjoin` (function, `include/block_flow.h:43`) `int bf_margins_adjoin(double border_px, double padding_px);` - Whether two vertical margins separated by this much border and padding ADJOIN, i.e. whether they col
- `finite_or_zero` (function, `src/block_flow.c:11`) `static double finite_or_zero(double v)` - A margin the caller could not compute (NaN from a hostile calc(), an infinity from an overflowing un
- `bf_collapse_n` (function, `src/block_flow.c:15`) `double bf_collapse_n(const double *m, size_t n)`
- `bf_collapse` (function, `src/block_flow.c:30`) `double bf_collapse(double a, double b)`
- `bf_margins_adjoin` (function, `src/block_flow.c:35`) `int bf_margins_adjoin(double border_px, double padding_px)`
- `dbl_eq` (function, `tests/test_block_flow.c:21`) `static int dbl_eq(double a, double b)`
- `test_two_positive_collapse_to_max` (function, `tests/test_block_flow.c:29`) `static void test_two_positive_collapse_to_max(void **state)` - Two positive margins collapse to the LARGER, never to their sum: this is the whole reason a paragrap
- `test_two_negative_take_the_most_negative` (function, `tests/test_block_flow.c:50`) `static void test_two_negative_take_the_most_negative(void **state)` - Two negatives: the most negative wins (max of absolute values, deducted). * max(a, b) answers -10 he
- `test_non_finite_is_absent` (function, `tests/test_block_flow.c:59`) `static void test_non_finite_is_absent(void **state)` - A non-finite margin is ABSENT, not propagated: a hostile calc() that divides by * zero must not pois
- `test_collapse_n_matches_binary` (function, `tests/test_block_flow.c:70`) `static void test_collapse_n_matches_binary(void **state)` - The n-ary form is the same rule and agrees with the binary one, so a caller can * collapse a chain o
- `test_collapse_n_edges` (function, `tests/test_block_flow.c:84`) `static void test_collapse_n_edges(void **state)` - static void test_collapse_n_matches_binary(void **state) { (void)state; double pair[2] = { 30.0, -10
- `test_margins_adjoin` (function, `tests/test_block_flow.c:95`) `static void test_margins_adjoin(void **state)` - Margins adjoin only when NOTHING separates them; any border or padding stops the * collapse. Non-fin
- `main` (function, `tests/test_block_flow.c:105`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/block_flow.h.
- [INFERRED] shares_context community 1 <-> 6 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (include) and community 6 (include).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `tests/test_block_flow.c`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.67?

## Sources

- `include/block_flow.h`
- `src/block_flow.c`
- `tests/test_block_flow.c`
