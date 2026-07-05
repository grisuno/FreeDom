# spec/url.md — Operaciones puras de URL (resolución y validación)

> Módulo `url` (prefijo `url_`). Lógica **pura, sin I/O, sin estado global**: el conocimiento
> canónico de "qué es una URL https absoluta válida" y "cómo se resuelve una referencia contra una
> base". No depende de libcurl ni de OpenSSL: es directamente auditable y testeable sin red.
> Metodología: SDD + TDD.

## 0. Por qué existe

La resolución de URL (unir una referencia relativa contra una base, rechazar esquemas inseguros,
normalizar segmentos `.`/`..`) la necesitan dos consumidores distintos:

- `secure_fetch`, para seguir redirecciones (cabecera `Location`).
- `link_nav`, para seguir un enlace que el usuario pulsa.

Tener esa lógica enterrada como funciones `static` dentro del módulo de red (que enlaza una pila
TLS) era deuda técnica: el resolutor no es de red, es de URL. `url` la extrae a un módulo puro,
único dueño de esa regla (DRY), reutilizable y auditable de forma aislada. `secure_fetch` delega
en él; sus validadores públicos (`sf_validate_url`, `sf_resolve_redirect`) se conservan como
envoltorios finos para no romper su API ni sus pruebas.

## 1. Tipos

```c
#define URL_MAX_LEN 8192u  /* tope duro para cualquier URL sobre la que actuamos.
                            * Subido de 2048 (2026-07-05): las URLs de bundle de la
                            * web moderna exceden 2048 (el xjs de google.com mide
                            * 3456 bytes) y el tope las hacía irresolubles; 8192 es
                            * el límite práctico de navegadores/CDNs. Sigue siendo
                            * anti-DoS: solo acota buffers de stack. */

typedef enum url_status {
    URL_OK = 0,
    URL_ERR_NULL_ARG,   /* un puntero requerido era NULL, o outsz == 0 */
    URL_ERR_NOT_HTTPS,  /* no es una URL https absoluta / esquema rechazado / host vacio */
    URL_ERR_OVERFLOW,   /* el resultado no cabe en el buffer del llamante */
    URL_ERR_NOT_LOCAL   /* no es una referencia file:// local valida, o escapa el dir base */
} url_status;

#define URL_SEARCH_ENDPOINT "https://html.duckduckgo.com/html/?q=" /* buscador sin JS */

typedef enum url_omni_kind {
    URL_OMNI_NAVIGATE = 0, /* out = https absoluta a cargar */
    URL_OMNI_SEARCH        /* out = URL https de búsqueda DuckDuckGo HTML */
} url_omni_kind;

/* Descomposición estilo WHATWG-location de una URL https absoluta validada. Cada campo
 * ALIASA la entrada (no se posee; válido mientras la URL viva); las longitudes excluyen
 * cualquier NUL. Un componente ausente tiene longitud 0. pathname es el tramo literal
 * del path y queda vacío cuando la URL no tiene path (el shim de location muestra "" como "/"). */
typedef struct url_parts {
    const char *href;     size_t href_len;     /* la URL completa */
    const char *protocol; size_t protocol_len; /* "https:" */
    const char *origin;   size_t origin_len;   /* "https://host[:port]" */
    const char *host;     size_t host_len;     /* "host[:port]" */
    const char *hostname; size_t hostname_len; /* "host" (corchetes conservados para IPv6) */
    const char *port;     size_t port_len;     /* "" o dígitos decimales */
    const char *pathname; size_t pathname_len; /* "/..." o "" */
    const char *search;   size_t search_len;   /* "?..." o "" */
    const char *hash;     size_t hash_len;     /* "#..." o "" */
} url_parts;
```

## 2. API (pura, reentrante)

```c
int        url_is_https(const char *s);
int        url_has_scheme(const char *s);
size_t     url_authority_len(const char *url);
url_status url_validate_https(const char *url);
url_status url_remove_dot_segments(const char *path, char *out, size_t outsz);
url_status url_resolve_https(const char *base, const char *ref, char *out, size_t outsz);
url_status url_omnibox(const char *input, url_omni_kind *kind, char *out, size_t outsz);
int         url_is_file(const char *s);
const char *url_file_path(const char *s);
url_status  url_resolve_file(const char *base, const char *ref, char *out, size_t outsz);
url_status  url_split(const char *url, url_parts *out);
```

### `url_is_https`
Devuelve distinto de cero **solo** si `s` empieza (sin distinguir mayúsculas) por `https://` y el
host no está vacío ni comienza por `/`. `NULL` → 0.

### `url_has_scheme`
Distinto de cero si `s` empieza por `<scheme>:` según RFC 3986
(`ALPHA *( ALPHA / DIGIT / "+" / "-" / "." ) ":"`). `NULL` → 0. No considera esquema un primer
carácter no alfabético (p. ej. `//host`, `/path`, `#frag`, `?q` no tienen esquema).

