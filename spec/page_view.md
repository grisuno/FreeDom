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
} pv_run;

typedef struct pv_view { pv_run *runs; size_t count; size_t cap; } pv_view;
```

En un run que no es imagen, `src == NULL` y `img_w == img_h == -1`. En un `PV_IMAGE`, `text` es el
texto alternativo (`alt`, puede ser cadena vacía) y `href == NULL` (la imagen no es un enlace).

**Color del autor (`fg_rgb`):** se extrae del ancestro más cercano que fije un `color` (atributo
`style` en línea con declaración `color:`, o el `<font color>` heredado), parseado por el módulo
puro `css_color`; `background-color` nunca se confunde con `color`; un valor no parseable → -1. Es
dato de presentación: `render_doc` solo lo propaga si la capacidad de CSS del autor está activa, y
nunca implica una petición de red (el color en línea no filtra nada). Ambos `pv_append*` inicializan
`fg_rgb` a -1; `pv_set_color` lo fija en el último run.

## 3. API

```c
pv_status pv_build(const hp_document *doc, pv_view **out); /* recorre el árbol (Lexbor) */
pv_view  *pv_new(void);                                    /* vista vacía (deserializador IPC) */
pv_status pv_append(pv_view *v, pv_kind kind, int heading, int block_break,
                    const char *text, const char *href);   /* texto/enlace; copia text/href */
pv_status pv_append_image(pv_view *v, int heading, int block_break,
                          const char *alt, const char *src, int w, int h); /* PV_IMAGE */
void          pv_set_color(pv_view *v, int fg_rgb);        /* color del autor del ultimo run */
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
- **Salto de bloque**: `block_break != 0` cuando el bloque contenedor más cercano del run difiere
  del bloque del run anterior, o cuando un `<br>`/`<hr>` precede al run. Bloques: `body, div, p,
  h1..h6, ul, ol, li, section, article, header, footer, nav, main, aside, blockquote, pre, table,
  tr, figure, form, fieldset, dl, dt, dd`.
- **UTF-8**: `text` se normaliza a UTF-8 bien formado (bytes inválidos → `?`), porque el renderer
  (cairo) rechaza UTF-8 inválido y muchas páginas llegan en codificaciones legadas (Latin-1).

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
