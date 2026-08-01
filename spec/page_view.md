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
    /* flex-wrap / row-gap / align-items (CONTENEDOR) + align-self (ITEM). Estructura
     * como el resto de cont_*/flex_* (render_doc los propaga siempre). */
    int     cont_wrap;        /* css_flex_wrap del contenedor, 0 (-> nowrap) */
    int     cont_row_gap;     /* px >= 0, o -1 (sin definir -> cae a cont_gap) */
    int     cont_align_items; /* css_align_kw del contenedor (align-items) */
    int     flex_align_self;  /* css_align_kw del ITEM (align-self); UNSET/AUTO
                               * -> usa cont_align_items */
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

**Extensiones 2026-07-10 (`image_rendering`, `caret_color`).** Dos campos heredables más en la misma
fusión `pv_text_ext`: `image_rendering` (`css_image_rendering`; `pixelated`/`crisp-edges` piden filtro
nearest-neighbour al escalar la imagen decodificada) y `caret_color` (0xRRGGBB o -1; tiñe el caret de un
control de formulario enfocado; `auto` ⇒ -1). Mismo gate `caps.css` aguas abajo. `pv_set_text_ext` pasa
a recibir la struct completa (`const pv_text_ext *`, ahora pública en `page_view.h`) en lugar de una
lista posicional de ints — con 20+ campos la firma posicional era deuda técnica.

**`pointer-events` y `content-visibility` (caja, no run).** `pointer-events` viaja en `pv_box_def`
(como `cursor`): la GUI resuelve el valor por la cadena de cajas ancestras y, con `none`, excluye el
elemento del hit-testing (hover/click/cursor). `content-visibility: hidden` **no** añade campo: se
pliega en `pv_box_def.visibility` (⇒ `CSS_VIS_HIDDEN`, si `visibility` no estaba fijada) al construir
la definición — misma simplificación documentada que `visibility: collapse` (se salta el pintado, se
reserva el espacio).

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
las columnas de `grid-template-columns` (cuenta de tracks, `[1, PV_MAX_GRID_COLS]`; `[[css]]` expande
`repeat(N, ...)` y cuenta `minmax(...)` como un track desde la expansión de layout CSS — los *pesos*
`fr`/tamaños de track siguen sin resolver, cada track maqueta como columna de igual ancho). Junto al
contenedor viajan también, desde esa misma expansión, `flex-wrap`/`row-gap`/`align-items`
(`cont_wrap`/`cont_row_gap`/`cont_align_items`). Es **estructura, no estilo de autor**: `render_doc` lo
propaga **siempre** (desacoplado de `caps.css`, doctrina "Layout != estilo de autor"); solo los
*colores*/`text-align`/`font-size` de autor quedan gateados por `caps.css`. Los `pv_append*`
inicializan `cont_id` a -1 y `cont_wrap`/`cont_align_items` a 0, `cont_row_gap` a -1;
`pv_set_container` fija los ocho campos en el último run. El `background` shorthand y `bgcolor` legacy
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
(0 = sin definir = `row`). El mismo elemento ITEM aporta también `align-self`
(`flex_align_self`, `css_align_kw`, 0/`CSS_AK_UNSET` si no se fijó — la GUI entonces usa el
`align-items` del contenedor). Dado que el texto directamente dentro del contenedor (item anónimo) no
tiene elemento intermedio, lleva los defaults. Es **estructura** como `cont_*`: `render_doc` lo propaga
siempre, sin gate de `caps.css`. `pv_set_flex` fija los seis campos en el último run. Runs del camino
de celdas de tabla (grid sintetizado) llevan los defaults. Fuera de alcance: `grid-template-rows`/
`grid-column`/`grid-row: span N` (resueltos en `css_style` por el Hito 23b-7, aún no consumidos aquí —
cada item de grid sigue ocupando exactamente una celda), alineación en el eje cruzado de GRID
(`align-items`/`align-self` solo llegan al pintor para contenedores FLEX).

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
                               int cont_gap, int cont_justify, int cont_cols,
                               int cont_wrap, int cont_row_gap, int cont_align_items); /* contenedor */
