# Vendored Public Suffix List

- File: `public_suffix_list.dat`
- Source (authoritative, pull ONLY from here):
  https://publicsuffix.org/list/public_suffix_list.dat
- License: Mozilla Public License v2.0 (see the header inside the file).
- Vendored copy taken: 2026-06-15 (from the system `publicsuffix` package,
  list dated 2026-04-28).

## Why vendored (and not `libpsl`)

Per the project doctrine, every dependency must justify itself by attack-surface
reduction. The PSL is *data*, not code: vendoring the canonical `.dat` and
compiling a sorted, read-only lookup table from it at build time
(`tools/gen_psl.c` -> `build/psl_data.c`) avoids linking `libpsl` (a whole
library with its own parsers and update logic) while keeping the suffix logic
pure and in-memory. The `.dat` is the single source of truth; the table is
derived, never hand-edited.

## Regenerating / updating

Replace `public_suffix_list.dat` with a fresh copy from the URL above. The build
regenerates `build/psl_data.c` automatically (`make` depends on the `.dat`).

## Known limitation

Rules are matched as lowercased UTF-8 text exactly as they appear in the list.
Full IDNA2008 / punycode normalization of internationalized hosts is out of
scope for v1; ASCII and already-punycoded hosts match correctly.
