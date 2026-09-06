# Subsystem: include

## include/anti_fp.h
- Layer: utility
- Doc: ifndef FREEDOM_ANTI_FP_H define FREEDOM_ANTI_FP_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freed
- Language: h
- Symbols:
  - `FREEDOM_ANTI_FP_H` (macro, line 2)
  - `FP_TIMER_RESOLUTION_MS` (macro, line 21)
  - `FP_USER_AGENT` (macro, line 31)
  - `FP_ACCEPT_LANGUAGE` (macro, line 33)
  - `FP_ACCEPT_LANGUAGE_HEADER` (macro, line 34)
  - `FP_ACCEPT_HEADER_NAV` (macro, line 40)
  - `FP_SEC_FETCH_DEST_NAV` (macro, line 45)
  - `FP_SEC_FETCH_MODE_NAV` (macro, line 46)
  - `FP_SEC_FETCH_SITE_NONE` (macro, line 47)
  - `FP_SEC_FETCH_USER_ON` (macro, line 48)

## include/block_flow.h
- Layer: utility
- Doc: block_flow (bf_) -- vertical margin collapsing for block-level boxes.
- Language: h
- Symbols:
  - `bf_collapse_n` (function, line 33) `* bf_collapse_n((double[])`
  - `FREEDOM_BLOCK_FLOW_H` (macro, line 11)

## include/box_style.h
- Layer: utility
- Doc: ifndef FREEDOM_BOX_STYLE_H define FREEDOM_BOX_STYLE_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supp
- Language: h
- Symbols:
  - `bx_edges` (struct, line 46)
  - `bx_box` (struct, line 50)
  - `bx_hplace` (struct, line 63)
  - `bx_bg_layer` (struct, line 254)
  - `FREEDOM_BOX_STYLE_H` (macro, line 2)
  - `BX_TAG_NAME_MAX` (macro, line 33)

## include/box_tree.h
- Layer: utility
- Doc: ifndef FREEDOM_BOX_TREE_H define FREEDOM_BOX_TREE_H  include <stddef.h>  include "box_style.h" include "flex_layout.h" i
- Language: h
- Symbols:
  - `bt_node` (struct, line 63)
  - `bt_positioned` (struct, line 122)
  - `FREEDOM_BOX_TREE_H` (macro, line 2)
  - `BT_MAX_DEPTH` (macro, line 35)
  - `BT_MAX_CHILDREN` (macro, line 36)
  - `BT_MAX_POSITIONED` (macro, line 42)
  - `BT_POS_STATIC` (macro, line 47)
  - `BT_POS_RELATIVE` (macro, line 48)
  - `BT_POS_ABSOLUTE` (macro, line 49)
  - `BT_POS_FIXED` (macro, line 50)
  - `BT_POS_STICKY` (macro, line 51)
  - `BT_ALIGN_START` (macro, line 58)
  - `BT_ALIGN_CENTER` (macro, line 59)
  - `BT_ALIGN_END` (macro, line 60)
  - `BT_ALIGN_STRETCH` (macro, line 61)

## include/browser.h
- Layer: utility
- Doc: ifndef FREEDOM_BROWSER_H define FREEDOM_BROWSER_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Freed
- Language: h
- Symbols:
  - `browser_state` (struct, line 27)
  - `FREEDOM_BROWSER_H` (macro, line 2)
  - `BROWSER_URL_MAX` (macro, line 20)
  - `BROWSER_STATUS_MAX` (macro, line 24)
  - `BROWSER_STATUS_DURATION_MS` (macro, line 25)

## include/compositor.h
- Layer: utility
- Doc: ifndef FREEDOM_COMPOSITOR_H define FREEDOM_COMPOSITOR_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C 
- Language: h
- Symbols:
  - `cx_style` (struct, line 46)
  - `cx_item` (struct, line 69)
  - `FREEDOM_COMPOSITOR_H` (macro, line 2)

