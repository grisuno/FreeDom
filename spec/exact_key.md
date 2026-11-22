# spec: exact_key (`ek_`) — clave de caché exacta construida por observación

## Por qué existe (medido, tanda 95)

La ventana re-maquetaba la página ENTERA en cada cuadro: scroll, animación, hover, parpadeo del
cursor, spinner. `tools/guiscroll.py` en la ventana real: `layout_doc` + `position_doc` cuestan
**27 ms por cuadro en GitHub y 19 ms en Wikipedia**, aunque nada de lo que el layout lee cambió.
Retener el layout exige una clave que sea **todas** sus entradas (doctrina `sheet_cache`): una
invalidación manual ("borrar la caché donde cambia X") olvida siempre un sitio. La clave se
construye en cada cuadro **leyendo** el estado del que depende el layout y se compara byte a byte
con la del layout retenido.

## Contrato

```c
typedef struct ek_key { unsigned char *b; size_t n, cap; int bad; } ek_key;

void ek_init(ek_key *k);                               /* vacía, sin memoria */
void ek_reset(ek_key *k);                              /* n = 0, bad = 0; conserva la memoria */
void ek_put(ek_key *k, const void *p, size_t len);     /* añade len bytes */
int  ek_equal(const ek_key *a, const ek_key *b);       /* 1 si son la MISMA secuencia de bytes */
void ek_swap(ek_key *a, ek_key *b);                    /* intercambia contenidos (sin copiar) */
void ek_free(ek_key *k);                               /* NULL-safe, idempotente */
```

- La clave es la concatenación, en orden, de todo lo añadido. Dos claves son iguales si y solo
  si tienen la misma longitud y los mismos bytes.
- **Fail-closed:** si una reserva falla, si `len` desborda el tamaño o si la clave superaría
  `EK_MAX_BYTES` (1 MiB), la clave queda marcada `bad` y **nunca** es igual a otra (ni a sí
  misma): el llamador recalcula, como sin caché. `ek_put(k, NULL, len > 0)` también la marca.
- Crece por duplicación acotada (la clave de un cuadro mide cientos de bytes; el tope es
  anti-DoS: una página con cientos de miles de imágenes no hace crecer la memoria sin fin).
- Sin estado global. Un dueño, un liberador idempotente.

## Uso: la caché de layout de la ventana

`paint_structured` construye la clave del cuadro (`layout_key_build`) con: el documento (puntero
y un serial que avanza cada vez que `w->doc` se reasigna, para que un documento nuevo en la
misma dirección no acierte), ancho de contenido y alto de viewport, el `ui_theme` entero (solo
`double`: sin relleno), `zoom_pct`, `force_theme`, `reader`, `caps`, la generación del registro
de webfonts (`tsh_webfont_generation`), y por cada imagen, fondo y control su estado
(diferida, decodificada, tamaño natural; marcado, foco, longitud del valor). Si es igual a la del
layout retenido, el cuadro pinta ese layout; si no, maqueta y retiene el nuevo.

El pintor muta dos cosas del layout durante el cuadro (`canvas_done` y el desplazamiento de
`position: sticky`); ambas se deshacen al terminar el cuadro, así que el layout retenido es
siempre el que produjo la maquetación.

`FREEDOM_LAYOUT_CACHE_CHECK=1` es el oráculo diferencial: en cada acierto vuelve a maquetar y
compara la geometría completa (filas, fragmentos con su texto, cajas, cajas posicionadas, alto
total) y aborta ante la primera diferencia, nombrándola.

## Dado-Cuando-Entonces

- **Dado** dos claves con los mismos `ek_put` **entonces** `ek_equal` = 1.
- **Dado** que difieren en un byte, en la longitud, o en cómo se partió el mismo flujo en dos
  claves distintas con la misma concatenación **entonces** igualdad por bytes (la partición no
  importa) y 0 si un byte o la longitud difieren.
- **Dado** una clave `bad` **entonces** `ek_equal` = 0 incluso consigo misma.
- **Dado** `ek_reset` **entonces** la clave vuelve a estar vacía y sana.
- **Dado** más de `EK_MAX_BYTES` **entonces** `bad`.
- **Dado** `ek_swap` **entonces** los contenidos se intercambian sin copia.
- **Dado** `NULL` **entonces** no-op / 0.

## Fuera de alcance

Hash o resumen de la clave (se compara entera: un acierto falso sería un render incorrecto), y
retener más de un layout.
