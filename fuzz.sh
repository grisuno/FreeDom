# 1. Asegurar estructura limpia
mkdir -p build

# 2. Configurar variables de compilación de AFL++
export CC=afl-clang-fast
export CXX=afl-clang-fast++

# 3. GENERAR ARCHIVOS DINÁMICOS (Paso crítico que faltaba)
# Generar la Public Suffix List
$CC -std=c11 -O2 -o build/gen_psl tools/gen_psl.c
build/gen_psl third_party/psl/public_suffix_list.dat > build/psl_data.c

# Generar los bindings de Wayland / XDG Protocols
wayland-scanner private-code /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml build/xdg-shell-protocol.c
wayland-scanner private-code /usr/share/wayland-protocols/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml build/xdg-decoration-protocol.c
wayland-scanner client-header /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml build/xdg-shell-client-protocol.h
wayland-scanner client-header /usr/share/wayland-protocols/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml build/xdg-decoration-client-protocol.h

# 4. COMPILAR TODO EL CORE E INFRAESTRUCTURA (Con banderas de inclusión correctas para Wayland)
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/tab.c -o build/tab.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/os_sandbox.c -o build/os_sandbox.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/html_parse.c -o build/html_parse.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/dom.c -o build/dom.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -isystem third_party/quickjs -c src/js_sandbox.c -o build/js_sandbox.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -isystem third_party/quickjs -c src/js_dom.c -o build/js_dom.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -isystem third_party/quickjs -c src/js_env.c -o build/js_env.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/anti_fp.c -o build/anti_fp.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/page_view.c -o build/page_view.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/secure_fetch.c -o build/secure_fetch.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/url.c -o build/url.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/link_nav.c -o build/link_nav.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/css_color.c -o build/css_color.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/request_policy.c -o build/request_policy.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/render_doc.c -o build/render_doc.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/render_policy.c -o build/render_policy.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/textfield.c -o build/textfield.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/form.c -o build/form.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c build/psl_data.c -o build/psl_data.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/browser.c -o build/browser.o
$CC -std=c11 -O2 -Iinclude -I/usr/local/include -c src/ui_layout.c -o build/ui_layout.o

# Compilar QuickJS
$CC -std=c11 -O2 -D_GNU_SOURCE -w -Ithird_party/quickjs -c third_party/quickjs/quickjs.c -o build/qjs_quickjs.o
$CC -std=c11 -O2 -D_GNU_SOURCE -w -Ithird_party/quickjs -c third_party/quickjs/libregexp.c -o build/qjs_libregexp.o
$CC -std=c11 -O2 -D_GNU_SOURCE -w -Ithird_party/quickjs -c third_party/quickjs/libunicode.c -o build/qjs_libunicode.o
$CC -std=c11 -O2 -D_GNU_SOURCE -w -Ithird_party/quickjs -c third_party/quickjs/dtoa.c -o build/qjs_dtoa.o

# Compilar código fuente principal, UI y protocolos dinámicos
$CC -std=c11 -O2 -Iinclude -Ibuild -I/usr/include/cairo -c src/freedom.c -o build/freedom.o
$CC -std=c11 -O2 -Iinclude -Ibuild -I/usr/include/cairo -c gui/browser_ui.c -o build/browser_ui.o
$CC -std=c11 -O2 -Iinclude -Ibuild -I/usr/include/cairo -c build/xdg-shell-protocol.c -o build/xdg-shell-protocol.o
$CC -std=c11 -O2 -Iinclude -Ibuild -I/usr/include/cairo -c build/xdg-decoration-protocol.c -o build/xdg-decoration-protocol.o

# 5. ENLAZADO FINAL ATÓMICO (Todos los objetos están garantizados en build/)
$CC build/*.o -o build/freedom \
  -pie -Wl,-z,relro,-z,now,-z,noexecstack \
  -lcurl -lssl -lcrypto -lm -lpthread -L/usr/local/lib -llexbor \
  -lwayland-cursor -lwayland-client -lcairo -lfontconfig -lfreetype -lxkbcommon
afl-fuzz -i fuzz/in -o fuzz/out -- ./build/freedom --headless @@
