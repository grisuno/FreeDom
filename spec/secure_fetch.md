# Especificación: `secure_fetch`

> Hito 1 — Núcleo de Red y Criptografía. Estado: **VERDE + INTEGRACIÓN CERRADA**.
> Metodología: SDD + TDD. Esta spec es el contrato; `tests/test_secure_fetch.c` (24 tests,
> ASan/UBSan limpio) cubre los validadores puros y `tests/itest_secure_fetch.c` (`make itest`)
> ejerce la ruta de red real contra un endpoint que negocia `X25519MLKEM768` (Cloudflare).

## 1. Propósito

`secure_fetch` realiza una petición HTTPS GET bajo garantías criptográficas estrictas y
post-cuánticas. Es el único punto de salida a la red del navegador: ningún otro módulo abre
sockets. Implementa el principio *Secure by Default* — la configuración insegura no es
representable en la API.

## 2. Decisión de stack (corrección 2026)

OpenSSL **3.5+** expone PQC de forma **nativa** en el `default` provider. Verificado en este
host (OpenSSL 3.6.2):

- Grupos KE: `X25519MLKEM768`, `MLKEM768`, `SecP256r1MLKEM768`, … (`@ default`).
- Firmas: `ML-DSA-44/65/87`, familia `SLH-DSA` completa (`@ default`).
- `curl 8.19.0` enlaza contra este mismo OpenSSL.

**Consecuencia:** se elimina la dependencia de `liboqs` + `oqsprovider` del plan original.
Menos superficie de ataque, una dependencia menos que auditar. El transporte es
`libcurl` (HTTPS estricto) sobre `OpenSSL 3.6.2`.

## 3. Política de aplicación PQC (por niveles)

| Política | Key Exchange | Firma de la cadena de certificados |
| :-- | :-- | :-- |
| `SF_POLICY_PQ_HYBRID_KE` *(por defecto)* | **Exige** grupo PQ-híbrido | Validación PKI clásica completa; firma PQ no requerida |
| `SF_POLICY_STRICT_PQ` | **Exige** grupo PQ-híbrido | **Exige además** una firma PQ (`ML-DSA`/`SLH-DSA`) en la cadena verificada |
| `SF_POLICY_PERMISSIVE` | **Exige** grupo PQ-híbrido | Permite primitivas débiles (RSA 2048, SHA-1) como **override explícito del usuario** |
| `SF_POLICY_ALLOW_CLASSICAL_KE` | **Acepta** KE clásico (no-PQ) | Validación PKI clásica completa (igual que el defecto; **no** se relaja el cert) |
| `SF_POLICY_ALLOWLISTED_INSECURE` | **Acepta** KE clásico; **mínimo TLS 1.2** | Permite primitivas débiles-pero-válidas (RSA 2048, SHA-1); la cadena se **sigue autenticando** (VERIFYPEER) |

`SF_POLICY_ALLOWLISTED_INSECURE` es el **override de soberanía por host**: el usuario pone un host en
`allow.conf` y el orquestador, si el intento estricto falla, reintenta con esta política. Baja el piso
de TLS a **1.2** (1.3 sigue siendo el techo, así que se prefiere), acepta KE clásico y certs débiles
pero **válidos**. Lo que **no** se relaja es la autenticidad: `CURLOPT_SSL_VERIFYPEER` sigue activo, así
que se llega al sitio real sobre cripto vieja, nunca a un impostor. Por debajo de TLS 1.2 se rechaza
(`SF_ERR_TLS_VERSION`). El orquestador **debe** avisar (toast). Es el caso de sitios solo-TLS-1.2 como
Hacker News: secure by default, pero el usuario es soberano sobre sus propios hosts (no es dictadura).

`SF_POLICY_ALLOW_CLASSICAL_KE` es el **fallback de navegabilidad**: cuando un host no puede negociar
un KE híbrido PQ, el defecto devuelve `SF_ERR_KEM_NOT_PQ` (status 4) y, en vez de detener la
navegación, el orquestador reintenta con esta política, que mantiene TLS 1.3 y la validación completa
del certificado y **solo** relaja la exigencia PQ del intercambio de claves. El orquestador **debe**
avisar al usuario del *downgrade* (toast). Decisión del dueño que se desvía conscientemente del
Principio 5 para que el navegador sea usable en la web no-PQ de 2026; nunca se aplica en silencio.

