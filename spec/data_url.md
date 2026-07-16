# spec/data_url.md — Imágenes `data:` (RFC 2397, variante base64)

> Módulo `data_url` (prefijo `du_`). Lógica **pura, sin I/O, sin estado global**: parseo de
> `data:` URLs y decodificación base64 (RFC 4648). Metodología: SDD + TDD.

## 0. Por qué existe

Un `<img src="data:image/png;base64,...">` embebe los bytes de la imagen directamente en el
HTML — no dispara ninguna petición de red. Antes de este módulo, `render_policy` clasificaba
TODO `data:` como `RDP_IMG_BLOCK_SCHEME` (mismo camino que un `javascript:` o `ftp:` hostil),
así que cualquier ícono/logo/spinner inline — un patrón extremadamente común en sitios
modernos (bundlers, SPAs, PNGs de 1x1 para CSS) — se mostraba como placeholder roto pese a
`caps.images` estar activo. Esto era el gap número uno de "las imágenes no siempre
renderizan" reportado por el dueño.

**Por qué `data:` no es un caso de Privacy by Default como `https://`:** el bloqueo de
imágenes por defecto (`spec/render_policy.md` §0) existe porque cargar una imagen remota abre
un socket nuevo que revela la IP del lector y habilita tracking pixels. Un `data:` URI no abre
ningún socket — los bytes ya están en el documento que el lector ya recibió. No hay IP que
filtrar ni petición que correlacionar. Por eso `data:` **se salta** el chequeo de esquema/host
de `request_policy` y la heurística de tracking-pixel (ninguna de las dos aplica sin red), pero
**sigue gateado por `caps.images`** — mismo interruptor único que gobierna toda imagen (remota
o `file://`), por consistencia y porque decodificar sigue siendo trabajo de CPU sobre bytes
hostiles que el usuario no pidió ver hasta que activa imágenes.

**Por qué el decode vive en el worker confinado, no en el padre:** el string del `data:` URI
(prefijo `data:`, tipo MIME, flag `;base64`, separador `,`) es hostil — viene de HTML remoto —
pero **localizar** esas partes es solo aritmética de punteros acotada (igual que
`url_resolve_https` ya parsea URLs hostiles en el padre). El PADRE solo recorta el substring
base64 (`du_base64_payload`, sin decodificar nada). El **decode base64 en sí** (una
transformación de bytes hostiles) y el decode de formato de imagen (PNG/JPEG/WebP/GIF — la
parte realmente peligrosa) corren los dos DENTRO del worker confinado, vía un opcode IPC nuevo
(`OP_DECODE_IMAGE_B64`, ver `spec/tab.md`), preservando "el worker decodifica todo contenido
hostil, el padre nunca".

## 1. Tipos

```c
typedef enum du_status {
    DU_OK = 0,
    DU_ERR_NULL_ARG,      /* puntero requerido NULL */
    DU_ERR_NOT_DATA_URL,  /* no empieza con "data:" (case-insensitive) */
    DU_ERR_NOT_BASE64,    /* es "data:" pero sin el flag ";base64" antes de la coma,
                           * o sin coma separadora -- variante percent-encoded, fuera
                           * de alcance (mayormente SVG/texto, que el decoder de
                           * imagen no rasteriza igual) */
    DU_ERR_BAD_BASE64,    /* longitud no múltiplo de 4, carácter fuera del alfabeto,
                           * o '=' de relleno en posición que no es la final */
    DU_ERR_TOO_LARGE,     /* payload codificado > DU_MAX_ENCODED_LEN (anti-DoS) */
    DU_ERR_OOM
} du_status;

/* 16 MiB de texto base64 codificado (~12 MiB decodificados) -- generoso para
 * cualquier ícono/logo/imagen inline real; acota la asignación antes de decodificar
 * un payload cuyo tamaño controla el HTML remoto. */
#define DU_MAX_ENCODED_LEN ((size_t)(16u * 1024u * 1024u))
```

## 2. Funciones (puras, reentrantes)

```c
/* Nonzero iff url empieza (case-insensitive) con "data:". NULL => 0. Usado por
 * render_doc (saltar url_resolve_https, que rechazaría el esquema) y por el
 * cargador de imágenes de la GUI (saltar el fetch de red por completo). */
int du_is_data_url(const char *url);

/* Localiza el payload base64 dentro de un data: URL: valida el prefijo "data:",
 * busca la coma separadora y el flag ";base64" inmediatamente antes de ella. NO
 * decodifica ni asigna memoria -- *payload apunta DENTRO de `url` (mismo tiempo de
 * vida). Falla cerrado ante cualquier variante no soportada (sin coma, sin flag
 * base64, payload que excede DU_MAX_ENCODED_LEN). */
du_status du_base64_payload(const char *url, const char **payload, size_t *payload_len);

/* Decodifica texto base64 (RFC 4648, alfabeto estándar +/, relleno = obligatorio,
 * longitud múltiplo de 4) a bytes recién asignados. *out queda en manos del
 * llamante (free). Cualquier carácter fuera del alfabeto, relleno mal ubicado, o
 * longitud no múltiplo de 4 falla cerrado (DU_ERR_BAD_BASE64) -- nunca decodifica
 * un prefijo parcial. */
du_status du_base64_decode(const char *b64, size_t b64_len, uint8_t **out, size_t *out_len);
```

