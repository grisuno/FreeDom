# Especificación: `local_store`

> Hito 5 — Zero Knowledge: estado local cifrado. Estado: **SPEC + TEST (rojo)**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_local_store.c` debe fallar (no
> enlaza) hasta que exista `src/local_store.c`.

## 1. Propósito

`local_store` cifra el **estado local** del navegador (caché, marcadores, credenciales) en reposo,
cumpliendo el principio **Zero Knowledge**: nada legible en disco, sin historial en claro. Es la
lógica criptográfica pura (sin I/O de filesystem/red; solo lee el RNG del SO, inevitable para
generar sal/nonce) que un orquestador de persistencia usará para sellar/abrir blobs antes de
escribirlos/leerlos.

Cumple la **Política criptográfica concreta** del contrato:
- AEAD: **AES-256-GCM** (por defecto) o **ChaCha20-Poly1305**.
- KDF: **Argon2id**, con **sal única** generada por sellado (más fuerte que por dispositivo).
- *Fail-closed*: si la autenticación falla (clave incorrecta o manipulación), **no se libera texto
  plano**; se devuelve `LS_ERR_AUTH`.

Se apoya en **OpenSSL 3.6+ nativo** (verificado en este host: `ARGON2ID`, `id-aes256-GCM`,
`ChaCha20-Poly1305` en el provider `default`). Sin `liboqs`.

## 2. Decisión de diseño

- **Contenedor autodescriptivo.** El blob sellado lleva su propia cabecera (magic, versión, ids de
  AEAD/KDF, sal, nonce) de modo que `ls_open*` no necesita parámetros fuera de banda salvo la
  clave/passphrase. La cabecera completa es el **AAD** del AEAD: manipular cualquier byte de
  cabecera (incl. sal/nonce/ids) invalida la autenticación.
- **Dos niveles de API.** Clave cruda de 32 bytes (`ls_seal`/`ls_open`) para quien ya gestiona la
  clave; y passphrase (`ls_seal_passphrase`/`ls_open_passphrase`) que deriva con Argon2id y guarda
  la sal en el contenedor.
- **Nonce aleatorio por sellado** (`RAND_bytes`): nunca se reutiliza un par (clave, nonce).
- **Parámetros Argon2id fijados en v1** (mínimos interactivos recomendados por OWASP): memoria
  19456 KiB (19 MiB), `t = 2` pasadas, `p = 1` lane. Documentados; elevables en una versión futura
  del contenedor.
- **Borrado seguro.** `ls_free` hace `OPENSSL_cleanse` antes de `free`; las claves derivadas y
  buffers temporales se limpian siempre.
- Sin estado global; reentrante. Cada salida tiene un único dueño y un único liberador (`ls_free`).

## 3. Formato del contenedor (v1)

```
offset  tam  campo
0       4    magic = "FRZS"            (Freedom Zero-knowledge Store)
4       1    version = 1
5       1    aead_id  (1=AES-256-GCM, 2=ChaCha20-Poly1305)
6       1    kdf_id   (0=ninguno/clave cruda, 1=Argon2id)
7       1    reserved = 0
8       16   salt                       (cero si kdf_id==0)
24      12   nonce
36      N    ciphertext                 (N == longitud del texto plano)
36+N    16   tag (GCM/Poly1305)
```

Cabecera = 36 bytes (`LS_HEADER_LEN`); sobrecarga total = 52 bytes (`LS_OVERHEAD`). El AAD del
AEAD son los 36 bytes de cabecera. El texto plano vacío (`pt_len == 0`) está permitido: produce un
contenedor de 52 bytes que autentica "vacío".

## 4. Contrato de la API (C)

Definida en `include/local_store.h`.

```c
#define LS_KEY_LEN     32u
#define LS_SALT_LEN    16u
#define LS_NONCE_LEN   12u
#define LS_TAG_LEN     16u
#define LS_HEADER_LEN  36u
#define LS_OVERHEAD    52u   /* LS_HEADER_LEN + LS_TAG_LEN */
#define LS_MAX_PLAINTEXT ((size_t)(64u * 1024u * 1024u))

typedef enum ls_aead { LS_AEAD_AES256_GCM = 1, LS_AEAD_CHACHA20_POLY1305 = 2 } ls_aead;

typedef enum ls_status {
    LS_OK = 0,
    LS_ERR_NULL_ARG,
    LS_ERR_TOO_LARGE,   /* pt_len > LS_MAX_PLAINTEXT */
    LS_ERR_FORMAT,      /* contenedor malformado: magic/version/aead/kdf/longitud */
    LS_ERR_AUTH,        /* autenticacion fallida: clave incorrecta o manipulacion */
    LS_ERR_KDF,         /* derivacion Argon2id fallida/indisponible */
    LS_ERR_CRYPTO,      /* fallo inesperado del AEAD/RNG */
    LS_ERR_OOM
} ls_status;

/* Argon2id (parametros v1 fijos). out_key recibe LS_KEY_LEN bytes. */
ls_status ls_derive_key(const uint8_t *passphrase, size_t pass_len,
                        const uint8_t *salt, size_t salt_len,
                        uint8_t out_key[LS_KEY_LEN]);

