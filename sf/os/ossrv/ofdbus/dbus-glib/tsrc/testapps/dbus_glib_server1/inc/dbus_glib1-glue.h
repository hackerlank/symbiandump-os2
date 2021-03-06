/*
* Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
*
*/


/* Generated by dbus-binding-tool; do not edit! */


#ifndef __dbus_glib_marshal_DBusGlibObject1_MARSHAL_H__
#define __dbus_glib_marshal_DBusGlibObject1_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* BOOLEAN:BOOLEAN,INT,INT,INT64,INT,UINT,UINT64,DOUBLE,STRING,BOXED,POINTER,POINTER (/tmp/dbus-binding-tool-c-marshallers.MSWV9T:1) */
extern void dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOOLEAN_INT_INT_INT64_INT_UINT_UINT64_DOUBLE_STRING_BOXED_POINTER_POINTER (GClosure     *closure,
                                                                                                                                  GValue       *return_value,
                                                                                                                                  guint         n_param_values,
                                                                                                                                  const GValue *param_values,
                                                                                                                                  gpointer      invocation_hint,
                                                                                                                                  gpointer      marshal_data);
void
dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOOLEAN_INT_INT_INT64_INT_UINT_UINT64_DOUBLE_STRING_BOXED_POINTER_POINTER (GClosure     *closure,
                                                                                                                      GValue       *return_value,
                                                                                                                      guint         n_param_values,
                                                                                                                      const GValue *param_values,
                                                                                                                      gpointer      invocation_hint,
                                                                                                                      gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOOLEAN_INT_INT_INT64_INT_UINT_UINT64_DOUBLE_STRING_BOXED_POINTER_POINTER) (gpointer     data1,
                                                                                                                       gboolean     arg_1,
                                                                                                                       gint         arg_2,
                                                                                                                       gint         arg_3,
                                                                                                                       gint64       arg_4,
                                                                                                                       gint         arg_5,
                                                                                                                       guint        arg_6,
                                                                                                                       guint64      arg_7,
                                                                                                                       gdouble      arg_8,
                                                                                                                       gpointer     arg_9,
                                                                                                                       gpointer     arg_10,
                                                                                                                       gpointer     arg_11,
                                                                                                                       gpointer     arg_12,
                                                                                                                       gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOOLEAN_INT_INT_INT64_INT_UINT_UINT64_DOUBLE_STRING_BOXED_POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 13);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOOLEAN_INT_INT_INT64_INT_UINT_UINT64_DOUBLE_STRING_BOXED_POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boolean (param_values + 1),
                       g_marshal_value_peek_int (param_values + 2),
                       g_marshal_value_peek_int (param_values + 3),
                       g_marshal_value_peek_int64 (param_values + 4),
                       g_marshal_value_peek_int (param_values + 5),
                       g_marshal_value_peek_uint (param_values + 6),
                       g_marshal_value_peek_uint64 (param_values + 7),
                       g_marshal_value_peek_double (param_values + 8),
                       g_marshal_value_peek_string (param_values + 9),
                       g_marshal_value_peek_boxed (param_values + 10),
                       g_marshal_value_peek_pointer (param_values + 11),
                       g_marshal_value_peek_pointer (param_values + 12),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:INT,POINTER,POINTER (/tmp/dbus-binding-tool-c-marshallers.MSWV9T:2) */
extern void dbus_glib_marshal_DBusGlibObject1_BOOLEAN__INT_POINTER_POINTER (GClosure     *closure,
                                                                            GValue       *return_value,
                                                                            guint         n_param_values,
                                                                            const GValue *param_values,
                                                                            gpointer      invocation_hint,
                                                                            gpointer      marshal_data);
void
dbus_glib_marshal_DBusGlibObject1_BOOLEAN__INT_POINTER_POINTER (GClosure     *closure,
                                                                GValue       *return_value,
                                                                guint         n_param_values,
                                                                const GValue *param_values,
                                                                gpointer      invocation_hint,
                                                                gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__INT_POINTER_POINTER) (gpointer     data1,
                                                                 gint         arg_1,
                                                                 gpointer     arg_2,
                                                                 gpointer     arg_3,
                                                                 gpointer     data2);
  register GMarshalFunc_BOOLEAN__INT_POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__INT_POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_int (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:BOXED,POINTER,POINTER (/tmp/dbus-binding-tool-c-marshallers.MSWV9T:3) */
extern void dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOXED_POINTER_POINTER (GClosure     *closure,
                                                                              GValue       *return_value,
                                                                              guint         n_param_values,
                                                                              const GValue *param_values,
                                                                              gpointer      invocation_hint,
                                                                              gpointer      marshal_data);
void
dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOXED_POINTER_POINTER (GClosure     *closure,
                                                                  GValue       *return_value,
                                                                  guint         n_param_values,
                                                                  const GValue *param_values,
                                                                  gpointer      invocation_hint,
                                                                  gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_POINTER_POINTER) (gpointer     data1,
                                                                   gpointer     arg_1,
                                                                   gpointer     arg_2,
                                                                   gpointer     arg_3,
                                                                   gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_POINTER_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_POINTER_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

G_END_DECLS

#endif /* __dbus_glib_marshal_DBusGlibObject1_MARSHAL_H__ */

#include <dbus/dbus-glib.h>
static const DBusGMethodInfo dbus_glib_DBusGlibObject1_methods[] = {
  { (GCallback) dbus_glib_object1_variable_args_method, dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOOLEAN_INT_INT_INT64_INT_UINT_UINT64_DOUBLE_STRING_BOXED_POINTER_POINTER, 0 },
  { (GCallback) dbus_glib_object1_simple_method, dbus_glib_marshal_DBusGlibObject1_BOOLEAN__INT_POINTER_POINTER, 123 },
  { (GCallback) dbus_glib_object1_struct_example_method, dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOXED_POINTER_POINTER, 195 },
  { (GCallback) dbus_glib_object1_variant_send_method, dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOXED_POINTER_POINTER, 270 },
  { (GCallback) dbus_glib_object1_dict_send_method, dbus_glib_marshal_DBusGlibObject1_BOOLEAN__BOXED_POINTER_POINTER, 348 },
};

const DBusGObjectInfo dbus_glib_DBusGlibObject1_object_info = {
  0,
  dbus_glib_DBusGlibObject1_methods,
  5,
"com.example.DBusGlibObject1\0Variable_args_method\0S\0b\0I\0b\0n\0I\0i\0i\0I\0i\0x\0I\0x\0q\0I\0i\0u\0I\0u\0t\0I\0t\0d\0I\0d\0s\0I\0s\0a\0I\0ai\0r\0O\0F\0N\0i\0\0com.example.DBusGlibObject1\0Simple_method\0S\0in_num\0I\0i\0out_num\0O\0F\0N\0i\0\0com.example.DBusGlibObject1\0Struct_example_method\0S\0st\0I\0(is)\0ret\0O\0F\0N\0i\0\0com.example.DBusGlibObject1\0Variant_send_method\0S\0in_var\0I\0v\0out_var\0O\0F\0N\0v\0\0com.example.DBusGlibObject1\0Dict_send_method\0S\0in_dict\0I\0a{ss}\0out_int\0O\0F\0N\0i\0\0\0",
"\0",
"\0"
};

