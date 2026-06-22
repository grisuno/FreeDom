# spec/link_nav.md — Política de navegación al pulsar un enlace

> Módulo `link_nav` (prefijo `ln_`). Lógica **pura, sin I/O, sin estado global**: decide **qué**
> ocurre cuando el usuario (o un agente) pulsa un hiperenlace, dada la ubicación de la página
> actual y el `href` crudo del documento. No descarga nada: produce una **decisión** que el
> orquestador ejecuta. Metodología: SDD + TDD.

## 0. Por qué existe

El render entrega enlaces como **dato con procedencia, nunca instrucción** (`render_doc` /
`page_view`). Para que un enlace "funcione" al pulsarlo hace falta resolver su `href` (que puede
ser relativo, absoluto, con esquema, un fragmento, o malicioso) contra la URL de la página y
decidir si se navega, si es la misma página, o si se rechaza. Esa decisión es seguridad pura y
debe ser auditable sin Wayland ni red: vive aquí, en una función testeable, y el orquestador GUI
solo la cablea (hit-test del clic → `ln_resolve` → cargar). Reutiliza el módulo `url` para la
resolución https (DRY: la misma regla que sigue una redirección sigue un enlace) y para colapsar
segmentos `.`/`..` también en rutas locales.

**Falla cerrado:** cualquier `href` que no sea demostrablemente seguro de navegar → `LN_BLOCKED`.

**Reutilización (Hito 20e):** la **navegación por JS** (`location.href=`/`assign`/`replace`) es
moralmente "un clic": el `tab` (proceso padre, confiable) gatea la string cruda que el JS de página
pidió con este mismo `ln_resolve(URL_real, cruda)`. Así un `location.href='javascript:...'` o un
downgrade `http://` se rechazan igual que un enlace hostil, y el worker no toma la decisión (Zero
Trust). Un fragmento (`#id`) da `LN_SAME_DOCUMENT` (no navega, aún sin scroll a ancla).

## 1. Tipos

```c
#define LN_MAX_TARGET 4096u    /* cabe una URL https (<=2048) o una ruta de fichero (PATH_MAX) */
#define LN_MAX_FRAGMENT 256u   /* identificador de fragmento (parte tras '#'); si no cabe, "" */

typedef enum ln_action {
    LN_NAVIGATE = 0,    /* cargar out->target */
    LN_SAME_DOCUMENT,   /* href vacio o fragmento (#...): misma pagina, no recargar */
    LN_BLOCKED          /* referencia no soportada/insegura: no navegar */
} ln_action;

typedef enum ln_target_kind {
    LN_TARGET_NONE = 0,
    LN_TARGET_HTTPS,    /* target es una URL https absoluta */
    LN_TARGET_FILE      /* target es una ruta de fichero local */
} ln_target_kind;

typedef enum ln_block_reason {
    LN_BLOCK_NONE = 0,       /* no bloqueado */
    LN_BLOCK_DOWNGRADE,      /* downgrade http:// en claro */
    LN_BLOCK_FOREIGN_SCHEME, /* javascript:/data:/file:/mailto:/ftp:/... */
    LN_BLOCK_NO_BASE,        /* referencia relativa sin base contra la que resolver */
    LN_BLOCK_UNSUPPORTED     /* relativa al esquema sin origen, desbordamiento, irresoluble */
} ln_block_reason;

typedef struct ln_result {
    ln_action       action;
    ln_target_kind  kind;                    /* significativo solo si action == LN_NAVIGATE */
    ln_block_reason reason;                  /* LN_BLOCK_NONE salvo si action == LN_BLOCKED */
    char            target[LN_MAX_TARGET];     /* destino resuelto; "" si no es NAVIGATE */
    char            fragment[LN_MAX_FRAGMENT]; /* id del fragmento sin '#'; "" si no hay */
} ln_result;

typedef enum ln_status { LN_OK = 0, LN_ERR_NULL_ARG } ln_status;
```

## 2. API (pura, reentrante)

```c
ln_status   ln_resolve(const char *base, const char *href, ln_result *out);
const char *ln_block_reason_text(ln_block_reason reason);
```

### Fragmento y motivo de bloqueo
- **Fragmento:** el `href` se separa por el **primer** `#` (delimitador de fragmento de URL): la
  parte posterior se copia a `out->fragment` (sin `#`) y la navegación actúa solo sobre la
  referencia previa. Así `page#sec` navega a `page` con `fragment = "sec"`, y `#sec` solo es
  `LN_SAME_DOCUMENT` con `fragment = "sec"`. Un fragmento que no quepa en `LN_MAX_FRAGMENT` se
  descarta (`""`): solo alimenta un futuro *scroll* al ancla, nunca la navegación, así que perderlo
  no es fatal. El *scroll* al ancla queda fuera de alcance (requiere el mapa de posiciones del
  documento); aquí se captura el dato.
