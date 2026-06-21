#!/usr/bin/env bash
# Thin wrapper. The fuzz build/run logic now lives in the Makefile (single source of
# truth), so it can never drift from the real build the way this script used to.
#   make fuzz-afl   -> AFL++ over the full headless pipeline (this script)
#   make fuzz       -> libFuzzer over the HTML parser
#   make fuzz-pv    -> libFuzzer over the display-list builder (page_view)
#   make fuzz-js    -> libFuzzer over the JS sandbox
#   make fuzz-img   -> libFuzzer over the PNG decoder
exec make fuzz-afl "$@"