void          pv_set_flex(pv_view *v, int flex_grow, int flex_shrink, int flex_basis,
                          int flex_order, int flex_direction, int flex_align_self); /* flex por-item */
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
  `title`, `noscript` (con JS activo), o `video`/`audio` (2026-07-19: el contenido interno de
  un elemento de media es fallback para motores SIN soporte; este motor pinta el elemento
  mismo como `PV_VIDEO`, así que el fallback no se muestra nunca — igual que todo motor
  moderno. Candado: `test_build_video_fallback_suppressed`).
- **Selección de `<source>` (2026-07-19)**: un `<video>`/`<audio>` sin `src` directo elige
  entre sus `<source>` hijos **por `type`**: gana el primero cuyo type contenga
  `mpegurl`/`mp2t`/`mp4` (lo que el pipeline de media reproduce nativo); si ninguno,
  el primero con `src`. Candado: `test_build_video_source_type_preference`.
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

**Fallback a `srcset` (sin `src`):** cuando `<img>` no tiene `src` (o está vacío), se usa el
primer candidato de `srcset` (`srcset_first_url`, pura) — el patrón habitual de imágenes
responsivas y de `<img srcset=...>` sin `src` de las librerías de lazy-loading (los hermanos
`<source srcset=...>` de un `<picture>` NO son visitados por este recorrido; solo el `<img>` de
fallback dentro de `<picture>` lo es, y ya funcionaba antes de este cambio). Un candidato
normal termina en el primer espacio o coma (su descriptor `2x`/`800w` opcional va separado por
espacio); un candidato `data:` termina en el primer espacio o el final de la cadena, para no
cortar en la coma interna de `;base64,`. Sin `src` **ni** `srcset` utilizable: sin run, como
antes. Ver `[[freedom-data-url-images]]`.

### Tamaño CSS de elementos reemplazados: `width`/`height` gana al atributo (2026-08-01)

`img_w`/`img_h` de un `<img>` o `<svg>` en línea se toman primero de los atributos
`width`/`height`, y luego se **sobreescriben** con el `width`/`height` **resueltos por CSS** del
propio elemento cuando cada uno es un px positivo (`apply_css_replaced_size`, sobre
`cached_element_style`). Es **maquetación, no color de autor**: se aplica siempre (no tras
`caps.css`), y una regla de autor gana al atributo de presentación como en la cascada real. `auto`,
porcentaje y unset se dejan intactos (el porcentaje no tiene bloque contenedor en este modelo
plano; `img{max-width:100%;height:auto}` no toca el tamaño intrínseco). Regresión que cierra: los
íconos (X, Bluesky, favicons) se pintaban a su tamaño natural de `viewBox` (~100–1792 px) en lugar
de los 20–40 px del CSS, reventando las corridas flex. Tests `test_build_svg_css_size`,
`test_build_image_css_size_overrides_attr`, `test_build_image_auto_size_keeps_attr`.
Ver `[[freedom-replaced-css-sizing-and-flex-spacer]]`.

### Spacer flex vacío: un ítem sin contenido que **crece** reserva su hueco (2026-08-01)

Un ítem flex/grid **vacío y sin decoración** con `flex-grow > 0` (el clásico
`<span style="flex:1"></span>` de una barra de navegación) antes se descartaba —solo los leaves
vacíos **decorados** recibían run placeholder— así que no participaba en la línea del contenedor y
la distribución de espacio libre colapsaba (el botón final "Sign in" quedaba pegado a la izquierda
en vez de empujado al extremo derecho). Ahora `pv_build` emite el placeholder también cuando el
elemento tiene `flex_grow > 0` **y** su padre directo es contenedor `flex`/`grid` (la condición del
padre evita emitir una línea en blanco por un `flex-grow` suelto en flujo de bloque).
Test `test_build_empty_flex_grow_spacer`.

