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
    wstring des((const wchar_t*)"test");
    __UHEAP_MARK;
    TBufC8<30> buf((unsigned char*)"My wide string");
    TPtrC8 src(buf);
    int retval=ESuccess;
    //int size=2;
    retval= Tptrc8ToWstring(src,des);

    if(retval == ESuccess)
    {
    printf("Test tptrc8towstring negative1 passed\n");
    }
    else
    {
    assert_failed = true;
    printf("Test tptrc8towstring negative1 FAILURE\n");
    }	
    __UHEAP_MARKEND;
    testResultXml("test_tptrc8towstring_negative1");
	
	return 0;
}
