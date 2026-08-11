# spec/box_style.md — Box model por etiqueta (hoja de estilo del agente de usuario)

> Módulo `box_style` (prefijo `bx_`). Lógica **pura, sin I/O, sin estado global, sin asignación
> dinámica**: dada una etiqueta HTML (y, opcionalmente, un token `display` del autor), devuelve el
> **box model por defecto** (márgenes y padding) y el **tipo de `display`** del elemento. No mide
> texto, no pinta, no resuelve geometría: solo clasifica. Metodología: SDD + TDD. Hito 7.

## 0. Por qué existe

El layout necesita saber, por cada elemento del documento, cuánto margen y padding lo separan de sus
vecinos y de qué tipo es (bloque que apila verticalmente, en línea que fluye con el texto, contenedor
flex/grid, o nada). Esa decisión es **reglas, no píxeles**: es lógica pura, auditable sin Cairo ni
red, y debe vivir en un solo sitio probado en vez de estar dispersa en el pintor con números mágicos.

`box_style` es la **hoja de estilo del agente de usuario** (UA) de Freedom: el subconjunto de las
reglas por defecto de CSS 2.1 que el motor aplica **siempre** (no son estilos del autor, así que no
están sujetas al gate de privacidad `caps.css`). El parser de `display` del autor (`bx_parse_display`)
es aparte: `box_style` solo decodifica el token; **el llamante decide si aplicarlo** según `caps.css`
(Privacy/Secure by Default: un documento no reconfigura el motor a menos que el usuario lo permita).

Es además la base de `flex_layout`: una vez que un elemento se clasifica como `BX_DISPLAY_FLEX` o
`BX_DISPLAY_GRID`, el solver geométrico toma el relevo.

## 1. Unidades

Los márgenes y el padding se expresan en **em** (múltiplos del tamaño de fuente del propio elemento),
como `double`. Es la unidad nativa de la hoja UA de CSS y es **independiente de la resolución**: el
orquestador (la GUI) multiplica por el tamaño de fuente de cada bloque para obtener píxeles. Así un
`h1` (fuente grande) recibe automáticamente más margen físico que un `p` con el mismo `1em`.

## 2. Tipos

```c
typedef enum bx_display {
    BX_DISPLAY_BLOCK = 0,     /* apila verticalmente, ocupa el ancho disponible */
    BX_DISPLAY_INLINE,        /* fluye con el texto; márgenes verticales ignorados por el layout */
    BX_DISPLAY_INLINE_BLOCK,  /* caja en línea con dimensiones propias (img, input, button) */
    BX_DISPLAY_LIST_ITEM,     /* como bloque, pero el layout dibuja un marcador (li) */
    BX_DISPLAY_FLEX,          /* contenedor flex: lo resuelve flex_layout */
    BX_DISPLAY_GRID,          /* contenedor grid: lo resuelve flex_layout */
    BX_DISPLAY_NONE           /* no se renderiza ni ocupa espacio (head, script, style...) */
} bx_display;

/* Bordes de la caja en em (múltiplos del tamaño de fuente del elemento). */
typedef struct bx_edges {
    double top, right, bottom, left;
} bx_edges;

typedef struct bx_box {
    bx_display display;
    bx_edges   margin;
    bx_edges   padding;
} bx_box;

typedef enum bx_status {
    BX_OK = 0,
    BX_ERR_NULL_ARG,  /* token u out era NULL */
    BX_ERR_SYNTAX     /* el token no es una palabra clave de display reconocida */
} bx_status;

/* Ubicación horizontal de una caja del autor dentro del ancho disponible. */
typedef struct bx_hplace {
    double x_off;      /* desplazamiento desde el borde izquierdo del área de contenido */
    double content_w;  /* ancho disponible para el contenido en línea del bloque */
} bx_hplace;
```

## 3. API (pura, reentrante)

