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
const char *fp_accept_language(void);              /* lista, p.ej. "en-US,en" */
const char *fp_accept_language_header(void);       /* valor de header HTTP, "en-US,en;q=0.5" */
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

/* Deriva la clave de readback por ORIGEN a partir del secreto de sesion y el
 * dominio registrable (eTLD+1) del sitio. misma (session_key,dominio) => misma
 * clave (el envenenado es estable dentro de un sitio); dominios distintos bajo
 * la misma sesion => claves distintas con probabilidad abrumadora (la huella de
 * canvas/audio NO es enlazable entre sitios). dominio NULL o "" se trata como un
 * unico namespace (su propia clave estable): nunca filtra nada ni aborta. */
uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);
```

## 3. Semántica

- `fp_timer_resolution_ms`: devuelve `FP_TIMER_RESOLUTION_MS` (100). 
- `fp_coarsen_time_ms(t)`: `t - (t % resolucion)`. Un atacante no puede medir diferencias por
  debajo de la rejilla. Idempotente sobre valores ya alineados.
- `fp_user_agent` / `fp_accept_language` / `fp_accept_language_header` / `fp_timezone` /
  `fp_platform` / `fp_vendor` / `fp_hardware_concurrency` / `fp_device_memory_gb`: constantes fijas
  e idénticas para todos. No reflejan el dispositivo real. `fp_platform` es coherente con la UA
  (`"Linux x86_64"`); `fp_vendor` es `""`. Punteros de cadena estáticos (no liberar).
- **Fuente única de identidad para JS y red:** las cadenas viven como macros (`FP_USER_AGENT`,
  `FP_ACCEPT_LANGUAGE`, `FP_ACCEPT_LANGUAGE_HEADER`) compartidas por las bindings JS
  (`navigator.*`) **y** por la capa de red (`secure_fetch`: headers `User-Agent` y
  `Accept-Language`). Un desajuste entre la identidad visible por JS y la enviada por la red **es en
  sí mismo huella de alta entropía** (y señal de bot que rompe sitios como Google), así que ambas
  deben coincidir. La UA es una cadena común de **Firefox/Linux** (no contiene `"Freedom"`):
  maximiza el conjunto de anonimato en vez de delatar el navegador.
- `fp_accept_language` devuelve la **lista** (`"en-US,en"`, para `navigator.languages`);
  `fp_accept_language_header` devuelve el **valor de header HTTP** con q-value (`"en-US,en;q=0.5"`).
  Son formas distintas de la misma preferencia: la lista no lleva `;q=`.
- `fp_bucket_screen`: elige el bucket estándar de **mayor área que quepa** en `(w,h)`; si ninguno
  cabe, el bucket más pequeño. Buckets: 1920x1080, 1600x900, 1536x864, 1440x900, 1366x768,
  1280x720, 1024x768, 800x600. `out_w`/`out_h` no nulos.
- `fp_perturb`: PRNG con clave (`session_key`) recorre el buffer; en un subconjunto disperso
  (~1/16) hace `buf[i] ^= 1`. Garantías: **determinista** (misma clave ⇒ misma salida),
  **acotado** (cada byte cambia a lo sumo en ±1 y solo en el LSB), **sensible a la clave** (claves
  distintas ⇒ salidas distintas con alta probabilidad sobre buffers grandes). `len == 0` o
  `buf == NULL`: no hace nada.
- `fp_origin_key(session_key, dominio)`: hash FNV-1a del dominio mezclado con el secreto de
  sesión y finalizado con `splitmix64` (el mismo primitivo de `fp_perturb`). Es la **derivación
  pura**: el orquestador (worker de pestaña) calcula el eTLD+1 con `request_policy` y la pasa aquí.
  Garantías: **determinista** (misma `(session_key,dominio)` ⇒ misma clave, el envenenado es
  estable dentro de un sitio), **no enlazable entre orígenes** (dominios distintos bajo la misma
  sesión ⇒ claves distintas con probabilidad abrumadora; un colisión solo ocurre ante una colisión
  FNV, irrelevante para dominios reales), **sensible a la sesión** (mismo sitio, otra
  `session_key` ⇒ otra clave). `dominio == NULL` o `""` colapsan a un **único namespace** (clave
  estable propia, distinta de cualquier dominio real): nunca aborta ni filtra. Sin I/O ni
  asignación.

## 4. Garantías

1. **Anti-entropía por defecto:** los valores expuestos son uniformes; el dispositivo real no se
   filtra.
2. **No enlazabilidad (entre sesiones y entre orígenes):** el envenenado depende de la clave; entre
   sesiones (clave distinta) la huella de canvas/audio cambia. Además, dentro de una misma sesión la
   clave se deriva **por eTLD+1** con `fp_origin_key`, de modo que dos sitios distintos ven ruido
   distinto: un tracker no puede correlacionar la lectura de canvas/audio de un origen con la de
   otro (no cross-origin linking).
3. **Imperceptibilidad:** el envenenado solo toca LSBs de un subconjunto disperso (cambio visual/
   acústico nulo a efectos prácticos).
4. **Puro y reentrante:** sin I/O ni estado global; ASan/UBSan limpios; sin asignación dinámica.

## 5. Matriz de pruebas

`tests/test_anti_fp.c` (cmocka):
- `fp_coarsen_time_ms`: alinea hacia abajo; idempotente; resolución > 0.
- Identidad: no nula, no vacía; `fp_timezone()=="UTC"`; `fp_platform()=="Linux x86_64"`;
  `fp_vendor()==""`; valores fijos coherentes. La UA **no contiene** `"Freedom"` y **sí** contiene
  `"Firefox"`; `fp_accept_language()=="en-US,en"` (sin `;`); `fp_accept_language_header()` lleva
  q-value (`"en-US,en;q=0.5"`).
- `fp_bucket_screen`: 1920x1080→igual; 1680x1050→1600x900; 1366x768→igual; 640x480→800x600.
- `fp_perturb`: determinista (dos copias, misma clave ⇒ iguales); acotado (`out^in ∈ {0,1}`);
  sensible a la clave (claves distintas ⇒ difieren en buffer grande); `NULL`/`len 0` no crashea.
- `fp_origin_key`: determinista (misma `(sesión,dominio)` ⇒ misma clave); por-sitio (dominios
  distintos ⇒ claves distintas); por-sesión (misma site, otra sesión ⇒ otra clave); `NULL` y `""`
  colapsan al mismo namespace y difieren de un dominio real; **invariante de extremo a extremo:** el
  mismo buffer envenenado bajo las claves de dos sitios diverge, y reproduce el mismo resultado para
  el mismo sitio.

## 6. Fuera de alcance

- Cableado a `navigator`/`screen`/`Date`/`performance`/`canvas` reales (cuando existan esas
  bindings JS).
- Resistencia a huella de fuentes, `AudioContext` real, WebGL parameters (mismas primitivas
  aplicarán).

> **Cerrado (antes fuera de alcance):** la clave de readback **por eTLD+1**. `anti_fp` aporta la
> derivación pura `fp_origin_key`; el orquestador (worker de pestaña en `tab`) calcula el dominio
> registrable con `request_policy` (`rp_host_of`→`rp_site_of`, tabla PSL) sobre la URL de la página
> y se la pasa a `je_install_canvas`. El secreto de sesión sigue siendo aleatorio por worker
> (`getrandom`); `fp_origin_key` lo combina con el sitio para que el envenenado sea por-origen.
