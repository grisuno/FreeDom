# doc_title — título de un documento aún no maquetado (`dt_`)

**Por qué:** una pestaña que terminó de cargar en segundo plano (tanda 98, `nav_token`) aparca su
resultado sin maquetarlo, así que su pestaña seguía mostrando la URL hasta volver a ella. Firefox
muestra el título en cuanto llega el documento. `doc_title` lo extrae de los bytes recibidos en el
**lado confiable** sin parser ni red: una función pura, acotada y fuzzeada sobre contenido hostil.

## Contrato

`int dt_scan(const char *html, size_t len, char *out, size_t cap)`

- Devuelve 1 y escribe en `out` (NUL-terminado, `strlen(out) < cap`) el texto del **primer**
  elemento `<title>`; 0 si no hay, si queda vacío tras recortar o si un argumento es inválido
  (`out` queda `""` cuando `cap > 0`).
- Solo mira los primeros `DT_SCAN_MAX` bytes (256 KiB): un título real vive en el `<head>`.
- Se saltan comentarios `<!-- … -->` y el contenido de `<script>`/`<style>`/`<template>`/
  `<textarea>`/`<noscript>`: un `<title>` ahí dentro no es el del documento.
- El texto se decodifica como RCDATA: `&amp; &lt; &gt; &quot; &apos; &nbsp;` y referencias
  numéricas (`&#NNN;`, `&#xHH;`; sin `;` también). Una referencia a NUL, sustituto o > U+10FFFF
  es U+FFFD.
- Blancos ASCII y controles C0/DEL/C1 colapsan a un espacio; se recorta al principio y al final.
- La salida es **UTF-8 válido**: una secuencia inválida es U+FFFD; los controles bidi
  (U+202A–U+202E, U+2066–U+2069, U+200E/F) se eliminan (un título no puede invertir el chrome).
- Se trunca en un límite de punto de código.

## Dado-Cuando-Entonces

- **Dado** `<title>A &amp; B</title>`, **entonces** `A & B`.
- **Dado** `<script>"<title>x</title>"</script><title>Y</title>`, **entonces** `Y`.
- **Dado** `<!-- <title>x</title> --><TITLE>  Z\n z </TITLE>`, **entonces** `Z z`.
- **Dado** `<title>` sin cierre, **entonces** el texto hasta el final del tramo escaneado.
- **Dado** un byte `0xFF` o `&#0;`, **entonces** U+FFFD; **dado** U+202E, se elimina.
- **Dado** `cap` 4 y `<title>ñññ</title>`, **entonces** `ñ` (no se parte un carácter).

## Fuera de alcance

Charsets distintos de UTF-8 (un byte latin-1 sale como U+FFFD hasta que la página se muestra y
el parser real fija el título), `<title>` en SVG.

## Uso

`gui/browser_ui.c`, al aparcar un resultado (`NT_PARK`): el título va a `tab_ctx.ready_title` y la
pestaña lo muestra hasta que la página se maqueta al volver.
