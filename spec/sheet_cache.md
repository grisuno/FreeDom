# sheet_cache (`shc_`) — hoja de estilos parseada, retenida por clave exacta

## Por qué

Cada `OP_TICK`/`OP_CLICK`/`OP_EVENT`/`OP_MOUSE` re-deriva la vista con `pv_build_styled`, y
cada derivación **re-parseaba todo el CSS de la página** aunque el texto no hubiera cambiado.
Medido (2026-11-11, `FREEDOM_JS_PROFILE=1`, `--as-gui`): una sola carga de GitHub parsea 37
veces la misma hoja de 6,5 MB a ~131 ms cada una (≈4,8 s de 19,6 s). `getComputedStyle`
(`pv_computed_new`) la parsea otra vez por su cuenta.

El parseo es una función pura de sus entradas (`spec/css.md`), así que el resultado se puede
retener. Idea tomada del `StylesheetCache` de Obscura: **una sola entrada, clave exacta**.
Sin hash (cero riesgo de colisión), sin crecimiento entre documentos.

## Contrato

- `shc_cache`: dueño único = quien lo creó (`child_state` del worker). `shc_free` idempotente.
- `shc_acquire(cache, key)` devuelve un `shc_sheet` con **una referencia** del llamador;
  `shc_release` la suelta. La hoja es de solo lectura (`const css_sheet *`).
- `cache == NULL` ⇒ parseo simple sin retención (mismo camino de código, mismo resultado).
- El caché vive **dentro del worker confinado**: no cruza el IPC, no toca disco, no hay
  estado global. Reentrante.

## Clave (todas las entradas del parseo)

| Componente | Motivo |
| :-- | :-- |
| bytes del texto (comparación `memcmp`, no hash) | la hoja |
| `prefers_dark`, `print`, `width_px` | gate de `@media` |
| `root_scope` (NULL ≠ "") | recolección de custom properties por clase |
| presencia de `scope_match` | con o sin matcher de raíz |
| **respuestas** de `scope_match` | única ventana del parseo al DOM vivo |

`scope_match` es un callback contra el DOM vivo (`<html>`/`<body>`): su respuesta no está en
el texto. El módulo envuelve el matcher, **graba cada pregunta** (copia compacta del selector,
`csel_compact_dup`) **y su respuesta**, y en un candidato a acierto **las vuelve a preguntar**
al matcher de la clave nueva. Acierto ⇔ todas las respuestas coinciden. Es exacto por
construcción: no hay huella que mantener sincronizada con lo que el matcher lee, y cubre por
igual atributos, clases y selectores estructurales (`:has()`, `+`, `:empty`).

Diseño descartado (primera versión, medida): huella de atributos de las raíces + marcar como
no reutilizable todo parseo que consultara un selector estructural. En GitHub **ninguna** de
las 37 derivaciones se retenía (basta una regla de raíz dependiente de estructura en 6,5 MB
para descartar la hoja entera; no se aisló cuál). El replay acierta 34 de 37.

## Dado-Cuando-Entonces

- **Dado** un caché y una clave, **cuando** se adquiere dos veces con la misma clave,
  **entonces** la segunda es un acierto y devuelve la MISMA hoja sin parsear.
- **Dado** un acierto previo, **cuando** cambia un byte del texto (misma longitud), el ancho,
  `prefers_dark`, `print`, `root_scope` o la presencia del matcher, **entonces** es un fallo.
- **Dado** un parseo que consultó al matcher, **cuando** el matcher responde distinto a
  cualquiera de las preguntas grabadas (un script cambió `data-theme` en `<html>`),
  **entonces** es un fallo y se parsea de nuevo; **cuando** responde igual a todas, acierto.
- **Dado** un parseo que hace más de `FC_SHC_MAX_QUERIES` preguntas, o un OOM al grabar,
  **entonces** la hoja se usa esta vez y **nunca se reutiliza** (fail-closed: comportamiento
  idéntico al de antes del caché).
- **Dado** un texto mayor que el tope del caché, **entonces** se parsea normal y no se retiene,
  y no desaloja la entrada retenida.
- **Dado** un `shc_sheet` adquirido, **cuando** una adquisición posterior reemplaza la entrada
  o el caché se libera, **entonces** la hoja sigue viva hasta su `shc_release` (refcount).
- **Dado** OOM del handle o clave NULL, **entonces** `shc_acquire` devuelve NULL; una hoja cuyo
  parseo falló se representa con `shc_css() == NULL` (el módulo css la trata como vacía).

## Garantías de seguridad

- El resultado servido es **el mismo objeto** que produjo `css_parse_scoped` con entradas
  idénticas: el caché no puede relajar ningún fail-closed del parser (`url()`, topes anti-DoS).
- Memoria acotada: una entrada; texto ≤ `FC_SHC_MAX_TEXT_BYTES`; ≤ `FC_SHC_MAX_QUERIES`
  selectores compactos.
- Sin hash ⇒ sin colisión que sirva la hoja de otro documento. Un worker reutilizado entre
  cargas solo acierta si TODAS las entradas coinciden, y entonces el resultado es correcto
  por pureza del parser.
- El matcher debe ser determinista y sin efectos (lo es: `cch_element_matches`).

## Medición (2026-11-11, `--as-gui`, github.com, `FREEDOM_JS_PROFILE=1`)

| | antes | después |
| :-- | :-- | :-- |
| derivaciones / parseos reales | 37 / 37 | 37 / 3 |
| tiempo en parseo CSS | 4981 ms | 520 ms |
| CPU usuario de la carga | 16,4 s | 11,4 s |

En la **ventana real** (Xvfb + weston, ventana fija de 40 s, dos rondas intercaladas con HEAD
compilado el mismo día): parseo CSS 3772/3750 → 499/500 ms, CPU del navegador y sus workers
14,2/13,9 → 11,1/11,0 s, 25 de 29 derivaciones servidas del caché. Captura de la ventana
(`FREEDOM_GUI_SHOT`) visualmente idéntica a HEAD. `make parity`: TOTAL +0.00.

## Errores

| Situación | Resultado |
| :-- | :-- |
| `key == NULL`, `text == NULL` con `len > 0` | `NULL` |
| `len == SIZE_MAX` (V-001) | `NULL` |
| OOM al copiar la clave o al grabar una pregunta | hoja válida sin retención |
| OOM del handle | `NULL` |

## Fuera de alcance

- Invalidación incremental de la cascada (mapa de dependencias de selectores): hito propio.
- Persistir entre procesos o en disco; compartir entre workers.
- Cachear `css_parse_logged` (diagnóstico).
