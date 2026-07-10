# Polyglot Codebase Knowledge Graph

> Generated offline by **readmenator**. Supports C, C++, Python, Go, Rust, JS/TS, Java, C#, Shell, PHP, Dart, GDScript, Nim, ASM.
> No LLMs. No tokens. Pure static analysis. See more [here](https://github.com/grisuno/ReadMenator) 

**Total Files Parsed:** 147 | **Total Symbols Extracted:** 2696 | **Total Imports:** 820

## Structural Knowledge Map
> **Note:** The visual graph below has been intelligently pruned to the top 300 most relevant nodes to prevent rendering crashes. Full details of all 147 files are documented below.

```mermaid
graph TD
    classDef mod fill:#1e1e1e,stroke:#ff6666,stroke-width:2px,color:#fff;
    classDef cls fill:#2d2d2d,stroke:#4ec9b0,stroke-width:2px,color:#fff;
    classDef fn fill:#333,stroke:#dcdcaa,stroke-width:1px,color:#dcdcaa;
    classDef ext fill:#111,stroke:#666,stroke-dasharray: 5 5,color:#aaa;
    gui_browser_ui_c["browser_ui.c (c)"]
    class gui_browser_ui_c mod;
    gui_browser_ui_c_ui_menu_item["ui_menu_item"]
    class gui_browser_ui_c_ui_menu_item cls;
    gui_browser_ui_c --> gui_browser_ui_c_ui_menu_item
    gui_browser_ui_c_ui_input_state["ui_input_state"]
    class gui_browser_ui_c_ui_input_state cls;
    gui_browser_ui_c --> gui_browser_ui_c_ui_input_state
    gui_browser_ui_c_ui_image["ui_image"]
    class gui_browser_ui_c_ui_image cls;
    gui_browser_ui_c --> gui_browser_ui_c_ui_image
    gui_browser_ui_c_tab_ctx["tab_ctx"]
    class gui_browser_ui_c_tab_ctx cls;
    gui_browser_ui_c --> gui_browser_ui_c_tab_ctx
    gui_browser_ui_c_browser_window["browser_window"]
    class gui_browser_ui_c_browser_window cls;
    gui_browser_ui_c --> gui_browser_ui_c_browser_window
    src_local_store_c["local_store.c (c)"]
    class src_local_store_c mod;
    src_local_store_c_cipher_for["cipher_for"]
    class src_local_store_c_cipher_for fn;
    src_local_store_c --> src_local_store_c_cipher_for
    src_local_store_c_argon2id_derive["argon2id_derive"]
    class src_local_store_c_argon2id_derive fn;
    src_local_store_c --> src_local_store_c_argon2id_derive
    src_local_store_c_ls_derive_key["ls_derive_key"]
    class src_local_store_c_ls_derive_key fn;
    src_local_store_c --> src_local_store_c_ls_derive_key
    src_local_store_c_aead_encrypt["aead_encrypt"]
    class src_local_store_c_aead_encrypt fn;
    src_local_store_c --> src_local_store_c_aead_encrypt
    src_local_store_c_aead_decrypt["aead_decrypt"]
    class src_local_store_c_aead_decrypt fn;
    src_local_store_c --> src_local_store_c_aead_decrypt
    src_tab_c["tab.c (c)"]
    class src_tab_c mod;
    src_tab_c_child_state["child_state"]
    class src_tab_c_child_state cls;
    src_tab_c --> src_tab_c_child_state
    src_tab_c_tab["tab"]
    class src_tab_c_tab cls;
    src_tab_c --> src_tab_c_tab
    src_tab_c_write_full["write_full"]
    class src_tab_c_write_full fn;
    src_tab_c --> src_tab_c_write_full
    src_tab_c_read_full["read_full"]
    class src_tab_c_read_full fn;
    src_tab_c --> src_tab_c_read_full
    src_tab_c_child_reset_page["child_reset_page"]
    class src_tab_c_child_reset_page fn;
    src_tab_c --> src_tab_c_child_reset_page
    src_os_sandbox_c["os_sandbox.c (c)"]
    class src_os_sandbox_c mod;
    src_os_sandbox_c_os_policy_allows["os_policy_allows"]
    class src_os_sandbox_c_os_policy_allows fn;
    src_os_sandbox_c --> src_os_sandbox_c_os_policy_allows
    src_os_sandbox_c_os_policy_size["os_policy_size"]
    class src_os_sandbox_c_os_policy_size fn;
    src_os_sandbox_c --> src_os_sandbox_c_os_policy_size
    src_os_sandbox_c_os_prot_allowed["os_prot_allowed"]
    class src_os_sandbox_c_os_prot_allowed fn;
    src_os_sandbox_c --> src_os_sandbox_c_os_prot_allowed
    src_os_sandbox_c_os_no_dump["os_no_dump"]
    class src_os_sandbox_c_os_no_dump fn;
    src_os_sandbox_c --> src_os_sandbox_c_os_no_dump
    src_os_sandbox_c_excluded["excluded"]
    class src_os_sandbox_c_excluded fn;
    src_os_sandbox_c --> src_os_sandbox_c_excluded
    tests_test_os_sandbox_c["test_os_sandbox.c (c)"]
    class tests_test_os_sandbox_c mod;
    tests_test_os_sandbox_c_test_policy_allows_safe["test_policy_allows_safe"]
    class tests_test_os_sandbox_c_test_policy_allows_safe fn;
    tests_test_os_sandbox_c --> tests_test_os_sandbox_c_test_policy_allows_safe
    tests_test_os_sandbox_c_test_policy_denies_dangerous["test_policy_denies_dangerous"]
    class tests_test_os_sandbox_c_test_policy_denies_dangerous fn;
    tests_test_os_sandbox_c --> tests_test_os_sandbox_c_test_policy_denies_dangerous
    tests_test_os_sandbox_c_test_policy_denies_io_uring["test_policy_denies_io_uring"]
    class tests_test_os_sandbox_c_test_policy_denies_io_uring fn;
    tests_test_os_sandbox_c --> tests_test_os_sandbox_c_test_policy_denies_io_uring
    tests_test_os_sandbox_c_test_policy_size["test_policy_size"]
    class tests_test_os_sandbox_c_test_policy_size fn;
    tests_test_os_sandbox_c --> tests_test_os_sandbox_c_test_policy_size
    tests_test_os_sandbox_c_test_harden_kills_denied_syscall["test_harden_kills_denied_syscall"]
    class tests_test_os_sandbox_c_test_harden_kills_denied_syscall fn;
    tests_test_os_sandbox_c --> tests_test_os_sandbox_c_test_harden_kills_denied_syscall
    src_page_view_c["page_view.c (c)"]
    class src_page_view_c mod;
    src_page_view_c_pv_node_map["pv_node_map"]
    class src_page_view_c_pv_node_map cls;
    src_page_view_c --> src_page_view_c_pv_node_map
    src_page_view_c_pv_cont_info["pv_cont_info"]
    class src_page_view_c_pv_cont_info cls;
    src_page_view_c --> src_page_view_c_pv_cont_info
    src_page_view_c_pv_item_track["pv_item_track"]
    class src_page_view_c_pv_item_track cls;
    src_page_view_c --> src_page_view_c_pv_item_track
    src_page_view_c_pv_box_info["pv_box_info"]
    class src_page_view_c_pv_box_info cls;
    src_page_view_c --> src_page_view_c_pv_box_info
    src_page_view_c_pv_text_ext["pv_text_ext"]
    class src_page_view_c_pv_text_ext cls;
    src_page_view_c --> src_page_view_c_pv_text_ext
    tests_test_disk_store_c["test_disk_store.c (c)"]
    class tests_test_disk_store_c mod;
    tests_test_disk_store_c_fixture["fixture"]
    class tests_test_disk_store_c_fixture cls;
    tests_test_disk_store_c --> tests_test_disk_store_c_fixture
    tests_test_disk_store_c_setup["setup"]
    class tests_test_disk_store_c_setup fn;
    tests_test_disk_store_c --> tests_test_disk_store_c_setup
    tests_test_disk_store_c_teardown["teardown"]
    class tests_test_disk_store_c_teardown fn;
    tests_test_disk_store_c --> tests_test_disk_store_c_teardown
    tests_test_disk_store_c_count_dir_entries["count_dir_entries"]
    class tests_test_disk_store_c_count_dir_entries fn;
    tests_test_disk_store_c --> tests_test_disk_store_c_count_dir_entries
    tests_test_disk_store_c_test_roundtrip["test_roundtrip"]
    class tests_test_disk_store_c_test_roundtrip fn;
    tests_test_disk_store_c --> tests_test_disk_store_c_test_roundtrip
    tests_test_dom_debug_c["test_dom_debug.c (c)"]
    class tests_test_dom_debug_c mod;
    tests_test_dom_debug_c_caps_css_on["caps_css_on"]
    class tests_test_dom_debug_c_caps_css_on fn;
    tests_test_dom_debug_c --> tests_test_dom_debug_c_caps_css_on
    tests_test_dom_debug_c_build["build"]
    class tests_test_dom_debug_c_build fn;
    tests_test_dom_debug_c --> tests_test_dom_debug_c_build
    tests_test_dom_debug_c_test_null_doc_is_empty_header["test_null_doc_is_empty_header"]
    class tests_test_dom_debug_c_test_null_doc_is_empty_header fn;
    tests_test_dom_debug_c --> tests_test_dom_debug_c_test_null_doc_is_empty_header
    tests_test_dom_debug_c_test_heading_paragraph_link["test_heading_paragraph_link"]
    class tests_test_dom_debug_c_test_heading_paragraph_link fn;
    tests_test_dom_debug_c --> tests_test_dom_debug_c_test_heading_paragraph_link
    tests_test_dom_debug_c_test_grid_container_annotation["test_grid_container_annotation"]
    class tests_test_dom_debug_c_test_grid_container_annotation fn;
    tests_test_dom_debug_c --> tests_test_dom_debug_c_test_grid_container_annotation
    tests_test_page_view_c["test_page_view.c (c)"]
    class tests_test_page_view_c mod;
    tests_test_page_view_c_parse["parse"]
    class tests_test_page_view_c_parse fn;
    tests_test_page_view_c --> tests_test_page_view_c_parse
    tests_test_page_view_c_find_text["find_text"]
    class tests_test_page_view_c_find_text fn;
    tests_test_page_view_c --> tests_test_page_view_c_find_text
    tests_test_page_view_c_find_image["find_image"]
    class tests_test_page_view_c_find_image fn;
    tests_test_page_view_c --> tests_test_page_view_c_find_image
    tests_test_page_view_c_test_new_is_empty["test_new_is_empty"]
    class tests_test_page_view_c_test_new_is_empty fn;
    tests_test_page_view_c --> tests_test_page_view_c_test_new_is_empty
    tests_test_page_view_c_test_append_copies_fields["test_append_copies_fields"]
    class tests_test_page_view_c_test_append_copies_fields fn;
    tests_test_page_view_c --> tests_test_page_view_c_test_append_copies_fields
    tests_test_tab_c["test_tab.c (c)"]
    class tests_test_tab_c mod;
    tests_test_tab_c_fixture["fixture"]
    class tests_test_tab_c_fixture cls;
    tests_test_tab_c --> tests_test_tab_c_fixture
    tests_test_tab_c_setup_loaded["setup_loaded"]
    class tests_test_tab_c_setup_loaded fn;
    tests_test_tab_c --> tests_test_tab_c_setup_loaded
    tests_test_tab_c_teardown["teardown"]
    class tests_test_tab_c_teardown fn;
    tests_test_tab_c --> tests_test_tab_c_teardown
    tests_test_tab_c_expect_eval["expect_eval"]
    class tests_test_tab_c_expect_eval fn;
    tests_test_tab_c --> tests_test_tab_c_expect_eval
    tests_test_tab_c_test_open_close["test_open_close"]
    class tests_test_tab_c_test_open_close fn;
    tests_test_tab_c --> tests_test_tab_c_test_open_close
    tests_test_render_doc_c["test_render_doc.c (c)"]
    class tests_test_render_doc_c mod;
    tests_test_render_doc_c_caps_images_on["caps_images_on"]
    class tests_test_render_doc_c_caps_images_on fn;
    tests_test_render_doc_c --> tests_test_render_doc_c_caps_images_on
    tests_test_render_doc_c_first_kind["first_kind"]
    class tests_test_render_doc_c_first_kind fn;
    tests_test_render_doc_c --> tests_test_render_doc_c_first_kind
    tests_test_render_doc_c_test_build_null_out["test_build_null_out"]
    class tests_test_render_doc_c_test_build_null_out fn;
    tests_test_render_doc_c --> tests_test_render_doc_c_test_build_null_out
    tests_test_render_doc_c_test_build_null_view_is_empty["test_build_null_view_is_empty"]
    class tests_test_render_doc_c_test_build_null_view_is_empty fn;
    tests_test_render_doc_c --> tests_test_render_doc_c_test_build_null_view_is_empty
    tests_test_render_doc_c_test_heading_paragraph_link["test_heading_paragraph_link"]
    class tests_test_render_doc_c_test_heading_paragraph_link fn;
    tests_test_render_doc_c --> tests_test_render_doc_c_test_heading_paragraph_link
    src_freedom_c["freedom.c (c)"]
    class src_freedom_c mod;
    src_freedom_c_print_usage["print_usage"]
    class src_freedom_c_print_usage fn;
    src_freedom_c --> src_freedom_c_print_usage
    src_freedom_c_is_https_url["is_https_url"]
    class src_freedom_c_is_https_url fn;
    src_freedom_c --> src_freedom_c_is_https_url
    src_freedom_c_is_http_url["is_http_url"]
    class src_freedom_c_is_http_url fn;
    src_freedom_c --> src_freedom_c_is_http_url
    src_freedom_c_is_overlay_http["is_overlay_http"]
    class src_freedom_c_is_overlay_http fn;
    src_freedom_c --> src_freedom_c_is_overlay_http
    src_freedom_c_read_file["read_file"]
    class src_freedom_c_read_file fn;
    src_freedom_c --> src_freedom_c_read_file
    tests_test_js_env_c["test_js_env.c (c)"]
    class tests_test_js_env_c mod;
    tests_test_js_env_c_fixture["fixture"]
    class tests_test_js_env_c_fixture cls;
    tests_test_js_env_c --> tests_test_js_env_c_fixture
    tests_test_js_env_c_setup["setup"]
    class tests_test_js_env_c_setup fn;
    tests_test_js_env_c --> tests_test_js_env_c_setup
    tests_test_js_env_c_teardown["teardown"]
    class tests_test_js_env_c_teardown fn;
    tests_test_js_env_c --> tests_test_js_env_c_teardown
    tests_test_js_env_c_run["run"]
    class tests_test_js_env_c_run fn;
    tests_test_js_env_c --> tests_test_js_env_c_run
    tests_test_js_env_c_test_install_null_args["test_install_null_args"]
    class tests_test_js_env_c_test_install_null_args fn;
    tests_test_js_env_c --> tests_test_js_env_c_test_install_null_args
    tests_test_js_dom_c["test_js_dom.c (c)"]
    class tests_test_js_dom_c mod;
    tests_test_js_dom_c_fixture["fixture"]
    class tests_test_js_dom_c_fixture cls;
    tests_test_js_dom_c --> tests_test_js_dom_c_fixture
    tests_test_js_dom_c_setup["setup"]
    class tests_test_js_dom_c_setup fn;
    tests_test_js_dom_c --> tests_test_js_dom_c_setup
    tests_test_js_dom_c_teardown["teardown"]
    class tests_test_js_dom_c_teardown fn;
    tests_test_js_dom_c --> tests_test_js_dom_c_teardown
    tests_test_js_dom_c_run["run"]
    class tests_test_js_dom_c_run fn;
    tests_test_js_dom_c --> tests_test_js_dom_c_run
    tests_test_js_dom_c_test_install_null_args["test_install_null_args"]
    class tests_test_js_dom_c_test_install_null_args fn;
    tests_test_js_dom_c --> tests_test_js_dom_c_test_install_null_args
    gui_ui_render_c["ui_render.c (c)"]
    class gui_ui_render_c mod;
    gui_ui_render_c_ui_window["ui_window"]
    class gui_ui_render_c_ui_window cls;
    gui_ui_render_c --> gui_ui_render_c_ui_window
    gui_ui_render_c_sanitize_utf8_inplace["sanitize_utf8_inplace"]
    class gui_ui_render_c_sanitize_utf8_inplace fn;
    gui_ui_render_c --> gui_ui_render_c_sanitize_utf8_inplace
    gui_ui_render_c_button_rects["button_rects"]
    class gui_ui_render_c_button_rects fn;
    gui_ui_render_c --> gui_ui_render_c_button_rects
    gui_ui_render_c_buffer_release["buffer_release"]
    class gui_ui_render_c_buffer_release fn;
    gui_ui_render_c --> gui_ui_render_c_buffer_release
    gui_ui_render_c_destroy_buffer["destroy_buffer"]
    class gui_ui_render_c_destroy_buffer fn;
    gui_ui_render_c --> gui_ui_render_c_destroy_buffer
    tests_test_freedom_c["test_freedom.c (c)"]
    class tests_test_freedom_c mod;
    tests_test_freedom_c_run_freedom["run_freedom"]
    class tests_test_freedom_c_run_freedom fn;
    tests_test_freedom_c --> tests_test_freedom_c_run_freedom
    tests_test_freedom_c_run_freedom_raw["run_freedom_raw"]
    class tests_test_freedom_c_run_freedom_raw fn;
    tests_test_freedom_c --> tests_test_freedom_c_run_freedom_raw
    tests_test_freedom_c_is_pdf_file["is_pdf_file"]
    class tests_test_freedom_c_is_pdf_file fn;
    tests_test_freedom_c --> tests_test_freedom_c_is_pdf_file
    tests_test_freedom_c_is_png_file["is_png_file"]
    class tests_test_freedom_c_is_png_file fn;
    tests_test_freedom_c --> tests_test_freedom_c_is_png_file
    tests_test_freedom_c_cleanup_files["cleanup_files"]
    class tests_test_freedom_c_cleanup_files fn;
    tests_test_freedom_c --> tests_test_freedom_c_cleanup_files
    src_disk_store_c["disk_store.c (c)"]
    class src_disk_store_c mod;
    src_disk_store_c_write_full["write_full"]
    class src_disk_store_c_write_full fn;
    src_disk_store_c --> src_disk_store_c_write_full
    src_disk_store_c_read_full["read_full"]
    class src_disk_store_c_read_full fn;
    src_disk_store_c --> src_disk_store_c_read_full
    src_disk_store_c_fsync_dir["fsync_dir"]
    class src_disk_store_c_fsync_dir fn;
    src_disk_store_c --> src_disk_store_c_fsync_dir
    src_disk_store_c_map_ls["map_ls"]
    class src_disk_store_c_map_ls fn;
    src_disk_store_c --> src_disk_store_c_map_ls
    src_disk_store_c_ds_write["ds_write"]
    class src_disk_store_c_ds_write fn;
    src_disk_store_c --> src_disk_store_c_ds_write
    tests_test_css_c["test_css.c (c)"]
    class tests_test_css_c mod;
    tests_test_css_c_test_inline_text_align["test_inline_text_align"]
    class tests_test_css_c_test_inline_text_align fn;
    tests_test_css_c --> tests_test_css_c_test_inline_text_align
    tests_test_css_c_test_inline_font_size["test_inline_font_size"]
    class tests_test_css_c_test_inline_font_size fn;
    tests_test_css_c --> tests_test_css_c_test_inline_font_size
    tests_test_css_c_test_inline_line_height["test_inline_line_height"]
    class tests_test_css_c_test_inline_line_height fn;
    tests_test_css_c --> tests_test_css_c_test_inline_line_height
    tests_test_css_c_test_inline_font_weight_style["test_inline_font_weight_style"]
    class tests_test_css_c_test_inline_font_weight_style fn;
    tests_test_css_c --> tests_test_css_c_test_inline_font_weight_style
    tests_test_css_c_test_inline_text_decoration["test_inline_text_decoration"]
    class tests_test_css_c_test_inline_text_decoration fn;
    tests_test_css_c --> tests_test_css_c_test_inline_text_decoration
    src_dom_c["dom.c (c)"]
    class src_dom_c mod;
    src_dom_c_sm_entry["sm_entry"]
    class src_dom_c_sm_entry cls;
    src_dom_c --> src_dom_c_sm_entry
    src_dom_c_strmap["strmap"]
    class src_dom_c_strmap cls;
    src_dom_c --> src_dom_c_strmap
    src_dom_c_pm_entry["pm_entry"]
    class src_dom_c_pm_entry cls;
    src_dom_c --> src_dom_c_pm_entry
    src_dom_c_ptrmap["ptrmap"]
    class src_dom_c_ptrmap cls;
    src_dom_c --> src_dom_c_ptrmap
    src_dom_c_dom_index["dom_index"]
    class src_dom_c_dom_index cls;
    src_dom_c --> src_dom_c_dom_index
    src_secure_fetch_c["secure_fetch.c (c)"]
    class src_secure_fetch_c mod;
    src_secure_fetch_c_body_sink["body_sink"]
    class src_secure_fetch_c_body_sink cls;
    src_secure_fetch_c --> src_secure_fetch_c_body_sink
    src_secure_fetch_c_tls_capture["tls_capture"]
    class src_secure_fetch_c_tls_capture cls;
    src_secure_fetch_c --> src_secure_fetch_c_tls_capture
    src_secure_fetch_c_fetch_ctx["fetch_ctx"]
    class src_secure_fetch_c_fetch_ctx cls;
    src_secure_fetch_c --> src_secure_fetch_c_fetch_ctx
    src_secure_fetch_c_ci_starts_with["ci_starts_with"]
    class src_secure_fetch_c_ci_starts_with fn;
    src_secure_fetch_c --> src_secure_fetch_c_ci_starts_with
    src_secure_fetch_c_ci_index["ci_index"]
    class src_secure_fetch_c_ci_index fn;
    src_secure_fetch_c --> src_secure_fetch_c_ci_index
    tests_test_dom_c["test_dom.c (c)"]
    class tests_test_dom_c mod;
    tests_test_dom_c_setup_doc["setup_doc"]
    class tests_test_dom_c_setup_doc fn;
    tests_test_dom_c --> tests_test_dom_c_setup_doc
    tests_test_dom_c_teardown_doc["teardown_doc"]
    class tests_test_dom_c_teardown_doc fn;
    tests_test_dom_c --> tests_test_dom_c_teardown_doc
    tests_test_dom_c_test_build_null_args["test_build_null_args"]
    class tests_test_dom_c_test_build_null_args fn;
    tests_test_dom_c --> tests_test_dom_c_test_build_null_args
    tests_test_dom_c_test_free_null_and_double["test_free_null_and_double"]
    class tests_test_dom_c_test_free_null_and_double fn;
    tests_test_dom_c --> tests_test_dom_c_test_free_null_and_double
    tests_test_dom_c_test_node_count["test_node_count"]
    class tests_test_dom_c_test_node_count fn;
    tests_test_dom_c --> tests_test_dom_c_test_node_count
    tests_test_html_parse_c["test_html_parse.c (c)"]
    class tests_test_html_parse_c mod;
    tests_test_html_parse_c_test_config_default_is_secure["test_config_default_is_secure"]
    class tests_test_html_parse_c_test_config_default_is_secure fn;
    tests_test_html_parse_c --> tests_test_html_parse_c_test_config_default_is_secure
    tests_test_html_parse_c_test_validate_rejects_null["test_validate_rejects_null"]
    class tests_test_html_parse_c_test_validate_rejects_null fn;
    tests_test_html_parse_c --> tests_test_html_parse_c_test_validate_rejects_null
    tests_test_html_parse_c_test_validate_rejects_empty["test_validate_rejects_empty"]
    class tests_test_html_parse_c_test_validate_rejects_empty fn;
    tests_test_html_parse_c --> tests_test_html_parse_c_test_validate_rejects_empty
    tests_test_html_parse_c_test_validate_rejects_oversize["test_validate_rejects_oversize"]
    class tests_test_html_parse_c_test_validate_rejects_oversize fn;
    tests_test_html_parse_c --> tests_test_html_parse_c_test_validate_rejects_oversize
    tests_test_html_parse_c_test_validate_accepts_within_cap["test_validate_accepts_within_cap"]
    class tests_test_html_parse_c_test_validate_accepts_within_cap fn;
    tests_test_html_parse_c --> tests_test_html_parse_c_test_validate_accepts_within_cap
    src_text_shape_c["text_shape.c (c)"]
    class src_text_shape_c mod;
    src_text_shape_c_tsh_entry["tsh_entry"]
    class src_text_shape_c_tsh_entry cls;
    src_text_shape_c --> src_text_shape_c_tsh_entry
    src_text_shape_c_generic_name["generic_name"]
    class src_text_shape_c_generic_name fn;
    src_text_shape_c --> src_text_shape_c_generic_name
    src_text_shape_c_backend_init["backend_init"]
    class src_text_shape_c_backend_init fn;
    src_text_shape_c --> src_text_shape_c_backend_init
    src_text_shape_c_read_font_file["read_font_file"]
    class src_text_shape_c_read_font_file fn;
    src_text_shape_c --> src_text_shape_c_read_font_file
    src_text_shape_c_load_entry["load_entry"]
    class src_text_shape_c_load_entry fn;
    src_text_shape_c --> src_text_shape_c_load_entry
    tests_test_text_shape_c["test_text_shape.c (c)"]
    class tests_test_text_shape_c mod;
    tests_test_text_shape_c_test_null_and_bad_inputs["test_null_and_bad_inputs"]
    class tests_test_text_shape_c_test_null_and_bad_inputs fn;
    tests_test_text_shape_c --> tests_test_text_shape_c_test_null_and_bad_inputs
    tests_test_text_shape_c_test_empty_slice_is_ok["test_empty_slice_is_ok"]
    class tests_test_text_shape_c_test_empty_slice_is_ok fn;
    tests_test_text_shape_c --> tests_test_text_shape_c_test_empty_slice_is_ok
    tests_test_text_shape_c_test_shape_ascii["test_shape_ascii"]
    class tests_test_text_shape_c_test_shape_ascii fn;
    tests_test_text_shape_c --> tests_test_text_shape_c_test_shape_ascii
    tests_test_text_shape_c_test_determinism["test_determinism"]
    class tests_test_text_shape_c_test_determinism fn;
    tests_test_text_shape_c --> tests_test_text_shape_c_test_determinism
    tests_test_text_shape_c_test_measure_matches_shape["test_measure_matches_shape"]
    class tests_test_text_shape_c_test_measure_matches_shape fn;
    tests_test_text_shape_c --> tests_test_text_shape_c_test_measure_matches_shape
    src_renderer_c["renderer.c (c)"]
    class src_renderer_c mod;
    src_renderer_c_write_full["write_full"]
    class src_renderer_c_write_full fn;
    src_renderer_c --> src_renderer_c_write_full
    src_renderer_c_read_full["read_full"]
    class src_renderer_c_read_full fn;
    src_renderer_c --> src_renderer_c_read_full
    src_renderer_c_child_render["child_render"]
    class src_renderer_c_child_render fn;
    src_renderer_c --> src_renderer_c_child_render
    src_renderer_c_read_field["read_field"]
    class src_renderer_c_read_field fn;
    src_renderer_c --> src_renderer_c_read_field
    src_renderer_c_rd_render_html["rd_render_html"]
    class src_renderer_c_rd_render_html fn;
    src_renderer_c --> src_renderer_c_rd_render_html
    src_js_dom_c["js_dom.c (c)"]
    class src_js_dom_c mod;
    src_js_dom_c_jd_method["jd_method"]
    class src_js_dom_c_jd_method cls;
    src_js_dom_c --> src_js_dom_c_jd_method
    src_js_dom_c_jd_click_state["jd_click_state"]
    class src_js_dom_c_jd_click_state cls;
    src_js_dom_c --> src_js_dom_c_jd_click_state
    src_js_dom_c_jd_opaque_get["jd_opaque_get"]
    class src_js_dom_c_jd_opaque_get fn;
    src_js_dom_c --> src_js_dom_c_jd_opaque_get
    src_js_dom_c_jd_idx["jd_idx"]
    class src_js_dom_c_jd_idx fn;
    src_js_dom_c --> src_js_dom_c_jd_idx
    src_js_dom_c_jd_handle["jd_handle"]
    class src_js_dom_c_jd_handle fn;
    src_js_dom_c --> src_js_dom_c_jd_handle
    tests_test_secure_fetch_c["test_secure_fetch.c (c)"]
    class tests_test_secure_fetch_c mod;
    tests_test_secure_fetch_c_test_user_agent_default_when_unset["test_user_agent_default_when_unset"]
    class tests_test_secure_fetch_c_test_user_agent_default_when_unset fn;
    tests_test_secure_fetch_c --> tests_test_secure_fetch_c_test_user_agent_default_when_unset
    tests_test_secure_fetch_c_test_user_agent_uses_override["test_user_agent_uses_override"]
    class tests_test_secure_fetch_c_test_user_agent_uses_override fn;
    tests_test_secure_fetch_c --> tests_test_secure_fetch_c_test_user_agent_uses_override
    tests_test_secure_fetch_c_test_url_rejects_null["test_url_rejects_null"]
    class tests_test_secure_fetch_c_test_url_rejects_null fn;
    tests_test_secure_fetch_c --> tests_test_secure_fetch_c_test_url_rejects_null
    tests_test_secure_fetch_c_test_url_rejects_plain_http["test_url_rejects_plain_http"]
    class tests_test_secure_fetch_c_test_url_rejects_plain_http fn;
    tests_test_secure_fetch_c --> tests_test_secure_fetch_c_test_url_rejects_plain_http
    tests_test_secure_fetch_c_test_url_rejects_dangerous_schemes["test_url_rejects_dangerous_schemes"]
    class tests_test_secure_fetch_c_test_url_rejects_dangerous_schemes fn;
    tests_test_secure_fetch_c --> tests_test_secure_fetch_c_test_url_rejects_dangerous_schemes
    tests_test_url_c["test_url.c (c)"]
    class tests_test_url_c mod;
    tests_test_url_c_test_is_https["test_is_https"]
    class tests_test_url_c_test_is_https fn;
    tests_test_url_c --> tests_test_url_c_test_is_https
    tests_test_url_c_test_validate_https["test_validate_https"]
    class tests_test_url_c_test_validate_https fn;
    tests_test_url_c --> tests_test_url_c_test_validate_https
    tests_test_url_c_test_validate_long_bundle_url["test_validate_long_bundle_url"]
    class tests_test_url_c_test_validate_long_bundle_url fn;
    tests_test_url_c --> tests_test_url_c_test_validate_long_bundle_url
    tests_test_url_c_test_has_scheme["test_has_scheme"]
    class tests_test_url_c_test_has_scheme fn;
    tests_test_url_c --> tests_test_url_c_test_has_scheme
    tests_test_url_c_test_authority_len["test_authority_len"]
    class tests_test_url_c_test_authority_len fn;
    tests_test_url_c --> tests_test_url_c_test_authority_len
    tests_test_box_tree_c["test_box_tree.c (c)"]
    class tests_test_box_tree_c mod;
    tests_test_box_tree_c_assert_rect["assert_rect"]
    class tests_test_box_tree_c_assert_rect fn;
    tests_test_box_tree_c --> tests_test_box_tree_c_assert_rect
    tests_test_box_tree_c_test_null_root["test_null_root"]
    class tests_test_box_tree_c_test_null_root fn;
    tests_test_box_tree_c --> tests_test_box_tree_c_test_null_root
    tests_test_box_tree_c_test_leaf["test_leaf"]
    class tests_test_box_tree_c_test_leaf fn;
    tests_test_box_tree_c --> tests_test_box_tree_c_test_leaf
    tests_test_box_tree_c_test_leaf_with_padding["test_leaf_with_padding"]
    class tests_test_box_tree_c_test_leaf_with_padding fn;
    tests_test_box_tree_c --> tests_test_box_tree_c_test_leaf_with_padding
    tests_test_box_tree_c_test_block_stacking_with_collapse["test_block_stacking_with_collapse"]
    class tests_test_box_tree_c_test_block_stacking_with_collapse fn;
    tests_test_box_tree_c --> tests_test_box_tree_c_test_block_stacking_with_collapse
    src_js_env_c["js_env.c (c)"]
    class src_js_env_c mod;
    src_js_env_c_wall_clock_ms["wall_clock_ms"]
    class src_js_env_c_wall_clock_ms fn;
    src_js_env_c --> src_js_env_c_wall_clock_ms
    src_js_env_c_monotonic_ms["monotonic_ms"]
    class src_js_env_c_monotonic_ms fn;
    src_js_env_c --> src_js_env_c_monotonic_ms
    src_js_env_c_m_date_now["m_date_now"]
    class src_js_env_c_m_date_now fn;
    src_js_env_c --> src_js_env_c_m_date_now
    src_js_env_c_m_perf_now["m_perf_now"]
    class src_js_env_c_m_perf_now fn;
    src_js_env_c --> src_js_env_c_m_perf_now
    src_js_env_c_m_empty_array["m_empty_array"]
    class src_js_env_c_m_empty_array fn;
    src_js_env_c --> src_js_env_c_m_empty_array
    src_dom_debug_c["dom_debug.c (c)"]
    class src_dom_debug_c mod;
    src_dom_debug_c_dd_cursor["dd_cursor"]
    class src_dom_debug_c_dd_cursor cls;
    src_dom_debug_c --> src_dom_debug_c_dd_cursor
    src_dom_debug_c_dd_putc["dd_putc"]
    class src_dom_debug_c_dd_putc fn;
    src_dom_debug_c --> src_dom_debug_c_dd_putc
    src_dom_debug_c_dd_emit["dd_emit"]
    class src_dom_debug_c_dd_emit fn;
    src_dom_debug_c --> src_dom_debug_c_dd_emit
    src_dom_debug_c_dd_puts["dd_puts"]
    class src_dom_debug_c_dd_puts fn;
    src_dom_debug_c --> src_dom_debug_c_dd_puts
    src_dom_debug_c_dd_printf["dd_printf"]
    class src_dom_debug_c_dd_printf fn;
    src_dom_debug_c --> src_dom_debug_c_dd_printf
    tests_test_local_store_c["test_local_store.c (c)"]
    class tests_test_local_store_c mod;
    tests_test_local_store_c_roundtrip_raw["roundtrip_raw"]
    class tests_test_local_store_c_roundtrip_raw fn;
    tests_test_local_store_c --> tests_test_local_store_c_roundtrip_raw
    tests_test_local_store_c_test_roundtrip_aes["test_roundtrip_aes"]
    class tests_test_local_store_c_test_roundtrip_aes fn;
    tests_test_local_store_c --> tests_test_local_store_c_test_roundtrip_aes
    tests_test_local_store_c_test_roundtrip_chacha["test_roundtrip_chacha"]
    class tests_test_local_store_c_test_roundtrip_chacha fn;
    tests_test_local_store_c --> tests_test_local_store_c_test_roundtrip_chacha
    tests_test_local_store_c_test_empty_plaintext["test_empty_plaintext"]
    class tests_test_local_store_c_test_empty_plaintext fn;
    tests_test_local_store_c --> tests_test_local_store_c_test_empty_plaintext
    tests_test_local_store_c_test_wrong_key["test_wrong_key"]
    class tests_test_local_store_c_test_wrong_key fn;
    tests_test_local_store_c --> tests_test_local_store_c_test_wrong_key
    tests_test_browser_c["test_browser.c (c)"]
    class tests_test_browser_c mod;
    tests_test_browser_c_test_init["test_init"]
    class tests_test_browser_c_test_init fn;
    tests_test_browser_c --> tests_test_browser_c_test_init
    tests_test_browser_c_test_navigate_history["test_navigate_history"]
    class tests_test_browser_c_test_navigate_history fn;
    tests_test_browser_c --> tests_test_browser_c_test_navigate_history
    tests_test_browser_c_test_navigate_from_middle_discards_future["test_navigate_from_middle_discards_future"]
    class tests_test_browser_c_test_navigate_from_middle_discards_future fn;
    tests_test_browser_c --> tests_test_browser_c_test_navigate_from_middle_discards_future
    tests_test_browser_c_test_back_forward_bounds["test_back_forward_bounds"]
    class tests_test_browser_c_test_back_forward_bounds fn;
    tests_test_browser_c --> tests_test_browser_c_test_back_forward_bounds
    tests_test_browser_c_test_rejects_invalid_url["test_rejects_invalid_url"]
    class tests_test_browser_c_test_rejects_invalid_url fn;
    tests_test_browser_c --> tests_test_browser_c_test_rejects_invalid_url
    tests_test_freebug_c["test_freebug.c (c)"]
    class tests_test_freebug_c mod;
    tests_test_freebug_c_test_push_and_read["test_push_and_read"]
    class tests_test_freebug_c_test_push_and_read fn;
    tests_test_freebug_c --> tests_test_freebug_c_test_push_and_read
    tests_test_freebug_c_test_empty_and_null_text["test_empty_and_null_text"]
    class tests_test_freebug_c_test_empty_and_null_text fn;
    tests_test_freebug_c --> tests_test_freebug_c_test_empty_and_null_text
    tests_test_freebug_c_test_count_cap_fails_closed["test_count_cap_fails_closed"]
    class tests_test_freebug_c_test_count_cap_fails_closed fn;
    tests_test_freebug_c --> tests_test_freebug_c_test_count_cap_fails_closed
    tests_test_freebug_c_test_entry_truncated_not_dropped["test_entry_truncated_not_dropped"]
    class tests_test_freebug_c_test_entry_truncated_not_dropped fn;
    tests_test_freebug_c --> tests_test_freebug_c_test_entry_truncated_not_dropped
    tests_test_freebug_c_test_total_bytes_cap_fails_closed["test_total_bytes_cap_fails_closed"]
    class tests_test_freebug_c_test_total_bytes_cap_fails_closed fn;
    tests_test_freebug_c --> tests_test_freebug_c_test_total_bytes_cap_fails_closed
    tests_test_renderer_c["test_renderer.c (c)"]
    class tests_test_renderer_c mod;
    tests_test_renderer_c_test_render_basic["test_render_basic"]
    class tests_test_renderer_c_test_render_basic fn;
    tests_test_renderer_c --> tests_test_renderer_c_test_render_basic
    tests_test_renderer_c_test_render_strips_script["test_render_strips_script"]
    class tests_test_renderer_c_test_render_strips_script fn;
    tests_test_renderer_c --> tests_test_renderer_c_test_render_strips_script
    tests_test_renderer_c_test_render_null_args["test_render_null_args"]
    class tests_test_renderer_c_test_render_null_args fn;
    tests_test_renderer_c --> tests_test_renderer_c_test_render_null_args
    tests_test_renderer_c_test_render_too_large["test_render_too_large"]
    class tests_test_renderer_c_test_render_too_large fn;
    tests_test_renderer_c --> tests_test_renderer_c_test_render_too_large
    tests_test_renderer_c_test_render_binary_does_not_crash_parent["test_render_binary_does_not_crash_parent"]
    class tests_test_renderer_c_test_render_binary_does_not_crash_parent fn;
    tests_test_renderer_c --> tests_test_renderer_c_test_render_binary_does_not_crash_parent
    fuzz_fuzz_dom_debug_c["fuzz_dom_debug.c (c)"]
    class fuzz_fuzz_dom_debug_c mod;
    fuzz_fuzz_dom_debug_c_pass["pass"]
    class fuzz_fuzz_dom_debug_c_pass fn;
    fuzz_fuzz_dom_debug_c --> fuzz_fuzz_dom_debug_c_pass
    tests_test_js_sandbox_c["test_js_sandbox.c (c)"]
    class tests_test_js_sandbox_c mod;
    tests_test_js_sandbox_c_test_validate_rejects_null["test_validate_rejects_null"]
    class tests_test_js_sandbox_c_test_validate_rejects_null fn;
    tests_test_js_sandbox_c --> tests_test_js_sandbox_c_test_validate_rejects_null
    tests_test_js_sandbox_c_test_validate_rejects_empty["test_validate_rejects_empty"]
    class tests_test_js_sandbox_c_test_validate_rejects_empty fn;
    tests_test_js_sandbox_c --> tests_test_js_sandbox_c_test_validate_rejects_empty
    tests_test_js_sandbox_c_test_validate_rejects_oversize["test_validate_rejects_oversize"]
    class tests_test_js_sandbox_c_test_validate_rejects_oversize fn;
    tests_test_js_sandbox_c --> tests_test_js_sandbox_c_test_validate_rejects_oversize
    tests_test_js_sandbox_c_test_validate_accepts_within_cap["test_validate_accepts_within_cap"]
    class tests_test_js_sandbox_c_test_validate_accepts_within_cap fn;
    tests_test_js_sandbox_c --> tests_test_js_sandbox_c_test_validate_accepts_within_cap
    tests_test_js_sandbox_c_test_context_new_and_free["test_context_new_and_free"]
    class tests_test_js_sandbox_c_test_context_new_and_free fn;
    tests_test_js_sandbox_c --> tests_test_js_sandbox_c_test_context_new_and_free
    tests_test_pdf_export_c["test_pdf_export.c (c)"]
    class tests_test_pdf_export_c mod;
    tests_test_pdf_export_c_pagination["pagination"]
    class tests_test_pdf_export_c_pagination fn;
    tests_test_pdf_export_c --> tests_test_pdf_export_c_pagination
    tests_test_pdf_export_c_test_basename_maps_spaces_and_reserved["test_basename_maps_spaces_and_reserved"]
    class tests_test_pdf_export_c_test_basename_maps_spaces_and_reserved fn;
    tests_test_pdf_export_c --> tests_test_pdf_export_c_test_basename_maps_spaces_and_reserved
    tests_test_pdf_export_c_test_basename_rejects_path_separators["test_basename_rejects_path_separators"]
    class tests_test_pdf_export_c_test_basename_rejects_path_separators fn;
    tests_test_pdf_export_c --> tests_test_pdf_export_c_test_basename_rejects_path_separators
    tests_test_pdf_export_c_test_basename_neutralizes_traversal["test_basename_neutralizes_traversal"]
    class tests_test_pdf_export_c_test_basename_neutralizes_traversal fn;
    tests_test_pdf_export_c --> tests_test_pdf_export_c_test_basename_neutralizes_traversal
    tests_test_pdf_export_c_test_basename_dotdot_only_falls_back["test_basename_dotdot_only_falls_back"]
    class tests_test_pdf_export_c_test_basename_dotdot_only_falls_back fn;
    tests_test_pdf_export_c --> tests_test_pdf_export_c_test_basename_dotdot_only_falls_back
    tests_test_image_decode_c["test_image_decode.c (c)"]
    class tests_test_image_decode_c mod;
    tests_test_image_decode_c_px["px"]
    class tests_test_image_decode_c_px fn;
    tests_test_image_decode_c --> tests_test_image_decode_c_px
    tests_test_image_decode_c_test_sniff_png["test_sniff_png"]
    class tests_test_image_decode_c_test_sniff_png fn;
    tests_test_image_decode_c --> tests_test_image_decode_c_test_sniff_png
    tests_test_image_decode_c_test_sniff_unsupported["test_sniff_unsupported"]
    class tests_test_image_decode_c_test_sniff_unsupported fn;
    tests_test_image_decode_c --> tests_test_image_decode_c_test_sniff_unsupported
    tests_test_image_decode_c_test_dimensions_from_ihdr["test_dimensions_from_ihdr"]
    class tests_test_image_decode_c_test_dimensions_from_ihdr fn;
    tests_test_image_decode_c --> tests_test_image_decode_c_test_dimensions_from_ihdr
    tests_test_image_decode_c_test_dimensions_truncated["test_dimensions_truncated"]
    class tests_test_image_decode_c_test_dimensions_truncated fn;
    tests_test_image_decode_c --> tests_test_image_decode_c_test_dimensions_truncated
    tests_test_flex_layout_c["test_flex_layout.c (c)"]
    class tests_test_flex_layout_c mod;
    tests_test_flex_layout_c_assert_item["assert_item"]
    class tests_test_flex_layout_c_assert_item fn;
    tests_test_flex_layout_c --> tests_test_flex_layout_c_assert_item
    tests_test_flex_layout_c_test_grow_equal["test_grow_equal"]
    class tests_test_flex_layout_c_test_grow_equal fn;
    tests_test_flex_layout_c --> tests_test_flex_layout_c_test_grow_equal
    tests_test_flex_layout_c_test_grow_weighted["test_grow_weighted"]
    class tests_test_flex_layout_c_test_grow_weighted fn;
    tests_test_flex_layout_c --> tests_test_flex_layout_c_test_grow_weighted
    tests_test_flex_layout_c_test_shrink_equal["test_shrink_equal"]
    class tests_test_flex_layout_c_test_shrink_equal fn;
    tests_test_flex_layout_c --> tests_test_flex_layout_c_test_shrink_equal
    tests_test_flex_layout_c_test_shrink_with_min_clamp["test_shrink_with_min_clamp"]
    class tests_test_flex_layout_c_test_shrink_with_min_clamp fn;
    tests_test_flex_layout_c --> tests_test_flex_layout_c_test_shrink_with_min_clamp
    tests_test_box_style_c["test_box_style.c (c)"]
    class tests_test_box_style_c mod;
    tests_test_box_style_c_dbl_eq["dbl_eq"]
    class tests_test_box_style_c_dbl_eq fn;
    tests_test_box_style_c --> tests_test_box_style_c_dbl_eq
    tests_test_box_style_c_assert_edges["assert_edges"]
    class tests_test_box_style_c_assert_edges fn;
    tests_test_box_style_c --> tests_test_box_style_c_assert_edges
    tests_test_box_style_c_test_body_has_no_margin["test_body_has_no_margin"]
    class tests_test_box_style_c_test_body_has_no_margin fn;
    tests_test_box_style_c --> tests_test_box_style_c_test_body_has_no_margin
    tests_test_box_style_c_test_paragraph["test_paragraph"]
    class tests_test_box_style_c_test_paragraph fn;
    tests_test_box_style_c --> tests_test_box_style_c_test_paragraph
    tests_test_box_style_c_test_heading_ladder["test_heading_ladder"]
    class tests_test_box_style_c_test_heading_ladder fn;
    tests_test_box_style_c --> tests_test_box_style_c_test_heading_ladder
    tests_test_hostblock_c["test_hostblock.c (c)"]
    class tests_test_hostblock_c mod;
    tests_test_hostblock_c_test_free_null_idempotent["test_free_null_idempotent"]
    class tests_test_hostblock_c_test_free_null_idempotent fn;
    tests_test_hostblock_c --> tests_test_hostblock_c_test_free_null_idempotent
    tests_test_hostblock_c_test_count_null_set["test_count_null_set"]
    class tests_test_hostblock_c_test_count_null_set fn;
    tests_test_hostblock_c --> tests_test_hostblock_c_test_count_null_set
    tests_test_hostblock_c_test_load_null_args["test_load_null_args"]
    class tests_test_hostblock_c_test_load_null_args fn;
    tests_test_hostblock_c --> tests_test_hostblock_c_test_load_null_args
    tests_test_hostblock_c_test_hosts_line_drops_ip["test_hosts_line_drops_ip"]
    class tests_test_hostblock_c_test_hosts_line_drops_ip fn;
    tests_test_hostblock_c --> tests_test_hostblock_c_test_hosts_line_drops_ip
    tests_test_hostblock_c_test_various_ip_tokens_ignored["test_various_ip_tokens_ignored"]
    class tests_test_hostblock_c_test_various_ip_tokens_ignored fn;
    tests_test_hostblock_c --> tests_test_hostblock_c_test_various_ip_tokens_ignored
    tests_test_link_nav_c["test_link_nav.c (c)"]
    class tests_test_link_nav_c mod;
    tests_test_link_nav_c_test_null_out["test_null_out"]
    class tests_test_link_nav_c_test_null_out fn;
    tests_test_link_nav_c --> tests_test_link_nav_c_test_null_out
    tests_test_link_nav_c_test_null_href_blocked["test_null_href_blocked"]
    class tests_test_link_nav_c_test_null_href_blocked fn;
    tests_test_link_nav_c --> tests_test_link_nav_c_test_null_href_blocked
    tests_test_link_nav_c_test_fragment_is_same_document["test_fragment_is_same_document"]
    class tests_test_link_nav_c_test_fragment_is_same_document fn;
    tests_test_link_nav_c --> tests_test_link_nav_c_test_fragment_is_same_document
    tests_test_link_nav_c_test_https_absolute["test_https_absolute"]
    class tests_test_link_nav_c_test_https_absolute fn;
    tests_test_link_nav_c --> tests_test_link_nav_c_test_https_absolute
    tests_test_link_nav_c_test_https_relative["test_https_relative"]
    class tests_test_link_nav_c_test_https_relative fn;
    tests_test_link_nav_c --> tests_test_link_nav_c_test_https_relative
    tests_test_download_c["test_download.c (c)"]
    class tests_test_download_c mod;
    tests_test_download_c_builder["builder"]
    class tests_test_download_c_builder fn;
    tests_test_download_c --> tests_test_download_c_builder
    tests_test_download_c_test_should_renderable_types["test_should_renderable_types"]
    class tests_test_download_c_test_should_renderable_types fn;
    tests_test_download_c --> tests_test_download_c_test_should_renderable_types
    tests_test_download_c_test_should_binary_types["test_should_binary_types"]
    class tests_test_download_c_test_should_binary_types fn;
    tests_test_download_c --> tests_test_download_c_test_should_binary_types
    tests_test_download_c_test_ext_known_types["test_ext_known_types"]
    class tests_test_download_c_test_ext_known_types fn;
    tests_test_download_c --> tests_test_download_c_test_ext_known_types
    tests_test_download_c_test_ext_unknown_type["test_ext_unknown_type"]
    class tests_test_download_c_test_ext_unknown_type fn;
    tests_test_download_c --> tests_test_download_c_test_ext_unknown_type
    tests_test_form_c["test_form.c (c)"]
    class tests_test_form_c mod;
    tests_test_form_c_test_encode_basic["test_encode_basic"]
    class tests_test_form_c_test_encode_basic fn;
    tests_test_form_c --> tests_test_form_c_test_encode_basic
    tests_test_form_c_test_encode_space_and_reserved["test_encode_space_and_reserved"]
    class tests_test_form_c_test_encode_space_and_reserved fn;
    tests_test_form_c --> tests_test_form_c_test_encode_space_and_reserved
    tests_test_form_c_test_encode_unreserved_kept["test_encode_unreserved_kept"]
    class tests_test_form_c_test_encode_unreserved_kept fn;
    tests_test_form_c --> tests_test_form_c_test_encode_unreserved_kept
    tests_test_form_c_test_encode_empty_and_nameless["test_encode_empty_and_nameless"]
    class tests_test_form_c_test_encode_empty_and_nameless fn;
    tests_test_form_c --> tests_test_form_c_test_encode_empty_and_nameless
    tests_test_form_c_test_encode_overflow_fails_closed["test_encode_overflow_fails_closed"]
    class tests_test_form_c_test_encode_overflow_fails_closed fn;
    tests_test_form_c --> tests_test_form_c_test_encode_overflow_fails_closed
    tests_test_render_policy_c["test_render_policy.c (c)"]
    class tests_test_render_policy_c mod;
    tests_test_render_policy_c_test_caps_safe_is_all_off["test_caps_safe_is_all_off"]
    class tests_test_render_policy_c_test_caps_safe_is_all_off fn;
    tests_test_render_policy_c --> tests_test_render_policy_c_test_caps_safe_is_all_off
    tests_test_render_policy_c_test_caps_zero_value_is_safe["test_caps_zero_value_is_safe"]
    class tests_test_render_policy_c_test_caps_zero_value_is_safe fn;
    tests_test_render_policy_c --> tests_test_render_policy_c_test_caps_zero_value_is_safe
    tests_test_render_policy_c_test_tracking_pixel_tiny["test_tracking_pixel_tiny"]
    class tests_test_render_policy_c_test_tracking_pixel_tiny fn;
    tests_test_render_policy_c --> tests_test_render_policy_c_test_tracking_pixel_tiny
    tests_test_render_policy_c_test_tracking_pixel_zero_area["test_tracking_pixel_zero_area"]
    class tests_test_render_policy_c_test_tracking_pixel_zero_area fn;
    tests_test_render_policy_c --> tests_test_render_policy_c_test_tracking_pixel_zero_area
    tests_test_render_policy_c_test_tracking_pixel_normal["test_tracking_pixel_normal"]
    class tests_test_render_policy_c_test_tracking_pixel_normal fn;
    tests_test_render_policy_c --> tests_test_render_policy_c_test_tracking_pixel_normal
    tests_test_css_color_c["test_css_color.c (c)"]
    class tests_test_css_color_c mod;
    tests_test_css_color_c_test_null_args["test_null_args"]
    class tests_test_css_color_c_test_null_args fn;
    tests_test_css_color_c --> tests_test_css_color_c_test_null_args
    tests_test_css_color_c_test_hex_short["test_hex_short"]
    class tests_test_css_color_c_test_hex_short fn;
    tests_test_css_color_c --> tests_test_css_color_c_test_hex_short
    tests_test_css_color_c_test_hex_short_alpha["test_hex_short_alpha"]
    class tests_test_css_color_c_test_hex_short_alpha fn;
    tests_test_css_color_c --> tests_test_css_color_c_test_hex_short_alpha
    tests_test_css_color_c_test_hex_long["test_hex_long"]
    class tests_test_css_color_c_test_hex_long fn;
    tests_test_css_color_c --> tests_test_css_color_c_test_hex_long
    tests_test_css_color_c_test_hex_long_alpha["test_hex_long_alpha"]
    class tests_test_css_color_c_test_hex_long_alpha fn;
    tests_test_css_color_c --> tests_test_css_color_c_test_hex_long_alpha
    tests_test_anti_fp_c["test_anti_fp.c (c)"]
    class tests_test_anti_fp_c mod;
    tests_test_anti_fp_c_test_coarsen_time["test_coarsen_time"]
    class tests_test_anti_fp_c_test_coarsen_time fn;
    tests_test_anti_fp_c --> tests_test_anti_fp_c_test_coarsen_time
    tests_test_anti_fp_c_test_identity_is_fixed["test_identity_is_fixed"]
    class tests_test_anti_fp_c_test_identity_is_fixed fn;
    tests_test_anti_fp_c --> tests_test_anti_fp_c_test_identity_is_fixed
    tests_test_anti_fp_c_test_bucket_screen["test_bucket_screen"]
    class tests_test_anti_fp_c_test_bucket_screen fn;
    tests_test_anti_fp_c --> tests_test_anti_fp_c_test_bucket_screen
    tests_test_anti_fp_c_test_perturb_deterministic["test_perturb_deterministic"]
    class tests_test_anti_fp_c_test_perturb_deterministic fn;
    tests_test_anti_fp_c --> tests_test_anti_fp_c_test_perturb_deterministic
    tests_test_anti_fp_c_test_perturb_bounded_lsb["test_perturb_bounded_lsb"]
    class tests_test_anti_fp_c_test_perturb_bounded_lsb fn;
    tests_test_anti_fp_c --> tests_test_anti_fp_c_test_perturb_bounded_lsb
    tests_test_net_realm_c["test_net_realm.c (c)"]
    class tests_test_net_realm_c mod;
    tests_test_net_realm_c_test_classify_host_onion["test_classify_host_onion"]
    class tests_test_net_realm_c_test_classify_host_onion fn;
    tests_test_net_realm_c --> tests_test_net_realm_c_test_classify_host_onion
    tests_test_net_realm_c_test_classify_host_i2p["test_classify_host_i2p"]
    class tests_test_net_realm_c_test_classify_host_i2p fn;
    tests_test_net_realm_c --> tests_test_net_realm_c_test_classify_host_i2p
    tests_test_net_realm_c_test_classify_host_clearnet["test_classify_host_clearnet"]
    class tests_test_net_realm_c_test_classify_host_clearnet fn;
    tests_test_net_realm_c --> tests_test_net_realm_c_test_classify_host_clearnet
    tests_test_net_realm_c_test_classify_host_lookalikes["test_classify_host_lookalikes"]
    class tests_test_net_realm_c_test_classify_host_lookalikes fn;
    tests_test_net_realm_c --> tests_test_net_realm_c_test_classify_host_lookalikes
    tests_test_net_realm_c_test_classify_host_edges["test_classify_host_edges"]
    class tests_test_net_realm_c_test_classify_host_edges fn;
    tests_test_net_realm_c --> tests_test_net_realm_c_test_classify_host_edges
    tests_test_request_policy_c["test_request_policy.c (c)"]
    class tests_test_request_policy_c mod;
    tests_test_request_policy_c_test_host_of_basic["test_host_of_basic"]
    class tests_test_request_policy_c_test_host_of_basic fn;
    tests_test_request_policy_c --> tests_test_request_policy_c_test_host_of_basic
    tests_test_request_policy_c_test_host_of_invalid["test_host_of_invalid"]
    class tests_test_request_policy_c_test_host_of_invalid fn;
    tests_test_request_policy_c --> tests_test_request_policy_c_test_host_of_invalid
    tests_test_request_policy_c_test_host_of_overflow["test_host_of_overflow"]
    class tests_test_request_policy_c_test_host_of_overflow fn;
    tests_test_request_policy_c --> tests_test_request_policy_c_test_host_of_overflow
    tests_test_request_policy_c_test_site_of["test_site_of"]
    class tests_test_request_policy_c_test_site_of fn;
    tests_test_request_policy_c --> tests_test_request_policy_c_test_site_of
    tests_test_request_policy_c_test_site_of_multi_suffix["test_site_of_multi_suffix"]
    class tests_test_request_policy_c_test_site_of_multi_suffix fn;
    tests_test_request_policy_c --> tests_test_request_policy_c_test_site_of_multi_suffix
    tests_test_ui_c["test_ui.c (c)"]
    class tests_test_ui_c mod;
    tests_test_ui_c_assert_line["assert_line"]
    class tests_test_ui_c_assert_line fn;
    tests_test_ui_c --> tests_test_ui_c_assert_line
    tests_test_ui_c_test_wrap_null_args["test_wrap_null_args"]
    class tests_test_ui_c_test_wrap_null_args fn;
    tests_test_ui_c --> tests_test_ui_c_test_wrap_null_args
    tests_test_ui_c_test_wrap_empty["test_wrap_empty"]
    class tests_test_ui_c_test_wrap_empty fn;
    tests_test_ui_c --> tests_test_ui_c_test_wrap_empty
```

---

## Architecture Reference

### C (98 files)

#### `fuzz_css.c`
**Path:** `fuzz/fuzz_css.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 61)

#### `fuzz_dom.c`
**Path:** `fuzz/fuzz_dom.c`

**Functions:**
- `ensure_built` (line 40)
- `LLVMFuzzerTestOneInput` (line 47)

#### `fuzz_dom_debug.c`
**Path:** `fuzz/fuzz_dom_debug.c`

**Functions:**
- `pass` (line 8)

#### `fuzz_download.c`
**Path:** `fuzz/fuzz_download.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 30)

