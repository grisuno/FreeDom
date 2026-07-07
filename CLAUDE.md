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
     autor (colores/cajas), `--js=on` para JS, `--tor`/`--i2p`/`--insecure` según haga falta.
  b. Lee la imagen con la herramienta Read: `Read $SP/frame.png`. (Fallback PDF: `--download-pdf` +
     `mutool draw -r 96 -o $SP/frame-%d.png $SP/frame.pdf`, o `Read` del PDF con `pages`.)
  c. Verifica:
    - ¿Se renderiza texto legible?
    - ¿Los elementos tienen posicionamiento correcto (no superpuestos)?
    - ¿Los colores/temas (sepia/oscuro) se aplican? (la exportación fuerza tema claro para imprimir
      oscuro-sobre-blanco; imágenes y colores de autor están OFF por defecto → placeholders.)
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
| Estado cifrado | `local_store`, `disk_store` | AEAD (AES-256-GCM/ChaCha20) + Argon2id; escritura atómica 0600 (Zero Knowledge). |
| Render | `page_view` (`pv_`), `render_doc` (`rd_`), `css` (`css_`), `css_color` (`cc_`) | Display list inerte → bloques pintables; presentación de autor solo con `caps.css`; `src` de imagen resuelto contra el origen. Acerca al render moderno (puro, con tests): **acentos** (byte inválido → Windows-1252 → UTF-8, no `?`), **énfasis inline** (`b/strong/th`→negrita, `i/em`→cursiva), **listas** (`ul/ol/li` con marcador `•`/`N.` + sangrado por anidamiento), **tablas** (`td/th` = celda recolectada, agrupadas como **grid** reusando `box_tree`), **CSS de autor** (`<style>` + `style=`: color/fondo/`text-align`/`font-size`/`line-height`/`font-weight`/`font-style`/`display`; selectores simples/compuestos **+ combinadores descendiente/hijo**; `display:none` oculta; **nunca telefonea a casa** — `url(`/`@`-reglas descartadas) y **modo sin distracciones**. |
| CSS de autor | `css` (`css_`) | Parser + cascada pura del CSS del **webmaster** (`<style>` + `style=`). Subconjunto simple (selectores de tipo/`.clase`/`#id`/`*`/grupos **+ combinadores descendiente `A B` e hijo `A > B`** + **selectores de atributo** `[attr]`/`[attr=v]`/`~=`/`\|=`/`^=`/`$=`/`*=` con flag `i`/`s` (Hito 23b-4, hasta `CSS_MAX_ATTR_SEL` (4) por compuesto, especificidad +10 c/u) — hasta `CSS_MAX_COMPOUNDS` (4) compuestos, especificidad = suma; **+ combinadores hermanos `+`/`~` y pseudo-clases** (Hito 23b-9, motor extraído a `css_select` (`csel_`)): `:link`/`:any-link` (ZK: sin historial, todo link no-visitado), `:visited`/`:hover`/`:focus`/`:active` parsean y **jamás matchean** (sin sniffing de historial, sin re-cascada interactiva), `:root`, `:first-child`/`:last-child`/`:only-child`/`:nth-child(An+B)`/`:nth-last-child()` (contexto nth/nsib/prev de `css_element`; 0/NULL = desconocido = no matchea), `:checked`/`:disabled`/`:enabled`; pseudo desconocida y todo pseudo-elemento `::` descartan el selector (fail closed); whitelist de propiedades). **`!important`** honrado (Hito 23b-4): el sufijo se quita y la declaración sube a un **tier de cascada superior** que gana a toda no-importante sin importar especificidad (antes se **descartaba** por completo). Propiedades de **layout de contenedor** (`display:flex`/`grid` + `gap`/`justify-content`/`grid-template-columns`) resueltas por la **misma cascada** y consumidas por `page_view`: una hoja `<style>` maqueta columnas, no solo `style=` inline (Hito 23b-2). **`@media`** soportado (subconjunto: `prefers-color-scheme` → modo oscuro automático, `screen`/`print`/`all`, `min/max-width` contra ancho normalizado; `not`/desconocido falla cerrado). Contenido hostil: descarta `url(` y `@import`/`@font-face` (cero red), acotado (anti-DoS), falla cerrado, no ejecuta nada; fuzzeado. Los **colores** de autor siguen gateados por `caps.css`; la **maquetación** (flex/grid) se aplica siempre (estructura). **Box model** (`margin`/`padding`/`width`/`max-width`, Hito 23b-3): resuelto por la misma cascada (px/`0`/`em`·`rem`; `%`/vw/`calc` fallan cerrado), gateado por `caps.css` (una caja del autor puede encoger el contenido a lo ilegible → familia de presentación, no la de layout siempre-on); habilita la **columna de lectura centrada** (`max-width` + `margin: 0 auto` + padding). La geometría horizontal vive en `bx_place` (puro, en `box_style`). **`text-decoration`** (`underline`/`line-through`/`overline`/`none`, Hito 23b-5): OR de bits `CSS_DECO_*` resuelto por la misma cascada (palabras clave de línea; tokens de estilo/color/grosor ignorados; `none`=0 quita p.ej. el subrayado de un `<a>`), gateado por `caps.css` como los colores; el painter reutiliza la maquinaria de subrayado de los links y añade tachado/línea-superior. **Presentación de texto** (Hito 23b-6, gateada por `caps.css` salvo `list-style`): `font-family` (bucket genérico serif/sans/mono/cursive/fantasy), `text-transform`, `letter-spacing`, `word-spacing`, `text-shadow` (una capa), `opacity`, `vertical-align` (sub/super), `text-indent`, `white-space` (ajuste/no-ajuste) y `list-style-type` (marcador del `<li>`: disc/circle/square/decimal/alpha/roman); `font-family` mapea a familia genérica (sin casado exacto) y descarta `@font-face`/`url(`. Inventario soportado-vs-faltante en `spec/css.md`. |
| Imágenes | `image_decode` (`img_`) | Decodificado **PNG + JPEG dentro del worker confinado**; topes anti-DoS; salida ARGB lista para Cairo. JPEG es excepción de doctrina autorizada (libjpeg con fuente en memoria + `longjmp` que nunca llama `exit()`). |
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
  (`Ctrl+I`). Imágenes **PNG y JPEG** (resto → placeholder) y fetch **síncrono**; el decode corre
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
- **Hito (tooling) — Revisión visual headless (`--download-pdf`) + skill `/visual-review`.** Para
  poder **inspeccionar visualmente** el render sin Wayland (CI / agente / este entorno), la GUI gana
  una salida headless que exporta la **misma** display list que pinta la pantalla a un PDF vectorial,
  sin abrir ventana. Refactor boyscout: el núcleo Cairo de `export_pdf` se extrajo a
  `write_doc_pdf(w, path)` (reusado por el "Save as PDF" del GUI **y** por el nuevo camino headless);
  `ui_render_pdf(doc, out_path, *pages)` (público en `include/ui.h`) arma un `browser_window` en cero
  (sin imágenes → placeholders, sin inputs, tema claro) y llama a `write_doc_pdf` — **no toca estado
  Wayland**. En `src/freedom.c`, `--download-pdf=PATH` (implica `--headless`) construye el `rd_doc` por
  el pipeline síncrono existente (`tab`→`rd_build`, mismas caps seguras: imágenes OFF) y escribe el
  PDF; el PATH es un argumento local de confianza, se usa tal cual (la sanitización fail-closed del
  título hostil, `pe_safe_basename`, sigue siendo solo del "Save as PDF" del GUI). La **skill**
  `.claude/skills/visual-review/SKILL.md` documenta el flujo: exportar → `mutool draw` a PNG → `Read`
  la imagen → checklist (texto legible, layout/listas/tablas/grid, énfasis inline, colores de tema,
  placeholders de imagen, artefactos). Spec (`freedom.md`) + 2 tests E2E nuevos en `test_freedom`
  (PDF local válido empieza por `%PDF`; `--download-pdf` sin `=PATH` → exit 2 fail-closed) + `make
  test` (35 suites) / `make asan` (35, exit 0; leaks de `libfontconfig` ya suprimidos por
  `tests/asan.supp`) limpios + **verificado E2E visual**: `examples/rich.html` (3pp) y
  `docs/index.html` (6pp) rasterizados y leídos — headings/párrafos/listas (`•`+sangrado)/tablas como
  grid/énfasis/enlaces/banner/botón se renderizan correctos, sin artefactos. Sin dependencia nueva
  (Cairo PDF ya enlazado; `mutool` es herramienta de validación, no del navegador). No se añade
  superficie de parseo de contenido remoto nueva (el HTML/CSS/título hostil sigue por
  `page_view`/`render_doc`/`pe_paginate`, ya fuzzeados); smoke headless sobre HTML adversario
  (vacío/título-sin-cerrar/grid y listas enormes) limpio bajo ASan. *(Núcleo + IPC + E2E visual
  verificados; la ventana Wayland interactiva sigue pendiente de verificación al dueño.)* Ver
  `[[freedom-visual-review-headless]]`.
- **Hito (tooling) — Export PNG headless + GUI "Save as PNG" (revisión visual más barata).** La
  revisión visual deja de depender del PDF: `--download-png=PATH` (y "Save as PNG (Ctrl+Shift+P)" en
  el GUI) exporta la **misma** display list a un **único PNG** (un `cairo_image_surface_t` ARGB de
  1000px de ancho, alto = contenido maquetado, acotado a 30000px anti-DoS, **sin paginar**), que el
  agente **lee en un paso** — mucho menos tokens que el PDF (que primero hay que rasterizar con
  `mutool`). Boyscout/DRY: `pe_build_path` se generalizó a `pe_build_path_ext(dir,title,ext,...)` (una
  sola superficie de saneo de nombre hostil fail-closed para `.pdf` y `.png`); `write_doc_png`/
  `ui_render_png` reusan `layout_doc`/`paint_content_row`/`paint_box_decoration` (idéntico a pantalla y
  PDF, tema claro forzado). Mismas reglas de Privacy by Default (imágenes off → placeholders). La skill
  `/visual-review` y la doctrina §3.5 ahora **prefieren PNG**; el PDF queda como fallback para el
  documento vectorial real. Spec (`freedom.md`, `pdf_export.md`) + tests (4 en `test_pdf_export` para
  `pe_build_path_ext`; 2 E2E en `test_freedom`: PNG local empieza por la firma PNG, `--download-png`
  sin `=PATH` → exit 2 fail-closed) + `make test`/`make asan` (exit 0) limpios + fuzz `make fuzz-pe`
  (7.4M execs, sin crash/leak/UB) + **E2E visual** (`examples/rich.html` y `box-model.html` con
  `--author-css` exportados y leídos directo del PNG). Sin dependencia nueva (`cairo_surface_write_to_png`
  ya viene con Cairo; `cairo-png` presente). *(Núcleo + E2E visual verificados; ventana Wayland
  interactiva pendiente al dueño.)* Ver `[[freedom-visual-review-headless]]`.
