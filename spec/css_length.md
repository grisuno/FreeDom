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

---

## 7. `<length-percentage>` — el tipo, no el caso especial (2026-08-12)

### 7.1 Por qué

Hasta esta tanda el motor sabía resolver `<length>` y **descartaba `%` entero**.
La única excepción era `width`/`max-width`, que tenían un canal paralelo propio
(`css_style.width_pct`, per-mille, resuelto por `bx_width_cap`). Ese canal es
correcto en lo que hace y **equivocado como arquitectura**: un porcentaje no es
una propiedad de `width`, es un **valor de tipo `<length-percentage>`** (CSS
Values 4 §5.3) que aparece en `margin`, `padding`, `width`, `height`, `inset`,
`text-indent`, `flex-basis`, `background-position`, `translate()` y `border-radius`.
Escribir un canal ad-hoc por propiedad es exactamente la clase de regla inventada
que este motor no debe tener; y mientras tanto `padding: 2% 5%` tiraba **el
shorthand completo** porque `expand_box4` falla cerrado ante un token que no
entiende.

La respuesta es la misma que la de la tanda 15 con `<length>`: **un solo tipo,
un solo resolvedor, y el contexto que el módulo no puede saber entra por
parámetro** — acá el *basis* (la dimensión del bloque contenedor), que sólo se
conoce en layout.

### 7.2 Representación

```c
typedef struct cl_lp {
    double px;       /* componente absoluta ya resuelta a px          */
    double pct;      /* componente porcentual, en PORCENTAJE (50% -> 50.0) */
    int    has_pct;  /* 1 si el valor lleva componente porcentual      */
} cl_lp;
```

Las dos componentes **coexisten**: `calc(100% - 10px)` es `{px:-10, pct:100}`.
Ésa es la razón de que no sea un `union` ni un enum de "o px o %": CSS Values 4
§10.3 define la suma como un único valor computado.

`cl_lp_used(lp, basis)` = `lp.px + lp.pct/100 * basis`. Es la totalidad de la
regla; no hay ninguna otra aritmética de porcentajes en el motor.

### 7.3 Contra qué se resuelve cada propiedad (el *basis*)

Esto **no** es una convención de Freedom: es la tabla normativa.

| Propiedad | Basis | Fuente |
| :-- | :-- | :-- |
| `margin-*` (las **cuatro** caras) | **ancho** del bloque contenedor | CSS 2.1 §8.3 |
| `padding-*` (las **cuatro** caras) | **ancho** del bloque contenedor | CSS 2.1 §8.4 |
| `width`, `min-width`, `max-width` | ancho del bloque contenedor | §10.2, §10.4 |
| `left`, `right` | ancho del bloque contenedor | §9.3.2 |
| `text-indent` | ancho del bloque contenedor | §16.1 |
| `height`, `min-height`, `max-height` | **alto** del bloque contenedor, **si es definido**; si el alto contenedor depende del contenido ⇒ el valor computa a `auto` | §10.5, §10.7 |
| `top`, `bottom` | alto del bloque contenedor (misma cláusula de definitud) | §9.3.2 |
| `flex-basis` | tamaño del eje principal del contenedor | Flexbox §7.2.3 |

Que `padding-top: 2%` se resuelva contra el **ancho** es contraintuitivo y es
justo lo que hace que un padding porcentual produzca cajas de proporción
constante. Es la regla más citada de esta tabla y la que la sonda `pct-box`
mide.

### 7.4 Dónde se resuelve

El parser **no puede** resolverlo: no conoce el bloque contenedor. Así que el
porcentaje viaja **simbólico** desde la cascada hasta el layout:

```
css.c (parse)      -> css_style.pct[CSS_PCT_*]  (per-mille: 50% -> 500)
page_view (worker) -> pv_box_def / pv_run       (mismo per-mille)
tab.c   (códec)    -> write_view / read_view
painter (layout)   -> bx_lp_px(px, pct_pm, basis)   <- ÚNICO punto de resolución
```

El canal per-mille (entero) y no `double` porque **todo el códec IPC es entero**
y porque un décimo de porcentaje es la resolución que cualquier hoja real usa
(`33.333%` -> 333). El clamp es `[-CSS_PCT_MAX, CSS_PCT_MAX]`, saturando, con el
mismo criterio que `CSS_LEN_MAX`: la política anti-DoS es del emisor.

`CSS_PCT_UNSET` (0 no sirve: `margin: 0%` es un valor legítimo) es el centinela
de "sin componente porcentual".

### 7.5 Contrato — Dado / Cuando / Entonces

