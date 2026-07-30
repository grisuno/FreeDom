# spec/svg_render.md — SVG en línea (`sv_`)

> **Estado:** Hito SVG-1 (2026-07-30). Módulo puro `svg_render` (`sv_`) + pintor Cairo
> `svg_paint` (`svp_`). Cubre `<svg>` **en línea** dentro del HTML.
> **Fuera de alcance v1:** `<image>`, `<use>`, `<foreignObject>`, `<script>`, `<style>`,
> animación (`<animate>`), gradientes/patrones (`<defs>`), filtros, máscaras, `.svg` como
> `<img src>` (recurso externo), `preserveAspectRatio` distinto de "meet" centrado.

---

## 1. Por qué existe

La web moderna dibuja sus íconos, logos y gráficos con `<svg>` en línea. Sin soporte, cada
uno de ellos desaparece: Freedom pintaba la página **sin** los íconos y, peor, dejaba
escapar el texto de `<text>` al flujo del documento como si fuera prosa.

**El SVG es contenido, no un recurso de red.** La gramática aceptada aquí **no tiene forma
de URL**: no hay `<image href>`, no hay `<use xlink:href>`, no hay `url()`. Un `<svg>` no
puede, estructuralmente, abrir un socket ni filtrar nada — por eso se renderiza **siempre**,
sin depender del toggle de imágenes (que existe porque una `<img>` **sí** hace fetch).

---

## 2. Frontera de confianza

El marcado SVG es **contenido remoto hostil**. Se procesa igual que el CSS de autor:

- **`svg_render` es puro**: sin I/O, sin red, sin FS, sin estado global mutable. Entra un
  buffer de bytes, sale una lista **acotada** de figuras geométricas. Se fuzzea
  (`make fuzz-svg`).
- **`svg_paint`** solo traduce esa lista a llamadas Cairo, del lado confiable, igual que el
  pintor ya dibuja cajas y gradientes de autor.
- Todo tope es fijo y se **falla cerrado**: pasado el límite, la figura se descarta; nunca
  se asigna memoria proporcional a lo que pida el atacante.

| Tope | Valor | Qué protege |
| :-- | :-- | :-- |
| `SV_MAX_SHAPES` | 512 | figuras por imagen |
| `SV_MAX_POINTS` | 4096 | pool de puntos (polígonos/polilíneas) |
| `SV_MAX_SEGS` | 4096 | pool de segmentos de `<path>` |
| `SV_MAX_DEPTH` | 32 | anidamiento de `<g>` |
| `SV_TEXT_MAX` | 128 | bytes de un `<text>` |
| `SV_MAX_INPUT` | 1 MiB | marcado de entrada |

---

## 3. Contrato (Dado-Cuando-Entonces)

**Dado** un buffer con marcado `<svg>…</svg>`, **cuando** se llama `sv_parse(markup, len, out)`,
**entonces** `out` queda con las figuras reconocidas en orden de documento y se devuelve
`SV_OK`; si no hay ninguna figura reconocible se devuelve `SV_ERR_PARSE` y `out` queda
vacío (nunca a medio llenar).

- **Dado** `viewBox="0 0 24 24"` y `width="64"`, **cuando** se pinta en un rect de 64×64,
  **entonces** las coordenadas del usuario se escalan por 64/24 y se centran (`meet`).
- **Dado** un atributo malformado (`width="abc"`, `d="M Q"`, color inválido),
  **cuando** se parsea, **entonces** ese atributo se ignora con su valor por defecto y el
  resto de la figura sigue siendo válida (**fail-open a lo geométrico, nunca a lo remoto**).
- **Dado** un elemento desconocido (`<image>`, `<use>`, `<script>`, `<style>`),
  **cuando** se parsea, **entonces** se **descarta junto con su contenido**: cero figuras,
  cero red.
- **Dado** `fill="currentColor"`, **cuando** se pinta, **entonces** se usa el color de texto
  heredado que el llamador pasa a `svp_draw` (así un ícono monocromo toma el color del texto).
- **Dado** un `<svg>` sin `width`/`height` pero con `viewBox`, **entonces** las dimensiones
  intrínsecas son las del `viewBox`; sin ninguno de los dos, `SV_DEFAULT_SIZE` (300×150,
  el default de CSS).

### Elementos soportados

`<svg>` (width/height/viewBox), `<g>` (transform + herencia de presentación), `<rect>`
(x/y/width/height/rx/ry), `<circle>` (cx/cy/r), `<ellipse>` (cx/cy/rx/ry), `<line>`
(x1/y1/x2/y2), `<polyline>`/`<polygon>` (points), `<path>` (d), `<text>` (x/y/font-size,
contenido literal acotado).

### Atributos de presentación

`fill`, `stroke`, `stroke-width`, `stroke-linecap`, `stroke-linejoin`, `opacity`,
`fill-opacity`, `stroke-opacity`, `fill-rule`, `transform`, y los mismos vía `style="…"`.
Los colores se resuelven con `css_color` (`cc_parse`) — una sola fuente de verdad de
"qué es un color" en todo el proyecto. `fill` por defecto es negro; `stroke` por defecto
es `none` (regla SVG).

### `transform`

`translate(tx[,ty])`, `scale(sx[,sy])`, `rotate(deg[,cx,cy])`, `skewX(deg)`, `skewY(deg)`,
`matrix(a,b,c,d,e,f)`. Se componen a lo largo de la cadena de `<g>` y se aplanan a una
matriz afín por figura, igual que hace `compositor` con `transform` de CSS.

### Comandos de `<path>`

`M m L l H h V v C c S s Q q T t A a Z z`. Q/T se convierten a cúbicas; los arcos `A/a` se
aproximan con cúbicas (parametrización por centro). Un comando desconocido **termina** el
path con lo acumulado hasta ahí (fail-closed, sin adivinar).

---

## 4. Integración en el pipeline

```
DOM (<svg> inerte)
  └─ page_view: serializa el subárbol → run PV_SVG (marcado en `text`, dims en img_w/img_h)
       y SALTA el subárbol en el recorrido de texto (su <text> no es prosa de la página)
  └─ tab.c: el marcado viaja por el campo `text` que ya existe (cero campos IPC nuevos)
  └─ render_doc: PV_SVG → RD_SVG, sin gate (no hay red que gatear)
  └─ browser_ui: fila RC_SVG; sv_parse (puro) + svp_draw (Cairo)
```

El parseo ocurre del **lado confiable**, igual que `css_parse`: es una función pura,
acotada y fuzzeada sobre bytes hostiles. La alternativa (parsear en el worker y serializar
las figuras) exigiría un array de longitud variable nuevo en el códec IPC sin ganar ninguna
garantía: el marcado ya cruza el pipe como dato inerte.

---

## 5. Errores

| Código | Cuándo |
| :-- | :-- |
| `SV_OK` | se reconoció al menos una figura |
| `SV_ERR_NULL_ARG` | puntero requerido nulo |
| `SV_ERR_PARSE` | no hay `<svg>` o no hay ninguna figura reconocible |
| `SV_ERR_LIMIT` | la entrada supera `SV_MAX_INPUT` |

`sv_image` es una estructura **grande** (pools fijos): se asigna en heap (`calloc`), nunca
en la pila. `sv_parse` la deja completamente inicializada antes de escribir.
