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
| Red/TLS | `secure_fetch` (`sf_`) | TLS 1.3 mínimo, KE híbrido PQ preferido, validación de cadena; cada redirección re-aplica TODA la política (Zero Trust). |
| URL/enlaces | `url` (`url_`), `link_nav` (`ln_`) | RFC 3986; "qué es una https absoluta válida" y "qué hace un clic" en un solo sitio; downgrade a http / esquemas ajenos no representables. |
| Política de red | `request_policy` (`rp_`), `render_policy` (`rdp_`) | Bloqueo de terceros por defecto, https-only, gate puro de imágenes/CSS/JS (todo opt-in). |
| Filtro de hosts | `hostblock` (`hb_`) | Lista negra + lista blanca en formato `/etc/hosts` (archivos `.conf`); la blanca gana y cubre subdominios; consultado antes de abrir el socket. Puro, falla **abierto** (adblock, no frontera de seguridad). |
| Enrutado de red | `net_realm` (`nr_`) | Clasifica clearnet / `.onion` / `.i2p` y decide ruta (directo / Tor SOCKS5h / I2P HTTP / **bloqueado**). Puro. Aislamiento de realm + **fail-closed** (nunca fuga `.onion` por clearnet). `secure_fetch` aplica el proxy (`sf_proxy_*`). |
| Parser | `html_parse` (`hp_`), `dom` (`dom_`) | DOM inerte con Lexbor, strip de `<script>`/`on*`; índice consultable de solo lectura. |
| JS/anti-FP | `js_sandbox`/`js_dom`/`js_env`, `anti_fp` | QuickJS-ng vendorizado sin I/O; bindings sellados; relojes/pantalla normalizados; readback de canvas/audio envenenado **por origen** (`fp_origin_key(session_key, eTLD+1)`, no enlazable cross-origin). |
| Aislamiento | `os_sandbox` (`os_`), `tab` (`tab_`) | **fork + exec del worker** (re-ejecuta `/proc/self/exe` como `--tab-worker`: NO hereda COW del padre → un worker no ve el contenido de las otras pestañas; ASLR fresca; higiene de fds vía `close_range`) + seccomp-bpf fail-closed (con **W^X**: `mmap`/`mprotect` con `PROT_EXEC` denegados por inspección de argumento → sin shellcode nativo aun tras secuestro de control) + **anti-volcado** (`PR_SET_DUMPABLE`=0 + `RLIMIT_CORE`=0, sin core ni ptrace ajeno) + Landlock + **namespaces por pestaña** (`unshare` user/net/ipc/uts, best-effort defensa en profundidad); worker por pestaña que parsea/decodifica/ejecuta contenido hostil; el padre sobrevive. |
| Estado cifrado | `local_store`, `disk_store`, `prefs` (`prefs_`), `profile` (`profile_`) | AEAD (AES-256-GCM/ChaCha20) + Argon2id; escritura atómica 0600 (Zero Knowledge). Perfil persistente (preferencias + marcadores + historial): modelo puro `prefs` (codec versionado fail-closed, fuzzeado) sellado por `profile` con clave por dispositivo; nada legible en disco, AUTH-fail ⇒ defaults sin clobber. |
| Render | `page_view` (`pv_`), `render_doc` (`rd_`), `css` (`css_`), `css_color` (`cc_`) | Display list inerte → bloques pintables; presentación de autor solo con `caps.css`; `src` de imagen resuelto contra el origen. Acerca al render moderno (puro, con tests): **acentos** (byte inválido → Windows-1252 → UTF-8, no `?`), **énfasis inline** (`b/strong/th`→negrita, `i/em`→cursiva), **listas** (`ul/ol/li` con marcador `•`/`N.` + sangrado por anidamiento), **tablas** (`td/th` = celda recolectada, agrupadas como **grid** reusando `box_tree`), **CSS de autor** (`<style>` + `style=`: color/fondo/`text-align`/`font-size`/`line-height`/`font-weight`/`font-style`/`display`; selectores simples/compuestos **+ combinadores descendiente/hijo**; `display:none` oculta; **nunca telefonea a casa** — `url(`/`@`-reglas descartadas) y **modo sin distracciones**. |
| CSS de autor | `css` (`css_`) | Parser + cascada pura del CSS del **webmaster** (`<style>` + `style=`). Subconjunto simple (selectores de tipo/`.clase`/`#id`/`*`/grupos **+ combinadores descendiente `A B` e hijo `A > B`** + **selectores de atributo** `[attr]`/`[attr=v]`/`~=`/`\|=`/`^=`/`$=`/`*=` con flag `i`/`s` (Hito 23b-4, hasta `CSS_MAX_ATTR_SEL` (4) por compuesto, especificidad +10 c/u) — hasta `CSS_MAX_COMPOUNDS` (4) compuestos, especificidad = suma; **+ combinadores hermanos `+`/`~` y pseudo-clases** (Hito 23b-9, motor extraído a `css_select` (`csel_`)): `:link`/`:any-link` (ZK: sin historial, todo link no-visitado), `:visited` parsea y **jamás matchea** (ZK, sin sniffing de historial); `:hover`/`:focus`/`:active`/`:focus-within`/`:focus-visible` parsean y **siempre matchean** (`PSEUDO_ALWAYS`, 2026-07-11: contenido oculto tras hover se vuelve visible; la cascada se resuelve una vez por carga), `:root`, `:first-child`/`:last-child`/`:only-child`/`:nth-child(An+B)`/`:nth-last-child()` (contexto nth/nsib/prev de `css_element`; 0/NULL = desconocido = no matchea), `:checked`/`:disabled`/`:enabled`; pseudo desconocida y todo pseudo-elemento `::` descartan el selector (fail closed); whitelist de propiedades). **`!important`** honrado (Hito 23b-4): el sufijo se quita y la declaración sube a un **tier de cascada superior** que gana a toda no-importante sin importar especificidad (antes se **descartaba** por completo). Propiedades de **layout de contenedor** (`display:flex`/`grid` + `gap`/`justify-content`/`grid-template-columns`) resueltas por la **misma cascada** y consumidas por `page_view`: una hoja `<style>` maqueta columnas, no solo `style=` inline (Hito 23b-2). **`@media`** soportado (subconjunto: `prefers-color-scheme` → modo oscuro automático, `screen`/`print`/`all`, `min/max-width` contra ancho normalizado; `not`/desconocido falla cerrado). Contenido hostil: descarta `url(` y `@import`/`@font-face` (cero red), acotado (anti-DoS), falla cerrado, no ejecuta nada; fuzzeado. Los **colores** de autor siguen gateados por `caps.css`; la **maquetación** (flex/grid) se aplica siempre (estructura). **Box model** (`margin`/`padding`/`width`/`max-width`, Hito 23b-3): resuelto por la misma cascada (px/`0`/`em`·`rem`; `%`/vw/`calc` fallan cerrado), gateado por `caps.css` (una caja del autor puede encoger el contenido a lo ilegible → familia de presentación, no la de layout siempre-on); habilita la **columna de lectura centrada** (`max-width` + `margin: 0 auto` + padding). La geometría horizontal vive en `bx_place` (puro, en `box_style`). **`text-decoration`** (`underline`/`line-through`/`overline`/`none`, Hito 23b-5): OR de bits `CSS_DECO_*` resuelto por la misma cascada (palabras clave de línea; tokens de estilo/color/grosor ignorados; `none`=0 quita p.ej. el subrayado de un `<a>`), gateado por `caps.css` como los colores; el painter reutiliza la maquinaria de subrayado de los links y añade tachado/línea-superior. **Presentación de texto** (Hito 23b-6, gateada por `caps.css` salvo `list-style`): `font-family` (bucket genérico serif/sans/mono/cursive/fantasy), `text-transform`, `letter-spacing`, `word-spacing`, `text-shadow` (una capa), `opacity`, `vertical-align` (sub/super), `text-indent`, `white-space` (ajuste/no-ajuste) y `list-style-type` (marcador del `<li>`: disc/circle/square/decimal/alpha/roman); `font-family` mapea a familia genérica (sin casado exacto) y descarta `@font-face`/`url(`. Inventario soportado-vs-faltante en `spec/css.md`. |
| Imágenes | `image_decode` (`img_`) | Decodificado **PNG + JPEG + WebP + GIF estático dentro del worker confinado**; topes anti-DoS; salida ARGB lista para Cairo. JPEG es excepción de doctrina autorizada (libjpeg con fuente en memoria + `longjmp` que nunca llama `exit()`); GIF usa un decoder LZW **propio** en C puro (sin giflib — menos superficie, fuzzeado). |
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
- **`-fvisibility=hidden` es invariante de build (no quitar):** el binario `freedom` no exporta API,
  así que todos sus símbolos van **ocultos** del `.dynsym`. No es solo endurecimiento: un símbolo del
  ejecutable con visibilidad por defecto **preempta** al homónimo de una librería enlazada en TODO el
  proceso. Concreto: `hostblock` usa prefijo `hb_` y HarfBuzz (Hito 25) exporta un `hb_free` público
  → sin la flag, el `hb_free` del ejecutable secuestra el alocador de HarfBuzz y lo crashea dentro de
  `hb_shape`. La flag vive en `HARDEN` **y** en el `CFLAGS` de `asan` (asan no hereda HARDEN, y su build
  de `freedom` vía `test_freedom --download-pdf` también enlaza HarfBuzz). Ver `[[freedom-harfbuzz-shaping]]`.

