# spec/tls_impersonate.md — Impersonación de ClientHello TLS (JA3/JA4) para hosts de confianza

> Módulo `tls_impersonate` (prefijo `ti_`). **HITO EN ESPECIFICACIÓN — sin código todavía.**
> Metodología: SDD + TDD estricto + BDD Given-When-Then (§3 de `CLAUDE.md`). Este documento es el
> paso 1 (Spec). No hay `include/tls_impersonate.h` ni `src/tls_impersonate.c` hasta que el dueño
> cierre las decisiones abiertas de §10 y exista el test rojo de §7.
>
> Autorizado por el dueño (2026-07-12) como **excepción explícita a §1/§4** (dependencia nueva
> pesada). Este archivo documenta *qué* se autorizó, *el costo real* y *cómo se contiene* para no
> destruir el núcleo Secure-by-Default en el intento.

## 0. Por qué existe (el problema real, no el que se creía)

Google / Facebook / YouTube / Cloudflare / Reddit no bloquean a Freedom por sus **cabeceras HTTP**:
esas ya imitan a Firefox de forma completa y coherente (`FP_USER_AGENT`, `Accept`, `Accept-Language`,
`Sec-Fetch-*`, `DNT`; ver `anti_fp.h` y `secure_fetch.c`). El discriminador está **una capa más
abajo**, en el **ClientHello de TLS**: los anti-bot calculan **JA3/JA4** (hash del orden de cipher
suites, extensiones, grupos y sigalgs) y lo comparan contra el User-Agent declarado. Freedom negocia
con **OpenSSL 3.6**, cuyo ClientHello **no se parece al de ningún navegador** (NSS de Firefox,
BoringSSL de Chrome): orden de extensiones distinto, sin GREASE al estilo Chrome, sin
`application_settings`, sin compressed-cert.

Peor aún, hay una **contradicción interna que hoy nos delata**:

- El UA declara **Firefox/128**. Firefox 128 **no** ofrece `X25519MLKEM768` en su ClientHello
  (Firefox lo activó por defecto ~v132+).
- Nuestro ClientHello **sí** ofrece `X25519MLKEM768` (Principio 5, PQ-by-default).
- Resultado: *"dice Firefox 128 pero manda MLKEM con ordering de OpenSSL"* → mismatch JA3↔UA → bot.

Es decir: **nuestro propio PQ-by-default es la señal TLS más fuerte que tenemos**, porque casi ningún
navegador real de esa versión manda MLKEM. Ninguna afinación de cabeceras arregla esto.

### 0.1 Qué NO arregla esto (fronteras honestas)

Este hito hace que el **handshake TLS** de un host de confianza sea indistinguible del de un Chrome
real. **No** resuelve, y no pretende resolver:

- **BotGuard / reCAPTCHA / hCaptcha:** viven en `<iframe>` (Freedom no tiene iframe, doctrina),
  se disparan async post-load y hacen su propio fingerprint de canvas/WebGL (envenenado/ausente por
  doctrina). Son muros de *motor*, no de TLS. Google search y el "select the ducks" de DuckDuckGo
  seguirán apareciendo si la **IP** está flageada (reputación, Tor/VPN).
- **Fingerprint de HTTP/2** (Akamai: orden de pseudo-headers + SETTINGS frame). Queda para un
  sub-hito posterior; curl-impersonate también lo cubre, pero se valida aparte.
- **Fingerprint de comportamiento** (timing de mouse, IP, ausencia de cuenta Google): server-side.

Ver `[[freedom-anti-fp-network-identity]]`, `[[freedom-sop-by-construction]]`.

## 1. Decisión de arquitectura: dual-stack POR PROCESO (no un swap)

La reacción ingenua ("cambiar OpenSSL por BoringSSL") **destruiría el Principio 5** y es inviable en
un solo proceso. Tres hechos verificados en este host lo prohíben:

1. **OpenSSL 3.6.2 verifica certificados `ML-DSA-44/65/87` y `SLH-DSA` nativamente**
   (`openssl list -signature-algorithms` los muestra `@ default`). Es la **mitad de firma** del
   Principio 5 (`SF_POLICY_STRICT_PQ`, umbral SHA-1, RSA<3072 al leaf). **BoringSSL mainline no
   verifica certs ML-DSA/SLH-DSA.** Arrancar OpenSSL = regresar esa garantía para *todo* el
   navegador.
