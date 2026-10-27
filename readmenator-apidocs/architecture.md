# freedom-0.0.3 Architecture and Execution Flows

[Back to index](index.md)

## Architecture Overview

13 components stacked in 7 dependency tiers (weighted Eades-Lin-Smyth ordering: arrows point from dependent to dependency, top to bottom). Labels are import counts, thick arrows the top quartile; 20 transitively implied edges are omitted. Dashed red arrows are upward dependencies: the smallest set of imports that closes every cycle and breaks the layering. Cyan components hold entry points. Interactive version: `readmenator-apidocs/index.html#/flows`.

Upward dependencies to fix first: `include: css` -> `include: page_view` (3 imports); `src: tab` -> `src: text_shape` (3 imports); `src: tab` -> `include: page_view` (3 imports); `src: tab` -> `include: browser_ui` (2 imports); `include: css` -> `src: text_shape` (1 imports); `src: text_shape` -> `include: browser_ui` (1 imports); `include: page_view` -> `src: text_shape` (1 imports); `include: browser` -> `src: tab` (1 imports); `include: svg_render` -> `src: tab` (1 imports); `include: secure_fetch` -> `src: tab` (1 imports); `include: secure_fetch` -> `src: text_shape` (1 imports); `include: prefetch` -> `src: tab` (1 imports)

```mermaid
flowchart TB
    classDef cycle fill:#1f1530,stroke:#f472b6,color:#fce7f3,stroke-width:2px;
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    subgraph lane_0["Tier 1 - entry / orchestration"]
        direction LR
        n_c2["include: browser_ui<br/>29 files, 967 symbols<br/>Core / utility"]:::cycle
        n_d_tools["tools<br/>13 files, 69 symbols<br/>Core / utility"]:::default
        n_d__root_["(root)<br/>5 files, 3 symbols<br/>Core / utility"]:::entry
    end
    subgraph lane_1["Tier 2"]
        direction LR
        n_c3["src: text_shape<br/>29 files, 406 symbols<br/>Core / utility"]:::cycle
    end
    subgraph lane_2["Tier 3"]
        direction LR
        n_c5["include: page_view<br/>12 files, 622 symbols<br/>Presentation / entry"]:::cycle
    end
    subgraph lane_3["Tier 4"]
        direction LR
        n_c1["src: tab<br/>36 files, 809 symbols<br/>Core / utility"]:::cycle
    end
    subgraph lane_4["Tier 5"]
        direction LR
        n_c7["include: svg_render<br/>12 files, 146 symbols<br/>Presentation / entry"]:::cycle
        n_c9["include: prefetch<br/>4 files, 90 symbols<br/>Core / utility"]:::cycle
        n_c10["include: sha2<br/>2 files, 21 symbols<br/>Core / utility"]:::default
    end
    subgraph lane_5["Tier 6"]
        direction LR
        n_c4["include: local_store<br/>16 files, 528 symbols<br/>Core / utility"]:::cycle
        n_c0["include: css<br/>36 files, 993 symbols<br/>Core / utility"]:::cycle
    end
    subgraph lane_6["Tier 7 - foundation"]
        direction LR
        n_c8["include: secure_fetch<br/>8 files, 276 symbols<br/>Core / utility"]:::cycle
        n_c6["include: browser<br/>13 files, 196 symbols<br/>Core / utility"]:::cycle
    end
    n_c1 -->|"1"| n_c10
    n_c1 -->|"1"| n_c7
    n_c1 -->|"1"| n_c9
    n_c2 ==>|"11"| n_c3
    n_c3 ==>|"6"| n_c5
    n_c4 -->|"1"| n_c6
    n_c4 -->|"1"| n_c8
    n_c5 ==>|"5"| n_c1
    n_c7 ==>|"4"| n_c0
    n_c7 -->|"1"| n_c4
    n_c3 <-.-|"1 upward"| n_c0
    n_c5 <-.-|"3 upward"| n_c0
    n_c2 <-.-|"2 upward"| n_c1
    n_c3 <-.-|"3 upward"| n_c1
    n_c5 <-.-|"3 upward"| n_c1
    n_c2 <-.-|"1 upward"| n_c3
    n_c3 <-.-|"1 upward"| n_c5
    n_c1 <-.-|"1 upward"| n_c6
    n_c1 <-.-|"1 upward"| n_c7
    n_c1 <-.-|"1 upward"| n_c8
    n_c3 <-.-|"1 upward"| n_c8
    n_c1 <-.-|"1 upward"| n_c9
    linkStyle 10,11,12,13,14,15,16,17,18,19,20,21 stroke:#f87171,stroke-width:2px;
    n_c2 ~~~ n_c3
    n_c3 ~~~ n_c5
    n_c5 ~~~ n_c1
    n_c1 ~~~ n_c7
    n_c7 ~~~ n_c4
    n_c4 ~~~ n_c8
```