## include/css.h
- Layer: utility
- Doc: ifndef FREEDOM_CSS_H define FREEDOM_CSS_H  include <stddef.h> include "css_color.h"  ifdef __cplusplus error "Freedom is
- Language: h
- Symbols:
  - `css_style` (struct, line 563)
  - `css_media` (struct, line 919)
  - `css_drop` (struct, line 977)
  - `css_drop_log` (struct, line 989)
  - `css_attr` (struct, line 1018)
  - `css_element` (struct, line 1028)
  - `FREEDOM_CSS_H` (macro, line 2)
  - `CSS_GAP_MAX` (macro, line 75)
  - `CSS_GRID_COLS_MAX` (macro, line 76)
  - `CSS_GRID_TRACKS_MAX` (macro, line 77)
  - `CSS_GRID_AREAS_MAX` (macro, line 83)
  - `CSS_GRAD_STOPS_MAX` (macro, line 84)
  - `CSS_LINE_MIN` (macro, line 85)
  - `CSS_LINE_MAX` (macro, line 86)
  - `CSS_URL_MAX` (macro, line 87)
  - `CSS_DECO_UNDERLINE` (macro, line 92)
  - `CSS_DECO_LINE_THROUGH` (macro, line 93)
  - `CSS_DECO_OVERLINE` (macro, line 94)
  - `CSS_CONTAIN_SIZE` (macro, line 332)
  - `CSS_CONTAIN_LAYOUT` (macro, line 333)
  - `CSS_CONTAIN_STYLE` (macro, line 334)
  - `CSS_CONTAIN_PAINT` (macro, line 335)
  - `CSS_BORDER_W_MAX` (macro, line 422)
  - `CSS_BORDER_SPACING_MAX` (macro, line 423)
  - `CSS_FLEX_FACTOR_MAX` (macro, line 424)
  - `CSS_GRID_SPAN_MAX` (macro, line 425)
  - `CSS_SPACING_MAX` (macro, line 429)
  - `CSS_SHADOW_MAX` (macro, line 430)
  - `CSS_LEN_MAX` (macro, line 435)
  - `CSS_LEN_UNSET` (macro, line 436)
  - `CSS_LEN_AUTO` (macro, line 437)
  - `CSS_LEN_END` (macro, line 438)
  - `CSS_LEN_MIN_CONTENT` (macro, line 445)
  - `CSS_LEN_MAX_CONTENT` (macro, line 446)
  - `CSS_LEN_FIT_CONTENT` (macro, line 447)
  - `CSS_LEN_IS_INTRINSIC` (macro, line 450)
  - `CSS_PCT_MAX` (macro, line 473)
  - `CSS_EM_MILLI_MAX` (macro, line 479)
  - `CSS_FONT_SIZE_MAX` (macro, line 485)
  - `CSS_COLUMN_COUNT_MAX` (macro, line 489)
  - `CSS_MAX_COMPOUNDS` (macro, line 544)
  - `CSS_MAX_ATTR_SEL` (macro, line 548)
  - `CSS_MAX_PSEUDO_SEL` (macro, line 552)
  - `CSS_NTH_MAX` (macro, line 556)
  - `CSS_MAX_KF_STOPS` (macro, line 830)
  - `CSS_MEDIA_DEFAULT_WIDTH` (macro, line 924)
  - `CSS_MEDIA_DEFAULT_HEIGHT` (macro, line 930)
  - `CSS_DROP_PROP_MAX` (macro, line 968)
  - `CSS_DROP_VAL_MAX` (macro, line 970)

## include/css_chain.h
- Layer: utility
- Doc: ifndef FREEDOM_CSS_CHAIN_H define FREEDOM_CSS_CHAIN_H  include <lexbor/html/html.h>  include "css.h" include "css_select
- Language: h
- Symbols:
  - `FREEDOM_CSS_CHAIN_H` (macro, line 2)
  - `CCH_CHAIN_MAX` (macro, line 26)
  - `CCH_SIB_MAX` (macro, line 27)
  - `CCH_NTH_MAX` (macro, line 28)

## include/css_color.h
- Layer: utility
- Doc: ifndef FREEDOM_CSS_COLOR_H define FREEDOM_CSS_COLOR_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supp
- Language: h
- Symbols:
  - `cc_rgb` (struct, line 27)
  - `FREEDOM_CSS_COLOR_H` (macro, line 2)
  - `CC_COLOR_CURRENT` (macro, line 59)
  - `CC_COLOR_TRANSPARENT` (macro, line 60)

## include/css_length.h
- Layer: utility
- Doc: ifndef FREEDOM_CSS_LENGTH_H define FREEDOM_CSS_LENGTH_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C 
- Language: h
- Symbols:
  - `cl_ctx` (struct, line 84)
  - `cl_lp` (struct, line 132)
  - `FREEDOM_CSS_LENGTH_H` (macro, line 2)
  - `CL_MAX_TOKEN` (macro, line 33)
  - `CL_INITIAL_FONT_SIZE` (macro, line 39)
  - `CL_NORMAL_LINE_RATIO` (macro, line 45)
  - `CL_FALLBACK_EX_RATIO` (macro, line 56)
  - `CL_FALLBACK_CH_RATIO` (macro, line 57)
  - `CL_FALLBACK_CAP_RATIO` (macro, line 58)
  - `CL_FALLBACK_IC_RATIO` (macro, line 59)

