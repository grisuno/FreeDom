# css_select — motor de selectores del CSS de autor

> Módulo interno extraído de `css` (cláusula anti-monolito, §3.4 de CLAUDE.md):
> `src/css.c` rozaba las ~2000 líneas, y el motor de selectores es una unidad
> coherente con contrato propio. `css` conserva la cascada y la interpretación de
> valores; `css_select` parsea un selector complejo y lo empareja contra un
> `css_element`. Consumido solo por `css.c` y sus tests/fuzzers; la API pública
> del navegador sigue siendo `css.h`.

## Entradas / salidas

- `int csel_parse(const char *s, size_t a, size_t b, css_sel *sel)` — parsea el
  selector complejo `s[a,b)` en `*sel` (compuestos + combinadores + especificidad;
  `order`/`rule` los estampa el llamador). Devuelve 1 si es soportado, 0 para
  **descartar el selector entero** (fail closed).
- `int csel_matches(const css_sel *sel, const css_element *el)` — 1 si `*sel`
  matchea `*el` contra sus cadenas de ancestros (`parent`) y hermanos previos
  (`prev`). Puro, acotado, sin asignaciones.
- Helpers ASCII compartidos con la cascada (`static inline` en el header):
  `csel_lower_ch`, `csel_ci_eq`, `csel_span_eq`, `csel_substr`, `csel_ident_ch`.

## Contrato (Dado-Cuando-Entonces)

- **Dado** un selector con sintaxis no soportada (`:not(...)`, `::before`,
  pseudo-clase desconocida, `[...]` malformado, cadena > `CSS_MAX_COMPOUNDS`,
  más de `CSS_MAX_PSEUDO_SEL` pseudo-clases o `CSS_MAX_ATTR_SEL` atributos por
  compuesto) — **cuando** se parsea — **entonces** `csel_parse` devuelve 0 y la
  regla pierde solo ese selector (los demás del grupo por coma siguen).
- **Dado** `a:link{...}` y un elemento `a` con atributo `href` — **cuando** se
  matchea — **entonces** aplica (Zero Knowledge: sin historial, todo enlace está
  no-visitado). **Dado** `:visited` — **entonces** jamás matchea (sin historial
  por diseño).
- **Dado** un pseudo dinámico (`:hover`/`:active`/`:focus`/`:focus-within`/
  `:focus-visible`) — **entonces** matchea **si y solo si** el bit
  correspondiente está encendido en `el->state`. En una carga sin puntero ni
  foco, `state == 0` y **ninguno** matchea, que es exactamente lo que hace
  cualquier navegador con el mouse fuera de la ventana.

  > **Cambio de doctrina (2026-08-11, autorizado por el dueño).** Hasta esta
  > fecha eran `PSEUDO_ALWAYS`: matcheaban siempre, con la idea de "revelar el
  > contenido escondido tras un menú". El efecto real era peor que el problema:
  > la página se pintaba como si el mouse estuviera **sobre todos los elementos
  > a la vez**. Medido en DuckDuckGo: cada snippet de resultado salía subrayado
  > y azul, aparecían bordes que el autor solo pone en `:hover`, y bloques que
  > el autor oculta hasta el hover se superponían al texto. Ninguna de esas
  > cosas está en el CSS de la página *en el estado en que la página se carga*.
  > Una regla `:hover` **sí** viene del CSS; aplicarla siempre **no**. El estado
  > es un input del motor, no una constante.
  >
  > El campo `state` es el punto de extensión: cuando la GUI sepa qué elemento
  > está bajo el puntero, prende `CSEL_STATE_HOVER` y re-resuelve ese subárbol;
  > el matcher ya no necesita cambiar. El selector parsea y cuenta especificidad
  > en todos los casos, matchee o no.
- **Dado** `li:nth-child(2n)` y un elemento con `nth=4` — **entonces** matchea;
  con `nth=0` (desconocido) — **entonces** NO matchea (fail closed).
- **Dado** `A + B` (`A ~ B`) y un sujeto con `prev` poblado — **entonces** `+`
  exige que el hermano inmediatamente anterior matchee `A`; `~` prueba cada
  hermano previo de la cadena. **Dado** `prev == NULL` — **entonces** no matchea.
