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
  por diseño). **Dado** `:hover`/`:focus`/`:active` — **entonces** siempre
  matchean (PSEUDO_ALWAYS, 2026-07-11: la cascada se resuelve una vez por carga;
  el contenido oculto tras `:hover` se vuelve visible. Sin re-cascada interactiva
  aún). El selector parsea y cuenta especificidad en todos los casos.
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