## include/css_select.h
- Layer: utility
- Doc: ifndef FREEDOM_CSS_SELECT_H define FREEDOM_CSS_SELECT_H  include <stddef.h> include <string.h>  include "css.h"  ifdef _
- Language: h
- Symbols:
  - `css_attr_match` (struct, line 84)
  - `css_sub_sel` (struct, line 91)
  - `css_pseudo_match` (struct, line 105)
  - `css_compound` (struct, line 115)
  - `css_sel` (struct, line 132)
  - `csel_lower_ch` (function, line 158) `static inline char csel_lower_ch(char c)`
  - `csel_ci_eq` (function, line 162) `static inline int csel_ci_eq(const char *a, const char *b)`
  - `csel_span_eq` (function, line 172) `static inline int csel_span_eq(const char *a, const char *b, size_t n, int ci)`
  - `csel_substr` (function, line 183) `static inline int csel_substr(const char *hay, const char *needle, int ci)`
  - `csel_ident_ch` (function, line 190) `static inline int csel_ident_ch(char c)`
  - `FREEDOM_CSS_SELECT_H` (macro, line 2)
  - `CSS_TOK_MAX` (macro, line 27)
  - `CSS_MAX_CLASSES_PER_SEL` (macro, line 28)
  - `CSS_MAX_SUB_SELS` (macro, line 80)
  - `CSS_SUB_MAX_ATTRS` (macro, line 81)

## include/data_url.h
- Layer: data_access
- Doc: ifndef FREEDOM_DATA_URL_H define FREEDOM_DATA_URL_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error "Fre
- Language: h
- Symbols:
  - `FREEDOM_DATA_URL_H` (macro, line 2)
  - `DU_MAX_ENCODED_LEN` (macro, line 43)

## include/disk_store.h
- Layer: data_access
- Doc: ifndef FREEDOM_DISK_STORE_H define FREEDOM_DISK_STORE_H  include <stddef.h> include <stdint.h>  include "local_store.h" 
- Language: h
- Symbols:
  - `FREEDOM_DISK_STORE_H` (macro, line 2)

## include/dom.h
- Layer: utility
- Doc: ifndef FREEDOM_DOM_H define FREEDOM_DOM_H  include <stddef.h> include <stdint.h>  include "html_parse.h"  ifdef __cplusp
- Language: h
- Symbols:
  - `FREEDOM_DOM_H` (macro, line 2)
  - `DOM_NODE_NONE` (macro, line 37)

## include/dom_debug.h
- Layer: utility
- Doc: ifndef FREEDOM_DOM_DEBUG_H define FREEDOM_DOM_DEBUG_H  include <stddef.h>  include "render_doc.h"  ifdef __cplusplus err
- Language: h
- Symbols:
  - `FREEDOM_DOM_DEBUG_H` (macro, line 2)
  - `DD_FIELD_MAX` (macro, line 28)

## include/download.h
- Layer: utility
- Doc: ifndef FREEDOM_DOWNLOAD_H define FREEDOM_DOWNLOAD_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11
- Language: h
- Symbols:
  - `FREEDOM_DOWNLOAD_H` (macro, line 2)
  - `DL_NAME_MAX` (macro, line 28)
  - `DL_FALLBACK_NAME` (macro, line 30)
  - `DL_MAX_BYTES` (macro, line 31)

## include/flex_layout.h
- Layer: presentation
- Doc: ifndef FREEDOM_FLEX_LAYOUT_H define FREEDOM_FLEX_LAYOUT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure 
- Language: h
- Symbols:
  - `fx_item` (struct, line 40)
  - `fx_result` (struct, line 48)
  - `fx_area_map` (struct, line 116)
  - `fx_float_rect` (struct, line 170)
  - `FREEDOM_FLEX_LAYOUT_H` (macro, line 2)
  - `FX_MAX_ITEMS` (macro, line 28)
  - `FX_AREA_MAX_ROWS` (macro, line 108)
  - `FX_AREA_MAX_COLS` (macro, line 109)
  - `FX_AREA_MAX_CELLS` (macro, line 110)
  - `FX_AREA_NAME_MAX` (macro, line 111)
  - `FX_FLOAT_MIN_LINE` (macro, line 164)
  - `FX_MAX_COLUMNS` (macro, line 215)