2. **Dos libcurl (uno OpenSSL, uno BoringSSL) en un mismo espacio de direcciones colisionan
   símbolos** (`SSL_*`, `curl_*`, `X509_*`). Ni `-fvisibility=hidden` salva la colisión transitiva
   del backend TLS. Es inseguro y no linkea limpio.
3. **curl-impersonate y BoringSSL NO están empaquetados** en este host (Kali/Debian; solo el fork
   Android de BoringSSL, inservible). Hay que **vendorizar y compilar de fuente** — una superficie
   enorme que **no debe tocar** el binario principal ni la ruta por defecto.

**Diseño resultante:** un **helper de red aislado**, `freedom-tls-helper` (re-exec de
`/proc/self/exe --tls-helper`, mismo patrón que `--tab-worker`), **linkeado contra la libcurl
impersonada + BoringSSL vendorizadas**. El binario principal `freedom` **sigue 100% OpenSSL 3.6**,
con todo `SF_POLICY` intacto, para todo el tráfico no-confiable. El helper se usa **solo** para el
tráfico de hosts allow∩js.

```
                    ┌─────────────────────────────────────────────┐
   host NO-confiable│ freedom (OpenSSL 3.6)                        │
   ───────────────► │   secure_fetch → SF_POLICY completo          │  (sin cambios)
                    │                   (PQ KE + PQ cert verify)    │
                    └─────────────────────────────────────────────┘
                    ┌─────────────────────────────────────────────┐
   host allow∩js    │ freedom (padre confiable)                    │
   ───────────────► │   ti_should_impersonate() == 1               │
                    │        │  socketpair (IPC ti_req/ti_resp)     │
                    │        ▼                                      │
                    │   freedom-tls-helper (BoringSSL, Chrome 13x)  │
                    │   handshake JA3-exacto + VERIFYPEER=1         │
                    │        │  devuelve: status, headers, body,    │
                    │        ▼  cadena DER, grupo/versión negociados│
                    │   padre RE-APLICA política de FUERZA sobre    │
                    │   la cadena reportada con OpenSSL:            │
                    │   RSA<3072 leaf, SHA-1 fatal, KE híbrido      │
                    └─────────────────────────────────────────────┘
```

**Reparto de responsabilidades de seguridad (clave):**

- **Autenticidad de cadena** → la hace **BoringSSL** en el helper (`VERIFYPEER=1`, trust store del
  sistema). El helper **nunca** devuelve cuerpo si la verificación falla (fail-closed).
- **Fuerza criptográfica** (RSA<3072 al leaf, SHA-1 fatal, exigir KE híbrido) → la **re-aplica el
  padre** con OpenSSL sobre la **cadena DER + parámetros negociados** que el helper reporta. La
  política de `secure_fetch` no se duplica en el helper; se reusa `sf_enforce_policy` sobre datos
  reportados.
- **Verificación de cert PQ** (`ML-DSA`/`SLH-DSA` en la cadena, `SF_POLICY_STRICT_PQ`) → **NO
  disponible en la ruta impersonada** (BoringSSL no la trae). Se maneja fail-closed: ver §4.

## 2. Gate: quién usa el helper (Zero Trust intacto) — TRIPLE opt-in

Decisión del dueño (2026-07-12): la impersonación es **opt-in por un tercer archivo
`impersonate.conf`** (formato `/etc/hosts`, reusa `hostblock`, cubre subdominios). El gate es
**triple**, puro y testeable: un host usa la ruta impersonada **solo si está en `allow.conf` Y en
`js.conf` Y en `impersonate.conf`**. Los dos primeros son la doble-confianza del Hito 26/28
(`net_allowed`); el tercero es el opt-in explícito de "quiero que ESTE host salga disfrazado de
Chrome". Para cualquier otro host la función devuelve 0 y **nunca** se instancia el helper — la ruta
OpenSSL endurecida es la única que ve el resto del tráfico.

```
Dado  un host H y las listas allow.conf / js.conf / impersonate.conf
Cuando se decide la ruta de red para H
Entonces ti_should_impersonate(H) == 1  SÍ Y SOLO SI
             hb_is_allowlisted(H) ∧ jsp_host_enabled(H) ∧ hb_in_impersonate(H)
         y en cualquier otro caso == 0 (fail-closed: se usa la ruta OpenSSL por defecto)
```

Un modo global `JSP_ON` **no** basta (igual que en el Hito 28): exige la entrada **explícita** en
`allow.conf`; y ni allow∩js basta sin el opt-in de `impersonate.conf`. Ver
`[[freedom-trusted-host-full-caps]]`, `[[freedom-parent-gated-xhr]]`.

