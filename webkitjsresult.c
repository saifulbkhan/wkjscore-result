#include <JavaScriptCore/JavaScript.h>
#include "webkitjsresult.h"

struct _WebkitJSResult
{
  GObject parent_instance;
};

G_DEFINE_TYPE (WebkitJSResult, webkit_jsresult, G_TYPE_OBJECT)

/*
 * process_js_result_as_string:
 * @wkjsresult: a WebkitJSResult object
 * @js_result: a WebKitJavascriptResult object to process value from
 *
 * Extracts the string value within a WebKitJavascriptResult object
 *
 * Return value: Pointer to string
 */
gchar*
process_js_result_as_string (WebkitJSResult *wkjsresult,
                             WebKitJavascriptResult *js_result)
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

  return (gchar*) retval;
}

/*
 * process_js_result_as_number:
 * @wkjsresult: a WebkitJSResult object
 * @js_result: a WebKitJavascriptResult object to process value from
 *
 * Extracts the number value within a WebKitJavascriptResult object
 *
 * Return value: Number as double
 */
gdouble
process_js_result_as_number (WebkitJSResult *wkjsresult,
                             WebKitJavascriptResult *js_result)
{
  JSValueRef js_value;
  double number;

  js_value = webkit_javascript_result_get_value (js_result);

  number = JSValueToNumber (webkit_javascript_result_get_global_context (js_result),
                          js_value, NULL);
  return (gdouble) number;
}

static void
webkit_jsresult_class_init (WebkitJSResultClass *klass)
{
}

static void
webkit_jsresult_init (WebkitJSResult *self)
{
}
