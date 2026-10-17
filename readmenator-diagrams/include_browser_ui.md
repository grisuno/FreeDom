# include: browser_ui

include: browser_ui groups 46 files (c, h) around FREEDOM_IMAGE_DECODE_H, guards, img_format, img_status, img_pixels. poke_and_free: Touch every claimed pixel corner so the sanitizer flags an...

```mermaid
graph LR
    fuzz["fuzz"]
    gui["gui"]
    include["include"]
    src["src"]
    tests["tests"]
    fuzz -- "calls into" --> include
    fuzz -- "calls into" --> src
    gui -- "calls into" --> include
    gui -- "calls into" --> src
    include -- "calls into" --> gui
    include -- "calls into" --> src
    src -- "calls into" --> gui
    src -- "depends on" --> include
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## fuzz (3.1)

fuzz groups 2 files (c) around poke_and_free, LLVMFuzzerTestOneInput. poke_and_free: Touch every claimed pixel corner so the sanitizer flags an...

## gui (3.2)

gui groups 1 files (c) around _GNU_SOURCE, UI_TOOLBAR_H, UI_TITLEBAR_H, UI_TABBAR_H, UI_TAB_MIN_W. ui_input_state: Live editable state for one form text control, aliasing a block of the...

## include (3.3)

include groups 14 files (h) around FREEDOM_IMAGE_DECODE_H, guards, img_format, img_status, img_pixels. block_flow (bf_) -- vertical margin collapsing for block-level boxes.

## src (3.4)

src groups 14 files (c) around finite_or_zero, bf_collapse_n, bf_collapse, bf_margins_adjoin, bb_box_sizes. block_flow (bf_) -- vertical margin collapsing.

## tests (3.5)

tests groups 15 files (c) around dbl_eq, test_two_positive_collapse_to_max, test_two_negative_take_the_most_negative, test_non_finite_is_absent, test_collapse_n_matches_binary. test_two_positive_collapse_to_max: Two positive margins collapse to the LARGER, never...

**Files**:

- fuzz/fuzz_image_decode.c
- fuzz/fuzz_tls_impersonate.c
- gui/browser_ui.c
- include/block_flow.h
- include/box_blur.h
- include/browser.h
- include/form.h
- include/frame_clock.h
- include/hls.h
- include/hostblock.h
- include/hostedit.h
- include/image_decode.h
- include/interp.h
- include/media_decoder.h
- include/net_realm.h
- include/textfield.h
- include/tls_impersonate.h
- src/block_flow.c
- src/box_blur.c
- src/browser.c
- src/form.c
- src/frame_clock.c
- src/hls.c
- src/hostblock.c
- src/hostedit.c
- src/image_decode.c
- src/interp.c
- src/media_decoder.c
- src/net_realm.c
- src/textfield.c
- src/tls_impersonate.c
- tests/test_block_flow.c
- tests/test_box_blur.c
- tests/test_browser.c
- tests/test_form.c
- tests/test_frame_clock.c
- tests/test_freedom.c
- tests/test_hls.c
- tests/test_hostblock.c
- tests/test_hostedit.c
- tests/test_image_decode.c
- tests/test_interp.c
- tests/test_media_decoder.c
- tests/test_net_realm.c
- tests/test_textfield.c
- tests/test_tls_impersonate.c
