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
#include <e32base.h>
#include "libutils.h"
#include"std_log_result.h"
#define LOG_FILENAME_LINE __FILE__, __LINE__
int main()
{
    __UHEAP_MARK;
    int retval =ESuccess;
    wchar_t* mycharstring = new wchar_t[600];
    _LIT8(KTxt, "HelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHelloHello");
    HBufC8* buff = HBufC8::NewL(600);
    *buff = KTxt;
    CleanupStack::PushL(buff);
    int size = 600;
    retval = HBufc8ToWchar(buff,mycharstring,size);

    if (retval ==ESuccess)
    {
    printf("hbufc8towchar Passed");
    }
    else
    {
    assert_failed = true;
    printf("hbufc8towchar failed");
    }      
    CleanupStack::PopAndDestroy(1);
    delete []mycharstring;
    mycharstring = NULL; 
    __UHEAP_MARKEND;
    testResultXml("test_hbufc8towchar_boundary1");
	return 0;
}
