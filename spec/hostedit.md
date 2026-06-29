# spec: hostedit (`he_`) — edit the user's host lists from the UI

> Pure, I/O-free helper behind the "Block site / Allow site / Allow JS" UI actions
> (hamburger + `Ctrl+Shift+B`/`A`/`J`). It turns the **current page's host** (hostile
> data with provenance) into the exact line to append to a `/etc/hosts`-format list
> (`block.conf` / `allow.conf` / `js.conf`), validated fail-closed. The file I/O, the
> atomic append and the in-memory reload are the orchestrator's job (`gui/browser_ui.c`).

## Entradas / salidas

- `he_make_line(host, out, cap)` → `HE_OK` and writes `"<host>\n"` (lowercased), or a
  status. `he_text_has_host(text, host)` → 1/0.

## Garantías de seguridad (fail-closed)

- **Solo hostnames registrables.** `host` debe ser 1..253 bytes de `[A-Za-z0-9.-]`,
  en labels de 1..63 separados por `.`, sin label vacío (`a..b` ❌), sin `-` al borde
  de un label. Cualquier cosa con esquema, `/`, `:`, `@`, `?`, `#`, espacios o bytes
  de control se **rechaza** (`HE_ERR_INVALID_HOST`) → nunca se escribe basura ni un
  path en un archivo de config.
- **Sin I/O ni asignación.** El módulo solo decide el texto; no abre archivos.
- **Append idempotente.** `he_text_has_host` deja que el orquestador no duplique una
  entrada ya presente (ignora el campo IP `0.0.0.0` y comentarios `#`).

## Tabla de errores

| Status | Causa |
| :-- | :-- |
| `HE_OK` | host válido; `out` = `"host\n"` |
| `HE_ERR_NULL_ARG` | `host`/`out` NULL |
| `HE_ERR_INVALID_HOST` | host no es un hostname registrable plausible |
| `HE_ERR_RANGE` | `cap` < `strlen(host)+2` |

## Given-When-Then

- **Dado** host `News.YCombinator.com`, **cuando** `he_make_line`, **entonces**
  `HE_OK` y `out == "news.ycombinator.com\n"` (minúsculas).
- **Dado** host `evil.com/../../etc`, **cuando** `he_make_line`, **entonces**
  `HE_ERR_INVALID_HOST` (`/` prohibido).
- **Dado** host `a..b` o `-x.com` o `x-.com` o `` (vacío), **entonces**
  `HE_ERR_INVALID_HOST`.
- **Dado** un texto `"0.0.0.0 ads.example\n# c\nexample.com\n"` y host `example.com`,
  **cuando** `he_text_has_host`, **entonces** 1; con host `other.com`, 0; con host
  `ads.example`, 1 (se ignora el token IP, no el dominio).

## Fuera de alcance

Resolver el host desde la URL (lo hace el orquestador con `rp_host_of`/`url_split`),
elegir el directorio de escritura, el formato `0.0.0.0 host` (se escribe el dominio
desnudo, que `hostblock` acepta), y borrar entradas.
