# Especificación: `js_sandbox`

> Hito 3 — Motor JS Aislado. Estado: **VERDE**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_js_sandbox.c` (18 tests,
> incluidos escape de sandbox, timeout y límite de memoria) pasa con ASan/UBSan limpio, y
> `fuzz/fuzz_js_sandbox.c` corre sin crash/leak/UB (`make fuzz-js`). Backend: QuickJS-ng
> `v0.15.1` vendorizado en `third_party/quickjs/`.

## 1. Propósito

`js_sandbox` ejecuta JavaScript **no confiable** dentro de un contexto aislado y acotado. Es
la segunda frontera Zero Trust tras el parser: el script remoto es hostil por defecto. El motor
**no tiene I/O** (sin sistema de archivos, sin red, sin proceso/OS, sin `console` al stdout
real) y se ejecuta bajo límites estrictos de **memoria**, **pila** y **tiempo**, de forma que
un script malicioso no pueda exfiltrar datos del host, escapar del aislamiento, agotar la
memoria ni colgar el navegador.

El alcance de este hito es **el motor aislado y su resistencia al escape**. El cableado del DOM
inerte (de `html_parse`) hacia el motor — exponer APIs de navegador concretas — se define en una
spec aparte: aquí el contexto JS no ve ningún DOM.

## 2. Decisión de stack (Zero Trust hacia la dependencia)

Motor: **QuickJS-ng `v0.15.1`**, **vendorizado** en `third_party/quickjs/` (fuentes pinneadas y
auditables por nosotros, no un paquete del sistema). Justificación frente a las alternativas:

- QuickJS-ng está **mantenido activamente** (parches de seguridad), es **C puro** y soporta
  ES2023; su núcleo no realiza **ninguna** operación de I/O.
- El I/O peligroso de QuickJS vive en el módulo opcional `quickjs-libc` (`std`, `os`: archivos,
  red, proceso). **No se compila ni se inicializa.** El contexto se crea con `JS_NewContext`,
  que añade solo intrínsecos de cómputo (Object, Array, JSON, Math, RegExp, Date, …) y **nunca**
  `std`/`os`/`require`/`print`.
- Vendorizar fija la versión y la superficie exacta a auditar (la cabecera `quickjs.h` queda
  encapsulada: ningún tipo `JS*`/`JSValue` aparece en `include/js_sandbox.h`, igual que `lxb_*`
  no aparece en `html_parse.h`).

Las fuentes vendorizadas se compilan con flags relajados (sin `-Werror`), aisladas del código
propio del proyecto; el código de `src/` mantiene el build endurecido completo.

## 3. Garantías de seguridad

1. **Sin superficie de I/O.** El contexto no expone archivos, red, proceso ni OS. Identificadores
   como `require`, `std`, `os`, `process`, `print`, `XMLHttpRequest`, `fetch`, `WebSocket` **no
   están definidos**; referenciarlos produce una excepción JS limpia (`ReferenceError`), nunca un
   acceso real.
2. **Acotado en memoria.** `memory_limit_bytes` limita el heap del motor. Superarlo aborta la
   evaluación con `JS_ERR_MEMORY`, no con un OOM del host.
3. **Acotado en pila.** `max_stack_bytes` limita la profundidad de pila del motor: la recursión
   no acotada de un atacante produce un error capturable, no un desbordamiento del host.
4. **Acotado en tiempo.** `time_budget_ms` fija un presupuesto de reloj por evaluación. Un bucle
   infinito (`while(true){}`) se interrumpe y devuelve `JS_ERR_TIMEOUT`. La interrupción usa
   `CLOCK_MONOTONIC` (inmune a saltos del reloj de pared) mediante el *interrupt handler* del
   motor.
5. **Robustez ante entrada maliciosa.** Fuente malformada, truncada o binaria produce un error
   limpio (`JS_ERR_SYNTAX`/`JS_ERR_RUNTIME`), **nunca** un fallo de memoria del host. Verificado
   con fuzzing (`fuzz/fuzz_js_sandbox.c`, libFuzzer + ASan/UBSan).
6. **Aislamiento entre contextos.** Cada `js_context` es independiente: no comparte runtime,
   globals ni heap con otro. Sin estado global mutable; reentrante.
7. **Memoria.** `js_context` y los buffers de `js_result` tienen dueño único; `js_context_free`,
   `js_result_free` son idempotentes / seguros con `NULL`. Objetivo: `valgrind` y ASan/UBSan
   limpios.

## 4. Contrato de la API

Definida en `include/js_sandbox.h`.

```c
js_limits js_limits_default(void);

