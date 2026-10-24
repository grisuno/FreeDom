# src: tab

src: tab groups 45 files (c, h) around FREEDOM_HTML_PARSE_H, hp_status, max_bytes, hp_config, hp_document. dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all...

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

## include (3.1)

include groups 13 files (h) around FREEDOM_HTML_PARSE_H, hp_status, max_bytes, hp_config, hp_document. dom_place: Where dom_move_children places the moved nodes (insertAdjacent* needs all...

## src (3.2)

src groups 21 files (c, h) around FREEDOM_JS_CUSTOM_ELEMENTS_H, jdce_install, FREEDOM_JS_DOM_INTERNAL_H, jd_opaque_get, jd_idx. node_next: }; /* --- helpers --- static char *dup_bytes(const lxb_char_t *src, size_t...

## tests (3.3)

tests groups 11 files (c) around setup_doc, teardown_doc, DOC, IDX, test_build_null_args. setup_doc: #include "dom.h" #include "html_parse.h" static const char HTML[] =...

**Files**:

- include/dom.h
- include/freebug.h
- include/html_parse.h
- include/js_dom.h
- include/js_env.h
- include/js_geom.h
- include/js_location.h
- include/js_sandbox.h
- include/js_trusted.h
- include/link_nav.h
- include/tab.h
- include/url.h
- include/web_storage.h
- src/freebug.c
- src/html_parse.c
- src/js_custom_elements.c
- src/js_custom_elements.h
- src/js_dom.c
- src/js_dom_ext.c
- src/js_dom_ext.h
- src/js_dom_internal.h
- src/js_embed.c
- src/js_env.c
- src/js_events.c
- src/js_fetch.c
- src/js_geom.c
- src/js_location.c
- src/js_location_internal.h
- src/js_sandbox.c
- src/js_trusted.c
- src/link_nav.c
- src/tab.c
- src/url.c
- src/web_storage.c
- tests/test_dom.c
- tests/test_freebug.c
- tests/test_html_parse.c
- tests/test_js_dom.c
- tests/test_js_env.c
- tests/test_js_geom.c
- tests/test_js_sandbox.c
- tests/test_link_nav.c
- tests/test_tab.c
- tests/test_url.c
- tests/test_web_storage.c
