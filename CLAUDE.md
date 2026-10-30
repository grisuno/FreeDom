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
- **Enmienda 2026-10-26 (dueño): allow∩js recibe TODO, terceros incluidos.** Una página cuyo host está en `allow.conf` Y `js.conf` carga JS, CSS, fuentes, XHR y WebSocket de cualquier host: `hb_check_subresource(…, page_trusted)` pasa por encima de la lista negra (los demás hosts la conservan). Se mantiene lo que no es política de permisos sino el sandbox: el worker no toca sockets, VERIFYPEER, realm. **iframes vivos y `postMessage` cross-window** para esas páginas: cada iframe es su PROPIO worker confinado y el padre media (`frame_broker` puro + `frame_host`; JS por JSON como dato, origen del emisor fijado por el padre). El frame se pinta desde la tanda 75 (instantánea por generación; hidden respeta `display:none`/tamaño: reCAPTCHA v3/BotGuard, Stripe). `spec/frame_broker.md`. `[[freedom-trusted-everything-iframes-tanda73-2026-10-26]]`
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
- **Todo se mide en la GUI real, no en el headless.** Paridad y velocidad se juzgan con `make fbench` (Xvfb+weston, `GUITIME_STDERR`, `--as-gui` como espejo) contra Firefox y contra los sitios de `allow.conf`/`js.conf`, que SON el corpus de benchmark: si un sitio necesita un CDN para verse bien, el dominio se añade a esas listas. El headless (`--download-png`, `make parity`) es diagnóstico y CI; una mejora que no se ve en la GUI no cuenta. `[[freedom-gui-timing-tanda65-2026-10-24]]`
- **`make clean` es obligatorio cuando crece una struct compartida** (`css_style`, `pv_run`, `pv_box_def`): el Makefile no rastrea dependencias de headers. Igual tras `make asan`.
- **`-fvisibility=hidden` es invariante de build (no quitar):** sin él, `hb_free` del ejecutable secuestra el alocador de HarfBuzz. Vive en `HARDEN` **y** en el `CFLAGS` de `asan`. `[[freedom-harfbuzz-shaping]]`
- Modo boyscout con memoria: ante una regresión, diff contra el commit inicial antes de tocar nada. `[[freedom-security-modules-butchered-by-fix-commits]]`

### 7.3 Hitos cerrados (una línea por hito)

> Comprimido 2026-07-17, 07-31 y 2026-10-29. El detalle vive en `git log`, `spec/` y la memoria.

