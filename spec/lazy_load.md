# lazy_load -- carga diferida de recursos (`ll_`)

Un recurso que la página nombra pero el usuario aún no ve (`<img loading=lazy>`, `background-image`
de CSS) no se pide hasta que su caja entra a `FC_LAZY_IMAGE_MARGIN_PX` del viewport. Privacy by
Default no cambia: lo que sí se pide pasa por el mismo fetcher gateado.

## `ll_near_viewport(top, height, view_top, view_h, margin)` (puro)

- Dado un tramo vertical dentro del viewport ampliado por `margin`, Cuando se consulta, Entonces 1.
- Dado un tramo enteramente fuera (arriba o abajo) de ese rango, Entonces 0.
- Dado `height < 0` (la caja nunca se colocó: subárbol fuera de flujo), Entonces 1: **falla abierto**,
  el contenido nunca queda sin cargar.

## Fondos CSS en la GUI

- La ventana registra cada `background-image` (capas 1 y 2) como diferido (`deferred`) con el índice de
  su caja; no se pide ni decodifica al cargar la página.
- Tras el layout estable de cada pintado, los diferidos cuya caja (`rc_box.block_id`) está cerca se piden
  (máx. `UI_LAZY_PER_PASS` por pintado, y solo si el worker no tiene un trabajo en curso); una URL ya
  decodificada se reutiliza. Un fondo es decoración: no cambia el flujo, así que no hay re-layout.
- El render headless (`--download-png/pdf`) sigue cargando todo: un export es de página completa.
