# table_layout (`tl_`) — anchos de columna de una tabla

Módulo puro: aritmética sobre `double`, sin I/O, sin asignación, sin estado global, reentrante.
Implementa el *automatic table layout* de CSS 2.1 §17.5.2.2 (con el reparto de sobrante de
css-tables-3 §3.9) para el motor de layout del lado confiable. No toca el DOM ni el IPC: el
llamador (`layout_container`) mide las celdas y este módulo decide los anchos.

## Por qué existe

La tabla se maquetaba como un grid sintetizado con dos atajos: columnas = contenido más ancho
**solo** si ninguna celda tenía `colspan`, y la tabla **encogía** siempre a la suma (el atributo
`width` se ignoraba). Hacker News — `<table width="85%">` con una fila de subtexto `colspan=2`
bajo cada titular — caía al reparto en tercios iguales o directamente a flujo.

## Entradas

- `tl_cell { col, span, min_w, max_w, decl_w, pct }` por celda: columna de inicio (0-based),
  columnas que ocupa (≥ 1), ancho mínimo (palabra más larga + bordes), ancho máximo (contenido
  en una línea + bordes), ancho declarado en px del border box (`< 0` = `auto`) y ancho
  declarado en porcentaje de la tabla, en per-mille (`0` = ninguno).
- `ncols` (1..`TL_MAX_COLS`), `gap` (espaciado entre columnas, px), `avail` (ancho del bloque
  contenedor), `table_w` (ancho declarado de la tabla ya resuelto a px, `< 0` = `auto`).

## Salida

`out[ncols]`: ancho usado de cada columna. `tl_columns` devuelve el ancho total de la tabla
(suma de columnas + gaps).

## Reglas (Dado–Cuando–Entonces)

1. **Dado** celdas de una columna (`span == 1`) **entonces** `min[c]`/`max[c]` son el máximo de
   sus `min_w`/`max_w`; un `decl_w ≥ 0` sube `max[c]` a `max(decl_w, min_w)` y marca la columna
   como *dimensionada* (no recibe sobrante mientras exista una columna `auto`).
2. **Dado** una celda con `span > 1` cuyo mínimo (o máximo) supera la suma de las columnas que
   cubre (más los gaps interiores) **entonces** la diferencia se reparte entre esas columnas en
   proporción a su `max` (a partes iguales si todos son 0). Se procesan en orden de `span`
   creciente (§17.5.2.2 paso 3).
3. **Dado** `table_w < 0` (auto) **entonces** el ancho usado es `min(suma max, avail)`, con
   piso en la suma de mínimos: si los mínimos no caben, la tabla **desborda** (regla 6).
4. **Dado** `table_w ≥ 0` **entonces** el ancho usado es `max(table_w, suma min)`.
5. **Reparto** del ancho usado `W` (sin gaps):
   - `W ≥ suma max`: cada columna toma su `max` y el sobrante va a las columnas `auto` en
     proporción a su `max` (a todas, si ninguna es `auto`; a partes iguales si la base es 0).
   - `suma min ≤ W < suma max`: `min[c] + (W − suma min)·(max[c] − min[c])/(suma max − suma min)`.
6. **Dado** una suma de mínimos mayor que el bloque contenedor **entonces** las columnas
   conservan su mínimo y la tabla desborda (CSS 2.1 §17.5.2.2: el min-content es un piso).
   Encogerlas en proporción partía una celda `nowrap` a una letra por línea. El llamador puede
   volver a resolver con mínimos más bajos si los suyos no son fiables.
7. **Columnas en porcentaje** (`width: N%`, el navbox de MediaWiki: etiqueta `1%`, contenido
   `100%`). **Dado** una tabla con ancho declarado **entonces** cada columna con porcentaje
   toma primero `N%` del ancho usado, con piso en su mínimo; los porcentajes se acotan en orden
   de columna para no sumar más de 100 %. El resto va a las demás columnas por la regla 5. Si
   los pisos sobregiran la tabla (o dejan a las demás bajo su mínimo), la diferencia se
   devuelve desde las columnas en porcentaje con holgura sobre su mínimo. Sin columnas `auto`,
   el sobrante se reparte por porcentaje. **Dado** una tabla `auto` **entonces** el porcentaje
   se ignora (no hay ancho del que tomar parte). `tl_intrinsic` lo ignora siempre.

## Errores / fail-closed

| Entrada | Resultado |
| :-- | :-- |
| `out == NULL`, `ncols == 0`, `ncols > TL_MAX_COLS` | devuelve 0, no escribe |
| `cells == NULL` con `n > 0` | se trata como `n = 0` |
| celda con `col ≥ ncols` | ignorada; `col + span > ncols` se recorta |
| `span < 1` | tratado como 1 |
| ancho no finito o negativo (`NaN`, `±inf`, `< 0` en min/max) | tratado como 0 |
| ancho mayor que `TL_WIDTH_MAX` (1e9 px) | acotado a `TL_WIDTH_MAX` (sumas siempre finitas; hallado por `fuzz-tl`) |
| `max_w < min_w` | `max_w = min_w` |
| `avail` no finito o `< 1` | 1 |
| `gap` no finito o `< 0` | 0 |
| `pct ≤ 0` | sin porcentaje; `pct > 1000` ⇒ 1000 |

Ningún `out[c]` es negativo ni no finito. Coste `O(n · TL_MAX_SPAN_PASSES + n · ncols)`; sin bucles
dependientes de valores (solo de `n` y `ncols`).

## Fuera de alcance

`table-layout: fixed`, `<col width>`, porcentaje en celdas con `colspan`,
`rowspan` en la asignación de columna, `border-collapse`, altura de filas (la decide el motor de
cajas), `caption`.
