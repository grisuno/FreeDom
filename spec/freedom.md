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

[url-or-file]:
  - "https://host/..."  → se obtiene con secure_fetch (TLS 1.3, KE híbrido PQ).
  - cualquier otra cosa → se lee como fichero HTML local.
  - si se omite y no se usa --headless, se abre about:blank en el GUI.

SALIDA headless (stdout):
  <título>\n\n<texto extraído>\n
```

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
