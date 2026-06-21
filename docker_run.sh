#!/usr/bin/env bash
# Thin wrapper. The docker build/run lives in the Makefile (single source of truth).
exec make docker "$@"
