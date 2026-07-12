# spec/flex_layout.md — Solver puro de flexbox (1D) y grid básico

> Módulo `flex_layout` (prefijo `fx_`). Lógica **pura, sin I/O, sin estado global, sin asignación
> dinámica**: dado el tamaño del contenedor y los parámetros de cada ítem, calcula posiciones y
> tamaños a lo largo del eje principal. No mide texto, no pinta, no toca el DOM. Metodología: SDD +
> TDD. Hito 7. Es la continuación de `[[box_style]]`: cuando un elemento se clasifica
> `BX_DISPLAY_FLEX`/`BX_DISPLAY_GRID`, este solver resuelve la geometría.

## 0. Por qué existe

Distribuir el espacio entre los hijos de un contenedor flex (crecer/encoger según factores, repartir
el espacio sobrante con `justify-content`) o repartir un ancho en columnas de grid es **aritmética
pura**: entran números (tamaños base, factores, hueco, ancho disponible) y salen números (posición y
tamaño de cada ítem). Es exactamente la clase de lógica que la doctrina manda aislar en funciones
puras testeables, separadas del pintor (que solo aplica los rectángulos resultantes a Cairo).

Aislarlo así permite auditar el algoritmo de flex —el punto donde un documento hostil podría intentar
provocar overflow o división por cero— sin Wayland ni red, y reutilizarlo en un único sitio probado.

## 1. Alcance ("básico", honesto)

- **Flex de una sola línea** a lo largo del **eje principal** (sin `flex-wrap`). El eje cruzado
  (`align-items`, altura de la línea) lo decide el orquestador con las alturas naturales de los hijos
  (fuera de alcance aquí).
- `flex-grow`, `flex-shrink` (con congelado iterativo al llegar al mínimo), `flex-basis`, `gap`.
- `justify-content`: `start`, `end`, `center`, `space-between`, `space-around`, `space-evenly`.
- **Grid básico**: `ncols` columnas iguales (`repeat(ncols, 1fr)`) separadas por `gap`, más la
  colocación fila-por-fila de los ítems. Pistas con tamaños mixtos (`px`/`fr`/`auto`), `grid-template`
  explícito y el eje de filas quedan fuera de alcance.

## 2. Tipos

```c
typedef enum fx_justify {
    FX_JUSTIFY_START = 0, FX_JUSTIFY_END, FX_JUSTIFY_CENTER,
    FX_JUSTIFY_SPACE_BETWEEN, FX_JUSTIFY_SPACE_AROUND, FX_JUSTIFY_SPACE_EVENLY
} fx_justify;

typedef struct fx_item {   /* todos en px; los negativos se tratan como 0 */
    double basis;          /* flex-basis: tamaño principal preferido */
    double grow;           /* flex-grow */
    double shrink;         /* flex-shrink */
    double min;            /* tamaño principal mínimo; nunca encoge por debajo */
} fx_item;

typedef struct fx_result { double pos; double size; } fx_result; /* offset y tamaño en el eje */

typedef enum fx_status {
    FX_OK = 0,
    FX_ERR_NULL_ARG,  /* puntero requerido NULL con n/ncols > 0 */
    FX_ERR_RANGE      /* avail/gap negativos, o n/ncols por encima del tope */
} fx_status;
```

## 3. API (pura, reentrante)

```c
fx_status   fx_flex_line(const fx_item *items, size_t n, double avail, double gap,
                         fx_justify justify, fx_result *out);
fx_status   fx_grid_columns(double avail, size_t ncols, double gap,
                            double *col_x, double *col_w);
fx_status   fx_grid_columns_weighted(double avail, size_t ncols, double gap,
                                     const int *track, size_t ntrack,
                                     double *col_x, double *col_w);
void        fx_grid_cell(size_t index, size_t ncols, size_t *row, size_t *col);
fx_status   fx_grid_place_span(size_t nitems, size_t ncols, const int *span,
                               size_t *out_row, size_t *out_col);
const char *fx_justify_name(fx_justify j);
```

### `fx_flex_line`
- `n == 0` → `FX_OK` sin escribir nada (`items`/`out` pueden ser `NULL`).
- Con `n > 0`: `items == NULL` u `out == NULL` → `FX_ERR_NULL_ARG`.
- `avail < 0`, `gap < 0`, o `n > FX_MAX_ITEMS` → `FX_ERR_RANGE`.
- Los campos negativos de un ítem (`basis`/`grow`/`shrink`/`min`) se **tratan como 0** (CSS los
  acota; determinista, no inventa números mágicos).
