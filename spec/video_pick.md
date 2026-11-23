# video_pick (`vpk_`) — qué vídeo reproduce un clic

> Puro, sin I/O. 2026-11-22. Caso real: jkanime.

## Problema

Desde la tanda 73/75 un `<iframe>` de una página allow∩js es su propio worker confinado y la
ventana lo pinta como una **imagen** (`freedom-frame:` + URL). El reproductor de jkanime vive
dentro del iframe `jkplayer`: el clic caía sobre esa imagen y no reproducía nada, porque la
ventana solo buscaba filas `<video>` del documento principal (el escaneo de iframes del worker
añade un `<video>` al **final** del `<body>`, lejos de donde el usuario hace clic).

## Contrato

```c
const char *vpk_first_video(const pv_view *v);
const char *vpk_for_frame(const pv_view *frame_view, const char *top_video);
```

- **Dado** una vista, **cuando** se pide `vpk_first_video`, **entonces** devuelve el `src` del
  primer run `PV_VIDEO` cuyo `src` es una URL absoluta `http(s)://` con algo tras el esquema
  (sin distinguir mayúsculas), o `NULL`.
- **Dado** un `src` que un script dejó como no-URL (`"[object Object]"`, `blob:`, `javascript:`),
  **entonces** no es un vídeo. Caso real: jkanime pasa el objeto DPlayer a `video.src` en la rama
  sin MSE (en Firefox gana hls.js y esa rama no corre); antes el clic pedía `[object Object]`.
- **Dado** un clic sobre la caja de un frame vivo, **cuando** el documento del frame tiene un
  vídeo, **entonces** se reproduce ESE (`vpk_for_frame` = `vpk_first_video(frame_view)`).
- **Dado** que el frame no tiene vídeo propio (su reproductor arma el `<video>` con JS que el
  motor no ejecuta hasta ahí, o todavía no cargó), **entonces** se usa `top_video`, el primer vídeo del
  documento principal (el que el escaneo de iframes extrajo del HTML del reproductor).
- **Dado** que ninguno tiene vídeo (`top_video` `NULL` o no reproducible por la misma regla), **entonces** `NULL`: el clic sigue su camino normal.
- El puntero devuelto es un alias de la vista; vale mientras la vista viva.

## Seguridad

- No abre red ni decide política: la URL ya pasó por el mismo gate que cualquier `<video>`
  (`video_play` usa el fetcher gateado de la ventana). Elegir entre vídeos ya descubiertos no
  añade capacidad.
- El vídeo se pinta dentro de la caja del frame clicado (lado confiable); el frame nunca toca
  el decoder.

## Fuera de alcance

- Hit-test dentro del documento del frame (qué botón del reproductor se pulsó): cualquier clic
  en la caja del reproductor reproduce, como el botón central de un reproductor real.
