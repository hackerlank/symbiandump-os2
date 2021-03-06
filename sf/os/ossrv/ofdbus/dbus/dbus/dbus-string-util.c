/* -*- mode: C; c-file-style: "gnu" -*- */
/* dbus-string-util.c Would be in dbus-string.c, but not used in libdbus
 * 
 * Copyright (C) 2002, 2003, 2004, 2005 Red Hat, Inc.
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
#include "dbus-string.h"
#define DBUS_CAN_USE_DBUS_STRING_PRIVATE 1
#include "dbus-string-private.h"

/**
 * @addtogroup DBusString
 * @{
 */

/**
 * Returns whether a string ends with the given suffix
 *
 * @todo memcmp might make this faster.
 * 
 * @param a the string
 * @param c_str the C-style string
 * @returns #TRUE if the string ends with the suffix
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_string_ends_with_c_str (const DBusString *a,
                              const char       *c_str)
{
  const unsigned char *ap;
  const unsigned char *bp;
  const unsigned char *a_end;
  unsigned long c_str_len;
  const DBusRealString *real_a = (const DBusRealString*) a;
  DBUS_GENERIC_STRING_PREAMBLE (real_a);
  _dbus_assert (c_str != NULL);
  
  c_str_len = strlen (c_str);
  if (((unsigned long)real_a->len) < c_str_len)
    return FALSE;
  
  ap = real_a->str + (real_a->len - c_str_len);
  bp = (const unsigned char*) c_str;
  a_end = real_a->str + real_a->len;
  while (ap != a_end)
    {
      if (*ap != *bp)
        return FALSE;
      
      ++ap;
      ++bp;
    }

  _dbus_assert (*ap == '\0');
  _dbus_assert (*bp == '\0');
  
  return TRUE;
}

/**
 * Find the given byte scanning backward from the given start.
 * Sets *found to -1 if the byte is not found.
 *
 * @param str the string
 * @param start the place to start scanning (will not find the byte at this point)
 * @param byte the byte to find
 * @param found return location for where it was found
 * @returns #TRUE if found
 */
#ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_string_find_byte_backward (const DBusString  *str,
                                 int                start,
                                 unsigned char      byte,
                                 int               *found)
{
  int i;
  DBUS_CONST_STRING_PREAMBLE (str);
  _dbus_assert (start <= real->len);
  _dbus_assert (start >= 0);
  _dbus_assert (found != NULL);

  i = start - 1;
  while (i >= 0)
    {
      if (real->str[i] == byte)
        break;
      
      --i;
    }

  if (found)
    *found = i;

  return i >= 0;
}

/** @} */

#ifdef DBUS_BUILD_TESTS
#include "dbus-test.h"
#include <stdio.h>

static void
test_max_len (DBusString *str,
              int         max_len)
{
  if (max_len > 0)
    {
      if (!_dbus_string_set_length (str, max_len - 1))
        _dbus_assert_not_reached ("setting len to one less than max should have worked");
    }

  if (!_dbus_string_set_length (str, max_len))
    _dbus_assert_not_reached ("setting len to max len should have worked");

  if (_dbus_string_set_length (str, max_len + 1))
    _dbus_assert_not_reached ("setting len to one more than max len should not have worked");

  if (!_dbus_string_set_length (str, 0))
    _dbus_assert_not_reached ("setting len to zero should have worked");
}