## include/form.h
- Layer: data_access
- Doc: ifndef FREEDOM_FORM_H define FREEDOM_FORM_H  include <stddef.h>  include "url.h"  ifdef __cplusplus error "Freedom is pu
- Language: h
- Symbols:
  - `fm_field` (struct, line 37)
  - `fm_plan` (struct, line 52)
  - `FREEDOM_FORM_H` (macro, line 2)
  - `FM_URL_MAX` (macro, line 28)
  - `FM_BODY_MAX` (macro, line 30)
  - `FM_MAX_FIELDS` (macro, line 31)

## include/frame_clock.h
- Layer: utility
- Doc: ifndef FREEDOM_FRAME_CLOCK_H define FREEDOM_FRAME_CLOCK_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not 
- Language: h
- Symbols:
  - `fc_clock` (struct, line 15)
  - `FREEDOM_FRAME_CLOCK_H` (macro, line 2)

## include/freebug.h
- Layer: utility
- Doc: ifndef FREEDOM_FREEBUG_H define FREEDOM_FREEBUG_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11).
- Language: h
- Symbols:
  - `fb_entry` (struct, line 36)
  - `fb_buffer` (struct, line 46)
  - `FREEDOM_FREEBUG_H` (macro, line 2)
  - `FB_MAX_ENTRIES` (macro, line 56)
  - `FB_MAX_ENTRY_BYTES` (macro, line 57)
  - `FB_MAX_TOTAL_BYTES` (macro, line 58)
  - `FB_MAX_FILE_BYTES` (macro, line 62)

## include/freedom_config.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `FREEDOM_CONFIG_H` (macro, line 14)
  - `FC_PNG_PAGE_W` (macro, line 20)
  - `FC_PNG_MARGIN` (macro, line 24)
  - `FC_PNG_MAX_H` (macro, line 29)
  - `FC_FLEX_MEASURE_W` (macro, line 35)
  - `FC_FLEX_MIN_MEASURE_W` (macro, line 41)
  - `FC_FONT_CHAIN_MAX` (macro, line 46)
  - `FC_MAX_BOXES` (macro, line 51)

## include/hls.h
- Layer: utility
- Doc: ifndef FREEDOM_HLS_H define FREEDOM_HLS_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is 
- Language: h
- Symbols:
  - `hls_segment` (struct, line 29)
  - `hls_variant` (struct, line 36)
  - `hls_playlist` (struct, line 45)
  - `FREEDOM_HLS_H` (macro, line 2)

## include/hostblock.h
- Layer: utility
- Doc: ifndef FREEDOM_HOSTBLOCK_H define FREEDOM_HOSTBLOCK_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C
- Language: h
- Symbols:
  - `FREEDOM_HOSTBLOCK_H` (macro, line 2)

## include/hostedit.h
- Layer: infrastructure
- Doc: ifndef FREEDOM_HOSTEDIT_H define FREEDOM_HOSTEDIT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11
- Language: h
- Symbols:
  - `FREEDOM_HOSTEDIT_H` (macro, line 2)
  - `HE_MAX_HOST` (macro, line 32)

## include/html_parse.h
- Layer: utility
- Doc: ifndef FREEDOM_HTML_PARSE_H define FREEDOM_HTML_PARSE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error 
- Language: h
- Symbols:
  - `hp_config` (struct, line 32)
  - `hp_script` (struct, line 76)
  - `FREEDOM_HTML_PARSE_H` (macro, line 2)
  - `HP_DEFAULT_MAX_BYTES` (macro, line 40)
  - `HP_MAX_SCRIPTS` (macro, line 48)
  - `HP_MAX_STYLESHEETS` (macro, line 112)

## include/image_decode.h
- Layer: utility
- Doc: ifndef FREEDOM_IMAGE_DECODE_H define FREEDOM_IMAGE_DECODE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus er
- Language: h
- Symbols:
  - `img_pixels` (struct, line 56)
  - `FREEDOM_IMAGE_DECODE_H` (macro, line 2)
  - `IMG_MAX_DIM` (macro, line 65)
  - `IMG_MAX_PIXELS` (macro, line 66)

## include/interp.h
- Layer: utility
- Doc: ifndef FREEDOM_INTERP_H define FREEDOM_INTERP_H  include <stdint.h>  ifdef __cplusplus error "Freedom is pure C (C11). C
- Language: h
- Symbols:
  - `ip_ease_fn` (struct, line 38)
  - `ip_keyframe` (struct, line 70)
  - `ip_anim` (struct, line 101)
  - `FREEDOM_INTERP_H` (macro, line 2)
  - `IP_MAX_KEYFRAMES` (macro, line 67)
  - `IP_ITERATION_INFINITE` (macro, line 84)

