/*
* Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
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

#ifndef __T_LAYDOC_H__
#define __T_LAYDOC_H__

#include <test/testexecutestepbase.h>

class CT_LAYDOC : public CTestStep
	{
public:
	CT_LAYDOC();
protected:
	TVerdict doTestStepL();
private:
	};

_LIT(KTestStep_T_LAYDOC, "T_LAYDOC");

#endif
