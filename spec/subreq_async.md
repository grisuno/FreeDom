# subreq_async — subpeticiones asíncronas por lotes (XHR/fetch de allow∩js)

## Problema
Cada XHR/`fetch` del worker bloqueaba hasta que el padre terminaba la descarga: las N
peticiones de una página (YouTube: >100) se servían **en serie**, y el worker esperaba cada
una. Medido: ~22 s de carga, 27 % dentro de la llamada de red del `xhr-shim`.

## Contrato
- **Dado** un XHR con `async=true` o un `fetch()` en un worker con red concedida, **cuando**
  se llama a `send()`/`fetch()`, **entonces** el worker escribe un frame `TAG_SUBREQ_ASYNC`
  (mismos campos que `TAG_SUBREQ`) y **no espera la respuesta**; el resultado llega por callback.
- **Dado** un frame `TAG_SUBREQ_ASYNC`, **cuando** el padre lo lee, **entonces** valida los
  permisos (`tab_subreq_permitted`) y lanza la descarga en un hilo (máx. `TAB_ASYNC_THREADS`
  simultáneas) por el MISMO fetcher con TODA la política; sigue leyendo frames.
- **Dado** `TAG_NETWAIT`, **cuando** lo recibe el padre, **entonces** une todos los hilos y
  escribe, en orden de emisión, una respuesta por petición pendiente (formato de `TAG_SUBREQ`).
  El presupuesto de red de la operación cuenta el tiempo de pared de la espera, no la suma.
- **Dado** que el worker recibió las respuestas, **entonces** las entrega a JS en orden de
  emisión, vacía los microtasks y, si las callbacks emitieron más peticiones, repite
  (`TAB_MAX_NET_ROUNDS`). Se drena al final de la carga y al final de cada operación
  (`child_handle_mutation`), antes de derivar la vista.
- **Formato de respuesta** (igual para `TAG_SUBREQ` y `TAG_NETWAIT`): `[status:int32][len][body][clen][ctype]
  [hlen][headers][ms:int32]`. `ms` es el tiempo de pared del fetch **medido por el padre** (en el hilo que lo
  ejecuta, sin contar la espera de turno): el reloj de la página está normalizado, solo el padre puede medirlo.
  Llega a `net()` del REPL (`ms`, `reqHeaders`, `respHeaders`) y a la pestaña Net de Freebug; solo existe en
  hosts allow∩js (los únicos con red de página). Una petición síncrona no se mide (`ms = -1`).
- XHR **síncrono** (`open(...,false)`), scripts, módulos y hojas siguen por `TAG_SUBREQ`.
- Contextos sin gancho asíncrono (tests de `js_dom`) conservan el camino síncrono.

## Seguridad
- Zero Trust: un frame asíncrono forjado pasa por el mismo gate que el síncrono.
- Tope de peticiones pendientes (`TAB_MAX_ASYNC_PENDING`) y de bytes acumulados por lote;
  excedido ⇒ respuesta de rechazo (status 0), el protocolo nunca se desincroniza.
- El worker no toca sockets ni threads nuevos: los hilos son del padre.

## Fuera de alcance
Entrega entre operaciones (callbacks sin tick), streaming, `AbortSignal` en vuelo.

## Verificación
`tests/test_subreq_batch.c` (módulo: orden, tope de hilos, rechazos, reutilización) y
`test_async_subrequests_run_in_parallel` en `tests/test_tab.c` (4 XHR + 1 `fetch` + 1 síncrono sobre un worker
real: solapan >= 3, callbacks en orden de emisión, `ms` 100..5000). `make asan` limpio. **Medido:** YouTube,
tiempo del worker 22 s -> 3,1 s. **Sin fuzzear** (la lectura de campos del frame es la misma de `TAG_SUBREQ`;
no hay fuzzer del IPC del tab todavía): abierto.
**Nota de harness:** `--download-png` bombea hasta 240 ticks virtuales y cada tick espera a la red; el tiempo de
pared de la exportación no mide el uso real (la ventana corre en tiempo real).
