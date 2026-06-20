# FreeDom

<img width="1922" height="825" alt="image" src="https://github.com/user-attachments/assets/6b049cfb-3253-469f-9547-3c88ba67c23a" />

A free and open-source minimal web browser written in C, focused on Zero Trust and Zero Knowledge principles.

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

### New Features & Improvements

- **Advanced Layout Engine**:
  - Full box model per HTML tag (margins, padding, display, border)
  - Flexbox 1D layout support (`flex-grow`, `flex-shrink`, `gap`, `justify-content`)
  - Basic CSS Grid support (`repeat(n, 1fr)`)
  - Recursive box-tree layout with margin collapsing
- **GUI & Usability**:
  - Visible vertical scrollbar with drag and click support
  - Vim-style keyboard navigation (`j`/`k`, `space`/`b`, `gg`/`G`, etc.)
  - Window controls: maximize, minimize, edge resize, titlebar drag
  - Sepia reading mode + Light/Dark themes with "Force theme colors" toggle
  - Dark mode + Dark theme with "Force theme colors" toggle
  - Hover link preview (shows destination URL)
  - Loading indicator (busy clock)
  - Improved dark mode and typography
- **Privacy & Networking**:
  - **Tor support** (`.onion` routing via SOCKS5h proxy, remote DNS = no leak)
  - **I2P support** (`.i2p` routing via HTTP proxy, plain-http eepsites allowed)
  - Clearnet Torification option (`--torify`)
  - Realm-based routing (`net_realm`) with **fail-closed** policy (no de-anonymizing fallback)
  - **Host filtering** (`hostblock`): `/etc/hosts`-format `block.conf` + `allow.conf`, allowlist
    wins and covers subdomains
  - **Sovereignty allowlist**: per-host override to navigate sites below FreeDom's TLS standard
    (e.g. TLS-1.2-only sites like Hacker News) while still authenticating the certificate chain
  - Post-quantum hybrid KE by default with a non-blocking classical-TLS-1.3 fallback
  - Enhanced secure fetch
- **Build & Distribution**:
  - Debian `.deb` packaging (`build_deb.sh`)
  - Improved `./configure`, `install.sh` and Makefile
- **Automation**:
  - Full GitHub Actions CI/CD pipeline
  - MCP (Model Context Protocol) server for AI agent integration

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



## License

This project is licensed under the **AGPL-3.0** license - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome. Please read [CONTRIBUTING.md](CONTRIBUTING.md) first.

## Roadmap

- Complete GUI implementation
- Full CSS support
- Improved networking and caching
- Extension system (future)
- More platform support (Linux first, others later)

---

## Current Status (Updated - June 2026)

- ✅ Advanced HTML rendering with box model and flex/grid layout
- ✅ Clickable links and basic image support (PNG)
- ✅ Headless mode
- ✅ Strong process-based sandboxing per tab
- ✅ Docker + noVNC environment
- ✅ User-Agent customization & anti-fingerprinting
- ✅ Modern GUI with scrollbar, vim shortcuts, window management, themes and sepia mode
- ✅ Tor & I2P routing support (`.onion` / `.i2p` + torify), socket-level, fail-closed
- ✅ Host filtering (block/allow lists) + per-host sovereignty TLS override
- ✅ Debian packaging
- ✅ Comprehensive CI/CD + fuzzing + MCP agentic automation
- ⚠️ CSS support still limited (static + author-gated)
- ⚠️ JavaScript support remains basic
- ⚠️ Full networking/caching layer in active development

**Status**: progressing Alpha — focus on secure, testable rendering engine and usable GUI.



For more information, visit the [GitHub repository](https://github.com/grisuno/FreeDom).

![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54) ![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white) [![License: AGPL v3](https://img.shields.io/badge/License-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Y8Y2Z73AV)