```c
bx_box     bx_default_for_tag(const char *tag);
bx_status  bx_parse_display(const char *token, bx_display *out);
const char *bx_display_name(bx_display d);
bx_hplace  bx_place(double inset_l, double inset_r, double width_cap, int center,
                    double avail_w);
double     bx_width_cap(int w_px, int w_pct, double avail_w);
double     bx_content_cap(double width_cap, int border_box,
                          double pad_l, double pad_r, double bord_l, double bord_r);
```

### `bx_content_cap` (2026-07-11 — `box-sizing: border-box`)

Ajusta el tope de ancho al modelo de caja declarado, ANTES de `bx_place` (que interpreta
el tope como ancho de **contenido**):

- **Dado** `border_box == 0` (content-box o unset) o `width_cap <= 0` (sin tope),
  **entonces** identidad: devuelve `width_cap` sin tocar.
- **Dado** `border_box != 0` y un tope, **entonces** devuelve
  `width_cap − pad_l − pad_r − bord_l − bord_r` acotado a `>= 1` (un border-box más
  angosto que sus propios bordes no colapsa a ancho negativo).
- Bordes/padding negativos se tratan como 0 (defensivo).
Pura, sin I/O; consumida por `open_box` en el painter — el único sitio que necesita el
ajuste, porque sin padding/border declarados los dos modelos coinciden y el box-def
existe exactamente cuando se declaran.

### `bx_width_cap` (Hito 32 — anchos porcentuales)

Resuelve el tope de ancho efectivo de una caja combinando el tope en px (`box_w`, `0` =
ninguno) con el tope porcentual (`box_w_pct`, por-mille del contenedor, `0` = ninguno)
contra el ancho disponible real, que recién se conoce en layout:

- **Dado** solo `w_px > 0`, **entonces** devuelve `w_px`.
- **Dado** solo `w_pct > 0`, **entonces** devuelve `avail_w * w_pct / 1000`
  (`998` ⇒ 99.8% del contenedor).
- **Dado** ambos, **entonces** devuelve el **menor** (el tope más estricto gana, igual
  que la regla px de `css_hbox_resolve`).
- **Dado** ninguno (o `avail_w <= 0`), **entonces** `0` (= sin tope). Nunca negativo.
Pura, sin I/O; consumida por el painter (banda de floats y flujo normal) y por
`layout_float_band` para el ancho de cada ítem flotado.

### `bx_default_for_tag`
- Busca, **sin distinguir mayúsculas/minúsculas**, la etiqueta en la tabla UA ordenada (búsqueda
  binaria; dato de referencia, no índices mágicos).
- `tag == NULL`, vacío, o desconocido → **caja en línea neutra**: `BX_DISPLAY_INLINE`, márgenes y
  padding a cero. Es el valor por defecto seguro: un elemento que no conocemos no inventa espaciado.
- Devuelve por valor (sin asignación). El `body` tiene margen **cero**: el gutter de la página lo
  aporta el chrome de la ventana (`content_margin`), así no hay doble margen.

Subconjunto cubierto (defaults de la hoja UA de CSS 2.1):

| Etiqueta(s) | display | margen (em) | padding (em) |
| :-- | :-- | :-- | :-- |
| `body` | block | 0 | 0 |
| `div` `section` `article` `header` `footer` `nav` `main` `aside` `figure` | block | 0 | 0 |
| `p` | block | 1.0 arriba/abajo | 0 |
| `h1` | block | 0.67 arriba/abajo | 0 |
| `h2` | block | 0.83 arriba/abajo | 0 |
| `h3` | block | 1.0 arriba/abajo | 0 |
| `h4` | block | 1.33 arriba/abajo | 0 |
| `h5` | block | 1.67 arriba/abajo | 0 |
| `h6` | block | 2.33 arriba/abajo | 0 |
| `ul` `ol` | block | 1.0 arriba/abajo | 2.5 izquierda |
| `li` | list-item | 0 | 0 |
| `blockquote` | block | 1.0 arriba/abajo, 2.5 izquierda/derecha | 0 |
| `pre` | block | 1.0 arriba/abajo | 0 |
| `hr` | block | 0.5 arriba/abajo | 0 |
| `span` `a` `b` `i` `em` `strong` `code` `small` `label` `sub` `sup` | inline | 0 | 0 |
| `img` `input` `button` `select` `textarea` | inline-block | 0 | 0 |
| `head` `script` `style` `title` `meta` `link` `base` | none | 0 | 0 |