> Para que un host no-PQ produzca un `SF_ERR_KEM_NOT_PQ` *limpio* (en vez de un fallo opaco de
> handshake), el cliente ofrece grupos clásicos además del híbrido: `SF_DEFAULT_KEX_GROUPS =
> "X25519MLKEM768:X25519:secp256r1"` (PQ preferido). Ofrecer un grupo clásico no debilita las
> políticas estrictas: un grupo *negociado* clásico sigue siendo rechazado por `sf_check_group_is_pq`.

Justificación: el KE híbrido es desplegable hoy y es lo que neutraliza *Harvest-Now,
Decrypt-Later*. Las firmas PQC aún no existen en la Web PKI pública en 2026; exigirlas por
defecto rompería la conectividad. `STRICT_PQ` queda disponible para entornos controlados
(infra propia, redes cerradas) donde el extremo sí presenta certificados PQ.

En **ambas** políticas seguras (`PQ_HYBRID_KE` y `STRICT_PQ`) se rechazan primitivas débiles.
El rechazo **RSA < 3072** se aplica al **certificado de sitio (end-entity / leaf)**: es la
clave que el operador del sitio controla y la que autentica la sesión. Los intermedios de CA
con RSA 2048 son universales en la Web PKI pública de 2026 (Google "WR2", Let's Encrypt
R10/R11, …) y quedan fuera del control del sitio, por lo que **no** se les exige RSA ≥ 3072;
exigirlo bloquearía la práctica totalidad de la web pública sin beneficio real de seguridad
(la confidencialidad frente a *Harvest-Now-Decrypt-Later* la aporta el KE híbrido, no la firma
de la CA). En cambio **SHA-1 es fatal en cualquier posición de la cadena**: una firma SHA-1 es
un riesgo de falsificación real. `SF_POLICY_PERMISSIVE` mantiene los requisitos de TLS 1.3 y KE
híbrido, pero relaja la política de firma para que un usuario informado pueda añadir una
excepción por host (actualmente en sesión; persistencia mediante `local_store` planificada).

## 4. Contrato de la API

Definida en `include/secure_fetch.h`. Resumen:

```c
sf_config   sf_config_default(void);
const char *sf_user_agent_or_default(const char *ua); /* ua/""=>SF_DEFAULT_USER_AGENT, puro */

/* Validadores puros (sin I/O) — superficie principal de pruebas unitarias. */
sf_status sf_validate_url(const char *url);
sf_status sf_check_tls_version(const char *negotiated_version);
sf_status sf_check_group_is_pq(const char *negotiated_group);
sf_status sf_check_chain_policy(const sf_chain_info *chain, sf_policy policy);

/* Redirecciones — lógica pura (sin I/O), también verificable directamente. */
int       sf_is_redirect_code(long http_code);
sf_status sf_parse_location_header(const char *header_line, char *out, size_t outsz);
sf_status sf_resolve_redirect(const char *base_url, const char *location,
                              char *out, size_t outsz);

/* Orquestadores con I/O. GET y POST comparten un único motor (sf_perform) que aplica
 * IDÉNTICA la política TLS/PQ/cadena: el método no cambia cómo se juzga la conexión. */
sf_status sf_get(const char *url, const sf_config *cfg, sf_response *out);
sf_status sf_get_follow(const char *url, const sf_config *cfg, sf_response *out,
                        int max_redirects);
sf_status sf_post(const char *url, const sf_config *cfg,
                  const void *body, size_t body_len, const char *content_type,
                  sf_response *out);
void      sf_response_free(sf_response *resp);
```

**Identidad de red normalizada (anti-fingerprinting).** `SF_DEFAULT_USER_AGENT` **es** la identidad
anti-fingerprinting (`FP_USER_AGENT` de `[[anti_fp]]`): una cadena común de **Firefox/Linux**, no
`"Freedom/0.1"`. El antiguo `"Freedom/0.1"` quedó degradado a mera marca de producto y **nunca** se
envía por la red — una UA con `"Freedom"` es una huella única y dispara la detección de bots (rompe
Google, Cloudflare, etc.). `sf_config.user_agent` (NULL o `""` ⇒ el default) fija la cabecera; lo
resuelve la función pura `sf_user_agent_or_default` (un único sitio probado). El usuario puede
sobrescribirla por sesión en el menú. Como ahora el default de red **coincide** con
`navigator.userAgent`, la identidad on-the-wire y la visible por JS son la misma (la discrepancia
era en sí misma huella). Además, **toda** petición (GET y POST) envía un `Accept-Language`
normalizado (`FP_ACCEPT_LANGUAGE_HEADER`, `"en-US,en;q=0.5"`): omitirlo es señal, y el locale real
del sistema no debe filtrarse.

