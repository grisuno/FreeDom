# Especificación: `page_view`

> Puente Hito 5→6 (renderizado de HTML). Estado: **VERDE** (núcleo puro). Metodología: SDD + TDD.
> Esta spec es el contrato; `tests/test_page_view.c` lo cubre parseando HTML real con `html_parse`
> y verificando la display list resultante.

## 1. Propósito

`page_view` convierte el DOM inerte y saneado (`html_parse`) en una **display list** plana: una
lista ordenada de *runs* en línea con la estructura mínima para maquetar y pintar una página
legible — texto, **enlaces**, **imágenes**, nivel de **encabezado** y **saltos de bloque**.

Una imagen es **dato con procedencia, nunca petición**: el `src` se guarda pero **no se descarga
aquí**. La decisión de cargarla (o no) la toma `render_policy`/el orquestador; `page_view` solo la
hace visible y aporta sus dimensiones declaradas para la heurística de píxel de rastreo.

Es el dato que el worker `tab` entrega a la GUI. El renderer **no** recorre el DOM hostil ni el
texto plano sin estructura; consume esta lista. Cada run es **dato con procedencia, nunca
instrucción**: el `href` de un enlace se guarda pero **no se sigue aquí**; la navegación lo
re-valida por `secure_fetch`.

## 2. Modelo de datos

```c
typedef enum { PV_TEXT, PV_LINK, PV_IMAGE } pv_kind;

typedef struct pv_run {
    pv_kind kind;        /* texto, enlace o imagen */
    int     heading;     /* 0 = cuerpo; 1..6 = dentro de h1..h6 */
    int     block_break; /* !=0: un límite de bloque precede a este run */
    char   *text;        /* propio, NUL-terminado, UTF-8 válido (alt en PV_IMAGE) */
    char   *href;        /* propio (PV_LINK), NUL-terminado; si no, NULL */
    char   *src;         /* propio (PV_IMAGE): URL de la imagen; si no, NULL */
    int     img_w;       /* ancho declarado del <img> (px), o -1 si desconocido */
    int     img_h;       /* alto declarado del <img> (px), o -1 si desconocido */
    int     fg_rgb;      /* color del autor empaquetado 0xRRGGBB, o -1 si no hay */
    int     bg_rgb;      /* background-color del autor 0xRRGGBB, o -1 si no hay */
    int     text_align;  /* text-align del autor (css_align), 0 = sin definir */
    int     font_scale;  /* font-size del autor en porcentaje (100=normal), 0 = sin definir */
    int     line_scale;  /* line-height del autor en % de la caja de línea, 0 = sin definir */
    int     text_decoration; /* text-decoration del autor (OR de CSS_DECO_*; 0=none, -1=sin definir) */
    /* Extensiones de presentación de texto del autor (Hito 23b-6), gateadas por caps.css. */
    int     font_family;     /* css_font_family, 0 sin definir */
    int     text_transform;  /* css_text_transform, 0 sin definir */
    int     letter_spacing;  /* px con signo, PV_LEN_UNSET sin definir */
    int     word_spacing;    /* px con signo, PV_LEN_UNSET sin definir */
    int     shadow_dx, shadow_dy; /* offsets de text-shadow px */
    int     shadow_color;    /* 0xRRGGBB, o -1 (sin sombra) */
    int     opacity;         /* 0..100, o -1 (sin definir) */
    int     valign;          /* css_valign, 0 sin definir */
    int     text_indent;     /* px con signo (sangría 1ª línea), PV_LEN_UNSET sin definir */
    int     white_space;     /* css_white_space, 0 sin definir */
    int     cont_id;     /* contenedor flex/grid de autor mas cercano, o -1 */
    int     cont_display;/* bx_display del contenedor (flex/grid), o 0 */
    int     cont_gap;    /* gap del contenedor en px */
    int     cont_justify;/* fx_justify del contenedor */
    int     cont_cols;   /* columnas del grid, o 0 */
    int     cont_item;   /* ordinal del ITEM (hijo directo del contenedor) al que
                          * pertenece el run dentro de su contenedor, o -1. Runs
                          * consecutivos con el mismo (cont_id, cont_item) son
                          * fragmentos del MISMO item (fluyen juntos en una celda). */
    /* Flex por-item (Stage 3): del css_style del ITEM (el hijo directo del contenedor
     * en la cadena de ancestros del run) + la direccion del contenedor. Estructura,
     * como cont_* (render_doc los propaga siempre). */
    int     flex_grow;      /* x100 (1.0 -> 100), o -1 (sin definir -> CSS 0) */
    int     flex_shrink;    /* x100, o -1 (sin definir -> CSS 1.0) */
    int     flex_basis;     /* px >= 0, CSS_LEN_AUTO, o CSS_LEN_UNSET (-> auto) */
    int     flex_order;     /* con signo, o CSS_LEN_UNSET (-> 0) */
    int     flex_direction; /* css_flex_direction del CONTENEDOR, 0 (-> row) */
    /* Box model del autor pre-resuelto a px (Hito 23b-3), gateado por caps.css. */
    int     box_l;       /* inset izquierdo px (padding-left + margin-left no-auto), 0 */
    int     box_r;       /* inset derecho px (padding-right + margin-right no-auto), 0 */
    int     box_w;       /* tope de ancho de contenido px (min width/max-width), 0 = sin tope */
    int     box_center;  /* 1: margin: 0 auto (centrar dentro del ancho disponible) */
    int     box_mt;      /* override de margen superior px, o PV_LEN_UNSET (usa el UA) */
    int     box_mb;      /* override de margen inferior px, o PV_LEN_UNSET (usa el UA) */
} pv_run;

typedef struct pv_view { pv_run *runs; size_t count; size_t cap; } pv_view;
```