### `bx_parse_display`
- `token == NULL` u `out == NULL` → `BX_ERR_NULL_ARG`.
- Recorta espacios ASCII sobre una copia acotada; un token que no quepa → `BX_ERR_SYNTAX` (out
  intacto).
- Reconoce, **sin distinguir mayúsculas/minúsculas**: `none`, `block`, `inline`, `inline-block`,
  `list-item`, `flex`, `inline-flex`, `grid`, `inline-grid`. Las variantes de nivel en línea
  (`inline-flex`/`inline-grid`) se mapean a `BX_DISPLAY_FLEX`/`BX_DISPLAY_GRID` (el motor básico no
  distingue el nivel del contenedor).
- Cualquier otra cosa (`table`, `contents`, `flow-root`, `var(...)`, basura) → `BX_ERR_SYNTAX`. El
  llamante mantiene el `display` por defecto de la etiqueta.
- En `BX_OK`, `*out` queda poblado; en error, `*out` no se toca.

### `bx_display_name`
- Nombre en inglés, corto y estable, del tipo de display (`"block"`, `"flex"`, ...), para salida
  estructurada/agente. Nunca `NULL`; un valor de enum desconocido → `"inline"`.

### `bx_place` (geometría del box model del autor, Hito 23b-3)
Resuelve la **ubicación horizontal** de un bloque con caja de autor dentro de `avail_w`. Es la única
pieza de geometría que vive en `box_style`, porque es **aritmética pura del box model** (no mide texto
ni pinta); el layout completo sigue en `flex_layout`/el pintor. `page_view` ya pre-resuelve los `px`
del autor; esta función solo decide dónde empieza el contenido y cuán ancho es.

- `inset_l` / `inset_r`: insets izquierdo/derecho en px (`padding` + `margin` no-`auto` de ese lado).
  Negativos se tratan como 0 (falla cerrado).
- `width_cap`: tope de ancho de contenido en px (`min(width, max-width)` ya resuelto por `page_view`),
  o `0` = sin tope.
- `center`: 1 cuando `margin-left` y `margin-right` son ambos `auto` y hay `width_cap` (`margin: 0 auto`).
- `avail_w`: ancho disponible (px); valores < 1 se elevan a 1.

Reglas (deterministas, sin asignación):
- `inner = max(1, avail_w − inset_l − inset_r)`.
- `content_w = (width_cap > 0 && width_cap < inner) ? width_cap : inner` (un tope mayor que el
  disponible no ensancha — `max-width` nunca desborda).
- `x_off = center && width_cap > 0 ? inset_l + (inner − content_w)/2 : inset_l`.
- Garantía: `content_w >= 1` y `x_off >= 0` siempre. Sin caja del autor (`inset_l=inset_r=0`,
  `width_cap=0`) ⇒ `x_off=0`, `content_w=avail_w`: comportamiento idéntico al previo (cero regresión).

## 4. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; la etiqueta y el token son dato
  hostil con procedencia.
- **Determinista:** misma entrada → misma salida (testeable, agent-friendly).
- **Falla cerrado / seguro por defecto:** etiqueta desconocida → caja inerte en línea sin espaciado;
  `display` no reconocido → `BX_ERR_SYNTAX` (no se reconfigura el motor).
- **Sin asignación dinámica:** opera sobre buffers de pila acotados y devuelve por valor.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 4b. Métricas UA del tema (2026-07-31)

`box_style` da los márgenes **en em**; quien los convierte a píxeles es el tema de la GUI
(`gui/bui_theme.c`), que es también la fuente única del **tamaño base** y de la escala de
títulos. Esos números son parte de la hoja UA aunque vivan en el pintor, así que su
contrato está aquí.

