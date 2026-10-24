# Subsystem: tests (page 3 of 8)
Previous: [KB_tests_p2.md](KB_tests_p2.md)

## tests/test_css_drops.c
- Doc: Suite for the parser drop log (spec/css_drops.md).
- Layer: testing
- Language: c
- Symbols:
  - `find_drop` (function, line 31) `static const css_drop *find_drop(const css_drop_log *log, const char *prop)`
  - `test_unknown_property_is_logged` (function, line 39) `static void test_unknown_property_is_logged(void **state)`
  - `test_bad_value_is_distinguished` (function, line 56) `static void test_bad_value_is_distinguished(void **state)`
  - `test_accepted_declaration_is_not_logged` (function, line 69) `static void test_accepted_declaration_is_not_logged(void **state)`
  - `test_repeats_coalesce_by_property_and_cause` (function, line 82) `static void test_repeats_coalesce_by_property_and_cause(void **state)`
  - `test_custom_property_is_not_a_drop` (function, line 109) `static void test_custom_property_is_not_a_drop(void **state)`
  - `test_full_log_still_counts_total` (function, line 121) `static void test_full_log_still_counts_total(void **state)`
  - `test_null_items_disables_listing` (function, line 132) `static void test_null_items_disables_listing(void **state)`
  - `test_long_value_truncates_and_control_bytes_are_stripped` (function, line 145) `static void test_long_value_truncates_and_control_bytes_are_stripped(void **state)`
  - `test_log_does_not_change_resolution` (function, line 173) `static void test_log_does_not_change_resolution(void **state)`
  - `parse_nodrop` (function, line 199) `static css_sheet *parse_nodrop(const char *text)`
  - `var` (function, line 213) `* was never collected and 40 var() declarations died as bad values. */
static void test_leading_b...`
  - `test_transform_function_names_are_case_insensitive` (function, line 238) `static void test_transform_function_names_are_case_insensitive(void **state)`
  - `test_transform_angle_units` (function, line 249) `static void test_transform_angle_units(void **state)`
  - `test_transform_3d_flattens` (function, line 260) `static void test_transform_3d_flattens(void **state)`
  - `test_transform_origin_number_component` (function, line 272) `static void test_transform_origin_number_component(void **state)`
  - `test_background_size_two_lengths` (function, line 283) `static void test_background_size_two_lengths(void **state)`
  - `test_background_position_percentages` (function, line 294) `static void test_background_position_percentages(void **state)`
  - `test_vertical_align_length` (function, line 313) `static void test_vertical_align_length(void **state)`
  - `test_css_wide_keyword_on_shorthand` (function, line 324) `static void test_css_wide_keyword_on_shorthand(void **state)`
  - `test_overflow_two_values` (function, line 334) `static void test_overflow_two_values(void **state)`
  - `test_intrinsic_sizing_keywords` (function, line 360) `static void test_intrinsic_sizing_keywords(void **state)`
  - `test_vendor_prefixed_value_keyword` (function, line 372) `static void test_vendor_prefixed_value_keyword(void **state)`
  - `test_font_shorthand_with_line_height` (function, line 382) `static void test_font_shorthand_with_line_height(void **state)`
  - `main` (function, line 392) `int main(void)`
- Depends on: `include/css.h`

## tests/test_css_gradient.c
- Layer: testing
- Language: c
- Symbols:
  - `test_linear_basic` (function, line 9) `static void test_linear_basic(void **state)`
  - `test_junk_drops` (function, line 22) `static void test_junk_drops(void **state)`
  - `test_url_single` (function, line 32) `static void test_url_single(void **state)`
  - `test_shorthand_resets` (function, line 43) `static void test_shorthand_resets(void **state)`
  - `test_shorthand_broken_drops` (function, line 54) `static void test_shorthand_broken_drops(void **state)`
  - `test_degree_prelude_edges` (function, line 64) `static void test_degree_prelude_edges(void **state)`
  - `test_radial_prelude_github_glow` (function, line 85) `static void test_radial_prelude_github_glow(void **state)`
  - `test_radial_prelude_keywords_and_defaults` (function, line 98) `static void test_radial_prelude_keywords_and_defaults(void **state)`
  - `test_radial_prelude_px_sizes_and_failures` (function, line 123) `static void test_radial_prelude_px_sizes_and_failures(void **state)`
  - `test_radial_len_resolution` (function, line 148) `static void test_radial_len_resolution(void **state)`
  - `near_d` (function, line 157) `static int near_d(double a, double b)`
  - `test_radial_geometry_keywords` (function, line 159) `static void test_radial_geometry_keywords(void **state)`
  - `main` (function, line 196) `int main(void)`
- Depends on: `include/css.h`, `include/css_gradient.h`

## tests/test_css_index.c
- Doc: test_css_index -- cascade rule index (spec/css_index.md).
- Layer: testing
- Language: c
- Symbols:
  - `parse_all` (function, line 14) `static css_sel *parse_all(const char *const *src, size_t n)`
  - `elem` (function, line 24) `static css_element elem(const char *tag, const char *id,
                        const char *cons...`
  - `has` (function, line 35) `static int has(const uint32_t *v, size_t n, uint32_t x)`
  - `test_buckets_and_order` (function, line 40) `static void test_buckets_and_order(void **state)`
  - `test_id_key` (function, line 61) `static void test_id_key(void **state)`
  - `test_long_class_folds` (function, line 82) `static void test_long_class_folds(void **state)`
  - `test_matching_implies_candidate` (function, line 105) `static void test_matching_implies_candidate(void **state)`
  - `test_invalid_index_reports_fallback` (function, line 140) `static void test_invalid_index_reports_fallback(void **state)`
  - `main` (function, line 153) `int main(void)`
