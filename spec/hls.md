# hls (`hls_`) — playlists HLS y validación de segmentos

> Puro, sin I/O. El padre baja; el proceso decoder aislado (`OS_PROFILE_MEDIA_DECODER`) decodifica.

## Playlist

`hls_parse` acepta VOD simple y maestras (multi-variante); `hls_select_variant` elige la de mayor
ancho de banda dentro de un tope; `hls_resolve_url` resuelve el segmento contra la URL del
playlist. Sin red; las URLs se devuelven como están escritas.

## Segmento utilizable (2026-11-22)

```c
long hls_segment_payload(long http_code, const unsigned char *body, size_t len);
```

Devuelve el desplazamiento donde empieza el medio dentro del cuerpo, o `-1` si el segmento no es
medio. Lo que no es medio **no entra al decoder** (fail-closed: un solo cuerpo de error rompía
`avformat_open_input` y con él la reproducción entera).

- **Dado** un estado HTTP fuera de 2xx, **entonces** `-1` (caso real: un nodo del CDN de jkanime
  responde `500 Internal Server Error` al primer segmento; curl ve lo mismo).
- **Dado** un MPEG-TS (`0x47` cada 188 bytes, al menos un paquete completo: un texto `"Gateway
Timeout"` empieza con `G` = `0x47` y no es un stream), **entonces** el desplazamiento del primer `0x47`
  que tiene otro `0x47` 188 y 376 bytes después (o fin del cuerpo), buscado en los primeros
  4 KiB. Cubre los TS con un prefijo de imagen falsa (hosts que disfrazan el segmento de `.png`).
- **Dado** un contenedor ISO BMFF (`ftyp`/`styp`/`moof`/`moov`/`sidx`/`emsg` en el byte 4),
  **entonces** `0`. **Dado** audio con cabecera `ID3`, **entonces** `0`.
- **Dado** cualquier otra cosa (HTML, texto, vacío, `NULL`), **entonces** `-1`.

El feeder reintenta UNA vez un segmento rechazado y, si vuelve a fallar, lo **salta** (como
hls.js: un hueco de unos segundos es mejor que detener el vídeo). Nunca se pasa al decoder un
cuerpo rechazado.

## Espejos declarados por el playlist (2026-11-22)

```c
size_t hls_mirror_url(const hls_playlist *pl, const char *seg_abs, size_t k,
                      char *out, size_t outsz);
```

Caso real: el playlist de jkanime reparte los segmentos entre `cdn1`…`cdn6.<dominio>`; dos nodos
responden 500 a todo, y el MISMO camino existe en los demás. Sin esto se perdía un segmento de
cada dos.

- **Dado** la URL absoluta de un segmento rechazado, **entonces** escribe en `out` esa URL con el
  host cambiado por el `k`-ésimo (desde 0) host **distinto** que aparece en las URLs absolutas
  `https://` del playlist y comparte con el original todo lo que sigue a la primera etiqueta
  (`cdn6.ducvomes.com` ↔ `cdn2.ducvomes.com`), en orden de aparición. Devuelve la longitud, o `0`
  si no hay `k`-ésimo espejo, si el segmento no es `https://` o si no cabe.
- Nunca inventa un host: solo usa los que el playlist ya declaró y que el feeder pediría de todos
  modos, del mismo dominio padre (un playlist no puede redirigir a otro sitio por esta vía).
- El feeder prueba hasta `HLS_MAX_MIRRORS` (3) espejos; todo segmento pasa por el mismo fetch
  gateado y por `hls_segment_payload`.

## Seguridad

- Acotado: nunca lee más allá de `len` ni de 4 KiB + 2·188 para el sondeo.
- Fuzzeado (`make fuzz-hls`).
