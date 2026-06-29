# Modern Navigation Plan — Hitos D-1..D-5, D-7, D-8

> **Status:** planning document (not a spec). Encodes the decisions taken with the
> owner for the "modern navigation" bucket. Source of truth for the next set of
> hitos after the current roadmap backlog.
>
> **Scope:** features a user in 2026 expects from a "modern browser" navigation
> experience. **No new dependencies.** Every hito follows the §3 cycle:
> spec → test (red) → code (green) → refactor → `make asan` → fuzzing → docs.
>
> **Persistence decision (Hito D-6):** explicitly **out of scope**. Zero
> persistence: session lives in RAM only, dies with the process, no disk write
> of any navigation state. This aligns with Zero Knowledge as the strongest
> possible default. Anything in this plan that *would* have needed persistence
> (bookmarks, persistent history) is reduced to its RAM-only form.
>
> **Doctrinal constraints:**
> - C11 pure, no new deps, no C++.
> - Modules are pure (TDD) when logic is involved; orchestrators wire I/O.
> - Fail-closed on every hostile input.
> - Privacy by Default; the user opts in to non-defaults.
> - Agent-friendly: deterministic, structured, no hidden state, headless paths.
>
> **Verification:** modules + integration verified under `make test` and
> `make asan` (36 → ~40 suites, exit 0). Visual GUI verification stays
> pending the owner in Wayland (consistent with every other hito in the
> project that touches the GUI).

---

## Bucket order (D-2 first — lowest cost, immediate value)

```
D-2 (anchor scroll)            1 day
D-1 (find in page)             1-2 days
D-3 (smooth scroll)            1 day
D-4 (touchpad + mouse gesture) 0.5 day
D-8 (indicators)               0.5 day
D-5 (bfcache)                  1 day
D-7 (new tab + quick switcher) 2-3 days
D-6 (session restore)          SKIPPED — zero persistence
```

Dependencies: D-3 helps D-2 (animated jump to anchor). D-7a (topsites) is
independent; D-7b (quick switcher) only needs in-RAM data (open tabs + topsites)
so it does not need D-6.

---

## Hito D-2 — Scroll-to-anchor `#id`

**Problem:** navigating to `https://example.com/page#section` lands the user
at the top of the page. The fragment is already extracted by `link_nav.c:51`
(`split_fragment` → `out->fragment`) but discarded by `tab.c:930` as a no-op.

**Goal:** after the first paint of a page whose URL has a non-empty
`location.hash`, scroll to the y-offset of the element with that `id`.

### Design

- **Pure module (puro):** add `pv_find_id_y(view, id, id_len, out_y, out_found)`
  to `page_view`. Walks the indexed tree via `dom_get_by_id` (already exists),
  returns the y-offset of the first block-level ancestor that contains the
  element. Returns `found = 0` if no element with that id.
- **Worker:** `tab.c` `child_handle_load` already returns the `tab_page`. Add
  one optional field `scroll_to_id` (zero-copy string, length-prefixed). Set
  it from `loc.hash` when non-empty.
- **GUI:** after `render_current`, if `w->doc.scroll_to_id` is non-empty and
  the doc is fresh, look up the y via `pv_find_id_y` and set
  `w->scroll = clamp(y - top_pad, 0, max_scroll)`. Reset on subsequent
  renders unless the URL hash changed.

### Files

- `src/page_view.c` + `include/page_view.h` — `pv_find_id_y`
- `src/tab.c` — add `scroll_to_id` to `tab_page` (length-prefixed over IPC,
  bounded by `LINK_FRAG_MAX` already in use)
- `gui/browser_ui.c` — apply after `render_current`
- `spec/page_view.md` — annex with Given-When-Then for `pv_find_id_y`
- `spec/link_nav.md` — note: the fragment is no longer discarded; it drives
  post-render scroll

### Tests (CMocka)

- `tests/test_page_view.c` (+4): hit, miss, id with spaces, overflow cap
- `tests/test_tab.c` (+1): `scroll_to_id` round-trip on IPC

### Fuzz

Not applicable (pure tree walk over an indexed tree; covered by `fuzz-pv`).

### Out of scope (handed to Hito 20e part 2)

Live anchor scroll on hash change triggered by JS (e.g. `location.hash = "#x"`
in a script) — that path needs the live worker round-trip.

