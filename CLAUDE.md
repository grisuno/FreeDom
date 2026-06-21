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
3. **Privacy by Default** — Bloqueo total de terceros a nivel del motor de red. Sin telemetría,
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

**Doctrina anti-vigilancia (Fase 5):** no se permite ninguna cadena de texto, dependencia,
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

## 3. Metodología: SDD + TDD estricto

Para cada módulo, el ciclo es inviolable y **en este orden**:

1. **Spec** — `spec/<modulo>.md`: entradas, salidas, tabla de errores, garantías de seguridad,
   y qué queda fuera de alcance.
2. **Test (rojo)** — `tests/test_<modulo>.c` con CMocka. Debe **fallar** porque no hay
   implementación todavía.
3. **Code (verde)** — `src/<modulo>.c` con el código mínimo para pasar.
4. **Refactor** — endurecer punteros, límites, legibilidad, sin romper pruebas.
5. **Validación** — `make asan` (ASan+UBSan) limpio, `valgrind`, `cppcheck`.
6. **Fuzzing** — el path que toca contenido remoto se fuzzea (libFuzzer: `make fuzz`/`fuzz-pv`/
   `fuzz-js`/`fuzz-img`; AFL++: `make fuzz-afl`). Cero crashes/leaks/UB antes de cerrar.
7. **Documentación** — **recién después de validar y fuzzear** se documenta: se actualiza la spec,
   este `CLAUDE.md` (hito → cerrado, doctrina nueva) y la memoria. Documentar antes de validar es
   documentar lo que todavía no es verdad. y casi mas importante actualizar docs/index.html ya que es el "home page" poner todos los atajos, etc.

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
- `make fuzz` / `fuzz-pv` / `fuzz-js` / `fuzz-img` — libFuzzer (parser HTML / display list
  `page_view` / sandbox JS / decoder PNG). `make fuzz-afl` — AFL++ sobre el binario headless.
- `make clean`.