| Métrica | Valor | Por qué |
| :-- | :-- | :-- |
| `body_font` (`UI_FONT_SIZE`) | **16.0 px** | Es el tamaño base de la web y, sobre todo, **el mismo root contra el que `css.c` resuelve `px`/`rem`**. Estaba en 14: todo el texto salía un 12 % más chico que en Firefox y, peor, un `font-size:40px` absoluto aterrizaba en `250 % × 14 = 35px`. Un solo número gobierna los dos lados o vuelven a divergir. |
| `heading_scale[1..6]` | **2.0, 1.5, 1.17, 1.0, 0.83, 0.67** | Los múltiplos de CSS 2.1 §App.D / HTML. Estaban en 2.0/1.6/1.35/1.2/1.1/1.05: un `<h4>` se pintaba 1.2× cuando debe ser exactamente el tamaño del cuerpo. |
| `line_spacing` | **1.0** | `line-height: normal` **ES** la caja de línea natural de la fuente: `ascent + descent` tal como la reporta Cairo/FreeType, sin factor extra. Medido contra Firefox en este host: una línea de 16 px mide **23 px** en ambos motores cuando el multiplicador es 1.0. Estaba en 1.2 (y antes en 1.3), y ese 1.2 se aplicaba **encima** de una caja que ya era la correcta ⇒ toda página sin `line-height` de autor salía un 20 % más alta. §4c. |
| `heading` (color) | **igual que `text`** | En CSS `color` **hereda**; la hoja UA no le da color propio a un `<h1>`. El tema pintaba los títulos en azul marino, así que toda página sin `color` de autor salía bicolor donde Firefox la pinta negra. El campo se conserva por tema (oscuro/sepia siguen tiñendo texto y títulos juntos). |

**Dado** un documento sin CSS de autor **cuando** se pinta **entonces** el cuerpo mide 16 px,
un `<h1>` 32 px y un `<h4>` 16 px, y ningún título toma un color que el documento no pidió.

`zoom` sigue escalando `body_font`, así que un `font-size` absoluto escala con el zoom
(que es lo que hace un navegador real).

## 4c. `line-height: normal` es la caja natural, no un múltiplo de ella (2026-08-10)

El pintor calcula el alto de línea como `(line_asc + line_desc) * spacing`, donde
`line_asc`/`line_desc` son las métricas **escaladas de la fuente**. Esa suma ya **es** la
caja de línea que CSS llama `normal`; multiplicarla otra vez es inventar interlineado.

**Dado** un `<div>` de `font-size: 16px` sin `line-height` de autor
**cuando** se calcula su caja de línea
**entonces** mide `ascent + descent` px (23 px con las fuentes de este host), el mismo
número que reporta Firefox — **y no** `1.2 x` esa cantidad.

- El multiplicador **solo** deja de ser 1.0 cuando el autor declara `line-height` (llega como
  `line_scale`, un porcentaje) o cuando un tema lo pide explícitamente.
- La regla del máximo por fragmento (CSS 2.1 §10.8) no cambia: la línea toma el mayor
  interlineado de sus fragmentos.
- **Por qué importa más de lo que parece:** es un factor multiplicativo sobre **cada línea de
  cada página**, así que se compone con cualquier otra brecha vertical. Medido en
  `make parity`: −23.03 puntos de una sola constante.

## 4d. El margen UA sale de la etiqueta real, no de una conjetura (2026-08-10)

La hoja UA de HTML le da margen vertical a **muy pocos** elementos: `p`, `h1`–`h6`, `ul`,
`ol`, `menu`, `dl`, `pre`, `blockquote`, `figure`, `hr`. Todo lo demás —`div`, `section`,
`header`, `article`, `footer`, `nav`, `main`, `td`, `tr`, `table`, `form`— tiene margen
**cero**. Un navegador que le da a un `<div>` el `1em` de un `<p>` inserta una línea en
blanco fantasma antes de **cada** bloque de la página.

