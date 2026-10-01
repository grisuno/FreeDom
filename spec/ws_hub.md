# ws_hub — conexiones WebSocket de una página de confianza (lado confiable)

> Estado: SDD (2026-09-30). Módulo `ws_hub` (`wh_`). Plan B5. Vive del lado confiable (GUI):
> el worker confinado nunca toca un socket (`spec/js_dom.md` §7f).

## 1. Propósito

Sostener los WebSocket que abrió el JS de una página allow∩js: abrirlos sin congelar la
interfaz, bombear sus mensajes y entregarlos como eventos, y cerrarlos todos cuando la página
cambia. La política de red (TLS/PQ/realm/identidad) la aplica `sf_ws_open`; la decisión de
**si** abrir (host de confianza, `hostblock`, realm, navegabilidad) la toma el llamante antes de
pedirle nada al hub.

## 2. Modelo

- Hasta `WH_MAX` (= `JD_WS_MAX`, 8) conexiones, identificadas por el id que eligió la página.
- `wh_open_async` copia URL y configuración (todas las cadenas) a un trabajo y lanza un hilo
  que llama a `sf_ws_open`; el resultado vuelve por un **socketpair** cuyo extremo de lectura el GUI
  mete en su `poll` (`wh_notify_fd`). El hilo escribe en su **propio `dup`** del extremo de
  escritura y lo cierra al terminar: aunque el hub se libere, nunca escribe en un descriptor
  reutilizado (`send` con `MSG_NOSIGNAL`: un hub ya liberado da `EPIPE`, nunca SIGPIPE, sin depender de la disposición de señales del proceso).
- Cada apertura lleva la **generación** del hub; `wh_close_all` la incrementa, así que un
  resultado que llega tarde para una página que ya no está se cierra y se descarta.
- `wh_on_readable` lee sin bloquear y **reensambla** fragmentos hasta completar un mensaje
  (`left == 0` y sin `CURLWS_CONT`), acotado a `SF_WS_MAX_MESSAGE`; emite `WH_EV_TEXT`/`BINARY`.
  Un marco de cierre emite `WH_EV_CLOSE`; un error de red o un mensaje gigante emite
  `WH_EV_ERROR` + `WH_EV_CLOSE` (código 1006) y libera la conexión.
- Los eventos salen por un callback `wh_emit_fn(ctx, id, kind, code, data, len)`; los tipos
  coinciden con `tab_ws_event_kind`.

## 3. API

```c
wh_hub *wh_new(void);                      /* NULL si no hay memoria o pipe */
void    wh_free(wh_hub *h);                /* cierra todo; NULL es no-op */
int     wh_notify_fd(const wh_hub *h);
int     wh_open_async(wh_hub *h, int id, const char *url, const sf_config *cfg);
void    wh_on_notify(wh_hub *h, wh_emit_fn emit, void *ctx);
int     wh_send(wh_hub *h, int id, const void *data, size_t len, int binary);
void    wh_close(wh_hub *h, int id);       /* cierre pedido por la página: frame close */
void    wh_close_all(wh_hub *h);           /* página nueva: todo fuera, generación++ */
size_t  wh_poll_fds(const wh_hub *h, struct pollfd *out, int *ids, size_t cap);
void    wh_on_readable(wh_hub *h, int id, wh_emit_fn emit, void *ctx);
```

`wh_open_async` devuelve -1 (sin lanzar nada) con id duplicado, hub lleno o memoria agotada;
el llamante entrega entonces `ERROR`+`CLOSE` a la página.

## 4. Garantías

- Ningún recurso cruza a la página: solo datos por el callback.
- Memoria acotada: `WH_MAX` × `SF_WS_MAX_MESSAGE`.
- Un hilo nunca toca el hub; el hub solo se toca en el hilo del GUI.

## 5. Pruebas (`tests/test_ws_hub.c`)

Sin red: una URL que `sf_ws_url_check` rechaza hace fallar la apertura en el hilo antes de
tocar un socket, lo que ejercita el ciclo completo (hilo → pipe → `wh_on_notify` → `ERROR` +
`CLOSE`), más duplicados, tope, `wh_close_all` con resultado tardío y envío a id inexistente.
El camino de red real se verificó a mano contra un eco `wss://` (política por defecto:
`SF_ERR_KEM_NOT_PQ`; política clásica: eco correcto).
