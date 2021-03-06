/*
* Copyright (c) 2004-2009 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of the License "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description: 
* The panic method and panic code declarations
*
*/


/**
 @file 
 @publishedAll
 @released
*/

#ifndef __CAFPANIC_H__
#define __CAFPANIC_H__

#include <e32base.h>

/** Panic codes generated by the Content Access Framework 
*/
enum TCafPanics
	{
	ECafPanicDuplicateF32Agent 					= 1, ///< There appears to be more than one default agent
	ECafPanicNoF32Agent							= 2, ///< No default (F32) agent was found
	ECafPanicF32AgentImportNotSupported			= 3, ///< CAF should never ask the F32 agent to import files
	ECafPanicF32AgentRightManagerNotSupported   = 4, ///< CAF should never ask the F32 agent to invoke a rights manager
	ECafPanicF32AgentManagementInfoNotSupported = 5,  ///< CAF should never ask the F32 agent to display an agent management dialog for itself
	ECafPanicContentIteratorThreadPanic 		= 6,  ///< The content iterator thread panic'd
	ECafPanicContentIteratorUnknownRequest		= 7,  ///< The content iterator was asked to perform an unknown function
	ECafPanicF32AgentPrepareHTTPHeadersNotSupported = 8  ///< CAF should never ask the F32 agent for HTTP download headers
	};

_LIT(KCafPanicString,"CAF");

#endif // __CAFPANIC_H__

