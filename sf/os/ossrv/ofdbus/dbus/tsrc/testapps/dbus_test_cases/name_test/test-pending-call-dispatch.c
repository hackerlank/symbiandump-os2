/* Portion Copyright � 2008 Nokia Corporation and/or its subsidiary(-ies). All rights reserved.*/
/**
* Test to make sure we don't get stuck polling a dbus connection
* which has no data on the socket.  This was an issue where
* one pending call would read all the data off the bus
* and the second pending call would not check to see
* if its data had already been read before polling the connection
* and blocking.
**/

#include <dbus/dbus.h>
#ifndef __SYMBIAN32__
#include <dbus/dbus-sysdeps.h>
#else
#include "dbus-sysdeps.h"
#endif //__SYMBIAN32__
#include <stdio.h>
#include <stdlib.h>

#define LOG_FILE "c:\\logs\\test_pending_call_dispatch_log1.txt"
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__

void create_xml(int result)
	{
	if(result)
		assert_failed = 1;
	
	testResultXml("test_pending_call_dispatch");
    close_log_file();
	}


static void
_run_iteration (DBusConnection *conn)
{
  DBusPendingCall *echo_pending;
  DBusPendingCall *dbus_pending;
  DBusMessage *method;
  DBusMessage *reply;
  char *echo = "echo";

  /* send the first message */
  method = dbus_message_new_method_call ("org.freedesktop.DBus.TestSuiteEchoService",
                                         "/org/freedesktop/TestSuite",
                                         "org.freedesktop.TestSuite",
                                         "Echo");

  dbus_message_append_args (method, DBUS_TYPE_STRING, &echo, NULL);
  dbus_connection_send_with_reply (conn, method, &echo_pending, -1);
  dbus_message_unref (method);
  
  /* send the second message */
  method = dbus_message_new_method_call (DBUS_SERVICE_DBUS,
                                         DBUS_PATH_DBUS,
                                         "org.freedesktop.Introspectable",
                                         "Introspect");

  dbus_connection_send_with_reply (conn, method, &dbus_pending, -1);
  dbus_message_unref (method);

  /* block on the second message (should return immediately) */
  dbus_pending_call_block (dbus_pending);

  /* block on the first message */
  /* if it does not return immediately chances 
     are we hit the block in poll bug */
  dbus_pending_call_block (echo_pending);

  /* check the reply only to make sure we
     are not getting errors unrelated
     to the block in poll bug */
  reply = dbus_pending_call_steal_reply (echo_pending);

  if (reply == NULL)
    {
      printf ("Failed: Reply is NULL ***\n");
      std_log(LOG_FILENAME_LINE, "Failed: Reply is NULL ***\n");
      create_xml(1);
      exit (1);
    }

  if (dbus_message_get_type (reply) == DBUS_MESSAGE_TYPE_ERROR)
    {
      printf ("Failed: Reply is error: %s ***\n", dbus_message_get_error_name (reply));
      std_log(LOG_FILENAME_LINE, "Failed: Reply is error: %s ***\n", dbus_message_get_error_name (reply));
      create_xml(1);
      exit (1);
    } 

  dbus_message_unref (reply);
  dbus_pending_call_unref (dbus_pending);
  dbus_pending_call_unref (echo_pending);
  
}

int
main ()
{
  long start_tv_sec, start_tv_usec;
  long end_tv_sec, end_tv_usec;
  int i;
  DBusMessage *method;
  DBusConnection *conn;
  DBusError error;
  
  /* Time each iteration and make sure it doesn't take more than 5 seconds
     to complete.  Outside influences may cause connections to take longer
     but if it does and we are stuck in a poll call then we know the 
     stuck in poll bug has come back to haunt us */

  printf ("*** Testing stuck in poll\n");
  std_log(LOG_FILENAME_LINE, "*** Testing stuck in poll\n");
  
  dbus_error_init (&error);

  conn = dbus_bus_get (DBUS_BUS_SESSION, &error);

  /* run 100 times to make sure */
  for (i = 0; i < 100; i++)
    {
      long delta;
      
      _dbus_get_current_time (&start_tv_sec, &start_tv_usec);
      _run_iteration (conn);
      _dbus_get_current_time (&end_tv_sec, &end_tv_usec);

      /* we just care about seconds */
      delta = end_tv_sec - start_tv_sec;
      printf ("Iter %i: %lis\n", i, delta);
      std_log(LOG_FILENAME_LINE, "Iter %i: %lis\n", i, delta);
      if (delta >= 5)
        {
	  printf ("Failed: looks like we might have been be stuck in poll ***\n");
      std_log(LOG_FILENAME_LINE, "Failed: looks like we might have been be stuck in poll ***\n");
	  create_xml(1);
	  exit (1);
	}
    }
 
  method = dbus_message_new_method_call ("org.freedesktop.TestSuiteEchoService",
                                         "/org/freedesktop/TestSuite",
                                         "org.freedesktop.TestSuite",
                                         "Exit");
  dbus_connection_send (conn, method, NULL);
  dbus_message_unref (method);

  printf ("Success ***\n");
  std_log(LOG_FILENAME_LINE, "Test Successful.");
//  ch=getchar();
  create_xml(0);
  exit (0);
}
