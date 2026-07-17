# Freedom

<img width="3716" height="1038" alt="screenshot" src="https://github.com/user-attachments/assets/f05ca2e0-0202-4708-a384-c49025967c18" />
<img width="3840" height="1080" alt="screenshot" src="https://github.com/user-attachments/assets/b989152a-9d14-441c-af9b-e36fa82e67b9" />

From the creators of LazyOwn Redteam Framework comes a free and open-source minimal web
browser written in C, focused on Zero Trust and Zero Knowledge principles.

## Quick Start

**Easiest way to try Freedom right now:**

```bash
git clone https://github.com/grisuno/FreeDom.git
cd FreeDom
```

### Native build (Linux)

**Dependencies:** `libavformat-dev libavcodec-dev libavutil-dev libswscale-dev`
(FFmpeg for H.264/H.265 video decoding), plus the same as the Dockerfile.

```bash
sudo apt install libavformat-dev libavcodec-dev libavutil-dev libswscale-dev
make
./build/freedom
```

### Docker (strongly recommended for testing)

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

Then open your browser and go to: http://localhost:8080/vnc.html

<img width="1127" height="921" alt="screenshot" src="https://github.com/user-attachments/assets/b00510ab-3870-4212-964d-56634ecc9c88" />

## Philosophy

<img width="800" height="450" alt="browser" src="https://github.com/user-attachments/assets/82918e97-852a-4bf0-81ce-ae39484008c4" />

Freedom (Free + DOM) is a lightweight, security-first web browser built from the
ground up in modern C. It prioritizes user privacy, strong isolation, and minimal
attack surface over feature bloat.

The name reflects its core goals:
- **Free**: Libre (freedom) and open source
- **Dom**: Reference to the DOM (Document Object Model) and domain-level control

## Freedom officially bans Google.

Their services cannot be implemented without compromising user privacy through
telemetry, mandatory API keys, or hidden solver workers. We refuse to do so.

## Features

- Portable C11 — no C++, no Rust, no hidden dependencies
- Strong process-based sandboxing for each tab: the worker is **forked and re-exec'd**
  so it inherits none of the browser's memory (a compromised tab cannot read other
  tabs' content; fresh ASLR), then confined with seccomp-bpf with **W^X** (no
  executable memory — `PROT_EXEC` `mmap`/`mprotect` are killed), Landlock, per-tab
  namespaces, and an undumpable worker so secrets cannot leak via core dump or
  ptrace. The syscall allowlist is **deny-by-default**, so **`io_uring` is blocked**
  in the worker — it is a seccomp-bypass primitive, so it never gets in.
- JavaScript sandbox using QuickJS-ng
- Hardened build with stack protection, PIE, RELRO, and FORTIFY_SOURCE
- Wayland + Cairo GUI backend with Client-Side Decorations (CSD)
- HarfBuzz text shaping (ligatures, GPOS kerning, complex scripts) on the trusted
  side, with local fonts only — never in the sandboxed worker, never a web font fetch
- Lexbor HTML parser and renderer
- Strict request policy using Public Suffix List + blocklist/allowlist
- Post-quantum hybrid cryptography support (X25519MLKEM768)
- Headless mode for automation and testing
- Anti-fingerprinting techniques
- Comprehensive test suite, fuzzing, and integration tests

### Modern Web Rendering (R1-R8 — July 2026)

A modernization push across eight phases delivered a rendering engine comparable
to modern browsers for trusted hosts (hosts present in both `allow.conf` and
`js.conf`):

**Animations & Transitions (R1):** pure interpolation engine (`interp` module)
supporting CSS easing functions (linear, ease, ease-in/out, steps, cubic-bezier),
scalar and color value interpolation, keyframe interpolation, and a full animation
state machine handling delays, direction, fill modes, and iteration counts.
`animation-duration` CSS property parsed and flows through the full pipeline
(CSS -> page_view -> IPC -> paint). `@keyframes` at-rules are parsed and stored;
`animation-name`, `animation-iteration-count`, `animation-direction`,
`animation-fill-mode`, `animation-timing-function`, and `animation-delay` are
all parsed through the CSS cascade. In the GUI, boxes with animations
automatically form stacking contexts and composite with animated opacity blended
from the interpolation engine against wall-clock time.

