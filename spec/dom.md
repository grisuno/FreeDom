# Especificación: `dom`

> Puente Hito 2 → Hito 3 — Índice DOM consultable. Estado: **VERDE (solo lectura)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_dom.c` (11 tests) pasa con
> ASan/UBSan limpio. Backend: capa de índices sobre Lexbor (Hito 2). Pendiente: mutación.

## 1. Propósito

`dom` convierte el árbol inerte de `html_parse` (Hito 2) en un **índice consultable** de nodos
**direccionables por entero**, con búsquedas O(1) por `id`/`tag`/`class` y primitivas de **orden
de documento** aptas para búsqueda binaria. Es el sustrato que el bridge JS del Hito 3 expondrá
a los scripts (DOM bindings de solo lectura) y la base sobre la que motores de UI/frameworks
(React, Astro, Qwik, etc.) operan: el navegador **no** implementa Virtual DOM, hidratación,
resumability ni islas — esos patrones se escriben en JavaScript y corren sobre esta API. Lo que
este módulo garantiza es que esa API sea **rápida**.

> **Actualización Hito 20b:** el índice ahora soporta **mutación acotada y memory-safe** para JS vivo
> (`dom_set_text_content`, `dom_set_document_title`). La invariante clave: los hijos removidos se
> **detachan** (`lxb_dom_node_remove`), **nunca** se destruyen, así que ningún handle del índice queda
> colgando (cero UAF). Agregar nodos / `setAttribute` / `innerHTML` siguen fuera de alcance.

La entrega original era **solo lectura**. La mutación (appendChild/removeChild/setAttribute con
mantenimiento incremental de índices) queda para un hito posterior.

## 2. Decisión de estructura

Capa de índices **sobre Lexbor** (no una arena propia): se reusa el parseo HTML5 tolerante ya
auditado (Hito 2: 14 tests + fuzzing) y se le añade una capa de aceleración propia. El árbol
base lo sigue poseyendo `hp_document`; `dom_index` solo guarda referencias y estructuras de
índice. Por eso **`doc` debe sobrevivir al `dom_index`**.

Tras el parseo, en una pasada en **orden de documento**, se construye:

- `nodes[]` — arena `dom_node_id (entero) -> nodo de elemento`. Cache-friendly, sin punteros
  expuestos. Los ids se asignan en orden de documento.
- `by_id` — hash `id -> dom_node_id` (O(1) `getElementById`). Coincidencia **sensible a
  mayúsculas** (HTML5).
- `by_tag` — hash `nombre-de-tag (minúsculas) -> lista de dom_node_id`.
- `by_class` — hash `clase (sensible a mayúsculas) -> lista de dom_node_id`.
- Mapa inverso `puntero-de-nodo -> dom_node_id` para resolver la navegación.

Como la pasada es en orden de documento, **cada lista de `by_tag`/`by_class` queda ordenada
ascendentemente por `dom_node_id`** ⇒ es binary-searchable (p. ej. "primer elemento de la clase
X después de la posición P" es una búsqueda binaria).

### El rol de la búsqueda binaria
Un árbol DOM no está ordenado, así que las búsquedas por clave (`id`/`tag`/`class`) usan **hash
O(1)**, no búsqueda binaria. La búsqueda binaria aplica al **orden de documento**: numerando
cada nodo con un entero monótono, "¿A va antes que B?" es una comparación de enteros y los
conjuntos de resultados (listas ordenadas) admiten búsqueda binaria por posición.

## 3. Garantías de seguridad

1. **Inerte y de solo lectura.** No ejecuta scripts ni muta el árbol; las consultas son puras
   lecturas. El saneo (strip de `<script>`/`on*`) ya lo aplicó `html_parse`.
2. **Recorrido sin recursión.** La construcción y la navegación son iterativas (punteros
   hijo/hermano/padre): el anidamiento profundo de un atacante no desborda la pila.
3. **Acotado.** El índice es lineal en el número de nodos; sin crecimiento ilimitado más allá
   del documento ya acotado por `html_parse` (`max_bytes`).
4. **Memoria.** `dom_index` tiene dueño único; `dom_free` es idempotente / seguro con `NULL`.
   No posee el árbol Lexbor (lo posee `hp_document`). Objetivo: `valgrind` y ASan/UBSan limpios.
5. **Punteros prestados.** `dom_tag_name`/`dom_get_attribute` devuelven memoria **prestada**,
   válida mientras vivan `idx` y `doc`; el llamante no la libera.

## 4. Contrato de la API

Definida en `include/dom.h`. Tipos opacos: `dom_index`. Identificador de nodo: `dom_node_id`
(entero); el centinela de "ninguno" es `DOM_NODE_NONE`.

```c
typedef uint32_t dom_node_id;
#define DOM_NODE_NONE ((dom_node_id)0xFFFFFFFFu)

dom_status dom_build(const hp_document *doc, dom_index **out);
void       dom_free(dom_index *idx);

size_t      dom_node_count(const dom_index *idx);

