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

**Dimensión** (HTML «rules for parsing dimension values»): espacios iniciales, dígitos, fracción
opcional, y `%` ⇒ porcentaje. Fail-closed: sin dígitos, valor 0, más de `PH_DIM_MAX_PX` px o más
de 1000 ‰·10 ⇒ se ignora el atributo. Valores de atributo de más de `PH_ATTR_MAX` bytes se ignoran.

Dado `<table width="85%" style="width:300px">` entonces gana el CSS (300 px, mitad % en 0).
Dado `tag == NULL`, `get == NULL` o `cs == NULL` entonces no hace nada.

Fuera de alcance: `height`, `cellpadding`/`cellspacing`, `border`, `valign`, `hspace`/`vspace`,
`bgcolor`/`color` (ya los resuelve `page_view` como respaldo de color), `<font size>`.
