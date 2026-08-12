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
   archivo más allá del umbral, **primero extraé**. **Deuda conocida:** `gui/browser_ui.c` ya
   excede el umbral (>12.000 líneas) — al tocarlo, la lógica nueva (sobre todo la pura) va a un
   módulo nuevo, no a engordarlo.
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
   `fuzz-img`/`fuzz-dom`/`fuzz-svg`/`fuzz-css`; AFL++ con `make fuzz-afl`). Cero crashes/leaks/UB
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

Todos con suites CMocka + ASan/UBSan limpio (53 suites, 17 targets de fuzzing).

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
| Render | `page_view` (`pv_`), `render_doc` (`rd_`), `box_tree` (`bt_`), `flex_layout` (`fx_`), `compositor` (`cx_`) | DOM → display list → cajas (block/flex/grid) → stacking context (7 capas CSS 2.1 App E). Posicionamiento, z-index, opacity, blend, transform matricial, clipping, float. |
| CSS | `css` (`css_`), `css_length` (`cl_`), `css_select` (`csel_`), `css_color` (`cc_`), `interp` | Parser + cascada pura. Selectores (tipo/clase/id/grupos, 4 combinadores, atributos, pseudo-clases, `::before`/`::after`), `!important`, `@media`, `@keyframes`, custom properties + `var()`, `calc()`/`min()`/`max()`/`clamp()`, flex/grid, gradientes, sombras, filtros, transform, **todas** las unidades de `<length>` de CSS Values 4 por un ÚNICO resolvedor (`css_length`: px/pt/pc/cm/mm/Q/in, em/rem/ex/ch/cap/ic/lh/rlh, vw/vh/vi/vb/vmin/vmax + variantes s/l/d). **Fail-closed:** `url()` de `@import`/`@font-face` descartados, topes anti-DoS, fuzzeado. Inventario completo en `spec/css.md`. |
| Imágenes | `image_decode` (`img_`), `data_url` (`du_`) | PNG + JPEG + WebP + GIF estático **dentro del worker confinado**; topes anti-DoS; ARGB listo para Cairo. GIF con decoder LZW propio. |
| Vídeo/Audio | `media_decoder` (`md_`), `hls` | H.264/H.265 desde MPEG-TS o HLS en proceso aislado; reproducción a ritmo de PTS (`md_pacer` puro). |
| Formularios | `form` (`fm_`), `textfield` | GET/POST nativos sin JS; target no-https no representable. |
| Shaping | `text_shape` (`tsh_`) | HarfBuzz + FreeType. Ligaduras, kerning GPOS, formas contextuales. Solo lado confiable, fuzzeado. |
| Export | `pdf_export` (`pe_`), `zoom` (`zm_`), `download` (`dl_`) | PDF vectorial; zoom 50–300 %; descargas con nombre fail-closed y escritura atómica 0600. |
| Prefetch | `prefetch` (`pf_`) | Pre-scanner puro + pool de 4 hilos por el MISMO fetcher gateado. |
| DevTools | `freebug` (`fb_`), `dom_debug` (`dd_`) | Consola JS (`F12`, `--dump-console`) con nivel y `file:line:col`; `--dump-dom`/`--dump-layout`/`--dump-css`. |
| UI | `ui`/`browser` (puros) + `gui/browser_ui.c` (orquestador) | Toolbar, tabs, omnibox, scroll, menú, multi-pestaña, atajos, temas. **DEUDA:** extraer painter/chrome. |
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
- SOP por construcción: sin API de red, sin `iframe`/`window.open`/`postMessage`/`opener`. Por eso **no se implementa CORS** (sería código muerto). `[[freedom-sop-by-construction]]`
- Excepción gateada allow∩js: XHR/`fetch` reales, pero **el JS nunca toca el socket** — el worker proxya al padre, que re-aplica TODA la política. `[[freedom-parent-gated-xhr]]`
- Readback de canvas/audio por origen (eTLD+1), no por sesión: cierra el cross-origin linking. `[[freedom-anti-fp-origin-readback-key]]`
- JS apagado salvo opt-in. Con JS activo los mutadores del DOM **DETACHAN** (`lxb_dom_node_remove`, nunca `destroy`): cero UAF. `location` real y de solo lectura; la navegación la gatea el padre con `ln_resolve`. Storage/cookies/referrer efímeros o vacíos. `[[freedom-live-js]]`
- Cada `<script>` es su propio programa; un **único** presupuesto de reloj por página se reparte entre todos. `[[freedom-per-script-isolation]]`
- Doctrina trusted-host: allow∩js ⇒ CSS de autor e imágenes efectivos sin toggles. `JSP_ON` global **no** es confianza. `[[freedom-trusted-host-full-caps]]`
- Cookies de sesión EN MEMORIA para allow∩js; nunca a disco. `[[freedom-session-cookies-trusted-spa]]`