- **Hito (tooling) — `debug_dom`: dump del árbol de render (instrumento del "CSS paint gap").** Para
  dejar de adivinar **por qué** un nodo maqueta mal, módulo **puro nuevo `dom_debug` (`dd_`)** con TDD:
  `dd_format(rd_doc, buf, cap)` formatea el árbol paint-ready (`[[render_doc]]`) a texto determinista y
  **agente-legible** (Principio 6) — cada `rd_block` (kind, tag, flags, grupo de contenedor flex/grid,
  `box=#id`, estilo de autor) + el árbol de cajas (`rd_doc.boxes`: parent, placement, decoración). Puro,
  sin I/O: lee un `rd_doc` inerte y escribe un buffer del llamador con **cursor acotado** (jamás escribe
  más allá de `cap-1`, NUL-termina, devuelve la longitud sin truncar tipo snprintf); los bytes hostiles
  (text/href) salen por un escritor de campo que trunca a `DD_FIELD_MAX` y escapa bytes de control →
  un bloque = una línea, sin smear. Headless `--dump-dom` (implica `--headless`, honra `--author-css`
  para poblar las cajas; **no** corre JS — Secure by Default); imprime tras cualquier render, así
  `--dump-dom --download-png` da PNG **y** árbol por stdout (ambos MCP-visibles). Spec (`dom_debug.md`,
  `freedom.md`) + tests (7 en `test_dom_debug`: header/mapping/grid/box-tree/no-css/truncación-sin-
  overflow/bytes-de-control; 1 E2E en `test_freedom`) + `make test` (39 suites) / `make asan` (39, exit
  0) limpios + fuzz `make fuzz-dd` (19k execs, sin crash/leak/UB; invariantes de no-overflow + acuerdo
  medir-vs-escribir como traps). **Diagnóstico inmediato de `news.ycombinator.com`** (el sitio "se ve
  horrible"): el dump probó que **no es `position`/`z-index`** — las 30 historias colapsan en UN `<p>`
  (filas/celdas de tabla aplanadas) y el conjunto cae en `cont=#0(grid cols=3)`, que encoge todo a ~1/3
  del ancho (la columna de 270px). Es **layout de tabla**, no posicionamiento. *(Módulo puro + IPC-N/A +
  E2E headless verificados; panel de devtools GUI pendiente.)* Ver `[[freedom-debug-dom]]`.
- **Hito (UI) — Fix de modo sin distracciones (render fuera de la ventana).** El centrado del reader
  inflaba `w->theme.content_margin`, que es **también** el margen VERTICAL → en ventanas anchas la
  altura de contenido se volvía negativa y la página se pintaba fuera de la ventana (nada visible).
  Se desacoplaron los ejes: nuevo `content_margin_x(w)` (HORIZONTAL, lo usan `content_width` y el
  `left` de pintado/hit-test) aplica el centrado; `content_margin` queda como margen vertical base.
  Afordancia de verificación `FREEDOM_READER=1`. **Verificado en pantalla** (weston+Xvfb): boilerplate
  eliminado, columna centrada, contenido completo visible. Ver `[[freedom-reader-mode-margin-axes]]`.
- **Hito 26 — `XMLHttpRequest`/`fetch` reales con gateo del padre (la web moderna funciona para sitios
  de confianza).** Revierte —**solo para hosts en allow.conf ∩ js.conf**— la doctrina "sin red en JS":
  el JS de un sitio doblemente confiable obtiene `XMLHttpRequest` y `fetch` reales, pero **nunca toca
  el socket**. El worker confinado (sin red: `CLONE_NEWNET`+seccomp) proxya la petición al **padre
  confiable** por los pipes existentes (protocolo nuevo: tras `OP_LOAD`, el worker emite 0+ tramas
  `TAG_SUBREQ` antes de `TAG_RESULT`; el padre las sirve y responde), y el padre **re-aplica TODA la
  política** (hostblock/rastreadores, `net_realm` fail-closed, TLS-PQ con fallbacks) antes de buscar —
  un worker comprometido no alcanza un host bloqueado. **Plumbing:** `jd_fetch_fn`+`jd_install_xhr`
  (js_dom: native `__hostFetch` con la fn/ctx como closure data —sin global, sin leak— + shim JS de
  XHR/fetch; `__hostFetch` se borra del global tras capturarse); `js_pump_jobs` (js_sandbox: drena
  microtasks acotado, para que `fetch().then`/`await` resuelvan); `child_fetch` (worker: round-trip por
  pipe, caps `TAB_MAX_SUBREQ`=64 / `TAB_MAX_SUBRESOURCE`=8 MiB, activo **solo** en la ventana de
  scripts de la carga); `tab_set_fetcher`/`tab_set_net_allowed` + flag `net` en `OP_LOAD`; GUI
  `gui_subresource_fetch` (reusa `ln_resolve`/`hb_check`/`apply_route`/`fetch_*_navigable`) gateado por
  `caps.js && page_host_allowlisted`; headless `headless_fetch` gateado por `--js=on` (señal de
  confianza del operador). **El candado de SOP se mantiene:** `test_eval_no_network_or_cross_origin_api`
  corre con la red apagada y exige XHR/fetch `undefined` por defecto; 3 tests nuevos en `test_tab` candan
  la ruta gateada (funciona / undefined-sin-gate / **host bloqueado rechazado por el padre**). `make
  test` (38 suites, 0 fallos) / `make asan` (exit 0, sin leaks/UB en el round-trip del worker) limpios
  + **E2E real verificado** (`--js=on --dump-console`: XHR a `https://example.com/` → status 200, body
  559B con `<title>`; `fetch().then` → status 200 ok, body 559B; con JS off XHR/fetch `undefined`).
  **Límites v1:** síncrono bajo el capó (bloquea el worker / hilo de render del GUI durante el
  round-trip), activo solo en la carga (no REPL ni eventos post-carga; async real necesita event loop
  en el worker), respuesta como string UTF-8 (sin `arrayBuffer` binario), `Promise`/`await` vía
  `js_pump_jobs`. **Google:** XHR/fetch ya no lanzan "is not defined"; su JS externo propietario
  (`<script src>`) corre desde el **Hito 24 EXT** (abajo).
  Ver `[[freedom-parent-gated-xhr]]`, `[[freedom-js-network-and-media-authorized]]`,
  `[[freedom-sop-by-construction]]`, `[[freedom-live-js]]`.
- **Hito 24 EXT — Scripts externos `<script src>` por soberanía + la tanda de fixes que hizo
  navegar la web real (2026-07-04).** El worker ejecuta también los scripts **externos** de la
  página — **solo** para hosts doblemente confiables (**allow.conf Y js.conf** en GUI; `--js=on` del
  operador en headless) — **en orden de documento** intercalados con los inline. El worker **no toca
  la red**: pide los bytes por la misma trama `TAG_SUBREQ` del Hito 26 y el **padre confiable**
  re-aplica TODA la política (`ln_resolve` contra la URL real de la página — sin `file://`/downgrade —,
  hostblock/rastreadores, `net_realm` fail-closed, TLS-PQ). Gates del worker antes de evaluar (todo
  fail-closed, el script no corre y la carga sigue, con nota `FB_WARN` en Freebug): red concedida,
  status 2xx, **Content-Type de JS** (vacío o `javascript`/`ecmascript`; un 404 HTML no se evalúa —
  anti confusión de tipo), presupuesto de página compartido y caps `TAB_MAX_SUBREQ`/`TAB_MAX_SUBRESOURCE`.
  El script se nombra por su `src` → Freebug reporta `url:line:col` en sus errores (verificado E2E:
  error real dentro de `https://www.gstatic.com/og/...js:168:28`). `hp_script` gana `src` (crudo,
  hostil; el parser jamás fetchea); `type=module` se excluye (fail-closed); un `<script src>` con
  cuerpo inline lista solo el src (regla de navegador). **Revierte "los `src` externos NUNCA corren"
  SOLO para hosts doblemente confiables; para el resto sigue vigente** (candado:
  `test_external_script_skipped_without_net`). **Cuatro fixes que la validación E2E real destapó:**
  (a) **Captura del grupo TLS rota en OpenSSL 3.6** — `SSL_get_negotiated_group`+`OBJ_nid2sn` no puede
  nombrar los híbridos PQ del provider (sin NID) → TODO host PQ-correcto (google, example.com) se
  rechazaba con status 4; ahora `SSL_get0_group_name` (≥3.2) con fallback a NID (`secure_fetch`).
  (b) **TZ del worker normalizada a UTC (`TZ=UTC0`+`tzset()` pre-seccomp)** — doble win: el
  `Date.getTimezoneOffset()` del JS real de Google disparaba el `openat("/etc/localtime")` perezoso de
  glibc → SIGSYS (worker muerto), y de paso la TZ del host era una fuga de fingerprinting; ahora todo
  JS ve UTC (candado: `test_js_date_timezone_is_utc_and_survives`; diagnóstico vía audit type=1326 +
  afordancia nueva `FREEDOM_DEBUG_WORKER=1`). (c) **El headless sigue la navegación por JS** (
  `location.href=`/`assign`/`replace`) como el GUI: cada salto re-entra el camino normal de fetch
  (re-aplica TODA la política), cap `HL_JS_NAV_MAX` (10) — sin esto el challenge anti-bot de Google
  (que Freedom **ejecuta**: computa el token `sg_ss` y navega con él) rendía una cáscara vacía; y
  `headless_fetch` resuelve URLs relativas de subrecursos contra la URL de página (`ln_resolve`).
  (d) **`collect_text` salta `<style>`/`<script>` anidados** — con JS vivo los scripts quedan en el
  árbol y el markup real de Google (styles dentro de botones, scripts en celdas) pintaba CSS/JS crudo
  como contenido (candado: `test_build_collected_text_skips_style_and_script`). Specs
  (`html_parse.md`, `tab.md`, `freedom.md`, `secure_fetch.md`, `page_view.md`) + tests (2 nuevos
  `html_parse`, 6 nuevos `test_tab`, 1 nuevo `page_view` → 39 suites) + `make test`/`make asan`
  (exit 0) limpios + fuzz `make fuzz` (1.68M execs, invariante inline-XOR-externo) y `fuzz-pv` sin
  crash/leak/UB + **E2E real verificado**: google.com homepage carga con su JS externo ejecutándose y
  renderiza limpia (PNG revisado); la búsqueda ejecuta el challenge JS de Google y sigue su navegación
  — Google puede aún servir su muro "unusual traffic" (decisión server-side: IP + sin cookies
  persistentes, que Zero Knowledge no negocia); DuckDuckGo (buscador por defecto de la omnibox) rinde
  resultados completos (PNG revisado). **Límites v1:** fetch de script síncrono en la ventana de carga;
  sin `defer`/`async` (orden de documento estricto); sin módulos ES (`type=module` excluido); sin
  cookies (por diseño). Ver `[[freedom-external-scripts]]`, `[[freedom-parent-gated-xhr]]`,
  `[[freedom-live-js]]`.
- **Hito 23b (combinadores) — CSS descendiente (`A B`) e hijo (`A > B`).** El módulo puro `css`
  deja de tratar todo combinador como "no soportado": un `css_sel` pasa de un único compuesto a una
  **cadena de compuestos** (`parts[CSS_MAX_COMPOUNDS]`, 4) unidos por descendiente (espacio) o hijo
  (`>`); el rightmost es el *sujeto*. El emparejado es **derecha-a-izquierda** sobre la cadena de
  ancestros: hijo exige el padre inmediato, descendiente prueba cada ancestro (la recursión
  `complex_matches` backtrackea), profundidad acotada (≤4) → anti-DoS. Especificidad = **suma** de
  los compuestos; empata por orden de documento. Nueva API `css_resolve_el(sheet, const
  css_element *el, inline, len)` donde `css_element` lleva el ancestro (`->parent`); `css_resolve`
  queda como wrapper (elemento sin padre → un complejo nunca matchea, comportamiento previo intacto).
  `page_view` (`element_css_style`) construye la cadena de ancestros (acotada a 32, fail-closed) con
  `fill_css_node` y llama `css_resolve_el`, así los combinadores resuelven en el render real.
  Sibling `+`/`~`, atributo `[...]` y pseudo `:`/`::` **siguen fuera** (se descarta el selector,
  falla cerrado). Specs (`css.md`, `page_view.md`) + tests (6 nuevos en `css`: descendiente/hijo/
  suma-especificidad/cadena-de-clases/sibling-no-soportado/`css_resolve_el` null; 1 E2E en
  `page_view` por el pipeline real `html_parse`→`page_view`) + `make test` (35 suites) / `make asan`
  (35, exit 0) limpios + fuzz `fuzz-css` (267k execs, ahora también `css_resolve_el` con cadena
  sintética) y `fuzz-pv` (31k execs, cadena sobre HTML hostil) sin crash/leak/UB + **E2E visual**
  (`examples/combinators.html` por `/visual-review`: `.menu > .row` maqueta flex solo en el hijo
  directo y `aside .ad{display:none}` oculta solo dentro de `aside` — precisión de ambos combinadores
  confirmada en PNG). **Fuera de alcance:** sibling/atributo/pseudo, y los **colores** de autor
  siguen gateados por `caps.css` (en el demo se usan efectos estructurales `display:flex/none`, que
  se aplican siempre). *(Módulos puros + integración verificados bajo test/ASan/fuzz + E2E visual
  headless; ventana Wayland interactiva pendiente al dueño.)* Ver `[[freedom-author-css-direction]]`,
  `[[freedom-css-combinators]]`.
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
- **Hito 17b — Endurecimiento de seccomp: W^X + anti-volcado.** Dos mejoras al confinamiento del
  worker (`os_sandbox`), ambas con TDD y verificadas en este host. (a) **W^X (sin memoria
  ejecutable):** el BPF clásico ahora **inspecciona argumentos** (no solo el número de syscall):
  `mmap` y `mprotect` salen del allowlist genérico y pasan por un bloque que enmascara `PROT_EXEC`
  en `seccomp_data.args[2]` → si pide ejecutable se **deniega** (KILL/ERRNO). El worker es un
  **intérprete** (QuickJS sin JIT) sobre código ya mapeado + parser/decoders, y con `-z relro -z
  now` el PLT/GOT queda de solo-lectura **antes** del `fork`, así que ninguna operación legítima
  necesita crear/voltear una página ejecutable; se cierra el último paso de la inyección de código
  nativo aun tras un secuestro de control. `mremap` sigue permitido (no toma protección);
  `pkey_mprotect` sigue denegado por completo (privilegio mínimo). Espejo puro `os_prot_allowed(nr,
  prot)` (la decisión efectiva; `os_policy_allows` sigue siendo la pertenencia). (b) **Anti-volcado:**
  `os_no_dump()` = `PR_SET_DUMPABLE`=0 + `RLIMIT_CORE`=0, así un crash no deja core ni un proceso
  ajeno puede `ptrace`/`/proc/<pid>/mem` — no se exfiltran los secretos del worker (clave de sesión
  del readback canvas/audio, bytes de la página descifrada). Best-effort (como Landlock/namespaces);
  el orden del hijo pasa a `os_isolate_namespaces()` → `os_no_dump()` → `os_landlock_restrict(NULL,0)`
  → `os_harden(KILL)` (cableado en `tab.c` y `renderer.c`). Spec (`os_sandbox.md` §11/§12, §10
  actualizado) + 4 tests nuevos (`os_prot_allowed` puro; fork: `mmap`/`mprotect` PROT_EXEC → `SIGSYS`;
  `os_no_dump` → undumpable + core=0) + `make test` (35 suites) / `make asan` (35, exit 0) limpios +
  **validación de no-regresión del worker**: `test_tab` (30 tests: parse + JS + decode bajo el filtro
  W^X) verde y un render headless real (`--download-pdf` de `examples/rich.html` → PDF de 3 páginas
  válido), probando que el intérprete-sobre-código-mapeado nunca necesita páginas ejecutables.
  **Diferido con justificación** (no por olvido): `RLIMIT_AS` (choca con la reserva de *shadow* de
  ASan; el heap JS ya está acotado por su asignador) y `RLIMIT_CPU` (mata todo el worker; el valor es
  política de render atada a un interrupt-handler de QuickJS). **No** se agregan `ppoll`/`epoll`
  (el worker hace I/O bloqueante: ensanchar sería lo contrario de endurecer). Origen: auditoría de
  gaps #5. *(El port aarch64 llegó en el Hito 17d, abajo.)* Ver `[[freedom-seccomp-wx-hardening]]`.
- **Hito 17d — Port de seccomp a aarch64 (gap #3).** El filtro dejó de ser x86_64-only: el guard de
  arquitectura del BPF se parametriza (`OS_SECCOMP_ARCH` = `AUDIT_ARCH_X86_64` en x86_64,
  `AUDIT_ARCH_AARCH64` en **aarch64 little-endian**) y la sección `os_harden` se habilita para ambos
  (`#if defined(__x86_64__) || (defined(__aarch64__) && !defined(__AARCH64EB__))`). **El allowlist y el
  W^X ya eran portables:** usan solo syscalls de la **ABI genérica**, así que los macros `__NR_*`
  resuelven el número correcto por arquitectura sin hardcodear, y `args[2]` (prot) está en la misma
  posición; ambas arquitecturas habilitadas son **little-endian**, condición que el load de bajo-orden
  del W^X exige (por eso **aarch64 big-endian se excluye** y cae a `OS_ERR_UNSUPPORTED`, fail-closed).
  Spec (`os_sandbox.md` §3/§10) + test nuevo `test_seccomp_arches_are_le` (invariante LE de
  `AUDIT_ARCH_X86_64`/`AARCH64`, corre en este host) + verificación concreta de que **los 34 syscalls
  del allowlist+landlock+close_range existen en `asm-generic/unistd.h`** (la ABI de aarch64) + `make
  test`/`make asan` (35, exit 0) limpios con el camino x86_64 **sin cambios**. **Honestidad:** el
  camino aarch64 es **source-complete** pero **no se pudo construir ni ejecutar aquí** (sin
  toolchain/sysroot aarch64 en este host x86_64) — queda **pendiente de itest en hardware/CI ARM64**,
  nunca marcado como verificado. Ver `[[freedom-seccomp-wx-hardening]]`.
- **Hito 17c — Aislamiento real de proceso por pestaña: fork + exec del worker.** El worker dejó de
  ser solo `fork()` (que hereda **copy-on-write** TODO el espacio del padre): ahora `tab_open`
  **re-ejecuta** el binario (`execv("/proc/self/exe", {"freedom","--tab-worker",rfd,wfd})`) tras el
  fork, así el worker arranca con una **imagen nueva sin herencia**. Cierra una fuga cross-pestaña
  real (el audit de gaps #4): el padre (GUI) tiene en `tab_slots[]` el HTML/URL/estado de **todas** las
  pestañas de fondo; con `fork`-solo, el worker que renderiza la pestaña activa hostil tenía copias COW
  de las otras y podía lavarlas por la red del padre (un `src` de imagen o `location.href` a
  `evil.com/?<secreto-de-otra-pestaña>`). seccomp/W^X/Landlock confinan lo que el worker *puede hacer*;
  el exec confina lo que *puede ver* (+ ASLR fresca). **Higiene de fds:** antes del exec el hijo marca
  `CLOEXEC` en todo fd≥3 (`close_range(3,~0,CLOSE_RANGE_CLOEXEC)`) y lo limpia solo en los 2 pipes, así
  el worker tampoco hereda el socket de Wayland ni otros fds. `tab_worker_dispatch(argc,argv)` (1ª línea
  de `main` del binario **y** de `test_tab`, porque el worker re-ejecuta `/proc/self/exe`) detecta
  `--tab-worker`, valida los fds con `tab_parse_worker_args` (puro, fail-closed: decimal, no-negativo,
  acotado) y corre `tab_worker_run`; exec fallido ⇒ sin handshake ⇒ `TAB_ERR_CONFINE`. Spec (`tab.md`
  §2) + 4 tests puros nuevos (`tab_parse_worker_args`: válido/no-worker/malformado/nulls) + **el set E2E
  de `test_tab` ahora corre a través del worker re-exec'd** (30 tests: parse+JS+decode) → `make test`
  (35 suites) / `make asan` (35, exit 0) limpios + verificación runtime por `strace`
  (`close_range`→`execve("/proc/self/exe", --tab-worker 3 6)`) + flag público `--tab-worker` fail-closed
  (fds malos salen rápido; arg malformado cae a la CLI normal). **Sin dependencia nueva.** Origen:
  auditoría de gaps #4 (el reclamo literal "unshare en proceso actual / no fork por tab" era falso —
  ya había fork-por-render; la fuga real era la herencia COW). Ver `[[freedom-tab-fork-exec]]`,
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
- **Hito 19b (JPEG) — Decodificado JPEG en el worker (excepción de doctrina autorizada).** `image_decode`
  deja de ser PNG-only: `img_sniff` reconoce `FF D8 FF`, `img_decode_jpeg` decodifica baseline/progressive
  con **libjpeg-turbo** y un nuevo despachador `img_decode` (sniff → png/jpeg/`IMG_ERR_FORMAT`) es la única
  entrada que usa el worker (`tab.c` `child_handle_decode_image`). JPEG **rompe la doctrina PNG-only** y se
  admite solo con sign-off del dueño + contención: decode **solo en el worker** (seccomp+Landlock+netns),
  **fuente solo en memoria** (`jpeg_mem_src`), **manejador de error `longjmp`** (el `error_exit` por defecto
  de libjpeg llama `exit()`; se reemplaza → un JPEG hostil devuelve `IMG_ERR_DECODE`, falla cerrado, no mata
  el worker), **tope anti-bomba antes del decode** (`jpeg_read_header`→`img_dimensions_ok`→`jpeg_start_
  decompress`), salida forzada a `JCS_RGB` expandida a **BGRA opaco** (sin extensión turbo; CMYK/YCCK se
  **rechazan**). Sin cambios de IPC/render (los píxeles ya viajaban igual). `-ljpeg` solo donde está
  `image_decode.o`. Spec (`image_decode.md` §0.1/§4.1) + tests (7 nuevos en `test_image_decode`: sniff/
  dispatch/dim+alfa/truncado/no-jpeg/nulls; `test_sniff_non_png`→`test_sniff_unsupported` por el cambio de
  contrato) + `make test` (35 suites) / `make asan` (exit 0, sin leaks en la ruta `longjmp`) limpios + fuzz
  `make fuzz-img` (4.2M execs; libFuzzer descubre `FF D8 FF` solo) + corpus JPEG sembrado (CMYK/progresivo/
  gris/truncado, 176k execs) sin crash/leak/UB + **verificación visual del decode**: una JPEG con formas/
  colores/texto decodificada por `img_decode`→PNG confirma orden de canal BGRA correcto (rojo=rojo) y
  fidelidad sin artefactos. **Fuera de alcance:** SVG/WebP/GIF/AVIF, EXIF/ICC, CMYK. *(Decode + ASan + fuzz
  + revisión visual del bitmap verificados; el render JPEG dentro de la GUI Wayland —con `Ctrl+I`— queda
  pendiente al dueño: el camino headless `--download-pdf` lleva imágenes OFF.)* Ver `[[freedom-jpeg-decode]]`.
- **Hito 23b (line-height) — CSS de autor `line-height` + `--author-css` para revisión visual.** El
  subconjunto `css` gana `line-height` (porcentaje de la caja de línea natural): unitless (`1.5`→150) o
  `%` (`160%`→160), clamp `[CSS_LINE_MIN, CSS_LINE_MAX]`, `normal`→0 (UA), `px`/`em` absolutos fuera de
  scope (se descartan). **Hereda** como `font-size` y viaja por el **mismo plumbing** que `font_scale`:
  `css_style.line_scale` → `pv_run.line_scale` (emitido en `resolve_context`/`pv_set_text_style`) → IPC
  `tab.c` `write_view`/`read_view` → `rd_block.line_scale` (gateado por `caps.css`) → GUI `flush_line`
  (reemplaza el factor `theme.line_spacing` por el del autor). Presentación, no estructura: gateado por
  `caps.css` como los colores/font-size. Además, **boyscout de tooling:** nuevo flag `--author-css` en el
  render headless (`src/freedom.c`) que activa `caps.css` (solo render local; el cap de **imágenes/red
  sigue OFF**, no telefonea), de modo que CUALQUIER feature de CSS de autor (line-height, colores,
  text-align, font-size) por fin es **visualmente revisable** sin Wayland — antes era imposible (el PDF
  headless iba con `caps.css` OFF). Specs (`css.md`, `page_view.md`, `render_doc.md`, `tab.md`,
  `freedom.md`) + tests (8 en `css`: unitless/%/normal/px-drop/clamp; 1 en `page_view`: hoja+inline+
  herencia; `pv_set_text_style` ahora 4-ario en `test_page_view`) + `make test` (35 suites) / `make asan`
  (exit 0) limpios + fuzz `fuzz-css` (256k) y `fuzz-pv` (26k) sin crash/leak/UB + **E2E visual**
  (`--author-css --download-pdf` sobre un demo `line-height:1.0` vs `2.4`: el PNG confirma interlineado
  apretado vs amplio con el mismo ancho de wrap). **Fuera de alcance:** `px`/`em` absolutos de line-height,
  `letter-spacing`/`text-decoration`. *(Módulos puros + IPC + E2E visual headless verificados; ventana
  Wayland interactiva pendiente al dueño.)* Ver `[[freedom-line-height]]`, `[[freedom-author-css-direction]]`.
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
  **Honestidad sobre Google (histórico; superado por el Hito 24 EXT):** en este hito los scripts
  `src` externos aún no corrían; desde el Hito 24 EXT sí (hosts allow∩js, fetch del padre bajo
  política) y el muro que queda es el anti-bot server-side de Google; la barra sigue enrutando
  búsquedas a DuckDuckGo HTML (Hito 18). *(Núcleo + ejecución verificados; integración visual GUI
  pendiente al dueño.)* Ver `[[freedom-live-js]]`, `[[freedom-external-scripts]]`.
- **Hito 20e parte 1 — JS vivo: `location.*` reales + navegación por JS.** El worker conoce la URL de
  la página y la inyecta para que el JS lea su `location` real, y captura la **navegación por JS**
  gateada con la misma política pura que un clic. (a) **`url_split` (puro, zero-copy):** descompone una
  https absoluta en componentes WHATWG-location (`href`/`protocol`/`origin`/`host`/`hostname`/`port`/
  `pathname`/`search`/`hash`), cada campo aliasando la entrada; reusa `url_authority_len`. https-only,
  fail-closed. (b) **`js_dom`:** `jd_set_location` construye `__locParts` **en C** (la URL hostil
  **nunca** se interpola en JS) e instala un `location`/`document.location`/`document.URL` real de solo
  lectura; las escrituras que navegan (`location.href=`/`assign`/`replace`/`reload`/`window.location=`)
  **no ejecutan nada**: registran la **string cruda** en `__navReq`; `jd_take_nav_request` la lee y
  limpia. (c) **`tab`:** OP_LOAD lleva la URL (`[op][run_js][reader][dark][url_len][url][len][html]`);
  el child captura la cruda tras correr scripts; **el padre (confiable) la gatea** con
  `ln_resolve(URL_real, cruda)` (Zero Trust: un worker comprometido no puede colar `file://`/downgrade)
  y solo expone `tab_page.nav_url`/`nav_replace` si la política lo permite. (d) **GUI:** pasa la URL al
  worker; en carga **fresca** (no en re-render por toggle) navega a `nav_url` por el camino normal
  (re-aplica TODA la política de red), con cap **anti-bucle** (`JS_NAV_MAX`, reset al asentarse).
  `link_nav`/`url_resolve_https` se reusan (DRY): la misma regla que un clic. Specs (`url.md`,
  `js_dom.md`, `tab.md`, `link_nav.md`) + tests (6 `url_split`, 8 `js_dom` location/nav, 5 E2E `tab`:
  location real / nav absoluta / relativa resuelta / downgrade+foreign+fragmento bloqueados / sin-JS
  sin-nav) + `make test` (35 suites) / `make asan` (35, exit 0) limpios + fuzz `make fuzz-url` (4.3M
  execs sin crash/leak/UB, invariantes de in-bounds + gate sostenidos). **Fuera de alcance (parte 2):**
  eventos interactivos (clic→handler→re-render), timers async reales, getter de `innerHTML`, scripts
  externos (`src`), scroll a ancla `#id`. *(Núcleo puro + IPC + ejecución verificados bajo
  test/ASan/fuzz; ruta GUI compila endurecida, verificación visual Wayland pendiente al dueño.)* Ver
  `[[freedom-live-js]]`.
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
  columna de lectura. **Fix (2026-06-29):** el centrado del reader vive en `content_margin_x`
  (HORIZONTAL únicamente); antes `apply_theme` inflaba `w->theme.content_margin`, que es **también** el
  margen VERTICAL (`content_geometry` resta `2*content_margin` a la altura del viewport y desplaza el
  origen) → en ventanas anchas la altura de contenido se volvía negativa y la página se pintaba
  **fuera de la ventana / nada visible**. Ahora los ejes están desacoplados: `content_margin_x(w)`
  (horizontal, lo usan `content_width` y el `left` de pintado/hit-test) aplica el centrado;
  `content_margin` sigue siendo el margen vertical base. Afordancia de verificación
  **`FREEDOM_READER=1`** (abre en modo reader al inicio, como `FREEDOM_FREEBUG=1`) — verificado en
  pantalla (weston+Xvfb): boilerplate eliminado, columna centrada, contenido completo visible.
  Specs (`css.md`, `page_view.md`, `tab.md`,
  `render_doc.md`) + tests (19 `css`, 6 nuevos en `page_view`: hoja/align+font/bold+inline-gana/
  display:none/reader/setter) + `make test` (35 suites) / `make asan` (35 suites, exit 0) limpios +
  fuzz `make fuzz-css` (1M execs) y `fuzz-pv` (cascada CSS sobre HTML hostil) sin crash/leak/UB.
  **Fuera de alcance (v1):** combinadores/pseudo-clases/selectores de atributo; `url()`/`@`-reglas/
  `calc()`/`var()`/`!important`; box model de autor (margin/padding/width — sigue el UA);
  flex/grid desde `<style>` (en v1 solo `display:none` de `<style>` surtía efecto; los parámetros
  `gap`/`justify-content`/`grid-template-columns` desde `<style>` llegaron en el Hito 23b parte 2,
  abajo). *(Módulos puros + IPC verificados bajo test/ASan/fuzz;
  ruta GUI compila endurecida, verificación visual Wayland pendiente al dueño.)* Ver
  `[[freedom-author-css-direction]]`.
- **Hito 23b (parte 1) — `@media` + `prefers-color-scheme` (modo oscuro automático).** El parser `css`
  deja de **descartar** `@media`: ahora lo **evalúa en tiempo de parseo** contra un contexto `css_media`
  (`css_parse_media`) y conserva las reglas internas **solo si la consulta matchea**. Subconjunto:
  tipos `screen`/`print`/`all` (+ `only` ignorado), `(prefers-color-scheme: dark|light)`,
  `(min-width|max-width: Npx)` contra un **ancho normalizado fijo (1920px, anti-fingerprint —
  el worker no conoce el ancho real)`; lista por comas = **OR**, partes con `and` = **AND**.
  **Falla cerrado:** `not`, tipos/features desconocidos y profundidad de anidamiento > 4 no matchean —
  nunca se aplica una regla que no se puede gatear bien. `@import`/`@font-face`/otras `@`-reglas siguen
  descartadas (cero red). El flag `prefers_dark` se hila GUI→worker (OP_LOAD gana un 3er byte:
  `[op][run_js][reader][dark][len][html]`; `pv_build_full`/`tab_load_full` ganan el parámetro), derivado
  del tema oscuro; cambiar de tema con `caps.css` activo re-renderiza desde caché (sin red) para aplicar
  el CSS dark del autor. `@media print` se excluye correctamente de la vista de pantalla (rendering a
  PDF queda para después). Spec (`css.md`, `page_view.md`, `tab.md`) + tests (5 nuevos en `css`:
  screen/print, prefers-color-scheme, width, and/or, fail-closed; 1 en `page_view`) + `make test`
  (35 suites) / `make asan` (35, exit 0) limpios + `fuzz-css`/`fuzz-pv` (contexto `@media` variado) sin
  crash/leak/UB. *(Módulo puro + IPC verificados; ruta GUI compila endurecida, verificación visual
  Wayland pendiente al dueño.)* **Pendiente (Hito 23b parte 2):** `position` relative/absolute/sticky,
  render de `@media print` al PDF (flex/grid desde `<style>` ya cerrado, abajo). Ver
  `[[freedom-author-css-direction]]`.
- **Hito 23b parte 2 (flex/grid desde `<style>`) — parámetros de contenedor por cascada.** Un
  contenedor `display:flex`/`grid` ya toma sus parámetros (`gap`/`justify-content`/
  `grid-template-columns`) de la **misma cascada** de `[[css]]` que los colores, así que una regla de
  `<style>` (no solo `style=` inline) maqueta columnas. El módulo puro `css` gana 3 propiedades
  whitelisteadas → `css_style.{gap,justify,grid_cols}` (con enum `css_justify`, topes `CSS_GAP_MAX`/
  `CSS_GRID_COLS_MAX`, fail-closed: `justify-content` desconocido se descarta, valor que excede el
  buffer de 64B se cae **entero**, nunca trunca). `page_view` deriva el contenedor del `css_style` ya
  resuelto por ancestro (`element_css_style`) y **se borró el parser inline duplicado**
  (`style_value`/`parse_px`/`parse_justify`/`count_tracks`/`element_container`/`ascii_eq_ci`): modo
  boyscout, una sola superficie auditada y fuzzeada. **Sin cambios de IPC/render_doc/GUI** — los
  campos `cont_*` ya viajaban de extremo a extremo; solo cambió la *fuente* de los valores.
  **Estructura, no estilo de autor:** `render_doc` los propaga **siempre** (desacoplado de `caps.css`;
  de paso se corrigió un comentario/spec que afirmaba lo contrario). Specs (`css.md`, `page_view.md`)
  + tests (5 nuevos en `css`: inline/hoja/cascada-inline-gana/fail-closed+topes/unset; 3 en
  `page_view`: flex-desde-hoja/grid-desde-hoja/cascada-hoja+inline) + `make test` (35 suites) /
  `make asan` (exit 0) limpios + fuzz `fuzz-css` (610k execs) y `fuzz-pv` (115k execs) sin
  crash/leak/UB + verificación E2E por el pipeline real (`html_parse`→`page_view`) y demo
  `examples/css-sheet-layout.html`. **Fuera de alcance:** flex por-item (`flex-grow`/`-shrink`/
  `-basis`/`order`), `align-items`/`align-content`, `row-gap` distinto de `column-gap`, expansión de
  `repeat()`/`minmax()`, y pesos `fr`/`auto`/tracks nombrados (todo track = 1fr de igual ancho).
  *(Módulos puros + IPC verificados bajo test/ASan/fuzz + E2E headless; verificación visual Wayland
  pendiente al dueño.)* Ver `[[freedom-author-css-direction]]`.
- **Hito 23b-3 — Box model de autor (`margin`/`padding`/`width`/`max-width`).** "Ver la web moderna
  como la maquetó el webmaster": el subconjunto `css` deja de ignorar el box model. (a) **`css`
  (puro, fuzzeado):** 10 campos nuevos en `css_style` + `interp_len` (px, `0`, `em`/`rem`×16; `%`/vw/
  `calc` **fallan cerrado** — necesitan un bloque contenedor que el parser no tiene) + `emit_len` +
  `expand_box4` (shorthand 1–4 valores, orden CSS). Márgenes admiten signo y `auto`
  (`CSS_LEN_AUTO`); padding/width no. Las cajas saltan el viejo gate `ival<0 ⇒ rechazo`; slots de
  margin/padding **contiguos** en orden CSS. (b) **`page_view`:** `css_hbox_resolve`/`css_has_hbox`
  pre-resuelven 6 campos de wire en `resolve_context` — **horizontal** (`box_l/r/w/center`) del
  **ancestro de bloque más cercano con caja** (así el `max-width`/centrado de un wrapper alcanza a
  sus descendientes), **margen vertical** (`box_mt/box_mb`) del **bloque hoja propio** (no se duplica
  por bloque interno). `pv_set_box`. (c) **IPC `tab.c`:** 6 int32 nuevos en write_view/read_view.
  (d) **`render_doc`:** copia los 6 **solo con `caps.css`** (una caja puede encoger el contenido a lo
  ilegible → familia de presentación, como colores/`text-align`/`font-size`, **no** la de layout
  siempre-on de flex/grid). (e) **`box_style`:** `bx_place` (puro, testeable) hace la geometría
  horizontal (cap + centrado + insets); la GUI `layout_doc` la llama y `block_margins` aplica el
  override de margen vertical. **Defecto (caps.css off) byte-idéntico** al previo: cajas en 0/`UNSET`,
  `bx_place(0,0,0,0,avail)` ⇒ `x_off=0, content_w=avail`. Specs (`css.md`, `box_style.md`,
  `page_view.md`, `render_doc.md`) + tests (6 en `css`, 5 `bx_place` en `box_style`, 3 E2E en
  `page_view`) + `make test` (35 suites) / `make asan` (35, exit 0) limpios + fuzz `fuzz-css` (~494k)
  y `fuzz-pv` (~265k) sin crash/leak/UB + **E2E visual** (`examples/box-model.html` por
  `--author-css --download-pdf` → PNG: columna centrada con `max-width`, padding horizontal, caja
  compartida por los descendientes del wrapper, y override de margen 64px/2px confirmados). **Fuera de
  alcance:** `border`, `box-sizing` (todo `width` = content-box), `padding-top/bottom` (la lista plana
  no tiene caja por-bloque que inflar — necesita box-grouping), `%`/viewport, composición de cajas
  anidadas, `position`. *(Módulos puros + IPC + E2E visual headless verificados; ventana Wayland
  interactiva pendiente al dueño.)* Ver `[[freedom-author-box-model]]`, `[[freedom-author-css-direction]]`.
- **Hito 23b-4 — Madurez de selectores y cascada: selectores de atributo + `!important`.** Dos
  features **puras del módulo `css`** que fluyen por el `css_style` ya existente → **cero plomería
  de IPC/`render_doc`/`tab.c`/GUI** (selectores y cascada solo cambian *qué* valor/elemento gana, no
  agregan propiedades). Totalmente testeadas y fuzzeadas aquí. (a) **Selectores de atributo:**
  `[attr]`, `[attr=v]`, `[attr~=v]` (palabra en lista), `[attr|=v]` (igual o prefijo `v-`),
  `[attr^=v]`/`[attr$=v]`/`[attr*=v]` (prefijo/sufijo/substring), con comillas opcionales (admiten
  espacios: `[title="a b"]`) y flag de caso `i`/`s` al final. Nombre case-insensitive (HTML); valor
  case-sensitive salvo `i`. Especificidad: cada `[attr]` = 10 (como una clase); hasta
  `CSS_MAX_ATTR_SEL` (4) por compuesto; `[...]` malformado descarta el selector entero (falla
  cerrado). `css_element` ganó `attrs`/`nattrs` (**gotcha: rompe inits posicionales** — corregidos en
  `css_resolve`, `fuzz_css.c`, helpers de test); `page_view` `fill_css_node` enumera los atributos del
  elemento por lexbor (`lxb_dom_element_first_attribute`…) a un buffer acotado (nombre en minúsculas);
  `id`/`class` son atributos también, así `[id=…]`/`[class~=…]` andan. El scan de sintaxis no
  soportada de `parse_complex_selector` es ahora **bracket-aware** (permite `[`/`]`, sigue rechazando
  `+`/`~`/`:`/`(`/`)` fuera de corchetes); el tokenizador de compuestos respeta la profundidad de
  corchete (un valor citado con espacios no parte el compuesto). (b) **`!important`:** antes se
  **descartaba en silencio** (el valor `red !important` no interpretaba → declaración perdida; la
  vieja spec mentía con "el token se quita"). Ahora `strip_important` quita el sufijo y
  `css_decl.important` sube la declaración a un **tier de cascada superior** que gana a toda
  no-importante sin importar especificidad; dentro del tier, especificidad→orden normales (inline
  importante gana a hoja importante; hoja importante gana a inline no-importante); se estampa en
  **todas** las declaraciones que expande un shorthand (`margin:0 auto !important`). `apply_decl` ganó
  un arreglo `wi[]` (importante-ganador) junto a `ws`/`wo`; `parse_one_decl` se partió en
  `interpret_prop` + wrapper que quita `!important` y estampa el flag. Boyscout: `ci_contains` se
  unificó en `substr_match` (case-aware, usado por `url(` y `*=`). Specs (`css.md`, `page_view.md`) +
  tests (14 nuevos en `css`: presencia/igual/operadores/flag-de-caso/nombre-CI/valor-citado/
  especificidad/combinador/malformado + 5 de `!important`; 1 E2E en `page_view` por el pipeline real
  `html_parse`→`page_view`) + `make test` (36 suites) / `make asan` (36, exit 0) limpios + fuzz
  `fuzz-css` (154k execs, ahora con `css_element` sintético que lleva atributos) y `fuzz-pv` sin
  crash/leak/UB + **E2E visual** (`examples/attr-selectors.html` por `--author-css --download-pdf`).
  **Fuera de alcance (siguiente; los hermanos `+`/`~` y las pseudo-clases cerraron en el Hito 23b-9):** `border`/`box-sizing`. *(Módulos puros + integración verificados bajo
  test/ASan/fuzz + E2E visual headless; ventana Wayland interactiva pendiente al dueño.)* Ver
  `[[freedom-css-attr-selectors-important]]`, `[[freedom-author-css-direction]]`.
- **Hito 23b-5 — `text-decoration` de autor (`underline`/`line-through`/`overline`/`none`).** Una
  propiedad de **texto** que viaja por el **mismo plumbing de runs** que `line-height` (plantilla del
  Hito 23b line-height): `css_style.text_decoration` (OR de `CSS_DECO_UNDERLINE`/`_LINE_THROUGH`/
  `_OVERLINE`; -1 sin definir, **0 = `none` explícito** para distinguirlo de "sin declarar") →
  `pv_run.text_decoration` (emitido por `resolve_context`/`pv_set_text_style`, ahora 4-ario) → IPC
  `tab.c` `write_view`/`read_view` (1 int32 nuevo) → `rd_block.text_decoration` (**gateado por
  `caps.css`** como los colores; -1 cuando off) → GUI `flow_text_block` (override del subrayado base de
  los links: `a{text-decoration:none}` **quita** el subrayado; añade `strike`/`overline` al `rc_frag`)
  → `paint_content_row` (reutiliza la maquinaria de subrayado de los links + dos líneas nuevas). El
  parser `css` recolecta las **palabras clave de línea** de un valor multi-token (`underline overline`)
  e **ignora** los tokens de estilo/color/grosor de CSS3 (`wavy`/`red`/`2px`); un valor sin ninguna
  palabra clave de línea se descarta (fail-closed → -1). **Boyscout:** el init posicional de `css_style`
  en `css_resolve_el` se pasó a **inicializadores designados** (extingue el gotcha recurrente de
  "campo nuevo default a 0 en vez de su sentinel"). Presentación, no estructura: como en CSS real no
  hereda, pero el modelo plano resuelve el **ancestro más cercano** que la fije (igual que `color`).
  Specs (`css.md`, `page_view.md`, `render_doc.md`) + tests (2 en `css`: inline-todas-las-variantes +
  cascada/none-quita-subrayado; 1 E2E en `page_view`; setter `pv_set_text_style` 4-ario) + `make test`
  (36 suites) / `make asan` (36, exit 0) limpios + fuzz `fuzz-css` (186k execs) y `fuzz-pv` (152k execs)
  sin crash/leak/UB + **E2E visual** (`examples/text-decoration.html` por `--author-css --download-pdf`:
  el PNG confirma subrayado/tachado/línea-superior, combinados, tokens extra ignorados, spans inline, y
  que `text-decoration:none` quita el subrayado del link; **sin** `--author-css` byte-idéntico al previo
  — ambos links subrayados, cero decoración de autor). **Fuera de alcance:** `text-decoration-style/
  -color/-thickness`, semántica de propagación (usamos ancestro-más-cercano), `letter-spacing`,
  `text-transform`. *(Módulos puros + IPC + E2E visual headless verificados; ventana Wayland
  interactiva pendiente al dueño.)* Ver `[[freedom-author-css-direction]]`, `[[freedom-line-height]]`.
- **Hito 23b-6 — 10 propiedades de presentación de texto (las de mayor impacto cosmético).** Tanda
  de **10 propiedades nuevas** de CSS de autor, todas con TDD + fuzz + E2E visual: **`font-family`**
  (mapea a un *bucket* genérico serif/sans/mono/cursive/fantasy — el motor no casa familias exactas;
  nombres comunes mapeados; `@font-face`/`url(` descartados → cero red), **`text-transform`**
  (uppercase/lowercase/capitalize/none), **`letter-spacing`**, **`word-spacing`**, **`text-shadow`**
  (una capa, blur ignorado, sin color → negro), **`opacity`** (0..100), **`vertical-align`** (solo
  sub/super/baseline), **`text-indent`** (primera línea), **`white-space`** (solo se consume la
  distinción ajuste/no-ajuste: `nowrap`/`pre` suprimen el wrap) y **`list-style-type`**/`list-style`
  (disc/circle/square/decimal/lower·upper-alpha/lower·upper-roman/none → cambia el marcador del `<li>`).
  `spec/css.md` ahora lleva un **inventario explícito de soportado vs faltante**. **Plumbing:** mismo
  patrón de run que `line-height`/`text-decoration` pero con un **setter nuevo dedicado**
  `pv_set_text_ext` (11 args; un `pv_text_ext` las transporta por la fusión nearest-ancestor de
  `resolve_context`) → **11 int32 nuevos en `tab.c` write_view/read_view** (insertados entre `deco` y
  `cid` en AMBOS, mismo orden — desincronizar = basura) → `rd_block` **gateado por `caps.css`** (salvo
  `list-style`, que es estructura: el marcador se hornea en el texto del run, no se gatea). En el painter
  (`browser_ui.c`): `content_font` gana arg `family` (`family_face` mapea bucket→cara Cairo);
  `styled_advance` (medición) y `styled_draw` (pintado) aplican `text-transform` + `letter-spacing`
  **igual por clúster UTF-8** → la geometría/hit-test quedan consistentes y el **camino por defecto
  (sin `--author-css`) es byte-idéntico** (verificado: `rich.html` sin author-CSS sin cambios);
  `word-spacing` = px extra al hueco inter-palabra; `vertical-align` sub/super encoge 0.83 + desplaza
  baseline; `text-indent` vía `rc_state.pending_indent` consumido en `open_line` (solo cuando un bloque
  abre línea fresca → pega a la 1ª línea una vez); `nowrap` suprime el test de wrap; `text-shadow` pinta
  una copia desplazada; `opacity` → `set_rgb_alpha`. `list_marker` ahora toma el `list-style` (helpers
  `alpha_marker`/`roman_marker`). **Gotcha (anotado en memoria):** el Makefile no rastrea deps de header
  → tras crecer `css_style`/`pv_run`/`rd_block` hay que **`make clean`** o un `.o` viejo lee el layout
  anterior (`css_resolve_el` devuelve `css_style` **por valor** → ABI rota → basura silenciosa; se
  manifestó como fallos de los tests flex de `page_view`). Specs (`css.md`, `page_view.md`, `render_doc.md`,
  `tab.md`) + tests (11 nuevos en `css`; el pipeline real cubierto por `page_view`/`render_doc`) +
  `make test` (36 suites) / `make asan` (36, exit 0) limpios + fuzz `fuzz-css` (175k execs) y `fuzz-pv`
  (21.8k execs) sin crash/leak/UB + **E2E visual** (`examples/text-presentation.html` por `--author-css
  --download-pdf`: el PNG confirma las 10 — serif/mono/cursive, MAYÚSCULAS/Capitalizado/minúsculas,
  tracking ancho, palabras separadas, sombra gris/roja, párrafo al 45% de opacidad, H₂O/mc² sub/super,
  sangría de 1ª línea, y marcadores i./ii./A./B./square). **Fuera de alcance (ahora el tope de la lista
  "faltante" en `spec/css.md`):** `border`/`border-radius`/`box-shadow`/`box-sizing` (necesitan
  agrupación de cajas por bloque), `position`, transforms/gradientes, casado exacto de fuentes, blur/
  multi-capa de `text-shadow`. *(Módulos puros + IPC + E2E visual headless verificados; ventana Wayland
  interactiva pendiente al dueño.)* Ver `[[freedom-text-presentation-css]]`, `[[freedom-author-css-direction]]`.
- **Hito 23b-7 — CSS de layout/decoración de caja: `position` + `border`/`box-sizing` +
  `box-shadow`/`outline` + flexbox por-item + grid por-item (resolución de valores).** Los cuatro
  GAPs CRÍTICOS de maquetación moderna (`position`, flexbox completo, `border`/`-radius`/`box-shadow`/
  `box-sizing`, grid completo) viven **todos en el mismo componente `css`**, así que se cierran en un
  golpe **en la capa que el módulo puro puede cerrar hoy: resolver los valores** por la misma cascada.
  El paint-time (honrar la caja, el posicionamiento fuera de flujo, el sizing flex/grid real) depende
  de la **agrupación de caja por-bloque** que el `rd_doc` plano aún no tiene (mismo bloqueo
  arquitectónico que `border`/`box-shadow`/padding-vertical del Hito 23b-3) y queda **explícitamente
  diferido** a un hito de motor de cajas (el embrión nativo es `box_tree`/`bt_node`, que ya da rects
  de border-box). **~40 campos nuevos en `css_style`** (no heredados) + 6 enums (`css_position`,
  `css_box_sizing`, `css_border_style`, `css_flex_direction`, `css_flex_wrap`, `css_align_kw`,
  `css_grid_flow`) + topes (`CSS_BORDER_W_MAX`, `CSS_FLEX_FACTOR_MAX`, `CSS_GRID_SPAN_MAX`):
  **`position`** (+`top`/`right`/`bottom`/`left`/`inset` shorthand 1–4 / `z-index` / `box-sizing`),
  **`border`** uniforme + per-side + longhands (`-width`/`-style`/`-color`; clasificador de token
  width/style/color en cualquier orden, fail-closed; `thin`/`medium`/`thick` → 1/3/5px) +
  **`border-radius`** (primer valor px; corner-by-corner fuera) + **`box-shadow`** (una capa: dx dy
  blur spread + color + `inset`; `none` → no-shadow explícito) + **`outline`** (mismo clasificador),
  **flexbox por-item** (`flex`/`-grow`/`-shrink` guardados ×100 / `-basis` auto·content→`CSS_LEN_AUTO`,
  `order`, `align-items`/`-self`/`-content`/`justify-items`, `flex-direction`, `flex-wrap`),
  **grid por-item** (`grid-template-rows`, `row-gap`, `grid-auto-flow`, `grid-column`/`grid-row` solo
  forma `span N`). **Honestidad (doctrina §8):** estos campos son **resolución de valor pura** —
  **NO** se hilan por IPC (`tab.c`) ni los consume `page_view` todavía, así que **no cambian un solo
  pixel del render aún**; lo que ya maqueta (display:flex/grid + gap/justify/grid-template-columns del
  Hito 23b-2) sigue igual. Boyscout: **bug latente de UB extinguido** — varios interpretadores casteaban
  `(int)(double + 0.5)` y clampaban **después** del cast (overflow `int` con valores enormes, p. ej.
  `flex: 3.3e12`); el fuzzer lo encontró (`src/css.c:850`) y se unificó un solo helper `round_clamp`
  que clampa el double **antes** del cast, aplicado en todos los sitios float→int (`interp_fontsize`/
  `_lineheight`/`_gap`/`_len`/`_opacity`/`_flex_factor`/`expand_flex`/`interp_grid_span`/`css_px`).
  Specs (`css.md`: tabla de propiedades + inventario soportado-vs-faltante + tipos/macros) + tests
  (9 nuevos en `css`: position+insets / box-sizing / border shorthand / border longhands /
  box-shadow+outline / flex item / flex align / grid extras / cascada+unset → **85 tests**) +
  `make test` (36 suites) / `make asan` (36, exit 0) limpios + fuzz `fuzz-css` (366k execs, **oráculo
  `check_style` reforzado** con invariantes de todos los campos nuevos: rangos de enum, clamps de
  border/flex/grid/insets) y `fuzz-pv` (195k execs) sin crash/leak/UB (tras el fix de `round_clamp`).
  **No hay E2E visual** porque no se pinta nada nuevo (sería deshonesto): la revisión visual llega con
  el hito de motor de cajas que consuma estos valores. **Fuera de alcance (siguiente, motor de cajas):**
  honrar `position`/`border`/`box-shadow`/`box-sizing` en el painter (necesita caja por-bloque),
  flex/grid sizing real por-item, `float`/`clear`/`overflow`, stacking de `z-index`, placeholders por
  número de línea/named-line en grid, `position:sticky` con scroll. *(Módulo puro `css` resuelto +
  fuzzeado; consumo en render/IPC y verificación visual pendientes del hito de motor de cajas.)* Ver
  `[[freedom-author-css-layout]]`, `[[freedom-author-css-direction]]`.
- **Hito (render) — Tablas anidadas: celda-hoja + fila-bloque (Hacker News deja de verse horrible).**
  `debug_dom` (arriba) probó que HN se rompía por **layout de tabla**, no `position`: `page_view`
  recolectaba la celda **externa** entera (la que envuelve la `<table>.itemlist` anidada) como **un**
  run gigante (las 30 historias colapsadas en un `<p>`), y todo caía en `grid cols=3` → columna de
  ~270px. Dos arreglos en `page_view` (puros, TDD): (a) **solo las celdas HOJA** (sin `<table>`
  descendiente) se recolectan como run; una celda que envuelve una tabla anidada es **contenedor
  estructural** que se recorre, así las celdas de la tabla interna se recolectan **cada una** contra
  **su** tabla (`cell_has_nested_table` + `in_collected_cell` con chequeo de hoja, reemplaza
  `in_cell_subtree`); (b) **cada `<tr>` es un bloque** (`nearest_row`): la 1ª celda de la fila lleva
  `block_break`, las demás la comparten. Y en `gui/browser_ui.c`, el **degrade path** de
  `layout_container` (cuando una tabla excede `BT_MAX_CHILDREN`=128 celdas — HN tiene ~150) ahora
  **honra `block_break`** → una fila por línea en vez de un bloque continuo. Tablas de datos chicas
  siguen alineando columnas por el grid (el `block_break` por fila no afecta la geometría de
  `box_tree`). Resultado E2E (`--author-css --download-png` de HN): de columna de 270px ilegible a
  **lista limpia, una historia por línea con su subtexto debajo, a ancho completo** — idéntico al HN
  real. Spec (`page_view.md`) + tests (`test_build_nested_table_not_flattened` con celdas separadas +
  break por fila; los `test_build_table_grid`/`flattens_cell` previos siguen verdes) + `make test`
  (39 suites) / `make asan` (39, exit 0, 798 casos) limpios + fuzz `make fuzz-pv` (19k execs, sin
  crash/leak/UB). **Fuera de alcance:** `colspan`/`rowspan` (la fila de subtexto de HN usa colspan, así
  que su grid no alinea perfecto — pero el degrade por-fila lo hace legible), columnas con ancho por
  contenido (todo track = 1fr), tablas >128 celdas que sí querrían grid alineado. Ver `[[freedom-debug-dom]]`.
- **Hito (render) — Tablas de navegación fluyen (los links de Hacker News por fin se ven) + `bgcolor`
  legacy.** El hito anterior dejó a HN *legible* pero **sin un solo link**: recolectar una celda a texto
  plano (`collect_text`) **destruye sus `<a href>`**, y HN mete cada título/subtexto/nav dentro de un
  `<td>`. Diagnóstico con `--dump-dom` + PNG (Principio 6): las celdas salían como runs `PV_TEXT`, cero
  hrefs; la barra naranja no aparecía (HN la pinta con `bgcolor="#ff6600"`, no CSS). Tres arreglos puros
  en `page_view` (TDD): (a) **clasificación tabla-de-navegación vs tabla-de-datos** — una tabla con
  **alguna celda hoja de ≥2 anclas** (`table_prefers_flow`, cacheado en `pv_flow_reg`, acotado a
  `PV_MAX_CONTAINERS`, fail-closed) es de layout: sus celdas **se recorren** (los links salen como
  `PV_LINK` con href/color/énfasis vía `resolve_context`, cada `<tr>` un bloque) en vez de recolectarse;
  un **run separador `" "`** dedupe (`last_was_gap`) entre celdas recorridas evita que "1." y el título se
  fusionen. (b) **celda de UNA sola ancla en tabla de datos** → run **`PV_LINK`** (clickeable sin romper
  la grilla: sigue siendo un run = un ítem). (c) **`bgcolor` legacy** como fallback de `background` (gemelo
  de `<font color>`: `bgcolor_attr`→`color_attr` unificado): la barra `#ff6600` y el beige `#f6f6ef` de HN
  aparecen (gateado por `caps.css` en `render_doc` como todo color). Resultado E2E (`--author-css
  --download-png` de HN, verificado): **barra naranja + fondo beige + 30 historias, cada título y cada
  ítem de subtexto un link azul clickeable con su href real** — antes cero links. Spec (`page_view.md`) +
  3 tests nuevos (`test_build_multilink_table_flows_links`, `_single_link_cell_collected_as_link`,
  `_bgcolor_attr_fallback`; los de tabla-de-datos/anidada siguen verdes) + `make test` (39 suites) /
  `make asan` (39, exit 0) limpios + fuzz `fuzz-pv` (18k execs, sin crash/leak/UB) + no-regresión de la
  tabla de datos de `rich.html` (sigue `grid cols=3` alineado). **Fuera de alcance (documentado):** los
  **colores de clase** de HN (títulos negros, subtexto gris) vivían en su **CSS externo** `news.css`
  (`<link rel=stylesheet>`) — **cerrado por el Hito 27** (abajo): con Author styles ON la hoja se
  fetchea bajo política y esos colores resuelven; `colspan`/`rowspan` sigue fuera. Ver
  `[[freedom-debug-dom]]`, `[[freedom-nav-tables-and-bgcolor]]`.
- **Hito 27 — Hojas de estilo externas (`<link rel=stylesheet>`) + gate de subrecursos del padre
  (2026-07-04).** El gap #1 de "web moderna" (casi todo sitio real sirve su CSS por `<link>`; hasta
  aquí solo se veían `<style>`/`style=`). Con **Author styles (CSS) ON** (GUI: `caps.css`, sin modo
  reader; headless: `--author-css`), el worker confinado pide cada hoja aplicable por la **misma trama
  `TAG_SUBREQ`** del Hito 26 — **jamás toca un socket** — y el **padre confiable re-aplica TODA la
  política** (ln_resolve contra la URL de página, hostblock/rastreadores, `net_realm` fail-closed,
  TLS-PQ) antes de servirla. Piezas: (a) **`html_parse`**: `hp_extract_stylesheet_hrefs` (+
  `HP_MAX_STYLESHEETS` 64) reporta los `href` crudos en orden de documento — `rel` por **token**
  case-insensitive (`alternate` excluido), `media` solo ausente/`screen`/`all` (fail-closed) — el
  parser jamás fetchea. (b) **`tab`**: 5º byte de bandera `css` en OP_LOAD (`tab_set_css_allowed`,
  independiente de `run_js`: el CSS no necesita JS); el worker fetchea ANTES de los scripts, gatea
  status 2xx + **Content-Type de CSS** (vacío o conteniendo `css` — un 404 HTML jamás se parsea como
  hoja; espejo de `ctype_is_javascript`), acumula acotado (`TAB_MAX_EXTERN_CSS` 1 MiB; hoja que no
  cabe se descarta ENTERA, nunca truncada a media regla) y **persiste `extern_css` en `child_state`**
  (un click/re-derivación restylea sin re-fetch); toda falla es fail-open para la página (nota
  `FB_WARN` en Freebug, la carga sigue) y fail-closed para la hoja. (c) **`page_view`**:
  `pv_build_styled` (extern_css antepuesto al texto de los `<style>` del documento → a igual
  especificidad la página gana; total acotado por `PV_MAX_STYLE_BYTES`; `pv_build_full` = wrapper
  NULL ⇒ byte-idéntico). (d) **Boyscout Zero-Trust (gap real encontrado):** el padre servía
  **cualquier** trama TAG_SUBREQ si había fetcher instalado (la GUI lo instala incondicionalmente),
  confiando en el flag del *worker* — un worker comprometido podía forjar tramas y hacer fetch sin
  grant. Ahora `tab_serve_subreq` gatea **del lado padre** con el puro `tab_subreq_permitted(net,
  css, method)`: net ⇒ cualquier método bien formado; solo-css ⇒ **exactamente `GET`** (sin POST de
  exfiltración); nada ⇒ rechazo (la trama se consume y responde status 0, sin desync). El gate de
  presentación **no cambia**: los colores externos siguen gateados por `caps.css` en `render_doc`;
  con el toggle OFF hay **cero fetches** (Privacy by Default, candado
  `test_external_css_skipped_without_grant`). Specs (`tab.md` §8, `html_parse.md` §9, `page_view.md`
  §8, `freedom.md` §6) + tests (5 `html_parse`, 1 `page_view`, 6 `tab`: aplicada/sin-grant/ctype/
  bloqueada/persistencia-click/tabla-del-gate-puro → 39 suites) + `make test`/`make asan` (exit 0)
  limpios + fuzz `make fuzz` (284k execs, harness ahora extrae hrefs con invariantes) y `fuzz-pv`
  (18k execs, harness alimenta la mitad del input como hoja externa hostil) sin crash/leak/UB +
  **E2E real verificado** (`--author-css --download-png` de news.ycombinator.com: `news.css` se
  fetchea y los **títulos salen negros y el subtexto gris** — los colores de clase antes imposibles).
  **Límites v1:** fetch síncrono en la ventana de carga; `media` del `<link>` por substring
  screen/all (no media-query real); `@import` sigue descartado (cero fetch recursivo); páginas
  `file://` sin hojas locales (resolver https-only); sin caché entre cargas; los subrayados de HN persistían porque `a:link{text-decoration:none}` usa **pseudo-clase**
  (`:link`) — **cerrado por el Hito 23b-9** (abajo): con Author styles ON los subrayados caen,
  verificado E2E en PNG. Ver `[[freedom-external-stylesheets]]`.
- **Hito 25 — Shaping de texto con HarfBuzz (rendering moderno, lado confiable).** El painter dejó
  de usar la **toy font API** de Cairo (`cairo_select_font_face`+`cairo_show_text`, un glifo por byte,
  sin conciencia de script) y pasa a **HarfBuzz** (shaping) + `cairo_show_glyphs` (FreeType vía
  `cairo-ft`): ahora hay **ligaduras** (fi/ffi/fl), **kerning GPOS** (AV/To/Wa), **formas
  contextuales** y **dirección intra-run** correcta para scripts complejos. Módulo nuevo `text_shape`
  (`tsh_`): resuelve una **fuente local** por bucket genérico (`fontconfig` → serif/sans/mono/cursive/
  fantasy × bold × italic, cacheada), la parsea con FreeType (para los glifos de Cairo) **y** con
  HarfBuzz (para el shaping) desde **los mismos bytes en memoria** (mismos glyph ids, sin estado FT
  mutable compartido), y maqueta `[text,len)` en `cairo_glyph_t`. **Lado confiable, doctrina:** la
  dependencia es **autorizada por el dueño** (como JPEG); el **texto** es contenido remoto hostil ya
  saneado a UTF-8 (**fuzzeado**, `make fuzz-tsh`), las **fuentes son locales** (las que Cairo ya abría);
  el módulo **nunca** se enlaza ni se llama desde el worker confinado (que produce display lists inertes
  y no toca fuentes), **nunca** abre socket ni persiste. **Fail-closed:** sin backend/fuente o ante
  cualquier error, `tsh_*` devuelve un status que hace al painter **caer al toy path** (byte-idéntico al
  render pre-Hito-25; sin regresión en hosts sin fuentes). **Integración mínima en `gui/browser_ui.c`:**
  `content_font` registra el `(family,bold,italic,px)` actual; los dos primitivos atómicos
  `measure_slice`/`draw_slice` (este último ahora toma `(x,baseline)`) shapean vía `tsh_` con fallback
  toy — así `styled_advance`/`styled_draw` ganan shaping de palabra entera, y measure==draw queda
  consistente (mismo shaper, misma slice). El path por-cluster (text-transform/letter-spacing) shapea
  cada cluster (coincide con CSS: letter-spacing desactiva ligaduras). Specs (`text_shape.md`) + tests
  (7 en `text_shape`: contrato fail-closed de input —sin fuente—, shaping ASCII, slice vacía,
  determinismo, measure==advance, cap-overflow, draw) + `make test` (**37 suites**) / `make asan`
  (37, exit 0; leaks de fontconfig suprimidos) limpios + fuzz `fuzz-tsh` (**1.11M execs**, sin
  crash/leak/UB, invariante de cap + measure==advance + sin NaN) + **E2E visual** (`--download-pdf` de
  una página con ligaduras/kerning/acentos/wrap, y la propia `docs/index.html` con `--author-css`: el
  PNG confirma fi/ffi/fl ligadas, AV/To/Wa kerneadas, café/naïve/résumé/Ñame, y tablas/listas/grid
  intactas). **Boyscout — colisión de símbolos extinguida:** HarfBuzz 8.0+ **exporta** un `hb_free`
  público (alocadores), que colisiona con el `hb_free` del módulo `hostblock` (prefijo `hb_`); el
  símbolo del ejecutable **preempta** el de la librería process-wide → SIGSEGV dentro de `hb_shape`.
  Fix: `-fvisibility=hidden` en la compilación (HARDEN + asan) — el binario `freedom` **no exporta API**,
  así que ocultar sus símbolos del `.dynsym` resuelve esta y **cualquier** futura colisión
  proyecto/librería (además es endurecimiento: menor superficie de símbolos dinámicos). No se renombró
  `hostblock` (no butcherear un módulo de seguridad). **Fuera de alcance (v1):** bidi de párrafo
  (reordenamiento mixto LTR/RTL; v1 shapea por palabra/run con dirección por-run), cadena de fallback de
  fuentes (un glifo ausente cae a `.notdef`), casado exacto de familia/webfonts (prohibido por Privacy
  by Default; CSS ya descarta `@font-face`/`url(`), shaping en el renderer plano `ui_render.c`. *(Módulo
  puro + integración + E2E visual headless verificados bajo test/ASan/fuzz; ventana Wayland interactiva
  pendiente al dueño.)* Ver `[[freedom-harfbuzz-shaping]]`.

- **Hito 23b-9 — Pseudo-clases + combinadores hermanos (`css_select`) + estilos en celdas
  recolectadas (2026-07-04).** El gap CSS más visible que quedaba ("los subrayados de HN
  persisten": `a:link{text-decoration:none}` usa pseudo-clase). Tres piezas, todas por el ciclo
  completo. (a) **Boyscout anti-monolito primero:** `css.c` rozaba las ~2000 líneas → el motor
  de selectores se **extrajo al módulo `css_select`** (`include/css_select.h` + `src/css_select.c`,
  prefijo `csel_`: `csel_parse`/`csel_matches` + helpers ASCII `static inline` compartidos con la
  cascada; spec `css_select.md`), tests byte-idénticos antes de tocar features. (b) **Pseudo-clases
  (subconjunto con semántica ZK/estática):** `:link`/`:any-link` matchea `a`/`area` **con `href`**
  (Zero Knowledge: sin historial, todo link es no-visitado — y el **sniffing de historial por CSS
  es imposible por construcción**); `:visited` y los dinámicos (`:hover`/`:active`/`:focus`/
  `:focus-within`/`:focus-visible`) **parsean, cuentan especificidad (+10 como una clase) y jamás
  matchean** (así `a:visited, b{...}` no pierde el grupo); `:root` (tag `html`);
  `:first-child`/`:last-child`/`:only-child`/`:nth-child(An+B)`/`:nth-last-child(An+B)` (gramática
  An+B completa: odd/even/N/An/An±B/-n+B, coeficientes acotados por `CSS_NTH_MAX`, malformado
  descarta el selector); `:checked`/`:disabled` (presencia de atributo) y `:enabled` (control de
  formulario sin `disabled`). Pseudo-clase desconocida, funcionales no soportadas
  (`:not()`/`:is()`/of-type) y **todo pseudo-elemento** (`::before`, grafías legadas `:before`)
  descartan el selector entero (fail closed), el grupo por coma sobrevive; hasta
  `CSS_MAX_PSEUDO_SEL` (4) por compuesto. (c) **Combinadores hermanos:** `A + B` (adyacente) y
  `A ~ B` (general) sobre la cadena `css_element.prev`; `css_element` ganó `nth`/`nsib`/`prev`
  (0/NULL = desconocido ⇒ estructurales/hermanos **no matchean**, jamás un falso positivo).
  `page_view` alimenta el contexto real: `sibling_position` (caminata acotada `CCH_NTH_MAX`
  1024) para **cada** nodo de la cadena de ancestros (así `tr:nth-child(even) td` funciona) y
  cadena de hermanos previos del **sujeto** acotada a `CCH_SIB_MAX` (16) — un `+`/`~` en
  compuesto no-sujeto falla cerrado (documentado). (d) **Bonus encontrado con `--dump-dom`
  (Principio 6):** las celdas de tabla de datos **recolectadas** no resolvían NINGÚN estilo de
  autor (`td{color}` se perdía en silencio): la ruta de celda ahora llama `resolve_context` **en
  el elemento celda** (`resolve_context` arranca en el propio elemento cuando `n` es elemento) →
  zebra `tr:nth-child(even){background}`, `tr:first-child{font-weight:bold}` y `td{...}`
  aterrizan en el run; y en el painter el **fondo de un item de contenedor pinta su columna**
  (`rc_row.bg_w`; antes se descartaba como "out of scope (basic)"). Specs (`css.md`,
  `css_select.md` nuevo, `page_view.md`) + tests (13 nuevos en `css` → 88; 2 E2E en `page_view`
  → 76 por el pipeline real, incl. el idiom checked+label y el candado fail-closed nth=0) +
  `make test` (39 suites, 0 fallos) / `make asan` (39, exit 0) limpios + fuzz `fuzz-css` (149k
  smoke + 180s extendido, harness con elementos sintéticos que poblan nth/nsib/prev y hermanos
  con checked/disabled) y `fuzz-pv` (12k smoke + 150s sobre el código final) sin crash/leak/UB +
  **E2E visual** (`examples/pseudo-classes.html` por `--author-css --download-png`: link azul sin
  subrayado y nunca-rojo, tabla zebra con header naranja bold y rayas grises por columna, listas
  first/last/3n+1, `h2 + p` solo el inmediato, `h2 ~ blockquote` a distancia; y
  **news.ycombinator.com real: los subrayados desaparecieron** — títulos negros, subtexto gris,
  barra naranja, cero subrayados, como el HN real). **Única fuente de verdad verificada:** el fix
  vive en `cch_element_style` (módulo nuevo `css_chain`, extraído de `page_view` cuando el hito lo empujó sobre ~2000 líneas)/`resolve_context` (worker) y fluye idéntico a GUI, `--download-png`,
  `--dump-dom` y `--dump-layout` (mismo `tab_load_full`→`pv_build_styled`→`rd_build`→`rd_doc`).
  **Fuera de alcance:** `:not()`/`:is()`/`:where()`/`:has()`, familia of-type, `:empty`/`:target`/
  `:lang()`, pseudo-elementos `::` (generan contenido que el modelo no tiene), re-matcheo dinámico
  de `:hover`/`:focus` (necesita re-cascada por evento — hito de interactividad), `+`/`~` en
  compuestos no-sujeto. Ver `[[freedom-css-pseudo-classes-siblings]]`,
  `[[freedom-author-css-direction]]`.
- **Hito (keystone) — Identidad estable de nodo (`node_id`) + click dispatcher (Stage 4).**
  Dos gaps críticos del motor cerrados de golpe. **Stage 0 (keystone):** `dom_node_id` se propaga
  `dom_index` → `pv_run` → IPC (`tab.c`) → `rd_block` con una caminata pre-order idéntica a la de
  `dom_build`, así el painter puede mapear un pixel pintado de vuelta al nodo vivo del worker. Se
  añadieron tests en `test_page_view`, `test_render_doc` y `test_tab`; `make test`/`make asan`/`make
  fuzz-pv` limpios. **Stage 4 (dispatcher):** el JS de página puede registrar click handlers vía
  `addEventListener('click', fn)` y `element.onclick = fn`; la GUI, al hacer click sobre el contenido,
  resuelve el `node_id` bajo el cursor (`node_at_point`), envía `OP_CLICK` al worker vivo
  (`w->tab_worker`), el worker ejecuta `jd_fire_click` y re-deriva la vista, y la GUI repinta con la
  mutación aplicada (`apply_click_result`). Si el punto era un enlace, se sigue tras la mutación (la
  navegación por JS sigue gateada por `ln_resolve` + `JS_NAV_MAX`). Limitaciones v1: no hay bubbling,
  coords en el evento, ni eventos distintos a click; el click es síncrono y bloquea el hilo de render
  durante el round-trip. Specs actualizadas (`js_dom.md`, `tab.md`, `PLAN-layout-engine.md`) + tests
  (4 nuevos en `test_js_dom`, 1 E2E en `test_tab`) + `make test` (39 suites) / `make asan` (39, exit 0)
  limpios + `make fuzz-js`/`make fuzz-pv` verdes. *(Núcleo + IPC + integración GUI compilan y pasan
  tests; la verificación visual interactiva en Wayland queda pendiente al dueño.)* Ver
  `[[freedom-node-id-keystone]]`, `[[freedom-click-dispatcher]]`.
- **Hito Stage 3 — Flex por-item (`flex-grow`/`shrink`/`basis`/`order` + `flex-direction`), 2026-07-05.**
  El último stage pendiente del motor de layout (`spec/PLAN-layout-engine.md`): los valores por-item
  que el Hito 23b-7 ya **resolvía** en `css_style` por fin **cambian pixeles**. (a) **Plumbing:** los 5
  campos que `pv_run`/`rd_block` ya declaraban (Stage 3a a medias: existía `pv_set_flex` pero nadie
  emitía, el IPC no los serializaba → se desvanecían al cruzar el worker) ahora fluyen completos —
  `resolve_context` captura el **item** (el elemento inmediatamente interior al contenedor en la
  caminata de ancestros: el flex item CSS real) + la `flex-direction` del **contenedor**; 5 int32
  nuevos tras `cont_cols` en `write_view`/`read_view` (mismo orden en ambos); `rd_build` los copia
  **sin gate** de `caps.css` (estructura, como `cont_*`). (b) **Consumo en `layout_container`:** si
  algún item declara una propiedad flex, el root pasa de grid-de-columnas-iguales a **`BX_DISPLAY_FLEX`
  real** alimentando `bt_node.grow/shrink/basis` (la distribución la hace `fx_flex_line`, que ya
  existía sin usuarios); `order` se honra con un sort de inserción **estable** (empate = orden de
  documento, como CSS); `flex-direction: column` **apila** los items a ancho completo con el gap como
  espacio vertical (antes un nav vertical se aplastaba en N columnas — el bug visible de Wikipedia);
  basis sin definir/auto → cuota igual de la línea (el modelo plano no mide contenido pre-layout). Sin
  ninguna propiedad flex el camino previo queda **byte-idéntico** (candado de regresión: HN renderiza
  idéntico px a px). (c) **Fix CSS-correcto encontrado por el ciclo:** el whitespace **hijo directo**
  del contenedor creaba items anónimos fantasma (columnas vacías que diluían TODO flex/grid ya antes
  del hito); ahora no se emite (CSS: el whitespace entre items no crea items anónimos); el separador
  inter-celda de tablas fluidas lleva `cont_id == -1` y no se toca. (d) **Tools (fuente única):**
  `--dump-dom` imprime `dir/grow/shrink/basis/order` tras `cont=` (solo si el autor los fijó);
  `--dump-layout` ahora imprime también las **filas** (`row[i] top/h/x_off/w`) — la geometría de línea
  resuelta que expone la columna flex donde aterrizó cada línea, la única vista del eje principal sin
  imagen; pantalla, PDF, PNG y ambos dumps consumen el MISMO `layout_doc`/`rd_doc`. Specs
  (`page_view.md`, `tab.md`, `render_doc.md`, `dom_debug.md`, `freedom.md`, `PLAN-layout-engine.md`) +
  tests (2 nuevos `page_view` incl. whitespace-no-item, 1 `render_doc` estructura-sin-gate + defaults,
  1 E2E `tab` round-trip IPC → 39 suites verdes) + `make asan` (exit 0) + fuzz `fuzz-pv` (78k execs
  extendido, sin crash/leak/UB) + **E2E visual** (`examples/flex-items.html` por `--author-css
  --download-png` + `--dump-layout`: sidebar 200px + main flex:1 (w=740), `order` invertido (x_off 480
  vs 0), columna apilada, grow 2:1 = 626.7/313.3 px, caso sin props = columnas iguales; Wikipedia
  mejora — la fila Donate/Create account/Log in maqueta como fila y los navs verticales apilan; HN
  **byte-idéntico**). **Fuera de alcance (siguiente tanda del motor):** `align-items/self/content`,
  `justify-items`, `flex-wrap`, `row-gap`, `grid-template-rows`, `grid-auto-flow`,
  `grid-column/row: span N`, pesos `fr`, reversión visual de `*-reverse`. *(Módulos puros + IPC + E2E
  visual headless verificados; ventana Wayland interactiva pendiente al dueño.)* Ver
  `[[freedom-flex-per-item]]`, `[[freedom-box-engine-and-dispatcher]]`.
- **Hito (render) — Whitespace inter-bloque no pinta + identidad de ítem de contenedor (`cont_item`)
  (Wikipedia se lee como en un navegador real), 2026-07-05.** Diagnóstico con las propias tools
  (`--dump-dom`/`--dump-layout`/PNG, Principio 6): en Wikipedia el **30% de los bloques (473/1592)
  eran runs de solo-whitespace**, 412 con `block_break` → cada newline del HTML fuente entre `<div>`s
  pintaba una **línea vacía de ~26px** (~11.000px de página en blanco); y el lead ("the free
  encyclopedia that anyone can edit") salía **una palabra por línea** porque el path de contenedor
  trataba **cada run como un ítem** del grid/flex (correcto para celdas recolectadas de tabla,
  incorrecto para fragmentos inline del mismo hijo). Dos arreglos por el ciclo completo: (a)
  **regla CSS de cajas anónimas** en `page_view`: un run de solo espacios que **iniciaría un bloque**
  no se emite y su break queda **pendiente** (`pending_break`) para el primer contenido real del
  bloque; el espacio separador **en medio** de un bloque (`<b>a</b> <i>b</i>`) se sigue emitiendo
  (es contenido, candado `test_build_inline_whitespace_kept`); subsume-y-conserva el caso Stage 3
  (hijo directo del contenedor). (b) **`cont_item`**: `resolve_context` ya identificaba el elemento
  ítem (hijo directo del contenedor, Stage 3) — ahora `pv_cont_info.item` lo expone y `pv_build` lo
  mapea a un **ordinal por contenedor** (`pv_item_track`/`item_ordinal`; celda recolectada = un
  ordinal por celda; texto directo en el contenedor = ítem anónimo por run) → `pv_set_cont_item` →
  **1 int32 nuevo en `tab.c`** tras los 5 de flex (mismo orden ambos lados) → `rd_block.cont_item`
  **sin gate** (estructura como `cont_*`) → `layout_container` agrupa **runs consecutivos del mismo
  (cont_id, cont_item) en UN ítem** que fluye junto en su celda (breaks internos = líneas dentro de
  la celda; `order`/flex leen del primer run del grupo; el path columna mete el `gap` **entre ítems**,
  no entre líneas). `--dump-dom` imprime `item=N` tras `cont=`. Boyscout: hallazgo cppcheck en
  `render_doc.c` endurecido (init `resolved[]=""`, falla cerrado si un resolve devolviera OK sin
  escribir). Specs (`page_view.md`, `tab.md`, `render_doc.md`, `dom_debug.md`) + tests (4 nuevos
  `page_view`: inter-bloque/inline-se-conserva/identidad/celdas-distintas; 1 `render_doc`; 1 E2E
  `tab` por el worker re-exec'd → 39 suites, 0 fallos) + `make asan` (exit 0) + cppcheck limpio +
  fuzz `fuzz-pv` (95k execs extendido, sin crash/leak/UB) + **E2E visual**: Wikipedia pasa de
  **25.337px a 18.809px** (whitespace 473→28, los 28 restantes separadores inline legítimos), el
  lead y el artículo destacado **fluyen inline con sus links** como en un navegador real; HN
  **misma altura px** (2347), `rich.html` tabla de datos 3 columnas intacta, `box-model`/
  `css-sheet-layout`/`flex-items` correctos (±px por líneas vacías colapsadas). **Fuera de alcance
  (siguiente):** los menús dropdown de Wikipedia siguen reservando ~400px invisibles — usan
  `opacity:0`/`visibility:hidden`/`position:absolute` de overlay cerrado (el `position` de un
  wrapper ancestro sin caja propia no saca el subárbol del flujo); `visibility` no se soporta aún.
  *(Módulos puros + IPC + E2E visual headless verificados; ventana Wayland interactiva pendiente al
  dueño.)* Ver `[[freedom-interblock-whitespace-cont-item]]`, `[[freedom-flex-per-item]]`.
- **Hito (JS web moderna) — `querySelector` real + superficie ambiente identity-safe + caps de red
  para bundles (2026-07-05).** Para que el JS de sitios doblemente confiables (allow.conf ∩ js.conf)
  **corra de verdad** en la web moderna, sin ceder Zero-Trust/Zero-Knowledge — el pedido del dueño:
  "que Google/YouTube funcionen bloqueando rastreadores". Tres piezas, todas por el ciclo completo
  (39 suites, ASan 0, cppcheck 0, fuzz limpio). (a) **Caps de red** (diagnóstico con
  `--js=on --dump-console`: la URL del bundle `xjs` de Google mide 3456 B > el viejo tope de 2048 →
  el subrecurso se rechazaba en silencio): `URL_MAX_LEN` 2048→**8192**, `SF_MAX_URL` 8192,
  `LN_MAX_TARGET` 4096→**8448**, `TAB_MAX_SUBREQ` 64→**128**, `TAB_MAX_SUBRESOURCE` 8→**16 MiB**
  (= `SF_DEFAULT_MAX_BODY`; el main de YouTube ~10.6 MB). Boyscout: `url_validate_https` **no
  aplicaba el tope** (delegaba en `url_is_https`, sin chequeo de longitud) → se endureció con un
  escaneo acotado (C11 puro) que **falla cerrado** más allá de `URL_MAX_LEN`. (b) **`querySelector`/
  `querySelectorAll`/`matches`/`closest` reales** por el **mismo motor de selectores de autor**
  (`css_select` vía `css_chain`: única fuente de verdad — un selector matchea igual desde JS que
  desde una hoja). `cch_element_matches` (puro, extrae `build_chain` compartido con
  `cch_element_style`); `dom_query_selector*`/`dom_matches`/`dom_closest` en `dom` (parseo de lista
  con split de comas top-level bracket/paren/quote-aware → `csel_parse` por selector, uno malo se
  descarta y el resto sobrevive = fail closed; walk del subárbol: `root=DOM_NODE_NONE`=documento,
  elemento=descendientes **estrictos** como `Element.querySelector`; mapa inverso nodo→handle).
  `dom.c` ahora depende de `css_chain`/`css`/`css_select`/`css_color` (agregados al link de
  `test_dom`/`test_js_dom`/`test_js_env`). El selector es hostil → nuevo harness **`make fuzz-dom`**.
  (c) **Superficie ambiente moderna identity-safe** (el desbloqueo grande): shim de `js_dom`
  ampliado — **caché de identidad de nodo** (`__wc[h]`, para que `===` funcione: los frameworks lo
  exigen), navegación (`parentNode`/`children`/`firstElementChild`/`nextElementSibling`/`contains`),
  `classList` sobre el atributo class, `style` como objeto seteable, **`DocumentFragment`** (`__frag`
  junta hijos; el `appendChild`/`insertBefore` de un nodo real los **re-parenta**), `cloneNode`/
  `append`/`prepend`/`remove`, `createElementNS` (ns ignorado → elemento plano), `createDocumentFragment`/
  `createComment`/`createEvent`, `document` visibility/scripts/forms/links/activeElement; **stubs de
  constructores** `Element`/`Node`/`HTMLElement`/`Event`/... (vacíos, `instanceof`→false, inocuos);
  `matchMedia` **nunca matchea**; `MutationObserver`/`IntersectionObserver`/`ResizeObserver`/
  `PerformanceObserver` **nunca disparan** (sin observación → sin fuga de info); `getComputedStyle`→`''`
  (ZK: sin fuga de layout/fuente); `requestAnimationFrame`/`requestIdleCallback`/`queueMicrotask`
  alimentan la cola de timers y **`__fireDeferred` drena en RONDAS acotadas** (≤8 rondas, ≤256 total)
  para que un timer que agenda otro corra; **viewport normalizado fijo** `innerWidth=1920`
  (anti-fp, coincide con el ancho de `@media`, no el real). **`performance.timing`/`timeOrigin`/
  `navigation`/`getEntries*`/`mark`/`measure`** se agregaron en **`js_env`** (el dueño del reloj,
  antes sellado con solo `now`): los campos de `timing` son todos el mismo epoch fijo (deltas 0, sin
  fuga de timing real). **INQUEBRANTABLE — `window.open`/`postMessage`/`opener` siguen AUSENTES**
  (SOP por construcción: sin popups, sin mensajería cross-frame): agregarlos como stub rompió
  `test_eval_no_network_or_cross_origin_api` (el candado net-off) → revertido; una llamada lanza
  `ReferenceError` (fail closed). Specs (`dom.md`, `js_dom.md`) + tests (7 en `test_dom`, 8 en
  `test_js_dom`, 1 en `test_js_env`) + `make test`/`make asan` (exit 0) + cppcheck 0 + fuzz
  `fuzz-dom` (183k), `fuzz-url` (3M), `fuzz-pv`/`fuzz-css` sin crash/leak/UB + **E2E verificado**:
  `google.com` **renderiza** (caja de búsqueda, botones, links de footer — PNG revisado); su bundle
  de 3456 B ahora **carga y ejecuta** hondo en el framework WIZ (de ~5 errores inmediatos a 2
  internos propietarios como `__wizmanager`, fuera de alcance). **Honestidad sobre lo que NO corre:**
  **YouTube** es web-components/Polymer y `customElements.define` es no-op (sin upgrade ni Shadow DOM)
  → su app-shell no renderiza; módulos ES, event loop async real, identidad de nodo a través de
  re-parseo de `innerHTML`, `insertAdjacentHTML` (no-op, clobbearía), valores reales de
  `getComputedStyle` — todo diferido. *(Módulos puros + IPC + E2E verificados; ventana Wayland
  interactiva pendiente al dueño.)* Ver `[[freedom-js-modern-web-surface]]`, `[[freedom-live-js]]`,
  `[[freedom-parent-gated-xhr]]`, `[[freedom-sop-by-construction]]`.
- **Hito (JS web moderna) — `URL`/`URLSearchParams` + gate de tipo de `<script>` + `DocumentFragment`
  completo (Slashdot: JS de 14 a 0 errores de consola, 2026-07-06).** Objetivo del dueño: navegador
  ZT/ZK compatible con la web moderna; página de prueba **Slashdot** ("se ve fea"). Diagnóstico con
  `--js=on --dump-console`: 14 errores. Tres arreglos de JS por el ciclo completo (spec → test rojo →
  código → 39 suites + ASan limpio; **el fuzzing lo hace el dueño manualmente**). (a) **`URL` y
  `URLSearchParams`** como **shim JS puro** (`JD_URL_SHIM` en `js_dom`, instalado tras el modern-shim):
  parseadores de strings, **sin red/IO/API de host** → seguros en el sandbox, no filtran identidad. `URL`
  resuelve por **RFC 3986 §5** (parser básico WHATWG para el subconjunto http/https): componentes
  `protocol/host/hostname/port/pathname/search/hash/origin/username/password`, `searchParams` vivo,
  relativa-sin-base-absoluta lanza `TypeError`. `URLSearchParams`: `get/getAll/has/set/append/delete/
  sort/keys/values/entries/forEach/toString`, iterable, percent + `+`↔espacio. Define-guarded, acotado
  por el presupuesto de tiempo. Era el **primer** error de Slashdot (`URL is not defined`). (b) **Un
  `<script>` inline solo EJECUTA si su `type` es JS** (ausente/vacío o contiene "javascript"/
  "ecmascript"): `script_classify` (`html_parse`) pasó de **exclusión** (saltar "json"/"module") a
  **inclusión** — las plantillas `text/x-jquery-tmpl`/`text/html`/`text/template`/`text/babel` se
  ejecutaban y lanzaban `SyntaxError: '#each'`; ahora son bloques de datos que no corren (Secure by
  Default, fail-closed; espeja `ctype_is_javascript` de `tab.c`). (c) **`DocumentFragment` completo →
  jQuery carga (el dominó):** la detección de features de jQuery hace
  `createDocumentFragment().cloneNode(true).cloneNode(true).lastChild.checked`; el fragment mínimo sin
  `cloneNode`/`lastChild` lanzaba `not a function` y **abortaba todo el bundle** → `$ is not defined` en
  cada script inline (6 errores). Fix: helper `mkFrag()` (fragment recursivamente clonable con
  `cloneNode(deep)`/`lastChild`/`insertBefore`/`removeChild`/`prepend`) + getters `lastChild`/
  `lastElementChild` en el `wrap` de elemento (el valor detectado no importa; solo que **no lance** para
  que la librería defina `$`). Specs (`js_dom.md`, `html_parse.md`) + tests (2 en `test_js_dom` para
  URL/URLSearchParams, 1 para el clone-chain de fragment, 1 en `test_html_parse` para el gate de tipo) +
  `make test` (39 suites, 0 fallos) / `make asan` (exit 0, sin leaks/UB) limpios + **E2E verificado**:
  `--js=on --dump-console` de Slashdot pasó de **14 a 0 errores** (jQuery carga, `$` definido), y un HTML
  local ejercitó `URL` (userinfo/puerto/resolución relativa `../c/d.html`→`/a/c/d.html`) y
  `URLSearchParams` correctos; candado SOP intacto (`test_eval_no_network_or_cross_origin_api` verde).
  Config: `slashdot.org`+`fsdn.com` en `allow.conf`, `slashdot.org` en `js.conf` (allow∩js = confiable).
  **Pendiente (hito aparte, honesto): el LAYOUT CSS de Slashdot sigue feo** — es un diseño de dos
  columnas con `float` (Freedom no tiene `float`: el nav se apila a ancho completo y las slashboxes caen
  al fondo) y su panel blanco de contenido (caja DOM #83, `position:relative`, `l=120 r=336`, `bg=#fff`)
  es una **caja huérfana** (ningún `rd_block` la reclama como ancestro de caja → nunca se abre en flujo y
  `position_doc` la resuelve al fondo, y=26505), así que el gris `#cccccc` de la página (caja #0, el bg
  real de Slashdot) se ve detrás de las historias = las "franjas grises". **Resuelto por el hito de
  `float` (abajo):** las bandas side-by-side anidan en el box stack, así el panel `relative` queda en
  flujo y pinta su fondo detrás de las columnas — franjas grises extinguidas. *(Módulos puros + IPC +
  E2E de JS verificados; ventana Wayland interactiva pendiente.)* Ver
  `[[freedom-url-api-and-script-type-gate]]`, `[[freedom-js-modern-web-surface]]`,
  `[[freedom-per-script-isolation]]`, `[[freedom-external-scripts]]`, `[[freedom-sop-by-construction]]`.
- **Hito (render) — `float:left`/`float:right` + `clear`: bandas side-by-side que ANIDAN en el
  box stack (el layout de 2 columnas de Slashdot y "muchos sitios de esa época" se ve bien,
  2026-07-06).** El gap de layout que quedaba de Slashdot: la web de dos columnas de esa era se
  construye con `float`, que Freedom ignoraba → sidebar y main se **apilaban** vertical y un panel de
  fondo `position:relative` sin contenido directo se iba al fondo (las "franjas grises"). Ciclo
  completo (spec `float.md` → tests rojos → código → 39 suites + ASan 0 + E2E visual). (a) **`css`:**
  dos propiedades nuevas whitelisteadas **no heredadas** — `float` (`css_float`: none/left/right) y
  `clear` (`css_clear`: none/left/right/both), fail-closed ante keyword desconocido; oráculo de
  `fuzz-css` reforzado con sus rangos. (b) **`flex_layout` (puro):** `fx_float_pack` empaqueta una
  banda — items `left` desde el borde izquierdo hacia la derecha, items `right` desde el derecho hacia
  la izquierda (orden de documento), clamp `x>=0`, sin wrap v1; sin I/O ni asignación, testeado.
  (c) **`page_view`:** `resolve_context` resuelve el **float ancestro más cercano** (side + un
  `float_id` de un registro en orden de documento que agrupa los runs de UN elemento flotado) y el
  `clear` del bloque hoja propio; 3 campos nuevos en `pv_run` (`float_side`/`float_id`/`float_clear`),
  **estructura** como `cont_*` (nunca gateada). (d) **IPC (`tab.c`) + `render_doc`:** 3 int32 nuevos
  tras `cont_item` en `write_view`/`read_view` (mismo orden ambos lados) + copia **ungated** en
  `rd_build`; `dom_debug` imprime `float=left|right(#id)`/`clear=N`. (e) **Painter (`browser_ui.c`):**
  `layout_float_band` detecta una banda maximal de bloques con `float_id>=0` (un bloque no-flotado o
  con `clear` la termina), la **reconcilia a su caja COMÚN** (`band_common_box` = prefijo común de los
  box-paths) — a diferencia de un contenedor flex/grid que hace `close_all_boxes`, la banda **NO cierra
  las cajas**, así un panel `position:relative`/bg que la envuelve queda **abierto en flujo y pinta su
  fondo detrás de las columnas** (extingue las franjas grises); agrupa por `float_id` en items, ancho
  del `box_w` de autor (los sin ancho reparten el sobrante), empaqueta con `fx_float_pack`, y fluye
  cada item en su columna (sub-estado, como el pase flex por-item). **Bug preexistente extinguido
  (boyscout):** una caja `position:relative` que envuelve varios bloques estaba **tanto** en
  `L.boxes` (pintada en flujo, correcta) **como** en `L.positioned` (porque `bt_resolve_positioning`
  incluye relative), así que el pase de posicionados la **re-pintaba encima** (su bg tapaba todo salvo
  el primer bloque); `position_doc` ahora **filtra de la lista de posicionados las cajas ya pintadas
  en flujo** (`in_flow`), dejando solo out-of-flow real (absolute/fixed). Specs (`float.md` nuevo,
  `css.md`) + tests (float+clear en `css`; `fx_float_pack` en `flex_layout`; threading en `page_view`;
  copia ungated en `render_doc`; roundtrip IPC en `tab`; E2E `test_dump_layout_float_two_columns` en
  `test_freedom` — 2 columnas a distinto `x_off` + panel en flujo) + `make test` (39 suites, 0
  fallos) / `make asan` (exit 0, 0 leaks/UB) limpios + **E2E visual** (`--author-css --download-png`
  de un repro Slashdot-like: sidebar gris a la izquierda, columna principal a la derecha, footer con
  `clear` abajo spanning, panel de fondo detrás; sin `--author-css` las 2 columnas también — layout es
  estructura; `rich.html` sin regresión). **Límites v1:** sin **text-wrap** alrededor de un float
  solo (la banda es una fila autocontenida; el contenido no-flotado siguiente limpia debajo); la
  decoración de caja **propia** de un item de float (bordes de una `.story` dentro de `.main`) no se
  compone (mismo límite que flex/grid — el bg del panel envolvente **sí** pinta); `clear` colapsa
  left/right/both a "terminar la banda"; floats sin ancho reparten el sobrante; sin `%`; profundidad
  por `RC_BOX_STACK_MAX`, items por `BT_MAX_CHILDREN`. *(Módulos puros + IPC + E2E visual headless
  verificados; ventana Wayland interactiva pendiente al dueño.)* Ver `[[freedom-float-layout]]`,
  `[[freedom-box-engine-and-dispatcher]]`.

### 7.3 Roadmap — por cruzar

- **Hito 24 — Freebug (consola de desarrollo JS) + scripts externos por soberanía.** Para no estar
  "a ciegas" sobre qué JS corre y por qué falla. **FB-1 (CERRADO):** captura de consola en el backend.
  Módulo **puro** `freebug` (`fb_`): `fb_buffer` acotado (caps `FB_MAX_ENTRIES`/`FB_MAX_ENTRY_BYTES`/
  `FB_MAX_TOTAL_BYTES`, fail-closed: trunca la entrada gigante, descarta entera la que excede el total/
  conteo, flag `overflow`). `js_dom` gana `jd_install_console(ctx, fb_buffer*)` que instala un `console.
  {log,info,warn,error,debug,trace,dir}` **capturador** (`JS_NewCFunctionMagic`, nivel=magic; junta args
  con espacio vía `JS_ToCStringLen`; un `toString` que lanza se traga → `<unprintable>`); el puntero al
  buffer vive en el **runtime opaque** (libre; el context opaque sigue siendo el `dom_index`). `tab`:
  `child_state.log` persiste entre cargas, se resetea por carga/eval, se instala en `child_load`, y una
  **excepción no capturada** del script de página se empuja como `FB_ERROR`; se **drena por IPC**
  (`write_console`/`read_console`) y viaja en `tab_page.console` (carga) y `tab_eval_result.console`
  (REPL). `tab_eval` (ya existía) **es** el backend del REPL: evalúa en el contexto vivo y devuelve
  valor/excepción. Spec (`freebug.md`) + tests (9 `freebug` + 4 `js_dom` console + 3 E2E `tab`) + `make
  test`/`make asan` (36 suites, exit 0) + `make fuzz-fb` (931k execs, sin crash/leak/UB; los NUL
  embebidos se preservan porque el wire es length-prefixed). **FB-1b (CERRADO): vista de consola
  headless.** `freedom.c` gana `--dump-console` (corre el JS de la página vía `tab_load_full(run_js)` e
  imprime la consola capturada en stdout: `=== Freebug console (n) === / [nivel] texto`) y honra `--js`
  en headless (corre JS cuando resuelve a `on`); `--dump-console` **fuerza JS on** sin importar el orden
  de flags. Es la forma de **ver** el comportamiento de JS **sin Wayland** (verificable aquí y por el
  dueño), riesgo cero al GUI interactivo (solo toca el entry headless). 2 tests E2E en `test_freedom`
  (11 total). **FB-2 (GUI) — IMPLEMENTADO y VERIFICADO VISUALMENTE** (weston headless con backend
  X11 sobre Xvfb + captura ImageMagick `import`; ver `[[freedom-gui-visual-verification-weston]]`):
  **ventana Wayland nueva** (segundo `xdg_toplevel` en `gui/browser_ui.c`, struct
  `freebug_window` con su propia surface/buffer/cairo/configure), toggle **F12** (en `handle_key_press`)
  **y** ítem de hamburguesa "Freebug console (F12)" (`UI_MENU_FREEBUG`); `Esc`/`F12` cierra desde dentro.
  Panel de log que pinta `browser_window.console` (color por nivel) sobre un editor JS redimensionable
  (divisor arrastrable; `tf_field` admite `\n`) que con **`Ctrl+Enter`** llama `tab_eval` contra la
  **página viva** y muestra valor/excepción + la consola del propio eval; `Ctrl+L` limpia, rueda/flechas
  scrollean. **Prerrequisito resuelto:** el GUI abría/cerraba un worker por render; ahora el worker de la
  pestaña activa se **mantiene vivo** (`browser_window.tab_worker`, cerrado al re-render/cambiar/cerrar
  pestaña; `drop_repl_worker`; `freebug_repl_worker` lo recrea lazy tras un cambio de pestaña) para que el
  REPL evalúe contra el DOM vivo. Ruteo de input por foco de surface (`kbd_focus`/`ptr_focus` en
  enter/leave; los listeners compartidos del seat enrutan a Freebug con `freebug_owns_surface`). Compila
  **warning-clean** (`make`/`make test` 36 suites/`make asan` exit 0) y se **verificó en pantalla**: el
  screenshot confirma la 2ª ventana, el panel de log con la consola capturada **coloreada por nivel**
  (log gris, info cian, warn amarillo, error rojo: `console.log/info/warn` + el `ReferenceError` no
  capturado) y el editor con prompt/caret/placeholder. Afordancia de arranque `FREEDOM_FREEBUG=1` abre
  Freebug al inicio (como auto-open-devtools; habilitó la captura sin inyectar F12). **Lo no inyectable
  aquí** (faltan `wtype`/`ydotool`): el *keypress* F12/`Ctrl+Enter` en vivo — pero `freebug_show` (lo que
  F12 invoca) está probado por el screenshot y `tab_eval` (el REPL) por `test_tab` + `--dump-console`.
  **Limitaciones v1 (notas):**
  consola por-pestaña activa (se limpia al cambiar de pestaña; no es por-tab persistente), sin auto-repeat
  de tecla en el editor, sin scroll-a-cursor multilínea. **EXT (scripts externos): CERRADO** — ver el
  Hito 24 EXT en §7.2 (los `<script src>` corren para hosts en **allow.conf Y js.conf**, fetcheados por
  el padre bajo TODA la política; la doctrina "externos nunca corren" quedó revertida SOLO para hosts
  doblemente confiables). Ver `[[freedom-external-scripts]]`, `[[freedom-freebug-console]]`.
  - **FB-3 (CERRADO) — Ubicación de errores `file:line:col` + completitud del wrapper de elemento.**
    Para que Freebug sea útil a un desarrollador, cada error ahora dice **dónde**: `js_sandbox` gana
    `js_eval_named` (etiqueta la fuente; el worker nombra cada `<script>` inline **`inline #N`**) y el
    parser **puro** `js_loc_from_stack` (extrae `file:line:col` del primer frame del `.stack` de
    QuickJS, forma `at <fn> (<file>:<line>:<col>)`; tolera URLs con `:`, solo-línea, basura/`NULL`;
    fuzzeado). `js_result` y `fb_entry` ganan `file/line/col` (dueño, `NULL`/0 = sin ubicación);
    `fb_buffer_push_loc` (push queda como wrapper sin ubicación); el wire de consola de `tab.c` los
    serializa (acotados por `FB_MAX_FILE_BYTES`); la GUI los pinta en tono atenuado antes del mensaje
    y `--dump-console` como `[nivel] file:line:col texto`. Con esta herramienta se diagnosticaron y
    **arreglaron los 4 errores de google.com** (`cannot read property 'ved' of undefined`,
    `not a function`×2, `cannot read property 'substring' of undefined`): todos eran **wrappers de
    elemento incompletos**. Se completó el wrapper (identity-safe, como `document.fonts`): `dataset`
    (Proxy sobre `data-*`), `hasAttribute`, `removeAttribute` (native nuevo `dom_remove_attribute`),
    y `src`/`href` (string, `''` si ausente — sin resolver a URL absoluta). **El 5º error surfaceado,
    `XMLHttpRequest is not defined`, se DEJA a propósito**: es la frontera Zero-Trust "sin API de red
    en JS" (SOP por construcción, candado `test_eval_no_network_or_cross_origin_api`); decisión del
    dueño de mantener la frontera, no stubbearla. Spec (`freebug.md`, `js_sandbox.md`, `dom.md`,
    `js_dom.md`, `tab.md`, `freedom.md`) + tests (9 `js_sandbox` loc/named, 3 `freebug` push_loc,
    1 `dom` remove_attribute, 4 `js_dom` wrapper, 2 E2E `tab` ubicación+idioms) + `make test`/`make
    asan` (exit 0) limpios + fuzz `fuzz-js` (parser sobre bytes arbitrarios) y `fuzz-fb` (push_loc)
    sin crash/leak/UB + **verificación visual de Freebug** (weston+Xvfb, `FREEDOM_FREEBUG=1`: el PNG
    confirma `inline #N:line:col` atenuado + niveles coloreados). Ver `[[freedom-freebug-error-locations]]`,
    `[[freedom-freebug-console]]`, `[[freedom-element-wrapper-completeness]]`.
- **Hito 9b — Fetch asíncrono (imágenes + multipestaña).** Sacar también las imágenes del hilo
  principal (hoy `load_images` hace fetch síncrono dentro del worker durante el render) y permitir
  **carga concurrente entre pestañas** (generación por pestaña en vez de global, entrega a la pestaña
  destino aunque esté en segundo plano). Destraba además I2P (lento de tejer túneles).
- **Hito 19b — Imágenes: formatos + lazy.** (Hito 19a imágenes locales y el sub-hito **JPEG**, ya
  cerrados arriba.) Falta: (a) **SVG** (¿`librsvg`? evaluar superficie de ataque); (b) **WebP/GIF/
  AVIF** (cada uno superficie nueva, contra doctrina salvo justificar); (c) **Lazy loading**
  (decodificar solo lo visible). Mantener Privacy by Default (opt-in `Ctrl+I`).
- **Hito 20e — JS vivo: lo dinámico real.** Cerrados 20b (ejecución + título/texto), 20c
  (construcción + eventos/timers sintéticos), 20d (`innerHTML` + superficie ambiente identity-safe),
  **parte 1** (`location.*` reales + navegación por JS gateada — ya cerrada arriba), **clic**
  (Stage 4 del keystone, arriba) y **scripts externos** (Hito 24 EXT, arriba). Falta (parte 2):
  **timers async reales** (event loop en el worker que empuja vistas nuevas), getter de `innerHTML`
  (serialización), `defer`/`async` y módulos ES para scripts externos, scroll a ancla de fragmento
  (`#id`), y **repintado incremental** en mutación. Persistir el modo y la allowlist con Hito 10.
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
- **Hito 23b-8 Steps A–D (CERRADO) — Motor de cajas: pintar borde/box-sizing/padding/sombra/outline
  + composición ANIDADA.** Steps A/B/C hilaron y pintaron la decoración de caja de un solo nivel
  (`block_id`, `paint_box_decoration`). **Step D (2026-06-29)** convirtió las cajas en un **ÁRBOL**:
  nuevo `pv_box_def` {parent_id, hbox, bg, 27 campos de decoración} indexado por `block_id`
  (`pv_view.boxes`/`rd_doc.boxes`), con la decoración **movida fuera de los runs** (extinguida la
  duplicación per-run del Step A; los runs solo llevan `block_id`). `page_view` registra **cada**
  bloque-con-caja ancestro y estampa `parent_id`; el painter mantiene una **pila de cajas abiertas**
  (`reconcile_boxes`) y compone cada hija dentro del rect de contenido de su padre (en vez de partir
  al padre), pintando exterior→interior (orden z implícito correcto). Resuelve el bug visual: una
  `.outer` que envuelve `<p>…</p><div class=inner>…</div><p>…</p>` ahora pinta UNA caja exterior con
  la interior anidada (antes: dos cajas + hermana). Cubre **wrappers sin texto** (una card cuyo único
  hijo es un body div). Validado: `make test`/`make asan` (exit 0), `fuzz_page_view` 138k sin
  crash/leak/UB, revisión visual (`--author-css --download-pdf` de `nested.html`) + byte-idéntico en
  `box-model.html`/`rich.html`. v1: imagen/input/contenedor flex cierra las cajas; indent de lista no
  se aplica a la caja; box-sizing width math aún no se resta. **Gaps deferidos con razón**
  (`spec/box_engine.md`): dirty-flag de invalidación (no hay path incremental → sería código muerto) y
  z-index explícito (solo aplica con `position` fuera de flujo → Stage 2). Ver `[[freedom-box-engine-and-dispatcher]]`.
- **Hito (UI) — Botón de recarga + edición de listas de host + autocompletado de omnibox.** Tres
  features de UI (todo en `gui/browser_ui.c` salvo la lógica pura). (a) **Botón de recarga** en la
  toolbar (tercer botón izquierdo, `UI_RELOAD_X`, icono `draw_reload` de Cairo) + `F5`/`Ctrl+R`
  (ya existían). (b) **Editar block/allow/js.conf desde la UI:** módulo **puro nuevo `hostedit`
  (`he_`)** que valida el host actual fail-closed (`he_make_line`: solo hostname registrable, sin
  `/`/`:`/esquema) y construye la línea; `he_text_has_host` deduplica. Ítems de hamburguesa +
  atajos **`Ctrl+Shift+B`/`A`/`J`** añaden el host de la página a `block.conf`/`allow.conf`/`js.conf`
  (en `$FREEDOM_HOSTS_DIR` o `~/.config/freedom`, append atómico 0600) y **recargan el filtro en
  memoria** al instante. (c) **Omnibox autocompletado** desde `allow.conf` tratado como favoritos:
  `he_suggest` (puro: prefijo primero, luego substring, dedup) alimenta un dropdown bajo la barra de
  URL (Tab completa, ↑/↓ navegan, Enter/clic confirman). **Cláusula anti-monolito** añadida a §3.4
  (modo boy-scout): un archivo cerca de ~2000 LoC se parte por contratos — por eso la lógica nueva
  fue al módulo `hostedit`, no a engordar `browser_ui.c` (>5000 LoC, deuda señalada). Spec
  (`hostedit.md`) + 10 tests + `make asan` exit 0. (d) **Selección de texto en la omnibar:** se
  añadió `url_bar_anchor` al modelo puro `browser_state` (selección = `[min(anchor,cursor),max)`),
  con `browser_url_bar_extend_cursor`/`_set_cursor`/`_select_all`/`_selection`/`_delete_selection`
  (insert/backspace/delete borran la selección primero; mover/clic/teclear la colapsan). GUI:
  **shift+←/→/Home/End** extienden, **Ctrl+A** selecciona todo, **Ctrl+X** corta, **Ctrl+C** copia la
  selección (o el campo completo) y **Ctrl+V** la reemplaza; resaltado pintado tras el texto. Test
  `test_url_bar_selection`. `make test` **780 OK** + `make asan` exit 0. **Verificación visual del chrome pendiente al
  dueño** (el flujo weston-sobre-Xvfb no cooperó esta sesión; sin inyección de teclado no se dispara
  el dropdown/menú). Ver `[[freedom-ui-host-editing-omnibox]]`.
- **Hito 23b-8 (resto, Stage 2 — `position`/z-index, CERRADO).** El Hito 23b-7 ya
  **resolvió los valores** de `position`/`box-shadow`/flex-por-item/grid-por-item en
  `css_style` (Hito 23b-7). El **Stage 2 del box engine** los consume para `position`
  y `z-index`:
  - **Pura (completa, testeada, ASan/UBSan limpio, 0 leaks/UB):** `bt_resolve_positioning`
    (`include/box_tree.h` + `src/box_tree.c`) — resuelve el containing block (ancestro
    posicionado más cercano para absolute, viewport para fixed), aplica `top`/`left`
    (v1: `right`/`bottom` leídos pero ignorados, `CSS_LEN_AUTO`→unset), ordena por
    `(z_index ASC, doc_order ASC)`. 13 tests en `test_box_tree.c`.
  - **GUI integration (CERRADA):** `layout_doc` skip absolute/fixed **sin cerrar el
    wrapper padre** (el bug `close_all_boxes` fragmentaba el wrapper en N pedazos
    h=0; el ÚLTIMO, al fondo de la página, se volvía containing block → los absolute
    anclaban al fondo en vez de cerca del wrapper); `open_box` aplica offset por insets
    para relative/sticky (sticky fail-closed→relative); `position_doc` arma geometry
    arrays y llama `bt_resolve_positioning`; `paint_structured` + `write_doc_pdf` +
    `write_doc_png` pintan las positioned boxes en stacking order sobre el in-flow
    (z<0 skipped en v1, documentado). **Verificado con `--dump-layout`** (tooling
    nuevo, abajo): `position-zindex.html` — `nbox=2` (era 10), z=1 box en `y=244.7`
    (era 548.7, al fondo); `position-overlay.html` — wrapper `h=486.2` (era
    fragmentado), badge en `y=56` (48+8). `position:relative` sigue funcionando
    end-to-end.
  - **Tooling (`--dump-layout`, CERRADO):** nuevo flag headless que imprime la
    **geometría resuelta** (cajas in-flow + positioned boxes en orden de stacking) a
    stdout — el complemento de `--dump-dom` (que muestra la entrada al layout,
    `--dump-layout` muestra la salida). Es la forma de verificar
    position/z-index/box-engine **sin Wayland ni imagen**: los bugs de
    anclaje/fragmentación se ven como números (`ui_dump_layout` en `gui/browser_ui.c`,
    declarada en `include/ui.h`). Test E2E en `test_freedom`
    (`test_dump_layout_no_wrapper_fragmentation`: el wrapper no se fragmenta y el
    z=1 absolute ancla cerca del wrapper, no al fondo).
  - **Deferred (no bloquean el core):** negative `z-index` (dos-pass painter);
    `right`/`bottom` insets; `position:sticky` con scroll hooks; containing block =
    padding-box (hoy border-box). `position:sticky` cae a `relative` (fail-closed).
  - **Stage 3 (flex por-item) CERRADO v1 el 2026-07-05** (hito propio en §7.2: grow/
    shrink/basis/order/direction de extremo a extremo + whitespace-no-item + filas en
    `--dump-layout`); **Stage 4 (event dispatcher) parcialmente cerrado** (click). Restan del
    plan: align-items/self, flex-wrap, row-gap/grid-template-rows/span N/pesos `fr`, y más
    eventos. El plan completo está en `spec/PLAN-layout-engine.md` y `spec/box_engine.md`. Ver
    `[[freedom-flex-per-item]]`, `[[freedom-box-engine-and-dispatcher]]`.
- **Hito 23b parte 2 — CSS de autor: más cobertura.** (Parte 1 `@media`+`prefers-color-scheme`, el
  sub-hito **flex/grid desde `<style>`**, el **box model `margin`/`padding`/`width`/`max-width`**
  —Hito 23b-3—, y la **resolución de valores** de `position`/`border`/`box-sizing`/`box-shadow`/flex-y-
  grid-por-item —Hito 23b-7— ya cerrados arriba; **honrarlos en el painter** es el Hito 23b-8.) Falta
  además: render de `@media print` al PDF; expansión de `repeat()`/`minmax()`/pesos `fr` en grid (hoy
  todo track = 1fr igual); ~~combinadores **hermano** (`+`/`~`) y **pseudo-clases**~~ (cerrados en el Hito 23b-9: hermanos + subconjunto de pseudo-clases; quedan `:not()`/`:is()`/of-type/pseudo-elementos `::`) (los combinadores
  **descendiente/hijo** y los **selectores de atributo** + **`!important`** ya cerrados arriba, Hito
  23b-4); persistir el toggle de estilos de autor y el modo reader con el Hito 10. (`line-height` y
  `text-decoration` cerrados en Hito 23b-5; `font-family`/`text-transform`/`letter-spacing`/
  `word-spacing`/`text-shadow`/`opacity`/`vertical-align`/`text-indent`/`white-space`/`list-style-type`
  cerrados en Hito 23b-6. Falta fino dentro de esa tanda: casado exacto de fuentes, blur/multi-capa de
  `text-shadow`, `letter-spacing`/`text-indent` en `%`, `vertical-align` con longitud/top/middle/bottom,
  preservación de espacios de `white-space`.)
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
