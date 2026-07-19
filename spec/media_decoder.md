# media_decoder — decodificación confinada + ritmo de reproducción (pacing)

## Alcance

El proceso decoder (`--media-decoder <out_fd> <cmd_fd>`, fork+exec de
`/proc/self/exe`, perfil `OS_PROFILE_MEDIA_DECODER`) convierte segmentos
MPEG-TS/HLS (H.264/H.265 + AAC) en frames ARGB y PCM S16, y el lado GUI los
reproduce **a ritmo de PTS contra el reloj de pared** (antes: a velocidad de
decode — fast-forward hasta el deadlock de audio, ver §Errores corregidos).

## Protocolo de pipes (v2, 2026-07-19 — PTS en MICROSEGUNDOS)

Comandos (`cmd_fd`, parent→decoder):

| cmd | payload |
| :-- | :-- |
| `MD_DECODE` | `[len:size_t][bytes]` — un segmento TS completo (≤ `MD_MAX_SEGMENT_BYTES`, 32 MiB) |
| `MD_FLUSH` | — drena los decoders y emite `MD_EOS` |
| `MD_QUIT` | — salida ordenada |

Respuestas (`out_fd`, decoder→parent):

| tag | payload |
| :-- | :-- |
| `MD_STREAM_INFO` | `[codec:i32][w:i32][h:i32][has_audio:i32]` |
| `MD_FRAME` | `[pts_us:i64][w:i32][h:i32][dlen:size_t][argb]` — **pts en µs** (v2; antes segundos enteros, inservible para pacing) |
| `MD_AUDIO_FRAME` | `[pts_us:i64][rate:i32][ch:i32][dlen:size_t][pcm S16LE]` |
| `MD_ERROR` | `[len:size_t][msg]` — no fatal, el stream continúa |
| `MD_EOS` | — fin del stream (tras `MD_FLUSH`) |

El PTS de video se calcula con el `time_base` del stream **del segmento que se
está decodificando** (v2; antes usaba el time_base del primer segmento para
todos — PTS corrupto en cuanto los índices de stream difieren).

**Dado** el primer `MD_DECODE` **cuando** el decoder se inicializa **entonces**
emite `MD_STREAM_INFO` **y decodifica ese mismo segmento** (v2; antes el
contenido del primer segmento se usaba solo para el probe y sus frames se
perdían — el usuario nunca veía los primeros ~10 s).

## Pacing (lado GUI, cerebro puro `md_pacer`)

El consumidor es el **regulador**: la GUI solo lee el siguiente frame del pipe
cuando el reloj de pared alcanza el instante debido del frame ya mostrado; la
contrapresión del pipe (frames ~1 MB ≫ capacidad del pipe) frena en cadena al
decoder (bloqueado en `write`) y al feeder (bloqueado en el cmd pipe). Nadie
necesita dormir: el pipeline entero queda regulado por el consumo.

Cerebro puro (`include/media_decoder.h`, `static inline`, testeado en
`tests/test_media_decoder.c`):

```c
typedef struct md_pacer { uint64_t epoch_ms; int64_t pts0_us; int primed; } md_pacer;
uint64_t md_pace_due_ms(md_pacer *p, uint64_t now_ms, int64_t pts_us);
```

- **Dado** un pacer virgen **cuando** llega el primer frame **entonces** ancla
  `epoch_ms=now`, `pts0_us=pts` y devuelve `now` (se muestra ya).
- **Dado** un pacer anclado **cuando** llega un frame con `pts >= pts0`
  **entonces** devuelve `epoch + (pts - pts0)/1000` (ms, saturado a ≥ epoch).
- **Dado** un PTS que retrocede (`pts < pts0`, discontinuidad HLS)
  **cuando** llega **entonces** re-ancla a `now` (nunca congela ni espera
  negativo).
- **Dado** un consumidor atrasado más de `MD_PACE_MAX_LAG_MS` (500 ms)
  **cuando** el due calculado quedó tan atrás **entonces** re-ancla a `now`
  (catch-up: no intenta reproducir el atraso acumulado a cámara rápida).
- **Dado** un salto de PTS hacia adelante cuyo due queda a más de
  `MD_PACE_MAX_STEP_MS` (5000 ms) del reloj **cuando** llega **entonces**
  re-ancla (un PTS hostil jamás agenda una espera de años).
