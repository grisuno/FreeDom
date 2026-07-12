# FreeDom

<img width="3716" height="1038" alt="image" src="https://github.com/user-attachments/assets/f05ca2e0-0202-4708-a384-c49025967c18" />
<img width="3840" height="1080" alt="image" src="https://github.com/user-attachments/assets/b989152a-9d14-441c-af9b-e36fa82e67b9" />



From the creators of LazyOwn Redteam Framework comes a free and open-source minimal web browser written in C, focused on Zero Trust and Zero Knowledge principles.

## Quick Start

### Join the rebellion

**Easiest way to try FreeDom right now:**

```bash
git clone https://github.com/grisuno/FreeDom.git
cd FreeDom

# Docker (strongly recommended for testing)
sudo docker build -t freedom-browser . 

sudo docker run -it \
  --name freedom-test \
  -p 8080:8080 \
  --cap-drop=ALL \
  --security-opt no-new-privileges:true \
  --memory="2g" \
  freedom-browser
```

Then open your browser and go to: http://localhost:8080/vnc.html

<img width="1127" height="921" alt="image" src="https://github.com/user-attachments/assets/b00510ab-3870-4212-964d-56634ecc9c88" />

## Philosophy

<img width="800" height="450" alt="browser" src="https://github.com/user-attachments/assets/82918e97-852a-4bf0-81ce-ae39484008c4" />

FreeDom (Free + DOM) is a lightweight, security-first web browser built from the ground up in modern C. It prioritizes user privacy, strong isolation, and minimal attack surface over feature bloat.

The name reflects its core goals:
- **Free**: Libre (freedom) and open source
- **Dom**: Reference to the DOM (Document Object Model) and domain-level control

## Features
- Written in portable C11
- Strong process-based sandboxing for each tab: the worker is **forked _and re-exec'd_** so it
  inherits none of the browser's memory (a compromised tab cannot read other tabs' content; fresh
  ASLR), then confined with seccomp-bpf with **W^X** (no executable memory — `PROT_EXEC`
  `mmap`/`mprotect` are killed), Landlock, per-tab namespaces, and an undumpable worker so secrets
  cannot leak via core dump or ptrace. The syscall allowlist is **deny-by-default**, so
  **`io_uring` is blocked** in the worker — it is a seccomp-bypass primitive (its operations skip the
  filtered syscall entry), so it never gets in, not even "for async I/O"; async I/O lives only on the
  trusted side
- JavaScript sandbox using QuickJS-ng
- Hardened build with stack protection, PIE, RELRO, and FORTIFY_SOURCE
- Wayland + Cairo GUI backend with Client-Side Decorations (CSD)
- HarfBuzz text shaping (ligatures, GPOS kerning, complex scripts) on the trusted side, with local fonts only — never in the sandboxed worker, never a web font fetch
- Lexbor HTML parser and renderer
- Strict request policy using Public Suffix List + blacklist/whitelist for TLS 1.2 compatibility
- Post-quantum hybrid cryptography support (X25519MLKEM768)
- Headless mode for automation and testing
- Anti-fingerprinting techniques
- Comprehensive test suite, fuzzing, and integration tests

### New Features & Improvements (Latest)
- **Trusted-host full experience (Hito 28)**: a host you trusted **twice** (in `allow.conf` *and*
  with JS enabled for it via `js.conf`) automatically gets the full modern experience — author CSS
  **and** images on, plus the full JS it already had (execution, gated `XMLHttpRequest`/`fetch`,
  external scripts) — no per-session toggles needed. Rationale: where gated XHR can already fetch
  arbitrary bytes, keeping images/CSS off adds no privacy, only friction. Reader mode still wins,
  and a global `js on` mode alone is **not** trust (the explicit `allow.conf` entry is required).
- **Parallel subresource prefetch (Hito 29)**: a browser-style *preload scanner* on the trusted
  side. The raw HTML is scanned (pure, fuzzed) for `<link rel=stylesheet>` and `<script src>`;
  those — and the page's policy-approved images — download **in parallel** (up to 4 threads)
  through the *same* policy-gated fetcher as before, while the sandboxed worker parses. The worker
  and its serial pipe protocol are untouched: total wait tends to the **max** of the latencies
  instead of the sum (E2E-verified: 4 stylesheets behind an artificial 400 ms server arrive within
  ~4 ms of each other, with zero duplicate requests).
- **Advanced Layout Engine**:
  - Full box model per HTML tag (margins, padding, display, border)
  - Flexbox layout support (`gap`, `justify-content`, `flex-wrap` multi-line, `align-items`/`align-self` cross-axis), fed from inline `style=` *and* `<style>` rules
  - CSS Grid with sized tracks (`grid-template-columns` resolves `fr` weights and fixed `px` tracks — `2fr 1fr`, `150px 1fr` — `repeat()`/`minmax()`-aware; `grid-column: span N` places across columns with CSS auto-placement wrap; `row-gap` distinct from column gap; row spans and `grid-template-rows` sizing still pending)
  - Recursive box-tree layout with margin collapsing
- **GUI & Usability**:
  - Visible vertical scrollbar with drag and click support
  - Vim-style keyboard shortcuts (`j`/`k`, `space`/`b`, `gg`/`G`, Home/End, arrows, etc.)
  - Window controls: maximize, minimize, edge resize, titlebar drag
  - Sepia reading mode + Light/Dark/Night themes with "Force theme colors" toggle
  - Hover link preview (shows destination URL)
  - Loading indicator (busy clock)
  - Improved margins/padding and typography for better readability
  - **Simplified/Distraction-free HTML rendering** (minimalist view focused on content)
  - **Tab management** with Vim-style shortcuts
