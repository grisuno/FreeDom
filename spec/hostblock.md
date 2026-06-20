# spec/hostblock.md — Filtro de hosts (lista negra + lista blanca, formato /etc/hosts)

> Módulo `hostblock` (prefijo `hb_`). Lógica **pura, sin I/O, sin estado global**: parsea listas de
> dominios en formato `/etc/hosts` (archivos `.conf`) a tablas hash y decide si un host se bloquea.
> No abre sockets ni lee archivos; el llamante le pasa el texto ya leído. Metodología: SDD + TDD.

## 0. Por qué existe

Privacy by Default: bloquear de raíz los dominios de rastreo y publicidad reduce superficie de
ataque, CPU y red, sin un motor de reglas tipo Brave. La decisión "¿este host está bloqueado?" es
**lógica pura, auditable sin red**, y debe vivir en un sitio probado: el llamante (la GUI / la capa
de red) la consulta **antes de abrir el socket**. Una **lista negra** bloquea dominios y todos sus
subdominios; una **lista blanca** los rehabilita (incluidos sus subdominios) — para poder ver un
subdominio concreto de un dominio por lo demás bloqueado. La lista blanca **gana** sobre la negra.

No introduce dependencias ni endpoints de terceros: las listas son archivos locales del usuario.

## 1. Formato de entrada (`/etc/hosts`)

Texto por líneas. En cada línea:
- Todo lo que sigue a `#` es comentario y se ignora.
- Se tokeniza por espacios/tabs. Un token **solo de dígitos, `.` y `:`** (una IP, p. ej. `0.0.0.0`,
  `127.0.0.1`, `::1`) se ignora — así `0.0.0.0 ads.example.com` aporta solo `ads.example.com`.
- Cada token restante se trata como dominio: se pasa a minúsculas, se valida (1..253 chars; solo
  `a-z 0-9 . - _`) y se inserta; se le quita un punto final si lo tiene. Tokens inválidos se omiten
  (no se aborta la carga). Líneas en blanco se ignoran.

Así sirven tanto las listas tipo hosts (`0.0.0.0 dominio`) como las de dominios "pelados" (un
dominio por línea).

## 2. Tipos

```c
typedef struct hb_set hb_set;   /* opaco: tabla hash de bloqueo + tabla de permitidos */

typedef enum hb_list { HB_LIST_BLOCK = 0, HB_LIST_ALLOW } hb_list;

typedef enum hb_decision { HB_ALLOW = 0, HB_BLOCK } hb_decision;

typedef enum hb_status {
    HB_OK = 0,
    HB_ERR_NULL_ARG,  /* set o text era NULL */
    HB_ERR_OOM        /* fallo de asignacion */
} hb_status;
```

## 3. API (reentrante; sin estado global)

```c
hb_set     *hb_new(void);
void        hb_free(hb_set *s);
hb_status   hb_load(hb_set *s, const char *text, hb_list list);
hb_decision hb_check(const hb_set *s, const char *host);
int         hb_is_allowlisted(const hb_set *s, const char *host);
size_t      hb_count(const hb_set *s, hb_list list);
```

> **Doble rol de la lista blanca.** Además de des-bloquear del adblock, una entrada en la blanca es
> el **override de soberanía** del usuario: el orquestador la usa (vía `hb_is_allowlisted`) para
> habilitar la navegación de un host por debajo del estándar de Freedom (p. ej. TLS 1.2). Secure by
> default, pero el usuario manda sobre sus propios hosts — no es una dictadura. La relajación TLS
> vive en `[[secure_fetch]]` (`SF_POLICY_ALLOWLISTED_INSECURE`); aquí solo se decide "¿está en la
> blanca explícita?".

### `hb_new` / `hb_free`
- `hb_new` reserva un conjunto vacío (NULL si OOM). `hb_free` es idempotente y seguro sobre NULL.

### `hb_load`
- `s == NULL` o `text == NULL` → `HB_ERR_NULL_ARG`. Un fallo de asignación → `HB_ERR_OOM`.
- Parsea `text` (§1) y añade los dominios a la lista indicada (`HB_LIST_BLOCK` / `HB_LIST_ALLOW`).
  Acumulativa (se puede llamar varias veces). Los duplicados se ignoran (cuenta única).

### `hb_check`
- `s == NULL`, `host == NULL`, vacío o de más de 253 chars → `HB_ALLOW` (sin lista no se bloquea;
  el adblock no es la frontera de seguridad, así que ante la duda **no** sobre-bloquea contenido).
- Pasa el host a minúsculas y le quita el punto final. Recorre los **sufijos de dominio** (el host,
  luego sin su primera etiqueta, etc.):
  1. Si algún sufijo está en la **lista blanca** → `HB_ALLOW` (la blanca gana y cubre subdominios).
  2. Si no, y algún sufijo está en la **lista negra** → `HB_BLOCK`.
  3. Si no → `HB_ALLOW`.
  Así `example.com` en la negra bloquea `example.com` y `ads.example.com`; `cdn.example.com` en la
  blanca permite `cdn.example.com` y `x.cdn.example.com` aunque `example.com` esté en la negra.

### `hb_is_allowlisted`
- `1` si algún sufijo de dominio del host está **explícitamente** en la lista blanca (cubre
  subdominios), si no `0`. Distinto de `hb_check`: reporta una entrada explícita de la blanca, no el
  "permitido porque nada lo bloquea". El orquestador lo usa como override por host (relajar TLS).
- `s`/`host` NULL, vacío o de más de 253 chars → `0`. Misma normalización que `hb_check`.

### `hb_count`
- Número de dominios únicos en la lista indicada (para tests/estadística).

## 4. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; el texto y el host son dato hostil.
- **Determinista:** misma entrada → misma decisión (testeable, agent-friendly).
- **Coste casi nulo:** búsqueda por tabla hash (FNV-1a, direccionamiento abierto); el chequeo recorre
  a lo sumo las etiquetas del host.
- **Robusto ante entrada hostil:** tokens inválidos/oversize se omiten; nunca desborda buffers.
- Objetivo de auditoría: `-fsanitize=address,undefined` limpio.

## 5. Tabla de estados (`hb_load`)

| `hb_status` | Condición |
| :-- | :-- |
| `HB_OK` | Lista cargada (los tokens inválidos se omiten en silencio). |
| `HB_ERR_NULL_ARG` | `set` o `text` es `NULL`. |
| `HB_ERR_OOM` | Fallo de asignación al crecer la tabla. |

## 6. Fuera de alcance

- Leer los archivos `.conf` del disco y elegir su ruta: lo hace el orquestador (la GUI los lee de la
  config del usuario y llama a `hb_load`).
- Reglas con comodines/regex, cosméticas (ocultar elementos), por tipo de recurso o por origen: aquí
  solo dominios y subdominios.
- La decisión de origen/terceros (eso es `[[request_policy]]`); `hostblock` es un filtro adicional
  ortogonal, consultado antes de abrir el socket.
