# css_import (`ci_`) — `@import` por el mismo fetcher gateado

Módulo puro (sin I/O, sin asignación, sin estado global). Lee el **preámbulo** de una hoja de
estilo — las reglas `@import` que CSS Cascade 5 §2 permite antes de cualquier otra regla — y
construye el envoltorio condicional que hace que el texto importado se comporte como lo exige la
spec. La red la pone el llamador (`tab.c`, worker): cada import se pide con `child_fetch`, el
mismo `TAG_SUBREQ` que un `<link rel=stylesheet>`, así que el padre re-aplica **toda** la política
(https-only, hostblock, realm, `net_guard`, gate de CSS). Un `@import` no abre ninguna capacidad
que un `<link>` no tenga ya: solo se sigue cuando las hojas externas ya se descargan (`caps.css`).

**Por qué:** lobste.rs (allow∩js) declara toda su paleta en hojas `@import` condicionadas por
`prefers-color-scheme`/`prefers-contrast`; descartar el `@import` dejaba las etiquetas, bordes y
colores de enlace sin pintar.

## Contrato

```c
size_t ci_scan(const char *css, size_t len, ci_import *out, size_t cap);
int    ci_wrap(const ci_import *im, char *open, size_t ocap, char *close, size_t ccap);
int    ci_balanced(const char *css, size_t len);
```

`ci_scan` salta espacios, comentarios, `@charset "...";` y sentencias `@layer a, b;`, y lee cada
`@import` hasta el primer `;` de nivel 0. Para en la primera regla que no es ninguna de esas (CSS:
un `@import` posterior es inválido y se ignora). Devuelve cuántos `ci_import` escribió (≤ `cap`).

Forma de cada import: `@import <url> [layer | layer(<nombre>)] [supports(<cond>)] [<media>] ;`
con `<url>` = `url(x)`, `url("x")`, `url('x')`, `"x"` o `'x'`.

| Campo | Contenido |
| :-- | :-- |
| `url` | texto crudo, sin resolver (lo resuelve el llamador contra la URL de la hoja) |
| `has_layer` / `layer` | `layer` ⇒ capa anónima (`layer` vacío); `layer(a.b)` ⇒ `"a.b"` |
| `supports` | condición de `supports(...)`, sin los paréntesis exteriores; `""` = ninguna |
| `media` | lista de media queries; `""` = `all` |

`ci_wrap` escribe `open` = `@layer N {` + `@supports (S) {` + `@media M {` (solo las partes
presentes, en ese orden: la capa envuelve a la condición) y `close` = las llaves de cierre. Sin
condiciones ⇒ `open` y `close` vacíos. Devuelve 0, o -1 si no cabe.

`ci_balanced` = 1 si en el texto todo comentario y cadena termina y las llaves `{}` (fuera de
cadenas y comentarios) nunca bajan de 0 y cierran en 0. El llamador **solo envuelve** un texto
balanceado: un `}` suelto o un `/*` sin cerrar dentro de la hoja importada cerraría el
envoltorio y escaparía del gate de `@media`.

## Dado-Cuando-Entonces

- Dado `@import url("/a.css");` entonces 1 import, url `/a.css`, sin condiciones; `ci_wrap` vacío.
- Dado `@import "/d.css" (prefers-color-scheme: dark) and (not (prefers-contrast: more));`
  entonces media = `(prefers-color-scheme: dark) and (not (prefers-contrast: more))` y
  `open` = `@media (prefers-color-scheme: dark) and (not (prefers-contrast: more)) {`.
- Dado `@import url(x.css) layer(base) supports(display: grid) screen;` entonces
  `open` = `@layer base {@supports (display: grid) {@media screen {` y `close` = `}}}`.
- Dado `@charset "utf-8"; /* c */ @layer a, b; @import "x.css";` entonces 1 import.
- Dado `a{} @import "x.css";` entonces 0 (el import llega tarde).
- Dado un import sin `;` final, con url vacía, o con `{`, `}` o `;` dentro de una condición,
  entonces ese import se ignora (fail-closed) y el escaneo continúa tras su `;` (o termina).
- Dado una url, condición o capa de más de `CI_URL_MAX` / `CI_COND_MAX` bytes, entonces se ignora.
- Dado `css == NULL`, `out == NULL` o `cap == 0`, entonces 0.

## Rebase de `url()` contra la hoja (`ci_rebase_urls`)

CSS Values 4 §4.5.1: un `url()` relativo se resuelve contra la URL de la **hoja** que lo contiene,
no contra la página. El worker concatena todas las hojas en un solo texto y el resolvedor de
imágenes (`render_doc`) solo conoce la página, así que `/css/main.css` con
`url(../img/bg.png)` pedía `/img/bg.png` relativo al documento y no a la hoja. Antes de unir
cada hoja externa (`<link>` o `@import`) al texto, el worker reescribe sus `url()` relativos a
absolutos contra la URL de esa hoja. Pura: el llamador da el resolvedor (el mismo de los
módulos) y un sumidero de salida; el módulo no aloca.

- Solo el token `url(` (sin distinguir mayúsculas) precedido de un carácter que no es de
  identificador; nunca dentro de comentarios ni de cadenas (`content:"url(x)"` no se toca).
- Se deja intacto (byte a byte): `url(#frag)` (referencia SVG local), un valor con esquema
  (`data:`, `https:`), vacío, con `\` (escape), sin `)` de cierre, o cuyo resultado no
  resuelve o supera `CI_URL_MAX`. Fallar acá es el comportamiento de antes, nunca una URL rota.
- La salida es `url("ABS")`; una comilla doble o un salto de línea en el resultado ⇒ intacto.
- Sin red: el rebase solo cambia QUÉ texto ve el parser; la URL sigue pasando por el mismo
  gate de imágenes (`caps.images`, rastreadores, confinamiento `file://`).

Dado-Cuando-Entonces:
- Dado `a{background:url(../i/b.png)}` con base `https://h/css/m.css`, entonces
  `a{background:url("https://h/i/b.png")}`.
- Dado `url('x.svg#ic')` con la misma base, entonces `url("https://h/css/x.svg#ic")`.
- Dado `mask:url(#m)`, `url(data:image/png;base64,AA)` o `url(https://o/x)`, entonces intactos.
- Dado `/* url(a) */ b{content:"url(a)"}`, entonces intacto.
- Dado `xurl(a)` (identificador más largo), entonces intacto.
- Dado un `url(a` sin cierre, entonces intacto hasta el final.
- Dado `url(x}y)` o `url(x/*y)` sin comillas, entonces intacto: la llave o el `/*` es estructura
  para todo lector que no conoce el token url (`ci_balanced`, el envoltorio del gate); meterlo en
  una cadena cambiaría lo que ven (hallado por `fuzz-ci`).
- Dado un resolvedor que falla, entonces intacto.

## Cotas (llamador, `tab.c`)

- Profundidad de anidamiento ≤ `CI_MAX_DEPTH` (4): corta ciclos `a → b → a`.
- ≤ `CI_MAX_PER_PAGE` (64) imports seguidos por carga; el resto se descarta con aviso en Freebug.
- El texto expandido cuenta contra el mismo tope `TAB_MAX_EXTERN_CSS` que los `<link>`; una hoja
  que no cabe se descarta ENTERA, nunca truncada.
- Respuesta no 2xx o `Content-Type` no CSS ⇒ el import se descarta (como un `<link>`).
- Los imports de un `<style>` inline se resuelven contra la URL de la página y se anteponen al
  texto externo.

## Fuera de alcance

- Hojas importadas en hosts sin `caps.css`: no se descargan, como cualquier hoja externa.
