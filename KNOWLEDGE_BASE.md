# Polyglot Codebase Knowledge Graph

> Generated offline by **readmenator**. Supports C, C++, Python, Go, Rust, JS/TS, Java, C#, Shell, PHP, Dart, GDScript, Nim, ASM, Ruby, Swift, Kotlin, Scala, Lua, Elixir.
> No LLMs. No tokens. Pure static analysis. See more [here](https://github.com/grisuno/ReadMenator)

**Total Files Parsed:** 162 | **Total Symbols Extracted:** 2955 | **Total Imports:** 901


## Table of Contents

1. [Statistics Dashboard](#statistics-dashboard)
2. [Architectural Layers](#architectural-layers)
3. [God Nodes](#god-nodes)
4. [Suggested Questions](#suggested-questions)
5. [Structural Knowledge Map](#structural-knowledge-map)
6. [Architecture Reference](#architecture-reference)
    - [C (109 files)](#c-109-files)
    - [H (46 files)](#h-46-files)
    - [PY (1 files)](#py-1-files)
    - [SH (6 files)](#sh-6-files)

---

## Statistics Dashboard

| Metric | Value |
|--------|-------|
| Total Files | 162 |
| Total Symbols | 2955 |
| Total Imports | 901 |
| Call Edges | 15 |
| Inheritance Edges | 0 |
| Languages | 4 |
| Avg Symbols/File | 18.2 |
| Avg Imports/File | 5.6 |

### Top Files by Import Count (Fan-Out)

| File | Imports | Symbols | Language |
|------|---------|---------|----------|
| `browser_ui.c` | 56 | 308 | c |
| `tab.c` | 27 | 62 | c |
| `os_sandbox.c` | 23 | 28 | c |
| `test_os_sandbox.c` | 22 | 19 | c |
| `freedom.c` | 18 | 24 | c |
| `page_view.c` | 14 | 109 | c |
| `test_disk_store.c` | 14 | 15 | c |
| `test_dom_debug.c` | 14 | 11 | c |
| `test_profile.c` | 14 | 16 | c |
| `local_store.c` | 13 | 43 | c |

---

## Architectural Layers

Auto-detected from path patterns, naming conventions, and imported frameworks.

| Layer | Files |
|-------|-------|
| utility | 84 |
| testing | 44 |
| presentation | 19 |
| data_access | 7 |
| infrastructure | 4 |
| business_logic | 4 |

### utility

- `app.py` (py, 3 symbols)
- `docker-entrypoint.sh` (sh, 0 symbols)
- `docker_run.sh` (sh, 0 symbols)
- `fuzz.sh` (sh, 0 symbols)
- `fuzz_css.c` (c, 1 symbols)
- `fuzz_dom.c` (c, 2 symbols)
- `fuzz_dom_debug.c` (c, 1 symbols)
- `fuzz_download.c` (c, 1 symbols)
- `fuzz_freebug.c` (c, 1 symbols)
- `fuzz_html_parse.c` (c, 0 symbols)
- `fuzz_image_decode.c` (c, 2 symbols)
- `fuzz_js_sandbox.c` (c, 0 symbols)
- `fuzz_pdf_export.c` (c, 1 symbols)
- `fuzz_prefetch.c` (c, 1 symbols)
- `fuzz_prefs.c` (c, 1 symbols)
- *... and 69 more*

### presentation

- `build_deb.sh` (sh, 0 symbols)
- `fuzz_page_view.c` (c, 0 symbols)
- `browser_ui.c` (c, 308 symbols)
- `browser_ui_internal.h` (h, 6 symbols)
- `bui_theme.c` (c, 6 symbols)
- `freedom_view.c` (c, 2 symbols)
- `ui_render.c` (c, 29 symbols)
- `flex_layout.h` (h, 4 symbols)
- `page_view.h` (h, 7 symbols)
- `render_doc.h` (h, 3 symbols)
- `render_policy.h` (h, 3 symbols)
- `renderer.h` (h, 4 symbols)
- `ui.h` (h, 4 symbols)
- `flex_layout.c` (c, 11 symbols)
- `page_view.c` (c, 109 symbols)
- *... and 4 more*

### data_access

- `disk_store.h` (h, 1 symbols)
- `form.h` (h, 6 symbols)
- `local_store.h` (h, 8 symbols)
- `psl_data.h` (h, 1 symbols)
- `disk_store.c` (c, 8 symbols)
- `form.c` (c, 8 symbols)
- `local_store.c` (c, 43 symbols)

### infrastructure

- `hostedit.h` (h, 2 symbols)
- `js_env.h` (h, 1 symbols)
- `hostedit.c` (c, 13 symbols)
- `js_env.c` (c, 27 symbols)

### business_logic

- `js_policy.h` (h, 1 symbols)
- `request_policy.h` (h, 1 symbols)
- `js_policy.c` (c, 6 symbols)
- `request_policy.c` (c, 11 symbols)

### testing

- `itest_secure_fetch.c` (c, 2 symbols)
- `test_anti_fp.c` (c, 15 symbols)
- `test_box_style.c` (c, 24 symbols)
- `test_box_tree.c` (c, 36 symbols)
- `test_browser.c` (c, 15 symbols)
- `test_css.c` (c, 182 symbols)
- `test_css_color.c` (c, 15 symbols)
- `test_disk_store.c` (c, 15 symbols)
- `test_dom.c` (c, 36 symbols)
- `test_dom_debug.c` (c, 11 symbols)
- `test_download.c` (c, 21 symbols)
- `test_flex_layout.c` (c, 37 symbols)
- `test_form.c` (c, 20 symbols)
- `test_freebug.c` (c, 13 symbols)
- `test_freedom.c` (c, 25 symbols)
- *... and 29 more*

---

## God Nodes

Most architecturally central files ranked by combined import/export degree and symbol richness.

| File | Score | Connections |
|------|-------|-------------|
| `browser_ui.c` | 30.8 | |
| `test_css.c` | 18.2 | |
| `css.c` | 15.6 | |
| `page_view.c` | 10.9 | |
| `test_page_view.c` | 8.5 | |
| `test_tab.c` | 7.7 | |
| `test_js_dom.c` | 7.2 | |
| `tab.c` | 6.2 | |
| `dom.c` | 6.1 | |
| `js_dom.c` | 5.3 | |

---

## Suggested Questions

Auto-generated exploration prompts based on graph structure:

- What does browser_ui.c depend on, and what depends on it? (0 connections)
- What does test_css.c depend on, and what depends on it? (0 connections)
- What does css.c depend on, and what depends on it? (0 connections)
- What is the overall architecture of this codebase?

---

## Structural Knowledge Map

> **Note:** The visual graph below has been intelligently pruned to the top 300 most relevant nodes to prevent rendering crashes. Full details of all files are documented in the Architecture Reference.

```mermaid
graph TD
    classDef mod fill:#1e1e1e,stroke:#ff6666,stroke-width:2px,color:#fff;
    classDef cls fill:#2d2d2d,stroke:#4ec9b0,stroke-width:2px,color:#fff;
    classDef fn fill:#333,stroke:#dcdcaa,stroke-width:1px,color:#dcdcaa;
    classDef ext fill:#111,stroke:#666,stroke-dasharray:5 5,color:#aaa;
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
    src_page_view_c_pv_container_reg["pv_container_reg"]
    class src_page_view_c_pv_container_reg cls;
    src_page_view_c --> src_page_view_c_pv_container_reg
    tests_test_profile_c["test_profile.c (c)"]
    class tests_test_profile_c mod;
    tests_test_profile_c_fixture["fixture"]
    class tests_test_profile_c_fixture cls;
    tests_test_profile_c --> tests_test_profile_c_fixture
    tests_test_profile_c_setup["setup"]
    class tests_test_profile_c_setup fn;
    tests_test_profile_c --> tests_test_profile_c_setup
    tests_test_profile_c_teardown["teardown"]
    class tests_test_profile_c_teardown fn;
    tests_test_profile_c --> tests_test_profile_c_teardown
    tests_test_profile_c_path_of["path_of"]
    class tests_test_profile_c_path_of fn;
    tests_test_profile_c --> tests_test_profile_c_path_of
    tests_test_profile_c_file_size["file_size"]
    class tests_test_profile_c_file_size fn;
    tests_test_profile_c --> tests_test_profile_c_file_size
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
    src_profile_c["profile.c (c)"]
    class src_profile_c mod;
    src_profile_c_join_path["join_path"]
    class src_profile_c_join_path fn;
    src_profile_c --> src_profile_c_join_path
    src_profile_c_keyfile_create["keyfile_create"]
    class src_profile_c_keyfile_create fn;
    src_profile_c --> src_profile_c_keyfile_create
    src_profile_c_profile_open["profile_open"]
    class src_profile_c_profile_open fn;
    src_profile_c --> src_profile_c_profile_open
    src_profile_c_map_ds["map_ds"]
    class src_profile_c_map_ds fn;
    src_profile_c --> src_profile_c_map_ds
    src_profile_c_profile_load["profile_load"]
    class src_profile_c_profile_load fn;
    src_profile_c --> src_profile_c_profile_load
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
    tests_test_prefs_c["test_prefs.c (c)"]
    class tests_test_prefs_c mod;
    tests_test_prefs_c_test_init_defaults["test_init_defaults"]
    class tests_test_prefs_c_test_init_defaults fn;
    tests_test_prefs_c --> tests_test_prefs_c_test_init_defaults
    tests_test_prefs_c_test_roundtrip["test_roundtrip"]
    class tests_test_prefs_c_test_roundtrip fn;
    tests_test_prefs_c --> tests_test_prefs_c_test_roundtrip
    tests_test_prefs_c_test_parse_bad_magic["test_parse_bad_magic"]
    class tests_test_prefs_c_test_parse_bad_magic fn;
    tests_test_prefs_c --> tests_test_prefs_c_test_parse_bad_magic
    tests_test_prefs_c_test_parse_too_large["test_parse_too_large"]
    class tests_test_prefs_c_test_parse_too_large fn;
    tests_test_prefs_c --> tests_test_prefs_c_test_parse_too_large
    tests_test_prefs_c_test_parse_unknown_and_malformed_skipped["test_parse_unknown_and_malformed_skipped"]
    class tests_test_prefs_c_test_parse_unknown_and_malformed_skipped fn;
    tests_test_prefs_c --> tests_test_prefs_c_test_parse_unknown_and_malformed_skipped
    tests_test_prefetch_c["test_prefetch.c (c)"]
    class tests_test_prefetch_c mod;
    tests_test_prefetch_c_fake_ctx["fake_ctx"]
    class tests_test_prefetch_c_fake_ctx cls;
    tests_test_prefetch_c --> tests_test_prefetch_c_fake_ctx
    tests_test_prefetch_c_test_scan_null_args["test_scan_null_args"]
    class tests_test_prefetch_c_test_scan_null_args fn;
    tests_test_prefetch_c --> tests_test_prefetch_c_test_scan_null_args
    tests_test_prefetch_c_test_scan_basic_stylesheet_and_script["test_scan_basic_stylesheet_and_script"]
    class tests_test_prefetch_c_test_scan_basic_stylesheet_and_script fn;
    tests_test_prefetch_c --> tests_test_prefetch_c_test_scan_basic_stylesheet_and_script
    tests_test_prefetch_c_test_scan_ref_cap["test_scan_ref_cap"]
    class tests_test_prefetch_c_test_scan_ref_cap fn;
    tests_test_prefetch_c --> tests_test_prefetch_c_test_scan_ref_cap
    tests_test_prefetch_c_fake_fetch["fake_fetch"]
    class tests_test_prefetch_c_fake_fetch fn;
    tests_test_prefetch_c --> tests_test_prefetch_c_fake_fetch
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
    tests_test_secure_fetch_c_test_config_blend_fields_default_null["test_config_blend_fields_default_null"]
    class tests_test_secure_fetch_c_test_config_blend_fields_default_null fn;
    tests_test_secure_fetch_c --> tests_test_secure_fetch_c_test_config_blend_fields_default_null
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
    tests_test_tls_impersonate_c["test_tls_impersonate.c (c)"]
    class tests_test_tls_impersonate_c mod;
    tests_test_tls_impersonate_c_test_gate_requires_all_three_signals["test_gate_requires_all_three_signals"]
    class tests_test_tls_impersonate_c_test_gate_requires_all_three_signals fn;
    tests_test_tls_impersonate_c --> tests_test_tls_impersonate_c_test_gate_requires_all_three_signals
    tests_test_tls_impersonate_c_test_encode_decode_req_roundtrip["test_encode_decode_req_roundtrip"]
    class tests_test_tls_impersonate_c_test_encode_decode_req_roundtrip fn;
    tests_test_tls_impersonate_c --> tests_test_tls_impersonate_c_test_encode_decode_req_roundtrip
    tests_test_tls_impersonate_c_test_encode_decode_req_empty_body["test_encode_decode_req_empty_body"]
    class tests_test_tls_impersonate_c_test_encode_decode_req_empty_body fn;
    tests_test_tls_impersonate_c --> tests_test_tls_impersonate_c_test_encode_decode_req_empty_body
    tests_test_tls_impersonate_c_test_encode_decode_resp_roundtrip["test_encode_decode_resp_roundtrip"]
    class tests_test_tls_impersonate_c_test_encode_decode_resp_roundtrip fn;
    tests_test_tls_impersonate_c --> tests_test_tls_impersonate_c_test_encode_decode_resp_roundtrip
    tests_test_tls_impersonate_c_test_resp_no_chain_ok["test_resp_no_chain_ok"]
    class tests_test_tls_impersonate_c_test_resp_no_chain_ok fn;
    tests_test_tls_impersonate_c --> tests_test_tls_impersonate_c_test_resp_no_chain_ok
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
    src_image_decode_c["image_decode.c (c)"]
    class src_image_decode_c mod;
    src_image_decode_c_jpeg_err_ctx["jpeg_err_ctx"]
    class src_image_decode_c_jpeg_err_ctx cls;
    src_image_decode_c --> src_image_decode_c_jpeg_err_ctx
    src_image_decode_c_gif_reader["gif_reader"]
    class src_image_decode_c_gif_reader cls;
    src_image_decode_c --> src_image_decode_c_gif_reader
    src_image_decode_c_gif_bits["gif_bits"]
    class src_image_decode_c_gif_bits cls;
    src_image_decode_c --> src_image_decode_c_gif_bits
    src_image_decode_c_read_be32["read_be32"]
    class src_image_decode_c_read_be32 fn;
    src_image_decode_c --> src_image_decode_c_read_be32
    src_image_decode_c_img_png_dimensions["img_png_dimensions"]
    class src_image_decode_c_img_png_dimensions fn;
    src_image_decode_c --> src_image_decode_c_img_png_dimensions
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
```

---

## Architecture Reference

### C (109 files)

#### `fuzz_css.c`
**Path:** `fuzz/fuzz_css.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 61) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_dom.c`
**Path:** `fuzz/fuzz_dom.c`

**Functions:**
- `ensure_built` (line 40) `static void ensure_built(void)`
- `LLVMFuzzerTestOneInput` (line 47) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_dom_debug.c`
**Path:** `fuzz/fuzz_dom_debug.c`

**Functions:**
- `pass` (line 8) `* the measure pass (cap 0) must agree with the would-write return value.
 *
 * Build & run: make ...`

#### `fuzz_download.c`
**Path:** `fuzz/fuzz_download.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 30) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_freebug.c`
**Path:** `fuzz/fuzz_freebug.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 36) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_html_parse.c`
**Path:** `fuzz/fuzz_html_parse.c`

*No symbols extracted*

#### `fuzz_image_decode.c`
**Path:** `fuzz/fuzz_image_decode.c`

**Functions:**
- `poke_and_free` (line 21) `static void poke_and_free(img_pixels *px)` - *Touch every claimed pixel corner so the sanitizer flags an out-of-bounds extent, * then release. Safe on a zeroed (failed-decode) struct.*
- `LLVMFuzzerTestOneInput` (line 31) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_js_sandbox.c`
**Path:** `fuzz/fuzz_js_sandbox.c`

*No symbols extracted*

#### `fuzz_page_view.c`
**Path:** `fuzz/fuzz_page_view.c`

*No symbols extracted*

#### `fuzz_pdf_export.c`
**Path:** `fuzz/fuzz_pdf_export.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 29) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_prefetch.c`
**Path:** `fuzz/fuzz_prefetch.c`
**File Doc:** *libFuzzer harness for the prefetch lookahead scanner (Hito 29). The scanned*

**Functions:**
- `LLVMFuzzerTestOneInput` (line 9) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` - *include "prefetch.h"*

#### `fuzz_prefs.c`
**Path:** `fuzz/fuzz_prefs.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 20) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_text_shape.c`
**Path:** `fuzz/fuzz_text_shape.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 24) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)` - *define FZ_CAP 2048u*

**Macros:**
- `FZ_CAP` (line 22)

#### `fuzz_tls_impersonate.c`
**Path:** `fuzz/fuzz_tls_impersonate.c`

*No symbols extracted*

#### `fuzz_url.c`
**Path:** `fuzz/fuzz_url.c`

**Functions:**
- `check_split` (line 29) `static void check_split(const char *url)`
- `LLVMFuzzerTestOneInput` (line 57) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `browser_ui.c`
**Path:** `gui/browser_ui.c`

**Functions:**
- `now_ms` (line 132) `static uint64_t now_ms(void)` - *Largest text slice measured/drawn at once (one word, or one clipped label). * Words longer than this are still placed, just measured up to the cap....*
- `gutter` (line 456) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
- `apply_zoom` (line 477) `static void apply_zoom(browser_window *w)` - *Applies a new zoom level: rebuild the theme and repaint. The page is laid out fresh from w->theme on every paint, so no re-fetch and no worker roun...*
- `buffer_release` (line 487) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` - *Applies a new zoom level: rebuild the theme and repaint. The page is laid out fresh from w->theme on every paint, so no re-fetch and no worker roun...*
- `destroy_buffer` (line 493) `static void destroy_buffer(browser_window *w)`
- `ensure_buffer` (line 499) `static int ensure_buffer(browser_window *w)`
- `read_file` (line 529) `static char *read_file(const char *path, size_t *out_len)` - *w->buffer = wl_shm_pool_create_buffer(pool, 0, w->width, w->height, stride, WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (w->b...*
- `build_file_origin` (line 569) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` - *Builds a "file:///<canonical absolute path>" origin from a local path (or passes through a file:// URL's path). realpath canonicalizes; on failure ...*
- `load_host_file` (line 579) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)` - *Loads one /etc/hosts-format .conf file (if present and readable) into the given * list. A missing file is not an error: the filter fails open, neve...*
- `build_host_filter` (line 596) `static hb_set *build_host_filter(void)` - *Builds the host filter from the user's .conf lists. Privacy by Default: block.conf (a /etc/hosts-format blocklist) blocks trackers/ads and their su...*
- `build_js_filter` (line 642) `static hb_set *build_js_filter(void)`
- `build_impersonate_filter` (line 646) `static hb_set *build_impersonate_filter(void)` - *impersonate.conf: the THIRD opt-in signal. A host here (and in allow.conf and js.conf) * gets the Chrome/Firefox-consistent TLS ClientHello blend (...*
- `freedom_write_dir` (line 651) `static int freedom_write_dir(char *out, size_t cap)` - *The writable Freedom config dir: $FREEDOM_HOSTS_DIR if set, else ~/.config/freedom (created if absent). Returns 0 on success. Mirrors the read sear...*
- `add_current_host_to_list` (line 676) `static void add_current_host_to_list(browser_window *w, int sel)` - *Appends the current page's host to one of the user's .conf lists (block/allow/js), then reloads the in-memory filter so it applies. The host is hos...*
- `load_favorites` (line 744) `static void load_favorites(browser_window *w)` - *Concatenates the allow.conf bodies along the same search path build_host_filter uses into one string: the omnibox "favorites". Frees any previous v...*
- `omni_refresh` (line 788) `static void omni_refresh(browser_window *w)` - *Recomputes the omnibox autocomplete suggestions for the current URL-bar text. Shown only while the URL bar is focused and something is typed; other...*
- `profile_sync` (line 819) `static void profile_sync(browser_window *w)` - *Mirrors the session's persistable choices into w->prefs and seals them to disk. Called after any preference change; with a read-only profile (absen...*
- `remember_visit` (line 836) `static void remember_visit(browser_window *w, const char *url)` - *Records a committed navigation in the persistent history (dedup + cap live in prefs). Opt-out via the "Remember history" toggle; internal pages are...*
- `bookmark_toggle_current` (line 844) `static void bookmark_toggle_current(browser_window *w)` - *Records a committed navigation in the persistent history (dedup + cap live in prefs). Opt-out via the "Remember history" toggle; internal pages are...*
- `proxy_addr_from_env` (line 868) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...` - *Copies a proxy "host:port" into dst: if the env value is unset/empty the default is used; the literal "1" also means "use the default" (a convenien...*
- `init_net_config` (line 882) `static void init_net_config(browser_window *w)` - *Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in, everything off unless explicitly enabled). FREEDOM_TOR_PROXY / ...*
- `is_https_url` (line 891) `static int is_https_url(const char *s)`
- `is_http_url` (line 895) `static int is_http_url(const char *s)`
- `host_from_url` (line 907) `static int host_from_url(const char *url, char *out, size_t outsz)` - *A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is * fetched over the network (through the overlay proxy), not read as a...*
- `input_is_interactive` (line 933) `static int input_is_interactive(int input_type)` - *An editable control gets a live text field; submit/button/hidden do not. Checkboxes, radios, and selects are interactive (click toggles/opens) but ...*
- `input_is_editable` (line 938) `static int input_is_editable(int input_type)`
- `free_inputs` (line 945) `static void free_inputs(browser_window *w)` - *are not text-editable -- they are tracked via rebuild_inputs so clicks * dispatch to them, but they have no tf_field. static int input_is_interacti...*
- `free_images` (line 953) `static void free_images(browser_window *w)` - *static int input_is_editable(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD || input_type == PV_IN_TEXTAREA; } /...*
- `find_image` (line 963) `static const ui_image *find_image(const browser_window *w, const rd_block *blk)` - *w->focused_input = -1; } /* Releases the decoded image surfaces of the current page and the array. static void free_images(browser_window *w) { for...*
- `layout` (line 973) `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...`
- `rebuild_inputs` (line 987) `static void rebuild_inputs(browser_window *w)` - *Builds the live editable state for the current doc: one entry per editable * control, seeded with its declared value. Aliases the doc blocks (not o...*
- `find_input_state` (line 1012) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` - *if (w->inputs == NULL) return; /* fail closed: no editable fields, page still shows size_t k = 0; for (size_t i = 0; i < n; ++i) { const rd_block *...*
- `clear_doc` (line 1020) `static void clear_doc(browser_window *w)` - *Releases the structured render of the previous page (text mode resumes). The * hovered link and the live form controls alias the doc, so they are c...*
- `set_cache` (line 1029) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` - *Releases the structured render of the previous page (text mode resumes). The * hovered link and the live form controls alias the doc, so they are c...*
- `surface_from_pixels` (line 1040) `static cairo_surface_t *surface_from_pixels(const tab_image *img)` - *Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit. Copies row by row because Cairo may use a wider stride than the tightly packed...*
- `fetch_follow_navigable` (line 1106) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...` - *Fetches url (following redirects) under cfg's policy, applying two navigability fallbacks in order of decreasing security: 1) If the only obstacle ...*
- `GET` (line 1139) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
- `gui_subresource_fetch` (line 1185) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...` - *tab_fetch_fn: the trusted parent's policy-checked subresource fetch for page XHR/fetch. The worker has no network; it proxied the request here. We ...*
- `prepare_fetch` (line 1291) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...` - *Builds cfg for url and applies the pre-fetch gates. Returns nonzero when the fetch may proceed (cfg and pr->allowlisted are then set); returns 0 wh...*
- `fetch_job_free` (line 1390) `static void fetch_job_free(fetch_job *j)`
- `stream_progress_cb` (line 1411) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` - *Called by the fetch thread (~1/sec) with the downloaded body so far. Copies the data to the window's thread-safe streaming buffer and signals the m...*
- `fetch_thread` (line 1435) `static void *fetch_thread(void *arg)` - *Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer back to the event loop. Pure with respect to the window: it rea...*
- `fetch_launch` (line 1482) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...` - *Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch). The caller has bumped w->net_gen for this navigation; the job sna...*
- `load_images` (line 1538) `static void load_images(browser_window *w, tab *t)` - *Fetches and decodes every allowed image of the current doc into w->images (one entry per RD_IMAGE block). Each fetch re-applies the full TLS/PQ/cha...*
- `compute_page_js` (line 1643) `static int compute_page_js(const browser_window *w)` - *Resolves the JS policy for the current page's host (Secure by Default: off unless the global mode is ON or the host is on the js.conf allowlist). P...*
- `seed_session_cookies` (line 1661) `static void seed_session_cookies(tab *t, int trusted, const char *url)` - *Seeds document.cookie for the next load from the ephemeral network jar (trusted host * only); reset to none otherwise so a persistent worker never ...*
- `foldback_session_cookies` (line 1674) `static void foldback_session_cookies(const char *url, const char *jar)` - *Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network jar * one pair at a time, so JS-set session cookies reach the next ...*
- `drop_repl_worker` (line 1693) `static void drop_repl_worker(browser_window *w)` - *Drops the kept-alive REPL worker and clears the (active-tab) console transcript. Used when the active page changes WITHOUT a re-render (tab switch ...*
- `schedule_js_tick` (line 1707) `static void schedule_js_tick(browser_window *w, int next_ms)` - *Schedules the next JS timer tick from the worker's reported smallest pending delay (tab_page.next_timer_ms; < 0 = nothing pending). The event loop ...*
- `render_current_ex` (line 1716) `static void render_current_ex(browser_window *w, int allow_js_nav)`
- `render_current` (line 1861) `static void render_current(browser_window *w)` - *Real async timers: a fresh load resets the per-page tick budget and schedules * the first OP_TICK from the worker's reported smallest pending delay...*
- `show_busy` (line 1868) `static void show_busy(browser_window *w)` - *Marks a request in flight and paints a frame so the spinner appears at once. The fetch now runs on a worker thread, so the event loop keeps animati...*
- `show_fetch_error` (line 1877) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...` - *Replaces the page with the standard "Failed to load" diagnostic for status ss on url. allowlisted tailors the hint (already retried vs. how to over...*
- `arrives` (line 1928) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
- `strcmp` (line 1996) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
- `tab_save` (line 2057) `static void tab_save(browser_window *w)` - *Parks the active tab's live state into its slot (a shallow move: the slot and the live fields briefly alias the same allocations; the live fields a...*
- `tab_restore` (line 2073) `static void tab_restore(browser_window *w)` - *c->bs = w->bs; c->doc = w->doc; c->caps = w->caps; c->scroll = w->scroll; c->content_total_h = w->content_total_h; c->inputs = w->inputs; c->input_...*
- `free_live_page` (line 2089) `static void free_live_page(browser_window *w)` - *w->bs = c->bs; w->doc = c->doc; w->caps = c->caps; w->scroll = c->scroll; w->content_total_h = c->content_total_h; w->inputs = c->inputs; w->input_...*
- `tab_ctx_release` (line 2098) `static void tab_ctx_release(tab_ctx *c)` - *w->hover_href = c->hover_href; w->hover_cursor = c->hover_cursor; } /* Frees the LIVE page's owned state (used when closing the foreground tab). st...*
- `tab_switch` (line 2113) `static void tab_switch(browser_window *w, int idx)` - *if (c->images != NULL) { for (size_t i = 0; i < c->image_count; ++i) if (c->images[i].surface != NULL) cairo_surface_destroy(c->images[i].surface);...*
- `tab_new` (line 2132) `static void tab_new(browser_window *w, const char *url)` - *w->net_gen++; w->loading = 0; drop_repl_worker(w); /* active page changes without a render; rebind on next eval tab_save(w); w->active_tab = idx; t...*
- `uitab_close` (line 2164) `static void uitab_close(browser_window *w, int idx)` - *w->inputs = NULL; w->input_count = 0; w->focused_input = -1; w->images = NULL; w->image_count = 0; w->cur_html = NULL; w->cur_html_len = 0; w->cur_...*
- `newtab_x` (line 2206) `static double newtab_x(const browser_window *w)` - *X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge.*
- `tab_title` (line 2213) `static const char *tab_title(const browser_window *w, int i)` - *X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge. static double newtab_x(const browser_win...*
- `tabbar_top` (line 2229) `static double tabbar_top(const browser_window *w)` - *Top of the tab strip: directly under the client-side titlebar (or at the surface * top under server-side decorations).*
- `toolbar_top` (line 2235) `static double toolbar_top(const browser_window *w)` - *Top of the toolbar: under the tab strip, which is always reserved. The whole * content area derives from this, so adding the strip reflows everythi...*
- `content_geometry` (line 2242) `static void content_geometry(const browser_window *w, double *top, double *height)` - *The content area rectangle below the toolbar, in surface coordinates. The single source of truth for both painting and click hit-testing so they ca...*
- `content_width` (line 2268) `static double content_width(const browser_window *w)`
- `scrollbar_metrics` (line 2279) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...` - *Geometry of the vertical scrollbar in surface coordinates, plus the current thumb position. Returns 0 (and leaves outputs untouched) when the conte...*
- `scrollbar_drag_to` (line 2307) `static void scrollbar_drag_to(browser_window *w)` - *Maps the current pointer Y (less the grab offset) to a scroll offset while the * thumb is being dragged, then repaints. No-op when there is no scro...*
- `draw_scrollbar` (line 2324) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` - *Paints the scrollbar track and thumb. The thumb highlights while hovered or * dragged, the same affordance the toolbar buttons and links get.*
- `window_button_rects` (line 2360) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
- `toolbar_rects` (line 2370) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...` - *The reload button sits as the third left chrome button (after back/forward), at a * fixed x; callers that need it derive it here so the layout stay...*
- `toolbar_button_at` (line 2386) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)` - *Which toolbar button (if any) is at (px, py). Shared by the hover highlight and * the cursor shape so they cannot drift from the click hit-test.*
- `hot_actionable` (line 2402) `static int hot_actionable(const browser_window *w, ui_hot hot)` - *A hovered button is "actionable" (gets the hand cursor) when clicking it would * do something: Go/menu always, Back/Forward only when there is hist...*
- `menu_panel_rect` (line 2413) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...` - *The options-menu panel rectangle (below the gear button), and its per-item row * height. The single source of truth for drawing and hit-testing the...*
- `ua_box_rect` (line 2429) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...` - *The editable User-Agent box rectangle inside the options panel. The single * source of truth for drawing and hit-testing the field.*
- `draw_text` (line 2438) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
- `rc_free` (line 2605) `static void rc_free(rc_layout *L)`
- `rc_add_box` (line 2614) `static rc_box *rc_add_box(rc_layout *L)`
- `rc_add_frag` (line 2626) `static rc_frag *rc_add_frag(rc_layout *L)`
- `rc_add_row` (line 2636) `static rc_row *rc_add_row(rc_layout *L)`
- `family_face` (line 2649) `static const char *family_face(int family)` - *Maps an author font-family bucket (css_font_family) to a Cairo toy-font family. * The engine matches no exact families, only the generic groups.*
- `content_font` (line 2666) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family)`
- `set_rgb_alpha` (line 2680) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` - *Sets the source color, applying an author opacity (0..100) as an alpha when set * (-1 = fully opaque). Used for author text and its shadow.*
- `utf8_clen` (line 2689) `static size_t utf8_clen(const char *s, size_t n)` - *Bytes in the UTF-8 cluster starting at s[0] (1 for a stray/continuation byte), * clamped to n.*
- `draw_slice` (line 2729) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` - *Draws a text slice at (x, baseline) in the current content font/source. Shapes with HarfBuzz when available; otherwise the Cairo toy API. Mirrors m...*
- `frag_styled` (line 2742) `static int frag_styled(const rc_frag *f)` - *True if a fragment needs the per-cluster path (text-transform other than none/unset, or a non-zero letter-spacing). Otherwise the fast whole-slice ...*
- `styled_advance` (line 2749) `static double styled_advance(cairo_t *cr, const rc_frag *f)` - *Advance (px) of a fragment's text under its text-transform + letter-spacing. The current Cairo font must already be selected. Mirrors styled_draw e...*
- `styled_draw` (line 2765) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` - *Draws a fragment's text starting at (x, baseline) under its text-transform + * letter-spacing. The current Cairo font/source must already be set.*
- `block_style` (line 2781) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
- `block_margins` (line 2805) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...` - *Vertical margins (px) of a block from the user-agent box model (box_style), resolved against the block's own font size (em -> px). The user-agent n...*
- `flush_line` (line 2817) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
- `open_line` (line 2837) `static void open_line(rc_layout *L, rc_state *s)`
- `flow_emit_frag` (line 2875) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...` - *Emits one fragment at the current pen position, advancing it. Shared by the * whole-word path and the word-break split path in flow_text.*
- `flow_text` (line 2922) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...` - *owning box (for the hover-cursor lookup), -1 if none.  word-break/overflow-wrap (s->break_words): a single word wider than the WHOLE line (not just...*
- `flow_text_block` (line 3070) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...` - *Flows one text/link/notice block into L at content_w using state s. The caller sets s->bg_rgb (the block's author background, or -1) beforehand; th...*
- `effect` (line 3151) `* effect (byte-identical default). */
static int container_has_flex_items(const rd_doc *doc, size...`
- `css_align_to_bt` (line 3167) `static int css_align_to_bt(int align_kw)` - *Maps a css_align_kw (align-items/align-self) to the box_tree cross-axis alignment it drives. BASELINE/AUTO/UNSET/space-* (align-content only, never...*
- `layout_container` (line 3175) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
- `ITEMS` (line 3225) `* between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visua...`
- `slot` (line 3303) `* layout slot (item 0 → rightmost, last item → leftmost). */
        if (head->flex_direction == ...`
- `box_edge_px` (line 3420) `static double box_edge_px(int wpx)` - *if (bt_layout(&root, content_w) != BT_OK) return; /* Translate each item's rows into its column rectangle. for (size_t j = 0; j < g; ++j) { const b...*
- `box_line_visible` (line 3426) `static int box_line_visible(int style)` - *True iff a border/outline style paints a line (solid..outset); none/hidden/unset * paint nothing. The fancier 3D styles collapse to solid at paint ...*
- `close_top_box` (line 3432) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` - *Closes the open block box: flushes the current line, reserves the box's bottom * padding+border, and finalizes the recorded border-box height. No-o...*
- `rc_box_context` (line 3463) `static void rc_box_context(const rc_state *s, double content_w,
                           double...` - *Content rect (left, width) the current run/box is laid out in: the innermost open * box's, or the page content box when no box is open (default fla...*
- `children` (line 3478) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
- `reconcile_boxes` (line 3586) `static void reconcile_boxes(rc_layout *L, rc_state *s, const ui_theme *th,
                      ...` - *Reconciles the open-box stack so it equals block b's box path (root..b->block_id), derived from the box-def parent_id chain. Closes any open box no...*
- `box_path_of` (line 3621) `static int box_path_of(const rd_doc *doc, int block_id, int *out)` - *Box path root..block_id via the box-def parent_id chain (root first), written into * out (bounded by RC_BOX_STACK_MAX). Returns the path length; bl...*
- `band_common_box` (line 3637) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` - *The innermost box that is an ancestor (or self) of EVERY block in [start, end), via the longest common prefix of their box paths — the box a float ...*
- `layout_float_band` (line 3659) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...` - *Lays a float band [start, end) — a maximal run of blocks each with float_id >= 0 — side by side inside the current box context (spec/float.md). Blo...*
- `layout_doc` (line 3757) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
- `position_doc` (line 3931) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...` - *Stage 2: resolves out-of-flow positioning for every absolute/fixed block in the document and stores the stacking-ordered result in L->positioned. R...*
- `input_box_width` (line 4032) `static double input_box_width(double content_w)` - *make the painter repaint the box on TOP of its rows — covering everything past the first block with the box background. So drop the in-flow (relati...*
- `select_box_width` (line 4035) `static double select_box_width(double content_w)`
- `button_box_width` (line 4041) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...` - *} L->npositioned = keep; } /* Width of a painted text-input box: the preferred width clamped to the content. static double input_box_width(double c...*
- `row_align_offset` (line 4288) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` - *Horizontal shift a row's text gets from author text-align (center/right): the slack between the available width and the line's right edge. 0 for le...*
- `upstream` (line 4301) `* upstream (see spec/css.md). */
static void box_path(cairo_t *cr, double x, double y, double w, ...`
- `paint_box_decoration` (line 4324) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy)` - *Paints one block box's decoration (Hito 23b-8 Step C): box-shadow, background fill, the four borders and the outline, behind the rows it encloses. ...*
- `paint_content_row` (line 4457) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...` - *Paints one laid-out row at vertical position ry. Shared by the on-screen painter and the PDF exporter so both render identically (same fonts, colou...*
- `cairo_set_dash` (line 4526) `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (line 4528) `cairo_set_dash(cr, (double[])`
- `ov_box_clips` (line 4554) `static int ov_box_clips(const pv_box_def *d)` - *} if (f->overline) { double oy = fbaseline - f->font_size * UI_OVERLINE_OFFSET; cairo_move_to(cr, x0, oy); cairo_line_to(cr, x1, oy); cairo_stroke(...*
- `ov_collect_chain` (line 4562) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` - *Walks the ancestor chain of block_id and collects overflow:hidden box IDs * into out[] (outermost first). Returns count, limited to OV_MAX_DEPTH.*
- `ov_find_box` (line 4576) `static const rc_box *ov_find_box(const rc_layout *L, int bid)` - *static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap) { int tmp[OV_MAX_DEPTH], n = 0; for (int id = block_id; id >= 0 && ...*
- `ov_content_rect` (line 4584) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...` - *Computes the padding-box content rect (in page coords: y, x, w, h) for a box. * Used as the clip region for overflow:hidden children.*
- `paint_structured` (line 4640) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
- `write_doc_pdf` (line 4790) `static long write_doc_pdf(browser_window *w, const char *path)` - *Writes the window's current laid-out document to a vector PDF at `path`, paginated to US Letter. Returns the page count (0 when the document lays o...*
- `export_pdf` (line 4928) `static void export_pdf(browser_window *w)`
- `write_doc_png` (line 4980) `static long write_doc_png(browser_window *w, const char *path)` - *Writes the window's current laid-out document to a single full-height PNG at `path` (the same layout/paint path as the screen and the PDF export, i...*
- `export_png` (line 5111) `static void export_png(browser_window *w)`
- `caller` (line 5146) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
- `ui_render_png` (line 5169) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` - *Headless PNG export (no Wayland; see include/ui.h). One full-height bitmap of the whole page, the cheapest artifact for visual review (no PDF raste...*
- `ui_dump_layout` (line 5194) `ui_status ui_dump_layout(const rd_doc *doc)` - *Headless layout dump: runs the same layout_doc + position_doc pass as the on-screen/PNG renderer and prints the resolved box geometry (in-flow boxe...*
- `link_at_point` (line 5246) `static const char *link_at_point(browser_window *w, double px, double py)`
- `resolve_box_cursor` (line 5294) `static int resolve_box_cursor(const rd_doc *doc, int block_id)` - *First non-unset author `cursor` on block_id's box or an ancestor (nearest wins, like the rest of the box-decoration fields), or CSS_CUR_UNSET if no...*
- `box_pointer_events_none` (line 5308) `static int box_pointer_events_none(const rd_doc *doc, int block_id)` - *True when author `pointer-events: none` removes block_id's content from hit-testing (2026-07-10): the nearest box in the parent chain that sets the...*
- `cursor_at_point` (line 5324) `static int cursor_at_point(browser_window *w, double px, double py)` - *Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET when outside content / no box sets one. Unlike link_at_point this t...*
- `node_at_point` (line 5372) `static dom_node_id node_at_point(browser_window *w, double px, double py)` - *Returns the DOM node id of the element under (px, py), or DOM_NODE_NONE if the point is over blank space / outside content. Mirrors layout and scro...*
- `reference` (line 5417) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
- `apply_click_result` (line 5438) `static void apply_click_result(browser_window *w, tab_page *page)` - *Applies a click result returned by the worker: rebuild the rendered document and refresh inputs/console, but keep the current page in history (a cl...*
- `memory` (line 5461) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
- `GET` (line 5532) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
- `ensure_download_dir` (line 5566) `static int ensure_download_dir(char *out, size_t outsz)` - *Builds ~/Downloads/freedom into out and creates both levels (best effort; an existing directory is fine). Returns 1 on success. Falls back to $HOME...*
- `write_file_atomic` (line 5581) `static int write_file_atomic(const char *path, const void *bytes, size_t len)` - *Writes len bytes to path with 0600 perms via a temp file + atomic rename (the disk_store convention): a crash mid-write never leaves a half file at...*
- `save_download` (line 5603) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` - *Saves a fetched resource to ~/Downloads/freedom instead of rendering it. The filename is derived fail-closed from the hostile Content-Disposition /...*
- `save_current_page` (line 5636) `static void save_current_page(browser_window *w)` - *Ctrl+S: save the current page's cached source to ~/Downloads/freedom. No network * round-trip -- the bytes already in the page cache are written.*
- `deliver_fetch_result` (line 5645) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
- `drain_fetch_results` (line 5700) `static void drain_fetch_results(browser_window *w)` - *Drains every completed fetch the worker threads have posted (the read end is non-blocking; pointer-sized writes are atomic). Called when the loop s...*
- `toggle_reader` (line 5767) `static void toggle_reader(browser_window *w)` - *Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author styling/images are gated off, a...*
- `menu_item_checked` (line 5778) `static int menu_item_checked(const browser_window *w, size_t i)` - *Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author styling/images are gated off, a...*
- `menu_item_toggle` (line 5800) `static void menu_item_toggle(browser_window *w, size_t i)` - *Toggles options-menu item i and applies its effect. Theme and force-colors only affect presentation (a repaint, which re-runs layout, suffices); a ...*
- `draw_clock` (line 5910) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...` - *A small spinner meaning "busy". Now that the fetch runs off the event-loop thread, the loop ticks ~12 fps while loading and rotates a leading arc s...*
- `draw_hamburger` (line 5921) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
- `draw_reload` (line 5938) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` - *The reload button glyph: a ~300-degree circular arrow centred in a UI_BTN_W button starting at bx. Drawn with Cairo (not a font glyph) so it never ...*
- `draw_menu` (line 5960) `static void draw_menu(cairo_t *cr, browser_window *w)` - *double a1 = a0 + UI_TWO_PI * 0.82;      /* leave a gap for the arrowhead cairo_new_sub_path(cr); cairo_arc(cr, cx, cy, r, a0, a1); cairo_stroke(cr)...*
- `draw_hover_url` (line 6071) `static double draw_hover_url(cairo_t *cr, browser_window *w)` - *Persistent bottom strip showing the target of the link under the pointer, so the user always knows where a click will go. Returns the strip height ...*
- `draw_toast` (line 6103) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` - *Draws the transient status toast (a banner near the bottom of the window), * raised by bottom_offset so it stacks above the hover-URL strip when bo...*
- `draw_tabstrip` (line 6133) `static void draw_tabstrip(cairo_t *cr, browser_window *w)` - *Paints the tab strip: one cell per tab (the active one connected to the content background, the rest dimmed), each with its clipped title and a clo...*
- `draw_omnibox` (line 6188) `static void draw_omnibox(cairo_t *cr, browser_window *w)` - *Omnibox autocomplete dropdown: a panel of favorite-host suggestions below the URL bar, drawn as an overlay (on top of content) while the URL bar is...*
- `paint` (line 6221) `static void paint(browser_window *w)`
- `redraw` (line 6462) `static void redraw(browser_window *w)`
- `wm_base_ping` (line 6473) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` - *cairo_surface_flush(w->cairo_surface); cairo_destroy(cr); } static void redraw(browser_window *w) { if (!w->configured) return; if (ensure_buffer(w...*
- `xdg_surface_configure` (line 6479) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (line 6487) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `wl_array_for_each` (line 6503) `wl_array_for_each(st, states)`
- `toplevel_close` (line 6508) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (line 6516) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
- `set_cursor` (line 6530) `static void set_cursor(browser_window *w, int hand)` - *Applies the hand (over a link) or default arrow cursor for the current pointer enter serial. A no-op when no themed cursor is available (the compos...*
- `update_hover` (line 6552) `static void update_hover(browser_window *w)` - *Recomputes which link (if any) is under the pointer; on a change, updates the cursor shape and repaints so the hover highlight follows. The author ...*
- `fbw_split_y` (line 6607) `static double fbw_split_y(const freebug_window *fb)` - *int    width, height; int    configured; int    visible; struct wl_buffer *buffer; void  *shm_data; size_t shm_size; cairo_surface_t *cairo_surface...*
- `freebug_ensure_buffer` (line 6615) `static int freebug_ensure_buffer(freebug_window *fb)`
- `fbw_level_rgb` (line 6643) `static void fbw_level_rgb(int level, double *r, double *g, double *b)` - *struct wl_shm_pool *pool = wl_shm_create_pool(fb->owner->shm, fd, (int32_t)size); fb->buffer = wl_shm_pool_create_buffer(pool, 0, fb->width, fb->he...*
- `fbw_console_lines` (line 6654) `static size_t fbw_console_lines(const fb_buffer *log)` - *} /* Color for a console level (dark devtools palette). static void fbw_level_rgb(int level, double *r, double *g, double *b) { switch (level) { ca...*
- `freebug_paint` (line 6663) `static void freebug_paint(freebug_window *fb)`
- `freebug_redraw_fb` (line 6822) `static void freebug_redraw_fb(freebug_window *fb)`
- `freebug_redraw` (line 6831) `static void freebug_redraw(browser_window *w)`
- `freebug_hide` (line 6835) `static void freebug_hide(browser_window *w)`
- `fbw_xdg_surface_configure` (line 6851) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `fbw_toplevel_configure` (line 6859) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
- `fbw_toplevel_close` (line 6869) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
- `freebug_show` (line 6878) `static void freebug_show(browser_window *w)`
- `freebug_toggle` (line 6908) `static void freebug_toggle(browser_window *w)`
- `freebug_destroy` (line 6913) `static void freebug_destroy(browser_window *w)`
- `freebug_owns_surface` (line 6920) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
- `freebug_is_open` (line 6924) `static int freebug_is_open(const browser_window *w)`
- `freebug_repl_worker` (line 6932) `static tab *freebug_repl_worker(browser_window *w)` - *Returns the live page worker for the REPL, lazily (re)opening one bound to the active page's cache if none is kept alive (e.g. just after a tab swi...*
- `freebug_eval` (line 6957) `static void freebug_eval(browser_window *w)`
- `freebug_handle_key` (line 6996) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
- `freebug_pointer_button` (line 7028) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
- `freebug_pointer_motion` (line 7039) `static void freebug_pointer_motion(browser_window *w)`
- `freebug_pointer_axis` (line 7051) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
- `ptr_enter` (line 7062) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` - *fb->split = s; freebug_redraw_fb(fb); } static void freebug_pointer_axis(browser_window *w, wl_fixed_t value) { freebug_window *fb = w->freebug; if...*
- `ptr_leave` (line 7075) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (line 7086) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `load_current` (line 7095) `static void load_current(browser_window *w)`
- `go_omnibox` (line 7109) `static void go_omnibox(browser_window *w)` - *Commits the URL bar like a real omnibox: an existing local file is opened as before; otherwise url_omnibox (pure) decides between navigating to a s...*
- `ptr_button` (line 7149) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
- `scroll_line_px` (line 7339) `static double scroll_line_px(const browser_window *w)` - *} else if (input_is_editable(ctl->input_type)) { for (size_t i = 0; i < w->input_count; ++i) { if (w->inputs[i].blk == ctl) { w->focused_input = (i...*
- `ptr_axis` (line 7342) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `mime_is_text` (line 7369) `static int mime_is_text(const char *mime)` - *redraw(w); } static const struct wl_pointer_listener pointer_listener = { .enter = ptr_enter, .leave = ptr_leave, .motion = ptr_motion, .button = p...*
- `data_offer_source_actions` (line 7387) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_offer_action` (line 7390) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_device_data_offer` (line 7400) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...` - *} static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) { (void)d; (void)o; (void)a; } static void data_offer_action(...*
- `data_device_selection` (line 7412) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...` - *The clipboard selection changed. Commit the new offer (or NULL when the clipboard * was cleared), destroying any previous one we held.*
- `data_device_enter` (line 7431) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...` - *wl_data_offer_destroy(w->selection_offer); if (offer == NULL) { w->selection_offer = NULL; w->selection_offer_has_text = 0; w->sel_mime[0] = '\0'; ...*
- `data_device_leave` (line 7436) `static void data_device_leave(void *d, struct wl_data_device *dev)`
- `data_device_motion` (line 7437) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
- `data_device_drop` (line 7441) `static void data_device_drop(void *d, struct wl_data_device *dev)`
- `data_source_cancelled` (line 7452) `static void data_source_cancelled(void *data, struct wl_data_source *src)` - *wl_fixed_t x, wl_fixed_t y) { (void)d; (void)dev; (void)t; (void)x; (void)y; } static void data_device_drop(void *d, struct wl_data_device *dev) { ...*
- `data_source_send` (line 7458) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...` - *.enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop, .selection = data_device_selection,...*
- `data_source_target` (line 7471) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
- `insert_pasted_text` (line 7484) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` - *Inserts pasted bytes into whichever text target currently has focus (page input, User-Agent box, or the URL bar). Control bytes -- including embedd...*
- `clipboard_copy` (line 7548) `static void clipboard_copy(browser_window *w)` - *Ctrl+C: copy the focused field's text (or, with nothing focused, the page address) * to the clipboard by owning a wl_data_source that serves it on ...*
- `keyboard_keymap` (line 7595) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...` - *Cut the omnibar selection: copy it to the clipboard, then remove it. v1 cut is the * URL bar only (page inputs / the UA box have no selection model...*
- `keyboard_enter` (line 7616) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
- `keyboard_leave` (line 7623) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
- `handle_key_press` (line 7632) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` - *Performs the effect of a single key press. Factored out of keyboard_key so a held key can be re-fired from the repeat timer with the exact same sem...*
- `key_is_repeatable` (line 7922) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` - *Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion and scrolling. A Ctrl chord (tab spawn, reload, image toggle...) o...*
- `key_repeat_arm` (line 7938) `static void key_repeat_arm(browser_window *w, uint32_t key)` - *Arms the repeat timer for key: first fire after repeat_delay ms, then every * 1/repeat_rate s. A held key thus repeats until released (key_repeat_s...*
- `key_repeat_stop` (line 7951) `static void key_repeat_stop(browser_window *w)` - *1/repeat_rate s. A held key thus repeats until released (key_repeat_stop). static void key_repeat_arm(browser_window *w, uint32_t key) { if (w->rep...*
- `key_repeat_fire` (line 7962) `static void key_repeat_fire(browser_window *w)` - *Re-fires the currently held key. Called from the event loop when the timer expires. Modifiers/keysym are recomputed from the live xkb_state, so a c...*
- `keyboard_key` (line 7975) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
- `keyboard_modifiers` (line 8014) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
- `keyboard_repeat_info` (line 8024) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
- `seat_caps` (line 8042) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` - *w->repeat_rate = rate; w->repeat_delay = delay; } static const struct wl_keyboard_listener keyboard_listener = { .keymap = keyboard_keymap, .enter ...*
- `seat_name` (line 8054) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (line 8060) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` - *w->pointer = wl_seat_get_pointer(seat); wl_pointer_add_listener(w->pointer, &pointer_listener, w); } if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && w-...*
- `registry_remove` (line 8081) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_browser` (line 8090) `ui_status ui_run_browser(const char *start_url)` - *w->data_device_manager = wl_registry_bind(reg, name, &wl_data_device_manager_interface, 1); } else if (strcmp(iface, zxdg_decoration_manager_v1_int...*

**Macros:**
- `_GNU_SOURCE` (line 11)
- `UI_TOOLBAR_H` (line 70)
- `UI_TITLEBAR_H` (line 72)
- `UI_TABBAR_H` (line 73)
- `UI_TAB_MIN_W` (line 74)
- `UI_TAB_MAX_W` (line 75)
- `UI_TAB_NEW_W` (line 76)
- `UI_TAB_CLOSE_W` (line 77)
- `UI_BTN_W` (line 78)
- `UI_WIN_BTN_W` (line 79)
- `UI_MARGIN` (line 80)
- `UI_BTN_LEFT` (line 81)
- `UI_LIST_INDENT` (line 82)
- `UI_SCROLLBAR_W` (line 87)
- `UI_SCROLLBAR_MIN` (line 88)
- `UI_SCROLLBAR_PAD` (line 89)
- `UI_RESIZE_MARGIN` (line 93)
- `UI_MENU_W` (line 98)
- `UI_MENU_ITEM_H` (line 99)
- `UI_MENU_PAD` (line 100)
- `UI_CHECK_SZ` (line 101)
- `UI_MENU_LABEL_H` (line 102)
- `UI_MENU_INPUT_H` (line 103)
- `UI_HAMBURGER_W` (line 104)
- `UI_HAMBURGER_GAP` (line 105)
- `UI_CURSOR_SIZE` (line 106)
- `UI_TOAST_PAD` (line 107)
- `OMNI_MAX_SUGG` (line 108)
- `UI_OMNI_ROW_H` (line 109)
- `UI_TWO_PI` (line 110)
- `UI_INPUT_PAD` (line 114)
- `UI_INPUT_WIDTH` (line 115)
- `UI_BUTTON_HPAD` (line 116)
- `UI_FORM_FIELDS_MAX` (line 117)
- `UI_UNDERLINE_OFFSET` (line 122)
- `UI_UNDERLINE_THICK` (line 123)
- `UI_STRIKE_OFFSET` (line 124)
- `UI_OVERLINE_OFFSET` (line 125)
- `UI_SLICE_MAX` (line 129)
- `UI_MENU_COUNT` (line 188)
- `UI_IMAGE_MAX_BODY` (line 206)
- `UI_MAX_TABS` (line 221)
- `UI_READER_COLUMN_W` (line 460)
- `JS_NAV_MAX` (line 1629)
- `JS_TICKS_PER_LOAD` (line 1702)
- `UI_RELOAD_X` (line 2369)
- `RC_BOX_STACK_MAX` (line 2572)
- `RC_MAX_OUT_OF_FLOW` (line 3617)
- `OV_MAX_DEPTH` (line 4551)
- `PDF_PAGE_W` (line 4774)
- `PDF_PAGE_H` (line 4775)
- `PDF_MARGIN` (line 4776)
- `PNG_PAGE_W` (line 4971)
- `PNG_MARGIN` (line 4972)
- `PNG_MAX_H` (line 4973)
- `FBW_W` (line 6577)
- `FBW_H` (line 6579)
- `FBW_HEADER` (line 6580)
- `FBW_PAD` (line 6581)
- `FBW_LINE` (line 6582)
- `FBW_GUTTER` (line 6583)
- `FBW_MIN_SPLIT` (line 6584)
- `FBW_MAX_SPLIT` (line 6585)

**Structs:**
- `ui_menu_item` (line 161)
- `ui_input_state` (line 199) - *Live editable state for one form text control, aliasing a block of the current rd_doc (not owned; valid until the doc is replaced). The field carri...*
- `ui_image` (line 212) - *A decoded image for one RD_IMAGE block of the current doc. surface owns the pixels (ARGB32) and is NULL when the image was blocked, not fetched, or...*
- `tab_ctx` (line 229) - *One tab's complete per-page state: everything that must persist when the tab is not the foreground one. The browser_window keeps the ACTIVE tab's c...*
- `browser_window` (line 242)
- `fetch_prep` (line 1282) - *Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post). Both MUST pass through the SAME host filter, per-host exception, ...*
- `fetch_job` (line 1360) - *A network request handed to the fetch thread. It owns deep copies of every input string (the window's buffers may change while the fetch runs), and...*
- `rc_frag` (line 2459)
- `rc_row` (line 2493)
- `rc_box` (line 2512) - *One painted block box (Hito 23b-8 Step C): a border-box rectangle in layout space with its author decoration, painted behind the rows it encloses. ...*
- `rc_layout` (line 2537)
- `rc_open_box` (line 2563) - *Box engine (Hito 23b-8 Step D): one entry of the open-box stack. A box's content rect (inner_left/inner_w) is the coordinate context its children (...*
- `rc_state` (line 2574)
- `rc_ext` (line 2852) - *Author text-presentation extensions for a block, derived from its rd_block (already * gated by caps.css upstream) and handed to flow_text.*
- `freebug_window` (line 6587)

#### `bui_theme.c`
**Path:** `gui/bui_theme.c`

**Functions:**
- `ui_theme_default` (line 14) `ui_theme ui_theme_default(void)` - *bui_theme — presentation palettes for the Wayland/Cairo GUI.  Carved out of browser_ui.c: the light/dark/sepia themes and the small colour helpers,...*
- `ui_theme_dark` (line 73) `ui_theme ui_theme_dark(void)` - *Dark reading palette. Shares all the metrics (font sizes, spacing) with the * default theme; only the colours change, so the box model stays in one...*
- `ui_theme_sepia` (line 118) `ui_theme ui_theme_sepia(void)` - *Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form text. Shares all the metrics with the default the...*
- `ui_theme_for` (line 160) `ui_theme ui_theme_for(int mode)` - *t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.menu_text      = (ui_rgb){ 0.26, 0.19, 0.10 }; ...*
- `rgb_from_packed` (line 169) `ui_rgb rgb_from_packed(int packed)` - *t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the theme mode to a palette. ui_theme ui_theme_for(...*
- `set_rgb` (line 173) `void set_rgb(cairo_t *cr, ui_rgb c)`

#### `freedom_view.c`
**Path:** `gui/freedom_view.c`

**Functions:**
- `main` (line 36) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 9)

#### `ui_render.c`
**Path:** `gui/ui_render.c`

**Functions:**
- `sanitize_utf8_inplace` (line 37) `static void sanitize_utf8_inplace(char *s)` - *Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence with '?'. cairo_show_text rejects invalid UTF-8 a...*
- `button_rects` (line 105) `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)` - *int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; double ptr_x, ptr_y; const char *title; const char *...*
- `buffer_release` (line 112) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` - *size_t      text_len; size_t      scroll; /* first visible line } ui_window; static void redraw(ui_window *w); /* Right-aligned control buttons: mi...*
- `destroy_buffer` (line 119) `static void destroy_buffer(ui_window *w)`
- `ensure_buffer` (line 125) `static int ensure_buffer(ui_window *w)`
- `paint` (line 156) `static void paint(ui_window *w)` - *WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (w->buffer == NULL) { munmap(data, size); return -1; } wl_buffer_add_listener(w->...*
- `redraw` (line 242) `static void redraw(ui_window *w)`
- `wm_base_ping` (line 257) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` - *Always repaint and re-commit. We do not gate on buffer release: a single shm buffer can be re-attached, and gating on release deadlocks against * c...*
- `xdg_surface_configure` (line 263) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (line 271) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `toplevel_close` (line 281) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (line 292) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` - *The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we draw our own titlebar; if server-side, we let it ...*
- `ptr_enter` (line 302) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` - *The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we draw our own titlebar; if server-side, we let it ...*
- `ptr_leave` (line 310) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (line 313) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `ptr_button` (line 320) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` - *ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); } static void ptr_leave(void *d, struct wl_point...*
- `ptr_axis` (line 342) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `seat_caps` (line 364) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (line 374) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (line 380) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` - *ui_window *w = (ui_window *)data; fprintf(stderr, "[ui] seat caps: pointer=%s\n", (caps & WL_SEAT_CAPABILITY_POINTER) ? "yes" : "no"); if ((caps & ...*
- `registry_remove` (line 399) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_text_view` (line 407) `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)` - *w->seat = wl_registry_bind(reg, name, &wl_seat_interface, 1); wl_seat_add_listener(w->seat, &seat_listener, w); } else if (strcmp(iface, zxdg_decor...*

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
- `fp_coarsen_time_ms` (line 16) `uint64_t fp_coarsen_time_ms(uint64_t raw_ms)`
- `fp_user_agent` (line 22) `const char *fp_user_agent(void)` - *#include "anti_fp.h" /* --- clocks --- uint64_t fp_timer_resolution_ms(void) { return FP_TIMER_RESOLUTION_MS; } uint64_t fp_coarsen_time_ms(uint64_...*
- `fp_accept_language` (line 26) `const char *fp_accept_language(void)`
- `fp_accept_language_header` (line 30) `const char *fp_accept_language_header(void)`
- `fp_timezone` (line 34) `const char *fp_timezone(void)`
- `fp_platform` (line 38) `const char *fp_platform(void)`
- `fp_vendor` (line 42) `const char *fp_vendor(void)`
- `fp_hardware_concurrency` (line 46) `int fp_hardware_concurrency(void)`
- `fp_device_memory_gb` (line 50) `int fp_device_memory_gb(void)`
- `fp_app_version` (line 56) `const char *fp_app_version(void)` - *const char *fp_vendor(void) { return ""; /* no vendor string: minimal entropy } int fp_hardware_concurrency(void) { return 2; /* fixed: do not reve...*
- `fp_app_code_name` (line 60) `const char *fp_app_code_name(void)`
- `fp_product` (line 64) `const char *fp_product(void)`
- `fp_app_name` (line 68) `const char *fp_app_name(void)`
- `fp_product_sub` (line 72) `const char *fp_product_sub(void)`
- `fp_oscpu` (line 76) `const char *fp_oscpu(void)`
- `fp_build_id` (line 80) `const char *fp_build_id(void)`
- `fp_max_touch_points` (line 84) `int fp_max_touch_points(void)`
- `fp_on_line` (line 88) `int fp_on_line(void)`
- `fp_cookie_enabled` (line 92) `int fp_cookie_enabled(void)`
- `fp_bucket_screen` (line 98) `void fp_bucket_screen(int w, int h, int *out_w, int *out_h)` - *int fp_max_touch_points(void) { return 0; } int fp_on_line(void) { return 1; } int fp_cookie_enabled(void) { return 1; } /* --- screen bucketing ---*
- `splitmix64` (line 120) `static uint64_t splitmix64(uint64_t *state)` - *long best_area = -1; size_t best = smallest; for (size_t i = 0; i < n; ++i) { if (buckets[i][0] <= w && buckets[i][1] <= h) { long area = (long)buc...*
- `fp_perturb` (line 127) `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
- `fp_origin_key` (line 138) `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`

#### `box_style.c`
**Path:** `src/box_style.c`

**Functions:**
- `lc` (line 23) `static char lc(char c)` - *Longest recognised tag is "blockquote" (10); longest display keyword is "inline-block" (12). The buffers are generous so a normal token always fits...*
- `is_ws` (line 27) `static int is_ws(char c)`
- `copy_lower_trim` (line 34) `static int copy_lower_trim(const char *in, char *out, size_t out_size)` - *Copies in into out, trimming ASCII whitespace and lowercasing. Returns 0 on * success, -1 if in is NULL, the trimmed token is empty, or it does not...*
- `name_cmp` (line 47) `static int name_cmp(const void *key, const void *elem)` - *Both row structs start with `const char *name`, so a pointer to a row is also a * pointer to its name field: one comparator serves both binary sear...*
- `bx_default_for_tag` (line 118) `bx_box bx_default_for_tag(const char *tag)` - *define TAG_N (sizeof TAG_TABLE / sizeof TAG_TABLE[0])*
- `bx_parse_display` (line 148) `bx_status bx_parse_display(const char *token, bx_display *out)` - *define DISP_N (sizeof DISP_TABLE / sizeof DISP_TABLE[0])*
- `bx_place` (line 158) `bx_hplace bx_place(double inset_l, double inset_r, double width_cap, int center,
                ...`
- `bx_width_cap` (line 175) `double bx_width_cap(int w_px, int w_pct, double avail_w)`
- `bx_content_cap` (line 183) `double bx_content_cap(double width_cap, int border_box,
                      double pad_l, doubl...`
- `bx_display_name` (line 194) `const char *bx_display_name(bx_display d)`

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
- `TAG_N` (line 117)
- `DISP_N` (line 147)

**Structs:**
- `tag_row` (line 53)
- `disp_row` (line 129)

#### `box_tree.c`
**Path:** `src/box_tree.c`

**Functions:**
- `layout_block` (line 32) `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` - *Block container: stack non-none children vertically, collapsing each child's top * margin with the previous child's bottom margin.*
- `bt_nn` (line 53) `static double bt_nn(double v)` - *if (cavail < 0.0) cavail = 0.0; bt_status r = layout_node(c, cavail, depth + 1); if (r != BT_OK) return r; double top_gap = (prev_bottom > c->margi...*
- `wrap_reverse` (line 73) `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...`
- `layout_grid` (line 196) `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...` - *Grid: sized columns via flex_layout (fixed px reserved first, the rest split by fr weight; a NULL grid_track keeps the historical equal columns), p...*
- `layout_node` (line 246) `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
- `bt_layout` (line 291) `bt_status bt_layout(bt_node *root, double avail_w)`
- `assign_doc_order` (line 332) `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` - *Recursive doc_order assignment. The box tree is acyclic (each box has at most one parent_id), so the visited bitmap is just a guard against the deg...*
- `find_positioned_ancestor` (line 349) `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` - *Walk the parent_id chain from `start` to find the nearest ancestor with position != STATIC. Returns the ancestor's index, or -1 if none exists (cal...*
- `resolve_inset` (line 363) `static double resolve_inset(int v)` - *Resolves an inset value: PV_LEN_UNSET or BT_LEN_AUTO → 0 (anchor at the * containing block's edge); otherwise the px value.*
- `bt_resolve_positioning` (line 367) `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`

**Macros:**
- `BT_LEN_AUTO` (line 26)
- `BT_WRAP_EPS` (line 56)

#### `browser.c`
**Path:** `src/browser.c`

**Functions:**
- `free_page` (line 13) `static void free_page(browser_state *bs)` - *include <stdlib.h> include <string.h>*
- `clear_status` (line 24) `static void clear_status(browser_state *bs)` - *#include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) { if (bs == NULL) return; free(bs->page_title); bs->page_title = N...*
- `free_history` (line 28) `static void free_history(browser_state *bs)`
- `free_exceptions` (line 38) `static void free_exceptions(browser_state *bs)`
- `is_https_url` (line 47) `static int is_https_url(const char *s)`
- `is_local_path` (line 51) `static int is_local_path(const char *s)`
- `url_is_allowed` (line 56) `static int url_is_allowed(const char *url)`
- `xstrdup` (line 70) `static char *xstrdup(const char *s)`
- `utf8_seq_len` (line 82) `static size_t utf8_seq_len(unsigned char c)` - *UTF-8 sequence length implied by a lead byte, or 0 for a continuation byte or * an invalid lead.*
- `cp1252_to_ucs` (line 93) `static unsigned int cp1252_to_ucs(unsigned char c)` - *Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0.. 0xFF map identically to Latin-1; 0x80..0x9F carry the Windows-1252 g...*
- `utf8_encode` (line 107) `static size_t utf8_encode(unsigned int cp, char *out)` - *Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the * byte count written.*
- `browser_init` (line 159) `browser_status browser_init(browser_state *bs)`
- `browser_free` (line 170) `void browser_free(browser_state *bs)`
- `browser_set_url_bar` (line 181) `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
- `browser_commit_url_bar` (line 193) `browser_status browser_commit_url_bar(browser_state *bs)`
- `browser_navigate` (line 198) `browser_status browser_navigate(browser_state *bs, const char *url)`
- `browser_back` (line 233) `browser_status browser_back(browser_state *bs)`
- `browser_forward` (line 245) `browser_status browser_forward(browser_state *bs)`
- `browser_can_back` (line 257) `int browser_can_back(const browser_state *bs)`
- `browser_can_forward` (line 261) `int browser_can_forward(const browser_state *bs)`
- `browser_current_url` (line 265) `const char *browser_current_url(const browser_state *bs)`
- `browser_url_bar_selection` (line 270) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
- `browser_url_bar_delete_selection` (line 281) `int browser_url_bar_delete_selection(browser_state *bs)`
- `browser_url_bar_insert` (line 291) `browser_status browser_url_bar_insert(browser_state *bs, char c)`
- `browser_url_bar_backspace` (line 306) `browser_status browser_url_bar_backspace(browser_state *bs)`
- `browser_url_bar_delete` (line 320) `browser_status browser_url_bar_delete(browser_state *bs)`
- `browser_url_bar_move_cursor` (line 331) `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
- `browser_url_bar_extend_cursor` (line 341) `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
- `browser_url_bar_set_cursor` (line 350) `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
- `browser_url_bar_select_all` (line 358) `browser_status browser_url_bar_select_all(browser_state *bs)`
- `browser_url_bar_clear` (line 365) `browser_status browser_url_bar_clear(browser_state *bs)`
- `browser_set_page` (line 374) `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
- `browser_set_status` (line 396) `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
- `browser_status_text` (line 410) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
- `host_equal` (line 418) `static int host_equal(const char *a, const char *b)` - *if (n >= BROWSER_STATUS_MAX) n = BROWSER_STATUS_MAX - 1; memcpy(bs->status_msg, msg, n); bs->status_msg[n] = '\0'; bs->status_expiry_ms = now_ms + ...*
- `browser_is_exception` (line 429) `int browser_is_exception(const browser_state *bs, const char *host)`
- `browser_add_exception` (line 437) `browser_status browser_add_exception(browser_state *bs, const char *host)`

**Macros:**
- `_POSIX_C_SOURCE` (line 6)

#### `css.c`
**Path:** `src/css.c`

**Functions:**
- `parse_num` (line 142) `static int parse_num(const char *s, double *out, const char **endp)` - *Parses a leading non-negative number (digits + optional fraction). Returns 1 on * success, setting *out and *endp to the first unconsumed char.*
- `round_clamp` (line 162) `static int round_clamp(double v, int lo, int hi)` - *Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the cast avoids undefined behaviour: casting an out-of-range double (e...*
- `interp_color` (line 169) `static int interp_color(const char *v)` - *Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the cast avoids undefined behaviour: casting an out-of-range double (e...*
- `interp_bg` (line 174) `static int interp_bg(const char *v)`
- `gradient` (line 205) `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
- `find_linear_gradient` (line 253) `static int find_linear_gradient(const char *v, size_t *start, size_t *end,
                      ...` - *Locates a plain linear-gradient(...) call in v (case-insensitive; an occurrence that is the tail of a longer ident, e.g. repeating-linear-gradient,...*
- `CSS_GRAD_STOPS_MAX` (line 287) `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when the
 * gradient fai...`
- `emit_gradient` (line 343) `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops, const int *colors)` - *Emits the gradient decl group. nstops == 0 emits only the explicit reset * (P_BG_GRAD_N = 0), which is how a shorthand clears a lower-tier gradient.*
- `expand_bg_image` (line 363) `static int expand_bg_image(const char *val, css_decl *dst, int cap)` - *background-image: linear-gradient resolves to the gradient group; url()/none/ radial/conic/repeating-gradients/malformed all emit the explicit grad...*
- `path` (line 375) `* nor a gradient keeps the historical drop path (url()-only stays unset). */
static int expand_ba...`
- `interp_align` (line 400) `static int interp_align(const char *v)`
- `interp_fontsize` (line 408) `static int interp_fontsize(const char *v)`
- `interp_lineheight` (line 435) `static int interp_lineheight(const char *v)` - *line-height as a percent of the natural line box. A unitless multiplier ("1.5" -> 150) or a percent ("160%" -> 160); "normal" is unset (the UA defa...*
- `interp_weight` (line 449) `static int interp_weight(const char *v)`
- `interp_style` (line 458) `static int interp_style(const char *v)`
- `interp_textdeco` (line 469) `static int interp_textdeco(const char *v)` - *text-decoration / text-decoration-line: OR of the line keywords underline / overline / line-through found in the (space-separated) value. "none" ->...*
- `interp_display` (line 488) `static int interp_display(const char *v)`
- `interp_gap` (line 507) `static int interp_gap(const char *v)` - *One gap length. Reuses interp_len (px / em / rem / bare 0 / calc() / math functions), so a `gap: 1em` is 16px instead of the old misparse-as-1px, a...*
- `interp_justify` (line 513) `static int interp_justify(const char *v)`
- `count_tracks` (line 539) `static int count_tracks(const char *s, size_t n)`
- `track_size_of` (line 548) `static int track_size_of(const char *tok)` - *Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0); minmax(a,b) -> the size of its max component b; auto/%/unknown -> 0 (...*
- `count_one_repeat` (line 577) `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
- `walk_tracks` (line 620) `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
- `expand_grid_template_cols` (line 681) `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` - *grid-template-columns: track count PLUS the first CSS_GRID_TRACKS_MAX track sizes, emitted in lock-step (P_GRIDCOLS + P_GRID_TRACK0..7; unsized slo...*
- `calc_skip_ws` (line 719) `static void calc_skip_ws(calc_parser *p)`
- `calc_match_fn` (line 727) `static int calc_match_fn(calc_parser *p, const char *name)` - *Max arguments of one min()/max() call (clamp() takes exactly three). More fail * the declaration (anti-DoS; the whole value already fits one CSS_TO...*
- `calc_mathfn` (line 742) `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` - *min()/max()/clamp() (2026-07-10): comma-separated full expressions, every argument the same shape (all lengths or all bare numbers, like +/-). clam...*
- `calc_term` (line 826) `static int calc_term(calc_parser *p, calc_val *out, int depth)` - *} if (p->i + 3 <= p->n && csel_lower_ch(p->s[p->i]) == 'r' && csel_lower_ch(p->s[p->i + 1]) == 'e' && csel_lower_ch(p->s[p->i + 2]) == 'm') { out->...*
- `calc_expr` (line 845) `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
- `calc_eval` (line 863) `static int calc_eval(const char *v, size_t vlen, double *out_px)` - *Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching ")" already stripped by the caller). Fails closed on any leftover/u...*
- `calc_unwrap` (line 876) `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` - *True if s (already trimmed) is a "calc(...)" call spanning the whole string (case-insensitive keyword, balanced trailing paren); on success the arg...*
- `interp_len` (line 893) `static int interp_len(const char *v, int allow_auto, int *out)` - *Parses one box-model length. Accepts "Npx", a bare "0", "Nem"/"Nrem" (x16 px, the engine's base font), "calc(...)" over the same units (+, -, *, /,...*
- `emit_len` (line 951) `static int emit_len(css_decl *dst, int cap, int slot, const char *val,
                    int al...` - *Emits one box length declaration for slot into dst (cap permitting). A negative value is rejected unless allow_neg (margins allow it; padding/width...*
- `emit_pct` (line 965) `static int emit_pct(css_decl *dst, int cap, int slot, const char *val)` - *Emits a symbolic percentage width for slot (Hito 32): "<num>%" with num > 0, carried as per-mille (99.8% -> 998) and saturating at 1000% (10000). T...*
- `interp_len` (line 990) `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
- `expand_box2` (line 1046) `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...` - *Expands a two-slot logical shorthand (margin-inline / padding-block / inset-inline: one value sets both sides, two set start then end; 2026-07-10)....*
- `family_of` (line 1069) `static int family_of(const char *name)` - *Maps one font-family name (a generic keyword or a common family) to a generic css_font_family bucket; -1 if unrecognised. Case-insensitive; multi-w...*
- `interp_fontfamily` (line 1094) `static int interp_fontfamily(const char *v)` - *font-family: the first recognised name in the comma-separated stack wins (its * generic bucket). Quotes are stripped. url() defensively dropped. -1...*
- `interp_texttransform` (line 1115) `static int interp_texttransform(const char *v)`
- `interp_valign` (line 1137) `static int interp_valign(const char *v)`
- `interp_whitespace` (line 1144) `static int interp_whitespace(const char *v)`
- `interp_tabsize` (line 1158) `static int interp_tabsize(const char *v)` - *break-spaces preserves whitespace and wraps; this engine only models the * wrap/keep distinction, so it collapses to pre-wrap (2026-07-10). if (cse...*
- `interp_textdeco_style` (line 1169) `static int interp_textdeco_style(const char *v)` - *} /* tab-size: a non-negative integer (number of spaces). -1 if unsupported. static int interp_tabsize(const char *v) { double num; const char *end...*
- `interp_textdeco_thickness` (line 1180) `static int interp_textdeco_thickness(const char *v)` - *text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length * (px -> px, em/rem x16). -1 if unsupported (negative, %, etc -> dr...*
- `interp_aspect_ratio` (line 1192) `static int interp_aspect_ratio(const char *v, int *num, int *den)` - *aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>` (auto fallback). Stores both numerator and denominator x1000 (for sub-...*
- `interp_direction` (line 1225) `static int interp_direction(const char *v)` - *num = round_clamp(nv * 1000.0, 1, CSS_LEN_MAX); den = round_clamp(dv * 1000.0, 1, CSS_LEN_MAX); return 1; } /* Bare number: treat as w/h = N/1 doub...*
- `liststyle_kw` (line 1230) `static int liststyle_kw(const char *t)`
- `interp_liststyle` (line 1246) `static int interp_liststyle(const char *v)` - *list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a list-style-image) is dropped: never f...*
- `emit_spacing` (line 1275) `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `expand_shadow` (line 1289) `static int expand_shadow(const char *val, css_decl *dst, int cap)` - *text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in any order. "none" emits an expl...*
- `interp_position` (line 1320) `static int interp_position(const char *v)` - *} if (nlen < 2) return 0;  /* need both offsets int dx = lens[0], dy = lens[1]; if (dx > CSS_SHADOW_MAX) dx = CSS_SHADOW_MAX; if (dx < -CSS_SHADOW_...*
- `interp_boxsizing` (line 1329) `static int interp_boxsizing(const char *v)`
- `interp_float` (line 1335) `static int interp_float(const char *v)`
- `interp_clear` (line 1342) `static int interp_clear(const char *v)`
- `interp_visibility` (line 1352) `static int interp_visibility(const char *v)` - *if (csel_ci_eq(v, "left"))  return CSS_FLOAT_LEFT; if (csel_ci_eq(v, "right")) return CSS_FLOAT_RIGHT; return -1; } static int interp_clear(const c...*
- `interp_overflow` (line 1359) `static int interp_overflow(const char *v)`
- `expand_overflow` (line 1371) `static int expand_overflow(const char *val, css_decl *dst, int cap)` - *`overflow: X` sets both overflow-x and overflow-y to the same value. The two-token * per-axis form (`overflow: hidden visible`) is out of scope -- ...*
- `interp_cursor` (line 1378) `static int interp_cursor(const char *v)`
- `interp_text_overflow` (line 1394) `static int interp_text_overflow(const char *v)`
- `interp_word_break` (line 1400) `static int interp_word_break(const char *v)`
- `interp_overflow_wrap` (line 1407) `static int interp_overflow_wrap(const char *v)`
- `interp_border_collapse` (line 1416) `static int interp_border_collapse(const char *v)` - *if (csel_ci_eq(v, "normal"))    return CSS_WB_NORMAL; if (csel_ci_eq(v, "break-all")) return CSS_WB_BREAK; if (csel_ci_eq(v, "keep-all"))  return C...*
- `number` (line 1425) `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
- `interp_empty_cells` (line 1450) `static int interp_empty_cells(const char *v)` - *if (interp_len(tok, 0, &px) && px >= 0) { if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX; return px; } double num; const char *end; i...*
- `interp_caption_side` (line 1457) `static int interp_caption_side(const char *v)` - *px = round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; } /* empty-cells: show/hide. -1 unknown. static int interp_empty_cells(co...*
- `interp_table_layout` (line 1464) `static int interp_table_layout(const char *v)` - *static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v, "hide")) return CSS_EC_HIDE; return...*
- `interp_font_variant` (line 1471) `static int interp_font_variant(const char *v)` - *static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v, "bottom")) return CSS_CS_BOTTOM; ...*
- `interp_hyphens` (line 1479) `static int interp_hyphens(const char *v)` - *if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; } /* font-variant (subset: only small-c...*
- `interp_user_select` (line 1487) `static int interp_user_select(const char *v)` - *if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail closed return -1; } /* hyphens: ...*
- `interp_caret_color` (line 1496) `static int interp_caret_color(const char *v)` - *if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; } /* user-select: none/text/all/auto. -1 unknown. static int interp_user_select(const c...*
- `interp_appearance` (line 1503) `static int interp_appearance(const char *v)` - *if (csel_ci_eq(v, "text")) return CSS_US_TEXT; if (csel_ci_eq(v, "all"))  return CSS_US_ALL; if (csel_ci_eq(v, "auto")) return CSS_US_AUTO; return ...*
- `interp_pointer_events` (line 1510) `static int interp_pointer_events(const char *v)` - *static int interp_caret_color(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO; cc_rgb c; return (cc_parse(v, &c) == CC_OK) ? cc_pac...*
- `interp_bg_repeat` (line 1517) `static int interp_bg_repeat(const char *v)` - *static int interp_appearance(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_AP_AUTO; if (csel_ci_eq(v, "none")) return CSS_AP_NONE; return ...*
- `interp_bg_size` (line 1527) `static int interp_bg_size(const char *v)` - *return -1; } /* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. static int interp_bg_repeat(const char *v) { if (cse...*
- `interp_bg_clip` (line 1534) `static int interp_bg_clip(const char *v)` - *if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X; if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y; if (csel_ci_eq(v, "space"))     r...*
- `interp_bg_origin` (line 1542) `static int interp_bg_origin(const char *v)` - *if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if (csel_ci_eq(v, "contain")) return CSS_BGS...*
- `interp_bg_attachment` (line 1549) `static int interp_bg_attachment(const char *v)` - *if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return CSS_BGC_PADDING_BOX; if (csel_ci_eq(v, "con...*
- `interp_isolation` (line 1556) `static int interp_isolation(const char *v)` - *static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if (csel_ci_eq(v, "border-box"))   retu...*
- `interp_contain` (line 1562) `static int interp_contain(const char *v)` - */* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if (csel_ci_eq(v, "scroll")) return CSS_...*
- `interp_content_visibility` (line 1583) `static int interp_content_visibility(const char *v)` - *while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k ...*
- `interp_image_rendering` (line 1590) `static int interp_image_rendering(const char *v)` - *else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |= CSS_CONTAIN_STYLE; else if (csel_ci_eq(...*
- `interp_color_scheme` (line 1597) `static int interp_color_scheme(const char *v)` - *static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if (csel_ci_eq(v, "auto"))    return CSS...*
- `interp_accent_color` (line 1615) `static int interp_accent_color(const char *v)` - *const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p ...*
- `interp_print_color_adjust` (line 1621) `static int interp_print_color_adjust(const char *v)` - *while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if (csel_ci_eq(tok, "light")) return CSS_CSH_LI...*
- `interp_forced_color_adjust` (line 1627) `static int interp_forced_color_adjust(const char *v)` - *} /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int interp_accent_color(const char *v) { if (csel_ci_eq(v, "auto")) ...*
- `interp_mix_blend_mode` (line 1634) `static int interp_mix_blend_mode(const char *v)` - */* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if (csel_ci_eq(v, "economy")) return CSS_PC...*
- `interp_object_fit` (line 1652) `static int interp_object_fit(const char *v)` - *if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY; if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN; if (csel_ci_eq(v, "lighten"))   ...*
- `interp_list_style_pos` (line 1661) `static int interp_list_style_pos(const char *v)` - *if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR; if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY; return -1; } /* object-fit: fi...*
- `interp_font_kerning` (line 1667) `static int interp_font_kerning(const char *v)` - *if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if (csel_ci_eq(v, "cover"))       ...*
- `interp_text_rendering` (line 1674) `static int interp_text_rendering(const char *v)` - */* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if (csel_ci_eq(v, "inside"))  return CSS_LP_I...*
- `interp_font_stretch` (line 1682) `static int interp_font_stretch(const char *v)` - *if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if (csel_ci_eq(v, "none"))   return CSS_FK_NONE...*
- `interp_resize` (line 1695) `static int interp_resize(const char *v)` - */* font-stretch: normal/condensed/expanded/etc. -1 unknown. static int interp_font_stretch(const char *v) { if (csel_ci_eq(v, "normal"))           ...*
- `interp_scroll_behavior` (line 1703) `static int interp_scroll_behavior(const char *v)` - *if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))     return CSS_FS_EXTRA_EXPANDED; if (cs...*
- `interp_touch_action` (line 1709) `static int interp_touch_action(const char *v)` - *static int interp_resize(const char *v) { if (csel_ci_eq(v, "none"))        return CSS_RS_NONE; if (csel_ci_eq(v, "both"))        return CSS_RS_BOT...*
- `interp_overscroll_behavior` (line 1716) `static int interp_overscroll_behavior(const char *v)` - */* scroll-behavior: auto/smooth. -1 unknown. static int interp_scroll_behavior(const char *v) { if (csel_ci_eq(v, "auto"))   return CSS_SB_AUTO; if...*
- `interp_backface_visibility` (line 1723) `static int interp_backface_visibility(const char *v)` - *static int interp_touch_action(const char *v) { if (csel_ci_eq(v, "auto"))         return CSS_TA_AUTO; if (csel_ci_eq(v, "none"))         return CS...*
- `interp_border_style` (line 1745) `static int interp_border_style(const char *v)`
- `interp_bwidth1` (line 1771) `static int interp_bwidth1(const char *v)`
- `interp_border_radius` (line 1779) `static int interp_border_radius(const char *v)` - *border-radius: the first value only (corner-by-corner / elliptical out of scope). * px >= 0, or -1 (unsupported: %/units dropped -> stays unset).*
- `interp_bw_tok` (line 1793) `static int interp_bw_tok(const char *t, int *o)` - *static int interp_border_radius(const char *v) { char tok[CSS_TOK_MAX]; size_t k = 0; const char *p = v; while (*p == ' ' || *p == '\t') ++p; while...*
- `interp_bs_tok` (line 1794) `static int interp_bs_tok(const char *t, int *o)`
- `interp_bc_tok` (line 1795) `static int interp_bc_tok(const char *t, int *o)`
- `expand_outline` (line 1859) `static int expand_outline(const char *val, css_decl *dst, int cap)`
- `expand_box_shadow` (line 1874) `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` - *box-shadow (single layer): up to four lengths in order dx, dy, blur, spread, an optional color, and an optional `inset` keyword, in any order. Need...*
- `interp_flex_factor` (line 1903) `static int interp_flex_factor(const char *v)` - *flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to * [0, CSS_FLEX_FACTOR_MAX]. Negative / unparseable -> -1 (droppe...*
- `expand_flex` (line 1924) `static int expand_flex(const char *val, css_decl *dst, int cap)` - *flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots. Keywords none/auto/initial; otherwise up to three values (a unitless number ...*
- `interp_align_kw` (line 1964) `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` - *align-items / align-self / align-content / justify-items keyword. allow_auto is for * align-self; allow_dist (space-*) is for align-content. Unknow...*
- `interp_flex_direction` (line 1976) `static int interp_flex_direction(const char *v)`
- `interp_flex_wrap` (line 1984) `static int interp_flex_wrap(const char *v)`
- `interp_grid_flow` (line 1993) `static int interp_grid_flow(const char *v)` - *if (csel_ci_eq(v, "row-reverse")) return CSS_FD_ROW_REVERSE; if (csel_ci_eq(v, "column")) return CSS_FD_COLUMN; if (csel_ci_eq(v, "column-reverse")...*
- `interp_grid_span` (line 2019) `static int interp_grid_span(const char *v)` - *grid-column / grid-row: only the `span N` form is supported -> N (clamped to * [1, CSS_GRID_SPAN_MAX]). Line-number / named-line placement is out o...*
- `copy_trim` (line 2038) `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` - *Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from * both ends. Returns the trimmed length, or SIZE_MAX if it does no...*
- `strip_important` (line 2051) `static int strip_important(char *val)` - *Strips a trailing "!important" (case-insensitive, with optional whitespace before '!' and between '!' and the keyword) from val, in place. Returns ...*
- `var_append` (line 2132) `static int var_append(char *out, size_t outcap, size_t *o, const char *s, size_t n)` - *} } i = v; continue; } } ++i; } } static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap, size_t *o, const css_custom_pr...*
- `value` (line 2159) `* any other unsupported value (fail closed, never a partially-substituted value). */
static int r...`
- `overflowed` (line 2219) `* overflowed (caller drops the declaration). */
static int resolve_var(const char *val, char *out...`
- `expand_gap` (line 2233) `static int expand_gap(const char *val, css_decl *dst, int cap)` - *gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both axes; row-gap stays unset and falls back to gap downstream), two valu...*
- `ignored` (line 2252) `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...`
- `shorthand` (line 2289) `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
- `caller` (line 2346) `* left to the caller (parse_one_decl stamps it). */
static int interpret_prop(const char *prop, c...`
- `interpret_decls` (line 2638) `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` - *Splits a ';'-separated declaration block into dst (up to cap). Returns count. tab/ntab is the custom-property table var() resolves against (NULL/0 ...*
- `add_rule` (line 2651) `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` - *e.g. an inline style resolved against a NULL sheet). static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap, const css_cu...*
- `skip_at_rule` (line 2687) `static size_t skip_at_rule(const char *s, size_t i, size_t n)` - *Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a * brace-balanced block. Returns the index just past it.*
- `block_end` (line 2703) `static size_t block_end(const char *s, size_t open, size_t n)` - *Index just past the '}' that closes the block whose '{' is at s[open]. n if * unbalanced.*
- `trim_inplace` (line 2725) `static void trim_inplace(char *s)` - *-- @media query evaluation (Hito 23b). All inputs are bounded substrings; the * query never fetches and unknown features fail closed (do not match)...*
- `copy_lower_trim` (line 2734) `static size_t copy_lower_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` - *const char *e; return parse_num(v, &d, &e) ? round_clamp(d, 0, CSS_LEN_MAX) : 0; } /* Trims ASCII spaces/tabs from both ends of a NUL-terminated st...*
- `media_part_matches` (line 2743) `static int media_part_matches(const char *p, const css_media *m)` - *One media part: a type word ("screen"/"print"/"all") or a "(feature: value)". * p is already lowercased and trimmed. Unknown -> 0 (fail closed).*
- `media_segment_matches` (line 2772) `static int media_segment_matches(const char *s, size_t a, size_t b, const css_media *m)` - *One media query segment (between commas): an AND of parts. `not`/`or`/unknown * fail closed. An empty segment matches (all).*
- `media_matches` (line 2809) `static int media_matches(const char *s, size_t a, size_t b, const css_media *m)` - *if (strcmp(buf, "and") == 0 || strcmp(buf, "only") == 0) { /* connector / legacy keyword: ignore } else if (strcmp(buf, "not") == 0 || strcmp(buf, ...*
- `at_is_media` (line 2823) `static int at_is_media(const char *s, size_t i, size_t n)` - *static int media_matches(const char *s, size_t a, size_t b, const css_media *m) { while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s...*
- `parse_block` (line 2836) `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` - *Parses rules in s[start,end). A matched @media block is descended into (bounded * depth); @import/@font-face/other @-rules and a non-matching @medi...*
- `strip_comments` (line 2878) `static char *strip_comments(const char *text, size_t len, size_t *outlen)` - *Removes C-style block comments into a fresh NUL-terminated buffer (each comment * becomes one space). Caller frees.*
- `css_parse` (line 2896) `css_status css_parse(const char *text, size_t len, css_sheet **out)`
- `css_parse_media` (line 2900) `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
- `css_free` (line 2920) `void css_free(css_sheet *s)`
- `apply_decl` (line 2930) `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, const css_decl *d,
              ...` - *Applies one declaration to the running style if it wins its property slot. The cascade is two-tiered: an !important declaration beats any non-impor...*
- `css_resolve_el` (line 3089) `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
- `css_resolve` (line 3212) `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
- `css_parse_inline` (line 3223) `css_style css_parse_inline(const char *style, size_t len)`

**Macros:**
- `CSS_MAX_SELS` (line 34)
- `CSS_MAX_DECLS` (line 35)
- `CSS_MAX_RULES` (line 36)
- `CSS_SELS_PER_GROUP` (line 37)
- `CSS_INLINE_DECLS` (line 38)
- `CSS_INLINE_SPEC` (line 39)
- `CSS_MAX_CUSTOM_PROPS` (line 50)
- `CSS_VAR_MAX_DEPTH` (line 51)
- `CSS_CALC_MAX_DEPTH` (line 711)
- `CSS_MATHFN_MAX_ARGS` (line 715)
- `CSS_MEDIA_TOK` (line 2714)
- `CSS_MEDIA_MAX_DEPTH` (line 2831)

**Structs:**
- `css_decl` (line 110)
- `css_custom_prop` (line 118) - *One custom property (--name: value), for var() lookups. Both fields are bounded * like every other token buffer here.*
- `css_sheet` (line 126)
- `calc_val` (line 717)
- `calc_parser` (line 718)

#### `css_chain.c`
**Path:** `src/css_chain.c`

**Functions:**
- `fill_css_node` (line 35) `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` - *Fills *node with element e's tag/id/class tokens (no style=, no parent link yet). * Over-long tokens are simply absent, which fails closed (does no...*
- `sibling_position` (line 116) `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` - *Computes the 1-based index of n among its ELEMENT siblings and the total element-sibling count (both walks bounded, anti-DoS: past CCH_NTH_MAX the ...*
- `inputs` (line 139) `* identical inputs (single source of truth). */
static const css_element *build_chain(lxb_dom_ele...`
- `cch_element_matches` (line 195) `int cch_element_matches(lxb_dom_element_t *el, const css_sel *sel)`

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
- `ascii_lower` (line 108) `static int ascii_lower(int c)`
- `hex_val` (line 112) `static int hex_val(int c)`
- `normalize` (line 122) `static int normalize(const char *token, char *out)` - *Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). * Returns 0, or -1 if the trimmed token is empty or does not fit.*
- `parse_hex` (line 136) `static int parse_hex(const char *s, cc_rgb *out)` - *static int normalize(const char *token, char *out) { size_t start = 0; while (token[start] == ' ' || token[start] == '\t') ++start; size_t end = st...*
- `parse_component` (line 162) `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` - *Parses one rgb() component in [b, e). For a color channel, the value is an integer 0..255 or a percentage 0%..100% (rounded). For the alpha channel...*
- `parse_func` (line 196) `static int parse_func(const char *s, cc_rgb *out)` - *v = v * 10 + (*p - '0'); if (v > 100000) return -1; } if (percent) { if (v > CC_PERCENT_MAX) return -1; out = (int)((v * CC_CHANNEL_MAX + CC_PERCEN...*
- `named_cmp` (line 230) `static int named_cmp(const void *key, const void *element)`
- `parse_named` (line 236) `static int parse_named(const char *s, cc_rgb *out)`
- `cc_parse` (line 246) `cc_status cc_parse(const char *token, cc_rgb *out)`
- `cc_pack` (line 267) `int cc_pack(cc_rgb c)`
- `cc_unpack` (line 271) `cc_rgb cc_unpack(int packed)`

**Macros:**
- `CC_TOKEN_MAX` (line 18)
- `CC_CHANNEL_MAX` (line 21)
- `CC_PERCENT_MAX` (line 22)

**Structs:**
- `cc_named` (line 24)

#### `css_select.c`
**Path:** `src/css_select.c`

**Functions:**
- `parse_attr_sel` (line 16) `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` - *Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am. Advances *ip past the closing ']'. Returns 1 if supported, 0 (fai...*
- `parse_nth_arg` (line 73) `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` - *Parses the An+B argument of the nth-child family, s[a,b) (surrounding space trimmed here). Accepts odd/even, N, An, An+B, An-B, n, -n+B, +n... (spa...*
- `parse_compound` (line 179) `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp)` - *Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space) * into *cp. Returns 1 if supported (type, .class, #id, *, [attr], :...*
- `selector` (line 237) `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
- `el_attr_value` (line 304) `static const char *el_attr_value(const css_element *el, const char *name)` - *The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no value reads as "".*
- `ends_with` (line 314) `static int ends_with(const char *v, const char *suf, int ci)` - *The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no value reads as "". static const cha...*
- `has_word` (line 322) `static int has_word(const char *v, const char *w, int ci)` - *True if `v` is a whitespace-separated list containing the word `w` (non-empty), * case-folded when ci (the `~=` operator).*
- `attr_matches` (line 337) `static int attr_matches(const css_attr_match *am, const css_element *el)` - *size_t wl = strlen(w); if (wl == 0) return 0; const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' ||...*
- `nth_matches` (line 357) `static int nth_matches(int A, int B, int idx)` - *True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling position" and never matches (fail ...*
- `is_form_control` (line 366) `static int is_form_control(const char *tag)` - *True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling position" and never matches (fail ...*
- `compound_matches` (line 405) `static int compound_matches(const css_compound *c, const css_element *el)` - *case PSEUDO_ONLY_CHILD:   return el->nth == 1 && el->nsib == 1; case PSEUDO_NTH_CHILD:    return nth_matches(pm->a, pm->b, el->nth); case PSEUDO_NT...*
- `sibling` (line 428) `* tries each preceding sibling (the recursion backtracks). Bounded by k
 * (<= CSS_MAX_COMPOUNDS)...`
- `csel_matches` (line 449) `int csel_matches(const css_sel *sel, const css_element *el)`

#### `disk_store.c`
**Path:** `src/disk_store.c`

**Functions:**
- `write_full` (line 27) `static int write_full(int fd, const void *buf, size_t n)` - *#include "disk_store.h" #include "local_store.h" #include <errno.h> #include <fcntl.h> #include <stdint.h> #include <stdio.h> #include <stdlib.h> #...*
- `read_full` (line 38) `static int read_full(int fd, void *buf, size_t n)`
- `fsync_dir` (line 53) `static void fsync_dir(const char *path)` - *Best-effort fsync of the directory holding path, for crash durability of the * rename. Failures are non-fatal (some filesystems do not support it).*
- `map_ls` (line 70) `static ds_status map_ls(ls_status s)`
- `ds_write` (line 86) `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...` - *switch (s) { case LS_OK:            return DS_OK; case LS_ERR_NULL_ARG:  return DS_ERR_NULL_ARG; case LS_ERR_TOO_LARGE: return DS_ERR_TOO_LARGE; ca...*
- `ds_read` (line 122) `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
- `ds_free` (line 155) `void ds_free(uint8_t *buf, size_t len)`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)

#### `dom.c`
**Path:** `src/dom.c`

**Functions:**
- `to_lower_buf` (line 32) `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` - *#include <stdint.h> #include <stdlib.h> #include <string.h> #include <lexbor/dom/dom.h> #include <lexbor/html/html.h> /* --- small character helper...*
- `fnv1a` (line 42) `static uint64_t fnv1a(const char *s, size_t n)`
- `ptr_hash` (line 51) `static size_t ptr_hash(const void *p)`
- `sm_entry_append` (line 76) `static int sm_entry_append(sm_entry *e, dom_node_id id)`
- `sm_grow` (line 88) `static int sm_grow(strmap *m)`
- `sm_put` (line 105) `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)`
- `sm_find` (line 132) `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)`
- `sm_free` (line 144) `static void sm_free(strmap *m)`
- `pm_grow` (line 171) `static int pm_grow(ptrmap *m)`
- `pm_put` (line 188) `static int pm_put(ptrmap *m, const void *key, dom_node_id id)`
- `pm_get` (line 205) `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)`
- `pm_free` (line 216) `static void pm_free(ptrmap *m)`
- `node_next` (line 238) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` - */* --- the index --- struct dom_index { lxb_dom_node_t      **nodes;    /* arena: id -> element node, in document order size_t                count...*
- `valid` (line 247) `static int valid(const dom_index *idx, dom_node_id n)`
- `index_element` (line 253) `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` - *if (node->first_child != NULL) return node->first_child; while (node != root && node->next == NULL) { if (node->parent == NULL) return NULL; node =...*
- `dom_build` (line 289) `dom_status dom_build(const hp_document *doc, dom_index **out)` - *} size_t tlen = 0; const lxb_char_t *tag = lxb_dom_element_qualified_name(el, &tlen); if (tag != NULL && tlen > 0) { char lower[256]; if (to_lower_...*
- `dom_free` (line 330) `void dom_free(dom_index *idx)`
- `dom_node_count` (line 342) `size_t dom_node_count(const dom_index *idx)` - *return DOM_ERR_OOM; } void dom_free(dom_index *idx) { if (idx == NULL) return; free(idx->nodes); sm_free(&idx->by_id); sm_free(&idx->by_tag); sm_fr...*
- `dom_get_element_by_id` (line 346) `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
- `copy_ids` (line 352) `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
- `dom_get_by_tag` (line 359) `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
- `dom_get_by_class` (line 368) `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
- `id_of` (line 382) `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` - *Max complex selectors in one comma-separated list. A longer list is truncated * (anti-DoS): the extra selectors are dropped, which only narrows mat...*
- `parse_selector_list` (line 392) `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` - *Parses a selector list "a, b, c" into up to cap css_sel. Splits only on TOP-LEVEL commas (respecting [], () and quotes so `[a="x,y"]` and `:not(a,b...*
- `node_matches_any` (line 425) `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` - *s.order = (int)n; s.rule = 0; out[n++] = s; } } start = i + 1; } break; default: break; } } return n; } /* Nonzero iff element node `cn` matches an...*
- `count` (line 436) `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
- `dom_query_selector` (line 465) `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
- `dom_query_selector_all` (line 474) `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
- `dom_matches` (line 485) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
- `dom_closest` (line 494) `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
- `dom_document_position` (line 510) `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
- `dom_precedes` (line 515) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
- `dom_node_at` (line 520) `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
- `dom_parent` (line 525) `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
- `dom_first_child` (line 535) `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
- `dom_next_sibling` (line 543) `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
- `dom_tag_name` (line 551) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_get_attribute` (line 562) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_attribute_names` (line 575) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
- `dom_text_content` (line 593) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_document_title` (line 603) `const char *dom_document_title(const dom_index *idx, size_t *len)`
- `dom_set_text_content` (line 616) `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...` - *} const char *dom_document_title(const dom_index *idx, size_t *len) { if (len != NULL) *len = 0; if (idx == NULL || idx->document == NULL) return N...*
- `dom_set_document_title` (line 641) `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
- `idx_push` (line 653) `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` - *return DOM_OK; } dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) { if (idx == NULL || idx->document == NULL) return...*
- `dom_create_element` (line 669) `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
- `dom_append_child` (line 689) `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_remove_child` (line 703) `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_set_attribute` (line 711) `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
- `dom_remove_attribute` (line 740) `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
- `index_subtree` (line 750) `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` - *} } return DOM_OK; } dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) { if (!valid(idx, node) || name == NULL) r...*
- `dom_set_inner_html` (line 759) `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
- `ih_append` (line 801) `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
- `dom_get_inner_html` (line 821) `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `DOM_QS_MAX_SELECTORS` (line 379)

**Structs:**
- `sm_entry` (line 62)
- `strmap` (line 71)
- `pm_entry` (line 160)
- `ptrmap` (line 166)
- `dom_index` (line 226)
- `ih_acc` (line 796) - *Accumulator for the serializer callback: a growing buffer hard-capped at * DOM_INNER_HTML_MAX so hostile content cannot force an unbounded allocation.*

#### `dom_debug.c`
**Path:** `src/dom_debug.c`

**Functions:**
- `dd_putc` (line 30) `static void dd_putc(dd_cursor *c, char ch)`
- `dd_emit` (line 35) `static void dd_emit(dd_cursor *c, const char *s, size_t len)`
- `dd_puts` (line 39) `static void dd_puts(dd_cursor *c, const char *s)`
- `dd_printf` (line 48) `static void dd_printf(dd_cursor *c, const char *fmt, ...)` - *Formats short fixed fields (ints, hex colours, fixed tokens) only; the variable hostile fields go through dd_field. Keeps `need` exact even on the ...*
- `dd_w` (line 80) `static int dd_w(int v)` - *A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the value.*
- `dd_color` (line 83) `static void dd_color(dd_cursor *c, int rgb)` - *A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the value. static int dd_w(int v) {...*
- `dd_display_name` (line 87) `static const char *dd_display_name(int d)`
- `dd_justify_name` (line 95) `static const char *dd_justify_name(int j)`
- `dd_align_name` (line 107) `static const char *dd_align_name(int a)`
- `dd_position_name` (line 117) `static const char *dd_position_name(int p)`
- `dd_visibility_name` (line 128) `static const char *dd_visibility_name(int v)`
- `dd_overflow_name` (line 136) `static const char *dd_overflow_name(int o)`
- `dd_cursor_name` (line 145) `static const char *dd_cursor_name(int c)`
- `dd_text_overflow_name` (line 162) `static const char *dd_text_overflow_name(int t)`
- `dd_inset` (line 168) `static int dd_inset(int v)` - *case CSS_CUR_WAIT:        return "wait"; case CSS_CUR_CROSSHAIR:   return "crosshair"; case CSS_CUR_GRAB:        return "grab"; case CSS_CUR_ZOOM_I...*
- `dd_border_style_name` (line 171) `static const char *dd_border_style_name(int s)`
- `dd_box_line` (line 204) `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
- `dd_block_line` (line 236) `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
- `dd_format` (line 293) `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
- `dd_format_css` (line 326) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` - *} dd_puts(&c, "[blocks]\n"); for (size_t i = 0; i < nblocks; ++i) { const rd_block *b = rd_at(doc, i); if (b != NULL) dd_block_line(&c, i, b); } /*...*

**Structs:**
- `dd_cursor` (line 24) - *Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the terminating NUL); `need` counts every byte that WOULD be writ...*

#### `download.c`
**Path:** `src/download.c`

**Functions:**
- `lc` (line 13) `static int lc(int c)` - *download — pure helpers for "save this resource to disk". See include/download.h and spec/download.md.  #include "download.h" #include "pdf_export....*
- `ci_find` (line 19) `static const char *ci_find(const char *hay, const char *needle)` - *#include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer #include <ctype.h> #include <string.h> /* ASCII l...*
- `media_type` (line 33) `static void media_type(const char *content_type, char *buf, size_t bufsz)` - *Writes the lowercased media type of content_type (the part before ';', with * surrounding spaces trimmed) into buf. Empty/NULL -> empty buf.*
- `dl_should_download` (line 46) `int dl_should_download(const char *content_type, const char *content_disposition)`
- `dl_ext_for_type` (line 57) `const char *dl_ext_for_type(const char *content_type)`
- `copy_span` (line 85) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` - *{ "application/xhtml+xml",  ".html" }, { "text/plain",            ".txt"  }, { "image/png",             ".png"  }, { "image/jpeg",            ".jpg...*
- `extract_disposition_name` (line 96) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` - *Extracts a filename candidate from a Content-Disposition value into buf. Handles filename="...", filename=..., and RFC 5987 filename*=charset''valu...*
- `extract_url_name` (line 134) `static int extract_url_name(const char *url, char *buf, size_t bufsz)` - *Extracts the last path segment of url (without ?query or #fragment) into buf. * Returns 1 if a non-empty candidate was written.*
- `has_extension` (line 148) `static int has_extension(const char *name)` - *Does name already carry an extension (a '.' past the first byte with at least * one character after it)?*
- `dl_pick_name` (line 152) `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...`
- `dl_build_path` (line 194) `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`
- `dl_check_size` (line 212) `dl_status dl_check_size(size_t len)`

#### `flex_layout.c`
**Path:** `src/flex_layout.c`

**Functions:**
- `nn` (line 18) `static double nn(double v)` - *No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers bounded by FX_MAX_ITEMS (no VLAs). The flex algorithm follows the ...*
- `fx_flex_line` (line 21) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
- `fx_grid_columns` (line 126) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
- `fx_grid_columns_weighted` (line 131) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
- `fx_grid_place_span` (line 165) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
- `float_pack_impl` (line 190) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` - *Shared packer: wrap == 0 is the single-row v1 contract (overflow clamps in place); wrap != 0 starts a new row (cursors reset) for an item that no l...*
- `fx_float_pack` (line 229) `fx_status fx_float_pack(const double *width, const int *side, size_t n,
                        d...`
- `fx_float_pack_wrap` (line 234) `fx_status fx_float_pack_wrap(const double *width, const int *side, size_t n,
                    ...`
- `fx_grid_cell` (line 240) `void fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col)`
- `fx_justify_name` (line 251) `const char *fx_justify_name(fx_justify j)`

**Macros:**
- `FX_EPS` (line 14)

#### `form.c`
**Path:** `src/form.c`

**Functions:**
- `put_char` (line 17) `static int put_char(char *out, size_t outsz, size_t *pos, char c)` - *No I/O, no global state. The action/names/values are hostile data: encoded (application/x-www-form-urlencoded) and resolved through the canonical u...*
- `enc_component` (line 25) `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` - *Encodes one component per the WHATWG application/x-www-form-urlencoded byte * serialiser. Returns -1 on overflow.*
- `fm_encode` (line 42) `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
- `copy_fit` (line 66) `static int copy_fit(char *dst, size_t dstsz, const char *src)` - *if (fields[i].name == NULL) continue; /* a nameless control is not submitted if (!first && put_char(out, outsz, &pos, '&') != 0) { out[0] = '\0'; r...*
- `clean_action` (line 75) `static int clean_action(const char *action, char *out, size_t outsz)` - *Removes TAB/LF/CR and trims leading/trailing ASCII spaces (WHATWG cleaning of a * URL-bearing attribute). Returns -1 if the cleaned value does not ...*
- `strip_query` (line 93) `static void strip_query(char *url)` - *if (c == '\t' || c == '\n' || c == '\r') continue; if (o + 1 >= outsz) return -1; out[o++] = c; } out[o] = '\0'; size_t s = 0, e = o; while (s < e ...*
- `resolve_target` (line 101) `static fm_block_reason resolve_target(const char *base, const char *act,
                        ...` - *Resolves the cleaned action into a validated absolute https URL R, or returns a * block reason.*
- `fm_build` (line 119) `fm_status fm_build(const char *base, const char *action, fm_method method,
                   con...`

#### `freebug.c`
**Path:** `src/freebug.c`

**Functions:**
- `fb_buffer_init` (line 14) `void fb_buffer_init(fb_buffer *b)` - *include <stdlib.h> include <string.h>*
- `fb_buffer_push` (line 18) `int fb_buffer_push(fb_buffer *b, int level, const char *text, size_t len)`
- `fb_buffer_push_loc` (line 22) `int fb_buffer_push_loc(fb_buffer *b, int level, const char *text, size_t len,
                   ...`
- `fb_buffer_reset` (line 75) `void fb_buffer_reset(fb_buffer *b)`
- `fb_buffer_free` (line 88) `void fb_buffer_free(fb_buffer *b)`
- `fb_buffer_count` (line 98) `size_t fb_buffer_count(const fb_buffer *b)`
- `fb_buffer_at` (line 102) `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
- `fb_level_name` (line 107) `const char *fb_level_name(int level)`

#### `freedom.c`
**Path:** `src/freedom.c`

**Functions:**
- `print_usage` (line 34) `static void print_usage(FILE *fp, const char *prog)` - *define EXIT_OK     0 define EXIT_ERROR  1 define EXIT_USAGE  2*
- `is_https_url` (line 53) `static int is_https_url(const char *s)`
- `is_http_url` (line 57) `static int is_http_url(const char *s)`
- `is_overlay_http` (line 63) `static int is_overlay_http(const char *s)` - *fprintf(fp, "  --dump-dom: headless, print the paint-ready render tree (blocks, boxes, containers) to stdout\n"); fprintf(fp, "  --dump-css: headle...*
- `read_file` (line 122) `static char *read_file(const char *path, size_t *out_len)` - */* HTTP Basic Authentication for headless mode. Set by --user=username:password. static char g_auth_user[256] = ""; static char g_auth_pass[256] = ...*
- `headless_load_hosts` (line 138) `static void headless_load_hosts(void)`
- `is_blank_text` (line 177) `static int is_blank_text(const char *s)` - *impersonate.conf lives in the same search dirs; load it as an allowlist so * hb_is_allowlisted answers the third gate signal (covers subdomains). i...*
- `print_doc` (line 190) `static void print_doc(const rd_doc *doc)` - *Writes the render document as deterministic, flowing plain text for a terminal and for an AI agent (content as data, never instruction). Inline run...*
- `print_console` (line 251) `static void print_console(const fb_buffer *log)` - *Prints the captured Freebug console (the developer-visible JS transcript) to stdout, one entry per line, prefixed with its level and (for located e...*
- `print_dom` (line 268) `static void print_dom(const rd_doc *doc)` - *Prints the paint-ready render tree (dom_debug) to stdout. Two-pass: measure, then allocate exactly and format. The dump is bounded by the document;...*
- `print_dom_css` (line 282) `static void print_dom_css(const rd_doc *doc)` - *Prints the CSS property inspector (dd_format_css) to stdout. Same contract as * print_dom: two-pass measure-then-allocate.*
- `headless_fetch` (line 305) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` - *tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page XHR/fetch and external <script src>. ctx is the page's top URL ...*
- `foldback_cookies` (line 362) `static void foldback_cookies(const char *url, const char *jar)` - *Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network * jar, one pair at a time, so JS-set session cookies reach the next...*
- `render_page` (line 377) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
- `sf_reason` (line 535) `static const char *sf_reason(sf_status ss)`
- `fetch_and_render_one` (line 555) `static int fetch_and_render_one(const char *url, char **out_nav)` - *Fetches one url with secure_fetch and renders the result. The response body is * consumed directly; no extra copy is made. out_nav as in render_page.*
- `elsewhere` (line 613) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
- `run_headless` (line 631) `static int run_headless(const char *target)`
- `main` (line 651) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 8)
- `EXIT_OK` (line 30)
- `EXIT_ERROR` (line 32)
- `EXIT_USAGE` (line 33)
- `HL_JS_NAV_MAX` (line 551)

#### `hostblock.c`
**Path:** `src/hostblock.c`

**Functions:**
- `fnv1a` (line 33) `static uint64_t fnv1a(const char *s, size_t n)`
- `table_probe` (line 45) `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` - *Finds the slot for key (length klen) in t, which must have a free slot. Returns * the index of either the matching entry or the first empty slot fo...*
- `table_grow` (line 56) `static int table_grow(hb_table *t, size_t newcap)` - *Finds the slot for key (length klen) in t, which must have a free slot. Returns * the index of either the matching entry or the first empty slot fo...*
- `table_insert` (line 78) `static int table_insert(hb_table *t, const char *key, size_t klen)` - *Inserts key (length klen) into t, deduping. Returns 0 (inserted or already * present), -1 on OOM.*
- `table_contains` (line 97) `static int table_contains(const hb_table *t, const char *key)`
- `table_free` (line 103) `static void table_free(hb_table *t)`
- `lower` (line 112) `static char lower(char c)` - *static int table_contains(const hb_table *t, const char *key) { if (t->cap == 0) return 0; size_t i = table_probe(t, key, strlen(key)); return t->s...*
- `is_ip_token` (line 119) `static int is_ip_token(const char *s, size_t n)` - *A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain. An empty token never reaches here.*
- `is_domain_char` (line 128) `static int is_domain_char(char c)` - *A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain. An empty token never reaches here. static int is_ip_token(con...*
- `hb_new` (line 149) `hb_set *hb_new(void)` - *token is not a domain we accept (caller skips it). static size_t normalise_domain(const char *tok, size_t n, char *out, size_t out_size) { if (n ==...*
- `hb_free` (line 154) `void hb_free(hb_set *s)`
- `hb_load` (line 161) `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
- `hb_check` (line 198) `hb_decision hb_check(const hb_set *s, const char *host)`
- `hb_is_allowlisted` (line 223) `int hb_is_allowlisted(const hb_set *s, const char *host)`
- `hb_count` (line 243) `size_t hb_count(const hb_set *s, hb_list list)`

**Macros:**
- `HB_MAX_HOST` (line 17)
- `HB_INIT_CAP` (line 19)

**Structs:**
- `hb_table` (line 23)
- `hb_set` (line 29)

#### `hostedit.c`
**Path:** `src/hostedit.c`

**Functions:**
- `he_lower` (line 11) `static char he_lower(char c)` - *include <string.h>*
- `is_label_char` (line 15) `static int is_label_char(char c)`
- `valid_host` (line 22) `static int valid_host(const char *host, size_t n)` - *#include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c; } static int is...*
- `he_make_line` (line 40) `he_status he_make_line(const char *host, char *out, size_t cap)`
- `is_ip_token` (line 67) `static int is_ip_token(const char *ts, const char *te)` - *True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostblock's is_ip_token spirit: such a leading token is...*
- `he_scan` (line 80) `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` - *Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(ts, tl, ctx). If fn returns nonzero, iteration ...*
- `has_host_cb` (line 104) `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
- `he_text_has_host` (line 108) `int he_text_has_host(const char *text, const char *host)`
- `contains_ci` (line 115) `static int contains_ci(const char *hs, size_t hl, const char *needle)` - *} return 0; } static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts, ts + tl, (const char *)ctx); } int he_text_ha...*
- `starts_with_ci` (line 127) `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
- `suggest_cb` (line 143) `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
- `he_suggest` (line 163) `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`

**Structs:**
- `suggest_ctx` (line 136)

#### `html_parse.c`
**Path:** `src/html_parse.c`

**Functions:**
- `dup_bytes` (line 25) `static char *dup_bytes(const lxb_char_t *src, size_t len)` - *#include "html_parse.h" #include <stdlib.h> #include <string.h> #include <lexbor/html/html.h> #include <lexbor/dom/dom.h> #include <lexbor/tag/cons...*
- `node_next` (line 35) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` - *lxb_html_document_t *doc; }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { char *out = (char *)malloc(len + 1); if...*
- `attr_is_event_handler` (line 44) `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
- `node_is_script` (line 51) `static int node_is_script(const lxb_dom_node_t *node)`
- `strip_scripts` (line 57) `static void strip_scripts(lxb_html_document_t *document)`
- `mem_contains_ci` (line 84) `static int mem_contains_ci(const lxb_char_t *hay, size_t hlen, const char *needle)` - *Case-insensitive (ASCII) substring test over a length-delimited attribute value. * needle must be lowercase letters.*
- `script_classify` (line 108) `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...` - *Classifies a <script>: a classic program runs only when its type is absent/empty or a JavaScript MIME type (contains "javascript"/"ecmascript"). Ev...*
- `hp_extract_script_list` (line 137) `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` - *Collects each executable <script> as its own entry, in document order: inline source for classic inline scripts, the raw src attribute for external...*
- `hp_free_scripts` (line 181) `void hp_free_scripts(hp_script *scripts, size_t count)`
- `attr_has_token_ci` (line 194) `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` - *Whitespace-separated token test over a length-delimited attribute value, ASCII case-insensitive: rel="preload stylesheet" has the token "stylesheet...*
- `link_is_active_stylesheet` (line 215) `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` - *An applicable stylesheet <link>: rel token "stylesheet" and not "alternate"; a non-empty href; media absent/empty or mentioning screen/all (fail cl...*
- `hp_extract_stylesheet_hrefs` (line 236) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
- `hp_free_stylesheet_hrefs` (line 270) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
- `strip_event_handlers` (line 276) `static void strip_event_handlers(lxb_html_document_t *document)`
- `hp_config_default` (line 299) `hp_config hp_config_default(void)` - *for (lxb_dom_attr_t *attr = lxb_dom_element_first_attribute(el); attr != NULL; attr = lxb_dom_element_next_attribute(attr)) { if (attr_is_event_han...*
- `hp_validate_input` (line 307) `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
- `hp_parse` (line 317) `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)` - *c.strip_scripts = 1; c.strip_event_handlers = 1; return c; } hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg) { if (...*
- `hp_element_count` (line 351) `size_t hp_element_count(const hp_document *doc)` - *if (local.strip_scripts) strip_scripts(document); if (local.strip_event_handlers) strip_event_handlers(document); hp_document *wrap = (hp_document ...*
- `hp_script_count` (line 361) `size_t hp_script_count(const hp_document *doc)`
- `hp_event_handler_count` (line 371) `size_t hp_event_handler_count(const hp_document *doc)`
- `hp_extract_text` (line 387) `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
- `hp_get_title` (line 406) `char *hp_get_title(const hp_document *doc, size_t *out_len)`
- `hp_free` (line 421) `void hp_free(char *buf)` - *char *hp_get_title(const hp_document *doc, size_t *out_len) { if (out_len != NULL) *out_len = 0; if (doc == NULL || doc->doc == NULL) return NULL; ...*
- `hp_document_free` (line 425) `void hp_document_free(hp_document *doc)`
- `hp_document_root` (line 431) `const void *hp_document_root(const hp_document *doc)`

**Macros:**
- `_POSIX_C_SOURCE` (line 8)

**Structs:**
- `hp_document` (line 20)

#### `image_decode.c`
**Path:** `src/image_decode.c`

**Functions:**
- `read_be32` (line 51) `static uint32_t read_be32(const uint8_t *p)`
- `img_png_dimensions` (line 56) `img_status img_png_dimensions(const uint8_t *bytes, size_t len,
                              uin...`
- `img_dimensions_ok` (line 67) `int img_dimensions_ok(uint32_t w, uint32_t h)`
- `img_fit` (line 75) `void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h,
             double *out_w, do...`
- `premultiply` (line 90) `static void premultiply(uint8_t *data, size_t pixels)` - *void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { if (out_w == NULL || out_h == NULL) return; out_...*
- `img_decode_png` (line 101) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
- `jpeg_error_longjmp` (line 157) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
- `jpeg_silence` (line 164) `static void jpeg_silence(j_common_ptr cinfo)` - *libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE) without tearing the worker down. s...*
- `img_decode_jpeg` (line 165) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
- `gr_u8` (line 259) `static int gr_u8(gif_reader *r, uint8_t *out)`
- `gr_u16le` (line 265) `static int gr_u16le(gif_reader *r, uint16_t *out)`
- `gr_skip` (line 272) `static int gr_skip(gif_reader *r, size_t n)`
- `gr_skip_subblocks` (line 280) `static int gr_skip_subblocks(gif_reader *r)` - *static int gr_u16le(gif_reader *r, uint16_t *out) { if (r->pos + 2u > r->len) return 0; out = (uint16_t)(r->p[r->pos] | ((uint16_t)r->p[r->pos + 1]...*
- `gb_next_code` (line 297) `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
- `gif_deinterlace_row` (line 319) `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` - *} uint8_t byte; if (!gr_u8(b->r, &byte)) return 0; b->block_left--; b->acc |= (uint32_t)byte << b->nbits; b->nbits += 8u; } out = b->acc & ((1u << ...*
- `gif_put_pixel` (line 334) `static void gif_put_pixel(uint32_t *canvas, uint32_t cw, uint32_t ch,
                          u...` - *Writes one palette pixel into the canvas at frame-relative index i (clipped to * the canvas; transparent index -> 0x00000000, already premultiplied).*
- `img_decode_gif` (line 353) `img_status img_decode_gif(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode_webp` (line 519) `img_status img_decode_webp(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_decode` (line 552) `img_status img_decode(const uint8_t *bytes, size_t len, img_pixels *out)`
- `img_pixels_free` (line 565) `void img_pixels_free(img_pixels *p)`
- `img_format_name` (line 574) `const char *img_format_name(img_format f)`

**Macros:**
- `PNG_IHDR_MIN` (line 34)
- `GIF_LZW_MAX_CODES` (line 252)

**Structs:**
- `jpeg_err_ctx` (line 153) - *libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE) without tearing the worker down.*
- `gif_reader` (line 255)
- `gif_bits` (line 290) - *return 1; } /* Skips a chain of data sub-blocks up to and including the 0 terminator. static int gr_skip_subblocks(gif_reader *r) { uint8_t n; for ...*

#### `js_dom.c`
**Path:** `src/js_dom.c`

**Functions:**
- `jd_opaque_get` (line 23) `static jd_opaque *jd_opaque_get(JSContext *ctx)` - *include "quickjs.h"*
- `jd_idx` (line 27) `static dom_index *jd_idx(JSContext *ctx)`
- `jd_handle` (line 37) `static int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` - *Coerces a JS argument to a node handle. Returns -1 with a pending exception if coercion threw; otherwise stores the handle (out-of-range values sta...*
- `jd_handle_or_null` (line 43) `static JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
- `m_node_count` (line 49) `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...` - *if coercion threw; otherwise stores the handle (out-of-range values stay * out of range and are rejected later by the dom validators). static int j...*
- `m_get_element_by_id` (line 55) `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
- `jd_query_list` (line 67) `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` - *return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx))); } static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val, int argc...*
- `m_get_by_tag` (line 96) `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
- `m_get_by_class` (line 102) `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_tag_name` (line 108) `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_attribute` (line 118) `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_parent` (line 131) `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
- `m_first_child` (line 139) `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_next_sibling` (line 147) `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_precedes` (line 155) `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_text_content` (line 166) `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...` - *if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return jd_handle_or_null(ctx, dom_next_sibling(jd_idx(ctx), h)); } static JSValue m_prece...*
- `m_set_text` (line 176) `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_title` (line 190) `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_set_title` (line 198) `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_create_element` (line 211) `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...` - *} static JSValue m_set_title(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; size_t len = 0; con...*
- `m_append_child` (line 223) `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_remove_child` (line 232) `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_set_attribute` (line 241) `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_remove_attribute` (line 257) `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
- `m_set_inner_html` (line 269) `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_get_inner_html` (line 286) `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` - *innerHTML getter (2026-07-11): serializes the node's children (bounded in dom.c; * over-cap or invalid handle yields "" -- a getter never throws pa...*
- `m_register_click` (line 307) `static JSValue m_register_click(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_query_selector` (line 333) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...` - *JS_FreeValue(ctx, reg); reg = JS_NewObject(ctx); if (JS_IsException(reg)) { JS_FreeValue(ctx, global); return JS_EXCEPTION; } JS_SetPropertyStr(ctx...*
- `m_query_selector_all` (line 346) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...` - */* dom.querySelector(root, sel): root is a handle or -1 for document scope. static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val, ...*
- `m_matches` (line 374) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_closest` (line 386) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_attr_names` (line 398) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
- `attrNames` (line 472) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
- `js_env` (line 804) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
- `jd_lp_set` (line 1047) `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...` - *Defines a string property on the __locParts data object from a (ptr,len) span. * The span is copied into an engine string; a NULL span becomes "".*
- `jd_install` (line 1088) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
- `fails` (line 1149) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
- `jd_install_console` (line 1206) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
- `jd_set_location` (line 1242) `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
- `jd_set_cookies` (line 1276) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
- `jd_get_cookies` (line 1296) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
- `jd_take_nav_request` (line 1318) `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
- `jd_pack_ptr` (line 1361) `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` - *Carry the host fetch fn + its ctx as a function's closure data, each split into 32-bit halves (no assumption about JS number width). The data lives...*
- `jd_unpack_ptr` (line 1366) `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
- `m_host_fetch` (line 1379) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...` - *__hostFetch(method, url, body) -> { status, body, contentType }. The ONLY network primitive exposed to script; it does NOT touch a socket -- it cal...*
- `jd_install_xhr` (line 1458) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
- `jd_click_state_new` (line 1488) `jd_click_state *jd_click_state_new(void)`
- `jd_click_state_free` (line 1493) `void jd_click_state_free(jd_click_state *s)`
- `jd_install_events` (line 1497) `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
- `jd_fire_click` (line 1508) `int jd_fire_click(js_context *ctx, dom_node_id node_id)`

**Macros:**
- `_POSIX_C_SOURCE` (line 9)

**Structs:**
- `jd_method` (line 302)
- `jd_click_state` (line 1485)

#### `js_env.c`
**Path:** `src/js_env.c`

**Functions:**
- `wall_clock_ms` (line 34) `static uint64_t wall_clock_ms(void)` - *#include "anti_fp.h" #include "js_sandbox.h" #include <stdint.h> #include <stdio.h> #include <stdlib.h> #include <string.h> #include <sys/random.h>...*
- `monotonic_ms` (line 40) `static double monotonic_ms(void)`
- `m_date_now` (line 48) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` - *static uint64_t wall_clock_ms(void) { struct timespec ts; if (clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0; return (uint64_t)ts.tv_sec * 1000u...*
- `m_perf_now` (line 57) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` - *performance.now: coarsened elapsed since the origin bound at install time, so * it never leaks the host uptime.*
- `m_empty_array` (line 76) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_get_random_values` (line 84) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...` - *timing (Zero Knowledge) while keeping analytics scripts from throwing. static JSValue m_noop(JSContext *ctx, JSValueConst this_val, int argc, JSVal...*
- `m_random_uuid` (line 124) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_subtle_null` (line 140) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
- `def_val` (line 152) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` - *Always takes ownership of v: JS_DefinePropertyValueStr consumes it (freeing it even when the define fails). An exception value is an immediate with...*
- `def_str` (line 157) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
- `def_int` (line 161) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
- `def_fn` (line 165) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
- `build_languages` (line 173) `static JSValue build_languages(JSContext *ctx)` - *navigator.languages: a sealed array built by splitting fp_accept_language() * (e.g. "en-US,en") on commas. Returns an exception value on OOM.*
- `build_navigator` (line 196) `static int build_navigator(JSContext *ctx, JSValueConst global)`
- `build_screen` (line 293) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
- `build_crypto` (line 337) `static int build_crypto(JSContext *ctx, JSValueConst global)` - *define PERF_ORIGIN_EPOCH 1700000000000.0*
- `build_perf_timing` (line 365) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
- `build_perf_navigation` (line 379) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
- `build_performance` (line 391) `static int build_performance(JSContext *ctx, JSValueConst global)`
- `override_date_now` (line 424) `static int override_date_now(JSContext *ctx, JSValueConst global)` - *Replaces the built-in Date.now with the coarsened version, non-writable and * non-configurable so a script cannot restore a high-resolution clock.*
- `make_readback` (line 467) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
- `build_readback_obj` (line 475) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
- `je_install` (line 488) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
- `je_install_canvas` (line 507) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`

**Macros:**
- `_POSIX_C_SOURCE` (line 16)
- `FP_MIME_COUNT` (line 252)
- `PERF_ORIGIN_EPOCH` (line 336)

#### `js_policy.c`
**Path:** `src/js_policy.c`

**Functions:**
- `eq_ci` (line 12) `static int eq_ci(const char *a, const char *b)` - *js_policy — implementation: pure per-host JavaScript policy decision.  No I/O, no global state. Fail-closed: an unknown mode never enables JS.  #in...*
- `jsp_enabled` (line 21) `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
- `jsp_trusted` (line 30) `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
- `jsp_present_trusted` (line 34) `bool jsp_present_trusted(int host_allowlisted)`
- `jsp_mode_from_str` (line 38) `jsp_mode jsp_mode_from_str(const char *s)`
- `jsp_mode_str` (line 50) `const char *jsp_mode_str(jsp_mode mode)`

#### `js_sandbox.c`
**Path:** `src/js_sandbox.c`

**Functions:**
- `jm_malloc` (line 44) `static void *jm_malloc(void *opaque, size_t size)` - *int    hit; /* sticky within one eval: an allocation was denied by the cap } js_mem_state; struct js_context { JSRuntime      *rt; JSContext      *...*
- `jm_calloc` (line 52) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
- `jm_free` (line 62) `static void jm_free(void *opaque, void *ptr)`
- `jm_realloc` (line 68) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
- `jm_usable_size` (line 78) `static size_t jm_usable_size(const void *ptr)`
- `host_dup` (line 88) `static char *host_dup(const char *src, size_t len)` - *if (p == NULL && size != 0) return NULL; /* original ptr left untouched m->used = m->used - old + ((p != NULL) ? malloc_usable_size(p) : 0); return...*
- `timespec_reached` (line 96) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
- `js_interrupt_cb` (line 103) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` - *static char *host_dup(const char *src, size_t len) { char *out = (char *)malloc(len + 1); if (out == NULL) return NULL; if (len != 0 && src != NULL...*
- `is_ascii_digit` (line 115) `static int is_ascii_digit(char c)`
- `js_loc_from_stack` (line 117) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
- `js_limits_default` (line 235) `js_limits js_limits_default(void)` - *if (out_col  != NULL) *out_col  = cl; } JS_FreeCString(ctx, ss); } else { JS_FreeValue(ctx, JS_GetException(ctx)); /* ToCString may have thrown } }...*
- `limits_resolve` (line 244) `static js_limits limits_resolve(const js_limits *lim)`
- `js_validate_source` (line 253) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
- `js_context_new` (line 264) `js_status js_context_new(const js_limits *lim, js_context **out)` - *if (l.time_budget_ms == 0)     l.time_budget_ms     = JS_DEFAULT_TIME_BUDGET; return l; } js_status js_validate_source(const char *src, size_t len,...*
- `js_context_free` (line 303) `void js_context_free(js_context *ctx)`
- `arm_deadline` (line 312) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` - *c->has_deadline = 0; c->interrupted = 0; out = c; return JS_OK; } void js_context_free(js_context *ctx) { if (ctx == NULL) return; if (ctx->ctx != ...*
- `js_set_time_budget` (line 327) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
- `js_eval` (line 332) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
- `js_eval_named` (line 336) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
- `js_pump_jobs` (line 419) `int js_pump_jobs(js_context *ctx, int max_jobs)`
- `js_eval_once` (line 437) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
- `js_result_free` (line 450) `void js_result_free(js_result *res)`
- `js_context_raw` (line 463) `void *js_context_raw(js_context *ctx)`

**Macros:**
- `_POSIX_C_SOURCE` (line 11)

**Structs:**
- `js_mem_state` (line 27) - *We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs *inside* QuickJS before our allocator and is therefore unobservable)...*
- `js_context` (line 33)

#### `link_nav.c`
**Path:** `src/link_nav.c`

**Functions:**
- `clean_href` (line 19) `static int clean_href(const char *href, char *out, size_t outsz)` - *Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out. Returns 0, or -1 if the href does not fit in out.*
- `ci_prefix` (line 38) `static int ci_prefix(const char *s, const char *prefix)` - *if (o + 1 >= outsz) return -1; out[o++] = (char)c; } out[o] = '\0'; size_t start = 0; while (out[start] == ' ') ++start; if (start > 0) memmove(out...*
- `classify_block` (line 62) `static ln_block_reason classify_block(const char *ref)` - *Splits the fragment (everything after the first '#') out of ref: copies the fragment id (without '#') into frag, then truncates ref at the '#'. A f...*
- `file_dir_len` (line 69) `static size_t file_dir_len(const char *base)` - *const char *f = hash + 1; size_t fl = strlen(f); if (fl + 1 <= fragsz) memcpy(frag, f, fl + 1); hash = '\0'; } /* Classifies why a fragment-less re...*
- `last_seg_is_dotdot` (line 79) `static int last_seg_is_dotdot(const char *body, size_t blen)` - *return LN_BLOCK_UNSUPPORTED; } /* Length of base up to and including the last '/'; 0 when base has no '/'. static size_t file_dir_len(const char *b...*
- `append_seg` (line 86) `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...` - *for (size_t i = 0; base[i] != '\0'; ++i) { if (base[i] == '/') { last = i; found = 1; } } return found ? last + 1 : 0; } /* Nonzero iff the last se...*
- `pop_seg` (line 98) `static void pop_seg(char *body, size_t *blen)` - */* Appends seg to body (with a '/' separator when non-empty). 0, or -1 on overflow. static int append_seg(char *body, size_t bodysz, size_t *blen, ...*
- `resolve_file` (line 149) `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` - *Resolves a local file reference (relative or absolute path) against base into * out. The fragment (#...) is dropped. Returns 0, or -1 on overflow/e...*
- `ln_resolve` (line 171) `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
- `ln_block_reason_text` (line 240) `const char *ln_block_reason_text(ln_block_reason reason)`

#### `local_store.c`
**Path:** `src/local_store.c`
**File Doc:** *include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM_ARGON2_LANES "lanes" endif ifndef OSSL_KDF_PARAM_ARGON2_MEMCOST de...*

**Functions:**
- `cipher_for` (line 100) `static const EVP_CIPHER *cipher_for(ls_aead aead)` - *#define LS_ARGON2_M_KIB  19456u  /* memory cost in KiB (19 MiB) #define LS_ARGON2_P      1u      /* lanes / parallelism /* Container field offsets....*
- `argon2id_derive` (line 110) `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...` - *static const uint8_t LS_MAGIC[4] = { 'F', 'R', 'Z', 'S' }; /* --- AEAD selection --- static const EVP_CIPHER *cipher_for(ls_aead aead) { switch (ae...*
- `ls_derive_key` (line 139) `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
- `aead_encrypt` (line 148) `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...` - *int rc = EVP_KDF_derive(kctx, out, out_len, params); EVP_KDF_CTX_free(kctx); return (rc == 1) ? LS_OK : LS_ERR_KDF; } ls_status ls_derive_key(const...*
- `aead_decrypt` (line 174) `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
- `seal_core` (line 202) `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...` - *if (aad_len > 0 && EVP_DecryptUpdate(ctx, NULL, &len, aad, (int)aad_len) != 1) goto done; if (ct_len > 0) { if (EVP_DecryptUpdate(ctx, pt, &len, ct...*
- `decrypt_blob` (line 239) `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
- `ls_seal` (line 270) `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...` - *if (pt == NULL) return LS_ERR_OOM; ls_status st = aead_decrypt(cipher, key, nonce, blob, LS_HEADER_LEN, ct, ct_len, tag, pt); if (st != LS_OK) { OP...*
- `ls_open` (line 283) `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
- `ls_seal_passphrase` (line 294) `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...` - *memset(salt, 0, sizeof salt); /* unused under kdf_id = none return seal_core(key, aead, LS_KDF_NONE, salt, plaintext, pt_len, out, out_len); } ls_s...*
- `ls_open_passphrase` (line 315) `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
- `ls_free` (line 335) `void ls_free(uint8_t *buf, size_t len)`

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
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 71)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 74)
- `OSSL_KDF_PARAM_THREADS` (line 77)
- `LS_VERSION` (line 79)
- `LS_KDF_NONE` (line 81)
- `LS_KDF_ARGON2ID` (line 82)
- `LS_ARGON2_T` (line 85)
- `LS_ARGON2_M_KIB` (line 86)
- `LS_ARGON2_P` (line 87)
- `OFF_MAGIC` (line 90)
- `OFF_VERSION` (line 91)
- `OFF_AEAD` (line 92)
- `OFF_KDF` (line 93)
- `OFF_SALT` (line 94)
- `OFF_NONCE` (line 95)

#### `net_realm.c`
**Path:** `src/net_realm.c`

**Functions:**
- `lower` (line 16) `static char lower(char c)` - *define NR_MAX_HOST 253u*
- `ends_with_realm` (line 23) `static int ends_with_realm(const char *host, size_t n, const char *suffix)` - *True if the lowercased host (length n) ends with ".suffix" AND has at least one * non-empty label before the dot. suffix is given without its leadi...*
- `nr_classify_host` (line 33) `nr_realm nr_classify_host(const char *host)`
- `host_of` (line 52) `static int host_of(const char *url, char *out, size_t out_size)` - *Extracts the host of scheme://host[:port][/...] into out (lowercased not required * here; nr_classify_host lowercases). Returns 0 on success, -1 if...*
- `nr_classify_url` (line 67) `nr_realm nr_classify_url(const char *url)`
- `nr_route_for` (line 73) `nr_route nr_route_for(const char *url, nr_config cfg)`
- `nr_realm_allows_http` (line 87) `int nr_realm_allows_http(nr_realm r)`
- `nr_realm_name` (line 93) `const char *nr_realm_name(nr_realm r)`
- `nr_route_name` (line 102) `const char *nr_route_name(nr_route r)`

**Macros:**
- `NR_MAX_HOST` (line 14)

#### `os_sandbox.c`
**Path:** `src/os_sandbox.c`

**Functions:**
- `os_policy_allows` (line 51) `int os_policy_allows(long syscall_nr)` - *define OS_ALLOWED_N (sizeof os_allowed / sizeof os_allowed[0])*
- `os_policy_size` (line 58) `size_t os_policy_size(void)`
- `os_prot_allowed` (line 65) `int os_prot_allowed(long syscall_nr, unsigned long prot)` - *W^X mirror: mmap/mprotect keep their membership but lose any request that asks * for executable memory. The single source of truth the BPF prot-che...*
- `os_no_dump` (line 75) `os_status os_no_dump(void)` - *Anti-dump defense in depth: undumpable + no core file, so neither a crash nor a foreign ptrace can exfiltrate worker secrets. Best-effort; call bef...*
- `excluded` (line 89) `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...`
- `os_isolate_namespaces` (line 93) `os_status os_isolate_namespaces(void)`
- `os_policy_allows` (line 105) `int os_policy_allows(long syscall_nr)` - *Unprivileged user namespaces disabled (EPERM) or unsupported kernel * (EINVAL/ENOSYS): not fatal -- seccomp remains the mandatory boundary. return ...*
- `os_policy_size` (line 107) `size_t os_policy_size(void)`
- `os_prot_allowed` (line 108) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
- `os_no_dump` (line 111) `os_status os_no_dump(void)`
- `os_harden` (line 112) `os_status os_harden(os_violation action)`
- `os_namespace_flags` (line 114) `int os_namespace_flags(void)`
- `os_isolate_namespaces` (line 116) `os_status os_isolate_namespaces(void)`
- `os_harden` (line 144) `os_status os_harden(os_violation action)` - *The native ABI token the BPF arch guard pins to (rejects x32/i386 on x86_64 and * AArch32 on aarch64 -- syscall-ABI-confusion defence). if defined(...*
- `ll_create_ruleset` (line 238) `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...` - *include <errno.h> include <fcntl.h> include <stddef.h> include <stdint.h> include <string.h> include <unistd.h> include <linux/landlock.h> include ...*
- `ll_add_rule` (line 243) `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...`
- `ll_restrict_self` (line 248) `static long ll_restrict_self(int fd, uint32_t flags)`
- `ll_handled` (line 265) `static uint64_t ll_handled(int abi)` - *The set of FS rights the ruleset handles, masked to what this ABI supports so * landlock_create_ruleset does not fail with EINVAL on older kernels.*
- `ll_read_access` (line 278) `static uint64_t ll_read_access(uint64_t handled)`
- `os_landlock_abi` (line 284) `int os_landlock_abi(void)`
- `os_landlock_restrict` (line 290) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
- `os_landlock_abi` (line 330) `int os_landlock_abi(void)` - *pb.parent_fd = pfd; long rc = ll_add_rule(rfd, LANDLOCK_RULE_PATH_BENEATH, &pb, 0); close(pfd); if (rc != 0) { close(rfd); return OS_ERR_LANDLOCK; ...*
- `os_landlock_restrict` (line 332) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`

**Macros:**
- `_GNU_SOURCE` (line 12)
- `OS_ALLOWED_N` (line 49)
- `OS_SECCOMP_ARCH` (line 140)
- `OS_SECCOMP_ARCH` (line 142)
- `LL_FS_BASE` (line 254)

#### `page_view.c`
**Path:** `src/page_view.c`

**Functions:**
- `input` (line 44) `* Output may be longer than the input (a single byte >=0x80 -> up to 3 UTF-8
 * bytes), so the ca...`
- `cp1252_to_ucs` (line 59) `static unsigned int cp1252_to_ucs(unsigned char c)` - *Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0.. 0xFF map identically to Latin-1 (code point == byte). 0x80..0x9F car...*
- `utf8_encode` (line 73) `static size_t utf8_encode(unsigned int cp, char *out)` - *Encodes a BMP scalar (<= 0xFFFF, which covers all Windows-1252 targets) as * UTF-8 into out (up to 3 bytes); returns the byte count written.*
- `utf8_sanitized_dup` (line 85) `static char *utf8_sanitized_dup(const char *s)`
- `dup_n` (line 117) `static char *dup_n(const char *s, size_t n)`
- `run_init_common` (line 131) `static void run_init_common(pv_run *r)` - *Common field initialization shared by all append helpers. Keeps the three constructors DRY and guarantees every run starts from the same sentinel s...*
- `pv_node_map_init` (line 220) `static int pv_node_map_init(pv_node_map *m)`
- `pv_node_map_free` (line 228) `static void pv_node_map_free(pv_node_map *m)`
- `pv_node_map_build` (line 265) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` - *Builds a document-order map of all element nodes under root. Returns 0, or -1 on * allocation failure.*
- `pv_new` (line 273) `pv_view *pv_new(void)`
- `pv_append` (line 277) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
- `pv_append_image` (line 310) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
- `pv_append_input` (line 339) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
- `pv_set_emphasis` (line 379) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
- `pv_set_indent` (line 386) `void pv_set_indent(pv_view *v, int indent)`
- `pv_set_color` (line 391) `void pv_set_color(pv_view *v, int fg_rgb)`
- `pv_set_bgcolor` (line 396) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
- `pv_set_text_style` (line 401) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int line_scale,
              ...`
- `pv_set_text_ext` (line 411) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
- `pv_set_container` (line 440) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
- `pv_set_grid` (line 455) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
- `pv_set_flex` (line 465) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
- `pv_set_cont_item` (line 477) `void pv_set_cont_item(pv_view *v, int cont_item)`
- `pv_set_float` (line 482) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear)`
- `pv_set_box` (line 490) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
- `pv_set_box_pct` (line 502) `void pv_set_box_pct(pv_view *v, int box_w_pct)`
- `pv_set_node_id` (line 507) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
- `pv_set_block_id` (line 512) `void pv_set_block_id(pv_view *v, int block_id)`
- `pv_set_input_checked` (line 517) `void pv_set_input_checked(pv_view *v, int checked)`
- `pv_set_input_select_opts` (line 522) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
- `pv_add_box_def` (line 530) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
- `pv_free` (line 543) `void pv_free(pv_view *v)`
- `pv_count` (line 558) `size_t pv_count(const pv_view *v)`
- `pv_at` (line 562) `const pv_run *pv_at(const pv_view *v, size_t i)`
- `pv_box_count` (line 567) `size_t pv_box_count(const pv_view *v)`
- `pv_box_at` (line 571) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
- `node_next` (line 580) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` - *} size_t pv_box_count(const pv_view *v) { return (v != NULL) ? v->nbox : 0; } const pv_box_def *pv_box_at(const pv_view *v, size_t i) { if (v == NU...*
- `is_block_tag` (line 589) `static int is_block_tag(lxb_tag_id_t t)`
- `is_block_like` (line 614) `static int is_block_like(lxb_tag_id_t t, css_display display)` - *An element should be treated as block-like (eligible for box registration, hbox, float) when its CSS display property indicates a block-level box, ...*
- `causes_block_break` (line 624) `static int causes_block_break(lxb_tag_id_t t, css_display display)` - *Returns 1 when the element should cause a block break (start a new line). display:inline-block and display:inline do NOT cause a break; they flow *...*
- `heading_level` (line 629) `static int heading_level(lxb_tag_id_t t)`
- `is_skipped_tag` (line 641) `static int is_skipped_tag(lxb_tag_id_t t)`
- `node_tag` (line 651) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
- `in_skipped_subtree` (line 660) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...` - *Nonzero if any ancestor up to base is a non-rendered container. When js_enabled, a <noscript> ancestor also suppresses content (the script would ru...*
- `font_color_attr` (line 693) `static int font_color_attr(lxb_dom_element_t *el)`
- `bgcolor_attr` (line 700) `static int bgcolor_attr(lxb_dom_element_t *el)` - *Legacy bgcolor attribute (body/table/tr/td), the background twin of <font * color>: pre-CSS sites (Hacker News' orange bar and beige page) still us...*
- `item_ordinal` (line 752) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` - *Ordinal for a run of container `cid` whose direct-child item is `item` (NULL = * anonymous: every such run is its own item). -1 when the run has no...*
- `pv_text_ext_reset` (line 774) `void pv_text_ext_reset(pv_text_ext *e)` - *The author text-presentation extensions struct (pv_text_ext) is public now (include/page_view.h): each field resolves from the nearest ancestor tha...*
- `pv_text_ext_merge` (line 793) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` - *Merges one ancestor's resolved css_style into ext, nearest ancestor first (a field * already set is not overwritten — keeps the nearest, matching i...*
- `css_has_hbox` (line 831) `static int css_has_hbox(const css_style *cs)` - *caret-color: an explicit `auto` (CSS_LEN_AUTO) on a nearer ancestor is a * resolved value -- it stops the walk, and pv_set_text_ext maps it to -1. ...*
- `css_hbox_resolve` (line 842) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` - *Pre-resolves the horizontal box (px) into a run's wire fields: l/r insets = padding + non-auto margin of each side (clamped >= 0); w = the tightest...*
- `css_has_position` (line 870) `static int css_has_position(const css_style *cs)` - *A real (non-static) position makes a block box-carrying too, so its position/insets/ * z-index ride the box-def tree (painted for relative; carried...*
- `css_has_boxdeco` (line 874) `static int css_has_boxdeco(const css_style *cs)`
- `container_id` (line 908) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` - *Document-order registry of flex/grid container nodes, so the runs of one * container share a stable id. typedef struct pv_container_reg { const lxb...*
- `boxdef_from_style` (line 928) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` - *Fills *d (decoration + hbox + bg; parent_id defaults to -1) from a resolved style. Padding unset -> 0 (geometry default); the rest keep the css mod...*
- `box_reg_id` (line 983) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs)` - *Id of node in the box registry, recording its decoration on first sight. -1 when * full. The parent link is stamped separately as the ancestor walk...*
- `pv_style_cache_init` (line 1009) `static int pv_style_cache_init(pv_style_cache *c)`
- `pv_style_cache_free` (line 1022) `static void pv_style_cache_free(pv_style_cache *c)`
- `cached_element_style` (line 1031) `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
            ...` - *cch_element_style(el, sheet), memoized in *cache. A NULL cache (OOM at init, or a caller that opts out) simply calls through uncached -- never a ha...*
- `css_to_fx_justify` (line 1060) `static int css_to_fx_justify(css_justify j)` - *Maps a css_justify (resolved by the css cascade) to a flex_layout fx_justify. * Unset / start / unknown all fall to FX_JUSTIFY_START (the default).*
- `is_bold_tag` (line 1075) `static int is_bold_tag(lxb_tag_id_t t)` - *Inline emphasis carried by a tag: bold from <b>/<strong>/<th>, italic from * <i>/<em>. <th> is a header cell, conventionally bold.*
- `is_italic_tag` (line 1078) `static int is_italic_tag(lxb_tag_id_t t)`
- `resolve_context` (line 1097) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...` - *level, nearest block-level ancestor (defaults to base), the inherited author color (nearest ancestor that sets one, packed 0xRRGGBB, or -1), the au...*
- `collapse_ws` (line 1293) `static char *collapse_ws(const char *s, size_t n)` - *prev_basis = cs.flex_basis; prev_order = cs.order; prev_align_self = cs.align_self; prev_col_span = (cs.grid_col_span > 0) ? cs.grid_col_span : 0; ...*
- `parse_dim` (line 1316) `static int parse_dim(const lxb_char_t *s, size_t len)` - *Parses the leading non-negative integer of an HTML length attribute value (e.g. "640", "640px", "50%"). Returns the value clamped to a sane bound, ...*
- `find_body` (line 1328) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
- `forms_free` (line 1351) `static void forms_free(form_table *ft)`
- `ascii_ieq` (line 1359) `static int ascii_ieq(const char *s, const char *lit)` - *} form_rec; typedef struct form_table { form_rec *recs; size_t    count, cap; } form_table; static void forms_free(form_table *ft) { for (size_t i ...*
- `attr_dup` (line 1371) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` - *Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent. A present-but-empty attribute yields a "" string (distingu...*
- `forms_add` (line 1380) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` - *Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent. A present-but-empty attribute yields a "" string (distingu...*
- `form_for` (line 1400) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...` - *} lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node); char *method = attr_dup(el, "method", 6); int m = ascii_ieq(method, "p...*
- `under_unrendered` (line 1416) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` - *Nonzero if a descendant text node sits under a non-rendered element (a <style> or <script> nested in the collected subtree -- with run_js the parse...*
- `collect_text` (line 1429) `static char *collect_text(const lxb_dom_node_t *el)` - *Concatenates the descendant text of el into an owned NUL-terminated string (the value of a <textarea> / the label of a <button> / a flattened table...*
- `classify_input` (line 1452) `static pv_input_type classify_input(const char *type)`
- `li_ordinal` (line 1598) `static int li_ordinal(const lxb_dom_node_t *li)` - *1-based position of an <li> among its <li> siblings (an <ol> counter, basic: the `start`/`value` attributes are out of scope). Counts preceding ele...*
- `roman_marker` (line 1624) `static void roman_marker(int n, int upper, char *out, size_t cap)` - *int k = 0; if (n < 1) n = 1; while (n > 0 && k < (int)sizeof buf) { int r = (n - 1) % 26; buf[k++] = (char)((upper ? 'A' : 'a') + r); n = (n - 1) /...*
- `list_marker` (line 1649) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...` - *Builds the list marker for the first run of an <li>. With no author list-style (CSS_LS_UNSET) it is the UA default: "N. " for an ordered list, "* "...*
- `nearest_table` (line 1669) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` - *case CSS_LS_CIRCLE:      snprintf(out, cap, "\xE2\x97\xA6 "); return; /* U+25E6 white bullet case CSS_LS_SQUARE:      snprintf(out, cap, "\xE2\x96\...*
- `cell_has_nested_table` (line 1694) `static int cell_has_nested_table(const lxb_dom_node_t *cell)` - *Nonzero if cell has a descendant <table>: it is then a structural CONTAINER, not a leaf cell. Only leaf cells (no nested table) are collected as on...*
- `next_skip` (line 1703) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` - *Pre-order successor that does NOT descend into n's children (used to skip an * already-decided subtree during the table scan).*
- `cell_anchors` (line 1714) `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` - *First <a href> element in the cell's subtree, with *count receiving how many * such anchors exist, capped at 2 (only none / exactly-one / several m...*
- `links` (line 1732) `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
- `flow_table` (line 1763) `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
- `table` (line 1779) `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
- `collect_style_text` (line 1826) `static char *collect_style_text(lxb_dom_node_t *root, size_t *outlen)` - *Concatenates the text of every <style> element in the document (head included) into one owned, NUL-terminated buffer, capped at PV_MAX_STYLE_BYTES....*
- `in_hidden_subtree` (line 1860) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...` - *Nonzero if n or any ancestor up to base has display:none (from the <style> sheet or its inline style=). display:none is structural visibility, appl...*
- `in_boilerplate_subtree` (line 1875) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` - *Nonzero if n or any ancestor up to base is page boilerplate (<nav>/<header>/ <footer>/<aside>). Used only in distraction-free (reader) mode to drop...*
- `pv_build` (line 1886) `pv_status pv_build(const hp_document *doc, pv_view **out)`
- `pv_build_ex` (line 1890) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
- `pv_build_full` (line 1894) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
- `pv_build_styled` (line 1899) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
- `appended` (line 2376) `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...`

**Macros:**
- `_POSIX_C_SOURCE` (line 9)
- `PV_MAX_DIM` (line 37)
- `PV_NODE_MAP_INIT_CAP` (line 213)
- `PV_COLOR_TOKEN_MAX` (line 675)
- `PV_MAX_CONTAINERS` (line 709)
- `PV_MAX_GRID_COLS` (line 711)
- `PV_MAX_STYLE_BYTES` (line 1820)

**Structs:**
- `pv_node_map` (line 215)
- `pv_cont_info` (line 719) - *Nearest-container info attached to a run, plus the flex per-item values (Stage 3): grow/shrink/basis/order come from the ITEM element (the containe...*
- `pv_item_track` (line 745) - *Per-container item-ordinal tracker: ord[cid] is the ordinal last handed out for container cid, node[cid] the direct-child element it belongs to. A ...*
- `pv_box_info` (line 764) - *Author box model resolved for a run: horizontal placement (l/r insets, w cap, centered) from the nearest block ancestor that declares a box, plus t...*
- `pv_container_reg` (line 902) - *Document-order registry of flex/grid container nodes, so the runs of one * container share a stable id.*
- `pv_box_reg` (line 919) - *Box engine (Hito 23b-8 Step D): document-order registry of box-carrying block nodes plus each box's resolved definition (decoration + parent link)....*
- `pv_style_cache` (line 1004) - *Per-document memo of cch_element_style() results, keyed by element pointer. resolve_context()/in_hidden_subtree() call cch_element_style once per A...*
- `form_rec` (line 1341) - *One <form> seen in document order: its grouping id is its index. action is an owned NUL-terminated copy of the raw action attribute (or NULL); meth...*
- `form_table` (line 1347)
- `pv_flow_reg` (line 1758) - *Cache of the per-table flow decision (a table subtree is scanned at most once, * anti-DoS). Registry full => grid (the previous behaviour), bounded...*

#### `pdf_export.c`
**Path:** `src/pdf_export.c`

**Functions:**
- `pe_safe_basename` (line 24) `pe_status pe_safe_basename(const char *title, char *out, size_t outsz)`
- `pe_build_path_ext` (line 65) `pe_status pe_build_path_ext(const char *dir, const char *title, const char *ext,
                ...`
- `pe_build_path` (line 90) `pe_status pe_build_path(const char *dir, const char *title, char *out, size_t outsz)`
- `pe_paginate` (line 94) `size_t pe_paginate(const double *tops, const double *heights, size_t n,
                   double...`

#### `prefetch.c`
**Path:** `src/prefetch.c`

**Functions:**
- `is_ws` (line 22) `static int is_ws(char c)` - *Longest raw reference the scanner keeps; matches URL_MAX_LEN (url.h) so a * ref the fetch path would reject on length is never even queued. define ...*
- `is_name_char` (line 26) `static int is_name_char(char c)`
- `lower` (line 31) `static int lower(int c)`
- `ci_starts` (line 37) `static int ci_starts(const char *p, const char *end, const char *kw)` - *static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int is_name_char(char c) { return (c >= 'a...*
- `ci_find` (line 46) `static const char *ci_find(const char *p, const char *end, const char *kw)` - *static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Case-insensitive: [p,end) starts with kw. static int ci_starts(...*
- `ci_eq_span` (line 54) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
- `emit` (line 116) `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
- `pf_scan` (line 128) `int pf_scan(const char *html, size_t len, pf_list *out)`
- `pf_list_free` (line 191) `void pf_list_free(pf_list *l)`
- `pf_worker` (line 199) `static void *pf_worker(void *arg)` - *} p++; } return 0; } void pf_list_free(pf_list *l) { if (l == NULL) return; for (size_t i = 0; i < l->count; ++i) free(l->refs[i].url); l->count = ...*
- `pf_pool_start` (line 225) `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
- `pf_pool_take` (line 269) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
- `pf_pool_finish` (line 308) `void pf_pool_finish(pf_pool *p)`
- `pf_pooled_fetch` (line 322) `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
                    const ch...`

**Macros:**
- `_POSIX_C_SOURCE` (line 11)
- `PF_MAX_URL` (line 21)

**Structs:**
- `attr_span` (line 62)

#### `prefs.c`
**Path:** `src/prefs.c`

**Functions:**
- `url_valid` (line 26) `static int url_valid(const char *url)` - *A representable URL: 1..PREFS_MAX_URL-1 bytes, no control bytes, no DEL. * Space is allowed (local paths may carry it; fields are tab-separated).*
- `title_clean` (line 39) `static char *title_clean(const char *src)` - *Copies src into a fresh buffer, mapping control bytes/DEL to ' ' and truncating to PREFS_MAX_TITLE bytes on a UTF-8 sequence boundary. A NULL * src...*
- `prefs_init` (line 65) `void prefs_init(prefs_state *p)` - *((unsigned char)dst[n - 1 - back] & 0xC0u) == 0x80u) { ++back; } if (back < n) { unsigned char lead = (unsigned char)dst[n - 1 - back]; size_t need...*
- `prefs_free` (line 73) `void prefs_free(prefs_state *p)`
- `bookmark_push` (line 91) `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` - *Appends a cleaned bookmark. Duplicate URLs are skipped (PREFS_OK). Used by * the toggle's add path and by the parser.*
- `history_push_back` (line 109) `static prefs_status history_push_back(prefs_state *p, const char *url)` - *Appends a history entry at the BACK preserving document order (parser path; * the API path inserts at the front). Duplicates and overflow are skipped.*
- `prefs_bookmark_index` (line 124) `int prefs_bookmark_index(const prefs_state *p, const char *url)` - *if (p->history_len >= PREFS_MAX_HISTORY) return PREFS_OK; for (size_t i = 0; i < p->history_len; ++i) if (strcmp(p->history[i], url) == 0) return P...*
- `prefs_bookmark_toggle` (line 131) `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
- `prefs_history_add` (line 151) `prefs_status prefs_history_add(prefs_state *p, const char *url)`
- `prefs_format` (line 182) `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` - *p->history_len--; } char **grown = (char **)realloc(p->history, (p->history_len + 1) * sizeof *grown); if (grown == NULL) { free(u); return PREFS_E...*
- `apply_kv` (line 215) `static void apply_kv(prefs_state *out, const char *key, long val)` - *PREFS_VERSION, p->theme_mode, p->force_theme, p->images, p->css, p->reader, p->js_mode, p->tor, p->i2p, p->torify, p->zoom_pct, p->remember_history...*
- `prefs_parse` (line 230) `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
- `ci_eq` (line 289) `static int ci_eq(char a, char b)` - *char *eq = strchr(lbuf, '='); if (eq != NULL && eq != lbuf) { eq = '\0'; apply_kv(out, lbuf, strtol(eq + 1, NULL, 10)); } } } /* Oversized or malfo...*
- `ci_starts` (line 295) `static int ci_starts(const char *s, const char *q)`
- `ci_contains` (line 303) `static int ci_contains(const char *s, const char *q)`
- `url_prefix_match` (line 313) `static int url_prefix_match(const char *url, const char *q)` - *Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits "https://www.wikipedia.org/").*
- `sugg_push` (line 325) `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...` - *Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits "https://www.wikipedia.org/"). static int...*
- `prefs_suggest` (line 333) `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
- `sb_put` (line 358) `static void sb_put(sbuf *b, const char *s, size_t n)`
- `sb_str` (line 373) `static void sb_str(sbuf *b, const char *s)`
- `sb_esc` (line 377) `static void sb_esc(sbuf *b, const char *s)` - *while (nc < b->len + n + 1) nc *= 2; char *nd = (char *)realloc(b->data, nc); if (nd == NULL) { b->oom = 1; return; } b->data = nd; b->cap = nc; } ...*
- `sb_link_item` (line 389) `static void sb_link_item(sbuf *b, const char *url, const char *label)`
- `prefs_bookmarks_page` (line 397) `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `PREFS_MAGIC` (line 19)

**Structs:**
- `sbuf` (line 357)

#### `profile.c`
**Path:** `src/profile.c`

**Functions:**
- `join_path` (line 28) `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...` - *#include "disk_store.h" #include <errno.h> #include <fcntl.h> #include <stdio.h> #include <stdlib.h> #include <string.h> #include <sys/stat.h> #inc...*
- `keyfile_create` (line 36) `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` - *#include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h> #define PROFILE_KEYFILE_LEN (LS_SALT_LEN + LS_KEY_LEN)  /* 16 + 32 static...*
- `profile_open` (line 58) `profile_status profile_open(profile_ctx *ctx, const char *dir)`
- `map_ds` (line 97) `static profile_status map_ds(ds_status ds)`
- `profile_load` (line 111) `profile_status profile_load(const profile_ctx *ctx, prefs_state *out)`
- `profile_save` (line 132) `profile_status profile_save(const profile_ctx *ctx, const prefs_state *p)`
- `profile_close` (line 148) `void profile_close(profile_ctx *ctx)`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `PROFILE_KEYFILE_LEN` (line 26)

#### `render_doc.c`
**Path:** `src/render_doc.c`

**Functions:**
- `utf8_seq_len` (line 23) `static size_t utf8_seq_len(unsigned char c)` - *UTF-8 sanitisation, kept local so render_doc stays self-contained (matching the convention in browser.c and page_view.c). Output is never longer th...*
- `utf8_sanitized_dup` (line 31) `static char *utf8_sanitized_dup(const char *s)`
- `rd_push` (line 63) `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` - *Appends one block, taking owned copies of text (required) and href (optional). * Returns 0 on success, -1 on allocation failure (the doc is left co...*
- `rd_push_input` (line 165) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` - *Appends an RD_INPUT block, copying text (placeholder/label), the form action * (href), and the control name/value. Returns 0, or -1 on allocation f...*
- `rd_build` (line 187) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
- `url_resolve_file` (line 236) `url_resolve_file(top_level_url, r->src,
                                                resolved,...`
- `rd_free` (line 397) `void rd_free(rd_doc *d)`
- `rd_count` (line 411) `size_t rd_count(const rd_doc *d)`
- `rd_at` (line 415) `const rd_block *rd_at(const rd_doc *d, size_t i)`
- `rd_box_count` (line 420) `size_t rd_box_count(const rd_doc *d)`
- `rd_box_at` (line 424) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
- `rd_kind_name` (line 429) `const char *rd_kind_name(rd_kind k)`
- `rd_block_tag` (line 441) `const char *rd_block_tag(const rd_block *b)`
- `rd_input_label` (line 467) `const char *rd_input_label(int input_type)`
- `rd_image_label` (line 482) `const char *rd_image_label(rdp_img_decision d)`

#### `render_policy.c`
**Path:** `src/render_policy.c`

**Functions:**
- `rdp_caps_safe` (line 15) `rdp_caps rdp_caps_safe(void)` - *include "request_policy.h"*
- `rdp_is_tracking_pixel` (line 20) `int rdp_is_tracking_pixel(int w, int h)`
- `rdp_image_decision` (line 26) `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
- `rdp_img_reason` (line 49) `const char *rdp_img_reason(rdp_img_decision d)`
- `rdp_images_warning` (line 60) `const char *rdp_images_warning(void)`

#### `renderer.c`
**Path:** `src/renderer.c`

**Functions:**
- `write_full` (line 22) `static int write_full(int fd, const void *buf, size_t n)` - *#include "renderer.h" #include "html_parse.h" #include "os_sandbox.h" #include <errno.h> #include <stdint.h> #include <stdlib.h> #include <string.h...*
- `read_full` (line 33) `static int read_full(int fd, void *buf, size_t n)`
- `child_render` (line 47) `static void child_render(int wfd, const char *html, size_t len)` - *static int read_full(int fd, void *buf, size_t n) { uint8_t *p = (uint8_t *)buf; size_t got = 0; while (got < n) { ssize_t r = read(fd, p + got, n ...*
- `read_field` (line 75) `static int read_field(int fd, char **out, size_t *out_len)` - *int ok = (title != NULL && text != NULL) && write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd,...*
- `rd_render_html` (line 91) `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` - *size_t n = 0; if (read_full(fd, &n, sizeof n) != 0) return -1; if (n > RD_MAX_FIELD) return -1; /* anti-amplification: reject huge lengths char *bu...*
- `rd_result_free` (line 141) `void rd_result_free(rd_result *out)`

**Macros:**
- `_POSIX_C_SOURCE` (line 6)

#### `request_policy.c`
**Path:** `src/request_policy.c`

**Functions:**
- `lower` (line 21) `static char lower(char c)` - *all output goes to caller-provided bounded buffers.  #include "request_policy.h" #include "psl_data.h" #include <stdlib.h> #include <string.h> #def...*
- `ci_starts_with` (line 25) `static int ci_starts_with(const char *s, const char *prefix)`
- `psl_cmp` (line 35) `static int psl_cmp(const void *key, const void *elem)` - *static char lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c; } static int ci_starts_with(const char *s, const char *pre...*
- `psl_in` (line 39) `static int psl_in(const char *const *arr, size_t n, const char *key)`
- `public_suffix_labels` (line 48) `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` - *Number of labels of the public suffix (eTLD) of a lowercased host, applying the full PSL algorithm: exception rules win; otherwise the longest matc...*
- `rp_host_of` (line 75) `int rp_host_of(const char *url, char *out, size_t out_size)` - *} if (s + 1 < n) { const char *parent = host + off[s + 1]; /* labels[s+1..n-1] if (psl_in(psl_wildcards, psl_wildcards_n, parent)) { if (ncand > be...*
- `rp_site_of` (line 101) `int rp_site_of(const char *host, char *out, size_t out_size)`
- `rp_same_site` (line 133) `int rp_same_site(const char *top_level_url, const char *request_url)`
- `rp_evaluate` (line 142) `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`

**Macros:**
- `RP_MAX_HOST` (line 16)
- `RP_MAX_LABELS` (line 18)

#### `secure_fetch.c`
**Path:** `src/secure_fetch.c`

**Functions:**
- `ci_starts_with` (line 42) `static int ci_starts_with(const char *haystack, const char *prefix)` - */* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a && *b) { int ca = (unsigned char...*
- `ci_index` (line 54) `static long ci_index(const char *haystack, const char *needle)` - */* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char *prefix) { while (*prefix) { int c...*
- `sf_share_lock` (line 65) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (line 71) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (line 78) `void sf_global_init(void)` - *static pthread_mutex_t sf_cookie_lock = PTHREAD_MUTEX_INITIALIZER; static void sf_share_lock(CURL *handle, curl_lock_data data, curl_lock_access ac...*
- `sf_cookie_line_matches` (line 93) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (line 149) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` - *Extracts host + path from a validated https url into caller buffers (path defaults * to "/"). Returns 0 on success, -1 on failure.*
- `sf_cookie_header_for` (line 163) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (line 192) `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (line 213) `sf_config sf_config_default(void)`
- `sf_user_agent_or_default` (line 236) `const char *sf_user_agent_or_default(const char *ua)`
- `sf_impersonate_kex_groups` (line 240) `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (line 242) `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (line 245) `sf_status sf_validate_url(const char *url)` - *c.sec_fetch_mode = NULL; c.progress_ctx = NULL; c.progress_cb = NULL; return c; } const char *sf_user_agent_or_default(const char *ua) { return (ua...*
- `sf_url_is_http` (line 254) `static int sf_url_is_http(const char *url)` - *Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host. Plain http is only ever permitted for overlay (.onion/.i2p) realms, g...*
- `sf_check_tls_version` (line 265) `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (line 270) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (line 279) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (line 289) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (line 320) `static int copy_checked(char *dst, size_t dstsz, const char *src)` - *The navigability fallback accepts a classical KE; every other policy requires * a PQ-hybrid group. The certificate chain is always validated below....*
- `sf_is_redirect_code` (line 329) `int sf_is_redirect_code(long http_code)` - *if (chain == NULL) return SF_ERR_INTERNAL; /* fail closed: chain not inspectable return sf_check_chain_policy(chain, policy); } /* --- bounded stri...*
- `sf_parse_location_header` (line 336) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (line 354) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `sf_ci_prefix` (line 367) `static int sf_ci_prefix(const char *s, const char *p)` - *Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a reference resolved against the ...*
- `sf_response_free` (line 406) `void sf_response_free(sf_response *resp)` - *if (sf_ci_prefix(location, "http://")) { if (snprintf(hloc, sizeof hloc, "https://%s", location + 7) >= (int)sizeof hloc) return SF_ERR_INVALID_URL...*
- `copy_bounded` (line 465) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (line 477) `static const char *get_negotiated_group_name(SSL *ssl)` - *static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void copy_bounded(char *dst, size_t dstsz, const c...*
- `tls_capture_try` (line 508) `static void tls_capture_try(tls_capture *cap)` - *first shared group, which corresponds to the negotiated key exchange * group (for both TLS 1.2 ECDHE and TLS 1.3). nid = SSL_get_shared_group(ssl, ...*
- `header_cb` (line 540) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` - *Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to snapshot the negotiated TLS state.*
- `write_cb` (line 575) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (line 608) `static int name_is_pq_sig(int pknid)` - *if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; } memcpy(sink->data + sink->len, ptr, in...*
- `inspect_chain` (line 618) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` - *Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if the chain could not be inspected.*
- `map_curl_error` (line 670) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `sf_perform` (line 713) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` - *The shared request engine for sf_get and sf_post. When post_body == NULL it is a GET; otherwise it is a POST carrying body (post_len bytes) with co...*
- `redirect` (line 806) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_get` (line 962) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (line 966) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_get_follow` (line 980) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`

**Macros:**
- `_POSIX_C_SOURCE` (line 11)

**Structs:**
- `body_sink` (line 430)
- `tls_capture` (line 443) - *Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a transfer is in progress (via CURLINFO_TLS_SSL_PTR); after curl_easy_p...*
- `fetch_ctx` (line 453)

#### `tab.c`
**Path:** `src/tab.c`

**Functions:**
- `write_full` (line 80) `static int write_full(int fd, const void *buf, size_t n)` - *Per-page subresource caps (anti-DoS): a hostile script cannot drive unbounded fetches * or amplification through the parent. #define TAB_MAX_SUBREQ...*
- `read_full` (line 91) `static int read_full(int fd, void *buf, size_t n)`
- `child_reset_page` (line 124) `static void child_reset_page(child_state *cs)`
- `policy` (line 138) `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
- `run_js` (line 190) `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
- `write_view` (line 276) `static int write_view(int wfd, const pv_view *v)` - *cont_col_w[PV_GRID_TRACKS],grid_span, flex_grow,flex_shrink,flex_basis,flex_order,flex_direction,cont_item, cont_wrap,cont_row_gap,cont_align_items...*
- `FB_MAX_FILE_BYTES` (line 497) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (line 527) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` - *Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS budget across the inline scrip...*
- `ctype_is_javascript` (line 541) `static int ctype_is_javascript(const char *ctype)` - *Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types): accept a missing/empty type -- class...*
- `ctype_is_css` (line 550) `static int ctype_is_css(const char *ctype)` - *Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is accepted, anything else must mention...*
- `log_external_skip` (line 558) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` - *Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused). The raw hostile src is bounded by the messag...*
- `window` (line 578) `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_handle_load` (line 620) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `child_next_timer_ms` (line 790) `static int32_t child_next_timer_ms(child_state *cs)` - *Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending. Does NOT touch the console trans...*
- `child_handle_mutation` (line 805) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` - *Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so the parent can repaint mutation...*
- `child_handle_click` (line 852) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (line 856) `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_eval` (line 864) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` - *Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a JS-level error is ok==1 with the...*
- `child_handle_decode_image` (line 893) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` - *Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data]. Decoding hostile image bytes happens here, inside the confinement...*
- `gen_session_key` (line 909) `static uint64_t gen_session_key(void)`
- `tab_worker_run` (line 930) `static void tab_worker_run(int rfd, int wfd)` - *The confined request loop. Runs in the re-exec'd worker image (see * tab_worker_dispatch). Never returns to the caller (always _exit).*
- `parse_worker_fd` (line 1043) `static int parse_worker_fd(const char *s, int *out)` - *else /* OP_DECODE_IMAGE */      child_handle_decode_image(wfd, buf, len); free(buf); free(url); free(cookies); } child_reset_page(&cs); fb_buffer_f...*
- `tab_parse_worker_args` (line 1054) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (line 1064) `void tab_worker_dispatch(int argc, char **argv)`
- `ignore_sigpipe` (line 1094) `static void ignore_sigpipe(void)` - *A write to a dead child must not kill the parent with SIGPIPE. Idempotent; * no module-level mutable state of our own (the disposition is process-w...*
- `tab_refresh_alive` (line 1100) `static void tab_refresh_alive(tab *t)`
- `read_field` (line 1120) `static int read_field(int fd, char **out, size_t *out_len)` - *Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.*
- `read_view` (line 1135) `static int read_view(int fd, pv_view **out)` - *Reads a display list serialised by write_view into a fresh pv_view. The run * count and each field are capped against amplification from a hostile ...*
- `read_console` (line 1376) `static int read_console(int fd, fb_buffer *out)` - *Reads the console section written by write_console into out (a zero-initialised fb_buffer). Bounds the entry count and each length against amplific...*
- `send_request` (line 1412) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` - *if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt, elen) != 0) { free(txt); free(file)...*
- `io_failure` (line 1421) `static tab_status io_failure(tab *t)`
- `exec_worker_child` (line 1430) `static void exec_worker_child(int rfd, int wfd)` - *Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other tabs' content from tab_slots[], fr...*
- `tab_set_fetcher` (line 1498) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_net_allowed` (line 1504) `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (line 1509) `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_set_cookies` (line 1514) `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (line 1520) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `answered` (line 1533) `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
- `tab_load` (line 1568) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (line 1572) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (line 1576) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (line 1772) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (line 1779) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_eval` (line 1786) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image` (line 1823) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_alive` (line 1866) `int tab_alive(const tab *t)`
- `tab_child_pid` (line 1872) `pid_t tab_child_pid(const tab *t)`
- `tab_close` (line 1876) `void tab_close(tab *t)`
- `tab_page_free` (line 1889) `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (line 1907) `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (line 1916) `void tab_image_free(tab_image *img)`

**Macros:**
- `_GNU_SOURCE` (line 13)
- `TAB_SCREEN_W` (line 50)
- `TAB_SCREEN_H` (line 51)
- `TAB_MAX_RUNS` (line 55)
- `TAB_MAX_URL` (line 58)
- `TAB_MAX_SUBREQ` (line 72)
- `TAB_MAX_SUBRESOURCE` (line 73)
- `TAB_MAX_JS_JOBS` (line 74)
- `TAB_MAX_EXTERN_CSS` (line 570)

**Structs:**
- `child_state` (line 106)
- `tab` (line 1075)

#### `text_shape.c`
**Path:** `src/text_shape.c`

**Functions:**
- `generic_name` (line 53) `static const char *generic_name(int family)`
- `backend_init` (line 63) `static int backend_init(void)`
- `read_font_file` (line 80) `static unsigned char *read_font_file(const char *path, long *out_n)`
- `load_entry` (line 96) `static int load_entry(tsh_entry *e, int family, int bold, int italic)`
- `get_entry` (line 151) `static tsh_entry *get_entry(int family, int bold, int italic)`
- `tsh_ready` (line 163) `int tsh_ready(void)`
- `tsh_shape` (line 168) `tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len,
                ...`
- `tsh_measure` (line 213) `double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)`
- `tsh_draw` (line 220) `tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px,
                    double x, doub...`
- `tsh_shutdown` (line 242) `void tsh_shutdown(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 11)
- `TSH_MAX_FONT_BYTES` (line 28)
- `TSH_CACHE_SLOTS` (line 32)

**Structs:**
- `tsh_entry` (line 34)

#### `textfield.c`
**Path:** `src/textfield.c`

**Functions:**
- `whole` (line 6) `* the buffer is rejected whole (fail closed), never applied partially.
 */

#include "textfield.h...`
- `tf_clear` (line 19) `void tf_clear(tf_field *f)`
- `tf_set` (line 23) `tf_status tf_set(tf_field *f, const char *s)`
- `tf_insert` (line 34) `tf_status tf_insert(tf_field *f, char c)`
- `tf_backspace` (line 46) `void tf_backspace(tf_field *f)`
- `tf_delete` (line 54) `void tf_delete(tf_field *f)`
- `tf_move` (line 61) `void tf_move(tf_field *f, long delta)`
- `tf_home` (line 72) `void tf_home(tf_field *f)`
- `tf_end` (line 77) `void tf_end(tf_field *f)`
- `tf_text` (line 82) `const char *tf_text(const tf_field *f)`
- `tf_len` (line 86) `size_t tf_len(const tf_field *f)`
- `tf_cursor` (line 90) `size_t tf_cursor(const tf_field *f)`

#### `tls_impersonate.c`
**Path:** `src/tls_impersonate.c`

**Functions:**
- `ti_should_impersonate` (line 17) `int ti_should_impersonate(int host_in_allowlist, int host_js_enabled,
                          i...` - *helper. See spec/tls_impersonate.md and include/tls_impersonate.h.  No I/O, no global state. Two pieces: the triple opt-in gate, and a little-endia...*
- `bounded_len` (line 24) `static size_t bounded_len(const char *s, size_t max)` - *#include "tls_impersonate.h" #include <stdlib.h> #include <string.h> /* --- the triple opt-in gate --- int ti_should_impersonate(int host_in_allowl...*
- `put_u8` (line 34) `static void put_u8(ti_wr *w, uint8_t v)`
- `put_u32` (line 39) `static void put_u32(ti_wr *w, uint32_t v)`
- `put_u64` (line 47) `static void put_u64(ti_wr *w, uint64_t v)`
- `put_blob` (line 52) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
- `get_u8` (line 64) `static uint8_t get_u8(ti_rd *r)`
- `get_u32` (line 69) `static uint32_t get_u32(ti_rd *r)`
- `get_u64` (line 79) `static uint64_t get_u64(ti_rd *r)`
- `get_bytes` (line 89) `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` - *| ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t get_u64(ti_rd *r) { if (r->err || r->off + 8u > r->len) { r->err = 1...*
- `get_str` (line 103) `static char *get_str(ti_rd *r, size_t cap)` - *static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len) { out = NULL; *out_len = 0; uint32_t n = get_u32(r); if (r->err) return...*
- `valid_profile` (line 114) `static int valid_profile(int p)`
- `ti_encode_req` (line 120) `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)` - *if ((size_t)n > cap || r->off + (size_t)n > r->len) { r->err = 1; return NULL; } char *s = malloc((size_t)n + 1u); if (s == NULL) { r->err = 1; ret...*
- `ti_decode_req` (line 138) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
- `ti_req_free` (line 164) `void ti_req_free(ti_req *r)`
- `ti_encode_resp` (line 175) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)` - *out->profile = (ti_profile)prof; return 0; } void ti_req_free(ti_req *r) { if (r == NULL) return; free((void *)r->url); free((void *)r->method); fr...*
- `ti_decode_resp` (line 194) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
- `ti_resp_free` (line 228) `void ti_resp_free(ti_resp *r)`

#### `ui_layout.c`
**Path:** `src/ui_layout.c`

**Functions:**
- `layout_push` (line 12) `static int layout_push(ui_layout *lay, size_t offset, size_t len)` - *include <stdlib.h>*
- `ui_wrap_text` (line 26) `ui_status ui_wrap_text(const char *text, size_t len, size_t max_cols, ui_layout *out)`
- `ui_layout_free` (line 90) `void ui_layout_free(ui_layout *lay)`
- `ui_clamp_scroll` (line 98) `size_t ui_clamp_scroll(size_t desired, size_t total_lines, size_t viewport_lines)`

#### `url.c`
**Path:** `src/url.c`

**Functions:**
- `ci_prefix` (line 19) `static int ci_prefix(const char *haystack, const char *prefix)` - *dot-segment canonicalisation. Fails closed: a non-https result is never produced; every assembly is bounded and reports overflow rather than trunca...*
- `copy_checked` (line 31) `static int copy_checked(char *out, size_t outsz, const char *src)` - */* Case-insensitive: does haystack start with prefix? static int ci_prefix(const char *haystack, const char *prefix) { while (*prefix) { int ch = (...*
- `cat_checked` (line 39) `static int cat_checked(char *out, size_t outsz, const char *src)` - *+haystack; ++prefix; } return 1; } /* Bounded copy: out gets src (NUL-terminated). Nonzero on overflow. static int copy_checked(char *out, size_t o...*
- `ncat_checked` (line 48) `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` - *memcpy(out, src, n + 1); return 0; } /* Bounded append: out += src. Nonzero on overflow. static int cat_checked(char *out, size_t outsz, const char...*
- `url_has_scheme` (line 57) `int url_has_scheme(const char *s)` - *memcpy(out + cur, src, n + 1); return 0; } /* Bounded append of the first n bytes of src. Nonzero on overflow. static int ncat_checked(char *out, s...*
- `url_is_https` (line 71) `int url_is_https(const char *s)`
- `url_validate_https` (line 78) `url_status url_validate_https(const char *url)`
- `url_authority_len` (line 89) `size_t url_authority_len(const char *url)`
- `out_pop_segment` (line 99) `static void out_pop_segment(char *out, size_t *olen)` - *while (i <= URL_MAX_LEN && url[i] != '\0') ++i; if (i > URL_MAX_LEN) return URL_ERR_NOT_HTTPS; return url_is_https(url) ? URL_OK : URL_ERR_NOT_HTTP...*
- `url_remove_dot_segments` (line 105) `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
- `dir_len` (line 156) `static size_t dir_len(const char *base)` - *Length of base up to and including the last path '/', ignoring query/fragment. * If the path carries no slash, returns the authority length.*
- `url_resolve_https` (line 166) `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
- `is_space` (line 214) `static int is_space(int c)` - *char norm[URL_MAX_LEN + 1]; url_status ns = url_remove_dot_segments(merged, norm, sizeof norm); if (ns != URL_OK) return ns; out[0] = '\0'; if (nca...*
- `is_unreserved` (line 218) `static int is_unreserved(int c)`
- `append_query_encoded` (line 226) `static int append_query_encoded(char *out, size_t outsz, const char *src)` - *Percent-encodes src into a query value appended to out (space -> '+', every * non-unreserved byte -> %XX). Nonzero on overflow.*
- `assumed` (line 251) `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
- `build_search` (line 299) `static url_status build_search(const char *query, char *out, size_t outsz)`
- `url_omnibox` (line 305) `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
- `host_equals` (line 375) `static int host_equals(const url_parts *p, const char *want)` - *Any remaining explicit scheme is never executed nor downgraded: search for it * (so "javascript:...", "file:...", "ftp://..." become harmless queri...*
- `query_find_q` (line 390) `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` - *Returns a pointer to the value of the "q" parameter within a "?a=b&q=v&..." search span, with its length in *vlen (up to the next '&' or the end), ...*
- `url_search_rewrite` (line 407) `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
- `url_extract_userinfo` (line 427) `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...` - *return URL_ERR_NOT_HTTPS; if (p.search_len == 0) return URL_ERR_NOT_HTTPS; size_t qv = 0; const char *q = query_find_q(p.search, p.search_len, &qv)...*
- `url_is_file` (line 521) `int url_is_file(const char *s)` - *username_out = strdup(username); if (*username_out == NULL) return URL_ERR_NULL_ARG; } if (password_out != NULL) { password_out = (pass_len > 0) ? ...*
- `url_file_path` (line 527) `const char *url_file_path(const char *s)`
- `url_resolve_file` (line 531) `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
- `url_split` (line 580) `url_status url_split(const char *url, url_parts *out)` - *Confinement: the canonical path must stay inside the base directory subtree. base directory text = base_path[0..dir_end) (ends with '/'), so a stri...*

**Macros:**
- `_POSIX_C_SOURCE` (line 8)

#### `zoom.c`
**Path:** `src/zoom.c`

**Functions:**
- `zm_clamp` (line 13) `int zm_clamp(int pct)` - *define ZM_LADDER_N ((int)(sizeof ZM_LADDER / sizeof ZM_LADDER[0]))*
- `zm_zoom_in` (line 19) `int zm_zoom_in(int pct)`
- `zm_zoom_out` (line 27) `int zm_zoom_out(int pct)`
- `zm_reset` (line 35) `int zm_reset(void)`
- `zm_scale` (line 39) `double zm_scale(int pct)`
- `zm_apply` (line 43) `double zm_apply(double base_px, int pct)`

**Macros:**
- `ZM_LADDER_N` (line 12)

#### `itest_secure_fetch.c`
**Path:** `tests/itest_secure_fetch.c`

**Functions:**
- `main` (line 25) `int main(void)`

**Macros:**
- `CHECK` (line 15)

#### `test_anti_fp.c`
**Path:** `tests/test_anti_fp.c`

**Functions:**
- `test_coarsen_time` (line 17) `static void test_coarsen_time(void **state)` - *Pure primitives: no I/O. Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #i...*
- `test_identity_is_fixed` (line 33) `static void test_identity_is_fixed(void **state)` - *(void)state; uint64_t res = fp_timer_resolution_ms(); assert_true(res > 0); assert_int_equal((int)fp_coarsen_time_ms(0), 0); assert_int_equal((int)...*
- `test_legacy_identity_fixed` (line 60) `static void test_legacy_identity_fixed(void **state)` - *assert_string_equal(fp_accept_language_header(), "en-US,en;q=0.5"); assert_non_null(strstr(fp_accept_language_header(), "en-US")); assert_null(strc...*
- `test_boolean_props` (line 73) `static void test_boolean_props(void **state)`
- `test_bucket_screen` (line 82) `static void test_bucket_screen(void **state)` - *assert_string_equal(fp_product_sub(), "20100101"); assert_string_equal(fp_oscpu(), "Linux x86_64"); assert_non_null(fp_build_id()); assert_true(str...*
- `test_perturb_deterministic` (line 100) `static void test_perturb_deterministic(void **state)` - *fp_bucket_screen(1920, 1080, &w, &h); assert_int_equal(w, 1920); assert_int_equal(h, 1080); fp_bucket_screen(1680, 1050, &w, &h); assert_int_equal(...*
- `test_perturb_bounded_lsb` (line 110) `static void test_perturb_bounded_lsb(void **state)`
- `test_perturb_key_sensitive` (line 125) `static void test_perturb_key_sensitive(void **state)`
- `test_perturb_safe_edges` (line 135) `static void test_perturb_safe_edges(void **state)`
- `test_origin_key_deterministic` (line 145) `static void test_origin_key_deterministic(void **state)` - *fp_perturb(a, sizeof a, 1); fp_perturb(b, sizeof b, 2); assert_memory_not_equal(a, b, sizeof a); /* different key => different output } static void...*
- `test_origin_key_per_site` (line 152) `static void test_origin_key_per_site(void **state)`
- `test_origin_key_per_session` (line 164) `static void test_origin_key_per_session(void **state)`
- `test_origin_key_empty_namespace` (line 170) `static void test_origin_key_empty_namespace(void **state)`
- `test_origin_key_unlinks_readback` (line 183) `static void test_origin_key_unlinks_readback(void **state)` - *The property that actually matters: the same canvas buffer poisoned under two different sites' keys diverges, so a tracker cannot link the two read...*
- `main` (line 196) `int main(void)`

#### `test_box_style.c`
**Path:** `tests/test_box_style.c`

**Functions:**
- `dbl_eq` (line 22) `static int dbl_eq(double a, double b)` - *the display-name helper.  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #...*
- `assert_edges` (line 26) `static void assert_edges(bx_edges e, double t, double r, double b, double l)`
- `test_body_has_no_margin` (line 33) `static void test_body_has_no_margin(void **state)`
- `test_paragraph` (line 41) `static void test_paragraph(void **state)`
- `test_heading_ladder` (line 48) `static void test_heading_ladder(void **state)`
- `test_lists` (line 64) `static void test_lists(void **state)`
- `test_blockquote` (line 75) `static void test_blockquote(void **state)`
- `test_hr` (line 82) `static void test_hr(void **state)`
- `test_inline_and_inline_block` (line 89) `static void test_inline_and_inline_block(void **state)`
- `test_display_none_for_non_rendered` (line 100) `static void test_display_none_for_non_rendered(void **state)`
- `test_case_insensitive` (line 109) `static void test_case_insensitive(void **state)`
- `test_unknown_and_null_are_neutral_inline` (line 117) `static void test_unknown_and_null_are_neutral_inline(void **state)`
- `test_div_is_block` (line 132) `static void test_div_is_block(void **state)`
- `test_parse_display_keywords` (line 139) `static void test_parse_display_keywords(void **state)`
- `test_parse_display_inline_aliases` (line 158) `static void test_parse_display_inline_aliases(void **state)`
- `test_parse_display_case_and_trim` (line 167) `static void test_parse_display_case_and_trim(void **state)`
- `test_parse_display_errors` (line 176) `static void test_parse_display_errors(void **state)`
- `test_display_name` (line 194) `static void test_display_name(void **state)`
- `test_place_no_box_is_identity` (line 209) `static void test_place_no_box_is_identity(void **state)` - *static void test_display_name(void **state) { (void)state; assert_string_equal(bx_display_name(BX_DISPLAY_BLOCK), "block"); assert_string_equal(bx_...*
- `test_place_max_width_caps` (line 216) `static void test_place_max_width_caps(void **state)`
- `test_place_centering` (line 227) `static void test_place_centering(void **state)`
- `test_place_insets` (line 239) `static void test_place_insets(void **state)`
- `test_place_failclosed_bounds` (line 251) `static void test_place_failclosed_bounds(void **state)`
- `main` (line 295) `int main(void)`

#### `test_box_tree.c`
**Path:** `tests/test_box_tree.c`

**Functions:**
- `assert_rect` (line 26) `static void assert_rect(const bt_node *n, double x, double y, double w, double h)`
- `test_null_root` (line 33) `static void test_null_root(void **state)`
- `test_leaf` (line 38) `static void test_leaf(void **state)`
- `test_leaf_with_padding` (line 45) `static void test_leaf_with_padding(void **state)`
- `test_block_stacking_with_collapse` (line 60) `static void test_block_stacking_with_collapse(void **state)`
- `test_flex_row_grow` (line 73) `static void test_flex_row_grow(void **state)`
- `test_flex_gap_and_justify_center` (line 91) `static void test_flex_gap_and_justify_center(void **state)`
- `test_flex_wrap_two_lines` (line 107) `static void test_flex_wrap_two_lines(void **state)`
- `test_flex_nowrap_default_single_line_unchanged` (line 129) `static void test_flex_nowrap_default_single_line_unchanged(void **state)`
- `test_flex_wrap_reverse_two_lines` (line 149) `static void test_flex_wrap_reverse_two_lines(void **state)`
- `test_flex_wrap_row_gap_distinct_from_gap` (line 171) `static void test_flex_wrap_row_gap_distinct_from_gap(void **state)`
- `test_flex_cross_axis_align` (line 191) `static void test_flex_cross_axis_align(void **state)`
- `test_grid_row_gap_distinct_from_gap` (line 209) `static void test_grid_row_gap_distinct_from_gap(void **state)`
- `test_grid_without_row_gap_falls_back_to_gap` (line 232) `static void test_grid_without_row_gap_falls_back_to_gap(void **state)`
- `test_grid` (line 248) `static void test_grid(void **state)`
- `test_grid_weighted_tracks` (line 269) `static void test_grid_weighted_tracks(void **state)`
- `test_grid_column_span` (line 287) `static void test_grid_column_span(void **state)`
- `test_nested_flex_in_block` (line 307) `static void test_nested_flex_in_block(void **state)`
- `test_display_none_skipped` (line 331) `static void test_display_none_skipped(void **state)`
- `test_grid_bad_columns` (line 346) `static void test_grid_bad_columns(void **state)`
- `test_flex_negative_gap` (line 356) `static void test_flex_negative_gap(void **state)`
- `test_children_cap` (line 366) `static void test_children_cap(void **state)`
- `test_depth_cap` (line 376) `static void test_depth_cap(void **state)`
- `test_positioning_null_args` (line 393) `static void test_positioning_null_args(void **state)` - *static bt_node chain[BT_MAX_DEPTH + 5]; size_t n = sizeof chain / sizeof chain[0]; for (size_t i = 0; i < n; ++i) { chain[i].display = BX_DISPLAY_B...*
- `test_positioning_static_unchanged` (line 407) `static void test_positioning_static_unchanged(void **state)`
- `test_positioning_relative_offset` (line 419) `static void test_positioning_relative_offset(void **state)`
- `test_positioning_absolute_against_ancestor` (line 440) `static void test_positioning_absolute_against_ancestor(void **state)`
- `test_positioning_absolute_against_viewport` (line 463) `static void test_positioning_absolute_against_viewport(void **state)`
- `test_positioning_fixed_against_viewport` (line 480) `static void test_positioning_fixed_against_viewport(void **state)`
- `test_positioning_sticky_treated_as_relative` (line 499) `static void test_positioning_sticky_treated_as_relative(void **state)`
- `test_positioning_stacking_order` (line 517) `static void test_positioning_stacking_order(void **state)`
- `test_positioning_doc_order_tiebreak` (line 537) `static void test_positioning_doc_order_tiebreak(void **state)`
- `test_positioning_no_insets` (line 555) `static void test_positioning_no_insets(void **state)`
- `test_positioning_null_geometry` (line 572) `static void test_positioning_null_geometry(void **state)`
- `test_positioning_nbox_cap` (line 589) `static void test_positioning_nbox_cap(void **state)`
- `main` (line 606) `int main(void)`

#### `test_browser.c`
**Path:** `tests/test_browser.c`

**Functions:**
- `test_init` (line 19) `static void test_init(void **state)` - *include "browser.h"*
- `test_navigate_history` (line 30) `static void test_navigate_history(void **state)`
- `test_navigate_from_middle_discards_future` (line 60) `static void test_navigate_from_middle_discards_future(void **state)`
- `test_back_forward_bounds` (line 78) `static void test_back_forward_bounds(void **state)`
- `test_rejects_invalid_url` (line 94) `static void test_rejects_invalid_url(void **state)`
- `test_accepts_https_and_file` (line 107) `static void test_accepts_https_and_file(void **state)`
- `test_url_bar_editing` (line 121) `static void test_url_bar_editing(void **state)`
- `test_url_bar_selection` (line 152) `static void test_url_bar_selection(void **state)` - *Omnibar selection model: extend builds a selection, ops replace/delete it, and a * plain move collapses it.*
- `test_set_page` (line 195) `static void test_set_page(void **state)`
- `test_set_page_sanitizes_invalid_utf8` (line 218) `static void test_set_page_sanitizes_invalid_utf8(void **state)` - *Page title/text come from hostile documents; legacy encodings (Latin-1) carry bytes that are invalid UTF-8 and poison the cairo text renderer. brow...*
- `test_exceptions` (line 251) `static void test_exceptions(void **state)`
- `test_status_toast` (line 277) `static void test_status_toast(void **state)` - *The transient status line (toast) is time-bounded and caller-clocked: visible until now_ms reaches the expiry, then gone. NULL/empty clears it, and...*
- `test_status_truncates` (line 308) `static void test_status_truncates(void **state)`
- `main` (line 325) `int main(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 7)

#### `test_css.c`
**Path:** `tests/test_css.c`

**Functions:**
- `test_inline_text_align` (line 31) `static void test_inline_text_align(void **state)`
- `test_inline_font_size` (line 39) `static void test_inline_font_size(void **state)`
- `test_inline_line_height` (line 49) `static void test_inline_line_height(void **state)`
- `test_inline_font_weight_style` (line 64) `static void test_inline_font_weight_style(void **state)`
- `test_inline_text_decoration` (line 76) `static void test_inline_text_decoration(void **state)`
- `test_font_family` (line 103) `static void test_font_family(void **state)` - */* none is an explicit value (0), distinct from unset (-1). assert_int_equal(css_parse_inline("text-decoration:none", 0).text_decoration, 0); /* Co...*
- `test_text_transform` (line 124) `static void test_text_transform(void **state)`
- `test_letter_word_spacing` (line 138) `static void test_letter_word_spacing(void **state)`
- `test_text_shadow` (line 153) `static void test_text_shadow(void **state)`
- `test_opacity` (line 175) `static void test_opacity(void **state)`
- `test_vertical_align` (line 185) `static void test_vertical_align(void **state)`
- `test_text_indent` (line 194) `static void test_text_indent(void **state)`
- `test_white_space` (line 203) `static void test_white_space(void **state)`
- `test_list_style_type` (line 214) `static void test_list_style_type(void **state)`
- `test_text_ext_cascade_and_important` (line 228) `static void test_text_ext_cascade_and_important(void **state)`
- `test_inline_display` (line 243) `static void test_inline_display(void **state)`
- `test_inline_container_props` (line 254) `static void test_inline_container_props(void **state)` - *assert_int_equal(s.font_family, CSS_FF_MONO);          /* inline wins css_free(sh); } static void test_inline_display(void **state) { (void)state; ...*
- `test_sheet_container_props` (line 282) `static void test_sheet_container_props(void **state)`
- `test_container_cascade_inline_wins` (line 303) `static void test_container_cascade_inline_wins(void **state)` - *const char *row[] = { "row" }; css_style f = css_resolve(sh, "div", NULL, row, 1, NULL, 0); assert_int_equal(f.display, CSS_DISP_FLEX); assert_int_...*
- `test_container_fail_closed_and_bounds` (line 318) `static void test_container_fail_closed_and_bounds(void **state)` - *Fail closed: a bad justify keyword is dropped (unset); grid-template-columns:none * is unset; gap and column count are clamped to their anti-DoS bo...*
- `test_grid_repeat_expands_count` (line 368) `static void test_grid_repeat_expands_count(void **state)`
- `test_grid_minmax_counts_as_one_track` (line 379) `static void test_grid_minmax_counts_as_one_track(void **state)`
- `test_grid_repeat_autofill_fails_closed` (line 387) `static void test_grid_repeat_autofill_fails_closed(void **state)`
- `test_grid_repeat_malformed_fails_closed` (line 398) `static void test_grid_repeat_malformed_fails_closed(void **state)`
- `test_grid_repeat_clamped_anti_dos` (line 405) `static void test_grid_repeat_clamped_anti_dos(void **state)`
- `test_container_unset` (line 412) `static void test_container_unset(void **state)`
- `test_url_value_dropped` (line 422) `static void test_url_value_dropped(void **state)` - *assert_int_equal( css_parse_inline("grid-template-columns: repeat(999, 1fr)", 0).grid_cols, (int)CSS_GRID_COLS_MAX); } static void test_container_u...*
- `test_unknown_props_ignored` (line 432) `static void test_unknown_props_ignored(void **state)`
- `test_linear_gradient_basic` (line 441) `static void test_linear_gradient_basic(void **state)` - */* A bare url() with no colour still yields -1. assert_int_equal(css_parse_inline("background: url(http://evil/x.png)", 0).background, -1); /* A pl...*
- `test_linear_gradient_directions` (line 452) `static void test_linear_gradient_directions(void **state)`
- `test_linear_gradient_stops` (line 471) `static void test_linear_gradient_stops(void **state)`
- `test_linear_gradient_fail_closed` (line 489) `static void test_linear_gradient_fail_closed(void **state)`
- `test_background_shorthand_resets_gradient` (line 510) `static void test_background_shorthand_resets_gradient(void **state)`
- `test_malformed_inline_no_crash` (line 529) `static void test_malformed_inline_no_crash(void **state)`
- `test_custom_prop_var_basic` (line 537) `static void test_custom_prop_var_basic(void **state)` - */* and a higher-specificity gradient CLEARS a lower-tier color css_style b = css_resolve(sh, "div", "grad", NULL, 0, NULL, 0); assert_int_equal(b.b...*
- `test_custom_prop_var_fallback_used_when_missing` (line 548) `static void test_custom_prop_var_fallback_used_when_missing(void **state)`
- `test_custom_prop_var_no_fallback_drops_decl` (line 554) `static void test_custom_prop_var_no_fallback_drops_decl(void **state)`
- `test_custom_prop_var_chain` (line 563) `static void test_custom_prop_var_chain(void **state)`
- `test_custom_prop_var_self_reference_fails_closed` (line 571) `static void test_custom_prop_var_self_reference_fails_closed(void **state)`
- `test_custom_prop_var_in_shorthand` (line 580) `static void test_custom_prop_var_in_shorthand(void **state)`
- `test_custom_prop_var_later_declaration_wins` (line 590) `static void test_custom_prop_var_later_declaration_wins(void **state)`
- `test_custom_prop_var_unbalanced_paren_drops` (line 603) `static void test_custom_prop_var_unbalanced_paren_drops(void **state)`
- `test_custom_prop_var_never_phones_home` (line 610) `static void test_custom_prop_var_never_phones_home(void **state)`
- `test_sheet_type_selector` (line 624) `static void test_sheet_type_selector(void **state)` - *A custom property whose value contains url() — colour IS honoured, * the URL is never fetched. css_style s = css_parse_inline( "--evil: url(http://...*
- `test_sheet_class_and_id` (line 635) `static void test_sheet_class_and_id(void **state)`
- `test_sheet_universal_and_group` (line 645) `static void test_sheet_universal_and_group(void **state)`
- `test_sheet_compound_selector` (line 655) `static void test_sheet_compound_selector(void **state)`
- `el_node` (line 669) `static css_element el_node(const char *tag, const char *id,
                           const char...` - *static void test_sheet_compound_selector(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse("a.button { color:#0a0b0c }"...*
- `el_sib_node` (line 680) `static css_element el_sib_node(const char *tag, int nth, int nsib,
                              ...` - *} /* Builds one css_element node aliasing the given fields (test-local helper). static css_element el_node(const char *tag, const char *id, const c...*
- `el_attr_node` (line 688) `static css_element el_attr_node(const char *tag, const char *id,
                                ...` - *e.attrs = NULL; e.nattrs = 0; e.parent = parent; e.nth = 0; e.nsib = 0; e.prev = NULL;   /* sibling context unknown by default return e; } /* Like ...*
- `test_text_decoration_cascade` (line 696) `static void test_text_decoration_cascade(void **state)`
- `test_descendant_combinator` (line 715) `static void test_descendant_combinator(void **state)`
- `test_child_combinator` (line 731) `static void test_child_combinator(void **state)`
- `test_combinator_specificity_sum` (line 744) `static void test_combinator_specificity_sum(void **state)`
- `test_combinator_class_chain` (line 759) `static void test_combinator_class_chain(void **state)`
- `test_adjacent_sibling_combinator` (line 778) `static void test_adjacent_sibling_combinator(void **state)` - *const char *nav[] = { "nav" }; const char *item[] = { "item" }; css_element navdiv = el_node("div", NULL, nav, 1, NULL); css_element li     = el_no...*
- `test_general_sibling_combinator` (line 793) `static void test_general_sibling_combinator(void **state)`
- `test_sibling_mixed_with_child` (line 808) `static void test_sibling_mixed_with_child(void **state)`
- `test_pseudo_link` (line 825) `static void test_pseudo_link(void **state)`
- `test_pseudo_never_match_keeps_group` (line 843) `static void test_pseudo_never_match_keeps_group(void **state)`
- `test_pseudo_structural` (line 862) `static void test_pseudo_structural(void **state)`
- `test_pseudo_nth_child` (line 882) `static void test_pseudo_nth_child(void **state)`
- `assert_int_equal` (line 886) `assert_int_equal(css_parse("tr:nth-child(even)`
- `test_pseudo_nth_last_child` (line 905) `static void test_pseudo_nth_last_child(void **state)`
- `assert_int_equal` (line 909) `assert_int_equal(css_parse("li:nth-last-child(2)`
- `test_pseudo_root_and_form_state` (line 916) `static void test_pseudo_root_and_form_state(void **state)`
- `test_pseudo_unknown_drops_selector` (line 940) `static void test_pseudo_unknown_drops_selector(void **state)`
- `test_pseudo_specificity` (line 962) `static void test_pseudo_specificity(void **state)`
- `test_pseudo_with_sibling_combinator` (line 980) `static void test_pseudo_with_sibling_combinator(void **state)`
- `test_pseudo_nth_malformed_drops` (line 997) `static void test_pseudo_nth_malformed_drops(void **state)`
- `assert_int_equal` (line 1003) `assert_int_equal(css_parse("li:nth-child()` - *Malformed or oversized An+B drops the selector (fail closed); partner rules * survive.*
- `test_resolve_el_inline_only` (line 1013) `static void test_resolve_el_inline_only(void **state)`
- `test_attr_presence` (line 1021) `static void test_attr_presence(void **state)` - *"li{background:#101010}", 0, &sh), CSS_OK); css_element li = el_sib_node("li", 1, 1, NULL, NULL); assert_int_equal(css_resolve_el(sh, &li, NULL, 0)...*
- `test_attr_equals` (line 1034) `static void test_attr_equals(void **state)`
- `test_attr_operators` (line 1052) `static void test_attr_operators(void **state)`
- `test_attr_case_insensitive_flag` (line 1084) `static void test_attr_case_insensitive_flag(void **state)`
- `test_attr_name_case_insensitive` (line 1099) `static void test_attr_name_case_insensitive(void **state)`
- `test_attr_quoted_value_with_space` (line 1110) `static void test_attr_quoted_value_with_space(void **state)`
- `test_attr_specificity_and_compound` (line 1124) `static void test_attr_specificity_and_compound(void **state)`
- `test_attr_in_combinator` (line 1141) `static void test_attr_in_combinator(void **state)`
- `test_attr_malformed_fail_closed` (line 1157) `static void test_attr_malformed_fail_closed(void **state)`
- `test_important_inline_not_dropped` (line 1175) `static void test_important_inline_not_dropped(void **state)` - *Unbalanced/empty/unknown-operator brackets drop only that selector; the plain * rule in the group survives. assert_int_equal(css_parse("input[ {col...*
- `test_important_beats_specificity` (line 1185) `static void test_important_beats_specificity(void **state)`
- `test_important_tier_then_normal_order` (line 1194) `static void test_important_tier_then_normal_order(void **state)`
- `test_important_inline_beats_sheet_important` (line 1204) `static void test_important_inline_beats_sheet_important(void **state)`
- `test_important_in_shorthand` (line 1216) `static void test_important_in_shorthand(void **state)`
- `test_cascade_specificity` (line 1233) `static void test_cascade_specificity(void **state)` - */* !important stamps every side a shorthand expands to. css_style s = css_parse_inline("margin:10px !important", 0); assert_int_equal(s.margin_top,...*
- `silent` (line 1250) `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past
 * the OLD cap...`
- `test_cascade_document_order` (line 1274) `static void test_cascade_document_order(void **state)`
- `test_cascade_inline_wins` (line 1283) `static void test_cascade_inline_wins(void **state)`
- `test_at_rules_skipped` (line 1292) `static void test_at_rules_skipped(void **state)`
- `test_media_screen_and_print` (line 1310) `static void test_media_screen_and_print(void **state)` - *@import is skipped entirely (no network). @media screen matches the default context, so its rule applies, then the later same-specificity plain rul...*
- `test_media_prefers_color_scheme` (line 1329) `static void test_media_prefers_color_scheme(void **state)` - *"@media print { p { color:#010101 } }", 0, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0xabcdef); css_free(...*
- `test_media_width_queries` (line 1345) `static void test_media_width_queries(void **state)` - *const char *css = "@media (prefers-color-scheme: dark) { body { color:#ffffff } }"; css_sheet *sh = NULL; assert_int_equal(css_parse(css, 0, &sh), ...*
- `assert_int_equal` (line 1348) `assert_int_equal(css_parse(
        "@media (min-width: 600px)`
- `test_media_and_or` (line 1360) `static void test_media_and_or(void **state)` - *(void)state; css_sheet *sh = NULL; assert_int_equal(css_parse( "@media (min-width: 600px) { p { color:#111111 } }\n" "@media (min-width: 3000px) { ...*
- `assert_int_equal` (line 1363) `assert_int_equal(css_parse(
        "@media screen and (min-width: 600px)`
- `test_media_unknown_fails_closed` (line 1374) `static void test_media_unknown_fails_closed(void **state)` - *static void test_media_and_or(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse( "@media screen and (min-width: 600px) ...*
- `assert_int_equal` (line 1377) `assert_int_equal(css_parse(
        "@media (hover: hover)`
- `test_parse_null_args` (line 1391) `static void test_parse_null_args(void **state)` - *assert_int_equal(css_parse( "@media (hover: hover) { p { color:#cccccc } }\n" "@media tv { a { color:#dddddd } }\n" "@media not screen { b { color:...*
- `test_resolve_null_safe` (line 1401) `static void test_resolve_null_safe(void **state)`
- `test_inline_box_longhands` (line 1415) `static void test_inline_box_longhands(void **state)` - *static void test_resolve_null_safe(void **state) { (void)state; /* NULL sheet and NULL tag are safe; everything unset. css_style s = css_resolve(NU...*
- `test_box_shorthand_expansion` (line 1433) `static void test_box_shorthand_expansion(void **state)`
- `test_box_auto_and_centering` (line 1461) `static void test_box_auto_and_centering(void **state)`
- `test_box_units_and_failclosed` (line 1478) `static void test_box_units_and_failclosed(void **state)`
- `test_width_percent_carried_symbolically` (line 1506) `static void test_width_percent_carried_symbolically(void **state)` - *Hito 32: width/max-width percentages are carried SYMBOLICALLY (per-mille in width_pct/max_width_pct; the px channel stays UNSET) and resolved at la...*
- `test_calc_basic_arithmetic` (line 1533) `static void test_calc_basic_arithmetic(void **state)`
- `test_calc_precedence_and_parens` (line 1542) `static void test_calc_precedence_and_parens(void **state)`
- `test_calc_units_and_signs` (line 1549) `static void test_calc_units_and_signs(void **state)`
- `test_calc_dimension_errors_fail_closed` (line 1557) `static void test_calc_dimension_errors_fail_closed(void **state)`
- `test_calc_clamped_anti_dos` (line 1572) `static void test_calc_clamped_anti_dos(void **state)`
- `test_calc_inside_shorthands` (line 1583) `static void test_calc_inside_shorthands(void **state)` - *calc() must survive being ONE token inside a multi-value shorthand: a naive whitespace splitter would break "calc(10px + 5px)" apart at the interna...*
- `test_calc_with_custom_property` (line 1620) `static void test_calc_with_custom_property(void **state)`
- `test_box_clamp_anti_dos` (line 1627) `static void test_box_clamp_anti_dos(void **state)`
- `test_inline_min_width_height` (line 1636) `static void test_inline_min_width_height(void **state)` - *(void)state; /* calc() and var() compose: var() substitutes text before calc() is parsed. css_style s = css_parse_inline("--base: 20px; width: calc...*
- `test_inline_min_max_height` (line 1663) `static void test_inline_min_max_height(void **state)`
- `test_box_extension_sheet_cascade` (line 1677) `static void test_box_extension_sheet_cascade(void **state)`
- `test_inline_text_decoration_color_style` (line 1697) `static void test_inline_text_decoration_color_style(void **state)` - *"#s { height:400px }", 0, &sh), CSS_OK); const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, NULL, 0); assert_int_eq...*
- `test_inline_text_decoration_thickness` (line 1726) `static void test_inline_text_decoration_thickness(void **state)` - */* All style keywords. assert_int_equal(css_parse_inline("text-decoration-style:solid", 0).text_decoration_style, CSS_TDS_SOLID); assert_int_equal(...*
- `test_inline_aspect_ratio` (line 1743) `static void test_inline_aspect_ratio(void **state)` - */* from-font -> 0 (the painter treats 0 as "default thickness" via cairo). assert_int_equal(css_parse_inline("text-decoration-thickness:from-font",...*
- `test_inline_direction` (line 1773) `static void test_inline_direction(void **state)` - *css_style d = css_parse_inline("aspect-ratio:auto", 0); assert_int_equal(d.aspect_num, 0); assert_int_equal(d.aspect_den, 0); /* Bad value -> 0/0 (...*
- `test_inline_outline_offset` (line 1782) `static void test_inline_outline_offset(void **state)` - *assert_int_equal(def.aspect_num, 0); assert_int_equal(def.aspect_den, 0); } /* --- direction --- static void test_inline_direction(void **state) { ...*
- `test_inline_tab_size` (line 1794) `static void test_inline_tab_size(void **state)` - */* --- outline-offset --- static void test_inline_outline_offset(void **state) { (void)state; assert_int_equal(css_parse_inline("outline-offset:2px...*
- `test_box_sheet_cascade_inline_wins` (line 1804) `static void test_box_sheet_cascade_inline_wins(void **state)`
- `test_position_and_insets` (line 1819) `static void test_position_and_insets(void **state)` - *static void test_box_sheet_cascade_inline_wins(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse(".card{max-width:600px...*
- `test_float_and_clear` (line 1850) `static void test_float_and_clear(void **state)`
- `test_visibility` (line 1874) `static void test_visibility(void **state)`
- `test_overflow` (line 1891) `static void test_overflow(void **state)`
- `test_cursor` (line 1914) `static void test_cursor(void **state)`
- `test_text_overflow_and_word_break` (line 1930) `static void test_text_overflow_and_word_break(void **state)`
- `test_box_sizing` (line 1955) `static void test_box_sizing(void **state)`
- `test_border_shorthand` (line 1963) `static void test_border_shorthand(void **state)`
- `test_border_longhands` (line 1993) `static void test_border_longhands(void **state)`
- `test_box_shadow_and_outline` (line 2019) `static void test_box_shadow_and_outline(void **state)`
- `test_flex_item` (line 2044) `static void test_flex_item(void **state)`
- `test_flex_align` (line 2073) `static void test_flex_align(void **state)`
- `test_grid_extras` (line 2095) `static void test_grid_extras(void **state)`
- `test_layout_sheet_cascade_and_unset` (line 2113) `static void test_layout_sheet_cascade_and_unset(void **state)`
- `test_inline_outline_longhands` (line 2150) `static void test_inline_outline_longhands(void **state)` - *const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, "z-index:9", 0); assert_int_equal(s.position, CSS_POS_ABSOLUTE);...*
- `test_inline_border_collapse` (line 2181) `static void test_inline_border_collapse(void **state)` - *assert_int_equal(css_parse_inline("outline-style:none", 0).outline_style, CSS_BST_NONE); assert_int_equal(css_parse_inline("outline-style:ridge", 0...*
- `test_inline_border_spacing` (line 2190) `static void test_inline_border_spacing(void **state)` - *assert_int_equal(css_parse_inline("outline-color:auto", 0).outline_color, -1); /* dropped assert_int_equal(css_parse_inline("color:red", 0).outline...*
- `test_inline_empty_cells` (line 2201) `static void test_inline_empty_cells(void **state)` - *} /* --- border-spacing --- static void test_inline_border_spacing(void **state) { (void)state; assert_int_equal(css_parse_inline("border-spacing:2...*
- `test_inline_caption_side` (line 2210) `static void test_inline_caption_side(void **state)` - *assert_int_equal(css_parse_inline("border-spacing:auto", 0).border_spacing, CSS_LEN_UNSET); /* dropped assert_int_equal(css_parse_inline("color:red...*
- `test_inline_table_layout` (line 2219) `static void test_inline_table_layout(void **state)` - *assert_int_equal(css_parse_inline("empty-cells:auto", 0).empty_cells, CSS_EC_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).e...*
- `test_inline_font_variant` (line 2228) `static void test_inline_font_variant(void **state)` - *assert_int_equal(css_parse_inline("caption-side:left", 0).caption_side, CSS_CS_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0)...*
- `test_inline_hyphens` (line 2237) `static void test_inline_hyphens(void **state)` - *assert_int_equal(css_parse_inline("table-layout:collapse", 0).table_layout, CSS_TL_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red"...*
- `test_inline_user_select` (line 2247) `static void test_inline_user_select(void **state)` - *assert_int_equal(css_parse_inline("color:red", 0).font_variant, CSS_FV_UNSET); } /* --- hyphens --- static void test_inline_hyphens(void **state) {...*
- `test_inline_caret_color` (line 2258) `static void test_inline_caret_color(void **state)` - *} /* --- user-select --- static void test_inline_user_select(void **state) { (void)state; assert_int_equal(css_parse_inline("user-select:none", 0)....*
- `test_inline_appearance` (line 2268) `static void test_inline_appearance(void **state)` - *assert_int_equal(css_parse_inline("color:red", 0).user_select, CSS_US_UNSET); } /* --- caret-color --- static void test_inline_caret_color(void **s...*
- `test_inline_pointer_events` (line 2277) `static void test_inline_pointer_events(void **state)` - *assert_int_equal(css_parse_inline("caret-color:blargh", 0).caret_color, -1); /* unknown -> unset assert_int_equal(css_parse_inline("color:red", 0)....*
- `test_table_sheet_cascade` (line 2286) `static void test_table_sheet_cascade(void **state)` - *assert_int_equal(css_parse_inline("appearance:button", 0).appearance, CSS_AP_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).a...*
- `test_inline_bg_repeat` (line 2301) `static void test_inline_bg_repeat(void **state)` - *(void)state; css_sheet *sh = NULL; assert_int_equal(css_parse("table{border-collapse:collapse;empty-cells:hide;caption-side:bottom;table-layout:fix...*
- `test_inline_bg_size` (line 2312) `static void test_inline_bg_size(void **state)`
- `test_inline_bg_clip_origin_attachment` (line 2321) `static void test_inline_bg_clip_origin_attachment(void **state)`
- `test_inline_isolation` (line 2341) `static void test_inline_isolation(void **state)`
- `test_inline_contain` (line 2349) `static void test_inline_contain(void **state)`
- `test_inline_content_visibility` (line 2364) `static void test_inline_content_visibility(void **state)`
- `test_inline_image_rendering` (line 2373) `static void test_inline_image_rendering(void **state)`
- `test_inline_color_scheme` (line 2382) `static void test_inline_color_scheme(void **state)`
- `test_inline_accent_color` (line 2392) `static void test_inline_accent_color(void **state)`
- `test_inline_print_forced_adjust` (line 2401) `static void test_inline_print_forced_adjust(void **state)`
- `test_inline_mix_blend_mode` (line 2415) `static void test_inline_mix_blend_mode(void **state)` - *static void test_inline_print_forced_adjust(void **state) { (void)state; assert_int_equal(css_parse_inline("print-color-adjust:economy", 0).print_c...*
- `test_inline_object_fit` (line 2435) `static void test_inline_object_fit(void **state)`
- `test_inline_list_style_pos` (line 2446) `static void test_inline_list_style_pos(void **state)`
- `test_inline_font_kerning` (line 2454) `static void test_inline_font_kerning(void **state)`
- `test_inline_text_rendering` (line 2463) `static void test_inline_text_rendering(void **state)`
- `test_inline_font_stretch` (line 2473) `static void test_inline_font_stretch(void **state)`
- `test_inline_resize` (line 2488) `static void test_inline_resize(void **state)`
- `test_inline_scroll_behavior` (line 2498) `static void test_inline_scroll_behavior(void **state)`
- `test_inline_touch_action` (line 2506) `static void test_inline_touch_action(void **state)`
- `test_inline_overscroll_behavior` (line 2515) `static void test_inline_overscroll_behavior(void **state)`
- `test_inline_backface_visibility` (line 2524) `static void test_inline_backface_visibility(void **state)`
- `test_math_min_max_top_level` (line 2534) `static void test_math_min_max_top_level(void **state)` - *assert_int_equal(css_parse_inline("overscroll-behavior:none", 0).overscroll_behavior, CSS_OS_NONE); assert_int_equal(css_parse_inline("overscroll-b...*
- `test_math_clamp` (line 2545) `static void test_math_clamp(void **state)`
- `test_math_nested_in_calc` (line 2555) `static void test_math_nested_in_calc(void **state)`
- `test_logical_margin_padding` (line 2570) `static void test_logical_margin_padding(void **state)` - *static void test_math_nested_in_calc(void **state) { (void)state; assert_int_equal(css_parse_inline("width:calc(min(10px, 2em) * 2)", 0).width, 20)...*
- `test_logical_inset_and_sizes` (line 2595) `static void test_logical_inset_and_sizes(void **state)`
- `test_place_shorthands` (line 2618) `static void test_place_shorthands(void **state)` - *assert_int_equal(s.inset_left, 1); assert_int_equal(s.inset_bottom, 2); s = css_parse_inline("inline-size:200px; block-size:100px", 0); assert_int_...*
- `test_gap_two_value` (line 2640) `static void test_gap_two_value(void **state)`
- `test_font_shorthand` (line 2658) `static void test_font_shorthand(void **state)` - *assert_int_equal(s.row_gap, 10); assert_int_equal(s.gap, 20); s = css_parse_inline("gap:12px", 0); assert_int_equal(s.gap, 12); assert_int_equal(s....*
- `test_white_space_break_spaces` (line 2680) `static void test_white_space_break_spaces(void **state)` - *s = css_parse_inline("font:16px sans-serif", 0); assert_int_equal(s.font_scale, 100); assert_int_equal(s.font_family, CSS_FF_SANS); assert_int_equa...*
- `main` (line 2684) `int main(void)`

#### `test_css_color.c`
**Path:** `tests/test_css_color.c`

**Functions:**
- `test_null_args` (line 21) `static void test_null_args(void **state)`
- `test_hex_short` (line 27) `static void test_hex_short(void **state)`
- `test_hex_short_alpha` (line 36) `static void test_hex_short_alpha(void **state)`
- `test_hex_long` (line 43) `static void test_hex_long(void **state)`
- `test_hex_long_alpha` (line 52) `static void test_hex_long_alpha(void **state)`
- `test_hex_bad` (line 58) `static void test_hex_bad(void **state)`
- `test_rgb_integer` (line 67) `static void test_rgb_integer(void **state)`
- `test_rgba_integer` (line 76) `static void test_rgba_integer(void **state)`
- `test_rgb_percent` (line 83) `static void test_rgb_percent(void **state)`
- `test_rgb_out_of_range` (line 89) `static void test_rgb_out_of_range(void **state)`
- `test_named` (line 99) `static void test_named(void **state)`
- `test_named_bad` (line 117) `static void test_named_bad(void **state)`
- `test_unsupported_syntax` (line 126) `static void test_unsupported_syntax(void **state)`
- `test_pack_unpack` (line 133) `static void test_pack_unpack(void **state)`
- `main` (line 147) `int main(void)`

#### `test_disk_store.c`
**Path:** `tests/test_disk_store.c`

**Functions:**
- `setup` (line 34) `static int setup(void **state)`
- `teardown` (line 44) `static int teardown(void **state)`
- `count_dir_entries` (line 64) `static size_t count_dir_entries(const char *dir)`
- `test_roundtrip` (line 77) `static void test_roundtrip(void **state)`
- `test_roundtrip_chacha` (line 88) `static void test_roundtrip_chacha(void **state)`
- `test_empty` (line 98) `static void test_empty(void **state)`
- `test_permissions` (line 107) `static void test_permissions(void **state)`
- `test_no_temp_left` (line 116) `static void test_no_temp_left(void **state)`
- `test_overwrite` (line 123) `static void test_overwrite(void **state)`
- `test_wrong_key` (line 137) `static void test_wrong_key(void **state)`
- `test_tamper_on_disk` (line 149) `static void test_tamper_on_disk(void **state)`
- `test_missing_and_null` (line 167) `static void test_missing_and_null(void **state)`
- `main` (line 180) `int main(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 7)

**Structs:**
- `fixture` (line 33)

#### `test_dom.c`
**Path:** `tests/test_dom.c`

**Functions:**
- `setup_doc` (line 32) `static int setup_doc(void **state)` - *#include "dom.h" #include "html_parse.h" static const char HTML[] = "<!DOCTYPE html><html><head><title>T</title></head>" "<body>" "<div id=\"main\"...*
- `teardown_doc` (line 44) `static int teardown_doc(void **state)`
- `test_build_null_args` (line 59) `static void test_build_null_args(void **state)` - *static int teardown_doc(void **state) { void **pair = (void **)*state; if (pair != NULL) { dom_free((dom_index *)pair[1]); hp_document_free((hp_doc...*
- `test_free_null_and_double` (line 69) `static void test_free_null_and_double(void **state)`
- `test_node_count` (line 80) `static void test_node_count(void **state)`
- `test_get_by_id` (line 87) `static void test_get_by_id(void **state)` - *hp_document *doc = NULL; assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK); dom_index *idx = NULL; assert_int_equal(dom_build(do...*
- `test_get_by_id_absent` (line 101) `static void test_get_by_id_absent(void **state)`
- `test_by_class` (line 108) `static void test_by_class(void **state)` - *assert_non_null(tag); assert_string_equal(tag, "div"); dom_node_id go = dom_get_element_by_id(idx, "go"); assert_int_not_equal(go, DOM_NODE_NONE); ...*
- `test_by_tag` (line 117) `static void test_by_tag(void **state)`
- `test_by_tag_results_in_document_order` (line 126) `static void test_by_tag_results_in_document_order(void **state)`
- `test_document_order` (line 136) `static void test_document_order(void **state)` - *assert_int_equal(dom_get_by_tag(idx, "P", buf, 8), 2); /* case-insensitive assert_int_equal(dom_get_by_tag(idx, "button", buf, 8), 1); assert_int_e...*
- `test_navigation` (line 150) `static void test_navigation(void **state)` - *static void test_document_order(void **state) { dom_index *idx = IDX(state); dom_node_id main_id = dom_get_element_by_id(idx, "main"); dom_node_id ...*
- `test_attributes` (line 170) `static void test_attributes(void **state)` - *assert_int_not_equal(p1, DOM_NODE_NONE); assert_string_equal(dom_tag_name(idx, p1, NULL), "p"); dom_node_id p2 = dom_next_sibling(idx, p1); assert_...*
- `test_text_content_read` (line 184) `static void test_text_content_read(void **state)` - *static void test_attributes(void **state) { dom_index *idx = IDX(state); dom_node_id main_id = dom_get_element_by_id(idx, "main"); size_t len = 0; ...*
- `test_set_text_content_changes_tree` (line 195) `static void test_set_text_content_changes_tree(void **state)`
- `test_set_text_content_empty_clears` (line 213) `static void test_set_text_content_empty_clears(void **state)`
- `test_set_text_content_invalid_node` (line 223) `static void test_set_text_content_invalid_node(void **state)`
- `test_set_and_get_document_title` (line 228) `static void test_set_and_get_document_title(void **state)`
- `test_create_and_append` (line 240) `static void test_create_and_append(void **state)`
- `test_append_rejects_cycle` (line 258) `static void test_append_rejects_cycle(void **state)`
- `test_remove_child` (line 268) `static void test_remove_child(void **state)`
- `test_set_attribute_reindexes_id` (line 280) `static void test_set_attribute_reindexes_id(void **state)`
- `test_remove_attribute` (line 293) `static void test_remove_attribute(void **state)`
- `test_set_inner_html` (line 310) `static void test_set_inner_html(void **state)`
- `test_construction_invalid_args` (line 326) `static void test_construction_invalid_args(void **state)`
- `test_get_inner_html` (line 334) `static void test_get_inner_html(void **state)`
- `test_query_selector_type_class_id` (line 362) `static void test_query_selector_type_class_id(void **state)` - *Fixture tree (inside body): div#main.container.box > [ p.text "Hello", * p.text.muted "World", button#go.btn "Go" ].*
- `test_query_selector_all_counts` (line 376) `static void test_query_selector_all_counts(void **state)`
- `test_query_selector_combinators` (line 387) `static void test_query_selector_combinators(void **state)`
- `test_query_selector_nth_and_structural` (line 400) `static void test_query_selector_nth_and_structural(void **state)`
- `test_query_selector_scope_is_descendants_only` (line 413) `static void test_query_selector_scope_is_descendants_only(void **state)`
- `test_matches_and_closest` (line 425) `static void test_matches_and_closest(void **state)`
- `test_query_selector_fail_closed` (line 438) `static void test_query_selector_fail_closed(void **state)`
- `main` (line 454) `int main(void)`

**Macros:**
- `DOC` (line 54)
- `IDX` (line 56)

#### `test_dom_debug.c`
**Path:** `tests/test_dom_debug.c`

**Functions:**
- `caps_css_on` (line 28) `static rdp_caps caps_css_on(void)`
- `build` (line 36) `static rd_doc *build(pv_view *v, rdp_caps caps)` - *#include "dom_debug.h" #include "page_view.h" #include "render_doc.h" #include "render_policy.h" static const char TOP[] = "https://example.com/"; ...*
- `test_null_doc_is_empty_header` (line 44) `static void test_null_doc_is_empty_header(void **state)` - *rdp_caps c = rdp_caps_safe(); c.css = true;          /* box tree + author box/style fields only with caps.css return c; } /* Builds an rd_doc from ...*
- `test_heading_paragraph_link` (line 58) `static void test_heading_paragraph_link(void **state)` - *static void test_null_doc_is_empty_header(void **state) { (void)state; char buf[256]; size_t n = dd_format(NULL, buf, sizeof buf); assert_true(n > ...*
- `test_grid_container_annotation` (line 91) `static void test_grid_container_annotation(void **state)` - *-- a grid container (a table) annotates its cells: the field that reveals a *     collapsed table column ---*
- `test_box_tree_width_cap` (line 115) `static void test_box_tree_width_cap(void **state)` - *char buf[1024]; size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf); assert_non_null(strstr(buf, "containers: 1")); /* one distin...*
- `test_visibility_overflow_cursor_and_text_wrap` (line 153) `static void test_visibility_overflow_cursor_and_text_wrap(void **state)` - *size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf); assert_non_null(strstr(buf, "boxes: 1")); assert_non_null(strstr(buf, "[boxe...*
- `test_no_box_tree_without_css` (line 196) `static void test_no_box_tree_without_css(void **state)` - *size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf); assert_non_null(strstr(buf, "visibility=hidden")); assert_non_null(strstr(bu...*
- `test_truncation_no_overflow` (line 216) `static void test_truncation_no_overflow(void **state)` - *pv_box_def b; memset(&b, 0, sizeof b); b.parent_id = -1; b.bsh_color = -1; assert_int_equal(pv_add_box_def(v, &b), PV_OK); rd_doc *d = build(v, rdp...*
- `test_control_bytes_kept_on_one_line` (line 244) `static void test_control_bytes_kept_on_one_line(void **state)` - *size_t n = dd_format(d, (char *)guard, cap); assert_int_equal((int)n, (int)full);          /* reports the untruncated length /* NUL within the cap ...*
- `main` (line 268) `int main(void)`

#### `test_download.c`
**Path:** `tests/test_download.c`

**Functions:**
- `builder` (line 8) `* builder (join, separator rejection, overflow, NULL), and the size cap.
 */

#include <setjmp.h>...`
- `test_should_renderable_types` (line 29) `static void test_should_renderable_types(void **state)`
- `test_should_binary_types` (line 40) `static void test_should_binary_types(void **state)`
- `test_ext_known_types` (line 51) `static void test_ext_known_types(void **state)` - *assert_int_equal(dl_should_download(NULL, NULL), 0);          /* missing type renders assert_int_equal(dl_should_download("", NULL), 0); } static v...*
- `test_ext_unknown_type` (line 62) `static void test_ext_unknown_type(void **state)`
- `test_pick_from_disposition_quoted` (line 71) `static void test_pick_from_disposition_quoted(void **state)` - *assert_string_equal(dl_ext_for_type("text/plain; charset=utf-8"), ".txt"); assert_string_equal(dl_ext_for_type("IMAGE/JPEG"), ".jpg"); assert_strin...*
- `test_pick_from_disposition_ext_form` (line 80) `static void test_pick_from_disposition_ext_form(void **state)`
- `test_pick_from_url_segment` (line 90) `static void test_pick_from_url_segment(void **state)`
- `test_pick_appends_extension_when_missing` (line 98) `static void test_pick_appends_extension_when_missing(void **state)`
- `test_pick_keeps_existing_extension` (line 107) `static void test_pick_keeps_existing_extension(void **state)`
- `test_pick_traversal_contained` (line 116) `static void test_pick_traversal_contained(void **state)`
- `test_pick_fallback_when_empty` (line 128) `static void test_pick_fallback_when_empty(void **state)`
- `test_pick_null_out` (line 140) `static void test_pick_null_out(void **state)`
- `test_pick_overflow_fails_closed` (line 147) `static void test_pick_overflow_fails_closed(void **state)`
- `test_build_path_basic` (line 157) `static void test_build_path_basic(void **state)` - *char out[8]; assert_int_equal(dl_pick_name("https://x/y.pdf", NULL, NULL, NULL, sizeof out), DL_ERR_NULL_ARG); assert_int_equal(dl_pick_name("https...*
- `test_build_path_trailing_slash` (line 164) `static void test_build_path_trailing_slash(void **state)`
- `test_build_path_rejects_separator_in_name` (line 171) `static void test_build_path_rejects_separator_in_name(void **state)`
- `test_build_path_overflow` (line 178) `static void test_build_path_overflow(void **state)`
- `test_build_path_null_args` (line 185) `static void test_build_path_null_args(void **state)`
- `test_check_size` (line 196) `static void test_check_size(void **state)` - *assert_int_equal(dl_build_path("/a/very/long/dir", "name.pdf", out, sizeof out), DL_ERR_OVERFLOW); assert_string_equal(out, ""); } static void test...*
- `main` (line 203) `int main(void)`

#### `test_flex_layout.c`
**Path:** `tests/test_flex_layout.c`

**Functions:**
- `assert_item` (line 24) `static void assert_item(fx_result r, double pos, double size)`
- `test_grow_equal` (line 29) `static void test_grow_equal(void **state)`
- `test_grow_weighted` (line 38) `static void test_grow_weighted(void **state)`
- `test_shrink_equal` (line 47) `static void test_shrink_equal(void **state)`
- `test_shrink_with_min_clamp` (line 56) `static void test_shrink_with_min_clamp(void **state)`
- `test_gap_start` (line 66) `static void test_gap_start(void **state)`
- `test_justify_center` (line 75) `static void test_justify_center(void **state)`
- `test_justify_end` (line 84) `static void test_justify_end(void **state)`
- `test_justify_space_between` (line 93) `static void test_justify_space_between(void **state)`
- `test_justify_space_around` (line 102) `static void test_justify_space_around(void **state)`
- `test_justify_space_evenly` (line 111) `static void test_justify_space_evenly(void **state)`
- `test_space_between_single_item_is_start` (line 121) `static void test_space_between_single_item_is_start(void **state)`
- `test_negative_fields_clamped` (line 129) `static void test_negative_fields_clamped(void **state)`
- `test_flex_zero_items_is_noop` (line 139) `static void test_flex_zero_items_is_noop(void **state)`
- `test_flex_errors` (line 144) `static void test_flex_errors(void **state)`
- `test_grid_columns` (line 156) `static void test_grid_columns(void **state)`
- `test_grid_columns_too_narrow_clamps_to_zero` (line 168) `static void test_grid_columns_too_narrow_clamps_to_zero(void **state)`
- `test_grid_columns_edges` (line 175) `static void test_grid_columns_edges(void **state)`
- `test_grid_cell` (line 185) `static void test_grid_cell(void **state)`
- `test_grid_weighted_fr` (line 196) `static void test_grid_weighted_fr(void **state)` - *assert_int_equal(fx_grid_columns(320, (size_t)FX_MAX_ITEMS + 1, 10, x, w), FX_ERR_RANGE); assert_int_equal(fx_grid_columns(320, 2, 10, NULL, w), FX...*
- `test_grid_weighted_fixed_px_reserved_first` (line 208) `static void test_grid_weighted_fixed_px_reserved_first(void **state)`
- `test_grid_weighted_all_auto_matches_equal` (line 220) `static void test_grid_weighted_all_auto_matches_equal(void **state)`
- `test_grid_weighted_fixed_overflow_zeroes_fr` (line 233) `static void test_grid_weighted_fixed_overflow_zeroes_fr(void **state)`
- `test_grid_weighted_errors` (line 243) `static void test_grid_weighted_errors(void **state)`
- `test_grid_place_span_basic` (line 253) `static void test_grid_place_span_basic(void **state)`
- `test_grid_place_span_wraps_when_it_does_not_fit` (line 264) `static void test_grid_place_span_wraps_when_it_does_not_fit(void **state)`
- `test_grid_place_span_clamps_and_defaults` (line 276) `static void test_grid_place_span_clamps_and_defaults(void **state)`
- `test_float_pack_left` (line 292) `static void test_float_pack_left(void **state)`
- `test_float_pack_left_and_right` (line 303) `static void test_float_pack_left_and_right(void **state)`
- `test_float_pack_two_right` (line 315) `static void test_float_pack_two_right(void **state)`
- `test_float_pack_edges` (line 326) `static void test_float_pack_edges(void **state)`
- `test_float_pack_wrap_full_width_stack` (line 343) `static void test_float_pack_wrap_full_width_stack(void **state)` - *Hito 32 (band wrap): two consecutive full-width floats (Slashdot's .grid_24 { width:99.8% }) must STACK -- one per row at x = 0 -- instead of * bei...*
- `test_float_pack_wrap_fits_matches_v1` (line 357) `static void test_float_pack_wrap_fits_matches_v1(void **state)` - *static void test_float_pack_wrap_full_width_stack(void **state) { (void)state; double w[3] = { 998.0, 998.0, 998.0 }; int side[3] = { 0, 0, 0 }; do...*
- `test_float_pack_wrap_partial` (line 380) `static void test_float_pack_wrap_partial(void **state)` - *assert_int_equal((int)row[i], 0); assert_true(dbl_eq(x[i], xv1[i])); } /* Left main + right sidebar share row 0 exactly like v1. double w2[2] = { 3...*
- `test_float_pack_wrap_errors` (line 402) `static void test_float_pack_wrap_errors(void **state)`
- `test_justify_name` (line 411) `static void test_justify_name(void **state)`
- `main` (line 422) `int main(void)`

#### `test_form.c`
**Path:** `tests/test_form.c`

**Functions:**
- `test_encode_basic` (line 23) `static void test_encode_basic(void **state)` - *NULL name, NULL args).  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #in...*
- `test_encode_space_and_reserved` (line 33) `static void test_encode_space_and_reserved(void **state)`
- `test_encode_unreserved_kept` (line 42) `static void test_encode_unreserved_kept(void **state)`
- `test_encode_empty_and_nameless` (line 50) `static void test_encode_empty_and_nameless(void **state)`
- `test_encode_overflow_fails_closed` (line 58) `static void test_encode_overflow_fails_closed(void **state)`
- `test_encode_null_args` (line 66) `static void test_encode_null_args(void **state)`
- `test_get_relative_action_on_https_base` (line 77) `static void test_get_relative_action_on_https_base(void **state)` - *assert_int_equal(fm_encode(f, 1, out, sizeof out, NULL), FM_ERR_OVERFLOW); assert_string_equal(out, ""); /* no partial encoding } static void test_...*
- `test_get_absolute_https_action_ignores_base` (line 88) `static void test_get_absolute_https_action_ignores_base(void **state)`
- `test_get_empty_action_submits_to_base` (line 99) `static void test_get_empty_action_submits_to_base(void **state)`
- `test_get_replaces_existing_query` (line 108) `static void test_get_replaces_existing_query(void **state)`
- `test_get_action_cleaned_of_whitespace` (line 118) `static void test_get_action_cleaned_of_whitespace(void **state)`
- `test_post_builds_body` (line 129) `static void test_post_builds_body(void **state)` - *assert_int_equal(p.kind, FM_NAVIGATE); assert_string_equal(p.url, "https://example.com/s?q=new"); } static void test_get_action_cleaned_of_whitespa...*
- `test_block_http_downgrade` (line 144) `static void test_block_http_downgrade(void **state)` - *static void test_post_builds_body(void **state) { (void)state; fm_field f[] = { { "user", "a b" }, { "pass", "p&q" } }; fm_plan p; assert_int_equal...*
- `test_block_foreign_scheme` (line 154) `static void test_block_foreign_scheme(void **state)`
- `test_block_relative_action_on_local_base` (line 163) `static void test_block_relative_action_on_local_base(void **state)`
- `test_block_too_many_fields` (line 172) `static void test_block_too_many_fields(void **state)`
- `test_block_null_field_name` (line 182) `static void test_block_null_field_name(void **state)`
- `test_build_null_args` (line 191) `static void test_build_null_args(void **state)`
- `test_get_no_fields_still_navigates` (line 198) `static void test_get_no_fields_still_navigates(void **state)`
- `main` (line 206) `int main(void)`

#### `test_freebug.c`
**Path:** `tests/test_freebug.c`

**Functions:**
- `test_push_and_read` (line 20) `static void test_push_and_read(void **state)` - *include "freebug.h"*
- `test_empty_and_null_text` (line 45) `static void test_empty_and_null_text(void **state)`
- `test_count_cap_fails_closed` (line 58) `static void test_count_cap_fails_closed(void **state)`
- `test_entry_truncated_not_dropped` (line 74) `static void test_entry_truncated_not_dropped(void **state)`
- `test_total_bytes_cap_fails_closed` (line 92) `static void test_total_bytes_cap_fails_closed(void **state)`
- `test_level_clamped` (line 117) `static void test_level_clamped(void **state)`
- `test_level_name` (line 128) `static void test_level_name(void **state)`
- `test_reset_reuses_and_no_leak` (line 139) `static void test_reset_reuses_and_no_leak(void **state)`
- `test_free_idempotent` (line 160) `static void test_free_idempotent(void **state)`
- `test_push_loc_records_location` (line 174) `static void test_push_loc_records_location(void **state)`
- `test_push_loc_null_file_and_negative_nums` (line 196) `static void test_push_loc_null_file_and_negative_nums(void **state)`
- `test_push_loc_file_truncated` (line 213) `static void test_push_loc_file_truncated(void **state)`
- `main` (line 227) `int main(void)`

#### `test_freedom.c`
**Path:** `tests/test_freedom.c`

**Functions:**
- `run_freedom` (line 27) `static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status)` - *define FREEDOM_BIN "./build/freedom" define OUT_FILE    "__freedom_test_out.txt" define ERR_FILE    "__freedom_test_err.txt"*
- `run_freedom_raw` (line 50) `static int run_freedom_raw(const char *args, int *exit_status)` - *Runs the binary with a raw argument string (no implicit --headless), capturing * stdout into OUT_FILE. Used by the --download-pdf tests, which set ...*
- `is_pdf_file` (line 62) `static int is_pdf_file(const char *path)` - *Runs the binary with a raw argument string (no implicit --headless), capturing * stdout into OUT_FILE. Used by the --download-pdf tests, which set ...*
- `is_png_file` (line 72) `static int is_png_file(const char *path)` - *return 0; } /* True if path exists and its first bytes are the PDF magic "%PDF". static int is_pdf_file(const char *path) { FILE *f = fopen(path, "...*
- `cleanup_files` (line 81) `static void cleanup_files(void)`
- `test_help` (line 88) `static void test_help(void **state)` - *if (f == NULL) return 0; unsigned char magic[8] = {0}; size_t got = fread(magic, 1, 8, f); fclose(f); static const unsigned char png_sig[8] = {0x89...*
- `test_version` (line 97) `static void test_version(void **state)`
- `test_no_args` (line 106) `static void test_no_args(void **state)`
- `test_local_html` (line 116) `static void test_local_html(void **state)` - *assert_int_equal(run_freedom("--version", out, sizeof out, &rc), 0); assert_int_equal(rc, 0); assert_non_null(strstr(out, "Freedom")); } static voi...*
- `test_local_form_renders_inputs` (line 139) `static void test_local_form_renders_inputs(void **state)`
- `test_missing_file` (line 165) `static void test_missing_file(void **state)`
- `test_download_pdf_local` (line 175) `static void test_download_pdf_local(void **state)` - *assert_null(strstr(out, "[hidden"));              /* ...nor is the hidden control unlink(path); } static void test_missing_file(void **state) { (vo...*
- `test_download_pdf_requires_path` (line 202) `static void test_download_pdf_requires_path(void **state)` - *char args[512]; assert_true((size_t)snprintf(args, sizeof args, "--download-pdf=%s %s", pdf, path) < sizeof args); int rc = -1; assert_int_equal(ru...*
- `test_download_png_local` (line 210) `static void test_download_png_local(void **state)` - *unlink(path); unlink(pdf); } /* --download-pdf with no PATH is a usage error (fail closed: never guess a path). static void test_download_pdf_requi...*
- `test_download_png_requires_path` (line 237) `static void test_download_png_requires_path(void **state)` - *char args[512]; assert_true((size_t)snprintf(args, sizeof args, "--download-png=%s %s", png, path) < sizeof args); int rc = -1; assert_int_equal(ru...*
- `test_dump_console_shows_output_and_error` (line 247) `static void test_dump_console_shows_output_and_error(void **state)` - *unlink(png); } /* --download-png with no PATH is a usage error (fail closed: never guess a path). static void test_download_png_requires_path(void ...*
- `test_no_dump_console_without_flag` (line 282) `static void test_no_dump_console_without_flag(void **state)` - *size_t got = fread(out, 1, sizeof out - 1, o); out[got] = '\0'; fclose(o); assert_non_null(strstr(out, "Freebug console")); assert_non_null(strstr(...*
- `test_dump_dom_prints_render_tree` (line 307) `static void test_dump_dom_prints_render_tree(void **state)` - *-dump-dom prints the agent-readable render tree (header + per-block lines) instead * of the normal text render, and does not run JS.*
- `ballooned` (line 340) `* ballooned (body + wrapper re-opened per child) and the LAST wrapper piece
 * became the contain...`
- `test_rejects_http_url` (line 456) `static void test_rejects_http_url(void **state)` - *The relative panel is in flow: at least one box, and no positioned box left it * at the page bottom (the grey-stripe bug had npositioned pushing it...*
- `main` (line 466) `int main(void)` - *unlink(path); } /* --- network policy --- static void test_rejects_http_url(void **state) { (void)state; char out[512]; int rc; assert_int_equal(ru...*

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `FREEDOM_BIN` (line 23)
- `OUT_FILE` (line 25)
- `ERR_FILE` (line 26)

#### `test_hostblock.c`
**Path:** `tests/test_hostblock.c`

**Functions:**
- `test_free_null_idempotent` (line 31) `static void test_free_null_idempotent(void **state)`
- `test_count_null_set` (line 36) `static void test_count_null_set(void **state)`
- `test_load_null_args` (line 44) `static void test_load_null_args(void **state)` - *} static void test_free_null_idempotent(void **state) { (void)state; hb_free(NULL);  /* must not crash } static void test_count_null_set(void **sta...*
- `test_hosts_line_drops_ip` (line 54) `static void test_hosts_line_drops_ip(void **state)` - *assert_int_equal(hb_count(NULL, HB_LIST_ALLOW), 0); } /* --- load: argument validation --- static void test_load_null_args(void **state) { (void)st...*
- `test_various_ip_tokens_ignored` (line 63) `static void test_various_ip_tokens_ignored(void **state)`
- `test_bare_domain_per_line` (line 72) `static void test_bare_domain_per_line(void **state)`
- `test_comments_and_blanks` (line 82) `static void test_comments_and_blanks(void **state)`
- `test_multiple_tokens_per_line` (line 98) `static void test_multiple_tokens_per_line(void **state)`
- `test_no_trailing_newline` (line 106) `static void test_no_trailing_newline(void **state)`
- `test_lowercased` (line 117) `static void test_lowercased(void **state)` - *assert_int_equal(hb_count(s, HB_LIST_BLOCK), 3); hb_free(s); } static void test_no_trailing_newline(void **state) { (void)state; hb_set *s = hb_new...*
- `test_trailing_dot_trimmed` (line 127) `static void test_trailing_dot_trimmed(void **state)`
- `test_invalid_tokens_skipped` (line 138) `static void test_invalid_tokens_skipped(void **state)`
- `test_oversize_token_skipped` (line 154) `static void test_oversize_token_skipped(void **state)`
- `test_underscore_and_hyphen_valid` (line 165) `static void test_underscore_and_hyphen_valid(void **state)`
- `test_dedup_and_accumulate` (line 173) `static void test_dedup_and_accumulate(void **state)`
- `test_lists_independent` (line 184) `static void test_lists_independent(void **state)`
- `test_block_covers_subdomains` (line 196) `static void test_block_covers_subdomains(void **state)` - *hb_free(s); } static void test_lists_independent(void **state) { (void)state; hb_set *s = hb_new(); assert_int_equal(hb_load(s, "a.com\nb.com\n", H...*
- `test_allow_wins_and_covers_subdomains` (line 209) `static void test_allow_wins_and_covers_subdomains(void **state)`
- `test_no_lists_allows` (line 223) `static void test_no_lists_allows(void **state)`
- `test_is_allowlisted` (line 230) `static void test_is_allowlisted(void **state)`
- `test_check_fail_open_edges` (line 251) `static void test_check_fail_open_edges(void **state)`
- `main` (line 265) `int main(void)`

#### `test_hostedit.c`
**Path:** `tests/test_hostedit.c`
**File Doc:** *include <setjmp.h> include <stdarg.h> include <stddef.h> include <stdint.h> include <string.h>  include <cmocka.h>  include "hostedit.h"*

**Functions:**
- `test_make_line_lowercases` (line 10) `static void test_make_line_lowercases(void **state)` - *include "hostedit.h"*
- `test_make_line_plain_host` (line 17) `static void test_make_line_plain_host(void **state)`
- `test_make_line_rejects_path_scheme_garbage` (line 24) `static void test_make_line_rejects_path_scheme_garbage(void **state)`
- `test_make_line_rejects_bad_labels` (line 35) `static void test_make_line_rejects_bad_labels(void **state)`
- `test_make_line_null_and_range` (line 46) `static void test_make_line_null_and_range(void **state)`
- `test_make_line_single_label_ok` (line 55) `static void test_make_line_single_label_ok(void **state)`
- `test_text_has_host` (line 62) `static void test_text_has_host(void **state)`
- `test_suggest_prefix_first` (line 75) `static void test_suggest_prefix_first(void **state)`
- `test_suggest_case_insensitive_and_dedup` (line 91) `static void test_suggest_case_insensitive_and_dedup(void **state)`
- `test_suggest_empty_query_and_cap` (line 100) `static void test_suggest_empty_query_and_cap(void **state)`
- `main` (line 113) `int main(void)`

#### `test_html_parse.c`
**Path:** `tests/test_html_parse.c`

**Functions:**
- `test_config_default_is_secure` (line 36) `static void test_config_default_is_secure(void **state)` - *static const char DOC_SIMPLE[] = "<!DOCTYPE html><html><head><title>Hello Title</title></head>" "<body><p>Hello World</p></body></html>"; static co...*
- `test_validate_rejects_null` (line 44) `static void test_validate_rejects_null(void **state)`
- `test_validate_rejects_empty` (line 50) `static void test_validate_rejects_empty(void **state)`
- `test_validate_rejects_oversize` (line 56) `static void test_validate_rejects_oversize(void **state)`
- `test_validate_accepts_within_cap` (line 63) `static void test_validate_accepts_within_cap(void **state)`
- `test_parse_rejects_null_args` (line 71) `static void test_parse_rejects_null_args(void **state)` - *static void test_validate_rejects_oversize(void **state) { (void)state; hp_config c = hp_config_default(); c.max_bytes = 8; assert_int_equal(hp_val...*
- `test_parse_rejects_oversize` (line 79) `static void test_parse_rejects_oversize(void **state)`
- `test_parse_simple_document` (line 90) `static void test_parse_simple_document(void **state)` - *assert_int_equal(hp_parse(NULL, 5, &c, &doc), HP_ERR_NULL_ARG); assert_int_equal(hp_parse("x", 1, &c, NULL), HP_ERR_NULL_ARG); } static void test_p...*
- `test_scripts_stripped_by_default` (line 115) `static void test_scripts_stripped_by_default(void **state)` - *assert_non_null(title); assert_string_equal(title, "Hello Title"); hp_free(title); size_t blen = 0; char *text = hp_extract_text(doc, &blen); asser...*
- `test_scripts_kept_when_disabled` (line 130) `static void test_scripts_kept_when_disabled(void **state)`
- `test_event_handlers_stripped_by_default` (line 140) `static void test_event_handlers_stripped_by_default(void **state)`
- `test_event_handlers_kept_when_disabled` (line 149) `static void test_event_handlers_kept_when_disabled(void **state)`
- `test_extract_script_list_skips_non_js_type` (line 227) `static void test_extract_script_list_skips_non_js_type(void **state)` - *A classic script runs only when its type is absent/empty or a JavaScript MIME type. Template/data blocks (text/x-jquery-tmpl, text/html, text/templ...*
- `test_extract_script_list_empty` (line 256) `static void test_extract_script_list_empty(void **state)` - *assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK); size_t n = 0; hp_script *s = hp_extract_script_list(doc, &n); assert_non_null(s); assert_int_e...*
- `test_extract_stylesheets_basic` (line 300) `static void test_extract_stylesheets_basic(void **state)` - *Two applicable <link rel=stylesheet> come back as their RAW hrefs in document * order; noise (rel=icon, link without href, a <style> element) is sk...*
- `test_extract_stylesheets_rel_tokens` (line 327) `static void test_extract_stylesheets_rel_tokens(void **state)` - *rel matches by whitespace-separated token, case-insensitively: "STYLESHEET" applies; "alternate stylesheet" is an inactive alternate sheet (skipped...*
- `test_extract_stylesheets_none_and_null` (line 377) `static void test_extract_stylesheets_none_and_null(void **state)` - *No applicable links => NULL with count 0; NULL doc likewise; the releaser is * idempotent on NULL.*
- `test_extract_stylesheets_caps` (line 394) `static void test_extract_stylesheets_caps(void **state)` - *hp_document *doc = NULL; assert_int_equal(hp_parse(LIT("<html><body><p>hi</p></body></html>"), &c, &doc), HP_OK); size_t n = 123; char **s = hp_ext...*
- `test_parse_malformed_does_not_crash` (line 417) `static void test_parse_malformed_does_not_crash(void **state)` - *off += (size_t)snprintf(html + off, buflen - off, "%s", one); hp_config c = hp_config_default(); hp_document *doc = NULL; assert_int_equal(hp_parse...*
- `test_free_null_and_double` (line 429) `static void test_free_null_and_double(void **state)` - */* --- robustness --- static void test_parse_malformed_does_not_crash(void **state) { (void)state; hp_config c = hp_config_default(); hp_document *...*
- `main` (line 439) `int main(void)`

**Macros:**
- `LIT` (line 20)

#### `test_image_decode.c`
**Path:** `tests/test_image_decode.c`

**Functions:**
- `px` (line 64) `static uint32_t px(const img_pixels *p, uint32_t x, uint32_t y)`
- `test_sniff_png` (line 74) `static void test_sniff_png(void **state)` - *0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x1...*
- `test_sniff_unsupported` (line 79) `static void test_sniff_unsupported(void **state)`
- `test_dimensions_from_ihdr` (line 88) `static void test_dimensions_from_ihdr(void **state)` - *static void test_sniff_png(void **state) { (void)state; assert_int_equal(img_sniff(PNG_2x2, sizeof PNG_2x2), IMG_FMT_PNG); } static void test_sniff...*
- `test_dimensions_truncated` (line 96) `static void test_dimensions_truncated(void **state)`
- `test_dimensions_non_png` (line 103) `static void test_dimensions_non_png(void **state)`
- `test_dimensions_null` (line 110) `static void test_dimensions_null(void **state)`
- `test_dimensions_ok_bounds` (line 119) `static void test_dimensions_ok_bounds(void **state)` - *(void)state; uint32_t w = 0, h = 0; const uint8_t junk[16] = {0}; assert_int_equal(img_png_dimensions(junk, sizeof junk, &w, &h), IMG_ERR_FORMAT); ...*
- `test_fit_landscape_into_square` (line 135) `static void test_fit_landscape_into_square(void **state)` - *(void)state; assert_int_equal(img_dimensions_ok(1, 1), 1); assert_int_equal(img_dimensions_ok(IMG_MAX_DIM, 1), 1); assert_int_equal(img_dimensions_...*
- `test_fit_portrait_into_box` (line 144) `static void test_fit_portrait_into_box(void **state)`
- `test_fit_degenerate` (line 153) `static void test_fit_degenerate(void **state)`
- `test_decode_dimensions_and_stride` (line 165) `static void test_decode_dimensions_and_stride(void **state)` - *assert_true(h > 99.9 && h < 100.1); } static void test_fit_degenerate(void **state) { (void)state; double w = 1, h = 1; img_fit(0, 10, 100.0, 100.0...*
- `test_decode_pixels_premultiplied` (line 177) `static void test_decode_pixels_premultiplied(void **state)`
- `test_decode_rejects_non_png` (line 189) `static void test_decode_rejects_non_png(void **state)`
- `test_decode_rejects_truncated` (line 199) `static void test_decode_rejects_truncated(void **state)`
- `test_decode_null_args` (line 209) `static void test_decode_null_args(void **state)`
- `test_pixels_free_idempotent` (line 217) `static void test_pixels_free_idempotent(void **state)`
- `test_format_name` (line 226) `static void test_format_name(void **state)`
- `test_sniff_jpeg` (line 235) `static void test_sniff_jpeg(void **state)` - *memset(&p, 0, sizeof p); img_pixels_free(&p); img_pixels_free(&p); img_pixels_free(NULL); } static void test_format_name(void **state) { (void)stat...*
- `test_decode_jpeg_dimensions_and_alpha` (line 243) `static void test_decode_jpeg_dimensions_and_alpha(void **state)`
- `test_decode_dispatch_routes_jpeg_and_png` (line 266) `static void test_decode_dispatch_routes_jpeg_and_png(void **state)`
- `test_decode_dispatch_rejects_unknown` (line 278) `static void test_decode_dispatch_rejects_unknown(void **state)`
- `test_decode_jpeg_rejects_truncated` (line 286) `static void test_decode_jpeg_rejects_truncated(void **state)`
- `test_decode_jpeg_rejects_non_jpeg` (line 294) `static void test_decode_jpeg_rejects_non_jpeg(void **state)`
- `test_decode_jpeg_null_args` (line 301) `static void test_decode_jpeg_null_args(void **state)`
- `test_sniff_gif` (line 355) `static void test_sniff_gif(void **state)`
- `test_decode_gif_pixels` (line 362) `static void test_decode_gif_pixels(void **state)`
- `test_decode_gif_transparency` (line 377) `static void test_decode_gif_transparency(void **state)`
- `test_decode_gif_interlaced` (line 389) `static void test_decode_gif_interlaced(void **state)`
- `test_decode_gif_animated_first_frame` (line 404) `static void test_decode_gif_animated_first_frame(void **state)`
- `test_decode_gif_fail_closed` (line 413) `static void test_decode_gif_fail_closed(void **state)`
- `test_decode_dispatch_routes_gif` (line 429) `static void test_decode_dispatch_routes_gif(void **state)`
- `test_sniff_webp` (line 447) `static void test_sniff_webp(void **state)`
- `test_decode_webp_dimensions_and_pixels` (line 453) `static void test_decode_webp_dimensions_and_pixels(void **state)`
- `test_decode_webp_fail_closed` (line 470) `static void test_decode_webp_fail_closed(void **state)`
- `test_decode_dispatch_routes_webp` (line 482) `static void test_decode_dispatch_routes_webp(void **state)`
- `main` (line 491) `int main(void)`

#### `test_js_dom.c`
**Path:** `tests/test_js_dom.c`

**Functions:**
- `setup` (line 40) `static int setup(void **state)`
- `teardown` (line 51) `static int teardown(void **state)`
- `run` (line 65) `static js_status run(fixture *f, const char *src, js_result *r)` - *Evaluates src in the fixture context and returns the result string (owned by * the caller-provided js_result, freed by the caller).*
- `test_install_null_args` (line 79) `static void test_install_null_args(void **state)` - *static js_status run(fixture *f, const char *src, js_result *r) { return js_eval(f->ctx, src, strlen(src), r); } #define EXPECT(f, src, expected)  ...*
- `test_get_element_by_id` (line 90) `static void test_get_element_by_id(void **state)` - *} while (0) /* --- install --- static void test_install_null_args(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_...*
- `test_node_count` (line 98) `static void test_node_count(void **state)`
- `test_by_class_and_tag` (line 103) `static void test_by_class_and_tag(void **state)`
- `test_navigation` (line 111) `static void test_navigation(void **state)`
- `test_attributes` (line 121) `static void test_attributes(void **state)`
- `test_document_order` (line 128) `static void test_document_order(void **state)`
- `test_invalid_handles` (line 137) `static void test_invalid_handles(void **state)` - *fixture *f = (fixture *)*state; EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'class')", "container box"); EXPECT(f, "dom.getAttribute(dom...*
- `test_methods_are_frozen` (line 147) `static void test_methods_are_frozen(void **state)` - *"true"); } /* --- robustness: bogus handles never crash, just yield null --- static void test_invalid_handles(void **state) { fixture *f = (fixture...*
- `test_no_io_with_dom` (line 158) `static void test_no_io_with_dom(void **state)` - *} /* --- the API cannot be hijacked --- static void test_methods_are_frozen(void **state) { fixture *f = (fixture *)*state; /* Reassigning a method...*
- `test_document_shim_present` (line 166) `static void test_document_shim_present(void **state)` - *"function"); /* The sealed object rejects new properties. EXPECT(f, "try{dom.injected=1}catch(e){}; typeof dom.injected", "undefined"); } /* --- st...*
- `test_query_selector_from_js` (line 173) `static void test_query_selector_from_js(void **state)`
- `test_element_matches_closest_query_from_js` (line 187) `static void test_element_matches_closest_query_from_js(void **state)`
- `test_node_identity_is_cached` (line 197) `static void test_node_identity_is_cached(void **state)`
- `test_element_traversal` (line 204) `static void test_element_traversal(void **state)`
- `test_classlist_backs_class_attr` (line 213) `static void test_classlist_backs_class_attr(void **state)`
- `test_document_fragment_reparents` (line 223) `static void test_document_fragment_reparents(void **state)`
- `jQuery` (line 238) `* page that ships jQuery (Slashdot). The fragment must be complete enough that the
 * detection c...`
- `test_modern_globals_do_not_throw` (line 256) `static void test_modern_globals_do_not_throw(void **state)`
- `EXPECT` (line 262) `EXPECT(f, "typeof (new MutationObserver(function()`
- `bundle` (line 277) `* library bundle (DuckDuckGo's l.js "cannot read property createElement of
 * undefined"). This l...`
- `methods` (line 293) `* backed by the sealed dom methods (this element's own attributes only). */
static void test_elem...`
- `test_intl_stub_does_not_throw` (line 312) `static void test_intl_stub_does_not_throw(void **state)` - *Intl stub: QuickJS-ng builds without ICU, so Intl is otherwise undefined and any locale-aware script (DuckDuckGo's wplv.js: "Intl is not defined") ...*
- `test_url_constructor_parses_components` (line 325) `static void test_url_constructor_parses_components(void **state)` - *WHATWG URL: identity-safe, pure string parsing (no network/IO). This was * Slashdot's first JS error (ReferenceError: URL is not defined).*
- `test_url_search_params` (line 348) `static void test_url_search_params(void **state)` - *EXPECT(f, "new URL('https://a.b.com/p?x=1#frag').hash", "#frag"); EXPECT(f, "new URL('https://a.b.com/p').origin", "https://a.b.com"); /* A bare pa...*
- `test_settimeout_chains_across_rounds` (line 372) `static void test_settimeout_chains_across_rounds(void **state)`
- `test_document_title_set_reflects_in_tree` (line 379) `static void test_document_title_set_reflects_in_tree(void **state)`
- `test_set_text_content_reflects_in_tree` (line 393) `static void test_set_text_content_reflects_in_tree(void **state)`
- `test_set_text_content_detach_is_memory_safe` (line 404) `static void test_set_text_content_detach_is_memory_safe(void **state)`
- `test_document_is_not_io` (line 419) `static void test_document_is_not_io(void **state)`
- `test_create_append_renders_in_tree` (line 428) `static void test_create_append_renders_in_tree(void **state)` - */* 'go' is detached but alive: its tag still reads safely. assert_string_equal(r.value, "BUTTON"); js_result_free(&r); EXPECT(f, "document.getEleme...*
- `test_set_attribute_makes_queryable` (line 444) `static void test_set_attribute_makes_queryable(void **state)`
- `test_element_has_attribute` (line 470) `static void test_element_has_attribute(void **state)`
- `test_element_remove_attribute` (line 476) `static void test_element_remove_attribute(void **state)`
- `test_element_src_href_are_strings` (line 486) `static void test_element_src_href_are_strings(void **state)`
- `test_append_cycle_is_rejected` (line 494) `static void test_append_cycle_is_rejected(void **state)`
- `test_onload_runs_and_mutates` (line 502) `static void test_onload_runs_and_mutates(void **state)`
- `assert_int_equal` (line 507) `assert_int_equal(run(f,
        "window.onload=function()`
- `test_settimeout_flushed_by_pump` (line 515) `static void test_settimeout_flushed_by_pump(void **state)`
- `EXPECT` (line 518) `EXPECT(f,
        "setTimeout(function()`
- `test_inner_html_builds_and_queryable` (line 523) `static void test_inner_html_builds_and_queryable(void **state)`
- `test_inner_html_getter_serializes` (line 534) `static void test_inner_html_getter_serializes(void **state)` - *"var b=document.getElementById('go').textContent; __fireDeferred();" "b+'/'+document.getElementById('go').textContent", "Go/timed"); } static void ...*
- `test_storage_is_ephemeral` (line 544) `static void test_storage_is_ephemeral(void **state)` - *assert_int_not_equal(ih, DOM_NODE_NONE); } /* innerHTML GETTER (2026-07-11): serializes the node's children back to markup. static void test_inner_...*
- `test_cookie_and_referrer_leak_nothing` (line 550) `static void test_cookie_and_referrer_leak_nothing(void **state)`
- `persisted` (line 565) `* never persisted (process-lifetime only). */
static void test_cookie_jar_enabled_for_trusted_hos...`
- `test_ambient_apis_do_not_throw` (line 589) `static void test_ambient_apis_do_not_throw(void **state)`
- `set_https_location` (line 601) `static void set_https_location(fixture *f, const char *url)` - *assert_null(strstr(buf, "theme=")); } static void test_ambient_apis_do_not_throw(void **state) { fixture *f = (fixture *)*state; /* history/locatio...*
- `test_location_reads_real_components` (line 606) `static void test_location_reads_real_components(void **state)`
- `test_location_pathname_defaults_slash` (line 623) `static void test_location_pathname_defaults_slash(void **state)`
- `test_location_href_set_captures_raw` (line 631) `static void test_location_href_set_captures_raw(void **state)`
- `test_location_replace_sets_replace_flag` (line 645) `static void test_location_replace_sets_replace_flag(void **state)`
- `test_location_assign_and_window_last_wins` (line 657) `static void test_location_assign_and_window_last_wins(void **state)`
- `test_no_nav_request_when_idle` (line 669) `static void test_no_nav_request_when_idle(void **state)`
- `test_local_page_captures_nav` (line 679) `static void test_local_page_captures_nav(void **state)` - *A local (file) page has no https parts but still captures navigation requests, * so the parent can resolve them against the file base.*
- `test_set_location_null_ctx` (line 690) `static void test_set_location_null_ctx(void **state)`
- `console_fixture` (line 701) `static void console_fixture(hp_document **doc, dom_index **idx, js_context **ctx,
               ...` - *assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1); assert_string_equal(buf, "sub.html"); } static void test_set_location_...*
- `console_teardown` (line 711) `static void console_teardown(hp_document *doc, dom_index *idx, js_context *ctx,
                 ...`
- `test_console_captures_levels` (line 719) `static void test_console_captures_levels(void **state)`
- `test_console_object_and_throwing_tostring` (line 746) `static void test_console_object_and_throwing_tostring(void **state)`
- `test_console_null_buffer_is_noop` (line 766) `static void test_console_null_buffer_is_noop(void **state)`
- `test_console_null_ctx` (line 787) `static void test_console_null_ctx(void **state)`
- `test_click_install_null_args` (line 796) `static void test_click_install_null_args(void **state)` - *js_context_free(ctx); dom_free(idx); hp_document_free(doc); } static void test_console_null_ctx(void **state) { (void)state; fb_buffer log; fb_buff...*
- `test_click_add_event_listener_fires` (line 803) `static void test_click_add_event_listener_fires(void **state)` - *(void)state; fb_buffer log; fb_buffer_init(&log); assert_int_equal(jd_install_console(NULL, &log), JD_ERR_NULL_ARG); fb_buffer_free(&log); } /* ---...*
- `test_click_onclick_fires` (line 827) `static void test_click_onclick_fires(void **state)` - *"p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_...*
- `test_click_prevent_default` (line 851) `static void test_click_prevent_default(void **state)` - *"b._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_...*
- `test_click_no_handler_allows_default` (line 874) `static void test_click_no_handler_allows_default(void **state)` - *"b.onclick = function(e){ e.preventDefault(); b.textContent = 'prevented'; };" "b._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(s...*
- `main` (line 884) `int main(void)`

**Macros:**
- `EXPECT` (line 68)

**Structs:**
- `fixture` (line 34)

#### `test_js_env.c`
**Path:** `tests/test_js_env.c`

**Functions:**
- `setup` (line 28) `static int setup(void **state)`
- `teardown` (line 37) `static int teardown(void **state)`
- `run` (line 46) `static js_status run(fixture *f, const char *src, js_result *r)`
- `test_install_null_args` (line 61) `static void test_install_null_args(void **state)` - *static js_status run(fixture *f, const char *src, js_result *r) { return js_eval(f->ctx, src, strlen(src), r); } #define EXPECT(f, src, expected)  ...*
- `test_navigator_identity` (line 73) `static void test_navigator_identity(void **state)` - */* --- install --- static void test_install_null_args(void **state) { (void)state; assert_int_equal(je_install(NULL, 1920, 1080), JE_ERR_NULL_ARG);...*
- `test_legacy_nav_props` (line 91) `static void test_legacy_nav_props(void **state)` - *EXPECT(f, "navigator.userAgent.length > 0", "true"); EXPECT(f, "navigator.language", "en-US"); EXPECT(f, "navigator.languages.length", "2"); EXPECT...*
- `test_bool_nav_props` (line 102) `static void test_bool_nav_props(void **state)`
- `test_navigator_plugins` (line 111) `static void test_navigator_plugins(void **state)` - *EXPECT(f, "navigator.productSub", "20100101"); EXPECT(f, "navigator.oscpu", "Linux x86_64"); EXPECT(f, "navigator.appVersion.length > 0", "true"); ...*
- `test_navigator_mime_types` (line 119) `static void test_navigator_mime_types(void **state)`
- `test_crypto_present` (line 128) `static void test_crypto_present(void **state)` - *EXPECT(f, "navigator.plugins.length > 0", "true"); EXPECT(f, "navigator.plugins[0].name.length > 0", "true"); EXPECT(f, "navigator.plugins[0].filen...*
- `test_crypto_random_uuid` (line 136) `static void test_crypto_random_uuid(void **state)`
- `test_crypto_random_values` (line 145) `static void test_crypto_random_values(void **state)`
- `test_screen_orientation` (line 155) `static void test_screen_orientation(void **state)` - *EXPECT(f, "var u=crypto.randomUUID(); u.charAt(14)==='4'?'v4':'not-v4'", "v4"); EXPECT(f, "var a=crypto.randomUUID(),b=crypto.randomUUID(); a!==b?'...*
- `test_screen_bucketed` (line 165) `static void test_screen_bucketed(void **state)` - *"a===b?'returned-same':'different'", "returned-same"); } /* --- screen orientation (Hito 30b) --- static void test_screen_orientation(void **state)...*
- `test_clocks_coarse` (line 177) `static void test_clocks_coarse(void **state)` - */* --- screen bucketing: real (1680,1050) snaps to 1600x900 --- static void test_screen_bucketed(void **state) { fixture *f = (fixture *)*state; EX...*
- `test_performance_timing_identity_safe` (line 190) `static void test_performance_timing_identity_safe(void **state)` - *performance.timing / navigation / getEntries*: present (real analytics read them) and identity-safe -- every timing field is the same fixed epoch (...*
- `test_unforgeable` (line 205) `static void test_unforgeable(void **state)` - *fixture *f = (fixture *)*state; EXPECT(f, "typeof performance.timing", "object"); EXPECT(f, "performance.timing.responseStart - performance.timing....*
- `test_screen_edges` (line 219) `static void test_screen_edges(void **state)` - *static void test_unforgeable(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "try{navigator.userAgent='x'}catch(e){};" "navigator.userAge...*
- `test_canvas_readback` (line 238) `static void test_canvas_readback(void **state)` - *assert_int_equal(je_install(ctx, 0, 0), JE_OK); js_result r; const char *probe = "screen.width > 0"; assert_int_equal(js_eval(ctx, probe, strlen(pr...*
- `readback_checksum` (line 279) `static void readback_checksum(uint64_t key, char *out, size_t out_size)` - *assert_int_equal(js_eval(ctx, det, strlen(det), &r), JS_OK); assert_string_equal(r.value, "true"); js_result_free(&r); /* audio shares the same poi...*
- `test_canvas_unlinkable` (line 294) `static void test_canvas_unlinkable(void **state)`
- `test_canvas_unforgeable` (line 302) `static void test_canvas_unforgeable(void **state)`
- `test_coexists_with_dom` (line 325) `static void test_coexists_with_dom(void **state)`
- `main` (line 354) `int main(void)`

**Macros:**
- `EXPECT` (line 50)

**Structs:**
- `fixture` (line 25)

#### `test_js_policy.c`
**Path:** `tests/test_js_policy.c`

**Functions:**
- `test_enabled_fail_closed_on_bad_mode` (line 30) `static void test_enabled_fail_closed_on_bad_mode(void **state)`
- `test_mode_from_str` (line 35) `static void test_mode_from_str(void **state)`
- `test_mode_str_roundtrip` (line 52) `static void test_mode_str_roundtrip(void **state)`
- `test_trusted_requires_both_signals` (line 68) `static void test_trusted_requires_both_signals(void **state)` - *Hito 28: a host is TRUSTED (full author CSS + images, on top of full JS) only when the user declared it twice: JS enabled for it AND explicitly on ...*
- `main` (line 88) `int main(void)`

#### `test_js_sandbox.c`
**Path:** `tests/test_js_sandbox.c`

**Functions:**
- `test_validate_rejects_null` (line 33) `static void test_validate_rejects_null(void **state)` - *#include "js_sandbox.h" /* --- js_limits_default --- static void test_limits_default_is_secure(void **state) { (void)state; js_limits l = js_limits...*
- `test_validate_rejects_empty` (line 38) `static void test_validate_rejects_empty(void **state)`
- `test_validate_rejects_oversize` (line 43) `static void test_validate_rejects_oversize(void **state)`
- `test_validate_accepts_within_cap` (line 50) `static void test_validate_accepts_within_cap(void **state)`
- `test_context_new_and_free` (line 57) `static void test_context_new_and_free(void **state)` - *static void test_validate_rejects_oversize(void **state) { (void)state; js_limits l = js_limits_default(); l.max_source_bytes = 4; assert_int_equal...*
- `test_context_new_null_out` (line 65) `static void test_context_new_null_out(void **state)`
- `test_eval_arithmetic` (line 72) `static void test_eval_arithmetic(void **state)` - *static void test_context_new_and_free(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); ass...*
- `test_eval_string_concat` (line 86) `static void test_eval_string_concat(void **state)`
- `test_eval_syntax_error` (line 98) `static void test_eval_syntax_error(void **state)` - *js_context_free(ctx); } static void test_eval_string_concat(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); assert_int_equal(js_...*
- `test_eval_runtime_exception` (line 107) `static void test_eval_runtime_exception(void **state)`
- `test_no_io_globals` (line 121) `static void test_no_io_globals(void **state)` - *static void test_eval_runtime_exception(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); assert_int_equal(js_eval_once("throw new...*
- `test_filesystem_access_is_reference_error` (line 134) `static void test_filesystem_access_is_reference_error(void **state)`
- `test_infinite_loop_times_out` (line 147) `static void test_infinite_loop_times_out(void **state)` - *} static void test_filesystem_access_is_reference_error(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); const char *src = "readF...*
- `assert_int_equal` (line 154) `assert_int_equal(js_eval_once("while(true)`
- `test_set_time_budget_applies` (line 161) `static void test_set_time_budget_applies(void **state)` - *js_set_time_budget lowers the wall-clock cap armed on subsequent evals, so a caller can enforce a single page-wide budget across many evaluations. ...*
- `assert_int_equal` (line 169) `assert_int_equal(js_eval(ctx, "while(true)`
- `test_memory_limit_is_enforced` (line 177) `static void test_memory_limit_is_enforced(void **state)`
- `test_result_free_on_zeroed` (line 193) `static void test_result_free_on_zeroed(void **state)` - *Unbounded object allocation exhausts the heap and is denied by the cap. (A doubling string instead trips the engine's max-string-length first, * wh...*
- `test_context_free_null_and_double` (line 202) `static void test_context_free_null_and_double(void **state)`
- `test_eval_null_args` (line 210) `static void test_eval_null_args(void **state)`
- `test_loc_parses_named_frame` (line 224) `static void test_loc_parses_named_frame(void **state)` - *static void test_eval_null_args(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); js_result...*
- `test_loc_parses_bare_frame` (line 235) `static void test_loc_parses_bare_frame(void **state)`
- `test_loc_file_may_contain_colons` (line 244) `static void test_loc_file_may_contain_colons(void **state)`
- `test_loc_line_only_sets_col_zero` (line 255) `static void test_loc_line_only_sets_col_zero(void **state)`
- `test_loc_truncates_to_cap` (line 264) `static void test_loc_truncates_to_cap(void **state)`
- `test_loc_rejects_garbage_and_null` (line 272) `static void test_loc_rejects_garbage_and_null(void **state)`
- `test_eval_named_captures_location` (line 287) `static void test_eval_named_captures_location(void **state)` - *static void test_loc_rejects_garbage_and_null(void **state) { (void)state; char file[16]; int line = 9, col = 9; assert_int_equal(js_loc_from_stack...*
- `test_eval_named_null_filename_defaults` (line 308) `static void test_eval_named_null_filename_defaults(void **state)`
- `test_eval_thrown_primitive_has_no_location` (line 323) `static void test_eval_thrown_primitive_has_no_location(void **state)`
- `main` (line 339) `int main(void)`

#### `test_link_nav.c`
**Path:** `tests/test_link_nav.c`

**Functions:**
- `test_null_out` (line 23) `static void test_null_out(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #include "link_nav.h" stati...*
- `test_null_href_blocked` (line 28) `static void test_null_href_blocked(void **state)`
- `test_fragment_is_same_document` (line 36) `static void test_fragment_is_same_document(void **state)` - */* --- argument handling --- static void test_null_out(void **state) { (void)state; assert_int_equal(ln_resolve("https://h/", "/x", NULL), LN_ERR_N...*
- `test_https_absolute` (line 48) `static void test_https_absolute(void **state)` - */* --- fragments / empty --- static void test_fragment_is_same_document(void **state) { (void)state; assert_int_equal(ln_resolve("https://h.example...*
- `test_https_relative` (line 56) `static void test_https_relative(void **state)`
- `test_https_absolute_path_and_parent` (line 64) `static void test_https_absolute_path_and_parent(void **state)`
- `test_https_blocks_downgrade_and_schemes` (line 75) `static void test_https_blocks_downgrade_and_schemes(void **state)`
- `test_https_scheme_relative` (line 90) `static void test_https_scheme_relative(void **state)`
- `test_resolve_long_bundle_target` (line 101) `static void test_resolve_long_bundle_target(void **state)` - *Modern bundle URLs exceed the old 4096 target cap (google's xjs URL is 3456 bytes BEFORE resolution; longer ones exist): a link/script href resolvi...*
- `test_href_cleaning` (line 113) `static void test_href_cleaning(void **state)` - *BEFORE resolution; longer ones exist): a link/script href resolving to > 4096 * bytes must still navigate. static void test_resolve_long_bundle_tar...*
- `test_file_relative` (line 124) `static void test_file_relative(void **state)` - *} /* --- href cleaning --- static void test_href_cleaning(void **state) { (void)state; /* Surrounding whitespace and embedded tab/newline/CR are st...*
- `test_file_parent` (line 132) `static void test_file_parent(void **state)`
- `test_file_absolute_path` (line 140) `static void test_file_absolute_path(void **state)`
- `test_file_drops_fragment` (line 148) `static void test_file_drops_fragment(void **state)`
- `test_file_base_to_https` (line 156) `static void test_file_base_to_https(void **state)`
- `test_file_base_blocks_schemes_and_scheme_relative` (line 164) `static void test_file_base_blocks_schemes_and_scheme_relative(void **state)`
- `test_no_base` (line 178) `static void test_no_base(void **state)` - *static void test_file_base_blocks_schemes_and_scheme_relative(void **state) { (void)state; assert_int_equal(ln_resolve("/home/u/a.html", "http://h....*
- `test_overflow_blocked` (line 194) `static void test_overflow_blocked(void **state)` - *(void)state; assert_int_equal(ln_resolve(NULL, "https://h.example/x", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_int_equal(R.kind...*
- `test_block_reasons` (line 206) `static void test_block_reasons(void **state)` - */* --- overflow fails closed --- static void test_overflow_blocked(void **state) { (void)state; char big[LN_MAX_TARGET + 64]; memcpy(big, "https://...*
- `test_block_reason_text` (line 233) `static void test_block_reason_text(void **state)`
- `test_fragment_capture` (line 243) `static void test_fragment_capture(void **state)` - *assert_int_equal(ln_resolve("https://h.example/", "/x", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_int_equal(R.reason, LN_BLOCK_N...*
- `main` (line 272) `int main(void)`

#### `test_local_store.c`
**Path:** `tests/test_local_store.c`

**Functions:**
- `roundtrip_raw` (line 29) `static void roundtrip_raw(ls_aead aead)` - *#include <cmocka.h> #include "local_store.h" static const uint8_t KEY[LS_KEY_LEN] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0...*
- `test_roundtrip_aes` (line 47) `static void test_roundtrip_aes(void **s)`
- `test_roundtrip_chacha` (line 49) `static void test_roundtrip_chacha(void **s)`
- `test_empty_plaintext` (line 52) `static void test_empty_plaintext(void **s)` - *assert_int_equal(blob_len, LS_OVERHEAD + (sizeof PT - 1)); assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_OK); assert_int_equal(...*
- `test_wrong_key` (line 66) `static void test_wrong_key(void **s)` - *static void test_empty_plaintext(void **s) { (void)s; uint8_t *blob = NULL, *out = NULL; size_t blob_len = 0, out_len = 99; assert_int_equal(ls_sea...*
- `tamper_at` (line 84) `static void tamper_at(size_t off)` - *size_t blob_len = 0, out_len = 1; assert_int_equal( ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len), LS_OK);...*
- `test_tamper_ciphertext` (line 98) `static void test_tamper_ciphertext(void **s)`
- `test_tamper_tag` (line 100) `static void test_tamper_tag(void **s)`
- `test_tamper_nonce` (line 101) `static void test_tamper_nonce(void **s)`
- `test_tamper_salt` (line 102) `static void test_tamper_salt(void **s)`
- `test_tamper_aead_id` (line 103) `static void test_tamper_aead_id(void **s)`
- `test_nondeterministic` (line 106) `static void test_nondeterministic(void **s)` - *blob[off] ^= 0x01; ls_status st = ls_open(KEY, blob, blob_len, &out, &out_len); assert_true(st == LS_ERR_AUTH || st == LS_ERR_FORMAT); assert_null(...*
- `test_passphrase_roundtrip` (line 120) `static void test_passphrase_roundtrip(void **s)` - *static void test_nondeterministic(void **s) { (void)s; uint8_t *a = NULL, *b = NULL; size_t al = 0, bl = 0; assert_int_equal(ls_seal(KEY, LS_AEAD_A...*
- `test_derive_key` (line 148) `static void test_derive_key(void **s)` - *assert_memory_equal(out, PT, sizeof PT - 1); ls_free(out, out_len); const char *wrong = "Tr0ub4dor&3"; uint8_t *out2 = (uint8_t *)0x1; size_t out2_...*
- `test_format_errors` (line 165) `static void test_format_errors(void **s)` - *const char *pass = "passphrase"; uint8_t salt1[LS_SALT_LEN], salt2[LS_SALT_LEN]; memset(salt1, 0xAA, sizeof salt1); memset(salt2, 0xBB, sizeof salt...*
- `test_null_and_limits` (line 180) `static void test_null_and_limits(void **s)`
- `main` (line 192) `int main(void)`

#### `test_net_realm.c`
**Path:** `tests/test_net_realm.c`

**Functions:**
- `test_classify_host_onion` (line 21) `static void test_classify_host_onion(void **state)` - *.i2p only via I2P) and fail-closed (missing proxy or unclassifiable URL => blocked).  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #...*
- `test_classify_host_i2p` (line 29) `static void test_classify_host_i2p(void **state)`
- `test_classify_host_clearnet` (line 36) `static void test_classify_host_clearnet(void **state)`
- `test_classify_host_lookalikes` (line 44) `static void test_classify_host_lookalikes(void **state)` - *static void test_classify_host_i2p(void **state) { (void)state; assert_int_equal(nr_classify_host("stats.i2p"), NR_I2P); assert_int_equal(nr_classi...*
- `test_classify_host_edges` (line 53) `static void test_classify_host_edges(void **state)`
- `test_classify_url` (line 66) `static void test_classify_url(void **state)` - *} static void test_classify_host_edges(void **state) { (void)state; assert_int_equal(nr_classify_host(NULL), NR_CLEARNET); assert_int_equal(nr_clas...*
- `test_route_onion` (line 78) `static void test_route_onion(void **state)` - */* --- nr_classify_url --- static void test_classify_url(void **state) { (void)state; assert_int_equal(nr_classify_url("https://abc.onion/path?q=1"...*
- `test_route_i2p` (line 87) `static void test_route_i2p(void **state)`
- `test_route_clearnet` (line 95) `static void test_route_clearnet(void **state)`
- `test_route_null_blocked` (line 109) `static void test_route_null_blocked(void **state)`
- `test_realm_allows_http` (line 117) `static void test_realm_allows_http(void **state)` - *assert_int_equal(nr_route_for("https://example.com/", direct), NR_ROUTE_DIRECT); assert_int_equal(nr_route_for("https://example.com/", tor_no_torif...*
- `test_names` (line 125) `static void test_names(void **state)`
- `main` (line 139) `int main(void)`

#### `test_os_sandbox.c`
**Path:** `tests/test_os_sandbox.c`

**Functions:**
- `test_policy_allows_safe` (line 42) `static void test_policy_allows_safe(void **state)` - *#include <stdlib.h> #include <linux/audit.h> #include <sys/mman.h> #include <sys/prctl.h> #include <sys/resource.h> #include <sys/socket.h> #includ...*
- `test_policy_denies_dangerous` (line 50) `static void test_policy_denies_dangerous(void **state)`
- `test_policy_denies_io_uring` (line 64) `static void test_policy_denies_io_uring(void **state)` - *io_uring is a seccomp-bypass primitive (its IORING_OP_* operations are dispatched without re-entering the syscall entry point the BPF filters), so ...*
- `test_policy_size` (line 70) `static void test_policy_size(void **state)`
- `test_harden_kills_denied_syscall` (line 79) `static void test_harden_kills_denied_syscall(void **state)` - *(void)state; assert_false(os_policy_allows(__NR_io_uring_setup)); assert_false(os_policy_allows(__NR_io_uring_enter)); assert_false(os_policy_allow...*
- `test_harden_allows_permitted_syscall` (line 96) `static void test_harden_allows_permitted_syscall(void **state)` - *assert_true(pid >= 0); if (pid == 0) { if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98); (void)syscall(__NR_getpid); /* allowed: must survive (...*
- `test_harden_errno_denies_with_eperm` (line 112) `static void test_harden_errno_denies_with_eperm(void **state)` - *pid_t pid = fork(); assert_true(pid >= 0); if (pid == 0) { if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98); long p = syscall(__NR_getpid); _ex...*
- `test_harden_kills_io_uring_setup` (line 130) `static void test_harden_kills_io_uring_setup(void **state)` - *KILL: io_uring_setup (the mandatory entry point of the whole subsystem -- no ring exists without it) must be killed with SIGSYS. Proves a compromis...*
- `test_prot_allowed_wx` (line 151) `static void test_prot_allowed_wx(void **state)` - *Pure mirror: mmap/mprotect are members of the allowlist but lose the request * when it asks for PROT_EXEC; other syscalls keep their membership dec...*
- `test_harden_blocks_exec_mmap` (line 162) `static void test_harden_blocks_exec_mmap(void **state)` - *Pure mirror: mmap/mprotect are members of the allowlist but lose the request * when it asks for PROT_EXEC; other syscalls keep their membership dec...*
- `test_harden_blocks_exec_mprotect` (line 182) `static void test_harden_blocks_exec_mprotect(void **state)` - *long rw = syscall(__NR_mmap, (void *)0, (size_t)4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0); if (rw == -1) _exit(60); ...*
- `test_no_dump_undumpable` (line 214) `static void test_no_dump_undumpable(void **state)` - *Probed BEFORE seccomp so prctl/getrlimit are still reachable: after os_no_dump * the process is undumpable and the core-file limit is zero.*
- `test_landlock_abi_present` (line 232) `static void test_landlock_abi_present(void **state)` - *if (pid == 0) { if (os_no_dump() != OS_OK) _exit(98); if (prctl(PR_GET_DUMPABLE) != 0) _exit(70); struct rlimit rl; if (getrlimit(RLIMIT_CORE, &rl)...*
- `test_landlock_deny_all` (line 239) `static void test_landlock_deny_all(void **state)` - *int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFEXITED(st)); assert_int_equal(WEXITSTATUS(st), 42); } /* --- Landlock files...*
- `test_landlock_allow_read` (line 257) `static void test_landlock_allow_read(void **state)` - *allow-read: a read rule on a temp dir lets reads inside through and blocks * everything else.*
- `net_ns_inode` (line 304) `static unsigned long net_ns_inode(void)` - *The pure flag set: the worker requests an isolated network (no remote access), * a user namespace (the unprivileged enabler), and IPC + UTS isolati...*
- `suite` (line 313) `* suite (it is best-effort defense in depth), and on a host that allows them the
 * isolation mus...`
- `main` (line 334) `int main(void)`

**Macros:**
- `_GNU_SOURCE` (line 13)

#### `test_page_view.c`
**Path:** `tests/test_page_view.c`

**Functions:**
- `parse` (line 27) `static hp_document *parse(const char *html)` - *#include <stdint.h> #include <stdlib.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "box_style.h" #include "css.h" #includ...*
- `find_text` (line 35) `static const pv_run *find_text(const pv_view *v, const char *text)` - *#include "dom.h" #include "flex_layout.h" #include "html_parse.h" #include "page_view.h" /* Parse helper: aborts the test on parse failure. Caller ...*
- `find_image` (line 44) `static const pv_run *find_image(const pv_view *v, const char *src)` - *assert_non_null(doc); return doc; } /* Finds the i-th run whose collapsed text equals `text`; NULL if none. static const pv_run *find_text(const pv...*
- `test_new_is_empty` (line 53) `static void test_new_is_empty(void **state)` - *} return NULL; } /* Finds the first image run whose src equals `src`; NULL if none. static const pv_run *find_image(const pv_view *v, const char *s...*
- `test_append_copies_fields` (line 62) `static void test_append_copies_fields(void **state)`
- `test_append_image_copies_fields` (line 89) `static void test_append_image_copies_fields(void **state)`
- `test_append_image_null_args` (line 105) `static void test_append_image_null_args(void **state)`
- `test_append_transcodes_latin1` (line 121) `static void test_append_transcodes_latin1(void **state)` - *A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8, recovering accents from a ...*
- `test_append_transcodes_word` (line 131) `static void test_append_transcodes_word(void **state)` - *A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8, recovering accents from a ...*
- `test_append_transcodes_cp1252_quotes` (line 142) `static void test_append_transcodes_cp1252_quotes(void **state)` - *Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls): * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each).*
- `test_append_undefined_cp1252_is_qmark` (line 152) `static void test_append_undefined_cp1252_is_qmark(void **state)` - *Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls): * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each...*
- `test_append_valid_utf8_passthrough` (line 162) `static void test_append_valid_utf8_passthrough(void **state)` - *pv_free(v); } /* Undefined Windows-1252 positions (0x81 here) have no glyph and still fail to '?'. static void test_append_undefined_cp1252_is_qmar...*
- `test_append_null_args` (line 169) `static void test_append_null_args(void **state)`
- `test_free_null_and_double` (line 177) `static void test_free_null_and_double(void **state)`
- `test_build_null_args` (line 186) `static void test_build_null_args(void **state)` - *pv_view *v = pv_new(); assert_int_equal(pv_append(NULL, PV_TEXT, 0, 0, "x", NULL), PV_ERR_NULL_ARG); assert_int_equal(pv_append(v, PV_TEXT, 0, 0, N...*
- `test_build_plain_text` (line 195) `static void test_build_plain_text(void **state)`
- `test_build_heading_level` (line 208) `static void test_build_heading_level(void **state)`
- `test_build_inline_emphasis` (line 226) `static void test_build_inline_emphasis(void **state)` - *Inline emphasis: <b>/<strong> set bold, <i>/<em> set italic, on the wrapped run * only; surrounding text stays plain. Nested b>i is both.*
- `test_build_unordered_list` (line 267) `static void test_build_unordered_list(void **state)` - *Unordered list: each <li>'s first run is prefixed with a bullet marker and * carries list depth 1.*
- `test_build_ordered_and_nested_list` (line 285) `static void test_build_ordered_and_nested_list(void **state)` - *assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *a = find_text(v, "\xE2\x80\xA2 apple"); /* "* apple" assert_non_null(a); assert_int_equal...*
- `test_build_table_grid` (line 308) `static void test_build_table_grid(void **state)` - *A table becomes a grid: each cell is one collected text run sharing the table's * cont_id, with the column count = widest row. <th> cells are bold.*
- `test_build_table_flattens_cell` (line 342) `static void test_build_table_flattens_cell(void **state)` - *Cell inner markup is flattened into the cell's text and not re-emitted as a * separate run; the column count comes from the widest row.*
- `test_build_bgcolor_attr_fallback` (line 478) `static void test_build_bgcolor_attr_fallback(void **state)` - *Legacy bgcolor attribute is the background fallback when no CSS background won (like <font color> for the foreground). Hacker News' orange bar and ...*
- `test_build_nested_table_not_flattened` (line 493) `static void test_build_nested_table_not_flattened(void **state)`
- `test_build_link_with_href` (line 542) `static void test_build_link_with_href(void **state)`
- `test_build_block_break_between_paragraphs` (line 561) `static void test_build_block_break_between_paragraphs(void **state)`
- `test_build_skips_script_and_style` (line 573) `static void test_build_skips_script_and_style(void **state)`
- `test_build_inline_link_no_break_within_paragraph` (line 587) `static void test_build_inline_link_no_break_within_paragraph(void **state)`
- `test_build_image_with_dims` (line 605) `static void test_build_image_with_dims(void **state)`
- `test_build_image_unknown_dims` (line 622) `static void test_build_image_unknown_dims(void **state)`
- `test_build_image_px_and_tracking_dims` (line 637) `static void test_build_image_px_and_tracking_dims(void **state)`
- `test_build_image_in_skipped_subtree_ignored` (line 659) `static void test_build_image_in_skipped_subtree_ignored(void **state)`
- `test_build_noscript_shown_when_js_off` (line 672) `static void test_build_noscript_shown_when_js_off(void **state)`
- `test_build_noscript_hidden_when_js_on` (line 685) `static void test_build_noscript_hidden_when_js_on(void **state)`
- `test_build_image_without_src_ignored` (line 698) `static void test_build_image_without_src_ignored(void **state)`
- `test_build_empty_document` (line 712) `static void test_build_empty_document(void **state)`
- `test_set_color_model` (line 727) `static void test_set_color_model(void **state)` - *The pure model defaults a run's author color to -1 (none); pv_set_color sets it * on the most recent run and is a safe no-op on an empty view.*
- `test_build_author_color` (line 749) `static void test_build_author_color(void **state)` - *pv_build extracts the author foreground color: inline style "color:" and the legacy <font color>; the nearest ancestor that sets a color wins (inhe...*
- `test_build_combinator_selectors` (line 796) `static void test_build_combinator_selectors(void **state)` - *Descendant (`div p`) and child (`nav > a`) combinators from a <style> sheet * resolve through the real DOM ancestor chain.*
- `test_build_flex_container` (line 834) `static void test_build_flex_container(void **state)` - *pv_build records the nearest author flex/grid container per run: its id, display, and parsed gap/justify/columns. Runs of one container share the i...*
- `test_build_flex_wrap_align_row_gap` (line 872) `static void test_build_flex_wrap_align_row_gap(void **state)` - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) resolve through * the same cascade and thread through the same run fields as the ...*
- `test_build_flex_item_values` (line 913) `static void test_build_flex_item_values(void **state)` - *Stage 3: each run carries the flex ITEM's own resolved values (the direct child of the container on the run's ancestor chain: grow/shrink/basis x10...*
- `test_build_float_threading` (line 976) `static void test_build_float_threading(void **state)` - *float.md: a run inside a floated block carries that block's side + a stable float_id grouping all its runs; two floated siblings get distinct ids; ...*
- `test_build_flex_whitespace_not_item` (line 1020) `static void test_build_flex_whitespace_not_item(void **state)` - *CSS: whitespace directly inside a flex/grid container creates NO anonymous item (the source newlines between <p> items must not become layout colum...*
- `test_build_inline_whitespace_kept` (line 1076) `static void test_build_inline_whitespace_kept(void **state)` - *The separator space BETWEEN two inline elements is content, not an anonymous box: * it flows mid-block (no break) and must keep being emitted.*
- `test_build_cont_item_identity` (line 1098) `static void test_build_cont_item_identity(void **state)` - *Container-item identity: inline fragments of the SAME direct child share one cont_item ordinal (they are one flex/grid item and must flow together ...*
- `test_build_grid_container` (line 1163) `static void test_build_grid_container(void **state)`
- `test_build_grid_columns_from_sheet` (line 1205) `static void test_build_grid_columns_from_sheet(void **state)`
- `test_container_defaults` (line 1245) `static void test_container_defaults(void **state)` - *pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *x = find_text(v, "x"); assert_non_null(x); assert_int_equal(x->cont_di...*
- `test_build_box_leaf_inline` (line 1293) `static void test_build_box_leaf_inline(void **state)` - *A leaf block's own box: vertical margins override the UA, horizontal padding + * a fixed width inset and cap the content. No centering without marg...*
- `test_box_defaults_and_setter` (line 1316) `static void test_box_defaults_and_setter(void **state)` - *A run with no author box carries the neutral defaults; pv_set_box fixes the * last run and is NULL-safe.*
- `test_build_boxdeco_border_padding` (line 1346) `static void test_build_boxdeco_border_padding(void **state)` - *pv_view *w = pv_new(); assert_int_equal(pv_append(w, PV_TEXT, 0, 0, "x", NULL), PV_OK); pv_set_box(w, 12, 8, 500, 1, 40, 4); assert_int_equal(pv_at...*
- `test_build_boxdeco_shadow_outline` (line 1373) `static void test_build_boxdeco_shadow_outline(void **state)`
- `test_build_boxdeco_visibility_overflow_cursor` (line 1396) `static void test_build_boxdeco_visibility_overflow_cursor(void **state)`
- `test_build_cursor_alone_triggers_box` (line 1421) `static void test_build_cursor_alone_triggers_box(void **state)` - *A block that sets ONLY cursor (no other box property) still registers a box: the trigger for a box-def entry must include visibility/overflow/curso...*
- `test_build_boxdeco_dims_alone_trigger_box` (line 1476) `static void test_build_boxdeco_dims_alone_trigger_box(void **state)` - *2026-07-10: a block that sets ONLY min-width / min-height / max-height / height / aspect-ratio (no other box property) still registers a box: those...*
- `test_build_text_overflow_and_word_break` (line 1521) `static void test_build_text_overflow_and_word_break(void **state)` - *assert_int_equal(bd->box_h, 80); const pv_run *e = find_text(v, "E"); assert_non_null(e); const pv_box_def *be = pv_box_at(v, (size_t)e->block_id);...*
- `test_build_boxdeco_defaults_no_box` (line 1545) `static void test_build_boxdeco_defaults_no_box(void **state)`
- `test_build_boxdeco_sibling_blocks_distinct_ids` (line 1559) `static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state)`
- `test_build_boxdeco_shared_id_within_block` (line 1577) `static void test_build_boxdeco_shared_id_within_block(void **state)`
- `test_build_box_tree_textless_wrapper` (line 1640) `static void test_build_box_tree_textless_wrapper(void **state)` - *A text-less wrapper (a card whose only child is a body div with the text) owns no run, yet its box def must still exist and be the body box's paren...*
- `test_build_box_tree_empty_no_box` (line 1665) `static void test_build_box_tree_empty_no_box(void **state)` - *const pv_box_def *bd = pv_box_at(v, (size_t)body->block_id); assert_non_null(bd); assert_int_equal(bd->pad_t, 9); int card_id = bd->parent_id; asse...*
- `find_input` (line 1677) `static const pv_run *find_input(const pv_view *v, const char *name)` - */* A page with no author box has an empty box tree (default render byte-identical). static void test_build_box_tree_empty_no_box(void **state) { (v...*
- `test_build_search_form_get` (line 1686) `static void test_build_search_form_get(void **state)` - *pv_free(v); hp_document_free(doc); } /* Finds the first PV_INPUT run whose name equals `name`; NULL if none. static const pv_run *find_input(const ...*
- `test_build_form_post_and_hidden` (line 1719) `static void test_build_form_post_and_hidden(void **state)`
- `test_build_textarea_value` (line 1753) `static void test_build_textarea_value(void **state)`
- `test_build_control_without_form` (line 1769) `static void test_build_control_without_form(void **state)`
- `test_build_two_forms_distinct_groups` (line 1782) `static void test_build_two_forms_distinct_groups(void **state)`
- `test_build_pseudo_classes_and_siblings` (line 1842) `static void test_build_pseudo_classes_and_siblings(void **state)` - *Pseudo-classes + sibling combinators (Hito 23b-9) resolve through the real pipeline: page_view must feed the css engine each element's sibling cont...*
- `test_build_table_cell_author_styles` (line 1898) `static void test_build_table_cell_author_styles(void **state)` - *Collected DATA-table cells resolve author styles too (found via --dump-dom: the cell path never called resolve_context, so td{color} / zebra tr:nth...*
- `test_build_style_cache_distinct_siblings` (line 1958) `static void test_build_style_cache_distinct_siblings(void **state)` - *Regression for pv_style_cache (page_view.c): resolve_context()/in_hidden_subtree() now memoize cch_element_style() per element pointer so a shared ...*
- `test_build_text_align_and_font_size` (line 2000) `static void test_build_text_align_and_font_size(void **state)` - *text-align and font-size resolve into the new run fields, from both a <style> * sheet and inline style=.*
- `test_build_text_decoration` (line 2047) `static void test_build_text_decoration(void **state)` - *text-decoration resolves into text_decoration from a <style> sheet and inline * style=, inherits to descendant text, and an inline `none` drops a l...*
- `test_build_css_bold_and_inline_wins` (line 2070) `static void test_build_css_bold_and_inline_wins(void **state)` - *pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); assert_int_equal(find_text(v, "struck ")->text_decoration, CSS_DECO_LINE_THROUGH); a...*
- `test_build_display_none_hidden` (line 2089) `static void test_build_display_none_hidden(void **state)` - *"<p class='b'>strongish</p></body>"); pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *t = find_text(v, "t"); assert_no...*
- `test_build_styled_external_css` (line 2112) `static void test_build_styled_external_css(void **state)` - *External pre-fetched CSS (Hito 27) feeds the same cascade as the document's <style>: an extern rule applies (presentation and display:none alike); ...*
- `test_build_reader_skips_boilerplate` (line 2138) `static void test_build_reader_skips_boilerplate(void **state)` - *Reader (distraction-free) mode skips nav/header/footer/aside boilerplate but * keeps the main article content; with reader off, the boilerplate is ...*
- `test_set_node_id_model` (line 2166) `static void test_set_node_id_model(void **state)` - *The setter is a no-op when the view is empty or NULL, and it writes to the * most recently appended run otherwise.*
- `test_build_node_id_matches_dom_index` (line 2182) `static void test_build_node_id_matches_dom_index(void **state)` - *Stage 0 keystone: every emitted run carries the document-order element id of its source element, matching the id that dom_build assigns to the same...*
- `test_set_text_style_model` (line 2220) `static void test_set_text_style_model(void **state)`
- `test_build_pointer_events_on_box` (line 2246) `static void test_build_pointer_events_on_box(void **state)` - *pointer-events rides the box-def tree like cursor: a block whose style sets it becomes box-carrying and the def records the value, so the GUI hit-t...*
- `test_build_content_visibility_hidden_folds` (line 2265) `static void test_build_content_visibility_hidden_folds(void **state)` - *content-visibility: hidden folds into the box's visibility (skip paint, keep space) -- the documented visibility:collapse simplification. An explic...*
- `test_build_image_rendering_inherited` (line 2291) `static void test_build_image_rendering_inherited(void **state)` - *image-rendering inherits (nearest ancestor) and is stamped on IMAGE runs so the * painter can pick the nearest-neighbour filter.*
- `test_build_caret_color_inherited` (line 2310) `static void test_build_caret_color_inherited(void **state)` - *caret-color inherits and is stamped on INPUT runs so the painter can tint the * caret of a focused control. auto/unset stays -1.*
- `main` (line 2331) `int main(void)`

#### `test_pdf_export.c`
**Path:** `tests/test_pdf_export.c`

**Functions:**
- `pagination` (line 8) `* deterministic pagination (single/multi page, no row splitting, oversized row,
 * gap preservati...`
- `test_basename_maps_spaces_and_reserved` (line 30) `static void test_basename_maps_spaces_and_reserved(void **state)`
- `test_basename_rejects_path_separators` (line 38) `static void test_basename_rejects_path_separators(void **state)`
- `test_basename_neutralizes_traversal` (line 48) `static void test_basename_neutralizes_traversal(void **state)`
- `test_basename_dotdot_only_falls_back` (line 56) `static void test_basename_dotdot_only_falls_back(void **state)`
- `test_basename_trims_edges` (line 63) `static void test_basename_trims_edges(void **state)`
- `test_basename_collapses_underscores` (line 71) `static void test_basename_collapses_underscores(void **state)`
- `test_basename_control_bytes_mapped` (line 78) `static void test_basename_control_bytes_mapped(void **state)`
- `test_basename_non_ascii_mapped` (line 86) `static void test_basename_non_ascii_mapped(void **state)`
- `test_basename_empty_and_null_fall_back` (line 95) `static void test_basename_empty_and_null_fall_back(void **state)`
- `test_basename_all_separators_fall_back` (line 104) `static void test_basename_all_separators_fall_back(void **state)`
- `test_basename_length_bound` (line 111) `static void test_basename_length_bound(void **state)`
- `test_basename_null_out_and_zero_size` (line 122) `static void test_basename_null_out_and_zero_size(void **state)`
- `test_basename_overflow_fails_closed` (line 129) `static void test_basename_overflow_fails_closed(void **state)`
- `test_build_path_basic` (line 138) `static void test_build_path_basic(void **state)` - *(void)state; char out[8]; assert_int_equal(pe_safe_basename("x", NULL, sizeof out), PE_ERR_NULL_ARG); assert_int_equal(pe_safe_basename("x", out, 0...*
- `test_build_path_trailing_slash` (line 145) `static void test_build_path_trailing_slash(void **state)`
- `test_build_path_hostile_title_contained` (line 152) `static void test_build_path_hostile_title_contained(void **state)`
- `test_build_path_empty_title_fallback` (line 161) `static void test_build_path_empty_title_fallback(void **state)`
- `test_build_path_overflow_fails_closed` (line 168) `static void test_build_path_overflow_fails_closed(void **state)`
- `test_build_path_null_args` (line 175) `static void test_build_path_null_args(void **state)`
- `test_build_path_ext_png` (line 185) `static void test_build_path_ext_png(void **state)` - *char out[16]; assert_int_equal(pe_build_path("/a/very/long/dir", "name", out, sizeof out), PE_ERR_OVERFLOW); assert_string_equal(out, ""); } static...*
- `test_build_path_ext_null_ext` (line 193) `static void test_build_path_ext_null_ext(void **state)`
- `test_build_path_ext_hostile_title_contained` (line 201) `static void test_build_path_ext_hostile_title_contained(void **state)`
- `test_build_path_ext_overflow_fails_closed` (line 212) `static void test_build_path_ext_overflow_fails_closed(void **state)`
- `test_paginate_single_page` (line 222) `static void test_paginate_single_page(void **state)` - *PE_EXT_PNG, out, sizeof out), PE_OK); assert_string_equal(out, "/safe/dir/etc_passwd.png"); assert_null(strstr(out + strlen("/safe/dir"), "..")); }...*
- `test_paginate_breaks_without_splitting` (line 237) `static void test_paginate_breaks_without_splitting(void **state)`
- `test_paginate_oversized_row_not_split` (line 251) `static void test_paginate_oversized_row_not_split(void **state)`
- `test_paginate_preserves_gaps` (line 263) `static void test_paginate_preserves_gaps(void **state)`
- `test_paginate_invalid_args` (line 275) `static void test_paginate_invalid_args(void **state)`
- `main` (line 289) `int main(void)`

#### `test_prefetch.c`
**Path:** `tests/test_prefetch.c`
**File Doc:** *Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool.*

**Functions:**
- `test_scan_null_args` (line 21) `static void test_scan_null_args(void **state)` - *#include <stdarg.h> #include <stddef.h> #include <setjmp.h> #include <stdint.h> #include <cmocka.h> #include <pthread.h> #include <stdlib.h> #inclu...*
- `test_scan_basic_stylesheet_and_script` (line 31) `static void test_scan_basic_stylesheet_and_script(void **state)`
- `test_scan_ref_cap` (line 104) `static void test_scan_ref_cap(void **state)` - *(void)state; const char *html = "<!-- <link rel=stylesheet href=commented.css> -->" "<script>document.write('<link rel=stylesheet href=fromjs.css>'...*
- `fake_fetch` (line 132) `static int fake_fetch(void *vctx, const char *method, const char *url,
                      cons...`
- `test_pool_parallel_fetch_and_take` (line 150) `static void test_pool_parallel_fetch_and_take(void **state)`
- `test_pool_miss_consume_and_failure` (line 182) `static void test_pool_miss_consume_and_failure(void **state)`
- `test_pool_finish_unconsumed_and_empty` (line 226) `static void test_pool_finish_unconsumed_and_empty(void **state)` - *finish() with results nobody took must free them all (ASan-verified) and be * idempotent. An empty pool is a no-op that reports -1 from start.*
- `test_pooled_fetch_adapter` (line 247) `static void test_pooled_fetch_adapter(void **state)` - *The shared cache-first adapter: pooled GETs hit the pool, everything else * (POST, miss, no pool) falls through to the inner fetcher exactly once.*
- `main` (line 286) `int main(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 4)

**Structs:**
- `fake_ctx` (line 124) - *Deterministic fake fetcher: body echoes the URL so take() can verify the per-URL mapping; a barrier proves REAL concurrency (the test only passes i...*

#### `test_prefs.c`
**Path:** `tests/test_prefs.c`

**Functions:**
- `test_init_defaults` (line 24) `static void test_init_defaults(void **state)` - *#include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <stdio.h> #include <stdlib.h> #include <setjmp.h> #include <string.h> #include...*
- `test_roundtrip` (line 49) `static void test_roundtrip(void **state)` - *assert_int_equal(p.tor, 0); assert_int_equal(p.i2p, 0); assert_int_equal(p.torify, 0); assert_int_equal(p.zoom_pct, 100); assert_int_equal(p.rememb...*
- `test_parse_bad_magic` (line 109) `static void test_parse_bad_magic(void **state)` - *assert_string_equal(q.bookmarks[0].url, "https://example.com/a"); assert_string_equal(q.bookmarks[0].title, "Example A"); assert_string_equal(q.boo...*
- `test_parse_too_large` (line 125) `static void test_parse_too_large(void **state)`
- `test_parse_unknown_and_malformed_skipped` (line 134) `static void test_parse_unknown_and_malformed_skipped(void **state)`
- `test_parse_clamps_out_of_range` (line 156) `static void test_parse_clamps_out_of_range(void **state)`
- `test_invalid_urls_rejected` (line 178) `static void test_invalid_urls_rejected(void **state)` - *"js=7\n" "zoom=9999\n" "images=5\n" "tor=-3\n"; assert_int_equal(prefs_parse(text, strlen(text), &p), PREFS_OK); assert_int_equal(p.theme_mode, 0);...*
- `test_hostile_title_cleaned` (line 206) `static void test_hostile_title_cleaned(void **state)` - *PREFS_ERR_INVALID); char big[PREFS_MAX_URL + 8]; memset(big, 'a', sizeof big - 1); big[sizeof big - 1] = '\0'; assert_int_equal(prefs_bookmark_togg...*
- `test_bookmark_toggle_and_cap` (line 236) `static void test_bookmark_toggle_and_cap(void **state)` - *long_title[n++] = (char)0xA1; } long_title[n] = '\0'; assert_int_equal(prefs_bookmark_toggle(&p, "https://y.test/", long_title, &added), PREFS_OK);...*
- `test_history_dedup_and_evict` (line 264) `static void test_history_dedup_and_evict(void **state)` - *assert_int_equal(p.bookmarks_len, 0); char url[64]; for (size_t i = 0; i < PREFS_MAX_BOOKMARKS; ++i) { snprintf(url, sizeof url, "https://cap.test/...*
- `test_suggest_priorities` (line 289) `static void test_suggest_priorities(void **state)` - *assert_string_equal(p.history[0], "https://a.test/"); assert_string_equal(p.history[1], "https://b.test/"); char url[64]; for (size_t i = 0; i < PR...*
- `test_bookmarks_page_escapes` (line 344) `static void test_bookmarks_page_escapes(void **state)` - */* Rows too small for a URL: that URL is skipped, no overflow. char tiny[6][16]; n = prefs_suggest(&p, "wiki", (char *)tiny, sizeof tiny[0], 6); as...*
- `test_format_null_args` (line 381) `static void test_format_null_args(void **state)` - */* Empty state still yields a valid page. prefs_state q; prefs_init(&q); assert_int_equal(prefs_bookmarks_page(&q, &html, &len), PREFS_OK); assert_...*
- `main` (line 393) `int main(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 8)

#### `test_profile.c`
**Path:** `tests/test_profile.c`

**Functions:**
- `setup` (line 29) `static int setup(void **state)`
- `teardown` (line 38) `static int teardown(void **state)`
- `path_of` (line 59) `static void path_of(const fixture *f, const char *name, char *out, size_t cap)`
- `file_size` (line 63) `static size_t file_size(const char *path)`
- `test_open_creates_keyfile` (line 71) `static void test_open_creates_keyfile(void **state)` - *return 0; } static void path_of(const fixture *f, const char *name, char *out, size_t cap) { snprintf(out, cap, "%s/%s", f->dir, name); } static si...*
- `test_open_rejects_corrupt_keyfile` (line 88) `static void test_open_rejects_corrupt_keyfile(void **state)`
- `test_open_bad_dir` (line 102) `static void test_open_bad_dir(void **state)`
- `test_first_launch_defaults` (line 114) `static void test_first_launch_defaults(void **state)` - *assert_int_equal(file_size(kp), 5); } static void test_open_bad_dir(void **state) { (void)state; profile_ctx ctx; assert_int_equal(profile_open(&ct...*
- `test_save_load_roundtrip_two_ctx` (line 127) `static void test_save_load_roundtrip_two_ctx(void **state)`
- `test_nothing_readable_on_disk` (line 173) `static void test_nothing_readable_on_disk(void **state)` - */* prefs.bin is 0600. char pp[512]; path_of(f, PROFILE_PREFS_FILE, pp, sizeof pp); struct stat st; assert_int_equal(stat(pp, &st), 0); assert_int_e...*
- `test_tampered_blob_auth_fails` (line 203) `static void test_tampered_blob_auth_fails(void **state)` - *assert_non_null(fp); static uint8_t blob[1 << 20]; size_t blen = fread(blob, 1, sizeof blob, fp); fclose(fp); assert_true(blen > 0); assert_null(me...*
- `test_foreign_key_auth_fails` (line 235) `static void test_foreign_key_auth_fails(void **state)`
- `test_null_and_not_ready` (line 260) `static void test_null_and_not_ready(void **state)` - *char kp[512]; path_of(f, PROFILE_KEY_FILE, kp, sizeof kp); assert_int_equal(unlink(kp), 0); profile_ctx other; assert_int_equal(profile_open(&other...*
- `main` (line 277) `int main(void)`

**Macros:**
- `_GNU_SOURCE` (line 8)

**Structs:**
- `fixture` (line 28)

#### `test_render_doc.c`
**Path:** `tests/test_render_doc.c`

**Functions:**
- `caps_images_on` (line 27) `static rdp_caps caps_images_on(void)`
- `first_kind` (line 35) `static const rd_block *first_kind(const rd_doc *d, rd_kind k)` - *#include "flex_layout.h" #include "page_view.h" #include "render_doc.h" #include "render_policy.h" static const char TOP[] = "https://example.com/"...*
- `test_build_null_out` (line 43) `static void test_build_null_out(void **state)` - *rdp_caps c = rdp_caps_safe(); c.images = true; return c; } /* First block of a given kind, or NULL. static const rd_block *first_kind(const rd_doc ...*
- `test_build_null_view_is_empty` (line 50) `static void test_build_null_view_is_empty(void **state)`
- `test_heading_paragraph_link` (line 63) `static void test_heading_paragraph_link(void **state)` - *} static void test_build_null_view_is_empty(void **state) { (void)state; rd_doc *d = NULL; assert_int_equal(rd_build(NULL, rdp_caps_safe(), TOP, &d...*
- `test_emphasis_propagates` (line 94) `static void test_emphasis_propagates(void **state)` - *Inline emphasis flags (bold/italic) carry from the run to the block, on text and * link blocks alike, and are independent of caps (structure, not a...*
- `test_image_off_emits_notice_and_blocked` (line 124) `static void test_image_off_emits_notice_and_blocked(void **state)` - *assert_int_equal(rd_at(d, 0)->italic, 0); assert_int_equal(rd_at(d, 1)->bold, 1); assert_int_equal(rd_at(d, 1)->italic, 0); assert_int_equal(rd_at(...*
- `test_no_images_no_notice` (line 149) `static void test_no_images_no_notice(void **state)`
- `test_image_on_allows_normal` (line 163) `static void test_image_on_allows_normal(void **state)` - *static void test_no_images_no_notice(void **state) { (void)state; pv_view *v = pv_new(); assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "just text", ...*
- `test_image_on_resolves_relative_src` (line 182) `static void test_image_on_resolves_relative_src(void **state)` - *A relative src ("/logo.png") is not an invalid URL: it resolves against the top-level document. The decision must allow it and the stored href must...*
- `test_image_on_resolves_doc_relative_src` (line 198) `static void test_image_on_resolves_doc_relative_src(void **state)` - *A document-relative src ("logo.png", no leading slash) resolves against the * page's directory, too.*
- `test_image_on_blocks_tracker` (line 211) `static void test_image_on_blocks_tracker(void **state)`
- `test_image_on_blocks_non_https` (line 224) `static void test_image_on_blocks_non_https(void **state)`
- `test_href_sanitised` (line 254) `static void test_href_sanitised(void **state)` - *static void test_image_on_local_top_fails_closed(void **state) { (void)state; pv_view *v = pv_new(); assert_int_equal(pv_append_image(v, 0, 0, "", ...*
- `test_kind_name_total` (line 271) `static void test_kind_name_total(void **state)` - *pv_view *v = pv_new(); /* pv_append stores the href verbatim; render_doc must make it paint-safe. const char bad[] = { 'h', 't', 't', 'p', 's', ':'...*
- `test_image_label_total` (line 281) `static void test_image_label_total(void **state)`
- `test_free_null_and_double` (line 294) `static void test_free_null_and_double(void **state)`
- `test_author_color_gated_by_css` (line 305) `static void test_author_color_gated_by_css(void **state)` - *Author colors are presentation gated by caps.css (Privacy by Default off): the * run's fg_rgb is dropped to -1 unless author CSS is enabled.*
- `test_text_overflow_word_break_gated_by_css` (line 335) `static void test_text_overflow_word_break_gated_by_css(void **state)` - */* CSS on: both colors carried through. rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = ...*
- `test_text_ext_2026_07_10_batch_gated_by_css` (line 370) `static void test_text_ext_2026_07_10_batch_gated_by_css(void **state)` - *2026-07-10 batch: tab_size / direction / font_variant / list_style_pos travel the same caps.css gate as the other text extensions (off by default; ...*
- `test_image_rendering_gated_on_image` (line 410) `static void test_image_rendering_gated_on_image(void **state)` - *2026-07-10 wiring batch: image_rendering reaches RD_IMAGE only with caps.css * (presentation; it also needs caps.images to matter, but the gate is ...*
- `test_caret_color_gated_on_input` (line 439) `static void test_caret_color_gated_on_input(void **state)` - *rd_free(d); rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); img = first_kind(d, RD_IMAGE); a...*
- `test_input_passthrough` (line 468) `static void test_input_passthrough(void **state)` - *rd_free(d); rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); in = first_kind(d, RD_INPUT); as...*
- `test_input_label_total` (line 503) `static void test_input_label_total(void **state)`
- `test_container_carried_by_default` (line 517) `static void test_container_carried_by_default(void **state)` - *The author flex/grid container annotation is structure, not styling: it is * carried regardless of caps.css (layout applies by default), with its p...*
- `test_cont_item_carried_by_default` (line 549) `static void test_cont_item_carried_by_default(void **state)` - *rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = first_kind(d, RD_PARAGRAPH); assert_non_...*
- `test_float_carried_by_default` (line 582) `static void test_float_carried_by_default(void **state)` - *float.md: float_side/float_id/float_clear are layout structure, carried regardless of * caps.css; a run that never got pv_set_float keeps the unset...*
- `test_flex_item_carried_by_default` (line 614) `static void test_flex_item_carried_by_default(void **state)`
- `test_flex_wrap_align_row_gap_carried_by_default` (line 663) `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)` - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) are structure * like the rest of the cont_ and flex_ fields: carried regardless o...*
- `test_block_tag_total` (line 694) `static void test_block_tag_total(void **state)`
- `test_node_id_carried_by_default` (line 731) `static void test_node_id_carried_by_default(void **state)` - *Stage 0 keystone: node_id is structure, so it is copied regardless of the * caps.css gate (unlike block_id, which exists only when author styling i...*
- `main` (line 743) `int main(void)`

#### `test_render_policy.c`
**Path:** `tests/test_render_policy.c`

**Functions:**
- `test_caps_safe_is_all_off` (line 17) `static void test_caps_safe_is_all_off(void **state)` - *Pure policy logic: no I/O. Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> ...*
- `test_caps_zero_value_is_safe` (line 25) `static void test_caps_zero_value_is_safe(void **state)`
- `test_tracking_pixel_tiny` (line 36) `static void test_tracking_pixel_tiny(void **state)` - *The zero value of the struct must equal the safe baseline: insecure config * is not representable as a default. rdp_caps z = {0}; rdp_caps s = rdp_...*
- `test_tracking_pixel_zero_area` (line 44) `static void test_tracking_pixel_zero_area(void **state)`
- `test_tracking_pixel_normal` (line 51) `static void test_tracking_pixel_normal(void **state)`
- `test_tracking_pixel_unknown` (line 61) `static void test_tracking_pixel_unknown(void **state)`
- `test_image_disabled_by_default` (line 71) `static void test_image_disabled_by_default(void **state)` - *classified as a tracker by the size heuristic. assert_int_equal(rdp_is_tracking_pixel(1, 300), 0); assert_int_equal(rdp_is_tracking_pixel(800, 600)...*
- `caps_images_on` (line 89) `static rdp_caps caps_images_on(void)` - *Images off: even a perfectly valid same-site image is blocked, and the URL * is not even consulted (a bogus URL still yields BLOCK_DISABLED). asser...*
- `test_image_allow_same_site` (line 95) `static void test_image_allow_same_site(void **state)`
- `test_image_allow_cross_site_when_enabled` (line 107) `static void test_image_allow_cross_site_when_enabled(void **state)`
- `test_image_block_tracker` (line 118) `static void test_image_block_tracker(void **state)`
- `test_image_block_scheme` (line 133) `static void test_image_block_scheme(void **state)`
- `test_image_block_invalid` (line 141) `static void test_image_block_invalid(void **state)`
- `test_image_disabled_precedence` (line 164) `static void test_image_disabled_precedence(void **state)` - *Disabled capability beats every other reason: a tracker URL with images off is * reported as DISABLED, not TRACKER (the gate short-circuits first).*
- `test_img_reason_total_and_stable` (line 173) `static void test_img_reason_total_and_stable(void **state)` - *Disabled capability beats every other reason: a tracker URL with images off is * reported as DISABLED, not TRACKER (the gate short-circuits first)....*
- `test_images_warning_present` (line 188) `static void test_images_warning_present(void **state)`
- `main` (line 197) `int main(void)`

#### `test_renderer.c`
**Path:** `tests/test_renderer.c`

**Functions:**
- `test_render_basic` (line 26) `static void test_render_basic(void **state)`
- `test_render_strips_script` (line 38) `static void test_render_strips_script(void **state)`
- `test_render_null_args` (line 47) `static void test_render_null_args(void **state)`
- `test_render_too_large` (line 54) `static void test_render_too_large(void **state)`
- `test_render_binary_does_not_crash_parent` (line 63) `static void test_render_binary_does_not_crash_parent(void **state)` - *(void)state; rd_result r; assert_int_equal(rd_render_html(NULL, 10, &r), RD_ERR_NULL_ARG); assert_int_equal(rd_render_html("x", 1, NULL), RD_ERR_NU...*
- `test_render_multiple_independent` (line 74) `static void test_render_multiple_independent(void **state)` - *} /* The parent must survive arbitrary/binary input: isolation in action. static void test_render_binary_does_not_crash_parent(void **state) { (voi...*
- `test_result_free_null_and_double` (line 83) `static void test_result_free_null_and_double(void **state)`
- `main` (line 92) `int main(void)`

#### `test_request_policy.c`
**Path:** `tests/test_request_policy.c`

**Functions:**
- `test_host_of_basic` (line 17) `static void test_host_of_basic(void **state)` - *Pure policy logic: no I/O. Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> ...*
- `test_host_of_invalid` (line 28) `static void test_host_of_invalid(void **state)`
- `test_host_of_overflow` (line 36) `static void test_host_of_overflow(void **state)`
- `test_site_of` (line 44) `static void test_site_of(void **state)` - *(void)state; char h[256]; assert_int_equal(rp_host_of("example.com", h, sizeof h), -1); /* no scheme assert_int_equal(rp_host_of("https:///path", h...*
- `test_site_of_multi_suffix` (line 57) `static void test_site_of_multi_suffix(void **state)`
- `test_site_of_psl` (line 70) `static void test_site_of_psl(void **state)` - *} static void test_site_of_multi_suffix(void **state) { (void)state; char s[256]; assert_int_equal(rp_site_of("example.co.uk", s, sizeof s), 0); as...*
- `test_same_site` (line 90) `static void test_same_site(void **state)` - *assert_int_equal(rp_site_of("a.blog.github.io", s, sizeof s), 0); assert_string_equal(s, "blog.github.io"); /* Wildcard rule "*.ck": bar.ck is the ...*
- `test_evaluate_allow_same_site` (line 104) `static void test_evaluate_allow_same_site(void **state)` - *static void test_same_site(void **state) { (void)state; assert_int_equal(rp_same_site("https://example.com/", "https://example.com/a"), 1); assert_...*
- `test_evaluate_block_third_party` (line 111) `static void test_evaluate_block_third_party(void **state)`
- `test_evaluate_block_scheme` (line 119) `static void test_evaluate_block_scheme(void **state)`
- `test_evaluate_block_invalid` (line 127) `static void test_evaluate_block_invalid(void **state)`
- `main` (line 138) `int main(void)`

#### `test_secure_fetch.c`
**Path:** `tests/test_secure_fetch.c`

**Functions:**
- `test_config_blend_fields_default_null` (line 33) `static void test_config_blend_fields_default_null(void **state)`
- `test_user_agent_default_when_unset` (line 45) `static void test_user_agent_default_when_unset(void **state)` - *assert_null(c.user_agent); /* NULL => resolved to the default at request time } static void test_config_blend_fields_default_null(void **state) { (...*
- `test_user_agent_uses_override` (line 51) `static void test_user_agent_uses_override(void **state)`
- `test_url_rejects_null` (line 59) `static void test_url_rejects_null(void **state)` - *static void test_user_agent_default_when_unset(void **state) { (void)state; assert_string_equal(sf_user_agent_or_default(NULL), SF_DEFAULT_USER_AGE...*
- `test_url_rejects_plain_http` (line 64) `static void test_url_rejects_plain_http(void **state)`
- `test_url_rejects_dangerous_schemes` (line 69) `static void test_url_rejects_dangerous_schemes(void **state)`
- `test_url_accepts_https` (line 79) `static void test_url_accepts_https(void **state)`
- `test_tls_rejects_12` (line 87) `static void test_tls_rejects_12(void **state)` - *assert_int_equal(sf_validate_url("javascript:alert(1)"), SF_ERR_INVALID_URL); assert_int_equal(sf_validate_url("data:text/html,<b>x"), SF_ERR_INVAL...*
- `test_tls_rejects_older_and_garbage` (line 92) `static void test_tls_rejects_older_and_garbage(void **state)`
- `test_tls_accepts_13` (line 101) `static void test_tls_accepts_13(void **state)`
- `test_group_rejects_classical` (line 108) `static void test_group_rejects_classical(void **state)` - *(void)state; assert_int_equal(sf_check_tls_version("TLSv1.1"), SF_ERR_TLS_VERSION); assert_int_equal(sf_check_tls_version("TLSv1"), SF_ERR_TLS_VERS...*
- `test_group_rejects_pure_pq` (line 115) `static void test_group_rejects_pure_pq(void **state)`
- `test_group_accepts_hybrid` (line 122) `static void test_group_accepts_hybrid(void **state)`
- `test_chain_strict_rejects_classical` (line 131) `static void test_chain_strict_rejects_classical(void **state)` - *(void)state; /* Pure PQ has no classical fallback: rejected by design. assert_int_equal(sf_check_group_is_pq("MLKEM768"), SF_ERR_KEM_NOT_PQ); asser...*
- `test_chain_strict_accepts_pq` (line 140) `static void test_chain_strict_accepts_pq(void **state)`
- `test_chain_hybrid_allows_classical` (line 148) `static void test_chain_hybrid_allows_classical(void **state)`
- `test_chain_rejects_sha1_in_any_policy` (line 156) `static void test_chain_rejects_sha1_in_any_policy(void **state)`
- `test_chain_permissive_allows_weak_certs` (line 165) `static void test_chain_permissive_allows_weak_certs(void **state)`
- `test_chain_rejects_weak_rsa` (line 178) `static void test_chain_rejects_weak_rsa(void **state)`
- `test_chain_rejects_null` (line 186) `static void test_chain_rejects_null(void **state)`
- `test_enforce_all_good_hybrid` (line 200) `static void test_enforce_all_good_hybrid(void **state)`
- `test_enforce_checks_version_first` (line 206) `static void test_enforce_checks_version_first(void **state)`
- `test_enforce_checks_group_after_version` (line 215) `static void test_enforce_checks_group_after_version(void **state)`
- `test_enforce_fails_closed_on_null_chain` (line 223) `static void test_enforce_fails_closed_on_null_chain(void **state)`
- `test_enforce_strict_requires_pq_chain` (line 230) `static void test_enforce_strict_requires_pq_chain(void **state)`
- `test_enforce_allow_classical_ke` (line 243) `static void test_enforce_allow_classical_ke(void **state)`
- `test_enforce_allowlisted_insecure` (line 263) `static void test_enforce_allowlisted_insecure(void **state)` - *The allowlist override: the user's sovereign per-host escape hatch for sites below Freedom's elevated standard. Tolerates TLS 1.2, a classical KE, ...*
- `test_redirect_code_recognizes_3xx` (line 284) `static void test_redirect_code_recognizes_3xx(void **state)` - *But authenticity is never waived: a non-inspectable chain still fails closed, * and anything below TLS 1.2 is still refused. assert_int_equal(sf_en...*
- `test_redirect_code_rejects_others` (line 293) `static void test_redirect_code_rejects_others(void **state)`
- `test_location_parses_value` (line 304) `static void test_location_parses_value(void **state)` - *assert_true(sf_is_redirect_code(307)); assert_true(sf_is_redirect_code(308)); } static void test_redirect_code_rejects_others(void **state) { (void...*
- `test_location_is_case_insensitive_and_trims` (line 312) `static void test_location_is_case_insensitive_and_trims(void **state)`
- `test_location_rejects_non_location_and_empty` (line 322) `static void test_location_rejects_non_location_and_empty(void **state)`
- `test_location_rejects_overflow` (line 334) `static void test_location_rejects_overflow(void **state)`
- `test_resolve_absolute_https` (line 343) `static void test_resolve_absolute_https(void **state)` - *SF_ERR_INVALID_URL); assert_int_equal(sf_parse_location_header("Location:    \r\n", out, sizeof out), SF_ERR_INVALID_URL); assert_int_equal(sf_pars...*
- `test_resolve_refuses_http_downgrade` (line 351) `static void test_resolve_refuses_http_downgrade(void **state)`
- `test_resolve_refuses_dangerous_schemes` (line 358) `static void test_resolve_refuses_dangerous_schemes(void **state)`
- `test_resolve_scheme_relative` (line 369) `static void test_resolve_scheme_relative(void **state)`
- `test_resolve_absolute_path` (line 377) `static void test_resolve_absolute_path(void **state)`
- `test_resolve_relative_path` (line 389) `static void test_resolve_relative_path(void **state)`
- `test_resolve_null_args` (line 401) `static void test_resolve_null_args(void **state)`
- `test_response_free_on_zeroed` (line 412) `static void test_response_free_on_zeroed(void **state)` - *out, sizeof out), SF_OK); assert_string_equal(out, "https://h.example/foo"); } static void test_resolve_null_args(void **state) { (void)state; char...*
- `test_response_free_releases_location` (line 421) `static void test_response_free_releases_location(void **state)`
- `test_get_follow_null_args` (line 435) `static void test_get_follow_null_args(void **state)`
- `test_get_null_args` (line 444) `static void test_get_null_args(void **state)`
- `test_post_null_args` (line 453) `static void test_post_null_args(void **state)`
- `test_cookie_line_matches_pure` (line 479) `static void test_cookie_line_matches_pure(void **state)` - *The URL scheme is validated before any socket is opened, so a downgrade is * rejected without network (Secure by Default: an insecure POST is unrep...*
- `test_cookie_jar_put_and_header` (line 515) `static void test_cookie_jar_put_and_header(void **state)`
- `main` (line 531) `int main(void)`

#### `test_tab.c`
**Path:** `tests/test_tab.c`

**Functions:**
- `setup_loaded` (line 40) `static int setup_loaded(void **state)`
- `teardown` (line 51) `static int teardown(void **state)`
- `expect_eval` (line 62) `static void expect_eval(tab *t, const char *js, const char *expected)` - *state = f; return 0; } static int teardown(void **state) { fixture *f = (fixture *)*state; if (f != NULL) { tab_close(f->t); free(f); } return 0; }...*
- `test_open_close` (line 72) `static void test_open_close(void **state)` - *return 0; } /* Evaluates js and asserts the (non-exception) string result. static void expect_eval(tab *t, const char *js, const char *expected) { ...*
- `test_open_null` (line 82) `static void test_open_null(void **state)`
- `test_load_basic` (line 89) `static void test_load_basic(void **state)` - *tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); assert_non_null(t); assert_true(tab_alive(t)); assert_true(tab_child_pid(t) > 0); tab_close(...*
- `test_load_returns_view_with_link` (line 107) `static void test_load_returns_view_with_link(void **state)` - *The structured display list must survive the IPC round-trip: a heading and a * link with its href arrive intact in p.view.*
- `test_load_returns_image_run` (line 134) `static void test_load_returns_image_run(void **state)` - *An <img> must survive the IPC round-trip as a PV_IMAGE run carrying its src, * alt text, and declared dimensions (so render_policy can later gate it).*
- `test_load_carries_author_color` (line 165) `static void test_load_carries_author_color(void **state)` - *An author color extracted in the confined child must survive the IPC round-trip * as the run's fg_rgb (so the parent can apply it once CSS is enabl...*
- `test_load_carries_flex_item` (line 192) `static void test_load_carries_flex_item(void **state)` - *Stage 3: the per-item flex values resolved by the worker must survive the IPC * round-trip (write_view/read_view), so the GUI's flex layout can hon...*
- `test_load_carries_flex_wrap_align_row_gap` (line 236) `static void test_load_carries_flex_wrap_align_row_gap(void **state)` - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) survive the worker round-trip (write_view/read_view serialize the 4 new fields in...*
- `test_load_carries_float` (line 276) `static void test_load_carries_float(void **state)` - *float.md over IPC: float_side/float_id/float_clear survive the worker round-trip * (write_view/read_view serialize them in the same order on both s...*
- `test_load_carries_visibility_overflow_cursor_and_text_wrap` (line 319) `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` - *visibility/overflow/cursor (box-level) and text-overflow/word-break (run-level) survive the worker round-trip -- write_view/read_view serialize the...*
- `test_load_carries_node_id` (line 403) `static void test_load_carries_node_id(void **state)` - *Stage 0 keystone: the document-order element id assigned by the child must survive the IPC round-trip, so the parent can map a painted block back t...*
- `test_click_runs_handler_and_returns_view` (line 437) `static void test_click_runs_handler_and_returns_view(void **state)` - *Stage 4 dispatcher: a click on a node with a JS handler mutates the DOM, and the * new view is returned over IPC with the mutation reflected.*
- `test_tick_fires_delayed_timer` (line 480) `static void test_tick_fires_delayed_timer(void **state)` - *Real async timers (2026-07-11): a setTimeout with a delay does NOT fire on the load pump; the load response reports the smallest pending delay; tab...*
- `test_tick_interval_rearms` (line 516) `static void test_tick_interval_rearms(void **state)`
- `test_load_carries_box_decoration` (line 547) `static void test_load_carries_box_decoration(void **state)` - *Box-engine identity + decoration resolved in the confined child must survive the * IPC round-trip (write_view/read_view symmetry for the new fields).*
- `test_load_carries_box_tree` (line 583) `static void test_load_carries_box_tree(void **state)` - *The box TREE (Step D) — the box-definition list with its parent links — must survive the IPC round-trip: a nested box parsed in the confined child ...*
- `test_load_strips_script` (line 662) `static void test_load_strips_script(void **state)`
- `test_load_no_session_cookies_when_untrusted` (line 733) `static void test_load_no_session_cookies_when_untrusted(void **state)` - *Untrusted host (net off): the cookie jar stays disabled -- document.cookie is '' even * if the parent were to seed it, and nothing is dumped back (...*
- `test_load_ex_builds_dom_and_fires_onload` (line 755) `static void test_load_ex_builds_dom_and_fires_onload(void **state)` - *Live JS construction (Hito 20c): a script builds a node and an onload handler * mutates it; both must be reflected in the worker's returned view.*
- `test_load_ex_inner_html_renders` (line 783) `static void test_load_ex_inner_html_renders(void **state)` - *innerHTML (Hito 20d): a script replaces a container's markup; the parsed content * renders, and ephemeral storage / empty cookie do not break the s...*
- `console_find` (line 834) `static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle)` - *assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK); assert_non_null(p.title); assert_string_equal(p.title, "Old"); int saw_before = 0; for ...*
- `test_load_captures_console_and_error` (line 844) `static void test_load_captures_console_and_error(void **state)` - *Freebug (FB-1): with run_js, the page's console.* output and any uncaught script * error are captured and delivered to the parent in tab_page.console.*
- `test_load_isolates_script_errors` (line 871) `static void test_load_isolates_script_errors(void **state)` - *Per-script isolation (browser semantics): an uncaught error in the FIRST inline <script> must NOT abort later scripts. Before this, all scripts wer...*
- `test_load_error_carries_location` (line 899) `static void test_load_error_carries_location(void **state)` - *FB error locations (Hito 24): an uncaught error reports the inline script name ("inline #N") plus the line and column of its throw site, carried ac...*
- `test_load_element_wrapper_idioms` (line 925) `static void test_load_element_wrapper_idioms(void **state)` - *Element-wrapper completeness (Hito 24): the exact google.com startup idioms that previously threw -- dataset.X, hasAttribute, removeAttribute, src....*
- `test_load_document_fonts_stub` (line 955) `static void test_load_document_fonts_stub(void **state)` - *document.fonts stub: a feature-detecting script that calls document.fonts.load()/ .check() must not throw (this exact call -- document.fonts.load -...*
- `test_load_without_js_has_empty_console` (line 975) `static void test_load_without_js_has_empty_console(void **state)` - *"</script></body></html>"; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &...*
- `test_eval_captures_console_output` (line 991) `static void test_eval_captures_console_output(void **state)` - *Freebug (FB-1): the REPL (tab_eval) returns the value AND the console output the * evaluation produced, each eval reporting only its own transcript.*
- `test_load_full_location_is_real` (line 1020) `static void test_load_full_location_is_real(void **state)` - *Real location (Hito 20e): the page URL passed to tab_load_full backs a real * location object the page's JS can read (no scripts need run for the r...*
- `test_js_navigation_relative_resolved` (line 1056) `static void test_js_navigation_relative_resolved(void **state)`
- `test_js_navigation_unsafe_is_blocked` (line 1076) `static void test_js_navigation_unsafe_is_blocked(void **state)` - *Fail-closed gate: the parent rejects a downgrade / foreign-scheme / fragment nav, * so a hostile or compromised worker cannot drive the browser off...*
- `test_no_js_no_navigation` (line 1098) `static void test_no_js_no_navigation(void **state)` - *const char *cases[] = { DOWNGRADE, FOREIGN, FRAGMENT }; for (size_t i = 0; i < 3; ++i) { tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab...*
- `test_load_null_and_too_large` (line 1111) `static void test_load_null_and_too_large(void **state)`
- `test_eval_sees_dom` (line 1127) `static void test_eval_sees_dom(void **state)` - *(void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load(NULL, HTML, 4, &p), TAB_ERR_NULL_ARG); as...*
- `test_eval_sees_env` (line 1137) `static void test_eval_sees_env(void **state)` - *tab_close(t); } /* --- eval: sees the DOM bound in the child --- static void test_eval_sees_dom(void **state) { fixture *f = (fixture *)*state; exp...*
- `test_eval_no_network_or_cross_origin_api` (line 1155) `static void test_eval_no_network_or_cross_origin_api(void **state)` - *SOP/CORS confidentiality (gap audit #2): the JS sandbox exposes NO way to make a network request or open a cross-origin browsing context, so it can...*
- `stub_fetch` (line 1174) `static int stub_fetch(void *ctx, const char *method, const char *url,
                      const...` - *Stub parent fetcher: returns a fixed 200/"PONG" body, but REFUSES any "blocked.example" * host -- standing in for the real parent's hostblock/realm...*
- `test_xhr_works_when_net_allowed` (line 1193) `static void test_xhr_works_when_net_allowed(void **state)` - *With net allowed (host in allow.conf AND js.conf) the page's XHR reaches the parent * fetcher and the response is visible to script.*
- `test_xhr_undefined_when_net_not_allowed` (line 1213) `static void test_xhr_undefined_when_net_not_allowed(void **state)` - *Default (net not allowed): XHR/fetch stay undefined -- Same-Origin-by-construction holds for every site not in BOTH lists. The script's `new XMLHtt...*
- `stub_script_fetch` (line 1252) `static int stub_script_fetch(void *ctx, const char *method, const char *url,
                    ...` - *Stub parent fetcher for external scripts: serves JS bodies by URL with a proper JavaScript Content-Type; refuses "blocked.example" (standing in for...*
- `test_external_script_executes_when_net_allowed` (line 1282) `static void test_external_script_executes_when_net_allowed(void **state)` - *With net granted (allow.conf AND js.conf) an external script's bytes come from the * trusted parent and execute: its DOM mutation is visible in the...*
- `test_external_script_document_order` (line 1299) `static void test_external_script_document_order(void **state)` - *External scripts execute IN DOCUMENT ORDER interleaved with inline ones: a later * inline script sees the external script's effects (exactly as a b...*
- `test_external_script_skipped_without_net` (line 1322) `static void test_external_script_skipped_without_net(void **state)` - *Without the network grant an external script is SKIPPED (never fetched, never run): the page still loads and a Freebug warn entry records the skip....*
- `test_external_script_bad_ctype_not_executed` (line 1346) `static void test_external_script_bad_ctype_not_executed(void **state)` - *A response that is not JavaScript (e.g. an HTML error page) is NOT executed * (type-confusion guard, fail closed); the page still loads.*
- `test_external_script_blocked_host_refused` (line 1363) `static void test_external_script_blocked_host_refused(void **state)` - *Even with net granted, the trusted parent's refusal (blocked host) means the script * never runs -- the gate is the PARENT's policy, not the page's.*
- `stub_css_fetch` (line 1386) `static int stub_css_fetch(void *ctx, const char *method, const char *url,
                       ...` - *Stub parent fetcher for stylesheets: serves CSS bodies by URL with a text/css Content-Type; refuses "blocked.example" (standing in for the parent's...*
- `view_find_text` (line 1407) `static const pv_run *view_find_text(const pv_view *v, const char *needle)`
- `test_external_css_applied_when_allowed` (line 1419) `static void test_external_css_applied_when_allowed(void **state)` - *With the css grant, the <link rel=stylesheet> bytes come from the trusted parent * and feed the author-CSS cascade -- no JS required (run_js == 0).*
- `test_external_css_skipped_without_grant` (line 1439) `static void test_external_css_skipped_without_grant(void **state)` - *Default (no grant): zero subresource requests and no external styling -- * Privacy by Default holds, byte-identical to the pre-Hito-27 view.*
- `test_external_css_bad_ctype_not_parsed` (line 1458) `static void test_external_css_bad_ctype_not_parsed(void **state)` - *A non-CSS Content-Type (an HTML 404 page, a script) is never parsed as a sheet * (anti type-confusion, fail closed); the load continues unstyled.*
- `test_external_css_blocked_host_refused` (line 1476) `static void test_external_css_blocked_host_refused(void **state)` - *The parent's policy refusal (blocked host) degrades to "no sheet", never a * failed load: presentation is fail-open like hostblock, the page stays ...*
- `test_external_css_survives_click_rederive` (line 1494) `static void test_external_css_survives_click_rederive(void **state)` - *The fetched sheet PERSISTS in the worker: a click re-derives the view (OP_CLICK) * and the styling survives without a re-fetch.*
- `test_subreq_permitted_pure` (line 1522) `static void test_subreq_permitted_pure(void **state)` - *Pure parent-side subresource gate (Zero Trust: the parent decides from ITS flags, never the worker's): net grants any well-formed method, css-only ...*
- `read` (line 1543) `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */
static void tes...`
- `test_eval_exception` (line 1563) `static void test_eval_exception(void **state)` - *"<!DOCTYPE html><html><head><title>x</title></head><body>" "<script>document.title = 'tz:' + new Date(0).getTimezoneOffset()" " + ':' + new Date(1e...*
- `test_eval_persistent_state` (line 1575) `static void test_eval_persistent_state(void **state)` - */* --- eval: a JS exception is TAB_OK with is_exception set, not a worker error --- static void test_eval_exception(void **state) { fixture *f = (f...*
- `test_reload_replaces_page` (line 1584) `static void test_reload_replaces_page(void **state)` - *assert_non_null(strstr(r.value, "boom")); tab_eval_result_free(&r); } /* --- eval: state persists across calls within the same worker --- static vo...*
- `test_eval_without_load` (line 1608) `static void test_eval_without_load(void **state)` - *static const char HTML2[] = "<!DOCTYPE html><html><head><title>Second</title></head>" "<body><span id=\"other\">x</span></body></html>"; assert_int...*
- `test_binary_does_not_crash_parent` (line 1620) `static void test_binary_does_not_crash_parent(void **state)` - */* --- eval before any load is a worker error, not a crash --- static void test_eval_without_load(void **state) { (void)state; tab *t = NULL; asser...*
- `test_child_death_survived` (line 1635) `static void test_child_death_survived(void **state)` - *static void test_binary_does_not_crash_parent(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); uint8_t junk[1024...*
- `test_free_null_and_double` (line 1661) `static void test_free_null_and_double(void **state)` - */* Give the kernel a moment to deliver the signal and reap-on-read. struct timespec ts = { 0, 50 * 1000 * 1000 }; nanosleep(&ts, NULL); tab_eval_re...*
- `test_decode_image_in_sandbox` (line 1695) `static void test_decode_image_in_sandbox(void **state)`
- `test_decode_image_rejects_junk` (line 1717) `static void test_decode_image_rejects_junk(void **state)`
- `test_decode_image_null_args` (line 1732) `static void test_decode_image_null_args(void **state)`
- `test_worker_args_valid` (line 1746) `static void test_worker_args_valid(void **state)` - *static void test_decode_image_null_args(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_image img; assert_i...*
- `test_worker_args_not_worker` (line 1755) `static void test_worker_args_not_worker(void **state)`
- `test_worker_args_malformed` (line 1762) `static void test_worker_args_malformed(void **state)`
- `test_worker_args_null_safe` (line 1777) `static void test_worker_args_null_safe(void **state)`
- `main` (line 1787) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 13)
- `XHR_PAGE` (line 1185)
- `EXT_PAGE` (line 1275)
- `CSS_PAGE` (line 1402)

**Structs:**
- `fixture` (line 39)

#### `test_text_shape.c`
**Path:** `tests/test_text_shape.c`

**Functions:**
- `test_null_and_bad_inputs` (line 26) `static void test_null_and_bad_inputs(void **state)` - *#include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <math.h> #include <string.h> #include <cmocka.h> #include "text_shape.h" #incl...*
- `test_empty_slice_is_ok` (line 56) `static void test_empty_slice_is_ok(void **state)`
- `test_shape_ascii` (line 69) `static void test_shape_ascii(void **state)` - *} static void test_empty_slice_is_ok(void **state) { (void)state; cairo_glyph_t g[8]; size_t n = 99; double adv = 99.0; /* Empty input is OK regard...*
- `test_determinism` (line 91) `static void test_determinism(void **state)`
- `test_measure_matches_shape` (line 107) `static void test_measure_matches_shape(void **state)`
- `test_overflow_cap` (line 119) `static void test_overflow_cap(void **state)`
- `test_draw_paints` (line 129) `static void test_draw_paints(void **state)`
- `teardown` (line 142) `static int teardown(void **state)`
- `main` (line 148) `int main(void)`

#### `test_textfield.c`
**Path:** `tests/test_textfield.c`

**Functions:**
- `test_init_and_accessors` (line 19) `static void test_init_and_accessors(void **state)` - *include "textfield.h"*
- `test_null_safe` (line 28) `static void test_null_safe(void **state)`
- `test_set` (line 45) `static void test_set(void **state)`
- `test_insert_sequence` (line 58) `static void test_insert_sequence(void **state)`
- `test_backspace_delete` (line 75) `static void test_backspace_delete(void **state)`
- `test_move_saturates` (line 99) `static void test_move_saturates(void **state)`
- `test_full_fails_closed` (line 112) `static void test_full_fails_closed(void **state)`
- `main` (line 139) `int main(void)`

#### `test_tls_impersonate.c`
**Path:** `tests/test_tls_impersonate.c`

**Functions:**
- `test_gate_requires_all_three_signals` (line 21) `static void test_gate_requires_all_three_signals(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <stdlib.h> #include <cmocka.h> #includ...*
- `test_encode_decode_req_roundtrip` (line 38) `static void test_encode_decode_req_roundtrip(void **state)` - *assert_int_equal(ti_should_impersonate(1, 1, 1), 1); /* any single missing signal fails closed assert_int_equal(ti_should_impersonate(0, 1, 1), 0);...*
- `test_encode_decode_req_empty_body` (line 64) `static void test_encode_decode_req_empty_body(void **state)`
- `test_encode_decode_resp_roundtrip` (line 88) `static void test_encode_decode_resp_roundtrip(void **state)` - *}; uint8_t buf[1024]; size_t n = ti_encode_req(&in, buf, sizeof buf); assert_true(n > 0); ti_req out; assert_int_equal(ti_decode_req(buf, n, &out),...*
- `test_resp_no_chain_ok` (line 120) `static void test_resp_no_chain_ok(void **state)`
- `test_decode_rejects_truncated` (line 143) `static void test_decode_rejects_truncated(void **state)` - *}; in.negotiated_group[0] = '\0'; uint8_t buf[256]; size_t n = ti_encode_resp(&in, buf, sizeof buf); assert_true(n > 0); ti_resp out; assert_int_eq...*
- `test_decode_rejects_bad_magic` (line 162) `static void test_decode_rejects_bad_magic(void **state)`
- `test_decode_rejects_overlong_field` (line 176) `static void test_decode_rejects_overlong_field(void **state)`
- `test_encode_fails_when_no_room` (line 191) `static void test_encode_fails_when_no_room(void **state)`
- `test_encode_rejects_oversize_url` (line 202) `static void test_encode_rejects_oversize_url(void **state)`
- `main` (line 217) `int main(void)`

#### `test_ui.c`
**Path:** `tests/test_ui.c`

**Functions:**
- `assert_line` (line 20) `static void assert_line(const char *text, const ui_layout *lay, size_t n,
                       ...` - *Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #include <string.h> #includ...*
- `test_wrap_null_args` (line 27) `static void test_wrap_null_args(void **state)`
- `test_wrap_empty` (line 34) `static void test_wrap_empty(void **state)`
- `test_wrap_short_single_line` (line 42) `static void test_wrap_short_single_line(void **state)`
- `test_wrap_breaks_at_space` (line 52) `static void test_wrap_breaks_at_space(void **state)`
- `test_wrap_hard_breaks_long_word` (line 63) `static void test_wrap_hard_breaks_long_word(void **state)`
- `test_wrap_does_not_split_utf8` (line 75) `static void test_wrap_does_not_split_utf8(void **state)`
- `test_wrap_respects_newline` (line 89) `static void test_wrap_respects_newline(void **state)`
- `test_wrap_zero_cols_is_sanitised` (line 100) `static void test_wrap_zero_cols_is_sanitised(void **state)`
- `test_clamp_scroll` (line 112) `static void test_clamp_scroll(void **state)`
- `test_layout_free_null_and_double` (line 120) `static void test_layout_free_null_and_double(void **state)`
- `main` (line 129) `int main(void)`

#### `test_url.c`
**Path:** `tests/test_url.c`

**Functions:**
- `test_is_https` (line 22) `static void test_is_https(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <stdlib.h> #include <string.h> #include <cmocka.h> #includ...*
- `test_validate_https` (line 35) `static void test_validate_https(void **state)`
- `test_validate_long_bundle_url` (line 49) `static void test_validate_long_bundle_url(void **state)` - *Modern bundle URLs exceed 2048 bytes (google.com's xjs script URL measures 3456): * anything within URL_MAX_LEN must validate and resolve; far past...*
- `test_has_scheme` (line 68) `static void test_has_scheme(void **state)` - *memset(url + base, 'a', 4000 - base); url[4000] = '\0'; assert_int_equal(url_validate_https(url), URL_OK); char out[URL_MAX_LEN + 1]; assert_int_eq...*
- `test_authority_len` (line 85) `static void test_authority_len(void **state)` - *assert_int_equal(url_has_scheme("https://x"), 1); assert_int_equal(url_has_scheme("mailto:a@b"), 1); assert_int_equal(url_has_scheme("javascript:vo...*
- `test_remove_dot_segments` (line 94) `static void test_remove_dot_segments(void **state)` - *assert_int_equal(url_has_scheme("3com:x"), 0); /* scheme must start with ALPHA assert_int_equal(url_has_scheme(NULL), 0); } /* --- url_authority_le...*
- `test_remove_dot_segments_nulls` (line 123) `static void test_remove_dot_segments_nulls(void **state)`
- `test_resolve_absolute` (line 134) `static void test_resolve_absolute(void **state)` - *assert_int_equal(url_remove_dot_segments("/a/b/", out, sizeof out), URL_OK); assert_string_equal(out, "/a/b/"); /* trailing slash preserved } stati...*
- `test_resolve_rejects_downgrade_and_schemes` (line 142) `static void test_resolve_rejects_downgrade_and_schemes(void **state)`
- `test_resolve_scheme_relative` (line 157) `static void test_resolve_scheme_relative(void **state)`
- `test_resolve_absolute_path` (line 165) `static void test_resolve_absolute_path(void **state)`
- `test_resolve_relative_path` (line 177) `static void test_resolve_relative_path(void **state)`
- `test_resolve_dot_segments` (line 189) `static void test_resolve_dot_segments(void **state)`
- `test_resolve_fail_closed_on_bad_base` (line 206) `static void test_resolve_fail_closed_on_bad_base(void **state)`
- `test_resolve_null_and_overflow` (line 218) `static void test_resolve_null_and_overflow(void **state)`
- `test_omnibox_navigate_https` (line 234) `static void test_omnibox_navigate_https(void **state)` - *(void)state; char out[256]; assert_int_equal(url_resolve_https(NULL, "/x", out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_https(...*
- `test_omnibox_bare_host_gets_https` (line 247) `static void test_omnibox_bare_host_gets_https(void **state)`
- `test_omnibox_http_upgraded_to_https` (line 264) `static void test_omnibox_http_upgraded_to_https(void **state)`
- `test_omnibox_search_for_queries` (line 274) `static void test_omnibox_search_for_queries(void **state)`
- `test_omnibox_foreign_scheme_is_searched_not_executed` (line 294) `static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state)`
- `test_omnibox_nulls_and_empty` (line 307) `static void test_omnibox_nulls_and_empty(void **state)`
- `test_search_rewrite_ddg_spa` (line 323) `static void test_search_rewrite_ddg_spa(void **state)` - *(void)state; char out[URL_MAX_LEN + 1]; url_omni_kind k; assert_int_equal(url_omnibox(NULL, &k, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equ...*
- `test_search_rewrite_leaves_others_alone` (line 340) `static void test_search_rewrite_leaves_others_alone(void **state)`
- `test_search_rewrite_nulls` (line 360) `static void test_search_rewrite_nulls(void **state)`
- `test_is_file_and_path` (line 375) `static void test_is_file_and_path(void **state)` - *static void test_search_rewrite_nulls(void **state) { (void)state; char out[URL_MAX_LEN + 1]; assert_int_equal(url_search_rewrite(NULL, out, sizeof...*
- `test_resolve_file_relative` (line 387) `static void test_resolve_file_relative(void **state)`
- `test_resolve_file_confinement_fail_closed` (line 407) `static void test_resolve_file_confinement_fail_closed(void **state)`
- `test_resolve_file_nulls` (line 433) `static void test_resolve_file_nulls(void **state)`
- `assert_span` (line 446) `static void assert_span(const char *p, size_t len, const char *expect)` - *} static void test_resolve_file_nulls(void **state) { (void)state; char out[URL_MAX_LEN + 1]; assert_int_equal(url_resolve_file(NULL, "x", out, siz...*
- `test_split_full_url` (line 450) `static void test_split_full_url(void **state)`
- `test_split_no_port_no_path` (line 469) `static void test_split_no_port_no_path(void **state)`
- `test_split_query_without_fragment` (line 482) `static void test_split_query_without_fragment(void **state)`
- `test_split_fragment_without_query` (line 491) `static void test_split_fragment_without_query(void **state)`
- `test_split_ipv6_literal_with_port` (line 500) `static void test_split_ipv6_literal_with_port(void **state)`
- `test_extract_userinfo_basic` (line 512) `static void test_extract_userinfo_basic(void **state)` - *assert_span(u.hash, u.hash_len, "#sec"); } static void test_split_ipv6_literal_with_port(void **state) { (void)state; url_parts u; assert_int_equal...*
- `test_extract_userinfo_user_only` (line 525) `static void test_extract_userinfo_user_only(void **state)`
- `test_extract_userinfo_no_userinfo` (line 538) `static void test_extract_userinfo_no_userinfo(void **state)`
- `test_extract_userinfo_non_https_passthrough` (line 550) `static void test_extract_userinfo_non_https_passthrough(void **state)`
- `test_extract_userinfo_https_subresource_no_auth` (line 562) `static void test_extract_userinfo_https_subresource_no_auth(void **state)`
- `test_extract_userinfo_nulls` (line 575) `static void test_extract_userinfo_nulls(void **state)`
- `test_extract_userinfo_at_authority_start` (line 585) `static void test_extract_userinfo_at_authority_start(void **state)`
- `test_extract_userinfo_no_at_sign` (line 598) `static void test_extract_userinfo_no_at_sign(void **state)`
- `test_extract_userinfo_empty_password` (line 611) `static void test_extract_userinfo_empty_password(void **state)`
- `test_split_fail_closed_non_https` (line 624) `static void test_split_fail_closed_non_https(void **state)`
- `main` (line 635) `int main(void)`

#### `test_zoom.c`
**Path:** `tests/test_zoom.c`

**Functions:**
- `test_clamp_bounds` (line 16) `static void test_clamp_bounds(void **state)` - *include "zoom.h"*
- `test_reset_is_default` (line 26) `static void test_reset_is_default(void **state)`
- `test_zoom_in_steps_ladder` (line 32) `static void test_zoom_in_steps_ladder(void **state)`
- `test_zoom_out_steps_ladder` (line 40) `static void test_zoom_out_steps_ladder(void **state)`
- `test_step_snaps_off_ladder` (line 48) `static void test_step_snaps_off_ladder(void **state)`
- `test_ends_are_idempotent` (line 58) `static void test_ends_are_idempotent(void **state)`
- `test_repeated_in_reaches_max` (line 66) `static void test_repeated_in_reaches_max(void **state)`
- `test_repeated_out_reaches_min` (line 78) `static void test_repeated_out_reaches_min(void **state)`
- `test_scale_factor` (line 90) `static void test_scale_factor(void **state)`
- `test_apply_scales_and_floors` (line 99) `static void test_apply_scales_and_floors(void **state)`
- `main` (line 111) `int main(void)`

#### `gen_psl.c`
**Path:** `tools/gen_psl.c`

**Functions:**
- `vec_push` (line 26) `static void vec_push(vec *v, const char *s)`
- `cmp_str` (line 37) `static int cmp_str(const void *a, const void *b)`
- `sort_unique` (line 43) `static void sort_unique(vec *v)` - *v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap * sizeof *v->items); if (v->items == NULL) { fputs("oom\n", stder...*
- `ascii_lower` (line 55) `static void ascii_lower(char *s)` - */* Sorts then drops adjacent duplicates in place. static void sort_unique(vec *v) { qsort(v->items, v->len, sizeof *v->items, cmp_str); size_t w = ...*
- `emit` (line 60) `static void emit(const char *name, vec *v)`
- `main` (line 66) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 14)

**Structs:**
- `vec` (line 21)

### H (46 files)

#### `browser_ui_internal.h`
**Path:** `gui/browser_ui_internal.h`
**File Doc:** *ifndef FREEDOM_BROWSER_UI_INTERNAL_H define FREEDOM_BROWSER_UI_INTERNAL_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported."...*

**Macros:**
- `FREEDOM_BROWSER_UI_INTERNAL_H` (line 2)
- `UI_FONT_SIZE` (line 23)
- `UI_TEXT_MARGIN` (line 25)
- `UI_HEADING_LEVELS` (line 26)

**Structs:**
- `ui_rgb` (line 35)
- `ui_theme` (line 37)

#### `anti_fp.h`
**Path:** `include/anti_fp.h`
**File Doc:** *ifndef FREEDOM_ANTI_FP_H define FREEDOM_ANTI_FP_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is ...*

**Macros:**
- `FREEDOM_ANTI_FP_H` (line 2)
- `FP_TIMER_RESOLUTION_MS` (line 21)
- `FP_USER_AGENT` (line 31)
- `FP_ACCEPT_LANGUAGE` (line 33)
- `FP_ACCEPT_LANGUAGE_HEADER` (line 34)
- `FP_ACCEPT_HEADER_NAV` (line 40)
- `FP_SEC_FETCH_DEST_NAV` (line 45)
- `FP_SEC_FETCH_MODE_NAV` (line 46)
- `FP_SEC_FETCH_SITE_NONE` (line 47)
- `FP_SEC_FETCH_USER_ON` (line 48)

#### `box_style.h`
**Path:** `include/box_style.h`
**File Doc:** *ifndef FREEDOM_BOX_STYLE_H define FREEDOM_BOX_STYLE_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_BOX_STYLE_H` (line 2)

**Structs:**
- `bx_edges` (line 39) - *See spec/box_style.md for the full contract.  typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width B...*
- `bx_box` (line 43)
- `bx_hplace` (line 56) - *typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box; typedef enum bx_status { BX_OK = 0, BX_ERR_NULL_ARG,  ...*

#### `box_tree.h`
**Path:** `include/box_tree.h`
**File Doc:** *ifndef FREEDOM_BOX_TREE_H define FREEDOM_BOX_TREE_H  include <stddef.h>  include "box_style.h" include "flex_layout.h" include "page_view.h"   /* p...*

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
- `bt_node` (line 58)
- `bt_positioned` (line 107) - *Stage 2: one positioned box in the final paint order. The GUI paints the in-flow rc_layout.rows first, then the bt_positioned list in this order (o...*

#### `browser.h`
**Path:** `include/browser.h`
**File Doc:** *ifndef FREEDOM_BROWSER_H define FREEDOM_BROWSER_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is ...*

**Macros:**
- `FREEDOM_BROWSER_H` (line 2)
- `BROWSER_URL_MAX` (line 20)
- `BROWSER_STATUS_MAX` (line 24)
- `BROWSER_STATUS_DURATION_MS` (line 25)

**Structs:**
- `browser_state` (line 27)

#### `css.h`
**Path:** `include/css.h`
**File Doc:** *ifndef FREEDOM_CSS_H define FREEDOM_CSS_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_CSS_H` (line 2)
- `CSS_GAP_MAX` (line 64)
- `CSS_GRID_COLS_MAX` (line 65)
- `CSS_GRID_TRACKS_MAX` (line 66)
- `CSS_GRAD_STOPS_MAX` (line 67)
- `CSS_LINE_MIN` (line 68)
- `CSS_LINE_MAX` (line 69)
- `CSS_DECO_UNDERLINE` (line 74)
- `CSS_DECO_LINE_THROUGH` (line 75)
- `CSS_DECO_OVERLINE` (line 76)
- `CSS_CONTAIN_SIZE` (line 310)
- `CSS_CONTAIN_LAYOUT` (line 311)
- `CSS_CONTAIN_STYLE` (line 312)
- `CSS_CONTAIN_PAINT` (line 313)
- `CSS_BORDER_W_MAX` (line 390)
- `CSS_BORDER_SPACING_MAX` (line 391)
- `CSS_FLEX_FACTOR_MAX` (line 392)
- `CSS_GRID_SPAN_MAX` (line 393)
- `CSS_SPACING_MAX` (line 397)
- `CSS_SHADOW_MAX` (line 398)
- `CSS_LEN_MAX` (line 403)
- `CSS_LEN_UNSET` (line 404)
- `CSS_LEN_AUTO` (line 405)
- `CSS_MAX_COMPOUNDS` (line 409)
- `CSS_MAX_ATTR_SEL` (line 413)
- `CSS_MAX_PSEUDO_SEL` (line 417)
- `CSS_NTH_MAX` (line 421)
- `CSS_MEDIA_DEFAULT_WIDTH` (line 593)

**Structs:**
- `css_style` (line 428) - *A resolved presentation. Each field uses a sentinel for "unset" so the caller can layer inheritance (take the first ancestor that sets each inherit...*
- `css_media` (line 588) - *Render-time media context for evaluating @media at parse time. width_px is a fixed, normalized desktop width, so a (min/max-width) query leaks no r...*
- `css_attr` (line 625) - *One element attribute, for attribute selectors ([attr], [attr=v], [attr~=v], ...). name is the lowercased local name; value is the attribute text (...*
- `css_element` (line 635) - *An element plus its ancestor chain, for combinator matching. Each field aliases caller storage (nothing is copied/owned). parent walks toward the r...*

#### `css_chain.h`
**Path:** `include/css_chain.h`
**File Doc:** *ifndef FREEDOM_CSS_CHAIN_H define FREEDOM_CSS_CHAIN_H  include <lexbor/html/html.h>  include "css.h" include "css_select.h"  ifdef __cplusplus erro...*

**Macros:**
- `FREEDOM_CSS_CHAIN_H` (line 2)
- `CCH_CHAIN_MAX` (line 26)
- `CCH_SIB_MAX` (line 27)
- `CCH_NTH_MAX` (line 28)

#### `css_color.h`
**Path:** `include/css_color.h`
**File Doc:** *ifndef FREEDOM_CSS_COLOR_H define FREEDOM_CSS_COLOR_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_CSS_COLOR_H` (line 2)

**Structs:**
- `cc_rgb` (line 25)

#### `css_select.h`
**Path:** `include/css_select.h`
**File Doc:** *ifndef FREEDOM_CSS_SELECT_H define FREEDOM_CSS_SELECT_H  include <stddef.h> include <string.h>  include "css.h"  ifdef __cplusplus error "Freedom i...*

**Functions:**
- `csel_lower_ch` (line 98) `static inline char csel_lower_ch(char c)` - *Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller). Returns 1 if supported, 0 to drop the selector (fail...*
- `csel_ci_eq` (line 102) `static inline int csel_ci_eq(const char *a, const char *b)`
- `csel_span_eq` (line 112) `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` - *static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c; } static inline int csel_ci_eq(const char *a, const ...*
- `csel_substr` (line 123) `static inline int csel_substr(const char *hay, const char *needle, int ci)` - *Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator). A non-empty needle only; an empty o...*
- `csel_ident_ch` (line 130) `static inline int csel_ident_ch(char c)`

**Macros:**
- `FREEDOM_CSS_SELECT_H` (line 2)
- `CSS_TOK_MAX` (line 27)
- `CSS_MAX_CLASSES_PER_SEL` (line 28)

**Structs:**
- `css_pseudo_match` (line 50) - *One pseudo-class inside a compound. a/b are the An+B coefficients of the * nth-child family (unused otherwise).*
- `css_attr_match` (line 56) - *One pseudo-class inside a compound. a/b are the An+B coefficients of the * nth-child family (unused otherwise). typedef struct css_pseudo_match { i...*
- `css_compound` (line 65) - *One compound selector: optional type, optional id, zero+ classes, zero+ [attr], * zero+ pseudo-classes.*
- `css_sel` (line 81) - *A complex selector: a chain of compounds, parts[nparts-1] being the subject (the element a rule styles). comb[k] (k>=1) is the combinator to the LE...*

#### `disk_store.h`
**Path:** `include/disk_store.h`
**File Doc:** *ifndef FREEDOM_DISK_STORE_H define FREEDOM_DISK_STORE_H  include <stddef.h> include <stdint.h>  include "local_store.h"  ifdef __cplusplus error "F...*

**Macros:**
- `FREEDOM_DISK_STORE_H` (line 2)

#### `dom.h`
**Path:** `include/dom.h`
**File Doc:** *ifndef FREEDOM_DOM_H define FREEDOM_DOM_H  include <stddef.h> include <stdint.h>  include "html_parse.h"  ifdef __cplusplus error "Freedom is pure ...*

**Macros:**
- `FREEDOM_DOM_H` (line 2)
- `DOM_NODE_NONE` (line 37)
- `DOM_INNER_HTML_MAX` (line 194)

#### `dom_debug.h`
**Path:** `include/dom_debug.h`
**File Doc:** *ifndef FREEDOM_DOM_DEBUG_H define FREEDOM_DOM_DEBUG_H  include <stddef.h>  include "render_doc.h"  ifdef __cplusplus error "Freedom is pure C (C11)...*

**Macros:**
- `FREEDOM_DOM_DEBUG_H` (line 2)
- `DD_FIELD_MAX` (line 28)

#### `download.h`
**Path:** `include/download.h`
**File Doc:** *ifndef FREEDOM_DOWNLOAD_H define FREEDOM_DOWNLOAD_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." e...*

**Macros:**
- `FREEDOM_DOWNLOAD_H` (line 2)
- `DL_NAME_MAX` (line 28)
- `DL_FALLBACK_NAME` (line 30)
- `DL_MAX_BYTES` (line 31)

#### `flex_layout.h`
**Path:** `include/flex_layout.h`
**File Doc:** *ifndef FREEDOM_FLEX_LAYOUT_H define FREEDOM_FLEX_LAYOUT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not support...*

**Macros:**
- `FREEDOM_FLEX_LAYOUT_H` (line 2)
- `FX_MAX_ITEMS` (line 28)

**Structs:**
- `fx_item` (line 40) - *Upper bound on items per flex line / grid columns. Caps the O(n) shrink loop and * keeps the fixed-size scratch buffers bounded (anti-DoS; no VLAs)...*
- `fx_result` (line 48) - *FX_JUSTIFY_SPACE_BETWEEN, FX_JUSTIFY_SPACE_AROUND, FX_JUSTIFY_SPACE_EVENLY } fx_justify; /* One flex item, all sizes in px. Negative fields are tre...*

#### `form.h`
**Path:** `include/form.h`
**File Doc:** *ifndef FREEDOM_FORM_H define FREEDOM_FORM_H  include <stddef.h>  include "url.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supp...*

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
**File Doc:** *ifndef FREEDOM_FREEBUG_H define FREEDOM_FREEBUG_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
**File Doc:** *ifndef FREEDOM_HOSTBLOCK_H define FREEDOM_HOSTBLOCK_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported."...*

**Macros:**
- `FREEDOM_HOSTBLOCK_H` (line 2)

#### `hostedit.h`
**Path:** `include/hostedit.h`
**File Doc:** *ifndef FREEDOM_HOSTEDIT_H define FREEDOM_HOSTEDIT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." e...*

**Macros:**
- `FREEDOM_HOSTEDIT_H` (line 2)
- `HE_MAX_HOST` (line 32)

#### `html_parse.h`
**Path:** `include/html_parse.h`
**File Doc:** *ifndef FREEDOM_HTML_PARSE_H define FREEDOM_HTML_PARSE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C...*

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
**File Doc:** *ifndef FREEDOM_IMAGE_DECODE_H define FREEDOM_IMAGE_DECODE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11...*

**Macros:**
- `FREEDOM_IMAGE_DECODE_H` (line 2)
- `IMG_MAX_DIM` (line 65)
- `IMG_MAX_PIXELS` (line 66)

**Structs:**
- `img_pixels` (line 56) - *A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32: each pixel is a uint32_t 0xAARRGGBB, i.e. byt...*

#### `js_dom.h`
**Path:** `include/js_dom.h`
**File Doc:** *ifndef FREEDOM_JS_DOM_H define FREEDOM_JS_DOM_H  include "dom.h" include "freebug.h" include "js_sandbox.h" include "url.h"  ifdef __cplusplus erro...*

**Macros:**
- `FREEDOM_JS_DOM_H` (line 2)

**Structs:**
- `jd_opaque` (line 35)

#### `js_env.h`
**Path:** `include/js_env.h`
**File Doc:** *ifndef FREEDOM_JS_ENV_H define FREEDOM_JS_ENV_H  include "js_sandbox.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." e...*

**Macros:**
- `FREEDOM_JS_ENV_H` (line 2)

#### `js_policy.h`
**Path:** `include/js_policy.h`
**File Doc:** *ifndef FREEDOM_JS_POLICY_H define FREEDOM_JS_POLICY_H  include <stdbool.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported....*

**Macros:**
- `FREEDOM_JS_POLICY_H` (line 2)

#### `js_sandbox.h`
**Path:** `include/js_sandbox.h`
**File Doc:** *ifndef FREEDOM_JS_SANDBOX_H define FREEDOM_JS_SANDBOX_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C...*

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
**File Doc:** *ifndef FREEDOM_LINK_NAV_H define FREEDOM_LINK_NAV_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." e...*

**Macros:**
- `FREEDOM_LINK_NAV_H` (line 2)
- `LN_MAX_TARGET` (line 33)
- `LN_MAX_FRAGMENT` (line 38)

**Structs:**
- `ln_result` (line 62)

#### `local_store.h`
**Path:** `include/local_store.h`
**File Doc:** *ifndef FREEDOM_LOCAL_STORE_H define FREEDOM_LOCAL_STORE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11)....*

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
**File Doc:** *ifndef FREEDOM_NET_REALM_H define FREEDOM_NET_REALM_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_NET_REALM_H` (line 2)

**Structs:**
- `nr_config` (line 42)

#### `os_sandbox.h`
**Path:** `include/os_sandbox.h`
**File Doc:** *ifndef FREEDOM_OS_SANDBOX_H define FREEDOM_OS_SANDBOX_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported...*

**Macros:**
- `FREEDOM_OS_SANDBOX_H` (line 2)

**Structs:**
- `os_fs_rule` (line 108)

#### `page_view.h`
**Path:** `include/page_view.h`
**File Doc:** *ifndef FREEDOM_PAGE_VIEW_H define FREEDOM_PAGE_VIEW_H  include <stddef.h> include <stdint.h>  include "dom.h" include "html_parse.h"  ifdef __cplus...*

**Macros:**
- `FREEDOM_PAGE_VIEW_H` (line 2)
- `PV_LEN_UNSET` (line 42)
- `PV_GRID_TRACKS` (line 45)

**Structs:**
- `pv_run` (line 83) - *One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-ter...*
- `pv_box_def` (line 261) - *Box engine (Hito 23b-8 Step D): one entry of the box-definition TREE. The box decoration and the parent link live here, not on each run, so a box i...*
- `pv_view` (line 330)
- `pv_text_ext` (line 449) - *The author text-presentation extensions of one run, resolved from the nearest ancestor that sets each field (they all inherit in CSS). The 20+ fiel...*

#### `pdf_export.h`
**Path:** `include/pdf_export.h`
**File Doc:** *ifndef FREEDOM_PDF_EXPORT_H define FREEDOM_PDF_EXPORT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported...*

**Macros:**
- `FREEDOM_PDF_EXPORT_H` (line 2)
- `PE_NAME_MAX` (line 27)
- `PE_EXT` (line 29)
- `PE_EXT_PNG` (line 30)
- `PE_FALLBACK_NAME` (line 31)

#### `prefetch.h`
**Path:** `include/prefetch.h`
**File Doc:** *ifndef FREEDOM_PREFETCH_H define FREEDOM_PREFETCH_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif  include <stdde...*

**Macros:**
- `FREEDOM_PREFETCH_H` (line 2)
- `PF_MAX_REFS` (line 46)
- `PF_MAX_THREADS` (line 48)

**Structs:**
- `pf_ref` (line 42) - *One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's ow...*
- `pf_list` (line 50)
- `pf_job` (line 77)
- `pf_pool` (line 87)
- `pf_gated_fetch` (line 129) - *Cache-first fetcher adapter, shared by every frontend (DRY): install pf_pooled_fetch as the tab fetcher with a pf_gated_fetch as its ctx. A GET who...*

#### `prefs.h`
**Path:** `include/prefs.h`
**File Doc:** *ifndef FREEDOM_PREFS_H define FREEDOM_PREFS_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_PREFS_H` (line 2)
- `PREFS_VERSION` (line 25)
- `PREFS_MAX_URL` (line 27)
- `PREFS_MAX_TITLE` (line 28)
- `PREFS_MAX_BOOKMARKS` (line 29)
- `PREFS_MAX_HISTORY` (line 30)
- `PREFS_MAX_TEXT` (line 31)
- `PREFS_PAGE_HISTORY` (line 34)

**Structs:**
- `prefs_entry` (line 45)
- `prefs_state` (line 50)

#### `profile.h`
**Path:** `include/profile.h`
**File Doc:** *ifndef FREEDOM_PROFILE_H define FREEDOM_PROFILE_H  include <stddef.h> include <stdint.h>  include "local_store.h" include "prefs.h"  ifdef __cplusp...*

**Macros:**
- `FREEDOM_PROFILE_H` (line 2)
- `PROFILE_KEY_FILE` (line 31)
- `PROFILE_PREFS_FILE` (line 33)

**Structs:**
- `profile_ctx` (line 46)

#### `psl_data.h`
**Path:** `include/psl_data.h`
**File Doc:** *ifndef FREEDOM_PSL_DATA_H define FREEDOM_PSL_DATA_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." e...*

**Macros:**
- `FREEDOM_PSL_DATA_H` (line 2)

#### `render_doc.h`
**Path:** `include/render_doc.h`
**File Doc:** *ifndef FREEDOM_RENDER_DOC_H define FREEDOM_RENDER_DOC_H  include <stddef.h>  include "page_view.h" include "render_policy.h"  ifdef __cplusplus err...*

**Macros:**
- `FREEDOM_RENDER_DOC_H` (line 2)

**Structs:**
- `rd_block` (line 44) - *One paint-ready block in document order. text is owned, NUL-terminated and valid UTF-8. href is owned and NUL-terminated for RD_LINK (link target),...*
- `rd_doc` (line 159)

#### `render_policy.h`
**Path:** `include/render_policy.h`
**File Doc:** *ifndef FREEDOM_RENDER_POLICY_H define FREEDOM_RENDER_POLICY_H  include <stdbool.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not su...*

**Macros:**
- `FREEDOM_RENDER_POLICY_H` (line 2)
- `RDP_TRACKER_MAX_DIM` (line 27)

**Structs:**
- `rdp_caps` (line 32) - *Render capabilities for a page. The zero value ({0}) is the safe baseline: every rich/risky capability off. The only way to opt in is to set a fiel...*

#### `renderer.h`
**Path:** `include/renderer.h`
**File Doc:** *ifndef FREEDOM_RENDERER_H define FREEDOM_RENDERER_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." e...*

**Macros:**
- `FREEDOM_RENDERER_H` (line 2)
- `RD_MAX_INPUT` (line 36)
- `RD_MAX_FIELD` (line 38)

**Structs:**
- `rd_result` (line 29)

#### `request_policy.h`
**Path:** `include/request_policy.h`
**File Doc:** *ifndef FREEDOM_REQUEST_POLICY_H define FREEDOM_REQUEST_POLICY_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not s...*

**Macros:**
- `FREEDOM_REQUEST_POLICY_H` (line 2)

#### `secure_fetch.h`
**Path:** `include/secure_fetch.h`
**File Doc:** *ifndef FREEDOM_SECURE_FETCH_H define FREEDOM_SECURE_FETCH_H  include <stddef.h> include <stdint.h>  include "anti_fp.h" /* normalized network ident...*

**Macros:**
- `FREEDOM_SECURE_FETCH_H` (line 2)
- `SF_DEFAULT_KEX_GROUPS` (line 139)
- `SF_IMPERSONATE_KEX_GROUPS` (line 148)
- `SF_IMPERSONATE_TLS13_CIPHERS` (line 149)
- `SF_IMPERSONATE_TLS12_CIPHERS` (line 153)
- `SF_DEFAULT_USER_AGENT` (line 164)
- `SF_DEFAULT_MAX_BODY` (line 165)
- `SF_DEFAULT_TIMEOUT_MS` (line 166)
- `SF_DEFAULT_MAX_REDIRECTS` (line 167)
- `SF_MAX_URL` (line 168)

**Structs:**
- `sf_chain_info` (line 60) - *Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testabl...*
- `sf_config` (line 75)
- `sf_response` (line 113)

#### `tab.h`
**Path:** `include/tab.h`
**File Doc:** *ifndef FREEDOM_TAB_H define FREEDOM_TAB_H  include <stddef.h> include <stdint.h> include <sys/types.h>  include "freebug.h" include "page_view.h"  ...*

**Macros:**
- `FREEDOM_TAB_H` (line 2)
- `TAB_MAX_INPUT` (line 100)

**Structs:**
- `tab_page` (line 49) - *Inert result of loading a page: title + extracted text + structured display list (all owned). text is kept for headless/plain output; view carries ...*
- `tab_eval_result` (line 80) - *The page's document.cookie jar after the scripts ran ("name=value; ..."), or NULL when the jar was disabled (untrusted host) or empty. The trusted ...*
- `tab_image` (line 93) - *Pixels of a decoded image, produced inside the confined worker. data is owned and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: b...*

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
**File Doc:** *ifndef FREEDOM_TEXTFIELD_H define FREEDOM_TEXTFIELD_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported."...*

**Macros:**
- `FREEDOM_TEXTFIELD_H` (line 2)
- `TF_CAP` (line 22)

**Structs:**
- `tf_field` (line 25)

#### `tls_impersonate.h`
**Path:** `include/tls_impersonate.h`
**File Doc:** *ifndef FREEDOM_TLS_IMPERSONATE_H define FREEDOM_TLS_IMPERSONATE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure ...*

**Macros:**
- `FREEDOM_TLS_IMPERSONATE_H` (line 2)
- `TI_MAGIC` (line 56)
- `TI_MAX_URL` (line 57)
- `TI_MAX_METHOD` (line 58)
- `TI_MAX_HEADERS` (line 59)
- `TI_MAX_BODY` (line 60)
- `TI_MAX_RESP_HDR` (line 61)
- `TI_MAX_RESP_BODY` (line 62)
- `TI_MAX_CHAIN` (line 63)
- `TI_MAX_GROUP` (line 64)

**Structs:**
- `ti_req` (line 68) - *Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied); * ti_decode_req allocates its own copies, released by ti_req_free.*
- `ti_resp` (line 78) - *Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied); * ti_decode_req allocates its own copies, released by ti_req_free. ...*

#### `ui.h`
**Path:** `include/ui.h`
**File Doc:** *ifndef FREEDOM_UI_H define FREEDOM_UI_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_UI_H` (line 2)

**Structs:**
- `ui_line` (line 29) - *A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.*
- `ui_layout` (line 34)
- `rd_doc` (line 68)

#### `url.h`
**Path:** `include/url.h`
**File Doc:** *ifndef FREEDOM_URL_H define FREEDOM_URL_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_URL_H` (line 2)
- `URL_MAX_LEN` (line 30)
- `URL_SEARCH_ENDPOINT` (line 76)

**Structs:**
- `url_parts` (line 129) - *Components of a validated absolute https URL, sliced for a JS location object. Every field ALIASES the input url (not owned, valid while url is ali...*

#### `zoom.h`
**Path:** `include/zoom.h`
**File Doc:** *ifndef FREEDOM_ZOOM_H define FREEDOM_ZOOM_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_ZOOM_H` (line 2)
- `ZM_MIN_PCT` (line 20)
- `ZM_MAX_PCT` (line 22)
- `ZM_DEFAULT_PCT` (line 23)

### PY (1 files)

#### `app.py`
**Path:** `app.py`
**File Doc:** *_*_ coding: utf8 _*_*

**Functions:**
- `read_fuzz_stats` (line 30) `def read_fuzz_stats()` - *Reads the current status of the active AFL++ fuzzing session.*
- `list_unique_crashes` (line 39) `def list_unique_crashes()` - *Lists all unique crash files generated by the fuzzer that broke the browser.*
- `run_freedom_headless` (line 47) `def run_freedom_headless(payload_path)` - *Executes the FreeDom browser in headless mode against a specific file input or mutated seed.

Args:
    payload_path: The relative or absolute path to the HTML/JS file to process (e.g., 'fuzz/in/seed.html').*

### SH (6 files)

#### `build_deb.sh`
**Path:** `build_deb.sh`
**File Doc:** *Thin wrapper. The .deb build lives in the Makefile (single source of truth) and also restores build/ ownership afterwards (debuild runs under faker...*

*No symbols extracted*

#### `docker-entrypoint.sh`
**Path:** `docker-entrypoint.sh`

*No symbols extracted*

#### `docker_run.sh`
**Path:** `docker_run.sh`
**File Doc:** *Thin wrapper. The docker build/run lives in the Makefile (single source of truth).*

*No symbols extracted*

#### `fuzz.sh`
**Path:** `fuzz.sh`
**File Doc:** *Thin wrapper. The fuzz build/run logic now lives in the Makefile (single source of truth), so it can never drift from the real build the way this s...*

*No symbols extracted*

#### `install.sh`
**Path:** `install.sh`
**File Doc:** *Exit immediately if a command exits with a non-zero status, if an undefined variable is used, or if any pipe fails.*

*No symbols extracted*

#### `run_freedom.sh`
**Path:** `run_freedom.sh`
**File Doc:** *Thin wrapper. Launches a nested weston (for boxes without a Wayland session), then runs the browser through the Makefile (single source of truth fo...*

*No symbols extracted*