**Consecuencia de doctrina del opt-in triple:** un host en `impersonate.conf` sale con **KE clásico**
(perfil Chrome sin MLKEM, §1.1) — pierde la mitad KE del Principio 5 en esa ruta. Que sea un tercer
archivo separado hace esa concesión **deliberada y por-host**, nunca implícita: el usuario firma la
exposición Harvest-Now-Decrypt-Later host por host.

## 3. Tipos y API (borrador; se congela con el test rojo de §7)

La **lógica pura** (lo que TDD cubre directamente) es: (a) la decisión de gate, y (b) el **códec de
IPC** padre↔helper (serialización determinista, fuzzeable). El handshake BoringSSL en sí NO es
lógica pura y se valida por prueba de integración, no por unit test.

```c
/* --- decisión de gate (pura, sin I/O): triple opt-in --- */
int ti_should_impersonate(int host_in_allowlist, int host_js_enabled, int host_in_impersonate);

/* --- perfil de impersonación (qué navegador imitamos) --- */
typedef enum ti_profile {
    TI_PROFILE_CHROME_CLASSIC = 0, /* ELEGIDO: Chrome con KE clásico (JA3 máximamente común;
                                      SIN X25519MLKEM768 -> sin PQ KE en esta ruta, §1.1) */
    TI_PROFILE_CHROME_MLKEM        /* reservado: Chrome >=131 con MLKEM (conservaría PQ KE) */
} ti_profile;

/* --- códec IPC (puro, determinista, fuzzeable) --- */
typedef struct ti_req {
    const char *url;            /* https únicamente en esta ruta */
    const char *method;         /* "GET"/"POST" */
    const char *headers;        /* headers ya normalizados por el padre (anti_fp) */
    const uint8_t *body; size_t body_len;
    ti_profile profile;
} ti_req;

typedef struct ti_resp {
    long   status;              /* HTTP status; 0 => fallo de transporte/verificación */
    char  *headers;             /* headers de respuesta (dueño: el llamador) */
    uint8_t *body; size_t body_len;
    /* Datos para que el PADRE re-aplique la política de fuerza con OpenSSL: */
    uint8_t *peer_chain_der; size_t peer_chain_len; /* cadena que BoringSSL verificó */
    char   negotiated_group[64];   /* p.ej. "X25519MLKEM768" */
    long   tls_version;            /* CURL_SSLVERSION_* negociado */
} ti_resp;

/* Serialización sobre el socketpair. Longitud-prefijada, fail-closed ante truncado/overflow.
 * Sin punteros crudos por el cable; todo copiado y acotado (TI_MAX_* anti-DoS). */
size_t ti_encode_req(const ti_req *r, uint8_t *out, size_t out_cap);   /* 0 = no cupo */
int    ti_decode_req(const uint8_t *in, size_t len, ti_req *out);      /* <0 = malformado */
size_t ti_encode_resp(const ti_resp *r, uint8_t *out, size_t out_cap);
int    ti_decode_resp(const uint8_t *in, size_t len, ti_resp *out);
```

El **transporte** (fork/exec del helper, socketpair, loop de escritura/lectura bloqueante en el
helper) vive en el orquestador de `secure_fetch`/`tab`, no en el módulo puro. **`io_uring` está
PROHIBIDO en el helper** igual que en el worker (es una primitiva de bypass de seccomp); el helper
hace I/O bloqueante sobre su socket y su conexión curl. Ver `[[freedom-io-uring-forbidden-in-worker]]`.

## 4. Tabla de errores (fail-closed en todos)

| Situación | Resultado | Razón |
| :-- | :-- | :-- |
| Host no está en allow∩js∩impersonate | no se usa helper; ruta OpenSSL normal | Zero Trust: triple opt-in |
| Helper no pudo hacer VERIFYPEER (cadena no auténtica) | `status=0`, sin cuerpo | autenticidad es innegociable |
| Cadena reportada con RSA<3072 al leaf / SHA-1 en cualquier posición | el padre rechaza | política de fuerza re-aplicada |
| KE negociado no híbrido y política lo exige | el padre rechaza (o avisa, según `SF_POLICY`) | navegabilidad vs PQ (doctrina existente) |
| Host exige `SF_POLICY_STRICT_PQ` (cert PQ requerido) | **no se usa el helper**; se intenta OpenSSL | BoringSSL no verifica certs PQ; fail-closed |
| Sitio sirve un cert `ML-DSA`/`SLH-DSA` (inexistente en Web PKI 2026) | el helper falla la verificación → `status=0` | BoringSSL no lo entiende; no se degrada a "aceptar" |
| IPC malformado / truncado / sobre-largo | `ti_decode_* < 0`, se aborta la petición | códec fail-closed, fuzzeado |
| Helper crashea / timeout | el padre lo mata y devuelve error de red | el padre sobrevive (como el worker) |

