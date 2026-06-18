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

Para cada módulo, el ciclo es inviolable:

1. **Spec** — `spec/<modulo>.md`: entradas, salidas, tabla de errores, garantías de seguridad,
   y qué queda fuera de alcance.
2. **Test (rojo)** — `tests/test_<modulo>.c` con CMocka. Debe **fallar** porque no hay
   implementación todavía.
3. **Code (verde)** — `src/<modulo>.c` con el código mínimo para pasar.
4. **Refactor** — endurecer punteros, límites, legibilidad, sin romper pruebas.
5. **Audit** — `make asan` (ASan+UBSan), `valgrind`, `cppcheck`.

**No escribas la implementación antes que la spec y el test.** No avances de hito sin que el
anterior esté verde y auditado.

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
- **Rechazos en toda política:** TLS < 1.3, KE no híbrido, **leaf (end-entity) con RSA < 3072**,
  y cualquier cert de la cadena firmado con SHA-1. El umbral RSA aplica solo al cert del sitio,
  no a los intermedios de CA (RSA 2048 universal en la Web PKI pública de 2026); SHA-1 es fatal
  en cualquier posición. Ver `spec/secure_fetch.md` §3.
- **Política por niveles** (ver `spec/secure_fetch.md`): `SF_POLICY_PQ_HYBRID_KE` (por defecto;
  exige KE híbrido, acepta certs clásicos válidos porque la Web PKI pública aún no tiene certs
  PQ en 2026) y `SF_POLICY_STRICT_PQ` (opt-in; exige además firma PQ en la cadena).
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
- `make clean`.

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

- **Hito 0** — Entorno seguro: build endurecido, CMocka/ASan/Valgrind. *(hecho: Makefile)*
- **Hito 1** — Núcleo de red y cripto: `secure_fetch` (TLS 1.3, KE híbrido, política PQC).
  *(cerrado: 40 tests + ASan/UBSan limpio + `make itest` verde contra endpoint PQ real que
  negocia `X25519MLKEM768`. Añadido seguimiento de redirecciones `sf_get_follow`: cada salto
  es un `sf_get` nuevo que re-aplica TODA la política PQ/TLS —Zero Trust—, lógica pura
  `sf_is_redirect_code`/`sf_parse_location_header`/`sf_resolve_redirect`, rechazo de downgrade a
  `http://` y de esquemas no-https, acotado a 10 saltos. Umbral RSA<3072 aplicado solo al leaf
  para no bloquear toda la Web PKI por sus intermedios RSA 2048.)*
- **Hito 2** — Parser/aislamiento con `Lexbor`: `html_parse` (DOM inerte, recorrido iterativo,
  strip de `<script>` y atributos `on*` por defecto). *(verde: 14 tests + ASan/UBSan limpio +
  278k runs de fuzzing sin crash)*
- **Hito 3** — Motor JS aislado: bridge C de superficie mínima; pruebas de escape de sandbox.
  *(verde: `js_sandbox` sobre QuickJS-ng v0.15.1 vendorizado en `third_party/quickjs/` sin
  `quickjs-libc`; sin I/O, límites de memoria/pila/tiempo; 18 tests + ASan/UBSan limpio +
  fuzzing sin crash. Pendiente: cableado del DOM inerte y APIs de navegador validadas.)*
- **Puente Hito 2→3** — `dom`: índice consultable (solo lectura) sobre el árbol de Lexbor;
  ids enteros en orden de documento (binary-search), `getElementById`/`by_tag`/`by_class` O(1),
  navegación de elementos. *(verde: 11 tests + ASan/UBSan limpio. Pendiente: mutación, selectores
  CSS completos, Shadow DOM.)*
- **Bridge DOM↔JS** — `js_dom`: global `dom` de solo lectura, sellado e infalsificable, expuesto
  al sandbox; nodos como handles enteros validados; sin objetos vivos ni mutación. *(verde: 10
  tests + ASan/UBSan limpio. Pendiente: objetos Node/`document`, eventos, `querySelector`.)*
