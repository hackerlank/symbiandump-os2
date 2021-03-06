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
    __UHEAP_MARK;
    {
    int retval[10];
    TBufC8<30> buf;
    TPtrC8 myTptr8 = buf.Des();
    wchar_t* myWchar = L"no_worth_purpose";
    char* temp = new char[15];
    retval[0] = WcharpToTptrc8(myWchar,temp,myTptr8);

    wstring myWstring;
    retval[1] = Tptrc8ToWstring(myTptr8,myWstring);

    TBufC<30> tbuf;
    TPtrC16 myTptr16 = tbuf.Des();
    retval[2] = WstringToTptrc16(myWstring,myTptr16);

    char* myChar = new char[40];
    int size = 40;
    retval[3] = Tptrc16ToCharp(myTptr16,myChar,size);

    TBufC8<30> buf8;
    TPtr8 myTptr = buf8.Des();  
    retval[4] = CharpToTptr8(myChar,myTptr);

    wchar_t* Wstr_fin = new wchar_t[36];
    int size_char=36;
    retval[5] = Tptr8ToWcharp(myTptr,Wstr_fin,size_char);
    
    for(int i=1; i<=5; i++)
        {
    if (retval[i]!= 0)
                printf("Conversion failed for retval\n",retval[i]);
        }

    if(!wcscmp(myWchar,Wstr_fin))
    {
    printf("\n\nintegration_test_scenario23 case passed");
    }
    else
    {
    printf("\n\nintegration_test_scenario23 case failed");
    assert_failed = true;
    }
    delete[] temp;
    delete[] myChar;
    delete[] Wstr_fin;	
    }
    __UHEAP_MARKEND;
    testResultXml("integration_test_scenario23");
    return 0;
}
