# `block_flow` (`bf_`) — flujo de bloques: colapso de márgenes verticales

> Módulo **puro**, sin I/O, sin asignación. Implementa las reglas de CSS 2.1 §8.3.1
> que gobiernan el espacio vertical entre cajas de bloque adyacentes.

## 1. Por qué existe

El espacio entre dos bloques hermanos **no es la suma de sus márgenes ni el mayor de
los dos**: los márgenes adyacentes *colapsan* en uno solo, y la regla normativa
(CSS 2.1 §8.3.1) es

> "the resulting margin width is the maximum of the adjoining margin widths. In the
> case of negative margins, the maximum of the absolute values of the negative
> adjoining margins is deducted from the maximum of the positive adjoining margins."

Es decir: **`max(0, positivos) + min(0, negativos)`**, no `max(a, b)`.

El motor traía `(a > b) ? a : b` escrito a mano en tres sitios de
`gui/browser_ui.c`. Con dos márgenes positivos coincide con la spec por accidente;
con cualquier margen negativo da el resultado equivocado, y `margin-top:-1px`
(solapar bordes de celdas/tarjetas) es idioma corriente. Además la regla estaba
duplicada, así que arreglarla en un sitio no arreglaba los otros.

Un segundo defecto no era de la fórmula sino de **dónde** se aplicaba: el gap se
insertaba solo si el documento ya había emitido una **fila de texto**
(`L->nrow > 0`), de modo que una página cuyo contenido son cajas decoradas sin texto
—un separador, un spacer, un contenedor de ícono, una tarjeta vacía— nunca cobraba
ningún margen. Tres `<div>` de 20 px con `margin-bottom:30px` salían en 0/20/40
contra **0/50/100** de Firefox (medido). Eso es política del llamante, no de este
módulo, pero es el motivo por el que el módulo se extrajo: la regla se vuelve
citable y testeable en aislamiento.

## 2. Contrato

### `double bf_collapse(double a, double b)`

**Dado** dos márgenes adyacentes `a` y `b` en px (el `margin-bottom` usado del
bloque anterior y el `margin-top` usado del siguiente),
**cuando** se pide el espacio que los separa,
**entonces** devuelve `max(0,a,b) + min(0,a,b)`.

| `a` | `b` | resultado | regla |
| --: | --: | --------: | :---- |
| 30 | 0 | 30 | el mayor positivo |
| 30 | 40 | 40 | el mayor positivo |
| 25 | 25 | 25 | colapsan a uno, no se suman |
| 0 | 0 | 0 | — |
| -10 | 0 | -10 | el único negativo se deduce de un positivo 0 |
| 30 | -10 | 20 | `max(0,30) + min(0,-10)` |
| -10 | -30 | -30 | el más negativo gana |
| 30 | NaN | 30 | entrada no finita se ignora (fail-closed) |

Entradas no finitas (`NaN`, `±inf`) se tratan como **ausentes** (0), no se propagan:
un valor no finito viene de una división por cero en `calc()` de contenido hostil y
propagarlo envenenaría toda la geometría de la página aguas abajo.

### `double bf_collapse_n(const double *m, size_t n)`

La misma regla sobre un conjunto de márgenes que colapsan **todos juntos** (CSS 2.1
§8.3.1: los márgenes de una cadena de cajas vacías, o el margen de un bloque con el
de su primer/último hijo cuando no hay borde ni padding entre ellos). `n == 0` o
`m == NULL` ⇒ `0.0`. Es asociativa y consistente con `bf_collapse`:
`bf_collapse_n({a,b}, 2) == bf_collapse(a, b)`.

### `int bf_margins_adjoin(double border_px, double padding_px)`

**Dado** el borde y el padding que separan dos márgenes en el eje vertical,
**cuando** ambos son cero,
**entonces** los márgenes son *adjoining* y colapsan (devuelve 1); si alguno es
distinto de cero, no colapsan (devuelve 0). Un valor no finito se trata como
presente (fail-closed: no colapsa), porque colapsar de más funde dos bloques en uno
y hace desaparecer espacio que el autor pidió.

## 3. Fuera de alcance (v1)

- **Colapso a través del padre** (margen del primer hijo con el del padre) y
  *self-collapsing boxes*: el motor los resuelve en el llamante, que es quien conoce
  el árbol; este módulo solo provee la aritmética con `bf_margins_adjoin`.
- Márgenes **horizontales**: no colapsan nunca (CSS 2.1 §8.3), no hay nada que
  calcular.
- Contextos de formato que **suprimen** el colapso (flotantes, `overflow` distinto de
  `visible`, absolutos, ítems flex/grid, celdas de tabla): la decisión es del
  llamante; este módulo no conoce el árbol.

## 4. Seguridad

Puro, total, sin asignación, sin bucles no acotados (`bf_collapse_n` recorre `n`
elementos y nada más). No hay entrada que pueda hacerlo fallar: todo `double` tiene
respuesta definida, y los no finitos se neutralizan en la entrada. No hay estado
global, es reentrante.