/* Lookups por clave. */
dom_node_id dom_get_element_by_id(const dom_index *idx, const char *id);
size_t      dom_get_by_tag(const dom_index *idx, const char *tag,
                           dom_node_id *out, size_t cap);
size_t      dom_get_by_class(const dom_index *idx, const char *cls,
                             dom_node_id *out, size_t cap);

/* Orden de documento (binary-search friendly). */
size_t      dom_document_position(const dom_index *idx, dom_node_id node);
int         dom_precedes(const dom_index *idx, dom_node_id a, dom_node_id b);
dom_node_id dom_node_at(const dom_index *idx, size_t position);

/* Navegacion (solo elementos; DOM_NODE_NONE en los limites). */
dom_node_id dom_parent(const dom_index *idx, dom_node_id node);
dom_node_id dom_first_child(const dom_index *idx, dom_node_id node);
dom_node_id dom_next_sibling(const dom_index *idx, dom_node_id node);

/* Lecturas (memoria prestada). */
const char *dom_tag_name(const dom_index *idx, dom_node_id node, size_t *len);
const char *dom_get_attribute(const dom_index *idx, dom_node_id node,
                              const char *name, size_t *len);
const char *dom_text_content(const dom_index *idx, dom_node_id node, size_t *len);
const char *dom_document_title(const dom_index *idx, size_t *len);

/* Mutación (Hito 20b — JS vivo). Memory-safe: los hijos removidos se DETACHAN
 * (lxb_dom_node_remove, nunca destroy), así un handle del índice a un nodo removido
 * sigue siendo un puntero válido (sale del árbol renderizado, no se libera). */
dom_status dom_set_text_content(dom_index *idx, dom_node_id node,
                                const char *text, size_t len);
dom_status dom_set_document_title(dom_index *idx, const char *text, size_t len);
```

`dom_get_by_tag`/`dom_get_by_class` escriben hasta `cap` ids en `out` (en orden de documento) y
devuelven el **total** de coincidencias (que puede exceder `cap`; permite dimensionar el buffer).

> Nota de contrato: en esta build de solo lectura `dom_document_position(id) == id` (los ids se
> asignan en orden de documento). El llamante **no debe** asumir esa igualdad: una build mutable
> futura podría romperla. Usa siempre `dom_document_position`/`dom_node_at`.

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `DOM_OK` | Índice construido. |
| `DOM_ERR_NULL_ARG` | `doc == NULL`, `out == NULL`, o el documento no tiene raíz. |
| `DOM_ERR_OOM` | Fallo de asignación. |
| `DOM_ERR_INTERNAL` | Estado inesperado del backend. |

Las consultas no devuelven `dom_status`: ante entrada inválida (`idx==NULL`, id fuera de rango,
clave ausente) devuelven `DOM_NODE_NONE`, `0`, o `NULL` según el tipo.

## 6. Semántica

- `dom_build`: dos pasadas iterativas. (1) cuenta elementos; (2) llena `nodes[]` en orden de
  documento, indexa `id`/`class`/`tag` y el mapa inverso. Las listas quedan ordenadas por id.
- `dom_get_element_by_id`: primera coincidencia en orden de documento (HTML5: el primero gana),
  o `DOM_NODE_NONE`.
- `dom_get_by_tag`: nombre normalizado a minúsculas. `dom_get_by_class`: token exacto
  (sensible a mayúsculas) tras dividir el atributo `class` por espacios.
- Navegación **solo de elementos**: `dom_first_child`/`dom_next_sibling` saltan nodos de texto y
  devuelven el siguiente *elemento*; `dom_parent` devuelve el elemento ancestro o
  `DOM_NODE_NONE` si el padre no es un elemento indexado (p. ej. el nodo documento).
- `dom_tag_name`/`dom_get_attribute`: punteros prestados; `dom_get_attribute` devuelve `NULL`
  si el atributo no existe.

## 7. Matriz de pruebas

`tests/test_dom.c` (cmocka), sobre un documento conocido:
- `dom_build`/`dom_free`: OK, `NULL`-safe, doble `free`.
- `dom_node_count > 0`.
- `getElementById` acierta (tag correcto), ausente ⇒ `DOM_NODE_NONE`.
- `by_class` y `by_tag` con conteos esperados; resultados en orden de documento.
- Navegación: `first_child`→`next_sibling`→… y `parent` sobre una estructura conocida.
- Orden de documento: `dom_precedes`, `dom_node_at(dom_document_position(n)) == n`.
- `dom_get_attribute` (presente/ausente) y `dom_tag_name`.
- Args inválidos ⇒ centinelas, sin crash.

## 8. Fuera de alcance

- **Mutación** del árbol e índices incrementales (hito siguiente).
- Selectores CSS completos (combinadores, pseudoclases); v1 cubre `id`/`tag`/`class`.
- Shadow DOM / encapsulación de subárboles (se define en spec aparte; encaja con Zero Trust).
- Cableado real al motor JS (la spec de las DOM bindings vive en el Hito 3).
- Layout, estilo y render (Hito 4).