### 7.2 Hitos cerrados (resumen)

> Este historial se comprimió a una línea por hito (2026-07-09) porque el detalle completo ya vive
> en la memoria persistente del agente (`~/.claude/projects/.../memory/freedom-*.md`, un archivo por
> `[[link]]`) y en `git log`. **Regla del archivo (§8):** nunca reinflar esta lista con prosa larga;
> un hito nuevo entra como una línea igual de corta, y el detalle va a spec/tests/memoria.

- **Hito 6 — Pulido interactivo GUI.** Temas claro/oscuro/sepia, hover, CSD, atajos vim. Verificado visualmente por el dueño.
- **Hito 7 — CSS estático / box model UA.** `box_style`+`flex_layout`+`box_tree` puros; pipeline DOM→cajas por `page_view`/`tab`/`render_doc`.
- **Hito 11 — Filtro de hosts.** `hostblock` puro (negra+blanca `/etc/hosts`, blanca gana y cubre subdominios, falla abierto); también override TLS por host.
- **Hito 12 — Tor/I2P a nivel de socket.** `net_realm` puro (clasifica y enruta, fail-closed) + `sf_proxy_*`. Verificado E2E. Ver `[[freedom-tor-i2p-integration]]`.
- **Hito 8 — Transcodificación de charset.** Byte inválido → Windows-1252 → UTF-8 (recupera acentos legados) en vez de `?`.
- **Hito 14 — Render moderno (listas/tablas/énfasis).** `bold/italic`, marcadores de lista + sangría, celdas de tabla como grid vía `box_tree`.
- **Hito 15 — Multi-pestaña.** Tira de tabs, `tab_save`/`tab_restore` mueven el estado vivo a `tab_slots[]` (ownership, no copia). Ver `[[freedom-multitab-save-restore]]`.
- **Hito 9 — Fetch asíncrono (página).** `fetch_thread` desacoplado + pipe no bloqueante + `net_gen` anti-obsolescencia; página previa navegable mientras carga. Ver `[[freedom-async-fetch]]`.
- **Hito (UI) — Teclado: auto-repeat + portapapeles.** `timerfd` de repetición (nunca en chords) + `wl_data_device` para Ctrl+V/C.
- **Hito 16 — Export a PDF vectorial.** `pdf_export` puro (nombre fail-closed, paginación) + `export_pdf` reusa `paint_content_row`. Ver `[[freedom-pdf-export]]`.
- **Hito (tooling) — Revisión visual headless + `/visual-review`.** `--download-pdf`/`ui_render_pdf` exportan la misma display list sin Wayland. Ver `[[freedom-visual-review-headless]]`.
- **Hito (tooling) — Export PNG headless.** `--download-png` (preferido sobre PDF: un solo bitmap, sin `mutool`). Ver `[[freedom-visual-review-headless]]`.
- **Hito (tooling) — `debug_dom`.** `dd_format`/`--dump-dom` vuelca el árbol paint-ready; diagnosticó que HN se rompía por layout de tabla, no `position`. Ver `[[freedom-debug-dom]]`.
- **Hito (UI) — Fix modo sin distracciones.** `content_margin_x` desacopla el eje horizontal del vertical (el bug pintaba la página fuera de la ventana). Ver `[[freedom-reader-mode-margin-axes]]`.
- **Hito 26 — `XMLHttpRequest`/`fetch` reales gateados por el padre.** Solo hosts allow∩js; el worker nunca toca el socket, el padre re-aplica toda la política. SOP-lock intacto. Ver `[[freedom-parent-gated-xhr]]`.
- **Hito 24 EXT — Scripts externos `<script src>`.** Corren para hosts allow∩js, fetcheados por el padre; fixes de esa validación: captura de grupo TLS en OpenSSL 3.6 (Ver `[[freedom-openssl-group-name-capture]]`), TZ del worker a UTC pre-seccomp, headless sigue navegación JS. Ver `[[freedom-external-scripts]]`.
- **Hito 23b (combinadores) — CSS descendiente `A B` e hijo `A > B`.** Cadena de compuestos, derecha-a-izquierda. Ver `[[freedom-css-combinators]]`.
- **Hito 17 — Namespaces OS por pestaña.** `unshare(user|net|ipc|uts)` best-effort antes de Landlock/seccomp. Ver `[[freedom-tab-namespaces]]`.
- **Hito 17b — Seccomp W^X + anti-volcado.** `mmap`/`mprotect` con `PROT_EXEC` denegados por inspección de argumento; `PR_SET_DUMPABLE=0`+`RLIMIT_CORE=0`. Ver `[[freedom-seccomp-wx-hardening]]`.
- **Hito 17d — Port seccomp a aarch64.** Allowlist y W^X ya portables (ABI genérica LE); source-complete, sin hardware ARM64 para itest aquí. Ver `[[freedom-seccomp-wx-hardening]]`.
- **Hito 17c — Worker fork+exec.** Re-ejecuta `/proc/self/exe --tab-worker` (sin herencia COW cross-pestaña) + `close_range` CLOEXEC. Ver `[[freedom-tab-fork-exec]]`.
- **Hito 18 — Identidad de red anti-fp + omnibox.** UA = `FP_USER_AGENT` (no "Freedom/0.1"); `url_omnibox` navegar-vs-buscar (DuckDuckGo HTML). Ver `[[freedom-anti-fp-network-identity]]`, `[[freedom-omnibox-search]]`.
- **Hito 19a — Origen `file://` local.** `url_resolve_file` confinado al subárbol del documento; imágenes locales resuelven contra ese origen. Ver `[[freedom-local-file-origin]]`.
- **Hito 19b (JPEG) — Decode JPEG en el worker.** Excepción de doctrina autorizada; libjpeg-turbo, fuente en memoria, `longjmp` nunca `exit()`. Ver `[[freedom-jpeg-decode]]`.
- **Hito 23b (line-height) — CSS `line-height` + `--author-css`.** Plantilla de plumbing para props heredadas de autor; el flag headless hizo revisable CUALQUIER `caps.css`. Ver `[[freedom-line-height]]`.
- **Hito 20 — Allowlist de JS por dominio.** `js_policy` (`jsp_enabled`) + `js.conf` (reusa `hostblock`) → `caps.js` por `tab_load_ex`. Ver `[[freedom-js-allowlist]]`.
- **Hito 20b/c/d/20e·1 — JS vivo.** Ejecución de scripts + DOM escribible memory-safe (detach-nunca-free) + construcción/eventos-timers sintéticos + `innerHTML` + storage/cookie efímeros ZK + `location.*` real con navegación gateada por `ln_resolve`. Ver `[[freedom-live-js]]`.
- **Hito 22 — Zoom + recarga + descargas.** `zm_`(ladder 50-300%) + `dl_`(nombre fail-closed reusando `pe_safe_basename`, 0600 atómico). Ver `[[freedom-zoom-download]]`.
- **Hito 23 — CSS de autor + modo sin distracciones.** Cascada pura `css_`, `url(`/`@`-reglas descartadas, `Ctrl+D` reader. Ver `[[freedom-author-css-direction]]`.
- **Hito 23b·1 — `@media`+`prefers-color-scheme`.** Ancho normalizado anti-fp fijo; `not`/desconocido falla cerrado. Ver `[[freedom-author-css-direction]]`.
- **Hito 23b·2 — flex/grid desde `<style>`.** `gap`/`justify-content`/`grid-template-columns` por la misma cascada, no solo inline. Ver `[[freedom-author-css-direction]]`.
- **Hito 23b-3 — Box model de autor.** `margin`/`padding`/`width`/`max-width`; `bx_place` puro. Habilita columna de lectura centrada. Ver `[[freedom-author-box-model]]`.
- **Hito 23b-4 — Selectores de atributo + `!important`.** `[attr op=v]` (4 ops + flag i/s) + tier de cascada superior para `!important`. Ver `[[freedom-css-attr-selectors-important]]`.
- **Hito 23b-5 — `text-decoration`.** underline/line-through/overline/none; `a{text-decoration:none}` quita el subrayado. Ver `[[freedom-author-css-direction]]`.
- **Hito 23b-6 — 10 props de presentación de texto.** `font-family`(bucket)/`text-transform`/`letter-spacing`/`word-spacing`/`text-shadow`/`opacity`/`vertical-align`/`text-indent`/`white-space`/`list-style-type`. Ver `[[freedom-text-presentation-css]]`.
- **Hito 23b-7 — Resolución de valores de layout.** `position`/`border`/`box-sizing`/`box-shadow`/flex-y-grid-por-item resueltos en `css_style` (~40 campos); pintarlos es el Hito 23b-8. Ver `[[freedom-author-css-layout]]`.
- **Hito (render) — Tablas anidadas.** Solo celdas HOJA se recolectan como run; `<tr>`=bloque; degrade honra `block_break`. Ver `[[freedom-nested-table-rendering]]`.
- **Hito (render) — Tablas de navegación fluyen + `bgcolor`.** Celda con ≥2 anclas se recorre (links sobreviven); `bgcolor` legacy = fallback de `background`. Ver `[[freedom-nav-tables-and-bgcolor]]`.
- **Hito 27 — Hojas de estilo externas.** `<link rel=stylesheet>` vía `TAG_SUBREQ` gateado por el padre; cerró un hueco Zero-Trust real (`tab_subreq_permitted`). Ver `[[freedom-external-stylesheets]]`.
- **Hito 25 — Shaping de texto HarfBuzz.** Ligaduras/kerning GPOS/formas contextuales; lado confiable únicamente, fuentes locales. `-fvisibility=hidden` fix de colisión de símbolos. Ver `[[freedom-harfbuzz-shaping]]`.
- **Hito 23b-9 — Pseudo-clases + hermanos `+`/`~`.** Motor extraído a `css_select`; `:link`/`:nth-child`/`:checked`; celdas recolectadas ahora resuelven CSS de autor. Ver `[[freedom-css-pseudo-classes-siblings]]`.
- **Hito (keystone) — `node_id` estable + click dispatcher.** Mapea pixel pintado → nodo vivo; `addEventListener('click')`/`onclick` re-derivan la vista. Ver `[[freedom-box-engine-and-dispatcher]]`.
- **Hito Stage 3 — Flex por-item.** `grow`/`shrink`/`basis`/`order`/`flex-direction` de extremo a extremo; whitespace hijo-directo ya no emite ítem fantasma. Ver `[[freedom-flex-per-item]]`.
- **Hito (render) — Whitespace inter-bloque + `cont_item`.** Runs de solo-espacio que abrirían bloque no se emiten; Wikipedia 25.337→18.809px. Ver `[[freedom-interblock-whitespace-cont-item]]`.
- **Hito (JS moderno) — `querySelector` real + superficie ambiente + caps de red.** Mismo motor `css_select` que las hojas; `URL_MAX_LEN`→8192 (bundles reales). Ver `[[freedom-js-modern-web-surface]]`.
- **Hito (JS moderno) — `URL`/`URLSearchParams` + gate de tipo de `<script>` + `DocumentFragment`.** Slashdot JS 14→0 errores. Ver `[[freedom-url-api-and-script-type-gate]]`.
- **Hito (render) — `float`/`clear`.** Bandas side-by-side que ANIDAN en el box stack (no cierran cajas); arregló las franjas grises de Slashdot. Ver `[[freedom-float-layout]]`.
- **Hito (CSS) — `var()`/`calc()`/`repeat()`/`minmax()`/`flex-wrap`/`align-items`/`row-gap`.** Custom properties page-global; bug real de tokenizer de shorthand encontrado y unificado. Ver `[[freedom-css-layout-expansion]]`.
- **Hito (CSS) — `visibility`/`overflow`(pintado)/`cursor`/`text-overflow`/`word-break`.** `visibility:hidden` reserva espacio sin pintar; `overflow:hidden` clipea in-flow rows + positioned boxes (2026-07-09); gap conocido: anidamiento flex/grid dentro de `hidden`. Ver `[[freedom-visibility-overflow-cursor-textwrap]]`.
- **Hito (CSS 2026-07-10) — Auditoría del pipeline CSS→pintura + Tier-2 carried.** Se cableó el resto del pipeline css_style hasta el GUI: `tab_size` (expansión en `<pre>`, 0→8 por defecto), `direction`, `font-variant: small-caps` (v1 = mayúsculas), `list-style-position`, `min_width`/`min_height`/`max_height`/`height` (cajas con esos solos campos se registran y se honran en `open_box`/`close_top_box`), `aspect-ratio` (siza la altura a partir del ancho), `box-shadow: inset` (ahora se pinta, no solo outset). Tier 2 documentado en `spec/css.md`: `background-image*`/`compositing`/`color-scheme`/`interaction`/extras de flex-grid/`table-*` se parsean y portan en `css_style` pero la v1 no los pinta. Ver `[[freedom-css-pipeline-audit-tier2]]`.
- **Hito (CSS 2026-07-10) — Math functions + propiedades lógicas + shorthands + cableado pe/ir/caret/cv.**
  `min()`/`max()`/`clamp()` (valor completo y dentro de `calc()`), propiedades lógicas
  (`margin-inline`/`padding-block`/`inset-inline`/`inline-size`… → mapeo físico LTR), `place-items`/
  `place-content`/`place-self`, `gap: <row> <col>` (2 valores → `row-gap`+`gap`; `interp_gap` ahora usa
  `interp_len`: em/rem/calc correctos, junk falla cerrado), shorthand `font`, `white-space: break-spaces`.
  Cableado a pintura de 4 props que morían en `css_style`: `pointer-events: none` (skip de hit-test por
  cadena de cajas, como `cursor`), `image-rendering: pixelated` (filtro NEAREST en `paint_image_row`),
  `caret-color` (tinte del caret del input enfocado), `content-visibility: hidden` (pliegue a
  `visibility` en el box def). `pv_set_text_ext` refactorizada a struct (`pv_text_ext` pública) — la
  firma posicional de 20 ints era deuda. IPC: +2 int32 de run, caja 50→51. Verificado con PNG headless
  (clamp/logical/gap/font/cv); filtro de imagen, caret y hit-test unit-tested pero pendientes de
  verificación visual en sesión viva. Ver `[[freedom-css-math-logical-and-wiring-batch]]`.
