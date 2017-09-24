#ifndef __WEBKIT_JSRESULT_H__
#define __WEBKIT_JSRESULT_H__

#include <glib-object.h>
#include <webkit2/webkit2.h>

G_BEGIN_DECLS

/*
 * Type declaration
 */
#define WEBKIT_TYPE_JSRESULT webkit_jsresult_get_type()
G_DECLARE_FINAL_TYPE (WebkitJSResult,
		      webkit_jsresult,
		      WEBKIT,
		      JSRESULT,
		      GObject)

/*
 * Method definitions
 */
WebkitJSResult *webkit_jsresult_new (void);

gchar*
process_js_result_as_string (WebkitJSResult *wkjsresult,
			     WebKitJavascriptResult *js_result);

gdouble
process_js_result_as_number (WebkitJSResult *wkjsresult,
			     WebKitJavascriptResult *js_result);

G_END_DECLS

#endif /* __WEBKIT_JSRESULT_H__ */
