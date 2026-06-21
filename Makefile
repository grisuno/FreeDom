# Freedom — pure C11, security-hardened by default.
# Targets: all (build src), test (cmocka suites), itest (network closure of Hito 1),
#          asan (suites under ASan+UBSan), fuzz / fuzz-js (libFuzzer), clean.

CC        ?= cc
STD        = -std=c11
WARN       = -Wall -Wextra -Werror -Wshadow -Wpointer-arith -Wvla -Wwrite-strings
HARDEN     = -fstack-protector-strong -fstack-clash-protection -fcf-protection=full \
             -D_FORTIFY_SOURCE=3 -fPIE
OPT        = -O2
LDHARDEN   = -pie -Wl,-z,relro,-z,now,-z,noexecstack

LEXBOR_CFLAGS := $(shell pkg-config --cflags lexbor 2>/dev/null)
LEXBOR_LIBS   := $(shell pkg-config --libs lexbor 2>/dev/null || echo -llexbor)
CMOCKA_CFLAGS := $(shell pkg-config --cflags cmocka 2>/dev/null)
CMOCKA_LIBS   := $(shell pkg-config --libs cmocka 2>/dev/null || echo -lcmocka)

# image_decode (PNG only): libpng is already pulled in transitively by Cairo, so
# this adds no new transitive dependency. Decoding runs inside the confined worker.
PNG_CFLAGS    := $(shell pkg-config --cflags libpng 2>/dev/null)
PNG_LIBS      := $(shell pkg-config --libs libpng 2>/dev/null || echo -lpng16)

# UI (Hito 4+): Wayland + Cairo + xkbcommon for the browser GUI. fontconfig is
# linked explicitly so the GUI can call FcFini() at shutdown (clean leak exit).
WL_CFLAGS   := $(shell pkg-config --cflags wayland-client wayland-cursor cairo fontconfig xkbcommon 2>/dev/null)
WL_LIBS     := $(shell pkg-config --libs wayland-client wayland-cursor cairo fontconfig xkbcommon 2>/dev/null || echo -lwayland-client -lwayland-cursor -lcairo -lfontconfig -lxkbcommon)
WL_SCANNER  := wayland-scanner
WL_PROTODIR := $(shell pkg-config --variable=pkgdatadir wayland-protocols 2>/dev/null)
XDG_XML     := $(WL_PROTODIR)/stable/xdg-shell/xdg-shell.xml
DECO_XML    := $(WL_PROTODIR)/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml

CFLAGS    ?= $(STD) $(WARN) $(HARDEN) $(OPT) -Iinclude $(LEXBOR_CFLAGS)
LDFLAGS   ?= $(LDHARDEN)

# Per-module link dependencies.
SF_LIBS    = -lcurl -lssl -lcrypto
HP_LIBS    = $(LEXBOR_LIBS)
JS_LIBS    = -lm -lpthread
LS_LIBS    = -lcrypto

SRC_DIR    = src
TEST_DIR   = tests
FUZZ_DIR   = fuzz
GUI_DIR    = gui
BUILD_DIR  = build

# Vendored QuickJS-ng core (third_party/quickjs). Built with relaxed flags and
# isolated from the project's hardened build; quickjs-ng needs _GNU_SOURCE. The
# I/O surface (quickjs-libc) is deliberately not vendored. See its VERSION.md.
QJS_DIR    = third_party/quickjs
QJS_SRC   := $(QJS_DIR)/quickjs.c $(QJS_DIR)/libregexp.c $(QJS_DIR)/libunicode.c $(QJS_DIR)/dtoa.c
QJS_OBJ   := $(patsubst $(QJS_DIR)/%.c,$(BUILD_DIR)/qjs_%.o,$(QJS_SRC))
QJS_OPT   ?= -O2
QJS_SAN   ?=
QJS_CFLAGS = $(STD) $(QJS_OPT) -D_GNU_SOURCE -w -I$(QJS_DIR) $(QJS_SAN)

