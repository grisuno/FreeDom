# spec/textfield.md — Campo de texto editable, puro

> Módulo `textfield` (prefijo `tf_`). Lógica **pura, sin I/O, sin estado global**: un buffer de
> texto de una sola línea con cursor, editable byte a byte. No pinta nada ni lee el teclado; solo
> mantiene el estado de edición de forma determinista y acotada. Metodología: SDD + TDD.

## 0. Por qué existe

La GUI necesita varios campos editables: el User-Agent configurable en el menú de opciones y, más
adelante, las cajas de texto de los formularios HTML (`<input>`/`<textarea>`). La barra de URL ya
tiene su propia edición dentro de `browser_state`, pero acoplada a ese struct. `textfield` extrae la
mecánica de edición (insertar, borrar, mover el cursor) a una primitiva pura, reentrante y testeable
sin Cairo ni Wayland, que la GUI reutiliza para cada caja. El orquestador (`browser_ui.c`) solo
cablea el teclado a estas funciones y pinta el contenido.

Es lógica directamente auditable: el contenido es dato del usuario, el buffer es de capacidad fija y
toda operación respeta sus límites (falla cerrado: nunca escribe fuera del buffer ni parte un punto
de inserción válido).

## 1. Tipos

```c
#define TF_CAP 1024u   /* capacidad fija del buffer, incluido el NUL final */

typedef struct tf_field {
    char   buf[TF_CAP]; /* contenido, siempre NUL-terminado en [len] */
    size_t len;         /* bytes usados, excluido el NUL; len < TF_CAP */
    size_t cursor;      /* posición de inserción en bytes, 0..len */
} tf_field;

typedef enum tf_status {
    TF_OK = 0,
    TF_ERR_NULL_ARG, /* puntero requerido era NULL */
    TF_ERR_FULL      /* la operación no cabe en el buffer (falla cerrado, no trunca a medias) */
} tf_status;
```

El struct es de tamaño fijo: el llamante lo declara en pila o lo embebe en su propio estado. No hay
asignación dinámica y no hay liberador (zero-init con `tf_init` o `{0}` es válido).

## 2. API (pura, reentrante)

```c
void        tf_init(tf_field *f);                 /* deja el campo vacío, cursor en 0 */
tf_status   tf_set(tf_field *f, const char *s);   /* reemplaza el contenido; cursor al final */
void        tf_clear(tf_field *f);                /* vacía; equivalente a tf_init salvo NULL-safe */

tf_status   tf_insert(tf_field *f, char c);       /* inserta un byte en el cursor; cursor avanza 1 */
void        tf_backspace(tf_field *f);            /* borra el byte previo al cursor */
void        tf_delete(tf_field *f);               /* borra el byte en el cursor */
void        tf_move(tf_field *f, long delta);     /* mueve el cursor (acotado a 0..len) */
void        tf_home(tf_field *f);                 /* cursor a 0 */
void        tf_end(tf_field *f);                  /* cursor a len */

const char *tf_text(const tf_field *f);           /* contenido NUL-terminado; "" si f es NULL */
size_t      tf_len(const tf_field *f);            /* bytes usados; 0 si f es NULL */
size_t      tf_cursor(const tf_field *f);         /* posición del cursor; 0 si f es NULL */
```

### Reglas

- `f == NULL`: las funciones que devuelven `tf_status` retornan `TF_ERR_NULL_ARG`; las `void` son
  no-ops; los lectores devuelven el valor neutro (`""`/`0`).
- `tf_set`: `s == NULL` → `TF_ERR_NULL_ARG`. Si `strlen(s) >= TF_CAP` → `TF_ERR_FULL` y el campo
  **no se modifica** (no se trunca el contenido a la mitad de una operación). En éxito, `len` y el
  cursor quedan al final del nuevo contenido.
- `tf_insert`: inserta el byte en `cursor`, desplazando la cola a la derecha. Si `len + 1 >= TF_CAP`
  (no cabe junto al NUL) → `TF_ERR_FULL` y el campo no cambia. El byte se inserta tal cual (la GUI
  envía los bytes UTF-8 uno a uno, igual que la barra de URL); el módulo no interpreta ni valida
  UTF-8 (eso es responsabilidad del que pinta, que sanea a UTF-8 válido).
- `tf_backspace`: si `cursor > 0`, borra el byte en `cursor-1` y retrocede el cursor; si `cursor == 0`
  es no-op.
- `tf_delete`: si `cursor < len`, borra el byte en `cursor` (el cursor no se mueve); si no, no-op.
- `tf_move`: suma `delta` al cursor con saturación a `[0, len]` (sin desbordamiento de `size_t`).
- El invariante `cursor <= len < TF_CAP` y `buf[len] == '\0'` se mantiene tras toda operación.

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; el contenido es dato del usuario.
- **Falla cerrado:** una operación que no cabe se rechaza entera (`TF_ERR_FULL`); nunca un escritura
  fuera de límites ni un buffer a medio modificar.
- **Sin asignación dinámica:** buffer de capacidad fija; sin dueño que liberar.
- **Determinista:** misma secuencia de operaciones → mismo estado (testeable, agent-friendly).
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 4. Tabla de estados

| `tf_status` | Condición |
| :-- | :-- |
| `TF_OK` | La operación se aplicó. |
| `TF_ERR_NULL_ARG` | Un puntero requerido era `NULL`. |
| `TF_ERR_FULL` | El contenido no cabe en `TF_CAP`; el campo queda intacto. |

## 5. Fuera de alcance

- Selección de texto, portapapeles, deshacer/rehacer, multilínea.
- Conocimiento de límites de carácter UTF-8 (mover/borrar por glifo): se opera por bytes; quien
  pinta sanea a UTF-8 válido. La navegación por palabras y el saneo visual viven en la GUI.
- El pintado del campo y del cursor, y el enrutado del teclado: los hace `browser_ui.c`.
