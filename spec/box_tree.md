# spec/box_tree.md — Árbol de cajas y layout recursivo (block / flex / grid)

> Módulo `box_tree` (prefijo `bt_`). Lógica **pura, sin I/O, sin asignación dinámica, sin estado
> global**: dado un árbol de cajas (cada nodo con su `display`, márgenes/padding en px, factores flex
> y, en las hojas, su tamaño de contenido) y un ancho disponible, calcula la posición y el tamaño de
> cada nodo. No mide texto, no pinta, no toca el DOM. Metodología: SDD + TDD. Hito 7. Cierra el
> camino abierto por `[[box_style]]` (qué es cada caja) y `[[flex_layout]]` (cómo reparte el espacio
> un contenedor): aquí se **anida** y se resuelve el árbol completo.

## 0. Por qué existe

`flex_layout` resuelve **una** línea/eje; `box_style` clasifica **un** elemento. Una página real es
un **árbol anidado** de contenedores. Recorrer ese árbol —apilar bloques con colapso de márgenes,
delegar los contenedores flex/grid en `flex_layout`, y bajar recursivamente con el ancho ya resuelto—
es aritmética pura: entra un árbol con tamaños de hoja, salen rectángulos. Es exactamente la lógica
que la doctrina manda aislar del pintor: el punto donde un documento hostil podría forzar recursión
infinita, desbordes o divisiones por cero, **auditable sin Wayland**.

El llamante (la GUI, orquestador) construye el árbol desde el DOM midiendo el texto con Cairo y
convirtiendo los `em` de `box_style` a px; `bt_layout` solo resuelve la geometría. Componer las
coordenadas absolutas (acumulando el origen de cada padre) también es del llamante.

## 1. Alcance ("básico", honesto)

- **Contenedor block**: hijos apilados en vertical, ancho = ancho de contenido del padre; **colapso
  de márgenes** entre hermanos (`max(margen_inferior_previo, margen_superior_actual)`).
- **Contenedor flex**: reparte el eje principal con `flex_layout` (`grow`/`shrink`/`gap`/
  `justify-content`). Sin `wrap` (el caso por defecto, `node->wrap == 0`), TODOS los hijos van en
  una línea — comportamiento idéntico al de antes de `flex-wrap` (byte-idéntico, ningún llamante
  previo se ve afectado). Con `wrap`, los hijos se empaquetan en **múltiples líneas** por su `basis`
  (empaquetado voraz: un hijo que desbordaría la línea abre una nueva), las líneas se apilan
  verticalmente con el gap del eje cruzado (`row_gap` si está fijado, si no `gap`). Dentro de una
  línea, cada hijo se alinea en el eje cruzado según su `align` resuelto (`BT_ALIGN_START`/`_CENTER`/
  `_END`; `_STRETCH` se aproxima en v1 a `_START` — el motor no tiene forma de forzar que el
  contenido de una hoja crezca para llenar la línea).
- **Contenedor grid**: `grid_cols` columnas vía `flex_layout`, colocación fila-por-fila, con
  altura de fila = máxima altura de los hijos de esa fila. El gap de **columna** siempre es `gap`; el
  de **fila** es `row_gap` si `has_row_gap` está fijado (author `row-gap`, distinto de `column-gap`),
  si no cae también a `gap` (un `gap: N` simple sirve a los dos ejes, comportamiento previo intacto).
  **Pistas con tamaño (2026-07-11):** `grid_track`/`grid_ntrack` (puntero del llamante, `NULL` =
  todas iguales) codifican por pista `0` = auto (`1fr`), `> 0` = px fijos, `< 0` = peso fr ×100;
  se resuelven con `fx_grid_columns_weighted` (fijas primero, el resto proporcional al peso).
  **Span de columna:** el `grid_span` de un hijo (≤ 0 = 1) lo coloca `fx_grid_place_span` ocupando
  N columnas consecutivas + los gaps intermedios (acotado a las columnas restantes de su fila;
  si no cabe, salta de fila — auto-placement CSS). El span de FILA no se coloca (v1).
- **Hoja** (nodo sin hijos): su altura es `content_h` (+ padding); su ancho lo fija el padre.
- **Anidamiento** arbitrario (con tope de profundidad) y `display:none` (no ocupa espacio).

## 2. Tipos