- **Fundación (hitos 6–30, jul):** GUI interactiva, red/TLS PQ híbrido, `hostblock`, Tor/I2P, multi-pestaña, fetch asíncrono, PDF, XHR/fetch gateados, scripts externos, namespaces + seccomp W^X + fork+exec, identidad anti-fp, omnibox, CSS de autor/`@media`/flex/grid/`var()`/`calc()`, HarfBuzz, JS vivo, perfil cifrado, zoom/descargas, doctrina trusted-host, prefetch paralelo.
- **Compositor y media (jul 19):** `compositor` puro (z-index, opacity, blend, transform afín), `data_url`, `srcset`, `background-image`, pacing de vídeo por PTS (`md_pacer`), unidades de viewport, `backdrop-filter`. `[[freedom-compositor-foundation]]` `[[freedom-video-pacing-v2]]` `[[freedom-visual-impact-batch]]`
- **Paridad Firefox, tandas 1–20 (jul–ago):** el arnés `make parity` es la función objetivo; márgenes colapsables, escala de encabezados, `rem`/`em`/`%` como tipos, float/clear, tablas, flex/grid anidados, `::before/::after`, pseudos por estado, `@media` al ancho de render, herencia desde `<html>`, y descubrir que el arnés medía la POLÍTICA (JS/red) y no el layout. TOTAL 301→110. `[[freedom-firefox-parity-batch-2026-08-10]]` `[[freedom-vertical-metrics-and-pseudo-leak-2026-08-11]]` `[[freedom-length-percentage-multicol-inline-replaced-2026-08-12]]` `[[freedom-font-relative-lengths-2026-08-13]]` `[[freedom-margin-collapse-heading-scale-grid-areas-2026-08-14]]` `[[freedom-parity-harness-and-parser-drops-2026-08-15]]`
- **Paridad 21–25 (sep):** sale-del-flujo con ancla, caja con tope y scroll, subset WPT (`make wpt`), holy-grail, pull-up cross-band (slashdot 20.7→15.5). `[[freedom-oof-leaves-flow-anchor-2026-09-06]]` `[[freedom-float-pullup-cross-band-2026-09-07]]`
- **Tandas 26–31 (sep):** `make drops` como gate, listas de `transform`/`<angle>`/3D, whitespace inline en tablas, `<img>` sin `src`, `content` con escapes (icon fonts).
- **Sitios allow∩js (sep 29–oct 2, tandas 32–41):** lobste.rs 42→1.4, CSS de design systems (GitHub/HF) que se perdía, custom properties por elemento, eventos con captura/burbuja, geometría real, `history`, `window.open`, WebSocket y `localStorage` en RAM, módulos ES. `[[freedom-allowlist-sites-lobsters-2026-09-29]]` `[[freedom-design-system-css-2026-09-29]]` `[[freedom-firefox-for-trusted-plan-2026-09-30]]` `[[freedom-allowlist-sites-tanda40-2026-10-01]]`
- **Tandas 42–54 (oct 15–21):** corpus de sitios del allowlist (280→197→119), velocidad de reglas/fuentes, caja inline y leading, apilado posicionado, tabla en grid, UNA fuente de verdad GUI=headless=`--as-gui`, Slashdot en la GUI real, `clip-path`. `[[freedom-allowlist-corpus-tanda42-2026-10-15]]` `[[freedom-speed-fonts-controls-tanda43-2026-10-16]]` `[[freedom-allowlist-tanda44-2026-10-17]]` `[[freedom-tanda45-br-bfc-pools-2026-10-17]]` `[[freedom-inline-box-leading-harness-tanda46-2026-10-18]]` `[[freedom-positioned-stacking-fbench-tanda47-2026-10-18]]` `[[freedom-table-in-grid-tanda48-2026-10-19]]` `[[freedom-heading-link-oof-veto-minsize-tanda49-2026-10-20]]` `[[freedom-single-source-of-truth-tanda50-2026-10-20]]` `[[freedom-live-sites-github-glow-slashdot-header-tanda51-2026-10-20]]` `[[freedom-slashdot-gui-clip-path-tanda54-2026-10-21]]`
- **Plataforma JS (tandas 55–59, 62, 66, 71, 74):** `IntersectionObserver`/`ResizeObserver`/`MutationObserver` reales, `getComputedStyle` real, `rules()` de Freebug, errores/`unhandledrejection`, márgenes negativos con signo, `loading=lazy`, barridos de consola. `[[freedom-intersection-observer-tanda55-2026-10-23]]` `[[freedom-computed-style-gap-margin-tanda57-58-2026-10-23]]` `[[freedom-platform-surface-rules-tanda59-2026-10-23]]` `[[freedom-js-errors-negative-margins-tanda62-2026-10-24]]` `[[freedom-js-console-sweep-tanda66-2026-10-24]]` `[[freedom-shadow-scope-shadydom-trap-tanda71-2026-10-26]]` `[[freedom-js-platform-gaps-tanda74-2026-10-26]]`
- **Identidad e `indexedDB` (tandas 60–61):** `about:config` con módulo puro `identity`, `indexedDB` en RAM, recorte al padding-box, `background-clip`, `mask:url()` oculta el elemento. `[[freedom-identity-config-tanda60-2026-10-23]]` `[[freedom-indexeddb-overflow-bgclip-mask-tanda61-2026-10-24]]`
- **Caché y red (tandas 63–64, 68–69, 76):** `pq_seal` ML-KEM-512 híbrido, `http_cache` con nombres HMAC, memoria de 301/308, conexiones/DNS compartidos, XHR completo con cabeceras filtradas (`rp_sanitize_request_headers`), XHR/fetch asíncronos en paralelo (`subreq_batch`). `[[freedom-http-cache-pqseal-tanda63-2026-10-24]]` `[[freedom-conn-reuse-qs-prefilter-tanda68-2026-10-25]]` `[[freedom-ajax-headers-xhr-tanda69-2026-10-25]]` `[[freedom-async-subreq-shady-slots-tanda76-2026-10-28]]`
- **Freebug (tandas 67, 72):** pestañas Console/HTML/CSS/Script/Net/DOM/Storage/Profile/Throws, `fb_panes`, `fb_cmdline`, `--dump-pane`; pila JS 180→2000+ niveles (GitLab 13.4→2.7). `[[freedom-freebug-tabs-gitlab-stack-tanda67-2026-10-25]]` `[[freedom-freebug-cmdline-tanda72-2026-10-26]]`
- **Iframes y custom elements (tandas 70, 73, 75):** allow∩js recibe terceros; iframe = worker propio mediado por `frame_broker`, pintado en la GUI real; reacciones CE reentrantes. `[[freedom-ce-reactions-readystate-tanda70-2026-10-25]]` `[[freedom-trusted-everything-iframes-tanda73-2026-10-26]]` `[[freedom-fragment-proto-yield-tanda75-2026-10-27]]`
- **Velocidad medida en la GUI real (tandas 65, 77, 78):** `make fbench`, doble buffer SHM, selectores compactos, `tab_prewarm`, IPC en lotes (46 000 syscalls→700), `cch_path`; Wikipedia 539→193 ms, GitHub 1473→463. `[[freedom-gui-timing-tanda65-2026-10-24]]` `[[freedom-speed-compact-selectors-prewarm-tanda77-2026-10-28]]` `[[freedom-speed-ipc-batching-cascade-path-tanda78-2026-10-28]]`
- **Tanda 79 (oct 29) — `width`/`height` declarados ganan a los insets y `height:%` bajo padre `aspect-ratio`. `parity` 93.34 → 87.28, ninguna página peor.** `[[freedom-oof-declared-width-aspect-pct-height-tanda79-2026-10-29]]`
- **Tanda 80 (oct 29) — propiedades CSS que faltaban, medidas en `make drops`: alias legacy `grid-*-gap` (~1400 descartes), `P_INERT` (válidas sin efecto estático), `translate`/`scale`/`rotate` individuales, `object-position` de punta a punta (PNG verificado), CSS-wide en `<time>`/`<easing>`/`<color>`, y `grid-auto-flow: column` que el layout NUNCA leía (`fx_grid_column_count` puro; sonda `grid-auto-flow-col` 0.00 = Firefox). `parity` 93.34 → 87.24, ninguna página peor; ASan/UBSan, `fuzz-css` 159k, `fuzz-pv`, `drift`, `drops` verdes. Boy scout: `configure`/`install.sh`/CI hacían un `sed` NO idempotente que anteponía un parche a `src/local_store.c` en cada corrida (82 copias): shim una vez en el fuente.** `[[freedom-css-gaps-inert-objpos-tanda80-2026-10-29]]`
- **Tanda 81 (oct 30) — contadores CSS y encabezados en línea. Módulo puro `css_counter` (`cnt_`, `spec/css_counter.md`, `fuzz-cnt` 3,3M): `counter-reset`/`counter-increment`/`counter()`/`counters()` con alcance de CSS 2.1 §12.4 resuelto en un pre-pase de `page_view` en orden de documento (solo si la hoja los usa; reescribe `content_*` en la caché de estilos, así los 6 puntos de emisión no cambian).** Dos bugs preexistentes hallados al verlo en PNG: (1) toda ejecución `RD_HEADING` era "standalone" aunque continuara la línea, así que `<h2>A<b>B</b></h2>` salía en dos filas con el margen doble (ahora solo abre bloque con `block_break`; "Powerful data on every IP" de ipinfo = Firefox, aunque su score sube +0.8 por otros déficits: el score no premia la corrección); (2) el texto generado de `::before`/`::after` se añadía con `heading=0` (otra fuente que el encabezado). Sonda `css-counters` 0.30, 3 tests rojo→verde en `test_page_view`, `parity` baseline 88.23 (+2 sondas nuevas), ASan/UBSan, `fuzz-css`/`fuzz-pv`, `drift`, `drops` verdes. `[[freedom-css-counters-heading-line-tanda81-2026-10-30]]`
- **Tanda 82 (oct 30) — auto-allow de CDN y formularios nativos. Doctrina del dueño: si está en allow, es allow (el usuario manda).** Tres casillas en `about:config` (CSS / JS / recursos): los hosts de terceros que pide una página de `allow.conf` se añaden a `allow.conf` (cola con mutex desde los hilos del pool, commit en el hilo de la GUI; `block.conf` sigue mandando; `he_cdn_kind` puro, `fuzz-idn` 1,5M). Verificado en la ventana real con Wikipedia (`thumb.wikimedia.org` apareció en `allow.conf`). Al hacerlo salieron tres brechas de HTML: `checked` (atributo booleano) nunca se detectaba (`has_attribute`), las casillas/radios no se alternaban al clic, y el envío las ignoraba; ahora estado vivo, radio exclusivo por grupo y envío del valor (verificado con xdotool en weston). Refactor: `list_append_host`/`reload_host_list` compartidos con el menú. También `text-underline-offset` de punta a punta (sonda `underline-offset` 0.33 = Firefox; `TAB_WIRE_A_N` 40). `[[freedom-auto-allow-cdn-checkbox-forms-tanda82-2026-10-30]]`

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
- **Una feature no está cerrada hasta que se ve o se usa en la GUI.** Un módulo, shim o API que pasa
  tests/ASan/fuzz pero no llega al navegador (pintado, evento, entrada real) es trabajo **a medias**:
  no se marca «cerrado», «validado» ni «hecho», ni en el resumen ni en CLAUDE.md. El criterio de
  cierre es el **píxel o la interacción**: PNG headless (`/visual-review`) y, si toca la ventana,
  Xvfb+weston, comparado con Firefox. Un error de consola que desaparece **no** es progreso de render
  (medido: PNG idéntico byte a byte). Lo que falte por cablear se declara «abierto» con su causa, y
  se cablea en la **misma sesión**, no se difiere a la siguiente.
- **Mide en la GUI, no en el headless:** el criterio de cierre de paridad y de velocidad es `make fbench`/ventana real contra Firefox; `allow.conf`/`js.conf` son el corpus de benchmark y los CDN necesarios se agregan a esas listas (§7.2).
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
