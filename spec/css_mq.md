# `css_mq` — evaluador de media queries (Media Queries 4)

Módulo puro (`cmq_`), sin I/O, sin DOM, sin asignación. Extraído de `css.c`
(cláusula anti-monolito) cuando la sintaxis de rango de Media Queries 4 se volvió la
forma por defecto de los design systems: Tailwind v4 (huggingface.co, antjs.org)
emite `@media (width>=48rem)` y github.com `@media (width<=767px)`. El evaluador
anterior solo conocía `min-width`/`max-width`/`prefers-color-scheme` y fallaba cerrado
en todo lo demás, así que el `.container{max-width:48rem}` de Tailwind no aplicaba
nunca y la página se pintaba a todo el ancho.

## Entrada

`cmq_matches(query, len, env)`: una *media query list* (el preludio de `@media` o el
`media=` de un `<link>`/`@import`) y el entorno:

| Campo `cmq_env` | Significado |
| :-- | :-- |
| `width_px` | ancho de render (el único dato real; doctrina tanda 12) |
| `height_px` | alto **normalizado** (`CSS_MEDIA_DEFAULT_HEIGHT`, igual que `vh`) |
| `prefers_dark` | preferencia del usuario |
| `print` | PDF |

## Gramática soportada

- Lista separada por comas = OR. Un segmento vacío = `all`.
- `[not|only] <tipo> [and <cond>]*`, `<cond> [and <cond>]*`, `<cond> [or <cond>]*`,
  `not <cond>`; paréntesis anidados `((a) or (b))`.
- Rango: `(name op v)`, `(v op name)`, `(v1 op name op v2)` con `<`, `<=`, `>`, `>=`, `=`.
- Plano: `(name: v)`, `(min-name: v)`, `(max-name: v)`, booleano `(name)`.

## Características y su respuesta

Las que dependen del dispositivo responden la **identidad de escritorio
normalizada** (anti-fingerprinting): nunca el hardware real.

| Característica | Valor |
| :-- | :-- |
| `width` | `width_px` |
| `height` | `height_px` |
| `aspect-ratio` | `width_px / height_px` |
| `orientation` | `landscape` |
| `prefers-color-scheme` | `dark` / `light` según `prefers_dark` |
| `prefers-reduced-motion`, `prefers-reduced-transparency`, `prefers-contrast` | `no-preference` |
| `forced-colors`, `inverted-colors` | `none` |
| `hover`, `any-hover` | `hover` |
| `pointer`, `any-pointer` | `fine` |
| `color` | 8 (booleano verdadero) |
| `color-gamut` | `srgb` |
| `resolution` / `-webkit-device-pixel-ratio` | 1dppx (96dpi) |
| `display-mode` | `browser` |
| `scripting` | desconocido → falso |
| tipos | `all`, `screen` (no print), `print` (print) |

Longitudes por el ÚNICO resolvedor (`css_length`) con el contexto inicial: dentro
de una media query `em`/`rem` son 16 px (MQ4 §1.3).

**Falla cerrado:** una característica o tipo desconocido, un operador mal formado o
un valor ilegible hace FALSO esa condición; `not` de algo desconocido también es
falso (MQ4 §3.2: una query mal formada es `not all`).

Dado-Cuando-Entonces (ancho 1000, alto 1080):
- `(width>=48rem)` → verdadero (768 ≤ 1000); `(width>=64rem)` → falso.
- `(width<=767px)` → falso; `(768px <= width <= 1011px)` → verdadero.
- `screen and (min-width:600px)` → verdadero; `print` → falso.
- `not all and (max-width:600px)` → verdadero; `not (hover:hover)` → falso.
- `(prefers-reduced-motion:reduce)` → falso; `(hover)` → verdadero.
- `((max-width:500px) or (min-width:900px))` → verdadero.
- `(frobnicate:1)` → falso; `(width >> 3px)` → falso.
