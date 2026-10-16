# css_index — índice de reglas de la cascada (`cix_`)

## Por qué

`resolve_core` probaba **cada selector de la hoja contra cada elemento**. github.com
trae ~6 MB de CSS (~40.000 selectores) para ~1.800 elementos: 12 s de cascada en el
worker contra ~1 s de Firefox para la página entera (medido 2026-10-15). Gecko y
Blink no hacen eso: agrupan las reglas por la clave más selectiva del compuesto
**sujeto** (id, clase, etiqueta) y solo prueban las que pueden aplicar
(el *RuleHash* de Gecko, `RuleSet` de Blink).

## Contrato

- `cix_build(sels, n, &idx)`: clave de cada selector = su compuesto sujeto
  (`parts[nparts-1]`): `#id` si lo tiene, si no su primera `.clase`, si no su
  etiqueta, si no **universal** (`*`, `[attr]`, `:root`, `:is()`, …).
- `cix_candidates(&idx, el, &buf, &n)`: índices de los selectores que **pueden**
  matchear `el`: los del cubo de su id, de cada una de sus clases, de su etiqueta y
  el cubo universal, **en orden ascendente y sin duplicados**.
- El índice es solo un pre-filtro: `csel_matches` sigue decidiendo. Una colisión de
  hash amplía los candidatos, nunca los reduce.

## Garantías

- **Equivalencia (la propiedad que importa):** para todo selector `s` y elemento
  `el`, `csel_matches(s, el) ⇒ s ∈ cix_candidates(el)`. Las claves se calculan sobre
  la MISMA forma canónica que compara `compound_matches`: id y clase exactos (un
  token del elemento de ≥ `CSS_TOK_MAX` bytes se pliega con `csel_ident_fold` igual
  que el almacenado), etiqueta en minúsculas (`csel_ci_eq`).
- **Orden idéntico:** los candidatos salen en orden de documento, así que la cascada
  aplica las mismas declaraciones en el mismo orden que el recorrido lineal ⇒ salida
  byte-idéntica (`layout-diff`).
- **Fail-safe:** si el índice no existe, falló por OOM, o se construyó para otro
  número de selectores (`idx.nsels != sheet->nsels`), la cascada vuelve al recorrido
  lineal. Nunca hay una cascada parcial.
- Sin estado global; el índice lo posee la hoja (`css_free` lo libera,
  `sheet_rewind` lo invalida). Memoria O(n).

## Dado-Cuando-Entonces

- Dado `.a{}`, `#b{}`, `p{}`, `*{}`, `[x]{}`, cuando se consulta `<p class=a>`
  sin id, entonces candidatos = {`.a`, `p`, `*`, `[x]`}, en orden de documento.
- Dado un elemento con la clase repetida (`class="a a"`), entonces `.a` aparece una
  sola vez.
- Dado `div.a#b`, la clave es el id: solo un elemento con `id=b` lo ve.
- Dado un nombre de clase de 80 bytes, un selector con ese nombre (plegado al
  parsear) es candidato del elemento con ese token.
- Dado `P{}` (etiqueta en mayúsculas en la hoja) y `<p>`, es candidato.

## Fuera de alcance

Filtro de Bloom de ancestros (descarta `.x .y` cuando ningún ancestro es `.x`): el
siguiente paso si la cascada vuelve a dominar.