- **Motivo:** cuando `action == LN_BLOCKED`, `reason` precisa por qué (downgrade, esquema ajeno, sin
  base, irresoluble) para un aviso exacto al usuario y para salida estructurada agent-friendly.
  `ln_block_reason_text` da una cadena inglesa estable por motivo.

### `ln_resolve`
- `out == NULL` → `LN_ERR_NULL_ARG` (único error). En cualquier otro caso devuelve `LN_OK` con
  `*out` completamente poblado.
- `base` es la ubicación de la página actual: una URL `https://...`, una ruta de fichero local, o
  `NULL` (sin ubicación, p. ej. la página de inicio).
- **Limpieza del `href`** (WHATWG URL): se eliminan TAB (0x09), LF (0x0A) y CR (0x0D) en cualquier
  posición y se recortan espacios al principio y al final, sobre una copia. `href == NULL` se trata
  como bloqueado (no hay destino).
- **Fragmento / vacío:** `href` limpio vacío, o que empieza por `#` → `LN_SAME_DOCUMENT`
  (`target = ""`). No se recarga ni se navega fuera; el desplazamiento al ancla queda fuera de
  alcance pero la acción correcta es "misma página".
- **Base https** (`url_is_https(base)`):
  - Se resuelve con `url_resolve_https(base, href, ...)`. Si `URL_OK` → `LN_NAVIGATE`,
    `kind = LN_TARGET_HTTPS`. Si falla (esquema rechazado, *downgrade* http, host vacío,
    desbordamiento) → `LN_BLOCKED`.
- **Base local** (no `NULL` y no https):
  - `href` con esquema explícito (`url_has_scheme`):
    - `https://...` válido → `LN_NAVIGATE`, `kind = LN_TARGET_HTTPS`.
    - cualquier otro (`http:`, `file:`, `javascript:`, `data:`, `mailto:`, ...) → `LN_BLOCKED`.
  - `href` relativo al esquema (`//host...`): sin origen para un fichero local → `LN_BLOCKED`
    (falla cerrado).
  - en otro caso (ruta relativa o absoluta): se resuelve como **ruta de fichero** contra el
    directorio de `base` (se descarta el fragmento `#...`; los segmentos `.`/`..` se colapsan con un
    normalizador de rutas que **preserva la relatividad**: `examples/../README.md` → `README.md`,
    no `/README.md`, de modo que un `..` nunca convierte por accidente una ruta relativa en absoluta
    —corrección y seguridad—) → `LN_NAVIGATE`, `kind = LN_TARGET_FILE`. La navegación local exige
    una acción explícita del usuario (un clic) y el contenido se renderiza inerte; no hay egreso de
    red. La resolución https sí reutiliza `url_remove_dot_segments` (semántica de URL: conserva el
    `/` absoluto y las barras finales).
- **Base `NULL`:**
  - `href` que es una URL `https://...` válida → `LN_NAVIGATE`, `kind = LN_TARGET_HTTPS`.
  - cualquier otra cosa → `LN_BLOCKED` (no hay base contra la que resolver; falla cerrado).
- Si el destino resuelto no cabe en `LN_MAX_TARGET` → `LN_BLOCKED` (nunca se trunca).

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; el `href` es dato hostil y se
  trata como tal. Salida determinista (testeable, agent-friendly).
- **Secure by Default:** ningún esquema salvo `https` (y la navegación a fichero local bajo base
  local) es navegable; el *downgrade* http y `javascript:`/`data:`/`file:` se bloquean.
- **Fail-closed:** ante cualquier duda (sin base, esquema desconocido, desbordamiento) →
  `LN_BLOCKED`. La política de red real (terceros, TLS/PQ) la aplica `secure_fetch` al cargar; este
  módulo solo decide la navegabilidad.
- **Sin estado oculto:** `ln_resolve` no muta nada salvo `*out`; el llamante decide y ejecuta.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 4. Tabla de estados

| `action` | Condición |
| :-- | :-- |
| `LN_NAVIGATE` | Destino resuelto y representable (https, o fichero bajo base local). |
| `LN_SAME_DOCUMENT` | `href` vacío o fragmento `#...`. |
| `LN_BLOCKED` | Esquema rechazado, sin base resoluble, o desbordamiento. |

## 5. Fuera de alcance

- Descarga/render del destino: lo hace el orquestador (`do_load` → `secure_fetch`/`read_file`),
  re-aplicando TODA la política de red.
- Desplazamiento a un ancla (`#sección`): la acción es `LN_SAME_DOCUMENT`; el scroll al ancla es un
  hito propio del renderer.
- Codificación porcentual / IDNA del `href`: no se requiere para la política de Freedom.