### Control de formulario dentro de una caja: se sienta en el rect de contenido (2026-08-01)

En el painter, una fila reemplazada de `RD_INPUT` se emitía con `x_off = 0` y `bg_w = content_w`
(ancho de página), por lo que un `<input>` con `width:100%` dentro de un `<form>` con
`padding`/`max-width` se escapaba al borde izquierdo de la página y a ancho completo. Al volver de
`emit_replaced_row`, si hay una caja abierta (`box_depth > 0`) la fila del input se **re-asienta**
sobre el rect de contenido de la caja (`rc_box_context` → `x_off`, `bg_w` acotado), igual que ya
hacen las filas de texto vía `s.indent_px`. Fuera de caja es idéntico byte a byte; imagen/vídeo/svg
quedan intactos para acotar el cambio.

### Cajas vacías: el elemento decorado sin contenido también genera caja (2026-07-26)

El recorrido es **por nodos de texto**: una caja (`pv_box_def`) solo se registraba cuando
`resolve_context` la alcanzaba subiendo desde un texto descendiente. Un elemento **decorado pero
vacío** (una barra `<div style="background:#f00;height:8px"></div>`, un separador con `height`,
un ícono `<div>` circular, una `tile` de grid) **no tiene texto descendiente**, así que su caja
nunca se registraba y **desaparecía del render** — justo lo contrario de un navegador real, donde
un `<div>` vacío con fondo/tamaño **sí** pinta y reserva su espacio.

- **Dado** un elemento que (a) **generaría una caja** (`css_has_boxdeco`: padding/borde/radio/
  sombra/outline **con valor > 0** — un `padding:0`/`border:0` de reset no es decoración, ver
  «Tablas flow» abajo —, posición/`height`/`min-height`/`aspect-ratio`/gradiente/opacity/blend/
  transform)
  y (b) es una **hoja de contenido** — sin elementos hijo y sin texto que no sea espacio en blanco —
  **cuando** el recorrido lo visita, **entonces** `page_view` emite **un run placeholder de texto
  vacío** que lleva el `block_id` de esa caja (más su pertenencia flex/grid `cont_*` e ítem, vía
  `resolve_context` sobre el propio elemento). El painter ya reserva `box_h`/`min-height` y pinta la
  decoración al abrir/cerrar la caja (`open_box`/`close_top_box`), así que el placeholder es el único
  eslabón que faltaba. El predicado de generación de caja es el **mismo** para elementos con y sin
  contenido (semántica CSS: la caja la decide el estilo, no el contenido).
- Las cajas **anidadas vacías** se resuelven solas por el mecanismo de padres existente: un
  `<div bg>` cuyo único hijo es un `<div vacío>` no es hoja (tiene hijo elemento) → no emite
  placeholder, pero el hijo hoja sí, y su `resolve_context` registra ambas cajas con su enlace
  `parent_id`; al abrir/cerrar, el padre reserva la altura del hijo + su padding. Candado:
  `test_build_empty_box_gets_run_and_box`.
- **Byte-identical por defecto:** el placeholder es texto vacío (no emite fila) y su `block_id`
  está gateado por `caps.css` en `render_doc`; con CSS de autor apagado (Privacy by Default) no hay
  caja ni fila → render idéntico al previo.

### Ítems flex/grid: reservan su altura de caja y pintan su decoración (2026-07-26)

Un ítem de contenedor flex/grid se maqueta en `layout_container` (no por el camino de cajas plano),
que antes solo **fluía el texto** del ítem: se perdía la **decoración de la caja raíz del ítem**
(fondo/borde/radio/sombra de una tarjeta) y un ítem **vacío** (una `tile` de grid sin texto)
colapsaba a altura 0 (la grilla entera desaparecía). Ahora, para cada ítem:

- La **caja raíz** del ítem = la caja de menor profundidad (más cercana al contenedor) entre los
  `block_id` de sus runs.
