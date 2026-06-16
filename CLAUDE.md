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
