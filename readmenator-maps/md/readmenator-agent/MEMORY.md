# Project Memory

> Cross-session context for agents. Sections 1-6 are regenerated from the source tree with zero LLM tokens: declared rules are quoted verbatim with `file:line`, measured baselines come from the scan. Section 7 is written by agents and humans and is preserved across rebuilds.

Generated from 279 files at commit `5bdb3531dba1`. Read this first, then `readmenator-wiki/index.md`, then `readmenator . ask "<question>"` for anything specific.

## 1. Purpose and domain

- What it is: From the creators of the LazyOwn Redteam Framework: a free, open-source web browser (`README.md:5`)
- Domain vocabulary (term, files): `null` (151), `max` (124), `size` (119), `not` (118), `out` (117), `include` (116), `one` (115), `freedom` (107), `char` (103), `free` (102), `const` (101), `css` (95), `its` (91), `void` (90), `static` (89)
- Subsystem `include: browser_ui`: 53 files, core `gui/browser_ui.c`: ui_input_state: Live editable state for one form text control, aliasing a block of the current...
- Subsystem `src: css`: 53 files, core `src/css.c`: len_rebase_ctx: int r = snprintf(out + *o, space, "%.4f", px); if (r < 0 || (size_t)r >= space)...
- Subsystem `src: tab`: 45 files, core `src/tab.c`: clip_pm_ok: A clip-edge percentage off the wire: per-mille, bounded like CSS_PCT_MAX (a hostile...
- Subsystem `src: text_shape`: 39 files, core `src/text_shape.c`: load_entry_file: Loads face `index` of the font file at `path` into e (FreeType + cairo + *...
- Subsystem `include: page_view`: 19 files, core `src/page_view.c`: pv_ptrmap: A small open-addressed map pointer -> int: the per-element verdict on a generated box...
- Subsystem `include: browser`: 19 files, core `src/browser.c`: clear_status: #include <stdlib.h> #include <string.h> static void free_page(browser_state *bs) {...
- Subsystem `src: local_store`: 16 files, core `src/local_store.c`
- Subsystem `include: secure_fetch`: 13 files, core `src/secure_fetch.c`: tls_capture: Snapshot of the negotiated TLS state. curl exposes the live SSL* only while a...
- Business rules that the code cannot show live in section 7: record them there.

## 2. Workflow

Detected commands:
- `python -m pytest -q` (tests/ layout)
- `make all` (Makefile)
- `make install` (Makefile)
- `make test` (Makefile)
- `make itest` (Makefile)
- `make asan` (Makefile)
- `make fuzz` (Makefile)
- `make fuzz-js` (Makefile)
- `make fuzz-imap` (Makefile)
- `make fuzz-wst` (Makefile)
- `make fuzz-geom` (Makefile)
- `make fuzz-jsdom` (Makefile)

Session protocol:
1. Start: read this file, then `readmenator . fresh` (exit 1 means run `readmenator . --rebuild`).
2. Orient: `readmenator-wiki/index.md`; for a question use `readmenator . ask "<question>"` (local = entities + sources, `--global` = community reports).
3. Before editing a file: `grep -n '<file>' readmenator-agent/GOTCHAS.md readmenator-agent/SECURITY.md`.
4. After the change: run the tests above, then `readmenator . --rebuild` so the maps, wiki, and this file stay true.
5. End: record decisions, business rules, and gotchas with `readmenator . remember "<note>" --kind decision`.

## 3. Rules and constraints

Declared:
- Pure C11 only. Headers reject C++ via `#error`. (`AGENTS.md:17`)
- Fail closed. Doubt means reject. No convenience downgrade. (`AGENTS.md:18`)
- No new deps without attack-surface reduction argument. Never liboqs/oqsprovider. OpenSSL 3.5+ native only. (`AGENTS.md:19`)
- No `io_uring` inside confined worker (`tab`/renderer). Blocked pipes only. Bypass seccomp otherwise. (`AGENTS.md:20`)
- Every new `pv_run`/`pv_box_def`/`rd_block` field crosses `write_view`/`read_view` in `src/tab.c`. Check `TAB_WIRE_*` constants. Run `make drift`. (`AGENTS.md:21`)
- Shared struct growth requires `make clean` rebuild. Makefile tracks no header deps. (`AGENTS.md:22`)
- `-fvisibility=hidden` invariant. Never remove. HarfBuzz allocator guard. (`AGENTS.md:23`)
- No magic numbers. Policy tunables live in `include/freedom_config.h` as `FC_*` with why-comment. Contract bounds live in module header. (`AGENTS.md:24`)
- No absolute paths. No emojis in code. English identifiers. (`AGENTS.md:25`)
- V-001 malloc(len+1) SIZE_MAX guard. V-002 calloc for arrays + zero-init stack views. V-003 chained fixed blocks for unbounded accumulators. V-004 snprintf truncation check. (`AGENTS.md:26`)
- `make drift` green before `make test`. Drops gate `make drops` green. New bad-value fails build. (`AGENTS.md:27`)
- Plans are hypotheses. Verify every file path and symbol against source before acting. (`AGENTS.md:28`)
- Log mechanism not incident in fix notes. State generalized error category. (`AGENTS.md:29`)

Measured baseline:
- Security findings at medium or above: 0 (see `readmenator-agent/SECURITY.md`); do not add new ones.
- Dependency cycles: 1; layer violations: 24 (see `readmenator-agent/GOTCHAS.md`).

## 4. Style norms

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- c: 174 files, 5752 symbols; docstrings on 27% of symbols; functions snake_case (99%); types PascalCase (0%); median file 244 lines, max 18996.
- h: 91 files, 1483 symbols; docstrings on 38% of symbols; functions snake_case (98%); types PascalCase (0%); median file 76 lines, max 1250.
- py: 10 files, 42 symbols; docstrings on 19% of symbols; functions snake_case (100%); median file 96 lines, max 345.
- sh: 4 files, 0 symbols; median file 39 lines, max 91.
- Tests: 80 files under tests; follow the existing naming (e.g. `itest_secure_fetch.c`).

## 5. Minimum deliverables

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Tests pass: `python -m pytest -q`.
- Docstring coverage stays at or above 29%.
- No new security findings at medium or above (current: 0).
- No new dependency cycles (current: 1).
- Files stay under 300 lines where possible (`readmenator . lint`).
- Docs refreshed: `readmenator . --rebuild`, and decisions recorded in section 7.

## 6. Risks to respect

- God nodes (changes ripple widely): `gui/browser_ui.c`, `include/css.h`, `src/tab.c`, `src/freedom.c`, `src/css.c`
- Hotspots (complex and central): `gui/browser_ui.c`, `src/tab.c`, `src/page_view.c`, `src/css.c`, `tests/test_css.c`
- Cycle: `include/js_dom.h` -> `include/js_location.h` -> `include/js_dom.h`
- Full blast radius: `readmenator-agent/GOTCHAS.md`; findings: `readmenator-agent/SECURITY.md`.

## 7. Session log (preserved across rebuilds)

Append with `readmenator . remember "<note>" --kind <kind>` (kinds: business, decision, rule, workflow, style, deliverable, gotcha, todo, note) or the MCP tool `readmenator.remember`. Record business rules, decisions and their reasons, workflow changes, and anything the next session must not rediscover.

<!-- readmenator:memory:notes:begin -->
<!-- readmenator:memory:notes:end -->