**El Makefile es la única fuente de verdad de los comandos.** Los scripts `*.sh` que duplicaban
la compilación (y por eso se desincronizaban: `fuzz.sh` quedó obsoleto y dejó de compilar) ahora son
**wrappers delgados** que delegan a un target: `fuzz.sh`→`fuzz-afl`, `build_deb.sh`→`deb`,
`docker_run.sh`→`docker`, `run_freedom.sh`→`run`. Targets de desarrollo/empaquetado centralizados:
- `make deps` — dependencias del sistema + Lexbor desde fuente (subconjunto seguro de `install.sh`;
  **sin** los `sed` que mutan fuentes: un target jamás reescribe código versionado).
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
| Red/TLS | `secure_fetch` (`sf_`) | TLS 1.3 mínimo, KE híbrido PQ preferido, validación de cadena; cada redirección re-aplica TODA la política (Zero Trust). |
| URL/enlaces | `url` (`url_`), `link_nav` (`ln_`) | RFC 3986; "qué es una https absoluta válida" y "qué hace un clic" en un solo sitio; downgrade a http / esquemas ajenos no representables. |
| Política de red | `request_policy` (`rp_`), `render_policy` (`rdp_`) | Bloqueo de terceros por defecto, https-only, gate puro de imágenes/CSS/JS (todo opt-in). |
| Filtro de hosts | `hostblock` (`hb_`) | Lista negra + lista blanca en formato `/etc/hosts` (archivos `.conf`); la blanca gana y cubre subdominios; consultado antes de abrir el socket. Puro, falla **abierto** (adblock, no frontera de seguridad). |
| Enrutado de red | `net_realm` (`nr_`) | Clasifica clearnet / `.onion` / `.i2p` y decide ruta (directo / Tor SOCKS5h / I2P HTTP / **bloqueado**). Puro. Aislamiento de realm + **fail-closed** (nunca fuga `.onion` por clearnet). `secure_fetch` aplica el proxy (`sf_proxy_*`). |
| Parser | `html_parse` (`hp_`), `dom` (`dom_`) | DOM inerte con Lexbor, strip de `<script>`/`on*`; índice consultable de solo lectura. |
| JS/anti-FP | `js_sandbox`/`js_dom`/`js_env`, `anti_fp` | QuickJS-ng vendorizado sin I/O; bindings sellados; relojes/pantalla/readback normalizados. |
| Aislamiento | `os_sandbox` (`os_`), `tab` (`tab_`) | seccomp-bpf fail-closed + Landlock + **namespaces por pestaña** (`unshare` user/net/ipc/uts, best-effort defensa en profundidad); worker por pestaña que parsea/decodifica/ejecuta contenido hostil; el padre sobrevive. |
| Estado cifrado | `local_store`, `disk_store` | AEAD (AES-256-GCM/ChaCha20) + Argon2id; escritura atómica 0600 (Zero Knowledge). |
| Render | `page_view` (`pv_`), `render_doc` (`rd_`), `css` (`css_`), `css_color` (`cc_`) | Display list inerte → bloques pintables; presentación de autor solo con `caps.css`; `src` de imagen resuelto contra el origen. Acerca al render moderno (puro, con tests): **acentos** (byte inválido → Windows-1252 → UTF-8, no `?`), **énfasis inline** (`b/strong/th`→negrita, `i/em`→cursiva), **listas** (`ul/ol/li` con marcador `•`/`N.` + sangrado por anidamiento), **tablas** (`td/th` = celda recolectada, agrupadas como **grid** reusando `box_tree`), **CSS de autor** (`<style>` + `style=`: color/fondo/`text-align`/`font-size`/`font-weight`/`font-style`/`display`; selectores simples/compuestos; `display:none` oculta; **nunca telefonea a casa** — `url(`/`@`-reglas descartadas) y **modo sin distracciones**. |
| CSS de autor | `css` (`css_`) | Parser + cascada pura del CSS del **webmaster** (`<style>` + `style=`). Subconjunto simple (selectores de tipo/`.clase`/`#id`/`*`/grupos, sin combinadores; whitelist de propiedades). Contenido hostil: descarta `url(` y `@`-reglas (cero red), acotado (anti-DoS), falla cerrado, no ejecuta nada; fuzzeado. La presentación sigue gateada por `caps.css`. |
| Imágenes | `image_decode` (`img_`) | Decodificado **PNG dentro del worker confinado**; topes anti-DoS; salida ARGB lista para Cairo. |
| Formularios | `form` (`fm_`) | **GET/POST nativos sin JS**; target no-https no representable (fail-closed). |
| Export PDF | `pdf_export` (`pe_`) | **Guardar página como PDF vectorial** (texto seleccionable, zoom infinito). Puro: el nombre de archivo se deriva del **título hostil** saneado fail-closed (sin traversal/separadores/oculto) y la paginación es determinista; el orquestador (`export_pdf` en la GUI) solo hace la I/O de Cairo, reusando el mismo `layout_doc`/`paint_content_row` que la pantalla. |
| Descargas | `download` (`dl_`) | **Guardar recurso a `~/Downloads/freedom/`** (link no renderizable → se descarga, no se parsea; `Ctrl+S` guarda la página). Puro: decide render-vs-download (`Content-Disposition` attachment / media-type binario), deriva el nombre **fail-closed** del header/URL hostil (reusa `pe_safe_basename`), y aplica el cap de tamaño; el orquestador escribe atómico 0600. |
| Zoom | `zoom` (`zm_`) | **Zoom de página** `Ctrl++`/`Ctrl+-`/`Ctrl+0` (ladder 50–300%). Puro: clamp + escalón discreto + factor de escala; la GUI escala `theme.body_font` y la página reflowa al repintar (sin red). |
| UI | `ui`/`browser` (puros) + `gui/browser_ui.c` (orquestador Wayland+Cairo) | Toolbar, historial, barra de URL editable, scroll, menú de opciones, navegación por clic, submit de formularios. **Multi-pestaña** (tira de tabs entre titlebar y toolbar, `+`/cerrar/click, atajos `Ctrl+T`/`Ctrl+W`/`Ctrl+Tab`). El contenido va **recortado** (`cairo_clip`) al viewport bajo el chrome, así no se solapa con la toolbar al scrollear. **Save as PDF** (`Ctrl+P`), **descarga** (`Ctrl+S`/auto), **recarga** (`Ctrl+R`/`F5`), **zoom** (`Ctrl++`/`Ctrl+-`/`Ctrl+0`). |
| Auditoría | `spec/threat-model.md` | Activos/adversarios/fronteras → mitigaciones. |

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
- **Omnibox en la barra de URL:** `url_omnibox` (puro) decide navegar vs buscar — host desnudo ⇒
  `https://`, `http://` ⇒ promovido a https, esquema ajeno (`javascript:`/`file:`) ⇒ **búsqueda**
  (nunca ejecución, fail-closed), texto libre ⇒ DuckDuckGo HTML (sin JS). El orquestador (`go_omnibox`)
  resuelve primero un archivo local existente (la función pura no hace I/O). Ver `[[freedom-omnibox-search]]`.
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
  `""`/set no-op), `document.referrer` `""`, `history`/`location` stubs no-op — para que el JS de
  detección **corra sin lanzar** sin filtrar identidad. **Fuera de alcance:** eventos interactivos
  (clic), timers async reales, scripts externos (`src`), navegación por `location`, getter de
  `innerHTML`. No usar `lxb_dom_node_destroy` en mutadores (colgaría el índice). **No** persistir el
  storage ni poblar cookie/referrer con datos reales (rompería Zero Knowledge). Ver `[[freedom-live-js]]`.
- **Privacy by Default:** imágenes y colores de autor (CSS) **apagados**; opt-in en el menú
  (`Ctrl+I`). Imágenes solo **PNG** y fetch **síncrono**; otros formatos → placeholder (superficie
  mínima). El toggle de imágenes cubre **remotas y locales** por igual (una regla, fail-closed): un
  HTML local hostil tampoco autocarga nada hasta que el usuario habilita imágenes.
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
- **Modo boyscout:** un "fix" puede destrozar un módulo de seguridad; ante una regresión, diff
  contra el commit inicial antes de tocar nada. Ver `[[freedom-security-modules-butchered-by-fix-commits]]`.

### 7.2 Hitos cerrados (resumen)

