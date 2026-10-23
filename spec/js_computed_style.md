# getComputedStyle real (allow∩js)

## Contrato

Dado un host de confianza (allow.conf ∩ js.conf) con JS activo,
Cuando la página (o el REPL de Freebug) llama `getComputedStyle(el)`,
Entonces el valor de cada propiedad sale de la **cascada real** (hojas de la página,
`<style>`, externas, herencia, `!important`, capas), no del atributo `style`.

Para cualquier otro host el objeto sigue devolviendo solo el `style` en línea
(identidad anti-fingerprinting: no se filtran estilos de la maqueta).

## Módulos

| Módulo | Rol |
| :-- | :-- |
| `css_computed` (`ccm_`) | Puro. `css_style` ya resuelto -> texto CSS de una propiedad (`rgb()`, `Npx`, keywords). Sin I/O. |
| `dom_native` / `dom_generation` | Puente de handle JS -> nodo nativo y contador de mutaciones. |
| `pv_computed` (en `page_view`) | Retiene la hoja y la cascada; `pv_computed_get(el)` resuelve un elemento con herencia. |
| `tab.c` | Posee el `pv_computed` del worker; lo reconstruye si `dom_generation` cambió; lo expone a `js_dom` por un callback. |

## Formato (como Firefox)

- Color: `rgb(r, g, b)`; con alfa < 1: `rgba(r, g, b, a)`. Sin fondo: `rgba(0, 0, 0, 0)`.
- Longitudes: `Npx`. `font-size` es el computado (px). `width`/`height` declarados en px o `auto`.
- `line-height`: `normal` o px. `font-weight`: `400`/`700`. `opacity`: `1`, `0.5`.
- No declarado: el valor inicial de la propiedad (`display:inline`, `position:static`, ...).
- `color` e herencia: el valor del ancestro más cercano que lo declara; inicial `rgb(0, 0, 0)`.
- Propiedad desconocida: cadena vacía (nunca se inventa un valor).

## Garantías

- Fail-closed: sin hoja, sin handle válido o sin permiso -> `''`.
- Acotado: salida <= `CCM_VALUE_MAX`; la reconstrucción de la hoja ocurre a lo sumo una vez
  por generación del DOM.
- El worker no ve más que su documento; no hay red ni E/S nueva.

## Fuera de alcance

Valores *usados* de layout (`width:auto` -> px medidos; eso sigue siendo `getBoundingClientRect`),
pseudo-elementos (`getComputedStyle(el, '::before')`), transiciones en curso.