---

## Hito D-1 — Find in page (`Ctrl+F` / `/`)

**Problem:** no way to search within the current page. A baseline browser
feature; also the most-asked user request.

**Goal:** a Vim/Chrome-style find bar at the bottom of the content area,
highlighting every match, with `n`/`N` navigation, regex opt-in, fail-closed
on pathological queries.

### Design

- **New pure module `find` (`fn_`):**
  - `fn_match(query, runs, n_runs, cap, opts, out_hits, max_hits)`
    - Plain text (default) or POSIX regex (`opts.regex`).
    - Case-insensitive by default (`opts.case_sensitive`).
    - Returns hit count (capped by `max_hits`, overflow flag).
    - Each hit: `{run_idx, byte_start, byte_end, line_y}`.
  - `fn_regex_compile(pattern, out_re) → status` — POSIX `regex.h`
    (libc, not a new runtime dep), with **anti-ReDoS cap**: pattern
    length cap (`FN_REGEX_MAX`, e.g. 256B) and a `regcomp` `cflags`
    restriction. Compilation errors fail closed (returns
    `FN_ERR_REGEX_INVALID`).
  - Backtracking is bounded by libc's own NFA limits; the *length* cap is
    what keeps us safe from catastrophic backtracking on hostile input.
- **Runs source:** the `pv_view` display list is already computed per page
  and lives in memory. We walk it.
- **GUI:** a thin bar overlaid on the content area (above the scroll gutter),
  with a `tf_field` (existing widget) and counters (`3/12`).
- **Paint:** `paint_content_row` (existing) gains a sibling path
  `paint_find_overlay` that draws a translucent background over the matched
  byte range of the active run(s). Active match uses a stronger tint.
- **Atajos:**
  - `Ctrl+F` opens the bar
  - `/` opens it (vim style) when focus is not in URL bar / Freebug editor
  - `Enter` / `n` → next match
  - `Shift+Enter` / `N` → previous match
  - `Esc` closes the bar and clears highlights
- **Focus routing:** the existing `kbd_focus` / `ptr_focus` mechanism (used
  by Freebug, Hito 24) is reused: while the find bar has focus, the same
  key handlers (`key_is_repeatable`, `handle_key_press`) consume
  `n`/`N`/`Enter`/`Esc` locally and never let them bubble to the page.

### Files (new)

- `src/find.c` + `include/find.h` — pure `fn_` module
- `spec/find.md` — full spec with Given-When-Then + error table

### Files (extended)

- `gui/browser_ui.c` — find bar, overlay paint, atajos, focus routing
- `Makefile` — add `find.c` to the `freedom` target

### Tests

- `tests/test_find.c` (new, 10): exact match, case-insensitive, whitespace,
  empty query, regex invalid, regex backtracking cap (feed a known ReDoS
  pattern with `FN_REGEX_MAX` exceeded → fail-closed), match across runs,
  cap saturation, null safety, query > `FN_QUERY_MAX`
- `tests/test_browser.c` (+2): find bar opens/closes; `n` advances

### Fuzz

- `make fuzz-fn` — `LLVMFuzzerTestOneInput` exercises `fn_match` with
  random bytes split into query + runs; verifies cap invariants and that
  no input can produce more than `max_hits` hits or write OOB.
- Seed corpus: a plain text page with known matches + an adversarial query.

### Out of scope

- Unicode normalization (case folding is byte-level, matching the rest of
  the project). Search is per-byte; sufficient for v1.
- Whole-word / case-sensitive toggles (can come in a follow-up; trivial
  once the bar is in place).
- Find across multiple tabs (search the active tab only).
- Live find (incremental, as-you-type): v1 is "press Enter to commit the
  query" matching the Vim mental model and avoiding O(n²) on huge pages.

---

## Hito D-3 — Smooth scroll animation

**Problem:** `w->scroll` jumps instantly. Wheel/keyboard/drag snaps. Modern
browsers animate the scroll. D-2's anchor jump will look much better animated.

**Goal:** all programmatic and wheel-driven scroll changes interpolate to the
target over ~150ms with cubic ease-out, except scrollbar drag (which stays
1:1 to preserve direct manipulation feel).

### Design

