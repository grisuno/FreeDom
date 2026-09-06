# Subsystem: root

## app.py
- Layer: utility
- Doc: _*_ coding: utf8 _*_
- Language: py
- Symbols:
  - `read_fuzz_stats` (function, line 30) `def read_fuzz_stats()`
  - `list_unique_crashes` (function, line 39) `def list_unique_crashes()`
  - `run_freedom_headless` (function, line 47) `def run_freedom_headless(payload_path)`

## docker-entrypoint.sh
- Layer: utility
- Language: sh

## docker_run.sh
- Layer: utility
- Doc: Thin wrapper. The docker build/run lives in the Makefile (single source of truth).
- Language: sh

## fuzz.sh
- Layer: utility
- Doc: Thin wrapper. The fuzz build/run logic now lives in the Makefile (single source of truth), so it can never drift from th
- Language: sh

## install.sh
- Layer: utility
- Doc: Exit immediately if a command exits with a non-zero status, if an undefined variable is used, or if any pipe fails.
- Language: sh

## run_freedom.sh
- Layer: utility
- Doc: Thin wrapper. Launches a nested weston (for boxes without a Wayland session), then runs the browser through the Makefile
- Language: sh
