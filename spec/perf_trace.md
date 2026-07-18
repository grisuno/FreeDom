# spec: perf_trace (`pt_`)

> Fase R0 — Plan de Optimización de Render. Módulo **puro**: acumulador de spans de
> tiempo por etapa del pipeline de render. No lee el reloj, no hace I/O, sin estado
> global, reentrante. El orquestador (headless `freedom.c` / GUI `gui/browser_ui.c`)
> mide con `clock_gettime(CLOCK_MONOTONIC)` y solo llama a estas funciones puras.

## 1. Propósito

Hasta ahora Freedom no tiene ninguna instrumentación de rendimiento (cero timings,
cero contador de frames — confirmado por auditoría de código, julio 2026). Sin
números no hay optimización honesta: cualquier hito de las fases R1+ del plan de
render exige un baseline antes/después. `perf_trace` es la superficie mínima y
auditable que permite acumular, consultar y volcar esos números de forma
determinista, sin telemetría implícita (Zero Knowledge: nunca se envía a ningún
lado, solo se imprime localmente bajo opt-in explícito — ver `spec/freedom.md`
`--dump-timings` y `FREEDOM_PERF`).

## 2. Modelo

Nueve etapas fijas del pipeline, en el orden en que ocurren en una carga+frame:

```c
typedef enum {
    PT_FETCH = 0,
    PT_PARSE,
    PT_STYLE,
    PT_IPC,
    PT_RD_BUILD,
    PT_LAYOUT,
    PT_PAINT,
    PT_COMMIT,
    PT_SHAPE,
    PT_STAGE_COUNT
} pt_stage;
```

Por etapa se guarda un anillo acotado de muestras (`PT_MAX_SAMPLES = 256`), la
última muestra y el total de muestras vistas (para reportar cuántas se
descartaron si el anillo dio la vuelta). **Por qué un cap fijo y no la cadena de
bloques V-003:** la fuente de estas muestras es el propio reloj monotónico del
lado confiable llamado por el propio orquestador — no es un acumulador de datos
de tamaño controlado por contenido remoto (la doctrina V-003 aplica a eso). 256
muestras por etapa alcanza para cualquier sesión de benchmark o interactiva
razonable; al llenarse, el anillo sobreescribe la muestra más vieja (FIFO),
nunca crece ni se cae.

## 3. API

```c
#define PT_MAX_SAMPLES 256

typedef struct pt_stage_stats {
    uint64_t samples[PT_MAX_SAMPLES];
    size_t   fill;    /* muestras válidas hoy en el anillo, <= PT_MAX_SAMPLES */
    size_t   next;    /* próxima posición de escritura (wrap) */
    size_t   total;   /* total de muestras vistas alguna vez (incl. descartadas) */
} pt_stage_stats;

typedef struct pt_trace {
    pt_stage_stats stage[PT_STAGE_COUNT];
} pt_trace;

/* Reinicia todas las etapas a vacío. NULL-safe (no-op). */
void pt_init(pt_trace *t);

/* Resta end_us - start_us con guarda anti-underflow: si end < start (reloj no
 * monotónico observado, o mal uso del llamador), devuelve 0 en vez de un
 * uint64_t gigante por wraparound. Pura. */
uint64_t pt_elapsed_us(uint64_t start_us, uint64_t end_us);

/* Registra una muestra (en microsegundos) para la etapa dada. NULL-safe y
 * stage-bounds-safe: t==NULL o stage fuera de [0, PT_STAGE_COUNT) es no-op
 * (fail-closed: nunca escribe fuera del arreglo). */
void pt_record(pt_trace *t, pt_stage stage, uint64_t elapsed_us);

/* Cuántas muestras válidas hay hoy en el anillo de la etapa (<= PT_MAX_SAMPLES). */
size_t pt_count(const pt_trace *t, pt_stage stage);

/* Última muestra registrada; 0 si no hay ninguna o t==NULL. */
uint64_t pt_last_us(const pt_trace *t, pt_stage stage);

/* Mínimo / máximo / mediana sobre las muestras actualmente en el anillo.
 * 0 si no hay muestras. La mediana ordena una copia local (<=256 elementos,
 * costo acotado) sin mutar el estado. */
uint64_t pt_min_us(const pt_trace *t, pt_stage stage);
uint64_t pt_max_us(const pt_trace *t, pt_stage stage);
uint64_t pt_median_us(const pt_trace *t, pt_stage stage);

/* Nombre corto en minúsculas de la etapa ("fetch", "parse", ... "shape").
 * Cadena estática; nunca NULL (etapa fuera de rango -> "unknown"). */
const char *pt_stage_name(pt_stage stage);

/* Vuelca una línea determinista por cada etapa con al menos una muestra:
 *   stage=<nombre> n=<total> last_us=<n> min_us=<n> max_us=<n> median_us=<n>\n
 * en orden de enum (PT_FETCH primero). Doctrina V-004 snprintf fail-closed:
 * si el buffer se llena a mitad de una línea, trunca ahí (nunca desborda) y
 * devuelve la cantidad de bytes efectivamente escritos (sin contar el NUL).
 * buf/cap == NULL/0 -> devuelve 0 sin escribir. */
size_t pt_format(const pt_trace *t, char *buf, size_t cap);
```

