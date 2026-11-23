# scroll_req (`srq_`) — desplazamientos pedidos por un script, `scroll-margin`/`scroll-padding`

> Estado: tanda 104 (2026-11-23). Módulo puro `scroll_req` (`srq_`), sin I/O ni estado global.
> Consumidores: `src/tab.c` (worker: registra; padre: valida), `gui/browser_ui.c` (ventana: aplica).

## 1. Por qué

Hasta la tanda 103 `window.scrollTo()`, `scrollBy()`, `scroll()`, `Element.scrollIntoView()` y
`document.documentElement.scrollTop = y` eran funciones vacías: el worker no tiene ventana ni
layout, y no existía canal worker→padre para pedir un desplazamiento. Un «volver arriba» con JS,
el índice de una SPA o un `scrollIntoView` tras un filtro no hacían nada. Y el destino de un ancla
quedaba bajo una cabecera `position:fixed` porque `scroll-margin`/`scroll-padding` se ignoraban.

## 2. Modelo

1. **Registrar** (worker, JS): cada llamada sobreescribe UNA petición pendiente (la última gana,
   como varios `scrollTo` seguidos antes de pintar):
   - `scrollTo(x, y)` / `scroll(x, y)` / `scrollTo({top, behavior})` ⇒ `SRQ_TO`, `y` absoluto;
     sin `top`/`y` numérico finito no hay petición (solo el eje horizontal, que el motor no tiene).
   - `scrollBy(dx, dy)` / `scrollBy({top})` ⇒ `SRQ_BY`, `y` relativo (el padre conoce el scroll real;
     el worker no, y no debe: `scrollY` sigue normalizado salvo para allow∩js).
   - `el.scrollIntoView()` / `(true)` ⇒ `block: start`; `(false)` ⇒ `end`;
     `({block, behavior})` con `start|center|end|nearest` ⇒ `SRQ_ELEMENT` con el handle.
   - `scrollTop = y` sobre `<html>`, `<body>` o `document.scrollingElement` ⇒ `SRQ_TO`;
     `el.scrollBy()` sobre esos ⇒ `SRQ_BY`. Otros elementos: sin cambio (contenedores internos
     desplazables quedan fuera de alcance).
   - `behavior`: `smooth` ⇒ `SRQ_SMOOTH`, `instant` ⇒ `SRQ_INSTANT`, otro ⇒ `SRQ_AUTO`.
2. **Enviar** (worker, C): al final de la respuesta de carga y de la de mutación (clic, tick,
   evento, ancla, socket) viaja `[SRQ_WIRE_N × int32][n × handle]`. Para `SRQ_ELEMENT` el worker
   recolecta el subárbol del destino con `anc_collect` (los mismos handles que un ancla) y calcula
   su `scroll-margin-top/bottom` computado.
3. **Validar** (padre, Zero Trust): `srq_decode` rechaza todo registro fuera de rango (tipo,
   `behavior`, `block`, coordenada `|y| > SRQ_MAX_COORD`, márgenes fuera de `[-SRQ_MAX_COORD,
   SRQ_MAX_COORD]`, `n`/`nsub` incoherentes): el worker muere (desincronización = fallo cerrado).
4. **Aplicar** (ventana): la caja del destino sale de la tabla de geometría del layout retenido
   (`anc_target_box`: el mínimo `y` y el máximo `y+h` del subárbol, o el primer elemento posterior
   que pintó) y `srq_target` da el scroll final, acotado a `[0, max]`. Se anima si
   `srq_smooth(req, root_smooth)`: `SRQ_SMOOTH`, o `SRQ_AUTO` con `scroll-behavior: smooth` en
   la raíz (CSSOM View §12.1). Un resultado en segundo plano (pestaña oculta) no desplaza nada.

## 3. Región de visión óptima (CSSOM View §4, Scroll Snap 1 §4.1)

`scroll-padding` de la RAÍZ (el `<html>`) achica el puerto de desplazamiento: la región útil es
`[scroll + pad_top, scroll + view_h − pad_bottom]`. `scroll-margin` del DESTINO agranda su caja:
`[top − margin_top, bottom + margin_bottom]`. Con eso:

