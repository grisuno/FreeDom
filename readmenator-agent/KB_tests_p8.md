# Subsystem: tests (page 8 of 8)
Previous: [KB_tests_p7.md](KB_tests_p7.md)

## tests/test_text_case.c
- Layer: testing
- Language: c
- Symbols:
  - `test_upper_lower_ascii_latin` (function, line 10) `static void test_upper_lower_ascii_latin(void **state)`
  - `test_transform_keeps_length` (function, line 33) `static void test_transform_keeps_length(void **state)`
  - `test_smallcaps_runs` (function, line 55) `static void test_smallcaps_runs(void **state)`
  - `main` (function, line 73) `int main(void)`
- Depends on: `include/css.h`, `include/text_case.h`

## tests/test_text_shape.c
- Doc: inked_pixels: Given a Private Use Area code point that no installed face covers (an icon font...
- Layer: testing
- Language: c
- Symbols:
  - `test_null_and_bad_inputs` (function, line 30) `static void test_null_and_bad_inputs(void **state)`
  - `test_empty_slice_is_ok` (function, line 60) `static void test_empty_slice_is_ok(void **state)`
  - `test_shape_ascii` (function, line 73) `static void test_shape_ascii(void **state)`
  - `test_determinism` (function, line 95) `static void test_determinism(void **state)`
  - `test_measure_matches_shape` (function, line 111) `static void test_measure_matches_shape(void **state)`
  - `test_overflow_cap` (function, line 123) `static void test_overflow_cap(void **state)`
  - `test_draw_paints` (function, line 133) `static void test_draw_paints(void **state)`
  - `inked_pixels` (function, line 149) `static int inked_pixels(cairo_surface_t *s)`
  - `test_uncovered_pua_draws_nothing` (function, line 161) `static void test_uncovered_pua_draws_nothing(void **state)`
  - `test_webfont_rejects_bad_input` (function, line 179) `static void test_webfont_rejects_bad_input(void **state)`
  - `read_host_font` (function, line 201) `static unsigned char *read_host_font(const char *path, size_t *out_n)`
  - `test_webfont_register_find_clear` (function, line 216) `static void test_webfont_register_find_clear(void **state)`
  - `test_generic_keywords` (function, line 264) `static void test_generic_keywords(void **state)`
  - `table_resolve` (function, line 276) `static int table_resolve(const char *name, char *out, size_t cap, void *ctx)`
  - `test_pick_from_list_order_and_generic_stop` (function, line 286) `static void test_pick_from_list_order_and_generic_stop(void **state)`
  - `set_installed` (function, line 306) `static int set_installed(const char *name, void *ctx)`
  - `test_pick_family_strong_vs_weak` (function, line 313) `static void test_pick_family_strong_vs_weak(void **state)`
  - `test_local_handle_real_fontconfig` (function, line 337) `static void test_local_handle_real_fontconfig(void **state)`
  - `teardown` (function, line 358) `static int teardown(void **state)`
  - `fake_cover` (function, line 383) `static int fake_cover(unsigned cp, void *ctx)`
  - `test_segment_runs` (function, line 390) `static void test_segment_runs(void **state)`
  - `test_measure_uses_fallback_face` (function, line 415) `static void test_measure_uses_fallback_face(void **state)`
  - `main` (function, line 426) `int main(void)`
- Depends on: `include/css.h`, `include/text_shape.h`, `include/webfont.h`

## tests/test_textfield.c
- Layer: testing
- Language: c
- Symbols:
  - `test_init_and_accessors` (function, line 20) `static void test_init_and_accessors(void **state)`
  - `test_null_safe` (function, line 29) `static void test_null_safe(void **state)`
  - `test_set` (function, line 46) `static void test_set(void **state)`
  - `test_insert_sequence` (function, line 59) `static void test_insert_sequence(void **state)`
  - `test_backspace_delete` (function, line 76) `static void test_backspace_delete(void **state)`
  - `test_move_saturates` (function, line 100) `static void test_move_saturates(void **state)`
  - `test_full_fails_closed` (function, line 113) `static void test_full_fails_closed(void **state)`
  - `main` (function, line 140) `int main(void)`
- Depends on: `include/textfield.h`

## tests/test_tls_impersonate.c
- Layer: testing
- Language: c
- Symbols:
  - `test_gate_requires_all_three_signals` (function, line 22) `static void test_gate_requires_all_three_signals(void **state)`
  - `test_encode_decode_req_roundtrip` (function, line 39) `static void test_encode_decode_req_roundtrip(void **state)`
  - `test_encode_decode_req_empty_body` (function, line 65) `static void test_encode_decode_req_empty_body(void **state)`
  - `test_encode_decode_resp_roundtrip` (function, line 89) `static void test_encode_decode_resp_roundtrip(void **state)`
  - `test_resp_no_chain_ok` (function, line 121) `static void test_resp_no_chain_ok(void **state)`
  - `test_decode_rejects_truncated` (function, line 144) `static void test_decode_rejects_truncated(void **state)`
  - `test_decode_rejects_bad_magic` (function, line 163) `static void test_decode_rejects_bad_magic(void **state)`
  - `test_decode_rejects_overlong_field` (function, line 177) `static void test_decode_rejects_overlong_field(void **state)`
  - `test_encode_fails_when_no_room` (function, line 192) `static void test_encode_fails_when_no_room(void **state)`
  - `test_encode_rejects_oversize_url` (function, line 203) `static void test_encode_rejects_oversize_url(void **state)`
  - `main` (function, line 218) `int main(void)`
- Depends on: `include/tls_impersonate.h`

## tests/test_ui.c
- Doc: assert_line: Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h>...
- Layer: testing
- Language: c
- Symbols:
  - `assert_line` (function, line 21) `static void assert_line(const char *text, const ui_layout *lay, size_t n,
                       ...`
  - `test_wrap_null_args` (function, line 29) `static void test_wrap_null_args(void **state)`
  - `test_wrap_empty` (function, line 36) `static void test_wrap_empty(void **state)`
  - `test_wrap_short_single_line` (function, line 44) `static void test_wrap_short_single_line(void **state)`
  - `test_wrap_breaks_at_space` (function, line 54) `static void test_wrap_breaks_at_space(void **state)`
  - `test_wrap_hard_breaks_long_word` (function, line 65) `static void test_wrap_hard_breaks_long_word(void **state)`
  - `test_wrap_does_not_split_utf8` (function, line 77) `static void test_wrap_does_not_split_utf8(void **state)`
  - `test_wrap_respects_newline` (function, line 91) `static void test_wrap_respects_newline(void **state)`
  - `test_wrap_zero_cols_is_sanitised` (function, line 102) `static void test_wrap_zero_cols_is_sanitised(void **state)`
  - `test_clamp_scroll` (function, line 114) `static void test_clamp_scroll(void **state)`
  - `test_layout_free_null_and_double` (function, line 122) `static void test_layout_free_null_and_double(void **state)`
  - `test_lazy_near_viewport` (function, line 133) `static void test_lazy_near_viewport(void **state)`
  - `main` (function, line 146) `int main(void)`
- Depends on: `include/lazy_load.h`, `include/ui.h`

## tests/test_url.c
- Doc: test_validate_long_bundle_url: Modern bundle URLs exceed 2048 bytes (google.com's xjs script URL...
- Layer: testing
- Language: c
- Symbols:
  - `test_is_https` (function, line 23) `static void test_is_https(void **state)`
  - `test_validate_https` (function, line 36) `static void test_validate_https(void **state)`
  - `test_validate_long_bundle_url` (function, line 49) `static void test_validate_long_bundle_url(void **state)`
  - `test_has_scheme` (function, line 69) `static void test_has_scheme(void **state)`
  - `test_authority_len` (function, line 86) `static void test_authority_len(void **state)`
  - `test_remove_dot_segments` (function, line 98) `static void test_remove_dot_segments(void **state)`
  - `test_remove_dot_segments_nulls` (function, line 127) `static void test_remove_dot_segments_nulls(void **state)`
  - `test_resolve_absolute` (function, line 138) `static void test_resolve_absolute(void **state)`
  - `test_resolve_rejects_downgrade_and_schemes` (function, line 146) `static void test_resolve_rejects_downgrade_and_schemes(void **state)`
  - `test_resolve_scheme_relative` (function, line 161) `static void test_resolve_scheme_relative(void **state)`
  - `test_resolve_absolute_path` (function, line 169) `static void test_resolve_absolute_path(void **state)`
  - `test_resolve_relative_path` (function, line 181) `static void test_resolve_relative_path(void **state)`
  - `test_resolve_dot_segments` (function, line 193) `static void test_resolve_dot_segments(void **state)`
  - `test_resolve_fail_closed_on_bad_base` (function, line 210) `static void test_resolve_fail_closed_on_bad_base(void **state)`
  - `test_resolve_null_and_overflow` (function, line 222) `static void test_resolve_null_and_overflow(void **state)`
  - `test_omnibox_navigate_https` (function, line 238) `static void test_omnibox_navigate_https(void **state)`
  - `test_omnibox_bare_host_gets_https` (function, line 251) `static void test_omnibox_bare_host_gets_https(void **state)`
  - `test_omnibox_http_upgraded_to_https` (function, line 268) `static void test_omnibox_http_upgraded_to_https(void **state)`
  - `test_omnibox_search_for_queries` (function, line 278) `static void test_omnibox_search_for_queries(void **state)`
  - `test_omnibox_foreign_scheme_is_searched_not_executed` (function, line 298) `static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state)`
  - `test_omnibox_nulls_and_empty` (function, line 311) `static void test_omnibox_nulls_and_empty(void **state)`
  - `test_search_rewrite_ddg_spa` (function, line 327) `static void test_search_rewrite_ddg_spa(void **state)`
  - `test_search_rewrite_leaves_others_alone` (function, line 344) `static void test_search_rewrite_leaves_others_alone(void **state)`
  - `test_search_rewrite_nulls` (function, line 364) `static void test_search_rewrite_nulls(void **state)`
  - `test_is_file_and_path` (function, line 379) `static void test_is_file_and_path(void **state)`
  - `test_resolve_file_relative` (function, line 391) `static void test_resolve_file_relative(void **state)`
  - `test_resolve_file_confinement_fail_closed` (function, line 411) `static void test_resolve_file_confinement_fail_closed(void **state)`
  - `test_resolve_file_nulls` (function, line 437) `static void test_resolve_file_nulls(void **state)`
  - `assert_span` (function, line 449) `static void assert_span(const char *p, size_t len, const char *expect)`
  - `test_split_full_url` (function, line 454) `static void test_split_full_url(void **state)`
  - `test_split_no_port_no_path` (function, line 473) `static void test_split_no_port_no_path(void **state)`
  - `test_split_query_without_fragment` (function, line 486) `static void test_split_query_without_fragment(void **state)`
  - `test_split_fragment_without_query` (function, line 495) `static void test_split_fragment_without_query(void **state)`
  - `test_split_ipv6_literal_with_port` (function, line 504) `static void test_split_ipv6_literal_with_port(void **state)`
  - `test_extract_userinfo_basic` (function, line 516) `static void test_extract_userinfo_basic(void **state)`
  - `test_extract_userinfo_user_only` (function, line 529) `static void test_extract_userinfo_user_only(void **state)`
  - `test_extract_userinfo_no_userinfo` (function, line 542) `static void test_extract_userinfo_no_userinfo(void **state)`
  - `test_extract_userinfo_non_https_passthrough` (function, line 554) `static void test_extract_userinfo_non_https_passthrough(void **state)`
  - `test_extract_userinfo_https_subresource_no_auth` (function, line 566) `static void test_extract_userinfo_https_subresource_no_auth(void **state)`
  - `test_extract_userinfo_nulls` (function, line 579) `static void test_extract_userinfo_nulls(void **state)`
  - `test_extract_userinfo_at_authority_start` (function, line 589) `static void test_extract_userinfo_at_authority_start(void **state)`
  - `test_extract_userinfo_no_at_sign` (function, line 602) `static void test_extract_userinfo_no_at_sign(void **state)`
  - `test_extract_userinfo_empty_password` (function, line 615) `static void test_extract_userinfo_empty_password(void **state)`
  - `test_split_fail_closed_non_https` (function, line 628) `static void test_split_fail_closed_non_https(void **state)`
  - `test_history_target_same_origin` (function, line 641) `static void test_history_target_same_origin(void **state)`
  - `test_history_target_cross_origin_rejected` (function, line 662) `static void test_history_target_cross_origin_rejected(void **state)`
  - `test_history_target_file_query_fragment_only` (function, line 677) `static void test_history_target_file_query_fragment_only(void **state)`
  - `test_history_target_bad_args` (function, line 690) `static void test_history_target_bad_args(void **state)`
  - `main` (function, line 701) `int main(void)`
- Depends on: `include/url.h`

## tests/test_web_storage.c
- Layer: testing
- Language: c
- Symbols:
  - `build` (function, line 24) `static size_t build(char *b, const char *const *kv, uint32_t n)`
  - `test_unknown_origin_encodes_empty` (function, line 34) `static void test_unknown_origin_encodes_empty(void **state)`
  - `test_replace_then_encode_roundtrip` (function, line 49) `static void test_replace_then_encode_roundtrip(void **state)`
  - `test_hostile_snapshots_rejected_and_db_unchanged` (function, line 73) `static void test_hostile_snapshots_rejected_and_db_unchanged(void **state)`
  - `test_quota_enforced` (function, line 112) `static void test_quota_enforced(void **state)`
  - `test_origin_table_is_bounded_lru` (function, line 129) `static void test_origin_table_is_bounded_lru(void **state)`
  - `count_pair` (function, line 147) `static void count_pair(void *ctx, const char *k, size_t kl, const char *v, size_t vl)`
  - `test_pack_foreach_roundtrip` (function, line 154) `static void test_pack_foreach_roundtrip(void **state)`
  - `main` (function, line 182) `int main(void)`
- Depends on: `include/web_storage.h`

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

