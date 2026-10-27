# include: page_view

include: page_view groups 19 files (c, h) around FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_caps, rdp_img_decision. bx_edges: anything longer fails closed instead of truncating into a wrong match....

```mermaid
graph LR
    include["include"]
    src["src"]
    tests["tests"]
    include -- "calls into" --> src
    include -- "calls into" --> tests
    src -- "depends on" --> include
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## include (6.1)

include groups 7 files (h) around FREEDOM_RENDER_POLICY_H, RDP_TRACKER_MAX_DIM, images, rdp_caps, rdp_img_decision. bx_edges: anything longer fails closed instead of truncating into a wrong match....

## src (6.2)

src groups 5 files (c) around BX_TAG_MAX, BX_DISPLAY_MAX, is_ws, copy_lower_trim, name_cmp. tag_row: One row of the user-agent sheet.

## tests (6.3)

tests groups 7 files (c) around dbl_eq, assert_edges, test_body_has_no_margin, test_paragraph, test_heading_ladder. dbl_eq: #include <setjmp.h> #include <stdarg.h> #include <stddef.h> #include...

**Files**:

- include/box_style.h
- include/box_tree.h
- include/dom_debug.h
- include/flex_layout.h
- include/page_view.h
- include/render_doc.h
- include/render_policy.h
- src/box_style.c
- src/dom_debug.c
- src/flex_layout.c
- src/page_view.c
- src/render_doc.c
- tests/test_box_style.c
- tests/test_box_tree.c
- tests/test_dom_debug.c
- tests/test_flex_layout.c
- tests/test_page_view.c
- tests/test_render_doc.c
- tests/test_render_policy.c
