# spec: css_nest (`cn_`) — CSS Nesting por desugaring (CSS Nesting Module 1)

## Por qué existe (medido)
ArchWiki (MediaWiki) escribe `div.related{float:right;width:25%; & > p{background:#333;…}}`
y el parser plano cortaba la regla en el primer `}`: la cabecera oscura de «Related articles»
desaparecía y la caja salía aplastada. Nesting es Baseline desde 2023 (Firefox 117) y lo usan
cada vez más hojas de design systems. Se resuelve **antes** del parser, en texto: el parser,
la cascada, el índice de selectores y el gate de `@media` no cambian.

## Contrato (puro, sin I/O, acotado)
```c
int cn_has_nesting(const char *css, size_t len);
cn_status cn_flatten(const char *css, size_t len, char **out, size_t *out_len);
```
- `cn_has_nesting`: 1 si algún bloque de regla de estilo contiene un bloque anidado (regla o
  at-rule condicional). Lineal, sin asignar. 0 ⇒ el llamador usa el texto tal cual (camino
  por defecto byte-idéntico).
- `cn_flatten`: devuelve un texto **sin anidamiento** que el parser plano entiende, en
  memoria nueva (`free()` del llamador). `CN_OK`, `CN_ERR_ARG`, `CN_ERR_OOM`.
- La entrada llega SIN comentarios (`strip_comments` corre antes); igual se respetan
  cadenas `"…"`/`'…'` y escapes `\x`, así una llave dentro de una cadena nunca abre bloque.

## Reglas (Dado-Cuando-Entonces)
- **Declaraciones y reglas anidadas.** Dado `P{d1; S{d2} d3}`, cuando se aplana, entonces sale
  `P{d1;d3}` y luego la regla anidada con su selector resuelto. Un ítem del cuerpo es regla
  anidada si contiene `{` antes de `;` en profundidad 0 y no empieza por `--` (una custom
  property puede contener llaves).
- **`&`.** Cada `&` del selector hijo se sustituye por el selector padre (`& > p`, `&.x`,
  `.dark &`). Un selector hijo sin `&` es descendiente: `P S` (también `> p` ⇒ `P > p`).
- **Listas.** Padre `a, b` e hijo `x, y` ⇒ producto cruzado `a x, a y, b x, b y`
  (no hay `:is()` complejo en el motor). Más de `CN_MAX_SELECTORS` (64) ⇒ la regla anidada
  se descarta (fail closed: nunca un selector truncado que matchee de más).
- **At-rules anidadas.** `@media`/`@supports`/`@container`/`@layer`/`@scope` dentro de una
  regla de estilo se sacan afuera envolviendo al padre: `P{@media q{d}}` ⇒
  `@media q{P{d}}`; su cuerpo se aplana con el mismo padre (anidamiento recursivo).
- **At-rules de primer nivel.** Las condicionales (`@media`, `@supports`, `@container`,
  `@layer` con bloque, `@scope`, `@document`) se recorren; el resto (`@font-face`,
  `@keyframes`, `@page`, `@property`, `@counter-style`, `@font-feature-values`) se copia
  textual: los `0%{…}` de un `@keyframes` no son anidamiento.
- **Texto hostil (hallado por `fuzz-cnest`).** Una llave domina siempre (`}` dentro de un `[`
  sin cerrar igual cierra el ítem), `;` no corta dentro de `(…)`/`[…]`. Un selector, preludio
  o declaración que contiene una *bad string* (cortada por salto de línea o por el EOF), un
  byte NUL o termina en una barra invertida sin par se DESCARTA: re-emitida, la cadena se
  volvería buena (o el escape se comería la llave de cierre) y cambiaría lo que ve el parser.
  Un trim nunca quita un blanco escapado. El detector usa el MISMO escáner de ítems que el
  aplanador (dos escáneres escritos a mano discrepaban).
- **Cotas anti-DoS.** Profundidad ≤ `CN_MAX_DEPTH` (8): más profundo se descarta. Salida ≤
  `CN_MAX_OUT_FACTOR` (8) × entrada + 64 KiB: al tope, el resto anidado se descarta y lo ya
  emitido queda (fail closed). Texto no balanceado: el bloque abierto se cierra en el EOF
  como hace el parser plano.

## Fuzzing
`make fuzz-cnest [T=s]`: sin lectura fuera de la entrada (no terminada en NUL a propósito),
salida dentro de la cota y terminada en NUL; oráculo estructural (la salida no tiene
anidamiento) para entradas sin comillas ni barras invertidas.

## Fuera de alcance
Especificidad exacta de `:is(P)` (se usa la del selector sustituido textualmente: igual en el
caso común de un padre simple), reglas de declaraciones anidadas intercaladas
(`CSSNestedDeclarations`: las declaraciones posteriores a una regla anidada se emiten con las
primeras, antes de las reglas hijas), `&` dentro de `:is()/:not()` del padre con listas.