```c
typedef struct bt_node {
    bx_display      display;     /* BLOCK / FLEX / GRID / NONE; otros => hoja de bloque */
    bx_edges        margin;      /* px; lo usa el padre al colocar este nodo */
    bx_edges        padding;     /* px; interior de este nodo */
    /* parametros de contenedor (FLEX/GRID): */
    double          gap;         /* px entre hijos (FLEX: eje principal; GRID: columnas) */
    fx_justify      justify;     /* reparto del eje principal en FLEX */
    size_t          grid_cols;   /* GRID: numero de columnas (>=1) */
    const int      *grid_track;  /* GRID: tamanos de pista (0 auto / >0 px / <0 fr x100),
                                  * NULL (default de zero-init) = columnas iguales */
    size_t          grid_ntrack; /* pistas validas en grid_track (resto = auto) */
    int             wrap;        /* FLEX: no-cero empaqueta en varias lineas (flex-wrap);
                                  * 0 (default de zero-init) = comportamiento previo, sin cambios */
    double          row_gap;     /* gap del eje cruzado (filas GRID / lineas FLEX envueltas);
                                  * solo se consulta si has_row_gap esta fijado */
    int             has_row_gap; /* 0 (default de zero-init): `gap` sirve a los dos ejes, igual
                                  * que antes de esta propiedad. 1: usar row_gap en vez de `gap`
                                  * para el eje de fila/cruzado (author `row-gap`) */
    /* este nodo como item flex de su padre FLEX: */
    double          grow, shrink, basis, min_main;
    /* este nodo como item grid de su padre GRID (2026-07-11): columnas que ocupa
     * (grid-column: span N); <= 0 (default de zero-init) = 1 columna. */
    int             grid_span;
    int             align;       /* BT_ALIGN_*: alineacion en el eje cruzado de este item dentro
                                  * de su linea (ya resuelta por el llamante desde align-self o
                                  * el align-items del contenedor) */
    /* hoja: altura del contenido en px (ignorada en contenedores, se calcula): */
    double          content_h;
    struct bt_node *children;    /* array de hijos (propiedad del llamante), o NULL */
    size_t          child_count;
    /* salida: rectangulo border-box relativo al origen del content-box del PADRE (px): */
    double          x, y, w, h;
} bt_node;

/* BT_ALIGN_START (0, default) / _CENTER / _END / _STRETCH (v1: igual que _START). */
```

## 2b. `flex-wrap` / `row-gap` / `align-items`/`align-self` (compatibilidad hacia atrás)

Las tres extensiones se diseñaron para que **todo árbol construido antes de que existieran** (todo
llamante existente, toda prueba existente) produzca **exactamente** la misma geometría, sin tocar un
solo sitio de llamada:

- `wrap`/`align` son `int` que bajo `memset`/inicializador-designado quedan en `0` — `0` es
  `BT_ALIGN_START` (comportamiento previo: los hijos se alinean al origen del eje cruzado) y "sin
  wrap" (una sola línea, el algoritmo previo exacto).
- `row_gap`/`has_row_gap`: en vez de usar un centinela negativo en `row_gap` (que colisionaría con el
  `0.0` que deja `memset`), se añadió el booleano explícito `has_row_gap`. Con `has_row_gap == 0`
  (el default de zero-init) el motor usa `gap` para el eje de fila/cruzado exactamente como antes de
  que `row-gap` existiera — nunca `0.0` por accidente.

```c

typedef enum bt_status {
    BT_OK = 0,
    BT_ERR_NULL_ARG,  /* root == NULL */
    BT_ERR_RANGE      /* profundidad/hijos/columnas sobre el tope, o gap negativo en flex/grid */
} bt_status;
```

## 3. API (pura, reentrante)

```c
bt_status bt_layout(bt_node *root, double avail_w);
```

- `root == NULL` → `BT_ERR_NULL_ARG`. `avail_w < 0` se trata como 0.
- Fija `root->x = root->y = 0` y resuelve todo el subárbol. Los `x`/`y` de cada nodo son **relativos
  al content-box de su padre**; `w`/`h` son el **border-box** (incluyen padding, no el margen). El
  margen del propio `root` se ignora en la raíz (lo posiciona el llamante).
