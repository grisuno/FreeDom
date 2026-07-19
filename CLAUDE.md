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
3. **Privacy by Default** — Bloqueo total de terceros a nivel del motor de red. Sin telemetría, tecnicas anti tracing o anti rastreo
   ni siquiera "anónima" u "opt-out". Integración opcional con Tor/I2P a nivel de socket.
4. **Secure by Default** — La configuración insegura **no debe ser representable** en la API.
   El camino por defecto es siempre el seguro. Fallar cerrado: si una garantía no se puede
   verificar, se rechaza la operación.
5. **Post-Quantum by Default** — TLS 1.3 es el mínimo absoluto. El intercambio de claves es
   **híbrido** (clásico + ML-KEM) para neutralizar *Harvest-Now, Decrypt-Later*. Nunca PQ puro
   (si ML-KEM cae, el componente clásico debe resistir); nunca clásico puro.
6. **Agent-Safe & Agent-Friendly** — El navegador es seguro para el usuario **y** para el agente
   de IA que lo opere, en ambas direcciones: el contenido remoto es hostil también para el agente
   (inyección de prompts), así que se le entrega siempre como **dato con procedencia, nunca como
   instrucción**, y sin acción implícita; y el navegador es manejable por un agente (salidas
   deterministas, estructuradas, con códigos de estado, sin estado oculto, *headless*). El agente
   opera dentro de los mismos sandboxes que el usuario. Contrato completo en
   `spec/agent-safety.md`.

**Doctrina anti-vigilancia:** no se permite ninguna cadena de texto, dependencia,
endpoint ni comentario que apunte a servicios de terceros no esenciales. Cada dependencia debe
justificarse por reducción de superficie de ataque, no por conveniencia.

---

## 2. Restricciones de lenguaje y estilo

- **Solo C puro (C11).** Nada de C++, Rust ni dependencias ocultas. El header rechaza C++ con
  `#error`.
- **Identificadores y strings en inglés.** La documentación (`spec/`, este archivo) puede estar
  en español; el código, no.
- Sin emojis en el código. Comentarios solo cuando explican un *porqué* no evidente; nada de
  ruido. Los headers llevan documentación de contrato.
- Nombres con prefijo de módulo (`sf_` para `secure_fetch`, etc.). Sin estado global mutable;
  todo reentrante. Cada asignación tiene un único dueño y un único liberador idempotente.

---

## 3. Metodología: SDD + TDD estricto + BDD Given-When-Then

Para cada módulo, el ciclo es inviolable y **en este orden** orientado boy scout extintor de deuda tecnica:

1. **Spec** — `spec/<modulo>.md`: entradas, salidas, tabla de errores, garantías de seguridad,
   y qué queda fuera de alcance. Usando Dado-Cuando-Entonces o BDD
2. **Test (rojo)** — `tests/test_<modulo>.c` con CMocka. Debe **fallar** porque no hay
   implementación todavía. usando ATDD (Acceptance Test-Driven Development - Desarrollo Orientado a Pruebas de Aceptación):
3. **Code (verde)** — `src/<modulo>.c` con el código mínimo para pasar. La I/O del **lado
   confiable** (orquestador / event loop, el que NO toca contenido hostil) debe ser **asíncrona** —
   `io_uring` cuando aplique — de modo que no bloquee la UI ni el hilo. **Excepción de seguridad
   inquebrantable:** `io_uring` está **PROHIBIDO dentro del worker confinado** (`tab`/`renderer`),
   porque es una **primitiva de bypass de seccomp** (sus `IORING_OP_*` no atraviesan el syscall entry
   que filtra el BPF → un ring anularía el allowlist, W^X y netns). El worker hace I/O **bloqueante**
   sobre los dos pipes ya abiertos y punto. La regla "usar io_uring" jamás se aplica donde corre
   contenido remoto. Ver `spec/os_sandbox.md` §13 y `[[freedom-io-uring-forbidden-in-worker]]`.
4. **Refactor** — endurecer punteros, límites, legibilidad, sin romper pruebas. si vez codigo duplicado lo unificas esto es imperativo busca codigo dduplicado y extinguelo sin perder funcionalidad, nunca esta fuera de scope, modo boy scout si ves deuda tecnica la extingues sin romper funcionalidades, lo mismo con las fallas de seguridad o vulnerabilidades la extincion de estas nunca esta fuera de scope, si puedes hacer lo mismo que haces en 40 lineas de codigo lo puedes hacer en 10 o 1 bienvenido siempre y cuando respete el dry solid y no pierda funcionalidad ni agregue mas deuda tecnica.
   **Cláusula anti-monolito (parte del modo boy-scout, nunca fuera de scope):** ningún
   archivo debe convertirse en un monolito. Si un archivo **roza las ~2000 líneas**, se
   **parte según contratos** (un módulo = un contrato `spec/<modulo>.md` + `include/<modulo>.h`
   + `src/<modulo>.c`), extrayendo unidades coherentes a módulos nuevos con su prefijo, sin
   perder funcionalidad ni añadir deuda. Aplica especialmente al añadir código: si tu cambio
   empujaría un archivo más allá del umbral, primero extrae. **Deuda conocida:**
   `gui/browser_ui.c` ya excede el umbral (>5000 líneas) — al tocarlo, la lógica nueva
   (especialmente lógica pura) va a un módulo nuevo, no a engordarlo más.
5. **Validación** — `make asan` (ASan+UBSan) limpio, `valgrind`, `cppcheck`. como parte de la
   validacion quiero que utilices ya sea urls y archivos html para revisar el comportamiento de la
   GUI al renderizar. La GUI necesita Wayland (no siempre disponible para un agente), así que el
   render se inspecciona **headless** exportando la página a **PNG** (método nativo "Save as PNG",
   flag `--download-png=PATH`) y leyendo la imagen directamente. **Preferí PNG sobre PDF:** un PNG es
   una sola imagen que se lee en **un paso** y cuesta muchos menos tokens; el PDF (`--download-pdf`)
   queda para cuando se necesita el documento vectorial real (texto seleccionable, paginación), y aún
   requiere rasterizar con `mutool`. Es la **skill `/visual-review`**
   (`.claude/skills/visual-review/SKILL.md`). ## Pasos
  a. Exporta a PNG: `./build/freedom --download-png=$SP/frame.png <URL-o-archivo.html>` (`$SP` = el
     scratchpad de la sesión; no `/tmp` ni el árbol del repo). Un solo bitmap de toda la página
     (1000px de ancho; alto = contenido, acotado a 30000px). Añadí `--author-css` para revisar CSS de
     autor (colores/cajas), `--images` para **decodificar y pintar las imágenes reales** (locales de
     disco / remotas bajo política, vía el worker confinado — antes el export siempre dibujaba
     placeholders), `--js=on` para JS, `--tor`/`--i2p`/`--insecure` según haga falta.
  b. Lee la imagen con la herramienta Read: `Read $SP/frame.png`. (Fallback PDF: `--download-pdf` +
     `mutool draw -r 96 -o $SP/frame-%d.png $SP/frame.pdf`, o `Read` del PDF con `pages`.)
  c. Verifica:
    - ¿Se renderiza texto legible?
    - ¿Los elementos tienen posicionamiento correcto (no superpuestos)?
    - ¿Los colores/temas (sepia/oscuro) se aplican? (la exportación fuerza tema claro para imprimir
      oscuro-sobre-blanco; imágenes y colores de autor están OFF por defecto → placeholders; con
      `--images`/`--author-css` se decodifican/pintan de verdad.)
    - ¿Hay artefactos de rendering?
  d. Compara con screenshot de referencia si existe

   **Verificación visual de Freebug (la consola de devtools) — parte del contrato.** El render de
   página se revisa headless con `--download-pdf`, pero **Freebug es una ventana Wayland aparte**
   (segundo `xdg_toplevel`): su panel de log, los colores por nivel y la **ubicación `file:line:col`**
   de cada error **no** salen en el PDF. Por eso **todo cambio que toque Freebug** (captura de consola,
   ubicación de errores, REPL, colores, layout del panel) se verifica **en pantalla** con el flujo
   weston-sobre-Xvfb (el único modo agent-verificable aquí, sin GPU ni Wayland real):
  i.   `Xvfb :99` + `weston --backend=x11 --renderer=pixman` (NO `--renderer=noop`, da pantalla en
       blanco; NO `weston-screenshooter`, está gateado). `XDG_RUNTIME_DIR` **corto** (p. ej.
       `/tmp/wlfb`): la ruta del socket AF_UNIX no puede pasar 108 bytes, y el scratchpad de sesión
       la excede.
  ii.  Arranca Freedom con la afordancia de env **`FREEDOM_FREEBUG=1`** (abre Freebug al inicio, como
       auto-open-devtools) sobre `WAYLAND_DISPLAY` de weston, con `--js=on` y una página que produzca
       entradas (p. ej. un HTML con `console.*` y un `<script>` que lance en su 2ª línea). No hay
       `wtype`/`ydotool`, así que el *keypress* F12/`Ctrl+Enter` no se inyecta: la afordancia de env
       ejercita la apertura, y el REPL queda cubierto por `tab_eval`/`--dump-console`.
  iii. Captura: `DISPLAY=:99 import -window root $SP/freebug.png` (ImageMagick; raíz X = salida de
       weston, ambos toplevels visibles).
  iv.  `Read $SP/freebug.png` y verifica: el panel de log; **niveles coloreados** (log gris, info cian,
       warn amarillo, error rojo); y que cada error muestre su **`file:line:col` en tono atenuado**
       antes del mensaje (p. ej. `inline #2:3:1`), mientras un `console.log` no lleva ubicación.
   Validación cruzada sin GUI: `./build/freedom --js=on --dump-console <URL|archivo>` imprime la misma
   consola con `[nivel] file:line:col  texto` (ver `[[freedom-freebug-console]]`,
   `[[freedom-gui-visual-verification-weston]]`).

