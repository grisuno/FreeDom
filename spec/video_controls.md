# video_controls (`vcl_`) — barra nativa del reproductor

## Por qué

La reproducción (`media_decoder` + feeder HLS) corre en el lado confiable y se pinta encima
de la caja del `<video>` o del iframe-reproductor (`spec/video_pick.md`). La barra del autor
(DPlayer en jkanime) vive en el DOM del frame y maneja un `<video>` que el motor no reproduce:
sus clics no llegan nunca a la reproducción real, y además queda tapada por el vídeo. El
navegador dibuja entonces SU barra, como hace Firefox con `controls`: pausa/reanudar,
posición, duración y búsqueda por clic en la pista.

## Contrato (módulo puro, sin I/O, sin reloj)

| Función | Entrada | Salida |
| :-- | :-- | :-- |
| `vcl_layout(x,y,w,h,&g)` | rect del vídeo en coordenadas de ventana | geometría de la barra (fondo, botón, pista, texto); 0 si el rect no admite barra |
| `vcl_hit(&g,&video,px,py,&frac)` | punto del puntero | `VCL_HIT_NONE` (fuera), `VCL_HIT_TOGGLE` (botón o superficie del vídeo), `VCL_HIT_SEEK` con `frac ∈ [0,1]`, `VCL_HIT_BAR` (resto de la barra: no hace nada pero no cae a la página) |
| `vcl_total(pl)` | playlist parseada | duración total en s |
| `vcl_segment_at(pl,t,&start)` | instante t en s | índice del segmento que contiene t y su comienzo |
| `vcl_position(base,pts0,pts,total)` | comienzo del segmento de arranque + PTS del primer cuadro + PTS actual | posición en s, acotada a `[0,total]` |
| `vcl_format_time(s,buf,cap)` | segundos | `m:ss` o `h:mm:ss`; truncado ⇒ 0 (V-004) |

## Garantías (Dado–Cuando–Entonces)

- **Dado** una playlist hostil con `#EXTINF` `NaN`, `inf`, negativos o enormes, **cuando** se
  suma o se busca, **entonces** cada duración no finita o negativa cuenta 0 y cada una se acota a
  `VCL_MAX_SEGMENT_S` (24 h): el total es finito y nunca UB.
- **Dado** `frac` fuera de `[0,1]` o `NaN`, **cuando** se busca, **entonces** se acota (`NaN` ⇒ 0).
- **Dado** un instante más allá del final, **cuando** `vcl_segment_at`, **entonces** devuelve el
  último segmento (nunca un índice fuera de rango); playlist vacía o NULL ⇒ 0.
- **Dado** un PTS anterior al de arranque o un salto absurdo, **cuando** `vcl_position`,
  **entonces** la posición queda en `[0,total]`.
- **Dado** un rect demasiado chico (alto < `VCL_MIN_H` o ancho < `VCL_MIN_W`), **cuando**
  `vcl_layout`, **entonces** devuelve 0 y no hay barra: un clic en la superficie sigue alternando.
- La barra se pinta con el vídeo; con pausa se ve siempre, reproduciendo solo con el puntero
  encima. Un clic en el rect del vídeo NUNCA cae a la página ni reinicia la reproducción.
- Teclado con el puntero sobre el vídeo: `Espacio`/`k` alternan, `←`/`→` buscan ±10 s.

## Búsqueda

La búsqueda es por segmento: el feeder y el decoder se reinician desde el segmento que contiene
el instante pedido (`video_restart_at`), reutilizando la playlist ya validada (no se vuelve a
pedir). Sin `#EXT-X-ENDLIST` ni duraciones (total 0) la pista no busca.

## Fuera de alcance

Volumen, velocidad, subtítulos, búsqueda dentro de un segmento, la barra del autor (sus
eventos `pause`/`seeked` no se emiten al DOM del frame).