- **Hito 6 — Pulido interactivo de la GUI.** Todo en `gui/browser_ui.c`: temas claro/oscuro/sepia +
  "Force theme colors", hover de botones/enlaces con cursor de mano, tira de `href` al pasar el
  cursor, indicador de carga ("busy"), barra de scroll arrastrable (gutter reservado), márgenes
  amplios, controles CSD (mover/maximizar/minimizar/cerrar/resize por bordes), atajos vim
  (`j`/`k`/`space`/`b`/`gg`/`G`). *(Compila endurecido; verificado visualmente en Wayland por el
  dueño.)*
- **Hito 7 — CSS estático / box model (Secure by Default, sin JS).** Módulos puros con TDD: `box_style`
  (caja UA por etiqueta), `flex_layout` (flex 1D + grid `repeat(n,1fr)`), `box_tree` (layout recursivo
  con colapso de márgenes). Pipeline DOM→cajas: `page_view` extrae contenedor/colores de autor, `tab`
  serializa por IPC, `render_doc` transporta (**layout siempre**; colores gateados por `caps.css`), la
  GUI dispone en columnas. `background-color` de autor. Demo `examples/flex.html`.
- **Hito 11 — Filtro de hosts.** Módulo puro `hostblock` (lista negra + blanca formato `/etc/hosts`,
  blanca gana y cubre subdominios, falla abierto). Cableado pre-fetch en la GUI; la blanca es además
  el **override de soberanía** por host (TLS 1.2 / cert débil-pero-válido vía
  `SF_POLICY_ALLOWLISTED_INSECURE`). Spec + tests + ASan.
- **Hito 12 — Privacidad de red (Tor/I2P) a nivel de socket.** Módulo puro `net_realm` (clasifica
  clearnet/`.onion`/`.i2p`, decide ruta, **fail-closed**) + proxy en `secure_fetch` (`sf_proxy_*`,
  SOCKS5h con DNS remoto / HTTP). `.i2p` acepta http (overlay autentica); redirects overlay resueltos
  en http. Toggles GUI + flags `--tor`/`--i2p`/`--torify` + env. Verificado E2E (jun 2026).
- **Hito 8 — Transcodificación de charset.** El sanitizer UTF-8 (gemelo en `page_view` y `browser`)
  ya no manda el byte inválido a `?`: lo reinterpreta como **Windows-1252** (superset de Latin-1) y lo
  reemite como UTF-8, recuperando acentos de páginas legadas sin charset declarado. Solo las 5
  posiciones indefinidas de CP-1252 caen a `?`. Puro, con tests; sin dependencia nueva.
- **Hito 14 — Render más cercano a un navegador moderno (puro, TDD).** En `page_view`→`render_doc`→IPC
  (`tab`)→GUI: **énfasis inline** (`bold`/`italic` desde `b/strong/th` e `i/em`; `content_font` con
  slant), **listas** (`indent` por anidamiento `ul/ol` + marcador `•`/`N.` antepuesto al primer run de
  cada `li`; la GUI sangra con `x_off`), **tablas** (cada `td/th` = un run recolectado anotado como item
  **grid** del `<table>`, reusando `box_tree`/`flex_layout`; `colspan/rowspan` fuera de alcance). Demo
  `examples/rich.html`. Fuzzeado (`make fuzz-pv`).
- **Hito 15 — Multi-pestaña.** En `gui/browser_ui.c`: arreglo **save/restore** — el estado por-página
  vive en los campos vivos de `browser_window` (los ~190 sitios de render/eventos no cambian) y
  `tab_save`/`tab_restore` mueven ese set a/desde `tab_slots[]` (transferencia de propiedad, sin copia
  ni free). Tira de tabs entre titlebar y toolbar (todo deriva de `toolbar_top()`, el contenido se
  reubica solo); `+`/cerrar/click; `Ctrl+T`/`Ctrl+W`/`Ctrl+Tab`. Las funciones UI usan prefijo `uitab_`
  para no chocar con el módulo `tab` (worker). Fix de solapamiento: `cairo_clip` al viewport de
  contenido. *(Compila endurecido + ASan limpio; verificación visual Wayland pendiente al dueño.)*
- **Hito 9 — Fetch asíncrono (página).** `do_load`/`do_submit_post` ya **no bloquean** el event loop:
  `prepare_fetch` (puro, rápido) corre en el hilo principal y el fetch bloqueante (`sf_get_follow`/
  `sf_post`) se lanza en un **hilo worker desacoplado** (`fetch_thread`) que NO toca `browser_window`
  (trabaja sobre un `fetch_job` con copias propias de cada string). El worker postea el `fetch_job*`
  por un **pipe no bloqueante** que el loop sondea junto al fd de Wayland y el timerfd; `deliver_fetch_
  result` renderiza en el hilo principal (Cairo/Wayland son single-thread). **Generación global**
  (`net_gen`): cada navegación y cada cambio de pestaña la incrementa, y un resultado con gen vieja se
  **descarta** (nunca pinta una página obsoleta ni en la pestaña equivocada). La página anterior queda
  **visible y navegable** mientras carga (como un navegador real); el spinner ahora **anima** (~12 fps).
  `sf_global_init` (nuevo, en `secure_fetch`) hace el init global de libcurl en el hilo principal
  (thread-safe). **POST también es async** y mantiene la paridad de ruta/fallbacks con el GET.
  *Fuera de alcance de este hito (siguen síncronos):* fetch de **imágenes** (opt-in, por eso no es el
  freeze común) y **carga concurrente entre pestañas** (modelo de una carga activa; cambiar de pestaña
  abandona la carga en vuelo). *(Compila endurecido + suite CMocka/ASan verde; verificación visual
  Wayland pendiente al dueño.)* Ver `[[freedom-async-fetch]]`.