**Buscador y navegación**
- Omnibox (`url_omnibox`, puro): host desnudo ⇒ `https://`; esquema ajeno (`javascript:`/`file:`) ⇒ **búsqueda**, nunca ejecución. `[[freedom-omnibox-search]]`
- El buscador depende de la allowlist: DuckDuckGo presenta leaf RSA-2048. `[[freedom-search-needs-allowlist]]`
- SPA de buscador ⇒ endpoint no-JS por rewrite transparente en el único choke point. Google **no** se toca. `[[freedom-search-spa-noscript-rewrite]]`

**Render y presentación**
- **Toda unidad de `<length>` se resuelve en `css_length` y en ningún otro lado.** Una unidad nueva se agrega ahí y todos los consumidores la obtienen solos; una tabla de unidades privada en otro módulo es un bug, no una optimización. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **Los pseudos dinámicos los gobierna el estado, no una constante:** `:hover`/`:active`/`:focus*` matchean si y solo si su bit está en `css_element.state`. Página recién cargada = `state` 0 = ninguno matchea, como cualquier navegador con el mouse afuera. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **Ninguna cadena que no venga del CSS/HTML/JS entra al flujo de la página.** Un diagnóstico del motor (imagen bloqueada, error de fetch) va a devtools; la página muestra lo que el autor escribió — para una imagen no disponible, su `alt` (HTML §4.8.4.4) y nada más. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- Privacy by Default: imágenes y CSS de autor **apagados**; opt-in (`Ctrl+I`, `FREEDOM_IMAGES=1`). Cubre remotas **y** locales por igual.
- **Layout != estilo de autor:** la maquetación (box model UA, flex/grid, márgenes, **tamaño de elementos reemplazados**) se aplica **siempre** — es estructura, no abre sockets. Solo los **colores** siguen tras `caps.css`.
- **El CSS externo es el gate, no el motor:** con `caps.css` OFF no se descarga ningún `<link>`, así que un layout basado en clases externas (Bootstrap de jkanime, `.social svg{width}` de slashdot) NO puede coincidir aunque el motor sea correcto. Antes de "arreglar" una diferencia, comprobá si es del motor o de una regla externa no aplicada: un `<svg>`/`<img>` sin tamaño declarado ocupa el ancho del contenedor **también en Firefox**. `[[freedom-replaced-css-sizing-and-flex-spacer]]`
- Origen `file://` para páginas locales, confinado al subárbol del documento. `[[freedom-local-file-origin]]`
- `display:none` es estructural, no una sugerencia. `[[freedom-display-none-structural]]`
- `preserved_view` gana solo con `>= 2` bloques de diferencia.
- **La paridad con Firefox se MIDE, no se supone:** `firefox --headless --screenshot X.png --window-size=1000 file://...` contra `--download-png` del mismo HTML. `[[freedom-firefox-parity-batch]]`, `[[freedom-firefox-parity-2026-07-30]]`
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
- **Paridad Firefox tanda 12 (ago 10) — `@media` al ancho de render (cambio de doctrina, autorizado):** `@media (min-width/max-width)` se evaluaba contra un viewport **fijo de 1920 px** (anti-fp) mientras la página se **pinta a ~1000 px**, así que Wikipedia activaba su layout de sidebar fijado `@media(min-width:1680px)` y **apretaba todo el artículo en una columna de 248 px** (una palabra por línea, 5× el alto de Firefox). Ahora `pv_build_styled` recibe `viewport_w` (nuevo campo del códec IPC `OP_LOAD`, con `tab_set_viewport_w`): GUI usa `w->width`, headless usa `ui_render_viewport_w()` (= `PNG_PAGE_W` 1000). **Solo la query de ancho lo ve; las unidades de viewport (vw/vh) siguen contra el desktop normalizado** ⇒ ninguna geometría real se filtra a longitudes computadas. Wikipedia 37788→22888 px, artículo ancho (576 filas >700 px). TOTAL 210.59→207.51. `layout-diff` byte-idéntico, 1459 asserts + ASan/UBSan limpios. Residual: la barra `columnEnd` de Vector queda en ~15 px (sus hijos TOC son `display:none` por selector compuesto aún no aplicado) y las listas de referencias multi-columna (`column-width`) siguen en 1 columna → falta placement por `grid-template-areas`. Junto: **dimensionado de tracks intrínsecos de grid** (`min-content`/`auto` + `fr` ⇒ el track intrínseco toma su contenido, el `fr` el resto; byte-idéntico, correcto, hoy no-op en la corpus a 1920). `[[freedom-parity-container-diagnosis-2026-08-10]]`
- **Paridad Firefox tanda 13 (ago 11) — las tres constantes verticales y el pseudo-elemento que estilaba al elemento. TOTAL 207.51 → 149.95 (−28 %), sin una sola página peor:** cuatro bugs **sistémicos** (afectan toda página, no un sitio), medidos con la sonda nueva `tests/parity/pages/ua-metrics.html` (18.94 → 0.98). (1) **`line-height: normal` era 1.2× la caja natural** — `(asc+desc)` **ya es** `normal`; multiplicarla otra vez estiraba cada línea un 20 %. `line_spacing` 1.2 → **1.0** (medido: línea de 16 px = 23 px en ambos motores). −23.03 de una constante. (2) **Todo bloque de texto cobraba el margen UA de un `<p>`** — `rd_block_tag` devuelve `"p"` para todo `RD_PARAGRAPH`, así que `<div>`/`<section>`/`<td>` metían **1em fantasma antes de cada bloque**. Nuevo código `bx_ua_tag` (estructura, **nunca** gateado por `caps.css`: un margen UA es la hoja UA, no estilo de autor) que `page_view` resuelve del ancestro de bloque y cruza el códec IPC; `bx_ua_of_tag`/`bx_default_for_ua` comparten la **misma** `TAG_TABLE` (una sola fuente de verdad). Los `<p>` reales conservan su margen — eso es lo que guarda la sección B de la sonda. −10.8. (3) **El `line-height` del AUTOR se aplicaba sobre la caja natural en vez del `font-size`** (CSS 2.1 §10.8.1): dos unidades distintas, ≈1.44× de más en toda página que declara interlineado — o sea todo buscador y todo portal. El acumulador por línea pasa a **píxeles** (`line_lead_px`, calculado donde se conoce el `font-size` del fragmento). −25.32; `slashdot` `h_ratio` 1.27 → **1.04**. (4) **`::before`/`::after` estilaban el elemento originante**: solo `content` debe cruzar (CSS 2.1 §12.1). La causa raíz estaba en `css_select`: el marcador de pseudo lo produce el compuesto **subjeto**, pero `complex_matches` le cedía el slot del llamante al recorrido de ancestros **justo en el nivel del subjeto**, que lo pisaba con -1 ⇒ **solo sobrevivía en selectores de un compuesto**, y toda regla real lleva combinadores. Los pies de foto de Wikipedia salían en una columna de 15 px, 131 líneas de un carácter (131 → 0). Se descarta **antes** de reclamar el slot de cascada, o sería una pérdida silenciosa en vez de una fuga. 1412 tests + ASan/UBSan limpios, fuzz-css 53k y fuzz-pv 21k sin hallazgos. `layout-diff`: las 20 páginas se acortan 5–22 % con **cero** cambio estructural (mismo `nbox`/`nrow`/`npositioned`) → baseline re-congelado. De paso: `fuzz-pv` no compilaba desde la tanda 12 (el harness no seguía a `viewport_w`) — reparado. `[[freedom-vertical-metrics-and-pseudo-leak-2026-08-11]]`
- **Tanda 15 (ago 11) — "todo sale del CSS": una sola tabla de unidades y el fin de las reglas inventadas.** Cuatro cambios, ninguno con un px en duro, cada uno citable de una spec. (1) **`css_length` (`cl_`), el ÚNICO resolvedor de `<length>`** (CSS Values 4 §5-6): reemplaza **cinco** tablas privadas divergentes (`interp_len`, `interp_lineheight`, `interp_fontsize_ex`, `media_len_px`, `calc_factor`), cada una con su propio `16.0` enterrado y ninguna de acuerdo con las otras — `interp_len` **descartaba `pt` entero** (Hacker News está escrito en puntos), `rem` y `em` eran el mismo número, y `vmax`/`vmin` eran alias de `vw`/`vh` (solo correcto en apaisado). Ahora entran px/pt/pc/cm/mm/Q/in, em/rem/ex/ch/cap/ic/lh/rlh y vw/vh/vi/vb/vmin/vmax con variantes s/l/d. Lo que el módulo no puede saber (métricas de fuente, viewport) entra por `cl_ctx`, **no** por una constante: los fallbacks de `ex`/`ch`/`cap`/`ic` son los que nombra la spec (§6.1.1-6.1.4), y `text_shape` podrá llenar métricas reales sin tocar el módulo. El clamp `CSS_LEN_MAX` queda del lado del emisor: es política anti-DoS del box model, no propiedad de la unidad. (2) **`cl_number` — la gramática `<number>` de CSS Syntax §4.3.12** compartida por longitudes, canales de color, `opacity` y argumentos de `transform`: el parser privado exigía un dígito **antes** del punto, así que `.5` se rechazaba en los 30 sitios que lo usan. Caso medido: `padding:0 28px 0 .75em` de DuckDuckGo se caía **entera**. (3) **`:hover`/`:active`/`:focus`/`:focus-within`/`:focus-visible` dejan de matchear SIEMPRE** — cambio de doctrina autorizado. Matcheaban incondicionalmente "para revelar menús ocultos"; el efecto real era pintar cada página como si el mouse estuviera sobre **todos** los elementos a la vez. Medido en DuckDuckGo: cada snippet subrayado y azul, bordes que el autor solo pone en `:hover`, y un tooltip oculto superpuesto al texto. Una regla `:hover` **sí** viene del CSS; aplicarla siempre **no**. Ahora las gobierna `css_element.state` (bitmask `CSEL_STATE_*`, 0 por defecto = página recién cargada) — el estado es un **input del motor**, y ese campo es el punto de extensión para re-resolver bajo el puntero. (4) **El diagnóstico de imagen bloqueada sale del flujo de la página**: se pintaba una barra a todo el ancho con `"image blocked: non-https : <alt>"`, una cadena que no existe en ningún CSS, HTML ni JS, inyectada como si fuera contenido. Por HTML §4.8.4.4 una imagen no disponible renderiza su **`alt`** y nada más (`alt=""` ⇒ nada, el autor la declaró decorativa), con el color del elemento; el motivo del bloqueo sigue disponible en devtools (`--dump-dom`). **Validación:** suite CMocka verde, ASan/UBSan limpio, `fuzz-css` 54k + `fuzz-pv` 21k + `fuzz-dom` 164k sin hallazgos, y **`layout-diff` byte-idéntico en las 20 páginas** (los cambios solo tocan rutas de CSS de autor). **Honestidad sobre la medición:** `make parity` TOTAL **145.10 → 148.73**, es decir el agregado EMPEORÓ. No es una regresión de corrección sino su consecuencia: casi todo (+3.31) es `ddg-results`, que ahora aplica el padding que su autor declara y por eso envuelve más texto — y la página ya venía 1.36x más alta que Firefox por un bug **preexistente** distinto (un elemento de nivel inline, como el badge "Ad", toma una fila propia en vez de fluir dentro de la línea: R7). El baseline **no se re-congeló** a propósito: dejar el +3.63 visible es lo que mantiene esa deuda en el radar. Verificado visualmente: DuckDuckGo pasa de subrayados falsos + tooltip superpuesto + barra roja a un render casi idéntico al de Firefox en el bloque de resumen. `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`
- **Tooling & seguridad:** doctrinas V-001..V-004 (abajo). `-fvisibility=hidden` invariante. `io_uring` prohibido en worker.
- **`<select>` cerrado muestra su opción seleccionada (ago 11) — corrección, no score.** `describe_control` derivaba el `value` visible del control con `collect_text(node)`, que **aplana el `<select>` entero** ⇒ pintaba `"All Regions Argentina Australia …"` (las 200+ opciones del filtro de DuckDuckGo concatenadas) en vez de `"All Regions"`. Por HTML *Rendering* §"The select element" un control colapsado muestra **solo su opción seleccionada**: la ÚLTIMA `<option selected>` en orden de árbol, o —sin ninguna— la PRIMera opción. Se captura en el mismo walk que ya arma `select_opts` (DRY), y `selected` se detecta con `has_attribute` (booleano sin valor, `get_attribute` devuelve NULL). Nada en duro, todo del HTML. `make parity` **148.73 → 148.76** (ruido): la barra de filtros de ddg NO desapila por esto —su apilado es otro bug (float:right + `transform:scale` + posicionamiento negativo del header)— pero el control ya pinta la etiqueta correcta (verificado en PNG). `layout-diff` byte-idéntico (ningún example tiene `<select>`); 3 candados (`selected`, last-wins, default-first). Descubierto de paso: la brecha de wikipedia (figcaption estallado) es `display:table`/`table-caption` **descartado** por `interp_display` (retorna -1) → el `<figcaption>` no maqueta como caption; y el `~=` de atributo es CORRECTO (matchea token entero, no substring — confirmado). `[[freedom-select-selected-option-2026-08-11]]`
- **Paridad Firefox tanda 14 (ago 11) — el elemento raíz estaba FUERA de la herencia. TOTAL 149.95 → 145.10, `layout-diff` byte-idéntico en las 20 páginas:** cinco brechas, todas regla citable de la spec (mandato del dueño: nada en duro, nada inventado; todo sale del CSS/HTML/JS). (1) **La dominante: el walk de contexto cortaba en `if (p == base) break;` y `base` es el raíz de RENDER (`<body>`), un nivel por debajo del raíz del documento ⇒ TODA declaración `html { ... }` se descartaba en silencio** (font-size, color, font-family). Medido con una sonda de una línea: `body{font-size:200%}` aplicaba (fila h=45), `html{font-size:200%}` no (h=23); `html{color:red}` pintaba gris del tema. Como `html{font-size:90%|62.5%}` es idioma corriente, era un **multiplicador de tamaño de toda la página**: DuckDuckGo declara `html{font-size:90%}`, así que cada línea salía 1/0.9 más grande **y** envolvía antes, componiendo en alto. El fix es borrar ese `break`: sobre `<html>` solo está el nodo documento, que no es elemento, así que el loop termina igual y sigue acotado por la profundidad del DOM. **ddg-results 19.74 → 15.24.** Ojo: es distinto del rebasing de `rem` (tanda 11) — `rem_rebase` ya leía el font-size de la raíz, y por eso el bug se escondía: `rem` funcionaba mientras el texto heredado no. (2) **`min_main = 1.0` era un piso en px HARDCODEADO** en lugar del *automatic minimum size* de CSS Flexbox §4.5: con piso ~0 una línea que desborda tritura cada ítem a una astilla y el texto cae a un carácter por línea. Ahora `fx_auto_min_size(min_content, basis, author_min, scroll_container)` — puro, en `flex_layout`, con test unitario: un `min-width` de autor gana (entonces no es `auto`); un scroll container tiene mínimo automático **0** (eso es lo que hace funcionar el idioma universal `overflow:hidden`); si no, min-content acotado por el tamaño base. La medición reusa `measure_item_w_at` en el extremo angosto (el código ya documentaba que ese extremo **es** min-content) y se saltea cuando no puede cambiar la respuesta. (3) **Un hijo `position:absolute` de un contenedor flex NO es un ítem** (§4.1): se comía una porción entera y mataba de hambre a los hermanos que crecen — era el bug MEDIDO del `<h1>` de Wikipedia (1 px, "Web browser" en 10 filas verticales). Sutileza: el walk fija `oof_seen` del ancestro ACTUAL, pero el ítem de un contenedor es `prev_el`, su hijo un paso adentro ⇒ la membresía la decide `oof_below`, el estado capturado **antes** de plegar la posición de `p`; si no, un elemento que ES el contenedor deja de poseer a sus propios hijos. **Wikipedia 17296 → 13614 px.** (4) **`visibility` se HEREDA (CSS 2.1 §11.2) y oculta el TEXTO, no solo cajas decoradas**: se leía únicamente del `pv_box_def` propio, así que un `<span style=visibility:hidden>` pelado (el patrón de etiqueta para lectores de pantalla) pintaba entero, y un hijo `visibility:visible` de un padre oculto seguía oculto. Ahora se resuelve por run vía `pv_text_ext` (nearest-ancestor-wins da herencia **y** override gratis), cruza el códec IPC en el bloque A y gatea por FRAGMENTO; la regla se extrajo pura en `pv_content_hidden`. Una fila de texto solo corta en seco cuando **todos** sus fragmentos están ocultos. Correcto pero neutro en score por construcción: lo oculto sigue reservando su espacio. (5) **`flex: 1 1 0` se descartaba entero**: `expand_flex` tomaba el tercer número como un tercer factor y hacía `return 0`; per §7.1.1 el tercer componente es `<'flex-basis'>` y un cero sin unidad **es** un `<length>` válido. `interp_flex_basis` sigue rechazando un número suelto no-cero, así que `flex:1 1 10` falla cerrado sin inventar unidad. Validación: suite CMocka verde, ASan/UBSan limpio, fuzz-css 51k + fuzz-pv 20k sin hallazgos, `make clean` obligatorio dos veces (crecieron `pv_run` y `rd_block`). `[[freedom-root-inheritance-and-flex-spec-2026-08-11]]`

