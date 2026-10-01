# import_map — `<script type="importmap">` (WHATWG HTML §8.1.5.3)

> Estado: SDD (2026-09-30). Módulo puro `import_map` (`im_`), sin I/O. Plan B6.

## 1. Propósito

Los sitios modernos importan módulos por **especificador desnudo** (`import React from
"react"`) y declaran a qué URL corresponde cada uno en un import map. Sin él, esos imports
fallan (`TypeError`) y la aplicación entera no arranca (medido en github.com: `react`,
`react-dom`, …).

## 2. Modelo

- **Entrada:** el texto JSON del primer `<script type="importmap">` inline del documento (un
  import map externo con `src` no existe en HTML). Es contenido hostil: se parsea con un parser
  **propio y acotado** que solo acepta lo que un import map puede ser — un objeto cuyos
  miembros `imports` y `scopes` son objetos de cadenas (y `scopes`, objeto de objetos de
  cadenas). Cualquier otro miembro de nivel superior se ignora (`integrity`, futuros); un JSON
  mal formado ⇒ mapa vacío (fallar cerrado = comportamiento previo).
- **Normalización (al parsear):** cada dirección se resuelve contra la URL del documento con
  el resolvedor del llamante (el mismo que usan los módulos: https o `file://` confinado); una
  dirección que no resuelve se descarta. Una clave con forma de URL (`/`, `./`, `../` o con
  esquema) se normaliza igual; una clave desnuda queda tal cual. Un prefijo de `scopes` se
  resuelve contra la URL del documento.
- **Resolución** (`im_resolve(map, base, especificador)`):
  1. Si el especificador es relativo (`/`, `./`, `../`) o absoluto, `asURL` = su resolución
     contra `base`; si no, `asURL` = nada (desnudo).
  2. Clave normalizada = `asURL` si existe, si no el especificador.
  3. Por cada scope cuyo prefijo coincide con `base` (igual, o prefijo terminado en `/`), del
     más largo al más corto: buscar la clave en su mapa.
  4. Buscar la clave en `imports`.
  5. Búsqueda en un mapa: igualdad exacta ⇒ dirección; si no, la clave más larga que termina
     en `/` y es prefijo ⇒ dirección + resto (la dirección debe terminar en `/`, si no la
     entrada no aplica).
  6. Sin coincidencia: `asURL` si existe; un desnudo sin coincidencia falla.
- **Cotas:** texto ≤ `IM_MAX_TEXT` 1 MiB, ≤ `IM_MAX_ENTRIES` 4096 entradas en total,
  ≤ `IM_MAX_SCOPES` 256 scopes, profundidad JSON ≤ 3. Pasado cualquiera, el mapa queda vacío.

## 3. API

```c
typedef int (*im_url_fn)(void *ctx, const char *base, const char *ref, char *out, size_t outsz);
im_map *im_parse(const char *json, size_t len, const char *doc_url, im_url_fn resolve, void *ctx);
int     im_resolve(const im_map *m, const char *base, const char *spec,
                   im_url_fn resolve, void *ctx, char *out, size_t outsz);   /* 0 / -1 */
size_t  im_count(const im_map *m);
void    im_free(im_map *m);
```

`im_parse` nunca devuelve NULL salvo sin memoria: un JSON inválido da un mapa vacío.

## 4. Integración

`html_parse` clasifica `type="importmap"` (inline) con el flag `importmap`; el worker usa el
**primero** antes de ejecutar ningún script y `tab_mod_resolve` consulta el mapa. Aplica a todo
host con JS (un import map no abre red: sus direcciones igual pasan por el cargador de
módulos, que solo carga en una página de confianza).

## 5. Fuera de alcance

Varios import maps combinados (se usa el primero), `integrity`, import maps externos,
`import.meta.resolve`.