- Depends on: `include/css_index.h`

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

## tests/test_css_mask.c
- Doc: Finds the value a decl list assigns to prop, or def when absent.
- Layer: testing
- Language: c
- Symbols:
  - `val_of` (function, line 10) `static int val_of(const css_decl *d, int n, int prop, int def)`
  - `has` (function, line 14) `static int has(const css_decl *d, int n, int prop)`
  - `test_prop_names` (function, line 19) `static void test_prop_names(void **state)`
  - `test_fade_gradient` (function, line 32) `static void test_fade_gradient(void **state)`
  - `test_gradient_border_technique` (function, line 77) `static void test_gradient_border_technique(void **state)`
  - `test_composite_vocabularies` (function, line 102) `static void test_composite_vocabularies(void **state)`
  - `test_clip_property` (function, line 122) `static void test_clip_property(void **state)`
  - `test_unsupported_fails_closed` (function, line 134) `static void test_unsupported_fails_closed(void **state)`
  - `test_none_resets` (function, line 149) `static void test_none_resets(void **state)`
  - `test_encode_decode_roundtrip` (function, line 162) `static void test_encode_decode_roundtrip(void **state)`
  - `test_split_never_overruns` (function, line 185) `static void test_split_never_overruns(void **state)`
  - `main` (function, line 200) `int main(void)`
- Depends on: `include/css_mask.h`

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
- Doc: test_aspect_ratio_large_keeps_shape: A large ratio (video sizes, `1206/684`) must keep its...
- Layer: testing
- Language: c
- Symbols:
  - `test_fontfamily_bucket` (function, line 10) `static void test_fontfamily_bucket(void **state)`
  - `test_opacity_shapes` (function, line 18) `static void test_opacity_shapes(void **state)`
  - `test_whitespace_direction` (function, line 26) `static void test_whitespace_direction(void **state)`
  - `test_shadow_needs_both_offsets` (function, line 34) `static void test_shadow_needs_both_offsets(void **state)`
  - `test_aspect_ratio` (function, line 44) `static void test_aspect_ratio(void **state)`
  - `test_aspect_ratio_large_keeps_shape` (function, line 59) `static void test_aspect_ratio_large_keeps_shape(void **state)`
  - `main` (function, line 73) `int main(void)`
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
  - `test_filter_scale_neutral_when_undeclared` (function, line 72) `static void test_filter_scale_neutral_when_undeclared(void **state)`
  - `main` (function, line 85) `int main(void)`
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
  - `test_multicol_used_counts` (function, line 686) `static void test_multicol_used_counts(void **state)`
  - `test_multicol_used_edges` (function, line 723) `static void test_multicol_used_edges(void **state)`
  - `test_area_hash_basics` (function, line 792) `static void test_area_hash_basics(void **state)`
  - `test_areas_parse_and_resolve` (function, line 804) `static void test_areas_parse_and_resolve(void **state)`
  - `test_areas_null_cell` (function, line 838) `static void test_areas_null_cell(void **state)`
  - `test_areas_rect_spans_rows_and_cols` (function, line 853) `static void test_areas_rect_spans_rows_and_cols(void **state)`
  - `test_areas_non_rectangular_is_rejected` (function, line 870) `static void test_areas_non_rectangular_is_rejected(void **state)`
  - `test_areas_parse_fails_closed` (function, line 884) `static void test_areas_parse_fails_closed(void **state)`
  - `test_areas_parse_bounds` (function, line 902) `static void test_areas_parse_bounds(void **state)`
  - `test_grid_line_side` (function, line 931) `static void test_grid_line_side(void **state)`
  - `test_grid_line_parse` (function, line 959) `static void test_grid_line_parse(void **state)`
  - `test_grid_line_resolve_table` (function, line 978) `static void test_grid_line_resolve_table(void **state)`
  - `test_grid_place_fixed_col_auto_row` (function, line 1009) `static void test_grid_place_fixed_col_auto_row(void **state)`
  - `test_grid_place_null_fixed_is_unchanged` (function, line 1040) `static void test_grid_place_null_fixed_is_unchanged(void **state)`
  - `test_grid_place_explicit_out_of_range_clamps` (function, line 1052) `static void test_grid_place_explicit_out_of_range_clamps(void **state)`
  - `test_auto_margins_push_right_and_center` (function, line 1063) `static void test_auto_margins_push_right_and_center(void **state)`
  - `test_column_place_stack_and_justify` (function, line 1096) `static void test_column_place_stack_and_justify(void **state)`
  - `test_cross_offset` (function, line 1125) `static void test_cross_offset(void **state)`
  - `test_column_place_auto_margins` (function, line 1139) `static void test_column_place_auto_margins(void **state)`
  - `main` (function, line 1180) `int main(void)`
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


Next: [KB_tests_p4.md](KB_tests_p4.md)