- **New pure module `scroll_anim` (`sa_`):**
  - `sa_init(&a, target_y, duration_ms)` — fixed duration default 150ms
  - `sa_tick(&a, dt_ms) → double` — returns new offset; advances internal t
  - `sa_done(&a) → bool` — true when t >= duration
  - `sa_cancel(&a)` — snap to current; mark done
  - Cubic ease-out: `1 - (1 - t)^3` where t is normalized 0..1
- **No new fd:** the existing `repeat_timer_fd` (gui/browser_ui.c:5132,
  ~25Hz by default) is reused. The tick handler in the event loop adds:
  ```
  if (!sa_done(&w->sa)) {
      w->scroll = sa_tick(&w->sa, dt_ms);
      redraw(w);
  }
  ```
- **Asignaciones a `w->scroll` en handlers** become:
  - wheel, `j`/`k`/`space`/`b`/`gg`/`G`, `PageUp`/`PageDown`/`Home`/`End`,
    anchor jump from D-2 → set `w->scroll_target = X; sa_init(&w->sa, X, 150)`
  - scrollbar drag (gui/browser_ui.c:1611) stays direct (`w->scroll = frac *
    max_scroll`) — direct manipulation feel
  - freebug / find bar / context menus that scroll the content area: also
    animated
- **In-place change:** `browser_window` gains `double scroll_target; scroll_anim
  sa;` next to the existing `double scroll;`. All ~200 existing call sites
  that read `w->scroll` keep working; only the *writes* in the handlers listed
  above need to change.

### Files (new)

- `src/scroll_anim.c` + `include/scroll_anim.h` — pure `sa_` module
- `spec/scroll_anim.md` — full spec

### Files (extended)

- `gui/browser_ui.c` — add fields, redirect writes, extend timerfd tick
- `Makefile` — add `scroll_anim.c`

### Tests

- `tests/test_scroll_anim.c` (new, 5): easing monotonicity, duration
  respected, done-state, delta=0 no-op, fuzz of the curve
- `tests/test_browser.c` (+1): wheel initiates animation; `sa_done` after
  expected tick count

### Fuzz

- `make fuzz-sa` — `LLVMFuzzerTestOneInput` splits bytes into a sequence of
  dt_ms values; verifies the curve is bounded in `[start, target]` and never
  NaNs.

### Out of scope

- Inertial / momentum scroll (Apple-style). Cubic ease-out covers the common
  case; momentum would need a velocity state and is a bigger behavioral
  change.
- Scrolling-on-drag animation (drag stays 1:1 by design).
- `prefers-reduced-motion` handling: deferred to a follow-up; for now the
  animation is short (150ms) and respects Privacy by Default in spirit.

---

## Hito D-4 — Touchpad + mouse back/forward gesture

**Problem:** on Wayland, `ptr_axis` (gui/browser_ui.c:4453) only handles
`WL_POINTER_AXIS_VERTICAL_SCROLL`. Touchpad horizontal swipes and mouse
side buttons are not wired to `browser_back` / `browser_forward`.

