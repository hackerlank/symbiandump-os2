/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-auth-util.c Would be in dbus-auth.c, but only used for tests/bus
 *
 * Copyright (C) 2002, 2003, 2004 Red Hat Inc.
 * Portion Copyright � 2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.
 * Licensed under the Academic Free License version 2.1
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include "dbus-internals.h"
#include "dbus-test.h"
#include "dbus-auth.h"

/**
 * @addtogroup DBusAuth
 * @{
 */

/** @} */

#ifdef DBUS_BUILD_TESTS
#include "dbus-test.h"
#include "dbus-auth-script.h"
#include <stdio.h>

#ifdef __SYMBIAN32__
#ifndef DBUS_DISABLE_CHECKS
/** String used in _dbus_return_if_fail macro */
const char _dbus_return_if_fail_warning_format[] =
"arguments to %s() were incorrect, assertion \"%s\" failed in file %s line %d.\n"
"This is normally a bug in some application using the D-Bus library.\n";
#endif
#endif

static dbus_bool_t
process_test_subdir (const DBusString          *test_base_dir,
                     const char                *subdir)
{
  DBusString test_directory;
  DBusString filename;
  DBusDirIter *dir;
  dbus_bool_t retval;
  DBusError error;

  retval = FALSE;
  dir = NULL;
  
  if (!_dbus_string_init (&test_directory))
    _dbus_assert_not_reached ("didn't allocate test_directory\n");

  _dbus_string_init_const (&filename, subdir);
  
  if (!_dbus_string_copy (test_base_dir, 0,
                          &test_directory, 0))
    _dbus_assert_not_reached ("couldn't copy test_base_dir to test_directory");
  
  if (!_dbus_concat_dir_and_file (&test_directory, &filename))    
    _dbus_assert_not_reached ("couldn't allocate full path");

  _dbus_string_free (&filename);
  if (!_dbus_string_init (&filename))
    _dbus_assert_not_reached ("didn't allocate filename string\n");

  dbus_error_init (&error);
  dir = _dbus_directory_open (&test_directory, &error);
  if (dir == NULL)
    {
      _dbus_warn ("Could not open %s: %s\n",
                  _dbus_string_get_const_data (&test_directory),
                  error.message);
      dbus_error_free (&error);
      goto failed;
    }

  printf ("Testing %s:\n", subdir);
  
 next:
  while (_dbus_directory_get_next_file (dir, &filename, &error))
    {
      DBusString full_path;
      
      if (!_dbus_string_init (&full_path))
        _dbus_assert_not_reached ("couldn't init string");

      if (!_dbus_string_copy (&test_directory, 0, &full_path, 0))
        _dbus_assert_not_reached ("couldn't copy dir to full_path");

      if (!_dbus_concat_dir_and_file (&full_path, &filename))
        _dbus_assert_not_reached ("couldn't concat file to dir");

      if (!_dbus_string_ends_with_c_str (&filename, ".auth-script"))
        {
          _dbus_verbose ("Skipping non-.auth-script file %s\n",
                         _dbus_string_get_const_data (&filename));
	  _dbus_string_free (&full_path);
          goto next;
        }

      printf ("    %s\n", _dbus_string_get_const_data (&filename));
      
      if (!_dbus_auth_script_run (&full_path))
        {
          _dbus_string_free (&full_path);
          goto failed;
        }
      else
        _dbus_string_free (&full_path);
    }

  if (dbus_error_is_set (&error))
    {
      _dbus_warn ("Could not get next file in %s: %s\n",
                  _dbus_string_get_const_data (&test_directory), error.message);
      dbus_error_free (&error);
      goto failed;
    }
    
  retval = TRUE;
  
 failed:

  if (dir)
    _dbus_directory_close (dir);
  _dbus_string_free (&test_directory);
  _dbus_string_free (&filename);

  return retval;
}

static dbus_bool_t
process_test_dirs (const char *test_data_dir)
{
  DBusString test_directory;
  dbus_bool_t retval;

  retval = FALSE;
  
  _dbus_string_init_const (&test_directory, test_data_dir);

  if (!process_test_subdir (&test_directory, "auth"))
    goto failed;

  retval = TRUE;
  
 failed:

  _dbus_string_free (&test_directory);
  
  return retval;
}

#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_auth_test (const char *test_data_dir)
{
  
  if (test_data_dir == NULL)
    return TRUE;
  
  if (!process_test_dirs (test_data_dir))
    return FALSE;

  return TRUE;
}

#endif /* DBUS_BUILD_TESTS */