| # | Dado (valor) | Entonces (`cl_resolve_lp`) |
| :-- | :-- | :-- |
| 1 | `"10px"` | `CL_OK`, `{px:10, pct:0, has_pct:0}` |
| 2 | `"50%"` | `CL_OK`, `{px:0, pct:50, has_pct:1}` |
| 3 | `"0"` | `CL_OK`, `{px:0, pct:0, has_pct:0}` |
| 4 | `"-25%"` | `CL_OK`, `{px:0, pct:-25, has_pct:1}` (el signo lo filtra el emisor: `padding` lo rechaza, `margin` no) |
| 5 | `".5%"` | `CL_OK`, `pct` = 0.5 — misma gramática `<number>` que el resto (`cl_number`) |
| 6 | `"2 %"` | `CL_ERR_SYNTAX`: un `<percentage>` es **un** token, igual que un `<dimension>` |
| 7 | `"50%x"` | `CL_ERR_SYNTAX` |
| 8 | `"1e400%"` | `CL_ERR_RANGE` |
| 9 | `NULL` | `CL_ERR_NULL_ARG` |

| # | Dado (`cl_lp_used`) | Entonces |
| :-- | :-- | :-- |
| 10 | `{px:10,pct:0}`, basis 200 | 10 |
| 11 | `{px:0,pct:50,has_pct:1}`, basis 200 | 100 |
| 12 | `{px:-10,pct:100,has_pct:1}`, basis 200 | 190 (`calc(100% - 10px)`) |
| 13 | basis negativo o no finito | se trata como 0: la componente porcentual aporta 0, la absoluta sobrevive |

**Garantía transversal:** `cl_resolve` sigue rechazando `%` con `CL_ERR_UNIT`
(no cambia su contrato — hay sitios donde un porcentaje efectivamente no es
válido, y ahí debe seguir fallando cerrado). `cl_resolve_lp` es un
**superconjunto** explícito que el llamador pide cuando la propiedad acepta el
tipo `<length-percentage>`.

---

## 8. La componente relativa a la fuente — `em` mide contra el elemento (2026-08-12)

### 8.1 Por qué

`cl_ctx` siempre tuvo un campo `font_size`, pero **nadie se lo llenaba**: la
cascada resolvía cada `<length>` con `cl_ctx_initial()`, es decir con
`CL_INITIAL_FONT_SIZE` (16 px) clavado. Comentario textual que había en
`css_len_ctx()`:

> The cascade is pure and element-free: it runs before any element is known, so
> it cannot see a computed font-size and must use the CSS initial context.

Consecuencia medida: **toda** unidad relativa a la fuente valía lo mismo en toda
la página, sin importar el `font-size` del elemento. Sonda de 10 líneas contra
Firefox 140 (`width:10em` bajo `font-size:32px` y bajo `font-size:8px`):

| | Firefox | Freedom (antes) |
| :-- | --: | --: |
| `10em` con `font-size:32px` | **320 px** | 160 px |
| `10em` con `font-size:8px`  | **80 px**  | 160 px |
| `height:2em` con `font-size:32px` | **64 px** | 32 px |

No es un caso de borde: en el corpus de paridad hay **905 declaraciones** con una
unidad relativa a la fuente (879 sueltas, 26 dentro de `calc()`, **0** dentro de
`min()`/`max()`/`clamp()`), y las propiedades que más la usan son justamente las
que mueven la maqueta: `margin` (349 contando longhands), `padding` (213),
`height` (59), `line-height` (41), `top`/`right` (48).

Es además exactamente el tipo de constante que la doctrina prohíbe: un `16.0`
enterrado decidiendo el tamaño de cajas que el autor escribió en `em`.

### 8.2 Representación — el valor es `a + b·font-size`

Una longitud relativa a la fuente **no es un número**: es una función afín del
`font-size` computado del elemento. `cl_lp` gana esa segunda componente:

```c
typedef struct cl_lp {
    double px;       /* valor resuelto EN EL ctx dado (ya incluye b*ctx->font_size) */
    double em;       /* d(px)/d(font_size): px ganados por cada px de font-size */
    double pct;      /* componente porcentual (50% -> 50.0) */
    int    has_pct;
} cl_lp;
```

Las tres componentes **coexisten** (igual que en §7.2): `calc(100% - 2em + 4px)`
es un solo valor computado con `pct=100`, `em=-2` y una parte absoluta.

`px` se guarda **ya evaluado en el contexto de parseo** (16 px), no como la parte
puramente absoluta. Eso hace que la corrección sea un término que **vale cero por
construcción** cuando el elemento está en el tamaño inicial:

```
used(font_size) = px + em * (font_size - ctx->font_size)
```

Esa es la única aritmética; vive en `cl_em_refit()` y en ningún otro lado. La
propiedad que compra: una página cuyos elementos están todos a 16 px sale
**byte-idéntica** a la de antes del cambio, así que cualquier movimiento en
`layout-diff` está acotado, por demostración, a elementos con otro `font-size`.

