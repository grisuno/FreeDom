#include "fb_panes.h"

#include <stdio.h>
#include <string.h>

static const char *const TAB_LABEL[FBP_COUNT] = { "Console", "HTML", "CSS", "Script", "Net", "Profile", "Throws" };

/* Each body runs as `function(q){ BODY }` and returns a string. q is the user's argument.
 * They read the page through the REPL command-line API (rules/styles/box/net), which exists
 * only in the REPL worker, and never write to the page or its console. */
static const char JS_HTML[] =
    "var d=document,e=q?d.querySelector(q):d.documentElement;"
    "if(!e)return '(no element matches '+q+')';"
    "var L=[];"
    "function lb(n){var s='<'+(n.localName||String(n.tagName).toLowerCase()),a=n.attributes,i,v;"
    "for(i=0;a&&i<a.length&&i<8;i++){v=String(a[i].value);if(v.length>48)v=v.slice(0,45)+'...';"
    "s+=' '+a[i].name+'=\"'+v+'\"';}return s+'>';}"
    "function w(n,lv){if(L.length>=800)return;var p=new Array(lv+1).join('  ');"
    "if(n.nodeType===3){var t=String(n.data).replace(/\\s+/g,' ').trim();"
    "if(t)L.push(p+'\"'+(t.length>72?t.slice(0,69)+'...':t)+'\"');return;}"
    "if(n.nodeType!==1)return;L.push(p+lb(n));if(lv>=24)return;"
    "var c=n.childNodes;for(var i=0;i<c.length&&L.length<800;i++)w(c[i],lv+1);}"
    "w(e,0);return L.join('\\n')+(L.length>=800?'\\n... (truncated)':'');";

static const char JS_CSS[] =
    "var e=document.querySelector(q||'body');"
    "if(!e)return '(no element matches '+q+')';"
    "var o=[],r=[],i,j,k,x;"
    "try{r=rules(e);}catch(z){}"
    "o.push('== matched rules ('+r.length+') ==');"
    "for(i=0;i<r.length;i++){o.push(r[i].selector+'  ['+r[i].source+(r[i].media?' @media '+r[i].media:'')"
    "+']  specificity '+r[i].specificity);"
    "for(j=0;j<r[i].declarations.length;j++){k=r[i].declarations[j];"
    "o.push('  '+(k.overridden?'~ ':'  ')+k.property+': '+k.value+(k.important?' !important':''));}}"
    "o.push('== computed ==');"
    "var nc=0;try{x=styles(e);for(k in x){nc++;o.push('  '+k+': '+x[k]);}}catch(z){}"
    "if(!nc)o.push('  (none: computed styles are available on allow.conf + js.conf pages)');"
    "try{var b=box(e),f=function(s){return s.top+' '+s.right+' '+s.bottom+' '+s.left;};"
    "if(b){o.push('== box ==');o.push('  content '+(b.content?b.content.width+' x '+b.content.height:'n/a'));"
    "o.push('  padding '+f(b.padding));o.push('  border  '+f(b.border));o.push('  margin  '+f(b.margin));}}catch(z){}"
    "return o.join('\\n');";

static const char JS_SCRIPT[] =
    "var s=document.scripts,o=[],i,x,n=q?parseInt(q,10):0;"
    "if(n>0){x=s[n-1];if(!x)return '(no script #'+n+')';"
    "var t=x.src?'/* external script: '+x.src+' (its source is not retained by the page) */':String(x.textContent||'');"
    "var ls=t.split('\\n');for(i=0;i<ls.length&&i<2000;i++){var l=ls[i];"
    "o.push(('     '+(i+1)).slice(-5)+'  '+(l.length>200?l.slice(0,197)+'...':l));}return o.join('\\n');}"
    "for(i=0;i<s.length&&i<256;i++){x=s[i];"
    "o.push((i+1)+'. '+(x.src?x.src:'inline, '+String(x.textContent||'').length+' chars')"
    "+(x.getAttribute('type')?'  type='+x.getAttribute('type'):'')+(x.defer?' defer':'')+(x.async?' async':''));}"
    "return o.length?o.join('\\n'):'(no scripts)';";

static const char JS_NET[] =
    "var r;try{r=net(q||undefined);}catch(z){return '(net() unavailable)';}"
    "var o=[],i,e;for(i=0;i<r.length;i++){e=r[i];"
    "o.push((e.method||'GET')+'  '+e.status+'  '+(e.type||'-')+'  '+e.url+(e.size?'  ('+e.size+' B)':''));}"
    "return o.length?o.join('\\n'):'(no requests)';";

static const char JS_PROFILE[] =
    "var r;try{r=profile(q||undefined);}catch(z){return '(profile() unavailable)';}"
    "return r||'(no samples: the profiler runs on allow.conf + js.conf pages)';";

static const char JS_THROWS[] =
    "var r;try{r=throws(q||undefined);}catch(z){return '(throws() unavailable)';}"
    "return r||'(no exceptions thrown)';";

