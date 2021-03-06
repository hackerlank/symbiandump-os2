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
*/

#include <e32std.h>

extern "C"   {

EXPORT_C unsigned int sleep (unsigned int secs)
	{
	if(((int)secs < 0)) 
		{
		return 0 ;
		}
	// we don't allow the possibility of being woken by signals
	User::After(secs*1000000);
	return 0;
	}

}  //extern "C"
