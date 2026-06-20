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
| Parser | `html_parse` (`hp_`), `dom` (`dom_`) | DOM inerte con Lexbor, strip de `<script>`/`on*`; índice consultable de solo lectura. |
| JS/anti-FP | `js_sandbox`/`js_dom`/`js_env`, `anti_fp` | QuickJS-ng vendorizado sin I/O; bindings sellados; relojes/pantalla/readback normalizados. |
| Aislamiento | `os_sandbox` (`os_`), `tab` (`tab_`) | seccomp-bpf fail-closed + Landlock; worker por pestaña que parsea/decodifica/ejecuta contenido hostil; el padre sobrevive. |
| Estado cifrado | `local_store`, `disk_store` | AEAD (AES-256-GCM/ChaCha20) + Argon2id; escritura atómica 0600 (Zero Knowledge). |
| Render | `page_view` (`pv_`), `render_doc` (`rd_`), `css_color` (`cc_`) | Display list inerte → bloques pintables; color de autor solo con `caps.css`; `src` de imagen resuelto contra el origen. |
| Imágenes | `image_decode` (`img_`) | Decodificado **PNG dentro del worker confinado**; topes anti-DoS; salida ARGB lista para Cairo. |
| Formularios | `form` (`fm_`) | **GET/POST nativos sin JS**; target no-https no representable (fail-closed). |
| UI | `ui`/`browser` (puros) + `gui/browser_ui.c` (orquestador Wayland+Cairo) | Toolbar, historial, barra de URL editable, scroll, menú de opciones, navegación por clic, submit de formularios. |
| Auditoría | `spec/threat-model.md` | Activos/adversarios/fronteras → mitigaciones. |

**Decisiones de doctrina vigentes** (no evidentes en el código; no re-litigar):
- **Navegabilidad sobre PQ estricto:** un host que no puede KE híbrido PQ **avisa** (toast
  "classical TLS 1.3"), no bloquea (`SF_POLICY_ALLOW_CLASSICAL_KE`). TLS<1.3, cadena inválida y
  SHA-1 siguen fatales. Ver `[[freedom-navigability-over-strict-pq]]`.
- **Umbral RSA<3072 solo al leaf** (los intermedios RSA-2048 de la Web PKI son válidos). Un
  sitio con leaf RSA-2048 se sortea con la excepción por host **Ctrl+Shift+E** (PERMISSIVE, solo
  sesión).
- **Privacy by Default:** imágenes y colores de autor (CSS) **apagados**; opt-in en el menú.
  Imágenes solo **PNG** y fetch **síncrono**; otros formatos → placeholder (superficie mínima).
- **Modo boyscout:** un "fix" puede destrozar un módulo de seguridad; ante una regresión, diff
  contra el commit inicial antes de tocar nada. Ver `[[freedom-security-modules-butchered-by-fix-commits]]`.

### 7.2 Roadmap — por alcanzar

- **Hito 6 — Pulido interactivo de la GUI (en curso).** Todo en `gui/browser_ui.c`
  (orquestador; sin lógica de seguridad nueva). *(compila + enlaza bajo los flags endurecidos;
  **sin verificar visualmente**: requiere una sesión Wayland.)*
  - [x] **Modo oscuro/claro** en el menú hamburguesa (`ui_theme_dark`/`ui_theme_for`, item
    `UI_MENU_DARK`). Toggle = swap de paleta + repaint (sin red); comparte las métricas con el
    tema claro, así el box model vive en un solo sitio.
  - [x] **Hover en los botones del toolbar** (Atrás/Adelante/Go/menú): la misma afordancia que
    ya tienen los enlaces —resaltado `btn_hover_bg` + cursor de mano sobre botones accionables
    (`toolbar_button_at`/`hot_actionable`, fuente única con el hit-test del clic)—.
  - [x] **Destino del enlace al pasar el cursor**: tira inferior persistente con el `href` bajo
    el puntero (`draw_hover_url`); el toast se apila encima.
  - [x] **Indicador de carga** (reloj "busy") en el tab/barra de URL durante un request
    (`show_busy` pinta y presenta un frame antes del fetch síncrono; título "Loading..."). Honesto:
    estático, no animado, porque el fetch bloquea el event loop (animarlo es el Hito 9).
  - [x] **Barra de scroll visible** (`scrollbar_metrics`/`draw_scrollbar`): track + thumb en un
    gutter derecho **siempre reservado** (`content_width` resta el gutter, una sola fuente de
    verdad para pintor y hit-test de enlaces/inputs). Arrastre del thumb y clic-en-track
    (`scrollbar_drag_to`, estado `dragging_scroll`); aparece solo si el contenido excede el
    viewport.
  - [x] **Márgenes/padding más amplios** (`UI_TEXT_MARGIN` 8→20): el contenido respira y los
    bordes de resize caen en el margen, no sobre el texto.
  - [x] **Controles de ventana (CSD)**: mover (arrastrar el titlebar → `xdg_toplevel_move`),
    maximizar/restaurar (botón `[]`, estado leído de `XDG_TOPLEVEL_STATE_MAXIMIZED`), minimizar
    (`_`), cerrar (`X`), y **redimensionar** por bordes (`resize_edge_at` → `xdg_toplevel_resize`,
    laterales solo en el área de contenido para no robar clics al chrome). Bajo SSD el compositor
    sigue dueño de los bordes.
  - [x] **Atajos vim** en el área de contenido (sin foco en la URL): `j`/`k` línea, `space`/`b`
    página, `gg` arriba, `G` abajo, además de `Home`/`End` y las flechas/PgUp-Dn ya existentes.
