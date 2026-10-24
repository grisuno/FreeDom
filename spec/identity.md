# spec: identity (`idn_`) — identidad y APIs sensibles configurables por el usuario

Modulo PURO (sin I/O, sin estado global, reentrante). Modela lo que el usuario puede decidir
sobre la identidad que Freedom presenta, la valida (fail-closed), la serializa para las prefs y
el IPC del worker, y genera la pagina interna `about:config`.

## Doctrina
- **Por defecto nada cambia**: `idn_defaults` = la identidad normalizada de `anti_fp` (la misma
  para todos los usuarios de Freedom, el conjunto de anonimato). Todo override es opt-in.
- **Un override es SOBERANIA, no gratis**: cambiar el User-Agent o los idiomas saca al usuario del
  conjunto de anonimato; la pagina lo dice. No hay valor "real": el navegador nunca lee la
  ubicacion, el locale ni el hardware verdadero. Lo que una pagina recibe es lo que el usuario
  escribio, o nada.
- **Coherencia**: el `User-Agent` del cable y `navigator.userAgent`/`appVersion` salen del MISMO
  valor efectivo (`idn_user_agent`); `Accept-Language` y `navigator.language(s)` del mismo
  (`idn_accept_language`/`idn_primary_language`).
- **Geolocalizacion**: `navigator.geolocation` existe SOLO si el modo es `fixed` Y el host es de
  confianza (allow.conf AND js.conf). Devuelve siempre las coordenadas fijadas por el usuario
  (precision declarada), sin consulta de red ni sensor.
- **WebGL, Service Workers**: el motor NO los implementa (no hay renderizador GL ni worker de
  fondo); la pagina los muestra como "no disponibles" y NO hay interruptor que finja lo
  contrario. Un interruptor sin motor detras seria una promesa falsa.

## Contrato
- `idn_set_user_agent(c, s)`: `""` restaura el defecto. Valido = solo ASCII imprimible (0x20-0x7E),
  1..`IDN_UA_MAX-1` bytes, sin ser solo espacios. Si no, `-1` y `c` queda intacto.
- `idn_set_languages(c, s)`: lista separada por comas de etiquetas `aa`/`aaa`(-`[A-Za-z0-9]{2,8}`)*,
  hasta 8; `""` restaura. Invalido => `-1`, `c` intacto.
- `idn_set_geo(c, lat, lon, acc)`: finitos, `lat` en [-90,90], `lon` en [-180,180], `acc` en
  [1,100000] metros. Invalido => `-1`, `c` intacto. `idn_clear_geo` apaga.
- `idn_accept_language(c, out, cap)`: cabecera (`es-AR,es;q=0.9,en;q=0.8`; defecto
  `fp_accept_language_header()`); `idn_primary_language`: la primera etiqueta.
- `idn_serialize`/`idn_parse`: una sola linea `ua=<pct>|lang=<pct>|geo=<lat>,<lon>,<acc>` (`%XX`
  para `|`, `%`, controles). `idn_parse` valida campo por campo: un campo invalido vuelve a su
  defecto, el resto se conserva; nunca falla abierto.
- `idn_apply_query(c, query)`: aplica `ua=`, `lang=`, `lat=`, `lon=`, `acc=` (los tres vacios = geolocalizacion
  apagada; los tres llenos = fija; parcial = rechazado; `geo=off|fixed` explicito tambien se acepta),
  `reset=1` (query estilo formulario GET, `+`/`%XX` decodificados). Devuelve una mascara
  `IDN_REJ_*` de los campos rechazados (0 = todo aplicado); un campo rechazado no altera nada.
- `idn_render_page(c, out, cap)`: HTML escapado de `about:config` (formulario GET con los campos,
  estado de cada API, advertencia de anonimato). Todo valor del usuario sale escapado.

## Fuera de alcance
Zona horaria, hardware (`hardwareConcurrency`, `deviceMemory`), pantalla: siguen normalizados.
WebGL/Service Workers hasta que existan en el motor.

## Frontera de confianza del formulario
`about:config` se envia a si misma: la GUI convierte los campos en `about:config?<query>` SOLO si la
pagina actual es la interna (bandera puesta por la propia ruta `about:config` de `do_load` y
`cur_top == NULL`). Un formulario de una pagina web cuyo `action` apunte a `about:config?...` NO
cambia nada (seria una pagina remota reescribiendo la identidad del usuario); sigue el camino normal
y `fm_build` lo bloquea por no ser https.