## include/js_dom.h
- Layer: utility
- Doc: ifndef FREEDOM_JS_DOM_H define FREEDOM_JS_DOM_H  include "dom.h" include "freebug.h" include "js_sandbox.h" include "url
- Language: h
- Symbols:
  - `jd_iframe_track` (struct, line 40)
  - `jd_opaque` (struct, line 45)
  - `FREEDOM_JS_DOM_H` (macro, line 2)
  - `JD_IFRAME_TRACK_MAX` (macro, line 39)

## include/js_env.h
- Layer: infrastructure
- Doc: ifndef FREEDOM_JS_ENV_H define FREEDOM_JS_ENV_H  include "js_sandbox.h"  ifdef __cplusplus error "Freedom is pure C (C11
- Language: h
- Symbols:
  - `FREEDOM_JS_ENV_H` (macro, line 2)

## include/js_policy.h
- Layer: business_logic
- Doc: ifndef FREEDOM_JS_POLICY_H define FREEDOM_JS_POLICY_H  include <stdbool.h>  ifdef __cplusplus error "Freedom is pure C (
- Language: h
- Symbols:
  - `FREEDOM_JS_POLICY_H` (macro, line 2)

## include/js_sandbox.h
- Layer: utility
- Doc: ifndef FREEDOM_JS_SANDBOX_H define FREEDOM_JS_SANDBOX_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus error 
- Language: h
- Symbols:
  - `js_limits` (struct, line 39)
  - `js_result` (struct, line 49)
  - `FREEDOM_JS_SANDBOX_H` (macro, line 2)
  - `JS_LOC_FILE_MAX` (macro, line 64)
  - `JS_DEFAULT_MAX_SOURCE` (macro, line 65)
  - `JS_DEFAULT_MEM_LIMIT` (macro, line 67)
  - `JS_DEFAULT_STACK_LIMIT` (macro, line 68)
  - `JS_DEFAULT_TIME_BUDGET` (macro, line 69)

## include/link_nav.h
- Layer: utility
- Doc: ifndef FREEDOM_LINK_NAV_H define FREEDOM_LINK_NAV_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11
- Language: h
- Symbols:
  - `ln_result` (struct, line 62)
  - `FREEDOM_LINK_NAV_H` (macro, line 2)
  - `LN_MAX_TARGET` (macro, line 33)
  - `LN_MAX_FRAGMENT` (macro, line 38)

## include/local_store.h
- Layer: data_access
- Doc: ifndef FREEDOM_LOCAL_STORE_H define FREEDOM_LOCAL_STORE_H  include <stddef.h> include <stdint.h>  ifdef __cplusplus erro
- Language: h
- Symbols:
  - `FREEDOM_LOCAL_STORE_H` (macro, line 2)
  - `LS_KEY_LEN` (macro, line 25)
  - `LS_SALT_LEN` (macro, line 27)
  - `LS_NONCE_LEN` (macro, line 28)
  - `LS_TAG_LEN` (macro, line 29)
  - `LS_HEADER_LEN` (macro, line 30)
  - `LS_OVERHEAD` (macro, line 31)
  - `LS_MAX_PLAINTEXT` (macro, line 32)

## include/media_decoder.h
- Layer: infrastructure
- Doc: ifndef FREEDOM_MEDIA_DECODER_H define FREEDOM_MEDIA_DECODER_H  include <stddef.h> include <stdint.h> include <sys/types.
- Language: h
- Symbols:
  - `md_pacer` (struct, line 67)
  - `md_pace_due_ms` (function, line 79) `static inline uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms,
                             ...`
  - `FREEDOM_MEDIA_DECODER_H` (macro, line 2)
  - `MD_MAX_SEGMENT_BYTES` (macro, line 45)
  - `MD_PACE_MAX_LAG_MS` (macro, line 58)
  - `MD_PACE_MAX_STEP_MS` (macro, line 62)
  - `MD_MAX_CATCHUP_READS` (macro, line 65)

## include/net_realm.h
- Layer: utility
- Doc: ifndef FREEDOM_NET_REALM_H define FREEDOM_NET_REALM_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supp
- Language: h
- Symbols:
  - `nr_config` (struct, line 42)
  - `FREEDOM_NET_REALM_H` (macro, line 2)

