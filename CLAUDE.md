# Freedom — Navegador Seguro por Defecto

> **Misión:** un navegador web construido desde cero en **C puro**, diseñado como respuesta
> directa a la vigilancia corporativa (modelos tipo Brave–Palantir). Cero telemetría, cero
> backdoors, cero confianza implícita. Lo que no se puede auditar, no entra.

Este archivo es el contrato de trabajo para cualquier agente (humano o IA) que toque este
repositorio. **Estas reglas anulan comportamientos por defecto.**

---

## 1. Los seis principios inquebrantables

1. **Zero Trust** — Ningún componente confía en otro. El renderizador no confía en la red; el
   motor JS no confía en el DOM; nada confía en el contenido remoto. Aislamiento por límites
   estrictos de memoria y, donde el SO lo permita, `seccomp-bpf` (Linux), `landlock`,
   `pledge`/`unveil` (OpenBSD).
2. **Zero Knowledge** — El navegador no sabe del usuario más de lo estrictamente necesario para
   renderizar. Sin historial en claro, sin fingerprinting pasivo, sin fugas de IP (WebRTC
   deshabilitado por defecto).
3. **Privacy by Default** — Bloqueo total de terceros a nivel del motor de red. Sin telemetría
   ni siquiera "anónima" u "opt-out". Integración opcional con Tor/I2P a nivel de socket.
4. **Secure by Default** — La configuración insegura **no debe ser representable** en la API.
   El camino por defecto es siempre el seguro. Fallar cerrado: si una garantía no se puede
   verificar, se rechaza la operación.
5. **Post-Quantum by Default** — TLS 1.3 mínimo. Intercambio de claves **híbrido** (clásico +
   ML-KEM) para neutralizar *Harvest-Now, Decrypt-Later*. Nunca PQ puro (si ML-KEM cae, el
   componente clásico debe resistir); nunca clásico puro.
6. **Agent-Safe & Agent-Friendly** — Seguro para el usuario **y** para el agente de IA que lo
   opere, en ambas direcciones: el contenido remoto es hostil también para el agente (inyección
   de prompts), así que se le entrega siempre como **dato con procedencia, nunca como
   instrucción**, y sin acción implícita; y el navegador es manejable por un agente (salidas
   deterministas, con códigos de estado, sin estado oculto, *headless*). El agente opera dentro
   de los mismos sandboxes que el usuario. Contrato completo en `spec/agent-safety.md`.

**Doctrina anti-vigilancia:** no se permite ninguna cadena de texto, dependencia, endpoint ni
comentario que apunte a servicios de terceros no esenciales. Cada dependencia se justifica por
reducción de superficie de ataque, no por conveniencia.

---

## 2. Restricciones de lenguaje y estilo

- **Solo C puro (C11).** Nada de C++, Rust ni dependencias ocultas. El header rechaza C++ con
  `#error`.
- **Identificadores y strings en inglés.** La documentación (`spec/`, este archivo) puede estar
  en español; el código, no.
- Sin emojis en el código. Comentarios solo cuando explican un *porqué* no evidente. Los headers
  llevan documentación de contrato.
- Nombres con prefijo de módulo (`sf_` para `secure_fetch`, etc.). Sin estado global mutable;
  todo reentrante. Cada asignación tiene un único dueño y un único liberador idempotente.

---

## 3. Metodología: SDD + TDD estricto + BDD Given-When-Then

Para cada módulo el ciclo es inviolable y **en este orden**:

1. **Spec** — `spec/<modulo>.md`: entradas, salidas, tabla de errores, garantías de seguridad y
   qué queda fuera de alcance, en Dado-Cuando-Entonces.
2. **Test (rojo)** — `tests/test_<modulo>.c` con CMocka (ATDD). Debe **fallar de verdad**:
   verificá el rojo revirtiendo el fix, no lo supongas. Un build que falla por `-Werror` deja el
   binario viejo en su sitio y el test "pasa" — eso no es rojo, es un experimento inválido.
3. **Code (verde)** — `src/<modulo>.c`, el código mínimo para pasar. La I/O del **lado confiable**
   (orquestador / event loop, el que NO toca contenido hostil) debe ser **asíncrona** (`io_uring`
   cuando aplique). **Excepción inquebrantable:** `io_uring` está **PROHIBIDO dentro del worker
   confinado** (`tab`/`renderer`): es una **primitiva de bypass de seccomp** (sus `IORING_OP_*` no
   atraviesan el syscall entry que filtra el BPF → anularía allowlist, W^X y netns). El worker hace
   I/O **bloqueante** sobre sus dos pipes. `spec/os_sandbox.md` §13,
   `[[freedom-io-uring-forbidden-in-worker]]`.
4. **Refactor** — endurecer punteros y límites. **Modo boy scout, nunca fuera de scope:** código
   duplicado se unifica; deuda técnica y vulnerabilidades se extinguen sin perder funcionalidad;
   si algo se hace en 10 líneas en vez de 40 respetando DRY/SOLID, se hace.
   **Cláusula anti-monolito:** ningún archivo se vuelve monolito. Al rozar las **~2000 líneas** se
   **parte según contratos** (módulo = `spec/` + `include/` + `src/`). Si tu cambio empujaría un
   archivo más allá del umbral, **primero extraé**: en un archivo que ya lo excede, la lógica nueva
   (sobre todo la pura) va a un módulo nuevo, no a engordarlo.
5. **Validación** — `make asan` (ASan+UBSan) limpio, `valgrind`, `cppcheck`, **más revisión visual
   del render**. La GUI necesita Wayland (no siempre disponible), así que se inspecciona headless:
   `./build/freedom --download-png=$SP/frame.png <URL-o-archivo.html>` y `Read` de la imagen.
   Procedimiento completo, flags (`--author-css`, `--images`, `--js=on`) y checklist en la skill
   **`/visual-review`** (`.claude/skills/visual-review/SKILL.md`) y en
   `[[freedom-visual-review-headless]]`. Preferí **PNG sobre PDF**: una sola imagen, un paso,
   muchos menos tokens.
   **Freebug** (la consola devtools) es una ventana Wayland aparte y **no** sale en el PNG: todo
   cambio que la toque se verifica en pantalla con el flujo Xvfb+weston descrito en
   `[[freedom-gui-visual-verification-weston]]`, con validación cruzada por `--dump-console`.
6. **Fuzzing** — todo path que toca contenido remoto se fuzzea (`make fuzz`/`fuzz-pv`/`fuzz-js`/
   `fuzz-img`/`fuzz-dom`/`fuzz-svg`/`fuzz-css`/`fuzz-jsdom`/`fuzz-geom`/`fuzz-wst`/`fuzz-imap`; AFL++ con `make fuzz-afl`). Cero crashes/leaks/UB
   antes de cerrar.
7. **Documentación** — **recién después de validar y fuzzear**: spec, este `CLAUDE.md`, la memoria,
   `docs/index.html` (el "home page": atajos, features) y `README.md`. Documentar antes de validar
   es documentar lo que todavía no es verdad.

**No escribas la implementación antes que la spec y el test.** No avances de hito sin que el
anterior esté verde, validado y fuzzeado.

**Diseño orientado a prueba:** la lógica de seguridad va en **funciones puras sin I/O**; los
orquestadores con red/SO solo cablean y llaman a esas funciones puras sobre el estado real.

---

## 4. Stack tecnológico (decisiones vigentes)

| Módulo | Biblioteca | Nota |
| :-- | :-- | :-- |
| Red & TLS | `libcurl` + **OpenSSL 3.5+ nativo** | **No usar `liboqs`/`oqsprovider`.** OpenSSL 3.5+ trae `X25519MLKEM768`, `ML-DSA`, `SLH-DSA` en el provider `default`. Una dependencia menos que auditar. |
| Parser HTML/CSS | `Lexbor` | C puro, superficie mínima. Sin ejecución de scripts inline por defecto. |
| Motor JS | `QuickJS-ng` (vendorizado) | C puro, sandboxed. Bridge C que expone **solo** APIs validadas. Sin XHR a terceros, sin WebRTC, sin WebGL, sin FS. |
| UI/Gráficos | `Cairo` + **Wayland** (nunca X11) | X11 permite keylogging entre ventanas. |
| Shaping de texto | **HarfBuzz** + FreeType + fontconfig | Lado confiable, **fuentes locales**, nunca en el worker ni en la red. `[[freedom-harfbuzz-shaping]]`. |
| Vídeo/Audio | FFmpeg | En proceso decoder aislado (`OS_PROFILE_MEDIA_DECODER`). |
| Pruebas | `CMocka` | `sudo apt install libcmocka-dev`. |
| Memoria | asignador endurecido / `mimalloc` | Mitigar UAF y overflows. |

> Verificación PQC en este host: `openssl list -tls-groups | grep -i mlkem` debe mostrar
> `X25519MLKEM768`.

### Política criptográfica concreta

- **KEM por defecto:** `X25519MLKEM768` (híbrido). **Firmas:** `ML-DSA-65`; alternativa `SLH-DSA`.
- **Rechazos por defecto:** TLS < 1.3, KE no híbrido, **leaf con RSA < 3072**, y cualquier cert de
  la cadena firmado con SHA-1. El umbral RSA aplica **solo al leaf** (RSA-2048 es universal en los
  intermedios de la Web PKI pública); SHA-1 es fatal en cualquier posición. `spec/secure_fetch.md` §3.
- **Soberanía del usuario:** un host **explícitamente** en `allow.conf` se navega bajo
  `SF_POLICY_ALLOWLISTED_INSECURE` si el intento estricto falla (TLS 1.2 mínimo, KE clásico, cert
  débil-pero-válido). Se relaja la **fuerza** criptográfica, **nunca la autenticidad**
  (VERIFYPEER intacto): llegás al sitio real sobre cripto vieja, no a un impostor. Opt-in, por
  host, con toast.
- **Niveles:** `SF_POLICY_PQ_HYBRID_KE` (defecto), `SF_POLICY_STRICT_PQ` (opt-in, exige firma PQ),
  `SF_POLICY_ALLOW_CLASSICAL_KE` (fallback) y `SF_POLICY_ALLOWLISTED_INSECURE` (override por host).
- **Estado local (Zero Knowledge):** caché/marcadores/credenciales con AES-256-GCM o
  ChaCha20-Poly1305; clave derivada con **Argon2id** y sal única por dispositivo.

---

## 5. Compilación, hardening y auditoría

`make` aplica por defecto:

```
-std=c11 -Wall -Wextra -Werror -Wshadow -Wpointer-arith -Wvla -Wwrite-strings
-fstack-protector-strong -fstack-clash-protection -fcf-protection=full
-D_FORTIFY_SOURCE=3 -fPIE -fvisibility=hidden -O2
-pie -Wl,-z,relro,-z,now,-z,noexecstack
```

Targets: `make` (compila `src/`), `make test` (suite CMocka), `make asan` (ASan+UBSan),
`make fuzz*` (libFuzzer / AFL++), `make clean`, `make deps`, `make run [URL=...]`, `make deb`,
`make docker`.

**El Makefile es la única fuente de verdad de los comandos.** Los `*.sh` son wrappers delgados que
delegan a un target (`fuzz.sh`→`fuzz-afl`, `build_deb.sh`→`deb`, `docker_run.sh`→`docker`,
`run_freedom.sh`→`run`). Una fuente nueva se parametriza en el Makefile y todos los targets la
toman solos. Todo PR pasa `make test` y `make asan` limpios.

---

## 6. Estructura del repositorio

```
freedom/
├── CLAUDE.md              # este archivo
├── Makefile               # build endurecido + targets test/asan/fuzz
├── include/<modulo>.h     # contratos públicos
├── src/<modulo>.c         # implementaciones
├── gui/                   # orquestador Wayland+Cairo (browser_ui.c, bui_theme.c, svg_paint.c)
├── spec/<modulo>.md       # especificaciones SDD
└── tests/test_<modulo>.c  # suites CMocka (TDD)
```

---

## 7. Estado y hoja de ruta

### 7.1 Núcleo cerrado — de la red a la pantalla

Todos con suites CMocka + ASan/UBSan limpio (66 suites, 21 targets de fuzzing).

