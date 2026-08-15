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
double      fx_auto_min_size(double min_content, double basis, double author_min,
                            int scroll_container);
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

#### Contrato del llamante: `basis` es el tamaño BASE, no un reparto (2026-07-27)

`fx_flex_line` es puro y no mide texto: el `basis` que recibe **es** el tamaño base del ítem. El
orquestador (`layout_container`, `gui/browser_ui.c`) lo resolvía como un **reparto en partes
iguales** (`content_w / n`) cuando el ítem no declaraba `flex-basis`, y solo entraba al motor flex
si algún ítem declaraba una propiedad flex. Dos consecuencias, ambas visibles contra Firefox:

- `justify-content` **no hacía nada**: columnas iguales llenan la línea, así que `leftover` era 0 y
  no había sobrante que repartir. `space-between`, `center`, `space-around` eran no-ops.
- Cada ítem se **estiraba** a su parte: una barra de navegación de tres enlaces ocupaba todo el
  ancho de la página en vez de encogerse a su contenido.

Ahora **todo** contenedor flex pasa por el motor, y el `basis` de un ítem sin `flex-basis` es
(en este orden): un `width` de autor, o su **ancho de max-content** medido —
`measure_item_content_w` fluye los bloques del ítem por el mismo `flow_text_block` que los maqueta,
en un layout de usar y tirar, así la medida no puede divergir del render — **más su padding, borde
y margen horizontal**, acotado al ancho del contenedor. El margen del ítem forma parte del espacio
que ocupa en el eje principal (`kid->w` es la caja de margen; la caja de borde se inserta por
`ml`), que es lo que separa los ítems cuando el autor usa `margin-right` en vez de `gap`.

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

### `fx_auto_min_size` (2026-08-11)

*Automatic minimum size* de un ítem flex sobre el eje principal (CSS Flexbox §4.5): lo que resuelve
`min-width: auto`, que es el valor **inicial** y por lo tanto el caso de casi todo ítem de la web.
Es el piso que `fx_flex_line` no debe cruzar al encoger.

Antes esto era un **1.0 px hardcodeado** en el llamante. Con un piso de ~0, una línea que desborda
tritura cada ítem hasta una astilla y su texto cae a **un carácter por línea** — el síntoma que se
venía atribuyendo a "el contenedor reparte 0 px".

- `author_min >= 0` ⇒ gana **tal cual**, más grande o más chico: si el autor declaró `min-width`,
  la propiedad ya no es `auto` y el mínimo automático no aplica.
- `scroll_container != 0` (overflow distinto de `visible`) ⇒ **0**. Es lo que hace funcionar el
  idioma casi universal de truncado con `overflow:hidden`.
- Si no: `min(min_content, basis)` — la *content size suggestion* acotada por la *specified size
  suggestion*, para que un ítem que el autor hizo chico no se infle por una palabra larga.
- Entradas negativas se tratan como 0; el resultado **nunca** es negativo. Puro, total, sin
  asignación.

`min_content` y `basis` vienen en las mismas unidades (border-box + márgenes) que `fx_item.basis`.
El llamante mide `min_content` fluyendo el ítem al extremo angosto de la misma vara con la que mide
`max-content`, y **se saltea esa medición** cuando no puede cambiar la respuesta.

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

## Colocación explícita de ítems de grilla (2026-08-14)

`fx_grid_place_span` acepta `fixed_row`/`fixed_col` (arreglos opcionales, `-1` = auto).
El algoritmo pasa a ser de **dos pases**, que es el orden que manda CSS Grid 1:

1. **§8.3, colocación explícita.** Todo ítem con celda declarada toma su rectángulo y
   lo marca ocupado, ANTES de colocar ningún ítem automático.
2. **§8.5, auto-colocación.** El cursor recorre la grilla y salta las celdas ya
   ocupadas.

Hacerlo en un solo pase intercalado dejaría que un ítem automático anterior en orden de
documento se sentara en una celda que un ítem nombrado posterior posee.

Con ambos arreglos en `NULL` el pase 1 no coloca nada y el pase 2 es **bit a bit** el
algoritmo anterior, así que ninguna grilla sin nombres cambia.

Una celda fija fuera de la grilla se **recorta** al rango válido en vez de descartarse:
un ítem en el borde es un error más chico que un ítem que desaparece. La fila NO está
acotada por la cantidad de ítems (un área nombrada puede legítimamente vivir en la cuarta
fila de una plantilla con un solo ítem); la única cota es el arreglo de ocupación.

De paso, el número de filas pasó a ser el **máximo sobre todos los ítems** en vez de la
fila del último: con colocación explícita el orden de documento ya no implica orden de
fila, así que leer el último ítem cortaba toda fila que un área nombrada hubiera puesto
por debajo de él.

Las funciones de áreas nombradas (`fx_grid_area_hash`, `fx_grid_areas_parse`,
`fx_grid_area_rect`) tienen su contrato completo en **`spec/grid_areas.md`**.