- **Hito (UI) — Entrada de teclado: repetición y portapapeles.** En `gui/browser_ui.c`: **auto-repeat**
  de tecla (un `timerfd` en el poll; `key_is_repeatable` habilita edición/cursor/caracteres, **nunca**
  chords de Ctrl ni Enter; respeta `repeat_info`, fallback 600ms/25Hz) — mantener Backspace borra de
  corrido. **Portapapeles** (`wl_data_device`): **Ctrl+V** pega en el campo enfocado (barra de URL /
  input de página / UA; se filtran bytes de control), **Ctrl+C** copia el campo enfocado o la URL de la
  página; lectura acotada (1 MiB + timeout 500ms), `SIGPIPE` ignorado. *(Compila endurecido + ASan
  limpio; verificación visual Wayland pendiente al dueño.)*
- **Hito 16 — Export a PDF vectorial (Cairo).** Módulo **puro** `pdf_export` (`pe_`) con TDD: el
  **título de la página es contenido remoto hostil**, así que `pe_safe_basename`/`pe_build_path`
  derivan el nombre de archivo **fail-closed** (solo `[A-Za-z0-9._-]`, resto→`_` colapsado, recorte de
  bordes, sin traversal ni separadores ni oculto; fallback `page`), y `pe_paginate` reparte las filas
  en páginas **sin partir ninguna**. El orquestador `export_pdf` (`gui/browser_ui.c`) solo cablea
  Cairo: re-pinta el **mismo** `rd_doc` con el helper compartido `paint_content_row` (extraído de
  `paint_structured`, así pantalla y PDF son idénticos) sobre un `cairo_pdf_surface_t` (US Letter,
  tema claro forzado para print dark-on-white). Resultado: PDF con **texto seleccionable/buscable**
  (verificado E2E: `mutool` → 2 páginas, texto extraíble), no una captura. Disparadores: **`Ctrl+P`**
  y menú "Save as PDF". Sin dependencia nueva (`-lcairo` ya enlazado; `cairo-pdf.h`). Spec + 25 tests
  CMocka + ASan/UBSan limpio + fuzz (`make fuzz-pe`, 7.3M execs sin crash). *(El módulo puro está
  verificado; la ruta Cairo de la GUI compila endurecida y se probó la API E2E, pero la integración
  visual en Wayland queda pendiente al dueño.)* Ver `[[freedom-pdf-export]]`.
- **Hito 17 — Namespaces OS por pestaña (aislamiento del proceso worker).** Tercera capa de
  confinamiento bajo seccomp+Landlock: el worker de cada pestaña hace `unshare(CLONE_NEWUSER |
  CLONE_NEWNET | CLONE_NEWIPC | CLONE_NEWUTS)` recién forkeado, antes de Landlock/seccomp
  (`child_main` en `tab.c`). Superficie pura `os_namespace_flags` (espejo testeable de lo aplicado,
  como `os_policy_allows`) + enforcement `os_isolate_namespaces` en `os_sandbox`. **Best-effort
  defensa en profundidad** (no fatal: seccomp sigue siendo la frontera obligatoria, así que un host
  sin userns no privilegiado no rompe el navegador) — exactamente el criterio de Landlock. El worker
  **nunca usa la red** (el padre hace el fetch y pasa bytes), por eso `CLONE_NEWNET` le da una pila
  vacía: ni siquiera un bypass del filtro seccomp encontraría red. Sin uid maps (cero escrituras a
  `/proc`); requiere contexto monohilo (lo cumple el hijo recién forkeado). Spec (`os_sandbox.md`
  §9) + tests CMocka fork-based (la inode de `/proc/self/ns/net` cambia) + ASan/UBSan limpio;
  `test_tab` sigue verde (el worker parsea/ejecuta/decodifica dentro de los namespaces nuevos).
  *(Verificado: módulo puro + enforcement + integración del worker bajo test.)* Ver
  `[[freedom-tab-namespaces]]`.