6. **Fuzzing** — el path que toca contenido remoto se fuzzea (libFuzzer: `make fuzz`/`fuzz-pv`/
   `fuzz-js`/`fuzz-img`; AFL++: `make fuzz-afl`). Cero crashes/leaks/UB antes de cerrar.
7. **Documentación** — **recién después de validar y fuzzear** se documenta: se actualiza la spec,
   este `CLAUDE.md` (hito → cerrado, doctrina nueva) y la memoria. Documentar antes de validar es
   documentar lo que todavía no es verdad. y casi mas importante actualizar docs/index.html ya que es el "home page" poner todos los atajos, etc. y el README.md

**No escribas la implementación antes que la spec y el test.** No avances de hito sin que el
anterior esté verde, validado y fuzzeado.

**Diseño orientado a prueba:** la lógica de seguridad va en **funciones puras sin I/O** (la
superficie verificable directamente); los orquestadores con red/SO solo cablean y llaman a esas
funciones puras sobre el estado real.

---

## 4. Stack tecnológico (decisiones vigentes)

| Módulo | Biblioteca | Nota |
| :-- | :-- | :-- |
| Red & TLS | `libcurl` + **OpenSSL 3.5+ nativo** | **No usar `liboqs`/`oqsprovider`.** OpenSSL 3.5+ trae `X25519MLKEM768`, `ML-DSA`, `SLH-DSA` en el `default` provider. Una dependencia menos que auditar. |
| Parser HTML/CSS | `Lexbor` | C puro, superficie de ataque mínima. Sin ejecución de scripts inline por defecto. |
| Motor JS | `QuickJS` / `MuJS` | C puro, sandboxed. Bridge C que expone **solo** APIs validadas. Sin `XHR` a terceros, sin WebRTC, sin WebGL, sin acceso a FS. |
| UI/Gráficos | `Cairo` + **Wayland** (nunca X11) | X11 permite keylogging entre ventanas. |
| Shaping de texto | **HarfBuzz** + FreeType + fontconfig (Hito 25) | C, lado confiable. Da ligaduras, kerning GPOS y formas contextuales (scripts complejos). Dependencia autorizada por el dueño: **solo** maqueta texto (hostil pero saneado, fuzzeado) con **fuentes locales**; **nunca** entra al worker confinado ni a la red. Ver `[[freedom-harfbuzz-shaping]]`. |
| Pruebas | `CMocka` | TDD. Instalar con `sudo apt install libcmocka-dev`. |
| Memoria | asignador endurecido / `mimalloc` | Mitigar UAF y overflows; canaries y hardening. |

> Verificación de capacidad PQC en este host:
> `openssl list -tls-groups | grep -i mlkem` debe mostrar `X25519MLKEM768`.

### Política criptográfica concreta
- **KEM por defecto:** `X25519MLKEM768` (híbrido).
- **Firmas (cuando estén en la cadena):** `ML-DSA-65`; alternativa basada en hash `SLH-DSA`.
- **Rechazos por defecto:** TLS < 1.3, KE no híbrido, **leaf (end-entity) con RSA < 3072**,
  y cualquier cert de la cadena firmado con SHA-1. El umbral RSA aplica solo al cert del sitio,
  no a los intermedios de CA (RSA 2048 universal en la Web PKI pública de 2026); SHA-1 es fatal
  en cualquier posición. Ver `spec/secure_fetch.md` §3.
- **Soberanía del usuario (la allowlist no es dictadura):** un host **explícitamente** en
  `allow.conf` se navega bajo `SF_POLICY_ALLOWLISTED_INSECURE` si el intento estricto falla:
  acepta **TLS 1.2** (mínimo; 1.3 sigue preferido), KE clásico y cert débil-pero-válido. La
  **autenticidad de la cadena se mantiene** (VERIFYPEER sigue activo): se relaja la fuerza
  criptográfica, nunca la autenticidad — llegás al sitio real sobre cripto vieja, no a un
  impostor. Por debajo de TLS 1.2 sigue rechazado. Es opt-in, por host, con aviso (toast).
- **Política por niveles** (ver `spec/secure_fetch.md`): `SF_POLICY_PQ_HYBRID_KE` (por defecto;
  exige KE híbrido, acepta certs clásicos válidos porque la Web PKI pública aún no tiene certs
  PQ en 2026), `SF_POLICY_STRICT_PQ` (opt-in; exige además firma PQ en la cadena),
  `SF_POLICY_ALLOW_CLASSICAL_KE` (fallback de navegabilidad PQ) y `SF_POLICY_ALLOWLISTED_INSECURE`
  (override por host de la allowlist; ver arriba).
- **Estado local (Zero Knowledge):** caché/marcadores/credenciales cifrados con AES-256-GCM o
  ChaCha20-Poly1305; clave derivada con **Argon2id** y sal única por dispositivo.

---

## 5. Compilación, hardening y auditoría

`make` aplica por defecto (ver `Makefile`):

```
-std=c11 -Wall -Wextra -Werror -Wshadow -Wpointer-arith -Wvla -Wwrite-strings
-fstack-protector-strong -fstack-clash-protection -fcf-protection=full
-D_FORTIFY_SOURCE=3 -fPIE -O2
-pie -Wl,-z,relro,-z,now,-z,noexecstack
```

Targets:
- `make` / `make all` — compila `src/` (no requiere CMocka).
- `make test` — compila y ejecuta la suite CMocka. Hasta que exista la implementación de un
  módulo, **enlaza con fallo a propósito** (estado rojo de TDD).
- `make asan` — la misma suite bajo AddressSanitizer + UBSan.
- `make fuzz` / `fuzz-pv` / `fuzz-js` / `fuzz-img` / `fuzz-dom` — libFuzzer (parser HTML / display
  list `page_view` / sandbox JS / decoder PNG / selectores `querySelector` sobre DOM real).
  `make fuzz-afl` — AFL++ sobre el binario headless.
- `make clean`.

**El Makefile es la única fuente de verdad de los comandos.** Los scripts `*.sh` que duplicaban
la compilación (y por eso se desincronizaban: `fuzz.sh` quedó obsoleto y dejó de compilar) ahora son
**wrappers delgados** que delegan a un target: `fuzz.sh`→`fuzz-afl`, `build_deb.sh`→`deb`,
`docker_run.sh`→`docker`, `run_freedom.sh`→`run`. Targets de desarrollo/empaquetado centralizados:
- `make deps` — dependencias del sistema + Lexbor desde fuente (subconjunto seguro de `install.sh`;
  **sin** los `sed` que mutan fuentes: un target jamás reescribe código versionado).
  **Video playback requires FFmpeg dev libraries:** `sudo apt install libavformat-dev libavcodec-dev libavutil-dev libswscale-dev`.
- `make run [URL=...]` — corre la GUI.
- `make deb` — construye el `.deb` y **restaura el dueño de `build/`** (`debuild` corre bajo
  fakeroot/sudo y lo deja root; el target hace `chown -R $(id -u):$(id -g) build`, si no `make`
  posterior falla por permisos).
- `make docker` — build + run de la imagen Zero-Trust (el entrypoint del contenedor sigue en
  `docker-entrypoint.sh`, que corre dentro de la imagen, no es comando de host).

Si agregás una fuente nueva a la compilación, queda parametrizada en el Makefile y todos los targets
(incluido `fuzz-afl`, que reusa el target `freedom` con `CC=afl-clang-fast`) la toman solos.

Todo PR debe pasar `make test` y `make asan` limpios antes de integrarse.

---

## 6. Estructura del repositorio

```
freedom/
├── CLAUDE.md              # este archivo
├── Makefile               # build endurecido + targets test/asan
├── include/<modulo>.h     # contratos públicos
├── src/<modulo>.c         # implementaciones
├── spec/<modulo>.md       # especificaciones SDD
└── tests/test_<modulo>.c  # suites CMocka (TDD)
```

---

## 7. Hoja de ruta por hitos

> **Convención de estado:** *cerrado* = spec + test verde + ASan/UBSan limpio (y, donde
> aplique, fuzzing y prueba de integración de red real). Lo que solo compila pero no se pudo
> ejercitar aquí (GUI Wayland, red real) se marca **sin verificar visualmente / pendiente de
> itest**, nunca como verificado.

