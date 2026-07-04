# Especificación: `freedom` (entrada principal)

> Hito 5+ — Integración final: `freedom` abre el navegador GUI por defecto y
> ofrece modo `--headless` para terminal. Esta spec es el contrato;
> `tests/test_freedom.c` ejercita el modo headless.

## 1. Propósito

`freedom` es la entrada de usuario del navegador. Sin modificadores abre una
ventana Wayland con barra de URL y botones Atrás/Adelante (ver
`spec/browser.md`). Con `--headless` actúa como CLI que carga una URL `https://`
o un fichero HTML local en un worker de pestaña confinado (`tab`) y emite el
título y el texto extraído por stdout.

## 2. Entradas y salidas

```
freedom [OPTIONS] [url-or-file]

OPTIONS:
  -h, --help        muestra uso y termina con éxito
  -V, --version     muestra la versión y termina con éxito
  -H, --headless    modo terminal: renderiza una única página a stdout y sale
  --download-pdf=PATH   modo headless: renderiza la página a un PDF vectorial en
                        PATH (sin abrir ventana) y sale. Implica --headless.
  --download-png=PATH   modo headless: renderiza la página a una imagen PNG única
                        (mapa de bits de altura completa) en PATH y sale. Implica
                        --headless. Es el artefacto MÁS BARATO de revisar (se lee
                        la imagen directa, sin paso de rasterizado de PDF).
  --author-css          aplica el CSS de autor (caps.css) en el render headless,
                        para que colores/text-align/font-size/line-height sean
                        revisables visualmente. Solo render local: el cap de
                        imágenes/red sigue OFF (nunca fetch, no telefonea). Default off.
  --js[=off|allowlist|on]   política de JS de página. En el GUI la lee FREEDOM_JS
                        (default allowlist vía js.conf). En headless, corre el JS
                        de la página solo cuando esto resuelve a "on". Con JS on el
                        headless también: (a) concede la red de página (XHR/fetch y
                        scripts externos <script src>, Hito 24 EXT) — el --js=on del
                        operador es la señal de confianza que en el GUI dan
                        allow.conf ∩ js.conf; el fetcher del padre resuelve la URL
                        cruda contra la URL de la página (ln_resolve: https-only,
                        sin downgrade) antes de tocar la red; y (b) SIGUE la
                        navegación pedida por el JS (location.href=/assign/replace),
                        cada salto por el camino normal de fetch (re-aplica TODA la
                        política), con cap anti-bucle HL_JS_NAV_MAX (10) — espejo del
                        JS_NAV_MAX del GUI. Sin esto, un interstitial que reenvía por
                        JS (p. ej. el challenge de un buscador) rendería como cáscara
                        vacía en vez de su destino.
  --dump-console        modo headless: corre el JS de la página e imprime la consola
                        capturada (Freebug) — cada console.* y cualquier excepción no
                        capturada del script. Implica JS encendido (una consola con JS
                        apagado no tendría sentido), independientemente del orden de los
                        flags. Es la forma de "ver" el comportamiento de JS sin Wayland.
  --dump-dom            modo headless: imprime el árbol de render listo para pintar
                        (dom_debug: bloques, cajas, contenedores) a stdout. Es la entrada
                        al layout (la estructura). Honora --author-css. No corre JS.
  --dump-layout         modo headless: imprime la GEOMETRÍA resuelta (cajas in-flow +
                        positioned boxes, en orden de stacking) a stdout. Es la SALIDA
                        del layout — el complemento de --dump-dom: --dump-dom muestra la
                        estructura (entrada), --dump-layout muestra los rectángulos que
                        el motor de cajas produjo (salida). Honora --author-css. Es la
                        forma de verificar position/z-index/box-engine sin Wayland ni
                        imagen: los bugs de anclaje/fragmentación se ven como números.

[url-or-file]:
  - "https://host/..."  → se obtiene con secure_fetch (TLS 1.3, KE híbrido PQ).
  - cualquier otra cosa → se lee como fichero HTML local.
  - si se omite y no se usa --headless, se abre about:blank en el GUI.

SALIDA headless (stdout):
  <título>\n\n<texto extraído>\n

SALIDA --dump-console (stdout, tras la salida normal de la página):
  === Freebug console (<n>) ===
  [<nivel>] <texto>                      (entrada sin ubicación, p. ej. un console.log)
  [<nivel>] <file>:<line>:<col>  <texto> (error con sitio de lanzamiento; p. ej.
                                          inline #9:2:54 para el 9º <script> inline)
  [notice] console output was truncated (buffer full)   (solo si se llenó el buffer)

SALIDA --download-pdf (fichero):
  Un PDF vectorial US Letter en PATH (mismo pipeline de render que la pantalla y
  que "Save as PDF" del GUI: reusa rd_doc + layout_doc + paint_content_row sobre
  un cairo_pdf_surface_t, tema claro forzado). A stdout solo va una línea de
  confirmación ("Saved PDF (<n> pages): <path>"). Sin red más allá del fetch de
  la página; las imágenes siguen apagadas por defecto (Privacy by Default), así
  que aparecen como placeholders salvo que se habiliten.

SALIDA --download-png (fichero):
  Un PNG ARGB único (1000px de ancho, altura = contenido maquetado, acotada a
  30000px anti-DoS — una página más alta se recorta) en PATH. Mismo pipeline de
  render que la pantalla y el PDF (rd_doc + layout_doc + paint_content_row sobre
  un cairo_image_surface_t, tema claro forzado), pero SIN paginar: un solo mapa
  de bits continuo de toda la página. A stdout solo va "Saved PNG (<h> px):
  <path>". Mismas reglas de Privacy by Default que el PDF (imágenes off →
  placeholders). Es la salida preferida para revisión visual automatizada: se
  lee la imagen directamente, sin el paso de rasterizado de PDF (mutool).

SALIDA --dump-layout (stdout):
  === Freedom layout ===
  content_w=<W> total_h=<H> nbox=<N> nrow=<R> npositioned=<P>
    box[<i>] bid=<block_id> x=<X> top=<Y> w=<W> h=<H>     (una por caja in-flow)
    pos[<i>] box=<box_index> z=<z_index> x=<X> y=<Y> w=<W> h=<H>  (una por positioned)
  El motor de cajas (layout_doc + position_doc) sobre el mismo rd_doc que pinta
  la pantalla, sin abrir ventana. Puro: no abre socket, no lee fichero, no
  muta el doc. Los valores ya están acotados por css/box_tree (CSS_LEN_MAX,
  BT_MAX_POSITIONED). Fail-closed: doc vacío → UI_ERR_NULL_ARG (no imprime nada).
```