- **Hito 18 — Identidad de red anti-fingerprinting + omnibox de búsqueda.** Dos cambios puros con
  TDD. (a) **Identidad de red:** `anti_fp` pasa a ser la **fuente única** de la identidad
  normalizada (macros `FP_USER_AGENT`/`FP_ACCEPT_LANGUAGE`/`FP_ACCEPT_LANGUAGE_HEADER` + nueva
  `fp_accept_language_header()`); `secure_fetch` repunta `SF_DEFAULT_USER_AGENT` a `FP_USER_AGENT`
  (incluye `anti_fp.h`) y envía `Accept-Language` normalizado en **toda** petición (antes solo había
  `Content-Type` en POST; ahora la slist se arma siempre). Así la UA de red **coincide** con
  `navigator.userAgent` y no se manda `"Freedom"` (huella + señal de bot que rompía Google). El
  placeholder del menú UA pasó a "anti-fingerprint default". (b) **Omnibox:** `url_omnibox` (puro)
  clasifica el texto de la barra en navegar (host desnudo→https, http→https) vs buscar (DuckDuckGo
  HTML sin JS); esquema ajeno→búsqueda (nunca ejecuta, fail-closed); query codificada en porcentaje.
  El orquestador `go_omnibox` (GUI) resuelve primero un archivo local existente (`access`) y cablea
  los 3 puntos de commit (botón Go + dos handlers Enter). Specs (`anti_fp.md`, `secure_fetch.md`,
  `url.md`) + tests (anti_fp identity, 6 tests de `url_omnibox`: navegar/host/upgrade/búsqueda/
  esquema-ajeno/nulls) + `make test`/`make asan` limpios + stress ASan/UBSan de 3M iters sobre
  `url_omnibox`. Docs: `docs/index.html` (logo relativo + tabla completa de atajos) y README.
  *(Módulos puros verificados; GUI compila endurecida, verificación visual Wayland pendiente al
  dueño.)* Ver `[[freedom-anti-fp-network-identity]]`, `[[freedom-omnibox-search]]`.
- **Hito 19a — Origen `file://` local + imágenes locales (el logo).** Una página de archivo recibe
  origen `file:///realpath` y "actúa como https": sus referencias relativas e imágenes resuelven
  contra ese origen. Núcleo puro en `url` (TDD): `url_is_file`/`url_file_path` y
  `url_resolve_file`, que resuelve `src` relativas/absolutas-locales **confinadas al subárbol del
  directorio del documento** (fail-closed: `../`, path absoluto fuera, scheme-relative o esquema
  remoto/ajeno → `URL_ERR_NOT_LOCAL`; colapsa dot-segments antes del prefijo, con barra final para
  que `/a/docsEVIL/` no pase). `render_doc` enruta las imágenes de páginas `file://` por esa función
  (decisión local separada del pipeline remoto: nunca telefonea a casa, mismo guard de tracking
  pixel); la GUI (`do_load` arma el origen con `realpath`; `load_images` lee del disco acotado con
  `read_file_bounded` y decodifica en el **worker**, como las remotas). `go_omnibox` acepta `file://`
  tecleado (lo normaliza a path). Las locales respetan Privacy by Default (opt-in `Ctrl+I`). Spec
  (`url.md`) + 4 tests nuevos de `url_resolve_file` (relativo/confinamiento/nulls) + `make test`/
  `make asan` limpios + stress ASan/UBSan 3M iters con invariante de confinamiento + verificación E2E
  (el `logo.png` de `docs/index.html` resuelve a un archivo legible; `../../etc/passwd` bloqueado).
  *(Núcleo puro verificado E2E; ruta GUI compila endurecida, verificación visual Wayland pendiente al
  dueño.)* Ver `[[freedom-local-file-origin]]`.
- **Hito 20 — Allowlist de JS por dominio (granular).** Espina de **política** pura + plumbing de
  `caps.js`. Módulo `js_policy` (`jsp_`): `jsp_enabled(mode, host_allowlisted)` combina un modo global
  tri-estado (`JSP_OFF`/`JSP_ALLOWLIST`/`JSP_ON`, defecto allowlist) con la pertenencia por host;
  `jsp_mode_from_str/str` para CLI/env. La allowlist por host **reusa `hostblock`** (`js.conf` cargado
  como `HB_LIST_ALLOW`, `hb_is_allowlisted` cubre subdominios). La GUI deriva `caps.js` por host de la
  página en `render_current` y lo pasa al worker con **`tab_load_ex(run_js)`** (nuevo; framing OP_LOAD
  = `[op][run_js:1][len][html]`, html zero-copy). El efecto **visible** hoy es el manejo de
  `<noscript>`: `pv_build_ex(doc, js_enabled, out)` muestra el fallback cuando JS está OFF (lo correcto
  en un navegador sin JS) y lo oculta cuando está ON; antes `<noscript>` se ocultaba siempre. Toggle en
  el menú (fila "JavaScript: off/allowlist/on" que cicla), CLI `--js[=MODE]` y env `FREEDOM_JS`; sample
  `config/js.conf`. Spec (`js_policy.md`) + tests (matriz off/allowlist/on, parser, roundtrip; 2 tests
  noscript en `page_view`) + `make test`/`make asan` limpios + fuzz del parser (2M iters, siempre un
  modo válido). **La EJECUCIÓN** de los scripts de páginas allowlisteadas queda para el hito de
  DOM-vivo: el puente `[[js_dom]]` es de **solo lectura** por diseño, así que correr scripts no podría
  mutar la página todavía; `caps.js` ya es el gancho. *(Núcleo puro + IPC verificados bajo test; ruta
  GUI compila endurecida, verificación visual Wayland pendiente al dueño.)* Ver
  `[[freedom-js-allowlist]]`.
