#ifndef __TEST_BASE_H__
#define __TEST_BASE_H__

#include <gtk/gtk.h>

typedef struct {
  guint         indent;
  const gchar  *html;
  const gchar  *javascript;
  GValue       *expected;
} TestData;

GtkApplication*
test_base_generate_test_run (const gchar      *app_id,
                             GApplicationFlags flags,
                             TestData         *test_data);

#endif /* __TEST_BASE_H__ */
