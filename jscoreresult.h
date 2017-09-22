#ifndef jscoreresult_h
#define jscoreresult_h

#include <glib.h>
#include <webkit2/webkit2.h>
#include <JavaScriptCore/JavaScript.h>

extern char* process_js_result_as_string(WebKitJavascriptResult *js_result);
extern double process_js_result_as_number (WebKitJavascriptResult *js_result);

#endif