/* Sella con clave cruda (kdf_id=0). *out es propio; liberar con ls_free. */
ls_status ls_seal(const uint8_t key[LS_KEY_LEN], ls_aead aead,
                  const uint8_t *plaintext, size_t pt_len,
                  uint8_t **out, size_t *out_len);

/* Abre lo sellado con ls_seal. Clave incorrecta/manipulacion => LS_ERR_AUTH. */
ls_status ls_open(const uint8_t key[LS_KEY_LEN],
                  const uint8_t *blob, size_t blob_len,
                  uint8_t **out, size_t *out_len);

/* Sella con passphrase: sal aleatoria + Argon2id, guardada en el contenedor. */
ls_status ls_seal_passphrase(const uint8_t *passphrase, size_t pass_len, ls_aead aead,
                             const uint8_t *plaintext, size_t pt_len,
                             uint8_t **out, size_t *out_len);

/* Abre lo sellado con ls_seal_passphrase (kdf_id debe ser Argon2id). */
ls_status ls_open_passphrase(const uint8_t *passphrase, size_t pass_len,
                             const uint8_t *blob, size_t blob_len,
                             uint8_t **out, size_t *out_len);

/* Borrado seguro: OPENSSL_cleanse(buf,len) y luego free. Idempotente con NULL. */
void ls_free(uint8_t *buf, size_t len);
```

## 5. Tabla de errores

| Código | Condición |
| :-- | :-- |
| `LS_OK` | Operación correcta. |
| `LS_ERR_NULL_ARG` | Algún puntero requerido es `NULL` (con `pt_len>0`). |
| `LS_ERR_TOO_LARGE` | `pt_len > LS_MAX_PLAINTEXT`. |
| `LS_ERR_FORMAT` | `blob_len < LS_OVERHEAD`, magic/versión/aead/kdf inválidos. |
| `LS_ERR_AUTH` | El tag no verifica (clave incorrecta o blob manipulado). No se libera texto plano. |
| `LS_ERR_KDF` | Argon2id no disponible o falló. |
| `LS_ERR_CRYPTO` | Fallo del cifrador o del RNG. |
| `LS_ERR_OOM` | Fallo de asignación. |

## 6. Garantías de seguridad

1. **Confidencialidad + integridad (AEAD).** Sin la clave correcta no se obtiene el texto plano ni
   se puede manipular el blob sin detección. La cabecera es AAD: ids/sal/nonce están autenticados.
2. **Fail-closed.** Cualquier fallo de autenticación devuelve `LS_ERR_AUTH` sin liberar ni un byte
   de texto plano descifrado.
3. **Derivación robusta.** Argon2id memory-hard con sal única por blob: resistente a fuerza bruta
   y a tablas precomputadas; dos sellados de la misma passphrase dan claves/blobs distintos.
4. **Sin reutilización de nonce.** Nonce aleatorio de 96 bits por sellado.
5. **Higiene de memoria.** Claves derivadas y buffers se limpian con `OPENSSL_cleanse`; `ls_free`
   borra antes de liberar. ASan/UBSan limpios.
6. **Zero Knowledge.** El blob no revela nada del contenido ni de la passphrase; solo metadatos de
   formato (magic/versión/algoritmos) y la longitud del texto plano.

## 7. Matriz de pruebas

`tests/test_local_store.c` (cmocka):
- **Round-trip clave cruda:** `ls_seal` → `ls_open` recupera el texto plano exacto (AES-GCM y
  ChaCha20-Poly1305).
- **Round-trip passphrase:** `ls_seal_passphrase` → `ls_open_passphrase` recupera el texto.
- **Passphrase incorrecta** ⇒ `LS_ERR_AUTH` (sin texto plano).
- **Clave cruda incorrecta** ⇒ `LS_ERR_AUTH`.
- **Manipulación:** voltear un bit del ciphertext, del tag, del nonce, del salt o de un id de
  cabecera ⇒ `LS_ERR_AUTH` o `LS_ERR_FORMAT` (nunca texto plano).
- **No determinista:** dos sellados de la misma entrada difieren (nonce/sal aleatorios).
- **Texto plano vacío** sella y abre correctamente (longitud 0).
- **Formato:** `blob_len < LS_OVERHEAD`, magic erróneo, versión/aead/kdf inválidos ⇒ `LS_ERR_FORMAT`.
- **`ls_derive_key` determinista:** misma passphrase + misma sal ⇒ misma clave; distinta sal ⇒
  clave distinta.
- **Args NULL** ⇒ `LS_ERR_NULL_ARG`; `pt_len > LS_MAX_PLAINTEXT` ⇒ `LS_ERR_TOO_LARGE`.
- **`ls_free(NULL,0)`** no crashea.

## 8. Fuera de alcance

- Persistencia en disco (escritura/lectura de ficheros, rutas, permisos): es del orquestador.
  `local_store` solo produce/consume blobs en memoria.
- Rotación de claves, versionado de esquema de datos, formato de los registros (marcadores, etc.).
- Gestión de la passphrase maestra / desbloqueo de sesión (UI/orquestador).
- `landlock`/confinamiento del acceso a ficheros (otro pendiente del Hito 5).
