#ifndef __WKJSCORE_RESULT_H__
#define __WKJSCORE_RESULT_H__

#include <glib-object.h>
#include <webkit2/webkit2.h>

G_BEGIN_DECLS

/* Enum for value types */
typedef enum {
  _UNDEFINED,
  _NULL,
  _BOOLEAN,
  _NUMBER,
  _STRING,
  _OBJECT
} WkJsCoreType;

/*
 * Type declaration
 */
#define WKJSCORE_TYPE_RESULT wk_js_core_result_get_type()
G_DECLARE_FINAL_TYPE (WkJsCoreResult,
                      wk_js_core_result,
                      WK_JS_CORE,
                      RESULT,
                      GObject)

/*
 * Method definitions
 */
WkJsCoreType
wk_js_core_result_get_result_type          (WkJsCoreResult         *result,
                                            WebKitJavascriptResult *js_result);

gchar*
wk_js_core_result_create_json_from_result  (WkJsCoreResult         *result,
                                            WebKitJavascriptResult *js_result,
                                            guint                  indent);

gchar*
wk_js_core_result_process_result_as_string (WkJsCoreResult         *result,
                                            WebKitJavascriptResult *js_result);

gdouble
wk_js_core_result_process_result_as_number (WkJsCoreResult         *result,
                                            WebKitJavascriptResult *js_result);

gboolean
wk_js_core_result_process_result_as_boolean (WkJsCoreResult        *result,
					                                  WebKitJavascriptResult *js_result);

G_END_DECLS

#endif /* __WK_JS_CORE_RESULT_H__ */
