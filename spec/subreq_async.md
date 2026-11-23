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

## Entrega con plazo (2026-11-22)
Una petición lenta (un host de anuncios caído: 8 s de connect) no puede retener la PRIMERA vista de
la página: Firefox pinta y deja la petición en vuelo. Por eso `TAG_NETWAIT` lleva un plazo:

- **Frame:** `TAG_NETWAIT [wait_ms:uint32]`. **Respuesta:** `[k:uint32]` seguido de `k` veces
  `[pos:uint32]` + respuesta (formato de arriba): **todas** las peticiones terminadas cuando todas
  terminaron o venció `wait_ms` (sin fetcher estable: cuando terminaron todas), en orden de emisión entre ellas. `pos` es
  el índice de esa petición en la cola de pendientes del worker **después** de quitar las anteriores
  del mismo lote (el worker hace `splice(pos,1)`); `pos` fuera de rango ⇒ fin del drenado (fail-closed).
- Como en un navegador, las callbacks corren en orden de **finalización**, no de emisión: un host
  muerto emitido primero no retiene a los que vienen detrás. Lo que no terminó sigue en su hilo.
- **Dado** el fin de la carga, **cuando** el worker drena, **entonces** espera hasta
  `FC_NET_LOAD_SETTLE_MS` en total (varias rondas comparten el plazo) y responde con lo que haya.
- **Dado** un tick/click, **cuando** drena, **entonces** `wait_ms = FC_NET_TICK_SETTLE_MS` (250):
  una API típica responde en el mismo tick que la pidió, como antes; una lenta llega en uno posterior.
- **Dado** que quedan peticiones pendientes, **entonces** el worker reporta
  `next_timer_ms ≤ FC_NET_POLL_MS`, así el padre sigue haciendo ticks hasta que lleguen.
- El headless/export no declara fetcher estable, así que espera todas las respuestas: el PNG sigue
  reflejando la página entera (diagnóstico determinista). Solo la ventana entrega con plazo.
- Una ronda que no entregó nada termina el drenado (nunca se gira en vacío).
- `TAB_MAX_ASYNC_PENDING` cuenta también las que sobreviven entre operaciones.

### Fetcher estable y abandono (memoria)
Una petición que sobrevive a la carga no puede seguir usando el fetcher DE la carga (la GUI lo
arma en su pila, con el pool de prefetch) ni la `tab*`, que puede cerrarse antes de que termine.

- **Dado** que el dueño llamó `tab_set_async_fetcher(t, fn, ctx)` (contrato: `fn/ctx` viven más
  que cualquier petición en vuelo; la GUI pasa su fetcher de ventana), **entonces** cada petición
  diferida corre con ESE par, capturado en el lote; nunca con `tab*` ni con el fetcher de carga.
- **Dado** que no lo llamó (headless, frames, tests), **entonces** el padre espera TODAS las
  peticiones en cada `TAG_NETWAIT` (comportamiento anterior): nada puede sobrevivir a su fetcher.
- **Dado** una pestaña que navega o se cierra con peticiones en vuelo, **cuando** se descarta el lote,
  **entonces** las terminadas se liberan y las que siguen corriendo se **abandonan**
  (`sqb_abandon`: hilo desacoplado; el trabajo y el lote se liberan cuando termina el último, por
  refcount): cerrar no bloquea. El resultado de una abandonada se descarta.

## Seguridad
- Zero Trust: un frame asíncrono forjado pasa por el mismo gate que el síncrono.
- Tope de peticiones pendientes (`TAB_MAX_ASYNC_PENDING`) y de bytes acumulados por lote;
  excedido ⇒ respuesta de rechazo (status 0), el protocolo nunca se desincroniza.
- El worker no toca sockets ni threads nuevos: los hilos son del padre.

## Fuera de alcance
Streaming, `AbortSignal` en vuelo. Una petición abandonada sigue usando la red hasta su timeout
(abierto: cancelarla por `sf_config.cancel_cb`).

## Verificación
`tests/test_subreq_batch.c` (módulo: orden, tope de hilos, rechazos, reutilización) y
`test_async_subrequests_run_in_parallel` en `tests/test_tab.c` (4 XHR + 1 `fetch` + 1 síncrono sobre un worker
real: solapan >= 3, callbacks en orden de emisión, `ms` 100..5000). `make asan` limpio. **Medido:** YouTube,
tiempo del worker 22 s -> 3,1 s. **Sin fuzzear** (la lectura de campos del frame es la misma de `TAG_SUBREQ`;
no hay fuzzer del IPC del tab todavía): abierto.
**Nota de harness:** `--download-png` bombea hasta 240 ticks virtuales y cada tick espera a la red; el tiempo de
pared de la exportación no mide el uso real (la ventana corre en tiempo real).