static void
test_hex_roundtrip (const unsigned char *data,
                    int                  len)
{
  DBusString orig;
  DBusString encoded;
  DBusString decoded;
  int end;

  if (len < 0)
#ifdef __SYMBIAN32__  
    len = strlen ((const char *)data);
#else
    len = strlen (data);
#endif
    
  
  if (!_dbus_string_init (&orig))
    _dbus_assert_not_reached ("could not init string");

  if (!_dbus_string_init (&encoded))
    _dbus_assert_not_reached ("could not init string");
  
  if (!_dbus_string_init (&decoded))
    _dbus_assert_not_reached ("could not init string");
#ifdef __SYMBIAN32__  
  if (!_dbus_string_append_len (&orig,(const char *) data, len))
#else
  if (!_dbus_string_append_len (&orig, data, len))
#endif
    _dbus_assert_not_reached ("couldn't append orig data");

  if (!_dbus_string_hex_encode (&orig, 0, &encoded, 0))
    _dbus_assert_not_reached ("could not encode");

  if (!_dbus_string_hex_decode (&encoded, 0, &end, &decoded, 0))
    _dbus_assert_not_reached ("could not decode");
    
  _dbus_assert (_dbus_string_get_length (&encoded) == end);

  if (!_dbus_string_equal (&orig, &decoded))
    {
      const char *s;
      
      printf ("Original string %d bytes encoded %d bytes decoded %d bytes\n",
              _dbus_string_get_length (&orig),
              _dbus_string_get_length (&encoded),
              _dbus_string_get_length (&decoded));
      printf ("Original: %s\n", data);
      s = _dbus_string_get_const_data (&decoded);
      printf ("Decoded: %s\n", s);
      _dbus_assert_not_reached ("original string not the same as string decoded from hex");
    }
  
  _dbus_string_free (&orig);
  _dbus_string_free (&encoded);
  _dbus_string_free (&decoded);  
}

typedef void (* TestRoundtripFunc) (const unsigned char *data,
                                    int                  len);
static void
test_roundtrips (TestRoundtripFunc func)
{
  (* func) ((const unsigned char *)"Hello this is a string\n", -1);
  (* func) ((const unsigned char *)"Hello this is a string\n1", -1);
  (* func) ((const unsigned char *)"Hello this is a string\n12", -1);
  (* func) ((const unsigned char *)"Hello this is a string\n123", -1);
  (* func) ((const unsigned char *)"Hello this is a string\n1234", -1);
  (* func) ((const unsigned char *)"Hello this is a string\n12345", -1);
  (* func) ((const unsigned char *)"", 0);
  (* func) ((const unsigned char *)"1", 1);
  (* func) ((const unsigned char *)"12", 2);
  (* func) ((const unsigned char *)"123", 3);
  (* func) ((const unsigned char *)"1234", 4);
  (* func) ((const unsigned char *)"12345", 5);
  (* func) ((const unsigned char *)"", 1);
  (* func) ((const unsigned char *)"1", 2);
  (* func) ((const unsigned char *)"12", 3);
  (* func) ((const unsigned char *)"123", 4);
  (* func) ((const unsigned char *)"1234", 5);
  (* func) ((const unsigned char *)"12345", 6);
  {
    unsigned char buf[512];
    int i;
    
    i = 0;
    while (i < _DBUS_N_ELEMENTS (buf))
      {
        buf[i] = i;
        ++i;
      }
    i = 0;
    while (i < _DBUS_N_ELEMENTS (buf))
      {
        (* func) (buf, i);
        ++i;
      }
  }
}

#ifdef DBUS_BUILD_TESTS
/* The max length thing is sort of a historical artifact
 * from a feature that turned out to be dumb; perhaps
 * we should purge it entirely. The problem with
 * the feature is that it looks like memory allocation
 * failure, but is not a transient or resolvable failure.
 */
static void
set_max_length (DBusString *str,
                int         max_length)
{
  DBusRealString *real;
  
  real = (DBusRealString*) str;

  real->max_length = max_length;
}
#endif /* DBUS_BUILD_TESTS */

/**
 * @ingroup DBusStringInternals
 * Unit test for DBusString.
 *
 * @todo Need to write tests for _dbus_string_copy() and
 * _dbus_string_move() moving to/from each of start/middle/end of a
 * string. Also need tests for _dbus_string_move_len ()
 * 
 * @returns #TRUE on success.
 */
 #ifdef __SYMBIAN32__
