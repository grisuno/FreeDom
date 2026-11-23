# Symbols (page 18 of 19)
Previous: [SYMBOLS_p17.md](SYMBOLS_p17.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `test_redirect_code_rejects_others` | function | `tests/test_secure_fetch.c:398` | `static void test_redirect_code_rejects_others(void **state)` |
| `test_resolve_absolute_https` | function | `tests/test_secure_fetch.c:472` | `static void test_resolve_absolute_https(void **state)` |
| `test_resolve_absolute_path` | function | `tests/test_secure_fetch.c:506` | `static void test_resolve_absolute_path(void **state)` |
| `test_resolve_null_args` | function | `tests/test_secure_fetch.c:530` | `static void test_resolve_null_args(void **state)` |
| `test_resolve_refuses_dangerous_schemes` | function | `tests/test_secure_fetch.c:487` | `static void test_resolve_refuses_dangerous_schemes(void **state)` |
| `test_resolve_refuses_http_downgrade` | function | `tests/test_secure_fetch.c:480` | `static void test_resolve_refuses_http_downgrade(void **state)` |
| `test_resolve_relative_path` | function | `tests/test_secure_fetch.c:518` | `static void test_resolve_relative_path(void **state)` |
| `test_resolve_scheme_relative` | function | `tests/test_secure_fetch.c:498` | `static void test_resolve_scheme_relative(void **state)` |
| `test_response_free_on_zeroed` | function | `tests/test_secure_fetch.c:541` | `static void test_response_free_on_zeroed(void **state)` |
| `test_response_free_releases_location` | function | `tests/test_secure_fetch.c:550` | `static void test_response_free_releases_location(void **state)` |
| `test_tls_accepts_13` | function | `tests/test_secure_fetch.c:126` | `static void test_tls_accepts_13(void **state)` |
| `test_tls_rejects_12` | function | `tests/test_secure_fetch.c:112` | `static void test_tls_rejects_12(void **state)` |
| `test_tls_rejects_older_and_garbage` | function | `tests/test_secure_fetch.c:117` | `static void test_tls_rejects_older_and_garbage(void **state)` |
| `test_url_accepts_https` | function | `tests/test_secure_fetch.c:104` | `static void test_url_accepts_https(void **state)` |
| `test_url_rejects_dangerous_schemes` | function | `tests/test_secure_fetch.c:94` | `static void test_url_rejects_dangerous_schemes(void **state)` |
| `test_url_rejects_null` | function | `tests/test_secure_fetch.c:84` | `static void test_url_rejects_null(void **state)` |
| `test_url_rejects_plain_http` | function | `tests/test_secure_fetch.c:89` | `static void test_url_rejects_plain_http(void **state)` |
| `test_user_agent_default_when_unset` | function | `tests/test_secure_fetch.c:57` | `static void test_user_agent_default_when_unset(void **state)` |
| `test_user_agent_uses_override` | function | `tests/test_secure_fetch.c:63` | `static void test_user_agent_uses_override(void **state)` |
| `test_ws_open_rejects_before_any_io` | function | `tests/test_secure_fetch.c:674` | `static void test_ws_open_rejects_before_any_io(void **state)` |
| `test_ws_url_check` | function | `tests/test_secure_fetch.c:662` | `static void test_ws_url_check(void **state)` |
| `check` | function | `tests/test_sha2.c:18` | `static void check(sha_alg a, const char *msg, size_t rep, const char *want)` |
| `hex` | function | `tests/test_sha2.c:14` | `static void hex(const uint8_t *d, size_t n, char *out)` |
| `main` | function | `tests/test_sha2.c:74` | `int main(void)` |
| `test_abc_vectors` | function | `tests/test_sha2.c:31` | `static void test_abc_vectors(void **state)` |
| `test_empty_and_long` | function | `tests/test_sha2.c:39` | `static void test_empty_and_long(void **state)` |
| `test_names_and_errors` | function | `tests/test_sha2.c:60` | `static void test_names_and_errors(void **state)` |
| `test_padding_boundaries` | function | `tests/test_sha2.c:52` | `static void test_padding_boundaries(void **state)` |
| `calls` | type_alias | `tests/test_sheet_cache.c:35` | `typedef struct matcher_log { int calls;` |
| `key_of` | function | `tests/test_sheet_cache.c:25` | `static shc_key key_of(const char *text, const css_media *m)` |
| `log_match` | function | `tests/test_sheet_cache.c:38` | `static int log_match(void *ctx, const struct css_sel *sel)` |
| `main` | function | `tests/test_sheet_cache.c:303` | `int main(void)` |
| `matcher_log` | struct | `tests/test_sheet_cache.c:36` | `` |
| `p_color` | function | `tests/test_sheet_cache.c:21` | `static int p_color(const shc_sheet *s)` |
| `stats_of` | function | `tests/test_sheet_cache.c:30` | `static shc_stats stats_of(const shc_cache *c)` |
| `test_a_bypassed_parse_does_not_evict_the_retained_entry` | function | `tests/test_sheet_cache.c:223` | `static void test_a_bypassed_parse_does_not_evict_the_retained_entry(void **state)` |
| `test_a_hit_replays_the_matcher_and_needs_the_same_answers` | function | `tests/test_sheet_cache.c:125` | `static void test_a_hit_replays_the_matcher_and_needs_the_same_answers(void **state)` |
| `test_a_reference_outlives_replacement_and_the_cache` | function | `tests/test_sheet_cache.c:253` | `static void test_a_reference_outlives_replacement_and_the_cache(void **state)` |
| `test_fails_closed_on_bad_arguments` | function | `tests/test_sheet_cache.c:279` | `static void test_fails_closed_on_bad_arguments(void **state)` |
| `test_matcher_presence_is_part_of_the_key` | function | `tests/test_sheet_cache.c:176` | `static void test_matcher_presence_is_part_of_the_key(void **state)` |
| `test_media_inputs_are_part_of_the_key` | function | `tests/test_sheet_cache.c:81` | `static void test_media_inputs_are_part_of_the_key(void **state)` |
| `test_no_cache_parses_without_retaining` | function | `tests/test_sheet_cache.c:267` | `static void test_no_cache_parses_without_retaining(void **state)` |
| `test_one_byte_of_text_changes_the_result` | function | `tests/test_sheet_cache.c:66` | `static void test_one_byte_of_text_changes_the_result(void **state)` |
| `test_oversized_text_is_parsed_but_not_retained` | function | `tests/test_sheet_cache.c:238` | `static void test_oversized_text_is_parsed_but_not_retained(void **state)` |
| `test_root_scope_is_part_of_the_key` | function | `tests/test_sheet_cache.c:107` | `static void test_root_scope_is_part_of_the_key(void **state)` |
| `test_same_key_is_a_hit_and_returns_the_same_sheet` | function | `tests/test_sheet_cache.c:45` | `static void test_same_key_is_a_hit_and_returns_the_same_sheet(void **state)` |
| `test_structural_root_selector_is_replayed_too` | function | `tests/test_sheet_cache.c:156` | `static void test_structural_root_selector_is_replayed_too(void **state)` |
| `test_too_many_matcher_questions_are_never_reused` | function | `tests/test_sheet_cache.c:192` | `static void test_too_many_matcher_questions_are_never_reused(void **state)` |
| `main` | function | `tests/test_shm_slots.c:42` | `int main(void)` |
| `test_alternates_and_never_paints_a_held_slot` | function | `tests/test_shm_slots.c:8` | `static void test_alternates_and_never_paints_a_held_slot(void **state)` |
| `test_release_of_unknown_or_idle_slot_is_ignored` | function | `tests/test_shm_slots.c:23` | `static void test_release_of_unknown_or_idle_slot_is_ignored(void **state)` |
| `test_repaint_before_commit_reuses_the_same_free_slot` | function | `tests/test_shm_slots.c:34` | `static void test_repaint_before_commit_reuses_the_same_free_slot(void **state)` |
| `main` | function | `tests/test_site_panel.c:218` | `int main(void)` |
| `pq_facts` | function | `tests/test_site_panel.c:11` | `static sp_facts pq_facts(void)` |
| `row` | function | `tests/test_site_panel.c:23` | `static const sp_row *row(const sp_panel *p, const char *label)` |
| `test_classical_weak_unverified` | function | `tests/test_site_panel.c:96` | `static void test_classical_weak_unverified(void **state)` |
| `test_hostile_host_sanitized` | function | `tests/test_site_panel.c:160` | `static void test_hostile_host_sanitized(void **state)` |
| `test_insecure_http` | function | `tests/test_site_panel.c:146` | `static void test_insecure_http(void **state)` |
| `test_layout_fits_and_hits` | function | `tests/test_site_panel.c:185` | `static void test_layout_fits_and_hits(void **state)` |
| `test_local_and_internal` | function | `tests/test_site_panel.c:124` | `static void test_local_and_internal(void **state)` |
| `test_pq_page` | function | `tests/test_site_panel.c:37` | `static void test_pq_page(void **state)` |
| `test_rejects_null` | function | `tests/test_site_panel.c:29` | `static void test_rejects_null(void **state)` |
| `test_trusted_site_offers_nothing` | function | `tests/test_site_panel.c:59` | `static void test_trusted_site_offers_nothing(void **state)` |
| `test_unknown_never_claims_pq` | function | `tests/test_site_panel.c:84` | `static void test_unknown_never_claims_pq(void **state)` |
| `test_unlistable_host_offers_nothing` | function | `tests/test_site_panel.c:73` | `static void test_unlistable_host_offers_nothing(void **state)` |
| `main` | function | `tests/test_smooth_scroll.c:99` | `int main(void)` |
| `test_clock_backwards_and_jump` | function | `tests/test_smooth_scroll.c:67` | `static void test_clock_backwards_and_jump(void **state)` |
| `test_ease_out_curve` | function | `tests/test_smooth_scroll.c:11` | `static void test_ease_out_curve(void **state)` |
| `test_non_finite_inputs_ignored` | function | `tests/test_smooth_scroll.c:79` | `static void test_non_finite_inputs_ignored(void **state)` |
| `test_retarget_accumulates_and_is_continuous` | function | `tests/test_smooth_scroll.c:27` | `static void test_retarget_accumulates_and_is_continuous(void **state)` |
| `test_upward_monotone_no_overshoot` | function | `tests/test_smooth_scroll.c:40` | `static void test_upward_monotone_no_overshoot(void **state)` |
| `test_zero_duration_and_same_target_jump` | function | `tests/test_smooth_scroll.c:54` | `static void test_zero_duration_and_same_target_jump(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_subreq_batch.c:2` | `#define _GNU_SOURCE` |
| `count_free` | function | `tests/test_subreq_batch.c:147` | `static void count_free(void *c)` |
| `main` | function | `tests/test_subreq_batch.c:178` | `int main(void)` |
| `mk` | function | `tests/test_subreq_batch.c:31` | `static sqb_req mk(const char *u)` |
| `slow_run` | function | `tests/test_subreq_batch.c:19` | `static int slow_run(void *ctx, const sqb_req *rq, sqb_res *out)` |
| `test_abandon_and_free_never_wait` | function | `tests/test_subreq_batch.c:151` | `static void test_abandon_and_free_never_wait(void **st)` |
| `test_full_batch_refuses_and_reset_reuses` | function | `tests/test_subreq_batch.c:76` | `static void test_full_batch_refuses_and_reset_reuses(void **st)` |
| `test_null_args_fail_closed` | function | `tests/test_subreq_batch.c:90` | `static void test_null_args_fail_closed(void **st)` |
| `test_refused_and_failed_keep_their_slot` | function | `tests/test_subreq_batch.c:61` | `static void test_refused_and_failed_keep_their_slot(void **st)` |
| `test_results_in_issue_order_and_overlap` | function | `tests/test_subreq_batch.c:33` | `static void test_results_in_issue_order_and_overlap(void **st)` |
| `test_thread_limit_is_respected` | function | `tests/test_subreq_batch.c:51` | `static void test_thread_limit_is_respected(void **st)` |
| `test_wait_ready_delivers_finished_out_of_issue_order` | function | `tests/test_subreq_batch.c:113` | `static void test_wait_ready_delivers_finished_out_of_issue_order(void **st)` |
| `varied_run` | function | `tests/test_subreq_batch.c:101` | `static int varied_run(void *ctx, const sqb_req *rq, sqb_res *out)` |
| `main` | function | `tests/test_svg_raster.c:111` | `int main(void)` |
| `pixel` | function | `tests/test_svg_raster.c:18` | `static uint32_t pixel(const img_pixels *px, uint32_t x, uint32_t y)` |
| `raster` | function | `tests/test_svg_raster.c:14` | `static img_status raster(const char *s, img_pixels *px)` |
| `test_garbage_fails_closed` | function | `tests/test_svg_raster.c:89` | `static void test_garbage_fails_closed(void **state)` |
| `test_huge_scales_down` | function | `tests/test_svg_raster.c:79` | `static void test_huge_scales_down(void **state)` |
| `test_large_svg_is_not_oversampled` | function | `tests/test_svg_raster.c:69` | `static void test_large_svg_is_not_oversampled(void **state)` |
| `test_rect_fills_red` | function | `tests/test_svg_raster.c:42` | `static void test_rect_fills_red(void **state)` |
| `test_sniff` | function | `tests/test_svg_raster.c:24` | `static void test_sniff(void **state)` |
| `test_text_is_skipped_not_fatal` | function | `tests/test_svg_raster.c:101` | `static void test_text_is_skipped_not_fatal(void **state)` |
| `test_viewbox_sets_size_and_transparent_bg` | function | `tests/test_svg_raster.c:56` | `static void test_viewbox_sets_size_and_transparent_bg(void **state)` |
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
| `CSS_PAGE` | macro | `tests/test_tab.c:2392` | `#define CSS_PAGE(HREF)` |
| `EXT_PAGE` | macro | `tests/test_tab.c:2265` | `#define EXT_PAGE(SRC)` |
| `LAZY_PAGE` | macro | `tests/test_tab.c:834` | `#define LAZY_PAGE(body_script)` |
| `XHR_PAGE` | macro | `tests/test_tab.c:2166` | `#define XHR_PAGE(URL)` |
| `_DEFAULT_SOURCE` | macro | `tests/test_tab.c:1` | `#define _DEFAULT_SOURCE` |
| `_POSIX_C_SOURCE` | macro | `tests/test_tab.c:15` | `#define _POSIX_C_SOURCE` |
| `console_find` | function | `tests/test_tab.c:1532` | `static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle)` |
| `cs_eval` | function | `tests/test_tab.c:2848` | `static void cs_eval(tab *t, const char *js, char *out, size_t outsz)` |
| `cs_open` | function | `tests/test_tab.c:2856` | `static void cs_open(tab **t, int net)` |
| `document` | function | `tests/test_tab.c:2688` | `* listener is on document (the React/jQuery-delegation shape);` |
| `expect_eval` | function | `tests/test_tab.c:73` | `static void expect_eval(tab *t, const char *js, const char *expected)` |
| `expect_eval` | function | `tests/test_tab.c:1848` | `expect_eval(f->t, "var fr=function(n)` |
| `expect_eval` | function | `tests/test_tab.c:1849` | `expect_eval(f->t, "var gr=function()` |
| `expect_eval` | function | `tests/test_tab.c:1952` | `expect_eval(t, "var n=net(), a=n.filter(function(e)` |
| `fixture` | struct | `tests/test_tab.c:50` | `` |
| `geom_load_and_measure` | function | `tests/test_tab.c:2748` | `static int geom_load_and_measure(int net, char *out, size_t outsz)` |
| `import_align` | function | `tests/test_tab.c:2465` | `static int import_align(const char *html, int prefers_dark)` |
| `load` | function | `tests/test_tab.c:2738` | `* table only for a trusted load (net granted: allow.conf AND js.conf);` |
| `load_js_page` | function | `tests/test_tab.c:2958` | `static void load_js_page(tab **out_t, const char *html, tab_page *p)` |
| `ls_load` | function | `tests/test_tab.c:3334` | `static void ls_load(int net, tab **t, tab_page *p)` |
| `main` | function | `tests/test_tab.c:4387` | `int main(int argc, char **argv)` |
| `module_page` | function | `tests/test_tab.c:3420` | `static const pv_run *module_page(int net, tab **t, tab_page *p, const char *needle)` |
| `ms_since` | function | `tests/test_tab.c:3567` | `static long ms_since(const struct timespec *a)` |
| `n` | type_alias | `tests/test_tab.c:2569` | `typedef struct sink_cap { int n;` |
| `netctx_free` | function | `tests/test_tab.c:2132` | `static void netctx_free(void *c)` |
| `node_of_text` | function | `tests/test_tab.c:4270` | `static dom_node_id node_of_text(const pv_view *v, const char *text)` |
| `open_page` | function | `tests/test_tab.c:3086` | `static void open_page(int net, tab **t, tab_page *p)` |
| `paragraph` | function | `tests/test_tab.c:222` | `* reserved 200x280 box and the alt flowed as a paragraph (jkanime tiles). */ static void test_loa...` |
| `read` | function | `tests/test_tab.c:3776` | `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */ static void tes...` |
| `script_host_fetch` | function | `tests/test_tab.c:2016` | `static int script_host_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `setup_loaded` | function | `tests/test_tab.c:52` | `static int setup_loaded(void **state)` |
| `sink_cap` | struct | `tests/test_tab.c:2569` | `` |
| `sink_capture` | function | `tests/test_tab.c:2571` | `static void sink_capture(void *ctx, const char *url,                          const char *body, s...` |
| `slow_fetch` | function | `tests/test_tab.c:1908` | `static int slow_fetch(void *ctx, const char *method, const char *url,                       const...` |
| `slow_tab` | function | `tests/test_tab.c:3556` | `static tab *slow_tab(void)` |
| `stub_css_fetch` | function | `tests/test_tab.c:2375` | `static int stub_css_fetch(void *ctx, const char *method, const char *url,                        ...` |
| `stub_fetch` | function | `tests/test_tab.c:1892` | `static int stub_fetch(void *ctx, const char *method, const char *url,                       const...` |
| `stub_import_fetch` | function | `tests/test_tab.c:2431` | `static int stub_import_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `stub_module_fetch` | function | `tests/test_tab.c:3382` | `static int stub_module_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `stub_script_fetch` | function | `tests/test_tab.c:2241` | `static int stub_script_fetch(void *ctx, const char *method, const char *url,                     ...` |
| `stub_slow_fetch` | function | `tests/test_tab.c:3514` | `static int stub_slow_fetch(void *ctx, const char *method, const char *url, const char *body,     ...` |
| `teardown` | function | `tests/test_tab.c:63` | `static int teardown(void **state)` |
| `test_ajax_after_load_reaches_the_gated_fetcher` | function | `tests/test_tab.c:3483` | `static void test_ajax_after_load_reaches_the_gated_fetcher(void **state)` |
| `test_anchor_query_push_fires_hashchange` | function | `tests/test_tab.c:4351` | `static void test_anchor_query_push_fires_hashchange(void **state)` |
| `test_anchor_query_resolves` | function | `tests/test_tab.c:4304` | `static void test_anchor_query_resolves(void **state)` |
| `test_async_subrequests_run_in_parallel` | function | `tests/test_tab.c:1927` | `static void test_async_subrequests_run_in_parallel(void **state)` |
| `test_async_tick_returns_at_once_and_delivers_through_eventfd` | function | `tests/test_tab.c:3573` | `static void test_async_tick_returns_at_once_and_delivers_through_eventfd(void **state)` |
| `test_binary_does_not_crash_parent` | function | `tests/test_tab.c:3854` | `static void test_binary_does_not_crash_parent(void **state)` |
| `test_boxdef_node_id_crosses_codec` | function | `tests/test_tab.c:2719` | `static void test_boxdef_node_id_crosses_codec(void **state)` |
| `test_child_death_survived` | function | `tests/test_tab.c:3869` | `static void test_child_death_survived(void **state)` |
| `test_click_bubbles_to_delegated_document_listener` | function | `tests/test_tab.c:2691` | `static void test_click_bubbles_to_delegated_document_listener(void **state)` |
| `test_click_handler_navigation_reaches_parent` | function | `tests/test_tab.c:2964` | `static void test_click_handler_navigation_reaches_parent(void **state)` |
| `test_click_reports_default_prevented` | function | `tests/test_tab.c:4278` | `static void test_click_reports_default_prevented(void **state)` |
| `test_click_runs_handler_and_returns_view` | function | `tests/test_tab.c:638` | `static void test_click_runs_handler_and_returns_view(void **state)` |
| `test_close_abandons_hung_request` | function | `tests/test_tab.c:2134` | `static void test_close_abandons_hung_request(void **state)` |
| `test_computed_style_follows_dom_mutation` | function | `tests/test_tab.c:2883` | `static void test_computed_style_follows_dom_mutation(void **state)` |
| `test_computed_style_is_inline_only_for_untrusted_host` | function | `tests/test_tab.c:2902` | `static void test_computed_style_is_inline_only_for_untrusted_host(void **state)` |
| `test_computed_style_reads_the_cascade_for_trusted_host` | function | `tests/test_tab.c:2864` | `static void test_computed_style_reads_the_cascade_for_trusted_host(void **state)` |
| `test_css_sink_ignores_non_css_body` | function | `tests/test_tab.c:2612` | `static void test_css_sink_ignores_non_css_body(void **state)` |
| `test_css_sink_observes_served_stylesheet` | function | `tests/test_tab.c:2586` | `static void test_css_sink_observes_served_stylesheet(void **state)` |
| `test_data_module_imports_absolute_https` | function | `tests/test_tab.c:3706` | `static void test_data_module_imports_absolute_https(void **state)` |
| `test_data_url_classic_script_runs_without_network` | function | `tests/test_tab.c:3636` | `static void test_data_url_classic_script_runs_without_network(void **state)` |
| `test_decode_image_data_url_in_sandbox` | function | `tests/test_tab.c:3985` | `static void test_decode_image_data_url_in_sandbox(void **state)` |
| `test_decode_image_data_url_null_args` | function | `tests/test_tab.c:4058` | `static void test_decode_image_data_url_null_args(void **state)` |
| `test_decode_image_in_sandbox` | function | `tests/test_tab.c:3929` | `static void test_decode_image_in_sandbox(void **state)` |
| `test_decode_image_null_args` | function | `tests/test_tab.c:3966` | `static void test_decode_image_null_args(void **state)` |
| `test_decode_image_rejects_junk` | function | `tests/test_tab.c:3951` | `static void test_decode_image_rejects_junk(void **state)` |
| `test_decode_svg_image_in_sandbox` | function | `tests/test_tab.c:4030` | `static void test_decode_svg_image_in_sandbox(void **state)` |
| `test_dynamic_import_from_classic_script_uses_document_base` | function | `tests/test_tab.c:3451` | `static void test_dynamic_import_from_classic_script_uses_document_base(void **state)` |
| `test_dynamic_script_from_dead_host_does_not_block` | function | `tests/test_tab.c:2030` | `static void test_dynamic_script_from_dead_host_does_not_block(void **state)` |
| `test_eval_captures_console_output` | function | `tests/test_tab.c:1689` | `static void test_eval_captures_console_output(void **state)` |
| `test_eval_exception` | function | `tests/test_tab.c:3797` | `static void test_eval_exception(void **state)` |
| `test_eval_no_network_or_cross_origin_api` | function | `tests/test_tab.c:1873` | `static void test_eval_no_network_or_cross_origin_api(void **state)` |
| `test_eval_persistent_state` | function | `tests/test_tab.c:3809` | `static void test_eval_persistent_state(void **state)` |
| `test_eval_sees_dom` | function | `tests/test_tab.c:1835` | `static void test_eval_sees_dom(void **state)` |
| `test_eval_sees_env` | function | `tests/test_tab.c:1856` | `static void test_eval_sees_env(void **state)` |
| `test_eval_without_load` | function | `tests/test_tab.c:3842` | `static void test_eval_without_load(void **state)` |
| `test_event_ipc_via_tab_eval` | function | `tests/test_tab.c:677` | `static void test_event_ipc_via_tab_eval(void **state)` |
| `test_event_navigation_is_policy_gated` | function | `tests/test_tab.c:3007` | `static void test_event_navigation_is_policy_gated(void **state)` |
| `test_external_css_applied_when_allowed` | function | `tests/test_tab.c:2408` | `static void test_external_css_applied_when_allowed(void **state)` |
| `test_external_css_bad_ctype_not_parsed` | function | `tests/test_tab.c:2651` | `static void test_external_css_bad_ctype_not_parsed(void **state)` |
| `test_external_css_blocked_host_refused` | function | `tests/test_tab.c:2669` | `static void test_external_css_blocked_host_refused(void **state)` |
| `test_external_css_skipped_without_grant` | function | `tests/test_tab.c:2632` | `static void test_external_css_skipped_without_grant(void **state)` |
| `test_external_css_survives_click_rederive` | function | `tests/test_tab.c:3727` | `static void test_external_css_survives_click_rederive(void **state)` |
| `test_external_script_bad_ctype_not_executed` | function | `tests/test_tab.c:2335` | `static void test_external_script_bad_ctype_not_executed(void **state)` |
| `test_external_script_blocked_host_refused` | function | `tests/test_tab.c:2352` | `static void test_external_script_blocked_host_refused(void **state)` |
| `test_external_script_document_order` | function | `tests/test_tab.c:2288` | `static void test_external_script_document_order(void **state)` |
| `test_external_script_executes_when_net_allowed` | function | `tests/test_tab.c:2271` | `static void test_external_script_executes_when_net_allowed(void **state)` |
| `test_external_script_skipped_without_net` | function | `tests/test_tab.c:2311` | `static void test_external_script_skipped_without_net(void **state)` |
| `test_first_visit_trusted_host_can_set_cookie` | function | `tests/test_tab.c:1363` | `static void test_first_visit_trusted_host_can_set_cookie(void **state)` |
| `test_focus_ipc_round_trip` | function | `tests/test_tab.c:777` | `static void test_focus_ipc_round_trip(void **state)` |
| `test_frames_absent_for_untrusted_host` | function | `tests/test_tab.c:3308` | `static void test_frames_absent_for_untrusted_host(void **state)` |
| `test_frames_cross_the_worker` | function | `tests/test_tab.c:3271` | `static void test_frames_cross_the_worker(void **state)` |
| `test_free_null_and_double` | function | `tests/test_tab.c:3895` | `static void test_free_null_and_double(void **state)` |
| `test_geometry_never_reaches_untrusted_page` | function | `tests/test_tab.c:2834` | `static void test_geometry_never_reaches_untrusted_page(void **state)` |
| `test_geometry_reaches_trusted_page` | function | `tests/test_tab.c:2826` | `static void test_geometry_reaches_trusted_page(void **state)` |
| `test_history_ops_reach_parent_and_popstate_returns` | function | `tests/test_tab.c:3035` | `static void test_history_ops_reach_parent_and_popstate_returns(void **state)` |
| `test_identity_override_reaches_worker` | function | `tests/test_tab.c:1403` | `static void test_identity_override_reaches_worker(void **state)` |
| `test_import_cycle_bounded` | function | `tests/test_tab.c:2499` | `static void test_import_cycle_bounded(void **state)` |
| `test_import_from_inline_style` | function | `tests/test_tab.c:2514` | `static void test_import_from_inline_style(void **state)` |
| `test_import_map_resolves_bare_specifier` | function | `tests/test_tab.c:3615` | `static void test_import_map_resolves_bare_specifier(void **state)` |
| `test_import_media_gated` | function | `tests/test_tab.c:2492` | `static void test_import_media_gated(void **state)` |
| `test_import_needs_css_grant` | function | `tests/test_tab.c:2551` | `static void test_import_needs_css_grant(void **state)` |
| `test_import_resolved_against_sheet` | function | `tests/test_tab.c:2484` | `static void test_import_resolved_against_sheet(void **state)` |
| `test_import_unbalanced_dropped` | function | `tests/test_tab.c:2507` | `static void test_import_unbalanced_dropped(void **state)` |
| `test_indexeddb_only_for_trusted_host` | function | `tests/test_tab.c:1384` | `static void test_indexeddb_only_for_trusted_host(void **state)` |
| `test_js_navigation_relative_resolved` | function | `tests/test_tab.c:1755` | `static void test_js_navigation_relative_resolved(void **state)` |
| `test_js_navigation_unsafe_is_blocked` | function | `tests/test_tab.c:1774` | `static void test_js_navigation_unsafe_is_blocked(void **state)` |
| `test_lazy_script_src_and_import_after_load` | function | `tests/test_tab.c:3494` | `static void test_lazy_script_src_and_import_after_load(void **state)` |
| `test_lazy_tick_after_discarded_result_sends_view` | function | `tests/test_tab.c:953` | `static void test_lazy_tick_after_discarded_result_sends_view(void **state)` |
| `test_lazy_tick_after_viewless_mutation_sends_view` | function | `tests/test_tab.c:930` | `static void test_lazy_tick_after_viewless_mutation_sends_view(void **state)` |
| `test_lazy_tick_with_mutation_sends_view` | function | `tests/test_tab.c:892` | `static void test_lazy_tick_with_mutation_sends_view(void **state)` |
| `test_lazy_tick_without_mutation_sends_no_view` | function | `tests/test_tab.c:859` | `static void test_lazy_tick_without_mutation_sends_no_view(void **state)` |
| `test_load_basic` | function | `tests/test_tab.c:145` | `static void test_load_basic(void **state)` |
| `test_load_captures_console_and_error` | function | `tests/test_tab.c:1542` | `static void test_load_captures_console_and_error(void **state)` |
| `test_load_carries_author_color` | function | `tests/test_tab.c:253` | `static void test_load_carries_author_color(void **state)` |
| `test_load_carries_box_decoration` | function | `tests/test_tab.c:1048` | `static void test_load_carries_box_decoration(void **state)` |
| `test_load_carries_box_tree` | function | `tests/test_tab.c:1084` | `static void test_load_carries_box_tree(void **state)` |
| `test_load_carries_flex_item` | function | `tests/test_tab.c:280` | `static void test_load_carries_flex_item(void **state)` |
| `test_load_carries_flex_wrap_align_row_gap` | function | `tests/test_tab.c:367` | `static void test_load_carries_flex_wrap_align_row_gap(void **state)` |
| `test_load_carries_float` | function | `tests/test_tab.c:442` | `static void test_load_carries_float(void **state)` |
| `test_load_carries_fontface` | function | `tests/test_tab.c:407` | `static void test_load_carries_fontface(void **state)` |
| `test_load_carries_input_box_and_clip` | function | `tests/test_tab.c:1171` | `static void test_load_carries_input_box_and_clip(void **state)` |
| `test_load_carries_node_id` | function | `tests/test_tab.c:569` | `static void test_load_carries_node_id(void **state)` |
| `test_load_carries_oof_flag` | function | `tests/test_tab.c:603` | `static void test_load_carries_oof_flag(void **state)` |
| `test_load_carries_visibility_overflow_cursor_and_text_wrap` | function | `tests/test_tab.c:485` | `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` |
| `test_load_document_fonts_stub` | function | `tests/test_tab.c:1653` | `static void test_load_document_fonts_stub(void **state)` |
| `test_load_element_wrapper_idioms` | function | `tests/test_tab.c:1623` | `static void test_load_element_wrapper_idioms(void **state)` |
| `test_load_error_carries_location` | function | `tests/test_tab.c:1597` | `static void test_load_error_carries_location(void **state)` |
| `test_load_ex_builds_dom_and_fires_onload` | function | `tests/test_tab.c:1453` | `static void test_load_ex_builds_dom_and_fires_onload(void **state)` |
| `test_load_ex_inner_html_renders` | function | `tests/test_tab.c:1481` | `static void test_load_ex_inner_html_renders(void **state)` |
| `test_load_ex_noscript_hidden_with_js` | function | `tests/test_tab.c:1285` | `static void test_load_ex_noscript_hidden_with_js(void **state)` |
| `test_load_ex_prescript_view_rebuilt_when_dom_shrinks` | function | `tests/test_tab.c:1264` | `static void test_load_ex_prescript_view_rebuilt_when_dom_shrinks(void **state)` |
| `test_load_full_location_is_real` | function | `tests/test_tab.c:1718` | `static void test_load_full_location_is_real(void **state)` |
| `test_load_isolates_script_errors` | function | `tests/test_tab.c:1569` | `static void test_load_isolates_script_errors(void **state)` |
| `test_load_no_session_cookies_when_untrusted` | function | `tests/test_tab.c:1431` | `static void test_load_no_session_cookies_when_untrusted(void **state)` |
| `test_load_null_and_too_large` | function | `tests/test_tab.c:1810` | `static void test_load_null_and_too_large(void **state)` |
| `test_load_returns_image_run` | function | `tests/test_tab.c:189` | `static void test_load_returns_image_run(void **state)` |
| `test_load_returns_view_with_link` | function | `tests/test_tab.c:162` | `static void test_load_returns_view_with_link(void **state)` |
| `test_load_strips_script` | function | `tests/test_tab.c:1217` | `static void test_load_strips_script(void **state)` |
| `test_load_view_codec_full_roundtrip` | function | `tests/test_tab.c:4118` | `static void test_load_view_codec_full_roundtrip(void **state)` |
| `test_load_without_js_has_empty_console` | function | `tests/test_tab.c:1673` | `static void test_load_without_js_has_empty_console(void **state)` |
| `test_local_storage_never_seeded_for_untrusted` | function | `tests/test_tab.c:3370` | `static void test_local_storage_never_seeded_for_untrusted(void **state)` |
| `test_local_storage_seeded_and_collected_for_trusted` | function | `tests/test_tab.c:3348` | `static void test_local_storage_seeded_and_collected_for_trusted(void **state)` |
| `test_long_data_module_runs_whole` | function | `tests/test_tab.c:3656` | `static void test_long_data_module_runs_whole(void **state)` |
| `test_module_scripts_run_for_trusted_host` | function | `tests/test_tab.c:3429` | `static void test_module_scripts_run_for_trusted_host(void **state)` |
| `test_module_src_is_a_url_and_data_modules_run` | function | `tests/test_tab.c:3681` | `static void test_module_src_is_a_url_and_data_modules_run(void **state)` |
| `test_mouse_ipc_round_trip` | function | `tests/test_tab.c:732` | `static void test_mouse_ipc_round_trip(void **state)` |
| `test_no_js_no_navigation` | function | `tests/test_tab.c:1796` | `static void test_no_js_no_navigation(void **state)` |
| `test_nomodule_fallback_for_untrusted_host` | function | `tests/test_tab.c:3438` | `static void test_nomodule_fallback_for_untrusted_host(void **state)` |
| `test_open_close` | function | `tests/test_tab.c:84` | `static void test_open_close(void **state)` |
| `test_open_null` | function | `tests/test_tab.c:138` | `static void test_open_null(void **state)` |
| `test_other_worker_calls_wait_for_the_job_and_discard_its_view` | function | `tests/test_tab.c:3598` | `static void test_other_worker_calls_wait_for_the_job_and_discard_its_view(void **state)` |
| `test_parser_async_script_does_not_block` | function | `tests/test_tab.c:2070` | `static void test_parser_async_script_does_not_block(void **state)` |
| `test_post_load_network_time_is_bounded_per_operation` | function | `tests/test_tab.c:3523` | `static void test_post_load_network_time_is_bounded_per_operation(void **state)` |
| `test_postmessage_absent_for_untrusted_host` | function | `tests/test_tab.c:3186` | `static void test_postmessage_absent_for_untrusted_host(void **state)` |
| `test_prewarm_dead_spare_falls_back` | function | `tests/test_tab.c:116` | `static void test_prewarm_dead_spare_falls_back(void **state)` |
| `test_prewarm_is_consumed_by_open` | function | `tests/test_tab.c:96` | `static void test_prewarm_is_consumed_by_open(void **state)` |
| `test_reload_replaces_page` | function | `tests/test_tab.c:3818` | `static void test_reload_replaces_page(void **state)` |
| `test_repl_net_lists_page_requests` | function | `tests/test_tab.c:2917` | `static void test_repl_net_lists_page_requests(void **state)` |
| `test_repl_panels_tree_styles_box` | function | `tests/test_tab.c:2937` | `static void test_repl_panels_tree_styles_box(void **state)` |
| `test_self_postmessage_and_document_domain_trusted` | function | `tests/test_tab.c:3143` | `static void test_self_postmessage_and_document_domain_trusted(void **state)` |
| `test_sheet_url_resolved_against_sheet` | function | `tests/test_tab.c:2532` | `static void test_sheet_url_resolved_against_sheet(void **state)` |
| `test_shutdown_spare_is_safe_without_one` | function | `tests/test_tab.c:131` | `static void test_shutdown_spare_is_safe_without_one(void **state)` |
| `test_slow_async_request_does_not_hold_first_view` | function | `tests/test_tab.c:1973` | `static void test_slow_async_request_does_not_hold_first_view(void **state)` |
| `test_subreq_permitted_pure` | function | `tests/test_tab.c:3755` | `static void test_subreq_permitted_pure(void **state)` |
| `test_tick_default_always_carries_view` | function | `tests/test_tab.c:839` | `static void test_tick_default_always_carries_view(void **state)` |
| `test_tick_fires_delayed_timer` | function | `tests/test_tab.c:981` | `static void test_tick_fires_delayed_timer(void **state)` |
| `test_tick_interval_rearms` | function | `tests/test_tab.c:1018` | `static void test_tick_interval_rearms(void **state)` |
| `test_timer_navigation_reaches_parent` | function | `tests/test_tab.c:2985` | `static void test_timer_navigation_reaches_parent(void **state)` |
| `test_view_ids_survive_script_insertion` | function | `tests/test_tab.c:2789` | `static void test_view_ids_survive_script_insertion(void **state)` |
| `test_websocket_absent_for_untrusted_host` | function | `tests/test_tab.c:3238` | `static void test_websocket_absent_for_untrusted_host(void **state)` |
| `test_websocket_ops_and_events_cross_the_worker` | function | `tests/test_tab.c:3211` | `static void test_websocket_ops_and_events_cross_the_worker(void **state)` |
| `test_window_open_absent_for_untrusted_host` | function | `tests/test_tab.c:3114` | `static void test_window_open_absent_for_untrusted_host(void **state)` |
| `test_window_open_on_gesture_for_trusted_host` | function | `tests/test_tab.c:3093` | `static void test_window_open_on_gesture_for_trusted_host(void **state)` |
| `test_without_async_fetcher_load_waits_for_all` | function | `tests/test_tab.c:2109` | `static void test_without_async_fetcher_load_waits_for_all(void **state)` |
| `test_worker_args_malformed` | function | `tests/test_tab.c:4087` | `static void test_worker_args_malformed(void **state)` |
| `test_worker_args_not_worker` | function | `tests/test_tab.c:4080` | `static void test_worker_args_not_worker(void **state)` |
| `test_worker_args_null_safe` | function | `tests/test_tab.c:4102` | `static void test_worker_args_null_safe(void **state)` |
| `test_worker_args_valid` | function | `tests/test_tab.c:4071` | `static void test_worker_args_valid(void **state)` |
| `test_worker_deep_recursion_and_runaway` | function | `tests/test_tab.c:1846` | `static void test_worker_deep_recursion_and_runaway(void **state)` |
| `test_xhr_undefined_when_net_not_allowed` | function | `tests/test_tab.c:2201` | `static void test_xhr_undefined_when_net_not_allowed(void **state)` |
| `test_xhr_works_when_net_allowed` | function | `tests/test_tab.c:2173` | `static void test_xhr_works_when_net_allowed(void **state)` |
| `tick_page` | function | `tests/test_tab.c:3471` | `static const pv_run *tick_page(const char *html, size_t len, tab **t, tab_page *p2,              ...` |
| `view_find_text` | function | `tests/test_tab.c:2397` | `static const pv_run *view_find_text(const pv_view *v, const char *needle)` |
| `view_has_bg` | function | `tests/test_tab.c:2524` | `static int view_has_bg(const pv_view *v, const char *url)` |
| `view_has_text` | function | `tests/test_tab.c:826` | `static int view_has_text(const pv_view *v, const char *want)` |
| `EPS` | macro | `tests/test_table_layout.c:11` | `#define EPS` |
| `assert_near` | function | `tests/test_table_layout.c:13` | `static void assert_near(double got, double want)` |
| `main` | function | `tests/test_table_layout.c:235` | `int main(void)` |
| `test_auto_table_takes_max_content` | function | `tests/test_table_layout.c:18` | `static void test_auto_table_takes_max_content(void **state)` |
| `test_declared_cell_width` | function | `tests/test_table_layout.c:141` | `static void test_declared_cell_width(void **state)` |
| `test_declared_table_width_distributes_surplus` | function | `tests/test_table_layout.c:32` | `static void test_declared_table_width_distributes_surplus(void **state)` |
| `test_declared_width_never_below_min` | function | `tests/test_table_layout.c:130` | `static void test_declared_width_never_below_min(void **state)` |
| `test_fail_closed` | function | `tests/test_table_layout.c:204` | `static void test_fail_closed(void **state)` |
| `test_gap_counts` | function | `tests/test_table_layout.c:115` | `static void test_gap_counts(void **state)` |
| `test_intrinsic` | function | `tests/test_table_layout.c:191` | `static void test_intrinsic(void **state)` |
| `test_percent_columns` | function | `tests/test_table_layout.c:155` | `static void test_percent_columns(void **state)` |
| `test_span_narrower_is_inert` | function | `tests/test_table_layout.c:94` | `static void test_span_narrower_is_inert(void **state)` |
| `test_span_over_empty_columns_splits_evenly` | function | `tests/test_table_layout.c:105` | `static void test_span_over_empty_columns_splits_evenly(void **state)` |
| `test_surplus_with_no_auto_column` | function | `tests/test_table_layout.c:44` | `static void test_surplus_with_no_auto_column(void **state)` |
| `main` | function | `tests/test_text_case.c:73` | `int main(void)` |
| `test_smallcaps_runs` | function | `tests/test_text_case.c:55` | `static void test_smallcaps_runs(void **state)` |
| `test_transform_keeps_length` | function | `tests/test_text_case.c:33` | `static void test_transform_keeps_length(void **state)` |
| `test_upper_lower_ascii_latin` | function | `tests/test_text_case.c:10` | `static void test_upper_lower_ascii_latin(void **state)` |
| `fake_cover` | function | `tests/test_text_shape.c:490` | `static int fake_cover(unsigned cp, void *ctx)` |
| `inked_pixels` | function | `tests/test_text_shape.c:149` | `static int inked_pixels(cairo_surface_t *s)` |
| `main` | function | `tests/test_text_shape.c:557` | `int main(void)` |
| `read_host_font` | function | `tests/test_text_shape.c:202` | `static unsigned char *read_host_font(const char *path, size_t *out_n)` |
| `set_installed` | function | `tests/test_text_shape.c:413` | `static int set_installed(const char *name, void *ctx)` |
| `table_resolve` | function | `tests/test_text_shape.c:383` | `static int table_resolve(const char *name, char *out, size_t cap, void *ctx)` |
| `teardown` | function | `tests/test_text_shape.c:465` | `static int teardown(void **state)` |
| `test_determinism` | function | `tests/test_text_shape.c:95` | `static void test_determinism(void **state)` |
| `test_draw_paints` | function | `tests/test_text_shape.c:133` | `static void test_draw_paints(void **state)` |
| `test_empty_slice_is_ok` | function | `tests/test_text_shape.c:60` | `static void test_empty_slice_is_ok(void **state)` |
| `test_face_generation_moves_with_faces` | function | `tests/test_text_shape.c:535` | `static void test_face_generation_moves_with_faces(void **state)` |
| `test_generic_keywords` | function | `tests/test_text_shape.c:371` | `static void test_generic_keywords(void **state)` |
| `test_local_handle_real_fontconfig` | function | `tests/test_text_shape.c:444` | `static void test_local_handle_real_fontconfig(void **state)` |
| `test_measure_matches_shape` | function | `tests/test_text_shape.c:111` | `static void test_measure_matches_shape(void **state)` |
| `test_measure_uses_fallback_face` | function | `tests/test_text_shape.c:522` | `static void test_measure_uses_fallback_face(void **state)` |
| `test_null_and_bad_inputs` | function | `tests/test_text_shape.c:30` | `static void test_null_and_bad_inputs(void **state)` |
| `test_overflow_cap` | function | `tests/test_text_shape.c:123` | `static void test_overflow_cap(void **state)` |
| `test_pick_family_strong_vs_weak` | function | `tests/test_text_shape.c:420` | `static void test_pick_family_strong_vs_weak(void **state)` |
| `test_pick_from_list_order_and_generic_stop` | function | `tests/test_text_shape.c:393` | `static void test_pick_from_list_order_and_generic_stop(void **state)` |
| `test_segment_runs` | function | `tests/test_text_shape.c:497` | `static void test_segment_runs(void **state)` |
| `test_shape_ascii` | function | `tests/test_text_shape.c:73` | `static void test_shape_ascii(void **state)` |
| `test_uncovered_pua_draws_nothing` | function | `tests/test_text_shape.c:161` | `static void test_uncovered_pua_draws_nothing(void **state)` |
| `test_webfont_optical_size` | function | `tests/test_text_shape.c:281` | `static void test_webfont_optical_size(void **state)` |
| `test_webfont_register_find_clear` | function | `tests/test_text_shape.c:323` | `static void test_webfont_register_find_clear(void **state)` |
| `test_webfont_rejects_bad_input` | function | `tests/test_text_shape.c:179` | `static void test_webfont_rejects_bad_input(void **state)` |
| `test_webfont_variable_weight` | function | `tests/test_text_shape.c:253` | `static void test_webfont_variable_weight(void **state)` |
| `test_webfont_woff2_container` | function | `tests/test_text_shape.c:241` | `static void test_webfont_woff2_container(void **state)` |
| `test_webfont_woff_container` | function | `tests/test_text_shape.c:246` | `static void test_webfont_woff_container(void **state)` |
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
| `main` | function | `tests/test_url.c:743` | `int main(void)` |
| `test_authority_len` | function | `tests/test_url.c:86` | `static void test_authority_len(void **state)` |
| `test_extract_userinfo_at_authority_start` | function | `tests/test_url.c:619` | `static void test_extract_userinfo_at_authority_start(void **state)` |
| `test_extract_userinfo_basic` | function | `tests/test_url.c:546` | `static void test_extract_userinfo_basic(void **state)` |
| `test_extract_userinfo_empty_password` | function | `tests/test_url.c:645` | `static void test_extract_userinfo_empty_password(void **state)` |
| `test_extract_userinfo_https_subresource_no_auth` | function | `tests/test_url.c:596` | `static void test_extract_userinfo_https_subresource_no_auth(void **state)` |
| `test_extract_userinfo_no_at_sign` | function | `tests/test_url.c:632` | `static void test_extract_userinfo_no_at_sign(void **state)` |
| `test_extract_userinfo_no_userinfo` | function | `tests/test_url.c:572` | `static void test_extract_userinfo_no_userinfo(void **state)` |
| `test_extract_userinfo_non_https_passthrough` | function | `tests/test_url.c:584` | `static void test_extract_userinfo_non_https_passthrough(void **state)` |
| `test_extract_userinfo_nulls` | function | `tests/test_url.c:609` | `static void test_extract_userinfo_nulls(void **state)` |
| `test_extract_userinfo_user_only` | function | `tests/test_url.c:559` | `static void test_extract_userinfo_user_only(void **state)` |
| `test_has_scheme` | function | `tests/test_url.c:69` | `static void test_has_scheme(void **state)` |
| `test_history_target_bad_args` | function | `tests/test_url.c:732` | `static void test_history_target_bad_args(void **state)` |
| `test_history_target_cross_origin_rejected` | function | `tests/test_url.c:692` | `static void test_history_target_cross_origin_rejected(void **state)` |
| `test_history_target_file_query_fragment_only` | function | `tests/test_url.c:707` | `static void test_history_target_file_query_fragment_only(void **state)` |
| `test_history_target_same_origin` | function | `tests/test_url.c:671` | `static void test_history_target_same_origin(void **state)` |
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
| `test_split_fail_closed_non_https` | function | `tests/test_url.c:658` | `static void test_split_fail_closed_non_https(void **state)` |
| `test_split_fragment_without_query` | function | `tests/test_url.c:495` | `static void test_split_fragment_without_query(void **state)` |
| `test_split_full_url` | function | `tests/test_url.c:454` | `static void test_split_full_url(void **state)` |
| `test_split_ipv6_literal_with_port` | function | `tests/test_url.c:534` | `static void test_split_ipv6_literal_with_port(void **state)` |
| `test_split_location_file` | function | `tests/test_url.c:506` | `static void test_split_location_file(void **state)` |
| `test_split_no_port_no_path` | function | `tests/test_url.c:473` | `static void test_split_no_port_no_path(void **state)` |
| `test_split_query_without_fragment` | function | `tests/test_url.c:486` | `static void test_split_query_without_fragment(void **state)` |
| `test_validate_https` | function | `tests/test_url.c:36` | `static void test_validate_https(void **state)` |
| `test_validate_long_bundle_url` | function | `tests/test_url.c:49` | `static void test_validate_long_bundle_url(void **state)` |
| `frac_and_time_format` | function | `tests/test_video_controls.c:107` | `static void frac_and_time_format(void **st)` |
| `hit_classifies_button_track_bar_surface` | function | `tests/test_video_controls.c:40` | `static void hit_classifies_button_track_bar_surface(void **st)` |
| `hostile_durations_stay_finite` | function | `tests/test_video_controls.c:62` | `static void hostile_durations_stay_finite(void **st)` |
| `layout_puts_bar_at_bottom_and_rejects_tiny` | function | `tests/test_video_controls.c:24` | `static void layout_puts_bar_at_bottom_and_rejects_tiny(void **st)` |
| `main` | function | `tests/test_video_controls.c:131` | `int main(void)` |
| `pl_of` | function | `tests/test_video_controls.c:10` | `static hls_playlist *pl_of(const double *d, size_t n, hls_segment *segs)` |
| `position_is_clamped` | function | `tests/test_video_controls.c:97` | `static void position_is_clamped(void **st)` |
| `segment_at_maps_time_and_clamps` | function | `tests/test_video_controls.c:75` | `static void segment_at_maps_time_and_clamps(void **st)` |
| `first_non_empty_src_wins` | function | `tests/test_video_pick.c:26` | `static void first_non_empty_src_wins(void **st)` |
| `frame_video_beats_top_video` | function | `tests/test_video_pick.c:36` | `static void frame_video_beats_top_video(void **st)` |
| `frame_without_video_falls_back_to_top` | function | `tests/test_video_pick.c:44` | `static void frame_without_video_falls_back_to_top(void **st)` |
| `main` | function | `tests/test_video_pick.c:75` | `int main(void)` |
| `non_url_src_is_not_a_video` | function | `tests/test_video_pick.c:61` | `static void non_url_src_is_not_a_video(void **st)` |
| `nothing_anywhere_is_null` | function | `tests/test_video_pick.c:52` | `static void nothing_anywhere_is_null(void **st)` |
| `null_and_empty_views_have_no_video` | function | `tests/test_video_pick.c:18` | `static void null_and_empty_views_have_no_video(void **st)` |
| `view_with` | function | `tests/test_video_pick.c:9` | `static pv_view *view_with(const char *const *srcs, size_t n)` |
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
| `main` | function | `tests/test_webfont.c:251` | `int main(void)` |
| `test_data_url_decodes_at_scan` | function | `tests/test_webfont.c:187` | `static void test_data_url_decodes_at_scan(void **state)` |
| `test_name_hash` | function | `tests/test_webfont.c:224` | `static void test_name_hash(void **state)` |
| `test_ref_move_transfers_bytes` | function | `tests/test_webfont.c:204` | `static void test_ref_move_transfers_bytes(void **state)` |
| `test_scan_basic_two_formats` | function | `tests/test_webfont.c:36` | `static void test_scan_basic_two_formats(void **state)` |
| `test_scan_case_and_ws` | function | `tests/test_webfont.c:106` | `static void test_scan_case_and_ws(void **state)` |
| `test_scan_hostile_truncations` | function | `tests/test_webfont.c:120` | `static void test_scan_hostile_truncations(void **state)` |
| `test_scan_ignores_other_at_rules` | function | `tests/test_webfont.c:174` | `static void test_scan_ignores_other_at_rules(void **state)` |
| `test_scan_local_only_yields_nothing` | function | `tests/test_webfont.c:81` | `static void test_scan_local_only_yields_nothing(void **state)` |
| `test_scan_overlong_url_dropped` | function | `tests/test_webfont.c:140` | `static void test_scan_overlong_url_dropped(void **state)` |
| `test_scan_quoted_family_variants` | function | `tests/test_webfont.c:92` | `static void test_scan_quoted_family_variants(void **state)` |
| `test_scan_weight_style` | function | `tests/test_webfont.c:55` | `static void test_scan_weight_style(void **state)` |
| `test_supported_format` | function | `tests/test_webfont.c:155` | `static void test_supported_format(void **state)` |
| `_POSIX_C_SOURCE` | macro | `tests/test_webfont_load.c:13` | `#define _POSIX_C_SOURCE` |
| `main` | function | `tests/test_webfont_load.c:350` | `int main(void)` |
| `read_host_font` | function | `tests/test_webfont_load.c:64` | `static unsigned char *read_host_font(size_t *out_n)` |
| `stub` | struct | `tests/test_webfont_load.c:30` | `` |
| `stub_fetch` | function | `tests/test_webfont_load.c:38` | `static int stub_fetch(void *ctx, const char *url,                       int *out_status, char **o...` |
| `teardown` | function | `tests/test_webfont_load.c:343` | `static int teardown(void **state)` |
| `test_b64` | function | `tests/test_webfont_load.c:92` | `static char *test_b64(const unsigned char *in, size_t n)` |
| `test_data_url_bad_bytes_skipped` | function | `tests/test_webfont_load.c:265` | `static void test_data_url_bad_bytes_skipped(void **state)` |
| `test_data_url_registers` | function | `tests/test_webfont_load.c:280` | `static void test_data_url_registers(void **state)` |
| `test_extern_sheet_relative_url` | function | `tests/test_webfont_load.c:242` | `static void test_extern_sheet_relative_url(void **state)` |
| `test_fallback_second_url` | function | `tests/test_webfont_load.c:195` | `static void test_fallback_second_url(void **state)` |
| `test_first_wins` | function | `tests/test_webfont_load.c:219` | `static void test_first_wins(void **state)` |
| `test_https_stub_registers` | function | `tests/test_webfont_load.c:126` | `static void test_https_stub_registers(void **state)` |
| `test_null_args` | function | `tests/test_webfont_load.c:113` | `static void test_null_args(void **state)` |
| `test_null_page_data_only` | function | `tests/test_webfont_load.c:313` | `static void test_null_page_data_only(void **state)` |
| `test_woff2_fetched_and_validated` | function | `tests/test_webfont_load.c:155` | `static void test_woff2_fetched_and_validated(void **state)` |
| `main` | function | `tests/test_wl_display.c:43` | `int main(void)` |

Next: [SYMBOLS_p19.md](SYMBOLS_p19.md)
