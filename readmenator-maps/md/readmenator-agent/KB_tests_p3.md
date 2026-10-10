# Subsystem: tests (page 3 of 7)
Previous: [KB_tests_p2.md](KB_tests_p2.md)

## tests/test_css_length.c
- Doc: test_unitless: static double px_of(const char *value, const cl_ctx *ctx) { double px = -12345.0...
- Layer: testing
- Language: c
- Symbols:
  - `px_of` (function, line 21) `static double px_of(const char *value, const cl_ctx *ctx)`
  - `expect_err` (function, line 27) `static void expect_err(const char *value, const cl_ctx *ctx, cl_status want)`
  - `test_unitless` (function, line 34) `static void test_unitless(void **state)`
  - `test_absolute_units` (function, line 45) `static void test_absolute_units(void **state)`
  - `test_font_relative_em_rem` (function, line 61) `static void test_font_relative_em_rem(void **state)`
  - `test_font_metric_fallbacks` (function, line 75) `static void test_font_metric_fallbacks(void **state)`
  - `test_line_height_units` (function, line 92) `static void test_line_height_units(void **state)`
  - `test_viewport_units` (function, line 104) `static void test_viewport_units(void **state)`
  - `test_case_insensitive` (function, line 129) `static void test_case_insensitive(void **state)`
  - `test_number_grammar` (function, line 140) `static void test_number_grammar(void **state)`
  - `test_not_a_length` (function, line 152) `static void test_not_a_length(void **state)`
  - `test_syntax` (function, line 164) `static void test_syntax(void **state)`
  - `test_null_args` (function, line 180) `static void test_null_args(void **state)`
  - `test_range` (function, line 192) `static void test_range(void **state)`
  - `test_unit_scale` (function, line 207) `static void test_unit_scale(void **state)`
  - `test_font_relative_classifier` (function, line 226) `static void test_font_relative_classifier(void **state)`
  - `test_is_length_unit` (function, line 244) `static void test_is_length_unit(void **state)`
  - `test_initial_ctx` (function, line 258) `static void test_initial_ctx(void **state)`
  - `test_cl_number` (function, line 273) `static void test_cl_number(void **state)`
  - `test_lp_parse` (function, line 304) `static void test_lp_parse(void **state)`
  - `test_lp_used` (function, line 356) `static void test_lp_used(void **state)`
  - `test_em_derivative` (function, line 379) `static void test_em_derivative(void **state)`
  - `test_em_refit` (function, line 425) `static void test_em_refit(void **state)`
  - `main` (function, line 450) `int main(void)`
  - `EPS` (macro, line 19) `#define EPS`
- Depends on: `include/css.h`, `include/css_length.h`

## tests/test_css_mq.c
- Layer: testing
- Language: c
- Symbols:
  - `m` (function, line 13) `static int m(const char *q)`
  - `test_range_syntax` (function, line 15) `static void test_range_syntax(void **state)`
  - `test_plain_and_types` (function, line 30) `static void test_plain_and_types(void **state)`
  - `test_not_or` (function, line 44) `static void test_not_or(void **state)`
  - `test_desktop_identity` (function, line 56) `static void test_desktop_identity(void **state)`
  - `test_fail_closed` (function, line 78) `static void test_fail_closed(void **state)`
  - `main` (function, line 91) `int main(void)`
- Depends on: `include/css_mq.h`

## tests/test_css_text.c
- Layer: testing
- Language: c
- Symbols:
  - `test_fontfamily_bucket` (function, line 10) `static void test_fontfamily_bucket(void **state)`
  - `test_opacity_shapes` (function, line 18) `static void test_opacity_shapes(void **state)`
  - `test_whitespace_direction` (function, line 26) `static void test_whitespace_direction(void **state)`
  - `test_shadow_needs_both_offsets` (function, line 34) `static void test_shadow_needs_both_offsets(void **state)`
  - `test_aspect_ratio` (function, line 44) `static void test_aspect_ratio(void **state)`
  - `main` (function, line 56) `int main(void)`
- Depends on: `include/css.h`, `include/css_decl.h`, `include/css_text.h`

## tests/test_css_values.c
- Layer: testing
- Language: c
- Symbols:
  - `test_parse_named` (function, line 9) `static void test_parse_named(void **state)`
  - `test_sentinels_ok` (function, line 16) `static void test_sentinels_ok(void **state)`
  - `test_junk_fails_closed` (function, line 24) `static void test_junk_fails_closed(void **state)`
  - `test_alpha` (function, line 33) `static void test_alpha(void **state)`
  - `test_bg_skips_url` (function, line 65) `static void test_bg_skips_url(void **state)`
  - `main` (function, line 71) `int main(void)`
  - `digit` (function, line 43) `* digit(s) -- the minifier writes `transparent` as #0000. */ assert_int_equal(cv_bg_alpha_of("#0000"), 0);`
- Depends on: `include/css.h`, `include/css_values.h`

## tests/test_css_vars.c
- Doc: test_css_vars -- the custom-property table and var() substitution (spec/css_vars.md).
- Layer: testing
- Language: c
- Symbols:
  - `set` (function, line 15) `static int set(cvr_table *t, const char *n, const char *v)`
  - `get` (function, line 19) `static const char *get(const cvr_table *t, const char *n)`
  - `test_set_get_overwrite` (function, line 23) `static void test_set_get_overwrite(void **state)`
  - `test_names_are_case_sensitive` (function, line 36) `static void test_names_are_case_sensitive(void **state)`
  - `test_bounds_drop_whole` (function, line 46) `static void test_bounds_drop_whole(void **state)`
  - `test_grows_to_thousands` (function, line 66) `static void test_grows_to_thousands(void **state)`
  - `test_collect_strips_important_and_trims` (function, line 86) `static void test_collect_strips_important_and_trims(void **state)`
  - `test_collect_keeps_semicolon_inside_url` (function, line 98) `static void test_collect_keeps_semicolon_inside_url(void **state)`
  - `test_resolve_scope_order_and_fallback` (function, line 110) `static void test_resolve_scope_order_and_fallback(void **state)`
  - `test_resolve_depth_and_cycle` (function, line 129) `static void test_resolve_depth_and_cycle(void **state)`
  - `test_cycle_takes_fallback` (function, line 149) `static void test_cycle_takes_fallback(void **state)`
  - `test_fallback_fanout_is_budgeted` (function, line 162) `static void test_fallback_fanout_is_budgeted(void **state)`
  - `test_resolve_overflow_fails` (function, line 174) `static void test_resolve_overflow_fails(void **state)`
  - `main` (function, line 185) `int main(void)`
- Depends on: `include/css_vars.h`

## tests/test_data_url.c
- Layer: testing
- Language: c
- Symbols:
  - `test_is_data_url_true` (function, line 23) `static void test_is_data_url_true(void **state)`
  - `test_is_data_url_false` (function, line 31) `static void test_is_data_url_false(void **state)`
  - `test_payload_basic` (function, line 43) `static void test_payload_basic(void **state)`
  - `test_payload_no_mediatype` (function, line 54) `static void test_payload_no_mediatype(void **state)`
  - `test_payload_empty` (function, line 63) `static void test_payload_empty(void **state)`
  - `test_payload_not_data_url` (function, line 73) `static void test_payload_not_data_url(void **state)`
  - `test_payload_percent_encoded_not_supported` (function, line 81) `static void test_payload_percent_encoded_not_supported(void **state)`
  - `test_payload_no_comma` (function, line 89) `static void test_payload_no_comma(void **state)`
  - `test_payload_base64_flag_case_insensitive` (function, line 97) `static void test_payload_base64_flag_case_insensitive(void **state)`
  - `test_payload_too_large` (function, line 106) `static void test_payload_too_large(void **state)`
  - `test_payload_nulls` (function, line 122) `static void test_payload_nulls(void **state)`
  - `test_decode_one_byte_double_pad` (function, line 135) `static void test_decode_one_byte_double_pad(void **state)`
  - `test_decode_two_bytes_single_pad` (function, line 146) `static void test_decode_two_bytes_single_pad(void **state)`
  - `test_decode_no_padding_needed` (function, line 159) `static void test_decode_no_padding_needed(void **state)`
  - `test_decode_multi_group` (function, line 171) `static void test_decode_multi_group(void **state)`
  - `test_decode_empty` (function, line 183) `static void test_decode_empty(void **state)`
  - `test_decode_bad_length_not_multiple_of_4` (function, line 193) `static void test_decode_bad_length_not_multiple_of_4(void **state)`
  - `test_decode_padding_in_wrong_position` (function, line 201) `static void test_decode_padding_in_wrong_position(void **state)`
  - `test_decode_invalid_character` (function, line 210) `static void test_decode_invalid_character(void **state)`
  - `test_decode_too_large` (function, line 221) `static void test_decode_too_large(void **state)`
  - `test_decode_nulls` (function, line 236) `static void test_decode_nulls(void **state)`
  - `test_end_to_end_png_data_uri` (function, line 247) `static void test_end_to_end_png_data_uri(void **state)`
  - `test_decode_percent_encoded_script` (function, line 270) `static void test_decode_percent_encoded_script(void **state)`
  - `test_decode_base64_forgiving_and_mime` (function, line 284) `static void test_decode_base64_forgiving_and_mime(void **state)`
  - `test_decode_rejects` (function, line 302) `static void test_decode_rejects(void **state)`
  - `main` (function, line 317) `int main(void)`
- Depends on: `include/data_url.h`

## tests/test_disk_store.c
- Layer: testing
- Language: c
- Symbols:
  - `fixture` (struct, line 33)
  - `dir` (type_alias, line 32) `typedef struct fixture { char dir[64];`
  - `setup` (function, line 35) `static int setup(void **state)`
  - `teardown` (function, line 45) `static int teardown(void **state)`
  - `count_dir_entries` (function, line 65) `static size_t count_dir_entries(const char *dir)`
  - `test_roundtrip` (function, line 78) `static void test_roundtrip(void **state)`
  - `test_roundtrip_chacha` (function, line 89) `static void test_roundtrip_chacha(void **state)`
  - `test_empty` (function, line 99) `static void test_empty(void **state)`
  - `test_permissions` (function, line 108) `static void test_permissions(void **state)`
  - `test_no_temp_left` (function, line 117) `static void test_no_temp_left(void **state)`
  - `test_overwrite` (function, line 124) `static void test_overwrite(void **state)`
  - `test_wrong_key` (function, line 138) `static void test_wrong_key(void **state)`
  - `test_tamper_on_disk` (function, line 150) `static void test_tamper_on_disk(void **state)`
  - `test_missing_and_null` (function, line 168) `static void test_missing_and_null(void **state)`
  - `main` (function, line 181) `int main(void)`
  - `_POSIX_C_SOURCE` (macro, line 8) `#define _POSIX_C_SOURCE`
- Depends on: `include/disk_store.h`, `include/local_store.h`

## tests/test_dom.c
- Doc: setup_doc: #include "dom.h" #include "html_parse.h" static const char HTML[] = "<!DOCTYPE...
- Layer: testing
- Language: c
- Symbols:
  - `setup_doc` (function, line 32) `static int setup_doc(void **state)`
  - `teardown_doc` (function, line 45) `static int teardown_doc(void **state)`
  - `test_build_null_args` (function, line 60) `static void test_build_null_args(void **state)`
  - `test_free_null_and_double` (function, line 70) `static void test_free_null_and_double(void **state)`
  - `test_node_count` (function, line 81) `static void test_node_count(void **state)`
  - `test_get_by_id` (function, line 88) `static void test_get_by_id(void **state)`
  - `test_get_by_id_absent` (function, line 102) `static void test_get_by_id_absent(void **state)`
  - `test_by_class` (function, line 109) `static void test_by_class(void **state)`
  - `test_by_tag` (function, line 118) `static void test_by_tag(void **state)`
  - `test_by_tag_results_in_document_order` (function, line 127) `static void test_by_tag_results_in_document_order(void **state)`
  - `test_document_order` (function, line 137) `static void test_document_order(void **state)`
  - `test_navigation` (function, line 151) `static void test_navigation(void **state)`
  - `test_attributes` (function, line 171) `static void test_attributes(void **state)`
  - `test_text_content_read` (function, line 185) `static void test_text_content_read(void **state)`
  - `test_set_text_content_changes_tree` (function, line 196) `static void test_set_text_content_changes_tree(void **state)`
  - `test_set_text_content_empty_clears` (function, line 214) `static void test_set_text_content_empty_clears(void **state)`
  - `test_set_text_content_invalid_node` (function, line 224) `static void test_set_text_content_invalid_node(void **state)`
  - `test_set_and_get_document_title` (function, line 229) `static void test_set_and_get_document_title(void **state)`
  - `test_create_and_append` (function, line 241) `static void test_create_and_append(void **state)`
  - `test_append_rejects_cycle` (function, line 259) `static void test_append_rejects_cycle(void **state)`
  - `test_remove_child` (function, line 269) `static void test_remove_child(void **state)`
  - `test_set_attribute_reindexes_id` (function, line 281) `static void test_set_attribute_reindexes_id(void **state)`
  - `test_remove_attribute` (function, line 294) `static void test_remove_attribute(void **state)`
  - `test_set_inner_html` (function, line 311) `static void test_set_inner_html(void **state)`
  - `test_construction_invalid_args` (function, line 327) `static void test_construction_invalid_args(void **state)`
  - `test_get_inner_html` (function, line 335) `static void test_get_inner_html(void **state)`
  - `test_query_selector_type_class_id` (function, line 363) `static void test_query_selector_type_class_id(void **state)`
  - `test_query_selector_all_counts` (function, line 377) `static void test_query_selector_all_counts(void **state)`
  - `test_query_selector_combinators` (function, line 388) `static void test_query_selector_combinators(void **state)`
  - `rule` (function, line 405) `* silently drops the whole rule (fail closed), so the title read black-on-teal
 * instead of the ...`
  - `test_query_selector_nth_and_structural` (function, line 435) `static void test_query_selector_nth_and_structural(void **state)`
  - `test_query_selector_scope_is_descendants_only` (function, line 448) `static void test_query_selector_scope_is_descendants_only(void **state)`
  - `test_matches_and_closest` (function, line 460) `static void test_matches_and_closest(void **state)`
  - `test_query_selector_fail_closed` (function, line 473) `static void test_query_selector_fail_closed(void **state)`
  - `test_insert_before` (function, line 493) `static void test_insert_before(void **state)`
  - `test_clone_node` (function, line 525) `static void test_clone_node(void **state)`
  - `test_move_children` (function, line 548) `static void test_move_children(void **state)`
  - `test_char_nodes` (function, line 589) `static void test_char_nodes(void **state)`
  - `main` (function, line 636) `int main(void)`
  - `DOC` (macro, line 55) `#define DOC(state)`
  - `IDX` (macro, line 56) `#define IDX(state)`
- Depends on: `include/dom.h`, `include/html_parse.h`

## tests/test_dom_debug.c
- Doc: build: #include "dom_debug.h" #include "page_view.h" #include "render_doc.h" #include...
- Layer: testing
- Language: c
- Symbols:
  - `caps_css_on` (function, line 29) `static rdp_caps caps_css_on(void)`
  - `build` (function, line 36) `static rd_doc *build(pv_view *v, rdp_caps caps)`
  - `test_null_doc_is_empty_header` (function, line 45) `static void test_null_doc_is_empty_header(void **state)`
  - `test_heading_paragraph_link` (function, line 59) `static void test_heading_paragraph_link(void **state)`
  - `test_grid_container_annotation` (function, line 92) `static void test_grid_container_annotation(void **state)`
  - `test_box_tree_width_cap` (function, line 116) `static void test_box_tree_width_cap(void **state)`
  - `test_visibility_overflow_cursor_and_text_wrap` (function, line 154) `static void test_visibility_overflow_cursor_and_text_wrap(void **state)`
  - `test_no_box_tree_without_css` (function, line 197) `static void test_no_box_tree_without_css(void **state)`
  - `test_truncation_no_overflow` (function, line 217) `static void test_truncation_no_overflow(void **state)`
  - `test_control_bytes_kept_on_one_line` (function, line 245) `static void test_control_bytes_kept_on_one_line(void **state)`
  - `main` (function, line 269) `int main(void)`
- Depends on: `include/box_style.h`, `include/css.h`, `include/dom_debug.h`, `include/flex_layout.h`, `include/page_view.h`, `include/render_doc.h`, `include/render_policy.h`

## tests/test_download.c
- Layer: testing
- Language: c
- Symbols:
  - `builder` (function, line 8) `* builder (join, separator rejection, overflow, NULL), and the size cap.
 */

#include <setjmp.h>...`
  - `test_should_renderable_types` (function, line 30) `static void test_should_renderable_types(void **state)`
  - `test_should_binary_types` (function, line 41) `static void test_should_binary_types(void **state)`
  - `test_ext_known_types` (function, line 52) `static void test_ext_known_types(void **state)`
  - `test_ext_unknown_type` (function, line 63) `static void test_ext_unknown_type(void **state)`
  - `test_pick_from_disposition_quoted` (function, line 72) `static void test_pick_from_disposition_quoted(void **state)`
  - `test_pick_from_disposition_ext_form` (function, line 81) `static void test_pick_from_disposition_ext_form(void **state)`
  - `test_pick_from_url_segment` (function, line 91) `static void test_pick_from_url_segment(void **state)`
  - `test_pick_appends_extension_when_missing` (function, line 99) `static void test_pick_appends_extension_when_missing(void **state)`
  - `test_pick_keeps_existing_extension` (function, line 108) `static void test_pick_keeps_existing_extension(void **state)`
  - `test_pick_traversal_contained` (function, line 117) `static void test_pick_traversal_contained(void **state)`
  - `test_pick_fallback_when_empty` (function, line 129) `static void test_pick_fallback_when_empty(void **state)`
  - `test_pick_null_out` (function, line 141) `static void test_pick_null_out(void **state)`
  - `test_pick_overflow_fails_closed` (function, line 148) `static void test_pick_overflow_fails_closed(void **state)`
  - `test_build_path_basic` (function, line 158) `static void test_build_path_basic(void **state)`
  - `test_build_path_trailing_slash` (function, line 165) `static void test_build_path_trailing_slash(void **state)`
  - `test_build_path_rejects_separator_in_name` (function, line 172) `static void test_build_path_rejects_separator_in_name(void **state)`
  - `test_build_path_overflow` (function, line 179) `static void test_build_path_overflow(void **state)`
  - `test_build_path_null_args` (function, line 186) `static void test_build_path_null_args(void **state)`
  - `test_check_size` (function, line 197) `static void test_check_size(void **state)`
  - `main` (function, line 204) `int main(void)`
- Depends on: `include/download.h`

## tests/test_flex_layout.c
- Doc: test_autofill_count: assert_item(out[0], 0.0, 100.0);  /* no divide-by-zero, behaves like start...
- Layer: testing
- Language: c
- Symbols:
  - `assert_item` (function, line 26) `static void assert_item(fx_result r, double pos, double size)`
  - `test_grow_equal` (function, line 31) `static void test_grow_equal(void **state)`
  - `test_grow_weighted` (function, line 40) `static void test_grow_weighted(void **state)`
  - `test_shrink_equal` (function, line 49) `static void test_shrink_equal(void **state)`
  - `test_shrink_with_min_clamp` (function, line 58) `static void test_shrink_with_min_clamp(void **state)`
  - `test_gap_start` (function, line 68) `static void test_gap_start(void **state)`
  - `test_justify_center` (function, line 77) `static void test_justify_center(void **state)`
  - `test_justify_end` (function, line 86) `static void test_justify_end(void **state)`
  - `test_justify_space_between` (function, line 95) `static void test_justify_space_between(void **state)`
  - `test_justify_space_around` (function, line 104) `static void test_justify_space_around(void **state)`
  - `test_justify_space_evenly` (function, line 113) `static void test_justify_space_evenly(void **state)`
  - `test_space_between_single_item_is_start` (function, line 123) `static void test_space_between_single_item_is_start(void **state)`
  - `test_negative_fields_clamped` (function, line 131) `static void test_negative_fields_clamped(void **state)`
  - `test_autofill_count` (function, line 142) `static void test_autofill_count(void **state)`
  - `test_flex_zero_items_is_noop` (function, line 152) `static void test_flex_zero_items_is_noop(void **state)`
  - `test_flex_errors` (function, line 157) `static void test_flex_errors(void **state)`
  - `test_grid_columns` (function, line 169) `static void test_grid_columns(void **state)`
  - `test_grid_columns_too_narrow_clamps_to_zero` (function, line 181) `static void test_grid_columns_too_narrow_clamps_to_zero(void **state)`
  - `test_grid_columns_edges` (function, line 188) `static void test_grid_columns_edges(void **state)`
  - `test_grid_cell` (function, line 198) `static void test_grid_cell(void **state)`
  - `test_grid_weighted_fr` (function, line 209) `static void test_grid_weighted_fr(void **state)`
  - `test_grid_weighted_fixed_px_reserved_first` (function, line 221) `static void test_grid_weighted_fixed_px_reserved_first(void **state)`
  - `test_grid_weighted_all_auto_matches_equal` (function, line 233) `static void test_grid_weighted_all_auto_matches_equal(void **state)`
  - `test_grid_weighted_fixed_overflow_zeroes_fr` (function, line 246) `static void test_grid_weighted_fixed_overflow_zeroes_fr(void **state)`
  - `test_grid_weighted_errors` (function, line 256) `static void test_grid_weighted_errors(void **state)`
  - `test_grid_place_span_basic` (function, line 266) `static void test_grid_place_span_basic(void **state)`
  - `test_grid_place_span_wraps_when_it_does_not_fit` (function, line 277) `static void test_grid_place_span_wraps_when_it_does_not_fit(void **state)`
  - `test_grid_place_span_clamps_and_defaults` (function, line 289) `static void test_grid_place_span_clamps_and_defaults(void **state)`
  - `test_grid_place_rowspan` (function, line 305) `static void test_grid_place_rowspan(void **state)`
  - `test_float_pack_left` (function, line 322) `static void test_float_pack_left(void **state)`
  - `test_float_pack_left_and_right` (function, line 333) `static void test_float_pack_left_and_right(void **state)`
  - `test_float_pack_two_right` (function, line 345) `static void test_float_pack_two_right(void **state)`
  - `article` (function, line 362) `* article (slashdot-cols probe: score 13.41). */

static void test_float_pack_m_holy_grail_pull_u...`
  - `test_float_pack_m_zero_margins_match_wrap` (function, line 381) `static void test_float_pack_m_zero_margins_match_wrap(void **state)`
  - `test_float_pack_m_positive_margin_widens` (function, line 401) `static void test_float_pack_m_positive_margin_widens(void **state)`
  - `test_float_pack_m_right_float_negative_margin` (function, line 417) `static void test_float_pack_m_right_float_negative_margin(void **state)`
  - `test_float_pack_m_errors` (function, line 433) `static void test_float_pack_m_errors(void **state)`
  - `test_float_insets_left_overlapping_line` (function, line 458) `static void test_float_insets_left_overlapping_line(void **state)`
  - `test_float_insets_line_past_bottom_is_full_width` (function, line 468) `static void test_float_insets_line_past_bottom_is_full_width(void **state)`
  - `test_float_insets_right` (function, line 485) `static void test_float_insets_right(void **state)`
  - `test_float_insets_both_sides_take_the_tightest` (function, line 495) `static void test_float_insets_both_sides_take_the_tightest(void **state)`
  - `test_float_insets_never_starve_the_line` (function, line 510) `static void test_float_insets_never_starve_the_line(void **state)`
  - `test_float_insets_edges` (function, line 532) `static void test_float_insets_edges(void **state)`
  - `test_float_pack_edges` (function, line 552) `static void test_float_pack_edges(void **state)`
  - `test_float_pack_wrap_full_width_stack` (function, line 568) `static void test_float_pack_wrap_full_width_stack(void **state)`
  - `test_float_pack_wrap_fits_matches_v1` (function, line 582) `static void test_float_pack_wrap_fits_matches_v1(void **state)`
  - `test_float_pack_wrap_partial` (function, line 605) `static void test_float_pack_wrap_partial(void **state)`
  - `test_float_pack_wrap_errors` (function, line 628) `static void test_float_pack_wrap_errors(void **state)`
  - `test_justify_name` (function, line 637) `static void test_justify_name(void **state)`
  - `test_auto_min_size_is_min_content` (function, line 653) `static void test_auto_min_size_is_min_content(void **state)`
  - `test_multicol_used_counts` (function, line 680) `static void test_multicol_used_counts(void **state)`
  - `test_multicol_used_edges` (function, line 717) `static void test_multicol_used_edges(void **state)`
  - `test_area_hash_basics` (function, line 786) `static void test_area_hash_basics(void **state)`
  - `test_areas_parse_and_resolve` (function, line 798) `static void test_areas_parse_and_resolve(void **state)`
  - `test_areas_null_cell` (function, line 832) `static void test_areas_null_cell(void **state)`
  - `test_areas_rect_spans_rows_and_cols` (function, line 847) `static void test_areas_rect_spans_rows_and_cols(void **state)`
  - `test_areas_non_rectangular_is_rejected` (function, line 864) `static void test_areas_non_rectangular_is_rejected(void **state)`
  - `test_areas_parse_fails_closed` (function, line 878) `static void test_areas_parse_fails_closed(void **state)`
  - `test_areas_parse_bounds` (function, line 896) `static void test_areas_parse_bounds(void **state)`
  - `test_grid_place_null_fixed_is_unchanged` (function, line 926) `static void test_grid_place_null_fixed_is_unchanged(void **state)`
  - `test_grid_place_explicit_out_of_range_clamps` (function, line 938) `static void test_grid_place_explicit_out_of_range_clamps(void **state)`
  - `test_auto_margins_push_right_and_center` (function, line 949) `static void test_auto_margins_push_right_and_center(void **state)`
  - `test_column_place_stack_and_justify` (function, line 982) `static void test_column_place_stack_and_justify(void **state)`
  - `test_cross_offset` (function, line 1011) `static void test_cross_offset(void **state)`
  - `test_column_place_auto_margins` (function, line 1025) `static void test_column_place_auto_margins(void **state)`
  - `main` (function, line 1042) `int main(void)`
  - `to` (function, line 280) `* jumps to (1,0);`
- Depends on: `include/flex_layout.h`

## tests/test_form.c
- Layer: testing
- Language: c
- Symbols:
  - `test_encode_basic` (function, line 24) `static void test_encode_basic(void **state)`
  - `test_encode_space_and_reserved` (function, line 34) `static void test_encode_space_and_reserved(void **state)`
  - `test_encode_unreserved_kept` (function, line 43) `static void test_encode_unreserved_kept(void **state)`
  - `test_encode_empty_and_nameless` (function, line 51) `static void test_encode_empty_and_nameless(void **state)`
  - `test_encode_overflow_fails_closed` (function, line 59) `static void test_encode_overflow_fails_closed(void **state)`
  - `test_encode_null_args` (function, line 67) `static void test_encode_null_args(void **state)`
  - `test_get_relative_action_on_https_base` (function, line 78) `static void test_get_relative_action_on_https_base(void **state)`
  - `test_get_absolute_https_action_ignores_base` (function, line 89) `static void test_get_absolute_https_action_ignores_base(void **state)`
  - `test_get_empty_action_submits_to_base` (function, line 100) `static void test_get_empty_action_submits_to_base(void **state)`
  - `test_get_replaces_existing_query` (function, line 109) `static void test_get_replaces_existing_query(void **state)`
  - `test_get_action_cleaned_of_whitespace` (function, line 119) `static void test_get_action_cleaned_of_whitespace(void **state)`
  - `test_post_builds_body` (function, line 130) `static void test_post_builds_body(void **state)`
  - `test_block_http_downgrade` (function, line 145) `static void test_block_http_downgrade(void **state)`
  - `test_block_foreign_scheme` (function, line 155) `static void test_block_foreign_scheme(void **state)`
  - `test_block_relative_action_on_local_base` (function, line 164) `static void test_block_relative_action_on_local_base(void **state)`
  - `test_block_too_many_fields` (function, line 173) `static void test_block_too_many_fields(void **state)`
  - `test_block_null_field_name` (function, line 183) `static void test_block_null_field_name(void **state)`
  - `test_build_null_args` (function, line 192) `static void test_build_null_args(void **state)`
  - `test_get_no_fields_still_navigates` (function, line 199) `static void test_get_no_fields_still_navigates(void **state)`
  - `main` (function, line 207) `int main(void)`
- Depends on: `include/form.h`

## tests/test_frame_clock.c
- Layer: testing
- Language: c
- Symbols:
  - `test_set_active_and_needs_tick` (function, line 23) `static void test_set_active_and_needs_tick(void **state)`
  - `test_set_active_twice` (function, line 36) `static void test_set_active_twice(void **state)`
  - `test_null_safe` (function, line 45) `static void test_null_safe(void **state)`
  - `main` (function, line 53) `int main(void)`
- Depends on: `include/frame_clock.h`

## tests/test_freebug.c
- Layer: testing
- Language: c
- Symbols:
  - `test_push_and_read` (function, line 21) `static void test_push_and_read(void **state)`
  - `test_empty_and_null_text` (function, line 46) `static void test_empty_and_null_text(void **state)`
  - `test_count_cap_fails_closed` (function, line 59) `static void test_count_cap_fails_closed(void **state)`
  - `test_entry_truncated_not_dropped` (function, line 75) `static void test_entry_truncated_not_dropped(void **state)`
  - `test_total_bytes_cap_fails_closed` (function, line 93) `static void test_total_bytes_cap_fails_closed(void **state)`
  - `test_level_clamped` (function, line 118) `static void test_level_clamped(void **state)`
  - `test_level_name` (function, line 129) `static void test_level_name(void **state)`
  - `test_reset_reuses_and_no_leak` (function, line 140) `static void test_reset_reuses_and_no_leak(void **state)`
  - `test_free_idempotent` (function, line 161) `static void test_free_idempotent(void **state)`
  - `test_push_loc_records_location` (function, line 175) `static void test_push_loc_records_location(void **state)`
  - `test_push_loc_null_file_and_negative_nums` (function, line 197) `static void test_push_loc_null_file_and_negative_nums(void **state)`
  - `test_push_loc_file_truncated` (function, line 214) `static void test_push_loc_file_truncated(void **state)`
  - `main` (function, line 228) `int main(void)`
- Depends on: `include/freebug.h`

## tests/test_freedom.c
- Doc: run_freedom_raw: Runs the binary with a raw argument string (no implicit --headless), capturing...
- Layer: testing
- Language: c
- Symbols:
  - `run_freedom` (function, line 30) `static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status)`
  - `run_freedom_raw` (function, line 52) `static int run_freedom_raw(const char *args, int *exit_status)`
  - `is_pdf_file` (function, line 64) `static int is_pdf_file(const char *path)`
  - `is_png_file` (function, line 74) `static int is_png_file(const char *path)`
  - `cleanup_files` (function, line 84) `static void cleanup_files(void)`
  - `read_file_all` (function, line 90) `static uint8_t *read_file_all(const char *path, size_t *out_len)`
  - `test_help` (function, line 107) `static void test_help(void **state)`
  - `test_version` (function, line 116) `static void test_version(void **state)`
  - `test_no_args` (function, line 125) `static void test_no_args(void **state)`
  - `test_local_html` (function, line 135) `static void test_local_html(void **state)`
  - `test_headless_js_measures_real_geometry` (function, line 161) `static void test_headless_js_measures_real_geometry(void **state)`
  - `test_headless_timer_navigation_followed` (function, line 187) `static void test_headless_timer_navigation_followed(void **state)`
  - `test_local_form_renders_inputs` (function, line 210) `static void test_local_form_renders_inputs(void **state)`
  - `test_missing_file` (function, line 236) `static void test_missing_file(void **state)`
  - `test_download_pdf_local` (function, line 246) `static void test_download_pdf_local(void **state)`
  - `test_download_pdf_requires_path` (function, line 272) `static void test_download_pdf_requires_path(void **state)`
  - `test_download_png_local` (function, line 281) `static void test_download_png_local(void **state)`
  - `test_download_png_images_local` (function, line 313) `static void test_download_png_images_local(void **state)`
  - `test_download_png_requires_path` (function, line 374) `static void test_download_png_requires_path(void **state)`
  - `test_download_png_negative_zindex_paints_behind_inflow` (function, line 390) `static void test_download_png_negative_zindex_paints_behind_inflow(void **state)`
  - `test_download_png_positioned_overflow_clips_own_content` (function, line 443) `static void test_download_png_positioned_overflow_clips_own_content(void **state)`
  - `blend` (function, line 491) `* not some other blend (double-composited or wrong alpha). */
