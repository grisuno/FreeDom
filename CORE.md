# CORE.md — using Freedom as dependency

Read this when consuming Freedom libraries without editing internals.
For editing internals read `AGENTS.md` instead, never both.

## What Freedom is

Security-first minimal browser engine in pure C11. Renders HTML/CSS to
display list, paints via Cairo Wayland. Fail-closed. Private by default.

## Reuse boundaries

- Stable pure units: `css_length`, `css_color`, `url`, `box_tree`, `flex_layout`, `block_flow`, `text_shape`, `image_decode`, `data_url`.
- Process isolation: `tab` fork+exec worker, seccomp mandatory, Landlock best-effort. Parent never parses hostile bytes.
- Network: `secure_fetch` libcurl OpenSSL 3.5 TLS1.3 min, hybrid X25519MLKEM768. No liboqs.
- State: `local_store` AEAD Argon2id, 0600, atomic replace, anti-replay.

## Integration contract

- Include `include/<module>.h`. Pure C11, C++ rejected.
- Single owner, single idempotent free per object. NULL-safe frees.
- Fallible init returns status enum, never partial object on success path.
- No global mutable state. No absolute paths required. No hidden IO.
- Layout tunables read from `include/freedom_config.h` `FC_*` at compile time.

## Do not depend on

- `gui/` internals. Wayland chrome only, not a library.
- `src/tab.c` static wire layout. Use `tab_*` API in `include/tab.h`.
- `third_party/` directly. QuickJS Lexbor vendored, version pinned.