En un run que no es imagen, `src == NULL` y `img_w == img_h == -1`. En un `PV_IMAGE`, `text` es el
texto alternativo (`alt`, puede ser cadena vacía) y `href == NULL` (la imagen no es un enlace).

**CSS de autor (Hito 23) — `<style>` + `style=` en línea.** La presentación del autor ya no sale solo
del `style` en línea: `pv_build_full` concatena los bloques `<style>` del documento (head incluido,
acotado a 1 MiB) y los parsea **una vez** con el módulo puro `[[css]]` en una hoja acotada. Por cada
ancestro de un run se calcula su `css_style` (reglas de la hoja + su propio `style=`, ganando el
inline; `[[css]]` hace la cascada por especificidad y orden), y se fusionan los campos heredables
desde el ancestro más cercano. El cálculo por elemento usa **`css_resolve_el`**: `cch_element_style` (módulo `css_chain`, extraído de page_view por anti-monolito)
arma la **cadena de ancestros** del elemento (`fill_css_node` extrae tag/id/clases/atributos por
nivel, acotada a 32 → fail-closed) y se la pasa al módulo, de modo que los **combinadores
descendiente (`A B`) e hijo (`A > B`)** resuelven sobre el DOM real. Desde el **Hito 23b-9** la
cadena lleva además el **contexto de hermanos**: `sibling_position` calcula `nth`/`nsib` (índice
1-based entre hermanos-elemento / total, caminata acotada por `CCH_NTH_MAX` (1024) → más allá
lee 0 = desconocido, fail-closed) **para cada nodo de la cadena** (así `tr:nth-child(even) td`
restringe a un ancestro), y el **sujeto** recibe su cadena de hermanos previos (`prev`), acotada a
`CCH_SIB_MAX` (16), cada hermano compartiendo el padre del sujeto y derivando su posición —
con eso los **combinadores hermanos `+`/`~`** y las **pseudo-clases estructurales** resuelven
sobre el DOM real (un `+`/`~` en un compuesto no-sujeto falla cerrado: los ancestros no llevan
`prev`). El subconjunto soportado: selectores simples/compuestos (tipo, `.clase`, `#id`, `*`,
grupos por coma) + combinadores descendiente/hijo/**adyacente `+`/general `~`** + selectores de
atributo + el subconjunto de **pseudo-clases** del Hito 23b-9 (`:link`/`:visited`/`:hover`-familia/
`:root`/`:first-child`/`:last-child`/`:only-child`/`:nth-child()`/`:nth-last-child()`/`:checked`/
`:disabled`/`:enabled`; ver `spec/css.md`) y las propiedades `color`, `background[-color]`,
`text-align`, `font-size`, `font-weight`, `font-style`, `display`. **Seguridad:** `[[css]]` descarta
cualquier valor con `url(` y toda `@`-regla, así que el CSS de autor **nunca telefonea a casa** ni abre
una baliza de rastreo; es contenido hostil, por eso se fuzzea (`make fuzz-css`/`fuzz-pv`).

**Color del autor (`fg_rgb`):** sale del ancestro más cercano cuyo `css_style` fije `color` (regla de
`<style>` o `color:` en línea), con el `<font color>` legacy como respaldo cuando ninguna declaración
CSS ganó; `background-color` nunca se confunde con `color`; valor no parseable → -1. Es dato de
presentación: `render_doc` solo lo propaga con `caps.css`, y nunca implica red. Los `pv_append*`
inicializan `fg_rgb` a -1; `pv_set_color` lo fija en el último run.

**Alineación y tamaño del autor (`text_align`/`font_scale`/`line_scale`):** `text_align` es el `text-align`
heredado (un `css_align`: 0 sin definir, 1 izquierda, 2 centro, 3 derecha, 4 justificado); `font_scale` es el
`font-size` en porcentaje (100 = normal; `px` relativo a 16px, `em`/`rem`/`%` y palabras clave), 0 si
no se define; `line_scale` es el `line-height` en % de la caja de línea natural (unitless×100 o `%`; `normal`
o `px`/`em` absolutos → 0). Los tres del ancestro más cercano que los fije. Mismo gate de presentación que los colores
(`render_doc` los propaga solo con `caps.css`); `pv_set_text_style` los fija en el último run.

**Decoración del autor (`text_decoration`):** OR de `CSS_DECO_UNDERLINE`/`CSS_DECO_LINE_THROUGH`/
`CSS_DECO_OVERLINE` resuelto del ancestro más cercano que fije `text-decoration` (incluido `none` → 0,
que p.ej. quita el subrayado de un `<a>`); -1 = sin definir. Presentación gateada por `caps.css` como los
colores; `pv_set_text_style` lo fija en el último run (4º argumento).

**Extensiones de presentación de texto del autor (Hito 23b-6).** Once campos de run más —
`font_family`, `text_transform`, `letter_spacing`, `word_spacing`, `shadow_dx`/`shadow_dy`/
`shadow_color`, `opacity`, `valign`, `text_indent`, `white_space` — resueltos del **ancestro más
cercano** que fije cada uno (heredan en CSS) por `resolve_context` (vía la struct interna `pv_text_ext`
+ `pv_text_ext_merge`) y fijados con el setter dedicado **`pv_set_text_ext`** (no se amplió de nuevo
`pv_set_text_style`). Presentación gateada por `caps.css` como los colores. Defaults sin autor:
`font_family`/`text_transform`/`valign`/`white_space` = 0, `letter_spacing`/`word_spacing`/`text_indent`
= `PV_LEN_UNSET`, `shadow_color`/`opacity` = -1, `shadow_dx`/`shadow_dy` = 0. El `list-style-type`
también se resuelve en la fusión, pero **no es un campo de run**: `list_marker` lo consume para elegir el
glyph/numeración del marcador del `<li>` (disc/circle/square/decimal/alpha/roman; `none` ⇒ sin marcador),
que se hornea en el texto del run — estructura, no gateada.

**`display:none` (estructura).** Un run cuyo elemento o algún ancestro tenga `display:none` (de la hoja
o en línea) **no se emite** (`in_hidden_subtree`). Es visibilidad estructural: se aplica siempre,
independiente de `caps.css` (el contenido oculto sigue oculto, como el caso `display:none` con JS off).
`font-weight`/`font-style` del autor, cuando el ancestro más cercano los fija, ganan al énfasis por
etiqueta (`<b>`/`<em>`); si no, sigue el énfasis por etiqueta.

**Modo sin distracciones (reader).** `pv_build_full(doc, js, reader, prefers_dark, out)` con
`reader != 0` descarta los subárboles de chrome (`<nav>`/`<header>`/`<footer>`/`<aside>`,
`in_boilerplate_subtree`) y emite solo el contenido principal. Determinista, no extracción heurística
de artículo. La hoja de autor se sigue resolviendo; el orquestador decide aplicarla o no (en reader
apaga `caps.css`/imágenes).

**Modo oscuro automático (Hito 23b).** `prefers_dark` se pasa a `css_parse_media` como contexto de
medios: con `prefers_dark != 0`, las reglas del autor bajo `@media (prefers-color-scheme: dark)` se
aplican (`screen`, `min/max-width` contra un ancho normalizado de 1920px, `print` excluido en pantalla).
El worker no conoce el ancho real de la ventana (anti-fingerprint); la GUI deriva `prefers_dark` del
tema oscuro y re-renderiza desde caché al cambiar de tema (con `caps.css` activo).

**Background-color del autor (`bg_rgb`):** se extrae solo del longhand `background-color:` del atributo
`style` (el shorthand `background` y el atributo legacy `bgcolor` quedan fuera de alcance), parseado
por `css_color`. En CSS `background-color` **no hereda**; en este modelo plano se toma del ancestro más
cercano que lo fije, de modo que el fondo de un bloque se ve tras su texto. Mismo gate de presentación
que `fg_rgb` (`render_doc` lo propaga solo con `caps.css`); los `pv_append*` lo inicializan a -1 y
`pv_set_bgcolor` lo fija en el último run.

**Contenedor flex/grid del autor (`cont_*`):** por cada run se busca el ancestro más cercano cuyo
`display` computado sea `flex` o `grid`. Desde el **Hito 23b-2** ese `display` y sus parámetros
(`gap`, `justify-content`, `grid-template-columns`) salen de la **cascada de `[[css]]`** — la misma
`css_style` que ya se resuelve por ancestro (hoja `<style>` + `style=` inline, inline gana) — no de un
parser inline propio (que se eliminó). El número de columnas mapea a `css_justify`→`fx_justify`
(`[[flex_layout]]`). Los runs de un mismo contenedor comparten `cont_id` (registro en orden de
documento, -1 = ninguno); se guardan además su `display`, el `gap` (px), `justify-content` y, en grid,
las columnas de `grid-template-columns` (cuenta de tokens, `[1, PV_MAX_GRID_COLS]`; `repeat()`/
`minmax()` fuera de alcance). Es **estructura, no estilo de autor**: `render_doc` lo propaga **siempre**
(desacoplado de `caps.css`, doctrina "Layout != estilo de autor"); solo los *colores*/`text-align`/
`font-size` de autor quedan gateados por `caps.css`. Los `pv_append*` inicializan `cont_id` a -1;
`pv_set_container` fija los cinco campos en el último run. El `background` shorthand y `bgcolor` legacy
siguen fuera de alcance.

