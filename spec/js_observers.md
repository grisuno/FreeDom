# spec: js_observers (IntersectionObserver real, host de confianza)

Vive en `src/js_trusted.c` (`jt_enable_observers`, `jt_geometry_changed`).

## Problema
El `IntersectionObserver` sintetico (`js_dom.c`) reporta siempre `isIntersecting:true`: todo
sitio con carga lazy revela y carga todo de golpe, y nada reacciona al scroll. Firefox carga
al acercarse al viewport.

## Contrato
- **Dado** un host allow∩js, **cuando** carga la pagina, **entonces** `tab` instala el observer
  real ANTES de los scripts (deteccion de caracteristicas). Un host no confiable conserva el
  sintetico y jamas ve geometria (`typeof __ioTick === 'undefined'`).
- **Dado** un target observado, **cuando** el padre instala una tabla `js_geom` (layout o scroll),
  **entonces** se mide su rect (coordenadas de documento) contra el viewport real mas
  `rootMargin` (px, 1-4 valores; `%` se trata como 0) y se notifica cuando cambia su estado
  (fuera / dentro / umbral alcanzado). La primera medicion siempre notifica (spec W3C).
- Un target sin rect (aun sin layout, `display:none`) no notifica.
- **Cuando** el scroll cambia entre dos tablas, se despacha un evento `scroll` en `window`.
- Cotas: 2048 observers vivos, 32 umbrales, `unobserve`/`disconnect` liberan.
- `jt_geometry_changed` sin `jt_enable_observers` es no-op.
- El GUI agenda un `tab_tick` de 0 ms tras publicar geometria para recoger mutaciones del DOM
  hechas por los callbacks (p. ej. `img.src = img.dataset.src`).

- **Headless (`--js=on`/`--as-gui`):** una pagina de confianza recibe su geometria aunque no
  tenga ningun timer pendiente, y tras publicarla se relee la vista con un `tab_tick` de 0 ms
  (sin avanzar el reloj virtual): lo que un callback de observer muta aparece en el export.
  Un objetivo fuera del viewport de 1000x1080 queda sin revelar, como en Firefox sin scroll.
  Test: `test_headless_intersection_observer_reveals_visible_only`.

## ResizeObserver real
- Host de confianza: `observe(el)` mide el rect del layout; dispara cuando el tamano difiere del
  ultimo reportado (inicial 0x0: un objetivo 0x0 o sin rect no dispara). Entrega
  `contentRect`/`borderBoxSize`/`contentBoxSize` (caja de borde: no hay modelo de padding aparte).
  Se reevalua en cada `jt_geometry_changed`. Host no confiable: sintetico, sin geometria.

## Fuera de alcance (siguientes hitos)
`loading="lazy"` nativo en `<img>` (diferir la descarga hasta acercarse), `root` explicito,
`%` en `rootMargin`, `MutationObserver`/`ResizeObserver` reales.