- Su **`box_h`/`min-height`** es un piso de la altura del ítem (una `tile` vacía reserva su alto).
- El contenido del ítem se **inserta por el padding+borde** de esa caja.
- Se crea una `rc_box` con el rect final de la columna del ítem, así la decoración pinta por el
  mismo bucle de cajas del painter.
- **Límite v1:** solo pinta la caja **raíz** del ítem; una caja **anidada dentro** del ítem (un
  `<span>` pill, un ícono circular dentro de una tarjeta) sigue sin pintar su decoración (el camino
  de contenedor aplana el interior a texto). Es el próximo incremento.

### Tablas flow: la fila es la línea; decoración cero no es caja (2026-07-29)

Una tabla **flow** (alguna celda hoja con 2+ anclas — el caso Hacker News) se recorre por el
camino normal para no destruir sus links. La intención de siempre («cada `<tr>` es un bloque: la
primera celda de la fila rompe línea, el resto la comparte») estaba rota por tres vías, y las tres
partían cada fila de HN en 3–4 líneas con huecos de párrafo (5208px de alto contra 1330px de
Firefox para la misma portada):

- **Dado** un elemento decorado **vacío** dentro de una celda walked de una tabla flow (la flecha
  de voto de HN: `<div class="votearrow">`), **cuando** se emite su run placeholder, **entonces**
  su bloque es **la fila** (`nearest_row`), no el propio `<div>` (que como block-tag rompería la
  línea), y **no lleva caja** (`block_id -1`): el painter hace flush de línea en cada transición
  de caja, así que una caja intercalada también partiría la fila. **Límite v1:** la decoración
  propia del ícono (su sprite de fondo) no pinta dentro de una fila flowed; la integridad de la
  fila gana. Helper: `in_flow_table_cell` (celda td/th sin tabla anidada cuya tabla decide flow).
- **Dado** un `<td>`/`<th>` de una tabla flow con decoración propia (el `td.title{padding-right}`
  de HN), **cuando** `resolve_context` registra cajas ancestrales, **entonces** la celda se
  **salta** (mismo helper): la caja por-celda partiría la fila en el painter. Las celdas de tablas
  **grid** (datos) no cambian: sus cajas viven en el camino de contenedor (`layout_container`).
- **Dado** un bloque cuyo elemento es `<tr>` sin margen de autor, **cuando** se resuelven los
  márgenes verticales del bloque, **entonces** default **0** (en CSS real los márgenes no aplican
  a cajas table-row) en vez del margen UA de `<p>` (1em arriba y abajo, que espaciaba cada fila
  una línea entera).

Dos arreglos de soporte en el mismo lote, ambos generales (no solo tablas):

- **`css_has_boxdeco` exige valor > 0:** `padding: 0` / `border: 0` (el reset universal que media
  web declara) y `visibility: visible` **no** son decoración — registraban una caja que no pinta
  ni inseta nada y cuyo único efecto era partir líneas y sumar huecos en el painter.
- **Run de continuación sin caja no cierra cajas (painter):** un run sin `block_break` y con
  `block_id < 0` (los separadores « » entre celdas walked) sigue en la línea abierta, así que
  sigue en el **contexto de caja** abierto; reconciliar a -1 cerraba la caja y hacía flush de la
  línea a mitad de fila.

### Paridad con Firefox: fila inline-block, hoja out-of-flow, caja de celda (2026-07-27)

Tres reglas de generación de estructura que separaban el render de Freedom del de Firefox en
páginas modernas. Verificadas comparando el mismo HTML en **Firefox 140 ESR headless**
(`firefox --headless --screenshot`) contra `--download-png`.

