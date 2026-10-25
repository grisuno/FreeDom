# Freedom — Usage Guide

[Back to README](../README.md)

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

### Inspecting a page without a window: `--dump-pane`

The Freebug window has Console / HTML / CSS / Script / Net tabs; `--dump-pane=TAB[:ARG]` prints the same
panel headlessly (it runs the very expression the window runs; add `--as-gui` so the host gets the
capabilities `allow.conf`/`js.conf` grant it):

```
./build/freedom --as-gui --dump-pane=html:'#main' page.html   # DOM outline of #main
./build/freedom --as-gui --dump-pane=css:'.btn'   page.html   # matching rules (winner first, ~ = overridden), computed, box
./build/freedom --as-gui --dump-pane=script       page.html   # the <script> list
./build/freedom --as-gui --dump-pane=script:2     page.html   # script #2 with numbered lines
./build/freedom --as-gui --dump-pane=net:api      page.html   # XHR/fetch requests whose URL contains "api"
```

The argument is only ever data (a selector, a number, a URL filter, at most 256 bytes); it is never spliced
into the script as code. There is no breakpoint debugger and no network timing yet.

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

### Seeing video layout 

Shows the rectangles the video engine actually reproduced the video 

```bash
VID=$(./build/freedom --js=on --dump-video-url "https://jkanime.net/dragon-ball-z/01/" 2>/dev/null | grep "\.m3u8" | tail -1)
./build/freedom --dump-video=- "$VID" 2>/dev/null | ffplay -i pipe:0 2>/dev/null

```

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
| `Alt+Enter` | Toggle fullscreen (video fills viewport when playing) |
| `Escape` | Exit fullscreen (when in fullscreen mode) |
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

## Video Debugging: `--dump-video`

Freedom can download and save video streams from HLS (.m3u8) or progressive
(MP4/WebM) URLs, bypassing the GUI for testing.

```bash
# Extract the video URL from a page (the actual .m3u8 from the video pipeline)
VID=$(./build/freedom --js=on --dump-video-url "https://site.com/episode" 2>/dev/null | grep "\.m3u8" | tail -1)

# Save to file:
./build/freedom --insecure --dump-video=output.ts "$VID"

# Pipe directly to ffplay for live testing:
./build/freedom --insecure --dump-video=- "$VID" 2>/dev/null | ffplay -i pipe:0 2>/dev/null

# Or concatenate all HLS segments and pipe:
./build/freedom --insecure --dump-video=- "https://cdn.example.com/stream.m3u8" 2>/dev/null | ffplay -i pipe:0 2>/dev/null
```

If the server does not support PQ-hybrid key exchange, add `--insecure` to fall
back to classical TLS. The tool respects `--tor`, `--i2p`, `--torify`, and
`--user=username:password`.

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

