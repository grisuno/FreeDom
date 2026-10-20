# Symbols (page 10 of 14)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `wh_hub` | struct | `src/ws_hub.c:35` | `` |
| `wh_job` | struct | `src/ws_hub.c:43` | `` |
| `wh_new` | function | `src/ws_hub.c:116` | `wh_hub *wh_new(void)` |
| `wh_notify_fd` | function | `src/ws_hub.c:144` | `int wh_notify_fd(const wh_hub *h)` |
| `wh_on_notify` | function | `src/ws_hub.c:192` | `void wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx)` |
| `wh_on_readable` | function | `src/ws_hub.c:266` | `void wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx)` |
| `wh_open_async` | function | `src/ws_hub.c:148` | `int wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg)` |
| `wh_poll_fds` | function | `src/ws_hub.c:240` | `size_t wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap)` |
| `wh_send` | function | `src/ws_hub.c:221` | `int wh_send(wh_hub *h, int id, const void *data, size_t len, int binary)` |
| `ZM_LADDER_N` | macro | `src/zoom.c:12` | `#define ZM_LADDER_N` |
| `zm_apply` | function | `src/zoom.c:44` | `double zm_apply(double base_px, int pct)` |
| `zm_clamp` | function | `src/zoom.c:14` | `int zm_clamp(int pct)` |
| `zm_reset` | function | `src/zoom.c:36` | `int zm_reset(void)` |
| `zm_scale` | function | `src/zoom.c:40` | `double zm_scale(int pct)` |
| `zm_zoom_in` | function | `src/zoom.c:20` | `int zm_zoom_in(int pct)` |
| `zm_zoom_out` | function | `src/zoom.c:28` | `int zm_zoom_out(int pct)` |
| `CHECK` | macro | `tests/itest_secure_fetch.c:16` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/itest_secure_fetch.c:26` | `int main(void)` |
| `main` | function | `tests/test_anti_fp.c:197` | `int main(void)` |
| `test_boolean_props` | function | `tests/test_anti_fp.c:74` | `static void test_boolean_props(void **state)` |
| `test_bucket_screen` | function | `tests/test_anti_fp.c:83` | `static void test_bucket_screen(void **state)` |
| `test_coarsen_time` | function | `tests/test_anti_fp.c:18` | `static void test_coarsen_time(void **state)` |
| `test_identity_is_fixed` | function | `tests/test_anti_fp.c:34` | `static void test_identity_is_fixed(void **state)` |
| `test_legacy_identity_fixed` | function | `tests/test_anti_fp.c:61` | `static void test_legacy_identity_fixed(void **state)` |
| `test_origin_key_deterministic` | function | `tests/test_anti_fp.c:146` | `static void test_origin_key_deterministic(void **state)` |
| `test_origin_key_empty_namespace` | function | `tests/test_anti_fp.c:171` | `static void test_origin_key_empty_namespace(void **state)` |
| `test_origin_key_per_session` | function | `tests/test_anti_fp.c:165` | `static void test_origin_key_per_session(void **state)` |
| `test_origin_key_per_site` | function | `tests/test_anti_fp.c:153` | `static void test_origin_key_per_site(void **state)` |
| `test_origin_key_unlinks_readback` | function | `tests/test_anti_fp.c:183` | `static void test_origin_key_unlinks_readback(void **state)` |
| `test_perturb_bounded_lsb` | function | `tests/test_anti_fp.c:111` | `static void test_perturb_bounded_lsb(void **state)` |
| `test_perturb_deterministic` | function | `tests/test_anti_fp.c:101` | `static void test_perturb_deterministic(void **state)` |
| `test_perturb_key_sensitive` | function | `tests/test_anti_fp.c:126` | `static void test_perturb_key_sensitive(void **state)` |
| `test_perturb_safe_edges` | function | `tests/test_anti_fp.c:136` | `static void test_perturb_safe_edges(void **state)` |
| `dbl_eq` | function | `tests/test_block_flow.c:21` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_block_flow.c:105` | `int main(void)` |
| `test_collapse_n_edges` | function | `tests/test_block_flow.c:84` | `static void test_collapse_n_edges(void **state)` |
| `test_collapse_n_matches_binary` | function | `tests/test_block_flow.c:70` | `static void test_collapse_n_matches_binary(void **state)` |
| `test_margins_adjoin` | function | `tests/test_block_flow.c:95` | `static void test_margins_adjoin(void **state)` |
| `test_non_finite_is_absent` | function | `tests/test_block_flow.c:59` | `static void test_non_finite_is_absent(void **state)` |
| `test_two_negative_take_the_most_negative` | function | `tests/test_block_flow.c:50` | `static void test_two_negative_take_the_most_negative(void **state)` |
| `test_two_positive_collapse_to_max` | function | `tests/test_block_flow.c:29` | `static void test_two_positive_collapse_to_max(void **state)` |
| `main` | function | `tests/test_box_blur.c:78` | `int main(void)` |
| `mass` | function | `tests/test_box_blur.c:11` | `static long mass(const unsigned char *b, int n)` |
| `test_box_sizes` | function | `tests/test_box_blur.c:17` | `static void test_box_sizes(void **state)` |
| `test_impulse_conserves_mass_and_is_symmetric` | function | `tests/test_box_blur.c:34` | `static void test_impulse_conserves_mass_and_is_symmetric(void **state)` |
| `test_invalid_arguments` | function | `tests/test_box_blur.c:69` | `static void test_invalid_arguments(void **state)` |
| `test_uniform_interior_unchanged` | function | `tests/test_box_blur.c:58` | `static void test_uniform_interior_unchanged(void **state)` |
| `test_zero_sigma_is_identity` | function | `tests/test_box_blur.c:50` | `static void test_zero_sigma_is_identity(void **state)` |
| `assert_edges` | function | `tests/test_box_style.c:28` | `static void assert_edges(bx_edges e, double t, double r, double b, double l)` |
| `dbl_eq` | function | `tests/test_box_style.c:23` | `static int dbl_eq(double a, double b)` |
| `main` | function | `tests/test_box_style.c:712` | `int main(void)` |
| `percentage` | function | `tests/test_box_style.c:543` | `* percentage (a plain `width:50%` leaves the px half UNSET, a plain `width:300px`  * leaves the p...` |
| `test_block_ua_box_heading_level_wins` | function | `tests/test_box_style.c:206` | `static void test_block_ua_box_heading_level_wins(void **state)` |
| `test_block_ua_box_is_content_independent` | function | `tests/test_box_style.c:195` | `static void test_block_ua_box_is_content_independent(void **state)` |
| `test_block_ua_box_is_total` | function | `tests/test_box_style.c:228` | `static void test_block_ua_box_is_total(void **state)` |
| `test_block_ua_box_list_item_wins_over_ancestor` | function | `tests/test_box_style.c:219` | `static void test_block_ua_box_list_item_wins_over_ancestor(void **state)` |
| `test_blockquote` | function | `tests/test_box_style.c:77` | `static void test_blockquote(void **state)` |
| `test_body_has_no_margin` | function | `tests/test_box_style.c:35` | `static void test_body_has_no_margin(void **state)` |
| `test_border_box_height` | function | `tests/test_box_style.c:475` | `static void test_border_box_height(void **state)` |
| `test_border_span` | function | `tests/test_box_style.c:646` | `static void test_border_span(void **state)` |
| `test_case_insensitive` | function | `tests/test_box_style.c:111` | `static void test_case_insensitive(void **state)` |
| `test_content_clipped` | function | `tests/test_box_style.c:493` | `static void test_content_clipped(void **state)` |
| `test_definite_content_h` | function | `tests/test_box_style.c:688` | `static void test_definite_content_h(void **state)` |
| `test_display_name` | function | `tests/test_box_style.c:375` | `static void test_display_name(void **state)` |
| `test_display_none_for_non_rendered` | function | `tests/test_box_style.c:102` | `static void test_display_none_for_non_rendered(void **state)` |
| `test_div_is_block` | function | `tests/test_box_style.c:134` | `static void test_div_is_block(void **state)` |
| `test_flex_max_clamp` | function | `tests/test_box_style.c:611` | `static void test_flex_max_clamp(void **state)` |
| `test_flex_min_clamp` | function | `tests/test_box_style.c:659` | `static void test_flex_min_clamp(void **state)` |
| `test_heading_ladder` | function | `tests/test_box_style.c:50` | `static void test_heading_ladder(void **state)` |
| `test_hr` | function | `tests/test_box_style.c:84` | `static void test_hr(void **state)` |
| `test_inline_and_inline_block` | function | `tests/test_box_style.c:91` | `static void test_inline_and_inline_block(void **state)` |
| `test_line_height_px` | function | `tests/test_box_style.c:701` | `static void test_line_height_px(void **state)` |
| `test_lists` | function | `tests/test_box_style.c:66` | `static void test_lists(void **state)` |
| `test_paragraph` | function | `tests/test_box_style.c:43` | `static void test_paragraph(void **state)` |
| `test_parse_display_case_and_trim` | function | `tests/test_box_style.c:348` | `static void test_parse_display_case_and_trim(void **state)` |
| `test_parse_display_errors` | function | `tests/test_box_style.c:357` | `static void test_parse_display_errors(void **state)` |
| `test_parse_display_inline_aliases` | function | `tests/test_box_style.c:339` | `static void test_parse_display_inline_aliases(void **state)` |
| `test_parse_display_keywords` | function | `tests/test_box_style.c:320` | `static void test_parse_display_keywords(void **state)` |
| `test_pct_block_size` | function | `tests/test_box_style.c:672` | `static void test_pct_block_size(void **state)` |
| `test_place_centering` | function | `tests/test_box_style.c:408` | `static void test_place_centering(void **state)` |
| `test_place_declared_width_overflows` | function | `tests/test_box_style.c:627` | `static void test_place_declared_width_overflows(void **state)` |
| `test_place_failclosed_bounds` | function | `tests/test_box_style.c:432` | `static void test_place_failclosed_bounds(void **state)` |
| `test_place_insets` | function | `tests/test_box_style.c:420` | `static void test_place_insets(void **state)` |
| `test_place_max_width_caps` | function | `tests/test_box_style.c:397` | `static void test_place_max_width_caps(void **state)` |
| `test_place_no_box_is_identity` | function | `tests/test_box_style.c:390` | `static void test_place_no_box_is_identity(void **state)` |
| `test_table_role_from_tag` | function | `tests/test_box_style.c:243` | `static void test_table_role_from_tag(void **state)` |
| `test_table_role_is_total` | function | `tests/test_box_style.c:273` | `static void test_table_role_is_total(void **state)` |
| `test_ua_case_insensitive_and_trimmed` | function | `tests/test_box_style.c:283` | `static void test_ua_case_insensitive_and_trimmed(void **state)` |
| `test_ua_code_space_is_total` | function | `tests/test_box_style.c:309` | `static void test_ua_code_space_is_total(void **state)` |
| `test_ua_fails_closed` | function | `tests/test_box_style.c:291` | `static void test_ua_fails_closed(void **state)` |
| `test_ua_list_item_is_distinct_but_unspaced` | function | `tests/test_box_style.c:182` | `static void test_ua_list_item_is_distinct_but_unspaced(void **state)` |
| `test_ua_spaced_tags_round_trip` | function | `tests/test_box_style.c:162` | `static void test_ua_spaced_tags_round_trip(void **state)` |
| `test_ua_structural_wrappers_have_no_margin` | function | `tests/test_box_style.c:145` | `static void test_ua_structural_wrappers_have_no_margin(void **state)` |
| `test_unknown_and_null_are_neutral_inline` | function | `tests/test_box_style.c:119` | `static void test_unknown_and_null_are_neutral_inline(void **state)` |
| `test_width_cap2_is_min_of_two_values` | function | `tests/test_box_style.c:524` | `static void test_width_cap2_is_min_of_two_values(void **state)` |
| `test_width_cap_pct` | function | `tests/test_box_style.c:509` | `static void test_width_cap_pct(void **state)` |
| `width` | function | `tests/test_box_style.c:553` | `* a negative width (CSS Values 4 section 10.1: out-of-range calc() results are * clamped at used-value time). */...` |
| `UNSET4` | macro | `tests/test_box_tree.c:630` | `#define UNSET4` |
| `assert_rect` | function | `tests/test_box_tree.c:28` | `static void assert_rect(const bt_node *n, double x, double y, double w, double h)` |
| `card` | function | `tests/test_box_tree.c:769` | `* containing block climbs the unplaced card(1) → placed ancestor(0, x=100). */ assert_true(dbl_eq(out[2].x, 100));` |
| `dbox` | function | `tests/test_box_tree.c:1050` | `static pv_box_def dbox(int parent, int position, int z)` |
| `main` | function | `tests/test_box_tree.c:1157` | `int main(void)` |
| `test_abspos_resolves_against_placed_ancestor` | function | `tests/test_box_tree.c:744` | `static void test_abspos_resolves_against_placed_ancestor(void **state)` |
| `test_abspos_unplaced_without_anchor_falls_to_viewport` | function | `tests/test_box_tree.c:774` | `static void test_abspos_unplaced_without_anchor_falls_to_viewport(void **state)` |
| `test_block_stacking_with_collapse` | function | `tests/test_box_tree.c:62` | `static void test_block_stacking_with_collapse(void **state)` |
| `test_box_hidden_ancestor` | function | `tests/test_box_tree.c:806` | `static void test_box_hidden_ancestor(void **state)` |
| `test_box_hidden_fail_closed` | function | `tests/test_box_tree.c:819` | `static void test_box_hidden_fail_closed(void **state)` |
| `test_box_hidden_self` | function | `tests/test_box_tree.c:794` | `static void test_box_hidden_self(void **state)` |
| `test_children_cap` | function | `tests/test_box_tree.c:388` | `static void test_children_cap(void **state)` |
| `test_defer_fails_open` | function | `tests/test_box_tree.c:1143` | `static void test_defer_fails_open(void **state)` |
| `test_defer_outermost_root_and_negative_z` | function | `tests/test_box_tree.c:1103` | `static void test_defer_outermost_root_and_negative_z(void **state)` |
| `test_defer_relative_after_abs` | function | `tests/test_box_tree.c:1059` | `static void test_defer_relative_after_abs(void **state)` |
| `test_defer_relative_before_abs_is_not_deferred` | function | `tests/test_box_tree.c:1076` | `static void test_defer_relative_before_abs_is_not_deferred(void **state)` |
| `test_defer_respects_z_order` | function | `tests/test_box_tree.c:1088` | `static void test_defer_respects_z_order(void **state)` |
| `test_defer_uses_tree_order_not_index` | function | `tests/test_box_tree.c:1127` | `static void test_defer_uses_tree_order_not_index(void **state)` |
| `test_depth_cap` | function | `tests/test_box_tree.c:398` | `static void test_depth_cap(void **state)` |
| `test_display_none_skipped` | function | `tests/test_box_tree.c:353` | `static void test_display_none_skipped(void **state)` |
| `test_flex_auto_margin_pushes_item` | function | `tests/test_box_tree.c:95` | `static void test_flex_auto_margin_pushes_item(void **state)` |
| `test_flex_cross_axis_align` | function | `tests/test_box_tree.c:213` | `static void test_flex_cross_axis_align(void **state)` |
| `test_flex_gap_and_justify_center` | function | `tests/test_box_tree.c:113` | `static void test_flex_gap_and_justify_center(void **state)` |
| `test_flex_negative_gap` | function | `tests/test_box_tree.c:378` | `static void test_flex_negative_gap(void **state)` |
| `test_flex_nowrap_default_single_line_unchanged` | function | `tests/test_box_tree.c:151` | `static void test_flex_nowrap_default_single_line_unchanged(void **state)` |
| `test_flex_row_grow` | function | `tests/test_box_tree.c:75` | `static void test_flex_row_grow(void **state)` |
| `test_flex_single_line_definite_height` | function | `tests/test_box_tree.c:997` | `static void test_flex_single_line_definite_height(void **state)` |
| `test_flex_wrap_reverse_two_lines` | function | `tests/test_box_tree.c:171` | `static void test_flex_wrap_reverse_two_lines(void **state)` |
| `test_flex_wrap_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:193` | `static void test_flex_wrap_row_gap_distinct_from_gap(void **state)` |
| `test_flex_wrap_two_lines` | function | `tests/test_box_tree.c:129` | `static void test_flex_wrap_two_lines(void **state)` |
| `test_grid` | function | `tests/test_box_tree.c:270` | `static void test_grid(void **state)` |
| `test_grid_bad_columns` | function | `tests/test_box_tree.c:368` | `static void test_grid_bad_columns(void **state)` |
| `test_grid_column_span` | function | `tests/test_box_tree.c:309` | `static void test_grid_column_span(void **state)` |
| `test_grid_justify_self` | function | `tests/test_box_tree.c:1024` | `static void test_grid_justify_self(void **state)` |
| `test_grid_row_gap_distinct_from_gap` | function | `tests/test_box_tree.c:231` | `static void test_grid_row_gap_distinct_from_gap(void **state)` |
| `test_grid_row_tracks_definite_height` | function | `tests/test_box_tree.c:934` | `static void test_grid_row_tracks_definite_height(void **state)` |
| `test_grid_spanning_item_fits_tracked_rows` | function | `tests/test_box_tree.c:973` | `static void test_grid_spanning_item_fits_tracked_rows(void **state)` |
| `test_grid_weighted_tracks` | function | `tests/test_box_tree.c:291` | `static void test_grid_weighted_tracks(void **state)` |
| `test_grid_without_row_gap_falls_back_to_gap` | function | `tests/test_box_tree.c:254` | `static void test_grid_without_row_gap_falls_back_to_gap(void **state)` |
| `test_leaf` | function | `tests/test_box_tree.c:40` | `static void test_leaf(void **state)` |
| `test_leaf_with_padding` | function | `tests/test_box_tree.c:47` | `static void test_leaf_with_padding(void **state)` |
| `test_nested_flex_in_block` | function | `tests/test_box_tree.c:329` | `static void test_nested_flex_in_block(void **state)` |
| `test_null_root` | function | `tests/test_box_tree.c:35` | `static void test_null_root(void **state)` |
| `test_oof_anchor_none_on_static_chain` | function | `tests/test_box_tree.c:832` | `static void test_oof_anchor_none_on_static_chain(void **state)` |
| `test_oof_anchor_self` | function | `tests/test_box_tree.c:842` | `static void test_oof_anchor_self(void **state)` |
| `test_oof_anchor_via_ancestor` | function | `tests/test_box_tree.c:849` | `static void test_oof_anchor_via_ancestor(void **state)` |
| `test_oof_avail_stretch_and_shrink` | function | `tests/test_box_tree.c:913` | `static void test_oof_avail_stretch_and_shrink(void **state)` |
| `test_oof_fail_open` | function | `tests/test_box_tree.c:891` | `static void test_oof_fail_open(void **state)` |
| `test_oof_nested_absolute_anchor_vs_root` | function | `tests/test_box_tree.c:862` | `static void test_oof_nested_absolute_anchor_vs_root(void **state)` |
| `test_oof_relative_does_not_anchor` | function | `tests/test_box_tree.c:877` | `static void test_oof_relative_does_not_anchor(void **state)` |
| `test_positioning_absolute_against_ancestor` | function | `tests/test_box_tree.c:462` | `static void test_positioning_absolute_against_ancestor(void **state)` |
| `test_positioning_absolute_against_viewport` | function | `tests/test_box_tree.c:485` | `static void test_positioning_absolute_against_viewport(void **state)` |
| `test_positioning_doc_order_tiebreak` | function | `tests/test_box_tree.c:559` | `static void test_positioning_doc_order_tiebreak(void **state)` |
| `test_positioning_fixed_against_viewport` | function | `tests/test_box_tree.c:502` | `static void test_positioning_fixed_against_viewport(void **state)` |
| `test_positioning_nbox_cap` | function | `tests/test_box_tree.c:611` | `static void test_positioning_nbox_cap(void **state)` |
| `test_positioning_no_insets` | function | `tests/test_box_tree.c:577` | `static void test_positioning_no_insets(void **state)` |
| `test_positioning_null_args` | function | `tests/test_box_tree.c:415` | `static void test_positioning_null_args(void **state)` |
| `test_positioning_null_geometry` | function | `tests/test_box_tree.c:594` | `static void test_positioning_null_geometry(void **state)` |
| `test_positioning_relative_offset` | function | `tests/test_box_tree.c:441` | `static void test_positioning_relative_offset(void **state)` |
| `test_positioning_stacking_order` | function | `tests/test_box_tree.c:539` | `static void test_positioning_stacking_order(void **state)` |
| `test_positioning_static_unchanged` | function | `tests/test_box_tree.c:429` | `static void test_positioning_static_unchanged(void **state)` |
| `test_positioning_sticky_treated_as_relative` | function | `tests/test_box_tree.c:521` | `static void test_positioning_sticky_treated_as_relative(void **state)` |
| `test_static_position_absolute_auto_insets` | function | `tests/test_box_tree.c:633` | `static void test_static_position_absolute_auto_insets(void **state)` |
| `test_static_position_explicit_insets_win` | function | `tests/test_box_tree.c:665` | `static void test_static_position_explicit_insets_win(void **state)` |
| `test_static_position_fixed_auto_insets` | function | `tests/test_box_tree.c:649` | `static void test_static_position_fixed_auto_insets(void **state)` |
| `test_static_position_mixed_axis` | function | `tests/test_box_tree.c:686` | `static void test_static_position_mixed_axis(void **state)` |
| `test_static_position_null_arrays_legacy` | function | `tests/test_box_tree.c:726` | `static void test_static_position_null_arrays_legacy(void **state)` |
| `test_static_position_right_inset_keeps_anchor` | function | `tests/test_box_tree.c:706` | `static void test_static_position_right_inset_keeps_anchor(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_browser.c:8` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_browser.c:378` | `int main(void)` |
| `test_accepts_https_and_file` | function | `tests/test_browser.c:108` | `static void test_accepts_https_and_file(void **state)` |
| `test_back_forward_bounds` | function | `tests/test_browser.c:79` | `static void test_back_forward_bounds(void **state)` |
| `test_exceptions` | function | `tests/test_browser.c:252` | `static void test_exceptions(void **state)` |
| `test_init` | function | `tests/test_browser.c:20` | `static void test_init(void **state)` |
| `test_navigate_from_middle_discards_future` | function | `tests/test_browser.c:61` | `static void test_navigate_from_middle_discards_future(void **state)` |
| `test_navigate_history` | function | `tests/test_browser.c:31` | `static void test_navigate_history(void **state)` |
| `test_push_state_rejects_and_guards` | function | `tests/test_browser.c:361` | `static void test_push_state_rejects_and_guards(void **state)` |
| `test_push_state_same_document` | function | `tests/test_browser.c:328` | `static void test_push_state_same_document(void **state)` |
| `test_rejects_invalid_url` | function | `tests/test_browser.c:95` | `static void test_rejects_invalid_url(void **state)` |
| `test_set_page` | function | `tests/test_browser.c:196` | `static void test_set_page(void **state)` |
| `test_set_page_sanitizes_invalid_utf8` | function | `tests/test_browser.c:218` | `static void test_set_page_sanitizes_invalid_utf8(void **state)` |
| `test_status_toast` | function | `tests/test_browser.c:277` | `static void test_status_toast(void **state)` |
| `test_status_truncates` | function | `tests/test_browser.c:309` | `static void test_status_truncates(void **state)` |
| `test_url_bar_editing` | function | `tests/test_browser.c:122` | `static void test_url_bar_editing(void **state)` |
| `test_url_bar_selection` | function | `tests/test_browser.c:152` | `static void test_url_bar_selection(void **state)` |
| `main` | function | `tests/test_compositor.c:231` | `int main(void)` |
| `mk` | function | `tests/test_compositor.c:133` | `static cx_item mk(cx_layer layer, int z, int z_auto, size_t doc, size_t ref)` |
| `test_compare_layer_then_z_then_doc` | function | `tests/test_compositor.c:139` | `static void test_compare_layer_then_z_then_doc(void **state)` |
| `test_layer_float` | function | `tests/test_compositor.c:116` | `static void test_layer_float(void **state)` |
| `test_layer_inline_and_block` | function | `tests/test_compositor.c:123` | `static void test_layer_inline_and_block(void **state)` |
| `test_layer_negative_z` | function | `tests/test_compositor.c:86` | `static void test_layer_negative_z(void **state)` |
| `test_layer_positive_z` | function | `tests/test_compositor.c:93` | `static void test_layer_positive_z(void **state)` |
| `test_layer_zero_z_context` | function | `tests/test_compositor.c:100` | `static void test_layer_zero_z_context(void **state)` |
| `test_layer_zero_z_positioned_auto` | function | `tests/test_compositor.c:109` | `static void test_layer_zero_z_positioned_auto(void **state)` |
| `test_sc_fixed_sticky_always` | function | `tests/test_compositor.c:70` | `static void test_sc_fixed_sticky_always(void **state)` |
| `test_sc_isolation` | function | `tests/test_compositor.c:43` | `static void test_sc_isolation(void **state)` |
| `test_sc_mix_blend` | function | `tests/test_compositor.c:35` | `static void test_sc_mix_blend(void **state)` |
| `test_sc_opacity` | function | `tests/test_compositor.c:26` | `static void test_sc_opacity(void **state)` |
| `test_sc_positioned_z` | function | `tests/test_compositor.c:58` | `static void test_sc_positioned_z(void **state)` |
| `test_sc_static_none` | function | `tests/test_compositor.c:77` | `static void test_sc_static_none(void **state)` |
| `test_sc_transform` | function | `tests/test_compositor.c:51` | `static void test_sc_transform(void **state)` |
| `test_sort_full_paint_order` | function | `tests/test_compositor.c:160` | `static void test_sort_full_paint_order(void **state)` |
| `test_sort_matches_zindex_only_ordering` | function | `tests/test_compositor.c:218` | `static void test_sort_matches_zindex_only_ordering(void **state)` |
| `test_sort_noop_guards` | function | `tests/test_compositor.c:207` | `static void test_sort_noop_guards(void **state)` |
| `test_sort_stability` | function | `tests/test_compositor.c:193` | `static void test_sort_stability(void **state)` |
| `test_sort_z_within_layer` | function | `tests/test_compositor.c:177` | `static void test_sort_z_within_layer(void **state)` |
| `assert_int_equal` | function | `tests/test_css.c:1040` | `assert_int_equal(css_parse(         "@supports (display:grid)` |
| `assert_int_equal` | function | `tests/test_css.c:1054` | `assert_int_equal(css_parse(         "@supports (display:flex)` |
| `assert_int_equal` | function | `tests/test_css.c:1118` | `assert_int_equal(css_parse("@container (width>=10px)` |
| `assert_int_equal` | function | `tests/test_css.c:1701` | `assert_int_equal(css_parse("tr:nth-child(even)` |
| `assert_int_equal` | function | `tests/test_css.c:1724` | `assert_int_equal(css_parse("li:nth-last-child(2)` |
| `assert_int_equal` | function | `tests/test_css.c:1820` | `assert_int_equal(css_parse(".s:not(:focus)` |
| `assert_int_equal` | function | `tests/test_css.c:1848` | `assert_int_equal(css_parse("p:not(.x > y)` |
| `assert_int_equal` | function | `tests/test_css.c:2266` | `assert_int_equal(css_parse("li:nth-child()` |
| `assert_int_equal` | function | `tests/test_css.c:2301` | `assert_int_equal(css_parse("li:nth-of-type(2n)` |
| `assert_int_equal` | function | `tests/test_css.c:2333` | `assert_int_equal(css_parse("div:has(.x)` |
| `assert_int_equal` | function | `tests/test_css.c:2354` | `assert_int_equal(css_parse("html:lang(en)` |
| `assert_int_equal` | function | `tests/test_css.c:2710` | `assert_int_equal(css_parse(         "@media (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2725` | `assert_int_equal(css_parse(         "@media screen and (min-width: 600px)` |
| `assert_int_equal` | function | `tests/test_css.c:2741` | `assert_int_equal(css_parse(         "@media (frobnicate: 1)` |
| `assert_int_equal` | function | `tests/test_css.c:5348` | `assert_int_equal(css_resolve(sh, "div", NULL, (const char *[])` |
| `assert_int_equal` | function | `tests/test_css.c:5472` | `assert_int_equal(css_parse("@media (min-width: 200em)` |
| `assert_int_equal` | function | `tests/test_css.c:5478` | `assert_int_equal(css_parse("@media (min-width: 40em)` |
| `box` | function | `tests/test_css.c:234` | `* box (CSS 2.1 section 10.8.1). With one line box per line and no separate * parent content edge, they land on the...` |
| `cls_el` | function | `tests/test_css.c:1216` | `static css_element cls_el(const char *tag, const char *const *cl, size_t n,                      ...` |
| `color_for_class` | function | `tests/test_css.c:1139` | `static int color_for_class(const char *css, const char *cls)` |
| `downstream` | function | `tests/test_css.c:657` | `* and deciding whether to fetch happens downstream (render_doc.c) */ assert_string_equal(css_parse_inline(...` |
| `dropped` | function | `tests/test_css.c:512` | `* dropped (which kept a lower rule's, or the UA button face's, colour). */ static void test_backg...` |
| `el_attr_node` | function | `tests/test_css.c:1484` | `static css_element el_attr_node(const char *tag, const char *id,                                 ...` |
| `el_node` | function | `tests/test_css.c:1449` | `static css_element el_node(const char *tag, const char *id,                            const char...` |
| `el_sib_node` | function | `tests/test_css.c:1464` | `static css_element el_sib_node(const char *tag, int nth, int nsib,                               ...` |
| `el_type_node` | function | `tests/test_css.c:1473` | `static css_element el_type_node(const char *tag, int nth, int nsib,                              ...` |
| `geometry` | function | `tests/test_css.c:2993` | `* hostile sheet never sees real window geometry (anti-fingerprinting) yet 100vh  * heroes and cal...` |
| `grammar` | function | `tests/test_css.c:5513` | `* grammar (spec/css.md), so they parse instead of dropping. */ static void test_vendor_prefixes(v...` |
| `invalid` | function | `tests/test_css.c:759` | `* invalid (fail closed), not silently coerced into some default. */ css_style s = css_parse_inline("color...` |
| `main` | function | `tests/test_css.c:5630` | `int main(void)` |
| `root_is_dark_html` | function | `tests/test_css.c:963` | `static int root_is_dark_html(void *ctx, const css_sel *sel)` |
| `silent` | function | `tests/test_css.c:2607` | `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past  * the OLD cap...` |
| `terminator` | function | `tests/test_css.c:2008` | `* terminator (consumed, not painted);` |
| `test_adjacent_sibling_combinator` | function | `tests/test_css.c:1575` | `static void test_adjacent_sibling_combinator(void **state)` |
| `test_anim_keyframes_resolved_from_sheet` | function | `tests/test_css.c:5177` | `static void test_anim_keyframes_resolved_from_sheet(void **state)` |
| `test_anim_transform_keyframes_from_sheet` | function | `tests/test_css.c:5210` | `static void test_anim_transform_keyframes_from_sheet(void **state)` |
| `test_animation_none_resets` | function | `tests/test_css.c:3428` | `static void test_animation_none_resets(void **state)` |
| `test_animation_shorthand_basic` | function | `tests/test_css.c:3403` | `static void test_animation_shorthand_basic(void **state)` |
| `test_animation_shorthand_ignores_bezier` | function | `tests/test_css.c:3421` | `static void test_animation_shorthand_ignores_bezier(void **state)` |
| `test_animation_shorthand_order_free` | function | `tests/test_css.c:3412` | `static void test_animation_shorthand_order_free(void **state)` |
| `test_at_rules_skipped` | function | `tests/test_css.c:2655` | `static void test_at_rules_skipped(void **state)` |
| `test_attr_case_insensitive_flag` | function | `tests/test_css.c:2442` | `static void test_attr_case_insensitive_flag(void **state)` |
| `test_attr_equals` | function | `tests/test_css.c:2392` | `static void test_attr_equals(void **state)` |
| `test_attr_in_combinator` | function | `tests/test_css.c:2499` | `static void test_attr_in_combinator(void **state)` |
| `test_attr_malformed_fail_closed` | function | `tests/test_css.c:2515` | `static void test_attr_malformed_fail_closed(void **state)` |
| `test_attr_name_case_insensitive` | function | `tests/test_css.c:2457` | `static void test_attr_name_case_insensitive(void **state)` |
| `test_attr_operators` | function | `tests/test_css.c:2410` | `static void test_attr_operators(void **state)` |
| `test_attr_presence` | function | `tests/test_css.c:2379` | `static void test_attr_presence(void **state)` |
| `test_attr_quoted_value_with_space` | function | `tests/test_css.c:2468` | `static void test_attr_quoted_value_with_space(void **state)` |
| `test_attr_specificity_and_compound` | function | `tests/test_css.c:2482` | `static void test_attr_specificity_and_compound(void **state)` |
| `test_backdrop_filter_blur` | function | `tests/test_css.c:5137` | `static void test_backdrop_filter_blur(void **state)` |
| `test_background_clip_text` | function | `tests/test_css.c:5012` | `static void test_background_clip_text(void **state)` |
| `test_background_rgba_alpha` | function | `tests/test_css.c:4983` | `static void test_background_rgba_alpha(void **state)` |
| `test_background_shorthand_resets_gradient` | function | `tests/test_css.c:615` | `static void test_background_shorthand_resets_gradient(void **state)` |
| `test_bare_ms_box_sizing_drops` | function | `tests/test_css.c:3779` | `static void test_bare_ms_box_sizing_drops(void **state)` |
| `test_bg_image_url_absolute` | function | `tests/test_css.c:654` | `static void test_bg_image_url_absolute(void **state)` |
| `test_bg_image_url_basic` | function | `tests/test_css.c:636` | `static void test_bg_image_url_basic(void **state)` |
| `test_bg_image_url_gradient_mutually_exclusive` | function | `tests/test_css.c:690` | `static void test_bg_image_url_gradient_mutually_exclusive(void **state)` |
| `test_bg_image_url_none_and_junk_reset` | function | `tests/test_css.c:663` | `static void test_bg_image_url_none_and_junk_reset(void **state)` |
| `test_bg_image_url_overlong_fails_closed` | function | `tests/test_css.c:677` | `static void test_bg_image_url_overlong_fails_closed(void **state)` |
| `test_bg_image_url_quoted` | function | `tests/test_css.c:643` | `static void test_bg_image_url_quoted(void **state)` |
| `test_bg_position_center_by_identity` | function | `tests/test_css.c:3489` | `static void test_bg_position_center_by_identity(void **state)` |
| `test_bg_position_collision_drops` | function | `tests/test_css.c:3510` | `static void test_bg_position_collision_drops(void **state)` |
| `test_bg_position_edge_offset` | function | `tests/test_css.c:3477` | `static void test_bg_position_edge_offset(void **state)` |
| `test_bg_position_four_value` | function | `tests/test_css.c:3500` | `static void test_bg_position_four_value(void **state)` |
| `test_bg_shorthand_captures_url_and_resets_color` | function | `tests/test_css.c:698` | `static void test_bg_shorthand_captures_url_and_resets_color(void **state)` |
| `test_bg_size_and_repeat` | function | `tests/test_css.c:717` | `static void test_bg_size_and_repeat(void **state)` |
| `test_border_longhands` | function | `tests/test_css.c:3861` | `static void test_border_longhands(void **state)` |
| `test_border_shorthand` | function | `tests/test_css.c:3831` | `static void test_border_shorthand(void **state)` |
| `test_box_auto_and_centering` | function | `tests/test_css.c:2826` | `static void test_box_auto_and_centering(void **state)` |
| `test_box_clamp_anti_dos` | function | `tests/test_css.c:3083` | `static void test_box_clamp_anti_dos(void **state)` |
| `test_box_extension_sheet_cascade` | function | `tests/test_css.c:3133` | `static void test_box_extension_sheet_cascade(void **state)` |
| `test_box_orient_maps_to_flex_direction` | function | `tests/test_css.c:4009` | `static void test_box_orient_maps_to_flex_direction(void **state)` |
| `test_box_shadow_and_outline` | function | `tests/test_css.c:3887` | `static void test_box_shadow_and_outline(void **state)` |
| `test_box_shadow_layers_and_alpha` | function | `tests/test_css.c:5589` | `static void test_box_shadow_layers_and_alpha(void **state)` |
| `test_box_sheet_cascade_inline_wins` | function | `tests/test_css.c:3260` | `static void test_box_sheet_cascade_inline_wins(void **state)` |
| `test_box_shorthand_expansion` | function | `tests/test_css.c:2798` | `static void test_box_shorthand_expansion(void **state)` |
| `test_box_sizing` | function | `tests/test_css.c:3823` | `static void test_box_sizing(void **state)` |
| `test_box_units_and_failclosed` | function | `tests/test_css.c:2843` | `static void test_box_units_and_failclosed(void **state)` |
| `test_calc_basic_arithmetic` | function | `tests/test_css.c:2939` | `static void test_calc_basic_arithmetic(void **state)` |
| `test_calc_clamped_anti_dos` | function | `tests/test_css.c:2985` | `static void test_calc_clamped_anti_dos(void **state)` |
| `test_calc_dimension_errors_fail_closed` | function | `tests/test_css.c:2963` | `static void test_calc_dimension_errors_fail_closed(void **state)` |
| `test_calc_inside_shorthands` | function | `tests/test_css.c:3038` | `static void test_calc_inside_shorthands(void **state)` |
| `test_calc_precedence_and_parens` | function | `tests/test_css.c:2948` | `static void test_calc_precedence_and_parens(void **state)` |
| `test_calc_shape_mismatch_drops` | function | `tests/test_css.c:3771` | `static void test_calc_shape_mismatch_drops(void **state)` |
| `test_calc_units_and_signs` | function | `tests/test_css.c:2955` | `static void test_calc_units_and_signs(void **state)` |
| `test_calc_with_custom_property` | function | `tests/test_css.c:3076` | `static void test_calc_with_custom_property(void **state)` |
| `test_cascade_document_order` | function | `tests/test_css.c:2637` | `static void test_cascade_document_order(void **state)` |
| `test_cascade_inline_wins` | function | `tests/test_css.c:2646` | `static void test_cascade_inline_wins(void **state)` |
| `test_cascade_specificity` | function | `tests/test_css.c:2591` | `static void test_cascade_specificity(void **state)` |
| `test_child_combinator` | function | `tests/test_css.c:1528` | `static void test_child_combinator(void **state)` |
| `test_clip_auto` | function | `tests/test_css.c:5496` | `static void test_clip_auto(void **state)` |
| `test_clip_rect` | function | `tests/test_css.c:5486` | `static void test_clip_rect(void **state)` |
| `test_color_keeps_alpha` | function | `tests/test_css.c:1979` | `static void test_color_keeps_alpha(void **state)` |
| `test_combinator_class_chain` | function | `tests/test_css.c:1556` | `static void test_combinator_class_chain(void **state)` |
| `test_combinator_specificity_sum` | function | `tests/test_css.c:1541` | `static void test_combinator_specificity_sum(void **state)` |
| `test_component_var_cascade_order` | function | `tests/test_css.c:1337` | `static void test_component_var_cascade_order(void **state)` |
| `test_component_var_inherited_by_child` | function | `tests/test_css.c:1317` | `static void test_component_var_inherited_by_child(void **state)` |
| `test_component_var_inline_overrides` | function | `tests/test_css.c:1354` | `static void test_component_var_inline_overrides(void **state)` |
| `test_component_var_same_element` | function | `tests/test_css.c:1304` | `static void test_component_var_same_element(void **state)` |
| `test_conic_gradient_basic` | function | `tests/test_css.c:5032` | `static void test_conic_gradient_basic(void **state)` |
| `test_conic_gradient_deg_positions` | function | `tests/test_css.c:5073` | `static void test_conic_gradient_deg_positions(void **state)` |
| `test_conic_gradient_fails_closed` | function | `tests/test_css.c:5083` | `static void test_conic_gradient_fails_closed(void **state)` |
| `test_conic_gradient_from_angle` | function | `tests/test_css.c:5044` | `static void test_conic_gradient_from_angle(void **state)` |
| `test_conic_gradient_pie_hard_stop` | function | `tests/test_css.c:5058` | `static void test_conic_gradient_pie_hard_stop(void **state)` |
| `test_container_block_still_skipped` | function | `tests/test_css.c:1115` | `static void test_container_block_still_skipped(void **state)` |
| `test_container_cascade_inline_wins` | function | `tests/test_css.c:381` | `static void test_container_cascade_inline_wins(void **state)` |
| `test_container_fail_closed_and_bounds` | function | `tests/test_css.c:396` | `static void test_container_fail_closed_and_bounds(void **state)` |
| `test_container_unset` | function | `tests/test_css.c:489` | `static void test_container_unset(void **state)` |
| `test_cursor` | function | `tests/test_css.c:3370` | `static void test_cursor(void **state)` |
| `test_custom_prop_attr_scoped_skipped_without_matcher` | function | `tests/test_css.c:987` | `static void test_custom_prop_attr_scoped_skipped_without_matcher(void **state)` |
| `test_custom_prop_attr_scoped_via_root_matcher` | function | `tests/test_css.c:975` | `static void test_custom_prop_attr_scoped_via_root_matcher(void **state)` |
| `test_custom_prop_chain_eight_deep` | function | `tests/test_css.c:940` | `static void test_custom_prop_chain_eight_deep(void **state)` |
| `test_custom_prop_class_scoped_applies_with_root_scope` | function | `tests/test_css.c:845` | `static void test_custom_prop_class_scoped_applies_with_root_scope(void **state)` |
| `test_custom_prop_class_scoped_skipped_without_scope` | function | `tests/test_css.c:833` | `static void test_custom_prop_class_scoped_skipped_without_scope(void **state)` |
| `test_custom_prop_dark_media_collected_in_dark` | function | `tests/test_css.c:820` | `static void test_custom_prop_dark_media_collected_in_dark(void **state)` |
| `test_custom_prop_dark_media_not_collected_in_light` | function | `tests/test_css.c:805` | `static void test_custom_prop_dark_media_not_collected_in_light(void **state)` |
| `test_custom_prop_descendant_scoped_skipped` | function | `tests/test_css.c:858` | `static void test_custom_prop_descendant_scoped_skipped(void **state)` |
| `test_custom_prop_fanout_bounded` | function | `tests/test_css.c:948` | `static void test_custom_prop_fanout_bounded(void **state)` |
| `test_custom_prop_long_name_survives` | function | `tests/test_css.c:909` | `static void test_custom_prop_long_name_survives(void **state)` |
| `test_custom_prop_long_value_survives` | function | `tests/test_css.c:894` | `static void test_custom_prop_long_value_survives(void **state)` |
| `test_custom_prop_root_matcher_rejects_descendant` | function | `tests/test_css.c:998` | `static void test_custom_prop_root_matcher_rejects_descendant(void **state)` |
| `test_custom_prop_table_holds_hundreds` | function | `tests/test_css.c:870` | `static void test_custom_prop_table_holds_hundreds(void **state)` |
| `test_custom_prop_table_holds_thousands` | function | `tests/test_css.c:921` | `static void test_custom_prop_table_holds_thousands(void **state)` |
| `test_custom_prop_var_basic` | function | `tests/test_css.c:739` | `static void test_custom_prop_var_basic(void **state)` |
| `test_custom_prop_var_chain` | function | `tests/test_css.c:765` | `static void test_custom_prop_var_chain(void **state)` |
| `test_custom_prop_var_fallback_used_when_missing` | function | `tests/test_css.c:750` | `static void test_custom_prop_var_fallback_used_when_missing(void **state)` |
| `test_custom_prop_var_in_shorthand` | function | `tests/test_css.c:782` | `static void test_custom_prop_var_in_shorthand(void **state)` |
| `test_custom_prop_var_later_declaration_wins` | function | `tests/test_css.c:792` | `static void test_custom_prop_var_later_declaration_wins(void **state)` |
| `test_custom_prop_var_never_phones_home` | function | `tests/test_css.c:1391` | `static void test_custom_prop_var_never_phones_home(void **state)` |
| `test_custom_prop_var_no_fallback_drops_decl` | function | `tests/test_css.c:756` | `static void test_custom_prop_var_no_fallback_drops_decl(void **state)` |
| `test_custom_prop_var_self_reference_fails_closed` | function | `tests/test_css.c:773` | `static void test_custom_prop_var_self_reference_fails_closed(void **state)` |
| `test_custom_prop_var_unbalanced_paren_drops` | function | `tests/test_css.c:1378` | `static void test_custom_prop_var_unbalanced_paren_drops(void **state)` |
| `test_decl_split_ignores_semicolon_in_url_and_string` | function | `tests/test_css.c:1194` | `static void test_decl_split_ignores_semicolon_in_url_and_string(void **state)` |
| `test_descendant_combinator` | function | `tests/test_css.c:1512` | `static void test_descendant_combinator(void **state)` |
| `test_drops_retry_rewinds_buckets` | function | `tests/test_css.c:2099` | `static void test_drops_retry_rewinds_buckets(void **state)` |
| `test_filter_blur_and_grayscale` | function | `tests/test_css.c:5149` | `static void test_filter_blur_and_grayscale(void **state)` |
| `test_filter_drop_shadow` | function | `tests/test_css.c:5110` | `static void test_filter_drop_shadow(void **state)` |
| `test_filter_drop_shadow_defaults_and_failclosed` | function | `tests/test_css.c:5123` | `static void test_filter_drop_shadow_defaults_and_failclosed(void **state)` |
| `test_filter_none_and_default_argument` | function | `tests/test_css.c:3700` | `static void test_filter_none_and_default_argument(void **state)` |
| `test_flex_align` | function | `tests/test_css.c:3978` | `static void test_flex_align(void **state)` |
| `test_flex_item` | function | `tests/test_css.c:3934` | `static void test_flex_item(void **state)` |
| `test_float_and_clear` | function | `tests/test_css.c:3306` | `static void test_float_and_clear(void **state)` |
| `test_font_family` | function | `tests/test_css.c:143` | `static void test_font_family(void **state)` |
| `test_font_list_inline_and_fontface_first_name` | function | `tests/test_css.c:3642` | `static void test_font_list_inline_and_fontface_first_name(void **state)` |
| `test_font_list_normalized` | function | `tests/test_css.c:3624` | `static void test_font_list_normalized(void **state)` |
| `test_font_shorthand` | function | `tests/test_css.c:4953` | `static void test_font_shorthand(void **state)` |
| `test_font_size_math_functions` | function | `tests/test_css.c:3683` | `static void test_font_size_math_functions(void **state)` |
| `test_font_without_family_drops` | function | `tests/test_css.c:3785` | `static void test_font_without_family_drops(void **state)` |
| `test_fontface_case_insensitive` | function | `tests/test_css.c:3556` | `static void test_fontface_case_insensitive(void **state)` |
| `test_fontface_data_url_family_matches` | function | `tests/test_css.c:3579` | `static void test_fontface_data_url_family_matches(void **state)` |
| `test_fontface_icon_only_family` | function | `tests/test_css.c:3567` | `static void test_fontface_icon_only_family(void **state)` |
| `test_fontface_inline_has_no_sheet` | function | `tests/test_css.c:3601` | `static void test_fontface_inline_has_no_sheet(void **state)` |
| `test_fontface_later_rule_clears` | function | `tests/test_css.c:3609` | `static void test_fontface_later_rule_clears(void **state)` |
| `test_fontface_local_only_is_alias` | function | `tests/test_css.c:5553` | `static void test_fontface_local_only_is_alias(void **state)` |
| `test_fontface_local_then_url_keeps_url` | function | `tests/test_css.c:5571` | `static void test_fontface_local_then_url_keeps_url(void **state)` |
| `test_fontface_matches_sheet_face` | function | `tests/test_css.c:3533` | `static void test_fontface_matches_sheet_face(void **state)` |
| `test_fontface_no_match_is_zero` | function | `tests/test_css.c:3545` | `static void test_fontface_no_match_is_zero(void **state)` |
| `test_gap_two_value` | function | `tests/test_css.c:4936` | `static void test_gap_two_value(void **state)` |
| `test_general_sibling_combinator` | function | `tests/test_css.c:1590` | `static void test_general_sibling_combinator(void **state)` |
| `test_gradient_stop_alpha` | function | `tests/test_css.c:1252` | `static void test_gradient_stop_alpha(void **state)` |
| `test_grid_autofill_marker` | function | `tests/test_css.c:3520` | `static void test_grid_autofill_marker(void **state)` |
| `test_grid_extras` | function | `tests/test_css.c:4088` | `static void test_grid_extras(void **state)` |
| `test_grid_line_names_are_not_tracks` | function | `tests/test_css.c:4068` | `static void test_grid_line_names_are_not_tracks(void **state)` |
| `test_grid_minmax_counts_as_one_track` | function | `tests/test_css.c:467` | `static void test_grid_minmax_counts_as_one_track(void **state)` |
| `test_grid_repeat_clamped_anti_dos` | function | `tests/test_css.c:482` | `static void test_grid_repeat_clamped_anti_dos(void **state)` |
| `test_grid_repeat_expands_count` | function | `tests/test_css.c:456` | `static void test_grid_repeat_expands_count(void **state)` |
| `test_grid_repeat_malformed_fails_closed` | function | `tests/test_css.c:475` | `static void test_grid_repeat_malformed_fails_closed(void **state)` |
| `test_grid_template_rows_tracks` | function | `tests/test_css.c:5614` | `static void test_grid_template_rows_tracks(void **state)` |
| `test_has_parses_and_fails_closed` | function | `tests/test_css.c:2327` | `static void test_has_parses_and_fails_closed(void **state)` |
| `test_important_beats_specificity` | function | `tests/test_css.c:2543` | `static void test_important_beats_specificity(void **state)` |
| `test_important_in_shorthand` | function | `tests/test_css.c:2574` | `static void test_important_in_shorthand(void **state)` |
| `test_important_inline_beats_sheet_important` | function | `tests/test_css.c:2562` | `static void test_important_inline_beats_sheet_important(void **state)` |
| `test_important_inline_not_dropped` | function | `tests/test_css.c:2533` | `static void test_important_inline_not_dropped(void **state)` |
| `test_important_tier_then_normal_order` | function | `tests/test_css.c:2552` | `static void test_important_tier_then_normal_order(void **state)` |
| `test_inline_accent_color` | function | `tests/test_css.c:4426` | `static void test_inline_accent_color(void **state)` |
| `test_inline_appearance` | function | `tests/test_css.c:4297` | `static void test_inline_appearance(void **state)` |
| `test_inline_aspect_ratio` | function | `tests/test_css.c:3199` | `static void test_inline_aspect_ratio(void **state)` |
| `test_inline_backface_visibility` | function | `tests/test_css.c:4820` | `static void test_inline_backface_visibility(void **state)` |
| `test_inline_bg_clip_origin_attachment` | function | `tests/test_css.c:4355` | `static void test_inline_bg_clip_origin_attachment(void **state)` |
| `test_inline_bg_repeat` | function | `tests/test_css.c:4334` | `static void test_inline_bg_repeat(void **state)` |
| `test_inline_bg_size` | function | `tests/test_css.c:4346` | `static void test_inline_bg_size(void **state)` |
| `test_inline_border_collapse` | function | `tests/test_css.c:4210` | `static void test_inline_border_collapse(void **state)` |
| `test_inline_border_spacing` | function | `tests/test_css.c:4219` | `static void test_inline_border_spacing(void **state)` |
| `test_inline_box_longhands` | function | `tests/test_css.c:2780` | `static void test_inline_box_longhands(void **state)` |
| `test_inline_caption_side` | function | `tests/test_css.c:4239` | `static void test_inline_caption_side(void **state)` |
| `test_inline_caret_color` | function | `tests/test_css.c:4287` | `static void test_inline_caret_color(void **state)` |
| `test_inline_color_scheme` | function | `tests/test_css.c:4416` | `static void test_inline_color_scheme(void **state)` |
| `test_inline_contain` | function | `tests/test_css.c:4383` | `static void test_inline_contain(void **state)` |
| `test_inline_container_props` | function | `tests/test_css.c:333` | `static void test_inline_container_props(void **state)` |
| `test_inline_content_visibility` | function | `tests/test_css.c:4398` | `static void test_inline_content_visibility(void **state)` |
| `test_inline_direction` | function | `tests/test_css.c:3229` | `static void test_inline_direction(void **state)` |
| `test_inline_display` | function | `tests/test_css.c:295` | `static void test_inline_display(void **state)` |
| `test_inline_display_table_family` | function | `tests/test_css.c:308` | `static void test_inline_display_table_family(void **state)` |
| `test_inline_empty_cells` | function | `tests/test_css.c:4230` | `static void test_inline_empty_cells(void **state)` |
| `test_inline_font_kerning` | function | `tests/test_css.c:4747` | `static void test_inline_font_kerning(void **state)` |
| `test_inline_font_size` | function | `tests/test_css.c:45` | `static void test_inline_font_size(void **state)` |
| `test_inline_font_size_absolute_flag` | function | `tests/test_css.c:60` | `static void test_inline_font_size_absolute_flag(void **state)` |
| `test_inline_font_stretch` | function | `tests/test_css.c:4766` | `static void test_inline_font_stretch(void **state)` |
| `test_inline_font_variant` | function | `tests/test_css.c:4257` | `static void test_inline_font_variant(void **state)` |
| `test_inline_font_weight_style` | function | `tests/test_css.c:104` | `static void test_inline_font_weight_style(void **state)` |
| `test_inline_hyphens` | function | `tests/test_css.c:4266` | `static void test_inline_hyphens(void **state)` |
| `test_inline_image_rendering` | function | `tests/test_css.c:4407` | `static void test_inline_image_rendering(void **state)` |
| `test_inline_isolation` | function | `tests/test_css.c:4375` | `static void test_inline_isolation(void **state)` |
| `test_inline_line_height` | function | `tests/test_css.c:87` | `static void test_inline_line_height(void **state)` |
| `test_inline_list_style_pos` | function | `tests/test_css.c:4739` | `static void test_inline_list_style_pos(void **state)` |
| `test_inline_min_max_height` | function | `tests/test_css.c:3119` | `static void test_inline_min_max_height(void **state)` |
| `test_inline_min_width_height` | function | `tests/test_css.c:3092` | `static void test_inline_min_width_height(void **state)` |
| `test_inline_mix_blend_mode` | function | `tests/test_css.c:4449` | `static void test_inline_mix_blend_mode(void **state)` |
| `test_inline_object_fit` | function | `tests/test_css.c:4728` | `static void test_inline_object_fit(void **state)` |
| `test_inline_outline_longhands` | function | `tests/test_css.c:4179` | `static void test_inline_outline_longhands(void **state)` |
| `test_inline_outline_offset` | function | `tests/test_css.c:3238` | `static void test_inline_outline_offset(void **state)` |
| `test_inline_overscroll_behavior` | function | `tests/test_css.c:4811` | `static void test_inline_overscroll_behavior(void **state)` |
| `test_inline_pointer_events` | function | `tests/test_css.c:4308` | `static void test_inline_pointer_events(void **state)` |
| `test_inline_print_forced_adjust` | function | `tests/test_css.c:4435` | `static void test_inline_print_forced_adjust(void **state)` |
| `test_inline_resize` | function | `tests/test_css.c:4781` | `static void test_inline_resize(void **state)` |
| `test_inline_scroll_behavior` | function | `tests/test_css.c:4791` | `static void test_inline_scroll_behavior(void **state)` |
| `test_inline_tab_size` | function | `tests/test_css.c:3250` | `static void test_inline_tab_size(void **state)` |
| `test_inline_table_layout` | function | `tests/test_css.c:4248` | `static void test_inline_table_layout(void **state)` |
| `test_inline_text_align` | function | `tests/test_css.c:37` | `static void test_inline_text_align(void **state)` |
| `test_inline_text_decoration` | function | `tests/test_css.c:116` | `static void test_inline_text_decoration(void **state)` |
| `test_inline_text_decoration_color_style` | function | `tests/test_css.c:3153` | `static void test_inline_text_decoration_color_style(void **state)` |
| `test_inline_text_decoration_thickness` | function | `tests/test_css.c:3182` | `static void test_inline_text_decoration_thickness(void **state)` |
| `test_inline_text_rendering` | function | `tests/test_css.c:4756` | `static void test_inline_text_rendering(void **state)` |
| `test_inline_touch_action` | function | `tests/test_css.c:4799` | `static void test_inline_touch_action(void **state)` |
| `test_inline_transform_independent_cascade_combines` | function | `tests/test_css.c:4714` | `static void test_inline_transform_independent_cascade_combines(void **state)` |
| `test_inline_transform_rotate` | function | `tests/test_css.c:4563` | `static void test_inline_transform_rotate(void **state)` |
| `test_inline_transform_scale` | function | `tests/test_css.c:4523` | `static void test_inline_transform_scale(void **state)` |
| `test_inline_transform_skew` | function | `tests/test_css.c:4593` | `static void test_inline_transform_skew(void **state)` |
| `test_inline_transform_translate` | function | `tests/test_css.c:4472` | `static void test_inline_transform_translate(void **state)` |
| `test_inline_user_select` | function | `tests/test_css.c:4276` | `static void test_inline_user_select(void **state)` |
| `test_justify_self_parsed` | function | `tests/test_css.c:1991` | `static void test_justify_self_parsed(void **state)` |
| `test_keyframes_content_does_not_crash` | function | `tests/test_css.c:1124` | `static void test_keyframes_content_does_not_crash(void **state)` |
| `test_keyframes_overflow_skips_block_not_sheet` | function | `tests/test_css.c:5281` | `static void test_keyframes_overflow_skips_block_not_sheet(void **state)` |
| `test_layer_block_applies` | function | `tests/test_css.c:1061` | `static void test_layer_block_applies(void **state)` |
| `test_layer_important_reverses` | function | `tests/test_css.c:1096` | `static void test_layer_important_reverses(void **state)` |
| `test_layer_inline_still_wins` | function | `tests/test_css.c:1106` | `static void test_layer_inline_still_wins(void **state)` |
| `test_layer_order_statement` | function | `tests/test_css.c:1083` | `static void test_layer_order_statement(void **state)` |
| `test_layout_sheet_cascade_and_unset` | function | `tests/test_css.c:4143` | `static void test_layout_sheet_cascade_and_unset(void **state)` |
| `test_letter_word_spacing` | function | `tests/test_css.c:178` | `static void test_letter_word_spacing(void **state)` |
| `test_linear_gradient_basic` | function | `tests/test_css.c:537` | `static void test_linear_gradient_basic(void **state)` |
| `test_linear_gradient_directions` | function | `tests/test_css.c:548` | `static void test_linear_gradient_directions(void **state)` |
| `test_linear_gradient_fail_closed` | function | `tests/test_css.c:585` | `static void test_linear_gradient_fail_closed(void **state)` |
| `test_linear_gradient_positions_emitted` | function | `tests/test_css.c:5093` | `static void test_linear_gradient_positions_emitted(void **state)` |
| `test_linear_gradient_stops` | function | `tests/test_css.c:567` | `static void test_linear_gradient_stops(void **state)` |
| `test_list_style_type` | function | `tests/test_css.c:266` | `static void test_list_style_type(void **state)` |
| `test_logical_borders` | function | `tests/test_css.c:3714` | `static void test_logical_borders(void **state)` |
| `test_logical_inset_and_sizes` | function | `tests/test_css.c:4891` | `static void test_logical_inset_and_sizes(void **state)` |
| `test_logical_margin_padding` | function | `tests/test_css.c:4865` | `static void test_logical_margin_padding(void **state)` |
| `test_malformed_inline_no_crash` | function | `tests/test_css.c:731` | `static void test_malformed_inline_no_crash(void **state)` |
| `test_math_clamp` | function | `tests/test_css.c:4841` | `static void test_math_clamp(void **state)` |
| `test_math_min_max_top_level` | function | `tests/test_css.c:4829` | `static void test_math_min_max_top_level(void **state)` |
| `test_math_nested_in_calc` | function | `tests/test_css.c:4851` | `static void test_math_nested_in_calc(void **state)` |
| `test_media_and_or` | function | `tests/test_css.c:2722` | `static void test_media_and_or(void **state)` |
| `test_media_prefers_color_scheme` | function | `tests/test_css.c:2691` | `static void test_media_prefers_color_scheme(void **state)` |
| `test_media_query_length_honours_its_unit` | function | `tests/test_css.c:5465` | `static void test_media_query_length_honours_its_unit(void **state)` |
| `test_media_range_syntax_applies` | function | `tests/test_css.c:1014` | `static void test_media_range_syntax_applies(void **state)` |
| `test_media_screen_and_print` | function | `tests/test_css.c:2672` | `static void test_media_screen_and_print(void **state)` |
| `test_media_width_queries` | function | `tests/test_css.c:2707` | `static void test_media_width_queries(void **state)` |
| `test_not_unreadable_argument_fails_closed` | function | `tests/test_css.c:1845` | `static void test_not_unreadable_argument_fails_closed(void **state)` |
| `test_not_with_pseudo_class` | function | `tests/test_css.c:1817` | `static void test_not_with_pseudo_class(void **state)` |
| `test_opacity` | function | `tests/test_css.c:215` | `static void test_opacity(void **state)` |
| `test_overflow` | function | `tests/test_css.c:3347` | `static void test_overflow(void **state)` |
| `test_parse_null_args` | function | `tests/test_css.c:2756` | `static void test_parse_null_args(void **state)` |
| `test_place_shorthands` | function | `tests/test_css.c:4913` | `static void test_place_shorthands(void **state)` |
| `test_placeholder_pseudo_element` | function | `tests/test_css.c:3658` | `static void test_placeholder_pseudo_element(void **state)` |
| `test_position_and_insets` | function | `tests/test_css.c:3275` | `static void test_position_and_insets(void **state)` |
| `test_property_initial_value` | function | `tests/test_css.c:1364` | `static void test_property_initial_value(void **state)` |
| `test_pseudo_content_attr_fallback` | function | `tests/test_css.c:2082` | `static void test_pseudo_content_attr_fallback(void **state)` |
| `test_pseudo_content_attr_missing_is_empty` | function | `tests/test_css.c:2071` | `static void test_pseudo_content_attr_missing_is_empty(void **state)` |
| `test_pseudo_content_attr_resolves` | function | `tests/test_css.c:2060` | `static void test_pseudo_content_attr_resolves(void **state)` |
| `test_pseudo_content_before_after_separate` | function | `tests/test_css.c:1862` | `static void test_pseudo_content_before_after_separate(void **state)` |
| `test_pseudo_content_decodes_escaped_char` | function | `tests/test_css.c:1899` | `static void test_pseudo_content_decodes_escaped_char(void **state)` |
| `test_pseudo_content_decodes_hex_escape` | function | `tests/test_css.c:1876` | `static void test_pseudo_content_decodes_hex_escape(void **state)` |
| `test_pseudo_content_empty_without_pseudo` | function | `tests/test_css.c:2139` | `static void test_pseudo_content_empty_without_pseudo(void **state)` |
| `test_pseudo_content_escape_eats_terminator_space` | function | `tests/test_css.c:1888` | `static void test_pseudo_content_escape_eats_terminator_space(void **state)` |
| `test_pseudo_content_escapes_fail_closed` | function | `tests/test_css.c:2004` | `static void test_pseudo_content_escapes_fail_closed(void **state)` |
| `test_pseudo_content_none_parses_empty` | function | `tests/test_css.c:2035` | `static void test_pseudo_content_none_parses_empty(void **state)` |
| `test_pseudo_does_not_claim_cascade_slot` | function | `tests/test_css.c:2213` | `static void test_pseudo_does_not_claim_cascade_slot(void **state)` |
| `test_pseudo_element_style` | function | `tests/test_css.c:1267` | `static void test_pseudo_element_style(void **state)` |
| `test_pseudo_empty` | function | `tests/test_css.c:2314` | `static void test_pseudo_empty(void **state)` |
| `test_pseudo_geometry_does_not_leak_to_element` | function | `tests/test_css.c:2157` | `static void test_pseudo_geometry_does_not_leak_to_element(void **state)` |
| `test_pseudo_lang` | function | `tests/test_css.c:2351` | `static void test_pseudo_lang(void **state)` |
| `test_pseudo_link` | function | `tests/test_css.c:1622` | `static void test_pseudo_link(void **state)` |
| `test_pseudo_never_match_keeps_group` | function | `tests/test_css.c:1640` | `static void test_pseudo_never_match_keeps_group(void **state)` |
| `test_pseudo_nth_child` | function | `tests/test_css.c:1698` | `static void test_pseudo_nth_child(void **state)` |
| `test_pseudo_nth_last_child` | function | `tests/test_css.c:1721` | `static void test_pseudo_nth_last_child(void **state)` |
| `test_pseudo_nth_malformed_drops` | function | `tests/test_css.c:2261` | `static void test_pseudo_nth_malformed_drops(void **state)` |
| `test_pseudo_nth_of_type` | function | `tests/test_css.c:2298` | `static void test_pseudo_nth_of_type(void **state)` |
| `test_pseudo_of_type` | function | `tests/test_css.c:2279` | `static void test_pseudo_of_type(void **state)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
