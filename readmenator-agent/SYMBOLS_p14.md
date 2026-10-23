# Symbols (page 14 of 15)
Previous: [SYMBOLS_p13.md](SYMBOLS_p13.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `test_single_record` | function | `tests/test_perf_trace.c:28` | `static void test_single_record(void **state)` |
| `test_stage_name` | function | `tests/test_perf_trace.c:101` | `static void test_stage_name(void **state)` |
| `test_stage_out_of_range_is_noop` | function | `tests/test_perf_trace.c:72` | `static void test_stage_out_of_range_is_noop(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_prefetch.c:5` | `#define _POSIX_C_SOURCE` |
| `bare_fetch` | function | `tests/test_prefetch.c:333` | `static int bare_fetch(void *ctx, const char *method, const char *url,                       const...` |
| `barrier` | type_alias | `tests/test_prefetch.c:126` | `typedef struct fake_ctx { pthread_barrier_t barrier;` |
| `fake_ctx` | struct | `tests/test_prefetch.c:126` | `` |
| `fake_fetch` | function | `tests/test_prefetch.c:135` | `static int fake_fetch(void *vctx, const char *method, const char *url,                       cons...` |
| `graph_fetch` | function | `tests/test_prefetch.c:320` | `static int graph_fetch(void *ctx, const char *method, const char *url,                        con...` |
| `main` | function | `tests/test_prefetch.c:395` | `int main(void)` |
| `test_find_importmap` | function | `tests/test_prefetch.c:366` | `static void test_find_importmap(void **state)` |
| `test_pool_finish_unconsumed_and_empty` | function | `tests/test_prefetch.c:234` | `static void test_pool_finish_unconsumed_and_empty(void **state)` |
| `test_pool_follows_module_graph` | function | `tests/test_prefetch.c:346` | `static void test_pool_follows_module_graph(void **state)` |
| `test_pool_miss_consume_and_failure` | function | `tests/test_prefetch.c:191` | `static void test_pool_miss_consume_and_failure(void **state)` |
| `test_pool_parallel_fetch_and_take` | function | `tests/test_prefetch.c:153` | `static void test_pool_parallel_fetch_and_take(void **state)` |
| `test_pool_start_page_import_map` | function | `tests/test_prefetch.c:378` | `static void test_pool_start_page_import_map(void **state)` |
| `test_pooled_fetch_adapter` | function | `tests/test_prefetch.c:255` | `static void test_pooled_fetch_adapter(void **state)` |
| `test_scan_basic_stylesheet_and_script` | function | `tests/test_prefetch.c:32` | `static void test_scan_basic_stylesheet_and_script(void **state)` |
| `test_scan_imports_static_only` | function | `tests/test_prefetch.c:298` | `static void test_scan_imports_static_only(void **state)` |
| `test_scan_null_args` | function | `tests/test_prefetch.c:22` | `static void test_scan_null_args(void **state)` |
| `test_scan_ref_cap` | function | `tests/test_prefetch.c:104` | `static void test_scan_ref_cap(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_prefs.c:9` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_prefs.c:394` | `int main(void)` |
| `test_bookmark_toggle_and_cap` | function | `tests/test_prefs.c:237` | `static void test_bookmark_toggle_and_cap(void **state)` |
| `test_bookmarks_page_escapes` | function | `tests/test_prefs.c:345` | `static void test_bookmarks_page_escapes(void **state)` |
| `test_format_null_args` | function | `tests/test_prefs.c:382` | `static void test_format_null_args(void **state)` |
| `test_history_dedup_and_evict` | function | `tests/test_prefs.c:265` | `static void test_history_dedup_and_evict(void **state)` |
| `test_hostile_title_cleaned` | function | `tests/test_prefs.c:207` | `static void test_hostile_title_cleaned(void **state)` |
| `test_init_defaults` | function | `tests/test_prefs.c:25` | `static void test_init_defaults(void **state)` |
| `test_invalid_urls_rejected` | function | `tests/test_prefs.c:179` | `static void test_invalid_urls_rejected(void **state)` |
| `test_parse_bad_magic` | function | `tests/test_prefs.c:110` | `static void test_parse_bad_magic(void **state)` |
| `test_parse_clamps_out_of_range` | function | `tests/test_prefs.c:157` | `static void test_parse_clamps_out_of_range(void **state)` |
| `test_parse_too_large` | function | `tests/test_prefs.c:126` | `static void test_parse_too_large(void **state)` |
| `test_parse_unknown_and_malformed_skipped` | function | `tests/test_prefs.c:135` | `static void test_parse_unknown_and_malformed_skipped(void **state)` |
| `test_roundtrip` | function | `tests/test_prefs.c:50` | `static void test_roundtrip(void **state)` |
| `test_suggest_priorities` | function | `tests/test_prefs.c:290` | `static void test_suggest_priorities(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_profile.c:9` | `#define _GNU_SOURCE` |
| `dir` | type_alias | `tests/test_profile.c:27` | `typedef struct fixture { char dir[64];` |
| `file_size` | function | `tests/test_profile.c:64` | `static size_t file_size(const char *path)` |
| `fixture` | struct | `tests/test_profile.c:28` | `` |
| `main` | function | `tests/test_profile.c:278` | `int main(void)` |
| `path_of` | function | `tests/test_profile.c:60` | `static void path_of(const fixture *f, const char *name, char *out, size_t cap)` |
| `setup` | function | `tests/test_profile.c:30` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_profile.c:39` | `static int teardown(void **state)` |
| `test_first_launch_defaults` | function | `tests/test_profile.c:115` | `static void test_first_launch_defaults(void **state)` |
| `test_foreign_key_auth_fails` | function | `tests/test_profile.c:236` | `static void test_foreign_key_auth_fails(void **state)` |
| `test_nothing_readable_on_disk` | function | `tests/test_profile.c:174` | `static void test_nothing_readable_on_disk(void **state)` |
| `test_null_and_not_ready` | function | `tests/test_profile.c:261` | `static void test_null_and_not_ready(void **state)` |
| `test_open_bad_dir` | function | `tests/test_profile.c:103` | `static void test_open_bad_dir(void **state)` |
| `test_open_creates_keyfile` | function | `tests/test_profile.c:72` | `static void test_open_creates_keyfile(void **state)` |
| `test_open_rejects_corrupt_keyfile` | function | `tests/test_profile.c:89` | `static void test_open_rejects_corrupt_keyfile(void **state)` |
| `test_save_load_roundtrip_two_ctx` | function | `tests/test_profile.c:128` | `static void test_save_load_roundtrip_two_ctx(void **state)` |
| `test_tampered_blob_auth_fails` | function | `tests/test_profile.c:204` | `static void test_tampered_blob_auth_fails(void **state)` |
| `caps_images_on` | function | `tests/test_render_doc.c:28` | `static rdp_caps caps_images_on(void)` |
| `first_kind` | function | `tests/test_render_doc.c:35` | `static const rd_block *first_kind(const rd_doc *d, rd_kind k)` |
| `main` | function | `tests/test_render_doc.c:842` | `int main(void)` |
| `test_author_color_gated_by_css` | function | `tests/test_render_doc.c:372` | `static void test_author_color_gated_by_css(void **state)` |
| `test_block_tag_total` | function | `tests/test_render_doc.c:793` | `static void test_block_tag_total(void **state)` |
| `test_build_null_out` | function | `tests/test_render_doc.c:44` | `static void test_build_null_out(void **state)` |
| `test_build_null_view_is_empty` | function | `tests/test_render_doc.c:51` | `static void test_build_null_view_is_empty(void **state)` |
| `test_caret_color_gated_on_input` | function | `tests/test_render_doc.c:506` | `static void test_caret_color_gated_on_input(void **state)` |
| `test_cont_item_carried_by_default` | function | `tests/test_render_doc.c:628` | `static void test_cont_item_carried_by_default(void **state)` |
| `test_container_carried_by_default` | function | `tests/test_render_doc.c:596` | `static void test_container_carried_by_default(void **state)` |
| `test_emphasis_propagates` | function | `tests/test_render_doc.c:94` | `static void test_emphasis_propagates(void **state)` |
| `test_flex_item_carried_by_default` | function | `tests/test_render_doc.c:697` | `static void test_flex_item_carried_by_default(void **state)` |
| `test_flex_wrap_align_row_gap_carried_by_default` | function | `tests/test_render_doc.c:745` | `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)` |
| `test_float_carried_by_default` | function | `tests/test_render_doc.c:661` | `static void test_float_carried_by_default(void **state)` |
| `test_free_null_and_double` | function | `tests/test_render_doc.c:362` | `static void test_free_null_and_double(void **state)` |
| `test_heading_level_of_link` | function | `tests/test_render_doc.c:777` | `static void test_heading_level_of_link(void **state)` |
| `test_heading_paragraph_link` | function | `tests/test_render_doc.c:64` | `static void test_heading_paragraph_link(void **state)` |
| `test_href_sanitised` | function | `tests/test_render_doc.c:322` | `static void test_href_sanitised(void **state)` |
| `test_image_data_url_allowed_no_top` | function | `tests/test_render_doc.c:278` | `static void test_image_data_url_allowed_no_top(void **state)` |
| `test_image_data_url_allowed_remote_top` | function | `tests/test_render_doc.c:260` | `static void test_image_data_url_allowed_remote_top(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_doc.c:291` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_percent_encoded_blocked_invalid` | function | `tests/test_render_doc.c:306` | `static void test_image_data_url_percent_encoded_blocked_invalid(void **state)` |
| `test_image_label_total` | function | `tests/test_render_doc.c:349` | `static void test_image_label_total(void **state)` |
| `test_image_off_emits_notice_and_blocked` | function | `tests/test_render_doc.c:125` | `static void test_image_off_emits_notice_and_blocked(void **state)` |
| `test_image_on_allows_normal` | function | `tests/test_render_doc.c:164` | `static void test_image_on_allows_normal(void **state)` |
| `test_image_on_blocks_non_https` | function | `tests/test_render_doc.c:225` | `static void test_image_on_blocks_non_https(void **state)` |
| `test_image_on_blocks_tracker` | function | `tests/test_render_doc.c:212` | `static void test_image_on_blocks_tracker(void **state)` |
| `test_image_on_resolves_doc_relative_src` | function | `tests/test_render_doc.c:198` | `static void test_image_on_resolves_doc_relative_src(void **state)` |
| `test_image_on_resolves_relative_src` | function | `tests/test_render_doc.c:182` | `static void test_image_on_resolves_relative_src(void **state)` |
| `test_image_rendering_gated_on_image` | function | `tests/test_render_doc.c:477` | `static void test_image_rendering_gated_on_image(void **state)` |
| `test_input_label_total` | function | `tests/test_render_doc.c:571` | `static void test_input_label_total(void **state)` |
| `test_input_passthrough` | function | `tests/test_render_doc.c:536` | `static void test_input_passthrough(void **state)` |
| `test_kind_name_total` | function | `tests/test_render_doc.c:339` | `static void test_kind_name_total(void **state)` |
| `test_no_images_no_notice` | function | `tests/test_render_doc.c:150` | `static void test_no_images_no_notice(void **state)` |
| `test_node_id_carried_by_default` | function | `tests/test_render_doc.c:829` | `static void test_node_id_carried_by_default(void **state)` |
| `test_text_ext_2026_07_10_batch_gated_by_css` | function | `tests/test_render_doc.c:437` | `static void test_text_ext_2026_07_10_batch_gated_by_css(void **state)` |
| `test_text_overflow_word_break_gated_by_css` | function | `tests/test_render_doc.c:402` | `static void test_text_overflow_word_break_gated_by_css(void **state)` |
| `caps_images_on` | function | `tests/test_render_policy.c:90` | `static rdp_caps caps_images_on(void)` |
| `consulted` | function | `tests/test_render_policy.c:76` | `* is not even consulted (a bogus URL still yields BLOCK_DISABLED). */ assert_int_equal( rdp_image_decision(off...` |
| `main` | function | `tests/test_render_policy.c:241` | `int main(void)` |
| `test_caps_safe_is_all_off` | function | `tests/test_render_policy.c:18` | `static void test_caps_safe_is_all_off(void **state)` |
| `test_caps_zero_value_is_safe` | function | `tests/test_render_policy.c:26` | `static void test_caps_zero_value_is_safe(void **state)` |
| `test_image_allow_cross_site_when_enabled` | function | `tests/test_render_policy.c:108` | `static void test_image_allow_cross_site_when_enabled(void **state)` |
| `test_image_allow_data_url` | function | `tests/test_render_policy.c:164` | `static void test_image_allow_data_url(void **state)` |
| `test_image_allow_same_site` | function | `tests/test_render_policy.c:96` | `static void test_image_allow_same_site(void **state)` |
| `test_image_block_invalid` | function | `tests/test_render_policy.c:142` | `static void test_image_block_invalid(void **state)` |
| `test_image_block_scheme` | function | `tests/test_render_policy.c:134` | `static void test_image_block_scheme(void **state)` |
| `test_image_block_tracker` | function | `tests/test_render_policy.c:119` | `static void test_image_block_tracker(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_policy.c:183` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_malformed_is_invalid` | function | `tests/test_render_policy.c:191` | `static void test_image_data_url_malformed_is_invalid(void **state)` |
| `test_image_disabled_by_default` | function | `tests/test_render_policy.c:72` | `static void test_image_disabled_by_default(void **state)` |
| `test_image_disabled_precedence` | function | `tests/test_render_policy.c:207` | `static void test_image_disabled_precedence(void **state)` |
| `test_images_warning_present` | function | `tests/test_render_policy.c:232` | `static void test_images_warning_present(void **state)` |
| `test_img_reason_total_and_stable` | function | `tests/test_render_policy.c:217` | `static void test_img_reason_total_and_stable(void **state)` |
| `test_tracking_pixel_normal` | function | `tests/test_render_policy.c:52` | `static void test_tracking_pixel_normal(void **state)` |
| `test_tracking_pixel_tiny` | function | `tests/test_render_policy.c:37` | `static void test_tracking_pixel_tiny(void **state)` |
| `test_tracking_pixel_unknown` | function | `tests/test_render_policy.c:62` | `static void test_tracking_pixel_unknown(void **state)` |
| `test_tracking_pixel_zero_area` | function | `tests/test_render_policy.c:45` | `static void test_tracking_pixel_zero_area(void **state)` |
| `main` | function | `tests/test_renderer.c:93` | `int main(void)` |
| `test_render_basic` | function | `tests/test_renderer.c:27` | `static void test_render_basic(void **state)` |
| `test_render_binary_does_not_crash_parent` | function | `tests/test_renderer.c:63` | `static void test_render_binary_does_not_crash_parent(void **state)` |
| `test_render_multiple_independent` | function | `tests/test_renderer.c:74` | `static void test_render_multiple_independent(void **state)` |
| `test_render_null_args` | function | `tests/test_renderer.c:48` | `static void test_render_null_args(void **state)` |
| `test_render_strips_script` | function | `tests/test_renderer.c:39` | `static void test_render_strips_script(void **state)` |
| `test_render_too_large` | function | `tests/test_renderer.c:55` | `static void test_render_too_large(void **state)` |
| `test_result_free_null_and_double` | function | `tests/test_renderer.c:84` | `static void test_result_free_null_and_double(void **state)` |
| `main` | function | `tests/test_request_policy.c:139` | `int main(void)` |
| `test_evaluate_allow_same_site` | function | `tests/test_request_policy.c:105` | `static void test_evaluate_allow_same_site(void **state)` |
| `test_evaluate_block_invalid` | function | `tests/test_request_policy.c:128` | `static void test_evaluate_block_invalid(void **state)` |
| `test_evaluate_block_scheme` | function | `tests/test_request_policy.c:120` | `static void test_evaluate_block_scheme(void **state)` |
| `test_evaluate_block_third_party` | function | `tests/test_request_policy.c:112` | `static void test_evaluate_block_third_party(void **state)` |
| `test_host_of_basic` | function | `tests/test_request_policy.c:18` | `static void test_host_of_basic(void **state)` |
| `test_host_of_invalid` | function | `tests/test_request_policy.c:29` | `static void test_host_of_invalid(void **state)` |
| `test_host_of_overflow` | function | `tests/test_request_policy.c:37` | `static void test_host_of_overflow(void **state)` |
| `test_same_site` | function | `tests/test_request_policy.c:91` | `static void test_same_site(void **state)` |
| `test_site_of` | function | `tests/test_request_policy.c:45` | `static void test_site_of(void **state)` |
| `test_site_of_multi_suffix` | function | `tests/test_request_policy.c:58` | `static void test_site_of_multi_suffix(void **state)` |
| `test_site_of_psl` | function | `tests/test_request_policy.c:70` | `static void test_site_of_psl(void **state)` |
| `main` | function | `tests/test_secure_fetch.c:597` | `int main(void)` |
| `test_chain_hybrid_allows_classical` | function | `tests/test_secure_fetch.c:149` | `static void test_chain_hybrid_allows_classical(void **state)` |
| `test_chain_permissive_allows_weak_certs` | function | `tests/test_secure_fetch.c:166` | `static void test_chain_permissive_allows_weak_certs(void **state)` |
| `test_chain_rejects_null` | function | `tests/test_secure_fetch.c:187` | `static void test_chain_rejects_null(void **state)` |
| `test_chain_rejects_sha1_in_any_policy` | function | `tests/test_secure_fetch.c:157` | `static void test_chain_rejects_sha1_in_any_policy(void **state)` |
| `test_chain_rejects_weak_rsa` | function | `tests/test_secure_fetch.c:179` | `static void test_chain_rejects_weak_rsa(void **state)` |
| `test_chain_strict_accepts_pq` | function | `tests/test_secure_fetch.c:141` | `static void test_chain_strict_accepts_pq(void **state)` |
| `test_chain_strict_rejects_classical` | function | `tests/test_secure_fetch.c:132` | `static void test_chain_strict_rejects_classical(void **state)` |
| `test_config_blend_fields_default_null` | function | `tests/test_secure_fetch.c:34` | `static void test_config_blend_fields_default_null(void **state)` |
| `test_cookie_jar_put_and_header` | function | `tests/test_secure_fetch.c:551` | `static void test_cookie_jar_put_and_header(void **state)` |
| `test_cookie_line_matches_pure` | function | `tests/test_secure_fetch.c:515` | `static void test_cookie_line_matches_pure(void **state)` |
| `test_enforce_all_good_hybrid` | function | `tests/test_secure_fetch.c:201` | `static void test_enforce_all_good_hybrid(void **state)` |
| `test_enforce_allow_classical_ke` | function | `tests/test_secure_fetch.c:244` | `static void test_enforce_allow_classical_ke(void **state)` |
| `test_enforce_allowlisted_insecure` | function | `tests/test_secure_fetch.c:263` | `static void test_enforce_allowlisted_insecure(void **state)` |
| `test_enforce_checks_group_after_version` | function | `tests/test_secure_fetch.c:216` | `static void test_enforce_checks_group_after_version(void **state)` |
| `test_enforce_checks_version_first` | function | `tests/test_secure_fetch.c:207` | `static void test_enforce_checks_version_first(void **state)` |
| `test_enforce_fails_closed_on_null_chain` | function | `tests/test_secure_fetch.c:224` | `static void test_enforce_fails_closed_on_null_chain(void **state)` |
| `test_enforce_strict_requires_pq_chain` | function | `tests/test_secure_fetch.c:231` | `static void test_enforce_strict_requires_pq_chain(void **state)` |
| `test_fallback_ladder_is_shared_and_ordered` | function | `tests/test_secure_fetch.c:285` | `static void test_fallback_ladder_is_shared_and_ordered(void **state)` |
| `test_get_follow_null_args` | function | `tests/test_secure_fetch.c:471` | `static void test_get_follow_null_args(void **state)` |
| `test_get_null_args` | function | `tests/test_secure_fetch.c:480` | `static void test_get_null_args(void **state)` |
| `test_group_accepts_hybrid` | function | `tests/test_secure_fetch.c:123` | `static void test_group_accepts_hybrid(void **state)` |
| `test_group_rejects_classical` | function | `tests/test_secure_fetch.c:109` | `static void test_group_rejects_classical(void **state)` |
| `test_group_rejects_pure_pq` | function | `tests/test_secure_fetch.c:116` | `static void test_group_rejects_pure_pq(void **state)` |
| `test_location_is_case_insensitive_and_trims` | function | `tests/test_secure_fetch.c:348` | `static void test_location_is_case_insensitive_and_trims(void **state)` |
| `test_location_parses_value` | function | `tests/test_secure_fetch.c:340` | `static void test_location_parses_value(void **state)` |
| `test_location_rejects_non_location_and_empty` | function | `tests/test_secure_fetch.c:358` | `static void test_location_rejects_non_location_and_empty(void **state)` |
| `test_location_rejects_overflow` | function | `tests/test_secure_fetch.c:370` | `static void test_location_rejects_overflow(void **state)` |
| `test_post_null_args` | function | `tests/test_secure_fetch.c:489` | `static void test_post_null_args(void **state)` |
| `test_rcache_remembers_permanent_redirects` | function | `tests/test_secure_fetch.c:301` | `static void test_rcache_remembers_permanent_redirects(void **state)` |
| `test_redirect_code_recognizes_3xx` | function | `tests/test_secure_fetch.c:320` | `static void test_redirect_code_recognizes_3xx(void **state)` |
| `test_redirect_code_rejects_others` | function | `tests/test_secure_fetch.c:329` | `static void test_redirect_code_rejects_others(void **state)` |
| `test_resolve_absolute_https` | function | `tests/test_secure_fetch.c:379` | `static void test_resolve_absolute_https(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_secure_fetch.c:413` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_null_args` | function | `tests/test_secure_fetch.c:437` | `static void test_resolve_null_args(void **state)` |
| `test_resolve_refuses_dangerous_schemes` | function | `tests/test_secure_fetch.c:394` | `static void test_resolve_refuses_dangerous_schemes(void **state)` |
| `test_resolve_refuses_http_downgrade` | function | `tests/test_secure_fetch.c:387` | `static void test_resolve_refuses_http_downgrade(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_secure_fetch.c:425` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_secure_fetch.c:405` | `static void test_resolve_scheme_relative(void **state)` |
| `test_response_free_on_zeroed` | function | `tests/test_secure_fetch.c:448` | `static void test_response_free_on_zeroed(void **state)` |
| `test_response_free_releases_location` | function | `tests/test_secure_fetch.c:457` | `static void test_response_free_releases_location(void **state)` |
| `test_tls_accepts_13` | function | `tests/test_secure_fetch.c:102` | `static void test_tls_accepts_13(void **state)` |
| `test_tls_rejects_12` | function | `tests/test_secure_fetch.c:88` | `static void test_tls_rejects_12(void **state)` |
| `test_tls_rejects_older_and_garbage` | function | `tests/test_secure_fetch.c:93` | `static void test_tls_rejects_older_and_garbage(void **state)` |
| `test_url_accepts_https` | function | `tests/test_secure_fetch.c:80` | `static void test_url_accepts_https(void **state)` |
| `test_url_rejects_dangerous_schemes` | function | `tests/test_secure_fetch.c:70` | `static void test_url_rejects_dangerous_schemes(void **state)` |
| `test_url_rejects_null` | function | `tests/test_secure_fetch.c:60` | `static void test_url_rejects_null(void **state)` |
| `test_url_rejects_plain_http` | function | `tests/test_secure_fetch.c:65` | `static void test_url_rejects_plain_http(void **state)` |
| `test_user_agent_default_when_unset` | function | `tests/test_secure_fetch.c:46` | `static void test_user_agent_default_when_unset(void **state)` |
| `test_user_agent_uses_override` | function | `tests/test_secure_fetch.c:52` | `static void test_user_agent_uses_override(void **state)` |
| `test_ws_open_rejects_before_any_io` | function | `tests/test_secure_fetch.c:581` | `static void test_ws_open_rejects_before_any_io(void **state)` |
| `test_ws_url_check` | function | `tests/test_secure_fetch.c:569` | `static void test_ws_url_check(void **state)` |
| `main` | function | `tests/test_svg_render.c:344` | `int main(void)` |
| `parse` | function | `tests/test_svg_render.c:26` | `static sv_status parse(sv_image *im, const char *s)` |
| `test_basic_shapes` | function | `tests/test_svg_render.c:71` | `static void test_basic_shapes(void **state)` |
| `test_bounds_are_enforced` | function | `tests/test_svg_render.c:248` | `static void test_bounds_are_enforced(void **state)` |
| `test_dimensions_and_viewbox` | function | `tests/test_svg_render.c:50` | `static void test_dimensions_and_viewbox(void **state)` |
| `test_empty_and_garbage_do_not_parse` | function | `tests/test_svg_render.c:38` | `static void test_empty_and_garbage_do_not_parse(void **state)` |
| `test_fit_uniform_and_centered` | function | `tests/test_svg_render.c:320` | `static void test_fit_uniform_and_centered(void **state)` |
| `test_group_inheritance_and_transform` | function | `tests/test_svg_render.c:118` | `static void test_group_inheritance_and_transform(void **state)` |
| `test_malformed_values_degrade` | function | `tests/test_svg_render.c:285` | `static void test_malformed_values_degrade(void **state)` |
| `test_null_args` | function | `tests/test_svg_render.c:30` | `static void test_null_args(void **state)` |
| `test_paint_attributes` | function | `tests/test_svg_render.c:96` | `static void test_paint_attributes(void **state)` |
| `test_path_arc_compact_flags` | function | `tests/test_svg_render.c:208` | `static void test_path_arc_compact_flags(void **state)` |
| `test_path_arc_reaches_endpoint` | function | `tests/test_svg_render.c:192` | `static void test_path_arc_reaches_endpoint(void **state)` |
| `test_path_commands` | function | `tests/test_svg_render.c:159` | `static void test_path_commands(void **state)` |
| `test_polygon_points` | function | `tests/test_svg_render.c:140` | `static void test_polygon_points(void **state)` |
| `test_text_element` | function | `tests/test_svg_render.c:304` | `static void test_text_element(void **state)` |
| `test_url_bearing_elements_are_dropped` | function | `tests/test_svg_render.c:224` | `static void test_url_bearing_elements_are_dropped(void **state)` |
| `CSS_PAGE` | macro | `tests/test_tab.c:1816` | `#define CSS_PAGE(HREF)` |
| `EXT_PAGE` | macro | `tests/test_tab.c:1689` | `#define EXT_PAGE(SRC)` |
| `XHR_PAGE` | macro | `tests/test_tab.c:1594` | `#define XHR_PAGE(URL)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_tab.c:14` | `#define _POSIX_C_SOURCE` |
| `console_find` | function | `tests/test_tab.c:1233` | `static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle)` |
| `cs_eval` | function | `tests/test_tab.c:2079` | `static void cs_eval(tab *t, const char *js, char *out, size_t outsz)` |
| `cs_open` | function | `tests/test_tab.c:2087` | `static void cs_open(tab **t, int net)` |
| `document` | function | `tests/test_tab.c:1972` | `* listener is on document (the React/jQuery-delegation shape);` |
| `expect_eval` | function | `tests/test_tab.c:66` | `static void expect_eval(tab *t, const char *js, const char *expected)` |
| `fixture` | struct | `tests/test_tab.c:43` | `` |
| `geom_load_and_measure` | function | `tests/test_tab.c:2032` | `static int geom_load_and_measure(int net, char *out, size_t outsz)` |
| `load` | function | `tests/test_tab.c:2022` | `* table only for a trusted load (net granted: allow.conf AND js.conf);` |
| `load_js_page` | function | `tests/test_tab.c:2189` | `static void load_js_page(tab **out_t, const char *html, tab_page *p)` |
| `ls_load` | function | `tests/test_tab.c:2424` | `static void ls_load(int net, tab **t, tab_page *p)` |
| `main` | function | `tests/test_tab.c:3128` | `int main(int argc, char **argv)` |
| `module_page` | function | `tests/test_tab.c:2502` | `static const pv_run *module_page(int net, tab **t, tab_page *p, const char *needle)` |
| `n` | type_alias | `tests/test_tab.c:1853` | `typedef struct sink_cap { int n;` |
| `open_page` | function | `tests/test_tab.c:2317` | `static void open_page(int net, tab **t, tab_page *p)` |
| `paragraph` | function | `tests/test_tab.c:171` | `* reserved 200x280 box and the alt flowed as a paragraph (jkanime tiles). */ static void test_loa...` |
| `read` | function | `tests/test_tab.c:2667` | `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */ static void tes...` |
| `setup_loaded` | function | `tests/test_tab.c:45` | `static int setup_loaded(void **state)` |
| `sink_cap` | struct | `tests/test_tab.c:1853` | `` |
| `sink_capture` | function | `tests/test_tab.c:1855` | `static void sink_capture(void *ctx, const char *url,                          const char *body, s...` |
| `stub_css_fetch` | function | `tests/test_tab.c:1799` | `static int stub_css_fetch(void *ctx, const char *method, const char *url,                        ...` |
| `stub_fetch` | function | `tests/test_tab.c:1582` | `static int stub_fetch(void *ctx, const char *method, const char *url,                       const...` |
| `stub_module_fetch` | function | `tests/test_tab.c:2472` | `static int stub_module_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `stub_script_fetch` | function | `tests/test_tab.c:1665` | `static int stub_script_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `teardown` | function | `tests/test_tab.c:56` | `static int teardown(void **state)` |
| `test_binary_does_not_crash_parent` | function | `tests/test_tab.c:2745` | `static void test_binary_does_not_crash_parent(void **state)` |
| `test_boxdef_node_id_crosses_codec` | function | `tests/test_tab.c:2003` | `static void test_boxdef_node_id_crosses_codec(void **state)` |
| `test_child_death_survived` | function | `tests/test_tab.c:2760` | `static void test_child_death_survived(void **state)` |
| `test_click_bubbles_to_delegated_document_listener` | function | `tests/test_tab.c:1975` | `static void test_click_bubbles_to_delegated_document_listener(void **state)` |
| `test_click_handler_navigation_reaches_parent` | function | `tests/test_tab.c:2195` | `static void test_click_handler_navigation_reaches_parent(void **state)` |
| `test_click_runs_handler_and_returns_view` | function | `tests/test_tab.c:587` | `static void test_click_runs_handler_and_returns_view(void **state)` |
| `test_computed_style_follows_dom_mutation` | function | `tests/test_tab.c:2114` | `static void test_computed_style_follows_dom_mutation(void **state)` |
| `test_computed_style_is_inline_only_for_untrusted_host` | function | `tests/test_tab.c:2133` | `static void test_computed_style_is_inline_only_for_untrusted_host(void **state)` |
| `test_computed_style_reads_the_cascade_for_trusted_host` | function | `tests/test_tab.c:2095` | `static void test_computed_style_reads_the_cascade_for_trusted_host(void **state)` |
| `test_css_sink_ignores_non_css_body` | function | `tests/test_tab.c:1896` | `static void test_css_sink_ignores_non_css_body(void **state)` |
| `test_css_sink_observes_served_stylesheet` | function | `tests/test_tab.c:1870` | `static void test_css_sink_observes_served_stylesheet(void **state)` |
| `test_data_url_classic_script_runs_without_network` | function | `tests/test_tab.c:2551` | `static void test_data_url_classic_script_runs_without_network(void **state)` |
| `test_decode_image_data_url_in_sandbox` | function | `tests/test_tab.c:2876` | `static void test_decode_image_data_url_in_sandbox(void **state)` |
| `test_decode_image_data_url_null_args` | function | `tests/test_tab.c:2918` | `static void test_decode_image_data_url_null_args(void **state)` |
| `test_decode_image_in_sandbox` | function | `tests/test_tab.c:2820` | `static void test_decode_image_in_sandbox(void **state)` |
| `test_decode_image_null_args` | function | `tests/test_tab.c:2857` | `static void test_decode_image_null_args(void **state)` |
| `test_decode_image_rejects_junk` | function | `tests/test_tab.c:2842` | `static void test_decode_image_rejects_junk(void **state)` |
| `test_eval_captures_console_output` | function | `tests/test_tab.c:1390` | `static void test_eval_captures_console_output(void **state)` |
| `test_eval_exception` | function | `tests/test_tab.c:2688` | `static void test_eval_exception(void **state)` |
| `test_eval_no_network_or_cross_origin_api` | function | `tests/test_tab.c:1563` | `static void test_eval_no_network_or_cross_origin_api(void **state)` |
| `test_eval_persistent_state` | function | `tests/test_tab.c:2700` | `static void test_eval_persistent_state(void **state)` |
| `test_eval_sees_dom` | function | `tests/test_tab.c:1536` | `static void test_eval_sees_dom(void **state)` |
| `test_eval_sees_env` | function | `tests/test_tab.c:1546` | `static void test_eval_sees_env(void **state)` |
| `test_eval_without_load` | function | `tests/test_tab.c:2733` | `static void test_eval_without_load(void **state)` |
| `test_event_ipc_via_tab_eval` | function | `tests/test_tab.c:626` | `static void test_event_ipc_via_tab_eval(void **state)` |
| `test_event_navigation_is_policy_gated` | function | `tests/test_tab.c:2238` | `static void test_event_navigation_is_policy_gated(void **state)` |
| `test_external_css_applied_when_allowed` | function | `tests/test_tab.c:1832` | `static void test_external_css_applied_when_allowed(void **state)` |
| `test_external_css_bad_ctype_not_parsed` | function | `tests/test_tab.c:1935` | `static void test_external_css_bad_ctype_not_parsed(void **state)` |
| `test_external_css_blocked_host_refused` | function | `tests/test_tab.c:1953` | `static void test_external_css_blocked_host_refused(void **state)` |
| `test_external_css_skipped_without_grant` | function | `tests/test_tab.c:1916` | `static void test_external_css_skipped_without_grant(void **state)` |
| `test_external_css_survives_click_rederive` | function | `tests/test_tab.c:2618` | `static void test_external_css_survives_click_rederive(void **state)` |
| `test_external_script_bad_ctype_not_executed` | function | `tests/test_tab.c:1759` | `static void test_external_script_bad_ctype_not_executed(void **state)` |
| `test_external_script_blocked_host_refused` | function | `tests/test_tab.c:1776` | `static void test_external_script_blocked_host_refused(void **state)` |
| `test_external_script_document_order` | function | `tests/test_tab.c:1712` | `static void test_external_script_document_order(void **state)` |
| `test_external_script_executes_when_net_allowed` | function | `tests/test_tab.c:1695` | `static void test_external_script_executes_when_net_allowed(void **state)` |
| `test_external_script_skipped_without_net` | function | `tests/test_tab.c:1735` | `static void test_external_script_skipped_without_net(void **state)` |
| `test_focus_ipc_round_trip` | function | `tests/test_tab.c:726` | `static void test_focus_ipc_round_trip(void **state)` |
| `test_free_null_and_double` | function | `tests/test_tab.c:2786` | `static void test_free_null_and_double(void **state)` |
| `test_geometry_never_reaches_untrusted_page` | function | `tests/test_tab.c:2065` | `static void test_geometry_never_reaches_untrusted_page(void **state)` |
| `test_geometry_reaches_trusted_page` | function | `tests/test_tab.c:2057` | `static void test_geometry_reaches_trusted_page(void **state)` |
| `test_history_ops_reach_parent_and_popstate_returns` | function | `tests/test_tab.c:2266` | `static void test_history_ops_reach_parent_and_popstate_returns(void **state)` |
| `test_import_map_resolves_bare_specifier` | function | `tests/test_tab.c:2530` | `static void test_import_map_resolves_bare_specifier(void **state)` |
| `test_js_navigation_relative_resolved` | function | `tests/test_tab.c:1456` | `static void test_js_navigation_relative_resolved(void **state)` |
| `test_js_navigation_unsafe_is_blocked` | function | `tests/test_tab.c:1475` | `static void test_js_navigation_unsafe_is_blocked(void **state)` |
| `test_load_basic` | function | `tests/test_tab.c:94` | `static void test_load_basic(void **state)` |
| `test_load_captures_console_and_error` | function | `tests/test_tab.c:1243` | `static void test_load_captures_console_and_error(void **state)` |
| `test_load_carries_author_color` | function | `tests/test_tab.c:202` | `static void test_load_carries_author_color(void **state)` |
| `test_load_carries_box_decoration` | function | `tests/test_tab.c:840` | `static void test_load_carries_box_decoration(void **state)` |
| `test_load_carries_box_tree` | function | `tests/test_tab.c:876` | `static void test_load_carries_box_tree(void **state)` |
| `test_load_carries_flex_item` | function | `tests/test_tab.c:229` | `static void test_load_carries_flex_item(void **state)` |
| `test_load_carries_flex_wrap_align_row_gap` | function | `tests/test_tab.c:316` | `static void test_load_carries_flex_wrap_align_row_gap(void **state)` |
| `test_load_carries_float` | function | `tests/test_tab.c:391` | `static void test_load_carries_float(void **state)` |
| `test_load_carries_fontface` | function | `tests/test_tab.c:356` | `static void test_load_carries_fontface(void **state)` |
| `test_load_carries_input_box_and_clip` | function | `tests/test_tab.c:963` | `static void test_load_carries_input_box_and_clip(void **state)` |
| `test_load_carries_node_id` | function | `tests/test_tab.c:518` | `static void test_load_carries_node_id(void **state)` |
| `test_load_carries_oof_flag` | function | `tests/test_tab.c:552` | `static void test_load_carries_oof_flag(void **state)` |
| `test_load_carries_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_tab.c:434` | `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `test_load_document_fonts_stub` | function | `tests/test_tab.c:1354` | `static void test_load_document_fonts_stub(void **state)` |
| `test_load_element_wrapper_idioms` | function | `tests/test_tab.c:1324` | `static void test_load_element_wrapper_idioms(void **state)` |
| `test_load_error_carries_location` | function | `tests/test_tab.c:1298` | `static void test_load_error_carries_location(void **state)` |
| `test_load_ex_builds_dom_and_fires_onload` | function | `tests/test_tab.c:1154` | `static void test_load_ex_builds_dom_and_fires_onload(void **state)` |
| `test_load_ex_inner_html_renders` | function | `tests/test_tab.c:1182` | `static void test_load_ex_inner_html_renders(void **state)` |
| `test_load_ex_noscript_hidden_with_js` | function | `tests/test_tab.c:1055` | `static void test_load_ex_noscript_hidden_with_js(void **state)` |
| `test_load_full_location_is_real` | function | `tests/test_tab.c:1419` | `static void test_load_full_location_is_real(void **state)` |
| `test_load_isolates_script_errors` | function | `tests/test_tab.c:1270` | `static void test_load_isolates_script_errors(void **state)` |
| `test_load_no_session_cookies_when_untrusted` | function | `tests/test_tab.c:1132` | `static void test_load_no_session_cookies_when_untrusted(void **state)` |
| `test_load_null_and_too_large` | function | `tests/test_tab.c:1511` | `static void test_load_null_and_too_large(void **state)` |
| `test_load_returns_image_run` | function | `tests/test_tab.c:138` | `static void test_load_returns_image_run(void **state)` |
| `test_load_returns_view_with_link` | function | `tests/test_tab.c:111` | `static void test_load_returns_view_with_link(void **state)` |
| `test_load_strips_script` | function | `tests/test_tab.c:1009` | `static void test_load_strips_script(void **state)` |
| `test_load_view_codec_full_roundtrip` | function | `tests/test_tab.c:2978` | `static void test_load_view_codec_full_roundtrip(void **state)` |
| `test_load_without_js_has_empty_console` | function | `tests/test_tab.c:1374` | `static void test_load_without_js_has_empty_console(void **state)` |
| `test_local_storage_never_seeded_for_untrusted` | function | `tests/test_tab.c:2460` | `static void test_local_storage_never_seeded_for_untrusted(void **state)` |
| `test_local_storage_seeded_and_collected_for_trusted` | function | `tests/test_tab.c:2438` | `static void test_local_storage_seeded_and_collected_for_trusted(void **state)` |
| `test_long_data_module_runs_whole` | function | `tests/test_tab.c:2571` | `static void test_long_data_module_runs_whole(void **state)` |
| `test_module_scripts_run_for_trusted_host` | function | `tests/test_tab.c:2511` | `static void test_module_scripts_run_for_trusted_host(void **state)` |
| `test_module_src_is_a_url_and_data_modules_run` | function | `tests/test_tab.c:2596` | `static void test_module_src_is_a_url_and_data_modules_run(void **state)` |
| `test_mouse_ipc_round_trip` | function | `tests/test_tab.c:681` | `static void test_mouse_ipc_round_trip(void **state)` |
| `test_no_js_no_navigation` | function | `tests/test_tab.c:1497` | `static void test_no_js_no_navigation(void **state)` |
| `test_nomodule_fallback_for_untrusted_host` | function | `tests/test_tab.c:2520` | `static void test_nomodule_fallback_for_untrusted_host(void **state)` |
| `test_open_close` | function | `tests/test_tab.c:77` | `static void test_open_close(void **state)` |
| `test_open_null` | function | `tests/test_tab.c:87` | `static void test_open_null(void **state)` |
| `test_reload_replaces_page` | function | `tests/test_tab.c:2709` | `static void test_reload_replaces_page(void **state)` |
| `test_repl_net_lists_page_requests` | function | `tests/test_tab.c:2148` | `static void test_repl_net_lists_page_requests(void **state)` |
| `test_repl_panels_tree_styles_box` | function | `tests/test_tab.c:2168` | `static void test_repl_panels_tree_styles_box(void **state)` |
| `test_subreq_permitted_pure` | function | `tests/test_tab.c:2646` | `static void test_subreq_permitted_pure(void **state)` |
| `test_tick_fires_delayed_timer` | function | `tests/test_tab.c:773` | `static void test_tick_fires_delayed_timer(void **state)` |
| `test_tick_interval_rearms` | function | `tests/test_tab.c:810` | `static void test_tick_interval_rearms(void **state)` |
| `test_timer_navigation_reaches_parent` | function | `tests/test_tab.c:2216` | `static void test_timer_navigation_reaches_parent(void **state)` |
| `test_websocket_absent_for_untrusted_host` | function | `tests/test_tab.c:2399` | `static void test_websocket_absent_for_untrusted_host(void **state)` |
| `test_websocket_ops_and_events_cross_the_worker` | function | `tests/test_tab.c:2372` | `static void test_websocket_ops_and_events_cross_the_worker(void **state)` |
| `test_window_open_absent_for_untrusted_host` | function | `tests/test_tab.c:2345` | `static void test_window_open_absent_for_untrusted_host(void **state)` |
| `test_window_open_on_gesture_for_trusted_host` | function | `tests/test_tab.c:2324` | `static void test_window_open_on_gesture_for_trusted_host(void **state)` |
| `test_worker_args_malformed` | function | `tests/test_tab.c:2947` | `static void test_worker_args_malformed(void **state)` |
| `test_worker_args_not_worker` | function | `tests/test_tab.c:2940` | `static void test_worker_args_not_worker(void **state)` |
| `test_worker_args_null_safe` | function | `tests/test_tab.c:2962` | `static void test_worker_args_null_safe(void **state)` |
| `test_worker_args_valid` | function | `tests/test_tab.c:2931` | `static void test_worker_args_valid(void **state)` |
| `test_xhr_undefined_when_net_not_allowed` | function | `tests/test_tab.c:1625` | `static void test_xhr_undefined_when_net_not_allowed(void **state)` |
| `test_xhr_works_when_net_allowed` | function | `tests/test_tab.c:1601` | `static void test_xhr_works_when_net_allowed(void **state)` |
| `view_find_text` | function | `tests/test_tab.c:1821` | `static const pv_run *view_find_text(const pv_view *v, const char *needle)` |
| `main` | function | `tests/test_text_case.c:73` | `int main(void)` |
| `test_smallcaps_runs` | function | `tests/test_text_case.c:55` | `static void test_smallcaps_runs(void **state)` |
| `test_transform_keeps_length` | function | `tests/test_text_case.c:33` | `static void test_transform_keeps_length(void **state)` |
| `test_upper_lower_ascii_latin` | function | `tests/test_text_case.c:10` | `static void test_upper_lower_ascii_latin(void **state)` |
| `fake_cover` | function | `tests/test_text_shape.c:383` | `static int fake_cover(unsigned cp, void *ctx)` |
| `inked_pixels` | function | `tests/test_text_shape.c:149` | `static int inked_pixels(cairo_surface_t *s)` |
| `main` | function | `tests/test_text_shape.c:426` | `int main(void)` |
| `read_host_font` | function | `tests/test_text_shape.c:201` | `static unsigned char *read_host_font(const char *path, size_t *out_n)` |
| `set_installed` | function | `tests/test_text_shape.c:306` | `static int set_installed(const char *name, void *ctx)` |
| `table_resolve` | function | `tests/test_text_shape.c:276` | `static int table_resolve(const char *name, char *out, size_t cap, void *ctx)` |
| `teardown` | function | `tests/test_text_shape.c:358` | `static int teardown(void **state)` |
| `test_determinism` | function | `tests/test_text_shape.c:95` | `static void test_determinism(void **state)` |
| `test_draw_paints` | function | `tests/test_text_shape.c:133` | `static void test_draw_paints(void **state)` |
| `test_empty_slice_is_ok` | function | `tests/test_text_shape.c:60` | `static void test_empty_slice_is_ok(void **state)` |
| `test_generic_keywords` | function | `tests/test_text_shape.c:264` | `static void test_generic_keywords(void **state)` |
| `test_local_handle_real_fontconfig` | function | `tests/test_text_shape.c:337` | `static void test_local_handle_real_fontconfig(void **state)` |
| `test_measure_matches_shape` | function | `tests/test_text_shape.c:111` | `static void test_measure_matches_shape(void **state)` |
| `test_measure_uses_fallback_face` | function | `tests/test_text_shape.c:415` | `static void test_measure_uses_fallback_face(void **state)` |
| `test_null_and_bad_inputs` | function | `tests/test_text_shape.c:30` | `static void test_null_and_bad_inputs(void **state)` |
| `test_overflow_cap` | function | `tests/test_text_shape.c:123` | `static void test_overflow_cap(void **state)` |
| `test_pick_family_strong_vs_weak` | function | `tests/test_text_shape.c:313` | `static void test_pick_family_strong_vs_weak(void **state)` |
| `test_pick_from_list_order_and_generic_stop` | function | `tests/test_text_shape.c:286` | `static void test_pick_from_list_order_and_generic_stop(void **state)` |
| `test_segment_runs` | function | `tests/test_text_shape.c:390` | `static void test_segment_runs(void **state)` |
| `test_shape_ascii` | function | `tests/test_text_shape.c:73` | `static void test_shape_ascii(void **state)` |
| `test_uncovered_pua_draws_nothing` | function | `tests/test_text_shape.c:161` | `static void test_uncovered_pua_draws_nothing(void **state)` |
| `test_webfont_register_find_clear` | function | `tests/test_text_shape.c:216` | `static void test_webfont_register_find_clear(void **state)` |
| `test_webfont_rejects_bad_input` | function | `tests/test_text_shape.c:179` | `static void test_webfont_rejects_bad_input(void **state)` |
| `main` | function | `tests/test_textfield.c:140` | `int main(void)` |
| `test_backspace_delete` | function | `tests/test_textfield.c:76` | `static void test_backspace_delete(void **state)` |
| `test_full_fails_closed` | function | `tests/test_textfield.c:113` | `static void test_full_fails_closed(void **state)` |
| `test_init_and_accessors` | function | `tests/test_textfield.c:20` | `static void test_init_and_accessors(void **state)` |
| `test_insert_sequence` | function | `tests/test_textfield.c:59` | `static void test_insert_sequence(void **state)` |
| `test_move_saturates` | function | `tests/test_textfield.c:100` | `static void test_move_saturates(void **state)` |
| `test_null_safe` | function | `tests/test_textfield.c:29` | `static void test_null_safe(void **state)` |
| `test_set` | function | `tests/test_textfield.c:46` | `static void test_set(void **state)` |
| `main` | function | `tests/test_tls_impersonate.c:218` | `int main(void)` |
| `test_decode_rejects_bad_magic` | function | `tests/test_tls_impersonate.c:163` | `static void test_decode_rejects_bad_magic(void **state)` |
| `test_decode_rejects_overlong_field` | function | `tests/test_tls_impersonate.c:177` | `static void test_decode_rejects_overlong_field(void **state)` |
| `test_decode_rejects_truncated` | function | `tests/test_tls_impersonate.c:144` | `static void test_decode_rejects_truncated(void **state)` |
| `test_encode_decode_req_empty_body` | function | `tests/test_tls_impersonate.c:65` | `static void test_encode_decode_req_empty_body(void **state)` |
| `test_encode_decode_req_roundtrip` | function | `tests/test_tls_impersonate.c:39` | `static void test_encode_decode_req_roundtrip(void **state)` |
| `test_encode_decode_resp_roundtrip` | function | `tests/test_tls_impersonate.c:89` | `static void test_encode_decode_resp_roundtrip(void **state)` |
| `test_encode_fails_when_no_room` | function | `tests/test_tls_impersonate.c:192` | `static void test_encode_fails_when_no_room(void **state)` |
| `test_encode_rejects_oversize_url` | function | `tests/test_tls_impersonate.c:203` | `static void test_encode_rejects_oversize_url(void **state)` |
| `test_gate_requires_all_three_signals` | function | `tests/test_tls_impersonate.c:22` | `static void test_gate_requires_all_three_signals(void **state)` |
| `test_resp_no_chain_ok` | function | `tests/test_tls_impersonate.c:121` | `static void test_resp_no_chain_ok(void **state)` |
| `assert_line` | function | `tests/test_ui.c:20` | `static void assert_line(const char *text, const ui_layout *lay, size_t n,                        ...` |
| `main` | function | `tests/test_ui.c:130` | `int main(void)` |
| `test_clamp_scroll` | function | `tests/test_ui.c:113` | `static void test_clamp_scroll(void **state)` |
| `test_layout_free_null_and_double` | function | `tests/test_ui.c:121` | `static void test_layout_free_null_and_double(void **state)` |
| `test_wrap_breaks_at_space` | function | `tests/test_ui.c:53` | `static void test_wrap_breaks_at_space(void **state)` |
| `test_wrap_does_not_split_utf8` | function | `tests/test_ui.c:76` | `static void test_wrap_does_not_split_utf8(void **state)` |
| `test_wrap_empty` | function | `tests/test_ui.c:35` | `static void test_wrap_empty(void **state)` |
| `test_wrap_hard_breaks_long_word` | function | `tests/test_ui.c:64` | `static void test_wrap_hard_breaks_long_word(void **state)` |
| `test_wrap_null_args` | function | `tests/test_ui.c:28` | `static void test_wrap_null_args(void **state)` |
| `test_wrap_respects_newline` | function | `tests/test_ui.c:90` | `static void test_wrap_respects_newline(void **state)` |
| `test_wrap_short_single_line` | function | `tests/test_ui.c:43` | `static void test_wrap_short_single_line(void **state)` |
| `test_wrap_zero_cols_is_sanitised` | function | `tests/test_ui.c:101` | `static void test_wrap_zero_cols_is_sanitised(void **state)` |
| `assert_span` | function | `tests/test_url.c:449` | `static void assert_span(const char *p, size_t len, const char *expect)` |
| `main` | function | `tests/test_url.c:701` | `int main(void)` |
| `test_authority_len` | function | `tests/test_url.c:86` | `static void test_authority_len(void **state)` |
| `test_extract_userinfo_at_authority_start` | function | `tests/test_url.c:589` | `static void test_extract_userinfo_at_authority_start(void **state)` |
| `test_extract_userinfo_basic` | function | `tests/test_url.c:516` | `static void test_extract_userinfo_basic(void **state)` |
| `test_extract_userinfo_empty_password` | function | `tests/test_url.c:615` | `static void test_extract_userinfo_empty_password(void **state)` |
| `test_extract_userinfo_https_subresource_no_auth` | function | `tests/test_url.c:566` | `static void test_extract_userinfo_https_subresource_no_auth(void **state)` |
| `test_extract_userinfo_no_at_sign` | function | `tests/test_url.c:602` | `static void test_extract_userinfo_no_at_sign(void **state)` |
| `test_extract_userinfo_no_userinfo` | function | `tests/test_url.c:542` | `static void test_extract_userinfo_no_userinfo(void **state)` |
| `test_extract_userinfo_non_https_passthrough` | function | `tests/test_url.c:554` | `static void test_extract_userinfo_non_https_passthrough(void **state)` |
| `test_extract_userinfo_nulls` | function | `tests/test_url.c:579` | `static void test_extract_userinfo_nulls(void **state)` |
| `test_extract_userinfo_user_only` | function | `tests/test_url.c:529` | `static void test_extract_userinfo_user_only(void **state)` |
| `test_has_scheme` | function | `tests/test_url.c:69` | `static void test_has_scheme(void **state)` |
| `test_history_target_bad_args` | function | `tests/test_url.c:690` | `static void test_history_target_bad_args(void **state)` |
| `test_history_target_cross_origin_rejected` | function | `tests/test_url.c:662` | `static void test_history_target_cross_origin_rejected(void **state)` |
| `test_history_target_file_query_fragment_only` | function | `tests/test_url.c:677` | `static void test_history_target_file_query_fragment_only(void **state)` |
| `test_history_target_same_origin` | function | `tests/test_url.c:641` | `static void test_history_target_same_origin(void **state)` |
| `test_is_file_and_path` | function | `tests/test_url.c:379` | `static void test_is_file_and_path(void **state)` |
| `test_is_https` | function | `tests/test_url.c:23` | `static void test_is_https(void **state)` |
| `test_omnibox_bare_host_gets_https` | function | `tests/test_url.c:251` | `static void test_omnibox_bare_host_gets_https(void **state)` |
| `test_omnibox_foreign_scheme_is_searched_not_executed` | function | `tests/test_url.c:298` | `static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state)` |
| `test_omnibox_http_upgraded_to_https` | function | `tests/test_url.c:268` | `static void test_omnibox_http_upgraded_to_https(void **state)` |
| `test_omnibox_navigate_https` | function | `tests/test_url.c:238` | `static void test_omnibox_navigate_https(void **state)` |
| `test_omnibox_nulls_and_empty` | function | `tests/test_url.c:311` | `static void test_omnibox_nulls_and_empty(void **state)` |
| `test_omnibox_search_for_queries` | function | `tests/test_url.c:278` | `static void test_omnibox_search_for_queries(void **state)` |
| `test_remove_dot_segments` | function | `tests/test_url.c:98` | `static void test_remove_dot_segments(void **state)` |
| `test_remove_dot_segments_nulls` | function | `tests/test_url.c:127` | `static void test_remove_dot_segments_nulls(void **state)` |
| `test_resolve_absolute` | function | `tests/test_url.c:138` | `static void test_resolve_absolute(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_url.c:169` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_dot_segments` | function | `tests/test_url.c:193` | `static void test_resolve_dot_segments(void **state)` |
| `test_resolve_fail_closed_on_bad_base` | function | `tests/test_url.c:210` | `static void test_resolve_fail_closed_on_bad_base(void **state)` |
| `test_resolve_file_confinement_fail_closed` | function | `tests/test_url.c:411` | `static void test_resolve_file_confinement_fail_closed(void **state)` |
| `test_resolve_file_nulls` | function | `tests/test_url.c:437` | `static void test_resolve_file_nulls(void **state)` |
| `test_resolve_file_relative` | function | `tests/test_url.c:391` | `static void test_resolve_file_relative(void **state)` |
| `test_resolve_null_and_overflow` | function | `tests/test_url.c:222` | `static void test_resolve_null_and_overflow(void **state)` |
| `test_resolve_rejects_downgrade_and_schemes` | function | `tests/test_url.c:146` | `static void test_resolve_rejects_downgrade_and_schemes(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_url.c:181` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_url.c:161` | `static void test_resolve_scheme_relative(void **state)` |
| `test_search_rewrite_ddg_spa` | function | `tests/test_url.c:327` | `static void test_search_rewrite_ddg_spa(void **state)` |
| `test_search_rewrite_leaves_others_alone` | function | `tests/test_url.c:344` | `static void test_search_rewrite_leaves_others_alone(void **state)` |
| `test_search_rewrite_nulls` | function | `tests/test_url.c:364` | `static void test_search_rewrite_nulls(void **state)` |
| `test_split_fail_closed_non_https` | function | `tests/test_url.c:628` | `static void test_split_fail_closed_non_https(void **state)` |
| `test_split_fragment_without_query` | function | `tests/test_url.c:495` | `static void test_split_fragment_without_query(void **state)` |
| `test_split_full_url` | function | `tests/test_url.c:454` | `static void test_split_full_url(void **state)` |
| `test_split_ipv6_literal_with_port` | function | `tests/test_url.c:504` | `static void test_split_ipv6_literal_with_port(void **state)` |
| `test_split_no_port_no_path` | function | `tests/test_url.c:473` | `static void test_split_no_port_no_path(void **state)` |
| `test_split_query_without_fragment` | function | `tests/test_url.c:486` | `static void test_split_query_without_fragment(void **state)` |
| `test_validate_https` | function | `tests/test_url.c:36` | `static void test_validate_https(void **state)` |
| `test_validate_long_bundle_url` | function | `tests/test_url.c:49` | `static void test_validate_long_bundle_url(void **state)` |
| `build` | function | `tests/test_web_storage.c:24` | `static size_t build(char *b, const char *const *kv, uint32_t n)` |
| `count_pair` | function | `tests/test_web_storage.c:147` | `static void count_pair(void *ctx, const char *k, size_t kl, const char *v, size_t vl)` |
| `main` | function | `tests/test_web_storage.c:182` | `int main(void)` |
| `test_hostile_snapshots_rejected_and_db_unchanged` | function | `tests/test_web_storage.c:73` | `static void test_hostile_snapshots_rejected_and_db_unchanged(void **state)` |
| `test_origin_table_is_bounded_lru` | function | `tests/test_web_storage.c:129` | `static void test_origin_table_is_bounded_lru(void **state)` |
| `test_pack_foreach_roundtrip` | function | `tests/test_web_storage.c:154` | `static void test_pack_foreach_roundtrip(void **state)` |
| `test_quota_enforced` | function | `tests/test_web_storage.c:112` | `static void test_quota_enforced(void **state)` |
| `test_replace_then_encode_roundtrip` | function | `tests/test_web_storage.c:49` | `static void test_replace_then_encode_roundtrip(void **state)` |
| `test_unknown_origin_encodes_empty` | function | `tests/test_web_storage.c:34` | `static void test_unknown_origin_encodes_empty(void **state)` |
| `assert_memory_equal` | function | `tests/test_webcaps.c:176` | `assert_memory_equal(&(rdp_caps)` |
| `main` | function | `tests/test_webcaps.c:181` | `int main(void)` |
| `mk` | function | `tests/test_webcaps.c:20` | `static wc_input mk(jsp_mode mode, int in_js, int in_allow)` |
| `test_bad_mode_fails_closed` | function | `tests/test_webcaps.c:127` | `static void test_bad_mode_fails_closed(void **state)` |
| `test_from_flags_headless` | function | `tests/test_webcaps.c:153` | `static void test_from_flags_headless(void **state)` |
| `test_jspon_alone_is_not_trust` | function | `tests/test_webcaps.c:85` | `static void test_jspon_alone_is_not_trust(void **state)` |
| `test_present_trust_css_images_only` | function | `tests/test_webcaps.c:56` | `static void test_present_trust_css_images_only(void **state)` |
| `test_render_caps_projection` | function | `tests/test_webcaps.c:138` | `static void test_render_caps_projection(void **state)` |
| `test_safe_is_all_off` | function | `tests/test_webcaps.c:29` | `static void test_safe_is_all_off(void **state)` |
| `test_trusted_host_gets_all_caps` | function | `tests/test_webcaps.c:38` | `static void test_trusted_host_gets_all_caps(void **state)` |
| `test_user_toggles_grant_leakfree` | function | `tests/test_webcaps.c:100` | `static void test_user_toggles_grant_leakfree(void **state)` |
| `main` | function | `tests/test_webfont.c:229` | `int main(void)` |
| `test_data_url_decodes_at_scan` | function | `tests/test_webfont.c:181` | `static void test_data_url_decodes_at_scan(void **state)` |
| `test_name_hash` | function | `tests/test_webfont.c:218` | `static void test_name_hash(void **state)` |
| `test_ref_move_transfers_bytes` | function | `tests/test_webfont.c:198` | `static void test_ref_move_transfers_bytes(void **state)` |
| `test_scan_basic_two_formats` | function | `tests/test_webfont.c:36` | `static void test_scan_basic_two_formats(void **state)` |
| `test_scan_case_and_ws` | function | `tests/test_webfont.c:106` | `static void test_scan_case_and_ws(void **state)` |
| `test_scan_hostile_truncations` | function | `tests/test_webfont.c:120` | `static void test_scan_hostile_truncations(void **state)` |
| `test_scan_ignores_other_at_rules` | function | `tests/test_webfont.c:168` | `static void test_scan_ignores_other_at_rules(void **state)` |
| `test_scan_local_only_yields_nothing` | function | `tests/test_webfont.c:81` | `static void test_scan_local_only_yields_nothing(void **state)` |
| `test_scan_overlong_url_dropped` | function | `tests/test_webfont.c:140` | `static void test_scan_overlong_url_dropped(void **state)` |
| `test_scan_quoted_family_variants` | function | `tests/test_webfont.c:92` | `static void test_scan_quoted_family_variants(void **state)` |
| `test_scan_weight_style` | function | `tests/test_webfont.c:55` | `static void test_scan_weight_style(void **state)` |
| `test_supported_format` | function | `tests/test_webfont.c:155` | `static void test_supported_format(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_webfont_load.c:13` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_webfont_load.c:325` | `int main(void)` |
| `read_host_font` | function | `tests/test_webfont_load.c:64` | `static unsigned char *read_host_font(size_t *out_n)` |
| `stub` | struct | `tests/test_webfont_load.c:30` | `` |
| `stub_fetch` | function | `tests/test_webfont_load.c:38` | `static int stub_fetch(void *ctx, const char *url,                       int *out_status, char **o...` |
| `teardown` | function | `tests/test_webfont_load.c:318` | `static int teardown(void **state)` |
| `test_b64` | function | `tests/test_webfont_load.c:92` | `static char *test_b64(const unsigned char *in, size_t n)` |
| `test_data_url_bad_bytes_skipped` | function | `tests/test_webfont_load.c:240` | `static void test_data_url_bad_bytes_skipped(void **state)` |
| `test_data_url_registers` | function | `tests/test_webfont_load.c:255` | `static void test_data_url_registers(void **state)` |
| `test_extern_sheet_relative_url` | function | `tests/test_webfont_load.c:217` | `static void test_extern_sheet_relative_url(void **state)` |
| `test_fallback_second_url` | function | `tests/test_webfont_load.c:170` | `static void test_fallback_second_url(void **state)` |
| `test_first_wins` | function | `tests/test_webfont_load.c:194` | `static void test_first_wins(void **state)` |
| `test_https_stub_registers` | function | `tests/test_webfont_load.c:126` | `static void test_https_stub_registers(void **state)` |
| `test_null_args` | function | `tests/test_webfont_load.c:113` | `static void test_null_args(void **state)` |
| `test_null_page_data_only` | function | `tests/test_webfont_load.c:288` | `static void test_null_page_data_only(void **state)` |
| `test_woff2_never_fetched` | function | `tests/test_webfont_load.c:152` | `static void test_woff2_never_fetched(void **state)` |
| `main` | function | `tests/test_wl_display.c:43` | `int main(void)` |
| `test_ignores_lock_and_garbage` | function | `tests/test_wl_display.c:19` | `static void test_ignores_lock_and_garbage(void **state)` |
| `test_null_entry` | function | `tests/test_wl_display.c:35` | `static void test_null_entry(void **state)` |
| `test_picks_lowest` | function | `tests/test_wl_display.c:11` | `static void test_picks_lowest(void **state)` |
| `test_small_cap_fails_closed` | function | `tests/test_wl_display.c:27` | `static void test_small_cap_fails_closed(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_ws_hub.c:7` | `#define _POSIX_C_SOURCE` |
| `emit` | function | `tests/test_ws_hub.c:21` | `static void emit(void *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `main` | function | `tests/test_ws_hub.c:142` | `int main(void)` |
| `n` | type_alias | `tests/test_ws_hub.c:18` | `typedef struct rec { int n;` |

Next: [SYMBOLS_p15.md](SYMBOLS_p15.md)
