# Especificación: `tab`

> Hito 5 — Aislamiento de pestañas: hijo de larga vida por pestaña + JS en el hijo.
> Estado: **SPEC + TEST (rojo)**. Metodología: SDD + TDD. Esta spec es el contrato;
> `tests/test_tab.c` debe fallar (no enlaza) hasta que exista `src/tab.c`.

## 1. Propósito

`tab` es la evolución del `renderer` *one-shot* a un **worker de pestaña de larga vida**: cada
pestaña es su propio proceso hijo, bifurcado una vez y confinado (Landlock sin filesystem +
seccomp-bpf) **antes** de tocar cualquier contenido remoto. Dentro del confinamiento, el hijo:

1. parsea HTML hostil (`html_parse`),
2. construye el DOM inerte e indexado (`dom`),
3. crea un contexto JS aislado (`js_sandbox`) y le cabletea las *bindings* validadas:
   `dom` de solo lectura (`js_dom`), identidad normalizada `navigator`/`screen`/`performance`
   con relojes engrosados (`js_env`) y `canvas`/`audio` con *readback* envenenado por sesión
   (`js_env`),
4. ejecuta JavaScript no confiable **in-process** contra ese DOM.

El **proceso padre nunca parsea ni ejecuta los bytes hostiles**. Conduce al hijo por un protocolo
privado de tuberías (petición/respuesta) y **sobrevive** a un cuelgue o explotación del hijo,
reportando `TAB_ERR_DEAD` en vez de morir. Un compromiso en una pestaña queda contenido en su
proceso y no alcanza al padre (UI/confianza) ni a otras pestañas.

A diferencia del `renderer` (un `fork` por render, devuelve solo título+texto inerte y muere),
`tab` mantiene el proceso vivo y su estado (DOM + contexto JS) entre peticiones, permitiendo
`tab_eval` repetidos contra la página cargada. Cierra los pendientes del puente Hito 2→3 y del
renderer: *IPC bidireccional persistente*, *ejecución de JS en el hijo* y *landlock*.

## 2. Arquitectura

```
proceso padre (UI/confianza)             proceso hijo (worker de pestaña, confinado)
  tab_open() -> pipe x2; fork() -------->  fd hygiene: CLOEXEC a TODO fd>=3, salvo los 2 pipes
                                           execv(/proc/self/exe, --tab-worker rfd wfd)  <- IMAGEN NUEVA
                                           ----- nuevo proceso, sin herencia COW -----
                                           tab_worker_dispatch() -> tab_worker_run(rfd,wfd)
                                           session_key = getrandom()      <- antes del confinamiento
                                           os_isolate_namespaces()         <- user/net/ipc/uts
                                           os_no_dump()                    <- undumpable + RLIMIT_CORE=0
                                           os_landlock_restrict(NULL,0)    <- niega TODO el filesystem
                                           os_harden(KILL)                 <- seccomp fail-closed + W^X
  read(handshake) <----------pipe-------- write(TAB_READY | TAB_NO_CONFINE)
  ----- bucle de peticiones -----         ----- bucle confinado -----
  tab_load(html) -> [OP_LOAD][len][html]-> hp_parse + dom_build + js_context_new
                                           + jd_install + je_install + je_install_canvas
  read(resp) <---------------pipe-------- [ok][title][text]
  tab_eval(js) -> [OP_EVAL][len][js] ----> js_eval(ctx, ...)   <- JS hostil, in-process
  read(resp) <---------------pipe-------- [ok][is_exception][value]
  tab_click(node_id) -> [OP_CLICK][nid] -> jd_fire_click(ctx, nid) + re-derivar vista
  read(resp) <---------------pipe-------- [ok][title][text][view]
  tab_close() -> close(req); SIGKILL; waitpid()   EOF en req -> libera estado -> _exit(0)
```