EXPORT_C
#endif
dbus_bool_t
_dbus_string_test (void)
{
  DBusString str;
  DBusString other;
  int i, end;
  long v;
  double d;
  int lens[] = { 0, 1, 2, 3, 4, 5, 10, 16, 17, 18, 25, 31, 32, 33, 34, 35, 63, 64, 65, 66, 67, 68, 69, 70, 71, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136 };
  char *s;
  dbus_unichar_t ch;
  
  i = 0;
  while (i < _DBUS_N_ELEMENTS (lens))
    {
      if (!_dbus_string_init (&str))
        _dbus_assert_not_reached ("failed to init string");

      set_max_length (&str, lens[i]);
      
      test_max_len (&str, lens[i]);
      _dbus_string_free (&str);

      ++i;
    }

  /* Test shortening and setting length */
  i = 0;
  while (i < _DBUS_N_ELEMENTS (lens))
    {
      int j;
      
      if (!_dbus_string_init (&str))
        _dbus_assert_not_reached ("failed to init string");

      set_max_length (&str, lens[i]);
      
      if (!_dbus_string_set_length (&str, lens[i]))
        _dbus_assert_not_reached ("failed to set string length");

      j = lens[i];
      while (j > 0)
        {
          _dbus_assert (_dbus_string_get_length (&str) == j);
          if (j > 0)
            {
              _dbus_string_shorten (&str, 1);
              _dbus_assert (_dbus_string_get_length (&str) == (j - 1));
            }
          --j;
        }
      
      _dbus_string_free (&str);

      ++i;
    }

  /* Test equality */
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("oom");

  if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("oom");

  _dbus_string_init_const (&other, "H");
  _dbus_assert (_dbus_string_equal_substring (&str, 0, 1, &other, 0));
  _dbus_assert (_dbus_string_equal_substring (&str, 1, 0, &other, 1));
  _dbus_string_init_const (&other, "Hello");
  _dbus_assert (_dbus_string_equal_substring (&str, 0, 5, &other, 0));
  _dbus_assert (_dbus_string_equal_substring (&str, 1, 4, &other, 1));
  _dbus_assert (_dbus_string_equal_substring (&str, 2, 3, &other, 2));
  _dbus_assert (_dbus_string_equal_substring (&str, 3, 2, &other, 3));
  _dbus_assert (_dbus_string_equal_substring (&str, 4, 1, &other, 4));
  _dbus_assert (_dbus_string_equal_substring (&str, 5, 0, &other, 5));

  _dbus_assert (_dbus_string_equal_substring (&other, 0, 5, &str, 0));
  _dbus_assert (_dbus_string_equal_substring (&other, 1, 4, &str, 1));
  _dbus_assert (_dbus_string_equal_substring (&other, 2, 3, &str, 2));
  _dbus_assert (_dbus_string_equal_substring (&other, 3, 2, &str, 3));
  _dbus_assert (_dbus_string_equal_substring (&other, 4, 1, &str, 4));
  _dbus_assert (_dbus_string_equal_substring (&other, 5, 0, &str, 5));

  
  _dbus_string_init_const (&other, "World");
  _dbus_assert (_dbus_string_equal_substring (&str, 6,  5, &other, 0));
  _dbus_assert (_dbus_string_equal_substring (&str, 7,  4, &other, 1));
  _dbus_assert (_dbus_string_equal_substring (&str, 8,  3, &other, 2));
  _dbus_assert (_dbus_string_equal_substring (&str, 9,  2, &other, 3));
  _dbus_assert (_dbus_string_equal_substring (&str, 10, 1, &other, 4));
  _dbus_assert (_dbus_string_equal_substring (&str, 11, 0, &other, 5));

  _dbus_assert (_dbus_string_equal_substring (&other, 0, 5, &str, 6));
  _dbus_assert (_dbus_string_equal_substring (&other, 1, 4, &str, 7));
  _dbus_assert (_dbus_string_equal_substring (&other, 2, 3, &str, 8));
  _dbus_assert (_dbus_string_equal_substring (&other, 3, 2, &str, 9));
  _dbus_assert (_dbus_string_equal_substring (&other, 4, 1, &str, 10));
  _dbus_assert (_dbus_string_equal_substring (&other, 5, 0, &str, 11));
  
  _dbus_string_free (&str);
  
  /* Test appending data */
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");

  i = 0;
  while (i < 10)
    {
      if (!_dbus_string_append (&str, "a"))
        _dbus_assert_not_reached ("failed to append string to string\n");

      _dbus_assert (_dbus_string_get_length (&str) == i * 2 + 1);

      if (!_dbus_string_append_byte (&str, 'b'))
        _dbus_assert_not_reached ("failed to append byte to string\n");

      _dbus_assert (_dbus_string_get_length (&str) == i * 2 + 2);
                    
      ++i;
    }

  _dbus_string_free (&str);

  /* Check steal_data */
  
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");

  if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("could not append to string");

  i = _dbus_string_get_length (&str);
  
  if (!_dbus_string_steal_data (&str, &s))
    _dbus_assert_not_reached ("failed to steal data");

  _dbus_assert (_dbus_string_get_length (&str) == 0);
  _dbus_assert (((int)strlen (s)) == i);

  dbus_free (s);

  /* Check move */
  
  if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("could not append to string");

  i = _dbus_string_get_length (&str);

  if (!_dbus_string_init (&other))
    _dbus_assert_not_reached ("could not init string");
  
  if (!_dbus_string_move (&str, 0, &other, 0))
    _dbus_assert_not_reached ("could not move");

  _dbus_assert (_dbus_string_get_length (&str) == 0);
  _dbus_assert (_dbus_string_get_length (&other) == i);

  if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("could not append to string");
  
  if (!_dbus_string_move (&str, 0, &other, _dbus_string_get_length (&other)))
    _dbus_assert_not_reached ("could not move");

  _dbus_assert (_dbus_string_get_length (&str) == 0);
  _dbus_assert (_dbus_string_get_length (&other) == i * 2);

    if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("could not append to string");
  
  if (!_dbus_string_move (&str, 0, &other, _dbus_string_get_length (&other) / 2))
    _dbus_assert_not_reached ("could not move");

  _dbus_assert (_dbus_string_get_length (&str) == 0);
  _dbus_assert (_dbus_string_get_length (&other) == i * 3);
  
  _dbus_string_free (&other);

  /* Check copy */
  
  if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("could not append to string");

  i = _dbus_string_get_length (&str);
  
  if (!_dbus_string_init (&other))
    _dbus_assert_not_reached ("could not init string");
  
  if (!_dbus_string_copy (&str, 0, &other, 0))
    _dbus_assert_not_reached ("could not copy");

  _dbus_assert (_dbus_string_get_length (&str) == i);
  _dbus_assert (_dbus_string_get_length (&other) == i);

  if (!_dbus_string_copy (&str, 0, &other, _dbus_string_get_length (&other)))
    _dbus_assert_not_reached ("could not copy");

  _dbus_assert (_dbus_string_get_length (&str) == i);
  _dbus_assert (_dbus_string_get_length (&other) == i * 2);
  _dbus_assert (_dbus_string_equal_c_str (&other,
                                          "Hello WorldHello World"));

  if (!_dbus_string_copy (&str, 0, &other, _dbus_string_get_length (&other) / 2))
    _dbus_assert_not_reached ("could not copy");

  _dbus_assert (_dbus_string_get_length (&str) == i);
  _dbus_assert (_dbus_string_get_length (&other) == i * 3);
  _dbus_assert (_dbus_string_equal_c_str (&other,
                                          "Hello WorldHello WorldHello World"));
  
  _dbus_string_free (&str);
  _dbus_string_free (&other);

  /* Check replace */

  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");
  
  if (!_dbus_string_append (&str, "Hello World"))
    _dbus_assert_not_reached ("could not append to string");

  i = _dbus_string_get_length (&str);
  
  if (!_dbus_string_init (&other))
    _dbus_assert_not_reached ("could not init string");
  
  if (!_dbus_string_replace_len (&str, 0, _dbus_string_get_length (&str),
                                 &other, 0, _dbus_string_get_length (&other)))
    _dbus_assert_not_reached ("could not replace");

  _dbus_assert (_dbus_string_get_length (&str) == i);
  _dbus_assert (_dbus_string_get_length (&other) == i);
  _dbus_assert (_dbus_string_equal_c_str (&other, "Hello World"));
  
  if (!_dbus_string_replace_len (&str, 0, _dbus_string_get_length (&str),
                                 &other, 5, 1))
    _dbus_assert_not_reached ("could not replace center space");

  _dbus_assert (_dbus_string_get_length (&str) == i);
  _dbus_assert (_dbus_string_get_length (&other) == i * 2 - 1);
  _dbus_assert (_dbus_string_equal_c_str (&other,
                                          "HelloHello WorldWorld"));

  
  if (!_dbus_string_replace_len (&str, 1, 1,
                                 &other,
                                 _dbus_string_get_length (&other) - 1,
                                 1))
    _dbus_assert_not_reached ("could not replace end character");
  
  _dbus_assert (_dbus_string_get_length (&str) == i);
  _dbus_assert (_dbus_string_get_length (&other) == i * 2 - 1);
  _dbus_assert (_dbus_string_equal_c_str (&other,
                                          "HelloHello WorldWorle"));
  
  _dbus_string_free (&str);
  _dbus_string_free (&other);
  
  /* Check append/get unichar */
  
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");

  ch = 0;
  if (!_dbus_string_append_unichar (&str, 0xfffc))
    _dbus_assert_not_reached ("failed to append unichar");

  _dbus_string_get_unichar (&str, 0, &ch, &i);

  _dbus_assert (ch == 0xfffc);
  _dbus_assert (i == _dbus_string_get_length (&str));

  _dbus_string_free (&str);

  /* Check insert/set/get byte */
  
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");

  if (!_dbus_string_append (&str, "Hello"))
    _dbus_assert_not_reached ("failed to append Hello");

  _dbus_assert (_dbus_string_get_byte (&str, 0) == 'H');
  _dbus_assert (_dbus_string_get_byte (&str, 1) == 'e');
  _dbus_assert (_dbus_string_get_byte (&str, 2) == 'l');
  _dbus_assert (_dbus_string_get_byte (&str, 3) == 'l');
  _dbus_assert (_dbus_string_get_byte (&str, 4) == 'o');

  _dbus_string_set_byte (&str, 1, 'q');
  _dbus_assert (_dbus_string_get_byte (&str, 1) == 'q');

  if (!_dbus_string_insert_bytes (&str, 0, 1, 255))
    _dbus_assert_not_reached ("can't insert byte");

  if (!_dbus_string_insert_bytes (&str, 2, 4, 'Z'))
    _dbus_assert_not_reached ("can't insert byte");

  if (!_dbus_string_insert_bytes (&str, _dbus_string_get_length (&str), 1, 'W'))
    _dbus_assert_not_reached ("can't insert byte");
  
  _dbus_assert (_dbus_string_get_byte (&str, 0) == 255);
  _dbus_assert (_dbus_string_get_byte (&str, 1) == 'H');
  _dbus_assert (_dbus_string_get_byte (&str, 2) == 'Z');
  _dbus_assert (_dbus_string_get_byte (&str, 3) == 'Z');
  _dbus_assert (_dbus_string_get_byte (&str, 4) == 'Z');
  _dbus_assert (_dbus_string_get_byte (&str, 5) == 'Z');
  _dbus_assert (_dbus_string_get_byte (&str, 6) == 'q');
  _dbus_assert (_dbus_string_get_byte (&str, 7) == 'l');
  _dbus_assert (_dbus_string_get_byte (&str, 8) == 'l');
  _dbus_assert (_dbus_string_get_byte (&str, 9) == 'o');
  _dbus_assert (_dbus_string_get_byte (&str, 10) == 'W');

  _dbus_string_free (&str);
  
  /* Check append/parse int/double */
  
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");

  if (!_dbus_string_append_int (&str, 27))
    _dbus_assert_not_reached ("failed to append int");

  i = _dbus_string_get_length (&str);

  if (!_dbus_string_parse_int (&str, 0, &v, &end))
    _dbus_assert_not_reached ("failed to parse int");

  _dbus_assert (v == 27);
  _dbus_assert (end == i);

  _dbus_string_free (&str);
  
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");
  
  if (!_dbus_string_append_double (&str, 50.3))
    _dbus_assert_not_reached ("failed to append float");

  i = _dbus_string_get_length (&str);

  if (!_dbus_string_parse_double (&str, 0, &d, &end))
    _dbus_assert_not_reached ("failed to parse float");

  _dbus_assert (d > (50.3 - 1e-6) && d < (50.3 + 1e-6));
  _dbus_assert (end == i);

  _dbus_string_free (&str);

  /* Test find */
  if (!_dbus_string_init (&str))
    _dbus_assert_not_reached ("failed to init string");

  if (!_dbus_string_append (&str, "Hello"))
    _dbus_assert_not_reached ("couldn't append to string");
  
  if (!_dbus_string_find (&str, 0, "He", &i))
    _dbus_assert_not_reached ("didn't find 'He'");
  _dbus_assert (i == 0);

  if (!_dbus_string_find (&str, 0, "Hello", &i))
    _dbus_assert_not_reached ("didn't find 'Hello'");
  _dbus_assert (i == 0);
  
  if (!_dbus_string_find (&str, 0, "ello", &i))
    _dbus_assert_not_reached ("didn't find 'ello'");
  _dbus_assert (i == 1);

  if (!_dbus_string_find (&str, 0, "lo", &i))
    _dbus_assert_not_reached ("didn't find 'lo'");
  _dbus_assert (i == 3);

  if (!_dbus_string_find (&str, 2, "lo", &i))
    _dbus_assert_not_reached ("didn't find 'lo'");
  _dbus_assert (i == 3);

  if (_dbus_string_find (&str, 4, "lo", &i))
    _dbus_assert_not_reached ("did find 'lo'");
  
  if (!_dbus_string_find (&str, 0, "l", &i))
    _dbus_assert_not_reached ("didn't find 'l'");
  _dbus_assert (i == 2);

  if (!_dbus_string_find (&str, 0, "H", &i))
    _dbus_assert_not_reached ("didn't find 'H'");
  _dbus_assert (i == 0);

  if (!_dbus_string_find (&str, 0, "", &i))
    _dbus_assert_not_reached ("didn't find ''");
  _dbus_assert (i == 0);
  
  if (_dbus_string_find (&str, 0, "Hello!", NULL))
    _dbus_assert_not_reached ("Did find 'Hello!'");

  if (_dbus_string_find (&str, 0, "Oh, Hello", NULL))
    _dbus_assert_not_reached ("Did find 'Oh, Hello'");
  
  if (_dbus_string_find (&str, 0, "ill", NULL))
    _dbus_assert_not_reached ("Did find 'ill'");

  if (_dbus_string_find (&str, 0, "q", NULL))
    _dbus_assert_not_reached ("Did find 'q'");

  if (!_dbus_string_find_to (&str, 0, 2, "He", NULL))
    _dbus_assert_not_reached ("Didn't find 'He'");

  if (_dbus_string_find_to (&str, 0, 2, "Hello", NULL))
    _dbus_assert_not_reached ("Did find 'Hello'");

  if (!_dbus_string_find_byte_backward (&str, _dbus_string_get_length (&str), 'H', &i))
    _dbus_assert_not_reached ("Did not find 'H'");
  _dbus_assert (i == 0);

  if (!_dbus_string_find_byte_backward (&str, _dbus_string_get_length (&str), 'o', &i))
    _dbus_assert_not_reached ("Did not find 'o'");
  _dbus_assert (i == _dbus_string_get_length (&str) - 1);

  if (_dbus_string_find_byte_backward (&str, _dbus_string_get_length (&str) - 1, 'o', &i))
    _dbus_assert_not_reached ("Did find 'o'");
  _dbus_assert (i == -1);

  if (_dbus_string_find_byte_backward (&str, 1, 'e', &i))
    _dbus_assert_not_reached ("Did find 'e'");
  _dbus_assert (i == -1);

  if (!_dbus_string_find_byte_backward (&str, 2, 'e', &i))
    _dbus_assert_not_reached ("Didn't find 'e'");
  _dbus_assert (i == 1);
  
  _dbus_string_free (&str);

  /* Hex encoding */
  _dbus_string_init_const (&str, "cafebabe, this is a bogus hex string");
  if (!_dbus_string_init (&other))
    _dbus_assert_not_reached ("could not init string");

  if (!_dbus_string_hex_decode (&str, 0, &end, &other, 0))
    _dbus_assert_not_reached ("deccoded bogus hex string with no error");

  _dbus_assert (end == 8);

  _dbus_string_free (&other);

  test_roundtrips (test_hex_roundtrip);
  
  _dbus_string_free (&str);
  
  return TRUE;
}

#endif /* DBUS_BUILD_TESTS */
