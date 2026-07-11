# Especificación: `profile`

> Hito 10 — Persistencia de preferencias, marcadores e historial (orquestador de I/O).
> Metodología: SDD + TDD. `tests/test_profile.c` debe fallar (no enlaza) hasta que exista
> `src/profile.c`.

## 1. Propósito

`profile` cablea el estado puro de `prefs` al disco **cifrado**: deriva una clave por
dispositivo, sella el texto de `prefs_format` con `disk_store` (AEAD + escritura atómica
0600) y lo reabre al arrancar. Cierra el pendiente del Hito 10: hoy nada persiste entre
sesiones (tema, zoom, toggles, Tor/I2P se pierden al cerrar) y no existen marcadores.

Cadena de módulos (cada uno ya cerrado y probado):

```
prefs (puro)  ->  profile (este)  ->  disk_store (I/O atomica)  ->  local_store (AEAD+Argon2id)
```

## 2. Decisiones de diseño

- **Clave por dispositivo, sin passphrase (v1).** Un navegador que pide contraseña en cada
  arranque no se usa a diario. Se genera **una vez** un fichero de clave
  `<dir>/profile.key` (0600) con 48 bytes del RNG del SO: 16 de **sal** + 32 de secreto.
  La clave AEAD se deriva con `ls_derive_key(secreto, sal)` — **Argon2id con sal única por
  dispositivo**, como manda la política criptográfica — una sola vez por arranque, y se
  reutiliza en cada load/save (AEAD rápido).
- **Honestidad del modelo de amenaza:** el fichero de clave vive junto al blob (como el
  perfil de cualquier navegador sin master password). Protege el contenido ante fugas del
  `prefs.bin` solo (backups parciales, sync de directorios), y mantiene el invariante
  Zero Knowledge "**nada legible en disco**"; NO resiste a un atacante con acceso total al
  directorio. El desbloqueo con passphrase maestra (que sí resiste) queda en el roadmap y
  este diseño lo permite sin migración (mismo contenedor `local_store`).
- **Fail closed, nunca clobber.** Un `profile.key` de tamaño incorrecto ⇒ error (jamás se
  regenera pisando la clave de un `prefs.bin` existente). Un `prefs.bin` que no autentica
  (clave ajena / manipulación) ⇒ error **y el llamador debe deshabilitar el guardado** para
  no destruir el fichero de otro dispositivo/usuario; la sesión sigue con defaults en
  memoria. Un `prefs.bin` ausente es el primer arranque: OK con defaults.
- **Escrituras atómicas heredadas de `ds_write`** (tmp + fsync + rename, 0600). El texto
  plano intermedio se libera con borrado seguro (`ls_free`).
- Sin estado global; el `profile_ctx` es del llamador. `profile_close` limpia la clave.

## 3. Contrato de la API (C)

Definida en `include/profile.h` (incluye `prefs.h` y `local_store.h`).

```c
#define PROFILE_KEY_FILE   "profile.key"  /* 16B sal + 32B secreto, 0600 */
#define PROFILE_PREFS_FILE "prefs.bin"    /* contenedor local_store sellado */

typedef enum profile_status {
    PROFILE_OK = 0,
    PROFILE_ERR_NULL_ARG,
    PROFILE_ERR_DIR,     /* dir NULL/vacio/demasiado largo o inexistente */
    PROFILE_ERR_KEY,     /* keyfile corrupto (tamano) o KDF/RNG fallo */
    PROFILE_ERR_IO,      /* fallo de lectura/escritura */
    PROFILE_ERR_AUTH,    /* prefs.bin manipulado o de otra clave (no clobber) */
    PROFILE_ERR_FORMAT,  /* contenedor o texto de prefs invalido */
    PROFILE_ERR_OOM
} profile_status;

typedef struct profile_ctx {
    char    dir[1024];
    uint8_t key[LS_KEY_LEN];
    int     ready;
} profile_ctx;

/* Abre el perfil en dir (debe existir; el llamador lo crea 0700). Crea el keyfile
 * si falta (0600, escritura atomica); si existe con tamano incorrecto falla cerrado
 * (PROFILE_ERR_KEY, nunca lo pisa). Deriva la clave (Argon2id) y deja ctx listo. */
profile_status profile_open(profile_ctx *ctx, const char *dir);

/* Carga y descifra prefs.bin sobre un out YA inicializado (prefs_init). Ausente =>
 * PROFILE_OK con defaults (primer arranque). Manipulado/clave ajena =>
 * PROFILE_ERR_AUTH y out queda en defaults. */
profile_status profile_load(const profile_ctx *ctx, prefs_state *out);

/* Serializa p y lo escribe sellado y atomico en prefs.bin (0600). */
profile_status profile_save(const profile_ctx *ctx, const prefs_state *p);

/* Limpia la clave del ctx (borrado seguro). Idempotente; NULL-safe. */
void profile_close(profile_ctx *ctx);
```

