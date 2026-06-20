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
```

## 3. API (pura, reentrante)

```c
bx_box     bx_default_for_tag(const char *tag);
bx_status  bx_parse_display(const char *token, bx_display *out);
const char *bx_display_name(bx_display d);
```

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

## 4. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; la etiqueta y el token son dato
  hostil con procedencia.
- **Determinista:** misma entrada → misma salida (testeable, agent-friendly).
- **Falla cerrado / seguro por defecto:** etiqueta desconocida → caja inerte en línea sin espaciado;
  `display` no reconocido → `BX_ERR_SYNTAX` (no se reconfigura el motor).
- **Sin asignación dinámica:** opera sobre buffers de pila acotados y devuelve por valor.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 5. Tabla de estados (`bx_parse_display`)

| `bx_status` | Condición |
| :-- | :-- |
| `BX_OK` | Token reconocido; `*out` es el `bx_display`. |
| `BX_ERR_NULL_ARG` | `token` u `out` es `NULL`. |
| `BX_ERR_SYNTAX` | Vacío, no cabe, o palabra clave no soportada. |

## 6. Fuera de alcance

- Resolver geometría (anchos, posiciones, line-boxes): eso es `flex_layout` y el pintor.
- `width`/`height`/`border`/`gap`/`flex`/`grid-template` del autor: los consume `flex_layout`; aquí
  solo se clasifica el `display`.
- Herencia y cascada CSS, selectores, especificidad: el motor aplica la hoja UA por etiqueta y, a lo
  sumo, un `display` en línea gateado por el llamante.
- `table`/`table-*`, `ruby`, `contents`, `flow-root` y demás valores de `display` raros.
- Extraer el token desde el atributo `style`/la hoja del autor: lo hace `page_view`/`render_doc`.
