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
#include "gobject/gvaluecollector.h"
#ifdef __SYMBIAN32__
#include "mrt2_glib2_test.h"
#endif /*__SYMBIAN32__*/

static void
test_enum_transformation (void)
{ 
  GType type; 
  GValue orig = { 0, };
  GValue xform = { 0, }; 
  GEnumValue values[] = { {0,"0","0"}, {1,"1","1"}}; 
  
 type = g_enum_register_static ("TestEnum", values); 
  
 g_value_init (&orig, type); 
 g_value_set_enum (&orig, 1); 

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_CHAR); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_char (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_UCHAR); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_uchar (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_INT); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_int (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_UINT); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_uint (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_LONG); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_long (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_ULONG); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_ulong (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_INT64); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_int64 (&xform) == 1);

 memset (&xform, 0, sizeof (GValue));
 g_value_init (&xform, G_TYPE_UINT64); 
 g_value_transform (&orig, &xform); 
 g_assert (g_value_get_uint64 (&xform) == 1);
}


static void
test_gtype_value (void)
{
  GType type;
  GValue value = { 0, };
  GValue copy = { 0, };

  g_value_init (&value, G_TYPE_GTYPE);

  g_value_set_gtype (&value, G_TYPE_BOXED);
  type = g_value_get_gtype (&value);
  g_assert (type == G_TYPE_BOXED);

  g_value_init (&copy, G_TYPE_GTYPE);
  g_value_copy (&value, &copy);
  type = g_value_get_gtype (&copy);
  g_assert (type == G_TYPE_BOXED);
}

static gchar *
collect (GValue *value, ...)
{
  gchar *error;
  va_list var_args;

  error = NULL;

  va_start (var_args, value);
  G_VALUE_COLLECT (value, var_args, 0, &error);
  va_end (var_args);

  return error;
}	 

static gchar *
lcopy (GValue *value, ...)
{
  gchar *error;
  va_list var_args;

  error = NULL;

  va_start (var_args, value);
  G_VALUE_LCOPY (value, var_args, 0, &error);
  va_end (var_args);

  return error;
}	 

static void
test_collection (void)
{
  GValue value = { 0, };
  gchar *error;
  
  g_value_init (&value, G_TYPE_CHAR);
  error = collect (&value, 'c');
  g_assert (error == NULL);
  g_assert (g_value_get_char (&value) == 'c');
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_UCHAR);
  error = collect (&value, 129);
  g_assert (error == NULL);
  g_assert (g_value_get_uchar (&value) == 129);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_BOOLEAN);
  error = collect (&value, TRUE);
  g_assert (error == NULL);
  g_assert (g_value_get_boolean (&value) == TRUE);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_INT);
  error = collect (&value, G_MAXINT);
  g_assert (error == NULL);
  g_assert (g_value_get_int (&value) == G_MAXINT);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_UINT);
  error = collect (&value, G_MAXUINT);
  g_assert (error == NULL);
  g_assert (g_value_get_uint (&value) == G_MAXUINT);
  
  g_value_unset (&value);  
  g_value_init (&value, G_TYPE_LONG);
  error = collect (&value, G_MAXLONG);
  g_assert (error == NULL);
  g_assert (g_value_get_long (&value) == G_MAXLONG);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_ULONG);
  error = collect (&value, G_MAXULONG);
  g_assert (error == NULL);
  g_assert (g_value_get_ulong (&value) == G_MAXULONG);
  
  g_value_unset (&value);  
  g_value_init (&value, G_TYPE_INT64);
  error = collect (&value, G_MAXINT64);
  g_assert (error == NULL);
  g_assert (g_value_get_int64 (&value) == G_MAXINT64);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_UINT64);
  error = collect (&value, G_MAXUINT64);
  g_assert (error == NULL);
  g_assert (g_value_get_uint64 (&value) == G_MAXUINT64);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_FLOAT);
  error = collect (&value, G_MAXFLOAT);
  g_assert (error == NULL);
  g_assert (g_value_get_float (&value) == G_MAXFLOAT);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_DOUBLE);
  error = collect (&value, G_MAXDOUBLE);
  g_assert (error == NULL);
  g_assert (g_value_get_double (&value) == G_MAXDOUBLE);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_STRING);
  error = collect (&value, "string ?");
  g_assert (error == NULL);
  g_assert (strcmp (g_value_get_string (&value), "string ?") == 0);
  
  g_value_unset (&value);
  g_value_init (&value, G_TYPE_GTYPE);
  error = collect (&value, G_TYPE_BOXED);
  g_assert (error == NULL);
  g_assert (g_value_get_gtype (&value) == G_TYPE_BOXED);
}

static void
test_copying (void)
{
  GValue value = { 0, };
  gchar *error;

  {
    gchar c = 0;

    g_value_init (&value, G_TYPE_CHAR);
    g_value_set_char (&value, 'c');
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == 'c');
  }  

  {
    guchar c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UCHAR);
    g_value_set_uchar (&value, 129);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == 129);
  }  

  {
    gint c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_INT);
    g_value_set_int (&value, G_MAXINT);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXINT);
  }  

  {
    guint c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT);
    g_value_set_uint (&value, G_MAXUINT);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXUINT);
  }  

  {
    glong c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_LONG);
    g_value_set_long (&value, G_MAXLONG);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXLONG);
  }  

  {
    gulong c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_ULONG);
    g_value_set_ulong (&value, G_MAXULONG);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXULONG);
  }  

  {
    gint64 c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_INT64);
    g_value_set_int64 (&value, G_MAXINT64);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXINT64);
  }  

  {
    guint64 c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_UINT64);
    g_value_set_uint64 (&value, G_MAXUINT64);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXUINT64);
  }  

  {
    gfloat c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_FLOAT);
    g_value_set_float (&value, G_MAXFLOAT);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXFLOAT);
  }  

  {
    gdouble c = 0;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_DOUBLE);
    g_value_set_double (&value, G_MAXDOUBLE);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_MAXDOUBLE);
  }  

  {
    gchar *c = NULL;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_STRING);
    g_value_set_string (&value, "string ?");
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (strcmp (c, "string ?") == 0);
  }  

  {
    GType c = G_TYPE_NONE;

    g_value_unset (&value);
    g_value_init (&value, G_TYPE_GTYPE);
    g_value_set_gtype (&value, G_TYPE_BOXED);
    error = lcopy (&value, &c);
    g_assert (error == NULL);
    g_assert (c == G_TYPE_BOXED);
  }  
}


int
main (int argc, char *argv[])
{
  #ifdef __SYMBIAN32__
  
  g_log_set_handler (NULL,  G_LOG_FLAG_FATAL| G_LOG_FLAG_RECURSION | G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING | G_LOG_LEVEL_MESSAGE | G_LOG_LEVEL_INFO | G_LOG_LEVEL_DEBUG, &mrtLogHandler, NULL);
  g_set_print_handler(mrtPrintHandler);
  #endif /*__SYMBIAN32__*/
  g_type_init (); 
  
  test_enum_transformation ();
  test_gtype_value ();
  test_collection ();
  test_copying ();
  #if __SYMBIAN32__
  testResultXml("gvalue-test");
  #endif /* EMULATOR */

  return 0;
}
