# API (page 2 of 13)
Previous: [API.md](API.md)

## gui/browser_ui.c
Depends on: `gui/browser_ui_internal.h`, `include/anchor.h`, `include/block_flow.h`, `include/box_blur.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/cached_fetch.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_values.h`, `include/data_url.h`, `include/doc_title.h`, `include/download.h`, `include/exact_key.h`, `include/fb_cmdline.h`, `include/fb_panes.h`, `include/find_text.h`, `include/form.h`, `include/frame_clock.h`, `include/frame_host.h`, `include/freebug.h`, `include/group_index.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/hostedit.h`, `include/identity.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/lazy_load.h`, `include/link_nav.h`, `include/mask_cache.h`, `include/media_decoder.h`, `include/nav_token.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/shm_slots.h`, `include/smooth_scroll.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/table_layout.h`, `include/text_case.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/video_controls.h`, `include/video_pick.h`, `include/web_storage.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/wl_guard.h`, `include/ws_hub.h`, `include/zoom.h`
- `now_ms` (function) `gui/browser_ui.c:175` `static uint64_t now_ms(void)` -- Largest text slice measured/drawn at once (one word, or one clipped label). * Words longer than this are still...
- `offset` (function) `gui/browser_ui.c:186` `* offset (labels and the flag live in one place, no magic indices);`
- `fields` (function) `gui/browser_ui.c:302` `* fields (so the 200+ render/event call sites stay unchanged);`
- `landed` (function) `gui/browser_ui.c:441` `* yet when the document landed (spec/anchor.md);`
- `delay` (function) `gui/browser_ui.c:452` `* timer delay (tab_page.next_timer_ms);`
- `main` (function) `gui/browser_ui.c:619` `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...`
- `gutter` (function) `gui/browser_ui.c:749` `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
- `apply_zoom` (function) `gui/browser_ui.c:769` `static void apply_zoom(browser_window *w)` -- Applies a new zoom level: rebuild the theme and repaint.
- `buffer_release` (function) `gui/browser_ui.c:780` `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
- `fb_buffer_release` (function) `gui/browser_ui.c:791` `static void fb_buffer_release(void *data, struct wl_buffer *wl_buffer)` -- Freebug's window keeps its single buffer: its user data is the freebug window, not a * browser_window, so it must...
- `destroy_buffer` (function) `gui/browser_ui.c:794` `static void destroy_buffer(browser_window *w)`
- `make_slot` (function) `gui/browser_ui.c:804` `static int make_slot(browser_window *w, int i, size_t size, int stride)`
- `ensure_buffer` (function) `gui/browser_ui.c:829` `static int ensure_buffer(browser_window *w)` -- Selects the slot to paint into and points the legacy aliases (buffer/shm_data/cairo_surface) * at it.
- `read_file` (function) `gui/browser_ui.c:848` `static char *read_file(const char *path, size_t *out_len)`
- `build_file_origin` (function) `gui/browser_ui.c:887` `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` -- Builds a "file:///<canonical absolute path>" origin from a local path (or passes through a file:// URL's path)....
- `build_host_filter` (function) `gui/browser_ui.c:901` `static hb_set *build_host_filter(void)` -- Builds the host filter from the user's .conf lists.
- `build_js_filter` (function) `gui/browser_ui.c:917` `static hb_set *build_js_filter(void)`
- `build_impersonate_optin` (function) `gui/browser_ui.c:920` `static int build_impersonate_optin(void)` -- No impersonate.conf: third signal is the user flag (FREEDOM_IMPERSONATE=1). * allow.conf AND js.conf AND this flag...
- `freedom_write_dir` (function) `gui/browser_ui.c:929` `static int freedom_write_dir(char *out, size_t cap)` -- The writable Freedom config dir: $FREEDOM_HOSTS_DIR if set, else ~/.config/freedom (created if absent).
- `list_append_host` (function) `gui/browser_ui.c:958` `static int list_append_host(const char *filename, const char *host)` -- Appends `host` to one of the user's .conf lists in the writable config dir, skipping a duplicate.
- `reload_host_list` (function) `gui/browser_ui.c:992` `static void reload_host_list(browser_window *w, int sel)`
- `add_current_host_to_list` (function) `gui/browser_ui.c:1042` `static int add_current_host_to_list(browser_window *w, int sel)` -- Appends the current page's host to one of the user's .conf lists (block/allow/js), * then reloads the in-memory...
- `load_favorites` (function) `gui/browser_ui.c:1077` `static void load_favorites(browser_window *w)` -- Concatenates the allow.conf bodies along the same search path build_host_filter uses into one string: the omnibox...
- `omni_refresh` (function) `gui/browser_ui.c:1114` `static void omni_refresh(browser_window *w)` -- Recomputes the omnibox autocomplete suggestions for the current URL-bar text.
- `profile_sync` (function) `gui/browser_ui.c:1145` `static void profile_sync(browser_window *w)` -- Mirrors the session's persistable choices into w->prefs and seals them to disk.
- `remember_visit` (function) `gui/browser_ui.c:1162` `static void remember_visit(browser_window *w, const char *url)` -- Records a committed navigation in the persistent history (dedup + cap live in prefs).
- `bookmark_star_state` (function) `gui/browser_ui.c:1171` `static int bookmark_star_state(const browser_window *w)` -- The pill's bookmark star: 0 hidden (nothing to bookmark: start page, about:), 1 the * page is not bookmarked, 2 it...
- `bookmark_toggle_current` (function) `gui/browser_ui.c:1178` `static void bookmark_toggle_current(browser_window *w)` -- The pill's bookmark star: 0 hidden (nothing to bookmark: start page, about:), 1 the * page is not bookmarked, 2 it...
- `proxy_addr_from_env` (function) `gui/browser_ui.c:1202` `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...` -- Copies a proxy "host:port" into dst: if the env value is unset/empty the default is used; the literal "1" also means...
- `proxy` (function) `gui/browser_ui.c:1213` `* and enable each proxy ("1" => the default port);`
- `init_net_config` (function) `gui/browser_ui.c:1216` `static void init_net_config(browser_window *w)` -- Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in, everything off unless explicitly...
- `is_https_url` (function) `gui/browser_ui.c:1226` `static int is_https_url(const char *s)`
- `is_http_url` (function) `gui/browser_ui.c:1230` `static int is_http_url(const char *s)`
- `host_from_url` (function) `gui/browser_ui.c:1241` `static int host_from_url(const char *url, char *out, size_t outsz)` -- A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is * fetched over the network (through...
- `video_feeder_thread` (function) `gui/browser_ui.c:1272` `static void *video_feeder_thread(void *arg);`
- `video_pipeline_down` (function) `gui/browser_ui.c:1274` `static void video_pipeline_down(browser_window *w);`
- `toggle_fullscreen` (function) `gui/browser_ui.c:1279` `static void toggle_fullscreen(browser_window *w)` -- Fullscreen toggle: ALT+ENTER switches the window between windowed and * compositor-managed fullscreen.
- `input_is_interactive` (function) `gui/browser_ui.c:1294` `static int input_is_interactive(int input_type)` -- An editable control gets a live text field; submit/button/hidden do not.
- `input_is_editable` (function) `gui/browser_ui.c:1300` `static int input_is_editable(int input_type)`
- `free_inputs` (function) `gui/browser_ui.c:1306` `static void free_inputs(browser_window *w)` -- are not text-editable -- they are tracked via rebuild_inputs so clicks * dispatch to them, but they have no...
- `free_images` (function) `gui/browser_ui.c:1314` `static void free_images(browser_window *w)` -- static int input_is_editable(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD ||...
- `find_bg_image` (function) `gui/browser_ui.c:1353` `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` -- The decoded background-image for url (a box's bg_image_url), or NULL when it has none (unset / blocked / failed...
- `box_pad_px` (function) `gui/browser_ui.c:1377` `static double box_pad_px(int px_val, int pct_pm, double cb_w);`
- `replaced_edges` (function) `gui/browser_ui.c:1379` `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
- `repl_edges_x` (function) `gui/browser_ui.c:1403` `static double repl_edges_x(const repl_edges *e)`
- `repl_edges_y` (function) `gui/browser_ui.c:1407` `static double repl_edges_y(const repl_edges *e)`
- `set_packed_rgba` (function) `gui/browser_ui.c:1413` `static void set_packed_rgba(cairo_t *cr, int col)` -- Sets a packed author color whose bits 24..30 carry its transparency (cv_parse_color_t7): * an opaque color is...
- `image_display_size` (function) `gui/browser_ui.c:1449` `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
- `placeholder_display_size` (function) `gui/browser_ui.c:1515` `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
- `rebuild_inputs` (function) `gui/browser_ui.c:1538` `static void rebuild_inputs(browser_window *w)` -- Builds the live editable state for the current doc: one entry per editable * control, seeded with its declared value.
- `find_input_state` (function) `gui/browser_ui.c:1564` `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` -- size_t k = 0; for (size_t i = 0; i < n; ++i) { const rd_block *b = rd_at(w->doc, i); if (b->kind != RD_INPUT ||...
- `set_doc` (function) `gui/browser_ui.c:1572` `static void set_doc(browser_window *w, rd_doc *d)` -- The ONE way the window's document changes: every reassignment advances doc_serial, which * the retained layout's key...
- `clear_doc` (function) `gui/browser_ui.c:1579` `static void clear_doc(browser_window *w)` -- Releases the structured render of the previous page (text mode resumes).
- `set_cache` (function) `gui/browser_ui.c:1589` `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` -- Releases the structured render of the previous page (text mode resumes).
- `img_css_w` (function) `gui/browser_ui.c:1605` `static uint32_t img_css_w(const tab_image *img)` -- Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit.
- `img_css_h` (function) `gui/browser_ui.c:1606` `static uint32_t img_css_h(const tab_image *img)`
- `surface_from_pixels` (function) `gui/browser_ui.c:1608` `static cairo_surface_t *surface_from_pixels(const tab_image *img)`
- `fetch_follow_navigable` (function) `gui/browser_ui.c:1672` `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...`
- `fetch_get_cached` (function) `gui/browser_ui.c:1680` `static sf_status fetch_get_cached(const browser_window *w, const char *url, sf_config *cfg,
     ...` -- GET through the sealed HTTP cache (spec/http_cache.md), partitioned by the top-level * site.
- `fetch_post_navigable` (function) `gui/browser_ui.c:1688` `static sf_status fetch_post_navigable(const char *url, sf_config *cfg,
                          ...`
- `page_host_allowlisted` (function) `gui/browser_ui.c:1712` `static int page_host_allowlisted(const browser_window *w)`
- `ui_set_operator_insecure` (function) `gui/browser_ui.c:1721` `void ui_set_operator_insecure(int on)`
- `apply_operator_override` (function) `gui/browser_ui.c:1722` `static void apply_operator_override(sf_config *cfg)`
- `aa_note` (function) `gui/browser_ui.c:1739` `static void aa_note(browser_window *w, const char *abs, const char *host)` -- A fetch thread asks: should `host` (pulled by the page at `abs`) be auto-allowed?
- `page_trusted` (function) `gui/browser_ui.c:1766` `static int page_trusted(const browser_window *w);`
- `gui_sub_prepare` (function) `gui/browser_ui.c:1778` `static int gui_sub_prepare(browser_window *w, const char *top, int trusted, int top_allowed,
    ...`
- `gui_sub_perform` (function) `gui/browser_ui.c:1819` `static int gui_sub_perform(gui_sub_prep *p, const char *method, const void *body, size_t body_len...` -- A page the user put on allow.conf also gets its own subresources (a CSS CDN with an RSA-2048 leaf) at the relaxed...
- `gui_subresource_fetch` (function) `gui/browser_ui.c:1848` `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
- `gui_net_ctx_free` (function) `gui/browser_ui.c:1873` `static void gui_net_ctx_free(void *p)`
- `gui_net_ctx_new` (function) `gui/browser_ui.c:1881` `static gui_net_ctx *gui_net_ctx_new(browser_window *w)`
- `net_ctx_lock` (function) `gui/browser_ui.c:1894` `static void net_ctx_lock(browser_window *w)`
- `net_ctx_unlock` (function) `gui/browser_ui.c:1895` `static void net_ctx_unlock(browser_window *w)`
- `gui_net_ctx_retire` (function) `gui/browser_ui.c:1898` `static void gui_net_ctx_retire(gui_net_ctx *c)` -- if (c == NULL) return NULL; c->top = strdup(w->cur_top); if (c->top == NULL || pthread_mutex_init(&c->mu, NULL) !=...
- `gui_async_fetch` (function) `gui/browser_ui.c:1905` `static int gui_async_fetch(void *vctx, const char *method, const char *url,
                     ...`
- `only` (function) `gui/browser_ui.c:1947` `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...`
- `gui_css_sink` (function) `gui/browser_ui.c:1952` `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...` -- tab_css_sink_fn: retains each served 2xx CSS body for the @font-face pass.
- `first` (function) `gui/browser_ui.c:2020` `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
- `hb_is_allowlisted` (function) `gui/browser_ui.c:2084` `&& hb_is_allowlisted(w->hosts, ihost);`
- `proceed` (function) `gui/browser_ui.c:2131` `* may proceed (cfg and pr->allowlisted are then set);`
- `prepare_fetch` (function) `gui/browser_ui.c:2134` `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...` -- Builds cfg for url and applies the pre-fetch gates.
- `fetch_job_free` (function) `gui/browser_ui.c:2241` `static void fetch_job_free(fetch_job *j)`
- `stream_progress_cb` (function) `gui/browser_ui.c:2263` `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` -- Called by the fetch thread (~1/sec) with the downloaded body so far.
- `fetch_job_cancelled` (function) `gui/browser_ui.c:2288` `static int fetch_job_cancelled(void *ctx)` -- Polled by libcurl on the fetch thread: a job whose navigation was superseded (Stop, a new navigation, a tab switch)...
- `fetch_thread` (function) `gui/browser_ui.c:2296` `static void *fetch_thread(void *arg)` -- Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer back to the event loop.
- `stream_discard` (function) `gui/browser_ui.c:2351` `static void stream_discard(browser_window *w)` -- int r1 = snprintf(j->tls, sizeof j->tls, "%s", resp.tls_version ? resp.tls_version : ""); int r2 =...
- `nav_supersede` (function) `gui/browser_ui.c:2362` `static void nav_supersede(browser_window *w)` -- Cancels the active tab's network navigation (its transfer stops at the next libcurl * poll, its result is dropped)...
- `fetch_launch` (function) `gui/browser_ui.c:2370` `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...` -- Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch).
- `secure_fetch` (function) `gui/browser_ui.c:2426` `* through secure_fetch (Zero Trust);`
- `is_frame_href` (function) `gui/browser_ui.c:2505` `static int is_frame_href(const char *href)` -- A live <iframe> run is painted from its frame's own document (spec/frame_broker.md section 5): * its "image" is a...
- `load_images` (function) `gui/browser_ui.c:2511` `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx,
     ...`
- `string` (function) `gui/browser_ui.c:2594` `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...`
- `do_load` (function) `gui/browser_ui.c:2655` `static void do_load(browser_window *w, const char *url);`
- `tab_new` (function) `gui/browser_ui.c:2662` `static void tab_new(browser_window *w, const char *url);`
- `toggle` (function) `gui/browser_ui.c:2676` `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...`
- `page_js_host_allowlisted` (function) `gui/browser_ui.c:2687` `static int page_js_host_allowlisted(const browser_window *w)` -- Resolves the JS policy for the current page's host (Secure by Default: off unless the global mode is ON or the host...
- `compute_page_js` (function) `gui/browser_ui.c:2693` `static int compute_page_js(const browser_window *w)`
- `seed_session_cookies` (function) `gui/browser_ui.c:2707` `static void seed_session_cookies(tab *t, int trusted, const char *url)` -- Seeds document.cookie for the next load from the ephemeral network jar (trusted host * only); reset to none...
- `seed_local_storage` (function) `gui/browser_ui.c:2731` `static void seed_local_storage(browser_window *w, tab *t, int trusted)` -- Seeds the next load's localStorage from the window's in-memory store (trusted host * only; cleared otherwise so a...
- `collect_local_storage` (function) `gui/browser_ui.c:2746` `static void collect_local_storage(browser_window *w, const tab_page *page)` -- Takes the page's changed localStorage (already validated by the tab reader) into * the window's store.
- `foldback_session_cookies` (function) `gui/browser_ui.c:2756` `static void foldback_session_cookies(const char *url, const char *jar)` -- Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network jar * one pair at a time, so JS-set...
- `drop_repl_worker` (function) `gui/browser_ui.c:2789` `static void drop_repl_worker(browser_window *w)`
- `gui_viewport_w` (function) `gui/browser_ui.c:2806` `static int gui_viewport_w(const browser_window *w)` -- The viewport width @media and the viewport units see: the WINDOW width, scrollbar gutter included (Media Queries 4...
- `schedule_js_tick` (function) `gui/browser_ui.c:2813` `static void schedule_js_tick(browser_window *w, int next_ms)` -- Schedules the next JS timer tick from the worker's reported smallest pending delay (tab_page.next_timer_ms; < 0 =...
- `render_current_ex` (function) `gui/browser_ui.c:2823` `static void render_current_ex(browser_window *w, int allow_js_nav)`
- `window` (function) `gui/browser_ui.c:2841` `* first paint and a hung one never holds the window (spec/subreq_async.md). */ gui_net_ctx *nctx = gui_net_ctx_new(w);`
- `stylesheets` (function) `gui/browser_ui.c:2850` `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...`
- `body` (function) `gui/browser_ui.c:2883` `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);`
- `ALIVE` (function) `gui/browser_ui.c:2991` `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...`
- `render_current` (function) `gui/browser_ui.c:3012` `static void render_current(browser_window *w)` -- the first OP_TICK from the worker's reported smallest pending delay. w->js_ticks_left = JS_TICKS_PER_LOAD...
- `show_busy` (function) `gui/browser_ui.c:3019` `static void show_busy(browser_window *w)` -- Marks a request in flight and paints a frame so the spinner appears at once.
- `show_fetch_error` (function) `gui/browser_ui.c:3028` `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...` -- Replaces the page with the standard "Failed to load" diagnostic for status ss on url. allowlisted tailors the hint...
- `identity_load` (function) `gui/browser_ui.c:3097` `static void identity_load(browser_window *w)` -- static void identity_commit(browser_window *w) { (void)idn_accept_language(&w->identity, w->accept_lang, sizeof...
- `arrives` (function) `gui/browser_ui.c:3107` `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
- `strcmp` (function) `gui/browser_ui.c:3214` `&& strcmp(auth_host_buf, w->auth_host) != 0)`
- `resolve` (function) `gui/browser_ui.c:3251` `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...`
- `tab_save` (function) `gui/browser_ui.c:3288` `static void tab_save(browser_window *w)` -- Parks the active tab's live state into its slot (a shallow move: the slot and the live fields briefly alias the same...
- `tab_restore` (function) `gui/browser_ui.c:3311` `static void tab_restore(browser_window *w)` -- c->images = w->images; c->image_count = w->image_count; c->bg_images = w->bg_images; c->bg_image_count =...
- `free_live_page` (function) `gui/browser_ui.c:3334` `static void free_live_page(browser_window *w)` -- w->images = c->images; w->image_count = c->image_count; w->bg_images = c->bg_images; w->bg_image_count =...
- `tab_ctx_release` (function) `gui/browser_ui.c:3347` `static void tab_ctx_release(tab_ctx *c)` -- /* Frees the LIVE page's owned state (used when closing the foreground tab). static void...
- `tab_show_ready` (function) `gui/browser_ui.c:3377` `static void tab_show_ready(browser_window *w)` -- } free(c->bg_images); } free(c->inputs); if (c->doc != NULL) rd_free(c->doc); free(c->cur_html); free(c->cur_top)...
- `tab_switch` (function) `gui/browser_ui.c:3386` `static void tab_switch(browser_window *w, int idx)` -- } static void deliver_fetch_result(browser_window *w, fetch_job *j); /* The tab just brought to the foreground...
- `uitab_close` (function) `gui/browser_ui.c:3452` `static void uitab_close(browser_window *w, int idx)` -- if (browser_init(&w->bs) != BROWSER_OK) { browser_set_page(&w->bs, "Freedom", "", 0); } if (url != NULL) {...
- `chrome_of` (function) `gui/browser_ui.c:3491` `static chl_layout chrome_of(const browser_window *w)` -- if (w->active_tab >= w->tab_count) w->active_tab = w->tab_count - 1; tab_restore(w); stream_discard(w); const char...
- `tab_move` (function) `gui/browser_ui.c:3502` `static void tab_move(browser_window *w, int from, int to)` -- Moves tab `from` to slot `to`; the others shift (chl_move_index is the one remapping).
- `tab_title` (function) `gui/browser_ui.c:3529` `static const char *tab_title(const browser_window *w, int i, char *buf, size_t cap)` -- static void tab_drag_motion(browser_window *w) { if (!w->tab_dragging) { if (fabs(w->ptr_x - w->tab_press_x) <...
- `tabbar_top` (function) `gui/browser_ui.c:3549` `static double tabbar_top(const browser_window *w)` -- Top of the tab strip: directly under the client-side titlebar (or at the surface * top under server-side decorations).
- `toolbar_top` (function) `gui/browser_ui.c:3556` `static double toolbar_top(const browser_window *w)` -- Top of the toolbar: under the tab strip, which is always reserved.
- `page_gutter` (function) `gui/browser_ui.c:3563` `static double page_gutter(const browser_window *w);` -- The content area rectangle below the toolbar, in surface coordinates.
- `content_geometry` (function) `gui/browser_ui.c:3565` `static void content_geometry(const browser_window *w, double *top, double *height)`
- `page_side` (function) `gui/browser_ui.c:3595` `static double page_side(const browser_window *w, int side)`
- `content_margin_x` (function) `gui/browser_ui.c:3599` `static double content_margin_x(const browser_window *w)`
- `content_margins_x` (function) `gui/browser_ui.c:3610` `static double content_margins_x(const browser_window *w)` -- return (w->doc != NULL) ?
- `content_width` (function) `gui/browser_ui.c:3615` `static double content_width(const browser_window *w)`
- `html_center_offset` (function) `gui/browser_ui.c:3625` `static double html_center_offset(const browser_window *w)`
- `scrollbar_metrics` (function) `gui/browser_ui.c:3639` `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...` -- Geometry of the vertical scrollbar in surface coordinates, plus the current thumb position.
- `scrollbar_drag_to` (function) `gui/browser_ui.c:3667` `static void scrollbar_drag_to(browser_window *w)` -- Maps the current pointer Y (less the grab offset) to a scroll offset while the * thumb is being dragged, then repaints.
- `draw_scrollbar` (function) `gui/browser_ui.c:3684` `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` -- Paints the scrollbar track and thumb.
- `chrome_hot_at` (function) `gui/browser_ui.c:3723` `static ui_hot chrome_hot_at(const browser_window *w, double px, double py)` -- The chrome part under (px, py), packed with its tab (ui_hot).
- `hot_actionable` (function) `gui/browser_ui.c:3735` `static int hot_actionable(const browser_window *w, ui_hot hot)` -- A hovered chrome part is "actionable" (gets the hand cursor) when clicking it would * do something: Back/Forward...
- `menu_panel_rect` (function) `gui/browser_ui.c:3747` `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...` -- The options-menu panel rectangle (below the gear button), and its per-item row * height.
- `ua_box_rect` (function) `gui/browser_ui.c:3762` `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...` -- The editable User-Agent box rectangle inside the options panel.
- `smaller` (function) `gui/browser_ui.c:3899` `* size when the content is smaller (height) or wider (min-width);`
- `rc_float_bottom` (function) `gui/browser_ui.c:4211` `static double rc_float_bottom(const rc_state *s)` -- Width left for the line after both insets, in the CURRENT box context. rc_float_fit_line uses it to decide whether...
- `rc_float_clear` (function) `gui/browser_ui.c:4220` `static void rc_float_clear(rc_state *s)` -- Ends the float context: drops every exclusion and moves cur_top below the tallest one.
- `rc_float_refresh` (function) `gui/browser_ui.c:4233` `static void rc_float_refresh(rc_state *s, double line_h)` -- Recomputes the open line's float insets for its own cur_top, discarding exclusions the flow has already passed.
- `rc_float_fit_line` (function) `gui/browser_ui.c:4279` `static void rc_float_fit_line(rc_state *s, double line_h)` -- CSS 2.1 9.5: "if there is not enough horizontal room for the line box beside the float, it is shifted downward until...
- `line_limit` (function) `gui/browser_ui.c:4298` `static double line_limit(const rc_state *s, double content_w)` -- The right edge available to the open line: the block's content width minus what a float steals from the right at...
- `rc_free` (function) `gui/browser_ui.c:4306` `static void rc_free(rc_layout *L)`
- `rc_add_box` (function) `gui/browser_ui.c:4326` `static rc_box *rc_add_box(rc_layout *L)`
- `rc_add_frag` (function) `gui/browser_ui.c:4338` `static rc_frag *rc_add_frag(rc_layout *L)`
- `rc_add_row` (function) `gui/browser_ui.c:4353` `static rc_row *rc_add_row(rc_layout *L)`
- `family_face` (function) `gui/browser_ui.c:4365` `static const char *family_face(int family)` -- Maps an author font-family bucket (css_font_family) to a Cairo toy-font family. * The engine matches no exact...
- `HarfBuzz` (function) `gui/browser_ui.c:4376` `* descriptor via HarfBuzz (text_shape);`
- `content_font_ex` (function) `gui/browser_ui.c:4387` `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...` -- Selects the slice font: the toy face (for the fallback path and chrome) plus the HarfBuzz descriptor the shapers...
- `sites` (function) `gui/browser_ui.c:4400` `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
- `content_font` (function) `gui/browser_ui.c:4409` `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
- `set_rgb_alpha` (function) `gui/browser_ui.c:4416` `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` -- Sets the source color, applying an author opacity (0..100) as an alpha when set * (-1 = fully opaque).
- `utf8_clen` (function) `gui/browser_ui.c:4425` `static size_t utf8_clen(const char *s, size_t n)` -- Bytes in the UTF-8 cluster starting at s[0] (1 for a stray/continuation byte), * clamped to n.
- `draw_slice` (function) `gui/browser_ui.c:4458` `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` -- Draws a text slice at (x, baseline) in the current content font/source.
- `frag_styled` (function) `gui/browser_ui.c:4471` `static int frag_styled(const rc_frag *f)` -- True if a fragment needs the per-cluster path (text-transform other than none/unset, or a non-zero letter-spacing).
- `styled_advance` (function) `gui/browser_ui.c:4478` `static double styled_advance(cairo_t *cr, const rc_frag *f)` -- Advance (px) of a fragment's text under its text-transform + letter-spacing.
- `styled_draw` (function) `gui/browser_ui.c:4500` `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` -- Draws a fragment's text starting at (x, baseline) under its text-transform + * letter-spacing.
- `block_style` (function) `gui/browser_ui.c:4523` `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
- `block_margins` (function) `gui/browser_ui.c:4551` `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...` -- cb_w is the containing block's content width: a PERCENTAGE vertical margin * resolves against it, not against any...
- `area` (function) `gui/browser_ui.c:4588` `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
- `run` (function) `gui/browser_ui.c:4645` `* continuation run (block_id < 0 with no block break) deliberately skips reconcile * to stay on the line, and that...`
- `leave_inline_box` (function) `gui/browser_ui.c:4651` `static void leave_inline_box(rc_layout *L, rc_state *s, const rd_doc *doc, int block_id)`
- `atoms_extend_line` (function) `gui/browser_ui.c:4673` `static void atoms_extend_line(const rc_layout *L, rc_state *s, double *h,
                       ...` -- A sized inline-block is part of the line box (CSS 2.1 10.8): the line grows to hold it, above the baseline for an...
- `flush_line` (function) `gui/browser_ui.c:4715` `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
- `open_line_height` (function) `gui/browser_ui.c:4786` `static double open_line_height(const rc_state *s, const ui_theme *th)` -- Height the currently open line WILL have when it flushes (same formula flush_line uses): an out-of-flow static...
- `open_line` (function) `gui/browser_ui.c:4801` `static void open_line(rc_layout *L, rc_state *s)`
- `flow_emit_frag` (function) `gui/browser_ui.c:4855` `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...` -- Emits one fragment at the current pen position, advancing it.
- `flow_smallcaps_word` (function) `gui/browser_ui.c:4917` `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...` -- One word under synthesized small caps (spec/text_case.md): its lowercase runs are capitals at TC_SMALLCAPS_SCALE of...
- `produced` (function) `gui/browser_ui.c:4951` `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...`
- `ibx_advance` (function) `gui/browser_ui.c:4972` `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)` -- Advances the pen by the inter-word space `adv` before a word.
- `flow_text` (function) `gui/browser_ui.c:4981` `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
- `line` (function) `gui/browser_ui.c:5051` `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...`
- `box_path4` (function) `gui/browser_ui.c:5254` `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);`
- `input_inline_eligible` (function) `gui/browser_ui.c:5262` `static int input_inline_eligible(const rd_block *b)` -- A native form control (no author box of its own -- one with a box goes through the box engine) is an inline-level...
- `input_inline_size` (function) `gui/browser_ui.c:5276` `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...` -- The size of a native control in its line: the same widths draw_input_row paints * and the field height the row path...
- `replaced_inline_size` (function) `gui/browser_ui.c:5298` `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
- `replaced_is_inline_level` (function) `gui/browser_ui.c:5330` `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` -- True when a replaced block is INLINE-LEVEL content of the line already being built, rather than a block of its own.
- `block_leaves_flow` (function) `gui/browser_ui.c:5336` `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);`
- `inlines` (function) `gui/browser_ui.c:5343` `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
- `place_inline_replaced` (function) `gui/browser_ui.c:5380` `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...` -- Places an inline-level replaced element inside the open line as an atomic inline: it advances the pen like a word...
- `css_replaced_box` (function) `gui/browser_ui.c:5465` `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...` -- The box an unavailable replaced element gets from its own CSS: a definite width plus an aspect-ratio (CSS Sizing 4...
- `emit_replaced_row` (function) `gui/browser_ui.c:5474` `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
- `block_text_style` (function) `gui/browser_ui.c:5587` `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...` -- The text style a block's text is drawn in: the UA style of its kind, the author colour (unless the theme is forced)...
- `flow_text_block` (function) `gui/browser_ui.c:5598` `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
- `run_is_content` (function) `gui/browser_ui.c:5755` `static int run_is_content(const rd_block *bk)` -- Whether a run is real content, as opposed to the empty or whitespace-only placeholder a decorated box with nothing...
- `item_root_box_pass` (function) `gui/browser_ui.c:5765` `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
- `them` (function) `gui/browser_ui.c:5818` `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
- `item_root_box` (function) `gui/browser_ui.c:5839` `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` -- Root box of a flex/grid item, bounded by the container box page_view stamped on the item's runs (pv_run.cont_box_id).
- `itself` (function) `gui/browser_ui.c:5847` `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
- `box_edge_px` (function) `gui/browser_ui.c:5858` `static double box_edge_px(int wpx)` -- Maps a css_align_kw (align-items/align-self) to the box_tree cross-axis alignment it drives.
- `rc_box_copy_decoration` (function) `gui/browser_ui.c:5878` `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` -- Copies a box def's paint-time decoration (borders, radius, shadow, outline, background, gradient, background-image...
- `box_is_strict_descendant` (function) `gui/browser_ui.c:5971` `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` -- True iff box `id` is a STRICT descendant of `anc` in the box tree (or anc < 0, * which means "no container box"...
- `block_space_px` (function) `gui/browser_ui.c:5989` `static double block_space_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
          ...` -- The advance of one collapsed word space in the font of block `b`: what separates two inline-level atoms written with...
- `item_sides_at_level` (function) `gui/browser_ui.c:6009` `static item_sides item_sides_at_level(cairo_t *cr, const browser_window *w, const ui_theme *th,
 ...` -- item_sides for one item of container `cid`, plus the word space that precedes an atom of a MIXED anonymous...
- `item_sides_at_level_raw` (function) `gui/browser_ui.c:6028` `static item_sides item_sides_at_level_raw(const rd_doc *doc, size_t b0, size_t b1,
              ...` -- The sides proper.
- `container_box_of` (function) `gui/browser_ui.c:6095` `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
- `table` (function) `gui/browser_ui.c:6117` `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
- `container` (function) `gui/browser_ui.c:6127` `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);`
- `row` (function) `gui/browser_ui.c:6182` `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
- `way` (function) `gui/browser_ui.c:6227` `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...`
- `empty_atom_continues_line` (function) `gui/browser_ui.c:6230` `static int empty_atom_continues_line(const rd_doc *doc, size_t run_i, int box_id);`
- `empty_atom_outer_w` (function) `gui/browser_ui.c:6234` `static double empty_atom_outer_w(const rd_doc *doc, size_t k, const rd_block *bk)` -- Outer width of run k when it is an EMPTY inline-block with a declared width (an icon * atom), 0 otherwise -- the...
- `sized_block_content_w` (function) `gui/browser_ui.c:6254` `static double sized_block_content_w(const rd_doc *doc, const rd_block *bk)` -- The content width a run's OWN block-level box declares in px (CSS 2.1 10.2), or 0 when it declares none, declares a...
- `inside` (function) `gui/browser_ui.c:6271` `* whatever its own items do inside (jkanime's fixed nav: one `<a display:flex>` per
 * entry, mea...`
- `measure_item_w_at` (function) `gui/browser_ui.c:6287` `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
- `width` (function) `gui/browser_ui.c:6327` `* the line: the layout spends its width (reconcile_boxes_below), so the * measure must too, or the label wraps...`
- `lines_at` (function) `gui/browser_ui.c:6361` `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...` -- Lines block b takes when flowed alone at width W (scratch layout, the real * flow_text_block -- so the count cannot...
- `balanced_wrap_width` (function) `gui/browser_ui.c:6379` `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...` -- text-wrap: balance: the narrowest width (to 1px) that keeps the line count the block has at W, for...
- `item_inner_inset` (function) `gui/browser_ui.c:6400` `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)` -- The horizontal padding+border of the boxes that sit INSIDE a flex/grid item, between its text and the item's own...
- `measure_item_content_w` (function) `gui/browser_ui.c:6427` `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
- `run_width_cap` (function) `gui/browser_ui.c:6460` `static double run_width_cap(const rd_block *b, double avail_w)` -- The used width cap of a run / a box: the tighter of its `width` and its * `max-width`, each its own...
- `def_width_cap` (function) `gui/browser_ui.c:6464` `static double def_width_cap(const pv_box_def *d, double avail_w)`
- `def_declared_width` (function) `gui/browser_ui.c:6470` `static double def_declared_width(const pv_box_def *d, double avail_w)` -- A DECLARED width (not a max-width alone), clamped by max-width: what an item's * flex base size is when the author...
- `cont_gap_px` (function) `gui/browser_ui.c:6479` `static double cont_gap_px(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...` -- The column gap of a container in px.
- `item_declared_basis` (function) `gui/browser_ui.c:6486` `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
- `nested_cont_basis` (function) `gui/browser_ui.c:6505` `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...`
- `layout` (function) `gui/browser_ui.c:6572` `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...`
- `flex_item_basis` (function) `gui/browser_ui.c:6586` `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
- `flex_item_min_main` (function) `gui/browser_ui.c:6634` `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...` -- Automatic minimum size of one flex item (CSS Flexbox 4.5), in the same border-box+margin units flex_item_basis...
- `close_all_boxes` (function) `gui/browser_ui.c:6664` `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` -- Defined below with the flat-flow box machinery; a flex/grid item's interior uses the SAME box opening/closing code...
- `it` (function) `gui/browser_ui.c:6687` `* precedes it (CSS 2.1 9.2.2: inline-level wherever it sits);`
- `text_atom_continues_line` (function) `gui/browser_ui.c:6692` `static int text_atom_continues_line(const rd_doc *doc, size_t run_i, int box_id)` -- An inline-block WITH TEXT that opens a line whose line goes on after it: the badge in `<span class=badge>972</span>...
- `deepest_open_on_path` (function) `gui/browser_ui.c:6719` `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);`
- `item_at_level` (function) `gui/browser_ui.c:6726` `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` -- Item index of run `bk` at container level `cid`: the run's own cont_item when it sits directly in cid, otherwise the...
- `child_cont_at_level` (function) `gui/browser_ui.c:6741` `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` -- The container on `bk`'s ancestor chain that is a DIRECT child of cid, or -1 when the run sits directly in cid.
- `cont_in_view` (function) `gui/browser_ui.c:6760` `static int cont_in_view(const rd_doc *doc, int cid)` -- Whether container cid belongs to the layout being built: always on the page; in a Stage-2f sub-view only when its...
- `root_cont_of` (function) `gui/browser_ui.c:6774` `static int root_cont_of(const rd_doc *doc, int cid)`
- `box_under` (function) `gui/browser_ui.c:6785` `static int box_under(const rd_doc *doc, int child, int anc)` -- return 0; } static int root_cont_of(const rd_doc *doc, int cid) { int c = cid; for (int guard = 0; c >= 0 && guard <...
- `root_cont_in` (function) `gui/browser_ui.c:6802` `static int root_cont_in(const rd_doc *doc, int cid, int float_box)` -- root_cont_of, but never climbing OUT of the float founder whose box is float_box: a container laid out inside a...
- `TABLE` (function) `gui/browser_ui.c:6834` `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...`
- `block_is_oof` (function) `gui/browser_ui.c:6846` `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` -- True iff the block lives inside an out-of-flow (absolute/fixed) subtree: Stage 2 positions it separately, so the...
- `item_vmargins` (function) `gui/browser_ui.c:6891` `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...` -- A flex/grid item's vertical margins: its root box's own (author, else the UA sheet's for its element).
- `container_inner_h` (function) `gui/browser_ui.c:6912` `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)` -- A flex/grid container's definite inner (content-box) height: a declared height, or a min-height floor, of its OWN box.
- `band_shared_box` (function) `gui/browser_ui.c:6944` `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);`
- `cont_next_item` (function) `gui/browser_ui.c:6955` `static int cont_next_item(const rd_doc *doc, int cid, size_t end, size_t *k, size_t *e)` -- The next item of container cid at or after *k in [*k, end): returns 1 with [*k, *e) its runs, 0 when none is left.
- `table_item_slot` (function) `gui/browser_ui.c:6972` `static void table_item_slot(const rd_doc *doc, size_t k, int cid, int *row, int *col, int *span)` -- The row/column/colspan page_view stamped on the cell that starts at run k (-1 = not * stamped).
- `table_solve` (function) `gui/browser_ui.c:6994` `static double table_solve(cairo_t *cr, const browser_window *w, const ui_theme *th,
             ...` -- Measures every cell of table cid (runs [b0, b1)) and solves its columns (spec/ table_layout.md).
- `layout_container` (function) `gui/browser_ui.c:7219` `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
- `axis` (function) `gui/browser_ui.c:7362` `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...`
- `slot` (function) `gui/browser_ui.c:7415` `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
- `struct` (function) `gui/browser_ui.c:7566` `* struct (0 = auto);`
- `descriptor` (function) `gui/browser_ui.c:7575` `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);`
- `builds` (function) `gui/browser_ui.c:7819` `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);`
- `flow` (function) `gui/browser_ui.c:7915` `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...`
- `own` (function) `gui/browser_ui.c:7963` `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...`
- `items` (function) `gui/browser_ui.c:8044` `* items (Flexbox 4.2);`
- `multicol_fragment` (function) `gui/browser_ui.c:8226` `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` -- True iff a border/outline style paints a line (solid..outset); none/hidden/unset * paint nothing.
- `box_line_visible` (function) `gui/browser_ui.c:8229` `static int box_line_visible(int style)`
- `col_spend_free_space` (function) `gui/browser_ui.c:8243` `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)` -- The free space of a flex column that flows as block (spec/flex_layout.md, tanda 44), spent when its box closes: the...
- `close_top_box` (function) `gui/browser_ui.c:8288` `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
- `wins` (function) `gui/browser_ui.c:8356` `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
- `rc_box_context` (function) `gui/browser_ui.c:8463` `static void rc_box_context(const rc_state *s, double content_w,
                           double...` -- Content rect (left, width) the current run/box is laid out in: the innermost open * box's, or the page content box...
- `box_margin_top` (function) `gui/browser_ui.c:8490` `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
- `box_margin_bottom` (function) `gui/browser_ui.c:8497` `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
- `children` (function) `gui/browser_ui.c:8507` `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
- `behind` (function) `gui/browser_ui.c:8516` `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...`
- `column` (function) `gui/browser_ui.c:8759` `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
- `box_path_has` (function) `gui/browser_ui.c:8853` `static int box_path_has(const rd_doc *doc, int block_id, int want)` -- Reconciles the open-box stack so it equals block b's box path (root..b->block_id), derived from the box-def...
- `columns` (function) `gui/browser_ui.c:8867` `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
- `float_item_stop` (function) `gui/browser_ui.c:8884` `static int float_item_stop(const rd_doc *doc, const rd_block *bk, int founder_key, int base_stop)` -- The cut for a NESTED float's column inside a multi-float band: the outermost founder's box (and everything above it)...
- `nested_stop` (function) `gui/browser_ui.c:8903` `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)` -- The cut for a nested flow's reconcile: the caller's stop box, or -- when the * enclosing state already holds a...
- `table_box_shrink_width` (function) `gui/browser_ui.c:8914` `static double table_box_shrink_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
  ...` -- The used width of an auto-width table whose own box is `box`: its solved columns, the spacing between them and the...
- `box_shrink_width` (function) `gui/browser_ui.c:8963` `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...` -- Max-content width (px) of the box `box_id` opening at run `start`: the widest line produced by the maximal run of...
- `reconcile_boxes_below` (function) `gui/browser_ui.c:9052` `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
- `treatment` (function) `gui/browser_ui.c:9110` `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...`
- `reconcile_boxes` (function) `gui/browser_ui.c:9202` `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
- `box_path_of` (function) `gui/browser_ui.c:9230` `static int box_path_of(const rd_doc *doc, int block_id, int *out)` -- Box path root..block_id via the box-def parent_id chain (root first), written into * out (bounded by RC_BOX_STACK_MAX).
- `oof_static_xy` (function) `gui/browser_ui.c:9250` `static void oof_static_xy(const rc_state *s, const ui_theme *th, double content_w,
              ...` -- Static position of an out-of-flow run met in the flow (CSS 2.1 10.3.7, 10.6.4): where a `position:static` box would...
- `band_parent_box` (function) `gui/browser_ui.c:9266` `static int band_parent_box(const rd_doc *doc, const rd_block *bk)` -- The box a run's OUTERMOST float founder sits in (its parent box), or -2 when the * founder carries no box of its own...
- `band_common_box_ex` (function) `gui/browser_ui.c:9273` `static int band_common_box_ex(const rd_doc *doc, size_t start, size_t end, int skip_boxless)`
- `band_common_box` (function) `gui/browser_ui.c:9298` `static int band_common_box(const rd_doc *doc, size_t start, size_t end)`
- `context` (function) `gui/browser_ui.c:9357` `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...`
- `block_in_table_caption` (function) `gui/browser_ui.c:9368` `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` -- True when a block sits inside a `display: table-caption` box.
- `path` (function) `gui/browser_ui.c:9389` `* overflow degrades to the old inline path (fail-open: content overlaps or * stacks instead of vanishing). With no...`
- `defer_key_block` (function) `gui/browser_ui.c:9434` `static int defer_key_block(const rd_block *bk)` -- The defer key of one block: its outermost founder id, else its own id (a single-level float is its own column).
- `beside` (function) `gui/browser_ui.c:9588` `* margin: nothing to pull up beside (CSS 2.1 9.5.1 rule 5 -- a float's top is never * above an earlier block). They...`
- `defer_append` (function) `gui/browser_ui.c:9634` `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
- `float_founder_edges` (function) `gui/browser_ui.c:9699` `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)` -- The border+padding a floated founder's box adds around its content: the shrink-to-fit width is the founder's BORDER...
- `defer_col_shrink_w` (function) `gui/browser_ui.c:9714` `static double defer_col_shrink_w(cairo_t *cr, const browser_window *w, const ui_theme *th,
      ...` -- Shrink-to-fit width of an outer float whose content is ONLY floats (a `ul{float:right}` holding `li{float:left}`...
- `defer_flush` (function) `gui/browser_ui.c:9769` `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...` -- Places every deferred column: each lays its inner bands (reused, not forked) at the column's border width, stacked...
- `x` (function) `gui/browser_ui.c:9851` `* reported x is already the BORDER x (the §7c.2 rule);`
- `layout_float_band` (function) `gui/browser_ui.c:10068` `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
- `yet` (function) `gui/browser_ui.c:10547` `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
- `layout_doc` (function) `gui/browser_ui.c:10562` `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
- `chain` (function) `gui/browser_ui.c:10616` `* chain (the box that left the normal flow at this pen position);`
- `anchor` (function) `gui/browser_ui.c:10731` `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...`
- `key` (function) `gui/browser_ui.c:10800` `* founders splits by key (stories, rail, footer nav each take * their column);`
- `inline` (function) `gui/browser_ui.c:10802` `* lays out whole inline (fail-open: today's path). */ if (getenv("FREEDOM_DEFER_DEBUG") != NULL) fprintf(stderr...`
- `have` (function) `gui/browser_ui.c:10837` `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...`
- `standalone` (function) `gui/browser_ui.c:10858` `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...`
- `count` (function) `gui/browser_ui.c:11096` `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
- `approximation` (function) `gui/browser_ui.c:11115` `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
- `margin` (function) `gui/browser_ui.c:11287` `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...`
- `page` (function) `gui/browser_ui.c:11345` `* such a page (Wikipedia's Vector skin) at 1080px, and a page made only of boxes has no
 * in-flo...`
- `position_doc` (function) `gui/browser_ui.c:11364` `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
- `position_boxes` (function) `gui/browser_ui.c:11370` `static void position_boxes(cairo_t *cr, const browser_window *w, double content_w,
              ...`
- `one` (function) `gui/browser_ui.c:11462` `* the padding of the boxes between the text and this one (a padded * `<a display:flex>` entry is as wide as its...`
- `defer_root_of` (function) `gui/browser_ui.c:11552` `static int defer_root_of(const rc_layout *L, int bid)` -- An in-flow positioned subtree that follows an out-of-flow box in the tree paints * above it (CSS 2.1 App E step 8)...
- `defer_wants` (function) `gui/browser_ui.c:11560` `static int defer_wants(const rc_layout *L, int bid, int only_root)` -- Whether an in-flow item owned by box `bid` is painted in the pass that serves `only_root`: -1 is the normal in-flow...
- `input_box_width` (function) `gui/browser_ui.c:11566` `static double input_box_width(double content_w)` -- Whether an in-flow item owned by box `bid` is painted in the pass that serves `only_root`: -1 is the normal in-flow...
- `select_box_width` (function) `gui/browser_ui.c:11570` `static double select_box_width(double content_w)`
- `button_box_width` (function) `gui/browser_ui.c:11575` `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...` -- int r = defer_root_of(L, bid); return (only_root < 0) ?
- `rd_build` (function) `gui/browser_ui.c:12009` `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...`
- `blit_image_box` (function) `gui/browser_ui.c:12024` `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...` -- Blits a decoded image into the (x, y, dw, dh) rect with the block's object-fit, scaling filter and clipping.
- `v_read` (function) `gui/browser_ui.c:12225` `static int v_read(int fd, void *buf, size_t n)` -- EINTR/EAGAIN-safe pipe read — loops until all bytes arrive or hard error.
- `dies` (function) `gui/browser_ui.c:12253` `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
- `audio_spawn` (function) `gui/browser_ui.c:12262` `static void audio_spawn(browser_window *w, int rate, int channels)`
- `descriptors` (function) `gui/browser_ui.c:12276` `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...`
- `audio_mark_dead` (function) `gui/browser_ui.c:12316` `static void audio_mark_dead(browser_window *w)` -- Reaps a dead sink child and advances the rotation so the next spawn tries * the next player.
- `audio_write` (function) `gui/browser_ui.c:12333` `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` -- Best-effort PCM write: whatever does not fit in the pipe is dropped (with PTS pacing the producer runs at ~real...
- `audio_stop` (function) `gui/browser_ui.c:12348` `static void audio_stop(browser_window *w)`
- `again` (function) `gui/browser_ui.c:12357` `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...`
- `video_stop` (function) `gui/browser_ui.c:12404` `static void video_stop(browser_window *w)`
- `video_feed_cancelled` (function) `gui/browser_ui.c:12558` `static int video_feed_cancelled(void *ctx)` -- Fetches a single resource (m3u8 or TS segment) under the full policy gates: impersonation, routing, auth...
- `video_fetch_ex` (function) `gui/browser_ui.c:12564` `static sf_status video_fetch_ex(const char *url, browser_window *w, sf_response *resp,
          ...` -- cancellable: the feeder's fetches stop as soon as the pipeline is torn down (seek, stop), * so the join never waits...
- `video_fetch` (function) `gui/browser_ui.c:12579` `static sf_status video_fetch(const char *url, browser_window *w, sf_response *resp)`
- `video_play` (function) `gui/browser_ui.c:12589` `static int video_play(browser_window *w, const char *m3u8_url)` -- Starts video playback from an m3u8 playlist URL.
- `video_pipeline_up` (function) `gui/browser_ui.c:12663` `static int video_pipeline_up(browser_window *w, size_t start_seg)` -- Spawns the decoder and the feeder thread starting at segment start_seg of the playlist already held in w->video_pl...
- `blocking` (function) `gui/browser_ui.c:12686` `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
- `video_seek_to` (function) `gui/browser_ui.c:12702` `static void video_seek_to(browser_window *w, double t)` -- Seeks to t seconds: the segment containing t is where the feeder restarts (segment * granularity...
- `video_position_s` (function) `gui/browser_ui.c:12710` `static double video_position_s(const browser_window *w)` -- Seeks to t seconds: the segment containing t is where the feeder restarts (segment * granularity...
- `video_toggle_pause` (function) `gui/browser_ui.c:12717` `static void video_toggle_pause(browser_window *w)` -- Pause stops reading the decoder (backpressure stalls decoder and feeder) and drops the * audio sink; resume...
- `video_stop` (function) `gui/browser_ui.c:12732` `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
- `video_draw_rect` (function) `gui/browser_ui.c:12809` `static void video_draw_rect(const browser_window *w, double *x, double *y,
                      ...` -- In fullscreen mode the video occupies the entire viewport (titlebar excluded * when CSD is active); otherwise the...
- `blit_video_frame` (function) `gui/browser_ui.c:12848` `static int blit_video_frame(cairo_t *cr, browser_window *w,
                            double x,...`
- `paint_video_row` (function) `gui/browser_ui.c:12876` `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
- `row_line_slack` (function) `gui/browser_ui.c:12954` `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` -- Free space left on a row's LINE BOX after its last fragment, or a negative/zero value when the line is full.
- `row_align_offset` (function) `gui/browser_ui.c:12966` `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` -- Horizontal shift a row's text gets from author text-align (center/right): the slack between the available width and...
- `upstream` (function) `gui/browser_ui.c:12994` `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
- `box_path` (function) `gui/browser_ui.c:13022` `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` -- One radius for all four corners: the shape every non-border-radius caller * (shadow blur, backdrop clip) still wants.
- `box_shadow_layers` (function) `gui/browser_ui.c:13035` `static int box_shadow_layers(const rc_box *bx, int layers[PV_BSHADOW_LAYERS][6])` -- The box-shadow layers of a box as {dx, dy, blur, spread, color, inset} rows, first on * top; returns how many (0 =...
- `cr_mask_cache` (function) `gui/browser_ui.c:13059` `static mkc_cache *cr_mask_cache(cairo_t *cr)`
- `shadow_mask_surface` (function) `gui/browser_ui.c:13097` `static cairo_surface_t *shadow_mask_surface(mkc_cache *mc, const mkc_key *k)` -- The blurred mask for k as an A8 surface the caller masks with and destroys: from the window's cache when it holds k...
- `paint_box_shadow_layer` (function) `gui/browser_ui.c:13137` `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...`
- `rect` (function) `gui/browser_ui.c:13210` `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...`
- `text` (function) `gui/browser_ui.c:13214` `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
- `grad_stop` (function) `gui/browser_ui.c:13241` `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` -- Stop k of a gradient (spec/css.md, stop alpha): its colour and opacity.
- `bui_grad_color_at` (function) `gui/browser_ui.c:13256` `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...` -- Interpolated gradient color at fraction t (0..1) of the stop run.
- `spaced` (function) `gui/browser_ui.c:13289` `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
- `paint_bg_layer` (function) `gui/browser_ui.c:13322` `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...` -- Paints one background-image layer into the box rect (x,y,w,h) with `radius_c` corners.
- `paint_gradient_fill` (function) `gui/browser_ui.c:13368` `static void paint_gradient_fill(cairo_t *cr, const rc_box *bx, double x, double y,
              ...` -- Fills (x,y,w,h) with the box's gradient (conic, radial or linear), clipped to the rounded * path.
- `paint_gradient_tiled` (function) `gui/browser_ui.c:13415` `static void paint_gradient_tiled(cairo_t *cr, const rc_box *bx, double x, double y,
             ...` -- A gradient with an explicit px background-size repeats as a tile (`radial-gradient(circle, #8a8a934d .8px, #0000...
- `paint_box_decoration` (function) `gui/browser_ui.c:13442` `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
- `layer` (function) `gui/browser_ui.c:13512` `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...`
- `widths` (function) `gui/browser_ui.c:13560` `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
- `cairo_set_dash` (function) `gui/browser_ui.c:13596` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:13599` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:13645` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:13648` `cairo_set_dash(cr, (double[])`
- `convention` (function) `gui/browser_ui.c:13668` `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style...`
- `set_rgb` (function) `gui/browser_ui.c:13682` `set_rgb(cr, (ui_rgb)`
- `cairo_set_dash` (function) `gui/browser_ui.c:13706` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:13709` `cairo_set_dash(cr, (double[])`
- `paint_deco_line` (function) `gui/browser_ui.c:13767` `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...` -- Paints one text-decoration line at a given y.
- `cairo_set_dash` (function) `gui/browser_ui.c:13801` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:13803` `cairo_set_dash(cr, (double[])`
- `identically` (function) `gui/browser_ui.c:13814` `* and the PDF exporter so both render identically (same fonts, colours, emphasis, * links and backgrounds). band_w...`
- `paint_svg_at` (function) `gui/browser_ui.c:13822` `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...` -- Draws one SVG block into an arbitrary rect.
- `replaced_current_color` (function) `gui/browser_ui.c:13842` `static int replaced_current_color(const browser_window *w, const rd_block *blk)` -- Resolves currentColor for a replaced element: the run's own author colour when it has one, else the theme's text...
- `paint_inline_replaced` (function) `gui/browser_ui.c:13851` `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...` -- Resolves currentColor for a replaced element: the run's own author colour when it has one, else the theme's text...
- `exactly` (function) `gui/browser_ui.c:13863` `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...`
- `fip_lower` (function) `gui/browser_ui.c:13890` `static size_t fip_lower(const browser_window *w, uintptr_t addr)` -- Row painting modes: the block-level BAND (a banner or the row's background) and the row's CONTENT.
- `fip_paint_frag` (function) `gui/browser_ui.c:13901` `static void fip_paint_frag(cairo_t *cr, const browser_window *w, const rc_frag *f,
              ...` -- Highlights the parts of fragment f that are matches, behind its glyphs.
- `fip_clear_hits` (function) `gui/browser_ui.c:13922` `static void fip_clear_hits(browser_window *w)`
- `fip_hit_cmp` (function) `gui/browser_ui.c:13933` `static int fip_hit_cmp(const void *a, const void *b)`
- `fip_collect` (function) `gui/browser_ui.c:13939` `static void fip_collect(const rc_layout *L, double dy, ft_piece *p, double *ys, size_t cap,
     ...` -- w->fip_hits = NULL; w->fip_y = NULL; w->fip_nhit = 0; w->fip_total = 0; w->fip_cur = -1; w->fip_trunc = 0; } static...
- `fip_sync` (function) `gui/browser_ui.c:13961` `static void fip_sync(browser_window *w, const rc_layout *L)` -- Recomputes the matches against layout L when the query, the layout or the document * changed.
- `fip_reveal` (function) `gui/browser_ui.c:14011` `static void fip_reveal(browser_window *w, double content_h)` -- } qsort(w->fip_hits, ns, sizeof *w->fip_hits, fip_hit_cmp); for (size_t i = 0; i < nm; ++i) w->fip_y[i] =...
- `paint_content_row` (function) `gui/browser_ui.c:14029` `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
- `paint_content_row_ex` (function) `gui/browser_ui.c:14035` `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
- `bg` (function) `gui/browser_ui.c:14092` `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
- `ov_box_clips` (function) `gui/browser_ui.c:14249` `static int ov_box_clips(const pv_box_def *d)` -- Returns nonzero if a box clips content on either axis (single predicate with * the layout path's close_top_box...
- `ov_collect_chain` (function) `gui/browser_ui.c:14256` `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` -- Walks the ancestor chain of block_id and collects overflow:hidden box IDs * into out[] (outermost first).
- `ov_box_bounds` (function) `gui/browser_ui.c:14277` `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` -- Fills *out (x/top/w/h only) with the UNION of every rc_box fragment carrying block_id bid, returning 1 if any exists.
- `ov_content_rect` (function) `gui/browser_ui.c:14303` `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...` -- Computes the PADDING-box rect (in page coords: y, x, w, h) of a box: the region overflow clips to (CSS Overflow 3...
- `rows` (function) `gui/browser_ui.c:14318` `* RC_IMAGE rows (see its declaration);`
- `fragment` (function) `gui/browser_ui.c:14319` `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
- `box_forms_stacking_context` (function) `gui/browser_ui.c:14374` `static int box_forms_stacking_context(const pv_box_def *def)` -- Does this box need its own offscreen compositing group?
- `bui_skew_tan` (function) `gui/browser_ui.c:14418` `static double bui_skew_tan(int deg)` -- transform (M1.2 translate; M1.2b scale/rotate; M1.2c skew + origin): builds the box's full 2D affine transform...

Next: [API_p3.md](API_p3.md)