| Capa | Módulo(s) | Garantía clave |
| :-- | :-- | :-- |
| Red/TLS | `secure_fetch` (`sf_`), `tls_impersonate` (`ti_`) | TLS 1.3 mínimo, KE híbrido PQ preferido; cada redirección re-aplica TODA la política. Impersonación JA3/JA4 por triple opt-in. |
| URL/enlaces | `url` (`url_`), `link_nav` (`ln_`) | RFC 3986; downgrade a http / esquemas ajenos no representables. |
| Política de red | `request_policy` (`rp_`), `render_policy` (`rdp_`), `webcaps` (`wc_`) | Bloqueo de terceros por defecto, https-only, gate de imágenes/CSS/JS (todo opt-in). |
| Filtro de hosts | `hostblock` (`hb_`), `js_policy` (`jsp_`) | Lista negra + blanca formato `/etc/hosts`; la blanca gana y cubre subdominios. Puros, fallan abierto. |
| Enrutado | `net_realm` (`nr_`) | clearnet / `.onion` / `.i2p` → directo / Tor SOCKS5h / I2P HTTP / **bloqueado**. Puro, fail-closed. |
| Parser | `html_parse` (`hp_`), `dom` (`dom_`) | DOM inerte con Lexbor, strip de `<script>`/`on*`; índice de solo lectura con handles enteros. |
| JS/anti-FP | `js_sandbox`/`js_dom`/`js_env`, `anti_fp` | QuickJS-ng sin I/O; bindings sellados; relojes/pantalla normalizados; readback de canvas/audio envenenado **por origen**. |
| Aislamiento | `os_sandbox` (`os_`), `tab` (`tab_`) | fork+exec + seccomp-bpf fail-closed con **W^X** + anti-volcado + Landlock + `unshare` user/net/ipc/uts. El worker NO toca red. |
| Estado cifrado | `local_store`, `disk_store`, `prefs`, `profile` | AEAD + Argon2id; escritura atómica 0600. AUTH-fail ⇒ defaults sin clobber. |
| Render | `page_view` (`pv_`), `render_doc` (`rd_`), `box_tree` (`bt_`), `flex_layout` (`fx_`), `block_flow` (`bf_`), `compositor` (`cx_`) | DOM → display list → cajas (block/flex/grid) → stacking context (7 capas CSS 2.1 App E). Posicionamiento, z-index, opacity, blend, transform matricial, clipping, float, **colapso de márgenes verticales** (`block_flow`, CSS 2.1 §8.3.1) y **colocación de grilla por nombre** (`grid-template-areas`, `spec/grid_areas.md`). |
| CSS | `css` (`css_`), `css_length` (`cl_`), `css_select` (`csel_`), `css_color` (`cc_`), `interp` | Parser + cascada pura. Selectores (tipo/clase/id/grupos, 4 combinadores, atributos, pseudo-clases, `::before`/`::after`), `!important`, `@media`, `@keyframes`, custom properties + `var()`, `calc()`/`min()`/`max()`/`clamp()`, flex/grid, gradientes, sombras, filtros, transform, **todas** las unidades de `<length>` de CSS Values 4 por un ÚNICO resolvedor (`css_length`: px/pt/pc/cm/mm/Q/in, em/rem/ex/ch/cap/ic/lh/rlh, vw/vh/vi/vb/vmin/vmax + variantes s/l/d). **Fail-closed:** `url()` de `@import`/`@font-face` descartados, topes anti-DoS, fuzzeado. Inventario completo en `spec/css.md`. |
| Imágenes | `image_decode` (`img_`), `data_url` (`du_`) | PNG + JPEG + WebP + GIF estático **dentro del worker confinado**; topes anti-DoS; ARGB listo para Cairo. GIF con decoder LZW propio. |
| Vídeo/Audio | `media_decoder` (`md_`), `hls` | H.264/H.265 desde MPEG-TS o HLS en proceso aislado; reproducción a ritmo de PTS (`md_pacer` puro). |
| Formularios | `form` (`fm_`), `textfield` | GET/POST nativos sin JS; target no-https no representable. |
| Shaping | `text_shape` (`tsh_`) | HarfBuzz + FreeType. Ligaduras, kerning GPOS, formas contextuales. Solo lado confiable, fuzzeado. |
| Export | `pdf_export` (`pe_`), `zoom` (`zm_`), `download` (`dl_`) | PDF vectorial; zoom 50–300 %; descargas con nombre fail-closed y escritura atómica 0600. |
| Prefetch | `prefetch` (`pf_`) | Pre-scanner puro + pool de 6 hilos por el MISMO fetcher gateado; sigue el grafo de módulos ES (imports estáticos + import map). |
| DevTools | `freebug` (`fb_`), `dom_debug` (`dd_`) | Consola JS (`F12`, `--dump-console`) con nivel y `file:line:col`; `--dump-dom`/`--dump-layout`/`--dump-css`. |
| UI | `ui`/`browser` (puros) + `gui/browser_ui.c` (orquestador) | Toolbar, tabs, omnibox, scroll, menú, multi-pestaña, atajos, temas. |
| SVG | `svg_render` (`sv_`), `svg_paint` (`svp_`) | `<svg>` en línea: parser puro y fuzzeado + pintor Cairo. La gramática **no tiene forma de URL** ⇒ cero red. |
| Auditoría | `spec/threat-model.md` | Activos/adversarios/fronteras → mitigaciones. |

### 7.2 Doctrina vigente (no re-litigar)

Cada línea es la decisión + su porqué; el detalle vive en `spec/`, en `git log` y en la memoria.

**Red, TLS y soberanía**
- Navegabilidad sobre PQ estricto: un host sin KE híbrido **avisa** (toast), no bloquea. `[[freedom-navigability-over-strict-pq]]`
- La allowlist es el override de soberanía, no una dictadura: relaja **fuerza**, nunca **autenticidad**. Caso real: Hacker News. `[[freedom-navigability-over-strict-pq]]`
- El umbral RSA<3072 aplica **solo al leaf**; un leaf RSA-2048 se sortea con **Ctrl+Shift+E** (solo sesión).
- Identidad de red = identidad anti-fingerprinting: el `User-Agent` por cable **es** `FP_USER_AGENT` y coincide con `navigator.userAgent`. `[[freedom-anti-fp-network-identity]]`
- Tor/I2P a nivel de socket, nunca embebido. `.onion` https-only; `.i2p` acepta `http://` (el overlay ya cifra). Fail-closed. `[[freedom-tor-i2p-integration]]`
- Filtro de hosts opcional con override; falla **abierto**. La blanca gana y tiene doble rol (des-bloquea del adblock **y** habilita el override TLS).
- Impersonación TLS por triple opt-in (`allow` ∩ `js` ∩ `impersonate`). NO derriba reCAPTCHA/BotGuard. `[[freedom-tls-impersonate]]`

**Aislamiento y superficie JS**
- `io_uring` PROHIBIDO en el worker (bypass de seccomp). `[[freedom-io-uring-forbidden-in-worker]]`
- SOP por construcción: sin API de red, sin `iframe`/`window.open`/`postMessage`/`opener`. Por eso **no se implementa CORS** (sería código muerto). `[[freedom-sop-by-construction]]` **Enmienda 2026-09-30 (dueño):** vale para todo host **no** confiable; un host allow∩js recibe `window.open` con semántica *noopener* (devuelve `null`: sigue sin haber referencia ni canal entre ventanas) y solo en un gesto del usuario. `opener`/`postMessage`/iframes vivos siguen ausentes hasta su propio hito (broker del padre).
- **Enmienda 2026-10-26 (dueño): allow∩js recibe TODO, terceros incluidos.** Una página cuyo host está en `allow.conf` Y `js.conf` carga JS, CSS, fuentes, XHR y WebSocket de cualquier host: `hb_check_subresource(…, page_trusted)` pasa por encima de la lista negra (los demás hosts la conservan). Se mantiene lo que no es política de permisos sino el sandbox: el worker no toca sockets, VERIFYPEER, realm. **iframes vivos y `postMessage` cross-window** para esas páginas: cada iframe es su PROPIO worker confinado y el padre media (`frame_broker` puro + `frame_host`; JS por JSON como dato, origen del emisor fijado por el padre). El frame no se pinta aún (hidden: reCAPTCHA v3/BotGuard). `spec/frame_broker.md`. `[[freedom-trusted-everything-iframes-tanda73-2026-10-26]]`
- **El worker nunca toca un socket, tampoco para WebSocket:** el objeto `WebSocket` (solo allow∩js) registra operaciones; el padre abre con `sf_ws_open`, que comparte `sf_setup_handle` con `sf_perform` (UNA configuración de TLS/PQ/realm/identidad) y aplica `sf_enforce_policy` al socket ya actualizado. `ws_hub` los sostiene (apertura en hilo, `socketpair`+`MSG_NOSIGNAL`, token por apertura contra cierres reentrantes). `spec/ws_hub.md`.
- **`localStorage` de un host de confianza vive en RAM del padre, por origen** (`web_storage`, cuota 5 MiB, LRU de 256 orígenes), nunca en disco (decisión del dueño). El worker devuelve la instantánea completa cuando cambió y el padre la valida entera (`wst_decode_check`, fuzzeado) antes de tocar la base. `spec/web_storage.md`.
- **La allowlist relaja FUERZA, nunca AUTENTICIDAD — también en el código:** ningún override pone `cfg.insecure` (solo el flag explícito de operador `--insecure`); `SF_POLICY_ALLOWLISTED_INSECURE` ya tolera TLS 1.2/KE clásico/leaf débil con VERIFYPEER y `sf_enforce_policy` activos. Un subrecurso pedido por una página allow∩js (CDN, módulos, WebSocket) recibe esa misma fuerza relajada; la carga de la página principal no.
- **Módulos por nivel de confianza:** con red (allow∩js) corren los `type=module` y se saltan los `nomodule`; sin red, los módulos externos se saltan y corre el `nomodule` del autor. Un especificador desnudo solo resuelve por `<script type=importmap>`.
- **`vw` = ancho de render (enmienda del dueño 2026-10-15):** `@media` ya ve el ancho real desde la tanda 12, así que `vw`/`vi`/`vmin`/`vmax` contra 1920 no ocultaban nada y rompían la geometría (sliders `calc(100vw*4)`, full-bleed). Se reescriben en el texto de la hoja (`len_rebase`, mismo choke point que `rem`) y en el `style` inline; `vh`/`vb` siguen en 1080. `spec/css.md`.
- **La geometría es identidad:** `getBoundingClientRect`/`offset*`/`client*`/`innerWidth` reales **solo** para allow∩js (`js_geom`, doble gate padre+worker); todo otro host ve ceros y el viewport normalizado. `spec/js_geom.md`.
- Excepción gateada allow∩js: XHR/`fetch` reales, pero **el JS nunca toca el socket** — el worker proxya al padre, que re-aplica TODA la política. `[[freedom-parent-gated-xhr]]`
- Readback de canvas/audio por origen (eTLD+1), no por sesión: cierra el cross-origin linking. `[[freedom-anti-fp-origin-readback-key]]`
- JS apagado salvo opt-in. Con JS activo los mutadores del DOM **DETACHAN** (`lxb_dom_node_remove`, nunca `destroy`): cero UAF. `location` real y de solo lectura; la navegación la gatea el padre con `ln_resolve`. Storage/cookies/referrer efímeros o vacíos. `[[freedom-live-js]]`
- **Un solo registro de listeners** para elementos, `document` y `window`, con captura → destino → burbuja (DOM §2.9) y camino calculado antes de despachar y acotado; los `jd_fire_*` de C pasan por él. Sin eso la delegación (React escucha en la raíz) quedaba sorda. `timeStamp` siempre 0 (anti-fp). `spec/js_dom.md` §7d.
- Cada `<script>` es su propio programa; un **único** presupuesto de reloj por página se reparte entre todos. `[[freedom-per-script-isolation]]`
- Doctrina trusted-host: allow∩js ⇒ CSS de autor e imágenes efectivos sin toggles. `JSP_ON` global **no** es confianza. `[[freedom-trusted-host-full-caps]]`
- Cookies de sesión EN MEMORIA para allow∩js; nunca a disco. `[[freedom-session-cookies-trusted-spa]]`

