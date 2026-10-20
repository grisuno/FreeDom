# Spec: `css_gradient`

## 1. Purpose

Single owner of gradient/background-image value expansion, extracted from
`css.c`. Pure, bounded, fail-closed. Second cut of cascade decomposition.

## 2. Contract

```c
int cg_expand_bg_image(const char *val, css_decl *dst, int cap,
                       char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);
int cg_expand_background(const char *val, css_decl *dst, int cap,
                         char (*urltab)[CSS_URL_MAX], size_t *nurl, size_t urlcap);
```

- Accepts `linear-`/`conic-`/`radial-gradient` with >=2 stops, single `url()`,
  `none`, `transparent`.
- Drops whole declaration on unbalanced parens, <2 stops, malformed url,
  multi-layer junk. Never fetches.
- `background` shorthand resets color+image layers per CSS Backgrounds 3 3.10.

## 3. Semantics

- Given `linear-gradient(red, blue)`, when expanded, then gradient group emits
  angle+stops, image reset.
- Given `url(x)` alone, when expanded, then image pool index, gradient reset.
- Given junk gradient, when expanded, then declaration dropped (0).

## 3b. Radial geometry (2026-10-20)

`radial-gradient([<shape> || <size>] [at <position>]?, <stops>)` (CSS Images 3 3.2), parsed by
the pure `cg_parse_radial_prelude`. Until now the prelude was consumed and thrown away (always a
centred circle of radius min(w,h)/2) and a size written as lengths made the WHOLE gradient fail.

- shape: `circle` | `ellipse`. Default ellipse; a circle takes one length, an ellipse two.
- size: `closest-side`, `farthest-side`, `closest-corner`, `farthest-corner` (default), or
  explicit `<length-percentage>{1,2}` (a percentage is of the box width / height).
- position: `at <x> [<y>]` with `left|center|right|top|bottom` and `<length-percentage>`;
  default `50% 50%`. One value centres the other axis.
- Encoding of every length (`cx`,`cy`,`rx`,`ry`): `>= 0` is per-mille of the box width/height
  (so `87.46%` is 875); `< 0` is `-(px) - 1`. `CG_LEN_UNSET` means "not given".
- A prelude that is neither a keyword nor a length list fails closed (the gradient is dropped,
  as before); out-of-range or negative radii fail closed.

Dado `radial-gradient(141.53% 114.68% at 87.46% 55.27%, #9a7cff 36.75%, #0e0aa200)`, entonces
rx = 1415 per-mille of the width, ry = 1147 of the height, centre (875, 553), and the stops parse.

## 4. Security guarantees

- No IO. Bounded `CSS_TOK_MAX`, `CSS_URL_MAX`, `CSS_GRAD_STOPS_MAX`.
- Fail closed on truncation, overrun, NULL.

## 5. Out of scope

- Fetch decision (downstream `render_doc`, gated `caps.images`).
- Repeating gradients (dropped, same as before).