- **Privacy & Networking**:
  - **Anti-fingerprinting network identity**: a normalized, shared `User-Agent` and
    `Accept-Language` (a common Firefox-on-Linux identity) sent on every request — Freedom never
    advertises "Freedom" on the wire, so it blends into the crowd and stops tripping bot detection
    (this is what lets sites like Google load). Overridable per session in the menu.
  - **Omnibox address bar**: type an address to navigate (the `https://` scheme is added; `http://`
    is upgraded), or type anything else to run a **DuckDuckGo HTML** (no-JS) search. A dangerous
    scheme such as `javascript:` is searched, never executed (fail-closed).
  - **Per-domain JavaScript policy + live JS**: Secure by Default, page JS is off unless you opt a
    host in. A global tri-state mode (off / allowlist / on) plus a `js.conf` allowlist (same
    `/etc/hosts` format and search path as the host filter, subdomains covered). When enabled, the
    page's inline scripts **run in the sandboxed worker** against a memory-safe writable DOM
    (`document.title`, `getElementById().textContent`); with JS off, `<noscript>` fallbacks show.
  - **Tor support** (`.onion` routing via SOCKS5h proxy, remote DNS, no leaks)
  - **I2P support** (`.i2p` routing via HTTP proxy)
  - Clearnet Torification option (`--torify`)
  - Realm-based routing with **fail-closed** policy
  - Host filtering (allow/block lists)
  - TLS 1.2 allowlist/blacklist support
- **Build & Distribution**:
  - Debian `.deb` packaging (`build_deb.sh`)
  - Improved `./configure`, `install.sh` and Makefile
- **Automation**:
  - Full GitHub Actions CI/CD pipeline
  - MCP (Model Context Protocol) server for AI agent integration

## Current Status (Updated - June 21, 2026)
- ✅ Advanced HTML rendering with box model, flex/grid and margin collapsing
- ✅ Clickable links + image support (PNG + JPEG + static GIF — the GIF decoder is our own bounded pure-C LZW, no giflib — all decoded inside the sandboxed worker)
- ✅ CSS `linear-gradient()` backgrounds (pure grammar, no URL form — can never fetch) and rounded corners (`border-radius` on backgrounds, borders, shadows and outlines)
- ✅ `box-sizing: border-box` honored (declared width includes padding + border)
- ✅ Real async JS timers: `setTimeout`/`setInterval` with actual delays on a **virtual clock the trusted parent drives** (the sandboxed worker cannot wake itself); chained timers render progressively in the GUI and in headless exports
- ✅ `innerHTML` getter (bounded serialization) alongside the existing setter
- ✅ Anti-fingerprinting network identity (normalized User-Agent + Accept-Language)
- ✅ Omnibox address bar (navigate or DuckDuckGo HTML search)
- ✅ Native forms (GET/POST, no JS)
- ✅ Save page as vector PDF (`Ctrl+P`) or as a single PNG image (`Ctrl+Shift+P`)
- ✅ Safe downloads (`Ctrl+S` / auto for non-renderable resources, fail-closed filenames, 0600)
- ✅ Page zoom (`Ctrl++`/`Ctrl+-`/`Ctrl+0`) and reload (`Ctrl+R`/`F5`)
- ✅ Encrypted persistent profile (Hito 10): preferences (theme/zoom/toggles/JS policy/Tor-I2P), **bookmarks** (`Ctrl+B`, browse at `about:bookmarks`) and **history** (feeds omnibox autocomplete; "Remember history" opt-out forgets it) — sealed with AES-256-GCM under a per-device Argon2id key, atomic 0600, nothing readable on disk
- ✅ Author CSS (`<style>` + inline `style=`, simple subset; descendant/child/sibling combinators, attribute selectors `[attr=v]`/`^=`/`$=`/`*=`/`~=`/`|=`, pseudo-classes `:link`/`:nth-child()`/…, `!important`; never phones home) — menu "Author styles (CSS)"
- ✅ External stylesheets (`<link rel=stylesheet>`): fetched by the **trusted parent** under the full network policy (tracker blocklist, realm routing, TLS-PQ) when Author styles is on — the sandboxed worker never touches a socket, and the parent serves style-only loads as `GET` exclusively
- ✅ Author box model (`margin`/`padding`/`width`/`max-width`): centered reading columns (`max-width` + `margin: 0 auto`)
- ✅ Author text presentation: `font-family` (generic families), `text-transform`, `letter-spacing`, `word-spacing`, `text-shadow`, `opacity`, `vertical-align` (sub/super), `text-indent`, `white-space` (nowrap), `list-style-type` (decimal/alpha/roman/disc/circle/square)
- ✅ `visibility` (hidden reserves layout space), `cursor: pointer` (hand cursor on any element), `text-overflow: ellipsis` (nowrap truncation), `word-break`/`overflow-wrap` (splits an unbreakable long word), `overflow: hidden` clipping (in-flow rows + positioned boxes)
- ✅ Math functions `min()`/`max()`/`clamp()` in every length (whole-value or inside `calc()`), logical properties (`margin-inline`, `padding-block`, `inset-inline`, `inline-size`/`block-size`, …) with physical LTR mapping, `place-items`/`place-content`/`place-self`, two-value `gap: <row> <col>`, and the `font` shorthand
- ✅ `pointer-events: none` (removes an element from hover/click hit-testing), `content-visibility: hidden` (skips paint, keeps space), `image-rendering: pixelated` (nearest-neighbour image scaling), `caret-color` (tints the focused input caret)
- ✅ Automatic dark mode (`@media (prefers-color-scheme: dark)`, safe `@media` subset; no viewport leak)
- ✅ Headless mode
- ✅ Strong per-tab sandboxing
- ✅ Docker + noVNC
- ✅ Modern GUI: scrollbar, vim shortcuts, window management, themes (including sepia/night), hover previews
- ✅ Tor & I2P routing (`.onion` / `.i2p` + torify)
- ✅ Tab shortcuts estilo Vim
- ✅ Distraction-free (reader) mode (`Ctrl+D`): drops boilerplate + author styles, centers the text
- ✅ Debian packaging
- ✅ Comprehensive CI/CD + fuzzing + MCP automation
- ⚠️ CSS support still limited (author `<style>`/inline subset + safe `@media` + combinators + box model incl. `box-sizing: border-box` + text presentation `font-family`/`text-transform`/`letter-spacing`/`text-shadow`/`opacity`/…; `calc()`, `min()`/`max()`/`clamp()` and `var()`/custom properties supported — bounded, non-executing; per-item flex — `flex-grow`/`shrink`/`basis`/`order` + `flex-direction: column` + `flex-wrap` multi-line + `align-items`/`align-self` — lays out for real; borders/`box-shadow`/`outline` and `position`/`z-index` stacking are painted with `border-radius` rounding, `linear-gradient()` backgrounds paint, `overflow: hidden` clips; grid tracks resolve `fr` weights and fixed px and `grid-column: span N` places, but `grid-row` spans, `grid-template-rows` sizing and `align-content`/`justify-items` resolve without a paint effect; no transforms/animations; author-gated — see `spec/css.md` for the full supported-vs-missing inventory)
- ⚠️ JavaScript support still partial (no ES modules/`defer`, no events beyond click, no Web Components upgrade — but timers are real and async now)
- ⚠️ Full async networking/caching in progress

