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
- **Contenedor flex** (fila): reparte el eje principal con `flex_layout` (`grow`/`shrink`/`gap`/
  `justify-content`); el eje cruzado es `align-start` y la altura de la fila = máxima altura de hijo.
- **Contenedor grid**: `grid_cols` columnas iguales vía `flex_layout`, colocación fila-por-fila, con
  altura de fila = máxima altura de los hijos de esa fila.
- **Hoja** (nodo sin hijos): su altura es `content_h` (+ padding); su ancho lo fija el padre.
- **Anidamiento** arbitrario (con tope de profundidad) y `display:none` (no ocupa espacio).

## 2. Tipos

```c
typedef struct bt_node {
    bx_display      display;     /* BLOCK / FLEX / GRID / NONE; otros => hoja de bloque */
    bx_edges        margin;      /* px; lo usa el padre al colocar este nodo */
    bx_edges        padding;     /* px; interior de este nodo */
    /* parametros de contenedor (FLEX/GRID): */
    double          gap;         /* px entre hijos */
    fx_justify      justify;     /* reparto del eje principal en FLEX */
    size_t          grid_cols;   /* GRID: numero de columnas iguales (>=1) */
    /* este nodo como item flex de su padre FLEX: */
    double          grow, shrink, basis, min_main;
    /* hoja: altura del contenido en px (ignorada en contenedores, se calcula): */
    double          content_h;
    struct bt_node *children;    /* array de hijos (propiedad del llamante), o NULL */
    size_t          child_count;
    /* salida: rectangulo border-box relativo al origen del content-box del PADRE (px): */
    double          x, y, w, h;
} bt_node;

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
  - **flex**: arma los `fx_item` de los hijos (`basis`/`grow`/`shrink`/`min_main`), llama
    `fx_flex_line` sobre el ancho de contenido; cada hijo se recoloca en `x = padding.left + pos` y
    se recurre con su tamaño resuelto; altura = padding + máxima altura de hijo.
  - **grid**: `fx_grid_columns` + `fx_grid_cell` (fila-por-fila); altura de fila = máxima de sus
    hijos; altura total = Σ filas + `gap·(filas−1)` + padding.
  - **none**: `w = h = 0` (no se coloca; el padre lo salta).
- Hijos `display:none` no ocupan hueco (ni slot flex/grid) y reciben `x=y=w=h=0`.

### Topes (anti-DoS)
- `BT_MAX_DEPTH` (profundidad de recursión) y `BT_MAX_CHILDREN` (hijos por contenedor) están topados;
  excederlos → `BT_ERR_RANGE` (falla cerrado, sin desbordar la pila). `grid_cols == 0` o
  `> BT_MAX_CHILDREN` con hijos en un GRID → `BT_ERR_RANGE`. `gap < 0` en flex/grid → `BT_ERR_RANGE`.

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
- Eje cruzado más allá de `align-start` (`align-items: stretch/center/end`, `align-self`), `flex-wrap`,
  `flex-direction: column`, `order`.
- Grid real: pistas mixtas `px`/`fr`/`auto`/`minmax`, `grid-template-areas`, colocación por línea.
- Colapso de márgenes padre-hijo y a través de cajas vacías (solo se colapsan hermanos adyacentes).
- Porcentajes, `width`/`height` de autor, posicionamiento absoluto/flotantes.
- Construir el árbol desde el DOM y aplicar los rectángulos a Cairo: eso es el orquestador (la GUI).
