# spec/css_length.md — `css_length` (`cl_`): la ÚNICA fuente de verdad de `<length>`

> **Estado:** SDD. Módulo puro, sin I/O, sin estado global, reentrante.
> **Referencia normativa:** CSS Values and Units Module Level 4, §5 (*Distance
> Units*) y §6 (*Font-relative* / *Viewport-relative lengths*).

---

## 1. Por qué existe este módulo

Antes de él, `src/css.c` resolvía longitudes en **cuatro tablas distintas y
mutuamente incompatibles**, cada una con su propio `16.0` en duro:

| Sitio | `px` | `em` | `rem` | `pt` | `%` | `vw/vh` | `cm/mm/Q/in/pc` | `ex/ch` |
| :-- | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| `interp_fontsize_ex` | ✓ | ✓ | ✓ | `1.333` | ✓ | ✓ | ✗ | ✗ |
| `interp_lineheight`  | ✓ | ✓ | =`em` | **✗** | ✓ | ✗ | ✗ | ✗ |
| `interp_len`         | ✓ | `×16` | =`em` | **✗** | – | ✓ | ✗ | ✗ |
| `media_len_px`       | ✓ | `×16` | `×16` | `4/3` | – | – | ✗ | ✗ |

Consecuencias medidas: `padding: 6pt` se **descartaba entero** (Hacker News está
escrito en `pt`), `rem` y `em` eran el mismo número, `vmax` valía lo mismo que
`vw` y `vmin` lo mismo que `vh` (solo correcto si el viewport es apaisado), y el
factor `1.333` no es `4/3`.

Este módulo reemplaza las cuatro. **Regla de oro: ninguna otra unidad de longitud
se resuelve fuera de `cl_`.** Una unidad nueva se agrega aquí y todos los
consumidores la obtienen solos.

**Nada de esto es una "regla de renderizado" inventada:** cada factor de
conversión es una cita literal de la spec (§5.2: `1in = 96px`, `1pt = 1/72in`,
`1pc = 1/6in`, `1cm = 1/2.54in`, `1mm = 1/10cm`, `1Q = 1/40cm`). Lo que el
módulo NO puede saber (métricas reales de la fuente, tamaño del viewport) entra
por el **contexto**, nunca por una constante enterrada en el código.

---

## 2. Contexto de resolución (`cl_ctx`)

Una longitud CSS no es un número: es un número **más el estado contra el que se
mide**. Ese estado es explícito y lo provee el llamador.

| Campo | Significado | Valor inicial (`cl_ctx_initial`) |
| :-- | :-- | :-- |
| `font_size` | `font-size` computado del elemento (px) | `CL_INITIAL_FONT_SIZE` (16, valor inicial de CSS) |
| `root_font_size` | `font-size` computado del elemento raíz (px) | ídem |
| `line_height` | `line-height` usado del elemento (px) | `CL_NORMAL_LINE_RATIO × font_size` |
| `root_line_height` | `line-height` usado de la raíz (px) | ídem |
| `viewport_w`, `viewport_h` | viewport **normalizado** (px) | `CSS_MEDIA_DEFAULT_WIDTH/HEIGHT` |
| `x_height` | altura de la x de la fuente (px), `<= 0` ⇒ fallback de spec | 0 |
| `zero_advance` | avance del glifo `0` (px), `<= 0` ⇒ fallback de spec | 0 |
| `cap_height` | cap-height de la fuente (px), `<= 0` ⇒ fallback de spec | 0 |
| `ideographic_advance` | avance del glifo `水` (px), `<= 0` ⇒ fallback | 0 |

**Zero Knowledge / anti-fingerprinting (doctrina, no negociable):** `viewport_w`
y `viewport_h` por defecto son el escritorio **normalizado** 1920×1080, nunca la
ventana real. Es la misma decisión que ya tomaba `viewport_unit_px`. Que una
longitud computada delate la geometría real de la ventana sería una fuga de
fingerprinting; el ancho de render solo alimenta las *media queries*
(`[[freedom-parity-container-diagnosis-2026-08-10]]`), no las unidades.