- **Hito 4** — UI + hardening del SO: `Cairo`+`Wayland`; `seccomp-bpf`/`pledge`/`unveil`.
  *(endurecimiento del SO verde: `os_sandbox` confina syscalls con seccomp-bpf crudo —lista
  blanca fail-closed, KILL por defecto / ERRNO diagnóstico, guard de arch x86_64—; 6 tests
  (puros + fork: SIGSYS/EPERM) + ASan/UBSan limpio. Pendiente: `pledge`/`unveil`, `landlock`.)*
  UI `ui`: núcleo puro (word-wrap monoespaciado + scroll) verde —9 tests + ASan/UBSan limpio—;
  orquestador Wayland+Cairo (`gui/ui_render.c`, solo Wayland, `xdg-shell` vía `wayland-scanner`)
  + demo `gui/freedom_view.c` (`make view`, ejecutable `build/freedom-view <file.html>`), prueba
  visual del usuario. *(Pendiente: layout de cajas/CSS, fuentes proporcionales, teclado/IME.)*
- **Hito 5** — Auditoría y doctrina anti-vigilancia: modelo de amenazas documentado; mitigación
  explícita de fingerprinting (canvas, WebGL) y aislamiento de pestañas.
  *(cerrado: `spec/threat-model.md` documenta activos/adversarios/fronteras→mitigaciones;
  `request_policy` implementa Privacy by Default —bloqueo de terceros por defecto, https-only,
  fail-closed, 10 tests—. `anti_fp`: primitivas anti-fingerprinting puras —identidad normalizada,
  coarsening de relojes, bucketing de pantalla, perturbación de readback por sesión, 7 tests—.
  `renderer`: aislamiento de pestañas —parseo de contenido hostil en proceso hijo confinado con
  seccomp; el padre sobrevive, 7 tests—. `js_env`: cableado de `anti_fp` a las bindings JS
  —globales `navigator`/`screen`/`performance` sellados e infalsificables + `Date.now` coarsenado,
  identidad normalizada desde `anti_fp` (añadidos `fp_platform`/`fp_vendor`), pantalla bucketeada,
  relojes en rejilla de 100 ms, `canvas`/`audio` con readback envenenado por sesión (`fp_perturb`),
  coexiste con `js_dom`, 10 tests—. `local_store`: estado local cifrado (Zero Knowledge)
  —contenedor AEAD autodescriptivo con cabecera autenticada (AAD), AES-256-GCM/ChaCha20-Poly1305 +
  KDF Argon2id sobre OpenSSL nativo, nonce/sal aleatorios, fail-closed (autenticación fallida no
  libera texto plano), borrado seguro con `OPENSSL_cleanse`, 14 tests—. `disk_store`: persistencia
  en disco del estado cifrado de `local_store` —escritura atómica (temporal + `rename`), permisos
  0600, sin temporales huérfanos, manipulación en disco no libera texto plano, 9 tests—. `tab`:
  hijo de larga vida por pestaña + JS en el hijo —evoluciona el `renderer` one-shot a un worker
  bifurcado y confinado (Landlock sin FS *best-effort* + seccomp obligatorio/fail-closed) que parsea
  HTML hostil, construye el DOM inerte y ejecuta JS no confiable in-process contra ese DOM con las
  bindings `js_dom`/`js_env`; IPC framed petición/respuesta por tubería privada; el padre sobrevive
  a la muerte del hijo (`TAB_ERR_DEAD`), ignora `SIGPIPE` y valida longitudes anti-amplificación;
  14 tests (QuickJS+Lexbor verificados bajo seccomp). `browser`: estado puro de navegación GUI
  (historial Atrás/Adelante, barra de URL, edición de texto), 8 tests. `freedom`: entrada principal
  integrada con `make all`; por defecto abre una ventana Wayland con toolbar (botones
  Atrás/Adelante, barra de URL editable con teclado, área de contenido con scroll) que carga
  ficheros locales o URLs `https://` a través del worker `tab`; el modo `--headless` emite
  título+texto por stdout, ejercitando el mismo pipeline seguro, 6 tests. Todo ASan/UBSan limpio:
  16 suites, 400 tests. Renderizado GUI endurecido contra contenido malformado: `browser_set_page`
  y `ui_render` normalizan el texto a UTF-8 válido (bytes inválidos→`?`) y `ui_wrap_text` corta por
  límites de carácter, porque `cairo_show_text` rechaza UTF-8 inválido y dejaba la página en blanco
  (p. ej. Google sirve su home en Latin-1); fuga de fontconfig liberada en el teardown del GUI
  (`cairo_debug_reset_static_data`+`FcFini`). Pendiente fuera del hito: transcodificación de charset
  (mostrar acentos en vez de `?`), PSL completa (parcial), multiplexado de pestañas + eventos/timers
  asíncronos en el worker, paso de `session_key`/dimensiones desde el orquestador, mitigación de
  WebGL por ausencia, `pledge`/`unveil` en OpenBSD.)*
