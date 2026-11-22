# spec: mask_cache (`mkc_`) — máscaras A8 retenidas entre cuadros

## Por qué existe (medido, tanda 95)

Cada cuadro de la ventana real (scroll, animación, hover, parpadeo del cursor) repinta la
página entera, y `box-shadow` con desenfoque crea en cada uno una máscara A8 del tamaño de la
caja, dibuja la silueta y la desenfoca con tres pasadas por eje (`spec/box_blur.md`). Medido
con `tools/guiscroll.py` en la portada de es.wikipedia: **55 ms de 63 ms por cuadro** eran
dos sombras de `blur: 1px` sobre paneles de 414×1310 y 506×1009. La máscara no depende del
scroll ni del tiempo: es función pura de la geometría de la silueta y del sigma, así que se
calcula una vez y se reutiliza.

## Contrato

```c
typedef struct mkc_key {
    int    w, h;          /* dimensiones de la máscara (px) */
    double sx, sy;        /* origen de la silueta dentro de la máscara */
    double sw, sh, sr;    /* tamaño y radio de esquina de la silueta */
    double sigma;         /* desviación estándar del desenfoque */
    int    inset;         /* 1 = sombra interior (se invierte la silueta) */
} mkc_key;

mkc_cache *mkc_new(size_t byte_budget, size_t max_entries);
void       mkc_free(mkc_cache *c);                 /* NULL-safe */
void       mkc_clear(mkc_cache *c);                /* NULL-safe, idempotente */
const unsigned char *mkc_get(mkc_cache *c, const mkc_key *k, int *stride);
unsigned char       *mkc_put(mkc_cache *c, const mkc_key *k, int stride);
size_t     mkc_bytes(const mkc_cache *c);
size_t     mkc_count(const mkc_cache *c);
```

- **Clave exacta, sin hash** (doctrina `sheet_cache`): dos claves son iguales si y solo si
  TODOS sus campos son iguales (los `double` se comparan por valor; un NaN nunca iguala, así
  que nunca acierta). La clave son todas las entradas de lo que se cachea: la máscara es
  función de `(w, h, sx, sy, sw, sh, sr, sigma, inset)` y de nada más (el color, el alfa y la
  posición en pantalla se aplican al usarla, no al construirla).
- `mkc_get`: el buffer retenido para `k` y su `stride`, o NULL. Un acierto lo vuelve el más
  reciente. El puntero vale hasta la siguiente llamada a `mkc_put`/`mkc_clear`/`mkc_free`.
- `mkc_put`: reserva un buffer de `stride·h` bytes **a cero** (V-002) del que la caché es
  dueña, lo asocia a `k` (si ya había entrada para `k`, la reemplaza) y lo devuelve para que
  el llamador lo llene. Desaloja por LRU hasta que el nuevo entre en el presupuesto. NULL —
  fail-closed, sin tocar la caché — si `stride < w`, alguna dimensión es `<= 0`,
  `stride·h` desborda o excede el presupuesto entero, o falla la asignación. El llamador
  entonces pinta sin caché (mismo resultado, más lento).
- Cotas: `byte_budget` (suma de los buffers retenidos) y `max_entries`; ambas se respetan
  siempre (`mkc_bytes() <= byte_budget`, `mkc_count() <= max_entries`).
- Sin estado global; un dueño (la ventana) y un liberador idempotente.

## Uso en el pintor

La ventana crea una caché (`FC_MASK_CACHE_BYTES`, `FC_MASK_CACHE_ENTRIES`) y la cuelga del
`cairo_t` de pantalla como *user data*. `paint_box_shadow_layer` la busca ahí: sin caché (PDF,
PNG headless) el camino es el de siempre. Con caché, un acierto se pinta con
`cairo_mask_surface` sobre un envoltorio del buffer; un fallo reserva con `mkc_put`, dibuja la
silueta, desenfoca y pinta. `FREEDOM_MASK_CACHE_CHECK=1` es el oráculo diferencial: en cada
acierto recalcula la máscara y aborta si un solo byte difiere. La caché NO se vacía al cambiar
de documento: la clave no nombra el documento porque la máscara no depende de él, y el LRU
acota la memoria (dos páginas del mismo sitio comparten sus tarjetas).

## Dado-Cuando-Entonces

- **Dado** una caché vacía **cuando** `mkc_get` **entonces** NULL.
- **Dado** un `mkc_put` de `k` **cuando** `mkc_get(k)` **entonces** devuelve el MISMO buffer,
  con el `stride` pedido y su contenido intacto.
- **Dado** `k` y `k'` que difieren en un solo campo (incluido `sigma` o `inset`) **cuando**
  `mkc_get(k')` **entonces** NULL.
- **Dado** un presupuesto para dos máscaras **cuando** se insertan A, B, se consulta A y se
  inserta C **entonces** B se desaloja (LRU) y A y C siguen.
- **Dado** una máscara mayor que el presupuesto entero **cuando** `mkc_put` **entonces** NULL
  y la caché queda igual.
- **Dado** `max_entries` alcanzado **cuando** se inserta otra **entonces** se desaloja la menos
  reciente y `mkc_count() == max_entries`.
- **Dado** un `mkc_put` de una clave ya presente **entonces** hay una sola entrada para ella.
- **Dado** `NULL` en cualquier argumento **entonces** NULL / 0 / no-op, nunca un crash.

## Fuera de alcance

Máscaras de `filter: blur()` y `backdrop-filter` (dependen del contenido pintado, no solo de
la geometría), y retener superficies ARGB.