---

## Execution Flows

Entry points are scored from `__main__` guards, `main` functions, entry-style names and files, and call-graph sources. Each flow walks resolved calls in call-site order (depth <= 4, <= 40 steps); numbers give the call order, dashed arrows revisit an already expanded callee, red arrows are recursion. Interactive version with zoom and per-node docs: `readmenator-apidocs/index.html#/flows`.

### `browser_ui.main`

`gui/browser_ui.c:553`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    n_gui_browser_ui_c__main["browser_ui.main<br/>browser_ui.c:553"]:::entry
    n_gui_browser_ui_c__now_ms["browser_ui.now_ms<br/>Largest text slice measured/drawn at once (on...<br/>browser_ui.c:169"]:::default
    n_gui_browser_ui_c__main -->|"1"| n_gui_browser_ui_c__now_ms
```

### `freedom_view.main`

`gui/freedom_view.c:37`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    classDef external fill:#1a1530,stroke:#a78bfa,color:#ede9fe;
    n_gui_freedom_view_c__main["freedom_view.main<br/>freedom_view.c:37"]:::entry
    n_src_html_parse_c__hp_parse["html_parse.hp_parse<br/>html_parse.c:375"]:::external
    n_src_html_parse_c__hp_config_default["html_parse.hp_config_default<br/>html_parse.c:357"]:::external
    n_src_html_parse_c__hp_validate_input["html_parse.hp_validate_input<br/>html_parse.c:365"]:::external
    n_src_html_parse_c__strip_scripts["html_parse.strip_scripts<br/>html_parse.c:60"]:::external
    n_src_html_parse_c__node_next["html_parse.node_next<br/>}#59; /* --- helpers --- static char *dup_bytes(...<br/>html_parse.c:37"]:::external
    n_src_html_parse_c__node_is_script["html_parse.node_is_script<br/>html_parse.c:54"]:::external
    n_src_html_parse_c__strip_event_handlers["html_parse.strip_event_handlers<br/>html_parse.c:334"]:::external
    n_src_html_parse_c__attr_is_event_handler["html_parse.attr_is_event_handler<br/>html_parse.c:47"]:::external
    n_include_html_parse_h__hp_get_title["html_parse.hp_get_title<br/>html_parse.h:70"]:::external
    n_include_html_parse_h__hp_extract_text["html_parse.hp_extract_text<br/>Owned, NUL-terminated buffers#59; release with h...<br/>html_parse.h:69"]:::external
    n_include_html_parse_h__hp_document_free["html_parse.hp_document_free<br/>(ASCII case-insensitive) and NOT the token #quot;a...<br/>html_parse.h:136"]:::external
    n_gui_ui_render_c__ui_run_text_view["ui_render.ui_run_text_view<br/>ui_render.c:410"]:::external
    n_gui_ui_render_c__destroy_buffer["ui_render.destroy_buffer<br/>ui_render.c:122"]:::external
    n_include_html_parse_h__hp_free["html_parse.hp_free<br/>number found.<br/>html_parse.h:133"]:::external
    n_gui_freedom_view_c__main -.->|"recursion"| n_gui_freedom_view_c__main
    n_gui_freedom_view_c__main -->|"1"| n_src_html_parse_c__hp_parse
    n_src_html_parse_c__hp_parse -.->|"recursion"| n_src_html_parse_c__hp_parse
    n_src_html_parse_c__hp_parse -->|"1"| n_src_html_parse_c__hp_config_default
    n_src_html_parse_c__hp_config_default -.->|"recursion"| n_src_html_parse_c__hp_config_default
    n_src_html_parse_c__hp_parse -->|"2"| n_src_html_parse_c__hp_validate_input
    n_src_html_parse_c__hp_validate_input -.->|"recursion"| n_src_html_parse_c__hp_validate_input
    n_src_html_parse_c__hp_parse -->|"3"| n_src_html_parse_c__strip_scripts
    n_src_html_parse_c__strip_scripts -->|"1"| n_src_html_parse_c__node_next
    n_src_html_parse_c__strip_scripts -->|"2"| n_src_html_parse_c__node_is_script
    n_src_html_parse_c__hp_parse -->|"4"| n_src_html_parse_c__strip_event_handlers
    n_src_html_parse_c__strip_event_handlers -.-> n_src_html_parse_c__node_next
    n_src_html_parse_c__strip_event_handlers -->|"1"| n_src_html_parse_c__attr_is_event_handler
    n_gui_freedom_view_c__main -->|"2"| n_include_html_parse_h__hp_get_title
    n_include_html_parse_h__hp_get_title -.->|"recursion"| n_include_html_parse_h__hp_get_title
    n_gui_freedom_view_c__main -->|"3"| n_include_html_parse_h__hp_extract_text
    n_include_html_parse_h__hp_extract_text -.->|"recursion"| n_include_html_parse_h__hp_extract_text
    n_gui_freedom_view_c__main -->|"4"| n_include_html_parse_h__hp_document_free
    n_include_html_parse_h__hp_document_free -.->|"recursion"| n_include_html_parse_h__hp_document_free
    n_gui_freedom_view_c__main -->|"5"| n_gui_ui_render_c__ui_run_text_view
    n_gui_ui_render_c__ui_run_text_view -.->|"recursion"| n_gui_ui_render_c__ui_run_text_view
    n_gui_ui_render_c__ui_run_text_view -->|"1"| n_gui_ui_render_c__destroy_buffer
    n_gui_freedom_view_c__main -->|"6"| n_include_html_parse_h__hp_free
    n_include_html_parse_h__hp_free -.->|"recursion"| n_include_html_parse_h__hp_free
    linkStyle 0,2,4,6,14,16,18,20,23 stroke:#f87171,stroke-width:2px;
```