**Dado** un `<div>` sin `margin` de autor **cuando** se resuelve su caja UA
**entonces** su margen vertical es **0**; **y dado** un `<p>` en la misma página
**entonces** el suyo sigue siendo `1em`.

El bloque no puede adivinar su etiqueta desde `rd_kind` (todo texto de cuerpo es
`RD_PARAGRAPH`), así que la etiqueta viaja: `bx_ua_tag` es un código chico y estable que
`page_view` resuelve del ancestro de nivel de bloque y que cruza el códec IPC como un
`int32` más. Es **estructura**, no estilo de autor — un margen UA no abre sockets ni
depende de `caps.css`, exactamente igual que el resto del box model UA
(`CLAUDE.md` §7.2 "Layout != estilo de autor").

`bx_ua_of_tag` / `bx_default_for_ua` son puras y comparten la **misma** `TAG_TABLE` que
`bx_default_for_tag`: una sola fuente de verdad para la hoja UA.

## 4e. El `line-height` del autor es múltiplo del `font-size`, no de la caja natural (2026-08-10)

CSS 2.1 §10.8.1: `line-height: 1.4` significa **1.4 × el `font-size` del fragmento**. La
caja de línea natural (`ascent + descent`) es **otra cosa**: en este host mide ≈ **1.44 ×**
el `font-size`. Son dos unidades distintas y el pintor las estaba mezclando —aplicaba el
factor del autor sobre la caja natural—, así que **todo** `line-height` de autor salía
≈ 1.44× de más.

**Dado** un fragmento de `font-size: 13px` con `line-height: 1.4`
**cuando** se cierra su línea
**entonces** aporta `13 × 1.4 = 18.2 px` de interlineado — **no** `(asc+desc) × 1.4 ≈ 26 px`.

- El acumulador por línea (`line_lead_px`) guarda **píxeles**, no un factor: es el único
  lugar donde las dos contribuciones son comparables. Se calcula en `flow_emit_frag`, que
  es donde se conoce el `font-size` del fragmento.
- La regla del máximo (§10.8) se mantiene: la línea toma el fragmento **más alto**. Un
  fragmento sin `line-height` de autor aporta la caja natural × `line_spacing`.
- Una línea sin ningún fragmento (bloque vacío que abre línea) cae al interlineado del
  bloque, y si tampoco lo hay, al del tema. Nunca queda en cero.
- **Por qué importa:** es el complemento de §4c. Una página **sin** `line-height` de autor
  la arregla §4c; una página **con** `line-height` (todo buscador, todo portal moderno) solo
  la arregla esto. Medido en `make parity`: −25.32 puntos, con `slashdot` pasando de
  `h_ratio` 1.27 a **1.04**.

## 5. Tabla de estados (`bx_parse_display`)

| `bx_status` | Condición |
| :-- | :-- |
| `BX_OK` | Token reconocido; `*out` es el `bx_display`. |
| `BX_ERR_NULL_ARG` | `token` u `out` es `NULL`. |
| `BX_ERR_SYNTAX` | Vacío, no cabe, o palabra clave no soportada. |

## 6. Fuera de alcance

- Resolver geometría de layout (line-boxes, packing flex/grid, posiciones verticales): eso es
  `flex_layout` y el pintor. La **excepción** es `bx_place`: la ubicación horizontal de UNA caja de
  autor (inset/cap/centrado) es aritmética pura del box model y vive aquí; el resto del layout no.
- `height`/`border`/`box-sizing`/`flex`/`grid-template` del autor: los consume `flex_layout`; aquí
  solo se clasifica el `display` y se ubica horizontalmente una caja ya resuelta a px (`bx_place`).
- Herencia y cascada CSS, selectores, especificidad: el motor aplica la hoja UA por etiqueta y, a lo
  sumo, un `display` en línea gateado por el llamante.
- `table`/`table-*`, `ruby`, `contents`, `flow-root` y demás valores de `display` raros.
- Extraer el token desde el atributo `style`/la hoja del autor: lo hace `page_view`/`render_doc`.