- **fork + exec (aislamiento de proceso real, no solo `fork`):** el hijo **re-ejecuta** el propio
  binario (`execv("/proc/self/exe", {"freedom","--tab-worker",rfd,wfd})`) en vez de seguir corriendo
  con la imagen heredada del padre. Así el worker **no hereda copy-on-write** del espacio de
  direcciones del padre (el contenido HTML/URL/estado de las **otras pestañas** vive en `tab_slots[]`
  del padre) y re-aleatoriza ASLR. seccomp/W^X/Landlock confinan lo que el worker *puede hacer*; el
  exec confina lo que el worker *puede ver*: cierra el filtrado cross-pestaña por inheritance de
  memoria (un worker comprometido renderizando la pestaña activa ya no puede leer las otras y
  lavarlas por la red del padre vía `src` de imagen o `location.href`). **Higiene de fds:** antes del
  exec, el hijo marca `CLOEXEC` en **todo** fd ≥ 3 (`close_range(3, ~0, CLOSE_RANGE_CLOEXEC)`) y lo
  limpia solo en los dos extremos de pipe que cruzan el exec, de modo que el worker tampoco hereda el
  socket de Wayland ni ningún otro fd del padre. `tab_worker_dispatch(argc,argv)` (llamado al inicio
  de `main` del binario **y** del `test_tab`, ya que el worker re-ejecuta `/proc/self/exe`) detecta la
  invocación `--tab-worker`, valida los fds con `tab_parse_worker_args` (puro, fail-closed) y corre el
  worker; si el exec falla, el hijo `_exit(127)` sin handshake y el padre devuelve `TAB_ERR_CONFINE`
  (*fail closed*).
- El hijo **se confina una sola vez** al arrancar (ya en la imagen nueva), antes de la primera
  petición y antes de mapear cualquier contenido. Todo lo subsiguiente (parseo, DOM, creación de
  contexto JS, `eval`) ocurre ya confinado. Si el parseo o el motor JS intentaran abrir un
  fichero/socket o `exec`, el kernel mata al hijo (`SIGSYS`) y el padre lo reporta como
  `TAB_ERR_DEAD`.
- **Orden de confinamiento:** `os_landlock_restrict(NULL, 0)` (Landlock niega todo el FS) va
  **antes** de `os_harden` (seccomp bloquea los propios syscalls de Landlock). Landlock es
  *best-effort* (defensa en profundidad): seccomp ya excluye `open`/`openat`/`socket`/`connect`,
  así que un kernel sin Landlock no debilita la garantía. **seccomp es obligatorio**: si
  `os_harden` falla (o la plataforma no lo soporta), el hijo reporta no-confinado y `tab_open`
  devuelve `TAB_ERR_CONFINE` (*fail closed*: nunca se ejecuta contenido sin sandbox).
- **session_key** se genera una vez por worker con `getrandom` (en la allowlist de seccomp); es el
  secreto de sesión por pestaña. En cada `OP_LOAD` el worker deriva la **clave de readback por
  origen** con `fp_origin_key(session_key, eTLD+1)`: el dominio registrable sale de `request_policy`
  (`rp_host_of`→`rp_site_of`, tabla PSL) sobre la URL de la página (una URL sin host —`file://`/
  vacía— da `NULL`, namespace propio). Así el envenenamiento de `canvas`/`audio` es **determinista
  por origen** y **no enlazable** ni entre pestañas (otro `session_key`) ni entre sitios de una misma
  pestaña (otro eTLD+1) — se cierra el cross-origin linking de la huella de readback.
- **Pantalla:** `tab.h` no recibe dimensiones; el worker usa un valor por defecto fijo
  (`TAB_SCREEN_W` × `TAB_SCREEN_H`) que `fp_bucket_screen` normaliza igual para todos.
- **Zona horaria normalizada a UTC (anti-fp + corrección de sandbox):** antes de confinarse,
  el worker fija `TZ=UTC0` y llama `tzset()`. Dos razones independientes: (a) **Zero
  Knowledge** — la zona horaria del host es un vector de fingerprinting y el `Date` de
  QuickJS la lee vía `localtime_r`; todo JS de página ve el mismo reloj UTC
  (`getTimezoneOffset() == 0`); (b) **corrección** — con `TZ` sin fijar, el primer
  `localtime_r` de glibc hace `openat("/etc/localtime")` perezoso, y `openat` (con razón) no
  está en el allowlist de seccomp: el JS real de google.com llamando
  `Date.getTimezoneOffset()` mataba el worker por SIGSYS. `"UTC0"` es una spec POSIX pura
  que glibc parsea sin tocar el filesystem; el `tzset()` temprano la cachea con los
  syscalls aún sin restringir. Candado: `test_js_date_timezone_is_utc_and_survives`.
- **Diagnóstico de muerte del worker:** con `FREEDOM_DEBUG_WORKER=1` el padre reporta a
  stderr cómo terminó el worker (`killed by signal N` / `exited N`) al detectar la muerte —
  afordancia agente-amigable (Principio 6) para distinguir SIGSYS de un exit limpio sin
  core (el worker es anti-dump). No cambia ningún comportamiento sin la variable.

