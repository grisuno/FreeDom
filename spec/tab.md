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

### Protocolo padre↔hijo (framed)

Padre y hijo son el mismo binario y arquitectura (`fork`), así que se intercambian estructuras
crudas de ancho nativo (`uint8_t` op, `size_t` longitudes, `int32_t` estados), como el `renderer`.

- **Petición:** `[op: uint8]`. `OP_LOAD` lleva **cuatro bytes de bandera** y la **URL de la página**
  antes de la carga: `[op][run_js:1][net:1][reader:1][dark:1][url_len: size_t][url][len: size_t][html]`
  (las banderas y la URL preceden a la carga para que el HTML quede zero-copy). `run_js` es la política
  de JS; `net` (Hito 26) concede red a `XMLHttpRequest`/`fetch` — solo `1` si el host está en
  **allow.conf Y js.conf** (el padre lo decide vía `tab_set_net_allowed`); `reader` es el modo sin
  distracciones; `dark` es la preferencia de esquema de color. `url` es la URL de la página (para el
  `location` real del JS — `url_len == 0` = sin URL). `OP_EVAL`/`OP_DECODE_IMAGE` llevan
  `[op][len][payload]`. EOF en la tubería de peticiones equivale a `OP_QUIT`.
- **Respuesta de `OP_LOAD` (Hito 26: con tramas de subrecurso):** mientras corre los scripts de la
  página el hijo puede emitir **0+ tramas `TAG_SUBREQ`** (un XHR/fetch), cada una
  `[TAG_SUBREQ:uint8][method_len][method][url_len][url][body_len][body]`; el padre la **sirve bajo
  política** (`tab_set_fetcher` → resuelve la URL cruda, hostblock/rastreadores, `net_realm`
  fail-closed, TLS-PQ) y responde por la tubería de peticiones `[status:int32][body_len][body][ctype_len][ctype]`
  (refuso = `status 0`, cuerpo vacío). El worker confinado **no tiene socket**: el padre es el único
  que toca la red, re-aplicando TODA la política (un worker comprometido no alcanza un host bloqueado).
  Caps anti-DoS: `TAB_MAX_SUBREQ` (64) y `TAB_MAX_SUBRESOURCE` (8 MiB). Tras los subrecursos llega
  `[TAG_RESULT:uint8]` y luego el resultado de página:
  `[ok: int32][title_len][title][text_len][text][view][navreq_len][navreq][nav_replace: int32]`.
  `navreq` (Hito 20e) es la string **cruda** que el JS pidió navegar; el padre la **gatea** con
  `ln_resolve(url_real, navreq)` y solo expone el destino resuelto en `tab_page.nav_url` si la política
  lo permite (Zero Trust). Las tramas de subrecurso solo aparecen en `OP_LOAD` (XHR vive solo en la
  ventana de scripts de la carga); `OP_EVAL`/`OP_DECODE_IMAGE` no llevan tags.
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
- **Wire de consola (Freebug)**: la sección de consola serializa por entrada
  `[level:int32][line:int32][col:int32][flen:size_t][file][elen:size_t][text]`; `flen` está acotado
  por `FB_MAX_FILE_BYTES`, `elen` por `FB_MAX_ENTRY_BYTES` y el conteo por `FB_MAX_ENTRIES`, así un
  worker hostil no puede amplificar el flujo. `file`/`line`/`col` son la ubicación del error
  (`NULL`/0 para entradas sin ubicación, p. ej. un `console.log`).
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
- Eventos del DOM, mutación, `setTimeout`/microtasks asíncronas: el `eval` es síncrono y de un solo
  disparo por petición.
- Serialización del árbol DOM completo al padre (se devuelve título+texto inerte; el JS consulta el
  DOM dentro del hijo).
- Reutilización de procesos entre orígenes (cada `tab` es un proceso; la política por-origen la
  decide el orquestador).
- Paso de `session_key`/dimensiones de pantalla desde el orquestador (v1 las fija en el worker).
