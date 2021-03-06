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
* Name        : wcsupr.c
* Part of     : libc
* Interface   : 
* Implementation of wcsupr on Symbian
* Version     :
*
*/




#include <wchar.h>
#include <wctype.h>

EXPORT_C
wchar_t* wcsupr(wchar_t *wcs)
{
	wchar_t  *ptr = wcs;
	
	while (*ptr) 
	{
		*ptr = towupper(*ptr);
		ptr++;
	}
	return wcs;
}
