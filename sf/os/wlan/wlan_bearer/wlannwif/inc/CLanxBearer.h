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
* Description:  Defines LanxBearer class
*
*/

/*
* %version: 8 %
*/

#ifndef CLANXBEARER_H
#define CLANXBEARER_H

#include <in_iface.h>
#include <comms-infras/nifif.h>
#include <e32uid.h>
#include <nifvar.h>
#include <nifutl.h>
#include <es_ini.h>
#include <es_mbuf.h>
#include <comms-infras/ss_protflow.h>
#include <comms-infras/ss_flowbinders.h>
#include <es_prot.h>


class CLANLinkCommon;
class TLanProvision;

NONSHARABLE_CLASS(CLanxBearer) : public CBase, public ESock::MLowerDataSender, public ESock::MLowerControl
{
public:
	CLanxBearer(CLANLinkCommon* aLink);
	virtual void ConstructL();
	
	// from MLowerControl
	virtual TInt GetName(TDes& aName);
	virtual TInt BlockFlow(TBlockOption aOption);
	virtual TInt GetConfig(TBinderConfig& aConfig) = 0;
	//
	
	virtual void StartSending(CProtocolBase* aProtocol);

	//Additional methods.
	virtual TBool WantsProtocol(TUint16 aProtocolCode, const TUint8* aPayload ) = 0;
	virtual void Process( RMBufChain& aPdu ) = 0;

	virtual void UpdateMACAddr();
    CLANLinkCommon* Link() const;
    
	// Support for CFProtocol based binding sequence
	virtual const TDesC8& ProtocolName() const = 0;
	void SetUpperPointers(ESock::MUpperDataReceiver* aReceiver, ESock::MUpperControl* aControl);
	TBool MatchesUpperControl(const ESock::MUpperControl* aControl) const;

	// Support for provisioning
	virtual void SetProvisionL(const Meta::SMetaData* aProvision) = 0;

protected: // Data
	ESock::MUpperControl* iUpperControl;
	ESock::MUpperDataReceiver* iUpperReceiver;
	CLANLinkCommon* iLink;
	TInterfaceName iIfName;

	// cache connection info to avoid dbms access after resume sending scenario
	TSoIfConnectionInfo iSoIfConnectionInfo;
	TBool iSoIfConnectionInfoCached;
};
    
inline CLANLinkCommon* CLanxBearer::Link() const
{
	return iLink;
}

#endif // CLANXBEARER_H
