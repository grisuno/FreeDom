# AGENTS.md — modifying Freedom internals

This file governs AI sessions that edit this repo. `CORE.md` governs sessions
that only consume Freedom as dependency. Read only the one matching current role.

## Order of work

1. Spec first: `spec/<module>.md` Given-When-Then, error table, security guarantees, out of scope.
2. Red test: `tests/test_<module>.c` CMocka. Verify red by reverting fix. Binary stale with `-Werror` is invalid red.
3. Green minimal: `src/<module>.c` pure C11, `sf_` style prefix, no global mutable state, single owner single idempotent free.
4. Boyscout refactor: unify dups, normalize spaghetti to established pattern, delete dead code, no behavior change without spec.
5. Validation: `make test`, `make asan`, valgrind, cppcheck, headless PNG visual review, `make fuzz-*` zero crash, mutation kill.
6. Docs after green: spec + CLAUDE.md contract line + README/docs if user-facing.

## Hard rules

- Pure C11 only. Headers reject C++ via `#error`.
- Fail closed. Doubt means reject. No convenience downgrade.
- No new deps without attack-surface reduction argument. Never liboqs/oqsprovider. OpenSSL 3.5+ native only.
- No `io_uring` inside confined worker (`tab`/renderer). Blocked pipes only. Bypass seccomp otherwise.
- Every new `pv_run`/`pv_box_def`/`rd_block` field crosses `write_view`/`read_view` in `src/tab.c`. Check `TAB_WIRE_*` constants. Run `make drift`.
- Shared struct growth requires `make clean` rebuild. Makefile tracks no header deps.
- `-fvisibility=hidden` invariant. Never remove. HarfBuzz allocator guard.
- No magic numbers. Policy tunables live in `include/freedom_config.h` as `FC_*` with why-comment. Contract bounds live in module header.
- No absolute paths. No emojis in code. English identifiers.
- V-001 malloc(len+1) SIZE_MAX guard. V-002 calloc for arrays + zero-init stack views. V-003 chained fixed blocks for unbounded accumulators. V-004 snprintf truncation check.
- `make drift` green before `make test`. Drops gate `make drops` green. New bad-value fails build.
- Plans are hypotheses. Verify every file path and symbol against source before acting.
- Log mechanism not incident in fix notes. State generalized error category.
