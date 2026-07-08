# spec/render_doc.md — Documento de render (modelo puro de pintado)

> Módulo `render_doc` (prefijo `rd_`). Lógica **pura, sin I/O**: la capa auditable entre la
> *display list* inerte (`page_view`) y el orquestador de presentación (GUI / `--headless`).
> Decide **qué** se muestra y **cómo se etiqueta** (estilo semántico + decisión de imagen),
> nunca píxeles, fuentes ni colores: eso pertenece a la capa de presentación. Metodología:
> SDD + TDD.

## 0. Por qué existe

`page_view` entrega una lista de *runs* inertes (texto, enlaces, imágenes). El renderer no debe
recorrer el DOM hostil ni pintar texto plano sin estructura, pero tampoco debe repetir en cada
orquestador (GUI y headless) las reglas de "esto es un encabezado", "esto es un enlace", "esta
imagen está bloqueada y hay que avisar". `render_doc` centraliza esas reglas en una función pura:

- Convierte cada run en un **bloque con estilo semántico** (`RD_HEADING`/`RD_PARAGRAPH`/`RD_LINK`/
  `RD_IMAGE`).
- Aplica el **gate de capacidades** (`render_policy`) a cada imagen y guarda su decisión.
- Cuando la página declara imágenes y la capacidad está **desactivada** (por defecto), antepone
  un **aviso** (`RD_NOTICE`) con `rdp_images_warning()`: el usuario **siempre** queda avisado.

Así, GUI y headless comparten exactamente el mismo modelo (DRY) y la lógica es directamente
testeable sin Wayland ni terminal.

## 1. Tipos

```c
typedef enum rd_kind {
    RD_HEADING = 0,   /* encabezado; heading_level 1..6 */
    RD_PARAGRAPH,     /* texto de cuerpo */
    RD_LINK,          /* hiperenlace; href es el destino */
    RD_IMAGE,         /* placeholder de imagen; href es el src, img_decision válida */
    RD_NOTICE         /* aviso del agente de usuario (p. ej. el aviso de rastreo) */
} rd_kind;

typedef struct rd_block {
    rd_kind          kind;
    int              heading_level;  /* 1..6 en RD_HEADING, 0 en otro caso */
    int              block_break;    /* !=0: un límite de bloque precede a este bloque */
    char            *text;           /* propio, NUL-terminado, UTF-8 válido */
    char            *href;           /* propio: destino (RD_LINK) o src (RD_IMAGE); si no, NULL */
    rdp_img_decision img_decision;   /* solo significativo en RD_IMAGE */
    int              fg_rgb;         /* color del autor 0xRRGGBB, o -1; solo con caps.css */
    int              bg_rgb;         /* background-color del autor 0xRRGGBB, o -1; solo con caps.css */
    int              text_align;     /* text-align del autor (css_align); solo con caps.css, si no 0 */
    int              font_scale;     /* font-size del autor en %; solo con caps.css, si no 0 */
    int              line_scale;     /* line-height del autor en % de la caja de línea; solo con caps.css, si no 0 */
    int              text_decoration;/* text-decoration del autor (OR de CSS_DECO_*); solo con caps.css, si no -1 */
    /* Extensiones de presentación de texto (Hito 23b-6); solo con caps.css, si no sus
     * defaults sin efecto. */
    int              font_family, text_transform, letter_spacing, word_spacing;
    int              shadow_dx, shadow_dy, shadow_color, opacity, valign, text_indent, white_space;
    /* Box model del autor (Hito 23b-3); solo con caps.css, si no 0 / PV_LEN_UNSET. */
    int              box_l, box_r;   /* insets izq/der px */
    int              box_w;          /* tope de ancho de contenido px, 0 = sin tope */
    int              box_center;     /* 1: margin: 0 auto */
    int              box_mt, box_mb; /* override de margen sup/inf px, o PV_LEN_UNSET (UA) */
    /* ... cont_* (contenedor flex/grid, transportado siempre) e input_* (RD_INPUT) ... */
} rd_block;

typedef struct rd_doc {
    rd_block *blocks;
    size_t    count;
    size_t    cap;
    int       has_images;  /* la página declaró al menos una imagen */
} rd_doc;

typedef enum rd_status { RD_OK = 0, RD_ERR_NULL_ARG, RD_ERR_OOM } rd_status;
```

## 2. API (pura, reentrante)

```c
rd_status      rd_build(const pv_view *view, rdp_caps caps,
                        const char *top_level_url, rd_doc **out);
void           rd_free(rd_doc *d);
size_t         rd_count(const rd_doc *d);
const rd_block *rd_at(const rd_doc *d, size_t i);
const char    *rd_kind_name(rd_kind k);          /* "heading"/"paragraph"/... */
const char    *rd_image_label(rdp_img_decision d); /* etiqueta del placeholder */
```

### `rd_build`
- `out == NULL` → `RD_ERR_NULL_ARG`. `view == NULL` se trata como vista vacía (doc con
  `count == 0`, `RD_OK`).
- Recorre la vista una vez:
  - `PV_TEXT` con `heading > 0` → `RD_HEADING` (`heading_level = heading`); si no → `RD_PARAGRAPH`.
  - `PV_LINK` → `RD_LINK`, `href` = destino del enlace (dato con procedencia; no se sigue aquí).
  - `PV_IMAGE` → `RD_IMAGE`, `href` = `src`, `text` = `alt`, e `img_decision =
    rdp_image_decision(caps, top_level_url, src, img_w, img_h)` (**Zero Trust**: re-evaluada por
    imagen).
