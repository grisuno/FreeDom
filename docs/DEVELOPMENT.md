# Freedom — Development

[Back to README](../README.md)

## Fuzzing

```bash
# 10 Cycles | 700 Paths | 0 Crashes | 0 Hangs | 74.91% Stability
./fuzz.sh
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

See [CONTRIBUTING.md](../CONTRIBUTING.md) for details.

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

See [SECURITY.md](../SECURITY.md) for reporting vulnerabilities.

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
make fuzz-svg     # Fuzz the inline-SVG parser (geometry + pool bounds)
make parity       # Score structural divergence vs Firefox over the page corpus
make parity-update # Freeze current parity scores as the baseline
make layout-diff  # Fail on any default-layout change over examples/
make layout-update # Re-freeze the layout baseline (justified diffs only)
make drops        # Fail on any new author-CSS parser discard over the corpus
make drops-update # Re-freeze the drops baseline (justified diffs only)
make wpt          # Score the vendored WPT static-reftest subset vs Firefox
make view         # Compile the standalone Wayland + Cairo GUI demo
make clean        # Wipe the build directory
make all          # Build the whole proyect
make deb          # Build debian deb package
```

## Screenshots

### Tor working on dark mode

<img width="921" height="718" alt="screenshot" src="https://github.com/user-attachments/assets/e6b9ef46-f75a-47a6-a1f0-98074b7fd424" />

