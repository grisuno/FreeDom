# css_vars — tabla de custom properties y sustitución `var()`

Extraído de `css.c` (cláusula anti-monolito) el 2026-09-29, al medir github.com.

## Contrato

| Función | Entrada | Salida |
| :-- | :-- | :-- |
| `cvr_set(t, name, nlen, value, vlen)` | nombre `--ident`, valor recortado | 1 guardado / 0 descartado |
| `cvr_get(t, name, nlen)` | nombre | valor o `NULL` (sensible a mayúsculas) |
| `cvr_collect_decls(t, s, a, b)` | un bloque de declaraciones | guarda cada `--x: v` (quita `!important`) |
| `cvr_resolve(val, out, outcap, scope)` | valor con `var()` | 1 sustituido / 0 la declaración falla |
| `cvr_reset` / `cvr_free` | tabla | libera cadenas / todo; idempotentes |

`cvr_scope { first, second }`: `first` gana una colisión de nombre (las propiedades
propias de un `style=` inline sobre las de la hoja).

## Cotas (anti-DoS, por encima de lo que publica un design system real)

| Cota | Valor | Por qué |
| :-- | :-- | :-- |
| `CVR_NAME_MAX` | 256 B | Primer tiene nombres de ~60 B; el tope viejo de 64 los rozaba. |
| `CVR_VALUE_MAX` | 1024 B (= `CSS_URL_MAX`) | Un stack de `font-family` o `var(--w) solid var(--c)` pasa de 64 B. |
| `CVR_MAX_ENTRIES` | 65536 | Primer declara 2443 nombres distintos; el tope viejo era 512. |
| `CVR_MAX_DEPTH` | 32 | Una cadena de tokens de componente llega a 4 saltos; el tope viejo era 4. |

Un nombre o valor fuera de cota se **descarta entero**, nunca se trunca: una entrada de
la tabla es la del autor o no existe.

## Garantías

- Dado `--a: var(--a)`, cuando se usa `var(--a)`, entonces la declaración falla al
  llegar a `CVR_MAX_DEPTH` (sin recursión infinita).
- Dado un abanico exponencial (`--b: var(--a) var(--a)` …), cuando se sustituye,
  entonces el trabajo está acotado por `outcap`: cada hoja agrega al menos un byte y el
  desborde falla la declaración.
- Dado un `var()` sin cerrar o sin nombre `--`, entonces 0 (falla cerrado).
- Búsqueda O(1) promedio (hash FNV-1a, direccionamiento abierto, índice ≥ 2× entradas).
- Toda cadena tiene un único dueño (la tabla) y un único liberador (`cvr_reset`).

## Fuera de alcance

Custom properties con alcance por elemento (la tabla es global por página: qué reglas la
alimentan lo decide `css.c`, ver `spec/css.md` "Custom properties" y "Root matcher").
`@property`, `env()`, `attr()`.

## Alcance por elemento y herencia (2026-09-29, tanda 34)

La tabla global por página (lo de arriba) no puede representar el patrón que usan todos
los design systems modernos: la variable se declara en un **componente** y se usa en el
mismo elemento o en un descendiente (`.btn{--bs-btn-bg:#0d6efd;background:var(--bs-btn-bg)}`
de Bootstrap 5; `.from-x{--tw-gradient-from:…}` + `.bg-linear-to-r{background-image:
linear-gradient(var(--tw-gradient-stops))}` de Tailwind v4; los tokens de componente de
Primer). CSS Variables 1 §2: una custom property es una propiedad **heredada** más, que se
cascadea por elemento.

**Modelo.**
- *Parseo:* cada `--x: v` de una regla es una declaración meta `P_META_CUSTOM` en el mismo
  arreglo de la regla (nombre y valor en el pool de texto crudo de la hoja). Toda
  declaración con `var()` va precedida de un marcador `P_META_VARSRC` con su texto crudo y
  `span` = cuántas declaraciones produjo la resolución **global** que le sigue (0 si la
  global no resolvió). Ninguna declaración meta reclama un slot de cascada.
- *Cascada del elemento* (`css_resolve_el_ex`): (1) las `--x` de las reglas que coinciden
  compiten por nombre con la regla normal (capa/`!important`, especificidad, orden, y
  dentro de la regla la posterior), más las del `style=` inline por encima; los ganadores
  forman la tabla **propia** del elemento. (2) Si el elemento tiene tabla propia o hereda
  una cadena, cada marcador `VARSRC` se vuelve a resolver con el alcance
  *propia → cadena heredada → tabla global → `@property initial-value`* y se reinterpreta;
  las `span` declaraciones globales se saltan. Sin tabla propia ni cadena, se aplican las
  globales: **el camino de siempre, byte a byte**.
- *Herencia:* `css_element.vars` es la cadena del padre (`cvr_chain`, un nodo por elemento
  que declara algo; los demás comparten el puntero del padre). La provee `page_view`, que ya
  resuelve estilos de la raíz hacia abajo con memo por nodo (igual que `font_size`); la
  profundidad de la cadena está acotada por la misma `PV_FONT_CHAIN_MAX`.
- *`@property --x { initial-value: v }`* (CSS Properties & Values 1 §3) alimenta una tabla
  base consultada al final.

**Garantías.** Dado `.btn{--c:#123456;color:var(--c)}`, cuando un elemento `.btn` se
resuelve, entonces su color es `#123456` (antes: declaración descartada, la variable no es
de raíz). Dado `.card{--c:X}` y `p{color:var(--c)}`, cuando `p` está dentro de `.card`,
entonces hereda X; fuera, usa el valor de `:root`. Dado un documento sin variables de
componente, entonces el resultado es idéntico al de la tabla global.

**Aproximaciones documentadas.** Una `var()` dentro del VALOR de una custom property se
resuelve donde se USA, no donde se declara (difiere solo si un descendiente redefine el
nombre referido). `@property inherits:false` todavía hereda.