| `block` | scroll resultante |
| :-- | :-- |
| `start` | `top − margin_top − pad_top` |
| `end` | `bottom + margin_bottom + pad_bottom − view_h` |
| `center` | centro de la caja al centro de la región útil |
| `nearest` | sin cambio si la caja está dentro de la región o la cubre por ambos lados; si sobresale por arriba (o es más alta que la región y sobresale por abajo) ⇒ `start`; si no ⇒ `end` |

El mismo cálculo (`block: start`) ubica un **ancla** (`spec/anchor.md`): un fragmento bajo una
cabecera fija respeta el `scroll-padding-top` del autor como en Firefox. Los paddings se acotan a
`≥ 0` y, si su suma supera el alto del viewport, se ignoran (la región quedaría vacía).

## 4. API (C)

```c
#define SRQ_MAX_COORD 10000000
#define SRQ_WIRE_N    8
typedef enum { SRQ_NONE, SRQ_TO, SRQ_BY, SRQ_ELEMENT } srq_kind;
typedef enum { SRQ_AUTO, SRQ_INSTANT, SRQ_SMOOTH } srq_behavior;
typedef enum { SRQ_START, SRQ_CENTER, SRQ_END, SRQ_NEAREST } srq_block;
typedef struct { int kind, behavior, block; double y, margin_top, margin_bottom;
                 size_t n, nsub; } srq_req;
typedef struct { double scroll, max_scroll, view_h, pad_top, pad_bottom; } srq_view;

void srq_encode(const srq_req *r, int32_t out[SRQ_WIRE_N]);
int  srq_decode(const int32_t in[SRQ_WIRE_N], size_t max_handles, srq_req *out);
int  srq_target(const srq_req *r, const srq_view *v, double el_top, double el_bottom,
                double *out);
int  srq_smooth(const srq_req *r, int root_smooth);
```

## 5. Tabla de errores

| Condición | Resultado |
| :-- | :-- |
| `srq_decode`: NULL | -1, `*out` = `SRQ_NONE` si no es NULL |
| tipo/behavior/block fuera de enum, `|y|` o margen > `SRQ_MAX_COORD` | -1 |
| `n > max_handles`, `nsub > n`, `n != 0` sin `SRQ_ELEMENT`, `SRQ_ELEMENT` con `n == 0` | -1 |
| `srq_target`: NULL, `SRQ_NONE`, algún valor no finito, `view_h ≤ 0`, `max < 0` | -1, `*out` sin tocar |
| `srq_encode`: NULL | no escribe; NaN ⇒ 0; fuera de rango ⇒ acotado |

## 6. Garantías

- El worker no lee el scroll real ni recibe confirmación: pedir un desplazamiento no le da al
  contenido ninguna lectura nueva (anti-fingerprinting intacto; `scrollY` real sigue siendo solo
  allow∩js por `js_geom`).
- El padre nunca confía en el registro: rango validado y handles solo usados como clave en SU tabla
  de geometría (un handle inventado no se encuentra ⇒ no se desplaza).
- `srq_target` es total sobre doubles finitos y su resultado está siempre en `[0, max_scroll]`
  (fuzz `fuzz-srq`).

## 7. Dado-Cuando-Entonces

- **Dado** una página de 5000 px, **cuando** un clic ejecuta `scrollTo(0, 2000)`, **entonces** el
  scroll queda en 2000; con `scrollBy(0, -500)` después, en 1500.
- **Dado** `<h2 id=t>` a 3000 px, **cuando** `t.scrollIntoView({block:'center'})`, **entonces** el
  centro del `<h2>` queda en el centro del viewport.
- **Dado** `html{scroll-padding-top:80px}` y una cabecera fija de 80 px, **cuando** se sigue
  `#t`, **entonces** el `<h2>` queda 80 px por debajo del tope (visible bajo la cabecera).
- **Dado** `h2{scroll-margin-top:1rem}`, **entonces** el ancla deja 16 px por encima del `<h2>`.
- **Dado** `scrollTo({top: 1e308})`, **entonces** el scroll queda en el máximo (acotado), nunca
  infinito ni negativo.

## 8. Fuera de alcance (abierto)

Contenedores internos `overflow:auto|scroll` (el motor no desplaza cajas internas), eje
horizontal, `scroll-snap-*`, `scrollend`, `scrollIntoViewIfNeeded`.
