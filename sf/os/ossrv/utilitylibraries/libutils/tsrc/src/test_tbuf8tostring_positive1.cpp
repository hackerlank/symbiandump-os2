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
    int retval =ESuccess;
    string s;
    __UHEAP_MARK;
    TBuf8 <12>  buf((const unsigned char *)"Hello");
    retval = Tbuf8ToString(buf, s);
    if (retval == ESuccess)
        {
        printf("TBuf8 to string conversion successful\n");
        }
    if (!strcmp(s.c_str(), "Hello"))
    {
    printf("tbuf8tostring Passed");
    }
    else
    {
    assert_failed = true;
    printf("Tbuf8ToString Failed");
    }  	
    __UHEAP_MARKEND;
    testResultXml("test_tbuf8tostring_positive1");
	return 0;
}