**Status**: Rapidly progressing Alpha — strong focus on secure rendering, usable GUI, and powerful anonymity tools (Tor/I2P).

## Building On Premise

```bash
# Clone the repository
git clone https://github.com/grisuno/FreeDom.git
cd FreeDom

# Install dependencies (Ubuntu/Debian example)
sudo ./install.sh

# Configure
./configure

# Build the browser
make clean && make all

# Run in GUI mode
weston --backend=x11-backend.so --renderer=pixman --width=1024 --height=768 &
WAYLAND_DISPLAY=wayland-1 ./build/freedom


# Run in headless mode
./freedom --headless https://example.com

# See what a page's JavaScript does, without a Wayland window (developer console).
# Runs the page's JS and prints every console.* call + any uncaught error.
./freedom --dump-console https://example.com
```

### Seeing JavaScript: the headless console

`--dump-console` runs the page's JavaScript and prints the captured console — every
`console.log`/`info`/`warn`/`error`/`debug` call, plus any uncaught script error — so you are
no longer blind about what the page's JS does and why it fails:

```
$ ./freedom --dump-console page.html
...page text...
=== Freebug console (3) ===
[log] hello from page 2
[warn] be careful
[error] inline #2:3:1  ReferenceError: notDefinedFn is not defined
```

Each uncaught error carries its **source location** — `file:line:col` — so you know exactly where
it threw: `inline #N` is the Nth inline `<script>` on the page (the page itself is in the URL bar),
and the line/column are the throw site (for minified code the column pinpoints it). Plain
`console.log` lines have no location. It implies JS on (a console dump with JS off is pointless) and
is a headless diagnostic, so it works in CI / over SSH / for an AI agent — no display required.

### Freebug: the in-window developer console (F12)

In the GUI, press **F12** (or pick **"Freebug console (F12)"** in the hamburger menu) to open
the **Freebug** developer console in a second window:

- The **log pane** shows the current page's `console.*` output and any uncaught JavaScript error,
  colour-coded by level. Errors are prefixed with their **`file:line:col`** (e.g. `inline #2:3:1`)
  in a muted tone, like a devtools source link, so you can jump straight to the failing line.
- The **editor** below is a JavaScript REPL: type or paste code and run it with **`Ctrl+Enter`**.
  It evaluates against the **live page** (the per-tab sandboxed worker stays alive for the console),
  so you see the returned value, any exception, *and* the console output the snippet produced.
- `Ctrl+L` clears the editor, drag the divider to resize the panes, mouse-wheel / arrows scroll the
  log, and `F12` / `Esc` closes the window.

So you are no longer blind about what a page's JS does or why it fails — and you can test fixes
interactively. The headless `--dump-console` above prints the same captured console for CI / agents.

### Seeing layout: the render-tree dump (`--dump-dom`)

When a page lays out wrong, `--dump-dom` prints the **paint-ready render tree** — the structure
the painter actually consumes — in a deterministic, agent-readable form, so you can see *why* a
node is mis-placed instead of guessing:

```
$ ./freedom --dump-dom --author-css news.ycombinator.com
=== Freedom render tree ===
blocks: 7  boxes: 1  containers: 1  has_images: 1
[boxes]
  #0 parent=-1 place(l=2 r=2 w=0 center=0) bg=- pad(2/2/2/2) bord(0/0/0/0 none) radius=0 shadow=0 outline=0
[blocks]
  #1 paragraph <p> bb cont=#0(grid cols=3 gap=0 start) "Hacker Newsnew | past | comments | ..."
  #3 paragraph <p> bb cont=#0(grid cols=3 gap=0 start) "1.Claude Sonnet 5 (anthropic.com)473 points by ..."
```