**Advanced Selectors (R2):** `:first-of-type`, `:last-of-type`, `:only-of-type`,
`:nth-of-type(An+B)`, `:nth-last-of-type(An+B)`, `:empty`, `:target`, and
`:lang(ident)` pseudo-classes fully parsed and matched. The existing `:not()`,
`:is()`, and `:where()` functional pseudo-classes were already implemented.
The DOM element chain (`css_chain.c`) was extended with per-type sibling counting
and child count for accurate matching. `:empty` correctly detects elements with
zero child nodes. `:lang()` performs case-insensitive prefix matching on the
`lang` attribute. Pseudo-elements are correctly distinguished: `::before` and
`::after` match in the CSS cascade (for style resolution) but never match in
DOM queries like `querySelector` (matching real browser behavior).

**CSS Filters (R3):** `filter: blur(Npx)` and `filter: grayscale(N%)` parsed
through the full pipeline. In the GUI, boxes with filters form stacking contexts.
The grayscale filter is applied via Cairo pixel manipulation: the box's offscreen
group is extracted as an image surface, each pixel is converted to grayscale
(weighted luminance: 0.299R + 0.587G + 0.114B), and the modified surface is
blended back with partial grayscale factor. Anti-DoS bounded at 4096px.

**Layout & Positioning (R4):** `position: sticky` implemented — boxes pin to the
viewport top when scrolled past their in-flow position, common for fixed
navigation bars. `right` and `bottom` CSS insets now honored for absolute/fixed
positioned boxes: when `right` is set and `left` is auto, the box anchors to
the right edge of its containing block (and similarly for `bottom`). These were
already parsed but previously ignored in the box-tree position resolver.

**Background Enhancements (R5):** `background-position` parsed with keyword
(`left`/`center`/`right`/`top`/`bottom`) and pixel value support. Applied as
a Cairo translate offset in the box decoration painter, with `center`
auto-resolving to `(box_w - img_w) / 2`. Multi-layer `background-image` with
comma-separated URLs (`url(a.png), url(b.png)`) — second layer painted behind
the first with independent sizing, repeat, and position. `radial-gradient()`
parsed and painted via `cairo_pattern_create_radial` with center at box center.
Gradient stop positions (e.g. `red 20%, blue 80%`) now consumed instead of
always-even spacing.

**Nested Compositor Tree (R6):** stacking-context boxes now recursively compose
their entire subtree as a single offscreen Cairo group. A parent with opacity
properly blends its children (including nested stacking contexts) as one unit —
fixing the previous limitation where child boxes with their own opacity were
composited independently on top of the parent's group. Implemented via a
recursive `paint_nested_children` helper that traverses the box tree.

**JavaScript Modernization (R7):** `<script defer>` attribute parsed in the HTML
parser and honored via two-pass script execution: sync/external scripts run first,
deferred scripts run after, all sharing the same per-page JS time budget.
`customElements.define()` now stores constructors in a live registry and fires
`connectedCallback` during `__fireDeferred`. Binary `arrayBuffer` response type
in XHR/fetch: `__hostFetch` returns raw binary as an ArrayBuffer, and
`responseType='arraybuffer'` in XHR as well as `fetch().arrayBuffer()` return
real binary data. DOM events `keydown`, `input`, `change`, `blur`, and `focus`
were already fully wired (discovered during the audit).

**Pseudo-elements (R8):** `::before` and `::after` parsed in the selector engine
and matched in the CSS cascade (rules like `div::before { color: red; }` apply
their styles). The `content` property is parsed (quoted strings) and stored in
`css_style`. DOM queries correctly reject pseudo-elements (matching browser
behavior). Full content injection into the display list during the page_view
walk is deferred to a follow-up.

### Additional Modern Features

- **Trusted-host full experience (Hito 28):** a host trusted **twice** (in
  `allow.conf` **and** `js.conf`) automatically gets author CSS, images, and
  full JS — no per-session toggles needed.
- **Parallel subresource prefetch (Hito 29):** a preload scanner on the trusted
  side scans raw HTML for `<link rel=stylesheet>` and `<script src>`, downloading
  them in parallel (up to 4 threads) through the same policy-gated fetcher while
  the worker parses. Total wait tends to the maximum latency instead of the sum.
- **Advanced Layout Engine:** full box model per HTML tag (margins, padding,
  display, border), flexbox with `gap`/`justify-content`/`flex-wrap` multi-line/
  `align-items`/`align-self`, CSS Grid with sized tracks (`fr` weights, fixed px,
  `repeat()`/`minmax()`, `grid-column: span N`), and recursive box-tree layout
  with margin collapsing.
