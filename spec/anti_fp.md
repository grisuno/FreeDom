# Especificación: `anti_fp`

> Hito 5 — Doctrina anti-vigilancia (anti-fingerprinting). Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_anti_fp.c` debe fallar hasta que
> exista `src/anti_fp.c` (estado rojo).

## 1. Propósito

`anti_fp` reúne las **primitivas puras** de resistencia al *fingerprinting* (huella de
dispositivo). El adversario A3 (vigilancia corporativa) combina señales de alta entropía leídas
desde JS — user-agent, resolución, zona horaria, núcleos, relojes de alta precisión, lectura de
canvas/audio — para identificar al usuario entre sitios. La estrategia, en dos frentes:

1. **Reducir la entropía:** presentar valores **normalizados** e idénticos para todos los usuarios
   de Freedom (no el valor real del dispositivo).
2. **Envenenar lo inevitable:** a señales que no se pueden uniformar (lectura de canvas/audio,
   relojes) se les aplica **ruido determinista por sesión** o **granularidad gruesa**, de modo que
   la huella sea estable dentro de una sesión pero no enlazable entre sesiones ni precisa.

Este módulo es la **lógica pura** (sin I/O, sin estado global). El cableado a las futuras APIs JS
(`navigator`, `screen`, `Date`/`performance`, `canvas`) se hará cuando esas APIs existan; aquí
solo se define qué se expone y cómo se transforma.

## 2. Contrato de la API

Definida en `include/anti_fp.h`.

```c
/* Relojes: granularidad gruesa contra timing/fingerprinting de alta resolucion. */
uint64_t fp_timer_resolution_ms(void);
uint64_t fp_coarsen_time_ms(uint64_t raw_ms);     /* redondea hacia abajo a la rejilla */

/* Identidad normalizada (baja entropia, igual para todos los usuarios). */
const char *fp_user_agent(void);
const char *fp_accept_language(void);              /* p.ej. "en-US,en" */
const char *fp_timezone(void);                     /* "UTC" */
const char *fp_platform(void);                     /* "Linux x86_64" (coherente con la UA) */
const char *fp_vendor(void);                       /* "" (sin vendor; minima entropia) */
int         fp_hardware_concurrency(void);         /* fijo */
int         fp_device_memory_gb(void);             /* fijo */

/* Resolucion de pantalla recortada a un bucket estandar (corta entropia). */
void fp_bucket_screen(int w, int h, int *out_w, int *out_h);

/* Envenenado de lectura (canvas/audio) determinista por sesion: invierte solo
 * el bit menos significativo de un subconjunto disperso elegido por la clave.
 * misma (buf,key) => misma salida; distinta key => distinta salida. */
void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);
```

## 3. Semántica

- `fp_timer_resolution_ms`: devuelve `FP_TIMER_RESOLUTION_MS` (100). 
- `fp_coarsen_time_ms(t)`: `t - (t % resolucion)`. Un atacante no puede medir diferencias por
  debajo de la rejilla. Idempotente sobre valores ya alineados.
- `fp_user_agent` / `fp_accept_language` / `fp_timezone` / `fp_platform` / `fp_vendor` /
  `fp_hardware_concurrency` / `fp_device_memory_gb`: constantes fijas e idénticas para todos. No
  reflejan el dispositivo real. `fp_platform` es coherente con la UA (`"Linux x86_64"`); `fp_vendor`
  es `""`. Punteros de cadena estáticos (no liberar).
- `fp_bucket_screen`: elige el bucket estándar de **mayor área que quepa** en `(w,h)`; si ninguno
  cabe, el bucket más pequeño. Buckets: 1920x1080, 1600x900, 1536x864, 1440x900, 1366x768,
  1280x720, 1024x768, 800x600. `out_w`/`out_h` no nulos.
- `fp_perturb`: PRNG con clave (`session_key`) recorre el buffer; en un subconjunto disperso
  (~1/16) hace `buf[i] ^= 1`. Garantías: **determinista** (misma clave ⇒ misma salida),
  **acotado** (cada byte cambia a lo sumo en ±1 y solo en el LSB), **sensible a la clave** (claves
  distintas ⇒ salidas distintas con alta probabilidad sobre buffers grandes). `len == 0` o
  `buf == NULL`: no hace nada.

## 4. Garantías

1. **Anti-entropía por defecto:** los valores expuestos son uniformes; el dispositivo real no se
   filtra.
2. **No enlazabilidad:** el envenenado depende de la clave de sesión; entre sesiones (clave
   distinta) la huella de canvas/audio cambia.
3. **Imperceptibilidad:** el envenenado solo toca LSBs de un subconjunto disperso (cambio visual/
   acústico nulo a efectos prácticos).
4. **Puro y reentrante:** sin I/O ni estado global; ASan/UBSan limpios; sin asignación dinámica.

## 5. Matriz de pruebas

`tests/test_anti_fp.c` (cmocka):
- `fp_coarsen_time_ms`: alinea hacia abajo; idempotente; resolución > 0.
- Identidad: no nula, no vacía; `fp_timezone()=="UTC"`; `fp_platform()=="Linux x86_64"`;
  `fp_vendor()==""`; valores fijos coherentes.
- `fp_bucket_screen`: 1920x1080→igual; 1680x1050→1600x900; 1366x768→igual; 640x480→800x600.
- `fp_perturb`: determinista (dos copias, misma clave ⇒ iguales); acotado (`out^in ∈ {0,1}`);
  sensible a la clave (claves distintas ⇒ difieren en buffer grande); `NULL`/`len 0` no crashea.

## 6. Fuera de alcance

- Cableado a `navigator`/`screen`/`Date`/`performance`/`canvas` reales (cuando existan esas
  bindings JS).
- Resistencia a huella de fuentes, `AudioContext` real, WebGL parameters (mismas primitivas
  aplicarán).
- Generación/gestión de la clave de sesión por eTLD+1 (la define el orquestador de sesión).