### Protocolo padre↔hijo (framed)

Padre y hijo son el mismo binario y arquitectura (`fork`), así que se intercambian estructuras
crudas de ancho nativo (`uint8_t` op, `size_t` longitudes, `int32_t` estados), como el `renderer`.

**Marshalling de la vista por bloques bulk (Hito M0.2):** los campos escalares de cada run se
serializan como **bloques de `int32` de ancho fijo** (`head[6]`, block A[36], el array de grid,
block B[26]) que listan cada campo **una sola vez** en el mismo orden en `write_view` y `read_view`,
en vez de un `write_full` por campo — igual que el array `f[]` de la box-def. Añadir un campo nuevo
es una entrada en el write-block y una en la extracción del read (antes eran ~4 sitios en lock-step),
lo que hace un desync estructuralmente difícil (los índices del array fijan el orden). **No hay
tags ni versionado**: el worker es el mismo binario que el padre (`/proc/self/exe --tab-worker`), así
que `write_view` y `read_view` son siempre la misma build — no existe version skew que tolerar, y un
codec TLV sería complejidad muerta. Las guardas anti-amplificación (`TAB_MAX_INPUT` por campo,
`TAB_MAX_RUNS` por conteo) son las mismas; el formato de wire es byte-idéntico al codec posicional
previo. Las secciones "Wire de la vista" de §4 describen el orden de campos, que este refactor no
altera.

- **Petición:** `[op: uint8]`. `OP_LOAD` lleva **cinco bytes de bandera** y la **URL de la página**
  antes de la carga: `[op][run_js:1][net:1][reader:1][dark:1][css:1][url_len: size_t][url][len: size_t][html]`
  (las banderas y la URL preceden a la carga para que el HTML quede zero-copy). `run_js` es la política
  de JS; `net` (Hito 26) concede red a `XMLHttpRequest`/`fetch` — solo `1` si el host está en
  **allow.conf Y js.conf** (el padre lo decide vía `tab_set_net_allowed`); `reader` es el modo sin
  distracciones; `dark` es la preferencia de esquema de color; `css` (Hito 27) autoriza el fetch de
  **hojas de estilo externas** (`<link rel=stylesheet>`) por la misma trama de subrecurso — el padre
  lo decide vía `tab_set_css_allowed` (en la GUI: el toggle "Author styles (CSS)"). `url` es la URL
  de la página (para el `location` real del JS — `url_len == 0` = sin URL).   `OP_EVAL`/`OP_DECODE_IMAGE` llevan
  `[op][len][payload]`. `OP_CLICK` es un comando corto:
  `[op][node_id: int32]` (sin payload de longitud). EOF en la tubería de peticiones equivale a `OP_QUIT`.
- **Respuesta de `OP_LOAD` (Hito 26: con tramas de subrecurso):** mientras corre los scripts de la
  página el hijo puede emitir **0+ tramas `TAG_SUBREQ`** (un XHR/fetch), cada una
  `[TAG_SUBREQ:uint8][method_len][method][url_len][url][body_len][body]`; el padre la **sirve bajo
  política** (`tab_set_fetcher` → resuelve la URL cruda, hostblock/rastreadores, `net_realm`
  fail-closed, TLS-PQ) y responde por la tubería de peticiones `[status:int32][body_len][body][ctype_len][ctype]`
  (refuso = `status 0`, cuerpo vacío). El worker confinado **no tiene socket**: el padre es el único
  que toca la red, re-aplicando TODA la política (un worker comprometido no alcanza un host bloqueado).
  Caps anti-DoS: `TAB_MAX_SUBREQ` (128) y `TAB_MAX_SUBRESOURCE` (16 MiB — igual al tope de cuerpo de `secure_fetch`, `SF_DEFAULT_MAX_BODY`; los bundles JS de la web moderna superan los 8 MiB: el principal de youtube.com mide 10,6 MB). Tras los subrecursos llega
  `[TAG_RESULT:uint8]` y luego el resultado de página:
  `[ok: int32][title_len][title][text_len][text][view][navreq_len][navreq][nav_replace: int32]`.
  `OP_CLICK` responde con el mismo formato, pero `navreq_len == 0` y `nav_replace == 0` (la
  navegación por defecto de un enlace la decide el padre tras recibir la vista actualizada).
  `navreq` (Hito 20e) es la string **cruda** que el JS pidió navegar; el padre la **gatea** con
  `ln_resolve(url_real, navreq)` y solo expone el destino resuelto en `tab_page.nav_url` si la política
  lo permite (Zero Trust). Las tramas de subrecurso solo aparecen en `OP_LOAD` (XHR vive solo en la
  ventana de scripts de la carga); `OP_EVAL`/`OP_DECODE_IMAGE` no llevan tags.
