#ifndef __WKJSCORE_RESULT_H__
#define __WKJSCORE_RESULT_H__

#include <glib-object.h>
#include <webkit2/webkit2.h>

G_BEGIN_DECLS

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
gchar*
wk_js_core_result_process_result_as_string (WkJsCoreResult *wkjscresult,
                                            WebKitJavascriptResult *js_result);

gdouble
wk_js_core_result_process_result_as_number (WkJsCoreResult *wkjscresult,
                                            WebKitJavascriptResult *js_result);

G_END_DECLS

#endif /* __WK_JS_CORE_RESULT_H__ */