Cross-file sequence:

```mermaid
sequenceDiagram
    autonumber
    participant p_gui_freedom_view_c as freedom_view.c
    participant p_src_html_parse_c as html_parse.c
    participant p_include_html_parse_h as html_parse.h
    participant p_gui_ui_render_c as ui_render.c
    p_gui_freedom_view_c->>p_src_html_parse_c: hp_parse()
    p_gui_freedom_view_c->>p_include_html_parse_h: hp_get_title()
    p_gui_freedom_view_c->>p_include_html_parse_h: hp_extract_text()
    p_gui_freedom_view_c->>p_include_html_parse_h: hp_document_free()
    p_gui_freedom_view_c->>p_gui_ui_render_c: ui_run_text_view()
    p_gui_freedom_view_c->>p_include_html_parse_h: hp_free()
```

### `freedom.main`

`src/freedom.c:1263`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    classDef external fill:#1a1530,stroke:#a78bfa,color:#ede9fe;
    n_src_freedom_c__main["freedom.main<br/>freedom.c:1263"]:::entry
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp<br/>browser_ui.c:2782"]:::external
    n_include_prefs_h__free["prefs.free<br/>prefs.h:72"]:::external
    n_src_prefs_c__prefs_format["prefs.prefs_format<br/>prefs.c:183"]:::external
    n_src_prefs_c__prefs_parse["prefs.prefs_parse<br/>prefs.c:247"]:::external
    n_src_prefs_c__prefs_free["prefs.prefs_free<br/>prefs.c:74"]:::external
    n_src_prefs_c__prefs_init["prefs.prefs_init<br/>prefs.c:66"]:::external
    n_src_prefs_c__url_valid["prefs.url_valid<br/>A representable URL: 1..PREFS_MAX_URL-1 bytes...<br/>prefs.c:26"]:::external
    n_src_prefs_c__bookmark_push["prefs.bookmark_push<br/>Appends a cleaned bookmark.<br/>prefs.c:91"]:::external
    n_src_prefs_c__history_push_back["prefs.history_push_back<br/>Appends a history entry at the BACK preservin...<br/>prefs.c:109"]:::external
    n_src_prefs_c__apply_kv["prefs.apply_kv<br/>} for (size_t i = 0#59; i #lt; p-#gt;history_len#59; ++i)...<br/>prefs.c:231"]:::external
    n_gui_browser_ui_c__prepare_fetch["browser_ui.prepare_fetch<br/>Builds cfg for url and applies the pre-fetch...<br/>browser_ui.c:1805"]:::external
    n_gui_browser_ui_c__host_from_url["browser_ui.host_from_url<br/>A plain-http URL whose realm self-authenticat...<br/>browser_ui.c:1068"]:::external
    n_gui_browser_ui_c__is_https_url["browser_ui.is_https_url<br/>browser_ui.c:1053"]:::external
    n_src_hostblock_c__hb_check["hostblock.hb_check<br/>hostblock.c:193"]:::external
    n_src_hostblock_c__lower["hostblock.lower<br/>hostblock.c:107"]:::external
    n_src_hostblock_c__table_contains["hostblock.table_contains<br/>hostblock.c:92"]:::external
    n_include_anti_fp_h__domain["anti_fp.domain<br/>anti_fp.h:91"]:::external
    n_include_browser_h__browser_is_exception["browser.browser_is_exception<br/>Index of the current entry within its documen...<br/>browser.h:99"]:::external
    n_src_browser_c__browser_add_exception["browser.browser_add_exception<br/>browser.c:472"]:::external
    n_src_browser_c__browser_set_url_bar["browser.browser_set_url_bar<br/>browser.c:178"]:::external
    n_src_browser_c__browser_commit_url_bar["browser.browser_commit_url_bar<br/>browser.c:190"]:::external
    n_src_browser_c__browser_url_bar_insert["browser.browser_url_bar_insert<br/>browser.c:326"]:::external
    n_src_browser_c__browser_url_bar_backspace["browser.browser_url_bar_backspace<br/>browser.c:341"]:::external
    n_src_browser_c__browser_url_bar_delete["browser.browser_url_bar_delete<br/>browser.c:355"]:::external
    n_src_browser_c__browser_url_bar_move_cursor["browser.browser_url_bar_move_cursor<br/>browser.c:366"]:::external
    n_src_browser_c__browser_url_bar_clear["browser.browser_url_bar_clear<br/>browser.c:400"]:::external
    n_src_browser_c__browser_url_bar_extend_cursor["browser.browser_url_bar_extend_cursor<br/>browser.c:376"]:::external
    n_src_browser_c__browser_url_bar_set_cursor["browser.browser_url_bar_set_cursor<br/>browser.c:385"]:::external
    n_src_browser_c__browser_url_bar_select_all["browser.browser_url_bar_select_all<br/>browser.c:393"]:::external
    n_gui_browser_ui_c__apply_operator_override["browser_ui.apply_operator_override<br/>browser_ui.c:1517"]:::external
    n_gui_browser_ui_c__hb_is_allowlisted["browser_ui.hb_is_allowlisted<br/>browser_ui.c:1756"]:::external
    n_include_request_policy_h__rp_host_of["request_policy.rp_host_of<br/>Lowercased host of an absolute URL into out.<br/>request_policy.h:30"]:::external
    n_src_freedom_c__main -.->|"recursion"| n_src_freedom_c__main
    n_src_freedom_c__main -->|"1"| n_gui_browser_ui_c__strcmp
    n_gui_browser_ui_c__strcmp -.->|"recursion"| n_gui_browser_ui_c__strcmp
    n_gui_browser_ui_c__strcmp -->|"1"| n_include_prefs_h__free
    n_include_prefs_h__free -->|"1"| n_src_prefs_c__prefs_format
    n_src_prefs_c__prefs_format -.->|"recursion"| n_src_prefs_c__prefs_format
    n_src_prefs_c__prefs_format -.->|"recursion"| n_include_prefs_h__free
    n_include_prefs_h__free -->|"2"| n_src_prefs_c__prefs_parse
    n_src_prefs_c__prefs_parse -.->|"recursion"| n_src_prefs_c__prefs_parse
    n_src_prefs_c__prefs_parse -->|"1"| n_src_prefs_c__prefs_free
    n_src_prefs_c__prefs_parse -->|"2"| n_src_prefs_c__prefs_init
    n_src_prefs_c__prefs_parse -->|"3"| n_src_prefs_c__url_valid
    n_src_prefs_c__prefs_parse -->|"4"| n_src_prefs_c__bookmark_push
    n_src_prefs_c__prefs_parse -->|"5"| n_src_prefs_c__history_push_back
    n_src_prefs_c__prefs_parse -->|"6"| n_src_prefs_c__apply_kv
    n_gui_browser_ui_c__strcmp -->|"2"| n_gui_browser_ui_c__prepare_fetch
    n_gui_browser_ui_c__prepare_fetch -->|"1"| n_gui_browser_ui_c__host_from_url
    n_gui_browser_ui_c__host_from_url -->|"1"| n_gui_browser_ui_c__is_https_url
    n_gui_browser_ui_c__prepare_fetch -->|"2"| n_src_hostblock_c__hb_check
    n_src_hostblock_c__hb_check -.->|"recursion"| n_src_hostblock_c__hb_check
    n_src_hostblock_c__hb_check -->|"1"| n_src_hostblock_c__lower
    n_src_hostblock_c__hb_check -->|"2"| n_src_hostblock_c__table_contains
    n_gui_browser_ui_c__prepare_fetch -->|"3"| n_include_anti_fp_h__domain
    n_gui_browser_ui_c__prepare_fetch -->|"4"| n_include_browser_h__browser_is_exception
    n_include_browser_h__browser_is_exception -.->|"recursion"| n_include_browser_h__browser_is_exception
    n_include_browser_h__browser_is_exception -->|"1"| n_src_browser_c__browser_add_exception
    n_include_browser_h__browser_is_exception -->|"2"| n_src_browser_c__browser_set_url_bar
    n_include_browser_h__browser_is_exception -->|"3"| n_src_browser_c__browser_commit_url_bar
    n_include_browser_h__browser_is_exception -->|"4"| n_src_browser_c__browser_url_bar_insert
    n_include_browser_h__browser_is_exception -->|"5"| n_src_browser_c__browser_url_bar_backspace
    n_include_browser_h__browser_is_exception -->|"6"| n_src_browser_c__browser_url_bar_delete
    n_include_browser_h__browser_is_exception -->|"7"| n_src_browser_c__browser_url_bar_move_cursor
    n_include_browser_h__browser_is_exception -->|"8"| n_src_browser_c__browser_url_bar_clear
    n_include_browser_h__browser_is_exception -->|"9"| n_src_browser_c__browser_url_bar_extend_cursor
    n_include_browser_h__browser_is_exception -->|"10"| n_src_browser_c__browser_url_bar_set_cursor
    n_include_browser_h__browser_is_exception -->|"11"| n_src_browser_c__browser_url_bar_select_all
    n_gui_browser_ui_c__prepare_fetch -->|"5"| n_gui_browser_ui_c__apply_operator_override
    n_gui_browser_ui_c__prepare_fetch -->|"6"| n_gui_browser_ui_c__hb_is_allowlisted
    n_gui_browser_ui_c__hb_is_allowlisted -.->|"recursion"| n_gui_browser_ui_c__hb_is_allowlisted
    n_gui_browser_ui_c__hb_is_allowlisted -->|"1"| n_include_request_policy_h__rp_host_of
    linkStyle 0,2,5,6,8,19,24,38 stroke:#f87171,stroke-width:2px;
