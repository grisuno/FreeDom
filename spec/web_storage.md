# web_storage — `localStorage` en memoria para hosts de confianza

> Estado: SDD (2026-09-30). Módulo puro `web_storage` (`wst_`), sin I/O. Plan B7.
> Decisión del dueño: **persistencia solo en memoria** — nada llega al disco; se pierde al
> cerrar el navegador.

## 1. Propósito

`localStorage` era un objeto nuevo en cada carga: una app que guarda su estado (preferencias,
borradores, un token de sesión) lo perdía al navegar o recargar. Para un host allow∩js el
padre mantiene, **en RAM y por origen**, el contenido de su `localStorage`, lo siembra en cada
carga y recoge los cambios. Un host no confiable sigue con su almacén efímero por carga (Zero
Knowledge).

## 2. Modelo

- **Base de datos** (`wst_db`): hasta `WST_MAX_ORIGINS` (256) orígenes; cada uno con pares
  clave→valor (cadenas UTF-8) y una **cuota** `WST_QUOTA` de 5 MiB (suma de bytes de claves y
  valores, como Firefox). Al llenarse la tabla de orígenes se descarta el usado hace más
  tiempo (LRU): memoria acotada.
- **Instantánea** (el formato del cable): `[n:u32][klen:u32][key][vlen:u32][val]...` en
  little-endian. `wst_encode` produce la de un origen; `wst_decode` la valida **completa**
  antes de aceptar nada: cuenta ≤ `WST_MAX_KEYS` (65536), longitudes que caben en el buffer,
  total ≤ `WST_QUOTA`, UTF-8 bien formado, sin claves repetidas. Cualquier falla ⇒ -1 y la
  base queda intacta (el worker es hostil).
- `wst_replace(db, origin, blob, len)` reemplaza el contenido del origen por la instantánea
  (así un `removeItem`/`clear` del worker también se refleja).
- Origen = `esquema://host[:puerto]` (lo calcula el llamante; `file://` nunca entra: no es un
  host de confianza).

## 3. API

```c
wst_db *wst_new(void);
void    wst_free(wst_db *db);
int     wst_encode(const wst_db *db, const char *origin, char **out, size_t *len);
int     wst_replace(wst_db *db, const char *origin, const char *blob, size_t len);
int     wst_decode_check(const char *blob, size_t len);          /* validación pura */
size_t  wst_origin_bytes(const wst_db *db, const char *origin);
```

`wst_encode` sobre un origen desconocido da una instantánea vacía válida (`n = 0`).

## 4. Garantías

- Nada toca el disco: el módulo no tiene I/O.
- Toda entrada del worker se valida antes de mutar la base; fuzzeado (`make fuzz-wst`).
- Memoria acotada: `WST_MAX_ORIGINS` × `WST_QUOTA`.

## 5. Integración

- Worker (`js_dom`): `jd_enable_storage(ctx, blob, len)` —solo con `net`— instala un
  `localStorage` sembrado desde la instantánea (los pares entran como **valores**, nunca
  interpolados) que marca un bit de "sucio" en cada escritura; `jd_take_storage` devuelve la
  instantánea completa solo si cambió. `setItem` que excede la cuota lanza
  `QuotaExceededError`, como Firefox.
- `tab`: la semilla viaja en `OP_LOAD` (como las cookies) y la instantánea sucia en cada
  respuesta; el padre la acepta solo si la carga fue de confianza.
- GUI: una `wst_db` por ventana (compartida entre pestañas); siembra antes de cada carga de
  confianza y aplica `wst_replace` con cada instantánea.

## 6. Fuera de alcance

`sessionStorage` compartido por pestaña (sigue efímero por carga), el evento `storage` entre
pestañas, IndexedDB (sigue sin implementar).