- **Hito 20b — JS vivo: ejecución de scripts + DOM escribible seguro.** Con JS habilitado por host
  (Hito 20), el worker **ejecuta** los scripts inline y sus mutaciones aparecen en la página. Núcleo:
  (a) **DOM escribible memory-safe** en `dom` — `dom_set_text_content`/`dom_set_document_title` +
  lecturas `dom_text_content`/`dom_document_title`; el setter de texto **DETACHA** los hijos
  (`lxb_dom_node_remove`, jamás `destroy`), de modo que un handle del índice a un nodo removido sigue
  siendo válido (sale del árbol, no se libera) → **cero UAF**. (b) **Bridge `js_dom` ahora mutable**
  (`jd_install` toma `dom_index*` no-const) con métodos `setText/textContent/setTitle/getTitle` y una
  **fachada estándar `document`** inyectada como shim JS (`document.title`,
  `getElementById().textContent`, `getElementsByTagName/ClassName`, `window=globalThis`, `console`
  no-op) sobre handles enteros validados (sin objetos-nodo vivos). (c) **html_parse**:
  `hp_extract_scripts` (solo inline; excluye `src` externos y bloques `type=*json*`); `child_load`
  parsea con `strip_scripts=0` cuando `run_js`. (d) **tab**: `child_handle_load` ejecuta los scripts y
  **luego** deriva título/texto/vista (las mutaciones se reflejan); error JS no es fatal. Specs
  (`dom.md`, `js_dom.md`, `html_parse.md`, `tab.md`) + tests (5 en `dom`, 5 live en `js_dom` incl.
  detach memory-safe, 2 E2E en `tab` ejecutando un script que muta título+texto) + `make test`/
  `make asan` limpios + fuzz: `fuzz-js`/`fuzz-pv` sin crash + stress ASan/UBSan dedicado (60k programas
  JS aleatorios contra el bridge + re-render, sin UAF). *(Núcleo + IPC + ejecución verificados
  bajo test/ASan/fuzz; integración visual GUI pendiente al dueño.)* Ver `[[freedom-live-js]]`.
- **Hito 20c — JS vivo: construcción de DOM + eventos/timers sintéticos.** Sobre 20b: los scripts
  ahora **construyen y reestructuran** el DOM y corren código `onload`. (a) **`dom`** crece de forma
  memory-safe: `dom_create_element` (índice reallocable; nuevo handle consultable + indexado por tag),
  `dom_append_child` (detach-luego-append; **rechaza ciclos**, child ancestro de parent),
  `dom_remove_child` (detach, sigue válido), `dom_set_attribute` (re-indexa `id`/`class`). **Jamás**
  `lxb_dom_node_destroy` → cero UAF. (b) **`js_dom`**: métodos nativos `createElement/appendChild/
  removeChild/setAttribute` + la fachada `document` ampliada (wrappers con `appendChild`/`removeChild`/
  `setAttribute`/`id`/`className`, `createElement`, `body`/`head`/`documentElement`) y eventos/timers
  **acotados** (`addEventListener('load'|'DOMContentLoaded')`/`onload`/`setTimeout`/`setInterval`
  encolan; `__fireDeferred()` los vacía una vez, ≤64). (c) **tab**: tras los scripts, el worker evalúa
  `__fireDeferred()` y **luego** deriva la vista. Specs (`dom.md`, `js_dom.md`) + tests (5 construcción
  en `dom` incl. ciclo/reindex, 5 live en `js_dom` incl. onload/setTimeout, 1 E2E en `tab` que construye
  con `createElement`+`onload`) + `make test`/`make asan` limpios + **stress ASan/UBSan dedicado: 40k
  programas JS aleatorios de create/append/remove/setAttr/onload + re-render, sin UAF**.
  *(Núcleo + IPC + ejecución verificados bajo test/ASan/fuzz; integración visual GUI pendiente al
  dueño.)* Ver `[[freedom-live-js]]`.
- **Hito 20d — JS vivo: `innerHTML` + superficie ambiente identity-safe.** (a) **`innerHTML`** setter:
  `dom_set_inner_html` re-parsea un fragmento con `lxb_html_document_parse_fragment` (node como
  contexto), **detacha** los hijos viejos (no libera) e **indexa el subárbol nuevo** (queryable); los
  `<script>` del fragmento quedan inertes. (b) **Superficie ambiente identity-safe** (el punto del
  pedido: "JS moderno sin comprometer identidad/seguridad") — todo en el shim, sin filtrar nada:
  `localStorage`/`sessionStorage` **efímeros en memoria** (Zero Knowledge: nunca persisten),
  `document.cookie` (get `""`/set no-op), `document.referrer` `""`, `history` y `location` **stubs**
  no-op, `querySelector`→null. Así el JS de detección **corre sin lanzar** ReferenceError y sin que
  el dispositivo/usuario se filtre. Specs (`dom.md`, `js_dom.md`) + tests (1 `innerHTML` en `dom`,
  4 en `js_dom` incl. storage efímero/cookie vacío/stubs, 1 E2E `innerHTML` en `tab`) + `make test`/
  `make asan` limpios + stress ASan/UBSan (40k JS aleatorios con `innerHTML`/storage, sin UAF).
  **Honestidad sobre Google:** `google.com/search` exige **su JS externo propietario**, que Freedom
  **no ejecuta** (los scripts `src` externos no se descargan ni corren — frontera de seguridad **y**
  de identidad), así que su muro "enable JavaScript" puede persistir; la barra ya enruta búsquedas a
  DuckDuckGo HTML (Hito 18). *(Núcleo + ejecución verificados; integración visual GUI pendiente al
  dueño.)* Ver `[[freedom-live-js]]`.
