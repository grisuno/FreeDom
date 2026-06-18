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
             $(BUILD_DIR)/test_textfield $(BUILD_DIR)/test_form

.PHONY: all test itest asan fuzz fuzz-js view clean

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

$(BUILD_DIR)/test_page_view: $(TEST_DIR)/test_page_view.c $(BUILD_DIR)/page_view.o $(BUILD_DIR)/css_color.o $(BUILD_DIR)/html_parse.o | $(BUILD_DIR)
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
                              $(BUILD_DIR)/html_parse.o $(PSL_OBJ) | $(BUILD_DIR)
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
                       $(BUILD_DIR)/css_color.o $(QJS_OBJ) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CMOCKA_CFLAGS) $^ -o $@ $(LDFLAGS) $(JS_LIBS) $(HP_LIBS) $(CMOCKA_LIBS)

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
                      $(BUILD_DIR)/textfield.o \
                      $(PSL_OBJ) $(FREEDOM_UI_OBJ) $(FREEDOM_GUI_OBJ) \
                      $(BUILD_DIR)/xdg-shell-client-protocol.h \
                      $(BUILD_DIR)/xdg-decoration-client-protocol.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(BUILD_DIR) $(WL_CFLAGS) $^ -o $@ $(LDFLAGS) $(SF_LIBS) $(JS_LIBS) $(HP_LIBS) $(WL_LIBS)

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
