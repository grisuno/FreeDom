#!/usr/bin/env bash
set -euo pipefail

echo "[*] Starting FreeDom Zero-Trust Isolation Layer..."

# 1. Configurar el directorio mandatorio para Wayland/Weston (XDG_RUNTIME_DIR)
export XDG_RUNTIME_DIR=/tmp/runtime-freedom
mkdir -p "$XDG_RUNTIME_DIR"
chmod 700 "$XDG_RUNTIME_DIR"

# 2. Inicializar la pantalla virtual Xvfb en el display :1
Xvfb :1 -screen 0 1024x768x24 &
export DISPLAY=:1

# Esperar a que el servidor Xvfb esté listo
sleep 1

# 3. Iniciar el gestor de ventanas mínimo
openbox &

# 4. Forzar a x11vnc a mirar SOLO a X11 deshabilitando explícitamente Wayland en su entorno
# También usamos -display :1 de forma directa para evitar que intente auto-detectar
env -u WAYLAND_DISPLAY x11vnc -forever -shared -nopw -listen localhost -display :1 &

# 5. Levantar Weston (entorno Wayland) mapeado sobre nuestro X11 virtual
weston --backend=x11-backend.so --width=1024 --height=768 &
export WAYLAND_DISPLAY=wayland-1

# Esperar a que el socket de Wayland se cree en XDG_RUNTIME_DIR
sleep 2

# 6. Exponer el buffer virtual de Xvfb mediante WebSockets (noVNC)
websockify --web=/usr/share/novnc/ 8080 localhost:5900 &

echo "[+] Sandbox environment ready. Access FreeDom at: http://localhost:8080/vnc.html"
echo "[*] Launching FreeDom browser process..."

# 7. Ejecutar FreeDom apuntando al socket gráfico de Wayland generado por Weston
exec ./build/freedom