### 8.3 De dónde sale el coeficiente

`b` **no** se escribe a mano por unidad: sale de la MISMA tabla de
`cl_unit_scale`, preguntándole el factor con un `cl_ctx` cuyo `font_size` es
`1.0` y cuyas métricas de fuente están en cero. Así `em`→1, `ex`→0.5, `ch`→0.5,
`cap`→0.7, `ic`→1.0, `lh`→`CL_NORMAL_LINE_RATIO`, y una unidad nueva que se
agregue a §6.1 obtiene su coeficiente sola, sin tocar este código.

`rem`/`rlh` tienen coeficiente **0**: miden contra la raíz, así que desde
cualquier elemento no-raíz son absolutas. Es la distinción que
`cl_unit_is_font_relative()` ya expresaba.

**Límite honesto:** si algún día `text_shape` llena métricas reales
(`x_height`, `zero_advance`, …), esas métricas son px absolutos medidos a UN
tamaño de fuente, y entonces `ex`/`ch`/`cap`/`ic` dejan de ser proporcionales al
`font-size`. Mientras las métricas vengan sin medir (hoy, siempre), los
fallbacks de §6.1 **son ratios del `font-size`** y la relación es exacta. Cuando
se midan de verdad, el llamador deberá re-medirlas al tamaño del elemento —
que es lo que un motor hace igual.

### 8.4 `calc()`

`calc_val` lleva la derivada junto al valor: `+`/`-` la suman componente a
componente, `*`/`/` por un escalar la escalan. Con eso `calc(2em + 10px)` es
exacto a cualquier `font-size`.

`min()`/`max()`/`clamp()` son **lineales a trozos**, no afines: cuál operando
gana depende del `font-size`, así que la derivada del resultado no es una
constante. Falla cerrado: si algún operando tiene componente relativa a la
fuente, el resultado se queda con la derivada **0**, o sea con el valor resuelto
al contexto inicial — el comportamiento anterior, sin inventar una pendiente que
no existe. En el corpus de paridad esto no afecta ninguna declaración (0 casos).

### 8.5 Dónde se dobla (un solo sitio)

Igual que un porcentaje se vuelve píxeles solo en `bx_lp_px`, una longitud
relativa a la fuente se dobla solo **al cerrar la cascada del elemento**, en
`css_resolve_el`:

1. La cascada corre como siempre y, además del ganador por slot
   (`wi`/`ws`/`wo`), registra su `ival` y su coeficiente (`wv`/`wem`).
2. Con la cascada cerrada se conoce el `font-size` **computado del elemento**:
   `font_scale`/`font_abs` aplicados sobre el heredado, que llega como
   `css_element.font_size` (el del PADRE — el modelo de CSS: primero se computa
   `font-size`, después todo lo demás).
3. Para cada slot con coeficiente distinto de cero se re-aplica el ganador con
   el valor corregido. Se re-aplica por `apply_decl`, con la misma especificidad
   y orden del ganador (el test de la cascada es `ord >= wo[slot]`, así que
   gana), **no** con un `switch` de slot→campo paralelo: un segundo mapeo sería
   conocimiento duplicado que se desincroniza al agregar una propiedad.

Nada de esto cruza el códec IPC: el `font-size` se conoce del lado de
`page_view`, así que lo que sale hacia layout ya son píxeles.

### 8.6 Contrato — Dado / Cuando / Entonces

- **Dado** `font-size: 32px` y `width: 10em`,
  **cuando** se resuelve el elemento,
  **entonces** `width` es 320 px (Firefox: 320 px).
- **Dado** `font-size: 8px` y el MISMO `width: 10em`,
  **entonces** `width` es 80 px — el mismo texto CSS, distinto valor usado.
- **Dado** un elemento sin `font-size` propio,
  **entonces** hereda el del padre y sus `em` miden contra ese.
- **Dado** `font-size: 2em` sobre un padre de 20 px,
  **entonces** el elemento computa 40 px y sus **propias** `em` miden contra 40,
  no contra 20 (CSS Values 4 §6.1.1: `em` es el `font-size` del PROPIO elemento;
  solo dentro de `font-size` significa el del padre).
- **Dado** `rem` en cualquier elemento,
  **entonces** el valor no cambia con el `font-size` del elemento (mide contra la
  raíz).
- **Dado** `calc(2em + 10px)` con `font-size: 20px`,
  **entonces** 50 px.
- **Dado** `min(10em, 100px)`,
  **entonces** se resuelve al contexto inicial (falla cerrado, §8.4).
- **Dado** un elemento cuyo `font-size` computado es 16 px,
  **entonces** todo valor sale **idéntico** al de antes de este cambio.