**Whitespace entre bloques (no pinta).** Un run de **solo espacios** que **iniciaría un bloque**
(le tocaría `block_break`) **no se emite**, y el break queda **pendiente** para el siguiente run con
contenido (`pending_break`), que abre el bloque normalmente. Es la regla CSS de cajas anónimas: el
whitespace entre cajas de nivel de bloque no genera caja alguna (y el whitespace al inicio de línea
colapsa). Sin esta regla, cada newline del HTML fuente entre `<div>`s/`<p>`s pintaba una **línea vacía
de ~26px** (en Wikipedia: 412 runs así ⇒ ~11.000px de página en blanco). Un run de solo espacios en
**medio** de un bloque (sin `block_break`: el separador entre dos inlines, `<b>a</b> <i>b</i>`) se
sigue emitiendo — ese espacio es contenido. Caso particular ya existente (Stage 3): el de solo
espacios **hijo directo** del elemento contenedor flex/grid tampoco se emite aunque no lleve break
(CSS: el whitespace entre items no crea items anónimos). El separador inter-celda de las tablas
fluidas no se ve afectado (se emite por otro camino y lleva `cont_id == -1`, sin break).

**Identidad de ítem del contenedor (`cont_item`).** Cada run de un contenedor lleva el **ordinal del
ítem** al que pertenece: el elemento **hijo directo** del contenedor en la cadena de ancestros del run
(el mismo elemento del que salen los `flex_*` por-item). Runs consecutivos del mismo hijo comparten
ordinal — así los **fragmentos inline de un mismo párrafo** (`texto <a>link</a> texto`) forman UN ítem
que fluye junto en una celda, en vez de N ítems de una línea cada uno (el bug del lead de Wikipedia:
"the / free / encyclopedia that / anyone can edit" uno por línea). Texto directamente dentro del
contenedor (ítem anónimo, sin elemento intermedio) recibe un ordinal propio por run. Las **celdas de
tabla recolectadas** reciben un ordinal por celda (cada celda sigue siendo su propio ítem del grid —
sin regresión de tablas de datos). El ordinal es por-contenedor y crece en orden de documento; la
interrupción por un contenedor anidado no rompe la continuidad del ítem del contenedor externo.
Estructura como `cont_*`: `render_doc` lo propaga siempre, sin gate de `caps.css`; default -1.
`pv_set_cont_item` lo fija en el último run.