### `--download-pdf` / `--download-png`: razón de ser (revisión visual)

El render del GUI necesita Wayland, que no siempre está disponible para una
herramienta automatizada (CI, un agente de IA, este entorno). Ambos flags
exportan la **misma** display list que pinta la pantalla **sin abrir ventana**.

- `--download-png` (preferido) escribe **directamente** un PNG: el agente lo lee
  con un solo paso, sin rasterizar. Por eso es la salida por defecto de la skill
  de revisión visual — un PNG cuesta muchos menos tokens que un PDF (que primero
  hay que pasar por `mutool` a PNG, o leerlo página a página).
- `--download-pdf` escribe un PDF vectorial (texto seleccionable, paginado a US
  Letter); útil cuando se quiere el documento real para guardar/imprimir, no solo
  una captura. Para inspeccionarlo se rasteriza con `mutool draw` → PNG.

Es la base de la skill de revisión visual (ver `CLAUDE.md` §3, paso de
validación). PATH es local y de confianza (lo teclea el operador), así que se usa
tal cual; la derivación fail-closed del nombre desde un título hostil
(`pe_safe_basename`/`pe_build_path_ext`) solo aplica al "Save as PDF/PNG" del GUI,
donde el nombre proviene de contenido remoto.

## 3. Códigos de salida

| Código | Significado |
| :-- | :-- |
| 0 | Éxito: GUI cerrada normalmente o headless terminó. |
| 1 | Error de ejecución: red, fichero ilegible, parseo/JS falló, etc. |
| 2 | Error de uso. |

## 4. Garantías de seguridad

- Solo se cargan URLs `https://` o ficheros locales; cualquier otro esquema se
  rechaza antes de tocar la red.
- El contenido remoto se parsea/ejecuta solo dentro del worker `tab` confinado
  con seccomp/Landlock.
- Fail-closed: si el worker no puede confinarse o la carga falla, no se emite
  contenido parcial.

## 5. Dependencias de build

`build/freedom` enlaza contra el pipeline completo: `tab`, `os_sandbox`,
`html_parse`, `dom`, `js_sandbox`, `js_dom`, `js_env`, `anti_fp`, QuickJS
vendoreado, `secure_fetch`, `request_policy`, `psl_data`, más Wayland/Cairo
(`gui/browser_ui.c`) y xkbcommon, junto con `-lcurl -lssl -lcrypto -llexbor
-lm -lpthread -lwayland-client -lcairo -lxkbcommon`.