### 7.1 Estado actual (cerrado) — núcleo seguro de extremo a extremo

El pipeline va de la red a la pantalla sin confiar en el contenido remoto. Módulos cerrados
(prefijo entre paréntesis), todos con suites CMocka + ASan/UBSan limpio:

| Capa | Módulo(s) | Garantía clave |
| :-- | :-- | :-- |
| Red/TLS | `secure_fetch` (`sf_`), `tls_impersonate` (`ti_`) | TLS 1.3 mínimo, KE híbrido PQ preferido, validación de cadena; cada redirección re-aplica TODA la política (Zero Trust). Impersonación JA3/JA4 por triple opt-in (allow∩js∩impersonate). |
| URL/enlaces | `url` (`url_`), `link_nav` (`ln_`) | RFC 3986; "qué es una https absoluta válida" y "qué hace un clic" en un solo sitio; downgrade a http / esquemas ajenos no representables. |
| Política de red | `request_policy` (`rp_`), `render_policy` (`rdp_`), `webcaps` (`wc_`) | Bloqueo de terceros por defecto, https-only, gate de imágenes/CSS/JS (todo opt-in). `webcaps` unifica todas las capacidades por página desde señales de confianza. |
| Filtro de hosts | `hostblock` (`hb_`), `js_policy` (`jsp_`) | Lista negra + blanca `/etc/hosts`; la blanca gana y cubre subdominios. `js_policy` decide JS por host (off/allowlist/on/trusted/present_trusted). Ambos puros, falla abierto. |
| Enrutado de red | `net_realm` (`nr_`) | Clasifica clearnet / `.onion` / `.i2p` y decide ruta (directo / Tor SOCKS5h / I2P HTTP / **bloqueado**). Puro. Aislamiento de realm + **fail-closed** (nunca fuga `.onion` por clearnet). |
| Parser | `html_parse` (`hp_`), `dom` (`dom_`) | DOM inerte con Lexbor, strip de `<script>`/`on*`; índice consultable de solo lectura con handles enteros. |
| JS/anti-FP | `js_sandbox`/`js_dom`/`js_env`, `anti_fp` | QuickJS-ng vendorizado sin I/O; bindings sellados; relojes/pantalla normalizados; readback de canvas/audio envenenado **por origen** (`fp_origin_key`). `navigator` Firefox-completo, `crypto.getRandomValues` real, `Intl` stub, `customElements` stub. |
| Aislamiento | `os_sandbox` (`os_`), `tab` (`tab_`) | **fork+exec** (`/proc/self/exe --tab-worker`, sin COW cross-pestaña) + seccomp-bpf fail-closed con **W^X** (deniega `mmap`/`mprotect` con `PROT_EXEC`) + anti-volcado + Landlock + `unshare` user/net/ipc/uts. Worker NO toca red (pipe IPC al padre). |
| Estado cifrado | `local_store`, `disk_store`, `prefs` (`prefs_`), `profile` (`profile_`) | AEAD (AES-256-GCM/ChaCha20) + Argon2id; escritura atómica 0600 (Zero Knowledge). Perfil persistente (preferencias + marcadores + historial): modelo puro `prefs` fuzzeado sellado por `profile` con clave por dispositivo; AUTH-fail ⇒ defaults sin clobber. |
| Render pipeline | `page_view` (`pv_`), `render_doc` (`rd_`), `box_tree` (`bt_`), `flex_layout` (`fx_`), `compositor` (`cx_`), `dom_debug` (`dd_`) | DOM → display list → cajas (block/flex/grid) → stacking context (`cx_sort`, 7 capas CSS 2.1 App E). Posicionamiento, z-index, opacity de grupo, mix-blend-mode, transform matricial, overflow clipping, float. `--dump-dom`/`--dump-layout` para depuración headless. |
| CSS | `css` (`css_`), `css_select` (`csel_`), `css_color` (`cc_`), `interp` | Parser + cascada pura (~4000 líneas). Selectores: tipo/clase/id/grupos, 4 combinadores (descendiente, hijo, hermano `+`/`~`), atributos (`[attr]`/`[op=v]` con flags `i`/`s`), pseudo-clases (`:nth-child(An+B)`/`:hover`/`:focus`/`:checked`/`:has()`), pseudo-elementos (`::before`/`::after`). `!important`, `@media` (`prefers-color-scheme`, width queries), `@keyframes` (parseado+almacenado), custom properties con `var()`, `calc()`/`min()`/`max()`/`clamp()`. Props de layout: flex/grid completos con `fr`/px tracks, `gap`, `flex-wrap`, `align-items`, `grid-column: span N`, `grid-row: span N`. Decoración: `border-radius`, `box-shadow` (outset+inset), `linear-gradient`/`radial-gradient`, `background-image: url()` real (fetcheado bajo política) con `background-size`/`background-repeat`, `opacity`/`mix-blend-mode`/`isolation`, `backdrop-filter: blur()` (glassmorphism: muestrea+desenfoca el backdrop ya pintado; alias `-webkit-`), alfa de fondo `rgba()`/`hsla()` (`bg_alpha`, fill translúcido real). Transform: `translate()`, `scale()`, `rotate()`, `skew()`/`skewX()`/`skewY()`, `matrix()` (descompuesta QR en parse) con matriz Cairo afín real, pivotada en `transform-origin` (keywords+`%`). Unidades de viewport `vw`/`vh`/`vmin`/`vmax` contra el desktop normalizado 1920×1080 (mismo que `@media`/anti-fp; también dentro de `calc()`/math fns y `font-size`). Texto: `font-family` (bucket), `text-transform`, `letter-spacing`, `word-spacing`, `text-shadow`, `text-decoration`, `vertical-align`, `text-indent`, `white-space`, `word-break`, `overflow-wrap`, `text-overflow: ellipsis`, `font-variant: small-caps`, `direction`, `tab-size`, `line-height`. Caja: `margin`/`padding`/`width`/`min-width`/`max-width`/`height`/`min-height`/`max-height`/`aspect-ratio`/`box-sizing`/`visibility`/`overflow`/`cursor`/`pointer-events`/`caret-color`/`content-visibility`/`image-rendering: pixelated`. Shorthands: `font`, `background`, `place-items`/`place-content`/`place-self`. **Fail-closed:** `url()`/`@import`/`@font-face` descartados (cero red), topes anti-DoS, fuzzeado. |
| Imágenes | `image_decode` (`img_`), `data_url` (`du_`) | Decodificado **PNG + JPEG + WebP + GIF estático dentro del worker confinado**; topes anti-DoS; salida ARGB lista para Cairo. JPEG: libjpeg-turbo con `longjmp` que nunca llama `exit()`. GIF: decoder LZW **propio** en C puro (~300 líneas, sin giflib, fuzzeado). WebP: libwebp. `data_url`: base64 inline sin red. |
| Video/Audio | `media_decoder` (`md_`), `hls` | FFmpeg pipeline para H.264/H.265 desde MPEG-TS o `.m3u8` HLS en **proceso decoder aislado** (fork+exec, `OS_PROFILE_MEDIA_DECODER`). **v2 (2026-07-19):** reproducción a **ritmo de PTS** contra reloj de pared (`md_pacer` puro, testeado; el consumidor regula el pipeline por contrapresión de pipes), PTS en µs con time_base por segmento, primer segmento decodificado (no solo probe), drain solo en flush (v1 dejaba el codec en EOF tras cada segmento: solo se reproducía uno), audio `aplay` O_NONBLOCK best-effort (jamás bloquea el hilo Wayland), EOF del decoder ⇒ cierre ordenado. E2E: 3 segmentos HLS ⇒ 150/150 frames. Fachada JS `HTMLMediaElement` + `new Audio()` identity-safe en el worker (`spec/js_dom.md` §7c); `<source>` elegido por `type`; fallback interno de `<video>` suprimido. Integración jkanime: extracción de iframe→.m3u8/.mp4. |
| Formularios | `form` (`fm_`), `textfield` | **GET/POST nativos sin JS**; target no-https no representable (fail-closed). Campos `<input>`/`<textarea>`/`<button>`/`<select>` nativos. |
| Shaping | `text_shape` (`tsh_`) | HarfBuzz + FreeType + fontconfig. Ligaduras, kerning GPOS, formas contextuales. **Solo lado confiable**, fuentes locales, fuzzeado. |
| Export | `pdf_export` (`pe_`), `zoom` (`zm_`) | PDF vectorial (texto seleccionable, paginación determinista, nombre fail-closed). Zoom 50–300% ladder, página reflowa al repintar. |
| Descargas | `download` (`dl_`) | Guardar recurso a `~/Downloads/freedom/`. Nombre fail-closed (reusa `pe_safe_basename`), escritura atómica 0600. |
| Pool/prefetch | `prefetch` (`pf_`) | Pre-scanner lookahead puro (fuzzeado) + pool pthreads (4 hilos) que baja stylesheets/scripts/imágenes en paralelo. Worker intacto. |
| DevTools | `freebug` (`fb_`), `dom_debug` (`dd_`) | Consola JS (`F12`, `--dump-console`): log coloreado por nivel + ubicación `file:line:col` + REPL. `--dump-dom`/`--dump-layout` para debugging headless. Persistencia por-pestaña pendiente. |
| UI | `ui`/`browser` (puros) + `gui/browser_ui.c` (orquestador Wayland+Cairo, 10.712 L — deuda) | Toolbar, tabs, barra URL, scroll, menú de opciones, clic, submit. Multi-pestaña, atajos (`Ctrl+T/W/Tab`, `Ctrl+R`, `Ctrl+P/S`, `Ctrl++/-/0`). Temas claro/oscuro/sepia. `Ctrl+D` reader mode. **DEUDA:** extraer painter/chrome a módulos propios. |
| Auditoría | `spec/threat-model.md` | Activos/adversarios/fronteras → mitigaciones. 16 fuzz targets, 1317 tests. |