**Flex por-item (`flex_*`, Stage 3).** Junto al contenedor se capturan los valores flex del **item**:
el elemento de la cadena de ancestros del run visitado inmediatamente **antes** del contenedor (su
hijo directo en ese camino — el flex item CSS real). De su `css_style` ya resuelta salen
`flex_grow`/`flex_shrink` (x100, -1 sin definir), `flex_basis` (px / `CSS_LEN_AUTO` / `CSS_LEN_UNSET`)
y `flex_order` (`CSS_LEN_UNSET` sin definir); `flex_direction` sale del `css_style` del **contenedor**
(0 = sin definir = `row`). Dado que el texto directamente dentro del contenedor (item anónimo) no tiene
elemento intermedio, lleva los defaults. Es **estructura** como `cont_*`: `render_doc` lo propaga
siempre, sin gate de `caps.css`. `pv_set_flex` fija los cinco campos en el último run. Runs del camino
de celdas de tabla (grid sintetizado) llevan los defaults. Fuera de alcance v1: `align-items`/
`align-self`, `flex-wrap`, `row-gap`, `grid-template-rows`, `grid-column/row: span N` (resueltos en
`css_style` por el Hito 23b-7; los consumirá una iteración futura del motor de cajas).

**Box model del autor (`box_*`, Hito 23b-3).** Por cada run se resuelve una caja horizontal del
**ancestro de bloque más cercano que declare alguna propiedad de caja** (`margin`/`padding`/`width`/
`max-width` en la `css_style` ya resuelta por ancestro). Se pre-calculan a px: `box_l`/`box_r` =
`padding` + `margin` no-`auto` de cada lado; `box_w` = `min(width, max-width)` (0 = sin tope);
`box_center` = 1 si `margin-left`/`margin-right` son ambos `auto` con `box_w` (`margin: 0 auto`). El
**override de margen vertical** (`box_mt`/`box_mb`) se toma del **bloque hoja propio** del run (no de
un wrapper externo), por eso un run cuyo bloque hoja no fija márgenes lleva `PV_LEN_UNSET` y la GUI usa
el margen UA. Así el `max-width`/centrado de un wrapper alcanza a todos sus descendientes (comparten el
ancestro), pero su margen vertical no se duplica en cada bloque interno. La geometría horizontal final
(inset/cap/centrado dentro del ancho disponible) la calcula `bx_place` (`[[box_style]]`, puro). Es
**presentación del autor**, gateada por `caps.css` igual que los colores/`text-align`/`font-size`
(`render_doc` la propaga solo con `caps.css`; las cajas de autor pueden encoger el contenido a lo
ilegible, así que Privacy/Secure by Default las mantiene apagadas hasta el opt-in). `pv_set_box` fija
los seis campos en el último run; `pv_append*` los inicializan a 0/`PV_LEN_UNSET`. Fuera de alcance v1:
`padding-top/bottom`, `border`, `box-sizing`, `%`/viewport y la composición de cajas anidadas.