## 4. Semántica (Dado-Cuando-Entonces)

- **Dado** `pt_init` → cada etapa tiene `count=0`, `last_us=0`, min/max/mediana `0`.
- **Dado** una muestra registrada con `pt_record(t, PT_LAYOUT, 1500)` →
  `pt_count(t, PT_LAYOUT)==1`, `pt_last_us==1500`, `pt_min_us==pt_max_us==pt_median_us==1500`.
- **Dado** `stage` fuera de `[0, PT_STAGE_COUNT)` → `pt_record` es no-op; las
  funciones de consulta devuelven `0`/`"unknown"` sin leer fuera de rango.
- **Dado** más de `PT_MAX_SAMPLES` registros en una etapa → `pt_count` se
  satura en `PT_MAX_SAMPLES`; las muestras más viejas se pierden (FIFO); `last_us`
  siempre refleja la más reciente sin importar el wraparound.
- **Dado** `pt_elapsed_us(start, end)` con `end < start` → `0` (nunca un valor
  gigante por underflow de `uint64_t`).
- **Dado** `t == NULL` en cualquier función → no-op o `0`/`"unknown"`, nunca crash.
- **Dado** `pt_format` con `cap` insuficiente para todas las líneas → escribe las
  líneas completas que entran y se detiene ahí (nunca escribe una línea a medias
  ni desborda `buf`).
- **Dado** dos llamadas a `pt_format` sobre el mismo estado (sin `pt_record` de
  por medio) → salida byte-idéntica (determinismo, útil para diffs antes/después
  de un cambio de rendimiento).

## 5. Consumidores previstos (fuera de este módulo, no implementados aquí)

- `freedom.c` (headless): `--dump-timings` mide fetch/espera-IPC/rd_build/
  layout/paint/commit del lado padre alrededor de una exportación
  `--download-png`, y llama `pt_format` sobre stdout al final.
- `gui/browser_ui.c`: bajo `FREEDOM_PERF=1` (opt-in, nunca por defecto), mide
  `layout_doc`/`position_doc`/`paint_structured`/commit de cada `redraw` y
  vuelca a stderr; nunca se activa implícitamente ni se envía a ningún lado
  (Zero Knowledge).
- `Makefile` `bench`: corre el binario headless N veces sobre un corpus local
  y reporta la mediana por etapa.

## 6. Fuera de alcance

- Lectura del reloj (responsabilidad exclusiva del orquestador que sí puede
  hacer syscalls).
- Persistencia de métricas entre procesos/sesiones.
- Envío remoto de cualquier dato (prohibido por doctrina — Zero Knowledge).
- Desglose de etapas internas del worker confinado (parse/style ya ocurren ahí;
  llegan al padre recién cuando el framing IPC se rehaga en R2.5 — hasta
  entonces `PT_IPC` incluye ese costo y así se documenta).
