# Subsystem: tests (page 6 of 9)
Previous: [KB_tests_p5.md](KB_tests_p5.md)

## tests/test_js_native.c
- Doc: test_host_functions_look_native: assert_string_equal(_r.value, (expected))...
- Layer: testing
- Language: c
- Symbols:
  - `fixture` (struct, line 29)
  - `K` (class, line 116)
  - `K` (class, line 116)
  - `setup` (function, line 36) `static int setup(void **state)`
  - `teardown` (function, line 50) `static int teardown(void **state)`
  - `test_null_and_idempotent` (function, line 72) `static void test_null_and_idempotent(void **state)`
  - `test_host_functions_look_native` (function, line 80) `static void test_host_functions_look_native(void **state)`
  - `test_no_global_leaks_source` (function, line 96) `static void test_no_global_leaks_source(void **state)`
  - `EXPECT` (function, line 98) `EXPECT(f,
        "(function()`
  - `test_page_functions_keep_source` (function, line 110) `static void test_page_functions_keep_source(void **state)`
  - `EXPECT` (function, line 112) `EXPECT(f, "function page(a)`
  - `EXPECT` (function, line 113) `EXPECT(f, "(function()`
  - `EXPECT` (function, line 118) `EXPECT(f, "window.mine=function()`
  - `EXPECT` (function, line 120) `EXPECT(f, "'['+mine.name+']'+mine.toString()", "[]function()`
  - `test_names` (function, line 126) `static void test_names(void **state)`
  - `test_interface_tags` (function, line 133) `static void test_interface_tags(void **state)`
  - `test_singleton_interfaces` (function, line 153) `static void test_singleton_interfaces(void **state)`
  - `test_navigator_shape` (function, line 161) `static void test_navigator_shape(void **state)`
  - `EXPECT` (function, line 164) `EXPECT(f, "['userAgent','webdriver','languages','plugins','platform','hardwareConcurrency']"
    ...`
  - `test_firefox_plugins` (function, line 177) `static void test_firefox_plugins(void **state)`
  - `EXPECT` (function, line 180) `EXPECT(f, "Array.prototype.map.call(navigator.plugins,function(p)`
  - `EXPECT` (function, line 184) `EXPECT(f, "Array.prototype.map.call(navigator.mimeTypes,function(m)`
  - `test_css_supports` (function, line 190) `static void test_css_supports(void **state)`
  - `main` (function, line 199) `int main(void)`
  - `EXPECT` (macro, line 61) `#define EXPECT(f, src, expected)`
  - `NATIVE` (macro, line 70) `#define NATIVE(n)`
- Depends on: `include/dom.h`, `include/html_parse.h`, `include/js_dom.h`, `include/js_env.h`, `include/js_native.h`, `include/js_sandbox.h`