- **Hito (CSS) — Caps de `css.c` 16x + `pv_style_cache` (2026-07-09).** Auditoría real
  contra un sitio propio (LazyOwn C2, Bootstrap 4.5.2 vendorizado) mostró que
  `CSS_MAX_RULES` (384) descartaba en silencio casi todas las utility classes
  (`.bg-dark`, `.text-success`...) de una hoja real de ~2100 reglas — el síntoma era
  "la página ignora tus clases de color" sin ningún error. Subidos 16x (384/512/2048 →
  6144/8192/32768 para rules/sels/decls). Emparejado con `pv_style_cache` nuevo en
  `page_view.c` (memoiza `cch_element_style()` por puntero de elemento — un ancestro
  compartido se re-resolvía antes una vez por CADA descendiente) para que el cap más
  grande no multiplique el runtime de `page_view` por cada nodo de texto de la página;
  medido en el sitio real: sin regresión perceptible (~0.4-0.9s headless). Sigue
  siendo un tope finito (anti-DoS), solo dimensionado para una hoja real de librería
  en vez de una de juguete. Ver `spec/css.md` §Security posture.

- **Hito 28 — Doctrina trusted-host.** allow∩js ⇒ `caps.css`+`caps.images` automáticos (`jsp_trusted` pura; reader gana; JSP_ON global no basta). Ver `[[freedom-trusted-host-full-caps]]`.
- **Hito 29 — Prefetch paralelo (pipeline no bloqueante).** Pre-scanner lookahead puro (fuzzeado) + pool pthreads en el lado confiable; stylesheets/scripts/imágenes en paralelo bajo el mismo fetcher gateado; worker intacto; E2E suma→máximo (4 ms de dispersión). Ver `[[freedom-prefetch-parallel-pool]]`.
- **Hito 10 — Perfil persistente cifrado (preferencias + marcadores + historial).** `prefs` (puro, fuzzeado) + `profile` (clave por dispositivo Argon2id→`disk_store`, fail-closed sin clobber); la GUI aplica al arrancar (env gana por sesión), guarda al cambiar, `Ctrl+B` marca, `about:bookmarks` lista (HTML escapado, render confinado), la omnibox sugiere marcadores+historial antes que favoritos; "Remember history" OFF olvida lo retenido. E2E weston: tema oscuro+zoom cargados del perfil sellado. Ver `[[freedom-profile-persistence]]`.
- **Hito (paint 2026-07-11) — `border-radius` redondeado + `linear-gradient`.** `box_path` Cairo (sombra/fondo/outline siempre; anillo de borde solo si uniforme) + gradiente lineal puro (gramática sin URL, shorthand resetea ambos canales, 2-4 stops, IPC de caja 58 int32). Ver `[[freedom-gradient-radius-paint]]`.
- **Hito (grid 2026-07-11) — Pesos `fr`/px por track + `grid-column: span N`.** `fx_grid_columns_weighted` (px fijos primero, resto proporcional a fr) + `fx_grid_place_span` (span que no cabe salta de fila); track sizes por la misma cascada (`grid_col_w[8]`), viajan en `pv_run`. Span de FILA sigue sin colocarse. Ver `[[freedom-grid-fr-span]]`.
- **Hito (layout 2026-07-11) — `box-sizing: border-box` consumido.** `bx_content_cap` (puro): el cap de ancho descuenta padding+border horizontales antes de `bx_place`; sin padding/border los dos modelos coinciden, así que el único sitio es `open_box`. Ver spec/box_style.md.
- **Hito 19b (GIF + WebP) — GIF estático con decoder PROPIO + WebP vía libwebp.** GIF: LZW acotado en C puro (~300 líneas, sin giflib), primera frame, paletas/transparencia/interlace; goldens contra Pillow; fuzz-img. WebP: libwebp vía `WebPDecodeBGRAInto`, dimensiones acotadas antes del decode, lossless + lossy, sniff `RIFF....WEBP`; Makefile extendido con `WEBP_CFLAGS`/`WEBP_LIBS`. Afordancia `FREEDOM_IMAGES=1`. Ver `[[freedom-gif-decoder]]`.
- **Hito 20e·2 (parcial) — Timers async REALES + getter de `innerHTML`.** Timers con delay virtual: el reloj solo avanza cuando el padre confiable manda `OP_TICK` (`tab_tick`; el worker no puede auto-despertarse — anti-fp y anti-abuso); `tab_page.next_timer_ms` programa el próximo tick (GUI: timeout del event loop, cap 240/carga; headless: pump de 8 ticks). `innerHTML` getter serializa hijos acotado a 1 MiB (fail closed). E2E: setTimeout encadenado renderiza en el PNG. Ver `[[freedom-async-timers-innerhtml]]`.
- **Hito (doctrina 2026-07-11) — PSEUDO_ALWAYS: `:hover`/`:focus`/`:active` ahora siempre matchean.** Contenido oculto tras `:hover` (Slashdot, menús) se vuelve visible sin re-cascada interactiva. `:visited` se queda PSEUDO_NEVER (ZK). Cambio simple: ~5 líneas en `css_select.c`/`.h`. Ver `[[freedom-pseudo-always]]`.
- **Hito (doctrina 2026-07-11) — Presentation-trust: allow.conf sin JS ya habilita CSS+imágenes.** Nueva `jsp_present_trusted` pura: un host en allow.conf recibe autor-presentation sin necesidad de JS. JS/red siguen doble-gateados (allow∩js). Ver `[[freedom-presentation-trust]]`.
- **Hito 19b (WebP) — WebP decoder vía libwebp.** Nuevo `IMG_FMT_WEBP` + `img_decode_webp()` con sniff `RIFF....WEBP`, WebPGetInfo anti-bomb, WebPDecodeBGRAInto → premultiplied BGRA. Tests goldens + fail-closed. Ver `[[freedom-webp-decoder]]`.
- **Hito (2026-07-12) — Cookies de sesión en memoria para hosts allow∩js.** `document.cookie` real en el worker (`jd_set_cookies`/`jd_get_cookies`, jar deshabilitado=no-op por defecto → ZK) + `sf_cookie_header_for`/`sf_cookie_put` sobre el jar CURLSH (excluye HttpOnly/expirados) + puente IPC OP_LOAD (cookies-in tras URL, dump-out en el tail) + seed/foldback en GUI y headless, gateado a trusted. Efímeras (mueren al cerrar la app), sin romper ZK/ZT. Google sigue con su muro botguard (documentado). Ver `[[freedom-session-cookies-trusted-spa]]`.
- **Hito (search 2026-07-12) — SPA de DuckDuckGo → endpoint no-JS + fixes de shim JS.** `url_search_rewrite` (puro, testeado) reescribe `duckduckgo.com/?q=` a `html.duckduckgo.com/html/?q=` en el choke point (`do_load`/`fetch_and_render_one`); shim JS: `document.nodeType===9`+`defaultView`, `element.attributes` NamedNodeMap (`dom_attribute_names` en C), `Intl` stub ⇒ consola de la SPA de 3→0 errores (beneficia toda la web jQuery/Intl). Boy-scout: extinguido stack-use-after-scope pre-existente en `headless_load_hosts` (buffer de bloque interno aliaseado por `dirs[2]` y leído fuera de scope; ASan lo cazaba). Ver `[[freedom-search-spa-noscript-rewrite]]`.
- **Hito 30b (2026-07-12) — Blend-in surface para Google/Facebook/YouTube.** La superficie `navigator` se completa con `plugins`/`mimeTypes`/legacy props/`onLine`/`cookieEnabled`/`maxTouchPoints` (valores normalizados Firefox, `anti_fp` puro); `window.crypto` con `getRandomValues` (real, `getrandom`) + `randomUUID` (UUIDv4 real) + `subtle` stub; `navigator.permissions.query` stub; `screen.orientation`; headers HTTP `Sec-Fetch-*`/`Accept`/`DNT` en `sf_perform`; campos nuevos `sf_config.referrer_url/sec_fetch_dest/sec_fetch_mode`. `boy-scout`: `sf_config_default` ahora hace `memset(0)` para toda la struct (antes dejaba `progress_ctx`/`progress_cb` sin inicializar). `JS_GetTypedArrayBuffer` evitado por leak de GC en QuickJS-ng; acceso a buffer vía `.buffer` property. 19 tests js_env + 14 anti_fp + 49 secure_fetch, ASan/UBSan limpio. Ver `[[freedom-blend-in-surface]]`.
- **Hito M0.1 (2026-07-15, modernización Fase 0) — Modelo de capacidades unificado (`webcaps`).** Módulo puro `wc_` que deriva la tabla COMPLETA de caps de una página (`js`/`css`/`images`/`net`/`cookies` + forward `persist`/`readback`/`gpu`/`sw`/`rtc`) de las señales de confianza, reusando los predicados de `js_policy` (no reimplementa membership). Doctrina de gating (owner): leak-free (`js`/`css`/`images`) global por toggle o presentation-trust; privacy-sensitive doble-gateado `allow.conf ∩ js.conf` (`jsp_trusted`). Reemplaza la derivación inline repartida en los 2 chokepoints de caps del GUI (`render_current_ex`, `freebug_repl_worker`) y en headless (`render_page` vía `wc_from_flags`); `wc_render_caps` proyecta a `rdp_caps` sin tocar `rd_build`. Sin cambio de comportamiento (unificación); habilitador de los milestones de Fase 3/4. 10 tests webcaps + ASan/UBSan limpio; sin fuzz (no parsea contenido remoto, como `js_policy`). Ver `[[freedom-modernization-roadmap]]`, `spec/webcaps.md`.
- **Hito M0.2 (2026-07-15, modernización Fase 0) — Codec IPC de la vista por bloques bulk.** Refactor boy-scout de `write_view`/`read_view` (`src/tab.c`): el codec posicional de ~77 `write_full`/campo por run pasa a **bloques de `int32` de ancho fijo** (`head[6]`, block A[36], grid array, block B[26]) que listan cada campo **una vez**, igual que el `f[]` de la box-def; añadir un campo es una entrada en el write-block + una en la extracción del read (no ya 4 sitios en lock-step). **Formato de wire byte-idéntico** (orden verificado campo por campo) ⇒ sin cambio de comportamiento. **NO tags/versionado**: el worker es el MISMO binario que el padre (`/proc/self/exe --tab-worker`), nunca hay version skew que tolerar — TLV sería complejidad muerta (por eso el plan pedía TLV pero la impl honesta es bloques bulk). Guards del boundary hostil intactos (`read_field` capa a `TAB_MAX_INPUT`, count a `TAB_MAX_RUNS`). Boy-scout: cerró un **leak latente de `poster`** (no se liberaba en los error paths del read). Golden `test_load_view_codec_full_roundtrip` (spread ancho de campos de run + box, un valor mal-serializado cae en el slot equivocado) + ASan/UBSan limpio + visual review sin regresión. Sin fuzz nuevo: formato de wire inalterado ⇒ misma superficie de parsing que ya existía. Habilitador barato: baja a "una línea" el costo IPC de cada campo de los milestones de compositor/transform/canvas. Ver `[[freedom-modernization-roadmap]]`, `spec/tab.md`.