static const char *const JS_BODY[FBP_COUNT] = { NULL, JS_HTML, JS_CSS, JS_SCRIPT, JS_NET, JS_PROFILE, JS_THROWS };

static int tab_ok(int tab) { return tab >= 0 && tab < FBP_COUNT; }

const char *fbp_tab_label(int tab) { return TAB_LABEL[tab_ok(tab) ? tab : FBP_CONSOLE]; }

static int ieq(const char *a, const char *b) {
    for (; *a != '\0' && *b != '\0'; ++a, ++b) {
        char ca = (*a >= 'A' && *a <= 'Z') ? (char)(*a + ('a' - 'A')) : *a;
        char cb = (*b >= 'A' && *b <= 'Z') ? (char)(*b + ('a' - 'A')) : *b;
        if (ca != cb) return 0;
    }
    return *a == '\0' && *b == '\0';
}

int fbp_tab_from_name(const char *name) {
    if (name == NULL) return -1;
    for (int t = 0; t < FBP_COUNT; ++t)
        if (ieq(name, TAB_LABEL[t])) return t;
    return -1;
}

int fbp_tab_wrap(int tab, int dir) {
    if (!tab_ok(tab)) tab = FBP_CONSOLE;
    int step = (dir > 0) ? 1 : (dir < 0) ? FBP_COUNT - 1 : 0;
    return (tab + step) % FBP_COUNT;
}

void fbp_tab_span(int tab, double cell_w, double pad_cells, double *x, double *w) {
    if (!tab_ok(tab)) tab = FBP_CONSOLE;
    double edge = 0.0;
    for (int t = 0; t < tab; ++t)
        edge += cell_w * ((double)strlen(TAB_LABEL[t]) + 2.0 * pad_cells);
    if (x != NULL) *x = edge;
    if (w != NULL) *w = cell_w * ((double)strlen(TAB_LABEL[tab]) + 2.0 * pad_cells);
}

int fbp_tab_at(double px, double cell_w, double pad_cells) {
    if (!(cell_w > 0.0) || px < 0.0) return -1;
    for (int t = 0; t < FBP_COUNT; ++t) {
        double x, w;
        fbp_tab_span(t, cell_w, pad_cells, &x, &w);
        if (px >= x && px < x + w) return t;
    }
    return -1;
}

int fbp_is_pane(int tab) { return tab_ok(tab) && tab != FBP_CONSOLE; }

size_t fbp_js_quote(const char *s, size_t n, char *out, size_t cap) {
    if (out == NULL || cap == 0 || (s == NULL && n > 0) || n > FBP_SELECTOR_MAX) return 0;
    size_t o = 0;
    if (o + 1 >= cap) return 0;
    out[o++] = '"';
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (c == '\0') return 0;
        char esc[8];
        size_t el;
        if (c == '"' || c == '\\') { esc[0] = '\\'; esc[1] = (char)c; el = 2; }
        else if (c == '\n') { esc[0] = '\\'; esc[1] = 'n'; el = 2; }
        else if (c == '\r') { esc[0] = '\\'; esc[1] = 'r'; el = 2; }
        else if (c == '\t') { esc[0] = '\\'; esc[1] = 't'; el = 2; }
        else if (c < 0x20 || c == 0x7f) {
            int r = snprintf(esc, sizeof esc, "\\u%04x", (unsigned)c);
            if (r < 0 || (size_t)r >= sizeof esc) return 0;
            el = (size_t)r;
        } else { esc[0] = (char)c; el = 1; }
        if (o + el + 2 > cap) return 0;       /* room for the closing quote and the NUL */
        memcpy(out + o, esc, el);
        o += el;
    }
    if (o + 2 > cap) return 0;
    out[o++] = '"';
    out[o] = '\0';
    return o;
}

size_t fbp_expr(int tab, const char *sel, size_t n, char *out, size_t cap) {
    if (out == NULL || !fbp_is_pane(tab) || (sel == NULL && n > 0)) return 0;
    char q[2 * FBP_SELECTOR_MAX * 3 + 8];
    size_t ql = fbp_js_quote(sel, n, q, sizeof q);
    if (ql == 0) return 0;
    static const char HEAD[] = "(function(q){";
    static const char MID[] = "})(";
    const char *body = JS_BODY[tab];
    size_t need = (sizeof HEAD - 1) + strlen(body) + (sizeof MID - 1) + ql + 1 /* ')' */ + 1 /* NUL */;
    if (need > cap) return 0;
    size_t o = 0;
    memcpy(out + o, HEAD, sizeof HEAD - 1); o += sizeof HEAD - 1;
    size_t bl = strlen(body);
    memcpy(out + o, body, bl); o += bl;
    memcpy(out + o, MID, sizeof MID - 1); o += sizeof MID - 1;
    memcpy(out + o, q, ql); o += ql;
    out[o++] = ')';
    out[o] = '\0';
    return o;
}
