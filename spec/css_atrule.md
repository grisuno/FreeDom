# css_atrule — reglas condicionales `@supports` y capas de cascada `@layer`

Módulo puro (`car_`), sin I/O ni DOM. `css.c` decide **dónde** aparece un at-rule y
llama aquí para las dos preguntas que no son de parseo: ¿se cumple esta condición
`@supports`? y ¿cuánto pesa una declaración de esta capa?

## Por qué (medido 2026-09-29)

`parse_block` solo entraba en `@media`; todo otro at-rule con bloque se saltaba
**entero**. Medido en snapshots de sitios del allowlist:

| Página | `@layer` | `@supports` | Efecto |
| :-- | --: | --: | :-- |
| github.com | 18 | 182 | Primer Brand (700 KB, toda la maqueta de la portada) vive en `@layer primer-brand{…}`: se perdía completa. |
| huggingface.co | 5 | 933 | Tailwind: utilidades envueltas en `@supports`/`@layer`. |
| wikipedia | 0 | 76 | reglas de `dvh`, `color-mix`, etc. |

## `@supports` (CSS Conditional 3 §6)

`car_supports(s, a, b, ops)` evalúa la condición `s[a,b)` (el preludio, sin la
palabra `@supports`):

```
condition = not <in-parens>
          | <in-parens> [ and <in-parens> ]*
          | <in-parens> [ or <in-parens> ]*
in-parens = ( <condition> ) | ( <prop> : <value> ) | selector( <sel> ) | <otra cosa>
```

- `( prop: value )` → `ops->decl_ok(ctx, prop, value)`: el llamador contesta con **su
  propio intérprete de propiedades**. Una propiedad o valor que el motor no implementa
  es **falso**, exactamente como en un navegador que no la soporta: el autor escribe el
  fallback para ese caso. Una custom property (`--x: …`) es verdadera.
- `selector( sel )` → `ops->selector_ok(ctx, sel)` (el llamador usa `csel_parse`).
- Toda otra forma (`font-tech()`, `font-format()`, *general-enclosed*) es **falsa**.
- Sintaxis inválida (paréntesis desbalanceados, `and` y `or` mezclados sin paréntesis,
  palabra clave desconocida) ⇒ **falso** (falla cerrado: se salta el bloque).
- Profundidad de anidamiento acotada a `CAR_MAX_DEPTH` (16); más ⇒ falso.

## `@layer` (CSS Cascade 5 §6.4)

`car_layers` registra nombres en orden de **primera aparición** (bloque
`@layer a {…}` o sentencia `@layer a, b;`). Un bloque anónimo `@layer {…}` recibe una
capa nueva cada vez. Un nombre anidado se registra con su ruta completa (`a.b`).
Rango: capa k-ésima = k (1…`CAR_MAX_LAYERS`, 256); pasado el tope, todas comparten el
último rango (acotado, nunca desborda). `0` = sin capa.

`car_effective_spec(spec, layer, important)` pliega capa y especificidad en un solo
entero comparable, porque la capa se compara **antes** que la especificidad:

- normal: `rango << 16 | spec`, con *sin capa* = `CAR_MAX_LAYERS + 1` (gana a toda capa).
- `!important`: el orden se **invierte**: `(CAR_MAX_LAYERS + 1 − rango) << 16 | spec`,
  con *sin capa* = 0 (pierde contra toda capa).
- `spec` se acota a 16 bits.

`CAR_INLINE_SPEC` = `(CAR_MAX_LAYERS + 2) << 16`: el atributo `style=` gana a todo.

## Fuera de alcance

- `@container` (depende del tamaño del contenedor, que no existe al parsear): se sigue
  saltando entero, falla cerrado.
- `@scope`, `@starting-style` (valores de *transición*: aplicarlos sería un bug),
  `@page`, `@document`: se saltan.
- Orden exacto de sub-capas: `a.b` debería quedar **debajo** de las reglas directas de
  `a`; aquí queda en su orden de primera aparición (aproximación documentada).
