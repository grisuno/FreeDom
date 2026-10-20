# API (page 2 of 11)
Previous: [API.md](API.md)

## gui/browser_ui.c
Depends on: `gui/browser_ui_internal.h`, `include/block_flow.h`, `include/box_blur.h`, `include/box_style.h`, `include/box_tree.h`, `include/browser.h`, `include/compositor.h`, `include/css.h`, `include/css_color.h`, `include/css_gradient.h`, `include/css_mask.h`, `include/css_values.h`, `include/data_url.h`, `include/download.h`, `include/form.h`, `include/frame_clock.h`, `include/freebug.h`, `include/hls.h`, `include/host_conf.h`, `include/hostblock.h`, `include/hostedit.h`, `include/image_decode.h`, `include/interp.h`, `include/js_policy.h`, `include/link_nav.h`, `include/media_decoder.h`, `include/net_realm.h`, `include/pdf_export.h`, `include/prefetch.h`, `include/prefs.h`, `include/profile.h`, `include/render_doc.h`, `include/render_policy.h`, `include/request_policy.h`, `include/secure_fetch.h`, `include/svg_paint.h`, `include/svg_render.h`, `include/tab.h`, `include/text_case.h`, `include/text_shape.h`, `include/textfield.h`, `include/tls_impersonate.h`, `include/ui.h`, `include/url.h`, `include/web_storage.h`, `include/webcaps.h`, `include/webfont.h`, `include/webfont_load.h`, `include/ws_hub.h`, `include/zoom.h`
- `now_ms` (function) `gui/browser_ui.c:162` `static uint64_t now_ms(void)` -- Largest text slice measured/drawn at once (one word, or one clipped label). * Words longer than this are still...
- `offset` (function) `gui/browser_ui.c:172` `* offset (labels and the flag live in one place, no magic indices);`
- `fields` (function) `gui/browser_ui.c:279` `* fields (so the 200+ render/event call sites stay unchanged);`
- `delay` (function) `gui/browser_ui.c:373` `* timer delay (tab_page.next_timer_ms);`
- `main` (function) `gui/browser_ui.c:516` `* * Feeder thread: downloads TS segments and writes them to the decoder pipe * so the main (Wayland) thread never...`
- `gutter` (function) `gui/browser_ui.c:590` `* gutter (content_margin) is intentionally left unzoomed, like a browser's text
 * zoom. The PDF ...`
