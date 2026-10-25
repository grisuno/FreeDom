# Symbols (page 13 of 16)
Previous: [SYMBOLS_p12.md](SYMBOLS_p12.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `ERR_FILE` | macro | `tests/test_freedom.c:29` | `#define ERR_FILE` |
| `FREEDOM_BIN` | macro | `tests/test_freedom.c:27` | `#define FREEDOM_BIN` |
| `OUT_FILE` | macro | `tests/test_freedom.c:28` | `#define OUT_FILE` |
| `PIXEL` | macro | `tests/test_freedom.c:509` | `#define PIXEL(yy, xx)` |
| `_DEFAULT_SOURCE` | macro | `tests/test_freedom.c:1` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `tests/test_freedom.c:12` | `#define _POSIX_C_SOURCE` |
| `ballooned` | function | `tests/test_freedom.c:2415` | `* ballooned (body + wrapper re-opened per child) and the LAST wrapper piece  * became the contain...` |
| `band` | function | `tests/test_freedom.c:3492` | `* band (which already recurses into nested containers) owns it. */ static void test_dump_layout_c...` |
| `blend` | function | `tests/test_freedom.c:1048` | `* not some other blend (double-composited or wrong alpha). */ static void test_download_png_group...` |
| `blend` | function | `tests/test_freedom.c:2074` | `* visibly different from either input color or an OVER blend (which would show  * opaque blue). E...` |
| `bottom` | function | `tests/test_freedom.c:3275` | `* at the page bottom (the grey-stripe bug had npositioned pushing it away). */ /* (Each sized float now has a box of...` |
| `cleanup_files` | function | `tests/test_freedom.c:85` | `static void cleanup_files(void)` |
| `count_color_in_row` | function | `tests/test_freedom.c:757` | `static int count_color_in_row(const img_pixels *px, uint32_t y, uint32_t rgb)` |
| `has_box` | function | `tests/test_freedom.c:2923` | `static int has_box(const char *out, double w, double h, double t0, double t1)` |
| `has_box_x` | function | `tests/test_freedom.c:2937` | `static int has_box_x(const char *out, double x0, double w0)` |
| `has_row_x` | function | `tests/test_freedom.c:2950` | `static int has_row_x(const char *out, double x0)` |
| `has_sub_x` | function | `tests/test_freedom.c:2961` | `static int has_sub_x(const char *out, double x0)` |
| `ink_width` | function | `tests/test_freedom.c:1187` | `static double ink_width(const char *html)` |
| `is_pdf_file` | function | `tests/test_freedom.c:65` | `static int is_pdf_file(const char *path)` |
| `is_png_file` | function | `tests/test_freedom.c:75` | `static int is_png_file(const char *path)` |
| `it` | function | `tests/test_freedom.c:2555` | `* the clip does not hide it (slashdot with JS on, tanda 53). */ static void test_dump_layout_rail...` |
| `layout_of` | function | `tests/test_freedom.c:2909` | `static void layout_of(const char *html, const char *path, char *out, size_t cap)` |
| `lost` | function | `tests/test_freedom.c:356` | `* lost (every code sample on animate.css lost its leading characters). */ static void test_pre_le...` |
| `main` | function | `tests/test_freedom.c:4317` | `int main(void)` |
| `markup` | function | `tests/test_freedom.c:2204` | `* against an unrotated control render of the identical markup (a 50-char-wide box  * at x:[24,975...` |
| `markup` | function | `tests/test_freedom.c:2263` | `* unscaled control render of the identical markup (box y:[24,49] at x=500,  * center y~36.5): y=2...` |
| `png_leftmost_ink` | function | `tests/test_freedom.c:340` | `static int png_leftmost_ink(const img_pixels *px, uint32_t y0, uint32_t y1, uint32_t *row)` |
| `read_file_all` | function | `tests/test_freedom.c:91` | `static uint8_t *read_file_all(const char *path, size_t *out_len)` |
| `render_html_pixels` | function | `tests/test_freedom.c:730` | `static int render_html_pixels(const char *html, img_pixels *out)` |
| `rows` | function | `tests/test_freedom.c:1549` | `* rows (the bug) made it several times taller. */ assert_true(px.height < 60);` |
| `run_freedom` | function | `tests/test_freedom.c:31` | `static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status)` |
| `run_freedom_raw` | function | `tests/test_freedom.c:53` | `static int run_freedom_raw(const char *args, int *exit_status)` |
| `test_absolute_font_size_lands_exact` | function | `tests/test_freedom.c:1234` | `static void test_absolute_font_size_lands_exact(void **state)` |
| `test_absolute_span_honours_right_bottom` | function | `tests/test_freedom.c:1346` | `static void test_absolute_span_honours_right_bottom(void **state)` |
| `test_author_can_unbold_a_heading` | function | `tests/test_freedom.c:1327` | `static void test_author_can_unbold_a_heading(void **state)` |
| `test_author_font_size_on_heading_replaces_ua_scale` | function | `tests/test_freedom.c:1252` | `static void test_author_font_size_on_heading_replaces_ua_scale(void **state)` |
| `test_download_pdf_local` | function | `tests/test_freedom.c:278` | `static void test_download_pdf_local(void **state)` |
| `test_download_pdf_requires_path` | function | `tests/test_freedom.c:304` | `static void test_download_pdf_requires_path(void **state)` |
| `test_download_png_absolute_shrinks_and_anchors_right` | function | `tests/test_freedom.c:1113` | `static void test_download_png_absolute_shrinks_and_anchors_right(void **state)` |
| `test_download_png_background_clip_content_and_padding_box` | function | `tests/test_freedom.c:480` | `static void test_download_png_background_clip_content_and_padding_box(void **state)` |
| `test_download_png_broken_image_keeps_row_order` | function | `tests/test_freedom.c:1669` | `static void test_download_png_broken_image_keeps_row_order(void **state)` |
| `test_download_png_flex_container_paints_one_band` | function | `tests/test_freedom.c:3937` | `static void test_download_png_flex_container_paints_one_band(void **state)` |
| `test_download_png_gradient_box_text_keeps_gradient` | function | `tests/test_freedom.c:3912` | `static void test_download_png_gradient_box_text_keeps_gradient(void **state)` |
| `test_download_png_images_local` | function | `tests/test_freedom.c:819` | `static void test_download_png_images_local(void **state)` |
| `test_download_png_inline_block_flows_in_line` | function | `tests/test_freedom.c:1495` | `static void test_download_png_inline_block_flows_in_line(void **state)` |
| `test_download_png_inline_block_shrinks_and_centers` | function | `tests/test_freedom.c:3957` | `static void test_download_png_inline_block_shrinks_and_centers(void **state)` |
| `test_download_png_inline_replaced_share_row` | function | `tests/test_freedom.c:1609` | `static void test_download_png_inline_replaced_share_row(void **state)` |
| `test_download_png_inline_svg_path_and_drops_image` | function | `tests/test_freedom.c:4001` | `static void test_download_png_inline_svg_path_and_drops_image(void **state)` |
| `test_download_png_line_height_zero_does_not_shrink_line` | function | `tests/test_freedom.c:1943` | `static void test_download_png_line_height_zero_does_not_shrink_line(void **state)` |
| `test_download_png_local` | function | `tests/test_freedom.c:313` | `static void test_download_png_local(void **state)` |
| `test_download_png_negative_zindex_paints_behind_inflow` | function | `tests/test_freedom.c:896` | `static void test_download_png_negative_zindex_paints_behind_inflow(void **state)` |
| `test_download_png_nested_flex_lays_out_on_one_row` | function | `tests/test_freedom.c:1416` | `static void test_download_png_nested_flex_lays_out_on_one_row(void **state)` |
| `test_download_png_overflow_clips_at_padding_box` | function | `tests/test_freedom.c:439` | `static void test_download_png_overflow_clips_at_padding_box(void **state)` |
| `test_download_png_positioned_overflow_clips_own_content` | function | `tests/test_freedom.c:1000` | `static void test_download_png_positioned_overflow_clips_own_content(void **state)` |
| `test_download_png_replaced_pct_width` | function | `tests/test_freedom.c:1721` | `static void test_download_png_replaced_pct_width(void **state)` |
| `test_download_png_requires_path` | function | `tests/test_freedom.c:880` | `static void test_download_png_requires_path(void **state)` |
| `test_download_png_svg_in_button_stays_in_its_box` | function | `tests/test_freedom.c:401` | `static void test_download_png_svg_in_button_stays_in_its_box(void **state)` |
| `test_download_png_text_color_alpha_blends` | function | `tests/test_freedom.c:4234` | `static void test_download_png_text_color_alpha_blends(void **state)` |
| `test_download_png_webfont_shapes` | function | `tests/test_freedom.c:1821` | `static void test_download_png_webfont_shapes(void **state)` |
| `test_dump_console_shows_output_and_error` | function | `tests/test_freedom.c:2322` | `static void test_dump_console_shows_output_and_error(void **state)` |
| `test_dump_dom_prints_render_tree` | function | `tests/test_freedom.c:2382` | `static void test_dump_dom_prints_render_tree(void **state)` |
| `test_dump_layout_band_flushes_line_before_clear` | function | `tests/test_freedom.c:3561` | `static void test_dump_layout_band_flushes_line_before_clear(void **state)` |
| `test_dump_layout_bounded_wrapper_around_lone_right_float` | function | `tests/test_freedom.c:3006` | `static void test_dump_layout_bounded_wrapper_around_lone_right_float(void **state)` |
| `test_dump_layout_br_after_block_is_a_line` | function | `tests/test_freedom.c:4165` | `static void test_dump_layout_br_after_block_is_a_line(void **state)` |
| `test_dump_layout_deferred_float_column_shrinks_to_content` | function | `tests/test_freedom.c:2751` | `static void test_dump_layout_deferred_float_column_shrinks_to_content(void **state)` |
| `test_dump_layout_flex_auto_margin_push_right` | function | `tests/test_freedom.c:3601` | `static void test_dump_layout_flex_auto_margin_push_right(void **state)` |
| `test_dump_layout_flex_definite_height_centres_item` | function | `tests/test_freedom.c:4210` | `static void test_dump_layout_flex_definite_height_centres_item(void **state)` |
| `test_dump_layout_flex_item_contains_block_margins` | function | `tests/test_freedom.c:4185` | `static void test_dump_layout_flex_item_contains_block_margins(void **state)` |
| `test_dump_layout_flex_item_is_wrapper_around_nested_container` | function | `tests/test_freedom.c:3671` | `static void test_dump_layout_flex_item_is_wrapper_around_nested_container(void **state)` |
| `test_dump_layout_flex_item_negative_margin_widens_sibling` | function | `tests/test_freedom.c:3641` | `static void test_dump_layout_flex_item_negative_margin_widens_sibling(void **state)` |
| `test_dump_layout_flex_item_sibling_boxes` | function | `tests/test_freedom.c:2594` | `static void test_dump_layout_flex_item_sibling_boxes(void **state)` |
| `test_dump_layout_float_band_keeps_wrapper_width` | function | `tests/test_freedom.c:2790` | `static void test_dump_layout_float_band_keeps_wrapper_width(void **state)` |
| `test_dump_layout_float_pct_widths_resolve_once` | function | `tests/test_freedom.c:2873` | `static void test_dump_layout_float_pct_widths_resolve_once(void **state)` |
| `test_dump_layout_inline_abs_static_position_on_line` | function | `tests/test_freedom.c:2990` | `static void test_dump_layout_inline_abs_static_position_on_line(void **state)` |
| `test_dump_layout_inline_box_second_run_stays` | function | `tests/test_freedom.c:3463` | `static void test_dump_layout_inline_box_second_run_stays(void **state)` |
| `test_dump_layout_inline_input_shares_line` | function | `tests/test_freedom.c:4084` | `static void test_dump_layout_inline_input_shares_line(void **state)` |
| `test_dump_layout_line_opening_image_is_inline` | function | `tests/test_freedom.c:3535` | `static void test_dump_layout_line_opening_image_is_inline(void **state)` |
| `test_dump_layout_margin_before_container_in_wrapper` | function | `tests/test_freedom.c:2526` | `static void test_dump_layout_margin_before_container_in_wrapper(void **state)` |
| `test_dump_layout_nested_column_takes_max` | function | `tests/test_freedom.c:3704` | `static void test_dump_layout_nested_column_takes_max(void **state)` |
| `test_dump_layout_nested_padded_item_opens_once` | function | `tests/test_freedom.c:2829` | `static void test_dump_layout_nested_padded_item_opens_once(void **state)` |
| `test_dump_layout_oof_label_does_not_widen_nested_container` | function | `tests/test_freedom.c:4130` | `static void test_dump_layout_oof_label_does_not_widen_nested_container(void **state)` |
| `test_dump_layout_oof_subtree_real_layout` | function | `tests/test_freedom.c:2484` | `static void test_dump_layout_oof_subtree_real_layout(void **state)` |
| `test_dump_layout_pulled_rail_single_margin` | function | `tests/test_freedom.c:3295` | `static void test_dump_layout_pulled_rail_single_margin(void **state)` |
| `test_dump_layout_relative_offset_moves_content` | function | `tests/test_freedom.c:2973` | `static void test_dump_layout_relative_offset_moves_content(void **state)` |
| `test_dump_layout_root_box_survives_replaced_run` | function | `tests/test_freedom.c:3202` | `static void test_dump_layout_root_box_survives_replaced_run(void **state)` |
| `test_dump_layout_row_nested_in_column` | function | `tests/test_freedom.c:3412` | `static void test_dump_layout_row_nested_in_column(void **state)` |
| `test_dump_layout_shrink_pill_nested_container` | function | `tests/test_freedom.c:4047` | `static void test_dump_layout_shrink_pill_nested_container(void **state)` |
| `test_dump_layout_sticky_footer` | function | `tests/test_freedom.c:3167` | `static void test_dump_layout_sticky_footer(void **state)` |
| `test_dump_layout_two_auto_floats_shrink_to_fit` | function | `tests/test_freedom.c:2712` | `static void test_dump_layout_two_auto_floats_shrink_to_fit(void **state)` |
| `test_dump_layout_ua_margin_scales_with_font_size` | function | `tests/test_freedom.c:4271` | `static void test_dump_layout_ua_margin_scales_with_font_size(void **state)` |
| `test_dump_timings_prints_stages` | function | `tests/test_freedom.c:4017` | `static void test_dump_timings_prints_stages(void **state)` |
| `test_grid_item_nested_box_keeps_padding` | function | `tests/test_freedom.c:619` | `static void test_grid_item_nested_box_keeps_padding(void **state)` |
| `test_heading_colour_matches_body_text` | function | `tests/test_freedom.c:1272` | `static void test_heading_colour_matches_body_text(void **state)` |
| `test_headless_intersection_observer_reveals_visible_only` | function | `tests/test_freedom.c:190` | `static void test_headless_intersection_observer_reveals_visible_only(void **state)` |
| `test_headless_js_measures_real_geometry` | function | `tests/test_freedom.c:162` | `static void test_headless_js_measures_real_geometry(void **state)` |
| `test_headless_timer_navigation_followed` | function | `tests/test_freedom.c:219` | `static void test_headless_timer_navigation_followed(void **state)` |
| `test_help` | function | `tests/test_freedom.c:108` | `static void test_help(void **state)` |
| `test_inline_box_paints_padding_around_text` | function | `tests/test_freedom.c:794` | `static void test_inline_box_paints_padding_around_text(void **state)` |
| `test_inline_horizontal_padding_spaces_neighbours` | function | `tests/test_freedom.c:770` | `static void test_inline_horizontal_padding_spaces_neighbours(void **state)` |
| `test_inline_run_boundary_collapses_runs_of_space` | function | `tests/test_freedom.c:1589` | `static void test_inline_run_boundary_collapses_runs_of_space(void **state)` |
| `test_inline_run_boundary_does_not_invent_space` | function | `tests/test_freedom.c:1568` | `static void test_inline_run_boundary_does_not_invent_space(void **state)` |
| `test_line_height_leading_is_split_above_and_below` | function | `tests/test_freedom.c:688` | `static void test_line_height_leading_is_split_above_and_below(void **state)` |
| `test_local_form_renders_inputs` | function | `tests/test_freedom.c:242` | `static void test_local_form_renders_inputs(void **state)` |
| `test_local_html` | function | `tests/test_freedom.c:136` | `static void test_local_html(void **state)` |
| `test_missing_file` | function | `tests/test_freedom.c:268` | `static void test_missing_file(void **state)` |
| `test_no_args` | function | `tests/test_freedom.c:126` | `static void test_no_args(void **state)` |
| `test_no_dump_console_without_flag` | function | `tests/test_freedom.c:2357` | `static void test_no_dump_console_without_flag(void **state)` |
| `test_rejects_http_url` | function | `tests/test_freedom.c:3754` | `static void test_rejects_http_url(void **state)` |
| `test_version` | function | `tests/test_freedom.c:117` | `static void test_version(void **state)` |
| `wf_test_host_font` | function | `tests/test_freedom.c:1800` | `static uint8_t *wf_test_host_font(const char *name, size_t *out_n)` |
| `white` | function | `tests/test_freedom.c:3816` | `* and not white (the old behaviour where only text rows got background fills). */ static void tes...` |
| `main` | function | `tests/test_hls.c:219` | `int main(void)` |
| `test_empty_m3u8_is_ok` | function | `tests/test_hls.c:22` | `static void test_empty_m3u8_is_ok(void **state)` |
| `test_handles_windows_line_endings` | function | `tests/test_hls.c:209` | `static void test_handles_windows_line_endings(void **state)` |
| `test_multi_variant_collects_all` | function | `tests/test_hls.c:114` | `static void test_multi_variant_collects_all(void **state)` |
| `test_multiple_segments` | function | `tests/test_hls.c:46` | `static void test_multiple_segments(void **state)` |
| `test_not_m3u8_returns_parse_error` | function | `tests/test_hls.c:15` | `static void test_not_m3u8_returns_parse_error(void **state)` |
| `test_resolve_url_absolute_passthrough` | function | `tests/test_hls.c:180` | `static void test_resolve_url_absolute_passthrough(void **state)` |
| `test_resolve_url_deep_relative` | function | `tests/test_hls.c:200` | `static void test_resolve_url_deep_relative(void **state)` |
| `test_resolve_url_relative` | function | `tests/test_hls.c:190` | `static void test_resolve_url_relative(void **state)` |
| `test_select_variant_empty_returns_error` | function | `tests/test_hls.c:170` | `static void test_select_variant_empty_returns_error(void **state)` |
| `test_select_variant_highest_bandwidth_no_limit` | function | `tests/test_hls.c:135` | `static void test_select_variant_highest_bandwidth_no_limit(void **state)` |
| `test_select_variant_respects_max_dimensions` | function | `tests/test_hls.c:152` | `static void test_select_variant_respects_max_dimensions(void **state)` |
| `test_single_segment` | function | `tests/test_hls.c:31` | `static void test_single_segment(void **state)` |
| `test_target_duration_is_parsed` | function | `tests/test_hls.c:68` | `static void test_target_duration_is_parsed(void **state)` |
| `test_variant_playlist_collects_variants` | function | `tests/test_hls.c:97` | `static void test_variant_playlist_collects_variants(void **state)` |
| `test_variant_playlist_detected` | function | `tests/test_hls.c:83` | `static void test_variant_playlist_detected(void **state)` |
| `_DEFAULT_SOURCE` | macro | `tests/test_host_conf.c:6` | `#define _DEFAULT_SOURCE` |
| `main` | function | `tests/test_host_conf.c:101` | `int main(void)` |
| `make_dir` | function | `tests/test_host_conf.c:29` | `static void make_dir(char *buf, size_t cap)` |
| `test_allowlist_reads_named_file` | function | `tests/test_host_conf.c:70` | `static void test_allowlist_reads_named_file(void **state)` |
| `test_filter_is_cumulative_and_allow_wins` | function | `tests/test_host_conf.c:50` | `static void test_filter_is_cumulative_and_allow_wins(void **state)` |
| `test_missing_files_fail_open` | function | `tests/test_host_conf.c:88` | `static void test_missing_files_fail_open(void **state)` |
| `test_search_order_and_dedup` | function | `tests/test_host_conf.c:34` | `static void test_search_order_and_dedup(void **state)` |
| `write_file` | function | `tests/test_host_conf.c:20` | `static void write_file(const char *dir, const char *name, const char *text)` |
| `main` | function | `tests/test_hostblock.c:282` | `int main(void)` |
| `test_allow_wins_and_covers_subdomains` | function | `tests/test_hostblock.c:210` | `static void test_allow_wins_and_covers_subdomains(void **state)` |
| `test_bare_domain_per_line` | function | `tests/test_hostblock.c:73` | `static void test_bare_domain_per_line(void **state)` |
| `test_block_covers_subdomains` | function | `tests/test_hostblock.c:197` | `static void test_block_covers_subdomains(void **state)` |
| `test_check_fail_open_edges` | function | `tests/test_hostblock.c:252` | `static void test_check_fail_open_edges(void **state)` |
| `test_comments_and_blanks` | function | `tests/test_hostblock.c:83` | `static void test_comments_and_blanks(void **state)` |
| `test_count_null_set` | function | `tests/test_hostblock.c:37` | `static void test_count_null_set(void **state)` |
| `test_dedup_and_accumulate` | function | `tests/test_hostblock.c:174` | `static void test_dedup_and_accumulate(void **state)` |
| `test_free_null_idempotent` | function | `tests/test_hostblock.c:32` | `static void test_free_null_idempotent(void **state)` |
| `test_hosts_line_drops_ip` | function | `tests/test_hostblock.c:55` | `static void test_hosts_line_drops_ip(void **state)` |
| `test_invalid_tokens_skipped` | function | `tests/test_hostblock.c:139` | `static void test_invalid_tokens_skipped(void **state)` |
| `test_is_allowlisted` | function | `tests/test_hostblock.c:231` | `static void test_is_allowlisted(void **state)` |
| `test_lists_independent` | function | `tests/test_hostblock.c:185` | `static void test_lists_independent(void **state)` |
| `test_load_null_args` | function | `tests/test_hostblock.c:45` | `static void test_load_null_args(void **state)` |
| `test_lowercased` | function | `tests/test_hostblock.c:118` | `static void test_lowercased(void **state)` |
| `test_multiple_tokens_per_line` | function | `tests/test_hostblock.c:99` | `static void test_multiple_tokens_per_line(void **state)` |
| `test_no_lists_allows` | function | `tests/test_hostblock.c:224` | `static void test_no_lists_allows(void **state)` |
| `test_no_trailing_newline` | function | `tests/test_hostblock.c:107` | `static void test_no_trailing_newline(void **state)` |
| `test_oversize_token_skipped` | function | `tests/test_hostblock.c:155` | `static void test_oversize_token_skipped(void **state)` |
| `test_tld_entry_blocks_every_host_under_it` | function | `tests/test_hostblock.c:268` | `static void test_tld_entry_blocks_every_host_under_it(void **state)` |
| `test_trailing_dot_trimmed` | function | `tests/test_hostblock.c:128` | `static void test_trailing_dot_trimmed(void **state)` |
| `test_underscore_and_hyphen_valid` | function | `tests/test_hostblock.c:166` | `static void test_underscore_and_hyphen_valid(void **state)` |
| `test_various_ip_tokens_ignored` | function | `tests/test_hostblock.c:64` | `static void test_various_ip_tokens_ignored(void **state)` |
| `main` | function | `tests/test_hostedit.c:114` | `int main(void)` |
| `test_make_line_lowercases` | function | `tests/test_hostedit.c:11` | `static void test_make_line_lowercases(void **state)` |
| `test_make_line_null_and_range` | function | `tests/test_hostedit.c:47` | `static void test_make_line_null_and_range(void **state)` |
| `test_make_line_plain_host` | function | `tests/test_hostedit.c:18` | `static void test_make_line_plain_host(void **state)` |
| `test_make_line_rejects_bad_labels` | function | `tests/test_hostedit.c:36` | `static void test_make_line_rejects_bad_labels(void **state)` |
| `test_make_line_rejects_path_scheme_garbage` | function | `tests/test_hostedit.c:25` | `static void test_make_line_rejects_path_scheme_garbage(void **state)` |
| `test_make_line_single_label_ok` | function | `tests/test_hostedit.c:56` | `static void test_make_line_single_label_ok(void **state)` |
| `test_suggest_case_insensitive_and_dedup` | function | `tests/test_hostedit.c:92` | `static void test_suggest_case_insensitive_and_dedup(void **state)` |
| `test_suggest_empty_query_and_cap` | function | `tests/test_hostedit.c:101` | `static void test_suggest_empty_query_and_cap(void **state)` |
| `test_suggest_prefix_first` | function | `tests/test_hostedit.c:76` | `static void test_suggest_prefix_first(void **state)` |
| `test_text_has_host` | function | `tests/test_hostedit.c:63` | `static void test_text_has_host(void **state)` |
| `LIT` | macro | `tests/test_html_parse.c:21` | `#define LIT(s)` |
| `main` | function | `tests/test_html_parse.c:507` | `int main(void)` |
| `test_config_default_is_secure` | function | `tests/test_html_parse.c:37` | `static void test_config_default_is_secure(void **state)` |
| `test_event_handlers_kept_when_disabled` | function | `tests/test_html_parse.c:150` | `static void test_event_handlers_kept_when_disabled(void **state)` |
| `test_event_handlers_stripped_by_default` | function | `tests/test_html_parse.c:141` | `static void test_event_handlers_stripped_by_default(void **state)` |
| `test_extract_script_list_empty` | function | `tests/test_html_parse.c:263` | `static void test_extract_script_list_empty(void **state)` |
| `test_extract_script_list_external_semantics` | function | `tests/test_html_parse.c:200` | `static void test_extract_script_list_external_semantics(void **state)` |
| `test_extract_script_list_module_flags` | function | `tests/test_html_parse.c:454` | `static void test_extract_script_list_module_flags(void **state)` |
| `test_extract_script_list_skips_non_js_type` | function | `tests/test_html_parse.c:234` | `static void test_extract_script_list_skips_non_js_type(void **state)` |
| `test_extract_stylesheets_basic` | function | `tests/test_html_parse.c:310` | `static void test_extract_stylesheets_basic(void **state)` |
| `test_extract_stylesheets_caps` | function | `tests/test_html_parse.c:404` | `static void test_extract_stylesheets_caps(void **state)` |
| `test_extract_stylesheets_none_and_null` | function | `tests/test_html_parse.c:387` | `static void test_extract_stylesheets_none_and_null(void **state)` |
| `test_extract_stylesheets_rel_tokens` | function | `tests/test_html_parse.c:337` | `static void test_extract_stylesheets_rel_tokens(void **state)` |
| `test_free_null_and_double` | function | `tests/test_html_parse.c:443` | `static void test_free_null_and_double(void **state)` |
| `test_parse_malformed_does_not_crash` | function | `tests/test_html_parse.c:431` | `static void test_parse_malformed_does_not_crash(void **state)` |
| `test_parse_rejects_null_args` | function | `tests/test_html_parse.c:72` | `static void test_parse_rejects_null_args(void **state)` |
| `test_parse_rejects_oversize` | function | `tests/test_html_parse.c:80` | `static void test_parse_rejects_oversize(void **state)` |
| `test_parse_simple_document` | function | `tests/test_html_parse.c:91` | `static void test_parse_simple_document(void **state)` |
| `test_scripts_kept_when_disabled` | function | `tests/test_html_parse.c:131` | `static void test_scripts_kept_when_disabled(void **state)` |
| `test_scripts_stripped_by_default` | function | `tests/test_html_parse.c:116` | `static void test_scripts_stripped_by_default(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_html_parse.c:64` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_html_parse.c:51` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_html_parse.c:45` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_html_parse.c:57` | `static void test_validate_rejects_oversize(void **state)` |
| `NOW` | macro | `tests/test_http_cache.c:16` | `#define NOW` |
| `_GNU_SOURCE` | macro | `tests/test_http_cache.c:1` | `#define _GNU_SOURCE` |
| `count_files` | function | `tests/test_http_cache.c:105` | `static size_t count_files(const char *skip)` |
| `main` | function | `tests/test_http_cache.c:220` | `int main(void)` |
| `meta_of` | function | `tests/test_http_cache.c:18` | `static hc_meta meta_of(const char *cc, const char *etag, const char *lm, const char *date,       ...` |
| `setup` | function | `tests/test_http_cache.c:93` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_http_cache.c:98` | `static int teardown(void **state)` |
| `test_classify_fresh_revalidate_unusable` | function | `tests/test_http_cache.c:63` | `static void test_classify_fresh_revalidate_unusable(void **state)` |
| `test_clear_removes_every_entry` | function | `tests/test_http_cache.c:207` | `static void test_clear_removes_every_entry(void **state)` |
| `test_foreign_profile_key_empties_the_cache` | function | `tests/test_http_cache.c:175` | `static void test_foreign_profile_key_empties_the_cache(void **state)` |
| `test_http_date_parses_imf_fixdate` | function | `tests/test_http_cache.c:35` | `static void test_http_date_parses_imf_fixdate(void **state)` |
| `test_lifetime_rules_in_order` | function | `tests/test_http_cache.c:44` | `static void test_lifetime_rules_in_order(void **state)` |
| `test_partitions_do_not_share_entries` | function | `tests/test_http_cache.c:138` | `static void test_partitions_do_not_share_entries(void **state)` |
| `test_put_get_roundtrip_and_no_plaintext_on_disk` | function | `tests/test_http_cache.c:115` | `static void test_put_get_roundtrip_and_no_plaintext_on_disk(void **state)` |
| `test_redirect_memory_persists_and_expires` | function | `tests/test_http_cache.c:189` | `static void test_redirect_memory_persists_and_expires(void **state)` |
| `test_storable_rules` | function | `tests/test_http_cache.c:76` | `static void test_storable_rules(void **state)` |
| `test_tampered_entry_is_removed_and_misses` | function | `tests/test_http_cache.c:151` | `static void test_tampered_entry_is_removed_and_misses(void **state)` |
| `main` | function | `tests/test_identity.c:182` | `int main(void)` |
| `test_apply_query` | function | `tests/test_identity.c:127` | `static void test_apply_query(void **state)` |
| `test_defaults_are_the_anti_fp_identity` | function | `tests/test_identity.c:16` | `static void test_defaults_are_the_anti_fp_identity(void **state)` |
| `test_geo_validation` | function | `tests/test_identity.c:74` | `static void test_geo_validation(void **state)` |
| `test_languages_build_header_and_primary` | function | `tests/test_identity.c:52` | `static void test_languages_build_header_and_primary(void **state)` |
| `test_page_escapes_user_values_and_states_unavailable_apis` | function | `tests/test_identity.c:160` | `static void test_page_escapes_user_values_and_states_unavailable_apis(void **state)` |
| `test_parse_keeps_valid_fields_and_defaults_the_bad` | function | `tests/test_identity.c:113` | `static void test_parse_keeps_valid_fields_and_defaults_the_bad(void **state)` |
| `test_serialize_roundtrip_and_escaping` | function | `tests/test_identity.c:92` | `static void test_serialize_roundtrip_and_escaping(void **state)` |
| `test_user_agent_validation_is_fail_closed` | function | `tests/test_identity.c:31` | `static void test_user_agent_validation_is_fail_closed(void **state)` |
| `main` | function | `tests/test_image_decode.c:492` | `int main(void)` |
| `px` | function | `tests/test_image_decode.c:65` | `static uint32_t px(const img_pixels *p, uint32_t x, uint32_t y)` |
| `test_decode_dimensions_and_stride` | function | `tests/test_image_decode.c:166` | `static void test_decode_dimensions_and_stride(void **state)` |
| `test_decode_dispatch_rejects_unknown` | function | `tests/test_image_decode.c:279` | `static void test_decode_dispatch_rejects_unknown(void **state)` |
| `test_decode_dispatch_routes_gif` | function | `tests/test_image_decode.c:430` | `static void test_decode_dispatch_routes_gif(void **state)` |
| `test_decode_dispatch_routes_jpeg_and_png` | function | `tests/test_image_decode.c:267` | `static void test_decode_dispatch_routes_jpeg_and_png(void **state)` |
| `test_decode_dispatch_routes_webp` | function | `tests/test_image_decode.c:483` | `static void test_decode_dispatch_routes_webp(void **state)` |
| `test_decode_gif_animated_first_frame` | function | `tests/test_image_decode.c:405` | `static void test_decode_gif_animated_first_frame(void **state)` |
| `test_decode_gif_fail_closed` | function | `tests/test_image_decode.c:414` | `static void test_decode_gif_fail_closed(void **state)` |
| `test_decode_gif_interlaced` | function | `tests/test_image_decode.c:390` | `static void test_decode_gif_interlaced(void **state)` |
| `test_decode_gif_pixels` | function | `tests/test_image_decode.c:363` | `static void test_decode_gif_pixels(void **state)` |
| `test_decode_gif_transparency` | function | `tests/test_image_decode.c:378` | `static void test_decode_gif_transparency(void **state)` |
| `test_decode_jpeg_dimensions_and_alpha` | function | `tests/test_image_decode.c:244` | `static void test_decode_jpeg_dimensions_and_alpha(void **state)` |
| `test_decode_jpeg_null_args` | function | `tests/test_image_decode.c:302` | `static void test_decode_jpeg_null_args(void **state)` |
| `test_decode_jpeg_rejects_non_jpeg` | function | `tests/test_image_decode.c:295` | `static void test_decode_jpeg_rejects_non_jpeg(void **state)` |
| `test_decode_jpeg_rejects_truncated` | function | `tests/test_image_decode.c:287` | `static void test_decode_jpeg_rejects_truncated(void **state)` |
| `test_decode_null_args` | function | `tests/test_image_decode.c:210` | `static void test_decode_null_args(void **state)` |
| `test_decode_pixels_premultiplied` | function | `tests/test_image_decode.c:178` | `static void test_decode_pixels_premultiplied(void **state)` |
| `test_decode_rejects_non_png` | function | `tests/test_image_decode.c:190` | `static void test_decode_rejects_non_png(void **state)` |
| `test_decode_rejects_truncated` | function | `tests/test_image_decode.c:200` | `static void test_decode_rejects_truncated(void **state)` |
| `test_decode_webp_dimensions_and_pixels` | function | `tests/test_image_decode.c:454` | `static void test_decode_webp_dimensions_and_pixels(void **state)` |
| `test_decode_webp_fail_closed` | function | `tests/test_image_decode.c:471` | `static void test_decode_webp_fail_closed(void **state)` |
| `test_dimensions_from_ihdr` | function | `tests/test_image_decode.c:89` | `static void test_dimensions_from_ihdr(void **state)` |
| `test_dimensions_non_png` | function | `tests/test_image_decode.c:104` | `static void test_dimensions_non_png(void **state)` |
| `test_dimensions_null` | function | `tests/test_image_decode.c:111` | `static void test_dimensions_null(void **state)` |
| `test_dimensions_ok_bounds` | function | `tests/test_image_decode.c:120` | `static void test_dimensions_ok_bounds(void **state)` |
| `test_dimensions_truncated` | function | `tests/test_image_decode.c:97` | `static void test_dimensions_truncated(void **state)` |
| `test_fit_degenerate` | function | `tests/test_image_decode.c:154` | `static void test_fit_degenerate(void **state)` |
| `test_fit_landscape_into_square` | function | `tests/test_image_decode.c:136` | `static void test_fit_landscape_into_square(void **state)` |
| `test_fit_portrait_into_box` | function | `tests/test_image_decode.c:145` | `static void test_fit_portrait_into_box(void **state)` |
| `test_format_name` | function | `tests/test_image_decode.c:227` | `static void test_format_name(void **state)` |
| `test_pixels_free_idempotent` | function | `tests/test_image_decode.c:218` | `static void test_pixels_free_idempotent(void **state)` |
| `test_sniff_gif` | function | `tests/test_image_decode.c:356` | `static void test_sniff_gif(void **state)` |
| `test_sniff_jpeg` | function | `tests/test_image_decode.c:236` | `static void test_sniff_jpeg(void **state)` |
| `test_sniff_png` | function | `tests/test_image_decode.c:75` | `static void test_sniff_png(void **state)` |
| `test_sniff_unsupported` | function | `tests/test_image_decode.c:80` | `static void test_sniff_unsupported(void **state)` |
| `test_sniff_webp` | function | `tests/test_image_decode.c:448` | `static void test_sniff_webp(void **state)` |
| `DOC` | macro | `tests/test_import_map.c:36` | `#define DOC` |
| `expect_res` | function | `tests/test_import_map.c:38` | `static void expect_res(const im_map *m, const char *base, const char *spec, const char *want)` |
| `main` | function | `tests/test_import_map.c:123` | `int main(void)` |
| `test_exact_and_prefix_imports` | function | `tests/test_import_map.c:48` | `static void test_exact_and_prefix_imports(void **state)` |
| `test_invalid_input_yields_empty_map` | function | `tests/test_import_map.c:102` | `static void test_invalid_input_yields_empty_map(void **state)` |
| `test_json_escapes_and_ignored_members` | function | `tests/test_import_map.c:90` | `static void test_json_escapes_and_ignored_members(void **state)` |
| `test_scopes_win_by_longest_prefix` | function | `tests/test_import_map.c:74` | `static void test_scopes_win_by_longest_prefix(void **state)` |
| `tres` | function | `tests/test_import_map.c:17` | `static int tres(void *ctx, const char *base, const char *ref, char *out, size_t outsz)` |
| `assert_float_equal` | function | `tests/test_interp.c:64` | `assert_float_equal(ip_ease(0.0, &(ip_ease_fn)` |
| `assert_float_equal` | function | `tests/test_interp.c:66` | `assert_float_equal(ip_ease(0.0, &(ip_ease_fn)` |
| `linear_ease` | function | `tests/test_interp.c:258` | `static ip_ease_fn linear_ease(void)` |
| `main` | function | `tests/test_interp.c:474` | `int main(void)` |
| `test_anim_active_linear` | function | `tests/test_interp.c:292` | `static void test_anim_active_linear(void **state)` |
| `test_anim_alternate` | function | `tests/test_interp.c:393` | `static void test_anim_alternate(void **state)` |
| `test_anim_alternate_reverse` | function | `tests/test_interp.c:410` | `static void test_anim_alternate_reverse(void **state)` |
| `test_anim_delay_backwards_fill` | function | `tests/test_interp.c:278` | `static void test_anim_delay_backwards_fill(void **state)` |
| `test_anim_delay_no_fill` | function | `tests/test_interp.c:263` | `static void test_anim_delay_no_fill(void **state)` |
| `test_anim_forwards_fill` | function | `tests/test_interp.c:325` | `static void test_anim_forwards_fill(void **state)` |
| `test_anim_infinite` | function | `tests/test_interp.c:367` | `static void test_anim_infinite(void **state)` |
| `test_anim_negative_dt` | function | `tests/test_interp.c:448` | `static void test_anim_negative_dt(void **state)` |
| `test_anim_no_keyframes` | function | `tests/test_interp.c:436` | `static void test_anim_no_keyframes(void **state)` |
| `test_anim_null_init` | function | `tests/test_interp.c:463` | `static void test_anim_null_init(void **state)` |
| `test_anim_reverse_direction` | function | `tests/test_interp.c:380` | `static void test_anim_reverse_direction(void **state)` |
| `test_anim_single_iteration_done` | function | `tests/test_interp.c:310` | `static void test_anim_single_iteration_done(void **state)` |
| `test_anim_two_iterations` | function | `tests/test_interp.c:338` | `static void test_anim_two_iterations(void **state)` |
| `test_anim_zero_duration` | function | `tests/test_interp.c:423` | `static void test_anim_zero_duration(void **state)` |
| `test_ease_clamp` | function | `tests/test_interp.c:78` | `static void test_ease_clamp(void **state)` |
| `test_ease_ease_in_concave` | function | `tests/test_interp.c:92` | `static void test_ease_ease_in_concave(void **state)` |
| `test_ease_ease_out_convex` | function | `tests/test_interp.c:99` | `static void test_ease_ease_out_convex(void **state)` |
| `test_ease_endpoints` | function | `tests/test_interp.c:31` | `static void test_ease_endpoints(void **state)` |
| `test_ease_monotonic` | function | `tests/test_interp.c:106` | `static void test_ease_monotonic(void **state)` |
| `test_ease_null_fn` | function | `tests/test_interp.c:85` | `static void test_ease_null_fn(void **state)` |
| `test_ease_step_start_end_aliases` | function | `tests/test_interp.c:147` | `static void test_ease_step_start_end_aliases(void **state)` |
| `test_ease_steps_end` | function | `tests/test_interp.c:127` | `static void test_ease_steps_end(void **state)` |
| `test_ease_steps_start` | function | `tests/test_interp.c:138` | `static void test_ease_steps_start(void **state)` |
| `test_interp_dispatches` | function | `tests/test_interp.c:192` | `static void test_interp_dispatches(void **state)` |
| `test_kf_after_last` | function | `tests/test_interp.c:231` | `static void test_kf_after_last(void **state)` |
| `test_kf_before_first` | function | `tests/test_interp.c:225` | `static void test_kf_before_first(void **state)` |
| `test_kf_color_interp` | function | `tests/test_interp.c:247` | `static void test_kf_color_interp(void **state)` |
| `test_kf_exact_match` | function | `tests/test_interp.c:219` | `static void test_kf_exact_match(void **state)` |
| `test_kf_null_or_empty` | function | `tests/test_interp.c:237` | `static void test_kf_null_or_empty(void **state)` |
| `test_kf_three_keyframes` | function | `tests/test_interp.c:212` | `static void test_kf_three_keyframes(void **state)` |
| `test_kf_two_keyframes` | function | `tests/test_interp.c:205` | `static void test_kf_two_keyframes(void **state)` |
| `test_lerp_color_rgb` | function | `tests/test_interp.c:171` | `static void test_lerp_color_rgb(void **state)` |
| `test_lerp_scalar` | function | `tests/test_interp.c:163` | `static void test_lerp_scalar(void **state)` |
| `EXPECT` | macro | `tests/test_js_dom.c:78` | `#define EXPECT(f, src, expected)` |
| `EXPECT` | function | `tests/test_js_dom.c:271` | `EXPECT(f, "typeof (new MutationObserver(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:596` | `EXPECT(f, "['setText','appendChild','insertBefore','moveChildren','removeChild','setAttribute'," ...` |
| `EXPECT` | function | `tests/test_js_dom.c:896` | `EXPECT(f,         "setTimeout(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:1977` | `EXPECT(f, "globalThis.$=function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2141` | `EXPECT(f, "R[2].declarations.concat(R[3].declarations).map(function(x)` |
| `EXPECT` | function | `tests/test_js_dom.c:2228` | `EXPECT(f, "function onc()` |
| `EXPECT` | function | `tests/test_js_dom.c:2662` | `EXPECT(f, "['DocumentType','CDATASection','ProcessingInstruction','Window','NamedNodeMap',"      ...` |
| `EXPECT` | function | `tests/test_js_dom.c:2803` | `EXPECT(f, "function mk(h)` |
| `EXPECT` | function | `tests/test_js_dom.c:2868` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2883` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2887` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2891` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2903` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2914` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2918` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2921` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2929` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2940` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2942` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2954` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2964` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2975` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2984` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:2997` | `EXPECT(f, "(function()` |
| `EXPECT` | function | `tests/test_js_dom.c:3008` | `EXPECT(f, "(function()` |
| `assert_int_equal` | function | `tests/test_js_dom.c:885` | `assert_int_equal(run(f,         "window.onload=function()` |
| `bundle` | function | `tests/test_js_dom.c:653` | `* library bundle (DuckDuckGo's l.js "cannot read property createElement of  * undefined"). This l...` |
| `console_fixture` | function | `tests/test_js_dom.c:1079` | `static void console_fixture(hp_document **doc, dom_index **idx, js_context **ctx,                ...` |
| `console_teardown` | function | `tests/test_js_dom.c:1092` | `static void console_teardown(hp_document *doc, dom_index *idx, js_context *ctx,                  ...` |
| `fake_fetch` | function | `tests/test_js_dom.c:2754` | `static int fake_fetch(void *ctx, const char *method, const char *url, const char *body,          ...` |
| `fake_net` | struct | `tests/test_js_dom.c:2753` | `` |
| `fixture` | struct | `tests/test_js_dom.c:43` | `` |
| `geom_parent` | function | `tests/test_js_dom.c:1911` | `static dom_node_id geom_parent(void *ctx, dom_node_id n)` |
| `handle_after` | function | `tests/test_js_dom.c:1715` | `static dom_node_id handle_after(fixture *f, const char *src)` |
| `identity` | function | `tests/test_js_dom.c:620` | `* identity (the same one innerWidth and the CSS viewport units use);` |
| `it` | function | `tests/test_js_dom.c:792` | `* itself no longer finds it (getElementById only answers with attached elements). */ assert_string_equal(r.value...` |
| `jQuery` | function | `tests/test_js_dom.c:247` | `* page that ships jQuery (Slashdot). The fragment must be complete enough that the  * detection c...` |
| `js_handle` | function | `tests/test_js_dom.c:1915` | `static dom_node_id js_handle(fixture *f, const char *expr)` |
| `main` | function | `tests/test_js_dom.c:3248` | `int main(void)` |
| `methods` | function | `tests/test_js_dom.c:669` | `* backed by the sealed dom methods (this element's own attributes only). */ static void test_elem...` |
| `persisted` | function | `tests/test_js_dom.c:943` | `* never persisted (process-lifetime only). */ static void test_cookie_jar_enabled_for_trusted_hos...` |
| `pump_ticks` | function | `tests/test_js_dom.c:3018` | `static void pump_ticks(fixture *f, int n)` |
| `run` | function | `tests/test_js_dom.c:74` | `static js_status run(fixture *f, const char *src, js_result *r)` |
| `run_pane` | function | `tests/test_js_dom.c:2151` | `static void run_pane(fixture *f, int tab, const char *arg, js_result *r)` |
| `set_https_location` | function | `tests/test_js_dom.c:979` | `static void set_https_location(fixture *f, const char *url)` |
| `set_loc` | function | `tests/test_js_dom.c:2328` | `static void set_loc(fixture *f, const char *href)` |
| `setup` | function | `tests/test_js_dom.c:50` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_js_dom.c:61` | `static int teardown(void **state)` |
| `test_ambient_apis_do_not_throw` | function | `tests/test_js_dom.c:968` | `static void test_ambient_apis_do_not_throw(void **state)` |
| `test_append_cycle_is_rejected` | function | `tests/test_js_dom.c:873` | `static void test_append_cycle_is_rejected(void **state)` |
| `test_attributes` | function | `tests/test_js_dom.c:131` | `static void test_attributes(void **state)` |
| `test_attributes_are_iterable` | function | `tests/test_js_dom.c:434` | `static void test_attributes_are_iterable(void **state)` |
| `test_blur_onblur_fires` | function | `tests/test_js_dom.c:1346` | `static void test_blur_onblur_fires(void **state)` |
| `test_by_class_and_tag` | function | `tests/test_js_dom.c:113` | `static void test_by_class_and_tag(void **state)` |
| `test_ce_attribute_changed` | function | `tests/test_js_dom.c:2982` | `static void test_ce_attribute_changed(void **state)` |
| `test_ce_connected_callbacks` | function | `tests/test_js_dom.c:2973` | `static void test_ce_connected_callbacks(void **state)` |
| `test_ce_create_runs_constructor` | function | `tests/test_js_dom.c:2952` | `static void test_ce_create_runs_constructor(void **state)` |
| `test_ce_define_upgrades_existing` | function | `tests/test_js_dom.c:2962` | `static void test_ce_define_upgrades_existing(void **state)` |
| `test_ce_define_validation` | function | `tests/test_js_dom.c:3006` | `static void test_ce_define_validation(void **state)` |
| `test_ce_sync_on_mutation` | function | `tests/test_js_dom.c:2995` | `static void test_ce_sync_on_mutation(void **state)` |
| `test_classlist_backs_class_attr` | function | `tests/test_js_dom.c:223` | `static void test_classlist_backs_class_attr(void **state)` |
| `test_click_add_event_listener_fires` | function | `tests/test_js_dom.c:1563` | `static void test_click_add_event_listener_fires(void **state)` |
| `test_click_install_null_args` | function | `tests/test_js_dom.c:1557` | `static void test_click_install_null_args(void **state)` |
| `test_click_no_handler_allows_default` | function | `tests/test_js_dom.c:1634` | `static void test_click_no_handler_allows_default(void **state)` |
| `test_click_onclick_fires` | function | `tests/test_js_dom.c:1587` | `static void test_click_onclick_fires(void **state)` |
| `test_click_prevent_default` | function | `tests/test_js_dom.c:1611` | `static void test_click_prevent_default(void **state)` |
| `test_console_captures_levels` | function | `tests/test_js_dom.c:1118` | `static void test_console_captures_levels(void **state)` |
| `test_console_formats_errors_and_elements` | function | `tests/test_js_dom.c:1102` | `static void test_console_formats_errors_and_elements(void **state)` |
| `test_console_methods_are_writable` | function | `tests/test_js_dom.c:1169` | `static void test_console_methods_are_writable(void **state)` |
| `test_console_null_buffer_is_noop` | function | `tests/test_js_dom.c:1209` | `static void test_console_null_buffer_is_noop(void **state)` |
| `test_console_null_ctx` | function | `tests/test_js_dom.c:1230` | `static void test_console_null_ctx(void **state)` |
| `test_console_object_and_throwing_tostring` | function | `tests/test_js_dom.c:1145` | `static void test_console_object_and_throwing_tostring(void **state)` |
| `test_cookie_and_referrer_leak_nothing` | function | `tests/test_js_dom.c:929` | `static void test_cookie_and_referrer_leak_nothing(void **state)` |
| `test_create_append_renders_in_tree` | function | `tests/test_js_dom.c:807` | `static void test_create_append_renders_in_tree(void **state)` |
| `test_current_script_values_and_methods` | function | `tests/test_js_dom.c:2565` | `static void test_current_script_values_and_methods(void **state)` |
| `test_dataset_is_a_domstringmap` | function | `tests/test_js_dom.c:453` | `static void test_dataset_is_a_domstringmap(void **state)` |
| `test_document_fragment_reparents` | function | `tests/test_js_dom.c:233` | `static void test_document_fragment_reparents(void **state)` |
| `test_document_is_not_io` | function | `tests/test_js_dom.c:798` | `static void test_document_is_not_io(void **state)` |
| `test_document_order` | function | `tests/test_js_dom.c:138` | `static void test_document_order(void **state)` |
| `test_document_parentnode_surface` | function | `tests/test_js_dom.c:425` | `static void test_document_parentnode_surface(void **state)` |
| `test_document_shim_present` | function | `tests/test_js_dom.c:176` | `static void test_document_shim_present(void **state)` |
| `test_document_title_set_reflects_in_tree` | function | `tests/test_js_dom.c:756` | `static void test_document_title_set_reflects_in_tree(void **state)` |
| `test_dom_childnode_mixins` | function | `tests/test_js_dom.c:2531` | `static void test_dom_childnode_mixins(void **state)` |
| `test_dom_interface_prototypes` | function | `tests/test_js_dom.c:2543` | `static void test_dom_interface_prototypes(void **state)` |
| `test_dom_mutators_are_sealed_after_install` | function | `tests/test_js_dom.c:594` | `static void test_dom_mutators_are_sealed_after_install(void **state)` |
| `test_dom_ordered_insertion` | function | `tests/test_js_dom.c:2521` | `static void test_dom_ordered_insertion(void **state)` |
| `test_dom_template_content` | function | `tests/test_js_dom.c:2552` | `static void test_dom_template_content(void **state)` |
| `test_dynamic_inline_script_runs_once_on_insert` | function | `tests/test_js_dom.c:482` | `static void test_dynamic_inline_script_runs_once_on_insert(void **state)` |
| `test_dynamic_script_src_loads_async_and_reports_load_or_error` | function | `tests/test_js_dom.c:497` | `static void test_dynamic_script_src_loads_async_and_reports_load_or_error(void **state)` |
| `test_element_has_attribute` | function | `tests/test_js_dom.c:849` | `static void test_element_has_attribute(void **state)` |
| `test_element_local_name_namespace` | function | `tests/test_js_dom.c:461` | `static void test_element_local_name_namespace(void **state)` |
| `test_element_matches_closest_query_from_js` | function | `tests/test_js_dom.c:197` | `static void test_element_matches_closest_query_from_js(void **state)` |
| `test_element_members_survive_prototype_swaps_and_detached_calls` | function | `tests/test_js_dom.c:512` | `static void test_element_members_survive_prototype_swaps_and_detached_calls(void **state)` |
| `test_element_nodevalue_is_null` | function | `tests/test_js_dom.c:442` | `static void test_element_nodevalue_is_null(void **state)` |
| `test_element_remove_attribute` | function | `tests/test_js_dom.c:855` | `static void test_element_remove_attribute(void **state)` |
| `test_element_src_href_are_strings` | function | `tests/test_js_dom.c:865` | `static void test_element_src_href_are_strings(void **state)` |
| `test_element_traversal` | function | `tests/test_js_dom.c:214` | `static void test_element_traversal(void **state)` |
| `test_event_add_event_listener_fires` | function | `tests/test_js_dom.c:1239` | `static void test_event_add_event_listener_fires(void **state)` |
| `test_event_capture_target_bubble_order` | function | `tests/test_js_dom.c:1738` | `static void test_event_capture_target_bubble_order(void **state)` |
| `test_event_click_bubbles_to_ancestor` | function | `tests/test_js_dom.c:1726` | `static void test_event_click_bubbles_to_ancestor(void **state)` |
| `test_event_delegated_prevent_default` | function | `tests/test_js_dom.c:1816` | `static void test_event_delegated_prevent_default(void **state)` |
| `test_event_focus_does_not_bubble` | function | `tests/test_js_dom.c:1848` | `static void test_event_focus_does_not_bubble(void **state)` |
| `test_event_handle_event_object` | function | `tests/test_js_dom.c:1899` | `static void test_event_handle_event_object(void **state)` |
| `test_event_handler_property_slot` | function | `tests/test_js_dom.c:1860` | `static void test_event_handler_property_slot(void **state)` |
| `test_event_input_handler_fires_with_value` | function | `tests/test_js_dom.c:1275` | `static void test_event_input_handler_fires_with_value(void **state)` |
| `test_event_keydown_bubbles_with_data` | function | `tests/test_js_dom.c:1837` | `static void test_event_keydown_bubbles_with_data(void **state)` |
| `test_event_listener_exception_continues` | function | `tests/test_js_dom.c:1887` | `static void test_event_listener_exception_continues(void **state)` |
| `test_event_multiple_click_listeners` | function | `tests/test_js_dom.c:1777` | `static void test_event_multiple_click_listeners(void **state)` |
| `test_event_no_handler_allows_default` | function | `tests/test_js_dom.c:1310` | `static void test_event_no_handler_allows_default(void **state)` |
| `test_event_null_args` | function | `tests/test_js_dom.c:1317` | `static void test_event_null_args(void **state)` |
| `test_event_once` | function | `tests/test_js_dom.c:1804` | `static void test_event_once(void **state)` |
| `test_event_onkeydown_fires` | function | `tests/test_js_dom.c:1257` | `static void test_event_onkeydown_fires(void **state)` |
| `test_event_prevent_default_suppresses` | function | `tests/test_js_dom.c:1293` | `static void test_event_prevent_default_suppresses(void **state)` |
| `test_event_remove_listener` | function | `tests/test_js_dom.c:1790` | `static void test_event_remove_listener(void **state)` |
| `test_event_script_dispatch_custom_event` | function | `tests/test_js_dom.c:1874` | `static void test_event_script_dispatch_custom_event(void **state)` |
| `test_event_stop_immediate_propagation` | function | `tests/test_js_dom.c:1765` | `static void test_event_stop_immediate_propagation(void **state)` |
| `test_event_stop_propagation` | function | `tests/test_js_dom.c:1752` | `static void test_event_stop_propagation(void **state)` |
| `test_event_submit_bubbles_to_document` | function | `tests/test_js_dom.c:1826` | `static void test_event_submit_bubbles_to_document(void **state)` |
| `test_ext_blob_family` | function | `tests/test_js_dom.c:2677` | `static void test_ext_blob_family(void **state)` |
| `test_ext_compare_document_position` | function | `tests/test_js_dom.c:2589` | `static void test_ext_compare_document_position(void **state)` |
| `test_ext_document_helpers` | function | `tests/test_js_dom.c:2619` | `static void test_ext_document_helpers(void **state)` |
| `test_ext_insert_adjacent` | function | `tests/test_js_dom.c:2696` | `static void test_ext_insert_adjacent(void **state)` |
| `test_ext_is_equal_node` | function | `tests/test_js_dom.c:2801` | `static void test_ext_is_equal_node(void **state)` |
| `test_ext_prototype_delegation` | function | `tests/test_js_dom.c:2711` | `static void test_ext_prototype_delegation(void **state)` |
| `test_ext_shadow_root` | function | `tests/test_js_dom.c:2598` | `static void test_ext_shadow_root(void **state)` |
| `test_ext_tree_navigation` | function | `tests/test_js_dom.c:2578` | `static void test_ext_tree_navigation(void **state)` |
| `test_ext_tree_walker_terminates` | function | `tests/test_js_dom.c:2609` | `static void test_ext_tree_walker_terminates(void **state)` |
| `test_focus_add_event_listener_fires` | function | `tests/test_js_dom.c:1329` | `static void test_focus_add_event_listener_fires(void **state)` |
| `test_focus_blur_scroll_no_handler_allows_default` | function | `tests/test_js_dom.c:1423` | `static void test_focus_blur_scroll_no_handler_allows_default(void **state)` |
| `test_focus_blur_scroll_null_args` | function | `tests/test_js_dom.c:1431` | `static void test_focus_blur_scroll_null_args(void **state)` |
| `test_focus_blur_scroll_prevent_default` | function | `tests/test_js_dom.c:1395` | `static void test_focus_blur_scroll_prevent_default(void **state)` |
| `test_freebug_css_pane_lists_rules_computed_and_box` | function | `tests/test_js_dom.c:2175` | `static void test_freebug_css_pane_lists_rules_computed_and_box(void **state)` |
| `test_freebug_html_pane_outlines_the_dom` | function | `tests/test_js_dom.c:2158` | `static void test_freebug_html_pane_outlines_the_dom(void **state)` |
| `test_freebug_net_pane_empty_and_selector_is_data` | function | `tests/test_js_dom.c:2210` | `static void test_freebug_net_pane_empty_and_selector_is_data(void **state)` |
| `test_freebug_script_pane_lists_and_numbers_source` | function | `tests/test_js_dom.c:2193` | `static void test_freebug_script_pane_lists_and_numbers_source(void **state)` |
| `test_geolocation_fixed_coordinates` | function | `tests/test_js_dom.c:2071` | `static void test_geolocation_fixed_coordinates(void **state)` |
| `test_geom_absent_is_zero` | function | `tests/test_js_dom.c:1926` | `static void test_geom_absent_is_zero(void **state)` |
| `test_geom_installed_is_real` | function | `tests/test_js_dom.c:1933` | `static void test_geom_installed_is_real(void **state)` |
| `test_geom_null_ctx` | function | `tests/test_js_dom.c:2321` | `static void test_geom_null_ctx(void **state)` |
| `test_get_computed_style_inline` | function | `tests/test_js_dom.c:313` | `static void test_get_computed_style_inline(void **state)` |
| `test_get_element_by_id` | function | `tests/test_js_dom.c:100` | `static void test_get_element_by_id(void **state)` |
| `test_history_cross_origin_is_security_error` | function | `tests/test_js_dom.c:2354` | `static void test_history_cross_origin_is_security_error(void **state)` |
| `test_history_go_records_delta` | function | `tests/test_js_dom.c:2380` | `static void test_history_go_records_delta(void **state)` |
| `test_history_is_bounded` | function | `tests/test_js_dom.c:2390` | `static void test_history_is_bounded(void **state)` |
| `test_history_popstate_restores_entry` | function | `tests/test_js_dom.c:2365` | `static void test_history_popstate_restores_entry(void **state)` |
| `test_history_push_replace_update_location` | function | `tests/test_js_dom.c:2334` | `static void test_history_push_replace_update_location(void **state)` |
| `test_indexeddb_core` | function | `tests/test_js_dom.c:2044` | `static void test_indexeddb_core(void **state)` |
| `test_inner_html_builds_and_queryable` | function | `tests/test_js_dom.c:902` | `static void test_inner_html_builds_and_queryable(void **state)` |
| `test_inner_html_getter_serializes` | function | `tests/test_js_dom.c:912` | `static void test_inner_html_getter_serializes(void **state)` |
| `test_install_null_args` | function | `tests/test_js_dom.c:89` | `static void test_install_null_args(void **state)` |
| `test_interfaces_window_and_canvas` | function | `tests/test_js_dom.c:2660` | `static void test_interfaces_window_and_canvas(void **state)` |
| `test_intersection_observer_fires_synthetically` | function | `tests/test_js_dom.c:289` | `static void test_intersection_observer_fires_synthetically(void **state)` |
| `test_intl_stub_does_not_throw` | function | `tests/test_js_dom.c:688` | `static void test_intl_stub_does_not_throw(void **state)` |
| `test_intl_surface` | function | `tests/test_js_dom.c:2727` | `static void test_intl_surface(void **state)` |
| `test_invalid_handles` | function | `tests/test_js_dom.c:147` | `static void test_invalid_handles(void **state)` |
| `test_io_real_follows_scroll` | function | `tests/test_js_dom.c:2274` | `static void test_io_real_follows_scroll(void **state)` |
| `test_io_untrusted_stays_synthetic` | function | `tests/test_js_dom.c:2315` | `static void test_io_untrusted_stays_synthetic(void **state)` |
| `test_lifecycle_listeners_get_event` | function | `tests/test_js_dom.c:2741` | `static void test_lifecycle_listeners_get_event(void **state)` |
| `test_local_page_captures_nav` | function | `tests/test_js_dom.c:1057` | `static void test_local_page_captures_nav(void **state)` |
| `test_location_assign_and_window_last_wins` | function | `tests/test_js_dom.c:1036` | `static void test_location_assign_and_window_last_wins(void **state)` |
| `test_location_href_set_captures_raw` | function | `tests/test_js_dom.c:1010` | `static void test_location_href_set_captures_raw(void **state)` |
| `test_location_pathname_defaults_slash` | function | `tests/test_js_dom.c:1002` | `static void test_location_pathname_defaults_slash(void **state)` |
| `test_location_reads_real_components` | function | `tests/test_js_dom.c:985` | `static void test_location_reads_real_components(void **state)` |
| `test_location_replace_sets_replace_flag` | function | `tests/test_js_dom.c:1024` | `static void test_location_replace_sets_replace_flag(void **state)` |
| `test_methods_are_frozen` | function | `tests/test_js_dom.c:157` | `static void test_methods_are_frozen(void **state)` |
| `test_modern_globals_do_not_throw` | function | `tests/test_js_dom.c:266` | `static void test_modern_globals_do_not_throw(void **state)` |
| `test_mouse_add_event_listener_fires` | function | `tests/test_js_dom.c:1441` | `static void test_mouse_add_event_listener_fires(void **state)` |
| `test_mouse_mousemove_sees_coords` | function | `tests/test_js_dom.c:1474` | `static void test_mouse_mousemove_sees_coords(void **state)` |
| `test_mouse_multi_event_fires` | function | `tests/test_js_dom.c:1491` | `static void test_mouse_multi_event_fires(void **state)` |
| `test_mouse_no_handler_allows_default` | function | `tests/test_js_dom.c:1541` | `static void test_mouse_no_handler_allows_default(void **state)` |
| `test_mouse_null_args` | function | `tests/test_js_dom.c:1548` | `static void test_mouse_null_args(void **state)` |
| `test_mouse_onmouseout_fires` | function | `tests/test_js_dom.c:1458` | `static void test_mouse_onmouseout_fires(void **state)` |
| `test_mouse_prevent_default_suppresses` | function | `tests/test_js_dom.c:1525` | `static void test_mouse_prevent_default_suppresses(void **state)` |
| `test_mutation_observer_accepts_document_target` | function | `tests/test_js_dom.c:360` | `static void test_mutation_observer_accepts_document_target(void **state)` |
| `test_mutation_observer_reports_attributes` | function | `tests/test_js_dom.c:548` | `static void test_mutation_observer_reports_attributes(void **state)` |
| `test_mutation_observer_reports_child_list` | function | `tests/test_js_dom.c:337` | `static void test_mutation_observer_reports_child_list(void **state)` |
| `test_mutation_observer_subtree_character_data_and_take_records` | function | `tests/test_js_dom.c:564` | `static void test_mutation_observer_subtree_character_data_and_take_records(void **state)` |
| `test_navigation` | function | `tests/test_js_dom.c:121` | `static void test_navigation(void **state)` |
| `test_no_io_with_dom` | function | `tests/test_js_dom.c:168` | `static void test_no_io_with_dom(void **state)` |
| `test_no_nav_request_when_idle` | function | `tests/test_js_dom.c:1048` | `static void test_no_nav_request_when_idle(void **state)` |
| `test_node_count` | function | `tests/test_js_dom.c:108` | `static void test_node_count(void **state)` |
| `test_node_identity_is_cached` | function | `tests/test_js_dom.c:207` | `static void test_node_identity_is_cached(void **state)` |
| `test_onload_runs_and_mutates` | function | `tests/test_js_dom.c:881` | `static void test_onload_runs_and_mutates(void **state)` |
| `test_performance_observer_supported_entry_types` | function | `tests/test_js_dom.c:417` | `static void test_performance_observer_supported_entry_types(void **state)` |
| `test_platform_dommatrix_and_imagedata` | function | `tests/test_js_dom.c:2013` | `static void test_platform_dommatrix_and_imagedata(void **state)` |
| `test_platform_element_surface` | function | `tests/test_js_dom.c:2112` | `static void test_platform_element_surface(void **state)` |
| `test_platform_form_controls` | function | `tests/test_js_dom.c:2022` | `static void test_platform_form_controls(void **state)` |
| `test_platform_streams` | function | `tests/test_js_dom.c:2088` | `static void test_platform_streams(void **state)` |
| `test_query_selector_from_js` | function | `tests/test_js_dom.c:183` | `static void test_query_selector_from_js(void **state)` |
| `test_repl_api_inspect_and_event_listeners` | function | `tests/test_js_dom.c:2223` | `static void test_repl_api_inspect_and_event_listeners(void **state)` |
| `test_repl_api_is_repl_only_and_nondestructive` | function | `tests/test_js_dom.c:1974` | `static void test_repl_api_is_repl_only_and_nondestructive(void **state)` |

Next: [SYMBOLS_p14.md](SYMBOLS_p14.md)