- **GUI:** visible scrollbar, Vim-style shortcuts (`j`/`k`, `gg`/`G`, etc.),
  window controls (maximize, minimize, resize, titlebar drag), sepia/light/dark
  themes, hover link preview, loading indicator, multi-tab with shortcuts.
- **Anti-fingerprinting:** normalized `User-Agent` and `Accept-Language` shared
  by all Freedom users — a common Firefox/Linux identity.
- **Omnibox:** type a URL to navigate (`https://` added, `http://` upgraded) or
  anything else for a DuckDuckGo HTML (no-JS) search. Dangerous schemes like
  `javascript:` are searched, never executed.
- **Per-domain JS policy + live JS:** Secure by Default — page JS off unless opted
  in. Global tri-state mode (off/allowlist/on) plus `js.conf` allowlist. Inline
  scripts execute in the sandboxed worker against a memory-safe writable DOM.
- **Tor & I2P:** `.onion` routing via SOCKS5h proxy, `.i2p` via HTTP proxy, both
  fail-closed (never leak to clearnet).
- **Encrypted persistent profile (Hito 10):** preferences, bookmarks, and history
  sealed with AES-256-GCM under a per-device Argon2id key, atomic 0600, nothing
  readable on disk.
- **External stylesheets and scripts:** fetched by the trusted parent under full
  network policy for trusted hosts — the sandboxed worker never touches a socket.
- **Real async JS timers:** `setTimeout`/`setInterval` with actual delays on a
  virtual clock the trusted parent drives (the worker cannot wake itself).
- **PDF/PNG export:** `Ctrl+P` for vector PDF, `Ctrl+Shift+P` for full-height PNG.
- **Safe downloads:** `Ctrl+S` with fail-closed filenames, atomic 0600 writes.
- **Page zoom:** `Ctrl++`/`Ctrl+-`/`Ctrl+0` with 50-300% ladder.
- **Box model:** `margin`/`padding`/`width`/`max-width` with `box-sizing:
  border-box`, `border-radius`, `box-shadow` (outset and inset), `outline`,
  `visibility:hidden`, `cursor:pointer`, `text-overflow:ellipsis`, `word-break`,
  `overflow:hidden` clipping.
- **Math functions:** `min()`/`max()`/`clamp()` in lengths, `calc()` with
  dimensional checking, `var()`/custom properties with depth-capped lookups.
- **Logical properties:** `margin-inline`, `padding-block`, `inset-inline`,
  `inline-size`/`block-size` with physical LTR mapping.
- **Automatic dark mode:** `@media (prefers-color-scheme: dark)` applies
  automatically when the dark theme is on.
- **CSS transforms:** `translate()`, `scale()`, `rotate()` via real Cairo affine
  matrix (pivoted at box center). Single function per declaration; `skew()`/
  `matrix()`/chaining not yet supported.
- **Form controls:** native GET/POST without JS, text inputs, checkboxes,
  select menus, submit buttons.
- **Image formats:** PNG, JPEG, WebP, and static GIF (own bounded pure-C LZW
  decoder, no giflib). Inline `data:` images. All decoded inside the sandboxed
  worker.

## Current Status (July 16, 2026)

- Advanced HTML rendering with box model, flex/grid, margin collapsing
- Clickable links + image support (PNG + JPEG + WebP + static GIF)
- Inline `data:` images with zero network request
- CSS `background-image` with `linear-gradient()`, `radial-gradient()`, and
  `url(...)` (fetched/decoded under same policy as `<img>`)
- `background-position`, `background-size`, `background-repeat`, multi-layer
- `border-radius` on backgrounds, borders, shadows, and outlines
- `box-sizing: border-box` honored
- CSS `filter: blur()` and `filter: grayscale()` parsed, grayscale painted
- Animation engine with `animation-duration` and `@keyframes` parsing
- Advanced selectors: `:nth-of-type()`, `:first-of-type`, `:empty`, `:lang()`,
  `:not()`/`:is()`/`:where()`
