#include <jscoreresult.h>

char*
process_js_result_as_string (WebKitJavascriptResult *js_result)
{
  JSValueRef js_value;
  JSStringRef js_string;
  size_t max_size;
  char *retval = NULL;

  js_value = webkit_javascript_result_get_value (js_result);
  js_string = JSValueToStringCopy (webkit_javascript_result_get_global_context (js_result),
                                   js_value, NULL);
  max_size = JSStringGetMaximumUTF8CStringSize (js_string);
  if (max_size) {
    retval = g_malloc (max_size);
    JSStringGetUTF8CString (js_string, retval, max_size);
  }
  JSStringRelease (js_string);

  return retval;
}

double
process_js_result_as_number (WebKitJavascriptResult *js_result)
{
  JSValueRef js_value;

  js_value = webkit_javascript_result_get_value (js_result);

  return JSValueToNumber (webkit_javascript_result_get_global_context (js_result),
                          js_value, NULL);
}