**Proxy de anonimato (Tor/I2P, a nivel de socket).** `sf_config.proxy_type` +
`sf_config.proxy_address` enrutan la petición por un proxy local (Principio 3). `SF_PROXY_NONE`
(defecto) = conexión directa; `SF_PROXY_SOCKS5H` = SOCKS5 con **DNS remoto** (Tor: sin fuga de DNS,
resuelve `.onion`); `SF_PROXY_HTTP` = proxy HTTP (I2P). `secure_fetch` solo **aplica** el proxy
(`CURLOPT_PROXY`/`CURLOPT_PROXYTYPE`); **quién** lo elige es el módulo puro `[[net_realm]]` en el
orquestador (clasifica el realm, decide la ruta, falla cerrado). Con un proxy fijado, libcurl nunca
lo evita: no hay fallback directo que desanonimice. La política TLS/PQ/cadena es **idéntica** con o
sin proxy (https-only y TLS 1.3 también para `.onion`). Para un request overlay http
(`allow_overlay_http`, p. ej. un eepsite `.i2p`) la política TLS se omite (no hay TLS; el overlay da
la seguridad) y los redirects se resuelven en esquema http (reusando el resolver https mapeando
http↔https); un salto explícito a `https` se rechaza (un eepsite no debe sacarte del overlay a
clearnet: fail-closed).

**POST (`sf_post`).** Envía `body` (`body_len` bytes) con `content_type` (NULL ⇒
`application/x-www-form-urlencoded`). Reusa el mismo `sf_perform` que `sf_get`, así que exige TLS 1.3
+ KE híbrido PQ + política de cadena igual que un GET (Zero Trust: un POST inseguro **no es
representable**; el esquema se valida antes de abrir socket). No sigue redirecciones (el llamante
inspecciona `http_code`/`location` y decide). `body == NULL` con `body_len != 0` ⇒ `SF_ERR_NULL_ARG`.
El plan de envío lo construye el módulo puro `form` (`spec/form.md`).

Diseño orientado a prueba: la lógica de seguridad vive en **funciones puras** sin red,
verificables directamente. `sf_get` solo orquesta: configura el transporte, ejecuta la
petición e invoca a los validadores sobre el estado negociado.

### Entradas

- `url`: cadena NUL-terminada. **Debe** comenzar por `https://`. Se rechaza todo lo demás
  (`http`, `file`, `data`, `javascript`, `ftp`, ausencia de esquema).
- `cfg`: configuración. `NULL` ⇒ se usan los valores de `sf_config_default()`
  (*secure by default*: el caso por defecto es el seguro).
- `out`: estructura de salida propiedad del llamante; el contenido lo asigna la función.

### Salidas

`sf_response`:
- `status`: resultado (ver tabla §5).
- `http_code`: código HTTP si hubo respuesta.
- `tls_version`: p. ej. `"TLSv1.3"` (propiedad de la struct).
- `negotiated_group`: p. ej. `"X25519MLKEM768"` (propiedad de la struct).
- `body` / `body_len`: cuerpo acotado por `max_body_bytes`; `body` lleva NUL final por
  conveniencia (`body_len` no lo cuenta).
- `location`: valor crudo de la cabecera `Location` si la respuesta la trae (propiedad de la
  struct); `NULL` si no hubo. Es un **dato con procedencia**, nunca una instrucción: no se
  sigue automáticamente dentro de `sf_get`.
- `content_type`: valor de la cabecera `Content-Type` (p. ej. `"text/html; charset=utf-8"`),
  vía `CURLINFO_CONTENT_TYPE`; `NULL` si el servidor la omitió. Lo consume la decisión pura
  **render-vs-download** (`download`); nunca se confía para ejecutar.
- `content_disposition`: valor crudo de la cabecera `Content-Disposition` (capturado en el
  `header_cb`), o `NULL`. Es **contenido hostil con procedencia**: su `filename` se sanea
  fail-closed antes de cualquier uso en disco (ver `spec/download.md`).

Ambos campos son additivos (solo lectura de cabeceras de respuesta): no cambian ninguna
decisión de TLS/PQ/cadena. En `sf_get_follow`, cada hop intermedio se libera con
`sf_response_free`; el del hop final sobrevive, así que `content_type`/`content_disposition`
reflejan la respuesta que produjo el cuerpo.

