#!/usr/bin/env python3
# _*_ coding: utf8 _*_
"""
app.py

Autor: Gris Iscomeback
Correo electrónico: grisiscomeback[at]gmail[dot]com
Fecha de creación: xx/xx/xxxx
Licencia: GPL v3

Descripción:  
"""
# app.py - Servidor MCP para monitoreo de Fuzzing
import os
import subprocess
from mcp.server.fastmcp import FastMCP
import logging
import sys

# Forzar a que todo el logging use stderr, dejando stdout limpio para JSON-RPC
logging.basicConfig(
    level=logging.INFO,
    stream=sys.stderr,
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s"
)
app = FastMCP("Freedom-Fuzz-Monitor")

@app.tool()
def read_fuzz_stats() -> str:
    """Lee el archivo de estado actual de la sesión de AFL++."""
    stats_path = "fuzz/out/default/fuzzer_stats"
    if not os.path.exists(stats_path):
        return "La sesión de fuzzing no ha generado estadísticas aún."
    with open(stats_path, "r") as f:
        return f.read()

@app.tool()
def list_unique_crashes() -> list:
    """Lista los archivos que han causado un crash real en el navegador."""
    crash_dir = "fuzz/out/default/crashes"
    if not os.path.exists(crash_dir):
        return []
    return [f for f in os.listdir(crash_dir) if f != "README.txt"]

if __name__ == "__main__":
    app.run(transport="stdio")