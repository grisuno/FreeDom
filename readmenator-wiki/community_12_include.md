# include

*Community 12 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `include` with dominant language c (cohesion 0.67). Central symbols: `FC_DEFAULT_INTERVAL_MS`, `FREEDOM_FRAME_CLOCK_H`, `active`, `fc_clock`, `fc_init`, `fc_interval_ms`, `fc_needs_tick`, `fc_set_active`. Core file: `include/frame_clock.h` (7 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `include/frame_clock.h` | h | utility | 7 | no |
| `src/frame_clock.c` | c | utility | 4 | no |
| `tests/test_frame_clock.c` | c | testing | 4 | no |

## Key Symbols

- `FREEDOM_FRAME_CLOCK_H` (macro, `include/frame_clock.h:2`) `#define FREEDOM_FRAME_CLOCK_H`
- `active` (type_alias, `include/frame_clock.h:14`) `typedef struct fc_clock { int active;` - frame_clock (fc_) — pure animation frame scheduler. Phase R1a. Tracks whether a steady repaint clock
- `fc_clock` (struct, `include/frame_clock.h:15`)
- `fc_init` (function, `include/frame_clock.h:20`) `void fc_init(fc_clock *c);`
- `fc_set_active` (function, `include/frame_clock.h:21`) `void fc_set_active(fc_clock *c, int active);`
- `fc_needs_tick` (function, `include/frame_clock.h:22`) `int fc_needs_tick(const fc_clock *c);`
- `fc_interval_ms` (function, `include/frame_clock.h:23`) `int fc_interval_ms(const fc_clock *c);`
- `FC_DEFAULT_INTERVAL_MS` (macro, `src/frame_clock.c:8`) `#define FC_DEFAULT_INTERVAL_MS`
- `fc_set_active` (function, `src/frame_clock.c:16`) `void fc_set_active(fc_clock *c, int active)`
- `fc_needs_tick` (function, `src/frame_clock.c:21`) `int fc_needs_tick(const fc_clock *c)`
- `fc_interval_ms` (function, `src/frame_clock.c:26`) `int fc_interval_ms(const fc_clock *c)`
- `test_set_active_and_needs_tick` (function, `tests/test_frame_clock.c:23`) `static void test_set_active_and_needs_tick(void **state)`
- `test_set_active_twice` (function, `tests/test_frame_clock.c:36`) `static void test_set_active_twice(void **state)`
- `test_null_safe` (function, `tests/test_frame_clock.c:45`) `static void test_null_safe(void **state)`
- `main` (function, `tests/test_frame_clock.c:53`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 3 <-> 12 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/frame_clock.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 3 file(s) lack file-level docs (e.g. `include/frame_clock.h`)? What purpose do they serve?
- What would break if the most connected file in include changed?
- Should include be split, given cohesion 0.67?

## Sources

- `include/frame_clock.h`
- `src/frame_clock.c`
- `tests/test_frame_clock.c`
