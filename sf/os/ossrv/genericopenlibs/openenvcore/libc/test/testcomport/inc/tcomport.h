/*
* Copyright (c) 2007-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Name        : tcomport.h
* 
*
*/



#ifndef __TCOMPORT_H__
#define __TCOMPORT_H__

#include <test/testexecutestepbase.h>
#define MAX_LEN 50

_LIT(Ktest_printf_COM, "test_printf_COM");
_LIT(Ktest_scanf_COM, "test_scanf_COM");


class CTestcomport : public CTestStep
	{
public:
	CTestcomport(const TDesC& aStepName);
	virtual ~CTestcomport(); 
	virtual TVerdict doTestStepL();

	TVerdict test_printf_COM();
	TVerdict test_scanf_COM();
	};
#endif //__TCOMPORT_H__