- **Scripts externos `<script src>` (Hito 24 EXT):** con `run_js && net` el worker ejecuta también
  los scripts **externos** de la página, **en orden de documento** intercalados con los inline
  (`hp_extract_script_list` ahora los lista con su `src` crudo). El worker **no tiene red**: pide los
  bytes por la **misma trama `TAG_SUBREQ`** (`GET`, url = el `src` crudo y hostil) y el padre
  confiable la sirve **re-aplicando TODA la política** (resolución `ln_resolve` contra la URL real de
  la página — un worker comprometido no cuela `file://`/downgrade —, hostblock/rastreadores,
  `net_realm` fail-closed, TLS-PQ con fallbacks de navegabilidad). Gates del worker antes de evaluar
  (todos fail-closed, el script simplemente **no corre** y la carga continúa):
  (a) `net == 1` (host en **allow.conf Y js.conf** vía `tab_set_net_allowed`; sin red el script
  externo se **salta** con una nota `FB_WARN` en la consola Freebug);
  (b) status HTTP 2xx;
  (c) Content-Type de JS (vacío/ausente, o que contenga `javascript`/`ecmascript` — un
  `text/html`/`application/json` **no** se evalúa: anti-confusión de tipo);
  (d) presupuesto de página compartido (`js_set_time_budget`) y caps `TAB_MAX_SUBREQ` (128) /
  `TAB_MAX_SUBRESOURCE` (16 MiB), los mismos del XHR.
  El script evaluado se **nombra por su `src`** (acotado) para que Freebug reporte
  `url:line:col` en sus errores. Un fetch rechazado/fallido deja nota `FB_WARN` y sigue con el
  próximo script. Esto **revierte, solo para hosts doblemente confiables**, la doctrina
  "los `<script src>` externos nunca corren"; para cualquier otro host la doctrina sigue vigente.
- **Respuesta de `OP_EVAL`:** `[ok: int32][is_exception: int32][value_len: size_t][value]`.
- `ok == 0` señala fallo de nivel-worker (parseo/DOM/contexto fallido, o `eval` sin página
  cargada): el padre devuelve `TAB_ERR_RENDER` / `TAB_ERR_SCRIPT` sin texto fugado.
- **Anti-amplificación:** el padre **valida** toda longitud recibida contra `TAB_MAX_INPUT` antes
  de asignar; un hijo comprometido no puede inducir una asignación gigante en el padre.

## 3. Contrato de la API

Definida en `include/tab.h`.

```c
typedef enum tab_status {
    TAB_OK = 0,
    TAB_ERR_NULL_ARG,
    TAB_ERR_SPAWN,     /* pipe()/fork() falló */
    TAB_ERR_CONFINE,   /* el hijo no pudo confinarse (fail closed) */
    TAB_ERR_IO,        /* fallo de framing IPC (hijo vivo) */
    TAB_ERR_TOO_LARGE, /* petición/respuesta excede el tope de tamaño */
    TAB_ERR_DEAD,      /* el hijo no está vivo (crash, kill o cierre) */
    TAB_ERR_RENDER,    /* parseo HTML / construcción de DOM falló en el hijo */
    TAB_ERR_SCRIPT,    /* fallo interno ejecutando el script (no una excepción JS) */
    TAB_ERR_OOM
} tab_status;

typedef struct tab tab;                 /* opaco; handle del padre */
/* nav_url (Hito 20e): destino https/file ya RESUELTO Y GATEADO (ln_resolve) que el JS
 * de la pagina pidio navegar; NULL/"" = ninguno. nav_replace: location.replace (history). */
typedef struct tab_page { char *title; size_t title_len; char *text; size_t text_len;
                          pv_view *view; char *nav_url; int nav_replace; } tab_page;
typedef struct tab_eval_result { char *value; size_t value_len; int is_exception; } tab_eval_result;

#define TAB_MAX_INPUT ((size_t)(32u * 1024u * 1024u))

tab_status tab_open(tab **out);
tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out);
/* Hito 20b: run_js es la política de JS de la página (rdp_caps.js). Controla el
 * render de <noscript> y, cuando es 1, EJECUTA los <script> inline en el worker antes
 * de derivar la vista (las mutaciones de document.title/textContent se reflejan).
 * tab_load == tab_load_ex con run_js == 0. Framing OP_LOAD: [op][run_js:1][reader:1][dark:1][len][html]. */
tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out);
/* Hito 23: reader = modo sin distracciones. Hito 23b: prefers_dark = preferencia de
 * esquema de color (gate de @media(prefers-color-scheme)). Ambos a pv_build_full.
 * Hito 20e: page_url = URL de la pagina (NULL permitido), para el location real del JS y
 * como base que GATEA cualquier navegacion por JS (ln_resolve). tab_load_ex ==
 * tab_load_full con page_url == NULL, reader == 0 y prefers_dark == 0. */
tab_status tab_load_full(tab *t, const char *html, size_t len, const char *page_url,
                         int run_js, int reader, int prefers_dark, tab_page *out);
/* Stage 4 dispatcher: dispara el click handler JS del node_id y devuelve la vista
 * re-derivada (con las mutaciones causadas por el handler). */
tab_status tab_click(tab *t, dom_node_id node_id, tab_page *out);
tab_status tab_eval(tab *t, const char *js, size_t len, tab_eval_result *out);
int        tab_alive(const tab *t);
pid_t      tab_child_pid(const tab *t);
void       tab_close(tab *t);
void       tab_page_free(tab_page *p);
void       tab_eval_result_free(tab_eval_result *r);
```