**Pérdida documentada y contenida:** la ruta impersonada **no verifica certs PQ** (`ML-DSA`/
`SLH-DSA`). Es aceptable **solo** porque: (1) la Web PKI pública **no tiene certs PQ en 2026**
(doctrina vigente en `CLAUDE.md` §4); (2) esta ruta es exclusiva de hosts allow∩js (Google/FB/YT,
todos con certs clásicos RSA/ECDSA válidos); (3) si un host pidiera `STRICT_PQ`, **no** se usa el
helper (cae a OpenSSL, que sí lo verifica, aunque el sitio probablemente no negocie). La **mitad de
KE** del Principio 5 (`X25519MLKEM768`) **sí se conserva** si el perfil Chrome elegido lo manda —
verificación obligatoria en la Fase 1 (§8).

## 5. Garantías de seguridad (invariantes con test)

1. **Aislamiento del blob:** el binario `freedom` principal y la ruta por defecto **nunca** linkean
   BoringSSL ni curl-impersonate. Test: `nm build/freedom | grep -i boringssl` vacío; el helper es un
   ejecutable separado.
2. **Gate estricto:** `ti_should_impersonate` devuelve 1 **solo** con ambas señales. Test rojo
   primero (§7). Candado de regresión análogo a `test_eval_no_network_or_cross_origin_api`.
3. **Autenticidad preservada:** el helper corre con `VERIFYPEER=1`/`VERIFYHOST=2`; jamás devuelve
   cuerpo sin verificación exitosa. La política de **fuerza** se re-aplica en el padre con OpenSSL.
4. **Sandbox del helper:** el helper necesita **red** (no puede `CLONE_NEWNET`), pero corre bajo
   seccomp-allowlist + Landlock + `PR_SET_DUMPABLE=0` + W^X, igual que el worker salvo el netns.
   No toca el DOM ni ejecuta contenido de página: solo hace la petición y devuelve bytes.
5. **Códec fuzzeado:** `ti_decode_req`/`ti_decode_resp` entran a `make fuzz` (nuevo `fuzz-tls`), cero
   crashes/UB antes de cerrar.
6. **Doctrina de superficie:** la excepción a §4 queda **contenida** a un proceso aislado y
   sandboxeado, activo solo para hosts que el usuario declaró de confianza dos veces. Es la
   justificación por la que la dependencia entra: no por conveniencia, sino acotada al mínimo.

## 6. Fuera de alcance (este hito)

- Fingerprint de **HTTP/2** (Akamai) y de **QUIC/HTTP3** — sub-hito posterior.
- reCAPTCHA/hCaptcha/BotGuard, iframes, WebGL, motor async completo — no son TLS (§0.1).
- Impersonar Firefox (solo si su perfil manda MLKEM; si no, viola el Principio 5 — ver §10).
- `arrayBuffer` binario en el XHR gateado (límite v1 existente, ortogonal).

## 7. Test rojo primero (TDD) — `tests/test_tls_impersonate.c`

Antes de una línea de implementación, estos deben **fallar por falta de símbolo** (estado rojo):

```
test_gate_requires_all_three_signals -> ti_should_impersonate(1,1,1)==1; cualquier 0 => 0
test_encode_decode_req_roundtrip     -> ti_encode_req → ti_decode_req reconstruye campos
test_encode_decode_resp_roundtrip    -> incluye peer_chain_der y negotiated_group
test_decode_rejects_truncated        -> ti_decode_* (buf, len-1) < 0  (fail-closed)
test_decode_rejects_overlong_field   -> longitud declarada > TI_MAX_* rechazada
test_helper_not_linked_to_boringssl  -> (integración) nm sobre build/freedom sin símbolos boringssl
```

## 8. Plan por fases (cada fase cierra verde antes de la siguiente)

