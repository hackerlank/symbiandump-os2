/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies). 
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
* Rule which marks an object "read-only"
*
*/
package com.nokia.tracecompiler.rules;

import com.nokia.tracecompiler.model.TraceObjectRule;

/**
 * Rule which marks an object "read-only". Read-only objects cannot be updated
 * via UI
 * 
 */
public interface ReadOnlyObjectRule extends TraceObjectRule {

}
