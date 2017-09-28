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

const gchar *HTML = "<p>lorem ipsum</p><p>dolor sit amet</p>";
const gchar *JS = "document.getElementsByTagName('p').length";
gint EXP = 2;

int
main (int    argc,
      char **argv)
{
  int status;
  GtkApplication *app;
  GValue exp = G_VALUE_INIT;
  TestData *test_data;

  g_value_init (&exp, G_TYPE_INT);
  g_value_set_int (&exp, EXP);

  test_data = g_malloc (sizeof (TestData));
  test_data->indent = 0;
  test_data->html = HTML;
  test_data->javascript = JS;
  test_data->expected = &exp;

  app = test_base_generate_test_run ("org.wkjscore.testint",
                                     G_APPLICATION_FLAGS_NONE,
                                     test_data);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  g_free (test_data);

  return status;
}
