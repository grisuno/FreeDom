# src: css

src: css groups 57 files (c, h) around FREEDOM_CSS_H, css_status, css_align, css_display, css_justify. ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb...

```mermaid
graph LR
    gui["gui"]
    include["include"]
    src["src"]
    tests["tests"]
    gui -- "depends on" --> include
    gui -- "calls into" --> src
    include -- "calls into" --> src
    src -- "calls into" --> include
    src -- "calls into" --> tests
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## gui (1.1)

gui groups 3 files (c, h) around FREEDOM_BROWSER_UI_INTERNAL_H, UI_FONT_SIZE, UI_TEXT_MARGIN, UI_HEADING_LEVELS, b. ui_theme_mode: ui_rgb button_text; ui_rgb menu_bg; ui_rgb menu_border; ui_rgb...

## include (1.2)

include groups 18 files (h) around FREEDOM_CSS_H, css_status, css_align, css_display, css_justify. cx_style: A box's resolved style, in the SAME value-spaces as css.h: position uses...

## src (1.3)

src groups 19 files (c) around cx_forms_stacking_context, cx_box_layer, eff_z, cx_item_compare, cx_sort. eff_z: Not a stacking context: a positioned box with z:auto still paints in the *...

## tests (1.4)

tests groups 17 files (c) around test_sc_opacity, test_sc_mix_blend, test_sc_isolation, test_sc_transform, test_sc_positioned_z. test_sort_matches_zindex_only_ordering: The positioned subset the painter already...

**Files**:

- gui/browser_ui_internal.h
- gui/bui_mask_img.c
- gui/bui_theme.c
- include/compositor.h
- include/css.h
- include/css_atrule.h
- include/css_box.h
- include/css_color.h
- include/css_computed.h
- include/css_counter.h
- include/css_decl.h
- include/css_gradient.h
- include/css_index.h
- include/css_length.h
- include/css_mask.h
- include/css_mq.h
- include/css_select.h
- include/css_text.h
- include/css_values.h
- include/css_vars.h
- include/text_case.h
- src/compositor.c
- src/css.c
- src/css_atrule.c
- src/css_box.c
- src/css_chain.c
- src/css_color.c
- src/css_computed.c
- src/css_counter.c
- src/css_gradient.c
- src/css_index.c
- src/css_length.c
- src/css_mask.c
- src/css_mq.c
- src/css_select.c
- src/css_text.c
- src/css_values.c
- src/css_vars.c
- src/js_native.c
- src/text_case.c
- tests/test_compositor.c
- tests/test_css.c
- tests/test_css_atrule.c
- tests/test_css_box.c
- tests/test_css_color.c
- tests/test_css_computed.c
- tests/test_css_counter.c
- tests/test_css_drops.c
- tests/test_css_gradient.c
- tests/test_css_index.c
- tests/test_css_length.c
- tests/test_css_mask.c
- tests/test_css_mq.c
- tests/test_css_text.c
- tests/test_css_values.c
- tests/test_css_vars.c
- tests/test_text_case.c
