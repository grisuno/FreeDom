# pres_hints (`ph_`) — atributos de presentación de HTML como estilo

Módulo puro (sin I/O, sin asignación, sin estado global). HTML §15 «Rendering» define que ciertos
atributos (`<table width>`, `<td align>`, `nowrap`, `<center>`) son *presentational hints*: reglas
de autor de especificidad cero. Cualquier declaración CSS gana. Sin ellos una tabla clásica
(`<center><table width="85%">`, Hacker News) se maqueta a todo el ancho y sin centrar.

`ph_apply(tag, get, ctx, centered, cs)` escribe en `cs` **solo los campos que la cascada dejó sin
declarar**. `get(ctx, name, &len)` devuelve el valor del atributo (no terminado en NUL) o `NULL`.
`centered != 0` dice que un ancestro centra sus bloques (`<center>` / `align=center`).

| Elemento | Atributo | Efecto (si no está declarado) |
| :-- | :-- | :-- |
| `table`, `td`, `th` | `width="N"` / `"N%"` | `width` en px / per-mille (las DOS mitades) |
| `table` | `align=center`, o `centered` | `margin-left/right: auto` |
| `td`, `th`, `tr`, `div`, `p`, `h1`–`h6` | `align=left|center|right|justify` | `text-align` |
| `td`, `th` | `nowrap` | `white-space: nowrap` |
| `center` | — | `text-align: center` |
| `table` | `cellspacing="N"` | `border-spacing: Npx` |
| `table` | — (hoja UA) | `border-spacing: 2px` |
| `td`, `th` | `cellpadding="N"` **del `<table>` ancestro** | `padding: Npx` en las cuatro caras |
| `td`, `th` | — (hoja UA) | `padding: 1px` en las cuatro caras |

`cellspacing`/`cellpadding` usan las «rules for parsing non-negative integers» (HTML §2.3.4.1):
espacios, `+` opcional, dígitos; basura final ignorada; `0` es válido. Sin dígitos o más de
`PH_DIM_MAX_PX` ⇒ se ignora. Los dos valores por defecto de la hoja UA (los de Firefox y la hoja
UA de HTML §15.3.8) viven acá porque este es el único punto donde se resuelve lo que la cascada
no declaró: una cara de `padding` o un `border-spacing` declarados por el autor ganan siempre.

`ph_table_cellpadding(get, ctx)` lee el atributo del `<table>` (px, o −1 si no hay o es
inválido); `ph_cell_padding(cellpad, cs)` lo aplica a una celda (−1 ⇒ el 1 px de la hoja UA).
`page_view` busca el `<table>` más cercano con un recorrido acotado que se detiene en el primer
`<table>` (una celda de una tabla anidada toma el atributo de SU tabla).

**Uso del `border-spacing`** (`page_view`): es el hueco entre columnas y entre filas de la rejilla
de la tabla (`gap`/`row_gap`), y también el margen entre el borde de la tabla y sus celdas (CSS
2.1 §17.6.1). En el modelo `border-collapse: collapse` no hay espaciado (§17.6.2): 0.

Dado `<table cellspacing=6 cellpadding=12>` entonces la tabla tiene `border-spacing` 6 y cada
celda `padding` 12. Dado `cellpadding=0` entonces 0 (válido). Dado `<td style="padding:1px">`
bajo `cellpadding=4` entonces 1 (gana el CSS). Dado `<table style="border-spacing:10px"
cellspacing=2>` entonces 10.

**Dimensión** (HTML «rules for parsing dimension values»): espacios iniciales, dígitos, fracción
opcional, y `%` ⇒ porcentaje. Fail-closed: sin dígitos, valor 0, más de `PH_DIM_MAX_PX` px o más
de 1000 ‰·10 ⇒ se ignora el atributo. Valores de atributo de más de `PH_ATTR_MAX` bytes se ignoran.

Dado `<table width="85%" style="width:300px">` entonces gana el CSS (300 px, mitad % en 0).
Dado `tag == NULL`, `get == NULL` o `cs == NULL` entonces no hace nada.

Fuera de alcance: `height`, `border`, `valign` (y el alineado vertical de celdas, que pide estirar
la caja de la celda al alto de la fila en el pintor: abierto), `hspace`/`vspace`,
`bgcolor`/`color` (ya los resuelve `page_view` como respaldo de color), `<font size>`.