### `url_authority_len`
Longitud de `https://host[:puerto]` dentro de una URL https ya validada: índice de la primera `/`
tras el esquema, o la longitud total si no hay path. Asume entrada validada por
`url_validate_https`.

### `url_validate_https`
`URL_OK` solo para una URL https absoluta con host no vacío. En otro caso `URL_ERR_NOT_HTTPS`
(o `URL_ERR_NULL_ARG` si `url == NULL`). El esquema se compara sin distinguir mayúsculas.

### `url_remove_dot_segments`
Implementación pura de RFC 3986 §5.2.4 sobre el componente *path* de entrada: elimina los
segmentos `.` y `..` y colapsa la salida. Conserva si el path empezaba por `/` (absoluto) y si
terminaba en `/`. `out`/`path == NULL` o `outsz == 0` → `URL_ERR_NULL_ARG`; si no cabe →
`URL_ERR_OVERFLOW`. La salida nunca es más larga que la entrada más un posible `/` inicial.

### `url_resolve_https`
Resuelve `ref` contra `base` produciendo **siempre** una URL https absoluta en `out` o fallando
cerrado:

- `base`, `ref` u `out` `NULL`, o `outsz == 0` → `URL_ERR_NULL_ARG`.
- `base` debe ser una URL https válida (`url_validate_https`); si no → `URL_ERR_NOT_HTTPS`
  (**falla cerrado**: no se confía en una base mal formada).
- `ref` vacía → `URL_ERR_NOT_HTTPS`.
- `ref` con `https://...` → se copia tal cual (absoluta).
- `ref` con `http://...` → `URL_ERR_NOT_HTTPS` (se rechaza el *downgrade* a texto claro).
- `ref` con cualquier otro esquema explícito (`javascript:`, `data:`, `mailto:`, `ftp:`, `file:`,
  ...) → `URL_ERR_NOT_HTTPS`.
- `ref` que empieza por `//` (relativa al esquema) → `https:` + `ref`.
- `ref` que empieza por `/` (path absoluto) → `origen(base)` + path normalizado.
- En otro caso (path relativo) → `directorio(base)` + `ref`, path normalizado.

El path resultante se normaliza con `url_remove_dot_segments` (los `.`/`..` se colapsan: la salida
es una URL canónica). Antes de devolver, el resultado se valida con `url_validate_https`; si no es
una https absoluta válida → `URL_ERR_NOT_HTTPS`. Si el ensamblado excede `outsz` →
`URL_ERR_OVERFLOW`.

### `url_omnibox`

Resuelve texto libre de la barra de URL en una https absoluta, decidiendo entre **navegar** a un
sitio o **buscar** en la web (DuckDuckGo HTML, `URL_SEARCH_ENDPOINT`, que funciona sin JS). Tipo
`url_omni_kind` = `{ URL_OMNI_NAVIGATE, URL_OMNI_SEARCH }`. Reglas (puro, fail-closed, Secure by
Default):

- ya es una https absoluta válida → `NAVIGATE` (copia verbatim);
- forma de host desnudo (`example.com`, `host:8443/p`, `localhost`) → `NAVIGATE`, prefijado con
  `https://`. "Host" = `localhost`, o etiquetas `[A-Za-z0-9-]` unidas por puntos con TLD final
  **alfabético de ≥2**. La forma `host:port` se reconoce como host **antes** del chequeo de esquema
  (sintácticamente `host:` parece `<scheme>:`);
- prefijo `http://` → `NAVIGATE`, **promovido a https** (HTTPS-only: nunca downgrade, el esquema
  seguro es el único representable);
- cualquier otra cosa — espacios en blanco, un esquema que no sea http(s) (así `javascript:...` se
  **busca**, nunca se ejecuta), o un token que no es host → `SEARCH`. La query se codifica en
  porcentaje (espacio→`+`, no-unreserved→`%XX`).

**No** maneja archivos locales: el orquestador resuelve un path local existente **antes** de llamar
(una función pura no puede `stat` el FS). `out` queda NUL-terminado en `URL_OK`; punteros NULL /
`outsz==0` → `URL_ERR_NULL_ARG`; URL construida que no cabe → `URL_ERR_OVERFLOW`.

### `url_is_file` / `url_file_path` / `url_resolve_file`

Origen **local** `file://` para que una página de archivo "actúe como https" (resolución de
referencias relativas e imágenes locales). `url_is_file(s)` = `s` empieza (case-insensitive) con
`file://` seguido de path absoluto (`file:///...`). `url_file_path(s)` = el path (`/...`) dentro del
`file://`, o NULL (alias de `s`, no se libera).

