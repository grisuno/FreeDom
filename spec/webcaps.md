# webcaps — modelo de capacidades unificado por página (M0.1)

> Módulo puro, sin I/O ni estado global. Deriva, de las señales de confianza de un
> host, la tabla **completa** de capacidades de una página. Fail-closed.

## Motivación

Hoy la decisión de "qué puede hacer esta página" está repartida:

- `rdp_caps` (`include/render_policy.h`) lleva 3 bools: `images`, `css`, `js`.
- La red es un flag aparte del `tab` (`tab_set_net_allowed`), no una cap.
- Las cookies de sesión se siembran ad-hoc según `trusted`.
- La derivación (`trusted`, `present_trusted`, `css_grant`, `js_grant`, la copia
  `eff`) se recalcula **inline** en cada sitio de carga de `gui/browser_ui.c`
  (`render_current_ex`, `freebug_repl_worker`) y en headless (`src/freedom.c`).

La modernización (roadmap `~/.claude/plans/...`) añade capacidades nuevas
(persistencia/IndexedDB, readback des-envenenado, WebGL, Service Workers, WebRTC).
Sumarlas como flags sueltos multiplicaría la lógica repartida y el riesgo de que un
sitio de carga quede desincronizado con otro. `webcaps` es el **único** lugar puro
que decide, para que cada milestone posterior solo **consuma** un campo.

Este módulo **no cambia el comportamiento** de las capacidades existentes
(`js`/`css`/`images`/`net`/`cookies`): reproduce exactamente la derivación actual.
Los campos nuevos (`persist`/`readback`/`gpu`/`sw`/`rtc`) se **derivan** ya, pero
ningún consumidor los lee todavía (los cablean los milestones de Fase 3/4).

## Doctrina de gating (decisión del owner, 2026-07-15)

- **Leak-free ⇒ global.** `js` (ejecución), `css` (presentación de autor) e `images`
  no exponen huella ni red nuevas más allá de lo que ya hoy; se conceden por la
  ruta actual (toggle del usuario **o** presentation-trust de `allow.conf`).
- **Privacy-sensitive ⇒ `allow.conf ∩ js.conf` (doble consentimiento).** `net`
  (XHR/fetch + script externo), `cookies`, `persist`, `readback`, `gpu`, `sw`, `rtc`
  exigen que el host esté en **ambas** listas (el predicado `jsp_trusted`).
- El worker de contenido hostil mantiene TODOS sus invariantes estructurales
  (seccomp W^X, sin socket, sin GPU): "trusted" abre **qué capacidad se instala**,
  nunca **quién toca el socket** — el padre sigue re-aplicando toda la política.

## Entradas / salidas

`wc_caps` (todos `bool`; el valor cero `{0}` es la línea base segura = todo off):

| Campo      | Significado                                             | Gate |
| :--------- | :----------------------------------------------------- | :--- |
| `js`       | ejecutar JavaScript de la página                        | leak-free |
| `css`      | aplicar CSS de autor + fetch de `<link rel=stylesheet>` | leak-free |
| `images`   | cargar/renderizar imágenes                              | leak-free |
| `net`      | XHR/fetch reales + `<script src>` externo (gateado padre)| trusted |
| `cookies`  | sembrar/foldback de cookies de sesión efímeras          | trusted |
| `persist`  | storage/IndexedDB/cookies a disco (Fase 3)              | trusted |
| `readback` | canvas/audio readback des-envenenado (Fase 3)          | trusted |
| `gpu`      | WebGL vía helper GPU aislado (Fase 4)                   | trusted |
| `sw`       | Service Workers (Fase 4)                                | trusted |
| `rtc`      | WebRTC / getUserMedia (Fase 4)                          | trusted |

### `wc_derive(wc_input in)` — ruta GUI por host (Dado-Cuando-Entonces)

`wc_input`: `{ jsp_mode js_mode; int host_in_js; int host_in_allow; int reader;
int user_css; int user_images; }` — `host_in_js`/`host_in_allow` son la pertenencia
a `js.conf`/`allow.conf` (vía `hb_is_allowlisted`, cubre subdominios); `user_css`/
`user_images` son los toggles de sesión del usuario.

Reutiliza los predicados de `js_policy` (NO reimplementa membership):
`js_enabled = jsp_enabled(js_mode, host_in_js)`,
`present = jsp_present_trusted(host_in_allow)` (= `host_in_allow != 0`),
`trusted = jsp_trusted(js_enabled, host_in_allow)` (= `js_enabled && host_in_allow`).

- **Dado** un host, **Cuando** se deriva, **Entonces**:
  - `js = js_enabled`
  - `css = (user_css || present) && !reader`
  - `images = (user_images || present) && !reader`
  - `net = cookies = persist = readback = gpu = sw = rtc = trusted`
- **Dado** `reader` on, **Entonces** `css` e `images` son `false` (el modo lectura
  gana, como hoy), sin tocar los toggles persistentes del usuario.
- **Dado** un modo global `JSP_ON` pero el host **no** en `allow.conf`, **Entonces**
  `js = true` pero `net`/privacy-caps `false` (JSP_ON no es confianza).
- Fail-closed: un `js_mode` fuera de rango ⇒ `js_enabled=false` (vía `jsp_enabled`).

### `wc_from_flags(bool js, bool css, bool images)` — ruta headless/operador

Headless no gatea por host: el operador declara la confianza con los flags de CLI
(`--js=on`/`--author-css`/`--images`), ortogonales entre sí. Reproduce exactamente
la política headless actual:

- `js = js`, `css = css`, `images = images`.
- `net = cookies = persist = readback = gpu = sw = rtc = js` (`--js=on` es la señal
  de confianza del operador para red/persistencia).
- No hay `present`/`reader` (headless no tiene modo lectura ni `allow.conf`-para-caps).

### `wc_render_caps(wc_caps c)` — proyección a `rdp_caps`

Devuelve `{ images: c.images, css: c.css, js: c.js }` para alimentar `rd_build`
sin cambiarle la firma. (`rd_build` ignora `caps.js`; se proyecta igual por
completitud y estabilidad futura.)

### `wc_safe(void)`

Todas las capacidades en `false` (línea base). Idéntico a `(wc_caps){0}`.

## Fuera de alcance

- Membership de hosts (la resuelve `hostblock`).
- I/O, red, persistencia: `webcaps` solo **decide**; los orquestadores cablean.
- Gating fino adicional por-capacidad (p. ej. una `webgl.conf` que estreche `gpu`
  como `impersonate.conf` estrecha el TLS): lo añadirá el milestone de esa
  capacidad extendiendo `wc_input`; hoy `gpu`/`sw`/`rtc` son el grant base `trusted`.

## Seguridad / testing

No parsea contenido remoto (la entrada es un puñado de enteros/enum), así que **no
requiere fuzz target** — igual que `js_policy`. Se candela con CMocka
(`tests/test_webcaps.c`): la matriz de derivación, el gate doble para privacy-caps,
`reader` gana, `JSP_ON`-sin-allowlist no es confianza, la proyección a `rdp_caps` y
la equivalencia con la ruta headless por flags.
