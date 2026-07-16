# Especificación: `compositor` (`cx_`)

> Fase 1 / Hito M1.1 (primer incremento) — Fundación del compositor de capas.
> Estado: **SPEC + TEST (rojo)** → verde. Metodología: SDD + TDD (ATDD Dado-Cuando-Entonces).
> Módulo **puro** (sin I/O, sin Cairo, sin GPU, sin asignación de surfaces): la lógica
> verificable directamente del backbone de compositing. La orquestación Cairo (surfaces
> offscreen, blend) vive en el lado confiable (GUI) y consumirá este módulo en incrementos
> posteriores (opacity de grupo, transform, animation, filter).

## 1. Propósito

Hoy el painter (`gui/browser_ui.c`) pinta una display list **plana, fila por fila**, y ordena
las cajas *out-of-flow* por `z_index` de forma **ad-hoc** en el paso Stage 2. No existe una
**fuente única** de "qué se pinta encima de qué" (el orden de pintado de CSS), lo que bloquea
`opacity` de grupo, `transform`, `animation`, `filter` y `mix-blend-mode` reales — todos exigen
un **árbol de capas** con contextos de apilamiento resueltos.

`compositor` es esa fuente única, **pura**: dada la tabla de estilo ya resuelta de una caja
(`position`, `z-index`, `opacity`, `mix-blend-mode`, `isolation`, float, inline), decide

1. si la caja **establece un contexto de apilamiento** (`cx_forms_stacking_context`), y
2. en cuál de las **siete capas de orden de pintado** de CSS 2.1 Apéndice E cae
   (`cx_box_layer`),

y ofrece un **orden total determinista** para pintar un conjunto de cajas (`cx_item_compare`,
`cx_sort`). No abre sockets, no lee ficheros, no toca Cairo ni la GPU, no asigna surfaces: es
matemática de orden sobre escalares ya validados por el parser CSS y el motor de cajas. Como
`js_policy`/`webcaps`, es lógica de decisión pura y por eso **directamente testeable** y sin
necesidad de fuzz (no parsea contenido remoto).

## 2. Contexto de apilamiento (stacking context)

Una caja establece un contexto de apilamiento (subconjunto soportado hoy; `transform`/`filter`/
`will-change` se añaden en M1.2/M1.4 sin cambiar el contrato) cuando:

- `opacity < 1` (opacidad fijada y menor que 100%), **o**
- `mix-blend-mode` distinto de `normal`, **o**
- `isolation: isolate`, **o**
- `position: relative | absolute` **con** `z-index` fijado (no `auto`), **o**
- `position: fixed | sticky` (siempre, en CSS moderno).

La raíz del documento establece el contexto raíz; eso lo decide el llamador (esta unidad
clasifica cajas no-raíz). `static` sin ninguna de las condiciones anteriores **no** establece
contexto.

## 3. Capas de orden de pintado (CSS 2.1 Apéndice E)

Dentro de un contexto de apilamiento, los descendientes se pintan en este orden (de atrás a
adelante). El enum `cx_layer` las numera 0..6:

| # | `cx_layer` | Contenido |
| :-- | :-- | :-- |
| 0 | `CX_LAYER_ROOT_BG` | fondo y bordes del elemento que forma el contexto |
| 1 | `CX_LAYER_NEG_Z` | contextos de apilamiento hijos con `z-index < 0` (más negativo primero) |
| 2 | `CX_LAYER_BLOCK` | descendientes in-flow, nivel-bloque, no posicionados |
| 3 | `CX_LAYER_FLOAT` | floats no posicionados |
| 4 | `CX_LAYER_INLINE` | descendientes in-flow, nivel-inline, no posicionados |
| 5 | `CX_LAYER_ZERO_Z` | contextos `z-index:0` + posicionados con `z-index:auto` |
| 6 | `CX_LAYER_POS_Z` | contextos de apilamiento hijos con `z-index > 0` (menos positivo primero) |

`cx_box_layer` mapea una caja a **una** de estas capas:

- forma contexto con `z<0` → `CX_LAYER_NEG_Z`;
- forma contexto con `z>0` → `CX_LAYER_POS_Z`;
- forma contexto con `z==0`/`auto`, o está posicionada con `z:auto` → `CX_LAYER_ZERO_Z`;
- float (no posicionado) → `CX_LAYER_FLOAT`;
- inline in-flow → `CX_LAYER_INLINE`;
- resto (bloque in-flow) → `CX_LAYER_BLOCK`.

## 4. Contrato de la API (`include/compositor.h`)

