# site_panel (`sp_`) — panel de identidad del sitio

## Por qué

Hasta la tanda 97 un clic en la insignia de identidad mostraba un aviso breve con una frase.
Un navegador cuya misión es la seguridad tiene que poder **explicar** cómo llegó la página:
versión de TLS, grupo de intercambio de claves negociado (¿híbrido post-cuántico?), si el
certificado se verificó, por dónde se enrutó (directo / Tor / I2P) y qué permisos tiene el
sitio (allow, JS, terceros, cookies). Firefox lo muestra en el panel del candado; Freedom lo
muestra en un panel anclado a la insignia, con las dos acciones de soberanía del usuario
(confiar en el sitio, activar JS) a un clic, sin atajos que recordar.

## Contrato (puro: sin I/O, sin Cairo, sin estado de ventana)

- `sp_build(const sp_facts *f, sp_panel *out)` → `SP_OK` / `SP_EINVAL` (`f` u `out` NULL).
  Construye el título (host), el titular (`chl_identity_label`), su tono, las filas
  (etiqueta, valor, tono) y las acciones ofrecidas.
- `sp_layout(const sp_panel *p, chl_rect anchor, double win_w, double win_h, sp_geom *g)`:
  rectángulo del panel bajo la insignia (`anchor`), acotado a la ventana con un margen de
  `SP_MARGIN`; rectángulo de cada acción. Tamaños no finitos se tratan como 1.
- `sp_hit(const sp_geom *g, x, y)` → `SP_HIT_OUTSIDE`, `SP_HIT_PANEL` o `SP_HIT_ACTION0 + i`.

### Entradas (`sp_facts`)

| Campo | Origen | Confianza |
| :-- | :-- | :-- |
| `url` | página mostrada | **hostil** (la elige la página por redirección) |
| `identity` | `chl_identity_of` | lado confiable |
| `tls_version`, `group` | `sf_response` del fetch que entregó ESTE documento | OpenSSL; igual se sanea |
| `route` | `SP_ROUTE_DIRECT/TOR/I2P` | `net_realm` |
| `allowlisted`, `js_site`, `trusted` | filtros de `allow.conf`/`js.conf` | lado confiable |
| `listable` | `he_make_line` sobre el host | lado confiable |

### Salida

- Título: el host de la URL (sin userinfo ni puerto), saneado a ASCII imprimible (otro byte ⇒
  `?`), recortado a `SP_HOST_MAX` con `...`. Sin host ⇒ `"Freedom"` (interna), `"Local file"`.
- Filas, en este orden y solo las que aplican:
  1. **Connection** — `"<tls> · <grupo>"` si el transporte es conocido; `"Not encrypted"`
     (INSECURE); `"No network"` (LOCAL/INTERNAL); `"Unknown: not delivered by a checked fetch"`.
  2. **Key exchange** — `"Hybrid post-quantum (ML-KEM + classical)"` solo si la identidad es
     `PQ` **y** el grupo nombra `MLKEM`; `"Classical: not quantum-resistant"` para
     `CLASSICAL`/`WEAK`; omitida si no hay red.
  3. **Certificate** — `"Verified"` (PQ/CLASSICAL/OVERLAY https), `"Verified; weak crypto allowed
     by allow.conf"` (WEAK), `"NOT verified (--insecure)"` (UNVERIFIED); omitida si no hay TLS.
  4. **Route** — `Direct` / `Tor (SOCKS5h, remote DNS)` / `I2P`; omitida sin red.
  5. **Third parties** — `trusted` ⇒ `"Allowed (site trusted)"`, si no `"Blocked"`.
  6. **JavaScript** — `js_site` ⇒ `"On for this site"`, si no `"Off"`.
  7. **Cookies** — `trusted` ⇒ `"Session only, in memory"`, si no `"None"`.
- Acciones (solo con host de red que `hostedit` acepta, `listable`): `SP_ACT_ALLOW` si
  `!allowlisted`, `SP_ACT_JS` si `!js_site`. Un botón que no puede hacer nada no se ofrece
  (`localhost`, una IP literal entre corchetes).
- Tono del titular: `GOOD` solo para `PQ`; `BAD` para `UNVERIFIED`/`INSECURE`; `WARN` para
  `CLASSICAL`/`WEAK`/`UNKNOWN`; `NEUTRAL` el resto. **Nunca verde por omisión.**

## Garantías

- Ningún byte de la URL llega al pintor sin sanear (no hay control/escape/UTF-8 crudo).
- El panel no afirma post-cuántico sin `identity == PQ`: un grupo `X25519MLKEM768` con una
  identidad desconocida no produce la fila híbrida.
- Las acciones solo **añaden** a la lista (mismo `list_append_host` validado por `hostedit`);
  quitar un host sigue siendo editar el archivo (falla cerrado: un clic no puede des-confiar
  ni des-bloquear por accidente algo que el usuario escribió a mano).
- Geometría: todo rectángulo es finito, de tamaño no negativo y queda dentro de la ventana
  cuando la ventana es mayor que `2·SP_MARGIN`.

## Dado-Cuando-Entonces

- **Dado** `https://example.org/x`, PQ, `TLSv1.3`/`X25519MLKEM768`, no allow, no js,
  **cuando** se construye, **entonces** título `example.org`, tono `GOOD`, fila Key exchange
  híbrida, Certificate `Verified`, Third parties `Blocked`, y dos acciones (allow, js).
- **Dado** la misma URL con identidad `UNKNOWN`, **entonces** no hay fila híbrida y el tono es
  `WARN`.
- **Dado** `file:///tmp/a.html`, **entonces** título `Local file`, Connection `No network`,
  sin acciones.
- **Dado** un host con bytes de control, **entonces** el título los muestra como `?`.
- **Dado** una ventana de 300×200 y una insignia en x=250, **entonces** el panel cabe en la
  ventana.

## Fuera de alcance

Detalles del certificado (emisor, validez): `sf_response` no los expone y exponerlos sería
otra copia de la cadena en memoria. Quitar hosts de las listas. Permisos por API.
