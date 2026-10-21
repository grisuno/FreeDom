```mermaid
graph LR
    src_tab["src: tab"]
    include_css["include: css"]
    include_browser_ui["include: browser_ui"]
    src_freedom["src: freedom"]
    include_page_view["include: page_view"]
    include_text_shape["include: text_shape"]
    include_local_store["include: local_store"]
    gui["gui"]
    include_secure_fetch["include: secure_fetch"]
    include_prefetch["include: prefetch"]
    src_tab -- "calls into" --> include_prefetch
    src_tab -- "calls into" --> include_css
    src_tab -- "calls into" --> include_browser_ui
    src_tab -- "calls into" --> src_freedom
    src_tab -- "calls into" --> include_page_view
    src_tab -- "calls into" --> include_text_shape
    src_tab -- "depends on" --> gui
    src_tab -- "calls into" --> include_secure_fetch
    include_prefetch -- "calls into" --> src_tab
    include_prefetch -- "calls into" --> include_css
    include_prefetch -- "calls into" --> include_browser_ui
    include_css -- "calls into" --> src_tab
    include_css -- "calls into" --> include_browser_ui
    include_css -- "calls into" --> src_freedom
    include_css -- "calls into" --> include_page_view
    include_css -- "depends on" --> include_text_shape
    include_browser_ui -- "calls into" --> src_tab
    include_browser_ui -- "calls into" --> include_prefetch
    include_browser_ui -- "calls into" --> include_css
    include_browser_ui -- "calls into" --> src_freedom
    include_browser_ui -- "calls into" --> include_page_view
    include_browser_ui -- "calls into" --> include_text_shape
    include_browser_ui -- "calls into" --> include_local_store
    include_browser_ui -- "calls into" --> gui
    include_browser_ui -- "calls into" --> include_secure_fetch
    src_freedom -- "calls into" --> src_tab
    src_freedom -- "calls into" --> include_prefetch
    src_freedom -- "calls into" --> include_css
    src_freedom -- "calls into" --> include_browser_ui
    src_freedom -- "calls into" --> include_page_view
    src_freedom -- "calls into" --> include_text_shape
    src_freedom -- "calls into" --> gui
    src_freedom -- "calls into" --> include_secure_fetch
    include_page_view -- "calls into" --> src_tab
    include_page_view -- "calls into" --> include_css
    include_page_view -- "calls into" --> include_browser_ui
    include_page_view -- "calls into" --> src_freedom
    include_page_view -- "calls into" --> include_text_shape
    include_page_view -- "depends on" --> gui
    include_text_shape -- "calls into" --> src_tab
    include_text_shape -- "calls into" --> include_prefetch
    include_text_shape -- "calls into" --> include_css
    include_text_shape -- "calls into" --> include_browser_ui
    include_text_shape -- "calls into" --> src_freedom
    include_text_shape -- "calls into" --> include_page_view
    include_local_store -- "calls into" --> src_tab
    include_local_store -- "calls into" --> include_browser_ui
    include_local_store -- "calls into" --> src_freedom
    gui -- "calls into" --> src_tab
    gui -- "calls into" --> include_css
    gui -- "calls into" --> include_browser_ui
    gui -- "calls into" --> src_freedom
    gui -- "calls into" --> include_page_view
    gui -- "depends on" --> include_local_store
    include_secure_fetch -- "calls into" --> src_tab
    include_secure_fetch -- "calls into" --> include_css
    include_secure_fetch -- "calls into" --> include_browser_ui
    include_secure_fetch -- "calls into" --> src_freedom
    click src_tab href "./src_tab.md" "Details"
    click include_css href "./include_css.md" "Details"
    click include_browser_ui href "./include_browser_ui.md" "Details"
    click src_freedom href "./src_freedom.md" "Details"
    click include_page_view href "./include_page_view.md" "Details"
    click include_text_shape href "./include_text_shape.md" "Details"
    click include_local_store href "./include_local_store.md" "Details"
    click gui href "./gui.md" "Details"
    click include_secure_fetch href "./include_secure_fetch.md" "Details"
    click include_prefetch href "./include_prefetch.md" "Details"
```

## Details

Static architecture map of 288 files (c, h, py, sh) in 10 components: src: tab, include: css, include: browser_ui, src: freedom, include: page_view, include: text_shape, include: local_store, gui. Structure is extracted statically without LLM calls; component prose may be enriched locally.

### src: tab (1)

src: tab groups 57 files (c, h) around FREEDOM_HTML_PARSE_H, hp_status, max_bytes, hp_config, hp_document.

**Related Classes/Methods**:

- <a href="../include/html_parse.h#L2-L21">include/html_parse.h::FREEDOM_HTML_PARSE_H</a>
- <a href="../include/html_parse.h#L22-L30">include/html_parse.h::hp_status</a>
- <a href="../include/html_parse.h">include/html_parse.h::max_bytes</a>
- <a href="../include/html_parse.h#L32-L38">include/html_parse.h::hp_config</a>
- <a href="../include/html_parse.h#L39-L40">include/html_parse.h::hp_document</a>
- <a href="../include/html_parse.h#L41-L46">include/html_parse.h::HP_DEFAULT_MAX_BYTES</a>
- <a href="../include/html_parse.h">include/html_parse.h::dropped</a>
- <a href="../include/html_parse.h#L48-L56">include/html_parse.h::HP_MAX_SCRIPTS</a>