- **Hito 22 — Zoom + recarga + descargas.** Tres features con dos módulos **puros** nuevos (TDD).
  (a) **`zoom` (`zm_`):** zoom como porcentaje entero que **engancha a un ladder** (50→300%);
  `zm_clamp`/`zm_zoom_in`/`zm_zoom_out`/`zm_reset`/`zm_scale`/`zm_apply` (esta última con piso de
  1px). Toda función clampa primero, así un valor fuera de rango no es representable. La GUI guarda
  `zoom_pct` por ventana, y `apply_theme` escala `theme.body_font`/`paragraph_gap`/`image_box_pad`;
  como el layout se recalcula en cada paint desde `w->theme`, el zoom es **rebuild+repaint** (sin red,
  sin worker). Atajos `Ctrl++`/`Ctrl+=`/`KP+` (in), `Ctrl+-`/`Ctrl+_`/`KP-` (out), `Ctrl+0` (reset).
  (b) **`download` (`dl_`):** el nombre de archivo se deriva de **input hostil** (`Content-Disposition`
  + path de la URL), así que es la superficie auditable: `dl_should_download` (attachment / media-type
  no renderizable vs `text/*`/xhtml/vacío → render), `dl_ext_for_type`, `dl_pick_name` (candidato
  disposition→URL→fallback `download`, saneado **reusando `pe_safe_basename`** — sin separadores, sin
  traversal, sin punto inicial; sintetiza extensión por content-type si falta), `dl_build_path`
  (rechaza `/` en el nombre, no escapa el dir), `dl_check_size` (cap 256 MiB). El orquestador
  (`save_download`/`ensure_download_dir`/`write_file_atomic` en la GUI) crea `~/Downloads/freedom/` y
  escribe **atómico 0600** (temp+rename). Auto-descarga cuando la respuesta no es renderizable (la
  página actual queda en pantalla); `Ctrl+S` guarda los bytes cacheados de la página (sin red).
  (c) **Recarga:** `Ctrl+R`/`F5` → `load_current` (re-fetch, re-aplica TODA la política TLS/PQ).
  **`secure_fetch`** gana dos campos additivos en `sf_response` (`content_type` vía
  `CURLINFO_CONTENT_TYPE`, `content_disposition` capturado en `header_cb`); solo lectura de cabeceras,
  no cambia ninguna decisión TLS/PQ/cadena; en `sf_get_follow` sobreviven los del hop final.
  Specs (`zoom.md`, `download.md`, `secure_fetch.md`) + tests (10 `zoom`, 20 `download`) + `make test`
  (34 suites) / `make asan` (34 suites, exit 0) limpios + fuzz `make fuzz-dl` (5.4M execs sin
  crash/leak/UB, invariante de contención del nombre sostenido). *(Módulos puros + IPC additivo
  verificados bajo test/ASan/fuzz; ruta GUI compila endurecida, verificación visual Wayland pendiente
  al dueño. `make itest` requiere endpoint PQ vivo, no disponible aquí.)* Ver `[[freedom-zoom-download]]`.
- **Hito 23 — CSS de autor (`<style>` + `style=`) + modo sin distracciones.** "Ver la web como la
  puso el webmaster", con un subconjunto deliberadamente más simple. (a) **Módulo puro `css` (`css_`)**
  con TDD: parsea una hoja acotada y resuelve un `css_style` por elemento por cascada
  (especificidad → orden de documento; inline gana). Selectores **simples/compuestos** (tipo, `.clase`,
  `#id`, `*`, grupos por coma; **sin combinadores**). Propiedades whitelisteadas: `color`,
  `background[-color]`, `text-align`, `font-size`, `font-weight`, `font-style`, `display`. **Seguridad
  (no negociable):** descarta cualquier valor con `url(` y **toda `@`-regla** → el CSS de autor **nunca
  telefonea a casa** ni abre balizas; acotado (anti-DoS), falla cerrado, no ejecuta nada. (b)
  **Integración en `page_view`** (`pv_build_full`): concatena los `<style>` del documento (≤1 MiB),
  parsea una vez, y en `resolve_context` fusiona el `css_style` del ancestro más cercano (la caminata de
  ancestros da herencia gratis); alimenta `fg_rgb`/`bg_rgb`/`bold`/`italic` y dos campos nuevos
  `text_align`/`font_scale`. `display:none` (de hoja o inline) **oculta** el subárbol
  (`in_hidden_subtree`, estructural, siempre); `<font color>` legacy queda como respaldo. (c)
  **IPC**: `text_align`/`font_scale` viajan por `tab.c` `write_view`/`read_view`; `render_doc` los
  transporta a `rd_block` **gateados por `caps.css`** como los colores. (d) **GUI**: pinta la
  alineación (`row_align_offset`, compartido por pintor y hit-test de enlaces) y el tamaño de fuente;
  el menú "Author colors (CSS)" pasa a **"Author styles (CSS)"**. (e) **Modo sin distracciones**
  (`reader`, **`Ctrl+D`** + ítem de menú): `pv_build_full(reader)` descarta `nav/header/footer/aside`,
  la GUI apaga `caps.css`/imágenes (sin tocar los toggles del usuario) y centra el contenido en una
  columna de lectura (`apply_theme` ensancha el gutter). Specs (`css.md`, `page_view.md`, `tab.md`,
  `render_doc.md`) + tests (19 `css`, 6 nuevos en `page_view`: hoja/align+font/bold+inline-gana/
  display:none/reader/setter) + `make test` (35 suites) / `make asan` (35 suites, exit 0) limpios +
  fuzz `make fuzz-css` (1M execs) y `fuzz-pv` (cascada CSS sobre HTML hostil) sin crash/leak/UB.
  **Fuera de alcance (v1):** combinadores/pseudo-clases/selectores de atributo; `url()`/`@`-reglas/
  `calc()`/`var()`/`!important`; box model de autor (margin/padding/width — sigue el UA);
  flex/grid desde `<style>` (los parámetros siguen viniendo del parser inline de `page_view`; solo
  `display:none` de `<style>` surte efecto). *(Módulos puros + IPC verificados bajo test/ASan/fuzz;
  ruta GUI compila endurecida, verificación visual Wayland pendiente al dueño.)* Ver
  `[[freedom-author-css-direction]]`.

