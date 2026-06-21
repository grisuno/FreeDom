# FreeDom

<img width="1922" height="825" alt="image" src="https://github.com/user-attachments/assets/6b049cfb-3253-469f-9547-3c88ba67c23a" />

From the creators of LazyOwn Redteam Framework comes a free and open-source minimal web browser written in C, focused on Zero Trust and Zero Knowledge principles.

## Quick Start (Recommended)

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
- Strong process-based sandboxing for each tab
- JavaScript sandbox using QuickJS-ng
- Hardened build with stack protection, PIE, RELRO, and FORTIFY_SOURCE
- Wayland + Cairo GUI backend with Client-Side Decorations (CSD)
- Lexbor HTML parser and renderer
- Strict request policy using Public Suffix List + blacklist/whitelist for TLS 1.2 compatibility
- Post-quantum hybrid cryptography support (X25519MLKEM768)
- Headless mode for automation and testing
- Anti-fingerprinting techniques
- Comprehensive test suite, fuzzing, and integration tests

### New Features & Improvements (Latest)
- **Advanced Layout Engine**:
  - Full box model per HTML tag (margins, padding, display, border)
  - Flexbox 1D layout support (`flex-grow`, `flex-shrink`, `gap`, `justify-content`)
  - Basic CSS Grid support (`repeat(n, 1fr)`)
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
- ✅ Clickable links + basic image support (PNG)
- ✅ Anti-fingerprinting network identity (normalized User-Agent + Accept-Language)
- ✅ Omnibox address bar (navigate or DuckDuckGo HTML search)
- ✅ Native forms (GET/POST, no JS)
- ✅ Save page as vector PDF (`Ctrl+P`)
- ✅ Headless mode
- ✅ Strong per-tab sandboxing
- ✅ Docker + noVNC
- ✅ Modern GUI: scrollbar, vim shortcuts, window management, themes (including sepia/night), hover previews
- ✅ Tor & I2P routing (`.onion` / `.i2p` + torify)
- ✅ Tab shortcuts estilo Vim
- ✅ Simplified/distraction-free rendering mode
- ✅ Debian packaging
- ✅ Comprehensive CI/CD + fuzzing + MCP automation
- ⚠️ CSS support still limited (static + author-gated)
- ⚠️ JavaScript support remains basic
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
```

## Address Bar, Search & Keyboard Shortcuts

The address bar works like a real **omnibox**:

- **`example.com`** → opens `https://example.com` (the scheme is added; a bare host is recognised).
- **`http://site`** → **upgraded to https** (Secure by Default: a downgrade is never representable).
- **`best linux distro`** (or anything that is not a URL) → runs a **DuckDuckGo HTML** search (the
  no-JS endpoint, which renders cleanly in Freedom).
- **`javascript:...` / `file:...` / `data:...`** → searched as text, **never executed** (fail-closed).
- An existing **local path** (e.g. `examples/rich.html`) still opens from disk.

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
| `Ctrl+P` | Save the current page as a vector PDF (selectable text) |
| `Ctrl+C` / `Ctrl+V` | Copy the focused field or page URL / paste into the focused field |
| `Ctrl+T` / `Ctrl+W` / `Ctrl+Tab` | New tab / close tab / next tab |
| `Ctrl+Shift+E` | Per-host exception for a weak-but-valid certificate (this session) |
| `j` / `k` | Scroll one line down / up (URL bar unfocused) |
| `Space` / `b` | Scroll one page down / up |
| `gg` / `G`, `Home` / `End` | Jump to top / bottom |

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
sudo apt install liblexbor-dev libcmocka-dev libcurl4-openssl-dev libwayland-dev wayland-protocols libcairo2-dev libfontconfig-dev libxkbcommon-dev pkg-config clang
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
