#include <JavaScriptCore/JavaScript.h>
#include "wkjscoreresult.h"

typedef struct
{
  WebKitJavascriptResult *jsresult;
} WkJsCoreResultPrivate;

enum
{
  PROP_JSRESULT = 1,
  N_PROPERTIES
};

static GParamSpec *obj_properties[N_PROPERTIES] = { NULL, };

G_DEFINE_TYPE_WITH_PRIVATE (WkJsCoreResult, wk_js_core_result, G_TYPE_OBJECT)

static void
wk_js_core_result_init (WkJsCoreResult *self)
{
  WkJsCoreResultPrivate *priv = wk_js_core_result_get_instance_private (self);
  priv->jsresult = NULL;
}

static void
wk_js_core_result_set_property (GObject      *object,
                                guint         property_id,
                                const GValue *value,
                                GParamSpec   *pspec)
{
  WkJsCoreResult *self = WK_JS_CORE_RESULT (object);
  WkJsCoreResultPrivate *priv = wk_js_core_result_get_instance_private (self);

  switch (property_id)
    {
    case PROP_JSRESULT:
      priv->jsresult = g_value_get_pointer (value);
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
wk_js_core_result_get_property (GObject    *object,
                                guint       property_id,
                                GValue     *value,
                                GParamSpec *pspec)
{
  WkJsCoreResult *self = WK_JS_CORE_RESULT (object);
  WkJsCoreResultPrivate *priv = wk_js_core_result_get_instance_private (self);

  switch (property_id)
    {
    case PROP_JSRESULT:
      g_value_set_pointer (value, priv->jsresult);
      break;

    default:
      /* We don't have any other property... */
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
    }
}

static void
wk_js_core_result_class_init (WkJsCoreResultClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->set_property = wk_js_core_result_set_property;
  object_class->get_property = wk_js_core_result_get_property;

  obj_properties[PROP_JSRESULT] =
    g_param_spec_pointer ("jsresult",
                          "JS Result",
                          "A Javascript result object.",
                          G_PARAM_CONSTRUCT_ONLY | G_PARAM_READWRITE);

  g_object_class_install_properties (object_class,
                                     N_PROPERTIES,
                                     obj_properties);

}

WkJsCoreResult*
wk_js_core_result_new (WebKitJavascriptResult *jsresult)
{
  WkJsCoreResult *result = g_object_new (WKJSCORE_TYPE_RESULT,
                                         "jsresult", jsresult,
                                         NULL);
  return result;
}

/*
 * wk_js_core_result_get_result_type
 * @wkjscoreresult: a WkJsCoreResult object
 * @jsresult: a WebKitJavascriptResult object to get value type from
 *
 * Gets the type of value represented by jsresult object
 *
 * Return value: A WkJsCoreType value
 */
WkJsCoreType
wk_js_core_result_get_result_type (WkJsCoreResult *result)
{
  JSValueRef js_value;
  JSContextRef js_ctx;
  WebKitJavascriptResult *jsresult;

  g_object_get (result, "jsresult", &jsresult, NULL);

  js_value = webkit_javascript_result_get_value (jsresult);
  js_ctx = webkit_javascript_result_get_global_context (jsresult);

  if (JSValueIsUndefined (js_ctx, js_value))
    return _UNDEFINED;
  if (JSValueIsNull (js_ctx, js_value))
    return _NULL;
  if (JSValueIsBoolean (js_ctx, js_value))
    return _BOOLEAN;
  if (JSValueIsNumber (js_ctx, js_value))
    return _NUMBER;
  if (JSValueIsString (js_ctx, js_value))
    return _STRING;
  g_assert (JSValueIsObject (js_ctx, js_value));
  return _OBJECT;
}

gchar*
js_string_to_gchar (JSStringRef js_string)
{
  size_t max_size;
  char *retval = NULL;

  max_size = JSStringGetMaximumUTF8CStringSize (js_string);
  if (max_size) {
    retval = g_malloc (max_size);
    JSStringGetUTF8CString (js_string, retval, max_size);
  }

  return (gchar*) retval;
}

/*
 * wk_js_core_result_create_json_from_result:
 * @wkjscresult: a WkJsCoreResult object
 * @jsresult: a WebKitJavasctiptResult object to create JSON from
 *
 * Creates a JSON string representation of the javascript value
 *
 * Return value: Pointer to string
 */
gchar*
wk_js_core_result_create_json_from_result (WkJsCoreResult *result, guint indent)
{
  JSValueRef js_value;
  JSContextRef js_ctx;
  JSStringRef js_string;
  WebKitJavascriptResult *jsresult;

  g_object_get (result, "jsresult", &jsresult, NULL);

  js_value = webkit_javascript_result_get_value (jsresult);
  js_ctx = webkit_javascript_result_get_global_context (jsresult);
  js_string = JSValueCreateJSONString (js_ctx, js_value, indent, NULL);

  return js_string_to_gchar(js_string);
}

/*
 * wk_js_core_result_process_result_as_string:
 * @wkjscresult: a WkJsCoreResult object
 * @jsresult: a WebKitJavascriptResult object to process value from
 *
 * Extracts the string value within a WebKitJavascriptResult object
 *
 * Return value: Pointer to string
 */
gchar*
wk_js_core_result_process_result_as_string (WkJsCoreResult *result)
{
  JSValueRef js_value;
  JSContextRef js_ctx;
  JSStringRef js_string;
  WebKitJavascriptResult *jsresult;

  g_object_get (result, "jsresult", &jsresult, NULL);

  js_value = webkit_javascript_result_get_value (jsresult);
  js_ctx = webkit_javascript_result_get_global_context (jsresult);
  js_string = JSValueToStringCopy (js_ctx, js_value, NULL);

  return js_string_to_gchar(js_string);
}

/*
 * wk_js_core_result_process_result_as_number:
 * @wkjscresult: a WkJsCoreResult object
 * @jsresult: a WebKitJavascriptResult object to process value from
 *
 * Extracts the number value within a WebKitJavascriptResult object
 *
 * Return value: Number as double
 */
gdouble
wk_js_core_result_process_result_as_number (WkJsCoreResult *result)
{
  JSValueRef js_value;
  JSContextRef js_ctx;
  double number;
  WebKitJavascriptResult *jsresult;

  g_object_get (result, "jsresult", &jsresult, NULL);

  js_value = webkit_javascript_result_get_value (jsresult);
  js_ctx = webkit_javascript_result_get_global_context (jsresult);
  number = JSValueToNumber (js_ctx, js_value, NULL);
  return (gdouble) number;
}

/*
 * wk_js_core_result_process_result_as_boolean:
 * @wkjscresult: a WkJsCoreResult object
 * @jsresult: a WebKitJavascriptResult object to process value from
 *
 * Extracts the boolean value within a WebKitJavascriptResult object
 *
 * Return value: Boolean value
 */
gboolean
wk_js_core_result_process_result_as_boolean (WkJsCoreResult *result)
{
  JSValueRef js_value;
  JSContextRef js_ctx;
  bool boolean;
  WebKitJavascriptResult *jsresult;

  g_object_get (result, "jsresult", &jsresult, NULL);

  js_value = webkit_javascript_result_get_value (jsresult);
  js_ctx = webkit_javascript_result_get_global_context (jsresult);
  boolean = JSValueToBoolean (js_ctx, js_value);
  return (gboolean) boolean;
}
