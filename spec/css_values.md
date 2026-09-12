# Spec: `css_values`

## 1. Purpose

Single owner of CSS color/background value interpretation, extracted from
`css.c`. Pure, bounded, fail-closed. First cut of `css.c` decomposition.

## 2. Contract

```c
int cv_parse_color(const char *v);
int cv_interp_color(const char *v);
int cv_color_ok(int c);
int cv_bg_alpha_of(const char *v);
int cv_interp_bg(const char *v);
```

- `NULL` input fails closed (`-1` or `CSS_LEN_UNSET`).
- `cv_color_ok(c)` true iff `c != -1`. Sentinels `CC_COLOR_CURRENT`,
  `CC_COLOR_TRANSPARENT` count as values.
- `cv_interp_bg` never fetches: `url()` tokens skipped.
- `cv_bg_alpha_of` returns percent 0..100 or `CSS_LEN_UNSET`.

## 3. Semantics

- Given `red`, when parsed, then packed `0xFF0000`.
- Given `transparent`/`currentColor`, when parsed, then sentinel, `color_ok` true.
- Given junk, when parsed, then `-1`.
- Given `rgba(0,0,0,0.5)`, when alpha read, then `50`.
- Given `background:url(x) red`, when interpreted, then red, no fetch.

## 4. Security guarantees

- No IO, no fetch, no global state. Bounded token buffer `CSS_TOK_MAX`.
- Fail closed on malformed input, unbalanced parens, NULL.

## 5. Out of scope

- Gradients, grid tracks, lengths. Future extracts follow same pattern.
