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
    __UHEAP_MARK;
    {
    string s;
    TPtr8  buf((unsigned char *)"", 10);
    buf.Set((unsigned char *)"Hello", 5, 10);
//    int i=0;
//    while (i<=1000)
//    {
      retval = Tptr8ToString(buf, s);
      if(retval == ESuccess)
          printf("conversion succeeded\n");
//    i++;
//    printf("%d\n",i);
//    }    

    if (!strcmp(s.c_str(), "Hello"))
    {
    printf("tbuf8tostring Passed");
    }
    else
    {
    assert_failed = true;
    printf("tbuf8tostring Failed");
    }  	
    }
    __UHEAP_MARKEND;
    testResultXml("test_tptr8tostring_positive");
	
	return 0;
}
