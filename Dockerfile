FROM ubuntu:24.04

# Evitar prompts interactivos durante el despliegue
ENV DEBIAN_FRONTEND=noninteractive

# 1. Instalar dependencias del sistema, herramientas de compilación y el stack gráfico virtual
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libcairo2-dev \
    libwayland-dev \
    wayland-protocols \
    libxkbcommon-dev \
    libcurl4-openssl-dev \
    libssl-dev \
    fontconfig \
    libfreetype6-dev \
    libcmocka-dev \
    sudo \
    # Componentes para renderizado virtual e interfaz Web (Zero Trust display)
    xvfb \
    x11vnc \
    novnc \
    websockify \
    openbox \
    weston \
    && rm -rf /var/lib/apt/lists/*

# 2. Crear un usuario de ejecución sin privilegios (Crucial para limitar el radio de explosión)
RUN useradd -m -s /bin/bash freedomuser && \
    echo "freedomuser ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER freedomuser
WORKDIR /home/freedomuser/FreeDom

# 3. Copiar las fuentes del proyecto manteniendo los permisos correctos
COPY --chown=freedomuser:freedomuser . .

# 4. Asegurar permisos de ejecución en scripts de configuración locales
RUN chmod +x configure install.sh || true

# 5. Ejecutar la configuración de entorno y la compilación estricta de FreeDom
RUN ./configure && make clean && make all

# 6. Copiar y preparar el script de arranque del ecosistema aislado
COPY --chown=freedomuser:freedomuser docker-entrypoint.sh /home/freedomuser/docker-entrypoint.sh
RUN chmod +x /home/freedomuser/docker-entrypoint.sh

# Exponer el puerto del cliente web noVNC
EXPOSE 8080

ENTRYPOINT ["/home/freedomuser/docker-entrypoint.sh"]