**Decisiones de doctrina vigentes** (no evidentes en el código; no re-litigar):
- **Navegabilidad sobre PQ estricto:** un host que no puede KE híbrido PQ **avisa** (toast
  "classical TLS 1.3"), no bloquea (`SF_POLICY_ALLOW_CLASSICAL_KE`). Por defecto, TLS<1.3 / cadena
  inválida / SHA-1 siguen fatales — **salvo** que el host esté en la allowlist (override de
  soberanía, abajo). Ver `[[freedom-navigability-over-strict-pq]]`.
- **La allowlist es el override de soberanía (no dictadura):** un host en `allow.conf` se navega
  bajo `SF_POLICY_ALLOWLISTED_INSECURE` (TLS 1.2, KE clásico, cert débil-pero-válido) si el
  estricto falla, con aviso; la autenticidad de la cadena se mantiene (VERIFYPEER). Es el caso
  de Hacker News (`news.ycombinator.com`, solo TLS 1.2). `hb_is_allowlisted` distingue "en la
  blanca explícita" de "permitido por defecto". Ver `[[freedom-navigability-over-strict-pq]]`.
- **Umbral RSA<3072 solo al leaf** (los intermedios RSA-2048 de la Web PKI son válidos). Un
  sitio con leaf RSA-2048 se sortea con la excepción por host **Ctrl+Shift+E** (PERMISSIVE, solo
  sesión).
- **Identidad de red = identidad anti-fingerprinting (no "Freedom/0.1"):** el `User-Agent` por
  defecto de la red **es** `FP_USER_AGENT` (cadena común de Firefox/Linux, fuente única en
  `anti_fp`) y **coincide** con `navigator.userAgent`; toda petición (GET y POST) envía además un
  `Accept-Language` normalizado (`FP_ACCEPT_LANGUAGE_HEADER`). Mandar `"Freedom"` por el cable era
  huella única + señal de bot (rompía Google/Cloudflare). El usuario puede sobrescribir la UA por
  sesión (menú); vacío ⇒ default anti-fp. Ver `[[freedom-anti-fp-network-identity]]`.
- **Readback de canvas/audio por origen (eTLD+1), no por sesión cruda:** la clave que envenena la
  lectura de `canvas`/`audio` se deriva por sitio con `fp_origin_key(session_key, eTLD+1)` (pura, en
  `anti_fp`: FNV-1a del dominio mezclado con el secreto de sesión y finalizado con `splitmix64`). El
  secreto de sesión sigue siendo aleatorio por worker (`getrandom`); en cada `OP_LOAD` el worker
  calcula el dominio registrable con `request_policy` (`rp_host_of`→`rp_site_of`, tabla PSL) sobre la
  URL de la página y se lo pasa a `je_install_canvas`. Así dos sitios renderizados por el mismo
  worker ven ruido distinto: se cierra el **cross-origin linking** de la huella de readback (antes la
  spec lo difería al "orquestador de sesión"). URL sin host (`file://`, vacía) ⇒ `NULL` ⇒ namespace
  propio estable; nunca aborta ni filtra. Layout/estructura no se ven afectados. Ver
  `[[freedom-anti-fp-origin-readback-key]]`.
- **Omnibox en la barra de URL:** `url_omnibox` (puro) decide navegar vs buscar — host desnudo ⇒
  `https://`, `http://` ⇒ promovido a https, esquema ajeno (`javascript:`/`file:`) ⇒ **búsqueda**
  (nunca ejecución, fail-closed), texto libre ⇒ DuckDuckGo HTML (sin JS). El orquestador (`go_omnibox`)
  resuelve primero un archivo local existente (la función pura no hace I/O). Ver `[[freedom-omnibox-search]]`.
  **El buscador depende de la allowlist:** `html.duckduckgo.com` (todos los endpoints de DuckDuckGo)
  presenta un **leaf RSA-2048**, que la política por defecto **rechaza** (`RSA<3072` ⇒ status 5). Por
  eso `config/allow.conf` **incluye `duckduckgo.com`** (cubre subdominios): el override de soberanía
  (`SF_POLICY_ALLOWLISTED_INSECURE`) acepta el cert débil-pero-válido **manteniendo** la autenticidad
  de cadena — y de hecho aún negocia **TLS 1.3 + X25519MLKEM768** (solo se relajó el cert). Si la
  búsqueda muestra **página en blanco / sin JS**, es que el `allow.conf` con `duckduckgo.com` **no está
  en el search path en runtime** (`$FREEDOM_HOSTS_DIR`, `~/.config/freedom`, `./config`): correr desde
  la raíz del repo o copiar el config a `~/.config/freedom/` lo resuelve. Ver `[[freedom-search-needs-allowlist]]`.
