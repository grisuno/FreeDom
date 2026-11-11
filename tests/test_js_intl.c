/*
 * TDD suite for js_intl (spec/js_intl.md). Expected strings are what Firefox and V8 print
 * for en-US / UTC.
 */
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <string.h>
#include <cmocka.h>

#include "js_intl.h"
#include "js_sandbox.h"

static int setup(void **state) {
    js_context *ctx = NULL;
    if (js_context_new(NULL, &ctx) != JS_OK) return -1;
    if (ji_install(ctx) != 0) return -1;
    *state = ctx;
    return 0;
}

static int teardown(void **state) {
    js_context_free((js_context *)*state);
    return 0;
}

#define EXPECT(src, expected)                                              \
    do {                                                                   \
        js_result _r;                                                      \
        assert_int_equal(js_eval(ctx, (src), strlen(src), &_r), JS_OK);    \
        assert_non_null(_r.value);                                         \
        assert_string_equal(_r.value, (expected));                         \
        js_result_free(&_r);                                               \
    } while (0)

static void test_install_null(void **state) {
    (void)state;
    assert_int_equal(ji_install(NULL), -1);
}

static void test_number_decimal(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("new Intl.NumberFormat('en-US').format(1234567.891)", "1,234,567.891");
    EXPECT("new Intl.NumberFormat().format(1234567.8915)", "1,234,567.892");
    EXPECT("Intl.NumberFormat('de-DE').format(-1234.5)", "-1,234.5");
    EXPECT("new Intl.NumberFormat('en',{maximumFractionDigits:0}).format(2.5)", "3");
    /* Shortest-decimal rounding (ICU), not the exact binary value toFixed uses. */
    EXPECT("[new Intl.NumberFormat('en',{maximumFractionDigits:2}).format(1.005),(1.005).toFixed(2),"
           "new Intl.NumberFormat('en',{maximumFractionDigits:2}).format(9.995),"
           "new Intl.NumberFormat('en',{maximumFractionDigits:1}).format(0.05),"
           "new Intl.NumberFormat('en',{maximumSignificantDigits:2}).format(9.96),"
           "new Intl.NumberFormat('en').format(1e-7),new Intl.NumberFormat('en',{maximumFractionDigits:10}).format(1.5e-7)].join('|')",
           "1.01|1.00|10|0.1|10|0|0.00000015");
    EXPECT("new Intl.NumberFormat('en',{minimumFractionDigits:2}).format(5)", "5.00");
    EXPECT("new Intl.NumberFormat('en',{minimumIntegerDigits:3}).format(7)", "007");
    EXPECT("new Intl.NumberFormat('en',{useGrouping:false}).format(1234567)", "1234567");
    EXPECT("new Intl.NumberFormat('en',{maximumSignificantDigits:3}).format(123456)", "123,000");
    EXPECT("new Intl.NumberFormat('en',{minimumSignificantDigits:4}).format(1.5)", "1.500");
    EXPECT("[new Intl.NumberFormat().format(NaN),new Intl.NumberFormat().format(-Infinity),"
           "new Intl.NumberFormat().format(0),new Intl.NumberFormat().format(999),"
           "new Intl.NumberFormat().format(1000)].join('|')", "NaN|-∞|0|999|1,000");
    EXPECT("new Intl.NumberFormat().format(1e21)", "1,000,000,000,000,000,000,000");
    EXPECT("new Intl.NumberFormat().format(12345678901234567890n)", "12,345,678,901,234,567,890");
    EXPECT("new Intl.NumberFormat('en',{signDisplay:'always'}).format(5)", "+5");
    EXPECT("new Intl.NumberFormat('en',{signDisplay:'exceptZero'}).format(0)", "0");
}