- **Puente Hito 5→render enriquecido** — `render_policy`: gate de capacidades de render
  (imágenes/CSS/JS) puro y sin I/O. Secure/Privacy by Default: `rdp_caps` con valor cero =
  baseline seguro (todo opt-in, imágenes OFF por defecto); `rdp_image_decision` reusa
  `rp_evaluate` (Zero Trust: revalida esquema/host por imagen) y, con imágenes activadas, aplica
  la postura "cargar todas salvo trackers" —cross-site permitido, bloqueo de píxel de rastreo
  (1x1 / diminuto / área cero vía `rdp_is_tracking_pixel`), no-https e inválidas fatales
  (fail-closed)—; `rdp_images_warning` para el aviso de rastreo de la UI. *(verde: 15 tests +
  ASan/UBSan limpio.)*
- **Render enriquecido cableado a pantalla** — la display list estructurada ahora llega de verdad
  al usuario, en GUI y `--headless` (antes el orquestador pintaba solo texto plano y descartaba la
  estructura, `render_policy` no estaba conectado y las imágenes eran invisibles). Piezas:
  `page_view` emite también runs `PV_IMAGE` (`PV_IMAGE` + `pv_append_image`, campos `src`/`img_w`/
  `img_h`; el `<img>` aporta `src`, `alt` y dimensiones declaradas —entero inicial de `width`/
  `height`, o −1—; el `src` se normaliza a UTF-8 seguro; nunca se descarga aquí). El IPC del worker
  `tab` transporta esos campos por run (write/read_view) con los topes anti-amplificación intactos.
  Nuevo módulo puro `render_doc` (prefijo `rd_`): convierte `pv_view` + `rdp_caps` + URL top-level
  en una lista de bloques lista para pintar (`RD_HEADING`/`RD_PARAGRAPH`/`RD_LINK`/`RD_IMAGE`/
  `RD_NOTICE`); aplica `render_policy` por imagen (Zero Trust, revalida por imagen; sin top-level
  https → falla cerrado) y antepone el aviso de rastreo (`RD_NOTICE` con `rdp_images_warning()`)
  siempre que la página declare imágenes con la capacidad apagada (defecto). Tanto `freedom
  --headless` como la GUI Wayland (`browser_ui`) consumen el MISMO `rd_doc` (DRY): el headless lo
  imprime como texto fluido determinista (encabezados `#`, enlaces `texto <href>`, placeholders de
  imagen `[image blocked: ...]`, aviso `! ...`); la GUI lo pinta con tema centralizado
  (`ui_theme`: tamaños, espaciados y colores, sin números mágicos) —encabezados escalados/negrita,
  enlaces en color+subrayado, párrafos con flujo en línea y wrapping, banner de aviso e imágenes
  como caja-placeholder con su decisión—, `Ctrl+I` alterna imágenes por sesión (Privacy by Default:
  off) y recarga para refrescar aviso/placeholders. Corregido de paso un bug latente: el scroll por
  rueda/teclado actualizaba un `static` distinto del que leía `paint()` (no hacía nada); ahora el
  desplazamiento es un offset en píxeles en el estado de la ventana (sin estado global mutable).
  *(verde: `page_view` 20 tests, `render_doc` 13 tests, `tab` 16, `freedom` 6; 19 suites / 250
  tests + ASan/UBSan limpio. Pendiente, honesto: descarga+decodificado+pintado de los BYTES reales
  de la imagen —requiere fetch https de subrecurso y un decodificador de formato (PNG/JPEG/WebP),
  una superficie de ataque grande, contraria a la doctrina de superficie mínima, y no verificable
  aquí; el gate, la decisión, el aviso y el placeholder ya están—; transcodificación de charset;
  persistencia del opt-in por sitio; motor de cajas CSS de autor y JS-vivo (mutación DOM→repintado)
  como hitos propios; verificación visual de la GUI en una sesión Wayland (aquí solo compila bajo
  los flags endurecidos, sin display para pintar).)*
