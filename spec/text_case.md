# spec: text_case (`tc_`) — mayúsculas/minúsculas y versalitas sintéticas

## Por qué existe (medido)

`text-transform` solo mapeaba ASCII y `font-variant: small-caps` se aproximaba
**midiendo** cada palabra en mayúsculas pero **pintándola** en su caja original:
cada palabra quedaba rodeada de un hueco del ancho de la diferencia (sonda
`Small Caps text here` → `Small   Caps text  here`). Firefox sintetiza las versalitas
cuando la fuente no trae la característica `smcp`: las minúsculas se dibujan como
mayúsculas al **0.8** del tamaño (`SMALL_CAPS_SCALE_FACTOR` de Gecko) y el resto
queda igual (medido en pool.ntp.org: el menú `ul#nav li{font-variant:small-caps}`
sale `JOIN THE POOL` en Firefox y `join the pool` en Freedom).

## Contrato

```c
uint32_t tc_upper(uint32_t cp);
uint32_t tc_lower(uint32_t cp);
int      tc_is_lower(uint32_t cp);
size_t   tc_transform(const char *s, size_t n, int transform, int word_start,
                      char *out, size_t cap);
size_t   tc_smallcaps_runs(const char *s, size_t n, tc_run *out, size_t cap);
```

- `tc_upper`/`tc_lower`: mapeo simple 1:1 (Unicode `UnicodeData` simple case
  mapping) para ASCII, Latin-1, Latin Extended-A, griego básico y cirílico básico.
  **Invariante:** solo devuelven un punto de código que se codifica en UTF-8 con la
  MISMA cantidad de bytes que el de entrada; si no, la identidad. Así una
  transformación nunca cambia la longitud del texto y los índices de un fragmento
  siguen valiendo sobre el texto fuente. Fuera de esos bloques: identidad (`ß`, que
  en mayúscula es `SS`, queda igual: falla cerrado a no transformar).
- `tc_is_lower(cp)`: `tc_upper(cp) != cp`.
- `tc_transform`: copia `s[0,n)` a `out` aplicando `transform` (`CSS_TT_UPPERCASE`,
  `CSS_TT_LOWERCASE`, `CSS_TT_CAPITALIZE`; cualquier otro valor copia tal cual).
  `capitalize` pone en mayúscula la primera letra de cada palabra (tras un espacio,
  o al inicio si `word_start`). Devuelve los bytes escritos (siempre `n`), o 0 si
  `s`/`out` son NULL o `cap < n`. Un byte UTF-8 inválido se copia sin tocar.
- `tc_smallcaps_runs`: parte `s[0,n)` en tramos maximales consecutivos de
  "minúsculas" (`lowered = 1`: se pintan en mayúscula a escala reducida) y "resto"
  (`lowered = 0`). Los tramos cubren el texto entero, en orden, sin solaparse.
  Devuelve cuántos tramos escribió; si no caben en `cap`, el último tramo absorbe el
  resto con su `lowered` (nunca se pierde texto).

Puro, sin I/O, sin estado, sin asignaciones.

## Dado-Cuando-Entonces

- Dado `"Small"`, cuando `tc_smallcaps_runs`, entonces dos tramos: `"S"` (0) y
  `"mall"` (1).
- Dado `"a1b"`, entonces tres tramos `a`(1) `1`(0) `b`(1).
- Dado `"éñ"` (UTF-8), cuando `tc_transform(..., CSS_TT_UPPERCASE)`, entonces
  `"ÉÑ"` con la misma longitud en bytes.
- Dado `"straße"`, cuando uppercase, entonces `"STRAßE"` (ß no se expande).
- Dado `"hello world"` y `capitalize`, entonces `"Hello World"`.
- Dado `cap < n`, entonces 0 y `out` sin tocar.

## Fuera de alcance

Mapeos especiales de longitud variable (`ß`→`SS`, `ŉ`), reglas dependientes del
idioma (turco `i`→`İ`), sigma final contextual, `smcp` real de OpenType y
`all-small-caps`/`petite-caps`.