## 4. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `PROFILE_OK` | Operación correcta (incluye `load` sin fichero: primer arranque). |
| `PROFILE_ERR_NULL_ARG` | `ctx`/`dir`/`out`/`p` requeridos son NULL, o ctx no `ready`. |
| `PROFILE_ERR_DIR` | `dir` vacío/demasiado largo/inexistente. |
| `PROFILE_ERR_KEY` | Keyfile con tamaño ≠ 48, o Argon2id/RNG fallaron. |
| `PROFILE_ERR_IO` | Fallo de open/read/write/rename (vía `DS_ERR_IO`). |
| `PROFILE_ERR_AUTH` | Tag AEAD inválido: manipulación o clave de otro dispositivo. |
| `PROFILE_ERR_FORMAT` | Contenedor no-`local_store` o texto de prefs con magia inválida. |
| `PROFILE_ERR_OOM` | Fallo de asignación. |

## 5. Garantías de seguridad (Dado-Cuando-Entonces)

- **Dado** un perfil recién abierto, **cuando** se guarda, **entonces** en disco solo hay
  el contenedor AEAD (`ds_write`): ni una URL ni un título legibles (`grep` del plaintext
  sobre el fichero falla), permisos 0600, sin temporales huérfanos.
- **Dado** un `prefs.bin` con un byte volteado, **cuando** se carga, **entonces**
  `PROFILE_ERR_AUTH` y el estado del llamador queda en defaults (fail closed, sin texto).
- **Dado** un `profile.key` truncado/crecido, **cuando** se abre el perfil, **entonces**
  `PROFILE_ERR_KEY` y el keyfile **no** se modifica (no clobber).
- **Dado** dos aperturas del mismo dir, **cuando** una guarda y la otra carga, **entonces**
  la clave derivada es la misma y el round-trip reproduce el estado (la sal vive en el
  keyfile, no se regenera).
- **Dado** el primer arranque (sin `prefs.bin`), **cuando** se carga, **entonces**
  `PROFILE_OK` y defaults (jamás error por ausencia).
- La clave en memoria se limpia en `profile_close` (OPENSSL_cleanse) y el texto plano
  intermedio se libera con `ls_free`.

## 6. Matriz de pruebas

`tests/test_profile.c` (CMocka, sobre `mkdtemp` real): open crea keyfile 48B 0600;
load-sin-fichero ⇒ defaults OK; save→load round-trip completo (prefs + marcadores +
historial); segunda apertura re-deriva la misma clave (save con ctx1, load con ctx2);
keyfile corrupto ⇒ `PROFILE_ERR_KEY` sin modificarlo; byte volteado en `prefs.bin` ⇒
`PROFILE_ERR_AUTH`; keyfile ajeno ⇒ `PROFILE_ERR_AUTH`; nada legible en el blob
(memmem del URL guardado falla); dir inexistente ⇒ `PROFILE_ERR_DIR`; args NULL;
`profile_close` idempotente.

## 7. Fuera de alcance

- Passphrase maestra / desbloqueo interactivo (roadmap; mismo contenedor, sin migración).
- Bloqueo entre procesos (`flock`) y merge de perfiles concurrentes (última escritura gana).
- Rotación de clave; sync remoto.
- Decidir *qué* se persiste y *cuándo* (eso es de la GUI: aplica env-overrides, llama
  save en cada cambio y deshabilita el guardado ante `PROFILE_ERR_AUTH`).