## include/os_sandbox.h
- Layer: utility
- Doc: ifndef FREEDOM_OS_SANDBOX_H define FREEDOM_OS_SANDBOX_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C 
- Language: h
- Symbols:
  - `os_fs_rule` (struct, line 108)
  - `FREEDOM_OS_SANDBOX_H` (macro, line 2)

## include/page_view.h
- Layer: presentation
- Doc: ifndef FREEDOM_PAGE_VIEW_H define FREEDOM_PAGE_VIEW_H  include <stddef.h> include <stdint.h>  include "dom.h" include "h
- Language: h
- Symbols:
  - `pv_run` (struct, line 108)
  - `pv_box_def` (struct, line 365)
  - `pv_cont_def` (struct, line 650)
  - `pv_view` (struct, line 686)
  - `pv_text_ext` (struct, line 847)
  - `FREEDOM_PAGE_VIEW_H` (macro, line 2)
  - `PV_LEN_UNSET` (macro, line 43)
  - `PV_LEN_AUTO` (macro, line 44)
  - `PV_LEN_END` (macro, line 45)
  - `PV_GRID_TRACKS` (macro, line 48)
  - `PV_CONT_DEPTH` (macro, line 53)
  - `PV_BG_URL_MAX` (macro, line 59)

## include/pdf_export.h
- Layer: utility
- Doc: ifndef FREEDOM_PDF_EXPORT_H define FREEDOM_PDF_EXPORT_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C 
- Language: h
- Symbols:
  - `FREEDOM_PDF_EXPORT_H` (macro, line 2)
  - `PE_NAME_MAX` (macro, line 27)
  - `PE_EXT` (macro, line 29)
  - `PE_EXT_PNG` (macro, line 30)
  - `PE_FALLBACK_NAME` (macro, line 31)

## include/perf_trace.h
- Layer: utility
- Doc: ifndef FREEDOM_PERF_TRACE_H define FREEDOM_PERF_TRACE_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not su
- Language: h
- Symbols:
  - `pt_stage_stats` (struct, line 34)
  - `pt_trace` (struct, line 41)
  - `FREEDOM_PERF_TRACE_H` (macro, line 2)
  - `PT_MAX_SAMPLES` (macro, line 31)

## include/prefetch.h
- Layer: utility
- Doc: ifndef FREEDOM_PREFETCH_H define FREEDOM_PREFETCH_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not suppor
- Language: h
- Symbols:
  - `pf_ref` (struct, line 42)
  - `pf_list` (struct, line 50)
  - `pf_job` (struct, line 77)
  - `pf_pool` (struct, line 87)
  - `pf_gated_fetch` (struct, line 129)
  - `FREEDOM_PREFETCH_H` (macro, line 2)
  - `PF_MAX_REFS` (macro, line 46)
  - `PF_MAX_THREADS` (macro, line 48)

## include/prefs.h
- Layer: utility
- Doc: ifndef FREEDOM_PREFS_H define FREEDOM_PREFS_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++
- Language: h
- Symbols:
  - `prefs_entry` (struct, line 45)
  - `prefs_state` (struct, line 50)
  - `FREEDOM_PREFS_H` (macro, line 2)
  - `PREFS_VERSION` (macro, line 25)
  - `PREFS_MAX_URL` (macro, line 27)
  - `PREFS_MAX_TITLE` (macro, line 28)
  - `PREFS_MAX_BOOKMARKS` (macro, line 29)
  - `PREFS_MAX_HISTORY` (macro, line 30)
  - `PREFS_MAX_TEXT` (macro, line 31)
  - `PREFS_PAGE_HISTORY` (macro, line 34)

## include/profile.h
- Layer: utility
- Doc: ifndef FREEDOM_PROFILE_H define FREEDOM_PROFILE_H  include <stddef.h> include <stdint.h>  include "local_store.h" includ
- Language: h
- Symbols:
  - `profile_ctx` (struct, line 46)
  - `FREEDOM_PROFILE_H` (macro, line 2)
  - `PROFILE_KEY_FILE` (macro, line 31)
  - `PROFILE_PREFS_FILE` (macro, line 33)

## include/psl_data.h
- Layer: data_access
- Doc: ifndef FREEDOM_PSL_DATA_H define FREEDOM_PSL_DATA_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11
- Language: h
- Symbols:
  - `FREEDOM_PSL_DATA_H` (macro, line 2)

