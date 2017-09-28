#include "testbase.h"

const gchar *HTML = "<p id=" "para" ">lorem ipsum</p>";
const gchar *JS = "document.getElementById('para').innerHTML";
const gchar *EXP = "lorem ipsum";

int
main (int    argc,
      char **argv)
{
  int status;
  GtkApplication *app;
  GValue exp = G_VALUE_INIT;
  TestData *test_data;

  g_value_init (&exp, G_TYPE_STRING);
  g_value_set_static_string (&exp, EXP);

  test_data = g_malloc (sizeof (TestData));
  test_data->indent = 0;
  test_data->html = HTML;
  test_data->javascript = JS;
  test_data->expected = &exp;

  app = test_base_generate_test_run ("org.wkjscore.teststring",
                                     G_APPLICATION_FLAGS_NONE,
                                     test_data);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  g_free (test_data);

  return status;
}