- **SPA de buscador ⇒ endpoint no-JS server-rendered (rewrite transparente):** navegar directo a la
  **SPA de DuckDuckGo** (`duckduckgo.com/?q=...`) se reescribe transparente a su endpoint HTML sin JS
  (`URL_SEARCH_ENDPOINT` + la misma query) en el único choke point de navegación (`do_load` GUI,
  `fetch_and_render_one` headless), vía `url_search_rewrite` (puro). La SPA trae resultados por XHR
  async + framework de render de cliente que el modelo síncrono no completa ⇒ pinta en blanco; el
  endpoint HTML da los mismos resultados sin nada de eso. Transparente: barra/historial guardan la URL
  pedida (Recargar/Atrás re-aplican). Google **no** se toca (sin endpoint no-JS fiable; su "tráfico
  inusual" es server-side). Aparte, se corrigieron los gaps del shim JS que hacían fallar la consola
  de la SPA (y de **toda** la web jQuery/`Intl`): `document.nodeType===9`+`defaultView` (el
  `setDocument` de Sizzle), `element.attributes` NamedNodeMap + `getAttributeNames`/`hasAttributes`
  (via C `dom_attribute_names`), y stub de `Intl` (QuickJS-ng sin ICU) ⇒ consola 0. Ver
  `[[freedom-search-spa-noscript-rewrite]]`.
- **Cookies de sesión EN MEMORIA para hosts de confianza (doctrina 2026-07-12, aprobada por el dueño):**
  un host allow∩js recibe cookies **efímeras en memoria** (nunca a disco, mueren al cerrar la app —
  mismo espíritu que el `localStorage` efímero), **sin romper Zero Knowledge ni Zero Trust**. El jar de
  red ya existía (`sf_share` CURLSH); lo que faltaba y se cerró: **`document.cookie` real** en el worker
  (jar deshabilitado por defecto = `''`/no-op para no-confiables → ZK; habilitado y sembrado por
  `jd_set_cookies`, volcado por `jd_get_cookies`), helpers `sf_cookie_header_for`/`sf_cookie_put`
  (excluyen `HttpOnly` — network-only — y expirados) y el puente IPC (OP_LOAD lleva cookies-in y el tail
  del resultado lleva el dump-out; solo en el path OP_LOAD, no en la cola de mutación). La GUI y headless
  siembran desde el jar antes de cargar y hacen foldback antes de cualquier salto de nav JS. **Google
  sigue sin renderizar** (su muro es botguard/consent/IP server-side, no algo que las cookies resuelvan;
  se lo dije al dueño): la capacidad sirve para sitios de confianza que usan cookies cooperativamente. El
  rewrite no-JS de DuckDuckGo se mantiene. Ver `[[freedom-session-cookies-trusted-spa]]`.
- **JS Secure by Default + allowlist por host + ejecución viva:** el JS de página está **apagado**
  salvo opt-in por host. Modo global tri-estado (`JSP_OFF`/`JSP_ALLOWLIST`(defecto)/`JSP_ON`);
  pertenencia por host en `js.conf` (reusa `hostblock`, cubre subdominios). `js_policy` (puro) decide;
  la GUI deriva `caps.js` por host y lo pasa al worker con `tab_load_ex(run_js)`. Con JS habilitado,
  el worker **ejecuta** los scripts inline de la página (Hito 20b) sobre un **DOM escribible pero
  seguro**: los mutadores (`dom_set_text_content`/`dom_set_document_title`) **DETACHAN** hijos
  (`lxb_dom_node_remove`, nunca `destroy`), así un handle del índice nunca queda colgando (cero UAF);
  el bridge expone una fachada estándar `document` (`document.title`, `getElementById().textContent`,
  **`createElement`/`appendChild`/`removeChild`/`setAttribute`**, `body`/`head`, `addEventListener`/
  `onload`, `setTimeout`) sobre handles enteros validados, sin objetos-nodo vivos. El índice **crece**
  para nodos nuevos; `append` rechaza ciclos; `setAttribute('id'/'class')` re-indexa lookups. Eventos
  y timers son **sintéticos y acotados**: el worker llama `__fireDeferred()` una vez tras los scripts
  (dispara handlers de carga + vacía la cola de timers ≤64). `<noscript>` se muestra con JS off, se
  oculta con JS on. **`innerHTML`** (setter) re-parsea un fragmento, detacha los hijos viejos e indexa
  el subárbol nuevo (memory-safe). **Superficie ambiente identity-safe** (Hito 20d): `localStorage`/
  `sessionStorage` **efímeros en memoria** (Zero Knowledge — nunca persisten), `document.cookie` (get
  `""`/set no-op), `document.referrer` `""`, `history` stub no-op — para que el JS de
  detección **corra sin lanzar** sin filtrar identidad. **`location` real + navegación por JS**
  (Hito 20e parte 1): el worker recibe la URL de la página, inyecta `__locParts` **en C** (`url_split`;
  la URL hostil nunca se interpola en JS) y expone un `location` real de **solo lectura**; las
  escrituras que navegan (`location.href=`/`assign`/`replace`/`reload`/`window.location=`) solo
  **registran la string cruda** — **el padre confiable la gatea** con `ln_resolve(URL_real, cruda)` (un
  worker comprometido no puede colar `file://`/downgrade) y la GUI navega por el camino normal
  (re-aplica TODA la política), con cap anti-bucle. **Fuera de alcance (parte 2):** eventos
  interactivos (clic), timers async reales, getter de `innerHTML`, scroll a ancla `#id`. (Los
  **scripts externos `src`** dejaron de estar fuera de alcance: corren para hosts allow∩js desde el
  **Hito 24 EXT**.) No usar `lxb_dom_node_destroy` en mutadores (colgaría el índice). **No** persistir
  el storage ni poblar cookie/referrer con datos reales (rompería Zero Knowledge). Ver `[[freedom-live-js]]`.
- **Aislamiento de scripts por `<script>` (browser semantics) + `document.fonts` stub:** el worker
  ejecuta **cada** `<script>` inline como su **propio programa** (`hp_extract_script_list` → un
  `js_eval` por script), no concatenados en un único eval. Antes, una excepción no capturada en el
  primer script **abortaba todos** los siguientes — por eso google.com "no cargaba nada": su primer
  script llama `document.fonts.load(...)` y, sin ese global, lanzaba `cannot read property 'load' of
  undefined`, matando el resto. Dos arreglos: (a) cada error de script se reporta a Freebug
  (`FB_ERROR`) pero **no** corta los demás; (b) `document.fonts` es un stub `FontFaceSet` benigno
  (identity-safe, sin red). Un **único presupuesto de reloj por página** (`js_set_time_budget`) se
  reparte entre todos los scripts + `__fireDeferred`, así aislar **no** multiplica el tope de 1 s
  (fail-closed: scripts tras agotarlo no corren); tope `HP_MAX_SCRIPTS` (4096) anti-DoS. Desde el
  **Hito 24 EXT** el JS externo (`<script src>`) de un host allow∩js **sí corre** (fetcheado por el
  padre bajo política); si Google aun así sirve su muro anti-bot, es decisión server-side (IP/cookies)
  — la omnibox (→ DuckDuckGo) sigue siendo el buscador por defecto. Ver `[[freedom-live-js]]`,
  `[[freedom-per-script-isolation]]`, `[[freedom-external-scripts]]`.
- **Privacy by Default:** imágenes y colores de autor (CSS) **apagados**; opt-in en el menú
  (`Ctrl+I`; `FREEDOM_IMAGES=1` al arrancar). Imágenes **PNG, JPEG y GIF estático** (resto →
  placeholder) y fetch **síncrono**; el decode corre
  en el worker confinado (JPEG es excepción de doctrina autorizada por el dueño, contenida por el
  sandbox + guardas de libjpeg; ver `[[freedom-jpeg-decode]]`). El toggle de imágenes cubre
  **remotas y locales** por igual (una regla, fail-closed): un HTML local hostil tampoco autocarga
  nada hasta que el usuario habilita imágenes.
- **Origen `file://` para páginas locales (actúan como https):** una página de archivo recibe origen
  `file:///realpath` (`build_file_origin`/`realpath` en la GUI), así sus `src` relativos resuelven
  con `url_resolve_file` (puro) **confinado al subárbol del directorio del documento** (sin escape
  `../`, sin path absoluto fuera, sin esquema remoto/ajeno → no telefonea a casa, no lee
  `/etc/passwd`). Con imágenes ON (`Ctrl+I`) el `logo.png` de `docs/index.html` se ve dentro de
  Freedom; la lectura de disco es acotada (`read_file_bounded`) y el decode sigue en el worker. La
  navegación local sigue usando paths planos (historial/barra/base de link), `file://` es solo el
  origen de render; un `file://` tecleado se normaliza a su path. Ver `[[freedom-local-file-origin]]`.
- **Layout != estilo de autor:** la **maquetación** (box model UA, flex/grid, márgenes/columnas)
  se aplica **siempre**, desacoplada de `caps.css`; es estructura, no abre sockets ni filtra a la
  red. Solo los **colores** de autor (`fg_rgb`/`bg_rgb`) siguen gateados por `caps.css`. El gate
  vive en `render_doc` (`rd_build`). Antes flex/grid estaba gateado y no se veía nunca.
- **Filtro de hosts opcional + override:** `block.conf`/`allow.conf` (formato `/etc/hosts`) se leen
  de `$FREEDOM_HOSTS_DIR`, `~/.config/freedom` y `./config`; la GUI consulta `hb_check` antes del
  fetch (la blanca gana y cubre subdominios). Falla **abierto**: sin listas no bloquea nada. La
  blanca tiene **doble rol**: des-bloquea del adblock **y** habilita el override TLS por host.
- **Tor/I2P a nivel de socket (opt-in):** integración por **proxy local** (Tor SOCKS5h
  `127.0.0.1:9050` / I2P HTTP `127.0.0.1:4444`), **nunca** embebiendo el daemon (superficie). El
  cerebro es `net_realm` (puro): `.onion`→solo Tor, `.i2p`→solo I2P, clearnet→directo o Tor si
  "torify". Dos invariantes: **DNS remoto** (SOCKS5h, sin fuga) y **fail-closed** (realm sin su
  proxy → bloqueado, jamás directo). `.onion` sigue **https-only**; **`.i2p` acepta `http://`**
  (`nr_realm_allows_http`/`sf_config.allow_overlay_http`): los eepsites son http y el overlay ya
  cifra/autentica por dirección, así que no es downgrade; `http://` clearnet **sigue rechazado**.
  TLS 1.3 sigue vigente en `.onion` (el override por host de `allow.conf` aplica si hace falta).
  Redirects overlay http se resuelven en http (sin salir del overlay). GUI: toggles "Tor/I2P
  routing"; headless: `--tor[=addr]`/`--i2p[=addr]`/`--torify`; env: `FREEDOM_TOR_PROXY`/
  `FREEDOM_I2P_PROXY`/`FREEDOM_TORIFY_CLEARNET`. **Verificado de extremo a extremo** (jun 2026):
  `.onion` vía Tor y `.i2p` vía el router Java (`stats.i2p`, `i2p-projekt.i2p` con redirect).
- **SOP por construcción por defecto + red-en-JS SOLO para hosts en allow.conf ∩ js.conf
  (override de soberanía, Hito 26):** por defecto el sandbox JS **no expone** ninguna API de red
  (`fetch`/`XMLHttpRequest`/`WebSocket`/`EventSource`/`sendBeacon`/`Image`), no hay `iframe`,
  `window.open`/`postMessage`/`opener`, el readback de canvas/audio está envenenado y el worker **no
  tiene red** (`CLONE_NEWNET`+seccomp): para un sitio normal la SOP clásica es **estructuralmente
  imposible** y no se implementa CORS (sería código muerto). **Excepción gateada:** un host presente
  en **allow.conf Y js.conf** (el usuario lo declaró de confianza dos veces) recibe `XMLHttpRequest`
  y `fetch` **reales** — pero el JS **nunca toca el socket**: el worker confinado proxya la petición
  al **padre confiable** (`tab_set_fetcher`/`tab_set_net_allowed`; protocolo `TAG_SUBREQ`/`TAG_RESULT`
  en `tab.c`), que **re-aplica TODA la política** (hostblock/filtro de rastreadores, `net_realm`
  fail-closed, TLS-PQ con los fallbacks de navegabilidad) antes de buscar. Así "la web moderna
  funciona" para sitios de confianza **bloqueando rastreadores en la capa de red** ("si el JS no toca
  el socket, no hay espionaje"). Para esos sitios SÍ hay lecturas cross-origin (no implementamos CORS;
  la protección es: solo hosts explícitamente confiables, rastreadores hostbloqueados, `document.cookie`
  vacío → nada sensible que robar). El candado de regresión **se mantiene**:
  `test_eval_no_network_or_cross_origin_api` corre con la red **apagada** (sitio no-confiable) y exige
  que XHR/fetch sigan `undefined` por defecto; tests nuevos (`test_xhr_works_when_net_allowed`,
  `test_xhr_undefined_when_net_not_allowed`, `test_xhr_blocked_host_refused_by_parent`) candan la ruta
  gateada y que el padre rechaza un host bloqueado. **Límites v1:** síncrono bajo el capó (el worker —y
  en el GUI el hilo de render— se bloquea durante el round-trip; aceptable por host de confianza),
  activo solo durante la ventana de scripts de la carga (no en el REPL ni en eventos post-carga), y la
  respuesta pasa por string UTF-8 (sin `arrayBuffer` binario real). Ver `spec/threat-model.md` §3,
  `[[freedom-sop-by-construction]]`, `[[freedom-parent-gated-xhr]]`, `[[freedom-js-network-and-media-authorized]]`.