## 4. Semántica

- **`tab_open`**: `out` no nulo (`TAB_ERR_NULL_ARG`); fallo de `pipe`/`fork` (`TAB_ERR_SPAWN`); el
  hijo no logra confinarse o la plataforma no soporta seccomp (`TAB_ERR_CONFINE`, *fail closed*).
  En éxito, `*out` es un worker confinado y vivo, liberable con `tab_close`. No hay página cargada
  todavía.
- **`tab_load`**: `t`/`out` no nulos; `html` no nulo si `len > 0` (`TAB_ERR_NULL_ARG`).
  `len > TAB_MAX_INPUT` ⇒ `TAB_ERR_TOO_LARGE` (comprobado en el padre, el hijo sigue vivo). Si el
  hijo ya está muerto ⇒ `TAB_ERR_DEAD`. El hijo parsea con la política por defecto de `html_parse`
  (strip de `<script>` y atributos `on*`), construye el DOM y arma un **contexto JS fresco** ligado
  a esa página (reemplaza cualquier página previa). En éxito, `*out` lleva `title`/`text` inertes y
  `TAB_OK`; `text` nunca contiene cuerpos de script. Fallo de parseo/DOM/contexto ⇒ `TAB_ERR_RENDER`
  (sin estado parcial). Fallo de IPC con el hijo aún vivo ⇒ `TAB_ERR_IO`; si el hijo murió ⇒
  `TAB_ERR_DEAD`.
- **Ejecución de scripts (run_js)**: con `run_js == 1`, el worker obtiene los `<script>` inline
  con `hp_extract_script_list` y **evalúa cada uno por separado** (`js_eval_named` por script,
  nombrado **`inline #N`** 1-based), como un navegador: una excepción no capturada en un script se
  reporta a la consola Freebug (`FB_ERROR`) **con su ubicación** (`inline #N`, línea y columna del
  sitio de lanzamiento, parseados del `.stack` por `js_loc_from_stack`) pero **no aborta** los
  siguientes (antes se concatenaban en un único `js_eval`, así que el primer fallo mataba a todos —
  por eso google.com "no cargaba nada"). El REPL (`tab_eval`) se nombra `<repl>`. Un **único
  presupuesto de reloj por página** (`JS_DEFAULT_TIME_BUDGET`, vía `js_set_time_budget`) se reparte
  entre todos los scripts y el pump sintético `__fireDeferred`, de modo que aislar los scripts **no
  multiplica** el tope de tiempo; al agotarse, los scripts restantes no se ejecutan (fail-closed).
  Luego se restaura el presupuesto completo para el REPL (`tab_eval`).
- **Wire de la vista (flex por-item, Stage 3)**: cada run serializa, tras los cinco campos de
  contenedor (`cont_id..cont_cols`), **seis** `int32` —
  `flex_grow, flex_shrink, flex_basis, flex_order, flex_direction, cont_item` — en el MISMO orden en
  `write_view` y `read_view` (desincronizar = basura). Son estructura de maquetación (como `cont_*`):
  viajan siempre, `render_doc` no los gatea por `caps.css`. `cont_item` es el ordinal del ítem
  (hijo directo del contenedor) al que pertenece el run (-1 = sin contenedor); runs consecutivos con
  el mismo `(cont_id, cont_item)` son fragmentos del mismo ítem y la GUI los fluye juntos en una celda.