## 3. Tabla de errores / decisiones

| Entrada | Resultado |
| :-- | :-- |
| `url == NULL` | `DU_ERR_NULL_ARG` |
| `"http://..."`, `"https://..."`, cualquier otro esquema | `du_is_data_url` = 0; `du_base64_payload` = `DU_ERR_NOT_DATA_URL` |
| `"data:image/png,AAAA"` (sin `;base64`) | `DU_ERR_NOT_BASE64` |
| `"data:image/png;base64"` (sin coma) | `DU_ERR_NOT_BASE64` |
| `"data:image/png;base64,"` (payload vacío) | `DU_OK`, `payload_len == 0` (decodifica a 0 bytes; el decoder de imagen lo rechazará después, capa separada) |
| payload codificado > 16 MiB | `DU_ERR_TOO_LARGE` |
| base64 con longitud no múltiplo de 4 | `DU_ERR_BAD_BASE64` |
| base64 con `=` en posición no final (p. ej. `"A=AA"`) | `DU_ERR_BAD_BASE64` |
| base64 con carácter fuera de `[A-Za-z0-9+/=]` | `DU_ERR_BAD_BASE64` |
| base64 válido, bien formado | `DU_OK`, `*out`/`*out_len` con los bytes decodificados |

## 4. Garantías de seguridad

- **Sin I/O, sin red:** el módulo entero es aritmética de punteros + una tabla de valores;
  ningún dato sale del proceso que lo invoca.
- **Fail-closed:** cualquier ambigüedad (longitud no múltiplo de 4, relleno mal ubicado,
  carácter inválido, variante percent-encoded) rechaza, nunca decodifica un prefijo parcial ni
  adivina.
- **Anti-DoS:** `DU_MAX_ENCODED_LEN` acota la asignación ANTES de decodificar; un HTML hostil
  con un `data:` URI de gigabytes no agota memoria en el intento.
- **`du_base64_payload` no asigna memoria** (solo apunta dentro del `url` del llamante) — cero
  superficie de fuga en el padre; el único `malloc` real (`du_base64_decode`) corre en el
  worker confinado (ver `spec/tab.md` `OP_DECODE_IMAGE_B64`).
- **No reemplaza el decoder de formato:** `du_base64_decode` produce bytes crudos; si esos
  bytes no son un PNG/JPEG/WebP/GIF válido, `image_decode` (ya fuzzeado, ver
  `spec/image_decode.md`) los rechaza como cualquier otro fetch fallido.

## 5. Fuera de alcance

- **Variante percent-encoded** (`data:image/svg+xml,<svg>...`): sin flag `;base64`, fuera de
  alcance v1. El caso de uso dominante para esta variante es SVG, que `image_decode` no
  rasteriza de todas formas (sin decoder SVG en el árbol).
- **Media-type declarado:** el módulo no valida que el `image/xxx` declarado coincida con los
  bytes reales; eso ya lo hace `image_decode` por sniffing de magic bytes, como con cualquier
  imagen remota.
- **`data:` en contextos no-imagen** (`href` de un link, `@import`, favicons): fuera de alcance;
  este hito cubre únicamente `<img src="data:...">`.

## 6. BDD (Given-When-Then)

```
Feature: Decodificar imágenes data: URI

  Scenario: Detectar un data: URL
    Given una URL "data:image/png;base64,iVBORw0KGgo="
    When se llama du_is_data_url
    Then devuelve distinto de 0

  Scenario: Rechazar esquema no-data
    Given una URL "https://example.com/logo.png"
    When se llama du_is_data_url
    Then devuelve 0

  Scenario: Localizar el payload base64
    Given una URL "data:image/png;base64,QQ=="
    When se llama du_base64_payload
    Then devuelve DU_OK con payload apuntando a "QQ==" y payload_len 4

  Scenario: Rechazar variante percent-encoded
    Given una URL "data:image/svg+xml,<svg/>"
    When se llama du_base64_payload
    Then devuelve DU_ERR_NOT_BASE64

  Scenario: Decodificar base64 válido
    Given el texto "QQ==" (1 byte, relleno doble)
    When se llama du_base64_decode
    Then devuelve DU_OK con 1 byte: 0x41 ('A')

  Scenario: Rechazar base64 mal formado
    Given el texto "QQ=A" (relleno en posición no final)
    When se llama du_base64_decode
    Then devuelve DU_ERR_BAD_BASE64

  Scenario: Anti-DoS
    Given un payload codificado de más de 16 MiB
    When se llama du_base64_payload
    Then devuelve DU_ERR_TOO_LARGE
```