- **Fase 0 (cerrada):** spec + decisiones §10 cerradas.
- **Fase 2 — Códec IPC puro + gate (TDD) — CERRADA (2026-07-12).** `include/tls_impersonate.h` +
  `src/tls_impersonate.c` + `tests/test_tls_impersonate.c` (10 tests, verde) +
  `fuzz/fuzz_tls_impersonate.c` (target `make fuzz-ti`). `ti_should_impersonate` (gate triple) y
  `ti_encode_*`/`ti_decode_*` (frame LE longitud-prefijada, fail-closed, caps `TI_MAX_*`).
  **Validado:** ASan/UBSan limpio; fuzz 8.3M ejecuciones/31s sin crash/leak/UB. Linkeado en `freedom`
  (aún dead code hasta la Fase 3). Se hizo **antes** que la Fase 1 a propósito: fija el contrato puro
  y auditable sin depender del blob. Bug de cierre-de-comentario prematuro (`*/` literal) encontrado y
  extinguido.
- **Fase 1 — Vendorizar + construir el helper. [BLOQUEADA en este host].** Traer curl-impersonate +
  BoringSSL como tarball verificado por hash; target `make tls-helper`. **Verificación obligatoria
  antes de seguir:** (a) el ClientHello del perfil Chrome-clásico matchea un JA3/JA4 de Chrome real
  contra un endpoint de referencia (`tls.peet.ws/api/all`); (b) NO se exige MLKEM (perfil clásico
  elegido, §10). **Bloqueo real verificado:** curl-impersonate y BoringSSL **no están empaquetados**
  (Kali/Debian), `ninja` ausente; requiere build de fuente pesado (Go+cmake+ninja). Es el gran lift
  restante; no completable de forma verificable en una sesión de agente.
- **Fase 3 — Cableado + blend interino OpenSSL — CERRADA (2026-07-12).** Sin esperar el helper
  BoringSSL, se cableó un **blend interino con OpenSSL** verificado en el cable real: `sf_config`
  gana `impersonate`; con el flag, `secure_fetch` deja el ClientHello **consistente con la identidad
  Firefox que ya mandamos** — quita `X25519MLKEM768`, ordena las cifras TLS 1.3 estilo Firefox
  (`SF_IMPERSONATE_TLS13_CIPHERS`), restringe la lista TLS 1.2 a la de Firefox
  (`SF_IMPERSONATE_TLS12_CIPHERS`, ~80→~14 suites) y usa `SF_IMPERSONATE_KEX_GROUPS` (grupos clásicos,
  orden Firefox 128). El **gate triple** (`ti_should_impersonate`) se alimenta de `impersonate.conf`
  (nuevo, vía `hostblock`) en headless (`freedom.c`) y GUI (`browser_ui.c`: `build_impersonate_filter`
  refactoriza `build_js_filter` a `build_conf_allowlist` DRY), en las tres rutas de fetch (página,
  subrecurso/XHR, imagen). Policy: los hosts impersonate ⊆ allow ⇒ ya usan `ALLOWLISTED_INSECURE`, que
  tolera el KE clásico. **Verificación E2E contra `tls.peet.ws/api/clean`:** ON → JA4
  `t13d1714h2_5b57614c22b0_...` (componente de cifras **idéntico al de Firefox 128**), 17 cifras,
  **sin grupo MLKEM 4588**; OFF → JA4 `t13d9014h2_...`, 90 cifras, con MLKEM. `make test` completo
  verde. **Techo honesto:** JA3 se acerca (cifras matchean), no byte-exacto (extensiones/GREASE de
  OpenSSL ≠ browser); eso es la Fase 1 (BoringSSL). El `impersonate` interino NO instancia el helper
  ni re-aplica política sobre cadena reportada (eso es cuando exista el helper) — hoy la ruta sigue
  siendo OpenSSL con `sf_enforce_policy` normal, solo con el ClientHello afinado.
- **Fase 4 — Sandbox del helper.** seccomp-allowlist con sockets (sin netns), Landlock, anti-dump,
  W^X. Reusar `os_sandbox` con un perfil "necesita red".
- **Fase 5 — Validación + fuzzing + itest.** `make asan`/`valgrind`/`cppcheck` sobre las partes
  OpenSSL/puras; `fuzz-tls`; **itest real**: fetch de un endpoint de eco-JA3 vía el helper mostrando
  JA3 == Chrome, y una carga real de un host allow∩js (p. ej. el panel propio) sin regresión.
- **Fase 6 — Documentación.** Recién acá: `CLAUDE.md` (hito → cerrado), `docs/index.html`, `README.md`,
  memoria (`[[freedom-tls-impersonate]]`).