### 7.3 Roadmap — por cruzar

- **Hito 9b — Fetch asíncrono (imágenes + multipestaña).** Sacar también las imágenes del hilo
  principal (hoy `load_images` hace fetch síncrono dentro del worker durante el render) y permitir
  **carga concurrente entre pestañas** (generación por pestaña en vez de global, entrega a la pestaña
  destino aunque esté en segundo plano). Destraba además I2P (lento de tejer túneles).
- **Hito 19b — Imágenes: formatos + lazy.** (Hito 19a, imágenes locales, ya cerrado arriba.)
  (b) **SVG** (¿`librsvg`? evaluar superficie de ataque) y **JPEG** (decoder en worker; contra la
  doctrina PNG-only salvo justificar la superficie). (c) **Lazy loading** (decodificar solo lo
  visible). Mantener Privacy by Default (opt-in `Ctrl+I`).
- **Hito 20e — JS vivo: lo dinámico real.** Cerrados 20b (ejecución + título/texto), 20c
  (construcción + eventos/timers sintéticos) y 20d (`innerHTML` + superficie ambiente identity-safe).
  Falta: **eventos interactivos** (clic del usuario → IPC GUI↔worker → handler JS → re-render),
  **timers async reales** (event loop en el worker que empuja vistas nuevas), **navegación por JS**
  (`location.href=`/`location.replace` → solicitud de navegación reportada a la GUI, vía secure_fetch),
  getter de `innerHTML` (serialización), `location.*` reales (requiere pasar la URL de la página al
  worker), scripts externos (`src`, con política de red), y **repintado incremental** en mutación.
  Persistir el modo y la allowlist con Hito 10.
- **Hito 21 — Buscar en página (`/` estilo Vim).** Resaltar todas las coincidencias con overlay
  Cairo suave; `n`/`N` para saltar. La lógica de matching es pura (sobre el display list/runs).
- **Hito 22b — Descargas/zoom: pulido.** (Hito 22, base, ya cerrado arriba.) Falta: ícono de recarga
  en la toolbar; barra/indicador de progreso de descarga y descarga **asíncrona** (hoy el cuerpo ya
  vino con el fetch async, pero la escritura es síncrona); evitar clobber (sufijo `(1)`); **fetch de
  imágenes** y descargas grandes fuera del hilo (depende del Hito 9b); zoom **por sitio** y persistido
  (Hito 10). Wart conocido: tras una auto-descarga la barra de URL muestra el recurso descargado
  aunque el contenido en pantalla sea la página previa.
- **Hito 10 — Persistencia de preferencias.** Opt-in de imágenes/CSS/tema, excepciones de host, y
  config Tor/I2P (hoy env/sesión) cifrados con `local_store`/`disk_store`.
- **Hito 13 — Privacidad de red avanzada.** `http://` opt-in también para `.onion`
  (`nr_realm_allows_http`); autenticación de onion services v3 con clave; **stream isolation** por
  pestaña/origen (circuitos Tor separados); unificar i2pd/router-Java; indicador de realm en el chrome.
- **Hito 23b — CSS de autor: más cobertura.** (Hito 23, base, ya cerrado arriba.) Falta: **combinadores**
  (descendiente/hijo/hermano) y pseudo-clases/selectores de atributo; **box model de autor**
  (margin/padding/width/border — hoy gobierna el UA); flex/grid **desde `<style>`** (hoy solo inline);
  `line-height`/`text-decoration`/`letter-spacing`; `!important`; persistir el toggle de estilos de autor
  y el modo reader con el Hito 10.
- **Pendiente de fondo (hitos propios):** motor de cajas CSS de autor completo (ver Hito 23b); JS-vivo
  (mutación DOM → repintado, eventos, timers); otros formatos de imagen
  (JPEG/WebP/GIF — superficie nueva, contra doctrina salvo justificación); `pledge`/`unveil` en
  OpenBSD; scroll al ancla de fragmento (`#id`); render: `colspan`/`rowspan` y énfasis inline
  **dentro** de celdas (hoy la celda se aplana a texto), sangría francesa real en listas, fetch
  de pestaña en background (carga concurrente entre tabs, depende del Hito 9).

---

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