- `::before`/`::after` parsed and matched in CSS cascade
- `position: sticky` (pins to viewport on scroll)
- `right`/`bottom` insets honored for absolute/fixed positioning
- Gradient stop positions consumed (not always evenly spaced)
- Nested compositor tree (opacity of parent blends entire subtree)
- `<script defer>` two-pass execution
- `customElements.define()` with `connectedCallback`
- Binary `arrayBuffer` in XHR/fetch
- Real async JS timers on a virtual clock
- `innerHTML` getter and setter
- Anti-fingerprinting network identity (normalized User-Agent + Accept-Language)
- Omnibox address bar (navigate or DuckDuckGo HTML search)
- Native forms (GET/POST, no JS)
- Save page as vector PDF (`Ctrl+P`) or PNG (`Ctrl+Shift+P`)
- Safe downloads (`Ctrl+S`, fail-closed filenames, 0600)
- Page zoom (`Ctrl++`/`Ctrl+-`/`Ctrl+0`) and reload (`Ctrl+R`/`F5`)
- Encrypted persistent profile (preferences, bookmarks, history)
- Author CSS with cascade (descendant/child/sibling combinators, attribute
  selectors, pseudo-classes, `!important`) — never phones home
- External stylesheets fetched by trusted parent under full policy
- Box model (`margin`/`padding`/`width`/`max-width`), text presentation
  (`font-family`, `text-transform`, `letter-spacing`, etc.)
- `visibility`, `cursor`, `text-overflow`, `word-break`, `overflow:hidden`
- Math functions, logical properties, `var()`/custom properties
- Automatic dark mode (`@media (prefers-color-scheme: dark)`)
- CSS transforms: `translate()`, `scale()`, `rotate()` via Cairo affine matrix
- Headless mode, `--dump-console`, `--dump-dom`, `--dump-layout`
- Strong per-tab sandboxing (seccomp-bpf W^X, Landlock, namespaces)
- Docker + noVNC
- Tor & I2P routing (`.onion`/`.i2p` + torify)
- Distraction-free (reader) mode (`Ctrl+D`)
- Debian packaging
- CI/CD + fuzzing + MCP automation

## Building On Premise

```bash
# Clone the repository
git clone https://github.com/grisuno/FreeDom.git
cd FreeDom

# Install dependencies (Ubuntu/Debian)
sudo ./install.sh

# Configure
./configure

# Build the browser
make clean && make all

# Run in GUI mode
weston --backend=x11-backend.so --renderer=pixman --width=1024 --height=768 &
WAYLAND_DISPLAY=wayland-1 ./build/freedom

# Run in headless mode
./build/freedom --headless https://example.com

# See what a page's JavaScript does (developer console, no Wayland needed)
./build/freedom --dump-console https://example.com
```

### Seeing JavaScript: the headless console

`--dump-console` runs the page's JavaScript and prints the captured console —
every `console.log`/`info`/`warn`/`error`/`debug` call, plus any uncaught script
error:

```
$ ./build/freedom --dump-console page.html
...page text...
=== Freebug console (3) ===
[log] hello from page 2
[warn] be careful
[error] inline #2:3:1  ReferenceError: notDefinedFn is not defined
```

Each uncaught error carries its **source location** — `file:line:col` — so you
know exactly where it threw. `inline #N` is the Nth inline `<script>` on the
page. Plain `console.log` lines have no location. It implies JS on and is a
headless diagnostic, so it works in CI / over SSH / for an AI agent.

### Freebug: the in-window developer console (F12)

In the GUI, press **F12** (or pick "Freebug console (F12)" in the hamburger menu)
to open the Freebug developer console in a second window:

- The **log pane** shows the current page's `console.*` output and any uncaught
  JavaScript error, colour-coded by level. Errors show their `file:line:col` in
  a muted tone.
- The **editor** below is a JavaScript REPL: type or paste code and run it with
  `Ctrl+Enter`. It evaluates against the **live page** (the per-tab sandboxed
  worker stays alive for the console).
- `Ctrl+L` clears the editor, drag the divider to resize panes, `F12`/`Esc`
  closes the window.

### Seeing layout: `--dump-dom`

Prints the paint-ready render tree in a deterministic, agent-readable form:

```
$ ./build/freedom --dump-dom --author-css news.ycombinator.com
=== Freedom render tree ===
blocks: 7  boxes: 1  containers: 1  has_images: 1
[boxes]
  #0 parent=-1 place(l=2 r=2 w=0 center=0) bg=- pad(2/2/2/2) ...
[blocks]
  #1 paragraph <p> bb cont=#0(grid cols=3 gap=0 start) ...
  #3 paragraph <p> bb cont=#0(grid cols=3 gap=0 start) ...
```

