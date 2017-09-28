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

#include "testbase.h"
#include "wkjscoreresult.h"

static void
web_view_javascript_finished (GObject      *object,
                              GAsyncResult *result,
                              gpointer      user_data)
{
  WebKitJavascriptResult *jsresult;
  WkJsCoreResult         *res;
  GError                 *error = NULL;
  TestData               *test_data = user_data;
  GValue                 *expected;
  gchar                  *string = NULL;
  gboolean                boolean;
  gint                    integer;
  gdouble                 dub;

  jsresult = webkit_web_view_run_javascript_finish (WEBKIT_WEB_VIEW (object),
                                                    result,
                                                    &error);
  if (!jsresult) {
    g_error ("Error running javascript: %s", error->message);
    g_error_free (error);
    return;
  }

  res = wk_js_core_result_new (jsresult);
  expected = test_data->expected;
  switch (G_VALUE_TYPE (expected))
    {
    case G_TYPE_BOOLEAN:
      boolean = wk_js_core_result_process_result_as_boolean (res);
      g_assert (wk_js_core_result_get_result_type (res) == _BOOLEAN);
      g_assert (boolean == g_value_get_boolean (expected));
      break;

    case G_TYPE_INT:
      integer = wk_js_core_result_process_result_as_number (res);
      g_assert (wk_js_core_result_get_result_type (res) == _NUMBER);
      g_assert (integer == g_value_get_int (expected));
      break;

    case G_TYPE_DOUBLE:
      dub = wk_js_core_result_process_result_as_number (res);
      g_assert (wk_js_core_result_get_result_type (res) == _NUMBER);
      g_assert (dub == g_value_get_double (expected));
      break;

    case G_TYPE_STRING:
      /* treat as json request if given a positive indentation value
       * otherwise process as regular string */
      if (test_data->indent) {
        string = wk_js_core_result_create_json_from_result (res,
                                                            test_data->indent);
        g_assert (g_strcmp0 (string, g_value_get_string (expected)) == 0);
      } else {
        string = wk_js_core_result_process_result_as_string (res);
        g_assert (wk_js_core_result_get_result_type(res) == _STRING);
        g_assert (g_strcmp0 (string, g_value_get_string (expected)) == 0);
      }
      break;

    default:
      // Not more test types.
      break;
    }
  g_print ("Javascript execution complete.\n");
  g_object_unref (res);
  webkit_javascript_result_unref (jsresult);
}

static void
web_view_load_changed (WebKitWebView  *webview,
                       WebKitLoadEvent load_event,
                       gpointer        user_data)
{
  TestData *test_data = user_data;

  switch (load_event)
    {
    case WEBKIT_LOAD_STARTED:
      g_print ("Loading HTML content...\n");
      break;

    case WEBKIT_LOAD_FINISHED:
      g_print ("Executing javascript code...\n");
      webkit_web_view_run_javascript (webview,
                                      test_data->javascript,
                                      NULL,
                                      web_view_javascript_finished,
                                      test_data);
      break;

    default:
      // ignoring other load events.
      break;
    }
}

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  GtkWidget *window;
  GtkWidget *scrolled;
  GtkWidget *webview;
  TestData  *test_data = user_data;

  /* create a new window, and set its title */
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Test Window");
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Here we construct the container that is going to house our webview */
  scrolled = gtk_scrolled_window_new (NULL, NULL);

  /* Pack the container in the window */
  gtk_container_add (GTK_CONTAINER (window), scrolled);

  webview = webkit_web_view_new();
  g_signal_connect (webview, "load-changed",
                    G_CALLBACK (web_view_load_changed),
                    test_data);

  /* Place the webview in the scrolled window */
  gtk_container_add (GTK_CONTAINER (scrolled), webview);
  gtk_widget_show_all (window);

  webkit_web_view_load_html (WEBKIT_WEB_VIEW (webview), test_data->html, NULL);
}

GtkApplication*
test_base_generate_test_run (const gchar      *app_id,
                             GApplicationFlags flags,
                             TestData         *test_data)
{
  GtkApplication *app;

  app = gtk_application_new (app_id, flags);
  g_signal_connect (app,
                    "activate",
                    G_CALLBACK (activate),
                    test_data);
  return app;
}
