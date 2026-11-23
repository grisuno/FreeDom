# include: page_view

include: page_view groups 30 files (c, h) around FREEDOM_PAGE_VIEW_H, pv_status, PV_BSHADOW_LAYERS, PV_MAUTO_LEFT, PV_MAUTO_RIGHT. Hostile box trees (any parent graph, cycles included) through the positioned paint

```mermaid
graph LR
    fuzz["fuzz"]
    include["include"]
    src["src"]
    tests["tests"]
    fuzz -- "calls into" --> include
    fuzz -- "calls into" --> src
    include -- "calls into" --> src
    include -- "calls into" --> tests
    src -- "depends on" --> include
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## fuzz (5.1)

fuzz groups 3 files (c) around FB_MAX, pass. Hostile box trees (any parent graph, cycles included) through the positioned paint

## include (5.2)

include groups 10 files (h) around FREEDOM_PAGE_VIEW_H, pv_status, PV_BSHADOW_LAYERS, PV_MAUTO_LEFT, PV_MAUTO_RIGHT. bx_edges: anything longer fails closed instead of truncating into a wrong match....

## src (5.3)

src groups 8 files (c) around BX_TAG_MAX, BX_DISPLAY_MAX, is_ws, copy_lower_trim, name_cmp. tag_row: One row of the user-agent sheet.

## tests (5.4)

tests groups 9 files (c) around dbl_eq, assert_edges, test_body_has_no_margin, test_paragraph, test_heading_ladder. dbl_eq: #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include...

**Files**:

- fuzz/fuzz_box_tree.c
- fuzz/fuzz_dom_debug.c
- fuzz/fuzz_page_view.c
- include/box_style.h
- include/box_tree.h
- include/dom_debug.h
- include/flex_layout.h
- include/freedom_config.h
- include/page_view.h
- include/render_doc.h
- include/render_policy.h
- include/sheet_cache.h
- include/video_pick.h
- src/box_style.c
- src/box_tree.c
- src/dom_debug.c
- src/flex_layout.c
- src/page_view.c
- src/render_doc.c
- src/sheet_cache.c
- src/video_pick.c
- tests/test_box_style.c
- tests/test_box_tree.c
- tests/test_dom_debug.c
- tests/test_flex_layout.c
- tests/test_page_view.c
- tests/test_render_doc.c
- tests/test_render_policy.c
- tests/test_sheet_cache.c
- tests/test_video_pick.c