### 7.3 Roadmap — por cruzar

> Mismo criterio de compresión que §7.2: los sub-hitos ya **cerrados** dentro de un roadmap más
> grande (p. ej. Freebug FB-1..3, box engine Steps A-D/Stage 2-3) quedan en una línea con
> `[[link]]`; solo el trabajo **todavía abierto** conserva detalle suficiente para ser accionable.

- **Hito 24 — Freebug (consola JS).** **FB-1/FB-1b/FB-2/FB-3 CERRADOS:** captura de consola pura
  (`freebug`/`fb_`) + `--dump-console` headless + ventana Wayland propia (F12, verificada
  visualmente vía weston+Xvfb) + ubicación `file:line:col` por error. Ver `[[freedom-freebug-console]]`,
  `[[freedom-freebug-error-locations]]`. **Abierto:** consola por-pestaña persistente (hoy se limpia
  al cambiar de tab), auto-repeat en el editor del REPL, scroll-a-cursor multilínea.
- **Hito 9b — Fetch asíncrono (imágenes + multipestaña).** Las imágenes de una página ya bajan **en
  paralelo** (pool del Hito 29), pero la pasada completa (fetch+decode) aún bloquea el hilo de GUI
  hasta terminar; falta despacharla al fetch-thread y la carga concurrente entre pestañas (hoy una
  carga activa a la vez). Destraba I2P.
