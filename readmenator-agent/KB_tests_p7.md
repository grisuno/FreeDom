# Subsystem: tests (page 7 of 7)
Previous: [KB_tests_p6.md](KB_tests_p6.md)

## tests/test_ws_hub.c
- Doc: wait_notify: #include <string.h> #include <cmocka.h> #include "ws_hub.h" typedef struct rec {...
- Layer: testing
- Language: c
- Symbols:
  - `rec` (struct, line 19)
  - `n` (type_alias, line 18) `typedef struct rec { int n;`
  - `emit` (function, line 21) `static void emit(void *ctx, int id, int kind, int code, const char *data, size_t len)`
  - `wait_notify` (function, line 28) `static void wait_notify(wh_hub *h, rec *r)`
  - `test_new_free` (function, line 34) `static void test_new_free(void **state)`
  - `test_failed_open_reports_error_then_close` (function, line 47) `static void test_failed_open_reports_error_then_close(void **state)`
  - `test_duplicate_and_capacity` (function, line 64) `static void test_duplicate_and_capacity(void **state)`
  - `test_close_all_drops_late_results` (function, line 85) `static void test_close_all_drops_late_results(void **state)`
  - `test_close_cancels_pending_open` (function, line 102) `static void test_close_cancels_pending_open(void **state)`
  - `test_send_unknown_and_readable_unknown` (function, line 115) `static void test_send_unknown_and_readable_unknown(void **state)`
  - `test_free_with_pending_open` (function, line 132) `static void test_free_with_pending_open(void **state)`
  - `main` (function, line 142) `int main(void)`
  - `_POSIX_C_SOURCE` (macro, line 7) `#define _POSIX_C_SOURCE`
- Depends on: `include/ws_hub.h`

## tests/test_zoom.c
- Layer: testing
- Language: c
- Symbols:
  - `test_clamp_bounds` (function, line 17) `static void test_clamp_bounds(void **state)`
  - `test_reset_is_default` (function, line 27) `static void test_reset_is_default(void **state)`
  - `test_zoom_in_steps_ladder` (function, line 33) `static void test_zoom_in_steps_ladder(void **state)`
  - `test_zoom_out_steps_ladder` (function, line 41) `static void test_zoom_out_steps_ladder(void **state)`
  - `test_step_snaps_off_ladder` (function, line 49) `static void test_step_snaps_off_ladder(void **state)`
  - `test_ends_are_idempotent` (function, line 59) `static void test_ends_are_idempotent(void **state)`
  - `test_repeated_in_reaches_max` (function, line 67) `static void test_repeated_in_reaches_max(void **state)`
  - `test_repeated_out_reaches_min` (function, line 79) `static void test_repeated_out_reaches_min(void **state)`
  - `test_scale_factor` (function, line 91) `static void test_scale_factor(void **state)`
  - `test_apply_scales_and_floors` (function, line 100) `static void test_apply_scales_and_floors(void **state)`
  - `main` (function, line 112) `int main(void)`
- Depends on: `include/zoom.h`

