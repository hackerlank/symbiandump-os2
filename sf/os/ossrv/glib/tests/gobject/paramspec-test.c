/* GLIB - Library of useful routines for C programming
 * Copyright (C) 1995-1997  Peter Mattis, Spencer Kimball and Josh MacDonald
 * Portions copyright (c) 2006-2009 Nokia Corporation.  All rights reserved.
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GLib Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GLib Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GLib at ftp://ftp.gtk.org/pub/gtk/. 
 */

#undef G_DISABLE_ASSERT
#undef G_LOG_DOMAIN

#include <string.h>

#include <glib.h>
#include <glib-object.h>

#ifdef __SYMBIAN32__
#include <gobject_global.h>
#include "mrt2_glib2_test.h"
#endif //__SYMBIAN32__
static void
test_param_spec_char (void)
{
  GParamSpec *pspec;
  GValue value = { 0, };
  gboolean modified;
 
  pspec = g_param_spec_char ("char", "nick", "blurb",
			     20, 40, 30, G_PARAM_READWRITE);

  g_assert (strcmp (g_param_spec_get_name (pspec), "char") == 0);
  g_assert (strcmp (g_param_spec_get_nick (pspec), "nick") == 0);
  g_assert (strcmp (g_param_spec_get_blurb (pspec), "blurb") == 0);

  g_value_init (&value, G_TYPE_CHAR);
  g_value_set_char (&value, 30);

  g_assert (g_param_value_defaults (pspec, &value));
  
  g_value_set_char (&value, 0);
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_char (&value) == 20);

  g_value_set_char (&value, 20);
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified && g_value_get_char (&value) == 20);

  g_value_set_char (&value, 40);
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified && g_value_get_char (&value) == 40);

  g_value_set_char (&value, 60);
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_char (&value) == 40);

  g_param_spec_unref (pspec);
}

static void
test_param_spec_string (void)
{
  GParamSpec *pspec;
  GValue value = { 0, };
  gboolean modified;

  pspec = g_param_spec_string ("string", "nick", "blurb",
                               NULL, G_PARAM_READWRITE);
  g_value_init (&value, G_TYPE_STRING);

  g_value_set_string (&value, "foobar");
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified);

  g_value_set_string (&value, "");
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified && g_value_get_string (&value) != NULL);

  /* test ensure_non_null */

  G_PARAM_SPEC_STRING (pspec)->ensure_non_null = TRUE;

  g_value_set_string (&value, NULL);
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value) != NULL);

  G_PARAM_SPEC_STRING (pspec)->ensure_non_null = FALSE;

  /* test null_fold_if_empty */

  G_PARAM_SPEC_STRING (pspec)->null_fold_if_empty = TRUE;

  g_value_set_string (&value, "");
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value) == NULL);

  g_value_set_static_string (&value, "");
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value) == NULL);

  G_PARAM_SPEC_STRING (pspec)->null_fold_if_empty = FALSE;

  /* test cset_first */

  G_PARAM_SPEC_STRING (pspec)->cset_first = g_strdup ("abc");
  G_PARAM_SPEC_STRING (pspec)->substitutor = '-';

  g_value_set_string (&value, "ABC");
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value)[0] == '-');

  g_value_set_static_string (&value, "ABC");
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value)[0] == '-');

  /* test cset_nth */

  G_PARAM_SPEC_STRING (pspec)->cset_nth = g_strdup ("abc");

  g_value_set_string (&value, "aBC");
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value)[1] == '-');

  g_value_set_static_string (&value, "aBC");
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_string (&value)[1] == '-');

  g_value_unset (&value);
  g_param_spec_unref (pspec);
}

static void
test_param_spec_override (void)
{
  GParamSpec *ospec, *pspec;
  GValue value = { 0, };
  gboolean modified;
 
  ospec = g_param_spec_char ("char", "nick", "blurb",
			     20, 40, 30, G_PARAM_READWRITE);

  pspec = g_param_spec_override ("override", ospec);

  g_assert (strcmp (g_param_spec_get_name (pspec), "override") == 0);
  g_assert (strcmp (g_param_spec_get_nick (pspec), "nick") == 0);
  g_assert (strcmp (g_param_spec_get_blurb (pspec), "blurb") == 0);

  g_value_init (&value, G_TYPE_CHAR);
  g_value_set_char (&value, 30);

  g_assert (g_param_value_defaults (pspec, &value));
  
  g_value_set_char (&value, 0);
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_char (&value) == 20);

  g_value_set_char (&value, 20);
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified && g_value_get_char (&value) == 20);

  g_value_set_char (&value, 40);
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified && g_value_get_char (&value) == 40);

  g_value_set_char (&value, 60);
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_char (&value) == 40);

  g_param_spec_unref (pspec);
}

static void
test_param_spec_gtype (void)
{
  GParamSpec *pspec;
  GValue value = { 0, };
  gboolean modified;
  
  pspec = g_param_spec_gtype ("gtype", "nick", "blurb",
			      G_TYPE_PARAM, G_PARAM_READWRITE);
  
  g_value_init (&value, G_TYPE_GTYPE);
  g_value_set_gtype (&value, G_TYPE_PARAM);

  g_assert (g_param_value_defaults (pspec, &value));
  
  g_value_set_gtype (&value, G_TYPE_INT);
  modified = g_param_value_validate (pspec, &value);
  g_assert (modified && g_value_get_gtype (&value) == G_TYPE_PARAM);

  g_value_set_gtype (&value, G_TYPE_PARAM_INT);
  modified = g_param_value_validate (pspec, &value);
  g_assert (!modified && g_value_get_gtype (&value) == G_TYPE_PARAM_INT);
}

int
main (int argc, char *argv[])
{
#ifdef __SYMBIAN32__
  g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
  g_set_print_handler(mrtPrintHandler);
  #endif /*__SYMBIAN32__*/
  g_type_init (); 
  
  test_param_spec_char ();
  test_param_spec_string ();
  test_param_spec_override ();
  test_param_spec_gtype ();

#ifdef __SYMBIAN32__
testResultXml("paramspec-test");
#endif /*__SYMBIAN32__*/
  return 0;
}
