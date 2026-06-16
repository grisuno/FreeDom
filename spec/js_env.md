# Especificación: `js_env`

> Hito 5 — Doctrina anti-vigilancia. Cableado de `anti_fp` a las bindings JS.
> Estado: **SPEC + TEST (rojo)**. Metodología: SDD + TDD. Esta spec es el contrato;
> `tests/test_js_env.c` debe fallar (no enlaza) hasta que exista `src/js_env.c`.

## 1. Propósito

`js_env` es el puente que expone al script no confiable un **entorno de navegador normalizado**
(`navigator`, `screen`, relojes), respaldado por las primitivas puras de `anti_fp`. Cierra el
pendiente del Hito 5 "cablear `anti_fp` a bindings JS".

El adversario A3 (vigilancia corporativa) lee desde JS señales de alta entropía —`navigator.*`,
`screen.*`, `Date.now()`, `performance.now()`— para identificar al usuario entre sitios. La
estrategia es la de `anti_fp`: **reducir la entropía** (valores normalizados idénticos para todos
los usuarios de Freedom) y **envenenar lo inevitable** (relojes con granularidad gruesa). Este
módulo no decide *qué* valores son seguros (eso es `anti_fp`, lógica pura y auditada); solo los
**cablea** al sandbox como un objeto sellado e infalsificable, igual que `js_dom` cablea el DOM.

Diseño Zero Trust idéntico a `js_dom`: nada de objetos vivos del motor, propiedades de solo
lectura no configurables, objetos sellados con `JS_PreventExtensions`. No usa el *context opaque*
del motor (lo reserva `js_dom`): es **sin estado**, salvo el origen temporal de `performance.now()`
que viaja en los `func_data` de la propia función nativa (per-contexto, reentrante, sin globales).

## 2. Decisión de diseño

- Los valores de identidad (`userAgent`, `language`, `platform`, `vendor`,
  `hardwareConcurrency`, `deviceMemory`) provienen **todos** de `anti_fp`: una única fuente
  auditada de constantes normalizadas. `js_env` no inventa valores de identidad.
- `screen` se obtiene aplicando `fp_bucket_screen` al tamaño real de salida (lo pasa el
  orquestador en `je_install`); el script nunca ve el tamaño real, solo el bucket.
- Los relojes se coarsenan con `fp_coarsen_time_ms` (rejilla de 100 ms). `Date.now()` se
  **reemplaza** por una versión coarsenada; `performance.now()` se crea coarsenada y relativa a un
  origen capturado en `je_install` (no filtra el *uptime* del host).
- Cada objeto (`navigator`, `screen`, `performance`) y cada propiedad es **no escribible, no
  configurable**, y el objeto se sella: el script no puede secuestrar ni inyectar nada.
- Sin I/O salvo la lectura del reloj del sistema (`clock_gettime`) que es inherente a un reloj;
  `anti_fp` permanece puro.

## 3. Superficie expuesta a JS

Objeto global `navigator` (solo lectura, sellado):

| Propiedad | Valor | Origen |
| :-- | :-- | :-- |
| `navigator.userAgent` | `"Mozilla/5.0 (X11; Linux x86_64; rv:128.0) Gecko/20100101 Firefox/128.0"` | `fp_user_agent()` |
| `navigator.language` | `"en-US"` | primer tag de `fp_accept_language()` |
| `navigator.languages` | `["en-US","en"]` (array congelado) | `fp_accept_language()` separado por `,` |
| `navigator.platform` | `"Linux x86_64"` | `fp_platform()` |
| `navigator.vendor` | `""` | `fp_vendor()` |
| `navigator.hardwareConcurrency` | `2` | `fp_hardware_concurrency()` |
| `navigator.deviceMemory` | `8` | `fp_device_memory_gb()` |
| `navigator.webdriver` | `false` | constante (el agente es indistinguible del usuario) |
| `navigator.doNotTrack` | `null` | constante (sin señal extra; igual que un Firefox sin DNT) |

Objeto global `screen` (solo lectura, sellado):

| Propiedad | Valor |
| :-- | :-- |
| `screen.width` / `screen.availWidth` | `bucket_w` (de `fp_bucket_screen`) |
| `screen.height` / `screen.availHeight` | `bucket_h` (de `fp_bucket_screen`) |
| `screen.colorDepth` / `screen.pixelDepth` | `24` (universal) |

Relojes (coarsenados a `FP_TIMER_RESOLUTION_MS` = 100 ms):

| Expresión JS | Devuelve |
| :-- | :-- |
| `Date.now()` | `fp_coarsen_time_ms(epoch_ms)` — múltiplo de 100 |
| `performance.now()` | `fp_coarsen_time_ms(monotonic_ms - origin_ms)` — múltiplo de 100, `>= 0` |

Envenenado de lectura (canvas/audio), instalado por `je_install_canvas(ctx, session_key)`:

| Expresión JS | Devuelve |
| :-- | :-- |
| `canvas.readback(u8)` | nueva `Uint8Array` = `u8` con `fp_perturb(.., session_key)` aplicado |
| `audio.readback(u8)`  | igual (misma costura sobre bytes de muestras de audio) |

`canvas`/`audio` son objetos sellados de solo lectura. El array de entrada **no se muta**: se copia,
se perturba la copia y se devuelve una `Uint8Array` nueva. El envenenado es determinista dentro de
una sesión (misma clave ⇒ misma salida) y no enlazable entre sesiones (clave distinta ⇒ salida
distinta), acotado al LSB (cambio visual/acústico nulo). La `session_key` la da el orquestador de
sesión (por eTLD+1). Pasar algo que no sea `Uint8Array` lanza `TypeError`.

