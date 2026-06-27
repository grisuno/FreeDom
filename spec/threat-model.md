# Modelo de amenazas — Freedom

> Hito 5 — Auditoría y doctrina anti-vigilancia. Documento vivo: se actualiza con cada módulo.
> Es el mapa entre *qué tememos* y *qué lo mitiga* en el código real.

## 1. Activos a proteger

1. **Confidencialidad del usuario:** qué navega, su IP, su identidad, su huella (fingerprint).
2. **Integridad del cliente:** que contenido remoto hostil no logre ejecución fuera del sandbox,
   exfiltración ni persistencia.
3. **Disponibilidad:** que una página no pueda colgar ni agotar la memoria del navegador.
4. **Estado local:** caché, marcadores, credenciales (cifrados en reposo — `local_store` + `disk_store`).

## 2. Adversarios considerados

- **A1 — Sitio/contenido remoto hostil:** HTML/CSS/JS malicioso (la entrada por defecto).
- **A2 — Red activa (MITM):** intercepta/modifica tráfico; cosecha hoy para descifrar mañana
  (*Harvest-Now, Decrypt-Later*).
- **A3 — Ecosistema de vigilancia corporativa:** rastreadores de terceros, fingerprinting,
  telemetría (el adversario que motiva el proyecto).
- **A4 — Atacante local entre ventanas:** otra app intentando keylogging/captura (vector clásico
  de X11).
- **Fuera de alcance:** atacante con root en la máquina del usuario; cadena de suministro del
  compilador/kernel; ataques físicos.

## 3. Fronteras de confianza y mitigaciones (mapa a módulos)

| Frontera | Amenaza | Mitigación | Módulo |
| :-- | :-- | :-- | :-- |
| Red ↔ navegador | A2 (MITM, HNDL) | TLS 1.3 mínimo; **KE híbrido PQ** obligatorio (`X25519MLKEM768`); rechazo de RSA<3072/SHA-1; fail-closed | `secure_fetch` |
| Red ↔ navegador | A3 (terceros) | **Bloqueo de terceros por defecto** (no representable permitirlos); eTLD+1 vía PSL completa (ICANN+PRIVATE) | `request_policy`, `psl_data` |
| JS ↔ otro origen | A1/A3 (exfiltración cross-origin / CORS) | **No hay lectura cross-origin para JS por construcción:** sin `fetch`/`XMLHttpRequest`/`WebSocket`/`sendBeacon`/`Image`, sin `iframe`/contexto anidado, sin `window.open`/`postMessage`/`opener`; readback de canvas/audio **envenenado** (nunca píxeles reales); el worker no tiene red (`CLONE_NEWNET`+seccomp). `document.cookie` presente pero **vacío** (Zero Knowledge). Por eso la SOP **clásica** (leer la respuesta de otro origen) es **estructuralmente imposible** y CORS (cabeceras ACAO) es **irrelevante** (no hay petición cross-origin de JS que negociar). Los subrecursos de imagen (opt-in) sí pueden ser cross-origin ("cargar todo menos trackers", `rp_evaluate`→píxel 1×1 bloqueado): es un faro de salida deliberado, no una fuga de confidencialidad (no hay dato sensible accesible). Test de regresión: `typeof fetch === 'undefined'` (etc.) — si alguien añade una API de red, falla y obliga a añadir CORS con ella. | `js_env`, `js_dom`, `request_policy`, `render_policy`, `tab` |
| Lectura JS ↔ identidad | A3 (fingerprint) | Identidad normalizada (UA/locale/TZ/cores/mem), coarsening de relojes, bucketing de pantalla, perturbación de canvas/audio por sesión | `anti_fp` |
| Bindings JS ↔ identidad | A3 (fingerprint) | Cableado de `anti_fp` a `navigator`/`screen`/`performance` (sellados, infalsificables) + `Date.now` engrosado + `canvas`/`audio` con readback envenenado por sesión | `js_env` |
| Pestaña ↔ pestaña / UI | A1 (post-explotación / fuga cross-pestaña) | Worker por pestaña **fork + exec** (re-ejecuta `/proc/self/exe`): **sin herencia COW** del padre → un worker comprometido no ve el contenido de las otras pestañas (`tab_slots[]`), ASLR fresca, higiene de fds (`close_range`, solo los 2 pipes sobreviven); parseo + DOM + JS hostil en hijo confinado; IPC framed; el padre nunca toca los bytes y sobrevive a un hijo caído (`TAB_ERR_DEAD`), ignora `SIGPIPE`, valida longitudes | `tab` |
| Contenido → DOM | A1 (scripts/handlers) | Árbol **inerte**: strip de `<script>` y `on*`; recorrido iterativo (anti stack-overflow); fuzzing | `html_parse`, `dom` |
| DOM → motor JS | A1 (escape de sandbox) | Motor **sin I/O** (sin `std`/`os`/`require`); límites de memoria/pila/tiempo; superficie nativa mínima y **handles validados** (sin objetos vivos) | `js_sandbox`, `js_dom` |
| Proceso ↔ kernel | A1 (post-explotación) | **seccomp-bpf** fail-closed: lista blanca de syscalls; sin `open`/`socket`/`execve`/`ptrace`. **`io_uring` prohibido** (`io_uring_setup`/`enter`/`register` fuera del allowlist → `SIGSYS`): es una **primitiva de bypass de seccomp** (sus `IORING_OP_*` no atraviesan el syscall entry que el BPF filtra), por eso —como Docker/ChromeOS/Android— jamás entra, ni "para E/S asíncrona"; la doctrina io_uring (§3) es **solo del lado confiable**. **W^X** (inspección de argumento: `mmap`/`mprotect` con `PROT_EXEC` denegados → sin shellcode nativo aun tras secuestro de control) + **anti-volcado** (`PR_SET_DUMPABLE`=0 + `RLIMIT_CORE`=0 → sin core ni ptrace ajeno que exfiltre secretos). x86_64 y **aarch64 LE** (BE excluido, fail-closed). Test de regresión: `io_uring_setup` ⇒ `SIGSYS` y `os_policy_allows(__NR_io_uring_*)`=0 — candadea la invariante deny-by-default | `os_sandbox` |
| Proceso ↔ filesystem | A1 (post-explotación) | **Landlock** (niega todo el FS) como defensa en profundidad, antes de seccomp; *best-effort* (seccomp ya excluye `open`) | `os_sandbox`, `tab` |
| Estado local ↔ disco | A3 / robo del dispositivo | Cifrado en reposo **AES-256-GCM/ChaCha20-Poly1305 + Argon2id**, fail-closed; escritura atómica con permisos 0600 | `local_store`, `disk_store` |
| Navegador ↔ escritorio | A4 (keylogging) | **Solo Wayland, nunca X11** (aislamiento de clientes por el compositor) | `ui` |
| Disponibilidad | A1 (DoS) | Cuerpo HTTP acotado; entrada HTML acotada; presupuesto de tiempo/memoria en JS | `secure_fetch`, `html_parse`, `js_sandbox` |