- Si la vista declara imágenes y `!caps.images`, antepone un `RD_NOTICE` con
  `rdp_images_warning()`. `has_images` refleja si hubo alguna imagen.
- **Presentación del autor (`fg_rgb`/`bg_rgb`/`text_align`/`font_scale`/`line_scale` + `box_*`):** se
  propaga del `pv_run` a `RD_HEADING`/`RD_PARAGRAPH`/`RD_LINK` **solo si `caps.css`** (Secure/Privacy
  by Default: apagado); en otro caso queda en -1 (colores), 0 (align/font/box_l/r/w/center) o
  `PV_LEN_UNSET` (box_mt/box_mb → la GUI usa el margen UA) y la presentación usa el tema/UA. Son el
  estilo de autor de Hito 23/23b (de `<style>` + `style=`, vía `[[css]]`/`[[page_view]]`); el **box
  model** `box_*` (Hito 23b-3) se gatea aquí igual que los colores porque una caja del autor puede
  encoger el contenido a lo ilegible. El *gate* de CSS vive en una función pura y testeable. Las
  **extensiones de presentación de texto** (Hito 23b-6: `font_family`/`text_transform`/
  `letter_spacing`/`word_spacing`/`shadow_*`/`opacity`/`valign`/`text_indent`/`white_space`) se
  gatean igual; con `caps.css` apagado quedan en sus defaults sin efecto (0 / `PV_LEN_UNSET` / -1). El
  `list-style` NO viaja por aquí: ya está horneado en el texto del run por `page_view` (estructura).
- **Contenedor flex/grid del autor (`cont_id`/`cont_display`/`cont_gap`/`cont_justify`/`cont_cols`),
  flex por-item (`flex_grow`/`flex_shrink`/`flex_basis`/`flex_order`/`flex_direction`, Stage 3),
  identidad de ítem (`cont_item`), y **flex-wrap/row-gap/align-items/align-self**
  (`cont_wrap`/`cont_row_gap`/`cont_align_items`/`flex_align_self`, CSS layout expansion):** se
  transportan **siempre**, con o sin `caps.css`. La maquetación (cajas, columnas, márgenes,
  distribución flex incl. envoltura multilínea y alineación de eje cruzado, a qué ítem pertenece cada
  run) es estructura, no estilo del autor: no abre sockets ni filtra nada a la red, así que el camino
  seguro por defecto la incluye. Solo los **colores** del autor siguen gateados por `caps.css`.
  Defaults sin definir: `-1`/`-1`/`CSS_LEN_UNSET`/`CSS_LEN_UNSET`/`0`/`-1`/`0`/`-1`/`0`/`0`.
- `top_level_url` puede ser `NULL` (p. ej. un fichero local): las decisiones de imagen entonces
  **fallan cerrado** (`RDP_IMG_BLOCK_INVALID`) salvo que la capacidad esté apagada
  (`RDP_IMG_BLOCK_DISABLED`, que tiene precedencia).
- `text` y `href` se normalizan a UTF-8 bien formado (bytes inválidos → `?`): todo string del
  `rd_doc` es seguro de pintar (cairo rechaza UTF-8 inválido).

### `rd_kind_name` / `rd_image_label`
Cadenas estables, cortas, en inglés, para salida determinista (agent-friendly). Nunca `NULL`; un
valor de enum desconocido devuelve una cadena por defecto, nunca `NULL`.

### `rd_block_tag`
Etiqueta HTML canónica del bloque, para que la capa de presentación consulte su caja UA
(`[[box_style]]`) sin re-derivar el mapeo kind->etiqueta en el sitio de llamada: `RD_HEADING` ->
`h1`..`h6` (con `heading_level` acotado a 1..6), `RD_PARAGRAPH` -> `p`, `RD_LINK` -> `a`,
`RD_IMAGE` -> `img`, `RD_INPUT` -> `textarea`/`button`/`input` según `input_type`. `RD_NOTICE`
(banner del UA, no es un elemento HTML) y un bloque `NULL` devuelven `NULL`. Cadena estática (no
se posee). Pura y determinista.

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; cada imagen se revalida contra
  el gate. Salida determinista (testeable, agent-friendly).
- **Privacy/Secure by Default:** con capacidades cero (defecto) ninguna imagen se marca como
  cargable y el aviso de rastreo está presente siempre que haya imágenes.
- **Fail-closed:** sin `top_level_url` válido (https), las imágenes no se permiten.
- **Memoria:** `rd_doc` tiene dueño único; `rd_free` es el único liberador, idempotente y
  `NULL`-safe. El doc copia sus strings: no depende de que la `pv_view` siga viva.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 4. Tabla de estados

| Código | Condición |
| :-- | :-- |
| `RD_OK` | Documento construido (puede tener `count == 0`). |
| `RD_ERR_NULL_ARG` | `out` era `NULL`. |
| `RD_ERR_OOM` | Fallo de asignación. |

## 5. Fuera de alcance (este hito)

- Maquetación en píxeles, fuentes y colores: los pone el orquestador de presentación a partir del
  estilo **semántico** de cada bloque.
- Descarga/decodificado/pintado real de los bytes de la imagen (red + decodificador de formato):
  hito propio del orquestador; aquí solo se decide y se etiqueta el placeholder.
- Motor de cajas CSS de autor y mutación JS→repintado en vivo: hitos propios; sus capacidades se
  exponen en `rdp_caps`, pero su implementación no es de este módulo.