```c
typedef enum cx_layer { CX_LAYER_ROOT_BG=0, CX_LAYER_NEG_Z, CX_LAYER_BLOCK,
    CX_LAYER_FLOAT, CX_LAYER_INLINE, CX_LAYER_ZERO_Z, CX_LAYER_POS_Z } cx_layer;

/* Estilo resuelto de una caja, en los mismos value-spaces que css.h (position =
 * css_position, mix_blend = css_mix_blend, isolation = css_isolation). z_auto == 1
 * significa z-index auto/unset (z_index se ignora). opacity: 0..100, o -1 (opaco). */
typedef struct cx_style { int position; int z_index; int z_auto; int opacity;
    int mix_blend; int isolation; int is_float; int is_inline; } cx_style;

int      cx_forms_stacking_context(const cx_style *s);   /* 1 si establece contexto */
cx_layer cx_box_layer(const cx_style *s);                /* capa de pintado */

/* Una caja a ordenar: su capa, z-index (auto=>0 en ZERO_Z), orden de documento
 * (desempate estable) y un handle opaco del llamador (p. ej. el box_index). */
typedef struct cx_item { cx_layer layer; int z_index; int z_auto;
    size_t doc_order; size_t ref; } cx_item;

int  cx_item_compare(const cx_item *a, const cx_item *b); /* <0/0/>0 estilo qsort */
void cx_sort(cx_item *items, size_t n);                   /* orden de pintado, estable */
```

### Errores / defensa
- Punteros `NULL`: `cx_forms_stacking_context(NULL)` y `cx_box_layer(NULL)` → `0`/`CX_LAYER_BLOCK`
  (fail-safe, nunca desreferencia). `cx_sort(NULL, n)` y `n==0` son no-op.
- Sin asignación dinámica: `cx_sort` ordena in-place. Sin límites artificiales (el llamador acota
  `n` por `BT_MAX_POSITIONED`); sin overflow (comparación de enteros con signo bien definida).

## 5. Semántica (Dado-Cuando-Entonces)

- **Dado** una caja `opacity:0.5`, **cuando** se clasifica, **entonces** forma contexto de
  apilamiento y cae en `CX_LAYER_ZERO_Z` (opacidad sin z-index).
- **Dado** `position:absolute; z-index:-1`, **cuando** se clasifica, **entonces** forma contexto y
  cae en `CX_LAYER_NEG_Z`.
- **Dado** `position:absolute; z-index:5`, **entonces** `CX_LAYER_POS_Z`.
- **Dado** `position:absolute` sin z-index (`z:auto`), **entonces** NO forma contexto por sí solo
  pero, al estar posicionada, cae en `CX_LAYER_ZERO_Z`.
- **Dado** `position:static; float:left`, **entonces** no forma contexto y cae en `CX_LAYER_FLOAT`.
- **Dado** `mix-blend-mode:multiply` sobre una caja estática, **entonces** forma contexto
  (`CX_LAYER_ZERO_Z`).
- **Dado** un conjunto de cajas, **cuando** `cx_sort` las ordena, **entonces** quedan por capa
  ascendente, luego z-index ascendente (auto=0), luego orden de documento ascendente — un orden
  **total y determinista** (dos cajas con la misma clave conservan el orden de documento).
- **Byte-idéntico:** para el subconjunto de cajas *out-of-flow* que el painter ya ordena por
  `z-index`, `cx_sort` produce **el mismo orden** (mismo z-index, mismo desempate por documento),
  así el cableado posterior no cambia ningún pixel donde no haya contexto de apilamiento nuevo.

## 6. Matriz de pruebas (`tests/test_compositor.c`)

- `cx_forms_stacking_context`: opacity<1 sí / opacity==100 no / opacity==-1 no; mix-blend
  multiply sí / normal no / unset no; isolation isolate sí / auto no; relative+z sí /
  relative sin z no; absolute+z sí; fixed siempre sí; sticky siempre sí; static puro no; `NULL` → 0.
- `cx_box_layer`: cada capa (NEG_Z, POS_Z, ZERO_Z por contexto z0, ZERO_Z por posicionado z:auto,
  FLOAT, INLINE, BLOCK); `NULL` → BLOCK.
- `cx_item_compare`: orden por capa; dentro de capa por z-index; auto tratado como 0; desempate por
  documento; reflexividad (`cmp(a,a)==0`) y antisimetría de signo.
- `cx_sort`: mezcla de las 7 capas + z-index mixtos → orden esperado exacto; estabilidad (claves
  iguales conservan documento); `n==0`/`NULL` no-op; equivalencia con el orden z-index del painter
  para un conjunto solo-posicionado.

## 7. Fuera de alcance (este incremento)

- **Cableado al painter** (usar `cx_sort` como el comparador del array `positioned` y construir el
  árbol de capas real): incrementos siguientes de M1.1.
- **Surfaces offscreen / compose Cairo** (`opacity` de grupo real, blend): M1.1 (painter de capas).
- `transform`/`filter`/`will-change` como disparadores de contexto: se añaden a `cx_style` en
  M1.2/M1.4 (campos nuevos, el contrato no cambia).
- Contención (`contain`) y `perspective` como disparadores: futuros.
- Ordenar la geometría o decidir clipping/overflow (eso sigue en `box_tree`/painter).