- **Wire de la vista (CSS layout expansion: flex-wrap/row-gap/align-items/align-self)**: inmediatamente
  después de `cont_item` (antes de `float_side`), **cuatro** `int32` más —
  `cont_wrap, cont_row_gap, cont_align_items, flex_align_self` — mismo orden en ambos lados. Los tres
  primeros son del CONTENEDOR (`css_flex_wrap`, px o -1 sin fijar, `css_align_kw`); el cuarto es del
  ÍTEM (`css_align_kw` de `align-self`, 0/`CSS_AK_UNSET` si no se fijó, en cuyo caso la GUI usa
  `cont_align_items`). Estructura como el resto de `cont_*`/`flex_*`: viajan siempre, nunca gateados.
- **Wire de consola (Freebug)**: la sección de consola serializa por entrada
  `[level:int32][line:int32][col:int32][flen:size_t][file][elen:size_t][text]`; `flen` está acotado
  por `FB_MAX_FILE_BYTES`, `elen` por `FB_MAX_ENTRY_BYTES` y el conteo por `FB_MAX_ENTRIES`, así un
  worker hostil no puede amplificar el flujo. `file`/`line`/`col` son la ubicación del error
  (`NULL`/0 para entradas sin ubicación, p. ej. un `console.log`).
- **`tab_click`**: dispara el evento de click en `node_id` dentro del worker vivo. El worker
  ejecuta cualquier handler registrado (`addEventListener('click')` / `onclick`) y **re-deriva la
  vista** con `pv_build_full` usando los mismos parámetros de la última carga, así el padre puede
  repintar las mutaciones del handler. `t`/`out` no nulos; `node_id == DOM_NODE_NONE` falla cerrado
  en el padre (`TAB_ERR_NULL_ARG`); hijo muerto o fallo interno ⇒ `TAB_ERR_DEAD`/`TAB_ERR_RENDER`.
  La respuesta no lleva navegación (`navreq_len == 0`); el padre decide después si sigue un enlace.
- **`tab_eval`**: requiere una página cargada con éxito. `t`/`out` no nulos; `js` no nulo si
  `len > 0`; `len > TAB_MAX_INPUT` ⇒ `TAB_ERR_TOO_LARGE`; hijo muerto ⇒ `TAB_ERR_DEAD`. El JS ve el
  DOM cargado y los globales `navigator`/`screen`/`performance`/`canvas`/`audio`. Un **error a nivel
  JS** (sintaxis, excepción en tiempo de ejecución, timeout, límite de memoria) se reporta con
  `TAB_OK` y `out->is_exception != 0` llevando el mensaje. `TAB_ERR_*` se reserva para fallos de
  transporte/worker: sin página cargada o fallo interno ⇒ `TAB_ERR_SCRIPT`.
- **`tab_alive`**: distinto de cero mientras el worker se considere vivo (refresca con
  `waitpid(WNOHANG)`). `tab_child_pid`: pid del worker, o `-1`.
- **`tab_close`**: cierra la tubería de peticiones (EOF ⇒ el hijo termina), `SIGKILL` defensivo y
  `waitpid` (sin zombis). `NULL`-safe.
- **`tab_page_free` / `tab_eval_result_free`**: liberan los buffers y ponen a cero; idempotentes,
  `NULL`-safe y seguros sobre structs en cero.

## 5. Garantías de seguridad

1. **Aislamiento de proceso por pestaña:** el contenido hostil se parsea y el JS hostil se ejecuta
   en otro espacio de direcciones; el padre no los mapea ni los ejecuta.
2. **Confinamiento del hijo (Zero Trust):** Landlock (sin FS) + seccomp-bpf *fail-closed* activos
   **antes** de tocar el contenido; seccomp es obligatorio (sin él, `tab_open` rechaza). El motor JS
   y el parser corren sin acceso a ficheros, sockets, `exec` ni `ptrace`.
3. **Tolerancia a fallos:** un hijo que muere (crash, `SIGSYS`, kill) no derriba al padre; se
   reporta `TAB_ERR_DEAD`. El padre ignora `SIGPIPE` para que un `write` a un hijo muerto devuelva
   error en vez de matar al padre.
