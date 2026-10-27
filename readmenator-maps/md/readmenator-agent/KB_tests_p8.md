# Subsystem: tests (page 8 of 8)
Previous: [KB_tests_p7.md](KB_tests_p7.md)

## tests/test_webcaps.c
- Doc: mk: projection, and the headless operator-flag path.  #include <setjmp.h> #include <stdarg.h>...
- Layer: testing
- Language: c
- Symbols:
  - `mk` (function, line 20) `static wc_input mk(jsp_mode mode, int in_js, int in_allow)`
  - `test_safe_is_all_off` (function, line 29) `static void test_safe_is_all_off(void **state)`
  - `test_trusted_host_gets_all_caps` (function, line 38) `static void test_trusted_host_gets_all_caps(void **state)`
  - `test_present_trust_css_images_only` (function, line 56) `static void test_present_trust_css_images_only(void **state)`
  - `test_jspon_alone_is_not_trust` (function, line 85) `static void test_jspon_alone_is_not_trust(void **state)`
  - `test_user_toggles_grant_leakfree` (function, line 100) `static void test_user_toggles_grant_leakfree(void **state)`
  - `test_bad_mode_fails_closed` (function, line 127) `static void test_bad_mode_fails_closed(void **state)`
  - `test_render_caps_projection` (function, line 138) `static void test_render_caps_projection(void **state)`
  - `test_from_flags_headless` (function, line 153) `static void test_from_flags_headless(void **state)`
  - `assert_memory_equal` (function, line 176) `assert_memory_equal(&(rdp_caps)`
  - `main` (function, line 181) `int main(void)`
- Depends on: `include/webcaps.h`

## tests/test_webfont.c
- Layer: testing
- Language: c
- Symbols:
  - `test_scan_basic_two_formats` (function, line 36) `static void test_scan_basic_two_formats(void **state)`
  - `test_scan_weight_style` (function, line 55) `static void test_scan_weight_style(void **state)`
  - `test_scan_local_only_yields_nothing` (function, line 81) `static void test_scan_local_only_yields_nothing(void **state)`
  - `test_scan_quoted_family_variants` (function, line 92) `static void test_scan_quoted_family_variants(void **state)`
  - `test_scan_case_and_ws` (function, line 106) `static void test_scan_case_and_ws(void **state)`
  - `test_scan_hostile_truncations` (function, line 120) `static void test_scan_hostile_truncations(void **state)`
  - `test_scan_overlong_url_dropped` (function, line 140) `static void test_scan_overlong_url_dropped(void **state)`
  - `test_supported_format` (function, line 155) `static void test_supported_format(void **state)`
  - `test_scan_ignores_other_at_rules` (function, line 168) `static void test_scan_ignores_other_at_rules(void **state)`
  - `test_data_url_decodes_at_scan` (function, line 181) `static void test_data_url_decodes_at_scan(void **state)`
  - `test_ref_move_transfers_bytes` (function, line 198) `static void test_ref_move_transfers_bytes(void **state)`
  - `test_name_hash` (function, line 218) `static void test_name_hash(void **state)`
  - `main` (function, line 229) `int main(void)`
- Depends on: `include/webfont.h`

## tests/test_webfont_load.c
- Doc: test_b64: if (b == NULL) { fclose(f); return NULL; } if (fread(b, 1, (size_t)sz, f) !=...
- Layer: testing
- Language: c
- Symbols:
  - `stub` (struct, line 30)
  - `stub_fetch` (function, line 38) `static int stub_fetch(void *ctx, const char *url,
                      int *out_status, char **o...`
  - `read_host_font` (function, line 64) `static unsigned char *read_host_font(size_t *out_n)`
  - `test_b64` (function, line 92) `static char *test_b64(const unsigned char *in, size_t n)`
  - `test_null_args` (function, line 113) `static void test_null_args(void **state)`
  - `test_https_stub_registers` (function, line 126) `static void test_https_stub_registers(void **state)`
  - `test_woff2_never_fetched` (function, line 152) `static void test_woff2_never_fetched(void **state)`
  - `test_fallback_second_url` (function, line 170) `static void test_fallback_second_url(void **state)`
  - `test_first_wins` (function, line 194) `static void test_first_wins(void **state)`
  - `test_extern_sheet_relative_url` (function, line 217) `static void test_extern_sheet_relative_url(void **state)`
  - `test_data_url_bad_bytes_skipped` (function, line 240) `static void test_data_url_bad_bytes_skipped(void **state)`
  - `test_data_url_registers` (function, line 255) `static void test_data_url_registers(void **state)`
  - `test_null_page_data_only` (function, line 288) `static void test_null_page_data_only(void **state)`
  - `teardown` (function, line 318) `static int teardown(void **state)`
  - `main` (function, line 325) `int main(void)`
  - `_POSIX_C_SOURCE` (macro, line 13) `#define _POSIX_C_SOURCE`
- Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`, `include/webfont_load.h`

## tests/test_wl_display.c
- Doc: test_wl_display — CMocka suite for the pure Wayland socket picker.
- Layer: testing
- Language: c
- Symbols:
  - `test_picks_lowest` (function, line 11) `static void test_picks_lowest(void **state)`
  - `test_ignores_lock_and_garbage` (function, line 19) `static void test_ignores_lock_and_garbage(void **state)`
  - `test_small_cap_fails_closed` (function, line 27) `static void test_small_cap_fails_closed(void **state)`
  - `test_null_entry` (function, line 35) `static void test_null_entry(void **state)`
  - `main` (function, line 43) `int main(void)`
- Depends on: `include/wl_display.h`

## tests/test_wl_guard.c
- Doc: test_guard_starts_idles_and_stops_promptly: The helper starts on a live display, tolerates an...
- Layer: testing
- Language: c
- Symbols:
  - `ms_since` (function, line 13) `static long ms_since(const struct timespec *a)`
  - `test_guard_starts_idles_and_stops_promptly` (function, line 21) `static void test_guard_starts_idles_and_stops_promptly(void **state)`
  - `test_guard_survives_peer_hangup` (function, line 41) `static void test_guard_survives_peer_hangup(void **state)`
  - `main` (function, line 55) `int main(void)`
  - `_DEFAULT_SOURCE` (macro, line 1) `#define _DEFAULT_SOURCE`
- Depends on: `include/wl_guard.h`

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

