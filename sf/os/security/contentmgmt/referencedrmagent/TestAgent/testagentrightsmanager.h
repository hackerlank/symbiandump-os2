/*
* Copyright (c) 2003-2009 Nokia Corporation and/or its subsidiary(-ies).
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
*
*/


#ifndef __TESTAGENTRIGHTSMANAGER_H__
#define __TESTAGENTRIGHTSMANAGER_H__

#include <caf/caf.h>
#include "agentinterface.h"

/** A simple agent implementing a small part of OMA DRM v1.0

Several of the functions such as Copy, Rename and GetDir are not supported
by this agent.

 */
class CTestAgentRightsManager : public ContentAccess::CAgentRightsManager
		{
	public:
		static CTestAgentRightsManager* NewL();
		static CTestAgentRightsManager* NewLC();

		~CTestAgentRightsManager();

	public:
		// From CAgentRightsManager
		virtual void  ListAllRightsL (ContentAccess::RStreamablePtrArray< ContentAccess::CRightsInfo > &aArray) const; 
		virtual void  ListRightsL (ContentAccess::RStreamablePtrArray< ContentAccess::CRightsInfo > &aArray, const TDesC &aUri) const;  
		virtual void  ListRightsL (ContentAccess::RStreamablePtrArray< ContentAccess::CRightsInfo > &aArray, ContentAccess::TVirtualPathPtr &aVirtualPath) const;
		virtual void  ListContentL (ContentAccess::RStreamablePtrArray< ContentAccess::CVirtualPath > &aArray, ContentAccess::CRightsInfo &aRightsInfo) const;
		virtual ContentAccess::MAgentRightsBase *  GetRightsDataL (const ContentAccess::CRightsInfo &aRightsInfo) const;
		virtual TInt  DeleteRightsObject (const ContentAccess::CRightsInfo &aRightsInfo);
		virtual TInt  DeleteAllRightsObjects (const ContentAccess::TVirtualPathPtr &aVirtualPath);
		virtual TInt SetProperty(ContentAccess::TAgentProperty aProperty, TInt aValue);
	private:
		CTestAgentRightsManager();
		};

#endif // __TESTAGENTMANAGER_H__