## include/render_doc.h
- Layer: presentation
- Doc: ifndef FREEDOM_RENDER_DOC_H define FREEDOM_RENDER_DOC_H  include <stddef.h>  include "page_view.h" include "render_polic
- Language: h
- Symbols:
  - `rd_block` (struct, line 64)
  - `rd_doc` (struct, line 231)
  - `FREEDOM_RENDER_DOC_H` (macro, line 2)

## include/render_policy.h
- Layer: presentation
- Doc: ifndef FREEDOM_RENDER_POLICY_H define FREEDOM_RENDER_POLICY_H  include <stdbool.h>  ifdef __cplusplus error "Freedom is 
- Language: h
- Symbols:
  - `rdp_caps` (struct, line 32)
  - `FREEDOM_RENDER_POLICY_H` (macro, line 2)
  - `RDP_TRACKER_MAX_DIM` (macro, line 27)

## include/renderer.h
- Layer: presentation
- Doc: ifndef FREEDOM_RENDERER_H define FREEDOM_RENDERER_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11
- Language: h
- Symbols:
  - `rd_result` (struct, line 29)
  - `FREEDOM_RENDERER_H` (macro, line 2)
  - `RD_MAX_INPUT` (macro, line 36)
  - `RD_MAX_FIELD` (macro, line 38)

## include/request_policy.h
- Layer: business_logic
- Doc: ifndef FREEDOM_REQUEST_POLICY_H define FREEDOM_REQUEST_POLICY_H  include <stddef.h>  ifdef __cplusplus error "Freedom is
- Language: h
- Symbols:
  - `FREEDOM_REQUEST_POLICY_H` (macro, line 2)

## include/secure_fetch.h
- Layer: utility
- Doc: ifndef FREEDOM_SECURE_FETCH_H define FREEDOM_SECURE_FETCH_H  include <stddef.h> include <stdint.h>  include "anti_fp.h" 
- Language: h
- Symbols:
  - `sf_chain_info` (struct, line 60)
  - `sf_config` (struct, line 75)
  - `sf_response` (struct, line 117)
  - `FREEDOM_SECURE_FETCH_H` (macro, line 2)
  - `SF_DEFAULT_KEX_GROUPS` (macro, line 143)
  - `SF_IMPERSONATE_KEX_GROUPS` (macro, line 152)
  - `SF_IMPERSONATE_TLS13_CIPHERS` (macro, line 153)
  - `SF_IMPERSONATE_TLS12_CIPHERS` (macro, line 157)
  - `SF_DEFAULT_USER_AGENT` (macro, line 168)
  - `SF_DEFAULT_MAX_BODY` (macro, line 169)
  - `SF_DEFAULT_TIMEOUT_MS` (macro, line 170)
  - `SF_CONNECT_TIMEOUT_MS` (macro, line 193)
  - `SF_SUBRESOURCE_TIMEOUT_MS` (macro, line 194)
  - `SF_DEFAULT_MAX_REDIRECTS` (macro, line 195)
  - `SF_MAX_URL` (macro, line 196)

## include/svg_paint.h
- Layer: utility
- Doc: ifndef FREEDOM_SVG_PAINT_H define FREEDOM_SVG_PAINT_H  include <cairo.h>  include "svg_render.h"  ifdef __cplusplus erro
- Language: h
- Symbols:
  - `FREEDOM_SVG_PAINT_H` (macro, line 2)

## include/svg_render.h
- Layer: presentation
- Doc: ifndef FREEDOM_SVG_RENDER_H define FREEDOM_SVG_RENDER_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C 
- Language: h
- Symbols:
  - `sv_seg` (struct, line 65)
  - `sv_shape` (struct, line 75)
  - `sv_image` (struct, line 104)
  - `FREEDOM_SVG_RENDER_H` (macro, line 2)
  - `SV_MAX_SHAPES` (macro, line 31)
  - `SV_MAX_POINTS` (macro, line 33)
  - `SV_MAX_SEGS` (macro, line 34)
  - `SV_MAX_DEPTH` (macro, line 35)
  - `SV_TEXT_MAX` (macro, line 36)
  - `SV_MAX_INPUT` (macro, line 37)
  - `SV_DEFAULT_W` (macro, line 41)
  - `SV_DEFAULT_H` (macro, line 42)

## include/tab.h
- Layer: utility
- Doc: ifndef FREEDOM_TAB_H define FREEDOM_TAB_H  include <stddef.h> include <stdint.h> include <sys/types.h>  include "freebug
- Language: h
- Symbols:
  - `tab_page` (struct, line 49)
  - `tab_eval_result` (struct, line 80)
  - `tab_image` (struct, line 93)
  - `FREEDOM_TAB_H` (macro, line 2)
  - `TAB_MAX_INPUT` (macro, line 100)