static void test_download_png_group...`
  - `test_download_png_absolute_shrinks_and_anchors_right` (function, line 556) `static void test_download_png_absolute_shrinks_and_anchors_right(void **state)`
  - `ink_width` (function, line 630) `static double ink_width(const char *html)`
  - `test_absolute_font_size_lands_exact` (function, line 677) `static void test_absolute_font_size_lands_exact(void **state)`
  - `test_author_font_size_on_heading_replaces_ua_scale` (function, line 695) `static void test_author_font_size_on_heading_replaces_ua_scale(void **state)`
  - `test_heading_colour_matches_body_text` (function, line 715) `static void test_heading_colour_matches_body_text(void **state)`
  - `test_author_can_unbold_a_heading` (function, line 770) `static void test_author_can_unbold_a_heading(void **state)`
  - `test_absolute_span_honours_right_bottom` (function, line 789) `static void test_absolute_span_honours_right_bottom(void **state)`
  - `test_download_png_nested_flex_lays_out_on_one_row` (function, line 859) `static void test_download_png_nested_flex_lays_out_on_one_row(void **state)`
  - `test_download_png_inline_block_flows_in_line` (function, line 938) `static void test_download_png_inline_block_flows_in_line(void **state)`
  - `test_inline_run_boundary_does_not_invent_space` (function, line 1011) `static void test_inline_run_boundary_does_not_invent_space(void **state)`
  - `test_inline_run_boundary_collapses_runs_of_space` (function, line 1032) `static void test_inline_run_boundary_collapses_runs_of_space(void **state)`
  - `test_download_png_inline_replaced_share_row` (function, line 1052) `static void test_download_png_inline_replaced_share_row(void **state)`
  - `test_download_png_broken_image_keeps_row_order` (function, line 1112) `static void test_download_png_broken_image_keeps_row_order(void **state)`
  - `test_download_png_replaced_pct_width` (function, line 1164) `static void test_download_png_replaced_pct_width(void **state)`
  - `wf_test_host_font` (function, line 1243) `static uint8_t *wf_test_host_font(const char *name, size_t *out_n)`
  - `test_download_png_webfont_shapes` (function, line 1264) `static void test_download_png_webfont_shapes(void **state)`
  - `test_download_png_line_height_zero_does_not_shrink_line` (function, line 1386) `static void test_download_png_line_height_zero_does_not_shrink_line(void **state)`
  - `blend` (function, line 1517) `* visibly different from either input color or an OVER blend (which would show
 * opaque blue). E...`
  - `markup` (function, line 1647) `* against an unrotated control render of the identical markup (a 50-char-wide box
 * at x:[24,975...`
  - `markup` (function, line 1706) `* unscaled control render of the identical markup (box y:[24,49] at x=500,
 * center y~36.5): y=2...`
  - `test_dump_console_shows_output_and_error` (function, line 1765) `static void test_dump_console_shows_output_and_error(void **state)`
  - `test_no_dump_console_without_flag` (function, line 1800) `static void test_no_dump_console_without_flag(void **state)`
  - `test_dump_dom_prints_render_tree` (function, line 1825) `static void test_dump_dom_prints_render_tree(void **state)`
  - `ballooned` (function, line 1858) `* ballooned (body + wrapper re-opened per child) and the LAST wrapper piece
 * became the contain...`
  - `test_dump_layout_oof_subtree_real_layout` (function, line 1927) `static void test_dump_layout_oof_subtree_real_layout(void **state)`
  - `test_dump_layout_flex_item_sibling_boxes` (function, line 1968) `static void test_dump_layout_flex_item_sibling_boxes(void **state)`
  - `test_dump_layout_sticky_footer` (function, line 2042) `static void test_dump_layout_sticky_footer(void **state)`
  - `test_dump_layout_root_box_survives_replaced_run` (function, line 2077) `static void test_dump_layout_root_box_survives_replaced_run(void **state)`
  - `test_dump_layout_pulled_rail_single_margin` (function, line 2170) `static void test_dump_layout_pulled_rail_single_margin(void **state)`
  - `test_dump_layout_row_nested_in_column` (function, line 2286) `static void test_dump_layout_row_nested_in_column(void **state)`
  - `test_dump_layout_inline_box_second_run_stays` (function, line 2337) `static void test_dump_layout_inline_box_second_run_stays(void **state)`
  - `band` (function, line 2366) `* band (which already recurses into nested containers) owns it. */
static void test_dump_layout_c...`
  - `test_dump_layout_line_opening_image_is_inline` (function, line 2409) `static void test_dump_layout_line_opening_image_is_inline(void **state)`
  - `test_dump_layout_band_flushes_line_before_clear` (function, line 2435) `static void test_dump_layout_band_flushes_line_before_clear(void **state)`
  - `test_dump_layout_flex_auto_margin_push_right` (function, line 2475) `static void test_dump_layout_flex_auto_margin_push_right(void **state)`
  - `test_dump_layout_nested_column_takes_max` (function, line 2518) `static void test_dump_layout_nested_column_takes_max(void **state)`
  - `test_rejects_http_url` (function, line 2567) `static void test_rejects_http_url(void **state)`
  - `white` (function, line 2629) `* and not white (the old behaviour where only text rows got background fills). */
static void tes...`
  - `test_download_png_gradient_box_text_keeps_gradient` (function, line 2725) `static void test_download_png_gradient_box_text_keeps_gradient(void **state)`
  - `test_download_png_flex_container_paints_one_band` (function, line 2750) `static void test_download_png_flex_container_paints_one_band(void **state)`
  - `test_download_png_inline_block_shrinks_and_centers` (function, line 2770) `static void test_download_png_inline_block_shrinks_and_centers(void **state)`
  - `test_download_png_inline_svg_path_and_drops_image` (function, line 2814) `static void test_download_png_inline_svg_path_and_drops_image(void **state)`
  - `test_dump_timings_prints_stages` (function, line 2830) `static void test_dump_timings_prints_stages(void **state)`
  - `main` (function, line 2855) `int main(void)`
  - `rows` (function, line 992) `* rows (the bug) made it several times taller. */ assert_true(px.height < 60);`
  - `bottom` (function, line 2150) `* at the page bottom (the grey-stripe bug had npositioned pushing it away). */ /* (Each sized float now has a box of...`
  - `_POSIX_C_SOURCE` (macro, line 11) `#define _POSIX_C_SOURCE`
  - `FREEDOM_BIN` (macro, line 26) `#define FREEDOM_BIN`
  - `OUT_FILE` (macro, line 27) `#define OUT_FILE`
  - `ERR_FILE` (macro, line 28) `#define ERR_FILE`
- Depends on: `include/image_decode.h`

## tests/test_hls.c
- Layer: testing
- Language: c
- Symbols:
  - `test_not_m3u8_returns_parse_error` (function, line 15) `static void test_not_m3u8_returns_parse_error(void **state)`
  - `test_empty_m3u8_is_ok` (function, line 22) `static void test_empty_m3u8_is_ok(void **state)`
  - `test_single_segment` (function, line 31) `static void test_single_segment(void **state)`
  - `test_multiple_segments` (function, line 46) `static void test_multiple_segments(void **state)`
  - `test_target_duration_is_parsed` (function, line 68) `static void test_target_duration_is_parsed(void **state)`
  - `test_variant_playlist_detected` (function, line 83) `static void test_variant_playlist_detected(void **state)`
  - `test_variant_playlist_collects_variants` (function, line 97) `static void test_variant_playlist_collects_variants(void **state)`
  - `test_multi_variant_collects_all` (function, line 114) `static void test_multi_variant_collects_all(void **state)`
  - `test_select_variant_highest_bandwidth_no_limit` (function, line 135) `static void test_select_variant_highest_bandwidth_no_limit(void **state)`
  - `test_select_variant_respects_max_dimensions` (function, line 152) `static void test_select_variant_respects_max_dimensions(void **state)`
  - `test_select_variant_empty_returns_error` (function, line 170) `static void test_select_variant_empty_returns_error(void **state)`
  - `test_resolve_url_absolute_passthrough` (function, line 180) `static void test_resolve_url_absolute_passthrough(void **state)`
  - `test_resolve_url_relative` (function, line 190) `static void test_resolve_url_relative(void **state)`
  - `test_resolve_url_deep_relative` (function, line 200) `static void test_resolve_url_deep_relative(void **state)`
  - `test_handles_windows_line_endings` (function, line 209) `static void test_handles_windows_line_endings(void **state)`
  - `main` (function, line 219) `int main(void)`
- Depends on: `include/hls.h`


Next: [KB_tests_p4.md](KB_tests_p4.md)