## 9. Riesgos y tensiones de doctrina (honestidad brutal)

1. **Superficie de ataque ↑↑.** BoringSSL + curl-impersonate son decenas de miles de líneas
   vendorizadas, contra *"lo que no se puede auditar, no entra"* (§1). Mitigación: proceso aislado +
   sandbox + solo trusted-hosts. Sigue siendo la mayor concesión de doctrina del proyecto. El dueño
   la autorizó explícitamente; queda registrada como excepción acotada, no como puerta abierta.
2. **Mantenimiento del blob.** curl-impersonate va detrás de las versiones de Chrome; un JA3 que hoy
   pasa, en 6 meses es "viejo" y vuelve a destacar. Es deuda perpetua, no un cierre definitivo.
3. **PQ cert-verify perdido en la ruta impersonada** (§4). Contenido, pero real.
4. **Complejidad de dos stacks TLS.** Un bug de build (linkado cruzado) podría meter BoringSSL en el
   binario principal sin que se note. Por eso la garantía §5.1 es un test, no una intención.
5. **No garantiza el objetivo del usuario.** Aun con JA3 perfecto, Google/reCAPTCHA pueden seguir
   bloqueando por IP/comportamiento/iframe (§0.1). Este hito sube la probabilidad de pasar el muro
   *de TLS*, no promete "entrar a Google". Prometer lo contrario sería deshonesto.

## 10. Decisiones del dueño (CERRADAS 2026-07-12)

1. **Perfil Chrome → `TI_PROFILE_CHROME_CLASSIC` (sin MLKEM).** Se prioriza un JA3 máximamente
   común sobre conservar el KE post-cuántico en esta ruta. Consecuencia aceptada: los hosts de
   `impersonate.conf` salen con **KE clásico** → exposición Harvest-Now-Decrypt-Later acotada a ese
   tráfico (§1.1). El resto del navegador conserva PQ KE (ruta OpenSSL por defecto).
2. **Activación → opt-in por `impersonate.conf`** (no siempre-on). Gate triple: allow∩js∩impersonate
   (§2). La concesión de KE clásico queda firmada por-host, deliberada, nunca implícita.
3. **Vendorizado → tarball pinneado por hash** (recomendación tomada por defecto; el dueño no la
   objetó). curl-impersonate + BoringSSL entran como tarball con hash verificado en el Makefile, no
   como submódulo git (auditabilidad §1: "lo que no se puede auditar, no entra").
4. **Pérdida de PQ cert-verify en la ruta impersonada → ACEPTADA** (default no objetado). Válida
   porque no hay certs PQ en la Web PKI 2026 y la ruta es trusted-only + opt-in; `STRICT_PQ` sigue
   cayendo a OpenSSL (§4).

> Si el dueño quiere revisar (3) o (4) explícitamente antes de la Fase 1, decirlo; se tomaron como
> el default recomendado por no haber sido objetadas.

## 1.1 Trade-off del KE clásico (perfil elegido)

Con `TI_PROFILE_CHROME_CLASSIC`, el handshake de un host en `impersonate.conf` negocia un KE
**clásico** (X25519/secp256r1, sin `X25519MLKEM768`). Eso significa que **ese** tráfico es
vulnerable a *Harvest-Now-Decrypt-Later* si un adversario con capacidad cuántica futura guarda hoy
el handshake. Es una concesión **consciente y acotada**: (a) solo afecta hosts que el usuario metió
en un tercer archivo a propósito; (b) el resto del navegador (toda ruta no-impersonada) mantiene
`X25519MLKEM768`; (c) la autenticidad de cadena y la política de fuerza (RSA/SHA-1) se mantienen
intactas — se relaja la resistencia cuántica del KE, **nunca** la autenticidad. El chrome debería
mostrar un indicador visual "classical TLS (Chrome-blend)" en esos hosts (sub-tarea de la Fase 3),
para que la concesión sea visible, no silenciosa.

---

**Estado:** ESPECIFICADO, decisiones §10 cerradas. Próximo paso: **test rojo (§7)** y luego **Fase 1**
(vendorizar + construir el helper, verificar JA3 == Chrome contra endpoint de referencia). Ninguna
garantía de seguridad existente (`SF_POLICY`, PQ KE+cert en la ruta por defecto) se toca hasta que
este hito esté verde y validado. Ver `[[freedom-tls-impersonate]]`.
