# Symbols (page 13 of 14)
Previous: [SYMBOLS_p12.md](SYMBOLS_p12.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `run` | function | `tests/test_js_env.c:47` | `static js_status run(fixture *f, const char *src, js_result *r)` |
| `setup` | function | `tests/test_js_env.c:29` | `static int setup(void **state)` |
| `teardown` | function | `tests/test_js_env.c:38` | `static int teardown(void **state)` |
| `test_bool_nav_props` | function | `tests/test_js_env.c:103` | `static void test_bool_nav_props(void **state)` |
| `test_canvas_readback` | function | `tests/test_js_env.c:239` | `static void test_canvas_readback(void **state)` |
| `test_canvas_unforgeable` | function | `tests/test_js_env.c:303` | `static void test_canvas_unforgeable(void **state)` |
| `test_canvas_unlinkable` | function | `tests/test_js_env.c:295` | `static void test_canvas_unlinkable(void **state)` |
| `test_clocks_coarse` | function | `tests/test_js_env.c:178` | `static void test_clocks_coarse(void **state)` |
| `test_coexists_with_dom` | function | `tests/test_js_env.c:326` | `static void test_coexists_with_dom(void **state)` |
| `test_crypto_present` | function | `tests/test_js_env.c:129` | `static void test_crypto_present(void **state)` |
| `test_crypto_random_uuid` | function | `tests/test_js_env.c:137` | `static void test_crypto_random_uuid(void **state)` |
| `test_crypto_random_values` | function | `tests/test_js_env.c:146` | `static void test_crypto_random_values(void **state)` |
| `test_install_null_args` | function | `tests/test_js_env.c:62` | `static void test_install_null_args(void **state)` |
| `test_legacy_nav_props` | function | `tests/test_js_env.c:92` | `static void test_legacy_nav_props(void **state)` |
| `test_navigator_identity` | function | `tests/test_js_env.c:74` | `static void test_navigator_identity(void **state)` |
| `test_navigator_mime_types` | function | `tests/test_js_env.c:120` | `static void test_navigator_mime_types(void **state)` |
| `test_navigator_plugins` | function | `tests/test_js_env.c:112` | `static void test_navigator_plugins(void **state)` |
| `test_performance_timing_identity_safe` | function | `tests/test_js_env.c:190` | `static void test_performance_timing_identity_safe(void **state)` |
| `test_screen_bucketed` | function | `tests/test_js_env.c:166` | `static void test_screen_bucketed(void **state)` |
| `test_screen_edges` | function | `tests/test_js_env.c:220` | `static void test_screen_edges(void **state)` |
| `test_screen_orientation` | function | `tests/test_js_env.c:156` | `static void test_screen_orientation(void **state)` |
| `test_unforgeable` | function | `tests/test_js_env.c:206` | `static void test_unforgeable(void **state)` |
| `chain_parent` | function | `tests/test_js_geom.c:97` | `static dom_node_id chain_parent(void *ctx, dom_node_id n)` |
| `cyclic_parent` | function | `tests/test_js_geom.c:132` | `static dom_node_id cyclic_parent(void *ctx, dom_node_id n)` |
| `main` | function | `tests/test_js_geom.c:213` | `int main(void)` |
| `test_add_and_find` | function | `tests/test_js_geom.c:29` | `static void test_add_and_find(void **state)` |
| `test_add_rejects_and_clamps` | function | `tests/test_js_geom.c:65` | `static void test_add_rejects_and_clamps(void **state)` |
| `test_aggregate_cycle_terminates` | function | `tests/test_js_geom.c:137` | `static void test_aggregate_cycle_terminates(void **state)` |
| `test_aggregate_unions_into_ancestors` | function | `tests/test_js_geom.c:108` | `static void test_aggregate_unions_into_ancestors(void **state)` |
| `test_capacity_bound` | function | `tests/test_js_geom.c:85` | `static void test_capacity_bound(void **state)` |
| `test_decode_fails_closed` | function | `tests/test_js_geom.c:179` | `static void test_decode_fails_closed(void **state)` |
| `test_same_node_unions` | function | `tests/test_js_geom.c:48` | `static void test_same_node_unions(void **state)` |
| `test_wire_roundtrip` | function | `tests/test_js_geom.c:149` | `static void test_wire_roundtrip(void **state)` |
| `main` | function | `tests/test_js_policy.c:89` | `int main(void)` |
| `test_enabled_fail_closed_on_bad_mode` | function | `tests/test_js_policy.c:31` | `static void test_enabled_fail_closed_on_bad_mode(void **state)` |
| `test_mode_from_str` | function | `tests/test_js_policy.c:36` | `static void test_mode_from_str(void **state)` |
| `test_mode_str_roundtrip` | function | `tests/test_js_policy.c:53` | `static void test_mode_str_roundtrip(void **state)` |
| `test_trusted_requires_both_signals` | function | `tests/test_js_policy.c:68` | `static void test_trusted_requires_both_signals(void **state)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:156` | `assert_int_equal(js_eval_once("while(true)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:171` | `assert_int_equal(js_eval(ctx, "while(true)` |
| `fetches` | type_alias | `tests/test_js_sandbox.c:343` | `typedef struct mod_host { int fetches;` |
| `main` | function | `tests/test_js_sandbox.c:570` | `int main(void)` |
| `mh_fetch` | function | `tests/test_js_sandbox.c:361` | `static char *mh_fetch(void *host, const char *url, size_t *len)` |
| `mh_resolve` | function | `tests/test_js_sandbox.c:346` | `static int mh_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)` |
| `mod_host` | struct | `tests/test_js_sandbox.c:344` | `` |
| `realm_expect` | function | `tests/test_js_sandbox.c:517` | `static void realm_expect(js_context *ctx, const char *src, const char *want)` |
| `self_fetch` | function | `tests/test_js_sandbox.c:478` | `static char *self_fetch(void *host, const char *url, size_t *len)` |
| `test_context_free_null_and_double` | function | `tests/test_js_sandbox.c:205` | `static void test_context_free_null_and_double(void **state)` |
| `test_context_new_and_free` | function | `tests/test_js_sandbox.c:60` | `static void test_context_new_and_free(void **state)` |
| `test_context_new_null_out` | function | `tests/test_js_sandbox.c:68` | `static void test_context_new_null_out(void **state)` |
| `test_eval_arithmetic` | function | `tests/test_js_sandbox.c:75` | `static void test_eval_arithmetic(void **state)` |
| `test_eval_named_captures_location` | function | `tests/test_js_sandbox.c:290` | `static void test_eval_named_captures_location(void **state)` |
| `test_eval_named_null_filename_defaults` | function | `tests/test_js_sandbox.c:311` | `static void test_eval_named_null_filename_defaults(void **state)` |
| `test_eval_null_args` | function | `tests/test_js_sandbox.c:213` | `static void test_eval_null_args(void **state)` |
| `test_eval_runtime_exception` | function | `tests/test_js_sandbox.c:110` | `static void test_eval_runtime_exception(void **state)` |
| `test_eval_string_concat` | function | `tests/test_js_sandbox.c:89` | `static void test_eval_string_concat(void **state)` |
| `test_eval_syntax_error` | function | `tests/test_js_sandbox.c:101` | `static void test_eval_syntax_error(void **state)` |
| `test_eval_thrown_primitive_has_no_location` | function | `tests/test_js_sandbox.c:326` | `static void test_eval_thrown_primitive_has_no_location(void **state)` |
| `test_filesystem_access_is_reference_error` | function | `tests/test_js_sandbox.c:137` | `static void test_filesystem_access_is_reference_error(void **state)` |
| `test_infinite_loop_times_out` | function | `tests/test_js_sandbox.c:150` | `static void test_infinite_loop_times_out(void **state)` |
| `test_loc_file_may_contain_colons` | function | `tests/test_js_sandbox.c:247` | `static void test_loc_file_may_contain_colons(void **state)` |
| `test_loc_line_only_sets_col_zero` | function | `tests/test_js_sandbox.c:258` | `static void test_loc_line_only_sets_col_zero(void **state)` |
| `test_loc_parses_bare_frame` | function | `tests/test_js_sandbox.c:238` | `static void test_loc_parses_bare_frame(void **state)` |
| `test_loc_parses_named_frame` | function | `tests/test_js_sandbox.c:227` | `static void test_loc_parses_named_frame(void **state)` |
| `test_loc_rejects_garbage_and_null` | function | `tests/test_js_sandbox.c:275` | `static void test_loc_rejects_garbage_and_null(void **state)` |
| `test_loc_truncates_to_cap` | function | `tests/test_js_sandbox.c:267` | `static void test_loc_truncates_to_cap(void **state)` |
| `test_memory_limit_is_enforced` | function | `tests/test_js_sandbox.c:180` | `static void test_memory_limit_is_enforced(void **state)` |
| `test_module_errors_are_reported` | function | `tests/test_js_sandbox.c:404` | `static void test_module_errors_are_reported(void **state)` |
| `test_module_imports_resolve_and_run` | function | `tests/test_js_sandbox.c:383` | `static void test_module_imports_resolve_and_run(void **state)` |
| `test_module_self_await_teardown` | function | `tests/test_js_sandbox.c:488` | `static void test_module_self_await_teardown(void **state)` |
| `test_module_without_host_cannot_import` | function | `tests/test_js_sandbox.c:456` | `static void test_module_without_host_cannot_import(void **state)` |
| `test_no_io_globals` | function | `tests/test_js_sandbox.c:124` | `static void test_no_io_globals(void **state)` |
| `test_realm_shares_time_budget` | function | `tests/test_js_sandbox.c:556` | `static void test_realm_shares_time_budget(void **state)` |
| `test_realms_isolate_and_clone` | function | `tests/test_js_sandbox.c:525` | `static void test_realms_isolate_and_clone(void **state)` |
| `test_result_free_on_zeroed` | function | `tests/test_js_sandbox.c:196` | `static void test_result_free_on_zeroed(void **state)` |
| `test_set_time_budget_applies` | function | `tests/test_js_sandbox.c:163` | `static void test_set_time_budget_applies(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_js_sandbox.c:53` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_js_sandbox.c:41` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_js_sandbox.c:36` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_js_sandbox.c:46` | `static void test_validate_rejects_oversize(void **state)` |
| `main` | function | `tests/test_link_nav.c:273` | `int main(void)` |
| `test_block_reason_text` | function | `tests/test_link_nav.c:234` | `static void test_block_reason_text(void **state)` |
| `test_block_reasons` | function | `tests/test_link_nav.c:207` | `static void test_block_reasons(void **state)` |
| `test_file_absolute_path` | function | `tests/test_link_nav.c:141` | `static void test_file_absolute_path(void **state)` |
| `test_file_base_blocks_schemes_and_scheme_relative` | function | `tests/test_link_nav.c:165` | `static void test_file_base_blocks_schemes_and_scheme_relative(void **state)` |
| `test_file_base_to_https` | function | `tests/test_link_nav.c:157` | `static void test_file_base_to_https(void **state)` |
| `test_file_drops_fragment` | function | `tests/test_link_nav.c:149` | `static void test_file_drops_fragment(void **state)` |
| `test_file_parent` | function | `tests/test_link_nav.c:133` | `static void test_file_parent(void **state)` |
| `test_file_relative` | function | `tests/test_link_nav.c:125` | `static void test_file_relative(void **state)` |
| `test_fragment_capture` | function | `tests/test_link_nav.c:244` | `static void test_fragment_capture(void **state)` |
| `test_fragment_is_same_document` | function | `tests/test_link_nav.c:37` | `static void test_fragment_is_same_document(void **state)` |
| `test_href_cleaning` | function | `tests/test_link_nav.c:114` | `static void test_href_cleaning(void **state)` |
| `test_https_absolute` | function | `tests/test_link_nav.c:49` | `static void test_https_absolute(void **state)` |
| `test_https_absolute_path_and_parent` | function | `tests/test_link_nav.c:65` | `static void test_https_absolute_path_and_parent(void **state)` |
| `test_https_blocks_downgrade_and_schemes` | function | `tests/test_link_nav.c:76` | `static void test_https_blocks_downgrade_and_schemes(void **state)` |
| `test_https_relative` | function | `tests/test_link_nav.c:57` | `static void test_https_relative(void **state)` |
| `test_https_scheme_relative` | function | `tests/test_link_nav.c:91` | `static void test_https_scheme_relative(void **state)` |
| `test_no_base` | function | `tests/test_link_nav.c:179` | `static void test_no_base(void **state)` |
| `test_null_href_blocked` | function | `tests/test_link_nav.c:29` | `static void test_null_href_blocked(void **state)` |
| `test_null_out` | function | `tests/test_link_nav.c:24` | `static void test_null_out(void **state)` |
| `test_overflow_blocked` | function | `tests/test_link_nav.c:195` | `static void test_overflow_blocked(void **state)` |
| `test_resolve_long_bundle_target` | function | `tests/test_link_nav.c:101` | `static void test_resolve_long_bundle_target(void **state)` |
| `local_store` | function | `tests/test_local_store.c:2` | `* TDD suite for local_store (Hito 5 - Zero Knowledge: encrypted local state). * * RED state until src/local_store.c...` |
| `main` | function | `tests/test_local_store.c:193` | `int main(void)` |
| `roundtrip_raw` | function | `tests/test_local_store.c:30` | `static void roundtrip_raw(ls_aead aead)` |
| `tamper_at` | function | `tests/test_local_store.c:85` | `static void tamper_at(size_t off)` |
| `test_derive_key` | function | `tests/test_local_store.c:149` | `static void test_derive_key(void **s)` |
| `test_empty_plaintext` | function | `tests/test_local_store.c:53` | `static void test_empty_plaintext(void **s)` |
| `test_format_errors` | function | `tests/test_local_store.c:166` | `static void test_format_errors(void **s)` |
| `test_nondeterministic` | function | `tests/test_local_store.c:107` | `static void test_nondeterministic(void **s)` |
| `test_null_and_limits` | function | `tests/test_local_store.c:181` | `static void test_null_and_limits(void **s)` |
| `test_passphrase_roundtrip` | function | `tests/test_local_store.c:121` | `static void test_passphrase_roundtrip(void **s)` |
| `test_roundtrip_aes` | function | `tests/test_local_store.c:48` | `static void test_roundtrip_aes(void **s)` |
| `test_roundtrip_chacha` | function | `tests/test_local_store.c:49` | `static void test_roundtrip_chacha(void **s)` |
| `test_tamper_aead_id` | function | `tests/test_local_store.c:103` | `static void test_tamper_aead_id(void **s)` |
| `test_tamper_ciphertext` | function | `tests/test_local_store.c:99` | `static void test_tamper_ciphertext(void **s)` |
| `test_tamper_nonce` | function | `tests/test_local_store.c:101` | `static void test_tamper_nonce(void **s)` |
| `test_tamper_salt` | function | `tests/test_local_store.c:102` | `static void test_tamper_salt(void **s)` |
| `test_tamper_tag` | function | `tests/test_local_store.c:100` | `static void test_tamper_tag(void **s)` |
| `test_wrong_key` | function | `tests/test_local_store.c:67` | `static void test_wrong_key(void **s)` |
| `main` | function | `tests/test_media_decoder.c:89` | `int main(void)` |
| `test_pacer_backwards_pts_reanchors` | function | `tests/test_media_decoder.c:40` | `static void test_pacer_backwards_pts_reanchors(void **state)` |
| `test_pacer_hostile_pts_bounded` | function | `tests/test_media_decoder.c:69` | `static void test_pacer_hostile_pts_bounded(void **state)` |
| `test_pacer_lag_reanchors` | function | `tests/test_media_decoder.c:52` | `static void test_pacer_lag_reanchors(void **state)` |
| `test_pacer_null_safe` | function | `tests/test_media_decoder.c:84` | `static void test_pacer_null_safe(void **state)` |
| `test_pacer_paces_by_pts_delta` | function | `tests/test_media_decoder.c:28` | `static void test_pacer_paces_by_pts_delta(void **state)` |
| `main` | function | `tests/test_net_realm.c:140` | `int main(void)` |
| `test_classify_host_clearnet` | function | `tests/test_net_realm.c:37` | `static void test_classify_host_clearnet(void **state)` |
| `test_classify_host_edges` | function | `tests/test_net_realm.c:54` | `static void test_classify_host_edges(void **state)` |
| `test_classify_host_i2p` | function | `tests/test_net_realm.c:30` | `static void test_classify_host_i2p(void **state)` |
| `test_classify_host_lookalikes` | function | `tests/test_net_realm.c:44` | `static void test_classify_host_lookalikes(void **state)` |
| `test_classify_host_onion` | function | `tests/test_net_realm.c:22` | `static void test_classify_host_onion(void **state)` |
| `test_classify_url` | function | `tests/test_net_realm.c:67` | `static void test_classify_url(void **state)` |
| `test_names` | function | `tests/test_net_realm.c:126` | `static void test_names(void **state)` |
| `test_realm_allows_http` | function | `tests/test_net_realm.c:118` | `static void test_realm_allows_http(void **state)` |
| `test_route_clearnet` | function | `tests/test_net_realm.c:96` | `static void test_route_clearnet(void **state)` |
| `test_route_i2p` | function | `tests/test_net_realm.c:88` | `static void test_route_i2p(void **state)` |
| `test_route_null_blocked` | function | `tests/test_net_realm.c:110` | `static void test_route_null_blocked(void **state)` |
| `test_route_onion` | function | `tests/test_net_realm.c:79` | `static void test_route_onion(void **state)` |
| `_GNU_SOURCE` | macro | `tests/test_os_sandbox.c:14` | `#define _GNU_SOURCE` |
| `main` | function | `tests/test_os_sandbox.c:335` | `int main(void)` |
| `net_ns_inode` | function | `tests/test_os_sandbox.c:304` | `static unsigned long net_ns_inode(void)` |
| `suite` | function | `tests/test_os_sandbox.c:313` | `* suite (it is best-effort defense in depth), and on a host that allows them the  * isolation mus...` |
| `test_harden_allows_permitted_syscall` | function | `tests/test_os_sandbox.c:96` | `static void test_harden_allows_permitted_syscall(void **state)` |
| `test_harden_blocks_exec_mmap` | function | `tests/test_os_sandbox.c:162` | `static void test_harden_blocks_exec_mmap(void **state)` |
| `test_harden_blocks_exec_mprotect` | function | `tests/test_os_sandbox.c:182` | `static void test_harden_blocks_exec_mprotect(void **state)` |
| `test_harden_errno_denies_with_eperm` | function | `tests/test_os_sandbox.c:112` | `static void test_harden_errno_denies_with_eperm(void **state)` |
| `test_harden_kills_denied_syscall` | function | `tests/test_os_sandbox.c:79` | `static void test_harden_kills_denied_syscall(void **state)` |
| `test_harden_kills_io_uring_setup` | function | `tests/test_os_sandbox.c:130` | `static void test_harden_kills_io_uring_setup(void **state)` |
| `test_landlock_abi_present` | function | `tests/test_os_sandbox.c:233` | `static void test_landlock_abi_present(void **state)` |
| `test_landlock_allow_read` | function | `tests/test_os_sandbox.c:257` | `static void test_landlock_allow_read(void **state)` |
| `test_landlock_deny_all` | function | `tests/test_os_sandbox.c:239` | `static void test_landlock_deny_all(void **state)` |
| `test_no_dump_undumpable` | function | `tests/test_os_sandbox.c:214` | `static void test_no_dump_undumpable(void **state)` |
| `test_policy_allows_safe` | function | `tests/test_os_sandbox.c:43` | `static void test_policy_allows_safe(void **state)` |
| `test_policy_denies_dangerous` | function | `tests/test_os_sandbox.c:51` | `static void test_policy_denies_dangerous(void **state)` |
| `test_policy_denies_io_uring` | function | `tests/test_os_sandbox.c:64` | `static void test_policy_denies_io_uring(void **state)` |
| `test_policy_size` | function | `tests/test_os_sandbox.c:71` | `static void test_policy_size(void **state)` |
| `test_prot_allowed_wx` | function | `tests/test_os_sandbox.c:151` | `static void test_prot_allowed_wx(void **state)` |
| `applies` | function | `tests/test_page_view.c:4383` | `* <style>: an extern rule applies (presentation and display:none alike);` |
| `box_of_run_with_bg` | function | `tests/test_page_view.c:3691` | `static const pv_box_def *box_of_run_with_bg(const pv_view *v, int bg)` |
| `break` | function | `tests/test_page_view.c:703` | `* block break (from entering <p>);` |
| `count_empty_lines` | function | `tests/test_page_view.c:3394` | `static int count_empty_lines(const pv_view *v)` |
| `count_inputs` | function | `tests/test_page_view.c:3291` | `static size_t count_inputs(const pv_view *v, int type)` |
| `dropped` | function | `tests/test_page_view.c:427` | `* either flank is dropped (the inter-cell rule above stays). */ static void test_build_table_inli...` |
| `find_image` | function | `tests/test_page_view.c:55` | `static const pv_run *find_image(const pv_view *v, const char *src)` |
| `find_input` | function | `tests/test_page_view.c:3193` | `static const pv_run *find_input(const pv_view *v, const char *name)` |
| `find_link` | function | `tests/test_page_view.c:73` | `static const pv_run *find_link(const pv_view *v, const char *href)` |
| `find_sub` | function | `tests/test_page_view.c:46` | `static const pv_run *find_sub(const pv_view *v, const char *sub)` |
| `find_svg` | function | `tests/test_page_view.c:81` | `static const pv_run *find_svg(const pv_view *v)` |
| `find_text` | function | `tests/test_page_view.c:37` | `static const pv_run *find_text(const pv_view *v, const char *text)` |
| `find_video` | function | `tests/test_page_view.c:64` | `static const pv_run *find_video(const pv_view *v, const char *src)` |
| `float_id` | function | `tests/test_page_view.c:1557` | `* A run inside a float nested in another float reports the inner element as * float_id (unchanged) plus the outer...` |
| `form` | function | `tests/test_page_view.c:3259` | `* invisible PV_IN_SUBMIT_BOX proxy carries the form (spec/page_view.md). */ assert_non_null(find_text(v, "Log in"));` |
| `height` | function | `tests/test_page_view.c:4357` | `* real height (jkanime's donghuas/ovas panes are display:none, yet all their  * thumbnails flowed...` |
| `it` | function | `tests/test_page_view.c:634` | `* the rest of the row share it (so an overflowing table degrades to one row per * line, not one blob). */...` |
| `line` | function | `tests/test_page_view.c:3678` | `* it flows in its line (no break around it) and the text clears the margin */ const pv_run *in = find_text(v, "Inline");` |
| `main` | function | `tests/test_page_view.c:5123` | `int main(void)` |
| `ordinal` | function | `tests/test_page_view.c:1859` | `* cont_item ordinal (they are one flex/grid item and must flow together in one * cell);` |
| `parse` | function | `tests/test_page_view.c:29` | `static hp_document *parse(const char *html)` |
| `reverted` | function | `tests/test_page_view.c:4343` | `* behavior of treating inline display:none as visible when JS is off * was reverted (commit 897f414 regression)...` |
| `scales` | function | `tests/test_page_view.c:4259` | `* value the UA rule scales (tanda 19). */ static void test_build_heading_own_relative_size_replac...` |
| `short` | function | `tests/test_page_view.c:1743` | `* heading came out two thirds short (and its UA margin with it, once it had a box). */ static voi...` |
| `size` | function | `tests/test_page_view.c:772` | `* size (~100px) instead of the CSS 40px, blowing up flex rows (slashdot socials). */ static void ...` |
| `test_after_box_on_empty_element` | function | `tests/test_page_view.c:3856` | `static void test_after_box_on_empty_element(void **state)` |
| `test_append_copies_fields` | function | `tests/test_page_view.c:100` | `static void test_append_copies_fields(void **state)` |
| `test_append_image_copies_fields` | function | `tests/test_page_view.c:127` | `static void test_append_image_copies_fields(void **state)` |
| `test_append_image_null_args` | function | `tests/test_page_view.c:143` | `static void test_append_image_null_args(void **state)` |
| `test_append_null_args` | function | `tests/test_page_view.c:207` | `static void test_append_null_args(void **state)` |
| `test_append_transcodes_cp1252_quotes` | function | `tests/test_page_view.c:179` | `static void test_append_transcodes_cp1252_quotes(void **state)` |
| `test_append_transcodes_latin1` | function | `tests/test_page_view.c:158` | `static void test_append_transcodes_latin1(void **state)` |
| `test_append_transcodes_word` | function | `tests/test_page_view.c:168` | `static void test_append_transcodes_word(void **state)` |
| `test_append_undefined_cp1252_is_qmark` | function | `tests/test_page_view.c:189` | `static void test_append_undefined_cp1252_is_qmark(void **state)` |
| `test_append_valid_utf8_passthrough` | function | `tests/test_page_view.c:199` | `static void test_append_valid_utf8_passthrough(void **state)` |
| `test_append_video_copies_fields` | function | `tests/test_page_view.c:4936` | `static void test_append_video_copies_fields(void **state)` |
| `test_append_video_no_poster` | function | `tests/test_page_view.c:4955` | `static void test_append_video_no_poster(void **state)` |
| `test_append_video_null_args` | function | `tests/test_page_view.c:4971` | `static void test_append_video_null_args(void **state)` |
| `test_author_list_padding_replaces_ua_indent` | function | `tests/test_page_view.c:4416` | `static void test_author_list_padding_replaces_ua_indent(void **state)` |
| `test_before_box_before_text` | function | `tests/test_page_view.c:3811` | `static void test_before_box_before_text(void **state)` |
| `test_before_box_on_empty_element` | function | `tests/test_page_view.c:3735` | `static void test_before_box_on_empty_element(void **state)` |
| `test_before_box_on_host_with_only_element_children` | function | `tests/test_page_view.c:3754` | `static void test_before_box_on_host_with_only_element_children(void **state)` |
| `test_before_rides_float_and_container` | function | `tests/test_page_view.c:4441` | `static void test_before_rides_float_and_container(void **state)` |
| `test_block_inside_inline_block_in_line` | function | `tests/test_page_view.c:4539` | `static void test_block_inside_inline_block_in_line(void **state)` |
| `test_body_background_propagates_to_canvas` | function | `tests/test_page_view.c:3773` | `static void test_body_background_propagates_to_canvas(void **state)` |
| `test_box_defaults_and_setter` | function | `tests/test_page_view.c:2549` | `static void test_box_defaults_and_setter(void **state)` |
| `test_box_min_width_zero_is_declared` | function | `tests/test_page_view.c:3642` | `static void test_box_min_width_zero_is_declared(void **state)` |
| `test_br_continuation_flag` | function | `tests/test_page_view.c:3437` | `static void test_br_continuation_flag(void **state)` |
| `test_br_opening_line_is_empty_line` | function | `tests/test_page_view.c:3406` | `static void test_br_opening_line_is_empty_line(void **state)` |
| `test_build_abs_child_is_not_a_flex_item` | function | `tests/test_page_view.c:2301` | `static void test_build_abs_child_is_not_a_flex_item(void **state)` |
| `test_build_absolute_inside_float_escapes` | function | `tests/test_page_view.c:1706` | `static void test_build_absolute_inside_float_escapes(void **state)` |
| `test_build_audio_as_video_kind` | function | `tests/test_page_view.c:5065` | `static void test_build_audio_as_video_kind(void **state)` |
| `test_build_author_color` | function | `tests/test_page_view.c:1167` | `static void test_build_author_color(void **state)` |
| `test_build_bgcolor_attr_fallback` | function | `tests/test_page_view.c:587` | `static void test_build_bgcolor_attr_fallback(void **state)` |
| `test_build_block_break_between_paragraphs` | function | `tests/test_page_view.c:671` | `static void test_build_block_break_between_paragraphs(void **state)` |
| `test_build_box_leaf_inline` | function | `tests/test_page_view.c:2514` | `static void test_build_box_leaf_inline(void **state)` |
| `test_build_box_tree_empty_no_box` | function | `tests/test_page_view.c:3181` | `static void test_build_box_tree_empty_no_box(void **state)` |
| `test_build_box_tree_textless_wrapper` | function | `tests/test_page_view.c:3110` | `static void test_build_box_tree_textless_wrapper(void **state)` |
| `test_build_boxdeco_border_padding` | function | `tests/test_page_view.c:2701` | `static void test_build_boxdeco_border_padding(void **state)` |
| `test_build_boxdeco_defaults_no_box` | function | `tests/test_page_view.c:3016` | `static void test_build_boxdeco_defaults_no_box(void **state)` |
| `test_build_boxdeco_dims_alone_trigger_box` | function | `tests/test_page_view.c:2911` | `static void test_build_boxdeco_dims_alone_trigger_box(void **state)` |
| `test_build_boxdeco_fit_content_height_is_auto` | function | `tests/test_page_view.c:2661` | `static void test_build_boxdeco_fit_content_height_is_auto(void **state)` |
| `test_build_boxdeco_h_margin_alone_creates_box` | function | `tests/test_page_view.c:2580` | `static void test_build_boxdeco_h_margin_alone_creates_box(void **state)` |
| `test_build_boxdeco_h_margin_zero_auto_no_box` | function | `tests/test_page_view.c:2600` | `static void test_build_boxdeco_h_margin_zero_auto_no_box(void **state)` |
| `test_build_boxdeco_min_content_height_is_auto` | function | `tests/test_page_view.c:2683` | `static void test_build_boxdeco_min_content_height_is_auto(void **state)` |
| `test_build_boxdeco_shadow_outline` | function | `tests/test_page_view.c:2809` | `static void test_build_boxdeco_shadow_outline(void **state)` |
| `test_build_boxdeco_shared_id_within_block` | function | `tests/test_page_view.c:3048` | `static void test_build_boxdeco_shared_id_within_block(void **state)` |
| `test_build_boxdeco_sibling_blocks_distinct_ids` | function | `tests/test_page_view.c:3030` | `static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state)` |
| `test_build_boxdeco_visibility_overflow_cursor` | function | `tests/test_page_view.c:2832` | `static void test_build_boxdeco_visibility_overflow_cursor(void **state)` |
| `test_build_boxdef_carries_node_id` | function | `tests/test_page_view.c:2624` | `static void test_build_boxdef_carries_node_id(void **state)` |
| `test_build_caret_color_inherited` | function | `tests/test_page_view.c:4912` | `static void test_build_caret_color_inherited(void **state)` |
| `test_build_combinator_selectors` | function | `tests/test_page_view.c:1299` | `static void test_build_combinator_selectors(void **state)` |
| `test_build_component_custom_props` | function | `tests/test_page_view.c:4292` | `static void test_build_component_custom_props(void **state)` |
| `test_build_cont_item_identity` | function | `tests/test_page_view.c:1861` | `static void test_build_cont_item_identity(void **state)` |
| `test_build_content_visibility_hidden_folds` | function | `tests/test_page_view.c:4867` | `static void test_build_content_visibility_hidden_folds(void **state)` |
| `test_build_control_without_form` | function | `tests/test_page_view.c:3929` | `static void test_build_control_without_form(void **state)` |
| `test_build_css_bold_and_inline_wins` | function | `tests/test_page_view.c:4236` | `static void test_build_css_bold_and_inline_wins(void **state)` |
| `test_build_cursor_alone_triggers_box` | function | `tests/test_page_view.c:2856` | `static void test_build_cursor_alone_triggers_box(void **state)` |
| `test_build_display_none_hidden` | function | `tests/test_page_view.c:4331` | `static void test_build_display_none_hidden(void **state)` |
| `test_build_empty_box_gets_run_and_box` | function | `tests/test_page_view.c:2732` | `static void test_build_empty_box_gets_run_and_box(void **state)` |
| `test_build_empty_document` | function | `tests/test_page_view.c:1131` | `static void test_build_empty_document(void **state)` |
| `test_build_empty_flex_grow_spacer` | function | `tests/test_page_view.c:949` | `static void test_build_empty_flex_grow_spacer(void **state)` |
| `test_build_flex_anchor_is_its_own_block` | function | `tests/test_page_view.c:1767` | `static void test_build_flex_anchor_is_its_own_block(void **state)` |
| `test_build_flex_container` | function | `tests/test_page_view.c:1337` | `static void test_build_flex_container(void **state)` |
| `test_build_flex_container_from_sheet` | function | `tests/test_page_view.c:2402` | `static void test_build_flex_container_from_sheet(void **state)` |
| `test_build_flex_item_values` | function | `tests/test_page_view.c:1450` | `static void test_build_flex_item_values(void **state)` |
| `test_build_flex_whitespace_not_item` | function | `tests/test_page_view.c:1783` | `static void test_build_flex_whitespace_not_item(void **state)` |
| `test_build_flex_wrap_align_row_gap` | function | `tests/test_page_view.c:1409` | `static void test_build_flex_wrap_align_row_gap(void **state)` |
| `test_build_float_outermost_founder` | function | `tests/test_page_view.c:1560` | `static void test_build_float_outermost_founder(void **state)` |
| `test_build_float_threading` | function | `tests/test_page_view.c:1514` | `static void test_build_float_threading(void **state)` |
| `test_build_float_widthless_stays_unset` | function | `tests/test_page_view.c:893` | `static void test_build_float_widthless_stays_unset(void **state)` |
| `test_build_flow_table_row_is_one_block` | function | `tests/test_page_view.c:2774` | `static void test_build_flow_table_row_is_one_block(void **state)` |
| `test_build_font_list_inherits` | function | `tests/test_page_view.c:2231` | `static void test_build_font_list_inherits(void **state)` |
| `test_build_fontface_hash` | function | `tests/test_page_view.c:2013` | `static void test_build_fontface_hash(void **state)` |
| `test_build_form_post_and_hidden` | function | `tests/test_page_view.c:3236` | `static void test_build_form_post_and_hidden(void **state)` |
| `test_build_frame_with_only_oof_content_keeps_box` | function | `tests/test_page_view.c:3138` | `static void test_build_frame_with_only_oof_content_keeps_box(void **state)` |
| `test_build_grid_autofill_marker` | function | `tests/test_page_view.c:1993` | `static void test_build_grid_autofill_marker(void **state)` |
| `test_build_grid_columns_from_sheet` | function | `tests/test_page_view.c:2424` | `static void test_build_grid_columns_from_sheet(void **state)` |
| `test_build_grid_container` | function | `tests/test_page_view.c:1973` | `static void test_build_grid_container(void **state)` |
| `test_build_hbox_container_width_never_seeds_items` | function | `tests/test_page_view.c:1677` | `static void test_build_hbox_container_width_never_seeds_items(void **state)` |
| `test_build_hbox_margin_above_container_merges` | function | `tests/test_page_view.c:1657` | `static void test_build_hbox_margin_above_container_merges(void **state)` |
| `test_build_heading_level` | function | `tests/test_page_view.c:246` | `static void test_build_heading_level(void **state)` |
| `test_build_iframe_display_none_hidden` | function | `tests/test_page_view.c:5110` | `static void test_build_iframe_display_none_hidden(void **state)` |
| `test_build_iframe_emits_navigable_link` | function | `tests/test_page_view.c:5079` | `static void test_build_iframe_emits_navigable_link(void **state)` |
| `test_build_iframe_without_src_ignored` | function | `tests/test_page_view.c:5097` | `static void test_build_iframe_without_src_ignored(void **state)` |
| `test_build_image_auto_size_keeps_attr` | function | `tests/test_page_view.c:929` | `static void test_build_image_auto_size_keeps_attr(void **state)` |
| `test_build_image_css_size_overrides_attr` | function | `tests/test_page_view.c:912` | `static void test_build_image_css_size_overrides_attr(void **state)` |
| `test_build_image_in_skipped_subtree_ignored` | function | `tests/test_page_view.c:967` | `static void test_build_image_in_skipped_subtree_ignored(void **state)` |
| `test_build_image_no_src_and_no_srcset_ignored` | function | `tests/test_page_view.c:1116` | `static void test_build_image_no_src_and_no_srcset_ignored(void **state)` |
| `test_build_image_plain_src_wins_over_srcset` | function | `tests/test_page_view.c:1073` | `static void test_build_image_plain_src_wins_over_srcset(void **state)` |
| `test_build_image_px_and_tracking_dims` | function | `tests/test_page_view.c:747` | `static void test_build_image_px_and_tracking_dims(void **state)` |
| `test_build_image_rendering_inherited` | function | `tests/test_page_view.c:4893` | `static void test_build_image_rendering_inherited(void **state)` |
| `test_build_image_srcset_data_url_not_truncated_at_comma` | function | `tests/test_page_view.c:1101` | `static void test_build_image_srcset_data_url_not_truncated_at_comma(void **state)` |
| `test_build_image_srcset_fallback_when_no_src` | function | `tests/test_page_view.c:1057` | `static void test_build_image_srcset_fallback_when_no_src(void **state)` |
| `test_build_image_srcset_single_no_descriptor` | function | `tests/test_page_view.c:1088` | `static void test_build_image_srcset_single_no_descriptor(void **state)` |
| `test_build_image_unknown_dims` | function | `tests/test_page_view.c:732` | `static void test_build_image_unknown_dims(void **state)` |
| `test_build_image_with_dims` | function | `tests/test_page_view.c:715` | `static void test_build_image_with_dims(void **state)` |
| `test_build_image_without_src_dims_emit_broken` | function | `tests/test_page_view.c:1040` | `static void test_build_image_without_src_dims_emit_broken(void **state)` |
| `test_build_image_without_src_ignored` | function | `tests/test_page_view.c:1009` | `static void test_build_image_without_src_ignored(void **state)` |
| `test_build_inline_block_row_alignment` | function | `tests/test_page_view.c:2085` | `static void test_build_inline_block_row_alignment(void **state)` |
| `test_build_inline_block_row_ignores_oof_child` | function | `tests/test_page_view.c:2135` | `static void test_build_inline_block_row_ignores_oof_child(void **state)` |
| `test_build_inline_emphasis` | function | `tests/test_page_view.c:263` | `static void test_build_inline_emphasis(void **state)` |
| `test_build_inline_link_no_break_within_paragraph` | function | `tests/test_page_view.c:697` | `static void test_build_inline_link_no_break_within_paragraph(void **state)` |
| `test_build_inline_whitespace_kept` | function | `tests/test_page_view.c:1839` | `static void test_build_inline_whitespace_kept(void **state)` |
| `test_build_input_own_box_and_placeholder` | function | `tests/test_page_view.c:2108` | `static void test_build_input_own_box_and_placeholder(void **state)` |
| `test_build_intrinsic_width_flag` | function | `tests/test_page_view.c:2157` | `static void test_build_intrinsic_width_flag(void **state)` |
| `test_build_link_with_href` | function | `tests/test_page_view.c:652` | `static void test_build_link_with_href(void **state)` |
| `test_build_long_class_attribute_keeps_classes` | function | `tests/test_page_view.c:2038` | `static void test_build_long_class_attribute_keeps_classes(void **state)` |
| `test_build_nested_table_not_flattened` | function | `tests/test_page_view.c:603` | `static void test_build_nested_table_not_flattened(void **state)` |
| `test_build_node_id_matches_dom_index` | function | `tests/test_page_view.c:4778` | `static void test_build_node_id_matches_dom_index(void **state)` |
| `test_build_noscript_hidden_when_js_on` | function | `tests/test_page_view.c:996` | `static void test_build_noscript_hidden_when_js_on(void **state)` |
| `test_build_noscript_shown_when_js_off` | function | `tests/test_page_view.c:983` | `static void test_build_noscript_shown_when_js_off(void **state)` |
| `test_build_null_args` | function | `tests/test_page_view.c:224` | `static void test_build_null_args(void **state)` |
| `test_build_oof_flag_badges_idiom` | function | `tests/test_page_view.c:2382` | `static void test_build_oof_flag_badges_idiom(void **state)` |
| `test_build_oof_flag_via_cascade` | function | `tests/test_page_view.c:2358` | `static void test_build_oof_flag_via_cascade(void **state)` |
| `test_build_oof_image_carries_block_id` | function | `tests/test_page_view.c:1592` | `static void test_build_oof_image_carries_block_id(void **state)` |
| `test_build_ordered_and_nested_list` | function | `tests/test_page_view.c:322` | `static void test_build_ordered_and_nested_list(void **state)` |
| `test_build_plain_text` | function | `tests/test_page_view.c:233` | `static void test_build_plain_text(void **state)` |
| `test_build_pointer_events_on_box` | function | `tests/test_page_view.c:4848` | `static void test_build_pointer_events_on_box(void **state)` |
| `test_build_pseudo_classes_and_siblings` | function | `tests/test_page_view.c:4001` | `static void test_build_pseudo_classes_and_siblings(void **state)` |
| `test_build_reader_skips_boilerplate` | function | `tests/test_page_view.c:4734` | `static void test_build_reader_skips_boilerplate(void **state)` |
| `test_build_root_element_style_inherits` | function | `tests/test_page_view.c:2263` | `static void test_build_root_element_style_inherits(void **state)` |
| `test_build_root_font_size_is_overridable` | function | `tests/test_page_view.c:2281` | `static void test_build_root_font_size_is_overridable(void **state)` |
| `test_build_search_form_get` | function | `tests/test_page_view.c:3203` | `static void test_build_search_form_get(void **state)` |
| `test_build_select_defaults_to_first_option` | function | `tests/test_page_view.c:3912` | `static void test_build_select_defaults_to_first_option(void **state)` |
| `test_build_select_shows_selected_option` | function | `tests/test_page_view.c:3873` | `static void test_build_select_shows_selected_option(void **state)` |
| `test_build_skips_script_and_style` | function | `tests/test_page_view.c:683` | `static void test_build_skips_script_and_style(void **state)` |
| `test_build_sourceless_video_keeps_its_box` | function | `tests/test_page_view.c:3162` | `static void test_build_sourceless_video_keeps_its_box(void **state)` |
| `test_build_style_cache_distinct_siblings` | function | `tests/test_page_view.c:4124` | `static void test_build_style_cache_distinct_siblings(void **state)` |
| `test_build_styled_external_css` | function | `tests/test_page_view.c:4387` | `static void test_build_styled_external_css(void **state)` |
| `test_build_svg_css_stroke_inherited` | function | `tests/test_page_view.c:2195` | `static void test_build_svg_css_stroke_inherited(void **state)` |
| `test_build_svg_fills_border_box_ancestor` | function | `tests/test_page_view.c:832` | `static void test_build_svg_fills_border_box_ancestor(void **state)` |
| `test_build_svg_no_ancestor_width_unset` | function | `tests/test_page_view.c:852` | `static void test_build_svg_no_ancestor_width_unset(void **state)` |
| `test_build_table_cell_author_styles` | function | `tests/test_page_view.c:4064` | `static void test_build_table_cell_author_styles(void **state)` |
| `test_build_table_colspan_rowspan` | function | `tests/test_page_view.c:1927` | `static void test_build_table_colspan_rowspan(void **state)` |
| `test_build_table_flattens_cell` | function | `tests/test_page_view.c:453` | `static void test_build_table_flattens_cell(void **state)` |
| `test_build_table_grid` | function | `tests/test_page_view.c:345` | `static void test_build_table_grid(void **state)` |
| `test_build_table_intercell_whitespace_dropped` | function | `tests/test_page_view.c:385` | `static void test_build_table_intercell_whitespace_dropped(void **state)` |
| `test_build_text_align_and_font_size` | function | `tests/test_page_view.c:4166` | `static void test_build_text_align_and_font_size(void **state)` |
| `test_build_text_balance_inherits` | function | `tests/test_page_view.c:2216` | `static void test_build_text_balance_inherits(void **state)` |
| `test_build_text_decoration` | function | `tests/test_page_view.c:4213` | `static void test_build_text_decoration(void **state)` |
| `test_build_text_overflow_and_word_break` | function | `tests/test_page_view.c:2956` | `static void test_build_text_overflow_and_word_break(void **state)` |
| `test_build_textarea_value` | function | `tests/test_page_view.c:3272` | `static void test_build_textarea_value(void **state)` |
| `test_build_two_forms_distinct_groups` | function | `tests/test_page_view.c:3942` | `static void test_build_two_forms_distinct_groups(void **state)` |
| `test_build_unordered_list` | function | `tests/test_page_view.c:304` | `static void test_build_unordered_list(void **state)` |
| `test_build_video_fallback_suppressed` | function | `tests/test_page_view.c:5039` | `static void test_build_video_fallback_suppressed(void **state)` |
| `test_build_video_source_type_preference` | function | `tests/test_page_view.c:5021` | `static void test_build_video_source_type_preference(void **state)` |
| `test_build_video_uses_source_child` | function | `tests/test_page_view.c:5001` | `static void test_build_video_uses_source_child(void **state)` |
| `test_build_video_with_source` | function | `tests/test_page_view.c:4981` | `static void test_build_video_with_source(void **state)` |
| `test_build_video_without_src_ignored` | function | `tests/test_page_view.c:5054` | `static void test_build_video_without_src_ignored(void **state)` |
| `test_build_zero_padding_is_not_a_box` | function | `tests/test_page_view.c:2757` | `static void test_build_zero_padding_is_not_a_box(void **state)` |
| `test_button_content_flows` | function | `tests/test_page_view.c:3313` | `static void test_button_content_flows(void **state)` |
| `test_button_icon_invents_no_label` | function | `tests/test_page_view.c:3298` | `static void test_button_icon_invents_no_label(void **state)` |
| `test_button_submit_proxy` | function | `tests/test_page_view.c:3327` | `static void test_button_submit_proxy(void **state)` |
| `test_button_ua_face_loses_to_author` | function | `tests/test_page_view.c:3352` | `static void test_button_ua_face_loses_to_author(void **state)` |
| `test_container_defaults` | function | `tests/test_page_view.c:2463` | `static void test_container_defaults(void **state)` |
| `test_flex_item_inline_is_blockified` | function | `tests/test_page_view.c:3662` | `static void test_flex_item_inline_is_blockified(void **state)` |
| `test_float_inner_blocks_keep_breaks` | function | `tests/test_page_view.c:3489` | `static void test_float_inner_blocks_keep_breaks(void **state)` |
| `test_free_null_and_double` | function | `tests/test_page_view.c:215` | `static void test_free_null_and_double(void **state)` |
| `test_gradient_text_runs` | function | `tests/test_page_view.c:1221` | `static void test_gradient_text_runs(void **state)` |
| `test_grid_line_placement_nested_container_item` | function | `tests/test_page_view.c:3554` | `static void test_grid_line_placement_nested_container_item(void **state)` |
| `test_grid_line_placement_plain_item` | function | `tests/test_page_view.c:3529` | `static void test_grid_line_placement_plain_item(void **state)` |
| `test_hidden_attribute_is_display_none` | function | `tests/test_page_view.c:3506` | `static void test_hidden_attribute_is_display_none(void **state)` |
| `test_inline_level_tag_list_stays_in_line` | function | `tests/test_page_view.c:4472` | `static void test_inline_level_tag_list_stays_in_line(void **state)` |
| `test_inline_pseudo_registers_no_box` | function | `tests/test_page_view.c:3844` | `static void test_inline_pseudo_registers_no_box(void **state)` |
| `test_link_color_inherit` | function | `tests/test_page_view.c:3708` | `static void test_link_color_inherit(void **state)` |
| `test_marker_only_for_list_item_display` | function | `tests/test_page_view.c:4500` | `static void test_marker_only_for_list_item_display(void **state)` |
| `test_mask_reaches_the_box` | function | `tests/test_page_view.c:3797` | `static void test_mask_reaches_the_box(void **state)` |
| `test_new_is_empty` | function | `tests/test_page_view.c:91` | `static void test_new_is_empty(void **state)` |
| `test_pct_padding_generates_box` | function | `tests/test_page_view.c:3722` | `static void test_pct_padding_generates_box(void **state)` |
| `test_phrasing_ua_faces` | function | `tests/test_page_view.c:3374` | `static void test_phrasing_ua_faces(void **state)` |
| `test_pseudo_after_on_element_with_children` | function | `tests/test_page_view.c:4615` | `static void test_pseudo_after_on_element_with_children(void **state)` |
| `test_pseudo_after_on_whitespace_only_no_run` | function | `tests/test_page_view.c:4693` | `static void test_pseudo_after_on_whitespace_only_no_run(void **state)` |
| `test_pseudo_before_escape_end_to_end` | function | `tests/test_page_view.c:4680` | `static void test_pseudo_before_escape_end_to_end(void **state)` |
| `test_pseudo_before_fires_with_nested_text` | function | `tests/test_page_view.c:4707` | `static void test_pseudo_before_fires_with_nested_text(void **state)` |
| `test_pseudo_before_on_element_with_children` | function | `tests/test_page_view.c:4600` | `static void test_pseudo_before_on_element_with_children(void **state)` |
| `test_pseudo_before_on_empty` | function | `tests/test_page_view.c:4587` | `static void test_pseudo_before_on_empty(void **state)` |
| `test_pseudo_before_on_textless_subtree` | function | `tests/test_page_view.c:4664` | `static void test_pseudo_before_on_textless_subtree(void **state)` |
| `test_pseudo_both_before_and_after` | function | `tests/test_page_view.c:4630` | `static void test_pseudo_both_before_and_after(void **state)` |
| `test_pseudo_display_none_generates_nothing` | function | `tests/test_page_view.c:3827` | `static void test_pseudo_display_none_generates_nothing(void **state)` |
| `test_pseudo_no_content_no_run` | function | `tests/test_page_view.c:4720` | `static void test_pseudo_no_content_no_run(void **state)` |
| `test_root_insets` | function | `tests/test_page_view.c:2065` | `static void test_root_insets(void **state)` |
| `test_set_color_model` | function | `tests/test_page_view.c:1145` | `static void test_set_color_model(void **state)` |
| `test_set_node_id_model` | function | `tests/test_page_view.c:4762` | `static void test_set_node_id_model(void **state)` |
| `test_set_text_style_model` | function | `tests/test_page_view.c:4817` | `static void test_set_text_style_model(void **state)` |
| `test_svg_append_root_attrs` | function | `tests/test_page_view.c:2178` | `static void test_svg_append_root_attrs(void **state)` |
| `test_text_fill_color_runs` | function | `tests/test_page_view.c:1253` | `static void test_text_fill_color_runs(void **state)` |
| `unset` | function | `tests/test_page_view.c:812` | `* unset (-1) so the render step derives it from the viewBox aspect. */ static void test_build_svg...` |
| `wrapping` | function | `tests/test_page_view.c:1377` | `* sideways instead of wrapping (spec/page_view.md, 2026-08-11 correction). */ static void test_bu...` |
| `main` | function | `tests/test_pdf_export.c:290` | `int main(void)` |
| `pagination` | function | `tests/test_pdf_export.c:8` | `* deterministic pagination (single/multi page, no row splitting, oversized row,  * gap preservati...` |
| `test_basename_all_separators_fall_back` | function | `tests/test_pdf_export.c:105` | `static void test_basename_all_separators_fall_back(void **state)` |
| `test_basename_collapses_underscores` | function | `tests/test_pdf_export.c:72` | `static void test_basename_collapses_underscores(void **state)` |
| `test_basename_control_bytes_mapped` | function | `tests/test_pdf_export.c:79` | `static void test_basename_control_bytes_mapped(void **state)` |
| `test_basename_dotdot_only_falls_back` | function | `tests/test_pdf_export.c:57` | `static void test_basename_dotdot_only_falls_back(void **state)` |
| `test_basename_empty_and_null_fall_back` | function | `tests/test_pdf_export.c:96` | `static void test_basename_empty_and_null_fall_back(void **state)` |
| `test_basename_length_bound` | function | `tests/test_pdf_export.c:112` | `static void test_basename_length_bound(void **state)` |
| `test_basename_maps_spaces_and_reserved` | function | `tests/test_pdf_export.c:31` | `static void test_basename_maps_spaces_and_reserved(void **state)` |
| `test_basename_neutralizes_traversal` | function | `tests/test_pdf_export.c:49` | `static void test_basename_neutralizes_traversal(void **state)` |
| `test_basename_non_ascii_mapped` | function | `tests/test_pdf_export.c:87` | `static void test_basename_non_ascii_mapped(void **state)` |
| `test_basename_null_out_and_zero_size` | function | `tests/test_pdf_export.c:123` | `static void test_basename_null_out_and_zero_size(void **state)` |
| `test_basename_overflow_fails_closed` | function | `tests/test_pdf_export.c:130` | `static void test_basename_overflow_fails_closed(void **state)` |
| `test_basename_rejects_path_separators` | function | `tests/test_pdf_export.c:39` | `static void test_basename_rejects_path_separators(void **state)` |
| `test_basename_trims_edges` | function | `tests/test_pdf_export.c:64` | `static void test_basename_trims_edges(void **state)` |
| `test_build_path_basic` | function | `tests/test_pdf_export.c:139` | `static void test_build_path_basic(void **state)` |
| `test_build_path_empty_title_fallback` | function | `tests/test_pdf_export.c:162` | `static void test_build_path_empty_title_fallback(void **state)` |
| `test_build_path_ext_hostile_title_contained` | function | `tests/test_pdf_export.c:202` | `static void test_build_path_ext_hostile_title_contained(void **state)` |
| `test_build_path_ext_null_ext` | function | `tests/test_pdf_export.c:194` | `static void test_build_path_ext_null_ext(void **state)` |
| `test_build_path_ext_overflow_fails_closed` | function | `tests/test_pdf_export.c:213` | `static void test_build_path_ext_overflow_fails_closed(void **state)` |
| `test_build_path_ext_png` | function | `tests/test_pdf_export.c:186` | `static void test_build_path_ext_png(void **state)` |
| `test_build_path_hostile_title_contained` | function | `tests/test_pdf_export.c:153` | `static void test_build_path_hostile_title_contained(void **state)` |
| `test_build_path_null_args` | function | `tests/test_pdf_export.c:176` | `static void test_build_path_null_args(void **state)` |
| `test_build_path_overflow_fails_closed` | function | `tests/test_pdf_export.c:169` | `static void test_build_path_overflow_fails_closed(void **state)` |
| `test_build_path_trailing_slash` | function | `tests/test_pdf_export.c:146` | `static void test_build_path_trailing_slash(void **state)` |
| `test_paginate_breaks_without_splitting` | function | `tests/test_pdf_export.c:238` | `static void test_paginate_breaks_without_splitting(void **state)` |
| `test_paginate_invalid_args` | function | `tests/test_pdf_export.c:276` | `static void test_paginate_invalid_args(void **state)` |
| `test_paginate_oversized_row_not_split` | function | `tests/test_pdf_export.c:252` | `static void test_paginate_oversized_row_not_split(void **state)` |
| `test_paginate_preserves_gaps` | function | `tests/test_pdf_export.c:264` | `static void test_paginate_preserves_gaps(void **state)` |
| `test_paginate_single_page` | function | `tests/test_pdf_export.c:223` | `static void test_paginate_single_page(void **state)` |
| `main` | function | `tests/test_perf_trace.c:174` | `int main(void)` |
| `test_elapsed_us_normal` | function | `tests/test_perf_trace.c:89` | `static void test_elapsed_us_normal(void **state)` |
| `test_elapsed_us_underflow_guard` | function | `tests/test_perf_trace.c:95` | `static void test_elapsed_us_underflow_guard(void **state)` |
| `test_format_deterministic_and_only_nonempty_stages` | function | `tests/test_perf_trace.c:115` | `static void test_format_deterministic_and_only_nonempty_stages(void **state)` |
| `test_format_null_or_zero_cap` | function | `tests/test_perf_trace.c:152` | `static void test_format_null_or_zero_cap(void **state)` |
| `test_format_truncates_never_overflows` | function | `tests/test_perf_trace.c:138` | `static void test_format_truncates_never_overflows(void **state)` |
| `test_min_max_median` | function | `tests/test_perf_trace.c:42` | `static void test_min_max_median(void **state)` |
| `test_null_safe` | function | `tests/test_perf_trace.c:163` | `static void test_null_safe(void **state)` |
| `test_ring_wraparound_fifo` | function | `tests/test_perf_trace.c:55` | `static void test_ring_wraparound_fifo(void **state)` |
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

Next: [SYMBOLS_p14.md](SYMBOLS_p14.md)
