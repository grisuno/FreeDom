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
| CSS | `css` (`css_`), `css_select` (`csel_`), `css_color` (`cc_`), `interp` | Parser + cascada pura. Selectores (tipo/clase/id/grupos, 4 combinadores, atributos, pseudo-clases, `::before`/`::after`), `!important`, `@media`, `@keyframes`, custom properties + `var()`, `calc()`/`min()`/`max()`/`clamp()`, flex/grid, gradientes, sombras, filtros, transform, unidades de viewport. **Fail-closed:** `url()` de `@import`/`@font-face` descartados, topes anti-DoS, fuzzeado. Inventario completo en `spec/css.md`. |
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
- **Madurez render tanda 6 (ago 1):** `<img>`/`<svg>` en línea respetan `width`/`height` de CSS (antes tamaño natural de `viewBox` → íconos gigantes); spacer flex vacío que **crece** reserva su hueco (nav "Sign in" al extremo derecho); `RD_INPUT` dentro de una caja se sienta en su rect de contenido (input `width:100%` ya no se escapa del `<form>`). `[[freedom-replaced-css-sizing-and-flex-spacer]]`
- **Tooling & seguridad:** doctrinas V-001..V-004 (abajo). `-fvisibility=hidden` invariante. `io_uring` prohibido en worker.

### 7.4 Abierto — por valor visual medido

**Paridad de render (lo que hoy más rompe una página real):**

| # | Hito | Estado | Esfuerzo |
| :-- | :-- | :-- | :-- |
| R3 | **Tablas: ancho automático (shrink-to-fit) + `colspan`/`rowspan`** — hoy toda tabla ocupa el ancho completo y los spans se ignoran. Es la rotura visual más grande que queda. | Sin empezar | Medio-alto |
| R4 | Texto que fluye **al lado** de un `float` (hoy va debajo) | Sin empezar | Medio |
| R5 | `grid-template-rows` y `grid-row: span N` (las columnas ya están) | Sin empezar | Medio |
| R6 | `position:sticky` con scroll real | Sin empezar | Medio |
| R7 | Un elemento reemplazado (`<img>`/`<svg>`) fluye en su propia fila, no dentro de la línea. Ahora que existen las cajas de nivel inline, el mismo mecanismo debería servir. | Sin empezar | Medio |
| R10 | Una caja de nivel inline que **cruza un salto de línea** termina en el salto (no se parte en dos rects), y su rect no sigue el desplazamiento de `text-align` al pintar | Sin empezar | Bajo |
| R8 | `html{font-size:62.5%}` no cambia lo que vale `rem` (el root queda fijo en 16 px) | Sin empezar | Bajo |
| R9 | SVG en línea: gradientes/patrones (`<defs>`), `<animate>`, filtros/máscaras, y `.svg` como recurso externo de `<img src>`. El **tamaño** (`width`/`height` de CSS o atributo) ya se respeta; un SVG sin tamaño ocupa el ancho del contenedor (aspecto por `viewBox`), como Firefox sin CSS externo. | Sin empezar | Medio |
| R11 | Control de formulario: ancho CSS real + shrink-to-fit del `<button>`; el fondo de autor debe **reemplazar** el chrome por defecto (hoy `<button>` pinta el verde de autor a ancho completo **y** una caja azul por defecto encima). El inset dentro de caja ya funciona (ago 1). | Sin empezar | Medio |

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