Each block shows its kind, tag, container, box, and author style. Add
`--author-css` so the box tree is populated. For the visual counterpart,
`--download-png=PATH` is the preferred one-step review artifact.

### Seeing the resolved geometry: `--dump-layout`

Shows the rectangles the box engine actually produced — every line row, box,
and positioned box with z-index and stacking order:

```
$ ./build/freedom --dump-layout --author-css examples/position-zindex.html
=== Freedom layout ===
content_w=952 total_h=204.7 nbox=2 nrow=4 npositioned=5
  box[0] bid=0 x=0.0 top=0.0 w=952.0 h=204.7
  pos[0] box=1 z=0 x=176.0 y=204.7 w=600.0 h=0.0
  pos[1] box=2 z=1 x=216.0 y=244.7 w=160.0 h=19.0
```

Add `--author-css` so the box tree is populated. Headless diagnostic with no
display required.

## Address Bar, Search & Keyboard Shortcuts

The address bar works as an **omnibox**:

- `example.com` — opens `https://example.com` (scheme added; bare host recognised)
- `http://site` — upgraded to https (Secure by Default)
- `best linux distro` (or anything non-URL) — DuckDuckGo HTML search
- `duckduckgo.com/?q=...` (JS SPA) — transparently routed to the no-JS HTML
  results endpoint. Reload and Back re-apply the route.
