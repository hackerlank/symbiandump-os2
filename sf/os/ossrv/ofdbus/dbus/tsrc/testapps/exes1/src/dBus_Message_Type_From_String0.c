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

#define LOG_FILE "c:\\logs\\dBus_Message_Type_From_string01_log1.txt"
#include "std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__

void create_xml(int result)
{
	if(result)
		assert_failed = 1;
	
	testResultXml("dBus_Message_Type_From_string0");
	close_log_file();
}

int main()
{
 	if(DBUS_MESSAGE_TYPE_METHOD_CALL != dbus_message_type_from_string("method_call"))
	{
		std_log(LOG_FILENAME_LINE, "dbus_message_type_from_string() failed for DBUS_MESSAGE_TYPE_METHOD_CALL.");
		create_xml(1);
		return 1;
	}
	
	if(DBUS_MESSAGE_TYPE_METHOD_RETURN != dbus_message_type_from_string("method_return"))
	{
		std_log(LOG_FILENAME_LINE, "dbus_message_type_from_string() failed for DBUS_MESSAGE_TYPE_METHOD_RETURN.");
		create_xml(1);
		return 1;
	}
	
	if(DBUS_MESSAGE_TYPE_SIGNAL != dbus_message_type_from_string("signal"))
	{
		std_log(LOG_FILENAME_LINE, "dbus_message_type_from_string() failed for DBUS_MESSAGE_TYPE_SIGNAL..");
		create_xml(1);
		return 1;
	}
	
	if(DBUS_MESSAGE_TYPE_ERROR != dbus_message_type_from_string("error"))
	{
		std_log(LOG_FILENAME_LINE, "dbus_message_type_from_string() failed for DBUS_MESSAGE_TYPE_ERROR.");
		create_xml(1);
		return 1;
	}
	
	if(DBUS_MESSAGE_TYPE_INVALID != dbus_message_type_from_string("invalid"))
	{
		std_log(LOG_FILENAME_LINE, "dbus_message_type_from_string() failed for DBUS_MESSAGE_TYPE_INVALID.");
		create_xml(1);
		return 1;
	}
	
	std_log(LOG_FILENAME_LINE, "SUCCESS");
	create_xml(0);
	return 0;
}
