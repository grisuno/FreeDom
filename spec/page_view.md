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
    int     cont_id;     /* contenedor flex/grid de autor mas cercano, o -1 */
    int     cont_display;/* bx_display del contenedor (flex/grid), o 0 */
    int     cont_gap;    /* gap del contenedor en px */
    int     cont_justify;/* fx_justify del contenedor */
    int     cont_cols;   /* columnas del grid, o 0 */
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
desde el ancestro más cercano. El subconjunto soportado: selectores simples/compuestos (tipo, `.clase`,
`#id`, `*`, grupos por coma; sin combinadores) y las propiedades `color`, `background[-color]`,
`text-align`, `font-size`, `font-weight`, `font-style`, `display`. **Seguridad:** `[[css]]` descarta
cualquier valor con `url(` y toda `@`-regla, así que el CSS de autor **nunca telefonea a casa** ni abre
una baliza de rastreo; es contenido hostil, por eso se fuzzea (`make fuzz-css`/`fuzz-pv`).

**Color del autor (`fg_rgb`):** sale del ancestro más cercano cuyo `css_style` fije `color` (regla de
`<style>` o `color:` en línea), con el `<font color>` legacy como respaldo cuando ninguna declaración
CSS ganó; `background-color` nunca se confunde con `color`; valor no parseable → -1. Es dato de
presentación: `render_doc` solo lo propaga con `caps.css`, y nunca implica red. Los `pv_append*`
inicializan `fg_rgb` a -1; `pv_set_color` lo fija en el último run.

**Alineación y tamaño del autor (`text_align`/`font_scale`):** `text_align` es el `text-align` heredado
(un `css_align`: 0 sin definir, 1 izquierda, 2 centro, 3 derecha, 4 justificado); `font_scale` es el
`font-size` en porcentaje (100 = normal; `px` relativo a 16px, `em`/`rem`/`%` y palabras clave), 0 si
no se define. Ambos del ancestro más cercano que los fije. Mismo gate de presentación que los colores
(`render_doc` los propaga solo con `caps.css`); `pv_set_text_style` los fija en el último run.

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
`style` declare `display:flex` o `display:grid` (parseado por `[[box_style]]`). Los runs de un mismo
contenedor comparten `cont_id` (registro en orden de documento, -1 = ninguno); se guardan además su
`display`, el `gap` (px), `justify-content` (`[[flex_layout]]` `fx_justify`) y, en grid, el número de
columnas de `grid-template-columns` (cuenta de tokens; `repeat()`/`minmax()` fuera de alcance). Es
dato de presentación: `render_doc` lo propaga solo con `caps.css`, así que con CSS de autor apagado
todo es flujo plano. Los `pv_append*` inicializan `cont_id` a -1; `pv_set_container` fija los cinco
campos en el último run. El `background` shorthand y `bgcolor` legacy siguen fuera de alcance.

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
void          pv_set_text_style(pv_view *v, int text_align, int font_scale); /* align/font del ultimo run */
void          pv_set_container(pv_view *v, int cont_id, int cont_display,
                               int cont_gap, int cont_justify, int cont_cols); /* contenedor */
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
- **Tablas**: cada celda `<td>/<th>` se emite como **un** run de texto recolectado (su markup
  interno se aplana a texto plano, no se re-emite), anotado como item de un contenedor **grid**:
  `cont_id` = id de la `<table>` ancestro, `cont_display` = `GRID`, `cont_cols` = la fila más ancha
  (máx. celdas por `<tr>`, en `[1, PV_MAX_GRID_COLS]`). `<th>` es negrita. Así la capa de
  presentación reusa el motor flex/grid (`box_tree`) y las celdas se alinean en columnas. `colspan`/
  `rowspan` quedan fuera de alcance (tabla rectangular).
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