- **Navegación de enlaces (clic → carga)** — los hiperenlaces renderizados ahora se pueden
  *seguir*. Lógica pura y testeable, orquestador que solo cablea. Piezas: `url` (prefijo `url_`):
  conocimiento canónico y único de "qué es una URL https absoluta válida" y "cómo resuelve una
  referencia (relativa / ruta absoluta / relativa al esquema / absoluta) contra una base" según
  RFC 3986 con colapso de segmentos `.`/`..`; rechaza el *downgrade* a `http://` y todo otro esquema;
  falla cerrado (resultado no-https no es representable). `secure_fetch` se refactoriza para delegar
  `sf_validate_url` y `sf_resolve_redirect` en este módulo (DRY: la regla que sigue una redirección
  es la misma que sigue un enlace), eliminando su copia duplicada de la lógica. (14 tests)
  `link_nav` (prefijo `ln_`): `ln_resolve(base, href, out)` decide qué hace un clic dado el `href`
  crudo del documento (dato hostil con procedencia, nunca instrucción) y la ubicación de la página:
  `LN_NAVIGATE` (https absoluta, o ruta de fichero local bajo base local), `LN_SAME_DOCUMENT`
  (vacío o fragmento `#...`) o `LN_BLOCKED` (downgrade, `javascript:`/`data:`/`file:`/`mailto:`, sin
  base resoluble, desbordamiento). Limpia el `href` (WHATWG: elimina TAB/LF/CR, recorta espacios),
  reusa `url_resolve_https` para enlaces https (DRY) y un normalizador de rutas que **preserva la
  relatividad** para ficheros locales (`examples/../README.md` → `README.md`, nunca `/README.md`,
  para que un `..` no convierta por accidente una ruta relativa en absoluta). Pura, reentrante,
  fail-closed. (17 tests) Cableado en `gui/browser_ui.c`: cada fragmento de enlace de la maqueta
  arrastra su `href` (alias, no propiedad); un clic en el área de contenido se *hit-testea* contra
  los fragmentos maquetados (`link_at_point`, que reusa exactamente la maqueta y el recorte de
  scroll del pintor para que el impacto coincida con lo que se ve) y `follow_link` pasa el `href`
  crudo por `ln_resolve` contra `browser_current_url`; solo con `LN_NAVIGATE` registra historial
  (`browser_navigate`) y carga (`do_load`), que re-aplica TODA la política TLS/PQ/cadena en cada
  salto (Zero Trust: la resolución no confía en el destino, se revalida al cargar). Un clic en un
  enlace de *downgrade*, esquema ajeno o fragmento no navega a ningún sitio (Secure by Default: el
  contenido hostil no puede provocar una carga insegura). Helper `content_geometry` compartido por
  el pintor y el hit-test (única fuente de verdad de la geometría, sin números mágicos). *(verde:
  21 suites / 281 tests + ASan/UBSan limpio; la GUI compila bajo los flags endurecidos, sin display
  para verificar el clic visualmente aquí.)*
