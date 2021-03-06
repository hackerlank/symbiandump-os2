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


#include<stdio.h>  
#include <dbus/dbus.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define LOG_FILE "c:\\logs\\bus_name_has_owner_log1.txt"
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__

void create_xml(int result)
	{
	if(result)
		assert_failed = 1;
	
	testResultXml("bus_name_has_owner");
    close_log_file();
	}

int handle_error(DBusError* error)
	{
	std_log(LOG_FILENAME_LINE,"%s", error->name);
	std_log(LOG_FILENAME_LINE,"%s", error->message);
	dbus_error_free(error);
	create_xml(1);
	return 1; 
	} 

int main()
{
	DBusConnection* connection;
	DBusError error;
	
	dbus_error_init(&error);
	connection = dbus_bus_get(DBUS_BUS_SESSION, &error);
	if(!connection || dbus_error_is_set(&error))
		return handle_error(&error);
	
	if(dbus_bus_request_name(connection, "Test.Request.Name", DBUS_NAME_FLAG_ALLOW_REPLACEMENT, &error) == -1)
	{
		std_log(LOG_FILENAME_LINE, "Error :: %s\nMessage :: %s", error.name, error.message);
		create_xml(1);
		return 1;
	}
	
	if(!dbus_bus_name_has_owner(connection, "Test.Request.Name", &error))
	{
		std_log(LOG_FILENAME_LINE, "Fail to check owner after requesting name.");
		create_xml(1);
		return 1;
	}
	
	if(dbus_bus_release_name(connection, "Test.Request.Name", &error) == -1)
	{
		std_log(LOG_FILENAME_LINE, "Error :: %s\nMessage :: %s", error.name, error.message);
		create_xml(1);
		return 1;
	}
	
	if(dbus_bus_name_has_owner(connection, "Test.Request.Name", &error))
	{
		std_log(LOG_FILENAME_LINE, "owner is there after releasing name.");
		create_xml(1);
		return 1;
	}
	
	dbus_connection_unref(connection);
	std_log(LOG_FILENAME_LINE, "Test Successful");
	create_xml(0);
	return 0;
}