- `apply_zoom` (function) `gui/browser_ui.c:610` `static void apply_zoom(browser_window *w)` -- Applies a new zoom level: rebuild the theme and repaint.
- `buffer_release` (function) `gui/browser_ui.c:621` `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
- `destroy_buffer` (function) `gui/browser_ui.c:627` `static void destroy_buffer(browser_window *w)`
- `ensure_buffer` (function) `gui/browser_ui.c:633` `static int ensure_buffer(browser_window *w)`
- `read_file` (function) `gui/browser_ui.c:663` `static char *read_file(const char *path, size_t *out_len)`
- `build_file_origin` (function) `gui/browser_ui.c:702` `static int build_file_origin(const char *path_or_url, char *out, size_t outsz)` -- Builds a "file:///<canonical absolute path>" origin from a local path (or passes through a file:// URL's path)....
- `build_host_filter` (function) `gui/browser_ui.c:716` `static hb_set *build_host_filter(void)` -- Builds the host filter from the user's .conf lists.
- `build_js_filter` (function) `gui/browser_ui.c:732` `static hb_set *build_js_filter(void)`
- `build_impersonate_optin` (function) `gui/browser_ui.c:735` `static int build_impersonate_optin(void)` -- No impersonate.conf: third signal is the user flag (FREEDOM_IMPERSONATE=1). * allow.conf AND js.conf AND this flag...
- `freedom_write_dir` (function) `gui/browser_ui.c:744` `static int freedom_write_dir(char *out, size_t cap)` -- The writable Freedom config dir: $FREEDOM_HOSTS_DIR if set, else ~/.config/freedom (created if absent).
- `add_current_host_to_list` (function) `gui/browser_ui.c:769` `static void add_current_host_to_list(browser_window *w, int sel)` -- Appends the current page's host to one of the user's .conf lists (block/allow/js), then reloads the in-memory filter...
- `load_favorites` (function) `gui/browser_ui.c:837` `static void load_favorites(browser_window *w)` -- Concatenates the allow.conf bodies along the same search path build_host_filter uses into one string: the omnibox...
- `omni_refresh` (function) `gui/browser_ui.c:874` `static void omni_refresh(browser_window *w)` -- Recomputes the omnibox autocomplete suggestions for the current URL-bar text.
- `profile_sync` (function) `gui/browser_ui.c:905` `static void profile_sync(browser_window *w)` -- Mirrors the session's persistable choices into w->prefs and seals them to disk.
- `remember_visit` (function) `gui/browser_ui.c:922` `static void remember_visit(browser_window *w, const char *url)` -- Records a committed navigation in the persistent history (dedup + cap live in prefs).
- `bookmark_toggle_current` (function) `gui/browser_ui.c:930` `static void bookmark_toggle_current(browser_window *w)` -- Records a committed navigation in the persistent history (dedup + cap live in prefs).
- `proxy_addr_from_env` (function) `gui/browser_ui.c:954` `static int proxy_addr_from_env(const char *envname, const char *deflt,
                          ...` -- Copies a proxy "host:port" into dst: if the env value is unset/empty the default is used; the literal "1" also means...
- `proxy` (function) `gui/browser_ui.c:965` `* and enable each proxy ("1" => the default port);`
- `init_net_config` (function) `gui/browser_ui.c:968` `static void init_net_config(browser_window *w)` -- Builds the Tor/I2P routing config from the environment (Privacy by Default: opt-in, everything off unless explicitly...
- `is_https_url` (function) `gui/browser_ui.c:978` `static int is_https_url(const char *s)`
- `is_http_url` (function) `gui/browser_ui.c:982` `static int is_http_url(const char *s)`
- `host_from_url` (function) `gui/browser_ui.c:993` `static int host_from_url(const char *url, char *out, size_t outsz)` -- A plain-http URL whose realm self-authenticates (an i2p eepsite today): it is * fetched over the network (through...
- `video_feeder_thread` (function) `gui/browser_ui.c:1020` `static void *video_feeder_thread(void *arg);`
- `toggle_fullscreen` (function) `gui/browser_ui.c:1025` `static void toggle_fullscreen(browser_window *w)` -- Fullscreen toggle: ALT+ENTER switches the window between windowed and * compositor-managed fullscreen.
- `input_is_interactive` (function) `gui/browser_ui.c:1040` `static int input_is_interactive(int input_type)` -- An editable control gets a live text field; submit/button/hidden do not.
- `input_is_editable` (function) `gui/browser_ui.c:1046` `static int input_is_editable(int input_type)`
- `free_inputs` (function) `gui/browser_ui.c:1052` `static void free_inputs(browser_window *w)` -- are not text-editable -- they are tracked via rebuild_inputs so clicks * dispatch to them, but they have no...
- `free_images` (function) `gui/browser_ui.c:1060` `static void free_images(browser_window *w)` -- static int input_is_editable(int input_type) { return input_type == PV_IN_TEXT || input_type == PV_IN_PASSWORD ||...
- `find_bg_image` (function) `gui/browser_ui.c:1099` `static const ui_bg_image *find_bg_image(const browser_window *w, const char *url)` -- The decoded background-image for url (a box's bg_image_url), or NULL when it has none (unset / blocked / failed...
- `box_pad_px` (function) `gui/browser_ui.c:1121` `static double box_pad_px(int px_val, int pct_pm, double cb_w);`
- `replaced_edges` (function) `gui/browser_ui.c:1123` `static repl_edges replaced_edges(const rd_doc *doc, const rd_block *b, double cb_w)`
- `repl_edges_x` (function) `gui/browser_ui.c:1147` `static double repl_edges_x(const repl_edges *e)`
- `repl_edges_y` (function) `gui/browser_ui.c:1151` `static double repl_edges_y(const repl_edges *e)`
- `image_display_size` (function) `gui/browser_ui.c:1185` `static int image_display_size(const browser_window *w, const rd_block *blk,
                     ...`
- `placeholder_display_size` (function) `gui/browser_ui.c:1251` `static int placeholder_display_size(const rd_block *blk, double box_w,
                          ...`
- `rebuild_inputs` (function) `gui/browser_ui.c:1274` `static void rebuild_inputs(browser_window *w)` -- Builds the live editable state for the current doc: one entry per editable * control, seeded with its declared value.
- `find_input_state` (function) `gui/browser_ui.c:1299` `static ui_input_state *find_input_state(browser_window *w, const rd_block *blk)` -- if (w->inputs == NULL) return; /* fail closed: no editable fields, page still shows size_t k = 0; for (size_t i = 0...
- `clear_doc` (function) `gui/browser_ui.c:1307` `static void clear_doc(browser_window *w)` -- Releases the structured render of the previous page (text mode resumes).
- `set_cache` (function) `gui/browser_ui.c:1317` `static void set_cache(browser_window *w, char *html, size_t len, const char *top)` -- Releases the structured render of the previous page (text mode resumes).
- `surface_from_pixels` (function) `gui/browser_ui.c:1328` `static cairo_surface_t *surface_from_pixels(const tab_image *img)` -- Wraps decoded ARGB32 pixels in a Cairo surface the painter can blit.
- `fetch_follow_navigable` (function) `gui/browser_ui.c:1395` `static sf_status fetch_follow_navigable(const char *url, sf_config *cfg,
                        ...` -- Fetches url (following redirects) under cfg's policy, applying two navigability fallbacks in order of decreasing...
- `GET` (function) `gui/browser_ui.c:1431` `* a GET (Zero Trust). cfg->policy is restored before returning. */
static sf_status fetch_post_na...`
- `page_trusted` (function) `gui/browser_ui.c:1470` `static int page_trusted(const browser_window *w);` -- tab_fetch_fn: the trusted parent's policy-checked subresource fetch for page XHR/fetch.
- `gui_subresource_fetch` (function) `gui/browser_ui.c:1472` `static int gui_subresource_fetch(void *vctx, const char *method, const char *url,
               ...`
- `only` (function) `gui/browser_ui.c:1551` `* Trusted pages only (untrusted CSS is still applied by the worker, but its * fonts never reach the parent...`
- `gui_css_sink` (function) `gui/browser_ui.c:1556` `static void gui_css_sink(void *vctx, const char *url,
                         const char *body, ...` -- tab_css_sink_fn: retains each served 2xx CSS body for the @font-face pass.
- `first` (function) `gui/browser_ui.c:1624` `* Navigation: clear the registry first (faces are per document). Untrusted:
 * no-op (fetch NULL)...`
- `hb_is_allowlisted` (function) `gui/browser_ui.c:1688` `&& hb_is_allowlisted(w->hosts, ihost);`
- `proceed` (function) `gui/browser_ui.c:1731` `* may proceed (cfg and pr->allowlisted are then set);`
- `prepare_fetch` (function) `gui/browser_ui.c:1734` `static int prepare_fetch(browser_window *w, const char *url, sf_config *cfg,
                    ...` -- Builds cfg for url and applies the pre-fetch gates.
- `fetch_job_free` (function) `gui/browser_ui.c:1838` `static void fetch_job_free(fetch_job *j)`
- `stream_progress_cb` (function) `gui/browser_ui.c:1858` `static void stream_progress_cb(const uint8_t *body, size_t body_len, void *userdata)` -- Called by the fetch thread (~1/sec) with the downloaded body so far.
- `fetch_thread` (function) `gui/browser_ui.c:1882` `static void *fetch_thread(void *arg)` -- Worker body: runs the (blocking) policy-enforcing fetch, then posts the job pointer back to the event loop.
- `fetch_launch` (function) `gui/browser_ui.c:1930` `static int fetch_launch(browser_window *w, const char *url, const sf_config *cfg,
               ...` -- Spawns a detached worker to fetch url under cfg (already gated by prepare_fetch).
- `secure_fetch` (function) `gui/browser_ui.c:1982` `* through secure_fetch (Zero Trust);`
- `load_images` (function) `gui/browser_ui.c:2051` `static void load_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)`
- `string` (function) `gui/browser_ui.c:2130` `* or an empty string (unset, blocked, or off by caps.images), so there is no * decision to re-check, unlike...`
- `load_bg_images` (function) `gui/browser_ui.c:2135` `static void load_bg_images(browser_window *w, tab *t, tab_fetch_fn img_fetch, void *fetch_ctx)` -- Fetches and decodes every box's resolved CSS background-image into w->bg_images (2026-07-16, mirrors load_images...
- `do_load` (function) `gui/browser_ui.c:2172` `static void do_load(browser_window *w, const char *url);`
- `tab_new` (function) `gui/browser_ui.c:2177` `static void tab_new(browser_window *w, const char *url);`
- `toggle` (function) `gui/browser_ui.c:2187` `* No network: a capability toggle (images/CSS) re-renders from cache. Does nothing * when there is no cached source...`
- `page_js_host_allowlisted` (function) `gui/browser_ui.c:2198` `static int page_js_host_allowlisted(const browser_window *w)` -- Resolves the JS policy for the current page's host (Secure by Default: off unless the global mode is ON or the host...
- `compute_page_js` (function) `gui/browser_ui.c:2204` `static int compute_page_js(const browser_window *w)`
- `seed_session_cookies` (function) `gui/browser_ui.c:2218` `static void seed_session_cookies(tab *t, int trusted, const char *url)` -- Seeds document.cookie for the next load from the ephemeral network jar (trusted host * only); reset to none...
- `seed_local_storage` (function) `gui/browser_ui.c:2242` `static void seed_local_storage(browser_window *w, tab *t, int trusted)` -- Seeds the next load's localStorage from the window's in-memory store (trusted host * only; cleared otherwise so a...
- `collect_local_storage` (function) `gui/browser_ui.c:2257` `static void collect_local_storage(browser_window *w, const tab_page *page)` -- Takes the page's changed localStorage (already validated by the tab reader) into * the window's store.
- `foldback_session_cookies` (function) `gui/browser_ui.c:2267` `static void foldback_session_cookies(const char *url, const char *jar)` -- Folds a page's document.cookie jar ("a=1; b=2") back into the ephemeral network jar * one pair at a time, so JS-set...
- `drop_repl_worker` (function) `gui/browser_ui.c:2293` `static void drop_repl_worker(browser_window *w)`
- `schedule_js_tick` (function) `gui/browser_ui.c:2307` `static void schedule_js_tick(browser_window *w, int next_ms)` -- Schedules the next JS timer tick from the worker's reported smallest pending delay (tab_page.next_timer_ms; < 0 =...
- `render_current_ex` (function) `gui/browser_ui.c:2317` `static void render_current_ex(browser_window *w, int allow_js_nav)`
- `stylesheets` (function) `gui/browser_ui.c:2337` `* External stylesheets (Hito 27) follow the author-styles opt-in -- or the * trusted-host doctrine (Hito 28)...`
- `body` (function) `gui/browser_ui.c:2369` `* every served CSS body (serial and pool paths alike). */ font_stash_reset(w);`
- `ALIVE` (function) `gui/browser_ui.c:2476` `* keep the worker ALIVE (tab_worker) so the console REPL can tab_eval against this * live page. The next render (or...`
- `render_current` (function) `gui/browser_ui.c:2495` `static void render_current(browser_window *w)` -- Real async timers: a fresh load resets the per-page tick budget and schedules * the first OP_TICK from the worker's...
- `show_busy` (function) `gui/browser_ui.c:2502` `static void show_busy(browser_window *w)` -- Marks a request in flight and paints a frame so the spinner appears at once.
- `show_fetch_error` (function) `gui/browser_ui.c:2511` `static void show_fetch_error(browser_window *w, const char *url, sf_status ss,
                  ...` -- Replaces the page with the standard "Failed to load" diagnostic for status ss on url. allowlisted tailors the hint...
- `arrives` (function) `gui/browser_ui.c:2562` `* on screen until the result arrives (deliver_fetch_result renders it). about:blank
 * and local ...`
- `strcmp` (function) `gui/browser_ui.c:2630` `&& strcmp(auth_host_buf, w->auth_host) != 0)`
- `resolve` (function) `gui/browser_ui.c:2664` `* origin so its relative references and local images resolve (confined to the * document's directory) -- a local...`
- `tab_save` (function) `gui/browser_ui.c:2691` `static void tab_save(browser_window *w)` -- Parks the active tab's live state into its slot (a shallow move: the slot and the live fields briefly alias the same...
- `tab_restore` (function) `gui/browser_ui.c:2708` `static void tab_restore(browser_window *w)` -- c->doc = w->doc; c->caps = w->caps; c->scroll = w->scroll; c->content_total_h = w->content_total_h; c->inputs =...
- `free_live_page` (function) `gui/browser_ui.c:2725` `static void free_live_page(browser_window *w)` -- w->doc = c->doc; w->caps = c->caps; w->scroll = c->scroll; w->content_total_h = c->content_total_h; w->inputs =...
- `tab_ctx_release` (function) `gui/browser_ui.c:2736` `static void tab_ctx_release(tab_ctx *c)` -- } /* Frees the LIVE page's owned state (used when closing the foreground tab). static void...
- `tab_switch` (function) `gui/browser_ui.c:2760` `static void tab_switch(browser_window *w, int idx)` -- if (c->bg_images[i].surface != NULL) cairo_surface_destroy(c->bg_images[i].surface); free(c->bg_images[i].url); }...
- `uitab_close` (function) `gui/browser_ui.c:2820` `static void uitab_close(browser_window *w, int idx)` -- if (browser_init(&w->bs) != BROWSER_OK) { browser_set_page(&w->bs, "Freedom", "", 0); } if (url != NULL) {...
- `newtab_x` (function) `gui/browser_ui.c:2862` `static double newtab_x(const browser_window *w)` -- X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge.
- `tab_title` (function) `gui/browser_ui.c:2869` `static const char *tab_title(const browser_window *w, int i)` -- X of the "new tab" (+) button: right after the last tab, clamped to the reserved * slot at the right edge. static...
- `tabbar_top` (function) `gui/browser_ui.c:2885` `static double tabbar_top(const browser_window *w)` -- Top of the tab strip: directly under the client-side titlebar (or at the surface * top under server-side decorations).
- `toolbar_top` (function) `gui/browser_ui.c:2891` `static double toolbar_top(const browser_window *w)` -- Top of the toolbar: under the tab strip, which is always reserved.
- `content_geometry` (function) `gui/browser_ui.c:2898` `static void content_geometry(const browser_window *w, double *top, double *height)` -- The content area rectangle below the toolbar, in surface coordinates.
- `page_side` (function) `gui/browser_ui.c:2924` `static double page_side(const browser_window *w, int side)`
- `content_margin_x` (function) `gui/browser_ui.c:2928` `static double content_margin_x(const browser_window *w)`
- `content_margins_x` (function) `gui/browser_ui.c:2939` `static double content_margins_x(const browser_window *w)` -- return (w->doc != NULL) ?
- `content_width` (function) `gui/browser_ui.c:2944` `static double content_width(const browser_window *w)`
- `html_center_offset` (function) `gui/browser_ui.c:2954` `static double html_center_offset(const browser_window *w)`
- `scrollbar_metrics` (function) `gui/browser_ui.c:2968` `static int scrollbar_metrics(const browser_window *w, double *track_x, double *track_y,
         ...` -- Geometry of the vertical scrollbar in surface coordinates, plus the current thumb position.
- `scrollbar_drag_to` (function) `gui/browser_ui.c:2996` `static void scrollbar_drag_to(browser_window *w)` -- Maps the current pointer Y (less the grab offset) to a scroll offset while the * thumb is being dragged, then repaints.
- `draw_scrollbar` (function) `gui/browser_ui.c:3013` `static void draw_scrollbar(cairo_t *cr, const browser_window *w)` -- Paints the scrollbar track and thumb.
- `window_button_rects` (function) `gui/browser_ui.c:3050` `static void window_button_rects(const browser_window *w, double *min_x, double *max_x, double *cl...`
- `toolbar_rects` (function) `gui/browser_ui.c:3060` `static void toolbar_rects(const browser_window *w,
                          double *back_x, doub...`
- `toolbar_button_at` (function) `gui/browser_ui.c:3075` `static ui_hot toolbar_button_at(const browser_window *w, double px, double py)` -- Which toolbar button (if any) is at (px, py).
- `hot_actionable` (function) `gui/browser_ui.c:3091` `static int hot_actionable(const browser_window *w, ui_hot hot)` -- A hovered button is "actionable" (gets the hand cursor) when clicking it would * do something: Go/menu always...
- `menu_panel_rect` (function) `gui/browser_ui.c:3102` `static void menu_panel_rect(const browser_window *w, double *x, double *y,
                      ...` -- The options-menu panel rectangle (below the gear button), and its per-item row * height.
- `ua_box_rect` (function) `gui/browser_ui.c:3118` `static void ua_box_rect(const browser_window *w, double *x, double *y,
                        do...` -- The editable User-Agent box rectangle inside the options panel.
- `draw_text` (function) `gui/browser_ui.c:3128` `static void draw_text(cairo_t *cr, const char *s, double x, double y, int centered)`
- `smaller` (function) `gui/browser_ui.c:3260` `* size when the content is smaller (height) or wider (min-width);`
- `rc_float_bottom` (function) `gui/browser_ui.c:3530` `static double rc_float_bottom(const rc_state *s)` -- Width left for the line after both insets, in the CURRENT box context. rc_float_fit_line uses it to decide whether...
- `rc_float_clear` (function) `gui/browser_ui.c:3539` `static void rc_float_clear(rc_state *s)` -- Ends the float context: drops every exclusion and moves cur_top below the tallest one.
- `rc_float_refresh` (function) `gui/browser_ui.c:3552` `static void rc_float_refresh(rc_state *s, double line_h)` -- Recomputes the open line's float insets for its own cur_top, discarding exclusions the flow has already passed.
- `rc_float_fit_line` (function) `gui/browser_ui.c:3598` `static void rc_float_fit_line(rc_state *s, double line_h)` -- CSS 2.1 9.5: "if there is not enough horizontal room for the line box beside the float, it is shifted downward until...
- `line_limit` (function) `gui/browser_ui.c:3617` `static double line_limit(const rc_state *s, double content_w)` -- The right edge available to the open line: the block's content width minus what a float steals from the right at...
- `rc_free` (function) `gui/browser_ui.c:3625` `static void rc_free(rc_layout *L)`
- `rc_add_box` (function) `gui/browser_ui.c:3645` `static rc_box *rc_add_box(rc_layout *L)`
- `rc_add_frag` (function) `gui/browser_ui.c:3657` `static rc_frag *rc_add_frag(rc_layout *L)`
- `rc_add_row` (function) `gui/browser_ui.c:3672` `static rc_row *rc_add_row(rc_layout *L)`
- `family_face` (function) `gui/browser_ui.c:3684` `static const char *family_face(int family)` -- Maps an author font-family bucket (css_font_family) to a Cairo toy-font family. * The engine matches no exact...
- `HarfBuzz` (function) `gui/browser_ui.c:3695` `* descriptor via HarfBuzz (text_shape);`
- `content_font_ex` (function) `gui/browser_ui.c:3706` `static void content_font_ex(cairo_t *cr, double size, int bold, int italic, int family,
         ...` -- Selects the slice font: the toy face (for the fallback path and chrome) plus the HarfBuzz descriptor the shapers...
- `sites` (function) `gui/browser_ui.c:3719` `* sites (wfh 0, local 0) get the bucket face, which is the toy face's twin. */
    if (wfh != 0u ...`
- `content_font` (function) `gui/browser_ui.c:3728` `static void content_font(cairo_t *cr, double size, int bold, int italic, int family,
            ...`
- `set_rgb_alpha` (function) `gui/browser_ui.c:3735` `static void set_rgb_alpha(cairo_t *cr, ui_rgb c, int opacity)` -- Sets the source color, applying an author opacity (0..100) as an alpha when set * (-1 = fully opaque).
- `utf8_clen` (function) `gui/browser_ui.c:3744` `static size_t utf8_clen(const char *s, size_t n)` -- Bytes in the UTF-8 cluster starting at s[0] (1 for a stray/continuation byte), * clamped to n.
- `draw_slice` (function) `gui/browser_ui.c:3777` `static void draw_slice(cairo_t *cr, double x, double baseline, const char *s, size_t n)` -- Draws a text slice at (x, baseline) in the current content font/source.
- `frag_styled` (function) `gui/browser_ui.c:3790` `static int frag_styled(const rc_frag *f)` -- True if a fragment needs the per-cluster path (text-transform other than none/unset, or a non-zero letter-spacing).
- `styled_advance` (function) `gui/browser_ui.c:3797` `static double styled_advance(cairo_t *cr, const rc_frag *f)` -- Advance (px) of a fragment's text under its text-transform + letter-spacing.
- `styled_draw` (function) `gui/browser_ui.c:3819` `static void styled_draw(cairo_t *cr, double x, double baseline, const rc_frag *f)` -- Draws a fragment's text starting at (x, baseline) under its text-transform + * letter-spacing.
- `block_style` (function) `gui/browser_ui.c:3842` `static void block_style(const ui_theme *th, const rd_block *b,
                        double *si...`
- `block_margins` (function) `gui/browser_ui.c:3870` `static void block_margins(const ui_theme *th, const rd_block *b,
                          double...` -- cb_w is the containing block's content width: a PERCENTAGE vertical margin * resolves against it, not against any...
- `area` (function) `gui/browser_ui.c:3907` `* box spans its CONTENT area (the font's ascent + descent plus its vertical padding
 * and border...`
- `run` (function) `gui/browser_ui.c:3960` `* continuation run (block_id < 0 with no block break) deliberately skips reconcile
 * to stay on ...`
- `flush_line` (function) `gui/browser_ui.c:3974` `static void flush_line(rc_layout *L, rc_state *s, const ui_theme *th)`
- `open_line_height` (function) `gui/browser_ui.c:4041` `static double open_line_height(const rc_state *s, const ui_theme *th)` -- Height the currently open line WILL have when it flushes (same formula flush_line uses): an out-of-flow static...
- `open_line` (function) `gui/browser_ui.c:4056` `static void open_line(rc_layout *L, rc_state *s)`
- `flow_emit_frag` (function) `gui/browser_ui.c:4110` `static void flow_emit_frag(rc_layout *L, rc_state *s, cairo_font_extents_t *fe,
                 ...` -- Emits one fragment at the current pen position, advancing it.
- `flow_smallcaps_word` (function) `gui/browser_ui.c:4170` `static double flow_smallcaps_word(cairo_t *cr, rc_layout *L, rc_state *s,
                       ...` -- One word under synthesized small caps (spec/text_case.md): its lowercase runs are capitals at TC_SMALLCAPS_SCALE of...
- `produced` (function) `gui/browser_ui.c:4204` `* href tags every fragment produced (NULL for non-link runs) so a later hit-test * can recover the click target...`
- `ibx_advance` (function) `gui/browser_ui.c:4225` `static void ibx_advance(const rc_layout *L, rc_state *s, double adv)` -- Advances the pen by the inter-word space `adv` before a word.
- `flow_text` (function) `gui/browser_ui.c:4233` `static void flow_text(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
               ...`
- `line` (function) `gui/browser_ui.c:4303` `* its neighbours on the line (spec/page_view.md "Colapso de espacio en el borde * entre runs"). Read from src, the...`
- `box_path4` (function) `gui/browser_ui.c:4504` `static void box_path4(cairo_t *cr, double x, double y, double w, double h, const double *rc);`
- `input_inline_eligible` (function) `gui/browser_ui.c:4512` `static int input_inline_eligible(const rd_block *b)` -- A native form control (no author box of its own -- one with a box goes through the box engine) is an inline-level...
- `input_inline_size` (function) `gui/browser_ui.c:4526` `static int input_inline_size(cairo_t *cr, const ui_theme *th, const rd_block *b,
                ...` -- The size of a native control in its line: the same widths draw_input_row paints * and the field height the row path...
- `replaced_inline_size` (function) `gui/browser_ui.c:4548` `static int replaced_inline_size(cairo_t *cr, const browser_window *w, const ui_theme *th,
       ...`
- `replaced_is_inline_level` (function) `gui/browser_ui.c:4580` `static int replaced_is_inline_level(const rc_state *s, const rd_block *b)` -- True when a replaced block is INLINE-LEVEL content of the line already being built, rather than a block of its own.
- `block_leaves_flow` (function) `gui/browser_ui.c:4586` `static int block_leaves_flow(const rd_doc *doc, const rd_block *bk);`
- `inlines` (function) `gui/browser_ui.c:4593` `* next run may also be a replaced element without its own break: consecutive
 * atomic inlines (`...`
- `place_inline_replaced` (function) `gui/browser_ui.c:4630` `static int place_inline_replaced(cairo_t *cr, rc_layout *L, rc_state *s, const ui_theme *th,
    ...` -- Places an inline-level replaced element inside the open line as an atomic inline: it advances the pen like a word...
- `css_replaced_box` (function) `gui/browser_ui.c:4715` `static int css_replaced_box(const rd_doc *doc, const rd_block *b, double avail_w,
               ...` -- The box an unavailable replaced element gets from its own CSS: a definite width plus an aspect-ratio (CSS Sizing 4...
- `emit_replaced_row` (function) `gui/browser_ui.c:4724` `static int emit_replaced_row(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
- `block_text_style` (function) `gui/browser_ui.c:4837` `static void block_text_style(const browser_window *w, const ui_theme *th, const rd_block *b,
    ...` -- The text style a block's text is drawn in: the UA style of its kind, the author colour (unless the theme is forced)...
- `flow_text_block` (function) `gui/browser_ui.c:4848` `static void flow_text_block(cairo_t *cr, const browser_window *w, rc_layout *L,
                 ...`
- `run_is_content` (function) `gui/browser_ui.c:5004` `static int run_is_content(const rd_block *bk)` -- Whether a run is real content, as opposed to the empty or whitespace-only placeholder a decorated box with nothing...
- `item_root_box_pass` (function) `gui/browser_ui.c:5014` `static int item_root_box_pass(const rd_doc *doc, size_t b0, size_t b1, int cbox,
                ...`
- `them` (function) `gui/browser_ui.c:5067` `* to them (jkanime's badge-only tiles keep their box). */
static int item_root_box_in(const rd_do...`
- `item_root_box` (function) `gui/browser_ui.c:5088` `static int item_root_box(const rd_doc *doc, size_t b0, size_t b1)` -- Root box of a flex/grid item, bounded by the container box page_view stamped on the item's runs (pv_run.cont_box_id).
- `itself` (function) `gui/browser_ui.c:5096` `* STRETCH itself (box_tree fills the line with it). */
static int css_align_to_bt(int align_kw)`
- `box_edge_px` (function) `gui/browser_ui.c:5107` `static double box_edge_px(int wpx)` -- Maps a css_align_kw (align-items/align-self) to the box_tree cross-axis alignment it drives.
- `rc_box_copy_decoration` (function) `gui/browser_ui.c:5127` `static void rc_box_copy_decoration(rc_box *bx, const pv_box_def *def)` -- Copies a box def's paint-time decoration (borders, radius, shadow, outline, background, gradient, background-image...
- `box_is_strict_descendant` (function) `gui/browser_ui.c:5212` `static int box_is_strict_descendant(const rd_doc *doc, int id, int anc)` -- True iff box `id` is a STRICT descendant of `anc` in the box tree (or anc < 0, * which means "no container box"...
- `item_sides_at_level` (function) `gui/browser_ui.c:5234` `static item_sides item_sides_at_level(const rd_doc *doc, size_t b0, size_t b1,
                  ...` -- item_sides for one item of container `cid`.
- `container_box_of` (function) `gui/browser_ui.c:5291` `static int container_box_of(const rd_doc *doc, size_t start, size_t end, int cid)`
- `table` (function) `gui/browser_ui.c:5313` `* synthesised table (no descriptors to disagree) keeps the stamp. */
        if (cd != NULL && !c...`
- `container` (function) `gui/browser_ui.c:5323` `* were the container (github's tab pill). */ int item = item_at_level(doc, rd_at(doc, k), cid);`
- `row` (function) `gui/browser_ui.c:5378` `* label beside them shrank to one word per row (spec/page_view.md, jkanime/slashdot). */
static d...`
- `way` (function) `gui/browser_ui.c:5423` `* intrinsic box either way (it does not wrap below its own size). */ static int block_leaves_flow(const rd_doc *doc...`
- `measure_item_w_at` (function) `gui/browser_ui.c:5426` `static double measure_item_w_at(cairo_t *cr, const browser_window *w,
                           ...`
- `lines_at` (function) `gui/browser_ui.c:5476` `static size_t lines_at(cairo_t *cr, const browser_window *w, const ui_theme *th,
                ...` -- Lines block b takes when flowed alone at width W (scratch layout, the real * flow_text_block -- so the count cannot...
- `balanced_wrap_width` (function) `gui/browser_ui.c:5494` `static double balanced_wrap_width(cairo_t *cr, const browser_window *w, const ui_theme *th,
     ...` -- text-wrap: balance: the narrowest width (to 1px) that keeps the line count the block has at W, for...
- `item_inner_inset` (function) `gui/browser_ui.c:5515` `static double item_inner_inset(const rd_doc *doc, size_t b0, size_t b1, int root)` -- The horizontal padding+border of the boxes that sit INSIDE a flex/grid item, between its text and the item's own...
- `measure_item_content_w` (function) `gui/browser_ui.c:5542` `static double measure_item_content_w(cairo_t *cr, const browser_window *w,
                      ...`
- `run_width_cap` (function) `gui/browser_ui.c:5575` `static double run_width_cap(const rd_block *b, double avail_w)` -- The used width cap of a run / a box: the tighter of its `width` and its * `max-width`, each its own...
- `def_width_cap` (function) `gui/browser_ui.c:5579` `static double def_width_cap(const pv_box_def *d, double avail_w)`
- `def_declared_width` (function) `gui/browser_ui.c:5585` `static double def_declared_width(const pv_box_def *d, double avail_w)` -- A DECLARED width (not a max-width alone), clamped by max-width: what an item's * flex base size is when the author...
- `item_declared_basis` (function) `gui/browser_ui.c:5590` `static double item_declared_basis(const rd_doc *doc, const item_sides *sd,
                      ...`
- `nested_cont_basis` (function) `gui/browser_ui.c:5604` `static double nested_cont_basis(cairo_t *cr, const browser_window *w,
                           ...` -- Max-content width of a NESTED container acting as one item: the sum of its own items' bases plus its gaps.
- `layout` (function) `gui/browser_ui.c:5664` `* hypothetical size in the real layout (Flexbox 9.2.3). */ if (ibd != NULL && ibd->box_min_w > 0) base =...`
- `flex_item_basis` (function) `gui/browser_ui.c:5678` `static double flex_item_basis(cairo_t *cr, const browser_window *w,
                             ...`
- `flex_item_min_main` (function) `gui/browser_ui.c:5718` `static double flex_item_min_main(cairo_t *cr, const browser_window *w,
                          ...` -- Automatic minimum size of one flex item (CSS Flexbox 4.5), in the same border-box+margin units flex_item_basis...
- `close_all_boxes` (function) `gui/browser_ui.c:5748` `static void close_all_boxes(rc_layout *L, rc_state *s, const ui_theme *th);` -- Defined below with the flat-flow box machinery; a flex/grid item's interior uses the SAME box opening/closing code...
- `deepest_open_on_path` (function) `gui/browser_ui.c:5766` `static int deepest_open_on_path(const rc_state *outer, const rd_doc *doc, int block_id);`
- `item_at_level` (function) `gui/browser_ui.c:5773` `static int item_at_level(const rd_doc *doc, const rd_block *bk, int cid)` -- Item index of run `bk` at container level `cid`: the run's own cont_item when it sits directly in cid, otherwise the...
- `child_cont_at_level` (function) `gui/browser_ui.c:5788` `static int child_cont_at_level(const rd_doc *doc, const rd_block *bk, int cid)` -- The container on `bk`'s ancestor chain that is a DIRECT child of cid, or -1 when the run sits directly in cid.
- `cont_in_view` (function) `gui/browser_ui.c:5807` `static int cont_in_view(const rd_doc *doc, int cid)` -- Whether container cid belongs to the layout being built: always on the page; in a Stage-2f sub-view only when its...
- `root_cont_of` (function) `gui/browser_ui.c:5821` `static int root_cont_of(const rd_doc *doc, int cid)`
- `box_under` (function) `gui/browser_ui.c:5832` `static int box_under(const rd_doc *doc, int child, int anc)` -- return 0; } static int root_cont_of(const rd_doc *doc, int cid) { int c = cid; for (int guard = 0; c >= 0 && guard <...
- `root_cont_in` (function) `gui/browser_ui.c:5849` `static int root_cont_in(const rd_doc *doc, int cid, int float_box)` -- root_cont_of, but never climbing OUT of the float founder whose box is float_box: a container laid out inside a...
- `TABLE` (function) `gui/browser_ui.c:5881` `* container TABLE (rd_cont_at) rather than from the head run, because a container * whose children are all...`
- `block_is_oof` (function) `gui/browser_ui.c:5893` `static int block_is_oof(const rd_doc *doc, const rd_block *bk)` -- True iff the block lives inside an out-of-flow (absolute/fixed) subtree: Stage 2 positions it separately, so the...
- `item_vmargins` (function) `gui/browser_ui.c:5938` `static void item_vmargins(const ui_theme *th, const rd_doc *doc, const pv_box_def *ib,
          ...` -- A flex/grid item's vertical margins: its root box's own (author, else the UA sheet's for its element).
- `container_inner_h` (function) `gui/browser_ui.c:5959` `static double container_inner_h(const rd_doc *doc, const pv_cont_def *cdv, double content_w)` -- A flex/grid container's definite inner (content-box) height: a declared height, or a min-height floor, of its OWN box.
- `band_shared_box` (function) `gui/browser_ui.c:5991` `static int band_shared_box(const rd_doc *doc, const rc_state *s, size_t start, size_t end);`
- `layout_container` (function) `gui/browser_ui.c:5999` `static void layout_container(cairo_t *cr, const browser_window *w, rc_layout *L,
                ...`
- `axis` (function) `gui/browser_ui.c:6142` `* differs: items stack on the vertical main axis (fx_column_place) and align on * the horizontal cross axis...`
- `slot` (function) `gui/browser_ui.c:6195` `* layout slot (item 0 → rightmost, last item → leftmost). */
    if (use_flex && cdv.direction ==...`
- `struct` (function) `gui/browser_ui.c:6341` `* struct (0 = auto);`
- `descriptor` (function) `gui/browser_ui.c:6349` `* placement rides the nested descriptor (spec/grid_areas.md 6). */ int nbc = child_cont_at_level(doc, bk, cid);`
- `path` (function) `gui/browser_ui.c:6394` `*
         * Only a SYNTHESISED table grid takes this path (cdv.is_table), and only when
        ...`
- `builds` (function) `gui/browser_ui.c:6628` `* wraps beside it: the same band the top level builds (spec/float.md). */ const rd_block *fk = rd_at(doc, k);`
- `flow` (function) `gui/browser_ui.c:6705` `* it collapse their vertical margins with each other exactly as in * the main flow (CSS 2.1 8.3.1), and none escapes...`
- `own` (function) `gui/browser_ui.c:6737` `* root box of its own (rb < 0) the walk must still stop at the * container's box, or it re-opens the container (and...`
- `items` (function) `gui/browser_ui.c:6818` `* items (Flexbox 4.2);`
- `multicol_fragment` (function) `gui/browser_ui.c:6983` `static double multicol_fragment(rc_layout *L, const rc_open_box *ob, double content_bottom);` -- True iff a border/outline style paints a line (solid..outset); none/hidden/unset * paint nothing.
- `box_line_visible` (function) `gui/browser_ui.c:6986` `static int box_line_visible(int style)`
- `col_spend_free_space` (function) `gui/browser_ui.c:7000` `static void col_spend_free_space(rc_layout *L, const rc_open_box *ob, double free_px)` -- The free space of a flex column that flows as block (spec/flex_layout.md, tanda 44), spent when its box closes: the...
- `close_top_box` (function) `gui/browser_ui.c:7045` `static void close_top_box(rc_layout *L, rc_state *s, const ui_theme *th)`
- `wins` (function) `gui/browser_ui.c:7110` `* content taller than the ratio still wins (min-height:auto). */
        if (bx->aspect_num > 0 &...`
- `rc_box_context` (function) `gui/browser_ui.c:7195` `static void rc_box_context(const rc_state *s, double content_w,
                           double...` -- Content rect (left, width) the current run/box is laid out in: the innermost open * box's, or the page content box...
- `box_margin_top` (function) `gui/browser_ui.c:7222` `static double box_margin_top(const ui_theme *th, const pv_box_def *def, double cb_w)`
- `box_margin_bottom` (function) `gui/browser_ui.c:7229` `static double box_margin_bottom(const ui_theme *th, const pv_box_def *def, double cb_w)`
- `children` (function) `gui/browser_ui.c:7239` `* own content rect onto the stack so its children (text or nested boxes) place inside
 * it. At t...`
- `behind` (function) `gui/browser_ui.c:7248` `* previous block left behind (CSS 2.1 8.3.1) -- read from the element's cascade, * never a theme constant. The old...`
- `column` (function) `gui/browser_ui.c:7462` `*
 * Returns the height of the tallest column (0 when there is nothing to fragment). */
static do...`
- `box_path_has` (function) `gui/browser_ui.c:7556` `static int box_path_has(const rd_doc *doc, int block_id, int want)` -- Reconciles the open-box stack so it equals block b's box path (root..b->block_id), derived from the box-def...
- `columns` (function) `gui/browser_ui.c:7570` `* each card made 1080px columns (huggingface, github). */
static int deepest_open_on_path(const r...`
- `nested_stop` (function) `gui/browser_ui.c:7584` `static int nested_stop(const rc_state *outer, const rd_doc *doc, int block_id, int stop_at)` -- The cut for a nested flow's reconcile: the caller's stop box, or -- when the * enclosing state already holds a...
- `box_shrink_width` (function) `gui/browser_ui.c:7596` `static double box_shrink_width(cairo_t *cr, const browser_window *w,
                            ...` -- Max-content width (px) of the box `box_id` opening at run `start`: the widest line produced by the maximal run of...
- `reconcile_boxes_below` (function) `gui/browser_ui.c:7672` `static void reconcile_boxes_below(cairo_t *cr, const browser_window *w,
                         ...`
- `treatment` (function) `gui/browser_ui.c:7723` `* block treatment (shrink-wrapped and placed by text-align), which is what a * standalone centred call-to-action...`
- `reconcile_boxes` (function) `gui/browser_ui.c:7788` `static void reconcile_boxes(cairo_t *cr, const browser_window *w,
                            rc_...`
- `box_path_of` (function) `gui/browser_ui.c:7816` `static int box_path_of(const rd_doc *doc, int block_id, int *out)` -- Box path root..block_id via the box-def parent_id chain (root first), written into * out (bounded by RC_BOX_STACK_MAX).
- `band_common_box` (function) `gui/browser_ui.c:7832` `static int band_common_box(const rd_doc *doc, size_t start, size_t end)` -- The innermost box that is an ancestor (or self) of EVERY block in [start, end), via the longest common prefix of...
- `context` (function) `gui/browser_ui.c:7885` `* side by side inside the current box context (spec/float.md). Blocks are grouped by * float_id into items (document...`
- `block_in_table_caption` (function) `gui/browser_ui.c:7896` `static int block_in_table_caption(const rd_doc *doc, const rd_block *b)` -- True when a block sits inside a `display: table-caption` box.
- `defer_key_block` (function) `gui/browser_ui.c:7960` `static int defer_key_block(const rd_block *bk)` -- The defer key of one block: its outermost founder id, else its own id (a single-level float is its own column).
- `defer_append` (function) `gui/browser_ui.c:8122` `static int defer_append(rc_defer *d, int key, int side,
                        int ml, int mlpct...`
- `float_founder_edges` (function) `gui/browser_ui.c:8178` `static double float_founder_edges(const rd_doc *doc, int float_box, double ctx_w)` -- The border+padding a floated founder's box adds around its content: the shrink-to-fit width is the founder's BORDER...
- `defer_flush` (function) `gui/browser_ui.c:8199` `static void defer_flush(cairo_t *cr, const browser_window *w, rc_layout *L,
                     ...` -- Places every deferred column: each lays its inner bands (reused, not forked) at the column's border width, stacked...
- `width` (function) `gui/browser_ui.c:8228` `* box width (an inline-block icon `width:12px` inside the float) is * not the float's. */ double t =...`
- `x` (function) `gui/browser_ui.c:8277` `* reported x is already the BORDER x (the §7c.2 rule);`
- `layout_float_band` (function) `gui/browser_ui.c:8460` `static void layout_float_band(cairo_t *cr, const browser_window *w, rc_layout *L,
               ...`
- `it` (function) `gui/browser_ui.c:8843` `* already sized it (see col_founder_set), so it is not a cap again. */ int fills_column = (si.col_founder_set &&...`
- `yet` (function) `gui/browser_ui.c:8936` `* does not carry yet (WPT flex-abspos-staticpos-*). */
static int runs_share_float(const rd_doc *...`
- `layout_doc` (function) `gui/browser_ui.c:8948` `static void layout_doc(cairo_t *cr, const browser_window *w, double content_w,
                  ...`
- `chain` (function) `gui/browser_ui.c:9002` `* chain (the box that left the normal flow at this pen position);`
- `anchor` (function) `gui/browser_ui.c:9114` `* anchor (spec/float.md §7d.3) exactly like a text block. An * empty/hidden one leaves cur_top untouched, so this is...`
- `key` (function) `gui/browser_ui.c:9174` `* founders splits by key (stories, rail, footer nav each take * their column);`
- `have` (function) `gui/browser_ui.c:9188` `* as they always have (spec/float.md §6b.3). The line still open beside * the previous float is committed first, at...`
- `standalone` (function) `gui/browser_ui.c:9209` `* must not be treated as standalone (which would flush that line and give * the element a row of its own -- R7). */...`
- `count` (function) `gui/browser_ui.c:9408` `* the box count (a hostile parent cycle terminates). */
static int oof_depth(const rd_doc *doc, s...`
- `approximation` (function) `gui/browser_ui.c:9427` `* anchors on the Stage 2d approximation (fail-open: content never vanishes). */
static void oof_s...`
- `margin` (function) `gui/browser_ui.c:9575` `* own left margin (the margin box starts at the anchor point), a right- * anchored one ends at it. Same for the...`
- `position_doc` (function) `gui/browser_ui.c:9628` `static void position_doc(cairo_t *cr, const browser_window *w, double content_w,
                ...`
- `defer_root_of` (function) `gui/browser_ui.c:9801` `static int defer_root_of(const rc_layout *L, int bid)` -- An in-flow positioned subtree that follows an out-of-flow box in the tree paints * above it (CSS 2.1 App E step 8)...
- `defer_wants` (function) `gui/browser_ui.c:9809` `static int defer_wants(const rc_layout *L, int bid, int only_root)` -- Whether an in-flow item owned by box `bid` is painted in the pass that serves `only_root`: -1 is the normal in-flow...
- `input_box_width` (function) `gui/browser_ui.c:9815` `static double input_box_width(double content_w)` -- Whether an in-flow item owned by box `bid` is painted in the pass that serves `only_root`: -1 is the normal in-flow...
- `select_box_width` (function) `gui/browser_ui.c:9819` `static double select_box_width(double content_w)`
- `button_box_width` (function) `gui/browser_ui.c:9824` `static double button_box_width(cairo_t *cr, const ui_theme *th, const rd_block *b,
              ...` -- int r = defer_root_of(L, bid); return (only_root < 0) ?
- `rd_build` (function) `gui/browser_ui.c:10253` `* rd_build (-1 = auto/off -> theme caret). */ if (b->caret_color >= 0 && !w->force_theme) set_rgb(cr...`
- `blit_image_box` (function) `gui/browser_ui.c:10268` `static void blit_image_box(cairo_t *cr, browser_window *w, const rd_block *blk,
                 ...` -- Blits a decoded image into the (x, y, dw, dh) rect with the block's object-fit, scaling filter and clipping.
- `v_read` (function) `gui/browser_ui.c:10459` `static int v_read(int fd, void *buf, size_t n)` -- EINTR/EAGAIN-safe pipe read — loops until all bytes arrive or hard error.
- `dies` (function) `gui/browser_ui.c:10487` `* child dies (exec failed, device busy, daemon absent) is detected on the
 * next PCM write (EPIP...`
- `audio_spawn` (function) `gui/browser_ui.c:10496` `static void audio_spawn(browser_window *w, int rate, int channels)`
- `descriptors` (function) `gui/browser_ui.c:10510` `* descriptors (especially the Wayland display fd) so the sink does * not corrupt the Wayland protocol connection —...`
- `audio_mark_dead` (function) `gui/browser_ui.c:10550` `static void audio_mark_dead(browser_window *w)` -- Reaps a dead sink child and advances the rotation so the next spawn tries * the next player.
- `audio_write` (function) `gui/browser_ui.c:10567` `static void audio_write(browser_window *w, const uint8_t *data, size_t len)` -- Best-effort PCM write: whatever does not fit in the pipe is dropped (with PTS pacing the producer runs at ~real...
- `audio_stop` (function) `gui/browser_ui.c:10582` `static void audio_stop(browser_window *w)`
- `again` (function) `gui/browser_ui.c:10591` `* before a respawn opens it again (the WNOHANG reap left the old * process alive long enough to make the new one...`
- `video_stop` (function) `gui/browser_ui.c:10602` `static void video_stop(browser_window *w)`
- `video_fetch` (function) `gui/browser_ui.c:10780` `static sf_status video_fetch(const char *url, browser_window *w,
                              sf...` -- Fetches a single resource (m3u8 or TS segment) under the full policy gates: impersonation, routing, auth...
- `video_play` (function) `gui/browser_ui.c:10797` `static int video_play(browser_window *w, const char *m3u8_url)` -- Starts video playback from an m3u8 playlist URL.
- `blocking` (function) `gui/browser_ui.c:10878` `* are blocking (POLLIN guaranteed data is available). */ int flags = fcntl(out_fd, F_GETFL, 0);`
- `video_stop` (function) `gui/browser_ui.c:10899` `* each segment loop so a video_stop() in the main thread (which sets it to 0
 * then calls pthrea...`
- `paint_video_row` (function) `gui/browser_ui.c:10953` `static void paint_video_row(cairo_t *cr, browser_window *w, const rd_block *blk,
                ...`
- `row_line_slack` (function) `gui/browser_ui.c:11065` `static double row_line_slack(const rc_layout *L, const rc_row *r, double content_w)` -- Free space left on a row's LINE BOX after its last fragment, or a negative/zero value when the line is full.
- `row_align_offset` (function) `gui/browser_ui.c:11077` `static double row_align_offset(const rc_layout *L, const rc_row *r, double content_w)` -- Horizontal shift a row's text gets from author text-align (center/right): the slack between the available width and...
- `upstream` (function) `gui/browser_ui.c:11105` `* upstream (see spec/css.md). */
static void box_path4(cairo_t *cr, double x, double y, double w,...`
- `box_path` (function) `gui/browser_ui.c:11133` `static void box_path(cairo_t *cr, double x, double y, double w, double h, double r)` -- One radius for all four corners: the shape every non-border-radius caller * (shadow blur, backdrop clip) still wants.
- `paint_box_shadow_layer` (function) `gui/browser_ui.c:11144` `static void paint_box_shadow_layer(cairo_t *cr, double x, double y, double w, double h,
         ...` -- One box-shadow layer {dx, dy, blur, spread, color, inset} around the border box (x, y, w, h, corner radius r).
- `rect` (function) `gui/browser_ui.c:11231` `* across rect (x,y,w,h): the gradient line runs through the rect center, long * enough that the first/last stops...`
- `text` (function) `gui/browser_ui.c:11235` `* fill and gradient text (2026-07-19). */
static cairo_pattern_t *bui_linear_grad(double x, doubl...`
- `grad_stop` (function) `gui/browser_ui.c:11262` `static ui_rgb grad_stop(const int *cols, int nst, int k, double *alpha)` -- Stop k of a gradient (spec/css.md, stop alpha): its colour and opacity.
- `bui_grad_color_at` (function) `gui/browser_ui.c:11277` `static ui_rgb bui_grad_color_at(const int *cols, const int *pos1000, int nst,
                   ...` -- Interpolated gradient color at fraction t (0..1) of the stop run.
- `spaced` (function) `gui/browser_ui.c:11310` `* or evenly spaced (bui_grad_color_at). */
static void bui_paint_conic(cairo_t *cr, double x, dou...`
- `paint_bg_layer` (function) `gui/browser_ui.c:11343` `static void paint_bg_layer(cairo_t *cr, const rc_box *bx, const ui_bg_image *img,
               ...` -- Paints one background-image layer into the box rect (x,y,w,h) with `radius_c` corners.
- `paint_box_decoration` (function) `gui/browser_ui.c:11387` `static void paint_box_decoration(cairo_t *cr, const rc_box *bx, double ox, double oy,
           ...`
- `layer` (function) `gui/browser_ui.c:11483` `* first layer (CSS multi-background: the first declared URL is the topmost) * and OVER bg_rgb/gradient, UNDER the...`
- `widths` (function) `gui/browser_ui.c:11530` `* the outer minus the adjacent border widths (CSS Backgrounds 3 5.2). The straight
     * per-sid...`
- `cairo_set_dash` (function) `gui/browser_ui.c:11566` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:11569` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:11615` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:11618` `cairo_set_dash(cr, (double[])`
- `convention` (function) `gui/browser_ui.c:11638` `* on the 3D bevel convention (light top/left, dark right/bottom). */ int is_3d = (style == CSS_BST_GROOVE || style...`
- `set_rgb` (function) `gui/browser_ui.c:11652` `set_rgb(cr, (ui_rgb)`
- `cairo_set_dash` (function) `gui/browser_ui.c:11676` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:11679` `cairo_set_dash(cr, (double[])`
- `paint_deco_line` (function) `gui/browser_ui.c:11737` `static void paint_deco_line(cairo_t *cr, double x0, double x1, double ly,
                       ...` -- Paints one text-decoration line at a given y.
- `cairo_set_dash` (function) `gui/browser_ui.c:11771` `cairo_set_dash(cr, (double[])`
- `cairo_set_dash` (function) `gui/browser_ui.c:11773` `cairo_set_dash(cr, (double[])`
- `row_owner_block_id` (function) `gui/browser_ui.c:11788` `static int row_owner_block_id(const rc_layout *L, const rc_row *r);` -- Paints one laid-out row at vertical position ry.
- `paint_svg_at` (function) `gui/browser_ui.c:11793` `static void paint_svg_at(cairo_t *cr, const rd_block *blk, int cur,
                         doub...` -- Draws one SVG block into an arbitrary rect.
- `replaced_current_color` (function) `gui/browser_ui.c:11813` `static int replaced_current_color(const browser_window *w, const rd_block *blk)` -- Resolves currentColor for a replaced element: the run's own author colour when it has one, else the theme's text...
- `paint_inline_replaced` (function) `gui/browser_ui.c:11822` `static void paint_inline_replaced(cairo_t *cr, browser_window *w,
                               ...` -- Resolves currentColor for a replaced element: the run's own author colour when it has one, else the theme's text...
- `exactly` (function) `gui/browser_ui.c:11834` `* the resolved size exactly (like the SVG path above): routing through * paint_image_row would re-resolve a % width...`
- `paint_content_row` (function) `gui/browser_ui.c:11867` `static void paint_content_row(cairo_t *cr, browser_window *w, const rc_layout *L,
               ...`
- `paint_content_row_ex` (function) `gui/browser_ui.c:11874` `static void paint_content_row_ex(cairo_t *cr, browser_window *w, const rc_layout *L,
            ...`
- `bg` (function) `gui/browser_ui.c:11930` `* its own DISTINCT bg (an inline span highlight) still paints. */ int own_bid = row_owner_block_id(L, r);`
- `ov_box_clips` (function) `gui/browser_ui.c:12083` `static int ov_box_clips(const pv_box_def *d)` -- Returns nonzero if a box clips content on either axis (single predicate with * the layout path's close_top_box...
- `ov_collect_chain` (function) `gui/browser_ui.c:12090` `static int ov_collect_chain(const rd_doc *doc, int block_id, int *out, int cap)` -- Walks the ancestor chain of block_id and collects overflow:hidden box IDs * into out[] (outermost first).
- `ov_box_bounds` (function) `gui/browser_ui.c:12111` `static int ov_box_bounds(const rc_layout *L, int bid, rc_box *out)` -- Fills *out (x/top/w/h only) with the UNION of every rc_box fragment carrying block_id bid, returning 1 if any exists.
- `ov_content_rect` (function) `gui/browser_ui.c:12135` `static void ov_content_rect(const rc_box *bx, const pv_box_def *d,
                            do...` -- Computes the padding-box content rect (in page coords: y, x, w, h) for a box. * Used as the clip region for...
- `rows` (function) `gui/browser_ui.c:12154` `* RC_IMAGE rows (see its declaration);`
- `fragment` (function) `gui/browser_ui.c:12155` `* first fragment (rc_frag.block_id, stamped at flow_emit_frag time) -- using
 * blk->block_id alo...`
- `box_forms_stacking_context` (function) `gui/browser_ui.c:12210` `static int box_forms_stacking_context(const pv_box_def *def)` -- Does this box need its own offscreen compositing group?
- `bui_skew_tan` (function) `gui/browser_ui.c:12254` `static double bui_skew_tan(int deg)` -- transform (M1.2 translate; M1.2b scale/rotate; M1.2c skew + origin): builds the box's full 2D affine transform...
- `box_transform_matrix` (function) `gui/browser_ui.c:12261` `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
- `bui_blend_operator` (function) `gui/browser_ui.c:12389` `static cairo_operator_t bui_blend_operator(int mix_blend)` -- Maps CSS mix-blend-mode to the Cairo compositing operator used when a box's offscreen group is blended back over its...
- `bui_gaussian_blur_surface` (function) `gui/browser_ui.c:12415` `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)` -- Gaussian blur of a premultiplied ARGB32 surface, standard deviation `sigma` px, in place (CSS Filter Effects 1...
- `bui_paint_backdrop_blur` (function) `gui/browser_ui.c:12451` `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...` -- backdrop-filter: blur (2026-07-19, glassmorphism v1).
- `bui_mask_ref_rect` (function) `gui/browser_ui.c:12520` `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)` -- The layout rect (x, y, w, h) and rc_box of box `ref`, found among the in-flow boxes or the * positioned ones; 0 when...
- `bui_build_mask` (function) `gui/browser_ui.c:12536` `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
- `bui_pop_group_composite` (function) `gui/browser_ui.c:12642` `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...` -- Composites the currently-pushed group back onto cr using def's opacity/mix-blend (the group must already be open via...
- `made` (function) `gui/browser_ui.c:12705` `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...`
- `the` (function) `gui/browser_ui.c:12809` `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...`
- `limits` (function) `gui/browser_ui.c:12894` `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
- `paint_box_decoration_grouped` (function) `gui/browser_ui.c:12963` `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
- `fill` (function) `gui/browser_ui.c:12993` `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...`
- `paint_box_and_direct_rows` (function) `gui/browser_ui.c:13004` `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...` -- (blk->block_id match), together, when the box forms a stacking context -- so a translucent/blended box's background...
- `overflow` (function) `gui/browser_ui.c:13053` `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...`
- `bui_pop_group_composite` (function) `gui/browser_ui.c:13080` `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
- `compositing` (function) `gui/browser_ui.c:13096` `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...`
- `paint_oof_sub` (function) `gui/browser_ui.c:13113` `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...` -- Stage 2f: paints one out-of-flow subtree's own layout at its translation.
- `paint_positioned_one` (function) `gui/browser_ui.c:13151` `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
- `box` (function) `gui/browser_ui.c:13266` `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
- `paint_nested_children` (function) `gui/browser_ui.c:13372` `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...` -- R6: recursively paints child boxes of `parent_id` that form stacking contexts, inside the parent's already-open...
- `bui_pop_group_composite` (function) `gui/browser_ui.c:13395` `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
- `geom_from_layout` (function) `gui/browser_ui.c:13410` `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...` -- One rect per element from a final layout, in document coordinates (spec/js_geom.md): every text fragment under its...
- `publish_geometry` (function) `gui/browser_ui.c:13441` `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...` -- Hands the window's final layout to a TRUSTED page's JS.
- `paint_positioned_layer` (function) `gui/browser_ui.c:13493` `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
- `paint_screen_inflow` (function) `gui/browser_ui.c:13541` `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)` -- Paints the in-flow boxes and rows the pass `only_root` serves (see defer_wants): * -1 = everything that is not...
- `bui_pop_group_composite` (function) `gui/browser_ui.c:13606` `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
- `paint_screen_deferred` (function) `gui/browser_ui.c:13656` `static void paint_screen_deferred(void *ctx, int root)`
- `paint_structured` (function) `gui/browser_ui.c:13660` `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
- `write_doc_pdf` (function) `gui/browser_ui.c:13776` `static long write_doc_pdf(browser_window *w, const char *path)` -- Writes the window's current laid-out document to a vector PDF at `path`, paginated to US Letter.
- `export_pdf` (function) `gui/browser_ui.c:13885` `static void export_pdf(browser_window *w)`
- `paint_png_inflow` (function) `gui/browser_ui.c:13957` `static void paint_png_inflow(const png_flow_ctx *c, int only_root)` -- Paints the in-flow boxes and rows the pass `only_root` serves (see defer_wants): -1 = everything that is not...
- `paint_png_deferred` (function) `gui/browser_ui.c:13986` `static void paint_png_deferred(void *ctx, int root)`
- `write_doc_png` (function) `gui/browser_ui.c:13995` `static long write_doc_png(browser_window *w, const char *path)` -- Writes the window's current laid-out document to a single full-height PNG at `path` (the same layout/paint path as...
- `export_png` (function) `gui/browser_ui.c:14094` `static void export_png(browser_window *w)`
- `caller` (function) `gui/browser_ui.c:14128` `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
- `ui_render_png` (function) `gui/browser_ui.c:14151` `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` -- Headless PNG export (no Wayland; see include/ui.h).
- `origin` (function) `gui/browser_ui.c:14207` `* top_url is the page origin (https or file://);`
- `render_doc_images` (function) `gui/browser_ui.c:14211` `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...` -- Headless PNG/PDF export WITH image decoding (see include/ui.h).
- `ui_render_png_images` (function) `gui/browser_ui.c:14242` `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_render_pdf_images` (function) `gui/browser_ui.c:14248` `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_dump_layout` (function) `gui/browser_ui.c:14263` `ui_status ui_dump_layout(const rd_doc *doc)` -- Headless layout dump: runs the same layout_doc + position_doc pass as the on-screen/PNG renderer and prints the...
- `in` (function) `gui/browser_ui.c:14285` `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
- `link_at_point` (function) `gui/browser_ui.c:14335` `static const char *link_at_point(browser_window *w, double px, double py)`
- `resolve_box_cursor` (function) `gui/browser_ui.c:14426` `static int resolve_box_cursor(const rd_doc *doc, int block_id)` -- First non-unset author `cursor` on block_id's box or an ancestor (nearest wins, like the rest of the box-decoration...
- `box_pointer_events_none` (function) `gui/browser_ui.c:14440` `static int box_pointer_events_none(const rd_doc *doc, int block_id)` -- True when author `pointer-events: none` removes block_id's content from hit-testing (2026-07-10): the nearest box in...
- `cursor_at_point` (function) `gui/browser_ui.c:14456` `static int cursor_at_point(browser_window *w, double px, double py)` -- Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET when outside content / no box sets one.
- `node_at_point` (function) `gui/browser_ui.c:14521` `static dom_node_id node_at_point(browser_window *w, double px, double py)`
- `Firefox` (function) `gui/browser_ui.c:14529` `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
- `frag_at_point` (function) `gui/browser_ui.c:14548` `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
- `reference` (function) `gui/browser_ui.c:14602` `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
- `set_page_url` (function) `gui/browser_ui.c:14621` `static void set_page_url(browser_window *w, const char *url)` -- Makes url the page's base (link/image resolution) without touching the cached * source: after pushState the...
- `ws_apply_ops` (function) `gui/browser_ui.c:14646` `static void ws_apply_ops(browser_window *w, const tab_page *page)` -- Opens/sends/closes the page's WebSockets (trusted host only; spec/js_dom.md 7f).
- `sf_ws_url_check` (function) `gui/browser_ui.c:14654` `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 && hb_check(w->hosts, host) !=...`
- `apply_history_ops` (function) `gui/browser_ui.c:14681` `static void apply_history_ops(browser_window *w, const tab_page *page)` -- Mirrors the page's history.pushState/replaceState into the session history (spec/js_dom.md 7e): same-document...
- `history_step` (function) `gui/browser_ui.c:14693` `static void history_step(browser_window *w, int steps)` -- Moves steps entries through the session history (negative = back).
- `apply_click_result` (function) `gui/browser_ui.c:14726` `static int apply_click_result(browser_window *w, tab_page *page)` -- Applies a click/event/timer result returned by the worker: rebuild the rendered document and refresh inputs/console...
- `memory` (function) `gui/browser_ui.c:14776` `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
- `GET` (function) `gui/browser_ui.c:14870` `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
- `ensure_download_dir` (function) `gui/browser_ui.c:14904` `static int ensure_download_dir(char *out, size_t outsz)` -- Builds ~/Downloads/freedom into out and creates both levels (best effort; an existing directory is fine).
- `write_file_atomic` (function) `gui/browser_ui.c:14919` `static int write_file_atomic(const char *path, const void *bytes, size_t len)` -- Writes len bytes to path with 0600 perms via a temp file + atomic rename (the disk_store convention): a crash...
- `save_download` (function) `gui/browser_ui.c:14941` `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` -- Saves a fetched resource to ~/Downloads/freedom instead of rendering it.
- `save_current_page` (function) `gui/browser_ui.c:14974` `static void save_current_page(browser_window *w)` -- Ctrl+S: save the current page's cached source to ~/Downloads/freedom.
- `deliver_fetch_result` (function) `gui/browser_ui.c:14984` `static void deliver_fetch_result(browser_window *w, fetch_job *j)`

Next: [API_p3.md](API_p3.md)
