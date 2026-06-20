# spec/net_realm.md — Clasificación de red y enrutado (Tor / I2P / clearnet)

> Módulo `net_realm` (prefijo `nr_`). Lógica **pura, sin I/O, sin estado global**: dado un host o
> URL decide en qué **realm** vive (clearnet, `.onion`, `.i2p`) y, según la configuración de proxies
> habilitados, **cómo enrutarlo** (directo, vía Tor, vía I2P, o bloqueado). No abre sockets ni habla
> con ningún proxy: solo decide. El orquestador (`secure_fetch` / GUI) ejecuta la decisión.
> Metodología: SDD + TDD.

## 0. Por qué existe

Principio 3 (Privacy by Default): *"Integración opcional con Tor/I2P a nivel de socket"*. La decisión
"¿por dónde sale esta petición?" es **lógica pura y auditable sin red**, así que vive en un sitio
probado, separada del cableado de `libcurl`. Esto permite garantizar, con tests, dos invariantes de
anonimato:

1. **Aislamiento de realm:** una dirección `.onion` **solo** puede salir por Tor; una `.i2p` **solo**
   por I2P. Nunca por DNS clearnet (eso filtraría la consulta a un resolver y delataría la visita).
2. **Fail-closed:** si el realm exige un proxy que no está habilitado, la decisión es `NR_ROUTE_BLOCKED`
   (se rechaza), **jamás** un fallback directo que desanonimice al usuario.

No se embebe el daemon de Tor/I2P (superficie de ataque enorme, contra doctrina): la integración es
"a nivel de socket" contra un proxy local que el usuario ejecuta (`tor`, `i2pd`).

## 1. Tipos

```c
typedef enum nr_realm {
    NR_CLEARNET = 0,  /* host con DNS ordinario */
    NR_ONION,         /* *.onion  -> Tor */
    NR_I2P            /* *.i2p    -> I2P */
} nr_realm;

typedef enum nr_route {
    NR_ROUTE_DIRECT = 0,  /* conexion directa (clearnet) */
    NR_ROUTE_TOR,         /* via el proxy SOCKS5h de Tor (DNS remoto) */
    NR_ROUTE_I2P,         /* via el proxy HTTP de I2P */
    NR_ROUTE_BLOCKED      /* no alcanzable con la config actual (fail-closed) */
} nr_route;

typedef struct nr_config {
    int tor_enabled;      /* hay un proxy Tor disponible/configurado */
    int i2p_enabled;      /* hay un proxy I2P disponible/configurado */
    int torify_clearnet;  /* enrutar tambien el clearnet por Tor (solo si tor_enabled) */
} nr_config;
```

## 2. API (reentrante; sin estado global)

```c
nr_realm    nr_classify_host(const char *host);
nr_realm    nr_classify_url(const char *url);
nr_route    nr_route_for(const char *url, nr_config cfg);
int         nr_realm_allows_http(nr_realm r);
const char *nr_realm_name(nr_realm r);   /* "clearnet"/"onion"/"i2p" */
const char *nr_route_name(nr_route r);   /* "direct"/"tor"/"i2p"/"blocked" */
```

### `nr_realm_allows_http`
- `1` si el realm puede usar `http://` plano; si no, `0`. Un realm overlay autentica y cifra por su
  dirección (la destination de I2P / la clave del onion), así que http sobre él **no es un
  downgrade**. Hoy: `NR_I2P` → `1` (los eepsites son http); `NR_ONION` → `0` (el dueño mantiene
  `.onion` https-only); `NR_CLEARNET` → `0` (clearnet siempre https). El llamante igual debe enrutar
  por el proxy del overlay. La aplicación de http vive en `[[secure_fetch]]` (`allow_overlay_http`):
  sin TLS no se aplica la política TLS/PQ (el overlay ya da la seguridad), y `http://` clearnet
  **sigue rechazado**.

### `nr_classify_host`
- Pasa el host a minúsculas (ASCII) y le quita un punto final. Clasifica por **etiqueta TLD final**:
  - termina en `.onion` (con al menos una etiqueta delante) → `NR_ONION`.
  - termina en `.i2p` → `NR_I2P`.
  - cualquier otra cosa → `NR_CLEARNET`.
- `host` NULL, vacío o > 253 chars → `NR_CLEARNET` (la validación real de la URL es de otro módulo;
  aquí "no sé" = clearnet, y el enrutado/validación decidirán). Un host que es exactamente `onion`
  o `i2p` (sin punto) → `NR_CLEARNET` (no es un sufijo de realm).

### `nr_classify_url`
- Extrae el host de una URL `esquema://host[:puerto][/...]` y lo clasifica con `nr_classify_host`.
- Si no se puede extraer host → `NR_CLEARNET`.

### `nr_route_for`
- `realm = nr_classify_url(url)`, luego:

| realm | condición | ruta |
| :-- | :-- | :-- |
| `NR_ONION` | `tor_enabled` | `NR_ROUTE_TOR` |
| `NR_ONION` | `!tor_enabled` | `NR_ROUTE_BLOCKED` |
| `NR_I2P` | `i2p_enabled` | `NR_ROUTE_I2P` |
| `NR_I2P` | `!i2p_enabled` | `NR_ROUTE_BLOCKED` |
| `NR_CLEARNET` | `tor_enabled && torify_clearnet` | `NR_ROUTE_TOR` |
| `NR_CLEARNET` | en otro caso | `NR_ROUTE_DIRECT` |

- `url` NULL → `NR_ROUTE_BLOCKED` (fail-closed: no se enruta lo que no se puede clasificar).

### `nr_realm_name` / `nr_route_name`
- Cadenas estables, cortas, en inglés (salida determinista, agent-friendly). Nunca `NULL`; un valor
  de enum desconocido devuelve una cadena por defecto.

## 3. Garantías

- **Pureza / Zero Trust:** sin I/O, sin estado global, reentrante; host/URL son dato hostil.
- **Aislamiento de realm:** `.onion`→solo Tor, `.i2p`→solo I2P; nunca se devuelve `DIRECT` para ellos.
- **Fail-closed:** realm que requiere proxy no habilitado → `BLOCKED`; URL inclasificable → `BLOCKED`.
- **Sin fuga de DNS:** la ruta Tor implica SOCKS5h en el orquestador (resolución remota); este módulo
  garantiza que el clearnet "torificado" y el `.onion` toman la ruta Tor, no la directa.
- **Determinista:** misma entrada → misma decisión (testeable).

## 4. Fuera de alcance

- Abrir/gestionar el proxy, detectar si el puerto escucha, o lanzar `tor`/`i2pd`: lo hace el
  orquestador (lee la config, fija `CURLOPT_PROXY`/`CURLOPT_PROXYTYPE` en `[[secure_fetch]]`).
- La política TLS/PQ/cadena: **no cambia** por el realm (https-only y TLS 1.3 siguen vigentes incluso
  en `.onion`/`.i2p`, por decisión del dueño). El override por host es `[[hostblock]]` (`allow.conf`).
- Stream isolation por pestaña, control de circuitos, autenticación de onion services v3 con clave:
  futuros hitos.