## 3. API

```c
pv_status pv_build(const hp_document *doc, pv_view **out); /* == pv_build_full(doc,0,0,0,out) */
pv_status pv_build_ex(const hp_document *doc, int js_enabled, pv_view **out); /* reader=0, prefers_dark=0 */
pv_status pv_build_full(const hp_document *doc, int js_enabled, int reader,   /* reader: sin distracciones */
                        int prefers_dark, pv_view **out);                     /* prefers_dark: auto dark mode */
pv_view  *pv_new(void);                                    /* vista vacía (deserializador IPC) */
pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    const char *text, const char *href);   /* texto/enlace; copia text/href */
pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src, int w, int h); /* PV_IMAGE */
void          pv_set_color(pv_view *v, int fg_rgb);        /* color del autor del ultimo run */
void          pv_set_bgcolor(pv_view *v, int bg_rgb);      /* background-color del ultimo run */
void          pv_set_text_style(pv_view *v, int text_align, int font_scale, int line_scale, int text_decoration); /* align/font/line-height/decoration del ultimo run */
void          pv_set_container(pv_view *v, int cont_id, int cont_display,
                               int cont_gap, int cont_justify, int cont_cols); /* contenedor */
void          pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                          int flex_order, int flex_direction); /* flex por-item del ultimo run */
void          pv_set_cont_item(pv_view *v, int cont_item);  /* ordinal de item del ultimo run */
void          pv_set_box(pv_view *v, int box_l, int box_r, int box_w,
                         int box_center, int box_mt, int box_mb); /* box model del ultimo run */
void          pv_free(pv_view *v);
size_t        pv_count(const pv_view *v);
const pv_run *pv_at(const pv_view *v, size_t i);
```

Diseño orientado a prueba: el modelo y `pv_append` son puros y testeables directamente;
`pv_build` se ejercita parseando HTML con `html_parse` y comprobando la lista.

## 4. Semántica de `pv_build`

