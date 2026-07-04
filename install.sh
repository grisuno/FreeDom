#!/usr/bin/env bash

# Exit immediately if a command exits with a non-zero status, 
# if an undefined variable is used, or if any pipe fails.
set -euo pipefail

# ANSI color codes for terminal output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}[*] Initializing installation environment...${NC}"

# 1. Verify OS environment and install base dependencies if on Debian/Ubuntu
if [ -f /etc/debian_version ]; then
    echo -e "${BLUE}[*] Debian/Ubuntu-based system detected. Installing package dependencies...${NC}"
    sudo apt-get update -y
    sudo apt-get install -y \
      build-essential \
      cmake \
      libcairo2-dev \
      libwayland-dev \
      wayland-protocols \
      libxkbcommon-dev \
      libcurl4-openssl-dev \
      libssl-dev \
      fontconfig \
      libfreetype6-dev \
      libcmocka-dev \
      git \
      libssl-dev \
      libpng-dev \
      wayland-protocols \
      libwayland-bin \
      weston \
      cage \
      liblexbor-dev \
      libcmocka-dev
else
    echo -e "${BLUE}[*] Non-Debian system detected. Please ensure build tools, OpenSSL, libcurl, CMake, and CMocka are installed manually.${NC}"
fi

# 2. Synchronize and update Git submodules if present
if [ -f .gitmodules ]; then
    echo -e "${BLUE}[*] Syncing Git submodules...${NC}"
    git submodule update --init --recursive
fi

# 3. Build and install Lexbor globally if not already present
if [ ! -d "/usr/local/include/lexbor" ]; then
    echo -e "${BLUE}[*] Lexbor headers not found globally. Cloning and compiling from source...${NC}"
    # Create a secure temporary directory to avoid cluttering the workspace
    BUILD_DIR=$(mktemp -d)
    cd "$BUILD_DIR"
    
    git clone --depth 1 https://github.com/lexbor/lexbor.git
    cd lexbor
    cmake -DLEXBOR_BUILD_SEPARATELY=OFF .
    make -j$(nproc)
    sudo make install
    sudo ldconfig
    
    # Return to the original workspace directory and clean up
    cd - > /dev/null
    rm -rf "$BUILD_DIR"
    echo -e "${GREEN}[+] Lexbor successfully installed.${NC}"
else
    echo -e "${GREEN}[+] Lexbor is already installed on the system.${NC}"
fi

# 4. Apply compatibility source patches for compilation
echo -e "${BLUE}[*] Preparing source files and applying environment patches...${NC}"

if [ -f src/local_store.c ]; then
    # Patch 2: Inject missing Argon2 macros if the host runs an OpenSSL version < 3.3
    sed -i '1s/^/#include <openssl\/kdf.h>\n#ifndef OSSL_KDF_PARAM_ARGON2_LANES\n#define OSSL_KDF_PARAM_ARGON2_LANES "lanes"\n#endif\n#ifndef OSSL_KDF_PARAM_ARGON2_MEMCOST\n#define OSSL_KDF_PARAM_ARGON2_MEMCOST "memcost"\n#endif\n#ifndef OSSL_KDF_PARAM_THREADS\n#define OSSL_KDF_PARAM_THREADS "threads"\n#endif\n#define _GNU_SOURCE\n/' src/local_store.c
fi

# 5. Export explicit search paths for headers and shared libraries
export CPATH="/usr/local/include:$CPATH"
export LIBRARY_PATH="/usr/local/lib:$LIBRARY_PATH"
export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"

# 6. Clean and compile the binaries
echo -e "${BLUE}[*] Compiling the project...${NC}"
make clean
make all

echo -e "${GREEN}[+] Installation and compilation completed successfully!${NC}"
echo -e "${BLUE}[*] To execute your unit tests, run: make test${NC}"
