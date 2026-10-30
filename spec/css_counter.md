# spec: css_counter (`cnt_`) — contadores CSS (CSS 2.1 §12.4, Lists 3, Counter Styles 3)

## Por qué existe (medido)
`counter-reset` / `counter-increment` (6 y 5 páginas del corpus) y `content: counter()` se
descartaban: toda sección numerada ("1.", "1.1", "Figure 3") salía sin su número. La
cascada es por elemento y memoizada; un contador depende de la POSICIÓN en el documento, así
que el valor se resuelve en un pre-pase puro de `page_view`, no en la cascada.

## Contrato (puro, sin I/O, acotado)
```c
int  cnt_parse_decls(const char *val, int dflt, cnt_decl out[CNT_MAX_DECL]);
int  cnt_parse_content(const char *val, char *out, size_t cap);
int  cnt_is_marker(const char *s);
size_t cnt_format(int style, long value, char *out, size_t cap);
cnt_state *cnt_state_new(void);  void cnt_state_free(cnt_state *);
void cnt_reset(cnt_state *, int depth, const cnt_decl *, int n);
void cnt_increment(cnt_state *, int depth, const cnt_decl *, int n);
void cnt_leave(cnt_state *, int depth);
size_t cnt_resolve(const cnt_state *, const char *marker, cnt_attr_fn attr, void *ctx,
                   char *out, size_t cap);
```

## Reglas (Dado-Cuando-Entonces)
- **Lista de contadores.** Dado `a 2 b` con `dflt`=0 (reset) o 1 (increment), cuando se parsea,
  entonces `a=2`, `b=dflt`; `none` es válida y vacía (reclama el slot); un identificador
  inválido, uno de `none/inherit/initial/unset/revert` como nombre, un entero fuera de rango o
  más de `CNT_MAX_DECL` (4) entradas ⇒ `-1` (falla cerrado).
- **Contenido.** Dado un valor con `counter()`/`counters()` (más cadenas, `attr()`,
  `open-quote`/`close-quote`), cuando se parsea, entonces se escribe un marcador
  `\x01seq:` + ítems; sin ningún contador devuelve 0 ("no es mío", sigue el camino viejo);
  malformado o más largo que `cap` ⇒ `-1`.
- **Alcance (CSS 2.1 §12.4.1).** Un `counter-reset` en un elemento a profundidad `d` crea una
  instancia visible para él, sus descendientes, sus hermanos siguientes y sus descendientes,
  hasta que sale el PADRE (`cnt_leave(d)`); si un hermano previo ya la creó a esa profundidad
  la REEMPLAZA (no anida) — `ol li` de listas hermanas.
- **Incremento.** Sin instancia visible se crea una con valor 0 antes de sumar.
- `counter(n)` = valor de la instancia más interna (0 si no hay); `counters(n, sep)` = todos
  los valores de las instancias de `n`, de la más externa a la más interna, unidos por `sep`.
- **Estilos.** decimal, decimal-leading-zero, lower/upper-roman, lower/upper-alpha|latin,
  lower-greek, disc, circle, square, none. Un nombre desconocido ⇒ decimal (Counter Styles §7.1);
  romanos fuera de 1..3999 y alfabéticos ≤ 0 caen a decimal.
- **Cotas anti-DoS.** `CNT_MAX_INSTANCES` 1024 vivas (las nuevas se ignoran, nunca desborda),
  nombre ≤ 63 bytes, enteros acotados a ±1e9, salida siempre acotada y NUL-terminada.

## Fuera de alcance
`counter-set`, contadores con `list-item` implícito, estilos CJK/árabe-índico, `symbols()`,
`@counter-style`.