Los cuatro campos de métrica de fuente existen para que la capa de shaping
(`text_shape`, lado confiable, fuentes locales) los rellene **más adelante** sin
tocar una sola línea de este módulo. Mientras valgan `<= 0` se usan los
*fallbacks que la propia spec nombra* (§6.1.1–6.1.4), no números elegidos a ojo.

---

## 3. Unidades soportadas

### 3.1 Absolutas (§5.2) — factor exacto contra `px`

| Unidad | px por unidad | Cita |
| :-- | :-- | :-- |
| `px` | `1` | unidad canónica |
| `in` | `96` | `1in = 96px` |
| `pt` | `96/72` | `1pt = 1/72in` |
| `pc` | `96/6` | `1pc = 1/6in` |
| `cm` | `96/2.54` | `1cm = 1/2.54in` |
| `mm` | `96/25.4` | `1mm = 1/10cm` |
| `Q` | `96/101.6` | `1Q = 1/40cm` |

### 3.2 Relativas a la fuente (§6.1)

| Unidad | px por unidad | Fallback de spec cuando no hay métrica |
| :-- | :-- | :-- |
| `em` | `ctx->font_size` | — |
| `rem` | `ctx->root_font_size` | — |
| `ex` | `ctx->x_height` | `0.5em` (§6.1.1) |
| `ch` | `ctx->zero_advance` | `0.5em` (§6.1.2) |
| `cap` | `ctx->cap_height` | `0.7em` (§6.1.3, aproximación de la ascendente) |
| `ic` | `ctx->ideographic_advance` | `1em` (§6.1.4) |
| `lh` | `ctx->line_height` | — |
| `rlh` | `ctx->root_line_height` | — |

### 3.3 Relativas al viewport (§6.2)

`vw`/`vi` = `viewport_w/100`; `vh`/`vb` = `viewport_h/100`;
`vmin` = `min(w,h)/100`; `vmax` = `max(w,h)/100`.

Los prefijos `s` (*small*), `l` (*large*) y `d` (*dynamic*) — `svw`, `lvh`,
`dvmin`, … — se aceptan y valen **lo mismo** que la variante base: Freedom no
tiene chrome de navegador retráctil, así que los tres viewports coinciden por
construcción. Es lo que la spec permite, no una simplificación.

`vi`/`vb` asumen modo de escritura horizontal (`horizontal-tb`), el único que el
motor implementa hoy. Cuando exista `writing-mode` se resuelve aquí y en ningún
otro lado.

### 3.4 Fuera de alcance (fallan cerrado, `CL_ERR_UNIT`)

`%` (no es `<length>`: es `<percentage>`, y necesita un bloque contenedor que
este módulo no ve), unidades de ángulo/tiempo/frecuencia/resolución, y
`cqw`/`cqh`/`cqi`/`cqb`/`cqmin`/`cqmax` (*container queries*: sin contenedor de
consulta no hay respuesta correcta, y **inventar una sería peor que rechazar**).

---

## 4. Contrato — Dado / Cuando / Entonces

**Dado** un valor CSS NUL-terminado y un `cl_ctx`,
**cuando** se llama `cl_resolve(value, ctx, &px)`,
**entonces**:

| # | Dado | Entonces |
| :-- | :-- | :-- |
| 1 | `"0"` (cero sin unidad) | `CL_OK`, `px = 0`. §5: un cero sin unidad **es** un `<length>` válido. |
| 2 | `"12"` (no-cero sin unidad) | `CL_ERR_UNIT`. Un número suelto no-cero no es una longitud; inventarle `px` es exactamente la clase de regla que este proyecto prohíbe. |
| 3 | `"10pt"` | `CL_OK`, `px = 13.333…` (`10 × 96/72`) |
| 4 | `"1in"` = `"6pc"` = `"72pt"` = `"2.54cm"` = `"25.4mm"` = `"101.6Q"` | los seis dan exactamente `96` |
| 5 | `"2em"` con `font_size = 20` | `40` |
| 6 | `"2rem"` con `root_font_size = 10` | `20` (independiente de `font_size`) |
| 7 | `"1ex"` sin métrica, `font_size = 20` | `10` (fallback `0.5em`) |
| 8 | `"1ex"` con `x_height = 8` | `8` (la métrica real gana) |
| 9 | `"50vmin"`, viewport `1920×1080` | `540` (usa el eje **menor**) |
| 10 | `"50vmax"`, viewport `1920×1080` | `960` (usa el eje **mayor**) |
| 11 | `"10PX"`, `"10Px"`, `"1IN"` | unidades ASCII **case-insensitive** (§5). `Q` también. |
| 12 | `"-5px"`, `"+5px"`, `".5px"`, `"5.px"`, `"1e2px"` | sintaxis numérica CSS completa, signo incluido |
| 13 | `"50%"` | `CL_ERR_UNIT` (no es `<length>`) |
| 14 | `"10px "` / `" 10px"` | `CL_OK` (espacios ASCII a ambos lados se ignoran) |
| 15 | `"10 px"` | `CL_ERR_SYNTAX`. §4: un `<dimension>` no admite espacio entre número y unidad. |
| 16 | `"10px;"`, `"abc"`, `""` | `CL_ERR_SYNTAX` |
| 17 | `NULL` en cualquier argumento | `CL_ERR_NULL_ARG`, `*out` intacto |
| 18 | resultado `inf`/`nan` (p. ej. `"1e400px"`) | `CL_ERR_RANGE` |
| 18b | resultado finito pero enorme (`"1e300px"`) | `CL_OK`. El **clamp a `CSS_LEN_MAX` es del emisor**, no de la unidad: `CSS_LEN_MAX` es política anti-DoS del box model. Rechazar en vez de saturar convertiría `width:99999999px` de "muy ancho" a "sin ancho", que es un cambio de significado, no una defensa. |
| 19 | `"1cqw"` | `CL_ERR_UNIT` (fuera de alcance, falla cerrado) |

**Garantías transversales**

- **Pura:** sin `malloc`, sin I/O, sin estado global, sin `errno`. Segura para
  llamarse dentro del worker confinado.
- **Acotada:** no recorre más de `CL_MAX_TOKEN` bytes del valor; una entrada sin
  NUL dentro de ese límite falla cerrado.
- **Total:** para toda entrada devuelve un `cl_status`; `*out_px` **solo** se
  escribe en `CL_OK`.
- **Determinista:** misma entrada + mismo contexto ⇒ mismo bit de salida.

---

## 5. Qué NO hace

- No consulta el DOM, la cascada ni el bloque contenedor.
- No resuelve `calc()`/`min()`/`max()`/`clamp()`: el evaluador de `css.c` ya
  existe y **llama a este módulo** para cada término hoja. La aritmética queda
  allá; las unidades, acá.
- No aplica `zoom` (`zm_`) ni el clamp de `font-size` (`PV_FONT_*`).
- No decide si una propiedad acepta negativos: eso es del emisor (`emit_len`).

---

## 6. Integración (quién llama)

| Llamador | Antes | Ahora |
| :-- | :-- | :-- |
| `interp_len` | tabla propia, sin `pt` | `cl_resolve` con `cl_ctx_initial()` |
| `interp_lineheight` | tabla propia, sin `pt` | `cl_resolve` para el caso con unidad |
| `interp_fontsize_ex` | tabla propia, `1.333` | `cl_resolve`, `abs` = unidad no relativa a la fuente |
| `media_len_px` | tabla propia | `cl_resolve` con contexto **inicial** (§ media queries usan siempre el tamaño inicial, nunca el `font-size` de autor — por eso `rem_rebase` no toca preludios) |
| `calc_*` | tabla propia | `cl_resolve` por término |

El campo `abs_out` de `interp_fontsize_ex` deja de ser una lista blanca de
unidades escrita a mano y pasa a derivarse de `cl_unit_is_font_relative`: una
unidad nueva queda clasificada correctamente sin tocar ese sitio.
