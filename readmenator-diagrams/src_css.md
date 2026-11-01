# src: css

src: css groups 38 files (c, h) around FREEDOM_CSS_COLOR_H, b, cc_rgb, cc_status, cc_pack. car_ops: The questions @supports asks the caller's own engine. prop is lowercased and...

```mermaid
graph LR
    include["include"]
    src["src"]
    tests["tests"]
    include -- "calls into" --> src
    src -- "calls into" --> include
    src -- "calls into" --> tests
    tests -- "calls into" --> include
    tests -- "calls into" --> src
```

## include (4.1)

include groups 13 files (h) around FREEDOM_CSS_COLOR_H, b, cc_rgb, cc_status, cc_pack. car_ops: The questions @supports asks the caller's own engine. prop is lowercased and...

## src (4.2)

src groups 14 files (c) around CSS_INIT_SELS, CSS_INIT_DECLS, emit, CSS_DECL_SLOTS_MIN, CSS_INIT_RULES. len_rebase_ctx: int r = snprintf(out + *o, space, "%.4f", px); if (r < 0 || (size_t)r...

## tests (4.3)

tests groups 11 files (c) around toy_decl, toy_sel, sup, test_declaration_tests, test_boolean_combinators. test_css_atrule -- @supports evaluation and @layer ranks (spec/css_atrule.md).

**Files**:

- include/css_atrule.h
- include/css_box.h
- include/css_color.h
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
- src/css.c
- src/css_atrule.c
- src/css_box.c
- src/css_chain.c
- src/css_color.c
- src/css_gradient.c
- src/css_index.c
- src/css_length.c
- src/css_mask.c
- src/css_mq.c
- src/css_select.c
- src/css_text.c
- src/css_values.c
- src/css_vars.c
- tests/test_css_atrule.c
- tests/test_css_box.c
- tests/test_css_color.c
- tests/test_css_gradient.c
- tests/test_css_index.c
- tests/test_css_length.c
- tests/test_css_mask.c
- tests/test_css_mq.c
- tests/test_css_text.c
- tests/test_css_values.c
- tests/test_css_vars.c
