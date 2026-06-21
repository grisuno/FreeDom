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
  tab_open() -> pipe x2; fork() -------->  close extremos del padre
                                           session_key = getrandom()      <- antes del confinamiento
                                           os_landlock_restrict(NULL,0)    <- niega TODO el filesystem
                                           os_harden(KILL)                 <- seccomp fail-closed activo
  read(handshake) <----------pipe-------- write(TAB_READY | TAB_NO_CONFINE)
  ----- bucle de peticiones -----         ----- bucle confinado -----
  tab_load(html) -> [OP_LOAD][len][html]-> hp_parse + dom_build + js_context_new
                                           + jd_install + je_install + je_install_canvas
  read(resp) <---------------pipe-------- [ok][title][text]
  tab_eval(js) -> [OP_EVAL][len][js] ----> js_eval(ctx, ...)   <- JS hostil, in-process
  read(resp) <---------------pipe-------- [ok][is_exception][value]
  tab_close() -> close(req); SIGKILL; waitpid()   EOF en req -> libera estado -> _exit(0)
```

- El hijo **se confina una sola vez** al arrancar, antes de la primera petición y antes de mapear
  cualquier contenido. Todo lo subsiguiente (parseo, DOM, creación de contexto JS, `eval`) ocurre
  ya confinado. Si el parseo o el motor JS intentaran abrir un fichero/socket o `exec`, el kernel
  mata al hijo (`SIGSYS`) y el padre lo reporta como `TAB_ERR_DEAD`.
- **Orden de confinamiento:** `os_landlock_restrict(NULL, 0)` (Landlock niega todo el FS) va
  **antes** de `os_harden` (seccomp bloquea los propios syscalls de Landlock). Landlock es
  *best-effort* (defensa en profundidad): seccomp ya excluye `open`/`openat`/`socket`/`connect`,
  así que un kernel sin Landlock no debilita la garantía. **seccomp es obligatorio**: si
  `os_harden` falla (o la plataforma no lo soporta), el hijo reporta no-confinado y `tab_open`
  devuelve `TAB_ERR_CONFINE` (*fail closed*: nunca se ejecuta contenido sin sandbox).
- **session_key** se genera una vez por worker con `getrandom` (en la allowlist de seccomp). Cada
  pestaña es una sesión: el envenenamiento de `canvas`/`audio` es determinista dentro de la pestaña
  y **no enlazable** entre pestañas.
- **Pantalla:** `tab.h` no recibe dimensiones; el worker usa un valor por defecto fijo
  (`TAB_SCREEN_W` × `TAB_SCREEN_H`) que `fp_bucket_screen` normaliza igual para todos.

### Protocolo padre↔hijo (framed)

Padre y hijo son el mismo binario y arquitectura (`fork`), así que se intercambian estructuras
crudas de ancho nativo (`uint8_t` op, `size_t` longitudes, `int32_t` estados), como el `renderer`.

- **Petición:** `[op: uint8]`. `OP_LOAD` lleva **dos bytes de bandera** antes de la carga:
  `[op][run_js:1][reader:1][len: size_t][html]` (las banderas preceden a la carga para que el HTML
  quede zero-copy). `run_js` es la política de JS; `reader` es el modo sin distracciones (Hito 23),
  reenviado a `pv_build_full`. `OP_EVAL`/`OP_DECODE_IMAGE` llevan `[op][len][payload]`. EOF en la
  tubería de peticiones equivale a `OP_QUIT`.
- **Respuesta de `OP_LOAD`:** `[ok: int32][title_len: size_t][title][text_len: size_t][text]`.
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
typedef struct tab_page { char *title; size_t title_len; char *text; size_t text_len; } tab_page;
typedef struct tab_eval_result { char *value; size_t value_len; int is_exception; } tab_eval_result;

#define TAB_MAX_INPUT ((size_t)(32u * 1024u * 1024u))

tab_status tab_open(tab **out);
tab_status tab_load(tab *t, const char *html, size_t len, tab_page *out);
/* Hito 20b: run_js es la política de JS de la página (rdp_caps.js). Controla el
 * render de <noscript> y, cuando es 1, EJECUTA los <script> inline en el worker antes
 * de derivar la vista (las mutaciones de document.title/textContent se reflejan).
 * tab_load == tab_load_ex con run_js == 0. Framing OP_LOAD: [op][run_js:1][reader:1][len][html]. */
tab_status tab_load_ex(tab *t, const char *html, size_t len, int run_js, tab_page *out);
/* Hito 23: reader = modo sin distracciones (reenviado a pv_build_full: descarta
 * nav/header/footer/aside). tab_load_ex == tab_load_full con reader == 0. */
tab_status tab_load_full(tab *t, const char *html, size_t len, int run_js, int reader,
                         tab_page *out);
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
5. **Anti-fingerprinting:** identidad normalizada y relojes engrosados (`js_env`); `session_key`
   aleatoria por pestaña hace el *readback* de canvas/audio no enlazable entre pestañas.
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
