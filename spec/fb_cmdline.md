# spec: fb_cmdline (`fbc_`)

Modelo puro de la **línea de comandos de Freebug** (lo que Firebug llama "command line"): historial del
REPL, autocompletado de propiedades y filtro de la consola. Sin E/S, sin Cairo, reentrante; la ventana
(`gui/browser_ui.c`) solo cablea teclas y pinta.

## Historial (`fbc_history`)
- **Dado** un texto no vacío de a lo sumo `FBC_ENTRY_MAX` bytes, **cuando** se hace `push`, **entonces** queda
  como la entrada más nueva; vacío, igual a la última o más largo que el tope se ignora (`-1` solo el exceso).
  Cota `FBC_HIST_MAX` (64): al llenarse cae la más vieja.
- `prev(cur)` retrocede una entrada; al dejar la línea viva guarda `cur` como **borrador**. Sin entradas
  más viejas devuelve `NULL` y no mueve nada. `next()` avanza; al pasar la más nueva devuelve el borrador
  (cadena vacía si no había); en la línea viva devuelve `NULL`.
- `push` vuelve a la línea viva y descarta el borrador. Un único dueño, `free` idempotente.

## Autocompletado
- `fbc_complete_split(text, n, base, cap, &poff)`: toma la ruta final `a.b.c` (solo `[A-Za-z0-9_$.]`),
  separa `base` (`a.b`, vacío = global) y el prefijo (desde `poff`). Devuelve el largo del prefijo, o `-1`
  si no hay nada completable (nada escrito, ruta con `..`, punto inicial, `base` que no cabe).
- `fbc_names_expr(base, out, cap)`: expresión JS que lista los nombres (con la cadena de prototipos, acotada)
  de la ruta `base`. La ruta entra como **literal de cadena** (nunca se concatena como código) y se resuelve
  paso a paso con descriptores. Un accessor **sobre la ruta tipeada** se sigue (`document.body`; Enter lo
  evaluaría igual); listar los nombres del dueño final no ejecuta ningún getter.
- `fbc_complete_pick(names, prefix, plen, ins, ins_cap, list, list_cap, &count)`: de la lista (una por
  línea) toma las que empiezan con el prefijo; `ins` es el prefijo común más largo **menos** el prefijo ya
  escrito, `list` las candidatas separadas por espacio (tope 40), `count` cuántas hay.

## Filtro de consola
`FBC_FILTER_ALL/ERRORS/WARNINGS/LOGS`. `ERRORS` = `FB_ERROR`; `WARNINGS` = `FB_WARN`; `LOGS` = `FB_LOG`,
`FB_INFO`, `FB_DEBUG`. Un filtro o nivel fuera de rango se trata como `ALL` / visible (nunca oculta por error).
`fbc_filter_next` es cíclico.

## Fuera de alcance
Completado de corchetes (`a[0].b`), de llamadas (`f().x`) y de palabras clave; búsqueda incremental en el
historial; persistencia del historial a disco (Zero Knowledge: vive en RAM de la ventana).