- **Doctrina trusted-host (Hito 28) — allow∩js ⇒ experiencia completa:** un host que el usuario
  declaró de confianza DOS veces (JS habilitado para él **y** presente explícito en `allow.conf`)
  recibe TODO el JS (ya lo tenía: ejecución, XHR/fetch, scripts externos) **y toda la presentación
  de autor** (CSS + imágenes) sin toggles de sesión: `jsp_trusted` (pura, `js_policy`) decide y la
  GUI enciende `caps.css`/`caps.images` **efectivos** (el modo lectura gana; los toggles
  persistentes del usuario no se tocan). Racional: donde el XHR gateado por el padre ya puede traer
  bytes arbitrarios, dejar imágenes/CSS apagados no añade privacidad — solo fricción. Un modo
  global `JSP_ON` **no** es confianza (falla cerrado: exige la entrada explícita en `allow.conf`).
  Ver `[[freedom-trusted-host-full-caps]]`.
- **Prefetch paralelo del lado confiable (Hito 29) — pipeline no bloqueante sin tocar el worker:**
  módulo `prefetch` (`pf_`): pre-scanner lookahead **puro** (fuzzeado; comentarios/`<script>`/
  `<style>` opacos, `rel` distinto de stylesheet descartado) sobre el HTML crudo + **pool de hilos**
  (`PF_MAX_THREADS`=4) que baja stylesheets/scripts externos e imágenes **en paralelo** por el
  MISMO `tab_fetch_fn` gateado del camino serial; `pf_pooled_fetch` sirve los `TAG_SUBREQ` del
  worker cache-first (miss ⇒ fetch directo). El worker y su protocolo no cambian un byte: un hit
  solo cambia **cuándo** se buscó, jamás **qué** (quitar el pool no cambia el conjunto de fetches).
  E2E verificado: 4 hojas con 400 ms de latencia artificial llegan con ~4 ms de dispersión
  (suma→máximo), 5 GETs exactos (cero re-fetch). Las **fronteras del motor moderno** siguen siendo
  doctrina, no gaps: **JIT dentro del worker es estructuralmente imposible** (el W^X de seccomp
  deniega `PROT_EXEC`; QuickJS es intérprete de bytecode a propósito) y el worker **no toca GPU**
  (el compositor vive en el lado confiable). Ver `[[freedom-prefetch-parallel-pool]]`.
- **`io_uring` PROHIBIDO en el worker confinado (la doctrina io_uring es solo del lado confiable):**
  la §3 pide I/O asíncrona con `io_uring`, pero `io_uring` es una **primitiva de bypass de seccomp**
  (sus `IORING_OP_*` no atraviesan el syscall entry que filtra el BPF), así que **nunca** entra al
  allowlist del worker: un ring le permitiría a un worker comprometido `openat`/`connect`/`read`
  burlando el filtro, W^X y `CLONE_NEWNET` — anularía toda la frontera Zero-Trust (como en Docker/
  ChromeOS/Android, que lo bloquean). Ya está denegado **por construcción** (el allowlist es blanco,
  deny-by-default), y se candadea con regresión: `test_policy_denies_io_uring` (puro) +
  `test_harden_kills_io_uring_setup` (`io_uring_setup` ⇒ `SIGSYS`). La asincronía de la UI vive en el
  lado confiable (event loop Wayland + fetch en hilo desacoplado, Hito 9), **jamás** donde corre
  contenido hostil; el worker solo hace I/O bloqueante sobre dos pipes. Análogo a SOP por
  construcción. Ver `spec/os_sandbox.md` §13, `[[freedom-io-uring-forbidden-in-worker]]`.
- **Impersonación de TLS (JA3/JA4) por host triple-opt-in (Hito TLS, autorizado como excepción §4):**
  el discriminador que bloquea a Freedom en Google/FB/YT **no** son las cabeceras HTTP (ya son
  Firefox-completas; `Sec-Ch-Ua` bajo UA Firefox *empeoraría*), sino el **ClientHello TLS**: nuestro
  PQ-by-default (`X25519MLKEM768` bajo UA Firefox 128 que no lo manda) es el tell más ruidoso. Gate
  **triple** (`ti_should_impersonate`, puro): un host en `allow.conf` ∩ `js.conf` ∩ **`impersonate.conf`**
  recibe `sf_config.impersonate` ⇒ `secure_fetch` deja el ClientHello consistente con la identidad
  Firefox que ya mandamos (quita MLKEM, ordena cifras TLS1.3/1.2 estilo Firefox, grupos clásicos).
  **Verificado E2E** (`tls.peet.ws`): ON ⇒ JA4 con componente de cifras idéntico al de Firefox 128 real,
  sin MLKEM; OFF ⇒ default PQ. **Solo relaja la fuerza del KE (clásico) en esa ruta, nunca la
  autenticidad** (VERIFYPEER intacto); el resto del navegador mantiene PQ. **Fase 2** (gate + códec IPC
  `ti_`, fuzzeado) y **Fase 3** (blend interino OpenSSL) cerradas; **Fase 1** (JA3 byte-exacto vía
  curl-impersonate+BoringSSL, proceso helper aislado) queda **bloqueada** en este host (no empaquetado).
  **NO** derriba reCAPTCHA/BotGuard/IP (muros de motor/red, no TLS). Ver `spec/tls_impersonate.md`,
  `[[freedom-tls-impersonate]]`.
- **Modo boyscout:** un "fix" puede destrozar un módulo de seguridad; ante una regresión, diff
  contra el commit inicial antes de tocar nada. Ver `[[freedom-security-modules-butchered-by-fix-commits]]`.
- **`display:none` es estructural, no una sugerencia de JS — revertida la regresión del commit 897f414:**
  el commit 897f414 modificó `in_hidden_subtree` en `page_view.c` para tratar
  `display:none` como "sugerencia de presentación" cuando el elemento tenía inline `style`
  Y no había JS (`js_enabled==0`). El problema: la comprobación era `st != NULL && sl > 0`
  (cualquier inline style), no si el inline style específicamente contenía `display:none`.
  En slashdot.org, muchos elementos con `display:none` del stylesheet tenían inline
  `style` para colores/posición → se mostraban como filas vacías de 1px → página
  ilegible (142.000 px de alto, en lugar de ~18.000). Se revirtió a la semántica
  correcta: `display:none` de cualquier fuente oculta el elemento; la excepción
  experimental de "JS toggle" se eliminó por romper más sitios de los que arreglaba.
  Ver `[[freedom-display-none-structural]]`.
- **`-fvisibility=hidden` es invariante de build (no quitar):** el binario `freedom` no exporta API,
  así que todos sus símbolos van **ocultos** del `.dynsym`. No es solo endurecimiento: un símbolo del
  ejecutable con visibilidad por defecto **preempta** al homónimo de una librería enlazada en TODO el
  proceso. Concreto: `hostblock` usa prefijo `hb_` y HarfBuzz (Hito 25) exporta un `hb_free` público
  → sin la flag, el `hb_free` del ejecutable secuestra el alocador de HarfBuzz y lo crashea dentro de
  `hb_shape`. La flag vive en `HARDEN` **y** en el `CFLAGS` de `asan` (asan no hereda HARDEN, y su build
  de `freedom` vía `test_freedom --download-pdf` también enlaza HarfBuzz). Ver `[[freedom-harfbuzz-shaping]]`.

### 7.2 Hitos cerrados (resumen)

> Comprimido 2026-07-17 — ~70 hitos menores cerrados (julio 2026). El detalle completo vive en
> `git log`, `spec/`, y la memoria persistente del agente. Ver §8 sobre el límite de tamaño.

