# Subsystem: tests (page 7 of 9)
Previous: [KB_tests_p6.md](KB_tests_p6.md)

## tests/test_pdf_export.c
- Layer: testing
- Language: c
- Symbols:
  - `pagination` (function, line 8) `* deterministic pagination (single/multi page, no row splitting, oversized row,
 * gap preservati...`
  - `test_basename_maps_spaces_and_reserved` (function, line 31) `static void test_basename_maps_spaces_and_reserved(void **state)`
  - `test_basename_rejects_path_separators` (function, line 39) `static void test_basename_rejects_path_separators(void **state)`
  - `test_basename_neutralizes_traversal` (function, line 49) `static void test_basename_neutralizes_traversal(void **state)`
  - `test_basename_dotdot_only_falls_back` (function, line 57) `static void test_basename_dotdot_only_falls_back(void **state)`
  - `test_basename_trims_edges` (function, line 64) `static void test_basename_trims_edges(void **state)`
  - `test_basename_collapses_underscores` (function, line 72) `static void test_basename_collapses_underscores(void **state)`
  - `test_basename_control_bytes_mapped` (function, line 79) `static void test_basename_control_bytes_mapped(void **state)`
  - `test_basename_non_ascii_mapped` (function, line 87) `static void test_basename_non_ascii_mapped(void **state)`
  - `test_basename_empty_and_null_fall_back` (function, line 96) `static void test_basename_empty_and_null_fall_back(void **state)`
  - `test_basename_all_separators_fall_back` (function, line 105) `static void test_basename_all_separators_fall_back(void **state)`
  - `test_basename_length_bound` (function, line 112) `static void test_basename_length_bound(void **state)`
  - `test_basename_null_out_and_zero_size` (function, line 123) `static void test_basename_null_out_and_zero_size(void **state)`
  - `test_basename_overflow_fails_closed` (function, line 130) `static void test_basename_overflow_fails_closed(void **state)`
  - `test_build_path_basic` (function, line 139) `static void test_build_path_basic(void **state)`
  - `test_build_path_trailing_slash` (function, line 146) `static void test_build_path_trailing_slash(void **state)`
  - `test_build_path_hostile_title_contained` (function, line 153) `static void test_build_path_hostile_title_contained(void **state)`
  - `test_build_path_empty_title_fallback` (function, line 162) `static void test_build_path_empty_title_fallback(void **state)`
  - `test_build_path_overflow_fails_closed` (function, line 169) `static void test_build_path_overflow_fails_closed(void **state)`
  - `test_build_path_null_args` (function, line 176) `static void test_build_path_null_args(void **state)`
  - `test_build_path_ext_png` (function, line 186) `static void test_build_path_ext_png(void **state)`
  - `test_build_path_ext_null_ext` (function, line 194) `static void test_build_path_ext_null_ext(void **state)`
  - `test_build_path_ext_hostile_title_contained` (function, line 202) `static void test_build_path_ext_hostile_title_contained(void **state)`
  - `test_build_path_ext_overflow_fails_closed` (function, line 213) `static void test_build_path_ext_overflow_fails_closed(void **state)`
  - `test_paginate_single_page` (function, line 223) `static void test_paginate_single_page(void **state)`
  - `test_paginate_breaks_without_splitting` (function, line 238) `static void test_paginate_breaks_without_splitting(void **state)`
  - `test_paginate_oversized_row_not_split` (function, line 252) `static void test_paginate_oversized_row_not_split(void **state)`
  - `test_paginate_preserves_gaps` (function, line 264) `static void test_paginate_preserves_gaps(void **state)`
  - `test_paginate_invalid_args` (function, line 276) `static void test_paginate_invalid_args(void **state)`
  - `main` (function, line 290) `int main(void)`
- Depends on: `include/pdf_export.h`

## tests/test_perf_trace.c
- Layer: testing
- Language: c
- Symbols:
  - `test_single_record` (function, line 28) `static void test_single_record(void **state)`
  - `test_min_max_median` (function, line 42) `static void test_min_max_median(void **state)`
  - `test_ring_wraparound_fifo` (function, line 55) `static void test_ring_wraparound_fifo(void **state)`
  - `test_stage_out_of_range_is_noop` (function, line 72) `static void test_stage_out_of_range_is_noop(void **state)`
  - `test_elapsed_us_normal` (function, line 89) `static void test_elapsed_us_normal(void **state)`
  - `test_elapsed_us_underflow_guard` (function, line 95) `static void test_elapsed_us_underflow_guard(void **state)`
  - `test_stage_name` (function, line 101) `static void test_stage_name(void **state)`
  - `test_format_deterministic_and_only_nonempty_stages` (function, line 115) `static void test_format_deterministic_and_only_nonempty_stages(void **state)`
  - `test_format_truncates_never_overflows` (function, line 138) `static void test_format_truncates_never_overflows(void **state)`
  - `test_format_null_or_zero_cap` (function, line 152) `static void test_format_null_or_zero_cap(void **state)`
  - `test_null_safe` (function, line 163) `static void test_null_safe(void **state)`
  - `main` (function, line 174) `int main(void)`
