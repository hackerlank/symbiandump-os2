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
#include <stdio.h>
#include<e32std.h>
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__

int main()
{
	//int count = 2;
	bool err = false;
	__UHEAP_MARK;
	__UHEAP_FAILNEXT(2);
	{
	string myString;
	while(!err)
	{
	int retval =ESuccess;
	_LIT8(Kname,"tlit8tochar");
	TBuf8 <20>src(Kname);

	retval = Tlit8ToString(src,myString);
  
  if (retval ==EInsufficientSystemMemory)
    {

    	printf("tlit8tostring_reliability Passed\n");
    	err = true;
    	//Logging to some file can be done here
    }
  else
    {
			assert_failed = true;
				err = true;
    	printf("tlit8tostring_reliability Failed\n");
    	//Logging to some file can be done here
    }      
	}
}
	__UHEAP_MARKEND;
	__UHEAP_RESET;

    testResultXml("test_tlit8tostring_reliability");
	return 0;
}