- **Fila anónima de inline-blocks** (`is_inline_block_row`). **Dado** un elemento cuyos hijos
  elemento son **todos** `display:inline-block`, que no tiene texto propio más allá de espacios,
  **cuando** se resuelve su contexto, **entonces** se marca como **contenedor flex anónimo**
  (`BX_DISPLAY_FLEX`, `gap` 0, `justify` derivado del `text-align` del padre: `center`→`CENTER`,
  `right`→`END`). Antes cada hijo `inline-block` abría una caja de bloque a ancho completo y se
  **apilaban verticalmente, uno por línea** — una barra de navegación, una tira de badges o un
  grupo de botones se rompía por completo. Deliberadamente **estrecho**: el contenido **mixto**
  (texto junto a un inline-block) se deja intacto, porque necesita maquetación inline real dentro
  de una línea, no una fila flex — convertirlo reflowaría la frase que lo rodea. Acotado por
  `PV_MAX_INLINE_ROW_ITEMS` (128).
- **Hoja de contenido ignora hijos fuera de flujo** (`element_is_content_leaf`). Un hijo
  `display:none` o **fuera de flujo** (`position:absolute`/`fixed`) **no es contenido**: lo pinta
  la pasada de posicionamiento, no el flujo del padre. Contarlo como contenido hacía que un
  wrapper `position:relative` que solo contiene hijos posicionados **no registrara caja alguna**,
  así que no pintaba, no reservaba altura y — lo peor — sus hijos **perdían su bloque contenedor**
  y resolvían sus insets contra un rect degenerado de 0x0, aterrizando fuera de pantalla. Es el
  patrón "hero con overlay" / "tarjeta con badge en la esquina".
- **Las celdas de tabla generan caja** (`generates_box`). `<td>`/`<th>` **no** son block tags (no
  deben cortar línea: una fila de celdas fluye como una línea por el contenedor grid, y hacer
  `<td>` block partiría las celdas de navegación multi-enlace), pero **sí** generan caja:
  `td { border: 1px solid }` es de lo más común en la web y no pintaba **nada** porque nunca se
  registraba caja para la celda. Además el `block_id` resuelto de la celda se **reenvía** con
  `pv_set_block_id` (se calculaba y se descartaba), y un `<th>` centra su texto por defecto de UA.

### Paridad con Firefox, tanda 2026-07-30: la banda, el contenedor y la caja inline

Cinco reglas medidas contra Firefox (`firefox --headless --screenshot` del mismo HTML) sobre
páginas modernas reales. Todas comparten un mismo síntoma: el modelo plano pintaba **algo**
donde el navegador pinta **otra cosa**, no donde no pinta nada.

- **La banda de fondo de una fila muere donde empieza una caja.** El fondo de fila es la
  aproximación del modelo plano a "se ve el fondo del ancestro detrás del texto". Si ese
  ancestro **registra una caja** y pinta un fondo propio (color, gradiente o imagen), la
  búsqueda **termina ahí sin banda**: la caja ya lo pinta, sobre su rect exacto. Antes el
  recorrido seguía hacia afuera, se llevaba el color de un ancestro EXTERNO y lo pintaba a
  ancho completo **encima** de lo que la caja acababa de dibujar — todo hero con gradiente
  perdía su titular bajo una banda del color de la página, y la banda de una caja angosta
  se desbordaba por sus lados.
- **El contenedor flex/grid conoce su propia caja (`cont_box_id`).** Es la caja del elemento
  contenedor cuando registra una, si no la del ancestro con caja más cercano, si no -1. La
  capa de presentación maqueta los ítems **dentro** de ese rect, y la caja raíz de un ítem
  debe ser **descendiente estricta** de ella. Sin ese límite, un contenedor cuyos ítems no
  llevan caja propia hacía que **todos** reclamaran la caja DEL CONTENEDOR como raíz: un
  `header{display:flex;justify-content:space-between}` pintaba su banda **dos veces**, una
  por ítem, con la página asomando por el medio. Campo nuevo ⇒ cruza el códec IPC
  (`spec/tab.md`), o la función queda muerta en silencio.