- **Hito 30 — Parse incremental / streaming (por iniciar).** `OP_LOAD` envía el documento entero;
  un parse por chunks (Lexbor lo soporta) exige rediseñar el protocolo y el ciclo de subreqs. El
  prefetch (Hito 29) ya entrega la mitad del beneficio (descarga temprana paralela) sin ese
  rediseño; el resto (DOM visible antes del EOF) es este hito.
- **Hito 31 — Compositor-lite (por iniciar).** Cachear la página pintada en una superficie Cairo
  offscreen y blitear en el scroll (hoy el display list se repinta por frame). GPU real/capas
  quedan fuera por doctrina: el worker no toca GPU y el pintado vive en el lado confiable.
- **Hito 19b — Imágenes: formatos + lazy.** JPEG y GIF estático cerrados (Ver `[[freedom-jpeg-decode]]`,
  `[[freedom-gif-decoder]]`). Falta: WebP (autorizado, bloqueado por `libwebp-dev` ausente en el host
  — `sudo apt install libwebp-dev` y sigue el patrón JPEG), SVG (evaluar superficie), GIF animado
  (necesita repintado por tiempo), lazy loading real. AVIF/AV1 NO autorizado.
- **Hito 20e parte 2 — JS vivo: lo que falta.** Cerrados: ejecución/DOM escribible/eventos-timers/
  `innerHTML` setter Y getter/`location`+nav/clic (Ver `[[freedom-live-js]]`,
  `[[freedom-box-engine-and-dispatcher]]`), scripts externos (Ver `[[freedom-external-scripts]]`) y
  **timers async reales** vía `OP_TICK` (Ver `[[freedom-async-timers-innerhtml]]`). Falta: `defer`/
  `async`/módulos ES en `<script src>`, scroll a ancla `#id`, repintado incremental en mutación,
  eventos distintos a click (keydown/submit).