- Entradas arbitrarias (overflow de resta de PTS hostil) no producen UB: la
  rama de retroceso excluye `pts < pts0` primero y la resta se hace en
  aritmética sin signo (wraparound definido), con guardas de overflow en la
  suma del due.

Bucle de eventos: el fd del decoder solo entra al `poll()` cuando
`now >= due`; si falta tiempo, el timeout del poll se acota a `due - now`
(≤ 33 ms de granularidad ya existente). Con `POLLIN` y due vencido se leen
hasta `MD_MAX_CATCHUP_READS` (4) frames por iteración (drenaje de atraso).

## Audio

`aplay` (S16LE raw) consume a tiempo real por su cuenta. El fd hacia aplay es
**O_NONBLOCK** y `audio_write` es **best-effort**: lo que no cabe se descarta
(con pacing el productor va a ~tiempo real, así que el descarte es raro).
**Dado** un pipe de audio lleno **cuando** la GUI escribe PCM **entonces**
NUNCA se bloquea el hilo de UI (v2; antes el `write` bloqueante congelaba todo
el navegador a los ~2 s: aplay drena 176 KB/s pero el decoder producía PCM a
velocidad de decode — ese era el "solo reproduce un par de segundos").

## Fin de stream y muerte del decoder

- `MD_EOS` ⇒ `video_active=0` (placeholder con poster).
- **EOF del pipe** (decoder muerto: `read()==0`) ⇒ `video_active=0` y cierre
  ordenado (v2; antes devolvía -1 y el poll re-disparaba `POLLHUP` en bucle
  ocupado para siempre).

## Errores corregidos (2026-07-19, v2)

1. Deadlock de audio: `audio_write` bloqueante en el hilo Wayland (causa raíz
   del "se detiene a los segundos").
2. Sin pacing de PTS: reproducción a velocidad de decode.
3. Frames del primer segmento descartados tras el probe.
4. PTS en segundos enteros / time_base del primer segmento aplicado a todos.
5. EOF del decoder tratado como error transitorio (busy-loop de POLLHUP).
6. **Drain de codec por segmento**: v1 enviaba `avcodec_send_packet(ctx,
   NULL)` al final de CADA segmento, dejando el codec en estado EOF
   permanente — todos los segmentos posteriores al primero decodificado se
   descartaban en silencio. v2 solo drena en `MD_FLUSH` (fin de stream);
   los frames retenidos por reorden salen con los paquetes del segmento
   siguiente. Verificado E2E: 3 segmentos HLS de 2 s ⇒ 150/150 frames,
   PTS µs monotónico, `MD_EOS` (harness con feeder separado — alimentar y
   leer desde el mismo hilo se atasca por la contrapresión del diseño).

## Superficie HTML/JS/CSS del elemento (2026-07-19)

- **HTML** (`page_view`): con varios `<source>`, gana por atributo `type` el
  contenedor nativo del pipeline (`mpegurl`/`mp2t`/`mp4`), con fallback al
  primero con `src`. El contenido de fallback dentro de `<video>`/`<audio>`
  (para motores sin soporte de media) **no se renderiza nunca** — este motor
  pinta el elemento (`PV_VIDEO`).
- **JS** (`js_dom`, identity-safe, sin red): fachada `HTMLMediaElement` en los
  wrappers de `<video>`/`<audio>` — `play()` (Promise resuelta), `pause()`,
  `load()`, `canPlayType()` (probably: mp4/mpegurl/mp2t; maybe: webm/ogg),
  `muted`/`autoplay`/`loop`/`controls`/`playsinline` reflejando atributos,
  `poster`, `currentSrc`, `buffered`/`played`/`seekable` (TimeRanges vacíos),
  constantes `HAVE_*`/`NETWORK_*`, handlers `on<evento>` de media registrados
  (sintéticos, nunca disparan), y constructor global `new Audio(src)` que crea
  un `<audio>` real envuelto. La reproducción REAL vive solo en el pipeline
  confiable (este spec); el worker jamás decodifica ni toca red por media.
- **CSS**: `object-fit`/`aspect-ratio`/box model de autor ya aplicaban a las
  cajas de video (sin cambios).

## Fuera de alcance

- Sincronía A/V fina (lip-sync): aplay bufferiza ~cientos de ms; aceptado v1.
- Seek/pausa, selección de calidad, DASH, MSE/EME.
- Live HLS (playlist rolling): solo VOD (lista completa al empezar).
