# request_headers -- cabeceras de XHR/fetch de una página (`rp_sanitize_request_headers`)

Hasta la tanda 69 `XMLHttpRequest.setRequestHeader` era un no-op y `fetch()` descartaba `headers`:
ninguna página podía enviar `Accept`, `Content-Type: application/json`, `X-Requested-With` ni un
token CSRF. Resultado medido: el parcial de login de reddit (`Accept: text/vnd.reddit.partial+html`)
respondía 406 y la página quedaba en blanco.

## Contrato

1. **Worker (no confiable):** `XHR.setRequestHeader` combina nombres repetidos con `", "`; `fetch`/`Request`
   aportan sus `Headers`. El bloque (`"Name: value\n"`) cruza como un campo más de la trama `TAG_SUBREQ`
   (tras el cuerpo), acotado a `RP_HDR_MAX_BYTES`.
2. **Padre (confiable):** `tab_serve_subreq` vuelve a filtrar el bloque con `rp_sanitize_request_headers`
   (un worker comprometido no se salta el filtro) y lo publica solo durante la llamada al fetcher
   (`tab_inflight_request_headers`, `_Thread_local`: contexto de la petición en vuelo, no estado compartido).
3. **`secure_fetch`:** `sf_config.extra_headers` se añade a la petición; un `Accept` o `Content-Type` propio
   de la página REEMPLAZA el de navegador por defecto (no se envían dos).

## `rp_sanitize_request_headers(raw, out, cap)` (puro, fail-closed)

- Dado un bloque, Entonces se conservan solo líneas con nombre token (`!#$%&'*+-.^_`|~` + alfanumérico,
  ≤ 64 B), valor sin bytes de control (≤ 1024 B, espacios exteriores recortados), a lo sumo
  `RP_HDR_MAX_COUNT` (32) y `RP_HDR_MAX_BYTES` (4096).
- Un nombre repetido conserva la primera aparición.
- **Prohibidos** (los posee el navegador): Host, Cookie, Cookie2, Set-Cookie, Referer, User-Agent,
  Accept-Language, Accept-Encoding, Connection, Content-Length, Content-Encoding, Transfer-Encoding, TE,
  Upgrade, Keep-Alive, Expect, Date, DNT, Via, Trailer, Origin, `Sec-*`, `Proxy-*`, `X-HTTP-Method*`,
  `Access-Control-Request-*`. Accept-Language y User-Agent protegen la identidad anti-fingerprinting.
- Una línea dudosa se descarta, nunca se reescribe. Devuelve cuántas se conservaron, o -1 con argumentos nulos.
- Idempotente; fuzzeado (`make fuzz-rqh`).

## Cabeceras de respuesta

`sf_response.headers` (todas las líneas de la respuesta FINAL, sin la de estado y **sin Set-Cookie**, ≤ 8 KiB)
viaja de vuelta tras el `Content-Type` en la trama de respuesta y alimenta `getAllResponseHeaders`,
`getResponseHeader` y `Response.headers` (`etag`, `x-total`, `link`, ...).

## XMLHttpRequest completo

EventTarget (`addEventListener`/`removeEventListener`/`dispatchEvent` + `on*`), `upload`, `timeout`,
`responseType` (`''`/text/json/arraybuffer/blob/document), `abort()`, `statusText` y la secuencia de eventos
`loadstart`, `readystatechange` 2-3-4, `progress`, `load`/`error`, `loadend`. El resultado (`status`,
`responseText`, cabeceras) se fija en `send()` (la ida y vuelta es síncrona por dentro); en una petición
asíncrona solo los EVENTOS se difieren a un timer, de modo que "leer justo tras `send()`" y "asignar `onload`
tras `send()`" funcionan los dos. YouTube moría en `d.addEventListener("loadend", ...)`.

## Fuera de alcance

CORS no se implementa (SOP por construcción: no hay red cross-origin sin allow∩js). `Origin` no se envía.