#### `fuzz_freebug.c`
**Path:** `fuzz/fuzz_freebug.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 36)

#### `fuzz_html_parse.c`
**Path:** `fuzz/fuzz_html_parse.c`

*No symbols extracted*

#### `fuzz_image_decode.c`
**Path:** `fuzz/fuzz_image_decode.c`

**Functions:**
- `poke_and_free` (line 21) - *Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Safe on a zeroed (failed-decode) struct.*
- `LLVMFuzzerTestOneInput` (line 31)

#### `fuzz_js_sandbox.c`
**Path:** `fuzz/fuzz_js_sandbox.c`

*No symbols extracted*

#### `fuzz_page_view.c`
**Path:** `fuzz/fuzz_page_view.c`

*No symbols extracted*

#### `fuzz_pdf_export.c`
**Path:** `fuzz/fuzz_pdf_export.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 29)

#### `fuzz_text_shape.c`
**Path:** `fuzz/fuzz_text_shape.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 24) - *The first input byte (when present) is consumed to vary the font selector and pixel size; the rest is the shaped text.  Build & run: make fuzz-tsh ...*

**Macros:**
- `FZ_CAP` (line 22)

#### `fuzz_url.c`
**Path:** `fuzz/fuzz_url.c`

**Functions:**
- `check_split` (line 29)
- `LLVMFuzzerTestOneInput` (line 57)

#### `browser_ui.c`
**Path:** `gui/browser_ui.c`

**Functions:**
- `now_ms` (line 127) - *Largest text slice measured/drawn at once (one word, or one clipped label). * Words longer than this are still placed, just measured up to the cap....*
- `gutter` (line 414)
- `apply_zoom` (line 435) - *Applies a new zoom level: rebuild the theme and repaint. The page is laid out fresh from w->theme on every paint, so no re-fetch and no worker roun...*
- `buffer_release` (line 444) - *Applies a new zoom level: rebuild the theme and repaint. The page is laid out fresh from w->theme on every paint, so no re-fetch and no worker roun...*
- `destroy_buffer` (line 450)
- `ensure_buffer` (line 456)
- `read_file` (line 486) - *w->buffer = wl_shm_pool_create_buffer(pool, 0, w->width, w->height, stride, WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (w->b...*
- `build_file_origin` (line 526) - *Builds a "file:///<canonical absolute path>" origin from a local path (or passes through a file:// URL's path). realpath canonicalizes; on failure ...*
- `load_host_file` (line 536) - *Loads one /etc/hosts-format .conf file (if present and readable) into the given * list. A missing file is not an error: the filter fails open, neve...*
- `build_host_filter` (line 553) - *Builds the host filter from the user's .conf lists. Privacy by Default: block.conf (a /etc/hosts-format blocklist) blocks trackers/ads and their su...*
- `freedom_write_dir` (line 603) - *The writable Freedom config dir: $FREEDOM_HOSTS_DIR if set, else ~/.config/freedom (created if absent). Returns 0 on success. Mirrors the read sear...*
- `add_current_host_to_list` (line 628) - *Appends the current page's host to one of the user's .conf lists (block/allow/js), then reloads the in-memory filter so it applies. The host is hos...*
- `load_favorites` (line 696) - *Concatenates the allow.conf bodies along the same search path build_host_filter uses into one string: the omnibox "favorites". Frees any previous v...*
- `omni_refresh` (line 739) - *Recomputes the omnibox autocomplete suggestions for the current URL-bar text. Shown only while the URL bar is focused and something is typed; other...*
- `proxy_addr_from_env` (line 753) - *Copies a proxy "host:port" into dst: if the env value is unset/empty the default is used; the literal "1" also means "use the default" (a convenien...*
- `init_net_config` (line 767) - *Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in, everything off unless explicitly enabled). FREEDOM_TOR_PROXY / ...*
- `is_https_url` (line 776)
- `is_http_url` (line 780)
- `host_from_url` (line 792) - *A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is * fetched over the network (through the overlay proxy), not read as a...*
- `input_is_editable` (line 814) - *const char *colon = memchr(p, ':', (size_t)(end - p)); const char *host_end = colon != NULL ? colon : end; size_t len = (size_t)(host_end - p); if ...*
- `free_inputs` (line 820) - *return 1; }  #include "form.h" #include "secure_fetch.h" #include "tab.h"  /* An editable control gets a live text field; submit/button/hidden do n...*
- `free_images` (line 828) - *static int input_is_editable(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD || input_type == PV_IN_TEXTAREA; }  ...*
- `find_image` (line 838) - *w->focused_input = -1; }  /* Releases the decoded image surfaces of the current page and the array. static void free_images(browser_window *w) { fo...*
- `layout` (line 848)
- `rebuild_inputs` (line 862) - *Builds the live editable state for the current doc: one entry per editable * control, seeded with its declared value. Aliases the doc blocks (not o...*
- `find_input_state` (line 887) - *if (w->inputs == NULL) return; /* fail closed: no editable fields, page still shows size_t k = 0; for (size_t i = 0; i < n; ++i) { const rd_block *...*
- `clear_doc` (line 895) - *Releases the structured render of the previous page (text mode resumes). The * hovered link and the live form controls alias the doc, so they are c...*
- `set_cache` (line 904) - *Releases the structured render of the previous page (text mode resumes). The * hovered link and the live form controls alias the doc, so they are c...*
- `surface_from_pixels` (line 915) - *Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit. Copies row by row because Cairo may use a wider stride than the tightly packed...*
- `fetch_follow_navigable` (line 981) - *Fetches url (following redirects) under cfg's policy, applying two navigability fallbacks in order of decreasing security: 1) If the only obstacle ...*
- `GET` (line 1014)
- `gui_subresource_fetch` (line 1060) - *tab_fetch_fn: the trusted parent's policy-checked subresource fetch for page XHR/fetch. The worker has no network; it proxied the request here. We ...*
- `prepare_fetch` (line 1113) - *Builds cfg for url and applies the pre-fetch gates. Returns nonzero when the fetch may proceed (cfg and pr->allowlisted are then set); returns 0 wh...*
- `fetch_job_free` (line 1202)
- `fetch_thread` (line 1222) - *Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer back to the event loop. Pure with respect to the window: it rea...*
- `fetch_launch` (line 1261) - *Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch). The caller has bumped w->net_gen for this navigation; the job sna...*
- `load_images` (line 1313) - *Fetches and decodes every allowed image of the current doc into w->images (one entry per RD_IMAGE block). Each fetch re-applies the full TLS/PQ/cha...*
- `compute_page_js` (line 1413) - *Resolves the JS policy for the current page's host (Secure by Default: off unless the global mode is ON or the host is on the js.conf allowlist). P...*
- `drop_repl_worker` (line 1424) - *Drops the kept-alive REPL worker and clears the (active-tab) console transcript. Used when the active page changes WITHOUT a re-render (tab switch ...*
- `render_current_ex` (line 1429)
- `render_current` (line 1518) - *Move the page's captured console transcript into the window for Freebug, then keep the worker ALIVE (tab_worker) so the console REPL can tab_eval a...*
- `show_busy` (line 1525) - *Marks a request in flight and paints a frame so the spinner appears at once. The fetch now runs on a worker thread, so the event loop keeps animati...*
- `show_fetch_error` (line 1534) - *Replaces the page with the standard "Failed to load" diagnostic for status ss on url. allowlisted tailors the hint (already retried vs. how to over...*
- `arrives` (line 1585)
- `strcmp` (line 1623)
- `tab_save` (line 1682) - *Parks the active tab's live state into its slot (a shallow move: the slot and the live fields briefly alias the same allocations; the live fields a...*
- `tab_restore` (line 1698) - *c->bs = w->bs; c->doc = w->doc; c->caps = w->caps; c->scroll = w->scroll; c->content_total_h = w->content_total_h; c->inputs = w->inputs; c->input_...*
- `free_live_page` (line 1714) - *w->bs = c->bs; w->doc = c->doc; w->caps = c->caps; w->scroll = c->scroll; w->content_total_h = c->content_total_h; w->inputs = c->inputs; w->input_...*
- `tab_ctx_release` (line 1723) - *w->hover_href = c->hover_href; w->hover_cursor = c->hover_cursor; }  /* Frees the LIVE page's owned state (used when closing the foreground tab). s...*
- `tab_switch` (line 1738) - *if (c->images != NULL) { for (size_t i = 0; i < c->image_count; ++i) if (c->images[i].surface != NULL) cairo_surface_destroy(c->images[i].surface);...*
- `tab_new` (line 1757) - *w->net_gen++; w->loading = 0; drop_repl_worker(w); /* active page changes without a render; rebind on next eval tab_save(w); w->active_tab = idx; t...*
- `uitab_close` (line 1789) - *w->inputs = NULL; w->input_count = 0; w->focused_input = -1; w->images = NULL; w->image_count = 0; w->cur_html = NULL; w->cur_html_len = 0; w->cur_...*
- `newtab_x` (line 1831) - *X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge.*
- `tab_title` (line 1838) - *X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge. static double newtab_x(const browser_win...*
- `tabbar_top` (line 1854) - *Top of the tab strip: directly under the client-side titlebar (or at the surface * top under server-side decorations).*
- `toolbar_top` (line 1860) - *Top of the toolbar: under the tab strip, which is always reserved. The whole * content area derives from this, so adding the strip reflows everythi...*
- `content_geometry` (line 1867) - *The content area rectangle below the toolbar, in surface coordinates. The single source of truth for both painting and click hit-testing so they ca...*
- `content_width` (line 1893)
- `scrollbar_metrics` (line 1904) - *Geometry of the vertical scrollbar in surface coordinates, plus the current thumb position. Returns 0 (and leaves outputs untouched) when the conte...*
- `scrollbar_drag_to` (line 1932) - *Maps the current pointer Y (less the grab offset) to a scroll offset while the * thumb is being dragged, then repaints. No-op when there is no scro...*
- `draw_scrollbar` (line 1949) - *Paints the scrollbar track and thumb. The thumb highlights while hovered or * dragged, the same affordance the toolbar buttons and links get.*
- `window_button_rects` (line 1985)
- `toolbar_rects` (line 1995) - *The reload button sits as the third left chrome button (after back/forward), at a * fixed x; callers that need it derive it here so the layout stay...*
- `toolbar_button_at` (line 2011) - *Which toolbar button (if any) is at (px, py). Shared by the hover highlight and * the cursor shape so they cannot drift from the click hit-test.*
- `hot_actionable` (line 2027) - *A hovered button is "actionable" (gets the hand cursor) when clicking it would * do something: Go/menu always, Back/Forward only when there is hist...*
- `menu_panel_rect` (line 2038) - *The options-menu panel rectangle (below the gear button), and its per-item row * height. The single source of truth for drawing and hit-testing the...*
- `ua_box_rect` (line 2054) - *The editable User-Agent box rectangle inside the options panel. The single * source of truth for drawing and hit-testing the field.*
- `draw_text` (line 2063)
- `rc_free` (line 2226)
- `rc_add_box` (line 2235)
- `rc_add_frag` (line 2247)
- `rc_add_row` (line 2257)
- `family_face` (line 2270) - *Maps an author font-family bucket (css_font_family) to a Cairo toy-font family. * The engine matches no exact families, only the generic groups.*
- `content_font` (line 2287)
- `set_rgb_alpha` (line 2301) - *Sets the source color, applying an author opacity (0..100) as an alpha when set * (-1 = fully opaque). Used for author text and its shadow.*
- `utf8_clen` (line 2310) - *Bytes in the UTF-8 cluster starting at s[0] (1 for a stray/continuation byte), * clamped to n.*
- `draw_slice` (line 2350) - *Draws a text slice at (x, baseline) in the current content font/source. Shapes with HarfBuzz when available; otherwise the Cairo toy API. Mirrors m...*
- `frag_styled` (line 2363) - *True if a fragment needs the per-cluster path (text-transform other than none/unset, or a non-zero letter-spacing). Otherwise the fast whole-slice ...*
- `styled_advance` (line 2370) - *Advance (px) of a fragment's text under its text-transform + letter-spacing. The current Cairo font must already be selected. Mirrors styled_draw e...*
- `styled_draw` (line 2386) - *Draws a fragment's text starting at (x, baseline) under its text-transform + * letter-spacing. The current Cairo font/source must already be set.*
- `block_style` (line 2402)
- `block_margins` (line 2426) - *Vertical margins (px) of a block from the user-agent box model (box_style), resolved against the block's own font size (em -> px). The user-agent n...*
- `flush_line` (line 2438)
- `open_line` (line 2458)
- `flow_emit_frag` (line 2496) - *Emits one fragment at the current pen position, advancing it. Shared by the * whole-word path and the word-break split path in flow_text.*
- `flow_text` (line 2543) - *owning box (for the hover-cursor lookup), -1 if none.  word-break/overflow-wrap (s->break_words): a single word wider than the WHOLE line (not just...*
- `flow_text_block` (line 2691) - *Flows one text/link/notice block into L at content_w using state s. The caller sets s->bg_rgb (the block's author background, or -1) beforehand; th...*
- `effect` (line 2772)
- `css_align_to_bt` (line 2788) - *Maps a css_align_kw (align-items/align-self) to the box_tree cross-axis alignment it drives. BASELINE/AUTO/UNSET/space-* (align-content only, never...*
- `layout_container` (line 2796)
- `ITEMS` (line 2846)
- `slot` (line 2924)
- `box_edge_px` (line 3029) - *if (bt_layout(&root, content_w) != BT_OK) return;  /* Translate each item's rows into its column rectangle. for (size_t j = 0; j < g; ++j) { const ...*
- `box_line_visible` (line 3035) - *True iff a border/outline style paints a line (solid..outset); none/hidden/unset * paint nothing. The fancier 3D styles collapse to solid at paint ...*
- `close_top_box` (line 3041) - *Closes the open block box: flushes the current line, reserves the box's bottom * padding+border, and finalizes the recorded border-box height. No-o...*
- `rc_box_context` (line 3072) - *Content rect (left, width) the current run/box is laid out in: the innermost open * box's, or the page content box when no box is open (default fla...*
- `children` (line 3087)
- `reconcile_boxes` (line 3188) - *Reconciles the open-box stack so it equals block b's box path (root..b->block_id), derived from the box-def parent_id chain. Closes any open box no...*
- `box_path_of` (line 3223) - *Box path root..block_id via the box-def parent_id chain (root first), written into * out (bounded by RC_BOX_STACK_MAX). Returns the path length; bl...*
- `band_common_box` (line 3239) - *The innermost box that is an ancestor (or self) of EVERY block in [start, end), via the longest common prefix of their box paths — the box a float ...*
- `layout_float_band` (line 3258) - *Lays a float band [start, end) — a maximal run of blocks each with float_id >= 0 — side by side inside the current box context (spec/float.md). Blo...*
- `layout_doc` (line 3341)
- `position_doc` (line 3514) - *Stage 2: resolves out-of-flow positioning for every absolute/fixed block in the document and stores the stacking-ordered result in L->positioned. R...*
- `input_box_width` (line 3616) - *make the painter repaint the box on TOP of its rows — covering everything past the first block with the box background. So drop the in-flow (relati...*
- `button_box_width` (line 3621) - *for (size_t i = 0; i < L->npositioned; ++i) { size_t bid = L->positioned[i].box_index; if (bid < BT_MAX_POSITIONED && in_flow[bid]) continue; L->po...*
- `row_align_offset` (line 3761) - *Horizontal shift a row's text gets from author text-align (center/right): the slack between the available width and the line's right edge. 0 for le...*
- `paint_box_decoration` (line 3776) - *Paints one block box's decoration (Hito 23b-8 Step C): box-shadow, background fill, the four borders and the outline, behind the rows it encloses. ...*
- `paint_content_row` (line 3872) - *Paints one laid-out row at vertical position ry. Shared by the on-screen painter and the PDF exporter so both render identically (same fonts, colou...*
- `cairo_set_dash` (line 3941)
- `cairo_set_dash` (line 3943)
- `ov_box_clips` (line 3969) - *} if (f->overline) { double oy = fbaseline - f->font_size * UI_OVERLINE_OFFSET; cairo_move_to(cr, x0, oy); cairo_line_to(cr, x1, oy); cairo_stroke(...*
- `ov_collect_chain` (line 3977) - *Walks the ancestor chain of block_id and collects overflow:hidden box IDs * into out[] (outermost first). Returns count, limited to OV_MAX_DEPTH.*
- `ov_find_box` (line 3991) - *static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap) { int tmp[OV_MAX_DEPTH], n = 0; for (int id = block_id; id >= 0 && ...*
- `ov_content_rect` (line 3999) - *Computes the padding-box content rect (in page coords: y, x, w, h) for a box. * Used as the clip region for overflow:hidden children.*
- `paint_structured` (line 4055)
- `write_doc_pdf` (line 4203) - *Writes the window's current laid-out document to a vector PDF at `path`, paginated to US Letter. Returns the page count (0 when the document lays o...*
- `export_pdf` (line 4339)
- `write_doc_png` (line 4391) - *Writes the window's current laid-out document to a single full-height PNG at `path` (the same layout/paint path as the screen and the PDF export, i...*
- `export_png` (line 4520)
- `caller` (line 4555)
- `ui_render_png` (line 4578) - *Headless PNG export (no Wayland; see include/ui.h). One full-height bitmap of the whole page, the cheapest artifact for visual review (no PDF raste...*
- `ui_dump_layout` (line 4603) - *Headless layout dump: runs the same layout_doc + position_doc pass as the on-screen/PNG renderer and prints the resolved box geometry (in-flow boxe...*
- `link_at_point` (line 4654) - *Returns the link target under the surface point (px, py), or NULL when the point is outside the content area or not over a link fragment. The layou...*
- `resolve_box_cursor` (line 4700) - *First non-unset author `cursor` on block_id's box or an ancestor (nearest wins, like the rest of the box-decoration fields), or CSS_CUR_UNSET if no...*
- `cursor_at_point` (line 4716) - *Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET when outside content / no box sets one. Unlike link_at_point this t...*
- `node_at_point` (line 4763) - *Returns the DOM node id of the element under (px, py), or DOM_NODE_NONE if the point is over blank space / outside content. Mirrors layout and scro...*
- `reference` (line 4807)
- `apply_click_result` (line 4828) - *Applies a click result returned by the worker: rebuild the rendered document and refresh inputs/console, but keep the current page in history (a cl...*
- `memory` (line 4849)
- `GET` (line 4920)
- `ensure_download_dir` (line 4954) - *Builds ~/Downloads/freedom into out and creates both levels (best effort; an existing directory is fine). Returns 1 on success. Falls back to $HOME...*
- `write_file_atomic` (line 4969) - *Writes len bytes to path with 0600 perms via a temp file + atomic rename (the disk_store convention): a crash mid-write never leaves a half file at...*
- `save_download` (line 4991) - *Saves a fetched resource to ~/Downloads/freedom instead of rendering it. The filename is derived fail-closed from the hostile Content-Disposition /...*
- `save_current_page` (line 5024) - *Ctrl+S: save the current page's cached source to ~/Downloads/freedom. No network * round-trip -- the bytes already in the page cache are written.*
- `deliver_fetch_result` (line 5033)
- `drain_fetch_results` (line 5088) - *Drains every completed fetch the worker threads have posted (the read end is non-blocking; pointer-sized writes are atomic). Called when the loop s...*
- `toggle_reader` (line 5155) - *Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author styling/images are gated off, a...*
- `menu_item_checked` (line 5165) - *Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author styling/images are gated off, a...*
- `menu_item_toggle` (line 5183) - *Toggles options-menu item i and applies its effect. Theme and force-colors only affect presentation (a repaint, which re-runs layout, suffices); a ...*
- `draw_clock` (line 5261) - *A small spinner meaning "busy". Now that the fetch runs off the event-loop thread, the loop ticks ~12 fps while loading and rotates a leading arc s...*
- `draw_hamburger` (line 5272)
- `draw_reload` (line 5289) - *The reload button glyph: a ~300-degree circular arrow centred in a UI_BTN_W button starting at bx. Drawn with Cairo (not a font glyph) so it never ...*
- `draw_menu` (line 5311) - *double a1 = a0 + UI_TWO_PI * 0.82;      /* leave a gap for the arrowhead cairo_new_sub_path(cr); cairo_arc(cr, cx, cy, r, a0, a1); cairo_stroke(cr)...*
- `draw_hover_url` (line 5422) - *Persistent bottom strip showing the target of the link under the pointer, so the user always knows where a click will go. Returns the strip height ...*
- `draw_toast` (line 5454) - *Draws the transient status toast (a banner near the bottom of the window), * raised by bottom_offset so it stacks above the hover-URL strip when bo...*
- `draw_tabstrip` (line 5484) - *Paints the tab strip: one cell per tab (the active one connected to the content background, the rest dimmed), each with its clipped title and a clo...*
- `draw_omnibox` (line 5539) - *Omnibox autocomplete dropdown: a panel of favorite-host suggestions below the URL bar, drawn as an overlay (on top of content) while the URL bar is...*
- `paint` (line 5572)
- `redraw` (line 5813)
- `wm_base_ping` (line 5824) - *cairo_surface_flush(w->cairo_surface); cairo_destroy(cr); }  static void redraw(browser_window *w) { if (!w->configured) return; if (ensure_buffer(...*
- `xdg_surface_configure` (line 5830)
- `toplevel_configure` (line 5838)
- `wl_array_for_each` (line 5854)
- `toplevel_close` (line 5859)
- `deco_configure` (line 5867)
- `set_cursor` (line 5881) - *Applies the hand (over a link) or default arrow cursor for the current pointer enter serial. A no-op when no themed cursor is available (the compos...*
- `update_hover` (line 5903) - *Recomputes which link (if any) is under the pointer; on a change, updates the cursor shape and repaints so the hover highlight follows. The author ...*
- `fbw_split_y` (line 5958) - *int    width, height; int    configured; int    visible; struct wl_buffer *buffer; void  *shm_data; size_t shm_size; cairo_surface_t *cairo_surface...*
- `freebug_ensure_buffer` (line 5966)
- `fbw_level_rgb` (line 5994) - *struct wl_shm_pool *pool = wl_shm_create_pool(fb->owner->shm, fd, (int32_t)size); fb->buffer = wl_shm_pool_create_buffer(pool, 0, fb->width, fb->he...*
- `fbw_console_lines` (line 6005) - *}  /* Color for a console level (dark devtools palette). static void fbw_level_rgb(int level, double *r, double *g, double *b) { switch (level) { c...*
- `freebug_paint` (line 6014)
- `freebug_redraw_fb` (line 6173)
- `freebug_redraw` (line 6182)
- `freebug_hide` (line 6186)
- `fbw_xdg_surface_configure` (line 6202)
- `fbw_toplevel_configure` (line 6210)
- `fbw_toplevel_close` (line 6220)
- `freebug_show` (line 6229)
- `freebug_toggle` (line 6259)
- `freebug_destroy` (line 6264)
- `freebug_owns_surface` (line 6271)
- `freebug_is_open` (line 6275)
- `freebug_repl_worker` (line 6283) - *Returns the live page worker for the REPL, lazily (re)opening one bound to the active page's cache if none is kept alive (e.g. just after a tab swi...*
- `freebug_eval` (line 6306)
- `freebug_handle_key` (line 6345)
- `freebug_pointer_button` (line 6377)
- `freebug_pointer_motion` (line 6388)
- `freebug_pointer_axis` (line 6400)
- `ptr_enter` (line 6411) - *fb->split = s; freebug_redraw_fb(fb); }  static void freebug_pointer_axis(browser_window *w, wl_fixed_t value) { freebug_window *fb = w->freebug; i...*
- `ptr_leave` (line 6424)
- `ptr_motion` (line 6435)
- `load_current` (line 6444)
- `go_omnibox` (line 6458) - *Commits the URL bar like a real omnibox: an existing local file is opened as before; otherwise url_omnibox (pure) decides between navigating to a s...*
- `ptr_button` (line 6490)
- `scroll_line_px` (line 6680) - *} else if (input_is_editable(ctl->input_type)) { for (size_t i = 0; i < w->input_count; ++i) { if (w->inputs[i].blk == ctl) { w->focused_input = (i...*
- `ptr_axis` (line 6683)
- `mime_is_text` (line 6710) - *redraw(w); }  static const struct wl_pointer_listener pointer_listener = { .enter = ptr_enter, .leave = ptr_leave, .motion = ptr_motion, .button = ...*
- `data_offer_source_actions` (line 6728)
- `data_offer_action` (line 6731)
- `data_device_data_offer` (line 6741) - *} static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) { (void)d; (void)o; (void)a; } static void data_offer_action(...*
- `data_device_selection` (line 6753) - *The clipboard selection changed. Commit the new offer (or NULL when the clipboard * was cleared), destroying any previous one we held.*
- `data_device_enter` (line 6772) - *wl_data_offer_destroy(w->selection_offer); if (offer == NULL) { w->selection_offer = NULL; w->selection_offer_has_text = 0; w->sel_mime[0] = '\0'; ...*
- `data_device_leave` (line 6777)
- `data_device_motion` (line 6778)
- `data_device_drop` (line 6782)
- `data_source_cancelled` (line 6793) - *wl_fixed_t x, wl_fixed_t y) { (void)d; (void)dev; (void)t; (void)x; (void)y; } static void data_device_drop(void *d, struct wl_data_device *dev) { ...*
- `data_source_send` (line 6799) - *.enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop, .selection = data_device_selection,...*
- `data_source_target` (line 6812)
- `insert_pasted_text` (line 6825) - *Inserts pasted bytes into whichever text target currently has focus (page input, User-Agent box, or the URL bar). Control bytes -- including embedd...*
- `clipboard_copy` (line 6889) - *Ctrl+C: copy the focused field's text (or, with nothing focused, the page address) * to the clipboard by owning a wl_data_source that serves it on ...*
- `keyboard_keymap` (line 6936) - *Cut the omnibar selection: copy it to the clipboard, then remove it. v1 cut is the * URL bar only (page inputs / the UA box have no selection model...*
- `keyboard_enter` (line 6957)
- `keyboard_leave` (line 6964)
- `handle_key_press` (line 6973) - *Performs the effect of a single key press. Factored out of keyboard_key so a held key can be re-fired from the repeat timer with the exact same sem...*
- `key_is_repeatable` (line 7254) - *Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion and scrolling. A Ctrl chord (tab spawn, reload, image toggle...) o...*
- `key_repeat_arm` (line 7270) - *Arms the repeat timer for key: first fire after repeat_delay ms, then every * 1/repeat_rate s. A held key thus repeats until released (key_repeat_s...*
- `key_repeat_stop` (line 7283) - *1/repeat_rate s. A held key thus repeats until released (key_repeat_stop). static void key_repeat_arm(browser_window *w, uint32_t key) { if (w->rep...*
- `key_repeat_fire` (line 7294) - *Re-fires the currently held key. Called from the event loop when the timer expires. Modifiers/keysym are recomputed from the live xkb_state, so a c...*
- `keyboard_key` (line 7307)
- `keyboard_modifiers` (line 7346)
- `keyboard_repeat_info` (line 7356)
- `seat_caps` (line 7374) - *w->repeat_rate = rate; w->repeat_delay = delay; }  static const struct wl_keyboard_listener keyboard_listener = { .keymap = keyboard_keymap, .enter...*
- `seat_name` (line 7386)
- `registry_global` (line 7392) - *w->pointer = wl_seat_get_pointer(seat); wl_pointer_add_listener(w->pointer, &pointer_listener, w); } if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && w-...*
- `registry_remove` (line 7413)
- `ui_run_browser` (line 7422) - *w->data_device_manager = wl_registry_bind(reg, name, &wl_data_device_manager_interface, 1); } else if (strcmp(iface, zxdg_decoration_manager_v1_int...*

**Macros:**
- `_GNU_SOURCE` (line 11)
- `UI_TOOLBAR_H` (line 65)
- `UI_TITLEBAR_H` (line 67)
- `UI_TABBAR_H` (line 68)
- `UI_TAB_MIN_W` (line 69)
- `UI_TAB_MAX_W` (line 70)
- `UI_TAB_NEW_W` (line 71)
- `UI_TAB_CLOSE_W` (line 72)
- `UI_BTN_W` (line 73)
- `UI_WIN_BTN_W` (line 74)
- `UI_MARGIN` (line 75)
- `UI_BTN_LEFT` (line 76)
- `UI_LIST_INDENT` (line 77)
- `UI_SCROLLBAR_W` (line 82)
- `UI_SCROLLBAR_MIN` (line 83)
- `UI_SCROLLBAR_PAD` (line 84)
- `UI_RESIZE_MARGIN` (line 88)
- `UI_MENU_W` (line 93)
- `UI_MENU_ITEM_H` (line 94)
- `UI_MENU_PAD` (line 95)
- `UI_CHECK_SZ` (line 96)
- `UI_MENU_LABEL_H` (line 97)
- `UI_MENU_INPUT_H` (line 98)
- `UI_HAMBURGER_W` (line 99)
- `UI_HAMBURGER_GAP` (line 100)
- `UI_CURSOR_SIZE` (line 101)
- `UI_TOAST_PAD` (line 102)
- `OMNI_MAX_SUGG` (line 103)
- `UI_OMNI_ROW_H` (line 104)
- `UI_TWO_PI` (line 105)
- `UI_INPUT_PAD` (line 109)
- `UI_INPUT_WIDTH` (line 110)
- `UI_BUTTON_HPAD` (line 111)
- `UI_FORM_FIELDS_MAX` (line 112)
- `UI_UNDERLINE_OFFSET` (line 117)
- `UI_UNDERLINE_THICK` (line 118)
- `UI_STRIKE_OFFSET` (line 119)
- `UI_OVERLINE_OFFSET` (line 120)
- `UI_SLICE_MAX` (line 124)
- `UI_MENU_COUNT` (line 177)
- `UI_IMAGE_MAX_BODY` (line 195)
- `UI_MAX_TABS` (line 210)
- `UI_READER_COLUMN_W` (line 418)
- `JS_NAV_MAX` (line 1399)
- `UI_RELOAD_X` (line 1994)
- `RC_BOX_STACK_MAX` (line 2193)
- `RC_MAX_OUT_OF_FLOW` (line 3219)
- `OV_MAX_DEPTH` (line 3966)
- `PDF_PAGE_W` (line 4187)
- `PDF_PAGE_H` (line 4188)
- `PDF_MARGIN` (line 4189)
- `PNG_PAGE_W` (line 4382)
- `PNG_MARGIN` (line 4383)
- `PNG_MAX_H` (line 4384)
- `FBW_W` (line 5928)
- `FBW_H` (line 5930)
- `FBW_HEADER` (line 5931)
- `FBW_PAD` (line 5932)
- `FBW_LINE` (line 5933)
- `FBW_GUTTER` (line 5934)
- `FBW_MIN_SPLIT` (line 5935)
- `FBW_MAX_SPLIT` (line 5936)

**Structs:**
- `ui_menu_item` (line 153)
- `ui_input_state` (line 188) - *Live editable state for one form text control, aliasing a block of the current rd_doc (not owned; valid until the doc is replaced). The field carri...*
- `ui_image` (line 201) - *A decoded image for one RD_IMAGE block of the current doc. surface owns the pixels (ARGB32) and is NULL when the image was blocked, not fetched, or...*
- `tab_ctx` (line 218) - *One tab's complete per-page state: everything that must persist when the tab is not the foreground one. The browser_window keeps the ACTIVE tab's c...*
- `browser_window` (line 231)
- `fetch_prep` (line 1104) - *Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post). Both MUST pass through the SAME host filter, per-host exception, ...*
- `fetch_job` (line 1173) - *A network request handed to the fetch thread. It owns deep copies of every input string (the window's buffers may change while the fetch runs), and...*
- `rc_frag` (line 2084) - *The content area paints an rd_doc (the same structured document the headless mode prints): headings, paragraphs and inline links flow word-by-word ...*
- `rc_row` (line 2118)
- `rc_box` (line 2137) - *One painted block box (Hito 23b-8 Step C): a border-box rectangle in layout space with its author decoration, painted behind the rows it encloses. ...*
- `rc_layout` (line 2158)
- `rc_open_box` (line 2184) - *Box engine (Hito 23b-8 Step D): one entry of the open-box stack. A box's content rect (inner_left/inner_w) is the coordinate context its children (...*
- `rc_state` (line 2195) - *Max box-nesting depth the painter composes (anti-DoS; deeper boxes are clamped to * the innermost open box, so a pathological tree never overflows ...*
- `rc_ext` (line 2473) - *Author text-presentation extensions for a block, derived from its rd_block (already * gated by caps.css upstream) and handed to flow_text.*
- `freebug_window` (line 5938) - *tab_eval's against the live page worker (browser_window.tab_worker, kept alive after render). Opened with F12 or the hamburger menu. It shares disp...*

#### `bui_theme.c`
**Path:** `gui/bui_theme.c`

**Functions:**
- `ui_theme_default` (line 14) - *bui_theme — presentation palettes for the Wayland/Cairo GUI.  Carved out of browser_ui.c: the light/dark/sepia themes and the small colour helpers,...*
- `ui_theme_dark` (line 73) - *Dark reading palette. Shares all the metrics (font sizes, spacing) with the * default theme; only the colours change, so the box model stays in one...*
- `ui_theme_sepia` (line 118) - *Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form text. Shares all the metrics with the default the...*
- `ui_theme_for` (line 160) - *t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.menu_text      = (ui_rgb){ 0.26, 0.19, 0.10 }; ...*
- `rgb_from_packed` (line 169) - *t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; }  /* The single place that maps the theme mode to a palette. ui_theme ui_theme_for...*
- `set_rgb` (line 173)

#### `freedom_view.c`
**Path:** `gui/freedom_view.c`

**Functions:**
- `main` (line 36)

**Macros:**
- `_POSIX_C_SOURCE` (line 9)

#### `ui_render.c`
**Path:** `gui/ui_render.c`

**Functions:**
- `sanitize_utf8_inplace` (line 37) - *Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence with '?'. cairo_show_text rejects invalid UTF-8 a...*
- `button_rects` (line 105) - *int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; double ptr_x, ptr_y;  const char *title; const char ...*
- `buffer_release` (line 112) - *size_t      text_len; size_t      scroll; /* first visible line } ui_window;  static void redraw(ui_window *w);  /* Right-aligned control buttons: ...*
- `destroy_buffer` (line 119)
- `ensure_buffer` (line 125)
- `paint` (line 156) - *WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (w->buffer == NULL) { munmap(data, size); return -1; } wl_buffer_add_listener(w->...*
- `redraw` (line 242)
- `wm_base_ping` (line 257) - *Always repaint and re-commit. We do not gate on buffer release: a single shm buffer can be re-attached, and gating on release deadlocks against * c...*
- `xdg_surface_configure` (line 263)
- `toplevel_configure` (line 271)
- `toplevel_close` (line 281)
- `deco_configure` (line 292) - *The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we draw our own titlebar; if server-side, we let it ...*
- `ptr_enter` (line 302) - *The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we draw our own titlebar; if server-side, we let it ...*
- `ptr_leave` (line 310)
- `ptr_motion` (line 313)
- `ptr_button` (line 320) - *ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); } static void ptr_leave(void *d, struct wl_point...*
- `ptr_axis` (line 342)
- `seat_caps` (line 364)
- `seat_name` (line 374)
- `registry_global` (line 380) - *ui_window *w = (ui_window *)data; fprintf(stderr, "[ui] seat caps: pointer=%s\n", (caps & WL_SEAT_CAPABILITY_POINTER) ? "yes" : "no"); if ((caps & ...*
- `registry_remove` (line 399)
- `ui_run_text_view` (line 407) - *w->seat = wl_registry_bind(reg, name, &wl_seat_interface, 1); wl_seat_add_listener(w->seat, &seat_listener, w); } else if (strcmp(iface, zxdg_decor...*

**Macros:**
- `_GNU_SOURCE` (line 9)
- `UI_FONT_SIZE` (line 25)
- `UI_MARGIN` (line 27)
- `UI_TITLEBAR_H` (line 28)
- `UI_BTN_W` (line 29)
- `UI_BTN_LEFT` (line 30)

**Structs:**
- `ui_window` (line 65)

#### `anti_fp.c`
**Path:** `src/anti_fp.c`

**Functions:**
- `fp_coarsen_time_ms` (line 16)
- `fp_user_agent` (line 22) - *#include "anti_fp.h"  /* --- clocks ---  uint64_t fp_timer_resolution_ms(void) { return FP_TIMER_RESOLUTION_MS; }  uint64_t fp_coarsen_time_ms(uint...*
- `fp_accept_language` (line 26)
- `fp_accept_language_header` (line 30)
- `fp_timezone` (line 34)
- `fp_platform` (line 38)
- `fp_vendor` (line 42)
- `fp_hardware_concurrency` (line 46)
- `fp_device_memory_gb` (line 50)
- `fp_bucket_screen` (line 56) - *const char *fp_vendor(void) { return ""; /* no vendor string: minimal entropy }  int fp_hardware_concurrency(void) { return 2; /* fixed: do not rev...*
- `splitmix64` (line 78) - *long best_area = -1; size_t best = smallest; for (size_t i = 0; i < n; ++i) { if (buckets[i][0] <= w && buckets[i][1] <= h) { long area = (long)buc...*
- `fp_perturb` (line 85)
- `fp_origin_key` (line 96)

#### `box_style.c`
**Path:** `src/box_style.c`

**Functions:**
- `lc` (line 23) - *Longest recognised tag is "blockquote" (10); longest display keyword is "inline-block" (12). The buffers are generous so a normal token always fits...*
- `is_ws` (line 27)
- `copy_lower_trim` (line 34) - *Copies in into out, trimming ASCII whitespace and lowercasing. Returns 0 on * success, -1 if in is NULL, the trimmed token is empty, or it does not...*
- `name_cmp` (line 47) - *Both row structs start with `const char *name`, so a pointer to a row is also a * pointer to its name field: one comparator serves both binary sear...*
- `bx_default_for_tag` (line 117) - *define TAG_N (sizeof TAG_TABLE / sizeof TAG_TABLE[0])*
- `bx_parse_display` (line 147) - *define DISP_N (sizeof DISP_TABLE / sizeof DISP_TABLE[0])*
- `bx_place` (line 157)
- `bx_display_name` (line 174)

**Macros:**
- `BX_TAG_MAX` (line 21)
- `BX_DISPLAY_MAX` (line 22)
- `BLOCK` (line 57)
- `INLINE` (line 59)
- `IBLOCK` (line 60)
- `LITEM` (line 61)
- `NONE` (line 62)
- `EDG` (line 63)
- `ZERO` (line 64)
- `TAG_N` (line 116)
- `DISP_N` (line 146)

**Structs:**
- `tag_row` (line 53) - *Both row structs start with `const char *name`, so a pointer to a row is also a * pointer to its name field: one comparator serves both binary sear...*
- `disp_row` (line 128) - *{ "ul",         { BLOCK,  EDG(1.0, 0.0, 1.0, 0.0), EDG(0.0, 0.0, 0.0, 2.5) } }, }; #define TAG_N (sizeof TAG_TABLE / sizeof TAG_TABLE[0])  bx_box b...*

#### `box_tree.c`
**Path:** `src/box_tree.c`

**Functions:**
- `layout_block` (line 32) - *Block container: stack non-none children vertically, collapsing each child's top * margin with the previous child's bottom margin.*
- `bt_nn` (line 53) - *if (cavail < 0.0) cavail = 0.0; bt_status r = layout_node(c, cavail, depth + 1); if (r != BT_OK) return r; double top_gap = (prev_bottom > c->margi...*
- `wrap_reverse` (line 73)
- `layout_grid` (line 192) - *Grid: equal columns via flex_layout, row-major placement, per-row max height. The column gap is always `gap`; the ROW gap is `row_gap` when has_row...*
- `layout_node` (line 232)
- `bt_layout` (line 277)
- `assign_doc_order` (line 318) - *Recursive doc_order assignment. The box tree is acyclic (each box has at most one parent_id), so the visited bitmap is just a guard against the deg...*
- `find_positioned_ancestor` (line 335) - *Walk the parent_id chain from `start` to find the nearest ancestor with position != STATIC. Returns the ancestor's index, or -1 if none exists (cal...*
- `resolve_inset` (line 349) - *Resolves an inset value: PV_LEN_UNSET or BT_LEN_AUTO → 0 (anchor at the * containing block's edge); otherwise the px value.*
- `bt_resolve_positioning` (line 353)

**Macros:**
- `BT_LEN_AUTO` (line 26)
- `BT_WRAP_EPS` (line 56)

#### `browser.c`
**Path:** `src/browser.c`

**Functions:**
- `free_page` (line 13) - *browser — pure navigation state for the Freedom GUI.  No I/O, no GUI toolkit. See spec/browser.md and include/browser.h.  define _POSIX_C_SOURCE 20...*
- `clear_status` (line 24) - *#include <stdlib.h> #include <string.h>  static void free_page(browser_state *bs) { if (bs == NULL) return; free(bs->page_title); bs->page_title = ...*
- `free_history` (line 28)
- `free_exceptions` (line 38)
- `is_https_url` (line 47)
- `is_local_path` (line 51)
- `url_is_allowed` (line 56)
- `xstrdup` (line 70)
- `utf8_seq_len` (line 82) - *UTF-8 sequence length implied by a lead byte, or 0 for a continuation byte or * an invalid lead.*
- `cp1252_to_ucs` (line 93) - *Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0.. 0xFF map identically to Latin-1; 0x80..0x9F carry the Windows-1252 g...*
- `utf8_encode` (line 107) - *Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the * byte count written.*
- `browser_init` (line 159)
- `browser_free` (line 170)
- `browser_set_url_bar` (line 181)
- `browser_commit_url_bar` (line 193)
- `browser_navigate` (line 198)
- `browser_back` (line 233)
- `browser_forward` (line 245)
- `browser_can_back` (line 257)
- `browser_can_forward` (line 261)
- `browser_current_url` (line 265)
- `browser_url_bar_selection` (line 270)
- `browser_url_bar_delete_selection` (line 281)
- `browser_url_bar_insert` (line 291)
- `browser_url_bar_backspace` (line 306)
- `browser_url_bar_delete` (line 320)
- `browser_url_bar_move_cursor` (line 331)
- `browser_url_bar_extend_cursor` (line 341)
- `browser_url_bar_set_cursor` (line 350)
- `browser_url_bar_select_all` (line 358)
- `browser_url_bar_clear` (line 365)
- `browser_set_page` (line 374)
- `browser_set_status` (line 396)
- `browser_status_text` (line 410)
- `host_equal` (line 418) - *if (n >= BROWSER_STATUS_MAX) n = BROWSER_STATUS_MAX - 1; memcpy(bs->status_msg, msg, n); bs->status_msg[n] = '\0'; bs->status_expiry_ms = now_ms + ...*
- `browser_is_exception` (line 429)
- `browser_add_exception` (line 437)

**Macros:**
- `_POSIX_C_SOURCE` (line 6)

#### `css.c`
**Path:** `src/css.c`

**Functions:**
- `parse_num` (line 133) - *Parses a leading non-negative number (digits + optional fraction). Returns 1 on * success, setting *out and *endp to the first unconsumed char.*
- `round_clamp` (line 153) - *Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the cast avoids undefined behaviour: casting an out-of-range double (e...*
- `interp_color` (line 160) - *Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the cast avoids undefined behaviour: casting an out-of-range double (e...*
- `interp_bg` (line 165)
- `interp_align` (line 192)
- `interp_fontsize` (line 200)
- `interp_lineheight` (line 227) - *line-height as a percent of the natural line box. A unitless multiplier ("1.5" -> 150) or a percent ("160%" -> 160); "normal" is unset (the UA defa...*
- `interp_weight` (line 239)
- `interp_style` (line 248)
- `interp_textdeco` (line 259) - *text-decoration / text-decoration-line: OR of the line keywords underline / overline / line-through found in the (space-separated) value. "none" ->...*
- `interp_display` (line 278)
- `interp_gap` (line 291) - *gap / grid-gap / column-gap: leading length as px (a two-value gap keeps the * first), "normal" -> 0; clamped to [0, CSS_GAP_MAX]. -1 when not a le...*
- `interp_justify` (line 298)
- `count_one_repeat` (line 321)
- `count_tracks` (line 351)
- `calc_skip_ws` (line 413)
- `calc_factor` (line 421) - *bare-number side; / requires a bare-number, non-zero divisor. A bare-number * *result* (e.g. calc(2 * 3), no length anywhere) is not a valid length...*
- `calc_term` (line 459) - *} if (p->i + 3 <= p->n && csel_lower_ch(p->s[p->i]) == 'r' && csel_lower_ch(p->s[p->i + 1]) == 'e' && csel_lower_ch(p->s[p->i + 2]) == 'm') { out->...*
- `calc_expr` (line 478)
- `calc_eval` (line 496) - *Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching ")" already stripped by the caller). Fails closed on any leftover/u...*
- `calc_unwrap` (line 509) - *True if s (already trimmed) is a "calc(...)" call spanning the whole string (case-insensitive keyword, balanced trailing paren); on success the arg...*
- `interp_len` (line 526) - *Parses one box-model length. Accepts "Npx", a bare "0", "Nem"/"Nrem" (x16 px, the engine's base font), "calc(...)" over the same units (+, -, *, /,...*
- `emit_len` (line 565) - *Emits one box length declaration for slot into dst (cap permitting). A negative value is rejected unless allow_neg (margins allow it; padding/width...*
- `interp_len` (line 581)
- `family_of` (line 639) - *Maps one font-family name (a generic keyword or a common family) to a generic css_font_family bucket; -1 if unrecognised. Case-insensitive; multi-w...*
- `interp_fontfamily` (line 664) - *font-family: the first recognised name in the comma-separated stack wins (its * generic bucket). Quotes are stripped. url() defensively dropped. -1...*
- `interp_texttransform` (line 685)
- `interp_valign` (line 707)
- `interp_whitespace` (line 714)
- `interp_tabsize` (line 725) - *if (csel_ci_eq(v, "super"))    return CSS_VA_SUPER; return -1;  /* top/middle/bottom/<length>: out of scope, fail closed }  static int interp_white...*
- `interp_textdeco_style` (line 736) - *}  /* tab-size: a non-negative integer (number of spaces). -1 if unsupported. static int interp_tabsize(const char *v) { double num; const char *en...*
- `interp_textdeco_thickness` (line 747) - *text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length * (px -> px, em/rem x16). -1 if unsupported (negative, %, etc -> dr...*
- `interp_aspect_ratio` (line 759) - *aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>` (auto fallback). Stores both numerator and denominator x1000 (for sub-...*
- `interp_direction` (line 792) - *num = round_clamp(nv * 1000.0, 1, CSS_LEN_MAX); den = round_clamp(dv * 1000.0, 1, CSS_LEN_MAX); return 1; } /* Bare number: treat as w/h = N/1 doub...*
- `liststyle_kw` (line 797)
- `interp_liststyle` (line 813) - *list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a list-style-image) is dropped: never f...*
- `emit_spacing` (line 842)
- `expand_shadow` (line 856) - *text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in any order. "none" emits an expl...*
- `interp_position` (line 887) - *} if (nlen < 2) return 0;  /* need both offsets int dx = lens[0], dy = lens[1]; if (dx > CSS_SHADOW_MAX) dx = CSS_SHADOW_MAX; if (dx < -CSS_SHADOW_...*
- `interp_boxsizing` (line 896)
- `interp_float` (line 902)
- `interp_clear` (line 909)
- `interp_visibility` (line 919) - *if (csel_ci_eq(v, "left"))  return CSS_FLOAT_LEFT; if (csel_ci_eq(v, "right")) return CSS_FLOAT_RIGHT; return -1; }  static int interp_clear(const ...*
- `interp_overflow` (line 926)
- `expand_overflow` (line 938) - *`overflow: X` sets both overflow-x and overflow-y to the same value. The two-token * per-axis form (`overflow: hidden visible`) is out of scope -- ...*
- `interp_cursor` (line 945)
- `interp_text_overflow` (line 961)
- `interp_word_break` (line 967)
- `interp_overflow_wrap` (line 974)
- `interp_border_collapse` (line 983) - *if (csel_ci_eq(v, "normal"))    return CSS_WB_NORMAL; if (csel_ci_eq(v, "break-all")) return CSS_WB_BREAK; if (csel_ci_eq(v, "keep-all"))  return C...*
- `number` (line 992)
- `interp_empty_cells` (line 1017) - *if (interp_len(tok, 0, &px) && px >= 0) { if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX; return px; } double num; const char *end; i...*
- `interp_caption_side` (line 1024) - *px = round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; }  /* empty-cells: show/hide. -1 unknown. static int interp_empty_cells(c...*
- `interp_table_layout` (line 1031) - *static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v, "hide")) return CSS_EC_HIDE; return...*
- `interp_font_variant` (line 1038) - *static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v, "bottom")) return CSS_CS_BOTTOM; ...*
- `interp_hyphens` (line 1046) - *if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; }  /* font-variant (subset: only small-...*
- `interp_user_select` (line 1054) - *if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail closed return -1; }  /* hyphens:...*
- `interp_caret_color` (line 1063) - *if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; }  /* user-select: none/text/all/auto. -1 unknown. static int interp_user_select(const ...*
- `interp_appearance` (line 1070) - *if (csel_ci_eq(v, "text")) return CSS_US_TEXT; if (csel_ci_eq(v, "all"))  return CSS_US_ALL; if (csel_ci_eq(v, "auto")) return CSS_US_AUTO; return ...*
- `interp_pointer_events` (line 1077) - *static int interp_caret_color(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO; cc_rgb c; return (cc_parse(v, &c) == CC_OK) ? cc_pac...*
- `interp_bg_repeat` (line 1084) - *static int interp_appearance(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_AP_AUTO; if (csel_ci_eq(v, "none")) return CSS_AP_NONE; return ...*
- `interp_bg_size` (line 1094) - *return -1; }  /* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. static int interp_bg_repeat(const char *v) { if (cs...*
- `interp_bg_clip` (line 1101) - *if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X; if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y; if (csel_ci_eq(v, "space"))     r...*
- `interp_bg_origin` (line 1109) - *if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if (csel_ci_eq(v, "contain")) return CSS_BGS...*
- `interp_bg_attachment` (line 1116) - *if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return CSS_BGC_PADDING_BOX; if (csel_ci_eq(v, "con...*
- `interp_isolation` (line 1123) - *static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if (csel_ci_eq(v, "border-box"))   retu...*
- `interp_contain` (line 1129) - */* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if (csel_ci_eq(v, "scroll")) return CSS_...*
- `interp_content_visibility` (line 1150) - *while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k ...*
- `interp_image_rendering` (line 1157) - *else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |= CSS_CONTAIN_STYLE; else if (csel_ci_eq(...*
- `interp_color_scheme` (line 1164) - *static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if (csel_ci_eq(v, "auto"))    return CSS...*
- `interp_accent_color` (line 1182) - *const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p ...*
- `interp_print_color_adjust` (line 1188) - *while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if (csel_ci_eq(tok, "light")) return CSS_CSH_LI...*
- `interp_forced_color_adjust` (line 1194) - *} /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int interp_accent_color(const char *v) { if (csel_ci_eq(v, "auto")) ...*
- `interp_mix_blend_mode` (line 1201) - */* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if (csel_ci_eq(v, "economy")) return CSS_PC...*
- `interp_object_fit` (line 1219) - *if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY; if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN; if (csel_ci_eq(v, "lighten"))   ...*
- `interp_list_style_pos` (line 1228) - *if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR; if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY; return -1; } /* object-fit: fi...*
- `interp_font_kerning` (line 1234) - *if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if (csel_ci_eq(v, "cover"))       ...*
- `interp_text_rendering` (line 1241) - */* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if (csel_ci_eq(v, "inside"))  return CSS_LP_I...*
- `interp_font_stretch` (line 1249) - *if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if (csel_ci_eq(v, "none"))   return CSS_FK_NONE...*
- `interp_resize` (line 1262) - */* font-stretch: normal/condensed/expanded/etc. -1 unknown. static int interp_font_stretch(const char *v) { if (csel_ci_eq(v, "normal"))           ...*
- `interp_scroll_behavior` (line 1270) - *if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))     return CSS_FS_EXTRA_EXPANDED; if (cs...*
- `interp_touch_action` (line 1276) - *static int interp_resize(const char *v) { if (csel_ci_eq(v, "none"))        return CSS_RS_NONE; if (csel_ci_eq(v, "both"))        return CSS_RS_BOT...*
- `interp_overscroll_behavior` (line 1283) - */* scroll-behavior: auto/smooth. -1 unknown. static int interp_scroll_behavior(const char *v) { if (csel_ci_eq(v, "auto"))   return CSS_SB_AUTO; if...*
- `interp_backface_visibility` (line 1290) - *static int interp_touch_action(const char *v) { if (csel_ci_eq(v, "auto"))         return CSS_TA_AUTO; if (csel_ci_eq(v, "none"))         return CS...*
- `interp_border_style` (line 1312)
- `interp_bwidth1` (line 1338)
- `interp_border_radius` (line 1346) - *border-radius: the first value only (corner-by-corner / elliptical out of scope). * px >= 0, or -1 (unsupported: %/units dropped -> stays unset).*
- `interp_bw_tok` (line 1360) - *static int interp_border_radius(const char *v) { char tok[CSS_TOK_MAX]; size_t k = 0; const char *p = v; while (*p == ' ' || *p == '\t') ++p; while...*
- `interp_bs_tok` (line 1361)
- `interp_bc_tok` (line 1362)
- `expand_outline` (line 1426)
- `expand_box_shadow` (line 1441) - *box-shadow (single layer): up to four lengths in order dx, dy, blur, spread, an optional color, and an optional `inset` keyword, in any order. Need...*
- `interp_flex_factor` (line 1470) - *flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to * [0, CSS_FLEX_FACTOR_MAX]. Negative / unparseable -> -1 (droppe...*
- `expand_flex` (line 1491) - *flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots. Keywords none/auto/initial; otherwise up to three values (a unitless number ...*
- `interp_align_kw` (line 1531) - *align-items / align-self / align-content / justify-items keyword. allow_auto is for * align-self; allow_dist (space-*) is for align-content. Unknow...*
- `interp_flex_direction` (line 1543)
- `interp_flex_wrap` (line 1551)
- `interp_grid_flow` (line 1560) - *if (csel_ci_eq(v, "row-reverse")) return CSS_FD_ROW_REVERSE; if (csel_ci_eq(v, "column")) return CSS_FD_COLUMN; if (csel_ci_eq(v, "column-reverse")...*
- `interp_grid_span` (line 1586) - *grid-column / grid-row: only the `span N` form is supported -> N (clamped to * [1, CSS_GRID_SPAN_MAX]). Line-number / named-line placement is out o...*
- `copy_trim` (line 1605) - *Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from * both ends. Returns the trimmed length, or SIZE_MAX if it does no...*
- `strip_important` (line 1618) - *Strips a trailing "!important" (case-insensitive, with optional whitespace before '!' and between '!' and the keyword) from val, in place. Returns ...*
- `var_append` (line 1699) - *} } i = v; continue; } } ++i; } }  static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap, size_t *o, const css_custom_p...*
- `value` (line 1726)
- `overflowed` (line 1786)
- `caller` (line 1799)
- `interpret_decls` (line 2046) - *Splits a ';'-separated declaration block into dst (up to cap). Returns count. tab/ntab is the custom-property table var() resolves against (NULL/0 ...*
- `add_rule` (line 2059) - *e.g. an inline style resolved against a NULL sheet). static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap, const css_cu...*
- `skip_at_rule` (line 2095) - *Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a * brace-balanced block. Returns the index just past it.*
- `block_end` (line 2111) - *Index just past the '}' that closes the block whose '{' is at s[open]. n if * unbalanced.*
- `trim_inplace` (line 2133) - *-- @media query evaluation (Hito 23b). All inputs are bounded substrings; the * query never fetches and unknown features fail closed (do not match)...*
- `copy_lower_trim` (line 2142) - *const char *e; return parse_num(v, &d, &e) ? round_clamp(d, 0, CSS_LEN_MAX) : 0; }  /* Trims ASCII spaces/tabs from both ends of a NUL-terminated s...*
- `media_part_matches` (line 2151) - *One media part: a type word ("screen"/"print"/"all") or a "(feature: value)". * p is already lowercased and trimmed. Unknown -> 0 (fail closed).*
- `media_segment_matches` (line 2180) - *One media query segment (between commas): an AND of parts. `not`/`or`/unknown * fail closed. An empty segment matches (all).*
- `media_matches` (line 2217) - *if (strcmp(buf, "and") == 0 || strcmp(buf, "only") == 0) { /* connector / legacy keyword: ignore } else if (strcmp(buf, "not") == 0 || strcmp(buf, ...*
- `at_is_media` (line 2231) - *static int media_matches(const char *s, size_t a, size_t b, const css_media *m) { while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s...*
- `parse_block` (line 2244) - *Parses rules in s[start,end). A matched @media block is descended into (bounded * depth); @import/@font-face/other @-rules and a non-matching @medi...*
- `strip_comments` (line 2286) - *Removes C-style block comments into a fresh NUL-terminated buffer (each comment * becomes one space). Caller frees.*
- `css_parse` (line 2304)
- `css_parse_media` (line 2308)
- `css_free` (line 2328)
- `apply_decl` (line 2338) - *Applies one declaration to the running style if it wins its property slot. The cascade is two-tiered: an !important declaration beats any non-impor...*
- `css_resolve_el` (line 2486)
- `css_resolve` (line 2606)
- `css_parse_inline` (line 2617)

**Macros:**
- `CSS_MAX_SELS` (line 34)
- `CSS_MAX_DECLS` (line 35)
- `CSS_MAX_RULES` (line 36)
- `CSS_SELS_PER_GROUP` (line 37)
- `CSS_INLINE_DECLS` (line 38)
- `CSS_INLINE_SPEC` (line 39)
- `CSS_MAX_CUSTOM_PROPS` (line 50)
- `CSS_VAR_MAX_DEPTH` (line 51)
- `CSS_CALC_MAX_DEPTH` (line 409)
- `CSS_MEDIA_TOK` (line 2122)
- `CSS_MEDIA_MAX_DEPTH` (line 2239)

**Structs:**
- `css_decl` (line 101)
- `css_custom_prop` (line 109) - *One custom property (--name: value), for var() lookups. Both fields are bounded * like every other token buffer here.*
- `css_sheet` (line 117) - *The selector types (css_attr_match/css_compound/css_sel) and their parser/matcher * live in css_select.{h,c}.*
- `calc_val` (line 411) - *-- calc() for length values -------------------------------------------------  A small recursive-descent evaluator over +, -, *, / and parens. Oper...*
- `calc_parser` (line 412)

#### `css_chain.c`
**Path:** `src/css_chain.c`

**Functions:**
- `fill_css_node` (line 35) - *Fills *node with element e's tag/id/class tokens (no style=, no parent link yet). * Over-long tokens are simply absent, which fails closed (does no...*
- `sibling_position` (line 116) - *Computes the 1-based index of n among its ELEMENT siblings and the total element-sibling count (both walks bounded, anti-DoS: past CCH_NTH_MAX the ...*
- `inputs` (line 139)
- `cch_element_matches` (line 195)

**Macros:**
- `CCH_TAG_MAX` (line 14)
- `CCH_ID_MAX` (line 15)
- `CCH_CLASS_BUF` (line 16)
- `CCH_MAX_CLASSES` (line 17)
- `CCH_MAX_ATTRS` (line 18)
- `CCH_ATTR_BUF` (line 19)

**Structs:**
- `cch_node` (line 23) - *One element's selector inputs (tag/id/classes) plus its css_element view, with * backing storage so the css_element pointers stay valid for the cha...*

#### `css_color.c`
**Path:** `src/css_color.c`

**Functions:**
- `ascii_lower` (line 108)
- `hex_val` (line 112)
- `normalize` (line 122) - *Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). * Returns 0, or -1 if the trimmed token is empty or does not fit.*
- `parse_hex` (line 136) - *static int normalize(const char *token, char *out) { size_t start = 0; while (token[start] == ' ' || token[start] == '\t') ++start; size_t end = st...*
- `parse_component` (line 162) - *Parses one rgb() component in [b, e). For a color channel, the value is an integer 0..255 or a percentage 0%..100% (rounded). For the alpha channel...*
- `parse_func` (line 196) - *v = v * 10 + (*p - '0'); if (v > 100000) return -1; } if (percent) { if (v > CC_PERCENT_MAX) return -1; out = (int)((v * CC_CHANNEL_MAX + CC_PERCEN...*
- `named_cmp` (line 230)
- `parse_named` (line 236)
- `cc_parse` (line 246)
- `cc_pack` (line 267)
- `cc_unpack` (line 271)

**Macros:**
- `CC_TOKEN_MAX` (line 18)
- `CC_CHANNEL_MAX` (line 21)
- `CC_PERCENT_MAX` (line 22)

**Structs:**
- `cc_named` (line 24) - *Largest CSS color token accepted. The longest named color ("lightgoldenrodyellow") is 20 bytes; functional rgba() with percentages fits * well unde...*

#### `css_select.c`
**Path:** `src/css_select.c`

**Functions:**
- `parse_attr_sel` (line 16) - *Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am. Advances *ip past the closing ']'. Returns 1 if supported, 0 (fai...*
- `parse_nth_arg` (line 73) - *Parses the An+B argument of the nth-child family, s[a,b) (surrounding space trimmed here). Accepts odd/even, N, An, An+B, An-B, n, -n+B, +n... (spa...*
- `parse_compound` (line 177) - *Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space) * into *cp. Returns 1 if supported (type, .class, #id, *, [attr], :...*
- `selector` (line 235)
- `el_attr_value` (line 302) - *The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no value reads as "".*
- `ends_with` (line 312) - *The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no value reads as "". static const cha...*
- `has_word` (line 320) - *True if `v` is a whitespace-separated list containing the word `w` (non-empty), * case-folded when ci (the `~=` operator).*
- `attr_matches` (line 335) - *size_t wl = strlen(w); if (wl == 0) return 0; const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' ||...*
- `nth_matches` (line 355) - *True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling position" and never matches (fail ...*
- `is_form_control` (line 364) - *True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling position" and never matches (fail ...*
- `compound_matches` (line 400) - *case PSEUDO_ONLY_CHILD:   return el->nth == 1 && el->nsib == 1; case PSEUDO_NTH_CHILD:    return nth_matches(pm->a, pm->b, el->nth); case PSEUDO_NT...*
- `sibling` (line 423)
- `csel_matches` (line 444)

#### `disk_store.c`
**Path:** `src/disk_store.c`

**Functions:**
- `write_full` (line 27) - *#include "disk_store.h"  #include "local_store.h"  #include <errno.h> #include <fcntl.h> #include <stdint.h> #include <stdio.h> #include <stdlib.h>...*
- `read_full` (line 38)
- `fsync_dir` (line 53) - *Best-effort fsync of the directory holding path, for crash durability of the * rename. Failures are non-fatal (some filesystems do not support it).*
- `map_ls` (line 70)
- `ds_write` (line 86) - *switch (s) { case LS_OK:            return DS_OK; case LS_ERR_NULL_ARG:  return DS_ERR_NULL_ARG; case LS_ERR_TOO_LARGE: return DS_ERR_TOO_LARGE; ca...*
- `ds_read` (line 122)
- `ds_free` (line 155)

**Macros:**
- `_POSIX_C_SOURCE` (line 10)

#### `dom.c`
**Path:** `src/dom.c`

**Functions:**
- `to_lower_buf` (line 32) - *#include <stdint.h> #include <stdlib.h> #include <string.h>  #include <lexbor/dom/dom.h> #include <lexbor/html/html.h>  /* --- small character help...*
- `fnv1a` (line 42)
- `ptr_hash` (line 51)
- `sm_entry_append` (line 76)
- `sm_grow` (line 88)
- `sm_put` (line 105)
- `sm_find` (line 132)
- `sm_free` (line 144)
- `pm_grow` (line 171)
- `pm_put` (line 188)
- `pm_get` (line 205)
- `pm_free` (line 216)
- `node_next` (line 238) - */* --- the index ---  struct dom_index { lxb_dom_node_t      **nodes;    /* arena: id -> element node, in document order size_t                coun...*
- `valid` (line 247)
- `index_element` (line 253) - *if (node->first_child != NULL) return node->first_child; while (node != root && node->next == NULL) { if (node->parent == NULL) return NULL; node =...*
- `dom_build` (line 289) - *}  size_t tlen = 0; const lxb_char_t *tag = lxb_dom_element_qualified_name(el, &tlen); if (tag != NULL && tlen > 0) { char lower[256]; if (to_lower...*
- `dom_free` (line 330)
- `dom_node_count` (line 342) - *return DOM_ERR_OOM; }  void dom_free(dom_index *idx) { if (idx == NULL) return; free(idx->nodes); sm_free(&idx->by_id); sm_free(&idx->by_tag); sm_f...*
- `dom_get_element_by_id` (line 346)
- `copy_ids` (line 352)
- `dom_get_by_tag` (line 359)
- `dom_get_by_class` (line 368)
- `id_of` (line 382) - *Max complex selectors in one comma-separated list. A longer list is truncated * (anti-DoS): the extra selectors are dropped, which only narrows mat...*
- `parse_selector_list` (line 392) - *Parses a selector list "a, b, c" into up to cap css_sel. Splits only on TOP-LEVEL commas (respecting [], () and quotes so `[a="x,y"]` and `:not(a,b...*
- `node_matches_any` (line 425) - *s.order = (int)n; s.rule = 0; out[n++] = s; } } start = i + 1; } break; default: break; } } return n; }  /* Nonzero iff element node `cn` matches a...*
- `count` (line 436)
- `dom_query_selector` (line 465)
- `dom_query_selector_all` (line 474)
- `dom_matches` (line 485)
- `dom_closest` (line 494)
- `dom_document_position` (line 510)
- `dom_precedes` (line 515)
- `dom_node_at` (line 520)
- `dom_parent` (line 525)
- `dom_first_child` (line 535)
- `dom_next_sibling` (line 543)
- `dom_tag_name` (line 551)
- `dom_get_attribute` (line 562)
- `dom_text_content` (line 575)
- `dom_document_title` (line 585)
- `dom_set_text_content` (line 598) - *}  const char *dom_document_title(const dom_index *idx, size_t *len) { if (len != NULL) *len = 0; if (idx == NULL || idx->document == NULL) return ...*
- `dom_set_document_title` (line 623)
- `idx_push` (line 635) - *return DOM_OK; }  dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) { if (idx == NULL || idx->document == NULL) retur...*
- `dom_create_element` (line 651)
- `dom_append_child` (line 671)
- `dom_remove_child` (line 685)
- `dom_set_attribute` (line 693)
- `dom_remove_attribute` (line 722)
- `index_subtree` (line 732) - *} } return DOM_OK; }  dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) { if (!valid(idx, node) || name == NULL) ...*
- `dom_set_inner_html` (line 741)

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `DOM_QS_MAX_SELECTORS` (line 379)

**Structs:**
- `sm_entry` (line 62) - *} return h; }  static size_t ptr_hash(const void *p) { uintptr_t x = (uintptr_t)p; x ^= x >> 33; x *= 0xff51afd7ed558ccdULL; x ^= x >> 33; return (...*
- `strmap` (line 71)
- `pm_entry` (line 160) - *for (size_t i = 0; i < m->cap; ++i) { if (m->buckets[i].used) { free(m->buckets[i].key); free(m->buckets[i].ids); } } free(m->buckets); m->buckets ...*
- `ptrmap` (line 166)
- `dom_index` (line 226) - *i = (i + 1) & mask; } return 0; }  static void pm_free(ptrmap *m) { free(m->buckets); m->buckets = NULL; m->cap = 0; m->size = 0; }  /* --- the ind...*

#### `dom_debug.c`
**Path:** `src/dom_debug.c`

**Functions:**
- `dd_putc` (line 30)
- `dd_emit` (line 35)
- `dd_puts` (line 39)
- `dd_printf` (line 48) - *Formats short fixed fields (ints, hex colours, fixed tokens) only; the variable hostile fields go through dd_field. Keeps `need` exact even on the ...*
- `dd_w` (line 80) - *A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the value.*
- `dd_color` (line 83) - *A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the value. static int dd_w(int v) {...*
- `dd_display_name` (line 87)
- `dd_justify_name` (line 95)
- `dd_align_name` (line 107)
- `dd_position_name` (line 117)
- `dd_visibility_name` (line 128)
- `dd_overflow_name` (line 136)
- `dd_cursor_name` (line 145)
- `dd_text_overflow_name` (line 162)
- `dd_inset` (line 168) - *case CSS_CUR_WAIT:        return "wait"; case CSS_CUR_CROSSHAIR:   return "crosshair"; case CSS_CUR_GRAB:        return "grab"; case CSS_CUR_ZOOM_I...*
- `dd_border_style_name` (line 171)
- `dd_box_line` (line 204)
- `dd_block_line` (line 235)
- `dd_format` (line 291)
- `dd_format_css` (line 324) - *}  dd_puts(&c, "[blocks]\n"); for (size_t i = 0; i < nblocks; ++i) { const rd_block *b = rd_at(doc, i); if (b != NULL) dd_block_line(&c, i, b); }  ...*

**Structs:**
- `dd_cursor` (line 24) - *Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the terminating NUL); `need` counts every byte that WOULD be writ...*

#### `download.c`
**Path:** `src/download.c`

**Functions:**
- `lc` (line 13) - *download — pure helpers for "save this resource to disk". See include/download.h and spec/download.md.   #include "download.h" #include "pdf_export...*
- `ci_find` (line 19) - *#include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer  #include <ctype.h> #include <string.h>  /* ASCII...*
- `media_type` (line 33) - *Writes the lowercased media type of content_type (the part before ';', with * surrounding spaces trimmed) into buf. Empty/NULL -> empty buf.*
- `dl_should_download` (line 46)
- `dl_ext_for_type` (line 57)
- `copy_span` (line 85) - *{ "application/xhtml+xml",  ".html" }, { "text/plain",            ".txt"  }, { "image/png",             ".png"  }, { "image/jpeg",            ".jpg...*
- `extract_disposition_name` (line 96) - *Extracts a filename candidate from a Content-Disposition value into buf. Handles filename="...", filename=..., and RFC 5987 filename*=charset''valu...*
- `extract_url_name` (line 134) - *Extracts the last path segment of url (without ?query or #fragment) into buf. * Returns 1 if a non-empty candidate was written.*
- `has_extension` (line 148) - *Does name already carry an extension (a '.' past the first byte with at least * one character after it)?*
- `dl_pick_name` (line 152)
- `dl_build_path` (line 194)
- `dl_check_size` (line 212)

#### `flex_layout.c`
**Path:** `src/flex_layout.c`

**Functions:**
- `nn` (line 18) - *No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers bounded by FX_MAX_ITEMS (no VLAs). The flex algorithm follows the ...*
- `fx_flex_line` (line 21)
- `fx_grid_columns` (line 126)
- `fx_float_pack` (line 142)
- `fx_grid_cell` (line 165)
- `fx_justify_name` (line 176)

**Macros:**
- `FX_EPS` (line 14)

#### `form.c`
**Path:** `src/form.c`

**Functions:**
- `put_char` (line 17) - *No I/O, no global state. The action/names/values are hostile data: encoded (application/x-www-form-urlencoded) and resolved through the canonical u...*
- `enc_component` (line 25) - *Encodes one component per the WHATWG application/x-www-form-urlencoded byte * serialiser. Returns -1 on overflow.*
- `fm_encode` (line 42)
- `copy_fit` (line 66) - *if (fields[i].name == NULL) continue; /* a nameless control is not submitted if (!first && put_char(out, outsz, &pos, '&') != 0) { out[0] = '\0'; r...*
- `clean_action` (line 75) - *Removes TAB/LF/CR and trims leading/trailing ASCII spaces (WHATWG cleaning of a * URL-bearing attribute). Returns -1 if the cleaned value does not ...*
- `strip_query` (line 93) - *if (c == '\t' || c == '\n' || c == '\r') continue; if (o + 1 >= outsz) return -1; out[o++] = c; } out[o] = '\0'; size_t s = 0, e = o; while (s < e ...*
- `resolve_target` (line 101) - *Resolves the cleaned action into a validated absolute https URL R, or returns a * block reason.*
- `fm_build` (line 119)

#### `freebug.c`
**Path:** `src/freebug.c`

**Functions:**
- `fb_buffer_init` (line 14) - *freebug — implementation of the pure, bounded console-log buffer.  Fail-closed at every cap: a push that would exceed FB_MAX_ENTRIES or FB_MAX_TOTA...*
- `fb_buffer_push` (line 18)
- `fb_buffer_push_loc` (line 22)
- `fb_buffer_reset` (line 75)
- `fb_buffer_free` (line 88)
- `fb_buffer_count` (line 98)
- `fb_buffer_at` (line 102)
- `fb_level_name` (line 107)

#### `freedom.c`
**Path:** `src/freedom.c`

**Functions:**
- `print_usage` (line 29) - *include "net_realm.h" include "render_doc.h" include "render_policy.h" include "secure_fetch.h" include "tab.h" include "ui.h" include <stdio.h> in...*
- `is_https_url` (line 48)
- `is_http_url` (line 52)
- `is_overlay_http` (line 58) - *fprintf(fp, "  --dump-dom: headless, print the paint-ready render tree (blocks, boxes, containers) to stdout\n"); fprintf(fp, "  --dump-css: headle...*
- `read_file` (line 114) - *When nonzero, the headless render runs the page's inline JS (tab_load_full run_js). * Set by --dump-console and by --js resolving to "on". Default ...*
- `is_blank_text` (line 132) - *long sz = ftell(f); if (sz < 0) { fclose(f); return NULL; } rewind(f);  char *buf = (char *)malloc((size_t)sz + 1); if (buf == NULL) { fclose(f); r...*
- `print_doc` (line 145) - *Writes the render document as deterministic, flowing plain text for a terminal and for an AI agent (content as data, never instruction). Inline run...*
- `print_console` (line 206) - *Prints the captured Freebug console (the developer-visible JS transcript) to stdout, one entry per line, prefixed with its level and (for located e...*
- `print_dom` (line 223) - *Prints the paint-ready render tree (dom_debug) to stdout. Two-pass: measure, then allocate exactly and format. The dump is bounded by the document;...*
- `print_dom_css` (line 237) - *Prints the CSS property inspector (dd_format_css) to stdout. Same contract as * print_dom: two-pass measure-then-allocate.*
- `headless_fetch` (line 260) - *tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page XHR/fetch and external <script src>. ctx is the page's top URL ...*
- `render_page` (line 305) - *out_nav (may be NULL): receives an owned copy of the JS-requested navigation target, if any. The tab layer already resolved and policy-gated it aga...*
- `sf_reason` (line 409)
- `fetch_and_render_one` (line 429) - *Fetches one url with secure_fetch and renders the result. The response body is * consumed directly; no extra copy is made. out_nav as in render_page.*
- `elsewhere` (line 471)
- `run_headless` (line 489)
- `main` (line 508)

**Macros:**
- `_POSIX_C_SOURCE` (line 8)
- `EXIT_OK` (line 25)
- `EXIT_ERROR` (line 27)
- `EXIT_USAGE` (line 28)
- `HL_JS_NAV_MAX` (line 425)

#### `hostblock.c`
**Path:** `src/hostblock.c`

**Functions:**
- `fnv1a` (line 33)
- `table_probe` (line 45) - *Finds the slot for key (length klen) in t, which must have a free slot. Returns * the index of either the matching entry or the first empty slot fo...*
- `table_grow` (line 56) - *Finds the slot for key (length klen) in t, which must have a free slot. Returns * the index of either the matching entry or the first empty slot fo...*
- `table_insert` (line 78) - *Inserts key (length klen) into t, deduping. Returns 0 (inserted or already * present), -1 on OOM.*
- `table_contains` (line 97)
- `table_free` (line 103)
- `lower` (line 112) - *static int table_contains(const hb_table *t, const char *key) { if (t->cap == 0) return 0; size_t i = table_probe(t, key, strlen(key)); return t->s...*
- `is_ip_token` (line 119) - *A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain. An empty token never reaches here.*
- `is_domain_char` (line 128) - *A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain. An empty token never reaches here. static int is_ip_token(con...*
- `hb_new` (line 149) - *token is not a domain we accept (caller skips it). static size_t normalise_domain(const char *tok, size_t n, char *out, size_t out_size) { if (n ==...*
- `hb_free` (line 154)
- `hb_load` (line 161)
- `hb_check` (line 198)
- `hb_is_allowlisted` (line 223)
- `hb_count` (line 243)

**Macros:**
- `HB_MAX_HOST` (line 17)
- `HB_INIT_CAP` (line 19)

**Structs:**
- `hb_table` (line 23) - *boundary.   #include "hostblock.h"  #include <stdint.h> #include <stdlib.h> #include <string.h>  #define HB_MAX_HOST   253u   /* longest domain we ...*
- `hb_set` (line 29)

#### `hostedit.c`
**Path:** `src/hostedit.c`

**Functions:**
- `he_lower` (line 11) - *hostedit — implementation: pure, I/O-free host-list line builder.  No allocation, no globals, no I/O. The hostile input (a hostname derived from th...*
- `is_label_char` (line 15)
- `valid_host` (line 22) - *#include "hostedit.h"  #include <string.h>  static char he_lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c; }  static int...*
- `he_make_line` (line 40)
- `is_ip_token` (line 67) - *True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostblock's is_ip_token spirit: such a leading token is...*
- `he_scan` (line 80) - *Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(ts, tl, ctx). If fn returns nonzero, iteration ...*
- `has_host_cb` (line 104)
- `he_text_has_host` (line 108)
- `contains_ci` (line 115) - *} return 0; }  static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts, ts + tl, (const char *)ctx); }  int he_text_...*
- `starts_with_ci` (line 127)
- `suggest_cb` (line 143)
- `he_suggest` (line 163)

**Structs:**
- `suggest_ctx` (line 136)

#### `html_parse.c`
**Path:** `src/html_parse.c`

**Functions:**
- `dup_bytes` (line 25) - *#include "html_parse.h"  #include <stdlib.h> #include <string.h>  #include <lexbor/html/html.h> #include <lexbor/dom/dom.h> #include <lexbor/tag/co...*
- `node_next` (line 35) - *lxb_html_document_t *doc; };  /* --- helpers ---  static char *dup_bytes(const lxb_char_t *src, size_t len) { char *out = (char *)malloc(len + 1); ...*
- `attr_is_event_handler` (line 44)
- `node_is_script` (line 51)
- `strip_scripts` (line 57)
- `mem_contains_ci` (line 84) - *Case-insensitive (ASCII) substring test over a length-delimited attribute value. * needle must be lowercase letters.*
- `script_classify` (line 108) - *Classifies a <script>: a classic program runs only when its type is absent/empty or a JavaScript MIME type (contains "javascript"/"ecmascript"). Ev...*
- `hp_extract_script_list` (line 137) - *Collects each executable <script> as its own entry, in document order: inline source for classic inline scripts, the raw src attribute for external...*
- `hp_free_scripts` (line 181)
- `attr_has_token_ci` (line 194) - *Whitespace-separated token test over a length-delimited attribute value, ASCII case-insensitive: rel="preload stylesheet" has the token "stylesheet...*
- `link_is_active_stylesheet` (line 215) - *An applicable stylesheet <link>: rel token "stylesheet" and not "alternate"; a non-empty href; media absent/empty or mentioning screen/all (fail cl...*
- `hp_extract_stylesheet_hrefs` (line 236)
- `hp_free_stylesheet_hrefs` (line 270)
- `strip_event_handlers` (line 276)
- `hp_config_default` (line 299) - *for (lxb_dom_attr_t *attr = lxb_dom_element_first_attribute(el); attr != NULL; attr = lxb_dom_element_next_attribute(attr)) { if (attr_is_event_han...*
- `hp_validate_input` (line 307)
- `hp_parse` (line 317) - *c.strip_scripts = 1; c.strip_event_handlers = 1; return c; }  hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg) { if ...*
- `hp_element_count` (line 351) - *if (local.strip_scripts) strip_scripts(document); if (local.strip_event_handlers) strip_event_handlers(document);  hp_document *wrap = (hp_document...*
- `hp_script_count` (line 361)
- `hp_event_handler_count` (line 371)
- `hp_extract_text` (line 387)
- `hp_get_title` (line 406)
- `hp_free` (line 421) - *char *hp_get_title(const hp_document *doc, size_t *out_len) { if (out_len != NULL) *out_len = 0; if (doc == NULL || doc->doc == NULL) return NULL; ...*
- `hp_document_free` (line 425)
- `hp_document_root` (line 431)

**Macros:**
- `_POSIX_C_SOURCE` (line 8)

**Structs:**
- `hp_document` (line 20) - *Sanitisation mutates the tree once in hp_parse; the query functions only read.  define _POSIX_C_SOURCE 200809L include "html_parse.h" include <stdl...*

#### `image_decode.c`
**Path:** `src/image_decode.c`

**Functions:**
- `read_be32` (line 38)
- `img_png_dimensions` (line 43)
- `img_dimensions_ok` (line 54)
- `img_fit` (line 62)
- `premultiply` (line 77) - *void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { if (out_w == NULL || out_h == NULL) return; out_...*
- `img_decode_png` (line 88)
- `jpeg_error_longjmp` (line 144)
- `jpeg_silence` (line 151) - *libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE) without tearing the worker down. s...*
- `img_decode_jpeg` (line 152)
- `img_decode` (line 233)
- `img_pixels_free` (line 244)
- `img_format_name` (line 253)

**Macros:**
- `PNG_IHDR_MIN` (line 28)

**Structs:**
- `jpeg_err_ctx` (line 140) - *libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE) without tearing the worker down.*

#### `js_dom.c`
**Path:** `src/js_dom.c`

**Functions:**
- `jd_opaque_get` (line 23) - *define _POSIX_C_SOURCE 200809L include "js_dom.h" include "dom.h" include "freebug.h" include "js_sandbox.h" include <stdint.h> include <stdlib.h> ...*
- `jd_idx` (line 27)
- `jd_handle` (line 37) - *Coerces a JS argument to a node handle. Returns -1 with a pending exception if coercion threw; otherwise stores the handle (out-of-range values sta...*
- `jd_handle_or_null` (line 43)
- `m_node_count` (line 49) - *if coercion threw; otherwise stores the handle (out-of-range values stay * out of range and are rejected later by the dom validators). static int j...*
- `m_get_element_by_id` (line 55)
- `jd_query_list` (line 67) - *return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx))); }  static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val, int arg...*
- `m_get_by_tag` (line 96)
- `m_get_by_class` (line 102)
- `m_tag_name` (line 108)
- `m_get_attribute` (line 118)
- `m_parent` (line 131)
- `m_first_child` (line 139)
- `m_next_sibling` (line 147)
- `m_precedes` (line 155)
- `m_text_content` (line 166) - *if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return jd_handle_or_null(ctx, dom_next_sibling(jd_idx(ctx), h)); }  static JSValue m_prec...*
- `m_set_text` (line 176)
- `m_get_title` (line 190)
- `m_set_title` (line 198)
- `m_create_element` (line 211) - *}  static JSValue m_set_title(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; size_t len = 0; co...*
- `m_append_child` (line 223)
- `m_remove_child` (line 232)
- `m_set_attribute` (line 241)
- `m_remove_attribute` (line 257)
- `m_set_inner_html` (line 269)
- `m_register_click` (line 291)
- `m_query_selector` (line 317) - *JS_FreeValue(ctx, reg); reg = JS_NewObject(ctx); if (JS_IsException(reg)) { JS_FreeValue(ctx, global); return JS_EXCEPTION; } JS_SetPropertyStr(ctx...*
- `m_query_selector_all` (line 330) - */* dom.querySelector(root, sel): root is a handle or -1 for document scope. static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val, ...*
- `m_matches` (line 358)
- `m_closest` (line 370)
- `js_env` (line 650)
- `jd_lp_set` (line 822) - *Defines a string property on the __locParts data object from a (ptr,len) span. * The span is copied into an engine string; a NULL span becomes "".*
- `jd_install` (line 863)
- `fails` (line 924)
- `jd_install_console` (line 981)
- `jd_set_location` (line 1017)
- `jd_take_nav_request` (line 1051)
- `jd_pack_ptr` (line 1094) - *Carry the host fetch fn + its ctx as a function's closure data, each split into 32-bit halves (no assumption about JS number width). The data lives...*
- `jd_unpack_ptr` (line 1099)
- `m_host_fetch` (line 1112) - *__hostFetch(method, url, body) -> { status, body, contentType }. The ONLY network primitive exposed to script; it does NOT touch a socket -- it cal...*
- `jd_install_xhr` (line 1191)
- `jd_click_state_new` (line 1221)
- `jd_click_state_free` (line 1226)
- `jd_install_events` (line 1230)
- `jd_fire_click` (line 1241)

**Macros:**
- `_POSIX_C_SOURCE` (line 9)

**Structs:**
- `jd_method` (line 286) - *(void)this_val; (void)argc; dom_node_id h; if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; size_t len = 0; const char *s = JS_ToCStringLe...*
- `jd_click_state` (line 1218) - *JSValue global = JS_GetGlobalObject(jsctx); if (JS_IsException(global)) { JS_FreeValue(jsctx, hf); return JD_ERR_OOM; } JS_SetPropertyStr(jsctx, gl...*

#### `js_env.c`
**Path:** `src/js_env.c`

**Functions:**
- `wall_clock_ms` (line 32) - *#include "js_env.h"  #include "anti_fp.h" #include "js_sandbox.h"  #include <stdint.h> #include <stdlib.h> #include <string.h> #include <time.h>  #...*
- `monotonic_ms` (line 38)
- `m_date_now` (line 46) - *static uint64_t wall_clock_ms(void) { struct timespec ts; if (clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0; return (uint64_t)ts.tv_sec * 1000u...*
- `m_perf_now` (line 55) - *performance.now: coarsened elapsed since the origin bound at install time, so * it never leaks the host uptime.*
- `m_empty_array` (line 74)
- `def_val` (line 86) - *Always takes ownership of v: JS_DefinePropertyValueStr consumes it (freeing it even when the define fails). An exception value is an immediate with...*
- `def_str` (line 91)
- `def_int` (line 95)
- `build_languages` (line 102) - *navigator.languages: a sealed array built by splitting fp_accept_language() * (e.g. "en-US,en") on commas. Returns an exception value on OOM.*
- `build_navigator` (line 125)
- `build_screen` (line 148)
- `def_fn` (line 180) - *define PERF_ORIGIN_EPOCH 1700000000000.0*
- `build_perf_timing` (line 185)
- `build_perf_navigation` (line 199)
- `build_performance` (line 211)
- `override_date_now` (line 244) - *Replaces the built-in Date.now with the coarsened version, non-writable and * non-configurable so a script cannot restore a high-resolution clock.*
- `make_readback` (line 287)
- `build_readback_obj` (line 295)
- `je_install` (line 308)
- `je_install_canvas` (line 326)

**Macros:**
- `_POSIX_C_SOURCE` (line 16)
- `PERF_ORIGIN_EPOCH` (line 179)

#### `js_policy.c`
**Path:** `src/js_policy.c`

**Functions:**
- `eq_ci` (line 12) - *js_policy — implementation: pure per-host JavaScript policy decision.  No I/O, no global state. Fail-closed: an unknown mode never enables JS.   #i...*
- `jsp_enabled` (line 21)
- `jsp_mode_from_str` (line 30)
- `jsp_mode_str` (line 42)

#### `js_sandbox.c`
**Path:** `src/js_sandbox.c`

**Functions:**
- `jm_malloc` (line 44) - *int    hit; /* sticky within one eval: an allocation was denied by the cap } js_mem_state;  struct js_context { JSRuntime      *rt; JSContext      ...*
- `jm_calloc` (line 52)
- `jm_free` (line 62)
- `jm_realloc` (line 68)
- `jm_usable_size` (line 78)
- `host_dup` (line 88) - *if (p == NULL && size != 0) return NULL; /* original ptr left untouched m->used = m->used - old + ((p != NULL) ? malloc_usable_size(p) : 0); return...*
- `timespec_reached` (line 96)
- `js_interrupt_cb` (line 103) - *static char *host_dup(const char *src, size_t len) { char *out = (char *)malloc(len + 1); if (out == NULL) return NULL; if (len != 0 && src != NULL...*
- `is_ascii_digit` (line 115)
- `js_loc_from_stack` (line 117)
- `js_limits_default` (line 235) - *if (out_col  != NULL) *out_col  = cl; } JS_FreeCString(ctx, ss); } else { JS_FreeValue(ctx, JS_GetException(ctx)); /* ToCString may have thrown } }...*
- `limits_resolve` (line 244)
- `js_validate_source` (line 253)
- `js_context_new` (line 264) - *if (l.time_budget_ms == 0)     l.time_budget_ms     = JS_DEFAULT_TIME_BUDGET; return l; }  js_status js_validate_source(const char *src, size_t len...*
- `js_context_free` (line 303)
- `arm_deadline` (line 312) - *c->has_deadline = 0; c->interrupted = 0; out = c; return JS_OK; }  void js_context_free(js_context *ctx) { if (ctx == NULL) return; if (ctx->ctx !=...*
- `js_set_time_budget` (line 327)
- `js_eval` (line 332)
- `js_eval_named` (line 336)
- `js_pump_jobs` (line 419)
- `js_eval_once` (line 437)
- `js_result_free` (line 450)
- `js_context_raw` (line 463)

**Macros:**
- `_POSIX_C_SOURCE` (line 11)

**Structs:**
- `js_mem_state` (line 27) - *We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs *inside* QuickJS before our allocator and is therefore unobservable)...*
- `js_context` (line 33)

#### `link_nav.c`
**Path:** `src/link_nav.c`

**Functions:**
- `clean_href` (line 19) - *Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out. Returns 0, or -1 if the href does not fit in out.*
- `ci_prefix` (line 38) - *if (o + 1 >= outsz) return -1; out[o++] = (char)c; } out[o] = '\0';  size_t start = 0; while (out[start] == ' ') ++start; if (start > 0) memmove(ou...*
- `classify_block` (line 62) - *Splits the fragment (everything after the first '#') out of ref: copies the fragment id (without '#') into frag, then truncates ref at the '#'. A f...*
- `file_dir_len` (line 69) - *const char *f = hash + 1; size_t fl = strlen(f); if (fl + 1 <= fragsz) memcpy(frag, f, fl + 1); hash = '\0'; }  /* Classifies why a fragment-less r...*
- `last_seg_is_dotdot` (line 79) - *return LN_BLOCK_UNSUPPORTED; }  /* Length of base up to and including the last '/'; 0 when base has no '/'. static size_t file_dir_len(const char *...*
- `append_seg` (line 86) - *for (size_t i = 0; base[i] != '\0'; ++i) { if (base[i] == '/') { last = i; found = 1; } } return found ? last + 1 : 0; }  /* Nonzero iff the last s...*
- `pop_seg` (line 98) - */* Appends seg to body (with a '/' separator when non-empty). 0, or -1 on overflow. static int append_seg(char *body, size_t bodysz, size_t *blen, ...*
- `resolve_file` (line 149) - *Resolves a local file reference (relative or absolute path) against base into * out. The fragment (#...) is dropped. Returns 0, or -1 on overflow/e...*
- `ln_resolve` (line 171)
- `ln_block_reason_text` (line 240)

#### `local_store.c`
**Path:** `src/local_store.c`

**Functions:**
- `cipher_for` (line 319) - *#define LS_ARGON2_M_KIB  19456u  /* memory cost in KiB (19 MiB) #define LS_ARGON2_P      1u      /* lanes / parallelism  /* Container field offsets...*
- `argon2id_derive` (line 329) - *static const uint8_t LS_MAGIC[4] = { 'F', 'R', 'Z', 'S' };  /* --- AEAD selection ---  static const EVP_CIPHER *cipher_for(ls_aead aead) { switch (...*
- `ls_derive_key` (line 358)
- `aead_encrypt` (line 367) - *int rc = EVP_KDF_derive(kctx, out, out_len, params); EVP_KDF_CTX_free(kctx); return (rc == 1) ? LS_OK : LS_ERR_KDF; }  ls_status ls_derive_key(cons...*
- `aead_decrypt` (line 393)
- `seal_core` (line 421) - *if (aad_len > 0 && EVP_DecryptUpdate(ctx, NULL, &len, aad, (int)aad_len) != 1) goto done; if (ct_len > 0) { if (EVP_DecryptUpdate(ctx, pt, &len, ct...*
- `decrypt_blob` (line 458)
- `ls_seal` (line 489) - *if (pt == NULL) return LS_ERR_OOM;  ls_status st = aead_decrypt(cipher, key, nonce, blob, LS_HEADER_LEN, ct, ct_len, tag, pt); if (st != LS_OK) { O...*
- `ls_open` (line 502)
- `ls_seal_passphrase` (line 513) - *memset(salt, 0, sizeof salt); /* unused under kdf_id = none return seal_core(key, aead, LS_KDF_NONE, salt, plaintext, pt_len, out, out_len); }  ls_...*
- `ls_open_passphrase` (line 534)
- `ls_free` (line 554)

**Macros:**
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 3)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 6)
- `OSSL_KDF_PARAM_THREADS` (line 9)
- `_GNU_SOURCE` (line 11)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 14)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 17)
- `OSSL_KDF_PARAM_THREADS` (line 20)
- `_GNU_SOURCE` (line 22)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 25)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 28)
- `OSSL_KDF_PARAM_THREADS` (line 31)
- `_GNU_SOURCE` (line 33)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 36)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 39)
- `OSSL_KDF_PARAM_THREADS` (line 42)
- `_GNU_SOURCE` (line 44)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 47)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 50)
- `OSSL_KDF_PARAM_THREADS` (line 53)
- `_GNU_SOURCE` (line 55)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 58)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 61)
- `OSSL_KDF_PARAM_THREADS` (line 64)
- `_GNU_SOURCE` (line 66)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 69)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 72)
- `OSSL_KDF_PARAM_THREADS` (line 75)
- `_GNU_SOURCE` (line 77)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 80)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 83)
- `OSSL_KDF_PARAM_THREADS` (line 86)
- `_GNU_SOURCE` (line 88)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 91)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 94)
- `OSSL_KDF_PARAM_THREADS` (line 97)
- `_GNU_SOURCE` (line 99)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 102)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 105)
- `OSSL_KDF_PARAM_THREADS` (line 108)
- `_GNU_SOURCE` (line 110)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 113)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 116)
- `OSSL_KDF_PARAM_THREADS` (line 119)
- `_GNU_SOURCE` (line 121)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 124)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 127)
- `OSSL_KDF_PARAM_THREADS` (line 130)
- `_GNU_SOURCE` (line 132)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 135)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 138)
- `OSSL_KDF_PARAM_THREADS` (line 141)
- `_GNU_SOURCE` (line 143)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 146)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 149)
- `OSSL_KDF_PARAM_THREADS` (line 152)
- `_GNU_SOURCE` (line 154)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 157)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 160)
- `OSSL_KDF_PARAM_THREADS` (line 163)
- `_GNU_SOURCE` (line 165)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 168)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 171)
- `OSSL_KDF_PARAM_THREADS` (line 174)
- `_GNU_SOURCE` (line 176)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 179)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 182)
- `OSSL_KDF_PARAM_THREADS` (line 185)
- `_GNU_SOURCE` (line 187)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 190)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 193)
- `OSSL_KDF_PARAM_THREADS` (line 196)
- `_GNU_SOURCE` (line 198)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 201)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 204)
- `OSSL_KDF_PARAM_THREADS` (line 207)
- `_GNU_SOURCE` (line 209)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 212)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 215)
- `OSSL_KDF_PARAM_THREADS` (line 218)
- `_GNU_SOURCE` (line 220)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 223)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 226)
- `OSSL_KDF_PARAM_THREADS` (line 229)
- `_GNU_SOURCE` (line 231)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 234)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 237)
- `OSSL_KDF_PARAM_THREADS` (line 240)
- `_GNU_SOURCE` (line 242)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 245)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 248)
- `OSSL_KDF_PARAM_THREADS` (line 251)
- `_GNU_SOURCE` (line 253)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 256)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 259)
- `OSSL_KDF_PARAM_THREADS` (line 262)
- `_GNU_SOURCE` (line 264)
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 267)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 270)
- `OSSL_KDF_PARAM_THREADS` (line 273)
- `_GNU_SOURCE` (line 275)
- `LS_VERSION` (line 298)
- `LS_KDF_NONE` (line 300)
- `LS_KDF_ARGON2ID` (line 301)
- `LS_ARGON2_T` (line 304)
- `LS_ARGON2_M_KIB` (line 305)
- `LS_ARGON2_P` (line 306)
- `OFF_MAGIC` (line 309)
- `OFF_VERSION` (line 310)
- `OFF_AEAD` (line 311)
- `OFF_KDF` (line 312)
- `OFF_SALT` (line 313)
- `OFF_NONCE` (line 314)

#### `net_realm.c`
**Path:** `src/net_realm.c`

**Functions:**
- `lower` (line 16) - *net_realm — implementation: pure realm classification and routing.  No I/O, no global state, no allocation. Classification is a case-insensitive fi...*
- `ends_with_realm` (line 23) - *True if the lowercased host (length n) ends with ".suffix" AND has at least one * non-empty label before the dot. suffix is given without its leadi...*
- `nr_classify_host` (line 33)
- `host_of` (line 52) - *Extracts the host of scheme://host[:port][/...] into out (lowercased not required * here; nr_classify_host lowercases). Returns 0 on success, -1 if...*
- `nr_classify_url` (line 67)
- `nr_route_for` (line 73)
- `nr_realm_allows_http` (line 87)
- `nr_realm_name` (line 93)
- `nr_route_name` (line 102)

**Macros:**
- `NR_MAX_HOST` (line 14)

#### `os_sandbox.c`
**Path:** `src/os_sandbox.c`

**Functions:**
- `os_policy_allows` (line 51) - *define OS_ALLOWED_N (sizeof os_allowed / sizeof os_allowed[0])*
- `os_policy_size` (line 58)
- `os_prot_allowed` (line 65) - *W^X mirror: mmap/mprotect keep their membership but lose any request that asks * for executable memory. The single source of truth the BPF prot-che...*
- `os_no_dump` (line 75) - *Anti-dump defense in depth: undumpable + no core file, so neither a crash nor a foreign ptrace can exfiltrate worker secrets. Best-effort; call bef...*
- `excluded` (line 89)
- `os_isolate_namespaces` (line 93)
- `os_policy_allows` (line 105) - *Unprivileged user namespaces disabled (EPERM) or unsupported kernel * (EINVAL/ENOSYS): not fatal -- seccomp remains the mandatory boundary. return ...*
- `os_policy_size` (line 107)
- `os_prot_allowed` (line 108)
- `os_no_dump` (line 111)
- `os_harden` (line 112)
- `os_namespace_flags` (line 114)
- `os_isolate_namespaces` (line 116)
- `os_harden` (line 144) - *The native ABI token the BPF arch guard pins to (rejects x32/i386 on x86_64 and * AArch32 on aarch64 -- syscall-ABI-confusion defence). if defined(...*
- `ll_create_ruleset` (line 238) - */* --- Landlock filesystem confinement (architecture-independent) --- if defined(__linux__) && defined(__NR_landlock_create_ruleset) include <errno...*
- `ll_add_rule` (line 243)
- `ll_restrict_self` (line 248)
- `ll_handled` (line 265) - *The set of FS rights the ruleset handles, masked to what this ABI supports so * landlock_create_ruleset does not fail with EINVAL on older kernels.*
- `ll_read_access` (line 278)
- `os_landlock_abi` (line 284)
- `os_landlock_restrict` (line 290)
- `os_landlock_abi` (line 330) - *pb.parent_fd = pfd; long rc = ll_add_rule(rfd, LANDLOCK_RULE_PATH_BENEATH, &pb, 0); close(pfd); if (rc != 0) { close(rfd); return OS_ERR_LANDLOCK; ...*
- `os_landlock_restrict` (line 332)

**Macros:**
- `_GNU_SOURCE` (line 12)
- `OS_ALLOWED_N` (line 49)
- `OS_SECCOMP_ARCH` (line 140)
- `OS_SECCOMP_ARCH` (line 142)
- `LL_FS_BASE` (line 254)

#### `page_view.c`
**Path:** `src/page_view.c`

**Functions:**
- `input` (line 39)
- `cp1252_to_ucs` (line 54) - *Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0.. 0xFF map identically to Latin-1 (code point == byte). 0x80..0x9F car...*
- `utf8_encode` (line 68) - *Encodes a BMP scalar (<= 0xFFFF, which covers all Windows-1252 targets) as * UTF-8 into out (up to 3 bytes); returns the byte count written.*
- `utf8_sanitized_dup` (line 80)
- `dup_n` (line 112)
- `run_init_common` (line 126) - *Common field initialization shared by all append helpers. Keeps the three constructors DRY and guarantees every run starts from the same sentinel s...*
- `pv_node_map_init` (line 208)
- `pv_node_map_free` (line 216)
- `pv_node_map_build` (line 253) - *Builds a document-order map of all element nodes under root. Returns 0, or -1 on * allocation failure.*
- `pv_new` (line 261)
- `pv_append` (line 265)
- `pv_append_image` (line 298)
- `pv_append_input` (line 327)
- `pv_set_emphasis` (line 367)
- `pv_set_indent` (line 374)
- `pv_set_color` (line 379)
- `pv_set_bgcolor` (line 384)
- `pv_set_text_style` (line 389)
- `pv_set_text_ext` (line 399)
- `pv_set_container` (line 430)
- `pv_set_flex` (line 445)
- `pv_set_cont_item` (line 457)
- `pv_set_float` (line 462)
- `pv_set_box` (line 470)
- `pv_set_node_id` (line 482)
- `pv_set_block_id` (line 487)
- `pv_add_box_def` (line 492)
- `pv_free` (line 505)
- `pv_count` (line 519)
- `pv_at` (line 523)
- `pv_box_count` (line 528)
- `pv_box_at` (line 532)
- `node_next` (line 541) - *}  size_t pv_box_count(const pv_view *v) { return (v != NULL) ? v->nbox : 0; }  const pv_box_def *pv_box_at(const pv_view *v, size_t i) { if (v == ...*
- `is_block_tag` (line 550)
- `heading_level` (line 568)
- `is_skipped_tag` (line 580)
- `node_tag` (line 590)
- `in_skipped_subtree` (line 599) - *Nonzero if any ancestor up to base is a non-rendered container. When js_enabled, a <noscript> ancestor also suppresses content (the script would ru...*
- `font_color_attr` (line 632)
- `bgcolor_attr` (line 639) - *Legacy bgcolor attribute (body/table/tr/td), the background twin of <font * color>: pre-CSS sites (Hacker News' orange bar and beige page) still us...*
- `item_ordinal` (line 682) - *Ordinal for a run of container `cid` whose direct-child item is `item` (NULL = * anonymous: every such run is its own item). -1 when the run has no...*
- `pv_text_ext_reset` (line 725) - *2026-07-10 batch: tab_size (0 unset -> 8), direction (CSS text direction, not flex-direction), font_variant (small-caps), list_style_pos (inside/ou...*
- `pv_text_ext_merge` (line 740) - *Merges one ancestor's resolved css_style into ext, nearest ancestor first (a field * already set is not overwritten — keeps the nearest, matching i...*
- `css_has_hbox` (line 773) - *if (e->word_break == 0 && cs->word_break != CSS_WB_UNSET) e->word_break = cs->word_break; if (e->text_decoration_color == -1 && cs->text_decoration...*
- `css_hbox_resolve` (line 783) - *Pre-resolves the horizontal box (px) into a run's wire fields: l/r insets = padding + non-auto margin of each side (clamped >= 0); w = the tightest...*
- `css_has_position` (line 803) - *A real (non-static) position makes a block box-carrying too, so its position/insets/ * z-index ride the box-def tree (painted for relative; carried...*
- `css_has_boxdeco` (line 807)
- `container_id` (line 834) - *Document-order registry of flex/grid container nodes, so the runs of one * container share a stable id. typedef struct pv_container_reg { const lxb...*
- `boxdef_from_style` (line 854) - *Fills *d (decoration + hbox + bg; parent_id defaults to -1) from a resolved style. Padding unset -> 0 (geometry default); the rest keep the css mod...*
- `box_reg_id` (line 898) - *Id of node in the box registry, recording its decoration on first sight. -1 when * full. The parent link is stamped separately as the ancestor walk...*
- `pv_style_cache_init` (line 924)
- `pv_style_cache_free` (line 937)
- `cached_element_style` (line 946) - *cch_element_style(el, sheet), memoized in *cache. A NULL cache (OOM at init, or a caller that opts out) simply calls through uncached -- never a ha...*
- `css_to_fx_justify` (line 975) - *Maps a css_justify (resolved by the css cascade) to a flex_layout fx_justify. * Unset / start / unknown all fall to FX_JUSTIFY_START (the default).*
- `is_bold_tag` (line 990) - *Inline emphasis carried by a tag: bold from <b>/<strong>/<th>, italic from * <i>/<em>. <th> is a header cell, conventionally bold.*
- `is_italic_tag` (line 993)
- `resolve_context` (line 1012) - *level, nearest block-level ancestor (defaults to base), the inherited author color (nearest ancestor that sets one, packed 0xRRGGBB, or -1), the au...*
- `collapse_ws` (line 1188) - *prev_grow = cs.flex_grow; prev_shrink = cs.flex_shrink; prev_basis = cs.flex_basis; prev_order = cs.order; prev_align_self = cs.align_self; have_pr...*
- `parse_dim` (line 1211) - *Parses the leading non-negative integer of an HTML length attribute value (e.g. "640", "640px", "50%"). Returns the value clamped to a sane bound, ...*
- `find_body` (line 1223)
- `forms_free` (line 1246)
- `ascii_ieq` (line 1254) - *} form_rec;  typedef struct form_table { form_rec *recs; size_t    count, cap; } form_table;  static void forms_free(form_table *ft) { for (size_t ...*
- `attr_dup` (line 1266) - *Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent. A present-but-empty attribute yields a "" string (distingu...*
- `forms_add` (line 1275) - *Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent. A present-but-empty attribute yields a "" string (distingu...*
- `form_for` (line 1295) - *} lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node); char *method = attr_dup(el, "method", 6); int m = ascii_ieq(method, "p...*
- `under_unrendered` (line 1311) - *Nonzero if a descendant text node sits under a non-rendered element (a <style> or <script> nested in the collected subtree -- with run_js the parse...*
- `collect_text` (line 1324) - *Concatenates the descendant text of el into an owned NUL-terminated string (the value of a <textarea> / the label of a <button> / a flattened table...*
- `classify_input` (line 1347)
- `describe_control` (line 1364) - *Fills owned label/name/value for a control element and its classified type. * Returns 0, or -1 on OOM (caller frees whatever is non-NULL).*
- `li_ordinal` (line 1426) - *1-based position of an <li> among its <li> siblings (an <ol> counter, basic: the `start`/`value` attributes are out of scope). Counts preceding ele...*
- `roman_marker` (line 1452) - *int k = 0; if (n < 1) n = 1; while (n > 0 && k < (int)sizeof buf) { int r = (n - 1) % 26; buf[k++] = (char)((upper ? 'A' : 'a') + r); n = (n - 1) /...*
- `list_marker` (line 1477) - *Builds the list marker for the first run of an <li>. With no author list-style (CSS_LS_UNSET) it is the UA default: "N. " for an ordered list, "* "...*
- `nearest_table` (line 1497) - *case CSS_LS_CIRCLE:      snprintf(out, cap, "\xE2\x97\xA6 "); return; /* U+25E6 white bullet case CSS_LS_SQUARE:      snprintf(out, cap, "\xE2\x96\...*
- `cell_has_nested_table` (line 1522) - *Nonzero if cell has a descendant <table>: it is then a structural CONTAINER, not a leaf cell. Only leaf cells (no nested table) are collected as on...*
- `next_skip` (line 1531) - *Pre-order successor that does NOT descend into n's children (used to skip an * already-decided subtree during the table scan).*
- `cell_anchors` (line 1542) - *First <a href> element in the cell's subtree, with *count receiving how many * such anchors exist, capped at 2 (only none / exactly-one / several m...*
- `links` (line 1560)
- `flow_table` (line 1591)
- `table` (line 1607)
- `collect_style_text` (line 1654) - *Concatenates the text of every <style> element in the document (head included) into one owned, NUL-terminated buffer, capped at PV_MAX_STYLE_BYTES....*
- `in_hidden_subtree` (line 1688) - *Nonzero if n or any ancestor up to base has display:none (from the <style> sheet or its inline style=). display:none is structural visibility, appl...*
- `in_boilerplate_subtree` (line 1703) - *Nonzero if n or any ancestor up to base is page boilerplate (<nav>/<header>/ <footer>/<aside>). Used only in distraction-free (reader) mode to drop...*
- `pv_build` (line 1714)
- `pv_build_ex` (line 1718)
- `pv_build_full` (line 1722)
- `pv_build_styled` (line 1727)

**Macros:**
- `_POSIX_C_SOURCE` (line 9)
- `PV_MAX_DIM` (line 32)
- `PV_NODE_MAP_INIT_CAP` (line 201)
- `PV_COLOR_TOKEN_MAX` (line 614)
- `PV_MAX_CONTAINERS` (line 648)
- `PV_MAX_GRID_COLS` (line 650)
- `PV_MAX_STYLE_BYTES` (line 1648)

**Structs:**
- `pv_node_map` (line 203) - *Keystone (Stage 0): document-order element identity. page_view builds the same pre-order element walk that dom_build uses, mapping each element poi...*
- `pv_cont_info` (line 658) - *Nearest-container info attached to a run, plus the flex per-item values (Stage 3): grow/shrink/basis/order come from the ITEM element (the containe...*
- `pv_item_track` (line 675) - *Per-container item-ordinal tracker: ord[cid] is the ordinal last handed out for container cid, node[cid] the direct-child element it belongs to. A ...*
- `pv_box_info` (line 694) - *Author box model resolved for a run: horizontal placement (l/r insets, w cap, centered) from the nearest block ancestor that declares a box, plus t...*
- `pv_text_ext` (line 702) - *Author text-presentation extensions resolved for a run (Hito 23b-6): each from the nearest ancestor that sets it (they inherit in CSS). list_style ...*
- `pv_container_reg` (line 828) - *Document-order registry of flex/grid container nodes, so the runs of one * container share a stable id.*
- `pv_box_reg` (line 845) - *Box engine (Hito 23b-8 Step D): document-order registry of box-carrying block nodes plus each box's resolved definition (decoration + parent link)....*
- `pv_style_cache` (line 919) - *Per-document memo of cch_element_style() results, keyed by element pointer. resolve_context()/in_hidden_subtree() call cch_element_style once per A...*
- `form_rec` (line 1236) - *One <form> seen in document order: its grouping id is its index. action is an owned NUL-terminated copy of the raw action attribute (or NULL); meth...*
- `form_table` (line 1242)
- `pv_flow_reg` (line 1586) - *Cache of the per-table flow decision (a table subtree is scanned at most once, * anti-DoS). Registry full => grid (the previous behaviour), bounded...*

#### `pdf_export.c`
**Path:** `src/pdf_export.c`

**Functions:**
- `pe_safe_basename` (line 24)
- `pe_build_path_ext` (line 65)
- `pe_build_path` (line 90)
- `pe_paginate` (line 94)

#### `render_doc.c`
**Path:** `src/render_doc.c`

**Functions:**
- `utf8_seq_len` (line 23) - *UTF-8 sanitisation, kept local so render_doc stays self-contained (matching the convention in browser.c and page_view.c). Output is never longer th...*
- `utf8_sanitized_dup` (line 31)
- `rd_push` (line 63) - *Appends one block, taking owned copies of text (required) and href (optional). * Returns 0 on success, -1 on allocation failure (the doc is left co...*
- `rd_push_input` (line 156) - *Appends an RD_INPUT block, copying text (placeholder/label), the form action * (href), and the control name/value. Returns 0, or -1 on allocation f...*
- `rd_build` (line 173)
- `url_resolve_file` (line 222)
- `rd_free` (line 369)
- `rd_count` (line 382)
- `rd_at` (line 386)
- `rd_box_count` (line 391)
- `rd_box_at` (line 395)
- `rd_kind_name` (line 400)
- `rd_block_tag` (line 412)
- `rd_input_label` (line 437)
- `rd_image_label` (line 449)

#### `render_policy.c`
**Path:** `src/render_policy.c`

**Functions:**
- `rdp_caps_safe` (line 15) - *render_policy — implementation: pure, I/O-free render-capabilities gate and per-image load decision.  Secure/Privacy by Default: images, author CSS...*
- `rdp_is_tracking_pixel` (line 20)
- `rdp_image_decision` (line 26)
- `rdp_img_reason` (line 49)
- `rdp_images_warning` (line 60)

#### `renderer.c`
**Path:** `src/renderer.c`

**Functions:**
- `write_full` (line 22) - *#include "renderer.h"  #include "html_parse.h" #include "os_sandbox.h"  #include <errno.h> #include <stdint.h> #include <stdlib.h> #include <string...*
- `read_full` (line 33)
- `child_render` (line 47) - *static int read_full(int fd, void *buf, size_t n) { uint8_t *p = (uint8_t *)buf; size_t got = 0; while (got < n) { ssize_t r = read(fd, p + got, n ...*
- `read_field` (line 75) - *int ok = (title != NULL && text != NULL) && write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd,...*
- `rd_render_html` (line 91) - *size_t n = 0; if (read_full(fd, &n, sizeof n) != 0) return -1; if (n > RD_MAX_FIELD) return -1; /* anti-amplification: reject huge lengths  char *b...*
- `rd_result_free` (line 141)

**Macros:**
- `_POSIX_C_SOURCE` (line 6)

#### `request_policy.c`
**Path:** `src/request_policy.c`

**Functions:**
- `lower` (line 21) - *all output goes to caller-provided bounded buffers.   #include "request_policy.h"  #include "psl_data.h"  #include <stdlib.h> #include <string.h>  ...*
- `ci_starts_with` (line 25)
- `psl_cmp` (line 35) - *static char lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c; }  static int ci_starts_with(const char *s, const char *pr...*
- `psl_in` (line 39)
- `public_suffix_labels` (line 48) - *Number of labels of the public suffix (eTLD) of a lowercased host, applying the full PSL algorithm: exception rules win; otherwise the longest matc...*
- `rp_host_of` (line 75) - *} if (s + 1 < n) { const char *parent = host + off[s + 1]; /* labels[s+1..n-1] if (psl_in(psl_wildcards, psl_wildcards_n, parent)) { if (ncand > be...*
- `rp_site_of` (line 101)
- `rp_same_site` (line 133)
- `rp_evaluate` (line 142)

**Macros:**
- `RP_MAX_HOST` (line 16)
- `RP_MAX_LABELS` (line 18)

#### `secure_fetch.c`
**Path:** `src/secure_fetch.c`

**Functions:**
- `ci_starts_with` (line 40) - */* --- small helpers (no libc locale dependence) ---  static int ci_equal(const char *a, const char *b) { while (*a && *b) { int ca = (unsigned cha...*
- `ci_index` (line 52) - */* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char *prefix) { while (*prefix) { int c...*
- `sf_share_lock` (line 63)
- `sf_share_unlock` (line 69)
- `sf_global_init` (line 76) - *static pthread_mutex_t sf_cookie_lock = PTHREAD_MUTEX_INITIALIZER;  static void sf_share_lock(CURL *handle, curl_lock_data data, curl_lock_access a...*
- `sf_config_default` (line 91)
- `sf_user_agent_or_default` (line 107)
- `sf_validate_url` (line 113) - *c.proxy_type = SF_PROXY_NONE; /* direct by default; Tor/I2P is opt-in c.proxy_address = NULL; c.allow_overlay_http = 0;     /* https-only unless an...*
- `sf_url_is_http` (line 122) - *Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host. Plain http is only ever permitted for overlay (.onion/.i2p) realms, g...*
- `sf_check_tls_version` (line 133)
- `sf_check_group_is_pq` (line 138)
- `sf_check_chain_policy` (line 147)
- `sf_enforce_policy` (line 157)
- `copy_checked` (line 188) - *The navigability fallback accepts a classical KE; every other policy requires * a PQ-hybrid group. The certificate chain is always validated below....*
- `sf_is_redirect_code` (line 197) - *if (chain == NULL) return SF_ERR_INTERNAL; /* fail closed: chain not inspectable return sf_check_chain_policy(chain, policy); }  /* --- bounded str...*
- `sf_parse_location_header` (line 204)
- `sf_resolve_redirect` (line 222)
- `sf_ci_prefix` (line 235) - *Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a reference resolved against the ...*
- `sf_response_free` (line 274) - *if (sf_ci_prefix(location, "http://")) { if (snprintf(hloc, sizeof hloc, "https://%s", location + 7) >= (int)sizeof hloc) return SF_ERR_INVALID_URL...*
- `copy_bounded` (line 331)
- `get_negotiated_group_name` (line 343) - *static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len);  static void copy_bounded(char *dst, size_t dstsz, const ...*
- `tls_capture_try` (line 374) - *first shared group, which corresponds to the negotiated key exchange * group (for both TLS 1.2 ECDHE and TLS 1.3). nid = SSL_get_shared_group(ssl, ...*
- `header_cb` (line 406) - *Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to snapshot the negotiated TLS state.*
- `write_cb` (line 441)
- `name_is_pq_sig` (line 474) - *if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; } memcpy(sink->data + sink->len, ptr, in...*
- `inspect_chain` (line 484) - *Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if the chain could not be inspected.*
- `map_curl_error` (line 536)
- `sf_perform` (line 566) - *The shared request engine for sf_get and sf_post. When post_body == NULL it is a GET; otherwise it is a POST carrying body (post_len bytes) with co...*
- `redirect` (line 646)
- `sf_get` (line 755)
- `sf_post` (line 759)
- `sf_get_follow` (line 773)

**Macros:**
- `_POSIX_C_SOURCE` (line 11)

**Structs:**
- `body_sink` (line 298) - *resp->tls_version = NULL; resp->negotiated_group = NULL; resp->body = NULL; resp->body_len = 0; resp->location = NULL; resp->final_url = NULL; resp...*
- `tls_capture` (line 311) - *Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a transfer is in progress (via CURLINFO_TLS_SSL_PTR); after curl_easy_p...*
- `fetch_ctx` (line 321)

#### `tab.c`
**Path:** `src/tab.c`

**Functions:**
- `write_full` (line 79) - *Per-page subresource caps (anti-DoS): a hostile script cannot drive unbounded fetches * or amplification through the parent. #define TAB_MAX_SUBREQ...*
- `read_full` (line 90)
- `child_reset_page` (line 123)
- `policy` (line 137)
- `run_js` (line 189)
- `write_view` (line 274) - *cont_id,cont_display,cont_gap,cont_justify,cont_cols, flex_grow,flex_shrink,flex_basis,flex_order,flex_direction,cont_item, cont_wrap,cont_row_gap,...*
- `FB_MAX_FILE_BYTES` (line 468)
- `budget_remaining_ms` (line 498) - *Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS budget across the inline scrip...*
- `ctype_is_javascript` (line 512) - *Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types): accept a missing/empty type -- class...*
- `ctype_is_css` (line 521) - *Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is accepted, anything else must mention...*
- `log_external_skip` (line 529) - *Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused). The raw hostile src is bounded by the messag...*
- `window` (line 549)
- `child_handle_load` (line 589)
- `click` (line 746)
- `child_handle_eval` (line 785) - *Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a JS-level error is ok==1 with the...*
- `child_handle_decode_image` (line 814) - *Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data]. Decoding hostile image bytes happens here, inside the confinement...*
- `gen_session_key` (line 830)
- `tab_worker_run` (line 851) - *The confined request loop. Runs in the re-exec'd worker image (see * tab_worker_dispatch). Never returns to the caller (always _exit).*
- `parse_worker_fd` (line 947) - *else if (op == OP_EVAL)         child_handle_eval(wfd, &cs, buf, len); else /* OP_DECODE_IMAGE */      child_handle_decode_image(wfd, buf, len); fr...*
- `tab_parse_worker_args` (line 958)
- `tab_worker_dispatch` (line 968)
- `ignore_sigpipe` (line 997) - *A write to a dead child must not kill the parent with SIGPIPE. Idempotent; * no module-level mutable state of our own (the disposition is process-w...*
- `tab_refresh_alive` (line 1003)
- `read_field` (line 1023) - *Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.*
- `read_view` (line 1038) - *Reads a display list serialised by write_view into a fresh pv_view. The run * count and each field are capped against amplification from a hostile ...*
- `read_console` (line 1230) - *Reads the console section written by write_console into out (a zero-initialised fb_buffer). Bounds the entry count and each length against amplific...*
- `send_request` (line 1266) - *if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt, elen) != 0) { free(txt); free(file)...*
- `io_failure` (line 1275)
- `exec_worker_child` (line 1284) - *Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other tabs' content from tab_slots[], fr...*
- `tab_set_fetcher` (line 1352)
- `tab_set_net_allowed` (line 1358)
- `tab_set_css_allowed` (line 1363)
- `tab_subreq_permitted` (line 1368)
- `answered` (line 1381)
- `tab_load` (line 1416)
- `tab_load_ex` (line 1420)
- `tab_load_full` (line 1424)
- `tab_click` (line 1528)
- `tab_eval` (line 1591)
- `tab_decode_image` (line 1628)
- `tab_alive` (line 1671)
- `tab_child_pid` (line 1677)
- `tab_close` (line 1681)
- `tab_page_free` (line 1693)
- `tab_eval_result_free` (line 1709)
- `tab_image_free` (line 1718)

**Macros:**
- `_GNU_SOURCE` (line 13)
- `TAB_SCREEN_W` (line 50)
- `TAB_SCREEN_H` (line 51)
- `TAB_MAX_RUNS` (line 55)
- `TAB_MAX_URL` (line 58)
- `TAB_MAX_SUBREQ` (line 71)
- `TAB_MAX_SUBRESOURCE` (line 72)
- `TAB_MAX_JS_JOBS` (line 73)
- `TAB_MAX_EXTERN_CSS` (line 541)

**Structs:**
- `child_state` (line 105) - *static int read_full(int fd, void *buf, size_t n) { uint8_t *p = (uint8_t *)buf; size_t got = 0; while (got < n) { ssize_t r = read(fd, p + got, n ...*
- `tab` (line 979) - *wfd = b; return 1; }  void tab_worker_dispatch(int argc, char **argv) { int rfd = -1, wfd = -1; if (!tab_parse_worker_args(argc, (const char *const...*

#### `text_shape.c`
**Path:** `src/text_shape.c`

**Functions:**
- `generic_name` (line 53)
- `backend_init` (line 63)
- `read_font_file` (line 80)
- `load_entry` (line 96)
- `get_entry` (line 151)
- `tsh_ready` (line 163)
- `tsh_shape` (line 168)
- `tsh_measure` (line 213)
- `tsh_draw` (line 220)
- `tsh_shutdown` (line 242)

**Macros:**
- `_POSIX_C_SOURCE` (line 11)
- `TSH_MAX_FONT_BYTES` (line 28)
- `TSH_CACHE_SLOTS` (line 32)

**Structs:**
- `tsh_entry` (line 34) - *One resolved face per (family, bold, italic). family is a CSS_FF_* bucket * (0..CSS_FF_FANTASY); idx = family*4 + bold*2 + italic. define TSH_CACHE...*

#### `textfield.c`
**Path:** `src/textfield.c`

**Functions:**
- `whole` (line 6)
- `tf_clear` (line 19)
- `tf_set` (line 23)
- `tf_insert` (line 34)
- `tf_backspace` (line 46)
- `tf_delete` (line 54)
- `tf_move` (line 61)
- `tf_home` (line 72)
- `tf_end` (line 77)
- `tf_text` (line 82)
- `tf_len` (line 86)
- `tf_cursor` (line 90)

#### `ui_layout.c`
**Path:** `src/ui_layout.c`

**Functions:**
- `layout_push` (line 12) - *ui_layout — pure layout core (no I/O).  Monospace word-wrapping and scroll clamping. Lines are contiguous slices of the source text, so no text is ...*
- `ui_wrap_text` (line 26)
- `ui_layout_free` (line 90)
- `ui_clamp_scroll` (line 98)

#### `url.c`
**Path:** `src/url.c`

**Functions:**
- `ci_prefix` (line 19) - *dot-segment canonicalisation. Fails closed: a non-https result is never produced; every assembly is bounded and reports overflow rather than trunca...*
- `copy_checked` (line 31) - */* Case-insensitive: does haystack start with prefix? static int ci_prefix(const char *haystack, const char *prefix) { while (*prefix) { int ch = (...*
- `cat_checked` (line 39) - *+haystack; ++prefix; } return 1; }  /* Bounded copy: out gets src (NUL-terminated). Nonzero on overflow. static int copy_checked(char *out, size_t ...*
- `ncat_checked` (line 48) - *memcpy(out, src, n + 1); return 0; }  /* Bounded append: out += src. Nonzero on overflow. static int cat_checked(char *out, size_t outsz, const cha...*
- `url_has_scheme` (line 57) - *memcpy(out + cur, src, n + 1); return 0; }  /* Bounded append of the first n bytes of src. Nonzero on overflow. static int ncat_checked(char *out, ...*
- `url_is_https` (line 71)
- `url_validate_https` (line 78)
- `url_authority_len` (line 89)
- `out_pop_segment` (line 99) - *while (i <= URL_MAX_LEN && url[i] != '\0') ++i; if (i > URL_MAX_LEN) return URL_ERR_NOT_HTTPS; return url_is_https(url) ? URL_OK : URL_ERR_NOT_HTTP...*
- `url_remove_dot_segments` (line 105)
- `dir_len` (line 156) - *Length of base up to and including the last path '/', ignoring query/fragment. * If the path carries no slash, returns the authority length.*
- `url_resolve_https` (line 166)
- `is_space` (line 214) - *char norm[URL_MAX_LEN + 1]; url_status ns = url_remove_dot_segments(merged, norm, sizeof norm); if (ns != URL_OK) return ns;  out[0] = '\0'; if (nc...*
- `is_unreserved` (line 218)
- `append_query_encoded` (line 226) - *Percent-encodes src into a query value appended to out (space -> '+', every * non-unreserved byte -> %XX). Nonzero on overflow.*
- `assumed` (line 251)
- `build_search` (line 299)
- `url_omnibox` (line 305)
- `url_extract_userinfo` (line 375) - *Any remaining explicit scheme is never executed nor downgraded: search for it * (so "javascript:...", "file:...", "ftp://..." become harmless queri...*
- `url_is_file` (line 469) - *username_out = strdup(username); if (*username_out == NULL) return URL_ERR_NULL_ARG; } if (password_out != NULL) { password_out = (pass_len > 0) ? ...*
- `url_file_path` (line 475)
- `url_resolve_file` (line 479)
- `url_split` (line 528) - *Confinement: the canonical path must stay inside the base directory subtree. base directory text = base_path[0..dir_end) (ends with '/'), so a stri...*

**Macros:**
- `_POSIX_C_SOURCE` (line 8)

#### `zoom.c`
**Path:** `src/zoom.c`

**Functions:**
- `zm_clamp` (line 13) - *define ZM_LADDER_N ((int)(sizeof ZM_LADDER / sizeof ZM_LADDER[0]))*
- `zm_zoom_in` (line 19)
- `zm_zoom_out` (line 27)
- `zm_reset` (line 35)
- `zm_scale` (line 39)
- `zm_apply` (line 43)

**Macros:**
- `ZM_LADDER_N` (line 12)

#### `itest_secure_fetch.c`
**Path:** `tests/itest_secure_fetch.c`

**Functions:**
- `main` (line 25)

**Macros:**
- `CHECK` (line 15)

#### `test_anti_fp.c`
**Path:** `tests/test_anti_fp.c`

**Functions:**
- `test_coarsen_time` (line 17) - *Pure primitives: no I/O. Build: make test   ;   ASan: make asan   #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #...*
- `test_identity_is_fixed` (line 33) - *(void)state; uint64_t res = fp_timer_resolution_ms(); assert_true(res > 0); assert_int_equal((int)fp_coarsen_time_ms(0), 0); assert_int_equal((int)...*
- `test_bucket_screen` (line 60) - *assert_string_equal(fp_accept_language_header(), "en-US,en;q=0.5"); assert_non_null(strstr(fp_accept_language_header(), "en-US")); assert_null(strc...*
- `test_perturb_deterministic` (line 78) - *fp_bucket_screen(1920, 1080, &w, &h); assert_int_equal(w, 1920); assert_int_equal(h, 1080);  fp_bucket_screen(1680, 1050, &w, &h); assert_int_equal...*
- `test_perturb_bounded_lsb` (line 88)
- `test_perturb_key_sensitive` (line 103)
- `test_perturb_safe_edges` (line 113)
- `test_origin_key_deterministic` (line 123) - *fp_perturb(a, sizeof a, 1); fp_perturb(b, sizeof b, 2); assert_memory_not_equal(a, b, sizeof a); /* different key => different output }  static voi...*
- `test_origin_key_per_site` (line 130)
- `test_origin_key_per_session` (line 142)
- `test_origin_key_empty_namespace` (line 148)
- `test_origin_key_unlinks_readback` (line 161) - *The property that actually matters: the same canvas buffer poisoned under two different sites' keys diverges, so a tracker cannot link the two read...*
- `main` (line 174)

#### `test_box_style.c`
**Path:** `tests/test_box_style.c`

**Functions:**
- `dbl_eq` (line 22) - *the display-name helper.   #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h>  #include <cmocka.h>...*
- `assert_edges` (line 26)
- `test_body_has_no_margin` (line 33)
- `test_paragraph` (line 41)
- `test_heading_ladder` (line 48)
- `test_lists` (line 64)
- `test_blockquote` (line 75)
- `test_hr` (line 82)
- `test_inline_and_inline_block` (line 89)
- `test_display_none_for_non_rendered` (line 100)
- `test_case_insensitive` (line 109)
- `test_unknown_and_null_are_neutral_inline` (line 117)
- `test_div_is_block` (line 132)
- `test_parse_display_keywords` (line 139)
- `test_parse_display_inline_aliases` (line 158)
- `test_parse_display_case_and_trim` (line 167)
- `test_parse_display_errors` (line 176)
- `test_display_name` (line 194)
- `test_place_no_box_is_identity` (line 209) - *static void test_display_name(void **state) { (void)state; assert_string_equal(bx_display_name(BX_DISPLAY_BLOCK), "block"); assert_string_equal(bx_...*
- `test_place_max_width_caps` (line 216)
- `test_place_centering` (line 227)
- `test_place_insets` (line 239)
- `test_place_failclosed_bounds` (line 251)
- `main` (line 265)

#### `test_box_tree.c`
**Path:** `tests/test_box_tree.c`

**Functions:**
- `assert_rect` (line 26)
- `test_null_root` (line 33)
- `test_leaf` (line 38)
- `test_leaf_with_padding` (line 45)
- `test_block_stacking_with_collapse` (line 60)
- `test_flex_row_grow` (line 73)
- `test_flex_gap_and_justify_center` (line 91)
- `test_flex_wrap_two_lines` (line 107)
- `test_flex_nowrap_default_single_line_unchanged` (line 129)
- `test_flex_wrap_reverse_two_lines` (line 149)
- `test_flex_wrap_row_gap_distinct_from_gap` (line 171)
- `test_flex_cross_axis_align` (line 191)
- `test_grid_row_gap_distinct_from_gap` (line 209)
- `test_grid_without_row_gap_falls_back_to_gap` (line 232)
- `test_grid` (line 248)
- `test_nested_flex_in_block` (line 269)
- `test_display_none_skipped` (line 293)
- `test_grid_bad_columns` (line 308)
- `test_flex_negative_gap` (line 318)
- `test_children_cap` (line 328)
- `test_depth_cap` (line 338)
- `test_positioning_null_args` (line 355) - *static bt_node chain[BT_MAX_DEPTH + 5]; size_t n = sizeof chain / sizeof chain[0]; for (size_t i = 0; i < n; ++i) { chain[i].display = BX_DISPLAY_B...*
- `test_positioning_static_unchanged` (line 369)
- `test_positioning_relative_offset` (line 381)
- `test_positioning_absolute_against_ancestor` (line 402)
- `test_positioning_absolute_against_viewport` (line 425)
- `test_positioning_fixed_against_viewport` (line 442)
- `test_positioning_sticky_treated_as_relative` (line 461)
- `test_positioning_stacking_order` (line 479)
- `test_positioning_doc_order_tiebreak` (line 499)
- `test_positioning_no_insets` (line 517)
- `test_positioning_null_geometry` (line 534)
- `test_positioning_nbox_cap` (line 551)
- `main` (line 568)

#### `test_browser.c`
**Path:** `tests/test_browser.c`

**Functions:**
- `test_init` (line 19) - *Build: make test   ;   ASan: make asan  define _POSIX_C_SOURCE 200809L include <stdarg.h> include <stddef.h> include <stdint.h> include <stdlib.h> ...*
- `test_navigate_history` (line 30)
- `test_navigate_from_middle_discards_future` (line 60)
- `test_back_forward_bounds` (line 78)
- `test_rejects_invalid_url` (line 94)
- `test_accepts_https_and_file` (line 107)
- `test_url_bar_editing` (line 121)
- `test_url_bar_selection` (line 152) - *Omnibar selection model: extend builds a selection, ops replace/delete it, and a * plain move collapses it.*
- `test_set_page` (line 195)
- `test_set_page_sanitizes_invalid_utf8` (line 218) - *Page title/text come from hostile documents; legacy encodings (Latin-1) carry bytes that are invalid UTF-8 and poison the cairo text renderer. brow...*
- `test_exceptions` (line 251)
- `test_status_toast` (line 277) - *The transient status line (toast) is time-bounded and caller-clocked: visible until now_ms reaches the expiry, then gone. NULL/empty clears it, and...*
- `test_status_truncates` (line 308)
- `main` (line 325)

**Macros:**
- `_POSIX_C_SOURCE` (line 7)

#### `test_css.c`
**Path:** `tests/test_css.c`

**Functions:**
- `test_inline_text_align` (line 31)
- `test_inline_font_size` (line 39)
- `test_inline_line_height` (line 49)
- `test_inline_font_weight_style` (line 62)
- `test_inline_text_decoration` (line 74)
- `test_font_family` (line 101) - */* none is an explicit value (0), distinct from unset (-1). assert_int_equal(css_parse_inline("text-decoration:none", 0).text_decoration, 0); /* Co...*
- `test_text_transform` (line 122)
- `test_letter_word_spacing` (line 136)
- `test_text_shadow` (line 151)
- `test_opacity` (line 173)
- `test_vertical_align` (line 183)
- `test_text_indent` (line 192)
- `test_white_space` (line 201)
- `test_list_style_type` (line 211)
- `test_text_ext_cascade_and_important` (line 225)
- `test_inline_display` (line 240)
- `test_inline_container_props` (line 251) - *assert_int_equal(s.font_family, CSS_FF_MONO);          /* inline wins css_free(sh); }  static void test_inline_display(void **state) { (void)state;...*
- `test_sheet_container_props` (line 278)
- `test_container_cascade_inline_wins` (line 299) - *const char *row[] = { "row" }; css_style f = css_resolve(sh, "div", NULL, row, 1, NULL, 0); assert_int_equal(f.display, CSS_DISP_FLEX); assert_int_...*
- `test_container_fail_closed_and_bounds` (line 314) - *Fail closed: a bad justify keyword is dropped (unset); grid-template-columns:none * is unset; gap and column count are clamped to their anti-DoS bo...*
- `test_grid_minmax_counts_as_one_track` (line 346)
- `test_grid_repeat_autofill_fails_closed` (line 354)
- `test_grid_repeat_malformed_fails_closed` (line 365)
- `test_grid_repeat_clamped_anti_dos` (line 372)
- `test_container_unset` (line 379)
- `test_url_value_dropped` (line 389) - *assert_int_equal( css_parse_inline("grid-template-columns: repeat(999, 1fr)", 0).grid_cols, (int)CSS_GRID_COLS_MAX); }  static void test_container_...*
- `test_unknown_props_ignored` (line 399)
- `test_malformed_inline_no_crash` (line 406)
- `test_custom_prop_var_basic` (line 414) - *static void test_unknown_props_ignored(void **state) { (void)state; css_style s = css_parse_inline("position:absolute; z-index:9; color:#abcdef; --...*
- `test_custom_prop_var_fallback_used_when_missing` (line 425)
- `test_custom_prop_var_no_fallback_drops_decl` (line 431)
- `test_custom_prop_var_chain` (line 440)
- `test_custom_prop_var_self_reference_fails_closed` (line 448)
- `test_custom_prop_var_in_shorthand` (line 457)
- `test_custom_prop_var_later_declaration_wins` (line 467)
- `test_custom_prop_var_unbalanced_paren_drops` (line 480)
- `test_custom_prop_var_never_phones_home` (line 487)
- `test_sheet_type_selector` (line 501) - *A custom property whose value contains url() — colour IS honoured, * the URL is never fetched. css_style s = css_parse_inline( "--evil: url(http://...*
- `test_sheet_class_and_id` (line 512)
- `test_sheet_universal_and_group` (line 522)
- `test_sheet_compound_selector` (line 532)
- `el_node` (line 546) - *static void test_sheet_compound_selector(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse("a.button { color:#0a0b0c }"...*
- `el_sib_node` (line 557) - *}  /* Builds one css_element node aliasing the given fields (test-local helper). static css_element el_node(const char *tag, const char *id, const ...*
- `el_attr_node` (line 565) - *e.attrs = NULL; e.nattrs = 0; e.parent = parent; e.nth = 0; e.nsib = 0; e.prev = NULL;   /* sibling context unknown by default return e; }  /* Like...*
- `test_text_decoration_cascade` (line 573)
- `test_descendant_combinator` (line 592)
- `test_child_combinator` (line 608)
- `test_combinator_specificity_sum` (line 621)
- `test_combinator_class_chain` (line 636)
- `test_adjacent_sibling_combinator` (line 655) - *const char *nav[] = { "nav" }; const char *item[] = { "item" }; css_element navdiv = el_node("div", NULL, nav, 1, NULL); css_element li     = el_no...*
- `test_general_sibling_combinator` (line 670)
- `test_sibling_mixed_with_child` (line 685)
- `test_pseudo_link` (line 702)
- `test_pseudo_never_match_keeps_group` (line 720)
- `test_pseudo_structural` (line 737)
- `test_pseudo_nth_child` (line 757)
- `assert_int_equal` (line 761)
- `test_pseudo_nth_last_child` (line 780)
- `assert_int_equal` (line 784)
- `test_pseudo_root_and_form_state` (line 791)
- `test_pseudo_unknown_drops_selector` (line 815)
- `test_pseudo_specificity` (line 837)
- `test_pseudo_with_sibling_combinator` (line 855)
- `test_pseudo_nth_malformed_drops` (line 872)
- `assert_int_equal` (line 878) - *Malformed or oversized An+B drops the selector (fail closed); partner rules * survive.*
- `test_resolve_el_inline_only` (line 888)
- `test_attr_presence` (line 896) - *"li{background:#101010}", 0, &sh), CSS_OK); css_element li = el_sib_node("li", 1, 1, NULL, NULL); assert_int_equal(css_resolve_el(sh, &li, NULL, 0)...*
- `test_attr_equals` (line 909)
- `test_attr_operators` (line 927)
- `test_attr_case_insensitive_flag` (line 959)
- `test_attr_name_case_insensitive` (line 974)
- `test_attr_quoted_value_with_space` (line 985)
- `test_attr_specificity_and_compound` (line 999)
- `test_attr_in_combinator` (line 1016)
- `test_attr_malformed_fail_closed` (line 1032)
- `test_important_inline_not_dropped` (line 1050) - *Unbalanced/empty/unknown-operator brackets drop only that selector; the plain * rule in the group survives. assert_int_equal(css_parse("input[ {col...*
- `test_important_beats_specificity` (line 1060)
- `test_important_tier_then_normal_order` (line 1069)
- `test_important_inline_beats_sheet_important` (line 1079)
- `test_important_in_shorthand` (line 1091)
- `test_cascade_specificity` (line 1108) - */* !important stamps every side a shorthand expands to. css_style s = css_parse_inline("margin:10px !important", 0); assert_int_equal(s.margin_top,...*
- `silent` (line 1125)
- `test_cascade_document_order` (line 1149)
- `test_cascade_inline_wins` (line 1158)
- `test_at_rules_skipped` (line 1167)
- `test_media_screen_and_print` (line 1185) - *@import is skipped entirely (no network). @media screen matches the default context, so its rule applies, then the later same-specificity plain rul...*
- `test_media_prefers_color_scheme` (line 1204) - *"@media print { p { color:#010101 } }", 0, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0xabcdef); css_free(...*
- `test_media_width_queries` (line 1220) - *const char *css = "@media (prefers-color-scheme: dark) { body { color:#ffffff } }"; css_sheet *sh = NULL;  assert_int_equal(css_parse(css, 0, &sh),...*
- `assert_int_equal` (line 1223)
- `test_media_and_or` (line 1235) - *(void)state; css_sheet *sh = NULL; assert_int_equal(css_parse( "@media (min-width: 600px) { p { color:#111111 } }\n" "@media (min-width: 3000px) { ...*
- `assert_int_equal` (line 1238)
- `test_media_unknown_fails_closed` (line 1249) - *static void test_media_and_or(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse( "@media screen and (min-width: 600px) ...*
- `assert_int_equal` (line 1252)
- `test_parse_null_args` (line 1266) - *assert_int_equal(css_parse( "@media (hover: hover) { p { color:#cccccc } }\n" "@media tv { a { color:#dddddd } }\n" "@media not screen { b { color:...*
- `test_resolve_null_safe` (line 1276)
- `test_inline_box_longhands` (line 1290) - *static void test_resolve_null_safe(void **state) { (void)state; /* NULL sheet and NULL tag are safe; everything unset. css_style s = css_resolve(NU...*
- `test_box_shorthand_expansion` (line 1308)
- `test_box_auto_and_centering` (line 1336)
- `test_box_units_and_failclosed` (line 1353)
- `test_calc_basic_arithmetic` (line 1376)
- `test_calc_precedence_and_parens` (line 1385)
- `test_calc_units_and_signs` (line 1392)
- `test_calc_dimension_errors_fail_closed` (line 1400)
- `test_calc_clamped_anti_dos` (line 1415)
- `test_calc_inside_shorthands` (line 1426) - *calc() must survive being ONE token inside a multi-value shorthand: a naive whitespace splitter would break "calc(10px + 5px)" apart at the interna...*
- `test_calc_with_custom_property` (line 1463)
- `test_box_clamp_anti_dos` (line 1470)
- `test_inline_min_width_height` (line 1479) - *(void)state; /* calc() and var() compose: var() substitutes text before calc() is parsed. css_style s = css_parse_inline("--base: 20px; width: calc...*
- `test_inline_min_max_height` (line 1506)
- `test_box_extension_sheet_cascade` (line 1520)
- `test_inline_text_decoration_color_style` (line 1540) - *"#s { height:400px }", 0, &sh), CSS_OK); const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, NULL, 0); assert_int_eq...*
- `test_inline_text_decoration_thickness` (line 1569) - */* All style keywords. assert_int_equal(css_parse_inline("text-decoration-style:solid", 0).text_decoration_style, CSS_TDS_SOLID); assert_int_equal(...*
- `test_inline_aspect_ratio` (line 1586) - */* from-font -> 0 (the painter treats 0 as "default thickness" via cairo). assert_int_equal(css_parse_inline("text-decoration-thickness:from-font",...*
- `test_inline_direction` (line 1616) - *css_style d = css_parse_inline("aspect-ratio:auto", 0); assert_int_equal(d.aspect_num, 0); assert_int_equal(d.aspect_den, 0); /* Bad value -> 0/0 (...*
- `test_inline_outline_offset` (line 1625) - *assert_int_equal(def.aspect_num, 0); assert_int_equal(def.aspect_den, 0); }  /* --- direction ---  static void test_inline_direction(void **state) ...*
- `test_inline_tab_size` (line 1637) - */* --- outline-offset ---  static void test_inline_outline_offset(void **state) { (void)state; assert_int_equal(css_parse_inline("outline-offset:2p...*
- `test_box_sheet_cascade_inline_wins` (line 1647)
- `test_position_and_insets` (line 1662) - *static void test_box_sheet_cascade_inline_wins(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse(".card{max-width:600px...*
- `test_float_and_clear` (line 1693)
- `test_visibility` (line 1717)
- `test_overflow` (line 1734)
- `test_cursor` (line 1757)
- `test_text_overflow_and_word_break` (line 1773)
- `test_box_sizing` (line 1798)
- `test_border_shorthand` (line 1806)
- `test_border_longhands` (line 1836)
- `test_box_shadow_and_outline` (line 1862)
- `test_flex_item` (line 1887)
- `test_flex_align` (line 1916)
- `test_grid_extras` (line 1938)
- `test_layout_sheet_cascade_and_unset` (line 1956)
- `test_inline_outline_longhands` (line 1993) - *const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, "z-index:9", 0); assert_int_equal(s.position, CSS_POS_ABSOLUTE);...*
- `test_inline_border_collapse` (line 2024) - *assert_int_equal(css_parse_inline("outline-style:none", 0).outline_style, CSS_BST_NONE); assert_int_equal(css_parse_inline("outline-style:ridge", 0...*
- `test_inline_border_spacing` (line 2033) - *assert_int_equal(css_parse_inline("outline-color:auto", 0).outline_color, -1); /* dropped assert_int_equal(css_parse_inline("color:red", 0).outline...*
- `test_inline_empty_cells` (line 2044) - *}  /* --- border-spacing --- static void test_inline_border_spacing(void **state) { (void)state; assert_int_equal(css_parse_inline("border-spacing:...*
- `test_inline_caption_side` (line 2053) - *assert_int_equal(css_parse_inline("border-spacing:auto", 0).border_spacing, CSS_LEN_UNSET); /* dropped assert_int_equal(css_parse_inline("color:red...*
- `test_inline_table_layout` (line 2062) - *assert_int_equal(css_parse_inline("empty-cells:auto", 0).empty_cells, CSS_EC_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).e...*
- `test_inline_font_variant` (line 2071) - *assert_int_equal(css_parse_inline("caption-side:left", 0).caption_side, CSS_CS_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0)...*
- `test_inline_hyphens` (line 2080) - *assert_int_equal(css_parse_inline("table-layout:collapse", 0).table_layout, CSS_TL_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red"...*
- `test_inline_user_select` (line 2090) - *assert_int_equal(css_parse_inline("color:red", 0).font_variant, CSS_FV_UNSET); }  /* --- hyphens --- static void test_inline_hyphens(void **state) ...*
- `test_inline_caret_color` (line 2101) - *}  /* --- user-select --- static void test_inline_user_select(void **state) { (void)state; assert_int_equal(css_parse_inline("user-select:none", 0)...*
- `test_inline_appearance` (line 2111) - *assert_int_equal(css_parse_inline("color:red", 0).user_select, CSS_US_UNSET); }  /* --- caret-color --- static void test_inline_caret_color(void **...*
- `test_inline_pointer_events` (line 2120) - *assert_int_equal(css_parse_inline("caret-color:blargh", 0).caret_color, -1); /* unknown -> unset assert_int_equal(css_parse_inline("color:red", 0)....*
- `test_table_sheet_cascade` (line 2129) - *assert_int_equal(css_parse_inline("appearance:button", 0).appearance, CSS_AP_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).a...*
- `test_inline_bg_repeat` (line 2144) - *(void)state; css_sheet *sh = NULL; assert_int_equal(css_parse("table{border-collapse:collapse;empty-cells:hide;caption-side:bottom;table-layout:fix...*
- `test_inline_bg_size` (line 2155)
- `test_inline_bg_clip_origin_attachment` (line 2164)
- `test_inline_isolation` (line 2184)
- `test_inline_contain` (line 2192)
- `test_inline_content_visibility` (line 2207)
- `test_inline_image_rendering` (line 2216)
- `test_inline_color_scheme` (line 2225)
- `test_inline_accent_color` (line 2235)
- `test_inline_print_forced_adjust` (line 2244)
- `test_inline_mix_blend_mode` (line 2258) - *static void test_inline_print_forced_adjust(void **state) { (void)state; assert_int_equal(css_parse_inline("print-color-adjust:economy", 0).print_c...*
- `test_inline_object_fit` (line 2278)
- `test_inline_list_style_pos` (line 2289)
- `test_inline_font_kerning` (line 2297)
- `test_inline_text_rendering` (line 2306)
- `test_inline_font_stretch` (line 2316)
- `test_inline_resize` (line 2331)
- `test_inline_scroll_behavior` (line 2341)
- `test_inline_touch_action` (line 2349)
- `test_inline_overscroll_behavior` (line 2358)
- `test_inline_backface_visibility` (line 2367)
- `main` (line 2375)

#### `test_css_color.c`
**Path:** `tests/test_css_color.c`

**Functions:**
- `test_null_args` (line 21)
- `test_hex_short` (line 27)
- `test_hex_short_alpha` (line 36)
- `test_hex_long` (line 43)
- `test_hex_long_alpha` (line 52)
- `test_hex_bad` (line 58)
- `test_rgb_integer` (line 67)
- `test_rgba_integer` (line 76)
- `test_rgb_percent` (line 83)
- `test_rgb_out_of_range` (line 89)
- `test_named` (line 99)
- `test_named_bad` (line 117)
- `test_unsupported_syntax` (line 126)
- `test_pack_unpack` (line 133)
- `main` (line 147)

#### `test_disk_store.c`
**Path:** `tests/test_disk_store.c`

**Functions:**
- `setup` (line 34)
- `teardown` (line 44)
- `count_dir_entries` (line 64)
- `test_roundtrip` (line 77)
- `test_roundtrip_chacha` (line 88)
- `test_empty` (line 98)
- `test_permissions` (line 107)
- `test_no_temp_left` (line 116)
- `test_overwrite` (line 123)
- `test_wrong_key` (line 137)
- `test_tamper_on_disk` (line 149)
- `test_missing_and_null` (line 167)
- `main` (line 180)

**Macros:**
- `_POSIX_C_SOURCE` (line 7)

**Structs:**
- `fixture` (line 33)

#### `test_dom.c`
**Path:** `tests/test_dom.c`

**Functions:**
- `setup_doc` (line 32) - *#include "dom.h" #include "html_parse.h"  static const char HTML[] = "<!DOCTYPE html><html><head><title>T</title></head>" "<body>" "<div id=\"main\...*
- `teardown_doc` (line 44)
- `test_build_null_args` (line 59) - *static int teardown_doc(void **state) { void **pair = (void **)*state; if (pair != NULL) { dom_free((dom_index *)pair[1]); hp_document_free((hp_doc...*
- `test_free_null_and_double` (line 69)
- `test_node_count` (line 80)
- `test_get_by_id` (line 87) - *hp_document *doc = NULL; assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK); dom_index *idx = NULL; assert_int_equal(dom_build(do...*
- `test_get_by_id_absent` (line 101)
- `test_by_class` (line 108) - *assert_non_null(tag); assert_string_equal(tag, "div");  dom_node_id go = dom_get_element_by_id(idx, "go"); assert_int_not_equal(go, DOM_NODE_NONE);...*
- `test_by_tag` (line 117)
- `test_by_tag_results_in_document_order` (line 126)
- `test_document_order` (line 136) - *assert_int_equal(dom_get_by_tag(idx, "P", buf, 8), 2); /* case-insensitive assert_int_equal(dom_get_by_tag(idx, "button", buf, 8), 1); assert_int_e...*
- `test_navigation` (line 150) - *static void test_document_order(void **state) { dom_index *idx = IDX(state); dom_node_id main_id = dom_get_element_by_id(idx, "main"); dom_node_id ...*
- `test_attributes` (line 170) - *assert_int_not_equal(p1, DOM_NODE_NONE); assert_string_equal(dom_tag_name(idx, p1, NULL), "p");  dom_node_id p2 = dom_next_sibling(idx, p1); assert...*
- `test_text_content_read` (line 184) - *static void test_attributes(void **state) { dom_index *idx = IDX(state); dom_node_id main_id = dom_get_element_by_id(idx, "main"); size_t len = 0; ...*
- `test_set_text_content_changes_tree` (line 195)
- `test_set_text_content_empty_clears` (line 213)
- `test_set_text_content_invalid_node` (line 223)
- `test_set_and_get_document_title` (line 228)
- `test_create_and_append` (line 240)
- `test_append_rejects_cycle` (line 258)
- `test_remove_child` (line 268)
- `test_set_attribute_reindexes_id` (line 280)
- `test_remove_attribute` (line 293)
- `test_set_inner_html` (line 310)
- `test_construction_invalid_args` (line 326)
- `test_query_selector_type_class_id` (line 339) - *Fixture tree (inside body): div#main.container.box > [ p.text "Hello", * p.text.muted "World", button#go.btn "Go" ].*
- `test_query_selector_all_counts` (line 353)
- `test_query_selector_combinators` (line 364)
- `test_query_selector_nth_and_structural` (line 377)
- `test_query_selector_scope_is_descendants_only` (line 390)
- `test_matches_and_closest` (line 402)
- `test_query_selector_fail_closed` (line 415)
- `main` (line 431)

**Macros:**
- `DOC` (line 54)
- `IDX` (line 56)

#### `test_dom_debug.c`
**Path:** `tests/test_dom_debug.c`

**Functions:**
- `caps_css_on` (line 28)
- `build` (line 36) - *#include "dom_debug.h" #include "page_view.h" #include "render_doc.h" #include "render_policy.h"  static const char TOP[] = "https://example.com/";...*
- `test_null_doc_is_empty_header` (line 44) - *rdp_caps c = rdp_caps_safe(); c.css = true;          /* box tree + author box/style fields only with caps.css return c; }  /* Builds an rd_doc from...*
- `test_heading_paragraph_link` (line 58) - *static void test_null_doc_is_empty_header(void **state) { (void)state; char buf[256]; size_t n = dd_format(NULL, buf, sizeof buf); assert_true(n > ...*
- `test_grid_container_annotation` (line 91) - *-- a grid container (a table) annotates its cells: the field that reveals a *     collapsed table column ---*
- `test_box_tree_width_cap` (line 115) - *char buf[1024]; size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf);  assert_non_null(strstr(buf, "containers: 1")); /* one disti...*
- `test_visibility_overflow_cursor_and_text_wrap` (line 153) - *size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf);  assert_non_null(strstr(buf, "boxes: 1")); assert_non_null(strstr(buf, "[box...*
- `test_no_box_tree_without_css` (line 195) - *size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf);  assert_non_null(strstr(buf, "visibility=hidden")); assert_non_null(strstr(b...*
- `test_truncation_no_overflow` (line 215) - *pv_box_def b; memset(&b, 0, sizeof b); b.parent_id = -1; b.bsh_color = -1; assert_int_equal(pv_add_box_def(v, &b), PV_OK);  rd_doc *d = build(v, rd...*
- `test_control_bytes_kept_on_one_line` (line 243) - *size_t n = dd_format(d, (char *)guard, cap); assert_int_equal((int)n, (int)full);          /* reports the untruncated length /* NUL within the cap ...*
- `main` (line 267)

#### `test_download.c`
**Path:** `tests/test_download.c`

**Functions:**
- `builder` (line 8)
- `test_should_renderable_types` (line 29)
- `test_should_binary_types` (line 40)
- `test_ext_known_types` (line 51) - *assert_int_equal(dl_should_download(NULL, NULL), 0);          /* missing type renders assert_int_equal(dl_should_download("", NULL), 0); }  static ...*
- `test_ext_unknown_type` (line 62)
- `test_pick_from_disposition_quoted` (line 71) - *assert_string_equal(dl_ext_for_type("text/plain; charset=utf-8"), ".txt"); assert_string_equal(dl_ext_for_type("IMAGE/JPEG"), ".jpg"); assert_strin...*
- `test_pick_from_disposition_ext_form` (line 80)
- `test_pick_from_url_segment` (line 90)
- `test_pick_appends_extension_when_missing` (line 98)
- `test_pick_keeps_existing_extension` (line 107)
- `test_pick_traversal_contained` (line 116)
- `test_pick_fallback_when_empty` (line 128)
- `test_pick_null_out` (line 140)
- `test_pick_overflow_fails_closed` (line 147)
- `test_build_path_basic` (line 157) - *char out[8]; assert_int_equal(dl_pick_name("https://x/y.pdf", NULL, NULL, NULL, sizeof out), DL_ERR_NULL_ARG); assert_int_equal(dl_pick_name("https...*
- `test_build_path_trailing_slash` (line 164)
- `test_build_path_rejects_separator_in_name` (line 171)
- `test_build_path_overflow` (line 178)
- `test_build_path_null_args` (line 185)
- `test_check_size` (line 196) - *assert_int_equal(dl_build_path("/a/very/long/dir", "name.pdf", out, sizeof out), DL_ERR_OVERFLOW); assert_string_equal(out, ""); }  static void tes...*
- `main` (line 203)

#### `test_flex_layout.c`
**Path:** `tests/test_flex_layout.c`

**Functions:**
- `assert_item` (line 24)
- `test_grow_equal` (line 29)
- `test_grow_weighted` (line 38)
- `test_shrink_equal` (line 47)
- `test_shrink_with_min_clamp` (line 56)
- `test_gap_start` (line 66)
- `test_justify_center` (line 75)
- `test_justify_end` (line 84)
- `test_justify_space_between` (line 93)
- `test_justify_space_around` (line 102)
- `test_justify_space_evenly` (line 111)
- `test_space_between_single_item_is_start` (line 121)
- `test_negative_fields_clamped` (line 129)
- `test_flex_zero_items_is_noop` (line 139)
- `test_flex_errors` (line 144)
- `test_grid_columns` (line 156)
- `test_grid_columns_too_narrow_clamps_to_zero` (line 168)
- `test_grid_columns_edges` (line 175)
- `test_grid_cell` (line 185)
- `test_float_pack_left` (line 194)
- `test_float_pack_left_and_right` (line 205)
- `test_float_pack_two_right` (line 217)
- `test_float_pack_edges` (line 228)
- `test_justify_name` (line 241)
- `main` (line 252)

#### `test_form.c`
**Path:** `tests/test_form.c`

**Functions:**
- `test_encode_basic` (line 23) - *NULL name, NULL args).   #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h>  #include <cmocka.h>  ...*
- `test_encode_space_and_reserved` (line 33)
- `test_encode_unreserved_kept` (line 42)
- `test_encode_empty_and_nameless` (line 50)
- `test_encode_overflow_fails_closed` (line 58)
- `test_encode_null_args` (line 66)
- `test_get_relative_action_on_https_base` (line 77) - *assert_int_equal(fm_encode(f, 1, out, sizeof out, NULL), FM_ERR_OVERFLOW); assert_string_equal(out, ""); /* no partial encoding }  static void test...*
- `test_get_absolute_https_action_ignores_base` (line 88)
- `test_get_empty_action_submits_to_base` (line 99)
- `test_get_replaces_existing_query` (line 108)
- `test_get_action_cleaned_of_whitespace` (line 118)
- `test_post_builds_body` (line 129) - *assert_int_equal(p.kind, FM_NAVIGATE); assert_string_equal(p.url, "https://example.com/s?q=new"); }  static void test_get_action_cleaned_of_whitesp...*
- `test_block_http_downgrade` (line 144) - *static void test_post_builds_body(void **state) { (void)state; fm_field f[] = { { "user", "a b" }, { "pass", "p&q" } }; fm_plan p; assert_int_equal...*
- `test_block_foreign_scheme` (line 154)
- `test_block_relative_action_on_local_base` (line 163)
- `test_block_too_many_fields` (line 172)
- `test_block_null_field_name` (line 182)
- `test_build_null_args` (line 191)
- `test_get_no_fields_still_navigates` (line 198)
- `main` (line 206)

#### `test_freebug.c`
**Path:** `tests/test_freebug.c`

**Functions:**
- `test_push_and_read` (line 20) - *name table, reset (array reuse, no leak) and free idempotency. Run under ASan to prove no leak/UAF across reset/free.  include <setjmp.h> include <...*
- `test_empty_and_null_text` (line 45)
- `test_count_cap_fails_closed` (line 58)
- `test_entry_truncated_not_dropped` (line 74)
- `test_total_bytes_cap_fails_closed` (line 92)
- `test_level_clamped` (line 117)
- `test_level_name` (line 128)
- `test_reset_reuses_and_no_leak` (line 139)
- `test_free_idempotent` (line 160)
- `test_push_loc_records_location` (line 174)
- `test_push_loc_null_file_and_negative_nums` (line 196)
- `test_push_loc_file_truncated` (line 213)
- `main` (line 227)

#### `test_freedom.c`
**Path:** `tests/test_freedom.c`

**Functions:**
- `run_freedom` (line 27) - *include <stdarg.h> include <stddef.h> include <stdint.h> include <stdlib.h> include <setjmp.h> include <string.h> include <stdio.h> include <sys/wa...*
- `run_freedom_raw` (line 50) - *Runs the binary with a raw argument string (no implicit --headless), capturing * stdout into OUT_FILE. Used by the --download-pdf tests, which set ...*
- `is_pdf_file` (line 62) - *Runs the binary with a raw argument string (no implicit --headless), capturing * stdout into OUT_FILE. Used by the --download-pdf tests, which set ...*
- `is_png_file` (line 72) - *return 0; }  /* True if path exists and its first bytes are the PDF magic "%PDF". static int is_pdf_file(const char *path) { FILE *f = fopen(path, ...*
- `cleanup_files` (line 81)
- `test_help` (line 88) - *if (f == NULL) return 0; unsigned char magic[8] = {0}; size_t got = fread(magic, 1, 8, f); fclose(f); static const unsigned char png_sig[8] = {0x89...*
- `test_version` (line 97)
- `test_no_args` (line 106)
- `test_local_html` (line 116) - *assert_int_equal(run_freedom("--version", out, sizeof out, &rc), 0); assert_int_equal(rc, 0); assert_non_null(strstr(out, "Freedom")); }  static vo...*
- `test_local_form_renders_inputs` (line 139)
- `test_missing_file` (line 165)
- `test_download_pdf_local` (line 175) - *assert_null(strstr(out, "[hidden"));              /* ...nor is the hidden control  unlink(path); }  static void test_missing_file(void **state) { (...*
- `test_download_pdf_requires_path` (line 202) - *char args[512]; assert_true((size_t)snprintf(args, sizeof args, "--download-pdf=%s %s", pdf, path) < sizeof args); int rc = -1; assert_int_equal(ru...*
- `test_download_png_local` (line 210) - *unlink(path); unlink(pdf); }  /* --download-pdf with no PATH is a usage error (fail closed: never guess a path). static void test_download_pdf_requ...*
- `test_download_png_requires_path` (line 237) - *char args[512]; assert_true((size_t)snprintf(args, sizeof args, "--download-png=%s %s", png, path) < sizeof args); int rc = -1; assert_int_equal(ru...*
- `test_dump_console_shows_output_and_error` (line 247) - *unlink(png); }  /* --download-png with no PATH is a usage error (fail closed: never guess a path). static void test_download_png_requires_path(void...*
- `test_no_dump_console_without_flag` (line 282) - *size_t got = fread(out, 1, sizeof out - 1, o); out[got] = '\0'; fclose(o);  assert_non_null(strstr(out, "Freebug console")); assert_non_null(strstr...*
- `test_dump_dom_prints_render_tree` (line 307) - *-dump-dom prints the agent-readable render tree (header + per-block lines) instead * of the normal text render, and does not run JS.*
- `ballooned` (line 340)
- `test_rejects_http_url` (line 456) - *The relative panel is in flow: at least one box, and no positioned box left it * at the page bottom (the grey-stripe bug had npositioned pushing it...*
- `main` (line 466) - *unlink(path); }  /* --- network policy ---  static void test_rejects_http_url(void **state) { (void)state; char out[512]; int rc; assert_int_equal(...*

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `FREEDOM_BIN` (line 23)
- `OUT_FILE` (line 25)
- `ERR_FILE` (line 26)

#### `test_hostblock.c`
**Path:** `tests/test_hostblock.c`

**Functions:**
- `test_free_null_idempotent` (line 31)
- `test_count_null_set` (line 36)
- `test_load_null_args` (line 44) - *}  static void test_free_null_idempotent(void **state) { (void)state; hb_free(NULL);  /* must not crash }  static void test_count_null_set(void **s...*
- `test_hosts_line_drops_ip` (line 54) - *assert_int_equal(hb_count(NULL, HB_LIST_ALLOW), 0); }  /* --- load: argument validation ---  static void test_load_null_args(void **state) { (void)...*
- `test_various_ip_tokens_ignored` (line 63)
- `test_bare_domain_per_line` (line 72)
- `test_comments_and_blanks` (line 82)
- `test_multiple_tokens_per_line` (line 98)
- `test_no_trailing_newline` (line 106)
- `test_lowercased` (line 117) - *assert_int_equal(hb_count(s, HB_LIST_BLOCK), 3); hb_free(s); }  static void test_no_trailing_newline(void **state) { (void)state; hb_set *s = hb_ne...*
- `test_trailing_dot_trimmed` (line 127)
- `test_invalid_tokens_skipped` (line 138)
- `test_oversize_token_skipped` (line 154)
- `test_underscore_and_hyphen_valid` (line 165)
- `test_dedup_and_accumulate` (line 173)
- `test_lists_independent` (line 184)
- `test_block_covers_subdomains` (line 196) - *hb_free(s); }  static void test_lists_independent(void **state) { (void)state; hb_set *s = hb_new(); assert_int_equal(hb_load(s, "a.com\nb.com\n", ...*
- `test_allow_wins_and_covers_subdomains` (line 209)
- `test_no_lists_allows` (line 223)
- `test_is_allowlisted` (line 230)
- `test_check_fail_open_edges` (line 251)
- `main` (line 265)

#### `test_hostedit.c`
**Path:** `tests/test_hostedit.c`

**Functions:**
- `test_make_line_lowercases` (line 10) - *include <setjmp.h> include <stdarg.h> include <stddef.h> include <stdint.h> include <string.h> include <cmocka.h> include "hostedit.h"*
- `test_make_line_plain_host` (line 17)
- `test_make_line_rejects_path_scheme_garbage` (line 24)
- `test_make_line_rejects_bad_labels` (line 35)
- `test_make_line_null_and_range` (line 46)
- `test_make_line_single_label_ok` (line 55)
- `test_text_has_host` (line 62)
- `test_suggest_prefix_first` (line 75)
- `test_suggest_case_insensitive_and_dedup` (line 91)
- `test_suggest_empty_query_and_cap` (line 100)
- `main` (line 113)

#### `test_html_parse.c`
**Path:** `tests/test_html_parse.c`

**Functions:**
- `test_config_default_is_secure` (line 36) - *static const char DOC_SIMPLE[] = "<!DOCTYPE html><html><head><title>Hello Title</title></head>" "<body><p>Hello World</p></body></html>";  static c...*
- `test_validate_rejects_null` (line 44)
- `test_validate_rejects_empty` (line 50)
- `test_validate_rejects_oversize` (line 56)
- `test_validate_accepts_within_cap` (line 63)
- `test_parse_rejects_null_args` (line 71) - *static void test_validate_rejects_oversize(void **state) { (void)state; hp_config c = hp_config_default(); c.max_bytes = 8; assert_int_equal(hp_val...*
- `test_parse_rejects_oversize` (line 79)
- `test_parse_simple_document` (line 90) - *assert_int_equal(hp_parse(NULL, 5, &c, &doc), HP_ERR_NULL_ARG); assert_int_equal(hp_parse("x", 1, &c, NULL), HP_ERR_NULL_ARG); }  static void test_...*
- `test_scripts_stripped_by_default` (line 115) - *assert_non_null(title); assert_string_equal(title, "Hello Title"); hp_free(title);  size_t blen = 0; char *text = hp_extract_text(doc, &blen); asse...*
- `test_scripts_kept_when_disabled` (line 130)
- `test_event_handlers_stripped_by_default` (line 140)
- `test_event_handlers_kept_when_disabled` (line 149)
- `test_extract_script_list_skips_non_js_type` (line 227) - *A classic script runs only when its type is absent/empty or a JavaScript MIME type. Template/data blocks (text/x-jquery-tmpl, text/html, text/templ...*
- `test_extract_script_list_empty` (line 256) - *assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK);  size_t n = 0; hp_script *s = hp_extract_script_list(doc, &n); assert_non_null(s); assert_int_...*
- `test_extract_stylesheets_basic` (line 300) - *Two applicable <link rel=stylesheet> come back as their RAW hrefs in document * order; noise (rel=icon, link without href, a <style> element) is sk...*
- `test_extract_stylesheets_rel_tokens` (line 327) - *rel matches by whitespace-separated token, case-insensitively: "STYLESHEET" applies; "alternate stylesheet" is an inactive alternate sheet (skipped...*
- `test_extract_stylesheets_none_and_null` (line 377) - *No applicable links => NULL with count 0; NULL doc likewise; the releaser is * idempotent on NULL.*
- `test_extract_stylesheets_caps` (line 394) - *hp_document *doc = NULL; assert_int_equal(hp_parse(LIT("<html><body><p>hi</p></body></html>"), &c, &doc), HP_OK); size_t n = 123; char **s = hp_ext...*
- `test_parse_malformed_does_not_crash` (line 417) - *off += (size_t)snprintf(html + off, buflen - off, "%s", one); hp_config c = hp_config_default(); hp_document *doc = NULL; assert_int_equal(hp_parse...*
- `test_free_null_and_double` (line 429) - */* --- robustness ---  static void test_parse_malformed_does_not_crash(void **state) { (void)state; hp_config c = hp_config_default(); hp_document ...*
- `main` (line 439)

**Macros:**
- `LIT` (line 20)

#### `test_image_decode.c`
**Path:** `tests/test_image_decode.c`

**Functions:**
- `px` (line 64)
- `test_sniff_png` (line 74) - *0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x1...*
- `test_sniff_unsupported` (line 79)
- `test_dimensions_from_ihdr` (line 91) - *An unsupported format (GIF) and garbage both sniff as UNKNOWN; PNG and JPEG * are the only recognised signatures (see test_sniff_png/test_sniff_jpe...*
- `test_dimensions_truncated` (line 99)
- `test_dimensions_non_png` (line 106)
- `test_dimensions_null` (line 113)
- `test_dimensions_ok_bounds` (line 122) - *(void)state; uint32_t w = 0, h = 0; const uint8_t junk[16] = {0}; assert_int_equal(img_png_dimensions(junk, sizeof junk, &w, &h), IMG_ERR_FORMAT); ...*
- `test_fit_landscape_into_square` (line 138) - *(void)state; assert_int_equal(img_dimensions_ok(1, 1), 1); assert_int_equal(img_dimensions_ok(IMG_MAX_DIM, 1), 1); assert_int_equal(img_dimensions_...*
- `test_fit_portrait_into_box` (line 147)
- `test_fit_degenerate` (line 156)
- `test_decode_dimensions_and_stride` (line 168) - *assert_true(h > 99.9 && h < 100.1); }  static void test_fit_degenerate(void **state) { (void)state; double w = 1, h = 1; img_fit(0, 10, 100.0, 100....*
- `test_decode_pixels_premultiplied` (line 180)
- `test_decode_rejects_non_png` (line 192)
- `test_decode_rejects_truncated` (line 202)
- `test_decode_null_args` (line 212)
- `test_pixels_free_idempotent` (line 220)
- `test_format_name` (line 229)
- `test_sniff_jpeg` (line 238) - *memset(&p, 0, sizeof p); img_pixels_free(&p); img_pixels_free(&p); img_pixels_free(NULL); }  static void test_format_name(void **state) { (void)sta...*
- `test_decode_jpeg_dimensions_and_alpha` (line 246)
- `test_decode_dispatch_routes_jpeg_and_png` (line 269)
- `test_decode_dispatch_rejects_unknown` (line 281)
- `test_decode_jpeg_rejects_truncated` (line 289)
- `test_decode_jpeg_rejects_non_jpeg` (line 297)
- `test_decode_jpeg_null_args` (line 304)
- `main` (line 312)

#### `test_js_dom.c`
**Path:** `tests/test_js_dom.c`

**Functions:**
- `setup` (line 40)
- `teardown` (line 51)
- `run` (line 65) - *Evaluates src in the fixture context and returns the result string (owned by * the caller-provided js_result, freed by the caller).*
- `test_install_null_args` (line 79) - *static js_status run(fixture *f, const char *src, js_result *r) { return js_eval(f->ctx, src, strlen(src), r); }  #define EXPECT(f, src, expected) ...*
- `test_get_element_by_id` (line 90) - *} while (0)  /* --- install ---  static void test_install_null_args(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_contex...*
- `test_node_count` (line 98)
- `test_by_class_and_tag` (line 103)
- `test_navigation` (line 111)
- `test_attributes` (line 121)
- `test_document_order` (line 128)
- `test_invalid_handles` (line 137) - *fixture *f = (fixture *)*state; EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'class')", "container box"); EXPECT(f, "dom.getAttribute(dom...*
- `test_methods_are_frozen` (line 147) - *"true"); }  /* --- robustness: bogus handles never crash, just yield null ---  static void test_invalid_handles(void **state) { fixture *f = (fixtu...*
- `test_no_io_with_dom` (line 158) - *}  /* --- the API cannot be hijacked ---  static void test_methods_are_frozen(void **state) { fixture *f = (fixture *)*state; /* Reassigning a meth...*
- `test_document_shim_present` (line 166) - *"function"); /* The sealed object rejects new properties. EXPECT(f, "try{dom.injected=1}catch(e){}; typeof dom.injected", "undefined"); }  /* --- s...*
- `test_query_selector_from_js` (line 173)
- `test_element_matches_closest_query_from_js` (line 187)
- `test_node_identity_is_cached` (line 197)
- `test_element_traversal` (line 204)
- `test_classlist_backs_class_attr` (line 213)
- `test_document_fragment_reparents` (line 223)
- `jQuery` (line 238)
- `test_modern_globals_do_not_throw` (line 256)
- `EXPECT` (line 262)
- `test_url_constructor_parses_components` (line 276) - *WHATWG URL: identity-safe, pure string parsing (no network/IO). This was * Slashdot's first JS error (ReferenceError: URL is not defined).*
- `test_url_search_params` (line 299) - *EXPECT(f, "new URL('https://a.b.com/p?x=1#frag').hash", "#frag"); EXPECT(f, "new URL('https://a.b.com/p').origin", "https://a.b.com"); /* A bare pa...*
- `test_settimeout_chains_across_rounds` (line 323)
- `test_document_title_set_reflects_in_tree` (line 330)
- `test_set_text_content_reflects_in_tree` (line 344)
- `test_set_text_content_detach_is_memory_safe` (line 355)
- `test_document_is_not_io` (line 370)
- `test_create_append_renders_in_tree` (line 379) - */* 'go' is detached but alive: its tag still reads safely. assert_string_equal(r.value, "BUTTON"); js_result_free(&r); EXPECT(f, "document.getEleme...*
- `test_set_attribute_makes_queryable` (line 395)
- `test_element_has_attribute` (line 421)
- `test_element_remove_attribute` (line 427)
- `test_element_src_href_are_strings` (line 437)
- `test_append_cycle_is_rejected` (line 445)
- `test_onload_runs_and_mutates` (line 453)
- `assert_int_equal` (line 458)
- `test_settimeout_flushed_by_pump` (line 466)
- `EXPECT` (line 469)
- `test_inner_html_builds_and_queryable` (line 474)
- `test_storage_is_ephemeral` (line 485) - *"var b=document.getElementById('go').textContent; __fireDeferred();" "b+'/'+document.getElementById('go').textContent", "Go/timed"); }  static void...*
- `test_cookie_and_referrer_leak_nothing` (line 491)
- `test_ambient_apis_do_not_throw` (line 498)
- `set_https_location` (line 510) - *EXPECT(f, "document.referrer", ""); }  static void test_ambient_apis_do_not_throw(void **state) { fixture *f = (fixture *)*state; /* history/locati...*
- `test_location_reads_real_components` (line 515)
- `test_location_pathname_defaults_slash` (line 532)
- `test_location_href_set_captures_raw` (line 540)
- `test_location_replace_sets_replace_flag` (line 554)
- `test_location_assign_and_window_last_wins` (line 566)
- `test_no_nav_request_when_idle` (line 578)
- `test_local_page_captures_nav` (line 588) - *A local (file) page has no https parts but still captures navigation requests, * so the parent can resolve them against the file base.*
- `test_set_location_null_ctx` (line 599)
- `console_fixture` (line 610) - *assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1); assert_string_equal(buf, "sub.html"); }  static void test_set_location...*
- `console_teardown` (line 620)
- `test_console_captures_levels` (line 628)
- `test_console_object_and_throwing_tostring` (line 655)
- `test_console_null_buffer_is_noop` (line 675)
- `test_console_null_ctx` (line 696)
- `test_click_install_null_args` (line 705) - *js_context_free(ctx); dom_free(idx); hp_document_free(doc); }  static void test_console_null_ctx(void **state) { (void)state; fb_buffer log; fb_buf...*
- `test_click_add_event_listener_fires` (line 712) - *(void)state; fb_buffer log; fb_buffer_init(&log); assert_int_equal(jd_install_console(NULL, &log), JD_ERR_NULL_ARG); fb_buffer_free(&log); }  /* --...*
- `test_click_onclick_fires` (line 736) - *"p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_...*
- `test_click_prevent_default` (line 760) - *"b._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_...*
- `test_click_no_handler_allows_default` (line 783) - *"b.onclick = function(e){ e.preventDefault(); b.textContent = 'prevented'; };" "b._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(s...*
- `main` (line 793)

**Macros:**
- `EXPECT` (line 68)

**Structs:**
- `fixture` (line 34)

#### `test_js_env.c`
**Path:** `tests/test_js_env.c`

**Functions:**
- `setup` (line 28)
- `teardown` (line 37)
- `run` (line 46)
- `test_install_null_args` (line 61) - *static js_status run(fixture *f, const char *src, js_result *r) { return js_eval(f->ctx, src, strlen(src), r); }  #define EXPECT(f, src, expected) ...*
- `test_navigator_identity` (line 73) - */* --- install ---  static void test_install_null_args(void **state) { (void)state; assert_int_equal(je_install(NULL, 1920, 1080), JE_ERR_NULL_ARG)...*
- `test_screen_bucketed` (line 91) - *EXPECT(f, "navigator.userAgent.length > 0", "true"); EXPECT(f, "navigator.language", "en-US"); EXPECT(f, "navigator.languages.length", "2"); EXPECT...*
- `test_clocks_coarse` (line 103) - */* --- screen bucketing: real (1680,1050) snaps to 1600x900 ---  static void test_screen_bucketed(void **state) { fixture *f = (fixture *)*state; E...*
- `test_performance_timing_identity_safe` (line 116) - *performance.timing / navigation / getEntries*: present (real analytics read them) and identity-safe -- every timing field is the same fixed epoch (...*
- `test_unforgeable` (line 131) - *fixture *f = (fixture *)*state; EXPECT(f, "typeof performance.timing", "object"); EXPECT(f, "performance.timing.responseStart - performance.timing....*
- `test_screen_edges` (line 145) - *static void test_unforgeable(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "try{navigator.userAgent='x'}catch(e){};" "navigator.userAge...*
- `test_canvas_readback` (line 164) - *assert_int_equal(je_install(ctx, 0, 0), JE_OK); js_result r; const char *probe = "screen.width > 0"; assert_int_equal(js_eval(ctx, probe, strlen(pr...*
- `readback_checksum` (line 205) - *assert_int_equal(js_eval(ctx, det, strlen(det), &r), JS_OK); assert_string_equal(r.value, "true"); js_result_free(&r);  /* audio shares the same po...*
- `test_canvas_unlinkable` (line 220)
- `test_canvas_unforgeable` (line 228)
- `test_coexists_with_dom` (line 251)
- `main` (line 280)

**Macros:**
- `EXPECT` (line 50)

**Structs:**
- `fixture` (line 25) - *include <stddef.h> include <stdint.h> include <stdio.h> include <stdlib.h> include <setjmp.h> include <string.h> include <cmocka.h> include "dom.h"...*

#### `test_js_policy.c`
**Path:** `tests/test_js_policy.c`

**Functions:**
- `test_enabled_fail_closed_on_bad_mode` (line 30)
- `test_mode_from_str` (line 35)
- `test_mode_str_roundtrip` (line 52)
- `main` (line 64)

#### `test_js_sandbox.c`
**Path:** `tests/test_js_sandbox.c`

**Functions:**
- `test_validate_rejects_null` (line 33) - *#include "js_sandbox.h"  /* --- js_limits_default ---  static void test_limits_default_is_secure(void **state) { (void)state; js_limits l = js_limi...*
- `test_validate_rejects_empty` (line 38)
- `test_validate_rejects_oversize` (line 43)
- `test_validate_accepts_within_cap` (line 50)
- `test_context_new_and_free` (line 57) - *static void test_validate_rejects_oversize(void **state) { (void)state; js_limits l = js_limits_default(); l.max_source_bytes = 4; assert_int_equal...*
- `test_context_new_null_out` (line 65)
- `test_eval_arithmetic` (line 72) - *static void test_context_new_and_free(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); ass...*
- `test_eval_string_concat` (line 86)
- `test_eval_syntax_error` (line 98) - *js_context_free(ctx); }  static void test_eval_string_concat(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); assert_int_equal(js...*
- `test_eval_runtime_exception` (line 107)
- `test_no_io_globals` (line 121) - *static void test_eval_runtime_exception(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); assert_int_equal(js_eval_once("throw new...*
- `test_filesystem_access_is_reference_error` (line 134)
- `test_infinite_loop_times_out` (line 147) - *}  static void test_filesystem_access_is_reference_error(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); const char *src = "read...*
- `assert_int_equal` (line 154)
- `test_set_time_budget_applies` (line 161) - *js_set_time_budget lowers the wall-clock cap armed on subsequent evals, so a caller can enforce a single page-wide budget across many evaluations. ...*
- `assert_int_equal` (line 169)
- `test_memory_limit_is_enforced` (line 177)
- `test_result_free_on_zeroed` (line 193) - *Unbounded object allocation exhausts the heap and is denied by the cap. (A doubling string instead trips the engine's max-string-length first, * wh...*
- `test_context_free_null_and_double` (line 202)
- `test_eval_null_args` (line 210)
- `test_loc_parses_named_frame` (line 224) - *static void test_eval_null_args(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); js_result...*
- `test_loc_parses_bare_frame` (line 235)
- `test_loc_file_may_contain_colons` (line 244)
- `test_loc_line_only_sets_col_zero` (line 255)
- `test_loc_truncates_to_cap` (line 264)
- `test_loc_rejects_garbage_and_null` (line 272)
- `test_eval_named_captures_location` (line 287) - *static void test_loc_rejects_garbage_and_null(void **state) { (void)state; char file[16]; int line = 9, col = 9; assert_int_equal(js_loc_from_stack...*
- `test_eval_named_null_filename_defaults` (line 308)
- `test_eval_thrown_primitive_has_no_location` (line 323)
- `main` (line 339)

#### `test_link_nav.c`
**Path:** `tests/test_link_nav.c`

**Functions:**
- `test_null_out` (line 23) - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h>  #include <cmocka.h>  #include "link_nav.h"  st...*
- `test_null_href_blocked` (line 28)
- `test_fragment_is_same_document` (line 36) - */* --- argument handling ---  static void test_null_out(void **state) { (void)state; assert_int_equal(ln_resolve("https://h/", "/x", NULL), LN_ERR_...*
- `test_https_absolute` (line 48) - */* --- fragments / empty ---  static void test_fragment_is_same_document(void **state) { (void)state; assert_int_equal(ln_resolve("https://h.exampl...*
- `test_https_relative` (line 56)
- `test_https_absolute_path_and_parent` (line 64)
- `test_https_blocks_downgrade_and_schemes` (line 75)
- `test_https_scheme_relative` (line 90)
- `test_resolve_long_bundle_target` (line 101) - *Modern bundle URLs exceed the old 4096 target cap (google's xjs URL is 3456 bytes BEFORE resolution; longer ones exist): a link/script href resolvi...*
- `test_href_cleaning` (line 113) - *BEFORE resolution; longer ones exist): a link/script href resolving to > 4096 * bytes must still navigate. static void test_resolve_long_bundle_tar...*
- `test_file_relative` (line 124) - *}  /* --- href cleaning ---  static void test_href_cleaning(void **state) { (void)state; /* Surrounding whitespace and embedded tab/newline/CR are ...*
- `test_file_parent` (line 132)
- `test_file_absolute_path` (line 140)
- `test_file_drops_fragment` (line 148)
- `test_file_base_to_https` (line 156)
- `test_file_base_blocks_schemes_and_scheme_relative` (line 164)
- `test_no_base` (line 178) - *static void test_file_base_blocks_schemes_and_scheme_relative(void **state) { (void)state; assert_int_equal(ln_resolve("/home/u/a.html", "http://h....*
- `test_overflow_blocked` (line 194) - *(void)state; assert_int_equal(ln_resolve(NULL, "https://h.example/x", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_int_equal(R.kind...*
- `test_block_reasons` (line 206) - */* --- overflow fails closed ---  static void test_overflow_blocked(void **state) { (void)state; char big[LN_MAX_TARGET + 64]; memcpy(big, "https:/...*
- `test_block_reason_text` (line 233)
- `test_fragment_capture` (line 243) - *assert_int_equal(ln_resolve("https://h.example/", "/x", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_int_equal(R.reason, LN_BLOCK_N...*
- `main` (line 272)

#### `test_local_store.c`
**Path:** `tests/test_local_store.c`

**Functions:**
- `roundtrip_raw` (line 29) - *#include <cmocka.h>  #include "local_store.h"  static const uint8_t KEY[LS_KEY_LEN] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,...*
- `test_roundtrip_aes` (line 47)
- `test_roundtrip_chacha` (line 49)
- `test_empty_plaintext` (line 52) - *assert_int_equal(blob_len, LS_OVERHEAD + (sizeof PT - 1));  assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_OK); assert_int_equal...*
- `test_wrong_key` (line 66) - *static void test_empty_plaintext(void **s) { (void)s; uint8_t *blob = NULL, *out = NULL; size_t blob_len = 0, out_len = 99; assert_int_equal(ls_sea...*
- `tamper_at` (line 84) - *size_t blob_len = 0, out_len = 1; assert_int_equal( ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len), LS_OK);...*
- `test_tamper_ciphertext` (line 98)
- `test_tamper_tag` (line 100)
- `test_tamper_nonce` (line 101)
- `test_tamper_salt` (line 102)
- `test_tamper_aead_id` (line 103)
- `test_nondeterministic` (line 106) - *blob[off] ^= 0x01; ls_status st = ls_open(KEY, blob, blob_len, &out, &out_len); assert_true(st == LS_ERR_AUTH || st == LS_ERR_FORMAT); assert_null(...*
- `test_passphrase_roundtrip` (line 120) - *static void test_nondeterministic(void **s) { (void)s; uint8_t *a = NULL, *b = NULL; size_t al = 0, bl = 0; assert_int_equal(ls_seal(KEY, LS_AEAD_A...*
- `test_derive_key` (line 148) - *assert_memory_equal(out, PT, sizeof PT - 1); ls_free(out, out_len);  const char *wrong = "Tr0ub4dor&3"; uint8_t *out2 = (uint8_t *)0x1; size_t out2...*
- `test_format_errors` (line 165) - *const char *pass = "passphrase"; uint8_t salt1[LS_SALT_LEN], salt2[LS_SALT_LEN]; memset(salt1, 0xAA, sizeof salt1); memset(salt2, 0xBB, sizeof salt...*
- `test_null_and_limits` (line 180)
- `main` (line 192)

#### `test_net_realm.c`
**Path:** `tests/test_net_realm.c`

**Functions:**
- `test_classify_host_onion` (line 21) - *.i2p only via I2P) and fail-closed (missing proxy or unclassifiable URL => blocked).   #include <setjmp.h> #include <stdarg.h> #include <stddef.h> ...*
- `test_classify_host_i2p` (line 29)
- `test_classify_host_clearnet` (line 36)
- `test_classify_host_lookalikes` (line 44) - *static void test_classify_host_i2p(void **state) { (void)state; assert_int_equal(nr_classify_host("stats.i2p"), NR_I2P); assert_int_equal(nr_classi...*
- `test_classify_host_edges` (line 53)
- `test_classify_url` (line 66) - *}  static void test_classify_host_edges(void **state) { (void)state; assert_int_equal(nr_classify_host(NULL), NR_CLEARNET); assert_int_equal(nr_cla...*
- `test_route_onion` (line 78) - */* --- nr_classify_url ---  static void test_classify_url(void **state) { (void)state; assert_int_equal(nr_classify_url("https://abc.onion/path?q=1...*
- `test_route_i2p` (line 87)
- `test_route_clearnet` (line 95)
- `test_route_null_blocked` (line 109)
- `test_realm_allows_http` (line 117) - *assert_int_equal(nr_route_for("https://example.com/", direct), NR_ROUTE_DIRECT); assert_int_equal(nr_route_for("https://example.com/", tor_no_torif...*
- `test_names` (line 125)
- `main` (line 139)

#### `test_os_sandbox.c`
**Path:** `tests/test_os_sandbox.c`

**Functions:**
- `test_policy_allows_safe` (line 42) - *#include <stdlib.h> #include <linux/audit.h> #include <sys/mman.h> #include <sys/prctl.h> #include <sys/resource.h> #include <sys/socket.h> #includ...*
- `test_policy_denies_dangerous` (line 50)
- `test_policy_denies_io_uring` (line 64) - *io_uring is a seccomp-bypass primitive (its IORING_OP_* operations are dispatched without re-entering the syscall entry point the BPF filters), so ...*
- `test_policy_size` (line 70)
- `test_harden_kills_denied_syscall` (line 79) - *(void)state; assert_false(os_policy_allows(__NR_io_uring_setup)); assert_false(os_policy_allows(__NR_io_uring_enter)); assert_false(os_policy_allow...*
- `test_harden_allows_permitted_syscall` (line 96) - *assert_true(pid >= 0); if (pid == 0) { if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98); (void)syscall(__NR_getpid); /* allowed: must survive (...*
- `test_harden_errno_denies_with_eperm` (line 112) - *pid_t pid = fork(); assert_true(pid >= 0); if (pid == 0) { if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98); long p = syscall(__NR_getpid); _ex...*
- `test_harden_kills_io_uring_setup` (line 130) - *KILL: io_uring_setup (the mandatory entry point of the whole subsystem -- no ring exists without it) must be killed with SIGSYS. Proves a compromis...*
- `test_prot_allowed_wx` (line 151) - *Pure mirror: mmap/mprotect are members of the allowlist but lose the request * when it asks for PROT_EXEC; other syscalls keep their membership dec...*
- `test_harden_blocks_exec_mmap` (line 162) - *Pure mirror: mmap/mprotect are members of the allowlist but lose the request * when it asks for PROT_EXEC; other syscalls keep their membership dec...*
- `test_harden_blocks_exec_mprotect` (line 182) - *long rw = syscall(__NR_mmap, (void *)0, (size_t)4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0); if (rw == -1) _exit(60); ...*
- `test_no_dump_undumpable` (line 214) - *Probed BEFORE seccomp so prctl/getrlimit are still reachable: after os_no_dump * the process is undumpable and the core-file limit is zero.*
- `test_landlock_abi_present` (line 232) - *if (pid == 0) { if (os_no_dump() != OS_OK) _exit(98); if (prctl(PR_GET_DUMPABLE) != 0) _exit(70); struct rlimit rl; if (getrlimit(RLIMIT_CORE, &rl)...*
- `test_landlock_deny_all` (line 239) - *int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFEXITED(st)); assert_int_equal(WEXITSTATUS(st), 42); }  /* --- Landlock file...*
- `test_landlock_allow_read` (line 257) - *allow-read: a read rule on a temp dir lets reads inside through and blocks * everything else.*
- `net_ns_inode` (line 304) - *The pure flag set: the worker requests an isolated network (no remote access), * a user namespace (the unprivileged enabler), and IPC + UTS isolati...*
- `suite` (line 313)
- `main` (line 334)

**Macros:**
- `_GNU_SOURCE` (line 13)

#### `test_page_view.c`
**Path:** `tests/test_page_view.c`

**Functions:**
- `parse` (line 27) - *#include <stdint.h> #include <stdlib.h> #include <setjmp.h> #include <string.h> #include <cmocka.h>  #include "box_style.h" #include "css.h" #inclu...*
- `find_text` (line 35) - *#include "dom.h" #include "flex_layout.h" #include "html_parse.h" #include "page_view.h"  /* Parse helper: aborts the test on parse failure. Caller...*
- `find_image` (line 44) - *assert_non_null(doc); return doc; }  /* Finds the i-th run whose collapsed text equals `text`; NULL if none. static const pv_run *find_text(const p...*
- `test_new_is_empty` (line 53) - *} return NULL; }  /* Finds the first image run whose src equals `src`; NULL if none. static const pv_run *find_image(const pv_view *v, const char *...*
- `test_append_copies_fields` (line 62)
- `test_append_image_copies_fields` (line 89)
- `test_append_image_null_args` (line 105)
- `test_append_transcodes_latin1` (line 121) - *A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8, recovering accents from a ...*
- `test_append_transcodes_word` (line 131) - *A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8, recovering accents from a ...*
- `test_append_transcodes_cp1252_quotes` (line 142) - *Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls): * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each).*
- `test_append_undefined_cp1252_is_qmark` (line 152) - *Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls): * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each...*
- `test_append_valid_utf8_passthrough` (line 162) - *pv_free(v); }  /* Undefined Windows-1252 positions (0x81 here) have no glyph and still fail to '?'. static void test_append_undefined_cp1252_is_qma...*
- `test_append_null_args` (line 169)
- `test_free_null_and_double` (line 177)
- `test_build_null_args` (line 186) - *pv_view *v = pv_new(); assert_int_equal(pv_append(NULL, PV_TEXT, 0, 0, "x", NULL), PV_ERR_NULL_ARG); assert_int_equal(pv_append(v, PV_TEXT, 0, 0, N...*
- `test_build_plain_text` (line 195)
- `test_build_heading_level` (line 208)
- `test_build_inline_emphasis` (line 226) - *Inline emphasis: <b>/<strong> set bold, <i>/<em> set italic, on the wrapped run * only; surrounding text stays plain. Nested b>i is both.*
- `test_build_unordered_list` (line 267) - *Unordered list: each <li>'s first run is prefixed with a bullet marker and * carries list depth 1.*
- `test_build_ordered_and_nested_list` (line 285) - *assert_int_equal(pv_build(doc, &v), PV_OK);  const pv_run *a = find_text(v, "\xE2\x80\xA2 apple"); /* "* apple" assert_non_null(a); assert_int_equa...*
- `test_build_table_grid` (line 308) - *A table becomes a grid: each cell is one collected text run sharing the table's * cont_id, with the column count = widest row. <th> cells are bold.*
- `test_build_table_flattens_cell` (line 342) - *Cell inner markup is flattened into the cell's text and not re-emitted as a * separate run; the column count comes from the widest row.*
- `test_build_bgcolor_attr_fallback` (line 478) - *Legacy bgcolor attribute is the background fallback when no CSS background won (like <font color> for the foreground). Hacker News' orange bar and ...*
- `test_build_nested_table_not_flattened` (line 493)
- `test_build_link_with_href` (line 542)
- `test_build_block_break_between_paragraphs` (line 561)
- `test_build_skips_script_and_style` (line 573)
- `test_build_inline_link_no_break_within_paragraph` (line 587)
- `test_build_image_with_dims` (line 605)
- `test_build_image_unknown_dims` (line 622)
- `test_build_image_px_and_tracking_dims` (line 637)
- `test_build_image_in_skipped_subtree_ignored` (line 659)
- `test_build_noscript_shown_when_js_off` (line 672)
- `test_build_noscript_hidden_when_js_on` (line 685)
- `test_build_image_without_src_ignored` (line 698)
- `test_build_empty_document` (line 712)
- `test_set_color_model` (line 727) - *The pure model defaults a run's author color to -1 (none); pv_set_color sets it * on the most recent run and is a safe no-op on an empty view.*
- `test_build_author_color` (line 749) - *pv_build extracts the author foreground color: inline style "color:" and the legacy <font color>; the nearest ancestor that sets a color wins (inhe...*
- `test_build_combinator_selectors` (line 796) - *Descendant (`div p`) and child (`nav > a`) combinators from a <style> sheet * resolve through the real DOM ancestor chain.*
- `test_build_flex_container` (line 834) - *pv_build records the nearest author flex/grid container per run: its id, display, and parsed gap/justify/columns. Runs of one container share the i...*
- `test_build_flex_wrap_align_row_gap` (line 872) - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) resolve through * the same cascade and thread through the same run fields as the ...*
- `test_build_flex_item_values` (line 913) - *Stage 3: each run carries the flex ITEM's own resolved values (the direct child of the container on the run's ancestor chain: grow/shrink/basis x10...*
- `test_build_float_threading` (line 976) - *float.md: a run inside a floated block carries that block's side + a stable float_id grouping all its runs; two floated siblings get distinct ids; ...*
- `test_build_flex_whitespace_not_item` (line 1020) - *CSS: whitespace directly inside a flex/grid container creates NO anonymous item (the source newlines between <p> items must not become layout colum...*
- `test_build_inline_whitespace_kept` (line 1076) - *The separator space BETWEEN two inline elements is content, not an anonymous box: * it flows mid-block (no break) and must keep being emitted.*
- `test_build_cont_item_identity` (line 1098) - *Container-item identity: inline fragments of the SAME direct child share one cont_item ordinal (they are one flex/grid item and must flow together ...*
- `test_build_grid_container` (line 1163)
- `test_build_grid_columns_from_sheet` (line 1205)
- `test_container_defaults` (line 1245) - *pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK);  const pv_run *x = find_text(v, "x"); assert_non_null(x); assert_int_equal(x->cont_d...*
- `test_build_box_leaf_inline` (line 1293) - *A leaf block's own box: vertical margins override the UA, horizontal padding + * a fixed width inset and cap the content. No centering without marg...*
- `test_box_defaults_and_setter` (line 1316) - *A run with no author box carries the neutral defaults; pv_set_box fixes the * last run and is NULL-safe.*
- `test_build_boxdeco_border_padding` (line 1346) - *pv_view *w = pv_new(); assert_int_equal(pv_append(w, PV_TEXT, 0, 0, "x", NULL), PV_OK); pv_set_box(w, 12, 8, 500, 1, 40, 4); assert_int_equal(pv_at...*
- `test_build_boxdeco_shadow_outline` (line 1373)
- `test_build_boxdeco_visibility_overflow_cursor` (line 1396)
- `test_build_cursor_alone_triggers_box` (line 1421) - *A block that sets ONLY cursor (no other box property) still registers a box: the trigger for a box-def entry must include visibility/overflow/curso...*
- `test_build_boxdeco_dims_alone_trigger_box` (line 1476) - *2026-07-10: a block that sets ONLY min-width / min-height / max-height / height / aspect-ratio (no other box property) still registers a box: those...*
- `test_build_text_overflow_and_word_break` (line 1521) - *assert_int_equal(bd->box_h, 80);  const pv_run *e = find_text(v, "E"); assert_non_null(e); const pv_box_def *be = pv_box_at(v, (size_t)e->block_id)...*
- `test_build_boxdeco_defaults_no_box` (line 1545)
- `test_build_boxdeco_sibling_blocks_distinct_ids` (line 1559)
- `test_build_boxdeco_shared_id_within_block` (line 1577)
- `test_build_box_tree_textless_wrapper` (line 1640) - *A text-less wrapper (a card whose only child is a body div with the text) owns no run, yet its box def must still exist and be the body box's paren...*
- `test_build_box_tree_empty_no_box` (line 1665) - *const pv_box_def *bd = pv_box_at(v, (size_t)body->block_id); assert_non_null(bd); assert_int_equal(bd->pad_t, 9); int card_id = bd->parent_id; asse...*
- `find_input` (line 1677) - */* A page with no author box has an empty box tree (default render byte-identical). static void test_build_box_tree_empty_no_box(void **state) { (v...*
- `test_build_search_form_get` (line 1686) - *pv_free(v); hp_document_free(doc); }  /* Finds the first PV_INPUT run whose name equals `name`; NULL if none. static const pv_run *find_input(const...*
- `test_build_form_post_and_hidden` (line 1719)
- `test_build_textarea_value` (line 1753)
- `test_build_control_without_form` (line 1769)
- `test_build_two_forms_distinct_groups` (line 1782)
- `test_build_pseudo_classes_and_siblings` (line 1842) - *Pseudo-classes + sibling combinators (Hito 23b-9) resolve through the real pipeline: page_view must feed the css engine each element's sibling cont...*
- `test_build_table_cell_author_styles` (line 1897) - *Collected DATA-table cells resolve author styles too (found via --dump-dom: the cell path never called resolve_context, so td{color} / zebra tr:nth...*
- `test_build_style_cache_distinct_siblings` (line 1957) - *Regression for pv_style_cache (page_view.c): resolve_context()/in_hidden_subtree() now memoize cch_element_style() per element pointer so a shared ...*
- `test_build_text_align_and_font_size` (line 1999) - *text-align and font-size resolve into the new run fields, from both a <style> * sheet and inline style=.*
- `test_build_text_decoration` (line 2046) - *text-decoration resolves into text_decoration from a <style> sheet and inline * style=, inherits to descendant text, and an inline `none` drops a l...*
- `test_build_css_bold_and_inline_wins` (line 2069) - *pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); assert_int_equal(find_text(v, "struck ")->text_decoration, CSS_DECO_LINE_THROUGH); a...*
- `test_build_display_none_hidden` (line 2088) - *"<p class='b'>strongish</p></body>"); pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *t = find_text(v, "t"); assert_no...*
- `test_build_styled_external_css` (line 2111) - *External pre-fetched CSS (Hito 27) feeds the same cascade as the document's <style>: an extern rule applies (presentation and display:none alike); ...*
- `test_build_reader_skips_boilerplate` (line 2137) - *Reader (distraction-free) mode skips nav/header/footer/aside boilerplate but * keeps the main article content; with reader off, the boilerplate is ...*
- `test_set_node_id_model` (line 2165) - *The setter is a no-op when the view is empty or NULL, and it writes to the * most recently appended run otherwise.*
- `test_build_node_id_matches_dom_index` (line 2181) - *Stage 0 keystone: every emitted run carries the document-order element id of its source element, matching the id that dom_build assigns to the same...*
- `test_set_text_style_model` (line 2219)
- `main` (line 2238)

#### `test_pdf_export.c`
**Path:** `tests/test_pdf_export.c`

**Functions:**
- `pagination` (line 8)
- `test_basename_maps_spaces_and_reserved` (line 30)
- `test_basename_rejects_path_separators` (line 38)
- `test_basename_neutralizes_traversal` (line 48)
- `test_basename_dotdot_only_falls_back` (line 56)
- `test_basename_trims_edges` (line 63)
- `test_basename_collapses_underscores` (line 71)
- `test_basename_control_bytes_mapped` (line 78)
- `test_basename_non_ascii_mapped` (line 86)
- `test_basename_empty_and_null_fall_back` (line 95)
- `test_basename_all_separators_fall_back` (line 104)
- `test_basename_length_bound` (line 111)
- `test_basename_null_out_and_zero_size` (line 122)
- `test_basename_overflow_fails_closed` (line 129)
- `test_build_path_basic` (line 138) - *(void)state; char out[8]; assert_int_equal(pe_safe_basename("x", NULL, sizeof out), PE_ERR_NULL_ARG); assert_int_equal(pe_safe_basename("x", out, 0...*
- `test_build_path_trailing_slash` (line 145)
- `test_build_path_hostile_title_contained` (line 152)
- `test_build_path_empty_title_fallback` (line 161)
- `test_build_path_overflow_fails_closed` (line 168)
- `test_build_path_null_args` (line 175)
- `test_build_path_ext_png` (line 185) - *char out[16]; assert_int_equal(pe_build_path("/a/very/long/dir", "name", out, sizeof out), PE_ERR_OVERFLOW); assert_string_equal(out, ""); }  stati...*
- `test_build_path_ext_null_ext` (line 193)
- `test_build_path_ext_hostile_title_contained` (line 201)
- `test_build_path_ext_overflow_fails_closed` (line 212)
- `test_paginate_single_page` (line 222) - *PE_EXT_PNG, out, sizeof out), PE_OK); assert_string_equal(out, "/safe/dir/etc_passwd.png"); assert_null(strstr(out + strlen("/safe/dir"), "..")); }...*
- `test_paginate_breaks_without_splitting` (line 237)
- `test_paginate_oversized_row_not_split` (line 251)
- `test_paginate_preserves_gaps` (line 263)
- `test_paginate_invalid_args` (line 275)
- `main` (line 289)

#### `test_render_doc.c`
**Path:** `tests/test_render_doc.c`

**Functions:**
- `caps_images_on` (line 27)
- `first_kind` (line 35) - *#include "flex_layout.h" #include "page_view.h" #include "render_doc.h" #include "render_policy.h"  static const char TOP[] = "https://example.com/...*
- `test_build_null_out` (line 43) - *rdp_caps c = rdp_caps_safe(); c.images = true; return c; }  /* First block of a given kind, or NULL. static const rd_block *first_kind(const rd_doc...*
- `test_build_null_view_is_empty` (line 50)
- `test_heading_paragraph_link` (line 63) - *}  static void test_build_null_view_is_empty(void **state) { (void)state; rd_doc *d = NULL; assert_int_equal(rd_build(NULL, rdp_caps_safe(), TOP, &...*
- `test_emphasis_propagates` (line 94) - *Inline emphasis flags (bold/italic) carry from the run to the block, on text and * link blocks alike, and are independent of caps (structure, not a...*
- `test_image_off_emits_notice_and_blocked` (line 124) - *assert_int_equal(rd_at(d, 0)->italic, 0); assert_int_equal(rd_at(d, 1)->bold, 1); assert_int_equal(rd_at(d, 1)->italic, 0); assert_int_equal(rd_at(...*
- `test_no_images_no_notice` (line 149)
- `test_image_on_allows_normal` (line 163) - *static void test_no_images_no_notice(void **state) { (void)state; pv_view *v = pv_new(); assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "just text", ...*
- `test_image_on_resolves_relative_src` (line 182) - *A relative src ("/logo.png") is not an invalid URL: it resolves against the top-level document. The decision must allow it and the stored href must...*
- `test_image_on_resolves_doc_relative_src` (line 198) - *A document-relative src ("logo.png", no leading slash) resolves against the * page's directory, too.*
- `test_image_on_blocks_tracker` (line 211)
- `test_image_on_blocks_non_https` (line 224)
- `test_href_sanitised` (line 254) - *static void test_image_on_local_top_fails_closed(void **state) { (void)state; pv_view *v = pv_new(); assert_int_equal(pv_append_image(v, 0, 0, "", ...*
- `test_kind_name_total` (line 271) - *pv_view *v = pv_new(); /* pv_append stores the href verbatim; render_doc must make it paint-safe. const char bad[] = { 'h', 't', 't', 'p', 's', ':'...*
- `test_image_label_total` (line 281)
- `test_free_null_and_double` (line 294)
- `test_author_color_gated_by_css` (line 305) - *Author colors are presentation gated by caps.css (Privacy by Default off): the * run's fg_rgb is dropped to -1 unless author CSS is enabled.*
- `test_text_overflow_word_break_gated_by_css` (line 335) - */* CSS on: both colors carried through. rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = ...*
- `test_text_ext_2026_07_10_batch_gated_by_css` (line 369) - *2026-07-10 batch: tab_size / direction / font_variant / list_style_pos travel the same caps.css gate as the other text extensions (off by default; ...*
- `test_input_passthrough` (line 405) - *caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = first_kind(d, RD_PARAGRAPH); assert_non_null(p); assert_int_equal(p->tab_...*
- `test_input_label_total` (line 440)
- `test_container_carried_by_default` (line 454) - *The author flex/grid container annotation is structure, not styling: it is * carried regardless of caps.css (layout applies by default), with its p...*
- `test_cont_item_carried_by_default` (line 486) - *rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = first_kind(d, RD_PARAGRAPH); assert_non_...*
- `test_float_carried_by_default` (line 519) - *float.md: float_side/float_id/float_clear are layout structure, carried regardless of * caps.css; a run that never got pv_set_float keeps the unset...*
- `test_flex_item_carried_by_default` (line 551)
- `test_flex_wrap_align_row_gap_carried_by_default` (line 600) - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) are structure * like the rest of the cont_ and flex_ fields: carried regardless o...*
- `test_block_tag_total` (line 631)
- `test_node_id_carried_by_default` (line 668) - *Stage 0 keystone: node_id is structure, so it is copied regardless of the * caps.css gate (unlike block_id, which exists only when author styling i...*
- `main` (line 680)

#### `test_render_policy.c`
**Path:** `tests/test_render_policy.c`

**Functions:**
- `test_caps_safe_is_all_off` (line 17) - *Pure policy logic: no I/O. Build: make test   ;   ASan: make asan   #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h>...*
- `test_caps_zero_value_is_safe` (line 25)
- `test_tracking_pixel_tiny` (line 36) - *The zero value of the struct must equal the safe baseline: insecure config * is not representable as a default. rdp_caps z = {0}; rdp_caps s = rdp_...*
- `test_tracking_pixel_zero_area` (line 44)
- `test_tracking_pixel_normal` (line 51)
- `test_tracking_pixel_unknown` (line 61)
- `test_image_disabled_by_default` (line 71) - *classified as a tracker by the size heuristic. assert_int_equal(rdp_is_tracking_pixel(1, 300), 0); assert_int_equal(rdp_is_tracking_pixel(800, 600)...*
- `caps_images_on` (line 89) - *Images off: even a perfectly valid same-site image is blocked, and the URL * is not even consulted (a bogus URL still yields BLOCK_DISABLED). asser...*
- `test_image_allow_same_site` (line 95)
- `test_image_allow_cross_site_when_enabled` (line 107)
- `test_image_block_tracker` (line 118)
- `test_image_block_scheme` (line 133)
- `test_image_block_invalid` (line 141)
- `test_image_disabled_precedence` (line 164) - *Disabled capability beats every other reason: a tracker URL with images off is * reported as DISABLED, not TRACKER (the gate short-circuits first).*
- `test_img_reason_total_and_stable` (line 173) - *Disabled capability beats every other reason: a tracker URL with images off is * reported as DISABLED, not TRACKER (the gate short-circuits first)....*
- `test_images_warning_present` (line 188)
- `main` (line 197)

#### `test_renderer.c`
**Path:** `tests/test_renderer.c`

**Functions:**
- `test_render_basic` (line 26)
- `test_render_strips_script` (line 38)
- `test_render_null_args` (line 47)
- `test_render_too_large` (line 54)
- `test_render_binary_does_not_crash_parent` (line 63) - *(void)state; rd_result r; assert_int_equal(rd_render_html(NULL, 10, &r), RD_ERR_NULL_ARG); assert_int_equal(rd_render_html("x", 1, NULL), RD_ERR_NU...*
- `test_render_multiple_independent` (line 74) - *}  /* The parent must survive arbitrary/binary input: isolation in action. static void test_render_binary_does_not_crash_parent(void **state) { (vo...*
- `test_result_free_null_and_double` (line 83)
- `main` (line 92)

#### `test_request_policy.c`
**Path:** `tests/test_request_policy.c`

**Functions:**
- `test_host_of_basic` (line 17) - *Pure policy logic: no I/O. Build: make test   ;   ASan: make asan   #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h>...*
- `test_host_of_invalid` (line 28)
- `test_host_of_overflow` (line 36)
- `test_site_of` (line 44) - *(void)state; char h[256]; assert_int_equal(rp_host_of("example.com", h, sizeof h), -1); /* no scheme assert_int_equal(rp_host_of("https:///path", h...*
- `test_site_of_multi_suffix` (line 57)
- `test_site_of_psl` (line 70) - *}  static void test_site_of_multi_suffix(void **state) { (void)state; char s[256]; assert_int_equal(rp_site_of("example.co.uk", s, sizeof s), 0); a...*
- `test_same_site` (line 90) - *assert_int_equal(rp_site_of("a.blog.github.io", s, sizeof s), 0); assert_string_equal(s, "blog.github.io"); /* Wildcard rule "*.ck": bar.ck is the ...*
- `test_evaluate_allow_same_site` (line 104) - *static void test_same_site(void **state) { (void)state; assert_int_equal(rp_same_site("https://example.com/", "https://example.com/a"), 1); assert_...*
- `test_evaluate_block_third_party` (line 111)
- `test_evaluate_block_scheme` (line 119)
- `test_evaluate_block_invalid` (line 127)
- `main` (line 138)

#### `test_secure_fetch.c`
**Path:** `tests/test_secure_fetch.c`

**Functions:**
- `test_user_agent_default_when_unset` (line 35) - */* --- sf_config_default ---  static void test_config_default_is_secure(void **state) { (void)state; sf_config c = sf_config_default(); assert_int_...*
- `test_user_agent_uses_override` (line 41)
- `test_url_rejects_null` (line 49) - *static void test_user_agent_default_when_unset(void **state) { (void)state; assert_string_equal(sf_user_agent_or_default(NULL), SF_DEFAULT_USER_AGE...*
- `test_url_rejects_plain_http` (line 54)
- `test_url_rejects_dangerous_schemes` (line 59)
- `test_url_accepts_https` (line 69)
- `test_tls_rejects_12` (line 77) - *assert_int_equal(sf_validate_url("javascript:alert(1)"), SF_ERR_INVALID_URL); assert_int_equal(sf_validate_url("data:text/html,<b>x"), SF_ERR_INVAL...*
- `test_tls_rejects_older_and_garbage` (line 82)
- `test_tls_accepts_13` (line 91)
- `test_group_rejects_classical` (line 98) - *(void)state; assert_int_equal(sf_check_tls_version("TLSv1.1"), SF_ERR_TLS_VERSION); assert_int_equal(sf_check_tls_version("TLSv1"), SF_ERR_TLS_VERS...*
- `test_group_rejects_pure_pq` (line 105)
- `test_group_accepts_hybrid` (line 112)
- `test_chain_strict_rejects_classical` (line 121) - *(void)state; /* Pure PQ has no classical fallback: rejected by design. assert_int_equal(sf_check_group_is_pq("MLKEM768"), SF_ERR_KEM_NOT_PQ); asser...*
- `test_chain_strict_accepts_pq` (line 130)
- `test_chain_hybrid_allows_classical` (line 138)
- `test_chain_rejects_sha1_in_any_policy` (line 146)
- `test_chain_permissive_allows_weak_certs` (line 155)
- `test_chain_rejects_weak_rsa` (line 168)
- `test_chain_rejects_null` (line 176)
- `test_enforce_all_good_hybrid` (line 190)
- `test_enforce_checks_version_first` (line 196)
- `test_enforce_checks_group_after_version` (line 205)
- `test_enforce_fails_closed_on_null_chain` (line 213)
- `test_enforce_strict_requires_pq_chain` (line 220)
- `test_enforce_allow_classical_ke` (line 233)
- `test_enforce_allowlisted_insecure` (line 253) - *The allowlist override: the user's sovereign per-host escape hatch for sites below Freedom's elevated standard. Tolerates TLS 1.2, a classical KE, ...*
- `test_redirect_code_recognizes_3xx` (line 274) - *But authenticity is never waived: a non-inspectable chain still fails closed, * and anything below TLS 1.2 is still refused. assert_int_equal(sf_en...*
- `test_redirect_code_rejects_others` (line 283)
- `test_location_parses_value` (line 294) - *assert_true(sf_is_redirect_code(307)); assert_true(sf_is_redirect_code(308)); }  static void test_redirect_code_rejects_others(void **state) { (voi...*
- `test_location_is_case_insensitive_and_trims` (line 302)
- `test_location_rejects_non_location_and_empty` (line 312)
- `test_location_rejects_overflow` (line 324)
- `test_resolve_absolute_https` (line 333) - *SF_ERR_INVALID_URL); assert_int_equal(sf_parse_location_header("Location:    \r\n", out, sizeof out), SF_ERR_INVALID_URL); assert_int_equal(sf_pars...*
- `test_resolve_refuses_http_downgrade` (line 341)
- `test_resolve_refuses_dangerous_schemes` (line 348)
- `test_resolve_scheme_relative` (line 359)
- `test_resolve_absolute_path` (line 367)
- `test_resolve_relative_path` (line 379)
- `test_resolve_null_args` (line 391)
- `test_response_free_on_zeroed` (line 402) - *out, sizeof out), SF_OK); assert_string_equal(out, "https://h.example/foo"); }  static void test_resolve_null_args(void **state) { (void)state; cha...*
- `test_response_free_releases_location` (line 411)
- `test_get_follow_null_args` (line 425)
- `test_get_null_args` (line 434)
- `test_post_null_args` (line 443)
- `main` (line 467)

#### `test_tab.c`
**Path:** `tests/test_tab.c`

**Functions:**
- `setup_loaded` (line 40)
- `teardown` (line 51)
- `expect_eval` (line 62) - *state = f; return 0; }  static int teardown(void **state) { fixture *f = (fixture *)*state; if (f != NULL) { tab_close(f->t); free(f); } return 0; ...*
- `test_open_close` (line 72) - *return 0; }  /* Evaluates js and asserts the (non-exception) string result. static void expect_eval(tab *t, const char *js, const char *expected) {...*
- `test_open_null` (line 82)
- `test_load_basic` (line 89) - *tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); assert_non_null(t); assert_true(tab_alive(t)); assert_true(tab_child_pid(t) > 0); tab_close(...*
- `test_load_returns_view_with_link` (line 107) - *The structured display list must survive the IPC round-trip: a heading and a * link with its href arrive intact in p.view.*
- `test_load_returns_image_run` (line 134) - *An <img> must survive the IPC round-trip as a PV_IMAGE run carrying its src, * alt text, and declared dimensions (so render_policy can later gate it).*
- `test_load_carries_author_color` (line 165) - *An author color extracted in the confined child must survive the IPC round-trip * as the run's fg_rgb (so the parent can apply it once CSS is enabl...*
- `test_load_carries_flex_item` (line 192) - *Stage 3: the per-item flex values resolved by the worker must survive the IPC * round-trip (write_view/read_view), so the GUI's flex layout can hon...*
- `test_load_carries_flex_wrap_align_row_gap` (line 236) - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) survive the worker round-trip (write_view/read_view serialize the 4 new fields in...*
- `test_load_carries_float` (line 276) - *float.md over IPC: float_side/float_id/float_clear survive the worker round-trip * (write_view/read_view serialize them in the same order on both s...*
- `test_load_carries_visibility_overflow_cursor_and_text_wrap` (line 319) - *visibility/overflow/cursor (box-level) and text-overflow/word-break (run-level) survive the worker round-trip -- write_view/read_view serialize the...*
- `test_load_carries_node_id` (line 403) - *Stage 0 keystone: the document-order element id assigned by the child must survive the IPC round-trip, so the parent can map a painted block back t...*
- `test_click_runs_handler_and_returns_view` (line 437) - *Stage 4 dispatcher: a click on a node with a JS handler mutates the DOM, and the * new view is returned over IPC with the mutation reflected.*
- `test_load_carries_box_decoration` (line 478) - *Box-engine identity + decoration resolved in the confined child must survive the * IPC round-trip (write_view/read_view symmetry for the new fields).*
- `test_load_carries_box_tree` (line 514) - *The box TREE (Step D) — the box-definition list with its parent links — must survive the IPC round-trip: a nested box parsed in the confined child ...*
- `test_load_strips_script` (line 593)
- `test_load_ex_builds_dom_and_fires_onload` (line 637) - *Live JS construction (Hito 20c): a script builds a node and an onload handler * mutates it; both must be reflected in the worker's returned view.*
- `test_load_ex_inner_html_renders` (line 665) - *innerHTML (Hito 20d): a script replaces a container's markup; the parsed content * renders, and ephemeral storage / empty cookie do not break the s...*
- `console_find` (line 716) - *assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK); assert_non_null(p.title); assert_string_equal(p.title, "Old"); int saw_before = 0; for ...*
- `test_load_captures_console_and_error` (line 726) - *Freebug (FB-1): with run_js, the page's console.* output and any uncaught script * error are captured and delivered to the parent in tab_page.console.*
- `test_load_isolates_script_errors` (line 753) - *Per-script isolation (browser semantics): an uncaught error in the FIRST inline <script> must NOT abort later scripts. Before this, all scripts wer...*
- `test_load_error_carries_location` (line 781) - *FB error locations (Hito 24): an uncaught error reports the inline script name ("inline #N") plus the line and column of its throw site, carried ac...*
- `test_load_element_wrapper_idioms` (line 807) - *Element-wrapper completeness (Hito 24): the exact google.com startup idioms that previously threw -- dataset.X, hasAttribute, removeAttribute, src....*
- `test_load_document_fonts_stub` (line 837) - *document.fonts stub: a feature-detecting script that calls document.fonts.load()/ .check() must not throw (this exact call -- document.fonts.load -...*
- `test_load_without_js_has_empty_console` (line 857) - *"</script></body></html>"; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &...*
- `test_eval_captures_console_output` (line 873) - *Freebug (FB-1): the REPL (tab_eval) returns the value AND the console output the * evaluation produced, each eval reporting only its own transcript.*
- `test_load_full_location_is_real` (line 902) - *Real location (Hito 20e): the page URL passed to tab_load_full backs a real * location object the page's JS can read (no scripts need run for the r...*
- `test_js_navigation_relative_resolved` (line 938)
- `test_js_navigation_unsafe_is_blocked` (line 958) - *Fail-closed gate: the parent rejects a downgrade / foreign-scheme / fragment nav, * so a hostile or compromised worker cannot drive the browser off...*
- `test_no_js_no_navigation` (line 980) - *const char *cases[] = { DOWNGRADE, FOREIGN, FRAGMENT }; for (size_t i = 0; i < 3; ++i) { tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab...*
- `test_load_null_and_too_large` (line 993)
- `test_eval_sees_dom` (line 1009) - *(void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load(NULL, HTML, 4, &p), TAB_ERR_NULL_ARG); as...*
- `test_eval_sees_env` (line 1019) - *tab_close(t); }  /* --- eval: sees the DOM bound in the child ---  static void test_eval_sees_dom(void **state) { fixture *f = (fixture *)*state; e...*
- `test_eval_no_network_or_cross_origin_api` (line 1037) - *SOP/CORS confidentiality (gap audit #2): the JS sandbox exposes NO way to make a network request or open a cross-origin browsing context, so it can...*
- `stub_fetch` (line 1056) - *Stub parent fetcher: returns a fixed 200/"PONG" body, but REFUSES any "blocked.example" * host -- standing in for the real parent's hostblock/realm...*
- `test_xhr_works_when_net_allowed` (line 1075) - *With net allowed (host in allow.conf AND js.conf) the page's XHR reaches the parent * fetcher and the response is visible to script.*
- `test_xhr_undefined_when_net_not_allowed` (line 1095) - *Default (net not allowed): XHR/fetch stay undefined -- Same-Origin-by-construction holds for every site not in BOTH lists. The script's `new XMLHtt...*
- `stub_script_fetch` (line 1134) - *Stub parent fetcher for external scripts: serves JS bodies by URL with a proper JavaScript Content-Type; refuses "blocked.example" (standing in for...*
- `test_external_script_executes_when_net_allowed` (line 1164) - *With net granted (allow.conf AND js.conf) an external script's bytes come from the * trusted parent and execute: its DOM mutation is visible in the...*
- `test_external_script_document_order` (line 1181) - *External scripts execute IN DOCUMENT ORDER interleaved with inline ones: a later * inline script sees the external script's effects (exactly as a b...*
- `test_external_script_skipped_without_net` (line 1204) - *Without the network grant an external script is SKIPPED (never fetched, never run): the page still loads and a Freebug warn entry records the skip....*
- `test_external_script_bad_ctype_not_executed` (line 1228) - *A response that is not JavaScript (e.g. an HTML error page) is NOT executed * (type-confusion guard, fail closed); the page still loads.*
- `test_external_script_blocked_host_refused` (line 1245) - *Even with net granted, the trusted parent's refusal (blocked host) means the script * never runs -- the gate is the PARENT's policy, not the page's.*
- `stub_css_fetch` (line 1268) - *Stub parent fetcher for stylesheets: serves CSS bodies by URL with a text/css Content-Type; refuses "blocked.example" (standing in for the parent's...*
- `view_find_text` (line 1289)
- `test_external_css_applied_when_allowed` (line 1301) - *With the css grant, the <link rel=stylesheet> bytes come from the trusted parent * and feed the author-CSS cascade -- no JS required (run_js == 0).*
- `test_external_css_skipped_without_grant` (line 1321) - *Default (no grant): zero subresource requests and no external styling -- * Privacy by Default holds, byte-identical to the pre-Hito-27 view.*
- `test_external_css_bad_ctype_not_parsed` (line 1340) - *A non-CSS Content-Type (an HTML 404 page, a script) is never parsed as a sheet * (anti type-confusion, fail closed); the load continues unstyled.*
- `test_external_css_blocked_host_refused` (line 1358) - *The parent's policy refusal (blocked host) degrades to "no sheet", never a * failed load: presentation is fail-open like hostblock, the page stays ...*
- `test_external_css_survives_click_rederive` (line 1376) - *The fetched sheet PERSISTS in the worker: a click re-derives the view (OP_CLICK) * and the styling survives without a re-fetch.*
- `test_subreq_permitted_pure` (line 1404) - *Pure parent-side subresource gate (Zero Trust: the parent decides from ITS flags, never the worker's): net grants any well-formed method, css-only ...*
- `read` (line 1425)
- `test_eval_exception` (line 1445) - *"<!DOCTYPE html><html><head><title>x</title></head><body>" "<script>document.title = 'tz:' + new Date(0).getTimezoneOffset()" " + ':' + new Date(1e...*
- `test_eval_persistent_state` (line 1457) - */* --- eval: a JS exception is TAB_OK with is_exception set, not a worker error ---  static void test_eval_exception(void **state) { fixture *f = (...*
- `test_reload_replaces_page` (line 1466) - *assert_non_null(strstr(r.value, "boom")); tab_eval_result_free(&r); }  /* --- eval: state persists across calls within the same worker ---  static ...*
- `test_eval_without_load` (line 1490) - *static const char HTML2[] = "<!DOCTYPE html><html><head><title>Second</title></head>" "<body><span id=\"other\">x</span></body></html>"; assert_int...*
- `test_binary_does_not_crash_parent` (line 1502) - */* --- eval before any load is a worker error, not a crash ---  static void test_eval_without_load(void **state) { (void)state; tab *t = NULL; asse...*
- `test_child_death_survived` (line 1517) - *static void test_binary_does_not_crash_parent(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); uint8_t junk[1024...*
- `test_free_null_and_double` (line 1543) - */* Give the kernel a moment to deliver the signal and reap-on-read. struct timespec ts = { 0, 50 * 1000 * 1000 }; nanosleep(&ts, NULL);  tab_eval_r...*
- `test_decode_image_in_sandbox` (line 1577)
- `test_decode_image_rejects_junk` (line 1599)
- `test_decode_image_null_args` (line 1614)
- `test_worker_args_valid` (line 1628) - *static void test_decode_image_null_args(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_image img; assert_i...*
- `test_worker_args_not_worker` (line 1637)
- `test_worker_args_malformed` (line 1644)
- `test_worker_args_null_safe` (line 1659)
- `main` (line 1669)

**Macros:**
- `_POSIX_C_SOURCE` (line 13)
- `XHR_PAGE` (line 1067)
- `EXT_PAGE` (line 1157)
- `CSS_PAGE` (line 1284)

**Structs:**
- `fixture` (line 39) - *#include <sys/types.h> #include <cmocka.h>  #include "css.h" #include "tab.h"  static const char HTML[] = "<!DOCTYPE html><html><head><title>Isolat...*

#### `test_text_shape.c`
**Path:** `tests/test_text_shape.c`

**Functions:**
- `test_null_and_bad_inputs` (line 26) - *#include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <math.h> #include <string.h>  #include <cmocka.h>  #include "text_shape.h" #in...*
- `test_empty_slice_is_ok` (line 56)
- `test_shape_ascii` (line 69) - *}  static void test_empty_slice_is_ok(void **state) { (void)state; cairo_glyph_t g[8]; size_t n = 99; double adv = 99.0; /* Empty input is OK regar...*
- `test_determinism` (line 91)
- `test_measure_matches_shape` (line 107)
- `test_overflow_cap` (line 119)
- `test_draw_paints` (line 129)
- `teardown` (line 142)
- `main` (line 148)

#### `test_textfield.c`
**Path:** `tests/test_textfield.c`

**Functions:**
- `test_init_and_accessors` (line 19) - *movement with saturation, home/end, the NULL-safe accessors, and the fail-closed FULL edges (set too long, insert into a full buffer leave the fiel...*
- `test_null_safe` (line 28)
- `test_set` (line 45)
- `test_insert_sequence` (line 58)
- `test_backspace_delete` (line 75)
- `test_move_saturates` (line 99)
- `test_full_fails_closed` (line 112)
- `main` (line 139)

#### `test_ui.c`
**Path:** `tests/test_ui.c`

**Functions:**
- `assert_line` (line 20) - *Build: make test   ;   ASan: make asan   #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #include <string.h> #inclu...*
- `test_wrap_null_args` (line 27)
- `test_wrap_empty` (line 34)
- `test_wrap_short_single_line` (line 42)
- `test_wrap_breaks_at_space` (line 52)
- `test_wrap_hard_breaks_long_word` (line 63)
- `test_wrap_does_not_split_utf8` (line 75)
- `test_wrap_respects_newline` (line 89)
- `test_wrap_zero_cols_is_sanitised` (line 100)
- `test_clamp_scroll` (line 112)
- `test_layout_free_null_and_double` (line 120)
- `main` (line 129)

#### `test_url.c`
**Path:** `tests/test_url.c`

**Functions:**
- `test_is_https` (line 22) - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <stdlib.h> #include <string.h>  #include <cmocka.h>  #incl...*
- `test_validate_https` (line 35)
- `test_validate_long_bundle_url` (line 49) - *Modern bundle URLs exceed 2048 bytes (google.com's xjs script URL measures 3456): * anything within URL_MAX_LEN must validate and resolve; far past...*
- `test_has_scheme` (line 68) - *memset(url + base, 'a', 4000 - base); url[4000] = '\0'; assert_int_equal(url_validate_https(url), URL_OK);  char out[URL_MAX_LEN + 1]; assert_int_e...*
- `test_authority_len` (line 85) - *assert_int_equal(url_has_scheme("https://x"), 1); assert_int_equal(url_has_scheme("mailto:a@b"), 1); assert_int_equal(url_has_scheme("javascript:vo...*
- `test_remove_dot_segments` (line 94) - *assert_int_equal(url_has_scheme("3com:x"), 0); /* scheme must start with ALPHA assert_int_equal(url_has_scheme(NULL), 0); }  /* --- url_authority_l...*
- `test_remove_dot_segments_nulls` (line 123)
- `test_resolve_absolute` (line 134) - *assert_int_equal(url_remove_dot_segments("/a/b/", out, sizeof out), URL_OK); assert_string_equal(out, "/a/b/"); /* trailing slash preserved }  stat...*
- `test_resolve_rejects_downgrade_and_schemes` (line 142)
- `test_resolve_scheme_relative` (line 157)
- `test_resolve_absolute_path` (line 165)
- `test_resolve_relative_path` (line 177)
- `test_resolve_dot_segments` (line 189)
- `test_resolve_fail_closed_on_bad_base` (line 206)
- `test_resolve_null_and_overflow` (line 218)
- `test_omnibox_navigate_https` (line 234) - *(void)state; char out[256]; assert_int_equal(url_resolve_https(NULL, "/x", out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_https(...*
- `test_omnibox_bare_host_gets_https` (line 247)
- `test_omnibox_http_upgraded_to_https` (line 264)
- `test_omnibox_search_for_queries` (line 274)
- `test_omnibox_foreign_scheme_is_searched_not_executed` (line 294)
- `test_omnibox_nulls_and_empty` (line 307)
- `test_is_file_and_path` (line 323) - *(void)state; char out[URL_MAX_LEN + 1]; url_omni_kind k; assert_int_equal(url_omnibox(NULL, &k, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equ...*
- `test_resolve_file_relative` (line 335)
- `test_resolve_file_confinement_fail_closed` (line 355)
- `test_resolve_file_nulls` (line 381)
- `assert_span` (line 394) - *}  static void test_resolve_file_nulls(void **state) { (void)state; char out[URL_MAX_LEN + 1]; assert_int_equal(url_resolve_file(NULL, "x", out, si...*
- `test_split_full_url` (line 398)
- `test_split_no_port_no_path` (line 417)
- `test_split_query_without_fragment` (line 430)
- `test_split_fragment_without_query` (line 439)
- `test_split_ipv6_literal_with_port` (line 448)
- `test_extract_userinfo_basic` (line 460) - *assert_span(u.hash, u.hash_len, "#sec"); }  static void test_split_ipv6_literal_with_port(void **state) { (void)state; url_parts u; assert_int_equa...*
- `test_extract_userinfo_user_only` (line 473)
- `test_extract_userinfo_no_userinfo` (line 486)
- `test_extract_userinfo_non_https_passthrough` (line 498)
- `test_extract_userinfo_https_subresource_no_auth` (line 510)
- `test_extract_userinfo_nulls` (line 523)
- `test_extract_userinfo_at_authority_start` (line 533)
- `test_extract_userinfo_no_at_sign` (line 546)
- `test_extract_userinfo_empty_password` (line 559)
- `test_split_fail_closed_non_https` (line 572)
- `main` (line 583)

#### `test_zoom.c`
**Path:** `tests/test_zoom.c`

**Functions:**
- `test_clamp_bounds` (line 16) - *test_zoom — CMocka suite for the pure page-zoom arithmetic.  Covers clamping bounds, ladder stepping (snap, monotonicity, idempotent ends), reset, ...*
- `test_reset_is_default` (line 26)
- `test_zoom_in_steps_ladder` (line 32)
- `test_zoom_out_steps_ladder` (line 40)
- `test_step_snaps_off_ladder` (line 48)
- `test_ends_are_idempotent` (line 58)
- `test_repeated_in_reaches_max` (line 66)
- `test_repeated_out_reaches_min` (line 78)
- `test_scale_factor` (line 90)
- `test_apply_scales_and_floors` (line 99)
- `main` (line 111)

#### `gen_psl.c`
**Path:** `tools/gen_psl.c`

**Functions:**
- `vec_push` (line 26)
- `cmp_str` (line 37)
- `sort_unique` (line 43) - *v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap * sizeof *v->items); if (v->items == NULL) { fputs("oom\n", stder...*
- `ascii_lower` (line 55) - */* Sorts then drops adjacent duplicates in place. static void sort_unique(vec *v) { qsort(v->items, v->len, sizeof *v->items, cmp_str); size_t w = ...*
- `emit` (line 60)
- `main` (line 66)

**Macros:**
- `_POSIX_C_SOURCE` (line 14)

**Structs:**
- `vec` (line 21) - *Usage: gen_psl <public_suffix_list.dat> > psl_data.c  Both the ICANN and PRIVATE sections are included: for privacy, treating e.g. each "*.github.i...*

### H (42 files)

#### `browser_ui_internal.h`
**Path:** `gui/browser_ui_internal.h`

**Macros:**
- `FREEDOM_BROWSER_UI_INTERNAL_H` (line 2)
- `UI_FONT_SIZE` (line 23)
- `UI_TEXT_MARGIN` (line 25)
- `UI_HEADING_LEVELS` (line 26)

**Structs:**
- `ui_rgb` (line 35) - *-- presentation theme ---  Every font size, spacing and colour the renderer uses, gathered in one place so no value is hardcoded at a call site. An...*
- `ui_theme` (line 37)

#### `anti_fp.h`
**Path:** `include/anti_fp.h`

**Macros:**
- `FREEDOM_ANTI_FP_H` (line 2)
- `FP_TIMER_RESOLUTION_MS` (line 21)
- `FP_USER_AGENT` (line 31)
- `FP_ACCEPT_LANGUAGE` (line 33)
- `FP_ACCEPT_LANGUAGE_HEADER` (line 34)

#### `box_style.h`
**Path:** `include/box_style.h`

**Macros:**
- `FREEDOM_BOX_STYLE_H` (line 2)

**Structs:**
- `bx_edges` (line 39) - *See spec/box_style.md for the full contract.   typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width ...*
- `bx_box` (line 43)
- `bx_hplace` (line 56) - *typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box;  typedef enum bx_status { BX_OK = 0, BX_ERR_NULL_ARG, ...*

#### `box_tree.h`
**Path:** `include/box_tree.h`

**Macros:**
- `FREEDOM_BOX_TREE_H` (line 2)
- `BT_MAX_DEPTH` (line 35)
- `BT_MAX_CHILDREN` (line 36)
- `BT_MAX_POSITIONED` (line 37)
- `BT_POS_STATIC` (line 42)
- `BT_POS_RELATIVE` (line 43)
- `BT_POS_ABSOLUTE` (line 44)
- `BT_POS_FIXED` (line 45)
- `BT_POS_STICKY` (line 46)
- `BT_ALIGN_START` (line 53)
- `BT_ALIGN_CENTER` (line 54)
- `BT_ALIGN_END` (line 55)
- `BT_ALIGN_STRETCH` (line 56)

**Structs:**
- `bt_node` (line 58) - *Cross-axis alignment of a node as a flex item of its FLEX parent (bt_node.align). 0 (the zero-init default) is START, matching the layout's behavio...*
- `bt_positioned` (line 100) - *Stage 2: one positioned box in the final paint order. The GUI paints the in-flow rc_layout.rows first, then the bt_positioned list in this order (o...*

#### `browser.h`
**Path:** `include/browser.h`

**Macros:**
- `FREEDOM_BROWSER_H` (line 2)
- `BROWSER_URL_MAX` (line 20)
- `BROWSER_STATUS_MAX` (line 24)
- `BROWSER_STATUS_DURATION_MS` (line 25)

**Structs:**
- `browser_state` (line 27) - *Maintains history, current URL bar, and last rendered page. All I/O (network, disk, sandboxed render) is delegated to the GUI orchestrator; this mo...*

#### `css.h`
**Path:** `include/css.h`

**Macros:**
- `FREEDOM_CSS_H` (line 2)
- `CSS_GAP_MAX` (line 63)
- `CSS_GRID_COLS_MAX` (line 64)
- `CSS_LINE_MIN` (line 65)
- `CSS_LINE_MAX` (line 66)
- `CSS_DECO_UNDERLINE` (line 71)
- `CSS_DECO_LINE_THROUGH` (line 72)
- `CSS_DECO_OVERLINE` (line 73)
- `CSS_CONTAIN_SIZE` (line 307)
- `CSS_CONTAIN_LAYOUT` (line 308)
- `CSS_CONTAIN_STYLE` (line 309)
- `CSS_CONTAIN_PAINT` (line 310)
- `CSS_BORDER_W_MAX` (line 387)
- `CSS_BORDER_SPACING_MAX` (line 388)
- `CSS_FLEX_FACTOR_MAX` (line 389)
- `CSS_GRID_SPAN_MAX` (line 390)
- `CSS_SPACING_MAX` (line 394)
- `CSS_SHADOW_MAX` (line 395)
- `CSS_LEN_MAX` (line 400)
- `CSS_LEN_UNSET` (line 401)
- `CSS_LEN_AUTO` (line 402)
- `CSS_MAX_COMPOUNDS` (line 406)
- `CSS_MAX_ATTR_SEL` (line 410)
- `CSS_MAX_PSEUDO_SEL` (line 414)
- `CSS_NTH_MAX` (line 418)
- `CSS_MEDIA_DEFAULT_WIDTH` (line 570)

**Structs:**
- `css_style` (line 425) - *A resolved presentation. Each field uses a sentinel for "unset" so the caller can layer inheritance (take the first ancestor that sets each inherit...*
- `css_media` (line 565) - *Render-time media context for evaluating @media at parse time. width_px is a fixed, normalized desktop width, so a (min/max-width) query leaks no r...*
- `css_attr` (line 602) - *One element attribute, for attribute selectors ([attr], [attr=v], [attr~=v], ...). name is the lowercased local name; value is the attribute text (...*
- `css_element` (line 612) - *An element plus its ancestor chain, for combinator matching. Each field aliases caller storage (nothing is copied/owned). parent walks toward the r...*

#### `css_chain.h`
**Path:** `include/css_chain.h`

**Macros:**
- `FREEDOM_CSS_CHAIN_H` (line 2)
- `CCH_CHAIN_MAX` (line 26)
- `CCH_SIB_MAX` (line 27)
- `CCH_NTH_MAX` (line 28)

#### `css_color.h`
**Path:** `include/css_color.h`

**Macros:**
- `FREEDOM_CSS_COLOR_H` (line 2)

**Structs:**
- `cc_rgb` (line 25) - *No I/O, no global state, no allocation. Decodes a single CSS color token (hostile data with provenance) into an opaque 8-bit-per-channel RGB, or fa...*

#### `css_select.h`
**Path:** `include/css_select.h`

**Functions:**
- `csel_lower_ch` (line 96) - *Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller). Returns 1 if supported, 0 to drop the selector (fail...*
- `csel_ci_eq` (line 100)
- `csel_span_eq` (line 110) - *static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c; }  static inline int csel_ci_eq(const char *a, const...*
- `csel_substr` (line 121) - *Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator). A non-empty needle only; an empty o...*
- `csel_ident_ch` (line 128)

**Macros:**
- `FREEDOM_CSS_SELECT_H` (line 2)
- `CSS_TOK_MAX` (line 27)
- `CSS_MAX_CLASSES_PER_SEL` (line 28)

**Structs:**
- `css_pseudo_match` (line 48) - *One pseudo-class inside a compound. a/b are the An+B coefficients of the * nth-child family (unused otherwise).*
- `css_attr_match` (line 54) - *One pseudo-class inside a compound. a/b are the An+B coefficients of the * nth-child family (unused otherwise). typedef struct css_pseudo_match { i...*
- `css_compound` (line 63) - *One compound selector: optional type, optional id, zero+ classes, zero+ [attr], * zero+ pseudo-classes.*
- `css_sel` (line 79) - *A complex selector: a chain of compounds, parts[nparts-1] being the subject (the element a rule styles). comb[k] (k>=1) is the combinator to the LE...*

#### `disk_store.h`
**Path:** `include/disk_store.h`

**Macros:**
- `FREEDOM_DISK_STORE_H` (line 2)

#### `dom.h`
**Path:** `include/dom.h`

**Macros:**
- `FREEDOM_DOM_H` (line 2)
- `DOM_NODE_NONE` (line 37)

#### `dom_debug.h`
**Path:** `include/dom_debug.h`

**Macros:**
- `FREEDOM_DOM_DEBUG_H` (line 2)
- `DD_FIELD_MAX` (line 28)

#### `download.h`
**Path:** `include/download.h`

**Macros:**
- `FREEDOM_DOWNLOAD_H` (line 2)
- `DL_NAME_MAX` (line 28)
- `DL_FALLBACK_NAME` (line 30)
- `DL_MAX_BYTES` (line 31)

#### `flex_layout.h`
**Path:** `include/flex_layout.h`

**Macros:**
- `FREEDOM_FLEX_LAYOUT_H` (line 2)
- `FX_MAX_ITEMS` (line 28)

**Structs:**
- `fx_item` (line 40) - *Upper bound on items per flex line / grid columns. Caps the O(n) shrink loop and * keeps the fixed-size scratch buffers bounded (anti-DoS; no VLAs)...*
- `fx_result` (line 48) - *FX_JUSTIFY_SPACE_BETWEEN, FX_JUSTIFY_SPACE_AROUND, FX_JUSTIFY_SPACE_EVENLY } fx_justify;  /* One flex item, all sizes in px. Negative fields are tr...*

#### `form.h`
**Path:** `include/form.h`

**Macros:**
- `FREEDOM_FORM_H` (line 2)
- `FM_URL_MAX` (line 28)
- `FM_BODY_MAX` (line 30)
- `FM_MAX_FIELDS` (line 31)

**Structs:**
- `fm_field` (line 37) - *One named control. value == NULL is treated as the empty value; name == NULL is * skipped by fm_encode and rejected (FM_BLOCK_INVALID) by fm_build.*
- `fm_plan` (line 52)

#### `freebug.h`
**Path:** `include/freebug.h`

**Macros:**
- `FREEDOM_FREEBUG_H` (line 2)
- `FB_MAX_ENTRIES` (line 55)
- `FB_MAX_ENTRY_BYTES` (line 56)
- `FB_MAX_TOTAL_BYTES` (line 57)
- `FB_MAX_FILE_BYTES` (line 61)

**Structs:**
- `fb_entry` (line 36) - *One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid)...*
- `fb_buffer` (line 46) - *One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid)...*

#### `hostblock.h`
**Path:** `include/hostblock.h`

**Macros:**
- `FREEDOM_HOSTBLOCK_H` (line 2)

#### `hostedit.h`
**Path:** `include/hostedit.h`

**Macros:**
- `FREEDOM_HOSTEDIT_H` (line 2)
- `HE_MAX_HOST` (line 32)

#### `html_parse.h`
**Path:** `include/html_parse.h`

**Macros:**
- `FREEDOM_HTML_PARSE_H` (line 2)
- `HP_DEFAULT_MAX_BYTES` (line 40)
- `HP_MAX_SCRIPTS` (line 48)
- `HP_MAX_STYLESHEETS` (line 109)

**Structs:**
- `hp_config` (line 32)
- `hp_script` (line 76) - *One executable <script>. Inline: text is a NUL-terminated buffer of `len` bytes (the NUL is not counted in len) and src == NULL. External: src is t...*

#### `image_decode.h`
**Path:** `include/image_decode.h`

**Macros:**
- `FREEDOM_IMAGE_DECODE_H` (line 2)
- `IMG_MAX_DIM` (line 58)
- `IMG_MAX_PIXELS` (line 59)

**Structs:**
- `img_pixels` (line 49) - *A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32: each pixel is a uint32_t 0xAARRGGBB, i.e. byt...*

#### `js_dom.h`
**Path:** `include/js_dom.h`

**Macros:**
- `FREEDOM_JS_DOM_H` (line 2)

**Structs:**
- `jd_opaque` (line 35)

#### `js_env.h`
**Path:** `include/js_env.h`

**Macros:**
- `FREEDOM_JS_ENV_H` (line 2)

#### `js_policy.h`
**Path:** `include/js_policy.h`

**Macros:**
- `FREEDOM_JS_POLICY_H` (line 2)

#### `js_sandbox.h`
**Path:** `include/js_sandbox.h`

**Macros:**
- `FREEDOM_JS_SANDBOX_H` (line 2)
- `JS_LOC_FILE_MAX` (line 64)
- `JS_DEFAULT_MAX_SOURCE` (line 65)
- `JS_DEFAULT_MEM_LIMIT` (line 67)
- `JS_DEFAULT_STACK_LIMIT` (line 68)
- `JS_DEFAULT_TIME_BUDGET` (line 69)

**Structs:**
- `js_limits` (line 39) - *Per-evaluation resource limits. A field set to 0 receives that field's * default: "no limit" is deliberately not representable (secure by default).*
- `js_result` (line 49)

#### `link_nav.h`
**Path:** `include/link_nav.h`

**Macros:**
- `FREEDOM_LINK_NAV_H` (line 2)
- `LN_MAX_TARGET` (line 33)
- `LN_MAX_FRAGMENT` (line 38)

**Structs:**
- `ln_result` (line 62)

#### `local_store.h`
**Path:** `include/local_store.h`

**Macros:**
- `FREEDOM_LOCAL_STORE_H` (line 2)
- `LS_KEY_LEN` (line 25)
- `LS_SALT_LEN` (line 27)
- `LS_NONCE_LEN` (line 28)
- `LS_TAG_LEN` (line 29)
- `LS_HEADER_LEN` (line 30)
- `LS_OVERHEAD` (line 31)
- `LS_MAX_PLAINTEXT` (line 32)

#### `net_realm.h`
**Path:** `include/net_realm.h`

**Macros:**
- `FREEDOM_NET_REALM_H` (line 2)

**Structs:**
- `nr_config` (line 42)

#### `os_sandbox.h`
**Path:** `include/os_sandbox.h`

**Macros:**
- `FREEDOM_OS_SANDBOX_H` (line 2)

**Structs:**
- `os_fs_rule` (line 108)

#### `page_view.h`
**Path:** `include/page_view.h`

**Macros:**
- `FREEDOM_PAGE_VIEW_H` (line 2)
- `PV_LEN_UNSET` (line 42)

**Structs:**
- `pv_run` (line 77) - *One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-ter...*
- `pv_box_def` (line 235) - *Box engine (Hito 23b-8 Step D): one entry of the box-definition TREE. The box decoration and the parent link live here, not on each run, so a box i...*
- `pv_view` (line 287)

#### `pdf_export.h`
**Path:** `include/pdf_export.h`

**Macros:**
- `FREEDOM_PDF_EXPORT_H` (line 2)
- `PE_NAME_MAX` (line 27)
- `PE_EXT` (line 29)
- `PE_EXT_PNG` (line 30)
- `PE_FALLBACK_NAME` (line 31)

#### `psl_data.h`
**Path:** `include/psl_data.h`

**Macros:**
- `FREEDOM_PSL_DATA_H` (line 2)

#### `render_doc.h`
**Path:** `include/render_doc.h`

**Macros:**
- `FREEDOM_RENDER_DOC_H` (line 2)

**Structs:**
- `rd_block` (line 44) - *One paint-ready block in document order. text is owned, NUL-terminated and valid UTF-8. href is owned and NUL-terminated for RD_LINK (link target),...*
- `rd_doc` (line 143)

#### `render_policy.h`
**Path:** `include/render_policy.h`

**Macros:**
- `FREEDOM_RENDER_POLICY_H` (line 2)
- `RDP_TRACKER_MAX_DIM` (line 27)

**Structs:**
- `rdp_caps` (line 32) - *Render capabilities for a page. The zero value ({0}) is the safe baseline: every rich/risky capability off. The only way to opt in is to set a fiel...*

#### `renderer.h`
**Path:** `include/renderer.h`

**Macros:**
- `FREEDOM_RENDERER_H` (line 2)
- `RD_MAX_INPUT` (line 36)
- `RD_MAX_FIELD` (line 38)

**Structs:**
- `rd_result` (line 29)

#### `request_policy.h`
**Path:** `include/request_policy.h`

**Macros:**
- `FREEDOM_REQUEST_POLICY_H` (line 2)

#### `secure_fetch.h`
**Path:** `include/secure_fetch.h`

**Macros:**
- `FREEDOM_SECURE_FETCH_H` (line 2)
- `SF_DEFAULT_KEX_GROUPS` (line 117)
- `SF_DEFAULT_USER_AGENT` (line 123)
- `SF_DEFAULT_MAX_BODY` (line 124)
- `SF_DEFAULT_TIMEOUT_MS` (line 125)
- `SF_DEFAULT_MAX_REDIRECTS` (line 126)
- `SF_MAX_URL` (line 127)

**Structs:**
- `sf_chain_info` (line 60) - *Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testabl...*
- `sf_config` (line 75)
- `sf_response` (line 91)

#### `tab.h`
**Path:** `include/tab.h`

**Macros:**
- `FREEDOM_TAB_H` (line 2)
- `TAB_MAX_INPUT` (line 89)

**Structs:**
- `tab_page` (line 49) - *Inert result of loading a page: title + extracted text + structured display list (all owned). text is kept for headless/plain output; view carries ...*
- `tab_eval_result` (line 69) - *Console output (console.* calls + any uncaught script exception) captured while loading the page, for the Freebug devtools. Owned; drained from the...*
- `tab_image` (line 82) - *Pixels of a decoded image, produced inside the confined worker. data is owned and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: b...*

#### `text_shape.h`
**Path:** `include/text_shape.h`

**Macros:**
- `FREEDOM_TEXT_SHAPE_H` (line 19)
- `TSH_MAX_GLYPHS` (line 35)
- `TSH_MAX_TEXT` (line 37)

**Structs:**
- `tsh_font` (line 30) - *Font selector: a css_font_family bucket (CSS_FF_*) plus weight/slant flags. * The engine matches the generic group only, never an exact author family.*

#### `textfield.h`
**Path:** `include/textfield.h`

**Macros:**
- `FREEDOM_TEXTFIELD_H` (line 2)
- `TF_CAP` (line 22)

**Structs:**
- `tf_field` (line 25) - *textfield — a pure, single-line editable text buffer with a cursor.  No I/O, no global state, no dynamic allocation: a fixed-capacity buffer the GU...*

#### `ui.h`
**Path:** `include/ui.h`

**Macros:**
- `FREEDOM_UI_H` (line 2)

**Structs:**
- `ui_line` (line 29) - *A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.*
- `ui_layout` (line 34)
- `rd_doc` (line 68)

#### `url.h`
**Path:** `include/url.h`

**Macros:**
- `FREEDOM_URL_H` (line 2)
- `URL_MAX_LEN` (line 30)
- `URL_SEARCH_ENDPOINT` (line 76)

**Structs:**
- `url_parts` (line 116) - *Components of a validated absolute https URL, sliced for a JS location object. Every field ALIASES the input url (not owned, valid while url is ali...*

#### `zoom.h`
**Path:** `include/zoom.h`

**Macros:**
- `FREEDOM_ZOOM_H` (line 2)
- `ZM_MIN_PCT` (line 20)
- `ZM_MAX_PCT` (line 22)
- `ZM_DEFAULT_PCT` (line 23)

### PY (1 files)

#### `app.py`
**Path:** `app.py`

**Functions:**
- `read_fuzz_stats` (line 30) - *Reads the current status of the active AFL++ fuzzing session.*
- `list_unique_crashes` (line 39) - *Lists all unique crash files generated by the fuzzer that broke the browser.*
- `run_freedom_headless` (line 47) - *Executes the FreeDom browser in headless mode against a specific file input or mutated seed.

Args:
    payload_path: The relative or absolute path to the HTML/JS file to process (e.g., 'fuzz/in/seed.html').*

### SH (6 files)

#### `build_deb.sh`
**Path:** `build_deb.sh`

*No symbols extracted*

#### `docker-entrypoint.sh`
**Path:** `docker-entrypoint.sh`

*No symbols extracted*

#### `docker_run.sh`
**Path:** `docker_run.sh`

*No symbols extracted*

#### `fuzz.sh`
**Path:** `fuzz.sh`

*No symbols extracted*

#### `install.sh`
**Path:** `install.sh`

*No symbols extracted*

#### `run_freedom.sh`
**Path:** `run_freedom.sh`

*No symbols extracted*