4. **Anti-amplificación:** toda longitud recibida del hijo se valida contra `TAB_MAX_INPUT` antes de
   asignar.
5. **Anti-fingerprinting:** identidad normalizada y relojes engrosados (`js_env`); la `session_key`
   aleatoria por pestaña, derivada por origen con `fp_origin_key(session_key, eTLD+1)`, hace el
   *readback* de canvas/audio no enlazable ni entre pestañas ni entre sitios de una misma pestaña.
6. **Memoria:** dueño único; `tab_page_free`/`tab_eval_result_free`/`tab_close` idempotentes.
   ASan/UBSan limpios. El hijo libera su estado y sale con `_exit` (sin reentrar al padre).

## 6. Matriz de pruebas

`tests/test_tab.c` (cmocka):
- `tab_open` ⇒ `TAB_OK`, `tab_alive` verdadero, `tab_child_pid > 0`.
- `tab_load` de un documento conocido ⇒ `TAB_OK`, `title`/`text` correctos.
- `<script>`/`onclick` eliminados ⇒ `text` no contiene el cuerpo del script.
- `tab_eval` tras `tab_load`: lee el DOM (`dom.nodeCount()`, `getElementById`).
- `tab_eval`: identidad normalizada (`navigator.language`), pantalla bucketeada, relojes en rejilla.
- `tab_eval` de una excepción JS ⇒ `TAB_OK` con `is_exception != 0` y mensaje.
- `tab_eval` repetidos contra la misma página (estado persistente del hijo).
- **Stage 4 dispatcher:** `tab_click` sobre un nodo con `onclick` muta el DOM y la nueva vista refleja
  la mutación; sin handler la vista no cambia; `DOM_NODE_NONE` ⇒ `TAB_ERR_NULL_ARG`.
- Recarga: un segundo `tab_load` reemplaza la página; el `eval` ve el nuevo DOM.
- `NULL` ⇒ `TAB_ERR_NULL_ARG`; sobre-tamaño ⇒ `TAB_ERR_TOO_LARGE`.
- Entrada binaria/malformada ⇒ retorna (`TAB_OK` o `TAB_ERR_RENDER`/`TAB_ERR_DEAD`) **sin** derribar
  el proceso de prueba (aislamiento en acción).
- Matar al hijo (`SIGKILL` sobre `tab_child_pid`) ⇒ siguiente `tab_eval` da `TAB_ERR_DEAD` y el
  padre **sobrevive**; `tab_alive` pasa a falso.
- `tab_close` con `NULL` y doble; `tab_page_free`/`tab_eval_result_free` con `NULL` y doble.

## 7. Fuera de alcance

- Multiplexado de muchas pestañas / scheduler (esta unidad es un worker; el orquestador de UI las
  agrupa).
- Eventos del DOM distintos a click, mutación observada, `setTimeout`/microtasks asíncronas: el click
  y el `eval` son síncronos y de un solo disparo por petición.
- Serialización del árbol DOM completo al padre (se devuelve título+texto inerte + display list; el
  JS consulta el DOM dentro del hijo).
- Reutilización de procesos entre orígenes (cada `tab` es un proceso; la política por-origen la
  decide el orquestador).
- Paso de `session_key`/dimensiones de pantalla desde el orquestador (v1 las fija en el worker).

## 8. Hojas de estilo externas + gate de subrecursos del padre (Hito 27)

La web moderna sirve casi todo su CSS por `<link rel=stylesheet href=...>`; hasta este hito
Freedom solo veía `<style>`/`style=` y todo sitio real quedaba con colores/tipografía por defecto.
Este hito reusa la trama `TAG_SUBREQ` existente (Hito 26) para que el worker obtenga esas hojas
**sin tocar jamás un socket**, y de paso cierra un gap Zero-Trust: el padre ahora **gatea cada
subrecurso** en su propio lado (antes servía cualquier trama si había fetcher instalado, confiando
en el flag del worker — un worker comprometido podía forjar tramas).

### 8.1 Contrato

```c
/* Autoriza (1) o revoca (0) el fetch de hojas de estilo externas para la PRÓXIMA carga.
 * Independiente de run_js/net: el CSS de autor no requiere JS. En la GUI se deriva del
 * toggle "Author styles (CSS)" (caps.css); en headless, de --author-css. */
void tab_set_css_allowed(tab *t, int allowed);

/* Puro (testeable): ¿puede el padre servir una trama de subrecurso del worker?
 *   net_allowed  => cualquier método (XHR/fetch/scripts externos, Hito 26/24 EXT).
 *   css_allowed  => SOLO "GET" exacto (hojas de estilo; un worker comprometido con
 *                   solo-css no puede exfiltrar por POST).
 *   ninguno      => 0 (la trama se consume y se responde rechazo, status 0).
 * Fail-closed: método NULL/vacío/distinto de "GET" con solo-css => 0. */
int tab_subreq_permitted(int net_allowed, int css_allowed, const char *method);
```

