# `grid_areas` — colocación por nombre en CSS Grid (`fx_grid_areas_*`)

> Funciones **puras** dentro de `flex_layout` (`fx_`). Sin I/O, sin asignación, sin
> estado global. Implementan CSS Grid Layout 1 §7.3 (`grid-template-areas`) y §8.4
> (resolución de una *named grid area* a su rectángulo).

## 1. Por qué existe

Hasta ahora los ítems de una grilla se colocaban **round-robin**: el ítem *i* iba a
la fila `i / ncols`, columna `i % ncols`. Eso es correcto solo para la
auto-colocación pura. Todo layout de portal moderno declara la posición por
**nombre**:

```css
.page { display: grid;
        grid-template-columns: 12.25rem minmax(0, 1fr);
        grid-template-areas: 'siteNotice siteNotice'
                             'columnStart pageContent'
                             'footer      footer'; }
.sidebar { grid-area: columnStart; }
.content { grid-area: pageContent; }
```

Sin resolver los nombres, el aviso de sitio cae en la columna estrecha, la barra
lateral en la ancha y el pie en cualquier lado — que es exactamente el estado
medido de Wikipedia (Vector 2022 arma **toda** su página así: `.mw-page-container-inner`,
`.mw-header` y `.mw-body` son tres grillas con nombres).

## 2. Contrato

### `unsigned fx_grid_area_hash(const char *name)`

**Dado** un identificador de área (`grid-area: columnStart`, o un token de la
plantilla), **cuando** se lo pide, **entonces** devuelve su FNV-1a de 32 bits sobre
el nombre **recortado** de espacios, **case-sensitive** (los identificadores CSS lo
son) — y **nunca 0**: el 0 está reservado para "sin nombre", así que un hash que
caiga en 0 se desplaza a 1. `NULL`, cadena vacía o solo espacios ⇒ 0.

El motor compara **hashes**, no cadenas: es lo que permite que el nombre del ítem
viaje por el códec IPC como un `int` en vez de como texto de longitud variable.
Una colisión coloca un ítem en la celda de otro — un artefacto de maquetación, no
un problema de memoria ni de seguridad: no hay indexado por hash, solo comparación,
y el rectángulo resultante siempre se valida contra las dimensiones de la grilla.

### `fx_status fx_grid_areas_parse(const char *tmpl, fx_area_map *out)`

**Dado** el valor crudo de `grid-template-areas` — una secuencia de cadenas
entrecomilladas, una por fila (`'a b' 'c d'`, comillas simples o dobles) —
**cuando** se parsea, **entonces** `out` queda con `rows`, `cols` y una celda por
posición con el hash del nombre, o **0** para la *null cell token* (`.` o una
secuencia de puntos, CSS Grid 1 §7.3).

Falla cerrado (`FX_ERR_RANGE`, `out->rows = 0`) si:

| caso | por qué |
| :-- | :-- |
| filas con distinto número de columnas | §7.3 lo declara inválido; una grilla dentada no tiene geometría definida |
| `rows > FX_AREA_MAX_ROWS` o `cols > FX_AREA_MAX_COLS` | anti-DoS: la plantilla la elige el atacante |
| `rows * cols > FX_AREA_MAX_CELLS` | idem, cota del arreglo |
| ninguna fila, o una fila vacía | no hay grilla |
| un token de más de `FX_AREA_NAME_MAX` bytes | se recorta a "sin nombre", no se trunca a un nombre distinto |

`tmpl == NULL` o `out == NULL` ⇒ `FX_ERR_NULL_ARG`. La función **no asigna**: toda
la salida cabe en `*out`.

### `fx_status fx_grid_area_rect(const fx_area_map *m, unsigned name, int *row, int *col, int *row_span, int *col_span)`

**Dado** un mapa parseado y el hash de un nombre, **cuando** ese nombre aparece en
el mapa, **entonces** devuelve el **rectángulo mínimo que cubre todas sus celdas**
(§8.4: una named grid area es rectangular por definición) y `FX_OK`.

- Un nombre que **no** aparece ⇒ `FX_ERR_RANGE` y las salidas quedan intactas: el
  llamante entonces auto-coloca el ítem, que es lo que hace un navegador con un
  `grid-area` que no existe en la plantilla.
- Un nombre cuyas celdas **no forman un rectángulo lleno** (p. ej. en forma de L)
  ⇒ `FX_ERR_RANGE`. §7.3 dice que eso hace inválida la declaración entera; fallar
  al ítem individual es la degradación más chica que preserva el resto.
- `name == 0` ⇒ `FX_ERR_RANGE` (0 es "sin nombre", no un nombre).

## 3. Colocación explícita + auto-colocación mezcladas

`fx_grid_place_span` acepta ahora `fixed_row`/`fixed_col` (arreglos opcionales,
`-1` = auto). Un ítem con posición fija **ocupa su rectángulo** y no consume el
cursor; los ítems automáticos fluyen **alrededor** de las celdas ya ocupadas, que es
el algoritmo de CSS Grid §8.5 (*auto-placement*) restringido al modo `row` denso-
cero. Con ambos arreglos en `NULL` el comportamiento es **byte-idéntico** al
anterior, así que ninguna grilla sin nombres cambia.

Una posición fija fuera de la grilla se **recorta** al rango válido en vez de
descartarse: el ítem se ve en el borde, que es preferible a que desaparezca.

## 4. Fuera de alcance (v1)

- Colocación por **número de línea** (`grid-column: 2 / 4`, `1 / -1`) y por
  **nombre de línea** (`[main-start]`): el corpus medido no las usa; el punto de
  extensión es el mismo par `fixed_row`/`fixed_col`.
- `grid-auto-flow: column` y `dense`.
- Filas implícitas creadas por un área que excede la plantilla (se recorta, §3).
- Alineación por ítem dentro de su área (`justify-self`/`align-self` en grid).

## 5. Seguridad

Todo es aritmética y recorrido acotado sobre buffers de tamaño fijo. La plantilla
viene de CSS remoto y por eso cada cota (`FX_AREA_MAX_ROWS`, `FX_AREA_MAX_COLS`,
`FX_AREA_MAX_CELLS`, `FX_AREA_NAME_MAX`) se comprueba **antes** de escribir, no
después. No hay recursión, no hay `malloc`, no hay estado global: reentrante.
