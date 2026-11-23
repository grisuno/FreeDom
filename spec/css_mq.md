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
- El valor de una característica de longitud puede ser una función matemática
  (`calc()`, `min()`, `max()`, `clamp()`; MQ4 §4.1 remite a CSS Values): se evalúa con
  el MISMO evaluador que una declaración (`cb_math_length_px`) contra la fuente inicial
  de 16 px. MediaWiki escribe todos sus cortes como
  `@media (max-width: calc(1120px - 1px))`; sin esto ninguno aplicaba y Wikipedia
  mostraba a la vez el diseño ancho y el angosto. Un porcentaje o un resultado sin
  dimensión no es una longitud de media query: la característica es desconocida
  (fail-closed, como cualquier valor que no se puede leer).
  - Dado `width_px = 1000`, cuando la query es `(max-width: calc(1120px - 1px))`,
    entonces coincide; con `(min-width: calc(1120px - 1px))` no coincide.
  - Dado lo mismo, cuando la query es `(width <= calc(70em - 1px))`, entonces coincide.
  - Dado `(max-width: calc(50% + 10px))` o `(max-width: calc(2 * 3))`, entonces no coincide.

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

## Container queries sin layout (tanda 83): `cmq_container_surely`

`@container [nombre] <condición>` (CSS Conditional 5 §2) pregunta por el tamaño del
**contenedor**, que la cascada (pura, previa al layout) no conoce. Antes se descartaba
la regla entera, así que ni la rama `<` ni la `>=` de un componente aplicaban nunca.

Hecho que la hace evaluable sin layout: un contenedor en flujo **nunca es más ancho que
el ancho de render**. Una condición que es un intervalo de anchos (comparaciones de
`width`/`inline-size` unidas por `and`) es verdadera para TODO ancho en `[0, W]` si y solo
si lo es en los dos extremos. Entonces:

- Se aplica la regla solo si es **seguramente** verdadera: cierta en `w=0` y en `w=W`.
- Cualquier cosa que no sea un intervalo de anchos falla cerrado (regla omitida, como
  antes): `or`, `not`, `height`/`block-size`/`aspect-ratio`/`orientation` (la altura del
  contenedor no está acotada por la del viewport), `style()`, `scroll-state()`.
- El nombre de contenedor se ignora: la cota vale para cualquier contenedor.

Dado-Cuando-Entonces (W = 1000):
- `(width<63.25rem)` → aplica (cierta en 0 y en 1000).
- `(width>=1280px)` → no aplica; `(width<480px)` → no aplica (falsa en 1000: puede no
  cumplirse); `blankslate (width<=34rem)` → no aplica.
- `(max-width: 1200px)` → aplica; `(min-width:32px)` → no aplica (falsa en 0).
- `(width<80rem) or (width>9px)` → no aplica (`or`); `(height<10px)` → no aplica.

## Container queries con layout (tanda 90): `cmq_container_holds`

La cota «seguramente verdadera» deja sin aplicar toda rama `>=` de un componente (el
formulario de alta de GitHub: `@container homepage-signup (width>=28.5rem)` pone email y
botón en fila; sin ella quedan apilados). La condición se evalúa ahora contra el **ancho
real** del contenedor cuando el motor lo conoce, y cae a la cota anterior cuando no.

Modelo (puro, sin I/O):

- `container-type` (`normal` | `inline-size` | `size`), `container-name` (hasta
  `CMQ_CONTAINER_NAMES` nombres, como hash) y el shorthand `container: <nombres> / <tipo>`
  son propiedades reales de `css_style`.
- El motor (page_view, que resuelve de la raíz hacia abajo) entrega a la cascada, como
  input del elemento igual que `font_size`, la **cadena de contenedores ancestro**
  (`cmq_container`: tipo, nombres, ancho de contenido en px o `-1` = desconocido, padre).
- `@container` ya **no se evalúa al parsear**: sus reglas entran a la hoja marcadas con su
  condición (y la de los `@container` que las anidan) y se filtran al matchear.
- `cmq_container_holds(prelude, scope, max_width)`: el contenedor consultado es el
  ancestro más cercano con `container-type != normal` y, si el preludio trae nombre, con
  ese nombre (Conditional 5 §2.1). Si existe y su ancho es conocido, la condición se evalúa
  con ese ancho; las mismas formas vetadas (`or`, `not`, altura, `style()`...) siguen
  fallando cerrado. Si no hay contenedor elegible **o su ancho es desconocido**, el
  resultado es `cmq_container_surely` (comportamiento anterior, byte-idéntico con
  `scope == NULL`).

Origen del ancho: la geometría del layout final que el padre ya entrega al worker
(`OP_GEOM`, `spec/js_geom.md`) — por tanto **solo en hosts allow∩js**; el resto conserva
la cota. Es el ancho de la caja del contenedor menos su padding y borde horizontales. La
primera derivación de una página no tiene geometría (cota); al llegar la primera tabla, si
el ancho de algún contenedor registrado cambió, el worker invalida su vista y el siguiente
tick la re-deriva. Acotado a `TAB_CQ_REDERIVE_MAX` re-derivaciones por generación del DOM
(un contenedor cuyo ancho dependiera de su contenido no puede oscilar sin fin).

Dado-Cuando-Entonces:
- Dado `scope = {inline-size, "card", 480px}`, `card (width>=456px)` → verdadero;
  `(width>=500px)` → falso; `other (width>=1px)` → sin contenedor con ese nombre → cota → falso.
- Dado un ancestro `normal` de 900 px y, encima, uno `inline-size` de 300 px:
  `(width<400px)` → verdadero (el `normal` no es contenedor).
- Dado `scope` con ancho `-1`: `(width<63.25rem)` → verdadero (cota), `(width>=1px)` → falso.
- `(height>1px)` con contenedor conocido → falso (vetado).

Fuera de alcance: unidades `cqw`/`cqi`, `style()`, consultas de alto, `::before`/`::after`
dentro de `@container` con contenedor conocido (siguen con la cota), custom properties
declaradas dentro de `@container` (cota), hosts no confiables.

## Ancho del viewport en la ventana (tanda 100)

`width` de una media query es el del viewport **incluida** la barra de desplazamiento (Media
Queries 4 §4.1), y las unidades `vw` miden el bloque contenedor inicial suponiendo que no hay
barras (CSS Values 4 §6.1.2). La ventana restaba su canal de barra (12 px): a 1012 px de ventana
las consultas veían 1000, así que jkanime aplicaba sus reglas `max-width:1000px` (menú de móvil,
"Buscar" en la barra lateral) y GitHub no llegaba a su `min-width:1012px`; Firefox ve 1012. La
ventana pasa ahora `gui_viewport_w` = ancho de la ventana; el ancho de pintado sigue siendo
`content_width()`. El headless no cambia: su lienzo ES el viewport, sin canal (como el Firefox
headless del arnés de paridad).