## 4. Doctrina aplicada

- **Zero Trust:** cada componente desconfía del anterior; el contenido remoto es hostil por
  defecto.
- **Zero Knowledge:** el navegador no registra al usuario más de lo imprescindible; sin
  telemetría (ni "anónima").
- **Secure/Privacy/PQ by Default:** las configuraciones inseguras **no son representables** en la
  API; el camino por defecto es el seguro; PQ híbrido siempre.
- **Fail-closed:** ante cualquier garantía no verificable, se rechaza la operación.

## 5. Riesgo residual / trabajo pendiente

**Cerrado desde la última revisión:**

- **Fingerprinting (cableado):** las primitivas de `anti_fp` están cableadas a las bindings JS en
  `js_env` (`navigator`/`screen`/`performance` sellados, `Date.now` engrosado, readback de
  `canvas`/`audio` envenenado por sesión).
- **Aislamiento de pestañas / multiproceso:** `tab` es el proceso hijo de larga vida por pestaña;
  ejecuta `js_sandbox` (+ `js_dom`/`js_env`) dentro del hijo confinado con IPC bidireccional framed.
  El `renderer` one-shot queda como base histórica.
- **PSL completa:** `request_policy` usa la Public Suffix List completa de Mozilla
  (ICANN + PRIVATE, ~10 200 reglas) generada en build (`tools/gen_psl` → `psl_data`).
- **Estado local cifrado:** `local_store` (AEAD + Argon2id, fail-closed) + `disk_store`
  (persistencia atómica 0600).
- **`landlock`:** confina el filesystem del worker de pestaña (niega todo el FS) además de seccomp.
- **Same-Origin / CORS (auditoría de gaps #2):** la SOP clásica (leer la respuesta de otro origen
  desde JS) es **estructuralmente imposible** — el sandbox JS no expone ninguna API de red ni de
  contexto cruzado, no hay `iframe`, el readback de canvas está envenenado, el worker no tiene red y
  `document.cookie` está vacío. CORS (cabeceras) es irrelevante porque no hay petición cross-origin de
  JS que negociar. Regresión bloqueada por `test_eval_no_network_or_cross_origin_api` (si se añade una
  API de red, falla y obliga a añadir CORS). Ver fila "JS ↔ otro origen" en §3.
- **Aislamiento real de proceso por pestaña (auditoría de gaps #4):** el worker pasa de `fork`-solo a
  **fork + exec** → sin herencia COW de la memoria del padre (ni el contenido de las otras pestañas),
  ASLR fresca, higiene de fds. Cierra el lavado cross-pestaña.
- **W^X + anti-volcado (auditoría de gaps #5):** seccomp inspecciona argumentos (deniega `PROT_EXEC`)
  y el worker es undumpable; secretos del worker no exfiltrables por core/ptrace.
- **seccomp aarch64 (auditoría de gaps #3):** el filtro ya no es x86_64-only (aarch64 LE soportado en
  fuente; pendiente de itest en hardware ARM64).

**Pendiente:**

- **WebGL / fuentes:** la superficie aún no existe en el env JS (no hay `getContext` ni contextos
  vivos: WebGL está ausente por construcción). Cuando se exponga, refusar WebGL (return `null`) y
  aplicar las mismas primitivas de `anti_fp`; añadir prueba explícita de ausencia.
- **WebRTC / fugas de IP:** deshabilitado por ausencia; cuando haya red de subrecursos, reforzar.
- **Orquestación multi-pestaña:** scheduler de varios `tab`, eventos/timers asíncronos en el worker,
  y paso de `session_key`/dimensiones de pantalla por origen (eTLD+1) desde el orquestador de UI.
- **`pledge`/`unveil`:** equivalentes de confinamiento en OpenBSD (hoy Linux: seccomp + Landlock).

## 6. Cómo se verifica

Cada mitigación tiene pruebas: `make test` (167 pruebas unitarias en 14 suites), `make asan`
(ASan+UBSan limpio), fuzzing (`make fuzz`, `make fuzz-js`), e integración de red (`make itest`,
negocia `X25519MLKEM768` real). El aislamiento de `tab` ejercita QuickJS + Lexbor **bajo seccomp**
en el hijo confinado. Ninguna garantía se declara "verificada" sin una prueba que la ejercite.