- **Navegación enriquecida + menú de opciones + colores del autor** — pulido interactivo y render
  con color, lógica nueva en módulos puros y testeables; la GUI solo cablea. Piezas: `css_color`
  (prefijo `cc_`): parser puro de tokens de color CSS —`#rgb`/`#rgba`/`#rrggbb`/`#rrggbbaa` (alfa
  validado y descartado, opaco), `rgb()`/`rgba()` con enteros o porcentajes, y el conjunto extendido
  de colores con nombre por búsqueda binaria sobre tabla ordenada (148 entradas, dato de referencia)—,
  falla cerrado (`transparent`/desconocido/`hsl()` → `CC_ERR_SYNTAX`), sin asignación dinámica, 14
  tests. `link_nav` enriquecido: `ln_result` añade `reason` (`ln_block_reason` + `ln_block_reason_text`
  para el aviso exacto: downgrade / esquema ajeno / sin base / irresoluble) y `fragment` (el `#id` se
  separa por el primer `#`; la navegación actúa sobre la referencia limpia y el ancla se captura para
  un *scroll* futuro), 20 tests. `browser`: aviso transitorio (toast) acotado en el tiempo
  —`browser_set_status`/`browser_status_text` con reloj `now_ms` aportado por el llamante (puro,
  testeable), capacidad y duración en `BROWSER_STATUS_MAX`/`BROWSER_STATUS_DURATION_MS`, una navegación
  descarta un toast obsoleto—, 12 tests. Colores del autor de extremo a extremo: `page_view` extrae el
  `color` del ancestro más cercano (atributo `style` en línea —`background-color` nunca se confunde con
  `color`— o `<font color>`) vía `css_color` a un nuevo `pv_run.fg_rgb` empaquetado (`pv_set_color`); el
  IPC del worker `tab` lo transporta por run (capa fija anti-desync); `render_doc` lo propaga a
  `rd_block.fg_rgb` **solo si `caps.css`** (Secure/Privacy by Default: apagado), de modo que el *gate* de
  CSS vive en una función pura (page_view +2, render_doc +1, tab +1 tests). GUI (`gui/browser_ui.c`):
  botón de menú (hamburguesa) que abre un panel de opciones con casillas "Load images" y "Author colors
  (CSS)" mapeadas a `rdp_caps` por `offsetof` (etiquetas y flag en un único sitio, sin índices mágicos);
  al alternar se **re-renderiza desde una caché del HTML** (`set_cache`/`render_current`) sin volver a la
  red —corrige el patrón previo de Ctrl+I que re-descargaba—; toast que pinta `ln_block_reason_text` al
  pulsar un enlace inseguro y se auto-oculta vía un bucle de eventos `poll`+`prepare_read` con timeout
  igual a la vida restante del aviso; cursor de mano sobre enlaces (`wayland-cursor`, tema del sistema,
  sin rutas absolutas) + resaltado del enlace bajo el puntero (hit-test en movimiento); colores del autor
  pintados (override del color del tema conservando subrayado/negrita); todo el tema (colores del menú,
  resaltado, toast) centralizado en `ui_theme`. *(verde: 22 suites / 304 tests + ASan/UBSan limpio.
  Pendiente honesto: *scroll* al ancla del fragmento (requiere mapa de posiciones del documento);
  transcodificación de charset; persistencia del opt-in por sitio; la GUI compila bajo los flags
  endurecidos pero su verificación visual —menú, hover, toast, color— requiere una sesión Wayland real,
  no disponible aquí.)*

---

## 8. Reglas para el asistente (IA)

- Aplica el ciclo SDD+TDD: spec → test rojo → código verde → refactor → audit. No te saltes
  pasos ni adelantes implementación sin spec+test.
- **Falla cerrado.** Ante la duda de seguridad, rechaza; nunca degrades una garantía por
  conveniencia.
- No introduzcas dependencias nuevas sin justificarlas por reducción de superficie de ataque, y
  nunca `liboqs`/`oqsprovider` (OpenSSL nativo cubre PQC).
- Sé honesto sobre lo no verificado: el código de red que no se pueda ejercitar aquí debe
  marcarse como pendiente de prueba de integración, no presentarse como verificado.
- Verifica que cada símbolo/flag/algoritmo existe en este host antes de recomendarlo
  (`openssl list ...`, `pkg-config ...`).
