// Copyright (c) 2008-2009 Nokia Corporation and/or its subsidiary(-ies).
// All rights reserved.
// This component and the accompanying materials are made available
// under the terms of "Eclipse Public License v1.0"
// which accompanies this distribution, and is available
// at the URL "http://www.eclipse.org/legal/epl-v10.html".
//
// Initial Contributors:
// Nokia Corporation - initial contribution.
//
// Contributors:
//
// Description:
// Name        : tcapclock.cpp
// 
//

 

#include "tcapclock.h"

Ctestcapclock::~Ctestcapclock() 
	{ 
	}  

Ctestcapclock::Ctestcapclock(const TDesC& aStepName)
	{
	// MANDATORY Call to base class method to set up the human readable name for logging.
	SetTestStepName(aStepName);		
	}

TVerdict Ctestcapclock::doTestStepPreambleL()
	{
	__UHEAP_MARK;	
	SetTestStepResult(EPass);
	return TestStepResult();
	}



TVerdict Ctestcapclock::doTestStepPostambleL()
	{
	__UHEAP_MARKEND;	
	return TestStepResult();
	}


TVerdict Ctestcapclock::doTestStepL()
	{
	int err;
	
	//captest steps
	if(TestStepName() == KTestcapclocksettime1)
   			{
   	   		INFO_PRINTF1(_L("Testcapclocksettime1():"));
   	   		err = Testcapclocksettime1();
   	   		SetTestStepResult(err ? static_cast<TVerdict>(err) : EPass);
   	   		}
	return TestStepResult(); 

	}
 
