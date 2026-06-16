# Especificación: `disk_store`

> Hito 5 — Zero Knowledge: persistencia cifrada en disco. Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. `tests/test_disk_store.c` debe fallar (no enlaza) hasta que exista
> `src/disk_store.c`.

## 1. Propósito

`disk_store` es el **orquestador de persistencia**: escribe y lee en disco los blobs sellados por
`local_store`, de forma **atómica**, con permisos restrictivos y **fail-closed**. No contiene
lógica criptográfica (esa vive, pura, en `local_store`); aquí solo se cablea la I/O de ficheros a
las funciones de cifrado/descifrado. Cierra el pendiente "persistencia en disco de `local_store`".

Doctrina: el camino por defecto es seguro. El fichero en disco nunca contiene texto plano; una
escritura interrumpida nunca deja el fichero destino a medias (se escribe en un temporal y se
renombra atómicamente); una lectura de un fichero manipulado o con clave incorrecta falla sin
liberar texto plano.

## 2. Decisión de diseño

- **Clave en crudo, no passphrase.** La API recibe la clave de 32 bytes ya derivada (con
  `ls_derive_key` al desbloquear la sesión, **una** vez con Argon2id) y la reutiliza en cada
  lectura/escritura (AEAD rápido). Así no se re-deriva Argon2id en cada operación.
- **Escritura atómica:** `mkstemp` en el **mismo directorio** que el destino (mismo sistema de
  ficheros ⇒ `rename` atómico), permisos `0600`, escritura completa, `fsync` del fichero,
  `rename(tmp, path)`, y `fsync` del directorio (best-effort, para durabilidad ante caída). Ante
  cualquier fallo se borra el temporal y **no** se toca el destino.
- **Lectura acotada:** `fstat` para conocer el tamaño; se rechaza un fichero mayor que
  `LS_OVERHEAD + LS_MAX_PLAINTEXT`. Se lee completo y se pasa a `ls_open`; el buffer cifrado se
  limpia con borrado seguro antes de liberar.
- **Permisos:** `0600` (solo el dueño). El temporal hereda `0600` de `mkstemp`.
- Sin estado global; reentrante. Cada salida tiene un único dueño y `ds_free` la libera.

## 3. Contrato de la API (C)

Definida en `include/disk_store.h` (incluye `local_store.h` por `LS_KEY_LEN` y `ls_aead`).

```c
typedef enum ds_status {
    DS_OK = 0,
    DS_ERR_NULL_ARG,
    DS_ERR_IO,         /* open/read/write/rename/fsync fallaron */
    DS_ERR_TOO_LARGE,  /* fichero o texto plano excede los limites */
    DS_ERR_FORMAT,     /* contenedor invalido (magic/version/...) */
    DS_ERR_AUTH,       /* clave incorrecta o manipulacion */
    DS_ERR_CRYPTO,     /* fallo de sellado/apertura */
    DS_ERR_OOM
} ds_status;

/* Sella plaintext con la clave dada y lo escribe atomicamente en path (0600). */
ds_status ds_write(const char *path, const uint8_t key[LS_KEY_LEN], ls_aead aead,
                   const uint8_t *plaintext, size_t pt_len);

/* Lee y descifra path. Clave incorrecta/manipulacion => DS_ERR_AUTH (sin texto
 * plano). *out es propio; liberar con ds_free. */
ds_status ds_read(const char *path, const uint8_t key[LS_KEY_LEN],
                  uint8_t **out, size_t *out_len);

/* Borrado seguro del buffer devuelto por ds_read (delega en ls_free). */
void ds_free(uint8_t *buf, size_t len);
```

## 4. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `DS_OK` | Operación correcta. |
| `DS_ERR_NULL_ARG` | `path`/`key`/`out` requeridos son `NULL`. |
| `DS_ERR_IO` | Fallo de `mkstemp`/`write`/`fsync`/`rename`/`open`/`read`. |
| `DS_ERR_TOO_LARGE` | `pt_len > LS_MAX_PLAINTEXT`, o fichero leído mayor que el máximo. |
| `DS_ERR_FORMAT` | El fichero no es un contenedor `local_store` válido. |
| `DS_ERR_AUTH` | Tag inválido (clave incorrecta o fichero manipulado). |
| `DS_ERR_CRYPTO` | Fallo inesperado del AEAD/RNG. |
| `DS_ERR_OOM` | Fallo de asignación. |

## 5. Garantías de seguridad

1. **Nada en claro en disco.** Solo se escribe el blob AEAD de `local_store`.
2. **Atomicidad.** El destino se actualiza con `rename` desde un temporal completamente escrito y
   `fsync`-eado; una caída deja el destino intacto (versión vieja) o completo (versión nueva),
   nunca a medias. Ante error se borra el temporal y no se deja basura.
3. **Permisos mínimos.** `0600`.
4. **Fail-closed.** Clave incorrecta, manipulación o formato inválido ⇒ error sin liberar texto
   plano. El buffer cifrado leído se borra de forma segura.
5. **Herencia de garantías cripto.** Confidencialidad/integridad/borrado seguro vienen de
   `local_store`; este módulo no añade superficie criptográfica.

## 6. Matriz de pruebas

`tests/test_disk_store.c` (cmocka, sobre un directorio temporal real):
- **Round-trip:** `ds_write` luego `ds_read` recupera el texto plano exacto (AES-GCM y ChaCha).
- **Permisos:** tras `ds_write`, `stat(path).st_mode & 0777 == 0600`.
- **Sin temporales:** tras `ds_write` el directorio contiene solo el fichero destino (no quedan
  `*.XXXXXX`).
- **Atomicidad/sobrescritura:** un segundo `ds_write` reemplaza el contenido; `ds_read` lee el
  nuevo.
- **Clave incorrecta** ⇒ `DS_ERR_AUTH` (sin texto plano).
- **Manipulación en disco:** voltear un byte del fichero ⇒ `DS_ERR_AUTH`/`DS_ERR_FORMAT`.
- **Fichero inexistente** ⇒ `DS_ERR_IO`. **Args NULL** ⇒ `DS_ERR_NULL_ARG`.
- **Texto plano vacío** round-trip correcto.

## 7. Fuera de alcance

- Esquema de datos de los registros (marcadores, caché, credenciales) y su versionado.
- Gestión/rotación de la clave maestra y desbloqueo de sesión (UI/orquestador).
- Bloqueo de ficheros entre procesos (`flock`) y acceso concurrente multi-proceso.
- Confinamiento del acceso a rutas (eso lo da `os_sandbox`/Landlock).