`sf_response_free` libera y pone a cero todos los punteros. Es **idempotente** y seguro
sobre una struct inicializada a cero o liberada dos veces.

## 5. Tabla de errores (garantías)

| Código | Condición |
| :-- | :-- |
| `SF_OK` | Petición completada bajo todas las garantías de la política activa. |
| `SF_ERR_NULL_ARG` | `url == NULL` o `out == NULL`. |
| `SF_ERR_INVALID_URL` | URL ausente, malformada, o esquema distinto de `https`. |
| `SF_ERR_TLS_VERSION` | Protocolo negociado por debajo de TLS 1.3. |
| `SF_ERR_KEM_NOT_PQ` | Grupo KE negociado no es PQ-híbrido (clásico puro **o** PQ puro). |
| `SF_ERR_WEAK_ALGO` | Certificado de sitio (leaf) con RSA < 3072, **o** algún certificado de la cadena firmado con SHA-1. |
| `SF_ERR_CERT_INVALID` | La verificación de la cadena de certificados falló. |
| `SF_ERR_CERT_NOT_PQ` | Política `STRICT_PQ`: ningún certificado de la cadena usa firma PQ. |
| `SF_ERR_TOO_LARGE` | Cuerpo de respuesta superó `max_body_bytes`. |
| `SF_ERR_NETWORK` | Fallo de transporte (conexión / lectura / timeout). |
| `SF_ERR_OOM` | Fallo de asignación de memoria. |
| `SF_ERR_TOO_MANY_REDIRECTS` | `sf_get_follow` superó `max_redirects` saltos. |
| `SF_ERR_INTERNAL` | El transporte devolvió un estado inesperado. |

## 6. Semántica de los validadores puros

- `sf_validate_url`: `NULL` ⇒ `SF_ERR_INVALID_URL`. Solo se acepta el prefijo `https://`
  (case-insensitive) seguido de al menos un carácter de host. Cualquier otro esquema ⇒
  `SF_ERR_INVALID_URL`.
- `sf_check_tls_version`: acepta exactamente `"TLSv1.3"`. `"TLSv1.2"`, versiones inferiores,
  `NULL` o cadena no reconocida ⇒ `SF_ERR_TLS_VERSION`.
- `sf_check_group_is_pq`: acepta solo grupos **híbridos** que combinan KEM clásico + ML-KEM
  (`X25519MLKEM768`, `SecP256r1MLKEM768`, `X448MLKEM1024`, `SecP384r1MLKEM1024`). Rechaza
  clásicos puros (`x25519`, `secp256r1`) **y** PQ puros (`MLKEM768`) ⇒ `SF_ERR_KEM_NOT_PQ`.
  Rechazar el PQ puro es deliberado: si ML-KEM cayera, el componente clásico debe resistir.
- `sf_check_chain_policy`: aplica los rechazos de primitiva débil en toda política — SHA-1
  (en cualquier cert de la cadena) y RSA < 3072 (`chain->rsa_bits`, que `inspect_chain` rellena
  solo con la clave del leaf); en `STRICT_PQ` exige además firma PQ en la cadena.
- `sf_is_redirect_code`: devuelve 1 para 301, 302, 303, 307 y 308; 0 en cualquier otro caso.
- `sf_parse_location_header`: extrae el valor de una línea de cabecera `Location` (nombre
  case-insensitive, espacios iniciales y `CR`/`LF` finales recortados). `SF_OK` solo si la
  línea es una cabecera `Location` con valor no vacío que cabe en `out`; en otro caso
  `SF_ERR_INVALID_URL`.
- `sf_resolve_redirect`: resuelve un destino de redirección contra la URL base y **siempre**
  produce una URL `https://` absoluta o falla (fail-closed). Casos: destino absoluto
  `https://…` (se usa tal cual); `http://…` y cualquier otro esquema (`javascript:`, `data:`,
  `ftp:`) ⇒ `SF_ERR_INVALID_URL` (rechazo de *downgrade* a texto claro y de esquemas
  peligrosos); relativo a esquema `//host/p` ⇒ `https://host/p`; ruta absoluta `/p` ⇒ origen
  de la base + `/p`; ruta relativa ⇒ directorio de la base + destino. El resultado se valida
  con `sf_validate_url` antes de devolverse.

## 6bis. Política de redirecciones (`sf_get_follow`)

