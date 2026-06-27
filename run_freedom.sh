#!/usr/bin/env bash
# Thin wrapper. Launches a nested weston (for boxes without a Wayland session), then
# runs the browser through the Makefile (single source of truth for the build).
# Usage: ./run_freedom.sh [url]
set -euo pipefail
URL="${1:-https://grisuno.github.io/LazyOwn}"
weston --backend=x11-backend.so --renderer=gl --width=1024 --height=768 &
WESTON_PID=$!
sleep 0.5
WAYLAND_DISPLAY=wayland-1 make run URL="$URL"
kill "$WESTON_PID"
