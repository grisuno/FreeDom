# spec/render_policy.md — Capacidades de render y carga de imágenes

> Módulo `render_policy` (prefijo `rdp_`). Lógica **pura, sin I/O**: es la superficie
> directamente auditable que decide *qué se le permite hacer a una página*. Un orquestador
> (el worker `tab` / el loader) consulta estas funciones antes de pedir nada por
> `secure_fetch`. La configuración insegura no debe ser representable: el valor por defecto
> de las capacidades es el seguro.

## 0. Por qué existe

Una imagen remota es un subrecurso: cargarla abre una petición de red nueva que **revela tu
IP** al servidor de la imagen y habilita el *tracking pixel* clásico (un GIF 1x1 cuyo único
fin es contar y correlacionar visitas). Por eso, en Freedom:

- **Imágenes OFF por defecto** (Secure/Privacy by Default). Activarlas es una acción explícita
  del usuario, acompañada de un aviso de rastreo.
- **CSS y JS de autor** también son capacidades opt-in, gobernadas por el mismo gate.
- Cuando el usuario **activa** imágenes, la postura es *cargar todas salvo trackers evidentes*:
  se permite cross-site, pero se bloquea la heurística de píxel de rastreo (1x1 / dimensiones
  diminutas / área cero).

Este módulo **no hace red**: solo decide. El que cumpla la decisión (o falle cerrado si no
puede) es el orquestador, en otro hito.

## 1. Tipos

### `rdp_caps` — capacidades de la página
```c
typedef struct rdp_caps {
    bool images;  /* cargar imágenes remotas (riesgo de rastreo) */
    bool css;     /* aplicar CSS de autor */
    bool js;      /* ejecutar JavaScript de la página */
} rdp_caps;
```
El **valor cero** (`{0}`) es el baseline seguro: todo desactivado. No hay forma de obtener
capacidades activas sin ponerlas a `true` de forma explícita y auditable.

### `rdp_img_decision` — decisión para una imagen concreta
```c
typedef enum rdp_img_decision {
    RDP_IMG_ALLOW = 0,        /* se puede pedir */
    RDP_IMG_BLOCK_DISABLED,   /* capacidad de imágenes desactivada (por defecto) */
    RDP_IMG_BLOCK_INVALID,    /* URL ausente/no parseable -> falla cerrado */
    RDP_IMG_BLOCK_SCHEME,     /* esquema no https */
    RDP_IMG_BLOCK_TRACKER     /* heurística de píxel de rastreo */
} rdp_img_decision;
```

## 2. Funciones (todas puras, reentrantes, sin asignación dinámica)

```c
rdp_caps         rdp_caps_safe(void);
int              rdp_is_tracking_pixel(int w, int h);
rdp_img_decision rdp_image_decision(rdp_caps caps,
                                    const char *top_level_url,
                                    const char *image_url,
                                    int declared_w, int declared_h);
const char      *rdp_img_reason(rdp_img_decision d);
const char      *rdp_images_warning(void);
```

### `rdp_caps_safe`
Devuelve las capacidades por defecto: `images=false, css=false, js=false`. Equivale al valor
cero, pero explícito y autodocumentado.

### `data:` URIs (2026-07-16)
Un `image_url` que empieza con `data:` (`du_is_data_url`, módulo `data_url`) se salta el
`rp_evaluate` (scheme/host) y la heurística de tracking-pixel de este mismo `rdp_image_decision`:
decodificarlo no abre ningún socket, así que ni filtra la IP del lector ni sirve como pixel de
rastreo, y el bloqueo por scheme (pensado para `http://`/`javascript:`/etc.) no tiene sentido
aplicado a bytes que ya están en el documento. Sigue exigiendo `caps.images` (mismo interruptor
único que toda imagen) y falla cerrado (`RDP_IMG_BLOCK_INVALID`) si `du_base64_payload` no
encuentra un payload base64 válido (p. ej. la variante percent-encoded, fuera de alcance). Ver
`spec/data_url.md`, `[[freedom-data-url-images]]`.

### `rdp_is_tracking_pixel(w, h)`
Heurística pura sobre las **dimensiones declaradas** de la imagen (atributos `width`/`height`
del `<img>`, o el tamaño anunciado). `w`/`h` negativos significan *desconocido*.