**Goal:** touchpad swipe (continuous source) → back/forward. Mouse
`BTN_SIDE` (8) / `BTN_EXTRA` (9) → back/forward. Wheel horizontal stays
ignored by default (Privacy by Default: it's accidental, not intentional).

### Design

- **Pure decision function** in `browser.c` (testable in isolation):
  ```
  int axis_is_nav_gesture(uint32_t axis, uint32_t axis_source,
                          wl_fixed_t value);
  ```
  Returns 1 iff `axis == WL_POINTER_AXIS_HORIZONTAL_SCROLL` AND
  `axis_source` is `FINGER` or `CONTINUOUS` AND `abs(value) > threshold`
  (threshold ~50, tuned experimentally; ~1cm of finger travel).
- **`ptr_axis` extended:**
  - Calls `axis_is_nav_gesture`. If 1, accumulates `value` and on crossing
    `±200` (one swipe = one action) calls `browser_back` or
    `browser_forward` and resets the accumulator. This stops a long swipe
    from triggering many navigations.
  - `axis_source == WHEEL` and axis is horizontal: ignore (logged at
    debug level for the owner to tune the menu toggle if they want it).
- **`ptr_button` extended:**
  - `button == 8` (`BTN_SIDE`) → `browser_back`
  - `button == 9` (`BTN_EXTRA`) → `browser_forward`
  - `BTN_BACK` (138) / `BTN_FORWARD` (139) — newer aliases, treat as 8/9.
- **Future toggle (not in this hito):** "Horizontal wheel = back/forward" in
  the options menu, default off. Documented but unimplemented to keep the
  change small.

### Files (extended)

- `gui/browser_ui.c` — `ptr_axis` horizontal path; `ptr_button` side buttons
- `src/browser.c` + `include/browser.h` — `axis_is_nav_gesture` (pure)
- `spec/browser.md` §3 — annex: navigation gestures

### Tests

- `tests/test_browser.c` (+4): pure decision table for `axis_is_nav_gesture`
  (finger + threshold met, finger + threshold not met, wheel + threshold met,
  vertical axis)

### Out of scope

- Visual swipe indicator (a translucent arrow appearing during a horizontal
  swipe, like ChromeOS). Easy to add later; not in this hito.
- Injected E2E test: this environment has no `wtype`/`ydotool`, so live
  touchpad/mouse events cannot be simulated. Visual verification stays
  pending the owner.

---

## Hito D-8 — Indicators and feedback (subset of bucket E)

**Problem:** the URL bar does not show the *security* state of the current
connection. The content area has a spinner, but the *tab* and the *URL bar*
do not show load progress. The owner has to read the toast to know if a
connection was PQ-hybrid or classical-KE.

**Goal:** a small chip at the left of the URL bar that encodes
`https + TLS 1.3 + PQ hybrid KE` (green), `classical KE` (amber), or
`allowlisted insecure` (red). A thin progress bar under the URL bar that
reflects `CURLOPT_NOPROGRESS` callbacks. A dot in the tab strip that pulses
while the tab is loading.

### Design

- **`sf_conn_class` enum** computed in `secure_fetch` at the end of
  `sf_get_follow` (the hop that succeeded):
  - `SF_CONN_PQ_HYBRID` — TLS 1.3 AND `tls_group` contains `MLKEM` /
    `X25519MLKEM`
  - `SF_CONN_CLASSICAL_KE` — TLS 1.3 AND no PQ group (the navigability
    fallback)
  - `SF_CONN_ALLOWLIST_INSECURE` — applied when the per-host allowlist
    override accepted a classical-KE / weak cert (Hito 11)
  - `SF_CONN_ONION` — `.onion` reached (Tor)
  - `SF_CONN_I2P` — `.i2p` reached (I2P HTTP proxy)
  - `SF_CONN_PLAIN_HTTP` — only reachable on overlay (`nr_realm_allows_http`
    for `.i2p`); distinct from clearnet HTTP rejection
  - `SF_CONN_FILE` — `file://` origin
- **`tab_page`** gains a `conn_class` field (1 byte). The GUI paints the
  chip from this field. No string formatting needed (avoids host-leak via
  error messages).
- **Progress bar:** `sf_get_follow` already runs with `CURLOPT_NOPROGRESS=0`
  + a `progress_cb` (Hito 9). The progress percentage is forwarded over IPC
  in a new `tab_progress` message type (1 byte: `pct` 0..100; 255 = done
  with error). The GUI shows the bar when `pct > 0 && pct < 100`; hides it
  otherwise.
- **Tab dot:** `w->loading` already exists. Paint a 4×4 filled circle in
  the tab strip next to the title when `w->loading`; pulse it via the same
  timerfd used for the spinner (D-3 reuses this).

### Files (new)

- `spec/secure_fetch.md` §X — `sf_conn_class` classification
- `spec/secure_fetch.md` §X — `tab_progress` message

### Files (extended)

- `include/secure_fetch.h` — `sf_conn_class` enum
- `src/secure_fetch.c` — classify at end of `sf_get_follow`
- `src/tab.c` — `tab_page.conn_class`; `tab_progress` IPC message
- `gui/browser_ui.c` — chip paint; progress bar paint; tab dot paint

### Tests

- `tests/test_secure_fetch.c` (+4): classifier pure function over a small
  enum/string input (tls_version, tls_group substring, allowlist flag, realm)

### Out of scope

- Detailed tooltip on the chip (hover, show "X25519MLKEM768 / TLS 1.3").
  Trivial follow-up; not in this hito.
- Per-tab badge for the realm (Tor/I2P). The chip already encodes the
  realm; a separate badge is redundant for v1.

---

## Hito D-5 — Back/forward cache (bfcache, RAM only)

**Problem:** `browser_back` and `browser_forward` (browser.c:232-249) only
walk the history position; they refetch and re-render the destination URL.
On a real site that is slow and breaks the SPA feel of "I just want to
peek at the previous page."

**Goal:** if the destination URL is in the bfcache, restore its snapshot
instantly (no fetch, no worker, no repaint of the page beyond re-paint).
If miss, current behavior. All in RAM; dies with the process.

### Design

- **New pure module `bfcache` (`bf_`):**
  - `bf_init(&bf, cap)` — bounded LRU (default `BF_MAX_ENTRIES = 8`)
  - `bf_put(&bf, key, page_copy)` — copies the `tab_page` snapshot
  - `bf_get(&bf, key, out) → bool` — hit/miss; on hit, returns the snapshot
    and promotes the entry to MRU
  - `bf_drop(&bf, key)` — explicit drop (tab close)
  - `bf_clear(&bf)` — on quit / config change
  - Key: `url_canonical(url)` (pure, reuses the canonicalize in `url.c`
    already used by `hostblock`). Fragment is **not** part of the key
    (changing hash on the same doc hits the same cache entry; the GUI
    applies the anchor scroll from D-2 on top).
- **Snapshot contents:** copy of `tab_page` — `text`, `runs`, `links`,
  `title`, `scroll`, `console`, `conn_class`, `scroll_to_id`. **Not**
  pixels, **not** the DOM, **not** the worker state. The worker has
  already exited for that page; restoring is purely a re-paint.
- **Memory bound:** `BF_MAX_ENTRIES * sizeof(tab_page)`. The `tab_page`
  struct already has bounded arrays (`text` up to `PAGE_TEXT_MAX`, runs up
  to `PV_MAX_RUNS`, etc.). Worst case fits in a few MB; measured in tests.
- **Plumbing in `browser.c`:** `browser_back`/`browser_forward` consult
  `bf_get` *before* deciding to refetch. On hit, they apply the snapshot
  via a new pure function `browser_apply_snapshot(bs, snap)`.
- **Plumbing in `tab.c`:** after every successful load, the parent calls
  `bf_put` for the now-current URL *before* the next navigation overwrites
  it. On tab close, `bf_drop` for all entries belonging to that tab's URLs
  (we track ownership by `tab_id`).
- **Plumbing in `gui/browser_ui.c`:** on tab close (`uitab_close`), drop
  the bfcache entries for that tab.

### Files (new)

- `src/bfcache.c` + `include/bfcache.h` — pure `bf_` module
- `spec/bfcache.md` — full spec

### Files (extended)

- `src/browser.c` + `include/browser.h` — `browser_apply_snapshot`
- `src/tab.c` — `bf_put` after every load, `bf_drop` on tab close
- `gui/browser_ui.c` — `bf_drop` on tab close
- `Makefile` — add `bfcache.c`

### Tests

- `tests/test_bfcache.c` (new, 6): LRU eviction, hit promotes to MRU, miss
  is miss, key with fragment, null safety, cap saturation, copy semantics
  (mutating the snapshot does not affect the cache)
- `tests/test_browser.c` (+2): back hits the cache (no refetch), forward
  hits the cache

### Fuzz

- `make fuzz-bf` — `LLVMFuzzerTestOneInput` for `bfcache`'s key handling
  and copy path.

### Out of scope

- Persistence to disk (forbidden by the D-6a decision).
- Scroll-restoration with smooth animation (D-3 covers programmatic scroll
  but `browser_apply_snapshot` sets `w->scroll` directly; a follow-up can
  add a flag `snap.scroll_animated = 1` that defers the scroll to the
  scroll_anim).
- bfcache for `file://` pages: works for free (they are in RAM too), but
  not specifically tested. Trivial follow-up.

---

## Hito D-7 — New tab page + quick switcher

**Problem:** `Ctrl+T` opens an empty `about:blank` page. The user has no
quick way to find an open tab, a top site, or a recent destination.
Both features are expected of any modern browser and were explicitly
approved by the owner.

**Goal:** a useful new-tab page (top sites + recent shortcuts, all RAM
local), and a Spotlight/Arc-style quick switcher overlay (`Ctrl+Shift+A`)
for fuzzy search across open tabs + top sites.

### Design (part 1: topsites)

- **New pure module `topsites` (`ts_`):**
  - Open-addressed hash table keyed by host (lowercased, eTLD+1 via the
    existing `rp_site_of`).
  - `ts_record(&ts, host, delta)` — `+= delta` (default 1 on visit).
  - `ts_tick(&ts, decay_per_day)` — called once per day (clock passed in;
    no I/O).
  - `ts_top(&ts, n, out[])` — top-N by score, ties broken by recency.
  - `TS_MAX_HOSTS = 64`, `TS_TOP = 8`. Both configurable, both bounded.
- **Hook:** `tab.c` `child_handle_load` (parent side, post-render) calls
  `ts_record(&w->ts, host, 1)`. Decay is best-effort on a coarse timer
  (once per app-day, computed from a `time()` read at startup; do not
  call `time()` in the pure path).

### Design (part 2: new tab page)

- `Ctrl+T` opens a tab with URL `about:newtab`.
- The worker / orchestrator short-circuits `about:newtab`: no fetch, no
  network, no worker. The renderer (`page_view` or a small specialized
  view) produces a `tab_page` directly from `ts_top` + a list of recent
  destinations (last N visited URLs, kept in RAM in a small ring buffer
  in `browser_state`).
- **New pure module `newtab_view` (`nt_`):** takes `ts_top(N)` + recent
  ring buffer + theme, returns a `tab_page` with a simple grid layout.
  Uses the existing box-tree / flex layout (Hito 7). Each card has
  favicon-ish placeholder (no network), host, title.
- **No favicon fetch.** Privacy by Default: a favicon is a third-party
  request; out of scope. Cards are typographic only.

### Design (part 3: quick switcher)

- **New pure module `fuzzy` (`fz_`):**
  - `fz_score(query, candidate) → {score, matched_spans[]}`: subsequence
    match with score = `100 * continuity + 10 * (1 / first_match_pos) +
    5 * (1 / run_length)`. Ties broken by candidate recency.
  - `fz_top(query, candidates[], n, out[], k)` — top-K by score.
  - Match is case-insensitive, byte-level (consistent with the rest of
    the project; no Unicode normalization in v1).
  - Empty query → returns candidates sorted by recency.
  - No regex (anti-ReDoS by construction).
- **GUI overlay (`Ctrl+Shift+A`):** a centered rectangle (modal) with a
  `tf_field` on top and a list of up to 8 results below. Same input
  model as the find bar (D-1). `Up`/`Down` move the selection; `Enter`
  activates; `Esc` closes.
- **Candidates:**
  1. Open tabs (highest priority — that's the primary use case).
  2. Top sites (from `ts_top(8)`).
  3. Recent destinations (the ring buffer in `browser_state`).
  No bookmarks (D-6a excludes persistence; bookmarks require disk).
- **Activation:**
  - Tab match: `tab_activate(idx)` (existing, Hito 15).
  - URL match: `browser_go(url)`.

### Files (new)

- `src/topsites.c` + `include/topsites.h` — pure `ts_`
- `src/fuzzy.c` + `include/fuzzy.h` — pure `fz_`
- `src/newtab_view.c` + `include/newtab_view.h` — pure `nt_`
- `spec/topsites.md`, `spec/fuzzy.md`, `spec/newtab_view.md` — full specs

### Files (extended)

- `src/browser.c` + `include/browser.h` — `browser_state` ring buffer
- `src/tab.c` — `ts_record` on each successful load
- `gui/browser_ui.c` — `about:newtab` shortcut; quick switcher overlay;
  Ctrl+Shift+A atajo
- `Makefile` — add three new modules

### Tests

- `tests/test_topsites.c` (new, 6): record/top, decay, cap eviction,
  null safety, eTLD+1 normalization, fuzz
- `tests/test_fuzzy.c` (new, 5): subsequence, ordering, scoring,
  empty query returns by recency, null safety, fuzz
- `tests/test_newtab_view.c` (new, 3): renders with no topsites, with
  8 topsites, with full cap (does not OOM)
- `tests/test_browser.c` (+2): quick switcher selects the right tab;
  recency is preserved across activations

### Fuzz

- `make fuzz-ts` — topsites hash table and decay
- `make fuzz-fz` — fuzzy scorer with random query/candidate pairs

### Out of scope

- Bookmarks. D-6a forbids persistence; bookmarks need disk.
- Favicons. Third-party fetch forbidden by Privacy by Default.
- Drag-and-drop to reorder cards in the new tab page.
- Customization of the new tab page background.
- The quick switcher does not search the page content (only titles, URLs,
  and hosts). Page-content search is the find bar (D-1).

---

## Summary of deliverables

| Hito | New pure modules | IPC / tab.c changes | GUI changes | New tests | Fuzz targets |
|---|---|---|---|---|---|
| D-2 anchor | `pv_find_id_y` (in page_view) | `scroll_to_id` field | apply after render | +5 | — |
| D-1 find | `fn_` | — | overlay bar + atajos | +12 | `fuzz-fn` |
| D-3 smooth | `sa_` | — | reuses timerfd | +6 | `fuzz-sa` |
| D-4 gesture | (pure decision fn in browser) | — | `ptr_axis`/`ptr_button` | +4 | — |
| D-8 indicators | `sf_conn_class` enum | `tab_page.conn_class`, `tab_progress` msg | chip + bar + dot | +4 | — |
| D-5 bfcache | `bf_` | `bf_put`/`bf_drop` on load/close | drop on tab close | +8 | `fuzz-bf` |
| D-7 newtab + qs | `ts_`, `fz_`, `nt_` | `about:newtab` switch; `ts_record` on load | new tab + overlay | +16 | `fuzz-ts`, `fuzz-fz` |
| D-6 session restore | **SKIPPED** (D-6a, zero persistence) | | | | |

**Totals:**
- 6 new pure modules (`fn_`, `sa_`, `bf_`, `ts_`, `fz_`, `nt_`) + 1 decision
  function in `browser`.
- 7 existing modules extended (`page_view`, `tab`, `browser`, `secure_fetch`,
  `browser_ui`, plus minor plumbing).
- ~55 new CMocka tests across 6 new test files + extensions to 3 existing.
- 4 new fuzz targets (`fuzz-fn`, `fuzz-sa`, `fuzz-bf`, `fuzz-ts`, `fuzz-fz` —
  5 in total).
- 0 new runtime dependencies. POSIX `regex.h` is libc (already linked).
- Test suite grows from 36 → ~40. `make asan` exit 0 throughout.
- `docs/index.html` updated with the new atajos (`Ctrl+F`, `Ctrl+Shift+A`,
  `/`, `n`, `N`, touchpad swipe, mouse side buttons).
- `README.md` updated with the new feature list.

---

## What stays in the broader roadmap (not in this plan)

- Hito 9b — async images + concurrent multi-tab loads.
- Hito 10 — persistence to disk (explicitly excluded by D-6a; revisit if
  the owner changes the policy).
- Hito 19b — more image formats (SVG/WebP/GIF/AVIF) and lazy loading.
- Hito 20e part 2 — interactive JS events, async timers, external scripts,
  live hash-change scroll.
- Hito 22b — download/zoom polish.
- Hito 23b (remaining) — more CSS (border, box-sizing, position, sibling
  combinators, pseudo-classes).

---

## Verification strategy (per the project §3 cycle)

Every hito in this plan follows:

1. **Spec first** (the relevant `spec/<module>.md`).
2. **Test (red)** in `tests/test_<module>.c` (CMocka).
3. **Code (green)** minimum to pass the tests.
4. **Refactor** (boy-scout mode: extract duplication, harden pointers,
   tighten bounds).
5. **Validate** with `make asan` (AddressSanitizer + UBSan) clean.
6. **Fuzz** with `make fuzz-<module>` for any module that touches
   untrusted input (DOM text, URLs, CSS, JS, headers).
7. **Visual review** for anything that paints (`/visual-review` skill:
   `--download-pdf` → `mutool draw` → Read PNG), with the explicit
   acknowledgment that the interactive Wayland window stays pending
   the owner (consistent with every other hito in the project).
8. **Document** (`docs/index.html` atajos table + `README.md` feature
   list) only after green tests + clean ASan + green fuzz.

This plan is a planning document, not a spec. Each hitos's detailed spec
gets written when the hito starts, in the same commit as the red test.
