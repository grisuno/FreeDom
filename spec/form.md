# spec/form.md — Construcción pura de envíos de formulario

> Módulo `form` (prefijo `fm_`). Lógica **pura, sin I/O, sin estado global**: a partir de la URL de
> la página, la `action` cruda de un `<form>`, el método y la lista de controles con valor, decide
> **qué petición** representa un envío: navegar (GET), enviar un cuerpo (POST) o bloquear. No abre
> sockets; solo construye el plan, que el orquestador ejecuta por `secure_fetch`. Metodología: SDD + TDD.

## 0. Por qué existe

Para usar un buscador hay que enviar un formulario: serializar los campos como
`application/x-www-form-urlencoded` y, según el método, anexarlos a la URL (GET) o mandarlos como
cuerpo (POST). Esa serialización y la resolución segura del destino son lógica pura, auditable sin
red. El contenido (nombres, valores, `action`) es **dato hostil con procedencia**: el módulo lo
codifica y resuelve, nunca lo ejecuta. Falla cerrado: si el destino resuelto no es `https`, el envío
no es representable (`FM_BLOCKED`), igual que el resto de la doctrina Secure by Default.

Reusa el conocimiento canónico de URLs (`url_resolve_https`/`url_validate_https`/`url_is_https`): la
regla de "qué es un destino https válido" vive en un único sitio probado (DRY, Zero Trust: el destino
se revalida, además, al cargar).

## 1. Tipos

```c
#define FM_URL_MAX     URL_MAX_LEN   /* 2048; cota de la URL resultante */
#define FM_BODY_MAX    4096u         /* cota del cuerpo POST / la query GET codificada */
#define FM_MAX_FIELDS  64u           /* cota de controles por envío (anti-amplificación) */

typedef enum fm_method { FM_GET = 0, FM_POST } fm_method;

typedef struct fm_field { const char *name; const char *value; } fm_field;

typedef enum fm_kind {
    FM_NAVIGATE = 0,   /* GET: navegar a url */
    FM_POST_REQUEST,   /* POST: enviar body (body_len) a url con content_type */
    FM_BLOCKED         /* no enviable de forma segura (falla cerrado) */
} fm_kind;

typedef enum fm_block_reason {
    FM_BLOCK_NONE = 0,
    FM_BLOCK_INSECURE,  /* el destino resuelto no es https (downgrade / esquema ajeno / base local) */
    FM_BLOCK_OVERFLOW,  /* los datos codificados o la URL no caben */
    FM_BLOCK_INVALID    /* demasiados campos, o un campo con nombre NULL */
} fm_block_reason;

typedef struct fm_plan {
    fm_kind         kind;
    fm_block_reason reason;        /* significativo solo si kind == FM_BLOCKED */
    char            url[FM_URL_MAX];
    char            body[FM_BODY_MAX];
    size_t          body_len;      /* bytes en body, excluido el NUL (0 para GET) */
    const char     *content_type;  /* estático para FM_POST_REQUEST; NULL en otro caso */
} fm_plan;

typedef enum fm_status { FM_OK = 0, FM_ERR_NULL_ARG, FM_ERR_OVERFLOW } fm_status;
```

## 2. API (pura, reentrante)

```c
fm_status fm_encode(const fm_field *fields, size_t n,
                    char *out, size_t outsz, size_t *out_len);

fm_status fm_build(const char *base, const char *action, fm_method method,
                   const fm_field *fields, size_t n, fm_plan *out);
```

### `fm_encode`
- Serializa los pares como `application/x-www-form-urlencoded`: `name=value` unidos por `&`.
- Codificación por byte (serializador WHATWG): `0x2A '*'`, `0x2D '-'`, `0x2E '.'`, dígitos, letras
  ASCII y `0x5F '_'` se emiten tal cual; `0x20` (espacio) → `'+'`; cualquier otro byte → `%XX` con
  hex en mayúsculas. Aplica idéntica a nombre y valor (dato hostil siempre escapado).
- Un campo con `value == NULL` se trata como valor vacío. Un campo con `name == NULL` → no se
  serializa el campo (se omite); si todos faltan, el resultado es la cadena vacía.
