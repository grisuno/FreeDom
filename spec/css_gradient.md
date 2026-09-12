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

## 4. Security guarantees

- No IO. Bounded `CSS_TOK_MAX`, `CSS_URL_MAX`, `CSS_GRAD_STOPS_MAX`.
- Fail closed on truncation, overrun, NULL.

## 5. Out of scope

- Fetch decision (downstream `render_doc`, gated `caps.images`).
- Repeating gradients (dropped, same as before).
