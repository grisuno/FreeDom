# Spec: `css_text`

## 1. Purpose

Single owner of CSS text-presentation value interpretation, extracted from
`css.c`. Pure, bounded, fail-closed. Fourth cut of cascade decomposition.

## 2. Contract

```c
int ct_interp_fontfamily(const char *v);
int ct_interp_texttransform(const char *v);
int ct_interp_opacity(const char *v);
int ct_interp_valign(const char *v);
int ct_expand_valign(const char *val, css_decl *dst, int cap);
int ct_interp_transition_property(const char *v);
int ct_interp_whitespace(const char *v);
int ct_interp_tabsize(const char *v);
int ct_interp_textdeco_style(const char *v);
int ct_interp_textdeco_thickness(const char *v);
int ct_interp_aspect_ratio(const char *v, int *num, int *den);
int ct_interp_direction(const char *v);
int ct_interp_liststyle(const char *v);
int ct_interp_spacing(const char *v, int *out);
int ct_emit_spacing(css_decl *dst, int cap, int slot, const char *val);
int ct_expand_shadow(const char *val, css_decl *dst, int cap);
```

- `fontfamily` buckets generic + common families, case-insensitive; -1 unknown.
- `opacity` accepts 0..1 float or N%, clamps 0..100.
- `text-shadow` needs dx+dy or dropped; `none` emits explicit reset;
  `url()` dropped (never fetch); missing color defaults to current color.
- `aspect-ratio` `W/H` stored x1000, clamped positive.

## 3. Semantics

- Given `serif`, when interpreted, then `CSS_FF_SERIF`.
- Given `0.5`, when opacity read, then 50.
- Given `1px 2px red`, when shadow expanded, then 3 decls with color.
- Given `1px` alone, when shadow expanded, then 0 (dropped).

## 4. Security guarantees

- No IO, no fetch, no global state. Bounded token buffers.
- Fail closed on malformed input.

## 5. Out of scope

- Shaping/painting (downstream `text_shape`/painter).
- Full `font` shorthand (dispatch-level, stays in `css.c`).