- `javascript:...` / `file:...` / `data:...` — searched as text, never executed
- An existing local path opens from disk with a `file://` origin and acts like
  https for resolution (relative links confined to the document's directory)

### JavaScript policy (per-domain allowlist)

Page JavaScript is **off by default**. A global tri-state mode controls it:

- `off` — never run page JS
- `allowlist` (default) — run JS only for hosts listed in `js.conf`
- `on` — run JS for every host (least safe; explicit opt-in)

When JS is enabled, inline scripts execute inside the per-tab sandbox against a
memory-safe writable DOM. A standard `document` facade exposes reads, writes,
DOM construction, events/timers, and `innerHTML`. `localStorage`/`sessionStorage`
are in-memory and ephemeral. `document.cookie` is empty for untrusted sites;
trusted hosts get a real in-memory session cookie jar (gone when you close
Freedom).

`querySelector`/`querySelectorAll` and `element.matches`/`closest` run through
the same CSS selector engine the stylesheets use. External `<script src>` scripts
run for doubly-trusted hosts — the sandboxed worker never touches a socket;
script bytes are requested from the trusted parent under full network policy.

**`defer` scripts** are collected during parsing and executed in a second pass
after all sync scripts, before `DOMContentLoaded` handlers.

### Anti-fingerprinting identity

Every request carries a normalized, low-entropy `User-Agent` and `Accept-Language`
shared by all Freedom users — a common Firefox-on-Linux identity that matches
`navigator.userAgent`. You can override the User-Agent per session in the menu.

### Keyboard shortcuts

| Shortcut | Action |
| :-- | :-- |
| `Enter` / `Go` | Open the address, or search if it is not a URL |
| `Ctrl+L` | Focus the URL bar |
| `Ctrl+I` | Toggle remote images (off by default) |
| `Ctrl+D` | Distraction-free (reader) mode |
| `Ctrl+P` | Save current page as vector PDF |
| `Ctrl+Shift+P` | Save current page as PNG image |
| `Ctrl+S` | Save current page to `~/Downloads/freedom/` |
| `Ctrl+R` / `F5` | Reload the current page |
| `Ctrl++` / `Ctrl+-` / `Ctrl+0` | Zoom in / out / reset |
| `Ctrl+C` / `Ctrl+X` / `Ctrl+V` | Copy / cut / paste |
| `Ctrl+B` | Bookmark the current page (toggle) |
| `Ctrl+T` / `Ctrl+W` / `Ctrl+Tab` | New tab / close tab / next tab |
| `Ctrl+Shift+B` | Add current host to `block.conf` |
| `Ctrl+Shift+A` | Add current host to `allow.conf` |
| `Ctrl+Shift+J` | Add current host to `js.conf` |
| `Ctrl+Shift+E` | Per-host TLS exception (this session) |
| `j` / `k` | Scroll one line down / up |
| `Space` / `b` | Scroll one page down / up |
| `gg` / `G` | Jump to top / bottom |
| `F12` | Open/close Freebug developer console |
| `Ctrl+Enter` | Run code in Freebug REPL editor |

### Downloads & zoom

Non-renderable resources are saved to `~/Downloads/freedom/`. Filenames are
derived fail-closed from hostile input (only `[A-Za-z0-9._-]` survive, no `..`
traversal). Files are written atomically with `0600` permissions, size-capped
at 256 MiB.

Zoom snaps to a 50-300% ladder. `Ctrl+0` resets to 100%. The page reflows at
the new size with no network round-trip.

### Author CSS & distraction-free reading

Enable **Author styles (CSS)** in the menu to see the page the way the webmaster
intended. Freedom renders the author's own CSS — external sheets, `<style>` blocks,
and inline `style=` — using a deliberately safe subset: `color`, `background`,
`text-align`, `font-size`, `line-height`, `font-weight`, `font-style`,
`text-decoration`, `display`, with type / `.class` / `#id` / `*` / group
selectors, descendant (`A B`) and child (`A > B`) combinators, sibling
combinators (`+`/`~`), attribute selectors (`[attr=v]` with operators `^=`/
`$=`/`*=`/`~=`/`|=` and case flag `i`), pseudo-classes (`:link`, `:root`,
`:first-child`, `:nth-child(An+B)`, `:nth-of-type`, `:first-of-type`, `:empty`,
`:lang()`, `:checked`, `:disabled`, `:enabled`, `:not()`, `:is()`, `:where()`,
`::before`/`::after`), `!important`, and a real specificity-then-document-order
cascade.

Flex and grid containers (`display:flex`/`display:grid`) take their layout
parameters from the same cascade, so `<style>` rules lay out columns — not only
inline `style=`. Layout is structure (always on); author colors stay gated by
the toggle.

CSS is hostile content, so the parser **never phones home**: any value
containing `url(` and network/font `@`-rules (`@import`/`@font-face`) are
dropped. `@media` can only choose which local rules apply. `var()`/custom
properties and `calc()`/`min()`/`max()`/`clamp()` are evaluated as bounded
text substitution and arithmetic — never code, never a fetch.

**Distraction-free mode** (`Ctrl+D`) is a clean reading view: boilerplate
elements (`nav`/`header`/`footer`/`aside`) are dropped, author styling and
images are turned off, and the text is centered in a comfortable reading column.

## Privacy Networking: Tor, I2P & Host Filtering

Freedom integrates Tor and I2P **at the socket level** (it routes through a local
proxy you run; it never embeds the Tor/I2P daemon). The routing brain is the pure,
tested `net_realm` module, which guarantees:

- **Realm isolation**: a `.onion` address only ever exits through Tor, a `.i2p`
  only through I2P.
- **Fail-closed**: if a realm's proxy is not enabled, the request is **blocked**,
  never leaked over the clearnet.

### Tor (`.onion`)

```bash
sudo systemctl start tor      # Tor SOCKS5 proxy on 127.0.0.1:9050
./build/freedom --tor https://<address>.onion/        # headless
# GUI: hamburger menu -> enable "Tor routing (.onion)", then reload
```

Use `--torify` (or `FREEDOM_TORIFY_CLEARNET=1`) to route clearnet sites through
Tor too.

### I2P (`.i2p`)

```bash
sudo systemctl start i2pd     # or: i2prouter start   (Java router)
                              # HTTP proxy on 127.0.0.1:4444
./build/freedom --i2p http://stats.i2p/               # headless
# GUI: hamburger menu -> enable "I2P routing (.i2p)", then reload
```

I2P eepsites are served over http — Freedom allows plain http **only** for
`.i2p`, where the I2P layer already encrypts and authenticates by destination.

### Host filtering & the sovereignty allowlist

A pure `hostblock` module reads `block.conf` (blocklist) and `allow.conf`
(allowlist) in `/etc/hosts` format from `$FREEDOM_HOSTS_DIR`,
`~/.config/freedom`, or `./config`. Sample files ship in `config/`.

The allowlist is also your **sovereignty override**: a host listed there may be
navigated even when it falls below Freedom's elevated TLS standard (TLS 1.2,
classical key exchange, weak-but-valid certificate — with a warning). This is
how TLS-1.2-only sites such as **Hacker News** load. The certificate chain is
still authenticated; you are sovereign over your own hosts.