Recorre el subárbol del `<body>` (si no hay, el documento) de forma **iterativa** (sin recursión:
la profundidad la controla el atacante). Para cada **nodo de texto**:

- **Subárboles invisibles**: se ignora el texto cuyo ancestro sea `script`, `style`, `head`,
  `title` o `noscript`.
- **Colapso de espacios**: las secuencias de espacios ASCII (` \t\n\r\f`) se colapsan a un solo
  espacio. Un run que queda vacío se descarta.
- **Enlace**: si el ancestro más cercano es un `<a>` con `href`, el run es `PV_LINK` y lleva ese
  `href`; si no, `PV_TEXT` con `href == NULL`.
- **Encabezado**: `heading` = nivel (1..6) del ancestro `h1..h6` más cercano, o 0.
- **Énfasis inline**: `bold` = 1 si algún ancestro es `<b>/<strong>/<th>`; `italic` = 1 si algún
  ancestro es `<i>/<em>`. Es estructura (peso/inclinación del glifo), se transporta por defecto y
  **no** está gateado por `caps.css`.
- **Texto recolectado nunca incluye fuente no renderizada.** Los tres caminos que aplanan un
  subárbol a texto (`collect_text`: valor de `<textarea>`, etiqueta de `<button>`, celda de
  tabla recolectada) **saltan** el texto bajo un `<style>`/`<script>`/`<head>`/`<title>`
  descendiente. Con JS vivo el parser conserva los nodos `<script>` (`strip_scripts=0`), así
  que sin este guard el markup real de google.com (elementos `<style>` dentro de botones,
  `<script>` dentro de celdas) pintaba CSS/JS crudo como contenido. Candado:
  `test_build_collected_text_skips_style_and_script`.
