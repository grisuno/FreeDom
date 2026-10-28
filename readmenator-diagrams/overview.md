```mermaid
graph LR
    include_browser_ui["include: browser_ui"]
    include_css["include: css"]
    src_tab["src: tab"]
    src_text_shape["src: text_shape"]
    include_page_view["include: page_view"]
    include_browser["include: browser"]
    src_local_store["src: local_store"]
    include_secure_fetch["include: secure_fetch"]
    include_tab["include: tab"]
    include_prefetch["include: prefetch"]
    include_sha2["include: sha2"]
    include_subreq_batch["include: subreq_batch"]
    include_browser_ui -- "calls into" --> include_prefetch
    include_browser_ui -- "calls into" --> include_css
    include_browser_ui -- "calls into" --> src_tab
    include_browser_ui -- "calls into" --> src_text_shape
    include_browser_ui -- "calls into" --> include_page_view
    include_browser_ui -- "calls into" --> include_browser
    include_browser_ui -- "calls into" --> src_local_store
    include_browser_ui -- "calls into" --> include_secure_fetch
    include_browser_ui -- "calls into" --> include_tab
    include_prefetch -- "calls into" --> include_browser_ui
    include_prefetch -- "calls into" --> include_css
    include_prefetch -- "calls into" --> src_tab
    include_subreq_batch -- "calls into" --> src_tab
    include_css -- "calls into" --> include_browser_ui
    include_css -- "calls into" --> src_tab
    include_css -- "calls into" --> src_text_shape
    include_css -- "calls into" --> include_page_view
    include_css -- "calls into" --> src_local_store
    include_css -- "calls into" --> include_secure_fetch
    include_css -- "calls into" --> include_tab
    src_tab -- "calls into" --> include_browser_ui
    src_tab -- "calls into" --> include_prefetch
    src_tab -- "calls into" --> include_sha2
    src_tab -- "calls into" --> include_subreq_batch
    src_tab -- "calls into" --> include_css
    src_tab -- "calls into" --> src_text_shape
    src_tab -- "calls into" --> include_page_view
    src_tab -- "calls into" --> include_browser
    src_tab -- "calls into" --> include_secure_fetch
    src_tab -- "calls into" --> include_tab
    src_text_shape -- "calls into" --> include_browser_ui
    src_text_shape -- "calls into" --> include_prefetch
    src_text_shape -- "calls into" --> include_css
    src_text_shape -- "calls into" --> src_tab
    src_text_shape -- "calls into" --> include_page_view
    src_text_shape -- "calls into" --> include_browser
    src_text_shape -- "calls into" --> include_secure_fetch
    src_text_shape -- "calls into" --> include_tab
    include_page_view -- "calls into" --> include_browser_ui
    include_page_view -- "calls into" --> include_css
    include_page_view -- "calls into" --> src_tab
    include_page_view -- "calls into" --> src_text_shape
    include_page_view -- "calls into" --> include_browser
    include_browser -- "calls into" --> include_browser_ui
    include_browser -- "calls into" --> include_css
    include_browser -- "calls into" --> src_tab
    include_browser -- "calls into" --> include_page_view
    src_local_store -- "calls into" --> include_browser_ui
    src_local_store -- "calls into" --> include_css
    src_local_store -- "calls into" --> src_tab
    src_local_store -- "calls into" --> src_text_shape
    src_local_store -- "calls into" --> include_browser
    src_local_store -- "calls into" --> include_secure_fetch
    include_secure_fetch -- "calls into" --> include_browser_ui
    include_secure_fetch -- "calls into" --> include_css
    include_secure_fetch -- "calls into" --> src_tab
    include_secure_fetch -- "calls into" --> src_text_shape
    include_tab -- "calls into" --> include_browser_ui
    include_tab -- "calls into" --> include_css
    include_tab -- "calls into" --> src_tab
    include_tab -- "depends on" --> include_page_view
    click include_browser_ui href "./include_browser_ui.md" "Details"
    click include_css href "./include_css.md" "Details"
    click src_tab href "./src_tab.md" "Details"
    click src_text_shape href "./src_text_shape.md" "Details"
    click include_page_view href "./include_page_view.md" "Details"
    click include_browser href "./include_browser.md" "Details"
    click src_local_store href "./src_local_store.md" "Details"
    click include_secure_fetch href "./include_secure_fetch.md" "Details"
    click include_tab href "./include_tab.md" "Details"
    click include_prefetch href "./include_prefetch.md" "Details"
```

## Details

Static architecture map of 305 files (c, h, py, sh) in 12 components: include: browser_ui, include: css, src: tab, src: text_shape, include: page_view, include: browser, src: local_store, include: secure_fetch. Structure is extracted statically without LLM calls; component prose may be enriched locally.

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

### include: css (2)

include: css groups 52 files (c, h) around FREEDOM_CSS_H, css_status, css_align, css_display, css_justify. cx_style: A box's resolved style, in the SAME value-spaces as css.h: position uses...

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