## Fuzzing

```bash
# 10 Cycles | 700 Paths | 0 Crashes | 0 Hangs | 74.91% Stability
./fuzz.sh
```

## Docker

Freedom is fully compatible with Docker:

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

This repository includes an MCP (Model Context Protocol) server (`app.py`) that
allows AI agents and LLM bridges to interact with the fuzzing environment.

### Exposed Tools
* `read_fuzz_stats`: Reads real-time performance metrics from the active AFL++
  session.
* `list_unique_crashes`: Lists all unique payloads that triggered a browser crash.
* `run_freedom_headless`: Executes `./build/freedom --headless <payload_path>` to
  triage specific inputs.

### Usage

```bash
pip install -r requirements.txt
```

Configure your MCP client or agent routing table to invoke the server via stdio:

```bash
# Do not run interactively; meant for stdio communication via MCP host config
python3 app.py
```

## Project Structure

```text
Freedom/
├── src/           # Core source code (one .c per module)
├── gui/           # Wayland + Cairo GUI implementation
├── include/       # Public headers (module contracts)
├── spec/          # SDD specifications (one spec per module)
├── config/        # Sample host filter lists (block.conf / allow.conf)
├── examples/      # Sample pages
├── third_party/   # Vendored libraries (Lexbor, QuickJS-ng, etc.)
├── tests/         # Unit (CMocka) and integration tests
├── fuzz/          # Fuzzing harnesses
├── docs/          # Documentation
└── Makefile       # Build system
```

See [CONTRIBUTING.md](CONTRIBUTING.md) for details.

## CI/CD

- **Automated CI/CD Pipeline:** every commit triggers a headless GitHub Actions
  workflow that fuzzes code, runs unit tests via CMocka, and validates builds.
- **Standard Toolchain (`./configure && make`):** traditional low-dependency
  build workflow with built-in patches for OpenSSL compatibility.
- **Deterministic Sandbox (Docker):** bundles a secure Xvfb + noVNC + Weston
  stack inside a non-root container, stripping Linux capabilities.

## Security

- Zero Trust architecture
- Strong sandboxing at OS and language level
- Minimal dependencies
- Hardened compiler flags
- Regular fuzzing and code auditing

See [SECURITY.md](SECURITY.md) for reporting vulnerabilities.

## Development

This project is written in pure C11 and is security-hardened by default using
stack protection, control-flow protection (`-fcf-protection`), and PIE.

### Prerequisites

```bash
sudo apt install liblexbor-dev libcmocka-dev libcurl4-openssl-dev libwayland-dev \
  wayland-protocols libcairo2-dev libfontconfig-dev libfreetype6-dev \
  libharfbuzz-dev libxkbcommon-dev pkg-config clang
```

### Available Targets

```bash
make              # Compile the main binary at build/freedom
sudo make install # Install globally into /usr/local/bin/
make test         # Run CMocka unit test suites
make itest        # Run network-dependent integration tests (live PQ key exchange)
make asan         # Run all suites under AddressSanitizer + UBSan
make fuzz         # 30-second libFuzzer session on the HTML parser
make fuzz-js      # 30-second libFuzzer session on the JS sandbox
make fuzz-css     # Fuzz the author-CSS parser + cascade
make fuzz-pv      # Fuzz the display-list builder
make fuzz-img     # Fuzz the PNG+JPEG+WebP+GIF decoder
make view         # Compile the standalone Wayland + Cairo GUI demo
make clean        # Wipe the build directory
make all          # Build the whole proyect
make deb          # Build debian deb package
```

## Screenshots

### Tor working on dark mode

<img width="921" height="718" alt="screenshot" src="https://github.com/user-attachments/assets/e6b9ef46-f75a-47a6-a1f0-98074b7fd424" />

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

This project is licensed under the **AGPL-3.0** license - see the
[LICENSE](LICENSE) file for details.

<img width="300" height="124" alt="logo" src="https://github.com/user-attachments/assets/db766969-44c2-4466-9529-5aef9908bdc8" />

---

For more information, visit the [GitHub repository](https://github.com/grisuno/FreeDom).

![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54) ![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white) [![License: AGPL v3](https://img.shields.io/badge/License-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Y8Y2Z73AV)