| Entrada | Resultado |
| :-- | :-- |
| `w < 0` **o** `h < 0` (desconocido) | `0` (no clasificable; no se bloquea por esta vía) |
| `w == 0` **o** `h == 0` (área cero) | `1` (beacon) |
| `w <= RDP_TRACKER_MAX_DIM` **y** `h <= RDP_TRACKER_MAX_DIM` | `1` (píxel de rastreo) |
| resto | `0` |

`RDP_TRACKER_MAX_DIM = 2` (cubre 1x1, 2x2, 1x2, …). Se exige que **ambas** dimensiones sean
diminutas para no bloquear imágenes finas legítimas con tamaño conocido.

### `rdp_image_decision(caps, top, image, w, h)`
Decisión combinada, evaluada en este orden (falla cerrado):

1. Si `!caps.images` → `RDP_IMG_BLOCK_DISABLED`. Con la capacidad apagada, no se mira siquiera
   la URL: nada de la imagen importa.
2. Reusa `rp_evaluate(top, image)` (Zero Trust: revalida host + esquema en cada subrecurso):
   - `RP_BLOCK_INVALID` → `RDP_IMG_BLOCK_INVALID`
   - `RP_BLOCK_SCHEME`  → `RDP_IMG_BLOCK_SCHEME`
   - `RP_ALLOW` (same-site) **o** `RP_BLOCK_THIRD_PARTY` (cross-site) → origen permitido para
     imágenes en esta postura; se continúa.
3. Si `rdp_is_tracking_pixel(w, h)` → `RDP_IMG_BLOCK_TRACKER`.
4. En otro caso → `RDP_IMG_ALLOW`.

> Diferencia deliberada con `request_policy`: para imágenes opt-in, cross-site **no** se bloquea
> (a diferencia de scripts/otros subrecursos); el filtro es la heurística de trackers. El
> esquema no-https y las URLs inválidas siguen siendo fatales.

### `rdp_img_reason(d)`
Cadena estable, corta, en inglés, para salida estructurada determinista (agent-friendly). Nunca
`NULL`; un valor de enum desconocido devuelve `"unknown"`.

### `rdp_images_warning()`
Texto fijo en inglés que la UI muestra al activar imágenes: advierte que cargar imágenes remotas
revela la IP y permite rastreo (tracking pixels). Nunca `NULL` ni vacío.

## 3. Tabla de errores / decisiones

| Decisión | Cuándo | Acción del orquestador |
| :-- | :-- | :-- |
| `RDP_IMG_ALLOW` | imágenes ON, esquema https, no tracker | pedir vía `secure_fetch` |
| `RDP_IMG_BLOCK_DISABLED` | imágenes OFF (defecto) | no pedir; mostrar placeholder |
| `RDP_IMG_BLOCK_INVALID` | URL ausente/no parseable o top no-https | no pedir (fail-closed) |
| `RDP_IMG_BLOCK_SCHEME` | esquema de la imagen no https | no pedir |
| `RDP_IMG_BLOCK_TRACKER` | dimensiones de píxel de rastreo | no pedir; placeholder |

## 4. Garantías de seguridad

- **Secure/Privacy by Default:** sin opt-in explícito, ninguna imagen remota se pide jamás.
- **Fail-closed:** ante URL inválida, esquema no-https o top-level no-https, se bloquea.
- **Zero Trust:** cada imagen se revalida contra `rp_evaluate`; no hay caché de confianza.
- **Pureza:** sin I/O, sin estado global, sin asignación; salida determinista (testeable y
  agent-friendly). El módulo no abre conexiones: solo el orquestador lo hace, y solo tras un
  `RDP_IMG_ALLOW`.
- **Insecure-not-representable:** el tipo `rdp_caps` por defecto (valor cero) es el seguro.

## 5. Fuera de alcance (este hito)

- Hacer la red de la imagen (descarga, decodificado, pintado): hito del orquestador/UI.
- Heurísticas de tracker más allá de tamaño (listas de dominios, aspect-ratio extremo, query
  params sospechosos): posible extensión futura, documentada aparte.
- CSS y JS *reales* (motor de cajas, mutación DOM→repintado): el gate los expone como
  capacidades, pero su implementación son hitos propios.
- Persistencia de la preferencia del usuario (en qué sitios activó imágenes): corresponde a
  `local_store`/`browser`, no aquí.
