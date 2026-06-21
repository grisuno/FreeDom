#!/usr/bin/env bash
# Thin wrapper. The .deb build lives in the Makefile (single source of truth) and
# also restores build/ ownership afterwards (debuild runs under fakeroot/sudo and
# would otherwise leave build/ root-owned).
exec make deb "$@"
