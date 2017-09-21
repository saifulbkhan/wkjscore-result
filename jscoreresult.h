#include <glib.h>
#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>

extern char* js_string_as_result(WebKitJavascriptResult *js_result);
extern double process_js_result_as_number (WebKitJavascriptResult *js_result);