- **`display:inline-block` encoge al contenido y lo coloca el `text-align` del padre**
  (CSS 2.2 §10.3.9). Un botón centrado se pintaba como una barra del ancho de la página.
  Dos caminos, una regla: en flujo plano la caja mide su contenido máximo
  (`box_shrink_width`, la misma medición que usa el motor flex) y se desplaza con el
  sobrante; y la **fila flex anónima** que se sintetiza para un padre de hijos inline-block
  adopta el `text-align` **heredado** (sólo se conoce al terminar el recorrido de ancestros:
  el elemento casi nunca lo declara, lo hereda de `body`).
- **Una caja anidada dentro de un ítem flex/grid ya pinta** (cerrado el límite v1 de
  "Ítems flex/grid" de arriba): el interior del ítem se maqueta con el MISMO
  `reconcile_boxes`, acotado a la caja raíz del ítem, y las cajas que abre se trasladan a la
  columna igual que sus filas. La caja raíz se **reserva antes** de que fluya el contenido,
  porque el pintor recorre las cajas en orden de array y si no taparía a las de dentro. Es
  la píldora de un badge, el chip de un ícono, el avatar de una tarjeta.
- **Un elemento reemplazado se coloca como la caja inline que es.** El `text-align` heredado
  viaja en los runs `PV_IMAGE`/`PV_SVG` y los centra/alinea; y las dimensiones
  **declaradas** (`<img width height>`) mandan sobre las del bitmap decodificado — un logo
  de 1024px con `width="180"` mide 180, como en Firefox. Además, dentro de una caja el run
  conserva su **propio** tope de ancho y su `margin:0 auto` (antes se descartaban por evitar
  el doble conteo de los insets de la caja, y un `max-width:560px; margin:0 auto` dentro de
  un hero nunca envolvía donde envuelve Firefox).

### SVG en línea: `PV_SVG` (2026-07-30)

Un `<svg>` se emite **entero** como un run `PV_SVG` que lleva su marcado serializado en
`text` y su tamaño intrínseco en `img_w`/`img_h`. Su subárbol queda **suprimido** del
recorrido de texto (`is_skipped_tag`), porque el contenido de un `<text>` es geometría, no
prosa de la página: antes aterrizaba en medio del artículo como palabras sueltas.

No lo gatea `caps.images`: la gramática que acepta `svg_render` **no tiene forma de URL**,
así que un SVG en línea no puede hacer fetch — no hay nada que gatear. Contrato completo
del parser y del pintor en `spec/svg_render.md`.

### Colapso de espacio en el borde entre runs (2026-07-31)

CSS colapsa una **secuencia** de espacios en uno solo; **no inventa** un espacio donde el
documento no tenía ninguno. El flujo de palabras del pintor hacía lo segundo: insertaba
`space_w` antes de cada palabra que no abriera la línea, así que
`<strong>bold</strong>, <em>italic</em>` se pintaba `bold , italic ,` — una coma separada
de su palabra en cada elemento inline de toda página con énfasis, enlaces o `<code>`.

**Dado** dos runs consecutivos en la misma línea
**cuando** el primero **no termina** en espacio y el segundo **no empieza** con espacio
**entonces** entre ellos no se pinta separación (`bold,`).

**Dado** que el primero termina en espacio **o** el segundo empieza con espacio
**cuando** se pinta el primer fragmento del segundo run
**entonces** se pinta **un** espacio, nunca dos (el colapso sigue valiendo).

Dentro de **un mismo** run las palabras siempre estuvieron separadas por espacio en la
fuente (el bucle parte en `' '`), así que ahí la separación se mantiene incondicional.
El estado vive en `rc_state.prev_ended_ws`, que se actualiza al terminar cada run y solo
importa a mitad de línea (al abrir línea no hay fragmento previo y no se separa nada).

`white-space: pre`/`pre-wrap`/`pre-line` no pasa por esta regla: ahí los espacios son
literales y ya se pintan uno a uno.

### `position:absolute|fixed` y `float` vuelven al elemento de bloque (2026-07-31)

CSS 2.2 §9.7: sacar un elemento del flujo (`position: absolute|fixed`, o un `float`
distinto de `none`) hace que su `display` **compute a `block`**. Un `<span>` absoluto es
una caja de bloque, no una caja en línea.