Por **Zero Trust**, `sf_get` nunca sigue una redirección por sí mismo: `CURLOPT_FOLLOWLOCATION`
está desactivado. Si curl siguiera los saltos internamente, solo se capturaría el estado TLS
del primer salto y los intermedios escaparían a la política PQ/TLS. En su lugar, `sf_get`
expone el `Location` como dato y `sf_get_follow` orquesta el seguimiento:

1. Llama a `sf_get` sobre la URL actual — esto **re-aplica la política completa** (TLS 1.3,
   KE híbrido, cadena) en *cada* salto.
2. Si el código no es de redirección (`sf_is_redirect_code`) o no hay `Location`, devuelve la
   respuesta tal cual.
3. Si hay redirección, resuelve el destino con `sf_resolve_redirect` (que rechaza el
   *downgrade* a `http://` y los esquemas no `https`), libera la respuesta intermedia y repite.
4. Acota a `max_redirects` saltos (`SF_DEFAULT_MAX_REDIRECTS` = 10); excederlos ⇒
   `SF_ERR_TOO_MANY_REDIRECTS`. Esto neutraliza bucles y cadenas de redirección abusivas.

`sf_get_follow` no comparte estado entre saltos salvo la URL resuelta: cada salto es una
conexión nueva auditada de cero.

## 7. Garantías de memoria

- Sin estado global mutable; reentrante.
- Toda asignación tiene un dueño único; `sf_response_free` es el único liberador y es
  idempotente.
- Ruta de error no asigna memoria de cuerpo (sin fugas en el camino de fallo).
- El cuerpo está acotado por `max_body_bytes` antes de asignarse — sin crecimiento ilimitado.
- Objetivo de auditoría: `valgrind` y `-fsanitize=address,undefined` limpios.

## 8. Matriz de pruebas (`tests/test_secure_fetch.c`)

Las tres exigencias del Hito 1 mapean así:

- **(a) Rechazo de TLS 1.2** → `sf_check_tls_version("TLSv1.2") == SF_ERR_TLS_VERSION`.
- **(b) Rechazo de cert sin validación PQC** → en `STRICT_PQ`, una cadena clásica devuelve
  `SF_ERR_CERT_NOT_PQ`; primitivas débiles (SHA-1, RSA<3072) rechazadas en toda política.
- **(c) Manejo seguro de memoria** → `sf_response_free` sobre struct a cero y doble llamada
  no fallan; argumentos `NULL` devuelven `SF_ERR_NULL_ARG` sin asignar.

Más cobertura de los validadores puros (URL, grupo KE híbrido vs. clásico/PQ-puro).

**Cierre de integración** (`tests/itest_secure_fetch.c`, `make itest`, dependiente de red):
- `http://` se rechaza antes de cualquier I/O.
- GET real bajo política por defecto ⇒ `SF_OK`, `TLSv1.3`, grupo con `MLKEM`.
- Forzando `kex_groups="x25519"` (clásico puro) ⇒ `SF_ERR_KEM_NOT_PQ`: el navegador
  rehúsa la conexión. El estado TLS negociado se captura **durante** la transferencia
  (callbacks de cabecera/cuerpo), porque `CURLINFO_TLS_SSL_PTR` solo expone el `SSL*`
  mientras la transferencia está viva; tras `curl_easy_perform` el puntero es nulo.

## 9. Fuera de alcance (de momento)

- Cookies y cabeceras de petición arbitrarias (*third-party* se bloquea a nivel de motor de
  red, ver `request_policy`).
- Reescritura de la barra de URL al destino final tras `sf_get_follow` (el orquestador GUI aún
  muestra la URL tecleada; pendiente devolver la URL final resuelta).
- Normalización completa de URL relativas con `.`/`..` y resolución de `query`/`fragment` en
  destinos relativos (se cubren los casos comunes; pendiente RFC 3986 íntegro).
- HTTP/2, HTTP/3 (el transporte los soporta; la política se fija después).
- Prueba de integración del POST en vivo: `sf_post` comparte el motor y la política con `sf_get`
  (verificado en unit tests: rechazo de no-https y de args nulos sin red); el envío real contra un
  endpoint PQ que acepte POST queda **pendiente de itest**, no presentado como verificado.
- Seguimiento de redirecciones en `sf_post` (un `303 See Other` debería re-emitirse como GET): por
  ahora el llamante inspecciona `http_code`/`location`.