- Algoritmo (flexbox de una línea):
  1. `base_total = Σ basis + gap·(n−1)`; `free = avail − base_total`.
  2. Si `free ≥ 0` y `Σ grow > 0`: cada ítem `size = basis + free · grow/Σgrow` (reparto por
     crecimiento; sin máximo, una pasada exacta). Si `Σ grow == 0`, los tamaños quedan en `basis` y
     el sobrante lo reparte `justify-content`.
  3. Si `free < 0`: encogimiento **iterativo** ponderado por `shrink·basis`; un ítem que caería por
     debajo de su `min` se fija en `min` y se **congela**, y se reparte de nuevo entre el resto hasta
     que nadie más se congela. Si nada puede encoger, los ítems mantienen `basis` (overflow, como en
     CSS).
  4. Posicionado: `used = Σ size + gap·(n−1)`, `leftover = avail − used`. Si `leftover > 0` (solo
     ocurre cuando los ítems no crecieron a llenar la línea), `justify-content` reparte el sobrante:
     `start` (todo al final libre), `end`, `center`, `space-between` (entre ítems; con un solo ítem
     equivale a `start`), `space-around` (mitad a cada lado), `space-evenly` (huecos iguales). El
     `gap` se respeta siempre y el sobrante se **suma** a él.
- Escribe `n` `fx_result` en `out` (eje principal). El llamante aporta `out` (sin asignación).

### `fx_grid_columns`
- `ncols == 0` → `FX_OK` sin escribir nada. `ncols > FX_MAX_ITEMS`, `avail < 0` o `gap < 0` →
  `FX_ERR_RANGE`. Con `ncols > 0`, `col_x`/`col_w` no pueden ser `NULL`.
- `col_w = max(0, (avail − gap·(ncols−1)) / ncols)` (igual para todas; se acota a 0 si no cabe).
  `col_x[k] = k · (col_w + gap)`.

### `fx_grid_columns_weighted` (2026-07-11)
- Mismos contratos de rango/NULL que `fx_grid_columns`. `track[i]` codifica el tamaño de la pista
  `i`: `0` = `auto` (peso `1fr`), `> 0` = **px fijos**, `< 0` = peso **fr ×100** (`2fr` → `-200`).
  Pistas con `i >= ntrack` (o `track == NULL`) son `auto`.
- Algoritmo: las pistas fijas reservan sus px primero; el resto
  (`avail − gaps − Σfijas`, acotado a ≥ 0) se reparte proporcional al peso fr. Todo-`auto`
  reproduce **byte-idéntico** el reparto igualitario de `fx_grid_columns`. Si las fijas exceden
  `avail`, las fr quedan en 0 (overflow a la derecha, como CSS).

### `fx_grid_cell`
- `row = index / ncols`, `col = index % ncols` (colocación fila-por-fila). `ncols == 0` →
  `row = col = 0` (defensivo, sin dividir por cero).

### `fx_grid_place_span` (2026-07-11)
- Colocación fila-por-fila con `grid-column: span N`: `span[i]` (≤ 0 o `NULL` = 1) se acota a
  `[1, ncols]`; si el span no cabe en las columnas restantes de la fila, el ítem **salta a la fila
  siguiente** (auto-placement CSS). Escribe fila y columna inicial por ítem. `nitems == 0` → `FX_OK`;
  `ncols == 0`, `nitems > FX_MAX_ITEMS` o punteros de salida NULL → error (falla cerrado).

### `fx_justify_name`
- Nombre en inglés, corto y estable (`"start"`, `"space-between"`, ...) para salida estructurada.
  Nunca `NULL`; valor desconocido → `"start"`.

## 4. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; las dimensiones son dato hostil.
- **Determinista:** misma entrada → misma salida (testeable, agent-friendly).
- **Acotado / anti-DoS:** `n`/`ncols` se topan en `FX_MAX_ITEMS`; sin VLAs ni asignación dinámica
  (arrays de pila de tamaño fijo). El bucle de encogimiento converge en ≤ `n` pasadas (cada pasada
  congela al menos un ítem o termina).
- **Falla cerrado:** punteros NULL o rangos inválidos → error; nunca escribe fuera de `out`.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 5. Tabla de estados

| `fx_status` | Condición |
| :-- | :-- |
| `FX_OK` | Resuelto (o no-op con `n`/`ncols` == 0). |
| `FX_ERR_NULL_ARG` | Puntero requerido NULL con `n`/`ncols` > 0. |
| `FX_ERR_RANGE` | `avail`/`gap` negativos, o `n`/`ncols` > `FX_MAX_ITEMS`. |

## 6. Fuera de alcance

- `flex-wrap` y múltiples líneas; el eje cruzado (`align-items`/`align-content`/`align-self`).
- Tamaños base de contenido (`flex-basis: auto`/`content`): el llamante resuelve `basis` antes.
- Grid real restante: `grid-template-areas`, posicionamiento por línea (`grid-column: 2 / 4`),
  `grid-auto-flow: column`, `span` de FILA (solo el de columna se coloca). Las pistas mixtas
  `px`/`fr`/`auto` y `minmax` (componente max) ya se resuelven vía `fx_grid_columns_weighted`
  (2026-07-11).
- Aplicar los rectángulos a Cairo / construir el árbol de cajas: eso es el orquestador (la GUI).