static void test_number_styles(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("new Intl.NumberFormat('en',{style:'percent'}).format(0.256)", "26%");
    EXPECT("new Intl.NumberFormat('en',{style:'percent',maximumFractionDigits:1}).format(0.2567)", "25.7%");
    /* The x100 of a percent can overflow to infinity: it must format, not throw. */
    EXPECT("new Intl.NumberFormat('en',{style:'percent'}).format(1.7976931348623157e308)", "∞%");
    EXPECT("new Intl.NumberFormat('en-US',{style:'currency',currency:'USD'}).format(1234.5)", "$1,234.50");
    EXPECT("new Intl.NumberFormat('en-US',{style:'currency',currency:'USD'}).format(-3)", "-$3.00");
    EXPECT("new Intl.NumberFormat('en-US',{style:'currency',currency:'EUR'}).format(2)", "€2.00");
    EXPECT("new Intl.NumberFormat('en-US',{style:'currency',currency:'JPY'}).format(1234.5)", "¥1,235");
    EXPECT("new Intl.NumberFormat('en-US',{style:'currency',currency:'usd',currencyDisplay:'code'}).format(2)", "USD 2.00");
    EXPECT("new Intl.NumberFormat('en-US',{style:'currency',currency:'USD',maximumFractionDigits:0}).format(1999.5)", "$2,000");
    EXPECT("var t=0;try{new Intl.NumberFormat('en',{style:'currency'})}catch(e){t=e instanceof TypeError} t", "true");
    EXPECT("new Intl.NumberFormat('en',{style:'unit',unit:'kilometer'}).format(5)", "5 km");
    EXPECT("new Intl.NumberFormat('en',{style:'unit',unit:'kilometer',unitDisplay:'long'}).format(5)", "5 kilometers");
    EXPECT("new Intl.NumberFormat('en',{style:'unit',unit:'kilometer',unitDisplay:'long'}).format(1)", "1 kilometer");
    EXPECT("new Intl.NumberFormat('en',{style:'unit',unit:'kilometer-per-hour'}).format(50)", "50 km/h");
}

static void test_number_compact(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("var f=new Intl.NumberFormat('en',{notation:'compact'});"
           "[f.format(999),f.format(1234),f.format(12345),f.format(123456),f.format(1234567),f.format(1.5e9),f.format(2e12)].join('|')",
           "999|1.2K|12K|123K|1.2M|1.5B|2T");
    EXPECT("new Intl.NumberFormat('en',{notation:'compact',compactDisplay:'long'}).format(1234567)", "1.2 million");
    EXPECT("new Intl.NumberFormat('en',{notation:'compact',maximumFractionDigits:1}).format(15300)", "15.3K");
}

static void test_number_parts_and_options(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("new Intl.NumberFormat('en',{style:'currency',currency:'USD'}).formatToParts(-1234.5)"
           ".map(function(p){return p.type+':'+p.value}).join(' ')",
           "minusSign:- currency:$ integer:1 group:, integer:234 decimal:. fraction:50");
    EXPECT("var o=new Intl.NumberFormat('fr').resolvedOptions();[o.locale,o.numberingSystem,o.style,"
           "o.minimumFractionDigits,o.maximumFractionDigits].join()", "en-US,latn,decimal,0,3");
    EXPECT("var t=0;try{new Intl.NumberFormat('en',{maximumFractionDigits:1000})}catch(e){t=e instanceof RangeError} t", "true");
    EXPECT("Intl.NumberFormat.supportedLocalesOf(['es-ar','en']).join()", "es-AR,en");
}

static void test_to_locale_string(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("(1234567.891).toLocaleString()", "1,234,567.891");
    EXPECT("(1234.5).toLocaleString('en-US',{style:'currency',currency:'USD'})", "$1,234.50");
    EXPECT("(0.5).toLocaleString(undefined,{style:'percent'})", "50%");
    EXPECT("(123456789n).toLocaleString()", "123,456,789");
    EXPECT("new Date(0).toLocaleString()", "1/1/1970, 12:00:00 AM");
    EXPECT("new Date(0).toLocaleDateString()", "1/1/1970");
    EXPECT("new Date(0).toLocaleTimeString()", "12:00:00 AM");
    EXPECT("new Date(Date.UTC(2026,10,11,15,4,5)).toLocaleString('en-US')", "11/11/2026, 3:04:05 PM");
    EXPECT("new Date(Date.UTC(2026,10,11)).toLocaleDateString('en-US',{year:'numeric',month:'short',day:'numeric'})",
           "Nov 11, 2026");
    EXPECT("new Date(Date.UTC(2026,0,5,9,7)).toLocaleTimeString([], {hour:'2-digit',minute:'2-digit'})", "09:07 AM");
    EXPECT("new Date(NaN).toLocaleString()", "Invalid Date");
}