**Hitos mayores por etapa:**
- **Foundation (Hitos 6–18):** GUI interactiva (temas/atajos), CSS estático+box model UA, filtro de hosts (`hostblock`), Tor/I2P (`net_realm`), charset, render moderno (listas/tablas/énfasis), multi-pestaña, fetch asíncrono, PDF export, tooling headless (`--download-png`/`--download-pdf`/`--dump-dom`), XHR/fetch gateados (Hito 26), scripts externos (Hito 24 EXT), namespaces+seccomp W^X+fork+exec worker, identidad anti-fp+omnibox.
- **CSS moderno (Hitos 19–25):** `file://` origen local, decodificación JPEG/GIF/WebP en worker, `line-height`+`--author-css`, allowlist JS, JS vivo (DOM bridge, timers sintéticos, `innerHTML`, `location`), zoom+descargas, CSS de autor+reader mode, `@media`, flex/grid desde `<style>`, box model de autor, selectores atributo+`!important`, `text-decoration`, props presentación, layout values, tablas anidadas, external stylesheets, HarfBuzz shaping.
- **JS & render avanzado (Hitos 26–30):** `querySelector`, `URL`/`URLSearchParams`, `float`/`clear`, `var()`/`calc()`/`repeat()`/`minmax()`/`flex-wrap`, `visibility`/`overflow` pintado, pipeline CSS→pintura completo, math functions+propiedades lógicas+shorthands, caps CSS 16x+`pv_style_cache`, trusted-host doctrina, prefetch paralelo, perfil persistente cifrado, `border-radius`+`linear-gradient`, `fr`/px grid tracks, `box-sizing: border-box`, timers async reales, PSEUDO_ALWAYS, presentation-trust, cookies sesión, DuckDuckGo SPA→rewrite, blend-in surface.
- **Compositor & transform (M0.1–M1.2b):** `webcaps` unificado, codec IPC bulk, `compositor` puro (`cx_`), z-index negativo fix, opacity grupo real, mix-blend-mode+isolation, CSS `transform` translate/scale/rotate con matriz Cairo afín.
- **Imágenes & datos (Julio 16–17):** `data_url` (base64 inline fuzzeado, 17M execs), `srcset` fallback, `background-image: url()` real con `background-size`/`background-repeat`, webp decoder, pipeline video jkanime (iframe→.m3u8/.mp4).
- **Video pipe hardening (Julio 18):** `video_read_frame` reads one frame per poll (no recursion), `v_read` handles `EAGAIN` via poll+retry, `decoder_out_fd` fixed `F_GETFL`/`O_NONBLOCK`. Script async attribute removed; R7 simplified to two-pass (sync→defer).
- **Video pacing v2 + superficie media moderna (Julio 19):** `md_pacer` puro (spec/media_decoder.md; 6 tests, ASan, hostile-PTS sin UB) + 5 fixes v1 (audio bloqueante, sin pacing, primer segmento perdido, PTS en segundos, drain por segmento ⇒ codec EOF permanente) + fachada `HTMLMediaElement`/`Audio` (spec/js_dom.md §7c) + `<source>` por type + fallback de media suprimido + fix noscript-con-JS (snapshot preserve llevaba js=0). **v2.1 (mismo día):** el repaint-por-frame ahogaba el pipeline (audio inaudible) — tope de catch-up solo-video, pintado desacoplado a `max(33, 3×costo medido)` ms y pipe de aplay 1 MiB; validado con simulador del consumidor (repaint 5/60/300 ms ⇒ 100 % del PCM a tiempo real). Ver `[[freedom-video-pacing-v2]]`.
- **Batch impacto visual moderno (Julio 19):** viewport units `vw`/`vh`/`vmin`/`vmax` vs 1920×1080 normalizado (spec/css.md "Viewport units"); M1.2c `skew()`/`matrix()` QR-decompuesta/`transform-origin` (spec/compositor.md); `backdrop-filter: blur()` + alfa de fondo `rgba()`/`hsla()` + dedup fila-vs-caja + altura de autor out-of-flow (glassmorphism E2E); `matchMedia` real + `IntersectionObserver` sintético identity-safe (spec/js_dom.md §7b, destraba reveal-on-scroll). Fuzz-css re-enlazado (bit rot lexbor). Ver `[[freedom-visual-impact-batch]]`.
- **Tooling & seguridad:** Doctrinas V-001 (SIZE_MAX guard), V-002 (`calloc`), V-003 (buffer encadenado), V-004 (`snprintf` fail-closed). `-fvisibility=hidden` invariante. `io_uring` PROHIBIDO en worker.

### 7.3 Plan Estratégico — Hitos abiertos por fase

> Convención: cada hito abierto requiere spec → test rojo → código verde → refactor →
> validación (ASan) → fuzzing → documentación. Un hito se marca cerrado solo cuando pasa
> `make test && make asan` y, donde aplique, `make fuzz-*`.

---

#### FASE 0: Cierre de Deuda + Animación CSS (prioridad inmediata)

| Hito | Descripción | Dependencias | Esfuerzo |
|:--|:--|:--|:--|
| **A. Cerrar animación `@keyframes`** | `interp.c` cableado al `frame_clock` → painter. `@keyframes` ya parseado+almacenado, `frame_clock` existe, `interp.c` listo. Falta: conectar el frame tick al pipeline de pintado. | Ninguna | Bajo |
| **B. Refactor painter (extraer de browser_ui.c)** | `paint_box_decoration`, `paint_content_row`, `paint_structured`, z-index painter → `src/painter.c` + `include/painter.h` | Ninguna | Bajo |
| **C. Refactor chrome (extraer de browser_ui.c)** | Toolbar, tabs, omnibox, menú de opciones → `src/chrome.c` + `include/chrome.h` | Hito B (desacople de painter) | Medio |
| **D. HTTP/2 en secure_fetch** | Negociación nativa HTTP/2 vía libcurl (`CURL_HTTP_VERSION_2_0`). Configurable por política. | Ninguna | Bajo |

**Driver:** Bajo esfuerzo, alto impacto visual. La animación es el 80% listo. El refactor de `gui/browser_ui.c` (~10.700 L → deuda §5) se hace incremental — estos dos hitos extraen la lógica más caliente. HTTP/2 es un cambio de configuración en curl, casi cero riesgo.

---

#### FASE 1: Red Moderna + Tiempo Real

| Hito | Descripción | Dependencias | Esfuerzo |
|:--|:--|:--|:--|
| **E. HTTP/3 (QUIC)** | Helper aislado con `ngtcp2` + `nghttp3`. Solo en el lado confiable (padre), nunca en el worker. Config toggle. | Hito D | Alto |
| **F. WebSockets** | Nuevo protocolo IPC `TAG_WS_*` (mismo patrón que `TAG_SUBREQ`). Gateado por `webcaps.net` (allow∩js). El worker proxea al padre, que abre el socket real. | Hito D (HTTP/1.1 upgrade base) | Medio |
| **G. Fetch asíncrono multipestaña** | Cargas concurrentes entre pestañas (hoy una a la vez). El fetch-thread atiende múltiples workers. | Hito 9 (existente) | Medio |

**Driver:** Sin HTTP/2/3, el rendimiento en redes modernas es pobre. WebSockets destraba apps real-time (chats, dashboards, notificaciones). Fetch concurrente destraba I2P (latencia alta).

---

#### FASE 2: APIs JS de Persistencia + Criptografía

| Hito | Descripción | Dependencias | Esfuerzo |
|:--|:--|:--|:--|
| **H. IndexedDB** | API `indexedDB` sobre `local_store` (cifrado Argon2id + AES-256-GCM/ChaCha20). Efímero por sesión = Zero Knowledge. | `local_store` (existente) | Alto |
| **I. Web Crypto (subtle full)** | `subtle.encrypt/decrypt/sign/verify/digest` real con OpenSSL nativo. `getRandomValues` y `randomUUID` ya existen. | Ninguna | Medio |
| **J. `arrayBuffer` binario real** | `fetch()` y XHR con response `arrayBuffer` (hoy solo string UTF-8). Streaming diferido. | Hito D (HTTP/2) | Bajo |

**Driver:** IndexedDB es la API de persistencia más solicitada para PWAs. Web Crypto permite firmas y cifrado sin exponer claves al contenido remoto.

---

#### FASE 3: Tiempo Real de Confianza + Wasm

| Hito | Descripción | Dependencias | Esfuerzo |
|:--|:--|:--|:--|
| **K. WebRTC (allow∩js)** | Solo para trusted hosts (allow∩js). Forzar TURN sobre Tor, bloquear STUN público. `getUserMedia` gateado. Proceso helper aislado con su propio perfil seccomp. | F (WebSockets, signaling) | Muy alto |
| **L. WebSocket para trusted hosts** | Extensión de F: el gate `webcaps.rtc` permite conexiones WebSocket sin restricción de proxy. | F (WebSockets) | Bajo |
| **M. Wasm helper process** | Nuevo `src/wasm_helper.c` con seccomp más permisivo (PROT_EXEC permitido). Comunicación pipe con el worker. Runtime interpreter-only (wasm3 modo intérprete, sin JIT). W^X del worker principal intacto. | Ninguna | Alto |
| **N. Service Workers (solo cache offline)** | Ciclo de vida limitado: mueren con la pestaña. Cache API sobre `local_store`. Sin sync en background, sin push, sin persistencia fantasma. | H (IndexedDB) | Alto |