`url_resolve_file(base, ref, out, outsz)` resuelve `ref` (relativa o absoluta-local o `file://`)
contra una base `file:///dir/page` y produce un `file:///...` canónico. **Crítico de seguridad y
fail-closed:** el resultado queda **confinado al subárbol del directorio de `base`** — un escape
`../`, un path absoluto fuera, una scheme-relative (`//..`) o cualquier esquema no-file (una `src`
remota https o de esquema ajeno en una página local) devuelven `URL_ERR_NOT_LOCAL`. Así un documento
local hostil **no puede** autocargar `/etc/passwd` ni telefonear a casa por una imagen. Los segmentos
punto se colapsan **antes** del chequeo de confinamiento (`../` no puede burlar el prefijo). `base`
inválida ⇒ `URL_ERR_NOT_LOCAL`; punteros NULL / `outsz==0` ⇒ `URL_ERR_NULL_ARG`; overflow ⇒
`URL_ERR_OVERFLOW`. **Solo** lo aplican páginas con origen `file://`; un origen https jamás entra a
esta rama (un remoto nunca resuelve a `file://`).

### `url_split` — descomposición WHATWG-location (para `location.*` del JS)

`url_split(url, out)` descompone una URL https absoluta validada en los componentes que un objeto
`location` del JS de página necesita leer (`href`, `protocol`, `origin`, `host`, `hostname`, `port`,
`pathname`, `search`, `hash`). Es **pura y zero-copy**: cada campo de `url_parts` apunta a un tramo
de `url` (no se copia, no se posee) con su longitud. Reusa `url_authority_len`/`url_validate_https`,
así "qué es la autoridad de una https" sigue viviendo en un solo lugar.

Reglas de partición (todas tramos de la entrada):
- `protocol` = `"https:"` (los 6 primeros bytes); `origin` = `"https://host[:port]"`
  (`url[0..url_authority_len)`); `host` = `origin` sin el prefijo `https://`.
- `hostname`/`port` parten `host` por el `:` (con soporte de literal IPv6 `[..]:port`; sin `:`,
  `port` queda vacío).
- El resto tras la autoridad se parte en `pathname` (hasta `?`/`#`), `search` (de `?` a `#`,
  incluye el `?`) y `hash` (de `#` al final, incluye el `#`). `pathname` puede quedar **vacío**
  (sin path); el consumidor lo presenta como `/`.

**Solo https** (Secure by Default y fail-closed): `url` que no sea una https absoluta válida ⇒
`URL_ERR_NOT_HTTPS`; punteros NULL ⇒ `URL_ERR_NULL_ARG`. No decodifica porcentual ni IDNA (igual
que el resto del módulo). Es el lado de **lectura** de `location`; la **decisión** de navegar
(`location.href=`/`assign`/`replace`) la toma `link_nav` (`ln_resolve`), no este módulo.

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante. Falla cerrado: ante cualquier
  duda (base inválida, esquema no https, desbordamiento) se rechaza, nunca se degrada.
- **Omnibox fail-closed:** un esquema peligroso tecleado/pegado (`javascript:`, `file:`, `data:`)
  se convierte en **búsqueda**, jamás en ejecución; `http://` se **promueve** a https, nunca se
  navega en claro.
- **Confinamiento local fail-closed:** `url_resolve_file` nunca produce un path fuera del directorio
  del documento; el prefijo se compara con la barra final (`/a/docs/`) para que `/a/docsEVIL/` no
  pase. Verificado con stress ASan/UBSan de 3M iteraciones (invariante de confinamiento intacto).
- **Secure by Default:** una URL no-https no es representable como salida de `url_resolve_https`;
  el *downgrade* a `http://` se rechaza explícitamente.
- **Sin desbordamiento:** todo ensamblado usa copias acotadas; nunca se trunca silenciosamente
  (se devuelve `URL_ERR_OVERFLOW`).
- **Determinismo:** salida canónica (segmentos punto colapsados), apta para comparación estable.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 4. Tabla de estados

| Código | Condición |
| :-- | :-- |
| `URL_OK` | Operación completada; `out` contiene una URL https válida. |
| `URL_ERR_NULL_ARG` | Puntero requerido `NULL` o `outsz == 0`. |
| `URL_ERR_NOT_HTTPS` | Entrada/resultado no es una URL https absoluta válida, o esquema rechazado. |
| `URL_ERR_OVERFLOW` | El resultado no cabe en `out`. |
| `URL_ERR_NOT_LOCAL` | No es una referencia `file://` local válida, o escapa el directorio base. |

## 5. Fuera de alcance

- Decodificación/codificación porcentual, IDNA/punycode, normalización de host: no se requiere para
  la política de Freedom (https-only, comparación de host la hace `request_policy`).
- Esquemas distintos de https: se rechazan por diseño (Secure by Default).
- Rutas de sistema de ficheros locales: las resuelve `link_nav` (semántica de path, no de URL),
  reutilizando `url_remove_dot_segments`.