static void test_date_components(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("new Intl.DateTimeFormat('en-US').format(new Date(0))", "1/1/1970");
    EXPECT("new Intl.DateTimeFormat('en-US',{month:'long',year:'numeric'}).format(0)", "January 1970");
    EXPECT("new Intl.DateTimeFormat('en-US',{month:'long',day:'numeric'}).format(0)", "January 1");
    EXPECT("new Intl.DateTimeFormat('en-US',{weekday:'long',year:'numeric',month:'long',day:'numeric'}).format(0)",
           "Thursday, January 1, 1970");
    EXPECT("new Intl.DateTimeFormat('en-US',{weekday:'short',month:'short',day:'numeric'}).format(0)", "Thu, Jan 1");
    EXPECT("new Intl.DateTimeFormat('en-US',{weekday:'long'}).format(0)", "Thursday");
    EXPECT("new Intl.DateTimeFormat('en-US',{year:'numeric'}).format(0)", "1970");
    EXPECT("new Intl.DateTimeFormat('en-US',{month:'short'}).format(0)", "Jan");
    EXPECT("new Intl.DateTimeFormat('en-US',{year:'2-digit',month:'2-digit',day:'2-digit'}).format(0)", "01/01/70");
    EXPECT("new Intl.DateTimeFormat('en-US',{year:'numeric',month:'numeric'}).format(0)", "1/1970");
    EXPECT("new Intl.DateTimeFormat('en-US',{hour:'numeric',minute:'2-digit'}).format(Date.UTC(2026,0,1,13,5))", "1:05 PM");
    EXPECT("new Intl.DateTimeFormat('en-US',{hour:'numeric'}).format(Date.UTC(2026,0,1,13,5))", "1 PM");
    EXPECT("new Intl.DateTimeFormat('en-US',{hour:'2-digit',minute:'2-digit',second:'2-digit',hour12:false})"
           ".format(Date.UTC(2026,0,1,0,5,9))", "00:05:09");
    EXPECT("new Intl.DateTimeFormat('en-US',{hour:'numeric',minute:'numeric',timeZoneName:'short'}).format(0)", "12:00 AM UTC");
    EXPECT("new Intl.DateTimeFormat('en-US',{year:'numeric',month:'short',day:'numeric',hour:'numeric',minute:'2-digit'})"
           ".format(Date.UTC(2026,10,11,15,4))", "Nov 11, 2026, 3:04 PM");
    EXPECT("new Intl.DateTimeFormat('en-US',{minute:'2-digit',second:'2-digit',fractionalSecondDigits:3}).format(61234)",
           "01:01.234");
}

static void test_date_styles_parts(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("['full','long','medium','short'].map(function(s){return new Intl.DateTimeFormat('en-US',{dateStyle:s}).format(0)}).join('|')",
           "Thursday, January 1, 1970|January 1, 1970|Jan 1, 1970|1/1/70");
    EXPECT("['medium','short'].map(function(s){return new Intl.DateTimeFormat('en-US',{timeStyle:s}).format(0)}).join('|')",
           "12:00:00 AM|12:00 AM");
    EXPECT("new Intl.DateTimeFormat('en-US',{dateStyle:'medium',timeStyle:'short'}).format(0)", "Jan 1, 1970, 12:00 AM");
    EXPECT("new Intl.DateTimeFormat('en-US',{dateStyle:'long',timeStyle:'short'}).format(0)", "January 1, 1970 at 12:00 AM");
    EXPECT("new Intl.DateTimeFormat('en-US',{month:'short',day:'numeric',year:'numeric'}).formatToParts(0)"
           ".map(function(p){return p.type+':'+p.value}).join('|')", "month:Jan|literal: |day:1|literal:, |year:1970");
    EXPECT("var o=new Intl.DateTimeFormat('ja-JP',{timeZone:'Asia/Tokyo'}).resolvedOptions();"
           "[o.locale,o.calendar,o.numberingSystem,o.timeZone].join()", "en-US,gregory,latn,UTC");
    EXPECT("var t=0;try{new Intl.DateTimeFormat().format(new Date(NaN))}catch(e){t=e instanceof RangeError} t", "true");
    EXPECT("new Intl.DateTimeFormat('en-US',{dateStyle:'medium'}).formatRange(0,86400000*2)", "Jan 1, 1970 – Jan 3, 1970");
    EXPECT("typeof new Intl.DateTimeFormat().format(undefined)", "string");
}

