# Symbols (page 16 of 16)
Previous: [SYMBOLS_p15.md](SYMBOLS_p15.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `cs_open` | function | `tests/test_tab.c:2225` | `static void cs_open(tab **t, int net)` |
| `document` | function | `tests/test_tab.c:2110` | `* listener is on document (the React/jQuery-delegation shape);` |
| `expect_eval` | function | `tests/test_tab.c:70` | `static void expect_eval(tab *t, const char *js, const char *expected)` |
| `expect_eval` | function | `tests/test_tab.c:1622` | `expect_eval(f->t, "var fr=function(n)` |
| `expect_eval` | function | `tests/test_tab.c:1623` | `expect_eval(f->t, "var gr=function()` |
| `expect_eval` | function | `tests/test_tab.c:1726` | `expect_eval(t, "var n=net(), a=n.filter(function(e)` |
| `fixture` | struct | `tests/test_tab.c:47` | `` |
| `geom_load_and_measure` | function | `tests/test_tab.c:2170` | `static int geom_load_and_measure(int net, char *out, size_t outsz)` |
| `load` | function | `tests/test_tab.c:2160` | `* table only for a trusted load (net granted: allow.conf AND js.conf);` |
| `load_js_page` | function | `tests/test_tab.c:2327` | `static void load_js_page(tab **out_t, const char *html, tab_page *p)` |
| `ls_load` | function | `tests/test_tab.c:2703` | `static void ls_load(int net, tab **t, tab_page *p)` |
| `main` | function | `tests/test_tab.c:3606` | `int main(int argc, char **argv)` |
| `module_page` | function | `tests/test_tab.c:2789` | `static const pv_run *module_page(int net, tab **t, tab_page *p, const char *needle)` |
| `ms_since` | function | `tests/test_tab.c:2936` | `static long ms_since(const struct timespec *a)` |
| `n` | type_alias | `tests/test_tab.c:1991` | `typedef struct sink_cap { int n;` |
| `open_page` | function | `tests/test_tab.c:2455` | `static void open_page(int net, tab **t, tab_page *p)` |
| `paragraph` | function | `tests/test_tab.c:175` | `* reserved 200x280 box and the alt flowed as a paragraph (jkanime tiles). */ static void test_loa...` |
| `read` | function | `tests/test_tab.c:3145` | `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */ static void tes...` |
| `setup_loaded` | function | `tests/test_tab.c:49` | `static int setup_loaded(void **state)` |
| `sink_cap` | struct | `tests/test_tab.c:1991` | `` |
| `sink_capture` | function | `tests/test_tab.c:1993` | `static void sink_capture(void *ctx, const char *url,                          const char *body, s...` |
| `slow_fetch` | function | `tests/test_tab.c:1682` | `static int slow_fetch(void *ctx, const char *method, const char *url,                       const...` |
| `slow_tab` | function | `tests/test_tab.c:2925` | `static tab *slow_tab(void)` |
| `stub_css_fetch` | function | `tests/test_tab.c:1937` | `static int stub_css_fetch(void *ctx, const char *method, const char *url,                        ...` |
| `stub_fetch` | function | `tests/test_tab.c:1666` | `static int stub_fetch(void *ctx, const char *method, const char *url,                       const...` |
| `stub_module_fetch` | function | `tests/test_tab.c:2751` | `static int stub_module_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `stub_script_fetch` | function | `tests/test_tab.c:1803` | `static int stub_script_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `stub_slow_fetch` | function | `tests/test_tab.c:2883` | `static int stub_slow_fetch(void *ctx, const char *method, const char *url, const char *body,     ...` |
| `teardown` | function | `tests/test_tab.c:60` | `static int teardown(void **state)` |
| `test_ajax_after_load_reaches_the_gated_fetcher` | function | `tests/test_tab.c:2852` | `static void test_ajax_after_load_reaches_the_gated_fetcher(void **state)` |
| `test_async_subrequests_run_in_parallel` | function | `tests/test_tab.c:1701` | `static void test_async_subrequests_run_in_parallel(void **state)` |
| `test_async_tick_returns_at_once_and_delivers_through_eventfd` | function | `tests/test_tab.c:2942` | `static void test_async_tick_returns_at_once_and_delivers_through_eventfd(void **state)` |
| `test_binary_does_not_crash_parent` | function | `tests/test_tab.c:3223` | `static void test_binary_does_not_crash_parent(void **state)` |
| `test_boxdef_node_id_crosses_codec` | function | `tests/test_tab.c:2141` | `static void test_boxdef_node_id_crosses_codec(void **state)` |
| `test_child_death_survived` | function | `tests/test_tab.c:3238` | `static void test_child_death_survived(void **state)` |
| `test_click_bubbles_to_delegated_document_listener` | function | `tests/test_tab.c:2113` | `static void test_click_bubbles_to_delegated_document_listener(void **state)` |
| `test_click_handler_navigation_reaches_parent` | function | `tests/test_tab.c:2333` | `static void test_click_handler_navigation_reaches_parent(void **state)` |
| `test_click_runs_handler_and_returns_view` | function | `tests/test_tab.c:591` | `static void test_click_runs_handler_and_returns_view(void **state)` |
| `test_computed_style_follows_dom_mutation` | function | `tests/test_tab.c:2252` | `static void test_computed_style_follows_dom_mutation(void **state)` |
| `test_computed_style_is_inline_only_for_untrusted_host` | function | `tests/test_tab.c:2271` | `static void test_computed_style_is_inline_only_for_untrusted_host(void **state)` |
| `test_computed_style_reads_the_cascade_for_trusted_host` | function | `tests/test_tab.c:2233` | `static void test_computed_style_reads_the_cascade_for_trusted_host(void **state)` |
| `test_css_sink_ignores_non_css_body` | function | `tests/test_tab.c:2034` | `static void test_css_sink_ignores_non_css_body(void **state)` |
| `test_css_sink_observes_served_stylesheet` | function | `tests/test_tab.c:2008` | `static void test_css_sink_observes_served_stylesheet(void **state)` |
| `test_data_module_imports_absolute_https` | function | `tests/test_tab.c:3075` | `static void test_data_module_imports_absolute_https(void **state)` |
| `test_data_url_classic_script_runs_without_network` | function | `tests/test_tab.c:3005` | `static void test_data_url_classic_script_runs_without_network(void **state)` |
| `test_decode_image_data_url_in_sandbox` | function | `tests/test_tab.c:3354` | `static void test_decode_image_data_url_in_sandbox(void **state)` |
| `test_decode_image_data_url_null_args` | function | `tests/test_tab.c:3396` | `static void test_decode_image_data_url_null_args(void **state)` |
| `test_decode_image_in_sandbox` | function | `tests/test_tab.c:3298` | `static void test_decode_image_in_sandbox(void **state)` |
| `test_decode_image_null_args` | function | `tests/test_tab.c:3335` | `static void test_decode_image_null_args(void **state)` |
| `test_decode_image_rejects_junk` | function | `tests/test_tab.c:3320` | `static void test_decode_image_rejects_junk(void **state)` |
| `test_dynamic_import_from_classic_script_uses_document_base` | function | `tests/test_tab.c:2820` | `static void test_dynamic_import_from_classic_script_uses_document_base(void **state)` |
| `test_eval_captures_console_output` | function | `tests/test_tab.c:1463` | `static void test_eval_captures_console_output(void **state)` |
| `test_eval_exception` | function | `tests/test_tab.c:3166` | `static void test_eval_exception(void **state)` |
| `test_eval_no_network_or_cross_origin_api` | function | `tests/test_tab.c:1647` | `static void test_eval_no_network_or_cross_origin_api(void **state)` |
| `test_eval_persistent_state` | function | `tests/test_tab.c:3178` | `static void test_eval_persistent_state(void **state)` |
| `test_eval_sees_dom` | function | `tests/test_tab.c:1609` | `static void test_eval_sees_dom(void **state)` |
| `test_eval_sees_env` | function | `tests/test_tab.c:1630` | `static void test_eval_sees_env(void **state)` |
| `test_eval_without_load` | function | `tests/test_tab.c:3211` | `static void test_eval_without_load(void **state)` |
| `test_event_ipc_via_tab_eval` | function | `tests/test_tab.c:630` | `static void test_event_ipc_via_tab_eval(void **state)` |
| `test_event_navigation_is_policy_gated` | function | `tests/test_tab.c:2376` | `static void test_event_navigation_is_policy_gated(void **state)` |
| `test_external_css_applied_when_allowed` | function | `tests/test_tab.c:1970` | `static void test_external_css_applied_when_allowed(void **state)` |
| `test_external_css_bad_ctype_not_parsed` | function | `tests/test_tab.c:2073` | `static void test_external_css_bad_ctype_not_parsed(void **state)` |
| `test_external_css_blocked_host_refused` | function | `tests/test_tab.c:2091` | `static void test_external_css_blocked_host_refused(void **state)` |
| `test_external_css_skipped_without_grant` | function | `tests/test_tab.c:2054` | `static void test_external_css_skipped_without_grant(void **state)` |
| `test_external_css_survives_click_rederive` | function | `tests/test_tab.c:3096` | `static void test_external_css_survives_click_rederive(void **state)` |
| `test_external_script_bad_ctype_not_executed` | function | `tests/test_tab.c:1897` | `static void test_external_script_bad_ctype_not_executed(void **state)` |
| `test_external_script_blocked_host_refused` | function | `tests/test_tab.c:1914` | `static void test_external_script_blocked_host_refused(void **state)` |
| `test_external_script_document_order` | function | `tests/test_tab.c:1850` | `static void test_external_script_document_order(void **state)` |
| `test_external_script_executes_when_net_allowed` | function | `tests/test_tab.c:1833` | `static void test_external_script_executes_when_net_allowed(void **state)` |
| `test_external_script_skipped_without_net` | function | `tests/test_tab.c:1873` | `static void test_external_script_skipped_without_net(void **state)` |
| `test_first_visit_trusted_host_can_set_cookie` | function | `tests/test_tab.c:1137` | `static void test_first_visit_trusted_host_can_set_cookie(void **state)` |
| `test_focus_ipc_round_trip` | function | `tests/test_tab.c:730` | `static void test_focus_ipc_round_trip(void **state)` |
| `test_frames_absent_for_untrusted_host` | function | `tests/test_tab.c:2677` | `static void test_frames_absent_for_untrusted_host(void **state)` |
| `test_frames_cross_the_worker` | function | `tests/test_tab.c:2640` | `static void test_frames_cross_the_worker(void **state)` |
| `test_free_null_and_double` | function | `tests/test_tab.c:3264` | `static void test_free_null_and_double(void **state)` |
| `test_geometry_never_reaches_untrusted_page` | function | `tests/test_tab.c:2203` | `static void test_geometry_never_reaches_untrusted_page(void **state)` |
| `test_geometry_reaches_trusted_page` | function | `tests/test_tab.c:2195` | `static void test_geometry_reaches_trusted_page(void **state)` |
| `test_history_ops_reach_parent_and_popstate_returns` | function | `tests/test_tab.c:2404` | `static void test_history_ops_reach_parent_and_popstate_returns(void **state)` |
| `test_identity_override_reaches_worker` | function | `tests/test_tab.c:1177` | `static void test_identity_override_reaches_worker(void **state)` |
| `test_import_map_resolves_bare_specifier` | function | `tests/test_tab.c:2984` | `static void test_import_map_resolves_bare_specifier(void **state)` |
| `test_indexeddb_only_for_trusted_host` | function | `tests/test_tab.c:1158` | `static void test_indexeddb_only_for_trusted_host(void **state)` |
| `test_js_navigation_relative_resolved` | function | `tests/test_tab.c:1529` | `static void test_js_navigation_relative_resolved(void **state)` |
| `test_js_navigation_unsafe_is_blocked` | function | `tests/test_tab.c:1548` | `static void test_js_navigation_unsafe_is_blocked(void **state)` |
| `test_lazy_script_src_and_import_after_load` | function | `tests/test_tab.c:2863` | `static void test_lazy_script_src_and_import_after_load(void **state)` |
| `test_load_basic` | function | `tests/test_tab.c:98` | `static void test_load_basic(void **state)` |
| `test_load_captures_console_and_error` | function | `tests/test_tab.c:1316` | `static void test_load_captures_console_and_error(void **state)` |
| `test_load_carries_author_color` | function | `tests/test_tab.c:206` | `static void test_load_carries_author_color(void **state)` |
| `test_load_carries_box_decoration` | function | `tests/test_tab.c:844` | `static void test_load_carries_box_decoration(void **state)` |
| `test_load_carries_box_tree` | function | `tests/test_tab.c:880` | `static void test_load_carries_box_tree(void **state)` |
| `test_load_carries_flex_item` | function | `tests/test_tab.c:233` | `static void test_load_carries_flex_item(void **state)` |
| `test_load_carries_flex_wrap_align_row_gap` | function | `tests/test_tab.c:320` | `static void test_load_carries_flex_wrap_align_row_gap(void **state)` |
| `test_load_carries_float` | function | `tests/test_tab.c:395` | `static void test_load_carries_float(void **state)` |
| `test_load_carries_fontface` | function | `tests/test_tab.c:360` | `static void test_load_carries_fontface(void **state)` |
| `test_load_carries_input_box_and_clip` | function | `tests/test_tab.c:967` | `static void test_load_carries_input_box_and_clip(void **state)` |
| `test_load_carries_node_id` | function | `tests/test_tab.c:522` | `static void test_load_carries_node_id(void **state)` |
| `test_load_carries_oof_flag` | function | `tests/test_tab.c:556` | `static void test_load_carries_oof_flag(void **state)` |
| `test_load_carries_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_tab.c:438` | `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `test_load_document_fonts_stub` | function | `tests/test_tab.c:1427` | `static void test_load_document_fonts_stub(void **state)` |
| `test_load_element_wrapper_idioms` | function | `tests/test_tab.c:1397` | `static void test_load_element_wrapper_idioms(void **state)` |
| `test_load_error_carries_location` | function | `tests/test_tab.c:1371` | `static void test_load_error_carries_location(void **state)` |
| `test_load_ex_builds_dom_and_fires_onload` | function | `tests/test_tab.c:1227` | `static void test_load_ex_builds_dom_and_fires_onload(void **state)` |
| `test_load_ex_inner_html_renders` | function | `tests/test_tab.c:1255` | `static void test_load_ex_inner_html_renders(void **state)` |
| `test_load_ex_noscript_hidden_with_js` | function | `tests/test_tab.c:1059` | `static void test_load_ex_noscript_hidden_with_js(void **state)` |
| `test_load_full_location_is_real` | function | `tests/test_tab.c:1492` | `static void test_load_full_location_is_real(void **state)` |
| `test_load_isolates_script_errors` | function | `tests/test_tab.c:1343` | `static void test_load_isolates_script_errors(void **state)` |
| `test_load_no_session_cookies_when_untrusted` | function | `tests/test_tab.c:1205` | `static void test_load_no_session_cookies_when_untrusted(void **state)` |
| `test_load_null_and_too_large` | function | `tests/test_tab.c:1584` | `static void test_load_null_and_too_large(void **state)` |
| `test_load_returns_image_run` | function | `tests/test_tab.c:142` | `static void test_load_returns_image_run(void **state)` |
| `test_load_returns_view_with_link` | function | `tests/test_tab.c:115` | `static void test_load_returns_view_with_link(void **state)` |
| `test_load_strips_script` | function | `tests/test_tab.c:1013` | `static void test_load_strips_script(void **state)` |
| `test_load_view_codec_full_roundtrip` | function | `tests/test_tab.c:3456` | `static void test_load_view_codec_full_roundtrip(void **state)` |
| `test_load_without_js_has_empty_console` | function | `tests/test_tab.c:1447` | `static void test_load_without_js_has_empty_console(void **state)` |
| `test_local_storage_never_seeded_for_untrusted` | function | `tests/test_tab.c:2739` | `static void test_local_storage_never_seeded_for_untrusted(void **state)` |
| `test_local_storage_seeded_and_collected_for_trusted` | function | `tests/test_tab.c:2717` | `static void test_local_storage_seeded_and_collected_for_trusted(void **state)` |
| `test_long_data_module_runs_whole` | function | `tests/test_tab.c:3025` | `static void test_long_data_module_runs_whole(void **state)` |
| `test_module_scripts_run_for_trusted_host` | function | `tests/test_tab.c:2798` | `static void test_module_scripts_run_for_trusted_host(void **state)` |
| `test_module_src_is_a_url_and_data_modules_run` | function | `tests/test_tab.c:3050` | `static void test_module_src_is_a_url_and_data_modules_run(void **state)` |
| `test_mouse_ipc_round_trip` | function | `tests/test_tab.c:685` | `static void test_mouse_ipc_round_trip(void **state)` |
| `test_no_js_no_navigation` | function | `tests/test_tab.c:1570` | `static void test_no_js_no_navigation(void **state)` |
| `test_nomodule_fallback_for_untrusted_host` | function | `tests/test_tab.c:2807` | `static void test_nomodule_fallback_for_untrusted_host(void **state)` |
| `test_open_close` | function | `tests/test_tab.c:81` | `static void test_open_close(void **state)` |
| `test_open_null` | function | `tests/test_tab.c:91` | `static void test_open_null(void **state)` |
| `test_other_worker_calls_wait_for_the_job_and_discard_its_view` | function | `tests/test_tab.c:2967` | `static void test_other_worker_calls_wait_for_the_job_and_discard_its_view(void **state)` |
| `test_post_load_network_time_is_bounded_per_operation` | function | `tests/test_tab.c:2892` | `static void test_post_load_network_time_is_bounded_per_operation(void **state)` |
| `test_postmessage_absent_for_untrusted_host` | function | `tests/test_tab.c:2555` | `static void test_postmessage_absent_for_untrusted_host(void **state)` |
| `test_reload_replaces_page` | function | `tests/test_tab.c:3187` | `static void test_reload_replaces_page(void **state)` |
| `test_repl_net_lists_page_requests` | function | `tests/test_tab.c:2286` | `static void test_repl_net_lists_page_requests(void **state)` |
| `test_repl_panels_tree_styles_box` | function | `tests/test_tab.c:2306` | `static void test_repl_panels_tree_styles_box(void **state)` |
| `test_self_postmessage_and_document_domain_trusted` | function | `tests/test_tab.c:2512` | `static void test_self_postmessage_and_document_domain_trusted(void **state)` |
| `test_subreq_permitted_pure` | function | `tests/test_tab.c:3124` | `static void test_subreq_permitted_pure(void **state)` |
| `test_tick_fires_delayed_timer` | function | `tests/test_tab.c:777` | `static void test_tick_fires_delayed_timer(void **state)` |
| `test_tick_interval_rearms` | function | `tests/test_tab.c:814` | `static void test_tick_interval_rearms(void **state)` |
| `test_timer_navigation_reaches_parent` | function | `tests/test_tab.c:2354` | `static void test_timer_navigation_reaches_parent(void **state)` |
| `test_websocket_absent_for_untrusted_host` | function | `tests/test_tab.c:2607` | `static void test_websocket_absent_for_untrusted_host(void **state)` |
| `test_websocket_ops_and_events_cross_the_worker` | function | `tests/test_tab.c:2580` | `static void test_websocket_ops_and_events_cross_the_worker(void **state)` |
| `test_window_open_absent_for_untrusted_host` | function | `tests/test_tab.c:2483` | `static void test_window_open_absent_for_untrusted_host(void **state)` |
| `test_window_open_on_gesture_for_trusted_host` | function | `tests/test_tab.c:2462` | `static void test_window_open_on_gesture_for_trusted_host(void **state)` |
| `test_worker_args_malformed` | function | `tests/test_tab.c:3425` | `static void test_worker_args_malformed(void **state)` |
| `test_worker_args_not_worker` | function | `tests/test_tab.c:3418` | `static void test_worker_args_not_worker(void **state)` |
| `test_worker_args_null_safe` | function | `tests/test_tab.c:3440` | `static void test_worker_args_null_safe(void **state)` |
| `test_worker_args_valid` | function | `tests/test_tab.c:3409` | `static void test_worker_args_valid(void **state)` |
| `test_worker_deep_recursion_and_runaway` | function | `tests/test_tab.c:1620` | `static void test_worker_deep_recursion_and_runaway(void **state)` |
| `test_xhr_undefined_when_net_not_allowed` | function | `tests/test_tab.c:1763` | `static void test_xhr_undefined_when_net_not_allowed(void **state)` |
| `test_xhr_works_when_net_allowed` | function | `tests/test_tab.c:1739` | `static void test_xhr_works_when_net_allowed(void **state)` |
| `tick_page` | function | `tests/test_tab.c:2840` | `static const pv_run *tick_page(const char *html, size_t len, tab **t, tab_page *p2,              ...` |
| `view_find_text` | function | `tests/test_tab.c:1959` | `static const pv_run *view_find_text(const pv_view *v, const char *needle)` |
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
| `assert_line` | function | `tests/test_ui.c:21` | `static void assert_line(const char *text, const ui_layout *lay, size_t n,                        ...` |
| `main` | function | `tests/test_ui.c:146` | `int main(void)` |
| `test_clamp_scroll` | function | `tests/test_ui.c:114` | `static void test_clamp_scroll(void **state)` |
| `test_layout_free_null_and_double` | function | `tests/test_ui.c:122` | `static void test_layout_free_null_and_double(void **state)` |
| `test_lazy_near_viewport` | function | `tests/test_ui.c:133` | `static void test_lazy_near_viewport(void **state)` |
| `test_wrap_breaks_at_space` | function | `tests/test_ui.c:54` | `static void test_wrap_breaks_at_space(void **state)` |
| `test_wrap_does_not_split_utf8` | function | `tests/test_ui.c:77` | `static void test_wrap_does_not_split_utf8(void **state)` |
| `test_wrap_empty` | function | `tests/test_ui.c:36` | `static void test_wrap_empty(void **state)` |
| `test_wrap_hard_breaks_long_word` | function | `tests/test_ui.c:65` | `static void test_wrap_hard_breaks_long_word(void **state)` |
| `test_wrap_null_args` | function | `tests/test_ui.c:29` | `static void test_wrap_null_args(void **state)` |
| `test_wrap_respects_newline` | function | `tests/test_ui.c:91` | `static void test_wrap_respects_newline(void **state)` |
| `test_wrap_short_single_line` | function | `tests/test_ui.c:44` | `static void test_wrap_short_single_line(void **state)` |
| `test_wrap_zero_cols_is_sanitised` | function | `tests/test_ui.c:102` | `static void test_wrap_zero_cols_is_sanitised(void **state)` |
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
| `_DEFAULT_SOURCE` | macro | `tests/test_wl_guard.c:1` | `#define _DEFAULT_SOURCE` |
| `main` | function | `tests/test_wl_guard.c:55` | `int main(void)` |
| `ms_since` | function | `tests/test_wl_guard.c:13` | `static long ms_since(const struct timespec *a)` |
| `test_guard_starts_idles_and_stops_promptly` | function | `tests/test_wl_guard.c:21` | `static void test_guard_starts_idles_and_stops_promptly(void **state)` |
| `test_guard_survives_peer_hangup` | function | `tests/test_wl_guard.c:41` | `static void test_guard_survives_peer_hangup(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_ws_hub.c:7` | `#define _POSIX_C_SOURCE` |
| `emit` | function | `tests/test_ws_hub.c:21` | `static void emit(void *ctx, int id, int kind, int code, const char *data, size_t len)` |
| `main` | function | `tests/test_ws_hub.c:142` | `int main(void)` |
| `n` | type_alias | `tests/test_ws_hub.c:18` | `typedef struct rec { int n;` |
| `rec` | struct | `tests/test_ws_hub.c:19` | `` |
| `test_close_all_drops_late_results` | function | `tests/test_ws_hub.c:85` | `static void test_close_all_drops_late_results(void **state)` |
| `test_close_cancels_pending_open` | function | `tests/test_ws_hub.c:102` | `static void test_close_cancels_pending_open(void **state)` |
| `test_duplicate_and_capacity` | function | `tests/test_ws_hub.c:64` | `static void test_duplicate_and_capacity(void **state)` |
| `test_failed_open_reports_error_then_close` | function | `tests/test_ws_hub.c:47` | `static void test_failed_open_reports_error_then_close(void **state)` |
| `test_free_with_pending_open` | function | `tests/test_ws_hub.c:132` | `static void test_free_with_pending_open(void **state)` |
| `test_new_free` | function | `tests/test_ws_hub.c:34` | `static void test_new_free(void **state)` |
| `test_send_unknown_and_readable_unknown` | function | `tests/test_ws_hub.c:115` | `static void test_send_unknown_and_readable_unknown(void **state)` |
| `wait_notify` | function | `tests/test_ws_hub.c:28` | `static void wait_notify(wh_hub *h, rec *r)` |
| `main` | function | `tests/test_zoom.c:112` | `int main(void)` |
| `test_apply_scales_and_floors` | function | `tests/test_zoom.c:100` | `static void test_apply_scales_and_floors(void **state)` |
| `test_clamp_bounds` | function | `tests/test_zoom.c:17` | `static void test_clamp_bounds(void **state)` |
| `test_ends_are_idempotent` | function | `tests/test_zoom.c:59` | `static void test_ends_are_idempotent(void **state)` |
| `test_repeated_in_reaches_max` | function | `tests/test_zoom.c:67` | `static void test_repeated_in_reaches_max(void **state)` |
| `test_repeated_out_reaches_min` | function | `tests/test_zoom.c:79` | `static void test_repeated_out_reaches_min(void **state)` |
| `test_reset_is_default` | function | `tests/test_zoom.c:27` | `static void test_reset_is_default(void **state)` |
| `test_scale_factor` | function | `tests/test_zoom.c:91` | `static void test_scale_factor(void **state)` |
| `test_step_snaps_off_ladder` | function | `tests/test_zoom.c:49` | `static void test_step_snaps_off_ladder(void **state)` |
| `test_zoom_in_steps_ladder` | function | `tests/test_zoom.c:33` | `static void test_zoom_in_steps_ladder(void **state)` |
| `test_zoom_out_steps_ladder` | function | `tests/test_zoom.c:41` | `static void test_zoom_out_steps_ladder(void **state)` |
| `bands` | function | `tools/fbench.py:83` | `def bands(fd, ff, band)` |
| `load_baseline` | function | `tools/fbench.py:53` | `def load_baseline()` |
| `load_current` | function | `tools/fbench.py:66` | `def load_current()` |
| `load_timing_baseline` | function | `tools/fbench.py:158` | `def load_timing_baseline()` |
| `luma` | function | `tools/fbench.py:79` | `def luma(img)` |
| `main` | function | `tools/fbench.py:227` | `def main()` |
| `publish_readme` | function | `tools/fbench.py:114` | `def publish_readme(name, score)` |
| `publish_timing` | function | `tools/fbench.py:171` | `def publish_timing(rows)` |
| `run_timer` | function | `tools/fbench.py:140` | `def run_timer(tool, pages, runs)` |
| `sbs` | function | `tools/fbench.py:95` | `def sbs(name, start, nrows)` |
| `timing` | function | `tools/fbench.py:193` | `def timing(names, runs, readme)` |
| `_append_probe` | function | `tools/ffgeom.py:254` | `def _append_probe(src, script)` |
| `_word_reader` | function | `tools/ffgeom.py:173` | `def _word_reader(path)` |
| `bit` | function | `tools/ffgeom.py:206` | `def bit(grid_row, cell, origin)` |
| `decode` | function | `tools/ffgeom.py:239` | `def decode(path)` |
| `height` | function | `tools/ffgeom.py:292` | `def height(path)` |
| `height_probe` | function | `tools/ffgeom.py:279` | `def height_probe(page, out_html)` |
| `load_rows` | function | `tools/ffgeom.py:116` | `def load_rows(path)` |
| `lum` | function | `tools/ffgeom.py:169` | `def lum(p)` |
| `lum_at` | function | `tools/ffgeom.py:181` | `def lum_at(x, y)` |
| `main` | function | `tools/ffgeom.py:301` | `def main(argv)` |
| `probe` | function | `tools/ffgeom.py:265` | `def probe(page, selector, out_html)` |
| `word` | function | `tools/ffgeom.py:209` | `def word(grid_row, origin)` |
| `main` | function | `tools/ffq.py:22` | `def main()` |
| `main` | function | `tools/ffshot.py:24` | `def main()` |
| `main` | function | `tools/fftime.py:38` | `def main()` |
| `_POSIX_C_SOURCE` | macro | `tools/gen_psl.c:15` | `#define _POSIX_C_SOURCE` |
| `ascii_lower` | function | `tools/gen_psl.c:55` | `static void ascii_lower(char *s)` |
| `cmp_str` | function | `tools/gen_psl.c:38` | `static int cmp_str(const void *a, const void *b)` |
| `emit` | function | `tools/gen_psl.c:61` | `static void emit(const char *name, vec *v)` |
| `main` | function | `tools/gen_psl.c:67` | `int main(int argc, char **argv)` |
| `sort_unique` | function | `tools/gen_psl.c:43` | `static void sort_unique(vec *v)` |
| `vec` | struct | `tools/gen_psl.c:21` | `` |
| `vec_push` | function | `tools/gen_psl.c:27` | `static void vec_push(vec *v, const char *s)` |
| `main` | function | `tools/guitime.py:92` | `def main()` |
| `one_run` | function | `tools/guitime.py:65` | `def one_run(binary, page, env, hosts_dir, tmp)` |
| `start_display` | function | `tools/guitime.py:34` | `def start_display(workdir)` |
| `find_modules` | function | `tools/mutate.py:107` | `def find_modules(root)` |
| `line_sites` | function | `tools/mutate.py:41` | `def line_sites(text)` |
| `main` | function | `tools/mutate.py:137` | `def main(argv)` |
| `mutate_line` | function | `tools/mutate.py:75` | `def mutate_line(line, op)` |
| `run_bin` | function | `tools/mutate.py:125` | `def run_bin(path)` |
| `run_make` | function | `tools/mutate.py:116` | `def run_make(root, target)` |
| `PD_COLS` | macro | `tools/pngdiff.c:57` | `#define PD_COLS` |
| `PD_INK_DELTA` | macro | `tools/pngdiff.c:63` | `#define PD_INK_DELTA` |
| `PD_ROWS` | macro | `tools/pngdiff.c:58` | `#define PD_ROWS` |
| `height` | type_alias | `tools/pngdiff.c:64` | `typedef struct pd_profile { uint32_t width, height;` |
| `main` | function | `tools/pngdiff.c:233` | `int main(int argc, char **argv)` |
| `pd_background` | function | `tools/pngdiff.c:147` | `static int pd_background(const char *path, double *out_bg)` |
| `pd_lum` | function | `tools/pngdiff.c:141` | `static double pd_lum(const png_byte *p)` |
| `pd_mae` | function | `tools/pngdiff.c:227` | `static double pd_mae(const double *a, const double *b, size_t n)` |
| `pd_profile` | struct | `tools/pngdiff.c:65` | `` |
| `pd_profile_of` | function | `tools/pngdiff.c:175` | `static int pd_profile_of(const char *path, pd_profile *out)` |
| `pd_reader` | struct | `tools/pngdiff.c:71` | `` |
| `pd_reader_close` | function | `tools/pngdiff.c:79` | `static void pd_reader_close(pd_reader *r)` |
| `pd_reader_open` | function | `tools/pngdiff.c:88` | `static int pd_reader_open(pd_reader *r, const char *path)` |
| `png_set_background` | function | `tools/pngdiff.c:116` | `png_set_background(r->png, &(png_color_16)` |
| `load_rows` | function | `tools/pngprof.py:41` | `def load_rows(path)` |
| `lum` | function | `tools/pngprof.py:95` | `def lum(p)` |
| `main` | function | `tools/pngprof.py:109` | `def main(argv)` |
| `render_glyph` | function | `tools/pngprof.py:99` | `def render_glyph(v)` |
| `main` | function | `tools/prune.py:21` | `def main()` |
| `expand_imports` | function | `tools/snapshot.py:32` | `def expand_imports(css, base, depth)` |
| `fetch` | function | `tools/snapshot.py:18` | `def fetch(url)` |
| `inline_css` | function | `tools/snapshot.py:49` | `def inline_css(html, base)` |
| `main` | function | `tools/snapshot.py:70` | `def main()` |
| `repl` | function | `tools/snapshot.py:35` | `def repl(m)` |
| `repl` | function | `tools/snapshot.py:50` | `def repl(m)` |
| `main` | function | `tools/snapshot_age.py:16` | `def main()` |