- Depends on: `include/perf_trace.h`

## tests/test_pq_seal.c
- Doc: test_requires_both_secrets_and_detects_tamper: static void test_each_seal_is_fresh(void **state)...
- Layer: testing
- Language: c
- Symbols:
  - `test_seal_open_roundtrip` (function, line 12) `static void test_seal_open_roundtrip(void **state)`
  - `test_each_seal_is_fresh` (function, line 31) `static void test_each_seal_is_fresh(void **state)`
  - `test_requires_both_secrets_and_detects_tamper` (function, line 44) `static void test_requires_both_secrets_and_detects_tamper(void **state)`
  - `test_format_errors` (function, line 65) `static void test_format_errors(void **state)`
  - `test_export_import_keeps_decapsulation` (function, line 77) `static void test_export_import_keeps_decapsulation(void **state)`
  - `main` (function, line 95) `int main(void)`
  - `_GNU_SOURCE` (macro, line 1) `#define _GNU_SOURCE`
- Depends on: `include/pq_seal.h`

## tests/test_prefetch.c
- Doc: Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool.
- Layer: testing
- Language: c
- Symbols:
  - `fake_ctx` (struct, line 126)
  - `barrier` (type_alias, line 126) `typedef struct fake_ctx { pthread_barrier_t barrier;`
  - `test_scan_null_args` (function, line 22) `static void test_scan_null_args(void **state)`
  - `test_scan_basic_stylesheet_and_script` (function, line 32) `static void test_scan_basic_stylesheet_and_script(void **state)`
  - `test_scan_ref_cap` (function, line 104) `static void test_scan_ref_cap(void **state)`
  - `fake_fetch` (function, line 135) `static int fake_fetch(void *vctx, const char *method, const char *url,
                      cons...`
  - `test_pool_parallel_fetch_and_take` (function, line 153) `static void test_pool_parallel_fetch_and_take(void **state)`
  - `test_pool_miss_consume_and_failure` (function, line 191) `static void test_pool_miss_consume_and_failure(void **state)`
  - `test_pool_finish_unconsumed_and_empty` (function, line 234) `static void test_pool_finish_unconsumed_and_empty(void **state)`
  - `test_pooled_fetch_adapter` (function, line 255) `static void test_pooled_fetch_adapter(void **state)`
  - `test_scan_imports_static_only` (function, line 298) `static void test_scan_imports_static_only(void **state)`
  - `graph_fetch` (function, line 320) `static int graph_fetch(void *ctx, const char *method, const char *url,
                       con...`
  - `bare_fetch` (function, line 333) `static int bare_fetch(void *ctx, const char *method, const char *url,
                      const...`
  - `test_pool_follows_module_graph` (function, line 346) `static void test_pool_follows_module_graph(void **state)`
  - `test_find_importmap` (function, line 366) `static void test_find_importmap(void **state)`
  - `test_pool_start_page_import_map` (function, line 378) `static void test_pool_start_page_import_map(void **state)`
  - `main` (function, line 395) `int main(void)`
  - `_POSIX_C_SOURCE` (macro, line 5) `#define _POSIX_C_SOURCE`
- Depends on: `include/prefetch.h`

## tests/test_prefs.c
- Layer: testing
- Language: c
- Symbols:
  - `test_init_defaults` (function, line 25) `static void test_init_defaults(void **state)`
  - `test_roundtrip` (function, line 80) `static void test_roundtrip(void **state)`
  - `test_parse_bad_magic` (function, line 140) `static void test_parse_bad_magic(void **state)`
  - `test_parse_too_large` (function, line 156) `static void test_parse_too_large(void **state)`
  - `test_parse_unknown_and_malformed_skipped` (function, line 165) `static void test_parse_unknown_and_malformed_skipped(void **state)`
  - `test_parse_clamps_out_of_range` (function, line 187) `static void test_parse_clamps_out_of_range(void **state)`
  - `test_invalid_urls_rejected` (function, line 209) `static void test_invalid_urls_rejected(void **state)`
  - `test_hostile_title_cleaned` (function, line 237) `static void test_hostile_title_cleaned(void **state)`
  - `test_bookmark_toggle_and_cap` (function, line 267) `static void test_bookmark_toggle_and_cap(void **state)`
  - `test_history_dedup_and_evict` (function, line 295) `static void test_history_dedup_and_evict(void **state)`
  - `test_suggest_priorities` (function, line 320) `static void test_suggest_priorities(void **state)`
  - `test_bookmarks_page_escapes` (function, line 375) `static void test_bookmarks_page_escapes(void **state)`
  - `test_format_null_args` (function, line 412) `static void test_format_null_args(void **state)`
  - `main` (function, line 424) `int main(void)`
  - `_POSIX_C_SOURCE` (macro, line 9) `#define _POSIX_C_SOURCE`
