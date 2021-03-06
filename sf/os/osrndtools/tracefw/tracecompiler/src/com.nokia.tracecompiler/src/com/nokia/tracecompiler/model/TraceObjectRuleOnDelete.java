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
* Rule to perform processing when object is deleted
*
*/
package com.nokia.tracecompiler.model;

/**
 * Rule to perform processing when object is deleted
 * 
 */
public interface TraceObjectRuleOnDelete extends TraceObjectRule {

	/**
	 * Called when the object that owns this rule is deleted
	 */
	public void objectDeleted();

}
