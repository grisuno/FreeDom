# Symbols (page 15 of 17)
Previous: [SYMBOLS_p14.md](SYMBOLS_p14.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `test_mode_str_roundtrip` | function | `tests/test_js_policy.c:53` | `static void test_mode_str_roundtrip(void **state)` |
| `test_trusted_requires_both_signals` | function | `tests/test_js_policy.c:68` | `static void test_trusted_requires_both_signals(void **state)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:175` | `assert_int_equal(js_eval_once("while(true)` |
| `assert_int_equal` | function | `tests/test_js_sandbox.c:190` | `assert_int_equal(js_eval(ctx, "while(true)` |
| `fetches` | type_alias | `tests/test_js_sandbox.c:459` | `typedef struct mod_host { int fetches;` |
| `main` | function | `tests/test_js_sandbox.c:722` | `int main(void)` |
| `mh_fetch` | function | `tests/test_js_sandbox.c:483` | `static char *mh_fetch(void *host, const char *url, size_t *len)` |
| `mh_resolve` | function | `tests/test_js_sandbox.c:462` | `static int mh_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)` |
| `mod_host` | struct | `tests/test_js_sandbox.c:460` | `` |
| `realm_expect` | function | `tests/test_js_sandbox.c:669` | `static void realm_expect(js_context *ctx, const char *src, const char *want)` |
| `self_fetch` | function | `tests/test_js_sandbox.c:630` | `static char *self_fetch(void *host, const char *url, size_t *len)` |
| `test_context_free_null_and_double` | function | `tests/test_js_sandbox.c:321` | `static void test_context_free_null_and_double(void **state)` |
| `test_context_new_and_free` | function | `tests/test_js_sandbox.c:79` | `static void test_context_new_and_free(void **state)` |
| `test_context_new_null_out` | function | `tests/test_js_sandbox.c:87` | `static void test_context_new_null_out(void **state)` |
| `test_deep_recursion_runs_and_runaway_is_caught` | function | `tests/test_js_sandbox.c:294` | `static void test_deep_recursion_runs_and_runaway_is_caught(void **state)` |
| `test_dynamic_import_of_long_data_url` | function | `tests/test_js_sandbox.c:582` | `static void test_dynamic_import_of_long_data_url(void **state)` |
| `test_eval_arithmetic` | function | `tests/test_js_sandbox.c:94` | `static void test_eval_arithmetic(void **state)` |
| `test_eval_named_captures_location` | function | `tests/test_js_sandbox.c:406` | `static void test_eval_named_captures_location(void **state)` |
| `test_eval_named_null_filename_defaults` | function | `tests/test_js_sandbox.c:427` | `static void test_eval_named_null_filename_defaults(void **state)` |
| `test_eval_null_args` | function | `tests/test_js_sandbox.c:329` | `static void test_eval_null_args(void **state)` |
| `test_eval_runtime_exception` | function | `tests/test_js_sandbox.c:129` | `static void test_eval_runtime_exception(void **state)` |
| `test_eval_string_concat` | function | `tests/test_js_sandbox.c:108` | `static void test_eval_string_concat(void **state)` |
| `test_eval_syntax_error` | function | `tests/test_js_sandbox.c:120` | `static void test_eval_syntax_error(void **state)` |
| `test_eval_thrown_primitive_has_no_location` | function | `tests/test_js_sandbox.c:442` | `static void test_eval_thrown_primitive_has_no_location(void **state)` |
| `test_filesystem_access_is_reference_error` | function | `tests/test_js_sandbox.c:156` | `static void test_filesystem_access_is_reference_error(void **state)` |
| `test_infinite_loop_times_out` | function | `tests/test_js_sandbox.c:169` | `static void test_infinite_loop_times_out(void **state)` |
| `test_limits_default_heap_holds_real_bundles` | function | `tests/test_js_sandbox.c:37` | `static void test_limits_default_heap_holds_real_bundles(void **state)` |
| `test_loc_file_may_contain_colons` | function | `tests/test_js_sandbox.c:363` | `static void test_loc_file_may_contain_colons(void **state)` |
| `test_loc_line_only_sets_col_zero` | function | `tests/test_js_sandbox.c:374` | `static void test_loc_line_only_sets_col_zero(void **state)` |
| `test_loc_parses_bare_frame` | function | `tests/test_js_sandbox.c:354` | `static void test_loc_parses_bare_frame(void **state)` |
| `test_loc_parses_named_frame` | function | `tests/test_js_sandbox.c:343` | `static void test_loc_parses_named_frame(void **state)` |
| `test_loc_rejects_garbage_and_null` | function | `tests/test_js_sandbox.c:391` | `static void test_loc_rejects_garbage_and_null(void **state)` |
| `test_loc_truncates_to_cap` | function | `tests/test_js_sandbox.c:383` | `static void test_loc_truncates_to_cap(void **state)` |
| `test_memory_limit_is_enforced` | function | `tests/test_js_sandbox.c:266` | `static void test_memory_limit_is_enforced(void **state)` |
| `test_module_errors_are_reported` | function | `tests/test_js_sandbox.c:528` | `static void test_module_errors_are_reported(void **state)` |
| `test_module_imports_resolve_and_run` | function | `tests/test_js_sandbox.c:507` | `static void test_module_imports_resolve_and_run(void **state)` |
| `test_module_self_await_teardown` | function | `tests/test_js_sandbox.c:640` | `static void test_module_self_await_teardown(void **state)` |
| `test_module_without_host_cannot_import` | function | `tests/test_js_sandbox.c:608` | `static void test_module_without_host_cannot_import(void **state)` |
| `test_no_io_globals` | function | `tests/test_js_sandbox.c:143` | `static void test_no_io_globals(void **state)` |
| `test_profiler_names_the_hot_function` | function | `tests/test_js_sandbox.c:201` | `static void test_profiler_names_the_hot_function(void **state)` |
| `test_realm_shares_time_budget` | function | `tests/test_js_sandbox.c:708` | `static void test_realm_shares_time_budget(void **state)` |
| `test_realms_isolate_and_clone` | function | `tests/test_js_sandbox.c:677` | `static void test_realms_isolate_and_clone(void **state)` |
| `test_result_free_on_zeroed` | function | `tests/test_js_sandbox.c:312` | `static void test_result_free_on_zeroed(void **state)` |
| `test_set_time_budget_applies` | function | `tests/test_js_sandbox.c:182` | `static void test_set_time_budget_applies(void **state)` |
| `test_stack_limit_follows_process_stack` | function | `tests/test_js_sandbox.c:281` | `static void test_stack_limit_follows_process_stack(void **state)` |
| `test_throw_tracer_records_caught_exceptions` | function | `tests/test_js_sandbox.c:235` | `static void test_throw_tracer_records_caught_exceptions(void **state)` |
| `test_validate_accepts_within_cap` | function | `tests/test_js_sandbox.c:72` | `static void test_validate_accepts_within_cap(void **state)` |
| `test_validate_rejects_empty` | function | `tests/test_js_sandbox.c:60` | `static void test_validate_rejects_empty(void **state)` |
| `test_validate_rejects_null` | function | `tests/test_js_sandbox.c:55` | `static void test_validate_rejects_null(void **state)` |
| `test_validate_rejects_oversize` | function | `tests/test_js_sandbox.c:65` | `static void test_validate_rejects_oversize(void **state)` |
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
| `expect_private` | function | `tests/test_net_guard.c:10` | `static void expect_private(const char *const *ips, size_t n, int want)` |
| `main` | function | `tests/test_net_guard.c:150` | `int main(void)` |
| `test_decide` | function | `tests/test_net_guard.c:124` | `static void test_decide(void **state)` |
| `test_host_is_ip` | function | `tests/test_net_guard.c:112` | `static void test_host_is_ip(void **state)` |
| `test_host_is_local` | function | `tests/test_net_guard.c:93` | `static void test_host_is_local(void **state)` |
| `test_ipv4_embedded_in_ipv6_is_unwrapped` | function | `tests/test_net_guard.c:56` | `static void test_ipv4_embedded_in_ipv6_is_unwrapped(void **state)` |
| `test_ipv4_private_and_special_ranges` | function | `tests/test_net_guard.c:16` | `static void test_ipv4_private_and_special_ranges(void **state)` |
| `test_ipv4_public_edges` | function | `tests/test_net_guard.c:29` | `static void test_ipv4_public_edges(void **state)` |
| `test_ipv6_private_and_special_ranges` | function | `tests/test_net_guard.c:41` | `static void test_ipv6_private_and_special_ranges(void **state)` |
| `test_unclassifiable_fails_closed` | function | `tests/test_net_guard.c:71` | `static void test_unclassifiable_fails_closed(void **state)` |
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
| `applies` | function | `tests/test_page_view.c:4952` | `* <style>: an extern rule applies (presentation and display:none alike);` |
| `box_of_run_with_bg` | function | `tests/test_page_view.c:4016` | `static const pv_box_def *box_of_run_with_bg(const pv_view *v, int bg)` |
| `break` | function | `tests/test_page_view.c:705` | `* block break (from entering <p>);` |
| `collect_elements` | function | `tests/test_page_view.c:4667` | `static void collect_elements(lxb_dom_node_t *n, lxb_dom_element_t **out, size_t *cnt, size_t cap)` |
| `count_empty_lines` | function | `tests/test_page_view.c:3719` | `static int count_empty_lines(const pv_view *v)` |
| `count_inputs` | function | `tests/test_page_view.c:3616` | `static size_t count_inputs(const pv_view *v, int type)` |
| `dropped` | function | `tests/test_page_view.c:429` | `* either flank is dropped (the inter-cell rule above stays). */ static void test_build_table_inli...` |
| `find_image` | function | `tests/test_page_view.c:57` | `static const pv_run *find_image(const pv_view *v, const char *src)` |
| `find_input` | function | `tests/test_page_view.c:3518` | `static const pv_run *find_input(const pv_view *v, const char *name)` |
| `find_link` | function | `tests/test_page_view.c:75` | `static const pv_run *find_link(const pv_view *v, const char *href)` |
| `find_sub` | function | `tests/test_page_view.c:48` | `static const pv_run *find_sub(const pv_view *v, const char *sub)` |
| `find_svg` | function | `tests/test_page_view.c:83` | `static const pv_run *find_svg(const pv_view *v)` |
| `find_text` | function | `tests/test_page_view.c:39` | `static const pv_run *find_text(const pv_view *v, const char *text)` |
| `find_video` | function | `tests/test_page_view.c:66` | `static const pv_run *find_video(const pv_view *v, const char *src)` |
| `float_id` | function | `tests/test_page_view.c:1634` | `* A run inside a float nested in another float reports the inner element as * float_id (unchanged) plus the outer...` |
| `form` | function | `tests/test_page_view.c:3584` | `* invisible PV_IN_SUBMIT_BOX proxy carries the form (spec/page_view.md). */ assert_non_null(find_text(v, "Log in"));` |
| `height` | function | `tests/test_page_view.c:4926` | `* real height (jkanime's donghuas/ovas panes are display:none, yet all their  * thumbnails flowed...` |
| `ids_probe` | struct | `tests/test_page_view.c:1384` | `` |
| `ids_probe_fn` | function | `tests/test_page_view.c:1385` | `static dom_node_id ids_probe_fn(void *ctx, const void *native)` |
| `it` | function | `tests/test_page_view.c:636` | `* the rest of the row share it (so an overflowing table degrades to one row per * line, not one blob). */...` |
| `line` | function | `tests/test_page_view.c:2008` | `* contiguous item run and dropped every cell onto its own line (Wikipedia's sister  * projects ta...` |
| `main` | function | `tests/test_page_view.c:5760` | `int main(void)` |
| `ordinal` | function | `tests/test_page_view.c:1936` | `* cont_item ordinal (they are one flex/grid item and must flow together in one * cell);` |
| `parse` | function | `tests/test_page_view.c:31` | `static hp_document *parse(const char *html)` |
| `reverted` | function | `tests/test_page_view.c:4912` | `* behavior of treating inline display:none as visible when JS is off * was reverted (commit 897f414 regression)...` |
| `run_with_text` | function | `tests/test_page_view.c:4086` | `static const pv_run *run_with_text(const pv_view *v, const char *text)` |
| `scales` | function | `tests/test_page_view.c:4828` | `* value the UA rule scales (tanda 19). */ static void test_build_heading_own_relative_size_replac...` |
| `short` | function | `tests/test_page_view.c:1820` | `* heading came out two thirds short (and its UA margin with it, once it had a box). */ static voi...` |
| `size` | function | `tests/test_page_view.c:774` | `* size (~100px) instead of the CSS 40px, blowing up flex rows (slashdot socials). */ static void ...` |
| `table` | function | `tests/test_page_view.c:5717` | `* table (the cache replays the root matcher), and must equal the uncached build. */ static void t...` |
| `test_after_box_on_empty_element` | function | `tests/test_page_view.c:4375` | `static void test_after_box_on_empty_element(void **state)` |
| `test_after_content_stays_in_flex_item` | function | `tests/test_page_view.c:4352` | `static void test_after_content_stays_in_flex_item(void **state)` |
| `test_append_copies_fields` | function | `tests/test_page_view.c:102` | `static void test_append_copies_fields(void **state)` |
| `test_append_image_copies_fields` | function | `tests/test_page_view.c:129` | `static void test_append_image_copies_fields(void **state)` |
| `test_append_image_null_args` | function | `tests/test_page_view.c:145` | `static void test_append_image_null_args(void **state)` |
| `test_append_null_args` | function | `tests/test_page_view.c:209` | `static void test_append_null_args(void **state)` |
| `test_append_transcodes_cp1252_quotes` | function | `tests/test_page_view.c:181` | `static void test_append_transcodes_cp1252_quotes(void **state)` |
| `test_append_transcodes_latin1` | function | `tests/test_page_view.c:160` | `static void test_append_transcodes_latin1(void **state)` |
| `test_append_transcodes_word` | function | `tests/test_page_view.c:170` | `static void test_append_transcodes_word(void **state)` |
| `test_append_undefined_cp1252_is_qmark` | function | `tests/test_page_view.c:191` | `static void test_append_undefined_cp1252_is_qmark(void **state)` |
| `test_append_valid_utf8_passthrough` | function | `tests/test_page_view.c:201` | `static void test_append_valid_utf8_passthrough(void **state)` |
| `test_append_video_copies_fields` | function | `tests/test_page_view.c:5505` | `static void test_append_video_copies_fields(void **state)` |
| `test_append_video_no_poster` | function | `tests/test_page_view.c:5524` | `static void test_append_video_no_poster(void **state)` |
| `test_append_video_null_args` | function | `tests/test_page_view.c:5540` | `static void test_append_video_null_args(void **state)` |
| `test_author_list_padding_replaces_ua_indent` | function | `tests/test_page_view.c:4985` | `static void test_author_list_padding_replaces_ua_indent(void **state)` |
| `test_before_box_before_text` | function | `tests/test_page_view.c:4256` | `static void test_before_box_before_text(void **state)` |
| `test_before_box_on_empty_element` | function | `tests/test_page_view.c:4156` | `static void test_before_box_on_empty_element(void **state)` |
| `test_before_box_on_host_with_only_element_children` | function | `tests/test_page_view.c:4175` | `static void test_before_box_on_host_with_only_element_children(void **state)` |
| `test_before_rides_float_and_container` | function | `tests/test_page_view.c:5010` | `static void test_before_rides_float_and_container(void **state)` |
| `test_block_inside_inline_block_in_line` | function | `tests/test_page_view.c:5108` | `static void test_block_inside_inline_block_in_line(void **state)` |
| `test_body_background_propagates_to_canvas` | function | `tests/test_page_view.c:4194` | `static void test_body_background_propagates_to_canvas(void **state)` |
| `test_box_defaults_and_setter` | function | `tests/test_page_view.c:2853` | `static void test_box_defaults_and_setter(void **state)` |
| `test_box_min_width_zero_is_declared` | function | `tests/test_page_view.c:3967` | `static void test_box_min_width_zero_is_declared(void **state)` |
| `test_br_continuation_flag` | function | `tests/test_page_view.c:3762` | `static void test_br_continuation_flag(void **state)` |
| `test_br_opening_line_is_empty_line` | function | `tests/test_page_view.c:3731` | `static void test_br_opening_line_is_empty_line(void **state)` |
| `test_build_abs_child_is_not_a_flex_item` | function | `tests/test_page_view.c:2605` | `static void test_build_abs_child_is_not_a_flex_item(void **state)` |
| `test_build_absolute_inside_float_escapes` | function | `tests/test_page_view.c:1783` | `static void test_build_absolute_inside_float_escapes(void **state)` |
| `test_build_anon_inline_block_row_wraps` | function | `tests/test_page_view.c:1455` | `static void test_build_anon_inline_block_row_wraps(void **state)` |
| `test_build_anon_row_word_space_gap` | function | `tests/test_page_view.c:1417` | `static void test_build_anon_row_word_space_gap(void **state)` |
| `test_build_audio_as_video_kind` | function | `tests/test_page_view.c:5634` | `static void test_build_audio_as_video_kind(void **state)` |
| `test_build_author_color` | function | `tests/test_page_view.c:1169` | `static void test_build_author_color(void **state)` |
| `test_build_bgcolor_attr_fallback` | function | `tests/test_page_view.c:589` | `static void test_build_bgcolor_attr_fallback(void **state)` |
| `test_build_block_break_between_paragraphs` | function | `tests/test_page_view.c:673` | `static void test_build_block_break_between_paragraphs(void **state)` |
| `test_build_box_leaf_inline` | function | `tests/test_page_view.c:2818` | `static void test_build_box_leaf_inline(void **state)` |
| `test_build_box_tree_empty_no_box` | function | `tests/test_page_view.c:3506` | `static void test_build_box_tree_empty_no_box(void **state)` |
| `test_build_box_tree_textless_wrapper` | function | `tests/test_page_view.c:3414` | `static void test_build_box_tree_textless_wrapper(void **state)` |
| `test_build_boxdeco_border_padding` | function | `tests/test_page_view.c:3005` | `static void test_build_boxdeco_border_padding(void **state)` |
| `test_build_boxdeco_defaults_no_box` | function | `tests/test_page_view.c:3320` | `static void test_build_boxdeco_defaults_no_box(void **state)` |
| `test_build_boxdeco_dims_alone_trigger_box` | function | `tests/test_page_view.c:3215` | `static void test_build_boxdeco_dims_alone_trigger_box(void **state)` |
| `test_build_boxdeco_fit_content_height_is_auto` | function | `tests/test_page_view.c:2965` | `static void test_build_boxdeco_fit_content_height_is_auto(void **state)` |
| `test_build_boxdeco_h_margin_alone_creates_box` | function | `tests/test_page_view.c:2884` | `static void test_build_boxdeco_h_margin_alone_creates_box(void **state)` |
| `test_build_boxdeco_h_margin_zero_auto_no_box` | function | `tests/test_page_view.c:2904` | `static void test_build_boxdeco_h_margin_zero_auto_no_box(void **state)` |
| `test_build_boxdeco_min_content_height_is_auto` | function | `tests/test_page_view.c:2987` | `static void test_build_boxdeco_min_content_height_is_auto(void **state)` |
| `test_build_boxdeco_shadow_outline` | function | `tests/test_page_view.c:3113` | `static void test_build_boxdeco_shadow_outline(void **state)` |
| `test_build_boxdeco_shared_id_within_block` | function | `tests/test_page_view.c:3352` | `static void test_build_boxdeco_shared_id_within_block(void **state)` |
| `test_build_boxdeco_sibling_blocks_distinct_ids` | function | `tests/test_page_view.c:3334` | `static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state)` |
| `test_build_boxdeco_visibility_overflow_cursor` | function | `tests/test_page_view.c:3136` | `static void test_build_boxdeco_visibility_overflow_cursor(void **state)` |
| `test_build_boxdef_carries_node_id` | function | `tests/test_page_view.c:2928` | `static void test_build_boxdef_carries_node_id(void **state)` |
| `test_build_caret_color_inherited` | function | `tests/test_page_view.c:5481` | `static void test_build_caret_color_inherited(void **state)` |
| `test_build_combinator_selectors` | function | `tests/test_page_view.c:1301` | `static void test_build_combinator_selectors(void **state)` |
| `test_build_component_custom_props` | function | `tests/test_page_view.c:4861` | `static void test_build_component_custom_props(void **state)` |
| `test_build_cont_item_identity` | function | `tests/test_page_view.c:1938` | `static void test_build_cont_item_identity(void **state)` |
| `test_build_container_registry_holds_a_real_page` | function | `tests/test_page_view.c:2407` | `static void test_build_container_registry_holds_a_real_page(void **state)` |
| `test_build_content_visibility_hidden_folds` | function | `tests/test_page_view.c:5436` | `static void test_build_content_visibility_hidden_folds(void **state)` |
| `test_build_control_without_form` | function | `tests/test_page_view.c:4448` | `static void test_build_control_without_form(void **state)` |
| `test_build_css_bold_and_inline_wins` | function | `tests/test_page_view.c:4805` | `static void test_build_css_bold_and_inline_wins(void **state)` |
| `test_build_cursor_alone_triggers_box` | function | `tests/test_page_view.c:3160` | `static void test_build_cursor_alone_triggers_box(void **state)` |
| `test_build_display_none_hidden` | function | `tests/test_page_view.c:4900` | `static void test_build_display_none_hidden(void **state)` |
| `test_build_empty_box_gets_run_and_box` | function | `tests/test_page_view.c:3036` | `static void test_build_empty_box_gets_run_and_box(void **state)` |
| `test_build_empty_document` | function | `tests/test_page_view.c:1133` | `static void test_build_empty_document(void **state)` |
| `test_build_empty_flex_grow_spacer` | function | `tests/test_page_view.c:951` | `static void test_build_empty_flex_grow_spacer(void **state)` |
| `test_build_flex_anchor_is_its_own_block` | function | `tests/test_page_view.c:1844` | `static void test_build_flex_anchor_is_its_own_block(void **state)` |
| `test_build_flex_container` | function | `tests/test_page_view.c:1339` | `static void test_build_flex_container(void **state)` |
| `test_build_flex_container_from_sheet` | function | `tests/test_page_view.c:2706` | `static void test_build_flex_container_from_sheet(void **state)` |
| `test_build_flex_item_values` | function | `tests/test_page_view.c:1527` | `static void test_build_flex_item_values(void **state)` |
| `test_build_flex_whitespace_not_item` | function | `tests/test_page_view.c:1860` | `static void test_build_flex_whitespace_not_item(void **state)` |
| `test_build_flex_wrap_align_row_gap` | function | `tests/test_page_view.c:1486` | `static void test_build_flex_wrap_align_row_gap(void **state)` |
| `test_build_float_outermost_founder` | function | `tests/test_page_view.c:1637` | `static void test_build_float_outermost_founder(void **state)` |
| `test_build_float_threading` | function | `tests/test_page_view.c:1591` | `static void test_build_float_threading(void **state)` |
| `test_build_float_widthless_stays_unset` | function | `tests/test_page_view.c:895` | `static void test_build_float_widthless_stays_unset(void **state)` |
| `test_build_flow_table_row_is_one_block` | function | `tests/test_page_view.c:3078` | `static void test_build_flow_table_row_is_one_block(void **state)` |
| `test_build_font_list_inherits` | function | `tests/test_page_view.c:2535` | `static void test_build_font_list_inherits(void **state)` |
| `test_build_fontface_hash` | function | `tests/test_page_view.c:2178` | `static void test_build_fontface_hash(void **state)` |
| `test_build_form_post_and_hidden` | function | `tests/test_page_view.c:3561` | `static void test_build_form_post_and_hidden(void **state)` |
| `test_build_frame_with_only_oof_content_keeps_box` | function | `tests/test_page_view.c:3442` | `static void test_build_frame_with_only_oof_content_keeps_box(void **state)` |
| `test_build_grid_autofill_marker` | function | `tests/test_page_view.c:2158` | `static void test_build_grid_autofill_marker(void **state)` |
| `test_build_grid_columns_from_sheet` | function | `tests/test_page_view.c:2728` | `static void test_build_grid_columns_from_sheet(void **state)` |
| `test_build_grid_container` | function | `tests/test_page_view.c:2138` | `static void test_build_grid_container(void **state)` |
| `test_build_hbox_container_width_never_seeds_items` | function | `tests/test_page_view.c:1754` | `static void test_build_hbox_container_width_never_seeds_items(void **state)` |
| `test_build_hbox_margin_above_container_merges` | function | `tests/test_page_view.c:1734` | `static void test_build_hbox_margin_above_container_merges(void **state)` |
| `test_build_heading_level` | function | `tests/test_page_view.c:248` | `static void test_build_heading_level(void **state)` |
| `test_build_iframe_display_none_hidden` | function | `tests/test_page_view.c:5701` | `static void test_build_iframe_display_none_hidden(void **state)` |
| `test_build_iframe_emits_navigable_link` | function | `tests/test_page_view.c:5648` | `static void test_build_iframe_emits_navigable_link(void **state)` |
| `test_build_iframe_without_src_ignored` | function | `tests/test_page_view.c:5688` | `static void test_build_iframe_without_src_ignored(void **state)` |
| `test_build_image_auto_size_keeps_attr` | function | `tests/test_page_view.c:931` | `static void test_build_image_auto_size_keeps_attr(void **state)` |
| `test_build_image_css_size_overrides_attr` | function | `tests/test_page_view.c:914` | `static void test_build_image_css_size_overrides_attr(void **state)` |
| `test_build_image_in_skipped_subtree_ignored` | function | `tests/test_page_view.c:969` | `static void test_build_image_in_skipped_subtree_ignored(void **state)` |
| `test_build_image_no_src_and_no_srcset_ignored` | function | `tests/test_page_view.c:1118` | `static void test_build_image_no_src_and_no_srcset_ignored(void **state)` |
| `test_build_image_plain_src_wins_over_srcset` | function | `tests/test_page_view.c:1075` | `static void test_build_image_plain_src_wins_over_srcset(void **state)` |
| `test_build_image_px_and_tracking_dims` | function | `tests/test_page_view.c:749` | `static void test_build_image_px_and_tracking_dims(void **state)` |
| `test_build_image_rendering_inherited` | function | `tests/test_page_view.c:5462` | `static void test_build_image_rendering_inherited(void **state)` |
| `test_build_image_srcset_data_url_not_truncated_at_comma` | function | `tests/test_page_view.c:1103` | `static void test_build_image_srcset_data_url_not_truncated_at_comma(void **state)` |
| `test_build_image_srcset_fallback_when_no_src` | function | `tests/test_page_view.c:1059` | `static void test_build_image_srcset_fallback_when_no_src(void **state)` |
| `test_build_image_srcset_single_no_descriptor` | function | `tests/test_page_view.c:1090` | `static void test_build_image_srcset_single_no_descriptor(void **state)` |
| `test_build_image_unknown_dims` | function | `tests/test_page_view.c:734` | `static void test_build_image_unknown_dims(void **state)` |
| `test_build_image_with_dims` | function | `tests/test_page_view.c:717` | `static void test_build_image_with_dims(void **state)` |
| `test_build_image_without_src_dims_emit_broken` | function | `tests/test_page_view.c:1042` | `static void test_build_image_without_src_dims_emit_broken(void **state)` |
| `test_build_image_without_src_ignored` | function | `tests/test_page_view.c:1011` | `static void test_build_image_without_src_ignored(void **state)` |
| `test_build_img_loading_lazy_is_recorded` | function | `tests/test_page_view.c:2274` | `static void test_build_img_loading_lazy_is_recorded(void **state)` |
| `test_build_inline_block_row_alignment` | function | `tests/test_page_view.c:2250` | `static void test_build_inline_block_row_alignment(void **state)` |
| `test_build_inline_block_row_ignores_oof_child` | function | `tests/test_page_view.c:2347` | `static void test_build_inline_block_row_ignores_oof_child(void **state)` |
| `test_build_inline_emphasis` | function | `tests/test_page_view.c:265` | `static void test_build_inline_emphasis(void **state)` |
| `test_build_inline_flex_is_inline_level` | function | `tests/test_page_view.c:2371` | `static void test_build_inline_flex_is_inline_level(void **state)` |
| `test_build_inline_link_no_break_within_paragraph` | function | `tests/test_page_view.c:699` | `static void test_build_inline_link_no_break_within_paragraph(void **state)` |
| `test_build_inline_whitespace_kept` | function | `tests/test_page_view.c:1916` | `static void test_build_inline_whitespace_kept(void **state)` |
| `test_build_input_bare_chrome` | function | `tests/test_page_view.c:2299` | `static void test_build_input_bare_chrome(void **state)` |
| `test_build_input_own_box_and_placeholder` | function | `tests/test_page_view.c:2320` | `static void test_build_input_own_box_and_placeholder(void **state)` |
| `test_build_intrinsic_width_flag` | function | `tests/test_page_view.c:2461` | `static void test_build_intrinsic_width_flag(void **state)` |
| `test_build_link_with_href` | function | `tests/test_page_view.c:654` | `static void test_build_link_with_href(void **state)` |
| `test_build_live_iframe_is_a_sized_replaced_run` | function | `tests/test_page_view.c:5668` | `static void test_build_live_iframe_is_a_sized_replaced_run(void **state)` |
| `test_build_live_uses_resolver_ids` | function | `tests/test_page_view.c:1394` | `static void test_build_live_uses_resolver_ids(void **state)` |
| `test_build_lone_float_container_is_row_item` | function | `tests/test_page_view.c:2433` | `static void test_build_lone_float_container_is_row_item(void **state)` |
| `test_build_long_class_attribute_keeps_classes` | function | `tests/test_page_view.c:2203` | `static void test_build_long_class_attribute_keeps_classes(void **state)` |
| `test_build_nested_table_not_flattened` | function | `tests/test_page_view.c:605` | `static void test_build_nested_table_not_flattened(void **state)` |
| `test_build_node_id_matches_dom_index` | function | `tests/test_page_view.c:5347` | `static void test_build_node_id_matches_dom_index(void **state)` |
| `test_build_noscript_hidden_when_js_on` | function | `tests/test_page_view.c:998` | `static void test_build_noscript_hidden_when_js_on(void **state)` |
| `test_build_noscript_shown_when_js_off` | function | `tests/test_page_view.c:985` | `static void test_build_noscript_shown_when_js_off(void **state)` |
| `test_build_null_args` | function | `tests/test_page_view.c:226` | `static void test_build_null_args(void **state)` |
| `test_build_oof_flag_badges_idiom` | function | `tests/test_page_view.c:2686` | `static void test_build_oof_flag_badges_idiom(void **state)` |
| `test_build_oof_flag_via_cascade` | function | `tests/test_page_view.c:2662` | `static void test_build_oof_flag_via_cascade(void **state)` |
| `test_build_oof_image_carries_block_id` | function | `tests/test_page_view.c:1669` | `static void test_build_oof_image_carries_block_id(void **state)` |
| `test_build_ordered_and_nested_list` | function | `tests/test_page_view.c:324` | `static void test_build_ordered_and_nested_list(void **state)` |
| `test_build_plain_text` | function | `tests/test_page_view.c:235` | `static void test_build_plain_text(void **state)` |
| `test_build_pointer_events_on_box` | function | `tests/test_page_view.c:5417` | `static void test_build_pointer_events_on_box(void **state)` |
| `test_build_pseudo_classes_and_siblings` | function | `tests/test_page_view.c:4520` | `static void test_build_pseudo_classes_and_siblings(void **state)` |
| `test_build_reader_skips_boilerplate` | function | `tests/test_page_view.c:5303` | `static void test_build_reader_skips_boilerplate(void **state)` |
| `test_build_root_element_style_inherits` | function | `tests/test_page_view.c:2567` | `static void test_build_root_element_style_inherits(void **state)` |
| `test_build_root_font_size_is_overridable` | function | `tests/test_page_view.c:2585` | `static void test_build_root_font_size_is_overridable(void **state)` |
| `test_build_search_form_get` | function | `tests/test_page_view.c:3528` | `static void test_build_search_form_get(void **state)` |
| `test_build_select_defaults_to_first_option` | function | `tests/test_page_view.c:4431` | `static void test_build_select_defaults_to_first_option(void **state)` |
| `test_build_select_shows_selected_option` | function | `tests/test_page_view.c:4392` | `static void test_build_select_shows_selected_option(void **state)` |
| `test_build_skips_script_and_style` | function | `tests/test_page_view.c:685` | `static void test_build_skips_script_and_style(void **state)` |
| `test_build_sourceless_video_keeps_its_box` | function | `tests/test_page_view.c:3466` | `static void test_build_sourceless_video_keeps_its_box(void **state)` |
| `test_build_style_cache_distinct_siblings` | function | `tests/test_page_view.c:4643` | `static void test_build_style_cache_distinct_siblings(void **state)` |
| `test_build_styled_external_css` | function | `tests/test_page_view.c:4956` | `static void test_build_styled_external_css(void **state)` |
| `test_build_svg_css_stroke_inherited` | function | `tests/test_page_view.c:2499` | `static void test_build_svg_css_stroke_inherited(void **state)` |
| `test_build_svg_fills_border_box_ancestor` | function | `tests/test_page_view.c:834` | `static void test_build_svg_fills_border_box_ancestor(void **state)` |
| `test_build_svg_no_ancestor_width_unset` | function | `tests/test_page_view.c:854` | `static void test_build_svg_no_ancestor_width_unset(void **state)` |
| `test_build_table_cell_author_styles` | function | `tests/test_page_view.c:4583` | `static void test_build_table_cell_author_styles(void **state)` |
| `test_build_table_cellless_display_table_is_not_nested` | function | `tests/test_page_view.c:2066` | `static void test_build_table_cellless_display_table_is_not_nested(void **state)` |
| `test_build_table_colspan_rowspan` | function | `tests/test_page_view.c:2092` | `static void test_build_table_colspan_rowspan(void **state)` |
| `test_build_table_flattens_cell` | function | `tests/test_page_view.c:455` | `static void test_build_table_flattens_cell(void **state)` |
| `test_build_table_grid` | function | `tests/test_page_view.c:347` | `static void test_build_table_grid(void **state)` |
| `test_build_table_intercell_whitespace_dropped` | function | `tests/test_page_view.c:387` | `static void test_build_table_intercell_whitespace_dropped(void **state)` |
| `test_build_text_align_and_font_size` | function | `tests/test_page_view.c:4735` | `static void test_build_text_align_and_font_size(void **state)` |
| `test_build_text_balance_inherits` | function | `tests/test_page_view.c:2520` | `static void test_build_text_balance_inherits(void **state)` |
| `test_build_text_decoration` | function | `tests/test_page_view.c:4782` | `static void test_build_text_decoration(void **state)` |
| `test_build_text_overflow_and_word_break` | function | `tests/test_page_view.c:3260` | `static void test_build_text_overflow_and_word_break(void **state)` |
| `test_build_textarea_value` | function | `tests/test_page_view.c:3597` | `static void test_build_textarea_value(void **state)` |
| `test_build_two_forms_distinct_groups` | function | `tests/test_page_view.c:4461` | `static void test_build_two_forms_distinct_groups(void **state)` |
| `test_build_unordered_list` | function | `tests/test_page_view.c:306` | `static void test_build_unordered_list(void **state)` |
| `test_build_video_fallback_suppressed` | function | `tests/test_page_view.c:5608` | `static void test_build_video_fallback_suppressed(void **state)` |
| `test_build_video_source_type_preference` | function | `tests/test_page_view.c:5590` | `static void test_build_video_source_type_preference(void **state)` |
| `test_build_video_uses_source_child` | function | `tests/test_page_view.c:5570` | `static void test_build_video_uses_source_child(void **state)` |
| `test_build_video_with_source` | function | `tests/test_page_view.c:5550` | `static void test_build_video_with_source(void **state)` |
| `test_build_video_without_src_ignored` | function | `tests/test_page_view.c:5623` | `static void test_build_video_without_src_ignored(void **state)` |
| `test_build_zero_padding_is_not_a_box` | function | `tests/test_page_view.c:3061` | `static void test_build_zero_padding_is_not_a_box(void **state)` |
| `test_button_content_flows` | function | `tests/test_page_view.c:3638` | `static void test_button_content_flows(void **state)` |
| `test_button_icon_invents_no_label` | function | `tests/test_page_view.c:3623` | `static void test_button_icon_invents_no_label(void **state)` |
| `test_button_submit_proxy` | function | `tests/test_page_view.c:3652` | `static void test_button_submit_proxy(void **state)` |
| `test_button_ua_face_loses_to_author` | function | `tests/test_page_view.c:3677` | `static void test_button_ua_face_loses_to_author(void **state)` |
| `test_checked_boolean_attribute_is_detected` | function | `tests/test_page_view.c:4063` | `static void test_checked_boolean_attribute_is_detected(void **state)` |
| `test_container_defaults` | function | `tests/test_page_view.c:2767` | `static void test_container_defaults(void **state)` |
| `test_flex_item_inline_is_blockified` | function | `tests/test_page_view.c:3987` | `static void test_flex_item_inline_is_blockified(void **state)` |
| `test_float_inner_blocks_keep_breaks` | function | `tests/test_page_view.c:3814` | `static void test_float_inner_blocks_keep_breaks(void **state)` |
| `test_free_null_and_double` | function | `tests/test_page_view.c:217` | `static void test_free_null_and_double(void **state)` |
| `test_gradient_text_runs` | function | `tests/test_page_view.c:1223` | `static void test_gradient_text_runs(void **state)` |
| `test_grid_line_placement_nested_container_item` | function | `tests/test_page_view.c:3879` | `static void test_grid_line_placement_nested_container_item(void **state)` |
| `test_grid_line_placement_plain_item` | function | `tests/test_page_view.c:3854` | `static void test_grid_line_placement_plain_item(void **state)` |
| `test_hidden_attribute_is_display_none` | function | `tests/test_page_view.c:3831` | `static void test_hidden_attribute_is_display_none(void **state)` |
| `test_inline_level_tag_list_stays_in_line` | function | `tests/test_page_view.c:5041` | `static void test_inline_level_tag_list_stays_in_line(void **state)` |
| `test_inline_pseudo_registers_no_box` | function | `tests/test_page_view.c:4289` | `static void test_inline_pseudo_registers_no_box(void **state)` |
| `test_link_color_inherit` | function | `tests/test_page_view.c:4033` | `static void test_link_color_inherit(void **state)` |
| `test_marker_only_for_list_item_display` | function | `tests/test_page_view.c:5069` | `static void test_marker_only_for_list_item_display(void **state)` |
| `test_mask_reaches_the_box` | function | `tests/test_page_view.c:4218` | `static void test_mask_reaches_the_box(void **state)` |
| `test_new_is_empty` | function | `tests/test_page_view.c:93` | `static void test_new_is_empty(void **state)` |
| `test_pct_padding_generates_box` | function | `tests/test_page_view.c:4047` | `static void test_pct_padding_generates_box(void **state)` |
| `test_phrasing_ua_faces` | function | `tests/test_page_view.c:3699` | `static void test_phrasing_ua_faces(void **state)` |
| `test_pseudo_after_on_element_with_children` | function | `tests/test_page_view.c:5184` | `static void test_pseudo_after_on_element_with_children(void **state)` |
| `test_pseudo_after_on_whitespace_only_no_run` | function | `tests/test_page_view.c:5262` | `static void test_pseudo_after_on_whitespace_only_no_run(void **state)` |
| `test_pseudo_before_escape_end_to_end` | function | `tests/test_page_view.c:5249` | `static void test_pseudo_before_escape_end_to_end(void **state)` |
| `test_pseudo_before_fires_with_nested_text` | function | `tests/test_page_view.c:5276` | `static void test_pseudo_before_fires_with_nested_text(void **state)` |
| `test_pseudo_before_on_element_with_children` | function | `tests/test_page_view.c:5169` | `static void test_pseudo_before_on_element_with_children(void **state)` |
| `test_pseudo_before_on_empty` | function | `tests/test_page_view.c:5156` | `static void test_pseudo_before_on_empty(void **state)` |
| `test_pseudo_before_on_textless_subtree` | function | `tests/test_page_view.c:5233` | `static void test_pseudo_before_on_textless_subtree(void **state)` |
| `test_pseudo_both_before_and_after` | function | `tests/test_page_view.c:5199` | `static void test_pseudo_both_before_and_after(void **state)` |
| `test_pseudo_content_inherits_color` | function | `tests/test_page_view.c:4332` | `static void test_pseudo_content_inherits_color(void **state)` |
| `test_pseudo_display_none_generates_nothing` | function | `tests/test_page_view.c:4272` | `static void test_pseudo_display_none_generates_nothing(void **state)` |
| `test_pseudo_no_content_no_run` | function | `tests/test_page_view.c:5289` | `static void test_pseudo_no_content_no_run(void **state)` |
| `test_root_insets` | function | `tests/test_page_view.c:2230` | `static void test_root_insets(void **state)` |
| `test_set_color_model` | function | `tests/test_page_view.c:1147` | `static void test_set_color_model(void **state)` |
| `test_set_node_id_model` | function | `tests/test_page_view.c:5331` | `static void test_set_node_id_model(void **state)` |
| `test_set_text_style_model` | function | `tests/test_page_view.c:5386` | `static void test_set_text_style_model(void **state)` |
| `test_style_path_matches_uncached_chain` | function | `tests/test_page_view.c:4675` | `static void test_style_path_matches_uncached_chain(void **state)` |
| `test_svg_append_root_attrs` | function | `tests/test_page_view.c:2482` | `static void test_svg_append_root_attrs(void **state)` |
| `test_text_fill_color_runs` | function | `tests/test_page_view.c:1255` | `static void test_text_fill_color_runs(void **state)` |
| `unset` | function | `tests/test_page_view.c:814` | `* unset (-1) so the render step derives it from the viewBox aspect. */ static void test_build_svg...` |
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
| `_GNU_SOURCE` | macro | `tests/test_pq_seal.c:1` | `#define _GNU_SOURCE` |
| `main` | function | `tests/test_pq_seal.c:95` | `int main(void)` |
| `test_each_seal_is_fresh` | function | `tests/test_pq_seal.c:31` | `static void test_each_seal_is_fresh(void **state)` |
| `test_export_import_keeps_decapsulation` | function | `tests/test_pq_seal.c:77` | `static void test_export_import_keeps_decapsulation(void **state)` |
| `test_format_errors` | function | `tests/test_pq_seal.c:65` | `static void test_format_errors(void **state)` |
| `test_requires_both_secrets_and_detects_tamper` | function | `tests/test_pq_seal.c:44` | `static void test_requires_both_secrets_and_detects_tamper(void **state)` |
| `test_seal_open_roundtrip` | function | `tests/test_pq_seal.c:12` | `static void test_seal_open_roundtrip(void **state)` |
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
| `main` | function | `tests/test_prefs.c:424` | `int main(void)` |
| `test_bookmark_toggle_and_cap` | function | `tests/test_prefs.c:267` | `static void test_bookmark_toggle_and_cap(void **state)` |
| `test_bookmarks_page_escapes` | function | `tests/test_prefs.c:375` | `static void test_bookmarks_page_escapes(void **state)` |
| `test_format_null_args` | function | `tests/test_prefs.c:412` | `static void test_format_null_args(void **state)` |
| `test_history_dedup_and_evict` | function | `tests/test_prefs.c:295` | `static void test_history_dedup_and_evict(void **state)` |
| `test_hostile_title_cleaned` | function | `tests/test_prefs.c:237` | `static void test_hostile_title_cleaned(void **state)` |
| `test_init_defaults` | function | `tests/test_prefs.c:25` | `static void test_init_defaults(void **state)` |
| `test_invalid_urls_rejected` | function | `tests/test_prefs.c:209` | `static void test_invalid_urls_rejected(void **state)` |
| `test_parse_bad_magic` | function | `tests/test_prefs.c:140` | `static void test_parse_bad_magic(void **state)` |
| `test_parse_clamps_out_of_range` | function | `tests/test_prefs.c:187` | `static void test_parse_clamps_out_of_range(void **state)` |
| `test_parse_too_large` | function | `tests/test_prefs.c:156` | `static void test_parse_too_large(void **state)` |
| `test_parse_unknown_and_malformed_skipped` | function | `tests/test_prefs.c:165` | `static void test_parse_unknown_and_malformed_skipped(void **state)` |
| `test_roundtrip` | function | `tests/test_prefs.c:80` | `static void test_roundtrip(void **state)` |
| `test_suggest_priorities` | function | `tests/test_prefs.c:320` | `static void test_suggest_priorities(void **state)` |
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
| `main` | function | `tests/test_render_doc.c:873` | `int main(void)` |
| `test_author_color_gated_by_css` | function | `tests/test_render_doc.c:403` | `static void test_author_color_gated_by_css(void **state)` |
| `test_block_tag_total` | function | `tests/test_render_doc.c:824` | `static void test_block_tag_total(void **state)` |
| `test_build_null_out` | function | `tests/test_render_doc.c:44` | `static void test_build_null_out(void **state)` |
| `test_build_null_view_is_empty` | function | `tests/test_render_doc.c:51` | `static void test_build_null_view_is_empty(void **state)` |
| `test_caret_color_gated_on_input` | function | `tests/test_render_doc.c:537` | `static void test_caret_color_gated_on_input(void **state)` |
| `test_cont_item_carried_by_default` | function | `tests/test_render_doc.c:659` | `static void test_cont_item_carried_by_default(void **state)` |
| `test_container_carried_by_default` | function | `tests/test_render_doc.c:627` | `static void test_container_carried_by_default(void **state)` |
| `test_emphasis_propagates` | function | `tests/test_render_doc.c:94` | `static void test_emphasis_propagates(void **state)` |
| `test_flex_item_carried_by_default` | function | `tests/test_render_doc.c:728` | `static void test_flex_item_carried_by_default(void **state)` |
| `test_flex_wrap_align_row_gap_carried_by_default` | function | `tests/test_render_doc.c:776` | `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)` |
| `test_float_carried_by_default` | function | `tests/test_render_doc.c:692` | `static void test_float_carried_by_default(void **state)` |
| `test_free_null_and_double` | function | `tests/test_render_doc.c:393` | `static void test_free_null_and_double(void **state)` |
| `test_heading_level_of_link` | function | `tests/test_render_doc.c:808` | `static void test_heading_level_of_link(void **state)` |
| `test_heading_paragraph_link` | function | `tests/test_render_doc.c:64` | `static void test_heading_paragraph_link(void **state)` |
| `test_href_sanitised` | function | `tests/test_render_doc.c:353` | `static void test_href_sanitised(void **state)` |
| `test_image_data_url_allowed_no_top` | function | `tests/test_render_doc.c:302` | `static void test_image_data_url_allowed_no_top(void **state)` |
| `test_image_data_url_allowed_remote_top` | function | `tests/test_render_doc.c:284` | `static void test_image_data_url_allowed_remote_top(void **state)` |
| `test_image_data_url_disabled_by_default` | function | `tests/test_render_doc.c:315` | `static void test_image_data_url_disabled_by_default(void **state)` |
| `test_image_data_url_percent_encoded_allowed` | function | `tests/test_render_doc.c:331` | `static void test_image_data_url_percent_encoded_allowed(void **state)` |
| `test_image_label_total` | function | `tests/test_render_doc.c:380` | `static void test_image_label_total(void **state)` |
| `test_image_off_emits_notice_and_blocked` | function | `tests/test_render_doc.c:125` | `static void test_image_off_emits_notice_and_blocked(void **state)` |
| `test_image_on_allows_normal` | function | `tests/test_render_doc.c:188` | `static void test_image_on_allows_normal(void **state)` |
| `test_image_on_blocks_non_https` | function | `tests/test_render_doc.c:249` | `static void test_image_on_blocks_non_https(void **state)` |
| `test_image_on_blocks_tracker` | function | `tests/test_render_doc.c:236` | `static void test_image_on_blocks_tracker(void **state)` |
| `test_image_on_resolves_doc_relative_src` | function | `tests/test_render_doc.c:222` | `static void test_image_on_resolves_doc_relative_src(void **state)` |
| `test_image_on_resolves_relative_src` | function | `tests/test_render_doc.c:206` | `static void test_image_on_resolves_relative_src(void **state)` |

Next: [SYMBOLS_p16.md](SYMBOLS_p16.md)