### 7.4 Abierto — por valor visual medido

**Paridad de render — se PRIORIZA por el score de `make parity`, no por intuición.** Última
medición (ago 11, tanda 15, `TOTAL 148.73`; ver la nota de honestidad en la tanda 15): `jkanime` 53.77, `wikipedia` 43.62, `ddg-results` 15.24,
`slashdot` 14.98, `hackernews` 12.75, `table-fit` 1.64, `float-beside` 1.23, `ua-metrics` 0.98,
`rem-62` 0.89. El término dominante del score es `h_ratio`, así que **lo que apila verticalmente
lo que debería ir al lado es siempre el bug más caro.**

**Lección de la tanda 13, vale para elegir el próximo objetivo:** los cuatro bugs más caros no
estaban en ninguna página en particular — eran **constantes y unidades del motor** que se
componen con todo lo demás. Antes de perseguir el layout de un sitio, comprobá si la brecha es
un factor uniforme: se mide en un probe de 10 líneas y suele valer más que semanas de casos.

| # | Hito | Estado | Esfuerzo |
| :-- | :-- | :-- | :-- |
| R12 | **`jkanime` (53.8) y `wikipedia` (43.6) siguen siendo las dos peores y las ÚNICAS por encima de 20 — pero la causa que se les atribuía ya NO es la vigente.** El `<h1>` de Wikipedia que recibía **1 px** era el hermano `position:absolute` comiéndose una porción de ítem flex: **resuelto en la tanda 14** (CSS Flexbox §4.1, un hijo absoluto no es ítem) ⇒ 17296 → 13614 px. Lo que queda en Wikipedia es **otra cosa, y está localizado**: el pie de foto de la `<figure>` estalla en **una fila de ancho completo por cada `<a>`** (≈500 px verticales donde Firefox pone 3 líneas dentro de un float de 260 px). **NO es un defecto general de flujo inline:** una sonda con links con fondo/borde dentro de un `<p>` y dentro de un `figcaption` de `float:right` sale **idéntica a Firefox**, así que es markup específico de Vector (probablemente `.mw-file-description`/`typeof=mw:File` volviéndose bloque) — ahí hay que empezar, no en el motor inline. Sigue faltando: placement por `grid-template-areas` (los ítems van round-robin `índice % cols`) y CSS multi-columna (`column-width:30em` cae a 1 columna). **jkanime**: `col_mae` 0.31 es el término dominante, no el alto, y **parte de su score NO es un bug del motor** — las imágenes remotas no cargan offline y Freedom fluye el texto `alt` en muchas líneas donde Firefox dibuja un placeholder chico (verificado visualmente); no gastar una tanda persiguiendo ese número. `[[freedom-root-inheritance-and-flex-spec-2026-08-11]]`, `[[freedom-parity-container-diagnosis-2026-08-10]]` | Parcial | Alto |
| R3 | **Tablas: ancho automático (shrink-to-fit).** **Hecho (ago 10):** columnas por contenido con la tabla encogiendo a la suma, y la celda ya no adopta la caja del `<body>` (que duplicaba el alto de fila). **Hecho (ago 2):** grid de N columnas en flujo plano y dentro de columnas de float. **Falta:** `colspan`/`rowspan` reales en el motor (el atributo se lee, pero una celda con `colspan` desactiva el ancho por contenido y vuelve al reparto igual), `border-collapse` real y altura de fila (38 px vs 32 px de Firefox). | Parcial | Bajo |
| R4 | **Texto que fluye al lado de un `float`. Hecho (ago 10)** vía `fx_float_insets`. **Falta:** una banda **multi-ítem** sigue empujando el contenido siguiente hacia abajo en vez de dejarlo fluir al lado, y las exclusiones se descartan (volviendo al apilado) cuando el bloque siguiente abre una caja propia — es fail-safe contra solapamiento, no paridad. | Parcial | Medio |
| R5 | `grid-template-rows` y `grid-row: span N` (las columnas ya están) | Sin empezar | Medio |
| R6 | `position:sticky` con scroll real | Sin empezar | Medio |
| R7 | Un elemento reemplazado (`<img>`/`<svg>`) fluye en su propia fila, no dentro de la línea, y **no queda acotado a su padre inline** (`<a>`/`<li>`): por eso un ícono SVG sin tamaño en una barra social llena el ancho de página en vez del `<a>` estrecho — gigante como en Firefox pero sin el contexto inline que allí lo encoge. Requiere contexto de formato inline para reemplazados. **Promovido a prioridad 1 (ago 11):** es el termino dominante medido de `ddg-results` — el badge "Ad" (nivel inline junto al titulo) toma una fila entera donde Firefox lo pone dentro de la linea, y ese patron se repite en cada resultado. Tambien es lo que amplifico el +3.31 de la tanda 15. | Sin empezar | **Alto valor** |
| R10 | Una caja de nivel inline que **cruza un salto de línea** termina en el salto (no se parte en dos rects), y su rect no sigue el desplazamiento de `text-align` al pintar | Sin empezar | Bajo |
| R8 | **`html{font-size:62.5%}` rebasa `rem`. Hecho (ago 10).** Resto: `em` sigue aproximado a ×16 en vez del tamaño computado del padre, y la raíz se lee como porcentaje entero (`62.5%` → 63 % → 10.08 px, ≤0.5 %). | Hecho | — |
| R9 | SVG en línea: gradientes/patrones (`<defs>`), `<animate>`, filtros/máscaras, y `.svg` como recurso externo de `<img src>`. **Ya hecho (ago 1):** `width`/`height` de CSS/atributo con derivación por aspecto del `viewBox`; `fill` de CSS colorea figuras sin fill propio (`sv_parse_ex`). Un SVG sin tamaño llena el contenedor (como Firefox). | Parcial | Medio |
| R11 | Control de formulario: ancho CSS real + shrink-to-fit del `<button>`; el fondo de autor debe **reemplazar** el chrome por defecto (hoy `<button>` pinta el verde de autor a ancho completo **y** una caja azul por defecto encima). El inset dentro de caja funciona (ago 1); un `<input>` como ítem flex reserva `UI_INPUT_MEASURE_W` px de base (ago 1). | Parcial | Medio |

**Deuda estructural:** extraer painter y chrome de `gui/browser_ui.c` a `src/painter.c` y
`src/chrome.c` (§3 cláusula anti-monolito). Cerrar la animación `@keyframes` (ya parseado y
almacenado; falta cablear `frame_clock` → pintado).

**Plataforma:** HTTP/2 y HTTP/3 (QUIC, helper aislado, solo lado confiable), WebSockets
(`TAG_WS_*` con el patrón de `TAG_SUBREQ`, gateado por `webcaps.net`), fetch concurrente
multipestaña, IndexedDB sobre `local_store`, Web Crypto real, `arrayBuffer` binario, Wasm en
proceso helper (intérprete, sin JIT), Service Workers solo caché, Freebug 2.0 (Network/Elements),
user scripts zero-trust, buscar en página, gestor de contraseñas, sincro E2EE por Tor, passphrase
maestra, back-stack persistente, `pledge`/`unveil` (OpenBSD), scroll suave, `defer`/`async`,
import/export de marcadores.

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
