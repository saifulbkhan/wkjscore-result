/* Copyright (C) <2017>  Saiful Bari Khan <saifulbkhan@gmail.com>

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
 * wk_js_core_result_new
 * @jsresult: a WebKitJavascriptResult object
 *
 * Create a new WkJsCoreResult object representing
 * @jsresult and providing nicer interface to extract
 * valuable information from it.
 *
 * Return value: new WkJsCoreResult object
 */
WkJsCoreResult*
wk_js_core_result_new (WebKitJavascriptResult *jsresult);

/*
 * wk_js_core_result_get_result_type
 * @wkjscoreresult: a WkJsCoreResult object
 *
 * Gets the type of value stored in @result
 *
 * Return value: A WkJsCoreType value
 */
WkJsCoreType
wk_js_core_result_get_result_type (WkJsCoreResult *result);

/*
 * wk_js_core_result_create_json_from_result:
 * @wkjscresult: a WkJsCoreResult object
 * @indent: number of indentation spaces
 *
 * Creates a JSON string for the JS object in @result.
 * The string is indented by @indent number of space
 * at each level of nesting.
 *
 * Return value: Pointer to string
 */
gchar*
wk_js_core_result_create_json_from_result (WkJsCoreResult *result, guint indent);

/*
 * wk_js_core_result_process_result_as_string:
 * @wkjscresult: a WkJsCoreResult object
 *
 * Extracts the string value represented by @result
 *
 * Return value: Pointer to string
 */
gchar*
wk_js_core_result_process_result_as_string (WkJsCoreResult *result);

/*
 * wk_js_core_result_process_result_as_number:
 * @wkjscresult: a WkJsCoreResult object
 *
 * Extracts the number value represented by @result
 *
 * Return value: Number as double
 */
gdouble
wk_js_core_result_process_result_as_number (WkJsCoreResult *result);

/*
 * wk_js_core_result_process_result_as_boolean:
 * @wkjscresult: a WkJsCoreResult object
 *
 * Extracts the boolean value represented by @result
 *
 * Return value: Boolean value
 */
gboolean
wk_js_core_result_process_result_as_boolean (WkJsCoreResult *result);

G_END_DECLS

#endif /* __WK_JS_CORE_RESULT_H__ */