### 8.2 Semántica (Dado-Cuando-Entonces)

- **Dado** un `tab` con `tab_set_css_allowed(t, 1)` y un fetcher instalado, **cuando** se carga un
  HTML con `<link rel=stylesheet href=S>`, **entonces** el worker emite una trama
  `TAG_SUBREQ` `GET S` (href crudo e hostil; el padre lo resuelve/gatea bajo TODA la política),
  y si la respuesta es status 2xx con Content-Type de CSS (vacío/ausente o conteniendo `css` —
  anti-confusión de tipo: un 404 HTML nunca se parsea como hoja), el cuerpo se **acumula** como
  CSS externo y alimenta `pv_build_styled` — los selectores/colores de la hoja se aplican a la
  vista (gateados por `caps.css` en `render_doc`, como todo estilo de autor).
- **Dado** `css == 0` (default), **cuando** se carga ese mismo HTML, **entonces** no se emite
  ninguna trama por los `<link>` y la vista es byte-idéntica a la previa al hito (Privacy by
  Default: cero fetches nuevos sin opt-in).
- **Dado** un fetcher que rechaza (host bloqueado / política), **cuando** la hoja no llega,
  **entonces** la carga **continúa sin esa hoja** (fail-open del adblock de presentación, como
  `hostblock`) con nota `FB_WARN` en Freebug; nunca se cae la página por una hoja.
- **Dado** el flujo de fetch, **cuando** se ordenan las hojas, **entonces** las externas se
  concatenan **en orden de documento** y preceden a los `<style>` del documento (aproximación v1
  del orden de cascada; a igual especificidad el `<style>` de la página gana).
- **Cuando** el usuario hace click (`OP_CLICK` re-deriva la vista) o el título/vista se
  re-derivan tras los scripts, **entonces** el CSS externo **persiste** en el `child_state`
  (`extern_css`, dueño único, liberado en el reset de página): la re-derivación no re-fetchea.
- **Anti-DoS:** hasta `HP_MAX_STYLESHEETS` (64) hojas por página; cada respuesta ≤
  `TAB_MAX_SUBRESOURCE` (16 MiB, cap de wire); el acumulado de CSS externo ≤ `TAB_MAX_EXTERN_CSS`
  (1 MiB — el mismo orden que `PV_MAX_STYLE_BYTES`); una hoja que no cabe entera se **descarta
  entera** (fail-closed, nunca truncada a media regla). El contador `TAB_MAX_SUBREQ` (128) es
  compartido con XHR/scripts.
- **Gate del padre (Zero Trust, corrección de este hito):** `tab_serve_subreq` consulta
  `tab_subreq_permitted(net_efectivo, css_efectivo, method)` con los flags que el padre
  **decidió para esta carga** (no los que reporte el hijo). Una trama no permitida se consume y
  se responde `status 0` (el protocolo no se desincroniza). `OP_CLICK`/`OP_EVAL` no llevan
  ventana de red: cualquier trama ahí sigue siendo desync ⇒ `TAB_ERR_IO`.

### 8.3 Matriz de pruebas

- Hoja externa aplicada con `css=1` (estilo visible en la vista, fetcher llamado con el href crudo).
- Sin flag ⇒ cero fetches y vista sin estilo externo.
- Fetcher rechaza ⇒ carga OK sin estilo, warn en consola.
- Content-Type no-CSS (`text/html`) ⇒ hoja no parseada.
- `tab_subreq_permitted`: tabla completa (net/css/ninguno × GET/POST/NULL/vacío/"get").
- Click tras carga con CSS externo ⇒ vista re-derivada conserva el estilo.

### 8.4 Fuera de alcance (v1)

- `<link>` con `media` que no contenga `screen`/`all` (se salta, fail-closed; la evaluación
  real de media queries del atributo queda con el motor `@media`).
- `@import` dentro de hojas externas (el módulo `css` lo sigue descartando: cero fetches
  recursivos). Hojas para páginas `file://` locales (el resolver de subrecursos es https-only).
- Caché de hojas entre cargas/pestañas.
