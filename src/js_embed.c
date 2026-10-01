/*
 * js_embed.c -- <iframe> discovery and the <video> facade for trusted pages.
 * Split out of js_dom.c (anti-monolith clause, CLAUDE.md 3.4); contract in
 * include/js_dom.h and spec/js_dom.md.
 */
#define _GNU_SOURCE

#include "js_dom.h"

#include "dom.h"
#include "freebug.h"
#include "html_parse.h"
#include "js_sandbox.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quickjs.h"
#include "js_dom_internal.h"

/* Scans a string `val` (len `vlen`) for `<iframe` and extracts its `src`
 * attribute value (URL). Writes the URL into `out` (bounded by `outsz`).
 * Returns 1 if found, 0 otherwise. Only matches absolute URLs (http/https)
 * and root-relative URLs (starting with /). */
static int extract_iframe_src(const char *val, size_t vlen,
                               char *out, size_t outsz) {
    if (val == NULL || vlen == 0 || out == NULL || outsz == 0) return 0;
    const char *end = val + vlen;
    const char *p = (const char *)memmem(val, vlen, "iframe", 6);
    if (p == NULL) return 0;
    /* Find src= after iframe */
    const char *s = (const char *)memmem(p, (size_t)(end - p), "src", 3);
    if (s == NULL) return 0;
    const char *eq = s + 3;
    while (eq < end && (*eq == ' ' || *eq == '\t' || *eq == '=')) eq++;
    if (eq >= end || (*eq != '"' && *eq != '\'')) return 0;
    char q = *eq;
    const char *url_start = eq + 1;
    const char *url_end = (const char *)memmem(url_start, (size_t)(end - url_start), &q, 1);
    if (url_end == NULL) return 0;
    size_t ulen = (size_t)(url_end - url_start);
    if (ulen == 0 || ulen >= outsz) return 0;
    memcpy(out, url_start, ulen);
    out[ulen] = '\0';
    return 1;
}

/* Resolves a potentially relative URL (root-relative: starts with /) against
 * page_url, writing the result into `out` (bounded by outsz). If the URL is
 * already absolute (starts with http:// or https://), it's copied as-is.
 * If page_url is NULL or parsing fails, the original URL is used. */
static void resolve_video_url(const char *url, const char *page_url,
                               char *out, size_t outsz) {
    if (out == NULL || outsz == 0) return;
    out[0] = '\0';
    if (url == NULL || url[0] == '\0') return;
    /* Already absolute: copy as-is */
    if (strncmp(url, "http://", 7) == 0 || strncmp(url, "https://", 8) == 0) {
        size_t ulen = strlen(url);
        if (ulen < outsz) { memcpy(out, url, ulen + 1); }
        return;
    }
    /* Root-relative: prepend origin from page_url */
    if (url[0] == '/' && page_url != NULL && page_url[0] != '\0') {
        url_parts parts;
        if (url_split(page_url, &parts) == URL_OK && parts.origin != NULL) {
            size_t olen = parts.origin_len;
            size_t ulen = strlen(url);
            if (olen + ulen < outsz) {
                memcpy(out, parts.origin, olen);
                memcpy(out + olen, url, ulen + 1);
                return;
            }
        }
    }
    /* Fallback: copy as-is */
    size_t ulen = strlen(url);
    if (ulen < outsz) memcpy(out, url, ulen + 1);
}

/* Scans an inline script body for `video[N]` or `video_data` assignment
 * and extracts the first usable iframe src. Returns 1 if an iframe was
 * created in the DOM, 0 otherwise. */
