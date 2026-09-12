# Spec: `css_box`

## 1. Purpose

Single owner of CSS length/box/grid-track value interpretation, extracted
from `css.c`. Pure, bounded, fail-closed. Third cut of cascade decomposition.

## 2. Contract

```c
int cb_length_px(const char *v, double *px);
int cb_interp_len(const char *v, int allow_auto, int *out);
int cb_emit_len(css_decl *dst, int cap, int slot, const char *val,
                int allow_auto, int allow_neg);
int cb_expand_box4(const char *val, int slot_top, int allow_auto, int allow_neg,
                   css_decl *dst, int cap);
int cb_expand_box2(const char *val, int slot_start, int slot_end,
                   int allow_auto, int allow_neg, css_decl *dst, int cap);
int cb_interp_lp(const char *v, int allow_auto, int allow_pct,
                 int *out_px, int *out_pm);
int cb_value_em_milli(const char *v);
int cb_lp_can_be_nonneg(int px_val, int pct_pm);
int cb_next_ws_token(const char **p, char *tok, size_t cap);
int cb_interp_align(const char *v);
int cb_interp_fontsize_ex(const char *v, int *abs_out);
int cb_interp_lineheight(const char *v);
int cb_interp_weight(const char *v);
int cb_interp_style(const char *v);
int cb_interp_textdeco(const char *v);
int cb_interp_display(const char *v);
int cb_interp_gap(const char *v);
int cb_interp_justify(const char *v);
int cb_interp_gridcols(const char *v);
int cb_expand_grid_template_cols(const char *val, css_decl *dst, int cap);
```

- `cb_interp_len` accepts px/em/rem/vw/vh/calc/math-fns/bare 0/`auto`.
  Rejects bare non-zero numbers and `%` (fail closed).
- `cb_emit_len` writes px half plus `%` half when the slot accepts
  `<length-percentage>`; claims both halves on wide keywords/`auto`-reset.
- `cb_expand_box4/2` fail closed on partial pairs (never half a shorthand)
  and on trailing junk (`1px 2px 3px 4px 5px` drops whole, per CSS -- the old
  code silently kept the first four).
- `CB_AUTO_*` modes mirror the old `AUTO_*`: reject/value/reset/reset-none.
- Grid `repeat()` with auto-fill/fit or malformed count fails the whole value.
- Proven-equivalent mutants (documented, allowlisted): `cb_copy_trim`'s
  `a >= b` vs `a > b` -- its only caller drops an empty trim either way
  (`fit-content()` never yields a value), so no test can distinguish them;
  the fail-closed spelling is kept. Same class as `css_round_clamp`
  boundaries (cast truncation makes edge comparisons unobservable).

## 3. Semantics

- Given `12px`, when interpreted, then 12.
- Given `auto` with `CB_AUTO_REJECT`, when interpreted, then reject (0).
- Given `margin:0 auto`, when expanded, then centering decls.
- Given `repeat(auto-fill, 1fr)`, when counted, then whole value dropped.

## 4. Security guarantees

- No IO, no fetch, no global state. Bounded `CSS_TOK_MAX`, track caps,
  `CSS_LEN_MAX`/`CSS_PCT_MAX` clamps before any int cast (no UB).
- Fail closed on malformed input, NULL handled by callers via dispatch.

## 5. Out of scope

- Cascade/dispatch/sheet storage (stays in `css.c`).
- Used-value clamping against containing blocks (consumer-side).