- **Dado** cualquier entrada hostil de hasta `CSS_TOK_MAX`-truncada — **cuando**
  se parsea/matchea — **entonces** no hay I/O, ni asignación, ni recursión sin
  cota (profundidad ≤ `CSS_MAX_COMPOUNDS`; el backtracking de descendiente/`~`
  está acotado por las cadenas del llamador).

## Tabla de errores

| Condición | Resultado |
| :-- | :-- |
| Sintaxis no soportada / malformada | `csel_parse` → 0 (selector descartado) |
| `An+B` malformado o \|A\|/\|B\| > `CSS_NTH_MAX` | `csel_parse` → 0 |
| `nth`/`nsib` = 0 en pseudo estructural | `csel_matches` → 0 (no matchea) |
| `prev` = NULL en combinador hermano | `csel_matches` → 0 |
| Elemento NULL | `csel_matches` → 0 |

## Garantías de seguridad

- **Puro y reentrante:** sin estado global, sin I/O, sin asignaciones.
- **Fail closed:** lo no soportado se descarta entero; lo desconocido no matchea.
- **Acotado (anti-DoS):** compuestos ≤ 4, atributos ≤ 4, pseudo-clases ≤ 4 por
  compuesto, tokens ≤ `CSS_TOK_MAX`; el emparejado recorre solo las cadenas que
  el llamador construyó (page_view las acota a 32 ancestros / 16 hermanos).
- El contenido de un selector es **remoto hostil**: se fuzzea vía `make fuzz-css`
  (la hoja completa) con elementos sintéticos que poblan `nth`/`nsib`/`prev`.

## Fuera de alcance

`:not()`/`:is()`/`:where()`/`:has()`, familia of-type, `:empty`/`:target`/
`:lang()`, pseudo-elementos `::` (y sus grafías legadas de un solo `:`), y el
re-matcheo dinámico de `:hover`/`:focus` (necesita re-cascada por evento de
puntero — hito de interactividad). La semántica de qué pseudo-clase matchea qué
estado vive en `spec/css.md` §Pseudo-clases.

## Identificadores: escapes y nombres largos (2026-09-29)

Medido en snapshots de sitios del allowlist: huggingface.co trae **6425** selectores con
escapes (Tailwind: `.md\:flex`, `.w-1\/2`, `.\32xl\:p-4`, `.\[mask\:f\(x\)\]`) y github.com
nombres de CSS Modules de **72 bytes** (`Primer_Brand__LogoSuite-module__…___bUhyS`). Los
dos se perdían en silencio: el `\` terminaba el selector (se descartaba entero) y el nombre
largo se **truncaba** a 63 bytes, así que nunca coincidía con la clase real del elemento.

- `csel_read_ident` lee tag/`.clase`/`#id` decodificando escapes con el MISMO decodificador
  de CSS Syntax §4.3.7 que usa `content` (`csel_unescape`, movido desde `css.c`): `\` + 1–6
  hex (+ un blanco opcional que pertenece al escape) es el codepoint en UTF-8; `\` + otro
  carácter es ese carácter. Los bytes ≥ 0x80 son caracteres de identificador.
- Los escaneos que parten el texto del selector (compuestos, argumentos de
  `:not()`/`:is()`, la lista por comas en `css.c`) saltan un escape completo
  (`csel_escape_len`): `\,`, `\(`, `\ ` y `\>` son bytes del identificador, no sintaxis.
- Un identificador decodificado de ≥ `CSS_TOK_MAX` bytes se guarda **plegado**
  (`csel_ident_fold`): primeros 40 bytes + `0x1F` + 16 hex del FNV-1a de 64 bits del nombre
  completo. `csel_ident_eq` pliega igual el token del elemento, así que la comparación es
  exacta salvo colisión de 64 bits — y una colisión solo haría que la página se estile a sí
  misma. Ampliar los buffers habría cuadruplicado `css_sel` (12.7 KB → ~50 KB por selector;
  github tiene decenas de miles).

Dado `.md\:flex{…}`, cuando un elemento tiene `class="md:flex"`, entonces coincide.
Dado un nombre de 72 bytes, cuando otro elemento comparte sus primeros 63 bytes pero no la
cola, entonces **no** coincide (el truncado viejo sí lo hacía coincidir con el prefijo).
Fuera de alcance: escapes en valores de atributo sin comillas y en nombres de pseudo-clase.
