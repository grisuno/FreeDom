# include: page_view

include: page_view groups 43 files (c, h) around FREEDOM_CSS_H, css_status, css_align, css_display, css_justify. ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb...

```mermaid
graph LR
    gui["gui"]
    include["include"]
    src["src"]
    tests["tests"]
    gui -- "depends on" --> include
    include -- "calls into" --> src
    include -- "calls into" --> tests
    src -- "calls into" --> include
    src -- "calls into" --> tests
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## gui (3.1)

gui groups 3 files (c, h) around FREEDOM_BROWSER_UI_INTERNAL_H, UI_FONT_SIZE, UI_TEXT_MARGIN, UI_HEADING_LEVELS, b. ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb...

## include (3.2)

include groups 15 files (h) around FREEDOM_CSS_H, css_status, css_align, css_display, css_justify. bx_edges: anything longer fails closed instead of truncating into a wrong match....

## src (3.3)

src groups 11 files (c) around BX_TAG_MAX, BX_DISPLAY_MAX, is_ws, copy_lower_trim, name_cmp. tag_row: One row of the user-agent sheet.

## tests (3.4)

tests groups 14 files (c) around dbl_eq, assert_edges, test_body_has_no_margin, test_paragraph, test_heading_ladder. dbl_eq: #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include...

**Files**:

- gui/browser_ui_internal.h
- gui/bui_mask_img.c
- gui/bui_theme.c
- include/box_style.h
- include/box_tree.h
- include/compositor.h
- include/css.h
- include/css_chain.h
- include/css_computed.h
- include/css_counter.h
- include/dom_debug.h
- include/flex_layout.h
- include/freedom_config.h
- include/page_view.h
- include/render_doc.h
- include/render_policy.h
- include/sheet_cache.h
- include/text_case.h
- src/box_style.c
- src/box_tree.c
- src/compositor.c
- src/css_computed.c
- src/css_counter.c
- src/dom_debug.c
- src/flex_layout.c
- src/page_view.c
- src/render_doc.c
- src/sheet_cache.c
- src/text_case.c
- tests/test_box_style.c
- tests/test_box_tree.c
- tests/test_compositor.c
- tests/test_css.c
- tests/test_css_computed.c
- tests/test_css_counter.c
- tests/test_css_drops.c
- tests/test_dom_debug.c
- tests/test_flex_layout.c
- tests/test_page_view.c
- tests/test_render_doc.c
- tests/test_render_policy.c
- tests/test_sheet_cache.c
- tests/test_text_case.c