## include/text_shape.h
- Layer: utility
- Language: h
- Symbols:
  - `tsh_font` (struct, line 30)
  - `FREEDOM_TEXT_SHAPE_H` (macro, line 19)
  - `TSH_MAX_GLYPHS` (macro, line 35)
  - `TSH_MAX_TEXT` (macro, line 37)

## include/textfield.h
- Layer: utility
- Doc: ifndef FREEDOM_TEXTFIELD_H define FREEDOM_TEXTFIELD_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C
- Language: h
- Symbols:
  - `tf_field` (struct, line 25)
  - `FREEDOM_TEXTFIELD_H` (macro, line 2)
  - `TF_CAP` (macro, line 22)

## include/tls_impersonate.h
- Layer: utility
- Doc: ifndef FREEDOM_TLS_IMPERSONATE_H define FREEDOM_TLS_IMPERSONATE_H  include <stddef.h> include <stdint.h>  ifdef __cplusp
- Language: h
- Symbols:
  - `ti_req` (struct, line 68)
  - `ti_resp` (struct, line 78)
  - `FREEDOM_TLS_IMPERSONATE_H` (macro, line 2)
  - `TI_MAGIC` (macro, line 56)
  - `TI_MAX_URL` (macro, line 57)
  - `TI_MAX_METHOD` (macro, line 58)
  - `TI_MAX_HEADERS` (macro, line 59)
  - `TI_MAX_BODY` (macro, line 60)
  - `TI_MAX_RESP_HDR` (macro, line 61)
  - `TI_MAX_RESP_BODY` (macro, line 62)
  - `TI_MAX_CHAIN` (macro, line 63)
  - `TI_MAX_GROUP` (macro, line 64)

## include/ui.h
- Layer: presentation
- Doc: ifndef FREEDOM_UI_H define FREEDOM_UI_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is no
- Language: h
- Symbols:
  - `ui_line` (struct, line 29)
  - `ui_layout` (struct, line 34)
  - `rd_doc` (struct, line 68)
  - `tab` (struct, line 94)
  - `FREEDOM_UI_H` (macro, line 2)

## include/url.h
- Layer: utility
- Doc: ifndef FREEDOM_URL_H define FREEDOM_URL_H  include <stddef.h>  ifdef __cplusplus error "Freedom is pure C (C11). C++ is 
- Language: h
- Symbols:
  - `url_parts` (struct, line 129)
  - `FREEDOM_URL_H` (macro, line 2)
  - `URL_MAX_LEN` (macro, line 30)
  - `URL_SEARCH_ENDPOINT` (macro, line 76)

## include/util.h
- Layer: utility
- Doc: util.h — shared pure helpers (no I/O except where noted). Static inline so each compilation unit gets its own copy witho
- Language: h
- Symbols:
  - `write_full` (function, line 14) `static inline int write_full(int fd, const void *buf, size_t n)`
  - `read_full` (function, line 25) `static inline int read_full(int fd, void *buf, size_t n)`
  - `mem_contains_ci` (function, line 43) `static inline int mem_contains_ci(const void *hay, size_t hlen, const char *needle)`
  - `utf8_seq_len` (function, line 56) `static inline size_t utf8_seq_len(unsigned char c)`
  - `fnv1a` (function, line 66) `static inline uint64_t fnv1a(const char *s, size_t n)`
  - `UTIL_H` (macro, line 5)

## include/webcaps.h
- Layer: utility
- Doc: ifndef FREEDOM_WEBCAPS_H define FREEDOM_WEBCAPS_H  include <stdbool.h>  include "js_policy.h" include "render_policy.h" 
- Language: h
- Symbols:
  - `wc_caps` (struct, line 38)
  - `wc_input` (struct, line 57)
  - `FREEDOM_WEBCAPS_H` (macro, line 2)

## include/zoom.h
- Layer: utility
- Doc: ifndef FREEDOM_ZOOM_H define FREEDOM_ZOOM_H  ifdef __cplusplus error "Freedom is pure C (C11). C++ is not supported." en
- Language: h
- Symbols:
  - `FREEDOM_ZOOM_H` (macro, line 2)
  - `ZM_MIN_PCT` (macro, line 20)
  - `ZM_MAX_PCT` (macro, line 22)
  - `ZM_DEFAULT_PCT` (macro, line 23)