static int try_create_iframe_from_script(dom_index *idx,
                                          const char *text, size_t len,
                                          const char *page_url) {
    if (idx == NULL || text == NULL || len == 0) return 0;
    const char *end = text + len;
    const char *p = text;
    char best_url[2048];
    best_url[0] = '\0';
    int found = 0;

    /* Try video_data first (highest priority) */
    const char *vd = (const char *)memmem(p, (size_t)(end - p), "video_data", 10);
    if (vd != NULL) {
        const char *eq = vd + 10;
        while (eq < end && (*eq == ' ' || *eq == '\t')) eq++;
        if (eq < end && *eq == '=') {
            eq++;
            while (eq < end && (*eq == ' ' || *eq == '\t')) eq++;
            if (eq < end && (*eq == '"' || *eq == '\'')) {
                char q = *eq;
                const char *vstart = eq + 1;
                const char *vend = (const char *)memmem(vstart, (size_t)(end - vstart), &q, 1);
                if (vend != NULL) {
                    char tmp[2048];
                    if (extract_iframe_src(vstart, (size_t)(vend - vstart), tmp, sizeof tmp)) {
                        resolve_video_url(tmp, page_url, best_url, sizeof best_url);
                        found = 1;
                    }
                }
            }
        }
    }

    /* If not found yet, scan for video[N] assignments */
    if (!found) {
        /* Collect all video[N] assignments, preferring N=1 then N=0 */
        const char *vscan = p;
        char candidate_urls[3][2048] = {{0}};
        int ncandidates = 0;
        while ((vscan = (const char *)memmem(vscan, (size_t)(end - vscan), "video", 5)) != NULL
               && ncandidates < 3) {
            const char *after = vscan + 5;
            if (after < end && *after == '[') {
                const char *b = after + 1;
                int idx_val = 0;
                while (b < end && *b >= '0' && *b <= '9') {
                    idx_val = idx_val * 10 + (*b - '0');
                    b++;
                }
                if (b < end && *b == ']') {
                    const char *eq = b + 1;
                    while (eq < end && (*eq == ' ' || *eq == '\t')) eq++;
                    if (eq < end && *eq == '=') {
                        eq++;
                        while (eq < end && (*eq == ' ' || *eq == '\t')) eq++;
                        if (eq < end && (*eq == '"' || *eq == '\'')) {
                            char q = *eq;
                            const char *vstart = eq + 1;
                            const char *vend = (const char *)memmem(vstart, (size_t)(end - vstart), &q, 1);
                            if (vend != NULL) {
                                char tmp[2048];
                                if (extract_iframe_src(vstart, (size_t)(vend - vstart), tmp, sizeof tmp)) {
                                    char resolved[2048];
                                    resolve_video_url(tmp, page_url, resolved, sizeof resolved);
                                    /* Store by index for priority ordering */
                                    if (idx_val == 1 && candidate_urls[0][0] == '\0') {
                                        memcpy(candidate_urls[0], resolved, strlen(resolved) + 1);
                                    } else if (idx_val == 0 && candidate_urls[1][0] == '\0') {
                                        memcpy(candidate_urls[1], resolved, strlen(resolved) + 1);
                                    } else {
                                        memcpy(candidate_urls[2], resolved, strlen(resolved) + 1);
                                    }
                                    ncandidates++;
                                }
                            }
                        }
                    }
                }
            }
            vscan = after;
        }
        /* Pick best candidate: video[1] > video[0] > video[N] */
        if (candidate_urls[0][0] != '\0') {
            memcpy(best_url, candidate_urls[0], strlen(candidate_urls[0]) + 1);
            found = 1;
        } else if (candidate_urls[1][0] != '\0') {
            memcpy(best_url, candidate_urls[1], strlen(candidate_urls[1]) + 1);
            found = 1;
        } else if (candidate_urls[2][0] != '\0') {
            memcpy(best_url, candidate_urls[2], strlen(candidate_urls[2]) + 1);
            found = 1;
        }
    }

    if (!found || best_url[0] == '\0') return 0;

    /* Find body element to append the iframe (same approach as jd_process_iframes). */
    dom_node_id bid = DOM_NODE_NONE;
    for (dom_node_id sib = dom_first_child(idx, 0);
         sib != DOM_NODE_NONE;
         sib = dom_next_sibling(idx, sib)) {
        size_t tlen = 0;
        const char *tag = dom_tag_name(idx, sib, &tlen);
        if (tag != NULL && tlen == 4 && memcmp(tag, "body", 4) == 0) {
            bid = sib;
            break;
        }
    }
    if (bid == DOM_NODE_NONE) return 0;

    dom_node_id ifr_id;
    if (dom_create_element(idx, "iframe", &ifr_id) != DOM_OK) return 0;
    dom_set_attribute(idx, ifr_id, "src", best_url);
    dom_append_child(idx, bid, ifr_id);
    return 1;
}