Freedom no aplicaba esa regla: la elegibilidad para registrar caja (`is_block_like`) se
decidía solo con la etiqueta y el `display` **declarado**, así que

```html
<div style="position:relative"><span style="position:absolute;right:10px;bottom:10px">x</span></div>
```

**no registraba ninguna caja** para el `<span>` — y sin caja no hay entrada en el árbol de
posicionados, con lo cual `right`/`bottom` (que `box_tree.c` ya resuelve, reglas R4/R8) no
tenían nada que posicionar. El mismo marcado con un `<div>` funcionaba. El síntoma es que
todo *badge* / *close button* / *tooltip* escrito sobre un `<span>` aterrizaba en el flujo,
a ancho completo, en vez de en su esquina.

**Dado** un elemento cuyo `position` resuelto es `absolute` o `fixed` (o cuyo `float` no es
`none`) **cuando** se decide si genera caja **entonces** se trata como de bloque **sea cual
sea** su etiqueta o su `display` declarado, incluido `display:inline`.

Es solo la regla de **elegibilidad**: no fuerza salto de bloque (`causes_block_break` sigue
mandando en el flujo) ni cambia el gate de `caps.css`.

### Cajas de nivel inline: `display:inline-block` dentro de una línea (2026-07-31)

Un `inline-block` en medio de una frase — un *badge*, una píldora, un *chip*, un botón
pequeño — **fluye dentro de la línea**. Antes partía la frase en tres: el texto anterior, el
badge en su propia línea a ancho completo, y el resto del texto.

**Causa.** `causes_block_break` ya devolvía 0 para `inline-block`, pero el elemento
**registra caja**, y abrir una caja es una operación de bloque: `open_box` hace `flush_line`
y estrecha el rect de contenido. Eso es exactamente lo que no debe pasarle a algo que fluye
dentro de una oración.

**Modelo.** Una caja de nivel inline **no entra en la pila de cajas** (`box_stack`). Se
sigue aparte en `rc_state` (`inline_box_def`, NULL = ninguna abierta — un centinela NULL, no
un id, para que el `memset(0)` que recibe todo `rc_state` ya signifique "ninguna"):

**Dado** un run cuya caja más profunda es `display:inline-block`
**cuando** la línea ya está abierta y **tiene fragmentos** (hay texto antes en la misma línea)
**entonces** la caja no se abre como bloque: se anota su fragmento inicial y el `pen_x` de
arranque, se reserva su padding/borde izquierdo avanzando el `pen_x`, y el texto sigue en la
**misma** línea.

**Dado** que el flujo abandona esa caja (un run posterior pertenece a otra)
**entonces** se registra su fragmento final y se reserva su padding/borde derecho, para que
el texto que sigue no se le encime.

**Dado** que la línea se vacía (`flush_line`)
**entonces** la caja se materializa como un `rc_box`: `x`/ancho salen de la extensión de
**sus** fragmentos (del inicial al final registrado), `y`/alto de la fila que se está
cerrando — que es el único momento en que se conocen.

**Dado** un `inline-block` que **abre** la línea (no hay texto antes)
**entonces** conserva el tratamiento de bloque de siempre (encoge a su contenido y lo coloca
el `text-align` del padre), que es lo que necesita un botón de llamada a la acción centrado.

**Fuera de alcance (v1):** una caja inline que **cruza un salto de línea** termina en el
salto (no se parte en dos rects), y su rect no sigue el desplazamiento que `text-align`
aplica a la línea al pintar — el caso centrado frecuente (todos los hijos `inline-block`) ya
lo cubre la fila anónima.

### Contenedores flex/grid ANIDADOS (2026-07-31)

Un `header{display:flex}` que contiene `nav > ul{display:flex}` se maqueta como **un**
contenedor con el `ul` dentro, no como dos hermanos apilados. Es el patrón de la barra de
navegación de casi cualquier sitio moderno, y el de una grilla de tarjetas donde cada
tarjeta es flex.

