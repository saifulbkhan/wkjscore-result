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
G_DECLARE_DERIVABLE_TYPE (WkJsCoreResult,
                          wk_js_core_result,
                          WK_JS_CORE,
                          RESULT,
                          GObject)

struct _WkJsCoreResultClass
{
  GObjectClass parent_class;
};

/*
 * Method definitions
 */
WkJsCoreResult*
wk_js_core_result_new (WebKitJavascriptResult *jsresult);

WkJsCoreType
wk_js_core_result_get_result_type (WkJsCoreResult *result);

gchar*
wk_js_core_result_create_json_from_result (WkJsCoreResult *result, guint indent);

gchar*
wk_js_core_result_process_result_as_string (WkJsCoreResult *result);

gdouble
wk_js_core_result_process_result_as_number (WkJsCoreResult *result);

gboolean
wk_js_core_result_process_result_as_boolean (WkJsCoreResult *result);

G_END_DECLS

#endif /* __WK_JS_CORE_RESULT_H__ */