- **Tablas**: cada celda `<td>/<th>` **hoja** se emite como **un** run de texto recolectado (su
  markup interno se aplana a texto plano, no se re-emite), anotado como item de un contenedor
  **grid**: `cont_id` = id de la `<table>` ancestro **más cercano** de la celda, `cont_display` =
  `GRID`, `cont_cols` = la fila más ancha de **esa** tabla (máx. celdas por `<tr>`, en
  `[1, PV_MAX_GRID_COLS]`). `<th>` es negrita. Así la capa de presentación reusa el motor flex/grid
  (`box_tree`) y las celdas se alinean en columnas. `colspan`/`rowspan` quedan fuera de alcance
  (tabla rectangular).
  - **La celda recolectada resuelve su presentación de autor (Hito 23b-9).** El run recolectado
    llama `resolve_context` **en el elemento celda** (no solo en nodos de texto): las reglas
    propias del `td`/`th` (`td{color}`) y la herencia de fila/tabla (zebra
    `tr:nth-child(even){background}`, `tr:first-child{font-weight:bold}`) aterrizan en el run
    (fg/bg/negrita/itálica/align/font/line/deco/text-ext), gateadas por `caps.css` como toda
    presentación. `resolve_context` ahora **arranca en el propio elemento** cuando `n` es un
    elemento (celda/input/imagen); para nodos de texto sigue arrancando en el padre. La
    geometría no cambia: la anotación de contenedor sigue siendo la grilla de la tabla y la
    caja/decoración de autor no se aplica a items de grid (v1). Encontrado con `--dump-dom`
    (Principio 6): antes la ruta de celda nunca resolvía estilos y `td{color}` se perdía en
    silencio. Candado: `test_build_table_cell_author_styles`. En el painter, el **fondo de un
    item de contenedor pinta su propia columna** (`rc_row.bg_w`; antes se descartaba con
    "out of scope (basic)").
  - **Tablas con celdas multi-link = FLUJO, no grid (los links sobreviven).** El aplanado a
    texto de una celda recolectada **destruye sus `<a href>`** (Hacker News quedaba sin un solo
    link). Regla: una tabla con **alguna celda hoja que contenga ≥2 anclas con `href`** es una
    **tabla de navegación/layout**, no de datos: sus celdas hoja **no se recolectan** — se
    **recorren** como contenido normal (dado que `<tr>` es block-tag, cada fila sigue siendo un
    bloque; los links salen como `PV_LINK` con su href/colores/énfasis por `resolve_context`).
    Al visitar una celda recorrida que continúa la fila ya abierta se emite un **run separador
    `" "`** (dedupe: nunca dos seguidos), así "1." y el título no se fusionan. La decisión es
    por tabla, **cacheada** (`pv_flow_reg`, tope `PV_MAX_CONTAINERS`; registro lleno ⇒ grid,
    comportamiento previo — fail-closed y acotado, anti-DoS). Las tablas anidadas deciden cada
    una por sí misma (el scan salta sub-tablas).
  - **Celda hoja con exactamente UNA ancla (tabla grid) = run-link.** En una tabla de datos
    (sin celdas multi-link) una celda cuyo subárbol contiene exactamente un `<a href>` se
    recolecta igual (un run, la grilla no pierde ítems) pero el run es **`PV_LINK`** con ese
    href: el caso común "celda = un link" queda clickeable sin romper la alineación de columnas.
    Con 0 anclas queda `PV_TEXT` como siempre; con ≥2 la tabla entera ya fluyó (regla anterior).
  - **`bgcolor` legacy como fallback de fondo.** Como `<font color>` para el fg: si ningún
    `background` de CSS ganó, el ancestro más cercano con atributo `bgcolor` válido
    (`cc_parse`) aporta `bg_rgb` (p. ej. la barra naranja `#ff6600` y el beige `#f6f6ef` de
    Hacker News, que no usa CSS para eso). Presentación de autor: gateado por `caps.css` en
    `render_doc` como todo color. Las hojas de estilo **externas** (`<link rel=stylesheet>`)
    llegan desde el Hito 27 vía `pv_build_styled` (el worker las fetchea por el padre bajo
    política; ver `spec/tab.md` §8): los colores de clase de HN — títulos negros, subtexto
    gris — ya resuelven cuando `caps.css` está activo.
  - **Tablas anidadas (celda = contenedor, no hoja).** Una celda que contiene una `<table>`
    descendiente es una **hoja = no**: NO se recolecta como un run (eso aplanaría todo su subárbol).
    Es un **contenedor estructural** que se recorre normalmente, de modo que las celdas de la tabla
    interna se recolectan **cada una por separado** contra **su** tabla (la interna): cada tabla
    aporta su propio `cont_id`/`cont_cols`. La supresión de re-emisión (`in_collected_cell`) solo
    aplica al texto cuya celda `<td>/<th>` ancestro **más cercana es hoja** (la que lo recolectó); el
    texto directo de una celda-contenedor se emite normal. Esto es lo que evita que un sitio legado
    que maqueta con tablas anidadas (p. ej. Hacker News: la lista de historias vive en una `<table>`
    dentro de un `<td>` de la tabla externa) colapse sus 30 filas en **un solo** run gigante: ahora
    cada celda de cada fila es un item de grid propio. Recursivo a cualquier profundidad
    (acotado por el árbol).
  - **Fila = bloque (separación por `<tr>`).** El **bloque** de una celda es su `<tr>` más
    cercano (no la tabla entera): la **primera** celda de cada fila lleva `block_break`, las
    demás de la fila lo comparten. Así, cuando una tabla **excede** el motor de grid
    (`BT_MAX_CHILDREN`=128 celdas — el caso de Hacker News, ~150 celdas), la presentación
    degrada a **una fila por línea** (las celdas de la fila fluyen en línea, salto entre filas)
    en vez de un único bloque de texto continuo. Cuando la tabla **sí** entra en el motor
    (tablas de datos chicas), el grid alinea columnas igual (el `block_break` por fila no afecta
    la geometría del grid, que la calcula `box_tree`).
- **Listas**: `indent` = profundidad de anidamiento (cantidad de ancestros `<ul>/<ol>`), 0 si no hay.
  Al **primer** run de cada `<li>` se le antepone un marcador ASCII: `"* "` (viñeta U+2022) en lista
  no ordenada, `"N. "` (ordinal 1-based entre los `<li>` hermanos) en ordenada. El marcador es texto
  normal (hereda estilo, no requiere pintado especial); el indentado lo aplica la capa de
  presentación (`indent * paso`). Atributos `start`/`value` de `<ol>` quedan fuera de alcance.
- **Salto de bloque**: `block_break != 0` cuando el bloque contenedor más cercano del run difiere
  del bloque del run anterior, o cuando un `<br>`/`<hr>` precede al run. Bloques: `body, div, p,
  h1..h6, ul, ol, li, section, article, header, footer, nav, main, aside, blockquote, pre, table,
  tr, figure, form, fieldset, dl, dt, dd`.