- **Hito 7 — CSS estático / box model enriquecido (Secure by Default, sin JS).** Estrategia del
  dueño: máxima legibilidad con superficie mínima. Lógica pura y testeable; la GUI solo cablea.
  Base ya existente: escala de headings, `paragraph_gap`, `content_margin`, color de autor
  (`css_color`, gateado por `caps.css`).
  - [x] **Box model por etiqueta** — módulo puro `box_style` (`bx_`): hoja de estilo del UA
    (márgenes/padding en `em` + `display`) por etiqueta vía búsqueda binaria sobre tabla ordenada,
    más `bx_parse_display` (gateado por el llamante con `caps.css`). Spec + test (16) verde +
    ASan/UBSan limpio. `body` con margen 0 (el gutter lo da el chrome).
  - [x] **Flexbox 1D + grid básico** — módulo puro `flex_layout` (`fx_`): solver del eje principal
    (`flex-grow`/`shrink` con congelado iterativo al `min`, `gap`, `justify-content` completo) y
    grid de columnas iguales (`repeat(n,1fr)`) + colocación fila-por-fila. Acotado (`FX_MAX_ITEMS`,
    sin VLA/alloc). Spec + test (19) verde + ASan/UBSan limpio.
  - [x] **Box model cableado al pintor**: puente puro `rd_block_tag` (`render_doc`: kind ->
    etiqueta HTML canónica, +1 test, ASan limpio) y la GUI compone `rd_block_tag ->
    bx_default_for_tag` en `block_margins` para espaciar cada bloque por su margen UA (em -> px del
    propio tamaño de fuente) con **colapso de márgenes** básico, sustituyendo el `paragraph_gap`
    único. Headings con jerarquía real, párrafos/listas con su margen. *(compila + enlaza
    endurecido; **sin verificar visualmente**: requiere Wayland.)*
  - [x] **Árbol de cajas (motor de layout)** — módulo puro `box_tree` (`bt_`): layout recursivo que
    apila bloques (con colapso de márgenes + padding), delega flex/grid en `flex_layout` y baja con
    el ancho resuelto; topes anti-DoS (`BT_MAX_DEPTH`/`BT_MAX_CHILDREN`), sin VLA/alloc. Spec +
    test (13) verde + ASan/UBSan limpio. Compone `[[box_style]]` + `[[flex_layout]]`.
  - [x] **Construcción del árbol desde el DOM + pintado** — pipeline puro (TDD): `page_view` extrae
    el contenedor flex/grid de autor más cercano por run (`cont_id`/`display`/`gap`/`justify`/`cols`
    vía `display`/`gap`/`justify-content`/`grid-template-columns`), `tab` lo serializa por IPC,
    `render_doc` lo transporta **gateado por `caps.css`** (apagado → flujo plano, cero regresión).
    La GUI agrupa los bloques de un contenedor, mide cada ítem y los dispone en columnas con
    `bt_layout`/`flex_layout` (flex=fila de N columnas, grid=`cols` con wrap), traduciendo las filas
    a su columna (`x_off`). Básico: cada bloque = un ítem; ítems multi-bloque y anidamiento profundo
    quedan fuera. Tests: page_view 30, render_doc 20, tab 21 verde + ASan limpio. La GUI **sin
    verificar visualmente** (requiere Wayland).
  - [x] **Reading mode (sepia)** — tercera paleta `ui_theme_sepia` en el menú (papel cálido + tinta
    marrón), con `theme_mode` (light/dark/sepia) y un toggle **"Force theme colors"** que ignora los
    colores de autor (legibilidad > fidelidad). Solo `gui/browser_ui.c`; **sin verificar visualmente**.
  - [x] **`background-color` de autor** — pipeline puro: `page_view` extrae la declaración
    `background-color` (longhand) a `bg_rgb` (no hereda en CSS; se toma del ancestro más cercano para
    que el fondo del bloque se vea tras su texto), `tab` lo serializa por IPC, `render_doc` lo
    transporta gateado por `caps.css`. La GUI lo pinta tras el bloque (orquestador). Spec + tests
    (page_view 27, render_doc 19, tab 21) verde + ASan limpio.
- **Hito 8 — Transcodificación de charset.** Mostrar acentos en vez de `?` (Latin-1 y otros →
  UTF-8) en `page_view`/`browser_set_page`. Lógica pura + tests; sin dependencia nueva.
- **Hito 9 — Fetch asíncrono.** Sacar `secure_fetch` del hilo del event loop (el worker/IPC de
  `tab` ya existe) para: spinner **animado** real, no congelar la UI, carga de imágenes no
  bloqueante, y `do_submit_post` (POST) con el mismo fallback clásico que el GET.
- **Hito 10 — Persistencia de preferencias por sitio.** Opt-in de imágenes/CSS/tema y excepciones
  de host (hoy solo sesión) cifrados con `local_store`/`disk_store`.
- **Pendiente de fondo (hitos propios, fuera del camino corto):** motor de cajas CSS de autor
  completo; JS-vivo (mutación DOM → repintado, eventos, timers); `querySelector`/selectores CSS;
  otros formatos de imagen (JPEG/WebP/GIF — superficie nueva, contra doctrina salvo justificación);
  `pledge`/`unveil` en OpenBSD; PSL completa; scroll al ancla de fragmento (`#id`); multiplexado de
  varias pestañas.

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
  (`openssl list ...`, `pkg-config ...`). y haz fuzzing por ejemplo con American Fuzzy Lop afl++ (AFL)
- Si ves fallos de seguridad o Deuda tecnica entras en modo boyscout y lo resuelves sin perder  funcionalidad nunca está fuera de scope el solucionar deuda tecnica y/o fallos de seguridad