- `fields`/`out` NULL (con `n > 0`) o `outsz == 0` → `FM_ERR_NULL_ARG`. Si no cabe → `FM_ERR_OVERFLOW`
  y `out` queda NUL-terminado vacío (no se entrega codificación parcial). En éxito `*out_len` (si no
  es NULL) recibe la longitud.

### `fm_build`
- `base == NULL` u `out == NULL` → `FM_ERR_NULL_ARG`. Siempre que devuelva `FM_OK`, `*out` es un plan
  válido (posiblemente `FM_BLOCKED`); el llamante decide según `kind`.
- `action` se limpia (se eliminan TAB/LF/CR y se recortan espacios ASCII; igual criterio WHATWG que
  los enlaces). Resolución del destino `R`:
  - `action` vacío → `R = base` (un formulario sin `action` envía al documento actual).
  - `action` es `https://...` absoluto → `R = action` (vale sea cual sea la base; p. ej. una página
    local que apunta a un buscador real).
  - en otro caso → `R = url_resolve_https(base, action)` (referencia relativa / ruta absoluta /
    relativa al esquema; exige base `https`).
  - `R` se valida con `url_validate_https`. Cualquier fallo (downgrade `http://`, `javascript:`,
    `mailto:`, base local sin `action` absoluta, host vacío) → `FM_BLOCKED`, `FM_BLOCK_INSECURE`.
- `n > FM_MAX_FIELDS`, o algún `fields[i].name == NULL` → `FM_BLOCKED`, `FM_BLOCK_INVALID`.
- Codifica los campos con `fm_encode`. Si no caben → `FM_BLOCKED`, `FM_BLOCK_OVERFLOW`.
- **GET** (`FM_GET`): `url` = `R` sin su query ni fragmento, más `"?" + codificación`. `kind =
  FM_NAVIGATE`, `body_len = 0`, `content_type = NULL`. Si no cabe en `FM_URL_MAX` → `FM_BLOCK_OVERFLOW`.
- **POST** (`FM_POST`): `url` = `R` (con su query intacta), `body` = codificación, `body_len` su
  longitud, `content_type = "application/x-www-form-urlencoded"`, `kind = FM_POST_REQUEST`.
- En `FM_BLOCKED`, `url`/`body` quedan vacíos y `content_type = NULL`.

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; `action`/nombres/valores son dato
  hostil; el destino se revalida al cargar (el plan no se confía a ciegas).
- **Secure by Default / falla cerrado:** un destino no-`https` no es representable como envío; ante
  cualquier duda, `FM_BLOCKED`. Nunca un downgrade ni una URL/cuerpo a medio formar.
- **Sin asignación dinámica:** buffers de capacidad fija en el plan y en el llamante.
- **Determinista:** misma entrada → mismo plan (testeable, agent-friendly).
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio; fuzzing del codificador y de
  `fm_build` sin crash.

## 4. Tabla de estados

| `fm_status` | Condición |
| :-- | :-- |
| `FM_OK` | `fm_encode` codificó; o `fm_build` produjo un plan (mira `kind`/`reason`). |
| `FM_ERR_NULL_ARG` | Puntero requerido NULL / `outsz == 0`. |
| `FM_ERR_OVERFLOW` | Solo `fm_encode`: la codificación no cabe (`out` queda vacío). |

## 5. Fuera de alcance

- `multipart/form-data` y `text/plain` (subida de ficheros): superficie grande, fuera del caso de
  uso (buscadores). Un `<form enctype>` distinto se trata como urlencoded por defecto.
- Validación de campos por tipo (`required`, `pattern`, `number`), `<select multiple>`, controles
  `checkbox`/`radio` agrupados: el llamante decide qué pares envía; aquí solo se serializan.
- La ejecución del plan (red): la hace `secure_fetch` (`sf_get_follow`/`sf_post`), que re-aplica
  TODA la política TLS/PQ/cadena (Zero Trust).
- La extracción de los controles del DOM y su valor vivo: la hacen `page_view` y la GUI.
