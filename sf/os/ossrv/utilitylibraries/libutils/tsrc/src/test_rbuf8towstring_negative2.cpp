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
#include<e32base.h>
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
int main()
{
    int retval =ESuccess;
    wstring des;
    __UHEAP_MARK;
    {
    RBuf8  buf;
    buf.Create(10);
    buf.Copy((TUint8 *)"Hello", 5);
    buf.CleanupClosePushL();
    //int size =5;
    retval = Rbuf8ToWstring(buf, des  );

    if (retval == ESuccess)
    {
    printf("test rbuf8towstring negative2 Passed\n");
    }
    else
    {
    assert_failed = true;
    printf("test_rbuf8towstring negative2 Failed\n");
    }
    CleanupStack::PopAndDestroy(1);
    }
    __UHEAP_MARKEND;    
    testResultXml("test_rbuf8towstring_negative2");
	return 0;
}
