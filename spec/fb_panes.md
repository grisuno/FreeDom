# spec: fb_panes (`fbp_`)

Modelo puro de las **pestañas de Freebug** (Consola / HTML / CSS / Script / Red), al estilo de Firebug.
Decide tres cosas y nada más: qué pestaña está activa y cómo se navega entre ellas, dónde cae cada
pestaña en la barra (geometría para pintar y para el clic) y **qué expresión JS** alimenta cada panel.
Sin E/S, sin Cairo, sin Wayland, sin estado global, reentrante. La ventana (`gui/browser_ui.c`) solo
pinta lo que este módulo describe y reenvía la expresión al worker del REPL; el camino headless
`--dump-pane=PESTAÑA[:ARG]` usa la **misma** expresión (una sola fuente de verdad).

## Pestañas
| id | etiqueta | argumento (editor) | panel |
| :-- | :-- | :-- | :-- |
| `FBP_CONSOLE` | Console | JS del REPL | transcripción de `console.*` y del REPL (como hoy) |
| `FBP_HTML` | HTML | selector CSS (vacío = `<html>`) | árbol del DOM con atributos y texto, sangrado |
| `FBP_CSS` | CSS | selector CSS (vacío = `body`) | reglas que coinciden (la ganadora primero, `~` = pisada), estilo calculado y caja |
| `FBP_SCRIPT` | Script | número 1..N (vacío = lista) | lista de `<script>`; con número, su código con líneas numeradas |
| `FBP_NET` | Net | subcadena de URL (vacío = todo) | peticiones XHR/fetch de la página: método, estado, **tiempo (ms)**, tipo, URL, tamaño; con varias, un total; con UNA coincidencia, cabeceras de petición y respuesta |

## Contrato
- **Dado** un id fuera de rango, **cuando** se pide etiqueta, vecino o expresión, **entonces** se trata
  como `FBP_CONSOLE` (nunca indexa fuera de la tabla).
- `fbp_tab_wrap(tab, dir)`: avanza cíclicamente (`dir>0` siguiente, `dir<0` anterior, 0 = misma).
- `fbp_tab_from_name`: nombre sin distinguir mayúsculas (`html`, `css`, `script`, `net`, `console`);
  desconocido = `-1` (la CLI lo rechaza, no adivina).
- Geometría: las pestañas son contiguas en orden, cada una de ancho `cell_w * (letras + 2 * pad)`;
  `fbp_tab_at(x, ...)` devuelve la pestaña bajo `x` o `-1` fuera de la barra. `fbp_tab_span` es su
  inversa exacta (lo que se pinta es lo que se golpea).
- `fbp_js_quote(s, n, out, cap)`: literal de cadena JS entre comillas dobles. Escapa `\`, `"`, `\n`,
  `\r`, `\t` y todo byte `< 0x20` o `0x7f` como `\u00XX`; los bytes `>= 0x80` pasan tal cual (UTF-8).
  **Falla cerrada:** `n > FBP_SELECTOR_MAX`, un NUL embebido o un `cap` que no alcanza devuelven 0 y no
  dejan salida parcial utilizable.
- `fbp_expr(tab, sel, n, out, cap)`: `(function(q){ CUERPO })("sel")`. El argumento del usuario solo
  entra como literal de cadena (`fbp_js_quote`): **nunca se concatena como código**, así que un
  selector `"});alert(1);("` no escapa del literal. `FBP_CONSOLE` no tiene expresión (0).
  La expresión no escribe en la consola de la página ni toca el DOM; devuelve una cadena.
- Cotas: selector 256 bytes, expresión 4096 + selector escapado, panel 800 líneas (HTML), 2000 líneas
  (Script), 256 scripts listados.

## Fuera de alcance (honesto)
Depurador con puntos de ruptura/paso a paso (QuickJS-ng embebido no expone un depurador al worker
confinado), edición en vivo de CSS desde el panel (el REPL ya permite `insertRule`), tiempos de red de
peticiones **síncronas** (`ms = -1`; las asíncronas sí se miden, `spec/subreq_async.md`) y selección de elemento con el ratón sobre la página.

## Pestañas DOM y Storage

`FBP_DOM` ("DOM", argumento: selector, vacío = `body`): etiqueta, ruta de ancestros (`html > body > p#a`), atributos, estado
(`id`, `className`, `hidden`, `href`, `src`, `textContent`; `value/checked/disabled/type/name` solo en controles de formulario),
geometría (`getBoundingClientRect`, `offset*`, `client*`) y modo del `shadowRoot`. `FBP_STORAGE` ("Storage"): cookies visibles
al script, `localStorage` y `sessionStorage` de la página (clave = valor, 120 caracteres por valor, 256 claves). Ambas **solo
leen**: ninguna expresión llama `setItem`/`removeItem` ni escribe en el DOM. La línea de comandos (historial, Tab,
filtro de consola) vive en `spec/fb_cmdline.md`.

## Pestañas Profile y Throws

`FBP_PROFILE` ("Profile") ejecuta `profile()` y `FBP_THROWS` ("Throws") ejecuta `throws()` del REPL: el
perfil ponderado por tiempo y el registro de TODA excepción lanzada (también las capturadas), ambos del
motor (`spec/js_sandbox.md` 7p/7q). Fallan blandos: sin la API (página no allow∩js) dicen
`(profile() unavailable)`. Mismo mecanismo en la ventana y en `--dump-pane=profile|throws`.