/* Validador puro (sin motor). */
js_status js_validate_source(const char *src, size_t len, const js_limits *lim);

/* Contexto opaco aislado. lim==NULL => defaults. */
js_status js_context_new(const js_limits *lim, js_context **out);
void      js_context_free(js_context *ctx);

/* Evalua JS no confiable en el contexto; captura resultado o excepcion en *res.
 * Nunca realiza I/O del host. */
js_status js_eval(js_context *ctx, const char *src, size_t len, js_result *res);

/* Como js_eval, pero etiqueta la fuente con `filename` para que la ubicacion de una
 * excepcion (res->file/line/col) y el .stack lleven un nombre util en vez del generico
 * "<sandbox>". filename NULL => "<sandbox>". El nombre es solo diagnostico; no concede
 * ninguna capacidad al script. */
js_status js_eval_named(js_context *ctx, const char *src, size_t len,
                        const char *filename, js_result *res);

/* Conveniencia: crea contexto, evalua, libera. */
js_status js_eval_once(const char *src, size_t len, const js_limits *lim, js_result *res);

/* Parser puro: extrae el sitio de lanzamiento (archivo, linea, columna) del PRIMER frame
 * de un string .stack de QuickJS. Formas reconocidas:
 *     at <nombre> (<archivo>:<linea>:<col>)
 *     at <archivo>:<linea>:<col>
 * Escribe hasta file_cap-1 bytes de <archivo> en file_out y los numeros en *line/*col
 * (*col=0 si el frame solo trae linea). Devuelve 1 si parseo una linea, 0 si no (file_out
 * vaciado, *line=*col=0). Tolera NULL/basura. Sin I/O ni asignacion, reentrante. */
int js_loc_from_stack(const char *stack, char *file_out, size_t file_cap,
                      int *line, int *col);

/* Ajusta el presupuesto de reloj armado en cada js_eval POSTERIOR. Permite imponer un
 * unico presupuesto por pagina a traves de una secuencia de evaluaciones (p. ej. los
 * <script> inline de una pagina corridos uno por uno): el llamador baja el presupuesto al
 * tiempo restante antes de cada llamada, de modo que aislar scripts no multiplica el tope.
 * No-op con ctx NULL; no afecta una evaluacion en curso. */
void      js_set_time_budget(js_context *ctx, uint64_t budget_ms);