Lo que **no** existe (por diseño, fuera de alcance): `navigator.plugins`, `mimeTypes`,
`connection`, `getBattery`, `mediaDevices`; el constructor `Date` completo (solo `Date.now`);
`Intl`/zona horaria (no hay `Intl` en el sandbox; la normalización a UTC es del proceso, no de la
binding); canvas/audio readback (necesita su propia API; `fp_perturb` se cableará ahí).

## 4. Contrato de la API (C)

Definida en `include/js_env.h`.

```c
typedef enum je_status {
    JE_OK = 0,
    JE_ERR_NULL_ARG,   /* ctx == NULL */
    JE_ERR_OOM,        /* fallo de asignacion construyendo los globales */
    JE_ERR_INTERNAL    /* contexto del motor inaccesible o instalacion fallida */
} je_status;

/* Instala los globales `navigator`, `screen` y `performance` (solo lectura,
 * sellados) y reemplaza `Date.now` por una version coarsenada. screen_w/screen_h
 * son el tamano real de salida; se bucketean con fp_bucket_screen. Llamar sobre
 * un contexto recien creado, antes de ejecutar script no confiable. */
je_status je_install(js_context *ctx, int screen_w, int screen_h);

/* Instala los globales sellados `canvas` y `audio`, cada uno con `readback(u8)`
 * que devuelve una Uint8Array nueva con fp_perturb aplicado bajo session_key
 * (envenenado de lectura anti-fingerprinting). No muta la entrada. */
je_status je_install_canvas(js_context *ctx, uint64_t session_key);
```

Extensión de `anti_fp` (identidad normalizada; punteros estáticos, no liberar):

```c
const char *fp_platform(void);   /* "Linux x86_64" (coherente con el user-agent) */
const char *fp_vendor(void);     /* "" (sin vendor; minima entropia) */
```

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `JE_OK` | Globales instalados. |
| `JE_ERR_NULL_ARG` | `ctx == NULL`. |
| `JE_ERR_OOM` | Fallo de asignación al construir objetos/funciones. |
| `JE_ERR_INTERNAL` | El contexto del motor no es accesible o la instalación falló. |

## 6. Garantías de seguridad

1. **Anti-entropía por defecto.** Todo valor de identidad es una constante normalizada de
   `anti_fp`, idéntica para todos los usuarios; no se filtra el dispositivo real.
2. **Pantalla bucketeada.** El script ve un bucket estándar, nunca el tamaño real;
   `availWidth/Height == width/height` (no filtra barras de tareas).
3. **Relojes gruesos.** `Date.now()` y `performance.now()` son múltiplos de 100 ms: se neutraliza
   el *timing* de alta resolución. `performance.now()` es relativo a un origen por contexto: no
   filtra el *uptime*.
4. **Infalsificable.** `navigator`/`screen`/`performance` y sus propiedades son no
   escribibles/no configurables; los objetos están sellados; `Date.now` reemplazado es no
   configurable. Un script no puede restaurar el reloj real ni secuestrar la API.
5. **Hereda el aislamiento del Hito 3.** Sigue sin I/O de host (salvo la lectura del reloj) y bajo
   los límites de memoria/pila/tiempo del `js_context`.
6. **Coexiste con `js_dom`.** No usa el *context opaque* (lo reserva `js_dom`); ambos puentes
   pueden instalarse en el mismo contexto.

## 7. Matriz de pruebas

`tests/test_js_env.c` (cmocka), sobre un contexto recién creado con `je_install(ctx, 1680, 1050)`:
- `je_install(NULL, ...)` ⇒ `JE_ERR_NULL_ARG`; instalación OK.
- Identidad: `navigator.userAgent` no vacío y contiene `"Firefox"`; `navigator.language==='en-US'`;
  `navigator.languages.length===2 && navigator.languages[0]==='en-US'`;
  `navigator.platform==='Linux x86_64'`; `navigator.vendor===''`;
  `navigator.hardwareConcurrency===2`; `navigator.deviceMemory===8`;
  `navigator.webdriver===false`; `navigator.doNotTrack===null`.
- Pantalla bucketeada: con `(1680,1050)` ⇒ `screen.width===1600 && screen.height===900`;
  `screen.availWidth===screen.width`; `screen.colorDepth===24`.
- Relojes: `Date.now()%100===0`; `Date.now()>1700000000000` (posterior a 2023);
  `performance.now()%100===0`; `performance.now()>=0`.
- Infalsificable: tras `navigator.userAgent='x'`, sigue conteniendo `"Firefox"`;
  `navigator.injected=1` no añade (objeto sellado); reasignar `Date.now` no toma efecto y sigue
  dando múltiplo de 100.
- Coexistencia: instalar `jd_install` y `je_install` en el mismo contexto; ambos funcionan
  (`dom.nodeCount()>0` y `navigator.language==='en-US'`).
- Robustez: `je_install(ctx, 0, 0)` y `(-1,-1)` no crashean; `screen.width>0` (bucket mínimo).

## 8. Fuera de alcance

- Constructor `Date` completo coarsenado (`new Date().getTime()`), `Intl`/zona horaria.
- Canvas/audio readback con `fp_perturb` (necesita la API de canvas; clave de sesión por eTLD+1).
- `navigator.plugins`/`mimeTypes`/`connection`/`mediaDevices`/`getBattery`.
- Letterboxing de la ventana real al bucket (es trabajo de la UI/orquestador, no de la binding).
