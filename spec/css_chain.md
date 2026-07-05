# css_chain — cadena DOM→selector y resolución de estilo por elemento

> Módulo interno extraído de `page_view` (cláusula anti-monolito §3.4: el Hito
> 23b-9 empujó `page_view.c` sobre las ~2000 líneas). Es el puente entre el DOM
> vivo de lexbor (contenido hostil ya parseado, dentro del worker confinado) y el
> motor puro `css`/`css_select`: arma el `css_element` de un elemento con todo su
> contexto acotado y resuelve su estilo de autor por la cascada.

## Entradas / salidas

- `css_style cch_element_style(lxb_dom_element_t *el, const css_sheet *sheet)` —
  estilo de autor resuelto para `el` (reglas de la hoja + su `style=` inline,
  inline gana). `sheet` puede ser NULL (solo inline).

## Contrato (Dado-Cuando-Entonces)

- **Dado** un elemento del DOM real — **cuando** se resuelve — **entonces** el
  `css_element` que ve el matcher lleva: cadena de **ancestros** acotada a
  `CCH_CHAIN_MAX` (32; combinadores descendiente/hijo), **atributos** por nivel
  (para `[attr]`; nombre en minúsculas, buffers acotados), **posición entre
  hermanos** `nth`/`nsib` por **cada** nodo de la cadena (caminata acotada a
  `CCH_NTH_MAX` (1024); más allá lee 0 = desconocido) y la cadena de **hermanos
  previos del sujeto** acotada a `CCH_SIB_MAX` (16; para `+`/`~` y sus pseudo-
  clases), cada hermano compartiendo el padre del sujeto y derivando su posición
  de la del sujeto.
- **Dado** cualquier tope excedido (token largo, cadena profunda, hermano lejano,
  posición más allá del cap) — **entonces** ese dato queda ausente/desconocido y
  el selector correspondiente **no matchea** (fail closed, jamás un falso
  positivo).
- **Dado** un `+`/`~` en un compuesto no-sujeto (`h1 + div p`) — **entonces** no
  matchea en v1 (los ancestros no llevan `prev`); documentado en `spec/css.md`.

## Garantías de seguridad

- Sin I/O, sin asignaciones (todo en buffers del stack del llamador), reentrante.
- El contenido (tags/atributos/clases hostiles) solo se copia truncado a buffers
  acotados; el truncado falla cerrado (no matchea).
- Corre dentro del worker confinado (page_view); se fuzzea vía `make fuzz-pv`
  (HTML hostil + hoja hostil por `pv_build_styled`).

## Fuera de alcance

Cachear posiciones de hermanos entre elementos (coste acotado ya; optimización,
no contrato), `prev` en ancestros, y cualquier semántica de selector (vive en
`spec/css.md` / `spec/css_select.md`).
