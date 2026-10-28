# `src/text_shape.c`

> Source: [src/text_shape.c:1](../../src/text_shape.c#L1) | language `c` | coverage 50.0% | [API index](../index.md)

## Contents

- **Structs:** [`tsh_entry`](#tsh_entry), [`tsh_web`](#tsh_web), [`tsh_lfam`](#tsh_lfam), [`tsh_llist`](#tsh_llist), [`tsh_fb`](#tsh_fb), [`tsh_fb_cp`](#tsh_fb_cp), [`tsh_cover_ctx`](#tsh_cover_ctx), [`tsh_measure_slot`](#tsh_measure_slot)
- **Type Aliases:** [`loaded`](#loaded), [`used`](#used), [`name`](#name), [`file`](#file)
- **Functions:** [`characters`](#characters), [`slice`](#slice), [`tsh_webfont_register`](#tsh_webfont_register), [`tsh_webfont_clear`](#tsh_webfont_clear), [`tsh_family_is_generic`](#tsh_family_is_generic), [`tsh_pick_from_list`](#tsh_pick_from_list), [`tsh_pick_family`](#tsh_pick_family), [`tsh_local_handle`](#tsh_local_handle), [`tsh_ready`](#tsh_ready), [`tsh_shape`](#tsh_shape), [`tsh_segment`](#tsh_segment), [`tsh_measure`](#tsh_measure), [`tsh_draw`](#tsh_draw), [`tsh_face`](#tsh_face), [`tsh_shutdown`](#tsh_shutdown)
- **Macros:** [`_POSIX_C_SOURCE`](#_posix_c_source), [`TSH_MAX_FONT_BYTES`](#tsh_max_font_bytes), [`TSH_CACHE_SLOTS`](#tsh_cache_slots), [`TSH_WEB_SLOTS`](#tsh_web_slots), [`TSH_SUBS_MAX`](#tsh_subs_max), [`TSH_BLANK_GLYPH`](#tsh_blank_glyph), [`TSH_FB_SLOTS`](#tsh_fb_slots), [`TSH_FB_BLOCKS`](#tsh_fb_blocks), [`TSH_FB_CP_SLOTS`](#tsh_fb_cp_slots), [`TSH_MAX_RUNS`](#tsh_max_runs), [`TSH_MEASURE_SLOTS`](#tsh_measure_slots), [`TSH_MEASURE_TEXT_MAX`](#tsh_measure_text_max)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class loaded
    <<type_alias>> loaded
    class tsh_entry
    <<struct>> tsh_entry
    class used
    <<type_alias>> used
    class tsh_web
    <<struct>> tsh_web
    class name
    <<type_alias>> name
    class tsh_lfam
    <<struct>> tsh_lfam
    class tsh_llist
    <<struct>> tsh_llist
    class file
    <<type_alias>> file
    class tsh_fb
    <<struct>> tsh_fb
    class tsh_fb_cp
    <<struct>> tsh_fb_cp
    class tsh_cover_ctx
    <<struct>> tsh_cover_ctx
    class tsh_measure_slot
    <<struct>> tsh_measure_slot
```

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_src_text_shape_c__tsh_pick_from_list(["tsh_pick_from_list"])
    n_src_text_shape_c__tsh_family_is_generic(["tsh_family_is_generic"])
    n_src_text_shape_c__tsh_local_handle(["tsh_local_handle"])
    n_src_text_shape_c__TSH_MAX_RUNS(["TSH_MAX_RUNS"])
    n_src_text_shape_c__tsh_segment(["tsh_segment"])
    n_src_text_shape_c__tsh_shutdown(["tsh_shutdown"])
    n_src_text_shape_c__tsh_webfont_clear(["tsh_webfont_clear"])
    n_src_text_shape_c__tsh_webfont_register(["tsh_webfont_register"])
    n_include_webfont_h__wf_name_hash["webfont.wf_name_hash"]
    n_gui_browser_ui_c__resolve["browser_ui.resolve"]
    n_gui_browser_ui_c__strcmp["browser_ui.strcmp"]
    n_src_text_shape_c__tsh_pick_from_list --> n_src_text_shape_c__tsh_family_is_generic
    n_src_text_shape_c__tsh_local_handle --> n_src_text_shape_c__tsh_pick_from_list
    n_src_text_shape_c__TSH_MAX_RUNS --> n_src_text_shape_c__tsh_segment
    n_src_text_shape_c__tsh_shutdown --> n_src_text_shape_c__tsh_webfont_clear
    n_src_text_shape_c__tsh_webfont_register -.-> n_include_webfont_h__wf_name_hash
    n_src_text_shape_c__tsh_pick_from_list -.-> n_gui_browser_ui_c__resolve
    n_src_text_shape_c__tsh_local_handle -.-> n_gui_browser_ui_c__strcmp
```

## Structs

<a id="tsh_entry"></a>

### `tsh_entry`

`struct` | [src/text_shape.c:36](../../src/text_shape.c#L36)

```c
typedef struct tsh_entry
```

---

<a id="tsh_web"></a>

### `tsh_web`

`struct` | [src/text_shape.c:192](../../src/text_shape.c#L192)

```c
typedef struct tsh_web
```

---

<a id="tsh_lfam"></a>

### `tsh_lfam`

`struct` | [src/text_shape.c:464](../../src/text_shape.c#L464)

```c
typedef struct tsh_lfam
```

---

<a id="tsh_llist"></a>

### `tsh_llist`

`struct` | [src/text_shape.c:470](../../src/text_shape.c#L470)

```c
typedef struct tsh_llist
```

---

<a id="tsh_fb"></a>

### `tsh_fb`

`struct` | [src/text_shape.c:665](../../src/text_shape.c#L665)

```c
typedef struct tsh_fb
```

---

<a id="tsh_fb_cp"></a>

### `tsh_fb_cp`

`struct` | [src/text_shape.c:681](../../src/text_shape.c#L681)

```c
typedef struct
```

Per-code-point verdicts of fb_entry.

The block cache above only remembers which face a 256-code-point block asked for first; a code point that face lacks used to go back to fontconfig on every occurrence (Wikipedia: a third of its render time). Direct-mapped, * stale entries simply miss. define TSH_FB_CP_SLOTS 1024u

---

<a id="tsh_cover_ctx"></a>

### `tsh_cover_ctx`

`struct` | [src/text_shape.c:809](../../src/text_shape.c#L809)

```c
typedef struct tsh_cover_ctx
```

---

<a id="tsh_measure_slot"></a>

### `tsh_measure_slot`

`struct` | [src/text_shape.c:919](../../src/text_shape.c#L919)

```c
typedef struct
```

Memoized measures.

A page measures the same words over and over (every line break decision, every flex basis probe), and each miss is a HarfBuzz shape plus fontconfig coverage lookups. * Direct-mapped; the key is the RESOLVED face, so two descriptors that land on one face share. define TSH_MEASURE_SLOTS 4096u define TSH_MEASURE_TEXT_MAX 48u

---

## Type Aliases

<a id="loaded"></a>

### `loaded`

`type_alias` | [src/text_shape.c:35](../../src/text_shape.c#L35)

```c
typedef struct tsh_entry { int loaded;
```

One resolved face per (family, bold, italic). family is a CSS_FF_* bucket * (0..CSS_FF_FANTASY); idx = family*4 + bold*2 + italic. define TSH_CACHE_SLOTS ((CSS_FF_FANTASY + 1) * 4)

---

<a id="used"></a>

### `used`

`type_alias` | [src/text_shape.c:191](../../src/text_shape.c#L191)

```c
typedef struct tsh_web { int used;
```

Per-document @font-face table (spec/webfont.md): registered by the trusted parent from policy-gated fetches, keyed by (name hash, bold, italic).

Memory only, freed by tsh_webfont_clear (navigation) and tsh_shutdown. Never the * worker: shaping a registered face runs on the painter side like every face. define TSH_WEB_SLOTS 16

---

<a id="name"></a>

### `name`

`type_alias` | [src/text_shape.c:463](../../src/text_shape.c#L463)

```c
typedef struct tsh_lfam { char name[TSH_FAMILY_MAX];
```

---

<a id="file"></a>

### `file`

`type_alias` | [src/text_shape.c:664](../../src/text_shape.c#L664)

```c
typedef struct tsh_fb { char file[512];
```

Fallback faces, one per font file fontconfig picked (bold/italic folded into the match).

The block cache maps (code point >> 8, bold) to a slot + 1, or -1 * for "no installed face covers this block" (0 = not asked yet). define TSH_FB_SLOTS 24 define TSH_FB_BLOCKS (0x110000u >> 8)

---

## Functions

<a id="characters"></a>

### `characters`

`function` | [src/text_shape.c:101](../../src/text_shape.c#L101)

```c
* hold characters ('-', ':') that the pattern syntax treats specially. */ static int load_entry_file(tsh_entry *e, const char *path, int index);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `'-'` |  |  |  |
| `':'` |  |  |  |

**Returns:** `* hold`

---

<a id="slice"></a>

### `slice`

`function` | [src/text_shape.c:214](../../src/text_shape.c#L214)

```c
* woff2 slice (spec/webfont.md);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `md` | `spec/webfont.` |  |  |

**Returns:** `* woff2`

---

<a id="tsh_webfont_register"></a>

### `tsh_webfont_register`

`function` | [src/text_shape.c:271](../../src/text_shape.c#L271)

```c
int tsh_webfont_register(const char *name, const unsigned char *bytes, size_t nbytes, int bold, int italic)
```

Registers one fetched @font-face for this document (spec/webfont.md): name is the author family (hashed with wf_name_hash), bytes the validated font program (copied; caller keeps ownership).

Re-registering a key replaces it. Returns 0 on success, -1 fail-closed (NULL/empty/oversize args, bad magic, unparseable bytes, table full). Trusted side only; never the worker.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |
| `bytes` | `unsigned char *` |  |  |
| `nbytes` | `size_t` |  |  |
| `bold` | `int` |  |  |
| `italic` | `int` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tsh_webfont_register`](#tsh_webfont_register) (include/text_shape.h:114).

*Calls:* [`wf_name_hash`](include.webfont.h.md#wf_name_hash)

---

<a id="tsh_webfont_clear"></a>

### `tsh_webfont_clear`

`function` | [src/text_shape.c:306](../../src/text_shape.c#L306)

```c
void tsh_webfont_clear(void)
```

Drops every registered webfont (document teardown / navigation).

Idempotent, NULL-safe by construction (no args). tsh_shutdown also clears the table.

> **Inherited:** Documentation from [`tsh_webfont_clear`](#tsh_webfont_clear) (include/text_shape.h:120).

*Called by:* [`tsh_shutdown`](#tsh_shutdown)

---

<a id="tsh_family_is_generic"></a>

### `tsh_family_is_generic`

`function` | [src/text_shape.c:346](../../src/text_shape.c#L346)

```c
int tsh_family_is_generic(const char *name)
```

1 for a CSS generic family keyword (serif, sans-serif, monospace, cursive, fantasy, system-ui, ui-*, emoji, math, fangsong), case-insensitive.

Pure.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tsh_family_is_generic`](#tsh_family_is_generic) (include/text_shape.h:52).

*Called by:* [`tsh_pick_from_list`](#tsh_pick_from_list)

---

<a id="tsh_pick_from_list"></a>

### `tsh_pick_from_list`

`function` | [src/text_shape.c:358](../../src/text_shape.c#L358)

```c
int tsh_pick_from_list(const char *list, tsh_name_resolver resolve, void *ctx, char *out, size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `list` | `char *` |  |  |
| `resolve` | `tsh_name_resolver` |  |  |
| `ctx` | `void *` |  |  |
| `out` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

*Calls:* [`resolve`](gui.browser_ui.c.md#resolve), [`tsh_family_is_generic`](#tsh_family_is_generic)

*Called by:* [`tsh_local_handle`](#tsh_local_handle)

---

<a id="tsh_pick_family"></a>

### `tsh_pick_family`

`function` `const` | [src/text_shape.c:379](../../src/text_shape.c#L379)

```c
const char *tsh_pick_family(const char *req, const char *const *subs, const int *strong, size_t n, int (*installed)(const char *name, void *ctx), void *ctx)
```

The acceptance rule for one requested name given fontconfig's substituted family list subs[0..n) and their bindings (strong[k] != 0 for a strong/same binding): req itself when installed, else the first INSTALLED entry of the leading run of strong substitutes; a weak substitute ends the run.

Returns the chosen name or NULL. Pure (installed is injected).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `req` | `char *` |  |  |
| `subs` | `char *const *` |  |  |
| `strong` | `int *` |  |  |
| `n` | `size_t` |  |  |
| `ctx` | `int (*installed)(const char *name, void * )` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `char *`

> **Inherited:** Documentation from [`tsh_pick_family`](#tsh_pick_family) (include/text_shape.h:68).

---

<a id="tsh_local_handle"></a>

### `tsh_local_handle`

`function` | [src/text_shape.c:499](../../src/text_shape.c#L499)

```c
int tsh_local_handle(const char *list)
```

Handle (>0) for an author family list that resolves to a local family, cached per list; 0 when nothing resolves, the list is NULL/empty, or a cap is hit (the caller then uses the bucket).

Trusted side only.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `list` | `char *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`tsh_local_handle`](#tsh_local_handle) (include/text_shape.h:75).

*Calls:* [`strcmp`](gui.browser_ui.c.md#strcmp), [`tsh_pick_from_list`](#tsh_pick_from_list)

---

<a id="tsh_ready"></a>

### `tsh_ready`

`function` | [src/text_shape.c:550](../../src/text_shape.c#L550)

```c
int tsh_ready(void)
```

1 once a fallback (sans) font resolves; lazily initialises on first call.

0 means no font backend: the caller must use the toy-API path.

**Returns:** `int`

> **Inherited:** Documentation from [`tsh_ready`](#tsh_ready) (include/text_shape.h:89).

---

<a id="tsh_shape"></a>

### `tsh_shape`

`function` | [src/text_shape.c:555](../../src/text_shape.c#L555)

```c
tsh_status tsh_shape(const tsh_font *f, double px, const char *text, size_t len, cairo_glyph_t *out, size_t cap, size_t *out_n, double *out_adv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `f` | `tsh_font *` |  |  |
| `px` | `double` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `out` | `cairo_glyph_t *` |  |  |
| `cap` | `size_t` |  |  |
| `out_n` | `size_t *` |  |  |
| `out_adv` | `double *` |  |  |

**Returns:** `tsh_status`

---

<a id="tsh_segment"></a>

### `tsh_segment`

`function` | [src/text_shape.c:636](../../src/text_shape.c#L636)

```c
int tsh_segment(const char *text, size_t len, tsh_cover_fn cover, void *ctx, tsh_run *runs, size_t cap)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |
| `cover` | `tsh_cover_fn` |  |  |
| `ctx` | `void *` |  |  |
| `runs` | `tsh_run *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`TSH_MAX_RUNS`](#tsh_max_runs)

---

<a id="tsh_measure"></a>

### `tsh_measure`

`function` | [src/text_shape.c:929](../../src/text_shape.c#L929)

```c
double tsh_measure(const tsh_font *f, double px, const char *text, size_t len)
```

Total advance (px) of [text,len).

Returns < 0.0 on any failure so the caller can fall back to the toy-API measurement.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `f` | `tsh_font *` |  |  |
| `px` | `double` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `double`

> **Inherited:** Documentation from [`tsh_measure`](#tsh_measure) (include/text_shape.h:101).

---

<a id="tsh_draw"></a>

### `tsh_draw`

`function` | [src/text_shape.c:964](../../src/text_shape.c#L964)

```c
tsh_status tsh_draw(cairo_t *cr, const tsh_font *f, double px, double x, double baseline, const char *text, size_t len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cr` | `cairo_t *` |  |  |
| `f` | `tsh_font *` |  |  |
| `px` | `double` |  |  |
| `x` | `double` |  |  |
| `baseline` | `double` |  |  |
| `text` | `char *` |  |  |
| `len` | `size_t` |  |  |

**Returns:** `tsh_status`

---

<a id="tsh_face"></a>

### `tsh_face`

`function` | [src/text_shape.c:971](../../src/text_shape.c#L971)

```c
cairo_font_face_t *tsh_face(const tsh_font *f)
```

The cairo face tsh_draw paints f with (webfont, local family or bucket), or NULL when no face resolves.

Borrowed: owned by the cache, valid until tsh_shutdown / tsh_webfont_clear. The painter selects it so cairo's font extents -- line-height: normal, ascent, descent -- are the metrics of the face that is actually drawn, not of the generic stand-in (CSS 2.1 10.8.1).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `f` | `tsh_font *` |  |  |

**Returns:** `cairo_font_face_t *`

> **Inherited:** Documentation from [`tsh_face`](#tsh_face) (include/text_shape.h:127).

---

<a id="tsh_shutdown"></a>

### `tsh_shutdown`

`function` | [src/text_shape.c:977](../../src/text_shape.c#L977)

```c
void tsh_shutdown(void)
```

Releases cached faces / blobs / FreeType library (leak hygiene; tests).

> **Inherited:** Documentation from [`tsh_shutdown`](#tsh_shutdown) (include/text_shape.h:143).

*Calls:* [`tsh_webfont_clear`](#tsh_webfont_clear)

---

## Macros

<a id="_posix_c_source"></a>

### `_POSIX_C_SOURCE`

`macro` | [src/text_shape.c:12](../../src/text_shape.c#L12)

```c
#define _POSIX_C_SOURCE
```

---

<a id="tsh_max_font_bytes"></a>

### `TSH_MAX_FONT_BYTES`

`macro` | [src/text_shape.c:30](../../src/text_shape.c#L30)

```c
#define TSH_MAX_FONT_BYTES
```

A single font file should never exceed this (CJK faces are the large case).

---

<a id="tsh_cache_slots"></a>

### `TSH_CACHE_SLOTS`

`macro` | [src/text_shape.c:34](../../src/text_shape.c#L34)

```c
#define TSH_CACHE_SLOTS
```

One resolved face per (family, bold, italic). family is a CSS_FF_* bucket (0..CSS_FF_FANTASY); idx = family*4 + bold*2 + italic.

---

<a id="tsh_web_slots"></a>

### `TSH_WEB_SLOTS`

`macro` | [src/text_shape.c:190](../../src/text_shape.c#L190)

```c
#define TSH_WEB_SLOTS
```

Per-document @font-face table (spec/webfont.md): registered by the trusted parent from policy-gated fetches, keyed by (name hash, bold, italic).

Memory only, freed by tsh_webfont_clear (navigation) and tsh_shutdown. Never the worker: shaping a registered face runs on the painter side like every face.

---

<a id="tsh_subs_max"></a>

### `TSH_SUBS_MAX`

`macro` | [src/text_shape.c:406](../../src/text_shape.c#L406)

```c
#define TSH_SUBS_MAX
```

---

<a id="tsh_blank_glyph"></a>

### `TSH_BLANK_GLYPH`

`macro` | [src/text_shape.c:620](../../src/text_shape.c#L620)

```c
#define TSH_BLANK_GLYPH
```

---

<a id="tsh_fb_slots"></a>

### `TSH_FB_SLOTS`

`macro` | [src/text_shape.c:662](../../src/text_shape.c#L662)

```c
#define TSH_FB_SLOTS
```

Fallback faces, one per font file fontconfig picked (bold/italic folded into the match).

The block cache maps (code point >> 8, bold) to a slot + 1, or -1 for "no installed face covers this block" (0 = not asked yet).

---

<a id="tsh_fb_blocks"></a>

### `TSH_FB_BLOCKS`

`macro` | [src/text_shape.c:663](../../src/text_shape.c#L663)

```c
#define TSH_FB_BLOCKS
```

---

<a id="tsh_fb_cp_slots"></a>

### `TSH_FB_CP_SLOTS`

`macro` | [src/text_shape.c:680](../../src/text_shape.c#L680)

```c
#define TSH_FB_CP_SLOTS
```

Per-code-point verdicts of fb_entry.

The block cache above only remembers which face a 256-code-point block asked for first; a code point that face lacks used to go back to fontconfig on every occurrence (Wikipedia: a third of its render time). Direct-mapped, stale entries simply miss.

---

<a id="tsh_max_runs"></a>

### `TSH_MAX_RUNS`

`macro` | [src/text_shape.c:864](../../src/text_shape.c#L864)

```c
#define TSH_MAX_RUNS
```

*Calls:* [`tsh_segment`](#tsh_segment)

---

<a id="tsh_measure_slots"></a>

### `TSH_MEASURE_SLOTS`

`macro` | [src/text_shape.c:917](../../src/text_shape.c#L917)

```c
#define TSH_MEASURE_SLOTS
```

Memoized measures.

A page measures the same words over and over (every line break decision, every flex basis probe), and each miss is a HarfBuzz shape plus fontconfig coverage lookups. Direct-mapped; the key is the RESOLVED face, so two descriptors that land on one face share.

---

<a id="tsh_measure_text_max"></a>

### `TSH_MEASURE_TEXT_MAX`

`macro` | [src/text_shape.c:918](../../src/text_shape.c#L918)

```c
#define TSH_MEASURE_TEXT_MAX
```

---