- Para cada nodo, según `display`:
  - **hoja** (`child_count == 0`): `w = avail_w`, `h = content_h + padding vertical`.
  - **block**: cada hijo se baja con `avail_w` = ancho de contenido − sus márgenes laterales; se
    apila con colapso de márgenes; la altura del contenedor incluye el último margen inferior y el
    padding.
  - **flex**: sin `wrap`, una sola "línea" con todos los hijos (comportamiento previo exacto). Con
    `wrap`, los hijos se particionan en líneas empaquetando voraz por `basis` (un hijo que
    desbordaría `avail_w` abre línea nueva); cada línea arma sus `fx_item` (`basis`/`grow`/`shrink`/
    `min_main`) y llama `fx_flex_line` sobre el ancho de contenido; los hijos se recolocan en
    `x = padding.left + pos`, se recurre con su tamaño resuelto, y luego se desplazan en el eje
    cruzado dentro de su línea según `align` (`_CENTER`/`_END` restan de `altura_línea − altura_hijo`;
    `_START`/`_STRETCH` no desplazan). Las líneas se apilan con el gap cruzado (`row_gap` si
    `has_row_gap`, si no `gap`); altura total = Σ alturas de línea + gap·(líneas−1) + padding.
  - **grid**: `fx_grid_columns` (siempre con `gap`, columna) + `fx_grid_cell` (fila-por-fila); altura
    de fila = máxima de sus hijos; altura total = Σ filas + `row_gap_efectivo·(filas−1)` + padding,
    donde `row_gap_efectivo` es `row_gap` si `has_row_gap`, si no `gap`.
  - **none**: `w = h = 0` (no se coloca; el padre lo salta).
- Hijos `display:none` no ocupan hueco (ni slot flex/grid) y reciben `x=y=w=h=0`.

### Topes (anti-DoS)
- `BT_MAX_DEPTH` (profundidad de recursión) y `BT_MAX_CHILDREN` (hijos por contenedor) están topados;
  excederlos → `BT_ERR_RANGE` (falla cerrado, sin desbordar la pila). `grid_cols == 0` o
  `> BT_MAX_CHILDREN` con hijos en un GRID → `BT_ERR_RANGE`. `gap < 0` en flex/grid → `BT_ERR_RANGE`;
  `has_row_gap && row_gap < 0` → `BT_ERR_RANGE` igual.

## 4. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; el árbol y sus tamaños son dato
  hostil con procedencia.
- **Determinista:** mismo árbol + mismo ancho → misma geometría (testeable, agent-friendly).
- **Acotado:** profundidad e hijos topados; sin VLA ni asignación dinámica (scratch de pila de tamaño
  fijo `BT_MAX_CHILDREN`). La recursión termina (cada nivel decrementa el presupuesto de profundidad).
- **Falla cerrado:** `NULL`/rangos inválidos → error; nunca escribe fuera de los nodos del árbol.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 5. Tabla de estados

| `bt_status` | Condición |
| :-- | :-- |
| `BT_OK` | Árbol resuelto. |
| `BT_ERR_NULL_ARG` | `root == NULL`. |
| `BT_ERR_RANGE` | Profundidad/hijos/columnas sobre el tope, o `gap` negativo en flex/grid. |

## 6. Fuera de alcance

- Inline / line-boxes / wrapping de texto: una hoja representa contenido ya medido (lo hace la GUI con
  Cairo); aquí no se parte texto.
- `align-items`/`align-self` **(cerrado, este batch):** `_START`/`_CENTER`/`_END` desplazan un item
  dentro de su línea; `_STRETCH` se aproxima a `_START` (no hay forma de forzar que una hoja crezca
  para llenar la línea). `flex-wrap` **(cerrado, este batch):** empaquetado voraz por `basis`,
  `wrap-reverse` no invierte el eje cruzado (se trata como `wrap` plano). `row-gap` **(cerrado, este
  batch):** distinto de `gap`/column-gap en GRID y en las líneas envueltas de FLEX. `flex-direction:
  column`/`order` ya estaban resueltos por el llamante (`gui/browser_ui.c`), no por `box_tree` mismo.
  Sigue fuera: `align-content` (distribución de las líneas SOBRE el eje cruzado cuando sobra espacio
  vertical), `justify-items`, reversión visual de `*-reverse`.
- Grid real: pistas mixtas `px`/`fr`/`auto`/`minmax` (pesos, no solo conteo — `css` ya cuenta
  `repeat()`/`minmax()` correctamente, pero cada pista sigue siendo una columna de igual ancho aquí),
  `grid-template-areas`, colocación por línea (`grid-column`/`grid-row: span N` se resuelve en `css`
  pero no llega aquí todavía), alineación en el eje cruzado por-fila.
- Colapso de márgenes padre-hijo y a través de cajas vacías (solo se colapsan hermanos adyacentes).
- Porcentajes, `width`/`height` de autor, posicionamiento absoluto/flotantes.
- Construir el árbol desde el DOM y aplicar los rectángulos a Cairo: eso es el orquestador (la GUI).