**Por qué no bastaba llevar el padre en el run.** Un run lleva **un solo** contenedor: el
más interno. Maquetar el nivel externo necesita las **propiedades** del contenedor externo,
y hay un caso frecuente en el que **ningún** run las lleva: una grilla cuyos hijos son
*todos* contenedores (`.cards{display:grid}` con tarjetas `display:flex`) no tiene ningún
run con `cont_id == .cards`.

**Diseño implementado** (espeja la tabla `pv_box_def`):

1. `pv_view`/`rd_doc` llevan una **tabla de descriptores** (`pv_cont_def`) indexada por
   `cont_id`: `parent_id`, `parent_item` y los parámetros del contenedor
   (display/gap/justify/cols/rows/direction/col_w/wrap/row_gap/align_*/grid_flow/box_id/
   anon_row). Cruza el IPC como un arreglo propio, después del árbol de cajas.
2. `resolve_context` **no corta** en el primer contenedor: describe **todos** los de la
   cadena y registra `anc_id[]`/`anc_item[]` (de dentro hacia fuera). `pv_build` los enlaza
   con `link_cont_chain`, que pide el ordinal al **mismo** tracker por contenedor que usan
   los runs — así un contenedor anidado ocupa exactamente **una** ranura de ítem de su
   padre, intercalada en orden con los runs directos del padre.
3. El bucle de layout agrupa por el contenedor **raíz** (`root_cont_of`), y
   `layout_container` recibe el `cid` que maqueta y lee sus parámetros de la tabla.
4. El ordinal de ítem se toma **a ese nivel** (`item_at_level`): un run dentro de un
   contenedor anidado reporta la ranura del contenedor anidado, así que todos sus runs
   colapsan en **un** ítem del externo.
5. Un ítem cuyos runs pertenecen a un contenedor más profundo se resuelve por
   **recursión**; su base de flex es el **max-content** del contenedor anidado
   (`nested_cont_basis`: suma de las bases de sus ítems más sus gaps), no el ancho de su
   texto puesto en fila.

**Tres reglas que costaron sangre y son parte del contrato:**

- **La caja raíz de un ítem anidado es la caja del contenedor HIJO**, no la que devuelve
  `item_root_box` (que la deriva del `cont_box_id` del run, o sea del rect del contenedor
  **interno**, y por eso devolvía la caja de un ítem interno suelto). Sigue exigiéndose que
  sea **descendiente estricta** de la caja de este contenedor.
- **Un contenedor sin caja propia hereda la primera caja de más afuera** (la misma regla
  `box_pending` que ya tenía la anotación del run). Sin eso su `box_id` quedaba en -1, el
  pintor no tenía frontera donde parar el walk de cajas del ítem y **reabría la caja del
  envoltorio dentro de cada ítem**.
- **El walk de cajas de un ítem para en la caja del CONTENEDOR** cuando el ítem no tiene
  caja propia (`stop_at = rb >= 0 ? rb : cdv.box_id`). Una caja en el contenedor o por
  encima es del contenedor, no del ítem.

**Contenedores sintetizados.** El contenedor de una tabla no lo descubre el walk de
`display:flex|grid`: lo sintetiza la ruta de celdas. Esa ruta **debe llenar el descriptor
también** — un descriptor sin describir dejaba `display = 0` y toda tabla se maquetaba como
una única fila flex con todas las celdas en línea. Lo mismo vale para la fila anónima de
`inline-block`, cuyo `justify` se resuelve por **herencia** de `text-align` *después* del
walk: ese valor tardío hay que escribirlo en el descriptor, no solo en el run.

**Cotas.** `PV_CONT_DEPTH` (8) acota la cadena; más allá los niveles externos se descartan y
esos contenedores se maquetan como nivel superior — degrada a lo de antes, nunca cicla.
`read_view` rechaza un `parent_id` fuera de rango o que apunte a sí mismo degradándolo a
nivel superior, así que un worker hostil no puede indexar fuera de la tabla.

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
