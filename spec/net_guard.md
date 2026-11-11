# net_guard (`ng_`) — una página pública no alcanza la red privada

## Por qué

Freedom no tenía ninguna noción de "dirección privada": `secure_fetch` conectaba a lo que el
DNS dijera. Con la enmienda *allow∩js recibe todo* (terceros, XHR/`fetch`/WebSocket reales y
**sin CORS**, §7.2), el JS de una página de confianza —o un script de terceros cargado por
ella— puede pedir `https://intranet.corp/` o `https://192.168.1.1/` y **leer la respuesta** si
el servicio presenta un certificado válido (intranets con CA pública, routers y NAS con
certificado real, `*.plex.direct`…). Y aunque el certificado falle, el intento de conexión ya
es un oráculo de escaneo de la LAN (fingerprinting + reconocimiento).

Idea tomada del crate `obscura-ssrf` de Obscura (deny-set único compartido por todos los
transportes), adaptada al modelo de un navegador: el **usuario** sí puede navegar a su router;
el **contenido remoto** no puede hacerlo por él (equivalente a *Private Network Access*).

## Contrato (puro, sin I/O)

- `ng_addr_is_private(family, bytes, len)` — 1 si la dirección no es globalmente enrutable:
  loopback, RFC 1918, link-local (incl. `169.254.169.254`), CGNAT `100.64/10`, `0/8`,
  `192.0.0/24` (salvo `.9`/`.10`), `192.0.2/24`, `198.18/15`, `198.51.100/24`, `203.0.113/24`,
  `192.88.99/24`, multicast, `240/4`, broadcast; IPv6 `::`, `::1`, `fc00::/7`, `fe80::/10`,
  multicast, documentación (`2001:db8::/32`, `3fff::/20`), descarte `100::/64`, NAT64 local
  `64:ff9b:1::/48`; y **toda forma IPv4-en-IPv6** (mapeada, compatible, NAT64 `64:ff9b::/96`,
  6to4 `2002::/16`, Teredo servidor y cliente) re-evaluada como IPv4. Familia o longitud
  desconocida ⇒ 1 (**fail-closed**).
- `ng_text_is_private(texto)` — lo mismo sobre una IP en texto canónico (la que reporta el
  transporte). No parseable ⇒ 1.
- `ng_host_is_local(host)` — 1 si el host es `localhost`, termina en `.localhost`, o es un
  literal IP privado (con o sin corchetes).
- `ng_decide(req, peer_private)` — `NG_ALLOW` / `NG_DENY`.

## Regla de decisión

| Condición (en orden) | Veredicto | Motivo |
| :-- | :-- | :-- |
| vía proxy de overlay (Tor/I2P) | ALLOW | el par es el proxy local; el overlay no enruta a la LAN |
| el par es público | ALLOW | |
| sin iniciador (navegación del usuario, salto 0) | ALLOW | soberanía: el usuario escribió la URL |
| iniciador local (`ng_host_is_local`) | ALLOW | local → local, misma zona |
| mismo sitio (eTLD+1) que el iniciador | ALLOW | una intranet carga sus propios subrecursos; el *rebinding* del mismo host no pasa VERIFYPEER |
| cualquier otro caso | **DENY** | contenido público alcanzando red privada |

Un **salto de redirección** tiene por iniciador el salto anterior: `https://evil.example` →
`302` → `https://192.168.1.1/…` se deniega aunque la navegación original fuera del usuario.

## Cableado (`secure_fetch`, único choke point `sf_setup_handle`)

- `CURLOPT_OPENSOCKETFUNCTION`: se decide sobre la dirección **ya resuelta** antes de crear
  el socket ⇒ no sale ni un SYN hacia la red privada, y cubre *DNS rebinding*, `/etc/hosts`,
  literales legacy (`127.1`, `0x7f.1`) y cualquier nombre que resuelva a privado.
- `CURLOPT_PREREQFUNCTION`: misma decisión sobre la IP del par cuando la conexión se
  **reutiliza** del pool compartido (una conexión abierta por una navegación legítima del
  usuario no puede ser reusada por una página pública).
- Resultado: `SF_ERR_PRIVATE_NET`. GET, POST y WebSocket comparten `sf_setup_handle`.

## Dado-Cuando-Entonces

- **Dado** que el usuario navega a `https://192.168.1.1/`, **entonces** se permite.
- **Dado** una página `https://news.example/` que pide `https://192.168.1.1/x`, o un nombre
  público que resuelve a `127.0.0.1`, **entonces** `SF_ERR_PRIVATE_NET` sin abrir socket.
- **Dado** `https://wiki.corp.example/` (privada) que pide `https://static.corp.example/`,
  **entonces** se permite (mismo sitio).
- **Dado** `[::ffff:127.0.0.1]`, `64:ff9b::7f00:1`, `2002:7f00:1::`, **entonces** privado.
- **Dado** una dirección que no se puede clasificar, **entonces** privada (fail-closed).

## Fuera de alcance

- Override por host (`allow.conf`) para permitir público → privado a un destino concreto.
- Espacio de direcciones del documento iniciador por IP real (se aproxima con mismo-sitio e
  iniciador local).
- `file://` (ya no tiene red).
