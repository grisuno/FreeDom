# frame_broker (`fbk_`) -- corredor de iframes y `postMessage` del lado confiable

Enmienda del dueno 2026-10-26: un host en allow.conf Y js.conf recibe iframes vivos y `postMessage`.
Cada iframe es **su propio documento en su propio worker confinado** (un proceso por documento, como
una pestana); el worker nunca ve a otro. El padre (confiable) lleva el arbol de frames y **media**
todo mensaje. Este modulo es la parte pura: registro del arbol y decision de enrutado.

## 1. Entradas / salidas
- `fbk_origin_of(url, out, cap)`: origen serializado `https://host[:puerto]` en minusculas; `"null"`
  (opaco) para `data:`, `about:`, `file:`, no-https o ilegible. Devuelve 0 / -1 (buffer chico).
- `fbk_table`: registro con tope `FBK_MAX_FRAMES` (16) y profundidad `FBK_MAX_DEPTH` (4). El frame 0 es
  el documento top.
- `fbk_add(t, parent, url, &id)`, `fbk_remove(t, id)` (quita el subarbol), `fbk_origin(t, id)`.
- `fbk_route(t, from, rel, child, target_origin, size, &dest)`: decide a quien llega un mensaje.

## 2. Dado-Cuando-Entonces
- Dado un frame `from`, cuando envia a `FBK_REL_PARENT` / `FBK_REL_TOP` / `FBK_REL_CHILD(child)`,
  entonces `dest` es ese frame; **hermanos y descendientes lejanos no son direccionables**.
- Dado `target_origin`: `"*"` entrega; `"/"` entrega solo si el destino tiene el origen del emisor;
  un origen exacto entrega solo si coincide con el del destino; cualquier otro texto (no
  serializable) => `FBK_DROP_ORIGIN`. Un origen opaco (`"null"`) nunca coincide con un exacto.
- Dado `size > FBK_MAX_MSG` (1 MiB) => `FBK_ERR_SIZE`. Frame inexistente/muerto => `FBK_ERR_FRAME`.
- Dado un mensaje entregado, `out->sender_origin` es el origen real del emisor (lo fija el padre; el
  worker no puede falsearlo).
- Dado `fbk_add` con padre inexistente, profundidad > 4, o tabla llena => error (fail-closed).

## 3. Garantias
Puro, sin I/O ni estado global, reentrante, entradas hostiles (todo texto es dato). Fuzzeado
(`make fuzz-fbk`). Fuera de alcance: serializacion del payload (structuredClone lo hace el worker),
la carga/pintado del iframe y el acceso DOM directo (cross-origin siempre denegado: no existe).

## 4. `frame_host` (`fh_`) -- el lado padre que conecta workers y corredor
Un `fh_host` por documento top trusted. Mantiene un `fbk_table` y **una pestana-worker por frame**
(`tab_open`, confinada como cualquier otra). Entradas: las ops que el worker anota
(`tab_ws_op` kinds `FRAME_OPEN` / `FRAME_CLOSE` / `FRAME_POST`).
- Dado `FRAME_OPEN` (token, url): `fbk_add`, baja el HTML por el **mismo fetcher con politica** de la
  pagina (`tab_fetch_fn`), carga el worker con `tab_set_frame_id(id)` y procesa las ops de su carga.
  Falla (fetch, fbk, worker) => el frame no existe (fail-closed, sin huecos en el arbol).
- Dado `FRAME_CLOSE`: cierra el subarbol (`fbk_remove` + `tab_close` de cada worker).
- Dado `FRAME_POST`: `fbk_route`; `FBK_DELIVER` => mensaje `origenEmisor\nrelacion\nJSON`
  (relacion: `p` si el emisor es el padre del receptor, `c<token>` si es su hijo; para el top que
  recibe de un nieto se usa el token del hijo del top que lo contiene). Al top se entrega por el
  callback `top_msg`; a un frame por `tab_ws_event(TAB_WSE_FRAME_MSG)`, y sus ops se procesan en
  seguida con un tope de profundidad (`FH_MAX_DEPTH`) contra ping-pong; lo que sobre espera al tick.
- `fh_tick` avanza el reloj virtual de cada frame y procesa sus ops; devuelve el proximo timer.
- Un frame no se pinta (documento oculto): reCAPTCHA v3 / BotGuard de fondo; el pintado visible es
  un hito aparte.
