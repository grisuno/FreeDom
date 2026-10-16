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

- Colocación por **nombre de línea** (`[main-start]`, `<integer> <ident>`): falla
  cerrado a auto-colocación (§6). La colocación por **número** ya está (§6).
- `grid-auto-flow: column` y `dense`.
- Filas implícitas creadas por un área que excede la plantilla (se recorta, §3).
- Alineación por ítem dentro de su área (`justify-self`/`align-self` en grid).

## 6. Colocación por número de línea (2026-10-15, CSS Grid 1 §8.3)

**Por qué:** medido en el corpus del allowlist. github.com declara ~700
`grid-column: auto/span N` (Primer Brand: la grilla de 12 columnas de TODA tarjeta)
y ipinfo.io apila sus pestañas con `grid-column:1; grid-row:1`. El parser solo
aceptaba `span N`, así que cada declaración era `bad-value`, cada tarjeta caía en
UNA pista de 1/12 y su texto envolvía un carácter por línea (github: 440 filas de
1 px, la página 1.5× más alta que en Firefox).

**Codificación de un lado** (`grid-column-start` y compañía), un `int`:
`FX_GL_AUTO` (0) = `auto`; `FX_GL_SPAN_BASE + n` = `span n` (n en
`[1, CSS_GRID_SPAN_MAX]`); cualquier otro valor no nulo = número de línea `n`
(negativo cuenta desde el final; `|n| <= FX_GL_LINE_MAX`). Un número cero, un
nombre o `<integer> <ident>` no son representables ⇒ la declaración se descarta.

### `int fx_grid_line_side(const char *s, int *out)`
Un lado: `auto` | `<integer>` | `span <integer>` (y `<integer>` antes de `span`
**no**). Devuelve 1 y escribe `*out`, o 0 sin tocarlo.

### `int fx_grid_line_parse(const char *v, int *start, int *end)`
El shorthand `grid-column`/`grid-row`: `<lado> [ / <lado> ]`. Sin barra el fin es
`auto`. Una sola barra de nivel superior; dos ⇒ 0.

### `void fx_grid_line_resolve(int start, int end, int ntracks, int *pos0, int *span)`
Resuelve contra las `ntracks` pistas explícitas (§8.3.1): línea negativa
`-k` ⇒ `ntracks + 2 - k`; `span` + línea ⇒ el span cuenta HACIA la línea; dos
spans ⇒ gana el de inicio; fin <= inicio ⇒ se intercambian (iguales ⇒ span 1).
`*pos0` es la pista de inicio en base 0, o **-1** = auto-colocar (posición no
definida). `*span` >= 1. Una línea negativa sin `ntracks` conocido (0, p. ej. `repeat(auto-fill,…)`, cuyo
conteo solo existe en el layout) ⇒ ese lado es `auto` (fail-closed, nunca una celda
inventada), salvo `<n> / -1`, que significa "hasta la última línea" y se resuelve
como `span FX_GL_SPAN_MAX`: el colocador lo recorta a las pistas reales.

| start | end | `pos0` | `span` |
| :-- | :-- | :-- | :-- |
| `auto` | `auto` | -1 | 1 |
| `span 6` | `auto` | -1 | 6 |
| `auto` | `span 6` | -1 | 6 |
| `2` | `auto` | 1 | 1 |
| `1` | `3` | 0 | 2 |
| `1` | `-1` (12 pistas) | 0 | 12 |
| `1` | `-1` (pistas desconocidas) | 0 | `FX_GL_SPAN_MAX` |
| `3` | `1` | 0 | 2 |
| `2` | `span 3` | 1 | 3 |
| `span 2` | `5` | 2 | 2 |

### Colocación (`fx_grid_place_span`)
Un ítem con **columna fija y fila auto** ya no se clava en la fila 0 (todos los
`1 / -1` se superponían): va en la pasada automática, con el cursor (§8.5 paso 4):
cursor de columna a su columna, si eso retrocede se baja una fila, y se baja hasta
que no se superponga. Fila fija + columna auto: primera columna libre de esa fila.
Con ambos fijos, comportamiento previo (byte-idéntico para `grid-area: <nombre>`).

## 5. Seguridad

Todo es aritmética y recorrido acotado sobre buffers de tamaño fijo. La plantilla
viene de CSS remoto y por eso cada cota (`FX_AREA_MAX_ROWS`, `FX_AREA_MAX_COLS`,
`FX_AREA_MAX_CELLS`, `FX_AREA_NAME_MAX`) se comprueba **antes** de escribir, no
después. No hay recursión, no hay `malloc`, no hay estado global: reentrante.
