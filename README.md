# FreeDom

<img width="927" height="723" alt="image" src="https://github.com/user-attachments/assets/988635c4-146d-4077-8182-fe7dafd69868" />

A free and open-source minimal web browser written in C, focused on Zero Trust and Zero Knowledge principles.

## Philosophy

FreeDom (Free + DOM) is a lightweight, security-first web browser built from the ground up in modern C. It prioritizes user privacy, strong isolation, and minimal attack surface over feature bloat.

The name reflects its core goals:
- **Free**: Libre (freedom) and open source
- **Dom**: Reference to the DOM (Document Object Model) and domain-level control

## Features

- Written in portable C11
- Strong process-based sandboxing for each tab
- JavaScript sandbox using QuickJS-ng
- Hardened build with stack protection, PIE, RELRO, and FORTIFY_SOURCE
- Wayland + Cairo GUI backend
- Lexbor HTML parser and renderer
- Strict request policy using Public Suffix List
- Post-quantum hybrid cryptography support (X25519MLKEM768)
- Headless mode for automation and testing
- Anti-fingerprinting techniques
- Comprehensive test suite, fuzzing, and integration tests

## Building

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
## Fuzzing

```bash
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
python3 app.py
```

## Project Structure

```text
FreeDom/
├── src/           # Core source code
├── gui/           # Wayland + Cairo GUI implementation
├── include/       # Public headers
├── third_party/   # Vendored libraries (Lexbor, QuickJS-ng, etc.)
├── tests/         # Unit and integration tests
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

**Status**: Early development stage (Alpha)

For more information, visit the [GitHub repository](https://github.com/grisuno/FreeDom).

![Python](https://img.shields.io/badge/python-3670A0?style=for-the-badge&logo=python&logoColor=ffdd54) ![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white) ![Flask](https://img.shields.io/badge/flask-%23000.svg?style=for-the-badge&logo=flask&logoColor=white) [![License: AGPL v3](https://img.shields.io/badge/License-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Y8Y2Z73AV)
