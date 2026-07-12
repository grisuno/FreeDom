# Especificacion: `anti_fp`

> Hito 5 — Doctrina anti-vigilancia (anti-fingerprinting). Estado: **VERDE + EXTENDIDO**.
> Metodologia: SDD + TDD. Esta spec es el contrato; `tests/test_anti_fp.c` cubre las primitivas.
>
> Extension Hito 30b (Blend-in): nuevos valores normalizados para completar la superficie
> `navigator` y parecerse a un Firefox real ante Google/Facebook/YouTube sin filtrar datos reales.

## 1. Proposito

`anti_fp` reune las **primitivas puras** de resistencia al *fingerprinting* (huella de
dispositivo). El adversario A3 (vigilancia corporativa) combina senales de alta entropia leidas
desde JS — user-agent, resolucion, zona horaria, nucleos, relojes de alta precision, lectura de
canvas/audio — para identificar al usuario entre sitios. La estrategia, en dos frentes:

1. **Reducir la entropia:** presentar valores **normalizados** e identicos para todos los usuarios
   de Freedom (no el valor real del dispositivo).
2. **Envenenar lo inevitable:** a senales que no se pueden uniformar (lectura de canvas/audio,
   relojes) se les aplica **ruido determinista por sesion** o **granularidad gruesa**, de modo que
   la huella sea estable dentro de una sesion pero no enlazable entre sesiones ni precisa.

Este modulo es la **logica pura** (sin I/O, sin estado global). El cableado a las APIs JS
(`navigator`, `screen`, `Date`/`performance`, `canvas`) se hace en `js_env`.

**Extension Hito 30b:** las propiedades `navigator` faltantes (plugins, mimeTypes, appVersion,
product, onLine, etc.) provocan que Google/Facebook/YouTube detecten a Freedom como bot. Los
nuevos valores normalizados cierran esa brecha — son constantes fijas, idénticas para todos los
usuarios, sin filtrar datos reales del dispositivo.

## 2. Contrato de la API

Definida en `include/anti_fp.h`.

```c
/* Relojes: granularidad gruesa contra timing/fingerprinting de alta resolucion. */
uint64_t fp_timer_resolution_ms(void);
uint64_t fp_coarsen_time_ms(uint64_t raw_ms);

/* Identidad normalizada (baja entropia, igual para todos los usuarios). */
const char *fp_user_agent(void);
const char *fp_accept_language(void);
const char *fp_accept_language_header(void);
const char *fp_timezone(void);
const char *fp_platform(void);
const char *fp_vendor(void);
int         fp_hardware_concurrency(void);
int         fp_device_memory_gb(void);

/* Extensiones Hito 30b: completan el objeto navigator con valores estandar de Firefox. */
const char *fp_app_version(void);       /* misma cadena que fp_user_agent() */
const char *fp_app_code_name(void);     /* "Mozilla" */
const char *fp_product(void);           /* "Gecko" */
const char *fp_app_name(void);          /* "Netscape" */
const char *fp_product_sub(void);       /* "20100101" */
const char *fp_oscpu(void);             /* "Linux x86_64" */
const char *fp_build_id(void);          /* firefox build id fijo */
int         fp_max_touch_points(void);  /* 0 (desktop) */
int         fp_on_line(void);           /* 1 (true) */
int         fp_cookie_enabled(void);    /* 1 (true) */

/* Resolucion de pantalla recortada a un bucket estandar (corta entropia). */
void fp_bucket_screen(int w, int h, int *out_w, int *out_h);

/* Envenenado de lectura (canvas/audio) determinista por sesion. */
void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);

/* Deriva clave de readback por ORIGEN a partir del secreto de sesion y eTLD+1. */
uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);
```

## 3. Semantica

- `fp_timer_resolution_ms`: devuelve `FP_TIMER_RESOLUTION_MS` (100).
- `fp_coarsen_time_ms(t)`: `t - (t % resolucion)`.
- `fp_user_agent` / `fp_accept_language` / `fp_accept_language_header` / `fp_timezone` /
  `fp_platform` / `fp_vendor` / `fp_hardware_concurrency` / `fp_device_memory_gb`: constantes fijas.
- **Extension Hito 30b:** `fp_app_version` = misma cadena que `fp_user_agent` (Firefox usa la UA
  como appVersion). `fp_app_code_name` = "Mozilla" (historico, todos los browsers). `fp_product` =
  "Gecko" (identidad de motor Firefox). `fp_app_name` = "Netscape" (historico). `fp_product_sub` =
  "20100101" (fecha de build Gecko, Firefox la mantiene constante). `fp_oscpu` = "Linux x86_64"
  (coherente con UA/platform). `fp_build_id` = fecha de build fija. `fp_max_touch_points` = 0
  (desktop sin touch). `fp_on_line` = 1 (conectado a red). `fp_cookie_enabled` = 1 (cookies
  habilitadas).
- `fp_bucket_screen`: elige el bucket estandar de mayor area que quepa en `(w,h)`.
- `fp_perturb`: PRNG con clave, voltea LSB en ~1/16 de bytes.
- `fp_origin_key`: FNV-1a del dominio + splitmix64 con session_key.

## 4. Garantias

1. **Anti-entropia por defecto:** valores expuestos uniformes; dispositivo real no se filtra.
2. **No enlazabilidad:** envenenado dependiente de clave por sesion y por eTLD+1.
3. **Imperceptibilidad:** envenenado solo toca LSBs.
4. **Puro y reentrante:** sin I/O ni estado global.
5. **Fuente unica de identidad para JS y red:** macros compartidas entre `js_env` y `secure_fetch`.

## 5. Matriz de pruebas

`tests/test_anti_fp.c` (cmocka):
- `fp_coarsen_time_ms`: alinea hacia abajo; idempotente; resolucion > 0.
- Identidad: no nula, no vacia; `fp_timezone()=="UTC"`; `fp_vendor()==""`.
- Extensiones Hito 30b: `fp_app_code_name()=="Mozilla"`; `fp_product()=="Gecko"`;
  `fp_app_name()=="Netscape"`; `fp_max_touch_points()==0`; `fp_on_line()==1`; `fp_cookie_enabled()==1`.
- `fp_bucket_screen`: 1920x1080, 1680x1050, 1366x768, 640x480.
- `fp_perturb`: determinista; acotado al LSB; sensible a clave; NULL/len 0 no crashea.
- `fp_origin_key`: determinista; por-sitio; por-sesion; namespace vacio.

## 6. Fuera de alcance

- Resistencia a huella de fuentes, AudioContext real, WebGL parameters.
- API real de canvas 2D / WebGL (hoy solo readback envenenado).