Each block shows its kind, tag, flags, the flex/grid **container** it joined (`cont=#id`), the
container **item** it belongs to (`item=N` — runs sharing `cont`/`item` are inline fragments of
one flex/grid item and flow together in one cell), the block-level **box** it belongs to
(`box=#id`), and any author style (align/font-size/colors/width caps); the `[boxes]` section
lists the box-definition tree (placement + decoration). Add
`--author-css` so the box tree is populated. It is a headless diagnostic — no display required —
and it is the instrument used to localise the "CSS paint gap". (For the *visual* counterpart, the
PNG export — `--download-png=PATH`, preferred over PDF — is the one-step, cheapest review artifact.)

### Seeing the resolved geometry: the layout dump (`--dump-layout`)

Where `--dump-dom` shows the render tree (the **input** to the layout engine), `--dump-layout` shows
the rectangles the box engine actually **produced** (the output): every line row `(top, h, x_off, w)`
— exposing the flex/grid column each line landed in (per-item `flex-grow`/`shrink`/`basis`/`order`
distribution included) — plus every in-flow box `(x, top, w, h)` and every out-of-flow positioned box
(with `z-index` and stacking order). Positioning, z-index stacking, flex distribution, and
wrapper-fragmentation bugs are visible as plain numbers — no display or rasterised image needed:

```
$ ./freedom --dump-layout --author-css examples/position-zindex.html
=== Freedom layout ===
content_w=952 total_h=204.7 nbox=2 nrow=4 npositioned=5
  box[0] bid=0 x=0.0 top=0.0 w=952.0 h=204.7
  box[1] bid=1 x=176.0 top=204.7 w=600.0 h=0.0
  pos[0] box=1 z=0 x=176.0 y=204.7 w=600.0 h=0.0
  pos[1] box=2 z=1 x=216.0 y=244.7 w=160.0 h=19.0
  pos[2] box=4 z=5 x=296.0 y=324.7 w=160.0 h=19.0
  pos[3] box=3 z=10 x=256.0 y=284.7 w=160.0 h=19.0
```

Here `nbox=2` (the body + one relative wrapper, each opened once — no fragmentation) and the
absolute boxes anchor near the wrapper (`y ≈ 244`, not at the page bottom). Add `--author-css` so
the box tree is populated. Headless diagnostic; pure I/O on already-resolved data.

## Address Bar, Search & Keyboard Shortcuts

The address bar works like a real **omnibox**:

- **`example.com`** → opens `https://example.com` (the scheme is added; a bare host is recognised).
- **`http://site`** → **upgraded to https** (Secure by Default: a downgrade is never representable).
- **`best linux distro`** (or anything that is not a URL) → runs a **DuckDuckGo HTML** search (the
  no-JS endpoint, which renders cleanly in Freedom).
- **`javascript:...` / `file:...` / `data:...`** → searched as text, **never executed** (fail-closed).
- An existing **local path** (e.g. `examples/rich.html`) still opens from disk. A local page gets a
  `file://` origin and **acts like https** for resolution: its relative links and images load from
  disk, confined to the document's own directory (no `../` escape, no phone-home). Enable images
  (`Ctrl+I`) to see local images such as the logo on the start page.

### JavaScript policy (per-domain allowlist)

Page JavaScript is hostile content, so it is **off by default**. A global tri-state mode controls it:

- `off` — never run page JS;
- `allowlist` (default) — run JS only for hosts listed in `js.conf`;
- `on` — run JS for every host (least safe; explicit opt-in).