**Buscador y navegación**
- Omnibox (`url_omnibox`, puro): host desnudo ⇒ `https://`; esquema ajeno (`javascript:`/`file:`) ⇒ **búsqueda**, nunca ejecución. `[[freedom-omnibox-search]]`
- El buscador depende de la allowlist: DuckDuckGo presenta leaf RSA-2048. `[[freedom-search-needs-allowlist]]`
- SPA de buscador ⇒ endpoint no-JS por rewrite transparente en el único choke point. Google **no** se toca. `[[freedom-search-spa-noscript-rewrite]]`

**Render y presentación**
- **Una longitud relativa a la fuente es `a + b·font-size`, no un número.** `em`/`ex`/`ch`/`cap`/`ic`/`lh` se resolvían contra un **16 px clavado** porque la cascada es element-free, así que `width:10em` medía 160 px tanto en un elemento de 32 px como en uno de 8 (Firefox: 320 y 80). El valor viaja con su **derivada** (`cl_lp.em`, per-mille en `css_decl.emil`) y se dobla en UN solo sitio, `fold_font_relative`, cuando la cascada del elemento cierra y el `font-size` computado ya se conoce. El `font-size` heredado es un **input del motor** (`css_element.font_size`), como `state`. Inerte por construcción a 16 px. `[[freedom-font-relative-lengths-2026-08-13]]`
- **Una propiedad con prefijo de vendor ES la propiedad estándar:** se saca el prefijo y se vuelve a preguntar una vez; el despacho existente es la tabla de alias. La sintaxis tweener de IE10 (`-ms-flex-pack`) se descarta sola porque `flex-pack` no existe — y eso es correcto, su gramática de valores es otra. `[[freedom-font-relative-lengths-2026-08-13]]`
- **Toda unidad de `<length>` se resuelve en `css_length` y en ningún otro lado.** Una unidad nueva se agrega ahí y todos los consumidores la obtienen solos; una tabla de unidades privada en otro módulo es un bug, no una optimización. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **Un porcentaje es un VALOR del tipo `<length-percentage>`, no una propiedad de `width`.** Viaja simbólico (per-mille) desde la cascada hasta el layout y se resuelve en **un solo sitio**, `bx_lp_px`. La tabla de *basis* por propiedad es normativa (CSS 2.1 §8.3/§8.4/§9.3.2/§10.5, Transforms 1 §8), no una convención: margin y padding de **las cuatro caras** miden contra el ANCHO del bloque contenedor. Un canal ad-hoc por propiedad es un bug, no una optimización. `[[freedom-length-percentage-multicol-inline-replaced-2026-08-12]]`
- **Un emisor de `<length-percentage>` escribe SIEMPRE las dos mitades.** Escribir solo la que cambió deja un `width:50%` de baja especificidad combinándose con el `width:200px` que ganó la cascada. Mismo motivo por el que las mitades cruzan el códec IPC juntas.
- **Los pseudos dinámicos los gobierna el estado, no una constante:** `:hover`/`:active`/`:focus*` matchean si y solo si su bit está en `css_element.state`. Página recién cargada = `state` 0 = ninguno matchea, como cualquier navegador con el mouse afuera. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **Ninguna cadena que no venga del CSS/HTML/JS entra al flujo de la página.** Un diagnóstico del motor (imagen bloqueada, error de fetch) va a devtools; la página muestra lo que el autor escribió — para una imagen no disponible, su `alt` (HTML §4.8.4.4) y nada más. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **El espacio entre dos bloques son sus dos márgenes COLAPSADOS, y la regla es `max(0,positivos)+min(0,negativos)`, no `max(a,b)`** (CSS 2.1 §8.3.1, módulo puro `block_flow`). Un margen es espacio FUERA del border box, así que lo aplica la CAJA del elemento (una vez, donde la caja empieza), nunca el run de adentro; y un margen basta para que un elemento genere caja, o un wrapper sin decoración no tiene dónde vivir el suyo. `[[freedom-margin-collapse-heading-scale-grid-areas-2026-08-14]]`
- **Un `font-size` absoluto reemplaza la escala UA del encabezado solo si el autor lo declaró EN el encabezado.** En un ancestro es el valor heredado y `h1{font-size:2em}` sigue doblándolo — tratarlo al revés hacía que `body{font-size:16px}` pintara `h1`, `h2` y `p` al mismo tamaño. `[[freedom-margin-collapse-heading-scale-grid-areas-2026-08-14]]`
- **Un límite que una página normal alcanza no es una cota anti-DoS, es un bug de render.** El registro de cajas topeaba en 256 (y vivía en la pila): una portada real lo satura y el elemento pierde su caja en silencio. Cotas acopladas por `_Static_assert` cuando dos módulos indexan los mismos ids.
- **El contenido de `::before` es el primer contenido INLINE de su elemento** (CSS 2.1 §12.1), y tiene que viajar con el mismo `block_id`/indent/contenedor que su texto: si no, el pintor reconcilia cajas entre los dos runs y los separa igual.
- Privacy by Default: imágenes y CSS de autor **apagados**; opt-in (`Ctrl+I`, `FREEDOM_IMAGES=1`). Cubre remotas **y** locales por igual.
- **Layout != estilo de autor:** la maquetación (box model UA, flex/grid, márgenes, **tamaño de elementos reemplazados**) se aplica **siempre** — es estructura, no abre sockets. Solo los **colores** siguen tras `caps.css`.
- **El CSS externo es el gate, no el motor:** con `caps.css` OFF no se descarga ningún `<link>`, así que un layout basado en clases externas (Bootstrap de jkanime, `.social svg{width}` de slashdot) NO puede coincidir aunque el motor sea correcto. Antes de "arreglar" una diferencia, comprobá si es del motor o de una regla externa no aplicada: un `<svg>`/`<img>` sin tamaño declarado ocupa el ancho del contenedor **también en Firefox**. `[[freedom-replaced-css-sizing-and-flex-spacer]]`
- Origen `file://` para páginas locales, confinado al subárbol del documento. `[[freedom-local-file-origin]]`
- `display:none` es estructural, no una sugerencia. `[[freedom-display-none-structural]]`
- `preserved_view` gana solo con `>= 2` bloques de diferencia.
- **Una línea que no entra al lado de un flotante se BAJA, no se pinta encima** (CSS 2.1 §9.5). Acotar el ancho y dibujar igual pone el párrafo encima del pie de foto de una `<figure>` de ancho completo. **Y el score no lo detecta:** `make parity` premia la página más corta mientras el render empeora — por eso el paso de revisión visual del §3 no es opcional. `[[freedom-length-percentage-multicol-inline-replaced-2026-08-12]]`
- **`clear` es del ELEMENTO, no de cada run de su subárbol**, y un flotante nunca se limpia contra sí mismo (CSS 2.1 §9.5.2 habla de flotantes **anteriores**). Una exclusión de flotante se descarta al **salir** de su contexto, no al entrar en una caja anidada: un flotante acorta las líneas de todo descendiente del mismo BFC. `[[freedom-length-percentage-multicol-inline-replaced-2026-08-12]]`
- **Un renderizador de referencia que no corre bajo NUESTRAS reglas no mide el motor, mide la política.** `make parity` corre Firefox con `javascript.enabled=false` y sin red, porque Freedom renderiza con JS apagado y bloquea terceros por doctrina. Sin eso el `h_ratio` de wikipedia (1.64) era en su mayor parte el JS de MediaWiki plegando sus navboxes, y "arreglarlo" habría vuelto el motor incorrecto. Mismo error, invertido, en jkanime: se la había descartado como "no medible" por sus imágenes de CDN, y offline valen 282 px de ~7000. `[[freedom-parity-harness-and-parser-drops-2026-08-15]]`
- **El parser no descarta nada en silencio, y eso se MIDE:** `--dump-css-drops` reporta cada declaración perdida por `(propiedad, causa)`, separando "no implementada" de "implementada y el valor se rechazó". La segunda es la cara: la propiedad aparece en cualquier inventario por nombre y la declaración se pierde igual. `spec/css_drops.md`.
- **Una palabra clave CSS-wide RECLAMA su slot y no escribe.** `initial`/`inherit`/`unset`/`revert` valen en toda propiedad (Cascade 5 §7.3); dejar el campo sin poner es lo que les da significado, y reclamar el slot es lo que impide que una regla de MENOR especificidad lo escriba después. Se reconocen en los DOS puntos de paso compartidos, nunca en una tabla por propiedad. Mismo mecanismo para `width:auto`: el auto-dimensionado ES el comportamiento sin declarar de este motor.
- **`transparent` y `currentColor` son valores, no fallos.** Solo `-1` significa "no es un color"; todo test escrito `>= 0` los rechazaba (`color_ok`).
- **Un `calc()` es `a·1px + b·1em + c·1%`** y las tres componentes viajan simbólicas. `min/max/clamp` fallan cerrado ante un porcentaje: son lineales a trozos y `min(50%,600px)` daría ancho CERO, que es peor que descartar.
- **El rechazo de negativos es sobre el valor USADO, no sobre cada mitad** (CSS Values 4 §10.1: un `calc()` fuera de rango se acota al usarlo, no es inválido al parsearlo).
- **Una lista con coma toma su PRIMER item y un shorthand se expande a sus longhands.** El motor representa una sola animación/transición, así que `transition-delay: 0s, 0s` es `0s` y `animation: spin 2s infinite linear` llena name/duration/iters/timing (el timing no representable —`cubic-bezier()`— se ignora laxamente sin tumbar lo demás, precedente: `filter`). Lo que Firefox también tira NO se toca: `font` sin familia, `progid:`, `-webkit-gradient()`, `no-display`, typos y `padding` negativo son fail-closed compartido, no brechas.
- **Un conteo que necesita el layout viaja como marcador, no como adivinanza.** `repeat(auto-fill, minmax(min,1fr))` no se cuenta en la cascada (sin bloque contenedor): `grid_cols = −min_px` cruza el IPC como int existente y `layout_container` cuenta con el ancho real (`fx_autofill_count`, pura y testeada). Solo patrón de 1 track con mínimo px; multi-track/`fr`/`rows` fallan como antes. Misma idea en `background-position` (`right X` = pct 100% + px −X, pintor intacto) y en `translateZ(0)`/`rotateX(0deg)`, que emiten identidad porque en Firefox SÍ crean stacking context.
- **Un átomo inline comparte la línea y un % se resuelve una sola vez.** `<img><img>` consecutivos sin break forman UNA línea (el abridor acepta al siguiente reemplazado, no solo texto); `width:%` viaja en `box_w_pct` y se combina en `image_display_size`, y el pintor blitea el tamaño ya resuelto del frag (`blit_image_box`) en vez de re-resolverlo contra ese tamaño (lo componía dos veces: 50 % de 950 daba 237). Roto mid-line: la línea abierta flushea primero (orden, no solape).
- **Un nombre de familia cruza como hash, y un rewind restaura TODO.** `font-family` emite su primer nombre junto al bucket; la cascada lo matchea contra `@font-face` y guarda `wf_name_hash` (0 = ninguna) que viaja run→doc→IPC (`b[57]`) hasta el registro de caras del pintor. Y el retry de `add_rule` snapshottea counts de buckets + cursores de pools, no solo `n`/`total`: restaurar a medias sobre-contaba exactamente los buckets viejos (transition 5→6 con total intacto).
- **El padre observa, no intercepta: el sink ve cada CSS servido y el wire no cambia.** El pase `@font-face` corre en el padre tras el load (externas vía `tab_set_css_sink` en el único punto de servicio —un wrapper del fetcher perdería lo servido desde el pool—, inline vía el HTML retenido), solo en trusted, con clear del registro solo al cambiar de documento; `page_url NULL` carga solo `data:`. La familia se registra en el worker aunque el src no quepa en el cap (el pintor matchea por hash, el padre re-escanea los bytes). Y un E2E que envuelve líneas mide el canvas, no la fuente: una sola línea por banda o el assert es imposible por construcción.
- **Un campo que responde DOS preguntas distintas termina rompiendo una.** `block_id` dice a qué caja pertenece un run (gobierna la reconciliación); la caja PROPIA de un reemplazado es otra pregunta y viaja en `own_box_id`. Sobrecargar el primero hizo que en slashdot los titulares se solaparan con el cuerpo.
- **Un contenedor pregunta por SU caja, no por el sello del run.** El sello por-run responde por el contenedor más interno, que es el primer ÍTEM del externo: un `.row` flex recibía como bloque contenedor la caja de su propia tarjeta.
- **La paridad con Firefox se MIDE, no se supone:** `make geom PAGE=x.html [SEL=...]` imprime la geometría de LOS DOS motores lado a lado (Firefox como texto, vía un probe de `getBoundingClientRect` sobre una COPIA de la página) — aislar el caso en una sonda chica, medir los dos, y recién entonces tocar código. `make parity` dice cuánto difiere una página; `make geom` dice qué caja se movió. `[[freedom-firefox-parity-batch]]`, `[[freedom-firefox-parity-2026-07-30]]`
- SVG en línea se renderiza SIEMPRE: su gramática no tiene forma de URL. `[[freedom-inline-svg]]`
- Cajas vacías y decoración de ítems flex/grid pintan como en Firefox. `[[freedom-empty-and-item-boxes]]`
- Custom properties con recolección scoped (respeta el gate de `@media`). `[[freedom-scoped-custom-props]]`
- Tablas flow: la fila es UNA línea y la decoración cero no es caja. `[[freedom-flow-table-row-line]]`
- El SUBÁRBOL out-of-flow sale del flujo, **fail-open** a -1 para que nunca desaparezca contenido. `[[freedom-oof-subtree-stage2d]]`
- Prefetch paralelo del lado confiable: un hit cambia **cuándo** se buscó, jamás **qué**. `[[freedom-prefetch-parallel-pool]]`