- Depends on: `include/prefs.h`, `include/zoom.h`

## tests/test_pres_hints.c
- Doc: test_pres_hints -- HTML presentational attributes (spec/pres_hints.md).
- Layer: testing
- Language: c
- Symbols:
  - `kv` (struct, line 11)
  - `get` (function, line 13) `static const char *get(void *ctx, const char *name, size_t *len)`
  - `fresh` (function, line 19) `static css_style fresh(void)`
  - `test_dimension` (function, line 28) `static void test_dimension(void **state)`
  - `test_table_width_and_centering` (function, line 49) `static void test_table_width_and_centering(void **state)`
  - `test_css_wins` (function, line 72) `static void test_css_wins(void **state)`
  - `test_cell_hints` (function, line 93) `static void test_cell_hints(void **state)`
  - `test_center_and_block_align` (function, line 106) `static void test_center_and_block_align(void **state)`
  - `test_bgcolor_and_quirks` (function, line 132) `static void test_bgcolor_and_quirks(void **state)`
  - `test_fail_closed` (function, line 162) `static void test_fail_closed(void **state)`
  - `main` (function, line 176) `int main(void)`
- Depends on: `include/pres_hints.h`

## tests/test_profile.c
- Doc: dir: include "prefs.h" include "profile.h"
- Layer: testing
- Language: c
- Symbols:
  - `fixture` (struct, line 28)
  - `dir` (type_alias, line 27) `typedef struct fixture { char dir[64];`
  - `setup` (function, line 30) `static int setup(void **state)`
  - `teardown` (function, line 39) `static int teardown(void **state)`
  - `path_of` (function, line 60) `static void path_of(const fixture *f, const char *name, char *out, size_t cap)`
  - `file_size` (function, line 64) `static size_t file_size(const char *path)`
  - `test_open_creates_keyfile` (function, line 72) `static void test_open_creates_keyfile(void **state)`
  - `test_open_rejects_corrupt_keyfile` (function, line 89) `static void test_open_rejects_corrupt_keyfile(void **state)`
  - `test_open_bad_dir` (function, line 103) `static void test_open_bad_dir(void **state)`
  - `test_first_launch_defaults` (function, line 115) `static void test_first_launch_defaults(void **state)`
  - `test_save_load_roundtrip_two_ctx` (function, line 128) `static void test_save_load_roundtrip_two_ctx(void **state)`
  - `test_nothing_readable_on_disk` (function, line 174) `static void test_nothing_readable_on_disk(void **state)`
  - `test_tampered_blob_auth_fails` (function, line 204) `static void test_tampered_blob_auth_fails(void **state)`
  - `test_foreign_key_auth_fails` (function, line 236) `static void test_foreign_key_auth_fails(void **state)`
  - `test_null_and_not_ready` (function, line 261) `static void test_null_and_not_ready(void **state)`
  - `main` (function, line 278) `int main(void)`
  - `_GNU_SOURCE` (macro, line 9) `#define _GNU_SOURCE`
- Depends on: `include/prefs.h`, `include/profile.h`