Set it in the hamburger menu (the "JavaScript: …" row cycles the mode), with `--js[=off|allowlist|on]`,
or with the `FREEDOM_JS` env var. `js.conf` uses the same `/etc/hosts` format and search path as the
host filter (subdomains covered). When JS is enabled for a page, its **inline scripts execute** inside
the per-tab sandbox (seccomp + Landlock + namespaces, no I/O) against a memory-safe writable DOM. A
standard `document` facade exposes reads/writes (`document.title`, `getElementById().textContent`),
**DOM construction** (`createElement`, `appendChild`, `removeChild`, `setAttribute`, `body`/`head`),
**bounded synthetic events/timers** (`addEventListener('load')`/`window.onload`, `setTimeout` —
fired once after the page's scripts run), and **`innerHTML`**. Removed nodes are detached, never
freed, so a script can never dangle a handle (no use-after-free), and `appendChild` rejects cycles.

To run more real-world JS **without leaking your identity**, Freedom also provides an *identity-safe*
ambient surface: `localStorage`/`sessionStorage` are **in-memory and ephemeral** (Zero Knowledge —
never written to disk, cleared every load), `document.cookie` is always empty (set is a no-op),
`document.referrer` is empty, and `history`/`location` are benign stubs — so detection scripts run
without throwing while nothing about the user or device is revealed. With JS off, `<noscript>`
fallback content is shown.

**Real `querySelector` + a modern DOM surface.** `document.querySelector`/`querySelectorAll` and
`element.matches`/`closest` run through the **same author-CSS selector engine** the stylesheets use,
so a selector matches identically from JS and from CSS (type/`.class`/`#id`/`*`/`[attr]` + descendant/
child/sibling combinators + structural/`:link` pseudo-classes; unsupported constructs fail closed).
Elements expose `parentNode`/`children`/`firstElementChild`/`classList`/`style`, `DocumentFragment`
(its children re-parent on append), `createElementNS`, and node identity is cached so `===` works.
The globals a modern site touches at startup are present but **inert and identity-safe**:
`matchMedia` never matches, `MutationObserver`/`IntersectionObserver`/`ResizeObserver` never fire,
`getComputedStyle` returns `""` (no layout/font leak), `performance.timing` is a fixed epoch (no real
timing leaks), `requestAnimationFrame`/`queueMicrotask` feed a bounded synthetic pump, and the
viewport reads a fixed normalized `1920` width. `window.open`/`postMessage` stay **undefined** by
design (no popups, no cross-frame messaging). With this, real homepages like `google.com` render;
web-component apps (YouTube's Polymer shell) still do not, since custom-element upgrade is not
implemented.

**External `<script src>` scripts (sovereignty-gated).** For a host you trust **twice** — present in
both `allow.conf` **and** `js.conf` (headless: `--js=on`) — Freedom also fetches and runs the page's
*external* scripts, in document order, interleaved with the inline ones. The sandboxed worker never
touches a socket: script bytes are requested from the **trusted parent** over the same gated channel
as `XMLHttpRequest`/`fetch`, and the parent re-applies the *full* network policy (URL resolution
against the real page URL, host/tracker blocklist, Tor/I2P realm routing, TLS-PQ) before anything is
fetched. Responses only execute on HTTP 2xx with a JavaScript `Content-Type` (a 404 HTML page is
never evaluated), under the shared per-page time budget and request caps. Each script is named by its
URL, so Freebug reports errors as `url:line:col`. For every other host, external scripts still
**never** run.

> **Note on Google Search:** with external scripts enabled for `google.com`, Freedom executes
> Google's real JS — including its anti-bot *challenge*, whose token navigation Freedom follows under
> full policy. Google may still serve its server-side "unusual traffic" wall (an IP/cookie decision on
> their end; Freedom never persists cookies, by design). The address bar routes searches to the no-JS
> DuckDuckGo HTML endpoint, which renders cleanly.

Partially implemented: interactive click events (`addEventListener('click')` and `element.onclick`
fire over IPC and the GUI repaints the mutated DOM; no bubbling or coords yet). Out of scope for
now: real async timers, `defer`/`async`/ES-module scripts, and events other than click. JS-driven
navigation (`location.href=`/`assign`/`replace`) is followed — gated by the trusted parent and
capped against loops — both in the GUI and headless.

### Anti-fingerprinting identity

Every request carries a normalized, low-entropy `User-Agent` and `Accept-Language` shared by all
Freedom users — a common Firefox-on-Linux identity that matches what the JS engine reports
(`navigator.userAgent`). The on-the-wire identity and the in-page identity are the same, so there is
no mismatch to fingerprint, and Freedom never sends a "Freedom" product string (which is a unique
fingerprint and a bot signal). You can override the User-Agent per session in the hamburger menu;
leave it empty to use the anti-fingerprint default.

### Keyboard shortcuts

| Shortcut | Action |
| :-- | :-- |
| `Enter` / `Go` | Open the address, or search the web if it is not a URL |
| `Ctrl+L` | Focus the URL bar |
| `Ctrl+I` | Toggle remote images (off by default) |
| `Ctrl+D` | Distraction-free (reader) mode: drop nav/header/footer/aside + author styles, center the text |
| `Ctrl+P` | Save the current page as a vector PDF (selectable text) |
| `Ctrl+Shift+P` | Save the current page as a single PNG image (full-height bitmap) |
| `Ctrl+S` | Save the current page to `~/Downloads/freedom/` |
| `Ctrl+R` / `F5` | Reload the current page (re-applies the full TLS/PQ policy); also a toolbar button |
| `Ctrl++` / `Ctrl+-` / `Ctrl+0` | Zoom in / out (50–300% ladder) / reset to 100% |
| `Ctrl+C` / `Ctrl+X` / `Ctrl+V` | Copy (selection or field) / cut the omnibar selection / paste into the focused field |
| `Ctrl+A` | Select all in the URL bar (Shift+arrows / Shift+Home/End extend a selection) |
| `Ctrl+B` | Bookmark the current page (toggle); browse at `about:bookmarks` (menu: "Bookmarks & history") |
| `Ctrl+T` / `Ctrl+W` / `Ctrl+Tab` | New tab / close tab / next tab |
| `Ctrl+Shift+B` / `Ctrl+Shift+A` / `Ctrl+Shift+J` | Add the current host to `block.conf` / `allow.conf` / `js.conf` (applies immediately) |
| `Ctrl+Shift+E` | Per-host exception for a weak-but-valid certificate (this session) |
| `j` / `k` | Scroll one line down / up (URL bar unfocused) |
| `Space` / `b` | Scroll one page down / up |
| `gg` / `G`, `Home` / `End` | Jump to top / bottom |

### Downloads & zoom

A link to a non-renderable resource (PDF, archive, e-book) is **saved** to
`~/Downloads/freedom/` instead of being parsed as a page; `Ctrl+S` saves the current
page there too. Because the filename comes from hostile input (the `Content-Disposition`
header and the URL), it is derived **fail-closed** by the pure `download` module: only
`[A-Za-z0-9._-]` survive, every separator maps to `_`, no `..` traversal and no hidden
leading dot are representable, and the extension is synthesized from the media type when
missing (reusing the same `pe_safe_basename` sanitizer as the PDF export). The body is
size-capped (256 MiB) and the file is written atomically with `0600` permissions.

Zoom (`Ctrl++` / `Ctrl+-`) snaps to a 50–300% ladder, `Ctrl+0` resets to 100%; the page
reflows at the new size with no network round-trip.

### Author CSS & distraction-free reading

Enable **Author styles (CSS)** in the menu to see the page the way the webmaster intended.
With the toggle on, Freedom also fetches the page's **external stylesheets**
(`<link rel=stylesheet>`): the confined worker asks the trusted parent for each sheet, and
the parent re-applies the full network policy (host blocklist, realm routing, TLS-PQ) before
any byte moves — style-only pages are limited to `GET` at the parent's gate, a wrong
Content-Type is never parsed as CSS, and with the toggle off nothing is fetched at all
(Privacy by Default). Freedom renders the author's own CSS — external sheets, `<style>`
blocks and inline `style=` — using a
deliberately simpler subset: `color`, `background`, `text-align`, `font-size`, `line-height`,
`font-weight`, `font-style`, `text-decoration` (`underline`/`line-through`/`overline`/`none`),
`display` (including `display:none`), with type / `.class` / `#id`
/ `*` / group selectors, the descendant (`div p`) and child (`nav > a`) combinators, **attribute
selectors** (`[type=text]`, `[href^="https"]`, `[lang|="en"]`, `~=`/`$=`/`*=` with the `i` case
flag), `!important`, and a real specificity-then-document-order cascade (inline wins). It is
rendered by the pure `css` module and stays gated behind the author-CSS capability (Privacy by
Default). For headless visual review, `freedom --author-css --download-png=PATH …` applies author
styling in the exported image (local render only — the network image cap stays off); see
`examples/attr-selectors.html`. **Sibling combinators** (`h2 + p` adjacent, `h2 ~ p` general) and a **pseudo-class subset**
are supported too: `:link`/`:any-link` (Zero Knowledge — no history, so every link is
unvisited and CSS history sniffing is impossible), `:root`, `:first-child`/`:last-child`/
`:only-child`/`:nth-child(An+B)`/`:nth-last-child()`, `:checked`/`:disabled`/`:enabled`;
`:visited` and the dynamic `:hover`/`:focus`/`:active` parse (keeping the rule group alive)
but never match; unknown pseudo-classes and all pseudo-elements (`::before`) fail closed.
Demo: `examples/pseudo-classes.html`.

**Text presentation:** the author subset also covers `font-family` (mapped to a generic family —
serif / sans-serif / monospace / cursive / fantasy; exact font files are never matched and
`@font-face`/`url()` are dropped, so it never fetches), `text-transform`
(`uppercase`/`lowercase`/`capitalize`), `letter-spacing`, `word-spacing`, `text-shadow` (single
layer), `opacity`, `vertical-align` (`sub`/`super`), `text-indent`, `white-space` (`nowrap`/`pre`
suppress wrapping) and `list-style-type` (`decimal`/`lower-alpha`/`upper-roman`/`disc`/`circle`/
`square`/… changes the `<li>` marker). All but `list-style` are gated behind the Author-styles
toggle. See `examples/text-presentation.html` and the full **supported-vs-missing** property
inventory in `spec/css.md`.

**Visibility, cursor & text wrapping:** `visibility:hidden` hides an element while still
reserving its layout space (unlike `display:none`, which removes it entirely — a nested
flex/grid container inside a hidden box is a known v1 gap); `cursor:pointer` shows the hand
cursor on any element, not just links (the rest of the CSS cursor keyword set resolves for
completeness but still paints as the default arrow); `text-overflow:ellipsis` truncates a
`white-space:nowrap` line that doesn't fit, with "…" appended at the UTF-8 boundary that
still fits; `word-break`/`overflow-wrap`/`word-wrap` (unified into one behaviour) split an
unbreakable long word — a URL, say — at UTF-8 cluster boundaries instead of letting it
overflow the box edge. `overflow`/`-x`/`-y` parse and resolve (so the cascade never
misinterprets them) but clipping isn't painted yet. See `examples/visibility-and-text-wrap.html`.

**Flex & grid from the stylesheet:** a `display:flex` / `display:grid` container takes its
layout params (`gap`, `justify-content`, `grid-template-columns`) from the same cascade, so a
`<style>` rule lays out columns — not only an inline `style=`. Because layout is *structure*,
not styling, the columns render even with author colors off (only author colors stay gated by
the toggle). See `examples/css-sheet-layout.html`.

**Flex per-item (Stage 3):** each item's `flex-grow` / `flex-shrink` / `flex-basis` (and the
`flex` shorthand) drive a real main-axis distribution — `flex: 0 0 200px` sidebar next to a
`flex: 1` main column works like in a modern browser; `order` reorders items visually (stable,
document order on ties); `flex-direction: column` stacks items vertically with the container
gap. Whitespace between items never fabricates ghost columns. Containers whose items declare no
flex properties keep the equal-column layout. See `examples/flex-items.html`, and
`--dump-layout` to inspect the resolved columns as numbers.

**Real items, no blank lines (container-item identity + anonymous-box whitespace):** inline
fragments of one container child (`text <a>link</a> text`) form **one** flex/grid item that flows
together in its cell — not one column per fragment — because every run carries the ordinal of the
container child it belongs to (`cont_item`, printed by `--dump-dom` as `item=N`); collected table
cells keep one ordinal per cell, so data tables still align column by column. And whitespace-only
text between block elements generates **no box at all** (the CSS anonymous-box rule): the source
newlines between `<div>`s no longer paint empty lines. On Wikipedia's Main Page this removed
~6,500 px of blank page and made the lead paragraph read like a real browser render.

**Box model (`margin` / `padding` / `width` / `max-width`):** resolved through the same cascade
(lengths in `px`, a bare `0`, or `em`/`rem`; `%`/viewport units fail closed). The headline win is
the modern **centered reading column** — `max-width` + `margin: 0 auto` + horizontal padding — and
an author `margin-top`/`margin-bottom` overrides the default block spacing. Because an author box
can shrink content to unreadability, the box model is gated behind the author-CSS capability like
the colors (Secure/Privacy by Default). Out of scope for now: `border`, `box-sizing`, vertical
`padding-top/bottom`, and `position`. See `examples/box-model.html`
(`freedom --author-css --download-png=… examples/box-model.html`).

**Automatic dark mode:** `@media` is supported as a safe subset — with the dark theme on (and
Author styles enabled), a page's `@media (prefers-color-scheme: dark)` rules apply automatically.
`screen`/`print` and `min-width`/`max-width` queries evaluate against a fixed, normalized desktop
width (no real viewport size leaks — anti-fingerprinting); `not` and unknown features fail closed.

CSS is hostile content, so the parser **never phones home**: any value containing `url(` and the
network/font `@`-rules (`@import` / `@font-face`) are dropped, and `@media` can only choose which
*local* rules apply — author CSS can never trigger a fetch or a tracking beacon. It is bounded
(anti-DoS) and fails closed. `expression()` and JS URLs are never evaluated; `var()`/custom
properties (a page-global `--name` table) and `calc()` (`+`/`-`/`*`/`/`, dimensionally checked) **are**
evaluated, but only as bounded text substitution and arithmetic over values the parser already
understands — never code, never a fetch, never unbounded (depth-capped lookups). It is fuzzed
(`make fuzz-css`).

**Distraction-free mode** (`Ctrl+D`, or the menu) is a clean reading view: `nav` / `header` /
`footer` / `aside` boilerplate is dropped in the sandboxed worker, author styling and images are
turned off for the view, and the text is centered in a comfortable reading column. Toggle again
to restore — your persistent image/CSS toggles are left untouched.

## Privacy Networking: Tor, I2P & Host Filtering

FreeDom integrates Tor and I2P **at the socket level** (it routes through a local proxy you run; it
never embeds the Tor/I2P daemon — minimal attack surface). The routing brain is the pure, tested
`net_realm` module, which guarantees two anonymity invariants:

- **Realm isolation**: a `.onion` address only ever exits through Tor, a `.i2p` only through I2P.
- **Fail-closed**: if a realm's proxy is not enabled, the request is **blocked**, never leaked over
  the clearnet. DNS for Tor is resolved remotely (SOCKS5h), so there is no DNS leak.

### Tor (`.onion`)

```bash
sudo systemctl start tor      # Tor SOCKS5 proxy on 127.0.0.1:9050
./build/freedom --tor https://<address>.onion/        # headless
# GUI: hamburger menu → enable "Tor routing (.onion)", then reload
```

`.onion` stays **https-only** by owner policy (most large onions — DuckDuckGo, NYT — serve https).
Use `--torify` (or `FREEDOM_TORIFY_CLEARNET=1`) to route ordinary clearnet sites through Tor too.

### I2P (`.i2p`)

```bash
sudo systemctl start i2pd     # or: i2prouter start   (Java router)
                              # HTTP proxy on 127.0.0.1:4444
./build/freedom --i2p http://stats.i2p/               # headless
# GUI: hamburger menu → enable "I2P routing (.i2p)", then reload
```

I2P eepsites are served over **http** — FreeDom allows plain http **only** for `.i2p`, where the I2P
layer already encrypts and authenticates by destination (http on the clearnet is still rejected).
Note: I2P takes several minutes to integrate (build tunnels) on first start; until then requests fail
closed (no leak), not load.

### Configuration (flags / env / menu)

| Setting | CLI flag (headless) | Env var | GUI |
| :-- | :-- | :-- | :-- |
| Tor routing | `--tor[=host:port]` | `FREEDOM_TOR_PROXY` (`1` = default) | "Tor routing (.onion)" |
| I2P routing | `--i2p[=host:port]` | `FREEDOM_I2P_PROXY` (`1` = default) | "I2P routing (.i2p)" |
| Torify clearnet | `--torify` | `FREEDOM_TORIFY_CLEARNET=1` | (implied by Tor toggle) |

### Host filtering & the sovereignty allowlist

A pure `hostblock` module reads two `/etc/hosts`-format files — `block.conf` (blocklist) and
`allow.conf` (allowlist) — from `$FREEDOM_HOSTS_DIR`, `~/.config/freedom`, or `./config` (sample
files ship in `config/`). The format is one domain per line, or `0.0.0.0 domain` hosts-style lines.

- A blocklisted domain blocks itself **and all subdomains**; the allowlist **wins** and likewise
  covers subdomains — so you can re-enable one subdomain of an otherwise blocked domain.
- The allowlist is also your **sovereignty override**: a host listed there may be navigated even when
  it falls below FreeDom's elevated TLS standard. If the strict attempt fails, FreeDom retries
  accepting TLS 1.2, a classical key exchange, and a weak-but-valid certificate (with a warning). The
  certificate chain is still authenticated, so you reach the real site over older crypto, not an
  impostor. This is how TLS-1.2-only sites such as **Hacker News** (`news.ycombinator.com`) load —
  secure by default, but you are sovereign over your own hosts.

This is purely opt-in: with no list files present, nothing is blocked (the filter fails open — it is
an adblock-style layer, not the security boundary).

Although Freedom uses neither the Blink (Chromium) nor the Gecko (Firefox) engine, it deliberately
presents the **identity** of a common Firefox-on-Linux browser on the wire (a shared, normalized
`User-Agent` and `Accept-Language`). The goal is anti-fingerprinting by **blending in**, not by
standing out: every Freedom user looks identical and indistinguishable from a large crowd, which
starves the commercial Machine Learning models that try to profile you from your browser's
behaviour — while still letting fingerprinting-hostile sites (Google, Cloudflare) serve you instead
of a bot-challenge wall.

## Fuzzing

Empirical security in C: Passing 10 full AFL++ mutation cycles and 700 unique code paths with 0 crashes, 0 hangs, and a rock-solid 75% stability map.

```bash
# 10 Cycles | 700 Paths | 0 Crashes | 0 Hangs | 74.91% Stability
./fuzz.sh
```

## Docker

FreeDom is fully compatible with Docker, enabling seamless deployment within an isolated sandbox environment.

FreeDom has evolved from an experimental build into a fully automated environment. The repository now features standard Unix ./configure validation, a robust install.sh for dependency management, and strict Zero-Trust runtime isolation using a custom Docker architecture—all continuously validated through an automated GitHub Actions CI/CD workflow.

```bash
sudo docker build -t freedom-browser . 

sudo docker run -it \
  --name freedom-test \
  -p 8080:8080 \
  --cap-drop=ALL \
  --security-opt no-new-privileges:true \
  --memory="2g" \
  freedom-browser
```

## Agentic Automation (MCP Server)

This repository includes an MCP (Model Context Protocol) server (`app.py`) that allows AI agents and LLM bridges (like the LazyOwn framework or OpenCode Adapter) to interact with and monitor the fuzzing environment natively.

The ability to act as a semantic reduction and normalization layer before information reaches the agentic/LLM

### Exposed Tools
* `read_fuzz_stats`: Reads the real-time performance and metrics from the active AFL++ session.
* `list_unique_crashes`: Lists all unique payloads that triggered a browser crash.
* `run_freedom_headless`: Executes `./build/freedom --headless <payload_path>` to triage specific inputs or mutated seeds programmatically.

### Usage

1. Install the required dependencies:

```bash
pip install -r requirements.txt
```

2. Configure your MCP client or agent routing table to invoke the server via stdio:

```bash
# Do not run interactively meant for stdio communication via your MCP host configuration
python3 app.py
```

## Project Structure

```text
FreeDom/
├── src/           # Core source code (one .c per module: secure_fetch, net_realm, hostblock, ...)
├── gui/           # Wayland + Cairo GUI implementation
├── include/       # Public headers (module contracts)
├── spec/          # SDD specifications (one spec per module)
├── config/        # Sample host filter lists (block.conf / allow.conf)
├── examples/      # Sample pages (rich.html, flex.html, ...)
├── third_party/   # Vendored libraries (Lexbor, QuickJS-ng, etc.)
├── tests/         # Unit (CMocka) and integration tests
├── fuzz/          # Fuzzing harnesses
├── docs/          # Documentation
└── Makefile       # Build system
```

## CI/CD & Enterprise Deployment

FreeDom is built for deterministic environments and integrates a layered deployment strategy:

* **Automated CI/CD Pipeline:** Every commit triggers a headless GitHub Actions workflow that fuzzes code, runs unit tests via CMocka, and validates cross-compilation parity.
* **Standard Toolchain (`./configure && make`):** Implements a traditional, low-dependency build workflow with built-in parches for OpenSSL compatibility.
* **Deterministic Sandbox (Docker):** Bundles a secure Xvfb + noVNC + Weston stack inside a non-root container, stripping Linux capabilities (`--cap-drop=ALL`) to guarantee zero host contamination during execution.

## Security

FreeDom follows security-by-design principles:
- Zero Trust architecture
- Strong sandboxing at OS and language level
- Minimal dependencies
- Hardened compiler flags
- Regular fuzzing and code auditing

See [SECURITY.md](SECURITY.md) for reporting vulnerabilities.


## Development

This project is written in pure C11 and is security-hardened by default using stack protection, control-flow protection (-fcf-protection), and PIE. 

### Prerequisites

Ensure you have the required development libraries installed (e.g., via apt on Kali/Debian):

```bash
sudo apt install liblexbor-dev libcmocka-dev libcurl4-openssl-dev libwayland-dev wayland-protocols libcairo2-dev libfontconfig-dev libfreetype6-dev libharfbuzz-dev libxkbcommon-dev pkg-config clang
```

### Available Targets

Run the following commands from the root directory of the repository:

* make (or make all): Compiles the main project and generates the binary executable at build/freedom.
* sudo make install: Installs the compiled binary globally into /usr/local/bin/.
* make test: Runs the TDD unit test suites utilizing the cmocka framework.
* make itest: Executes network-dependent integration tests (performs a live PQ key exchange GET request).
* make asan: Recompiles and runs all test suites under AddressSanitizer (ASan) and UndefinedBehaviorSanitizer (UBSan) to detect memory leaks and UB.
* make fuzz: Initiates a 30-second coverage-guided fuzzing session on the HTML parser using libFuzzer.
* make fuzz-js: Initiates a 30-second coverage-guided fuzzing session on the isolated JavaScript sandbox.
* make fuzz-css: Fuzzes the author-CSS parser + cascade (hostile `<style>` bytes; never phones home).
* make fuzz-pv / fuzz-img / fuzz-pe / fuzz-dl: Fuzz the display-list builder / PNG+JPEG decoder / PDF-name / download-name paths.
* make view: Compiles the experimental standalone Wayland + Cairo GUI demo application (build/freedom-view).
* make clean: Wipes out the build/ directory and resets the environment.


```bash
make 
sudo make install
make test
make itest
make asan
make fuzz
make fuzz-js
make view
make clean
```

## Secreenshots

### Tor working on dark mode

<img width="921" height="718" alt="image" src="https://github.com/user-attachments/assets/e6b9ef46-f75a-47a6-a1f0-98074b7fd424" />

## Contributing

Contributions are welcome. Please read [CONTRIBUTING.md](CONTRIBUTING.md) first.

## Roadmap

- Complete GUI implementation
- Full CSS support
- Improved networking and caching
- Extension system (future)
- More platform support (Linux first, others later)

---

## License

This project is licensed under the **AGPL-3.0** license - see the [LICENSE](LICENSE) file for details.

---

For more information, visit the [GitHub repository](https://github.com/grisuno/FreeDom).

![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54) ![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white) [![License: AGPL v3](https://img.shields.io/badge/License-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Y8Y2Z73AV)
