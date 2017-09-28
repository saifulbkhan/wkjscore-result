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
