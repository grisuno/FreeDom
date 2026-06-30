# spec: dom_debug (`dd_`) — agent-readable dump of the paint-ready render tree

> **Why.** Freedom resolves a lot of CSS into the render tree but the relationship
> between a source node, the box it joined, its container, and its author box/style is
> invisible — so diagnosing *why* a node lays out wrong (the "CSS paint gap") is
> guesswork. `dom_debug` makes that tree **visible and deterministic**: it formats an
> already-built, inert `rd_doc` (`[[render_doc]]`) into a line-oriented text dump that
> is greppable by a human and by an agent (Principle 6, Agent-Friendly: structured,
> deterministic, no hidden state). It is the instrument the `position`/box work
> (`[[box_engine]]`) is diagnosed with.
>
> It is read **headless** (`freedom --dump-dom`, stdout) and, because the same dump can
> be rasterised, **in the GUI via the PNG export** (CLAUDE.md §3: PNG is the cheap,
> one-step visual-review channel — preferred over PDF). One formatter, two channels.

## Scope

- **In:** the logical paint-ready tree — every `rd_block` (kind, tag, flags, container
  group, box id, author style/box annotations, truncated text, href) and the
  box-definition tree (`rd_doc.boxes`: parent link, placement, decoration).
- **Out (own follow-ups):** painted pixel geometry (x/y/width after `layout_doc`) lives
  in the GUI orchestrator, not in the pre-layout `rd_doc`; the live Lexbor node tree
  lives in the confined worker and is destroyed after `pv_build`. `dom_debug` dumps what
  the trusted side actually paints from, which is exactly what reveals a paint gap.

## Security posture (non-negotiable)

- **Pure, I/O-free.** `dd_format` reads an inert `rd_doc` and writes a caller buffer.
  It opens no socket, reads no file, runs no script, walks no hostile DOM. The hostile
  bytes it touches (a block's `text`/`href`) were already normalised to valid UTF-8 and
  bounded by `[[page_view]]`.
- **Bounded / fail-closed.** `dd_format` never writes past `cap-1` and always
  NUL-terminates when `cap > 0`. Each variable-length field (text, href) is truncated
  to a fixed cap (`DD_FIELD_MAX`) and control bytes are escaped, so a hostile document
  cannot blow up or smear the dump. It returns the number of bytes that *would* be
  written (snprintf semantics) so a caller can detect truncation; it allocates nothing.
- **No new capability.** The dump exposes only what `rd_doc` already carries on the
  trusted side. It is a diagnostic, not a parser: it adds no attack surface.

## API

```c
size_t dd_format(const rd_doc *doc, char *out, size_t cap);
```

- Formats `doc` into `out[0..cap)` as a NUL-terminated, line-oriented dump.
- Returns the byte count that *would* be written excluding the NUL (snprintf
  semantics); `>= cap` means the output was truncated.
- `doc == NULL` formats a valid empty tree (header with zero counts).
- `out == NULL` or `cap == 0` only measures (writes nothing).

## Output format (stable; one block/box per line)

```
=== Freedom render tree ===
blocks: <N>  boxes: <M>  containers: <C>  has_images: <0|1>
[boxes]
  #<id> parent=<pid> place(l=<l> r=<r> w=<w> center=<0|1>) bg=<#rrggbb|-> pad(<t>/<r>/<b>/<l>) bord(<tw>/<rw>/<bw>/<lw> <style>) radius=<n> shadow=<0|1> outline=<n>
  ...
[blocks]
  #<i> <kind> <tag> [bb] [h<lvl>] [b] [i] [indent=<n>] [cont=#<id>(<flex|grid> cols=<n> gap=<n> <justify>)] [box=#<id>] [align=<kw>] [fscale=<n>] [lscale=<n>] [fg=<#rrggbb>] [bg=<#rrggbb>] [w=<n>] [ins(l=<n> r=<n>)] [center] href=<...> "<text>"
```

Concretely, three blocks render as:

```
  #0 heading <h2> bb h2 "Title"
  #1 paragraph <p> bb "body text"
  #2 link <a> href=https://e.example/x "click"
```

- A bracketed field is **emitted only when set** (non-default), so the noise is low and
  the signal — which blocks joined a container/box, which carry a width cap — is clear.
- `[boxes]` is present only when `rd_doc.boxes` is non-empty (i.e. author CSS on);
  `bg=-` / `fg` absent means "unset".
- `<kind>` is `rd_kind_name` (lowercase, canonical), `<tag>` is `rd_block_tag` (NULL
  tag prints `-`).
- Text is truncated to `DD_FIELD_MAX` (a trailing `…` marks truncation) and control
  bytes (`< 0x20`) render as `.` so one block stays one line.

### Given-When-Then

- **Given** an `rd_doc` with a heading, a paragraph and a link, **when**
  `dd_format(doc, buf, big)`, **then** the output starts with the `=== Freedom render
  tree ===` header, reports `blocks: 3`, and has one `[blocks]` line per block naming
  its kind and tag in document order.
- **Given** a grid container of three cells (a table), **when** dumped, **then** the
  three cell blocks share one `cont=#<id>(grid cols=3 …)` annotation — the field that
  reveals a collapsed table column.
- **Given** author CSS that puts a `max-width` + centered margin on a wrapper, **when**
  dumped, **then** a `[boxes]` section lists the box with its `place(...w=<n>...)` and
  the wrapper's blocks carry `box=#<id>` — the fields that reveal a width constraint.
- **Given** `doc == NULL`, **when** `dd_format(NULL, buf, big)`, **then** the header
  reports `blocks: 0  boxes: 0  containers: 0` and the call does not crash.
- **Given** any `doc` and a tiny `cap`, **when** `dd_format(doc, buf, 4)`, **then** the
  return value is the full untruncated length, `buf` is NUL-terminated, and no byte past
  `buf[3]` is written (the truncation/no-overflow invariant the fuzzer pins).

## Errors

No status codes: a pure formatter cannot fail short of the caller passing a buffer, and
truncation is reported by the return value, not an error. Malformed author CSS / hostile
text were already dropped or normalised upstream (`[[css]]`, `[[page_view]]`).

## CLI / GUI surface

- Headless: `freedom --dump-dom <url|file>` prints `dd_format` to stdout and exits
  (implies `--headless`; honours `--author-css` so the box tree is populated). It is a
  diagnostic with no window, exactly like `--dump-console` (`[[freebug]]`).
- GUI/PNG: the same dump is rasterised by the PNG export path so it is reviewable
  without a Wayland display (CLAUDE.md §3, PNG-preferred doctrine). See `freedom.md`.
