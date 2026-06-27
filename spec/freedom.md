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
  --author-css          aplica el CSS de autor (caps.css) en el render headless,
                        para que colores/text-align/font-size/line-height sean
                        revisables visualmente. Solo render local: el cap de
                        imágenes/red sigue OFF (nunca fetch, no telefonea). Default off.
  --js[=off|allowlist|on]   política de JS de página. En el GUI la lee FREEDOM_JS
                        (default allowlist vía js.conf). En headless, corre el JS
                        de la página solo cuando esto resuelve a "on".
  --dump-console        modo headless: corre el JS de la página e imprime la consola
                        capturada (Freebug) — cada console.* y cualquier excepción no
                        capturada del script. Implica JS encendido (una consola con JS
                        apagado no tendría sentido), independientemente del orden de los
                        flags. Es la forma de "ver" el comportamiento de JS sin Wayland.

[url-or-file]:
  - "https://host/..."  → se obtiene con secure_fetch (TLS 1.3, KE híbrido PQ).
  - cualquier otra cosa → se lee como fichero HTML local.
  - si se omite y no se usa --headless, se abre about:blank en el GUI.

SALIDA headless (stdout):
  <título>\n\n<texto extraído>\n

SALIDA --dump-console (stdout, tras la salida normal de la página):
  === Freebug console (<n>) ===
  [<nivel>] <texto>            (una línea por entrada; nivel = log/info/warn/error/debug)
  [notice] console output was truncated (buffer full)   (solo si se llenó el buffer)

SALIDA --download-pdf (fichero):
  Un PDF vectorial US Letter en PATH (mismo pipeline de render que la pantalla y
  que "Save as PDF" del GUI: reusa rd_doc + layout_doc + paint_content_row sobre
  un cairo_pdf_surface_t, tema claro forzado). A stdout solo va una línea de
  confirmación ("Saved PDF (<n> pages): <path>"). Sin red más allá del fetch de
  la página; las imágenes siguen apagadas por defecto (Privacy by Default), así
  que aparecen como placeholders salvo que se habiliten.
```

### `--download-pdf`: razón de ser (revisión visual)

El render del GUI necesita Wayland, que no siempre está disponible para una
herramienta automatizada (CI, un agente de IA, este entorno). `--download-pdf`
exporta la **misma** display list que pinta la pantalla a un PDF vectorial **sin
abrir ventana**, de modo que el resultado pueda inspeccionarse visualmente
(rasterizar con `mutool draw` → PNG y leer la imagen). Es la base de la skill de
revisión visual (ver `CLAUDE.md` §3, paso de validación). PATH es local y de
confianza (lo teclea el operador), así que se usa tal cual; la derivación
fail-closed del nombre desde un título hostil (`pe_safe_basename`) solo aplica al
"Save as PDF" del GUI, donde el nombre proviene de contenido remoto.

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