- **UTF-8**: `text` se normaliza a UTF-8 bien formado, porque el renderer (cairo) rechaza UTF-8
  inválido y muchas páginas llegan en codificaciones legadas. Las secuencias UTF-8 válidas pasan
  intactas. Un byte que **no** forma una secuencia UTF-8 válida se reinterpreta como **Windows-1252**
  (superóptimo de Latin-1: cubre 0xA0–0xFF idéntico a ISO-8859-1, más comillas tipográficas y guiones
  en 0x80–0x9F) y se reemite como su UTF-8 (p. ej. `0xE9` → `é`). Solo las posiciones **indefinidas**
  de Windows-1252 (`0x81 0x8D 0x8F 0x90 0x9D`) caen a `?`. Esto recupera los acentos de páginas
  Latin-1/Windows-1252 sin declaración de charset, sin dependencia nueva y de forma pura. La salida
  puede ser más larga que la entrada (un byte ≥0x80 → hasta 3 bytes UTF-8).

`href` se guarda **sin** normalizar (no se muestra; la navegación lo valida con `sf_validate_url`).

Además, para cada elemento **`<img>`** (no dentro de un subárbol invisible) se emite un run
`PV_IMAGE`: `text` = atributo `alt` colapsado (o cadena vacía), `src` = atributo `src`, y
`img_w`/`img_h` = el entero inicial de los atributos `width`/`height` (o `-1` si ausente o no
numérico). El `src` se normaliza igual que el `text` para que sea seguro de pintar. El salto de
bloque se calcula como para el texto (bloque contenedor distinto del anterior, o `<br>`/`<hr>`
previo).

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `PV_OK` | Lista construida (puede tener `count == 0`). |
| `PV_ERR_NULL_ARG` | `doc`/`out`/`v`/`text` requerido era `NULL`. |
| `PV_ERR_OOM` | Fallo de asignación. |
| `PV_ERR_INTERNAL` | El backend devolvió un estado inesperado. |

## 6. Garantías de memoria

- Sin estado global mutable; reentrante.
- Cada `pv_view` tiene un dueño único; `pv_free` es el único liberador, idempotente y `NULL`-safe.
- La vista referencia copias propias de texto/href: **no** depende de que el `hp_document` siga vivo
  tras `pv_build` (a diferencia de `dom`).
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 7. Fuera de alcance (de momento)

- Maquetación (posiciones, líneas): la hace el orquestador de UI a partir de esta lista.
- Descarga/decodificado/pintado de la imagen: lo decide `render_policy` y lo ejecuta el
  orquestador. `page_view` solo emite el run con `src` y dimensiones declaradas.
- Estilos CSS, formularios funcionales, tablas con celdas, listas con viñetas/numeración.
- Normalización de espacios entre runs adyacentes (colapso entre nodos), `white-space: pre`.

## 8. CSS externo pre-fetcheado: `pv_build_styled` (Hito 27)

`page_view` es puro y **jamás fetchea**; las hojas externas (`<link rel=stylesheet>`) las obtiene
el worker por el padre confiable (`spec/tab.md` §8) y entran aquí como **texto ya en memoria**:

```c
/* Como pv_build_full, más una hoja de CSS externa pre-fetcheada (extern_css/extern_len;
 * NULL/0 = ninguna: byte-idéntico a pv_build_full). El texto externo se antepone al de los
 * <style> del documento (aproximación v1 del orden de documento: a igual especificidad el
 * <style> de la página gana) y el TOTAL alimentado al parser css queda acotado por
 * PV_MAX_STYLE_BYTES (anti-DoS; el módulo css además se auto-acota). El contenido es HOSTIL:
 * pasa por css_parse_media, que descarta url()/@import (cero red) y falla cerrado. */
pv_status pv_build_styled(const hp_document *doc, int js_enabled, int reader,
                          int prefers_dark, const char *extern_css, size_t extern_len,
                          pv_view **out);
```

- **Dado** `extern_css == NULL`, **cuando** se construye la vista, **entonces** el resultado es
  byte-idéntico a `pv_build_full` (candado de no-regresión).
- **Dado** un `extern_css` con `p{text-align:center}` y un documento sin `<style>`, **cuando** se
  construye, **entonces** los runs de `<p>` llevan `text_align == CSS_ALIGN_CENTER` (la hoja
  externa alimenta la misma cascada que las internas).
- **Dado** un `extern_css` y un `<style>` del documento que declaran la misma propiedad con la
  misma especificidad, **cuando** se resuelve, **entonces** gana el `<style>` del documento
  (viene después en el texto concatenado — orden de cascada).
- El gate de presentación **no cambia**: los colores/estilos de autor (externos o internos)
  siguen gateados por `caps.css` en `render_doc`; `display:none`/flex/grid siguen siendo
  estructurales.
