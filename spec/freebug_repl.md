# spec: freebug_repl (API de linea de comandos del REPL)

`jd_install_repl_api` (`src/js_dom_ext.c`, declarado en `include/js_dom.h`), llamada por
`tab` en el primer `OP_EVAL` de una pagina (`child_state.repl_api`).

## Contrato
- **Dado** un script de la pagina, **cuando** consulta `typeof $$`/`inspect`/`keys`/
  `getEventListeners`, **entonces** es `undefined`: la API existe SOLO en el worker del REPL
  (Freebug F12, Ctrl+Enter). Una pagina no puede detectar Freebug por esta via.
- Se definen como globales NO enumerables y nunca reemplazan un global real de la pagina.
  `$` es `querySelector` salvo que la pagina haya cargado jQuery real; el stub de compatibilidad
  de Freedom (`JQ.__stub`) SI se reemplaza.
- `$(sel[,ctx])`, `$$(sel[,ctx])` (array), `keys(o)`, `values(o)`.
- `inspect(el)` devuelve `{tag,id,classes,attributes,style,rect,text,children}` y registra una
  linea resumen en la consola; `rect` es `null` sin geometria (host no confiable).
- `getEventListeners(el|document|window)` -> `{tipo:[{listener,useCapture,once,passive,type}]}`
  desde el registro unico de listeners (`__evList`, solo lectura).
- `monitorEvents(el[,tipos])` / `unmonitorEvents(el[,tipos])`: registra cada evento en la
  consola. Cota 256 monitores.

## Paneles como comandos (Elementos / CSS / Red)
- `tree([el[,depth]])`: esquema del DOM (`<div#id.cls>`, 2 espacios por nivel, profundidad 3 por
  defecto, tope 32 niveles / 400 lineas); lo devuelve y lo registra en la consola.
- `styles(el[,filtro])`: estilos calculados (cascada real, `spec/js_computed_style.md`) sin los valores
  iniciales; objeto `{propiedad: valor}` y una linea en la consola.
- `box(el)`: `{margin,border,padding}` por lado (px) y `content` `{width,height}` o `null` sin geometria.
- `net([filtro])`: peticiones XHR/fetch/beacon de la pagina (`method,url,status,size,type`), acotado a
  512. El lector se captura una vez y el global `__netLog` se borra al instalarse la API.
- Headless: `freedom --headless --eval='EXPR' pagina` ejecuta una linea del REPL (valor a stdout,
  consola a stderr), el mismo camino que la ventana Freebug.

## Fuera de alcance (siguiente hito)
Pestanas graficas dedicadas (hoy son comandos en la consola), reglas CSS que coinciden por
elemento, tiempos de red.
