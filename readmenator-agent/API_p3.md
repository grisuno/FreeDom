# API (page 3 of 13)
Previous: [API_p2.md](API_p2.md)

## gui/browser_ui.c (continued)
- `box_transform_matrix` (function) `gui/browser_ui.c:14425` `static int box_transform_matrix(const pv_box_def *def, double box_x, double box_y,
              ...`
- `bui_blend_operator` (function) `gui/browser_ui.c:14553` `static cairo_operator_t bui_blend_operator(int mix_blend)` -- Maps CSS mix-blend-mode to the Cairo compositing operator used when a box's offscreen group is blended back over its...
- `bui_gaussian_blur_surface` (function) `gui/browser_ui.c:14579` `static void bui_gaussian_blur_surface(cairo_surface_t *surf, double sigma)` -- Gaussian blur of a premultiplied ARGB32 surface, standard deviation `sigma` px, in place (CSS Filter Effects 1...
- `bui_paint_backdrop_blur` (function) `gui/browser_ui.c:14622` `static void bui_paint_backdrop_blur(cairo_t *cr, const pv_box_def *def,
                         ...` -- backdrop-filter: blur (2026-07-19, glassmorphism v1).
- `bui_mask_ref_rect` (function) `gui/browser_ui.c:14692` `static int bui_mask_ref_rect(const rc_layout *L, int ref, rc_box *out)` -- The layout rect (x, y, w, h) and rc_box of box `ref`, found among the in-flow boxes or the * positioned ones; 0 when...
- `bui_build_mask` (function) `gui/browser_ui.c:14708` `static cairo_surface_t *bui_build_mask(const pv_box_def *def, const rc_box *bx_in,
              ...`
- `bui_pop_group_composite` (function) `gui/browser_ui.c:14824` `static void bui_pop_group_composite(cairo_t *cr, const pv_box_def *def, uint64_t elapsed_ms,
    ...` -- Composites the currently-pushed group back onto cr using def's opacity/mix-blend (the group must already be open via...
- `made` (function) `gui/browser_ui.c:14889` `* its zero channels made (255,255,255,alpha 0) -- an invalid * premultiplied value Cairo composites as ADDITIVE...`
- `the` (function) `gui/browser_ui.c:14993` `* the (already filtered) group with the shadow color, blur it, and * paint it under the group at the declared offset...`
- `limits` (function) `gui/browser_ui.c:15079` `* documents narrower v1 limits (no overflow:hidden, no negative z-index). A box
 * grouped this w...`
- `paint_box_decoration_grouped` (function) `gui/browser_ui.c:15148` `static void paint_box_decoration_grouped(cairo_t *cr, browser_window *w,
                        ...`
- `fill` (function) `gui/browser_ui.c:15178` `* fill (paint_content_row's r->bg_rgb branch) cascades the SAME author * background-color as the box, but paints in...`
- `paint_box_and_direct_rows` (function) `gui/browser_ui.c:15189` `static void paint_box_and_direct_rows(cairo_t *cr, browser_window *w, const rc_layout *L,
       ...` -- (blk->block_id match), together, when the box forms a stacking context -- so a translucent/blended box's background...
- `overflow` (function) `gui/browser_ui.c:15238` `* adding two of them in int was signed overflow (UB, found by UBSan). */ double ox = left + bx->x +...`
- `bui_pop_group_composite` (function) `gui/browser_ui.c:15265` `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
- `compositing` (function) `gui/browser_ui.c:15281` `* * Group compositing (M1.1 increments 3-4): a box that forms a CSS stacking context * (box_forms_stacking_context...`
- `paint_oof_sub` (function) `gui/browser_ui.c:15319` `static void paint_oof_sub(cairo_t *cr, browser_window *w, const rc_oof_sub *sub,
                ...` -- Stage 2f: paints one out-of-flow subtree's own layout at its translation.
- `paint_positioned_one` (function) `gui/browser_ui.c:15357` `static void paint_positioned_one(cairo_t *cr, browser_window *w, const ui_theme *th,
            ...`
- `box` (function) `gui/browser_ui.c:15478` `* content belongs to that box (painted by its own positioned entry). */
    if (sub == NULL)`
- `paint_owned_negz` (function) `gui/browser_ui.c:15583` `static void paint_owned_negz(cairo_t *cr, browser_window *w, rc_layout *L, double left,
         ...` -- Paints the negative-z positioned boxes owned by stacking-context box `owner`, right after * that box's own...
- `paint_nested_children` (function) `gui/browser_ui.c:15599` `static void paint_nested_children(cairo_t *cr, browser_window *w,
                               ...` -- R6: recursively paints child boxes of `parent_id` that form stacking contexts, inside the parent's already-open...
- `bui_pop_group_composite` (function) `gui/browser_ui.c:15622` `bui_pop_group_composite(cr, cdef, now_ms() - w->page_load_mono_ms, &L->boxes[j], left, origin,
  ...`
- `geom_from_layout` (function) `gui/browser_ui.c:15643` `static void geom_from_layout(const rd_doc *doc, const rc_layout *L, double left,
                ...` -- One rect per element from a final layout, in document coordinates (spec/js_geom.md): every text fragment under its...
- `publish_geometry` (function) `gui/browser_ui.c:15674` `static void publish_geometry(browser_window *w, const rc_layout *L, double left,
                ...` -- Hands the window's final layout to a TRUSTED page's JS.
- `defer_root_z` (function) `gui/browser_ui.c:15736` `static int defer_root_z(const rd_doc *doc, size_t root)` -- if (!bx->canvas_bg || bx->bg_rgb < 0 || bx->canvas_done) continue; double a = (bx->bg_alpha != PV_LEN_UNSET) ?
- `defer_root_before` (function) `gui/browser_ui.c:15742` `static int defer_root_before(const rd_doc *doc, const rc_layout *L, size_t a, size_t b)` -- cairo_paint(cr); cairo_restore(cr); bx->canvas_done = 1; return; } } /* The z-index a deferred root paints at (auto...
- `paint_positioned_layer` (function) `gui/browser_ui.c:15748` `static void paint_positioned_layer(cairo_t *cr, browser_window *w, const ui_theme *th,
          ...`
- `flow_box_of` (function) `gui/browser_ui.c:15821` `static const rc_box *flow_box_of(const screen_flow_ctx *c, int bid)` -- Frame index (spec/group_index.md), NULL = full scans (same result, slower): boxes and * rows grouped by deferred...
- `flow_index_build` (function) `gui/browser_ui.c:15835` `static void flow_index_build(screen_flow_ctx *c, void **blob)` -- Builds the frame index into c (spec/group_index.md); on any allocation failure the * index stays NULL and the passes...
- `flow_index_free` (function) `gui/browser_ui.c:15899` `static void flow_index_free(void **blob)`
- `paint_screen_inflow` (function) `gui/browser_ui.c:15908` `static void paint_screen_inflow(const screen_flow_ctx *c, int only_root)` -- Paints the in-flow boxes and rows the pass `only_root` serves (see defer_wants): * -1 = everything that is not...
- `bui_pop_group_composite` (function) `gui/browser_ui.c:15993` `bui_pop_group_composite(cr, def, now_ms() - w->page_load_mono_ms, bx, left, origin,
             ...`
- `lazy_slot` (function) `gui/browser_ui.c:16042` `static ui_image *lazy_slot(browser_window *w, const char *href, size_t *idx)`
- `lazy_load_one` (function) `gui/browser_ui.c:16053` `static void lazy_load_one(browser_window *w, ui_image *slot, const rd_block *b)` -- #define UI_LAZY_PER_PASS 16 #define UI_LAZY_PASSES 4 static ui_image *lazy_slot(browser_window *w, const char *href...
- `once` (function) `gui/browser_ui.c:16108` `* box the layout never placed loads at once (fail open);`
- `load_lazy_bg_images` (function) `gui/browser_ui.c:16109` `static void load_lazy_bg_images(browser_window *w, const rc_layout *L, double origin,
           ...` -- Fetches the deferred CSS background-images whose box is near the viewport (spec/lazy_load.md).
- `paint_screen_deferred` (function) `gui/browser_ui.c:16144` `static void paint_screen_deferred(void *ctx, int root)`
- `gui_prof_now_ms` (function) `gui/browser_ui.c:16149` `static double gui_prof_now_ms(void)` -- slot->nat_w = twin->nat_w; slot->nat_h = twin->nat_h; continue; } fetch_decode_image(w, w->tab_worker...
- `gui_prof_log` (function) `gui/browser_ui.c:16154` `static void gui_prof_log(const char *what, double ms)`
- `layout_key_build` (function) `gui/browser_ui.c:16165` `static void layout_key_build(const browser_window *w, double content_w, double content_h,
       ...` -- Every input layout_doc + position_doc read, observed into k: the document and its serial, the sizes, the whole theme...
- `layout_diff` (function) `gui/browser_ui.c:16209` `static const char *layout_diff(const rc_layout *a, const rc_layout *b)` -- First difference between two layouts of the same inputs, or NULL when they are the same * geometry: the differential...
- `layout_for_frame` (function) `gui/browser_ui.c:16249` `static rc_layout *layout_for_frame(cairo_t *cr, browser_window *w, double content_w,
            ...` -- Lays the document out for this frame and returns the layout to paint: the retained one when every observed input is...
- `layout_cache_free` (function) `gui/browser_ui.c:16290` `static void layout_cache_free(browser_window *w)` -- } rc_free(L); ++w->lc_gen; double prof_t0 = gui_prof_now_ms(); layout_doc(cr, w, content_w, L); double prof_t1 =...
- `frame_undo_restore` (function) `gui/browser_ui.c:16309` `static void frame_undo_restore(rc_layout *L, frame_undo *u)`
- `paint_structured` (function) `gui/browser_ui.c:16320` `static void paint_structured(cairo_t *cr, browser_window *w, double content_top,
                ...`
- `write_doc_pdf` (function) `gui/browser_ui.c:16485` `static long write_doc_pdf(browser_window *w, const char *path)` -- Writes the window's current laid-out document to a vector PDF at `path`, paginated to US Letter.
- `export_pdf` (function) `gui/browser_ui.c:16595` `static void export_pdf(browser_window *w)`
- `ui_render_viewport_w` (function) `gui/browser_ui.c:16650` `int ui_render_viewport_w(void)`
- `paint_png_inflow` (function) `gui/browser_ui.c:16679` `static void paint_png_inflow(const png_flow_ctx *c, int only_root)` -- Paints the in-flow boxes and rows the pass `only_root` serves (see defer_wants): -1 = everything that is not...
- `paint_png_deferred` (function) `gui/browser_ui.c:16716` `static void paint_png_deferred(void *ctx, int root)`
- `write_doc_png` (function) `gui/browser_ui.c:16816` `static long write_doc_png(browser_window *w, const char *path)`
- `render_frame_surface` (function) `gui/browser_ui.c:16828` `static cairo_surface_t *render_frame_surface(const pv_view *view, tab *ft, const char *url,
     ...` -- Renders a frame's document at its box size: a white canvas bw x bh with the page laid out at * that width from the...
- `live_frame_view` (function) `gui/browser_ui.c:16871` `static const pv_view *live_frame_view(const browser_window *w, const char *href, tab **ft,
      ...` -- The live frame document a freedom-frame: block names (NULL when none is loaded): its src * resolves against the top...
- `fill_frame_slot` (function) `gui/browser_ui.c:16885` `static void fill_frame_slot(browser_window *w, const rd_block *b, ui_image *slot,
               ...`
- `refresh_frame_images` (function) `gui/browser_ui.c:16934` `static void refresh_frame_images(browser_window *w)`
- `export_png` (function) `gui/browser_ui.c:16952` `static void export_png(browser_window *w)`
- `caller` (function) `gui/browser_ui.c:16986` `* caller (freedom.c --download-pdf) owns the fetch/parse pipeline and supplies the
 * out_path ve...`
- `ui_render_png` (function) `gui/browser_ui.c:17009` `ui_status ui_render_png(const rd_doc *doc, const char *out_path, long *out_h)` -- Headless PNG export (no Wayland; see include/ui.h).
- `origin` (function) `gui/browser_ui.c:17065` `* top_url is the page origin (https or file://);`
- `render_doc_images` (function) `gui/browser_ui.c:17069` `static ui_status render_doc_images(const rd_doc *doc, tab *t, const char *top_url,
              ...` -- Headless PNG/PDF export WITH image decoding (see include/ui.h).
- `ui_render_png_images` (function) `gui/browser_ui.c:17102` `ui_status ui_render_png_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_render_png_frames` (function) `gui/browser_ui.c:17108` `ui_status ui_render_png_frames(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_render_pdf_images` (function) `gui/browser_ui.c:17114` `ui_status ui_render_pdf_images(const rd_doc *doc, tab *t, const char *top_url,
                  ...`
- `ui_dump_layout` (function) `gui/browser_ui.c:17129` `ui_status ui_dump_layout(const rd_doc *doc)` -- Headless layout dump: runs the same layout_doc + position_doc pass as the on-screen/PNG renderer and prints the...
- `in` (function) `gui/browser_ui.c:17151` `* a line landed in (Stage 3), which no other dump shows. Text stays out (it is * --dump-dom's job);`
- `hit_layout` (function) `gui/browser_ui.c:17209` `static const rc_layout *hit_layout(cairo_t *cr, browser_window *w, double content_w,
            ...`
- `hit_layout_done` (function) `gui/browser_ui.c:17219` `static void hit_layout_done(rc_layout *own, int owned)`
- `link_at_point` (function) `gui/browser_ui.c:17223` `static const char *link_at_point(browser_window *w, double px, double py)`
- `video_at_point` (function) `gui/browser_ui.c:17289` `static const char *video_at_point(browser_window *w, double px, double py,
                      ...` -- The video a click at (px,py) plays, or NULL: a <video> row under the cursor, or a live frame box (an embedded...
- `resolve_box_cursor` (function) `gui/browser_ui.c:17341` `static int resolve_box_cursor(const rd_doc *doc, int block_id)` -- First non-unset author `cursor` on block_id's box or an ancestor (nearest wins, like the rest of the box-decoration...
- `box_pointer_events_none` (function) `gui/browser_ui.c:17355` `static int box_pointer_events_none(const rd_doc *doc, int block_id)` -- True when author `pointer-events: none` removes block_id's content from hit-testing (2026-07-10): the nearest box in...
- `cursor_at_point` (function) `gui/browser_ui.c:17371` `static int cursor_at_point(browser_window *w, double px, double py)` -- Returns the resolved author `cursor` (css_cursor) at (px, py), or CSS_CUR_UNSET when outside content / no box sets one.
- `node_at_point` (function) `gui/browser_ui.c:17437` `static dom_node_id node_at_point(browser_window *w, double px, double py)`
- `Firefox` (function) `gui/browser_ui.c:17445` `* on its face does in Firefox (spec/page_view.md, tanda 40). */
static const rd_block *submit_pro...`
- `frag_at_point` (function) `gui/browser_ui.c:17464` `static dom_node_id frag_at_point(browser_window *w, double px, double py,
                       ...`
- `scroll_to_fragment` (function) `gui/browser_ui.c:17524` `static void scroll_to_fragment(browser_window *w, const char *fragment, const char *push_url,
   ...` -- Scrolls to the indicated part of the document for fragment (spec/anchor.md): the worker resolves it against the live...
- `url_fragment` (function) `gui/browser_ui.c:17563` `static const char *url_fragment(const char *url)` -- cairo_destroy(cr); } tab_anchor_free(&a); if (target < 0.0) { redraw(w); return; } if (animate && w->doc != NULL &&...
- `scroll_to_url_fragment` (function) `gui/browser_ui.c:17570` `static void scroll_to_url_fragment(browser_window *w)` -- A loaded document whose URL carries a fragment opens at its indicated part * (HTML 7.4.6.4), instantly: the page has...
- `frag_hold_check` (function) `gui/browser_ui.c:17585` `static void frag_hold_check(browser_window *w)` -- Called after every frame: re-applies a held fragment when the document height moved * under it, drops the hold once...
- `navigate_fragment` (function) `gui/browser_ui.c:17599` `static void navigate_fragment(browser_window *w, const char *fragment)` -- Same-document fragment navigation (spec/anchor.md 3): the entry being left keeps its * scroll, a new entry is pushed...
- `reference` (function) `gui/browser_ui.c:17625` `* reference (downgrade, foreign scheme, no resolvable base) navigates nowhere:
 * hostile content...`
- `load` (function) `gui/browser_ui.c:17636` `* without a load (spec/anchor.md);`
- `open_link_background` (function) `gui/browser_ui.c:17660` `static void open_link_background(browser_window *w, const char *href)` -- Middle-click / Ctrl+click on a link (Firefox): the target opens in a new tab next to this one that loads in the...
- `set_page_url` (function) `gui/browser_ui.c:17683` `static void set_page_url(browser_window *w, const char *url)` -- Makes url the page's base (link/image resolution) without touching the cached * source: after pushState the...
- `gui_frame_top_msg` (function) `gui/browser_ui.c:17711` `static void gui_frame_top_msg(void *ctx, const char *data, size_t len)` -- fh_top_msg_fn: a frame posted to the top document.
- `frames_drain` (function) `gui/browser_ui.c:17724` `static void frames_drain(browser_window *w)` -- Delivers the queued frame messages to the top document, one at a time.
- `frames_apply` (function) `gui/browser_ui.c:17742` `static void frames_apply(browser_window *w, const tab_page *page)` -- char *m = w->frame_q[0]; memmove(&w->frame_q[0], &w->frame_q[1], (w->frame_qn - 1) * sizeof w->frame_q[0])...
- `ws_apply_ops` (function) `gui/browser_ui.c:17757` `static void ws_apply_ops(browser_window *w, const tab_page *page)`
- `sf_ws_url_check` (function) `gui/browser_ui.c:17767` `&& sf_ws_url_check(op->data) == SF_OK && rp_host_of(op->data, host, sizeof host) == 0 &&...`
- `apply_history_ops` (function) `gui/browser_ui.c:17794` `static void apply_history_ops(browser_window *w, const tab_page *page)` -- Mirrors the page's history.pushState/replaceState into the session history (spec/js_dom.md 7e): same-document...
- `history_step` (function) `gui/browser_ui.c:17806` `static void history_step(browser_window *w, int steps)` -- Moves steps entries through the session history (negative = back).
- `page_render_caps` (function) `gui/browser_ui.c:17844` `static rdp_caps page_render_caps(const browser_window *w)` -- The caps a document of THIS page is rendered with: the user's toggles widened by the host's trust * (webcaps)...
- `wc_render_caps` (function) `gui/browser_ui.c:17845` `return wc_render_caps(wc_derive((wc_input)`
- `apply_click_result` (function) `gui/browser_ui.c:17865` `static int apply_click_result(browser_window *w, tab_page *page)`
- `on_tab_async` (function) `gui/browser_ui.c:17925` `static void on_tab_async(browser_window *w)` -- Completion of the tab's background job (tab_tick_async / tab_geometry_async).
- `gui_quiesce` (function) `gui/browser_ui.c:17945` `static void gui_quiesce(browser_window *w)`
- `memory` (function) `gui/browser_ui.c:17953` `* memory (the href pointer, not its contents, was all the old code preserved). */
static void dis...`
- `vcl_layout` (function) `gui/browser_ui.c:17966` `&& vcl_layout(w->video_rect.x, w->video_rect.y, w->video_rect.w, w->video_rect.h, &g);`
- `GET` (function) `gui/browser_ui.c:18075` `* the network under weaker rules than a GET (Zero Trust). */
static void do_submit_post(browser_w...`
- `ensure_download_dir` (function) `gui/browser_ui.c:18110` `static int ensure_download_dir(char *out, size_t outsz)` -- Builds ~/Downloads/freedom into out and creates both levels (best effort; an existing directory is fine).
- `write_file_atomic` (function) `gui/browser_ui.c:18125` `static int write_file_atomic(const char *path, const void *bytes, size_t len)` -- Writes len bytes to path with 0600 perms via a temp file + atomic rename (the disk_store convention): a crash...
- `save_download` (function) `gui/browser_ui.c:18147` `static void save_download(browser_window *w, const char *url, const char *bytes,
                ...` -- Saves a fetched resource to ~/Downloads/freedom instead of rendering it.
- `save_current_page` (function) `gui/browser_ui.c:18180` `static void save_current_page(browser_window *w)` -- Ctrl+S: save the current page's cached source to ~/Downloads/freedom.
- `deliver_fetch_result` (function) `gui/browser_ui.c:18190` `static void deliver_fetch_result(browser_window *w, fetch_job *j)`
- `drain_fetch_results` (function) `gui/browser_ui.c:18260` `static void drain_fetch_results(browser_window *w)` -- Drains every completed fetch the worker threads have posted (the read end is non-blocking; pointer-sized writes are...
- `toggle_reader` (function) `gui/browser_ui.c:18413` `static void toggle_reader(browser_window *w)` -- Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author...
- `menu_item_checked` (function) `gui/browser_ui.c:18424` `static int menu_item_checked(const browser_window *w, size_t i)` -- Toggles distraction-free (reader) mode and re-renders from cache (no network): the worker drops boilerplate, author...
- `presentation` (function) `gui/browser_ui.c:18444` `* affect presentation (a repaint, which re-runs layout, suffices);`
- `menu_item_toggle` (function) `gui/browser_ui.c:18446` `static void menu_item_toggle(browser_window *w, size_t i)` -- Toggles options-menu item i and applies its effect.
- `draw_menu` (function) `gui/browser_ui.c:18560` `static void draw_menu(cairo_t *cr, browser_window *w)` -- browser_set_status(&w->bs, w->prefs.remember_history ? "History will be remembered (encrypted at rest)." : "History...
- `draw_toast` (function) `gui/browser_ui.c:18696` `static void draw_toast(cairo_t *cr, browser_window *w, double bottom_offset)` -- Draws the transient status toast (a banner near the bottom of the window), * raised by bottom_offset so it stacks...
- `page_identity` (function) `gui/browser_ui.c:18722` `static chl_identity page_identity(const browser_window *w)` -- double bh = fe.height + 2.0 * UI_TOAST_PAD; double bw = te.width + 2.0 * UI_TOAST_PAD; double bx = 2.0 * UI_MARGIN...
- `site_panel_now` (function) `gui/browser_ui.c:18728` `static int site_panel_now(const browser_window *w, sp_panel *p, sp_geom *g)` -- The site identity panel for the page on screen and where it sits (spec/site_panel.md). * Built from live state every...
- `draw_site_panel` (function) `gui/browser_ui.c:18748` `static void draw_site_panel(cairo_t *cr, browser_window *w)`
- `site_panel_act` (function) `gui/browser_ui.c:18756` `static void site_panel_act(browser_window *w, sp_action a)` -- && he_make_line(host, line, sizeof line) == HE_OK; if (sp_build(&f, p) != SP_OK) return 0; chl_layout l =...
- `chrome_view_fill` (function) `gui/browser_ui.c:18763` `static void chrome_view_fill(browser_window *w, const chl_layout *l, const char **titles,
       ...` -- if (!w->site_panel_open) return; sp_panel p; sp_geom g; if (site_panel_now(w, &p, &g)) bui_paint_site_panel(cr...
- `paint_chrome` (function) `gui/browser_ui.c:18794` `static void paint_chrome(cairo_t *cr, browser_window *w)`
- `draw_omnibox` (function) `gui/browser_ui.c:18806` `static void draw_omnibox(cairo_t *cr, browser_window *w)` -- Omnibox autocomplete dropdown: a panel of favorite-host suggestions below the URL bar, drawn as an overlay (on top...
- `draw_findbar` (function) `gui/browser_ui.c:18841` `static void draw_findbar(cairo_t *cr, browser_window *w)` -- double ry = top + UI_OMNI_ROW_H * (double)i; if (i == w->omni_sel) { set_rgb(cr, th->btn_hover_bg)...
- `paint` (function) `gui/browser_ui.c:18856` `static void paint(browser_window *w)`
- `redraw` (function) `gui/browser_ui.c:18961` `static void redraw(browser_window *w)`
- `wm_base_ping` (function) `gui/browser_ui.c:19010` `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
- `xdg_surface_configure` (function) `gui/browser_ui.c:19016` `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (function) `gui/browser_ui.c:19024` `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `resizes` (function) `gui/browser_ui.c:19032` `* when the window resizes (a no-op for the other modes). */ if (w->reader) apply_theme(w);`
- `wl_array_for_each` (function) `gui/browser_ui.c:19040` `wl_array_for_each(st, states)`
- `toplevel_close` (function) `gui/browser_ui.c:19046` `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (function) `gui/browser_ui.c:19055` `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)`
- `set_cursor` (function) `gui/browser_ui.c:19067` `static void set_cursor(browser_window *w, int cur_kind)` -- Applies the appropriate Wayland cursor for the given CSS cursor value. * A no-op when no themed cursor is available...
- `element` (function) `gui/browser_ui.c:19097` `* cursor:pointer element (a JS-driven button/div, not just an <a>) shows the hand
 * even without...`
- `update_hover` (function) `gui/browser_ui.c:19111` `static void update_hover(browser_window *w)` -- The pointer shape: the page's `cursor` when it set one, else a hand over a link or * an actionable chrome part, an...
- `update_hover_inner` (function) `gui/browser_ui.c:19117` `static void update_hover_inner(browser_window *w)`
- `fbw_split_y` (function) `gui/browser_ui.c:19210` `static double fbw_split_y(const freebug_window *fb)` -- int    dragging_split; /* the divider is being dragged int    hover_copy;     /* mouse is over the copy button int...
- `freebug_ensure_buffer` (function) `gui/browser_ui.c:19219` `static int freebug_ensure_buffer(freebug_window *fb)`
- `fbw_level_rgb` (function) `gui/browser_ui.c:19246` `static void fbw_level_rgb(int level, double *r, double *g, double *b)` -- struct wl_shm_pool *pool = wl_shm_create_pool(fb->owner->shm, fd, (int32_t)size); fb->buffer =...
- `fbw_console_lines` (function) `gui/browser_ui.c:19257` `static size_t fbw_console_lines(const fb_buffer *log, int filter)` -- } /* Color for a console level (dark devtools palette). static void fbw_level_rgb(int level, double *r, double *g...
- `fbw_cell_w` (function) `gui/browser_ui.c:19272` `static double fbw_cell_w(cairo_t *cr)` -- size_t lines = 0; for (size_t i = 0; i < fb_buffer_count(log); ++i) { const fb_entry *e = fb_buffer_at(log, i); if...
- `fbw_text_lines` (function) `gui/browser_ui.c:19278` `static size_t fbw_text_lines(const char *t)`
- `fbw_arg_hint` (function) `gui/browser_ui.c:19285` `static const char *fbw_arg_hint(int which)`
- `fbw_paint_tabs` (function) `gui/browser_ui.c:19296` `static void fbw_paint_tabs(cairo_t *cr, const freebug_window *fb)` -- return n; } static const char *fbw_arg_hint(int which) { switch (which) { case FBP_HTML:   return "CSS selector...
- `fbw_paint_pane` (function) `gui/browser_ui.c:19329` `static void fbw_paint_pane(cairo_t *cr, const freebug_window *fb, double y, double split_y)` -- cairo_show_text(cr, fbp_tab_label(t)); } if (fb->tab == FBP_CONSOLE) { char flt[40]; snprintf(flt, sizeof flt...
- `freebug_paint` (function) `gui/browser_ui.c:19360` `static void freebug_paint(freebug_window *fb)`
- `freebug_redraw_fb` (function) `gui/browser_ui.c:19572` `static void freebug_redraw_fb(freebug_window *fb)`
- `freebug_redraw` (function) `gui/browser_ui.c:19581` `static void freebug_redraw(browser_window *w)`
- `freebug_hide` (function) `gui/browser_ui.c:19585` `static void freebug_hide(browser_window *w)`
- `fbw_xdg_surface_configure` (function) `gui/browser_ui.c:19601` `static void fbw_xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `fbw_toplevel_configure` (function) `gui/browser_ui.c:19609` `static void fbw_toplevel_configure(void *data, struct xdg_toplevel *t,
                          ...`
- `fbw_toplevel_close` (function) `gui/browser_ui.c:19618` `static void fbw_toplevel_close(void *data, struct xdg_toplevel *t)`
- `freebug_show` (function) `gui/browser_ui.c:19628` `static void freebug_show(browser_window *w)`
- `freebug_toggle` (function) `gui/browser_ui.c:19658` `static void freebug_toggle(browser_window *w)`
- `freebug_destroy` (function) `gui/browser_ui.c:19663` `static void freebug_destroy(browser_window *w)`
- `freebug_owns_surface` (function) `gui/browser_ui.c:19672` `static int freebug_owns_surface(const browser_window *w, const struct wl_surface *sf)`
- `freebug_is_open` (function) `gui/browser_ui.c:19676` `static int freebug_is_open(const browser_window *w)`
- `freebug_repl_worker` (function) `gui/browser_ui.c:19683` `static tab *freebug_repl_worker(browser_window *w)` -- Returns the live page worker for the REPL, lazily (re)opening one bound to the active page's cache if none is kept...
- `freebug_pane_refresh` (function) `gui/browser_ui.c:19725` `static void freebug_pane_refresh(browser_window *w)` -- Runs the active panel's expression (fb_panes) in the page's REPL worker and stores the text it returns.
- `freebug_set_tab` (function) `gui/browser_ui.c:19762` `static void freebug_set_tab(browser_window *w, int which)` -- Activates `tab`: each tab keeps its own editor text and scroll, so switching back finds the * argument and position...
- `freebug_panes_invalidate` (function) `gui/browser_ui.c:19780` `static void freebug_panes_invalidate(browser_window *w)` -- A new page (or a dropped worker) makes every fetched panel stale: forget them and, when the * window shows one...
- `freebug_eval` (function) `gui/browser_ui.c:19787` `static void freebug_eval(browser_window *w)`
- `freebug_set_editor` (function) `gui/browser_ui.c:19830` `static void freebug_set_editor(freebug_window *fb, const char *s)` -- char out[1100]; int m = snprintf(out, sizeof out, "%s %.1000s", r.is_exception ? "x" : "=", r.value ? r.value...
- `freebug_complete` (function) `gui/browser_ui.c:19838` `static void freebug_complete(browser_window *w)` -- Tab in the console: completes the property path before the cursor.
- `freebug_handle_key` (function) `gui/browser_ui.c:19868` `static void freebug_handle_key(browser_window *w, xkb_keysym_t sym,
                             ...`
- `freebug_pointer_button` (function) `gui/browser_ui.c:19921` `static void freebug_pointer_button(browser_window *w, uint32_t serial,
                          ...`
- `freebug_pointer_motion` (function) `gui/browser_ui.c:19950` `static void freebug_pointer_motion(browser_window *w)`
- `freebug_pointer_axis` (function) `gui/browser_ui.c:19972` `static void freebug_pointer_axis(browser_window *w, wl_fixed_t value)`
- `down` (function) `gui/browser_ui.c:19984` `* defined further down (after dispatch_js_event) but called from ptr_enter/leave * /motion too. */ static void...`
- `ptr_enter` (function) `gui/browser_ui.c:19990` `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
- `ptr_leave` (function) `gui/browser_ui.c:20008` `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (function) `gui/browser_ui.c:20025` `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `stop_loading` (function) `gui/browser_ui.c:20054` `static int stop_loading(browser_window *w)` -- Stop (spec/browser.md 3c): the in-flight navigation is superseded -- its transfer aborts at the next libcurl poll...
- `load_current` (function) `gui/browser_ui.c:20067` `static void load_current(browser_window *w)`
- `go_omnibox` (function) `gui/browser_ui.c:20080` `static void go_omnibox(browser_window *w)` -- Commits the URL bar like a real omnibox: an existing local file is opened as before; otherwise url_omnibox (pure)...
- `ptr_button` (function) `gui/browser_ui.c:20125` `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...`
- `scroll_line_px` (function) `gui/browser_ui.c:20417` `static double scroll_line_px(const browser_window *w)` -- const rd_block *again = NULL; for (size_t i = 0; w->doc != NULL && i < rd_count(w->doc); ++i) { const rd_block *b =...
- `scroll_max` (function) `gui/browser_ui.c:20422` `static double scroll_max(const browser_window *w)` -- } if (again != NULL) submit_form(w, again); } } } redraw(w); } /* One body line of scroll, in pixels (the common...
- `smooth_scroll_step` (function) `gui/browser_ui.c:20438` `static int smooth_scroll_step(browser_window *w)` -- Cancel by observation (spec/smooth_scroll.md): a scroll offset the animation did not write means another path moved...
- `scroll_goal` (function) `gui/browser_ui.c:20449` `static double scroll_goal(browser_window *w)` -- Where the page is heading: a running animation's target, else where it is.
- `scroll_animate_to_ms` (function) `gui/browser_ui.c:20456` `static void scroll_animate_to_ms(browser_window *w, double target, double dur_ms)` -- Scrolls the page to target (clamped to the document) over dur_ms, animated unless * disabled.
- `scroll_animate_to` (function) `gui/browser_ui.c:20474` `static void scroll_animate_to(browser_window *w, double target)`
- `ptr_axis` (function) `gui/browser_ui.c:20478` `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `ptr_frame` (function) `gui/browser_ui.c:20511` `static void ptr_frame(void *d, struct wl_pointer *p)`
- `ptr_axis_source` (function) `gui/browser_ui.c:20517` `static void ptr_axis_source(void *d, struct wl_pointer *p, uint32_t source)` -- dom_node_id nid = node_at_point(w, w->ptr_x, w->ptr_y); if (nid != DOM_NODE_NONE) { dispatch_mouse_event(w, nid...
- `ptr_axis_stop` (function) `gui/browser_ui.c:20522` `static void ptr_axis_stop(void *d, struct wl_pointer *p, uint32_t time, uint32_t axis)`
- `ptr_axis_discrete` (function) `gui/browser_ui.c:20526` `static void ptr_axis_discrete(void *d, struct wl_pointer *p, uint32_t axis, int32_t discrete)`
- `mime_is_text` (function) `gui/browser_ui.c:20545` `static int mime_is_text(const char *mime)` -- .enter = ptr_enter, .leave = ptr_leave, .motion = ptr_motion, .button = ptr_button, .axis = ptr_axis, .frame =...
- `data_offer_source_actions` (function) `gui/browser_ui.c:20563` `static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_offer_action` (function) `gui/browser_ui.c:20566` `static void data_offer_action(void *d, struct wl_data_offer *o, uint32_t a)`
- `data_device_data_offer` (function) `gui/browser_ui.c:20576` `static void data_device_data_offer(void *data, struct wl_data_device *dev,
                      ...` -- } static void data_offer_source_actions(void *d, struct wl_data_offer *o, uint32_t a) { (void)d; (void)o; (void)a; }...
- `data_device_selection` (function) `gui/browser_ui.c:20588` `static void data_device_selection(void *data, struct wl_data_device *dev,
                       ...` -- The clipboard selection changed.
- `data_device_enter` (function) `gui/browser_ui.c:20607` `static void data_device_enter(void *d, struct wl_data_device *dev, uint32_t serial,
             ...` -- wl_data_offer_destroy(w->selection_offer); if (offer == NULL) { w->selection_offer = NULL...
- `data_device_leave` (function) `gui/browser_ui.c:20612` `static void data_device_leave(void *d, struct wl_data_device *dev)`
- `data_device_motion` (function) `gui/browser_ui.c:20613` `static void data_device_motion(void *d, struct wl_data_device *dev, uint32_t t,
                 ...`
- `data_device_drop` (function) `gui/browser_ui.c:20617` `static void data_device_drop(void *d, struct wl_data_device *dev)`
- `data_source_cancelled` (function) `gui/browser_ui.c:20628` `static void data_source_cancelled(void *data, struct wl_data_source *src)` -- wl_fixed_t x, wl_fixed_t y) { (void)d; (void)dev; (void)t; (void)x; (void)y; } static void data_device_drop(void *d...
- `data_source_send` (function) `gui/browser_ui.c:20634` `static void data_source_send(void *data, struct wl_data_source *src,
                            ...` -- .enter = data_device_enter, .leave = data_device_leave, .motion = data_device_motion, .drop = data_device_drop...
- `data_source_target` (function) `gui/browser_ui.c:20647` `static void data_source_target(void *d, struct wl_data_source *s, const char *m)`
- `freebug_copy_console` (function) `gui/browser_ui.c:20659` `static void freebug_copy_console(browser_window *w)` -- Formats the entire Freebug console buffer and places it on the Wayland clipboard, so the user can paste the...
- `loop` (function) `gui/browser_ui.c:20718` `* we return to the event loop (without this, the clipboard offer stays queued * and a paste that follows immediately...`
- `insert_pasted_text` (function) `gui/browser_ui.c:20727` `static void insert_pasted_text(browser_window *w, const char *text, size_t len)` -- Inserts pasted bytes into whichever text target currently has focus (page input, User-Agent box, or the URL bar).
- `clipboard_copy` (function) `gui/browser_ui.c:20793` `static void clipboard_copy(browser_window *w)` -- Ctrl+C: copy the focused field's text (or, with nothing focused, the page address) * to the clipboard by owning a...
- `keyboard_keymap` (function) `gui/browser_ui.c:20843` `static void keyboard_keymap(void *data, struct wl_keyboard *kbd,
                            uint...`
- `keyboard_enter` (function) `gui/browser_ui.c:20864` `static void keyboard_enter(void *d, struct wl_keyboard *kbd, uint32_t s,
                        ...`
- `keyboard_leave` (function) `gui/browser_ui.c:20871` `static void keyboard_leave(void *d, struct wl_keyboard *kbd, uint32_t s, struct wl_surface *sf)`
- `key_sym_to_js_key` (function) `gui/browser_ui.c:20879` `static const char *key_sym_to_js_key(xkb_keysym_t sym)` -- Maps an xkb keysym to a JS event.key string.
- `key_sym_to_keycode` (function) `gui/browser_ui.c:20905` `static int key_sym_to_keycode(xkb_keysym_t sym)` -- Maps an xkb keysym to a JS keyCode number.
- `dispatch_js_event` (function) `gui/browser_ui.c:20930` `static void dispatch_js_event(browser_window *w, dom_node_id node_id,
                           ...` -- Dispatches a JS DOM event to the worker for the given node_id.
- `fip_focus` (function) `gui/browser_ui.c:20987` `static void fip_focus(browser_window *w)`
- `fip_open_bar` (function) `gui/browser_ui.c:20996` `static void fip_open_bar(browser_window *w)` -- tab_page_free(&page); } /* --- Find bar control (spec/find_text.md) --- static void fip_focus(browser_window *w) {...
- `fip_close_bar` (function) `gui/browser_ui.c:21007` `static void fip_close_bar(browser_window *w)`
- `fip_step` (function) `gui/browser_ui.c:21018` `static void fip_step(browser_window *w, int dir)` -- redraw(w); } static void fip_close_bar(browser_window *w) { if (!w->fip_open) return; w->fip_open = 0...
- `fip_edited` (function) `gui/browser_ui.c:21027` `static void fip_edited(browser_window *w)` -- fip_clear_hits(w); redraw(w); } /* Enter / F3 (dir > 0) and Shift+Enter / Shift+F3 (dir < 0). static void...
- `fip_type` (function) `gui/browser_ui.c:21033` `static void fip_type(browser_window *w, const char *s, size_t n)`
- `fip_key` (function) `gui/browser_ui.c:21044` `static int fip_key(browser_window *w, xkb_keysym_t sym, const char *utf8, int n, int ctrl,
      ...` -- redraw(w); } static void fip_type(browser_window *w, const char *s, size_t n) { if (w->fip_selected) {...
- `fip_click` (function) `gui/browser_ui.c:21077` `static int fip_click(browser_window *w, double x, double y)` -- case XKB_KEY_End:   w->fip_selected = 0; tf_end(&w->fip_field);      redraw(w); return 1; default: break; } if (ctrl...
- `fip_hot_at` (function) `gui/browser_ui.c:21092` `static chl_find_part fip_hot_at(const browser_window *w, double x, double y)`
- `handle_key_press` (function) `gui/browser_ui.c:21102` `static void handle_key_press(browser_window *w, xkb_keysym_t sym, const char *utf8,
             ...` -- Performs the effect of a single key press.
- `key_is_repeatable` (function) `gui/browser_ui.c:21500` `static int key_is_repeatable(xkb_keysym_t sym, int n, int ctrl)` -- Keys whose held-down auto-repeat is safe and useful: text editing, cursor motion and scrolling.
- `key_repeat_arm` (function) `gui/browser_ui.c:21516` `static void key_repeat_arm(browser_window *w, uint32_t key)` -- Arms the repeat timer for key: first fire after repeat_delay ms, then every * 1/repeat_rate s.
- `key_repeat_stop` (function) `gui/browser_ui.c:21529` `static void key_repeat_stop(browser_window *w)` -- 1/repeat_rate s.
- `key_repeat_fire` (function) `gui/browser_ui.c:21540` `static void key_repeat_fire(browser_window *w)` -- Re-fires the currently held key.
- `keyboard_key` (function) `gui/browser_ui.c:21554` `static void keyboard_key(void *data, struct wl_keyboard *kbd, uint32_t serial,
                  ...`
- `keyboard_modifiers` (function) `gui/browser_ui.c:21594` `static void keyboard_modifiers(void *data, struct wl_keyboard *kbd, uint32_t s,
                 ...`
- `keyboard_repeat_info` (function) `gui/browser_ui.c:21603` `static void keyboard_repeat_info(void *d, struct wl_keyboard *kbd, int32_t rate, int32_t delay)`
- `seat_caps` (function) `gui/browser_ui.c:21622` `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (function) `gui/browser_ui.c:21633` `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (function) `gui/browser_ui.c:21640` `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
- `registry_remove` (function) `gui/browser_ui.c:21662` `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `gui_is_idle` (function) `gui/browser_ui.c:21675` `static int gui_is_idle(const browser_window *w)` -- The page has nothing left to do: loaded, no background job, no JS tick due, no deferred repaint.
- `gui_timing_step` (function) `gui/browser_ui.c:21686` `static int gui_timing_step(browser_window *w, uint64_t now)` -- Called every loop turn while FREEDOM_GUI_TIMING is set.
- `startup_abort_release` (function) `gui/browser_ui.c:21744` `static void startup_abort_release(browser_window *w)` -- Release what ui_run_browser opened before the window exists (profile, sealed cache, prefs) so a * failed start -- no...
- `absolute_start` (function) `gui/browser_ui.c:21759` `static const char *absolute_start(const char *start, char *abs, size_t cap)` -- A relative local path on the command line becomes its canonical absolute path, as in Firefox: the URL bar, the link...
- `ui_run_browser` (function) `gui/browser_ui.c:21765` `ui_status ui_run_browser(const char *start_url_arg)`
- `saving` (function) `gui/browser_ui.c:21790` `* disables saving (never clobber);`
- `redraws` (function) `gui/browser_ui.c:21891` `* so a large page with frequent redraws (spinner, JS ticks, video frames) * never hits "Data too big for buffer". A...`
- `moves` (function) `gui/browser_ui.c:21904` `* client that stops reading its socket while the pointer moves (spec/wl_guard.md). */ if...`
- `cost` (function) `gui/browser_ui.c:22260` `* measured cost (floor 33 ms = the existing ~30 fps ceiling):
             * cheap pages paint at...`

## gui/browser_ui_internal.h
Depends on: `include/chrome_layout.h`, `include/freedom_config.h`, `include/link_preview.h`, `include/video_controls.h`
Imported by: `gui/browser_ui.c`, `gui/bui_chrome.c`, `gui/bui_mask_img.c`, `gui/bui_theme.c`
- `set_rgb` (function) `gui/browser_ui_internal.h:120` `void set_rgb(cairo_t *cr, ui_rgb c);` -- /* Selectable palettes for the options menu. typedef enum ui_theme_mode { UI_THEME_LIGHT = 0, UI_THEME_DARK...
- `bui_paint_findbar` (function) `gui/browser_ui_internal.h:164` `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v);`
- `bui_chrome_font` (function) `gui/browser_ui_internal.h:166` `void bui_chrome_font(cairo_t *cr, double size);`
- `bui_paint_chrome` (function) `gui/browser_ui_internal.h:168` `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v);` -- const char        *text;        /* query size_t             len, cursor; int                focused; int...
- `bui_url_text_x` (function) `gui/browser_ui_internal.h:171` `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift);` -- X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry the painter and...
- `bui_url_index_at` (function) `gui/browser_ui_internal.h:173` `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x);` -- X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry the painter and...
- `bui_round_rect` (function) `gui/browser_ui_internal.h:175` `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r);` -- X where URL text starts and the horizontal shift keeping the caret visible: * the single geometry the painter and...
- `bui_paint_video_bar` (function) `gui/browser_ui_internal.h:180` `void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos, double total);` -- The browser's player bar over a playing video (spec/video_controls.md), drawn in the * geometry g the pointer...
- `bui_paint_site_panel` (function) `gui/browser_ui_internal.h:184` `void bui_paint_site_panel(cairo_t *cr, const ui_theme *th, const sp_panel *p, const sp_geom *g, int hot_action);` -- The browser's player bar over a playing video (spec/video_controls.md), drawn in the * geometry g the pointer...
- `bui_paint_link_status` (function) `gui/browser_ui_internal.h:191` `double bui_paint_link_status(cairo_t *cr, const ui_theme *th, const lp_preview *p, double left, double right, double...` -- The status strip for the link under the pointer (spec/link_preview.md): bottom-left of the content area [left...
- `bui_link_status_flips` (function) `gui/browser_ui_internal.h:196` `int bui_link_status_flips(const double zone[3], double ptr_x, double ptr_y);` -- Whether the pointer sits over the strip's left placement `zone` (left, top, right) that the * last paint reported...
- `area` (function) `gui/browser_ui_internal.h:201` `* tiled over the mask area (ax, ay, aw, ah) by the layer geometry `geo` (css.h CSS_MG_*, * resolved by...`

## gui/bui_chrome.c
Depends on: `gui/browser_ui_internal.h`
- `bui_round_rect` (function) `gui/bui_chrome.c:35` `void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r)`
- `tab_path` (function) `gui/bui_chrome.c:48` `static void tab_path(cairo_t *cr, chl_rect t, double r)` -- void bui_round_rect(cairo_t *cr, double x, double y, double w, double h, double r) { if (r > w / 2.0) r = w / 2.0...
- `set_rgba` (function) `gui/bui_chrome.c:57` `static void set_rgba(cairo_t *cr, ui_rgb c, double a)`
- `bui_chrome_font` (function) `gui/bui_chrome.c:61` `void bui_chrome_font(cairo_t *cr, double size)`
- `rcx` (function) `gui/bui_chrome.c:66` `static double rcx(chl_rect r)`
- `rcy` (function) `gui/bui_chrome.c:67` `static double rcy(chl_rect r)`
- `icon_stroke` (function) `gui/bui_chrome.c:69` `static void icon_stroke(cairo_t *cr)`
- `icon_arrow` (function) `gui/bui_chrome.c:76` `static void icon_arrow(cairo_t *cr, double cx, double cy, int dir)`
- `icon_reload` (function) `gui/bui_chrome.c:87` `static void icon_reload(cairo_t *cr, double cx, double cy)` -- cairo_stroke(cr); } static void icon_arrow(cairo_t *cr, double cx, double cy, int dir) { double s = 6.0 *...
- `icon_menu` (function) `gui/bui_chrome.c:99` `static void icon_menu(cairo_t *cr, double cx, double cy)`
- `icon_cross` (function) `gui/bui_chrome.c:107` `static void icon_cross(cairo_t *cr, double cx, double cy, double h)`
- `icon_plus` (function) `gui/bui_chrome.c:115` `static void icon_plus(cairo_t *cr, double cx, double cy, double h)`
- `spinner` (function) `gui/bui_chrome.c:123` `static void spinner(cairo_t *cr, ui_rgb c, double cx, double cy, double phase)`
- `glyph_shield` (function) `gui/bui_chrome.c:137` `static void glyph_shield(cairo_t *cr, double cx, double cy, int check, int fill)`
- `glyph_lock` (function) `gui/bui_chrome.c:161` `static void glyph_lock(cairo_t *cr, double cx, double cy)`
- `glyph_warning` (function) `gui/bui_chrome.c:173` `static void glyph_warning(cairo_t *cr, double cx, double cy)`
- `glyph_overlay` (function) `gui/bui_chrome.c:192` `static void glyph_overlay(cairo_t *cr, double cx, double cy)`
- `glyph_page` (function) `gui/bui_chrome.c:200` `static void glyph_page(cairo_t *cr, double cx, double cy)`
- `glyph_info` (function) `gui/bui_chrome.c:210` `static void glyph_info(cairo_t *cr, double cx, double cy)`
- `paint_identity` (function) `gui/bui_chrome.c:220` `static void paint_identity(cairo_t *cr, const bui_chrome_view *v)`
- `star_path` (function) `gui/bui_chrome.c:269` `static void star_path(cairo_t *cr, double cx, double cy, double ro)` -- break; case CHL_ID_INTERNAL: set_rgb(cr, th->url_text_dim); glyph_shield(cr, cx, cy, 0, 0); break; case...
- `paint_star` (function) `gui/bui_chrome.c:280` `static void paint_star(cairo_t *cr, const bui_chrome_view *v)`
- `url_text_end` (function) `gui/bui_chrome.c:302` `static double url_text_end(const bui_chrome_view *v)` -- } star_path(cr, rcx(r), rcy(r), 7.5); if (v->star == 2) { set_rgb(cr, th->accent); cairo_fill_preserve(cr); } else {...
- `utf8_next` (function) `gui/bui_chrome.c:310` `static size_t utf8_next(const char *s, size_t n, size_t i)`
- `text_w` (function) `gui/bui_chrome.c:317` `static double text_w(cairo_t *cr, const char *s, size_t n)`
- `show_n` (function) `gui/bui_chrome.c:327` `static void show_n(cairo_t *cr, const char *s, size_t n)`
- `bui_url_text_x` (function) `gui/bui_chrome.c:335` `double bui_url_text_x(const bui_chrome_view *v, cairo_t *cr, double *shift)`
- `bui_url_index_at` (function) `gui/bui_chrome.c:349` `size_t bui_url_index_at(cairo_t *cr, const bui_chrome_view *v, double x)`
- `paint_url` (function) `gui/bui_chrome.c:386` `static void paint_url(cairo_t *cr, const bui_chrome_view *v)`
- `round_button` (function) `gui/bui_chrome.c:459` `static void round_button(cairo_t *cr, const bui_chrome_view *v, chl_rect r, chl_part part,
      ...`
- `paint_toolbar` (function) `gui/bui_chrome.c:470` `static void paint_toolbar(cairo_t *cr, const bui_chrome_view *v)`
- `tab_title` (function) `gui/bui_chrome.c:489` `static void tab_title(cairo_t *cr, const char *s, ui_rgb c, double alpha,
                      d...` -- round_button(cr, v, l->back, CHL_PART_BACK, v->can_back); icon_arrow(cr, rcx(l->back), rcy(l->back), 1)...
- `icon_side_chevron` (function) `gui/bui_chrome.c:521` `static void icon_side_chevron(cairo_t *cr, double cx, double cy, int dir)` -- double f0 = x1 - BUI_TAB_FADE; if (f0 < x0) f0 = x0; cairo_pattern_t *fade = cairo_pattern_create_linear(f0, 0.0...
- `paint_tabstrip` (function) `gui/bui_chrome.c:554` `static void paint_tabstrip(cairo_t *cr, const bui_chrome_view *v)`
- `bui_paint_chrome` (function) `gui/bui_chrome.c:646` `void bui_paint_chrome(cairo_t *cr, const bui_chrome_view *v)`
- `paint_find_field` (function) `gui/bui_chrome.c:663` `static void paint_find_field(cairo_t *cr, const bui_find_view *v)`
- `find_button` (function) `gui/bui_chrome.c:712` `static void find_button(cairo_t *cr, const bui_find_view *v, chl_rect r, chl_find_part part,
    ...`
- `icon_chevron` (function) `gui/bui_chrome.c:724` `static void icon_chevron(cairo_t *cr, double cx, double cy, int dir)` -- } static void find_button(cairo_t *cr, const bui_find_view *v, chl_rect r, chl_find_part part, int enabled) { if...
- `bui_paint_findbar` (function) `gui/bui_chrome.c:732` `void bui_paint_findbar(cairo_t *cr, const bui_find_view *v)`
- `mix_rgb` (function) `gui/bui_chrome.c:785` `static ui_rgb mix_rgb(ui_rgb a, ui_rgb b, double t)` -- set_rgb(cr, v->total == 0 ? v->th->id_bad : v->th->chrome_text); cairo_move_to(cr, f->count.x, rcy(f->count) +...
- `tone_rgb` (function) `gui/bui_chrome.c:793` `static ui_rgb tone_rgb(const ui_theme *th, sp_tone t)`
- `text_in` (function) `gui/bui_chrome.c:804` `static void text_in(cairo_t *cr, const char *s, double x, double baseline, double w, double top,
...` -- return c; } static ui_rgb tone_rgb(const ui_theme *th, sp_tone t) { switch (t) { case SP_TONE_GOOD: return...
- `bui_paint_site_panel` (function) `gui/bui_chrome.c:815` `void bui_paint_site_panel(cairo_t *cr, const ui_theme *th, const sp_panel *p, const sp_geom *g,
 ...`
- `bui_paint_video_bar` (function) `gui/bui_chrome.c:903` `void bui_paint_video_bar(cairo_t *cr, const vcl_geom *g, int paused, double pos, double total)`
- `bui_link_status_flips` (function) `gui/bui_chrome.c:962` `int bui_link_status_flips(const double zone[3], double ptr_x, double ptr_y)`
- `bui_paint_link_status` (function) `gui/bui_chrome.c:966` `double bui_paint_link_status(cairo_t *cr, const ui_theme *th, const lp_preview *p, double left,
 ...`

## gui/bui_mask_img.c
Depends on: `gui/browser_ui_internal.h`, `include/box_style.h`, `include/css.h`
- `bui_paint_mask_image` (function) `gui/bui_mask_img.c:17` `int bui_paint_mask_image(cairo_t *c, cairo_surface_t *img, int nat_w, int nat_h,
                ...`

## gui/bui_theme.c
Depends on: `gui/browser_ui_internal.h`, `include/css.h`, `include/css_color.h`
- `ui_theme_default` (function) `gui/bui_theme.c:15` `ui_theme ui_theme_default(void)` -- bui_theme — presentation palettes for the Wayland/Cairo GUI.
- `ui_theme_dark` (function) `gui/bui_theme.c:91` `ui_theme ui_theme_dark(void)` -- Dark reading palette.
- `ui_theme_sepia` (function) `gui/bui_theme.c:137` `ui_theme ui_theme_sepia(void)` -- Sepia reading palette: warm paper background and dark-brown ink, easier on the eyes for long-form text.
- `ui_theme_for` (function) `gui/bui_theme.c:189` `ui_theme ui_theme_for(int mode)` -- t.menu_bg        = (ui_rgb){ 0.95, 0.90, 0.80 }; t.menu_border    = (ui_rgb){ 0.55, 0.46, 0.32 }; t.menu_text      =...
- `rgb_from_packed` (function) `gui/bui_theme.c:198` `ui_rgb rgb_from_packed(int packed)` -- t.scrollbar_thumb_hot = (ui_rgb){ 0.44, 0.35, 0.22 }; return t; } /* The single place that maps the theme mode to a...
- `set_rgb` (function) `gui/bui_theme.c:203` `void set_rgb(cairo_t *cr, ui_rgb c)`

## gui/freedom_view.c
Depends on: `include/html_parse.h`, `include/ui.h`
- `main` (function) `gui/freedom_view.c:37` `int main(int argc, char **argv)`

## gui/ui_render.c
Depends on: `include/freedom_config.h`, `include/ui.h`
- `sanitize_utf8_inplace` (function) `gui/ui_render.c:39` `static void sanitize_utf8_inplace(char *s)` -- Rewrites s in place to well-formed UTF-8, replacing any byte that is not part of a valid sequence with '?'....
- `button_rects` (function) `gui/ui_render.c:107` `static void button_rects(const ui_window *w, double *min_x, double *max_x, double *close_x)` -- int    use_csd;    /* draw our own titlebar/controls (compositor has no SSD) int    maximized; double ptr_x, ptr_y...
- `buffer_release` (function) `gui/ui_render.c:115` `static void buffer_release(void *data, struct wl_buffer *wl_buffer)`
- `destroy_buffer` (function) `gui/ui_render.c:122` `static void destroy_buffer(ui_window *w)`
- `ensure_buffer` (function) `gui/ui_render.c:128` `static int ensure_buffer(ui_window *w)`
- `paint` (function) `gui/ui_render.c:159` `static void paint(ui_window *w)`
- `redraw` (function) `gui/ui_render.c:245` `static void redraw(ui_window *w)`
- `wm_base_ping` (function) `gui/ui_render.c:260` `static void wm_base_ping(void *data, struct xdg_wm_base *b, uint32_t serial)`
- `xdg_surface_configure` (function) `gui/ui_render.c:266` `static void xdg_surface_configure(void *data, struct xdg_surface *s, uint32_t serial)`
- `toplevel_configure` (function) `gui/ui_render.c:274` `static void toplevel_configure(void *data, struct xdg_toplevel *t,
                              ...`
- `toplevel_close` (function) `gui/ui_render.c:283` `static void toplevel_close(void *data, struct xdg_toplevel *t)`
- `deco_configure` (function) `gui/ui_render.c:294` `static void deco_configure(void *data, struct zxdg_toplevel_decoration_v1 *d, uint32_t mode)` -- The compositor tells us the actual decoration mode it granted.
- `ptr_enter` (function) `gui/ui_render.c:305` `static void ptr_enter(void *d, struct wl_pointer *p, uint32_t s,
                      struct wl_...`
- `ptr_leave` (function) `gui/ui_render.c:312` `static void ptr_leave(void *d, struct wl_pointer *p, uint32_t s, struct wl_surface *sf)`
- `ptr_motion` (function) `gui/ui_render.c:315` `static void ptr_motion(void *d, struct wl_pointer *p, uint32_t t, wl_fixed_t x, wl_fixed_t y)`
- `ptr_button` (function) `gui/ui_render.c:322` `static void ptr_button(void *d, struct wl_pointer *p, uint32_t serial, uint32_t t,
              ...` -- ui_window *w = (ui_window *)d; w->ptr_x = wl_fixed_to_double(x); w->ptr_y = wl_fixed_to_double(y); } static void...
- `ptr_axis` (function) `gui/ui_render.c:344` `static void ptr_axis(void *data, struct wl_pointer *p, uint32_t time,
                     uint32...`
- `seat_caps` (function) `gui/ui_render.c:367` `static void seat_caps(void *data, struct wl_seat *seat, uint32_t caps)`
- `seat_name` (function) `gui/ui_render.c:376` `static void seat_name(void *d, struct wl_seat *s, const char *name)`
- `registry_global` (function) `gui/ui_render.c:383` `static void registry_global(void *data, struct wl_registry *reg, uint32_t name,
                 ...`
- `registry_remove` (function) `gui/ui_render.c:401` `static void registry_remove(void *d, struct wl_registry *r, uint32_t name)`
- `ui_run_text_view` (function) `gui/ui_render.c:410` `ui_status ui_run_text_view(const char *title, const char *text, size_t text_len)`

## include/anchor.h
Depends on: `include/dom.h`, `include/js_geom.h`
Imported by: `fuzz/fuzz_anchor.c`, `gui/browser_ui.c`, `src/anchor.c`, `src/tab.c`, `tests/test_anchor.c`, `tests/test_tab.c`
- `fit` (function) `include/anchor.h:35` `* result does not fit (out is then "" when cap > 0). */ size_t anc_percent_decode(const char *in, char *out, size_t...`
- `anc_collect` (function) `include/anchor.h:50` `size_t anc_collect(const dom_index *idx, dom_node_id target, dom_node_id *out, size_t cap, size_t *nsub);` -- Writes target and its element subtree in preorder (*nsub handles), then the elements that follow the subtree in tree...
- `anc_target_top` (function) `include/anchor.h:57` `int anc_target_top(const jg_table *g, const dom_node_id *h, size_t n, size_t nsub, double *top);` -- The document offset of the target from a FINISHED geometry table (jg_finish): the smallest y among the rects of h[0...
- `anc_scroll_for` (function) `include/anchor.h:62` `double anc_scroll_for(double top, double max_scroll);` -- The scroll offset that puts top at the top of the viewport, clamped to * [0, max_scroll].

## include/anti_fp.h
Imported by: `include/secure_fetch.h`, `src/anti_fp.c`, `src/identity.c`, `src/js_env.c`, `src/secure_fetch.c`, `src/tab.c`, `tests/test_anti_fp.c`, `tests/test_identity.c`
- `fp_timer_resolution_ms` (function) `include/anti_fp.h:52` `uint64_t fp_timer_resolution_ms(void);`
- `fp_coarsen_time_ms` (function) `include/anti_fp.h:53` `uint64_t fp_coarsen_time_ms(uint64_t raw_ms);`
- `fp_user_agent` (function) `include/anti_fp.h:57` `const char *fp_user_agent(void);`
- `fp_accept_language` (function) `include/anti_fp.h:58` `const char *fp_accept_language(void);`
- `fp_accept_language_header` (function) `include/anti_fp.h:59` `const char *fp_accept_language_header(void);` -- #define FP_SEC_FETCH_DEST_NAV  "document" #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE...
- `fp_timezone` (function) `include/anti_fp.h:60` `const char *fp_timezone(void);` -- #define FP_SEC_FETCH_MODE_NAV  "navigate" #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1"...
- `fp_platform` (function) `include/anti_fp.h:61` `const char *fp_platform(void);` -- #define FP_SEC_FETCH_SITE_NONE "none" #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against...
- `fp_vendor` (function) `include/anti_fp.h:62` `const char *fp_vendor(void);` -- #define FP_SEC_FETCH_USER_ON   "?1" /* --- clocks: coarse granularity against high-resolution timing --- uint64_t...
- `fp_hardware_concurrency` (function) `include/anti_fp.h:63` `int fp_hardware_concurrency(void);` -- /* --- clocks: coarse granularity against high-resolution timing --- uint64_t fp_timer_resolution_ms(void); uint64_t...
- `fp_device_memory_gb` (function) `include/anti_fp.h:64` `int fp_device_memory_gb(void);`
- `properties` (function) `include/anti_fp.h:67` `* Legacy navigator properties (Hito 30b): normalized Firefox values shared by * js_env and the network layer so JS...`
- `fp_app_code_name` (function) `include/anti_fp.h:71` `const char *fp_app_code_name(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_product` (function) `include/anti_fp.h:72` `const char *fp_product(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_app_name` (function) `include/anti_fp.h:73` `const char *fp_app_name(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_product_sub` (function) `include/anti_fp.h:74` `const char *fp_product_sub(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_oscpu` (function) `include/anti_fp.h:75` `const char *fp_oscpu(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_build_id` (function) `include/anti_fp.h:76` `const char *fp_build_id(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_max_touch_points` (function) `include/anti_fp.h:77` `int fp_max_touch_points(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_on_line` (function) `include/anti_fp.h:78` `int fp_on_line(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_cookie_enabled` (function) `include/anti_fp.h:79` `int fp_cookie_enabled(void);` -- Legacy navigator properties (Hito 30b): normalized Firefox values shared by js_env and the network layer so JS and...
- `fp_bucket_screen` (function) `include/anti_fp.h:83` `void fp_bucket_screen(int w, int h, int *out_w, int *out_h);` -- Snaps a screen size to a standard bucket (cuts entropy). out_w/out_h non-NULL. * Picks the largest-area bucket that...
- `fp_perturb` (function) `include/anti_fp.h:88` `void fp_perturb(uint8_t *buf, size_t len, uint64_t session_key);` -- Deterministic per-session readback poisoning (canvas/audio): flips only the least-significant bit of a sparse...
- `domain` (function) `include/anti_fp.h:91` `* registrable domain (eTLD+1). Same (session_key, domain) => same key (poisoning * is stable within a site);`
- `probability` (function) `include/anti_fp.h:93` `* keys with overwhelming probability (canvas/audio noise is not linkable across * sites, defeating cross-origin...`
- `fp_origin_key` (function) `include/anti_fp.h:98` `uint64_t fp_origin_key(uint64_t session_key, const char *registrable_domain);` -- Derives the per-origin readback key from the per-session secret and a site's registrable domain (eTLD+1).

## include/block_flow.h
Imported by: `gui/browser_ui.c`, `src/block_flow.c`, `tests/test_block_flow.c`
- `ABSENT` (function) `include/block_flow.h:26` `* as ABSENT (0) rather than propagated: a poisoned length must not spread into * the geometry of the rest of the...`
- `bf_collapse_n` (function) `include/block_flow.h:33` `* bf_collapse_n((double[])`
- `bf_margins_adjoin` (function) `include/block_flow.h:43` `int bf_margins_adjoin(double border_px, double padding_px);` -- Whether two vertical margins separated by this much border and padding ADJOIN, i.e. whether they collapse at all...

## include/box_blur.h
Imported by: `fuzz/fuzz_box_blur.c`, `gui/browser_ui.c`, `src/box_blur.c`, `tests/test_box_blur.c`
- `bb_box_sizes` (function) `include/box_blur.h:16` `int bb_box_sizes(double sigma, int sizes[3]);` -- The three odd box widths approximating a Gaussian of standard deviation sigma. * Returns 0 (sizes untouched) when...
- `wider` (function) `include/box_blur.h:21` `* BB_BOX_MAX px or wider (buffer untouched). One scratch copy of w x h bytes. */ int bb_blur_a8(unsigned char *buf...`
- `alpha` (function) `include/box_blur.h:27` `* no pixel has alpha (nothing to blur), 1 otherwise. Everything outside rect stays 0 after the blur, * so blurring...`

## include/box_style.h
Depends on: `include/css.h`
Imported by: `gui/browser_ui.c`, `gui/bui_mask_img.c`, `include/box_tree.h`, `src/box_style.c`, `src/box_tree.c`, `src/dom_debug.c`, `src/page_view.c`, `src/render_doc.c`, `tests/test_box_style.c`, `tests/test_dom_debug.c`, `tests/test_page_view.c`, `tests/test_render_doc.c`
- `box` (function) `include/box_style.h:115` `* in_list nonzero when the block sits inside a list item: it then takes * the <li> box (zero margin), keeping items...`
- `BX_TROLE_NONE` (function) `include/box_style.h:144` `* BX_TROLE_NONE (an unrecognised element joins no table -- fail closed). */ bx_table_role bx_table_role_of(const...`
- `bx_display_name` (function) `include/box_style.h:156` `const char *bx_display_name(bx_display d);` -- Stable, short English name of a display type for structured/agent output.
- `bx_width_cap` (function) `include/box_style.h:182` `double bx_width_cap(int w_px, int w_pct, double avail_w);` -- Effective width cap combining the px cap (w_px, 0 = none) with a symbolic per-mille cap (w_pct, 0 = none; Hito 32)...
- `bx_width_cap2` (function) `include/box_style.h:187` `double bx_width_cap2(int w_px, int w_pct, int mw_px, int mw_pct, double avail_w);` -- The used width cap of an element: the tighter of its `width` (w_px, w_pct) and its `max-width` (mw_px, mw_pct), each...
- `bx_replaced_box` (function) `include/box_style.h:206` `int bx_replaced_box(int w_px, int w_pct, int aspect_num, int aspect_den, double avail_w, double *out_w, double *out_h);` -- CSS Sizing 4 section 4: when one axis is definite and an aspect-ratio is present, the ratio supplies the other.
- `bx_border_box_h` (function) `include/box_style.h:220` `double bx_border_box_h(double declared_h, int border_box, double pad_t, double pad_b, double bord_t, double bord_b);` -- Border-box height for a DECLARED height under box-sizing (CSS 2.1 10.6.3, CSS Box Sizing 3 section 4).
- `block` (function) `include/box_style.h:226` `* indefinite containing block (cb_h < 0) the value behaves as auto: -1. * Without a percentage it is px_val...`
- `bx_line_height_px` (function) `include/box_style.h:239` `double bx_line_height_px(int line_scale, double font_px);` -- The used line-height in px of text at font_px for a css line_scale value (spec/box_style.md 4c): 0 = normal (returns...
- `bx_definite_content_h` (function) `include/box_style.h:241` `double bx_definite_content_h(double h, double min_h, double max_h, int border_box, double v_edges);`
- `page` (function) `include/box_style.h:245` `* instead of letting it extend the page (CSS 2.1 section 10.7 + 11.1.1). That * is the case unless BOTH overflow...`
- `bx_lp_px` (function) `include/box_style.h:267` `double bx_lp_px(int px_val, int pct_pm, double basis);` -- half plus pct_pm per-mille of `basis`.
- `bx_content_cap` (function) `include/box_style.h:275` `double bx_content_cap(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` -- Content-width cap adjusted for box-sizing (2026-07-11).
- `bx_border_span` (function) `include/box_style.h:286` `double bx_border_span(double width_cap, int border_box, double pad_l, double pad_r, double bord_l, double bord_r);` -- The border-inclusive span the painter lays a box out with (its content plus left/right border; padding sits outside it).
- `bx_flex_max_clamp` (function) `include/box_style.h:292` `double bx_flex_max_clamp(double outer_basis, double mw_cap, int border_box, double pad_bord_h, double margin_h);` -- Flexbox 1 9.2.3: an item's OUTER flex base size clamped by its max-width (the hypothetical main size). mw_cap <= 0 =...
- `bx_flex_min_clamp` (function) `include/box_style.h:298` `double bx_flex_min_clamp(double outer_basis, double min_w, int border_box, double pad_bord_h, double margin_h);` -- The min-width half of the same clamp (Flexbox 9.2.3): an outer base below the item's min-width (converted to the...
- `bx_background_layer` (function) `include/box_style.h:331` `int bx_background_layer(const bx_bg_layer *in, double *out_w, double *out_h, double *out_x, double *out_y);`


Next: [API_p4.md](API_p4.md)