static void test_relative_plural_list(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("var r=new Intl.RelativeTimeFormat('en');[r.format(-3,'day'),r.format(1,'hour'),r.format(2,'months'),"
           "r.format(-1,'year'),r.format(0,'second')].join('|')",
           "3 days ago|in 1 hour|in 2 months|1 year ago|in 0 seconds");
    EXPECT("var a=new Intl.RelativeTimeFormat('en',{numeric:'auto'});[a.format(-1,'day'),a.format(1,'day'),a.format(0,'day'),"
           "a.format(-1,'week'),a.format(1,'month'),a.format(0,'second'),a.format(-2,'day')].join('|')",
           "yesterday|tomorrow|today|last week|next month|now|2 days ago");
    EXPECT("new Intl.RelativeTimeFormat('en',{style:'short'}).format(-3,'month')", "3 mo. ago");
    EXPECT("new Intl.RelativeTimeFormat('en',{style:'narrow'}).format(5,'minute')", "in 5min");
    EXPECT("new Intl.RelativeTimeFormat('en').format(-1234,'day')", "1,234 days ago");
    EXPECT("var t=0;try{new Intl.RelativeTimeFormat('en').format(1,'fortnight')}catch(e){t=e instanceof RangeError} t", "true");
    EXPECT("var p=new Intl.PluralRules('en');[p.select(0),p.select(1),p.select(2),p.select(1.5)].join()", "other,one,other,other");
    EXPECT("var o=new Intl.PluralRules('en',{type:'ordinal'});[1,2,3,4,11,12,13,21,22,23,101].map(function(n){return o.select(n)}).join()",
           "one,two,few,other,other,other,other,one,two,few,one");
    EXPECT("var l=new Intl.ListFormat('en');[l.format([]),l.format(['a']),l.format(['a','b']),l.format(['a','b','c'])].join('|')",
           "|a|a and b|a, b, and c");
    EXPECT("new Intl.ListFormat('en',{type:'disjunction'}).format(['a','b','c'])", "a, b, or c");
    EXPECT("new Intl.ListFormat('en',{style:'narrow',type:'unit'}).format(['5 h','3 min'])", "5 h 3 min");
    EXPECT("new Intl.ListFormat('en',{style:'short'}).format(['a','b','c'])", "a, b, & c");
}

static void test_collator_and_rest(void **state) {
    js_context *ctx = (js_context *)*state;
    EXPECT("['b','A','a','C'].sort(new Intl.Collator('en').compare).join('')", "aAbC");
    EXPECT("['item10','item9','item1'].sort(new Intl.Collator('en',{numeric:true}).compare).join()", "item1,item9,item10");
    EXPECT("new Intl.Collator('en',{sensitivity:'base'}).compare('a','A')", "0");
    EXPECT("['b','a'].sort(Intl.Collator().compare).join('')", "ab");
    EXPECT("'a'.localeCompare('B')<0", "true");
    EXPECT("[typeof Intl.Locale,typeof Intl.DisplayNames,typeof Intl.Segmenter,Intl.getCanonicalLocales('EN-us')[0],"
           "new Intl.Locale('pt-br').region,Object.prototype.toString.call(Intl)].join()",
           "function,function,function,en-US,BR,[object Intl]");
    EXPECT("Array.from(new Intl.Segmenter('en',{granularity:'word'}).segment('a b')).length", "3");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_install_null),
        cmocka_unit_test_setup_teardown(test_number_decimal, setup, teardown),
        cmocka_unit_test_setup_teardown(test_number_styles, setup, teardown),
        cmocka_unit_test_setup_teardown(test_number_compact, setup, teardown),
        cmocka_unit_test_setup_teardown(test_number_parts_and_options, setup, teardown),
        cmocka_unit_test_setup_teardown(test_to_locale_string, setup, teardown),
        cmocka_unit_test_setup_teardown(test_date_components, setup, teardown),
        cmocka_unit_test_setup_teardown(test_date_styles_parts, setup, teardown),
        cmocka_unit_test_setup_teardown(test_relative_plural_list, setup, teardown),
        cmocka_unit_test_setup_teardown(test_collator_and_rest, setup, teardown),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
