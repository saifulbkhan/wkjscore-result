#include <JavaScriptCore/JavaScript.h>
#include "wkjscoreresult.h"

struct _WkJsCoreResult
{
  GObject parent_instance;
};

G_DEFINE_TYPE (WkJsCoreResult, wk_js_core_result, G_TYPE_OBJECT)

/*
 * wk_js_core_result_process_result_as_string:
 * @wkjscresult: a WkJsCoreResult object
 * @js_result: a WebKitJavascriptResult object to process value from
 *
 * Extracts the string value within a WebKitJavascriptResult object
 *
 * Return value: Pointer to string
 */
gchar*
wk_js_core_result_process_result_as_string (WkJsCoreResult *wkjscresult,
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
 * wk_js_core_result_process_result_as_number:
 * @wkjscresult: a WkJsCoreResult object
 * @js_result: a WebKitJavascriptResult object to process value from
 *
 * Extracts the number value within a WebKitJavascriptResult object
 *
 * Return value: Number as double
 */
gdouble
wk_js_core_result_process_result_as_number (WkJsCoreResult *wkjscresult,
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
wk_js_core_result_class_init (WkJsCoreResultClass *klass)
{
}

static void
wk_js_core_result_init (WkJsCoreResult *self)
{
}
