# spec: wl_guard (guardián del socket de Wayland, `wlg_`)

## Problema (reproducido)
El compositor guarda los eventos de un cliente en un búfer de 4 KiB respaldado por el socket. Si el cliente
**no lee** durante varios segundos mientras el puntero se mueve, el compositor lo desconecta:
`libwayland: Data too big for buffer (4084 + 20 > 4096)` / `error in client communication`. Freedom bloquea
su hilo de GUI en cargas de página (JS), descargas de imágenes (Wikipedia con ~30 imágenes: ~8 s) y layouts
grandes, así que cerraba la ventana. Reproducido bajo weston bloqueando 12 s con el puntero en movimiento
(sin guardián: `Broken pipe`; con guardián: la ventana sigue viva).

## Contrato
- **Dado** el hilo de GUI bloqueado, **entonces** un hilo auxiliar lee el socket (`poll` de 100 ms +
  `wl_display_prepare_read_queue` sobre una cola privada siempre vacía + `wl_display_read_events`). Los
  eventos solo se ENCOLAN en las colas de sus proxies: **ningún manejador corre en el hilo auxiliar**; se
  ejecutan en orden en el hilo de GUI cuando el bucle principal despacha.
- No reemplaza al bucle principal (que sigue con `prepare_read`/`read_events`/`dispatch`): libwayland
  coordina a los lectores. Los `pong` de `xdg_wm_base` siguen saliendo del hilo de GUI, así que el
  compositor puede marcar la ventana «sin respuesta», pero no la desconecta.
- `wlg_stop` (antes de `wl_display_disconnect`) para y une el hilo en < 1 s. `FREEDOM_NO_WL_GUARD=1` lo apaga.
- Un `POLLHUP`/`POLLERR` (compositor desaparecido) termina el hilo; el bucle principal informa del error.

## Fuera de alcance
Evitar el bloqueo en sí (las cargas siguen en el hilo de GUI: ticks y geometría ya son asíncronos,
`spec/tab.md`; imágenes y carga de página, no).