SOURCES   := $(wildcard $(SRC_DIR)/*.c)
OBJECTS   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Public Suffix List: vendored .dat -> generated sorted C table (no libpsl).
# request_policy links against psl_data.o. The table is rebuilt from the .dat.
PSL_DAT    = third_party/psl/public_suffix_list.dat
PSL_OBJ    = $(BUILD_DIR)/psl_data.o
TEST_BINS := $(BUILD_DIR)/test_secure_fetch $(BUILD_DIR)/test_html_parse \
             $(BUILD_DIR)/test_js_sandbox $(BUILD_DIR)/test_dom \
             $(BUILD_DIR)/test_js_dom $(BUILD_DIR)/test_os_sandbox \
             $(BUILD_DIR)/test_ui $(BUILD_DIR)/test_request_policy \
             $(BUILD_DIR)/test_anti_fp $(BUILD_DIR)/test_renderer \
             $(BUILD_DIR)/test_js_env $(BUILD_DIR)/test_local_store \
             $(BUILD_DIR)/test_disk_store $(BUILD_DIR)/test_tab \
             $(BUILD_DIR)/test_browser $(BUILD_DIR)/test_freedom \
             $(BUILD_DIR)/test_page_view $(BUILD_DIR)/test_render_policy \
             $(BUILD_DIR)/test_render_doc $(BUILD_DIR)/test_url \
             $(BUILD_DIR)/test_link_nav $(BUILD_DIR)/test_css_color \
             $(BUILD_DIR)/test_textfield $(BUILD_DIR)/test_form \
             $(BUILD_DIR)/test_image_decode $(BUILD_DIR)/test_box_style \
             $(BUILD_DIR)/test_flex_layout $(BUILD_DIR)/test_box_tree \
             $(BUILD_DIR)/test_hostblock $(BUILD_DIR)/test_net_realm

.PHONY: all install test itest asan fuzz fuzz-js fuzz-img fuzz-pv fuzz-afl \
        deps run deb docker view clean

all: $(BUILD_DIR)/freedom

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Public Suffix List table generation (build tool + generated source).
$(BUILD_DIR)/gen_psl: tools/gen_psl.c | $(BUILD_DIR)
	$(CC) $(STD) -O2 -o $@ $<

$(BUILD_DIR)/psl_data.c: $(BUILD_DIR)/gen_psl $(PSL_DAT) | $(BUILD_DIR)
	$(BUILD_DIR)/gen_psl $(PSL_DAT) > $@

$(PSL_OBJ): $(BUILD_DIR)/psl_data.c include/psl_data.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/request_policy.o: $(SRC_DIR)/request_policy.c include/psl_data.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# image_decode pulls in <png.h>; libpng's include dir is added explicitly.
$(BUILD_DIR)/image_decode.o: $(SRC_DIR)/image_decode.c include/image_decode.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(PNG_CFLAGS) -c $< -o $@

# js_sandbox / js_dom include the vendored quickjs.h: keep our code under the
# hardened flags, but pull the header via -isystem so its warnings do not trip
# -Werror.
$(BUILD_DIR)/js_sandbox.o: $(SRC_DIR)/js_sandbox.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -isystem $(QJS_DIR) -c $< -o $@

$(BUILD_DIR)/js_dom.o: $(SRC_DIR)/js_dom.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -isystem $(QJS_DIR) -c $< -o $@

$(BUILD_DIR)/js_env.o: $(SRC_DIR)/js_env.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -isystem $(QJS_DIR) -c $< -o $@

# Vendored QuickJS core objects (relaxed flags; sanitizer added under `asan`).
$(BUILD_DIR)/qjs_%.o: $(QJS_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(QJS_CFLAGS) -c $< -o $@

install: all
	@echo "[*] Installing binary and assets..."
	install -d /usr/local/bin
	install -m 0755 build/freedom /usr/local/bin/
	@echo "[+] Installation successful."

# Until the corresponding src/*.c exists, a test fails to link on purpose:
# that is the RED state of TDD.
test: $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do echo "== run $$t =="; $$t; done

$(BUILD_DIR)/test_secure_fetch: $(TEST_DIR)/test_secure_fetch.c $(BUILD_DIR)/secure_fetch.o $(BUILD_DIR)/url.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(SF_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_html_parse: $(TEST_DIR)/test_html_parse.c $(BUILD_DIR)/html_parse.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(HP_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_js_sandbox: $(TEST_DIR)/test_js_sandbox.c $(BUILD_DIR)/js_sandbox.o $(QJS_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(JS_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_dom: $(TEST_DIR)/test_dom.c $(BUILD_DIR)/dom.o $(BUILD_DIR)/html_parse.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(HP_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_page_view: $(TEST_DIR)/test_page_view.c $(BUILD_DIR)/page_view.o $(BUILD_DIR)/css_color.o $(BUILD_DIR)/box_style.o $(BUILD_DIR)/html_parse.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(HP_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_js_dom: $(TEST_DIR)/test_js_dom.c $(BUILD_DIR)/js_dom.o $(BUILD_DIR)/js_sandbox.o $(BUILD_DIR)/dom.o $(BUILD_DIR)/html_parse.o $(QJS_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) -isystem $(QJS_DIR) $^ -o $@ $(LDFLAGS) $(JS_LIBS) $(HP_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_os_sandbox: $(TEST_DIR)/test_os_sandbox.c $(BUILD_DIR)/os_sandbox.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure UI core only; the Wayland/Cairo orchestrator is built by `make view`.
$(BUILD_DIR)/test_ui: $(TEST_DIR)/test_ui.c $(BUILD_DIR)/ui_layout.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_request_policy: $(TEST_DIR)/test_request_policy.c $(BUILD_DIR)/request_policy.o $(PSL_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_anti_fp: $(TEST_DIR)/test_anti_fp.c $(BUILD_DIR)/anti_fp.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# render_policy reuses rp_evaluate, so it links request_policy.o + the PSL table.
$(BUILD_DIR)/test_render_policy: $(TEST_DIR)/test_render_policy.c $(BUILD_DIR)/render_policy.o $(BUILD_DIR)/request_policy.o $(PSL_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# render_doc builds the paint-ready model from a page_view + render_policy gate,
# so it links page_view/html_parse (lexbor) plus the render/request policy chain.
$(BUILD_DIR)/test_render_doc: $(TEST_DIR)/test_render_doc.c $(BUILD_DIR)/render_doc.o \
                              $(BUILD_DIR)/render_policy.o $(BUILD_DIR)/request_policy.o \
                              $(BUILD_DIR)/page_view.o $(BUILD_DIR)/css_color.o \
                              $(BUILD_DIR)/box_style.o \
                              $(BUILD_DIR)/html_parse.o $(BUILD_DIR)/url.o $(PSL_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(HP_LIBS) $(CMOCKA_LIBS)

# Pure URL operations: validation + RFC 3986 reference resolution. No I/O deps.
$(BUILD_DIR)/test_url: $(TEST_DIR)/test_url.c $(BUILD_DIR)/url.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Clicked-link navigation policy: reuses the pure url module, no I/O deps.
$(BUILD_DIR)/test_link_nav: $(TEST_DIR)/test_link_nav.c $(BUILD_DIR)/link_nav.o $(BUILD_DIR)/url.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure CSS color token parser. No I/O deps.
$(BUILD_DIR)/test_css_color: $(TEST_DIR)/test_css_color.c $(BUILD_DIR)/css_color.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure user-agent box model (per-tag margins/padding + display). No I/O deps.
$(BUILD_DIR)/test_box_style: $(TEST_DIR)/test_box_style.c $(BUILD_DIR)/box_style.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure flexbox/grid geometry solver. No I/O deps.
$(BUILD_DIR)/test_flex_layout: $(TEST_DIR)/test_flex_layout.c $(BUILD_DIR)/flex_layout.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure recursive block/flex/grid box-tree layout. Composes flex_layout. No I/O deps.
$(BUILD_DIR)/test_box_tree: $(TEST_DIR)/test_box_tree.c $(BUILD_DIR)/box_tree.o $(BUILD_DIR)/flex_layout.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure /etc/hosts-format host filter (blocklist + allowlist). No I/O deps.
$(BUILD_DIR)/test_hostblock: $(TEST_DIR)/test_hostblock.c $(BUILD_DIR)/hostblock.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure realm classifier + router (Tor/I2P/clearnet). No I/O deps.
$(BUILD_DIR)/test_net_realm: $(TEST_DIR)/test_net_realm.c $(BUILD_DIR)/net_realm.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# PNG decode (runs inside the confined worker). Links libpng only.
$(BUILD_DIR)/test_image_decode: $(TEST_DIR)/test_image_decode.c $(BUILD_DIR)/image_decode.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(PNG_CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(PNG_LIBS) $(CMOCKA_LIBS)

# Pure editable text-field primitive (UA field + form inputs). No I/O deps.
$(BUILD_DIR)/test_textfield: $(TEST_DIR)/test_textfield.c $(BUILD_DIR)/textfield.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Pure form-submission builder. Reuses the url module (resolution/validation).
$(BUILD_DIR)/test_form: $(TEST_DIR)/test_form.c $(BUILD_DIR)/form.o $(BUILD_DIR)/url.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_renderer: $(TEST_DIR)/test_renderer.c $(BUILD_DIR)/renderer.o $(BUILD_DIR)/os_sandbox.o $(BUILD_DIR)/html_parse.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(HP_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_js_env: $(TEST_DIR)/test_js_env.c $(BUILD_DIR)/js_env.o $(BUILD_DIR)/js_dom.o $(BUILD_DIR)/js_sandbox.o $(BUILD_DIR)/anti_fp.o $(BUILD_DIR)/dom.o $(BUILD_DIR)/html_parse.o $(QJS_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) -isystem $(QJS_DIR) $^ -o $@ $(LDFLAGS) $(JS_LIBS) $(HP_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_local_store: $(TEST_DIR)/test_local_store.c $(BUILD_DIR)/local_store.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(LS_LIBS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_disk_store: $(TEST_DIR)/test_disk_store.c $(BUILD_DIR)/disk_store.o $(BUILD_DIR)/local_store.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(LS_LIBS) $(CMOCKA_LIBS)

# Long-lived per-tab worker: links the whole hostile-content pipeline that runs
# inside the confined child (parse + DOM + JS sandbox + bindings) plus os_sandbox.
$(BUILD_DIR)/test_tab: $(TEST_DIR)/test_tab.c $(BUILD_DIR)/tab.o \
                       $(BUILD_DIR)/os_sandbox.o $(BUILD_DIR)/html_parse.o \
                       $(BUILD_DIR)/dom.o $(BUILD_DIR)/js_sandbox.o \
                       $(BUILD_DIR)/js_dom.o $(BUILD_DIR)/js_env.o \
                       $(BUILD_DIR)/anti_fp.o $(BUILD_DIR)/page_view.o \
                       $(BUILD_DIR)/css_color.o $(BUILD_DIR)/box_style.o \
                       $(BUILD_DIR)/image_decode.o \
                       $(QJS_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(JS_LIBS) $(HP_LIBS) $(PNG_LIBS) $(CMOCKA_LIBS)

# Freedom browser (Hito 5+): GUI by default, --headless for terminal output.
# Links the full secure tab pipeline plus the Wayland/Cairo/xkbcommon UI.
FREEDOM_UI_OBJ = $(BUILD_DIR)/browser.o $(BUILD_DIR)/ui_layout.o
FREEDOM_GUI_OBJ = $(GUI_DIR)/browser_ui.c \
                  $(BUILD_DIR)/xdg-shell-protocol.c \
                  $(BUILD_DIR)/xdg-decoration-protocol.c

$(BUILD_DIR)/freedom: $(SRC_DIR)/freedom.c $(BUILD_DIR)/tab.o \
                      $(BUILD_DIR)/os_sandbox.o $(BUILD_DIR)/html_parse.o \
                      $(BUILD_DIR)/dom.o $(BUILD_DIR)/js_sandbox.o \
                      $(BUILD_DIR)/js_dom.o $(BUILD_DIR)/js_env.o \
                      $(BUILD_DIR)/anti_fp.o $(BUILD_DIR)/page_view.o $(QJS_OBJ) \
                      $(BUILD_DIR)/secure_fetch.o $(BUILD_DIR)/url.o \
                      $(BUILD_DIR)/link_nav.o $(BUILD_DIR)/css_color.o \
                      $(BUILD_DIR)/request_policy.o \
                      $(BUILD_DIR)/render_doc.o $(BUILD_DIR)/render_policy.o \
                      $(BUILD_DIR)/box_style.o $(BUILD_DIR)/box_tree.o \
                      $(BUILD_DIR)/flex_layout.o $(BUILD_DIR)/hostblock.o \
                      $(BUILD_DIR)/net_realm.o \
                      $(BUILD_DIR)/textfield.o $(BUILD_DIR)/form.o \
                      $(BUILD_DIR)/image_decode.o \
                      $(PSL_OBJ) $(FREEDOM_UI_OBJ) $(FREEDOM_GUI_OBJ) \
                      $(BUILD_DIR)/xdg-shell-client-protocol.h \
                      $(BUILD_DIR)/xdg-decoration-client-protocol.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(BUILD_DIR) $(WL_CFLAGS) $^ -o $@ $(LDFLAGS) $(SF_LIBS) $(JS_LIBS) $(HP_LIBS) $(PNG_LIBS) $(WL_LIBS)

$(BUILD_DIR)/test_browser: $(TEST_DIR)/test_browser.c $(BUILD_DIR)/browser.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

$(BUILD_DIR)/test_freedom: $(TEST_DIR)/test_freedom.c $(BUILD_DIR)/freedom | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $< -o $@ $(LDFLAGS) $(CMOCKA_LIBS)

# Network-dependent closure of Hito 1: a live GET against an endpoint that
# negotiates the hybrid PQ key exchange (X25519MLKEM768). Not part of `make test`
# because it requires outbound network; run explicitly with `make itest`.
itest: $(BUILD_DIR)/itest_secure_fetch
	@echo "== run $< (network-dependent) =="; $<

$(BUILD_DIR)/itest_secure_fetch: $(TEST_DIR)/itest_secure_fetch.c $(BUILD_DIR)/secure_fetch.o $(BUILD_DIR)/url.o | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(SF_LIBS)

# Same suites under AddressSanitizer + UBSan (FORTIFY/PIE relaxed for the sanitizers).
# The vendored QuickJS objects are rebuilt with the sanitizer too (QJS_OPT/QJS_SAN).
asan: CFLAGS  := $(STD) $(WARN) -g -O1 -Iinclude $(LEXBOR_CFLAGS) -fsanitize=address,undefined -fno-omit-frame-pointer
asan: LDFLAGS := -fsanitize=address,undefined
asan: QJS_OPT := -O1 -g
asan: QJS_SAN := -fsanitize=address,undefined -fno-omit-frame-pointer
asan: clean $(TEST_BINS)
	@set -e; for t in $(TEST_BINS); do \
	  echo "== ASan $$t =="; \
	  LSAN_OPTIONS=suppressions=tests/asan.supp:detect_leaks=1 $$t; \
	done

# Coverage-guided fuzzing of the HTML parser (clang + libFuzzer).
fuzz: | $(BUILD_DIR)
	clang $(STD) -g -O1 -Iinclude $(LEXBOR_CFLAGS) \
	  -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer \
	  $(FUZZ_DIR)/fuzz_html_parse.c $(SRC_DIR)/html_parse.c -o $(BUILD_DIR)/fuzz_html_parse $(HP_LIBS)
	./$(BUILD_DIR)/fuzz_html_parse -max_total_time=30 -rss_limit_mb=2048

# Coverage-guided fuzzing of the JS sandbox (clang + libFuzzer). Arbitrary bytes
# as untrusted script must never crash/leak/UB the host.
fuzz-js: | $(BUILD_DIR)
	clang $(STD) -g -O1 -Iinclude -isystem $(QJS_DIR) -D_GNU_SOURCE \
	  -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer \
	  $(FUZZ_DIR)/fuzz_js_sandbox.c $(SRC_DIR)/js_sandbox.c $(QJS_SRC) \
	  -o $(BUILD_DIR)/fuzz_js_sandbox $(JS_LIBS)
	./$(BUILD_DIR)/fuzz_js_sandbox -max_total_time=30 -rss_limit_mb=2048

# Coverage-guided fuzzing of the PNG decoder (clang + libFuzzer). Hostile image
# bytes through sniff + dimensions + decode + free must never crash/leak/UB.
fuzz-img: | $(BUILD_DIR)
	clang $(STD) -g -O1 -Iinclude $(PNG_CFLAGS) \
	  -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer \
	  $(FUZZ_DIR)/fuzz_image_decode.c $(SRC_DIR)/image_decode.c \
	  -o $(BUILD_DIR)/fuzz_image_decode $(PNG_LIBS)
	./$(BUILD_DIR)/fuzz_image_decode -max_total_time=30 -rss_limit_mb=2048

# Coverage-guided fuzzing of the display-list builder (clang + libFuzzer). Arbitrary
# bytes -> DOM -> pv_build must never crash/leak/UB: covers the UTF-8/Windows-1252
# transcoder, inline emphasis, list markers and the table-to-grid cell collection.
fuzz-pv: | $(BUILD_DIR)
	clang $(STD) -g -O1 -Iinclude $(LEXBOR_CFLAGS) \
	  -fsanitize=fuzzer,address,undefined -fno-omit-frame-pointer \
	  $(FUZZ_DIR)/fuzz_page_view.c $(SRC_DIR)/page_view.c $(SRC_DIR)/css_color.c \
	  $(SRC_DIR)/box_style.c $(SRC_DIR)/html_parse.c \
	  -o $(BUILD_DIR)/fuzz_page_view $(HP_LIBS)
	./$(BUILD_DIR)/fuzz_page_view -max_total_time=30 -rss_limit_mb=2048 $(FUZZ_DIR)/in

# ====================================================================== #
#  Developer / packaging targets centralised from the old *.sh scripts.  #
#  Single source of truth: these reuse the canonical source/object lists #
#  defined above, so a new module added to the build is picked up here    #
#  automatically. The standalone scripts (fuzz.sh, build_deb.sh, ...) now #
#  delegate to these targets instead of carrying a hand-maintained copy   #
#  of the build (which is how fuzz.sh silently went stale).               #
# ====================================================================== #

# System build dependencies + a source build of Lexbor (Debian/Ubuntu). Centralises
# the dependency half of install.sh. NOTE: install.sh's source-mutating `sed`
# patches (OpenSSL<3.3 / CI host workarounds) are deliberately NOT here -- a build
# target must never rewrite tracked sources. Run them only on the hosts that need
# them, from install.sh.
deps:
	sudo apt-get update -y
	sudo apt-get install -y build-essential cmake libcairo2-dev libwayland-dev \
	  wayland-protocols libxkbcommon-dev libcurl4-openssl-dev libssl-dev fontconfig \
	  libfreetype6-dev libcmocka-dev libpng-dev libwayland-bin git
	@if [ ! -d /usr/local/include/lexbor ]; then \
	  echo "[*] building Lexbor from source..."; \
	  d=$$(mktemp -d); git clone --depth 1 https://github.com/lexbor/lexbor.git $$d/lexbor; \
	  cmake -S $$d/lexbor -B $$d/lexbor -DLEXBOR_BUILD_SEPARATELY=OFF; \
	  $(MAKE) -C $$d/lexbor -j$$(nproc); sudo $(MAKE) -C $$d/lexbor install; sudo ldconfig; \
	  rm -rf $$d; \
	else echo "[+] Lexbor already installed"; fi

# Run the GUI browser, optionally on a URL: `make run URL=https://example.com`.
# Centralises run_freedom.sh (minus its nested-weston launch, which is only for a
# headless CI box; in a real Wayland session the binary runs directly).
run: $(BUILD_DIR)/freedom
	./$(BUILD_DIR)/freedom $(URL)

# AFL++ coverage-guided fuzzing of the full headless pipeline. Replaces fuzz.sh,
# whose hand-copied object list drifted out of date: this rebuilds the canonical
# `freedom` target with the AFL compiler, so the source list can never diverge.
# Requires afl++ (`sudo apt install afl++`).
fuzz-afl: CC := afl-clang-fast
fuzz-afl: clean $(BUILD_DIR)/freedom
	mkdir -p $(FUZZ_DIR)/in $(FUZZ_DIR)/out
	[ -e $(FUZZ_DIR)/in/seed.html ] || echo '<html><body><p>seed</p></body></html>' > $(FUZZ_DIR)/in/seed.html
	afl-fuzz -i $(FUZZ_DIR)/in -o $(FUZZ_DIR)/out -- ./$(BUILD_DIR)/freedom --headless @@

# Build the Debian .deb, then restore build/ ownership: debuild runs under
# fakeroot/sudo and leaves build/ root-owned, which then blocks an ordinary `make`.
# Centralises build_deb.sh.
deb:
	rm -fr debian/*.ex debian/*.EX debian/freedom.doc-base*
	$(MAKE) clean
	chmod +x debian/rules
	debuild -us -uc -b -d
	@echo "[*] restoring build/ ownership after the fakeroot/sudo build"
	-sudo chown -R $$(id -u):$$(id -g) $(BUILD_DIR)
	@echo "[+] package built: ../freedom_0.0.3-1_amd64.deb"

# Build and run the Zero-Trust Docker image (Xvfb+weston+noVNC on :8080). Centralises
# docker_run.sh; the in-container entrypoint stays in docker-entrypoint.sh (it is the
# image's ENTRYPOINT, run inside the container, not a host build command).
docker:
	sudo docker build -t freedom-browser .
	sudo docker run -it --rm --name freedom-test -p 8080:8080 \
	  --cap-drop=ALL --security-opt no-new-privileges:true --memory=2g freedom-browser

# --- UI demo (Hito 4): Wayland + Cairo. Visual test, not part of `make test`. ---
# Generated xdg-shell glue (relaxed flags: generated code is not ours to harden).
$(BUILD_DIR)/xdg-shell-client-protocol.h: $(XDG_XML) | $(BUILD_DIR)
	$(WL_SCANNER) client-header $< $@

$(BUILD_DIR)/xdg-shell-protocol.c: $(XDG_XML) | $(BUILD_DIR)
	$(WL_SCANNER) private-code $< $@

$(BUILD_DIR)/xdg-decoration-client-protocol.h: $(DECO_XML) | $(BUILD_DIR)
	$(WL_SCANNER) client-header $< $@

$(BUILD_DIR)/xdg-decoration-protocol.c: $(DECO_XML) | $(BUILD_DIR)
	$(WL_SCANNER) private-code $< $@

# View flags: hardened + warnings, but not -Werror (generated headers/code). Our
# gui/*.c is still expected to be warning-clean.
VIEW_CFLAGS = $(STD) -Wall -Wextra $(HARDEN) $(OPT) -Iinclude -I$(BUILD_DIR) \
              $(WL_CFLAGS) $(LEXBOR_CFLAGS)

view: $(BUILD_DIR)/freedom-view
	@echo "Built $<. On a Wayland session run:  $< <file.html>"

$(BUILD_DIR)/freedom-view: $(GUI_DIR)/freedom_view.c $(GUI_DIR)/ui_render.c \
                           $(SRC_DIR)/ui_layout.c $(SRC_DIR)/html_parse.c \
                           $(BUILD_DIR)/xdg-shell-protocol.c \
                           $(BUILD_DIR)/xdg-shell-client-protocol.h \
                           $(BUILD_DIR)/xdg-decoration-protocol.c \
                           $(BUILD_DIR)/xdg-decoration-client-protocol.h | $(BUILD_DIR)
	$(CC) $(VIEW_CFLAGS) \
	  $(GUI_DIR)/freedom_view.c $(GUI_DIR)/ui_render.c $(SRC_DIR)/ui_layout.c \
	  $(SRC_DIR)/html_parse.c $(BUILD_DIR)/xdg-shell-protocol.c \
	  $(BUILD_DIR)/xdg-decoration-protocol.c \
	  -o $@ $(LDHARDEN) $(WL_LIBS) $(HP_LIBS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)
