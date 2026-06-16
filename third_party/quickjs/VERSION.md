# Vendored dependency: QuickJS-ng

- **Project:** quickjs-ng (actively maintained fork of Bellard's QuickJS)
- **Version:** v0.15.1 (pinned)
- **Source:** https://github.com/quickjs-ng/quickjs/archive/refs/tags/v0.15.1.tar.gz
- **Tarball SHA-256:** `c4e813951b7c46845096a948e978c620b11ab4cf5fd622ca09c727ec31f42623`
- **License:** MIT (see `LICENSE`)

## Why vendored

Zero Trust toward dependencies: pinning the exact sources fixes the attack surface we audit,
instead of tracking a moving system package. The header `quickjs.h` is encapsulated behind
`include/js_sandbox.h` (no `JS*` / `JSValue` type leaks into the project API).

## What is included (and what is deliberately NOT)

Only the **core engine** translation units are vendored:

- `quickjs.c` — the engine
- `libregexp.c` — regular expressions
- `libunicode.c` — Unicode tables/algorithms
- `dtoa.c` — number <-> string conversion

plus the headers they include (`cutils.h` is header-only in quickjs-ng, `list.h`, `quickjs.h`,
`libregexp*.h`, `libunicode*.h`, `dtoa.h`, `quickjs-atom.h`, `quickjs-opcode.h`,
`quickjs-c-atomics.h`, `builtin-*.h`).

**`quickjs-libc.c` / `quickjs-libc.h` are intentionally NOT vendored.** That module is the
entire host I/O surface of QuickJS (`std`, `os`: filesystem, network, process). Excluding it,
and never calling `js_init_module_std`/`js_init_module_os`, is what makes the sandbox have no
I/O. The context is created with `JS_NewContext`, which adds only compute intrinsics.

## Build

Compiled with relaxed flags (`-D_GNU_SOURCE -w`, no `-Werror`) and isolated from the project's
hardened build. quickjs-ng requires `_GNU_SOURCE` for `alloca`, `localtime_r`, `tm_gmtoff` and
`CLOCK_MONOTONIC`. See the `quickjs` object rules in the top-level `Makefile`.

## Updating

1. Download the new tag tarball, record its SHA-256 here.
2. Copy the core `.c`/`.h` above (never `quickjs-libc.*`).
3. Re-run `make test` and `make asan`; re-run the JS fuzzer.
