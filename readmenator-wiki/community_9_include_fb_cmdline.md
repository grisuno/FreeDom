# include: fb_cmdline

*Community 9 | 11 files | cohesion 0.44*

## Definition

This community groups 11 file(s) rooted at `include` with dominant language c (cohesion 0.44). Central symbols: `FBC_BASE_MAX`, `FBC_ENTRY_MAX`, `FBC_HIST_MAX`, `FBC_LIST_NAMES`, `FBP_EXPR_MAX`, `FBP_SELECTOR_MAX`, `FB_MAX_ENTRIES`, `FB_MAX_ENTRY_BYTES`. Core file: `include/fb_cmdline.h` (18 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fuzz/fuzz_fb_cmdline.c` | c | utility | 1 | no |
| `fuzz/fuzz_freebug.c` | c | utility | 1 | no |
| `include/fb_cmdline.h` | h | utility | 18 | no |
| `include/fb_panes.h` | h | utility | 12 | no |
| `include/freebug.h` | h | utility | 18 | no |
| `src/fb_cmdline.c` | c | utility | 13 | no |
| `src/fb_panes.c` | c | utility | 10 | no |
| `src/freebug.c` | c | utility | 9 | no |
| `tests/test_fb_cmdline.c` | c | testing | 7 | no |
| `tests/test_fb_panes.c` | c | testing | 11 | no |
| `tests/test_freebug.c` | c | testing | 13 | no |

## Key Symbols

- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_fb_cmdline.c:5`) `int LLVMFuzzerTestOneInput(const uint8_t *d, size_t n)` - include <stdint.h> include <stdlib.h> include <string.h> include "fb_cmdline.h"
- `LLVMFuzzerTestOneInput` (function, `fuzz/fuzz_freebug.c:37`) `int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)`
- `FREEDOM_FB_CMDLINE_H` (macro, `include/fb_cmdline.h:2`) `#define FREEDOM_FB_CMDLINE_H`
- `FBC_HIST_MAX` (macro, `include/fb_cmdline.h:15`) `#define FBC_HIST_MAX`
- `FBC_ENTRY_MAX` (macro, `include/fb_cmdline.h:16`) `#define FBC_ENTRY_MAX`
- `FBC_BASE_MAX` (macro, `include/fb_cmdline.h:17`) `#define FBC_BASE_MAX`
- `FBC_LIST_NAMES` (macro, `include/fb_cmdline.h:18`) `#define FBC_LIST_NAMES`
- `fbc_history` (struct, `include/fb_cmdline.h:20`)
- `fbc_history_init` (function, `include/fb_cmdline.h:27`) `void fbc_history_init(fbc_history *h);`
- `fbc_history_free` (function, `include/fb_cmdline.h:28`) `void fbc_history_free(fbc_history *h);`
- `fbc_history_push` (function, `include/fb_cmdline.h:31`) `int fbc_history_push(fbc_history *h, const char *text, size_t len);` - #define FBC_BASE_MAX   256    /* bytes of a completion base path #define FBC_LIST_NAMES 40     /* ca
- `fbc_history_prev` (function, `include/fb_cmdline.h:35`) `const char *fbc_history_prev(fbc_history *h, const char *cur, size_t curlen);` - Older entry (saves cur as the draft when leaving the live line), or NULL when there is none. * The p
- `fbc_history_next` (function, `include/fb_cmdline.h:38`) `const char *fbc_history_next(fbc_history *h);` - Older entry (saves cur as the draft when leaving the live line), or NULL when there is none. * The p
- `fbc_complete_split` (function, `include/fb_cmdline.h:42`) `long fbc_complete_split(const char *text, size_t n, char *base, size_t cap, size` - Splits the trailing property path of text[0,n): base ("a.b" of "a.b.c", "" = global) into base[cap],
- `fbc_names_expr` (function, `include/fb_cmdline.h:46`) `size_t fbc_names_expr(const char *base, char *out, size_t cap);` - JS expression returning the newline-joined property names reachable from the path `base` * (no gette
- `fbc_complete_pick` (function, `include/fb_cmdline.h:51`) `size_t fbc_complete_pick(const char *names, const char *prefix, size_t plen, cha` - From the newline-separated `names`, those starting with prefix[0,plen): `ins` gets the longest commo
- `fbc_filter` (enum, `include/fb_cmdline.h:54`)
- `fbc_filter_passes` (function, `include/fb_cmdline.h:62`) `int fbc_filter_passes(int filter, int level);`
- `fbc_filter_next` (function, `include/fb_cmdline.h:63`) `int fbc_filter_next(int filter);` - extension beyond the prefix, `list` the candidates space-separated; *count how many matched. Returns
- `fbc_filter_label` (function, `include/fb_cmdline.h:64`) `const char *fbc_filter_label(int filter);` - the length of the insertion. size_t fbc_complete_pick(const char *names, const char *prefix, size_t
- `FREEDOM_FB_PANES_H` (macro, `include/fb_panes.h:2`) `#define FREEDOM_FB_PANES_H`
- `fbp_tab` (enum, `include/fb_panes.h:17`)
- `FBP_SELECTOR_MAX` (macro, `include/fb_panes.h:30`) `#define FBP_SELECTOR_MAX`
- `FBP_EXPR_MAX` (macro, `include/fb_panes.h:31`) `#define FBP_EXPR_MAX`
- `fbp_tab_label` (function, `include/fb_panes.h:34`) `const char *fbp_tab_label(int tab);` - FBP_CSS, FBP_SCRIPT, FBP_NET, FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weig
- `fbp_tab_from_name` (function, `include/fb_panes.h:37`) `int fbp_tab_from_name(const char *name);` - FBP_PROFILE,   /* where the JS time went (sampling profiler, time-weighted) FBP_THROWS,    /* every
- `fbp_tab_wrap` (function, `include/fb_panes.h:40`) `int fbp_tab_wrap(int tab, int dir);` - FBP_STORAGE,   /* cookies, localStorage and sessionStorage of the page FBP_COUNT } fbp_tab; #define
- `fbp_tab_span` (function, `include/fb_panes.h:43`) `void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w` - #define FBP_SELECTOR_MAX 256   /* bytes of the user's argument (selector / index / filter) #define F
- `fbp_tab_at` (function, `include/fb_panes.h:46`) `int fbp_tab_at(double x, double cell_w, double pad_cells);` - /* Label of a tab; an out-of-range id is the console. Never NULL. const char *fbp_tab_label(int tab)
- `fbp_is_pane` (function, `include/fb_panes.h:49`) `int fbp_is_pane(int tab);` - /* Tab named `name` (case-insensitive), or -1 when unknown / NULL. int fbp_tab_from_name(const char

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 11
- Cross-boundary resolved imports (EXTRACTED): 14

## Connections

- [EXTRACTED] depends_on community 1 <-> 9 (strength 0.9): Extracted import edge crosses communities: gui/browser_ui.c imports include/freebug.h.

## Risks

- [dataflow UNCHECKED_ALLOC] `fuzz/fuzz_fb_cmdline.c:7` `LLVMFuzzerTestOneInput` `cut`: Result of allocator stored in `cut` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `fuzz/fuzz_fb_cmdline.c:7` `LLVMFuzzerTestOneInput` `t`: Result of allocator stored in `t` is never checked against NULL.

## Open Questions

- Why do 11 file(s) lack file-level docs (e.g. `fuzz/fuzz_fb_cmdline.c`)? What purpose do they serve?
- What would break if the most connected file in include: fb_cmdline changed?
- Should include: fb_cmdline be split, given cohesion 0.44?

## Sources

- `fuzz/fuzz_fb_cmdline.c`
- `fuzz/fuzz_freebug.c`
- `include/fb_cmdline.h`
- `include/fb_panes.h`
- `include/freebug.h`
- `src/fb_cmdline.c`
- `src/fb_panes.c`
- `src/freebug.c`
- `tests/test_fb_cmdline.c`
- `tests/test_fb_panes.c`
- `tests/test_freebug.c`
