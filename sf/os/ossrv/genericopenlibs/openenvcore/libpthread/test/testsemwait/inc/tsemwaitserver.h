/*
* Copyright (c) 2002-2009 Nokia Corporation and/or its subsidiary(-ies).
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
* Name        : tsemwaitserver.h
* Part of     : testsemwait
* This material, including documentation and any related 
* computer programs, is protected by copyright controlled by 
* Nokia Corporation. All rights are reserved. Copying, 
* including reproducing, storing,  adapting or translating, any 
* or all of this material requires the prior written consent of 
* Nokia Corporation. This material also contains confidential 
* information which may not be disclosed to others without the 
* prior written consent of Nokia Corporation.
*
*/



#ifndef __TSEMWAITSERVER_H__
#define __TSEMWAITSERVER_H__

#include <f32file.h>
#include <test/testexecuteserverbase.h>

class CSemwaitTestServer : public CTestServer
	{
public:
	static CSemwaitTestServer* NewL();
	virtual CTestStep* CreateTestStep(const TDesC& aStepName);
	RFs& Fs() {return iFs;}

private:
	RFs iFs;
	};

#endif // 