size_t jd_video_from_scripts(dom_index *idx, const char *const *script_texts,
                              const size_t *script_lens, size_t nscripts,
                              const char *page_url) {
    if (idx == NULL || script_texts == NULL || script_lens == NULL || nscripts == 0)
        return 0;
    size_t created = 0;
    for (size_t i = 0; i < nscripts; i++) {
        if (script_texts[i] != NULL && script_lens[i] > 0) {
            if (try_create_iframe_from_script(idx, script_texts[i],
                                               script_lens[i], page_url)) {
                created++;
                /* Only create ONE iframe across all scripts (first match wins) */
                break;
            }
        }
    }
    return created;
}

/* JS shim that emulates a missing `video_min.js`: reads `video_data` or the
 * `video[]` array (defined by the page's inline script), extracts the iframe
 * `src` from the HTML string, resolves relative URLs, and creates an `<iframe>`
 * element in the DOM via the `dom.*` bridge. Later, `jd_process_iframes()`
 * fetches the iframe content and scans it for .m3u8 video URLs. */
static const char JD_VIDEO_SHIM[] =
    "(function(){try{"
    "var h;"
    "if(typeof video_data!=='undefined'&&video_data)h=video_data;"
    "else{if(typeof video==='undefined'||!video)return;h=video[1]||video[0];}"
    "if(typeof h!=='string'||!h)return;"
    "var m=h.match(/src\\s*=\\s*[\"']([^\"']+)[\"']/);if(!m)return;"
    "var s=m[1];"
    "if(s.indexOf('://')===-1&&s.charCodeAt(0)===47){"
    "try{s=location.protocol+'//'+location.hostname+s;}catch(e){}}"
    "var bl=dom.getByTag('body');if(!bl||!bl.length)return;"
    "var b=bl[0];var ifr=dom.createElement('iframe');"
    "dom.setAttribute(ifr,'src',s);dom.appendChild(b,ifr);"
    "}catch(e){}})();";

jd_status jd_inject_video_shim(js_context *ctx) {
    if (ctx == NULL) return JD_ERR_NULL_ARG;
    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return JD_ERR_INTERNAL;
    JSValue r = JS_Eval(jsctx, JD_VIDEO_SHIM, sizeof JD_VIDEO_SHIM - 1,
                        "<video-shim>", JS_EVAL_TYPE_GLOBAL);
    int ok = !JS_IsException(r);
    JS_FreeValue(jsctx, r);
    return ok ? JD_OK : JD_ERR_INTERNAL;
}

/* Scans a body buffer for `.m3u8` (HLS) or `.mp4` (progressive) video URLs.
 * Writes the first found URL into `out` (bounded by `outsz`). Prefers .m3u8
 * over .mp4. Returns 1 if found, 0 otherwise. */
static int scan_video_url(const char *body, size_t blen,
                           char *out, size_t outsz) {
    if (body == NULL || blen == 0 || out == NULL || outsz == 0) return 0;
    out[0] = '\0';
    const char *end = body + blen;
    static const char *exts[] = {".m3u8", ".mp4"};
    static const size_t extlens[] = {5, 4};
    for (int ei = 0; ei < 2; ei++) {
        const char *marker = exts[ei];
        size_t mlen = extlens[ei];
        for (const char *p = body; p + mlen <= end; ++p) {
            if (memcmp(p, marker, mlen) == 0) {
                const char *url_start = p;
                while (url_start > body && url_start[-1] != '\'' && url_start[-1] != '"'
                       && url_start[-1] != ' ' && url_start[-1] != '>' && url_start[-1] != '<'
                       && url_start[-1] != ')' && url_start[-1] != '}' && url_start[-1] != ']'
                       && url_start[-1] != ';' && url_start[-1] != ',' && url_start[-1] != '\n'
                       && url_start[-1] != '\r' && url_start[-1] != '\t')
                    --url_start;
                const char *url_end = p + mlen;
                while (url_end < end && *url_end != '\'' && *url_end != '"'
                       && *url_end != ' ' && *url_end != '>' && *url_end != '<'
                       && *url_end != ')' && *url_end != '}' && *url_end != ']'
                       && *url_end != ';' && *url_end != ',' && *url_end != '\n'
                       && *url_end != '\r' && *url_end != '\t')
                    ++url_end;
                size_t ulen = (size_t)(url_end - url_start);
                if (ulen > 0 && ulen + 1 <= outsz) {
                    memcpy(out, url_start, ulen);
                    out[ulen] = '\0';
                    return 1;
                }
            }
        }
    }
    return 0;
}