- **Hito 21 — Buscar en página (`/` estilo Vim).** Overlay Cairo de coincidencias sobre el display
  list/runs (puro); `n`/`N` para saltar. No iniciado.
- **Hito 22b — Descargas/zoom: pulido.** Base cerrada (Ver `[[freedom-zoom-download]]`). Falta:
  barra de progreso + descarga async, anti-clobber (`(1)`), zoom por-sitio (el zoom global ya
  persiste desde el Hito 10; falta la variante por-sitio).
- **Hito 10b — Perfil: passphrase maestra (opt-in).** El Hito 10 cerró la persistencia cifrada con
  clave por dispositivo (keyfile junto al blob, como todo navegador sin master password); falta el
  desbloqueo opcional con passphrase que resista acceso total al directorio (mismo contenedor
  `local_store`, sin migración). También: restaurar el back-stack entre sesiones (hoy el historial
  persistente alimenta omnibox + `about:bookmarks`, no los botones atrás/adelante).
- **Hito 13 — Privacidad de red avanzada.** `http://` opt-in en `.onion`, auth de onion v3, stream
  isolation por pestaña/origen, indicador de realm en el chrome.
- **Hito 23b-8 (box engine, CERRADO v1).** Steps A-D (decoración de caja anidada) + Stage 2
  (`position`/z-index pintados) + Stage 3 (flex por-item) + Stage 4 parcial (clic). Ver
  `[[freedom-box-engine-and-dispatcher]]`, `[[freedom-flex-per-item]]`. **Abierto:** `grid-template-rows`
   reales, `grid-row: span N` (el de COLUMNA y los pesos `fr` cerraron 2026-07-11, Ver
   `[[freedom-grid-fr-span]]`), alineación de eje cruzado en GRID, `align-content`, más eventos del
   dispatcher, `right`/`bottom` insets, `position:sticky` con
   scroll real. **Negative z-index (two-pass painter) + overflow clipping para positioned boxes** CERRADOS (2026-07-09).