## tests/test_js_policy.c
- Doc: test_trusted_requires_both_signals: Hito 28: a host is TRUSTED (full author CSS + images, on top...
- Layer: testing
- Language: c
- Symbols:
  - `test_enabled_fail_closed_on_bad_mode` (function, line 31) `static void test_enabled_fail_closed_on_bad_mode(void **state)`
  - `test_mode_from_str` (function, line 36) `static void test_mode_from_str(void **state)`
  - `test_mode_str_roundtrip` (function, line 53) `static void test_mode_str_roundtrip(void **state)`
  - `test_trusted_requires_both_signals` (function, line 68) `static void test_trusted_requires_both_signals(void **state)`
  - `main` (function, line 89) `int main(void)`
- Depends on: `include/js_policy.h`

## tests/test_js_sandbox.c
- Doc: test_limits_default_heap_holds_real_bundles: A real site bundle (YouTube: ~1.2 MB of minified...
- Layer: testing
- Language: c
- Symbols:
  - `mod_host` (struct, line 460)
  - `fetches` (type_alias, line 459) `typedef struct mod_host { int fetches;`
  - `test_limits_default_heap_holds_real_bundles` (function, line 37) `static void test_limits_default_heap_holds_real_bundles(void **state)`
  - `test_validate_rejects_null` (function, line 55) `static void test_validate_rejects_null(void **state)`
  - `test_validate_rejects_empty` (function, line 60) `static void test_validate_rejects_empty(void **state)`
  - `test_validate_rejects_oversize` (function, line 65) `static void test_validate_rejects_oversize(void **state)`
  - `test_validate_accepts_within_cap` (function, line 72) `static void test_validate_accepts_within_cap(void **state)`
  - `test_context_new_and_free` (function, line 79) `static void test_context_new_and_free(void **state)`
  - `test_context_new_null_out` (function, line 87) `static void test_context_new_null_out(void **state)`
  - `test_eval_arithmetic` (function, line 94) `static void test_eval_arithmetic(void **state)`
  - `test_eval_string_concat` (function, line 108) `static void test_eval_string_concat(void **state)`
  - `test_eval_syntax_error` (function, line 120) `static void test_eval_syntax_error(void **state)`
  - `test_eval_runtime_exception` (function, line 129) `static void test_eval_runtime_exception(void **state)`
  - `test_no_io_globals` (function, line 143) `static void test_no_io_globals(void **state)`
  - `test_filesystem_access_is_reference_error` (function, line 156) `static void test_filesystem_access_is_reference_error(void **state)`
  - `test_infinite_loop_times_out` (function, line 169) `static void test_infinite_loop_times_out(void **state)`
  - `assert_int_equal` (function, line 175) `assert_int_equal(js_eval_once("while(true)`
  - `test_set_time_budget_applies` (function, line 182) `static void test_set_time_budget_applies(void **state)`
  - `assert_int_equal` (function, line 190) `assert_int_equal(js_eval(ctx, "while(true)`
  - `test_profiler_names_the_hot_function` (function, line 201) `static void test_profiler_names_the_hot_function(void **state)`
  - `test_throw_tracer_records_caught_exceptions` (function, line 235) `static void test_throw_tracer_records_caught_exceptions(void **state)`
  - `test_memory_limit_is_enforced` (function, line 266) `static void test_memory_limit_is_enforced(void **state)`
  - `test_stack_limit_follows_process_stack` (function, line 281) `static void test_stack_limit_follows_process_stack(void **state)`
  - `test_deep_recursion_runs_and_runaway_is_caught` (function, line 294) `static void test_deep_recursion_runs_and_runaway_is_caught(void **state)`
  - `test_result_free_on_zeroed` (function, line 312) `static void test_result_free_on_zeroed(void **state)`
  - `test_context_free_null_and_double` (function, line 321) `static void test_context_free_null_and_double(void **state)`
  - `test_eval_null_args` (function, line 329) `static void test_eval_null_args(void **state)`
  - `test_loc_parses_named_frame` (function, line 343) `static void test_loc_parses_named_frame(void **state)`
  - `test_loc_parses_bare_frame` (function, line 354) `static void test_loc_parses_bare_frame(void **state)`
  - `test_loc_file_may_contain_colons` (function, line 363) `static void test_loc_file_may_contain_colons(void **state)`
  - `test_loc_line_only_sets_col_zero` (function, line 374) `static void test_loc_line_only_sets_col_zero(void **state)`
  - `test_loc_truncates_to_cap` (function, line 383) `static void test_loc_truncates_to_cap(void **state)`
  - `test_loc_rejects_garbage_and_null` (function, line 391) `static void test_loc_rejects_garbage_and_null(void **state)`
  - `test_eval_named_captures_location` (function, line 406) `static void test_eval_named_captures_location(void **state)`
  - `test_eval_named_null_filename_defaults` (function, line 427) `static void test_eval_named_null_filename_defaults(void **state)`
  - `test_eval_thrown_primitive_has_no_location` (function, line 442) `static void test_eval_thrown_primitive_has_no_location(void **state)`
  - `mh_resolve` (function, line 462) `static int mh_resolve(void *host, const char *base, const char *spec, char *out, size_t outsz)`
  - `mh_fetch` (function, line 483) `static char *mh_fetch(void *host, const char *url, size_t *len)`
  - `test_module_imports_resolve_and_run` (function, line 507) `static void test_module_imports_resolve_and_run(void **state)`
  - `test_module_errors_are_reported` (function, line 528) `static void test_module_errors_are_reported(void **state)`
  - `test_dynamic_import_of_long_data_url` (function, line 582) `static void test_dynamic_import_of_long_data_url(void **state)`
  - `test_module_without_host_cannot_import` (function, line 608) `static void test_module_without_host_cannot_import(void **state)`
  - `self_fetch` (function, line 630) `static char *self_fetch(void *host, const char *url, size_t *len)`
  - `test_module_self_await_teardown` (function, line 640) `static void test_module_self_await_teardown(void **state)`
  - `realm_expect` (function, line 669) `static void realm_expect(js_context *ctx, const char *src, const char *want)`
  - `test_realms_isolate_and_clone` (function, line 677) `static void test_realms_isolate_and_clone(void **state)`
  - `test_realm_shares_time_budget` (function, line 708) `static void test_realm_shares_time_budget(void **state)`
  - `main` (function, line 722) `int main(void)`
- Depends on: `include/js_sandbox.h`

## tests/test_link_nav.c
- Doc: test_resolve_long_bundle_target: Modern bundle URLs exceed the old 4096 target cap (google's xjs...
- Layer: testing
- Language: c
- Symbols:
  - `test_null_out` (function, line 24) `static void test_null_out(void **state)`
  - `test_null_href_blocked` (function, line 29) `static void test_null_href_blocked(void **state)`
  - `test_fragment_is_same_document` (function, line 37) `static void test_fragment_is_same_document(void **state)`
  - `test_https_absolute` (function, line 49) `static void test_https_absolute(void **state)`
  - `test_https_relative` (function, line 57) `static void test_https_relative(void **state)`
  - `test_https_absolute_path_and_parent` (function, line 65) `static void test_https_absolute_path_and_parent(void **state)`
  - `test_https_blocks_downgrade_and_schemes` (function, line 76) `static void test_https_blocks_downgrade_and_schemes(void **state)`
  - `test_https_scheme_relative` (function, line 91) `static void test_https_scheme_relative(void **state)`
  - `test_resolve_long_bundle_target` (function, line 101) `static void test_resolve_long_bundle_target(void **state)`
  - `test_href_cleaning` (function, line 114) `static void test_href_cleaning(void **state)`
  - `test_file_relative` (function, line 125) `static void test_file_relative(void **state)`
  - `test_file_parent` (function, line 133) `static void test_file_parent(void **state)`
  - `test_file_absolute_path` (function, line 141) `static void test_file_absolute_path(void **state)`
  - `test_file_drops_fragment` (function, line 149) `static void test_file_drops_fragment(void **state)`
  - `test_file_base_to_https` (function, line 157) `static void test_file_base_to_https(void **state)`
  - `test_file_base_blocks_schemes_and_scheme_relative` (function, line 165) `static void test_file_base_blocks_schemes_and_scheme_relative(void **state)`
  - `test_no_base` (function, line 179) `static void test_no_base(void **state)`
  - `test_overflow_blocked` (function, line 195) `static void test_overflow_blocked(void **state)`
  - `test_block_reasons` (function, line 207) `static void test_block_reasons(void **state)`
  - `test_block_reason_text` (function, line 234) `static void test_block_reason_text(void **state)`
  - `test_fragment_capture` (function, line 244) `static void test_fragment_capture(void **state)`
  - `main` (function, line 273) `int main(void)`
- Depends on: `include/link_nav.h`

## tests/test_local_store.c
- Layer: testing
- Language: c
- Symbols:
  - `roundtrip_raw` (function, line 30) `static void roundtrip_raw(ls_aead aead)`
  - `test_roundtrip_aes` (function, line 48) `static void test_roundtrip_aes(void **s)`
  - `test_roundtrip_chacha` (function, line 49) `static void test_roundtrip_chacha(void **s)`
  - `test_empty_plaintext` (function, line 53) `static void test_empty_plaintext(void **s)`
  - `test_wrong_key` (function, line 67) `static void test_wrong_key(void **s)`
  - `tamper_at` (function, line 85) `static void tamper_at(size_t off)`
  - `test_tamper_ciphertext` (function, line 99) `static void test_tamper_ciphertext(void **s)`
  - `test_tamper_tag` (function, line 100) `static void test_tamper_tag(void **s)`
  - `test_tamper_nonce` (function, line 101) `static void test_tamper_nonce(void **s)`
  - `test_tamper_salt` (function, line 102) `static void test_tamper_salt(void **s)`
  - `test_tamper_aead_id` (function, line 103) `static void test_tamper_aead_id(void **s)`
  - `test_nondeterministic` (function, line 107) `static void test_nondeterministic(void **s)`
  - `test_passphrase_roundtrip` (function, line 121) `static void test_passphrase_roundtrip(void **s)`
  - `test_derive_key` (function, line 149) `static void test_derive_key(void **s)`
  - `test_format_errors` (function, line 166) `static void test_format_errors(void **s)`
  - `test_null_and_limits` (function, line 181) `static void test_null_and_limits(void **s)`
  - `main` (function, line 193) `int main(void)`
  - `local_store` (function, line 2) `* TDD suite for local_store (Hito 5 - Zero Knowledge: encrypted local state). * * RED state until src/local_store.c...`
- Depends on: `include/local_store.h`

## tests/test_mask_cache.c
- Layer: testing
- Language: c
- Symbols:
  - `key_of` (function, line 11) `static mkc_key key_of(int w, int h, double sigma)`
  - `test_empty_misses` (function, line 16) `static void test_empty_misses(void **state)`
  - `test_put_then_get_same_buffer` (function, line 28) `static void test_put_then_get_same_buffer(void **state)`
  - `test_any_field_differs_misses` (function, line 46) `static void test_any_field_differs_misses(void **state)`
  - `test_lru_eviction_by_bytes` (function, line 65) `static void test_lru_eviction_by_bytes(void **state)`
  - `test_entry_cap` (function, line 81) `static void test_entry_cap(void **state)`
  - `test_over_budget_and_invalid_fail_closed` (function, line 97) `static void test_over_budget_and_invalid_fail_closed(void **state)`
  - `test_replace_keeps_one_entry` (function, line 119) `static void test_replace_keeps_one_entry(void **state)`
  - `test_clear_and_null_safety` (function, line 133) `static void test_clear_and_null_safety(void **state)`
  - `main` (function, line 158) `int main(void)`
- Depends on: `include/mask_cache.h`

## tests/test_media_decoder.c
- Doc: test_pacer_paces_by_pts_delta: #include "media_decoder.h" /* First frame anchors the epoch and...
- Layer: testing
- Language: c
- Symbols:
  - `test_pacer_paces_by_pts_delta` (function, line 28) `static void test_pacer_paces_by_pts_delta(void **state)`
  - `test_pacer_backwards_pts_reanchors` (function, line 40) `static void test_pacer_backwards_pts_reanchors(void **state)`
  - `test_pacer_lag_reanchors` (function, line 52) `static void test_pacer_lag_reanchors(void **state)`
  - `test_pacer_hostile_pts_bounded` (function, line 69) `static void test_pacer_hostile_pts_bounded(void **state)`
  - `test_pacer_null_safe` (function, line 84) `static void test_pacer_null_safe(void **state)`
  - `main` (function, line 89) `int main(void)`
- Depends on: `include/media_decoder.h`

## tests/test_nav_token.c
- Doc: Suite for nav_token (spec/nav_token.md).
- Layer: testing
- Language: c
- Symbols:
  - `test_new_defaults` (function, line 11) `static void test_new_defaults(void **state)`
  - `test_null_fails_closed` (function, line 28) `static void test_null_fails_closed(void **state)`
  - `test_shared_reference` (function, line 39) `static void test_shared_reference(void **state)`
  - `test_route` (function, line 52) `static void test_route(void **state)`
  - `hammer` (function, line 75) `static void *hammer(void *arg)`
  - `test_concurrent_refcount` (function, line 87) `static void test_concurrent_refcount(void **state)`
  - `main` (function, line 98) `int main(void)`
- Depends on: `include/nav_token.h`

## tests/test_net_guard.c
- Doc: Suite for net_guard (spec/net_guard.md).
- Layer: testing
- Language: c
- Symbols:
  - `expect_private` (function, line 10) `static void expect_private(const char *const *ips, size_t n, int want)`
  - `test_ipv4_private_and_special_ranges` (function, line 16) `static void test_ipv4_private_and_special_ranges(void **state)`
  - `test_ipv4_public_edges` (function, line 29) `static void test_ipv4_public_edges(void **state)`
  - `test_ipv6_private_and_special_ranges` (function, line 41) `static void test_ipv6_private_and_special_ranges(void **state)`
  - `test_ipv4_embedded_in_ipv6_is_unwrapped` (function, line 56) `static void test_ipv4_embedded_in_ipv6_is_unwrapped(void **state)`
  - `test_unclassifiable_fails_closed` (function, line 71) `static void test_unclassifiable_fails_closed(void **state)`
  - `test_host_is_local` (function, line 93) `static void test_host_is_local(void **state)`
  - `test_host_is_ip` (function, line 112) `static void test_host_is_ip(void **state)`
  - `test_decide` (function, line 124) `static void test_decide(void **state)`
  - `main` (function, line 150) `int main(void)`
- Depends on: `include/net_guard.h`

## tests/test_net_realm.c
- Doc: test_classify_host_lookalikes: static void test_classify_host_i2p(void **state) { (void)state...
- Layer: testing
- Language: c
- Symbols:
  - `test_classify_host_onion` (function, line 22) `static void test_classify_host_onion(void **state)`
  - `test_classify_host_i2p` (function, line 30) `static void test_classify_host_i2p(void **state)`
  - `test_classify_host_clearnet` (function, line 37) `static void test_classify_host_clearnet(void **state)`
  - `test_classify_host_lookalikes` (function, line 44) `static void test_classify_host_lookalikes(void **state)`
  - `test_classify_host_edges` (function, line 54) `static void test_classify_host_edges(void **state)`
  - `test_classify_url` (function, line 67) `static void test_classify_url(void **state)`
  - `test_route_onion` (function, line 79) `static void test_route_onion(void **state)`
  - `test_route_i2p` (function, line 88) `static void test_route_i2p(void **state)`
  - `test_route_clearnet` (function, line 96) `static void test_route_clearnet(void **state)`
  - `test_route_null_blocked` (function, line 110) `static void test_route_null_blocked(void **state)`
  - `test_realm_allows_http` (function, line 118) `static void test_realm_allows_http(void **state)`
  - `test_names` (function, line 126) `static void test_names(void **state)`
  - `main` (function, line 140) `int main(void)`
- Depends on: `include/net_realm.h`

## tests/test_os_sandbox.c
- Doc: test_policy_denies_io_uring: io_uring is a seccomp-bypass primitive (its IORING_OP_* operations...
- Layer: testing
- Language: c
- Symbols:
  - `test_policy_allows_safe` (function, line 43) `static void test_policy_allows_safe(void **state)`
  - `test_policy_denies_dangerous` (function, line 51) `static void test_policy_denies_dangerous(void **state)`
  - `test_policy_denies_io_uring` (function, line 64) `static void test_policy_denies_io_uring(void **state)`
  - `test_policy_size` (function, line 71) `static void test_policy_size(void **state)`
  - `test_harden_kills_denied_syscall` (function, line 79) `static void test_harden_kills_denied_syscall(void **state)`
  - `test_harden_allows_permitted_syscall` (function, line 96) `static void test_harden_allows_permitted_syscall(void **state)`
  - `test_harden_errno_denies_with_eperm` (function, line 112) `static void test_harden_errno_denies_with_eperm(void **state)`
  - `test_harden_kills_io_uring_setup` (function, line 130) `static void test_harden_kills_io_uring_setup(void **state)`
  - `test_prot_allowed_wx` (function, line 151) `static void test_prot_allowed_wx(void **state)`
  - `test_harden_blocks_exec_mmap` (function, line 162) `static void test_harden_blocks_exec_mmap(void **state)`
  - `test_harden_blocks_exec_mprotect` (function, line 182) `static void test_harden_blocks_exec_mprotect(void **state)`
  - `test_no_dump_undumpable` (function, line 214) `static void test_no_dump_undumpable(void **state)`
  - `test_landlock_abi_present` (function, line 233) `static void test_landlock_abi_present(void **state)`
  - `test_landlock_deny_all` (function, line 239) `static void test_landlock_deny_all(void **state)`
  - `test_landlock_allow_read` (function, line 257) `static void test_landlock_allow_read(void **state)`
  - `net_ns_inode` (function, line 304) `static unsigned long net_ns_inode(void)`
  - `suite` (function, line 313) `* suite (it is best-effort defense in depth), and on a host that allows them the
 * isolation mus...`
  - `main` (function, line 335) `int main(void)`
  - `_GNU_SOURCE` (macro, line 14) `#define _GNU_SOURCE`
- Depends on: `include/os_sandbox.h`


Next: [KB_tests_p7.md](KB_tests_p7.md)