void jd_process_iframes(js_context *ctx, dom_index *idx,
                        jd_fetch_fn fn, void *fetch_ctx) {
    if (ctx == NULL || idx == NULL || fn == NULL) return;

    JSContext *jsctx = (JSContext *)js_context_raw(ctx);
    if (jsctx == NULL) return;

    /* Per-context iframe tracking (no static state — avoids cross-page leaks). */
    jd_opaque *o = (jd_opaque *)JS_GetContextOpaque(jsctx);
    if (o == NULL) return;
    jd_iframe_track *track = &o->iframe_track;

    /* Find all iframe elements in the index. */
    size_t niframe = dom_get_by_tag(idx, "iframe", NULL, 0);
    if (niframe == 0) return;
    dom_node_id *iframes = (dom_node_id *)calloc(niframe, sizeof(dom_node_id));
    if (iframes == NULL) return;
    dom_get_by_tag(idx, "iframe", iframes, niframe);

    for (size_t i = 0; i < niframe; ++i) {
        dom_node_id nid = iframes[i];
        if (nid == DOM_NODE_NONE) continue;

        /* Skip already-processed iframes. */
        int already = 0;
        for (size_t j = 0; j < track->nprocessed; ++j) {
            if (track->processed[j] == nid) { already = 1; break; }
        }
        if (already) continue;

        /* Get the src attribute. */
        size_t slen = 0;
        const char *src = dom_get_attribute(idx, nid, "src", &slen);
        if (src == NULL || slen == 0) continue;

        /* Track this iframe as processed. */
        if (track->nprocessed < JD_IFRAME_TRACK_MAX)
            track->processed[track->nprocessed++] = nid;

        /* Fetch the iframe content. */
        int status = 0;
        char *body = NULL;
        size_t blen = 0;
        char *ctype = NULL;
        int fr = fn(fetch_ctx, "GET", src, "", 0,
                    &status, &body, &blen, &ctype);
        free(ctype);

        if (fr != 0 || body == NULL || blen == 0) {
            free(body);
            continue;
        }

        /* Scan for video URLs in the response (.m3u8 first, then .mp4). */
        char video_url[2048];
        if (scan_video_url(body, blen, video_url, sizeof video_url)) {
            /* Create a <video> element in the document with this URL
             * and append it as a child of <body>. The DOM index tracks
             * it — inject_video_into_view in tab.c finds it via the
             * index and injects it with pv_append_video. */
            dom_node_id root_id = 0;
            dom_node_id body_id = DOM_NODE_NONE;
            for (dom_node_id sib = dom_first_child(idx, root_id);
                 sib != DOM_NODE_NONE;
                 sib = dom_next_sibling(idx, sib)) {
                size_t tlen = 0;
                const char *tag = dom_tag_name(idx, sib, &tlen);
                if (tag != NULL && tlen == 4 && memcmp(tag, "body", 4) == 0) {
                    body_id = sib;
                    break;
                }
            }
            if (body_id != DOM_NODE_NONE) {
                dom_node_id vid_id = DOM_NODE_NONE;
                if (dom_create_element(idx, "video", &vid_id) == DOM_OK) {
                    dom_set_attribute(idx, vid_id, "src", video_url);
                    dom_append_child(idx, body_id, vid_id);
                }
            }
        }

        free(body);
    }
    free(iframes);
}
