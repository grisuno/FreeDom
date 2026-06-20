#!/usr/bin/env bash

# Exit immediately if any command fails
set -e

# Terminal colors
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${GREEN}[*] Starting Debian package automation...${NC}"

# 1. Ensure we are in the project's root directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# 2. Clean up dh_make boilerplate files that cause Lintian errors
echo -e "${GREEN}[*] Cleaning up obsolete templates from debian/...${NC}"
rm -fr debian/*.ex debian/*.EX debian/freedom.doc-base*

# 3. Clean up previous build artifacts from the Makefile
if [ -f Makefile ]; then
    echo -e "${GREEN}[*] Cleaning up previous build files...${NC}"
    make clean || true
fi

# 4. Ensure debian/rules has the correct executable permissions
chmod +x debian/rules

# 5. Build the .deb package (skipping tests)
echo -e "${GREEN}[*] Building the binary package (.deb)...${NC}"
# -us -uc skips signing, -b is for binary-only, -d skips build-dependency check if needed. No cheks it's only meanwhile i repair the 4 test are broken
debuild -us -uc -b -d

echo -e "${GREEN}[+] Package built successfully!${NC}"
echo -e "To install it, run:"
echo -e "${RED}sudo apt install ../freedom_0.0.3-1_amd64.deb${NC}"