## tests/test_render_doc.c
- Doc: first_kind: #include "flex_layout.h" #include "page_view.h" #include "render_doc.h" #include...
- Layer: testing
- Language: c
- Symbols:
  - `caps_images_on` (function, line 28) `static rdp_caps caps_images_on(void)`
  - `first_kind` (function, line 35) `static const rd_block *first_kind(const rd_doc *d, rd_kind k)`
  - `test_build_null_out` (function, line 44) `static void test_build_null_out(void **state)`
  - `test_build_null_view_is_empty` (function, line 51) `static void test_build_null_view_is_empty(void **state)`
  - `test_heading_paragraph_link` (function, line 64) `static void test_heading_paragraph_link(void **state)`
  - `test_emphasis_propagates` (function, line 94) `static void test_emphasis_propagates(void **state)`
  - `test_image_off_emits_notice_and_blocked` (function, line 125) `static void test_image_off_emits_notice_and_blocked(void **state)`
  - `test_no_images_no_notice` (function, line 174) `static void test_no_images_no_notice(void **state)`
  - `test_image_on_allows_normal` (function, line 188) `static void test_image_on_allows_normal(void **state)`
  - `test_image_on_resolves_relative_src` (function, line 206) `static void test_image_on_resolves_relative_src(void **state)`
  - `test_image_on_resolves_doc_relative_src` (function, line 222) `static void test_image_on_resolves_doc_relative_src(void **state)`
  - `test_image_on_blocks_tracker` (function, line 236) `static void test_image_on_blocks_tracker(void **state)`
  - `test_image_on_blocks_non_https` (function, line 249) `static void test_image_on_blocks_non_https(void **state)`
  - `test_image_data_url_allowed_remote_top` (function, line 284) `static void test_image_data_url_allowed_remote_top(void **state)`
  - `test_image_data_url_allowed_no_top` (function, line 302) `static void test_image_data_url_allowed_no_top(void **state)`
  - `test_image_data_url_disabled_by_default` (function, line 315) `static void test_image_data_url_disabled_by_default(void **state)`
  - `test_image_data_url_percent_encoded_allowed` (function, line 331) `static void test_image_data_url_percent_encoded_allowed(void **state)`
  - `test_href_sanitised` (function, line 353) `static void test_href_sanitised(void **state)`
  - `test_kind_name_total` (function, line 370) `static void test_kind_name_total(void **state)`
  - `test_image_label_total` (function, line 380) `static void test_image_label_total(void **state)`
  - `test_free_null_and_double` (function, line 393) `static void test_free_null_and_double(void **state)`
  - `test_author_color_gated_by_css` (function, line 403) `static void test_author_color_gated_by_css(void **state)`
  - `test_text_overflow_word_break_gated_by_css` (function, line 433) `static void test_text_overflow_word_break_gated_by_css(void **state)`
  - `test_text_ext_2026_07_10_batch_gated_by_css` (function, line 468) `static void test_text_ext_2026_07_10_batch_gated_by_css(void **state)`
  - `test_image_rendering_gated_on_image` (function, line 508) `static void test_image_rendering_gated_on_image(void **state)`
  - `test_caret_color_gated_on_input` (function, line 537) `static void test_caret_color_gated_on_input(void **state)`
  - `test_input_passthrough` (function, line 567) `static void test_input_passthrough(void **state)`
  - `test_input_label_total` (function, line 602) `static void test_input_label_total(void **state)`
  - `test_container_carried_by_default` (function, line 627) `static void test_container_carried_by_default(void **state)`
  - `test_cont_item_carried_by_default` (function, line 659) `static void test_cont_item_carried_by_default(void **state)`
  - `test_float_carried_by_default` (function, line 692) `static void test_float_carried_by_default(void **state)`
  - `test_flex_item_carried_by_default` (function, line 728) `static void test_flex_item_carried_by_default(void **state)`
  - `test_flex_wrap_align_row_gap_carried_by_default` (function, line 776) `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)`
  - `test_heading_level_of_link` (function, line 808) `static void test_heading_level_of_link(void **state)`
  - `test_block_tag_total` (function, line 824) `static void test_block_tag_total(void **state)`
  - `test_node_id_carried_by_default` (function, line 860) `static void test_node_id_carried_by_default(void **state)`
  - `main` (function, line 873) `int main(void)`
- Depends on: `include/box_style.h`, `include/css.h`, `include/flex_layout.h`, `include/page_view.h`, `include/render_doc.h`, `include/render_policy.h`

## tests/test_render_policy.c
- Doc: test_image_allow_data_url: A data: URI embeds its bytes inline: no socket opens, so it skips the...
- Layer: testing
- Language: c
- Symbols:
  - `test_caps_safe_is_all_off` (function, line 18) `static void test_caps_safe_is_all_off(void **state)`
  - `test_caps_zero_value_is_safe` (function, line 26) `static void test_caps_zero_value_is_safe(void **state)`
  - `test_tracking_pixel_tiny` (function, line 37) `static void test_tracking_pixel_tiny(void **state)`
  - `test_tracking_pixel_zero_area` (function, line 45) `static void test_tracking_pixel_zero_area(void **state)`
  - `test_tracking_pixel_normal` (function, line 52) `static void test_tracking_pixel_normal(void **state)`
  - `test_tracking_pixel_unknown` (function, line 62) `static void test_tracking_pixel_unknown(void **state)`
  - `test_image_disabled_by_default` (function, line 72) `static void test_image_disabled_by_default(void **state)`
  - `caps_images_on` (function, line 90) `static rdp_caps caps_images_on(void)`
  - `test_image_allow_same_site` (function, line 96) `static void test_image_allow_same_site(void **state)`
  - `test_image_allow_cross_site_when_enabled` (function, line 108) `static void test_image_allow_cross_site_when_enabled(void **state)`
  - `test_image_block_tracker` (function, line 119) `static void test_image_block_tracker(void **state)`
  - `test_image_block_scheme` (function, line 134) `static void test_image_block_scheme(void **state)`
  - `test_image_block_invalid` (function, line 142) `static void test_image_block_invalid(void **state)`
  - `test_image_allow_data_url` (function, line 164) `static void test_image_allow_data_url(void **state)`
  - `test_image_data_url_disabled_by_default` (function, line 183) `static void test_image_data_url_disabled_by_default(void **state)`
  - `test_image_data_url_malformed_is_invalid` (function, line 191) `static void test_image_data_url_malformed_is_invalid(void **state)`
  - `test_image_disabled_precedence` (function, line 209) `static void test_image_disabled_precedence(void **state)`
  - `test_img_reason_total_and_stable` (function, line 219) `static void test_img_reason_total_and_stable(void **state)`
  - `test_images_warning_present` (function, line 234) `static void test_images_warning_present(void **state)`
  - `main` (function, line 243) `int main(void)`
  - `consulted` (function, line 76) `* is not even consulted (a bogus URL still yields BLOCK_DISABLED). */ assert_int_equal( rdp_image_decision(off...`