**Driver:** Wasm y SW son las dos capacidades "modernas" más pedidas. WebRTC solo se activa con doble opt-in explícito (allow∩js es la llave maestra).

---

#### FASE 4: DevTools + Ecosistema

| Hito | Descripción | Dependencias | Esfuerzo |
|:--|:--|:--|:--|
| **O. Freebug 2.0 (Network tab)** | Log de todos los `TAG_SUBREQ`/`TAG_RESULT` con estado, URL, tiempo, política aplicada. | Hito B (painter hook) | Medio |
| **P. Freebug 2.0 (Elements tab)** | Inspector DOM en vivo sobre el índice `dom_` + CSS calculado (`dd_format_css`). | Ninguna | Medio |
| **Q. User Scripts zero-trust** | API reducida: solo manipulación DOM (`document`, `Element`) + fetch gateado. Sin red propia, sin almacenamiento. Cargados desde `~/.config/freedom/userscripts/`. | Ninguna | Medio |
| **R. Buscar en página (`/`)** | Overlay Cairo de coincidencias sobre display list. `n`/`N` para saltar. | Hito B | Bajo |

**Driver:** Freebug 2.0 convierte a Freedom en un navegador utilizable para desarrolladores. User Scripts son el equivalente de extensiones sin la superficie de ataque de Chrome.

---

#### FASE 5: UX Cotidiano + Seguridad

| Hito | Descripción | Dependencias | Esfuerzo |
|:--|:--|:--|:--|
| **S. Gestor de contraseñas** | Autocompletado sobre `profile.c` + master passphrase (Argon2id). Datos desencriptados solo en memoria. | Hito 10 (existente) | Alto |
| **T. Sincronización E2EE vía Tor** | Sincro de marcadores/historial/prefs cifrados. Servidor .onion autoalojado. Reusa `tls_impersonate` para transporte. | Hito 10 (existente) | Muy alto |
| **U. Passphrase maestra (opt-in)** | Desbloqueo del perfil con passphrase que resiste acceso total al directorio. Mismo contenedor `local_store`. | Hito 10 (existente) | Medio |
| **V. Back-stack persistente entre sesiones** | Historial de navegación (atrás/adelante) sobrevive al cierre, no solo la omnibox. | H 10 (existente) | Bajo |

**Driver:** Gestor de contraseñas y sincro hacen de Freedom un daily driver. La passphrase maestra protege contra acceso al disco.

---

#### PENDIENTE DE FONDO (sin iniciar)

- `colspan`/`rowspan` en tablas
- `position:sticky` con scroll real
- `right`/`bottom` insets
- `grid-template-rows` y `grid-row: span N` (columnas ya cerradas)
- Import/export de bookmarks
- `pledge`/`unveil` para OpenBSD
- Scroll suave (smooth scroll)
- `defer`/`async` en `<script src>`

## 8. Reglas para el asistente (IA)

- Aplica el ciclo completo de §3 **en orden**: spec → test rojo → código verde → refactor →
  validación (ASan) → fuzzing → documentación. No te saltes pasos ni adelantes implementación sin
  spec+test, y no documentes antes de validar y fuzzear.
- **Falla cerrado.** Ante la duda de seguridad, rechaza; nunca degrades una garantía por conveniencia.
- No introduzcas dependencias nuevas sin justificarlas por reducción de superficie de ataque, y nunca
  `liboqs`/`oqsprovider` (OpenSSL nativo cubre PQC).
- Sé honesto sobre lo no verificado: el código de red/GUI que no se pueda ejercitar aquí se marca como
  pendiente de prueba de integración / verificación visual, no como verificado.
- Verifica que cada símbolo/flag/algoritmo existe en este host antes de recomendarlo
  (`openssl list ...`, `pkg-config ...`).
- Comandos nuevos van al **Makefile** (única fuente de verdad), no a scripts sueltos que se
  desincronizan (ver §5).
- Modo **boyscout**: resolver deuda técnica y fallos de seguridad nunca está fuera de scope, siempre
  sin perder funcionalidad.
- **Doctrina `malloc(n+1)` fail-closed (V-001):** todo patrón `malloc(len + 1)` → `memcpy(dst, src, len)`
  debe llevar un `if (len == (size_t)-1) return NULL;` antes de `malloc`. `len + 1` sin esa guarda
  revienta el heap cuando `len == SIZE_MAX` (wrap a 0, `malloc(0)` devuelve puntero válido, `memcpy`
  escribe `SIZE_MAX` bytes). Aplica a `dup_bytes`, `dup_n`, `host_dup` y cualquier helper análogo
  que aparezca. La guarda cuesta 0 en runtime y es defensa en profundidad aunque el llamador acote
  la longitud. Esta regla se verifica en code review y vale también para `realloc(n * sizeof(T))` y
     cualquier suma/tamaño cuya fuente sea remotamente controlable.
- **Doctrina `calloc` sobre `malloc` para arreglos (V-002):** todo patrón de asignación de
  múltiples arreglos del mismo tamaño (`malloc(n * sizeof(T))` para varios punteros) debe
  usar `calloc(n, sizeof(T))` en lugar de `malloc(n * sizeof(T))` para garantizar
  zero-initialization y prevenir lecturas de memoria no inicializada. Además, toda operación
  `memcpy(dst, src, len)` donde `len` sea un valor en tiempo de ejecución debe llevar una
  verificación explícita de que `len` no excede el tamaño del destino, ya sea por cota
  conocida (check antes del malloc/realloc) o por guarda inmediata antes del memcpy.
  `calloc` cuesta lo mismo que `malloc` (la memoria ya viene zeroed del kernel por razones
  de seguridad) y previene fugas de información por páginas no inicializadas. Esta regla se
  verifica en code review y aplica a archivos nuevos y existentes (boy-scout: nunca está
   fuera de scope arreglar un V-002 donde se encuentre).
- **Doctrina de buffer encadenado (V-003):** todo acumulador/acopiador de datos cuyo tamaño
  no sea estrictamente acotado por un límite de protocolo (p. ej. un solo campo de formulario)
  debe implementarse como una **cadena de bloques de tamaño fijo** (linked list de bloques de
  64 KiB por defecto), donde cuando un bloque se llena se asigna otro. Esto evita límites
  artificiales que pueden romper páginas legítimas y previene que contenido hostil fuerce una
  asignación contigua enorme. El único límite es OOM de `malloc`. NO usar un solo buffer que
  crece con `realloc` (riesgo de fragmentación / OOM en asignación contigua grande). NO poner
  un tope duro tipo "#define ..._MAX  (1024u * 1024u)" — la cadena de bloques escala sin tope
  excepto la memoria disponible. El patrón es `ih_block`/`ih_acc` en `dom.c:805`:
  un callback que recibe chunks y los copia al bloque actual, allocando un nuevo bloque
  encadenado cuando se llena, y un `ih_flatten` final que recorre la cadena y produce un solo
  buffer contiguo. Esta regla se verifica en code review y aplica a todo nuevo recolector de
     datos cuyo tamaño sea controlado por contenido remoto.
- **Doctrina `snprintf` fail-closed (V-004):** nunca usar `n += (size_t)snprintf(buf + n, rem, ...)` sin
  verificar que `rem` no se desbordó. `snprintf` retorna el número de bytes que *habría* escrito (no el
  real); si ese valor >= `rem`, hubo truncamiento y `n` crece más allá de la capacidad → en la siguiente
  iteración `rem` wrappea a un valor enorme y la escritura desborda el buffer. El patrón correcto es:
  `size_t space = cap - n; if (space == 0) break; int r = snprintf(buf + n, space, ...);
  if (r < 0 || (size_t)r >= space) { n = cap; break; } n += (size_t)r;`. Esta regla se verifica en
  code review y aplica a todo `snprintf`/`vsnprintf` cuyo tamaño dependa de un acumulador.
- **Este archivo nunca debe superar ~150.000 caracteres** (`wc -c CLAUDE.md`). Es doctrina, no
  sugerencia: un `CLAUDE.md` que crece sin límite deja de leerse. El historial de hitos cerrados
  (§7.2/§7.3) se comprime a **una línea por hito** (título + resultado en una frase + `[[link]]` a
  la memoria persistente del agente o a `spec/`) apenas se cierra; el detalle extenso vive en la
  memoria (`~/.claude/projects/.../memory/freedom-*.md`), en `spec/<modulo>.md` y en `git log`,
  nunca en prosa acumulada aquí. Si al documentar un hito nuevo el archivo se acercaría al límite,
  comprimí hitos viejos **antes** de añadir el nuevo, no después.