- **Hito (UI) — Host editing + omnibox autocomplete (CERRADO, verificación visual pendiente).**
  Ver `[[freedom-ui-host-editing-omnibox]]`.
- **Pendiente de fondo (hitos propios, sin iniciar):** `colspan`/`rowspan`, énfasis inline dentro de
  celda, sangría francesa real en listas, `pledge`/`unveil` OpenBSD.

#### CSS/JS de web moderna — auditoría 2026-07-09 (esta iteración)

El dueño pidió cerrar la brecha con sitios reales: CSS (transforms, animations, grid completo,
`position` pintado del todo, overflow clipping, flex avanzado, media queries completas) y JS
(fetch completo, Web Components, async/await completo, Service Workers, WebGL, Canvas avanzado,
IndexedDB) — probado contra un sitio propio real (panel LazyOwn C2 en `localhost:4444`, Basic Auth
+ login de sesión Flask, Bootstrap 4.5.2/particles.js/Chart.js/xterm vendorizados: exactamente el
perfil "no tan moderno" que ejercita ambos frentes). **Encontrados y CERRADOS esta sesión:** el
Hito "Caps de css.c 16x + pv_style_cache" de arriba — el `CSS_MAX_RULES` (384) descartaba en
silencio casi toda utility class de Bootstrap; era la causa real de "el sitio ignora mis colores/
fondos", no un gap de feature. **Overflow clipping + negative z-index** — añadido al painter en
`gui/browser_ui.c` (dos-pass painter con `ov_reconcile` por positioned box). Verificado E2E en
Wikipedia + test HTML. Ver `[[freedom-visibility-overflow-cursor-textwrap]]`. Estado del resto del
pedido:

- `transform`/`filter`/`animation`/`@keyframes`/`transition`: **arquitectónicamente fuera de
  alcance con el motor actual** (display-list plana pintada fila-por-fila, sin pipeline de matrices
  ni compositing por capa) — ver el "fuera de alcance" del Hito "CSS layout expansion" en
  `[[freedom-css-layout-expansion]]`. Añadirlos a medias sería deshonesto; requieren un rediseño del
  motor de pintado, no un parche.
- Grid `fr`/tracks con peso, `grid-column: span N`: **CERRADOS** (2026-07-11, ver `[[freedom-grid-fr-span]]`);
  queda `grid-row: span N` y `grid-template-rows` reales.
- `overflow` clipping (real): **pintado** (2026-07-09) — clipea in-flow rows + positioned boxes a rectos `overflow:hidden` ancestro; ver `[[freedom-visibility-overflow-cursor-textwrap]]`.
- `position:fixed/sticky` completos: `position`/z-index ya pintan (Stage 2); falta `sticky` con
  scroll real y `right`/`bottom`. **Nuevo hallazgo E2E** en el sitio real: con varias cajas
  `position:relative/absolute/fixed` anidadas el layout desborda el borde derecho del viewport y
  una caja parece pintarse dos veces (una franja gris duplicada arriba) — no diagnosticado a fondo
  todavía, candidato para el próximo hito de motor de cajas (relacionado con
  `[[freedom-box-engine-and-dispatcher]]`, pero es un caso nuevo, no el mismo bug ya cerrado ahí).
- `<pre>`: **CERRADO** — `page_view.c` aplica los UA-defaults `white-space:pre` +
  `font-family:monospace` y divide el texto en una línea por `\n` de origen (cada una con
  `block_break`), así ASCII-art y bloques de código renderizan línea a línea.
- Service Workers / IndexedDB / WebGL: en tensión directa con Zero Knowledge (persistencia real) y
  con "el worker no toca red/GPU" — necesitan una decisión de doctrina del dueño antes de
  implementarse, no son solo trabajo de ingeniería.
- `fetch`/XHR ya son reales para allow∩js (Hito 26); falta `arrayBuffer` binario real y streaming.
- Custom Elements: `customElements.define` hoy es no-op (sin upgrade/Shadow DOM); tratable como shim
  JS puro sin tocar el sandbox de red.

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