- Depends on: `include/render_policy.h`

## tests/test_renderer.c
- Doc: test_render_binary_does_not_crash_parent: (void)state; rd_result r...
- Layer: testing
- Language: c
- Symbols:
  - `test_render_basic` (function, line 27) `static void test_render_basic(void **state)`
  - `test_render_strips_script` (function, line 39) `static void test_render_strips_script(void **state)`
  - `test_render_null_args` (function, line 48) `static void test_render_null_args(void **state)`
  - `test_render_too_large` (function, line 55) `static void test_render_too_large(void **state)`
  - `test_render_binary_does_not_crash_parent` (function, line 63) `static void test_render_binary_does_not_crash_parent(void **state)`
  - `test_render_multiple_independent` (function, line 74) `static void test_render_multiple_independent(void **state)`
  - `test_result_free_null_and_double` (function, line 84) `static void test_result_free_null_and_double(void **state)`
  - `main` (function, line 93) `int main(void)`
- Depends on: `include/renderer.h`

## tests/test_request_policy.c
- Doc: test_site_of_psl: } static void test_site_of_multi_suffix(void **state) { (void)state; char...
- Layer: testing
- Language: c
- Symbols:
  - `test_host_of_basic` (function, line 19) `static void test_host_of_basic(void **state)`
  - `test_host_of_invalid` (function, line 30) `static void test_host_of_invalid(void **state)`
  - `test_host_of_overflow` (function, line 38) `static void test_host_of_overflow(void **state)`
  - `test_site_of` (function, line 46) `static void test_site_of(void **state)`
  - `test_site_of_multi_suffix` (function, line 59) `static void test_site_of_multi_suffix(void **state)`
  - `test_site_of_psl` (function, line 71) `static void test_site_of_psl(void **state)`
  - `test_same_site` (function, line 92) `static void test_same_site(void **state)`
  - `test_evaluate_allow_same_site` (function, line 106) `static void test_evaluate_allow_same_site(void **state)`
  - `test_evaluate_block_third_party` (function, line 113) `static void test_evaluate_block_third_party(void **state)`
  - `test_evaluate_block_scheme` (function, line 121) `static void test_evaluate_block_scheme(void **state)`
  - `test_evaluate_block_invalid` (function, line 129) `static void test_evaluate_block_invalid(void **state)`
  - `test_hdr_keeps_application_headers` (function, line 142) `static void test_hdr_keeps_application_headers(void **state)`
  - `test_hdr_drops_forbidden_and_identity` (function, line 157) `static void test_hdr_drops_forbidden_and_identity(void **state)`
  - `test_hdr_rejects_malformed` (function, line 171) `static void test_hdr_rejects_malformed(void **state)`
  - `test_hdr_first_duplicate_wins` (function, line 184) `static void test_hdr_first_duplicate_wins(void **state)`
  - `test_hdr_caps_and_args` (function, line 191) `static void test_hdr_caps_and_args(void **state)`
  - `main` (function, line 212) `int main(void)`
- Depends on: `include/request_policy.h`

## tests/test_secure_fetch.c
- Doc: test_default_groups_offer_p384: Some servers (justpaste.it, 2026 Let's Encrypt P-384 chain)...
- Layer: testing
- Language: c
- Symbols:
  - `test_default_groups_offer_p384` (function, line 37) `static void test_default_groups_offer_p384(void **state)`
  - `test_config_blend_fields_default_null` (function, line 43) `static void test_config_blend_fields_default_null(void **state)`
  - `test_user_agent_default_when_unset` (function, line 55) `static void test_user_agent_default_when_unset(void **state)`
  - `test_user_agent_uses_override` (function, line 61) `static void test_user_agent_uses_override(void **state)`
  - `test_url_rejects_null` (function, line 82) `static void test_url_rejects_null(void **state)`
  - `test_url_rejects_plain_http` (function, line 87) `static void test_url_rejects_plain_http(void **state)`
  - `test_url_rejects_dangerous_schemes` (function, line 92) `static void test_url_rejects_dangerous_schemes(void **state)`
  - `test_url_accepts_https` (function, line 102) `static void test_url_accepts_https(void **state)`
  - `test_tls_rejects_12` (function, line 110) `static void test_tls_rejects_12(void **state)`
  - `test_tls_rejects_older_and_garbage` (function, line 115) `static void test_tls_rejects_older_and_garbage(void **state)`
  - `test_tls_accepts_13` (function, line 124) `static void test_tls_accepts_13(void **state)`
  - `test_group_rejects_classical` (function, line 131) `static void test_group_rejects_classical(void **state)`
  - `test_group_rejects_pure_pq` (function, line 138) `static void test_group_rejects_pure_pq(void **state)`
  - `test_group_accepts_hybrid` (function, line 145) `static void test_group_accepts_hybrid(void **state)`
  - `test_chain_strict_rejects_classical` (function, line 154) `static void test_chain_strict_rejects_classical(void **state)`
  - `test_chain_strict_accepts_pq` (function, line 163) `static void test_chain_strict_accepts_pq(void **state)`
  - `test_chain_hybrid_allows_classical` (function, line 171) `static void test_chain_hybrid_allows_classical(void **state)`
  - `test_chain_rejects_sha1_in_any_policy` (function, line 179) `static void test_chain_rejects_sha1_in_any_policy(void **state)`
  - `test_chain_permissive_allows_weak_certs` (function, line 188) `static void test_chain_permissive_allows_weak_certs(void **state)`
  - `test_chain_rejects_weak_rsa` (function, line 201) `static void test_chain_rejects_weak_rsa(void **state)`
  - `test_chain_rejects_null` (function, line 209) `static void test_chain_rejects_null(void **state)`
  - `test_enforce_all_good_hybrid` (function, line 223) `static void test_enforce_all_good_hybrid(void **state)`
  - `test_enforce_checks_version_first` (function, line 229) `static void test_enforce_checks_version_first(void **state)`
  - `test_enforce_checks_group_after_version` (function, line 238) `static void test_enforce_checks_group_after_version(void **state)`
  - `test_enforce_fails_closed_on_null_chain` (function, line 246) `static void test_enforce_fails_closed_on_null_chain(void **state)`
  - `test_enforce_strict_requires_pq_chain` (function, line 253) `static void test_enforce_strict_requires_pq_chain(void **state)`
  - `test_enforce_allow_classical_ke` (function, line 266) `static void test_enforce_allow_classical_ke(void **state)`
  - `test_enforce_allowlisted_insecure` (function, line 285) `static void test_enforce_allowlisted_insecure(void **state)`
  - `test_fallback_ladder_is_shared_and_ordered` (function, line 307) `static void test_fallback_ladder_is_shared_and_ordered(void **state)`
  - `bk_save` (function, line 327) `static void bk_save(void *c, const char *from, const char *to, time_t now)`
  - `bk_load` (function, line 333) `static int bk_load(void *c, const char *from, time_t now, char *out, size_t cap)`
  - `test_rcache_backing_persists_and_serves_after_ram_loss` (function, line 340) `static void test_rcache_backing_persists_and_serves_after_ram_loss(void **state)`
  - `test_rcache_remembers_permanent_redirects` (function, line 358) `static void test_rcache_remembers_permanent_redirects(void **state)`
  - `test_redirect_code_recognizes_3xx` (function, line 377) `static void test_redirect_code_recognizes_3xx(void **state)`
  - `test_redirect_code_rejects_others` (function, line 386) `static void test_redirect_code_rejects_others(void **state)`
  - `test_header_value_reads_named_header` (function, line 397) `static void test_header_value_reads_named_header(void **state)`
  - `test_header_value_rejects_other_empty_and_oversize` (function, line 408) `static void test_header_value_rejects_other_empty_and_oversize(void **state)`
  - `test_location_parses_value` (function, line 421) `static void test_location_parses_value(void **state)`
  - `test_location_is_case_insensitive_and_trims` (function, line 429) `static void test_location_is_case_insensitive_and_trims(void **state)`
  - `test_location_rejects_non_location_and_empty` (function, line 439) `static void test_location_rejects_non_location_and_empty(void **state)`
  - `test_location_rejects_overflow` (function, line 451) `static void test_location_rejects_overflow(void **state)`
  - `test_resolve_absolute_https` (function, line 460) `static void test_resolve_absolute_https(void **state)`
  - `test_resolve_refuses_http_downgrade` (function, line 468) `static void test_resolve_refuses_http_downgrade(void **state)`
  - `test_resolve_refuses_dangerous_schemes` (function, line 475) `static void test_resolve_refuses_dangerous_schemes(void **state)`
  - `test_resolve_scheme_relative` (function, line 486) `static void test_resolve_scheme_relative(void **state)`
  - `test_resolve_absolute_path` (function, line 494) `static void test_resolve_absolute_path(void **state)`
  - `test_resolve_relative_path` (function, line 506) `static void test_resolve_relative_path(void **state)`
  - `test_resolve_null_args` (function, line 518) `static void test_resolve_null_args(void **state)`
  - `test_response_free_on_zeroed` (function, line 529) `static void test_response_free_on_zeroed(void **state)`
  - `test_response_free_releases_location` (function, line 538) `static void test_response_free_releases_location(void **state)`
  - `test_get_follow_null_args` (function, line 552) `static void test_get_follow_null_args(void **state)`
  - `test_get_null_args` (function, line 561) `static void test_get_null_args(void **state)`
  - `test_post_null_args` (function, line 570) `static void test_post_null_args(void **state)`
  - `test_cookie_line_matches_pure` (function, line 596) `static void test_cookie_line_matches_pure(void **state)`
  - `test_cookie_jar_put_and_header` (function, line 632) `static void test_cookie_jar_put_and_header(void **state)`
  - `test_ws_url_check` (function, line 650) `static void test_ws_url_check(void **state)`
  - `test_ws_open_rejects_before_any_io` (function, line 662) `static void test_ws_open_rejects_before_any_io(void **state)`
  - `main` (function, line 736) `int main(void)`
- Depends on: `include/secure_fetch.h`

## tests/test_sha2.c
- Doc: test_sha2 -- CMocka suite for the pure SHA-1/256/384/512 (FIPS 180-4 vectors).
- Layer: testing
- Language: c
- Symbols:
  - `hex` (function, line 14) `static void hex(const uint8_t *d, size_t n, char *out)`
  - `check` (function, line 18) `static void check(sha_alg a, const char *msg, size_t rep, const char *want)`
  - `test_abc_vectors` (function, line 31) `static void test_abc_vectors(void **state)`
  - `test_empty_and_long` (function, line 39) `static void test_empty_and_long(void **state)`
  - `test_padding_boundaries` (function, line 52) `static void test_padding_boundaries(void **state)`
  - `test_names_and_errors` (function, line 60) `static void test_names_and_errors(void **state)`
  - `main` (function, line 74) `int main(void)`
- Depends on: `include/sha2.h`

## tests/test_sheet_cache.c
- Doc: Suite for sheet_cache (spec/sheet_cache.md).
- Layer: testing
- Language: c
- Symbols:
  - `matcher_log` (struct, line 36)
  - `calls` (type_alias, line 35) `typedef struct matcher_log { int calls;`
  - `p_color` (function, line 21) `static int p_color(const shc_sheet *s)`
  - `key_of` (function, line 25) `static shc_key key_of(const char *text, const css_media *m)`
  - `stats_of` (function, line 30) `static shc_stats stats_of(const shc_cache *c)`
  - `log_match` (function, line 38) `static int log_match(void *ctx, const struct css_sel *sel)`
  - `test_same_key_is_a_hit_and_returns_the_same_sheet` (function, line 45) `static void test_same_key_is_a_hit_and_returns_the_same_sheet(void **state)`
  - `test_one_byte_of_text_changes_the_result` (function, line 66) `static void test_one_byte_of_text_changes_the_result(void **state)`
  - `test_media_inputs_are_part_of_the_key` (function, line 81) `static void test_media_inputs_are_part_of_the_key(void **state)`
  - `test_root_scope_is_part_of_the_key` (function, line 107) `static void test_root_scope_is_part_of_the_key(void **state)`
  - `test_a_hit_replays_the_matcher_and_needs_the_same_answers` (function, line 125) `static void test_a_hit_replays_the_matcher_and_needs_the_same_answers(void **state)`
  - `test_structural_root_selector_is_replayed_too` (function, line 156) `static void test_structural_root_selector_is_replayed_too(void **state)`
  - `test_matcher_presence_is_part_of_the_key` (function, line 176) `static void test_matcher_presence_is_part_of_the_key(void **state)`
  - `test_too_many_matcher_questions_are_never_reused` (function, line 192) `static void test_too_many_matcher_questions_are_never_reused(void **state)`
  - `test_a_bypassed_parse_does_not_evict_the_retained_entry` (function, line 223) `static void test_a_bypassed_parse_does_not_evict_the_retained_entry(void **state)`
  - `test_oversized_text_is_parsed_but_not_retained` (function, line 238) `static void test_oversized_text_is_parsed_but_not_retained(void **state)`
  - `test_a_reference_outlives_replacement_and_the_cache` (function, line 253) `static void test_a_reference_outlives_replacement_and_the_cache(void **state)`
  - `test_no_cache_parses_without_retaining` (function, line 267) `static void test_no_cache_parses_without_retaining(void **state)`
  - `test_fails_closed_on_bad_arguments` (function, line 279) `static void test_fails_closed_on_bad_arguments(void **state)`
  - `main` (function, line 303) `int main(void)`
- Depends on: `include/freedom_config.h`, `include/sheet_cache.h`

## tests/test_shm_slots.c
- Layer: testing
- Language: c
- Symbols:
  - `test_alternates_and_never_paints_a_held_slot` (function, line 8) `static void test_alternates_and_never_paints_a_held_slot(void **state)`
  - `test_release_of_unknown_or_idle_slot_is_ignored` (function, line 23) `static void test_release_of_unknown_or_idle_slot_is_ignored(void **state)`
  - `test_repaint_before_commit_reuses_the_same_free_slot` (function, line 34) `static void test_repaint_before_commit_reuses_the_same_free_slot(void **state)`
  - `main` (function, line 42) `int main(void)`
- Depends on: `include/shm_slots.h`

## tests/test_subreq_batch.c
- Doc: subreq_batch (spec/subreq_async.md): parallelism, issue order, refusals, reuse.
- Layer: testing
- Language: c
- Symbols:
  - `slow_run` (function, line 18) `static int slow_run(void *ctx, const sqb_req *rq, sqb_res *out)`
  - `mk` (function, line 30) `static sqb_req mk(const char *u)`
  - `test_results_in_issue_order_and_overlap` (function, line 32) `static void test_results_in_issue_order_and_overlap(void **st)`
  - `test_thread_limit_is_respected` (function, line 50) `static void test_thread_limit_is_respected(void **st)`
  - `test_refused_and_failed_keep_their_slot` (function, line 60) `static void test_refused_and_failed_keep_their_slot(void **st)`
  - `test_full_batch_refuses_and_reset_reuses` (function, line 75) `static void test_full_batch_refuses_and_reset_reuses(void **st)`
  - `test_null_args_fail_closed` (function, line 89) `static void test_null_args_fail_closed(void **st)`
  - `main` (function, line 99) `int main(void)`
  - `_GNU_SOURCE` (macro, line 2) `#define _GNU_SOURCE`
- Depends on: `include/subreq_batch.h`

## tests/test_svg_raster.c
- Doc: tests/test_svg_raster.c -- CMocka suite for SVG-as-image rasterization (sr_). spec/svg_raster.md...
- Layer: testing
- Language: c
- Symbols:
  - `raster` (function, line 14) `static img_status raster(const char *s, img_pixels *px)`
  - `pixel` (function, line 18) `static uint32_t pixel(const img_pixels *px, uint32_t x, uint32_t y)`
  - `test_sniff` (function, line 24) `static void test_sniff(void **state)`
  - `test_rect_fills_red` (function, line 42) `static void test_rect_fills_red(void **state)`
  - `test_viewbox_sets_size_and_transparent_bg` (function, line 56) `static void test_viewbox_sets_size_and_transparent_bg(void **state)`
  - `test_large_svg_is_not_oversampled` (function, line 69) `static void test_large_svg_is_not_oversampled(void **state)`
  - `test_huge_scales_down` (function, line 79) `static void test_huge_scales_down(void **state)`
  - `test_garbage_fails_closed` (function, line 89) `static void test_garbage_fails_closed(void **state)`
  - `test_text_is_skipped_not_fatal` (function, line 101) `static void test_text_is_skipped_not_fatal(void **state)`
  - `main` (function, line 111) `int main(void)`
- Depends on: `include/svg_raster.h`

## tests/test_svg_render.c
- Doc: tests/test_svg_render.c — CMocka suite for the pure inline-SVG parser (sv_).
- Layer: testing
- Language: c
- Symbols:
  - `parse` (function, line 26) `static sv_status parse(sv_image *im, const char *s)`
  - `test_null_args` (function, line 30) `static void test_null_args(void **state)`
  - `test_empty_and_garbage_do_not_parse` (function, line 38) `static void test_empty_and_garbage_do_not_parse(void **state)`
  - `test_dimensions_and_viewbox` (function, line 50) `static void test_dimensions_and_viewbox(void **state)`
  - `test_basic_shapes` (function, line 71) `static void test_basic_shapes(void **state)`
  - `test_paint_attributes` (function, line 96) `static void test_paint_attributes(void **state)`
  - `test_group_inheritance_and_transform` (function, line 118) `static void test_group_inheritance_and_transform(void **state)`
  - `test_polygon_points` (function, line 140) `static void test_polygon_points(void **state)`
  - `test_path_commands` (function, line 159) `static void test_path_commands(void **state)`
  - `test_path_arc_reaches_endpoint` (function, line 192) `static void test_path_arc_reaches_endpoint(void **state)`
  - `test_path_arc_compact_flags` (function, line 208) `static void test_path_arc_compact_flags(void **state)`
  - `test_url_bearing_elements_are_dropped` (function, line 224) `static void test_url_bearing_elements_are_dropped(void **state)`
  - `test_bounds_are_enforced` (function, line 248) `static void test_bounds_are_enforced(void **state)`
  - `test_malformed_values_degrade` (function, line 285) `static void test_malformed_values_degrade(void **state)`
  - `test_text_element` (function, line 304) `static void test_text_element(void **state)`
  - `test_fit_uniform_and_centered` (function, line 320) `static void test_fit_uniform_and_centered(void **state)`
  - `main` (function, line 344) `int main(void)`
- Depends on: `include/svg_render.h`


Next: [KB_tests_p8.md](KB_tests_p8.md)
