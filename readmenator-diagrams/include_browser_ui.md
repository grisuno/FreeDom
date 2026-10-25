# include: browser_ui

include: browser_ui groups 59 files (c, h) around FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL, PREFS_MAX_TITLE, PREFS_MAX_BOOKMARKS. ui_input_state: Live editable state for one form text control, aliasing a block of the...

```mermaid
graph LR
    gui["gui"]
    include["include"]
    src["src"]
    tests["tests"]
    gui -- "calls into" --> include
    gui -- "calls into" --> src
    include -- "calls into" --> gui
    include -- "calls into" --> src
    src -- "calls into" --> gui
    src -- "calls into" --> include
    tests -- "calls into" --> gui
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## gui (1.1)

gui groups 6 files (c, h) around FREEDOM_BROWSER_UI_INTERNAL_H, UI_FONT_SIZE, UI_TEXT_MARGIN, UI_HEADING_LEVELS, b. ui_input_state: Live editable state for one form text control, aliasing a block of the...

## include (1.2)

include groups 20 files (h) around FREEDOM_PREFS_H, PREFS_VERSION, PREFS_MAX_URL, PREFS_MAX_TITLE, PREFS_MAX_BOOKMARKS. block_flow (bf_) -- vertical margin collapsing for block-level boxes.

## src (1.3)

src groups 15 files (c) around finite_or_zero, bf_collapse_n, bf_collapse, bf_margins_adjoin, bb_box_sizes. block_flow (bf_) -- vertical margin collapsing.

## tests (1.4)

tests groups 18 files (c) around dbl_eq, test_two_positive_collapse_to_max, test_two_negative_take_the_most_negative, test_non_finite_is_absent, test_collapse_n_matches_binary. test_two_positive_collapse_to_max: Two positive margins collapse to the LARGER, never...

**Files**:

- gui/browser_ui.c
- gui/browser_ui_internal.h
- gui/bui_theme.c
- gui/freedom_view.c
- gui/svg_paint.c
- gui/ui_render.c
- include/block_flow.h
- include/box_blur.h
- include/download.h
- include/form.h
- include/frame_clock.h
- include/freedom_config.h
- include/hostedit.h
- include/image_decode.h
- include/interp.h
- include/lazy_load.h
- include/pdf_export.h
- include/prefs.h
- include/profile.h
- include/shm_slots.h
- include/svg_paint.h
- include/svg_render.h
- include/textfield.h
- include/ui.h
- include/wl_guard.h
- include/zoom.h
- src/block_flow.c
- src/box_blur.c
- src/download.c
- src/form.c
- src/frame_clock.c
- src/hostedit.c
- src/image_decode.c
- src/interp.c
- src/pdf_export.c
- src/prefs.c
- src/svg_render.c
- src/textfield.c
- src/ui_layout.c
- src/wl_guard.c
- src/zoom.c
- tests/test_block_flow.c
- tests/test_box_blur.c
- tests/test_download.c
- tests/test_form.c
- tests/test_frame_clock.c
- tests/test_freedom.c
- tests/test_hostedit.c
- tests/test_image_decode.c
- tests/test_interp.c
- tests/test_pdf_export.c
- tests/test_prefs.c
- tests/test_profile.c
- tests/test_shm_slots.c
- tests/test_svg_render.c
- tests/test_textfield.c
- tests/test_ui.c
- tests/test_wl_guard.c
- tests/test_zoom.c
