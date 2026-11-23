# group_index (`gi_`) — agrupar ítems por clave, una vez por cuadro

## Por qué

Cada subárbol diferido (un elemento en flujo que pinta en el orden de las cajas posicionadas,
`paint_positioned_layer`) se pintaba con un pase que **recorría todas las cajas y todas las
filas del documento** para quedarse con las suyas, y cada fila buscaba su caja con otro
recorrido lineal. Con ~700 subárboles (GitHub) eso son millones de iteraciones por cuadro:
medido en la ventana real, 15–31 ms de los ~40 ms de un cuadro de scroll en GitHub y 7–22 ms
en Hugging Face (`make gscroll`, tanda 102).

`gi_build` es un *group-by* estable (formato CSR): los ítems quedan agrupados por su clave en
el MISMO orden relativo que tenían, así cada pase diferido visita solo lo suyo y el orden de
pintado no cambia.

## Contrato

`size_t gi_build(const int *keys, size_t n, size_t nkeys, size_t *offs, size_t *items)`

- `keys[i]` es la clave del ítem `i`; una clave fuera de `[0, nkeys)` (p. ej. `-1`, «no
  diferido») deja el ítem **fuera** de todo grupo.
- Escribe `offs[0..nkeys]` (`nkeys + 1` entradas) e `items[0..m)`, con `m` el valor devuelto:
  el grupo `k` son los índices `items[offs[k] .. offs[k+1])`, en orden creciente.
- Devuelve `m` (cantidad de ítems agrupados) o `(size_t)-1` si `keys`, `offs` o `items` son
  NULL con `n > 0`, si `offs` es NULL, o si `nkeys == SIZE_MAX` (`nkeys + 1` desbordaría).
  `n == 0` es válido: todos los grupos vacíos.
- Puro, sin asignaciones, O(n + nkeys).

## Garantías (comprobadas por el fuzzer contra una referencia ingenua)

1. `offs` es no decreciente, `offs[0] == 0`, `offs[nkeys] == m ≤ n`.
2. Cada índice de `items[0..m)` aparece una vez, y su clave es la de su grupo.
3. Todo ítem con clave válida está en su grupo; ninguno con clave inválida aparece.
4. Dentro de un grupo los índices son estrictamente crecientes (estable).

## Dado-Cuando-Entonces

- **Dado** `keys = {1, -1, 0, 1, 5, 0}` y `nkeys = 2`, **entonces** `offs = {0, 2, 4}`,
  `items = {2, 5, 0, 3}` y devuelve 4 (el `-1` y el `5` quedan fuera).
- **Dado** `n = 0`, **entonces** `offs` todo ceros y devuelve 0.
- **Dado** `offs == NULL`, **entonces** `(size_t)-1` y nada escrito.

## Uso

`gui/browser_ui.c`, `paint_structured`: una vez por cuadro, cajas y filas se agrupan por su
raíz diferida (`defer_root_of`); el pase de una raíz recorre solo su grupo. Si la memoria del
índice no se puede obtener, el pase vuelve al recorrido completo de siempre (mismo resultado,
más lento). Junto a él, un mapa `block_id → caja` reemplaza la búsqueda lineal de la caja de
cada fila.

## Fuera de alcance

Claves que cambian durante el pintado: el índice se construye sobre el layout ya cerrado del
cuadro y se descarta al terminarlo.