src: tab groups 48 files (c, h) around FREEDOM_HTML_PARSE_H, hp_status, max_bytes, hp_config, hp_document. dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all...

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

include: page_view groups 19 files (c, h) around FREEDOM_PAGE_VIEW_H, pv_status, PV_BSHADOW_LAYERS, PV_MAUTO_LEFT, PV_MAUTO_RIGHT. bx_edges: anything longer fails closed instead of truncating into a wrong match....

**Related Classes/Methods**:

- <a href="../include/page_view.h#L2-L33">include/page_view.h::FREEDOM_PAGE_VIEW_H</a>
- <a href="../include/page_view.h#L34-L43">include/page_view.h::pv_status</a>
- <a href="../include/page_view.h#L44-L45">include/page_view.h::PV_BSHADOW_LAYERS</a>
- <a href="../include/page_view.h">include/page_view.h::PV_MAUTO_LEFT</a>
- <a href="../include/page_view.h">include/page_view.h::PV_MAUTO_RIGHT</a>
- <a href="../include/page_view.h">include/page_view.h::PV_MAUTO_TOP</a>
- <a href="../include/page_view.h#L49-L52">include/page_view.h::PV_MAUTO_BOTTOM</a>
- <a href="../include/page_view.h">include/page_view.h::PV_LEN_UNSET</a>

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

### include: tab (9)

include: tab groups 7 files (c, h) around FREEDOM_FRAME_BROKER_H, FBK_MAX_FRAMES, FBK_MAX_DEPTH, FBK_MAX_MSG, FBK_ORIGIN_MAX. fbk_origin_of: Serialized origin ("https://host[:port]", lowercase) or "null" for...

**Related Classes/Methods**:

- <a href="../include/frame_broker.h#L2-L15">include/frame_broker.h::FREEDOM_FRAME_BROKER_H</a>
- <a href="../include/frame_broker.h">include/frame_broker.h::FBK_MAX_FRAMES</a>
- <a href="../include/frame_broker.h">include/frame_broker.h::FBK_MAX_DEPTH</a>
- <a href="../include/frame_broker.h">include/frame_broker.h::FBK_MAX_MSG</a>
- <a href="../include/frame_broker.h">include/frame_broker.h::FBK_ORIGIN_MAX</a>
- <a href="../include/frame_broker.h#L20-L21">include/frame_broker.h::FBK_URL_MAX</a>
- <a href="../include/frame_broker.h#L22-L23">include/frame_broker.h::fbk_rel</a>
- <a href="../include/frame_broker.h#L24-L29">include/frame_broker.h::fbk_verdict</a>

### include: prefetch (10)

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

### include: sha2 (11)

include: sha2 groups 3 files (c, h) around FREEDOM_SHA2_H, sha_alg, SHA_MAX_DIGEST, sha_digest_len, sha_alg_from_name. sha_digest_len: sha2 -- one-shot SHA-1 / SHA-256 / SHA-384 / SHA-512 (FIPS 180-4)...

**Related Classes/Methods**:

- <a href="../include/sha2.h#L2-L15">include/sha2.h::FREEDOM_SHA2_H</a>
- <a href="../include/sha2.h#L16-L17">include/sha2.h::sha_alg</a>
- <a href="../include/sha2.h#L18-L20">include/sha2.h::SHA_MAX_DIGEST</a>
- <a href="../include/sha2.h#L21-L23">include/sha2.h::sha_digest_len</a>
- <a href="../include/sha2.h#L24-L27">include/sha2.h::sha_alg_from_name</a>
- <a href="../include/sha2.h#L28-L30">include/sha2.h::sha_digest</a>
- <a href="../src/sha2.c">src/sha2.c::ROR32</a>
- <a href="../src/sha2.c">src/sha2.c::ROL32</a>

### include: subreq_batch (12)

include: subreq_batch groups 3 files (c, h) around SUBREQ_BATCH_H, SQB_MAX_JOBS, sqb_req, ok, sqb_res. sqb_res: #ifndef SUBREQ_BATCH_H #define SUBREQ_BATCH_H #include <stddef.h> #define...

**Related Classes/Methods**:

- <a href="../include/subreq_batch.h#L10-L13">include/subreq_batch.h::SUBREQ_BATCH_H</a>
- <a href="../include/subreq_batch.h#L14-L15">include/subreq_batch.h::SQB_MAX_JOBS</a>
- <a href="../include/subreq_batch.h#L16-L22">include/subreq_batch.h::sqb_req</a>
- <a href="../include/subreq_batch.h">include/subreq_batch.h::ok</a>
- <a href="../include/subreq_batch.h#L23-L33">include/subreq_batch.h::sqb_res</a>
- <a href="../include/subreq_batch.h#L34-L36">include/subreq_batch.h::sqb</a>
- <a href="../include/subreq_batch.h#L37-L40">include/subreq_batch.h::sqb_new</a>
- <a href="../include/subreq_batch.h">include/subreq_batch.h::sqb_submit</a>
