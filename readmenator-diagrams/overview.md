```mermaid
graph LR
    include_browser_ui["include: browser_ui"]
    src_css["src: css"]
    src_tab["src: tab"]
    src_text_shape["src: text_shape"]
    include_page_view["include: page_view"]
    include_browser["include: browser"]
    src_local_store["src: local_store"]
    include_secure_fetch["include: secure_fetch"]
    include_prefetch["include: prefetch"]
    include_browser_ui -- "calls into" --> src_css
    include_browser_ui -- "calls into" --> src_tab
    include_browser_ui -- "calls into" --> src_text_shape
    include_browser_ui -- "calls into" --> include_page_view
    include_browser_ui -- "calls into" --> include_browser
    include_browser_ui -- "calls into" --> src_local_store
    include_browser_ui -- "calls into" --> include_secure_fetch
    include_browser_ui -- "calls into" --> include_prefetch
    src_css -- "calls into" --> include_browser_ui
    src_css -- "calls into" --> src_tab
    src_css -- "calls into" --> src_text_shape
    src_css -- "calls into" --> include_page_view
    src_css -- "calls into" --> include_browser
    src_css -- "calls into" --> src_local_store
    src_css -- "calls into" --> include_secure_fetch
    src_tab -- "calls into" --> include_browser_ui
    src_tab -- "calls into" --> src_css
    src_tab -- "calls into" --> src_text_shape
    src_tab -- "calls into" --> include_page_view
    src_tab -- "calls into" --> include_browser
    src_tab -- "calls into" --> include_secure_fetch
    src_tab -- "calls into" --> include_prefetch
    src_text_shape -- "calls into" --> include_browser_ui
    src_text_shape -- "calls into" --> src_css
    src_text_shape -- "calls into" --> src_tab
    src_text_shape -- "calls into" --> include_page_view
    src_text_shape -- "calls into" --> include_browser
    src_text_shape -- "calls into" --> include_secure_fetch
    src_text_shape -- "calls into" --> include_prefetch
    include_page_view -- "calls into" --> include_browser_ui
    include_page_view -- "calls into" --> src_css
    include_page_view -- "calls into" --> src_tab
    include_page_view -- "calls into" --> src_text_shape
    include_page_view -- "calls into" --> include_browser
    include_browser -- "calls into" --> include_browser_ui
    include_browser -- "calls into" --> src_css
    include_browser -- "calls into" --> src_tab
    include_browser -- "calls into" --> src_text_shape
    include_browser -- "calls into" --> include_page_view
    include_browser -- "calls into" --> include_secure_fetch
    src_local_store -- "calls into" --> include_browser_ui
    src_local_store -- "calls into" --> src_css
    src_local_store -- "calls into" --> src_tab
    src_local_store -- "calls into" --> src_text_shape
    src_local_store -- "calls into" --> include_browser
    src_local_store -- "calls into" --> include_secure_fetch
    include_secure_fetch -- "calls into" --> include_browser_ui
    include_secure_fetch -- "calls into" --> src_css
    include_secure_fetch -- "calls into" --> src_tab
    include_secure_fetch -- "calls into" --> src_text_shape
    include_prefetch -- "calls into" --> include_browser_ui
    include_prefetch -- "calls into" --> src_css
    include_prefetch -- "calls into" --> src_tab
    include_prefetch -- "calls into" --> src_text_shape
    click include_browser_ui href "./include_browser_ui.md" "Details"
    click src_css href "./src_css.md" "Details"
    click src_tab href "./src_tab.md" "Details"
    click src_text_shape href "./src_text_shape.md" "Details"
    click include_page_view href "./include_page_view.md" "Details"
    click include_browser href "./include_browser.md" "Details"
    click src_local_store href "./src_local_store.md" "Details"
    click include_secure_fetch href "./include_secure_fetch.md" "Details"
    click include_prefetch href "./include_prefetch.md" "Details"
```

## Details

Static architecture map of 290 files (c, h, py, sh) in 9 components: include: browser_ui, src: css, src: tab, src: text_shape, include: page_view, include: browser, src: local_store, include: secure_fetch. Structure is extracted statically without LLM calls; component prose may be enriched locally.

### include: browser_ui (1)

include: browser_ui groups 59 files (c, h) around FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL, PREFS_MAX_TITLE, PREFS_MAX_BOOKMARKS. ui_input_state: Live editable state for one form text control, aliasing a block of the...

**Related Classes/Methods**:

- <a href="../include/prefs.h#L2-L25">include/prefs.h::FREEDOM_PREFS_H</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_VERSION</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_URL</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_TITLE</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_BOOKMARKS</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_HISTORY</a>
- <a href="../include/prefs.h#L31-L33">include/prefs.h::PREFS_MAX_TEXT</a>
- <a href="../include/prefs.h#L34-L35">include/prefs.h::PREFS_PAGE_HISTORY</a>

### src: css (2)

src: css groups 53 files (c, h) around FREEDOM_CSS_H, css_status, css_align, css_display, css_justify. cx_style: A box's resolved style, in the SAME value-spaces as css.h: position uses...

**Related Classes/Methods**:

- <a href="../include/css.h#L2-L27">include/css.h::FREEDOM_CSS_H</a>
- <a href="../include/css.h#L28-L33">include/css.h::css_status</a>
- <a href="../include/css.h#L34-L41">include/css.h::css_align</a>
- <a href="../include/css.h#L42-L68">include/css.h::css_display</a>
- <a href="../include/css.h#L69-L79">include/css.h::css_justify</a>
- <a href="../include/css.h">include/css.h::CSS_GAP_MAX</a>
- <a href="../include/css.h">include/css.h::CSS_GRID_COLS_MAX</a>
- <a href="../include/css.h#L82-L83">include/css.h::CSS_GRID_TRACKS_MAX</a>

### src: tab (3)

src: tab groups 45 files (c, h) around FREEDOM_HTML_PARSE_H, hp_status, max_bytes, hp_config, hp_document. dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all...

**Related Classes/Methods**:

- <a href="../include/html_parse.h#L2-L21">include/html_parse.h::FREEDOM_HTML_PARSE_H</a>
- <a href="../include/html_parse.h#L22-L30">include/html_parse.h::hp_status</a>
- <a href="../include/html_parse.h">include/html_parse.h::max_bytes</a>
- <a href="../include/html_parse.h#L32-L38">include/html_parse.h::hp_config</a>
- <a href="../include/html_parse.h#L39-L40">include/html_parse.h::hp_document</a>
- <a href="../include/html_parse.h#L41-L46">include/html_parse.h::HP_DEFAULT_MAX_BYTES</a>
- <a href="../include/html_parse.h">include/html_parse.h::dropped</a>
- <a href="../include/html_parse.h#L48-L56">include/html_parse.h::HP_MAX_SCRIPTS</a>

### src: text_shape (4)

src: text_shape groups 42 files (c, h) around FREEDOM_JS_POLICY_H, membership, jsp_mode, allowlist, jsp_trusted. du_is_data_url: 16 MiB of encoded text (~12 MiB decoded) -- generous for any real...

**Related Classes/Methods**:

- <a href="../include/js_policy.h#L2-L15">include/js_policy.h::FREEDOM_JS_POLICY_H</a>
- <a href="../include/js_policy.h#L16-L26">include/js_policy.h::membership</a>
- <a href="../include/js_policy.h#L27-L33">include/js_policy.h::jsp_mode</a>
- <a href="../include/js_policy.h#L34-L44">include/js_policy.h::allowlist</a>
- <a href="../include/js_policy.h#L45-L53">include/js_policy.h::jsp_trusted</a>
- <a href="../include/js_policy.h#L54-L63">include/js_policy.h::jsp_present_trusted</a>
- <a href="../include/js_policy.h#L64-L66">include/js_policy.h::jsp_mode_str</a>
- <a href="../include/data_url.h#L2-L20">include/data_url.h::FREEDOM_DATA_URL_H</a>

### include: page_view (5)

include: page_view groups 19 files (c, h) around FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_caps, rdp_img_decision. bx_edges: anything longer fails closed instead of truncating into a wrong match....

**Related Classes/Methods**:

- <a href="../include/render_policy.h#L2-L26">include/render_policy.h::FREEDOM_RENDER_POLICY_H</a>
- <a href="../include/render_policy.h#L27-L31">include/render_policy.h::RDP_TRACKER_MAX_DIM</a>
- <a href="../include/render_policy.h">include/render_policy.h::images</a>
- <a href="../include/render_policy.h#L32-L38">include/render_policy.h::rdp_caps</a>
- <a href="../include/render_policy.h#L39-L52">include/render_policy.h::rdp_img_decision</a>
- <a href="../include/render_policy.h#L53-L55">include/render_policy.h::rdp_is_tracking_pixel</a>
- <a href="../include/render_policy.h#L56-L65">include/render_policy.h::size</a>
- <a href="../include/render_policy.h#L66-L68">include/render_policy.h::rdp_img_reason</a>