### include: css (2)

include: css groups 50 files (c, h) around FREEDOM_CSS_COLOR_H, b, cc_rgb, cc_status, cc_pack. fuzz_root_match: Root matcher for the attribute-scoped custom-property path: a fixed...

**Related Classes/Methods**:

- <a href="../include/css_color.h#L2-L25">include/css_color.h::FREEDOM_CSS_COLOR_H</a>
- <a href="../include/css_color.h">include/css_color.h::b</a>
- <a href="../include/css_color.h#L27-L30">include/css_color.h::cc_rgb</a>
- <a href="../include/css_color.h#L31-L48">include/css_color.h::cc_status</a>
- <a href="../include/css_color.h#L49-L58">include/css_color.h::cc_pack</a>
- <a href="../include/css_color.h">include/css_color.h::CC_COLOR_CURRENT</a>
- <a href="../include/css_color.h#L60-L62">include/css_color.h::CC_COLOR_TRANSPARENT</a>
- <a href="../include/css.h#L2-L27">include/css.h::FREEDOM_CSS_H</a>

### include: browser_ui (3)

include: browser_ui groups 38 files (c, h) around FREEDOM_IMAGE_DECODE_H, guards, img_format, img_status, img_pixels. poke_and_free: Touch every claimed pixel corner so the sanitizer flags an...

**Related Classes/Methods**:

- <a href="../include/image_decode.h#L2-L24">include/image_decode.h::FREEDOM_IMAGE_DECODE_H</a>
- <a href="../include/image_decode.h#L25-L32">include/image_decode.h::guards</a>
- <a href="../include/image_decode.h#L33-L40">include/image_decode.h::img_format</a>
- <a href="../include/image_decode.h#L41-L55">include/image_decode.h::img_status</a>
- <a href="../include/image_decode.h">include/image_decode.h::img_pixels</a>
- <a href="../include/image_decode.h#L56-L64">include/image_decode.h::width</a>
- <a href="../include/image_decode.h">include/image_decode.h::IMG_MAX_DIM</a>
- <a href="../include/image_decode.h#L66-L77">include/image_decode.h::IMG_MAX_PIXELS</a>

### src: freedom (4)

src: freedom groups 36 files (c, h) around FREEDOM_HOSTBLOCK_H, hb_set, hb_list, hb_decision, hb_status. hls_segment: or variant info.

**Related Classes/Methods**:

- <a href="../include/hostblock.h#L2-L28">include/hostblock.h::FREEDOM_HOSTBLOCK_H</a>
- <a href="../include/hostblock.h#L29-L31">include/hostblock.h::hb_set</a>
- <a href="../include/hostblock.h#L32-L36">include/hostblock.h::hb_list</a>
- <a href="../include/hostblock.h#L37-L41">include/hostblock.h::hb_decision</a>
- <a href="../include/hostblock.h#L42-L48">include/hostblock.h::hb_status</a>
- <a href="../include/hostblock.h#L49-L51">include/hostblock.h::hb_new</a>
- <a href="../include/hostblock.h#L52-L64">include/hostblock.h::hb_free</a>
- <a href="../include/hostblock.h#L65-L74">include/hostblock.h::walked</a>

### include: page_view (5)

include: page_view groups 21 files (c, h) around FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_caps, rdp_img_decision. bx_edges: anything longer fails closed instead of truncating into a wrong match....

**Related Classes/Methods**:

- <a href="../include/render_policy.h#L2-L26">include/render_policy.h::FREEDOM_RENDER_POLICY_H</a>
- <a href="../include/render_policy.h#L27-L31">include/render_policy.h::RDP_TRACKER_MAX_DIM</a>
- <a href="../include/render_policy.h">include/render_policy.h::images</a>
- <a href="../include/render_policy.h#L32-L38">include/render_policy.h::rdp_caps</a>
- <a href="../include/render_policy.h#L39-L52">include/render_policy.h::rdp_img_decision</a>
- <a href="../include/render_policy.h#L53-L55">include/render_policy.h::rdp_is_tracking_pixel</a>
- <a href="../include/render_policy.h#L56-L65">include/render_policy.h::size</a>
- <a href="../include/render_policy.h#L66-L68">include/render_policy.h::rdp_img_reason</a>

### include: text_shape (6)

include: text_shape groups 20 files (c, h) around FREEDOM_DATA_URL_H, allocation, du_status, DU_MAX_ENCODED_LEN, du_is_data_url. libFuzzer harness for the webfont lookahead scanner (spec/webfont.md).

**Related Classes/Methods**:

- <a href="../include/data_url.h#L2-L20">include/data_url.h::FREEDOM_DATA_URL_H</a>
- <a href="../include/data_url.h#L21-L26">include/data_url.h::allocation</a>
- <a href="../include/data_url.h#L27-L42">include/data_url.h::du_status</a>
- <a href="../include/data_url.h#L43-L45">include/data_url.h::DU_MAX_ENCODED_LEN</a>
- <a href="../include/data_url.h#L46-L58">include/data_url.h::du_is_data_url</a>
- <a href="../include/data_url.h#L59-L72">include/data_url.h::closed</a>
- <a href="../include/webfont.h#L2-L19">include/webfont.h::FREEDOM_WEBFONT_H</a>
- <a href="../include/webfont.h">include/webfont.h::WF_FAMILY_MAX</a>

### include: local_store (7)

include: local_store groups 16 files (c, h) around FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL, PREFS_MAX_TITLE, PREFS_MAX_BOOKMARKS. ds_free: Reads and decrypts path.

**Related Classes/Methods**:

- <a href="../include/prefs.h#L2-L25">include/prefs.h::FREEDOM_PREFS_H</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_VERSION</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_URL</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_TITLE</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_BOOKMARKS</a>
- <a href="../include/prefs.h">include/prefs.h::PREFS_MAX_HISTORY</a>
- <a href="../include/prefs.h#L31-L33">include/prefs.h::PREFS_MAX_TEXT</a>
- <a href="../include/prefs.h#L34-L35">include/prefs.h::PREFS_PAGE_HISTORY</a>

### gui (8)

gui groups 15 files (c, h) around FREEDOM_SVG_RENDER_H, sv_status, SV_MAX_SHAPES, SV_MAX_POINTS, SV_MAX_SEGS. ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb...

**Related Classes/Methods**:

- <a href="../include/svg_render.h#L2-L24">include/svg_render.h::FREEDOM_SVG_RENDER_H</a>
- <a href="../include/svg_render.h#L25-L31">include/svg_render.h::sv_status</a>
- <a href="../include/svg_render.h">include/svg_render.h::SV_MAX_SHAPES</a>
- <a href="../include/svg_render.h">include/svg_render.h::SV_MAX_POINTS</a>
- <a href="../include/svg_render.h">include/svg_render.h::SV_MAX_SEGS</a>
- <a href="../include/svg_render.h">include/svg_render.h::SV_MAX_DEPTH</a>
- <a href="../include/svg_render.h">include/svg_render.h::SV_TEXT_MAX</a>
- <a href="../include/svg_render.h#L37-L40">include/svg_render.h::SV_MAX_INPUT</a>

### include: secure_fetch (9)

include: secure_fetch groups 10 files (c, h) around FREEDOM_ANTI_FP_H, FP_TIMER_RESOLUTION_MS, FP_USER_AGENT, FP_ACCEPT_LANGUAGE, FP_ACCEPT_LANGUAGE_HEADER. fp_accept_language_header: #define FP_SEC_FETCH_DEST_NAV  "document" #define...

**Related Classes/Methods**:

- <a href="../include/anti_fp.h#L2-L21">include/anti_fp.h::FREEDOM_ANTI_FP_H</a>
- <a href="../include/anti_fp.h#L22-L30">include/anti_fp.h::FP_TIMER_RESOLUTION_MS</a>
- <a href="../include/anti_fp.h#L31-L32">include/anti_fp.h::FP_USER_AGENT</a>
- <a href="../include/anti_fp.h">include/anti_fp.h::FP_ACCEPT_LANGUAGE</a>
- <a href="../include/anti_fp.h#L34-L39">include/anti_fp.h::FP_ACCEPT_LANGUAGE_HEADER</a>
- <a href="../include/anti_fp.h#L40-L44">include/anti_fp.h::FP_ACCEPT_HEADER_NAV</a>
- <a href="../include/anti_fp.h">include/anti_fp.h::FP_SEC_FETCH_DEST_NAV</a>
- <a href="../include/anti_fp.h">include/anti_fp.h::FP_SEC_FETCH_MODE_NAV</a>

### include: prefetch (10)

include: prefetch groups 8 files (c, h) around FREEDOM_IMPORT_MAP_H, algorithm, IM_MAX_TEXT, IM_MAX_ENTRIES, IM_MAX_SCOPES. libFuzzer harness for the prefetch lookahead scanner (Hito 29).

**Related Classes/Methods**:

- <a href="../include/import_map.h#L2-L12">include/import_map.h::FREEDOM_IMPORT_MAP_H</a>
- <a href="../include/import_map.h#L13-L16">include/import_map.h::algorithm</a>
- <a href="../include/import_map.h">include/import_map.h::IM_MAX_TEXT</a>
- <a href="../include/import_map.h">include/import_map.h::IM_MAX_ENTRIES</a>
- <a href="../include/import_map.h#L19-L22">include/import_map.h::IM_MAX_SCOPES</a>
- <a href="../include/import_map.h#L23-L27">include/import_map.h::im_map</a>
- <a href="../include/import_map.h#L28-L32">include/import_map.h::map</a>
- <a href="../include/import_map.h#L33-L36">include/import_map.h::im_resolve</a>