**Invariantes de build y de proceso**
- **Un campo nuevo que no cruza el códec IPC es una feature muerta en silencio.** Todo campo de `pv_run`/`pv_box_def`/`rd_block` —y todo `pv_kind` nuevo— se hilvana en `write_view`/`read_view` (`src/tab.c`). Ya pasó cuatro veces. `[[freedom-render-pipeline-ipc]]`
- **`make clean` es obligatorio cuando crece una struct compartida** (`css_style`, `pv_run`, `pv_box_def`): el Makefile no rastrea dependencias de headers. Igual tras `make asan`.
- **`-fvisibility=hidden` es invariante de build (no quitar):** sin él, `hb_free` del ejecutable secuestra el alocador de HarfBuzz. Vive en `HARDEN` **y** en el `CFLAGS` de `asan`. `[[freedom-harfbuzz-shaping]]`
- Modo boyscout con memoria: ante una regresión, diff contra el commit inicial antes de tocar nada. `[[freedom-security-modules-butchered-by-fix-commits]]`

### 7.3 Hitos cerrados (una línea por hito)

> Comprimido 2026-07-17 y 2026-07-31. El detalle vive en `git log`, `spec/` y la memoria.

- **Foundation (6–18):** GUI interactiva, CSS estático + box model UA, `hostblock`, Tor/I2P, charset, render moderno, multi-pestaña, fetch asíncrono, PDF export, tooling headless, XHR/fetch gateados, scripts externos, namespaces + seccomp W^X + fork+exec, identidad anti-fp + omnibox, fullscreen (`Alt+Enter`).
- **CSS moderno (19–25):** origen `file://`, JPEG/GIF/WebP en worker, `line-height` + `--author-css`, allowlist JS, JS vivo, zoom + descargas, CSS de autor + reader mode, `@media`, flex/grid, box model de autor, selectores de atributo + `!important`, HarfBuzz shaping.
- **JS & render avanzado (26–30):** `querySelector`, `URL`/`URLSearchParams`, `float`/`clear`, `var()`/`calc()`, `visibility`/`overflow`, math functions + propiedades lógicas + shorthands, caps CSS 16x + `pv_style_cache`, doctrina trusted-host, prefetch paralelo, perfil cifrado, `border-radius` + gradientes, `fr`/px tracks, `box-sizing`, timers async, cookies de sesión, rewrite DuckDuckGo.
- **Compositor & transform (M0.1–M1.2c):** `webcaps` unificado, códec IPC bulk, `compositor` puro, z-index negativo, opacity de grupo, `mix-blend-mode` + `isolation`, transform con matriz Cairo afín (incl. `skew`/`matrix`/`transform-origin`).
- **Imágenes & datos:** `data_url` (fuzzeado, 17M execs), `srcset`, `background-image: url()` con `size`/`repeat`, webp, pipeline vídeo jkanime.
- **Vídeo pacing v2 + superficie media (jul 19):** `md_pacer` puro + 5 fixes v1 + fachada `HTMLMediaElement`/`Audio` + `<source>` por type. **v2.1:** nunca acoplar audio/pipeline a la cadencia de repintado. `[[freedom-video-pacing-v2]]`
- **Batch impacto visual (jul 19):** unidades de viewport, `skew`/`matrix`/`origin`, `backdrop-filter` + alfa de fondo, `matchMedia` + `IntersectionObserver`. `[[freedom-visual-impact-batch]]`
- **Paridad Firefox tanda 1 y 2 (jul 27 y 30):** banda de fila que muere donde empieza una caja, `cont_box_id`, `inline-block` shrink-to-fit, cajas anidadas en ítems, elementos reemplazados, `max-width`/`margin:auto`. Módulos nuevos `svg_render` + `svg_paint`. `[[freedom-firefox-parity-2026-07-30]]`
- **Paridad Firefox tanda 3 (jul 31) — tipografía:** `font-size` absoluto reemplaza la escala UA (relativo encadena); métricas UA (16px base, `heading_scale` 2.0…0.67); `position:absolute|fixed`/`float` coercen a bloque; PNG dimensionado por la caja más baja. `[[freedom-typography-parity-2026-07-31]]`
- **Paridad Firefox tanda 4 (jul 31) — estructura:** contenedores flex/grid **ANIDADOS** vía tabla `pv_cont_def` (cruza el IPC como arreglo; `layout_container` recursiona) + `display:inline-block` que fluye DENTRO de la línea. `[[freedom-nested-flex-containers-design]]`
- **Paridad Firefox tanda 5 (jul 31) — grid Bootstrap (jkanime):** el colapso a columna estrecha eran 5 brechas sumadas; la dominante: los runs reemplazados perdían membresía flex en los 3 cruces del códec. `emit_replaced_row` compartido plano+flex. `[[freedom-flex-replaced-runs-and-nesting-2026-07-31]]`
- **Madurez render tanda 6 (ago 1):** `<img>`/`<svg>` en línea respetan `width`/`height` de CSS (antes viewBox natural → íconos gigantes); spacer flex vacío que **crece** reserva su hueco; `RD_INPUT` en caja se sienta en su rect de contenido. `[[freedom-replaced-css-sizing-and-flex-spacer]]`
- **Madurez render tanda 7 (ago 1):** el flex-basis de un ítem reemplazado se medía como su MARKUP-texto → íconos dispersos y texto vecino a min-content; `replaced_item_width` lo mide por tamaño intrínseco. SVG con un solo eje deriva el otro por aspecto del `viewBox`. `fill` de CSS colorea figuras SVG sin fill propio (`sv_parse_ex`, reusa `fg_rgb`). Un SVG sin tamaño llena el contenedor **también en Firefox** (medido). `[[freedom-flex-replaced-measure-svg-fill]]`
- **Paridad Firefox tanda 8 (ago 1) — slashdot:** el título negro-sobre-teal era el límite `CSS_MAX_COMPOUNDS 4` → todo selector de 5+ compuestos (`#firehose article header h2 a`) se descartaba en silencio; subido a 8 (mide: profundidad<=6 = 99% de la hoja). El header teal 3x de alto era `.comment-bubble{position:absolute}` heredando el float del `article` — `position:absolute|fixed` computa `float:none` (CSS 2.2 §9.7, flag `oof_seen` en `resolve_context`). Un `<img>` bloqueado con `width/height` reservaba una barra a todo el ancho → `placeholder_display_size` le da su caja declarada (paridad broken-image; importa porque las imágenes van OFF por defecto). (`:hover`-siempre era doctrina hasta ago 11; **revertida**, ver tanda 15.) Nav superior sigue tosco (pre-existente). `[[freedom-slashdot-render-2026-08-01]]`
- **Paridad Firefox tanda 9 (ago 2) — tablas de datos que colapsaban a lista vertical:** dos brechas sumadas. (1) El whitespace fuente entre `</td>` y `<td>` (hijo directo de `<tr>`/`<tbody>`/`<table>`) se emitía como run y partía la corrida **contigua** de ítems del grid sintetizado → cada celda a su fila (CSS 2.1 §17.2.1: ese whitespace no genera caja; ahora se descarta). (2) Un contenedor flex/grid **dentro de una columna de float** (el cuerpo de artículo de slashdot va `float:left`) se fluía run-por-run como texto plano en vez de por `layout_container` → misma colapso; ahora la columna es una BFC real y llama a `layout_container` a su ancho, con el `x_off` por-columna **sumado** (no asignado) al trasladar filas. Tablas de mercado de slashdot: lista de 1 columna → grid de 2. Sin hardcodeo; default byte-idéntico. `[[freedom-table-grid-in-float-2026-08-02]]`
- **Paridad Firefox tanda 10 (ago 2) — buscador DuckDuckGo + nav slashdot:** dos bugs sistémicos independientes. (1) **DuckDuckGo `/html` salía con cajas de resultado vacías** (título/url/snippet recortados): un wrapper de nivel de página con `overflow:hidden` (patrón universal anti-scroll-horizontal) se parte en varios `rc_box` al cruzar bandas de layout (header→resultados); el clip tomaba el **primer** fragmento (solo el header) → intersección vacía → nada pintaba. `ov_box_bounds` ahora **une todos los fragmentos** → el clip es el border-box completo. (2) **Login/Sign-up gigantes en slashdot:** `.ua{width:50%}` (UL `float:right` de `<li>` inline-block) es contenedor flex/anon **y** float; tanto el float-seed como el hbox-walk copiaban su `width:50%` como ancho **propio de cada ítem** → cada uno al 50% de la página. `width` no se hereda: flag `crossed_container` corta el sembrado de ancho al llegar al contenedor del run (ancho solo del elemento propio, si no auto/shrink). Ambos: suite `examples/*.html` byte-idéntica, ASan/UBSan + fuzz-pv limpio. Firefox headless roto en este entorno → verificado por dumps+PNG, no pixel-parity. `[[freedom-overflow-clip-union-and-flex-item-width-2026-08-02]]`
- **Pseudo-elementos ::before/::after (ago 3):** cascade separa `content_before_str`/`content_after_str` por pseudo-elemento (`csel_matches` con output `pseudo_kind` opcional, `apply_decl` rutea `content` al campo correcto). page_view genera runs sintéticos para elementos vacíos (content-leaf path con pseudo-content) y para elementos con hijos (::before prepended, ::after tracked con pending-emit al salir del subtree). IPC transporta ambos campos. 5 tests unitarios (cascade separation + run generation), 5 tests page_view (empty, with-children, both, no-content, ordering). ASan+UBSan limpio, fuzz-css 51k runs y fuzz-pv 18k runs sin crashes. `[[freedom-pseudo-elements-content-2026-08-03]]`
- **word-break vs overflow-wrap des-unificados (ago 3):** `overflow-wrap`/`word-wrap:break-word` (regla defensiva casi universal) cortaba la última palabra de CADA línea (estaba unificado con el corte codicioso de `word-break:break-all`). Nuevo `CSS_WB_BREAK_WORD` (último recurso) distinto de `CSS_WB_BREAK` (codicioso); `flow_text` usa modo 0/1/2. Snippets de DuckDuckGo legibles. Cruza el IPC como int crudo (sin cambio de códec). ASan + fuzz-css 53k + fuzz-pv 20k limpios; 4 modos = Firefox. `[[freedom-overflow-wrap-break-word-2026-08-03]]`
- **Paridad Firefox tanda 11 (ago 10) — las tres brechas que más rompían una página, MEDIDAS:** el arnés `make parity` (que ya existía, con `tools/pngdiff.c` y baseline) es la función objetivo: **TOTAL 301.93 → 210.59 (−30 %)**, sin una sola página peor. Tres sondas nuevas en `tests/parity/pages/` aíslan cada bug, y son **más altas que 768 px** a propósito: Firefox reporta la altura de viewport en páginas cortas y ahí el `h_ratio` no mide nada. (1) **`rem` rebasado en el `font-size` de la raíz** — `html{font-size:62.5%}` es idioma casi universal y `rem` estaba clavado en 16 px ⇒ **toda** esa página 1.6× más grande. Doble pase en `css_parse_scoped`: la raíz se lee por la **cascada real** y se reescribe el TEXTO (`rem_rebase`), no los 22 sitios de `interp_len` — un solo cambio cubre `font-size`, `line-height`, cajas, `calc()`, shorthands, gradientes y `var()`. Nunca toca preludios de at-rule (dentro de `@media`, `rem` es la inicial 16 px), strings ni `url()`; y hay chequeo de **punto fijo** por si la raíz se define a sí misma en `rem`. De paso `media_len_px` honra la unidad (antes `40em` comparaba **40** contra el viewport). Sonda 41.39 → 5.95. (2) **Texto que fluye AL LADO de un float** (la brecha #1 medida del motor) — `fx_float_insets` puro (CSS 2.1 §9.5): un float no mueve el bloque, **acorta las líneas** que solapa, y la línea recupera el ancho completo al pasar su `bottom`. Una banda de 1 ítem registra exclusión en vez de empujar `cur_top`; las bandas multi-ítem quedan intactas. Segundo bug en la misma sonda: un `float:right` **solo** pintaba su caja a la **izquierda**, porque `band_common_box` devolvía la caja **propia** del float como contexto compartido (`band_shared_box`). Sonda 34.25 → 17.06. (3) **Tablas: columnas por contenido** — `pv_cont_def.is_table` distingue el grid sintetizado del `display:grid` de autor (el de autor queda byte-idéntico), y la caja de ítem de una celda ya no puede ser la del `<body>`, que le inyectaba su padding y duplicaba el alto de cada fila. Sonda 43.12 → 7.09. `[[freedom-firefox-parity-batch-2026-08-10]]`
- **Paridad Firefox tanda 12 (ago 10) — `@media` al ancho de render (cambio de doctrina, autorizado):** `@media (min-width/max-width)` se evaluaba contra un viewport **fijo de 1920 px** (anti-fp) mientras la página se **pinta a ~1000 px**, así que Wikipedia activaba su layout de sidebar fijado `@media(min-width:1680px)` y **apretaba todo el artículo en una columna de 248 px** (una palabra por línea, 5× el alto de Firefox). Ahora `pv_build_styled` recibe `viewport_w` (nuevo campo del códec IPC `OP_LOAD`, con `tab_set_viewport_w`): GUI usa `w->width`, headless usa `ui_render_viewport_w()` (= `PNG_PAGE_W` 1000). **Solo la query de ancho lo ve; las unidades de viewport (vw/vh) siguen contra el desktop normalizado** ⇒ ninguna geometría real se filtra a longitudes computadas. Wikipedia 37788→22888 px, artículo ancho (576 filas >700 px). TOTAL 210.59→207.51. `layout-diff` byte-idéntico, 1459 asserts + ASan/UBSan limpios. Junto: **dimensionado de tracks intrínsecos de grid** (`min-content`/`auto` + `fr` ⇒ el track intrínseco toma su contenido, el `fr` el resto; byte-idéntico, correcto, hoy no-op en la corpus a 1920). `[[freedom-parity-container-diagnosis-2026-08-10]]`
- **Paridad Firefox tanda 13 (ago 11) — las tres constantes verticales y el pseudo-elemento que estilaba al elemento. TOTAL 207.51 → 149.95 (−28 %), sin una sola página peor:** cuatro bugs **sistémicos** (afectan toda página, no un sitio), medidos con la sonda nueva `tests/parity/pages/ua-metrics.html` (18.94 → 0.98). (1) **`line-height: normal` era 1.2× la caja natural** — `(asc+desc)` **ya es** `normal`; multiplicarla otra vez estiraba cada línea un 20 %. `line_spacing` 1.2 → **1.0** (medido: línea de 16 px = 23 px en ambos motores). −23.03 de una constante. (2) **Todo bloque de texto cobraba el margen UA de un `<p>`** — `rd_block_tag` devuelve `"p"` para todo `RD_PARAGRAPH`, así que `<div>`/`<section>`/`<td>` metían **1em fantasma antes de cada bloque**. Nuevo código `bx_ua_tag` (estructura, **nunca** gateado por `caps.css`: un margen UA es la hoja UA, no estilo de autor) que `page_view` resuelve del ancestro de bloque y cruza el códec IPC; `bx_ua_of_tag`/`bx_default_for_ua` comparten la **misma** `TAG_TABLE` (una sola fuente de verdad). Los `<p>` reales conservan su margen — eso es lo que guarda la sección B de la sonda. −10.8. (3) **El `line-height` del AUTOR se aplicaba sobre la caja natural en vez del `font-size`** (CSS 2.1 §10.8.1): dos unidades distintas, ≈1.44× de más en toda página que declara interlineado — o sea todo buscador y todo portal. El acumulador por línea pasa a **píxeles** (`line_lead_px`, calculado donde se conoce el `font-size` del fragmento). −25.32; `slashdot` `h_ratio` 1.27 → **1.04**. (4) **`::before`/`::after` estilaban el elemento originante**: solo `content` debe cruzar (CSS 2.1 §12.1). La causa raíz estaba en `css_select`: el marcador de pseudo lo produce el compuesto **subjeto**, pero `complex_matches` le cedía el slot del llamante al recorrido de ancestros **justo en el nivel del subjeto**, que lo pisaba con -1 ⇒ **solo sobrevivía en selectores de un compuesto**, y toda regla real lleva combinadores. Los pies de foto de Wikipedia salían en una columna de 15 px, 131 líneas de un carácter (131 → 0). Se descarta **antes** de reclamar el slot de cascada, o sería una pérdida silenciosa en vez de una fuga. 1412 tests + ASan/UBSan limpios, fuzz-css 53k y fuzz-pv 21k sin hallazgos. `layout-diff`: las 20 páginas se acortan 5–22 % con **cero** cambio estructural (mismo `nbox`/`nrow`/`npositioned`) → baseline re-congelado. De paso: `fuzz-pv` no compilaba desde la tanda 12 (el harness no seguía a `viewport_w`) — reparado. `[[freedom-vertical-metrics-and-pseudo-leak-2026-08-11]]`
- **Tanda 15 (ago 11) — «todo sale del CSS»:** `css_length` (`cl_`) es el ÚNICO resolvedor de `<length>` (reemplazó 5 tablas privadas divergentes: `pt` descartado, `rem`==`em`, `vmax`==`vw`); `cl_number` acepta `.5`; `:hover/:active/:focus*` los gobierna `css_element.state` (0 = ninguno, antes matcheaban SIEMPRE); el diagnóstico de imagen bloqueada sale del flujo (solo `alt`, HTML §4.8.4.4). `parity` empeoró 145.10→148.73 a propósito (baseline sin re-congelar). `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **Tooling & seguridad:** doctrinas V-001..V-004 (abajo). `-fvisibility=hidden` invariante. `io_uring` prohibido en worker.
- **`<select>` cerrado muestra su opción seleccionada (ago 11) — corrección, no score.** `describe_control` derivaba el `value` visible del control con `collect_text(node)`, que **aplana el `<select>` entero** ⇒ pintaba `"All Regions Argentina Australia …"` (las 200+ opciones del filtro de DuckDuckGo concatenadas) en vez de `"All Regions"`. Por HTML *Rendering* §"The select element" un control colapsado muestra **solo su opción seleccionada**: la ÚLTIMA `<option selected>` en orden de árbol, o —sin ninguna— la PRIMera opción. Se captura en el mismo walk que ya arma `select_opts` (DRY), y `selected` se detecta con `has_attribute` (booleano sin valor, `get_attribute` devuelve NULL). Nada en duro, todo del HTML. `make parity` **148.73 → 148.76** (ruido): la barra de filtros de ddg NO desapila por esto —su apilado es otro bug (float:right + `transform:scale` + posicionamiento negativo del header)— pero el control ya pinta la etiqueta correcta (verificado en PNG). `layout-diff` byte-idéntico (ningún example tiene `<select>`); 3 candados (`selected`, last-wins, default-first). Descubierto de paso: la brecha de wikipedia (figcaption estallado) es `display:table`/`table-caption` **descartado** por `interp_display` (retorna -1) → el `<figcaption>` no maqueta como caption; y el `~=` de atributo es CORRECTO (matchea token entero, no substring — confirmado). `[[freedom-select-selected-option-2026-08-11]]`
- **Paridad Firefox tanda 14 (ago 11) — el elemento raíz estaba FUERA de la herencia. TOTAL 149.95 → 145.10:** el walk de contexto cortaba en `<body>`, así que TODA regla `html{…}` (font-size 90 %/62.5 %, color) se descartaba; `fx_auto_min_size` (Flexbox §4.5) reemplaza el piso `min_main=1.0`; un hijo `position:absolute` de un contenedor flex NO es ítem; `visibility` se hereda y oculta TEXTO; `flex:1 1 0` parsea. `[[freedom-root-inheritance-and-flex-spec-2026-08-11]]`
- **Tanda 16 (ago 11) — estructura:** `display:table` family por UNA función pura `bx_table_role_of(tag,display)` (3.74× → exacto); la fila anónima de inline-blocks envuelve (`CSS_FW_WRAP`, §9.4.2); el margen UA no lo borra el contenido (`bx_block_ua_box`); **`css_element.state` se leía SIN INICIALIZAR (render no determinista)**: una struct de vista sobre la pila se zero-inicializa por construcción. Sondas `css-table`, `inline-links`, `multicol`, `inline-replaced`, `pct-box`. `[[freedom-table-roles-inline-wrap-ua-margin-2026-08-11]]`
- **Tanda 17 (ago 12) — `<length-percentage>` es un TIPO, no una propiedad de `width`:** un solo `bx_lp_px`, per-mille, tabla de *basis* normativa (margin/padding de las 4 caras contra el ANCHO); `height` es altura de contenido; multicolumna (`fx_multicol_*`); reemplazado inline fluye en la línea (señal estructural); `clear` es del elemento y un flotante no se limpia contra sí mismo; las exclusiones sobreviven al entrar en una caja anidada. TOTAL 231.21→147.64. `[[freedom-length-percentage-multicol-inline-replaced-2026-08-12]]`
- **Tanda 18 (ago 13) — `em` valía 16 px en toda la página:** una longitud relativa a la fuente es `a + b·font-size`; la derivada `cl_lp.em` viaja per-mille y se dobla en UN sitio (`fold_font_relative`) al cerrar la cascada del elemento; `font-size` heredado = input del motor (`css_element.font_size`), resuelto raíz→abajo, memoizado e ITERATIVO (profundidad elegida por el atacante); 3 agujeros V-002 (decls sin zero-init); prefijos de vendor = alias. `[[freedom-font-relative-lengths-2026-08-13]]`
- **Tanda 19 (ago 14) — margen vertical, escala de encabezados, colocación por nombre:** colapso de márgenes CSS 2.1 §8.3.1 (módulo puro `block_flow`: `max(0,pos)+min(0,neg)`, padre-hijo en ambas direcciones); un margen genera caja; `PV_MAX_BOXES` 256 en la PILA perdía cajas en portadas reales (un límite que una página normal alcanza es un bug de render); la escala UA de `h1…` sobrevive a un `font-size` absoluto HEREDADO; `grid-template-areas` por nombre (dos pases); `::before` es contenido INLINE. TOTAL 154.06→126.04. `[[freedom-margin-collapse-heading-scale-grid-areas-2026-08-14]]`
- **Tanda 20 (ago 15) — el arnés medía la POLÍTICA, no el layout:** Firefox corría con JS y red mientras Freedom no (wikipedia 28.87→6.30 sin tocar el motor; jkanime SÍ es medición limpia); nuevo `--dump-css-drops` separa `unknown-prop` de `bad-value`; palabras CSS-wide, `transparent/currentColor`, `calc()` con %, una regla perdía declaraciones por array lleno, `bx_width_cap` tomaba el mínimo en vez de la suma, `own_box_id` separado de `block_id`. TOTAL 129.19→110.64. `[[freedom-parity-harness-and-parser-drops-2026-08-15]]`
- **Tanda 26 (sep 11) — `make drops` gate + trusted-profile doc.** Los descartes del parser dejan de ser reporte y pasan a ser gate: `make drops`/`drops-update` con baselines en `tests/parity/drops/` (28 páginas); un `bad-value` nuevo falla el build. `spec/parity.md` documenta el perfil trusted (el corpus ya renderiza con `--author-css --images` = lo que la allowlist enciende; JS sigue off en ambos lados o se miden documentos distintos).
- **Tanda 27 (sep 11) — listas de `transform`, `<angle>`, 3D, `box-orient`, `origin:0`.** Seis tests rojos SDD en `test_css_drops` (corpus-medidos) a verde + `box-orient` (el comentario prometía el alias, el despacho no lo tenía): composición por matriz afín + QR compartido con `matrix()`, `translate3d/Z` aplanados, `turn/rad/grad`/fraccionales, `skew` fuera de la matriz (el pintor fija el orden), `none` emitía escala 1000 (10x, sin test que lo atara) → 100. jkanime 371→344 descartes, slashdot/wikipedia listas skew/center adentro; `parity` TOTAL sin deltas (transform es pintura, no layout), `layout-diff` byte-idéntico, 4 mutantes muertos, ASan/UBSan + `fuzz-css` 51k limpios, PNG visual.
- **Tanda 28 (sep 11) — doble cómputo del margen en columna pulled (§7d.6).**
- **Tanda 29 (sep 11) — whitespace inline en tablas (WPT 11.33→6.05).** `parent_is_table_internal` descartaba todo espacio con padre tabla, incluso entre inlines (`<span>a</span> <span>b</span>` → "ab"): ahora mira vecinos (se descarta solo sin material de celda anónima — elemento sin rol o texto con contenido — a través de blancos, acotado 16). Test rojo en `test_page_view`, mutante muerto, tanda-9 intacta (inter-celda sigue cayendo), ASan + `fuzz-pv` 12k + `fuzz-dom` 167k limpios, `parity`/`layout-diff`/`drops` sin deltas, PNG "a b" visual.
- **Tanda 30 (sep 18) — un `<img>` sin `src` es imagen rota, no ausencia (HTML §4.8.3).**
- **Tanda 31 (sep 18) — `content` con escapes + `::before` sin texto: las icon fonts (CSS Syntax §4.3.7, CSS 2.1 §5.12.3/§12.1).**

- **Tanda 32 (sep 29) — sitios del allow∩js: lobste.rs 42.60 → 1.44, corpus viejo `parity` −21.58 (jkanime −12.98), ninguna página peor salvo slashdot +0.45.** `[[freedom-allowlist-sites-lobsters-2026-09-29]]`

- **Tanda 33 (sep 29) — el CSS de los design systems llegaba al parser y se perdía en silencio (medido en github.com y huggingface.co del allowlist).** `[[freedom-design-system-css-2026-09-29]]`

- **Tanda 34 (sep 29) — custom properties POR ELEMENTO, con herencia, y los contenedores flex/grid que no generaban caja.** `[[freedom-design-system-css-2026-09-29]]`

- **Tanda 35 (sep 30) — propagación de eventos + plan "Firefox para allow∩js".** Plan del dueño (terceros con `hostblock`, persistencia solo en RAM, runtime JS primero). Un registro único de listeners con captura/destino/burbuja (DOM §2.9): React y toda delegación estaban sordos. `fuzz-jsdom` nuevo. `[[freedom-firefox-for-trusted-plan-2026-09-30]]`

- **Tanda 36 (sep 30) — geometría real, navegación JS, `history`, `window.open` (B3+B4a-c).** `js_geom` + `OP_GEOM` (doble gate; headless maqueta antes de los timers); `location.href=` en click/timer/evento se descartaba en silencio; `pushState`/`popstate` con ids de documento; `window.open` noopener en gesto. Boyscout: `url_authority_len` tragaba la consulta de una URL sin ruta.

- **Tanda 37 (sep 30) — WebSocket y `localStorage` en RAM (B5+B7).** `sf_ws_*` comparte `sf_setup_handle` con fetch (verificado en vivo: un eco no-PQ se rechaza con la política por defecto); `ws_hub` en el GUI; `web_storage` puro con cuota 5 MiB y validación total de la instantánea del worker. En este host `-lcurl` es GnuTLS: las sondas enlazan `-l:libcurl.so.4`.

- **Tanda 38 (sep 30) — módulos ES, import maps y la superficie DOM que GitHub necesita (B6a).** `[[freedom-firefox-for-trusted-plan-2026-09-30]]`

- **Tanda 39 (sep 30) — errores de Freebug en sitios reales: nodos de texto, `Worker`, datos binarios (B5+B6b).** `[[freedom-firefox-for-trusted-plan-2026-09-30]]`

- **Tanda 40 (oct 1) — los sitios de allow.conf medidos contra Firefox: botones, subárboles out-of-flow, columnas flex, media queries, max-width, cajas generadas.** `[[freedom-allowlist-sites-tanda40-2026-10-01]]`

- **Tanda 40b (oct 2) — el ítem flex dejaba de re-abrir `html`/`body` y conserva sus márgenes.**

- **Tanda 40c (oct 2) — alfa en paradas de degradado y pseudo-clases dentro de `:not()`.**

- **Tanda 41 (oct 2) — márgenes `auto` en columnas flex y la caja raíz que un `<img>` cerraba.**

- **Tanda 42 (oct 15) — sitios del allowlist medidos en el corpus: TOTAL 280.27 → 197.16 (−83.11), ninguna página peor.** `[[freedom-allowlist-corpus-tanda42-2026-10-15]]`

- **Tanda 43 (oct 16) — velocidad y "se ve como Firefox": índice de reglas, fuentes por nombre, margen UA del body, controles, grafo de módulos, CSS descartado.** `[[freedom-speed-fonts-controls-tanda43-2026-10-16]]`

- **Tanda 44 (oct 17) — allowlist contra Firefox: alturas `%`, sombras, glifos, grilla de filas, flotantes en ítems. `parity` 200.77 → 171.38 sobre el corpus previo (+ `site-ntp` 1.38).** `[[freedom-allowlist-tanda44-2026-10-17]]`

- **Tanda 45 (oct 17) — `<br>`, BFC, flotantes, pools, reemplazados. `parity` 172.76 → 119.05 (baseline re-congelado: el probe de altura fallaba en justpaste/lobsters).** `[[freedom-tanda45-br-bfc-pools-2026-10-17]]`

- **Tanda 46 (oct 18) — la caja inline, el leading y el arnés (vh).** `[[freedom-inline-box-leading-harness-tanda46-2026-10-18]]`

- **Tanda 47 (oct 18) — apilado posicionado, hijos absolutos y la fuente por defecto. `parity` TOTAL 157.45 → 130.28 (discord 17.83→1.93, gitlab 14.75→6.78, github 11.28→9.36), cero páginas peor.** `[[freedom-positioned-stacking-fbench-tanda47-2026-10-18]]`

- **Tanda 48 (oct 19) — tabla de datos dentro de un grid: `site-animate` 13.07 → 4.42, TOTAL −8.65 sin una página peor.** `[[freedom-table-in-grid-tanda48-2026-10-19]]`

- **Tanda 49 (oct 20) — cinco brechas sistémicas medidas en GitLab/GitHub. TOTAL −0.61, `layout-diff` byte-idéntico, ASan/UBSan + fuzz-svg 170k + fuzz-pv limpios.** `[[freedom-heading-link-oof-veto-minsize-tanda49-2026-10-20]]`

- **Tanda 50 (oct 20) — UNA fuente de verdad (GUI = headless = benchmark), slashdot 17.69 → 5.0, efectos CSS y Custom Elements. `parity` TOTAL −13.57, WPT/layout/drops/drift verdes, ASan/UBSan + fuzz limpios.** `[[freedom-single-source-of-truth-tanda50-2026-10-20]]`

- **Tanda 51 (oct 20) — el README mostraba OTRO documento, el marco con brillo de GitHub y los flotantes anidados.** `[[freedom-live-sites-github-glow-slashdot-header-tanda51-2026-10-20]]`

- **Tanda 52 (oct 20) — Slashdot en la GUI real: cabeceras con flotantes, rail y alto declarado.** `[[freedom-live-sites-github-glow-slashdot-header-tanda51-2026-10-20]]`

- **Tanda 53 (oct 21) — dos front ends, dos verdades: el GUI y `--as-gui` leían cosas distintas.**

- **Tanda 54 (oct 21) — Slashdot en la GUI real, `clip-path`, y el `.deb` mudo. `parity` slashdot −1.03, ninguna página peor.**

- **Tanda 55 (oct 23) — JS lazy/observers/Freebug: `IntersectionObserver` y `ResizeObserver` reales (allow∩js), `MutationObserver` real, API de consola del REPL.**

- **Tanda 56 (oct 23) — un `<svg>` ítem de contenedor se centraba contra la PÁGINA.**

- **Tanda 57 (oct 23) — `getComputedStyle` real (allow∩js).**

- **Tanda 58 (oct 23) — GitLab: `gap` de un valor y el margen antes de un contenedor.**

- **Tanda 59 (oct 23) — superficie JS de plataforma + `rules()` de Freebug.** `[[freedom-platform-surface-rules-tanda59-2026-10-23]]`

- **Tanda 60 (oct 23) — configuracion de identidad y APIs sensibles (`about:config`).** Modulo puro `identity` (`idn_`, `spec/identity.md`): User-Agent, idiomas y geolocalizacion fija, validados fail-closed (un campo invalido no cambia nada; CR/LF/no-ASCII rechazados), serializados en una linea (prefs cifradas) y con la pagina `about:config` generada y escapada. UNA fuente de verdad: el mismo valor llega a la cabecera de red (`sf_config.accept_language`, `apply_route`), a `navigator.userAgent/appVersion/language(s)` (`je_install_identity`, via un bloque nuevo de `OP_LOAD`: `tab_set_identity`) y a `navigator.geolocation` (`jd_install_geolocation`, SOLO host allow∩js con lugar fijo; devuelve exactamente lo escrito por el usuario, sin sensor ni red). Menu hamburguesa: "Config: identity & APIs"; reemplaza al campo de UA sin validar que no llegaba a `navigator`. Seguridad: el formulario de `about:config` solo se acepta si la pagina actual ES la interna (`config_page` y `cur_top == NULL`): un `<form action="about:config?...">` de una pagina remota no reescribe la identidad. `sf_user_agent_or_default` descarta valores con bytes de control. WebGL y Service Workers NO se ofrecen: el motor no los implementa y un interruptor sin motor seria una promesa falsa (la pagina lo dice). Headless `--as-gui` lee la misma identidad persistida. Verificado en la GUI real (Xvfb+weston+xdotool: llenar, aplicar, reiniciar, persistencia), tests rojo-verde en `test_identity`/`test_prefs`/`test_secure_fetch`/`test_js_env`/`test_js_dom`/`test_tab`, `make test`/`asan` limpios, `drift` OK. `[[freedom-identity-config-tanda60-2026-10-23]]`

- **Tanda 61 (oct 24) — `indexedDB` y tres causas de render medidas en GitLab.** (1) `indexedDB` en memoria de la pagina (`jd_install_indexeddb`, solo allow∩js; almacenes, indices, cursores perezosos, `IDBKeyRange`, versionchange con rollback), nada a disco. (2) **`overflow:hidden` recortaba al content box**: CSS Overflow recorta al **padding box** (`ov_content_rect`); todo overlay `inset:0` de una seccion con padding quedaba mutilado. (3) **`background-clip: padding-box|content-box`** de punta a punta (`pv_box_def.bg_clip`, `TAB_WIRE_BOX_F_N` 268, clip de cairo sobre relleno e imagenes; base del % de padding = ancho propio, exacto en `inset:0`). (4) **Una capa `url()` en `mask-image` es "no disponible"**: Firefox no pinta el elemento (medido: sola, XOR y ADD) y Freedom no descarga mascaras; antes invalidaba la declaracion y pintaba una losa gris sobre el contenido (`css_mask`: una sola capa transparente; `data:` sigue descartado). GitLab 13.56 → 11.95, TOTAL 110.74 → 110.41, telegram +0.27 (iconos `mask:url()` ahora ocultos como en Firefox offline). Tests rojos verificados (`test_freedom` x2, `test_css_mask`, `test_js_dom`, `test_tab`), `make test`/`asan` limpios, `layout-diff` byte-identico, `drift` OK, `drops` re-congelado (las mascaras dejan de ser `bad-value`). **Boy scout:** el regenerador de shims perdio `js_dom_ext.c` una vez (regex perezosa): reconstruido desde HEAD + fuentes `.js`; nunca regenerar con regex sobre el archivo, usar un unico paso desde HEAD. `[[freedom-indexeddb-overflow-bgclip-mask-tanda61-2026-10-24]]`

- **Tanda 62 (oct 24) — JS de plataforma sin inventos y márgenes negativos reales.** Medido con `--dump-console` en los sitios de `js.conf`: DDG 17→1 errores, Blogger 2→0, GitHub 3→1 (resto: presupuesto de 15 s del intérprete y hidratación #418 de DDG). (1) Se retiró el stub de `jQuery`/`$` y los globales inventados (`duckduckgo`, `__NEXT_DATA__`, `locale_data`): rompían `a.fn.x` en librerías. (2) `window` `error`/`onerror` y `unhandledrejection` reales (`__reportError`, rastreador de rechazos en `js_sandbox`, `spec/js_sandbox.md` 7d). (3) `DocumentFragment`/`ShadowRoot` son `EventTarget`; `MutationObserver.observe(document|shadowRoot)`; interfaces `SVG*`. (4) **`css_hbox_resolve` recortaba a 0 todo margen horizontal negativo** (Bootstrap `.row`, hero de GitHub): ahora viaja con signo; ítem flex mide por caja exterior. `parity` TOTAL −0.78 (gitlab −1.15), `layout-diff` idéntico, 185+104 tests, ASan limpio, rojo verificado en cada test. (5) **Carga lazy (pedido del dueño):** `<img loading=lazy>` diferido hasta el viewport±1000 px (`load_lazy_images`, `spec/page_view.md`); `<script>` insertado dinámicamente se ejecuta (`spec/js_dom.md` 7m); **la red del worker ya no se cierra al terminar la carga** (AJAX, `import()` y script lazy desde timers/eventos/observadores funcionan; antes devolvían status 0); `import()` clásico resuelve contra el documento. `[[freedom-js-errors-negative-margins-tanda62-2026-10-24]]`

- **Tanda 63 (oct 24) — caché, redirecciones persistentes y red acotada (pedido del dueño: "como Firefox, cifrado con Kyber 512").** (1) `pq_seal` (`pqs_`, `spec/pq_seal.md`): ML-KEM-512 de OpenSSL + clave del perfil por HKDF — **híbrido** (hacen falta los dos secretos; nunca PQ puro). (2) `http_cache` (`hc_`, `spec/http_cache.md`) + `cached_fetch` (`cf_`): caché HTTP al estilo Firefox (`max-age`/`Expires`/heurística 10 %, `ETag`/`Last-Modified` con GET condicional contra la URL **final**), blobs sellados con `pq_seal`, **nombre = HMAC de (partición ‖ url)** (nada legible), partición por sitio, 8 MiB/entrada, 128 MiB total, `FREEDOM_NO_CACHE=1` la apaga, solo GUI (el arnés headless sigue sin caché). (3) **Memoria de redirecciones 301/308 entre sesiones** (`sf_rcache_set_backing`): la siguiente visita entra directo al destino, que se vuelve a pedir bajo la política completa; 30 días, solo https; `FREEDOM_TRACE_FETCH` imprime `cache[hit|miss|revalidated]` y `redirect-memory`. (4) **Bloqueo de la GUI acotado:** la red post-carga cuenta su tiempo por operación (`FC_TAB_OP_NET_BUDGET_MS` 3000, `tab_set_op_net_budget_ms`); agotado, el resto de esa operación falla (status 0) en vez de congelar. NO es asíncrono: el fetch del padre sigue siendo síncrono. (5) **GitHub:** `customElements.define` era O(define²×DOM) (`github-elements` 8.3 s → 0.9 s); `FREEDOM_JS_PROFILE=1` mide cada script; el hero (texto a 49.8 px) era `item_sides_at_level` tomando el contenedor anidado como ítem en vez del wrapper (ddmin automático de ~5000 reglas a 5). Validación: 5 suites nuevas, `layout-diff` idéntico, ASan limpio. `[[freedom-http-cache-pqseal-tanda63-2026-10-24]]`

- **Tanda 64 (oct 24) — red asíncrona, selectores lineales y wrappers compartidos.** (1) `tab_tick_async`/`tab_geometry_async` (`spec/tab.md`): el tick y la publicación de geometría corren en un hilo del tab y avisan por `eventfd`; la ventana sigue pintando mientras un XHR espera. Un solo trabajo a la vez; TODA otra llamada pública al worker espera y descarta su resultado obsoleto; `gui_quiesce` protege lo que lee el fetcher (URL, listas de hosts, credenciales). Click/evento/ws/popstate siguen síncronos (tope de 3 s por operación). (2) **`querySelectorAll`/`matches`/`closest` eran O(N²)** en documentos anchos: `build_chain` recorría los hermanos y contaba los hijos de cada ancestro por candidato; `csel_needs_structure` (pura) se lo salta si el selector no lee estructura: 8000 hermanos 5223 ms → 41 ms. (3) Los ~100 miembros de cada wrapper viven UNA vez en `HTMLElement.prototype` (`this._h`; los stubs delegan por `memD`). (4) `FREEDOM_JS_PROFILE=1` mide cada script y cuenta selectores. `[[freedom-http-cache-pqseal-tanda63-2026-10-24]]`

- **Tanda 65 (oct 24) — tiempo de render medido en la GUI real y recortado.** `make fbench` mide render-hasta-idle de la ventana real (weston) contra Firefox (`spec/parity.md` "Timing"); `wl_guard` evita que el compositor mate al cliente con el socket sin leer (caida de Wikipedia con imagenes); doble buffer SHM (`shm_slots`) elimina el parpadeo del video. Rendimiento: snapshot pre-script omitido sin scripts, cascada sin copias de 7 KB (`cached_element_style_ref`), filtro de ancestros por Bloom en selectores (`csel_anc_reject`), blur solo sobre el rectangulo con tinta (`bb_ink_rect`). Wikipedia 539->295 ms, GitHub 1473->871, Discord 20984->338. `parity`/`layout-diff`/`drops` sin cambios. `[[freedom-gui-timing-tanda65-2026-10-24]]`

- **Tanda 66 (oct 24) — barrido de consola JS en los sitios de `js.conf`: OSM 3→0, YouTube 2→0, HF 3→1, GitHub 5→2, reddit 11→8.** Causas sistémicas, cada una con test rojo: módulos `data:` con imports absolutos, cookie jar muerto en la primera visita, accesor delegador reentrante, `<template>.content` vacío (hidratación de Svelte), `nodeName`, `document.firstElementChild`, `attributes` iterable, `console` escribible. `spec/js_dom.md` 7o.

- **Tanda 67 (oct 25) — GitLab 13.38 → 2.7 (TOTAL −17.7, ninguna página peor), pestañas de Freebug y pila JS de miles de niveles.** Cuatro causas de motor medidas en la sección real (aisladas con `tools/prune.py` + oráculo de píxel): (1) `bt_defer_roots` difería TODO el subárbol de un `relative` tras un absoluto z:0 y un descendiente con `z` MAYOR (`.layout{z-index:1}`) quedaba bajo el `::before` posterior — ahora conserva su turno; (2) el `::after` pendiente de un elemento con hijos no heredaba contenedor/ítem/bloque si el pseudo no tenía caja propia y **partía la banda del ítem flex** (`pv_after_pending`, un emisor DRY); (3) los pseudos pintaban con el color propio del elemento, no el heredado; (4) los hijos de una columna flex que fluye como bloque no se blockificaban (`<p style="display:flex;flex-direction:column">` en una línea). JS: `localName`/`namespaceURI`/`prefix` (reddit 3→0), `DOMStringMap` (facebook), y el tope de pila de QuickJS era 256 KiB = **~180 niveles de recursión** (Firefox: decenas de miles; la hidratación de Svelte en HF desbordaba): ahora `js_stack_limit_for` = 75 % de `RLIMIT_STACK` (≤ 6 MiB, >2000 niveles) leído ANTES de seccomp (`js_prime_stack_limit`: `getrlimit` no está permitido en el worker; sin eso el worker moría por SIGSYS). **Freebug** con pestañas Console/HTML/CSS/Script/Net: módulo puro `fb_panes` (`fbp_`, `spec/fb_panes.md`: geometría de la barra, selector solo como literal JS escapado, una expresión por panel) + `--dump-pane=TAB[:ARG]` headless con la MISMA expresión; verificado con clics y teclas reales en weston. `[[freedom-freebug-tabs-gitlab-stack-tanda67-2026-10-25]]`

- **Tanda 68 (oct 25) — GitHub 48 s → 28 s, YouTube/justpaste/DDG sin errores de consola, telemetría cortada.** Medido con `FREEDOM_JS_PROFILE=2` (perfilador de muestreo ponderado por tiempo, `spec/js_sandbox.md` 7p): ~40 % de GitHub era `querySelector`/`matches` (cada candidato construía TODA la cadena de ancestros; `cch_element_matches_any` rechaza por rasgos del sujeto antes) y el resto 134 fetches secuenciales con handshake PQ nuevo + ~10 `connect()` cada uno (el `CURLSH` solo compartía cookies: ahora también conexiones y DNS, un mutex por tipo; sesiones TLS NO; la política corre sobre el `SSL*` vivo de cada respuesta). `--as-gui` llama `sf_global_init` como la GUI; `querySelectorAll` recorría el documento dos veces; heap JS 64→256 MiB; `justpaste.it` solo acepta `secp384r1` (ahora ofrecido); `block.conf` trae telemetría, analítica, anuncios y el TLD `.cyou`; el fetcher headless consulta `hb_check` como la GUI. `[[freedom-conn-reuse-qs-prefilter-tanda68-2026-10-25]]`
- **Tanda 69 (oct 25) — AJAX real: cabeceras de petición/respuesta y XHR completo. Reddit pasa de 57 px en blanco a su página real; YouTube ejecuta su bundle de 10,8 MB.** `XMLHttpRequest.setRequestHeader` era un no-op y `fetch` descartaba `headers`: ninguna página enviaba `Accept`/`Content-Type`/CSRF (el parcial de login de reddit respondía 406). Ahora el bloque cruza worker→padre, el padre lo vuelve a filtrar (`rp_sanitize_request_headers`, fuzzeado, `spec/request_headers.md`) y `secure_fetch` lo aplica; las cabeceras de respuesta (sin Set-Cookie) vuelven a `getAllResponseHeaders`/`Response.headers`; el XHR es EventTarget con ciclo de vida completo (YouTube moría en `d.addEventListener("loadend")`). El tope de fuente JS era 4 MiB y un script mayor se rechazaba **sin decir nada** (YouTube: 10,8 MB, 0 ms «evaluado»): 32 MiB y el rechazo se reporta en consola. `crypto.getRandomValues` rellenaba todo el ArrayBuffer desde `byteOffset` (escritura fuera de la vista): ahora solo la vista, enteros únicamente. `XMLSerializer` serializa fragmentos y texto. `document.getElementById` devolvía un nodo DESPRENDIDO que el índice (solo crece) aún recordaba, en vez del elemento vivo: ahora `dom_get_connected_by_id` (solo en el documento; con duplicados, orden de árbol); `dom_get_element_by_id` sigue siendo la búsqueda de handle por índice. Presupuesto de JS de host de confianza 15→60 s. `background-image` de CSS carga lazy en la ventana (`lazy_load`, `spec/lazy_load.md`; el export headless sigue completo). Herramientas de depuración: `JS_SetThrowHook` en el motor vendorizado (registro de TODA excepción, también las capturadas), pestañas **Profile** y **Throws** de Freebug (`profile()`/`throws()` en el REPL; el muestreo corre en páginas allow∩js y los globales con tiempos reales solo existen cuando el REPL los toma), `FREEDOM_JS_PRELUDE=archivo.js` (se evalúa antes que los scripts de la página, leído antes de seccomp). Validación: 83 suites, ASan/UBSan, `fuzz-rqh` 374k, `fuzz-dom`/`fuzz-js`/`fuzz-jsdom`, `parity` +0.00, `drift`/`drops` verdes. `[[freedom-ajax-headers-xhr-tanda69-2026-10-25]]`

- **Tanda 70 (oct 25) — YouTube arranca su app: `readyState` real y reacciones CE reentrantes.** `readyState` recorría solo `loading`; una inserción dentro de un `connectedCallback` se descartaba (guard booleano); y la búsqueda de custom elements usaba un selector con TODAS las definiciones (~900 en YouTube) que no resolvía, dejando `ytd-page-manager` sin actualizar (`PAGE_TOKEN` sin proveedor). Masthead real en PNG; contenido de portada y reddit siguen abiertos. `spec/js_dom.md` 7q. `[[freedom-ce-reactions-readystate-tanda70-2026-10-25]]`

- **Tanda 71 (oct 26) — sitios de `js.conf` sin errores de consola: reddit pasa su verificacion, OSM arranca, x.com muestra su landing.** `form.elements`/`submit` GET, estilos de shadow acotados (`:host`), `currentScript` real, `createHTMLDocument` desacoplado (jQuery 3 borraba el `<body>`), consultas en fragmentos. ASan + `fuzz-jsdom` limpios, `parity` +0.01. Abierto: hidratado Lit de reddit, iframes (JustPaste/TinyMCE), chrome UA de inputs con `border:0`, GitHub header. `[[freedom-shadow-scope-shadydom-trap-tanda71-2026-10-26]]`

- **Tanda 72 (oct 26) — Freebug como Firebug + dos fugas de reddit.** `this.search=` en un custom element lanzaba (los miembros URL eran getters sin setter en `HTMLElement.prototype`: `urlShadow`); nodos slotteados sin slot o bajo `display:none` se marcan `data-fzu` y no se pintan; la firma de la caché de `getComputedStyle` solo hasheaba 256 `<style>` (un `<style>` por componente la dejaba obsoleta). Freebug: módulo puro `fb_cmdline` (historial ↑/↓, Tab completa rutas por descriptores, filtro Ctrl+F) + pestañas DOM y Storage; verificado con teclas reales en weston, `fuzz-fbc` 6.6M. Abierto: tooltips Lit de reddit aún visibles, muro reCAPTCHA (tercero bloqueado), tiempos en Net, breakpoints (QuickJS-ng no expone depurador). `[[freedom-freebug-cmdline-tanda72-2026-10-26]]`

- **Tanda 73 (oct 26) — allow∩js sin doctrina de terceros + iframes con broker.** `hb_check_subresource`; `frame_broker` (`fbk_`, fuzzeado 9.5M) + `frame_host` (`fh_`, worker por frame, E2E sobre workers reales); ops de frame sobre la cola del WebSocket (kinds 5–7), byte de rol en `OP_LOAD`; shim `jt_enable_frames` (`parent`/`top`/`contentWindow`/`message`). ASan/UBSan, `drift`, `make test` limpios; mutantes muertos. Abierto: pintar el frame, cookies del frame, fases 3–6 del plan (huella, APIs, render, velocidad). `[[freedom-trusted-everything-iframes-tanda73-2026-10-26]]`

- **Tanda 74 (oct 26) — huecos de plataforma JS medidos en el barrido de consola: `classList` DOMTokenList completo, `<canvas>` heredaba de nada (sin `style`), `contentDocument` de iframe en blanco, `getRootNode` en documentos/fragmentos desprendidos.** Barrido: github/HF 0 errores. Abierto: masthead de YouTube (`#guide-button` null), pintar iframes. `[[freedom-js-platform-gaps-tanda74-2026-10-26]]`

### 7.4 Tandas de paridad 21–25

- **Tanda 21 (sep 6) — "sale del flujo" necesita ancla, y el bloque contenedor de un contenedor SIN caja era el de su primer ítem.** `[[freedom-oof-leaves-flow-anchor-2026-09-06]]`
- **Tanda 22 (sep 6) — una caja con tope y scroll recorta: el sidebar de jkanime fluía 7000 px.**
- **Tanda 23 (sep 6) — segundo eje de benchmark: `make wpt` sobre un subset WPT.** 102 reftests CSS estáticos vendorizados en `tests/wpt/` + targets `make wpt`/`wpt-update` (reusan `pngdiff` y el perfil sin-JS-sin-red de parity); reglas de viewport para páginas sub-viewport (Firefox a `--window-size=1000,H_FD`, `pngdiff` sin `scrollHeight`). Primera pasada: 64/100 PASS. Triage en `tests/wpt/README.md`; contrato en `spec/parity.md`.
- **Tanda 24 (sep 7) — holy-grail: márgenes del fundador, ancho de columna y viewport-verdad. Sonda `slashdot-cols` 13.41 → 11.03, `ddg` −0.53, `hackernews` −1.27; sonda nueva `story-chain` 8.93 (cadena artículo 1–2 px de Firefox).** `[[freedom-oof-leaves-flow-anchor-2026-09-06]]`
- **Tanda 25 (sep 7) — pull-up cross-band: el rail de slashdot por fin al lado de las historias. `slashdot` 20.70 → 15.51 (h_ratio 1.165 → 0.969), sonda `slashdot-cols` 11.03 → 8.65, TOTAL −4.30; cero regresiones en el resto.** `[[freedom-float-pullup-cross-band-2026-09-07]]`

---

## 8. Reglas para el asistente (IA)

- Aplica el ciclo completo de §3 **en orden**. No te saltes pasos ni adelantes implementación sin
  spec+test, y no documentes antes de validar y fuzzear.
- **Falla cerrado.** Ante la duda de seguridad, rechaza; nunca degrades una garantía por conveniencia.
- No introduzcas dependencias nuevas sin justificarlas por reducción de superficie de ataque, y nunca
  `liboqs`/`oqsprovider`.
- Sé honesto sobre lo no verificado: el código de red/GUI que no se pueda ejercitar aquí se marca
  como pendiente de prueba de integración / verificación visual, no como verificado.
- Verifica que cada símbolo/flag/algoritmo existe en este host antes de recomendarlo.
- Comandos nuevos van al **Makefile**, no a scripts sueltos.
- Modo **boyscout**: resolver deuda técnica y fallos de seguridad nunca está fuera de scope.
- **V-001 — `malloc(n+1)` fail-closed:** todo `malloc(len + 1)` → `memcpy(dst, src, len)` lleva
  `if (len == (size_t)-1) return NULL;` antes del `malloc`. Sin esa guarda, `len == SIZE_MAX`
  wrapea a 0 y el `memcpy` escribe `SIZE_MAX` bytes. Aplica a `dup_bytes`/`dup_n`/`host_dup` y
  análogos, y a `realloc(n * sizeof(T))` o cualquier suma/tamaño de fuente remota.
- **V-002 — `calloc` sobre `malloc` para arreglos:** asignar varios arreglos del mismo tamaño usa
  `calloc(n, sizeof(T))`, no `malloc(n * sizeof(T))`: garantiza zero-init y evita fugas por páginas
  no inicializadas, al mismo costo. Todo `memcpy` con `len` de runtime lleva verificación explícita
  de que no excede el destino.
- **V-003 — buffer encadenado:** todo acumulador cuyo tamaño no esté acotado por un límite de
  protocolo se implementa como **cadena de bloques fijos** (64 KiB), no como un buffer que crece con
  `realloc` ni con un tope duro artificial. Patrón de referencia: `ih_block`/`ih_acc`/`ih_flatten`
  en `dom.c`.
- **V-004 — `snprintf` fail-closed:** nunca `n += (size_t)snprintf(buf + n, rem, ...)` sin
  comprobar truncamiento. Patrón correcto:
  `size_t space = cap - n; if (space == 0) break; int r = snprintf(buf + n, space, ...);
  if (r < 0 || (size_t)r >= space) { n = cap; break; } n += (size_t)r;`
- **Un test rojo se verifica revirtiendo el fix.** Un binario que no relinkeó (p. ej. porque
  `-Werror` abortó el build) hace pasar el test con el código viejo: eso no es rojo.
- **Este archivo nunca debe superar ~150.000 caracteres** (`wc -c CLAUDE.md`), y el objetivo real es
  mantenerlo **bien por debajo**: un `CLAUDE.md` que crece sin límite deja de leerse. El historial de
  hitos se comprime a **una línea por hito** (título + resultado + `[[link]]`) apenas se cierra; el
  detalle vive en la memoria, en `spec/<modulo>.md` y en `git log`, nunca en prosa acumulada aquí.
  Si al documentar un hito nuevo el archivo creciera de más, comprimí lo viejo **antes**, no después.
- Roles: `AGENTS.md` modifica internos, `CORE.md` consume como dependencia. Leer solo uno por rol.
- IPC: todo campo nuevo `pv_run`/`pv_box_def` cruza `write_view`/`read_view`; correr `make drift`.
- Tunables en `include/freedom_config.h` (`FC_*`); bounds de contrato en header de modulo.
- `css_values` dueno de color/bg; `css.c` delega. Mutantes equivalentes `round_clamp` documentados (redondeo hace borde inobservable).
- Cascade split: `css_decl` (P_* slots + `css_round_clamp` unico), `css_values` (cv_), `css_gradient` (cg_), `css_box` (cb_ + grid/calc), `css_text` (ct_). `css.c` solo dispatch/cascade + wrappers. Drift gate verifica duenos.

<!-- readmenator-agent-kb-link -->
## Project Knowledge Base (MUST read before coding)

Generated offline by [ReadMenator](https://github.com/grisuno/ReadMenator) (zero-token static analysis). Humans: `KNOWLEDGE_BASE.md`.

0. Memory: `cat readmenator-agent/MEMORY.md` (business rules, workflow, constraints, style, done criteria, session log). Record new decisions with `readmenator . remember "<note>" --kind decision`.
1. Freshness: `readmenator . fresh` (exit 1 means stale: run `readmenator . --rebuild`). Without the CLI, compare `git_commit` in `readmenator-agent/MANIFEST.json` with `git log -1`.
2. Orient: `ls *.md readmenator-agent/ readmenator-wiki/`, then read `readmenator-wiki/index.md` (big picture, communities, god nodes).
3. Locate: `grep -n '<keyword>' readmenator-agent/INDEX*.md readmenator-agent/SYMBOLS*.md` before any `glob` over sources; for questions use `readmenator . ask "<question>"` (GraphRAG, `--global` for overviews).
4. Context: `cat readmenator-agent/KB_<subsystem>.md` for the subsystem you touch.
5. Before editing: `grep -n '<file>' readmenator-agent/GOTCHAS.md readmenator-agent/SECURITY.md` (blast radius, cycles, findings).

Also: `API*.md` (public functions, one line each), `ARCHITECTURE*.md` (dependency pairs), `recipes/*.md` (grounded task steps). Large docs are paged as `NAME_p2.md`, so always grep with `NAME*.md`.

    pip install readmenator && readmenator . --rebuild
<!-- /readmenator-agent-kb-link -->
