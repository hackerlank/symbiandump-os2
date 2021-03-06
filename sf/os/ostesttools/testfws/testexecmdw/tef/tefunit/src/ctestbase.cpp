/*
* Copyright (c) 2005-2009 Nokia Corporation and/or its subsidiary(-ies).
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



/**
 @file CTestBase.cpp
*/

#include "tefunit.h"

CTestBase::CTestBase(const TTestName &aName)
/**
 * Constructor
 *
 * @param aName - The name of the test
 */
	: iName(aName)
	{
	}

CTestBase::~CTestBase() 
/**
 * Destructor
 */
	{
	}

const TTestName& CTestBase::Name() const
/**
 * Name
 *
 * @return - The name of the test
 */
	{
	return iName;
	}