```

Cross-file sequence:

```mermaid
sequenceDiagram
    autonumber
    participant p_src_freedom_c as freedom.c
    participant p_gui_browser_ui_c as browser_ui.c
    participant p_include_prefs_h as prefs.h
    participant p_src_prefs_c as prefs.c
    participant p_src_hostblock_c as hostblock.c
    participant p_include_anti_fp_h as anti_fp.h
    participant p_include_browser_h as browser.h
    participant p_src_browser_c as browser.c
    participant p_include_request_policy_h as request_policy.h
    p_src_freedom_c->>p_gui_browser_ui_c: strcmp()
    p_gui_browser_ui_c->>p_include_prefs_h: free()
    p_include_prefs_h->>p_src_prefs_c: prefs_format()
    p_src_prefs_c->>p_include_prefs_h: free()
    p_include_prefs_h->>p_src_prefs_c: prefs_parse()
    p_gui_browser_ui_c->>p_src_hostblock_c: hb_check()
    p_gui_browser_ui_c->>p_include_anti_fp_h: domain()
    p_gui_browser_ui_c->>p_include_browser_h: browser_is_exception()
    p_include_browser_h->>p_src_browser_c: browser_add_exception()
    p_include_browser_h->>p_src_browser_c: browser_set_url_bar()
    p_include_browser_h->>p_src_browser_c: browser_commit_url_bar()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_insert()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_backspace()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_delete()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_move_cursor()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_clear()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_extend_cursor()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_set_cursor()
    p_include_browser_h->>p_src_browser_c: browser_url_bar_select_all()
    p_gui_browser_ui_c->>p_include_request_policy_h: rp_host_of()
```

---