void      js_result_free(js_result *res);
```

### Configuración por defecto (Secure by Default)
- `max_source_bytes  = JS_DEFAULT_MAX_SOURCE`   (4 MiB).
- `memory_limit_bytes = JS_DEFAULT_MEM_LIMIT`   (64 MiB).
- `max_stack_bytes    = JS_DEFAULT_STACK_LIMIT` (256 KiB).
- `time_budget_ms     = JS_DEFAULT_TIME_BUDGET` (1000 ms).

Un `js_limits` con un campo a `0` recibe el default de ese campo (el camino por defecto es el
seguro; no es representable "sin límite").

### `js_result`
- `status`: resultado (ver §5).
- `value` / `value_len`: forma textual del resultado (o el mensaje de la excepción si
  `is_exception`); buffer en propiedad del llamante, NUL-terminado, `value_len` excluye el NUL.
- `is_exception`: distinto de cero si `value` contiene un mensaje de error en vez de un valor.
- `file` / `line` / `col`: **sitio de lanzamiento** de la excepción (ayuda al desarrollador),
  parseado del `.stack` del motor. Solo significativo con `is_exception`; `file` es `NULL` y
  `line`/`col` 0 cuando no se pudo determinar (p. ej. al lanzar un primitivo sin `.stack`).
  `file` lo libera `js_result_free`. El nombre proviene del `filename` pasado a `js_eval_named`
  (`<sandbox>` por defecto). Cota del nombre: `JS_LOC_FILE_MAX`.

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `JS_OK` | Evaluación completada; `value` contiene el resultado. |
| `JS_ERR_NULL_ARG` | `src == NULL`, `ctx == NULL` u `out`/`res == NULL`. |
| `JS_ERR_EMPTY` | `len == 0`. |
| `JS_ERR_TOO_LARGE` | `len > max_source_bytes`. |
| `JS_ERR_SYNTAX` | Error de compilación/parseo (`value` lleva el mensaje, `is_exception=1`). |
| `JS_ERR_RUNTIME` | Excepción JS no capturada en ejecución (`value` lleva el mensaje). |
| `JS_ERR_TIMEOUT` | Se superó `time_budget_ms`; la evaluación fue interrumpida. |
| `JS_ERR_MEMORY` | Se superó `memory_limit_bytes` (o el motor agotó memoria). |
| `JS_ERR_OOM` | Fallo de asignación del host (creación de contexto / copia de salida). |
| `JS_ERR_INTERNAL` | Estado inesperado del motor. |

## 6. Semántica

- `js_validate_source`: `NULL`⇒`JS_ERR_NULL_ARG`; `len==0`⇒`JS_ERR_EMPTY`; `len>cap`⇒
  `JS_ERR_TOO_LARGE`; si no, `JS_OK`. `cap` = `lim->max_source_bytes` o el default si
  `lim==NULL`/0.
- `js_context_new`: crea runtime + contexto endurecidos (límites de memoria/pila aplicados,
  interrupt handler instalado). `out==NULL`⇒`JS_ERR_NULL_ARG`. Fallo de asignación⇒`JS_ERR_OOM`.
- `js_eval`: valida la fuente; **compila** primero (separar sintaxis de ejecución) y luego
  ejecuta el bytecode con el presupuesto de tiempo armado. Mapea el desenlace a §5. Reevaluar
  sobre el mismo contexto comparte globals (útil); para aislamiento total, usar un contexto nuevo.
- Distinción sintaxis vs ejecución: la compilación fallida ⇒ `JS_ERR_SYNTAX`; la ejecución
  fallida ⇒ `JS_ERR_TIMEOUT` (si hubo interrupción), `JS_ERR_MEMORY` (si se agotó el límite de
  memoria) o `JS_ERR_RUNTIME` (cualquier otra excepción).
- `js_eval_once`: equivalente a `new` + `eval` + `free`; los mismos códigos de error.

## 7. Matriz de pruebas

`tests/test_js_sandbox.c` (cmocka):
- `js_limits_default` segura (todos los campos > 0).
- Validador: `NULL`, vacío, sobre-tamaño, OK.
- `js_context_new`/`free`: OK, `NULL`-safe, doble `free`.
- Aritmética: `"1+2"` ⇒ `JS_OK`, `value=="3"`.
- Cadena: `"'a'+'b'"` ⇒ `value=="ab"`.
- Sintaxis: `"]["` ⇒ `JS_ERR_SYNTAX`.
- Runtime: `"throw new Error('boom')"` ⇒ `JS_ERR_RUNTIME`, `is_exception`, mensaje contiene
  `boom`.
- **Escape de sandbox:** `"typeof std+typeof os+typeof require+typeof process+typeof fetch"`
  ⇒ `"undefinedundefinedundefinedundefinedundefined"`; `"readFile('/etc/passwd')"` ⇒
  `JS_ERR_RUNTIME` (no existe `readFile`).
- **Timeout:** con `time_budget_ms` pequeño, `"while(true){}"` ⇒ `JS_ERR_TIMEOUT`.
- **Memoria:** con `memory_limit_bytes` pequeño, `"var s='x';while(true){s+=s;}"` ⇒
  `JS_ERR_MEMORY`.
- `js_eval_once` de un programa simple ⇒ `JS_OK`.
- `js_result_free`/`js_context_free` con `NULL` y dobles llamadas.
- **Ubicación de excepción:** `js_loc_from_stack` parsea frame con nombre, frame desnudo,
  archivo con `:` (URL), solo-línea (col 0), truncado a cap, basura/`NULL` ⇒ 0. `js_eval_named`
  con un error en la 2ª línea ⇒ `res->file` == el filename dado, `res->line==2`, `res->col>0`;
  filename `NULL` ⇒ `"<sandbox>"`; lanzar un primitivo (`throw 'x'`) ⇒ sin ubicación (no crashea).

`fuzz/fuzz_js_sandbox.c` (libFuzzer): bytes arbitrarios → `js_eval_once` con límites estrictos
**y** `js_loc_from_stack` sobre los mismos bytes (parser puro, sin motor); el objetivo es que
**nunca** se produzca crash/leak/UB (el `.stack` lleva nombres de función/archivo controlados por
el script hostil, así que el parser ve entrada no confiable).

## 8. Fuera de alcance

- Cableado del DOM inerte (`html_parse`) hacia el motor y exposición de APIs de navegador
  validadas (spec aparte; aquí el contexto no ve DOM).
- Bucle de eventos / `Promise` asíncronos / temporizadores (`setTimeout`): el drenaje de
  microtareas y los jobs pendientes se definen en su propia spec.
- Carga de módulos / `import` (deshabilitada: sin FS, sin resolución de módulos).
- Mitigación de fingerprinting por temporización (`Date`, `performance.now`): pertenece al
  Hito 5 (doctrina anti-vigilancia). Aquí `Date` existe como intrínseco de cómputo pero no
  expone identidad del host.