### include: browser (6)

include: browser groups 19 files (c, h) around FREEDOM_HOSTBLOCK_H, hb_set, hb_list, hb_decision, hb_status. browser_free: Zero-initialise or reset a state.

**Related Classes/Methods**:

- <a href="../include/hostblock.h#L2-L28">include/hostblock.h::FREEDOM_HOSTBLOCK_H</a>
- <a href="../include/hostblock.h#L29-L31">include/hostblock.h::hb_set</a>
- <a href="../include/hostblock.h#L32-L36">include/hostblock.h::hb_list</a>
- <a href="../include/hostblock.h#L37-L41">include/hostblock.h::hb_decision</a>
- <a href="../include/hostblock.h#L42-L48">include/hostblock.h::hb_status</a>
- <a href="../include/hostblock.h#L49-L51">include/hostblock.h::hb_new</a>
- <a href="../include/hostblock.h#L52-L64">include/hostblock.h::hb_free</a>
- <a href="../include/hostblock.h#L65-L74">include/hostblock.h::walked</a>

### src: local_store (7)

src: local_store groups 16 files (c, h) around FREEDOM_LOCAL_STORE_H, LS_KEY_LEN, LS_SALT_LEN, LS_NONCE_LEN, LS_TAG_LEN. cf_set_store: Cache-aware GET.

**Related Classes/Methods**:

- <a href="../include/local_store.h#L2-L25">include/local_store.h::FREEDOM_LOCAL_STORE_H</a>
- <a href="../include/local_store.h">include/local_store.h::LS_KEY_LEN</a>
- <a href="../include/local_store.h">include/local_store.h::LS_SALT_LEN</a>
- <a href="../include/local_store.h">include/local_store.h::LS_NONCE_LEN</a>
- <a href="../include/local_store.h">include/local_store.h::LS_TAG_LEN</a>
- <a href="../include/local_store.h">include/local_store.h::LS_HEADER_LEN</a>
- <a href="../include/local_store.h">include/local_store.h::LS_OVERHEAD</a>
- <a href="../include/local_store.h#L32-L33">include/local_store.h::LS_MAX_PLAINTEXT</a>

### include: secure_fetch (8)

include: secure_fetch groups 13 files (c, h) around FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER. fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define...

**Related Classes/Methods**:

- <a href="../include/anti_fp.h#L2-L21">include/anti_fp.h::FREEDOM_ANTI_FP_H</a>
- <a href="../include/anti_fp.h#L22-L30">include/anti_fp.h::FP_TIMER_RESOLUTION_MS</a>
- <a href="../include/anti_fp.h#L31-L32">include/anti_fp.h::FP_USER_AGENT</a>
- <a href="../include/anti_fp.h">include/anti_fp.h::FP_ACCEPT_LANGUAGE</a>
- <a href="../include/anti_fp.h#L34-L39">include/anti_fp.h::FP_ACCEPT_LANGUAGE_HEADER</a>
- <a href="../include/anti_fp.h#L40-L44">include/anti_fp.h::FP_ACCEPT_HEADER_NAV</a>
- <a href="../include/anti_fp.h">include/anti_fp.h::FP_SEC_FETCH_DEST_NAV</a>
- <a href="../include/anti_fp.h">include/anti_fp.h::FP_SEC_FETCH_MODE_NAV</a>

### include: prefetch (9)

include: prefetch groups 6 files (c, h) around FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES. im_resolve: Resolves specifier as imported from base (the importing module's URL).

**Related Classes/Methods**:

- <a href="../include/import_map.h#L2-L12">include/import_map.h::FREEDOM_IMPORT_MAP_H</a>
- <a href="../include/import_map.h#L13-L16">include/import_map.h::algorithm</a>
- <a href="../include/import_map.h">include/import_map.h::IM_MAX_TEXT</a>
- <a href="../include/import_map.h">include/import_map.h::IM_MAX_ENTRIES</a>
- <a href="../include/import_map.h#L19-L22">include/import_map.h::IM_MAX_SCOPES</a>
- <a href="../include/import_map.h#L23-L27">include/import_map.h::im_map</a>
- <a href="../include/import_map.h#L28-L32">include/import_map.h::map</a>
- <a href="../include/import_map.h#L33-L36">include/import_map.h::im_resolve</a>
