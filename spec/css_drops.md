# `css_drops` — inventario de declaraciones que el parser descarta

> **Propósito.** Convertir "medí qué descarta el parser" (CLAUDE.md §7.4) de una
> heurística de `grep` en una **medición del motor**. El `grep` sobre `strcmp(prop, "...")`
> solo ve **nombres de propiedad**; la mitad cara de las brechas históricas fue un
> **VALOR** rechazado (`.5` sin cero inicial, un `%` en un shorthand, `pt`), que tira la
> declaración entera y no aparece en ninguna lista de nombres.

Este módulo no cambia el render. Es un **sink opcional** que el parser rellena mientras
parsea; con el sink en `NULL` el parser se comporta exactamente igual (mismo camino,
mismo resultado, mismo costo salvo un `if (log != NULL)`).

---

## 1. Alcance

**Entra:** toda declaración `prop: value` que el parser encuentra dentro de un bloque de
reglas y que **no produce ni un solo `css_decl`**. Ese es exactamente el criterio de
"descartada": `parse_one_decl` devuelve 0.

**Queda fuera (no son descartes):**
- Una declaración que emite `n >= 1` decls, aunque el layout después no use alguno.
- Custom properties (`--name: v`): no son propiedades, se recogen aparte.
- Preludios de at-rule, selectores, y bloques que el parser saltea enteros
  (`@import`, `@font-face`): no son declaraciones de una regla.

**Distingue dos causas**, porque piden arreglos distintos:

| Causa | Significado | Arreglo típico |
| :-- | :-- | :-- |
| `CSS_DROP_UNKNOWN_PROP` | El nombre no está en el dispatch de `interpret_prop`. | Implementar la propiedad. |
| `CSS_DROP_BAD_VALUE` | El nombre SÍ está; el valor no se pudo interpretar. | Ampliar la gramática del valor. |

La segunda es la peligrosa: la propiedad "existe" (aparece en cualquier inventario por
nombre) y sin embargo la declaración se pierde.

---

## 2. Contrato

```c
typedef enum css_drop_cause {
    CSS_DROP_UNKNOWN_PROP = 0,
    CSS_DROP_BAD_VALUE    = 1
} css_drop_cause;

typedef struct css_drop {
    char prop[CSS_DROP_PROP_MAX];   /* nombre lowercased, tal como se despachó */
    char val[CSS_DROP_VAL_MAX];     /* valor recortado; truncado con marca si excede */
    int  cause;                     /* css_drop_cause */
    int  count;                     /* ocurrencias coalescidas de (prop,cause) */
} css_drop;

typedef struct css_drop_log {
    css_drop *items;   /* arreglo PROPIEDAD DEL LLAMANTE; NULL desactiva el log */
    size_t    cap;     /* entradas disponibles en items */
    size_t    n;       /* entradas usadas */
    size_t    total;   /* declaraciones descartadas vistas, incl. coalescidas y desbordadas */
} css_drop_log;

css_status css_parse_logged(const char *text, size_t len, const css_media *media,
                            const char *root_scope, css_sheet **out,
                            css_drop_log *log);
```

`css_parse_scoped(text, len, media, scope, out)` es exactamente
`css_parse_logged(text, len, media, scope, out, NULL)`.

**Coalescencia.** Las entradas se agrupan por `(prop, cause)` — una hoja real repite
`-ms-flex-pack` cientos de veces y un listado sin agrupar es ilegible. `val` guarda la
**primera** ocurrencia (es la muestra representativa), `count` cuenta todas.

**Sin asignación.** El log no reserva memoria: el llamante provee `items`/`cap`. Al
llenarse, `n` deja de crecer pero `total` **sigue contando**, así que el reporte nunca
miente sobre la magnitud — dice "se descartaron N, se listan los primeros M".

**Reentrante y sin estado global.** El sink viaja por parámetro por toda la cadena
(`css_parse_logged` → `parse_block` → `interpret_decls` → `parse_one_decl`).

---

## 3. Dado-Cuando-Entonces

1. **Dado** una hoja `a{unknown-prop:1}` **cuando** se parsea con log **entonces**
   `n == 1`, `total == 1`, `items[0].prop == "unknown-prop"`,
   `cause == CSS_DROP_UNKNOWN_PROP`.
2. **Dado** `a{color:not-a-color}` **entonces** `cause == CSS_DROP_BAD_VALUE`
   (la propiedad existe, el valor no se interpreta).
3. **Dado** `a{color:red}` **entonces** `n == 0` y `total == 0` (no hay descarte).
4. **Dado** dos reglas que repiten la misma propiedad desconocida **entonces**
   `n == 1` y `items[0].count == 2` (coalescencia por `(prop,cause)`).
5. **Dado** `a{--x:1}` **entonces** `n == 0`: una custom property no es un descarte.
6. **Dado** un log con `cap == 0` (o `items == NULL`) **entonces** el parseo es
   idéntico al de `css_parse_scoped` y `total` sigue contando.
7. **Dado** un valor más largo que `CSS_DROP_VAL_MAX` **entonces** se trunca y
   termina en `"..."`, nunca desborda.
8. **Dado** el mismo texto parseado con y sin log **entonces** la hoja resultante es
   **idéntica** (el log no puede cambiar el render).

---

## 4. Superficie

`--dump-css-drops` (headless) imprime el reporte de la página cargada, ordenado por
`count` descendente:

```
CSS drops: 412 declaration(s) dropped, 23 distinct
  count cause          property                  first value
    117 unknown-prop   -ms-flex                  1 1 auto
     13 bad-value      background                url(data:...) no-repeat
```

Es diagnóstico: sale por stdout del proceso confiable, nunca al flujo de la página
(doctrina `[[freedom-canonical-length-and-invented-rules-2026-08-11]]`).

---

## 5. Seguridad

- El valor se copia **acotado** a `CSS_DROP_VAL_MAX` con truncamiento explícito; el
  texto es contenido remoto hostil y nunca se imprime como formato (`%s` sobre buffer
  terminado, jamás como cadena de formato).
- Bytes de control (`< 0x20`) se sustituyen por `.` al copiar: el reporte va a una
  terminal y una secuencia ANSI incrustada en un CSS remoto no debe poder pintarla.
- Sin asignación dinámica ⇒ sin ruta de OOM nueva en el parser.
- El log es **solo escritura** desde el parser; nada de lo que registra realimenta la
  cascada.
